#include <catch2/catch_test_macros.hpp>

#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "core/ignore/matcher.hpp"
#include "core/repo/discover.hpp"

namespace {

struct TempDir {
  std::filesystem::path path;
  explicit TempDir(const std::string& name)
      : path{std::filesystem::temp_directory_path() /
             ("biv-repo-engine-" + name + "-" + std::to_string(::getpid()))} {
    std::filesystem::remove_all(path);
    std::filesystem::create_directories(path);
  }
  ~TempDir() { std::filesystem::remove_all(path); }
};

void touch(const std::filesystem::path& path, const std::string& text = {}) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream{path} << text;
}

}  // namespace

TEST_CASE("repo discovery preserves prune ordering and records nested boundaries") {
  TempDir root{"discover"};
  std::filesystem::create_directories(root.path / "ignored/repo/.git");
  std::filesystem::create_directories(root.path / ".biv/private/.git");
  std::filesystem::create_directories(root.path / "visible/.git");
  std::filesystem::create_directories(root.path / "visible/nested/.git");
  touch(root.path / "visible/submodule/.git", "gitdir: ../.git/modules/submodule\n");
  auto matcher = biv::ignore::Matcher::compile("ignored/\n", false);
  REQUIRE(matcher.has_value());

  auto result = biv::repo::discover(root.path, *matcher);

  REQUIRE(result.has_value());
  REQUIRE(result->repos.size() == 3);
  CHECK(result->repos[0].relpath == "visible");
  CHECK(result->repos[0].kind == biv::repo::RepoKind::repo);
  CHECK_FALSE(result->repos[0].parent_index.has_value());
  CHECK(result->repos[1].relpath == "visible/nested");
  CHECK(result->repos[1].kind == biv::repo::RepoKind::nested);
  CHECK(result->repos[1].parent_index == 0);
  CHECK(result->repos[2].relpath == "visible/submodule");
  CHECK(result->repos[2].kind == biv::repo::RepoKind::submodule);
  CHECK(result->repos[2].parent_index == 0);
}
