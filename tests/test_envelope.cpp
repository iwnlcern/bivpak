#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/report/envelope.hpp"
#include "core/report/exit_map.hpp"

namespace {

size_t count_occurrences(std::string_view text, std::string_view needle) {
  size_t count = 0;
  size_t pos = 0;
  while ((pos = text.find(needle, pos)) != std::string_view::npos) {
    ++count;
    pos += needle.size();
  }
  return count;
}

}  // namespace

TEST_CASE("exit map classifies refusal, mid-fail, and usage") {
  CHECK(biv::report::exit_for_error(biv::ErrKind::PartialPresent) == 3);
  CHECK(biv::report::exit_for_error(biv::ErrKind::IntegrityFailurePreApply) == 3);
  CHECK(biv::report::exit_for_error(biv::ErrKind::ArchiveWriteFailed) == 4);
  CHECK(biv::report::exit_for_error(biv::ErrKind::RestoreWriteFailed) == 4);
  CHECK(biv::report::exit_for_error(biv::ErrKind::UsageError) == 5);
  CHECK(biv::report::exit_for_warnings(false) == 0);
  CHECK(biv::report::exit_for_warnings(true) == 2);
}

TEST_CASE("pack success envelope includes advisories") {
  biv::pack::PackReport report;
  report.image_path = "/tmp/sample.bvpk";
  report.source_path = "/tmp/sample";
  report.image_id = "00000000-0000-4000-8000-000000000000";
  report.member_count = 2;
  report.payload_bytes = 5;
  report.agent_sessions_summary.push_back(
      biv::pack::AgentSessionsSummary{.agent = "claude-code", .session_count = 1});
  report.advisories.push_back(biv::pack::Advisory{
      .kind = "prune-summary",
      .entries = {biv::scan::PruneEntry{.relpath = "target", .source = "builtin-v1"}},
      .paths = {}});

  const auto json = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  CHECK(json.find("\"ok\": true") != std::string::npos);
  CHECK(json.find("\"verb\": \"pack\"") != std::string::npos);
  CHECK(json.find("\"exit_code\": 0") != std::string::npos);
  CHECK(json.find("\"app_version\": \"0.1.0\"") != std::string::npos);
  CHECK(json.find("\"kind\": \"prune-summary\"") != std::string::npos);
  CHECK(json.find("\"path\": \"target\"") != std::string::npos);
  CHECK(json.find("\"source\": \"builtin-v1\"") != std::string::npos);
  CHECK(json.find("\"agent\": \"claude-code\"") != std::string::npos);
  CHECK(json.find("\"session_count\": 1") != std::string::npos);
  CHECK(json.find("\"manifest\"") != std::string::npos);
  CHECK(json.find("\"error\": null") != std::string::npos);
}

TEST_CASE("pack envelope uses per-kind advisory shapes") {
  biv::pack::PackReport report;
  report.image_path = "/tmp/sample.bvpk";
  report.source_path = "/tmp/sample";
  report.image_id = "00000000-0000-4000-8000-000000000000";
  report.member_count = 2;
  report.payload_bytes = 5;
  report.advisories.push_back(biv::pack::Advisory{
      .kind = "prune-summary",
      .entries = {biv::scan::PruneEntry{.relpath = "target", .source = ".bivignore:1"}},
      .paths = {}});
  report.advisories.push_back(biv::pack::Advisory{
      .kind = "nested-bivignore-ignored",
      .entries = {},
      .paths = {"dir/.bivignore"}});

  const auto json = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  const auto prune_pos = json.find("\"kind\": \"prune-summary\"");
  REQUIRE(prune_pos != std::string::npos);
  CHECK(json.find("\"entries\"", prune_pos) != std::string::npos);
  CHECK(json.find("\"paths\": []", prune_pos) == std::string::npos);

  const auto nested_pos = json.find("\"kind\": \"nested-bivignore-ignored\"");
  REQUIRE(nested_pos != std::string::npos);
  CHECK(json.find("\"paths\"", nested_pos) != std::string::npos);
  CHECK(json.find("\"entries\": []", nested_pos) == std::string::npos);
}

