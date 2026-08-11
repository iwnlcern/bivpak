#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "adapters/claude_code/claude_code.hpp"
#include "adapters/codex/codex.hpp"
#include "adapters/rewrite_common.hpp"
#include "core/container/tar_reader.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"
#include "core/open/sessions.hpp"
#include "core/pack/pack.hpp"
#include "core/report/envelope.hpp"

namespace {

struct ArchiveMember {
  biv::container::MemberMeta meta;
  std::vector<std::byte> data;
  std::string extent;
};

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() /
              ("biv-pack-" + std::string{name} + "-" + std::to_string(::getpid()));
  std::filesystem::remove_all(base);
  std::filesystem::create_directories(base);
  return std::filesystem::canonical(base);
}

void write_file(const std::filesystem::path& path, std::string_view content) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  out << content;
}

std::vector<std::byte> read_file_bytes(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  REQUIRE(in);
  std::string bytes{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
  std::vector<std::byte> out(bytes.size());
  for (size_t i = 0; i < bytes.size(); ++i) {
    out[i] = static_cast<std::byte>(bytes[i]);
  }
  return out;
}

std::span<const std::byte> as_span(const std::vector<std::byte>& bytes) {
  return std::span<const std::byte>{bytes.data(), bytes.size()};
}

std::map<std::string, std::vector<std::byte>> snapshot_files(const std::filesystem::path& root) {
  std::map<std::string, std::vector<std::byte>> snapshot;
  for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    snapshot.emplace(std::filesystem::relative(entry.path(), root).generic_string(), read_file_bytes(entry.path()));
  }
  return snapshot;
}

std::vector<ArchiveMember> read_archive(const std::filesystem::path& path) {
  auto compressed = read_file_bytes(path);
  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return as_span(compressed);
  }};
  biv::container::TarReader reader{source};

  std::vector<ArchiveMember> members;
  while (true) {
    auto next = reader.next();
    REQUIRE(next.has_value());
    if (!*next) {
      break;
    }
    ArchiveMember member{.meta = next->value().meta, .data = {}, .extent = {}};
    std::array<std::byte, 32> buffer {};
    while (true) {
      auto n = reader.read_data(buffer);
      REQUIRE(n.has_value());
      if (*n == 0U) {
        break;
      }
      member.data.insert(member.data.end(), buffer.begin(), buffer.begin() + static_cast<std::ptrdiff_t>(*n));
    }
    member.extent = reader.extent_sha256_hex();
    members.push_back(std::move(member));
  }
  return members;
}

std::string byte_string(std::span<const std::byte> bytes) {
  std::string out;
  out.reserve(bytes.size());
  for (const auto byte : bytes) {
    out.push_back(static_cast<char>(byte));
  }
  return out;
}

void copy_fixture_tree_with_workspace(const std::filesystem::path& from,
                                      const std::filesystem::path& to,
                                      const std::filesystem::path& workspace) {
  const auto workspace_text = workspace.generic_string();
  for (const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
    const auto rel = std::filesystem::relative(entry.path(), from);
    const auto dest = to / rel;
    if (entry.is_directory()) {
      std::filesystem::create_directories(dest);
      continue;
    }
    if (!entry.is_regular_file()) {
      continue;
    }
    std::string text = byte_string(as_span(read_file_bytes(entry.path())));
    size_t pos = 0;
    while ((pos = text.find("/ws/proj", pos)) != std::string::npos) {
      text.replace(pos, 8, workspace_text);
      pos += workspace_text.size();
    }
    write_file(dest, text);
  }
}

