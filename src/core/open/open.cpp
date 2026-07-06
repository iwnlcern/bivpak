#include "core/open/open.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <span>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "core/container/tar_reader.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"

namespace biv::open {

namespace {

constexpr uint64_t kManifestMemberCap = manifest::kManifestByteCap;
constexpr uint64_t kChecksumsMemberCap = manifest::kChecksumsByteCap;

struct PlannedMember {
  container::MemberMeta meta;
  std::string extent;
};

struct ArchivePlan {
  manifest::Manifest manifest;
  manifest::Checksums checksums;
  std::vector<PlannedMember> payload;
};

bool has_zstd_magic(std::span<const std::byte> bytes) {
  if (bytes.size() < container::kZstdMagic.size()) {
    return false;
  }
  auto byte = bytes.begin();
  for (const unsigned char magic : container::kZstdMagic) {
    if (*byte != static_cast<std::byte>(magic)) {
      return false;
    }
    ++byte;
  }
  return true;
}

std::span<const std::byte> byte_span(const std::vector<std::byte>& bytes) {
  return std::span<const std::byte>{bytes.data(), bytes.size()};
}

template <typename Func>
auto with_tar_reader(const std::filesystem::path& image, Func func) -> decltype(func(std::declval<container::TarReader&>())) {
  std::ifstream input{image, std::ios::binary};
  if (!input) {
    return std::unexpected(BivError{ErrKind::ImageUnreadable, image.generic_string()});
  }

  std::array<char, 8192> first_buffer {};
  input.read(first_buffer.data(), static_cast<std::streamsize>(first_buffer.size()));
  const auto first_count = input.gcount();
  if (first_count <= 0) {
    return std::unexpected(BivError{ErrKind::NotABivpakImage, image.generic_string()});
  }
  if (input.bad()) {
    return std::unexpected(BivError{ErrKind::ImageUnreadable, image.generic_string()});
  }

  std::vector<std::byte> first_chunk;
  first_chunk.reserve(static_cast<size_t>(first_count));
  for (std::streamsize i = 0; i < first_count; ++i) {
    first_chunk.push_back(static_cast<std::byte>(first_buffer.at(static_cast<size_t>(i))));
  }
  if (!has_zstd_magic(first_chunk)) {
    return std::unexpected(BivError{ErrKind::NotABivpakImage, image.generic_string()});
  }

  bool served_first = false;
  std::array<char, 8192> read_buffer {};
  container::ZstdDecompressSource source{[&]() -> expected<std::span<const std::byte>> {
    if (!served_first) {
      served_first = true;
      return byte_span(first_chunk);
    }
    input.read(read_buffer.data(), static_cast<std::streamsize>(read_buffer.size()));
    const auto count = input.gcount();
    if (count > 0) {
      return std::as_bytes(std::span<const char>{read_buffer.data(), static_cast<size_t>(count)});
    }
    if (input.bad()) {
      return std::unexpected(BivError{ErrKind::ImageUnreadable, image.generic_string()});
    }
    return std::span<const std::byte>{};
  }};
  container::TarReader reader{source};
  return func(reader);
}

BivError preapply_error(BivError error, const std::filesystem::path& image) {
  if (error.kind == ErrKind::NotABivpakImage || error.kind == ErrKind::ImageUnreadable) {
    return error;
  }
  if (error.kind == ErrKind::MemberPathUnsafe || error.kind == ErrKind::UnmanifestedMember ||
      error.kind == ErrKind::FormatVersionUnsupported || error.kind == ErrKind::UnknownRequiredCapability) {
    return error;
  }
  if (error.kind == ErrKind::IntegrityFailurePreApply) {
    return error;
  }
  return BivError{ErrKind::IntegrityFailurePreApply, image.generic_string(), error.detail, error.err_no, error.facts};
}

expected<std::vector<std::byte>> read_member_data(container::TarReader& reader,
                                                  const container::MemberMeta& meta,
                                                  uint64_t cap) {
  std::vector<std::byte> data;
  std::array<std::byte, 8192> buffer {};
  while (true) {
    auto n = reader.read_data(buffer);
    if (!n) {
      return std::unexpected(n.error());
    }
    if (*n == 0U) {
      break;
    }
    if (data.size() > cap - *n) {
      return std::unexpected(BivError{ErrKind::ParseError, meta.path, "member-size"});
    }
    data.insert(data.end(), buffer.begin(), std::next(buffer.begin(), static_cast<std::ptrdiff_t>(*n)));
  }
  return data;
}

expected<void> drain_member(container::TarReader& reader) {
  std::array<std::byte, 8192> buffer {};
  while (true) {
    auto n = reader.read_data(buffer);
    if (!n) {
      return std::unexpected(n.error());
    }
    if (*n == 0U) {
      return {};
    }
  }
}

expected<container::RMember> require_member(container::TarReader& reader, std::string_view path) {
  auto next = reader.next();
  if (!next) {
    return std::unexpected(next.error());
  }
  if (!*next || next->value().meta.path != path || next->value().meta.kind != scan::NodeKind::file) {
    return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, std::string{path}, "member-order"});
  }
  return **next;
}

