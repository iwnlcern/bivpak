#include <cstddef>
#include <cstdint>
#include <fstream>
#include <limits>
#include <optional>
#include <string>
#include <type_traits>
#include <string_view>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <simdjson.h>

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

// One source of truth for BOTH legs. Leg A navigates this envelope structurally;
// Leg C validates the SAME envelope against the schema. Two copies could drift
// apart silently and leave both test names reading true.
std::string detail_bearing_envelope_json() {
  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  biv::core_sessions::AgentPreview preview;
  preview.agent = "future-tool";
  sessions.preview.agents.push_back(std::move(preview));
  sessions.outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
      .reason = "error",
      .installed_session_id = std::nullopt,
      .host_version_unverified = false,
      .activation_suppressed = true,
      .live_at_pack = false,
      .detail = "capability_refused"});
  return biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);
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
  CHECK(std::string_view{biv::to_string(biv::ErrKind::EntrySchemaSkipped)} ==
        "EntrySchemaSkipped");
  CHECK(biv::report::exit_for_error(biv::ErrKind::EntrySchemaSkipped) == 0);
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

TEST_CASE("pack warning carrier serializes optional artifact and byte facts") {
  biv::pack::PackReport report;
  report.image_path = "/tmp/sample.bvpk";
  report.source_path = "/tmp/sample";
  report.image_id = "00000000-0000-4000-8000-000000000000";
  report.warnings.push_back(biv::pack::Warning{
      .kind = std::string{biv::pack::kWarningTornTailDropped},
      .path = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee2001",
      .artifact = "agents/codex/session.jsonl",
      .bytes = 42U});
  report.warnings.push_back(biv::pack::Warning{
      .kind = "SourceUnreadableSubpath", .path = "unreadable.txt"});

  const auto json = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 2);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(json).get(document) == simdjson::SUCCESS);

  simdjson::dom::array warnings;
  REQUIRE(document["warnings"].get(warnings) == simdjson::SUCCESS);
  const auto warning_count = std::distance(warnings.begin(), warnings.end());
  REQUIRE(warning_count == 2);

  std::string_view artifact;
  REQUIRE(warnings.at(0)["artifact"].get(artifact) == simdjson::SUCCESS);
  CHECK(artifact == "agents/codex/session.jsonl");
  std::uint64_t bytes = 0;
  REQUIRE(warnings.at(0)["bytes"].get(bytes) == simdjson::SUCCESS);
  CHECK(bytes == 42U);

  simdjson::dom::element absent;
  CHECK(warnings.at(1)["artifact"].get(absent) == simdjson::NO_SUCH_FIELD);
  CHECK(warnings.at(1)["bytes"].get(absent) == simdjson::NO_SUCH_FIELD);
}

