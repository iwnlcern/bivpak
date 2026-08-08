#pragma once

#include <chrono>
#include <filesystem>
#include <initializer_list>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "core/repo/git.hpp"
#include "core/repo/types.hpp"

namespace biv::repo {

enum class GitCallClass { local, network, bundle };

struct GitInvokeOptions {
  bool promisor{false};
  bool restore{false};
  bool allow_user_protocol{false};
  GitCallClass call_class{GitCallClass::local};
  std::optional<std::chrono::milliseconds> budget_override;
  std::span<const std::string> empty_config_keys;
};

expected<support::SpawnResult> invoke_git(const Git& git,
                                          const std::filesystem::path& repo,
                                          std::span<const std::string> args,
                                          std::span<const std::string> operands,
                                          std::string_view operation,
                                          GitInvokeOptions options = {});

inline expected<support::SpawnResult> invoke_git(
    const Git& git, const std::filesystem::path& repo,
    std::initializer_list<std::string> args,
    std::initializer_list<std::string> operands,
    const std::string_view operation, const GitInvokeOptions options = {}) {
  return invoke_git(
      git, repo, std::span<const std::string>{args.begin(), args.size()},
      std::span<const std::string>{operands.begin(), operands.size()},
      operation, options);
}

BivError git_invocation_failure(const std::filesystem::path& repo,
                                std::string_view operation, int exit_code,
                                std::string_view detail);

std::string git_bytes(const std::vector<std::byte>& value);
std::string trim_git_newline(std::string value);
std::string git_checked_at_now();
bool promisor_config_enabled(std::string_view output);
bool missing_object_failure(const support::SpawnResult& result);

expected<std::vector<std::string>> repo_local_command_config_keys(
    const Git& git, const std::filesystem::path& repo);

expected<std::vector<std::filesystem::path>> snapshot_penumbra(
    const Git& git, const std::filesystem::path& repo,
    GitInvokeOptions options = {});

bool valid_object_id(std::string_view value) noexcept;
bool valid_ref_name(std::string_view value) noexcept;
bool valid_manifest_path(const std::filesystem::path& value,
                         bool allow_dot = false) noexcept;

}  // namespace biv::repo
