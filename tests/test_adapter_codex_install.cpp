#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
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
#include "adapters/rewrite_common.hpp"
#include "adapters/version_floor.hpp"
#include "core/support/probe.hpp"

namespace {

namespace fs = std::filesystem;

constexpr std::string_view kParent = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001";
constexpr std::string_view kChild = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0002";
constexpr std::string_view kFxParent = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1441";
constexpr std::string_view kFxChild = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1442";
constexpr std::string_view kIdPlaceholder = "<installed-id>";
constexpr std::string_view kNormalizedRolloutFile =
    "sessions/YYYY/MM/DD/rollout-YYYY-MM-DDTHH-MM-SS-<installed-id>.jsonl";

void replace_all(std::string& value, const std::string_view token,
                 const std::string_view replacement) {
  REQUIRE_FALSE(token.empty());
  auto position = value.find(token);
  while (position != std::string::npos) {
    value.replace(position, token.size(), replacement.data(), replacement.size());
    position = value.find(token, position + replacement.size());
  }
}

void normalize_minted_ids(
    std::string& value,
    const std::vector<biv::adapters::IdMapEntry>& id_map) {
  for (const auto& row : id_map) {
    replace_all(value, row.installed_session_id, kIdPlaceholder);
    for (const auto& child : row.children) {
      replace_all(value, child.second, kIdPlaceholder);
    }
  }
}

void normalize_rollout_clock(std::string& relative) {
  if (!relative.starts_with("sessions/")) {
    return;
  }
  REQUIRE(relative.size() > 47U);
  REQUIRE(relative.at(13) == '/');
  REQUIRE(relative.at(16) == '/');
  REQUIRE(relative.at(19) == '/');
  REQUIRE(relative.compare(20U, 8U, "rollout-") == 0);
  REQUIRE(relative.at(47) == '-');
  relative.replace(28U, 19U, "YYYY-MM-DDTHH-MM-SS");
  relative.replace(17U, 2U, "DD");
  relative.replace(14U, 2U, "MM");
  relative.replace(9U, 4U, "YYYY");
}

fs::path fixture_root() {
  return fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" / "codex_store" /
         "fx-cx-144";
}

fs::path make_tmp(std::string_view name) {
  auto base = fs::temp_directory_path() / ("biv-codex-install-" + std::string{name} + "-" + std::to_string(::getpid()));
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
      std::string{kChild} + "\",\"session_id\":\"" + std::string{kParent} +
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

biv::adapters::InstallTarget target_for(
    fs::path workspace, fs::path store, std::map<std::string, std::vector<std::byte>>& members,
    biv::adapters::Capabilities capabilities = [] {
      return biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::readable,
          std::optional<std::string>{"0.144.4"}, false, true,
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

TEST_CASE("version floor parses the complete bounded grammar") {
  using biv::adapters::version_floor::extract_single_version;
  using biv::adapters::version_floor::parse_grammar;

  for (const auto version : {"0.144.4", "v2.1.207", "0.145.0-alpha.1+build",
                             "2", "2.1.207.1", "00.144.0002"}) {
    CAPTURE(version);
    CHECK(parse_grammar(version).has_value());
  }

  const std::string nul_bearing{"0.144.\0", 7U};
  for (const auto& version : {std::string{}, std::string{"null"},
                              std::string{"unknown"}, nul_bearing,
                              std::string{"0.14x"}, std::string{"0.144.x7"},
                              std::string{"0.1234567890"},
                              std::string{"0.1.2.3.4"}}) {
    CAPTURE(version);
    CHECK_FALSE(parse_grammar(version).has_value());
  }

  CHECK(extract_single_version("codex-cli v0.145.0-alpha.1+build\n") ==
        std::optional<std::string>{"v0.145.0-alpha.1+build"});
  CHECK(extract_single_version("2.1.207.1 (Claude Code)\n") ==
        std::optional<std::string>{"2.1.207.1"});
  CHECK_FALSE(extract_single_version(
                  "codex-cli 0.145.0\nsandbox-runtime 0.142.9\n")
                  .has_value());
  constexpr char nul_delimited_raw[] =
      "codex-cli 0.145.0\0sandbox-runtime unavailable\n";
  const std::string nul_delimited_output{nul_delimited_raw,
                                         sizeof(nul_delimited_raw) - 1U};
  CHECK_FALSE(extract_single_version(nul_delimited_output).has_value());
  CHECK_FALSE(extract_single_version("codex-cli 0.145.\n").has_value());
}

TEST_CASE("version floor compares only the numeric major-minor line") {
  using biv::adapters::version_floor::Order;
  using biv::adapters::version_floor::compare_line;
  using biv::adapters::version_floor::parse_grammar;

  const auto order = [](const std::string_view left,
                        const std::string_view right) {
    const auto parsed_left = parse_grammar(left);
    const auto parsed_right = parse_grammar(right);
    REQUIRE(parsed_left.has_value());
    REQUIRE(parsed_right.has_value());
    return compare_line(*parsed_left, *parsed_right);
  };

  CHECK(order("0.142.99", "0.144.0") == Order::less);
  CHECK(order("0.144.0-alpha", "0.144.999+build") == Order::equal);
  CHECK(order("2.1", "0.300.0") == Order::greater);
  CHECK(order("1", "1.0.9.5") == Order::equal);
  CHECK(order("00.144.2", "0.144.9") == Order::equal);
}

TEST_CASE("version floor centralizes admission policy for both adapters") {
  struct Case {
    std::string_view agent;
    std::string_view host;
    std::string_view image;
    bool admitted;
    bool host_version_unverified;
    std::string_view detail;
  };
  constexpr Case cases[]{
      {"codex", "0.144.4", "0.142.5", true, false, {}},
      {"codex", "0.144.4", "0.145.0", false, false,
       "basis_newer_than_host"},
      {"codex", "unknown", "0.142.5", false, false,
       "basis_unorderable"},
      {"codex", "0.144.4", "unknown", false, false,
       "basis_unorderable"},
      {"codex", "0.300.0", "0.145.0", true, true, {}},
      {"claude-code", "2.1.211", "2.1.202", true, false, {}},
      {"claude-code", "2.9.0", "2.2.0", true, true, {}},
      // The pack MIN is not an open-side admission invariant (§A7.4).
      {"codex", "0.61.0", "0.61.0", true, false, {}},
  };

  for (const auto& test : cases) {
    DYNAMIC_SECTION(test.agent << " host " << test.host << " image "
                               << test.image) {
      const auto admission = biv::adapters::version_floor::admit(
          {.agent = test.agent,
           .host_version = test.host,
           .image_version = test.image});
      CHECK(admission.admitted == test.admitted);
      CHECK(admission.host_version_unverified ==
            test.host_version_unverified);
      CHECK(admission.detail == test.detail);
    }
  }
}

TEST_CASE("FX-VF-O2 codex direction refusal is per-session and transports detail") {
  const auto root = make_tmp("fx-vf-o2");
  auto members = std::map<std::string, std::vector<std::byte>>{};
  auto target = target_for(root / "workspace", root / "codex", members);
  target.capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.142.5"}, false, true,
      {.collect = true, .install = true, .rewrite = true});
  auto newer = codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0201", "unused");
  newer.agent_version_at_pack = "0.145.0";
  newer.children.clear();
  newer.artifacts.clear();
  auto older = codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0202", "unused");
  older.agent_version_at_pack = "0.142.1";
  older.children.clear();
  older.artifacts.clear();

  const auto result = biv::adapters::codex_adapter().install(
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
    "Codex admission refuses an unparseable host version through InstallTarget") {
  const auto root = make_tmp("host-unparseable");
  auto members = std::map<std::string, std::vector<std::byte>>{};
  auto capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"unknown"}, false, true,
      {.collect = true, .install = true, .rewrite = true});
  auto target = target_for(root / "workspace", root / "codex", members,
                           std::move(capabilities));
  auto record =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0402", "unused");
  record.children.clear();
  record.artifacts.clear();

  const auto result = biv::adapters::codex_adapter().install(
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

TEST_CASE("FX-VF-O4 and FX-MG-7 codex hostile bases refuse before ordering") {
  const std::string nul_bearing{"0.144.\0", 7U};
  const std::string control_bearing{"0.144.\x1f", 7U};
  const std::vector<std::pair<std::string, std::string>> cases{
      {"basis-absent", ""},
      {"basis-null", "null"},
      {"basis-nul-bearing", nul_bearing},
      {"basis-non-numeric", "0.14x"},
      {"basis-overlong-patch", "0.144.1234567890"},
      {"basis-control-bearing", control_bearing},
      {"basis-unicode-bearing", "0.144.\xE2\x98\x83"},
      {"basis-line-valid-but-unparseable", "0.144."}};

  for (const auto& [name, basis] : cases) {
    DYNAMIC_SECTION(name) {
      const auto root = make_tmp("fx-vf-o4-" + name);
      auto members = std::map<std::string, std::vector<std::byte>>{};
      auto target = target_for(root / "workspace", root / "codex", members);
      target.capabilities = biv::adapters::Capabilities::from_probe(
          biv::adapters::Capabilities::Verdict::readable,
          std::optional<std::string>{"0.142.5"}, false, true,
          {.collect = true, .install = true, .rewrite = true});
      auto record =
          codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee0401", "unused");
      record.agent_version_at_pack = basis;
      record.children.clear();
      record.artifacts.clear();

      const auto result = biv::adapters::codex_adapter().install(
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

TEST_CASE("Codex install produces identical bytes with or without packer_home") {
  const auto root = make_tmp("packer-home-receipt");
  const auto workspace = root / "workspace";
  constexpr std::string_view kEngagedCarrier = "/ws";
  fs::create_directories(workspace);
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
  auto record = codex_entry();
  record.children.clear();
  CHECK(record.original_path.starts_with(std::string{kEngagedCarrier} + "/"));
  std::string escaped_member_needle;
  for (const char value : kEngagedCarrier) {
    if (value == '/') {
      escaped_member_needle += '\\';
    }
    escaped_member_needle += value;
  }
  const auto escaped_member_bytes = bytes(escaped_member_needle);
  const auto& raw_member = members.at(parent_artifact());
  CHECK(std::search(raw_member.begin(), raw_member.end(),
                    escaped_member_bytes.begin(), escaped_member_bytes.end()) !=
        raw_member.end());
  const std::vector<biv::manifest::AgentSessionEntry> records{record};
  struct StoreReceipt {
    struct IdMapShape {
      std::string agent;
      std::string image_session_id;
      std::vector<std::string> image_children;

      bool operator==(const IdMapShape&) const = default;
    };

    std::vector<std::string> files;
    std::map<std::string, std::string> contents;
    std::vector<IdMapShape> id_map_shape;
  };
  const auto install_receipt = [&](const std::string_view arm,
                                   std::optional<biv::manifest::PackerHome> home) {
    const auto store = root / std::string{arm};
    fs::create_directories(store);
    auto target = target_for(workspace, store, members);
    target.packer_home = std::move(home);
    const auto result = biv::adapters::codex_adapter().install(
        target, biv::adapters::Consent::yes, records);
    REQUIRE(result.has_value());
    REQUIRE(result->sessions.size() == 1U);
    REQUIRE(result->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::installed);
    REQUIRE(result->id_map.size() == 1U);
    const auto files = relative_files(store);
    StoreReceipt receipt;
    for (const auto& row : result->id_map) {
      std::vector<std::string> image_children;
      image_children.reserve(row.children.size());
      std::ranges::transform(row.children, std::back_inserter(image_children),
                             [](const auto& child) { return child.first; });
      receipt.id_map_shape.push_back({.agent = row.agent,
                                      .image_session_id = row.image_session_id,
                                      .image_children =
                                          std::move(image_children)});
    }
    for (const auto& file : files) {
      auto relative = file;
      auto installed = read_text(store / file);
      normalize_rollout_clock(relative);
      normalize_minted_ids(relative, result->id_map);
      normalize_minted_ids(installed, result->id_map);
      receipt.files.push_back(relative);
      REQUIRE(receipt.contents.emplace(std::move(relative),
                                       std::move(installed)).second);
    }
    std::ranges::sort(receipt.files);
    REQUIRE_FALSE(receipt.files.empty());
    REQUIRE(std::ranges::find(receipt.files, kNormalizedRolloutFile) !=
            receipt.files.end());
    return receipt;
  };

  const auto engaged = install_receipt(
      "engaged", biv::manifest::PackerHome{
                     std::string{kEngagedCarrier}, biv::manifest::PathFlavor::posix});
  const auto absent = install_receipt("absent", std::nullopt);
  // Minted installed ids are normalized across arms by construction, so these
  // byte-identity checks deliberately exclude id-only divergence.
  REQUIRE(engaged.files == absent.files);
  REQUIRE(engaged.contents == absent.contents);
  REQUIRE(engaged.id_map_shape.size() == absent.id_map_shape.size());
  REQUIRE(engaged.id_map_shape == absent.id_map_shape);
  fs::remove_all(root);
}

TEST_CASE(
    "FX-VF-O1 Codex consent-no stages install-ready parent and child rollouts") {
  const auto root = make_tmp("consent-no-staging");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};

  const auto staged = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no, records);

  REQUIRE(staged.has_value());
  CHECK(staged->mode == biv::adapters::InstallResult::Mode::staged);
  REQUIRE(staged->sessions.size() == 1U);
  CHECK(staged->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::staged);
  CHECK(staged->sessions.front().content_rewrite ==
        std::optional<std::string>{"pair"});
  CHECK(staged->sessions.front().verify.origin_path_hits == 0U);
  CHECK(staged->sessions.front().verify.origin_id_hits == 0U);
  CHECK(staged->sessions.front().verify.artifacts_checked == 2U);
  REQUIRE(staged->id_map.size() == 1U);
  REQUIRE(staged->id_map.front().children.size() == 1U);
  CHECK(staged->activation.empty());
  CHECK(staged->pair_set_applied ==
        biv::adapters::rewrite::derive_pair_set(
            records.front().original_path, records.front().path_flavor,
            workspace.generic_string(),
            biv::manifest::PathFlavor::posix));
  CHECK(relative_files(store).empty());

  const auto staging_root = workspace / ".biv" / "agents" / "codex";
  const auto files = relative_files(staging_root);
  REQUIRE(files.size() == 2U);
  const auto& installed_id = staged->id_map.front().installed_session_id;
  const auto& child_id = staged->id_map.front().children.front().second;
  CHECK(std::ranges::all_of(files, [](const std::string& file) {
    return file.starts_with("sessions/");
  }));
  const auto parent_file = std::ranges::find_if(files, [&](const auto& file) {
    return file.find(installed_id) != std::string::npos;
  });
  const auto child_file = std::ranges::find_if(files, [&](const auto& file) {
    return file.find(child_id) != std::string::npos;
  });
  REQUIRE(parent_file != files.end());
  REQUIRE(child_file != files.end());
  const auto parent_text = read_text(staging_root / *parent_file);
  const auto child_text = read_text(staging_root / *child_file);
  CHECK(parent_text.find(kParent) == std::string::npos);
  CHECK(parent_text.find(installed_id) != std::string::npos);
  CHECK(parent_text.find(workspace.generic_string()) != std::string::npos);
  CHECK(child_text.find(kParent) == std::string::npos);
  CHECK(child_text.find(kChild) == std::string::npos);
  CHECK(child_text.find(installed_id) != std::string::npos);
  CHECK(child_text.find(child_id) != std::string::npos);
  CHECK(child_text.find(workspace.generic_string()) != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("FX-VF-O1 Codex installs a re-packed staged artifact identity") {
  constexpr std::string_view provenance_id = "cx-0001";
  constexpr std::string_view child_provenance_id = "cx-child-0001";
  constexpr std::string_view staged_id =
      "019f1d8c-e200-7000-8000-000000000001";
  constexpr std::string_view staged_child_id =
      "019f1d8c-e200-7000-8000-000000000002";
  const auto root = make_tmp("repacked-staged-identity");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto record = codex_entry(std::string{provenance_id},
                            std::string{child_provenance_id});
  record.provenance.locator = "staging";
  record.provenance.discovery_tier = "staged";
  record.artifacts = {"agents/codex/" + std::string{staged_id} + ".jsonl"};
  record.children.front().artifacts = {
      "agents/codex/" + std::string{staged_child_id} + ".jsonl"};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{staged_id} + "\",\"session_id\":\"" +
            std::string{staged_id} + "\",\"cwd\":\"/ws/proj\"," +
            "\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      record.children.front().artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{staged_child_id} + "\",\"session_id\":\"" +
            std::string{staged_id} + "\",\"parent_thread_id\":\"" +
            std::string{staged_id} + "\",\"cwd\":\"/ws/proj\"," +
            "\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::vector{record});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  REQUIRE(result->id_map.size() == 1U);
  CHECK(result->id_map.front().image_session_id == provenance_id);
  REQUIRE(result->id_map.front().children.size() == 1U);
  CHECK(result->id_map.front().children.front().first == child_provenance_id);
  const auto files = relative_files(store);
  REQUIRE(files.size() == 2U);
  const auto installed =
      read_text(store / files.front()) + read_text(store / files.back());
  CHECK(installed.find(staged_id) == std::string::npos);
  CHECK(installed.find(staged_child_id) == std::string::npos);
  CHECK(installed.find(provenance_id) == std::string::npos);
  CHECK(installed.find(child_provenance_id) == std::string::npos);
  CHECK(installed.find(result->id_map.front().installed_session_id) !=
        std::string::npos);
  CHECK(installed.find(result->id_map.front().children.front().second) !=
        std::string::npos);
  fs::remove_all(root);
}

TEST_CASE(
    "B2 composed Codex descendant staging path uses the exact final workspace") {
  constexpr std::string_view staged_id =
      "019f1d8c-e200-7000-8000-000000000011";
  const auto root = make_tmp("descendant-staging-path");
  const auto original_workspace = root / "original-workspace";
  const auto staging_workspace = original_workspace / "staging-workspace";
  const auto final_workspace = root / "final-workspace";
  const auto incorrectly_rewritten = final_workspace / "staging-workspace";
  const auto store = root / "codex";
  fs::create_directories(final_workspace);
  fs::create_directories(store);

  auto record = codex_entry(std::string{staged_id}, "unused-child");
  record.original_path = original_workspace.generic_string();
  record.normalized_path_key = record.original_path;
  record.provenance.store_root = staging_workspace.generic_string();
  record.provenance.locator = "staging";
  record.provenance.discovery_tier = "staged";
  record.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      bytes(std::string{
                "{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{staged_id} + "\",\"session_id\":\"" +
            std::string{staged_id} + "\",\"cwd\":\"" +
            staging_workspace.generic_string() +
            "\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(final_workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::vector{record});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(result->sessions.front().verify.origin_path_hits == 0U);
  REQUIRE(result->id_map.size() == 1U);
  const auto files = relative_files(store);
  REQUIRE(files.size() == 1U);
  const auto installed = read_text(store / files.front());
  CHECK(installed.find("\"cwd\":\"" + final_workspace.generic_string() +
                       "\"") != std::string::npos);
  CHECK(installed.find("\"cwd\":\"" + incorrectly_rewritten.generic_string() +
                       "\"") == std::string::npos);
  CHECK(installed.find(original_workspace.generic_string()) ==
        std::string::npos);
  CHECK(installed.find(staging_workspace.generic_string()) ==
        std::string::npos);
  fs::remove_all(root);
}

TEST_CASE(
    "Codex consent-no reports an unwritable workspace without a staged artifact") {
  const auto root = make_tmp("consent-no-unwritable");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry()};
  fs::permissions(workspace,
                  fs::perms::owner_read | fs::perms::owner_exec,
                  fs::perm_options::replace);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no, records);

  fs::permissions(workspace, fs::perms::owner_all,
                  fs::perm_options::replace);
  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"error"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"EACCES"});
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(workspace).empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex install rewrites escaped values and origin path keys") {
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
  CHECK(installed.find("\"" + workspace.generic_string() +
                       "\":\"key-must-not-change\"") !=
        std::string::npos);
  CHECK(installed.find("\"/ws/proj\":\"key-must-not-change\"") ==
        std::string::npos);
  CHECK(installed.find(workspace.generic_string()) != std::string::npos);
  CHECK(installed.find("\"decimal\":0.1") != std::string::npos);
  CHECK(installed.find("\"integral\":1.0") != std::string::npos);
  CHECK(installed.find("\"exponent\":1e+03") != std::string::npos);
  CHECK(installed.find("18446744073709551615") != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("FX-CX-144 discover collect install preserves new rollout variants") {
  const auto& adapter = biv::adapters::codex_adapter();
  const auto source_store = fixture_root();
  const biv::adapters::Env source_env{
      .getenv = [&](std::string_view name) -> std::optional<std::string> {
        return name == "CODEX_HOME"
                   ? std::optional<std::string>{source_store.string()}
                   : std::nullopt;
      },
      .home = source_store.parent_path()};

  const auto stores = adapter.discover(source_env);
  REQUIRE(stores);
  REQUIRE(stores->size() == 1U);
  CHECK(stores->front().root == source_store);
  const auto collected = adapter.collect("/ws/proj", *stores);
  REQUIRE(collected);
  REQUIRE(collected->sessions.size() == 1U);
  const auto& session = collected->sessions.front();
  CHECK(session.original_session_id == kFxParent);
  CHECK(session.child_ids == std::vector<std::string>{std::string{kFxChild}});
  CHECK(session.agent_version_at_pack == "0.144.1");
  REQUIRE(session.artifacts.size() == 2U);
  REQUIRE(session.artifact_sources.size() == session.artifacts.size());

  biv::manifest::AgentSessionEntry record;
  record.agent = session.agent;
  record.agent_version_at_pack = session.agent_version_at_pack;
  record.relpath_key = ".";
  record.original_path = session.original_path;
  record.normalized_path_key = session.normalized_path_key;
  record.normalization_scheme = session.normalization_scheme;
  record.path_flavor = session.path_flavor;
  record.provenance = session.provenance;
  record.original_session_ids.primary = session.original_session_id;
  record.artifacts = {session.artifacts.front()};
  record.children = {{.original_id = session.child_ids.front(),
                      .artifacts = {session.artifacts.at(1)}}};
  record.imported_at = "2026-07-12T12:02:00Z";

  std::map<std::string, std::vector<std::byte>> members;
  for (size_t i = 0; i < session.artifacts.size(); ++i) {
    members.emplace(session.artifacts.at(i),
                    bytes(read_text(session.artifact_sources.at(i).path)));
  }
  const auto root = make_tmp("fx-cx-144");
  const auto workspace = root / "workspace";
  const auto target_store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(target_store);
  {
    std::ofstream marker{target_store / "version.json"};
    marker << "{\"version\":\"0.144.1\"}\n";
  }
  auto target = target_for(workspace, target_store, members);

  const auto installed = adapter.install(
      target, biv::adapters::Consent::yes,
      std::vector<biv::manifest::AgentSessionEntry>{record});

  REQUIRE(installed);
  REQUIRE(installed->sessions.size() == 1U);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(installed->sessions.front().verify.origin_path_hits == 0U);
  CHECK(installed->sessions.front().verify.origin_id_hits == 0U);
  CHECK(installed->sessions.front().verify.artifacts_checked == 2U);
  REQUIRE(installed->id_map.size() == 1U);
  const auto& id_map = installed->id_map.front();
  REQUIRE(id_map.children.size() == 1U);
  const auto& installed_child = id_map.children.front().second;
  const auto files = relative_files(target_store);
  REQUIRE(files.size() == 3U);
  const auto parent_file = std::ranges::find_if(files, [&](const auto& file) {
    return file.find(id_map.installed_session_id) != std::string::npos;
  });
  const auto child_file = std::ranges::find_if(files, [&](const auto& file) {
    return file.find(installed_child) != std::string::npos;
  });
  REQUIRE(parent_file != files.end());
  REQUIRE(child_file != files.end());
  const auto parent_text = read_text(target_store / *parent_file);
  const auto child_text = read_text(target_store / *child_file);
  const auto all_text = parent_text + child_text;
  const auto expected_parent_meta =
      std::string{
          "{\"timestamp\":\"2026-07-12T12:00:00Z\",\"type\":\"session_meta\","
          "\"payload\":{\"id\":\""} +
      id_map.installed_session_id + "\",\"session_id\":\"" +
      id_map.installed_session_id + "\",\"cwd\":\"" +
      workspace.generic_string() +
      "\",\"cli_version\":\"0.144.1\",\"selected_capability_roots\":[\"/opt/"
      "codex/capabilities\"],\"history_mode\":\"legacy\",\"context_window\":{"
      "\"window_id\":\"" +
      id_map.installed_session_id +
      "\",\"max_tokens\":200000},\"source\":\"cli\",\"thread_source\":\"user\"}"
      "}\n";
  const auto expected_world_state =
      std::string{
          "{\"timestamp\":\"2026-07-12T12:00:01Z\",\"type\":\"world_state\","
          "\"payload\":{\"full\":true,\"state\":{\"environments\":{\"local\":{"
          "\"cwd\":\""} +
      workspace.generic_string() + "/sub\",\"thread_id\":\"" + id_map.installed_session_id +
      "\"}},\"outside_pair\":\"/opt/codex/capabilities\"}}}\n";
  const auto expected_child_meta =
      std::string{
          "{\"timestamp\":\"2026-07-12T12:01:00Z\",\"type\":\"session_meta\","
          "\"payload\":{\"id\":\""} +
      installed_child + "\",\"session_id\":\"" + installed_child + "\",\"cwd\":\"" + workspace.generic_string() +
      "/sub\",\"cli_version\":\"0.144.1\",\"selected_capability_roots\":[\"/"
      "opt/"
      "codex/capabilities\"],\"history_mode\":\"legacy\",\"context_window\":{"
      "\"window_id\":\"" +
      installed_child +
      "\",\"max_tokens\":200000},\"thread_source\":\"subagent\","
      "\"parent_thread_id\":\"" +
      id_map.installed_session_id +
      "\",\"source\":{\"subagent\":{\"thread_spawn\":{\"parent_thread_id\":\"" +
      id_map.installed_session_id +
      "\",\"depth\":1,\"agent_role\":\"worker\"}}}}}\n";

  CHECK(all_text.find(kFxParent) == std::string::npos);
  CHECK(all_text.find(kFxChild) == std::string::npos);
  CHECK(parent_text.find(expected_parent_meta) != std::string::npos);
  CHECK(parent_text.find(expected_world_state) != std::string::npos);
  CHECK(child_text.find(expected_child_meta) != std::string::npos);
  CHECK(parent_text.find(workspace.generic_string() + "/sub") !=
        std::string::npos);
  CHECK(parent_text.find(id_map.installed_session_id) != std::string::npos);
  CHECK(child_text.find(id_map.installed_session_id) != std::string::npos);
  CHECK(child_text.find(installed_child) != std::string::npos);
  CHECK(all_text.find("\"selected_capability_roots\":[\"/opt/codex/capabilities\"]") !=
        std::string::npos);
  CHECK(all_text.find("\"history_mode\":\"legacy\"") !=
        std::string::npos);
  CHECK(all_text.find("\"context_window\":{") != std::string::npos);
  CHECK(all_text.find("\"max_tokens\":200000") != std::string::npos);
  CHECK(parent_text.find("{\"timestamp\":\"2026-07-12T12:00:02Z\",\"type\":\"inter_agent_"
                         "communication_metadata\",\"payload\":{\"trigger_turn\":true}}\n") != std::string::npos);
  CHECK(parent_text.find("{\"timestamp\":\"2026-07-12T12:00:03Z\",\"type\":\"response_"
                         "item\",\"payload\":{\"type\":\"function_call\",\"name\":\"spawn_"
                         "agent\",\"arguments\":\"candidate-child\",\"call_id\":\"call_fx_"
                         "cx_144\"}}\n") != std::string::npos);
  REQUIRE(installed->activation.size() == 1U);
  CHECK(installed->activation.front().command ==
        "codex resume " + id_map.installed_session_id);
  fs::remove_all(root);
}

TEST_CASE("Codex install uses grammar and direction instead of an allowlist") {
  const auto root = make_tmp("capability-gate");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto members = codex_members();
  const auto& adapter = biv::adapters::codex_adapter();
  const std::vector<biv::manifest::AgentSessionEntry> valid_records{
      codex_entry()};

  const auto supported_store = root / "supported-codex";
  fs::create_directories(supported_store);
  auto supported_target = target_for(workspace, supported_store, members);
  const auto supported = adapter.install(supported_target, biv::adapters::Consent::yes, valid_records);
  REQUIRE(supported.has_value());
  REQUIRE(supported->sessions.size() == 1);
  CHECK(supported->mode == biv::adapters::InstallResult::Mode::host_installed);
  CHECK(supported->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK_FALSE(supported->sessions.front().host_version_unverified);
  REQUIRE(supported->activation.size() == 1);

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
  CHECK(unknown->sessions.front().reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(unknown->sessions.front().detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK_FALSE(unknown->sessions.front().host_version_unverified);
  CHECK(unknown->id_map.empty());
  CHECK(unknown->activation.empty());
  CHECK(relative_files(unknown_image_store).empty());

  const auto forward_store = root / "forward-codex";
  fs::create_directories(forward_store);
  auto forward_caps = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.300.0"}, true, true,
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
  CHECK(fs::exists(forward_store / "sessions"));
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

TEST_CASE("Codex install refuses non-UTF8 JSONL before writing") {
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
  CHECK(result->sessions.front().verify.origin_path_hits == 0U);
  CHECK(result->sessions.front().verify.origin_id_hits == 0U);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"undecodable_line"});
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "Codex rewrite verification preserves a sibling capability refusal") {
  const auto root = make_tmp("verify-refusal-cohort");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto refused =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee9005");
  refused.agent_version_at_pack = "unknown";
  refused.original_path = "/capability-origin";
  refused.normalized_path_key = refused.original_path;
  refused.children.clear();
  refused.artifacts.clear();
  auto verify = codex_entry();
  verify.original_path = "/verify-origin";
  verify.normalized_path_key = verify.original_path;
  verify.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      verify.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"
                        "\"id\":\""} +
            std::string{kParent} + "\",\"session_id\":\"" +
            std::string{kParent} +
            "\",\"cwd\":\"/verify-origin\",\"foreign_path\":"
            "\"/capability-origin\",\"foreign_id\":\"" +
            refused.original_session_ids.primary + "\"}}\n"));
  auto target = target_for(workspace, store, members);
  const std::vector<biv::manifest::AgentSessionEntry> records{refused, verify};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2U);
  const auto row_for = [&](const std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto verify_row = row_for(verify.original_session_ids.primary);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(verify_row != result->sessions.end());
  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(verify_row->reason == std::optional<std::string>{"verify-hits"});
  CHECK(verify_row->detail == std::optional<std::string>{"origin_path"});
  CHECK(verify_row->verify.origin_path_hits > 0U);
  CHECK(verify_row->verify.origin_id_hits > 0U);
  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "A2 Codex image union includes staged primary aliases before version admission") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9011";
  constexpr std::string_view staged_alias =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9012";
  constexpr std::string_view recipient_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9013";
  const auto root = make_tmp("version-refused-staged-primary-alias");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto refused = codex_entry(std::string{refused_id});
  refused.provenance.locator = "staging";
  refused.provenance.discovery_tier = "staged";
  refused.agent_version_at_pack = "unknown";
  refused.children.clear();
  refused.artifacts = {
      "agents/codex/" + std::string{staged_alias} + ".jsonl"};
  auto recipient = codex_entry(std::string{recipient_id});
  recipient.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      refused.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
            "\"id\":\"" + std::string{staged_alias} +
            "\",\"session_id\":\"" + std::string{staged_alias} +
            "\",\"cwd\":\"/srv/alpha\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      recipient.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
            "\"id\":\"" + std::string{recipient_id} +
            "\",\"session_id\":\"" + std::string{recipient_id} +
            "\",\"cwd\":\"/ws/proj\",\"foreign_id\":\"" +
            std::string{staged_alias} +
            "\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);
  const std::array records{refused, recipient};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  const auto refused_row = std::ranges::find(
      result->sessions, refused_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  const auto recipient_row = std::ranges::find(
      result->sessions, recipient_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(recipient_row != result->sessions.end());
  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(recipient_row->reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(recipient_row->detail == std::optional<std::string>{"origin_id"});
  CHECK(recipient_row->verify.origin_id_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE(
    "F-5 Codex image union includes staged child artifact aliases before version admission") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9021";
  constexpr std::string_view staged_primary =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9022";
  constexpr std::string_view original_child =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9023";
  constexpr std::string_view staged_child =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9024";
  constexpr std::string_view recipient_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee9025";
  const auto root = make_tmp("version-refused-staged-child-alias");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto refused = codex_entry(std::string{refused_id},
                             std::string{original_child});
  refused.provenance.locator = "staging";
  refused.provenance.discovery_tier = "staged";
  refused.agent_version_at_pack = "unknown";
  refused.artifacts = {
      "agents/codex/" + std::string{staged_primary} + ".jsonl"};
  refused.children.front().artifacts = {
      "agents/codex/" + std::string{staged_child} + ".jsonl"};
  auto recipient = codex_entry(std::string{recipient_id});
  recipient.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      refused.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
            "\"id\":\"" + std::string{staged_primary} +
            "\",\"session_id\":\"" + std::string{staged_primary} +
            "\",\"cwd\":\"/srv/alpha\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      refused.children.front().artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
            "\"id\":\"" + std::string{staged_child} +
            "\",\"session_id\":\"" + std::string{staged_child} +
            "\",\"cwd\":\"/srv/alpha\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      recipient.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{"} +
            "\"id\":\"" + std::string{recipient_id} +
            "\",\"session_id\":\"" + std::string{recipient_id} +
            "\",\"cwd\":\"/ws/proj\",\"foreign_id\":\"" +
            std::string{staged_child} +
            "\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);
  const std::array records{refused, recipient};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  const auto refused_row = std::ranges::find(
      result->sessions, refused_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  const auto recipient_row = std::ranges::find(
      result->sessions, recipient_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(recipient_row != result->sessions.end());
  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(recipient_row->reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(recipient_row->detail ==
        std::optional<std::string>{"origin_id"});
  CHECK(recipient_row->verify.origin_id_hits > 0U);
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
            std::optional<std::string>{"verify-hits"});
      CHECK(result->sessions.front().detail ==
            std::optional<std::string>{"undecodable_line"});
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
          .child_artifact_map = {},
          .original_path = entry.original_path,
          .normalized_path_key = entry.normalized_path_key,
          .normalization_scheme = entry.normalization_scheme,
          .path_flavor = entry.path_flavor,
          .provenance = entry.provenance,
          .artifacts = {parent_artifact(), child_artifact()},
          .artifact_sources = {},
          .torn_tails = {},
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

TEST_CASE("Task 3 Codex capabilities parse probe output and ignore store versions") {
  struct ProbeCase {
    std::string raw;
    biv::adapters::Capabilities::Verdict verdict;
    std::optional<std::string> parsed;
    biv::support::ProbeOutcome outcome;
    bool newer_than_survey;
  };
  const std::vector<ProbeCase> cases{
      {"codex-cli 0.144.4\n", biv::adapters::Capabilities::Verdict::readable, "0.144.4",
       biv::support::ProbeOutcome::ok, false},
      {"codex-cli 0.142.9 trailing text ", biv::adapters::Capabilities::Verdict::readable, "0.142.9",
       biv::support::ProbeOutcome::ok, false},
      {"codex-cli 0.145.0\n", biv::adapters::Capabilities::Verdict::readable, "0.145.0",
       biv::support::ProbeOutcome::ok, true},
      {"codex-cli v0.145.0-alpha.1+build\n",
       biv::adapters::Capabilities::Verdict::readable,
       "v0.145.0-alpha.1+build", biv::support::ProbeOutcome::ok, true},
      {"codex-cli 0.145.0.1\n",
       biv::adapters::Capabilities::Verdict::readable, "0.145.0.1",
       biv::support::ProbeOutcome::ok, true},
      {"codex-cli 0.145.0\nsandbox-runtime 0.142.9\n",
       biv::adapters::Capabilities::Verdict::unreadable, std::nullopt,
       biv::support::ProbeOutcome::unparseable, false},
      {"not a version", biv::adapters::Capabilities::Verdict::unreadable, std::nullopt,
       biv::support::ProbeOutcome::unparseable, false},
      {"", biv::adapters::Capabilities::Verdict::unreadable, std::nullopt,
       biv::support::ProbeOutcome::unparseable, false}};

  for (const auto& probe_case : cases) {
    DYNAMIC_SECTION(probe_case.raw) {
      const auto root = make_tmp("probe-capabilities");
      const auto store = root / ".codex";
      const auto rollout = store / "sessions" / "2026" / "07" / "06" /
                           "rollout-2026-07-06T01-00-00-019faaaa-bbbb-7ccc-8ddd-"
                           "eeeeeeee0001.jsonl";
      fs::create_directories(rollout.parent_path());
      {
        std::ofstream marker{store / "version.json"};
        marker << "{\"latest_version\":\"0.144.4\","
                  "\"last_checked_at\":\"now\"}\n";
      }
      {
        std::ofstream old_rollout{rollout};
        old_rollout << "{\"type\":\"session_meta\",\"payload\":{\"cli_version\":"
                       "\"0.61.0\"}}\n";
      }
      const auto pin = root / "bin" / "codex";
      const biv::adapters::Env env{
          .getenv = [](std::string_view) -> std::optional<std::string> { return std::nullopt; }, .home = root};
      size_t observations = 0;
      const biv::adapters::Host host{
          .home = root,
          .env = env,
          .version_probe = [&](const std::string_view agent,
                               const std::optional<fs::path>& requested) -> biv::expected<biv::support::ProbeEvidence> {
            ++observations;
            CHECK(agent == "codex");
            CHECK(requested == std::optional<fs::path>{pin});
            return biv::support::ProbeEvidence{.agent = "host-probe",
                                               .requested = requested,
                                               .executed = pin,
                                               .pinned = true,
                                               .outcome = biv::support::ProbeOutcome::ok,
                                               .exit_code = 0,
                                               .raw = probe_case.raw,
                                               .parsed = std::nullopt};
          },
          .pinned_bins = {{"codex", pin}}};

      const auto caps = biv::adapters::codex_adapter().capabilities(host);

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
      CHECK(caps.probe->agent == "codex");
      CHECK(caps.per_verb.collect);
      CHECK(caps.per_verb.install);
      CHECK(caps.per_verb.rewrite);
      fs::remove_all(root);
    }
  }
}

TEST_CASE("Task 3 Codex capabilities preserve not-found and timeout evidence") {
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

      const auto caps = biv::adapters::codex_adapter().capabilities(host);

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

  const auto caps = biv::adapters::codex_adapter().capabilities(host);

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
      biv::adapters::codex_adapter().capabilities(error_host);

  REQUIRE(error_caps.probe.has_value());
  CHECK(error_caps.probe->outcome ==
        biv::support::ProbeOutcome::spawn_error);
  CHECK(error_caps.probe->raw == "probe error \xEF\xBF\xBD");
  CHECK(biv::support::sanitize_utf8(error_caps.probe->raw) ==
        error_caps.probe->raw);
  fs::remove_all(error_root);
}

TEST_CASE("Task 5 Codex absent store dominates readable probe") {
  const auto root = make_tmp("probe-store-orthogonal");
  const auto& adapter = biv::adapters::codex_adapter();
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
                                           .executed = root / "bin" / "codex",
                                           .pinned = false,
                                           .outcome = biv::support::ProbeOutcome::ok,
                                           .exit_code = 0,
                                           .raw = "codex-cli 0.144.4",
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

  fs::create_directories(root / ".codex");
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
    "Task 3 Codex install consumes supplied capabilities and has no "
    "store oracle") {
  const auto root = make_tmp("supplied-capabilities");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  {
    std::ofstream marker{store / "version.json"};
    marker << "{\"version\":\"0.61.0\"}\n";
  }
  auto members = codex_members();
  auto capabilities = biv::adapters::Capabilities::from_probe(
      biv::adapters::Capabilities::Verdict::readable,
      std::optional<std::string>{"0.144.4"}, false, true,
      {.collect = true, .install = true, .rewrite = true});
  auto target = target_for(workspace, store, members, std::move(capabilities));

  const auto installed = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::vector<biv::manifest::AgentSessionEntry>{codex_entry()});

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1);
  CHECK(installed->sessions.front().outcome == biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK_FALSE(installed->sessions.front().host_version_unverified);
  const auto source = read_text(fs::path{BIV_SOURCE_DIR} / "src" / "adapters" / "codex" / "install.cpp");
  CHECK(source.find("capabilities_for_root") == std::string::npos);
  fs::remove_all(root);
}

TEST_CASE("Codex preserves a capability refusal through a containment publish fact") {
  const auto root = make_tmp("cell-c4");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  const auto outside = root / "outside";
  fs::create_directories(workspace);
  fs::create_directories(store);
  fs::create_directories(outside);
  fs::create_directory_symlink(outside, store / "sessions");
  auto members = codex_members();
  auto target = target_for(workspace, store, members);

  auto refused =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee9004");
  refused.agent_version_at_pack = "unknown";
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry(),
                                                              refused};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  const auto row_for = [&](std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto cohort_row = row_for(codex_entry().original_session_ids.primary);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(cohort_row != result->sessions.end());

  CHECK(refused_row->reason == std::optional<std::string>{"not-validated"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  CHECK(cohort_row->reason ==
        std::optional<std::string>{"containment_refused"});

  CHECK(result->id_map.empty());
  CHECK(result->activation.empty());
  CHECK(relative_files(outside).empty());
  fs::remove_all(root);
}

TEST_CASE("Codex preserves a capability refusal through an ambient publish fault") {
  const auto root = make_tmp("cell-c3");
  const auto workspace = root / "workspace";
  const auto store = root / "never-created";
  fs::create_directories(workspace);
  auto members = codex_members();
  auto target = target_for(workspace, store, members);

  auto refused =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee9003");
  refused.agent_version_at_pack = "unknown";
  const std::vector<biv::manifest::AgentSessionEntry> records{codex_entry(),
                                                              refused};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result.has_value());
  REQUIRE(result->sessions.size() == 2);
  const auto row_for = [&](std::string_view id) {
    return std::ranges::find_if(result->sessions, [&](const auto& row) {
      return row.image_session_id == id;
    });
  };
  const auto refused_row = row_for(refused.original_session_ids.primary);
  const auto cohort_row = row_for(codex_entry().original_session_ids.primary);
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

TEST_CASE("Codex install refuses a retained undecodable JSONL line") {
  const auto root = make_tmp("undecodable-line");
  auto members = codex_members();
  members[parent_artifact()] = bytes("{bad\n");
  auto target = target_for(root / "workspace", root / "store", members);
  const auto result = biv::adapters::codex_install(
      target, biv::adapters::Consent::no,
      std::vector<biv::manifest::AgentSessionEntry>{codex_entry()});
  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().reason == std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.front().detail == std::optional<std::string>{"undecodable_line"});
  fs::remove_all(root);
}

TEST_CASE("Codex install accepts an empty JSONL artifact as zero records") {
  const auto root = make_tmp("empty-jsonl");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto members = codex_members();
  members.at(child_artifact()).clear();
  auto target = target_for(workspace, store, members);

  const auto installed = biv::adapters::codex_install(
      target, biv::adapters::Consent::yes,
      std::vector<biv::manifest::AgentSessionEntry>{codex_entry()});

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1U);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(installed->sessions.front().verify.artifacts_checked == 2U);
  REQUIRE(installed->id_map.size() == 1U);
  REQUIRE(installed->id_map.front().children.size() == 1U);
  const auto files = relative_files(store);
  REQUIRE(files.size() == 2U);
  const auto child_file = std::ranges::find_if(files, [&](const auto& file) {
    return file.find(installed->id_map.front().children.front().second) !=
           std::string::npos;
  });
  REQUIRE(child_file != files.end());
  CHECK(fs::is_empty(store / *child_file));
  fs::remove_all(root);
}

TEST_CASE("Codex non-staged artifact identity mismatch refuses the whole set") {
  constexpr std::string_view wrong_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0999";
  const auto root = make_tmp("identity-mismatch");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  auto record = codex_entry();
  record.children.clear();
  record.artifacts = {"agents/codex/" + std::string{wrong_id} + ".jsonl"};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(record.artifacts.front(), std::vector<std::byte>{});
  auto target = target_for(workspace, store, members);

  const auto installed = biv::adapters::codex_install(
      target, biv::adapters::Consent::yes,
      std::vector<biv::manifest::AgentSessionEntry>{record});

  REQUIRE(installed.has_value());
  REQUIRE(installed->sessions.size() == 1U);
  CHECK(installed->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(installed->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(installed->id_map.empty());
  CHECK(installed->activation.empty());
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "Codex preserves an undecodable refusal through an ambient publish fault") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0911";
  constexpr std::string_view cohort_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0912";
  const auto root = make_tmp("verify-refusal-ambient-fault");
  const auto workspace = root / "workspace";
  fs::create_directories(workspace);
  auto refused = codex_entry(std::string{refused_id});
  auto cohort = codex_entry(std::string{cohort_id});
  refused.children.clear();
  cohort.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(refused.artifacts.front(), bytes("{bad\n"));
  members.emplace(
      cohort.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{cohort_id} + "\",\"session_id\":\"" +
            std::string{cohort_id} + "\",\"cwd\":\"/ws/proj\"," +
            "\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, root / "never-created", members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::vector{refused, cohort});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  const auto refused_row = std::ranges::find(
      result->sessions, refused_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  const auto cohort_row = std::ranges::find(
      result->sessions, cohort_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(cohort_row != result->sessions.end());
  CHECK(refused_row->reason == std::optional<std::string>{"verify-hits"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"undecodable_line"});
  CHECK(cohort_row->reason == std::optional<std::string>{"error"});
  CHECK(cohort_row->detail == std::optional<std::string>{"ENOENT"});
  fs::remove_all(root);
}

TEST_CASE("Codex verifies every session against the image origin union") {
  constexpr std::string_view first_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0011";
  constexpr std::string_view second_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0012";
  const auto root = make_tmp("image-origin-union");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto first = codex_entry(std::string{first_id}, "unused-first-child");
  auto second = codex_entry(std::string{second_id}, "unused-second-child");
  first.children.clear();
  second.children.clear();
  first.original_path = "/srv/alpha";
  first.normalized_path_key = first.original_path;
  second.original_path = "/srv/beta";
  second.normalized_path_key = second.original_path;
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      first.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{first_id} +
            R"(","session_id":")" + std::string{first_id} +
            R"(","cwd":"/srv/alpha"}})" + "\n"));
  members.emplace(
      second.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{second_id} +
            R"(","session_id":")" + std::string{second_id} +
            R"(","cwd":"/srv/beta","foreign_path":"/srv/alpha","foreign_id":")" +
            std::string{first_id} + R"("}})" + "\n"));
  auto target = target_for(workspace, store, members);
  const std::vector records{first, second};

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(1).reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.at(1).detail ==
        std::optional<std::string>{"origin_path"});
  CHECK(result->sessions.at(1).verify.origin_path_hits > 0U);
  CHECK(result->sessions.at(1).verify.origin_id_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE("B2 image union includes Codex manifest parent session IDs") {
  constexpr std::string_view origin_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0411";
  constexpr std::string_view recipient_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0412";
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0413";
  const auto root = make_tmp("image-origin-parent-union");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto parent = codex_entry(std::string{parent_id}, "unused-parent-child");
  auto origin = codex_entry(std::string{origin_id}, "unused-origin-child");
  auto recipient =
      codex_entry(std::string{recipient_id}, "unused-recipient-child");
  parent.children.clear();
  origin.children.clear();
  recipient.children.clear();
  origin.original_session_ids.parent = std::string{parent_id};
  parent.original_path = "/srv/parent";
  parent.normalized_path_key = parent.original_path;
  origin.original_path = "/srv/alpha";
  origin.normalized_path_key = origin.original_path;
  recipient.original_path = "/srv/beta";
  recipient.normalized_path_key = recipient.original_path;
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      parent.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{parent_id} + R"(","session_id":")" +
            std::string{parent_id} + R"(","cwd":"/srv/parent"}})" + "\n"));
  members.emplace(
      origin.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{origin_id} + R"(","session_id":")" +
            std::string{origin_id} + R"(","cwd":"/srv/alpha","parent_thread_id":")" +
            std::string{parent_id} + R"("}})" + "\n"));
  members.emplace(
      recipient.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{recipient_id} + R"(","session_id":")" +
            std::string{recipient_id} +
            R"(","cwd":"/srv/beta","foreign_id":")" +
            std::string{parent_id} + R"("}})" + "\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes,
      std::array{parent, origin, recipient});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 3U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK(result->sessions.at(1).verify.origin_id_hits == 0U);
  REQUIRE(result->id_map.size() == 2U);
  const auto parent_map = std::ranges::find_if(
      result->id_map, [&](const biv::adapters::IdMapEntry& entry) {
        return entry.image_session_id == parent_id;
      });
  const auto origin_map = std::ranges::find_if(
      result->id_map, [&](const biv::adapters::IdMapEntry& entry) {
        return entry.image_session_id == origin_id;
      });
  REQUIRE(parent_map != result->id_map.end());
  REQUIRE(origin_map != result->id_map.end());
  const auto files = relative_files(store);
  const auto origin_file = std::ranges::find_if(
      files, [&](const std::string& file) {
        return file.find(origin_map->installed_session_id) != std::string::npos;
      });
  REQUIRE(origin_file != files.end());
  const auto origin_text = read_text(store / *origin_file);
  CHECK(origin_text.find(parent_map->installed_session_id) !=
        std::string::npos);
  CHECK(origin_text.find(parent_id) == std::string::npos);
  CHECK(result->sessions.at(2).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(2).reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.at(2).detail ==
        std::optional<std::string>{"origin_id"});
  CHECK(result->sessions.at(2).verify.origin_id_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE("B2 image union includes Codex manifest child session IDs") {
  constexpr std::string_view origin_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0421";
  constexpr std::string_view recipient_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0422";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0423";
  const auto root = make_tmp("image-origin-child-union");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto origin = codex_entry(std::string{origin_id}, std::string{child_id});
  auto recipient =
      codex_entry(std::string{recipient_id}, "unused-recipient-child");
  origin.children.front().artifacts.clear();
  origin.agent_version_at_pack = "999.0.0";
  recipient.children.clear();
  origin.original_path = "/srv/alpha";
  origin.normalized_path_key = origin.original_path;
  recipient.original_path = "/srv/beta";
  recipient.normalized_path_key = recipient.original_path;
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      origin.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{origin_id} + R"(","session_id":")" +
            std::string{origin_id} + R"(","cwd":"/srv/alpha"}})" + "\n"));
  members.emplace(
      recipient.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{recipient_id} + R"(","session_id":")" +
            std::string{recipient_id} +
            R"(","cwd":"/srv/beta","foreign_id":")" +
            std::string{child_id} + R"("}})" + "\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::array{origin, recipient});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(0).reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(1).reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.at(1).detail ==
        std::optional<std::string>{"origin_id"});
  CHECK(result->sessions.at(1).verify.origin_id_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE("B2 image union includes Codex parent IDs from refused rows") {
  constexpr std::string_view origin_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0431";
  constexpr std::string_view recipient_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0432";
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0433";
  const auto root = make_tmp("image-origin-parent-refused-union");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto origin = codex_entry(std::string{origin_id}, "unused-origin-child");
  auto recipient =
      codex_entry(std::string{recipient_id}, "unused-recipient-child");
  origin.children.clear();
  recipient.children.clear();
  origin.agent_version_at_pack = "999.0.0";
  origin.original_session_ids.parent = std::string{parent_id};
  origin.original_session_ids.parent_in_image = false;
  origin.original_path = "/srv/alpha";
  origin.normalized_path_key = origin.original_path;
  recipient.original_path = "/srv/beta";
  recipient.normalized_path_key = recipient.original_path;
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      origin.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{origin_id} + R"(","session_id":")" +
            std::string{origin_id} +
            R"(","cwd":"/srv/alpha","parent_thread_id":")" +
            std::string{parent_id} + R"("}})" + "\n"));
  members.emplace(
      recipient.artifacts.front(),
      bytes(std::string{R"({"type":"session_meta","payload":{"id":")"} +
            std::string{recipient_id} + R"(","session_id":")" +
            std::string{recipient_id} +
            R"(","cwd":"/srv/beta","foreign_id":")" +
            std::string{parent_id} + R"("}})" + "\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, std::array{origin, recipient});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(0).reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(1).reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(result->sessions.at(1).detail ==
        std::optional<std::string>{"origin_id"});
  CHECK(result->sessions.at(1).verify.origin_id_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE("Codex mixed verify failures preserve rows and publish clean siblings") {
  const auto root = make_tmp("mixed-verify-radius");
  const auto workspace = root / "workspace";
  const auto store = root / "codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  constexpr std::string_view undecodable_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0901";
  constexpr std::string_view verify_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0902";
  constexpr std::string_view clean_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0903";
  constexpr std::string_view capability_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0904";

  auto undecodable = codex_entry(std::string{undecodable_id});
  auto verify = codex_entry(std::string{verify_id});
  auto clean = codex_entry(std::string{clean_id});
  auto capability = codex_entry(std::string{capability_id});
  for (auto* record : {&undecodable, &verify, &clean, &capability}) {
    record->children.clear();
  }
  undecodable.original_path = "/undecodable-origin";
  verify.original_path = "/verify-origin";
  clean.original_path = "/clean-origin";
  capability.original_path = "/capability-origin";
  capability.agent_version_at_pack = "unknown";

  const auto transcript = [](const std::string_view id,
                             const std::string_view cwd) {
    return bytes(std::string{"{\"timestamp\":\"2026-07-06T01:00:00Z\","} +
                 "\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                 std::string{id} + "\",\"session_id\":\"" +
                 std::string{id} + "\",\"cwd\":\"" + std::string{cwd} +
                 "\",\"cli_version\":\"0.142.5\"}}\n");
  };
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace("agents/codex/" + std::string{undecodable_id} + ".jsonl",
                  bytes("{bad\n"));
  members.emplace("agents/codex/" + std::string{verify_id} + ".jsonl",
                  bytes(std::string{"{\"timestamp\":\"2026-07-06T01:00:00Z\","} +
                        "\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                        std::string{verify_id} + "\",\"session_id\":\"" +
                        std::string{verify_id} +
                        "\",\"cwd\":\"/verify-origin\"," +
                        "\"foreign_path\":\"/verify-origin2\"," +
                        "\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace("agents/codex/" + std::string{clean_id} + ".jsonl",
                  transcript(clean_id, "/clean-origin"));
  members.emplace("agents/codex/" + std::string{capability_id} + ".jsonl",
                  transcript(capability_id, "/capability-origin"));

  auto target = target_for(workspace, store, members);
  const std::vector records{undecodable, verify, clean, capability};
  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::yes, records);

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 4U);
  const auto row_for = [&](const std::string_view id) {
    return std::ranges::find(result->sessions, id,
                             &biv::adapters::InstallSessionOutcome::image_session_id);
  };
  const auto undecodable_row = row_for(undecodable_id);
  const auto verify_row = row_for(verify_id);
  const auto clean_row = row_for(clean_id);
  const auto capability_row = row_for(capability_id);
  REQUIRE(undecodable_row != result->sessions.end());
  REQUIRE(verify_row != result->sessions.end());
  REQUIRE(clean_row != result->sessions.end());
  REQUIRE(capability_row != result->sessions.end());
  CHECK(undecodable_row->reason ==
        std::optional<std::string>{"verify-hits"});
  CHECK(undecodable_row->detail ==
        std::optional<std::string>{"undecodable_line"});
  CHECK(verify_row->reason == std::optional<std::string>{"verify-hits"});
  CHECK(verify_row->detail == std::optional<std::string>{"origin_path"});
  CHECK(verify_row->verify.origin_path_hits > 0U);
  CHECK(clean_row->outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::installed);
  CHECK_FALSE(clean_row->reason.has_value());
  CHECK(capability_row->reason ==
        std::optional<std::string>{"not-validated"});
  CHECK(capability_row->detail ==
        std::optional<std::string>{"basis_unorderable"});
  REQUIRE(result->id_map.size() == 1U);
  CHECK(result->id_map.front().image_session_id == clean_id);
  REQUIRE(result->activation.size() == 1U);
  CHECK(result->activation.front().command ==
        "codex resume " + result->id_map.front().installed_session_id);
  const auto files = relative_files(store);
  REQUIRE(files.size() == 1U);
  CHECK(files.front().find(result->id_map.front().installed_session_id) !=
        std::string::npos);
  const auto installed = read_text(store / files.front());
  CHECK(installed.find("/clean-origin") == std::string::npos);
  CHECK(installed.find(workspace.generic_string()) != std::string::npos);
  fs::remove_all(root);
}

