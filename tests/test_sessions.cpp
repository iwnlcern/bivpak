#include <algorithm>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/open/sessions.hpp"
#include "core/report/exit_map.hpp"
#include "core/support/probe.hpp"

namespace {

namespace fs = std::filesystem;

fs::path make_tmp(std::string_view name) {
  auto base = fs::temp_directory_path() /
              ("biv-sessions-" + std::string{name} + "-" +
               std::to_string(::getpid()));
  fs::remove_all(base);
  fs::create_directories(base);
  return fs::canonical(base);
}

biv::manifest::AgentSessionEntry entry(std::string agent, int schema = 1) {
  biv::manifest::AgentSessionEntry value;
  value.agent = std::move(agent);
  value.entry_schema = schema;
  value.agent_version_at_pack = "1.0.0";
  value.relpath_key = ".";
  value.original_path = "/tmp/source";
  value.normalized_path_key = "/tmp/source";
  value.normalization_scheme = "test/v1";
  value.path_flavor = biv::manifest::PathFlavor::posix;
  value.provenance = {.store_root = "/tmp/store", .locator = "sessions_root", .discovery_tier = "default"};
  value.original_session_ids = {.primary = value.agent + "-session",
                                .parent = std::nullopt,
                                .parent_in_image = std::nullopt};
  value.artifacts = {"agents/" + value.agent + "/session.jsonl"};
  value.imported_at = "2026-07-11T00:00:00Z";
  return value;
}

biv::manifest::Manifest model(std::vector<biv::manifest::AgentSessionEntry> entries) {
  biv::manifest::Manifest manifest;
  manifest.agent_sessions = std::move(entries);
  return manifest;
}

biv::adapters::Env env(const std::filesystem::path& home) {
  return biv::adapters::Env{.getenv = [](std::string_view) { return std::optional<std::string>{}; },
                            .home = home};
}

std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> result;
  result.reserve(text.size());
  for (const char value : text) {
    result.push_back(static_cast<std::byte>(value));
  }
  return result;
}

// R-3.45 / m-3 014309:
//   reason "verify-hits" => detail in {origin_path, origin_id, undecodable_line}
//   ambient reason       => detail is a pinned uppercase POSIX errno symbol
bool is_errno_family(const std::optional<std::string>& detail) {
  if (!detail || detail->empty() || detail->front() != 'E') {
    return false;
  }
  return std::ranges::all_of(*detail, [](unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
  });
}

bool is_verify_family(const std::optional<std::string>& detail) {
  return detail == std::optional<std::string>{"origin_path"} ||
         detail == std::optional<std::string>{"origin_id"} ||
         detail == std::optional<std::string>{"undecodable_line"};
}

// The control. True when a row pairs the two families illegally.
bool violates_cross_family(const biv::core_sessions::SessionRowReport& row) {
  const bool verify_reason = row.reason == std::optional<std::string>{"verify-hits"};
  if (verify_reason) {
    return is_errno_family(row.detail);
  }
  return is_verify_family(row.detail);
}

biv::manifest::AgentSessionEntry codex_entry(std::string_view version) {
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1440";
  auto value = entry("codex");
  value.agent_version_at_pack = version;
  value.original_path = "/ws/proj";
  value.normalized_path_key = "/ws/proj";
  value.normalization_scheme = "codex-cwd/v1";
  value.original_session_ids.primary = session_id;
  value.artifacts = {"agents/codex/" + std::string{session_id} + ".jsonl"};
  return value;
}

