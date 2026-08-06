#include "core/repo/classify.hpp"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string_view>

namespace biv::repo {
namespace {

BivError command_error(const std::filesystem::path& repo,
                       const std::string_view operation) {
  return BivError{ErrKind::InternalError, repo,
                  "repo classification git invocation failed: " +
                      std::string{operation}};
}

std::string bytes(const std::vector<std::byte>& value) {
  return {reinterpret_cast<const char*>(value.data()), value.size()};
}

std::string trim_newline(std::string value) {
  while (!value.empty() && (value.back() == '\n' || value.back() == '\r')) {
    value.pop_back();
  }
  return value;
}

expected<support::SpawnResult> invoke(const Git& git,
                                      const std::filesystem::path& repo,
                                      std::vector<std::string> args,
                                      const bool no_lazy_fetch = false) {
  auto result = git.run(args, {}, Git::Opts{.cwd = repo,
                                            .no_lazy_fetch = no_lazy_fetch});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->spawn_failed || result->timed_out || result->io_failed) {
    return std::unexpected(command_error(repo, args.empty() ? "git" : args.front()));
  }
  return result;
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

std::string checked_at_now() {
  const auto now = std::chrono::system_clock::now();
  const auto value = std::chrono::system_clock::to_time_t(now);
  std::tm utc{};
  ::gmtime_r(&value, &utc);
  std::ostringstream output;
  output << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ");
  return output.str();
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

bool promisor_enabled(const std::string& output) {
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\n', cursor);
    const auto row = output.substr(cursor, end - cursor);
    const auto separator = row.find_first_of(" \t");
    if (separator != std::string::npos) {
      const auto key = row.substr(0U, separator);
      const auto value = row.substr(separator + 1U);
      if (key.ends_with(".partialclonefilter") ||
          (key.ends_with(".promisor") &&
           (value == "true" || value == "yes" || value == "on" ||
            value == "1"))) {
        return true;
      }
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  return false;
}

}  // namespace

expected<Classification> classify(const Git& git,
                                  const std::filesystem::path& repo,
                                  const Discovery& discovery) {
  Classification result;
  result.entry.id = repo.filename().string();
  result.entry.relpath = repo;

  auto promisor = invoke(
      git, repo,
      {"config", "--get-regexp",
       "^(remote\\..*\\.promisor|remote\\..*\\.partialclonefilter)$"});
  if (!promisor) {
    return std::unexpected(promisor.error());
  }
  result.promisor =
      promisor->exit_code == 0 && promisor_enabled(bytes(promisor->stdout_bytes));

  const auto nested = std::ranges::find_if(discovery.repos, [](const auto& boundary) {
    return boundary.kind == RepoKind::nested;
  });
  if (nested != discovery.repos.end()) {
    result.fence = Classification::Fence::nested;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_nested_unsupported,
                               .paths = {nested->relpath}};
    return result;
  }
  const auto submodule = std::ranges::find_if(discovery.repos, [](const auto& boundary) {
    return boundary.kind == RepoKind::submodule;
  });
  if (submodule != discovery.repos.end()) {
    result.fence = Classification::Fence::submodule;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_submodule_unsupported,
                               .paths = {submodule->relpath}};
    return result;
  }

  auto index = invoke(git, repo, {"ls-files", "-s", "-z"}, result.promisor);
  if (!index || index->exit_code != 0) {
    return std::unexpected(index ? command_error(repo, "ls-files -s")
                                 : index.error());
  }
  if (const auto gitlink = first_gitlink_path(bytes(index->stdout_bytes))) {
    result.fence = Classification::Fence::submodule;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_submodule_unsupported,
                               .paths = {*gitlink}};
    return result;
  }