expected<ArchivePlan> read_archive_plan(const std::filesystem::path& image, bool verify) {
  return with_tar_reader(image, [&](container::TarReader& reader) -> expected<ArchivePlan> {
    auto manifest_member = require_member(reader, "manifest.json");
    if (!manifest_member) {
      return std::unexpected(manifest_member.error());
    }
    auto manifest_bytes = read_member_data(reader, manifest_member->meta, kManifestMemberCap);
    if (!manifest_bytes) {
      return std::unexpected(manifest_bytes.error());
    }
    auto manifest_model = manifest::parse(byte_span(*manifest_bytes));
    if (!manifest_model) {
      return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, image.generic_string(),
                                      manifest_model.error().detail});
    }
    if (manifest_model->format_version != manifest::kFormatVersion) {
      return std::unexpected(BivError{ErrKind::FormatVersionUnsupported, image.generic_string()});
    }
    if (!manifest_model->required_capabilities.empty()) {
      return std::unexpected(BivError{ErrKind::UnknownRequiredCapability, image.generic_string(),
                                      manifest_model->required_capabilities.front()});
    }

    auto checksums_member = require_member(reader, "checksums.json");
    if (!checksums_member) {
      return std::unexpected(checksums_member.error());
    }
    auto checksums_bytes = read_member_data(reader, checksums_member->meta, kChecksumsMemberCap);
    if (!checksums_bytes) {
      return std::unexpected(checksums_bytes.error());
    }
    auto checksums = manifest::parse_checksums(byte_span(*checksums_bytes));
    if (!checksums) {
      return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, image.generic_string(),
                                      checksums.error().detail});
    }

    ArchivePlan plan{.manifest = std::move(*manifest_model), .checksums = std::move(*checksums), .payload = {}};
    std::set<std::string> seen;
    while (true) {
      auto next = reader.next();
      if (!next) {
        return std::unexpected(next.error());
      }
      if (!*next) {
        break;
      }
      auto member = **next;
      if (!member.meta.path.starts_with("payload/") || !plan.checksums.entries.contains(member.meta.path)) {
        return std::unexpected(BivError{ErrKind::UnmanifestedMember, member.meta.path});
      }
      if (auto ok = drain_member(reader); !ok) {
        return std::unexpected(ok.error());
      }
      const auto extent = reader.extent_sha256_hex();
      if (verify && plan.checksums.entries.at(member.meta.path) != extent) {
        return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, member.meta.path, "checksum"});
      }
      seen.insert(member.meta.path);
      plan.payload.push_back(PlannedMember{.meta = std::move(member.meta), .extent = extent});
    }
    for (const auto& [path, digest] : plan.checksums.entries) {
      (void)digest;
      if (!seen.contains(path)) {
        return std::unexpected(BivError{ErrKind::UnmanifestedMember, path});
      }
    }
    return plan;
  });
}

std::filesystem::path default_dest_for(const std::filesystem::path& image) {
  auto name = image.filename().generic_string();
  if (name.ends_with(".bvpk")) {
    name.resize(name.size() - 5U);
  }
  return std::filesystem::current_path() / name;
}

