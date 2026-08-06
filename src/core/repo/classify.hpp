#pragma once

#include <optional>

#include "core/repo/discover.hpp"
#include "core/repo/git.hpp"
#include "core/repo/types.hpp"

namespace biv::repo {

struct Classification {
  enum class Fence { none, dirty, nested, submodule, unmerged };

  RepoEntry entry;
  bool promisor{false};
  Fence fence{Fence::none};
  std::optional<EngineIssue> issue;
};

expected<Classification> classify(const Git& git,
                                  const std::filesystem::path& repo,
                                  const Discovery& discovery);

}  // namespace biv::repo
