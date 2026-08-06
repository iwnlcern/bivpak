#include <catch2/catch_test_macros.hpp>

#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

#include "core/ignore/matcher.hpp"
#include "core/repo/classify.hpp"
#include "core/repo/discover.hpp"
#include "core/repo/git.hpp"

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

biv::repo::Git resolved_git() {
  auto git = biv::repo::Git::resolve([](const std::string_view name)
                                        -> std::optional<std::string> {
    if (const char* value = std::getenv(std::string{name}.c_str())) {
      return std::string{value};
    }
    return std::nullopt;
  });
  if (!git) {
    throw std::runtime_error{"git unavailable"};
  }
  return *git;
}

biv::support::SpawnResult git_run(
    const biv::repo::Git& git, const std::filesystem::path& cwd,
    const std::vector<std::string>& args,
    const std::vector<std::string>& operands = {}, const bool allow_nonzero = false) {
  auto result = git.run(args, operands, biv::repo::Git::Opts{.cwd = cwd});
  if (!result || (!allow_nonzero && result->exit_code != 0)) {
    throw std::runtime_error{"git fixture command failed"};
  }
  return *result;
}

void init_repo(const biv::repo::Git& git, const std::filesystem::path& repo,
               const bool commit = true) {
  std::filesystem::create_directories(repo);
  git_run(git, repo, {"init"});
  git_run(git, repo, {"symbolic-ref", "HEAD", "refs/heads/main"});
  if (!commit) {
    return;
  }
  touch(repo / "a.txt", "one\n");
  git_run(git, repo, {"add"}, {"a.txt"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "initial"});
}

std::string git_stdout(const biv::support::SpawnResult& result) {
  auto value = std::string{reinterpret_cast<const char*>(result.stdout_bytes.data()),
                           result.stdout_bytes.size()};
  while (!value.empty() && (value.back() == '\n' || value.back() == '\r')) {
    value.pop_back();
  }
  return value;
}