std::filesystem::path choose_rename_dest(const std::filesystem::path& dest) {
  for (int index = 1; index < 10000; ++index) {
    auto candidate = dest.parent_path() / (dest.filename().generic_string() + "(" + std::to_string(index) + ")");
    std::error_code ec;
    if (!std::filesystem::exists(candidate, ec)) {
      return candidate;
    }
  }
  return {};
}

BivError with_partial_dir(BivError error, const std::filesystem::path& partial_dir) {
  error.facts["partial_dir"] = partial_dir.generic_string();
  return error;
}

std::filesystem::path containing_dir(const std::filesystem::path& path) {
  const auto parent = path.parent_path();
  return parent.empty() ? std::filesystem::path{"."} : parent;
}

expected<void> set_mode(const std::filesystem::path& path, uint32_t mode) {
  std::error_code ec;
  std::filesystem::permissions(path,
                               static_cast<std::filesystem::perms>(mode & 0777U),
                               std::filesystem::perm_options::replace,
                               ec);
  if (ec) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }
  return {};
}

expected<void> set_mtime(const std::filesystem::path& path, int64_t seconds, uint32_t nanoseconds) {
  std::array<timespec, 2> times{timespec{.tv_sec = seconds, .tv_nsec = nanoseconds},
                                timespec{.tv_sec = seconds, .tv_nsec = nanoseconds}};
  if (::utimensat(AT_FDCWD, path.c_str(), times.data(), AT_SYMLINK_NOFOLLOW) != 0) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string(), {}, errno});
  }
  return {};
}

expected<void> fsync_path(const std::filesystem::path& path, bool directory) {
  const int flags = O_RDONLY | O_CLOEXEC | (directory ? O_DIRECTORY : 0);
  const int fd = ::open(path.c_str(), flags);
  if (fd < 0) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string(), {}, errno});
  }
  const int rc = ::fsync(fd);
  const int saved_errno = errno;
  ::close(fd);
  if (rc != 0) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string(), {}, saved_errno});
  }
  return {};
}

expected<void> fsync_tree(const std::filesystem::path& root) {
  std::error_code ec;
  for (const auto& entry : std::filesystem::recursive_directory_iterator(root, std::filesystem::directory_options::none, ec)) {
    if (ec) {
      return std::unexpected(BivError{ErrKind::RestoreWriteFailed, root.generic_string(), ec.message(),
                                      static_cast<int>(ec.value())});
    }
    const auto status = entry.symlink_status(ec);
    if (ec) {
      return std::unexpected(BivError{ErrKind::RestoreWriteFailed, entry.path().generic_string(), ec.message(),
                                      static_cast<int>(ec.value())});
    }
    if (std::filesystem::is_regular_file(status)) {
      if (auto ok = fsync_path(entry.path(), false); !ok) {
        return ok;
      }
    }
  }
  return fsync_path(root, true);
}

expected<void> write_file_stream(const std::filesystem::path& path,
                                 container::TarReader& reader,
                                 const container::MemberMeta& meta) {
  std::ofstream out{path, std::ios::binary};
  if (!out) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string()});
  }
  std::array<std::byte, 8192> buffer {};
  while (true) {
    auto n = reader.read_data(buffer);
    if (!n) {
      return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, meta.path, n.error().detail,
                                      n.error().err_no, n.error().facts});
    }
    if (*n == 0U) {
      break;
    }
    std::string chunk;
    chunk.reserve(*n);
    for (size_t i = 0; i < *n; ++i) {
      chunk.push_back(static_cast<char>(buffer.at(i)));
    }
    out.write(chunk.data(), static_cast<std::streamsize>(chunk.size()));
    if (!out) {
      return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string()});
    }
  }
  out.flush();
  if (!out) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string()});
  }
  return {};
}

