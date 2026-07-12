#include <string>

#include <catch2/catch_test_macros.hpp>

#include "core/open/render.hpp"

TEST_CASE("prompt B renders counts provenance and trust warning") {
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::AgentPreview validated;
  validated.agent = "future-one";
  validated.parent_count = 2;
  validated.child_count = 1;
  validated.store = biv::adapters::Store{.root = "/tmp/store-one",
                                          .locators = {},
                                          .tier = biv::adapters::DiscoveryTier::defaults,
                                          .archived = false};
  validated.caps = biv::adapters::Capabilities{.agent_version = "1.2.3",
                                                .validated_range = "1.x",
                                                .verdict = biv::adapters::Capabilities::Verdict::validated,
                                                .long_path_keys_pinned = false,
                                                .per_verb = {}};
  biv::core_sessions::AgentPreview unverified;
  unverified.agent = "future-two";
  unverified.parent_count = 1;
  unverified.store = biv::adapters::Store{.root = "/tmp/store-two",
                                           .locators = {},
                                           .tier = biv::adapters::DiscoveryTier::defaults,
                                           .archived = false};
  unverified.caps = biv::adapters::Capabilities{.agent_version = "unknown",
                                                 .validated_range = "2.x",
                                                 .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
                                                 .long_path_keys_pinned = false,
                                                 .per_verb = {}};
  biv::core_sessions::AgentPreview absent;
  absent.agent = "future-three";
  absent.parent_count = 1;
  absent.caps = biv::adapters::Capabilities{.agent_version = "unknown",
                                            .validated_range = "3.x",
                                            .verdict = biv::adapters::Capabilities::Verdict::absent,
                                            .long_path_keys_pinned = false,
                                            .per_verb = {}};
  preview.agents = {validated, unverified, absent};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/tmp/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-11T00:00:00Z";

  const std::string expected =
      "This image contains agent sessions that can be imported into your host stores:\n\n"
      "  future-one: 3 session(s) (2 parent + 1 child) -> /tmp/store-one\n"
      "  future-two: 1 session(s) (1 parent + 0 child) -> /tmp/store-two\n"
      "  future-two: host version unverified \u2014 import proceeds on the image entry's version\n"
      "  future-three: 1 session(s) (1 parent + 0 child) -> <not found>\n"
      "  future-three: not validated on this host (agent store absent) \u2014 consent-yes will report FAILED for this agent's sessions (no staging in Step 3)\n\n"
      "Image provenance: packed from /tmp/source by biv 0.1.0 at 2026-07-11T00:00:00Z.\n\n" +
      std::string{biv::open_render::kTrustWarning} +
      "\n\nImport these sessions into your host agent stores? [y/N] ";
  CHECK(biv::open_render::render_prompt_b(preview, manifest) == expected);
}

TEST_CASE("malformed activation falls back to report without inventing a command") {
  biv::core_sessions::SessionsOutcome outcome;
  outcome.activation = {{.agent = "future-one", .command = ""},
                        {.agent = "future-two", .command = "resume\nunsafe"}};
  const auto text = biv::open_render::render_summary(outcome, false);
  CHECK(text.find("future-one: resume command unavailable; see JSON report") != std::string::npos);
  CHECK(text.find("future-two: resume command unavailable; see JSON report") != std::string::npos);
  CHECK(text.find("resume\nunsafe") == std::string::npos);
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
  outcome.caveats.push_back({.agent = "future-tool", .kind = "picker_gap", .note = "not listed in picker"});

  const auto text = biv::open_render::render_summary(outcome, false);
  CHECK(text.find("future-tool") != std::string::npos);
  CHECK(text.find("new-id") != std::string::npos);
  CHECK(text.find("future resume new-id") != std::string::npos);
  CHECK(text.find("not listed in picker") != std::string::npos);
  CHECK(text.find("live at pack") != std::string::npos);
}
