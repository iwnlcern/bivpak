#include "core/pack/pack.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <exception>
#include <fstream>
#include <random>
#include <span>
#include <sstream>
#include <string_view>
#include <system_error>

#include <fcntl.h>
#include <sys/random.h>
#include <unistd.h>

#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/manifest/checksums.hpp"
#include "core/scan/scan.hpp"
#include "core/support/version.hpp"

namespace biv::pack {

namespace {

struct ClockStamp {
  int64_t seconds;
  std::string rfc3339;
};

std::filesystem::path existing_canonical(const std::filesystem::path& path, std::error_code& ec) {
  auto canonical = std::filesystem::weakly_canonical(path, ec);
  if (ec) {
    return {};
  }
  return canonical;
}

bool lexically_inside(const std::filesystem::path& candidate, const std::filesystem::path& root) {
  const auto rel = candidate.lexically_normal().lexically_relative(root.lexically_normal());
  if (rel.empty()) {
    return false;
  }
  const auto begin = rel.begin();
  if (begin == rel.end()) {
    return false;
  }
  return *begin != "..";
}

BivError with_temp_facts(BivError error,
                         const std::filesystem::path& partial_path,
                         const std::filesystem::path& spool_path) {
  error.facts.try_emplace("partial_path", partial_path.generic_string());
  error.facts.try_emplace("spool_path", spool_path.generic_string());
  return error;
}

expected<void> write_bytes(std::ofstream& out, std::span<const std::byte> bytes, const std::filesystem::path& path) {
  std::string chunk;
  chunk.reserve(bytes.size());
  for (const auto byte : bytes) {
    chunk.push_back(static_cast<char>(byte));
  }
  out.write(chunk.data(), static_cast<std::streamsize>(chunk.size()));
  if (!out) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  return {};
}

expected<void> fsync_path(const std::filesystem::path& path, bool directory) {
  const int flags = O_RDONLY | O_CLOEXEC | (directory ? O_DIRECTORY : 0);
  const int fd = ::open(path.c_str(), flags);
  if (fd < 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string(), {}, errno});
  }
  const int rc = ::fsync(fd);
  const int saved_errno = errno;
  ::close(fd);
  if (rc != 0) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string(), {}, saved_errno});
  }
  return {};
}

std::string uuid4() {
  std::array<unsigned char, 16> bytes {};
  if (::getrandom(bytes.data(), bytes.size(), 0) != static_cast<ssize_t>(bytes.size())) {
    std::random_device rd;
    for (auto& byte : bytes) {
      byte = static_cast<unsigned char>(rd());
    }
  }
  bytes.at(6) = static_cast<unsigned char>((bytes.at(6) & 0x0fU) | 0x40U);
  bytes.at(8) = static_cast<unsigned char>((bytes.at(8) & 0x3fU) | 0x80U);

  constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  out.reserve(36);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (i == 4U || i == 6U || i == 8U || i == 10U) {
      out.push_back('-');
    }
    out.push_back(hex.at((bytes.at(i) >> 4U) & 0x0fU));
    out.push_back(hex.at(bytes.at(i) & 0x0fU));
  }
  return out;
}

ClockStamp now_stamp() {
  const auto now = std::chrono::system_clock::now();
  const auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
  const std::time_t time = std::chrono::system_clock::to_time_t(seconds);
  std::tm tm {};
  gmtime_r(&time, &tm);
  std::array<char, 32> buffer {};
  const size_t written = std::strftime(buffer.data(), buffer.size(), "%FT%TZ", &tm);
  if (written == 0U) {
    return ClockStamp{.seconds = static_cast<int64_t>(time), .rfc3339 = {}};
  }
  return ClockStamp{.seconds = static_cast<int64_t>(time), .rfc3339 = buffer.data()};
}

manifest::PathFlavor path_flavor(const std::filesystem::path& path) {
  const auto text = path.generic_string();
  if (text.size() >= 7U && text.starts_with("/mnt/") && text.at(6) == '/') {
    const char drive = text.at(5);
    if ((drive >= 'a' && drive <= 'z') || (drive >= 'A' && drive <= 'Z')) {
      return manifest::PathFlavor::wsl;
    }
  }
  return manifest::PathFlavor::posix;
}