class ScopedEnv {
 public:
  ScopedEnv(std::string name, std::optional<std::string> value)
      : name_{std::move(name)} {
    if (const char* old = std::getenv(name_.c_str()); old != nullptr) {
      old_value_ = std::string{old};
    }
    if (value) {
      setenv(name_.c_str(), value->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }

  ~ScopedEnv() {
    if (old_value_.has_value()) {
      setenv(name_.c_str(), old_value_->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }

  ScopedEnv(const ScopedEnv&) = delete;
  ScopedEnv& operator=(const ScopedEnv&) = delete;
  ScopedEnv(ScopedEnv&&) = delete;
  ScopedEnv& operator=(ScopedEnv&&) = delete;

 private:
  std::string name_;
  std::optional<std::string> old_value_;
};

struct PackDiscoveryEnvValues {
  std::optional<std::string> home;
  std::optional<std::string> claude_config_dir;
  std::optional<std::string> codex_home;
  std::optional<std::string> codex_sqlite_home;
};

PackDiscoveryEnvValues isolated_pack_discovery_env(
    const std::filesystem::path& root) {
  return {
      .home = (root / "home").string(),
      .claude_config_dir = (root / "claude").string(),
      .codex_home = (root / "codex").string(),
      .codex_sqlite_home = (root / "codex-sqlite").string(),
  };
}

class ScopedPackDiscoveryEnv {
 public:
  explicit ScopedPackDiscoveryEnv(const PackDiscoveryEnvValues& values)
      : home_{"HOME", values.home},
        claude_config_dir_{"CLAUDE_CONFIG_DIR", values.claude_config_dir},
        codex_home_{"CODEX_HOME", values.codex_home},
        codex_sqlite_home_{"CODEX_SQLITE_HOME",
                           values.codex_sqlite_home} {}

 private:
  ScopedEnv home_;
  ScopedEnv claude_config_dir_;
  ScopedEnv codex_home_;
  ScopedEnv codex_sqlite_home_;
};

void require_store_roots_under(const biv::pack::PackReport& report,
                               const std::filesystem::path& root) {
  const auto canonical_root = std::filesystem::weakly_canonical(root);
  for (const auto& session : report.agent_sessions) {
    const auto store_root = std::filesystem::weakly_canonical(
        std::filesystem::path{session.provenance.store_root});
    const auto relative = store_root.lexically_relative(canonical_root);
    CAPTURE(store_root, canonical_root, relative);
    REQUIRE_FALSE(relative.empty());
    REQUIRE(relative != ".");
    REQUIRE_FALSE(relative.is_absolute());
    REQUIRE(*relative.begin() != "..");
  }
}

std::vector<std::byte> text_bytes(const std::string_view text) {
  std::vector<std::byte> out;
  out.reserve(text.size());
  for (const char value : text) {
    out.push_back(static_cast<std::byte>(value));
  }
  return out;
}

biv::adapters::Capabilities round_trip_capabilities(
    const std::string_view agent) {
  return biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{agent == "codex" ? "0.144.1" : "2.1.211"},
      false, agent == "codex",
      {.collect = true, .install = true, .rewrite = true});
}

struct StagedPackImage {
  biv::manifest::Manifest manifest;
  std::map<std::string, std::vector<std::byte>> members;
  std::vector<biv::adapters::IdMapEntry> staged_id_map;
};

StagedPackImage stage_then_pack(
    const std::filesystem::path& root,
    const biv::adapters::AgentAdapter& adapter,
    const std::span<const biv::manifest::AgentSessionEntry> records,
    std::map<std::string, std::vector<std::byte>>& input_members) {
  REQUIRE_FALSE(records.empty());
  const auto staging_workspace = root / "staging-workspace";
  const auto staging_store = root / "staging-host-store";
  std::filesystem::create_directories(staging_workspace);
  std::filesystem::create_directories(staging_store);

  biv::manifest::Manifest input_manifest;
  input_manifest.agent_sessions.assign(records.begin(), records.end());
  size_t child_count = 0U;
  for (const auto& record : records) {
    REQUIRE(record.agent == records.front().agent);
    child_count += record.children.size();
  }
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(biv::core_sessions::AgentPreview{
      .agent = records.front().agent,
      .parent_count = records.size(),
      .child_count = child_count,
      .known_adapter = true,
      .entry_schema_skipped = false,
      .caps = round_trip_capabilities(records.front().agent),
      .store = biv::adapters::Store{
          .root = staging_store,
          .locators = {},
          .tier = biv::adapters::DiscoveryTier::env,
          .archived = false},
      .adapter = &adapter});
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back(records.front().agent, false);
  const biv::adapters::MemberRead input_reader =
      [&](const std::string_view path)
      -> biv::expected<std::vector<std::byte>> {
    const auto found = input_members.find(std::string{path});
    if (found == input_members.end()) {
      return std::unexpected(
          biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
    }
    return found->second;
  };

  const auto staged = biv::core_sessions::run_session_leg(
      preview, consent, input_manifest, staging_workspace, input_reader);

  REQUIRE(staged);
  REQUIRE(staged->rows.size() == records.size());
  for (const auto& row : staged->rows) {
    CHECK(row.row ==
          biv::core_sessions::SessionRowReport::Row::sessions_staged);
  }
  REQUIRE(staged->id_map.size() == records.size());
  REQUIRE(std::filesystem::is_regular_file(
      staging_workspace / ".biv/agents/manifest.json"));

  write_file(staging_workspace / "work.txt", "workspace\n");
  const ScopedEnv codex_home{"CODEX_HOME",
                             (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "absent-home").string()};

  const auto packed = biv::pack::pack(staging_workspace);

  REQUIRE(packed);
  const auto archive = read_archive(root / "staging-workspace.bvpk");
  const auto manifest_member = std::ranges::find(
      archive, std::string_view{"manifest.json"},
      [](const ArchiveMember& member) {
        return std::string_view{member.meta.path};
      });
  REQUIRE(manifest_member != archive.end());
  auto parsed = biv::manifest::parse(as_span(manifest_member->data));
  REQUIRE(parsed);
  std::map<std::string, std::vector<std::byte>> members;
  for (const auto& member : archive) {
    members.emplace(member.meta.path, member.data);
  }
  return StagedPackImage{.manifest = std::move(*parsed),
                         .members = std::move(members),
                         .staged_id_map = staged->id_map};
}

StagedPackImage stage_then_pack(
    const std::filesystem::path& root,
    const biv::adapters::AgentAdapter& adapter,
    const biv::manifest::AgentSessionEntry& record,
    std::map<std::string, std::vector<std::byte>>& input_members) {
  return stage_then_pack(
      root, adapter,
      std::span<const biv::manifest::AgentSessionEntry>{&record, 1U},
      input_members);
}

biv::manifest::AgentSessionEntry round_trip_record(
    const std::string_view agent, const std::string_view session_id,
    const std::filesystem::path& original_workspace) {
  const bool codex = agent == "codex";
  return biv::manifest::AgentSessionEntry{
      .agent = std::string{agent},
      .agent_version_at_pack = codex ? "0.144.1" : "2.1.207",
      .relpath_key = ".",
      .original_path = original_workspace.generic_string(),
      .normalized_path_key = original_workspace.generic_string(),
      .normalization_scheme = codex ? "codex-cwd/v1" : "claude-cwd/v1",
      .path_flavor = biv::manifest::PathFlavor::posix,
      .provenance = {.store_root = codex ? "/source/.codex"
                                           : "/source/.claude",
                     .locator = "sessions_root",
                     .discovery_tier = "env",
                     .archived = false},
      .original_session_ids = {.primary = std::string{session_id},
                               .parent = std::nullopt,
                               .parent_in_image = std::nullopt},
      .children = {},
      .artifacts = {"agents/" + std::string{agent} + "/" +
                    std::string{session_id} + ".jsonl"},
      .live_at_pack = false,
      .imported_at = "2026-08-10T00:00:00Z",
      .entry_schema = 1};
}

biv::manifest::AgentSessionEntry windows_round_trip_record(
    const std::string_view agent, const std::string_view session_id,
    const std::string_view original_path) {
  const bool codex = agent == "codex";
  const std::string artifact =
      "agents/" + std::string{agent} + "/" + std::string{session_id} +
      ".jsonl";
  return biv::manifest::AgentSessionEntry{
      .agent = std::string{agent},
      .agent_version_at_pack = codex ? "0.144.1" : "2.1.211",
      .relpath_key = ".",
      .original_path = std::string{original_path},
      .normalized_path_key =
          biv::adapters::rewrite::normalized_path_key(original_path),
      .normalization_scheme = codex ? "codex-cwd/v1" : "claude-cwd/v1",
      .path_flavor = biv::manifest::PathFlavor::windows,
      .provenance = {.store_root = codex ? "C:\\Users\\Me\\.codex"
                                         : "C:\\Users\\Me\\.claude",
                     .locator = "sessions_root",
                     .discovery_tier = "env",
                     .archived = false},
      .original_session_ids = {.primary = std::string{session_id},
                               .parent = std::nullopt,
                               .parent_in_image = std::nullopt},
      .children = {},
      .artifacts = {artifact},
      .live_at_pack = false,
      .imported_at = "2026-08-10T00:00:00Z",
      .entry_schema = 1};
}

std::map<std::string, std::vector<std::byte>> windows_round_trip_members(
    const biv::manifest::AgentSessionEntry& record) {
  REQUIRE(record.artifacts.size() == 1U);
  const bool codex = record.agent == "codex";
  const auto& session_id = record.original_session_ids.primary;
  auto artifact_path = record.original_path;
  std::ranges::replace(artifact_path, '\\', '/');
  const std::string text = codex
      ? std::string{"{\"timestamp\":\"2026-08-10T00:00:00Z\","}
            + "\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
            session_id + "\",\"session_id\":\"" + session_id +
            "\",\"cwd\":\"" + artifact_path +
            "\",\"cli_version\":\"0.144.1\"}}\n"
      : std::string{"{\"type\":\"user\",\"cwd\":\""} +
            artifact_path + "\",\"sessionId\":\"" + session_id +
            "\",\"version\":\"2.1.211\"}\n";
  return {{record.artifacts.front(), text_bytes(text)}};
}

std::string combined_file_text(const std::filesystem::path& root) {
  std::string combined;
  for (const auto& [path, content] : snapshot_files(root)) {
    static_cast<void>(path);
    combined += byte_string(as_span(content));
  }
  return combined;
}

void write_agent_session(const std::filesystem::path& store,
                         const std::filesystem::path& source,
                         const std::string_view agent,
                         const std::string_view session_id,
                         const std::string_view version) {
  if (agent == "codex") {
    write_file(store / "sessions" / "2026" / "08" / "06" /
                   ("rollout-2026-08-06T01-00-00-" +
                    std::string{session_id} + ".jsonl"),
               "{\"timestamp\":\"2026-08-06T01:00:00Z\",\"type\":"
               "\"session_meta\",\"payload\":{\"id\":\"" +
                   std::string{session_id} + "\",\"session_id\":\"" +
                   std::string{session_id} + "\",\"cwd\":\"" +
                   source.generic_string() + "\",\"cli_version\":\"" +
                   std::string{version} + "\"}}\n");
    return;
  }
  write_file(store / "projects" / "project" /
                 (std::string{session_id} + ".jsonl"),
             "{\"type\":\"user\",\"cwd\":\"" +
                 source.generic_string() + "\",\"sessionId\":\"" +
                 std::string{session_id} + "\",\"version\":\"" +
                 std::string{version} + "\"}\n");
}

}  // namespace

TEST_CASE("pack captures packer_home per HOME shape") {
  {
    // A valid store outside the pinned temp universe is unreachable even when
    // the runner's ambient HOME points directly at it.
    const auto root = make_tmp("ambient-home-guard");
    const auto source = root / "proj";
    const auto decoy_home = make_tmp("ambient-home-decoy");
    const auto decoy_store = decoy_home / ".codex";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    write_agent_session(decoy_store, source, "codex",
                        "019faaaa-bbbb-7ccc-8ddd-eeeeeeee8800", "0.142.5");
    const ScopedEnv ambient_home{"HOME", decoy_home.string()};
    const ScopedPackDiscoveryEnv discovery_env{
        isolated_pack_discovery_env(root)};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
    require_store_roots_under(*report, root);
    CHECK(report->agent_sessions.empty());
    CHECK(std::ranges::none_of(
        report->agent_sessions, [&](const auto& session) {
          return session.provenance.store_root == decoy_store.generic_string();
        }));
    std::filesystem::remove_all(root);
    std::filesystem::remove_all(decoy_home);
  }

  struct Row {
    std::string_view label;
    std::optional<std::string> home;
    bool use_temp_home;
    std::optional<biv::manifest::PathFlavor> expected_flavor;
  };
  const auto rows = std::array{
      Row{.label = "absolute-posix", .home = std::nullopt,
          .use_temp_home = true,
          .expected_flavor = biv::manifest::PathFlavor::posix},
      Row{.label = "unset", .home = std::nullopt, .use_temp_home = false,
          .expected_flavor = std::nullopt},
      Row{.label = "empty", .home = "", .use_temp_home = false,
          .expected_flavor = std::nullopt},
      Row{.label = "relative", .home = "relative/home", .use_temp_home = false,
          .expected_flavor = std::nullopt},
      Row{.label = "degenerate-root", .home = "/", .use_temp_home = false,
          .expected_flavor = std::nullopt},
      Row{.label = "wsl-mount", .home = "/mnt/c/Users/x",
          .use_temp_home = false,
          .expected_flavor = biv::manifest::PathFlavor::wsl},
      Row{.label = "windows-drive", .home = "C:/Users/x",
          .use_temp_home = false,
          .expected_flavor = biv::manifest::PathFlavor::windows},
  };
  for (const auto& row : rows) {
    CAPTURE(row.label);
    const auto root = make_tmp("packer-home-" + std::string{row.label});
    const auto source = root / "proj";
    const auto codex_store = root / "codex";
    const auto claude_store = root / "claude";
    std::filesystem::create_directories(source);
    std::filesystem::create_directories(codex_store);
    std::filesystem::create_directories(claude_store);
    write_file(source / "work.txt", "workspace");
    const auto home_value = row.use_temp_home
                                ? std::optional<std::string>{(root / "home").string()}
                                : row.home;
    auto env_values = isolated_pack_discovery_env(root);
    env_values.home = home_value;
    env_values.codex_home = codex_store.string();
    env_values.claude_config_dir = claude_store.string();
    const ScopedPackDiscoveryEnv discovery_env{env_values};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
    require_store_roots_under(*report, root);
    CHECK(report->agent_sessions.empty());
    const auto members = read_archive(root / "proj.bvpk");
    auto manifest = biv::manifest::parse(as_span(members.at(0).data));
    REQUIRE(manifest.has_value());
    const auto expected = row.expected_flavor
                              ? std::optional<biv::manifest::PackerHome>{
                                    biv::manifest::PackerHome{
                                        .path = *home_value,
                                        .flavor = *row.expected_flavor}}
                              : std::nullopt;
    REQUIRE(manifest->packer_home == expected);
    REQUIRE(manifest->source_path_flavor == biv::manifest::PathFlavor::posix);
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("Task 6 pack omits known below-minimum sessions and reports every floor fact") {
  struct Case {
    std::string_view agent;
    std::string_view session_id;
    std::string_view version;
    std::string_view minimum;
  };
  for (const auto& test : std::array{
           Case{"codex", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee6100", "0.61.0",
                "0.142"},
           Case{"claude-code", "aaaaaaaa-1111-4000-8000-000000000205",
                "2.0.5", "2.1"},
       }) {
    CAPTURE(test.agent);
    const auto root = make_tmp("below-min-" + std::string{test.agent});
    const auto source = root / "proj";
    const auto codex_store = root / "codex";
    const auto claude_store = root / "claude";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    write_agent_session(test.agent == "codex" ? codex_store : claude_store,
                        source, test.agent, test.session_id, test.version);
    auto env_values = isolated_pack_discovery_env(root);
    env_values.codex_home = codex_store.string();
    env_values.claude_config_dir = claude_store.string();
    const ScopedPackDiscoveryEnv discovery_env{env_values};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
    require_store_roots_under(*report, root);
    // FX-VF-P1/*/not-in-image
    CHECK(report->agent_sessions.empty());
    CHECK(report->agent_sessions_summary.empty());
    const auto members = read_archive(root / "proj.bvpk");
    CHECK(std::ranges::none_of(members, [&](const ArchiveMember& member) {
      return member.meta.path.starts_with("agents/" + std::string{test.agent} +
                                          "/");
    }));
    auto manifest = biv::manifest::parse(as_span(members.at(0).data));
    REQUIRE(manifest.has_value());
    CHECK(manifest->agent_sessions.empty());

    const auto warning = std::ranges::find_if(
        report->warnings, [&](const biv::pack::Warning& candidate) {
          return candidate.kind == "SessionBelowMinimumOmitted" &&
                 candidate.path == test.session_id;
        });
    // FX-VF-P1/*/skip-report-default-visible and report-names-{version,min,reason}
    REQUIRE(warning != report->warnings.end());
    const auto visible = biv::pack::warning_text(*warning);
    CHECK(visible.find(test.session_id) != std::string::npos);
    CHECK(visible.find(test.version) != std::string::npos);
    CHECK(visible.find(test.minimum) != std::string::npos);
    CHECK(visible.find("below-minimum") != std::string::npos);
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("Task 6 pack keeps minimum and forward-known sessions at entry schema one") {
  struct Case {
    std::string_view key;
    std::string_view agent;
    std::string_view session_id;
    std::string_view version;
  };
  for (const auto& test : std::array{
           Case{"P2", "codex", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1425",
                "0.142.5"},
           Case{"P2", "claude-code",
                "aaaaaaaa-1111-4000-8000-000000000217", "2.1.207"},
           Case{"P4", "codex", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee3000",
                "0.300.0"},
           Case{"P4", "claude-code",
                "aaaaaaaa-1111-4000-8000-000000000290", "2.9.0"},
           Case{"P3", "codex", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0003",
                "unknown"},
       }) {
    CAPTURE(test.key, test.agent);
    const auto root =
        make_tmp(std::string{test.key} + "-schema-one-" + std::string{test.agent});
    const auto source = root / "proj";
    const auto codex_store = root / "codex";
    const auto claude_store = root / "claude";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    write_agent_session(test.agent == "codex" ? codex_store : claude_store,
                        source, test.agent, test.session_id, test.version);
    auto env_values = isolated_pack_discovery_env(root);
    env_values.codex_home = codex_store.string();
    env_values.claude_config_dir = claude_store.string();
    const ScopedPackDiscoveryEnv discovery_env{env_values};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
    require_store_roots_under(*report, root);
    REQUIRE(report->agent_sessions.size() == 1);
    CHECK(report->agent_sessions.front().agent_version_at_pack == test.version);
    CHECK(report->agent_sessions.front().entry_schema == 1);
    const auto members = read_archive(root / "proj.bvpk");
    auto manifest = biv::manifest::parse(as_span(members.at(0).data));
    REQUIRE(manifest.has_value());
    REQUIRE(manifest->agent_sessions.size() == 1);
    CHECK(manifest->agent_sessions.front().entry_schema == 1);
    CHECK(std::ranges::any_of(members, [&](const ArchiveMember& member) {
      return member.meta.path.starts_with("agents/" + std::string{test.agent} +
                                          "/");
    }));
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("pack writes manifest, checksums, and payload extents") {
  const auto root = make_tmp("happy");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / ".bivignore", "target/\n");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");
  std::filesystem::create_directories(source / "target");
  write_file(source / "target" / "skip.txt", "skip");
  std::filesystem::create_symlink("a.txt", source / "link.txt");
  const ScopedPackDiscoveryEnv discovery_env{
      isolated_pack_discovery_env(root)};

  auto report = biv::pack::pack(source);
  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  CHECK(report->image_path == (root / "sample.bvpk").generic_string());
  CHECK(std::filesystem::exists(root / "sample.bvpk"));
  CHECK_FALSE(std::filesystem::exists(source / "sample.bvpk"));
  REQUIRE(report->advisories.size() == 1);
  CHECK(report->advisories[0].kind == "prune-summary");
  CHECK(report->advisories[0].entries[0].relpath == "target");

  const auto members = read_archive(root / "sample.bvpk");
  REQUIRE(members.size() == 7);
  CHECK(members[0].meta.path == "manifest.json");
  CHECK(members[1].meta.path == "checksums.json");
  CHECK(members[2].meta.path == "payload/.bivignore");
  CHECK(members[3].meta.path == "payload/a.txt");
  CHECK(members[4].meta.path == "payload/dir");
  CHECK(members[5].meta.path == "payload/dir/b.txt");
  CHECK(members[6].meta.path == "payload/link.txt");
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return member.meta.path.find(".bvpk") != std::string::npos;
  }));

  auto manifest = biv::manifest::parse(as_span(members[0].data));
  REQUIRE(manifest.has_value());
  CHECK(manifest->format_version == 1);
  CHECK(manifest->bivignore.source == "file");

  auto checksums = biv::manifest::parse_checksums(as_span(members[1].data));
  REQUIRE(checksums.has_value());
  for (const auto& member : members) {
    if (!member.meta.path.starts_with("payload/")) {
      continue;
    }
    REQUIRE(checksums->entries.contains(member.meta.path));
    CHECK(checksums->entries.at(member.meta.path) == member.extent);
  }
  CHECK(byte_string(as_span(members[3].data)) == "alpha");

  std::filesystem::remove_all(root);
}

TEST_CASE("pack refuses stale partial and reports facts") {
  const auto root = make_tmp("partial");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  write_file(source / "a.txt", "alpha");
  write_file(root / "sample.bvpk.partial", "stale");
  const ScopedPackDiscoveryEnv discovery_env{
      isolated_pack_discovery_env(root)};

  auto report = biv::pack::pack(source);
  REQUIRE_FALSE(report.has_value());
  CHECK(report.error().kind == biv::ErrKind::PartialPresent);
  CHECK(report.error().facts.at("partial_path") == (root / "sample.bvpk.partial").generic_string());
  CHECK(std::filesystem::exists(root / "sample.bvpk.partial"));
  std::filesystem::remove_all(root);
}

TEST_CASE("pack refuses repo-bearing source") {
  const auto root = make_tmp("repo");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / ".git");
  const ScopedPackDiscoveryEnv discovery_env{
      isolated_pack_discovery_env(root)};
  auto report = biv::pack::pack(source);
  REQUIRE_FALSE(report.has_value());
  CHECK(report.error().kind == biv::ErrKind::RepoDiscoveredUnsupported);
  CHECK_FALSE(std::filesystem::exists(root / "sample.bvpk"));
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "pack collects Claude adapter artifacts into agents members and "
    "manifest sessions") {
  const auto root = make_tmp("claude");
  const auto source = root / "proj";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto store = root / "claude_store";
  copy_fixture_tree_with_workspace(std::filesystem::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "claude_store",
                                   store,
                                   source);
  const auto source_before = snapshot_files(source);
  const auto store_before = snapshot_files(store);
  auto env_values = isolated_pack_discovery_env(root);
  env_values.claude_config_dir = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  REQUIRE(report->agent_sessions.size() == 1);
  CHECK(report->agent_sessions.front().agent == "claude-code");
  REQUIRE(report->agent_sessions_summary.size() == 1);
  CHECK(report->agent_sessions_summary.front().agent == "claude-code");
  CHECK(report->agent_sessions_summary.front().session_count == 1);
  CHECK(std::ranges::any_of(report->warnings, [](const biv::pack::Warning& warning) {
    return warning.kind == "SessionLiveAtPack" &&
           warning.path == "aaaaaaaa-1111-4000-8000-000000000001";
  }));
  const auto members = read_archive(root / "proj.bvpk");
  CHECK(std::ranges::any_of(members, [](const ArchiveMember& member) {
    return member.meta.path == "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001.jsonl";
  }));
  CHECK(std::ranges::any_of(members, [](const ArchiveMember& member) {
    return member.meta.path ==
           "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/agent-a01.jsonl";
  }));
  CHECK(std::ranges::any_of(members, [](const ArchiveMember& member) {
    return member.meta.path ==
           "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/agent-a01.meta.json";
  }));

  auto manifest = biv::manifest::parse(as_span(members.at(0).data));
  REQUIRE(manifest.has_value());
  REQUIRE(manifest->agent_sessions.size() == 1);
  CHECK(manifest->agent_sessions.front().agent == "claude-code");
  CHECK(manifest->agent_sessions.front().artifacts ==
        std::vector<std::string>{"agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001.jsonl"});
  REQUIRE(manifest->agent_sessions.front().children.size() == 1);
  CHECK(manifest->agent_sessions.front().children.front().original_id == "agent-a01");

  auto checksums = biv::manifest::parse_checksums(as_span(members.at(1).data));
  REQUIRE(checksums.has_value());
  for (const auto& member : members) {
    if (!member.meta.path.starts_with("agents/")) {
      continue;
    }
    REQUIRE(checksums->entries.contains(member.meta.path));
    CHECK(checksums->entries.at(member.meta.path) == member.extent);
  }
  CHECK(snapshot_files(source) == source_before);
  CHECK(snapshot_files(store) == store_before);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "T-3 pack attributes every same-stem nested Claude workflow artifact") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000001";
  const auto root = make_tmp("claude-same-stem-workflows");
  const auto source = root / "proj";
  const auto store = root / "claude_store";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  copy_fixture_tree_with_workspace(
      std::filesystem::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
          "claude_store",
      store, source);
  const auto session_root =
      store / "projects/-ws-proj" / std::string{session_id};
  const auto transcript = std::string{"{\"type\":\"assistant\",\"sessionId\":\""} +
                          std::string{session_id} +
                          "\",\"agentId\":\"agent-a01\"}\n";
  write_file(session_root / "subagents/workflows/wf-a/agent-a01.jsonl",
             transcript);
  write_file(session_root / "subagents/workflows/wf-b/agent-a01.jsonl",
             transcript);
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report);
  REQUIRE(report->agent_sessions.size() == 1U);
  REQUIRE(report->agent_sessions.front().children.size() == 1U);
  const auto& child = report->agent_sessions.front().children.front();
  CHECK(child.original_id == "agent-a01");
  CHECK(child.artifacts ==
        std::vector<std::string>{
            "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/agent-a01.jsonl",
            "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/agent-a01.meta.json",
            "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/workflows/wf-a/agent-a01.jsonl",
            "agents/claude-code/aaaaaaaa-1111-4000-8000-000000000001/subagents/workflows/wf-b/agent-a01.jsonl"});
  std::filesystem::remove_all(root);
}

TEST_CASE("pack rejects duplicate adapter members before publishing an image") {
  const auto root = make_tmp("claude-dedupe");
  const auto source = root / "proj";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto store = root / "claude_store";
  copy_fixture_tree_with_workspace(std::filesystem::path{BIV_SOURCE_DIR} /
                                       "tests" / "fixtures" / "claude_store",
                                   store, source);
  const auto session_id = std::string{"aaaaaaaa-1111-4000-8000-000000000001"};
  write_file(store / "projects" / "-ws-proj" / "duplicate.jsonl",
             "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                 "\",\"sessionId\":\"" + session_id +
                 "\",\"version\":\"2.1.202\"}\n");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.claude_config_dir = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  const auto report = biv::pack::pack(source);

  REQUIRE_FALSE(report.has_value());
  CHECK_FALSE(std::filesystem::exists(root / "proj.bvpk"));
  std::filesystem::remove_all(root);
}

TEST_CASE("pack rejects traversal and control-character session ids atomically") {
  for (const auto& [name, hostile_id] :
       std::vector<std::pair<std::string, std::string>>{
           {"traversal", "../escape"},
           {"backslash", R"(bad\\id)"},
           {"drive", "C:escape"},
           {"empty", ""},
           {"control", R"(bad\u0001id)"}}) {
    const auto root = make_tmp("claude-id-" + name);
    const auto source = root / "proj";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    const auto store = root / "claude_store";
    write_file(store / "projects" / "project" / "safe.jsonl",
               "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                   "\",\"sessionId\":\"" + hostile_id +
                   "\",\"version\":\"2.1.202\"}\n");
    auto env_values = isolated_pack_discovery_env(root);
    env_values.claude_config_dir = store.string();
    const ScopedPackDiscoveryEnv discovery_env{env_values};

    const auto report = biv::pack::pack(source);

    REQUIRE_FALSE(report.has_value());
    CHECK_FALSE(std::filesystem::exists(root / "proj.bvpk"));
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("pack rejects control and DEL bytes in collected artifact members") {
  for (const auto hostile : {static_cast<char>(0x01), static_cast<char>(0x7f)}) {
    const auto root = make_tmp("claude-member-control-" +
                               std::to_string(static_cast<unsigned char>(hostile)));
    const auto source = root / "proj";
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    const auto store = root / "claude_store";
    copy_fixture_tree_with_workspace(std::filesystem::path{BIV_SOURCE_DIR} /
                                         "tests" / "fixtures" / "claude_store",
                                     store, source);
    const auto hostile_name = std::string{"bad"} + hostile + ".jsonl";
    write_file(store / "projects" / "-ws-proj" /
                   "aaaaaaaa-1111-4000-8000-000000000001" / hostile_name,
               "{\"message\":\"must-not-pack\"}\n");
    auto env_values = isolated_pack_discovery_env(root);
    env_values.claude_config_dir = store.string();
    const ScopedPackDiscoveryEnv discovery_env{env_values};

    const auto report = biv::pack::pack(source);

    REQUIRE_FALSE(report.has_value());
    CHECK_FALSE(std::filesystem::exists(root / "proj.bvpk"));
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("pack carries duplicate-store warning and A5 pick into the envelope") {
  const auto root = make_tmp("codex-duplicate-warning");
  const auto source = root / "proj";
  const auto env_store = root / "env-codex";
  const auto default_store = root / "home" / ".codex";
  const auto session_id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7700"};
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto rollout = [&](const std::filesystem::path& store,
                           const std::string_view timestamp) {
    write_file(store / "sessions" / "2026" / "07" / "06" /
                   ("rollout-2026-07-06T01-00-00-" + session_id + ".jsonl"),
               "{\"timestamp\":\"" + std::string{timestamp} +
                   "\",\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                   session_id + "\",\"session_id\":\"" + session_id +
                   "\",\"cwd\":\"" + source.generic_string() +
                   "\",\"cli_version\":\"0.142.5\"}}\n");
  };
  rollout(env_store, "2026-07-06T01:00:00Z");
  rollout(default_store, "2026-07-06T02:00:00Z");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.codex_home = env_store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  REQUIRE(report->agent_sessions.size() == 1);
  CHECK(report->agent_sessions.front().provenance.store_root ==
        default_store.generic_string());
  CHECK(std::ranges::any_of(report->warnings, [&](const biv::pack::Warning& warning) {
    return warning.kind == "SessionDuplicateStore" && warning.path == session_id &&
           !warning.artifact.has_value() && !warning.bytes.has_value();
  }));
  const auto json = biv::report::envelope("pack", *report, std::nullopt,
                                          std::nullopt, 2);
  CHECK(json.find("\"kind\": \"SessionDuplicateStore\"") != std::string::npos);
  CHECK(json.find(session_id) != std::string::npos);
  const auto members = read_archive(root / "proj.bvpk");
  const auto winner = std::ranges::find_if(members, [&](const ArchiveMember& member) {
    return member.meta.path == "agents/codex/" + session_id + ".jsonl";
  });
  REQUIRE(winner != members.end());
  CHECK(byte_string(as_span(winner->data)).find("2026-07-06T02:00:00Z") !=
        std::string::npos);
  CHECK(byte_string(as_span(winner->data)).find("2026-07-06T01:00:00Z") ==
        std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("pack excludes symlinked Claude agent artifacts") {
  const auto root = make_tmp("claude-symlink");
  const auto source = root / "proj";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto store = root / "claude_store";
  copy_fixture_tree_with_workspace(std::filesystem::path{BIV_SOURCE_DIR} /
                                       "tests" / "fixtures" / "claude_store",
                                   store, source);
  write_file(root / "secret.jsonl", "DO_NOT_COLLECT_SYMLINK_SECRET");
  std::filesystem::create_symlink(root / "secret.jsonl",
                                  store / "projects" / "-ws-proj" /
                                      "aaaaaaaa-1111-4000-8000-000000000001" /
                                      "leak.jsonl");
  write_file(store / "projects" / "-ws-proj" /
                 "aaaaaaaa-1111-4000-8000-000000000001" /
                 ".credentials.json",
             "DO_NOT_COLLECT_REGULAR_CREDENTIAL");
  write_file(store / "projects" / "-ws-proj" / "history.jsonl",
             "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                 "\",\"sessionId\":\"history-sentinel\",\"version\":"
                 "\"2.1.202\",\"message\":\"DO_NOT_COLLECT_MAIN_HISTORY\"}\n");
  write_file(store / "projects" / "-ws-proj" /
                 "aaaaaaaa-1111-4000-8000-000000000001" / "history.jsonl",
             "DO_NOT_COLLECT_SUBTREE_HISTORY");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.claude_config_dir = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  const auto members = read_archive(root / "proj.bvpk");
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return member.meta.path.find("leak.jsonl") != std::string::npos;
  }));
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return byte_string(as_span(member.data))
               .find("DO_NOT_COLLECT_SYMLINK_SECRET") != std::string::npos;
  }));
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return byte_string(as_span(member.data))
               .find("DO_NOT_COLLECT_REGULAR_CREDENTIAL") != std::string::npos;
  }));
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return member.meta.path.find("history.jsonl") != std::string::npos ||
           byte_string(as_span(member.data)).find("DO_NOT_COLLECT_MAIN_HISTORY") !=
               std::string::npos ||
           byte_string(as_span(member.data)).find(
               "DO_NOT_COLLECT_SUBTREE_HISTORY") != std::string::npos;
  }));
  std::filesystem::remove_all(root);
}

