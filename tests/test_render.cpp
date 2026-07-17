#include <filesystem>
#include <fstream>
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
                                                .per_verb = {},
                                                .probe = std::nullopt};
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
                                                 .per_verb = {},
                                                 .probe = std::nullopt};
  biv::core_sessions::AgentPreview absent;
  absent.agent = "future-three";
  absent.parent_count = 1;
  absent.caps = biv::adapters::Capabilities{.agent_version = "unknown",
                                            .validated_range = "3.x",
                                            .verdict = biv::adapters::Capabilities::Verdict::absent,
                                            .long_path_keys_pinned = false,
                                            .per_verb = {},
                                            .probe = std::nullopt};
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
  const auto text =
      biv::open_render::render_summary(outcome, false, "/tmp/restored");
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

  const auto text =
      biv::open_render::render_summary(outcome, false, "/tmp/restored");
  CHECK(text.find("future-tool") != std::string::npos);
  CHECK(text.find("new-id") != std::string::npos);
  CHECK(text.find("future resume new-id") != std::string::npos);
  CHECK(text.find("not listed in picker") != std::string::npos);
  CHECK(text.find("live at pack") != std::string::npos);
}

TEST_CASE("Task 5 prompt discloses probe evidence before consent") {
  biv::core_sessions::AgentPreview codex;
  codex.agent = "codex";
  codex.parent_count = 1;
  codex.store = biv::adapters::Store{
      .root = "/tmp/codex",
      .locators = {},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false};
  codex.caps = biv::adapters::Capabilities{
      .agent_version = "0.144.4",
      .validated_range = "0.142.x, 0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::validated,
      .long_path_keys_pinned = true,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = "codex",
          .requested = "/opt/pinned/codex",
          .executed = "/opt/pinned/codex",
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = "codex-cli 0.144.4\n",
          .parsed = "0.144.4"}};
  biv::core_sessions::AgentPreview claude;
  claude.agent = "claude-code";
  claude.parent_count = 1;
  claude.store = biv::adapters::Store{
      .root = "/tmp/claude",
      .locators = {},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false};
  claude.caps = biv::adapters::Capabilities{
      .agent_version = "unknown",
      .validated_range = "2.1.x",
      .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
      .long_path_keys_pinned = false,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = "claude-code",
          .requested = std::nullopt,
          .executed = "/usr/local/bin/claude",
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::timeout,
          .exit_code = -1,
          .raw = "",
          .parsed = std::nullopt}};
  biv::core_sessions::SessionPreview preview;
  preview.agents = {codex, claude};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-17T00:00:00Z";

  const auto text =
      biv::open_render::render_probe_disclosure(preview) +
      biv::open_render::render_prompt_b(preview, manifest);

  const auto codex_probe =
      text.find("/opt/pinned/codex --version -> codex-cli 0.144.4");
  const auto pinned = text.find("(pinned)", codex_probe);
  const auto validated =
      text.find("validated; supported 0.142.x, 0.144.x", codex_probe);
  const auto claude_failure =
      text.find("claude-code: version probe failed (timeout after 2000ms)");
  const auto honest_semantics = text.find(
      "consent-yes installs with host_version_unverified=true when the image "
      "entry's version is supported, and refuses otherwise",
      claude_failure);
  const auto consent = text.find("Import these sessions");
  REQUIRE(codex_probe != std::string::npos);
  REQUIRE(pinned != std::string::npos);
  REQUIRE(validated != std::string::npos);
  REQUIRE(claude_failure != std::string::npos);
  REQUIRE(honest_semantics != std::string::npos);
  REQUIRE(consent != std::string::npos);
  CHECK(text.find("/usr/local/bin/claude --version -> <no output>",
                  claude_failure) != std::string::npos);
  CHECK(codex_probe < consent);
  CHECK(claude_failure < consent);
  CHECK(text.find("stage", claude_failure) == std::string::npos);

  biv::core_sessions::AgentPreview unwired_agent;
  unwired_agent.agent = "codex";
  unwired_agent.parent_count = 1;
  unwired_agent.caps = biv::adapters::Capabilities{
      .agent_version = "unknown",
      .validated_range = "0.142.x, 0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
      .long_path_keys_pinned = true,
      .per_verb = {},
      .probe = std::nullopt};
  biv::core_sessions::SessionPreview unwired_preview;
  unwired_preview.agents = {std::move(unwired_agent)};
  biv::manifest::Manifest unwired_manifest;
  unwired_manifest.source_path = "/source";
  unwired_manifest.app_version = "0.1.0";
  unwired_manifest.created_at = "2026-07-18T00:00:00Z";

  const auto unwired_text =
      biv::open_render::render_prompt_b(unwired_preview, unwired_manifest);

  CHECK(unwired_text.find("version probe failed") == std::string::npos);
  CHECK(unwired_text.find("host version unverified") != std::string::npos);
}

