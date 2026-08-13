#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <sqlite3.h>

#include "adapters/codex/codex.hpp"

namespace biv::adapters {
void normalize_torn_jsonl_artifacts(
    std::vector<std::string>& artifacts,
    std::vector<SessionRecord::ArtifactSource>& sources,
    bool live,
    std::vector<SessionRecord::TornTail>& torn_tails);
}

namespace {

namespace fs = std::filesystem;

volatile std::sig_atomic_t fifo_deadline_expired = 0;

void mark_fifo_deadline_expired(int) noexcept { fifo_deadline_expired = 1; }

// An interrupted openat has no retry above it in the component loop, so a
// wedged FIFO open becomes an attributed per-case failure rather than process
// death or a CI timeout. The committed control proves the reporting half only.
class ScopedFifoDeadline {
 public:
  ScopedFifoDeadline() {
    fifo_deadline_expired = 0;
    struct sigaction action {};
    action.sa_handler = mark_fifo_deadline_expired;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    REQUIRE(::sigaction(SIGALRM, &action, &previous_action_) == 0);
  }

  ScopedFifoDeadline(const ScopedFifoDeadline&) = delete;
  ScopedFifoDeadline& operator=(const ScopedFifoDeadline&) = delete;

  ~ScopedFifoDeadline() {
    cancel();
    (void)::sigaction(SIGALRM, &previous_action_, nullptr);
  }

  void arm(const unsigned int seconds) {
    const auto previous_alarm = ::alarm(seconds);
    armed_ = true;
    REQUIRE(previous_alarm == 0U);
  }

  void cancel() noexcept {
    if (armed_) {
      (void)::alarm(0);
      armed_ = false;
    }
  }

 private:
  struct sigaction previous_action_ {};
  bool armed_{false};
};

TEST_CASE("Codex FIFO deadline control reports synchronous SIGALRM delivery") {
  ScopedFifoDeadline deadline;
  REQUIRE(::raise(SIGALRM) == 0);
  REQUIRE(fifo_deadline_expired == 1);
}

constexpr std::string_view kParent = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001";
constexpr std::string_view kChild = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0002";
constexpr std::string_view kDuplicate = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0003";

fs::path fixture_root() {
  return fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "codex_store";
}

fs::path tail_fixture_root() { return fixture_root() / "tail_matrix"; }

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

void write_rollout(const fs::path& store, std::string_view id,
                   std::string_view timestamp, std::string_view marker) {
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T01-00-00-" + std::string{id} + ".jsonl"),
             "{\"timestamp\":\"" + std::string{timestamp} +
                 "\",\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                 std::string{id} + "\",\"session_id\":\"" + std::string{id} +
                 "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"" +
                 std::string{marker} + "\"}}\n");
}

void write_threads_db(const fs::path& directory, std::string_view id,
                      std::int64_t updated_at) {
  fs::create_directories(directory);
  sqlite3* database = nullptr;
  REQUIRE(sqlite3_open((directory / "state_5.sqlite").c_str(), &database) ==
          SQLITE_OK);
  const std::string sql =
      "CREATE TABLE threads(id TEXT PRIMARY KEY, updated_at INTEGER, extra TEXT);"
      "INSERT INTO threads(id, updated_at, extra) VALUES('" +
      std::string{id} + "'," + std::to_string(updated_at) + ",'ignored');";
  char* error = nullptr;
  CHECK(sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &error) == SQLITE_OK);
  sqlite3_free(error);
  CHECK(sqlite3_close(database) == SQLITE_OK);
}

