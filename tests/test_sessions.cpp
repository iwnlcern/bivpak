#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/open/sessions.hpp"
#include "core/report/exit_map.hpp"

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

}  // namespace

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
                          {.agent = "future-tool", .command = "future resume bad-id"}};
  std::vector<biv::core_sessions::SessionRowReport> rows{
      {.agent = "future-tool",
       .image_session_id = "clean-image",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "clean-id"},
      {.agent = "future-tool",
       .image_session_id = "bad-image",
       .row = biv::core_sessions::SessionRowReport::Row::containment_refused,
       .reason = "verify-hits",
       .installed_session_id = "bad-id",
       .activation_suppressed = true}};

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
      auto preview = biv::core_sessions::build_preview(manifest, env(home));
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
