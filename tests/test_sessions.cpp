#include <algorithm>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>
#include <simdjson.h>

#include "adapters/claude_code/claude_code.hpp"
#include "adapters/codex/codex.hpp"
#include "adapters/rewrite_common.hpp"
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

std::string read_text(const fs::path& path) {
  std::ifstream input{path, std::ios::binary};
  REQUIRE(input);
  return {std::istreambuf_iterator<char>{input},
          std::istreambuf_iterator<char>{}};
}

struct SidecarContent {
  std::vector<biv::adapters::IdMapEntry> id_map;
  std::map<std::pair<std::string, std::string>, std::string>
      row_original_paths;
  std::vector<std::string> provenance_chain;
  std::vector<std::pair<std::string, std::string>> pair_set_applied;
};

SidecarContent read_sidecar_content(const fs::path& path) {
  const auto text = read_text(path);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(text).get(document) == simdjson::SUCCESS);

  SidecarContent content;
  simdjson::dom::array id_map;
  REQUIRE(document["id_map"].get(id_map) == simdjson::SUCCESS);
  for (simdjson::dom::element item : id_map) {
    std::string_view agent;
    std::string_view image_session_id;
    std::string_view installed_session_id;
    std::string_view original_path;
    REQUIRE(item["agent"].get(agent) == simdjson::SUCCESS);
    REQUIRE(item["image_session_id"].get(image_session_id) ==
            simdjson::SUCCESS);
    REQUIRE(item["installed_session_id"].get(installed_session_id) ==
            simdjson::SUCCESS);
    REQUIRE(item["original_path"].get(original_path) == simdjson::SUCCESS);
    biv::adapters::IdMapEntry entry{.agent = std::string{agent},
                                    .image_session_id =
                                        std::string{image_session_id},
                                    .installed_session_id =
                                        std::string{installed_session_id},
                                    .children = {}};
    simdjson::dom::array children;
    REQUIRE(item["children"].get(children) == simdjson::SUCCESS);
    for (simdjson::dom::element child : children) {
      simdjson::dom::array pair;
      REQUIRE(child.get(pair) == simdjson::SUCCESS);
      std::string_view original;
      std::string_view installed;
      REQUIRE(pair.at(0).get(original) == simdjson::SUCCESS);
      REQUIRE(pair.at(1).get(installed) == simdjson::SUCCESS);
      entry.children.emplace_back(original, installed);
    }
    content.id_map.push_back(std::move(entry));
    content.row_original_paths.emplace(
        std::pair{std::string{agent}, std::string{image_session_id}},
        original_path);
  }

  simdjson::dom::array provenance_chain;
  REQUIRE(document["provenance_chain"].get(provenance_chain) ==
          simdjson::SUCCESS);
  for (simdjson::dom::element item : provenance_chain) {
    std::string_view value;
    REQUIRE(item.get(value) == simdjson::SUCCESS);
    content.provenance_chain.emplace_back(value);
  }

  simdjson::dom::array pair_set_applied;
  REQUIRE(document["pair_set_applied"].get(pair_set_applied) ==
          simdjson::SUCCESS);
  for (simdjson::dom::element item : pair_set_applied) {
    simdjson::dom::array pair;
    REQUIRE(item.get(pair) == simdjson::SUCCESS);
    std::string_view original;
    std::string_view staged;
    REQUIRE(pair.at(0).get(original) == simdjson::SUCCESS);
    REQUIRE(pair.at(1).get(staged) == simdjson::SUCCESS);
    content.pair_set_applied.emplace_back(original, staged);
  }

  std::ranges::sort(content.id_map, {}, &biv::adapters::IdMapEntry::agent);
  std::ranges::sort(content.provenance_chain);
  std::ranges::sort(content.pair_set_applied);
  return content;
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
  mutable std::vector<std::optional<biv::manifest::PackerHome>>
      seen_packer_homes;
  mutable std::optional<biv::adapters::Consent> install_consent;
  mutable std::optional<biv::adapters::InstallTarget> install_target;
  biv::adapters::InstallResult install_result;
  std::optional<biv::BivError> install_error;
  std::function<void(const biv::adapters::InstallTarget&)> install_hook;

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
      const biv::adapters::InstallTarget& target, const biv::adapters::Consent consent,
      std::span<const biv::manifest::AgentSessionEntry>) const override {
    ++install_calls;
    seen_packer_homes.push_back(target.packer_home);
    install_consent = consent;
    install_target = target;
    if (install_hook) {
      install_hook(target);
    }
    if (install_error.has_value()) {
      return std::unexpected(*install_error);
    }
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

void configure_staged(CountingAdapter& adapter,
                      const biv::manifest::AgentSessionEntry& record,
                      std::string agent, std::string installed_session_id,
                      std::vector<std::pair<std::string, std::string>>
                          pair_set_applied) {
  adapter.install_result.sessions = {
      {.image_session_id = record.original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::staged,
       .reason = std::nullopt,
       .content_rewrite = "pair",
       .verify = {.origin_path_hits = 0,
                  .origin_id_hits = 0,
                  .artifacts_checked = 1},
       .detail = std::nullopt},
  };
  adapter.install_result.id_map = {
      {.agent = std::move(agent),
       .image_session_id = record.original_session_ids.primary,
       .installed_session_id = std::move(installed_session_id),
       .children = {}},
  };
  adapter.install_result.activation = {
      {.agent = "fixture-agent", .command = "fixture resume minted-session"}};
  adapter.install_result.pair_set_applied = std::move(pair_set_applied);
}

void append_readable_agent(biv::core_sessions::SessionPreview& preview,
                           std::string agent_name, const fs::path& store,
                           CountingAdapter& adapter) {
  biv::core_sessions::AgentPreview agent;
  agent.agent = std::move(agent_name);
  agent.parent_count = 1;
  agent.known_adapter = true;
  agent.store = biv::adapters::Store{.root = store, .locators = {}};
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  agent.adapter = &adapter;
  preview.agents.push_back(std::move(agent));
}

constexpr std::string_view kRealCodexId =
    "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001";
constexpr std::string_view kRealClaudeId =
    "aaaaaaaa-1111-4000-8000-000000000001";
constexpr std::string_view kRealCodexPath = "/ws/real-codex";
constexpr std::string_view kRealClaudePath = "/ws/real-claude";

biv::manifest::AgentSessionEntry real_codex_entry() {
  auto value = entry("codex");
  value.agent_version_at_pack = "0.142.5";
  value.original_path = kRealCodexPath;
  value.normalized_path_key = kRealCodexPath;
  value.normalization_scheme = "codex-cwd/v1";
  value.provenance = {.store_root = "/source/.codex",
                      .locator = "sessions_root",
                      .discovery_tier = "env"};
  value.original_session_ids.primary = kRealCodexId;
  value.artifacts = {"agents/codex/" + std::string{kRealCodexId} +
                     ".jsonl"};
  return value;
}

biv::manifest::AgentSessionEntry real_claude_entry() {
  auto value = entry("claude-code");
  value.agent_version_at_pack = "2.1.202";
  value.original_path = kRealClaudePath;
  value.normalized_path_key = kRealClaudePath;
  value.normalization_scheme = "claude-cwd/v1";
  value.provenance = {.store_root = "/source/.claude",
                      .locator = "sessions_root",
                      .discovery_tier = "env"};
  value.original_session_ids.primary = kRealClaudeId;
  value.artifacts = {"agents/claude-code/" + std::string{kRealClaudeId} +
                     ".jsonl"};
  value.children = {biv::manifest::SessionChild{
      .original_id = "agent-a01",
      .artifacts = {"agents/claude-code/" + std::string{kRealClaudeId} +
                        "/subagents/agent-a01.jsonl",
                    "agents/claude-code/" + std::string{kRealClaudeId} +
                        "/subagents/agent-a01.meta.json"}}};
  return value;
}

std::map<std::string, std::vector<std::byte>> real_agent_members() {
  const std::string codex =
      std::string{
          "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":\"session_"
          "meta\",\"payload\":{\"id\":\""} +
      std::string{kRealCodexId} + "\",\"session_id\":\"" +
      std::string{kRealCodexId} + "\",\"cwd\":\"" +
      std::string{kRealCodexPath} +
      "\",\"cli_version\":\"0.142.5\"}}\n"
      "{\"timestamp\":\"2026-07-06T01:01:00Z\",\"type\":\"turn_context\","
      "\"payload\":{\"cwd\":\"" +
      std::string{kRealCodexPath} + "\",\"workspace_roots\":[\"" +
      std::string{kRealCodexPath} + "\"]}}\n";
  const std::string claude =
      std::string{"{\"type\":\"bridge-session\",\"sessionId\":\""} +
      std::string{kRealClaudeId} +
      "\",\"bridgeSessionId\":\"bbbb-1111-4000-8000-000000000001\","
      "\"lastSequenceNum\":3}\n"
      "{\"type\":\"user\",\"cwd\":\"" + std::string{kRealClaudePath} +
      "\",\"uuid\":\"00000000-0000-4000-8000-000000000101\","
      "\"parentUuid\":\"00000000-0000-4000-8000-000000000100\","
      "\"leafUuid\":\"00000000-0000-4000-8000-000000000102\","
      "\"sourceToolAssistantUUID\":\"00000000-0000-4000-8000-000000000103\","
      "\"sessionId\":\"" +
      std::string{kRealClaudeId} + "\",\"message\":\"hello\"}\n";
  const std::string claude_subagent =
      std::string{"{\"type\":\"assistant\",\"cwd\":\""} +
      std::string{kRealClaudePath} + "\",\"sessionId\":\"" +
      std::string{kRealClaudeId} +
      "\",\"agentId\":\"agent-a01\",\"message\":\"sub\"}\n";
  const std::string claude_meta =
      "{\"agentType\":\"explore\",\"description\":\"d\"}\n";
  const auto claude_entry = real_claude_entry();
  return {{real_codex_entry().artifacts.front(), bytes(codex)},
          {claude_entry.artifacts.front(), bytes(claude)},
          {claude_entry.children.front().artifacts.at(0),
           bytes(claude_subagent)},
          {claude_entry.children.front().artifacts.at(1), bytes(claude_meta)}};
}

biv::adapters::MemberRead member_reader(
    const std::map<std::string, std::vector<std::byte>>& members) {
  return [&members](const std::string_view path)
             -> biv::expected<std::vector<std::byte>> {
    const auto found = members.find(std::string{path});
    if (found == members.end()) {
      return std::unexpected(
          biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
    }
    return found->second;
  };
}

biv::core_sessions::SessionPreview real_adapter_preview(
    const fs::path& codex_store, const fs::path& claude_store) {
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::AgentPreview codex;
  codex.agent = "codex";
  codex.parent_count = 1;
  codex.known_adapter = true;
  codex.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, true,
      {.collect = true, .install = true, .rewrite = true});
  codex.store = biv::adapters::Store{.root = codex_store, .locators = {}};
  codex.adapter = &biv::adapters::codex_adapter();
  preview.agents.push_back(std::move(codex));

  biv::core_sessions::AgentPreview claude;
  claude.agent = "claude-code";
  claude.parent_count = 1;
  claude.known_adapter = true;
  claude.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"2.1.211"}, false, false,
      {.collect = true, .install = true, .rewrite = true});
  claude.store = biv::adapters::Store{.root = claude_store, .locators = {}};
  claude.adapter = &biv::adapters::claude_code_adapter();
  preview.agents.push_back(std::move(claude));
  return preview;
}