TEST_CASE("pack warning bytes serialize uint64 maximum as an unsigned JSON integer") {
  biv::pack::PackReport report;
  report.image_path = "/tmp/sample.bvpk";
  report.source_path = "/tmp/sample";
  report.image_id = "00000000-0000-4000-8000-000000000000";
  report.warnings.push_back(biv::pack::Warning{
      .kind = std::string{biv::pack::kWarningTornTailDropped},
      .path = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee2001",
      .artifact = "agents/codex/session.jsonl",
      .bytes = std::numeric_limits<std::uint64_t>::max()});

  const auto json = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 2);
  CHECK(json.find("\"bytes\": 18446744073709551615") != std::string::npos);
  CHECK(json.find("\"bytes\": \"18446744073709551615\"") == std::string::npos);

  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(json).get(document) == simdjson::SUCCESS);
  std::uint64_t bytes = 0;
  REQUIRE(document["warnings"].at(0)["bytes"].get(bytes) == simdjson::SUCCESS);
  CHECK(bytes == std::numeric_limits<std::uint64_t>::max());
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
      {"EntrySchemaSkipped", "advisory", biv::report::exit_for_error(biv::ErrKind::EntrySchemaSkipped)},
      {"SessionsConsentSkipped", "advisory", biv::report::exit_for_error(biv::ErrKind::SessionsConsentSkipped)},
      {"SessionsStaged", "advisory", 0},
      {"AgentNotValidatedFailed", "divergence", biv::report::exit_for_error(biv::ErrKind::AgentNotValidatedFailed)},
      {"InternalError", "mid-fail", biv::report::exit_for_error(biv::ErrKind::InternalError)},
      {"UsageError", "usage", biv::report::exit_for_error(biv::ErrKind::UsageError)},
      {"UrlDivergenceRefused", "refusal", biv::report::exit_for_error(biv::ErrKind::UrlDivergenceRefused)},
      {"UrlDivergenceEntryRefused", "divergence", biv::report::exit_for_error(biv::ErrKind::UrlDivergenceEntryRefused)}};
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
  CHECK(envelope_text.find("\"probe\"") != std::string::npos);
  CHECK(envelope_text.find("\"nonzero_exit\"") != std::string::npos);
  CHECK(envelope_text.find("\"not_accessible\"") != std::string::npos);
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
                          .live_at_pack = false,
                          .detail = std::nullopt});
  CHECK(biv::report::exit_for_sessions(consent) == 0);

  auto entry_schema = consent;
  entry_schema.rows.front().reason = "entry-schema";
  CHECK(biv::core_sessions::kind_for_row(
            entry_schema.rows.front().row, *entry_schema.rows.front().reason) ==
        biv::ErrKind::EntrySchemaSkipped);
  CHECK(biv::report::exit_for_sessions(entry_schema) == 0);

  auto unknown = consent;
  unknown.rows.front().reason = "unknown-agent";
  CHECK(biv::report::exit_for_sessions(unknown) == 2);

  unknown.rows.push_back(consent.rows.front());
  CHECK(biv::report::exit_for_sessions(unknown) == 2);

  auto failed = consent;
  failed.rows.front().row = biv::core_sessions::SessionRowReport::Row::failed;
  failed.rows.front().reason = "store-absent";
  CHECK(biv::report::exit_for_sessions(failed) == 2);

  auto mixed = failed;
  mixed.rows.push_back(entry_schema.rows.front());
  CHECK(biv::report::exit_for_sessions(mixed) == 2);
  CHECK(biv::report::exit_for_sessions({}) == 0);
}

TEST_CASE("entry-schema advisory cannot mask a failed session in the envelope") {
  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  biv::core_sessions::AgentPreview preview;
  preview.agent = "codex";
  preview.entry_schema_skipped_count = 1;
  preview.entry_schema_unparsed_count = 1;
  sessions.preview.agents.push_back(preview);
  sessions.outcome.rows = {
      {.agent = "codex",
       .image_session_id = "future",
       .row = biv::core_sessions::SessionRowReport::Row::unknown_agent_skipped,
       .reason = "entry-schema",
       .installed_session_id = std::nullopt,
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt},
      {.agent = "codex",
       .image_session_id = "failed",
       .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
       .reason = "error",
       .installed_session_id = std::nullopt,
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt},
  };
  const int exit_code = biv::report::exit_for_sessions(sessions.outcome);
  REQUIRE(exit_code == 2);
  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, exit_code, sessions);
  CHECK(json.find("\"kind\": \"EntrySchemaSkipped\"") !=
        std::string::npos);
  CHECK(json.find("\"kind\": \"SessionInstallFailed\"") !=
        std::string::npos);
  CHECK(json.find("\"exit_code\": 2") != std::string::npos);
}