// Drives the REAL session leg with a member_read that fails, so the adapter
// returns std::unexpected and sessions.cpp fans one row per eligible record.
std::vector<biv::core_sessions::SessionRowReport> fanned_rows(
    const std::filesystem::path& home,
    std::vector<biv::manifest::AgentSessionEntry> records,
    const biv::BivError& failure) {
  const auto store = home / ".codex";
  const auto workspace = home / "workspace";
  std::filesystem::create_directories(store);
  std::filesystem::create_directories(workspace);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.144.1\"}\n";
  }
  auto manifest = model(std::move(records));
  const biv::adapters::Host host{
      .home = home,
      .env = env(home),
      .version_probe = [&](const std::string_view agent,
                           const std::optional<std::filesystem::path>&)
          -> biv::expected<biv::support::ProbeEvidence> {
        return biv::support::ProbeEvidence{.agent = std::string{agent},
                                           .requested = std::nullopt,
                                           .executed = home / "bin" / "codex",
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::ok,
                                           .exit_code = 0,
                                           .raw = "codex-cli 0.144.1",
                                           .parsed = std::nullopt};
      },
      .pinned_bins = {}};
  auto preview = biv::core_sessions::build_preview(manifest, host);
  REQUIRE(preview);
  biv::core_sessions::ConsentSpec consent_spec;
  consent_spec.global = biv::core_sessions::ConsentValue::yes;
  const auto consent =
      biv::core_sessions::resolve_consent(consent_spec, *preview, std::nullopt);
  const biv::adapters::MemberRead reader =
      [&](std::string_view) -> biv::expected<std::vector<std::byte>> {
    return std::unexpected(failure);
  };
  const auto outcome = biv::core_sessions::run_session_leg(
      *preview, consent, manifest, workspace, reader);
  REQUIRE(outcome);
  return outcome->rows;
}

std::vector<biv::manifest::AgentSessionEntry> two_codex_records() {
  auto first = codex_entry("0.144.1");
  auto second = codex_entry("0.144.1");
  second.original_session_ids.primary =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1441";
  second.artifacts = {
      "agents/codex/019faaaa-bbbb-7ccc-8ddd-eeeeeeee1441.jsonl"};
  return {first, second};
}

}  // namespace

TEST_CASE("the cross-family control catches an illegal reason/detail pair") {
  // The report layer is a verbatim pass-through and enforces no pairing
  // (sessions.hpp:53, :58-61), so a violating row is one initializer.
  biv::core_sessions::SessionRowReport conforming_verify{};
  conforming_verify.reason = "verify-hits";
  conforming_verify.detail = "origin_path";
  CHECK_FALSE(violates_cross_family(conforming_verify));

  biv::core_sessions::SessionRowReport violating_verify{};
  violating_verify.reason = "verify-hits";
  violating_verify.detail = "EACCES";
  CHECK(violates_cross_family(violating_verify));      // <- the bite

  biv::core_sessions::SessionRowReport conforming_ambient{};
  conforming_ambient.reason = "error";
  conforming_ambient.detail = "ENOSPC";
  CHECK_FALSE(violates_cross_family(conforming_ambient));

  biv::core_sessions::SessionRowReport violating_ambient{};
  violating_ambient.reason = "error";
  violating_ambient.detail = "origin_path";
  CHECK(violates_cross_family(violating_ambient));     // <- the bite, other direction
}

TEST_CASE("session preview groups manifest agents and flags unsupported rows") {
  const auto home = make_tmp("preview");
  auto manifest = model({entry("future-tool"), entry("codex", 99)});

  auto preview = biv::core_sessions::build_preview(manifest, env(home));
  REQUIRE(preview);
  REQUIRE(preview->agents.size() == 2U);
  CHECK_FALSE(preview->agents.at(0).known_adapter);
  CHECK(preview->agents.at(1).known_adapter);
  CHECK(preview->agents.at(1).entry_schema_skipped);
  CHECK(preview->any_sessions());
  std::filesystem::remove_all(home);

  const auto unwired_home = make_tmp("probe-unwired");
  auto unwired_manifest = model({entry("claude-code"), entry("codex")});
  const biv::adapters::Host host{
      .home = unwired_home,
      .env = env(unwired_home),
      .version_probe = {},
      .pinned_bins = {}};

  const auto unwired_preview =
      biv::core_sessions::build_preview(unwired_manifest, host);

  REQUIRE(unwired_preview);
  REQUIRE(unwired_preview->agents.size() == 2U);
  for (const auto& agent : unwired_preview->agents) {
    REQUIRE(agent.caps.has_value());
    CHECK(agent.caps->verdict ==
          biv::adapters::Capabilities::Verdict::unvalidated_host);
    CHECK_FALSE(agent.caps->probe.has_value());
  }
  std::filesystem::remove_all(unwired_home);
}

