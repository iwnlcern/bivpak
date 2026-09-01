#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "core/ignore/matcher.hpp"
#include "core/repo/capture.hpp"
#include "core/repo/classify.hpp"
#include "core/repo/discover.hpp"
#include "core/repo/eligibility.hpp"
#include "core/repo/git.hpp"
#include "core/repo/git_exec.hpp"
#include "core/repo/restore.hpp"
#include "core/support/subprocess.hpp"
#include "support/temp_dir.hpp"

namespace {

using biv::test_support::as_string;
using biv::test_support::TempDir;

void touch(const std::filesystem::path &path, const std::string &text = {}) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream{path} << text;
}

biv::repo::Git resolved_git(biv::repo::Git::RequestTrace trace = {}) {
  auto git = biv::repo::Git::resolve(
      [](const std::string_view name) -> std::optional<std::string> {
        if (const char *value = std::getenv(std::string{name}.c_str())) {
          return std::string{value};
        }
        return std::nullopt;
      },
      std::move(trace));
  if (!git) {
    throw std::runtime_error{"git unavailable"};
  }
  return *git;
}

biv::repo::Git fake_network_git(const std::filesystem::path &root,
                                const std::string &effective,
                                biv::repo::Git::RequestTrace trace = {}) {
  const auto fake_git = root / "git";
  const auto network_marker = root / "network-spawned";
  touch(fake_git, "#!/bin/sh\n"
                  "resolve=0\n"
                  "for arg in \"$@\"; do\n"
                  "  test \"$arg\" = \"--get-url\" && resolve=1\n"
                  "done\n"
                  "if test \"$resolve\" = 1; then\n"
                  "  printf '%s\\n' '" +
                      effective +
                      "'\n"
                      "  exit 0\n"
                      "fi\n"
                      "printf 'network\\n' >> '" +
                      network_marker.string() +
                      "'\n"
                      "exit 0\n");
  std::filesystem::permissions(fake_git,
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write |
                                   std::filesystem::perms::owner_exec);
  auto git = biv::repo::Git::resolve(
      [&](const std::string_view name) -> std::optional<std::string> {
        if (name == "PATH") {
          return root.string();
        }
        return std::nullopt;
      },
      std::move(trace));
  if (!git) {
    throw std::runtime_error{"fake git unavailable"};
  }
  return *git;
}

bool request_has_env(const biv::support::SpawnRequest &request,
                     const std::string_view value) {
  return std::ranges::find(request.env, value) != request.env.end();
}

bool request_has_argv(const biv::support::SpawnRequest &request,
                      const std::string_view value) {
  return std::ranges::find(request.argv, value) != request.argv.end();
}

biv::support::SpawnResult git_run(const biv::repo::Git &git,
                                  const std::filesystem::path &cwd,
                                  const std::vector<std::string> &args,
                                  const std::vector<std::string> &operands = {},
                                  const bool allow_nonzero = false) {
  biv::repo::Git::Opts options;
  options.cwd = cwd;
  options.allow_user_protocol = true;
  auto result = git.run(args, operands, options);
  if (!result || (!allow_nonzero && result->exit_code != 0)) {
    throw std::runtime_error{"git fixture command failed"};
  }
  return *result;
}

