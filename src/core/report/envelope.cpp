#include "core/report/envelope.hpp"

#include "core/json/writer.hpp"
#include "core/manifest/manifest.hpp"
#include "core/report/exit_map.hpp"
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

void write_empty_manifest_summary(json::Writer& writer, int format_version) {
  writer.key("manifest");
  writer.begin_object();
  writer.key("format_version");
  writer.value_int(format_version);
  writer.key("repos");
  writer.begin_array();
  writer.end_array();
  writer.key("agent_sessions");
  writer.begin_array();
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
  write_empty_manifest_summary(writer, manifest::kFormatVersion);
}

void write_open_result(json::Writer& writer, const open::OpenReport& report) {
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
  write_empty_manifest_summary(writer, report.manifest_format_version);
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

std::string envelope(std::string_view verb,
                     std::optional<pack::PackReport> pack_report,
                     std::optional<open::OpenReport> open_report,
                     std::optional<BivError> error,
                     int exit_code) {
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
      write_open_result(writer, *open_report);
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