expected<std::filesystem::path> contained_output_path(const container::MemberMeta& meta,
                                                      const std::filesystem::path& temp_root,
                                                      const std::map<std::string, scan::NodeKind>& created) {
  constexpr std::string_view prefix = "payload/";
  if (!meta.path.starts_with(prefix)) {
    return std::unexpected(BivError{ErrKind::UnmanifestedMember, meta.path});
  }
  const std::string rel{meta.path.substr(prefix.size())};
  if (rel.empty()) {
    return std::unexpected(BivError{ErrKind::MemberPathUnsafe, meta.path});
  }

  std::string current;
  size_t segment_start = 0;
  while (true) {
    const size_t slash = rel.find('/', segment_start);
    if (slash == std::string::npos) {
      break;
    }
    if (!current.empty()) {
      current.push_back('/');
    }
    current.append(rel.substr(segment_start, slash - segment_start));
    const auto found = created.find(current);
    if (found == created.end() || found->second != scan::NodeKind::dir) {
      return std::unexpected(BivError{ErrKind::MemberPathUnsafe, meta.path});
    }
    segment_start = slash + 1U;
  }

  if (created.contains(rel)) {
    return std::unexpected(BivError{ErrKind::MemberPathUnsafe, meta.path});
  }
  return temp_root / std::filesystem::path{rel};
}

expected<void> apply_member(container::TarReader& reader,
                            const container::MemberMeta& meta,
                            const std::filesystem::path& temp_root,
                            std::vector<container::MemberMeta>& dirs,
                            std::map<std::string, scan::NodeKind>& created) {
  auto out_path = contained_output_path(meta, temp_root, created);
  if (!out_path) {
    return std::unexpected(out_path.error());
  }
  const std::string rel = meta.path.substr(std::string_view{"payload/"}.size());

  std::error_code ec;
  switch (meta.kind) {
    case scan::NodeKind::dir:
      std::filesystem::create_directory(*out_path, ec);
      if (ec) {
        return std::unexpected(BivError{ErrKind::RestoreWriteFailed, out_path->generic_string(), ec.message(),
                                        static_cast<int>(ec.value())});
      }
      if (auto ok = set_mode(*out_path, meta.mode); !ok) {
        return ok;
      }
      dirs.push_back(meta);
      created.emplace(rel, meta.kind);
      return {};
    case scan::NodeKind::file:
      if (auto ok = write_file_stream(*out_path, reader, meta); !ok) {
        return ok;
      }
      if (auto ok = set_mode(*out_path, meta.mode); !ok) {
        return ok;
      }
      if (auto ok = set_mtime(*out_path, meta.mtime_s, meta.mtime_ns); !ok) {
        return ok;
      }
      created.emplace(rel, meta.kind);
      return {};
    case scan::NodeKind::symlink:
      std::filesystem::create_symlink(meta.symlink_target, *out_path, ec);
      if (ec) {
        return std::unexpected(BivError{ErrKind::RestoreWriteFailed, out_path->generic_string(), ec.message(),
                                        static_cast<int>(ec.value())});
      }
      if (auto ok = set_mtime(*out_path, meta.mtime_s, meta.mtime_ns); !ok) {
        return ok;
      }
      created.emplace(rel, meta.kind);
      return {};
  }
  return std::unexpected(BivError{ErrKind::InternalError, meta.path, "node-kind"});
}

expected<uint64_t> apply_archive(const std::filesystem::path& image,
                                 const ArchivePlan& plan,
                                 const std::filesystem::path& partial_dir,
                                 std::vector<container::MemberMeta>& dirs) {
  return with_tar_reader(image, [&](container::TarReader& reader) -> expected<uint64_t> {
    auto manifest_member = require_member(reader, "manifest.json");
    if (!manifest_member) {
      return std::unexpected(manifest_member.error());
    }
    if (auto ok = drain_member(reader); !ok) {
      return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, manifest_member->meta.path, ok.error().detail,
                                      ok.error().err_no, ok.error().facts});
    }
    auto checksums_member = require_member(reader, "checksums.json");
    if (!checksums_member) {
      return std::unexpected(checksums_member.error());
    }
    if (auto ok = drain_member(reader); !ok) {
      return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, checksums_member->meta.path, ok.error().detail,
                                      ok.error().err_no, ok.error().facts});
    }

    uint64_t restored = 0;
    size_t index = 0;
    std::map<std::string, scan::NodeKind> created;
    while (true) {
      auto next = reader.next();
      if (!next) {
        return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, image.generic_string(),
                                        next.error().detail, next.error().err_no, next.error().facts});
      }
      if (!*next) {
        break;
      }
      if (index >= plan.payload.size() || next->value().meta.path != plan.payload.at(index).meta.path ||
          next->value().meta.kind != plan.payload.at(index).meta.kind) {
        return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, next->value().meta.path, "member-mismatch"});
      }
      auto ok = apply_member(reader, next->value().meta, partial_dir, dirs, created);
      if (!ok) {
        return std::unexpected(ok.error());
      }
      ++restored;
      ++index;
    }
    if (index != plan.payload.size()) {
      return std::unexpected(BivError{ErrKind::IntegrityFailureMidApply, image.generic_string(), "member-count"});
    }
    return restored;
  });
}

