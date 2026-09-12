#include <unistd.h>

#include <algorithm>
#include <cstdlib>
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
  return fs::canonical(base);
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

TEST_CASE("Claude collector rejects subtree files outside its three classes") {
  const auto root = make_tmp("subtree-class-set");
  const auto store = root / "claude_store";
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000077";
  const auto project = store / "projects" / "-ws-proj";
  const auto session_dir = project / session_id;
  write_file(project / (std::string{session_id} + ".jsonl"),
             std::string{R"({"type":"user","cwd":"/ws/proj","sessionId":")"} +
                 std::string{session_id} +
                 R"(","version":"2.1.202"})" + "\n");
  write_file(session_dir / "subagents" / "agent-a01.jsonl", "{}\n");
  write_file(session_dir / "subagents" / "agent-a01.meta.json", "{}\n");
  write_file(session_dir / "tool-results" / "nested" / "result.txt",
             "tool output\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto allowed =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE(allowed);
  REQUIRE(allowed->sessions.size() == 1U);
  CHECK(allowed->sessions.front().artifacts.size() == 4U);

  const auto offending = session_dir / "notes.md";
  write_file(offending, "not an installable subtree class\n");
  const auto refused =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE_FALSE(refused);
  CHECK(refused.error().kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(refused.error().path == offending.generic_string());
  CHECK(refused.error().detail == "unsupported_subtree_artifact");
  fs::remove_all(root);
}

TEST_CASE("CB2 Claude live collect covers flat bare and slug hex plus nested "
          "bare hex layouts") {
  const auto root = make_tmp("nested-subagent-reality-shape");
  const auto store = root / "claude_store";
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000078";
  const auto project = store / "projects" / "-ws-proj";
  const auto flat_bare_relative =
      std::string{session_id} + "/subagents/agent-a00e74f5f82549807.jsonl";
  const auto flat_slug_relative =
      std::string{session_id} +
      "/subagents/agent-explore-b00e74f5f82549807.jsonl";
  const auto nested_bare_relative =
      std::string{session_id} +
      "/subagents/workflows/wf-a/agent-c00e74f5f82549807.jsonl";
  const auto flat_bare_artifact = "agents/claude-code/" + flat_bare_relative;
  const auto flat_slug_artifact = "agents/claude-code/" + flat_slug_relative;
  const auto nested_bare_artifact =
      "agents/claude-code/" + nested_bare_relative;
  write_file(project / (std::string{session_id} + ".jsonl"),
             std::string{R"({"type":"user","cwd":"/ws/proj","sessionId":")"} +
                 std::string{session_id} +
                 R"(","version":"2.1.202"})" + "\n");
  write_file(project / flat_bare_relative,
             std::string{R"({"type":"assistant","sessionId":")"} +
                 std::string{session_id} +
                 R"(","agentId":"agent-a00e74f5f82549807"})" + "\n");
  write_file(project / flat_slug_relative,
             std::string{R"({"type":"assistant","sessionId":")"} +
                 std::string{session_id} +
                 R"(","agentId":"agent-explore-b00e74f5f82549807"})" + "\n");
  write_file(project / nested_bare_relative,
             std::string{R"({"type":"assistant","sessionId":")"} +
                 std::string{session_id} +
                 R"(","agentId":"agent-c00e74f5f82549807"})" + "\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& record = report->sessions.front();
  CHECK(contains_artifact(record, flat_bare_artifact));
  CHECK(contains_artifact(record, flat_slug_artifact));
  CHECK(contains_artifact(record, nested_bare_artifact));
  CHECK(record.child_ids ==
        std::vector<std::string>{"agent-a00e74f5f82549807",
                                 "agent-explore-b00e74f5f82549807"});
  CHECK(record.child_artifact_map.empty());
  fs::remove_all(root);
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
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents,
                          ".credentials.json") !=
        inventory.caveat_facts.relocated_contents.end());
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents,
                          "settings.json") !=
        inventory.caveat_facts.relocated_contents.end());
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents, "projects") !=
        inventory.caveat_facts.relocated_contents.end());
}