fs::path make_tmp(std::string_view name) {
  auto base =
      fs::temp_directory_path() / ("biv-codex-collect-" + std::string{name} +
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

TEST_CASE("Codex adapter reads sqlite_home from config and collection honors it") {
  const auto root = make_tmp("config-sqlite-home");
  const auto store = root / "codex";
  const auto sqlite_home = root / "sqlite";
  fs::create_directories(store);
  fs::create_directories(sqlite_home);
  write_file(store / "config.toml",
             "model = \"gpt-5\"\nsqlite_home = \"" +
                 sqlite_home.generic_string() + "\"\n");
  write_file(sqlite_home / "state_5.sqlite", "not-a-database");
  const auto session_id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee6611"};
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T01-00-00-" + session_id + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":"
             "\"session_meta\",\"payload\":{\"id\":\"" + session_id +
                 "\",\"session_id\":\"" + session_id +
                 "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n");
  const biv::adapters::Env env{
      .getenv = [&](const std::string_view name) -> std::optional<std::string> {
        return name == "CODEX_HOME" ? std::optional<std::string>{store.string()}
                                    : std::nullopt;
      },
      .home = root};

  const auto stores = biv::adapters::codex_adapter().discover(env);

  REQUIRE(stores.has_value());
  REQUIRE(stores->size() == 1);
  REQUIRE(stores->front().locators.size() == 2);
  CHECK(stores->front().locators.at(1).kind == "sqlite_home");
  CHECK(stores->front().locators.at(1).path == sqlite_home);

  const auto report = biv::adapters::codex_adapter().collect("/ws/proj", *stores);
  REQUIRE(report.has_value());
  CHECK(std::ranges::any_of(report->warnings, [&](const std::string& warning) {
    return warning ==
           "CodexDbEnrichmentSkipped:" +
               (sqlite_home / "state_5.sqlite").generic_string();
  }));
  fs::remove_all(root);
}

TEST_CASE("Codex collect executes database reachability for a FIFO") {
  // REACHABILITY EXECUTION. Absence-blind as to which arm fired: a directory,
  // FIFO, symlink, corrupt-but-regular file, and permission failure all emit the
  // same warning. This asserts an OBSERVED warning, never a derived state, and
  // discharges no part of the arm coverage.
  const auto root = make_tmp("fifo-database-reachability");
  const auto database = root / "state_5.sqlite";
  write_rollout(root, "019faaaa-bbbb-7ccc-8ddd-eeeeeeee6612",
                "2026-07-06T01:00:00Z", "fifo-database");
  REQUIRE(::mkfifo(database.c_str(), 0600) == 0);
  const std::vector<biv::adapters::Store> stores{
      biv::adapters::Store{
          .root = root,
          .locators = {biv::adapters::StoreLocator{
              .kind = "sessions_root", .path = root / "sessions"}},
          .tier = biv::adapters::DiscoveryTier::env,
          .archived = false}};

  const auto report = [&] {
    ScopedFifoDeadline deadline;
    deadline.arm(5);
    auto guarded_report = biv::adapters::codex_adapter().collect("/ws/proj", stores);
    deadline.cancel();
    REQUIRE(fifo_deadline_expired == 0);
    return guarded_report;
  }();

  REQUIRE(report.has_value());
  CHECK(std::ranges::any_of(report->warnings, [&](const std::string& warning) {
    return warning ==
           "CodexDbEnrichmentSkipped:" + database.generic_string();
  }));
  fs::remove_all(root);
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
  const auto child_text = read_text(parent.artifact_sources.at(1).path);
  CHECK(count_occurrences(child_text, kParent) == 2);

  const auto& duplicate = find_session(*report, kDuplicate);
  CHECK(duplicate.agent_version_at_pack == "0.142.7");
  REQUIRE(duplicate.artifact_sources.size() == 1);
  CHECK(duplicate.artifact_sources.front().path
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

TEST_CASE("Codex adapter derives liveness from exactly the final rollout record") {
  struct TailCase {
    std::string_view fixture;
    std::string_view id;
    bool live;
    bool collectable;
  };
  const std::array cases{
      TailCase{"rollout-task-complete-with-lf-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1001.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1001", false, true},
      TailCase{"rollout-task-complete-without-lf-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1002.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1002", false, true},
      TailCase{"rollout-turn-aborted-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1003.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1003", false, true},
      TailCase{"rollout-thread-rolled-back-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1004.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1004", false, true},
      TailCase{"rollout-session-meta-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1005.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1005", true, true},
      TailCase{"rollout-dangling-tool-call-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1006.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1006", true, true},
      TailCase{"rollout-malformed-complete-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1007.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1007", true, true},
      TailCase{"rollout-truncated-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1008.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1008", true, true},
      TailCase{"rollout-empty-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1009.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1009", true, false},
      TailCase{"rollout-terminal-before-corrupt-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1010.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1010", true, true},
      TailCase{"rollout-trailing-blank-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1011.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1011", true, true},
      TailCase{"rollout-lone-lf-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1012.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1012", true, false},
      TailCase{"rollout-final-record-missing-type-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1013.jsonl",
               "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1013", true, true},
  };

  for (const auto& test_case : cases) {
    DYNAMIC_SECTION(test_case.fixture) {
      const auto fixture = tail_fixture_root() / test_case.fixture;
      REQUIRE(fs::is_regular_file(fixture));
      const auto rollout = read_text(fixture);
      CHECK(biv::adapters::has_terminal_tail_record(rollout) ==
            !test_case.live);

      const auto root = make_tmp(test_case.id);
      const auto store = root / "codex";
      const auto destination = store / "sessions" / "2026" / "08" / "05" /
                               std::string{test_case.fixture};
      fs::create_directories(destination.parent_path());
      fs::copy_file(fixture, destination);
      const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
          .root = store,
          .locators = {biv::adapters::StoreLocator{
              .kind = "sessions_root", .path = store / "sessions"}},
          .tier = biv::adapters::DiscoveryTier::defaults,
          .archived = false}};

      const auto report =
          biv::adapters::codex_adapter().collect("/ws/proj", stores);

      REQUIRE(report.has_value());
      if (!test_case.collectable) {
        CHECK(report->sessions.empty());
        fs::remove_all(root);
        continue;
      }
      REQUIRE(report->sessions.size() == 1);
      CHECK(report->sessions.front().original_session_id == test_case.id);
      CHECK(report->sessions.front().live_at_pack == test_case.live);
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Codex parent liveness includes an absorbed live child") {
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1014";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1015";
  const auto root = make_tmp("terminal-parent-live-child");
  const auto store = root / "codex";
  const auto sessions = store / "sessions" / "2026" / "08" / "05";
  fs::create_directories(sessions);
  for (const auto name : {
           "rollout-terminal-parent-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1014.jsonl",
           "rollout-live-child-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1015.jsonl"}) {
    fs::copy_file(tail_fixture_root() / name, sessions / name);
  }
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};

  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1);
  const auto& parent = report->sessions.front();
  CHECK(parent.original_session_id == parent_id);
  CHECK(parent.child_ids ==
        std::vector<std::string>{std::string{child_id}});
  CHECK(parent.live_at_pack);
  fs::remove_all(root);
}

TEST_CASE("Codex collect trims only a live invalid final segment") {
  struct TailCase {
    std::string_view name;
    std::string_view tail;
    std::string_view expected;
    bool live;
    bool dropped;
  };
  const std::array cases{
      TailCase{"empty", "", "", true, false},
      TailCase{"valid", "{\"type\":\"task_complete\"}",
               "{\"type\":\"task_complete\"}\n", false, false},
      // This liveness assertion deliberately rides B1's real final-record
      // derivation; do not replace it with a test-only live flag.
      TailCase{"invalid-live", "{bad", "", true, true},
  };
  for (const auto& test_case : cases) {
    DYNAMIC_SECTION(test_case.name) {
      const auto root = make_tmp("torn-tail-" + std::string{test_case.name});
      const auto store = root / "codex";
      const auto id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee1020"};
      const auto prefix = std::string{"{\"timestamp\":\"2026-08-05T00:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                          id + "\",\"session_id\":\"" + id +
                          "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n";
      const auto path = store / "sessions" / "2026" / "08" / "05" /
                        ("rollout-2026-08-05T00-00-00-" + id + ".jsonl");
      write_file(path, prefix + std::string{test_case.tail});
      const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
          .root = store,
          .locators = {{.kind = "sessions_root", .path = store / "sessions"}},
          .tier = biv::adapters::DiscoveryTier::defaults}};
      const auto report = biv::adapters::codex_adapter().collect("/ws/proj", stores);
      REQUIRE(report);
      REQUIRE(report->sessions.size() == 1U);
      const auto& record = report->sessions.front();
      CHECK(record.live_at_pack == test_case.live);
      REQUIRE(record.artifact_sources.size() == 1U);
      std::string bytes;
      REQUIRE(record.artifact_sources.front().stream(
          [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
            for (const auto byte : chunk) bytes.push_back(static_cast<char>(byte));
            return {};
          }));
      CHECK(bytes == prefix + std::string{test_case.expected});
      REQUIRE(record.torn_tails.size() == (test_case.dropped ? 1U : 0U));
      if (test_case.dropped) {
        CHECK(record.torn_tails.front().artifact == "agents/codex/" + id + ".jsonl");
        CHECK(record.torn_tails.front().bytes == test_case.tail.size());
      }
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Codex tail normalizer retains an invalid non-live final segment") {
  const auto path = fs::path{"/virtual/branch-4.jsonl"};
  const std::string prefix{"{\"type\":\"task_complete\"}\n"};
  const std::string tail{"{bad"};
  std::vector<std::string> artifacts{"agents/codex/branch-4.jsonl"};
  std::vector<biv::adapters::SessionRecord::ArtifactSource> sources{
      {.path = path,
       .size = static_cast<std::uint64_t>(prefix.size() + tail.size()),
       .stream = [bytes = prefix + tail](const auto& sink) {
         return sink(std::as_bytes(std::span<const char>{bytes.data(), bytes.size()}));
       }}};
  std::vector<biv::adapters::SessionRecord::TornTail> facts;

  biv::adapters::normalize_torn_jsonl_artifacts(artifacts, sources, false, facts);

  std::string retained;
  REQUIRE(sources.front().stream([&](const std::span<const std::byte> chunk) -> biv::expected<void> {
    for (const auto byte : chunk) retained.push_back(static_cast<char>(byte));
    return {};
  }));
  CHECK(retained == prefix + tail);
  REQUIRE(facts.size() == 1U);
  CHECK(facts.front().artifact == "agents/codex/branch-4.jsonl");
  CHECK(facts.front().bytes == tail.size());
}

TEST_CASE("Codex tail normalizer drops a whole-file invalid live segment") {
  const auto path = fs::path{"/virtual/whole-invalid.jsonl"};
  const std::string tail{"{bad"};
  std::vector<std::string> artifacts{"agents/codex/whole-invalid.jsonl"};
  std::vector<biv::adapters::SessionRecord::ArtifactSource> sources{
      {.path = path,
       .size = static_cast<std::uint64_t>(tail.size()),
       .stream = [tail](const auto& sink) {
         return sink(std::as_bytes(
             std::span<const char>{tail.data(), tail.size()}));
       }}};
  std::vector<biv::adapters::SessionRecord::TornTail> facts;

  biv::adapters::normalize_torn_jsonl_artifacts(artifacts, sources, true,
                                                 facts);

  std::string retained;
  REQUIRE(sources.front().stream(
      [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
        for (const auto byte : chunk) {
          retained.push_back(static_cast<char>(byte));
        }
        return {};
      }));
  CHECK(retained.empty());
  CHECK(sources.front().size == 0U);
  REQUIRE(facts.size() == 1U);
  CHECK(facts.front().artifact == artifacts.front());
  CHECK(facts.front().bytes == tail.size());
}

TEST_CASE("Codex tail normalizer keeps multi-artifact facts paired") {
  const std::array tails{std::string{"{bad"}, std::string{"{worse"}};
  std::vector<std::string> artifacts{"agents/codex/parent.jsonl",
                                     "agents/codex/child.jsonl"};
  std::vector<biv::adapters::SessionRecord::ArtifactSource> sources;
  for (std::size_t i = 0; i < tails.size(); ++i) {
    sources.push_back(
        {.path = fs::path{"/virtual"} / fs::path{artifacts.at(i)}.filename(),
         .size = static_cast<std::uint64_t>(tails.at(i).size()),
         .stream = [tail = tails.at(i)](const auto& sink) {
           return sink(std::as_bytes(
               std::span<const char>{tail.data(), tail.size()}));
         }});
  }
  std::vector<biv::adapters::SessionRecord::TornTail> facts;

  biv::adapters::normalize_torn_jsonl_artifacts(artifacts, sources, true,
                                                 facts);

  REQUIRE(facts.size() == 2U);
  for (std::size_t i = 0; i < facts.size(); ++i) {
    CHECK(facts.at(i).artifact == artifacts.at(i));
    CHECK(facts.at(i).bytes == tails.at(i).size());
    CHECK(sources.at(i).size == 0U);
  }
}

TEST_CASE("Codex collect keeps a terminal child under a live parent intact") {
  const auto root = make_tmp("live-parent-terminal-child");
  const auto store = root / "codex";
  const std::string parent_id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee1031"};
  const std::string child_id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee1032"};
  const std::string parent =
      "{\"timestamp\":\"2026-08-05T00:00:00Z\",\"type\":\"session_meta\","
      "\"payload\":{\"id\":\"" +
      parent_id +
      "\",\"session_id\":\"" + parent_id +
      "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}";
  const std::string child =
      "{\"timestamp\":\"2026-08-05T00:01:00Z\",\"type\":\"session_meta\","
      "\"payload\":{\"id\":\"" +
      child_id + "\",\"session_id\":\"" + parent_id +
      "\",\"cwd\":\"/ws/proj/sub\",\"cli_version\":\"0.142.5\","
      "\"parent_thread_id\":\"" + parent_id +
      "\"}}\n{\"type\":\"task_complete\"}";
  write_file(store / "sessions" / "2026" / "08" / "05" /
                 ("rollout-2026-08-05T00-00-00-" + parent_id + ".jsonl"),
             parent);
  write_file(store / "sessions" / "2026" / "08" / "05" /
                 ("rollout-2026-08-05T00-01-00-" + child_id + ".jsonl"),
             child);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {{.kind = "sessions_root", .path = store / "sessions"}}}};

  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  REQUIRE(report->sessions.size() == 1U);
  const auto& record = report->sessions.front();
  CHECK(record.live_at_pack);
  CHECK(record.child_ids == std::vector<std::string>{child_id});
  REQUIRE(record.artifact_sources.size() == 2U);
  CHECK(record.torn_tails.empty());
  const std::array expected{parent + "\n", child + "\n"};
  for (std::size_t i = 0; i < record.artifact_sources.size(); ++i) {
    std::string streamed;
    REQUIRE(record.artifact_sources.at(i).stream(
        [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
          for (const auto byte : chunk) {
            streamed.push_back(static_cast<char>(byte));
          }
          return {};
        }));
    CHECK(streamed == expected.at(i));
  }
  fs::remove_all(root);
}