TEST_CASE("consent resolution covers global per-agent prompt and deny default") {
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::AgentPreview claude;
  claude.agent = "claude-code";
  biv::core_sessions::AgentPreview codex;
  codex.agent = "codex";
  preview.agents = {claude, codex};

  biv::core_sessions::ConsentSpec global;
  global.global = biv::core_sessions::ConsentValue::yes;
  auto yes = biv::core_sessions::resolve_consent(global, preview, std::nullopt);
  CHECK(yes.source == biv::core_sessions::ConsentSource::flag);
  CHECK(yes.per_agent == std::vector<std::pair<std::string, bool>>{{"claude-code", true}, {"codex", true}});

  biv::core_sessions::ConsentSpec split;
  split.per_agent = {{"codex", biv::core_sessions::ConsentValue::yes}};
  auto per_agent = biv::core_sessions::resolve_consent(split, preview, std::nullopt);
  CHECK(per_agent.per_agent ==
        std::vector<std::pair<std::string, bool>>{{"claude-code", false}, {"codex", true}});

  auto prompt = biv::core_sessions::resolve_consent({}, preview, true);
  CHECK(prompt.source == biv::core_sessions::ConsentSource::prompt);
  CHECK(prompt.per_agent.front().second);

  auto denied = biv::core_sessions::resolve_consent({}, preview, std::nullopt);
  CHECK(denied.source == biv::core_sessions::ConsentSource::deny_default);
  CHECK_FALSE(denied.per_agent.front().second);
}

TEST_CASE("session leg skips denied and unknown rows without reading members") {
  const auto home = make_tmp("skip");
  auto manifest = model({entry("future-tool")});
  auto preview = biv::core_sessions::build_preview(manifest, env(home));
  REQUIRE(preview);
  auto consent = biv::core_sessions::resolve_consent({}, *preview, std::nullopt);
  bool read_called = false;
  biv::adapters::MemberRead reader = [&](std::string_view) -> biv::expected<std::vector<std::byte>> {
    read_called = true;
    return std::vector<std::byte>{};
  };

  auto outcome = biv::core_sessions::run_session_leg(*preview, consent, manifest, home / "workspace", reader);
  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 1U);
  CHECK(outcome->rows.front().row == biv::core_sessions::SessionRowReport::Row::unknown_agent_skipped);
  CHECK(outcome->rows.front().reason == "unknown-agent");
  CHECK(biv::core_sessions::kind_for_row(outcome->rows.front().row, *outcome->rows.front().reason) ==
        biv::ErrKind::UnknownAgentSkipped);
  CHECK_FALSE(read_called);
  CHECK(outcome->activation.empty());
  std::filesystem::remove_all(home);
}

TEST_CASE("typed session kinds cover every advisory and divergence class") {
  using Row = biv::core_sessions::SessionRowReport;
  CHECK(biv::core_sessions::kind_for_row(Row::Row::sessions_consent_skipped, "") ==
        biv::ErrKind::SessionsConsentSkipped);
  CHECK(biv::core_sessions::kind_for_row(Row::Row::unknown_agent_skipped, "") ==
        biv::ErrKind::UnknownAgentSkipped);
  CHECK(biv::core_sessions::kind_for_row(Row::Row::containment_refused, "") ==
        biv::ErrKind::ContainmentRefused);
  CHECK(biv::core_sessions::kind_for_row(Row::Row::agent_not_validated_failed, "") ==
        biv::ErrKind::AgentNotValidatedFailed);
  CHECK(biv::core_sessions::kind_for_row(Row::Row::session_install_failed, "") ==
        biv::ErrKind::SessionInstallFailed);
  CHECK_FALSE(biv::core_sessions::kind_for_row(Row::Row::installed, "").has_value());
  CHECK(biv::core_sessions::install_failure_reason(
            biv::BivError{biv::ErrKind::RestoreWriteFailed, {}, "write_protected"}) == "write_protected");
}