TEST_CASE(
    "R-6 Codex consent-no checks both payload identity arms and stages a clean sibling") {
  constexpr std::string_view refused_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a01";
  constexpr std::string_view foreign_session_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a02";
  constexpr std::string_view clean_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a03";
  constexpr std::string_view wrong_id_record =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a04";
  constexpr std::string_view foreign_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a05";
  const auto root = make_tmp("codex-divergent-payload-identities");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto refused = codex_entry(std::string{refused_id});
  auto clean = codex_entry(std::string{clean_id});
  auto wrong_id = codex_entry(std::string{wrong_id_record});
  refused.children.clear();
  clean.children.clear();
  wrong_id.children.clear();
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      refused.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{refused_id} + "\",\"session_id\":\"" +
            std::string{foreign_session_id} +
            "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      clean.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{clean_id} + "\",\"session_id\":\"" +
            std::string{clean_id} +
            "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      wrong_id.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{foreign_id} + "\",\"session_id\":\"" +
            std::string{wrong_id_record} +
            "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no,
      std::array{refused, clean, wrong_id});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 3U);
  const auto refused_row = std::ranges::find(
      result->sessions, refused_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  const auto clean_row = std::ranges::find(
      result->sessions, clean_id,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  const auto wrong_id_row = std::ranges::find(
      result->sessions, wrong_id_record,
      &biv::adapters::InstallSessionOutcome::image_session_id);
  REQUIRE(refused_row != result->sessions.end());
  REQUIRE(clean_row != result->sessions.end());
  REQUIRE(wrong_id_row != result->sessions.end());
  CHECK(refused_row->outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(refused_row->reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(refused_row->detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  CHECK(clean_row->outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::staged);
  CHECK(wrong_id_row->outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(wrong_id_row->reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(wrong_id_row->detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  REQUIRE(result->id_map.size() == 1U);
  CHECK(result->id_map.front().image_session_id == clean_id);
  CHECK(relative_files(workspace / ".biv/agents/codex").size() == 1U);
  CHECK(relative_files(store).empty());
  fs::remove_all(root);
}

TEST_CASE(
    "R-5 Codex preserves a typed identity refusal over an earlier verify hit") {
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a11";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a12";
  constexpr std::string_view foreign_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a13";
  const auto root = make_tmp("codex-typed-refusal-precedence");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto record = codex_entry(std::string{parent_id}, std::string{child_id});
  record.original_path = "/typed-origin";
  record.normalized_path_key = record.original_path;
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      record.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{parent_id} + "\",\"session_id\":\"" +
            std::string{parent_id} +
            "\",\"cwd\":\"/typed-origin\",\"foreign_path\":"
            "\"/typed-origin-suffix\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      record.children.front().artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{child_id} + "\",\"session_id\":\"" +
            std::string{foreign_id} + "\",\"parent_thread_id\":\"" +
            std::string{parent_id} +
            "\",\"cwd\":\"/typed-origin\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no,
      std::array{record});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  CHECK(result->sessions.front().verify.origin_path_hits > 0U);
  fs::remove_all(root);
}

TEST_CASE(
    "R-1b Codex refuses an unrecoverable separately mapped parent lineage") {
  constexpr std::string_view parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a21";
  constexpr std::string_view child_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0a22";
  const auto root = make_tmp("codex-unrecoverable-parent-lineage");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);

  auto parent = codex_entry(std::string{parent_id}, "unused-parent-child");
  auto child = codex_entry(std::string{child_id}, "unused-child-child");
  parent.children.clear();
  child.children.clear();
  child.original_session_ids.parent = std::string{parent_id};
  std::map<std::string, std::vector<std::byte>> members;
  members.emplace(
      parent.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{parent_id} +
            "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"));
  members.emplace(
      child.artifacts.front(),
      bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
            std::string{child_id} +
            "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n"));
  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no, std::array{parent, child});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 2U);
  CHECK(result->sessions.at(0).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::staged);
  CHECK(result->sessions.at(1).outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.at(1).reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->sessions.at(1).detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  REQUIRE(result->id_map.size() == 1U);
  CHECK(result->id_map.front().image_session_id == parent_id);
  fs::remove_all(root);
}

namespace slice_e_install_guards {

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
  ScopedEnv(const ScopedEnv&) = delete;
  ScopedEnv& operator=(const ScopedEnv&) = delete;

 private:
  std::string name_;
  std::optional<std::string> previous_;
};

class ScopedPackDiscoveryEnv {
 public:
  explicit ScopedPackDiscoveryEnv(const fs::path& root)
      : home_{"HOME", root / "home"},
        claude_{"CLAUDE_CONFIG_DIR", root / "absent-claude"},
        codex_{"CODEX_HOME", root / "target-codex"},
        sqlite_{"CODEX_SQLITE_HOME", root / "absent-sqlite"} {}

 private:
  ScopedEnv home_;
  ScopedEnv claude_;
  ScopedEnv codex_;
  ScopedEnv sqlite_;
};

void require_store_roots_under(const fs::path& root,
                               std::initializer_list<fs::path> paths) {
  const auto canonical_root = fs::canonical(root);
  for (const auto& path : paths) {
    const auto relative =
        fs::weakly_canonical(path).lexically_relative(canonical_root);
    CAPTURE(path, relative);
    REQUIRE(!relative.empty());
    REQUIRE(*relative.begin() != "..");
  }
}

}  // namespace slice_e_install_guards

TEST_CASE("FX-A12-6 Codex install validates a grandchild against its own parent",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view root_id =
      "019fa120-0000-7000-8000-000000000601";
  constexpr std::string_view parent_id =
      "019fa120-0000-7000-8000-000000000602";
  constexpr std::string_view child_id =
      "019fa120-0000-7000-8000-000000000603";
  const auto root = make_tmp("slice-e-fx-a12-6");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  const slice_e_install_guards::ScopedPackDiscoveryEnv discovery_env{root};

  auto record = codex_entry(std::string{root_id}, std::string{parent_id});
  record.children.push_back(biv::manifest::SessionChild{
      .original_id = std::string{child_id},
      .artifacts = {"agents/codex/" + std::string{child_id} + ".jsonl"}});
  std::map<std::string, std::vector<std::byte>> members;
  const auto fixture = fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
                       "slice-e" / "codex" /
                       "descendant-validated-own-parent";
  for (const auto id : {root_id, parent_id, child_id}) {
    const auto artifact = "agents/codex/" + std::string{id} + ".jsonl";
    members.emplace(artifact, bytes(read_text(fixture / artifact)));
  }
  members.emplace("auth.json", bytes("SLICE_E_CREDENTIAL_DECOY"));
  std::vector<std::string> member_reads;
  auto target = target_for(workspace, store, members);
  target.member_read = [&](const std::string_view path)
      -> biv::expected<std::vector<std::byte>> {
    member_reads.emplace_back(path);
    const auto found = members.find(std::string{path});
    if (found == members.end()) {
      return std::unexpected(
          biv::BivError{biv::ErrKind::ImageUnreadable, std::string{path}});
    }
    return found->second;
  };

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no, std::array{record});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::staged);
  CHECK(result->sessions.front().reason == std::nullopt);
  CHECK(result->sessions.front().detail == std::nullopt);
  CHECK(result->id_map.size() == 1U);
  if (!result->id_map.empty()) {
    CHECK(result->id_map.front().children.size() == 2U);
  }
  CHECK(std::ranges::none_of(member_reads, [](const std::string& path) {
    return path == "auth.json";
  }));
  CHECK(std::ranges::all_of(member_reads, [](const std::string& path) {
    return path.starts_with("agents/codex/");
  }));
  slice_e_install_guards::require_store_roots_under(root,
                                                    {workspace, store});
  fs::remove_all(root);
}

