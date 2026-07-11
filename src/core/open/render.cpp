#include "core/open/render.hpp"

#include <cctype>
#include <sstream>

namespace biv::open_render {

namespace {

std::string display(std::string_view value) {
  std::string out;
  for (const unsigned char ch : value) {
    if (ch == '\n') {
      out += "\\n";
    } else if (ch == '\r') {
      out += "\\r";
    } else if (ch == '\t') {
      out += "\\t";
    } else if (std::iscntrl(ch) != 0) {
      out += "?";
    } else {
      out.push_back(static_cast<char>(ch));
    }
  }
  return out;
}

std::string row_name(const core_sessions::SessionRowReport::Row row) {
  switch (row) {
    case core_sessions::SessionRowReport::Row::installed:
      return "installed";
    case core_sessions::SessionRowReport::Row::skipped:
    case core_sessions::SessionRowReport::Row::unknown_agent_skipped:
    case core_sessions::SessionRowReport::Row::sessions_consent_skipped:
      return "skipped";
    case core_sessions::SessionRowReport::Row::failed:
    case core_sessions::SessionRowReport::Row::containment_refused:
    case core_sessions::SessionRowReport::Row::session_install_failed:
    case core_sessions::SessionRowReport::Row::agent_not_validated_failed:
      return "failed";
  }
  return "failed";
}

}  // namespace

std::string render_prompt_b(const core_sessions::SessionPreview& preview,
                            const manifest::Manifest& manifest) {
  std::ostringstream out;
  out << "This image contains agent sessions that can be imported into your host stores:\n\n";
  for (const auto& agent : preview.agents) {
    out << "  " << display(agent.agent) << ": " << (agent.parent_count + agent.child_count)
        << " session(s) (" << agent.parent_count << " parent + " << agent.child_count << " child) -> ";
    if (agent.store.has_value()) {
      out << display(agent.store->root.generic_string());
    } else {
      out << "<not found>";
    }
    out << '\n';
    if (agent.caps.has_value() &&
        agent.caps->verdict == adapters::Capabilities::Verdict::unvalidated_host) {
      out << "  " << display(agent.agent)
          << ": host version unverified \u2014 import proceeds on the image entry's version\n";
    } else if (agent.caps.has_value() &&
               (agent.caps->verdict == adapters::Capabilities::Verdict::unvalidated ||
                agent.caps->verdict == adapters::Capabilities::Verdict::absent)) {
      const auto detail = agent.caps->verdict == adapters::Capabilities::Verdict::absent
                              ? std::string{"agent store absent"}
                              : "version " + display(agent.caps->agent_version) + " outside " +
                                    display(agent.caps->validated_range);
      out << "  " << display(agent.agent) << ": not validated on this host (" << detail
          << ") \u2014 consent-yes will report FAILED for this agent's sessions (no staging in Step 3)\n";
    }
  }
  out << "\nImage provenance: packed from " << display(manifest.source_path) << " by biv "
      << display(manifest.app_version) << " at " << display(manifest.created_at) << ".\n\n";
  out << kTrustWarning << "\n\nImport these sessions into your host agent stores? [y/N] ";
  return out.str();
}

std::string render_summary(const core_sessions::SessionsOutcome& outcome, const bool consent_no_all) {
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
    if (row.host_version_unverified) {
      out << " [host version unverified]";
    }
    if (row.live_at_pack) {
      out << " [session was live at pack]";
    }
    out << '\n';
  }
  if (!consent_no_all) {
    for (const auto& activation : outcome.activation) {
      if (activation.command.empty() || display(activation.command) != activation.command) {
        out << "  " << display(activation.agent) << ": resume command unavailable; see JSON report\n";
      } else {
        out << "  resume: " << activation.command << '\n';
      }
    }
  }
  for (const auto& caveat : outcome.caveats) {
    out << "  " << display(caveat.agent) << " note [" << display(caveat.kind)
        << "]: " << display(caveat.note) << '\n';
  }
  return out.str();
}

}  // namespace biv::open_render
