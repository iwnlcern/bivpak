#include "core/report/envelope.hpp"

#include <algorithm>
#include <filesystem>

#include "core/json/writer.hpp"
#include "core/manifest/manifest.hpp"
#include "core/report/exit_map.hpp"
#include "core/support/probe.hpp"
#include "core/support/version.hpp"

namespace biv::report {

namespace {

void write_warnings(json::Writer& writer, const std::vector<pack::Warning>& warnings) {
  writer.key("warnings");
  writer.begin_array();
  for (const auto& warning : warnings) {
    writer.begin_object();
    writer.key("kind");
    writer.value_string(warning.kind);
    if (!warning.path.empty()) {
      writer.key("path");
      writer.value_string(warning.path);
    }
    writer.end_object();
  }
  writer.end_array();
}

void write_prune_entries(json::Writer& writer, const std::vector<scan::PruneEntry>& entries) {
  writer.key("entries");
  writer.begin_array();
  for (const auto& entry : entries) {
    writer.begin_object();
    writer.key("path");
    writer.value_string(entry.relpath);
    writer.key("source");
    writer.value_string(entry.source);
    writer.end_object();
  }
  writer.end_array();
}

void write_paths(json::Writer& writer, const std::vector<std::string>& paths) {
  writer.key("paths");
  writer.begin_array();
  for (const auto& path : paths) {
    writer.value_string(path);
  }
  writer.end_array();
}

void write_advisories(json::Writer& writer, const std::vector<pack::Advisory>& advisories) {
  writer.key("advisories");
  writer.begin_array();
  for (const auto& advisory : advisories) {
    writer.begin_object();
    writer.key("kind");
    writer.value_string(advisory.kind);
    if (advisory.kind == "prune-summary") {
      write_prune_entries(writer, advisory.entries);
    } else {
      write_paths(writer, advisory.paths);
    }
    writer.end_object();
  }
  writer.end_array();
}

void write_manifest_summary(json::Writer& writer,
                            int format_version,
                            const std::vector<pack::AgentSessionsSummary>& agent_sessions) {
  writer.key("manifest");
  writer.begin_object();
  writer.key("format_version");
  writer.value_int(format_version);
  writer.key("repos");
  writer.begin_array();
  writer.end_array();
  writer.key("agent_sessions");
  writer.begin_array();
  for (const auto& summary : agent_sessions) {
    writer.begin_object();
    writer.key("agent");
    writer.value_string(summary.agent);
    writer.key("session_count");
    writer.value_int(static_cast<int64_t>(summary.session_count));
    writer.end_object();
  }
  writer.end_array();
  writer.end_object();
}

void write_empty_manifest_summary(json::Writer& writer, int format_version) {
  write_manifest_summary(writer, format_version, {});
}

void write_open_manifest_summary(json::Writer& writer,
                                 const int format_version,
                                 const core_sessions::SessionPreview& preview) {
  writer.key("manifest");
  writer.begin_object();
  writer.key("format_version");
  writer.value_int(format_version);
  writer.key("repos");
  writer.begin_array();
  writer.end_array();
  writer.key("agent_sessions");
  writer.begin_array();
  for (const auto& agent : preview.agents) {
    writer.begin_object();
    writer.key("agent");
    writer.value_string(agent.agent);
    writer.key("session_count");
    writer.value_int(static_cast<int64_t>(agent.parent_count + agent.child_count));
    writer.end_object();
  }
  writer.end_array();
  writer.end_object();
}

void write_pack_result(json::Writer& writer, const pack::PackReport& report) {
  writer.key("image_path");
  writer.value_string(report.image_path);
  writer.key("source_path");
  writer.value_string(report.source_path);
  writer.key("source_path_flavor");
  writer.value_string(manifest::to_string(report.flavor));
  writer.key("image_id");
  writer.value_string(report.image_id);
  writer.key("member_count");
  writer.value_int(static_cast<int64_t>(report.member_count));
  writer.key("payload_bytes");
  writer.value_int(static_cast<int64_t>(report.payload_bytes));
  write_manifest_summary(writer, manifest::kFormatVersion, report.agent_sessions_summary);
}

std::string_view capability_name(const adapters::Capabilities::Verdict verdict) {
  switch (verdict) {
    case adapters::Capabilities::Verdict::validated:
      return "validated";
    case adapters::Capabilities::Verdict::unvalidated_host:
      return "unvalidated-host";
    case adapters::Capabilities::Verdict::unvalidated:
      return "unvalidated";
    case adapters::Capabilities::Verdict::absent:
      return "absent";
  }
  return "absent";
}

std::string_view probe_outcome_name(const support::ProbeOutcome outcome) {
  switch (outcome) {
    case support::ProbeOutcome::ok:
      return "ok";
    case support::ProbeOutcome::not_found:
      return "not_found";
    case support::ProbeOutcome::not_executable:
      return "not_executable";
    case support::ProbeOutcome::not_accessible:
      return "not_accessible";
    case support::ProbeOutcome::spawn_error:
      return "spawn_error";
    case support::ProbeOutcome::nonzero_exit:
      return "nonzero_exit";
    case support::ProbeOutcome::timeout:
      return "timeout";
    case support::ProbeOutcome::unparseable:
      return "unparseable";
    case support::ProbeOutcome::probe_io_error:
      return "probe_io_error";
  }
  return "spawn_error";
}

void write_optional_path(
    json::Writer& writer,
    const std::optional<std::filesystem::path>& path) {
  if (path.has_value()) {
    writer.value_string(support::sanitize_utf8(path->generic_string()));
  } else {
    writer.value_null();
  }
}

void write_probe(json::Writer& writer,
                 const support::ProbeEvidence& probe) {
  writer.key("probe");
  writer.begin_object();
  writer.key("agent");
  writer.value_string(support::sanitize_utf8(probe.agent));
  writer.key("requested");
  write_optional_path(writer, probe.requested);
  writer.key("executed");
  write_optional_path(writer, probe.executed);
  writer.key("pinned");
  writer.value_bool(probe.pinned);
  writer.key("outcome");
  writer.value_string(
      support::sanitize_utf8(probe_outcome_name(probe.outcome)));
  writer.key("exit_code");
  writer.value_int(probe.exit_code);
  writer.key("raw");
  writer.value_string(support::sanitize_utf8(probe.raw));
  writer.key("parsed");
  if (probe.parsed.has_value()) {
    writer.value_string(support::sanitize_utf8(*probe.parsed));
  } else {
    writer.value_null();
  }
  writer.end_object();
}

std::string_view row_name(const core_sessions::SessionRowReport::Row row) {
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

std::string_view consent_source(const core_sessions::ConsentSource source) {
  switch (source) {
    case core_sessions::ConsentSource::flag:
      return "flag";
    case core_sessions::ConsentSource::prompt:
      return "prompt";
    case core_sessions::ConsentSource::deny_default:
      return "deny-default";
  }
  return "deny-default";
}

void write_sessions(json::Writer& writer, const OpenSessionsReport& report) {
  writer.key("sessions");
  writer.begin_object();
  writer.key("prompt_shown");
  writer.value_bool(report.prompt_shown);
  writer.key("warning_shown");
  writer.value_bool(report.warning_shown);
  writer.key("consent");
  writer.begin_object();
  writer.key("source");
  writer.value_string(consent_source(report.consent.source));
  writer.key("values");
  writer.begin_array();
  for (const auto& [agent, allowed] : report.consent.per_agent) {
    writer.begin_object();
    writer.key("agent");
    writer.value_string(agent);
    writer.key("value");
    writer.value_string(allowed ? "yes" : "no");
    writer.end_object();
  }
  writer.end_array();
  writer.end_object();
  writer.key("agents");
  writer.begin_array();
  for (const auto& agent : report.preview.agents) {
    writer.begin_object();
    writer.key("agent");
    writer.value_string(agent.agent);
    writer.key("capabilities_verdict");
    writer.value_string(agent.caps.has_value() ? capability_name(agent.caps->verdict) : "absent");
    if (agent.caps.has_value() && agent.caps->probe.has_value()) {
      write_probe(writer, *agent.caps->probe);
    }
    writer.key("store_root");
    writer.value_string(agent.store.has_value() ? agent.store->root.generic_string() : "");
    writer.key("sessions");
    writer.begin_array();
    for (const auto& row : report.outcome.rows) {
      if (row.agent != agent.agent) {
        continue;
      }
      writer.begin_object();
      writer.key("image_session_id");
      writer.value_string(row.image_session_id);
      if (row.installed_session_id.has_value()) {
        writer.key("installed_session_id");
        writer.value_string(*row.installed_session_id);
      }
      writer.key("outcome");
      writer.value_string(row_name(row.row));
      const auto kind = core_sessions::kind_for_row(row.row, row.reason.value_or(""));
      if (kind.has_value()) {
        writer.key("kind");
        writer.value_string(to_string(*kind));
      }
      if (row.reason.has_value()) {
        writer.key("reason");
        writer.value_string(*row.reason);
      }
      if (row.detail.has_value()) {
        writer.key("detail");
        writer.value_string(*row.detail);
      }
      writer.key("host_version_unverified");
      writer.value_bool(row.host_version_unverified);
      writer.key("activation_suppressed");
      writer.value_bool(row.activation_suppressed);
      writer.end_object();
    }
    writer.end_array();
    writer.key("activation");
    writer.begin_array();
    for (const auto& activation : report.outcome.activation) {
      if (activation.agent == agent.agent) {
        writer.value_string(activation.command);
      }
    }
    writer.end_array();
    writer.key("caveats");
    writer.begin_array();
    for (const auto& caveat : report.outcome.caveats) {
      if (caveat.agent == agent.agent) {
        writer.value_string(caveat.kind + ": " + caveat.note);
      }
    }
    writer.end_array();
    writer.end_object();
  }
  writer.end_array();
  writer.end_object();
}

void write_open_result(json::Writer& writer,
                       const open::OpenReport& report,
                       const std::optional<OpenSessionsReport>& sessions) {
  writer.key("image_path");
  writer.value_string(report.image_path);
  writer.key("output_dir");
  writer.value_string(report.output_dir);
  writer.key("collision_action");
  writer.value_string(report.collision_action);
  writer.key("restored_member_count");
  writer.value_int(static_cast<int64_t>(report.restored_member_count));
  writer.key("checksums_verified");
  writer.value_bool(report.checksums_verified);
  if (sessions.has_value()) {
    write_open_manifest_summary(writer, report.manifest_format_version, sessions->preview);
    write_sessions(writer, *sessions);
  } else {
    write_empty_manifest_summary(writer, report.manifest_format_version);
  }
}

void write_error(json::Writer& writer, const BivError& error) {
  writer.begin_object();
  writer.key("kind");
  writer.value_string(to_string(error.kind));
  writer.key("path");
  writer.value_string(error.path);
  writer.key("detail");
  writer.value_string(error.detail);
  writer.key("errno");
  writer.value_int(error.err_no);
  writer.key("facts");
  writer.begin_object();
  for (const auto& [key, value] : error.facts) {
    writer.key(key);
    writer.value_string(value);
  }
  writer.end_object();
  writer.end_object();
}

}  // namespace

int exit_for_error(const ErrKind kind) noexcept {
  switch (kind) {
    case ErrKind::UsageError:
      return 5;
    case ErrKind::ArchiveWriteFailed:
    case ErrKind::IntegrityFailureMidApply:
    case ErrKind::RestoreWriteFailed:
    case ErrKind::InternalError:
    case ErrKind::ParseError:
      return 4;
    case ErrKind::ContainmentRefused:
    case ErrKind::SessionInstallFailed:
    case ErrKind::UnknownAgentSkipped:
    case ErrKind::AgentNotValidatedFailed:
      return 2;
    case ErrKind::SessionsConsentSkipped:
      return 0;
    case ErrKind::SourceUnreadableRoot:
    case ErrKind::RepoDiscoveredUnsupported:
    case ErrKind::OutputInsideSource:
    case ErrKind::PartialPresent:
    case ErrKind::NotABivpakImage:
    case ErrKind::ImageUnreadable:
    case ErrKind::FormatVersionUnsupported:
    case ErrKind::UnknownRequiredCapability:
    case ErrKind::IntegrityFailurePreApply:
    case ErrKind::UnmanifestedMember:
    case ErrKind::MemberPathUnsafe:
    case ErrKind::CollisionRefused:
    case ErrKind::OpenPartialPresent:
      return 3;
  }
  return 4;
}

int exit_for_warnings(const bool any_divergence_warning) noexcept {
  return any_divergence_warning ? 2 : 0;
}

int exit_for_sessions(const core_sessions::SessionsOutcome& outcome) noexcept {
  int exit_code = 0;
  for (const auto& row : outcome.rows) {
    const auto kind = core_sessions::kind_for_row(row.row, row.reason.value_or(""));
    if (kind.has_value()) {
      exit_code = std::max(exit_code, exit_for_error(*kind));
    }
  }
  return exit_code;
}

std::string envelope(std::string_view verb,
                     std::optional<pack::PackReport> pack_report,
                     std::optional<open::OpenReport> open_report,
                     std::optional<BivError> error,
                     int exit_code,
                     std::optional<OpenSessionsReport> sessions) {
  json::Writer writer;
  writer.begin_object();
  writer.key("envelope_version");
  writer.value_int(kEnvelopeVersion);
  writer.key("app_version");
  writer.value_string(app_version());
  writer.key("ok");
  writer.value_bool(!error.has_value() && (exit_code == 0 || exit_code == 2));
  writer.key("verb");
  writer.value_string(verb);
  writer.key("exit_code");
  writer.value_int(exit_code);
  if (pack_report.has_value()) {
    write_warnings(writer, pack_report->warnings);
    write_advisories(writer, pack_report->advisories);
  } else {
    writer.key("warnings");
    writer.begin_array();
    writer.end_array();
    writer.key("advisories");
    writer.begin_array();
    writer.end_array();
  }
  writer.key("result");
  if (error.has_value()) {
    writer.value_null();
  } else {
    writer.begin_object();
    if (pack_report.has_value()) {
      write_pack_result(writer, *pack_report);
    }
    if (open_report.has_value()) {
      write_open_result(writer, *open_report, sessions);
    }
    writer.end_object();
  }
  writer.key("error");
  if (error.has_value()) {
    write_error(writer, *error);
  } else {
    writer.value_null();
  }
  writer.end_object();
  return writer.take();
}

}  // namespace biv::report
