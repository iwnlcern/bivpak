#include <catch2/catch_test_macros.hpp>

#include <unistd.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

#include "core/ignore/matcher.hpp"
#include "core/repo/classify.hpp"
#include "core/repo/capture.hpp"
#include "core/repo/discover.hpp"
#include "core/repo/eligibility.hpp"
#include "core/repo/git.hpp"
#include "core/repo/restore.hpp"

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
  biv::repo::Git::Opts options;
  options.cwd = cwd;
  auto result = git.run(args, operands, options);
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

biv::repo::Discovery one_repo(
    const std::filesystem::path& root = {},
    const std::filesystem::path& relpath = ".") {
  return biv::repo::Discovery{
      .root = root,
      .repos = {biv::repo::RepoBoundary{
          .relpath = relpath,
          .kind = biv::repo::RepoKind::repo,
          .parent_index = std::nullopt}}};
}

std::filesystem::path init_bare_remote(const biv::repo::Git& git,
                                       const std::filesystem::path& root) {
  const auto remote = root / "remote.git";
  std::filesystem::create_directories(remote);
  git_run(git, remote, {"init", "--bare"});
  return remote;
}

void add_remote_and_push(const biv::repo::Git& git,
                         const std::filesystem::path& repo,
                         const std::filesystem::path& remote) {
  git_run(git, repo, {"remote", "add"}, {"origin", remote.string()});
  git_run(git, repo, {"push", "-u", "origin", "main"});
}

void stage_artifacts(const biv::repo::CaptureResult& capture,
                     const std::filesystem::path& stage_root) {
  for (const auto& artifact : capture.artifacts) {
    const auto target = stage_root / artifact.archive_path;
    std::filesystem::create_directories(target.parent_path());
    std::filesystem::copy_file(artifact.disk_path, target);
  }
}

}  // namespace

TEST_CASE("repo discovery preserves prune ordering and records nested boundaries") {
  TempDir root{"discover"};
  std::filesystem::create_directories(root.path / "ignored/repo/.git");
  std::filesystem::create_directories(root.path / ".biv/private/.git");
  std::filesystem::create_directories(root.path / "visible/.git");
  std::filesystem::create_directories(root.path / "visible/nested/.git");
  touch(root.path / "visible/linked/.git",
        "gitdir: ../../.git/worktrees/linked\n");
  auto matcher = biv::ignore::Matcher::compile("ignored/\n", false);
  REQUIRE(matcher.has_value());

  auto result = biv::repo::discover(root.path, *matcher);

  REQUIRE(result.has_value());
  REQUIRE(result->repos.size() == 3);
  CHECK(result->repos[0].relpath == "visible");
  CHECK(result->repos[0].kind == biv::repo::RepoKind::repo);
  CHECK_FALSE(result->repos[0].parent_index.has_value());
  CHECK(result->repos[1].relpath == "visible/linked");
  CHECK(result->repos[1].kind == biv::repo::RepoKind::nested);
  CHECK(result->repos[1].parent_index == 0);
  CHECK(result->repos[2].relpath == "visible/nested");
  CHECK(result->repos[2].kind == biv::repo::RepoKind::nested);
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
  git_run(git, root.path, {"remote", "add"},
          {"origin", (root.path / "remote.git").string()});

  auto any_ref = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(any_ref.has_value());
  REQUIRE(any_ref->entry.eligibility.has_value());
  CHECK(any_ref->entry.eligibility->result == biv::repo::EligibilityResult::unborn_head);
  CHECK(any_ref->entry.capture_mode == biv::repo::CaptureMode::full);
  CHECK(any_ref->fence == biv::repo::Classification::Fence::none);
  REQUIRE(any_ref->entry.remotes.size() == 1);
  CHECK(any_ref->entry.remotes[0].name == "origin");
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
  git_run(git, root.path, {"config", "user.name", "Biv Test"});
  git_run(git, root.path,
          {"config", "user.email", "biv@example.invalid"});
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
  const auto head = git_stdout(git_run(git, root.path, {"rev-parse", "HEAD"}));
  touch(root.path / ".git/shallow", head + "\n");
  git_run(git, root.path, {"config", "remote.origin.promisor", "false"});
  auto disabled = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(disabled.has_value());
  CHECK_FALSE(disabled->promisor);
  REQUIRE(disabled->entry.shallow.has_value());
  CHECK(disabled->entry.notes.empty());
  git_run(git, root.path, {"config", "remote.origin.promisor", "true"});

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

TEST_CASE("eligibility proves HEAD from one advertisement snapshot") {
  auto git = resolved_git();
  TempDir root{"eligibility-proven"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path);
  add_remote_and_push(git, repo, remote);
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result == biv::repo::EligibilityResult::proven);
  CHECK(classified->entry.capture_mode == biv::repo::CaptureMode::overlay);
  REQUIRE(classified->entry.eligibility->proof.has_value());
  CHECK(classified->entry.eligibility->proof->remote == "origin");
  CHECK(classified->entry.eligibility->proof->url == remote.string());
  REQUIRE(classified->entry.local_refs.size() == 1);
  CHECK(classified->entry.local_refs[0].availability ==
        biv::repo::RefAvailability::remote_proven);
  REQUIRE(classified->entry.local_refs[0].proof.has_value());
}