TEST_CASE("probe failure disclosure distinguishes typed execution failures") {
  const auto render_failure = [](const biv::support::ProbeOutcome outcome) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = "codex";
    agent.parent_count = 1;
    agent.caps = biv::adapters::Capabilities{
        .agent_version = "unknown",
        .validated_range = "0.142.x, 0.144.x",
        .verdict = biv::adapters::Capabilities::Verdict::unvalidated_host,
        .long_path_keys_pinned = true,
        .per_verb = {},
        .probe = biv::support::ProbeEvidence{
            .agent = "codex",
            .requested = "/opt/pinned/codex",
            .executed = std::nullopt,
            .pinned = true,
            .outcome = outcome,
            .exit_code = -1,
            .raw = "",
            .parsed = std::nullopt}};
    biv::core_sessions::SessionPreview preview;
    preview.agents = {std::move(agent)};
    biv::manifest::Manifest manifest;
    manifest.source_path = "/source";
    manifest.app_version = "0.1.0";
    manifest.created_at = "2026-07-19T00:00:00Z";
    return biv::open_render::render_probe_disclosure(preview);
  };

  const auto not_executable =
      render_failure(biv::support::ProbeOutcome::not_executable);
  CHECK(not_executable.find("present but not executable") !=
        std::string::npos);
  CHECK(not_executable.find("executable not found") == std::string::npos);
  CHECK(not_executable.find("spawn error") == std::string::npos);

  const auto not_accessible =
      render_failure(biv::support::ProbeOutcome::not_accessible);
  CHECK(not_accessible.find("pinned path resolution failed") !=
        std::string::npos);
  CHECK(not_accessible.find("executable not found") == std::string::npos);
  CHECK(not_accessible.find("present but not executable") ==
        std::string::npos);

  const auto io_error =
      render_failure(biv::support::ProbeOutcome::probe_io_error);
  CHECK(io_error.find("probe I/O readiness failure") != std::string::npos);
  CHECK(io_error.find("timeout after") == std::string::npos);
  CHECK(io_error.find("spawn error") == std::string::npos);
}

TEST_CASE("Task 5 prompt discloses refusal for parsed unsupported versions") {
  const auto unsupported = [](std::string agent, std::string executable,
                              std::string raw, std::string parsed,
                              std::string range) {
    biv::core_sessions::AgentPreview preview;
    preview.agent = std::move(agent);
    preview.parent_count = 1;
    preview.store = biv::adapters::Store{
        .root = "/tmp/store",
        .locators = {},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false};
    preview.caps = biv::adapters::Capabilities{
        .agent_version = parsed,
        .validated_range = std::move(range),
        .verdict = biv::adapters::Capabilities::Verdict::unvalidated,
        .long_path_keys_pinned = false,
        .per_verb = {.collect = true, .install = false, .rewrite = false},
        .probe = biv::support::ProbeEvidence{
            .agent = preview.agent,
            .requested = std::nullopt,
            .executed = std::move(executable),
            .pinned = false,
            .outcome = biv::support::ProbeOutcome::ok,
            .exit_code = 0,
            .raw = std::move(raw),
            .parsed = std::move(parsed)}};
    return preview;
  };
  biv::core_sessions::SessionPreview preview;
  preview.agents = {
      unsupported("codex", "/usr/bin/codex", "codex-cli 0.145.0\n",
                  "0.145.0", "0.142.x, 0.144.x"),
      unsupported("claude-code", "/usr/bin/claude",
                  "2.2.0 (Claude Code)\n", "2.2.0", "2.1.x")};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-17T00:00:00Z";

  const auto text =
      biv::open_render::render_probe_disclosure(preview) +
      biv::open_render::render_prompt_b(preview, manifest);
  const auto consent = text.find("Import these sessions");
  const auto codex = text.find("codex-cli 0.145.0");
  const auto claude = text.find("2.2.0 (Claude Code)");
  const std::string refusal =
      "consent-yes refuses this agent's sessions";

  REQUIRE(consent != std::string::npos);
  REQUIRE(codex != std::string::npos);
  REQUIRE(claude != std::string::npos);
  CHECK(text.find(refusal, codex) < consent);
  CHECK(text.find(refusal, claude) < consent);
}

TEST_CASE(
    "Task 5 summary filters failed activations and pairs clean commands with "
    "the post-collision output") {
  biv::core_sessions::SessionsOutcome outcome;
  outcome.rows = {
      {.agent = "claude-code",
       .image_session_id = "old-one",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "minted-one",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false},
      {.agent = "claude-code",
       .image_session_id = "old-two",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "minted-two",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false},
      {.agent = "claude-code",
       .image_session_id = "old-failed",
       .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
       .reason = "verify-hits",
       .installed_session_id = "minted-failed",
       .host_version_unverified = false,
       .activation_suppressed = true,
       .live_at_pack = false},
      {.agent = "codex",
       .image_session_id = "old-three",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "minted-three",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false}};
  const std::vector<biv::adapters::Activation> candidates{
      {.agent = "claude-code", .command = "claude --resume minted-one"},
      {.agent = "claude-code", .command = "claude --resume minted-two"},
      {.agent = "claude-code", .command = "claude --resume minted-failed"},
      {.agent = "codex", .command = "codex resume minted-three"}};
  outcome.activation =
      biv::core_sessions::filter_activation(candidates, outcome.rows);
  std::string output_text{"/tmp/final dir(1)/\t"};
  output_text.push_back('\x01');
  output_text += "name";
  const std::filesystem::path output{output_text};

  const auto text =
      biv::open_render::render_summary(outcome, false, output);

  CHECK(text.find(
            "resume from /tmp/final\\x20dir(1)/\\t\\x01name: claude --resume "
            "minted-one") != std::string::npos);
  CHECK(text.find(
            "resume from /tmp/final\\x20dir(1)/\\t\\x01name: claude --resume "
            "minted-two") != std::string::npos);
  CHECK(text.find(
            "resume from /tmp/final\\x20dir(1)/\\t\\x01name: codex resume "
            "minted-three") != std::string::npos);
  CHECK(text.find("claude --resume minted-failed") == std::string::npos);
  CHECK(text.find("cd ") == std::string::npos);
  CHECK(text.find("&&") == std::string::npos);
}