std::vector<fs::path> regular_files(const fs::path& root) {
  std::vector<fs::path> result;
  if (!fs::exists(root)) {
    return result;
  }
  for (const auto& item : fs::recursive_directory_iterator(root)) {
    if (item.is_regular_file()) {
      result.push_back(item.path());
    }
  }
  std::ranges::sort(result);
  return result;
}

class ScopedPermissions {
 public:
  ScopedPermissions(fs::path path, const fs::perms permissions)
      : path_(std::move(path)), original_(fs::status(path_).permissions()) {
    fs::permissions(path_, permissions, fs::perm_options::replace);
  }
  ScopedPermissions(const ScopedPermissions&) = delete;
  ScopedPermissions& operator=(const ScopedPermissions&) = delete;
  ~ScopedPermissions() {
    std::error_code ignored;
    fs::permissions(path_, original_, fs::perm_options::replace, ignored);
  }

 private:
  fs::path path_;
  fs::perms original_;
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

TEST_CASE("a readable agent missing its store refuses before consent or adapter calls") {
  const auto manifest = model({entry("fixture-agent")});
  CountingAdapter adapter;
  biv::core_sessions::AgentPreview preview_agent;
  preview_agent.agent = "fixture-agent";
  preview_agent.parent_count = 1;
  preview_agent.known_adapter = true;
  preview_agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  preview_agent.adapter = &adapter;
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(preview_agent));
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back("fixture-agent", false);
  const auto workspace = make_tmp("store-missing");
  std::size_t member_reads = 0;

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [&](std::string_view) -> biv::expected<std::vector<std::byte>> {
        ++member_reads;
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 1U);
  CHECK(outcome->rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::agent_not_validated_failed);
  CHECK(outcome->rows.front().reason == std::optional<std::string>{"store-absent"});
  CHECK(adapter.install_calls == 0U);
  CHECK(member_reads == 0U);
  CHECK_FALSE(std::filesystem::exists(workspace / ".biv"));
  CHECK(biv::report::exit_for_sessions(*outcome) == 2);
  std::filesystem::remove_all(workspace);
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

TEST_CASE("run_session_leg transports packer_home to every adapter leg") {
  const auto workspace = make_tmp("packer-home-present");
  auto manifest = model({entry("fixture-agent-a"), entry("fixture-agent-b")});
  manifest.packer_home = biv::manifest::PackerHome{
      "/Users/packer", biv::manifest::PathFlavor::posix};
  CountingAdapter adapter;
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::ConsentDecision consent;
  for (const std::string agent_name : {"fixture-agent-a", "fixture-agent-b"}) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = agent_name;
    agent.parent_count = 1;
    agent.known_adapter = true;
    agent.store = biv::adapters::Store{.root = workspace, .locators = {}};
    agent.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable,
        std::optional<std::string>{"9.0.0"}, false);
    agent.adapter = &adapter;
    preview.agents.push_back(std::move(agent));
    consent.per_agent.emplace_back(agent_name, true);
  }

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  const biv::manifest::PackerHome expected{
      "/Users/packer", biv::manifest::PathFlavor::posix};
  REQUIRE(adapter.install_calls == 2U);
  REQUIRE(adapter.seen_packer_homes ==
          std::vector<std::optional<biv::manifest::PackerHome>>{expected,
                                                               expected});
  std::filesystem::remove_all(workspace);
}