TEST_CASE("capability factory enforces four deterministic wire states") {
  using Capabilities = biv::adapters::Capabilities;
  CHECK_FALSE(std::is_aggregate_v<Capabilities>);
  CHECK_FALSE(std::is_default_constructible_v<Capabilities>);
  struct Case {
    Capabilities::Verdict verdict;
    std::optional<std::string> parsed;
    bool newer;
    std::string_view wire;
  };
  const Case cases[] = {
      {Capabilities::Verdict::readable, "0.300.0", true,
       "readable-newer-than-survey"},
      {Capabilities::Verdict::readable, "0.144.4", false, "readable"},
      {Capabilities::Verdict::unreadable, std::nullopt, false, "unreadable"},
      {Capabilities::Verdict::absent, std::nullopt, false, "absent"},
  };

  for (const auto& item : cases) {
    const auto caps =
        Capabilities::from_probe(item.verdict, item.parsed, item.newer);
    CHECK(caps.wire_verdict() == item.wire);
    CHECK(caps.newer_than_survey() == item.newer);
    CHECK(caps.agent_version() ==
          (item.verdict == Capabilities::Verdict::readable
               ? *item.parsed
               : std::string{"unknown"}));
    if (item.verdict != Capabilities::Verdict::readable) {
      CHECK_FALSE(caps.newer_than_survey());
    }
  }
}

