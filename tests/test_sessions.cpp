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

// R-3.45 / m-3 014309 — the SEALED FUTURE detail domains (Addendum-3 §A3.6 / §A3.4 item 3):
//   reason "verify-hits" => detail in {origin_path, origin_id, undecodable_line}
//   ambient reason       => detail is a pinned uppercase POSIX errno symbol
// NOT YET SHIPPED. Verified at 8a3e8c45: those three literals have ZERO quoted
// occurrences under src/. Production today emits reason="verify-hits" with
// detail="rewrite_verify_failed" (adapters/claude_code/install.cpp:582-583 ->
// core/open/sessions.cpp:309 verbatim, :318 relabels the reason).
// These predicates therefore describe the FUTURE domain and are exercised ONLY
// against hand-constructed rows. They observe no producer. R-3.45 is fixture-owed
// and "assertable only in fixtures" (RESIDUALS.md:799), which is why that is enough.
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

class CountingAdapter final : public biv::adapters::AgentAdapter {
 public:
  mutable std::size_t install_calls{0};
  mutable std::optional<biv::manifest::PackerHome> seen_packer_home;
  biv::adapters::InstallResult install_result;

  std::string_view id() const override { return "fixture-agent"; }
  biv::expected<std::vector<biv::adapters::Store>> discover(
      const biv::adapters::Env&) const override {
    return std::vector<biv::adapters::Store>{};
  }
  const biv::adapters::Inventory& state_inventory() const override {
    static const biv::adapters::Inventory inventory{};
    return inventory;
  }
  biv::expected<biv::adapters::CollectReport> collect(
      const std::filesystem::path&,
      std::span<const biv::adapters::Store>) const override {
    return biv::adapters::CollectReport{};
  }
  biv::expected<biv::adapters::InstallResult> install(
      const biv::adapters::InstallTarget& target, biv::adapters::Consent,
      std::span<const biv::manifest::AgentSessionEntry>) const override {
    ++install_calls;
    seen_packer_home = target.packer_home;
    return install_result;
  }
  biv::expected<biv::adapters::RewriteReport> rewrite(
      std::span<const biv::adapters::SessionRecord>,
      const biv::adapters::InstallTarget&) const override {
    return biv::adapters::RewriteReport{};
  }
  biv::adapters::Capabilities capabilities(
      const biv::adapters::Host&) const override {
    return biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::absent, std::nullopt, false);
  }
};

}  // namespace

TEST_CASE("FX-VF-O5 unreadable hosts produce CANON-3 rows before consent") {
  // FX-MG-9's former evaluability input class is extinct after A7.5. This
  // fixture carries its stronger M4-C1 burden at the live unreadable gate.
  for (const std::string agent : {"codex", "claude-code"}) {
    DYNAMIC_SECTION(agent) {
      auto first = entry(agent);
      first.original_session_ids.primary =
          agent == "codex" ? "cx-0001" : "cl-0001";
      auto second = entry(agent);
      second.original_session_ids.primary =
          agent == "codex" ? "cx-0002" : "cl-0002";
      const auto manifest = model({first, second});

      CountingAdapter adapter;
      biv::core_sessions::AgentPreview preview_agent;
      preview_agent.agent = agent;
      preview_agent.parent_count = 2;
      preview_agent.known_adapter = true;
      preview_agent.store = biv::adapters::Store{
          .root = "/tmp/fixture-store", .locators = {}};
      preview_agent.caps = biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::unreadable, std::nullopt,
          false);
      preview_agent.adapter = &adapter;
      biv::core_sessions::SessionPreview preview;
      preview.agents.push_back(std::move(preview_agent));

      biv::core_sessions::ConsentDecision consent;
      consent.per_agent.emplace_back(agent, false);
      const auto workspace = make_tmp("o5-" + agent);
      std::size_t member_reads = 0;
      const auto outcome = biv::core_sessions::run_session_leg(
          preview, consent, manifest, workspace,
          [&](std::string_view)
              -> biv::expected<std::vector<std::byte>> {
            ++member_reads;
            return std::vector<std::byte>{};
          });

      REQUIRE(outcome);
      REQUIRE(outcome->rows.size() == 2U);
      for (std::size_t index = 0; index < outcome->rows.size(); ++index) {
        const auto& row = outcome->rows.at(index);
        CHECK(row.agent == agent);
        CHECK(row.image_session_id ==
              (index == 0 ? first.original_session_ids.primary
                          : second.original_session_ids.primary));
        CHECK(row.row == biv::core_sessions::SessionRowReport::Row::
                             agent_not_validated_failed);
        CHECK(row.reason ==
              std::optional<std::string>{"host-version-unreadable"});
        CHECK_FALSE(row.installed_session_id.has_value());
        CHECK_FALSE(row.host_version_unverified);
        CHECK(row.activation_suppressed);
        CHECK_FALSE(row.live_at_pack);
        CHECK_FALSE(row.detail.has_value());  // pending-pin comparator input
      }
      CHECK(adapter.install_calls == 0U);
      CHECK(member_reads == 0U);
      CHECK_FALSE(std::filesystem::exists(workspace / ".biv"));
      CHECK(biv::report::exit_for_sessions(*outcome) == 2);
      std::filesystem::remove_all(workspace);
    }
  }
}

