#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstddef>
#include <cstdint>
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

TEST_CASE(
    "Codex rewrite verification preserves a sibling capability refusal") {
  const auto root = make_tmp("verify-refusal-cohort");
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
  auto refused =
      codex_entry("019faaaa-bbbb-7ccc-8ddd-eeeeeeee9005");
  refused.agent_version_at_pack = "unknown";
  refused.children.clear();
  refused.artifacts.clear();
  const std::vector<biv::manifest::AgentSessionEntry> records{refused,
                                                              codex_entry()};

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
  const auto verify_row = row_for(codex_entry().original_session_ids.primary);
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