TEST_CASE("envelope serializes each derived capability state exactly once") {
  using Capabilities = biv::adapters::Capabilities;
  biv::report::OpenSessionsReport sessions;
  const auto add = [&](std::string agent, Capabilities capabilities) {
    biv::core_sessions::AgentPreview preview;
    preview.agent = std::move(agent);
    preview.primary_count = 1;
    preview.caps = std::move(capabilities);
    sessions.preview.agents.push_back(std::move(preview));
  };
  add("newer", Capabilities::from_probe(
                   Capabilities::Verdict::readable, "0.300.0", true));
  add("readable", Capabilities::from_probe(
                     Capabilities::Verdict::readable, "0.144.4", false));
  add("unreadable", Capabilities::from_probe(
                       Capabilities::Verdict::unreadable, std::nullopt, false));
  add("absent", Capabilities::from_probe(
                   Capabilities::Verdict::absent, std::nullopt, false));
  const biv::open::OpenReport opened{
      .image_path = "/tmp/image.bvpk",
      .output_dir = "/tmp/restored",
      .collision_action = "none",
      .restored_member_count = 0,
      .checksums_verified = true,
      .manifest_format_version = 1};

  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);

  for (const std::string_view spelling : {
           "readable-newer-than-survey", "readable", "unreadable", "absent"}) {
    CHECK(count_occurrences(
              json, "\"capabilities_verdict\": \"" +
                        std::string{spelling} + "\"") == 1U);
  }
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
  preview.primary_count = 1;
  preview.descendant_count = 2;
  preview.entry_schema_skipped_count = 1;
  preview.entry_schema_unparsed_count = 1;
  preview.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, true,
      {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = "future-tool",
          .requested = "/opt/future",
          .executed = "/opt/future",
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = "future 0.144.4\n",
          .parsed = "0.144.4"});
  sessions.preview.agents.push_back(std::move(preview));
  biv::core_sessions::AgentPreview failed_preview;
  failed_preview.agent = "missing-tool";
  failed_preview.primary_count = 1;
  failed_preview.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false,
      false, {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = "missing-tool",
          .requested = std::nullopt,
          .executed = std::nullopt,
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::not_executable,
          .exit_code = -1,
          .raw = "",
          .parsed = std::nullopt});
  sessions.preview.agents.push_back(std::move(failed_preview));
  auto io_preview = sessions.preview.agents.back();
  io_preview.agent = "io-failed-tool";
  io_preview.caps->probe->agent = "io-failed-tool";
  io_preview.caps->probe->outcome =
      biv::support::ProbeOutcome::probe_io_error;
  sessions.preview.agents.push_back(std::move(io_preview));
  auto inaccessible_preview = sessions.preview.agents.at(1);
  inaccessible_preview.agent = "inaccessible-tool";
  inaccessible_preview.caps->probe->agent = "inaccessible-tool";
  inaccessible_preview.caps->probe->outcome =
      biv::support::ProbeOutcome::not_accessible;
  sessions.preview.agents.push_back(std::move(inaccessible_preview));
  sessions.outcome.rows.push_back({.agent = "future-tool",
                                   .image_session_id = "old",
                                   .row = biv::core_sessions::SessionRowReport::Row::installed,
                                   .reason = std::nullopt,
                                   .installed_session_id = "new",
                                   .host_version_unverified = false,
                                   .activation_suppressed = false,
                                   .live_at_pack = false,
                                   .detail = std::nullopt});
  sessions.outcome.activation.push_back(
      {.agent = "future-tool", .command = "future resume new"});

  const auto json = biv::report::envelope("open", std::nullopt, opened, std::nullopt, 0, sessions);
  CHECK(json.find("\"sessions\"") != std::string::npos);
  CHECK(json.find("\"warning_shown\": true") != std::string::npos);
  CHECK(json.find("\"installed_session_id\": \"new\"") != std::string::npos);
  CHECK(json.find("\"session_count\": 3") != std::string::npos);
  CHECK(json.find("\"primary_count\": 1") != std::string::npos);
  CHECK(json.find("\"descendant_count\": 2") != std::string::npos);
  CHECK(json.find("\"entry_schema_skipped_count\": 1") != std::string::npos);
  CHECK(json.find("\"entry_schema_unparsed_count\": 1") != std::string::npos);
  CHECK(json.find("\"probe\"") != std::string::npos);
  CHECK(json.find("\"outcome\": \"not_executable\"") !=
        std::string::npos);
  CHECK(json.find("\"outcome\": \"probe_io_error\"") !=
        std::string::npos);
  CHECK(json.find("\"outcome\": \"not_accessible\"") !=
        std::string::npos);
  CHECK(json.find("\"requested\": \"/opt/future\"") !=
        std::string::npos);
  CHECK(json.find("\"executed\": \"/opt/future\"") !=
        std::string::npos);
  CHECK(json.find("\"pinned\": true") != std::string::npos);
  CHECK(json.find("\"outcome\": \"ok\"") != std::string::npos);
  CHECK(json.find("\"exit_code\": 0") != std::string::npos);
  CHECK(json.find("\"raw\": \"future 0.144.4") != std::string::npos);
  CHECK(json.find("future 0.144.4\n") == std::string::npos);
  CHECK(json.find("\"parsed\": \"0.144.4\"") != std::string::npos);
  CHECK(count_occurrences(json, "\"probe\"") == 4);
  const auto failed_probe =
      json.find("\"outcome\": \"not_executable\"");
  REQUIRE(failed_probe != std::string::npos);
  const auto failed_object = json.rfind("\"probe\"", failed_probe);
  REQUIRE(failed_object != std::string::npos);
  CHECK(json.find("\"requested\": null", failed_object) < failed_probe);
  CHECK(json.find("\"executed\": null", failed_object) < failed_probe);
  CHECK(json.find("\"parsed\": null", failed_probe) != std::string::npos);
  CHECK(json.find("\"activation\"") != std::string::npos);
  CHECK(json.find("\"future resume new\"") != std::string::npos);
  CHECK(json.find("\"output_dir\": \"/tmp/restored\"") !=
        std::string::npos);

  biv::report::OpenSessionsReport unwired_sessions;
  biv::core_sessions::AgentPreview unwired_preview;
  unwired_preview.agent = "codex";
  unwired_preview.primary_count = 1;
  unwired_preview.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false,
      true);
  unwired_sessions.preview.agents.push_back(std::move(unwired_preview));

  const auto unwired_json =
      biv::report::envelope("open", std::nullopt, opened, std::nullopt, 0,
                            unwired_sessions);

  CHECK(unwired_json.find(
            "\"capabilities_verdict\": \"unreadable\"") !=
        std::string::npos);
  CHECK(unwired_json.find("\"probe\"") == std::string::npos);
}

