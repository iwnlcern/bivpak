#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "adapters/claude_code/claude_code.hpp"
#include "adapters/rewrite_common.hpp"

namespace {

namespace fs = std::filesystem;

constexpr std::string_view kOriginalSession = "aaaaaaaa-1111-4000-8000-000000000001";
constexpr std::string_view kBridgeSession = "bbbb-1111-4000-8000-000000000001";

fs::path make_tmp(std::string_view name) {
  auto base = fs::temp_directory_path() /
              ("biv-claude-install-" + std::string{name} + "-" + std::to_string(::getpid()));
  fs::remove_all(base);
  fs::create_directories(base);
  return base;
}

std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> out;
  out.reserve(text.size());
  for (const char value : text) {
    out.push_back(static_cast<std::byte>(value));
  }
  return out;
}

std::string text(std::span<const std::byte> data) {
  std::string out;
  out.reserve(data.size());
  for (const std::byte value : data) {
    out.push_back(static_cast<char>(value));
  }
  return out;
}

std::string read_text(const fs::path& path) {
  std::ifstream input{path, std::ios::binary};
  REQUIRE(input);
  return {std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
}

std::vector<fs::path> regular_files(const fs::path& root) {
  std::vector<fs::path> out;
  if (!fs::exists(root)) {
    return out;
  }
  for (const auto& entry : fs::recursive_directory_iterator(root)) {
    if (entry.is_regular_file()) {
      out.push_back(entry.path());
    }
  }
  std::ranges::sort(out);
  return out;
}

std::string claude_project_key(const fs::path& path) {
  std::string key = path.generic_string();
  for (char& value : key) {
    const bool alnum = (value >= '0' && value <= '9') || (value >= 'A' && value <= 'Z') ||
                       (value >= 'a' && value <= 'z');
    if (!alnum) {
      value = '-';
    }
  }
  return key;
}

std::string main_artifact(std::string_view session_id = kOriginalSession) {
  return "agents/claude-code/" + std::string{session_id} + ".jsonl";
}

std::string subagent_artifact(std::string_view session_id = kOriginalSession) {
  return "agents/claude-code/" + std::string{session_id} + "/subagents/agent-a01.jsonl";
}

std::string meta_artifact(std::string_view session_id = kOriginalSession) {
  return "agents/claude-code/" + std::string{session_id} + "/subagents/agent-a01.meta.json";
}

biv::manifest::AgentSessionEntry claude_entry(std::string original_path = "/ws/proj") {
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "claude-code";
  entry.agent_version_at_pack = "2.1.202";
  entry.relpath_key = ".";
  entry.original_path = std::move(original_path);
  entry.normalized_path_key = entry.original_path;
  entry.normalization_scheme = "claude-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::posix;
  entry.provenance = {.store_root = "/source/.claude", .locator = "projects", .discovery_tier = "env"};
  entry.original_session_ids.primary = std::string{kOriginalSession};
  entry.children = {biv::manifest::SessionChild{
      .original_id = "agent-a01", .artifacts = {subagent_artifact(), meta_artifact()}}};
  entry.artifacts = {main_artifact()};
  entry.live_at_pack = false;
  entry.imported_at = "2026-07-07T00:00:00Z";
  entry.entry_schema = 1;
  return entry;
}

std::map<std::string, std::vector<std::byte>> claude_members() {
  std::map<std::string, std::vector<std::byte>> members;
  const std::string main = std::string{
                               "{\"type\":\"bridge-session\",\"sessionId\":\""} +
                           std::string{kOriginalSession} + "\",\"bridgeSessionId\":\"" +
                           std::string{kBridgeSession} + "\",\"lastSequenceNum\":3}\n" +
                           "{\"type\":\"user\",\"cwd\":\"/ws/proj\",\"uuid\":\"u1\",\"parentUuid\":\"p1\","
                           "\"sessionId\":\"" +
                           std::string{kOriginalSession} +
                           "\",\"message\":\"tool saw /ws/proj and /other/machine/path\"}\n";
  const std::string subagent = std::string{"{\"type\":\"assistant\",\"cwd\":\"/ws/proj\",\"sessionId\":\""} +
                               std::string{kOriginalSession} +
                               "\",\"agentId\":\"agent-a01\",\"message\":\"sub\"}\n";
  const std::string meta = "{\"agentType\":\"explore\",\"description\":\"d\",\"toolUseId\":\"tu1\",\"spawnDepth\":1}\n";
  members.emplace(main_artifact(), bytes(main));
  members.emplace(subagent_artifact(), bytes(subagent));
  members.emplace(meta_artifact(), bytes(meta));
  return members;
}

biv::adapters::InstallTarget target_for(fs::path workspace,
                                        fs::path store,
                                        std::map<std::string, std::vector<std::byte>>& members) {
  return biv::adapters::InstallTarget{
      .workspace_root = std::move(workspace),
      .target_store = biv::adapters::Store{.root = std::move(store),
                                           .locators = {},
                                           .tier = biv::adapters::DiscoveryTier::env,
                                           .archived = false},
      .member_read = [&](const std::string_view path) -> biv::expected<std::vector<std::byte>> {
        const auto found = members.find(std::string{path});
        if (found == members.end()) {
          return std::unexpected(biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
        }
        return found->second;
      }};
}

}  // namespace

TEST_CASE("rewrite common derives pair sets and rewrites JSONL strings") {
  const auto pairs = biv::adapters::rewrite::derive_pair_set("/mnt/c/Users/Me/Proj",
                                                            biv::manifest::PathFlavor::wsl,
                                                            "/home/me/proj",
                                                            biv::manifest::PathFlavor::posix);
  CHECK(std::ranges::find(pairs, std::pair<std::string, std::string>{"/mnt/c/Users/Me/Proj", "/home/me/proj"}) !=
        pairs.end());
  CHECK(std::ranges::find(pairs, std::pair<std::string, std::string>{"/mnt/c/users/me/proj", "/home/me/proj"}) !=
        pairs.end());
  CHECK(std::ranges::find(pairs, std::pair<std::string, std::string>{"C:\\Users\\Me\\Proj", "/home/me/proj"}) !=
        pairs.end());
  CHECK(std::ranges::find(pairs, std::pair<std::string, std::string>{"C:/Users/Me/Proj", "/home/me/proj"}) !=
        pairs.end());
  const auto mount_pairs = biv::adapters::rewrite::derive_pair_set("C:\\Users\\Me\\Proj",
                                                                   biv::manifest::PathFlavor::windows,
                                                                   "/mnt/d/Work/New",
                                                                   biv::manifest::PathFlavor::wsl);
  CHECK(std::ranges::find(mount_pairs,
                          std::pair<std::string, std::string>{"C:\\Users\\Me\\Proj", "D:\\Work\\New"}) !=
        mount_pairs.end());
  CHECK(std::ranges::find(mount_pairs,
                          std::pair<std::string, std::string>{"C:/Users/Me/Proj", "D:/Work/New"}) !=
        mount_pairs.end());
  CHECK(std::ranges::find(mount_pairs,
                          std::pair<std::string, std::string>{"/mnt/c/Users/Me/Proj", "/mnt/d/Work/New"}) !=
        mount_pairs.end());

  const std::vector<std::pair<std::string, std::string>> ids{{std::string{kOriginalSession}, "new-session"},
                                                             {"u1", "u2"},
                                                             {"p1", "p2"}};
  const std::string line = std::string{
                               "{\"cwd\":\"/mnt/c/Users/Me/Proj\",\"sessionId\":\""} +
                           std::string{kOriginalSession} +
                           "\",\"uuid\":\"u1\",\"parentUuid\":\"p1\","
                           "\"message\":\"/mnt/c/Users/Me/Proj and /other/machine/path\"}";

  const auto rewritten = biv::adapters::rewrite::rewrite_jsonl_line(line,
                                                                    biv::adapters::rewrite::PathPairsView{pairs},
                                                                    biv::adapters::rewrite::IdPairsView{ids});

  CHECK_FALSE(rewritten.skipped_non_utf8);
  CHECK(rewritten.line.find("/home/me/proj") != std::string::npos);
  CHECK(rewritten.line.find("new-session") != std::string::npos);
  CHECK(rewritten.line.find("u2") != std::string::npos);
  CHECK(rewritten.line.find("p2") != std::string::npos);
  CHECK(rewritten.line.find("/other/machine/path") != std::string::npos);
  CHECK(rewritten.line.find(kOriginalSession) == std::string::npos);

  const std::vector<std::string> origins{"/mnt/c/Users/Me/Proj",
                                         "/mnt/c/users/me/proj",
                                         "C:\\Users\\Me\\Proj",
                                         "C:/Users/Me/Proj"};
  const std::vector<std::string> origin_ids{std::string{kOriginalSession}, "u1", "p1"};
  const auto verify = biv::adapters::rewrite::verify_scan(bytes(rewritten.line),
                                                          biv::adapters::rewrite::OriginPathsView{origins},
                                                          biv::adapters::rewrite::OriginIdsView{origin_ids});
  CHECK(verify.origin_path_hits == 0);
  CHECK(verify.origin_id_hits == 0);
  CHECK(verify.artifacts_checked == 1);

  const std::string binary_line{"{\"cwd\":\"/ws/proj\"}\xFF", 20};
  const auto skipped = biv::adapters::rewrite::rewrite_jsonl_line(binary_line,
                                                                  biv::adapters::rewrite::PathPairsView{pairs},
                                                                  biv::adapters::rewrite::IdPairsView{ids});
  CHECK(skipped.skipped_non_utf8);
  CHECK(skipped.line == binary_line);
}

TEST_CASE("Claude install rewrites transcripts, preserves meta, and avoids collisions") {
  const auto root = make_tmp("install");
  const auto workspace = root / "workspace" / "proj";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  auto members = claude_members();
  auto target = target_for(workspace, store, members);
  const auto& adapter = biv::adapters::claude_code_adapter();
  std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  const auto first = adapter.install(target, biv::adapters::Consent::yes, records);

  REQUIRE(first.has_value());
  CHECK(first->mode == biv::adapters::InstallResult::Mode::host_installed);
  REQUIRE(first->sessions.size() == 1);
  CHECK(first->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(first->sessions.front().image_session_id == kOriginalSession);
  CHECK(first->sessions.front().host_version_unverified);
  CHECK(first->sessions.front().verify.origin_path_hits == 0);
  CHECK(first->sessions.front().verify.origin_id_hits == 0);
  REQUIRE(first->id_map.size() == 1);
  const std::string first_id = first->id_map.front().installed_session_id;
  CHECK(first_id != kOriginalSession);
  REQUIRE(first->activation.size() == 1);

  const auto project_dir = store / "projects" / claude_project_key(workspace);
  const auto main_path = project_dir / (first_id + ".jsonl");
  const auto subagent_path = project_dir / first_id / "subagents" / "agent-a01.jsonl";
  const auto meta_path = project_dir / first_id / "subagents" / "agent-a01.meta.json";
  REQUIRE(fs::exists(main_path));
  REQUIRE(fs::exists(subagent_path));
  REQUIRE(fs::exists(meta_path));
  const auto main_text = read_text(main_path);
  CHECK(main_text.find(first_id) != std::string::npos);
  CHECK(main_text.find(kOriginalSession) == std::string::npos);
  CHECK(main_text.find(workspace.generic_string()) != std::string::npos);
  CHECK(main_text.find("/other/machine/path") != std::string::npos);
  CHECK(main_text.find(kBridgeSession) != std::string::npos);
  const auto subagent_text = read_text(subagent_path);
  CHECK(subagent_text.find(first_id) != std::string::npos);
  CHECK(subagent_text.find("agent-a01") != std::string::npos);
  CHECK(read_text(meta_path) == text(members.at(meta_artifact())));

  const auto second = adapter.install(target, biv::adapters::Consent::yes, records);

  REQUIRE(second.has_value());
  REQUIRE(second->id_map.size() == 1);
  CHECK(second->id_map.front().installed_session_id != first_id);
  size_t main_transcripts = 0;
  for (const auto& file : regular_files(project_dir)) {
    if (file.parent_path() == project_dir && file.extension() == ".jsonl") {
      ++main_transcripts;
    }
  }
  CHECK(main_transcripts == 2);
  fs::remove_all(root);
}

TEST_CASE("Claude install refuses unpinned long project keys and unsafe artifacts") {
  const auto root = make_tmp("refusal");
  const auto store = root / "target-claude";
  auto members = claude_members();
  const auto& adapter = biv::adapters::claude_code_adapter();
  std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  auto long_target = target_for(root / std::string(280, 'a'), store, members);
  const auto long_result = adapter.install(long_target, biv::adapters::Consent::yes, records);

  REQUIRE(long_result.has_value());
  REQUIRE(long_result->sessions.size() == 1);
  CHECK(long_result->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::failed);
  REQUIRE(long_result->sessions.front().reason.has_value());
  CHECK(*long_result->sessions.front().reason == "long_path_key_unpinned");
  CHECK(long_result->activation.empty());

  auto unsafe_record = claude_entry();
  unsafe_record.artifacts = {"agents/claude-code/" + std::string{kOriginalSession} + "/../escape.jsonl"};
  members.emplace(unsafe_record.artifacts.front(), bytes("{}\n"));
  auto unsafe_target = target_for(root / "workspace", store, members);
  const auto unsafe_result = adapter.install(unsafe_target, biv::adapters::Consent::yes, {&unsafe_record, 1});

  REQUIRE(unsafe_result.has_value());
  REQUIRE(unsafe_result->sessions.size() == 1);
  CHECK(unsafe_result->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::failed);
  REQUIRE(unsafe_result->sessions.front().reason.has_value());
  CHECK(*unsafe_result->sessions.front().reason == "containment_refused");
  CHECK(unsafe_result->activation.empty());
  CHECK(regular_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Claude capabilities report absent, unvalidated, and validated hosts") {
  const auto root = make_tmp("capabilities");
  const auto& adapter = biv::adapters::claude_code_adapter();
  const biv::adapters::Env env{
      .getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; }, .home = root};
  const biv::adapters::Host host{.home = root, .env = env};

  auto caps = adapter.capabilities(host);
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::absent);
  CHECK_FALSE(caps.per_verb.collect);
  CHECK_FALSE(caps.long_path_keys_pinned);

  fs::create_directories(root / ".claude");
  caps = adapter.capabilities(host);
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::unvalidated_host);
  CHECK(caps.per_verb.collect);
  CHECK(caps.per_verb.install);
  CHECK(caps.per_verb.rewrite);

  std::ofstream marker{root / ".claude" / ".last-update-result.json"};
  marker << "{\"version\":\"2.1.202\"}\n";
  marker.close();
  caps = adapter.capabilities(host);
  CHECK(caps.agent_version == "2.1.202");
  CHECK(caps.validated_range == "2.1.x");
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::validated);
  CHECK_FALSE(caps.long_path_keys_pinned);
  fs::remove_all(root);
}

TEST_CASE("Claude bridge-session E-1 slot preserves bridgeSessionId", "[!mayfail][pending-e1]") {
  // E-1 answer relay under s3-escalate-1 -> revisit this assertion.
  const std::vector<std::pair<std::string, std::string>> ids{{std::string{kOriginalSession}, "new-session"}};
  const std::vector<std::pair<std::string, std::string>> paths;
  const std::string line = std::string{"{\"type\":\"bridge-session\",\"sessionId\":\""} +
                           std::string{kOriginalSession} + "\",\"bridgeSessionId\":\"" +
                           std::string{kBridgeSession} + "\"}";

  const auto rewritten = biv::adapters::rewrite::rewrite_jsonl_line(line,
                                                                    biv::adapters::rewrite::PathPairsView{paths},
                                                                    biv::adapters::rewrite::IdPairsView{ids});

  CHECK(rewritten.line.find("new-session") != std::string::npos);
  CHECK(rewritten.line.find(kBridgeSession) != std::string::npos);
}
