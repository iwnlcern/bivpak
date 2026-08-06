#include "core/repo/eligibility.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string_view>

namespace biv::repo {
namespace {

struct AdvertisedTip {
  std::string remote;
  std::string url;
  std::string ref;
  std::string sha;
};

struct Verdict {
  std::optional<Proof> proof;
  std::optional<std::size_t> first_unknown;
};

BivError command_error(const std::filesystem::path& repo,
                       const std::string_view operation) {
  return BivError{ErrKind::InternalError, repo,
                  "repo eligibility git invocation failed: " +
                      std::string{operation}};
}

std::string bytes(const std::vector<std::byte>& value) {
  return {reinterpret_cast<const char*>(value.data()), value.size()};
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

expected<support::SpawnResult> invoke(
    const Git& git, const std::filesystem::path& repo,
    std::vector<std::string> args, std::vector<std::string> operands,
    const bool no_lazy_fetch) {
  auto result = git.run(args, operands,
                        Git::Opts{.cwd = repo,
                                  .no_lazy_fetch = no_lazy_fetch});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->spawn_failed || result->timed_out || result->io_failed) {
    return std::unexpected(command_error(repo, args.empty() ? "git" : args.front()));
  }
  return result;
}

expected<bool> detect_promisor(const Git& git,
                               const std::filesystem::path& repo) {
  auto result = invoke(
      git, repo,
      {"config", "--get-regexp",
       "^(remote\\..*\\.promisor|remote\\..*\\.partialclonefilter)$"},
      {}, false);
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    return false;
  }
  const auto output = bytes(result->stdout_bytes);
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

void append_advertisement(const Remote& remote, const std::string& output,
                          std::vector<AdvertisedTip>& tips) {
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\n', cursor);
    const auto row = output.substr(cursor, end - cursor);
    const auto tab = row.find('\t');
    if (tab != std::string::npos) {
      const auto ref = row.substr(tab + 1U);
      if (!ref.ends_with("^{}")) {
        tips.push_back(AdvertisedTip{.remote = remote.name,
                                     .url = remote.url,
                                     .ref = ref,
                                     .sha = row.substr(0U, tab)});
      }
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
}

expected<Verdict> check_ancestry(const Git& git,
                                 const std::filesystem::path& repo,
                                 const std::string& sha,
                                 const std::vector<AdvertisedTip>& tips,
                                 const bool no_lazy_fetch) {
  Verdict verdict;
  for (std::size_t index = 0; index < tips.size(); ++index) {
    const auto& tip = tips[index];
    if (sha == tip.sha) {
      verdict.proof = Proof{.remote = tip.remote,
                            .url = tip.url,
                            .ref = tip.ref,
                            .tip_sha = tip.sha};
      return verdict;
    }
    auto present = invoke(git, repo, {"cat-file", "-e"}, {tip.sha},
                          no_lazy_fetch);
    if (!present) {
      return std::unexpected(present.error());
    }
    if (present->exit_code != 0) {
      if (!verdict.first_unknown) {
        verdict.first_unknown = index;
      }
      continue;
    }
    auto ancestor = invoke(git, repo, {"merge-base", "--is-ancestor"},
                           {sha, tip.sha}, no_lazy_fetch);
    if (!ancestor) {
      return std::unexpected(ancestor.error());
    }
    if (ancestor->exit_code == 0) {
      verdict.proof = Proof{.remote = tip.remote,
                            .url = tip.url,
                            .ref = tip.ref,
                            .tip_sha = tip.sha};
      return verdict;
    }
  }
  return verdict;
}

}  // namespace

expected<void> run_eligibility(const Git& git, RepoEntry& entry) {
  if (entry.head_state == HeadState::unborn || entry.shallow) {
    return {};
  }
  if (!entry.sha) {
    return std::unexpected(BivError{ErrKind::InternalError, entry.relpath,
                                    "born repo has no HEAD sha"});
  }

  auto promisor = detect_promisor(git, entry.relpath);
  if (!promisor) {
    return std::unexpected(promisor.error());
  }

  Eligibility eligibility{.method = "ls-remote-ancestry",
                          .checked_at = checked_at_now()};
  if (entry.remotes.empty()) {
    eligibility.result = EligibilityResult::no_remote;
    entry.eligibility = std::move(eligibility);
    entry.capture_mode = CaptureMode::full;
    for (auto& ref : entry.local_refs) {
      ref.availability = RefAvailability::repo_bundle_carried;
      ref.proof.reset();
    }
    return {};
  }

  std::vector<AdvertisedTip> tips;
  std::size_t reachable_remotes = 0;
  for (const auto& remote : entry.remotes) {
    auto advertisement = invoke(git, entry.relpath,
                                {"ls-remote", "--heads", "--tags"},
                                {remote.url}, *promisor);
    if (!advertisement) {
      return std::unexpected(advertisement.error());
    }
    if (advertisement->exit_code == 0) {
      ++reachable_remotes;
      append_advertisement(remote, bytes(advertisement->stdout_bytes), tips);
    }
  }

  if (reachable_remotes == 0) {
    eligibility.result = EligibilityResult::remote_unreachable;
  } else {
    auto verdict = check_ancestry(git, entry.relpath, *entry.sha, tips, *promisor);
    if (!verdict) {
      return std::unexpected(verdict.error());
    }
    if (!verdict->proof && verdict->first_unknown) {
      const auto& unknown = tips[*verdict->first_unknown];
      auto fetched = invoke(git, entry.relpath, {"fetch", "--no-tags"},
                            {unknown.url, unknown.ref}, *promisor);
      if (!fetched) {
        return std::unexpected(fetched.error());
      }
      if (fetched->exit_code == 0) {
        verdict = check_ancestry(git, entry.relpath, *entry.sha, tips, *promisor);
        if (!verdict) {
          return std::unexpected(verdict.error());
        }
      }
    }

    if (verdict->proof) {
      eligibility.result = EligibilityResult::proven;
      eligibility.proof = verdict->proof;
    } else if (verdict->first_unknown) {
      eligibility.result = EligibilityResult::unknown_tip;
    } else {
      eligibility.result = EligibilityResult::sha_unpushed;
    }
  }

  entry.capture_mode = eligibility.result == EligibilityResult::proven
                           ? CaptureMode::overlay
                           : CaptureMode::full;
  entry.eligibility = eligibility;

  for (auto& ref : entry.local_refs) {
    ref.proof.reset();
    if (entry.capture_mode == CaptureMode::full) {
      ref.availability = RefAvailability::repo_bundle_carried;
      continue;
    }
    auto verdict = check_ancestry(git, entry.relpath, ref.sha, tips, *promisor);
    if (!verdict) {
      return std::unexpected(verdict.error());
    }
    if (verdict->proof) {
      ref.availability = RefAvailability::remote_proven;
      ref.proof = verdict->proof;
    } else {
      ref.availability = RefAvailability::bundle_carried;
    }
  }
  return {};
}

}  // namespace biv::repo
