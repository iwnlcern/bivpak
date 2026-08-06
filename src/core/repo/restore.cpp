#include "core/repo/restore.hpp"

#include <algorithm>
#include <iterator>
#include <string_view>

namespace biv::repo {
namespace {

// The two views are named domain values at every private call site.
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BivError restore_error(const RepoEntry& entry, const std::string_view step,
                       const std::string_view detail = {}) {
  auto message = "RepoRestoreFailed: " + std::string{step};
  if (!detail.empty()) {
    message += ": " + std::string{detail};
  }
  return make_engine_error(EngineErrorKind::repo_restore_failed, entry.relpath,
                           std::move(message));
}

std::string bytes(const std::vector<std::byte>& value) {
  std::string output;
  output.reserve(value.size());
  std::ranges::transform(value, std::back_inserter(output), [](const auto byte) {
    return static_cast<char>(std::to_integer<unsigned char>(byte));
  });
  return output;
}

std::string trim_newline(std::string value) {
  while (!value.empty() && (value.back() == '\n' || value.back() == '\r')) {
    value.pop_back();
  }
  return value;
}

expected<support::SpawnResult> invoke(
    const Git& git, const std::filesystem::path& repo,
    std::vector<std::string> args, std::vector<std::string> operands = {}) {
  Git::Opts options;
  options.cwd = repo;
  auto result = git.run(args, operands, options);
  if (!result) {
    return std::unexpected(make_engine_error(
        EngineErrorKind::repo_restore_failed, repo,
        "repo restore subprocess failed: " + result.error().detail));
  }
  if (result->spawn_failed || result->timed_out || result->io_failed) {
    return std::unexpected(make_engine_error(
        EngineErrorKind::repo_restore_failed, repo,
        "repo restore subprocess failed"));
  }
  return result;
}

expected<void> require_success(const Git& git,
                               const std::filesystem::path& repo,
                               std::vector<std::string> args,
                               std::vector<std::string> operands,
                               const RepoEntry& entry,
                               const std::string_view step) {
  auto result = invoke(git, repo, std::move(args), std::move(operands));
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    return std::unexpected(restore_error(entry, step));
  }
  return {};
}

expected<void> make_directories(const std::filesystem::path& path,
                                const RepoEntry& entry) {
  std::error_code error;
  std::filesystem::create_directories(path, error);
  if (error) {
    return std::unexpected(
        restore_error(entry, "clone", "mkdir: " + error.message()));
  }
  return {};
}

std::optional<std::string> clone_url(const RepoEntry& entry) {
  if (entry.remote) {
    const auto selected = std::ranges::find_if(entry.remotes, [&](const auto& remote) {
      return remote.name == *entry.remote;
    });
    if (selected != entry.remotes.end()) {
      return selected->url;
    }
  }
  if (!entry.remotes.empty()) {
    return entry.remotes.front().url;
  }
  return std::nullopt;
}

expected<void> replace_remotes(const Git& git,
                               const std::filesystem::path& target,
                               const RepoEntry& entry) {
  auto removed = invoke(git, target, {"remote", "remove", "origin"});
  if (!removed) {
    return std::unexpected(removed.error());
  }
  for (const auto& remote : entry.remotes) {
    if (auto added = require_success(git, target, {"remote", "add"},
                                     {remote.name, remote.url}, entry, "clone");
        !added) {
      return added;
    }
  }
  return {};
}

expected<void> import_bundle_closure(const Git& git,
                                     const std::filesystem::path& target,
                                     const std::filesystem::path& bundle,
                                     const RepoEntry& entry) {
  if (!std::filesystem::is_regular_file(bundle)) {
    return std::unexpected(restore_error(entry, "clone", "missing repo member"));
  }
  return require_success(git, target, {"bundle", "unbundle"}, {bundle.string()},
                         entry, "clone");
}

expected<std::optional<std::string>> current_ref(
    const Git& git, const std::filesystem::path& target,
    const std::string& ref) {
  auto result = invoke(git, target, {"show-ref", "--verify", "--quiet", ref});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code == 1) {
    return std::optional<std::string>{};
  }
  if (result->exit_code != 0) {
    return std::unexpected(BivError{ErrKind::InternalError, target,
                                    "repo restore ref query failed"});
  }
  result = invoke(git, target, {"show-ref", "--verify", "--hash=40", ref});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    return std::unexpected(BivError{ErrKind::InternalError, target,
                                    "repo restore ref read failed"});
  }
  return std::optional<std::string>{trim_newline(bytes(result->stdout_bytes))};
}