TEST_CASE("Codex collect never inspects an invalid interior segment") {
  const auto root = make_tmp("torn-tail-interior");
  const auto store = root / "codex";
  const auto id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee1021"};
  const auto bytes = std::string{"{\"timestamp\":\"2026-08-05T00:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                     id + "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n{bad\n{\"type\":\"event_msg\",\"payload\":{\"type\":\"user_message\",\"message\":\"x\"}}";
  write_file(store / "sessions" / "2026" / "08" / "05" /
                 ("rollout-2026-08-05T00-00-00-" + id + ".jsonl"), bytes);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store, .locators = {{.kind = "sessions_root", .path = store / "sessions"}}}};
  const auto report = biv::adapters::codex_adapter().collect("/ws/proj", stores);
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
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents, "auth.json") !=
        inventory.caveat_facts.relocated_contents.end());
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents, "config.toml") !=
        inventory.caveat_facts.relocated_contents.end());
  CHECK(std::ranges::find(inventory.caveat_facts.relocated_contents, "sessions") !=
        inventory.caveat_facts.relocated_contents.end());
  CHECK(std::ranges::find(inventory.caveat_facts.notes,
                          std::pair<std::string, std::string>{
                              "picker_gap",
                              "session may not appear in the default picker until first opened by id"}) !=
        inventory.caveat_facts.notes.end());
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
                 child + "\",\"session_id\":\"" + missing_parent +
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