expected<void> copy_file_to_sink(const std::filesystem::path& path, container::TarWriter::Sink sink);

expected<std::string> write_payload_member(container::TarWriter& writer,
                                           const std::filesystem::path& source_root,
                                           const scan::Node& node) {
  const std::string archive_path = "payload/" + node.relpath;
  const auto abs = source_root / std::filesystem::path{node.relpath};
  const container::MemberMeta meta{
      .path = archive_path,
      .kind = node.kind,
      .mode = node.mode,
      .mtime_s = node.mtime_s,
      .mtime_ns = node.mtime_ns,
      .size = node.size,
      .symlink_target = node.symlink_target,
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return std::unexpected(ok.error());
  }
  if (node.kind == scan::NodeKind::file) {
    auto ok = copy_file_to_sink(abs, [&](std::span<const std::byte> chunk) -> expected<void> {
      return writer.write_data(chunk);
    });
    if (!ok) {
      return std::unexpected(ok.error());
    }
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return *extent;
}

expected<void> write_string_member(container::TarWriter& writer,
                                   std::string_view path,
                                   std::string_view bytes,
                                   int64_t mtime_s) {
  const container::MemberMeta meta{
      .path = std::string{path},
      .kind = scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = mtime_s,
      .mtime_ns = 0,
      .size = bytes.size(),
      .symlink_target = {},
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return ok;
  }
  if (auto ok = writer.write_data(std::as_bytes(std::span<const char>{bytes.data(), bytes.size()})); !ok) {
    return ok;
  }
  auto extent = writer.end_member();
  if (!extent) {
    return std::unexpected(extent.error());
  }
  return {};
}

expected<void> copy_file_to_sink(const std::filesystem::path& path, container::TarWriter::Sink sink) {
  std::ifstream in{path, std::ios::binary};
  if (!in) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  std::array<char, 8192> buffer {};
  while (in) {
    in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    const auto count = in.gcount();
    if (count > 0) {
      auto ok = sink(std::as_bytes(std::span<const char>{buffer.data(), static_cast<size_t>(count)}));
      if (!ok) {
        return ok;
      }
    }
  }
  if (in.bad()) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, path.generic_string()});
  }
  return {};
}

