#include <fstream>
#include <optional>
#include <string>
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
  preview.caps = biv::adapters::Capabilities{
      .agent_version = "0.144.4",
      .validated_range = "0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::validated,
      .long_path_keys_pinned = true,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = "future-tool",
          .requested = "/opt/future",
          .executed = "/opt/future",
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = "future 0.144.4\n",
          .parsed = "0.144.4"}};
  sessions.preview.agents.push_back(std::move(preview));
  biv::core_sessions::AgentPreview failed_preview;
  failed_preview.agent = "missing-tool";
  failed_preview.parent_count = 1;
  failed_preview.caps = biv::adapters::Capabilities{
      .agent_version = "unknown",
      .validated_range = "2.1.x",
      .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
      .long_path_keys_pinned = false,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = "missing-tool",
          .requested = std::nullopt,
          .executed = std::nullopt,
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::not_executable,
          .exit_code = -1,
          .raw = "",
          .parsed = std::nullopt}};
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
  CHECK(json.find("\"session_count\": 1") != std::string::npos);
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
  unwired_preview.parent_count = 1;
  unwired_preview.caps = biv::adapters::Capabilities{
      .agent_version = "unknown",
      .validated_range = "0.142.x, 0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
      .long_path_keys_pinned = true,
      .per_verb = {},
      .probe = std::nullopt};
  unwired_sessions.preview.agents.push_back(std::move(unwired_preview));

  const auto unwired_json =
      biv::report::envelope("open", std::nullopt, opened, std::nullopt, 0,
                            unwired_sessions);

  CHECK(unwired_json.find(
            "\"capabilities_verdict\": \"unvalidated-host\"") !=
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
  preview.parent_count = 1;
  std::string full_raw(300, 'r');
  full_raw += invalid("-");
  preview.caps = biv::adapters::Capabilities{
      .agent_version = "0.144.4",
      .validated_range = "0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::validated,
      .long_path_keys_pinned = true,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = invalid("agent-"),
          .requested = std::filesystem::path{invalid("/tmp/requested-")},
          .executed = std::filesystem::path{invalid("/tmp/executed-")},
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = full_raw,
          .parsed = invalid("parsed-")}};
  sessions.preview.agents.push_back(std::move(preview));

  const auto json = biv::report::envelope(
      "open", std::nullopt, opened, std::nullopt, 0, sessions);
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
          "session_count": 0
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

  simdjson::dom::parser parser;
  simdjson::dom::element document;
  CHECK(parser.parse(json).get(document) == simdjson::SUCCESS);

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
