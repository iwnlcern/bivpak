#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "core/manifest/manifest.hpp"
#include "core/support/error.hpp"

namespace biv::scan {

enum class Kind { file, dir, symlink };

struct Entry {
  std::string relpath;
  Kind kind{Kind::file};
  uintmax_t size{0};
  uint32_t mode{0};
  int64_t mtime_ns{0};
  std::string link_target;
};

struct PruneEntry {
  std::string relpath;
  std::string source;
};

struct ScanResult {
  std::vector<Entry> payload;
  manifest::BivignoreProvenance bivignore;
  std::vector<PruneEntry> pruned;
  std::vector<std::string> nested_bivignores;
};

expected<ScanResult> scan(const std::filesystem::path& source_root);

}  // namespace biv::scan