TEST_CASE("probe display escapes controls by scalar and preserves non-controls") {
  const auto render_raw = [](std::string raw) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = "codex";
    agent.parent_count = 1;
    agent.store = biv::adapters::Store{
        .root = "/tmp/codex",
        .locators = {},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false};
    agent.caps = biv::adapters::Capabilities{
        .agent_version = "0.144.4",
        .validated_range = "0.144.x",
        .verdict = biv::adapters::Capabilities::Verdict::validated,
        .long_path_keys_pinned = false,
        .per_verb = {.collect = true, .install = true, .rewrite = true},
        .probe = biv::support::ProbeEvidence{
            .agent = "codex",
            .requested = std::nullopt,
            .executed = "/usr/bin/codex",
            .pinned = false,
            .outcome = biv::support::ProbeOutcome::ok,
            .exit_code = 0,
            .raw = std::move(raw),
            .parsed = "0.144.4"}};
    biv::core_sessions::SessionPreview preview;
    preview.agents = {std::move(agent)};
    biv::manifest::Manifest manifest;
    manifest.source_path = "/source";
    manifest.app_version = "0.1.0";
    manifest.created_at = "2026-07-18T00:00:00Z";
    return biv::open_render::render_probe_disclosure(preview);
  };

  std::string controls{"start"};
  controls.push_back('\x01');
  controls.push_back('\x7f');
  controls += "\xC2\x80";
  controls += "\xC2\x9B";
  controls += "\xC4\x80";
  controls.push_back('\n');
  const auto scalar_text = render_raw(controls);
  CHECK(scalar_text.find(
            "start\\u0001\\u007f\\u0080\\u009b\xC4\x80") !=
        std::string::npos);
  CHECK(scalar_text.find("\xC2\x9B") == std::string::npos);

  std::string invalid{"invalid-"};
  invalid.push_back(static_cast<char>(0x9b));
  const auto invalid_text = render_raw(invalid);
  CHECK(invalid_text.find("invalid-\xEF\xBF\xBD") != std::string::npos);
}

TEST_CASE("probe display truncation reports the complete UTF-8 prefix") {
  biv::core_sessions::AgentPreview agent;
  agent.agent = "codex";
  agent.parent_count = 1;
  agent.store = biv::adapters::Store{
      .root = "/tmp/codex",
      .locators = {},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false};
  std::string raw(253, 'a');
  raw += "\xC4\x80";
  raw += "\xC4\x80";
  raw.push_back('z');
  REQUIRE(raw.size() == 258);
  agent.caps = biv::adapters::Capabilities{
      .agent_version = "0.144.4",
      .validated_range = "0.144.x",
      .verdict = biv::adapters::Capabilities::Verdict::validated,
      .long_path_keys_pinned = false,
      .per_verb = {.collect = true, .install = true, .rewrite = true},
      .probe = biv::support::ProbeEvidence{
          .agent = "codex",
          .requested = std::nullopt,
          .executed = "/usr/bin/codex",
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = raw,
          .parsed = "0.144.4"}};
  biv::core_sessions::SessionPreview preview;
  preview.agents = {std::move(agent)};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-18T00:00:00Z";

  const auto text = biv::open_render::render_probe_disclosure(preview);
  const std::string expected_prefix = std::string(253, 'a') + "\xC4\x80";
  CHECK(text.find(
            expected_prefix +
            "\u2026 [truncated, showing 255 of 258 captured bytes]") !=
        std::string::npos);
  CHECK(text.find(std::string(253, 'a') + "\xC4\x80\xC4\x80") ==
        std::string::npos);
}

TEST_CASE("probe timeout disclosure derives from the shared constant") {
  std::ifstream source{std::string{BIV_SOURCE_DIR} +
                       "/src/core/open/render.cpp"};
  REQUIRE(source);
  const std::string text{std::istreambuf_iterator<char>{source},
                         std::istreambuf_iterator<char>{}};
  CHECK(text.find("\"timeout after 2000ms\"") == std::string::npos);
  CHECK(text.find("kProbeTimeout.count()") != std::string::npos);
}
