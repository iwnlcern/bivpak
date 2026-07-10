#include <unistd.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "adapters/claude_code/claude_code.hpp"

namespace {

namespace fs = std::filesystem;

fs::path fixture_root() {
  return fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "claude_store";
}

struct FileStamp {
  std::uintmax_t size{};
  fs::file_time_type mtime{};

  friend bool operator==(const FileStamp&, const FileStamp&) = default;
};

std::map<std::string, FileStamp> snapshot_tree(const fs::path& root) {
  std::map<std::string, FileStamp> snapshot;
  for (const auto& entry : fs::recursive_directory_iterator(root)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    const auto rel = fs::relative(entry.path(), root).generic_string();
    snapshot.emplace(rel, FileStamp{.size = entry.file_size(), .mtime = entry.last_write_time()});
  }
  return snapshot;
}

std::string joined_record_text(const biv::adapters::SessionRecord& record) {
  std::string text = record.agent;
  text += record.original_session_id;
  text += record.original_path;
  text += record.normalized_path_key;
  text += record.agent_version_at_pack;
  for (const auto& child_id : record.child_ids) {
    text += child_id;
  }
  for (const auto& artifact : record.artifacts) {
    text += artifact;
  }
  return text;
}

bool contains_artifact(const biv::adapters::SessionRecord& record, const std::string_view artifact) {
  return std::ranges::find(record.artifacts, artifact) != record.artifacts.end();
}

fs::path make_tmp(std::string_view name) {
  auto base =
      fs::temp_directory_path() / ("biv-claude-collect-" + std::string{name} +
                                   "-" + std::to_string(::getpid()));
  fs::remove_all(base);
  fs::create_directories(base);
  return base;
}

void copy_fixture_tree(const fs::path& from, const fs::path& to) {
  for (const auto& entry : fs::recursive_directory_iterator(from)) {
    const auto rel = fs::relative(entry.path(), from);
    const auto dest = to / rel;
    if (entry.is_directory()) {
      fs::create_directories(dest);
      continue;
    }
    if (entry.is_regular_file()) {
      fs::create_directories(dest.parent_path());
      fs::copy_file(entry.path(), dest);
    }
  }
}

void write_file(const fs::path& path, const std::string_view content) {
  fs::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  out << content;
}

}  // namespace

TEST_CASE("Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store") {
  const auto& adapter = biv::adapters::claude_code_adapter();
  const auto root = fixture_root();
  const biv::adapters::Env env{
      .getenv = [&](const std::string_view name) -> std::optional<std::string> {
        if (name == "CLAUDE_CONFIG_DIR") {
          return root.string();
        }
        return std::nullopt;
      },
      .home = root.parent_path()};

  const auto stores = adapter.discover(env);

  REQUIRE(stores.has_value());
  REQUIRE(stores->size() == 1);
  CHECK(stores->front().root == root);
  CHECK(stores->front().tier == biv::adapters::DiscoveryTier::env);
  REQUIRE(stores->front().locators.size() == 1);
  CHECK(stores->front().locators.front().kind == "sessions_root");
}

