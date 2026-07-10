#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "adapters/claude_code/claude_code.hpp"
#include "adapters/rewrite_common.hpp"
#include "adapters/secure_io.hpp"

namespace {

namespace fs = std::filesystem;

constexpr std::string_view kOriginalSession = "aaaaaaaa-1111-4000-8000-000000000001";
constexpr std::string_view kBridgeSession = "bbbb-1111-4000-8000-000000000001";
constexpr std::string_view kRootUuid = "00000000-0000-4000-8000-000000000100";
constexpr std::string_view kUserUuid = "00000000-0000-4000-8000-000000000101";
constexpr std::string_view kLeafUuid = "00000000-0000-4000-8000-000000000102";
constexpr std::string_view kToolUuid = "00000000-0000-4000-8000-000000000103";
constexpr std::string_view kSubagentUuid =
    "00000000-0000-4000-8000-000000000201";

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

std::set<std::string> uuid_strings(std::string_view input) {
  std::set<std::string> out;
  for (size_t i = 0; i + 36U <= input.size(); ++i) {
    const auto candidate = input.substr(i, 36U);
    const bool hyphens = candidate.at(8) == '-' && candidate.at(13) == '-' &&
                         candidate.at(18) == '-' && candidate.at(23) == '-';
    const bool hex = std::ranges::all_of(candidate, [](const char value) {
      return (value >= '0' && value <= '9') || (value >= 'a' && value <= 'f') ||
             value == '-';
    });
    if (hyphens && hex) {
      out.emplace(candidate);
    }
  }
  return out;
}

bool disjoint(const std::set<std::string>& lhs,
              const std::set<std::string>& rhs) {
  for (const auto& value : lhs) {
    if (rhs.contains(value)) {
      return false;
    }
  }
  return true;
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

biv::manifest::AgentSessionEntry claude_entry(
    std::string original_path = "/ws/proj",
    std::string session_id = std::string{kOriginalSession}) {
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "claude-code";
  entry.agent_version_at_pack = "2.1.202";
  entry.relpath_key = ".";
  entry.original_path = std::move(original_path);
  entry.normalized_path_key = entry.original_path;
  entry.normalization_scheme = "claude-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::posix;
  entry.provenance = {.store_root = "/source/.claude",
                      .locator = "sessions_root",
                      .discovery_tier = "env"};
  entry.original_session_ids.primary = session_id;
  entry.children = {biv::manifest::SessionChild{
      .original_id = "agent-a01",
      .artifacts = {subagent_artifact(session_id), meta_artifact(session_id)}}};
  entry.artifacts = {main_artifact(session_id)};
  entry.live_at_pack = false;
  entry.imported_at = "2026-07-07T00:00:00Z";
  entry.entry_schema = 1;
  return entry;
}

std::map<std::string, std::vector<std::byte>> claude_members() {
  std::map<std::string, std::vector<std::byte>> members;
  const std::string main =
      std::string{"{\"type\":\"bridge-session\",\"sessionId\":\""} +
      std::string{kOriginalSession} + "\",\"bridgeSessionId\":\"" +
      std::string{kBridgeSession} + "\",\"lastSequenceNum\":3}\n" +
      "{\"type\":\"user\",\"cwd\":\"/ws/proj\",\"uuid\":\"" +
      std::string{kUserUuid} + "\",\"parentUuid\":\"" + std::string{kRootUuid} +
      "\",\"leafUuid\":\"" + std::string{kLeafUuid} +
      "\",\"sourceToolAssistantUUID\":\"" + std::string{kToolUuid} +
      "\",\"sessionId\":\"" + std::string{kOriginalSession} +
      "\",\"message\":\"tool saw /ws/proj and /other/machine/path\"}\n";
  const std::string subagent =
      std::string{
          "{\"type\":\"assistant\",\"cwd\":\"/ws/proj\",\"sessionId\":\""} +
      std::string{kOriginalSession} + "\",\"uuid\":\"" +
      std::string{kSubagentUuid} + "\",\"parentUuid\":\"" +
      std::string{kLeafUuid} + "\",\"sourceToolAssistantUUID\":\"" +
      std::string{kToolUuid} +
      "\",\"agentId\":\"agent-a01\",\"message\":\"sub\"}\n";
  const std::string meta =
      "{\"agentType\":\"explore\",\"description\":\"d\","
      "\"toolUseId\":\"tu1\",\"spawnDepth\":1}\n";
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

  const auto boundary_pairs = biv::adapters::rewrite::derive_pair_set(
      "/ws/proj", biv::manifest::PathFlavor::posix, "/tmp/restored",
      biv::manifest::PathFlavor::posix);
  const std::string boundary_line =
      "{\"cwd\":\"/ws/proj\",\"message\":\"/ws/proj /ws/proj/sub /ws/proj2\"}";
  const auto boundary_rewritten = biv::adapters::rewrite::rewrite_jsonl_line(
      boundary_line, biv::adapters::rewrite::PathPairsView{boundary_pairs},
      biv::adapters::rewrite::IdPairsView{});
  CHECK(boundary_rewritten.line.find(
            "/tmp/restored /tmp/restored/sub /ws/proj2") != std::string::npos);
  CHECK(boundary_rewritten.line.find("/tmp/restored2") == std::string::npos);
}

TEST_CASE("rewrite common preserves every non-target JSON value type") {
  const std::vector<std::pair<std::string, std::string>> paths{{"/old", "/new"}};
  const std::vector<std::pair<std::string, std::string>> ids{{"old-id", "new-id"}};
  const std::string line =
      "{\"path\":\"/old\",\"id\":\"old-id\",\"signed\":-7,"
      "\"unsigned\":18446744073709551615,\"decimal\":0.1,"
      "\"integral_float\":1.0,\"exponent\":1e+03,\"negative_zero\":-0.0,"
      "\"flag\":true,\"nothing\":null,\"array\":[1,2.5,false,null],"
      "\"object\":{\"value\":3.75}}";

  const auto rewritten = biv::adapters::rewrite::rewrite_jsonl_line(
      line, biv::adapters::rewrite::PathPairsView{paths},
      biv::adapters::rewrite::IdPairsView{ids});

  CHECK_FALSE(rewritten.skipped_non_utf8);
  std::string expected = line;
  expected.replace(expected.find("/old"), 4, "/new");
  expected.replace(expected.find("old-id"), 6, "new-id");
  CHECK(rewritten.line == expected);
}

TEST_CASE("rewrite common decodes only string values and verifies decoded values") {
  const std::vector<std::pair<std::string, std::string>> paths{
      {"/ws/proj", "/restored/proj"}};
  const std::string line =
      "{\"/ws/proj\":\"key-must-not-change\","
      "\"solidus\":\"\\/ws\\/proj\","
      "\"unicode\":\"\\u002fws\\u002fproj\","
      "\"decimal\":0.1,\"integral\":1.0,\"exponent\":1e+03,"
      "\"unsigned\":18446744073709551615}";

  const auto rewritten = biv::adapters::rewrite::rewrite_jsonl_line(
      line, biv::adapters::rewrite::PathPairsView{paths},
      biv::adapters::rewrite::IdPairsView{});

  CHECK(rewritten.line.find("\"/ws/proj\":\"key-must-not-change\"") !=
        std::string::npos);
  CHECK(rewritten.line.find("\"solidus\":\"/restored/proj\"") !=
        std::string::npos);
  CHECK(rewritten.line.find("\"unicode\":\"/restored/proj\"") !=
        std::string::npos);
  CHECK(rewritten.line.find("\"decimal\":0.1") != std::string::npos);
  CHECK(rewritten.line.find("\"integral\":1.0") != std::string::npos);
  CHECK(rewritten.line.find("\"exponent\":1e+03") != std::string::npos);
  CHECK(rewritten.line.find("18446744073709551615") != std::string::npos);

  const auto stale = bytes("{\"cwd\":\"\\/ws\\/\\u0070roj\"}\n");
  const std::vector<std::string> origins{"/ws/proj"};
  const auto verify = biv::adapters::rewrite::verify_scan(
      stale, biv::adapters::rewrite::OriginPathsView{origins},
      biv::adapters::rewrite::OriginIdsView{});
  CHECK(verify.origin_path_hits > 0);
}

TEST_CASE("Claude install rewrites escaped values without changing keys or numbers") {
  const auto root = make_tmp("escaped-values");
  const auto workspace = root / "workspace";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = claude_members();
  members.at(main_artifact()) = bytes(
      std::string{"{\"/ws/proj\":\"key-must-not-change\",\"type\":\"user\","
                  "\"cwd\":\"\\/ws\\/\\u0070roj\",\"sessionId\":\""} +
      std::string{kOriginalSession} +
      "\",\"decimal\":0.1,\"integral\":1.0,\"exponent\":1e+03,"
      "\"unsigned\":18446744073709551615}\n");
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  REQUIRE(result->id_map.size() == 1);
  const auto installed_id = result->id_map.front().installed_session_id;
  const auto installed = read_text(store / "projects" /
                                   claude_project_key(workspace) /
                                   (installed_id + ".jsonl"));
  CHECK(installed.find("\"/ws/proj\":\"key-must-not-change\"") !=
        std::string::npos);
  CHECK(installed.find(workspace.generic_string()) != std::string::npos);
  CHECK(installed.find("\"decimal\":0.1") != std::string::npos);
  CHECK(installed.find("\"integral\":1.0") != std::string::npos);
  CHECK(installed.find("\"exponent\":1e+03") != std::string::npos);
  CHECK(installed.find("18446744073709551615") != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("Claude install rewrites transcripts, preserves meta, and avoids collisions") {
  const auto root = make_tmp("install");
  const auto workspace = root / "workspace" / "proj";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
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
  REQUIRE(first->sessions.front().content_rewrite.has_value());
  CHECK(*first->sessions.front().content_rewrite == "pair");
  CHECK(first->sessions.front().verify.origin_path_hits == 0);
  CHECK(first->sessions.front().verify.origin_id_hits == 0);
  CHECK(first->sessions.front().verify.artifacts_checked == 3);
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
  CHECK(main_text.find(kRootUuid) == std::string::npos);
  CHECK(main_text.find(kUserUuid) == std::string::npos);
  CHECK(main_text.find(kLeafUuid) == std::string::npos);
  CHECK(main_text.find(kToolUuid) == std::string::npos);
  CHECK(main_text.find(workspace.generic_string()) != std::string::npos);
  CHECK(main_text.find("/other/machine/path") != std::string::npos);
  CHECK(main_text.find(kBridgeSession) != std::string::npos);
  const auto subagent_text = read_text(subagent_path);
  CHECK(subagent_text.find(first_id) != std::string::npos);
  CHECK(subagent_text.find(kSubagentUuid) == std::string::npos);
  CHECK(subagent_text.find(kLeafUuid) == std::string::npos);
  CHECK(subagent_text.find(kToolUuid) == std::string::npos);
  CHECK(subagent_text.find("agent-a01") != std::string::npos);
  CHECK(read_text(meta_path) == text(members.at(meta_artifact())));

  const auto second = adapter.install(target, biv::adapters::Consent::yes, records);

  REQUIRE(second.has_value());
  REQUIRE(second->id_map.size() == 1);
  CHECK(second->id_map.front().installed_session_id != first_id);
  const auto second_id = second->id_map.front().installed_session_id;
  const auto second_main = read_text(project_dir / (second_id + ".jsonl"));
  auto first_uuids = uuid_strings(main_text + subagent_text);
  auto second_uuids = uuid_strings(second_main);
  first_uuids.erase(std::string{kBridgeSession});
  second_uuids.erase(std::string{kBridgeSession});
  CHECK(disjoint(first_uuids, second_uuids));
  size_t main_transcripts = 0;
  for (const auto& file : regular_files(project_dir)) {
    if (file.parent_path() == project_dir && file.extension() == ".jsonl") {
      ++main_transcripts;
    }
  }
  CHECK(main_transcripts == 2);
  fs::remove_all(root);
}

TEST_CASE("Claude install gates host and image-entry capability verdicts") {
  const auto root = make_tmp("capability-gate");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto members = claude_members();
  const auto& adapter = biv::adapters::claude_code_adapter();
  const std::vector<biv::manifest::AgentSessionEntry> valid_records{
      claude_entry()};

  const auto absent_store = root / "absent-claude";
  auto absent_target = target_for(workspace, absent_store, members);
  const auto absent = adapter.install(
      absent_target, biv::adapters::Consent::yes, valid_records);
  REQUIRE(absent.has_value());
  REQUIRE(absent->sessions.size() == 1);
  CHECK(absent->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(absent->sessions.front().reason == std::optional<std::string>{"error"});
  CHECK(absent->sessions.front().detail ==
        std::optional<std::string>{"capability_refused"});
  CHECK_FALSE(absent->sessions.front().host_version_unverified);
  CHECK(absent->id_map.empty());
  CHECK(absent->activation.empty());
  CHECK(regular_files(absent_store).empty());

  const auto unsupported_store = root / "unsupported-claude";
  fs::create_directories(unsupported_store);
  {
    std::ofstream marker{unsupported_store / ".last-update-result.json"};
    marker << "{\"version\":\"3.0.0\"}\n";
  }
  auto unsupported_target = target_for(workspace, unsupported_store, members);
  const auto unsupported = adapter.install(
      unsupported_target, biv::adapters::Consent::yes, valid_records);
  REQUIRE(unsupported.has_value());
  REQUIRE(unsupported->sessions.size() == 1);
  CHECK(unsupported->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(unsupported->sessions.front().detail ==
        std::optional<std::string>{"capability_refused"});
  CHECK(unsupported->id_map.empty());
  CHECK(unsupported->activation.empty());
  CHECK_FALSE(fs::exists(unsupported_store / "projects"));

  const auto unknown_image_store = root / "unknown-image-claude";
  fs::create_directories(unknown_image_store);
  auto unknown_record = claude_entry();
  unknown_record.agent_version_at_pack = "unknown";
  const std::vector<biv::manifest::AgentSessionEntry> unknown_records{
      unknown_record};
  auto unknown_target = target_for(workspace, unknown_image_store, members);
  const auto unknown = adapter.install(
      unknown_target, biv::adapters::Consent::yes, unknown_records);
  REQUIRE(unknown.has_value());
  REQUIRE(unknown->sessions.size() == 1);
  CHECK(unknown->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(unknown->sessions.front().detail ==
        std::optional<std::string>{"capability_refused"});
  CHECK_FALSE(unknown->sessions.front().host_version_unverified);
  CHECK(unknown->id_map.empty());
  CHECK(unknown->activation.empty());
  CHECK(regular_files(unknown_image_store).empty());
  fs::remove_all(root);
}

TEST_CASE("Claude rewrite applies pair rewrites and reports non-UTF8 skips") {
  const auto root = make_tmp("rewrite");
  const auto workspace = root / "workspace" / "proj";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  auto members = claude_members();
  members.at(main_artifact()).push_back(static_cast<std::byte>(0xff));
  auto target = target_for(workspace, store, members);
  const auto& adapter = biv::adapters::claude_code_adapter();
  const auto entry = claude_entry();
  std::vector<biv::adapters::SessionRecord> records{
      biv::adapters::SessionRecord{
          .agent = "claude-code",
          .original_session_id = entry.original_session_ids.primary,
          .parent_id = std::nullopt,
          .child_ids = {"agent-a01"},
          .original_path = entry.original_path,
          .normalized_path_key = entry.normalized_path_key,
          .normalization_scheme = entry.normalization_scheme,
          .path_flavor = entry.path_flavor,
          .provenance = entry.provenance,
          .artifacts = {main_artifact(), subagent_artifact()},
          .artifact_sources = {},
          .agent_version_at_pack = entry.agent_version_at_pack,
          .live_at_pack = false}};

  const auto report = adapter.rewrite(records, target);

  REQUIRE(report.has_value());
  CHECK(report->per_artifact_hits.size() == 2);
  CHECK(report->verify.origin_path_hits == 0);
  CHECK(report->verify.origin_id_hits == 0);
  CHECK(report->verify.artifacts_checked == 2);
  CHECK(report->skipped_non_utf8 == 1);
  fs::remove_all(root);
}

TEST_CASE(
    "Claude install refuses unpinned long project keys and unsafe artifacts") {
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

TEST_CASE("Claude containment refusal fails every session before writing") {
  const auto root = make_tmp("multi-containment");
  const auto store = root / "target-claude";
  auto members = claude_members();
  auto good = claude_entry();
  const auto unsafe_id = std::string{"dddddddd-1111-4000-8000-000000000001"};
  auto unsafe = claude_entry("/ws/proj", unsafe_id);
  unsafe.children.clear();
  unsafe.artifacts = {"agents/claude-code/" + unsafe_id + "/../escape.jsonl"};
  const std::vector<biv::manifest::AgentSessionEntry> records{good, unsafe};
  auto target = target_for(root / "workspace", store, members);

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  CHECK(std::ranges::all_of(
      result->sessions,
      [](const biv::adapters::InstallSessionOutcome& outcome) {
        return outcome.outcome ==
                   biv::adapters::InstallSessionOutcome::Outcome::failed &&
               outcome.reason ==
                   std::optional<std::string>{"containment_refused"};
      }));
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Claude install refuses parent symlinks without visible writes") {
  const auto root = make_tmp("parent-symlink");
  const auto workspace = root / "workspace";
  const auto store = root / "target-claude";
  const auto outside = root / "outside";
  fs::create_directories(workspace);
  fs::create_directories(store);
  fs::create_directories(outside);
  fs::create_directory_symlink(outside, store / "projects");
  auto members = claude_members();
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(outside).empty());
  fs::remove_all(root);
}

TEST_CASE("secure install batch refuses a leaf symlink before any publication") {
  const auto root = make_tmp("leaf-symlink-batch");
  const auto store = root / "store";
  const auto outside = root / "outside";
  fs::create_directories(store / "sessions");
  {
    std::ofstream output{outside};
    output << "sentinel";
  }
  fs::create_symlink(outside, store / "sessions" / "blocked.jsonl");
  const auto first = bytes("first\n");
  const auto second = bytes("second\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> writes{
      {.relative_path = "sessions/good.jsonl", .bytes = first},
      {.relative_path = "sessions/blocked.jsonl", .bytes = second}};

  const auto result = biv::adapters::secure_io::write_batch_no_replace(store, writes);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().detail == "containment_refused");
  CHECK_FALSE(fs::exists(store / "sessions" / "good.jsonl"));
  CHECK(read_text(outside) == "sentinel");
  fs::remove_all(root);
}

TEST_CASE("secure install preserves unowned temporary-name collisions") {
  const auto root = make_tmp("temporary-collision");
  const auto store = root / "store";
  const auto sessions = store / "sessions";
  fs::create_directories(sessions);
  const auto first_collision =
      sessions / (".bivpak-install-" + std::to_string(::getpid()) + "-0.tmp");
  {
    std::ofstream output{first_collision, std::ios::binary};
    output << "first-host-bytes";
  }
  const auto payload = bytes("new bytes\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> first_write{
      {.relative_path = "sessions/target.jsonl", .bytes = payload}};

  const auto first_result =
      biv::adapters::secure_io::write_batch_no_replace(store, first_write);

  REQUIRE(first_result.has_value());
  CHECK(read_text(first_collision) == "first-host-bytes");
  CHECK(read_text(sessions / "target.jsonl") == "new bytes\n");

  fs::remove(first_collision);
  fs::remove(sessions / "target.jsonl");
  const auto later_collision =
      sessions / (".bivpak-install-" + std::to_string(::getpid()) + "-1.tmp");
  {
    std::ofstream output{later_collision, std::ios::binary};
    output << "later-host-bytes";
  }
  const auto first = bytes("first\n");
  const auto second = bytes("second\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> later_writes{
      {.relative_path = "sessions/first.jsonl", .bytes = first},
      {.relative_path = "sessions/second.jsonl", .bytes = second}};

  const auto later_result =
      biv::adapters::secure_io::write_batch_no_replace(store, later_writes);

  REQUIRE(later_result.has_value());
  CHECK(read_text(later_collision) == "later-host-bytes");
  CHECK(read_text(sessions / "first.jsonl") == "first\n");
  CHECK(read_text(sessions / "second.jsonl") == "second\n");
  CHECK_FALSE(fs::exists(sessions / (".bivpak-install-" +
                                     std::to_string(::getpid()) + "-0.tmp")));
  fs::remove_all(root);
}

TEST_CASE("Claude install refuses nonzero rewrite verification before writing") {
  const auto root = make_tmp("verify-refuse");
  const auto workspace = root / "workspace";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = claude_members();
  auto hostile = bytes(std::string{"{\"cwd\":\"/ws/proj\",\"sessionId\":\""} +
                       std::string{kOriginalSession} + "\"}");
  hostile.push_back(static_cast<std::byte>(0xff));
  hostile.push_back(static_cast<std::byte>('\n'));
  members.at(main_artifact()) = std::move(hostile);
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().verify.origin_path_hits > 0);
  CHECK(result->sessions.front().verify.origin_id_hits > 0);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "Claude capabilities report absent, unvalidated, and validated hosts") {
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
