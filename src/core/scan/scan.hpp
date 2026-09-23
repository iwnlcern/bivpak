#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include "core/ignore/matcher.hpp"
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

struct ScanExclusions {
  std::vector<std::string> repo_subtrees;
  std::vector<std::string> claimed_markers;

  static std::string canonical(const std::filesystem::path& rel);
  bool claims_root() const;
  bool claims(std::string_view canonical_rel) const;
  bool claims_marker(std::string_view canonical_rel) const;
};

struct MatcherBundle {
  ignore::Matcher matcher;
  manifest::BivignoreProvenance bivignore;
};

expected<MatcherBundle> prepare_matcher(const std::filesystem::path& source_root);
expected<ScanResult> scan(const std::filesystem::path& source_root,
                          const ignore::Matcher& matcher,
                          const ScanExclusions& exclusions);
expected<void> scan_subtree(const std::filesystem::path& source_root,
                            const ignore::Matcher& matcher,
                            const ScanExclusions& exclusions,
                            std::string_view subtree_rel,
                            ScanResult& into);
expected<ScanResult> scan(const std::filesystem::path& source_root);

}  // namespace biv::scan