TEST_CASE("eligibility forces full capture for an unpushed HEAD") {
  auto git = resolved_git();
  TempDir root{"eligibility-unpushed"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path);
  add_remote_and_push(git, repo, remote);
  commit_file(git, repo, "unpushed\n", "unpushed");
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result ==
        biv::repo::EligibilityResult::sha_unpushed);
  CHECK(classified->entry.capture_mode == biv::repo::CaptureMode::full);
  CHECK(classified->entry.local_refs[0].availability ==
        biv::repo::RefAvailability::repo_bundle_carried);
}

TEST_CASE("eligibility distinguishes absent and unreachable remotes") {
  auto git = resolved_git();
  TempDir root{"eligibility-remote-failures"};
  const auto no_remote_repo = root.path / "none";
  init_repo(git, no_remote_repo);
  auto no_remote = biv::repo::classify(git, no_remote_repo, one_repo());
  REQUIRE(no_remote.has_value());
  REQUIRE(biv::repo::run_eligibility(git, no_remote->entry).has_value());
  REQUIRE(no_remote->entry.eligibility.has_value());
  CHECK(no_remote->entry.eligibility->result ==
        biv::repo::EligibilityResult::no_remote);
  CHECK(no_remote->entry.capture_mode == biv::repo::CaptureMode::full);

  const auto unreachable_repo = root.path / "unreachable";
  init_repo(git, unreachable_repo);
  git_run(git, unreachable_repo, {"remote", "add"},
          {"origin", (root.path / "missing.git").string()});
  auto unreachable = biv::repo::classify(git, unreachable_repo, one_repo());
  REQUIRE(unreachable.has_value());
  REQUIRE(biv::repo::run_eligibility(git, unreachable->entry).has_value());
  REQUIRE(unreachable->entry.eligibility.has_value());
  CHECK(unreachable->entry.eligibility->result ==
        biv::repo::EligibilityResult::remote_unreachable);
  CHECK(unreachable->entry.capture_mode == biv::repo::CaptureMode::full);
}

TEST_CASE("eligibility fetch-probes one advertised unknown tip") {
  auto git = resolved_git();
  TempDir root{"eligibility-fetch-probe"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path);
  add_remote_and_push(git, repo, remote);

  const auto publisher = root.path / "publisher";
  git_run(git, root.path, {"clone"}, {remote.string(), publisher.string()});
  git_run(git, publisher, {"checkout", "-b", "main", "origin/main"});
  commit_file(git, publisher, "remote descendant\n", "remote descendant");
  git_run(git, publisher, {"push", "origin", "main"});
  const auto remote_tip =
      git_stdout(git_run(git, publisher, {"rev-parse", "HEAD"}));
  REQUIRE(git_run(git, repo, {"cat-file", "-e"}, {remote_tip}, true).exit_code != 0);

  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result == biv::repo::EligibilityResult::proven);
  REQUIRE(classified->entry.eligibility->proof.has_value());
  CHECK(classified->entry.eligibility->proof->tip_sha == remote_tip);
  CHECK(git_run(git, repo, {"cat-file", "-e"}, {remote_tip}, true).exit_code == 0);
}

