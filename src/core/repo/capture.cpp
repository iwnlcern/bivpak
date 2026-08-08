#include "core/repo/capture.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <limits>
#include <set>
#include <string_view>

#include "core/repo/git_exec.hpp"

namespace biv::repo {
namespace {

constexpr std::size_t kMaxListedRefs = 4096U;
constexpr std::size_t kMaxRefBytes = 1024U;
constexpr std::uint64_t kOmittedSentinel = 9007199254740991ULL;

BivError capture_error(const std::filesystem::path& repo,
                       const std::string_view operation,
                       const EngineErrorKind kind) {
  return make_engine_error(
      kind, repo,
      std::string{engine_error_name(kind)} + ": " + std::string{operation});
}

expected<support::SpawnResult> invoke(const Git& git,
                                      const std::filesystem::path& repo,
                                      std::vector<std::string> args,
                                      std::vector<std::string> operands,
                                      const bool no_lazy_fetch) {
  return invoke_git(git, repo, args, operands,
                    args.empty() ? "git" : args.front(),
                    GitInvokeOptions{.promisor = no_lazy_fetch});
}

expected<void> make_directories(const std::filesystem::path& path) {
  std::error_code error;
  std::filesystem::create_directories(path, error);
  if (error) {
    auto failure =
        make_engine_error(EngineErrorKind::git_invocation_failed, path,
                          "repo capture scratch: " + error.message());
    failure.err_no = error.value();
    return std::unexpected(std::move(failure));
  }
  return {};
}

expected<std::filesystem::path> absolute_capture_path(
    const std::filesystem::path& path) {
  std::error_code error;
  auto absolute = std::filesystem::absolute(path, error);
  if (error || !absolute.is_absolute()) {
    auto failure =
        make_engine_error(EngineErrorKind::git_invocation_failed, path,
                          "repo capture could not make artifact path absolute");
    failure.err_no = error.value();
    return std::unexpected(std::move(failure));
  }
  return absolute.lexically_normal();
}

BivError ref_uncapturable_error(const std::filesystem::path& repo,
                                const std::string& ref) {
  auto error = capture_error(repo, "ref has neither remote nor bundle route",
                             EngineErrorKind::ref_uncapturable);
  error.facts.emplace("repo_relpath", repo.string());
  error.facts.emplace("ref", ref);
  return error;
}

expected<void> require_bundle_source_ref(const Git& git,
                                         const std::filesystem::path& repo,
                                         const LocalRef& ref,
                                         const bool promisor) {
  if (!valid_ref_name(ref.ref) || !valid_object_id(ref.sha)) {
    return std::unexpected(ref_uncapturable_error(repo, ref.ref));
  }
  auto actual =
      invoke_git(git, repo, {"show-ref", "--verify", "--hash"}, {ref.ref},
                 "capture-ref-route", GitInvokeOptions{.promisor = promisor});
  if (!actual) {
    return std::unexpected(actual.error());
  }
  if (actual->exit_code != 0 ||
      trim_git_newline(git_bytes(actual->stdout_bytes)) != ref.sha) {
    return std::unexpected(ref_uncapturable_error(repo, ref.ref));
  }
  return {};
}

expected<void> verify_bundle(const Git& git, const std::filesystem::path& repo,
                             const std::filesystem::path& bundle,
                             const bool promisor) {
  auto verified = invoke_git(
      git, repo, {"bundle", "verify"}, {bundle.string()}, "bundle-verify",
      GitInvokeOptions{.promisor = promisor,
                       .call_class = GitCallClass::bundle});
  if (!verified) {
    return std::unexpected(verified.error());
  }
  if (verified->exit_code != 0) {
    return std::unexpected(git_invocation_failure(
        repo, "bundle-verify", verified->exit_code, "bundle verify failed"));
  }
  return {};
}

std::vector<std::string> parse_ref_names(const std::string& output) {
  std::vector<std::string> refs;
  std::size_t cursor = 0;
  while (cursor < output.size()) {
    const auto end = output.find('\0', cursor);
    auto ref = output.substr(cursor, end - cursor);
    while (!ref.empty() && (ref.front() == '\n' || ref.front() == '\r')) {
      ref.erase(ref.begin());
    }
    if (!ref.empty()) {
      refs.push_back(std::move(ref));
    }
    if (end == std::string::npos) {
      break;
    }
    cursor = end + 1U;
  }
  return refs;
}

expected<void> run_penumbra_oracle(const Git& git, const RepoEntry& entry,
                                   const std::filesystem::path& repo,
                                   const bool no_lazy_fetch,
                                   CaptureResult& result) {
  if (!entry.engine_source) {
    return {};
  }
  auto current =
      snapshot_penumbra(git, repo, GitInvokeOptions{.promisor = no_lazy_fetch});
  if (!current) {
    return std::unexpected(current.error());
  }
  const auto& classified_paths = entry.engine_source->penumbra_paths;
  std::vector<std::filesystem::path> difference;
  std::ranges::set_difference(classified_paths, *current,
                              std::back_inserter(difference));
  for (const auto& path : difference) {
    result.advisories.push_back("capture-loss: " +
                                p1_encode(path.generic_string()));
  }
  difference.clear();
  std::ranges::set_difference(*current, classified_paths,
                              std::back_inserter(difference));
  for (const auto& path : difference) {
    result.advisories.push_back("capture-contamination: " +
                                p1_encode(path.generic_string()));
  }
  return {};
}

bool catch_all_ref(const std::string_view ref) {
  return ref.starts_with("refs/") && !ref.starts_with("refs/heads/") &&
         !ref.starts_with("refs/tags/") && !ref.starts_with("refs/remotes/") &&
         ref != "refs/stash";
}

void replace_non_carried_note(RepoEntry& entry,
                              std::optional<NonCarriedRefsNote> note) {
  std::erase_if(entry.notes, [](const RepoNote& existing) {
    return std::holds_alternative<NonCarriedRefsNote>(existing);
  });
  if (note) {
    entry.notes.emplace_back(std::move(*note));
  }
}

}  // namespace

std::string p1_encode(const std::string_view value) {
  static constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5',
                                            '6', '7', '8', '9', 'a', 'b',
                                            'c', 'd', 'e', 'f'};
  std::string encoded;
  encoded.reserve(value.size());
  for (const unsigned char octet : value) {
    if (octet == '\\') {
      encoded += "\\\\";
    } else if (octet >= 0x20U && octet <= 0x7eU) {
      encoded.push_back(static_cast<char>(octet));
    } else {
      encoded += "\\x";
      encoded.push_back(hex.at(octet >> 4U));
      encoded.push_back(hex.at(octet & 0x0fU));
    }
  }
  return encoded;
}