TEST_CASE("FX-A12-4a a present inconsistent parent edge refuses",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view root_id =
      "019fa120-0000-7000-8000-000000000411";
  constexpr std::string_view declared_parent =
      "019fa120-0000-7000-8000-000000000412";
  constexpr std::string_view child_id =
      "019fa120-0000-7000-8000-000000000413";
  constexpr std::string_view actual_parent =
      "019fa120-0000-7000-8000-000000000499";
  const auto root = make_tmp("slice-e-fx-a12-4a");
  const auto workspace = root / "workspace";
  const auto store = root / "target-codex";
  fs::create_directories(workspace);
  fs::create_directories(store);
  const slice_e_install_guards::ScopedPackDiscoveryEnv discovery_env{root};

  auto record = codex_entry(std::string{root_id},
                            std::string{declared_parent});
  record.children.push_back(biv::manifest::SessionChild{
      .original_id = std::string{child_id},
      .artifacts = {"agents/codex/" + std::string{child_id} + ".jsonl"},
      .parent_id = std::string{declared_parent}});
  record.children.push_back(biv::manifest::SessionChild{
      .original_id = std::string{actual_parent},
      .artifacts = {"agents/codex/" + std::string{actual_parent} + ".jsonl"}});
  std::map<std::string, std::vector<std::byte>> members;
  const auto simple_artifact = [&](const std::string_view id) {
    return bytes(std::string{"{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                 std::string{id} + "\",\"session_id\":\"" +
                 std::string{id} +
                 "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n");
  };
  members.emplace(record.artifacts.front(), simple_artifact(root_id));
  members.emplace(record.children.at(0).artifacts.front(),
                  simple_artifact(declared_parent));
  const auto fixture = fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
                       "slice-e" / "data-only" /
                       "4a-edge-inconsistency-refuses" / "artifact.jsonl";
  members.emplace(record.children.at(1).artifacts.front(),
                  bytes(read_text(fixture)));
  members.emplace(record.children.at(2).artifacts.front(),
                  simple_artifact(actual_parent));
  auto absent_record = record;
  absent_record.children.at(1).parent_id = std::nullopt;
  fs::create_directories(root / "absent-workspace");
  fs::create_directories(root / "absent-store");
  auto absent_target =
      target_for(root / "absent-workspace", root / "absent-store", members);

  const auto absent_result = biv::adapters::codex_adapter().install(
      absent_target, biv::adapters::Consent::no, std::array{absent_record});

  REQUIRE(absent_result);
  REQUIRE(absent_result->sessions.size() == 1U);
  CHECK(absent_result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::staged);
  CHECK(absent_result->sessions.front().reason == std::nullopt);
  CHECK(absent_result->sessions.front().detail == std::nullopt);
  REQUIRE(absent_result->id_map.size() == 1U);

  auto target = target_for(workspace, store, members);

  const auto result = biv::adapters::codex_adapter().install(
      target, biv::adapters::Consent::no, std::array{record});

  REQUIRE(result);
  REQUIRE(result->sessions.size() == 1U);
  CHECK(result->sessions.front().outcome ==
        biv::adapters::InstallSessionOutcome::Outcome::failed);
  CHECK(result->sessions.front().reason ==
        std::optional<std::string>{"containment_refused"});
  CHECK(result->sessions.front().detail ==
        std::optional<std::string>{"staged_identity_mismatch"});
  CHECK(result->id_map.empty());
  fs::remove_all(root);
}

TEST_CASE("FX-A12-5 adding a consistent edge never grants acceptance",
          "[slice-e][slice-e-red]") {
  constexpr std::string_view root_id =
      "019fa120-0000-7000-8000-000000000511";
  constexpr std::string_view parent_id =
      "019fa120-0000-7000-8000-000000000512";
  constexpr std::string_view child_id =
      "019fa120-0000-7000-8000-000000000513";
  for (const auto edge_present : {false, true}) {
    DYNAMIC_SECTION("edge present=" << edge_present) {
      const auto root = make_tmp(edge_present ? "slice-e-fx-a12-5-edge"
                                              : "slice-e-fx-a12-5-absent");
      const auto workspace = root / "workspace";
      const auto store = root / "target-codex";
      fs::create_directories(workspace);
      fs::create_directories(store);
      const slice_e_install_guards::ScopedPackDiscoveryEnv discovery_env{root};

      auto record = codex_entry(std::string{root_id}, std::string{parent_id});
      record.children.push_back(biv::manifest::SessionChild{
          .original_id = std::string{child_id},
          .artifacts = {"agents/codex/" + std::string{child_id} + ".jsonl"},
          .parent_id = edge_present
                           ? std::optional<std::string>{parent_id}
                           : std::nullopt});
      std::map<std::string, std::vector<std::byte>> members;
      const auto simple_artifact = [&](const std::string_view id) {
        return bytes(std::string{
                         "{\"type\":\"session_meta\",\"payload\":{\"id\":\""} +
                     std::string{id} + "\",\"session_id\":\"" +
                     std::string{id} +
                     "\",\"cwd\":\"/ws/proj\",\"cli_version\":\"0.142.5\"}}\n");
      };
      members.emplace(record.artifacts.front(), simple_artifact(root_id));
      members.emplace(record.children.front().artifacts.front(),
                      simple_artifact(parent_id));
      const auto fixture = fs::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
                           "slice-e" / "data-only" /
                           "5-mono-adding-edge-never-grants" /
                           "artifact.jsonl";
      members.emplace(record.children.back().artifacts.front(),
                      bytes(read_text(fixture)));
      auto target = target_for(workspace, store, members);

      const auto result = biv::adapters::codex_adapter().install(
          target, biv::adapters::Consent::no, std::array{record});

      REQUIRE(result);
      REQUIRE(result->sessions.size() == 1U);
      CHECK(result->sessions.front().outcome ==
            biv::adapters::InstallSessionOutcome::Outcome::staged);
      CHECK(result->sessions.front().reason == std::nullopt);
      CHECK(result->sessions.front().detail == std::nullopt);
      REQUIRE(result->id_map.size() == 1U);
      CHECK(result->id_map.front().children.size() == 2U);
      fs::remove_all(root);
    }
  }
}
