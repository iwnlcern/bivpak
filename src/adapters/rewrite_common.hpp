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

ReplacementPairs derive_pair_set(std::string_view original_path,
                                  manifest::PathFlavor original_flavor,
                                  std::string_view target_path,
                                  manifest::PathFlavor target_flavor);

RewriteLineResult rewrite_jsonl_line(std::string_view line, PathPairsView pair_set, IdPairsView id_map);

InstallVerify verify_scan(std::span<const std::byte> artifact_bytes,
                          OriginPathsView pair_set_origins,
                          OriginIdsView origin_ids);

std::vector<std::string> origins_from_pairs(std::span<const std::pair<std::string, std::string>> pair_set);

}  // namespace biv::adapters::rewrite