TEST_CASE("X-2 Codex warns when a rollout has session_id but no id") {
  const auto root = make_tmp("session-id-without-id");
  const auto store = root / "codex";
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee7011";
  const auto rollout =
      store / "sessions/2026/07/06/rollout-2026-07-06T11-00-00-019faaaa-"
              "bbbb-7ccc-8ddd-eeeeeeee7011.jsonl";
  write_file(rollout,
             std::string{"{\"timestamp\":\"2026-07-06T11:00:00Z\","
                         "\"type\":\"session_meta\",\"payload\":{"
                         "\"session_id\":\""} +
                 std::string{session_id} +
                 "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};
  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);
  REQUIRE(report);
  CHECK(report->sessions.empty());
  CHECK(std::ranges::any_of(report->warnings, [&](const std::string& warning) {
    return warning == "SessionIdWithoutId:" + rollout.generic_string();
  }));
  fs::remove_all(root);
}

TEST_CASE("X-2 Codex suppresses session_id warnings outside the source root") {
  const auto root = make_tmp("out-of-scope-session-id-without-id");
  const auto store = root / "codex";
  const auto rollout =
      store / "sessions/2026/07/06/rollout-2026-07-06T11-00-00-019faaaa-"
              "bbbb-7ccc-8ddd-eeeeeeee7012.jsonl";
  write_file(rollout,
             "{\"timestamp\":\"2026-07-06T11:00:00Z\","
             "\"type\":\"session_meta\",\"payload\":{"
             "\"session_id\":\"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7012\","
             "\"cwd\":\"/other/project\",\"cli_version\":\"0.142.5\"}}\n");
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{.kind = "sessions_root",
                                               .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::defaults,
      .archived = false}};
  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);
  REQUIRE(report);
  CHECK(report->sessions.empty());
  CHECK_FALSE(std::ranges::any_of(
      report->warnings, [&](const std::string& warning) {
        return warning == "SessionIdWithoutId:" + rollout.generic_string();
      }));
  fs::remove_all(root);
}

