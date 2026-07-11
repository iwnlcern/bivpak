#include <string>

#include <catch2/catch_test_macros.hpp>

#include "core/open/render.hpp"

TEST_CASE("prompt B renders counts provenance and trust warning") {
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::AgentPreview agent;
  agent.agent = "future-tool";
  agent.parent_count = 2;
  agent.child_count = 1;
  agent.store = biv::adapters::Store{.root = "/tmp/future-store",
                                     .locators = {},
                                     .tier = biv::adapters::DiscoveryTier::defaults,
                                     .archived = false};
  preview.agents.push_back(std::move(agent));
  biv::manifest::Manifest manifest;
  manifest.source_path = "/tmp/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-11T00:00:00Z";

  const auto text = biv::open_render::render_prompt_b(preview, manifest);
  CHECK(text.find("future-tool") != std::string::npos);
  CHECK(text.find("3 session(s)") != std::string::npos);
  CHECK(text.find("/tmp/future-store") != std::string::npos);
  CHECK(text.find("/tmp/source") != std::string::npos);
  CHECK(text.find(biv::open_render::kTrustWarning) != std::string::npos);
  CHECK(text.find("[y/N]") != std::string::npos);
}

TEST_CASE("session summary renders outcomes activation and caveats from data") {
  biv::core_sessions::SessionsOutcome outcome;
  outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::installed,
      .reason = std::nullopt,
      .installed_session_id = "new-id",
      .host_version_unverified = true,
      .activation_suppressed = false,
      .live_at_pack = true});
  outcome.activation.push_back({.agent = "future-tool", .command = "future resume new-id"});
  outcome.caveats.push_back({"picker_gap", "not listed in picker"});

  const auto text = biv::open_render::render_summary(outcome, false);
  CHECK(text.find("future-tool") != std::string::npos);
  CHECK(text.find("new-id") != std::string::npos);
  CHECK(text.find("future resume new-id") != std::string::npos);
  CHECK(text.find("not listed in picker") != std::string::npos);
  CHECK(text.find("live at pack") != std::string::npos);
}
