#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <sys/types.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "adapters/codex/codex.hpp"

namespace {

namespace fs = std::filesystem;

constexpr std::string_view kParent = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001";
constexpr std::string_view kChild = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0002";

fs::path make_tmp(std::string_view name) {
  auto base = fs::temp_directory_path() / ("biv-codex-install-" + std::string{name} + "-" + std::to_string(::getpid()));
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

std::string read_text(const fs::path& path) {
  std::ifstream input{path, std::ios::binary};
  REQUIRE(input);
  return {std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
}

std::uint64_t unix_ms_now() {
  return static_cast<std::uint64_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count());
}

int hex_value(const char value) {
  if (value >= '0' && value <= '9') {
    return value - '0';
  }
  if (value >= 'a' && value <= 'f') {
    return value - 'a' + 10;
  }
  return -1;
}

std::uint64_t uuidv7_ms(std::string_view uuid) {
  std::string hex;
  for (const char value : uuid) {
    if (value != '-') {
      hex.push_back(value);
    }
  }
  REQUIRE(hex.size() == 32);
  std::uint64_t ms = 0;
  for (size_t i = 0; i < 12U; ++i) {
    const auto digit = hex_value(hex.at(i));
    REQUIRE(digit >= 0);
    ms = (ms << 4U) | static_cast<std::uint64_t>(digit);
  }
  return ms;
}

bool uuidv7_shape(std::string_view uuid) {
  return uuid.size() == 36U && uuid.at(8) == '-' && uuid.at(13) == '-' &&
         uuid.at(18) == '-' && uuid.at(23) == '-' && uuid.at(14) == '7' &&
         (uuid.at(19) == '8' || uuid.at(19) == '9' || uuid.at(19) == 'a' ||
          uuid.at(19) == 'b');
}

std::vector<std::string> relative_files(const fs::path& root) {
  std::vector<std::string> files;
  if (!fs::exists(root)) {
    return files;
  }
  for (const auto& entry : fs::recursive_directory_iterator(root)) {
    if (entry.is_regular_file()) {
      files.push_back(fs::relative(entry.path(), root).generic_string());
    }
  }
  std::ranges::sort(files);
  return files;
}

std::string parent_artifact() {
  return "agents/codex/" + std::string{kParent} + ".jsonl";
}

std::string child_artifact() {
  return "agents/codex/" + std::string{kChild} + ".jsonl";
}

biv::manifest::AgentSessionEntry codex_entry(
    std::string primary = std::string{kParent},
    std::string child = std::string{kChild}) {
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "codex";
  entry.agent_version_at_pack = "0.142.5";
  entry.relpath_key = ".";
  entry.original_path = "/ws/proj";
  entry.normalized_path_key = "/ws/proj";
  entry.normalization_scheme = "codex-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::posix;
  entry.provenance = {.store_root = "/source/.codex",
                      .locator = "sessions_root",
                      .discovery_tier = "env"};
  entry.original_session_ids.primary = std::move(primary);
  entry.children = {biv::manifest::SessionChild{
      .original_id = child, .artifacts = {"agents/codex/" + child + ".jsonl"}}};
  entry.artifacts = {"agents/codex/" + entry.original_session_ids.primary +
                     ".jsonl"};
  entry.imported_at = "2026-07-07T00:00:00Z";
  return entry;
}

std::map<std::string, std::vector<std::byte>> codex_members() {
  std::map<std::string, std::vector<std::byte>> members;
  const std::string parent =
      std::string{
          "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":\"session_"
          "meta\",\"payload\":"
          "{\"id\":\""} +
      std::string{kParent} + "\",\"session_id\":\"" + std::string{kParent} +
      "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"
      "{\"timestamp\":\"2026-07-06T01:01:00Z\",\"type\":\"turn_context\","
      "\"payload\":"
      "{\"cwd\":\"/ws/proj\",\"workspace_roots\":[\"/ws/proj\"]}}\n";
  const std::string child =
      std::string{
          "{\"timestamp\":\"2026-07-06T01:05:00Z\",\"type\":\"session_"
          "meta\",\"payload\":"
          "{\"id\":\""} +
      std::string{kChild} + "\",\"session_id\":\"" + std::string{kChild} +
      "\",\"cwd\":\"/ws/proj/sub\",\"cli_version\":\"0.142.5\","
      "\"parent_thread_id\":\"" +
      std::string{kParent} +
      "\",\"source\":{\"subagent\":{\"thread_spawn\":{\"parent_thread_id\":\"" +
      std::string{kParent} +
      "\"}}}}}\n"
      "{\"timestamp\":\"2026-07-06T01:06:00Z\",\"type\":\"turn_context\","
      "\"payload\":"
      "{\"cwd\":\"/ws/proj/sub\",\"workspace_roots\":[\"/ws/proj\"]}}\n";
  members.emplace(parent_artifact(), bytes(parent));
  members.emplace(child_artifact(), bytes(child));
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

TEST_CASE(
    "Codex install rewrites parent and child rollouts with coherent "
    "UUIDv7 filenames") {
  const auto root = make_tmp("install");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  const auto& adapter = biv::adapters::codex_adapter();
  std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};
  const auto before_ms = unix_ms_now();

  const auto installed =
      adapter.install(target, biv::adapters::Consent::yes, records);
  const auto after_ms = unix_ms_now();

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  REQUIRE(installed->sessions.front().content_rewrite.has_value());
  CHECK(*installed->sessions.front().content_rewrite == "pair");
  CHECK(installed->sessions.front().verify.origin_path_hits == 0);
  CHECK(installed->sessions.front().verify.origin_id_hits == 0);
  CHECK(installed->sessions.front().verify.artifacts_checked == 2);
  REQUIRE(installed->id_map.size() == 1);
  const auto& id_map = installed->id_map.front();
  REQUIRE(id_map.children.size() == 1);
  CHECK(uuidv7_shape(id_map.installed_session_id));
  CHECK(uuidv7_shape(id_map.children.front().second));
  CHECK(uuidv7_ms(id_map.installed_session_id) >= before_ms);
  CHECK(uuidv7_ms(id_map.installed_session_id) <= after_ms);
  CHECK(uuidv7_ms(id_map.children.front().second) >= before_ms);
  CHECK(uuidv7_ms(id_map.children.front().second) <= after_ms);
  REQUIRE(installed->activation.size() == 1);
  CHECK(installed->activation.front().command == "codex resume " + id_map.installed_session_id);

  const auto files = relative_files(store);
  REQUIRE(files.size() == 2);
  for (const auto& file : files) {
    CHECK(file.starts_with("sessions/"));
    const auto filename = fs::path{file}.filename().generic_string();
    CHECK(filename.starts_with("rollout-"));
    const bool filename_uses_installed_id = filename.find(id_map.installed_session_id) != std::string::npos ||
                                            filename.find(id_map.children.front().second) != std::string::npos;
    CHECK(filename_uses_installed_id);
    const std::string directory_date = file.substr(9, 4) + "-" + file.substr(14, 2) + "-" + file.substr(17, 2);
    CHECK(directory_date == filename.substr(8, 10));
  }
  CHECK(std::ranges::none_of(files, [](const std::string& file) {
    return file.find("state_5.sqlite") != std::string::npos || file.find("session_index.jsonl") != std::string::npos;
  }));

  const auto parent_file = *std::ranges::find_if(files, [&](const std::string& file) {
    return file.find(id_map.installed_session_id) != std::string::npos;
  });
  const auto child_file = *std::ranges::find_if(files, [&](const std::string& file) {
    return file.find(id_map.children.front().second) != std::string::npos;
  });
  const auto parent_text = read_text(store / parent_file);
  const auto child_text = read_text(store / child_file);
  CHECK(parent_text.find(kParent) == std::string::npos);
  CHECK(parent_text.find(workspace.generic_string()) != std::string::npos);
  CHECK(child_text.find(kParent) == std::string::npos);
  CHECK(child_text.find(kChild) == std::string::npos);
  CHECK(child_text.find(id_map.installed_session_id) != std::string::npos);
  CHECK(child_text.find(id_map.children.front().second) != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("Codex install rewrites escaped values without changing keys or numbers") {
  const auto root = make_tmp("escaped-values");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  members.at(parent_artifact()) = bytes(
      std::string{"{\"/ws/proj\":\"key-must-not-change\",\"timestamp\":"
                  "\"2026-07-06T01:00:00Z\",\"type\":\"session_meta\","
                  "\"payload\":{\"id\":\""} +
      std::string{kParent} + "\",\"session_id\":\"" +
      std::string{kParent} +
      "\",\"cwd\":\"\\/ws\\/\\u0070roj\",\"cli_version\":\"0.142.5\","
      "\"decimal\":0.1,\"integral\":1.0,\"exponent\":1e+03,"
      "\"unsigned\":18446744073709551615}}\n");
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  REQUIRE(result->id_map.size() == 1);
  const auto installed_id = result->id_map.front().installed_session_id;
  const auto files = relative_files(store);
  const auto parent_file = std::ranges::find_if(files, [&](const std::string& file) {
    return file.find(installed_id) != std::string::npos;
  });
  REQUIRE(parent_file != files.end());
  const auto installed = read_text(store / *parent_file);
  CHECK(installed.find("\"/ws/proj\":\"key-must-not-change\"") !=
        std::string::npos);
  CHECK(installed.find(workspace.generic_string()) != std::string::npos);
  CHECK(installed.find("\"decimal\":0.1") != std::string::npos);
  CHECK(installed.find("\"integral\":1.0") != std::string::npos);
  CHECK(installed.find("\"exponent\":1e+03") != std::string::npos);
  CHECK(installed.find("18446744073709551615") != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("Codex install gates host and image-entry capability verdicts") {
  const auto root = make_tmp("capability-gate");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto members = codex_members();
  const auto& adapter = biv::adapters::codex_adapter();
  const std::vector<biv::manifest::AgentSessionEntry> valid_records{
      codex_entry()};

  const auto absent_store = root / "absent-codex";
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
  CHECK(relative_files(absent_store).empty());

  const auto unsupported_store = root / "unsupported-codex";
  fs::create_directories(unsupported_store);
  {
    std::ofstream marker{unsupported_store / "version.json"};
    marker << "{\"version\":\"1.0.0\"}\n";
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
  CHECK_FALSE(fs::exists(unsupported_store / "sessions"));

  const auto unknown_image_store = root / "unknown-image-codex";
  fs::create_directories(unknown_image_store);
  auto unknown_record = codex_entry();
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
  CHECK(relative_files(unknown_image_store).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex install refuses unsafe artifacts for the whole install set") {
  const auto root = make_tmp("refuse");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  auto members = codex_members();
  auto good = codex_entry();
  auto unsafe = codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0101",
                            "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0102");
  unsafe.artifacts = {
      "agents/codex/019faaaa-bbbb-7ccc-8ddd-eeeeeeee9999.jsonl"};
  members.emplace(unsafe.artifacts.front(), bytes("{}\n"));
  std::vector<biv::manifest::AgentSessionEntry> records{good, unsafe};
  auto target = target_for(workspace, store, members);
  const auto& adapter = biv::adapters::codex_adapter();

  const auto result =
      adapter.install(target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  CHECK(std::ranges::all_of(
      result->sessions,
      [](const biv::adapters::InstallSessionOutcome& outcome) {
        return outcome.outcome ==
                   biv::adapters::InstallSessionOutcome::Outcome::failed &&
               outcome.reason.has_value() &&
               *outcome.reason == "containment_refused";
      }));
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "Codex install rejects traversal-shaped artifact ids for the whole set") {
  const auto root = make_tmp("traversal-refuse");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto good = codex_entry();
  auto unsafe =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0101", "../escape");
  members.emplace(unsafe.artifacts.front(), bytes("{}\n"));
  members.emplace(unsafe.children.front().artifacts.front(), bytes("{}\n"));
  const std::vector<biv::manifest::AgentSessionEntry> records{good, unsafe};
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
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
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex install refuses parent symlinks without visible writes") {
  const auto root = make_tmp("parent-symlink");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  const auto outside = root / "outside";
  fs::create_directories(workspace);
  fs::create_directories(store);
  fs::create_directories(outside);
  fs::create_directory_symlink(outside, store / "sessions");
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(outside).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex install refuses nonzero rewrite verification before writing") {
  const auto root = make_tmp("verify-refuse");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto hostile = bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"
                                   "\"id\":\""} +
                       std::string{kParent} + "\",\"session_id\":\"" +
                       std::string{kParent} + "\",\"cwd\":\"/ws/proj\"}}");
  hostile.push_back(static_cast<std::byte>(0xff));
  hostile.push_back(static_cast<std::byte>('\n'));
  members.at(parent_artifact()) = std::move(hostile);
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().verify.origin_path_hits > 0);
  CHECK(result->sessions.front().verify.origin_id_hits > 0);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex install refuses every unverifiable escaped origin line") {
  struct HostileLine {
    std::string name;
    std::vector<std::byte> content;
  };
  std::vector<HostileLine> hostile_lines{
      {"malformed escaped solidus", bytes(R"({"cwd":"\/ws\/proj")")},
      {"malformed Unicode escape", bytes(R"({"cwd":"\u002fws\u002fproj")")},
      {"non-UTF8 escaped solidus", bytes(R"({"cwd":"\/ws\/proj"})")},
      {"non-UTF8 Unicode escape", bytes(R"({"cwd":"\u002fws\u002fproj"})")},
  };
  hostile_lines.at(2).content.push_back(static_cast<std::byte>(0xff));
  hostile_lines.at(3).content.push_back(static_cast<std::byte>(0xff));

  for (const auto& hostile : hostile_lines) {
    DYNAMIC_SECTION(hostile.name) {
      const auto root = make_tmp("unverifiable-escaped");
      const auto workspace = root / "workspace";
      const auto store = root / "codex";
      fs::create_directories(workspace);
      fs::create_directories(store);
      auto members = codex_members();
      members.at(parent_artifact()) = hostile.content;
      auto target = target_for(workspace, store, members);
      const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

      const auto result = biv::adapters::codex_adapter().install(
          target, biv::adapters::Consent::yes, records);

      REQUIRE(result.has_value());
      REQUIRE(result->sessions.size() == 1);
      CHECK(result->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::failed);
      CHECK(result->sessions.front().reason ==
            std::optional<std::string>{"containment_refused"});
      CHECK(result->sessions.front().detail ==
            std::optional<std::string>{"rewrite_verify_failed"});
      CHECK(result->id_map.empty());
      CHECK(result->activation.empty());
      CHECK(relative_files(store).empty());
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Codex install reads the whole set before its first host write") {
  const auto root = make_tmp("read-before-write");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  target.member_read = [&](const std::string_view path)
      -> biv::expected<std::vector<std::byte>> {
    if (path == child_artifact()) {
      return std::unexpected(
          biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
    }
    return members.at(std::string{path});
  };
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE_FALSE(result.has_value());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex rewrite applies pair rewrites and reports non-UTF8 skips") {
  const auto root = make_tmp("rewrite");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  auto members = codex_members();
  members.at(parent_artifact()).push_back(static_cast<std::byte>(0xff));
  auto target = target_for(workspace, store, members);
  const auto entry = codex_entry();
  std::vector<biv::adapters::SessionRecord> records{
      biv::adapters::SessionRecord{
          .agent = "codex",
          .original_session_id = entry.original_session_ids.primary,
          .parent_id = std::nullopt,
          .child_ids = {std::string{kChild}},
          .original_path = entry.original_path,
          .normalized_path_key = entry.normalized_path_key,
          .normalization_scheme = entry.normalization_scheme,
          .path_flavor = entry.path_flavor,
          .provenance = entry.provenance,
          .artifacts = {parent_artifact(), child_artifact()},
          .artifact_sources = {},
          .agent_version_at_pack = entry.agent_version_at_pack,
          .live_at_pack = false}};
  const auto& adapter = biv::adapters::codex_adapter();

  const auto report = adapter.rewrite(records, target);

  REQUIRE(report.has_value());
  CHECK(report->per_artifact_hits.size() == 2);
  CHECK(report->verify.origin_path_hits > 0);
  CHECK(report->verify.origin_id_hits == 0);
  CHECK(report->verify.artifacts_checked == 2);
  CHECK(report->skipped_non_utf8 == 1);
  fs::remove_all(root);
}

TEST_CASE(
    "Codex capabilities use fresh-host fallback, marker, and rollout "
    "cli_version") {
  const auto root = make_tmp("capabilities");
  const auto& adapter = biv::adapters::codex_adapter();
  const biv::adapters::Env env{
      .getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; }, .home = root};
  const biv::adapters::Host host{.home = root, .env = env};

  auto caps = adapter.capabilities(host);
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::absent);

  fs::create_directories(root / ".codex");
  caps = adapter.capabilities(host);
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::unvalidated_host);
  CHECK(caps.per_verb.collect);
  CHECK(caps.per_verb.install);
  CHECK(caps.per_verb.rewrite);

  std::ofstream marker{root / ".codex" / "version.json"};
  marker << "{\"version\":\"0.142.5\"}\n";
  marker.close();
  caps = adapter.capabilities(host);
  CHECK(caps.agent_version == "0.142.5");
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::validated);

  fs::remove(root / ".codex" / "version.json");
  const auto rollout_dir = root / ".codex" / "sessions" / "2026" / "07" / "06";
  fs::create_directories(rollout_dir);
  std::ofstream rollout{rollout_dir / "rollout-2026-07-06T01-00-00-019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001.jsonl"};
  rollout << "{\"type\":\"session_meta\",\"payload\":{\"cli_version\":\"0.142.6\"}}\n";
  rollout.close();
  caps = adapter.capabilities(host);
  CHECK(caps.agent_version == "0.142.6");
  CHECK(caps.verdict == biv::adapters::Capabilities::Verdict::validated);
  fs::remove_all(root);
}
