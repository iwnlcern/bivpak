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

biv::manifest::AgentSessionEntry codex_entry() {
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "codex";
  entry.agent_version_at_pack = "0.142.5";
  entry.relpath_key = ".";
  entry.original_path = "/ws/proj";
  entry.normalized_path_key = "/ws/proj";
  entry.normalization_scheme = "codex-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::posix;
  entry.provenance = {.store_root = "/source/.codex", .locator = "sessions", .discovery_tier = "env"};
  entry.original_session_ids.primary = std::string{kParent};
  entry.children = {biv::manifest::SessionChild{.original_id = std::string{kChild}, .artifacts = {child_artifact()}}};
  entry.artifacts = {parent_artifact()};
  entry.imported_at = "2026-07-07T00:00:00Z";
  return entry;
}

std::map<std::string, std::vector<std::byte>> codex_members() {
  std::map<std::string, std::vector<std::byte>> members;
  const std::string parent = std::string{
                                 "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":\"session_meta\",\"payload\":"
                                 "{\"id\":\""} +
                             std::string{kParent} + "\",\"session_id\":\"" + std::string{kParent} +
                             "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"
                             "{\"timestamp\":\"2026-07-06T01:01:00Z\",\"type\":\"turn_context\",\"payload\":"
                             "{\"cwd\":\"/ws/proj\",\"workspace_roots\":[\"/ws/proj\"]}}\n";
  const std::string child = std::string{
                                "{\"timestamp\":\"2026-07-06T01:05:00Z\",\"type\":\"session_meta\",\"payload\":"
                                "{\"id\":\""} +
                            std::string{kChild} + "\",\"session_id\":\"" + std::string{kChild} +
                            "\",\"cwd\":\"/ws/proj/sub\",\"cli_version\":\"0.142.5\","
                            "\"parent_thread_id\":\"" +
                            std::string{kParent} +
                            "\",\"source\":{\"subagent\":{\"thread_spawn\":{\"parent_thread_id\":\"" +
                            std::string{kParent} +
                            "\"}}}}}\n"
                            "{\"timestamp\":\"2026-07-06T01:06:00Z\",\"type\":\"turn_context\",\"payload\":"
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

TEST_CASE("Codex install rewrites parent and child rollouts with coherent UUIDv7 filenames") {
  const auto root = make_tmp("install");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  const auto& adapter = biv::adapters::codex_adapter();
  std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto installed = adapter.install(target, biv::adapters::Consent::yes, records);

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1);
  CHECK(installed->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(installed->sessions.front().verify.origin_path_hits == 0);
  CHECK(installed->sessions.front().verify.origin_id_hits == 0);
  REQUIRE(installed->id_map.size() == 1);
  const auto& id_map = installed->id_map.front();
  REQUIRE(id_map.children.size() == 1);
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

TEST_CASE("Codex capabilities use fresh-host fallback, marker, and rollout cli_version") {
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