TEST_CASE("absent stores produce refusal rows before consent or adapter calls") {
  for (const std::string agent : {"codex", "claude-code"}) {
    DYNAMIC_SECTION(agent) {
      const auto manifest = model({entry(agent)});
      CountingAdapter adapter;
      biv::core_sessions::AgentPreview preview_agent;
      preview_agent.agent = agent;
      preview_agent.parent_count = 1;
      preview_agent.known_adapter = true;
      preview_agent.caps = biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::absent, std::nullopt, false);
      preview_agent.adapter = &adapter;
      biv::core_sessions::SessionPreview preview;
      preview.agents.push_back(std::move(preview_agent));
      biv::core_sessions::ConsentDecision consent;
      consent.per_agent.emplace_back(agent, false);
      const auto workspace = make_tmp("absent-" + agent);
      std::size_t member_reads = 0;

      const auto outcome = biv::core_sessions::run_session_leg(
          preview, consent, manifest, workspace,
          [&](std::string_view)
              -> biv::expected<std::vector<std::byte>> {
            ++member_reads;
            return std::vector<std::byte>{};
          });

      REQUIRE(outcome);
      REQUIRE(outcome->rows.size() == 1U);
      const auto& row = outcome->rows.front();
      CHECK(row.row == biv::core_sessions::SessionRowReport::Row::
                           agent_not_validated_failed);
      CHECK(row.reason == std::optional<std::string>{"store-absent"});
      CHECK_FALSE(row.installed_session_id.has_value());
      CHECK_FALSE(row.host_version_unverified);
      CHECK(row.activation_suppressed);
      CHECK_FALSE(row.detail.has_value());
      CHECK(adapter.install_calls == 0U);
      CHECK(member_reads == 0U);
      CHECK(biv::report::exit_for_sessions(*outcome) == 2);
      std::filesystem::remove_all(workspace);
    }
  }
}

TEST_CASE("version refusal details map to closed reasons without changing siblings") {
  const auto workspace = make_tmp("version-detail-map");
  auto newer = entry("fixture-agent");
  newer.original_session_ids.primary = "basis-newer";
  auto unorderable = entry("fixture-agent");
  unorderable.original_session_ids.primary = "basis-unorderable";
  auto collision = entry("fixture-agent");
  collision.original_session_ids.primary = "collision";
  const auto manifest =
      model({std::move(newer), std::move(unorderable), std::move(collision)});
  CountingAdapter adapter;
  adapter.install_result.sessions = {
      {.image_session_id = manifest.agent_sessions.at(0).original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::failed,
       .reason = std::nullopt,
       .content_rewrite = std::nullopt,
       .verify = {},
       .detail = "basis_newer_than_host"},
      {.image_session_id = manifest.agent_sessions.at(1).original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::failed,
       .reason = std::nullopt,
       .content_rewrite = std::nullopt,
       .verify = {},
       .detail = "basis_unorderable"},
      {.image_session_id = manifest.agent_sessions.at(2).original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::failed,
       .reason = "collision_refused",
       .content_rewrite = std::nullopt,
       .verify = {},
       .detail = "collision_refused"},
  };
  biv::core_sessions::AgentPreview agent;
  agent.agent = "fixture-agent";
  agent.parent_count = 3;
  agent.known_adapter = true;
  agent.store =
      biv::adapters::Store{.root = workspace, .locators = {}};
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  agent.adapter = &adapter;
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(agent));
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back("fixture-agent", true);

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 3U);
  CHECK(outcome->rows.at(0).row == biv::core_sessions::SessionRowReport::Row::
                                        agent_not_validated_failed);
  CHECK(outcome->rows.at(0).image_session_id == "basis-newer");
  CHECK(outcome->rows.at(0).reason == "basis-newer-than-host");
  CHECK(outcome->rows.at(0).detail == "basis_newer_than_host");
  CHECK(outcome->rows.at(1).row == biv::core_sessions::SessionRowReport::Row::
                                        agent_not_validated_failed);
  CHECK(outcome->rows.at(1).image_session_id == "basis-unorderable");
  CHECK(outcome->rows.at(1).reason == "basis-unorderable");
  CHECK(outcome->rows.at(1).detail == "basis_unorderable");
  CHECK(outcome->rows.at(2).row ==
        biv::core_sessions::SessionRowReport::Row::session_install_failed);
  CHECK(outcome->rows.at(2).image_session_id == "collision");
  CHECK(outcome->rows.at(2).reason == "collision_refused");
  CHECK(outcome->rows.at(2).detail == "collision_refused");
  CHECK(adapter.install_calls == 1U);
  std::filesystem::remove_all(workspace);
}

