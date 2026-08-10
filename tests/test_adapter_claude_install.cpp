#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <csignal>
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
#include "adapters/secure_io_fstat_seam.hpp"
#include "adapters/version_floor.hpp"
#include "core/open/sessions.hpp"
#include "core/support/probe.hpp"

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

TEST_CASE("Claude FIFO deadline control reports synchronous SIGALRM delivery") {
  ScopedFifoDeadline deadline;
  REQUIRE(::raise(SIGALRM) == 0);
  REQUIRE(fifo_deadline_expired == 1);
}

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
  return fs::canonical(base);
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

void add_claude_members(std::map<std::string, std::vector<std::byte>>& members, const std::string_view session_id) {
  const auto originals = claude_members();
  for (const auto& [path, content] : originals) {
    auto rewritten_path = path;
    auto rewritten_content = text(content);
    for (auto position = rewritten_path.find(kOriginalSession); position != std::string::npos;
         position = rewritten_path.find(kOriginalSession, position)) {
      rewritten_path.replace(position, kOriginalSession.size(), session_id);
      position += session_id.size();
    }
    for (auto position = rewritten_content.find(kOriginalSession); position != std::string::npos;
         position = rewritten_content.find(kOriginalSession, position)) {
      rewritten_content.replace(position, kOriginalSession.size(), session_id);
      position += session_id.size();
    }
    members.emplace(std::move(rewritten_path), bytes(rewritten_content));
  }
}

biv::adapters::InstallTarget target_for(
    fs::path workspace, fs::path store, std::map<std::string, std::vector<std::byte>>& members,
    biv::adapters::Capabilities capabilities = [] {
      return biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::readable,
          std::optional<std::string>{"2.1.211"}, false, false,
          {.collect = true, .install = true, .rewrite = true});
    }()) {
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
      },
      .capabilities = std::move(capabilities)};
}

}  // namespace

TEST_CASE("FX-VF-O2 claude direction refusal is per-session and transports detail") {
  const auto root = make_tmp("fx-vf-o2");
  auto members = std::map<std::string, std::vector<std::byte>>{};
  auto target = target_for(root / "workspace", root / "claude", members);
  target.capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"2.1.100"}, false, false,
      {.collect = true, .install = true, .rewrite = true});
  auto newer = claude_entry("/ws/proj", "aaaaaaaa-1111-4000-8000-000000000201");
  newer.agent_version_at_pack = "2.2.0";
  newer.children.clear();
  newer.artifacts.clear();
  auto older = claude_entry("/ws/proj", "aaaaaaaa-1111-4000-8000-000000000202");
  older.agent_version_at_pack = "2.0.5";
  older.children.clear();
  older.artifacts.clear();

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, std::vector{newer, older});

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(0).reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(result->sessions.at(0).detail ==
        std::optional<std::string>{std::string{
            biv::adapters::version_floor::kBasisNewerThanHost}});
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  fs::remove_all(root);
}

TEST_CASE(
    "Claude admission refuses an unparseable host version through InstallTarget") {
  const auto root = make_tmp("host-unparseable");
  auto members = std::map<std::string, std::vector<std::byte>>{};
  auto capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"unknown"}, false, false,
      {.collect = true, .install = true, .rewrite = true});
  auto target = target_for(root / "workspace", root / "claude", members,
                           std::move(capabilities));
  auto record = claude_entry(
      "/ws/proj", "aaaaaaaa-1111-4000-8000-000000000402");
  record.children.clear();
  record.artifacts.clear();

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, std::vector{record});

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK_FALSE(result->sessions.front().host_version_unverified);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  fs::remove_all(root);
}

TEST_CASE("FX-VF-O4 and FX-MG-7 claude hostile bases refuse before ordering") {
  const std::string nul_bearing{"2.1.\0", 5U};
  const std::string control_bearing{"2.1.\x1f", 5U};
  const std::vector<std::pair<std::string, std::string>> cases{
      {"basis-absent", ""},
      {"basis-null", "null"},
      {"basis-nul-bearing", nul_bearing},
      {"basis-non-numeric", "2.1.x7"},
      {"basis-overlong-patch", "2.1.1234567890"},
      {"basis-control-bearing", control_bearing},
      {"basis-unicode-bearing", "2.1.\xE2\x98\x83"},
      {"basis-line-valid-but-unparseable", "2.1."}};

  for (const auto& [name, basis] : cases) {
    DYNAMIC_SECTION(name) {
      const auto root = make_tmp("fx-vf-o4-" + name);
      auto members = std::map<std::string, std::vector<std::byte>>{};
      auto target = target_for(root / "workspace", root / "claude", members);
      target.capabilities = biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::readable,
          std::optional<std::string>{"2.1.100"}, false, false,
          {.collect = true, .install = true, .rewrite = true});
      auto record =
          claude_entry("/ws/proj", "aaaaaaaa-1111-4000-8000-000000000401");
      record.agent_version_at_pack = basis;
      record.children.clear();
      record.artifacts.clear();

      const auto result = biv::adapters::claude_code_adapter().install(
          target, biv::adapters::Consent::yes, std::vector{record});

      REQUIRE(result.has_value());
      REQUIRE(result->sessions.size() == 1U);
      CHECK(result->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::failed);
      CHECK(result->sessions.front().reason ==
            std::optional<std::string>{"not-validated"});
      CHECK(result->sessions.front().detail ==
            std::optional<std::string>{std::string{
                biv::adapters::version_floor::kBasisUnorderable}});
      CHECK(result->id_map.empty());
      CHECK(result->activation.empty());
      fs::remove_all(root);
    }
  }
}

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