void init_repo(const biv::repo::Git &git, const std::filesystem::path &repo,
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

std::string git_stdout(const biv::support::SpawnResult &result) {
  auto value = as_string(result.stdout_bytes);
  while (!value.empty() && (value.back() == '\n' || value.back() == '\r')) {
    value.pop_back();
  }
  return value;
}

void commit_file(const biv::repo::Git &git, const std::filesystem::path &repo,
                 const std::string &text, const std::string &message) {
  touch(repo / "a.txt", text);
  git_run(git, repo, {"add"}, {"a.txt"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", message});
}

biv::repo::Discovery one_repo(const std::filesystem::path &root = {},
                              const std::filesystem::path &relpath = ".") {
  return biv::repo::Discovery{
      .root = root,
      .repos = {biv::repo::RepoBoundary{.relpath = relpath,
                                        .kind = biv::repo::RepoKind::repo,
                                        .parent_index = std::nullopt}}};
}

std::filesystem::path init_bare_remote(const biv::repo::Git &git,
                                       const std::filesystem::path &root) {
  const auto remote = root / "remote.git";
  std::filesystem::create_directories(remote);
  git_run(git, remote, {"init", "--bare"});
  return remote;
}

void add_remote_and_push(const biv::repo::Git &git,
                         const std::filesystem::path &repo,
                         const std::filesystem::path &remote) {
  git_run(git, repo, {"remote", "add"}, {"origin", remote.string()});
  git_run(git, repo, {"push", "-u", "origin", "main"});
}

class ScopedEnv {
 public:
  ScopedEnv(std::string name, std::string value) : name_(std::move(name)) {
    if (const char *current = std::getenv(name_.c_str()); current != nullptr) {
      previous_ = std::string{current};
    }
    if (::setenv(name_.c_str(), value.c_str(), 1) != 0) {
      throw std::runtime_error{"fixture environment setup failed"};
    }
  }

  ~ScopedEnv() {
    if (previous_) {
      (void)::setenv(name_.c_str(), previous_->c_str(), 1);
    } else {
      (void)::unsetenv(name_.c_str());
    }
  }

  ScopedEnv(const ScopedEnv &) = delete;
  ScopedEnv &operator=(const ScopedEnv &) = delete;

 private:
  std::string name_;
  std::optional<std::string> previous_;
};

std::filesystem::path clone_real_shallow_repo(
    const biv::repo::Git &git, const std::filesystem::path &root,
    const std::string_view name) {
  const auto publisher = root / "publisher";
  init_repo(git, publisher);
  const auto remote = init_bare_remote(git, root);
  add_remote_and_push(git, publisher, remote);
  git_run(git, remote, {"symbolic-ref", "HEAD", "refs/heads/main"});

  const auto clone = root / name;
  git_run(git, root, {"clone", "--depth", "1"},
          {"file://" + remote.string(), clone.string()});
  return clone;
}

void configure_url_rewrite(const biv::repo::Git &git,
                           const std::filesystem::path &repo,
                           const std::string &requested,
                           const std::string &effective) {
  git_run(git, repo,
          {"config", "--local", "url." + effective + ".insteadOf", requested});
}

biv::expected<biv::support::SpawnResult>
real_network_probe(const biv::repo::Git &git, const std::filesystem::path &repo,
                   const std::string &requested,
                   const std::string_view operation = "url-fixture") {
  return biv::repo::invoke_git(
      git, repo, {"ls-remote", "--get-url"}, {requested}, operation,
      biv::repo::GitInvokeOptions{.allow_user_protocol = true,
                                  .call_class =
                                      biv::repo::GitCallClass::network,
                                  .requested_endpoints = {requested}});
}

std::size_t
request_count_with_argv(const std::vector<biv::support::SpawnRequest> &requests,
                        const std::string_view value) {
  return static_cast<std::size_t>(
      std::ranges::count_if(requests, [&](const auto &request) {
        return request_has_argv(request, value);
      }));
}

std::string ssh_expanded_port(const std::filesystem::path &config,
                              const std::vector<std::string> &extra_args) {
  std::vector<std::string> argv{"/usr/bin/ssh", "-G", "-F", config.string()};
  argv.insert(argv.end(), extra_args.begin(), extra_args.end());
  argv.emplace_back("endpoint.invalid");
  auto result = biv::support::run_argv(biv::support::SpawnRequest{
      .executable = "/usr/bin/ssh",
      .argv = std::move(argv),
      .env = {"PATH=/usr/bin:/bin", "LC_ALL=C"},
      .stderr_mode = biv::support::StderrMode::separate,
      .stdout_file = std::nullopt,
      .stdout_cap = 64U * 1024U,
      .stderr_cap = 64U * 1024U,
      .budgets = biv::support::ProbeBudgets{}});
  if (!result || result->exit_code != 0) {
    throw std::runtime_error{"ssh transport expansion failed"};
  }
  const auto output = as_string(result->stdout_bytes);
  const auto marker = output.find("port ");
  if (marker == std::string::npos) {
    throw std::runtime_error{"ssh transport expansion omitted port"};
  }
  const auto begin = marker + std::string_view{"port "}.size();
  return output.substr(begin, output.find('\n', begin) - begin);
}

void stage_artifacts(const biv::repo::CaptureResult &capture,
                     const std::filesystem::path &stage_root) {
  for (const auto &artifact : capture.artifacts) {
    const auto target = stage_root / artifact.archive_path;
    std::filesystem::create_directories(target.parent_path());
    std::filesystem::copy_file(artifact.disk_path, target);
  }
}

} // namespace

TEST_CASE("git invoke options value-initialize extension members") {
  const biv::repo::GitInvokeOptions options{.promisor = true};

  CHECK_FALSE(options.budget_override.has_value());
  CHECK(options.empty_config_keys.empty());
  CHECK(options.requested_endpoints.empty());
}

TEST_CASE("network endpoint carrier fails closed before resolution or spawn") {
  TempDir root{"url-carrier"};
  std::vector<biv::support::SpawnRequest> requests;
  auto git = fake_network_git(
      root.path(), "https://effective.invalid/repo.git",
      [&](const auto &request) { requests.push_back(request); });

  auto missing = biv::repo::invoke_git(
      git, root.path(), {"fetch"}, {"https://requested.invalid/repo.git"},
      "carrier-missing",
      biv::repo::GitInvokeOptions{.call_class =
                                      biv::repo::GitCallClass::network});
  REQUIRE_FALSE(missing.has_value());
  CHECK(biv::repo::engine_error_kind(missing.error()) ==
        biv::repo::EngineErrorKind::git_invocation_failed);
  CHECK(missing.error().detail == "network-endpoint-carrier");
  CHECK(requests.empty());

  auto multiple = biv::repo::invoke_git(
      git, root.path(), {"fetch"}, {"https://requested.invalid/repo.git"},
      "carrier-multiple",
      biv::repo::GitInvokeOptions{
          .call_class = biv::repo::GitCallClass::network,
          .requested_endpoints = {"https://one.invalid/repo.git",
                                  "https://two.invalid/repo.git"}});
  REQUIRE_FALSE(multiple.has_value());
  CHECK(multiple.error().detail == "network-endpoint-carrier");
  CHECK(requests.empty());
}

TEST_CASE("URL comparator implements only the sealed equivalence set") {
  const std::vector<std::pair<std::string, std::string>> equivalent{
      {"HTTPS://Example.Invalid/repo.git/",
       "https://example.invalid:443/repo.git"},
      {"http://example.invalid/repo.git",
       "http://EXAMPLE.invalid:80/repo.git/"},
      {"https://example.invalid/repo.git/",
       "https://example.invalid/repo.git//"},
      {"git@example.invalid:/repo.git", "ssh://git@example.invalid/repo.git"},
      {"example.invalid:/repo.git", "ssh://example.invalid/repo.git"}};
  for (const auto &[requested, effective] : equivalent) {
    INFO(requested << " -> " << effective);
    CHECK(biv::repo::url_endpoints_equivalent(requested, effective));
  }

  const std::vector<std::pair<std::string, std::string>> divergent{
      {"http://example.invalid/repo.git", "https://example.invalid/repo.git"},
      {"git@example.invalid:repo.git", "ssh://git@example.invalid/repo.git"},
      {"git@example.invalid:/repo.git",
       "ssh://git@example.invalid:22/repo.git"},
      {"ssh://example.invalid/repo.git", "ssh://example.invalid:22/repo.git"},
      {"git://example.invalid/repo.git", "git://example.invalid:9418/repo.git"},
      {"https://one.invalid/repo.git", "https://two.invalid/repo.git"},
      {"https://example.invalid/repo.git",
       "https://example.invalid/repo.git//"},
      {"https://example.invalid/repo.git",
       "https://example.invalid/repo.git///"},
      {"https://@example.invalid/repo.git", "https://example.invalid/repo.git"},
      {"https://user@example.invalid/repo.git",
       "https://other@example.invalid/repo.git"},
      {"1SSH://example.invalid/repo.git", "1ssh://example.invalid/repo.git"},
      {"https://example.invalid/repo.git?ref=main",
       "https://example.invalid/repo.git?ref=main/"},
      {"https://EXAMPLE.invalid:bogus/repo.git",
       "https://example.invalid:bogus/repo.git"},
      {"not a URL", "still not a URL"}};
  for (const auto &[requested, effective] : divergent) {
    INFO(requested << " -> " << effective);
    CHECK_FALSE(biv::repo::url_endpoints_equivalent(requested, effective));
  }
}

TEST_CASE("network divergence refuses without a hook before network spawn") {
  TempDir root{"url-absent-hook"};
  std::vector<biv::support::SpawnRequest> requests;
  auto git = fake_network_git(
      root.path(), "https://effective.invalid/repo.git",
      [&](const auto &request) { requests.push_back(request); });
  biv::repo::UrlDivergenceRun run;
  biv::repo::ScopedUrlDivergenceRun scoped{run};

  auto result = biv::repo::invoke_git(
      git, root.path(), {"fetch"}, {"https://requested.invalid/repo.git"},
      "restore-proof",
      biv::repo::GitInvokeOptions{
          .call_class = biv::repo::GitCallClass::network,
          .requested_endpoints = {"https://requested.invalid/repo.git"}});

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("requested") ==
        "https://requested.invalid/repo.git");
  CHECK(result.error().facts.at("effective") ==
        "https://effective.invalid/repo.git");
  CHECK(result.error().facts.at("op") == "restore-proof");
  REQUIRE(requests.size() == 1);
  CHECK(request_has_argv(requests.front(), "--get-url"));
  CHECK_FALSE(std::filesystem::exists(root.path() / "network-spawned"));
}

TEST_CASE("consent decision memo prompts and discloses once per triple") {
  TempDir root{"url-consent-memo"};
  std::vector<biv::support::SpawnRequest> requests;
  auto git = fake_network_git(
      root.path(), "https://effective.invalid/repo.git",
      [&](const auto &request) { requests.push_back(request); });
  std::size_t hook_calls = 0;
  biv::repo::UrlDivergenceRun run;
  run.hook = [&](const biv::repo::UrlDivergence &event) {
    ++hook_calls;
    CHECK(event.requested == "https://requested.invalid/repo.git");
    CHECK(event.effective == "https://effective.invalid/repo.git");
    CHECK(event.operation == "eligibility-advertisement");
    CHECK(event.repo == root.path());
    return biv::repo::UrlDivergenceDecision::proceed;
  };
  biv::repo::ScopedUrlDivergenceRun scoped{run};
  const auto options = biv::repo::GitInvokeOptions{
      .call_class = biv::repo::GitCallClass::network,
      .requested_endpoints = {"https://requested.invalid/repo.git"}};

  auto first = biv::repo::invoke_git(git, root.path(), {"ls-remote"},
                                     {"https://requested.invalid/repo.git"},
                                     "eligibility-advertisement", options);
  auto second = biv::repo::invoke_git(git, root.path(), {"ls-remote"},
                                      {"https://requested.invalid/repo.git"},
                                      "eligibility-advertisement", options);

  REQUIRE(first.has_value());
  REQUIRE(second.has_value());
  CHECK(hook_calls == 1);
  REQUIRE(run.accepted.size() == 1);
  CHECK(run.accepted.front().repo == root.path());
  CHECK(std::filesystem::exists(root.path() / "network-spawned"));
  CHECK(requests.size() == 4);
}

TEST_CASE("F-URL-1 real git a eligibility refuses a repo-local rewrite") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git =
      resolved_git([&](const auto &request) { requests.push_back(request); });
  TempDir root{"url-real-eligibility"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const std::string requested{"http://endpoint.invalid/repo.git"};
  const std::string effective{"https://endpoint.invalid/repo.git"};
  git_run(git, repo, {"remote", "add"}, {"origin", requested});
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  configure_url_rewrite(git, repo, requested, effective);
  requests.clear();

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("requested") == requested);
  CHECK(result.error().facts.at("effective") == effective);
  CHECK(result.error().facts.at("op") == "eligibility-advertisement");
  CHECK(request_count_with_argv(requests, "ls-remote") == 1U);
  CHECK_FALSE(request_has_argv(requests.front(), "--heads"));
}

TEST_CASE("F-URL-1 real git b restore ref proof refusal is entry-fatal") {
  auto git = resolved_git();
  TempDir root{"url-real-restore-ref"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, source, remote);
  const auto head = git_stdout(git_run(git, source, {"rev-parse", "HEAD"}));
  const auto partial = root.path() / "partial";
  init_repo(git, partial, false);
  const std::string requested{"http://endpoint.invalid/proof.git"};
  const std::string effective{"https://endpoint.invalid/proof.git"};
  configure_url_rewrite(git, partial, requested, effective);
  const std::string missing_sha(40U, '1');
  biv::repo::RepoEntry entry;
  entry.id = "root";
  entry.relpath = ".";
  entry.kind = biv::repo::RepoKind::repo;
  entry.remote = "origin";
  entry.remotes = {{.name = "origin", .url = remote.string()}};
  entry.sha = head;
  entry.branch = "main";
  entry.head_state = biv::repo::HeadState::branch;
  entry.capture_mode = biv::repo::CaptureMode::overlay;
  entry.eligibility =
      biv::repo::Eligibility{.method = "ls-remote-ancestry",
                             .result = biv::repo::EligibilityResult::proven,
                             .checked_at = "fixture",
                             .proof = biv::repo::Proof{.remote = "origin",
                                                       .url = remote.string(),
                                                       .ref = "refs/heads/main",
                                                       .tip_sha = head}};
  entry.local_refs = {biv::repo::LocalRef{
      .ref = "refs/heads/missing",
      .sha = missing_sha,
      .availability = biv::repo::RefAvailability::remote_proven,
      .proof = biv::repo::Proof{.remote = "proof",
                                .url = requested,
                                .ref = "refs/heads/missing",
                                .tip_sha = missing_sha}}};

  auto result =
      biv::repo::restore_entry(git, entry, partial, root.path() / "stage");

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("requested") == requested);
  CHECK(result.error().facts.at("effective") == effective);
  CHECK(result.error().facts.at("op") == "fetch");
}