TEST_CASE("error envelope carries failure facts in result") {
  biv::BivError error{biv::ErrKind::PartialPresent};
  error.facts["partial_path"] = "/tmp/sample.bvpk.partial";
  error.facts["spool_path"] = "/tmp/sample.bvpk.spool";

  const auto json = biv::report::envelope("pack", std::nullopt, std::nullopt, error, 3);
  CHECK(json.find("\"ok\": false") != std::string::npos);
  CHECK(json.find("\"result\": null") != std::string::npos);
  CHECK(json.find("\"kind\": \"PartialPresent\"") != std::string::npos);
  CHECK(json.find("\"partial_path\": \"/tmp/sample.bvpk.partial\"") != std::string::npos);
  CHECK(json.find("\"spool_path\": \"/tmp/sample.bvpk.spool\"") != std::string::npos);
}

TEST_CASE("schema artifacts reserve envelope and exit-map contracts") {
  std::ifstream exit_map{std::string{BIV_SOURCE_DIR} + "/schemas/biv-exit-map.v1.json"};
  REQUIRE(exit_map);
  const std::string exit_text{std::istreambuf_iterator<char>{exit_map}, std::istreambuf_iterator<char>{}};
  struct ExpectedRow {
    std::string_view kind;
    std::string_view klass;
    int exit;
  };
  const std::vector<ExpectedRow> rows{
      {"SourceUnreadableRoot", "refusal", biv::report::exit_for_error(biv::ErrKind::SourceUnreadableRoot)},
      {"RepoDiscoveredUnsupported", "refusal", biv::report::exit_for_error(biv::ErrKind::RepoDiscoveredUnsupported)},
      {"OutputInsideSource", "refusal", biv::report::exit_for_error(biv::ErrKind::OutputInsideSource)},
      {"PartialPresent", "refusal", biv::report::exit_for_error(biv::ErrKind::PartialPresent)},
      {"SourceUnreadableSubpath", "divergence", biv::report::exit_for_warnings(true)},
      {"UnsupportedFileTypeSkipped", "divergence", biv::report::exit_for_warnings(true)},
      {"ArchiveWriteFailed", "mid-fail", biv::report::exit_for_error(biv::ErrKind::ArchiveWriteFailed)},
      {"NotABivpakImage", "refusal", biv::report::exit_for_error(biv::ErrKind::NotABivpakImage)},
      {"ImageUnreadable", "refusal", biv::report::exit_for_error(biv::ErrKind::ImageUnreadable)},
      {"FormatVersionUnsupported", "refusal", biv::report::exit_for_error(biv::ErrKind::FormatVersionUnsupported)},
      {"UnknownRequiredCapability", "refusal", biv::report::exit_for_error(biv::ErrKind::UnknownRequiredCapability)},
      {"IntegrityFailurePreApply", "refusal", biv::report::exit_for_error(biv::ErrKind::IntegrityFailurePreApply)},
      {"UnmanifestedMember", "refusal", biv::report::exit_for_error(biv::ErrKind::UnmanifestedMember)},
      {"MemberPathUnsafe", "refusal", biv::report::exit_for_error(biv::ErrKind::MemberPathUnsafe)},
      {"CollisionRefused", "refusal", biv::report::exit_for_error(biv::ErrKind::CollisionRefused)},
      {"OpenPartialPresent", "refusal", biv::report::exit_for_error(biv::ErrKind::OpenPartialPresent)},
      {"IntegrityFailureMidApply", "mid-fail", biv::report::exit_for_error(biv::ErrKind::IntegrityFailureMidApply)},
      {"RestoreWriteFailed", "mid-fail", biv::report::exit_for_error(biv::ErrKind::RestoreWriteFailed)},
      {"ContainmentRefused", "divergence", biv::report::exit_for_error(biv::ErrKind::ContainmentRefused)},
      {"SessionInstallFailed", "divergence", biv::report::exit_for_error(biv::ErrKind::SessionInstallFailed)},
      {"UnknownAgentSkipped", "divergence", biv::report::exit_for_error(biv::ErrKind::UnknownAgentSkipped)},
      {"SessionsConsentSkipped", "advisory", biv::report::exit_for_error(biv::ErrKind::SessionsConsentSkipped)},
      {"AgentNotValidatedFailed", "divergence", biv::report::exit_for_error(biv::ErrKind::AgentNotValidatedFailed)},
      {"InternalError", "mid-fail", biv::report::exit_for_error(biv::ErrKind::InternalError)},
      {"UsageError", "usage", biv::report::exit_for_error(biv::ErrKind::UsageError)}};
  for (const auto& row : rows) {
    const std::string needle = "\"kind\": \"" + std::string{row.kind} + "\"";
    INFO(row.kind);
    CHECK(exit_text.find(needle) != std::string::npos);
    CHECK(exit_text.find("\"class\": \"" + std::string{row.klass} + "\"", exit_text.find(needle)) !=
          std::string::npos);
    CHECK(exit_text.find("\"exit\": " + std::to_string(row.exit), exit_text.find(needle)) != std::string::npos);
  }
  CHECK(count_occurrences(exit_text, "\"kind\": \"") == rows.size());
  CHECK(exit_text.find("\"kind\": \"ParseError\"") == std::string::npos);
  CHECK(exit_text.find("\"RepoDiscoveredUnsupported\", \"class\": \"refusal\", \"exit\": 3, \"transitional\": true") !=
        std::string::npos);
  CHECK(exit_text.find("NotYetImplemented") != std::string::npos);

  std::ifstream envelope{std::string{BIV_SOURCE_DIR} + "/schemas/biv-json-envelope.v1.schema.json"};
  REQUIRE(envelope);
  const std::string envelope_text{std::istreambuf_iterator<char>{envelope}, std::istreambuf_iterator<char>{}};
  CHECK(envelope_text.find("prune-summary") != std::string::npos);
  CHECK(envelope_text.find("\"detail\"") != std::string::npos);
  CHECK(envelope_text.find("\"refused\"") != std::string::npos);
  CHECK(envelope_text.find("exit_code") != std::string::npos);
  CHECK(envelope_text.find("partial_dir") != std::string::npos);
}

