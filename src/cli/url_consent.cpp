#include "cli/url_consent.hpp"

#include <array>
#include <istream>
#include <ostream>
#include <unistd.h>

#include "cli/consent_display_table.hpp"
#include "core/support/probe.hpp"
#include "core/repo/restore.hpp"

namespace biv::cli {

namespace {

struct Scalar {
  char32_t value;
  std::size_t width;
};

Scalar decode_scalar(const std::string_view value, const std::size_t offset) {
  const auto lead = static_cast<unsigned char>(value.at(offset));
  if (lead < 0x80U) {
    return {.value = lead, .width = 1};
  }

  const auto continuation = [&value](const std::size_t index) {
    return static_cast<char32_t>(
        static_cast<unsigned char>(value.at(index)) & 0x3fU);
  };
  if (lead < 0xe0U) {
    return {.value = ((lead & 0x1fU) << 6U) | continuation(offset + 1),
            .width = 2};
  }
  if (lead < 0xf0U) {
    return {.value = ((lead & 0x0fU) << 12U) |
                     (continuation(offset + 1) << 6U) |
                     continuation(offset + 2),
            .width = 3};
  }
  return {.value = ((lead & 0x07U) << 18U) |
                   (continuation(offset + 1) << 12U) |
                   (continuation(offset + 2) << 6U) |
                   continuation(offset + 3),
          .width = 4};
}

constexpr std::array<char, 16> kLowerHex{
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void append_u00(std::string& out, const char32_t value) {
  out += "\\u00";
  out.push_back(kLowerHex.at((value >> 4U) & 0x0fU));
  out.push_back(kLowerHex.at(value & 0x0fU));
}

void append_braced(std::string& out, char32_t value) {
  std::array<char, 6> reversed{};
  std::size_t count = 0;
  do {
    reversed.at(count++) = kLowerHex.at(value & 0x0fU);
    value >>= 4U;
  } while (value != 0);

  out += "\\u{";
  while (count > 0) {
    out.push_back(reversed.at(--count));
  }
  out.push_back('}');
}

}  // namespace

bool interactive_url_hook_installable() {
  return ::isatty(STDIN_FILENO) != 0 && ::isatty(STDERR_FILENO) != 0;
}

std::string consent_display(const std::string_view value) {
  const auto sanitized = support::sanitize_utf8(value);
  std::string out;
  for (std::size_t offset = 0; offset < sanitized.size();) {
    const auto scalar = decode_scalar(sanitized, offset);
    if (scalar.value == U'\n') {
      out += "\\n";
    } else if (scalar.value == U'\r') {
      out += "\\r";
    } else if (scalar.value == U'\t') {
      out += "\\t";
    } else if (scalar.value <= 0x1fU || scalar.value == 0x7fU ||
               (scalar.value >= 0x80U && scalar.value <= 0x9fU)) {
      append_u00(out, scalar.value);
    } else if (consent_display_active(scalar.value)) {
      append_braced(out, scalar.value);
    } else {
      out.append(sanitized, offset, scalar.width);
    }
    offset += scalar.width;
  }
  return out;
}

std::string render_prompt_d(const UrlDivergenceFacts& facts) {
  return "  " + consent_display(facts.op) +
         ": the address git will contact for " + consent_display(facts.repo) +
         " differs from the requested address:\n"
         "    requested: " + consent_display(facts.requested) + "\n"
         "    effective: " + consent_display(facts.effective) + "\n"
         "  Contact the effective address? [y/N] ";
}

std::string render_accepted_notice(const UrlDivergenceFacts& facts) {
  return "  " + consent_display(facts.op) + ": contacting " +
         consent_display(facts.effective) + " for " +
         consent_display(facts.repo) + " (requested: " +
         consent_display(facts.requested) + " — accepted for this run)\n";
}

std::string render_pack_refusal_detail(const UrlDivergenceFacts& facts) {
  return "pack refused: " + consent_display(facts.op) + " for " +
         consent_display(facts.repo) + " would contact " +
         consent_display(facts.effective) + " instead of the requested " +
         consent_display(facts.requested) +
         "; approval was not given. Re-run interactively to review, or pass "
         "--accept-url-divergence to proceed.";
}

std::string render_unclaimed_git_entry_detail(const std::string_view path,
                                              const std::string_view reason) {
  return "pack refused: " + consent_display(path) +
         " is a .git-named entry that is not a repository boundary (" +
         consent_display(reason) + "); remove or repair it and re-run.";
}

std::string render_engine_refusal_detail(
    const ErrKind kind, const std::map<std::string, std::string>& facts) {
  const auto raw = [&](const std::string_view key,
                       const std::string_view fallback = "") -> std::string {
    const auto found = facts.find(std::string{key});
    return found == facts.end() ? std::string{fallback} : found->second;
  };
  const auto shown = [&](const std::string_view key,
                         const std::string_view fallback = "") {
    return consent_display(raw(key, fallback));
  };
  const auto repo = shown("repo_relpath", "(repository)");
  const auto op = shown("op", "call");
  const bool open = raw("verb") == "open";
  switch (kind) {
    case ErrKind::RepoDirtyUnsupported:
      return "pack refused: " + repo + " has uncommitted changes; this build captures clean repositories only. Commit or stash the changes, or declare the path in .bivignore, and re-run.";
    case ErrKind::RepoNestedUnsupported:
      return "pack refused: " + repo + " contains a nested repository at " + shown("child") + "; this build captures single repositories only. Declare " + shown("child") + " in .bivignore, and re-run.";
    case ErrKind::RepoSubmoduleUnsupported:
      return "pack refused: " + repo + " has a submodule at " + shown("gitlink") + "; this build captures repositories without submodules only. Declare " + shown("gitlink") + " in .bivignore, and re-run.";
    case ErrKind::UnmergedIndexUnrepresentable: {
      const auto count = raw("unmerged_count", "0");
      std::vector<std::string> paths;
      std::string all = raw("unmerged_paths");
      for (std::size_t start = 0; start <= all.size() && paths.size() < 3;) {
        const auto end = all.find('\n', start);
        paths.push_back(consent_display(all.substr(start, end - start)));
        if (end == std::string::npos) break;
        start = end + 1;
      }
      std::string list;
      for (std::size_t index = 0; index < paths.size(); ++index) {
        if (index != 0) list += ", ";
        list += paths[index];
      }
      std::size_t total = 0;
      try { total = static_cast<std::size_t>(std::stoull(count)); } catch (...) {}
      if (total > 3) list += " and " + std::to_string(total - 3) + " more";
      return "pack refused: " + repo + " has an unmerged index (" + consent_display(count) + " paths: " + list + "); an in-progress merge cannot be represented. Resolve or abort the merge and re-run.";
    }
    case ErrKind::RefUncapturable:
      return "pack refused: " + repo + " ref " + shown("ref") + " has neither a remote nor a bundle route; the image would lose it. Push or remove the ref and re-run.";
    case ErrKind::PromisorObjectsUnavailable:
      return "pack refused: " + repo + " is a partial clone whose objects are unavailable (git " + op + " exit " + shown("exit_code") + (raw("offline") == "true" ? ", offline" : "") + "); the image would be incomplete. Fetch the missing objects, or re-run without --offline, and re-run.";
    case ErrKind::GitInvocationFailed:
      return open ? "open failed while restoring " + repo + ": git " + op + " did not complete (" + shown("engine_detail") + ")."
                  : "pack failed: git " + op + " for " + repo + " did not complete (" + shown("engine_detail") + "); no image was written.";
    case ErrKind::GitBudgetExpired:
      return open ? "open failed while restoring " + repo + ": git " + op + " exceeded the call budget."
                  : "pack failed: git " + op + " for " + repo + " exceeded the call budget; no image was written.";
    case ErrKind::RepoRestoreFailed: {
      std::string detail = raw("engine_detail");
      constexpr std::string_view prefix = "RepoRestoreFailed: ";
      if (detail.starts_with(prefix)) detail.erase(0, prefix.size());
      return "open failed while restoring " + repo + ": " + consent_display(detail) + ".";
    }
    default:
      return {};
  }
}

std::string render_entry_refusal_line(std::string_view relpath,
                                      const UrlDivergenceFacts& facts) {
  return "  " + consent_display(relpath) + ": restore failed — " +
         consent_display(facts.op) + " would contact " +
         consent_display(facts.effective) + " instead of the requested " +
         consent_display(facts.requested) + "; approval was not given.\n";
}

std::string render_run_guidance_line(std::size_t refused_count) {
  return "  open: " + std::to_string(refused_count) +
         " restore entry(ies) refused — the effective address was not approved. "
         "Re-run interactively to review, or pass --accept-url-divergence to proceed.\n";
}

std::string render_offline_header() {
  return "open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.\n";
}

std::string render_offline_row(const std::string_view relpath,
                                const std::optional<std::string>& branch,
                                const std::string_view sha,
                                const std::vector<std::string>& remotes) {
  auto out = consent_display(relpath) + " · " +
             consent_display(branch.value_or("(detached)")) + " · " + consent_display(sha) + " · ";
  if (remotes.empty()) out += "(no stored remote)";
  for (std::size_t index = 0; index < remotes.size(); ++index) {
    if (index != 0) out += ", ";
    out += consent_display(remotes.at(index));
  }
  return out + '\n';
}

std::string render_network_consent(const std::vector<repo::RepoEntry>& entries,
                                   const bool include_prompt) {
  std::string out =
      "Opening this image will run git to clone/fetch its repositories. This is git clone-grade trust — only open images you trust.\n"
      "  manifest/stored URLs (informational):\n";
  for (const auto& entry : entries) {
    if (!repo::restore_invokes_git(entry)) continue;
    out += "    " + consent_display(entry.relpath.generic_string()) + " · ";
    if (entry.remotes.empty()) {
      out += "(no stored remote)";
    } else {
      for (std::size_t index = 0; index < entry.remotes.size(); ++index) {
        if (index != 0) out += ", ";
        out += consent_display(entry.remotes.at(index).url);
      }
    }
    out += '\n';
  }
  out +=
      "  git may contact ADDITIONAL URLs found in repo metadata (.gitmodules, nested submodules, or host git config) that Bivpak does not see or police.\n"
      "Run `biv open --offline` to open with zero network access — files + sessions only, repos listed for manual clone.\n";
  if (include_prompt) out += "Run git for these repositories? [y/N] ";
  return out;
}

std::string render_offline_bundle_row(
    const std::string_view relpath, const std::string_view absolute_bundle_path,
    const std::optional<std::string>& reconstruct) {
  const auto prefix = consent_display(relpath) + ": ";
  constexpr std::string_view suffix =
      "   (partial/manual reconstruction — not a full restore)\n";
  if (reconstruct) return prefix + *reconstruct + std::string{suffix};
  return prefix + "bundle at " + consent_display(absolute_bundle_path) +
         " — no copy-paste command: the path or branch carries characters a shell line cannot carry faithfully; reconstruct by hand from the bundle" +
         std::string{suffix};
}

bool prompt_url_divergence(const UrlDivergenceFacts& facts, std::istream& in,
                           std::ostream& err) {
  err << render_prompt_d(facts);
  std::string answer;
  if (!std::getline(in, answer)) {
    return false;
  }
  return answer == "y" || answer == "Y";
}

}  // namespace biv::cli