TEST_CASE("F-URL-1 real git c unchanged endpoint stays silent") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git =
      resolved_git([&](const auto &request) { requests.push_back(request); });
  TempDir root{"url-real-unchanged"};
  const auto remote = init_bare_remote(git, root.path());
  const std::string requested{remote.string()};
  requests.clear();

  auto result = real_network_probe(git, root.path(), requested);

  REQUIRE(result.has_value());
  CHECK(request_count_with_argv(requests, "ls-remote") == 2U);
}

TEST_CASE("F-URL-1 real git e sealed equivalent forms stay silent") {
  const std::vector<std::pair<std::string, std::string>> cases{
      {"https://endpoint.invalid/repo.git/",
       "https://endpoint.invalid/repo.git"},
      {"https://ENDPOINT.invalid/repo.git",
       "https://endpoint.invalid/repo.git"},
      {"https://endpoint.invalid/repo.git",
       "https://endpoint.invalid:443/repo.git"}};
  for (std::size_t index = 0; index < cases.size(); ++index) {
    INFO("equivalent arm " << index);
    std::vector<biv::support::SpawnRequest> requests;
    auto git =
        resolved_git([&](const auto &request) { requests.push_back(request); });
    TempDir root{"url-real-equivalent-" + std::to_string(index)};
    init_repo(git, root.path(), false);
    const auto &[requested, effective] = cases.at(index);
    configure_url_rewrite(git, root.path(), requested, effective);
    requests.clear();

    auto result = real_network_probe(git, root.path(), requested);

    REQUIRE(result.has_value());
    CHECK(request_count_with_argv(requests, "ls-remote") == 2U);
  }
}

TEST_CASE("F-URL-1 veto-7 real-git multi-slash rewrite diverges") {
  auto git = resolved_git();
  TempDir root{"url-real-multi-slash"};
  init_repo(git, root.path(), false);
  const std::string requested{"https://endpoint.invalid/repo.git"};
  const std::string effective{"https://endpoint.invalid/repo.git//"};
  configure_url_rewrite(git, root.path(), requested, effective);
  REQUIRE(git_stdout(git_run(git, root.path(), {"ls-remote", "--get-url"},
                             {requested})) == effective);

  auto result = real_network_probe(git, root.path(), requested, "multi-slash");

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("requested") == requested);
  CHECK(result.error().facts.at("effective") == effective);
  CHECK(result.error().facts.at("op") == "multi-slash");
}

TEST_CASE("F-URL-1 real git f scheme change alone diverges") {
  auto git = resolved_git();
  TempDir root{"url-real-scheme"};
  init_repo(git, root.path(), false);
  const std::string requested{"http://endpoint.invalid/repo.git"};
  const std::string effective{"https://endpoint.invalid/repo.git"};
  configure_url_rewrite(git, root.path(), requested, effective);
  REQUIRE(git_stdout(git_run(git, root.path(), {"ls-remote", "--get-url"},
                             {requested})) == effective);

  auto result = real_network_probe(git, root.path(), requested);

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
}

TEST_CASE("F-URL-1 real git g absent hook is fail-safe") {
  auto git = resolved_git();
  TempDir root{"url-real-absent-hook"};
  init_repo(git, root.path(), false);
  const std::string requested{"https://one.invalid/repo.git"};
  const std::string effective{"https://two.invalid/repo.git"};
  configure_url_rewrite(git, root.path(), requested, effective);

  auto result = real_network_probe(git, root.path(), requested, "absent-hook");

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("requested") == requested);
  CHECK(result.error().facts.at("effective") == effective);
}

TEST_CASE("F-URL-1 real git h resolution uses the network call cwd") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git =
      resolved_git([&](const auto &request) { requests.push_back(request); });
  TempDir root{"url-real-context"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo, false);
  const std::string requested{"https://one.invalid/repo.git"};
  const std::string effective{"https://two.invalid/repo.git"};
  configure_url_rewrite(git, repo, requested, effective);
  CHECK(git_stdout(git_run(git, root.path(), {"ls-remote", "--get-url"},
                           {requested})) == requested);
  requests.clear();

  auto result = real_network_probe(git, repo, requested, "same-context");

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().facts.at("effective") == effective);
  REQUIRE(requests.size() == 1U);
  CHECK(requests.front().argv.at(2) == repo.string());
}

TEST_CASE("F-URL-1 real git i root overlay proof fetch refuses") {
  auto git = resolved_git();
  TempDir root{"url-real-overlay-proof"};
  const auto partial = root.path() / "partial";
  init_repo(git, partial, false);
  const std::string requested{"http://endpoint.invalid/repo.git"};
  const std::string effective{"https://endpoint.invalid/repo.git"};
  configure_url_rewrite(git, partial, requested, effective);
  const std::string sha(40U, '1');
  biv::repo::RepoEntry entry;
  entry.id = "root";
  entry.relpath = ".";
  entry.kind = biv::repo::RepoKind::repo;
  entry.sha = sha;
  entry.head_state = biv::repo::HeadState::detached;
  entry.capture_mode = biv::repo::CaptureMode::overlay;
  entry.eligibility =
      biv::repo::Eligibility{.method = "ls-remote-ancestry",
                             .result = biv::repo::EligibilityResult::proven,
                             .checked_at = "fixture",
                             .proof = biv::repo::Proof{.remote = "origin",
                                                       .url = requested,
                                                       .ref = "refs/heads/main",
                                                       .tip_sha = sha}};

  auto result =
      biv::repo::restore_entry(git, entry, partial, root.path() / "stage");

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(result.error().facts.at("op") == "fetch");
}

TEST_CASE("F-URL-1 real git j overlay clone is gated and full clone is not") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git =
      resolved_git([&](const auto &request) { requests.push_back(request); });
  TempDir root{"url-real-clone-population"};
  const auto partial = root.path() / "partial";
  init_repo(git, partial, false);
  const std::string requested{"http://endpoint.invalid/repo.git"};
  const std::string effective{"https://endpoint.invalid/repo.git"};
  configure_url_rewrite(git, partial, requested, effective);
  const std::string sha(40U, '1');
  biv::repo::RepoEntry overlay;
  overlay.id = "overlay";
  overlay.relpath = "overlay";
  overlay.kind = biv::repo::RepoKind::repo;
  overlay.remote = "origin";
  overlay.remotes = {{.name = "origin", .url = requested}};
  overlay.sha = sha;
  overlay.head_state = biv::repo::HeadState::detached;
  overlay.capture_mode = biv::repo::CaptureMode::overlay;
  overlay.eligibility =
      biv::repo::Eligibility{.method = "ls-remote-ancestry",
                             .result = biv::repo::EligibilityResult::proven,
                             .checked_at = "fixture",
                             .proof = biv::repo::Proof{.remote = "origin",
                                                       .url = requested,
                                                       .ref = "refs/heads/main",
                                                       .tip_sha = sha}};
  requests.clear();

  auto refused =
      biv::repo::restore_entry(git, overlay, partial, root.path() / "stage");

  REQUIRE_FALSE(refused.has_value());
  CHECK(biv::repo::engine_error_kind(refused.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
  CHECK(request_count_with_argv(requests, "ls-remote") == 1U);

  const auto source = root.path() / "source";
  init_repo(git, source);
  const auto source_head =
      git_stdout(git_run(git, source, {"rev-parse", "HEAD"}));
  const auto stage = root.path() / "full-stage";
  std::filesystem::create_directories(stage);
  git_run(git, source, {"bundle", "create"},
          {(stage / "repo.bundle").string(), "--all"});
  biv::repo::RepoEntry full;
  full.id = "full";
  full.relpath = "full";
  full.kind = biv::repo::RepoKind::repo;
  full.sha = source_head;
  full.branch = "main";
  full.head_state = biv::repo::HeadState::branch;
  full.capture_mode = biv::repo::CaptureMode::full;
  full.bundle = std::filesystem::path{"repo.bundle"};
  requests.clear();

  auto restored = biv::repo::restore_entry(git, full, partial, stage);

  REQUIRE(restored.has_value());
  CHECK(request_count_with_argv(requests, "--get-url") == 0U);
}

TEST_CASE("F-URL-1 real git k endpoint carrier refuses zero and many") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git =
      resolved_git([&](const auto &request) { requests.push_back(request); });
  TempDir root{"url-real-carrier"};
  init_repo(git, root.path(), false);
  const std::string requested{"https://endpoint.invalid/repo.git"};
  requests.clear();

  auto missing = biv::repo::invoke_git(
      git, root.path(), {"ls-remote", "--get-url"}, {requested}, "carrier-zero",
      biv::repo::GitInvokeOptions{.call_class =
                                      biv::repo::GitCallClass::network});
  auto multiple = biv::repo::invoke_git(
      git, root.path(), {"ls-remote", "--get-url"}, {requested}, "carrier-many",
      biv::repo::GitInvokeOptions{
          .call_class = biv::repo::GitCallClass::network,
          .requested_endpoints = {requested, requested}});

  REQUIRE_FALSE(missing.has_value());
  REQUIRE_FALSE(multiple.has_value());
  CHECK(missing.error().detail == "network-endpoint-carrier");
  CHECK(multiple.error().detail == "network-endpoint-carrier");
  CHECK(requests.empty());
}