TEST_CASE("pack derives relpath from slash-form Windows extended paths") {
  if (!std::filesystem::exists("/mnt/c") || ::access("/mnt/c", W_OK) != 0) {
    SKIP("requires a writable /mnt/c WSL fixture root");
  }
  const auto token = "biv-pack-extended-" + std::to_string(::getpid());
  const auto source = std::filesystem::path{"/mnt/c/tmp"} / token / "proj";
  const auto root = make_tmp("extended-relpath");
  const auto store = root / "codex";
  const auto session_id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee9900"};
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T01-00-00-" + session_id + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":"
             "\"session_meta\",\"payload\":{\"id\":\"" + session_id +
                 "\",\"session_id\":\"" + session_id +
                 "\",\"cwd\":\"//?/C:/tmp/" + token +
                 "/proj/sub\",\"cli_version\":\"0.142.5\"}}\n");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.codex_home = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  REQUIRE(report->agent_sessions.size() == 1);
  CHECK(report->agent_sessions.front().relpath_key == "sub");
  std::filesystem::remove_all(source.parent_path());
  std::filesystem::remove_all(root);
}

TEST_CASE("pack computes foreign-flavor session relpaths without host path parsing") {
  if (!std::filesystem::exists("/mnt/c") || ::access("/mnt/c", W_OK) != 0) {
    SKIP("requires a writable /mnt/c WSL fixture root");
  }
  const auto root = std::filesystem::path{"/mnt/c/tmp"} /
                    ("biv-pack-foreign-relpath-" +
                     std::to_string(static_cast<long long>(::getpid())));
  std::filesystem::remove_all(root);
  const auto source = root / "proj";
  const auto store = root / "codex";
  const auto session_id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7800"};
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  auto windows_cwd = "C:" + source.generic_string().substr(6);
  std::ranges::replace(windows_cwd, '/', '\\');
  windows_cwd += "\\sub";
  std::string json_cwd;
  for (const char character : windows_cwd) {
    if (character == '\\') {
      json_cwd += "\\\\";
    } else {
      json_cwd.push_back(character);
    }
  }
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T01-00-00-" + session_id + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T01:00:00Z\",\"type\":"
             "\"session_meta\",\"payload\":{\"id\":\"" + session_id +
                 "\",\"session_id\":\"" + session_id +
                 "\",\"cwd\":\"" + json_cwd +
                 "\",\"cli_version\":\"0.142.5\"}}\n");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.codex_home = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  REQUIRE(report->agent_sessions.size() == 1);
  CHECK(report->agent_sessions.front().relpath_key == "sub");
  std::filesystem::remove_all(root);
}

TEST_CASE("pack writes dangling Codex parent fields as parent not in image") {
  const auto root = make_tmp("codex-dangling-parent");
  const auto source = root / "proj";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto store = root / "codex_store";
  const auto missing_parent =
      std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7000"};
  const auto child = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7001"};
  write_file(store / "sessions" / "2026" / "07" / "06" /
                 ("rollout-2026-07-06T11-00-00-" + child + ".jsonl"),
             "{\"timestamp\":\"2026-07-06T11:00:00Z\",\"type\":\"session_"
             "meta\",\"payload\":{\"id\":\"" +
                 child + "\",\"session_id\":\"" + missing_parent + "\",\"cwd\":\"" +
                 source.generic_string() +
                 "\",\"cli_version\":\"0.142.5\",\"parent_thread_id\":\"" +
                 missing_parent + "\"}}\n");
  auto env_values = isolated_pack_discovery_env(root);
  env_values.codex_home = store.string();
  const ScopedPackDiscoveryEnv discovery_env{env_values};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
  require_store_roots_under(*report, root);
  REQUIRE(report->agent_sessions.size() == 1);
  const auto& entry = report->agent_sessions.front();
  CHECK(entry.agent == "codex");
  CHECK(entry.original_session_ids.primary == child);
  REQUIRE(entry.original_session_ids.parent.has_value());
  CHECK(*entry.original_session_ids.parent == missing_parent);
  REQUIRE(entry.original_session_ids.parent_in_image.has_value());
  CHECK_FALSE(*entry.original_session_ids.parent_in_image);

  const auto members = read_archive(root / "proj.bvpk");
  auto manifest = biv::manifest::parse(as_span(members.at(0).data));
  REQUIRE(manifest.has_value());
  REQUIRE(manifest->agent_sessions.size() == 1);
  REQUIRE(
      manifest->agent_sessions.front().original_session_ids.parent.has_value());
  CHECK(*manifest->agent_sessions.front().original_session_ids.parent ==
        missing_parent);
  REQUIRE(manifest->agent_sessions.front()
              .original_session_ids.parent_in_image.has_value());
  CHECK_FALSE(
      *manifest->agent_sessions.front().original_session_ids.parent_in_image);
  std::filesystem::remove_all(root);
}