expected<void> ensure_object(const Git& git,
                             const std::filesystem::path& target,
                             const LocalRef& ref, const RepoEntry& entry) {
  auto present = invoke(git, target, {"cat-file", "-e"}, {ref.sha});
  if (!present) {
    return std::unexpected(present.error());
  }
  if (present->exit_code == 0) {
    return {};
  }
  if (!ref.proof) {
    return std::unexpected(
        restore_error(entry, "ref-recreation", "object absent for " + ref.ref));
  }
  if (auto fetched = require_success(git, target, {"fetch", "--no-tags"},
                                     {ref.proof->url, ref.proof->ref}, entry,
                                     "ref-recreation");
      !fetched) {
    return fetched;
  }
  present = invoke(git, target, {"cat-file", "-e"}, {ref.sha});
  if (!present || present->exit_code != 0) {
    return std::unexpected(
        present ? restore_error(entry, "ref-recreation", "fetched object absent")
                : present.error());
  }
  return {};
}

expected<std::vector<LocalRefRestoreRow>> recreate_refs(
    const Git& git, const std::filesystem::path& target,
    const RepoEntry& entry) {
  std::vector<LocalRefRestoreRow> rows;
  rows.reserve(entry.local_refs.size());
  for (const auto& ref : entry.local_refs) {
    LocalRefRestoreRow row;
    row.ref = ref.ref;
    auto existing = current_ref(git, target, ref.ref);
    if (!existing) {
      return std::unexpected(existing.error());
    }
    if (*existing && **existing == ref.sha) {
      row.recreated = true;
      row.skipped_at_sha = true;
      rows.push_back(std::move(row));
      continue;
    }
    if (auto available = ensure_object(git, target, ref, entry); !available) {
      return std::unexpected(available.error());
    }
    if (auto updated = require_success(git, target,
                                       {"update-ref", ref.ref, ref.sha}, {}, entry,
                                       "ref-recreation");
        !updated) {
      return std::unexpected(updated.error());
    }
    row.recreated = true;
    rows.push_back(std::move(row));
  }
  return rows;
}

expected<void> establish_head(const Git& git,
                              const std::filesystem::path& target,
                              const RepoEntry& entry) {
  if (entry.head_state == HeadState::unborn) {
    if (!entry.branch) {
      return std::unexpected(
          restore_error(entry, "checkout", "unborn branch absent"));
    }
    return require_success(git, target,
                           {"symbolic-ref", "HEAD", "refs/heads/" + *entry.branch},
                           {}, entry, "checkout");
  }
  if (!entry.sha) {
    return std::unexpected(restore_error(entry, "checkout", "HEAD sha absent"));
  }
  if (entry.head_state == HeadState::detached) {
    return require_success(git, target, {"checkout", "--detach", *entry.sha}, {},
                           entry, "checkout");
  }
  if (!entry.branch) {
    return std::unexpected(restore_error(entry, "checkout", "branch absent"));
  }
  if (auto symbolic = require_success(
          git, target, {"symbolic-ref", "HEAD", "refs/heads/" + *entry.branch}, {},
          entry, "checkout");
      !symbolic) {
    return symbolic;
  }
  return require_success(git, target, {"reset", "--hard", *entry.sha}, {}, entry,
                         "checkout");
}