TEST_CASE("F-URL-1 real git l absolute scp rewrite stays silent") {
  auto git = resolved_git();
  TempDir root{"url-real-scp-absolute"};
  init_repo(git, root.path(), false);
  const std::string requested{"git@endpoint.invalid:/repo.git"};
  const std::string effective{"ssh://git@endpoint.invalid/repo.git"};
  configure_url_rewrite(git, root.path(), requested, effective);

  auto result = real_network_probe(git, root.path(), requested);

  REQUIRE(result.has_value());
}

TEST_CASE("F-URL-1 real git m relative scp rewrite diverges") {
  auto git = resolved_git();
  TempDir root{"url-real-scp-relative"};
  init_repo(git, root.path(), false);
  const std::string requested{"git@endpoint.invalid:repo.git"};
  const std::string effective{"ssh://git@endpoint.invalid/repo.git"};
  configure_url_rewrite(git, root.path(), requested, effective);

  auto result = real_network_probe(git, root.path(), requested);

  REQUIRE_FALSE(result.has_value());
  CHECK(biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::url_divergence_refused);
}

TEST_CASE("F-URL-1 real git n implicit and explicit SSH ports diverge") {
  TempDir root{"url-real-ssh-port"};
  const auto ssh_config = root.path() / "ssh_config";
  touch(ssh_config, "Host endpoint.invalid\n  Port 2222\n");
  CHECK(ssh_expanded_port(ssh_config, {}) == "2222");
  CHECK(ssh_expanded_port(ssh_config, {"-p", "22"}) == "22");

  const std::vector<std::pair<std::string, std::string>> cases{
      {"git@endpoint.invalid:/repo.git",
       "ssh://git@endpoint.invalid:22/repo.git"},
      {"ssh://endpoint.invalid/repo.git",
       "ssh://endpoint.invalid:22/repo.git"}};
  for (std::size_t index = 0; index < cases.size(); ++index) {
    INFO("SSH port arm " << index);
    const auto repo = root.path() / ("repo-" + std::to_string(index));
    auto git = resolved_git();
    init_repo(git, repo, false);
    const auto &[requested, effective] = cases.at(index);
    configure_url_rewrite(git, repo, requested, effective);

    auto result = real_network_probe(git, repo, requested);

    CHECK_FALSE(result.has_value());
    if (!result) {
      CHECK(biv::repo::engine_error_kind(result.error()) ==
            biv::repo::EngineErrorKind::url_divergence_refused);
    }
  }
}

TEST_CASE("F-URL-1 real git o HTTP default port stays silent") {
  auto git = resolved_git();
  TempDir root{"url-real-http-port"};
  init_repo(git, root.path(), false);
  const std::string requested{"http://endpoint.invalid/repo.git"};
  const std::string effective{"http://endpoint.invalid:80/repo.git"};
  configure_url_rewrite(git, root.path(), requested, effective);

  auto result = real_network_probe(git, root.path(), requested);

  REQUIRE(result.has_value());
}

TEST_CASE(
    "repo discovery preserves prune ordering and records nested boundaries") {
  TempDir root{"discover"};
  std::filesystem::create_directories(root.path() / "ignored/repo/.git");
  std::filesystem::create_directories(root.path() / ".biv/private/.git");
  std::filesystem::create_directories(root.path() / "visible/.git");
  std::filesystem::create_directories(root.path() / "visible/nested/.git");
  touch(root.path() / "visible/linked/.git",
        "gitdir: ../../.git/worktrees/linked\n");
  auto matcher = biv::ignore::Matcher::compile("ignored/\n", false);
  REQUIRE(matcher.has_value());

  auto result = biv::repo::discover(root.path(), *matcher);

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
  init_repo(git, root.path(), false);
  touch(root.path() / "payload.txt", "payload\n");

  auto zero = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(zero.has_value());
  CHECK(zero->entry.head_state == biv::repo::HeadState::unborn);
  CHECK_FALSE(zero->entry.eligibility.has_value());
  CHECK(zero->fence == biv::repo::Classification::Fence::none);

  git_run(git, root.path(), {"hash-object", "-w"}, {"payload.txt"});
  const auto blob = git_run(git, root.path(), {"hash-object"}, {"payload.txt"});
  const std::string sha{
      reinterpret_cast<const char *>(blob.stdout_bytes.data()),
      blob.stdout_bytes.size() - 1U};
  git_run(git, root.path(), {"update-ref", "refs/tags/blob-only", sha});
  git_run(git, root.path(), {"remote", "add"},
          {"origin", (root.path() / "remote.git").string()});

  auto any_ref = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(any_ref.has_value());
  REQUIRE(any_ref->entry.eligibility.has_value());
  CHECK(any_ref->entry.eligibility->result ==
        biv::repo::EligibilityResult::unborn_head);
  CHECK(any_ref->entry.capture_mode == biv::repo::CaptureMode::full);
  CHECK(any_ref->fence == biv::repo::Classification::Fence::none);
  REQUIRE(any_ref->entry.remotes.size() == 1);
  CHECK(any_ref->entry.remotes[0].name == "origin");
}

TEST_CASE("classification fences discovery shape, dirt, and unmerged paths") {
  auto git = resolved_git();
  TempDir root{"classify-fences"};
  init_repo(git, root.path());

  auto nested_discovery = one_repo();
  nested_discovery.repos.push_back(
      biv::repo::RepoBoundary{.relpath = "nested",
                              .kind = biv::repo::RepoKind::nested,
                              .parent_index = 0});
  auto nested = biv::repo::classify(git, root.path(), nested_discovery);
  REQUIRE(nested.has_value());
  CHECK(nested->fence == biv::repo::Classification::Fence::nested);

  touch(root.path() / "dirty.txt", "dirty\n");
  auto dirty = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(dirty.has_value());
  CHECK(dirty->fence == biv::repo::Classification::Fence::dirty);
}