TEST_CASE("activation filtering suppresses only the failed session command") {
  biv::adapters::InstallResult installed;
  installed.activation = {{.agent = "future-tool", .command = "future resume clean-id"},
                          {.agent = "future-tool", .command = "future resume bad-id"},
                          {.agent = "future-tool", .command = "future resume orphan-id"}};
  std::vector<biv::core_sessions::SessionRowReport> rows{
      {.agent = "future-tool",
       .image_session_id = "clean-image",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "clean-id",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt},
      {.agent = "future-tool",
       .image_session_id = "bad-image",
       .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
       .reason = "error",
       .installed_session_id = "bad-id",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt}};

  const auto safe = biv::core_sessions::filter_activation(installed.activation, rows);
  REQUIRE(safe.size() == 1U);
  CHECK(safe.front().command == "future resume clean-id");
}

TEST_CASE("Codex session outcomes accept only the enumerated validated lines") {
  struct VersionCase {
    std::string_view version;
    bool accepted;
  };
  constexpr VersionCase cases[]{{"0.142.5", true},
                                {"0.144.1", true},
                                {"0.143.0", false},
                                {"0.145.0", false},
                                {"0.61.0", false}};
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1440";

  for (const auto& version_case : cases) {
    DYNAMIC_SECTION(version_case.version) {
      const auto home =
          make_tmp("codex-range-" + std::string{version_case.version});
      const auto store = home / ".codex";
      const auto workspace = home / "workspace";
      std::filesystem::create_directories(store);
      std::filesystem::create_directories(workspace);
      {
        std::ofstream marker{store / "version.json"};
        marker << "{\"version\":\"" << version_case.version << "\"}\n";
      }
      auto manifest = model({codex_entry(version_case.version)});
      const biv::adapters::Host host{
          .home = home,
          .env = env(home),
          .version_probe = [&](const std::string_view agent, const std::optional<std::filesystem::path>&)
              -> biv::expected<biv::support::ProbeEvidence> {
            return biv::support::ProbeEvidence{.agent = std::string{agent},
                                               .requested = std::nullopt,
                                               .executed = home / "bin" / "codex",
                                               .pinned = false,
                                               .outcome = biv::support::ProbeOutcome::ok,
                                               .exit_code = 0,
                                               .raw = "codex-cli " + std::string{version_case.version},
                                               .parsed = std::nullopt};
          },
          .pinned_bins = {}};
      auto preview = biv::core_sessions::build_preview(manifest, host);
      REQUIRE(preview);
      biv::core_sessions::ConsentSpec consent_spec;
      consent_spec.global = biv::core_sessions::ConsentValue::yes;
      const auto consent =
          biv::core_sessions::resolve_consent(consent_spec, *preview, std::nullopt);
      const std::string artifact = "agents/codex/" +
                                   std::string{session_id} + ".jsonl";
      const auto content = bytes(
          "{\"timestamp\":\"2026-07-12T00:00:00Z\",\"type\":"
          "\"session_meta\",\"payload\":{\"id\":\"" +
          std::string{session_id} + "\",\"session_id\":\"" +
          std::string{session_id} +
          "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"" +
          std::string{version_case.version} + "\"}}\n");
      const biv::adapters::MemberRead reader =
          [&](std::string_view path) -> biv::expected<std::vector<std::byte>> {
        if (path != artifact) {
          return std::unexpected(
              biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
        }
        return content;
      };

      const auto outcome = biv::core_sessions::run_session_leg(
          *preview, consent, manifest, workspace, reader);

      REQUIRE(outcome);
      REQUIRE(outcome->rows.size() == 1U);
      const auto& row = outcome->rows.front();
      if (version_case.accepted) {
        CHECK(row.row ==
              biv::core_sessions::SessionRowReport::Row::installed);
        CHECK(row.installed_session_id.has_value());
        CHECK_FALSE(row.activation_suppressed);
        CHECK(biv::report::exit_for_sessions(*outcome) == 0);
        CHECK(std::filesystem::exists(store / "sessions"));
      } else {
        CHECK(row.row == biv::core_sessions::SessionRowReport::Row::
                             agent_not_validated_failed);
        CHECK(row.reason == std::optional<std::string>{"not-validated"});
        CHECK_FALSE(row.installed_session_id.has_value());
        CHECK(row.activation_suppressed);
        CHECK(outcome->activation.empty());
        CHECK(biv::report::exit_for_sessions(*outcome) == 2);
        CHECK_FALSE(std::filesystem::exists(store / "sessions"));
      }
      std::filesystem::remove_all(home);
    }
  }
}

TEST_CASE("the seam copies an adapter-authored detail to the row verbatim") {
  const auto home = make_tmp("carrier-verbatim");
  const auto store = home / ".codex";
  const auto workspace = home / "workspace";
  std::filesystem::create_directories(store);
  std::filesystem::create_directories(workspace);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.144.1\"}\n";
  }
  // agent_version_at_pack "unknown" drives the capability refusal at
  // codex/install.cpp:350-360, which pushes a row with detail
  // "capability_refused" and returns a SUCCESSFUL InstallResult.
  auto record = codex_entry("0.144.1");
  record.agent_version_at_pack = "unknown";
  auto manifest = model({record});
  const biv::adapters::Host host{
      .home = home,
      .env = env(home),
      .version_probe = [&](const std::string_view agent,
                           const std::optional<std::filesystem::path>&)
          -> biv::expected<biv::support::ProbeEvidence> {
        return biv::support::ProbeEvidence{.agent = std::string{agent},
                                           .requested = std::nullopt,
                                           .executed = home / "bin" / "codex",
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::ok,
                                           .exit_code = 0,
                                           .raw = "unparseable-version",
                                           .parsed = std::nullopt};
      },
      .pinned_bins = {}};
  auto preview = biv::core_sessions::build_preview(manifest, host);
  REQUIRE(preview);
  biv::core_sessions::ConsentSpec consent_spec;
  consent_spec.global = biv::core_sessions::ConsentValue::yes;
  const auto consent =
      biv::core_sessions::resolve_consent(consent_spec, *preview, std::nullopt);
  const biv::adapters::MemberRead reader =
      [&](std::string_view path) -> biv::expected<std::vector<std::byte>> {
    return std::unexpected(
        biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
  };

  const auto outcome = biv::core_sessions::run_session_leg(
      *preview, consent, manifest, workspace, reader);

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 1U);
  CHECK(outcome->rows.front().detail ==
        std::optional<std::string>{"capability_refused"});
  std::filesystem::remove_all(home);
}

