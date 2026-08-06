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
  validated.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"1.2.3"}, false);
  biv::core_sessions::AgentPreview unverified;
  unverified.agent = "future-two";
  unverified.parent_count = 1;
  unverified.store = biv::adapters::Store{.root = "/tmp/store-two",
                                           .locators = {},
                                           .tier = biv::adapters::DiscoveryTier::defaults,
                                           .archived = false};
  unverified.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false);
  biv::core_sessions::AgentPreview absent;
  absent.agent = "future-three";
  absent.parent_count = 1;
  absent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::absent, std::nullopt, false);
  preview.agents = {validated, unverified, absent};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/tmp/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-11T00:00:00Z";

  const std::string expected =
      "This image contains agent sessions that can be imported into your host stores:\n\n"
      "  future-one: 3 session(s) (2 parent + 1 child) -> /tmp/store-one\n"
      "  future-two: 1 session(s) (1 parent + 0 child) -> /tmp/store-two\n"
      "  future-two: host version unreadable \u2014 make future-two --version return one readable version and retry; sessions will not be installed or staged\n"
      "  future-three: 1 session(s) (1 parent + 0 child) -> <not found>\n"
      "  future-three: not validated on this host (agent store absent) \u2014 sessions will not be installed or staged\n\n"
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
      .live_at_pack = true,
      .detail = std::nullopt});
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
  codex.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, true,
      {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = "codex",
          .requested = "/opt/pinned/codex",
          .executed = "/opt/pinned/codex",
          .pinned = true,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = "codex-cli 0.144.4\n",
          .parsed = "0.144.4"});
  biv::core_sessions::AgentPreview claude;
  claude.agent = "claude-code";
  claude.parent_count = 1;
  claude.store = biv::adapters::Store{
      .root = "/tmp/claude",
      .locators = {},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false};
  claude.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false,
      false, {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = "claude-code",
          .requested = std::nullopt,
          .executed = "/usr/local/bin/claude",
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::timeout,
          .exit_code = -1,
          .raw = "",
          .parsed = std::nullopt});
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
  const auto readable = text.find(
      "readable; minimum 0.142; surveyed through 0.144", codex_probe);
  const auto claude_failure =
      text.find("claude-code: version probe failed (timeout after 2000ms)");
  const auto recovery = text.find(
      "make claude-code --version return one readable version and retry; "
      "sessions will not be installed or staged",
      claude_failure);
  const auto consent = text.find("Import these sessions");
  REQUIRE(codex_probe != std::string::npos);
  REQUIRE(pinned != std::string::npos);
  REQUIRE(readable != std::string::npos);
  REQUIRE(claude_failure != std::string::npos);
  REQUIRE(recovery != std::string::npos);
  REQUIRE(consent != std::string::npos);
  CHECK(text.find("/usr/local/bin/claude --version -> <no output>",
                  claude_failure) != std::string::npos);
  CHECK(codex_probe < consent);
  CHECK(claude_failure < consent);
  CHECK(text.find("host version unreadable", claude_failure) !=
        std::string::npos);

  biv::core_sessions::AgentPreview unwired_agent;
  unwired_agent.agent = "codex";
  unwired_agent.parent_count = 1;
  unwired_agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false,
      true);
  biv::core_sessions::SessionPreview unwired_preview;
  unwired_preview.agents = {std::move(unwired_agent)};
  biv::manifest::Manifest unwired_manifest;
  unwired_manifest.source_path = "/source";
  unwired_manifest.app_version = "0.1.0";
  unwired_manifest.created_at = "2026-07-18T00:00:00Z";

  const auto unwired_text =
      biv::open_render::render_prompt_b(unwired_preview, unwired_manifest);

  CHECK(unwired_text.find("version probe failed") == std::string::npos);
  CHECK(unwired_text.find("host version unreadable") != std::string::npos);
  CHECK(unwired_text.find("make codex --version return one readable version") !=
        std::string::npos);
}

TEST_CASE(
    "store-absent capability is never disclosed as readable before consent") {
  biv::core_sessions::AgentPreview codex;
  codex.agent = "codex";
  codex.parent_count = 1;
  codex.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::absent, std::nullopt, false, true,
      {.collect = false, .install = false, .rewrite = false},
      biv::support::ProbeEvidence{
          .agent = "codex",
          .requested = std::nullopt,
          .executed = "/usr/local/bin/codex",
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = "codex-cli 0.144.4\n",
          .parsed = "0.144.4"});
  biv::core_sessions::SessionPreview preview;
  preview.agents = {std::move(codex)};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-17T00:00:00Z";

  const auto text = biv::open_render::render_probe_disclosure(preview) +
                    biv::open_render::render_prompt_b(preview, manifest);

  const auto absent = text.find(
      "codex: not validated on this host (agent store absent)");
  const auto consent = text.find("Import these sessions");
  REQUIRE(absent != std::string::npos);
  REQUIRE(consent != std::string::npos);
  CHECK(absent < consent);
  CHECK(text.find("readable; minimum") == std::string::npos);
  CHECK(text.find("version probe failed") == std::string::npos);
}