TEST_CASE("Codex duplicate-store E-3 warns and picks by declared freshness") {
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
  CHECK(std::ranges::any_of(report->sessions, [](const biv::adapters::SessionRecord& session) {
    return session.original_session_id == kParent;
  }));
  CHECK(std::ranges::any_of(report->warnings, [](const std::string& warning) {
    return warning == "SessionDuplicateStore:" + std::string{kParent};
  }));
}

TEST_CASE("Codex duplicate selection follows every locked A5 freshness key") {
  const auto root = make_tmp("a5-keys");
  const auto db_old_store = root / "db-old";
  const auto db_new_store = root / "db-new";
  const auto db_old = root / "db-old-sqlite";
  const auto db_new = root / "db-new-sqlite";
  const std::string db_id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee8100"};
  write_rollout(db_old_store, db_id, "2026-07-06T01:00:00Z", "db-old");
  write_rollout(db_new_store, db_id, "2026-07-06T01:00:00Z", "db-new");
  write_threads_db(db_old, db_id, 100);
  write_threads_db(db_new, db_id, 200);
  const auto now = fs::file_time_type::clock::now();
  for (const auto& entry : fs::recursive_directory_iterator(db_old_store)) {
    if (entry.is_regular_file()) fs::last_write_time(entry.path(), now);
  }
  for (const auto& entry : fs::recursive_directory_iterator(db_new_store)) {
    if (entry.is_regular_file()) fs::last_write_time(entry.path(), now - std::chrono::hours{1});
  }

  const auto fractional_a = root / "fractional-a";
  const auto fractional_b = root / "fractional-b";
  const std::string fractional_id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee8101"};
  write_rollout(fractional_a, fractional_id, "2026-07-06T01:00:00.1Z", "fractional-a");
  write_rollout(fractional_b, fractional_id, "2026-07-06T01:00:00.10Z", "fractional-b");
  for (const auto& entry : fs::recursive_directory_iterator(fractional_a)) {
    if (entry.is_regular_file()) fs::last_write_time(entry.path(), now - std::chrono::hours{2});
  }
  for (const auto& entry : fs::recursive_directory_iterator(fractional_b)) {
    if (entry.is_regular_file()) fs::last_write_time(entry.path(), now);
  }

  const auto default_store = root / "default";
  const auto config_store = root / "config";
  const std::string tier_id{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee8102"};
  write_rollout(default_store, tier_id, "2026-07-06T01:00:00Z", "default-wins");
  write_rollout(config_store, tier_id, "2026-07-06T01:00:00Z", "config-loses");
  for (const auto& store : {default_store, config_store}) {
    for (const auto& entry : fs::recursive_directory_iterator(store)) {
      if (entry.is_regular_file()) fs::last_write_time(entry.path(), now);
    }
  }

  const std::vector<biv::adapters::Store> stores{
      {.root = db_old_store,
       .locators = {{.kind = "sessions_root", .path = db_old_store / "sessions"},
                    {.kind = "sqlite_home", .path = db_old}},
       .tier = biv::adapters::DiscoveryTier::env},
      {.root = db_new_store,
       .locators = {{.kind = "sessions_root", .path = db_new_store / "sessions"},
                    {.kind = "sqlite_home", .path = db_new}},
       .tier = biv::adapters::DiscoveryTier::env},
      {.root = fractional_a,
       .locators = {{.kind = "sessions_root", .path = fractional_a / "sessions"}},
       .tier = biv::adapters::DiscoveryTier::env},
      {.root = fractional_b,
       .locators = {{.kind = "sessions_root", .path = fractional_b / "sessions"}},
       .tier = biv::adapters::DiscoveryTier::env},
      {.root = default_store,
       .locators = {{.kind = "sessions_root", .path = default_store / "sessions"}},
       .tier = biv::adapters::DiscoveryTier::defaults},
      {.root = config_store,
       .locators = {{.kind = "sessions_root", .path = config_store / "sessions"}},
       .tier = biv::adapters::DiscoveryTier::config}};

  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);

  REQUIRE(report.has_value());
  CHECK(find_session(*report, db_id).agent_version_at_pack == "db-new");
  CHECK(find_session(*report, db_id).provenance.store_root ==
        db_new_store.generic_string());
  CHECK(find_session(*report, fractional_id).agent_version_at_pack ==
        "fractional-b");
  CHECK(find_session(*report, tier_id).agent_version_at_pack == "default-wins");
  fs::remove_all(root);
}