TEST_CASE("eligibility selects the remote whose advertisement proves HEAD") {
  auto git = resolved_git();
  TempDir root{"eligibility-select-remote"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const auto wrong = root.path / "wrong.git";
  const auto right = root.path / "right.git";
  std::filesystem::create_directories(wrong);
  std::filesystem::create_directories(right);
  git_run(git, wrong, {"init", "--bare"});
  git_run(git, right, {"init", "--bare"});
  git_run(git, repo, {"remote", "add"}, {"aaa", wrong.string()});
  git_run(git, repo, {"remote", "add"}, {"zzz", right.string()});
  git_run(git, repo, {"push", "zzz", "main"});
  auto classified = biv::repo::classify(
      git, repo, one_repo(root.path, "repo"));
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.remote == "aaa");

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  REQUIRE(classified->entry.eligibility->proof.has_value());
  CHECK(classified->entry.eligibility->proof->remote == "zzz");
  CHECK(classified->entry.remote == "zzz");
}

TEST_CASE("capture writes and verifies a full bundle plus a hostile-ref note") {
  auto git = resolved_git();
  TempDir root{"capture-full"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const std::string hostile_ref = "refs/notes/hidden-\xe2\x80\xae-cba";
  const auto head = git_stdout(git_run(git, repo, {"rev-parse", "HEAD"}));
  git_run(git, repo, {"update-ref", hostile_ref, head});
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());

  auto result = biv::repo::capture(git, classified->entry, root.path / "scratch");

  REQUIRE(result.has_value());
  REQUIRE(result->artifacts.size() == 1);
  CHECK(result->artifacts[0].archive_path ==
        std::filesystem::path{"repos/repo/repo.bundle"});
  CHECK(std::filesystem::is_regular_file(result->artifacts[0].disk_path));
  CHECK(git_run(git, repo, {"bundle", "verify"},
                {result->artifacts[0].disk_path.string()})
            .exit_code == 0);
  REQUIRE(classified->entry.bundle.has_value());
  REQUIRE(classified->entry.notes.size() == 1);
  const auto& note =
      std::get<biv::repo::NonCarriedRefsNote>(classified->entry.notes.front());
  REQUIRE(note.refs_p1.size() == 1);
  CHECK(note.refs_p1[0] == "refs/notes/hidden-\\xe2\\x80\\xae-cba");
  CHECK_FALSE(note.omitted_count.has_value());
  REQUIRE(result->advisories.size() == 1);
}

TEST_CASE("capture writes a thin local-ref bundle from advertisement bases") {
  auto git = resolved_git();
  TempDir root{"capture-thin"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path);
  add_remote_and_push(git, repo, remote);
  git_run(git, repo, {"checkout", "-b", "side"});
  commit_file(git, repo, "side-only\n", "side-only");
  git_run(git, repo, {"checkout", "main"});
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  REQUIRE(classified->entry.capture_mode == biv::repo::CaptureMode::overlay);

  auto result = biv::repo::capture(git, classified->entry, root.path / "scratch");

  REQUIRE(result.has_value());
  REQUIRE(result->artifacts.size() == 1);
  REQUIRE(classified->entry.local_refs_bundle.has_value());
  CHECK_FALSE(classified->entry.bundle.has_value());
  const auto heads = git_stdout(git_run(
      git, repo, {"bundle", "list-heads"}, {result->artifacts[0].disk_path.string()}));
  CHECK(heads.find("refs/heads/side") != std::string::npos);

  const auto stage = root.path / "stage";
  stage_artifacts(*result, stage);
  classified->entry.relpath = "restored";
  auto restored_row = biv::repo::restore_entry(
      git, classified->entry, root.path / "partial", stage);
  const std::string restore_detail =
      restored_row ? "" : restored_row.error().detail;
  INFO(restore_detail);
  REQUIRE(restored_row.has_value());
  const auto restored = root.path / "partial/restored";
  const auto side = std::ranges::find_if(classified->entry.local_refs,
                                         [](const auto& ref) {
    return ref.ref == "refs/heads/side";
  });
  REQUIRE(side != classified->entry.local_refs.end());
  CHECK(git_stdout(git_run(
            git, restored,
            {"show-ref", "--verify", "--hash=40", "refs/heads/side"})) == side->sha);
}