TEST_CASE("probe fields replace invalid UTF-8 before envelope serialization") {
  const auto invalid = [](std::string prefix) {
    prefix.push_back(static_cast<char>(0x9b));
    return prefix;
  };

  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  biv::core_sessions::AgentPreview preview;
  preview.agent = "codex";
  preview.primary_count = 1;
  std::string full_raw(300, 'r');
  full_raw += invalid("-");
  preview.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, true,
      {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = invalid("agent-"),
          .requested = std::filesystem::path{invalid("/tmp/requested-")},
          .executed = std::filesystem::path{invalid("/tmp/executed-")},
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = full_raw,
          .parsed = invalid("parsed-")});
  sessions.preview.agents.push_back(std::move(preview));

  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);
  CHECK(json.find("\"session_count\": 1") != std::string::npos);
  CHECK(json.find("\"primary_count\": 1") != std::string::npos);
  CHECK(json.find("\"descendant_count\": 0") != std::string::npos);
  CHECK(json.find("\"entry_schema_skipped_count\"") == std::string::npos);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  CHECK(parser.parse(json).get(document) == simdjson::SUCCESS);

  const std::string replacement{"\xEF\xBF\xBD"};
  CHECK(json.find("\"agent\": \"agent-" + replacement + "\"") !=
        std::string::npos);
  CHECK(json.find("\"requested\": \"/tmp/requested-" + replacement + "\"") !=
        std::string::npos);
  CHECK(json.find("\"executed\": \"/tmp/executed-" + replacement + "\"") !=
        std::string::npos);
  CHECK(json.find("\"raw\": \"" + std::string(300, 'r') + "-" +
                  replacement + "\"") != std::string::npos);
  CHECK(json.find("\"parsed\": \"parsed-" + replacement + "\"") !=
        std::string::npos);
}

TEST_CASE("no-detail session rows serialize byte-identically to the pre-carrier baseline") {
  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  biv::core_sessions::AgentPreview preview;
  preview.agent = "future-tool";
  sessions.preview.agents.push_back(std::move(preview));
  sessions.outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::installed,
      .reason = std::nullopt,
      .installed_session_id = "new-id",
      .host_version_unverified = false,
      .activation_suppressed = false,
      .live_at_pack = false,
      .detail = std::nullopt});
  sessions.outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "failed-id",
      .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
      .reason = "error",
      .installed_session_id = std::nullopt,
      .host_version_unverified = false,
      .activation_suppressed = true,
      .live_at_pack = false,
      .detail = std::nullopt});

  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);

  // ORACLE RULE: captured at BASE cd61ac6, before SessionRowReport gained a
  // detail field. NEVER regenerate this literal from the serializer.
  CHECK(json == R"({
  "envelope_version": 1,
  "app_version": "0.1.0",
  "ok": true,
  "verb": "open",
  "exit_code": 0,
  "warnings": [],
  "advisories": [],
  "result": {
    "image_path": "/tmp/image.bvpk",
    "output_dir": "/tmp/restored",
    "collision_action": "none",
    "restored_member_count": 1,
    "checksums_verified": true,
    "manifest": {
      "format_version": 1,
      "repos": [],
      "agent_sessions": [
        {
          "agent": "future-tool",
          "session_count": 0,
          "primary_count": 0,
          "descendant_count": 0
        }
      ]
    },
    "sessions": {
      "prompt_shown": false,
      "warning_shown": false,
      "consent": {
        "source": "deny-default",
        "values": []
      },
      "agents": [
        {
          "agent": "future-tool",
          "capabilities_verdict": "absent",
          "store_root": "",
          "sessions": [
            {
              "image_session_id": "old-id",
              "installed_session_id": "new-id",
              "outcome": "installed",
              "host_version_unverified": false,
              "activation_suppressed": false
            },
            {
              "image_session_id": "failed-id",
              "outcome": "failed",
              "kind": "SessionInstallFailed",
              "reason": "error",
              "host_version_unverified": false,
              "activation_suppressed": true
            }
          ],
          "activation": [],
          "caveats": []
        }
      ]
    }
  },
  "error": null
}
)");
}