TEST_CASE("Codex sqlite_home config parsing is top-level TOML aware") {
  const auto root = make_tmp("toml");
  const auto store = root / "codex";
  const auto literal_home = root / "literal";
  const auto nested_home = root / "nested";
  const auto env_home = root / "env";
  fs::create_directories(store);
  fs::create_directories(literal_home);
  fs::create_directories(nested_home);
  fs::create_directories(env_home);
  const auto discover = [&](std::optional<std::string> env_sqlite = std::nullopt) {
    return biv::adapters::codex_adapter().discover(biv::adapters::Env{
        .getenv = [&](const std::string_view name) -> std::optional<std::string> {
          if (name == "CODEX_HOME") return store.string();
          if (name == "CODEX_SQLITE_HOME") return env_sqlite;
          return std::nullopt;
        },
        .home = root});
  };

  write_file(store / "config.toml",
             "sqlite_home = '" + literal_home.generic_string() + "' # valid literal\n"
             "[other]\nsqlite_home = \"" + nested_home.generic_string() + "\"\n");
  auto literal = discover();
  REQUIRE(literal.has_value());
  REQUIRE(literal->front().locators.size() == 2);
  CHECK(literal->front().locators.at(1).path == literal_home);

  write_file(store / "config.toml",
             "\"sqlite_home\" = '" + literal_home.generic_string() + "'\n");
  auto quoted_key = discover();
  REQUIRE(quoted_key.has_value());
  REQUIRE(quoted_key->front().locators.size() == 2);
  CHECK(quoted_key->front().locators.at(1).path == literal_home);

  write_file(store / "config.toml",
             "\"sqlite\\u005fhome\" = '" + literal_home.generic_string() +
                 "'\n");
  auto escaped_key = discover();
  REQUIRE(escaped_key.has_value());
  REQUIRE(escaped_key->front().locators.size() == 2);
  CHECK(escaped_key->front().locators.at(1).path == literal_home);

  const auto literal_text = literal_home.generic_string();
  REQUIRE(literal_text.starts_with('/'));
  write_file(store / "config.toml",
             "sqlite_home = \"\\u002f" + literal_text.substr(1) + "\"\n");
  auto unicode_value = discover();
  REQUIRE(unicode_value.has_value());
  REQUIRE(unicode_value->front().locators.size() == 2);
  CHECK(unicode_value->front().locators.at(1).path == literal_home);

  write_file(store / "config.toml",
             "sqlite_home = \"" + literal_home.generic_string() + "\"\r\n");
  auto crlf_basic = discover();
  REQUIRE(crlf_basic.has_value());
  REQUIRE(crlf_basic->front().locators.size() == 2);
  CHECK(crlf_basic->front().locators.at(1).path == literal_home);

  write_file(store / "config.toml",
             "sqlite_home = '" + literal_home.generic_string() + "'\r\n");
  auto crlf_literal = discover();
  REQUIRE(crlf_literal.has_value());
  REQUIRE(crlf_literal->front().locators.size() == 2);
  CHECK(crlf_literal->front().locators.at(1).path == literal_home);

  write_file(store / "config.toml",
             "sqlite_home = '" + literal_home.generic_string() + "'\n"
             "sqlite_home = '" + nested_home.generic_string() + "'\n");
  auto duplicate = discover();
  REQUIRE(duplicate.has_value());
  CHECK(duplicate->front().locators.size() == 1);

  write_file(store / "config.toml", R"(sqlite_home = "/tmp/\uD800")" "\n");
  auto surrogate = discover();
  REQUIRE(surrogate.has_value());
  CHECK(surrogate->front().locators.size() == 1);

  write_file(store / "config.toml",
             R"(sqlite_home = "/tmp/\U00110000")" "\n");
  auto out_of_range = discover();
  REQUIRE(out_of_range.has_value());
  CHECK(out_of_range->front().locators.size() == 1);

  write_file(store / "config.toml",
             "[other]\nsqlite_home = '" + nested_home.generic_string() + "'\n");
  auto nested = discover();
  REQUIRE(nested.has_value());
  CHECK(nested->front().locators.size() == 1);

  write_file(store / "config.toml", "sqlite_home = 42\n");
  auto malformed = discover();
  REQUIRE(malformed.has_value());
  CHECK(malformed->front().locators.size() == 1);

  auto env = discover(env_home.string());
  REQUIRE(env.has_value());
  REQUIRE(env->front().locators.size() == 2);
  CHECK(env->front().locators.at(1).path == env_home);
  fs::remove_all(root);
}