TEST_CASE("capture discloses stash-only unborn refs without carrying the ref name") {
  auto git = resolved_git();
  TempDir root{"capture-stash-only"};
  init_repo(git, root.path, false);
  touch(root.path / "blob", "stash object\n");
  const auto blob = git_stdout(git_run(git, root.path, {"hash-object", "-w"}, {"blob"}));
  git_run(git, root.path, {"update-ref", "refs/stash", blob});
  auto classified = biv::repo::classify(git, root.path, one_repo());
  REQUIRE(classified.has_value());
  CHECK(classified->entry.head_state == biv::repo::HeadState::unborn);
  CHECK(classified->entry.local_refs.empty());

  auto result = biv::repo::capture(git, classified->entry, root.path / "scratch");

  REQUIRE(result.has_value());
  REQUIRE(result->artifacts.size() == 1);
  CHECK(classified->entry.notes.empty());
  REQUIRE(result->advisories.size() == 1);
  CHECK(result->advisories[0].find("refs/stash") != std::string::npos);
}

TEST_CASE("capture oracle reports penumbra loss and contamination") {
  auto git = resolved_git();
  TempDir root{"capture-penumbra-oracle"};
  init_repo(git, root.path);
  touch(root.path / ".gitignore", "*.cache\n");
  git_run(git, root.path, {"add"}, {".gitignore"});
  git_run(git, root.path,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "ignore cache"});
  touch(root.path / "old.cache", "old\n");
  auto classified = biv::repo::classify(git, root.path, one_repo(root.path));
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.engine_source.has_value());
  CHECK(classified->entry.engine_source->penumbra_paths ==
        std::vector<std::filesystem::path>{"old.cache"});
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  REQUIRE(std::filesystem::remove(root.path / "old.cache"));
  touch(root.path / "new.cache", "new\n");

  auto result = biv::repo::capture(git, classified->entry, root.path / "scratch");

  REQUIRE(result.has_value());
  CHECK(std::ranges::find(result->advisories, "capture-loss: old.cache") !=
        result->advisories.end());
  CHECK(std::ranges::find(result->advisories,
                          "capture-contamination: new.cache") !=
        result->advisories.end());
}

