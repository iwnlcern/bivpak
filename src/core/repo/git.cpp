#include "core/repo/git.hpp"

#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <string_view>
#include <utility>

namespace biv::repo {

namespace {

constexpr std::size_t kCaptureCap = std::size_t{16} * 1024U * 1024U;

BivError resolve_error(const std::string_view detail, const int err_no = 0) {
  return BivError{ErrKind::InternalError, "git", std::string{detail}, err_no};
}

std::optional<std::filesystem::path> resolve_from_path(
    const std::string& path_value) {
  std::size_t begin = 0;
  while (begin <= path_value.size()) {
    const auto end = path_value.find(':', begin);
    const auto component = path_value.substr(
        begin, end == std::string::npos ? std::string::npos : end - begin);
    const auto directory = component.empty() ? std::filesystem::path{"."}
                                             : std::filesystem::path{component};
    const auto candidate = directory / "git";
    std::error_code status_error;
    if (std::filesystem::is_regular_file(candidate, status_error) &&
        !status_error && ::access(candidate.c_str(), X_OK) == 0) {
      std::error_code canonical_error;
      auto resolved = std::filesystem::canonical(candidate, canonical_error);
      if (!canonical_error && resolved.is_absolute()) {
        return resolved;
      }
    }
    if (end == std::string::npos) {
      break;
    }
    begin = end + 1U;
  }
  return std::nullopt;
}

void append_if_present(std::vector<std::string>& env,
                       const support::Getenv& getenv,
                       const std::string_view name) {
  if (const auto value = getenv(name)) {
    env.emplace_back(std::string{name} + "=" + *value);
  }
}

}  // namespace

expected<Git> Git::resolve(const support::Getenv& getenv) {
  if (!getenv) {
    return std::unexpected(resolve_error("git resolver missing environment"));
  }
  const auto path_value = getenv("PATH");
  if (!path_value) {
    return std::unexpected(resolve_error("PATH is unavailable"));
  }
  auto executable = resolve_from_path(*path_value);
  if (!executable) {
    return std::unexpected(resolve_error("git executable not found", ENOENT));
  }

  std::vector<std::string> env;
  env.reserve(18U);
  env.emplace_back("PATH=" + *path_value);
  append_if_present(env, getenv, "HOME");
  append_if_present(env, getenv, "TMPDIR");
  env.emplace_back("GIT_TERMINAL_PROMPT=0");
  env.emplace_back("GIT_PROTOCOL_FROM_USER=0");
  env.emplace_back("LC_ALL=C");
  env.emplace_back("GIT_CONFIG_NOSYSTEM=1");
  env.emplace_back("GIT_CONFIG_COUNT=3");
  env.emplace_back("GIT_CONFIG_KEY_0=core.hooksPath");
  env.emplace_back("GIT_CONFIG_VALUE_0=/dev/null");
  env.emplace_back("GIT_CONFIG_KEY_1=credential.helper");
  env.emplace_back("GIT_CONFIG_VALUE_1=");
  env.emplace_back("GIT_CONFIG_KEY_2=core.sshCommand");
  env.emplace_back("GIT_CONFIG_VALUE_2=/usr/bin/false");
  env.emplace_back("GIT_ASKPASS=/usr/bin/false");
  env.emplace_back("SSH_ASKPASS=/usr/bin/false");
  return Git{std::move(*executable), std::move(env)};
}

support::SpawnRequest Git::build_spawn_request(
    const std::span<const std::string> args,
    const std::span<const std::string> operands, const Opts& opts) const {
  std::vector<std::string> argv;
  argv.reserve(1U + (opts.cwd ? 2U : 0U) + args.size() +
               (operands.empty() ? 0U : 1U + operands.size()));
  argv.emplace_back(executable_.string());
  if (opts.cwd) {
    argv.emplace_back("-C");
    argv.emplace_back(opts.cwd->string());
  }
  argv.insert(argv.end(), args.begin(), args.end());
  if (!operands.empty()) {
    argv.emplace_back("--");
    argv.insert(argv.end(), operands.begin(), operands.end());
  }

  auto env = base_env_;
  if (opts.isolate_global_config) {
    env.emplace_back("GIT_CONFIG_GLOBAL=/dev/null");
  }
  if (opts.no_lazy_fetch) {
    env.emplace_back("GIT_NO_LAZY_FETCH=1");
  }

  auto budgets = support::ProbeBudgets{};
  budgets.probe_wall = opts.budget;
  return support::SpawnRequest{
      .executable = executable_,
      .argv = std::move(argv),
      .env = std::move(env),
      .stderr_mode = opts.stderr_mode,
      .stdout_file = opts.stdout_file,
      .stdout_cap = kCaptureCap,
      .stderr_cap = kCaptureCap,
      .budgets = budgets};
}

expected<support::SpawnResult> Git::run(
    const std::span<const std::string> args,
    const std::span<const std::string> operands, const Opts& opts) const {
  return support::run_argv(build_spawn_request(args, operands, opts));
}

#if defined(BIV_REPO_TESTING)
support::SpawnRequest git_testing_build_spawn_request(
    const Git& git, const std::span<const std::string> args,
    const std::span<const std::string> operands, const Git::Opts& opts) {
  return git.build_spawn_request(args, operands, opts);
}
#endif

}  // namespace biv::repo