TEST_CASE("Claude adapter rejects symlinked project and session roots") {
  const auto root = make_tmp("symlink-roots");
  const auto store = root / "claude_store";
  const auto outside = root / "outside";
  copy_fixture_tree(fixture_root(), outside);
  fs::create_directories(store);
  fs::create_directory_symlink(outside / "projects", store / "projects");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults}};

  const auto project_result =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);
  REQUIRE_FALSE(project_result.has_value());

  fs::remove(store / "projects");
  fs::create_directories(store / "projects" / "-ws-proj");
  const auto session_id = std::string{"aaaaaaaa-1111-4000-8000-000000000001"};
  write_file(store / "projects" / "-ws-proj" / (session_id + ".jsonl"),
             "{\"cwd\":\"/ws/proj\",\"sessionId\":\"" + session_id +
                 "\"}\n");
  fs::create_directory_symlink(
      outside / "projects" / "-ws-proj" / session_id,
      store / "projects" / "-ws-proj" / session_id);

  const auto session_result =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);
  REQUIRE_FALSE(session_result.has_value());
  fs::remove_all(root);
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

TEST_CASE("Claude collected sources stay fd-bound across a leaf swap") {
  const auto root = make_tmp("fd-bound-swap");
  const auto store = root / "claude_store";
  copy_fixture_tree(fixture_root(), store);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::defaults}};
  const auto report =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);
  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  const auto source = report->sessions.front().artifact_sources.front();
  const auto moved = source.path.string() + ".approved";
  fs::rename(source.path, moved);
  write_file(root / "credential.jsonl", "DO_NOT_COLLECT_SWAPPED_CREDENTIAL\n");
  fs::create_symlink(root / "credential.jsonl", source.path);

  std::string streamed;
  const auto read = source.stream(
      [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
        for (const auto byte : chunk) {
          streamed.push_back(static_cast<char>(byte));
        }
        return {};
      });

  REQUIRE(read.has_value());
  CHECK(streamed.find("DO_NOT_COLLECT_SWAPPED_CREDENTIAL") == std::string::npos);
  CHECK(streamed.find("aaaaaaaa-1111-4000-8000-000000000001") !=
        std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("Claude collect applies all four torn-tail branches") {
  struct TailCase {
    std::string_view name;
    std::string_view tail;
    std::string_view expected;
    bool live;
    bool dropped;
  };
  const std::array cases{
      TailCase{"empty", "", "", true, false},
      TailCase{"valid", "{\"type\":\"assistant\"}", "{\"type\":\"assistant\"}\n", true, false},
      TailCase{"invalid-live", "{bad", "", true, true},
      TailCase{"invalid-terminal", "{bad", "{bad", false, false},
  };
  for (const auto& test_case : cases) {
    DYNAMIC_SECTION(test_case.name) {
      const auto root = make_tmp("torn-tail-" + std::string{test_case.name});
      const auto store = root / "claude";
      const auto id = std::string{"aaaaaaaa-1111-4000-8000-000000000120"};
      const auto prefix = std::string{"{\"type\":\"user\",\"cwd\":\"/ws/proj\",\"sessionId\":\""} +
                          id + "\",\"version\":\"2.1.202\"}\n";
      write_file(store / "projects" / "project" / (id + ".jsonl"),
                 prefix + std::string{test_case.tail});
      write_file(store / "sessions" / (id + ".json"),
                 std::string{"{\"sessionId\":\""} + id + "\",\"status\":\"" +
                     (test_case.live ? "running" : "completed") + "\"}");
      const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
          .root = store, .locators = {{.kind = "sessions_root", .path = store / "projects"}}}};
      const auto report = biv::adapters::claude_code_adapter().collect("/ws/proj", stores);
      REQUIRE(report);
      REQUIRE(report->sessions.size() == 1U);
      const auto& record = report->sessions.front();
      CHECK(record.live_at_pack == test_case.live);
      std::string bytes;
      REQUIRE(record.artifact_sources.front().stream(
          [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
            for (const auto byte : chunk) bytes.push_back(static_cast<char>(byte));
            return {};
          }));
      CHECK(bytes == prefix + std::string{test_case.expected});
      const auto has_invalid_tail = test_case.dropped || test_case.name == "invalid-terminal";
      REQUIRE(record.torn_tails.size() == (has_invalid_tail ? 1U : 0U));
      if (has_invalid_tail) {
        CHECK(record.torn_tails.front().artifact == "agents/claude-code/" + id + ".jsonl");
        CHECK(record.torn_tails.front().bytes == test_case.tail.size());
      }
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Claude collect never inspects an invalid interior segment") {
  const auto root = make_tmp("torn-tail-interior");
  const auto store = root / "claude";
  const auto id = std::string{"aaaaaaaa-1111-4000-8000-000000000121"};
  const auto bytes = std::string{"{\"type\":\"user\",\"cwd\":\"/ws/proj\",\"sessionId\":\""} +
                     id + "\",\"version\":\"2.1.202\"}\n{bad\n{\"type\":\"assistant\"}";
  write_file(store / "projects" / "project" / (id + ".jsonl"), bytes);
  write_file(store / "sessions" / (id + ".json"),
             "{\"sessionId\":\"" + id + "\",\"status\":\"running\"}");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store, .locators = {{.kind = "sessions_root", .path = store / "projects"}}}};
  const auto report = biv::adapters::claude_code_adapter().collect("/ws/proj", stores);
  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  CHECK(report->sessions.front().live_at_pack);
  std::string streamed;
  REQUIRE(report->sessions.front().artifact_sources.front().stream(
      [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
        for (const auto byte : chunk) {
          streamed.push_back(static_cast<char>(byte));
        }
        return {};
      }));
  CHECK(streamed == bytes + "\n");
  CHECK(report->sessions.front().torn_tails.empty());
  fs::remove_all(root);
}

