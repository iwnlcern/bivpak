#pragma once

#include <cstddef>
#include <filesystem>
#include <optional>
#include <vector>

#include "core/ignore/matcher.hpp"
#include "core/repo/types.hpp"
#include "core/support/error.hpp"

namespace biv::repo {

struct RepoBoundary {
  std::filesystem::path relpath;
  RepoKind kind{RepoKind::repo};
  std::optional<std::size_t> parent_index;
};

struct Discovery {
  std::vector<RepoBoundary> repos;
};

expected<Discovery> discover(const std::filesystem::path& root,
                             const ignore::Matcher& matcher);

}  // namespace biv::repo
