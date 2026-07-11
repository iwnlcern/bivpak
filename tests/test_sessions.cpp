#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/open/sessions.hpp"

namespace {

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

}  // namespace

TEST_CASE("session preview groups manifest agents and flags unsupported rows") {
  const auto home = std::filesystem::temp_directory_path() /
                    ("biv-sessions-preview-" + std::to_string(::getpid()));
  std::filesystem::remove_all(home);
  std::filesystem::create_directories(home);
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
  const auto home = std::filesystem::temp_directory_path() /
                    ("biv-sessions-skip-" + std::to_string(::getpid()));
  std::filesystem::remove_all(home);
  std::filesystem::create_directories(home);
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
  CHECK(outcome->rows.front().row == biv::core_sessions::SessionRowReport::Row::skipped);
  CHECK(outcome->rows.front().reason == "unknown-agent");
  CHECK_FALSE(read_called);
  CHECK(outcome->activation.empty());
  std::filesystem::remove_all(home);
}