TEST_CASE("Claude collect drops a whole-file invalid live subtree segment") {
  const auto root = make_tmp("torn-tail-whole-invalid");
  const auto store = root / "claude";
  const auto id = std::string{"aaaaaaaa-1111-4000-8000-000000000122"};
  const auto tail = std::string{"{bad"};
  const auto artifact = "agents/claude-code/" + id +
                        "/subagents/agent-a01.jsonl";
  write_file(store / "projects" / "project" / (id + ".jsonl"),
             "{\"type\":\"user\",\"cwd\":\"/ws/proj\",\"sessionId\":\"" +
                 id + "\",\"version\":\"2.1.202\"}\n");
  write_file(store / "projects" / "project" / id / "subagents" /
                 "agent-a01.jsonl",
             tail);
  write_file(store / "sessions" / (id + ".json"),
             "{\"sessionId\":\"" + id + "\",\"status\":\"running\"}");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {{.kind = "sessions_root", .path = store / "projects"}}}};

  const auto report = biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& record = report->sessions.front();
  const auto source_index = std::ranges::find(record.artifacts, artifact) -
                            record.artifacts.begin();
  REQUIRE(source_index < static_cast<std::ptrdiff_t>(record.artifact_sources.size()));
  std::string streamed;
  REQUIRE(record.artifact_sources.at(static_cast<std::size_t>(source_index)).stream(
      [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
        for (const auto byte : chunk) streamed.push_back(static_cast<char>(byte));
        return {};
      }));
  CHECK(streamed.empty());
  CHECK(record.artifact_sources.at(static_cast<std::size_t>(source_index)).size == 0U);
  const auto fact = std::ranges::find(record.torn_tails, artifact,
                                     &biv::adapters::SessionRecord::TornTail::artifact);
  REQUIRE(fact != record.torn_tails.end());
  CHECK(fact->bytes == tail.size());
  fs::remove_all(root);
}