namespace {

constexpr std::string_view kSliceEDecoy = "SLICE_E_CREDENTIAL_DECOY";

class ScopedSliceEEnv {
 public:
  ScopedSliceEEnv(std::string name, const fs::path& value)
      : name_(std::move(name)) {
    if (const char* current = std::getenv(name_.c_str()); current != nullptr) {
      previous_ = std::string{current};
    }
    REQUIRE(::setenv(name_.c_str(), value.c_str(), 1) == 0);
  }
  ~ScopedSliceEEnv() {
    if (previous_) {
      (void)::setenv(name_.c_str(), previous_->c_str(), 1);
    } else {
      (void)::unsetenv(name_.c_str());
    }
  }
  ScopedSliceEEnv(const ScopedSliceEEnv&) = delete;
  ScopedSliceEEnv& operator=(const ScopedSliceEEnv&) = delete;

 private:
  std::string name_;
  std::optional<std::string> previous_;
};

class ScopedPackDiscoveryEnv {
 public:
  explicit ScopedPackDiscoveryEnv(const fs::path& root)
      : home_{"HOME", root / "home"},
        claude_{"CLAUDE_CONFIG_DIR", root / "absent-claude"},
        codex_{"CODEX_HOME", root / "codex"},
        sqlite_{"CODEX_SQLITE_HOME", root / "absent-sqlite"} {}

 private:
  ScopedSliceEEnv home_;
  ScopedSliceEEnv claude_;
  ScopedSliceEEnv codex_;
  ScopedSliceEEnv sqlite_;
};

fs::path slice_e_codex_fixture(std::string_view name) {
  return fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "slice-e" /
         "codex" / name;
}

class ScopedSliceETree {
 public:
  explicit ScopedSliceETree(std::string_view name) : root_(make_tmp(name)) {}
  ScopedSliceETree(const ScopedSliceETree&) = delete;
  ScopedSliceETree& operator=(const ScopedSliceETree&) = delete;
  ~ScopedSliceETree() {
    std::error_code error;
    fs::remove_all(root_, error);
  }

  [[nodiscard]] const fs::path& root() const { return root_; }

 private:
  fs::path root_;
};

biv::expected<biv::adapters::CollectReport> collect_slice_e_fixture(
    std::string_view fixture, ScopedSliceETree& tree) {
  const auto store = tree.root() / "codex";
  copy_fixture_tree(slice_e_codex_fixture(fixture), store);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::env,
      .archived = false}};
  return biv::adapters::codex_adapter().collect("/ws/proj", stores);
}

std::string streamed_record_text(const biv::adapters::SessionRecord& record) {
  std::string text;
  for (const auto& source : record.artifact_sources) {
    REQUIRE(source.stream(
        [&](const std::span<const std::byte> chunk) -> biv::expected<void> {
          for (const auto byte : chunk) {
            text.push_back(static_cast<char>(byte));
          }
          return {};
        }));
  }
  return text;
}

void require_store_roots_under(
    const biv::adapters::CollectReport& report, const fs::path& root) {
  const auto canonical_root = fs::weakly_canonical(root);
  for (const auto& session : report.sessions) {
    const auto relative = fs::weakly_canonical(session.provenance.store_root)
                              .lexically_relative(canonical_root);
    CAPTURE(session.provenance.store_root);
    REQUIRE(!relative.empty());
    REQUIRE(*relative.begin() != "..");
    CHECK(streamed_record_text(session).find(kSliceEDecoy) ==
          std::string::npos);
  }
}

std::vector<std::string> sorted_artifacts(
    const biv::adapters::SessionRecord& session) {
  auto artifacts = session.artifacts;
  std::ranges::sort(artifacts);
  return artifacts;
}

}  // namespace

