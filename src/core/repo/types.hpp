#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "core/support/error.hpp"

namespace biv::repo {

enum class RepoKind { repo, nested, submodule };

enum class HeadState { branch, detached, unborn };

enum class CaptureMode { overlay, full };

enum class EligibilityResult {
  proven,
  unknown_tip,
  no_remote,
  sha_unpushed,
  remote_unreachable,
  offline_declared,
  unborn_head
};

enum class RefAvailability {
  remote_proven,
  bundle_carried,
  repo_bundle_carried
};

enum class EngineErrorKind {
  repo_dirty_unsupported,
  repo_nested_unsupported,
  repo_submodule_unsupported,
  unmerged_index_unrepresentable,
  ref_uncapturable,
  promisor_objects_unavailable,
  git_invocation_failed,
  git_budget_expired,
  repo_restore_failed
};

struct EngineIssue {
  EngineErrorKind kind{EngineErrorKind::git_invocation_failed};
  std::vector<std::filesystem::path> paths;
  std::string detail;
};

inline constexpr std::string_view engine_error_name(
    const EngineErrorKind kind) noexcept {
  switch (kind) {
    case EngineErrorKind::repo_dirty_unsupported:
      return "repo-dirty-unsupported";
    case EngineErrorKind::repo_nested_unsupported:
      return "repo-nested-unsupported";
    case EngineErrorKind::repo_submodule_unsupported:
      return "repo-submodule-unsupported";
    case EngineErrorKind::unmerged_index_unrepresentable:
      return "unmerged-index-unrepresentable";
    case EngineErrorKind::ref_uncapturable:
      return "ref-uncapturable";
    case EngineErrorKind::promisor_objects_unavailable:
      return "promisor-objects-unavailable";
    case EngineErrorKind::git_invocation_failed:
      return "git-invocation-failed";
    case EngineErrorKind::git_budget_expired:
      return "git-budget-expired";
    case EngineErrorKind::repo_restore_failed:
      return "repo-restore-failed";
  }
  return "git-invocation-failed";
}

inline BivError make_engine_error(const EngineErrorKind kind,
                                  const std::filesystem::path& path,
                                  std::string detail) {
  BivError error{ErrKind::InternalError, path.string(), std::move(detail)};
  error.facts.emplace("repo_engine_kind", std::string{engine_error_name(kind)});
  return error;
}

inline std::optional<EngineErrorKind> engine_error_kind(const BivError& error) {
  const auto fact = error.facts.find("repo_engine_kind");
  if (fact == error.facts.end()) {
    return std::nullopt;
  }
  for (const auto kind : {EngineErrorKind::repo_dirty_unsupported,
                          EngineErrorKind::repo_nested_unsupported,
                          EngineErrorKind::repo_submodule_unsupported,
                          EngineErrorKind::unmerged_index_unrepresentable,
                          EngineErrorKind::ref_uncapturable,
                          EngineErrorKind::promisor_objects_unavailable,
                          EngineErrorKind::git_invocation_failed,
                          EngineErrorKind::git_budget_expired,
                          EngineErrorKind::repo_restore_failed}) {
    if (fact->second == engine_error_name(kind)) {
      return kind;
    }
  }
  return std::nullopt;
}

struct Remote {
  std::string name;
  std::string url;
};

struct Proof {
  std::string remote;
  std::string url;
  std::string ref;
  std::string tip_sha;
};

struct LocalRef {
  std::string ref;
  std::string sha;
  RefAvailability availability{RefAvailability::remote_proven};
  std::optional<Proof> proof;
};

struct NonCarriedRefsNote {
  std::vector<std::string> refs_p1;
  std::optional<std::uint64_t> omitted_count;
};

struct PromisorSourceNote {};

struct Eligibility {
  std::string method;
  EligibilityResult result{EligibilityResult::no_remote};
  std::string checked_at;
  std::optional<Proof> proof;
};

struct Shallow {
  std::string sha;
  std::vector<std::string> boundary;
  std::vector<std::string> remote_urls;
};

enum class ForcedPayloadReason {
  eol_conversion,
  filemode_unrepresentable,
  rename_in_flight,
  binary_unstaged_intent,
  adapter_other
};

struct ForcedPayload {
  std::filesystem::path path;
  ForcedPayloadReason reason{ForcedPayloadReason::adapter_other};
};

struct CaptureEnvironment {
  std::optional<std::string> core_autocrlf;
  std::optional<bool> core_filemode;
  bool sparse{false};
};

struct Capture {
  std::optional<std::filesystem::path> staged_patch;
  std::optional<std::filesystem::path> worktree_patch;
  std::string payload_prefix{"payload/"};
  std::vector<ForcedPayload> forced_payload;
  CaptureEnvironment capture_env;
};

struct UnknownNote {
  std::string kind;
  // Exact validated manifest-member bytes. Unknown discriminants are skipped
  // for default rendering but must survive byte-for-byte for --json.
  std::string verbatim_json;
};

using RepoNote =
    std::variant<NonCarriedRefsNote, PromisorSourceNote, UnknownNote>;

// Transient engine state. This is deliberately not a manifest field; T5
// serializes only the schema members below and uses this state while packing
// the source tree.
struct EngineSourceState {
  std::filesystem::path repo_path;
  std::vector<std::filesystem::path> penumbra_paths;
  std::vector<std::string> neutralized_git_config_keys{};
};

struct RepoEntry {
  std::string id;
  std::filesystem::path relpath;
  RepoKind kind{RepoKind::repo};
  std::optional<std::string> parent_id;
  std::optional<std::string> remote;
  std::vector<Remote> remotes;
  std::optional<std::string> sha;
  std::optional<std::string> branch;
  HeadState head_state{HeadState::detached};
  bool dirty{false};
  CaptureMode capture_mode{CaptureMode::full};
  // Classification-time policy carried across later pack-side Git calls;
  // never serialized as a manifest field.
  bool promisor{false};
  std::optional<Eligibility> eligibility;
  std::vector<LocalRef> local_refs;
  std::optional<std::filesystem::path> local_refs_bundle;
  Capture capture;
  std::optional<std::filesystem::path> bundle;
  std::optional<Shallow> shallow;
  std::nullptr_t sparse{nullptr};
  std::vector<RepoNote> notes;
  std::optional<EngineSourceState> engine_source;
};

}  // namespace biv::repo