TEST_CASE("Claude install produces identical bytes with or without packer_home") {
  const auto root = make_tmp("packer-home-receipt");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto members = claude_members();
  members.at(main_artifact()) = bytes(
      std::string{"{\"/ws/proj\":\"key-must-not-change\",\"type\":\"user\","
                  "\"cwd\":\"\\/ws\\/\\u0070roj\",\"sessionId\":\""} +
      std::string{kOriginalSession} +
      "\",\"decimal\":0.1,\"integral\":1.0,\"exponent\":1e+03,"
      "\"unsigned\":18446744073709551615}\n");
  auto record = claude_entry();
  record.children.clear();
  const std::vector<biv::manifest::AgentSessionEntry> records{record};
  struct StoreReceipt {
    std::vector<std::string> files;
    std::map<std::string, std::string> contents;
  };
  const auto install_receipt = [&](const std::string_view arm,
                                   std::optional<biv::manifest::PackerHome> home) {
    const auto store = root / std::string{arm};
    fs::create_directories(store);
    auto target = target_for(workspace, store, members);
    target.packer_home = std::move(home);
    const auto result = biv::adapters::claude_code_adapter().install(
        target, biv::adapters::Consent::yes, records);
    REQUIRE(result.has_value());
    REQUIRE(result->sessions.size() == 1U);
    REQUIRE(result->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::installed);
    REQUIRE(result->id_map.size() == 1U);
    const auto& installed_id = result->id_map.front().installed_session_id;
    StoreReceipt receipt;
    for (const auto& file : regular_files(store)) {
      auto relative = fs::relative(file, store).generic_string();
      auto installed = read_text(file);
      auto normalize_id = [&](std::string& value) {
        auto id_position = value.find(installed_id);
        while (id_position != std::string::npos) {
          value.replace(id_position, installed_id.size(), "<installed-id>");
          id_position = value.find(installed_id, id_position + 14U);
        }
      };
      normalize_id(relative);
      normalize_id(installed);
      receipt.files.push_back(relative);
      receipt.contents.emplace(std::move(relative), std::move(installed));
    }
    std::ranges::sort(receipt.files);
    return receipt;
  };

  const auto engaged = install_receipt(
      "engaged", biv::manifest::PackerHome{
                     "/Users/packer", biv::manifest::PathFlavor::posix});
  const auto absent = install_receipt("absent", std::nullopt);
  REQUIRE(engaged.files == absent.files);
  REQUIRE(engaged.contents == absent.contents);
  fs::remove_all(root);
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

TEST_CASE(
    "Claude install rewrites transcripts, preserves meta, and avoids "
    "collisions") {
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
  CHECK_FALSE(first->sessions.front().host_version_unverified);
  REQUIRE(first->sessions.front().content_rewrite.has_value());
  CHECK(*first->sessions.front().content_rewrite == "pair");
  CHECK(first->sessions.front().verify.origin_path_hits == 0);
  CHECK(first->sessions.front().verify.origin_id_hits == 0);
  CHECK(first->sessions.front().verify.artifacts_checked == 3);
  REQUIRE(first->id_map.size() == 1);
  const std::string first_id = first->id_map.front().installed_session_id;
  CHECK(first_id != kOriginalSession);
  REQUIRE(first->activation.size() == 1);
  CHECK(first->activation.front().command == "claude --resume " + first_id);

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

TEST_CASE("Claude install uses grammar and direction instead of an allowlist") {
  const auto root = make_tmp("capability-gate");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto members = claude_members();
  const auto& adapter = biv::adapters::claude_code_adapter();
  const std::vector<biv::manifest::AgentSessionEntry> valid_records{
      claude_entry()};

  const auto supported_store = root / "supported-claude";
  fs::create_directories(supported_store);
  auto supported_target = target_for(workspace, supported_store, members);
  const auto supported = adapter.install(supported_target, biv::adapters::Consent::yes, valid_records);
  REQUIRE(supported.has_value());
  REQUIRE(supported->sessions.size() == 1);
  CHECK(supported->mode == biv::adapters::InstallResult::Mode::host_installed);
  CHECK(supported->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK_FALSE(supported->sessions.front().host_version_unverified);
  REQUIRE(supported->activation.size() == 1);

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
  CHECK(unknown->sessions.front().reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(unknown->sessions.front().detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK_FALSE(unknown->sessions.front().host_version_unverified);
  CHECK(unknown->id_map.empty());
  CHECK(unknown->activation.empty());
  CHECK(regular_files(unknown_image_store).empty());

  const auto forward_store = root / "forward-claude";
  fs::create_directories(forward_store);
  auto forward_caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"2.9.0"}, true, false,
      {.collect = true, .install = true, .rewrite = true});
  auto forward_target =
      target_for(workspace, forward_store, members, std::move(forward_caps));
  const auto forward = adapter.install(
      forward_target, biv::adapters::Consent::yes, valid_records);
  REQUIRE(forward.has_value());
  REQUIRE(forward->sessions.size() == 1);
  CHECK(forward->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(forward->sessions.front().host_version_unverified);
  CHECK_FALSE(forward->sessions.front().detail.has_value());
  REQUIRE(forward->id_map.size() == 1U);
  REQUIRE(forward->activation.size() == 1U);
  CHECK(fs::exists(forward_store / "projects"));
  fs::remove_all(root);
}

TEST_CASE(
    "Task 3 Claude activation binds every clean session and omits failed "
    "rows") {
  constexpr std::string_view second_id = "bbbbbbbb-2222-4000-8000-000000000002";
  constexpr std::string_view failed_id = "cccccccc-3333-4000-8000-000000000003";
  const auto root = make_tmp("activation-per-clean-session");
  const auto workspace = root / "workspace";
  const auto store = root / "claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = claude_members();
  add_claude_members(members, second_id);
  add_claude_members(members, failed_id);
  auto first = claude_entry();
  auto second = claude_entry("/ws/proj", std::string{second_id});
  auto failed = claude_entry("/ws/proj", std::string{failed_id});
  failed.agent_version_at_pack = "2.2.0";
  const std::vector records{first, second, failed};
  auto target = target_for(workspace, store, members);

  const auto installed = biv::adapters::claude_code_adapter().install(target, biv::adapters::Consent::yes, records);

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 3);
  REQUIRE(installed->id_map.size() == 2);
  REQUIRE(installed->activation.size() == 2);
  for (const auto& id : installed->id_map) {
    CHECK(std::ranges::any_of(installed->activation, [&](const auto& item) {
      return item.command == "claude --resume " + id.installed_session_id;
    }));
  }
  const auto failed_row = std::ranges::find(installed->sessions, std::string{failed_id},
                                            &biv::adapters::InstallSessionOutcome::image_session_id);
  REQUIRE(failed_row != installed->sessions.end());
  CHECK(failed_row->outcome == biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(failed_row->detail ==
        std::optional<std::string>{"basis_newer_than_host"});
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
  CHECK(report->verify.origin_path_hits > 0);
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
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"rewrite_verify_failed"});
  CHECK(result->sessions.front().verify.origin_id_hits > 0);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "Claude rewrite verification preserves a sibling capability refusal") {
  const auto root = make_tmp("verify-refusal-cohort");
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
  auto refused = claude_entry(
      "/ws/proj", "aaaaaaaa-1111-4000-8000-000000000905");
  refused.agent_version_at_pack = "unknown";
  refused.children.clear();
  refused.artifacts.clear();
  const std::vector<biv::manifest::AgentSessionEntry> records{refused,
                                                              claude_entry()};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2U);
  const auto row_for = [&](const std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto verify_row = row_for(claude_entry().original_session_ids.primary);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(verify_row != result->sessions.end());
  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(verify_row->reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(verify_row->detail ==
        std::optional<std::string>{"rewrite_verify_failed"});
  CHECK(verify_row->verify.origin_path_hits > 0U);
  CHECK(verify_row->verify.origin_id_hits > 0U);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Claude install refuses every unverifiable escaped origin line") {
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
      const auto store = root / "target-claude";
      fs::create_directories(workspace);
      fs::create_directories(store);
      auto members = claude_members();
      members.at(main_artifact()) = hostile.content;
      auto target = target_for(workspace, store, members);
      const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

      const auto result = biv::adapters::claude_code_adapter().install(
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
      CHECK(regular_files(store).empty());
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Task 3 Claude capabilities parse one probe observation") {
  struct ProbeCase {
    std::string raw;
    biv::adapters::Capabilities::Verdict verdict;
    std::optional<std::string> parsed;
    biv::support::ProbeOutcome outcome;
    bool newer_than_survey;
  };
  const std::vector<ProbeCase> cases{{"2.1.211 (Claude Code)\n", biv::adapters::Capabilities::Verdict::readable,
                                      "2.1.211", biv::support::ProbeOutcome::ok, false},
                                     {"2.2.0 (Claude Code)", biv::adapters::Capabilities::Verdict::readable, "2.2.0",
                                      biv::support::ProbeOutcome::ok, true},
                                     {"v2.2.0-alpha.1+build (Claude Code)",
                                      biv::adapters::Capabilities::Verdict::readable,
                                      "v2.2.0-alpha.1+build",
                                      biv::support::ProbeOutcome::ok, true},
                                     {"2.2.0.1 (Claude Code)",
                                      biv::adapters::Capabilities::Verdict::readable,
                                      "2.2.0.1", biv::support::ProbeOutcome::ok,
                                      true},
                                     {"2.2.0 (Claude Code)\nruntime 2.1.0",
                                      biv::adapters::Capabilities::Verdict::unreadable,
                                      std::nullopt,
                                      biv::support::ProbeOutcome::unparseable,
                                      false},
                                     {"not a version", biv::adapters::Capabilities::Verdict::unreadable,
                                      std::nullopt, biv::support::ProbeOutcome::unparseable, false},
                                     {"", biv::adapters::Capabilities::Verdict::unreadable, std::nullopt,
                                      biv::support::ProbeOutcome::unparseable, false}};

  for (const auto& probe_case : cases) {
    DYNAMIC_SECTION(probe_case.raw) {
      const auto root = make_tmp("probe-capabilities");
      const auto store = root / ".claude";
      fs::create_directories(store);
      {
        std::ofstream marker{store / ".last-update-result.json"};
        marker << "{\"version\":\"3.0.0\"}\n";
      }
      const auto pin = root / "bin" / "claude";
      const biv::adapters::Env env{
          .getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; }, .home = root};
      size_t observations = 0;
      const biv::adapters::Host host{
          .home = root,
          .env = env,
          .version_probe = [&](const std::string_view executable,
                               const std::optional<fs::path>& requested) -> biv::expected<biv::support::ProbeEvidence> {
            ++observations;
            CHECK(executable == "claude");
            CHECK(requested == std::optional<fs::path>{pin});
            return biv::support::ProbeEvidence{.agent = std::string{executable},
                                               .requested = requested,
                                               .executed = pin,
                                               .pinned = true,
                                               .outcome = biv::support::ProbeOutcome::ok,
                                               .exit_code = 0,
                                               .raw = probe_case.raw,
                                               .parsed = std::nullopt};
          },
          .pinned_bins = {{"claude-code", pin}}};

      const auto caps = biv::adapters::claude_code_adapter().capabilities(host);

      CHECK(observations == 1);
      CHECK(caps.verdict() == probe_case.verdict);
      CHECK(caps.agent_version() == probe_case.parsed.value_or("unknown"));
      CHECK(caps.newer_than_survey() == probe_case.newer_than_survey);
      REQUIRE(caps.probe.has_value());
      CHECK(caps.probe->parsed == probe_case.parsed);
      CHECK(caps.probe->outcome == probe_case.outcome);
      CHECK(caps.probe->raw == probe_case.raw);
      CHECK(caps.probe->pinned);
      CHECK(caps.probe->executed == pin);
      CHECK(caps.probe->agent == "claude-code");
      CHECK(caps.per_verb.collect);
      CHECK(caps.per_verb.install);
      CHECK(caps.per_verb.rewrite);
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Task 3 Claude capabilities preserve not-found and timeout evidence") {
  for (const auto outcome : {biv::support::ProbeOutcome::not_found,
                             biv::support::ProbeOutcome::timeout}) {
    DYNAMIC_SECTION(static_cast<int>(outcome)) {
      const auto root = make_tmp("probe-failure-matrix");
      const biv::adapters::Env env{
          .getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; }, .home = root};
      size_t observations = 0;
      const biv::adapters::Host host{
          .home = root,
          .env = env,
          .version_probe =
              [&](const std::string_view agent,
                  const std::optional<fs::path>&) -> biv::expected<biv::support::ProbeEvidence> {
            ++observations;
            return biv::support::ProbeEvidence{
                .agent = std::string{agent},
                .requested = std::nullopt,
                .executed = std::nullopt,
                .pinned = false,
                .outcome = outcome,
                .exit_code = -1,
                .raw = "",
                .parsed = std::nullopt};
          },
          .pinned_bins = {}};

      const auto caps =
          biv::adapters::claude_code_adapter().capabilities(host);

      CHECK(observations == 1);
      CHECK(caps.verdict() ==
            biv::adapters::Capabilities::Verdict::absent);
      CHECK(caps.agent_version() == "unknown");
      REQUIRE(caps.probe.has_value());
      CHECK(caps.probe->outcome == outcome);
      CHECK_FALSE(caps.probe->parsed.has_value());
      fs::remove_all(root);
    }
  }

  const auto root = make_tmp("probe-unwired");
  const biv::adapters::Host host{
      .home = root,
      .env =
          {.getenv = [](std::string_view) -> std::optional<std::string> {
             return std::nullopt;
           },
           .home = root},
      .version_probe = {},
      .pinned_bins = {}};

  const auto caps = biv::adapters::claude_code_adapter().capabilities(host);

  CHECK(caps.verdict() ==
        biv::adapters::Capabilities::Verdict::absent);
  CHECK_FALSE(caps.probe.has_value());
  fs::remove_all(root);

  const auto error_root = make_tmp("probe-error-detail");
  std::string invalid_detail{"probe error "};
  invalid_detail.push_back(static_cast<char>(0x9b));
  const biv::adapters::Host error_host{
      .home = error_root,
      .env =
          {.getenv = [](std::string_view) -> std::optional<std::string> {
             return std::nullopt;
           },
           .home = error_root},
      .version_probe =
          [invalid_detail](
              std::string_view,
              const std::optional<fs::path>&)
          -> biv::expected<biv::support::ProbeEvidence> {
        return std::unexpected(
            biv::BivError{.kind = biv::ErrKind::InternalError,
                          .detail = invalid_detail});
      },
      .pinned_bins = {}};

  const auto error_caps =
      biv::adapters::claude_code_adapter().capabilities(error_host);

  REQUIRE(error_caps.probe.has_value());
  CHECK(error_caps.probe->outcome ==
        biv::support::ProbeOutcome::spawn_error);
  CHECK(error_caps.probe->raw == "probe error \xEF\xBF\xBD");
  CHECK(biv::support::sanitize_utf8(error_caps.probe->raw) ==
        error_caps.probe->raw);
  fs::remove_all(error_root);
}

TEST_CASE("Task 5 Claude absent store dominates readable probe") {
  const auto root = make_tmp("probe-store-orthogonal");
  const auto& adapter = biv::adapters::claude_code_adapter();
  const biv::adapters::Env env{.getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; },
                               .home = root};
  size_t observations = 0;
  const biv::adapters::Host working_host{
      .home = root,
      .env = env,
      .version_probe = [&](const std::string_view agent,
                           const std::optional<fs::path>&) -> biv::expected<biv::support::ProbeEvidence> {
        ++observations;
        return biv::support::ProbeEvidence{.agent = std::string{agent},
                                           .requested = std::nullopt,
                                           .executed = root / "bin" / "claude",
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::ok,
                                           .exit_code = 0,
                                           .raw = "2.1.211 (Claude Code)",
                                           .parsed = std::nullopt};
      },
      .pinned_bins = {}};

  const auto caps = adapter.capabilities(working_host);
  CHECK(observations == 1);
  CHECK(caps.verdict() == biv::adapters::Capabilities::Verdict::absent);
  CHECK(caps.agent_version() == "unknown");
  CHECK_FALSE(caps.newer_than_survey());
  CHECK_FALSE(caps.per_verb.collect);
  CHECK_FALSE(caps.per_verb.install);
  CHECK_FALSE(caps.per_verb.rewrite);
  CHECK_FALSE(caps.long_path_keys_pinned);

  fs::create_directories(root / ".claude");
  const biv::adapters::Host failed_host{
      .home = root,
      .env = env,
      .version_probe = [](const std::string_view agent,
                          const std::optional<fs::path>&) -> biv::expected<biv::support::ProbeEvidence> {
        return biv::support::ProbeEvidence{.agent = std::string{agent},
                                           .requested = std::nullopt,
                                           .executed = std::nullopt,
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::nonzero_exit,
                                           .exit_code = 1,
                                           .raw = "probe failed",
                                           .parsed = std::nullopt};
      },
      .pinned_bins = {}};
  const auto failed = adapter.capabilities(failed_host);
  CHECK(failed.verdict() == biv::adapters::Capabilities::Verdict::unreadable);
  REQUIRE(failed.probe.has_value());
  CHECK(failed.probe->outcome == biv::support::ProbeOutcome::nonzero_exit);
  CHECK(failed.per_verb.collect);
  CHECK(failed.per_verb.install);
  CHECK(failed.per_verb.rewrite);
  fs::remove_all(root);
}

TEST_CASE(
    "Task 3 Claude install consumes supplied capabilities and has no "
    "store oracle") {
  const auto root = make_tmp("supplied-capabilities");
  const auto workspace = root / "workspace";
  const auto store = root / "claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
  {
    std::ofstream marker{store / ".last-update-result.json"};
    marker << "{\"version\":\"3.0.0\"}\n";
  }
  auto members = claude_members();
  auto capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"2.1.211"}, false, false,
      {.collect = true, .install = true, .rewrite = true});
  auto target = target_for(workspace, store, members, std::move(capabilities));

  const auto installed = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, std::vector<biv::manifest::AgentSessionEntry>{claude_entry()});

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1);
  CHECK(installed->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK_FALSE(installed->sessions.front().host_version_unverified);
  const auto source = read_text(fs::path{BIV_SOURCE_DIR} / "src" / "adapters" / "claude_code" / "install.cpp");
  CHECK(source.find("capabilities_for_root") == std::string::npos);
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

TEST_CASE("errno_symbol converts representative errnos to exact POSIX spellings") {
  using biv::adapters::secure_io::errno_symbol;
  CHECK(errno_symbol(ENOENT) == std::optional<std::string_view>{"ENOENT"});
  CHECK(errno_symbol(EACCES) == std::optional<std::string_view>{"EACCES"});
  CHECK(errno_symbol(EEXIST) == std::optional<std::string_view>{"EEXIST"});
  CHECK(errno_symbol(ENOSPC) == std::optional<std::string_view>{"ENOSPC"});
  CHECK(errno_symbol(EMFILE) == std::optional<std::string_view>{"EMFILE"});
  CHECK(errno_symbol(ELOOP) == std::optional<std::string_view>{"ELOOP"});
  CHECK(errno_symbol(ENOTDIR) == std::optional<std::string_view>{"ENOTDIR"});
  CHECK(errno_symbol(EINVAL) == std::optional<std::string_view>{"EINVAL"});
  // Target-specific values are IN the namespace under Reading B: a network or
  // FUSE mount can return these from the very syscalls C1 classifies. EACH IS
  // GUARDED because the macOS job compiles this file and Darwin defines only
  // some of them -- it reportedly defines EHOSTDOWN at its full feature level
  // and neither EREMOTEIO nor EUCLEAN. The guards are per-name for that reason;
  // do not collapse them.
#ifdef EREMOTEIO
  CHECK(errno_symbol(EREMOTEIO) == std::optional<std::string_view>{"EREMOTEIO"});
#endif
#ifdef EUCLEAN
  CHECK(errno_symbol(EUCLEAN) == std::optional<std::string_view>{"EUCLEAN"});
#endif
#ifdef EHOSTDOWN
  CHECK(errno_symbol(EHOSTDOWN) == std::optional<std::string_view>{"EHOSTDOWN"});
#endif
}

TEST_CASE("errno_symbol resolves each equal-valued group by the owner's rule") {
  // m-3 032747: EVERY multi-name group must be pinned; the canonical name
  // comes from tests/errno_pins.txt, keyed by GROUP SIGNATURE (never by
  // integer -- integers name opposite groups on different targets).
  // m-3 020759 requires the test guards to MIRROR the
  // production guards, and mirroring means THE SAME PREDICATE -- not a
  // logically equivalent one. rev3 reached the distinct arm through a bare
  // `#elif defined(A) && defined(B)`, which is equivalent after the preceding
  // branch but is NOT the production predicate the owner made contract
  // surface. Each pair below therefore states the production `!=` predicate
  // verbatim, and expresses the equal case as its own `==` block.
  using biv::adapters::secure_io::errno_symbol;

  // --- group 11 on Linux: multiple-POSIX, pinned EAGAIN -------------------
#if defined(EAGAIN) && defined(EWOULDBLOCK) && (EAGAIN) != (EWOULDBLOCK)
  // DISTINCT: two singleton groups, each its own spelling.
  CHECK(errno_symbol(EWOULDBLOCK) == std::optional<std::string_view>{"EWOULDBLOCK"});
#endif
#if defined(EAGAIN) && defined(EWOULDBLOCK) && (EAGAIN) == (EWOULDBLOCK)
  // EQUAL: one group, the pin wins for the shared value.
  CHECK(errno_symbol(EWOULDBLOCK) == std::optional<std::string_view>{"EAGAIN"});
#endif
#ifdef EAGAIN
  CHECK(errno_symbol(EAGAIN) == std::optional<std::string_view>{"EAGAIN"});
#endif

  // --- group 35 on Linux: pinned EDEADLK ------------------------------
#if defined(EDEADLK) && defined(EDEADLOCK) && (EDEADLK) != (EDEADLOCK)
  CHECK(errno_symbol(EDEADLOCK) == std::optional<std::string_view>{"EDEADLOCK"});
#endif
#if defined(EDEADLK) && defined(EDEADLOCK) && (EDEADLK) == (EDEADLOCK)
  CHECK(errno_symbol(EDEADLOCK) == std::optional<std::string_view>{"EDEADLK"});
#endif
#ifdef EDEADLK
  // EDEADLOCK is reportedly undefined on Darwin; nothing is owed for it, and
  // this assertion still holds there.
  CHECK(errno_symbol(EDEADLK) == std::optional<std::string_view>{"EDEADLK"});
#endif

  // --- group 74 on Linux: pinned EBADMSG ------------------------------
#if defined(EBADMSG) && defined(EFSBADCRC) && (EBADMSG) != (EFSBADCRC)
  CHECK(errno_symbol(EFSBADCRC) == std::optional<std::string_view>{"EFSBADCRC"});
#endif
#if defined(EBADMSG) && defined(EFSBADCRC) && (EBADMSG) == (EFSBADCRC)
  CHECK(errno_symbol(EFSBADCRC) == std::optional<std::string_view>{"EBADMSG"});
#endif
#ifdef EBADMSG
  CHECK(errno_symbol(EBADMSG) == std::optional<std::string_view>{"EBADMSG"});
#endif

  // --- group 95 on Linux: multiple-POSIX, pinned ENOTSUP ------------------
#if defined(ENOTSUP) && defined(EOPNOTSUPP) && (ENOTSUP) != (EOPNOTSUPP)
  // THE DARWIN ARM. ENOTSUP and EOPNOTSUPP are DISTINCT values under
  // __DARWIN_UNIX03. EOPNOTSUPP is its own singleton group: emitting "ENOTSUP" for it
  // would be a FALSE SYMBOL and emitting nothing would be the forbidden
  // omission. This assertion is the one that fails if the distinct-value arm
  // is wrong, absent, or never compiled.
  CHECK(errno_symbol(EOPNOTSUPP) == std::optional<std::string_view>{"EOPNOTSUPP"});
#endif
#if defined(ENOTSUP) && defined(EOPNOTSUPP) && (ENOTSUP) == (EOPNOTSUPP)
  CHECK(errno_symbol(EOPNOTSUPP) == std::optional<std::string_view>{"ENOTSUP"});
#endif
#ifdef ENOTSUP
  CHECK(errno_symbol(ENOTSUP) == std::optional<std::string_view>{"ENOTSUP"});
#endif

  // --- group 117 on Linux: zero POSIX members, pinned EUCLEAN -------------
#if defined(EUCLEAN) && defined(EFSCORRUPTED) && (EUCLEAN) != (EFSCORRUPTED)
  CHECK(errno_symbol(EFSCORRUPTED) == std::optional<std::string_view>{"EFSCORRUPTED"});
#endif
#if defined(EUCLEAN) && defined(EFSCORRUPTED) && (EUCLEAN) == (EFSCORRUPTED)
  CHECK(errno_symbol(EFSCORRUPTED) == std::optional<std::string_view>{"EUCLEAN"});
#endif
#ifdef EUCLEAN
  CHECK(errno_symbol(EUCLEAN) == std::optional<std::string_view>{"EUCLEAN"});
#endif

  // --- Darwin-only group {ENOTCAPABLE, ELAST}: zero POSIX members, pinned
  // ENOTCAPABLE ----------------------------------------------------------
  // ELAST is a MARKER naming the highest errno value, so it can never win a
  // tie-break. It stays a namespace member no user will ever see, and
  // detail: "ELAST" can therefore never be emitted.
#if defined(ENOTCAPABLE) && defined(ELAST) && (ENOTCAPABLE) == (ELAST)
  CHECK(errno_symbol(ELAST) == std::optional<std::string_view>{"ENOTCAPABLE"});
#endif
#ifdef ENOTCAPABLE
  CHECK(errno_symbol(ENOTCAPABLE) == std::optional<std::string_view>{"ENOTCAPABLE"});
#endif
}

TEST_CASE("errno_symbol disengages for zero and never yields an empty string") {
  // The presence rule (m-3 010403): present iff err_no is a NONZERO MEMBER of
  // the namespace. Absence covers zero truthfully. An ENGAGED optional holding
  // "" is the third state no contract admits and must be unreachable.
  using biv::adapters::secure_io::errno_symbol;
  CHECK_FALSE(errno_symbol(0).has_value());
  // TARGET-INDEPENDENT names only. rev3 had EUCLEAN in this list while
  // guarding it thirty lines above -- the instance was fixed and the class was
  // then asserted, and the Darwin build would have failed here. Any
  // target-specific value belongs in its own guarded block, never in an
  // unconditional initializer list.
  for (const int value : {ENOENT, EACCES, ENOSPC, EMFILE, EROFS}) {
    const auto symbol = errno_symbol(value);
    REQUIRE(symbol.has_value());
    CHECK_FALSE(symbol->empty());
  }
#ifdef EUCLEAN
  {
    const auto symbol = errno_symbol(EUCLEAN);
    REQUIRE(symbol.has_value());
    CHECK_FALSE(symbol->empty());
  }
#endif
}

TEST_CASE("ambient_error binds all five BivError fields with an empty detail") {
  const auto error =
      biv::adapters::secure_io::internal::ambient_error("/store/root", ENOSPC);

  CHECK(error.kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(error.path == "/store/root");
  CHECK(error.detail.empty());
  CHECK(error.err_no == ENOSPC);
  CHECK(error.facts.empty());
}

TEST_CASE("ambient_error never emits a detail install_failure_reason can retype") {
  for (const int value : {ENOENT, EACCES, ENOSPC, EMFILE, EROFS}) {
    const auto error =
        biv::adapters::secure_io::internal::ambient_error("/store/root", value);
    CHECK(error.detail.empty());
    CHECK(biv::core_sessions::install_failure_reason(error) == "error");
  }
}

TEST_CASE("classify keeps containment only where the errno is the I7 signal") {
  using biv::adapters::secure_io::internal::classify;
  using biv::adapters::secure_io::internal::SiteClass;
  using biv::adapters::secure_io::internal::SiteKind;

  // Directory-walk opens (:98, :149, :194): a symlink or non-directory
  // interposed in an O_NOFOLLOW|O_DIRECTORY walk IS the containment fact.
  CHECK(classify(SiteKind::directory_walk, ELOOP) == SiteClass::containment);
  CHECK(classify(SiteKind::directory_walk, ENOTDIR) == SiteClass::containment);
  CHECK(classify(SiteKind::directory_walk, ENOENT) == SiteClass::ambient);
  CHECK(classify(SiteKind::directory_walk, EACCES) == SiteClass::ambient);
  CHECK(classify(SiteKind::directory_walk, EMFILE) == SiteClass::ambient);
  CHECK(classify(SiteKind::directory_walk, ENOSPC) == SiteClass::ambient);

  // Intermediate mkdirat (:181): reached only after the SAME component was
  // observed ENOENT, so EEXIST means a node appeared in the checked path
  // between the two operations -- the intermediate-path analogue of :358.
  CHECK(classify(SiteKind::intermediate_create, EEXIST) == SiteClass::containment);
  CHECK(classify(SiteKind::intermediate_create, EACCES) == SiteClass::ambient);
  CHECK(classify(SiteKind::intermediate_create, ENOSPC) == SiteClass::ambient);
  CHECK(classify(SiteKind::intermediate_create, EROFS) == SiteClass::ambient);
  CHECK(classify(SiteKind::intermediate_create, ELOOP) == SiteClass::ambient);

  // O_EXCL temporary creation (:342): retry-exhausted EEXIST stays containment.
  CHECK(classify(SiteKind::temporary_create, EEXIST) == SiteClass::containment);
  CHECK(classify(SiteKind::temporary_create, EACCES) == SiteClass::ambient);
  CHECK(classify(SiteKind::temporary_create, ENOSPC) == SiteClass::ambient);

  // linkat publish (:358): the canonical CB4-1 no-replace race.
  CHECK(classify(SiteKind::publish_link, EEXIST) == SiteClass::containment);
  CHECK(classify(SiteKind::publish_link, ENOSPC) == SiteClass::ambient);
  CHECK(classify(SiteKind::publish_link, EMLINK) == SiteClass::ambient);
  CHECK(classify(SiteKind::publish_link, EXDEV) == SiteClass::ambient);
}

TEST_CASE("classify is pure and total over every site kind") {
  using biv::adapters::secure_io::internal::classify;
  using biv::adapters::secure_io::internal::SiteClass;
  using biv::adapters::secure_io::internal::SiteKind;

  for (const auto kind : {SiteKind::directory_walk, SiteKind::intermediate_create,
                          SiteKind::temporary_create, SiteKind::publish_link}) {
    for (int value = 1; value < 200; ++value) {
      const auto first = classify(kind, value);
      CHECK(classify(kind, value) == first);
      CHECK((first == SiteClass::containment || first == SiteClass::ambient));
    }
  }
}

TEST_CASE("secure install reports an absent store root as ambient, not containment") {
  const auto root = make_tmp("absent-root");
  const auto store = root / "never-created";
  const auto payload = bytes("payload\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> writes{
      {.relative_path = "sessions/only.jsonl", .bytes = payload}};

  const auto result = biv::adapters::secure_io::write_batch_no_replace(store, writes);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(result.error().detail.empty());
  CHECK(result.error().err_no == ENOENT);
  CHECK(biv::core_sessions::install_failure_reason(result.error()) == "error");
  fs::remove_all(root);
}

TEST_CASE("secure install refuses a duplicate publish target and rolls back completely") {
  const auto root = make_tmp("duplicate-publish");
  const auto store = root / "store";
  fs::create_directories(store);
  // NOTE: "newdir" is deliberately NOT created. The primitive must mkdirat it,
  // pushing a CreatedDirectory, so the reverse-walk rollback leg has work to do.
  const auto first = bytes("first\n");
  const auto second = bytes("second\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> writes{
      {.relative_path = "newdir/leaf.jsonl", .bytes = first},
      {.relative_path = "newdir/leaf.jsonl", .bytes = second}};

  const auto result = biv::adapters::secure_io::write_batch_no_replace(store, writes);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().detail == "containment_refused");
  CHECK(result.error().err_no == EEXIST);

  // All three rollback legs, asserted separately.
  CHECK_FALSE(fs::exists(store / "newdir" / "leaf.jsonl"));
  CHECK(regular_files(store).empty());
  CHECK_FALSE(fs::exists(store / "newdir"));
  fs::remove_all(root);
}

TEST_CASE("secure install classifies temporary-name exhaustion as containment") {
  const auto root = make_tmp("temporary-exhaustion");
  const auto store = root / "store";
  const auto sessions = store / "sessions";
  fs::create_directories(sessions);
  const std::string base =
      ".bivpak-install-" + std::to_string(::getpid()) + "-0.tmp";
  // Occupy ALL 1024 candidates for ordinal 0. Occupying only some is rejected:
  // the loop exits at the first free name and the terminal assertion never runs.
  for (std::size_t attempt = 0; attempt < 1024U; ++attempt) {
    const std::string name =
        attempt == 0U ? base : base + "." + std::to_string(attempt);
    std::ofstream occupied{sessions / name};
    occupied << "occupied";
  }
  const auto payload = bytes("payload\n");
  const std::vector<biv::adapters::secure_io::WriteRequest> writes{
      {.relative_path = "sessions/only.jsonl", .bytes = payload}};

  const auto result = biv::adapters::secure_io::write_batch_no_replace(store, writes);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().detail == "containment_refused");
  CHECK(result.error().err_no == EEXIST);
  CHECK_FALSE(fs::exists(sessions / "only.jsonl"));
  fs::remove_all(root);
}

