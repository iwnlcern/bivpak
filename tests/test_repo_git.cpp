#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/repo/git.hpp"
#include "core/repo/types.hpp"
#include "support/temp_dir.hpp"

namespace {

namespace fs = std::filesystem;
using biv::test_support::TempDir;

std::string as_string(const std::vector<std::byte>& bytes) {
  std::string output;
  output.reserve(bytes.size());
  for (const auto byte : bytes) {
    output.push_back(static_cast<char>(byte));
  }
  return output;
}

biv::support::Getenv getenv_with_home(const fs::path& home) {
  return [home](const std::string_view name) -> std::optional<std::string> {
    if (name == "HOME") {
      return home.string();
    }
    const std::string key{name};
    if (const char* value = std::getenv(key.c_str())) {
      return std::string{value};
    }
    return std::nullopt;
  };
}

biv::repo::Git resolve_git(const fs::path& home) {
  auto git = biv::repo::Git::resolve(getenv_with_home(home));
  REQUIRE(git.has_value());
  return std::move(*git);
}

biv::support::SpawnResult run_ok(
    const biv::repo::Git& git, const std::vector<std::string>& args,
    const std::vector<std::string>& operands,
    const biv::repo::Git::Opts& opts = biv::repo::Git::Opts{}) {
  const auto result = git.run(args, operands, opts);
  REQUIRE(result.has_value());
  INFO("stderr: " << as_string(result->stderr_bytes));
  REQUIRE_FALSE(result->spawn_failed);
  REQUIRE_FALSE(result->timed_out);
  REQUIRE_FALSE(result->io_failed);
  REQUIRE(result->exit_code == 0);
  return *result;
}

struct RepoHistory {
  std::string first;
  std::string second;
};

RepoHistory make_two_commit_repo(const biv::repo::Git& git,
                                 const fs::path& repo) {
  run_ok(git, {"init"}, {repo.string()});
  biv::repo::Git::Opts opts;
  opts.cwd = repo;
  run_ok(git, {"config", "user.name", "Biv Fixture"}, {}, opts);
  run_ok(git, {"config", "user.email", "fixture@example.invalid"}, {}, opts);

  {
    std::ofstream file{repo / "tracked.txt", std::ios::binary};
    file << "first\n";
  }
  run_ok(git, {"add"}, {"tracked.txt"}, opts);
  run_ok(git, {"commit", "-m", "first"}, {}, opts);
  const auto first =
      as_string(run_ok(git, {"rev-parse", "HEAD"}, {}, opts).stdout_bytes);

  {
    std::ofstream file{repo / "tracked.txt", std::ios::binary};
    file << "second\n";
  }
  run_ok(git, {"add"}, {"tracked.txt"}, opts);
  run_ok(git, {"commit", "-m", "second"}, {}, opts);
  const auto second =
      as_string(run_ok(git, {"rev-parse", "HEAD"}, {}, opts).stdout_bytes);

  const auto trim = [](std::string value) {
    while (!value.empty() &&
           (value.back() == '\n' || value.back() == '\r')) {
      value.pop_back();
    }
    return value;
  };
  return RepoHistory{.first = trim(first), .second = trim(second)};
}

bool has_env(const std::vector<std::string>& env,
             const std::string_view item) {
  return std::ranges::find(env, item) != env.end();
}

}  // namespace

TEST_CASE("Git resolve records one fully resolved binary") {
  TempDir root{"resolve"};
  const auto git = resolve_git(root.path());

  CHECK(git.executable().is_absolute());
  CHECK(fs::exists(git.executable()));

  const auto request = biv::repo::git_testing::build_spawn_request(
      git, {"--version"}, {}, biv::repo::Git::Opts{});
  CHECK(request.executable == git.executable());
  REQUIRE_FALSE(request.argv.empty());
  CHECK(request.argv.front() == git.executable().string());
}

TEST_CASE("Git run pins environment away from hostile user config") {
  TempDir root{"hostile-env"};
  const auto excludes = root.path() / "global-ignore";
  {
    std::ofstream patterns{excludes};
    patterns << "junk.log\n";
  }
  {
    std::ofstream config{root.path() / ".gitconfig"};
    config << "[user]\n\tname = Hostile Global Identity\n"
              "\temail = hostile@example.invalid\n"
              "[core]\n\texcludesFile = "
           << excludes.string() << "\n";
  }
  const auto git = resolve_git(root.path());
  const auto repo = root.path() / "repo";
  run_ok(git, {"init"}, {repo.string()});
  biv::repo::Git::Opts ordinary_opts;
  ordinary_opts.cwd = repo;
  run_ok(git, {"config", "user.name", "Local Fixture"}, {}, ordinary_opts);
  run_ok(git, {"config", "user.email", "local@example.invalid"}, {},
         ordinary_opts);
  {
    std::ofstream ignored{repo / "junk.log"};
    ignored << "ignored by the user's global excludes\n";
  }

  const auto request = biv::repo::git_testing::build_spawn_request(
      git, {"status", "--porcelain=v2"}, {}, ordinary_opts);
  CHECK(has_env(request.env, "GIT_TERMINAL_PROMPT=0"));
  CHECK(has_env(request.env, "LC_ALL=C"));
  CHECK(has_env(request.env, "GIT_CONFIG_NOSYSTEM=1"));
  CHECK_FALSE(has_env(request.env, "GIT_CONFIG_GLOBAL=/dev/null"));
  CHECK(has_env(request.env, "GIT_PROTOCOL_FROM_USER=0"));
  CHECK(has_env(request.env, "GIT_CONFIG_COUNT=3"));
  CHECK(has_env(request.env, "GIT_CONFIG_KEY_0=core.hooksPath"));
  CHECK(has_env(request.env, "GIT_CONFIG_VALUE_0=/dev/null"));
  CHECK(has_env(request.env, "GIT_CONFIG_KEY_1=credential.helper"));
  CHECK(has_env(request.env, "GIT_CONFIG_VALUE_1="));
  CHECK(has_env(request.env, "GIT_CONFIG_KEY_2=core.sshCommand"));
  CHECK(has_env(request.env, "GIT_CONFIG_VALUE_2=/usr/bin/false"));
  CHECK(has_env(request.env, "GIT_ASKPASS=/usr/bin/false"));
  CHECK(has_env(request.env, "SSH_ASKPASS=/usr/bin/false"));

  const auto status = run_ok(git, {"status", "--porcelain=v2"}, {},
                             ordinary_opts);
  CHECK(status.stdout_bytes.empty());

  auto restore_opts = ordinary_opts;
  restore_opts.isolate_global_config = true;
  const auto restore_request = biv::repo::git_testing::build_spawn_request(
      git, {"var", "GIT_COMMITTER_IDENT"}, {}, restore_opts);
  CHECK(has_env(restore_request.env, "GIT_CONFIG_GLOBAL=/dev/null"));

  const auto identity = run_ok(git, {"var", "GIT_COMMITTER_IDENT"}, {},
                               restore_opts);
  CHECK(as_string(identity.stdout_bytes).find("Local Fixture") !=
        std::string::npos);
  CHECK(as_string(identity.stdout_bytes).find("Hostile Global Identity") ==
        std::string::npos);
}

