#include "core/pack/pack.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <exception>
#include <fstream>
#include <optional>
#include <random>
#include <set>
#include <span>
#include <sstream>
#include <string_view>
#include <system_error>

#include <fcntl.h>
#include <sys/random.h>
#include <unistd.h>

#include "adapters/registry.hpp"
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

expected<std::string> write_file_member(container::TarWriter& writer,
                                        const std::filesystem::path& source,
                                        const std::string_view archive_path,
                                        const int64_t mtime_s) {
  std::error_code ec;
  const auto size = std::filesystem::file_size(source, ec);
  if (ec) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, source.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }
  const container::MemberMeta meta{
      .path = std::string{archive_path},
      .kind = scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = mtime_s,
      .mtime_ns = 0,
      .size = size,
      .symlink_target = {},
  };
  if (auto ok = writer.begin_member(meta); !ok) {
    return std::unexpected(ok.error());
  }
  auto copied = copy_file_to_sink(source, [&](std::span<const std::byte> chunk) -> expected<void> {
    return writer.write_data(chunk);
  });
  if (!copied) {
    return std::unexpected(copied.error());
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

adapters::Env process_env() {
  return adapters::Env{
      .getenv = [](const std::string_view name) -> std::optional<std::string> {
        const std::string key{name};
        if (const char* value = std::getenv(key.c_str()); value != nullptr) {
          return std::string{value};
        }
        return std::nullopt;
      },
      .home = [] {
        if (const char* value = std::getenv("HOME"); value != nullptr) {
          return std::filesystem::path{value};
        }
        return std::filesystem::path{};
      }()};
}

std::string relpath_key_for(const std::filesystem::path& source, std::string_view original_path) {
  const auto rel = std::filesystem::path{original_path}.lexically_normal().lexically_relative(source.lexically_normal());
  if (rel.empty() || rel == ".") {
    return ".";
  }
  return rel.generic_string();
}

struct ChildArtifactMatcher {
  std::string_view child_id;

  bool matches(std::string_view artifact) const {
    const std::string child_jsonl = std::string{child_id} + ".jsonl";
    size_t start = 0;
    while (start <= artifact.size()) {
      const size_t slash = artifact.find('/', start);
      const size_t end =
          slash == std::string_view::npos ? artifact.size() : slash;
      const std::string_view segment = artifact.substr(start, end - start);
      if (segment == child_id || segment == child_jsonl ||
          (segment.starts_with(child_id) && segment.size() > child_id.size() &&
           segment.at(child_id.size()) == '.')) {
        return true;
      }
      if (slash == std::string_view::npos) {
        break;
      }
      start = slash + 1U;
    }
    return false;
  }
};

manifest::AgentSessionEntry manifest_entry_for(const adapters::SessionRecord& session,
                                               const std::filesystem::path& source,
                                               const std::string& imported_at) {
  std::vector<manifest::SessionChild> children;
  std::vector<std::string> parent_artifacts;
  for (const auto& child_id : session.child_ids) {
    const ChildArtifactMatcher child_matcher{.child_id = child_id};
    std::vector<std::string> child_artifacts;
    for (const auto& artifact : session.artifacts) {
      if (child_matcher.matches(artifact)) {
        child_artifacts.push_back(artifact);
      }
    }
    children.push_back(manifest::SessionChild{.original_id = child_id, .artifacts = std::move(child_artifacts)});
  }
  for (const auto& artifact : session.artifacts) {
    const bool belongs_to_child = std::ranges::any_of(session.child_ids, [&](const std::string& child_id) {
      return ChildArtifactMatcher{.child_id = child_id}.matches(artifact);
    });
    if (!belongs_to_child) {
      parent_artifacts.push_back(artifact);
    }
  }

  return manifest::AgentSessionEntry{
      .agent = session.agent,
      .agent_version_at_pack = session.agent_version_at_pack,
      .relpath_key = relpath_key_for(source, session.original_path),
      .original_path = session.original_path,
      .normalized_path_key = session.normalized_path_key,
      .normalization_scheme = session.normalization_scheme,
      .path_flavor = session.path_flavor,
      .provenance = session.provenance,
      .original_session_ids = {.primary = session.original_session_id,
                               .parent = session.parent_id,
                               .parent_in_image =
                                   session.parent_id.has_value()
                                       ? std::optional<bool>{false}
                                       : std::nullopt},
      .children = std::move(children),
      .artifacts = std::move(parent_artifacts),
      .live_at_pack = session.live_at_pack,
      .imported_at = imported_at,
      .entry_schema = 1};
}

void add_summary(PackReport& report, std::string_view agent) {
  auto found = std::ranges::find_if(report.agent_sessions_summary, [&](const AgentSessionsSummary& summary) {
    return summary.agent == agent;
  });
  if (found == report.agent_sessions_summary.end()) {
    report.agent_sessions_summary.push_back(AgentSessionsSummary{.agent = std::string{agent}, .session_count = 1});
  } else {
    ++found->session_count;
  }
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

  const auto created = now_stamp();
  {
    std::ofstream spool{spool_path, std::ios::binary};
    if (!spool) {
      return cleanup_error(BivError{ErrKind::ArchiveWriteFailed, spool_path.generic_string()});
    }
    container::TarWriter spool_writer{
        [&](std::span<const std::byte> chunk) -> expected<void> {
          return write_bytes(spool, chunk, spool_path);
        }};
    std::set<std::pair<std::string, std::string>> emitted_agent_sessions;
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
    const auto env = process_env();
    for (const auto* adapter : adapters::all_adapters()) {
      auto stores = adapter->discover(env);
      if (!stores) {
        return cleanup_error(stores.error());
      }
      if (stores->empty()) {
        continue;
      }
      auto collected = adapter->collect(source, *stores);
      if (!collected) {
        return cleanup_error(collected.error());
      }
      for (const auto& path : collected->no_cwd_record) {
        report.warnings.push_back(Warning{.kind = "SessionNoCwdRecord", .path = path});
      }
      for (const auto& session : collected->sessions) {
        if (!emitted_agent_sessions
                 .insert({session.agent, session.original_session_id})
                 .second) {
          continue;
        }
        if (session.artifacts.size() != session.artifact_sources.size()) {
          return cleanup_error(BivError{ErrKind::InternalError, {}, "adapter-artifact-sources"});
        }
        for (size_t i = 0; i < session.artifacts.size(); ++i) {
          auto extent = write_file_member(spool_writer, session.artifact_sources.at(i), session.artifacts.at(i),
                                          created.seconds);
          if (!extent) {
            return cleanup_error(extent.error());
          }
          checksums.entries[session.artifacts.at(i)] = std::move(*extent);
          ++report.member_count;
        }
        if (session.live_at_pack) {
          report.warnings.push_back(Warning{.kind = "SessionLiveAtPack", .path = session.original_session_id});
        }
        report.agent_sessions.push_back(manifest_entry_for(session, source, created.rfc3339));
        add_summary(report, session.agent);
      }
    }
    if (auto ok = spool_writer.finish(); !ok) {
      return cleanup_error(ok.error());
    }
  }

  const manifest::Manifest manifest_model{
      .format_version = manifest::kFormatVersion,
      .required_capabilities = {},
      .image_id = report.image_id,
      .app_version = app_version(),
      .created_at = created.rfc3339,
      .source_path = source.generic_string(),
      .source_path_flavor = report.flavor,
      .agent_sessions = report.agent_sessions,
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
