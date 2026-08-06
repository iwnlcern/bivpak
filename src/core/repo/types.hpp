#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <variant>
#include <vector>

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
  repo_restore_failed
};

struct EngineIssue {
  EngineErrorKind kind{EngineErrorKind::git_invocation_failed};
  std::vector<std::filesystem::path> paths;
  std::string detail;
};

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
  std::optional<Eligibility> eligibility;
  std::vector<LocalRef> local_refs;
  std::optional<std::filesystem::path> local_refs_bundle;
  Capture capture;
  std::optional<std::filesystem::path> bundle;
  std::optional<Shallow> shallow;
  std::nullptr_t sparse{nullptr};
  std::vector<RepoNote> notes;
};

}  // namespace biv::repo
