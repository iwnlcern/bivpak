#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "core/manifest/manifest.hpp"
#include "core/support/error.hpp"

namespace biv::scan {

enum class NodeKind { file, dir, symlink };

struct Node {
  std::string relpath;
  NodeKind kind{NodeKind::file};
  uint32_t mode{0};
  int64_t mtime_s{0};
  uint32_t mtime_ns{0};
  uint64_t size{0};
  std::string symlink_target;
};

struct PruneEntry {
  std::string relpath;
  std::string source;
};

struct ScanResult {
  std::vector<Node> payload;
  std::vector<PruneEntry> pruned;
  std::vector<std::string> skipped_unsupported;
  std::vector<std::string> nested_bivignore;
  std::vector<std::string> unreadable;
  manifest::BivignoreProvenance bivignore;
};

expected<ScanResult> scan(const std::filesystem::path& source_root);

}  // namespace biv::scan
