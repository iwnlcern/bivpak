#include "core/repo/classify.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string_view>

#include "core/repo/git_exec.hpp"

namespace biv::repo {
namespace {

BivError command_error(const std::filesystem::path& repo,
                       const std::string_view operation) {
  return make_engine_error(
      EngineErrorKind::git_invocation_failed, repo,
      "repo classification git invocation failed: " + std::string{operation});
}

std::vector<std::pair<std::string, std::string>> parse_ref_pairs(
    const std::string& output) {
  std::vector<std::pair<std::string, std::string>> refs;
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto name_end = output.find('\0', cursor);
    if (name_end == std::string::npos) {
      break;
    }
    const auto sha_end = output.find('\0', name_end + 1U);
    if (sha_end == std::string::npos) {
      break;
    }
    auto name = output.substr(cursor, name_end - cursor);
    while (!name.empty() && (name.front() == '\n' || name.front() == '\r')) {
      name.erase(name.begin());
    }
    refs.emplace_back(std::move(name),
                      output.substr(name_end + 1U, sha_end - name_end - 1U));
    cursor = sha_end + 1U;
  }
  return refs;
}

std::optional<std::filesystem::path> first_gitlink_path(
    const std::string& output) {
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\0', cursor);
    const auto row = output.substr(cursor, end - cursor);
    const auto tab = row.find('\t');
    if (row.starts_with("160000 ") && tab != std::string::npos) {
      return std::filesystem::path{row.substr(tab + 1U)};
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  return std::nullopt;
}

expected<void> record_penumbra(const Git& git, EngineSourceState& source_state,
                               const bool promisor,
                               const std::filesystem::path& repo,
                               const std::span<const std::string>
                                   empty_config_keys) {
  auto snapshot = snapshot_penumbra(
      git, repo,
      GitInvokeOptions{.promisor = promisor,
                       .empty_config_keys = empty_config_keys});
  if (!snapshot) {
    return std::unexpected(snapshot.error());
  }
  source_state.penumbra_paths = std::move(*snapshot);
  return {};
}

}  // namespace

expected<Classification> classify(const Git& git,
                                  const std::filesystem::path& repo,
                                  const Discovery& discovery) {
  Classification result;
  result.entry.id = repo.filename().string();
  auto& source_state = result.entry.engine_source.emplace();
  source_state.repo_path = repo;
  if (!discovery.root.empty()) {
    std::error_code relative_error;
    result.entry.relpath =
        std::filesystem::relative(repo, discovery.root, relative_error);
    if (relative_error) {
      return std::unexpected(make_engine_error(
          EngineErrorKind::git_invocation_failed, repo,
          "repo classification could not derive relative path"));
    }
  } else if (discovery.repos.size() == 1U) {
    result.entry.relpath = discovery.repos.front().relpath;
  } else {
    result.entry.relpath = repo.filename();
  }

  auto command_config_keys = repo_local_command_config_keys(git, repo);
  if (!command_config_keys) {
    return std::unexpected(command_config_keys.error());
  }
  source_state.neutralized_git_config_keys = std::move(*command_config_keys);
  const auto invoke_classify = [&](std::vector<std::string> args,
                                   const bool no_lazy_fetch = false) {
    const auto operation = args.empty() ? std::string{"git"} : args.front();
    return invoke_git(
        git, repo, args, {}, operation,
        GitInvokeOptions{
            .promisor = no_lazy_fetch,
            .empty_config_keys = source_state.neutralized_git_config_keys});
  };

  auto promisor =
      invoke_classify(
          {"config", "--get-regexp",
           "^(remote\\..*\\.promisor|remote\\..*\\.partialclonefilter)$"});
  if (!promisor) {
    return std::unexpected(promisor.error());
  }
  result.entry.promisor =
      promisor->exit_code == 0 &&
      promisor_config_enabled(git_bytes(promisor->stdout_bytes));

  auto index = invoke_classify({"ls-files", "-s", "-z"}, result.entry.promisor);
  if (!index || index->exit_code != 0) {
    return std::unexpected(index ? command_error(repo, "ls-files -s")
                                 : index.error());
  }
  if (const auto gitlink = first_gitlink_path(git_bytes(index->stdout_bytes))) {
    result.fence = Classification::Fence::submodule;
    result.issue =
        EngineIssue{.kind = EngineErrorKind::repo_submodule_unsupported,
                    .paths = {*gitlink},
                    .detail = {}};
    return result;
  }

  const auto nested = std::ranges::find_if(
      discovery.repos,
      [](const auto& boundary) { return boundary.kind == RepoKind::nested; });
  if (nested != discovery.repos.end()) {
    result.fence = Classification::Fence::nested;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_nested_unsupported,
                               .paths = {nested->relpath},
                               .detail = {}};
    return result;
  }