namespace slice_e_claude_guards {

class ScopedEnv {
 public:
  ScopedEnv(std::string name, const fs::path& value) : name_(std::move(name)) {
    if (const char* current = std::getenv(name_.c_str()); current != nullptr) {
      previous_ = std::string{current};
    }
    REQUIRE(::setenv(name_.c_str(), value.c_str(), 1) == 0);
  }
  ~ScopedEnv() {
    if (previous_) {
      (void)::setenv(name_.c_str(), previous_->c_str(), 1);
    } else {
      (void)::unsetenv(name_.c_str());
    }
  }

 private:
  std::string name_;
  std::optional<std::string> previous_;
};

class ScopedPackDiscoveryEnv {
 public:
  explicit ScopedPackDiscoveryEnv(const fs::path& root)
      : home_{"HOME", root / "home"},
        claude_{"CLAUDE_CONFIG_DIR", root / "claude"},
        codex_{"CODEX_HOME", root / "absent-codex"},
        sqlite_{"CODEX_SQLITE_HOME", root / "absent-sqlite"} {}

 private:
  ScopedEnv home_;
  ScopedEnv claude_;
  ScopedEnv codex_;
  ScopedEnv sqlite_;
};

void require_store_roots_under(const biv::adapters::SessionRecord& record,
                               const fs::path& root) {
  const auto relative = fs::weakly_canonical(record.provenance.store_root)
                            .lexically_relative(fs::canonical(root));
  REQUIRE(!relative.empty());
  REQUIRE(*relative.begin() != "..");
}

}  // namespace slice_e_claude_guards

TEST_CASE("FX-A12-7 Claude flat subagents enumeration is unchanged",
          "[slice-e][slice-e-control]") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-00000000a120";
  constexpr std::string_view decoy = "SLICE_E_CREDENTIAL_DECOY";
  const auto root = make_tmp("slice-e-fx-a12-7");
  const auto store = root / "claude";
  const slice_e_claude_guards::ScopedPackDiscoveryEnv discovery_env{root};
  copy_fixture_tree(fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
                        "slice-e" / "claude" /
                        "flat-subagents-unchanged",
                    store);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "projects"}},
      .tier = biv::adapters::DiscoveryTier::env,
      .archived = false}};

  const auto report =
      biv::adapters::claude_code_adapter().collect("/ws/proj", stores);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& record = report->sessions.front();
  CHECK(record.original_session_id == session_id);
  CHECK(record.child_ids ==
        std::vector<std::string>{"agent-a00e74f5f82549807",
                                 "agent-explore-b00e74f5f82549807"});
  CHECK(record.child_artifact_map.empty());
  CHECK(contains_artifact(
      record, "agents/claude-code/aaaaaaaa-1111-4000-8000-00000000a120/"
              "subagents/agent-a00e74f5f82549807.jsonl"));
  CHECK(contains_artifact(
      record, "agents/claude-code/aaaaaaaa-1111-4000-8000-00000000a120/"
              "subagents/agent-explore-b00e74f5f82549807.jsonl"));
  CHECK(contains_artifact(
      record, "agents/claude-code/aaaaaaaa-1111-4000-8000-00000000a120/"
              "subagents/workflows/wf-a/agent-c00e74f5f82549807.jsonl"));
  slice_e_claude_guards::require_store_roots_under(record, root);
  CHECK(joined_record_text(record).find(decoy) == std::string::npos);
  for (const auto& source : record.artifact_sources) {
    std::string content;
    REQUIRE(source.stream(
        [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
          for (const auto byte : chunk) {
            content.push_back(static_cast<char>(byte));
          }
          return {};
        }));
    CHECK(content.find(decoy) == std::string::npos);
  }
  fs::remove_all(root);
}