TEST_CASE("pack forwards each collected torn-tail fact as an exact warning") {
  const auto root = make_tmp("torn-tail-warning");
  const auto source = root / "proj";
  const auto store = root / "codex";
  const auto id = std::string{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee7900"};
  const auto tail = std::string{"{bad"};
  const auto artifact = "agents/codex/" + id + ".jsonl";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  write_file(store / "sessions" / "2026" / "08" / "06" /
                 ("rollout-2026-08-06T01-00-00-" + id + ".jsonl"),
             "{\"timestamp\":\"2026-08-06T01:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                 id + "\",\"cwd\":\"" + source.generic_string() +
                 "\",\"cli_version\":\"0.142.5\"}}\n" + tail);
  const ScopedEnv codex_home{"CODEX_HOME", store.string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report);
  const auto warning = std::ranges::find_if(report->warnings, [&](const auto& candidate) {
    return candidate.kind == biv::pack::kWarningTornTailDropped;
  });
  REQUIRE(warning != report->warnings.end());
  CHECK(warning->path == id);
  CHECK(warning->artifact == std::optional<std::string>{artifact});
  CHECK(warning->bytes == std::optional<std::uint64_t>{tail.size()});
  CHECK(biv::pack::warning_text(*warning) ==
        "warning: torn tail dropped from " + artifact + ": 4 bytes");
  const auto members = read_archive(root / "proj.bvpk");
  const auto session = std::ranges::find_if(members, [&](const ArchiveMember& member) {
    return member.meta.path == artifact;
  });
  REQUIRE(session != members.end());
  CHECK(byte_string(session->data).ends_with("\n"));
  std::filesystem::remove_all(root);
}

TEST_CASE("pack warns that a retained torn tail makes the session uninstallable") {
  const auto root = make_tmp("retained-torn-tail-warning");
  const auto source = root / "proj";
  const auto store = root / "claude";
  const auto id = std::string{"aaaaaaaa-1111-4000-8000-000000007901"};
  const auto tail = std::string{"{bad"};
  const auto artifact = "agents/claude-code/" + id + ".jsonl";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  write_file(store / "projects" / "project" / (id + ".jsonl"),
             "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                 "\",\"sessionId\":\"" + id +
                 "\",\"version\":\"2.1.202\"}\n" + tail);
  write_file(store / "sessions" / (id + ".json"),
             "{\"sessionId\":\"" + id + "\",\"status\":\"completed\"}");
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", store.string()};
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report);
  const auto warning = std::ranges::find_if(report->warnings, [](const auto& candidate) {
    return candidate.kind == "TornTailRetained";
  });
  REQUIRE(warning != report->warnings.end());
  CHECK(warning->path == id);
  CHECK(warning->artifact == std::optional<std::string>{artifact});
  CHECK(warning->bytes == std::optional<std::uint64_t>{tail.size()});
  CHECK(biv::pack::warning_text(*warning) ==
        "warning: torn tail retained in " + artifact +
            ": 4 bytes; install will refuse this session");
  const auto members = read_archive(root / "proj.bvpk");
  const auto session = std::ranges::find_if(members, [&](const ArchiveMember& member) {
    return member.meta.path == artifact;
  });
  REQUIRE(session != members.end());
  CHECK(byte_string(session->data).ends_with(tail));
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-VF-O1 re-pack manifests retain staged identity and original provenance") {
  constexpr std::string_view codex_original = "cx-0001";
  constexpr std::string_view codex_minted =
      "019f1d8c-e200-7000-8000-000000000001";
  constexpr std::string_view claude_original = "cl-0001";
  constexpr std::string_view claude_minted =
      "4c1e9a20-0000-4000-8000-000000000001";
  const auto root = make_tmp("repack-manifest-aggregate");
  const auto source = root / "workspace";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");

  const std::string codex_transcript =
      std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
      std::string{codex_minted} + "\",\"session_id\":\"" +
      std::string{codex_minted} + "\",\"cwd\":\"" +
      source.generic_string() + "\",\"cli_version\":\"0.142.5\"}}\n"
      "{\"timestamp\":\"2026-07-01T12:01:00Z\",\"type\":\"turn_context\",\"payload\":{\"cwd\":\"" +
      source.generic_string() + "\",\"workspace_roots\":[\"" +
      source.generic_string() + "\"]}}\n";
  const std::string claude_transcript =
      std::string{"{\"type\":\"user\",\"cwd\":\""} +
      source.generic_string() + "\",\"sessionId\":\"" +
      std::string{claude_minted} + "\",\"version\":\"2.1.207\"}\n";
  const std::string codex_artifact =
      "agents/codex/" + std::string{codex_minted} + ".jsonl";
  const std::string claude_artifact =
      "agents/claude-code/" + std::string{claude_minted} + ".jsonl";
  write_file(
      source /
          (".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
           std::string{codex_minted} + ".jsonl"),
      codex_transcript);
  write_file(source / (".biv/agents/claude-code/projects/-home-packer-proj/" +
                       std::string{claude_minted} + ".jsonl"),
             claude_transcript);
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\""} +
          std::string{claude_original} + "\",\"installed_session_id\":\"" +
          std::string{claude_minted} +
          "\",\"children\":[]},{\"agent\":\"codex\",\"image_session_id\":\"" +
          std::string{codex_original} + "\",\"installed_session_id\":\"" +
          std::string{codex_minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\",\"cx-0001\"],"
          "\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
          source.generic_string() + "\"]]}");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report);
  REQUIRE(report->agent_sessions.size() == 2U);
  const auto check_canon_entry = [&](const auto& entries,
                                     const std::string_view agent,
                                     const std::string_view original,
                                     const std::string_view artifact) {
    const auto entry = std::ranges::find(
        entries, agent, [](const auto& value) {
          return std::string_view{value.agent};
        });
    REQUIRE(entry != entries.end());
    CHECK(entry->provenance.locator == "staging");
    CHECK(entry->provenance.discovery_tier == "staged");
    CHECK(entry->original_session_ids.primary == original);
    REQUIRE(entry->artifacts.size() == 1U);
    CHECK(entry->artifacts.front() == artifact);
    CHECK(entry->original_path == "/home/packer/proj");
  };
  check_canon_entry(report->agent_sessions, "codex", codex_original,
                    codex_artifact);
  check_canon_entry(report->agent_sessions, "claude-code", claude_original,
                    claude_artifact);

  const auto members = read_archive(root / "workspace.bvpk");
  std::vector<std::string> member_paths;
  for (const auto& member : members) member_paths.push_back(member.meta.path);
  std::ranges::sort(member_paths);
  const std::vector<std::string> expected_member_paths{
      claude_artifact, codex_artifact, "checksums.json", "manifest.json",
      "payload/work.txt"};
  REQUIRE(member_paths.size() == expected_member_paths.size());
  CHECK(member_paths == expected_member_paths);

  const auto manifest_member = std::ranges::find(
      members, std::string_view{"manifest.json"},
      [](const ArchiveMember& member) {
        return std::string_view{member.meta.path};
      });
  REQUIRE(manifest_member != members.end());
  const auto manifest = biv::manifest::parse(as_span(manifest_member->data));
  REQUIRE(manifest);
  REQUIRE(manifest->agent_sessions.size() == 2U);
  check_canon_entry(manifest->agent_sessions, "codex", codex_original,
                    codex_artifact);
  check_canon_entry(manifest->agent_sessions, "claude-code", claude_original,
                    claude_artifact);

  const auto check_artifact = [&](const std::string_view path,
                                  const std::string_view transcript) {
    const auto artifact = std::ranges::find(
        members, path, [](const ArchiveMember& member) {
          return std::string_view{member.meta.path};
        });
    REQUIRE(artifact != members.end());
    CHECK(byte_string(artifact->data) == transcript);
    CHECK(byte_string(artifact->data).find("/home/packer/proj") ==
          std::string::npos);
    CHECK(byte_string(artifact->data).find(source.generic_string()) !=
          std::string::npos);
  };
  check_artifact(codex_artifact, codex_transcript);
  check_artifact(claude_artifact, claude_transcript);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "B2 composed Claude stage pack install removes the staging workspace path") {
  constexpr std::string_view original_id =
      "aaaaaaaa-1111-4000-8000-000000009101";
  const auto root = make_tmp("claude-stage-pack-install-path");
  const auto original_workspace = root / "original-workspace";
  const auto final_workspace = root / "final-workspace";
  const auto final_store = root / "final-claude";
  std::filesystem::create_directories(original_workspace);
  std::filesystem::create_directories(final_workspace);
  std::filesystem::create_directories(final_store);

  const std::string artifact =
      "agents/claude-code/" + std::string{original_id} + ".jsonl";
  biv::manifest::AgentSessionEntry record{
      .agent = "claude-code",
      .agent_version_at_pack = "2.1.207",
      .relpath_key = ".",
      .original_path = original_workspace.generic_string(),
      .normalized_path_key = original_workspace.generic_string(),
      .normalization_scheme = "claude-cwd/v1",
      .path_flavor = biv::manifest::PathFlavor::posix,
      .provenance = {.store_root = "/source/.claude",
                     .locator = "sessions_root",
                     .discovery_tier = "env",
                     .archived = false},
      .original_session_ids = {.primary = std::string{original_id},
                               .parent = std::nullopt,
                               .parent_in_image = std::nullopt},
      .children = {},
      .artifacts = {artifact},
      .live_at_pack = false,
      .imported_at = "2026-08-09T00:00:00Z",
      .entry_schema = 1};
  std::map<std::string, std::vector<std::byte>> input_members;
  input_members.emplace(
      artifact,
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{original_id} +
                 "\",\"version\":\"2.1.207\"}\n"));

  auto image = stage_then_pack(root, biv::adapters::claude_code_adapter(),
                               record, input_members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  const auto& packed_record = image.manifest.agent_sessions.front();
  CHECK(packed_record.original_path == original_workspace.generic_string());
  CHECK(packed_record.provenance.store_root ==
        (root / "staging-workspace").generic_string());
  auto target = biv::adapters::InstallTarget{
      .workspace_root = final_workspace,
      .target_store = biv::adapters::Store{
          .root = final_store,
          .locators = {},
          .tier = biv::adapters::DiscoveryTier::env,
          .archived = false},
      .member_read = [&](const std::string_view path)
          -> biv::expected<std::vector<std::byte>> {
        const auto found = image.members.find(std::string{path});
        if (found == image.members.end()) {
          return std::unexpected(
              biv::BivError{biv::ErrKind::ImageUnreadable,
                            std::string{path}});
        }
        return found->second;
      },
      .capabilities = round_trip_capabilities("claude-code")};
  const auto installed = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes,
      image.manifest.agent_sessions);

  REQUIRE(installed);
  REQUIRE(installed->sessions.size() == 1U);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  const auto content = combined_file_text(final_store);
  CHECK(content.find(original_workspace.generic_string()) == std::string::npos);
  CHECK(content.find((root / "staging-workspace").generic_string()) ==
        std::string::npos);
  CHECK(content.find(final_workspace.generic_string()) != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "B1 Claude consent-no round trip carries every declared subtree class") {
  constexpr std::string_view original_id =
      "aaaaaaaa-1111-4000-8000-000000009111";
  const auto root = make_tmp("claude-stage-pack-subtree-class");
  const auto original_workspace = root / "original-workspace";
  std::filesystem::create_directories(original_workspace);

  const std::string main =
      "agents/claude-code/" + std::string{original_id} + ".jsonl";
  const std::string note =
      "agents/claude-code/" + std::string{original_id} + "/notes.txt";
  biv::manifest::AgentSessionEntry record{
      .agent = "claude-code",
      .agent_version_at_pack = "2.1.207",
      .relpath_key = ".",
      .original_path = original_workspace.generic_string(),
      .normalized_path_key = original_workspace.generic_string(),
      .normalization_scheme = "claude-cwd/v1",
      .path_flavor = biv::manifest::PathFlavor::posix,
      .provenance = {.store_root = "/source/.claude",
                     .locator = "sessions_root",
                     .discovery_tier = "env",
                     .archived = false},
      .original_session_ids = {.primary = std::string{original_id},
                               .parent = std::nullopt,
                               .parent_in_image = std::nullopt},
      .children = {},
      .artifacts = {main, note},
      .live_at_pack = false,
      .imported_at = "2026-08-10T00:00:00Z",
      .entry_schema = 1};
  std::map<std::string, std::vector<std::byte>> input_members;
  input_members.emplace(
      main,
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{original_id} +
                 "\",\"version\":\"2.1.207\"}\n"));
  input_members.emplace(note, text_bytes("declared subtree note\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::claude_code_adapter(), record, input_members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  const auto packed_note = std::ranges::find_if(
      image.manifest.agent_sessions.front().artifacts,
      [](const std::string_view artifact) {
        return artifact.ends_with("/notes.txt");
      });
  REQUIRE(packed_note !=
          image.manifest.agent_sessions.front().artifacts.end());
  REQUIRE(image.members.contains(*packed_note));
  CHECK(image.members.at(*packed_note) == text_bytes("declared subtree note\n"));
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "B2 composed Codex stage pack install removes the staging workspace path") {
  constexpr std::string_view original_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9101";
  const auto root = make_tmp("codex-stage-pack-install-path");
  const auto original_workspace = root / "original-workspace";
  const auto final_workspace = root / "final-workspace";
  const auto final_store = root / "final-codex";
  std::filesystem::create_directories(original_workspace);
  std::filesystem::create_directories(final_workspace);
  std::filesystem::create_directories(final_store);

  const std::string artifact =
      "agents/codex/" + std::string{original_id} + ".jsonl";
  biv::manifest::AgentSessionEntry record{
      .agent = "codex",
      .agent_version_at_pack = "0.144.1",
      .relpath_key = ".",
      .original_path = original_workspace.generic_string(),
      .normalized_path_key = original_workspace.generic_string(),
      .normalization_scheme = "codex-cwd/v1",
      .path_flavor = biv::manifest::PathFlavor::posix,
      .provenance = {.store_root = "/source/.codex",
                     .locator = "sessions_root",
                     .discovery_tier = "env",
                     .archived = false},
      .original_session_ids = {.primary = std::string{original_id},
                               .parent = std::nullopt,
                               .parent_in_image = std::nullopt},
      .children = {},
      .artifacts = {artifact},
      .live_at_pack = false,
      .imported_at = "2026-08-09T00:00:00Z",
      .entry_schema = 1};
  std::map<std::string, std::vector<std::byte>> input_members;
  input_members.emplace(
      artifact,
      text_bytes(
          std::string{
              "{\"timestamp\":\"2026-08-09T00:00:00Z\",\"type\":"
              "\"session_meta\",\"payload\":{\"id\":\""} +
          std::string{original_id} + "\",\"session_id\":\"" +
          std::string{original_id} + "\",\"cwd\":\"" +
          original_workspace.generic_string() +
          "\",\"cli_version\":\"0.144.1\"}}\n"));

  auto image = stage_then_pack(root, biv::adapters::codex_adapter(), record,
                               input_members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  const auto& packed_record = image.manifest.agent_sessions.front();
  CHECK(packed_record.original_path == original_workspace.generic_string());
  CHECK(packed_record.provenance.store_root ==
        (root / "staging-workspace").generic_string());
  auto target = biv::adapters::InstallTarget{
      .workspace_root = final_workspace,
      .target_store = biv::adapters::Store{
          .root = final_store,
          .locators = {},
          .tier = biv::adapters::DiscoveryTier::env,
          .archived = false},
      .member_read = [&](const std::string_view path)
          -> biv::expected<std::vector<std::byte>> {
        const auto found = image.members.find(std::string{path});
        if (found == image.members.end()) {
          return std::unexpected(
              biv::BivError{biv::ErrKind::ImageUnreadable,
                            std::string{path}});
        }
        return found->second;
      },
      .capabilities = round_trip_capabilities("codex")};
  const auto installed = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes,
      image.manifest.agent_sessions);

  REQUIRE(installed);
  REQUIRE(installed->sessions.size() == 1U);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  const auto content = combined_file_text(final_store);
  CHECK(content.find(original_workspace.generic_string()) == std::string::npos);
  CHECK(content.find((root / "staging-workspace").generic_string()) ==
        std::string::npos);
  CHECK(content.find(final_workspace.generic_string()) != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "FX-A11-1 Codex consent-no round trip preserves two distinct original paths") {
  constexpr std::array ids{
      std::string_view{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee9121"},
      std::string_view{"019faaaa-bbbb-7ccc-8ddd-eeeeeeee9122"}};
  const auto root = make_tmp("codex-stage-pack-two-original-paths");
  std::vector<biv::manifest::AgentSessionEntry> records;
  std::map<std::string, std::vector<std::byte>> input_members;
  for (size_t index = 0; index < ids.size(); ++index) {
    const auto original_workspace =
        root / ("original-workspace-" + std::to_string(index));
    std::filesystem::create_directories(original_workspace);
    const std::string artifact =
        "agents/codex/" + std::string{ids.at(index)} + ".jsonl";
    records.push_back(biv::manifest::AgentSessionEntry{
        .agent = "codex",
        .agent_version_at_pack = "0.144.1",
        .relpath_key = ".",
        .original_path = original_workspace.generic_string(),
        .normalized_path_key = original_workspace.generic_string(),
        .normalization_scheme = "codex-cwd/v1",
        .path_flavor = biv::manifest::PathFlavor::posix,
        .provenance = {.store_root = "/source/.codex",
                       .locator = "sessions_root",
                       .discovery_tier = "env",
                       .archived = false},
        .original_session_ids = {.primary = std::string{ids.at(index)},
                                 .parent = std::nullopt,
                                 .parent_in_image = std::nullopt},
        .children = {},
        .artifacts = {artifact},
        .live_at_pack = false,
        .imported_at = "2026-08-10T00:00:00Z",
        .entry_schema = 1});
    input_members.emplace(
        artifact,
        text_bytes(
            std::string{"{\"timestamp\":\"2026-08-10T00:00:00Z\","}
            + "\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
            std::string{ids.at(index)} + "\",\"session_id\":\"" +
            std::string{ids.at(index)} + "\",\"cwd\":\"" +
            original_workspace.generic_string() +
            "\",\"cli_version\":\"0.144.1\"}}\n"));
  }

  const auto image = stage_then_pack(
      root, biv::adapters::codex_adapter(),
      std::span<const biv::manifest::AgentSessionEntry>{records},
      input_members);

  REQUIRE(image.manifest.agent_sessions.size() == records.size());
  for (const auto& record : records) {
    const auto packed = std::ranges::find(
        image.manifest.agent_sessions, record.original_session_ids.primary,
        [](const auto& candidate) {
          return candidate.original_session_ids.primary;
        });
    REQUIRE(packed != image.manifest.agent_sessions.end());
    CHECK(packed->original_path == record.original_path);
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-A11-7a Codex mixed-separator origin canonicalizes on round trip") {
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9171";
  constexpr std::string_view mixed = "C:\\Users/Me/Proj";
  constexpr std::string_view canonical = "C:\\Users\\Me\\Proj";
  const auto root = make_tmp("a11-codex-mixed-origin");
  const auto record = windows_round_trip_record("codex", session_id, mixed);
  auto members = windows_round_trip_members(record);

  const auto image = stage_then_pack(
      root, biv::adapters::codex_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().original_path == canonical);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "FX-A11-7b Claude mixed-separator origin canonicalizes on round trip") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000009172";
  constexpr std::string_view mixed = "C:\\Users/Me/Proj";
  constexpr std::string_view canonical = "C:\\Users\\Me\\Proj";
  const auto root = make_tmp("a11-claude-mixed-origin");
  const auto record =
      windows_round_trip_record("claude-code", session_id, mixed);
  auto members = windows_round_trip_members(record);

  const auto image = stage_then_pack(
      root, biv::adapters::claude_code_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().original_path == canonical);
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-A11-8a Codex canonical original_path bytes are fixed on repack") {
  constexpr std::string_view session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9181";
  constexpr std::string_view canonical = "C:\\Users\\Me\\Proj";
  const auto first_root = make_tmp("a11-codex-fixed-first");
  const auto record =
      windows_round_trip_record("codex", session_id, canonical);
  auto first_members = windows_round_trip_members(record);
  const auto first = stage_then_pack(
      first_root, biv::adapters::codex_adapter(), record, first_members);
  REQUIRE(first.manifest.agent_sessions.size() == 1U);
  const auto first_value =
      first.manifest.agent_sessions.front().original_path;

  const auto second_root = make_tmp("a11-codex-fixed-second");
  auto second_members = first.members;
  const auto second = stage_then_pack(
      second_root, biv::adapters::codex_adapter(),
      first.manifest.agent_sessions.front(), second_members);

  REQUIRE(second.manifest.agent_sessions.size() == 1U);
  CHECK(first_value == canonical);
  CHECK(second.manifest.agent_sessions.front().original_path == first_value);
  std::filesystem::remove_all(first_root);
  std::filesystem::remove_all(second_root);
}

TEST_CASE("FX-A11-8b Claude canonical original_path bytes are fixed on repack") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000009182";
  constexpr std::string_view canonical = "C:\\Users\\Me\\Proj";
  const auto first_root = make_tmp("a11-claude-fixed-first");
  const auto record =
      windows_round_trip_record("claude-code", session_id, canonical);
  auto first_members = windows_round_trip_members(record);
  const auto first = stage_then_pack(
      first_root, biv::adapters::claude_code_adapter(), record,
      first_members);
  REQUIRE(first.manifest.agent_sessions.size() == 1U);
  const auto first_value =
      first.manifest.agent_sessions.front().original_path;

  const auto second_root = make_tmp("a11-claude-fixed-second");
  auto second_members = first.members;
  const auto second = stage_then_pack(
      second_root, biv::adapters::claude_code_adapter(),
      first.manifest.agent_sessions.front(), second_members);

  REQUIRE(second.manifest.agent_sessions.size() == 1U);
  CHECK(first_value == canonical);
  CHECK(second.manifest.agent_sessions.front().original_path == first_value);
  std::filesystem::remove_all(first_root);
  std::filesystem::remove_all(second_root);
}

TEST_CASE("B2 standing Claude stage pack open keeps parent references equal to "
          "child stems") {
  struct Case {
    std::string_view name;
    std::string_view child_id;
    std::string_view subtree;
  };
  for (const auto &test : std::array{
           Case{"flat-bare-hex", "agent-a00e74f5f82549807",
                "subagents/agent-a00e74f5f82549807.jsonl"},
           Case{"flat-slug-hex", "agent-explore-b00e74f5f82549807",
                "subagents/agent-explore-b00e74f5f82549807.jsonl"},
           Case{"nested-bare-hex", "agent-c00e74f5f82549807",
                "subagents/workflows/wf-a/agent-c00e74f5f82549807.jsonl"}}) {
    DYNAMIC_SECTION(test.name) {
      constexpr std::string_view original_id =
          "aaaaaaaa-1111-4000-8000-000000009111";
      constexpr std::string_view message_id =
          "00000000-0000-4000-8000-000000009112";
      const auto original_child = test.child_id;
      const auto root =
          make_tmp("claude-stage-pack-install-child-" + std::string{test.name});
      const auto original_workspace = root / "original-workspace";
      const auto final_workspace = root / "final-workspace";
      const auto final_store = root / "final-claude";
      std::filesystem::create_directories(original_workspace);
      std::filesystem::create_directories(final_workspace);
      std::filesystem::create_directories(final_store);

      const std::string main_artifact =
          "agents/claude-code/" + std::string{original_id} + ".jsonl";
      const std::string child_artifact = "agents/claude-code/" +
                                         std::string{original_id} + "/" +
                                         std::string{test.subtree};
      const std::string child_meta =
          child_artifact.substr(0, child_artifact.size() - 6U) + ".meta.json";
      biv::manifest::AgentSessionEntry record{
          .agent = "claude-code",
          .agent_version_at_pack = "2.1.207",
          .relpath_key = ".",
          .original_path = original_workspace.generic_string(),
          .normalized_path_key = original_workspace.generic_string(),
          .normalization_scheme = "claude-cwd/v1",
          .path_flavor = biv::manifest::PathFlavor::posix,
          .provenance = {.store_root = "/source/.claude",
                         .locator = "sessions_root",
                         .discovery_tier = "env",
                         .archived = false},
          .original_session_ids = {.primary = std::string{original_id},
                                   .parent = std::nullopt,
                                   .parent_in_image = std::nullopt},
          .children = {{.original_id = std::string{original_child},
                        .artifacts = {child_artifact, child_meta}}},
          .artifacts = {main_artifact},
          .live_at_pack = false,
          .imported_at = "2026-08-09T00:00:00Z",
          .entry_schema = 1};
      std::map<std::string, std::vector<std::byte>> input_members;
      input_members.emplace(
          main_artifact,
          text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                     original_workspace.generic_string() +
                     "\",\"sessionId\":\"" + std::string{original_id} +
                     "\",\"senderTaskId\":\"" + std::string{original_child} +
                     "\",\"version\":\"2.1.207\"}\n"));
      input_members.emplace(
          child_artifact,
          text_bytes(std::string{"{\"type\":\"assistant\",\"cwd\":\""} +
                     original_workspace.generic_string() +
                     "\",\"sessionId\":\"" + std::string{original_id} +
                     "\",\"agentId\":\"" + std::string{original_child} +
                     "\",\"uuid\":\"" + std::string{message_id} + "\"}\n"));
      input_members.emplace(child_meta,
                            text_bytes("{\"agentType\":\"explore\"}\n"));

      auto image = stage_then_pack(root, biv::adapters::claude_code_adapter(),
                                   record, input_members);

      REQUIRE(image.staged_id_map.front().children.size() == 1U);
      const auto staged_child =
          image.staged_id_map.front().children.front().second;
      CHECK(image.staged_id_map.front().children.front().first ==
            original_child);
      CHECK(staged_child == original_child);
      REQUIRE(image.manifest.agent_sessions.size() == 1U);
      const auto &packed_record = image.manifest.agent_sessions.front();
      REQUIRE(packed_record.children.size() == 1U);
      CHECK(packed_record.children.front().original_id == original_child);
      CHECK(packed_record.children.front().artifacts.size() == 2U);
      auto target = biv::adapters::InstallTarget{
          .workspace_root = final_workspace,
          .target_store =
              biv::adapters::Store{.root = final_store,
                                   .locators = {},
                                   .tier = biv::adapters::DiscoveryTier::env,
                                   .archived = false},
          .member_read = [&](const std::string_view path)
              -> biv::expected<std::vector<std::byte>> {
            const auto found = image.members.find(std::string{path});
            if (found == image.members.end()) {
              return std::unexpected(biv::BivError{
                  biv::ErrKind::ImageUnreadable, std::string{path}});
            }
            return found->second;
          },
          .capabilities = round_trip_capabilities("claude-code")};
      const auto installed = biv::adapters::claude_code_adapter().install(
          target, biv::adapters::Consent::yes, image.manifest.agent_sessions);

      REQUIRE(installed);
      REQUIRE(installed->sessions.size() == 1U);
      CHECK(installed->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::installed);
      REQUIRE(installed->id_map.size() == 1U);
      REQUIRE(installed->id_map.front().children.size() == 1U);
      const auto final_child =
          installed->id_map.front().children.front().second;
      CHECK(installed->id_map.front().children.front().first == original_child);
      CHECK(final_child == original_child);
      std::optional<std::filesystem::path> restored_child;
      for (const auto &entry :
           std::filesystem::recursive_directory_iterator(final_store)) {
        if (entry.is_regular_file() &&
            entry.path().filename() == std::string{original_child} + ".jsonl") {
          restored_child = entry.path();
          break;
        }
      }
      REQUIRE(restored_child.has_value());
      CHECK(restored_child->stem() == original_child);
      CHECK(restored_child->generic_string().ends_with(test.subtree));
      const auto content = combined_file_text(final_store);
      CHECK(content.find("\"senderTaskId\":\"" + std::string{original_child} +
                         "\"") != std::string::npos);
      CHECK(content.find("\"agentId\":\"" + std::string{original_child} +
                         "\"") != std::string::npos);
      CHECK(content.find(original_workspace.generic_string()) ==
            std::string::npos);
      CHECK(content.find((root / "staging-workspace").generic_string()) ==
            std::string::npos);
      CHECK(content.find(final_workspace.generic_string()) !=
            std::string::npos);
      std::filesystem::remove_all(root);
    }
  }
}