TEST_CASE("probe failure disclosure distinguishes typed execution failures") {
  const auto render_failure = [](const biv::support::ProbeOutcome outcome) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = "codex";
    agent.parent_count = 1;
    agent.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::unreadable, std::nullopt, false,
        true, {}, biv::support::ProbeEvidence{
            .agent = "codex",
            .requested = "/opt/pinned/codex",
            .executed = std::nullopt,
            .pinned = true,
            .outcome = outcome,
            .exit_code = -1,
            .raw = "",
            .parsed = std::nullopt});
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

TEST_CASE("Task 6 prompt discloses readable versions above the survey watermark") {
  const auto forward = [](std::string agent, std::string executable,
                          std::string raw, std::string parsed) {
    biv::core_sessions::AgentPreview preview;
    preview.agent = std::move(agent);
    preview.parent_count = 1;
    preview.store = biv::adapters::Store{
        .root = "/tmp/store",
        .locators = {},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false};
    preview.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable, parsed, true, false,
        {.collect = true, .install = false, .rewrite = false},
        biv::support::ProbeEvidence{
            .agent = preview.agent,
            .requested = std::nullopt,
            .executed = std::move(executable),
            .pinned = false,
            .outcome = biv::support::ProbeOutcome::ok,
            .exit_code = 0,
            .raw = std::move(raw),
            .parsed = parsed});
    return preview;
  };
  biv::core_sessions::SessionPreview preview;
  preview.agents = {
      forward("codex", "/usr/bin/codex", "codex-cli 0.300.0\n",
              "0.300.0"),
      forward("claude-code", "/usr/bin/claude",
              "2.9.0 (Claude Code)\n", "2.9.0")};
  biv::manifest::Manifest manifest;
  manifest.source_path = "/source";
  manifest.app_version = "0.1.0";
  manifest.created_at = "2026-07-17T00:00:00Z";

  const auto text =
      biv::open_render::render_probe_disclosure(preview) +
      biv::open_render::render_prompt_b(preview, manifest);
  const auto consent = text.find("Import these sessions");
  const auto codex = text.find("codex-cli 0.300.0");
  const auto claude = text.find("2.9.0 (Claude Code)");
  REQUIRE(consent != std::string::npos);
  REQUIRE(codex != std::string::npos);
  REQUIRE(claude != std::string::npos);
  CHECK(text.find("readable; minimum 0.142; surveyed through 0.144", codex) <
        consent);
  CHECK(text.find("readable; minimum 2.1; surveyed through 2.1", claude) <
        consent);
  const auto codex_loud = text.find(
      "codex host version 0.300.0 is newer than surveyed through 0.144; "
      "session import compatibility is uncertain");
  const auto claude_loud = text.find(
      "claude-code host version 2.9.0 is newer than surveyed through 2.1; "
      "session import compatibility is uncertain");
  REQUIRE(codex_loud != std::string::npos);
  REQUIRE(claude_loud != std::string::npos);
  CHECK(codex_loud < consent);
  CHECK(claude_loud < consent);
  CHECK(text.find("refuses this agent's sessions") == std::string::npos);
}

TEST_CASE("Task 6 survey boundary is quiet while one line above is loud") {
  const auto render = [](std::string agent, std::string version,
                         const bool newer_than_survey) {
    biv::support::ProbeEvidence probe{
        .agent = agent,
        .requested = std::nullopt,
        .executed = "/usr/bin/" + agent,
        .pinned = false,
        .outcome = biv::support::ProbeOutcome::ok,
        .exit_code = 0,
        .raw = version + "\n",
        .parsed = version};
    biv::core_sessions::AgentPreview agent_preview;
    agent_preview.agent = std::move(agent);
    agent_preview.parent_count = 1;
    agent_preview.store = biv::adapters::Store{
        .root = "/tmp/store",
        .locators = {},
        .tier = biv::adapters::DiscoveryTier::defaults,
        .archived = false};
    agent_preview.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable, version,
        newer_than_survey, false,
        {.collect = true, .install = true, .rewrite = true}, std::move(probe));
    biv::core_sessions::SessionPreview preview;
    preview.agents = {std::move(agent_preview)};
    return biv::open_render::render_probe_disclosure(preview);
  };

  const auto codex_at = render("codex", "0.144.9", false);
  const auto codex_above = render("codex", "0.145.0", true);
  const auto claude_at = render("claude-code", "2.1.207", false);
  const auto claude_above = render("claude-code", "2.2.0", true);

  CHECK(codex_at.find("session import compatibility is uncertain") ==
        std::string::npos);
  CHECK(claude_at.find("session import compatibility is uncertain") ==
        std::string::npos);
  CHECK(codex_above.find(
            "codex host version 0.145.0 is newer than surveyed through 0.144") !=
        std::string::npos);
  CHECK(claude_above.find(
            "claude-code host version 2.2.0 is newer than surveyed through 2.1") !=
        std::string::npos);
}