TEST_CASE("classification neutralizes repo-local clean filter commands") {
  auto git = resolved_git();
  TempDir root{"classify-filter-command"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  touch(repo / ".gitattributes", "* filter=evil\n");
  git_run(git, repo, {"add"}, {".gitattributes"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "attributes"});

  const auto marker = root.path() / "clean-filter-ran";
  const auto driver = root.path() / "evil-clean.sh";
  touch(driver, "#!/bin/sh\n: > '" + marker.string() + "'\ncat\n");
  std::filesystem::permissions(driver,
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write |
                                   std::filesystem::perms::owner_exec,
                               std::filesystem::perm_options::replace);
  git_run(git, repo, {"config", "filter.evil.clean", driver.string()});
  git_run(git, repo, {"config", "filter.dormant.smudge", "unused"});
  git_run(git, repo, {"config", "filter.dormant.process", "unused"});
  git_run(git, repo, {"config", "diff.dormant.command", "unused"});
  git_run(git, repo, {"config", "diff.dormant.textconv", "unused"});
  git_run(git, repo, {"config", "merge.dormant.driver", "unused"});
  git_run(git, repo, {"config", "core.editor", "not-a-driver"});
  REQUIRE_FALSE(std::filesystem::exists(marker));

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  REQUIRE(result->entry.engine_source.has_value());
  CHECK(result->entry.engine_source->neutralized_git_config_keys ==
        std::vector<std::string>{
            "diff.dormant.command", "diff.dormant.textconv",
            "filter.dormant.process", "filter.dormant.smudge",
            "filter.evil.clean", "merge.dormant.driver"});
  CHECK_FALSE(std::filesystem::exists(marker));
}

TEST_CASE("classification neutralizes clean filters from local includes") {
  auto git = resolved_git();
  TempDir root{"classify-included-filter-command"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  touch(repo / ".gitattributes", "* filter=evil\n");
  git_run(git, repo, {"add"}, {".gitattributes"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "attributes"});

  const auto marker = root.path() / "included-clean-filter-ran";
  const auto driver = root.path() / "evil-included-clean.sh";
  touch(driver, "#!/bin/sh\n: > '" + marker.string() + "'\ncat\n");
  std::filesystem::permissions(driver,
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write |
                                   std::filesystem::perms::owner_exec,
                               std::filesystem::perm_options::replace);
  const auto included = repo / ".git/evil-include";
  git_run(git, repo,
          {"config", "--file", included.string(), "filter.evil.clean",
           driver.string()});
  git_run(git, repo, {"config", "--local", "include.path", "evil-include"});
  REQUIRE_FALSE(std::filesystem::exists(marker));

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  REQUIRE(result->entry.engine_source.has_value());
  CHECK(result->entry.engine_source->neutralized_git_config_keys ==
        std::vector<std::string>{"filter.evil.clean"});
  CHECK_FALSE(std::filesystem::exists(marker));
}

TEST_CASE("classification neutralizes clean filters from worktree config") {
  auto git = resolved_git();
  TempDir root{"classify-worktree-filter-command"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  touch(repo / ".gitattributes", "* filter=evil\n");
  git_run(git, repo, {"add"}, {".gitattributes"});
  git_run(git, repo,
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "attributes"});

  const auto marker = root.path() / "worktree-clean-filter-ran";
  const auto driver = root.path() / "evil-worktree-clean.sh";
  touch(driver, "#!/bin/sh\n: > '" + marker.string() + "'\ncat\n");
  std::filesystem::permissions(driver,
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write |
                                   std::filesystem::perms::owner_exec,
                               std::filesystem::perm_options::replace);
  git_run(git, repo,
          {"config", "--local", "core.repositoryformatversion", "1"});
  git_run(git, repo,
          {"config", "--local", "extensions.worktreeConfig", "true"});
  git_run(git, repo,
          {"config", "--worktree", "filter.evil.clean", driver.string()});
  REQUIRE_FALSE(std::filesystem::exists(marker));

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  REQUIRE(result->entry.engine_source.has_value());
  CHECK(result->entry.engine_source->neutralized_git_config_keys ==
        std::vector<std::string>{"filter.evil.clean"});
  CHECK_FALSE(std::filesystem::exists(marker));
}

TEST_CASE("classification treats disabled worktree config as empty in linked "
          "worktrees") {
  auto git = resolved_git();
  TempDir root{"classify-disabled-worktree-config"};
  const auto repo = root.path() / "repo";
  const auto linked = root.path() / "linked";
  init_repo(git, repo);
  git_run(git, repo, {"worktree", "add", "-b", "linked", linked.string()});

  auto result = biv::repo::classify(git, linked, one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  REQUIRE(result->entry.engine_source.has_value());
  CHECK(result->entry.engine_source->neutralized_git_config_keys.empty());
}

TEST_CASE("classification detects gitlinks from the parent index") {
  auto git = resolved_git();
  TempDir root{"classify-gitlink"};
  init_repo(git, root.path());
  const auto head =
      git_stdout(git_run(git, root.path(), {"rev-parse", "HEAD"}));
  git_run(
      git, root.path(),
      {"update-index", "--add", "--cacheinfo", "160000," + head + ",module"});

  auto result = biv::repo::classify(git, root.path(), one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::submodule);
  REQUIRE(result->issue.has_value());
  CHECK(result->issue->kind ==
        biv::repo::EngineErrorKind::repo_submodule_unsupported);
  REQUIRE(result->issue->paths.size() == 1);
  CHECK(result->issue->paths[0] == "module");
}

TEST_CASE("classification reports each unmerged path before the dirt gate") {
  auto git = resolved_git();
  TempDir root{"classify-unmerged"};
  init_repo(git, root.path());
  git_run(git, root.path(), {"checkout", "-b", "side"});
  commit_file(git, root.path(), "side\n", "side");
  git_run(git, root.path(), {"checkout", "main"});
  commit_file(git, root.path(), "main\n", "main");
  git_run(git, root.path(), {"config", "user.name", "Biv Test"});
  git_run(git, root.path(), {"config", "user.email", "biv@example.invalid"});
  const auto merge = git_run(git, root.path(), {"merge", "side"}, {}, true);
  REQUIRE(merge.exit_code != 0);

  auto result = biv::repo::classify(git, root.path(), one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::unmerged);
  REQUIRE(result->issue.has_value());
  CHECK(result->issue->kind ==
        biv::repo::EngineErrorKind::unmerged_index_unrepresentable);
  REQUIRE(result->issue->paths.size() == 1);
  CHECK(result->issue->paths[0] == "a.txt");
}

TEST_CASE(
    "classification records head, branch, refs, remotes, and promisor policy") {
  auto git = resolved_git();
  TempDir root{"classify-clean"};
  init_repo(git, root.path());
  git_run(git, root.path(), {"remote", "add"},
          {"origin", "https://example.invalid/r.git"});
  git_run(git, root.path(), {"config", "remote.origin.promisor", "true"});
  git_run(git, root.path(), {"tag", "v1"});

  auto result = biv::repo::classify(git, root.path(), one_repo());

  REQUIRE(result.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  CHECK(result->entry.promisor);
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
  init_repo(git, root.path());
  git_run(git, root.path(), {"remote", "add"},
          {"origin", "https://example.invalid/r.git"});
  const auto head =
      git_stdout(git_run(git, root.path(), {"rev-parse", "HEAD"}));
  touch(root.path() / ".git/shallow", head + "\n");
  git_run(git, root.path(), {"config", "remote.origin.promisor", "false"});
  auto disabled = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(disabled.has_value());
  CHECK_FALSE(disabled->entry.promisor);
  REQUIRE(disabled->entry.shallow.has_value());
  CHECK(disabled->entry.notes.empty());
  git_run(git, root.path(), {"config", "remote.origin.promisor", "true"});

  auto result = biv::repo::classify(git, root.path(), one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK(result->entry.sha == head);
  CHECK(result->entry.shallow->boundary == std::vector<std::string>{head});
  CHECK_FALSE(result->entry.bundle.has_value());
  REQUIRE(result->entry.notes.size() == 1);
  CHECK(std::holds_alternative<biv::repo::PromisorSourceNote>(
      result->entry.notes.front()));
}

TEST_CASE("classification records a zero-ref shallow unborn source as payload-only") {
  TempDir root{"classify-shallow-unborn-zero-ref"};
  const auto home = root.path() / "home";
  const auto global_config = root.path() / "global.gitconfig";
  std::filesystem::create_directories(home);
  touch(global_config, "[protocol \"file\"]\n\tallow = always\n");
  ScopedEnv fixture_home{"HOME", home.string()};
  ScopedEnv fixture_global{"GIT_CONFIG_GLOBAL", global_config.string()};
  ScopedEnv fixture_no_system{"GIT_CONFIG_NOSYSTEM", "1"};
  auto git = resolved_git();
  const auto repo = clone_real_shallow_repo(git, root.path(), "zero-ref");
  git_run(git, repo, {"checkout", "--orphan", "orphan-zero"});
  git_run(git, repo, {"update-ref", "-d", "refs/heads/main"});

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK_FALSE(result->entry.shallow->boundary.empty());
  CHECK(result->entry.head_state == biv::repo::HeadState::unborn);
  CHECK_FALSE(result->entry.sha.has_value());
  CHECK(result->entry.branch == "orphan-zero");
  CHECK(result->entry.local_refs.empty());
  CHECK_FALSE(result->entry.bundle.has_value());
  CHECK_FALSE(result->entry.eligibility.has_value());
}

TEST_CASE("classification suppresses refs for a shallow unborn source") {
  TempDir root{"classify-shallow-unborn-refs"};
  const auto home = root.path() / "home";
  const auto global_config = root.path() / "global.gitconfig";
  std::filesystem::create_directories(home);
  touch(global_config, "[protocol \"file\"]\n\tallow = always\n");
  ScopedEnv fixture_home{"HOME", home.string()};
  ScopedEnv fixture_global{"GIT_CONFIG_GLOBAL", global_config.string()};
  ScopedEnv fixture_no_system{"GIT_CONFIG_NOSYSTEM", "1"};
  auto git = resolved_git();
  const auto repo = clone_real_shallow_repo(git, root.path(), "with-refs");
  git_run(git, repo, {"checkout", "--orphan", "orphan-refs"});

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK_FALSE(result->entry.shallow->boundary.empty());
  CHECK(result->entry.head_state == biv::repo::HeadState::unborn);
  CHECK_FALSE(result->entry.sha.has_value());
  CHECK(result->entry.branch == "orphan-refs");
  CHECK(result->entry.local_refs.empty());
  CHECK_FALSE(result->entry.bundle.has_value());
  CHECK_FALSE(result->entry.eligibility.has_value());
}

TEST_CASE("classification lets shallowness dominate dirt for a born source") {
  TempDir root{"classify-shallow-dirty-born"};
  const auto home = root.path() / "home";
  const auto global_config = root.path() / "global.gitconfig";
  std::filesystem::create_directories(home);
  touch(global_config, "[protocol \"file\"]\n\tallow = always\n");
  ScopedEnv fixture_home{"HOME", home.string()};
  ScopedEnv fixture_global{"GIT_CONFIG_GLOBAL", global_config.string()};
  ScopedEnv fixture_no_system{"GIT_CONFIG_NOSYSTEM", "1"};
  auto git = resolved_git();
  const auto repo = clone_real_shallow_repo(git, root.path(), "dirty-born");
  touch(repo / "a.txt", "modified\n");

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK_FALSE(result->entry.shallow->boundary.empty());
  CHECK(result->entry.local_refs.empty());
  CHECK_FALSE(result->entry.eligibility.has_value());
  CHECK_FALSE(result->entry.bundle.has_value());
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  CHECK_FALSE(result->issue.has_value());
}

TEST_CASE("classification lets shallowness dominate dirt for an unborn source") {
  TempDir root{"classify-shallow-dirty-unborn"};
  const auto home = root.path() / "home";
  const auto global_config = root.path() / "global.gitconfig";
  std::filesystem::create_directories(home);
  touch(global_config, "[protocol \"file\"]\n\tallow = always\n");
  ScopedEnv fixture_home{"HOME", home.string()};
  ScopedEnv fixture_global{"GIT_CONFIG_GLOBAL", global_config.string()};
  ScopedEnv fixture_no_system{"GIT_CONFIG_NOSYSTEM", "1"};
  auto git = resolved_git();
  const auto repo = clone_real_shallow_repo(git, root.path(), "dirty-unborn");
  git_run(git, repo, {"checkout", "--orphan", "orphan-dirty"});

  auto result = biv::repo::classify(git, repo, one_repo());

  REQUIRE(result.has_value());
  REQUIRE(result->entry.shallow.has_value());
  CHECK_FALSE(result->entry.shallow->boundary.empty());
  CHECK(result->entry.head_state == biv::repo::HeadState::unborn);
  CHECK_FALSE(result->entry.sha.has_value());
  CHECK(result->entry.branch == "orphan-dirty");
  CHECK(result->fence == biv::repo::Classification::Fence::none);
  CHECK_FALSE(result->issue.has_value());
}

TEST_CASE("eligibility proves HEAD from one advertisement snapshot") {
  auto git = resolved_git();
  TempDir root{"eligibility-proven"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, repo, remote);
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result ==
        biv::repo::EligibilityResult::proven);
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
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path());
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
  const auto no_remote_repo = root.path() / "none";
  init_repo(git, no_remote_repo);
  auto no_remote = biv::repo::classify(git, no_remote_repo, one_repo());
  REQUIRE(no_remote.has_value());
  REQUIRE(biv::repo::run_eligibility(git, no_remote->entry).has_value());
  REQUIRE(no_remote->entry.eligibility.has_value());
  CHECK(no_remote->entry.eligibility->result ==
        biv::repo::EligibilityResult::no_remote);
  CHECK(no_remote->entry.capture_mode == biv::repo::CaptureMode::full);

  const auto unreachable_repo = root.path() / "unreachable";
  init_repo(git, unreachable_repo);
  git_run(git, unreachable_repo, {"remote", "add"},
          {"origin", (root.path() / "missing.git").string()});
  auto unreachable = biv::repo::classify(git, unreachable_repo, one_repo());
  REQUIRE(unreachable.has_value());
  REQUIRE(biv::repo::run_eligibility(git, unreachable->entry).has_value());
  REQUIRE(unreachable->entry.eligibility.has_value());
  CHECK(unreachable->entry.eligibility->result ==
        biv::repo::EligibilityResult::remote_unreachable);
  CHECK(unreachable->entry.capture_mode == biv::repo::CaptureMode::full);
}

TEST_CASE(
    "eligibility leaves an advertised unknown tip unmodified and honest") {
  auto git = resolved_git();
  TempDir root{"eligibility-fetch-probe"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, repo, remote);

  const auto publisher = root.path() / "publisher";
  git_run(git, root.path(), {"clone"}, {remote.string(), publisher.string()});
  git_run(git, publisher, {"checkout", "-b", "main", "origin/main"});
  commit_file(git, publisher, "remote descendant\n", "remote descendant");
  git_run(git, publisher, {"push", "origin", "main"});
  const auto remote_tip =
      git_stdout(git_run(git, publisher, {"rev-parse", "HEAD"}));
  REQUIRE(
      git_run(git, repo, {"cat-file", "-e"}, {remote_tip}, true).exit_code !=
      0);

  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result ==
        biv::repo::EligibilityResult::unknown_tip);
  CHECK_FALSE(classified->entry.eligibility->proof.has_value());
  CHECK(classified->entry.capture_mode == biv::repo::CaptureMode::full);
  CHECK(git_run(git, repo, {"cat-file", "-e"}, {remote_tip}, true).exit_code !=
        0);
}

TEST_CASE("promisor policy is carried and traced across every later git call") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git = resolved_git([&](const biv::support::SpawnRequest &request) {
    requests.push_back(request);
  });
  TempDir root{"promisor-trace"};
  init_repo(git, root.path());
  git_run(git, root.path(), {"remote", "add"},
          {"origin", (root.path() / "absent.git").string()});
  git_run(git, root.path(), {"config", "remote.origin.promisor", "true"});
  requests.clear();

  auto classified = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(classified.has_value());
  CHECK(classified->entry.promisor);
  const auto detection = std::ranges::find_if(requests, [](const auto
                                                               &request) {
    return request_has_argv(request, "--get-regexp") &&
           request_has_argv(
               request,
               "^(remote\\..*\\.promisor|remote\\..*\\.partialclonefilter)$");
  });
  REQUIRE(detection != requests.end());
  CHECK_FALSE(request_has_env(*detection, "GIT_NO_LAZY_FETCH=1"));
  CHECK(std::ranges::all_of(
      std::next(detection), requests.end(), [](const auto &request) {
        return request_has_env(request, "GIT_NO_LAZY_FETCH=1");
      }));
  requests.clear();

  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");

  REQUIRE(captured.has_value());
  REQUIRE_FALSE(requests.empty());
  CHECK(std::ranges::all_of(requests, [](const auto &request) {
    return request_has_env(request, "GIT_NO_LAZY_FETCH=1");
  }));
  const auto bundle = std::ranges::find_if(requests, [](const auto &request) {
    return request_has_argv(request, "bundle") &&
           request_has_argv(request, "create");
  });
  REQUIRE(bundle != requests.end());
  CHECK(bundle->budgets.probe_wall > std::chrono::seconds{30});
}

TEST_CASE("git exec distinguishes a call budget expiry from git failure") {
  TempDir root{"git-budget-expiry"};
  const auto fake_git = root.path() / "git";
  touch(fake_git, "#!/bin/sh\n/bin/sleep 1\n");
  std::filesystem::permissions(fake_git,
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write |
                                   std::filesystem::perms::owner_exec);
  auto git = biv::repo::Git::resolve(
      [&](const std::string_view name) -> std::optional<std::string> {
        if (name == "PATH") {
          return root.path().string();
        }
        return std::nullopt;
      });
  REQUIRE(git.has_value());

  auto result = biv::repo::invoke_git(
      *git, root.path(), {"status"}, {}, "budget-test",
      biv::repo::GitInvokeOptions{.budget_override =
                                      std::chrono::milliseconds{20}});

  REQUIRE_FALSE(result.has_value());
  REQUIRE(biv::repo::engine_error_kind(result.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::git_budget_expired);
}

TEST_CASE("eligibility selects the remote whose advertisement proves HEAD") {
  auto git = resolved_git();
  TempDir root{"eligibility-select-remote"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto wrong = root.path() / "wrong.git";
  const auto right = root.path() / "right.git";
  std::filesystem::create_directories(wrong);
  std::filesystem::create_directories(right);
  git_run(git, wrong, {"init", "--bare"});
  git_run(git, right, {"init", "--bare"});
  git_run(git, repo, {"remote", "add"}, {"aaa", wrong.string()});
  git_run(git, repo, {"remote", "add"}, {"zzz", right.string()});
  git_run(git, repo, {"push", "zzz", "main"});
  auto classified =
      biv::repo::classify(git, repo, one_repo(root.path(), "repo"));
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.remote == "aaa");

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  REQUIRE(classified->entry.eligibility->proof.has_value());
  CHECK(classified->entry.eligibility->proof->remote == "zzz");
  CHECK(classified->entry.remote == "zzz");
}

TEST_CASE("eligibility bounds an oversized advertisement explicitly") {
  auto git = resolved_git();
  TempDir root{"eligibility-tip-cap"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, repo, remote);
  const auto head = git_stdout(git_run(git, repo, {"rev-parse", "HEAD"}));
  for (std::size_t index = 0; index < 4097U; ++index) {
    touch(remote / "refs/tags" / ("tip-" + std::to_string(index)), head + "\n");
  }
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());

  auto result = biv::repo::run_eligibility(git, classified->entry);

  REQUIRE(result.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  CHECK(classified->entry.eligibility->result ==
        biv::repo::EligibilityResult::unknown_tip);
  CHECK(classified->entry.capture_mode == biv::repo::CaptureMode::full);
}

TEST_CASE("capture writes and verifies a full bundle plus a hostile-ref note") {
  auto git = resolved_git();
  TempDir root{"capture-full"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const std::string hostile_ref = "refs/notes/hidden-\xe2\x80\xae-cba";
  const auto head = git_stdout(git_run(git, repo, {"rev-parse", "HEAD"}));
  git_run(git, repo, {"update-ref", hostile_ref, head});
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());

  auto result =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");

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
  const auto &note =
      std::get<biv::repo::NonCarriedRefsNote>(classified->entry.notes.front());
  REQUIRE(note.refs_p1.size() == 1);
  CHECK(note.refs_p1[0] == "refs/notes/hidden-\\xe2\\x80\\xae-cba");
  CHECK_FALSE(note.omitted_count.has_value());
  REQUIRE(result->advisories.size() == 1);
}

TEST_CASE("capture writes a thin local-ref bundle from advertisement bases") {
  auto git = resolved_git();
  TempDir root{"capture-thin"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, repo, remote);
  git_run(git, repo, {"checkout", "-b", "side"});
  commit_file(git, repo, "side-only\n", "side-only");
  git_run(git, repo, {"checkout", "main"});
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  REQUIRE(classified->entry.capture_mode == biv::repo::CaptureMode::overlay);

  auto result =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");

  REQUIRE(result.has_value());
  REQUIRE(result->artifacts.size() == 1);
  REQUIRE(classified->entry.local_refs_bundle.has_value());
  CHECK_FALSE(classified->entry.bundle.has_value());
  const auto heads =
      git_stdout(git_run(git, repo, {"bundle", "list-heads"},
                         {result->artifacts[0].disk_path.string()}));
  CHECK(heads.find("refs/heads/side") != std::string::npos);

  const auto stage = root.path() / "stage";
  stage_artifacts(*result, stage);
  classified->entry.relpath = "restored";
  auto restored_row = biv::repo::restore_entry(git, classified->entry,
                                               root.path() / "partial", stage);
  const std::string restore_detail =
      restored_row ? "" : restored_row.error().detail;
  INFO(restore_detail);
  REQUIRE(restored_row.has_value());
  const auto restored = root.path() / "partial/restored";
  const auto side =
      std::ranges::find_if(classified->entry.local_refs, [](const auto &ref) {
        return ref.ref == "refs/heads/side";
      });
  REQUIRE(side != classified->entry.local_refs.end());
  CHECK(git_stdout(git_run(git, restored,
                           {"show-ref", "--verify", "--hash=40",
                            "refs/heads/side"})) == side->sha);
}

TEST_CASE(
    "capture discloses stash-only unborn refs without carrying the ref name") {
  auto git = resolved_git();
  TempDir root{"capture-stash-only"};
  init_repo(git, root.path(), false);
  touch(root.path() / "blob", "stash object\n");
  const auto blob =
      git_stdout(git_run(git, root.path(), {"hash-object", "-w"}, {"blob"}));
  git_run(git, root.path(), {"update-ref", "refs/stash", blob});
  auto classified = biv::repo::classify(git, root.path(), one_repo());
  REQUIRE(classified.has_value());
  CHECK(classified->entry.head_state == biv::repo::HeadState::unborn);
  CHECK(classified->entry.local_refs.empty());

  auto result =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");

  REQUIRE(result.has_value());
  REQUIRE(result->artifacts.size() == 1);
  CHECK(classified->entry.notes.empty());
  REQUIRE(result->advisories.size() == 1);
  CHECK(result->advisories[0].find("refs/stash") != std::string::npos);
}

TEST_CASE("capture oracle reports penumbra loss and contamination") {
  auto git = resolved_git();
  TempDir root{"capture-penumbra-oracle"};
  init_repo(git, root.path());
  touch(root.path() / ".gitignore", "*.cache\n");
  git_run(git, root.path(), {"add"}, {".gitignore"});
  git_run(git, root.path(),
          {"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
           "commit", "-m", "ignore cache"});
  touch(root.path() / "old.cache", "old\n");
  auto classified =
      biv::repo::classify(git, root.path(), one_repo(root.path()));
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.engine_source.has_value());
  CHECK(classified->entry.engine_source->penumbra_paths ==
        std::vector<std::filesystem::path>{"old.cache"});
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  REQUIRE(std::filesystem::remove(root.path() / "old.cache"));
  touch(root.path() / "new.cache", "new\n");

  auto result =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");

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
  const auto repo = root.path() / "repo";
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
      biv::repo::capture(git, uncapturable, root.path() / "scratch-ref");
  REQUIRE_FALSE(ref_failure.has_value());
  REQUIRE(biv::repo::engine_error_kind(ref_failure.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(ref_failure.error()) ==
        biv::repo::EngineErrorKind::ref_uncapturable);
  REQUIRE(ref_failure.error().facts.contains("ref"));
  CHECK(ref_failure.error().facts.at("ref") == "refs/heads/not-present");
  CHECK(ref_failure.error().facts.at("repo_relpath") == repo.string());

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
  promisor.promisor = true;
  promisor.engine_source =
      biv::repo::EngineSourceState{.repo_path = repo, .penumbra_paths = {}};
  auto promisor_failure =
      biv::repo::capture(git, promisor, root.path() / "scratch-promisor");
  REQUIRE_FALSE(promisor_failure.has_value());
  REQUIRE(biv::repo::engine_error_kind(promisor_failure.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(promisor_failure.error()) ==
        biv::repo::EngineErrorKind::promisor_objects_unavailable);
}

TEST_CASE("capture maps bundle process failures to git invocation failure") {
  auto git = resolved_git();
  TempDir root{"capture-process-failure"};
  const auto repo = root.path() / "repo";
  init_repo(git, repo);
  auto classified = biv::repo::classify(git, repo, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  const auto scratch = root.path() / "scratch";
  std::filesystem::create_directories(scratch / "repo/repo.bundle");

  auto result = biv::repo::capture(git, classified->entry, scratch);

  REQUIRE_FALSE(result.has_value());
  REQUIRE(biv::repo::engine_error_kind(result.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::git_invocation_failed);
  CHECK(result.error().facts.at("op") == "bundle-create-full");
  CHECK_FALSE(result.error().facts.at("exit_code").empty());
}

TEST_CASE(
    "non-carried-ref writer obeys eligible bounds and sentinel semantics") {
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

  const std::vector<std::string> overlength{"refs/custom/" +
                                            std::string(1013, 'x')};
  auto o3 = biv::repo::build_non_carried_refs_note(overlength);
  REQUIRE(o3.has_value());
  CHECK(o3->refs_p1.empty());
  CHECK(o3->omitted_count == 1);

  const std::vector<std::string> mixed{"refs/custom/z", overlength[0],
                                       "refs/custom/a"};
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

TEST_CASE(
    "restore dispatch leaves zero-ref and shallow payload trees untouched") {
  auto git = resolved_git();
  TempDir root{"restore-payload-branches"};
  const auto partial = root.path() / "partial";
  touch(partial / "empty/payload.txt", "payload\n");
  biv::repo::RepoEntry empty;
  empty.id = "empty";
  empty.relpath = "empty";
  empty.head_state = biv::repo::HeadState::unborn;

  auto payload =
      biv::repo::restore_entry(git, empty, partial, root.path() / "stage");

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
      .boundary = {"0123456789012345678901234567890123456789"}};

  auto pointer =
      biv::repo::restore_entry(git, shallow, partial, root.path() / "stage");

  REQUIRE(pointer.has_value());
  CHECK(pointer->outcome == biv::repo::RepoRestoreOutcome::shallow_pointer);
  REQUIRE(pointer->shallow.has_value());
  CHECK(pointer->sha == shallow.sha);
  CHECK(pointer->shallow->boundary == shallow.shallow->boundary);
  CHECK_FALSE(std::filesystem::exists(partial / "shallow/.git"));
}

TEST_CASE("restore imports unborn object closure without source refs") {
  auto git = resolved_git();
  TempDir root{"restore-unborn-closure"};
  const auto source = root.path() / "source";
  init_repo(git, source, false);
  touch(source / "blob", "object closure\n");
  const auto blob =
      git_stdout(git_run(git, source, {"hash-object", "-w"}, {"blob"}));
  git_run(git, source, {"update-ref", "refs/tags/blob-tag", blob});
  git_run(git, source, {"update-ref", "refs/stash", blob});
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(classified->entry.eligibility.has_value());
  REQUIRE(classified->entry.local_refs.size() == 1);
  CHECK(classified->entry.local_refs[0].ref == "refs/tags/blob-tag");
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path() / "stage";
  stage_artifacts(*captured, stage);
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path() / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  INFO("advisories=" << row->advisories.size());
  REQUIRE(row->local_refs.size() == 1);
  INFO(row->local_refs.front().ref
       << ": " << row->local_refs.front().detail.value_or("ok"));
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  CHECK_FALSE(row->sha.has_value());
  const auto restored = root.path() / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"symbolic-ref", "HEAD"})) ==
        "refs/heads/main");
  const auto tag = git_run(
      git, restored,
      {"show-ref", "--verify", "--hash=40", "refs/tags/blob-tag"}, {}, true);
  const std::string tag_error{
      reinterpret_cast<const char *>(tag.stderr_bytes.data()),
      tag.stderr_bytes.size()};
  INFO(tag_error);
  REQUIRE(tag.exit_code == 0);
  CHECK(git_stdout(tag) == blob);
  CHECK(git_run(git, restored,
                {"show-ref", "--verify", "--hash=40", "refs/stash"}, {}, true)
            .exit_code != 0);
  CHECK(git_run(git, restored, {"cat-file", "-e"}, {blob}).exit_code == 0);
}

TEST_CASE("restore full mode skips exact refs, updates missing refs, and "
          "corrects HEAD") {
  auto git = resolved_git();
  TempDir root{"restore-full-refs"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  git_run(git, source, {"branch", "side"});
  auto classified =
      biv::repo::classify(git, source, one_repo(root.path(), "source"));
  REQUIRE(classified.has_value());
  CHECK(classified->entry.relpath == "source");
  REQUIRE(classified->entry.engine_source.has_value());
  CHECK(classified->entry.engine_source->repo_path == source);
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path() / "stage";
  stage_artifacts(*captured, stage);

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path() / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  REQUIRE(row->local_refs.size() == 2);
  CHECK(std::ranges::any_of(
      row->local_refs, [](const auto &ref) { return ref.skipped_at_sha; }));
  CHECK(std::ranges::any_of(row->local_refs, [](const auto &ref) {
    return ref.recreated && !ref.skipped_at_sha;
  }));
  const auto restored = root.path() / "partial/source";
  CHECK(git_stdout(git_run(git, restored,
                           {"symbolic-ref", "--short", "HEAD"})) == "main");
  for (const auto &ref : classified->entry.local_refs) {
    CHECK(git_stdout(git_run(git, restored,
                             {"show-ref", "--verify", "--hash=40", ref.ref})) ==
          ref.sha);
  }
}

TEST_CASE(
    "restore rejects manifest paths before any filesystem or git effect") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git = resolved_git([&](const biv::support::SpawnRequest &request) {
    requests.push_back(request);
  });
  TempDir root{"restore-containment"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path() / "stage";
  stage_artifacts(*captured, stage);

  classified->entry.relpath = "../escape";
  requests.clear();
  auto relpath_result = biv::repo::restore_entry(
      git, classified->entry, root.path() / "partial", stage);
  REQUIRE_FALSE(relpath_result.has_value());
  CHECK(requests.empty());
  CHECK_FALSE(std::filesystem::exists(root.path() / "escape"));

  classified->entry.relpath = "restored";
  classified->entry.bundle = "../outside.bundle";
  std::filesystem::copy_file(captured->artifacts.front().disk_path,
                             root.path() / "outside.bundle");
  requests.clear();
  auto bundle_result = biv::repo::restore_entry(git, classified->entry,
                                                root.path() / "partial", stage);
  REQUIRE_FALSE(bundle_result.has_value());
  CHECK(requests.empty());
  CHECK_FALSE(std::filesystem::exists(root.path() / "partial/restored"));
}

TEST_CASE("restore rejects invalid object and ref names before spawning git") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git = resolved_git([&](const biv::support::SpawnRequest &request) {
    requests.push_back(request);
  });
  TempDir root{"restore-name-validation"};
  biv::repo::RepoEntry entry;
  entry.id = "repo";
  entry.relpath = "repo";
  entry.sha = "-c";
  entry.branch = "-bad";
  entry.head_state = biv::repo::HeadState::branch;
  entry.capture_mode = biv::repo::CaptureMode::overlay;
  entry.remotes = {biv::repo::Remote{.name = "origin",
                                     .url = "https://example.invalid/r.git"}};
  entry.remote = "origin";
  entry.local_refs = {biv::repo::LocalRef{
      .ref = "-also-bad",
      .sha = "0123456789012345678901234567890123456789",
      .availability = biv::repo::RefAvailability::remote_proven,
      .proof = std::nullopt}};

  auto result = biv::repo::restore_entry(git, entry, root.path() / "partial",
                                         root.path() / "stage");

  REQUIRE_FALSE(result.has_value());
  CHECK(requests.empty());
}

TEST_CASE("restore returns per-ref failures and repo verification divergence") {
  auto git = resolved_git();
  TempDir root{"restore-divergence"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path() / "stage";
  stage_artifacts(*captured, stage);
  classified->entry.relpath = "restored";
  REQUIRE_FALSE(classified->entry.local_refs.empty());
  classified->entry.local_refs.front().sha = std::string(40U, '0');

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path() / "partial", stage);

  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::failed);
  REQUIRE_FALSE(row->local_refs.empty());
  CHECK_FALSE(row->local_refs.front().recreated);
  REQUIRE(row->local_refs.front().detail.has_value());
  CHECK(row->local_refs.front().detail->find("object absent") !=
        std::string::npos);
  CHECK(std::ranges::find(row->advisories, "repo-verify-divergence") !=
        row->advisories.end());
}