TEST_CASE("F-1 Claude consent-no round trip accepts an empty subagent body") {
  constexpr std::string_view original_id =
      "aaaaaaaa-1111-4000-8000-000000009121";
  constexpr std::string_view child_id = "agent-empty";
  const auto root = make_tmp("claude-stage-pack-empty-subagent");
  const auto workspace = root / "original-workspace";
  std::filesystem::create_directories(workspace);
  auto record = round_trip_record("claude-code", original_id, workspace);
  const auto child_artifact =
      "agents/claude-code/" + std::string{original_id} + "/subagents/" +
      std::string{child_id} + ".jsonl";
  record.children = {{.original_id = std::string{child_id},
                      .artifacts = {child_artifact}}};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 workspace.generic_string() + "\",\"sessionId\":\"" +
                 std::string{original_id} +
                 "\",\"version\":\"2.1.207\"}\n"));
  members.emplace(child_artifact, text_bytes("{}\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::claude_code_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  REQUIRE(image.manifest.agent_sessions.front().children.size() == 1U);
  const auto packed_child =
      image.manifest.agent_sessions.front().children.front().artifacts.front();
  REQUIRE(image.members.contains(packed_child));
  CHECK(image.members.at(packed_child) == text_bytes("{}\n"));
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "F-2 staged readers use the minted filename when legal writer content has no id") {
  struct Case {
    std::string_view agent;
    std::string_view original_id;
  };
  for (const auto& test : std::array{
           Case{"claude-code",
                "aaaaaaaa-1111-4000-8000-000000009131"},
           Case{"codex", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9132"}}) {
    DYNAMIC_SECTION(test.agent) {
      const auto root = make_tmp("stage-pack-idless-" +
                                 std::string{test.agent});
      const auto workspace = root / "original-workspace";
      std::filesystem::create_directories(workspace);
      auto record = round_trip_record(test.agent, test.original_id, workspace);
      std::map<std::string, std::vector<std::byte>> members;
      if (test.agent == "codex") {
        const auto child_artifact =
            "agents/codex/019faaaa-bbbb-7ccc-8ddd-eeeeeeee9133.jsonl";
        record.children = {{
            .original_id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9133",
            .artifacts = {child_artifact}}};
        members.emplace(
            record.artifacts.front(),
            text_bytes(
                std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
                "\"cwd\":\"" + workspace.generic_string() +
                "\",\"cli_version\":\"0.144.1\"}}\n"));
        members.emplace(
            child_artifact,
            text_bytes(
                std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
                "\"cwd\":\"" + workspace.generic_string() +
                "\",\"cli_version\":\"0.144.1\"}}\n"));
      } else {
        members.emplace(
            record.artifacts.front(),
            text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                       workspace.generic_string() +
                       "\",\"version\":\"2.1.207\"}\n"));
      }

      const auto image = stage_then_pack(
          root,
          test.agent == "codex" ? biv::adapters::codex_adapter()
                                : biv::adapters::claude_code_adapter(),
          record, members);

      REQUIRE(image.manifest.agent_sessions.size() == 1U);
      CHECK(image.manifest.agent_sessions.front().original_session_ids.primary ==
            test.original_id);
      if (test.agent == "codex") {
        REQUIRE(image.manifest.agent_sessions.front().children.size() == 1U);
      }
      std::filesystem::remove_all(root);
    }
  }
}

TEST_CASE(
    "G-3 Claude consent-no establishes manifest version for a nested staged round trip") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000601";
  const auto root = make_tmp("claude-staged-version-establishment");
  const auto original_workspace = root / "original-workspace";
  auto record = round_trip_record("claude-code", session_id,
                                  original_workspace);
  const auto nested = "agents/claude-code/" + std::string{session_id} +
                      "/subagents/workflows/wf-a/agent-nested.jsonl";
  record.children = {{.original_id = "agent-nested",
                      .artifacts = {nested}}};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{session_id} +
                 "\"}\n"));
  members.emplace(
      nested,
      text_bytes(std::string{"{\"type\":\"assistant\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{session_id} +
                 "\",\"agentId\":\"agent-nested\"}\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::claude_code_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().original_session_ids.primary ==
        session_id);
  CHECK(image.manifest.agent_sessions.front().agent_version_at_pack ==
        "2.1.211");
  REQUIRE(image.manifest.agent_sessions.front().children.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().children.front().original_id ==
        "agent-nested");
  REQUIRE(image.manifest.agent_sessions.front().children.front().artifacts.size() ==
          1U);
  CHECK(image.manifest.agent_sessions.front().children.front().artifacts.front().find(
            "subagents/workflows/wf-a/agent-nested.jsonl") !=
        std::string::npos);
  CHECK(std::ranges::any_of(image.members, [](const auto& member) {
    return member.first.find(
               "subagents/workflows/wf-a/agent-nested.jsonl") !=
           std::string::npos;
  }));
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "R-1 Claude consent-no preserves an unattributed nested subagent agentId") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000c21";
  constexpr std::string_view alias =
      "00000000-0000-4000-8000-000000000c22";
  const auto root = make_tmp("claude-staged-unattributed-alias");
  const auto original_workspace = root / "original-workspace";
  auto record = round_trip_record("claude-code", session_id,
                                  original_workspace);
  const auto nested = "agents/claude-code/" + std::string{session_id} +
                      "/subagents/workflows/wf-a/agent-unattributed.jsonl";
  record.artifacts.push_back(nested);
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{session_id} +
                 "\",\"version\":\"2.1.211\"}\n"));
  members.emplace(
      nested,
      text_bytes(std::string{"{\"type\":\"assistant\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{session_id} +
                 "\",\"agentId\":\"" + std::string{alias} + "\"}\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::claude_code_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().children.empty());
  const auto packed_nested = std::ranges::find_if(
      image.members, [](const auto& member) {
        return member.first.find("agent-unattributed.jsonl") !=
               std::string::npos;
      });
  REQUIRE(packed_nested != image.members.end());
  const auto packed_text = byte_string(as_span(packed_nested->second));
  CHECK(packed_text.find("\"agentId\":\"" + std::string{alias} + "\"") !=
        std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "R-1b Codex parent-valued child session identity survives staged repack") {
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c01";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c02";
  const auto root = make_tmp("codex-parent-session-id-round-trip");
  const auto original_workspace = root / "original-workspace";
  auto record = round_trip_record("codex", parent_id, original_workspace);
  const auto child_artifact =
      "agents/codex/" + std::string{child_id} + ".jsonl";
  record.children = {{.original_id = std::string{child_id},
                      .artifacts = {child_artifact}}};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{parent_id} + "\",\"session_id\":\"" +
                 std::string{parent_id} + "\",\"cwd\":\"" +
                 original_workspace.generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));
  members.emplace(
      child_artifact,
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"session_id\":\""} +
                 std::string{parent_id} + "\",\"parent_thread_id\":\"" +
                 std::string{parent_id} + "\",\"cwd\":\"" +
                 original_workspace.generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::codex_adapter(), record, members);

  REQUIRE(image.manifest.agent_sessions.size() == 1U);
  REQUIRE(image.manifest.agent_sessions.front().children.size() == 1U);
  CHECK(image.manifest.agent_sessions.front().children.front().original_id ==
        child_id);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "R-1b Codex staged reader accepts a separately mapped in-image parent reference") {
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c03";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c04";
  const auto root = make_tmp("codex-separate-parent-round-trip");
  const auto original_workspace = root / "original-workspace";
  auto parent = round_trip_record("codex", parent_id, original_workspace);
  auto child = round_trip_record("codex", child_id, original_workspace);
  child.original_session_ids.parent = std::string{parent_id};
  std::array records{parent, child};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      parent.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{parent_id} + "\",\"session_id\":\"" +
                 std::string{parent_id} + "\",\"cwd\":\"" +
                 original_workspace.generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));
  members.emplace(
      child.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{child_id} + "\",\"session_id\":\"" +
                 std::string{parent_id} + "\",\"cwd\":\"" +
                 original_workspace.generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));

  const auto image = stage_then_pack(
      root, biv::adapters::codex_adapter(),
      std::span<const biv::manifest::AgentSessionEntry>{records}, members);

  REQUIRE(image.manifest.agent_sessions.size() == 2U);
  CHECK(std::ranges::any_of(image.manifest.agent_sessions, [&](const auto& row) {
    return row.original_session_ids.primary == parent_id;
  }));
  const auto packed_child = std::ranges::find(
      image.manifest.agent_sessions, child_id,
      [](const auto& row) { return row.original_session_ids.primary; });
  REQUIRE(packed_child != image.manifest.agent_sessions.end());
  CHECK(packed_child->original_session_ids.parent ==
        std::optional<std::string>{parent_id});
  CHECK_FALSE(packed_child->original_session_ids.parent_in_image.has_value());
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "X-3 Codex staged reader skips one conflicting row and keeps its sibling") {
  constexpr std::string_view parent_original =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c05";
  constexpr std::string_view child_original =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0c06";
  constexpr std::string_view parent_minted =
      "019f1d8c-e200-7000-8000-000000000007";
  constexpr std::string_view child_minted =
      "019f1d8c-e200-7000-8000-000000000008";
  const auto root = make_tmp("codex-conflicting-staged-parents");
  const auto source = root / "workspace";
  const auto sessions = source / ".biv/agents/codex/sessions/2026/07/01";
  write_file(source / "work.txt", "workspace\n");
  write_file(
      sessions / ("rollout-2026-07-01T12-00-00-" +
                  std::string{parent_minted} + ".jsonl"),
      std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
          std::string{parent_minted} + "\",\"session_id\":\"" +
          std::string{parent_minted} + "\",\"cwd\":\"" +
          source.generic_string() +
          "\",\"cli_version\":\"0.144.1\"}}\n");
  write_file(
      sessions / ("rollout-2026-07-01T12-00-00-" +
                  std::string{child_minted} + ".jsonl"),
      std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
          std::string{child_minted} + "\",\"session_id\":\"" +
          std::string{parent_minted} + "\",\"parent_thread_id\":\"" +
          std::string{parent_minted} +
          "\",\"source\":{\"subagent\":{\"thread_spawn\":{"
          "\"parent_thread_id\":\"" +
          std::string{child_minted} + "\"}}},\"cwd\":\"" +
          source.generic_string() +
          "\",\"cli_version\":\"0.144.1\"}}\n");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{"{\"id_map\":[{\"agent\":\"codex\","
                  "\"image_session_id\":\""} +
          std::string{parent_original} + "\",\"installed_session_id\":\"" +
          std::string{parent_minted} +
          "\",\"children\":[]},{\"agent\":\"codex\","
          "\"image_session_id\":\"" +
          std::string{child_original} + "\",\"installed_session_id\":\"" +
          std::string{child_minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"" +
          std::string{parent_original} + "\",\"" +
          std::string{child_original} +
          "\"],\"pair_set_applied\":[[\"/original\",\"" +
          source.generic_string() + "\"]]}");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "absent-home").string()};

  const auto packed = biv::pack::pack(source);

  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 1U);
  CHECK(packed->agent_sessions.front().original_session_ids.primary ==
        parent_original);
  CHECK(std::ranges::any_of(
      packed->warnings, [&](const biv::pack::Warning& warning) {
        return warning.kind == "StagedSessionIdentityMismatch" &&
               warning.path.ends_with(std::string{child_minted} + ".jsonl");
      }));
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "R-9 Claude version establishment is stable across staged repack cycles") {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-000000000c11";
  const auto root = make_tmp("claude-version-cycle");
  const auto original_workspace = root / "original-workspace";
  auto record = round_trip_record("claude-code", session_id,
                                  original_workspace);
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"user\",\"cwd\":\""} +
                 original_workspace.generic_string() +
                 "\",\"sessionId\":\"" + std::string{session_id} +
                 "\"}\n"));

  const auto first = stage_then_pack(
      root / "cycle-1", biv::adapters::claude_code_adapter(), record,
      members);
  REQUIRE(first.manifest.agent_sessions.size() == 1U);
  auto second_record = first.manifest.agent_sessions.front();
  auto second_members = first.members;
  const auto second = stage_then_pack(
      root / "cycle-2", biv::adapters::claude_code_adapter(), second_record,
      second_members);

  REQUIRE(second.manifest.agent_sessions.size() == 1U);
  CHECK(first.manifest.agent_sessions.front().agent_version_at_pack ==
        "2.1.211");
  CHECK(second.manifest.agent_sessions.front().agent_version_at_pack ==
        "2.1.211");
  const auto first_main = byte_string(first.members.at(
      first.manifest.agent_sessions.front().artifacts.front()));
  const auto second_main = byte_string(second.members.at(
      second.manifest.agent_sessions.front().artifacts.front()));
  const auto version_needle = std::string{"\"version\":\"2.1.211\""};
  REQUIRE(first_main.find(version_needle) != std::string::npos);
  CHECK(first_main.find(version_needle,
                        first_main.find(version_needle) + 1U) ==
        std::string::npos);
  REQUIRE(second_main.find(version_needle) != std::string::npos);
  CHECK(second_main.find(version_needle,
                         second_main.find(version_needle) + 1U) ==
        std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "G-2 Codex divergent payload identities refuse one row and the clean sibling re-packs") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0b01";
  constexpr std::string_view foreign_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0b02";
  constexpr std::string_view clean_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0b03";
  const auto root = make_tmp("codex-identity-refusal-round-trip");
  const auto staging_workspace = root / "staging-workspace";
  const auto staging_store = root / "staging-store";
  std::filesystem::create_directories(staging_workspace);
  std::filesystem::create_directories(staging_store);
  auto refused = round_trip_record("codex", refused_id, root / "original");
  auto clean = round_trip_record("codex", clean_id, root / "original");
  std::array records{refused, clean};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      refused.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{refused_id} + "\",\"session_id\":\"" +
                 std::string{foreign_id} +
                 "\",\"cwd\":\"" + (root / "original").generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));
  members.emplace(
      clean.artifacts.front(),
      text_bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{clean_id} + "\",\"session_id\":\"" +
                 std::string{clean_id} +
                 "\",\"cwd\":\"" + (root / "original").generic_string() +
                 "\",\"cli_version\":\"0.144.1\"}}\n"));

  biv::manifest::Manifest manifest;
  manifest.agent_sessions.assign(records.begin(), records.end());
  biv::core_sessions::SessionPreview preview;
  preview.agents.push_back(biv::core_sessions::AgentPreview{
      .agent = "codex",
      .parent_count = 2U,
      .known_adapter = true,
      .caps = round_trip_capabilities("codex"),
      .store = biv::adapters::Store{.root = staging_store,
                                    .locators = {},
                                    .tier = biv::adapters::DiscoveryTier::env,
                                    .archived = false},
      .adapter = &biv::adapters::codex_adapter()});
  biv::core_sessions::ConsentDecision consent;
  consent.per_agent.emplace_back("codex", false);
  const auto reader = [&](const std::string_view path)
      -> biv::expected<std::vector<std::byte>> {
    return members.at(std::string{path});
  };

  const auto staged = biv::core_sessions::run_session_leg(
      preview, consent, manifest, staging_workspace, reader);

  REQUIRE(staged);
  REQUIRE(staged->rows.size() == 2U);
  CHECK(staged->rows.at(0).row ==
        biv::core_sessions::SessionRowReport::Row::containment_refused);
  CHECK(staged->rows.at(0).detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  CHECK(staged->rows.at(1).row ==
        biv::core_sessions::SessionRowReport::Row::sessions_staged);
  REQUIRE(staged->id_map.size() == 1U);
  CHECK(staged->id_map.front().image_session_id == clean_id);
  write_file(staging_workspace / "work.txt", "workspace\n");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "absent-home").string()};
  const auto packed = biv::pack::pack(staging_workspace);
  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 1U);
  CHECK(packed->agent_sessions.front().original_session_ids.primary ==
        clean_id);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "G-1 missing staged version skips one row without losing same-adapter or other-adapter siblings") {
  struct Case {
    std::string_view agent;
    std::string_view original;
    std::string_view minted;
    std::string_view same_original;
    std::string_view same_minted;
    std::string_view other_agent;
    std::string_view other_original;
    std::string_view other_minted;
  };
  for (const auto& test : std::array{
           Case{"codex", "cx-0001",
                "019f1d8c-e200-7000-8000-000000000001", "cx-0003",
                "019f1d8c-e200-7000-8000-000000000003", "claude-code",
                "cl-0002", "4c1e9a20-0000-4000-8000-000000000002"},
           Case{"claude-code", "cl-0001",
                "4c1e9a20-0000-4000-8000-000000000001", "cl-0003",
                "4c1e9a20-0000-4000-8000-000000000003", "codex",
                "cx-0002", "019f1d8c-e200-7000-8000-000000000002"}}) {
    DYNAMIC_SECTION(test.agent) {
      const auto root = make_tmp("staged-missing-version-" +
                                 std::string{test.agent});
      const auto source = root / "workspace";
      write_file(source / "work.txt", "workspace");
      if (test.agent == "codex") {
        write_file(
            source /
                (".biv/agents/codex/sessions/2026/07/01/"
                 "rollout-2026-07-01T12-00-00-" +
                 std::string{test.minted} + ".jsonl"),
            std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                std::string{test.minted} + "\",\"session_id\":\"" +
                std::string{test.minted} + "\",\"cwd\":\"" +
                source.generic_string() + "\"}}\n");
      } else {
        write_file(
            source /
                (".biv/agents/claude-code/projects/-home-packer-proj/" +
                 std::string{test.minted} + ".jsonl"),
            std::string{"{\"type\":\"user\",\"cwd\":\""} +
                source.generic_string() + "\",\"sessionId\":\"" +
                std::string{test.minted} + "\"}\n");
      }
      if (test.agent == "codex") {
        write_file(
            source /
                (".biv/agents/codex/sessions/2026/07/01/"
                 "rollout-2026-07-01T12-00-00-" +
                 std::string{test.same_minted} + ".jsonl"),
            std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                std::string{test.same_minted} + "\",\"session_id\":\"" +
                std::string{test.same_minted} + "\",\"cwd\":\"" +
                source.generic_string() +
                "\",\"cli_version\":\"0.142.5\"}}\n");
      } else {
        write_file(
            source /
                (".biv/agents/claude-code/projects/-home-packer-proj/" +
                 std::string{test.same_minted} + ".jsonl"),
            std::string{"{\"type\":\"user\",\"cwd\":\""} +
                source.generic_string() + "\",\"sessionId\":\"" +
                std::string{test.same_minted} +
                "\",\"version\":\"2.1.207\"}\n");
      }
      if (test.other_agent == "codex") {
        write_file(
            source /
                (".biv/agents/codex/sessions/2026/07/01/"
                 "rollout-2026-07-01T12-00-00-" +
                 std::string{test.other_minted} + ".jsonl"),
            std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                std::string{test.other_minted} + "\",\"session_id\":\"" +
                std::string{test.other_minted} + "\",\"cwd\":\"" +
                source.generic_string() +
                "\",\"cli_version\":\"0.142.5\"}}\n");
      } else {
        write_file(
            source /
                (".biv/agents/claude-code/projects/-home-packer-proj/" +
                 std::string{test.other_minted} + ".jsonl"),
            std::string{"{\"type\":\"user\",\"cwd\":\""} +
                source.generic_string() + "\",\"sessionId\":\"" +
                std::string{test.other_minted} +
                "\",\"version\":\"2.1.207\"}\n");
      }
      write_file(
          source / ".biv/agents/manifest.json",
          std::string{"{\"id_map\":[{\"agent\":\""} +
              std::string{test.agent} + "\",\"image_session_id\":\"" +
              std::string{test.original} +
              "\",\"installed_session_id\":\"" +
              std::string{test.minted} +
              "\",\"children\":[]},{\"agent\":\"" + std::string{test.agent} +
              "\",\"image_session_id\":\"" + std::string{test.same_original} +
              "\",\"installed_session_id\":\"" + std::string{test.same_minted} +
              "\",\"children\":[]},{\"agent\":\"" +
              std::string{test.other_agent} +
              "\",\"image_session_id\":\"" +
              std::string{test.other_original} +
              "\",\"installed_session_id\":\"" +
              std::string{test.other_minted} +
              "\",\"children\":[]}],\"provenance_chain\":[\"" +
              std::string{test.original} +
              "\",\"" + std::string{test.same_original} +
              "\",\"" + std::string{test.other_original} +
              "\"],\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
              source.generic_string() + "\"]]}" );
      const ScopedEnv codex_home{"CODEX_HOME",
                                 (root / "absent-codex").string()};
      const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                                  (root / "absent-claude").string()};
      const ScopedEnv home{"HOME", (root / "home").string()};

      const auto report = biv::pack::pack(source);

      REQUIRE(report);
      REQUIRE(report->agent_sessions.size() == 2U);
      CHECK(std::ranges::any_of(report->agent_sessions, [&](const auto& row) {
        return row.agent == test.agent &&
               row.original_session_ids.primary == test.same_original;
      }));
      CHECK(std::ranges::any_of(report->agent_sessions, [&](const auto& row) {
        return row.agent == test.other_agent &&
               row.original_session_ids.primary == test.other_original;
      }));
      CHECK(std::ranges::any_of(
          report->warnings, [](const biv::pack::Warning& warning) {
            return warning.kind == "StagedSessionVersionMissing";
          }));
      CHECK(std::filesystem::exists(root / "workspace.bvpk"));
      std::filesystem::remove_all(root);
    }
  }
}