TEST_CASE("run_session_leg passes absent packer_home through unchanged") {
  const auto workspace = make_tmp("packer-home-absent");
  auto manifest = model({entry("fixture-agent-a"), entry("fixture-agent-b")});
  CountingAdapter adapter;
  biv::core_sessions::SessionPreview preview;
  biv::core_sessions::ConsentDecision consent;
  for (const std::string agent_name : {"fixture-agent-a", "fixture-agent-b"}) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = agent_name;
    agent.parent_count = 1;
    agent.known_adapter = true;
    agent.store = biv::adapters::Store{.root = workspace, .locators = {}};
    agent.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable,
        std::optional<std::string>{"9.0.0"}, false);
    agent.adapter = &adapter;
    preview.agents.push_back(std::move(agent));
    consent.per_agent.emplace_back(agent_name, true);
  }

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(adapter.install_calls == 2U);
  REQUIRE(adapter.seen_packer_homes ==
          std::vector<std::optional<biv::manifest::PackerHome>>{std::nullopt,
                                                               std::nullopt});
  std::filesystem::remove_all(workspace);
}

TEST_CASE("consent-no carries a staged adapter outcome successfully") {
  const auto workspace = make_tmp("staged-outcome");
  const auto manifest = model({entry("fixture-agent")});
  CountingAdapter adapter;
  adapter.install_result.sessions = {
      {.image_session_id = manifest.agent_sessions.front().original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::staged,
       .reason = std::nullopt,
       .content_rewrite = std::nullopt,
       .verify = {},
       .detail = std::nullopt},
  };
  adapter.install_result.id_map = {
      {.agent = "fixture-agent",
       .image_session_id =
           manifest.agent_sessions.front().original_session_ids.primary,
       .installed_session_id = "minted-session",
       .children = {}},
  };
  adapter.install_result.activation = {
      {.agent = "fixture-agent", .command = "fixture resume minted-session"}};
  adapter.install_result.pair_set_applied = {
      {manifest.agent_sessions.front().original_path,
       workspace.generic_string()}};
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
  consent.per_agent.emplace_back("fixture-agent", false);

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 1U);
  CHECK(adapter.install_calls == 1U);
  CHECK(adapter.install_consent == biv::adapters::Consent::no);
  REQUIRE(adapter.install_target.has_value());
  CHECK(adapter.install_target->workspace_root == workspace);
  CHECK(outcome->rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  CHECK_FALSE(outcome->rows.front().reason.has_value());
  CHECK(biv::core_sessions::kind_for_row(outcome->rows.front().row, "") ==
        biv::ErrKind::SessionsStaged);
  CHECK(biv::report::exit_for_error(biv::ErrKind::SessionsStaged) == 0);
  CHECK(biv::report::exit_for_sessions(*outcome) == 0);
  CHECK(outcome->activation.empty());
  const auto sidecar = workspace / ".biv" / "agents" / "manifest.json";
  REQUIRE(fs::exists(sidecar));
  const auto content = read_sidecar_content(sidecar);
  REQUIRE(content.id_map.size() == 1U);
  CHECK(content.id_map.front().agent == "fixture-agent");
  CHECK(content.id_map.front().image_session_id == "fixture-agent-session");
  CHECK(content.id_map.front().installed_session_id == "minted-session");
  CHECK(content.id_map.front().children.empty());
  CHECK(content.row_original_paths ==
        std::map<std::pair<std::string, std::string>, std::string>{
            {{"fixture-agent", "fixture-agent-session"}, "/tmp/source"}});
  CHECK(content.provenance_chain ==
        std::vector<std::string>{"fixture-agent-session"});
  CHECK(content.pair_set_applied ==
        std::vector<std::pair<std::string, std::string>>{
            {"/tmp/source", workspace.generic_string()}});
  std::filesystem::remove_all(workspace);
}

