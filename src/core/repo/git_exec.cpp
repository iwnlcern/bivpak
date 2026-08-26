#include "core/repo/git_exec.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <optional>
#include <sstream>
#include <tuple>

namespace biv::repo {
namespace {

UrlDivergenceRun *&active_url_divergence_run() {
  static thread_local UrlDivergenceRun *run = nullptr;
  return run;
}

struct InvocationDetail {
  std::string_view value;
};

struct ParsedEndpoint {
  std::string scheme;
  std::optional<std::string> user;
  std::string host;
  std::optional<std::string> port;
  std::string suffix;
};

std::string ascii_lower(std::string value) {
  std::ranges::transform(value, value.begin(), [](const unsigned char byte) {
    if (byte >= static_cast<unsigned char>('A') &&
        byte <= static_cast<unsigned char>('Z')) {
      return static_cast<char>(byte + ('a' - 'A'));
    }
    return static_cast<char>(byte);
  });
  return value;
}

bool suffixes_equivalent(const std::string_view lhs,
                         const std::string_view rhs) {
  if (lhs == rhs) {
    return true;
  }
  const auto differs_by_one_trailing_slash = [](const std::string_view shorter,
                                                const std::string_view longer) {
    return longer.size() == shorter.size() + 1U && longer.ends_with('/') &&
           longer.starts_with(shorter);
  };
  return differs_by_one_trailing_slash(lhs, rhs) ||
         differs_by_one_trailing_slash(rhs, lhs);
}

bool valid_port(const std::string_view value) {
  if (value.empty()) {
    return false;
  }
  unsigned port = 0U;
  for (const unsigned char byte : value) {
    if (!std::isdigit(byte)) {
      return false;
    }
    port = port * 10U + static_cast<unsigned>(byte - '0');
    if (port > 65535U) {
      return false;
    }
  }
  return true;
}

std::optional<ParsedEndpoint> parse_url(const std::string_view value) {
  const auto separator = value.find("://");
  if (separator == std::string_view::npos || separator == 0U) {
    return std::nullopt;
  }
  if (!std::isalpha(static_cast<unsigned char>(value.front()))) {
    return std::nullopt;
  }
  for (const unsigned char byte : value.substr(1U, separator - 1U)) {
    if (!std::isalnum(byte) && byte != '+' && byte != '-' && byte != '.') {
      return std::nullopt;
    }
  }
  const auto authority_begin = separator + 3U;
  const auto suffix_begin = value.find_first_of("/?#", authority_begin);
  const auto authority =
      value.substr(authority_begin, suffix_begin == std::string_view::npos
                                        ? std::string_view::npos
                                        : suffix_begin - authority_begin);
  if (authority.empty()) {
    return std::nullopt;
  }

  ParsedEndpoint parsed;
  parsed.scheme = ascii_lower(std::string{value.substr(0U, separator)});
  parsed.suffix = suffix_begin == std::string_view::npos
                      ? "/"
                      : std::string{value.substr(suffix_begin)};
  if (parsed.suffix.find_first_of("?#") != std::string::npos) {
    return std::nullopt;
  }
  const auto user_end = authority.rfind('@');
  auto host_port = authority;
  if (user_end != std::string_view::npos) {
    parsed.user = std::string{authority.substr(0U, user_end)};
    host_port.remove_prefix(user_end + 1U);
  }
  if (host_port.empty()) {
    return std::nullopt;
  }
  if (host_port.front() == '[') {
    const auto bracket = host_port.find(']');
    if (bracket == std::string_view::npos) {
      return std::nullopt;
    }
    parsed.host = ascii_lower(std::string{host_port.substr(0U, bracket + 1U)});
    if (bracket + 1U < host_port.size()) {
      if (host_port.at(bracket + 1U) != ':' ||
          bracket + 2U == host_port.size()) {
        return std::nullopt;
      }
      parsed.port = std::string{host_port.substr(bracket + 2U)};
    }
  } else {
    const auto colon = host_port.rfind(':');
    if (colon != std::string_view::npos) {
      if (colon == 0U || colon + 1U == host_port.size()) {
        return std::nullopt;
      }
      parsed.port = std::string{host_port.substr(colon + 1U)};
      host_port = host_port.substr(0U, colon);
    }
    parsed.host = ascii_lower(std::string{host_port});
  }
  if (parsed.host.empty()) {
    return std::nullopt;
  }
  if (parsed.port && !valid_port(*parsed.port)) {
    return std::nullopt;
  }
  if ((parsed.scheme == "https" && parsed.port == "443") ||
      (parsed.scheme == "http" && parsed.port == "80")) {
    parsed.port.reset();
  }
  return parsed;
}

std::optional<ParsedEndpoint> parse_absolute_scp(const std::string_view value) {
  const auto colon = value.find(':');
  if (colon == std::string_view::npos || colon == 0U ||
      colon + 1U >= value.size() || value.at(colon + 1U) != '/') {
    return std::nullopt;
  }
  const auto authority = value.substr(0U, colon);
  const auto at = authority.find('@');
  ParsedEndpoint parsed;
  parsed.scheme = "ssh";
  if (at == std::string_view::npos) {
    parsed.host = ascii_lower(std::string{authority});
  } else {
    if (at == 0U || at + 1U == authority.size() ||
        authority.find('@', at + 1U) != std::string_view::npos) {
      return std::nullopt;
    }
    parsed.user = std::string{authority.substr(0U, at)};
    parsed.host = ascii_lower(std::string{authority.substr(at + 1U)});
  }
  parsed.suffix = std::string{value.substr(colon + 1U)};
  return parsed;
}

bool same_endpoint(const ParsedEndpoint &lhs, const ParsedEndpoint &rhs) {
  return lhs.scheme == rhs.scheme && lhs.user == rhs.user &&
         lhs.host == rhs.host && lhs.port == rhs.port &&
         suffixes_equivalent(lhs.suffix, rhs.suffix);
}

std::chrono::milliseconds budget_for(const GitCallClass call_class) {
  switch (call_class) {
  case GitCallClass::local:
    return std::chrono::seconds{30};
  case GitCallClass::network:
    return std::chrono::minutes{2};
  case GitCallClass::bundle:
    return std::chrono::minutes{5};
  }
  return std::chrono::seconds{30};
}

BivError invocation_error(const EngineErrorKind kind,
                          const std::filesystem::path &repo,
                          const std::string_view operation,
                          const InvocationDetail detail,
                          const std::optional<int> exit_code = std::nullopt) {
  auto error = make_engine_error(kind, repo, std::string{detail.value});
  error.facts.emplace("op", operation);
  if (exit_code) {
    error.facts.emplace("exit_code", std::to_string(*exit_code));
  }
  return error;
}

void append_nul_paths(const std::string &output,
                      std::vector<std::filesystem::path> &paths) {
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\0', cursor);
    if (end != cursor) {
      paths.emplace_back(output.substr(cursor, end - cursor));
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
}

} // namespace

ScopedUrlDivergenceRun::ScopedUrlDivergenceRun(UrlDivergenceRun &run) noexcept
    : previous_{active_url_divergence_run()} {
  active_url_divergence_run() = &run;
}

ScopedUrlDivergenceRun::~ScopedUrlDivergenceRun() {
  active_url_divergence_run() = previous_;
}

bool url_endpoints_equivalent(const std::string_view requested,
                              const std::string_view effective) {
  if (requested == effective) {
    return true;
  }
  const auto requested_url = parse_url(requested);
  const auto effective_url = parse_url(effective);
  if (requested_url && effective_url) {
    return same_endpoint(*requested_url, *effective_url);
  }
  const auto requested_scp = parse_absolute_scp(requested);
  const auto effective_scp = parse_absolute_scp(effective);
  if (requested_scp && effective_url) {
    return same_endpoint(*requested_scp, *effective_url) &&
           effective_url->scheme == "ssh" && !effective_url->port;
  }
  if (requested_url && effective_scp) {
    return same_endpoint(*requested_url, *effective_scp) &&
           requested_url->scheme == "ssh" && !requested_url->port;
  }
  return false;
}

expected<support::SpawnResult>
invoke_git(const Git &git, const std::filesystem::path &repo,
           const std::span<const std::string> args,
           const std::span<const std::string> operands,
           const std::string_view operation, const GitInvokeOptions options) {
  Git::Opts git_options;
  git_options.cwd = repo;
  git_options.no_lazy_fetch = options.promisor;
  git_options.isolate_global_config = options.restore;
  git_options.allow_user_protocol = options.allow_user_protocol;
  git_options.empty_config_keys.assign(options.empty_config_keys.begin(),
                                       options.empty_config_keys.end());
  git_options.budget =
      options.budget_override.value_or(budget_for(options.call_class));
  if (options.call_class == GitCallClass::network) {
    if (options.requested_endpoints.size() != 1U) {
      return std::unexpected(invocation_error(
          EngineErrorKind::git_invocation_failed, repo, operation,
          InvocationDetail{"network-endpoint-carrier"}));
    }
    const auto &requested = options.requested_endpoints.front();
    auto resolved =
        git.run({"ls-remote", "--get-url"}, {requested}, git_options);
    if (!resolved || resolved->timed_out || resolved->spawn_failed ||
        resolved->io_failed || resolved->output_incomplete ||
        resolved->exit_code != 0) {
      return std::unexpected(invocation_error(
          EngineErrorKind::git_invocation_failed, repo, operation,
          InvocationDetail{"network endpoint resolution failed"}));
    }
    const auto effective = trim_git_newline(git_bytes(resolved->stdout_bytes));
    if (effective.empty()) {
      return std::unexpected(invocation_error(
          EngineErrorKind::git_invocation_failed, repo, operation,
          InvocationDetail{"network endpoint resolution failed"}));
    }
    if (!url_endpoints_equivalent(requested, effective)) {
      UrlDivergence event{.requested = requested,
                          .effective = effective,
                          .operation = std::string{operation},
                          .repo = repo};
      const auto key =
          std::tuple{event.requested, event.effective, event.repo.string()};
      auto decision = UrlDivergenceDecision::refuse;
      auto first_decision = true;
      if (active_url_divergence_run()) {
        if (const auto found = active_url_divergence_run()->decisions.find(key);
            found != active_url_divergence_run()->decisions.end()) {
          decision = found->second;
          first_decision = false;
        } else {
          if (active_url_divergence_run()->hook) {
            decision = active_url_divergence_run()->hook(event);
          }
          active_url_divergence_run()->decisions.emplace(key, decision);
        }
      }
      if (decision == UrlDivergenceDecision::refuse) {
        if (active_url_divergence_run() && first_decision) {
          active_url_divergence_run()->refused.push_back(event);
        }
        auto error = invocation_error(
            EngineErrorKind::url_divergence_refused, repo, operation,
            InvocationDetail{"network endpoint approval refused"});
        error.facts.emplace("requested", requested);
        error.facts.emplace("effective", effective);
        return std::unexpected(std::move(error));
      }
      if (active_url_divergence_run() && first_decision) {
        active_url_divergence_run()->accepted.push_back(std::move(event));
      }
    }
  }
  auto result = git.run(args, operands, git_options);
  if (!result) {
    return std::unexpected(invocation_error(
        EngineErrorKind::git_invocation_failed, repo, operation,
        InvocationDetail{"git subprocess failed: " + result.error().detail}));
  }
  if (result->timed_out) {
    return std::unexpected(
        invocation_error(EngineErrorKind::git_budget_expired, repo, operation,
                         InvocationDetail{"git call budget expired"}));
  }
  if (result->spawn_failed || result->io_failed || result->output_incomplete) {
    return std::unexpected(invocation_error(
        EngineErrorKind::git_invocation_failed, repo, operation,
        InvocationDetail{"git subprocess transport failed"}));
  }
  if (options.promisor && result->exit_code != 0 &&
      missing_object_failure(*result)) {
    return std::unexpected(invocation_error(
        EngineErrorKind::promisor_objects_unavailable, repo, operation,
        InvocationDetail{"promisor object unavailable"}, result->exit_code));
  }
  return result;
}

expected<std::vector<std::string>>
repo_local_command_config_keys(const Git &git,
                               const std::filesystem::path &repo) {
  static constexpr std::string_view kCommandKeyPattern =
      R"(^(filter\..*\.(clean|smudge|process)|diff\..*\.(command|textconv)|merge\..*\.driver)$)";
  std::vector<std::string> keys;
  const auto collect = [&](const std::string_view scope) -> expected<void> {
    auto defined = invoke_git(git, repo,
                              {"config", std::string{scope}, "--includes",
                               "--null", "--name-only", "--get-regexp",
                               std::string{kCommandKeyPattern}},
                              {}, "config-command-drivers");
    if (!defined) {
      return std::unexpected(defined.error());
    }
    if (defined->exit_code == 1) {
      return {};
    }
    if (scope == "--worktree" && defined->exit_code == 128) {
      const auto detail = git_bytes(defined->stderr_bytes);
      if (detail.find(
              "--worktree cannot be used with multiple working trees unless") !=
              std::string::npos &&
          detail.find("worktreeConfig is enabled") != std::string::npos) {
        return {};
      }
    }
    if (defined->exit_code != 0) {
      return std::unexpected(git_invocation_failure(
          repo, "config-command-drivers", defined->exit_code,
          "git config command-driver enumeration failed"));
    }

    const auto output = git_bytes(defined->stdout_bytes);
    std::size_t cursor = 0;
    while (cursor < output.size()) {
      const auto end = output.find('\0', cursor);
      if (end == std::string::npos) {
        break;
      }
      if (end != cursor) {
        keys.emplace_back(output.substr(cursor, end - cursor));
      }
      cursor = end + 1U;
    }
    return {};
  };

  if (auto local = collect("--local"); !local) {
    return std::unexpected(local.error());
  }
  if (auto worktree = collect("--worktree"); !worktree) {
    return std::unexpected(worktree.error());
  }
  std::ranges::sort(keys);
  keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
  return keys;
}

BivError git_invocation_failure(const std::filesystem::path &repo,
                                const std::string_view operation,
                                const int exit_code,
                                const std::string_view detail) {
  return invocation_error(EngineErrorKind::git_invocation_failed, repo,
                          operation, InvocationDetail{detail}, exit_code);
}

std::string git_bytes(const std::vector<std::byte> &value) {
  std::string output;
  output.reserve(value.size());
  std::ranges::transform(
      value, std::back_inserter(output), [](const auto byte) {
        return static_cast<char>(std::to_integer<unsigned char>(byte));
      });
  return output;
}

std::string trim_git_newline(std::string value) {
  while (!value.empty() && (value.back() == '\n' || value.back() == '\r')) {
    value.pop_back();
  }
  return value;
}

std::string git_checked_at_now() {
  const auto now = std::chrono::system_clock::now();
  const auto value = std::chrono::system_clock::to_time_t(now);
  std::tm utc{};
  if (::gmtime_r(&value, &utc) == nullptr) {
    return "1970-01-01T00:00:00Z";
  }
  std::ostringstream output;
  output << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ");
  return output.str();
}

bool promisor_config_enabled(const std::string_view output) {
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\n', cursor);
    const auto row = output.substr(cursor, end - cursor);
    const auto separator = row.find_first_of(" \t");
    if (separator != std::string_view::npos) {
      const auto key = row.substr(0U, separator);
      const auto value = row.substr(separator + 1U);
      if (key.ends_with(".partialclonefilter") ||
          (key.ends_with(".promisor") && (value == "true" || value == "yes" ||
                                          value == "on" || value == "1"))) {
        return true;
      }
    }
    if (end == std::string_view::npos) {
      break;
    }
    cursor = end + 1U;
  }
  return false;
}

bool missing_object_failure(const support::SpawnResult &result) {
  // LC_ALL=C in Git::resolve makes these porcelain diagnostics stable.
  const auto detail =
      git_bytes(result.stderr_bytes) + git_bytes(result.stdout_bytes);
  return detail.find("missing object") != std::string::npos ||
         detail.find("missing blob") != std::string::npos ||
         detail.find("missing tree") != std::string::npos ||
         detail.find("missing commit") != std::string::npos ||
         detail.find("missing prerequisite") != std::string::npos ||
         detail.find("unable to read") != std::string::npos ||
         detail.find("bad object") != std::string::npos ||
         detail.find("invalid object") != std::string::npos ||
         detail.find("could not get object info") != std::string::npos;
}

expected<std::vector<std::filesystem::path>>
snapshot_penumbra(const Git &git, const std::filesystem::path &repo,
                  const GitInvokeOptions options) {
  std::vector<std::filesystem::path> paths;
  for (const auto &args :
       {std::vector<std::string>{"ls-files", "--others", "--exclude-standard",
                                 "-z"},
        std::vector<std::string>{"ls-files", "--others", "--ignored",
                                 "--exclude-standard", "-z"}}) {
    auto listed = invoke_git(git, repo, args, {}, "ls-files-penumbra", options);
    if (!listed) {
      return std::unexpected(listed.error());
    }
    if (listed->exit_code != 0) {
      return std::unexpected(invocation_error(
          EngineErrorKind::git_invocation_failed, repo, "ls-files-penumbra",
          InvocationDetail{"git ls-files penumbra failed"}, listed->exit_code));
    }
    append_nul_paths(git_bytes(listed->stdout_bytes), paths);
  }
  std::ranges::sort(paths);
  paths.erase(std::unique(paths.begin(), paths.end()), paths.end());
  return paths;
}

bool valid_object_id(const std::string_view value) noexcept {
  if (value.size() != 40U && value.size() != 64U) {
    return false;
  }
  return std::ranges::all_of(
      value, [](const unsigned char byte) { return std::isxdigit(byte) != 0; });
}

bool valid_ref_name(const std::string_view value) noexcept {
  if (!value.starts_with("refs/") || value.ends_with('/') ||
      value.ends_with('.') || value.find("..") != std::string_view::npos ||
      value.find("@{") != std::string_view::npos ||
      value.find("//") != std::string_view::npos) {
    return false;
  }
  for (const unsigned char byte : value) {
    if (byte <= 0x20U || byte == 0x7fU || byte == '~' || byte == '^' ||
        byte == ':' || byte == '?' || byte == '*' || byte == '[' ||
        byte == '\\') {
      return false;
    }
  }
  std::size_t cursor = 0;
  while (cursor < value.size()) {
    const auto end = value.find('/', cursor);
    const auto part = value.substr(cursor, end - cursor);
    if (part.empty() || part.front() == '.' || part.ends_with(".lock")) {
      return false;
    }
    if (end == std::string_view::npos) {
      break;
    }
    cursor = end + 1U;
  }
  return true;
}

bool valid_manifest_path(const std::filesystem::path &value,
                         const bool allow_dot) noexcept {
  if (value.empty() || value.is_absolute() || value.has_root_name() ||
      value.has_root_directory()) {
    return false;
  }
  const auto normalized = value.lexically_normal();
  if (normalized != value || (!allow_dot && normalized == ".")) {
    return false;
  }
  return std::ranges::none_of(
      value, [](const auto &component) { return component == ".."; });
}

} // namespace biv::repo