TEST_CASE(
    "Task 3 session preview observes capabilities once and install "
    "reuses them") {
  constexpr std::string_view session_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1440";
  const auto home = make_tmp("single-capability-observation");
  const auto store = home / ".codex";
  const auto workspace = home / "workspace";
  std::filesystem::create_directories(store);
  std::filesystem::create_directories(workspace);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.61.0\"}\n";
  }
  auto manifest = model({codex_entry("0.143.0")});
  size_t observations = 0;
  const biv::adapters::Host host{
      .home = home,
      .env = env(home),
      .version_probe = [&](const std::string_view agent,
                           const std::optional<std::filesystem::path>&) -> biv::expected<biv::support::ProbeEvidence> {
        ++observations;
        return biv::support::ProbeEvidence{.agent = std::string{agent},
                                           .requested = std::nullopt,
                                           .executed = home / "bin" / "codex",
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::ok,
                                           .exit_code = 0,
                                           .raw = "codex-cli 0.144.4",
                                           .parsed = std::nullopt};
      },
      .pinned_bins = {}};

  auto preview = biv::core_sessions::build_preview(manifest, host);
  REQUIRE(preview);
  REQUIRE(preview->agents.size() == 1);
  REQUIRE(preview->agents.front().caps.has_value());
  CHECK(preview->agents.front().caps->verdict == biv::adapters::Capabilities::Verdict::validated);
  CHECK(observations == 1);

  biv::core_sessions::ConsentSpec consent_spec;
  consent_spec.global = biv::core_sessions::ConsentValue::yes;
  const auto consent = biv::core_sessions::resolve_consent(consent_spec, *preview, std::nullopt);
  const std::string artifact = "agents/codex/" + std::string{session_id} + ".jsonl";
  const auto content = bytes(
      "{\"timestamp\":\"2026-07-12T00:00:00Z\",\"type\":"
      "\"session_meta\",\"payload\":{\"id\":\"" +
      std::string{session_id} + "\",\"session_id\":\"" + std::string{session_id} +
      "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.143.0\"}}\n");
  const biv::adapters::MemberRead reader = [&](std::string_view path) -> biv::expected<std::vector<std::byte>> {
    if (path != artifact) {
      return std::unexpected(biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
    }
    return content;
  };

  const auto outcome = biv::core_sessions::run_session_leg(*preview, consent, manifest, workspace, reader);

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 1);
  CHECK(outcome->rows.front().row == biv::core_sessions::SessionRowReport::Row::installed);
  CHECK_FALSE(outcome->rows.front().host_version_unverified);
  CHECK(observations == 1);
  std::filesystem::remove_all(home);
}

