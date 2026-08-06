#include "core/repo/discover.hpp"

#include <algorithm>
#include <string>

namespace biv::repo {
namespace {

BivError discovery_error(const std::filesystem::path& path,
                         const std::error_code& error) {
  return BivError{ErrKind::InternalError, path, "repo discovery: " + error.message(),
                  error.value()};
}

expected<void> walk(const std::filesystem::path& directory,
                    const ignore::Matcher& matcher,
                    const std::optional<std::size_t> parent,
                    Discovery& result) {
  std::error_code iterator_error;
  std::filesystem::directory_iterator iterator{directory, iterator_error};
  if (iterator_error) {
    return std::unexpected(discovery_error(directory, iterator_error));
  }
  std::vector<std::filesystem::directory_entry> children;
  for (const auto& child : iterator) {
    children.push_back(child);
  }
  std::ranges::sort(children, {}, [](const auto& child) {
    return child.path().filename().generic_string();
  });

  for (const auto& child : children) {
    std::error_code status_error;
    const auto status = child.symlink_status(status_error);
    if (status_error) {
      return std::unexpected(discovery_error(child.path(), status_error));
    }
    if (!std::filesystem::is_directory(status) ||
        std::filesystem::is_symlink(status)) {
      continue;
    }
    const auto name = child.path().filename();
    if (name == ".git" || name == ".biv") {
      continue;
    }
    const auto rel =
        std::filesystem::relative(child.path(), result.root, status_error);
    if (status_error) {
      return std::unexpected(discovery_error(child.path(), status_error));
    }
    if (matcher.match(rel.generic_string(), true).ignored) {
      continue;
    }

    auto next_parent = parent;
    const auto marker = child.path() / ".git";
    const auto marker_status = std::filesystem::symlink_status(marker, status_error);
    if (status_error && status_error != std::errc::no_such_file_or_directory) {
      return std::unexpected(discovery_error(marker, status_error));
    }
    status_error.clear();
    if (std::filesystem::is_directory(marker_status) ||
        std::filesystem::is_regular_file(marker_status)) {
      // A .git file is also the normal marker for a linked worktree. Only the
      // parent index's 160000 mode can authoritatively identify a submodule.
      const auto kind = parent ? RepoKind::nested : RepoKind::repo;
      result.repos.push_back(
          RepoBoundary{.relpath = rel, .kind = kind, .parent_index = parent});
      next_parent = result.repos.size() - 1U;
    }
    if (auto nested = walk(child.path(), matcher, next_parent, result); !nested) {
      return nested;
    }
  }
  return {};
}

}  // namespace

expected<Discovery> discover(const std::filesystem::path& root,
                             const ignore::Matcher& matcher) {
  Discovery result;
  result.root = root.lexically_normal();
  std::error_code error;
  if (!std::filesystem::is_directory(root, error) || error) {
    return std::unexpected(discovery_error(root, error));
  }
  const auto marker = root / ".git";
  const auto marker_status = std::filesystem::symlink_status(marker, error);
  if (!error && (std::filesystem::is_directory(marker_status) ||
                 std::filesystem::is_regular_file(marker_status))) {
    result.repos.push_back(RepoBoundary{.relpath = ".",
                                        .kind = RepoKind::repo,
                                        .parent_index = std::nullopt});
  }
  error.clear();
  if (auto walked = walk(root, matcher,
                         result.repos.empty()
                             ? std::optional<std::size_t>{}
                             : std::optional<std::size_t>{0U},
                         result);
      !walked) {
    return std::unexpected(walked.error());
  }
  return result;
}

}  // namespace biv::repo
