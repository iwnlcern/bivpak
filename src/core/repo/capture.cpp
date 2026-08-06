#include "core/repo/capture.hpp"

#include <algorithm>
#include <array>
#include <limits>
#include <set>
#include <string_view>

namespace biv::repo {
namespace {

constexpr std::size_t kMaxListedRefs = 4096U;
constexpr std::size_t kMaxRefBytes = 1024U;
constexpr std::uint64_t kOmittedSentinel = 9007199254740991ULL;

BivError capture_error(const std::filesystem::path& repo,
                       const std::string_view operation,
                       const bool promisor = false) {
  return BivError{
      ErrKind::InternalError, repo,
      promisor ? "PromisorObjectsUnavailable: " + std::string{operation}
               : "repo capture git invocation failed: " + std::string{operation}};
}

std::string bytes(const std::vector<std::byte>& value) {
  return {reinterpret_cast<const char*>(value.data()), value.size()};
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
    return std::unexpected(
        capture_error(repo, args.empty() ? "git" : args.front(), no_lazy_fetch));
  }
  return result;
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
  return result->exit_code == 0 && promisor_enabled(bytes(result->stdout_bytes));
}

expected<void> make_directories(const std::filesystem::path& path) {
  std::error_code error;
  std::filesystem::create_directories(path, error);
  if (error) {
    return std::unexpected(BivError{ErrKind::InternalError, path,
                                    "repo capture scratch: " + error.message(),
                                    error.value()});
  }
  return {};
}

expected<void> verify_bundle(const Git& git, const std::filesystem::path& repo,
                             const std::filesystem::path& bundle,
                             const bool promisor) {
  auto verified = invoke(git, repo, {"bundle", "verify"}, {bundle.string()},
                         promisor);
  if (!verified) {
    return std::unexpected(verified.error());
  }
  if (verified->exit_code != 0) {
    return std::unexpected(capture_error(repo, "bundle verify", promisor));
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

bool catch_all_ref(const std::string_view ref) {
  return ref.starts_with("refs/") && !ref.starts_with("refs/heads/") &&
         !ref.starts_with("refs/tags/") &&
         !ref.starts_with("refs/remotes/") && ref != "refs/stash";
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
  static constexpr std::array<char, 16> hex{
      '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string encoded;
  encoded.reserve(value.size());
  for (const unsigned char octet : value) {
    if (octet == '\\') {
      encoded += "\\\\";
    } else if (octet >= 0x20U && octet <= 0x7eU) {
      encoded.push_back(static_cast<char>(octet));
    } else {
      encoded += "\\x";
      encoded.push_back(hex[octet >> 4U]);
      encoded.push_back(hex[octet & 0x0fU]);
    }
  }
  return encoded;
}

std::optional<NonCarriedRefsNote> build_non_carried_refs_note(
    const std::span<const std::string> refs,
    const std::optional<std::uint64_t> injected_source_count) {
  const auto source_count =
      std::max<std::uint64_t>(injected_source_count.value_or(refs.size()),
                              refs.size());
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
  if (entry.shallow ||
      (entry.head_state == HeadState::unborn && !entry.eligibility)) {
    return result;
  }

  auto promisor = detect_promisor(git, entry.relpath);
  if (!promisor) {
    return std::unexpected(promisor.error());
  }
  const auto artifact_directory = scratch / entry.id;
  if (auto created = make_directories(artifact_directory); !created) {
    return std::unexpected(created.error());
  }
  const auto archive_directory = std::filesystem::path{"repos"} / entry.id;

  if (entry.capture_mode == CaptureMode::full) {
    const auto disk_path = artifact_directory / "repo.bundle";
    std::vector<std::string> args{"bundle", "create", disk_path.string(), "--all"};
    auto bundled = invoke(git, entry.relpath, std::move(args), {}, *promisor);
    if (!bundled) {
      return std::unexpected(bundled.error());
    }
    if (bundled->exit_code != 0) {
      return std::unexpected(capture_error(entry.relpath, "bundle create --all",
                                           *promisor));
    }
    if (auto verified = verify_bundle(git, entry.relpath, disk_path, *promisor);
        !verified) {
      return std::unexpected(verified.error());
    }
    const auto archive_path = archive_directory / "repo.bundle";
    entry.bundle = archive_path;
    result.artifacts.push_back(
        ArtifactFile{.archive_path = archive_path, .disk_path = disk_path});

    for (auto& ref : entry.local_refs) {
      ref.availability = RefAvailability::repo_bundle_carried;
      ref.proof.reset();
    }

    auto refs = invoke(git, entry.relpath,
                       {"for-each-ref", "--format=%(refname)%00"}, {}, *promisor);
    if (!refs || refs->exit_code != 0) {
      return std::unexpected(refs ? capture_error(entry.relpath, "for-each-ref",
                                                  *promisor)
                                  : refs.error());
    }
    std::vector<std::string> catch_all;
    for (const auto& ref : parse_ref_names(bytes(refs->stdout_bytes))) {
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
  if (entry.eligibility && entry.eligibility->proof) {
    bases.insert(entry.eligibility->proof->tip_sha);
  }
  for (const auto& ref : entry.local_refs) {
    if (ref.availability == RefAvailability::bundle_carried) {
      carried_refs.push_back(ref.ref);
    }
    if (ref.proof) {
      bases.insert(ref.proof->tip_sha);
    }
  }
  if (carried_refs.empty()) {
    return result;
  }

  const auto disk_path = artifact_directory / "local-refs.bundle";
  std::vector<std::string> args{"bundle", "create", disk_path.string()};
  args.insert(args.end(), carried_refs.begin(), carried_refs.end());
  for (const auto& base : bases) {
    args.push_back("^" + base);
  }
  auto bundled = invoke(git, entry.relpath, std::move(args), {}, *promisor);
  if (!bundled) {
    return std::unexpected(bundled.error());
  }
  if (bundled->exit_code != 0) {
    return std::unexpected(
        capture_error(entry.relpath, "thin bundle create", *promisor));
  }
  if (auto verified = verify_bundle(git, entry.relpath, disk_path, *promisor);
      !verified) {
    return std::unexpected(verified.error());
  }
  const auto archive_path = archive_directory / "local-refs.bundle";
  entry.local_refs_bundle = archive_path;
  result.artifacts.push_back(
      ArtifactFile{.archive_path = archive_path, .disk_path = disk_path});
  return result;
}

}  // namespace biv::repo