void commit_file(const biv::repo::Git& git, const std::filesystem::path& repo,
                 const std::string& text, const std::string& message) {
  touch(repo / "a.txt", text);
  git_run(git, repo, {"add"}, {"a.txt"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", message});
}

biv::repo::Discovery one_repo() {
  return biv::repo::Discovery{.repos = {biv::repo::RepoBoundary{
                                   .relpath = ".", .kind = biv::repo::RepoKind::repo}}};
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

TEST_CASE("classification orders zero-ref and any-ref unborn before dirt") {
  auto git = resolved_git();
  TempDir root{"classify-unborn"};
  init_repo(git, root.path, false);
  touch(root.path / "payload.txt", "payload\n");

  auto zero = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(zero.has_value());
  CHECK(zero->entry.head_state == biv::repo::HeadState::unborn);
  CHECK_FALSE(zero->entry.eligibility.has_value());
  CHECK(zero->fence == biv::repo::Classification::Fence::none);

  git_run(git, root.path, {"hash-object", "-w"}, {"payload.txt"});
  const auto blob = git_run(git, root.path, {"hash-object"}, {"payload.txt"});
  const std::string sha{reinterpret_cast<const char*>(blob.stdout_bytes.data()),
                        blob.stdout_bytes.size() - 1U};
  git_run(git, root.path, {"update-ref", "refs/tags/blob-only", sha});

  auto any_ref = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(any_ref.has_value());
  REQUIRE(any_ref->entry.eligibility.has_value());
  CHECK(any_ref->entry.eligibility->result == biv::repo::EligibilityResult::unborn_head);
  CHECK(any_ref->entry.capture_mode == biv::repo::CaptureMode::full);
  CHECK(any_ref->fence == biv::repo::Classification::Fence::none);
}

TEST_CASE("classification fences discovery shape, dirt, and unmerged paths") {
  auto git = resolved_git();
  TempDir root{"classify-fences"};
  init_repo(git, root.path);

  auto nested_discovery = one_repo();
  nested_discovery.repos.push_back(biv::repo::RepoBoundary{
      .relpath = "nested", .kind = biv::repo::RepoKind::nested, .parent_index = 0});
  auto nested = biv::repo::classify(git, root.path, nested_discovery);
  REQUIRE(nested.has_value());
  CHECK(nested->fence == biv::repo::Classification::Fence::nested);

  touch(root.path / "dirty.txt", "dirty\n");
  auto dirty = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(dirty.has_value());
  CHECK(dirty->fence == biv::repo::Classification::Fence::dirty);
}

TEST_CASE("classification detects gitlinks from the parent index") {
  auto git = resolved_git();
  TempDir root{"classify-gitlink"};
  init_repo(git, root.path);
  const auto head = git_stdout(git_run(git, root.path, {"rev-parse", "HEAD"}));
  git_run(git, root.path,
          {"update-index", "--add", "--cacheinfo", "160000," + head + ",module"});

  auto result = biv::repo::classify(git, root.path, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::submodule);
  REQUIRE(result->issue.has_value());
  CHECK(result->issue->kind == biv::repo::EngineErrorKind::repo_submodule_unsupported);
  REQUIRE(result->issue->paths.size() == 1);
  CHECK(result->issue->paths[0] == "module");
}

TEST_CASE("classification reports each unmerged path before the dirt gate") {
  auto git = resolved_git();
  TempDir root{"classify-unmerged"};
  init_repo(git, root.path);
  git_run(git, root.path, {"checkout", "-b", "side"});
  commit_file(git, root.path, "side\n", "side");
  git_run(git, root.path, {"checkout", "main"});
  commit_file(git, root.path, "main\n", "main");
  const auto merge = git_run(git, root.path, {"merge", "side"}, {}, true);
  REQUIRE(merge.exit_code != 0);

  auto result = biv::repo::classify(git, root.path, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::unmerged);
  REQUIRE(result->issue.has_value());
  CHECK(result->issue->kind ==
        biv::repo::EngineErrorKind::unmerged_index_unrepresentable);
  REQUIRE(result->issue->paths.size() == 1);
  CHECK(result->issue->paths[0] == "a.txt");
}

TEST_CASE("classification records head, branch, refs, remotes, and promisor policy") {
  auto git = resolved_git();
  TempDir root{"classify-clean"};
  init_repo(git, root.path);
  git_run(git, root.path, {"remote", "add"}, {"origin", "https://example.invalid/r.git"});
  git_run(git, root.path, {"config", "remote.origin.promisor", "true"});
  git_run(git, root.path, {"tag", "v1"});

  auto result = biv::repo::classify(git, root.path, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  CHECK(result->promisor);
  CHECK(result->entry.head_state == biv::repo::HeadState::branch);
  CHECK(result->entry.branch == "main");
  REQUIRE(result->entry.sha.has_value());
  CHECK(result->entry.local_refs.size() == 2);
  REQUIRE(result->entry.remotes.size() == 1);
  CHECK(result->entry.remotes[0].name == "origin");
}

TEST_CASE("classification records shallow promisor source without a bundle") {
  auto git = resolved_git();
  TempDir root{"classify-shallow-promisor"};
  init_repo(git, root.path);
  git_run(git, root.path, {"remote", "add"},
          {"origin", "https://example.invalid/r.git"});
  git_run(git, root.path, {"config", "remote.origin.promisor", "true"});
  const auto head = git_stdout(git_run(git, root.path, {"rev-parse", "HEAD"}));
  touch(root.path / ".git/shallow", head + "\n");

  auto result = biv::repo::classify(git, root.path, one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK(result->entry.shallow->sha == head);
  CHECK(result->entry.shallow->boundary == std::vector<std::string>{head});
  CHECK_FALSE(result->entry.bundle.has_value());
  REQUIRE(result->entry.notes.size() == 1);
  CHECK(std::holds_alternative<biv::repo::PromisorSourceNote>(
      result->entry.notes.front()));
}