TEST_CASE("run_session_leg transports packer_home to the adapter once per image") {
  const auto workspace = make_tmp("packer-home-present");
  auto eligible = entry("fixture-agent");
  auto manifest = model({std::move(eligible)});
  manifest.packer_home = biv::manifest::PackerHome{
      "/Users/packer", biv::manifest::PathFlavor::posix};
  CountingAdapter adapter;
  adapter.install_result.sessions = {{
      .image_session_id = manifest.agent_sessions.front().original_session_ids.primary,
      .outcome = biv::adapters::InstallSessionOutcome::Outcome::installed,
      .reason = std::nullopt,
      .content_rewrite = std::nullopt,
      .verify = {},
      .detail = std::nullopt,
  }};
  biv::core_sessions::AgentPreview agent;
  agent.agent = "fixture-agent";
  agent.parent_count = 1;
  agent.known_adapter = true;
  agent.store = biv::adapters::Store{.root = workspace, .locators = {}};
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  agent.adapter = &adapter;
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(agent));
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back("fixture-agent", true);

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  const biv::manifest::PackerHome expected{
      "/Users/packer", biv::manifest::PathFlavor::posix};
  REQUIRE(adapter.install_calls == 1U);
  REQUIRE(adapter.seen_packer_home == expected);
  std::filesystem::remove_all(workspace);
}

TEST_CASE("run_session_leg passes absent packer_home through unchanged") {
  const auto workspace = make_tmp("packer-home-absent");
  auto eligible = entry("fixture-agent");
  auto manifest = model({std::move(eligible)});
  CountingAdapter adapter;
  adapter.install_result.sessions = {{
      .image_session_id = manifest.agent_sessions.front().original_session_ids.primary,
      .outcome = biv::adapters::InstallSessionOutcome::Outcome::installed,
      .reason = std::nullopt,
      .content_rewrite = std::nullopt,
      .verify = {},
      .detail = std::nullopt,
  }};
  biv::core_sessions::AgentPreview agent;
  agent.agent = "fixture-agent";
  agent.parent_count = 1;
  agent.known_adapter = true;
  agent.store = biv::adapters::Store{.root = workspace, .locators = {}};
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  agent.adapter = &adapter;
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(agent));
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back("fixture-agent", true);

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(adapter.install_calls == 1U);
  REQUIRE(adapter.seen_packer_home == std::nullopt);
  std::filesystem::remove_all(workspace);
}