TEST_CASE("Task 6 newer disclosure is driven by capability state without probe evidence") {
  biv::core_sessions::AgentPreview agent;
  agent.agent = "codex";
  agent.parent_count = 1;
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.300.0"}, true);
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(agent));

  const auto text = biv::open_render::render_probe_disclosure(preview);
  const std::string loud =
      "codex host version 0.300.0 is newer than surveyed through 0.144; "
      "session import compatibility is uncertain";
  const auto first = text.find(loud);
  REQUIRE(first != std::string::npos);
  CHECK(text.find(loud, first + loud.size()) == std::string::npos);
  CHECK(text.find("--version ->") == std::string::npos);
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
       .live_at_pack = false,
       .detail = std::nullopt},
      {.agent = "claude-code",
       .image_session_id = "old-two",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "minted-two",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt},
      {.agent = "claude-code",
       .image_session_id = "old-failed",
       .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
       .reason = "verify-hits",
       .installed_session_id = "minted-failed",
       .host_version_unverified = false,
       .activation_suppressed = true,
       .live_at_pack = false,
       .detail = std::nullopt},
      {.agent = "codex",
       .image_session_id = "old-three",
       .row = biv::core_sessions::SessionRowReport::Row::installed,
       .reason = std::nullopt,
       .installed_session_id = "minted-three",
       .host_version_unverified = false,
       .activation_suppressed = false,
       .live_at_pack = false,
       .detail = std::nullopt}};
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
    agent.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable,
        std::optional<std::string>{"0.144.4"}, false, false,
        {.collect = true, .install = true, .rewrite = true},
        biv::support::ProbeEvidence{
            .agent = "codex",
            .requested = std::nullopt,
            .executed = "/usr/bin/codex",
            .pinned = false,
            .outcome = biv::support::ProbeOutcome::ok,
            .exit_code = 0,
            .raw = std::move(raw),
            .parsed = "0.144.4"});
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
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, false,
      {.collect = true, .install = true, .rewrite = true},
      biv::support::ProbeEvidence{
          .agent = "codex",
          .requested = std::nullopt,
          .executed = "/usr/bin/codex",
          .pinned = false,
          .outcome = biv::support::ProbeOutcome::ok,
          .exit_code = 0,
          .raw = raw,
          .parsed = "0.144.4"});
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

TEST_CASE("no-detail session rows render byte-identically to the pre-carrier baseline") {
  biv::core_sessions::SessionsOutcome outcome;
  outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::installed,
      .reason = std::nullopt,
      .installed_session_id = "new-id",
      .host_version_unverified = false,
      .activation_suppressed = false,
      .live_at_pack = false,
      .detail = std::nullopt});
  outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "failed-id",
      .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
      .reason = "error",
      .installed_session_id = std::nullopt,
      .host_version_unverified = false,
      .activation_suppressed = true,
      .live_at_pack = false,
      .detail = std::nullopt});

  const auto text =
      biv::open_render::render_summary(outcome, true, "/tmp/restored");

  // ORACLE RULE: captured at BASE cd61ac6, before SessionRowReport gained a
  // detail field. NEVER regenerate this literal from the renderer.
  CHECK(text == R"(Session import summary:
  future-tool: old-id -> installed as new-id
  future-tool: failed-id -> failed (error)
)");
}

TEST_CASE("an adapter-authored detail reaches the rendered summary verbatim") {
  biv::core_sessions::SessionsOutcome outcome;
  outcome.rows.push_back(biv::core_sessions::SessionRowReport{
      .agent = "future-tool",
      .image_session_id = "old-id",
      .row = biv::core_sessions::SessionRowReport::Row::session_install_failed,
      .reason = "error",
      .installed_session_id = std::nullopt,
      .host_version_unverified = false,
      .activation_suppressed = true,
      .live_at_pack = false,
      .detail = "capability_refused"});

  const auto text =
      biv::open_render::render_summary(outcome, true, "/tmp/restored");

  CHECK(text.find("[capability_refused]") != std::string::npos);
  CHECK(text.find("capability-refused") == std::string::npos);
}