  auto unmerged = invoke(git, repo, {"ls-files", "-u", "-z"}, result.promisor);
  if (!unmerged) {
    return std::unexpected(unmerged.error());
  }
  if (unmerged->exit_code != 0) {
    return std::unexpected(command_error(repo, "ls-files -u"));
  }
  const auto unmerged_output = bytes(unmerged->stdout_bytes);
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
    result.issue = EngineIssue{.kind = EngineErrorKind::unmerged_index_unrepresentable,
                               .paths = std::move(paths)};
    return result;
  }

  auto head = invoke(git, repo, {"rev-parse", "--verify", "HEAD"}, result.promisor);
  if (!head) {
    return std::unexpected(head.error());
  }
  auto refs = invoke(git, repo,
                     {"for-each-ref", "--format=%(refname)%00%(objectname)%00"},
                     result.promisor);
  if (!refs || refs->exit_code != 0) {
    return std::unexpected(refs ? command_error(repo, "for-each-ref") : refs.error());
  }
  const auto ref_pairs = parse_ref_pairs(bytes(refs->stdout_bytes));
  if (head->exit_code != 0) {
    result.entry.head_state = HeadState::unborn;
    result.entry.sha.reset();
    auto branch = invoke(git, repo, {"symbolic-ref", "--quiet", "--short", "HEAD"},
                         result.promisor);
    if (branch && branch->exit_code == 0) {
      result.entry.branch = trim_newline(bytes(branch->stdout_bytes));
    }
    if (!ref_pairs.empty()) {
      result.entry.capture_mode = CaptureMode::full;
      result.entry.eligibility = Eligibility{
          .method = "ls-remote-ancestry",
          .result = EligibilityResult::unborn_head,
          .checked_at = checked_at_now()};
    }
    return result;
  }

  result.entry.sha = trim_newline(bytes(head->stdout_bytes));
  auto branch = invoke(git, repo, {"symbolic-ref", "--quiet", "--short", "HEAD"},
                       result.promisor);
  if (branch && branch->exit_code == 0) {
    result.entry.head_state = HeadState::branch;
    result.entry.branch = trim_newline(bytes(branch->stdout_bytes));
  } else {
    result.entry.head_state = HeadState::detached;
  }
  for (const auto& [name, sha] : ref_pairs) {
    if (name.starts_with("refs/heads/") || name.starts_with("refs/tags/")) {
      result.entry.local_refs.push_back(LocalRef{
          .ref = name, .sha = sha, .availability = RefAvailability::bundle_carried});
    }
  }

  auto remotes = invoke(git, repo, {"remote"}, result.promisor);
  if (!remotes || remotes->exit_code != 0) {
    return std::unexpected(remotes ? command_error(repo, "remote") : remotes.error());
  }
  std::string remote_names = bytes(remotes->stdout_bytes);
  std::size_t cursor = 0;
  while (cursor < remote_names.size()) {
    const auto end = remote_names.find('\n', cursor);
    const auto name = remote_names.substr(cursor, end - cursor);
    if (!name.empty()) {
      auto url = invoke(git, repo, {"remote", "get-url", name}, result.promisor);
      if (!url || url->exit_code != 0) {
        return std::unexpected(url ? command_error(repo, "remote get-url") : url.error());
      }
      result.entry.remotes.push_back(
          Remote{.name = name, .url = trim_newline(bytes(url->stdout_bytes))});
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  if (!result.entry.remotes.empty()) {
    result.entry.remote = result.entry.remotes.front().name;
  }

  auto dirt = invoke(git, repo, {"status", "--porcelain=v2", "-z"}, result.promisor);
  if (!dirt || dirt->exit_code != 0) {
    return std::unexpected(dirt ? command_error(repo, "status") : dirt.error());
  }
  if (!dirt->stdout_bytes.empty()) {
    result.entry.dirty = true;
    result.fence = Classification::Fence::dirty;
    result.issue = EngineIssue{.kind = EngineErrorKind::repo_dirty_unsupported};
    return result;
  }

  auto shallow = invoke(git, repo, {"rev-parse", "--is-shallow-repository"},
                        result.promisor);
  if (!shallow || shallow->exit_code != 0) {
    return std::unexpected(shallow ? command_error(repo, "is-shallow") : shallow.error());
  }
  if (trim_newline(bytes(shallow->stdout_bytes)) == "true") {
    Shallow metadata{.sha = *result.entry.sha};
    const auto shallow_file = repo / ".git/shallow";
    std::ifstream input{shallow_file};
    std::string boundary;
    while (std::getline(input, boundary)) {
      if (!boundary.empty()) {
        metadata.boundary.push_back(boundary);
      }
    }
    for (const auto& remote : result.entry.remotes) {
      metadata.remote_urls.push_back(remote.url);
    }
    result.entry.shallow = std::move(metadata);
    if (result.promisor) {
      result.entry.notes.emplace_back(PromisorSourceNote{});
    }
  }
  return result;
}

}  // namespace biv::repo