TEST_CASE("one sidecar aggregates two successful staged agents") {
  const auto root = make_tmp("cross-agent-staging-success");
  const auto workspace = root / "workspace";
  const auto first_store = root / "first-store";
  const auto second_store = root / "second-store";
  fs::create_directories(workspace);
  fs::create_directories(first_store);
  fs::create_directories(second_store);
  auto first_entry = entry("agent-a");
  first_entry.original_path = "/mnt/c/Users/Me/AgentA";
  first_entry.normalized_path_key = first_entry.original_path;
  first_entry.path_flavor = biv::manifest::PathFlavor::wsl;
  auto second_entry = entry("agent-b");
  second_entry.original_path = "/tmp/agent-b-source";
  second_entry.normalized_path_key = second_entry.original_path;
  const auto manifest = model({first_entry, second_entry});
  const auto first_pairs = biv::adapters::rewrite::derive_pair_set(
      first_entry.original_path, first_entry.path_flavor,
      workspace.generic_string(), biv::manifest::PathFlavor::posix);
  const auto second_pairs = biv::adapters::rewrite::derive_pair_set(
      second_entry.original_path, second_entry.path_flavor,
      workspace.generic_string(), biv::manifest::PathFlavor::posix);

  CountingAdapter first;
  configure_staged(first, first_entry, "agent-a", "minted-agent-a",
                   first_pairs);
  CountingAdapter second;
  configure_staged(second, second_entry, "agent-b", "minted-agent-b",
                   second_pairs);
  biv::core_sessions::SessionPreview preview;
  append_readable_agent(preview, "agent-a", first_store, first);
  append_readable_agent(preview, "agent-b", second_store, second);
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"agent-a", false}, {"agent-b", false}};

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 2U);
  CHECK(outcome->rows.at(0).agent == "agent-a");
  CHECK(outcome->rows.at(0).row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  CHECK(outcome->rows.at(1).agent == "agent-b");
  CHECK(outcome->rows.at(1).row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  CHECK(biv::report::exit_for_sessions(*outcome) == 0);
  CHECK(first.install_calls == 1U);
  CHECK(second.install_calls == 1U);
  CHECK(outcome->activation.empty());

  std::size_t sidecar_count = 0;
  for (const auto& item : fs::recursive_directory_iterator{workspace}) {
    if (item.is_regular_file() && item.path().filename() == "manifest.json") {
      ++sidecar_count;
    }
  }
  CHECK(sidecar_count == 1U);
  const auto content =
      read_sidecar_content(workspace / ".biv" / "agents" / "manifest.json");
  REQUIRE(content.id_map.size() == 2U);
  CHECK(content.id_map.at(0).agent == "agent-a");
  CHECK(content.id_map.at(0).image_session_id == "agent-a-session");
  CHECK(content.id_map.at(0).installed_session_id == "minted-agent-a");
  CHECK(content.id_map.at(0).children.empty());
  CHECK(content.id_map.at(1).agent == "agent-b");
  CHECK(content.id_map.at(1).image_session_id == "agent-b-session");
  CHECK(content.id_map.at(1).installed_session_id == "minted-agent-b");
  CHECK(content.id_map.at(1).children.empty());
  CHECK(content.row_original_paths ==
        std::map<std::pair<std::string, std::string>, std::string>{
            {{"agent-a", "agent-a-session"},
             first_entry.original_path},
            {{"agent-b", "agent-b-session"},
             second_entry.original_path}});
  CHECK(content.provenance_chain ==
        std::vector<std::string>{"agent-a-session", "agent-b-session"});
  auto expected_pairs = first_pairs;
  expected_pairs.insert(expected_pairs.end(), second_pairs.begin(),
                        second_pairs.end());
  std::ranges::sort(expected_pairs);
  CHECK(content.pair_set_applied == expected_pairs);
  fs::remove_all(root);
}

TEST_CASE(
    "FX-A11 producer emits one canonical original_path per staged row") {
  const auto root = make_tmp("a11-producer-canonical-per-row");
  const auto workspace = root / "workspace";
  const auto codex_store = root / "codex-store";
  const auto claude_store = root / "claude-store";
  fs::create_directories(workspace);
  fs::create_directories(codex_store);
  fs::create_directories(claude_store);

  auto codex_entry = entry("codex");
  codex_entry.original_path = "C:\\Users/Me/Shared";
  codex_entry.normalized_path_key = codex_entry.original_path;
  codex_entry.path_flavor = biv::manifest::PathFlavor::windows;
  auto claude_entry = entry("claude-code");
  claude_entry.original_path = codex_entry.original_path;
  claude_entry.normalized_path_key = claude_entry.original_path;
  claude_entry.path_flavor = biv::manifest::PathFlavor::windows;
  const auto manifest = model({codex_entry, claude_entry});

  CountingAdapter codex;
  configure_staged(
      codex, codex_entry, "codex", "minted-codex",
      biv::adapters::rewrite::derive_pair_set(
          codex_entry.original_path, codex_entry.path_flavor,
          workspace.generic_string(), biv::manifest::PathFlavor::posix));
  CountingAdapter claude;
  configure_staged(
      claude, claude_entry, "claude-code", "minted-claude",
      biv::adapters::rewrite::derive_pair_set(
          claude_entry.original_path, claude_entry.path_flavor,
          workspace.generic_string(), biv::manifest::PathFlavor::posix));
  biv::core_sessions::SessionPreview preview;
  append_readable_agent(preview, "codex", codex_store, codex);
  append_readable_agent(preview, "claude-code", claude_store, claude);
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"codex", false}, {"claude-code", false}};

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 2U);
  const auto sidecar = read_sidecar_content(
      workspace / ".biv" / "agents" / "manifest.json");
  CHECK(sidecar.row_original_paths ==
        std::map<std::pair<std::string, std::string>, std::string>{
            {{"claude-code", "claude-code-session"},
             "C:\\Users\\Me\\Shared"},
            {{"codex", "codex-session"}, "C:\\Users\\Me\\Shared"}});
  CHECK(sidecar.row_original_paths.size() == sidecar.id_map.size());
  CHECK(sidecar.pair_set_applied.size() == 3U);
  fs::remove_all(root);
}