TEST_CASE("Codex staged reader accepts a global cross-agent path set") {
  constexpr std::string_view codex_minted =
      "019f1d8c-e200-7000-8000-000000000001";
  constexpr std::string_view claude_minted =
      "4c1e9a20-0000-4000-8000-000000000001";
  const auto root = make_tmp("staged-sidecar-cross-agent-paths");
  const auto source = root / "workspace";
  write_file(source / "work.txt", "workspace");
  write_file(
      source /
          (".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
           std::string{codex_minted} + ".jsonl"),
      std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
          std::string{codex_minted} + "\",\"session_id\":\"" +
          std::string{codex_minted} + "\",\"cwd\":\"" +
          source.generic_string() + "\",\"cli_version\":\"0.142.5\"}}\n");
  write_file(
      source /
          (".biv/agents/claude-code/projects/-home-packer-claude/" +
           std::string{claude_minted} + ".jsonl"),
      std::string{"{\"type\":\"user\",\"cwd\":\""} +
          source.generic_string() + "\",\"sessionId\":\"" +
          std::string{claude_minted} + "\",\"version\":\"2.1.207\"}\n");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0001\",\"installed_session_id\":\""} +
          std::string{claude_minted} +
          "\",\"children\":[]},{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\"" +
          std::string{codex_minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\",\"cx-0001\"],"
          "\"pair_set_applied\":[[\"/home/packer/claude\",\"" +
          source.generic_string() +
          "\"],[\"/home/packer/codex\",\"" + source.generic_string() +
          "\"]]}");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto packed = biv::pack::pack(source);

  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 2U);
  const auto codex = std::ranges::find(
      packed->agent_sessions, std::string_view{"codex"},
      [](const auto& entry) { return std::string_view{entry.agent}; });
  const auto claude = std::ranges::find(
      packed->agent_sessions, std::string_view{"claude-code"},
      [](const auto& entry) { return std::string_view{entry.agent}; });
  REQUIRE(codex != packed->agent_sessions.end());
  REQUIRE(claude != packed->agent_sessions.end());
  CHECK(codex->original_path == "/home/packer/codex");
  CHECK(codex->original_session_ids.primary == "cx-0001");
  CHECK(claude->original_path == "/home/packer/claude");
  CHECK(claude->original_session_ids.primary == "cl-0001");
  std::filesystem::remove_all(root);
}