TEST_CASE("a fanned hard error carries the exact errno symbol to every row") {
  const auto home = make_tmp("fanned-errno");
  const auto rows = fanned_rows(
      home, two_codex_records(),
      biv::BivError{biv::ErrKind::ArchiveWriteFailed, "/store", "", ENOSPC});

  REQUIRE(rows.size() == 2U);
  for (const auto& row : rows) {
    CHECK(row.row ==
          biv::core_sessions::SessionRowReport::Row::session_install_failed);
    CHECK(row.reason == std::optional<std::string>{"error"});
    CHECK(row.detail == std::optional<std::string>{"ENOSPC"});
    // Applied to output from fanned_rows() -> run_session_leg(), a real producer.
    CHECK_FALSE(violates_cross_family(row));
  }
  std::filesystem::remove_all(home);
}

TEST_CASE("a fanned hard error with a zero errno omits the detail entirely") {
  const auto home = make_tmp("fanned-zero");
  const auto rows = fanned_rows(
      home, {codex_entry("0.144.1")},
      biv::BivError{biv::ErrKind::ArchiveWriteFailed, "/store", "", 0});

  REQUIRE(rows.size() == 1U);
  CHECK(rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::session_install_failed);
  CHECK_FALSE(rows.front().detail.has_value());
  std::filesystem::remove_all(home);
}

TEST_CASE("a fanned containment error stays outside the errno family") {
  const auto home = make_tmp("fanned-containment");
  const auto rows = fanned_rows(
      home, {codex_entry("0.144.1")},
      biv::BivError{biv::ErrKind::ArchiveWriteFailed, "/store",
                    "containment_refused", EEXIST});

  REQUIRE(rows.size() == 1U);
  CHECK(rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(rows.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK_FALSE(rows.front().detail.has_value());
  std::filesystem::remove_all(home);
}