TEST_CASE("a foreign staging carrier is refused before adapter writes") {
  for (const auto& foreign_relative :
       {fs::path{"manifest.json"}, fs::path{"foreign/payload.bin"}}) {
    DYNAMIC_SECTION(foreign_relative.generic_string()) {
      const auto root = make_tmp("foreign-staging-carrier-" +
                                 foreign_relative.filename().string());
      const auto workspace = root / "workspace";
      const auto store = root / "store";
      const auto carrier = workspace / ".biv" / "agents";
      const auto foreign_path = carrier / foreign_relative;
      fs::create_directories(foreign_path.parent_path());
      fs::create_directories(store);
      {
        std::ofstream foreign{foreign_path, std::ios::binary};
        foreign << "unowned carrier bytes\n";
      }
      const auto manifest = model({entry("fixture-agent")});
      CountingAdapter adapter;
      configure_staged(
          adapter, manifest.agent_sessions.front(), "fixture-agent",
          "minted-session",
          {{manifest.agent_sessions.front().original_path,
            workspace.generic_string()}});
      biv::core_sessions::SessionPreview preview;
      append_readable_agent(preview, "fixture-agent", store, adapter);
      biv::core_sessions::ConsentDecision consent;
      consent.per_agent = {{"fixture-agent", false}};

      const auto outcome = biv::core_sessions::run_session_leg(
          preview, consent, manifest, workspace,
          [](std::string_view) -> biv::expected<std::vector<std::byte>> {
            return std::vector<std::byte>{};
          });

      REQUIRE(outcome);
      REQUIRE(outcome->rows.size() == 1U);
      CHECK(outcome->rows.front().row ==
            biv::core_sessions::SessionRowReport::Row::containment_refused);
      CHECK(outcome->rows.front().reason ==
            std::optional<std::string>{"foreign_staging_carrier"});
      CHECK_FALSE(outcome->rows.front().detail.has_value());
      CHECK(adapter.install_calls == 0U);
      CHECK(outcome->id_map.empty());
      CHECK(outcome->activation.empty());
      CHECK(outcome->caveats.empty());
      CHECK(regular_files(carrier) == std::vector<fs::path>{foreign_path});
      CHECK(read_text(foreign_path) == "unowned carrier bytes\n");
      fs::remove_all(root);
    }
  }
}

