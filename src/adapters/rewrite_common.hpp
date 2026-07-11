#pragma once

#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "adapters/adapter.hpp"

namespace biv::adapters::rewrite {

using ReplacementPairs = std::vector<std::pair<std::string, std::string>>;

struct RewriteLineResult {
  std::string line;
  bool skipped_non_utf8{false};
};

struct RewriteBytesResult {
  std::vector<std::byte> bytes;
  size_t skipped_non_utf8{0};
};

struct PathPairsView {
  std::span<const std::pair<std::string, std::string>> values;
};

struct IdPairsView {
  std::span<const std::pair<std::string, std::string>> values;
};

struct OriginPathsView {
  std::span<const std::string> values;
};

struct OriginIdsView {
  std::span<const std::string> values;
};

struct PathMembership {
  std::string_view candidate;
  std::string_view root;
};

ReplacementPairs derive_pair_set(std::string_view original_path,
                                  manifest::PathFlavor original_flavor,
                                  std::string_view target_path,
                                  manifest::PathFlavor target_flavor);

manifest::PathFlavor path_flavor_for(std::string_view path);
std::string normalized_path_key(std::string_view path);
bool path_is_same_or_descendant(PathMembership membership);

RewriteLineResult rewrite_jsonl_line(std::string_view line,
                                     PathPairsView pair_set,
                                     IdPairsView id_map);
RewriteBytesResult rewrite_jsonl_bytes(std::span<const std::byte> bytes,
                                       PathPairsView pair_set,
                                       IdPairsView id_map);

InstallVerify verify_scan(std::span<const std::byte> artifact_bytes,
                          OriginPathsView pair_set_origins,
                          OriginIdsView origin_ids);

std::vector<std::string> origins_from_pairs(std::span<const std::pair<std::string, std::string>> pair_set);

}  // namespace biv::adapters::rewrite