TEST_CASE("capture failures retain ref and promisor engine kinds") {
  auto git = resolved_git();
  TempDir root{"capture-typed-errors"};
  const auto repo = root.path / "repo";
  init_repo(git, repo);

  biv::repo::RepoEntry uncapturable;
  uncapturable.id = "repo";
  uncapturable.relpath = ".";
  uncapturable.sha = "0123456789012345678901234567890123456789";
  uncapturable.head_state = biv::repo::HeadState::branch;
  uncapturable.capture_mode = biv::repo::CaptureMode::overlay;
  uncapturable.local_refs = {biv::repo::LocalRef{
      .ref = "refs/heads/not-present",
      .sha = "0123456789012345678901234567890123456789",
      .availability = biv::repo::RefAvailability::bundle_carried,
      .proof = std::nullopt}};
  uncapturable.engine_source =
      biv::repo::EngineSourceState{.repo_path = repo, .penumbra_paths = {}};
  auto ref_failure =
      biv::repo::capture(git, uncapturable, root.path / "scratch-ref");
  REQUIRE_FALSE(ref_failure.has_value());
  REQUIRE(biv::repo::engine_error_kind(ref_failure.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(ref_failure.error()) ==
        biv::repo::EngineErrorKind::ref_uncapturable);

  const auto head = git_stdout(git_run(git, repo, {"rev-parse", "HEAD"}));
  git_run(git, repo, {"config", "remote.origin.promisor", "true"});
  const auto object_path =
      repo / ".git/objects" / head.substr(0U, 2U) / head.substr(2U);
  REQUIRE(std::filesystem::is_regular_file(object_path));
  REQUIRE(std::filesystem::remove(object_path));
  biv::repo::RepoEntry promisor;
  promisor.id = "repo";
  promisor.relpath = ".";
  promisor.sha = head;
  promisor.head_state = biv::repo::HeadState::branch;
  promisor.capture_mode = biv::repo::CaptureMode::full;
  promisor.engine_source =
      biv::repo::EngineSourceState{.repo_path = repo, .penumbra_paths = {}};
  auto promisor_failure =
      biv::repo::capture(git, promisor, root.path / "scratch-promisor");
  REQUIRE_FALSE(promisor_failure.has_value());
  REQUIRE(biv::repo::engine_error_kind(promisor_failure.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(promisor_failure.error()) ==
        biv::repo::EngineErrorKind::promisor_objects_unavailable);
}

TEST_CASE("non-carried-ref writer obeys eligible bounds and sentinel semantics") {
  std::vector<std::string> maximum;
  maximum.reserve(4096);
  for (std::size_t index = 0; index < 4096; ++index) {
    maximum.push_back("refs/custom/r" + std::to_string(10000U + index));
  }
  maximum.back() = "refs/custom/" + std::string(1012, 'z');
  auto o1 = biv::repo::build_non_carried_refs_note(maximum);
  REQUIRE(o1.has_value());
  CHECK(o1->refs_p1.size() == 4096);
  CHECK_FALSE(o1->omitted_count.has_value());

  auto first_over = maximum;
  first_over.push_back("refs/custom/zzzz");
  auto o2 = biv::repo::build_non_carried_refs_note(first_over);
  REQUIRE(o2.has_value());
  CHECK(o2->refs_p1.size() == 4096);
  CHECK(o2->omitted_count == 1);

  const std::vector<std::string> overlength{
      "refs/custom/" + std::string(1013, 'x')};
  auto o3 = biv::repo::build_non_carried_refs_note(overlength);
  REQUIRE(o3.has_value());
  CHECK(o3->refs_p1.empty());
  CHECK(o3->omitted_count == 1);

  const std::vector<std::string> mixed{
      "refs/custom/z", overlength[0], "refs/custom/a"};
  auto o4 = biv::repo::build_non_carried_refs_note(mixed);
  REQUIRE(o4.has_value());
  CHECK(o4->refs_p1 ==
        std::vector<std::string>{"refs/custom/a", "refs/custom/z"});
  CHECK(o4->omitted_count == 1);

  constexpr std::uint64_t sentinel = 9007199254740991ULL;
  auto o5_at = biv::repo::build_non_carried_refs_note({}, sentinel);
  auto o5_over = biv::repo::build_non_carried_refs_note({}, sentinel + 1U);
  REQUIRE(o5_at.has_value());
  REQUIRE(o5_over.has_value());
  CHECK(o5_at->omitted_count == sentinel);
  CHECK(o5_over->omitted_count == sentinel);
}

TEST_CASE("restore dispatch leaves zero-ref and shallow payload trees untouched") {
  auto git = resolved_git();
  TempDir root{"restore-payload-branches"};
  const auto partial = root.path / "partial";
  touch(partial / "empty/payload.txt", "payload\n");
  biv::repo::RepoEntry empty;
  empty.id = "empty";
  empty.relpath = "empty";
  empty.head_state = biv::repo::HeadState::unborn;

  auto payload = biv::repo::restore_entry(git, empty, partial, root.path / "stage");

  REQUIRE(payload.has_value());
  CHECK(payload->outcome == biv::repo::RepoRestoreOutcome::payload_only_unborn);
  CHECK(std::filesystem::is_regular_file(partial / "empty/payload.txt"));
  CHECK_FALSE(std::filesystem::exists(partial / "empty/.git"));
  REQUIRE(payload->advisories.size() == 1);
  CHECK(payload->advisories[0] == "EmptyRepoPayloadOnly");

  touch(partial / "shallow/file.txt", "shallow payload\n");
  biv::repo::RepoEntry shallow;
  shallow.id = "shallow";
  shallow.relpath = "shallow";
  shallow.sha = "0123456789012345678901234567890123456789";
  shallow.head_state = biv::repo::HeadState::detached;
  shallow.shallow = biv::repo::Shallow{
      .sha = "0123456789012345678901234567890123456789",
      .boundary = {"0123456789012345678901234567890123456789"},
      .remote_urls = {"https://example.invalid/r.git"}};

  auto pointer = biv::repo::restore_entry(git, shallow, partial, root.path / "stage");

  REQUIRE(pointer.has_value());
  CHECK(pointer->outcome == biv::repo::RepoRestoreOutcome::shallow_pointer);
  REQUIRE(pointer->shallow.has_value());
  CHECK(pointer->shallow->sha == shallow.shallow->sha);
  CHECK(pointer->shallow->boundary == shallow.shallow->boundary);
  CHECK(pointer->shallow->remote_urls == shallow.shallow->remote_urls);
  CHECK_FALSE(std::filesystem::exists(partial / "shallow/.git"));
}

TEST_CASE("restore imports unborn object closure without source refs") {
  auto git = resolved_git();
  TempDir root{"restore-unborn-closure"};
  const auto source = root.path / "source";
  init_repo(git, source, false);
  touch(source / "blob", "object closure\n");
  const auto blob = git_stdout(git_run(git, source, {"hash-object", "-w"}, {"blob"}));
  git_run(git, source, {"update-ref", "refs/tags/blob-tag", blob});
  git_run(git, source, {"update-ref", "refs/stash", blob});
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  REQUIRE(classified->entry.local_refs.size() == 1);
  CHECK(classified->entry.local_refs[0].ref == "refs/tags/blob-tag");
  auto captured = biv::repo::capture(git, classified->entry, root.path / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path / "stage";
  stage_artifacts(*captured, stage);
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  CHECK_FALSE(row->sha.has_value());
  const auto restored = root.path / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"symbolic-ref", "HEAD"})) ==
        "refs/heads/main");
  const auto tag = git_run(git, restored,
                           {"show-ref", "--verify", "--hash=40", "refs/tags/blob-tag"},
                           {}, true);
  const std::string tag_error{reinterpret_cast<const char*>(tag.stderr_bytes.data()),
                              tag.stderr_bytes.size()};
  INFO(tag_error);
  REQUIRE(tag.exit_code == 0);
  CHECK(git_stdout(tag) == blob);
  CHECK(git_run(git, restored,
                {"show-ref", "--verify", "--hash=40", "refs/stash"}, {}, true)
            .exit_code != 0);
  CHECK(git_run(git, restored, {"cat-file", "-e"}, {blob}).exit_code == 0);
}