std::optional<NonCarriedRefsNote> build_non_carried_refs_note(
    const std::span<const std::string> refs,
    const std::optional<std::uint64_t> injected_source_count) {
  const auto source_count = std::max<std::uint64_t>(
      injected_source_count.value_or(refs.size()), refs.size());
  if (source_count == 0U) {
    return std::nullopt;
  }

  std::vector<std::string> eligible;
  eligible.reserve(std::min(refs.size(), kMaxListedRefs));
  for (const auto& ref : refs) {
    if (ref.size() <= kMaxRefBytes) {
      eligible.push_back(ref);
    }
  }
  std::ranges::sort(eligible);
  if (eligible.size() > kMaxListedRefs) {
    eligible.resize(kMaxListedRefs);
  }

  NonCarriedRefsNote note;
  note.refs_p1.reserve(eligible.size());
  for (const auto& ref : eligible) {
    note.refs_p1.push_back(p1_encode(ref));
  }
  const auto exact_omitted = source_count - note.refs_p1.size();
  if (exact_omitted != 0U) {
    note.omitted_count = std::min(exact_omitted, kOmittedSentinel);
  }
  return note;
}

expected<CaptureResult> capture(const Git& git, RepoEntry& entry,
                                const std::filesystem::path& scratch) {
  CaptureResult result;
  const auto repo =
      entry.engine_source ? entry.engine_source->repo_path : entry.relpath;
  const auto promisor = entry.promisor;

  if (auto oracle = run_penumbra_oracle(git, entry, repo, promisor, result);
      !oracle) {
    return std::unexpected(oracle.error());
  }
  if (entry.shallow ||
      (entry.head_state == HeadState::unborn && !entry.eligibility)) {
    return result;
  }
  const auto artifact_directory = scratch / entry.id;
  if (auto created = make_directories(artifact_directory); !created) {
    return std::unexpected(created.error());
  }
  const auto archive_directory = std::filesystem::path{"repos"} / entry.id;

  if (entry.capture_mode == CaptureMode::full) {
    for (const auto& ref : entry.local_refs) {
      if (auto routed = require_bundle_source_ref(git, repo, ref, promisor);
          !routed) {
        return std::unexpected(routed.error());
      }
    }
    auto disk_path = absolute_capture_path(artifact_directory / "repo.bundle");
    if (!disk_path) {
      return std::unexpected(disk_path.error());
    }
    std::vector<std::string> args{"bundle", "create", disk_path->string(),
                                  "--all"};
    auto bundled =
        invoke_git(git, repo, args, {}, "bundle-create-full",
                   GitInvokeOptions{.promisor = promisor,
                                    .call_class = GitCallClass::bundle});
    if (!bundled) {
      return std::unexpected(bundled.error());
    }
    if (bundled->exit_code != 0) {
      return std::unexpected(
          git_invocation_failure(repo, "bundle-create-full", bundled->exit_code,
                                 "bundle create --all failed"));
    }
    if (auto verified = verify_bundle(git, repo, *disk_path, promisor);
        !verified) {
      return std::unexpected(verified.error());
    }
    const auto archive_path = archive_directory / "repo.bundle";
    entry.bundle = archive_path;
    result.artifacts.push_back(
        ArtifactFile{.archive_path = archive_path, .disk_path = *disk_path});

    for (auto& ref : entry.local_refs) {
      ref.availability = RefAvailability::repo_bundle_carried;
      ref.proof.reset();
    }

    auto refs = invoke(git, repo, {"for-each-ref", "--format=%(refname)%00"},
                       {}, promisor);
    if (!refs || refs->exit_code != 0) {
      return std::unexpected(
          refs ? git_invocation_failure(repo, "for-each-ref", refs->exit_code,
                                        "ref inventory failed")
               : refs.error());
    }
    std::vector<std::string> catch_all;
    for (const auto& ref : parse_ref_names(git_bytes(refs->stdout_bytes))) {
      if (ref == "refs/stash") {
        result.advisories.push_back("non-carried ref: refs/stash");
      } else if (catch_all_ref(ref)) {
        catch_all.push_back(ref);
      }
    }
    auto note = build_non_carried_refs_note(catch_all);
    replace_non_carried_note(entry, note);
    if (note) {
      result.advisories.push_back(
          "non-carried refs: listed=" + std::to_string(note->refs_p1.size()) +
          (note->omitted_count
               ? " omitted=" + std::to_string(*note->omitted_count)
               : std::string{}));
    }
    return result;
  }

  std::vector<std::string> carried_refs;
  std::set<std::string> bases;
  if (entry.eligibility && entry.eligibility->proof && entry.remote &&
      entry.eligibility->proof->remote == *entry.remote) {
    bases.insert(entry.eligibility->proof->tip_sha);
  }
  for (const auto& ref : entry.local_refs) {
    if (ref.availability == RefAvailability::bundle_carried) {
      if (auto routed = require_bundle_source_ref(git, repo, ref, promisor);
          !routed) {
        return std::unexpected(routed.error());
      }
      carried_refs.push_back(ref.ref);
    } else if (ref.availability == RefAvailability::remote_proven &&
               !ref.proof) {
      return std::unexpected(ref_uncapturable_error(repo, ref.ref));
    }
    if (ref.proof && entry.remote && ref.proof->remote == *entry.remote) {
      bases.insert(ref.proof->tip_sha);
    }
  }
  if (carried_refs.empty()) {
    return result;
  }

  auto disk_path =
      absolute_capture_path(artifact_directory / "local-refs.bundle");
  if (!disk_path) {
    return std::unexpected(disk_path.error());
  }
  std::vector<std::string> args{"bundle", "create", disk_path->string()};
  args.insert(args.end(), carried_refs.begin(), carried_refs.end());
  for (const auto& base : bases) {
    if (!valid_object_id(base)) {
      return std::unexpected(capture_error(
          repo, "thin bundle base", EngineErrorKind::git_invocation_failed));
    }
    args.push_back("^" + base);
  }
  auto bundled =
      invoke_git(git, repo, args, {}, "bundle-create-thin",
                 GitInvokeOptions{.promisor = promisor,
                                  .call_class = GitCallClass::bundle});
  if (!bundled) {
    return std::unexpected(bundled.error());
  }
  if (bundled->exit_code != 0) {
    return std::unexpected(git_invocation_failure(repo, "bundle-create-thin",
                                                  bundled->exit_code,
                                                  "thin bundle create failed"));
  }
  if (auto verified = verify_bundle(git, repo, *disk_path, promisor);
      !verified) {
    return std::unexpected(verified.error());
  }
  const auto archive_path = archive_directory / "local-refs.bundle";
  entry.local_refs_bundle = archive_path;
  result.artifacts.push_back(
      ArtifactFile{.archive_path = archive_path, .disk_path = *disk_path});
  return result;
}

}  // namespace biv::repo
