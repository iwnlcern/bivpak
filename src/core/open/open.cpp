#include "core/open/open.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <span>
#include <string_view>
#include <system_error>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "core/container/tar_reader.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"

namespace biv::open {

namespace {

struct ArchiveMember {
  container::MemberMeta meta;
  std::vector<std::byte> data;
  std::string extent;
};

std::vector<std::byte> to_bytes(const std::string& text) {
  std::vector<std::byte> out(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    out[i] = static_cast<std::byte>(text[i]);
  }
  return out;
}

expected<std::vector<std::byte>> read_file_bytes(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  if (!in) {
    return std::unexpected(BivError{ErrKind::ImageUnreadable, path.generic_string()});
  }
  std::string text{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
  if (in.bad()) {
    return std::unexpected(BivError{ErrKind::ImageUnreadable, path.generic_string()});
  }
  return to_bytes(text);
}

bool has_zstd_magic(std::span<const std::byte> bytes) {
  if (bytes.size() < container::kZstdMagic.size()) {
    return false;
  }
  for (size_t i = 0; i < container::kZstdMagic.size(); ++i) {
    if (bytes[i] != static_cast<std::byte>(container::kZstdMagic[i])) {
      return false;
    }
  }
  return true;
}

BivError preapply_error(BivError error, const std::filesystem::path& image) {
  if (error.kind == ErrKind::NotABivpakImage || error.kind == ErrKind::ImageUnreadable) {
    return error;
  }
  if (error.kind == ErrKind::MemberPathUnsafe || error.kind == ErrKind::UnmanifestedMember ||
      error.kind == ErrKind::FormatVersionUnsupported || error.kind == ErrKind::UnknownRequiredCapability) {
    return error;
  }
  return BivError{ErrKind::IntegrityFailurePreApply, image.generic_string(), error.detail, error.err_no, error.facts};
}

expected<std::vector<ArchiveMember>> read_archive(const std::filesystem::path& image) {
  auto compressed = read_file_bytes(image);
  if (!compressed) {
    return std::unexpected(compressed.error());
  }
  if (!has_zstd_magic(*compressed)) {
    return std::unexpected(BivError{ErrKind::NotABivpakImage, image.generic_string()});
  }

  bool served = false;
  container::ZstdDecompressSource source{[&]() -> expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{*compressed};
  }};
  container::TarReader reader{source};

  std::vector<ArchiveMember> members;
  while (true) {
    auto next = reader.next();
    if (!next) {
      return std::unexpected(next.error());
    }
    if (!*next) {
      break;
    }
    ArchiveMember member{.meta = next->value().meta, .data = {}, .extent = {}};
    std::array<std::byte, 8192> buffer {};
    while (true) {
      auto n = reader.read_data(buffer);
      if (!n) {
        return std::unexpected(n.error());
      }
      if (*n == 0U) {
        break;
      }
      member.data.insert(member.data.end(), buffer.begin(), buffer.begin() + static_cast<std::ptrdiff_t>(*n));
    }
    member.extent = reader.extent_sha256_hex();
    members.push_back(std::move(member));
  }
  return members;
}

std::span<const std::byte> byte_span(const std::vector<std::byte>& bytes) {
  return std::span<const std::byte>{bytes.data(), bytes.size()};
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

bool parent_is_real_dir(const std::filesystem::path& path, const std::filesystem::path& temp_root) {
  auto parent = path.parent_path();
  if (parent.empty()) {
    parent = temp_root;
  }
  std::error_code ec;
  const auto status = std::filesystem::symlink_status(parent, ec);
  return !ec && std::filesystem::is_directory(status) && !std::filesystem::is_symlink(status);
}

expected<void> write_file(const std::filesystem::path& path, std::span<const std::byte> bytes) {
  std::ofstream out{path, std::ios::binary};
  if (!out) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string()});
  }
  for (const auto byte : bytes) {
    out.put(static_cast<char>(byte));
    if (!out) {
      return std::unexpected(BivError{ErrKind::RestoreWriteFailed, path.generic_string()});
    }
  }
  return {};
}