TEST_CASE("Codex staged reader collapses multiple spellings of one origin") {
  constexpr std::string_view minted =
      "019f1d8c-e200-7000-8000-000000000001";
  const auto root = make_tmp("staged-sidecar-codex-path-spellings");
  const auto source = root / "workspace";
  write_file(source / "work.txt", "workspace");
  write_file(
      source /
          (".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
           std::string{minted} + ".jsonl"),
      std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
          std::string{minted} + "\",\"session_id\":\"" +
          std::string{minted} + "\",\"cwd\":\"" +
          source.generic_string() + "\",\"cli_version\":\"0.142.5\"}}\n");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{"{\"id_map\":[{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\""} +
          std::string{minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"cx-0001\"],"
          "\"pair_set_applied\":[[\"/mnt/c/Users/Me/Proj\",\"" +
          source.generic_string() +
          "\"],[\"/mnt/c/users/me/proj\",\"" + source.generic_string() +
          "\"],[\"C:/Users/Me/Proj\",\"" + source.generic_string() +
          "\"],[\"C:\\\\Users\\\\Me\\\\Proj\",\"" +
          source.generic_string() + "\"]]}");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto packed = biv::pack::pack(source);

  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 1U);
  const auto& entry = packed->agent_sessions.front();
  CHECK(entry.agent == "codex");
  CHECK(entry.original_session_ids.primary == "cx-0001");
  CHECK(entry.original_path == "/mnt/c/Users/Me/Proj");
  CHECK(entry.path_flavor == biv::manifest::PathFlavor::wsl);
  std::filesystem::remove_all(root);
}

TEST_CASE("staged sidecars reject malformed and decoy Codex state but row-scope identity mismatches") {
  const auto root = make_tmp("staged-sidecar-rejections");
  const auto source = root / "workspace";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};
  const auto sidecar = source / ".biv/agents/manifest.json";
  const auto valid = std::string{"{\"id_map\":[{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\"019f1d8c-e200-7000-8000-000000000001\",\"children\":[]}],\"provenance_chain\":[\"cx-0001\"],\"pair_set_applied\":[[\"/home/packer/proj\",\""} + source.generic_string() + "\"]]}";
  const auto expect_error = [&] { CHECK_FALSE(biv::pack::pack(source).has_value()); };
  write_file(sidecar, "{bad"); expect_error();
  write_file(sidecar, "{}"); expect_error();
  write_file(sidecar, valid);
  const auto decoy = source / ".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-prefix-019f1d8c-e200-7000-8000-000000000001-suffix.jsonl";
  write_file(decoy, "{\"type\":\"session_meta\",\"payload\":{\"id\":\"019f1d8c-e200-7000-8000-000000000001\",\"session_id\":\"019f1d8c-e200-7000-8000-000000000001\"}}\n");
  expect_error();
  std::filesystem::remove(decoy);
  const auto exact = source / ".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-019f1d8c-e200-7000-8000-000000000001.jsonl";
  write_file(exact, "{\"type\":\"session_meta\",\"payload\":{\"id\":\"wrong\",\"session_id\":\"wrong\"}}\n");
  const auto mismatched = biv::pack::pack(source);
  REQUIRE(mismatched);
  CHECK(mismatched->agent_sessions.empty());
  CHECK(std::ranges::any_of(
      mismatched->warnings, [&](const biv::pack::Warning& warning) {
        return warning.kind == "StagedSessionIdentityMismatch" &&
               warning.path == exact.generic_string();
      }));
  std::filesystem::remove(exact);
  const auto external = root / "external.json"; write_file(external, valid);
  std::filesystem::remove(sidecar); std::filesystem::create_symlink(external, sidecar);
  expect_error();
  std::filesystem::remove(sidecar); std::filesystem::create_symlink(root / "missing.json", sidecar);
  expect_error();
  std::filesystem::remove_all(root);
}

TEST_CASE("staged sidecars require exact unique Codex dated locations") {
  const auto root = make_tmp("staged-codex-exact-location");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};
  constexpr std::string_view minted =
      "019f1d8c-e200-7000-8000-000000000001";
  constexpr std::string_view child_minted =
      "019f1d8c-e200-7000-8000-000000000002";

  const auto transcript = [](const std::string_view id,
                             const std::filesystem::path& source) {
    return std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
           std::string{id} + "\",\"session_id\":\"" + std::string{id} +
           "\",\"cwd\":\"" + source.generic_string() +
           "\",\"cli_version\":\"0.142.5\"}}\n";
  };
  const auto sidecar = [&](const std::filesystem::path& source,
                          const std::string_view children,
                          const bool include_child) {
    return std::string{"{\"id_map\":[{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\""} +
           std::string{minted} + "\",\"children\":" + std::string{children} +
           "}],\"provenance_chain\":[\"cx-0001\"" +
           (include_child ? std::string{",\"cx-child\""} : std::string{}) +
           "],\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
           source.generic_string() + "\"]]}";
  };
  const auto reject = [&](const std::string_view name,
                          const std::vector<std::pair<std::filesystem::path,
                                                      std::string>>& files,
                          const std::string_view children = "[]",
                          const bool include_child = false) {
    const auto source = root / std::string{name} / "workspace";
    write_file(source / "work.txt", "workspace");
    write_file(source / ".biv/agents/manifest.json",
               sidecar(source, children, include_child));
    for (const auto& [relative, content] : files) {
      write_file(source / relative, content);
    }
    CAPTURE(name);
    CHECK_FALSE(biv::pack::pack(source).has_value());
  };

  const auto exact = std::filesystem::path{
      ".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
      std::string{minted} + ".jsonl"};
  const auto evil = std::filesystem::path{
      ".biv/agents/codex/sessions/2026/07/01/evil-" +
      std::string{minted} + ".jsonl"};
  const auto wrong_date = std::filesystem::path{
      ".biv/agents/codex/sessions/2026/07/02/rollout-2026-07-02T12-00-00-" +
      std::string{minted} + ".jsonl"};
  reject("evil-name", {{evil, transcript(minted, root / "evil-name/workspace")}});
  reject("wrong-date",
         {{wrong_date, transcript(minted, root / "wrong-date/workspace")}});
  reject("duplicate",
         {{exact, transcript(minted, root / "duplicate/workspace")},
          {evil, transcript(minted, root / "duplicate/workspace")}});

  const auto child_wrong = std::filesystem::path{
      ".biv/agents/codex/sessions/2026/07/02/rollout-2026-07-02T12-00-00-" +
      std::string{child_minted} + ".jsonl"};
  const auto child_map = std::string{"[[\"cx-child\",\""} +
                         std::string{child_minted} + "\"]]";
  reject("child-wrong-date",
         {{exact, transcript(minted, root / "child-wrong-date/workspace")},
          {child_wrong,
           transcript(child_minted, root / "child-wrong-date/workspace")}},
         child_map, true);
  std::filesystem::remove_all(root);
}

TEST_CASE("staged sidecars require exact unique Claude project locations and subtree classes") {
  const auto root = make_tmp("staged-claude-exact-location");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};
  constexpr std::string_view minted =
      "4c1e9a20-0000-4000-8000-000000000001";
  const auto sidecar = [&](const std::filesystem::path& source) {
    return std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0001\",\"installed_session_id\":\""} +
           std::string{minted} +
           "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\"],\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
           source.generic_string() + "\"]]}";
  };
  const auto transcript = [&](const std::filesystem::path& source) {
    return std::string{"{\"type\":\"user\",\"cwd\":\""} +
           source.generic_string() + "\",\"sessionId\":\"" +
           std::string{minted} + "\",\"version\":\"2.1.207\"}\n";
  };
  const auto reject = [&](const std::string_view name,
                          const std::vector<std::pair<std::filesystem::path,
                                                      std::string>>& files) {
    const auto source = root / std::string{name} / "workspace";
    write_file(source / "work.txt", "workspace");
    write_file(source / ".biv/agents/manifest.json", sidecar(source));
    for (const auto& [relative, content] : files) {
      write_file(source / relative, content);
    }
    CAPTURE(name);
    CHECK_FALSE(biv::pack::pack(source).has_value());
  };
  const auto exact = std::filesystem::path{
      ".biv/agents/claude-code/projects/-home-packer-proj/" +
      std::string{minted} + ".jsonl"};
  const auto wrong = std::filesystem::path{
      ".biv/agents/claude-code/projects/wrong-project/" +
      std::string{minted} + ".jsonl"};
  reject("wrong-project",
         {{wrong, transcript(root / "wrong-project/workspace")}});
  reject("duplicate-project",
         {{exact, transcript(root / "duplicate-project/workspace")},
          {wrong, transcript(root / "duplicate-project/workspace")}});
  reject("mismatched-main-identity",
         {{exact,
           std::string{"{\"type\":\"user\",\"cwd\":\""} +
               (root / "mismatched-main-identity/workspace").generic_string() +
               "\",\"sessionId\":\"wrong\",\"version\":\"2.1.207\"}\n"}});
  reject("mismatched-subagent-identity",
         {{exact,
           transcript(root / "mismatched-subagent-identity/workspace")},
          {std::filesystem::path{
               ".biv/agents/claude-code/projects/-home-packer-proj/" +
               std::string{minted} + "/subagents/agent-a.jsonl"},
           "{\"sessionId\":\"wrong\"}\n"}});
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "T-1 T-2 staged Claude collection warns for denied and unknown regular files") {
  const auto root = make_tmp("staged-claude-unknown-file");
  const auto source = root / "workspace";
  constexpr std::string_view minted =
      "4c1e9a20-0000-4000-8000-000000000011";
  write_file(source / "work.txt", "workspace");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0011\",\"installed_session_id\":\""} +
          std::string{minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"cl-0011\"],\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
          source.generic_string() + "\"]]}" );
  const auto session_root =
      source / ".biv/agents/claude-code/projects/-home-packer-proj";
  write_file(
      session_root / (std::string{minted} + ".jsonl"),
      std::string{"{\"type\":\"user\",\"cwd\":\""} +
          source.generic_string() + "\",\"sessionId\":\"" +
          std::string{minted} + "\",\"version\":\"2.1.211\"}\n");
  write_file(session_root / std::string{minted} / "history.jsonl", "denied\n");
  write_file(session_root / std::string{minted} / "notes.md", "unknown\n");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto packed = biv::pack::pack(source);

  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 1U);
  CHECK(packed->agent_sessions.front().original_session_ids.primary ==
        "cl-0011");
  CHECK(std::ranges::any_of(
      packed->warnings, [](const biv::pack::Warning& warning) {
        return warning.kind == "StagedSessionArtifactSkipped" &&
               warning.path.ends_with("history.jsonl");
      }));
  CHECK(std::ranges::any_of(
      packed->warnings, [](const biv::pack::Warning& warning) {
        return warning.kind == "StagedSessionArtifactSkipped" &&
               warning.path.ends_with("notes.md");
      }));
  std::filesystem::remove_all(root);
}