expected<PackReport> pack_impl(const std::filesystem::path& source_dir) {
  std::error_code ec;
  const auto source = existing_canonical(source_dir, ec);
  if (ec || !std::filesystem::is_directory(source, ec)) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, source_dir.generic_string(),
                                    ec ? ec.message() : "not-directory", static_cast<int>(ec.value())});
  }

  const auto name = source.filename().generic_string();
  const auto image_path = (source.parent_path() / (name + ".bvpk")).lexically_normal();
  const auto partial_path = (source.parent_path() / (name + ".bvpk.partial")).lexically_normal();
  const auto spool_path = (source.parent_path() / (name + ".bvpk.spool")).lexically_normal();
  if (lexically_inside(image_path, source) || lexically_inside(partial_path, source) ||
      lexically_inside(spool_path, source)) {
    return std::unexpected(with_temp_facts(BivError{ErrKind::OutputInsideSource, image_path.generic_string()},
                                           partial_path,
                                           spool_path));
  }
  if (std::filesystem::exists(partial_path, ec) || std::filesystem::exists(spool_path, ec)) {
    BivError error{ErrKind::PartialPresent};
    if (std::filesystem::exists(partial_path)) {
      error.facts["partial_path"] = partial_path.generic_string();
    }
    if (std::filesystem::exists(spool_path)) {
      error.facts["spool_path"] = spool_path.generic_string();
    }
    return std::unexpected(error);
  }

  auto cleanup_error = [&](BivError error) {
    std::error_code cleanup_ec;
    std::filesystem::remove(partial_path, cleanup_ec);
    std::filesystem::remove(spool_path, cleanup_ec);
    return std::unexpected(with_temp_facts(std::move(error), partial_path, spool_path));
  };

  auto scan_result = scan::scan(source);
  if (!scan_result) {
    return cleanup_error(scan_result.error());
  }

  manifest::Checksums checksums;
  PackReport report;
  report.image_path = image_path.generic_string();
  report.source_path = source.generic_string();
  report.flavor = path_flavor(source);
  report.image_id = uuid4();
  for (const auto& path : scan_result->skipped_unsupported) {
    report.warnings.push_back(Warning{.kind = "UnsupportedFileTypeSkipped", .path = path});
  }
  for (const auto& path : scan_result->unreadable) {
    report.warnings.push_back(Warning{.kind = "SourceUnreadableSubpath", .path = path});
  }
  if (!scan_result->pruned.empty()) {
    report.advisories.push_back(Advisory{.kind = "prune-summary", .entries = scan_result->pruned, .paths = {}});
  }
  if (!scan_result->nested_bivignore.empty()) {
    report.advisories.push_back(
        Advisory{.kind = "nested-bivignore-ignored", .entries = {}, .paths = scan_result->nested_bivignore});
  }

  {
    std::ofstream spool{spool_path, std::ios::binary};
    if (!spool) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, spool_path.generic_string()});
    }
    container::TarWriter spool_writer{[&](std::span<const std::byte> chunk) -> expected<void> {
      return write_bytes(spool, chunk, spool_path);
    }};
    for (const auto& node : scan_result->payload) {
      auto extent = write_payload_member(spool_writer, source, node);
      if (!extent) {
        return cleanup_error(extent.error());
      }
      const std::string archive_path = "payload/" + node.relpath;
      checksums.entries[archive_path] = std::move(*extent);
      ++report.member_count;
      if (node.kind == scan::NodeKind::file) {
        report.payload_bytes += node.size;
      }
    }
    if (auto ok = spool_writer.finish(); !ok) {
      return cleanup_error(ok.error());
    }
  }

  const auto created = now_stamp();
  const manifest::Manifest manifest_model{
      .format_version = manifest::kFormatVersion,
      .required_capabilities = {},
      .image_id = report.image_id,
      .app_version = app_version(),
      .created_at = created.rfc3339,
      .source_path = source.generic_string(),
      .source_path_flavor = report.flavor,
      .agent_sessions = {},
      .bivignore = scan_result->bivignore,
  };
  const std::string manifest_json = manifest::serialize(manifest_model);
  const std::string checksums_json = manifest::serialize(checksums);

  {
    std::ofstream partial{partial_path, std::ios::binary};
    if (!partial) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, partial_path.generic_string()});
    }
    container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk) -> expected<void> {
      return write_bytes(partial, chunk, partial_path);
    }};
    auto zstd_sink = zstd.as_sink();
    container::TarWriter archive{zstd_sink};
    if (auto ok = write_string_member(archive, "manifest.json", manifest_json, created.seconds); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = write_string_member(archive, "checksums.json", checksums_json, created.seconds); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = copy_file_to_sink(spool_path, zstd_sink); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = archive.finish(); !ok) {
      return cleanup_error(ok.error());
    }
    if (auto ok = zstd.finish(); !ok) {
      return cleanup_error(ok.error());
    }
  }

  if (auto ok = fsync_path(partial_path, false); !ok) {
    return cleanup_error(ok.error());
  }
  if (auto ok = fsync_path(partial_path.parent_path(), true); !ok) {
    return cleanup_error(ok.error());
  }
  std::filesystem::rename(partial_path, image_path, ec);
  if (ec) {
    return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, image_path.generic_string(), ec.message(),
                                  static_cast<int>(ec.value())});
  }
  if (auto ok = fsync_path(image_path.parent_path(), true); !ok) {
    return cleanup_error(ok.error());
  }
  std::filesystem::remove(spool_path, ec);
  return report;
}

}  // namespace

expected<PackReport> pack(const std::filesystem::path& source_dir) {
  try {
    return pack_impl(source_dir);
  } catch (const std::exception& error) {
    return std::unexpected(BivError{ErrKind::InternalError, source_dir.generic_string(), error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, source_dir.generic_string(), "pack"});
  }
}

}  // namespace biv::pack
