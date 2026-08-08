#include "core/repo/eligibility.hpp"

#include <algorithm>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "core/repo/git_exec.hpp"

namespace biv::repo {
namespace {

constexpr std::size_t kMaxAdvertisedTips = 4096U;

struct AdvertisedTip {
  std::string remote;
  std::string url;
  std::string ref;
  std::string sha;
  bool present{false};
};

struct Verdict {
  std::optional<Proof> proof;
  bool unknown_tip{false};
};

void append_advertisement(const Remote& remote, const std::string& output,
                          std::vector<AdvertisedTip>& tips) {
  std::size_t cursor = 0;
  while (cursor < output.size() && tips.size() <= kMaxAdvertisedTips) {
    const auto end = output.find('\n', cursor);
    const auto row = output.substr(cursor, end - cursor);
    const auto tab = row.find('\t');
    if (tab != std::string::npos) {
      const auto ref = row.substr(tab + 1U);
      const auto sha = row.substr(0U, tab);
      if (!ref.ends_with("^{}") && valid_ref_name(ref) &&
          valid_object_id(sha)) {
        tips.push_back(AdvertisedTip{.remote = remote.name,
                                     .url = remote.url,
                                     .ref = ref,
                                     .sha = sha,
                                     .present = false});
      }
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
}

expected<void> mark_present_tips(const Git& git,
                                 const std::filesystem::path& repo,
                                 std::vector<AdvertisedTip>& tips,
                                 const bool promisor) {
  std::unordered_map<std::string, bool> presence;
  for (auto& tip : tips) {
    const auto known = presence.find(tip.sha);
    if (known != presence.end()) {
      tip.present = known->second;
      continue;
    }
    auto result = invoke_git(git, repo, {"cat-file", "-e"}, {tip.sha},
                             "eligibility-tip-presence",
                             GitInvokeOptions{.promisor = promisor});
    if (!result) {
      return std::unexpected(result.error());
    }
    tip.present = result->exit_code == 0;
    presence.emplace(tip.sha, tip.present);
  }
  return {};
}

expected<Verdict> check_ancestry(const Git& git,
                                 const std::filesystem::path& repo,
                                 const std::string& sha,
                                 const std::vector<AdvertisedTip>& tips,
                                 const bool promisor) {
  Verdict verdict;
  std::vector<const AdvertisedTip*> present;
  present.reserve(tips.size());
  for (const auto& tip : tips) {
    if (!tip.present) {
      verdict.unknown_tip = true;
      continue;
    }
    if (sha == tip.sha) {
      verdict.proof = Proof{.remote = tip.remote,
                            .url = tip.url,
                            .ref = tip.ref,
                            .tip_sha = tip.sha};
      return verdict;
    }
    present.push_back(&tip);
  }
  if (present.empty() || !valid_object_id(sha)) {
    return verdict;
  }

  std::vector<std::string> args{"rev-list", "--ancestry-path",
                                sha + ".." + present.front()->sha};
  for (std::size_t index = 1; index < present.size(); ++index) {
    args.push_back(present.at(index)->sha);
  }
  auto result = invoke_git(git, repo, args, {}, "eligibility-ancestry",
                           GitInvokeOptions{.promisor = promisor});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    return verdict;
  }
  std::unordered_set<std::string> reachable;
  const auto output = git_bytes(result->stdout_bytes);
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\n', cursor);
    const auto value = output.substr(cursor, end - cursor);
    if (valid_object_id(value)) {
      reachable.insert(value);
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  for (const auto* tip : present) {
    if (reachable.contains(tip->sha)) {
      verdict.proof = Proof{.remote = tip->remote,
                            .url = tip->url,
                            .ref = tip->ref,
                            .tip_sha = tip->sha};
      break;
    }
  }
  return verdict;
}

void force_full(RepoEntry& entry, Eligibility eligibility) {
  entry.capture_mode = CaptureMode::full;
  entry.eligibility = std::move(eligibility);
  for (auto& ref : entry.local_refs) {
    ref.availability = RefAvailability::repo_bundle_carried;
    ref.proof.reset();
  }
}

}  // namespace

expected<void> run_eligibility(const Git& git, RepoEntry& entry) {
  if (entry.head_state == HeadState::unborn || entry.shallow) {
    return {};
  }
  if (!entry.sha || !valid_object_id(*entry.sha)) {
    return std::unexpected(
        make_engine_error(EngineErrorKind::git_invocation_failed, entry.relpath,
                          "born repo has no valid HEAD object id"));
  }

  const auto repo =
      entry.engine_source ? entry.engine_source->repo_path : entry.relpath;
  Eligibility eligibility{.method = "ls-remote-ancestry",
                          .result = EligibilityResult::no_remote,
                          .checked_at = git_checked_at_now(),
                          .proof = std::nullopt};
  if (entry.remotes.empty()) {
    force_full(entry, std::move(eligibility));
    return {};
  }

  std::vector<AdvertisedTip> tips;
  std::size_t reachable_remotes = 0;
  for (const auto& remote : entry.remotes) {
    auto advertisement =
        invoke_git(git, repo, {"ls-remote", "--heads", "--tags"}, {remote.url},
                   "eligibility-advertisement",
                   GitInvokeOptions{.promisor = entry.promisor,
                                    .allow_user_protocol = true,
                                    .call_class = GitCallClass::network});
    if (!advertisement) {
      return std::unexpected(advertisement.error());
    }
    if (advertisement->exit_code == 0) {
      ++reachable_remotes;
      append_advertisement(remote, git_bytes(advertisement->stdout_bytes),
                           tips);
    }
    if (tips.size() > kMaxAdvertisedTips) {
      // The sealed vocabulary has one honest-unprovable result; exceeding the
      // bounded advertisement snapshot is that class and therefore forces full.
      eligibility.result = EligibilityResult::unknown_tip;
      force_full(entry, std::move(eligibility));
      return {};
    }
  }

  if (reachable_remotes == 0) {
    eligibility.result = EligibilityResult::remote_unreachable;
    force_full(entry, std::move(eligibility));
    return {};
  }
  if (auto present = mark_present_tips(git, repo, tips, entry.promisor);
      !present) {
    return std::unexpected(present.error());
  }

  auto head = check_ancestry(git, repo, *entry.sha, tips, entry.promisor);
  if (!head) {
    return std::unexpected(head.error());
  }
  if (head->proof) {
    eligibility.result = EligibilityResult::proven;
    eligibility.proof = std::move(head->proof);
    entry.remote = eligibility.proof->remote;
    entry.capture_mode = CaptureMode::overlay;
  } else {
    eligibility.result = head->unknown_tip ? EligibilityResult::unknown_tip
                                           : EligibilityResult::sha_unpushed;
    force_full(entry, std::move(eligibility));
    return {};
  }
  entry.eligibility = std::move(eligibility);

  for (auto& ref : entry.local_refs) {
    ref.proof.reset();
    if (!valid_ref_name(ref.ref) || !valid_object_id(ref.sha)) {
      ref.availability = RefAvailability::bundle_carried;
      continue;
    }
    auto verdict = check_ancestry(git, repo, ref.sha, tips, entry.promisor);
    if (!verdict) {
      return std::unexpected(verdict.error());
    }
    if (verdict->proof) {
      ref.availability = RefAvailability::remote_proven;
      ref.proof = std::move(verdict->proof);
    } else {
      ref.availability = RefAvailability::bundle_carried;
    }
  }
  return {};
}

}  // namespace biv::repo
