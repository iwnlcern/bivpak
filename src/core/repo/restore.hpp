#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "core/repo/git.hpp"
#include "core/repo/types.hpp"
#include "core/support/error.hpp"

namespace biv::repo {

enum class RepoRestoreOutcome {
  restored,
  shallow_pointer,
  payload_only_unborn,
  failed
};

struct LocalRefRestoreRow {
  std::string ref;
  bool recreated{false};
  bool skipped_at_sha{false};
  std::optional<std::string> detail;
};

struct RepoRestoreRow {
  std::string id;
  std::filesystem::path relpath;
  RepoRestoreOutcome outcome{RepoRestoreOutcome::failed};
  std::optional<std::string> sha;
  CaptureMode capture_mode{CaptureMode::full};
  std::vector<LocalRefRestoreRow> local_refs;
  std::vector<std::string> advisories;
  std::optional<Shallow> shallow;
};

expected<RepoRestoreRow> restore_entry(
    const Git& git, const RepoEntry& entry,
    const std::filesystem::path& partial_root,
    const std::filesystem::path& stage_root);

}  // namespace biv::repo