TEST_CASE("an adapter-authored detail reaches the envelope verbatim") {
  biv::open::OpenReport opened{.image_path = "/tmp/image.bvpk",
                               .output_dir = "/tmp/restored",
                               .collision_action = "none",
                               .restored_member_count = 1,
                               .checksums_verified = true,
                               .manifest_format_version = 1};
  biv::report::OpenSessionsReport sessions;
  biv::core_sessions::AgentPreview preview;
  preview.agent = "future-tool";
  sessions.preview.agents.push_back(std::move(preview));
  sessions.outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
      .reason = "error",
      .installed_session_id = std::nullopt,
      .host_version_unverified = false,
      .activation_suppressed = true,
      .live_at_pack = false,
      .detail = "capability_refused"});

  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);

  CHECK(json.find("\"detail\": \"capability_refused\"") !=
        std::string::npos);
  CHECK(json.find("capability-refused") == std::string::npos);
}

TEST_CASE("the emitted envelope carries detail at the schema's session-row path") {
  const auto json = detail_bearing_envelope_json();

  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(json).get(document) == simdjson::SUCCESS);

  simdjson::dom::array agents;
  REQUIRE(document["result"]["sessions"]["agents"].get(agents) ==
          simdjson::SUCCESS);

  std::size_t detail_rows = 0;
  for (simdjson::dom::element agent : agents) {
    simdjson::dom::array rows;
    if (agent["sessions"].get(rows) != simdjson::SUCCESS) {
      continue;
    }
    for (simdjson::dom::element row : rows) {
      simdjson::dom::element detail;
      if (row["detail"].get(detail) != simdjson::SUCCESS) {
        continue;
      }
      ++detail_rows;
      // TYPE, not just presence: R-3.43 leaves the schema unable to type this.
      std::string_view value;
      REQUIRE(detail.get(value) == simdjson::SUCCESS);
      CHECK(value == "capability_refused");
    }
  }
  CHECK(detail_rows == 1);
}

TEST_CASE("a generated detail-bearing envelope is emitted for schema conformance") {
  const auto json = detail_bearing_envelope_json();

  std::ofstream out{BIV_GENERATED_ENVELOPE_PATH,
                    std::ios::binary | std::ios::trunc};
  REQUIRE(out);
  out << json;
  out.close();
  REQUIRE(out);
}

namespace {

void check_refusal_row(const simdjson::dom::element row,
                       const std::string& repo_id, const std::string& relpath,
                       const std::string& requested, const std::string& effective,
                       const std::string& op) {
  CHECK(std::string_view{row["kind"]} == "UrlDivergenceEntryRefused");
  CHECK(std::string_view{row["repo_id"]} == repo_id);
  CHECK(std::string_view{row["relpath"]} == relpath);
  CHECK(std::string_view{row["requested"]} == requested);
  CHECK(std::string_view{row["effective"]} == effective);
  CHECK(std::string_view{row["op"]} == op);
  CHECK(simdjson::dom::object(row).size() == 6);
}

void check_accepted_entry(const simdjson::dom::element entry,
                          const std::string& requested, const std::string& effective,
                          const std::string& op, const std::string& repo) {
  CHECK(std::string_view{entry["requested"]} == requested);
  CHECK(std::string_view{entry["effective"]} == effective);
  CHECK(std::string_view{entry["op"]} == op);
  CHECK(std::string_view{entry["repo"]} == repo);
  CHECK(simdjson::dom::object(entry).size() == 4);
}

simdjson::dom::array single_accepted_entries(const simdjson::dom::element document) {
  size_t accepted_count = 0;
  simdjson::dom::array entries;
  for (const auto advisory : simdjson::dom::array(document["advisories"])) {
    if (std::string_view{advisory["kind"]} == "url-divergence-accepted") {
      ++accepted_count;
      entries = simdjson::dom::array(advisory["entries"]);
    }
  }
  REQUIRE(accepted_count == 1);
  return entries;
}

}  // namespace