TEST_CASE("Git returns merge-base non-ancestry exit one as data") {
  TempDir root{"exit-data"};
  const auto git = resolve_git(root.path());
  const auto repo = root.path() / "repo";
  const auto history = make_two_commit_repo(git, repo);
  biv::repo::Git::Opts opts;
  opts.cwd = repo;

  const auto result = git.run({"merge-base", "--is-ancestor"},
                              {history.second, history.first}, opts);

  REQUIRE(result.has_value());
  CHECK_FALSE(result->spawn_failed);
  CHECK_FALSE(result->timed_out);
  CHECK_FALSE(result->io_failed);
  CHECK(result->exit_code == 1);
}

TEST_CASE("Git request pins no-lazy-fetch and mechanically delimits operands") {
  TempDir root{"request"};
  const auto git = resolve_git(root.path());
  const auto opts = biv::repo::Git::Opts{
      .cwd = root.path(),
      .no_lazy_fetch = true,
      .isolate_global_config = false,
      .stderr_mode = biv::support::StderrMode::separate,
      .stdout_file = std::nullopt,
      .budget = std::chrono::milliseconds{1234}};

  const auto request = biv::repo::git_testing::build_spawn_request(
      git, {"status", "--porcelain"}, {"-rf"}, opts);

  CHECK(has_env(request.env, "GIT_NO_LAZY_FETCH=1"));
  REQUIRE(request.argv.size() >= 7U);
  const std::vector<std::string> expected_tail{"status", "--porcelain", "--",
                                               "-rf"};
  CHECK(std::equal(expected_tail.begin(), expected_tail.end(),
                   request.argv.end() -
                       static_cast<std::ptrdiff_t>(expected_tail.size())));
  CHECK(request.budgets.probe_wall == std::chrono::milliseconds{1234});

  const auto ordinary = biv::repo::git_testing::build_spawn_request(
      git, {"status"}, {}, biv::repo::Git::Opts{});
  CHECK_FALSE(has_env(ordinary.env, "GIT_NO_LAZY_FETCH=1"));
  CHECK(std::ranges::find(ordinary.argv, "--") == ordinary.argv.end());
}

TEST_CASE("RepoEntry preserves unknown notes verbatim for JSON re-emission") {
  const std::string raw =
      R"({"kind":"zz-future","scalar":7,"nested":{"x":[true,null,"v"]}})";
  biv::repo::RepoEntry entry;
  entry.notes.emplace_back(biv::repo::UnknownNote{
      .kind = "zz-future",
      .verbatim_json = raw,
  });

  const auto copied = entry;
  REQUIRE(copied.notes.size() == 1U);
  const auto* unknown = std::get_if<biv::repo::UnknownNote>(&copied.notes.front());
  REQUIRE(unknown != nullptr);
  CHECK(unknown->kind == "zz-future");
  CHECK(unknown->verbatim_json == raw);
}

TEST_CASE("Git streams cat-file stdout to a file") {
  TempDir root{"stdout-file"};
  const auto git = resolve_git(root.path());
  const auto repo = root.path() / "repo";
  static_cast<void>(make_two_commit_repo(git, repo));
  const auto output = root.path() / "blob.out";
  const auto opts = biv::repo::Git::Opts{
      .cwd = repo,
      .no_lazy_fetch = false,
      .isolate_global_config = false,
      .stderr_mode = biv::support::StderrMode::separate,
      .stdout_file = output,
      .budget = std::chrono::seconds{10}};

  const auto result =
      git.run({"cat-file", "blob"}, {"HEAD:tracked.txt"}, opts);

  REQUIRE(result.has_value());
  CHECK(result->exit_code == 0);
  CHECK(result->stdout_bytes.empty());
  std::ifstream file{output, std::ios::binary};
  REQUIRE(file);
  const std::string contents{std::istreambuf_iterator<char>{file},
                             std::istreambuf_iterator<char>{}};
  CHECK(contents == "second\n");
}