TEST_CASE("Claude adapter collects only matching cwd transcript and subagent artifacts") {
  const auto& adapter = biv::adapters::claude_code_adapter();
  const auto root = fixture_root();
  const auto before = snapshot_tree(root);
  const std::vector<biv::adapters::Store> stores{
      biv::adapters::Store{
          .root = root,
          .locators = {biv::adapters::StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
          .tier = biv::adapters::DiscoveryTier::defaults,
          .archived = false}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  const auto& session = report->sessions.front();
  CHECK(session.agent == "claude-code");
  CHECK(session.original_session_id == "aaaaaaaa-1111-4000-8000-000000000001");
  CHECK(session.child_ids == std::vector<std::string>{"agent-a01"});
  CHECK(session.original_path == "/ws/proj");
  CHECK(session.normalized_path_key == "/ws/proj");
  CHECK(session.path_flavor == biv::manifest::PathFlavor::posix);
  CHECK(session.agent_version_at_pack == "2.1.202");
  CHECK(session.live_at_pack);
  CHECK(session.provenance.store_root == root.generic_string());
  CHECK(session.provenance.locator == "sessions_root");
  CHECK(session.provenance.discovery_tier == "default");
  CHECK_FALSE(session.provenance.archived);
  REQUIRE(session.artifacts.size() == 3);
  CHECK(contains_artifact(
      session,
      "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001.jsonl"));
  CHECK(contains_artifact(
      session,
      "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/"
      "subagents/agent-a01.jsonl"));
  CHECK(contains_artifact(
      session,
      "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/"
      "subagents/agent-a01.meta.json"));
  REQUIRE(report->no_cwd_record.size() == 1);
  CHECK(report->no_cwd_record.front().find("no-cwd") != std::string::npos);
  CHECK(joined_record_text(session).find("DO_NOT_COLLECT") == std::string::npos);
  CHECK(joined_record_text(session).find("cccc-2222") == std::string::npos);
  CHECK(snapshot_tree(root) == before);
}

TEST_CASE("Claude adapter keys membership on the first cwd record") {
  const auto root = make_tmp("first-cwd");
  const auto store = root / "claude_store";
  const auto session_id = std::string{"aaaaaaaa-1111-4000-8000-000000000099"};
  write_file(
      store / "projects" / "-ws-proj" / (session_id + ".jsonl"),
      "{\"type\":\"user\",\"cwd\":\"/other/proj\",\"sessionId\":\"" +
          session_id +
          "\",\"version\":\"2.1.202\"}\n"
          "{\"type\":\"assistant\",\"cwd\":\"/ws/proj\",\"sessionId\":\"" +
          session_id + "\"}\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  CHECK(report->sessions.empty());
  fs::remove_all(root);
}

TEST_CASE("Claude adapter matches Windows cwd to its WSL workspace") {
  const auto root = make_tmp("windows-wsl");
  const auto store = root / "claude_store";
  const auto session_id = std::string{"aaaaaaaa-1111-4000-8000-000000000098"};
  write_file(store / "projects" / "windows-project" / (session_id + ".jsonl"),
             "{\"type\":\"user\",\"cwd\":\"\\\\\\\\?\\\\C:"
             "\\\\Users\\\\Me\\\\Proj\\\\sub\","
             "\"sessionId\":\"" +
                 session_id + "\",\"version\":\"2.1.202\"}\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report = biv::adapters::claude_code_adapter().collect(
      "/mnt/c/users/me/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  CHECK(report->sessions.front().original_session_id == session_id);
  CHECK(report->sessions.front().path_flavor ==
        biv::manifest::PathFlavor::windows);
  fs::remove_all(root);
}

TEST_CASE("Claude adapter inventory denies credential and settings files") {
  const auto& adapter = biv::adapters::claude_code_adapter();
  const auto& inventory = adapter.state_inventory();

  CHECK(std::ranges::find(inventory.never_collect, ".credentials.json") !=
        inventory.never_collect.end());
  CHECK(std::ranges::find(inventory.never_collect, ".claude.json") !=
        inventory.never_collect.end());
  CHECK(std::ranges::find(inventory.never_collect, "settings.json") !=
        inventory.never_collect.end());
  CHECK(std::ranges::find(inventory.never_collect, "settings.local.json") !=
        inventory.never_collect.end());
}

TEST_CASE("Claude adapter does not collect symlinked subtree artifacts") {
  const auto root = make_tmp("symlink");
  const auto store = root / "claude_store";
  copy_fixture_tree(fixture_root(), store);
  const auto secret = root / "secret.jsonl";
  {
    std::ofstream out{secret};
    out << "DO_NOT_COLLECT_SYMLINK_SECRET\n";
  }
  const auto link = store / "projects" / "-ws-proj" /
                    "aaaaaaaa-1111-4000-8000-000000000001" / "leak.jsonl";
  fs::create_symlink(secret, link);

  const auto& adapter = biv::adapters::claude_code_adapter();
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  const auto& session = report->sessions.front();
  CHECK_FALSE(contains_artifact(
      session,
      "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/leak.jsonl"));
  CHECK(joined_record_text(session).find("leak.jsonl") == std::string::npos);
  fs::remove_all(root);
}