TEST_CASE("fstat_outcome routes a failed fstat to ambient with the captured errno") {
  const auto outcome = biv::adapters::secure_io::internal::fstat_outcome(
      "/store/file.jsonl",
      biv::adapters::secure_io::internal::FstatObservation{std::unexpect, EIO});

  REQUIRE(outcome.has_value());
  CHECK(outcome->kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(outcome->path == "/store/file.jsonl");
  CHECK(outcome->detail.empty());
  CHECK(outcome->err_no == EIO);
  CHECK(outcome->facts.empty());
}

TEST_CASE("fstat_outcome routes a non-regular file to containment with explicit EINVAL") {
  // The stale-errno argument this test used to carry is GONE, and deliberately:
  // FstatObservation's success arm cannot hold an errno at all, so "succeeded,
  // and here is a leftover errno" is now unrepresentable rather than merely
  // forbidden. The rationale and its guard live at the alias (m-2 ruling 20260731-202000).
  // What this test still proves is the branch itself: a successful fstat over a
  // NON-REGULAR file yields containment EINVAL, never an ambient errno.
  struct stat dir_status {};
  dir_status.st_mode = S_IFDIR | 0755;
  const auto outcome = biv::adapters::secure_io::internal::fstat_outcome(
      "/store/dir", biv::adapters::secure_io::internal::FstatObservation{dir_status});

  REQUIRE(outcome.has_value());
  CHECK(outcome->kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(outcome->path == "/store/dir");
  CHECK(outcome->detail == "containment_refused");
  CHECK(outcome->err_no == EINVAL);
  CHECK(outcome->facts.empty());
}

TEST_CASE("fstat_outcome disengages for a successful fstat over a regular file") {
  struct stat reg_status {};
  reg_status.st_mode = S_IFREG | 0600;
  CHECK_FALSE(biv::adapters::secure_io::internal::fstat_outcome(
                  "/store/file.jsonl",
                  biv::adapters::secure_io::internal::FstatObservation{reg_status})
                  .has_value());
}

TEST_CASE("open_read_no_follow refuses a directory through real fstat containment") {
  const auto root = make_tmp("open-read-directory");
  const auto directory = root / "directory";
  fs::create_directory(directory);

  const auto result =
      biv::adapters::secure_io::open_read_no_follow(directory);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(result.error().detail == "containment_refused");
  CHECK(result.error().err_no == EINVAL);
  fs::remove_all(root);
}

TEST_CASE("open_read_no_follow refuses a FIFO through real fstat containment") {
  const auto root = make_tmp("open-read-fifo");
  const auto fifo = root / "fifo";
  REQUIRE(::mkfifo(fifo.c_str(), 0600) == 0);

  const auto result = [&] {
    ScopedFifoDeadline deadline;
    deadline.arm(5);
    auto guarded_result = biv::adapters::secure_io::open_read_no_follow(fifo);
    deadline.cancel();
    REQUIRE(fifo_deadline_expired == 0);
    return guarded_result;
  }();

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(result.error().detail == "containment_refused");
  CHECK(result.error().err_no == EINVAL);
  fs::remove_all(root);
}

TEST_CASE("open_read_no_follow refuses a final symlink before fstat") {
  const auto root = make_tmp("open-read-symlink");
  const auto symlink = root / "symlink";
  fs::create_symlink(root / "missing-target", symlink);

  const auto result =
      biv::adapters::secure_io::open_read_no_follow(symlink);

  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::ArchiveWriteFailed);
  CHECK(result.error().detail == "containment_refused");
  CHECK(result.error().err_no == ELOOP);
  fs::remove_all(root);
}

TEST_CASE("Claude preserves a capability refusal through a containment publish fact") {
  const auto root = make_tmp("cell-c2");
  const auto workspace = root / "workspace";
  const auto store = root / "target-claude";
  const auto outside = root / "outside";
  fs::create_directories(workspace);
  fs::create_directories(store);
  fs::create_directories(outside);
  fs::create_directory_symlink(outside, store / "projects");
  auto members = claude_members();
  auto target = target_for(workspace, store, members);

  auto refused =
      claude_entry("/ws/proj", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9002");
  refused.agent_version_at_pack = "unknown";
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry(),
                                                              refused};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  const auto row_for = [&](std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto cohort_row = row_for(claude_entry().original_session_ids.primary);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(cohort_row != result->sessions.end());

  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(cohort_row->reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(cohort_row->detail != std::optional<std::string>{"ELOOP"});

  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(regular_files(outside).empty());
  fs::remove_all(root);
}

TEST_CASE("Claude preserves a capability refusal through an ambient publish fault") {
  const auto root = make_tmp("cell-c1");
  const auto workspace = root / "workspace";
  const auto store = root / "never-created";
  fs::create_directories(workspace);
  auto members = claude_members();
  auto target = target_for(workspace, store, members);

  auto refused =
      claude_entry("/ws/proj", "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9001");
  refused.agent_version_at_pack = "unknown";
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry(),
                                                              refused};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  const auto row_for = [&](std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto cohort_row = row_for(claude_entry().original_session_ids.primary);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(cohort_row != result->sessions.end());

  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(cohort_row->outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(cohort_row->reason == std::optional<std::string>{"error"});
  CHECK(cohort_row->detail == std::optional<std::string>{"ENOENT"});

  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  fs::remove_all(root);
}

TEST_CASE("every installed path embeds that session's freshly minted id") {
  // AC12 pins the remoteness precondition: ordinary destination naming embeds
  // the fresh id, so collision requires a UUID collision rather than overlap.
  const auto root = make_tmp("remoteness-precondition");
  const auto workspace = root / "workspace";
  const auto store = root / "target-claude";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = claude_members();
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{claude_entry()};

  const auto result = biv::adapters::claude_code_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->id_map.size() == 1);
  const auto installed_id = result->id_map.front().installed_session_id;
  REQUIRE_FALSE(installed_id.empty());

  const auto created = regular_files(store);
  REQUIRE_FALSE(created.empty());
  bool saw_main = false;
  bool saw_subtree = false;
  for (const auto& path : created) {
    const auto text = path.generic_string();
    CHECK(text.find(installed_id) != std::string::npos);
    if (text.ends_with(installed_id + ".jsonl")) {
      saw_main = true;
    }
    if (text.find("/" + installed_id + "/") != std::string::npos) {
      saw_subtree = true;
    }
  }
  CHECK(saw_main);
  CHECK(saw_subtree);
  fs::remove_all(root);
}