  auto unmerged =
      invoke_classify({"ls-files", "-u", "-z"}, result.entry.promisor);
  if (!unmerged) {
    return std::unexpected(unmerged.error());
  }
  if (unmerged->exit_code != 0) {
    return std::unexpected(command_error(repo, "ls-files -u"));
  }
  const auto unmerged_output = git_bytes(unmerged->stdout_bytes);
  if (!unmerged_output.empty()) {
    std::vector<std::filesystem::path> paths;
    std::size_t cursor = 0;
    while (cursor < unmerged_output.size()) {
      const auto end = unmerged_output.find('\0', cursor);
      const auto row = unmerged_output.substr(cursor, end - cursor);
      const auto tab = row.find('\t');
      if (tab != std::string::npos) {
        paths.emplace_back(row.substr(tab + 1U));
      }
      if (end == std::string::npos) {
        break;
      }
      cursor = end + 1U;
    }
    std::ranges::sort(paths);
    paths.erase(std::unique(paths.begin(), paths.end()), paths.end());
    result.fence = Classification::Fence::unmerged;
    result.issue =
        EngineIssue{.kind = EngineErrorKind::unmerged_index_unrepresentable,
                    .paths = std::move(paths),
                    .detail = {}};
    return result;
  }

  auto head = invoke_classify({"rev-parse", "--verify", "HEAD"},
                              result.entry.promisor);
  if (!head) {
    return std::unexpected(head.error());
  }
  auto refs = invoke_classify(
      {"for-each-ref", "--format=%(refname)%00%(objectname)%00"},
      result.entry.promisor);
  if (!refs || refs->exit_code != 0) {
    return std::unexpected(refs ? command_error(repo, "for-each-ref")
                                : refs.error());
  }
  const auto ref_pairs = parse_ref_pairs(git_bytes(refs->stdout_bytes));
  auto shallow = invoke_classify({"rev-parse", "--is-shallow-repository"},
                                 result.entry.promisor);
  if (!shallow || shallow->exit_code != 0) {
    return std::unexpected(shallow ? command_error(repo, "is-shallow")
                                   : shallow.error());
  }
  if (trim_git_newline(git_bytes(shallow->stdout_bytes)) == "true") {
    Shallow metadata{.boundary = {}};
    const auto shallow_file = repo / ".git/shallow";
    std::ifstream input{shallow_file};
    std::string boundary;
    while (std::getline(input, boundary)) {
      if (!boundary.empty()) {
        metadata.boundary.push_back(boundary);
      }
    }
    result.entry.shallow = std::move(metadata);
    if (result.entry.promisor) {
      result.entry.notes.emplace_back(PromisorSourceNote{});
    }
  }
  if (head->exit_code != 0) {
    result.entry.head_state = HeadState::unborn;
    result.entry.sha.reset();
    auto branch = invoke_classify(
        {"symbolic-ref", "--quiet", "--short", "HEAD"},
        result.entry.promisor);
    if (branch && branch->exit_code == 0) {
      result.entry.branch = trim_git_newline(git_bytes(branch->stdout_bytes));
    }
    if (!result.entry.shallow && !ref_pairs.empty()) {
      for (const auto& [name, sha] : ref_pairs) {
        if (name.starts_with("refs/heads/") || name.starts_with("refs/tags/")) {
          result.entry.local_refs.push_back(
              LocalRef{.ref = name,
                       .sha = sha,
                       .availability = RefAvailability::bundle_carried,
                       .proof = std::nullopt});
        }
      }
      result.entry.capture_mode = CaptureMode::full;
      result.entry.eligibility =
          Eligibility{.method = "ls-remote-ancestry",
                      .result = EligibilityResult::unborn_head,
                      .checked_at = git_checked_at_now(),
                      .proof = std::nullopt};

      auto remotes = invoke_classify({"remote"}, result.entry.promisor);
      if (!remotes || remotes->exit_code != 0) {
        return std::unexpected(remotes ? command_error(repo, "remote")
                                       : remotes.error());
      }
      const auto remote_names = git_bytes(remotes->stdout_bytes);
      std::size_t cursor = 0;
      while (cursor < remote_names.size()) {
        const auto end = remote_names.find('\n', cursor);
        const auto name = remote_names.substr(cursor, end - cursor);
        if (!name.empty()) {
          auto url = invoke_classify({"remote", "get-url", name},
                                     result.entry.promisor);
          if (!url || url->exit_code != 0) {
            return std::unexpected(url ? command_error(repo, "remote get-url")
                                       : url.error());
          }
          result.entry.remotes.push_back(
              Remote{.name = name,
                     .url = trim_git_newline(git_bytes(url->stdout_bytes))});
        }
        if (end == std::string::npos) {
          break;
        }
        cursor = end + 1U;
      }
      if (!result.entry.remotes.empty()) {
        result.entry.remote = result.entry.remotes.front().name;
      }
    }
    if (auto recorded = record_penumbra(
            git, source_state, result.entry.promisor, repo,
            source_state.neutralized_git_config_keys);
        !recorded) {
      return std::unexpected(recorded.error());
    }
    return result;
  }

