#include "core/scan/scan.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <fstream>
#include <string_view>
#include <system_error>

#include <sys/stat.h>
#include <unistd.h>

#include "core/ignore/builtin.hpp"
#include "core/ignore/matcher.hpp"
#include "core/support/portability.hpp"
#include "core/support/sha256.hpp"

namespace biv::scan {

namespace {

expected<std::string> read_file(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  if (!in) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string()});
  }
  std::string bytes{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
  if (!in.eof() && in.bad()) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string()});
  }
  return bytes;
}

bool is_directory_status(const std::filesystem::file_status status) {
  return status.type() == std::filesystem::file_type::directory;
}

bool is_supported_status(const std::filesystem::file_status status) {
  return status.type() == std::filesystem::file_type::regular ||
         status.type() == std::filesystem::file_type::directory ||
         status.type() == std::filesystem::file_type::symlink;
}

NodeKind kind_from_status(const std::filesystem::file_status status) {
  if (status.type() == std::filesystem::file_type::directory) {
    return NodeKind::dir;
  }
  if (status.type() == std::filesystem::file_type::symlink) {
    return NodeKind::symlink;
  }
  return NodeKind::file;
}

expected<struct stat> stat_path(const std::filesystem::path& path) {
  struct stat statbuf {};
  if (::lstat(path.c_str(), &statbuf) != 0) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string(), {}, errno});
  }
  return statbuf;
}

expected<std::string> symlink_target(const std::filesystem::path& path) {
  std::array<char, 4096> buffer {};
  const ssize_t size = ::readlink(path.c_str(), buffer.data(), buffer.size());
  if (size < 0) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string(), {}, errno});
  }
  if (static_cast<size_t>(size) == buffer.size()) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string(), "symlink-target-too-long"});
  }
  return std::string{buffer.data(), static_cast<size_t>(size)};
}

std::string child_relpath(std::string_view parent, std::string_view name) {
  if (parent.empty()) {
    return std::string{name};
  }
  std::string out;
  out.reserve(parent.size() + 1U + name.size());
  out.append(parent);
  out.push_back('/');
  out.append(name);
  return out;
}

expected<std::vector<std::filesystem::directory_entry>> sorted_children(const std::filesystem::path& path) {
  std::error_code ec;
  std::filesystem::directory_iterator iterator{path, std::filesystem::directory_options::none, ec};
  if (ec) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, path.generic_string(), ec.message(),
                                    static_cast<int>(ec.value())});
  }

  std::vector<std::filesystem::directory_entry> entries;
  for (const auto& entry : iterator) {
    entries.push_back(entry);
  }
  std::ranges::sort(entries, {}, [](const std::filesystem::directory_entry& entry) {
    return entry.path().filename().generic_string();
  });
  return entries;
}

expected<void> walk(const std::filesystem::path& dir,
                    std::string_view rel_dir,
                    const ignore::Matcher& matcher,
                    ScanResult& result) {
  auto children = sorted_children(dir);
  if (!children) {
    if (!rel_dir.empty()) {
      result.unreadable.emplace_back(rel_dir);
      return {};
    }
    return std::unexpected(children.error());
  }

  for (const auto& child : *children) {
    std::error_code ec;
    const auto status = child.symlink_status(ec);
    if (ec) {
      return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, child.path().generic_string(), ec.message(),
                                      static_cast<int>(ec.value())});
    }

    const std::string name = child.path().filename().generic_string();
    const std::string relpath = child_relpath(rel_dir, name);
    const bool is_dir = is_directory_status(status);

    if (relpath != ".bivignore") {
      const auto verdict = matcher.match(relpath, is_dir);
      if (verdict.ignored) {
        result.pruned.push_back(PruneEntry{.relpath = relpath, .source = verdict.source});
        continue;
      }
    }

    if (name == ".git") {
      return std::unexpected(BivError{ErrKind::RepoDiscoveredUnsupported, child.path().generic_string()});
    }
    if (name == ".biv" && is_dir) {
      continue;
    }

    if (!is_supported_status(status)) {
      result.skipped_unsupported.push_back(relpath);
      continue;
    }

    auto statbuf = stat_path(child.path());
    if (!statbuf) {
      return std::unexpected(statbuf.error());
    }

    Node entry;
    entry.relpath = relpath;
    entry.kind = kind_from_status(status);
    entry.size = entry.kind == NodeKind::file ? static_cast<uint64_t>(statbuf->st_size) : 0U;
    entry.mode = static_cast<uint32_t>(statbuf->st_mode);
    entry.mtime_s = support::stat_mtime_sec(*statbuf);
    entry.mtime_ns = support::stat_mtime_nsec(*statbuf);
    if (entry.kind == NodeKind::symlink) {
      auto target = symlink_target(child.path());
      if (!target) {
        return std::unexpected(target.error());
      }
      entry.symlink_target = std::move(*target);
    }
    result.payload.push_back(std::move(entry));

    if (relpath != ".bivignore" && name == ".bivignore") {
      result.nested_bivignore.push_back(relpath);
    }

    if (is_dir) {
      auto recurse = walk(child.path(), relpath, matcher, result);
      if (!recurse) {
        return std::unexpected(recurse.error());
      }
    }
  }
  return {};
}

}  // namespace

expected<ScanResult> scan(const std::filesystem::path& source_root) {
  std::error_code ec;
  const auto root_status = std::filesystem::symlink_status(source_root, ec);
  if (ec || !is_directory_status(root_status)) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot, source_root.generic_string(),
                                    ec ? ec.message() : "not-directory", static_cast<int>(ec.value())});
  }

  ScanResult result;
  ignore::Matcher matcher;
  const auto bivignore_path = source_root / ".bivignore";
  const auto bivignore_status = std::filesystem::symlink_status(bivignore_path, ec);
  if (!ec && bivignore_status.type() == std::filesystem::file_type::regular) {
    auto bytes = read_file(bivignore_path);
    if (!bytes) {
      return std::unexpected(bytes.error());
    }
    auto compiled = ignore::Matcher::compile(*bytes, false);
    if (!compiled) {
      return std::unexpected(compiled.error());
    }
    matcher = std::move(*compiled);
    support::Sha256 sha;
    sha.update(std::as_bytes(std::span<const char>{bytes->data(), bytes->size()}));
    result.bivignore = manifest::BivignoreProvenance{
        .source = "file",
        .builtin_id = std::nullopt,
        .sha256_hex = sha.finish_hex(),
    };
  } else {
    auto compiled = ignore::Matcher::compile(ignore::kBuiltinV1, true);
    if (!compiled) {
      return std::unexpected(compiled.error());
    }
    matcher = std::move(*compiled);
    result.bivignore = manifest::BivignoreProvenance{
        .source = "builtin",
        .builtin_id = std::string{"builtin-v1"},
        .sha256_hex = std::string{ignore::kBuiltinV1Sha256},
    };
  }

  auto walked = walk(source_root, {}, matcher, result);
  if (!walked) {
    return std::unexpected(walked.error());
  }
  return result;
}

}  // namespace biv::scan
