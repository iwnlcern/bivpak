#include "core/open/render.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <sstream>

#include "adapters/version_floor.hpp"

namespace biv::open_render {

namespace {

struct Utf8Scalar {
  std::uint32_t value;
  std::size_t width;
};

Utf8Scalar decode_scalar(const std::string_view value,
                         const std::size_t offset) {
  const auto lead = static_cast<unsigned char>(value.at(offset));
  if (lead < 0x80U) {
    return {.value = lead, .width = 1};
  }

  const auto continuation = [&value](const std::size_t index) {
    return static_cast<std::uint32_t>(
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

void append_control_escape(std::string& out, const std::uint32_t scalar) {
  constexpr std::array<char, 16> hex{
      '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  out += "\\u00";
  out.push_back(hex.at((scalar >> 4U) & 0x0fU));
  out.push_back(hex.at(scalar & 0x0fU));
}

std::string display(std::string_view value) {
  const auto sanitized = support::sanitize_utf8(value);
  std::string out;
  for (std::size_t offset = 0; offset < sanitized.size();) {
    const auto scalar = decode_scalar(sanitized, offset);
    if (scalar.value == '\n') {
      out += "\\n";
    } else if (scalar.value == '\r') {
      out += "\\r";
    } else if (scalar.value == '\t') {
      out += "\\t";
    } else if (scalar.value <= 0x1fU || scalar.value == 0x7fU ||
               (scalar.value >= 0x80U && scalar.value <= 0x9fU)) {
      append_control_escape(out, scalar.value);
    } else {
      out.append(sanitized, offset, scalar.width);
    }
    offset += scalar.width;
  }
  return out;
}

std::string display_path(std::string_view value) {
  constexpr std::array<char, 16> hex{
      '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  for (const unsigned char ch : value) {
    if (ch == ' ') {
      out += "\\x20";
    } else if (ch == '\n') {
      out += "\\n";
    } else if (ch == '\r') {
      out += "\\r";
    } else if (ch == '\t') {
      out += "\\t";
    } else if (std::iscntrl(ch) != 0) {
      out += "\\x";
      out.push_back(hex.at(ch >> 4U));
      out.push_back(hex.at(ch & 0x0fU));
    } else {
      out.push_back(static_cast<char>(ch));
    }
  }
  return out;
}

std::string trimmed_probe_raw(std::string_view raw) {
  constexpr std::size_t kDisplayLimit = 256;
  const auto captured_bytes = raw.size();
  auto sanitized = support::sanitize_utf8(raw);
  while (!sanitized.empty() &&
         (sanitized.back() == ' ' || sanitized.back() == '\t' ||
          sanitized.back() == '\r' || sanitized.back() == '\n')) {
    sanitized.pop_back();
  }

  std::size_t prefix_bytes = 0;
  while (prefix_bytes < sanitized.size()) {
    const auto scalar = decode_scalar(sanitized, prefix_bytes);
    if (prefix_bytes + scalar.width > kDisplayLimit) {
      break;
    }
    prefix_bytes += scalar.width;
  }

  auto rendered = display(std::string_view{sanitized}.substr(0, prefix_bytes));
  if (prefix_bytes < sanitized.size()) {
    rendered += "\u2026 [truncated, showing " +
                std::to_string(prefix_bytes) + " of " +
                std::to_string(captured_bytes) + " captured bytes]";
  }
  return rendered;
}

std::string probe_failure(const support::ProbeEvidence& probe) {
  switch (probe.outcome) {
    case support::ProbeOutcome::not_found:
      return "executable not found";
    case support::ProbeOutcome::not_executable:
      return "present but not executable (permission or file kind)";
    case support::ProbeOutcome::not_accessible:
      return "pinned path resolution failed";
    case support::ProbeOutcome::spawn_error:
      return "spawn error";
    case support::ProbeOutcome::nonzero_exit:
      return "exit " + std::to_string(probe.exit_code);
    case support::ProbeOutcome::timeout:
      return "timeout after " +
             std::to_string(support::kProbeTimeout.count()) + "ms";
    case support::ProbeOutcome::unparseable:
      return "unparseable output";
    case support::ProbeOutcome::probe_io_error:
      return "probe I/O readiness failure";
    case support::ProbeOutcome::ok:
      return "unknown error";
  }
  return "unknown error";
}

std::string row_name(const core_sessions::SessionRowReport::Row row) {
  switch (row) {
    case core_sessions::SessionRowReport::Row::installed:
      return "installed";
    case core_sessions::SessionRowReport::Row::skipped:
    case core_sessions::SessionRowReport::Row::unknown_agent_skipped:
    case core_sessions::SessionRowReport::Row::sessions_consent_skipped:
      return "skipped";
    case core_sessions::SessionRowReport::Row::sessions_staged:
      return "staged";
    case core_sessions::SessionRowReport::Row::failed:
    case core_sessions::SessionRowReport::Row::containment_refused:
    case core_sessions::SessionRowReport::Row::session_install_failed:
    case core_sessions::SessionRowReport::Row::agent_not_validated_failed:
      return "failed";
  }
  return "failed";
}

}  // namespace

std::string render_probe_disclosure(
    const core_sessions::SessionPreview& preview) {
  std::ostringstream out;
  for (const auto& agent : preview.agents) {
    if (agent.caps.has_value() && agent.caps->probe.has_value()) {
      const auto& caps = *agent.caps;
      const auto& probe = *caps.probe;
      if (caps.verdict() == adapters::Capabilities::Verdict::absent) {
        out << "  " << display(agent.agent)
            << ": not validated on this host (agent store absent) \u2014 "
               "sessions will not be installed or staged\n";
      } else if (caps.verdict() == adapters::Capabilities::Verdict::readable &&
                 probe.outcome == support::ProbeOutcome::ok &&
          probe.parsed.has_value()) {
        const auto floor = adapters::version_floor::row_for(agent.agent);
        out << "  " << display(agent.agent) << ": "
            << display(probe.executed.has_value()
                           ? probe.executed->generic_string()
                           : std::string{"<not resolved>"})
            << " --version -> " << trimmed_probe_raw(probe.raw)
            << " (readable; minimum " << display(floor.min_line)
            << "; surveyed through " << display(floor.surveyed_through)
            << ')';
        if (probe.pinned) {
          out << " (pinned)";
        }
        out << '\n';
      } else {
        out << "  " << display(agent.agent) << ": version probe failed ("
            << probe_failure(probe) << ") at "
            << display(probe.executed.has_value()
                           ? probe.executed->generic_string()
                           : probe.requested.has_value()
                                 ? probe.requested->generic_string()
                                 : std::string{"<not resolved>"})
            << " --version -> "
            << (trimmed_probe_raw(probe.raw).empty()
                    ? std::string{"<no output>"}
                    : trimmed_probe_raw(probe.raw));
        if (probe.pinned) {
          out << " (pinned)";
        }
        /* m-3 spelling at consumer review */
        out << " \u2014 host version unreadable; make " << display(agent.agent)
            << " --version return one readable version and retry; sessions "
               "will not be installed or staged\n";
      }
    }
    if (agent.caps.has_value() &&
        agent.caps->wire_verdict() == "readable-newer-than-survey") {
      const auto floor = adapters::version_floor::row_for(agent.agent);
      out << "  " << display(agent.agent) << " host version "
          << display(agent.caps->agent_version())
          << " is newer than surveyed through "
          << display(floor.surveyed_through)
          << "; session import compatibility is uncertain\n";
    }
    if (agent.entry_schema_skipped_count != 0U) {
      const auto eligible = agent.primary_count + agent.descendant_count;
      out << "  " << display(agent.agent) << ": " << eligible
          << " session(s) can be imported; "
          << (agent.entry_schema_unparsed_count != 0U ? "at least " : "")
          << agent.entry_schema_skipped_count
          << " session(s) will be skipped \u2014 the skipped session(s) are recorded in a format this version of biv cannot read and are not counted among the "
          << eligible
          << ". Nothing has been written yet; a newer version of biv may be able to import them.\n";
    }
  }
  return out.str();
}

std::string render_prompt_b(const core_sessions::SessionPreview& preview,
                            const manifest::Manifest& manifest) {
  std::ostringstream out;
  out << "This image contains agent sessions that can be imported into your host stores:\n\n";
  for (const auto& agent : preview.agents) {
    out << "  " << display(agent.agent) << ": " << (agent.primary_count + agent.descendant_count)
        << " session(s) (" << agent.primary_count << " primary + " << agent.descendant_count
        << " descendant) -> ";
    if (agent.store.has_value()) {
      out << display(agent.store->root.generic_string());
    } else {
      out << "<not found>";
    }
    out << '\n';
    if (agent.caps.has_value() && !agent.caps->probe.has_value() &&
        agent.caps->verdict() == adapters::Capabilities::Verdict::unreadable) {
      /* m-3 spelling at consumer review */
      out << "  " << display(agent.agent)
          << ": host version unreadable \u2014 make " << display(agent.agent)
          << " --version return one readable version and retry; sessions will "
             "not be installed or staged\n";
    } else if (agent.caps.has_value() && !agent.caps->probe.has_value() &&
               agent.caps->verdict() == adapters::Capabilities::Verdict::absent) {
      const std::string detail{"agent store absent"};
      /* m-3 spelling at consumer review */
      out << "  " << display(agent.agent) << ": not validated on this host (" << detail
          << ") \u2014 sessions will not be installed or staged\n";
    }
  }
  out << "\nImage provenance: packed from " << display(manifest.source_path) << " by biv "
      << display(manifest.app_version) << " at " << display(manifest.created_at) << ".\n\n";
  out << kTrustWarning << "\n\nImport these sessions into your host agent stores? [y/N] ";
  return out.str();
}

std::string render_summary(
    const core_sessions::SessionPreview& preview,
    const core_sessions::SessionsOutcome& outcome,
    const bool consent_no_all,
    const std::filesystem::path& output_dir) {
  std::ostringstream out;
  out << "Session import summary:\n";
  for (const auto& row : outcome.rows) {
    out << "  " << display(row.agent) << ": " << display(row.image_session_id) << " -> "
        << row_name(row.row);
    if (row.installed_session_id.has_value()) {
      out << " as " << display(*row.installed_session_id);
    }
    if (row.reason.has_value()) {
      out << " (" << display(*row.reason) << ')';
    }
    if (row.detail.has_value()) {
      out << " [" << display(*row.detail) << ']';
    }
    if (row.host_version_unverified) {
      out << " [host version unverified]";
    }
    if (row.live_at_pack) {
      out << " [session was live at pack]";
    }
    out << '\n';
  }
  for (const auto& agent : preview.agents) {
    if (agent.entry_schema_skipped_count == 0U) {
      continue;
    }
    size_t imported = 0U;
    for (const auto& row : outcome.rows) {
      if (row.agent != agent.agent || row.row != core_sessions::SessionRowReport::Row::installed) {
        continue;
      }
      ++imported;
      const auto mapping = std::ranges::find_if(outcome.id_map, [&](const adapters::IdMapEntry& candidate) {
        return candidate.agent == agent.agent && candidate.image_session_id == row.image_session_id;
      });
      if (mapping != outcome.id_map.end()) {
        imported += mapping->children.size();
      }
    }
    out << "  " << display(agent.agent) << ": " << imported << " session(s) imported; "
        << (agent.entry_schema_unparsed_count != 0U ? "at least " : "")
        << agent.entry_schema_skipped_count
        << " session(s) skipped \u2014 recorded in a format this version of biv cannot read.\n";
  }
  if (!consent_no_all) {
    for (const auto& activation : outcome.activation) {
      if (activation.command.empty() || display(activation.command) != activation.command) {
        out << "  " << display(activation.agent) << ": resume command unavailable; see JSON report\n";
      } else {
        out << "  resume from "
            << display_path(output_dir.generic_string()) << ": "
            << activation.command << '\n';
      }
    }
  }
  for (const auto& caveat : outcome.caveats) {
    out << "  " << display(caveat.agent) << " note [" << display(caveat.kind)
        << "]: " << display(caveat.note) << '\n';
  }
  if (std::ranges::any_of(outcome.rows, [](const auto& row) {
        return row.row == core_sessions::SessionRowReport::Row::sessions_staged;
      })) {
    /* m-3 spelling at consumer review */
    out << "  Staged sessions were not installed into host stores; inspect the workspace "
           "staging area before use.\n";
  }
  return out.str();
}

}  // namespace biv::open_render