expected<OpenReport> open_impl(const OpenOptions& options) {
  auto plan = read_archive_plan(options.image, options.verify);
  if (!plan) {
    return std::unexpected(preapply_error(plan.error(), options.image));
  }

  std::filesystem::path dest = options.dest.value_or(default_dest_for(options.image)).lexically_normal();
  std::string collision_action = "none";
  std::error_code ec;
  if (std::filesystem::exists(dest, ec)) {
    if (options.collision == Collision::rename) {
      dest = choose_rename_dest(dest);
      collision_action = "renamed";
      if (dest.empty()) {
        return std::unexpected(BivError{ErrKind::CollisionRefused, {}, "rename-exhausted"});
      }
    } else {
      return std::unexpected(BivError{ErrKind::CollisionRefused, dest.generic_string(),
                                      options.collision == Collision::abort_preset ? "abort-on-collision" : ""});
    }
  }

  const auto partial_dir = containing_dir(dest) / (dest.filename().generic_string() + ".bvpk-open.partial");
  if (std::filesystem::exists(partial_dir, ec)) {
    return std::unexpected(with_partial_dir(BivError{ErrKind::OpenPartialPresent, partial_dir.generic_string()},
                                           partial_dir));
  }

  std::filesystem::create_directories(partial_dir, ec);
  if (ec) {
    return std::unexpected(with_partial_dir(BivError{ErrKind::RestoreWriteFailed, partial_dir.generic_string(),
                                                    ec.message(), static_cast<int>(ec.value())},
                                           partial_dir));
  }

  std::vector<container::MemberMeta> dirs;
  auto restored = apply_archive(options.image, *plan, partial_dir, dirs);
  if (!restored) {
    return std::unexpected(with_partial_dir(restored.error(), partial_dir));
  }

  for (auto it = dirs.rbegin(); it != dirs.rend(); ++it) {
    const auto rel = it->path.substr(std::string_view{"payload/"}.size());
    if (auto ok = set_mtime(partial_dir / std::filesystem::path{rel}, it->mtime_s, it->mtime_ns); !ok) {
      return std::unexpected(with_partial_dir(ok.error(), partial_dir));
    }
  }
  if (auto ok = fsync_tree(partial_dir); !ok) {
    return std::unexpected(with_partial_dir(ok.error(), partial_dir));
  }
  if (auto ok = fsync_path(containing_dir(partial_dir), true); !ok) {
    return std::unexpected(with_partial_dir(ok.error(), partial_dir));
  }

  std::filesystem::rename(partial_dir, dest, ec);
  if (ec) {
    return std::unexpected(with_partial_dir(BivError{ec.value() == EEXIST ? ErrKind::CollisionRefused
                                                                          : ErrKind::RestoreWriteFailed,
                                                    dest.generic_string(), ec.message(), static_cast<int>(ec.value())},
                                           partial_dir));
  }
  if (auto ok = fsync_path(containing_dir(dest), true); !ok) {
    return std::unexpected(ok.error());
  }

  return OpenReport{
      .image_path = options.image.generic_string(),
      .output_dir = dest.generic_string(),
      .collision_action = collision_action,
      .restored_member_count = *restored,
      .checksums_verified = options.verify,
      .manifest_format_version = plan->manifest.format_version,
  };
}

}  // namespace

expected<OpenReport> open(const OpenOptions& options) {
  try {
    return open_impl(options);
  } catch (const std::exception& error) {
    return std::unexpected(BivError{ErrKind::InternalError, options.image.generic_string(), error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, options.image.generic_string(), "open"});
  }
}

}  // namespace biv::open