expected<void> verify_restored(const Git& git,
                               const std::filesystem::path& target,
                               const RepoEntry& entry) {
  for (const auto& ref : entry.local_refs) {
    auto actual = current_ref(git, target, ref.ref);
    if (!actual || !*actual || **actual != ref.sha) {
      return std::unexpected(
          actual ? restore_error(entry, "ref-recreation", "verification: " + ref.ref)
                 : actual.error());
    }
  }
  if (entry.head_state == HeadState::unborn) {
    auto symbolic = invoke(git, target, {"symbolic-ref", "HEAD"});
    const auto expected_ref = entry.branch ? "refs/heads/" + *entry.branch : "";
    if (!symbolic || symbolic->exit_code != 0 ||
        trim_newline(bytes(symbolic->stdout_bytes)) != expected_ref) {
      return std::unexpected(
          symbolic ? restore_error(entry, "checkout", "HEAD symref verification")
                   : symbolic.error());
    }
    return {};
  }

  auto head = invoke(git, target, {"rev-parse", "HEAD"});
  if (!head || head->exit_code != 0 ||
      trim_newline(bytes(head->stdout_bytes)) != entry.sha) {
    return std::unexpected(
        head ? restore_error(entry, "checkout", "HEAD verification") : head.error());
  }
  auto status = invoke(git, target, {"status", "--porcelain=v2", "-z"});
  if (!status || status->exit_code != 0 || !status->stdout_bytes.empty()) {
    return std::unexpected(
        status ? restore_error(entry, "checkout", "worktree verification")
               : status.error());
  }
  return {};
}

void append_note_advisories(const RepoEntry& entry, RepoRestoreRow& row) {
  for (const auto& note : entry.notes) {
    if (const auto* refs = std::get_if<NonCarriedRefsNote>(&note)) {
      auto advisory = "non-carried refs: listed=" +
                      std::to_string(refs->refs_p1.size());
      if (refs->omitted_count) {
        advisory += " omitted=" + std::to_string(*refs->omitted_count);
      }
      row.advisories.push_back(std::move(advisory));
    }
  }
}

// Both paths have distinct, stable roles and are kept adjacent at this private seam.
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
expected<void> finalize_root_repo(const std::filesystem::path& materialized,
                                  const std::filesystem::path& partial_root,
                                  const RepoEntry& entry) {
  std::error_code iterator_error;
  std::filesystem::directory_iterator iterator{materialized, iterator_error};
  if (iterator_error) {
    return std::unexpected(
        restore_error(entry, "clone", "root inventory: " + iterator_error.message()));
  }
  std::vector<std::filesystem::path> children;
  for (const auto& child : iterator) {
    children.push_back(child.path());
  }
  std::ranges::sort(children);
  for (const auto& child : children) {
    const auto destination = partial_root / child.filename();
    if (std::filesystem::exists(destination)) {
      return std::unexpected(
          restore_error(entry, "clone", "root destination collision"));
    }
    std::error_code rename_error;
    std::filesystem::rename(child, destination, rename_error);
    if (rename_error) {
      return std::unexpected(
          restore_error(entry, "clone", "root move: " + rename_error.message()));
    }
  }
  std::error_code remove_error;
  if (!std::filesystem::remove(materialized, remove_error) || remove_error) {
    return std::unexpected(
        restore_error(entry, "stage-cleanup", "root helper cleanup"));
  }
  return {};
}

}  // namespace