TEST_CASE("a6-R1 open carriers: exact rows, order, cardinality, grouped advisory, zero state", "[a6-fabric]") {
  biv::open::OpenReport report{};
  report.image_path = "img.bvpk";
  report.output_dir = "out";
  const auto zero = biv::report::envelope("open", std::nullopt, report, std::nullopt, 0);
  CHECK(zero.find("url_divergence_refusals") == std::string::npos);
  CHECK(zero.find("url-divergence-accepted") == std::string::npos);
  report.url_divergence_refusals = {
      {"repoA", "path/one", "https://req-1", "https://eff-1", "fetch"},
      {"repoB", "path/two", "https://req-2", "https://eff-2", "ls-remote"}};
  report.url_divergence_accepted = {{"https://acc-req", "https://acc-eff", "clone", "/hook/acc"}};
  const auto populated = biv::report::envelope("open", std::nullopt, report, std::nullopt, 2);
  simdjson::dom::parser parser;
  const simdjson::dom::element document = parser.parse(populated);
  const simdjson::dom::array rows{document["result"]["url_divergence_refusals"]};
  REQUIRE(rows.size() == 2);
  check_refusal_row(rows.at(0), "repoA", "path/one", "https://req-1", "https://eff-1", "fetch");
  check_refusal_row(rows.at(1), "repoB", "path/two", "https://req-2", "https://eff-2", "ls-remote");
  const auto entries = single_accepted_entries(document);
  REQUIRE(entries.size() == 1);
  check_accepted_entry(entries.at(0), "https://acc-req", "https://acc-eff", "clone", "/hook/acc");
}

TEST_CASE("a6-R1 pack carries the grouped advisory too: exact entries, order, zero state", "[a6-fabric]") {
  biv::pack::PackReport report{};
  report.image_path = "img.bvpk";
  report.source_path = "src";
  const auto zero = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  CHECK(zero.find("url-divergence-accepted") == std::string::npos);
  CHECK(zero.find("url_divergence_refusals") == std::string::npos);
  report.url_divergence_accepted = {
      {"https://p1-req", "https://p1-eff", "ls-remote", "/pack/one"},
      {"https://p2-req", "https://p2-eff", "fetch", "/pack/two"}};
  const auto populated = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  simdjson::dom::parser parser;
  const simdjson::dom::element document = parser.parse(populated);
  const auto entries = single_accepted_entries(document);
  REQUIRE(entries.size() == 2);
  check_accepted_entry(entries.at(0), "https://p1-req", "https://p1-eff", "ls-remote", "/pack/one");
  check_accepted_entry(entries.at(1), "https://p2-req", "https://p2-eff", "fetch", "/pack/two");
}

TEST_CASE("a6-R1 site 1: the preflight grain rides the top-level error carrier", "[a6-fabric]") {
  biv::BivError error{.kind = biv::ErrKind::UrlDivergenceRefused,
                      .path = "/hook/repo",
                      .detail = "placeholder-until-task-4",
                      .facts = {{"requested", "https://req"},
                                {"effective", "https://eff"},
                                {"op", "ls-remote"}}};
  const auto envelope = biv::report::envelope("pack", std::nullopt, std::nullopt, error, 3);
  CHECK(envelope.find("\"kind\": \"UrlDivergenceRefused\"") != std::string::npos);
  CHECK(envelope.find("\"path\": \"/hook/repo\"") != std::string::npos);
  CHECK(envelope.find("\"requested\": \"https://req\"") != std::string::npos);
  CHECK(envelope.find("\"effective\": \"https://eff\"") != std::string::npos);
  CHECK(envelope.find("\"op\": \"ls-remote\"") != std::string::npos);
  CHECK(envelope.find("\"exit_code\": 3") != std::string::npos);
  CHECK(envelope.find("\"result\": null") != std::string::npos);
}

TEST_CASE("a6-R1 exit composition: one typed aggregator over both sources", "[a6-fabric]") {
  biv::core_sessions::SessionsOutcome clean{};
  const std::vector<biv::UrlDivergenceEntryRefusal> rows{
      {"r1", "a/b", "https://req", "https://eff", "fetch"}};
  CHECK(biv::report::exit_for_open(clean, {}) == 0);
  CHECK(biv::report::exit_for_open(clean, rows) == 2);
}