TEST_CASE(
    "real adapters stage consent-no bytes and one sealed sidecar with read-only host stores") {
  const auto root = make_tmp("real-adapter-consent-no-sidecar");
  const auto workspace = root / "workspace";
  const auto codex_store = root / "codex-store";
  const auto claude_store = root / "claude-store";
  fs::create_directories(workspace);
  fs::create_directories(codex_store);
  fs::create_directories(claude_store);
  {
    std::ofstream marker{codex_store / "sentinel.txt", std::ios::binary};
    marker << "codex host store\n";
  }
  {
    std::ofstream marker{claude_store / "sentinel.txt", std::ios::binary};
    marker << "claude host store\n";
  }
  const auto codex_before = read_text(codex_store / "sentinel.txt");
  const auto claude_before = read_text(claude_store / "sentinel.txt");
  const auto codex_files_before = regular_files(codex_store);
  const auto claude_files_before = regular_files(claude_store);
  const auto manifest = model({real_codex_entry(), real_claude_entry()});
  const auto members = real_agent_members();
  const auto preview = real_adapter_preview(codex_store, claude_store);
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"codex", false}, {"claude-code", false}};

  {
    ScopedPermissions codex_read_only{
        codex_store, fs::perms::owner_read | fs::perms::owner_exec};
    ScopedPermissions claude_read_only{
        claude_store, fs::perms::owner_read | fs::perms::owner_exec};
    const auto outcome = biv::core_sessions::run_session_leg(
        preview, consent, manifest, workspace, member_reader(members));

    REQUIRE(outcome);
    REQUIRE(outcome->rows.size() == 2U);
    CHECK(outcome->rows.at(0).agent == "codex");
    CHECK(outcome->rows.at(1).agent == "claude-code");
    for (const auto& row : outcome->rows) {
      CHECK(row.row ==
            biv::core_sessions::SessionRowReport::Row::sessions_staged);
      CHECK_FALSE(row.reason.has_value());
      CHECK(row.installed_session_id.has_value());
    }
    CHECK(biv::report::exit_for_sessions(*outcome) == 0);
    CHECK(outcome->activation.empty());
    REQUIRE(outcome->id_map.size() == 2U);

    const auto codex_map = std::ranges::find(
        outcome->id_map, "codex", &biv::adapters::IdMapEntry::agent);
    const auto claude_map = std::ranges::find(
        outcome->id_map, "claude-code", &biv::adapters::IdMapEntry::agent);
    REQUIRE(codex_map != outcome->id_map.end());
    REQUIRE(claude_map != outcome->id_map.end());
    CHECK(codex_map->image_session_id == kRealCodexId);
    CHECK(claude_map->image_session_id == kRealClaudeId);
    CHECK(codex_map->installed_session_id != kRealCodexId);
    CHECK(claude_map->installed_session_id != kRealClaudeId);

    const auto agents_root = workspace / ".biv" / "agents";
    const auto files = regular_files(agents_root);
    REQUIRE(files.size() == 5U);
    CHECK(std::ranges::count(files,
                             agents_root / "manifest.json") == 1);
    const auto codex_file = std::ranges::find_if(files, [&](const auto& path) {
      return path.generic_string().find(codex_map->installed_session_id) !=
             std::string::npos;
    });
    const auto claude_file =
        std::ranges::find_if(files, [&](const auto& path) {
          return path.filename() ==
                 claude_map->installed_session_id + ".jsonl";
        });
    REQUIRE(codex_file != files.end());
    REQUIRE(claude_file != files.end());
    const auto codex_staged = read_text(*codex_file);
    const auto claude_staged = read_text(*claude_file);
    CHECK(codex_staged.find(kRealCodexId) == std::string::npos);
    CHECK(codex_staged.find(kRealCodexPath) == std::string::npos);
    CHECK(codex_staged.find(codex_map->installed_session_id) !=
          std::string::npos);
    CHECK(codex_staged.find(workspace.generic_string()) != std::string::npos);
    CHECK(claude_staged.find(kRealClaudeId) == std::string::npos);
    CHECK(claude_staged.find(kRealClaudePath) == std::string::npos);
    CHECK(claude_staged.find(claude_map->installed_session_id) !=
          std::string::npos);
    CHECK(claude_staged.find(workspace.generic_string()) != std::string::npos);

    const auto sidecar = read_sidecar_content(agents_root / "manifest.json");
    REQUIRE(sidecar.id_map.size() == 2U);  // sealed member: id_map
    CHECK(sidecar.id_map.at(0).agent == "claude-code");
    CHECK(sidecar.id_map.at(0).image_session_id == kRealClaudeId);
    CHECK(sidecar.id_map.at(0).installed_session_id ==
          claude_map->installed_session_id);
    CHECK(sidecar.id_map.at(1).agent == "codex");
    CHECK(sidecar.id_map.at(1).image_session_id == kRealCodexId);
    CHECK(sidecar.id_map.at(1).installed_session_id ==
          codex_map->installed_session_id);
    CHECK(sidecar.provenance_chain ==
          std::vector<std::string>{std::string{kRealCodexId},
                                   std::string{kRealClaudeId},
                                   "agent-a01"});  // sealed member
    CHECK(sidecar.pair_set_applied ==
          std::vector<std::pair<std::string, std::string>>{
              {std::string{kRealClaudePath}, workspace.generic_string()},
              {std::string{kRealCodexPath},
               workspace.generic_string()}});  // sealed member
    CHECK(read_text(codex_store / "sentinel.txt") == codex_before);
    CHECK(read_text(claude_store / "sentinel.txt") == claude_before);
    CHECK(regular_files(codex_store) == codex_files_before);
    CHECK(regular_files(claude_store) == claude_files_before);
  }
  fs::remove_all(root);
}