TEST_CASE("session exit composition uses typed skip reasons") {
  biv::core_sessions::SessionsOutcome consent;
  consent.rows.push_back({.agent = "future-tool",
                          .image_session_id = "a",
                          .row = biv::core_sessions::SessionRowReport::Row::skipped,
                          .reason = "consent-denied",
                          .installed_session_id = std::nullopt,
                          .host_version_unverified = false,
                          .activation_suppressed = false,
                          .live_at_pack = false});
  CHECK(biv::report::exit_for_sessions(consent) == 0);

  auto unknown = consent;
  unknown.rows.front().reason = "unknown-agent";
  CHECK(biv::report::exit_for_sessions(unknown) == 2);

  unknown.rows.push_back(consent.rows.front());
  CHECK(biv::report::exit_for_sessions(unknown) == 2);

  auto failed = consent;
  failed.rows.front().row = biv::core_sessions::SessionRowReport::Row::failed;
  failed.rows.front().reason = "store-absent";
  CHECK(biv::report::exit_for_sessions(failed) == 2);
  CHECK(biv::report::exit_for_sessions({}) == 0);
}

TEST_CASE("open envelope includes typed sessions report") {
  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  sessions.warning_shown = true;
  sessions.consent.source = biv::core_sessions::ConsentSource::flag;
  sessions.consent.per_agent = {{"future-tool", true}};
  biv::core_sessions::AgentPreview preview;
  preview.agent = "future-tool";
  preview.parent_count = 1;
  sessions.preview.agents.push_back(std::move(preview));
  sessions.outcome.rows.push_back({.agent = "future-tool",
                                   .image_session_id = "old",
                                   .row = biv::core_sessions::SessionRowReport::Row::installed,
                                   .reason = std::nullopt,
                                   .installed_session_id = "new",
                                   .host_version_unverified = false,
                                   .activation_suppressed = false,
                                   .live_at_pack = false});

  const auto json = biv::report::envelope("open", std::nullopt, opened, std::nullopt, 0, sessions);
  CHECK(json.find("\"sessions\"") != std::string::npos);
  CHECK(json.find("\"warning_shown\": true") != std::string::npos);
  CHECK(json.find("\"installed_session_id\": \"new\"") != std::string::npos);
  CHECK(json.find("\"session_count\": 1") != std::string::npos);
}