TEST_CASE("restore full mode skips exact refs, updates missing refs, and corrects HEAD") {
  auto git = resolved_git();
  TempDir root{"restore-full-refs"};
  const auto source = root.path / "source";
  init_repo(git, source);
  git_run(git, source, {"branch", "side"});
  auto classified = biv::repo::classify(
      git, source, one_repo(root.path, "source"));
  REQUIRE(classified.has_value());
  CHECK(classified->entry.relpath == "source");
  REQUIRE(classified->entry.engine_source.has_value());
  CHECK(classified->entry.engine_source->repo_path == source);
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured = biv::repo::capture(git, classified->entry, root.path / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path / "stage";
  stage_artifacts(*captured, stage);

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  REQUIRE(row->local_refs.size() == 2);
  CHECK(std::ranges::any_of(row->local_refs, [](const auto& ref) {
    return ref.skipped_at_sha;
  }));
  CHECK(std::ranges::any_of(row->local_refs, [](const auto& ref) {
    return ref.recreated && !ref.skipped_at_sha;
  }));
  const auto restored = root.path / "partial/source";
  CHECK(git_stdout(git_run(git, restored, {"symbolic-ref", "--short", "HEAD"})) ==
        "main");
  for (const auto& ref : classified->entry.local_refs) {
    CHECK(git_stdout(git_run(
              git, restored, {"show-ref", "--verify", "--hash=40", ref.ref})) == ref.sha);
  }
}

TEST_CASE("restore overlay is total with zero captured artifacts") {
  auto git = resolved_git();
  TempDir root{"restore-overlay-zero-artifact"};
  const auto source = root.path / "source";
  init_repo(git, source);
  const auto remote = init_bare_remote(git, root.path);
  add_remote_and_push(git, source, remote);
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured = biv::repo::capture(git, classified->entry, root.path / "scratch");
  REQUIRE(captured.has_value());
  CHECK(captured->artifacts.empty());
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path / "partial", root.path / "stage");

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  const auto restored = root.path / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"rev-parse", "HEAD"})) ==
        *classified->entry.sha);
  CHECK(git_stdout(git_run(git, restored, {"symbolic-ref", "--short", "HEAD"})) ==
        "main");
}