TEST_CASE("the cross-family control catches an illegal constructed reason/detail pair") {
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
    CHECK(agent.caps->verdict() ==
          biv::adapters::Capabilities::Verdict::absent);
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

TEST_CASE("Codex session outcomes map admitted and refusing version directions") {
  struct VersionCase {
    std::string_view image_version;
    std::string_view host_version;
    bool accepted;
  };
  constexpr VersionCase cases[]{{"0.142.5", "0.142.5", true},
                                {"0.144.1", "0.144.1", true},
                                {"0.143.0", "0.143.0", true},
                                {"0.145.0", "0.145.0", true},
                                {"0.61.0", "0.61.0", true},
                                {"0.145.0", "0.144.1", false}};
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1440";

  for (const auto& version_case : cases) {
    DYNAMIC_SECTION("image " << version_case.image_version << " on host "
                              << version_case.host_version) {
      const auto home =
          make_tmp("codex-range-" + std::string{version_case.image_version} +
                   "-on-" + std::string{version_case.host_version});
      const auto store = home / ".codex";
      const auto workspace = home / "workspace";
      std::filesystem::create_directories(store);
      std::filesystem::create_directories(workspace);
      {
        std::ofstream marker{store / "version.json"};
        marker << "{\"version\":\"" << version_case.host_version
               << "\"}\n";
      }
      auto manifest = model({codex_entry(version_case.image_version)});
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
                                               .raw = "codex-cli " + std::string{version_case.host_version},
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
          std::string{version_case.image_version} + "\"}}\n");
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
        CHECK(row.reason ==
              std::optional<std::string>{"basis-newer-than-host"});
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

TEST_CASE(
    "Codex session leg preserves a version refusal beside a verify-hit sibling") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1440";
  constexpr std::string_view verify_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1441";
  const auto home = make_tmp("codex-refusal-verify-cohort");
  const auto store = home / ".codex";
  const auto workspace = home / "workspace";
  std::filesystem::create_directories(store);
  std::filesystem::create_directories(workspace);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.144.1\"}\n";
  }
  auto refused = codex_entry("0.145.0");
  auto verify = codex_entry("0.144.1");
  verify.original_session_ids.primary = verify_id;
  verify.artifacts = {
      "agents/codex/" + std::string{verify_id} + ".jsonl"};
  auto manifest = model({refused, verify});
  const biv::adapters::Host host{
      .home = home,
      .env = env(home),
      .version_probe = [&](const std::string_view agent,
                           const std::optional<std::filesystem::path>&)
          -> biv::expected<biv::support::ProbeEvidence> {
        return biv::support::ProbeEvidence{
            .agent = std::string{agent},
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
  auto hostile = bytes("{\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                       std::string{verify_id} + "\",\"session_id\":\"" +
                       std::string{verify_id} +
                       "\",\"cwd\":\"/ws/proj\"}}");
  hostile.push_back(static_cast<std::byte>(0xff));
  hostile.push_back(static_cast<std::byte>('\n'));
  const auto verify_artifact = verify.artifacts.front();
  const biv::adapters::MemberRead reader =
      [&](const std::string_view path)
          -> biv::expected<std::vector<std::byte>> {
    if (path == verify_artifact) {
      return hostile;
    }
    return std::unexpected(
        biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
  };

  const auto outcome = biv::core_sessions::run_session_leg(
      *preview, consent, manifest, workspace, reader);

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 2U);
  const auto row_for = [&](const std::string_view id) {
    return std::ranges::find_if(outcome->rows, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused_id);
  const auto verify_row = row_for(verify_id);
  REQUIRE(refused_row != outcome->rows.end());
  REQUIRE(verify_row != outcome->rows.end());
  CHECK(refused_row->row == biv::core_sessions::SessionRowReport::Row::
                                 agent_not_validated_failed);
  CHECK(refused_row->reason ==
        std::optional<std::string>{"basis-newer-than-host"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_newer_than_host"});
  CHECK(refused_row->activation_suppressed);
  CHECK(verify_row->row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(verify_row->reason == std::optional<std::string>{"verify-hits"});
  CHECK(verify_row->detail ==
        std::optional<std::string>{"rewrite_verify_failed"});
  CHECK(verify_row->activation_suppressed);
  CHECK(outcome->activation.empty());
  CHECK_FALSE(std::filesystem::exists(store / "sessions"));
  std::filesystem::remove_all(home);
}

TEST_CASE("unreadable probes stop before adapter-authored detail exists") {
  const auto home = make_tmp("carrier-verbatim");
  const auto store = home / ".codex";
  const auto workspace = home / "workspace";
  std::filesystem::create_directories(store);
  std::filesystem::create_directories(workspace);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.144.1\"}\n";
  }
  // A7 moves this former adapter call to the agent-level unreadable gate.
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
  CHECK(outcome->rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::agent_not_validated_failed);
  CHECK(outcome->rows.front().reason ==
        std::optional<std::string>{"host-version-unreadable"});
  CHECK_FALSE(outcome->rows.front().detail.has_value());
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
  CHECK(preview->agents.front().caps->verdict() ==
        biv::adapters::Capabilities::Verdict::readable);
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