  result.entry.sha = trim_git_newline(git_bytes(head->stdout_bytes));
  auto branch = invoke_classify(
      {"symbolic-ref", "--quiet", "--short", "HEAD"},
      result.entry.promisor);
  if (branch && branch->exit_code == 0) {
    result.entry.head_state = HeadState::branch;
    result.entry.branch = trim_git_newline(git_bytes(branch->stdout_bytes));
  } else {
    result.entry.head_state = HeadState::detached;
  }
  if (!result.entry.shallow) {
    for (const auto& [name, sha] : ref_pairs) {
      if (name.starts_with("refs/heads/") || name.starts_with("refs/tags/")) {
        result.entry.local_refs.push_back(
            LocalRef{.ref = name,
                     .sha = sha,
                     .availability = RefAvailability::bundle_carried,
                     .proof = std::nullopt});
      }
    }
  }

  auto remotes = invoke_classify({"remote"}, result.entry.promisor);
  if (!remotes || remotes->exit_code != 0) {
    return std::unexpected(remotes ? command_error(repo, "remote")
                                   : remotes.error());
  }
  std::string remote_names = git_bytes(remotes->stdout_bytes);
  std::size_t cursor = 0;
  while (cursor < remote_names.size()) {
    const auto end = remote_names.find('\n', cursor);
    const auto name = remote_names.substr(cursor, end - cursor);
    if (!name.empty()) {
      auto url = invoke_classify({"remote", "get-url", name},
                                 result.entry.promisor);
      if (!url || url->exit_code != 0) {
        return std::unexpected(url ? command_error(repo, "remote get-url")
                                   : url.error());
      }
      result.entry.remotes.push_back(Remote{
          .name = name, .url = trim_git_newline(git_bytes(url->stdout_bytes))});
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  if (!result.entry.remotes.empty()) {
    result.entry.remote = result.entry.remotes.front().name;
  }

  if (result.entry.shallow) {
    if (auto recorded = record_penumbra(
            git, source_state, result.entry.promisor, repo,
            source_state.neutralized_git_config_keys);
        !recorded) {
      return std::unexpected(recorded.error());
    }
    return result;
  }

  auto dirt = invoke_classify({"status", "--porcelain=v2", "-z"},
                              result.entry.promisor);
  if (!dirt || dirt->exit_code != 0) {
    return std::unexpected(dirt ? command_error(repo, "status") : dirt.error());
  }
  if (!dirt->stdout_bytes.empty()) {
    result.entry.dirty = true;
    result.fence = Classification::Fence::dirty;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_dirty_unsupported,
                               .paths = {},
                               .detail = {}};
    return result;
  }

  if (auto recorded = record_penumbra(
          git, source_state, result.entry.promisor, repo,
          source_state.neutralized_git_config_keys);
      !recorded) {
    return std::unexpected(recorded.error());
  }

  return result;
}

}  // namespace biv::repo