TEST_CASE(
    "publication-race containment preserves detail and discloses every staged file") {
  const auto root = make_tmp("real-adapter-sidecar-failure");
  const auto workspace = root / "workspace";
  const auto codex_store = root / "codex-store";
  const auto claude_store = root / "claude-store";
  const auto detail_store = root / "detail-store";
  const auto collision_store = root / "collision-store";
  const auto sidecar = workspace / ".biv" / "agents" / "manifest.json";
  fs::create_directories(workspace);
  fs::create_directories(codex_store);
  fs::create_directories(claude_store);
  fs::create_directories(detail_store);
  fs::create_directories(collision_store);
  {
    std::ofstream marker{codex_store / "sentinel.txt", std::ios::binary};
    marker << "codex host store\n";
  }
  {
    std::ofstream marker{claude_store / "sentinel.txt", std::ios::binary};
    marker << "claude host store\n";
  }
  const auto codex_before = read_text(codex_store / "sentinel.txt");
  const auto claude_before = read_text(claude_store / "sentinel.txt");
  const auto codex_files_before = regular_files(codex_store);
  const auto claude_files_before = regular_files(claude_store);
  const auto detail_entry = entry("detail-agent");
  const auto collision_entry = entry("collision-agent");
  const auto manifest = model({real_codex_entry(), real_claude_entry(),
                               detail_entry, collision_entry});
  auto members = real_agent_members();
  auto preview = real_adapter_preview(codex_store, claude_store);
  CountingAdapter detail;
  configure_staged(
      detail, detail_entry, "detail-agent", "minted-detail-session",
      {{detail_entry.original_path, workspace.generic_string()}});
  detail.install_result.sessions.front().detail = "non_utf8_skipped=1";
  detail.install_hook = [&](const biv::adapters::InstallTarget&) {
    const auto path = workspace / ".biv" / "agents" / "detail-agent" /
                      "minted-detail-session.jsonl";
    fs::create_directories(path.parent_path());
    std::ofstream staged{path, std::ios::binary};
    staged << "staged detail bytes\n";
  };
  append_readable_agent(preview, "detail-agent", detail_store, detail);
  CountingAdapter collision;
  collision.install_hook = [&](const biv::adapters::InstallTarget&) {
    fs::create_directories(sidecar.parent_path());
    std::ofstream existing{sidecar, std::ios::binary};
    existing << "unowned sidecar\n";
  };
  collision.install_error = biv::BivError{
      biv::ErrKind::RestoreWriteFailed, {}, "error", EIO};
  append_readable_agent(preview, "collision-agent", collision_store,
                        collision);
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"codex", false},
                       {"claude-code", false},
                       {"detail-agent", false},
                       {"collision-agent", false}};

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace, member_reader(members));

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 4U);
  CHECK(outcome->rows.at(0).agent == "codex");
  CHECK(outcome->rows.at(0).row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(outcome->rows.at(0).reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK_FALSE(outcome->rows.at(0).detail.has_value());
  CHECK(outcome->rows.at(1).agent == "claude-code");
  CHECK(outcome->rows.at(1).row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(outcome->rows.at(1).reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK_FALSE(outcome->rows.at(1).detail.has_value());
  CHECK(outcome->rows.at(2).agent == "detail-agent");
  CHECK(outcome->rows.at(2).row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(outcome->rows.at(2).reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(outcome->rows.at(2).detail ==
        std::optional<std::string>{"non_utf8_skipped=1"});
  CHECK(outcome->rows.at(3).agent == "collision-agent");
  CHECK(outcome->rows.at(3).row ==
        biv::core_sessions::SessionRowReport::Row::session_install_failed);
  CHECK(outcome->rows.at(3).reason == std::optional<std::string>{"error"});
  CHECK(outcome->rows.at(3).detail == std::optional<std::string>{"EIO"});
  CHECK(std::ranges::all_of(
      outcome->rows,
      &biv::core_sessions::SessionRowReport::activation_suppressed));
  CHECK(biv::report::exit_for_sessions(*outcome) == 2);
  CHECK(outcome->activation.empty());
  REQUIRE(outcome->id_map.size() == 3U);
  CHECK(detail.install_calls == 1U);
  CHECK(collision.install_calls == 1U);
  CHECK(read_text(sidecar) == "unowned sidecar\n");

  auto staged_files = regular_files(workspace / ".biv" / "agents");
  std::erase(staged_files, sidecar);
  REQUIRE(staged_files.size() == 5U);
  REQUIRE(static_cast<std::size_t>(std::ranges::count(
              outcome->caveats, "staged-byte-path",
              &biv::core_sessions::AgentCaveat::kind)) ==
          staged_files.size());
  for (const auto& staged : staged_files) {
    const auto relative =
        staged.lexically_relative(workspace).generic_string();
    const auto caveat = std::ranges::find_if(
        outcome->caveats, [&](const auto& item) {
          return item.kind == "staged-byte-path" && item.note == relative;
        });
    CHECK(caveat != outcome->caveats.end());
  }
  CHECK(read_text(codex_store / "sentinel.txt") == codex_before);
  CHECK(read_text(claude_store / "sentinel.txt") == claude_before);
  CHECK(regular_files(codex_store) == codex_files_before);
  CHECK(regular_files(claude_store) == claude_files_before);
  fs::remove_all(root);
}

TEST_CASE(
    "real adapters report consent-no failure without artifacts in an unwritable workspace") {
  const auto root = make_tmp("real-adapter-consent-no-unwritable");
  const auto workspace = root / "workspace";
  const auto codex_store = root / "codex-store";
  const auto claude_store = root / "claude-store";
  fs::create_directories(workspace);
  fs::create_directories(codex_store);
  fs::create_directories(claude_store);
  {
    std::ofstream marker{codex_store / "sentinel.txt", std::ios::binary};
    marker << "codex host store\n";
  }
  {
    std::ofstream marker{claude_store / "sentinel.txt", std::ios::binary};
    marker << "claude host store\n";
  }
  const auto codex_before = read_text(codex_store / "sentinel.txt");
  const auto claude_before = read_text(claude_store / "sentinel.txt");
  const auto codex_files_before = regular_files(codex_store);
  const auto claude_files_before = regular_files(claude_store);
  const auto manifest = model({real_codex_entry(), real_claude_entry()});
  const auto members = real_agent_members();
  const auto preview = real_adapter_preview(codex_store, claude_store);
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"codex", false}, {"claude-code", false}};

  {
    ScopedPermissions workspace_read_only{
        workspace, fs::perms::owner_read | fs::perms::owner_exec};
    const auto outcome = biv::core_sessions::run_session_leg(
        preview, consent, manifest, workspace, member_reader(members));

    REQUIRE(outcome);
    REQUIRE(outcome->rows.size() == 2U);
    CHECK(outcome->rows.at(0).agent == "codex");
    CHECK(outcome->rows.at(1).agent == "claude-code");
    for (const auto& row : outcome->rows) {
      CHECK(row.row == biv::core_sessions::SessionRowReport::Row::
                           session_install_failed);
      CHECK(row.reason == std::optional<std::string>{"error"});
      CHECK(row.detail == std::optional<std::string>{"EACCES"});
    }
    CHECK(biv::report::exit_for_sessions(*outcome) == 2);
    CHECK(outcome->activation.empty());
    CHECK(outcome->id_map.empty());
    CHECK(regular_files(workspace).empty());
    CHECK_FALSE(fs::exists(workspace / ".biv" / "agents" / "manifest.json"));
    CHECK(read_text(codex_store / "sentinel.txt") == codex_before);
    CHECK(read_text(claude_store / "sentinel.txt") == claude_before);
    CHECK(regular_files(codex_store) == codex_files_before);
    CHECK(regular_files(claude_store) == claude_files_before);
  }
  fs::remove_all(root);
}

TEST_CASE(
    "a read-only host store permits consent-no staging but blocks consent-yes") {
  const auto root = make_tmp("read-only-store-cross-product");
  const auto workspace = root / "workspace";
  const auto store = root / "store";
  fs::create_directories(workspace);
  fs::create_directories(store);
  const auto manifest = model({entry("fixture-agent")});
  CountingAdapter adapter;
  adapter.install_result.sessions = {
      {.image_session_id =
           manifest.agent_sessions.front().original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::staged,
       .reason = std::nullopt,
       .content_rewrite = "pair",
       .verify = {.origin_path_hits = 0,
                  .origin_id_hits = 0,
                  .artifacts_checked = 1},
       .detail = std::nullopt},
  };
  adapter.install_result.id_map = {
      {.agent = "fixture-agent",
       .image_session_id =
           manifest.agent_sessions.front().original_session_ids.primary,
       .installed_session_id = "minted-session",
       .children = {}},
  };
  adapter.install_result.pair_set_applied = {
      {manifest.agent_sessions.front().original_path,
       workspace.generic_string()}};
  biv::core_sessions::AgentPreview agent;
  agent.agent = "fixture-agent";
  agent.parent_count = 1;
  agent.known_adapter = true;
  agent.store = biv::adapters::Store{.root = store, .locators = {}};
  agent.caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"9.0.0"}, false);
  agent.adapter = &adapter;
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(std::move(agent));
  fs::permissions(store, fs::perms::owner_read | fs::perms::owner_exec,
                  fs::perm_options::replace);
  biv::core_sessions::ConsentDecision denied;
  denied.per_agent.emplace_back("fixture-agent", false);

  const auto staged = biv::core_sessions::run_session_leg(
      preview, denied, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(staged);
  REQUIRE(staged->rows.size() == 1U);
  CHECK(staged->rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  CHECK(adapter.install_calls == 1U);
  CHECK(adapter.install_consent == biv::adapters::Consent::no);
  CHECK(fs::exists(workspace / ".biv" / "agents" / "manifest.json"));
  biv::core_sessions::ConsentDecision allowed;
  allowed.per_agent.emplace_back("fixture-agent", true);

  const auto refused = biv::core_sessions::run_session_leg(
      preview, allowed, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  fs::permissions(store, fs::perms::owner_all, fs::perm_options::replace);
  REQUIRE(refused);
  REQUIRE(refused->rows.size() == 1U);
  CHECK(refused->rows.front().row ==
        biv::core_sessions::SessionRowReport::Row::session_install_failed);
  CHECK(refused->rows.front().reason ==
        std::optional<std::string>{"store_locked"});
  CHECK(biv::report::exit_for_sessions(*refused) == 2);
  CHECK(adapter.install_calls == 1U);
  fs::remove_all(root);
}

TEST_CASE(
    "one adapter failure leaves its staged sibling in the aggregate sidecar") {
  const auto root = make_tmp("per-agent-staging-isolation");
  const auto workspace = root / "workspace";
  const auto first_store = root / "first-store";
  const auto second_store = root / "second-store";
  fs::create_directories(workspace);
  fs::create_directories(first_store);
  fs::create_directories(second_store);
  auto first_entry = entry("agent-a");
  auto second_entry = entry("agent-b");
  const auto manifest = model({first_entry, second_entry});
  CountingAdapter first;
  first.install_result.sessions = {
      {.image_session_id = first_entry.original_session_ids.primary,
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::staged,
       .reason = std::nullopt,
       .content_rewrite = "pair",
       .verify = {.origin_path_hits = 0,
                  .origin_id_hits = 0,
                  .artifacts_checked = 1},
       .detail = std::nullopt},
  };
  first.install_result.id_map = {
      {.agent = "agent-a",
       .image_session_id = first_entry.original_session_ids.primary,
       .installed_session_id = "minted-agent-a",
       .children = {}},
  };
  first.install_result.pair_set_applied = {
      {first_entry.original_path, workspace.generic_string()}};
  CountingAdapter second;
  second.install_error = biv::BivError{biv::ErrKind::ArchiveWriteFailed,
                                       ".biv/agents/agent-b", "", ENOSPC};
  biv::core_sessions::SessionPreview preview;
  for (const auto& [agent_name, store, adapter] :
       std::vector<std::tuple<std::string, fs::path, CountingAdapter*>>{
           {"agent-a", first_store, &first},
           {"agent-b", second_store, &second}}) {
    biv::core_sessions::AgentPreview agent;
    agent.agent = agent_name;
    agent.parent_count = 1;
    agent.known_adapter = true;
    agent.store = biv::adapters::Store{.root = store, .locators = {}};
    agent.caps = biv::adapters::Capabilities::from_probe(
        biv::adapters::Capabilities::Verdict::readable,
        std::optional<std::string>{"9.0.0"}, false);
    agent.adapter = adapter;
    preview.agents.push_back(std::move(agent));
  }
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent = {{"agent-a", false}, {"agent-b", false}};

  const auto outcome = biv::core_sessions::run_session_leg(
      preview, consent, manifest, workspace,
      [](std::string_view) -> biv::expected<std::vector<std::byte>> {
        return std::vector<std::byte>{};
      });

  REQUIRE(outcome);
  REQUIRE(outcome->rows.size() == 2U);
  CHECK(outcome->rows.at(0).row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  CHECK(outcome->rows.at(1).row ==
        biv::core_sessions::SessionRowReport::Row::session_install_failed);
  CHECK(outcome->rows.at(1).detail == std::optional<std::string>{"ENOSPC"});
  REQUIRE(outcome->id_map.size() == 1U);
  CHECK(outcome->id_map.front().agent == "agent-a");
  CHECK(first.install_calls == 1U);
  CHECK(second.install_calls == 1U);
  const auto sidecar =
      read_text(workspace / ".biv" / "agents" / "manifest.json");
  CHECK(sidecar.find("agent-a") != std::string::npos);
  CHECK(sidecar.find("minted-agent-a") != std::string::npos);
  CHECK(sidecar.find("agent-b") == std::string::npos);
  CHECK(biv::report::exit_for_sessions(*outcome) == 2);
  fs::remove_all(root);
}

TEST_CASE("an adapter row missing from the manifest is reported live at pack") {
  const auto workspace = make_tmp("lookup-miss-live");
  const auto manifest = model({entry("fixture-agent")});
  CountingAdapter adapter;
  adapter.install_result.sessions = {
      {.image_session_id = "not-in-manifest",
       .outcome = biv::adapters::InstallSessionOutcome::Outcome::failed,
       .reason = "collision_refused",
       .content_rewrite = std::nullopt,
       .verify = {},
       .detail = "collision_refused"},
  };
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
  REQUIRE(outcome->rows.size() == 1U);
  CHECK(outcome->rows.front().live_at_pack);
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