TEST_CASE("staged sidecars reject malformed rows and sealed associations") {
  struct Malformed {
    std::string_view name;
    std::string_view id_map;
    std::string_view provenance;
    std::string_view pairs;
  };
  const std::array cases{
      Malformed{"missing-agent",
                R"([{"image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"ill-typed-agent",
                R"([{"agent":7,"image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"unknown-agent",
                R"([{"agent":"unknown","image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"missing-image",
                R"([{"agent":"codex","installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"ill-typed-image",
                R"([{"agent":"codex","image_session_id":7,"installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"missing-installed",
                R"([{"agent":"claude-code","image_session_id":"cl-0001","children":[]}])",
                R"(["cl-0001"])", "PAIR"},
      Malformed{"ill-typed-installed",
                R"([{"agent":"claude-code","image_session_id":"cl-0001","installed_session_id":7,"children":[]}])",
                R"(["cl-0001"])", "PAIR"},
      Malformed{"missing-children",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted"}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"ill-typed-children",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":"none"}])",
                R"(["cx-0001"])", "PAIR"},
      Malformed{"malformed-child",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":[["child"]]}])",
                R"(["cx-0001","child"])", "PAIR"},
      Malformed{"ill-typed-provenance",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"([7,"cx-0001"])", "PAIR"},
      Malformed{"missing-provenance",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"(["some-other-id"])", "PAIR"},
      Malformed{"ill-typed-pair",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":[]}])",
                R"(["cx-0001"])", R"([7,"TARGET"] )"},
      Malformed{"malformed-other-supported-row",
                R"([{"agent":"codex","image_session_id":"cx-0001","installed_session_id":"minted","children":[]},{"agent":"claude-code","image_session_id":"cl-bad","children":[]}])",
                R"(["cl-bad","cx-0001"])", "PAIR"},
  };

  const auto root = make_tmp("staged-sidecar-malformed-rows");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};
  for (const auto& test : cases) {
    DYNAMIC_SECTION(test.name) {
      const auto source = root / std::string{test.name} / "workspace";
      write_file(source / "work.txt", "workspace");
      auto pairs = std::string{test.pairs};
      if (pairs == "PAIR") {
        pairs = "[[\"/home/packer/proj\",\"" + source.generic_string() +
                "\"]]";
      } else {
        const auto target = pairs.find("TARGET");
        if (target != std::string::npos) {
          pairs.replace(target, 6U, source.generic_string());
        }
      }
      write_file(source / ".biv/agents/manifest.json",
                 "{\"id_map\":" + std::string{test.id_map} +
                     ",\"provenance_chain\":" +
                     std::string{test.provenance} +
                     ",\"pair_set_applied\":" + pairs + "}");
      const auto packed = biv::pack::pack(source);
      REQUIRE_FALSE(packed.has_value());
      CHECK(packed.error().detail == "invalid_staged_sidecar");
    }
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-A11-3 malformed present original_path fails at parse") {
  struct Case {
    std::string_view name;
    std::string_view member;
  };
  const std::array cases{
      Case{"empty", R"("original_path":"",)"},
      Case{"wrong-type", R"("original_path":7,)"},
      Case{"duplicate",
           R"("original_path":"/home/packer/proj","original_path":"/home/packer/proj",)"},
  };
  const auto root = make_tmp("a11-malformed-present-row-path");
  const ScopedEnv codex_home{"CODEX_HOME",
                             (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};
  for (const auto& test : cases) {
    DYNAMIC_SECTION(test.name) {
      const auto source = root / std::string{test.name} / "workspace";
      write_file(source / "work.txt", "workspace");
      write_file(
          source / ".biv/agents/manifest.json",
          std::string{"{\"id_map\":[{\"agent\":\"codex\","} +
              std::string{test.member} +
              "\"image_session_id\":\"cx-0001\"," +
              "\"installed_session_id\":\"minted\",\"children\":[]}]," +
              "\"provenance_chain\":[\"cx-0001\"]," +
              "\"pair_set_applied\":[[\"/home/packer/proj\",\"" +
              source.generic_string() + "\"]]}" );

      const auto sidecar = source / ".biv/agents/manifest.json";
      const auto sidecar_text =
          byte_string(as_span(read_file_bytes(sidecar)));
      const auto parsed = biv::adapters::rewrite::parse_staged_sidecar(
          sidecar, sidecar_text, source);

      REQUIRE_FALSE(parsed);
      CHECK(parsed.error().kind == biv::ErrKind::ParseError);
      CHECK(parsed.error().detail == "invalid_staged_sidecar");
    }
  }
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "FX-A11-4 well-formed original_path outside audit set refuses") {
  const auto root = make_tmp("a11-row-path-outside-audit-set");
  const auto source = root / "workspace";
  write_file(source / "work.txt", "workspace");
  const ScopedEnv codex_home{"CODEX_HOME",
                             (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto expect_refusal = [&](const std::string_view row_path,
                                  const std::string_view pair_path,
                                  const std::filesystem::path& pair_target) {
    const auto sidecar = source / ".biv/agents/manifest.json";
    write_file(
        sidecar,
        std::string{
            "{\"id_map\":[{\"agent\":\"codex\",\"original_path\":\""} +
            std::string{row_path} +
            "\",\"image_session_id\":\"cx-0001\","
            "\"installed_session_id\":\"minted\",\"children\":[]}],"
            "\"provenance_chain\":[\"cx-0001\"],"
            "\"pair_set_applied\":[[\"" + std::string{pair_path} +
            "\",\"" + pair_target.generic_string() + "\"]]}" );
    const auto sidecar_text = byte_string(as_span(read_file_bytes(sidecar)));
    const auto parsed = biv::adapters::rewrite::parse_staged_sidecar(
        sidecar, sidecar_text, source);
    REQUIRE_FALSE(parsed);
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
    CHECK(parsed.error().detail == "invalid_staged_sidecar");
  };

  SECTION("missing exact pair") {
    expect_refusal("/home/packer/outside", "/home/packer/inside", source);
  }
  SECTION("target mismatch") {
    expect_refusal("/home/packer/proj", "/home/packer/proj",
                   root / "other-workspace");
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-A11-5 mixed original_path presence refuses at parse") {
  const auto root = make_tmp("a11-row-path-mixed-presence");
  const auto source = root / "workspace";
  write_file(source / "work.txt", "workspace");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{
          "{\"id_map\":[{\"agent\":\"codex\","
          "\"original_path\":\"/home/packer/a\","
          "\"image_session_id\":\"cx-0001\","
          "\"installed_session_id\":\"minted-a\",\"children\":[]},{"
          "\"agent\":\"codex\",\"image_session_id\":\"cx-0002\","
          "\"installed_session_id\":\"minted-b\",\"children\":[]}],"
          "\"provenance_chain\":[\"cx-0001\",\"cx-0002\"],"
          "\"pair_set_applied\":[[\"/home/packer/a\",\""} +
          source.generic_string() + "\"],[\"/home/packer/b\",\"" +
          source.generic_string() + "\"]]}" );
  const ScopedEnv codex_home{"CODEX_HOME",
                             (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto sidecar = source / ".biv/agents/manifest.json";
  const auto sidecar_text = byte_string(as_span(read_file_bytes(sidecar)));
  const auto parsed = biv::adapters::rewrite::parse_staged_sidecar(
      sidecar, sidecar_text, source);

  REQUIRE_FALSE(parsed);
  CHECK(parsed.error().kind == biv::ErrKind::ParseError);
  CHECK(parsed.error().detail == "invalid_staged_sidecar");
  std::filesystem::remove_all(root);
}

TEST_CASE("FX-A11-6a Claude provenance uses the validated row value") {
  constexpr std::string_view minted =
      "4c1e9a20-0000-4000-8000-000000000061";
  const auto root = make_tmp("a11-claude-row-provenance");
  const auto source = root / "workspace";
  write_file(source / "work.txt", "workspace");
  write_file(
      source /
          (".biv/agents/claude-code/projects/-home-packer-location/" +
           std::string{minted} + ".jsonl"),
      std::string{"{\"type\":\"user\",\"cwd\":\""} +
          source.generic_string() + "\",\"sessionId\":\"" +
          std::string{minted} + "\",\"version\":\"2.1.207\"}\n");
  write_file(
      source / ".biv/agents/manifest.json",
      std::string{
          "{\"id_map\":[{\"agent\":\"claude-code\","
          "\"original_path\":\"/home/packer/provenance\","
          "\"image_session_id\":\"cl-0001\","
          "\"installed_session_id\":\""} +
          std::string{minted} +
          "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\"],"
          "\"pair_set_applied\":[[\"/home/packer/location\",\"" +
          source.generic_string() +
          "\"],[\"/home/packer/provenance\",\"" +
          source.generic_string() + "\"]]}" );
  const ScopedEnv codex_home{"CODEX_HOME",
                             (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto packed = biv::pack::pack(source);

  REQUIRE(packed);
  REQUIRE(packed->agent_sessions.size() == 1U);
  CHECK(packed->agent_sessions.front().original_path ==
        "/home/packer/provenance");
  std::filesystem::remove_all(root);
}

TEST_CASE("staged sidecars resolve only path associations proven by the global sidecar") {
  const auto root = make_tmp("staged-sidecar-multi-entry");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude").string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  SECTION("codex") {
    const auto source = root / "codex-workspace";
    write_file(source / "work.txt", "workspace");
    constexpr std::string_view first =
        "019f1d8c-e200-7000-8000-000000000001";
    constexpr std::string_view second =
        "019f1d8c-e200-7000-8000-000000000002";
    const auto record = [&](const std::string_view id) {
      return std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
             std::string{id} + "\",\"session_id\":\"" + std::string{id} +
             "\",\"cwd\":\"" + source.generic_string() +
             "\",\"cli_version\":\"0.142.5\"}}\n";
    };
    write_file(source / (".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
                         std::string{first} + ".jsonl"),
               record(first));
    write_file(source / (".biv/agents/codex/sessions/2026/07/01/rollout-2026-07-01T12-00-00-" +
                         std::string{second} + ".jsonl"),
               record(second));
    const auto sidecar = [&](const std::string_view pairs) {
      return std::string{"{\"id_map\":[{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\""} +
             std::string{first} +
             "\",\"children\":[]},{\"agent\":\"codex\",\"image_session_id\":\"cx-0002\",\"installed_session_id\":\"" +
             std::string{second} +
             "\",\"children\":[]}],\"provenance_chain\":[\"cx-0001\",\"cx-0002\"],\"pair_set_applied\":" +
             std::string{pairs} + "}";
    };

    SECTION("same origin class is shared by both rows") {
      write_file(source / ".biv/agents/manifest.json",
                 sidecar("[[\"/home/packer/shared\",\"" +
                         source.generic_string() + "\"]]"));
      const auto packed = biv::pack::pack(source);
      REQUIRE(packed);
      REQUIRE(packed->agent_sessions.size() == 2U);
      for (const auto& entry : packed->agent_sessions) {
        CHECK(entry.original_path == "/home/packer/shared");
      }
    }

    SECTION("FX-A11-2 absent row edge preserves ambiguous typed refusal") {
      write_file(source / ".biv/agents/manifest.json",
                 sidecar("[[\"/home/packer/a\",\"" +
                         source.generic_string() +
                         "\"],[\"/home/packer/z\",\"" +
                         source.generic_string() + "\"]]"));
      const auto packed = biv::pack::pack(source);
      REQUIRE_FALSE(packed.has_value());
      CHECK(packed.error().detail == "invalid_staged_sidecar");
    }
  }

  SECTION("cross-agent partial sharing is ambiguous for multiple Codex rows") {
    const auto source = root / "partial-sharing-workspace";
    constexpr std::string_view first =
        "019f1d8c-e200-7000-8000-000000000001";
    constexpr std::string_view second =
        "019f1d8c-e200-7000-8000-000000000002";
    constexpr std::string_view claude =
        "4c1e9a20-0000-4000-8000-000000000001";
    const auto codex_record = [&](const std::string_view id) {
      return std::string{"{\"timestamp\":\"2026-07-01T12:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
             std::string{id} + "\",\"session_id\":\"" + std::string{id} +
             "\",\"cwd\":\"" + source.generic_string() +
             "\",\"cli_version\":\"0.142.5\"}}\n";
    };
    write_file(source / "work.txt", "workspace");
    write_file(source / (".biv/agents/codex/sessions/2026/07/01/"
                         "rollout-2026-07-01T12-00-00-" +
                         std::string{first} + ".jsonl"),
               codex_record(first));
    write_file(source / (".biv/agents/codex/sessions/2026/07/01/"
                         "rollout-2026-07-01T12-00-00-" +
                         std::string{second} + ".jsonl"),
               codex_record(second));
    write_file(source / (".biv/agents/claude-code/projects/-home-packer-a/" +
                         std::string{claude} + ".jsonl"),
               std::string{"{\"type\":\"user\",\"cwd\":\""} +
                   source.generic_string() + "\",\"sessionId\":\"" +
                   std::string{claude} +
                   "\",\"version\":\"2.1.207\"}\n");
    write_file(
        source / ".biv/agents/manifest.json",
        std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0001\",\"installed_session_id\":\""} +
            std::string{claude} +
            "\",\"children\":[]},{\"agent\":\"codex\",\"image_session_id\":\"cx-0001\",\"installed_session_id\":\"" +
            std::string{first} +
            "\",\"children\":[]},{\"agent\":\"codex\",\"image_session_id\":\"cx-0002\",\"installed_session_id\":\"" +
            std::string{second} +
            "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\",\"cx-0001\",\"cx-0002\"],"
            "\"pair_set_applied\":[[\"/home/packer/a\",\"" +
            source.generic_string() + "\"],[\"/home/packer/b\",\"" +
            source.generic_string() + "\"]]}");

    const auto packed = biv::pack::pack(source);

    REQUIRE_FALSE(packed.has_value());
    CHECK(packed.error().detail == "invalid_staged_sidecar");
  }

  SECTION("claude") {
    const auto source = root / "claude-workspace";
    write_file(source / "work.txt", "workspace");
    constexpr std::string_view first =
        "4c1e9a20-0000-4000-8000-000000000001";
    constexpr std::string_view second =
        "4c1e9a20-0000-4000-8000-000000000002";
    const auto record = [&](const std::string_view id) {
      return std::string{"{\"type\":\"user\",\"cwd\":\""} +
             source.generic_string() + "\",\"sessionId\":\"" +
             std::string{id} + "\",\"version\":\"2.1.207\"}\n";
    };
    const auto first_root = source / ".biv/agents/claude-code/projects/-home-packer-a";
    const auto second_root = source / ".biv/agents/claude-code/projects/-home-packer-z";
    write_file(first_root / (std::string{first} + ".jsonl"), record(first));
    write_file(second_root / (std::string{second} + ".jsonl"), record(second));
    write_file(first_root / std::string{first} / "subagents/agent-a.jsonl",
               record(first));
    write_file(first_root / std::string{first} / "subagents/agent-a.meta.json",
               "{\"agentType\":\"explore\"}\n");
    write_file(first_root / std::string{first} / "tool-results/nested/result.txt",
               "tool result\n");
    write_file(
        source / ".biv/agents/manifest.json",
        std::string{"{\"id_map\":[{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0001\",\"installed_session_id\":\""} +
            std::string{first} +
            "\",\"children\":[]},{\"agent\":\"claude-code\",\"image_session_id\":\"cl-0002\",\"installed_session_id\":\"" +
            std::string{second} +
            "\",\"children\":[]}],\"provenance_chain\":[\"cl-0001\",\"cl-0002\"],\"pair_set_applied\":[[\"/home/packer/a\",\"" +
            source.generic_string() + "\"],[\"/home/packer/z\",\"" +
            source.generic_string() + "\"]]}" );

    const auto packed = biv::pack::pack(source);
    REQUIRE(packed);
    REQUIRE(packed->agent_sessions.size() == 2U);
    const auto first_entry = std::ranges::find(
        packed->agent_sessions, std::string_view{"cl-0001"},
        [](const auto& entry) { return std::string_view{entry.original_session_ids.primary}; });
    const auto second_entry = std::ranges::find(
        packed->agent_sessions, std::string_view{"cl-0002"},
        [](const auto& entry) { return std::string_view{entry.original_session_ids.primary}; });
    REQUIRE(first_entry != packed->agent_sessions.end());
    REQUIRE(second_entry != packed->agent_sessions.end());
    CHECK(first_entry->original_path == "/home/packer/a");
    CHECK(second_entry->original_path == "/home/packer/z");
    CHECK(first_entry->children.empty());
    CHECK(first_entry->artifacts ==
          std::vector<std::string>{
              "agents/claude-code/" + std::string{first} + ".jsonl",
              "agents/claude-code/" + std::string{first} +
                  "/subagents/agent-a.jsonl",
              "agents/claude-code/" + std::string{first} +
                  "/subagents/agent-a.meta.json",
              "agents/claude-code/" + std::string{first} +
                  "/tool-results/nested/result.txt"});
  }
  std::filesystem::remove_all(root);
}
