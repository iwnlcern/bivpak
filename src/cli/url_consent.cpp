#include "cli/url_consent.hpp"

#include <array>
#include <istream>
#include <ostream>
#include <unistd.h>

#include "cli/consent_display_table.hpp"
#include "core/support/probe.hpp"

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