TEST_CASE("restore preserves a detached HEAD") {
  auto git = resolved_git();
  TempDir root{"restore-detached"};
  const auto source = root.path / "source";
  init_repo(git, source);
  git_run(git, source, {"checkout", "--detach", "HEAD"});
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  CHECK(classified->entry.head_state == biv::repo::HeadState::detached);
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured = biv::repo::capture(git, classified->entry, root.path / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path / "stage";
  stage_artifacts(*captured, stage);
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  const auto restored = root.path / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"rev-parse", "HEAD"})) ==
        *classified->entry.sha);
  CHECK(git_run(git, restored, {"symbolic-ref", "HEAD"}, {}, true).exit_code != 0);
}

TEST_CASE("restore materializes a root repo beside the live stage directory") {
  auto git = resolved_git();
  TempDir root{"restore-root-repo"};
  const auto source = root.path / "source";
  init_repo(git, source);
  auto classified = biv::repo::classify(git, source, one_repo(source));
  REQUIRE(classified.has_value());
  CHECK(classified->entry.relpath == ".");
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured = biv::repo::capture(git, classified->entry, root.path / "scratch");
  REQUIRE(captured.has_value());

  const auto partial = root.path / "partial";
  const auto stage = partial / ".biv-stage";
  touch(stage / "keep", "stage remains live\n");
  stage_artifacts(*captured, stage);

  auto row = biv::repo::restore_entry(git, classified->entry, partial, stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  CHECK(std::filesystem::is_directory(partial / ".git"));
  CHECK(std::filesystem::is_regular_file(stage / "keep"));
  CHECK(git_stdout(git_run(git, partial, {"rev-parse", "HEAD"})) ==
        *classified->entry.sha);
}

TEST_CASE("restore failures retain the typed engine mapping seam") {
  auto git = resolved_git();
  TempDir root{"restore-typed-error"};
  biv::repo::RepoEntry entry;
  entry.id = "repo";
  entry.relpath = "repo";
  entry.sha = "0123456789012345678901234567890123456789";
  entry.head_state = biv::repo::HeadState::detached;
  entry.capture_mode = biv::repo::CaptureMode::full;
  entry.bundle = std::filesystem::path{"repos/repo/missing.bundle"};

  auto result = biv::repo::restore_entry(git, entry, root.path / "partial",
                                         root.path / "stage");

  REQUIRE_FALSE(result.has_value());
  REQUIRE(biv::repo::engine_error_kind(result.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::repo_restore_failed);
}
