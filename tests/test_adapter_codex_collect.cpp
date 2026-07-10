#include <unistd.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "adapters/codex/codex.hpp"

namespace {

namespace fs = std::filesystem;

constexpr std::string_view kParent = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001";
constexpr std::string_view kChild = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0002";
constexpr std::string_view kDuplicate = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0003";

fs::path fixture_root() {
  return fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "codex_store";
}

struct FileStamp {
  std::uintmax_t size{};
  fs::file_time_type mtime{};

  friend bool operator==(const FileStamp&, const FileStamp&) = default;
};

std::map<std::string, FileStamp> snapshot_tree(const fs::path& root) {
  std::map<std::string, FileStamp> snapshot;
  for (const auto& entry : fs::recursive_directory_iterator(root)) {
    if (entry.is_regular_file()) {
      snapshot.emplace(fs::relative(entry.path(), root).generic_string(),
                       FileStamp{.size = entry.file_size(), .mtime = entry.last_write_time()});
    }
  }
  return snapshot;
}

std::string read_text(const fs::path& path) {
  std::ifstream input{path, std::ios::binary};
  return {std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
}

void write_file(const fs::path& path, std::string_view content) {
  fs::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  out << content;
}

fs::path make_tmp(std::string_view name) {
  auto base =
      fs::temp_directory_path() / ("biv-codex-collect-" + std::string{name} +
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

std::string joined_record_text(const biv::adapters::SessionRecord& record) {
  std::string text = record.agent;
  text += record.original_session_id;
  text += record.original_path;
  text += record.normalized_path_key;
  text += record.normalization_scheme;
  text += record.agent_version_at_pack;
  for (const auto& child : record.child_ids) {
    text += child;
  }
  for (const auto& artifact : record.artifacts) {
    text += artifact;
  }
  return text;
}

const biv::adapters::SessionRecord& find_session(const biv::adapters::CollectReport& report,
                                                 std::string_view id) {
  const auto found = std::ranges::find_if(report.sessions, [&](const biv::adapters::SessionRecord& session) {
    return session.original_session_id == id;
  });
  REQUIRE(found != report.sessions.end());
  return *found;
}

int count_occurrences(std::string_view haystack, std::string_view needle) {
  int count = 0;
  size_t pos = 0;
  while ((pos = haystack.find(needle, pos)) != std::string_view::npos) {
    ++count;
    pos += needle.size();
  }
  return count;
}

}  // namespace

TEST_CASE("Codex adapter discovers CODEX_HOME as an env-tier store") {
  const auto& adapter = biv::adapters::codex_adapter();
  const auto root = fixture_root();
  const auto sqlite_home = root / "sqlite";
  fs::create_directories(sqlite_home);
  fs::create_directories(root / "archived_sessions");
  const biv::adapters::Env env{
      .getenv = [&](const std::string_view name) -> std::optional<std::string> {
        if (name == "CODEX_HOME") {
          return root.string();
        }
        if (name == "CODEX_SQLITE_HOME") {
          return sqlite_home.string();
        }
        return std::nullopt;
      },
      .home = root.parent_path()};

  const auto stores = adapter.discover(env);

  REQUIRE(stores.has_value());
  REQUIRE(stores->size() == 2);
  CHECK(stores->front().root == root);
  CHECK(stores->front().tier == biv::adapters::DiscoveryTier::env);
  REQUIRE(stores->front().locators.size() == 2);
  CHECK(stores->front().locators.front().kind == "sessions_root");
  CHECK(stores->front().locators.at(1).kind == "sqlite_home");
  CHECK(stores->front().locators.at(1).path == sqlite_home);
  CHECK_FALSE(stores->front().archived);
  CHECK(stores->at(1).archived);
  REQUIRE(stores->at(1).locators.size() == 1);
  CHECK(stores->at(1).locators.front().kind == "sessions_root");
  CHECK(stores->at(1).locators.front().path == root / "archived_sessions");
  fs::remove_all(sqlite_home);
  fs::remove_all(root / "archived_sessions");
}

TEST_CASE("Codex adapter collects rollout parent, child, and same-store newest duplicate") {
  const auto& adapter = biv::adapters::codex_adapter();
  const auto root = fixture_root();
  const auto before = snapshot_tree(root);
  const std::vector<biv::adapters::Store> stores{
      biv::adapters::Store{
          .root = root,
          .locators = {biv::adapters::StoreLocator{.kind = "sessions_root", .path = root / "sessions"}},
          .tier = biv::adapters::DiscoveryTier::defaults,
          .archived = false}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 2);
  const auto& parent = find_session(*report, kParent);
  CHECK(parent.agent == "codex");
  CHECK(parent.child_ids == std::vector<std::string>{std::string{kChild}});
  CHECK(parent.original_path == "/ws/proj");
  CHECK(parent.normalized_path_key == "/ws/proj");
  CHECK(parent.normalization_scheme == "codex-cwd/v1");
  CHECK(parent.path_flavor == biv::manifest::PathFlavor::posix);
  CHECK(parent.agent_version_at_pack == "0.142.5");
  CHECK(parent.provenance.store_root == root.generic_string());
  CHECK(parent.provenance.locator == "sessions_root");
  CHECK(parent.provenance.discovery_tier == "default");
  CHECK(parent.artifacts == std::vector<std::string>{"agents/codex/" + std::string{kParent} + ".jsonl",
                                                     "agents/codex/" + std::string{kChild} + ".jsonl"});
  REQUIRE(parent.artifact_sources.size() == 2);
  const auto child_text = read_text(parent.artifact_sources.at(1));
  CHECK(count_occurrences(child_text, kParent) == 2);

  const auto& duplicate = find_session(*report, kDuplicate);
  CHECK(duplicate.agent_version_at_pack == "0.142.7");
  REQUIRE(duplicate.artifact_sources.size() == 1);
  CHECK(duplicate.artifact_sources.front()
            .filename()
            .generic_string()
            .starts_with("rollout-2026-07-06T02-00-00"));

  CHECK(std::ranges::any_of(report->warnings, [](const std::string& warning) {
    return warning.find("CodexDbEnrichmentSkipped") != std::string::npos;
  }));
  CHECK(joined_record_text(parent).find("DO_NOT_COLLECT") == std::string::npos);
  CHECK(joined_record_text(parent).find("eeeeeeee9999") == std::string::npos);
  CHECK(snapshot_tree(root) == before);
}

TEST_CASE("Codex adapter matches Windows cwd to its WSL workspace") {
  const auto root = make_tmp("windows-wsl");
  const auto store = root / "codex_store";
  const auto session_id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee0098"};
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T12-00-00-" + session_id + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T12:00:00Z\",\"type\":"
             "\"session_meta\",\"payload\":{\"id\":\"" +
                 session_id + "\",\"session_id\":\"" + session_id +
                 "\",\"cwd\":\"C:\\\\Users\\\\Me\\\\Proj\\\\sub\","
                 "\"cli_version\":\"0.142.5\"}}\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report =
      biv::adapters::codex_adapter().collect("/mnt/c/users/me/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  CHECK(report->sessions.front().original_session_id == session_id);
  CHECK(report->sessions.front().path_flavor ==
        biv::manifest::PathFlavor::windows);
  fs::remove_all(root);
}

TEST_CASE("Codex adapter inventory denies credentials and installation ids") {
  const auto& adapter = biv::adapters::codex_adapter();
  const auto& inventory = adapter.state_inventory();

  CHECK(std::ranges::find(inventory.never_collect, "auth.json") !=
        inventory.never_collect.end());
  CHECK(std::ranges::find(inventory.never_collect, "installation_id") !=
        inventory.never_collect.end());
}

TEST_CASE("Codex adapter skips symlinked and compressed rollout files") {
  const auto root = make_tmp("skip");
  const auto store = root / "codex_store";
  copy_fixture_tree(fixture_root(), store);
  const auto secret =
      root /
      "rollout-2026-07-06T09-00-00-019faaaa-bbbb-7ccc-8ddd-eeeeeeee7777.jsonl";
  write_file(secret,
             "{\"timestamp\":\"2026-07-06T09:00:00Z\",\"type\":"
             "\"session_meta\",\"payload\":{\"id\":\"019faaaa-"
             "bbbb-7ccc-8ddd-eeeeeeee7777\",\"cwd\":\"/ws/"
             "proj\",\"cli_version\":\"0.142.5\"}}\n");
  fs::create_symlink(secret, store / "sessions" / "2026" / "07" / "06" /
                                 "rollout-2026-07-06T09-00-00-019faaaa-bbbb-"
                                 "7ccc-8ddd-eeeeeeee7777.jsonl");
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 "rollout-2026-07-06T10-00-00-019faaaa-bbbb-7ccc-8ddd-"
                 "eeeeeeee8888.jsonl.zst",
             "{\"timestamp\":\"2026-07-06T10:00:00Z\",\"type\":\"session_"
             "meta\",\"payload\":{\"id\":\"019faaaa-"
             "bbbb-7ccc-8ddd-eeeeeeee8888\",\"cwd\":\"/ws/"
             "proj\",\"cli_version\":\"0.142.5\"}}\n");
  const auto& adapter = biv::adapters::codex_adapter();
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  CHECK(std::ranges::none_of(
      report->sessions, [](const biv::adapters::SessionRecord& session) {
        return session.original_session_id ==
                   "019faaaa-bbbb-7ccc-8ddd-eeeeeeee7777" ||
               session.original_session_id ==
                   "019faaaa-bbbb-7ccc-8ddd-eeeeeeee8888";
      }));
  CHECK(std::ranges::any_of(report->warnings, [](const std::string& warning) {
    return warning.find("CompressedRolloutSkipped") != std::string::npos;
  }));
  fs::remove_all(root);
}

TEST_CASE("Codex adapter keeps dangling parent ids for manifest emission") {
  const auto root = make_tmp("dangling-parent");
  const auto store = root / "codex";
  const auto missing_parent =
      std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7000"};
  const auto child = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7001"};
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T11-00-00-" + child + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T11:00:00Z\",\"type\":\"session_"
             "meta\",\"payload\":{\"id\":\"" +
                 child + "\",\"session_id\":\"" + child +
                 "\",\"cwd\":\"/ws/proj/"
                 "sub\",\"cli_version\":\"0.142.5\",\"parent_thread_id\":\"" +
                 missing_parent + "\"}}\n");
  const auto& adapter = biv::adapters::codex_adapter();
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  CHECK(report->sessions.front().original_session_id == child);
  REQUIRE(report->sessions.front().parent_id.has_value());
  CHECK(*report->sessions.front().parent_id == missing_parent);
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 fail-safe excludes duplicated ids",
          "[!mayfail][pending-e3]") {
  // E-3 answer relay under s3-escalate-3 -> replace exclusion with ruled A5
  // behavior.
  const auto& adapter = biv::adapters::codex_adapter();
  const auto root = fixture_root();
  const auto duplicate_root = fixture_root() / "duplicate_store";
  const std::vector<biv::adapters::Store> stores{
      biv::adapters::Store{.root = root,
                           .locators = {biv::adapters::StoreLocator{.kind = "sessions_root", .path = root / "sessions"}},
                           .tier = biv::adapters::DiscoveryTier::defaults},
      biv::adapters::Store{.root = duplicate_root,
                           .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                                                     .path = duplicate_root / "sessions"}},
                           .tier = biv::adapters::DiscoveryTier::defaults}};

  const auto report = adapter.collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  CHECK(std::ranges::none_of(report->sessions, [](const biv::adapters::SessionRecord& session) {
    return session.original_session_id == kParent;
  }));
  CHECK(std::ranges::any_of(report->warnings, [](const std::string& warning) {
    return warning.find("SessionDuplicateStorePending") != std::string::npos;
  }));
}
