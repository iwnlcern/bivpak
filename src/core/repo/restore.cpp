#include "core/repo/restore.hpp"

#include <algorithm>
#include <string_view>

#include "core/repo/git_exec.hpp"

namespace biv::repo {
namespace {

// The two views are named domain values at every private call site.
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
BivError restore_error(const RepoEntry &entry, const std::string_view step,
                       const std::string_view detail = {}) {
  auto message = "RepoRestoreFailed: " + std::string{step};
  if (!detail.empty()) {
    message += ": " + std::string{detail};
  }
  return make_engine_error(EngineErrorKind::repo_restore_failed, entry.relpath,
                           std::move(message));
}

expected<support::SpawnResult>
restore_invoke(const Git &git, const std::filesystem::path &repo,
               std::vector<std::string> args,
               std::vector<std::string> operands = {},
               const GitCallClass call_class = GitCallClass::local,
               const bool allow_user_protocol = false,
               std::optional<std::string> requested_endpoint = std::nullopt) {
  const auto operation = args.empty() ? std::string{"git"} : args.front();
  return invoke_git(
      git, repo, args, operands, operation,
      GitInvokeOptions{
          .promisor = false,
          .restore = true,
          .allow_user_protocol = allow_user_protocol,
          .call_class = call_class,
          .requested_endpoints =
              requested_endpoint
                  ? std::vector<std::string>{std::move(*requested_endpoint)}
                  : std::vector<std::string>{}});
}

expected<void>
require_success(const Git &git, const std::filesystem::path &repo,
                std::vector<std::string> args,
                std::vector<std::string> operands, const RepoEntry &entry,
                const std::string_view step,
                const GitCallClass call_class = GitCallClass::local,
                const bool allow_user_protocol = false,
                std::optional<std::string> requested_endpoint = std::nullopt) {
  auto result = restore_invoke(git, repo, std::move(args), std::move(operands),
                               call_class, allow_user_protocol,
                               std::move(requested_endpoint));
  if (!result) {
    if (engine_error_kind(result.error()) ==
        EngineErrorKind::url_divergence_refused) {
      auto refusal = result.error();
      refusal.path = entry.relpath.string();
      refusal.facts.emplace("repo_id", entry.id);
      refusal.facts.emplace("relpath", entry.relpath.string());
      return std::unexpected(std::move(refusal));
    }
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    auto detail = trim_git_newline(git_bytes(result->stderr_bytes));
    if (detail.empty()) {
      detail = trim_git_newline(git_bytes(result->stdout_bytes));
    }
    if (detail.empty()) {
      detail = "exit " + std::to_string(result->exit_code);
    }
    return std::unexpected(restore_error(entry, step, detail));
  }
  return {};
}

expected<void> make_directories(const std::filesystem::path &path,
                                const RepoEntry &entry) {
  std::error_code error;
  std::filesystem::create_directories(path, error);
  if (error) {
    return std::unexpected(
        restore_error(entry, "clone", "mkdir: " + error.message()));
  }
  return {};
}

bool path_exists(const std::filesystem::path &path, std::error_code &error) {
  error.clear();
  return std::filesystem::exists(path, error);
}

expected<void> validate_entry(const RepoEntry &entry) {
  if (!valid_manifest_path(entry.relpath, true)) {
    return std::unexpected(
        restore_error(entry, "clone", "unsafe repo relpath"));
  }
  for (const auto *member :
       {entry.bundle ? &*entry.bundle : nullptr,
        entry.local_refs_bundle ? &*entry.local_refs_bundle : nullptr}) {
    if (member != nullptr && !valid_manifest_path(*member)) {
      return std::unexpected(
          restore_error(entry, "clone", "unsafe repo member path"));
    }
  }
  if (entry.sha && !valid_object_id(*entry.sha)) {
    return std::unexpected(
        restore_error(entry, "checkout", "invalid HEAD object id"));
  }
  if (entry.branch && (entry.branch->empty() || entry.branch->front() == '-' ||
                       !valid_ref_name("refs/heads/" + *entry.branch))) {
    return std::unexpected(
        restore_error(entry, "checkout", "invalid branch name"));
  }
  if (entry.eligibility && entry.eligibility->proof &&
      (!valid_ref_name(entry.eligibility->proof->ref) ||
       !valid_object_id(entry.eligibility->proof->tip_sha))) {
    return std::unexpected(
        restore_error(entry, "clone", "invalid eligibility proof"));
  }
  for (const auto &ref : entry.local_refs) {
    if (!valid_ref_name(ref.ref) || !valid_object_id(ref.sha)) {
      return std::unexpected(
          restore_error(entry, "ref-recreation", "invalid ref record"));
    }
    if (ref.proof && (!valid_ref_name(ref.proof->ref) ||
                      !valid_object_id(ref.proof->tip_sha))) {
      return std::unexpected(
          restore_error(entry, "ref-recreation", "invalid ref proof"));
    }
  }
  return {};
}

expected<std::filesystem::path>
contained_member(const std::filesystem::path &stage_root,
                 const std::filesystem::path &relative,
                 const RepoEntry &entry) {
  std::error_code root_error;
  const auto root = std::filesystem::weakly_canonical(stage_root, root_error);
  std::error_code member_error;
  const auto member =
      std::filesystem::weakly_canonical(stage_root / relative, member_error);
  const auto relative_to_root = member.lexically_relative(root);
  if (root_error || member_error || relative_to_root.empty() ||
      relative_to_root.is_absolute() ||
      std::ranges::any_of(relative_to_root, [](const auto &component) {
        return component == "..";
      })) {
    return std::unexpected(
        restore_error(entry, "clone", "repo member escapes stage"));
  }
  return member;
}

std::optional<std::string> clone_url(const RepoEntry &entry) {
  if (entry.remote) {
    const auto selected =
        std::ranges::find_if(entry.remotes, [&](const auto &remote) {
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

expected<void> replace_remotes(const Git &git,
                               const std::filesystem::path &target,
                               const RepoEntry &entry) {
  auto removed = restore_invoke(git, target, {"remote", "remove"}, {"origin"});
  if (!removed) {
    return std::unexpected(removed.error());
  }
  for (const auto &remote : entry.remotes) {
    if (auto added = require_success(git, target, {"remote", "add"},
                                     {remote.name, remote.url}, entry, "clone");
        !added) {
      return added;
    }
  }
  return {};
}

expected<void> import_bundle_closure(const Git &git,
                                     const std::filesystem::path &target,
                                     const std::filesystem::path &bundle,
                                     const RepoEntry &entry) {
  std::error_code status_error;
  if (!std::filesystem::is_regular_file(bundle, status_error) || status_error) {
    return std::unexpected(
        restore_error(entry, "clone", "missing repo member"));
  }
  return require_success(git, target, {"bundle", "unbundle"}, {bundle.string()},
                         entry, "clone", GitCallClass::bundle, true);
}

expected<std::optional<std::string>>
current_ref(const Git &git, const std::filesystem::path &target,
            const std::string &ref) {
  auto result =
      restore_invoke(git, target, {"show-ref", "--verify", "--quiet"}, {ref});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code == 1) {
    return std::optional<std::string>{};
  }
  if (result->exit_code != 0) {
    return std::unexpected(
        make_engine_error(EngineErrorKind::git_invocation_failed, target,
                          "repo restore ref query failed"));
  }
  result =
      restore_invoke(git, target, {"show-ref", "--verify", "--hash=40"}, {ref});
  if (!result) {
    return std::unexpected(result.error());
  }
  if (result->exit_code != 0) {
    return std::unexpected(
        make_engine_error(EngineErrorKind::git_invocation_failed, target,
                          "repo restore ref read failed"));
  }
  return std::optional<std::string>{
      trim_git_newline(git_bytes(result->stdout_bytes))};
}

expected<void> ensure_object(const Git &git,
                             const std::filesystem::path &target,
                             const LocalRef &ref, const RepoEntry &entry) {
  auto present = restore_invoke(git, target, {"cat-file", "-e"}, {ref.sha});
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
  if (auto fetched = require_success(
          git, target, {"fetch", "--no-tags"}, {ref.proof->url, ref.proof->ref},
          entry, "ref-recreation", GitCallClass::network, true, ref.proof->url);
      !fetched) {
    return fetched;
  }
  present = restore_invoke(git, target, {"cat-file", "-e"}, {ref.sha});
  if (!present || present->exit_code != 0) {
    return std::unexpected(present ? restore_error(entry, "ref-recreation",
                                                   "fetched object absent")
                                   : present.error());
  }
  return {};
}

expected<std::vector<LocalRefRestoreRow>>
recreate_refs(const Git &git, const std::filesystem::path &target,
              const RepoEntry &entry) {
  std::vector<LocalRefRestoreRow> rows;
  rows.reserve(entry.local_refs.size());
  for (const auto &ref : entry.local_refs) {
    LocalRefRestoreRow row{.ref = ref.ref,
                           .recreated = false,
                           .skipped_at_sha = false,
                           .detail = std::nullopt};
    auto existing = current_ref(git, target, ref.ref);
    if (!existing) {
      row.detail = existing.error().detail;
      rows.push_back(std::move(row));
      continue;
    }
    if (*existing && **existing == ref.sha) {
      row.recreated = true;
      row.skipped_at_sha = true;
      rows.push_back(std::move(row));
      continue;
    }
    if (auto available = ensure_object(git, target, ref, entry); !available) {
      if (engine_error_kind(available.error()) ==
          EngineErrorKind::url_divergence_refused) {
        return std::unexpected(available.error());
      }
      row.detail = available.error().detail;
      rows.push_back(std::move(row));
      continue;
    }
    if (auto updated =
            require_success(git, target, {"update-ref", ref.ref, ref.sha}, {},
                            entry, "ref-recreation");
        !updated) {
      row.detail = updated.error().detail;
      rows.push_back(std::move(row));
      continue;
    }
    row.recreated = true;
    rows.push_back(std::move(row));
  }
  return rows;
}

expected<void> establish_head(const Git &git,
                              const std::filesystem::path &target,
                              const RepoEntry &entry) {
  if (entry.head_state == HeadState::unborn) {
    if (!entry.branch) {
      return std::unexpected(
          restore_error(entry, "checkout", "unborn branch absent"));
    }
    return require_success(
        git, target, {"symbolic-ref", "HEAD", "refs/heads/" + *entry.branch},
        {}, entry, "checkout");
  }
  if (!entry.sha) {
    return std::unexpected(restore_error(entry, "checkout", "HEAD sha absent"));
  }
  if (entry.head_state == HeadState::detached) {
    return require_success(git, target, {"checkout", "--detach", *entry.sha},
                           {}, entry, "checkout");
  }
  if (!entry.branch) {
    return std::unexpected(restore_error(entry, "checkout", "branch absent"));
  }
  return require_success(
      git, target, {"checkout", "--force", "-B", *entry.branch, *entry.sha}, {},
      entry, "checkout");
}

expected<void> verify_restored(const Git &git,
                               const std::filesystem::path &target,
                               const RepoEntry &entry, const bool root_repo) {
  for (const auto &ref : entry.local_refs) {
    auto actual = current_ref(git, target, ref.ref);
    if (!actual || !*actual || **actual != ref.sha) {
      return std::unexpected(
          restore_error(entry, "ref-recreation", "verification: " + ref.ref));
    }
  }
  if (entry.head_state == HeadState::unborn) {
    auto symbolic = restore_invoke(git, target, {"symbolic-ref", "HEAD"});
    const auto expected_ref = entry.branch ? "refs/heads/" + *entry.branch : "";
    if (!symbolic || symbolic->exit_code != 0 ||
        trim_git_newline(git_bytes(symbolic->stdout_bytes)) != expected_ref) {
      return std::unexpected(
          symbolic
              ? restore_error(entry, "checkout", "HEAD symref verification")
              : symbolic.error());
    }
    return {};
  }

  auto head = restore_invoke(git, target, {"rev-parse", "HEAD"});
  if (!head || head->exit_code != 0 ||
      trim_git_newline(git_bytes(head->stdout_bytes)) != entry.sha) {
    return std::unexpected(
        head ? restore_error(entry, "checkout", "HEAD verification")
             : head.error());
  }
  auto status =
      root_repo
          ? restore_invoke(git, target, {"status", "--porcelain=v2", "-z"},
                           {".", ":(exclude).biv-stage"})
          : restore_invoke(git, target, {"status", "--porcelain=v2", "-z"});
  if (!status || status->exit_code != 0 || !status->stdout_bytes.empty()) {
    return std::unexpected(
        status ? restore_error(entry, "checkout", "worktree verification")
               : status.error());
  }
  return {};
}

void append_note_advisories(const RepoEntry &entry, RepoRestoreRow &row) {
  for (const auto &note : entry.notes) {
    if (const auto *refs = std::get_if<NonCarriedRefsNote>(&note)) {
      auto advisory =
          "non-carried refs: listed=" + std::to_string(refs->refs_p1.size());
      if (refs->omitted_count) {
        advisory += " omitted=" + std::to_string(*refs->omitted_count);
      }
      row.advisories.push_back(std::move(advisory));
    }
  }
}

void append_ref_warnings(RepoRestoreRow &row) {
  for (const auto &ref : row.local_refs) {
    if (ref.detail) {
      row.advisories.push_back("local-ref-failed: " + ref.ref + ": " +
                               *ref.detail);
    }
  }
}

expected<void>
initialize_root_base(const Git &git, const std::filesystem::path &target,
                     const RepoEntry &entry,
                     const std::optional<std::filesystem::path> &bundle) {
  if (auto initialized =
          require_success(git, target, {"init"}, {}, entry, "clone");
      !initialized) {
    return initialized;
  }
  if (bundle) {
    return import_bundle_closure(git, target, *bundle, entry);
  }
  if (!entry.eligibility || !entry.eligibility->proof) {
    return std::unexpected(
        restore_error(entry, "clone", "overlay proof absent"));
  }
  return require_success(
      git, target, {"fetch", "--no-tags"},
      {entry.eligibility->proof->url, entry.eligibility->proof->ref}, entry,
      "clone", GitCallClass::network, true, entry.eligibility->proof->url);
}

} // namespace

expected<RepoRestoreRow> restore_entry(
    const Git &git, const RepoEntry &entry,
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters): stable public API.
    const std::filesystem::path &partial_root,
    const std::filesystem::path &stage_root) {
  if (auto valid = validate_entry(entry); !valid) {
    return std::unexpected(valid.error());
  }

  RepoRestoreRow row{.id = entry.id,
                     .relpath = entry.relpath,
                     .outcome = RepoRestoreOutcome::failed,
                     .sha = entry.sha,
                     .capture_mode = entry.capture_mode,
                     .local_refs = {},
                     .advisories = {},
                     .shallow = std::nullopt};
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

  std::optional<std::filesystem::path> bundle;
  if (entry.bundle) {
    auto contained = contained_member(stage_root, *entry.bundle, entry);
    if (!contained) {
      return std::unexpected(contained.error());
    }
    bundle = *contained;
  }
  std::optional<std::filesystem::path> local_refs_bundle;
  if (entry.local_refs_bundle) {
    auto contained =
        contained_member(stage_root, *entry.local_refs_bundle, entry);
    if (!contained) {
      return std::unexpected(contained.error());
    }
    local_refs_bundle = *contained;
  }

  const auto root_repo = entry.relpath == ".";
  const auto target = root_repo ? partial_root : partial_root / entry.relpath;
  std::error_code target_error;
  if ((!root_repo && path_exists(target, target_error)) || target_error) {
    return std::unexpected(
        restore_error(entry, "clone", "materialization target already exists"));
  }
  if (auto parents =
          make_directories(root_repo ? target : target.parent_path(), entry);
      !parents) {
    return std::unexpected(parents.error());
  }

  if (entry.head_state == HeadState::unborn && bundle) {
    if (auto created = make_directories(target, entry); !created) {
      return std::unexpected(created.error());
    }
    if (auto initialized =
            require_success(git, target, {"init"}, {}, entry, "clone");
        !initialized) {
      return std::unexpected(initialized.error());
    }
    if (auto imported = import_bundle_closure(git, target, *bundle, entry);
        !imported) {
      return std::unexpected(imported.error());
    }
    auto refs = recreate_refs(git, target, entry);
    if (!refs) {
      return std::unexpected(refs.error());
    }
    row.local_refs = std::move(*refs);
    append_ref_warnings(row);
    if (auto head = establish_head(git, target, entry); !head) {
      return std::unexpected(head.error());
    }
    if (auto verified = verify_restored(git, target, entry, root_repo);
        !verified) {
      row.advisories.push_back("repo-verify-divergence");
      return row;
    }
    row.outcome = RepoRestoreOutcome::restored;
    return row;
  }

  if (root_repo) {
    if (entry.capture_mode == CaptureMode::full && !bundle) {
      return std::unexpected(restore_error(entry, "clone", "bundle absent"));
    }
    if (auto initialized = initialize_root_base(
            git, target, entry,
            entry.capture_mode == CaptureMode::full ? bundle : std::nullopt);
        !initialized) {
      return std::unexpected(initialized.error());
    }
  } else {
    std::string source;
    if (entry.capture_mode == CaptureMode::full) {
      if (!bundle) {
        return std::unexpected(restore_error(entry, "clone", "bundle absent"));
      }
      source = bundle->string();
    } else {
      const auto remote = clone_url(entry);
      if (!remote) {
        return std::unexpected(restore_error(entry, "clone", "remote absent"));
      }
      source = *remote;
    }
    if (auto cloned = require_success(
            git, partial_root, {"clone", "--no-checkout"},
            {source, target.string()}, entry, "clone",
            entry.capture_mode == CaptureMode::full ? GitCallClass::bundle
                                                    : GitCallClass::network,
            true,
            entry.capture_mode == CaptureMode::overlay
                ? std::optional<std::string>{source}
                : std::nullopt);
        !cloned) {
      return std::unexpected(cloned.error());
    }
  }

  if (auto remotes = replace_remotes(git, target, entry); !remotes) {
    return std::unexpected(remotes.error());
  }
  if (local_refs_bundle) {
    if (auto imported =
            import_bundle_closure(git, target, *local_refs_bundle, entry);
        !imported) {
      return std::unexpected(imported.error());
    }
  }
  if (!entry.sha) {
    return std::unexpected(restore_error(entry, "checkout", "HEAD sha absent"));
  }
  if (auto detached =
          require_success(git, target, {"checkout", "--detach", *entry.sha}, {},
                          entry, "checkout");
      !detached) {
    return std::unexpected(detached.error());
  }
  auto refs = recreate_refs(git, target, entry);
  if (!refs) {
    return std::unexpected(refs.error());
  }
  row.local_refs = std::move(*refs);
  append_ref_warnings(row);
  if (auto head = establish_head(git, target, entry); !head) {
    return std::unexpected(head.error());
  }
  if (auto verified = verify_restored(git, target, entry, root_repo);
      !verified) {
    row.advisories.push_back("repo-verify-divergence");
    return row;
  }
  row.outcome = RepoRestoreOutcome::restored;
  return row;
}

} // namespace biv::repo
