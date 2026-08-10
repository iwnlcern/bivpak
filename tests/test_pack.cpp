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

#include "core/container/tar_reader.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"
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
    std::filesystem::create_directories(source);
    write_file(source / "work.txt", "workspace");
    const auto home_value = row.use_temp_home
                                ? std::optional<std::string>{(root / "home").string()}
                                : row.home;
    const ScopedEnv home{"HOME", home_value};
    const ScopedEnv codex_home{"CODEX_HOME", (root / "codex").string()};
    const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR",
                                  (root / "claude").string()};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
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
    const ScopedEnv home{"HOME", (root / "home").string()};
    const ScopedEnv codex_home{"CODEX_HOME", codex_store.string()};
    const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", claude_store.string()};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
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
    const ScopedEnv home{"HOME", (root / "home").string()};
    const ScopedEnv codex_home{"CODEX_HOME", codex_store.string()};
    const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", claude_store.string()};

    const auto report = biv::pack::pack(source);

    REQUIRE(report.has_value());
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

  auto report = biv::pack::pack(source);
  REQUIRE(report.has_value());
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
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

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
    const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

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
    const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

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
  const ScopedEnv codex_home{"CODEX_HOME", env_store.string()};
  const ScopedEnv home{"HOME", (root / "home").string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", store.string()};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
  const ScopedEnv codex_home{"CODEX_HOME", store.string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
  const ScopedEnv codex_home{"CODEX_HOME", store.string()};

  const auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
                 child + "\",\"session_id\":\"" + child + "\",\"cwd\":\"" +
                 source.generic_string() +
                 "\",\"cli_version\":\"0.142.5\",\"parent_thread_id\":\"" +
                 missing_parent + "\"}}\n");
  const ScopedEnv codex_home{"CODEX_HOME", store.string()};

  auto report = biv::pack::pack(source);

  REQUIRE(report.has_value());
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