TEST_CASE("restore overlay is total with zero captured artifacts") {
  auto git = resolved_git();
  TempDir root{"restore-overlay-zero-artifact"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  const auto remote = init_bare_remote(git, root.path());
  add_remote_and_push(git, source, remote);
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  CHECK(captured->artifacts.empty());
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(
      git, classified->entry, root.path() / "partial", root.path() / "stage");

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  CHECK(row->outcome == biv::repo::RepoRestoreOutcome::restored);
  const auto restored = root.path() / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"rev-parse", "HEAD"})) ==
        *classified->entry.sha);
  CHECK(git_stdout(git_run(git, restored,
                           {"symbolic-ref", "--short", "HEAD"})) == "main");
}

TEST_CASE("restore preserves a detached HEAD") {
  auto git = resolved_git();
  TempDir root{"restore-detached"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  git_run(git, source, {"checkout", "--detach", "HEAD"});
  auto classified = biv::repo::classify(git, source, one_repo());
  REQUIRE(classified.has_value());
  CHECK(classified->entry.head_state == biv::repo::HeadState::detached);
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());
  const auto stage = root.path() / "stage";
  stage_artifacts(*captured, stage);
  classified->entry.relpath = "restored";

  auto row = biv::repo::restore_entry(git, classified->entry,
                                      root.path() / "partial", stage);

  const std::string row_detail = row ? "" : row.error().detail;
  INFO(row_detail);
  REQUIRE(row.has_value());
  const auto restored = root.path() / "partial/restored";
  CHECK(git_stdout(git_run(git, restored, {"rev-parse", "HEAD"})) ==
        *classified->entry.sha);
  CHECK(git_run(git, restored, {"symbolic-ref", "HEAD"}, {}, true).exit_code !=
        0);
}

TEST_CASE("restore materializes a root repo beside the live stage directory") {
  auto git = resolved_git();
  TempDir root{"restore-root-repo"};
  const auto source = root.path() / "source";
  init_repo(git, source);
  auto classified = biv::repo::classify(git, source, one_repo(source));
  REQUIRE(classified.has_value());
  CHECK(classified->entry.relpath == ".");
  REQUIRE(biv::repo::run_eligibility(git, classified->entry).has_value());
  auto captured =
      biv::repo::capture(git, classified->entry, root.path() / "scratch");
  REQUIRE(captured.has_value());

  const auto partial = root.path() / "partial";
  const auto stage = partial / ".biv-stage";
  touch(stage / "keep", "stage remains live\n");
  touch(stage / "repo-materialize-source", "no helper staging slot\n");
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

  auto result = biv::repo::restore_entry(git, entry, root.path() / "partial",
                                         root.path() / "stage");

  REQUIRE_FALSE(result.has_value());
  REQUIRE(biv::repo::engine_error_kind(result.error()).has_value());
  CHECK(*biv::repo::engine_error_kind(result.error()) ==
        biv::repo::EngineErrorKind::repo_restore_failed);
}