expected<void> apply_member(const ArchiveMember& member,
                            const std::filesystem::path& temp_root,
                            std::vector<container::MemberMeta>& dirs) {
  constexpr std::string_view prefix = "payload/";
  if (!member.meta.path.starts_with(prefix)) {
    return std::unexpected(BivError{ErrKind::UnmanifestedMember, member.meta.path});
  }
  const auto rel = member.meta.path.substr(prefix.size());
  const auto out_path = temp_root / std::filesystem::path{rel};
  if (!parent_is_real_dir(out_path, temp_root)) {
    return std::unexpected(BivError{ErrKind::MemberPathUnsafe, member.meta.path});
  }

  std::error_code ec;
  switch (member.meta.kind) {
    case scan::NodeKind::dir:
      std::filesystem::create_directory(out_path, ec);
      if (ec) {
        return std::unexpected(BivError{ErrKind::RestoreWriteFailed, out_path.generic_string(), ec.message(),
                                        static_cast<int>(ec.value())});
      }
      if (auto ok = set_mode(out_path, member.meta.mode); !ok) {
        return ok;
      }
      dirs.push_back(member.meta);
      return {};
    case scan::NodeKind::file:
      if (auto ok = write_file(out_path, byte_span(member.data)); !ok) {
        return ok;
      }
      if (auto ok = set_mode(out_path, member.meta.mode); !ok) {
        return ok;
      }
      return set_mtime(out_path, member.meta.mtime_s, member.meta.mtime_ns);
    case scan::NodeKind::symlink:
      std::filesystem::create_symlink(member.meta.symlink_target, out_path, ec);
      if (ec) {
        return std::unexpected(BivError{ErrKind::RestoreWriteFailed, out_path.generic_string(), ec.message(),
                                        static_cast<int>(ec.value())});
      }
      return set_mtime(out_path, member.meta.mtime_s, member.meta.mtime_ns);
  }
  return std::unexpected(BivError{ErrKind::InternalError, member.meta.path, "node-kind"});
}

expected<OpenReport> open_impl(const OpenOptions& options) {
  auto members = read_archive(options.image);
  if (!members) {
    return std::unexpected(preapply_error(members.error(), options.image));
  }
  if (members->size() < 2U || (*members)[0].meta.path != "manifest.json" ||
      (*members)[1].meta.path != "checksums.json") {
    return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, options.image.generic_string(), "member-order"});
  }

  auto manifest_model = manifest::parse(byte_span((*members)[0].data));
  if (!manifest_model) {
    return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, options.image.generic_string(),
                                    manifest_model.error().detail});
  }
  if (manifest_model->format_version != manifest::kFormatVersion) {
    return std::unexpected(BivError{ErrKind::FormatVersionUnsupported, options.image.generic_string()});
  }
  if (!manifest_model->required_capabilities.empty()) {
    return std::unexpected(BivError{ErrKind::UnknownRequiredCapability, options.image.generic_string(),
                                    manifest_model->required_capabilities.front()});
  }

  auto checksums = manifest::parse_checksums(byte_span((*members)[1].data));
  if (!checksums) {
    return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, options.image.generic_string(),
                                    checksums.error().detail});
  }

  std::set<std::string> seen;
  for (size_t i = 2; i < members->size(); ++i) {
    const auto& member = (*members)[i];
    if (!member.meta.path.starts_with("payload/") || !checksums->entries.contains(member.meta.path)) {
      return std::unexpected(BivError{ErrKind::UnmanifestedMember, member.meta.path});
    }
    seen.insert(member.meta.path);
    if (options.verify && checksums->entries.at(member.meta.path) != member.extent) {
      return std::unexpected(BivError{ErrKind::IntegrityFailurePreApply, member.meta.path, "checksum"});
    }
  }
  for (const auto& [path, digest] : checksums->entries) {
    (void)digest;
    if (!seen.contains(path)) {
      return std::unexpected(BivError{ErrKind::UnmanifestedMember, path});
    }
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

  const auto partial_dir =
      dest.parent_path() / (dest.filename().generic_string() + ".bvpk-open.partial");
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
  uint64_t restored = 0;
  for (size_t i = 2; i < members->size(); ++i) {
    auto ok = apply_member((*members)[i], partial_dir, dirs);
    if (!ok) {
      return std::unexpected(with_partial_dir(ok.error(), partial_dir));
    }
    ++restored;
  }
  for (auto it = dirs.rbegin(); it != dirs.rend(); ++it) {
    const auto rel = it->path.substr(std::string_view{"payload/"}.size());
    if (auto ok = set_mtime(partial_dir / std::filesystem::path{rel}, it->mtime_s, it->mtime_ns); !ok) {
      return std::unexpected(with_partial_dir(ok.error(), partial_dir));
    }
  }

  std::filesystem::rename(partial_dir, dest, ec);
  if (ec) {
    return std::unexpected(with_partial_dir(BivError{ErrKind::CollisionRefused, dest.generic_string(), ec.message(),
                                                    static_cast<int>(ec.value())},
                                           partial_dir));
  }

  return OpenReport{
      .image_path = options.image.generic_string(),
      .output_dir = dest.generic_string(),
      .collision_action = collision_action,
      .restored_member_count = restored,
      .checksums_verified = options.verify,
      .manifest_format_version = manifest_model->format_version,
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