TEST_CASE("FX-A12-1 Codex carries a three-level descendant chain",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view root_id =
      "019fa120-0000-7000-8000-000000000101";
  constexpr std::string_view parent_id =
      "019fa120-0000-7000-8000-000000000102";
  constexpr std::string_view leaf_id =
      "019fa120-0000-7000-8000-000000000103";
  ScopedSliceETree tree{"slice-e-fx-a12-1"};
  const ScopedPackDiscoveryEnv discovery_env{tree.root()};

  const auto report = collect_slice_e_fixture("three-level-chain-carried", tree);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& root = find_session(*report, root_id);
  CHECK(root.child_ids ==
        std::vector<std::string>{std::string{parent_id}, std::string{leaf_id}});
  CHECK(sorted_artifacts(root) ==
        std::vector<std::string>{
            "agents/codex/019fa120-0000-7000-8000-000000000101.jsonl",
            "agents/codex/019fa120-0000-7000-8000-000000000102.jsonl",
            "agents/codex/019fa120-0000-7000-8000-000000000103.jsonl"});
  CHECK(streamed_record_text(root).find("SLICE_E_LEAF_1") !=
        std::string::npos);
  require_store_roots_under(*report, tree.root());
}

TEST_CASE("FX-A12-3 Codex breaks a rootless cycle and carries its component",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view off_cycle =
      "019fa120-0000-7000-8000-000000000301";
  constexpr std::string_view primary =
      "019fa120-0000-7000-8000-000000000310";
  constexpr std::string_view cycle_peer =
      "019fa120-0000-7000-8000-000000000320";
  ScopedSliceETree tree{"slice-e-fx-a12-3"};
  const ScopedPackDiscoveryEnv discovery_env{tree.root()};

  const auto report =
      collect_slice_e_fixture("rootless-cycle-broken-carried", tree);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& carried = find_session(*report, primary);
  CHECK(carried.child_ids == std::vector<std::string>{
                                  std::string{off_cycle},
                                  std::string{cycle_peer}});
  CHECK(sorted_artifacts(carried) ==
        std::vector<std::string>{
            "agents/codex/019fa120-0000-7000-8000-000000000301.jsonl",
            "agents/codex/019fa120-0000-7000-8000-000000000310.jsonl",
            "agents/codex/019fa120-0000-7000-8000-000000000320.jsonl"});

  // The selected cycle member is the primary, so its declared A -> B edge is
  // the one omitted to make every fixture node's chain terminate at A.
  const auto warning = std::ranges::find_if(
      report->warnings, [](const std::string& value) {
        const auto from = value.find("019fa120-0000-7000-8000-000000000310");
        const auto to = value.find("019fa120-0000-7000-8000-000000000320");
        return from != std::string::npos && to != std::string::npos && from < to;
      });
  REQUIRE(warning != report->warnings.end());

  const std::map<std::string, std::string> retained_parent{
      {std::string{off_cycle}, std::string{primary}},
      {std::string{cycle_peer}, std::string{primary}}};
  for (const auto node : {off_cycle, primary, cycle_peer}) {
    auto cursor = std::string{node};
    for (std::size_t hops = 0; cursor != primary && hops < 3U; ++hops) {
      cursor = retained_parent.at(cursor);
    }
    CHECK(cursor == primary);
  }
  require_store_roots_under(*report, tree.root());
}

TEST_CASE("FX-A12-4 Codex warns when a descendant cannot be carried",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view root_id =
      "019fa120-0000-7000-8000-000000000401";
  constexpr std::string_view child_id =
      "019fa120-0000-7000-8000-000000000402";
  ScopedSliceETree tree{"slice-e-fx-a12-4"};
  const ScopedPackDiscoveryEnv discovery_env{tree.root()};
  const auto store = tree.root() / "codex";
  copy_fixture_tree(slice_e_codex_fixture("uncarryable-descendant-warns"),
                    store);
  const auto child = store / "sessions" / "2026" / "08" / "12" /
                     "rollout-2026-08-12T04-02-00-019fa120-0000-7000-8000-000000000402.jsonl";
  fs::remove(child);
  fs::create_symlink(store / "auth.json", child);
  const std::vector<biv::adapters::Store> stores{biv::adapters::Store{
      .root = store,
      .locators = {biv::adapters::StoreLocator{
          .kind = "sessions_root", .path = store / "sessions"}},
      .tier = biv::adapters::DiscoveryTier::env,
      .archived = false}};

  const auto report =
      biv::adapters::codex_adapter().collect("/ws/proj", stores);

  REQUIRE(report);
  REQUIRE(report->sessions.size() == 1U);
  const auto& root = find_session(*report, root_id);
  CHECK(std::ranges::find(root.child_ids, child_id) == root.child_ids.end());
  CHECK(std::ranges::none_of(root.artifacts, [](const std::string& artifact) {
    return artifact.find("019fa120-0000-7000-8000-000000000402") !=
           std::string::npos;
  }));
  CHECK(std::ranges::any_of(report->warnings, [](const std::string& warning) {
    return warning.find("019fa120-0000-7000-8000-000000000402") !=
           std::string::npos;
  }));
  require_store_roots_under(*report, tree.root());
}
