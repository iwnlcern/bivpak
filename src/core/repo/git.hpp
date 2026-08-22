#pragma once

#include <chrono>
#include <filesystem>
#include <initializer_list>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "core/support/subprocess.hpp"

namespace biv::repo {

class Git {
 public:
  struct Opts {
    std::optional<std::filesystem::path> cwd;
    bool no_lazy_fetch{false};
    bool isolate_global_config{false};
    std::vector<std::string> empty_config_keys{};
    support::StderrMode stderr_mode{support::StderrMode::separate};
    std::optional<std::filesystem::path> stdout_file;
    std::chrono::milliseconds budget{std::chrono::seconds{30}};
  };

  static expected<Git> resolve(const support::Getenv& getenv);

  [[nodiscard]] const std::filesystem::path& executable() const noexcept {
    return executable_;
  }

  expected<support::SpawnResult> run(
      std::span<const std::string> args,
      std::span<const std::string> operands, const Opts& opts) const;

  expected<support::SpawnResult> run(
      std::initializer_list<std::string> args,
      std::initializer_list<std::string> operands, const Opts& opts) const {
    return run(std::span<const std::string>{args.begin(), args.size()},
               std::span<const std::string>{operands.begin(), operands.size()},
               opts);
  }

 private:
  Git(std::filesystem::path executable, std::vector<std::string> base_env)
      : executable_{std::move(executable)}, base_env_{std::move(base_env)} {}

  [[nodiscard]] support::SpawnRequest build_spawn_request(
      std::span<const std::string> args,
      std::span<const std::string> operands, const Opts& opts) const;

  std::filesystem::path executable_;
  std::vector<std::string> base_env_;

#if defined(BIV_REPO_TESTING)
  friend support::SpawnRequest git_testing_build_spawn_request(
      const Git&, std::span<const std::string>,
      std::span<const std::string>, const Opts&);
#endif
};

#if defined(BIV_REPO_TESTING)
support::SpawnRequest git_testing_build_spawn_request(
    const Git& git, std::span<const std::string> args,
    std::span<const std::string> operands, const Git::Opts& opts);

namespace git_testing {

inline support::SpawnRequest build_spawn_request(
    const Git& git, std::span<const std::string> args,
    std::span<const std::string> operands, const Git::Opts& opts) {
  return git_testing_build_spawn_request(git, args, operands, opts);
}

inline support::SpawnRequest build_spawn_request(
    const Git& git, std::initializer_list<std::string> args,
    std::initializer_list<std::string> operands, const Git::Opts& opts) {
  return build_spawn_request(
      git, std::span<const std::string>{args.begin(), args.size()},
      std::span<const std::string>{operands.begin(), operands.size()}, opts);
}

}  // namespace git_testing
#endif

}  // namespace biv::repo