expected<RepoRestoreRow> restore_entry(
    const Git& git, const RepoEntry& entry,
    const std::filesystem::path& partial_root,
    const std::filesystem::path& stage_root) {
  RepoRestoreRow row;
  row.id = entry.id;
  row.relpath = entry.relpath;
  row.sha = entry.sha;
  row.capture_mode = entry.capture_mode;
  append_note_advisories(entry, row);

  if (entry.head_state == HeadState::unborn && !entry.bundle &&
      !entry.eligibility) {
    row.outcome = RepoRestoreOutcome::payload_only_unborn;
    row.advisories.push_back("EmptyRepoPayloadOnly");
    return row;
  }
  if (entry.shallow) {
    row.outcome = RepoRestoreOutcome::shallow_pointer;
    row.shallow = entry.shallow;
    return row;
  }

  const auto root_repo = entry.relpath.empty() || entry.relpath.lexically_normal() == ".";
  const auto final_target = root_repo ? partial_root : partial_root / entry.relpath;
  const auto target = root_repo
                          ? stage_root / ("repo-materialize-" + entry.id)
                          : final_target;
  if (std::filesystem::exists(target)) {
    return std::unexpected(
        restore_error(entry, "clone", "materialization target already exists"));
  }
  if (auto parents = make_directories(target.parent_path(), entry); !parents) {
    return std::unexpected(parents.error());
  }

  if (entry.head_state == HeadState::unborn && entry.bundle) {
    if (auto created = make_directories(target, entry); !created) {
      return std::unexpected(created.error());
    }
    if (auto initialized = require_success(git, target, {"init"}, {}, entry, "clone");
        !initialized) {
      return std::unexpected(initialized.error());
    }
    if (auto imported = import_bundle_closure(git, target,
                                              stage_root / *entry.bundle, entry);
        !imported) {
      return std::unexpected(imported.error());
    }
    auto refs = recreate_refs(git, target, entry);
    if (!refs) {
      return std::unexpected(refs.error());
    }
    row.local_refs = std::move(*refs);
    if (auto head = establish_head(git, target, entry); !head) {
      return std::unexpected(head.error());
    }
    if (auto verified = verify_restored(git, target, entry); !verified) {
      return std::unexpected(verified.error());
    }
    if (root_repo) {
      if (auto finalized = finalize_root_repo(target, partial_root, entry);
          !finalized) {
        return std::unexpected(finalized.error());
      }
    }
    row.outcome = RepoRestoreOutcome::restored;
    return row;
  }

  std::filesystem::path source;
  if (entry.capture_mode == CaptureMode::full) {
    if (!entry.bundle) {
      return std::unexpected(restore_error(entry, "clone", "bundle absent"));
    }
    source = stage_root / *entry.bundle;
    if (!std::filesystem::is_regular_file(source)) {
      return std::unexpected(restore_error(entry, "clone", "missing repo member"));
    }
  } else {
    const auto remote = clone_url(entry);
    if (!remote) {
      return std::unexpected(restore_error(entry, "clone", "remote absent"));
    }
    source = *remote;
  }

  if (auto cloned = require_success(git, partial_root, {"clone", "--no-checkout"},
                                    {source.string(), target.string()}, entry, "clone");
      !cloned) {
    return std::unexpected(cloned.error());
  }
  if (auto remotes = replace_remotes(git, target, entry); !remotes) {
    return std::unexpected(remotes.error());
  }
  if (entry.local_refs_bundle) {
    if (auto imported = import_bundle_closure(
            git, target, stage_root / *entry.local_refs_bundle, entry);
        !imported) {
      return std::unexpected(imported.error());
    }
  }
  if (!entry.sha) {
    return std::unexpected(restore_error(entry, "checkout", "HEAD sha absent"));
  }
  if (auto detached = require_success(git, target,
                                      {"checkout", "--detach", *entry.sha}, {}, entry,
                                      "checkout");
      !detached) {
    return std::unexpected(detached.error());
  }
  auto refs = recreate_refs(git, target, entry);
  if (!refs) {
    return std::unexpected(refs.error());
  }
  row.local_refs = std::move(*refs);
  if (auto head = establish_head(git, target, entry); !head) {
    return std::unexpected(head.error());
  }
  if (auto verified = verify_restored(git, target, entry); !verified) {
    return std::unexpected(verified.error());
  }
  if (root_repo) {
    if (auto finalized = finalize_root_repo(target, partial_root, entry);
        !finalized) {
      return std::unexpected(finalized.error());
    }
  }
  row.outcome = RepoRestoreOutcome::restored;
  return row;
}

}  // namespace biv::repo
