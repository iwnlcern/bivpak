#include "core/repo/git_exec.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <sstream>

namespace biv::repo {
namespace {

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
                          const std::filesystem::path& repo,
                          const std::string_view operation,
                          const std::string_view detail,
                          const std::optional<int> exit_code = std::nullopt) {
  auto error = make_engine_error(kind, repo, std::string{detail});
  error.facts.emplace("op", operation);
  if (exit_code) {
    error.facts.emplace("exit_code", std::to_string(*exit_code));
  }
  return error;
}

void append_nul_paths(const std::string& output,
                      std::vector<std::filesystem::path>& paths) {
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

}  // namespace

expected<support::SpawnResult> invoke_git(
    const Git& git, const std::filesystem::path& repo,
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
  auto result = git.run(args, operands, git_options);
  if (!result) {
    return std::unexpected(invocation_error(
        EngineErrorKind::git_invocation_failed, repo, operation,
        "git subprocess failed: " + result.error().detail));
  }
  if (result->timed_out) {
    return std::unexpected(invocation_error(EngineErrorKind::git_budget_expired,
                                            repo, operation,
                                            "git call budget expired"));
  }
  if (result->spawn_failed || result->io_failed || result->output_incomplete) {
    return std::unexpected(
        invocation_error(EngineErrorKind::git_invocation_failed, repo,
                         operation, "git subprocess transport failed"));
  }
  if (options.promisor && result->exit_code != 0 &&
      missing_object_failure(*result)) {
    return std::unexpected(invocation_error(
        EngineErrorKind::promisor_objects_unavailable, repo, operation,
        "promisor object unavailable", result->exit_code));
  }
  return result;
}

expected<std::vector<std::string>> repo_local_command_config_keys(
    const Git& git, const std::filesystem::path& repo) {
  static constexpr std::string_view kCommandKeyPattern =
      R"(^(filter\..*\.(clean|smudge|process)|diff\..*\.(command|textconv)|merge\..*\.driver)$)";
  std::vector<std::string> keys;
  const auto collect = [&](const std::string_view scope) -> expected<void> {
    auto defined = invoke_git(
        git, repo,
        {"config", std::string{scope}, "--includes", "--null", "--name-only",
         "--get-regexp", std::string{kCommandKeyPattern}},
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

BivError git_invocation_failure(const std::filesystem::path& repo,
                                const std::string_view operation,
                                const int exit_code,
                                const std::string_view detail) {
  return invocation_error(EngineErrorKind::git_invocation_failed, repo,
                          operation, detail, exit_code);
}

std::string git_bytes(const std::vector<std::byte>& value) {
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

bool missing_object_failure(const support::SpawnResult& result) {
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

expected<std::vector<std::filesystem::path>> snapshot_penumbra(
    const Git& git, const std::filesystem::path& repo,
    const GitInvokeOptions options) {
  std::vector<std::filesystem::path> paths;
  for (const auto& args :
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
          "git ls-files penumbra failed", listed->exit_code));
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

bool valid_manifest_path(const std::filesystem::path& value,
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
      value, [](const auto& component) { return component == ".."; });
}

}  // namespace biv::repo
