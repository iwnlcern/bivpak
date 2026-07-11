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
      return "skipped";
    case core_sessions::SessionRowReport::Row::failed:
      return "failed";
  }
  return "failed";
}

}  // namespace

std::string render_prompt_b(const core_sessions::SessionPreview& preview,
                            const manifest::Manifest& manifest) {
  std::ostringstream out;
  out << "Sessions found in this image:\n";
  for (const auto& agent : preview.agents) {
    out << "  " << display(agent.agent) << ": " << (agent.parent_count + agent.child_count)
        << " session(s)";
    if (agent.store.has_value()) {
      out << " -> " << display(agent.store->root.generic_string());
    }
    if (agent.caps.has_value() &&
        agent.caps->verdict == adapters::Capabilities::Verdict::unvalidated_host) {
      out << " (host version unvalidated)";
    } else if (agent.caps.has_value() &&
               (agent.caps->verdict == adapters::Capabilities::Verdict::unvalidated ||
                agent.caps->verdict == adapters::Capabilities::Verdict::absent)) {
      out << " (FAILED: agent not validated)";
    }
    out << '\n';
  }
  out << "Image provenance: " << display(manifest.source_path) << " | "
      << display(manifest.app_version) << " | " << display(manifest.created_at) << "\n\n";
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
  for (const auto& [kind, note] : outcome.caveats) {
    out << "  note [" << display(kind) << "]: " << display(note) << '\n';
  }
  return out.str();
}

}  // namespace biv::open_render
