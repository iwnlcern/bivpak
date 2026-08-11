#include <array>
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "adapters/rewrite_common.hpp"
#include "core/manifest/manifest.hpp"

namespace {

std::vector<std::byte> bytes_of(const std::string& text) {
  std::vector<std::byte> bytes(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    bytes[i] = static_cast<std::byte>(static_cast<unsigned char>(text[i]));
  }
  return bytes;
}

biv::manifest::Manifest fixed_manifest() {
  return biv::manifest::Manifest{
      .format_version = 1,
      .required_capabilities = {},
      .image_id = "00000000-0000-4000-8000-000000000000",
      .app_version = "0.1.0",
      .created_at = "2026-07-05T00:00:00Z",
      .source_path = "/mnt/c/tmp/plain",
      .source_path_flavor = biv::manifest::PathFlavor::wsl,
      .agent_sessions = {},
      .bivignore = {.source = "builtin", .builtin_id = "builtin-v1", .sha256_hex = "abc123"}};
}

biv::manifest::AgentSessionEntry codex_session_entry() {
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "codex";
  entry.agent_version_at_pack = "0.142.5";
  entry.relpath_key = ".";
  entry.original_path = "/mnt/c/Users/x/proj";
  entry.normalized_path_key = "/mnt/c/users/x/proj";
  entry.normalization_scheme = "codex-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::wsl;
  entry.provenance = {.store_root = "/home/u/.codex",
                      .locator = "sessions_root",
                      .discovery_tier = "default",
                      .archived = false};
  entry.original_session_ids = {.primary = "019f-aaaa", .parent = std::nullopt, .parent_in_image = std::nullopt};
  entry.children = {{.original_id = "019f-bbbb", .artifacts = {"agents/codex/019f-bbbb.jsonl"}}};
  entry.artifacts = {"agents/codex/019f-aaaa.jsonl"};
  entry.live_at_pack = false;
  entry.imported_at = "2026-07-07T00:00:00Z";
  entry.entry_schema = 1;
  return entry;
}

std::string manifest_json_with(std::vector<biv::manifest::AgentSessionEntry> entries) {
  auto manifest = fixed_manifest();
  manifest.agent_sessions = std::move(entries);
  return biv::manifest::serialize(manifest);
}

std::string carrier_json(const std::string& injected) {
  return "{"
         "\"format_version\":1,"
         "\"required_capabilities\":[],"
         "\"image_id\":\"id\","
         "\"app_version\":\"0.1.0\","
         "\"created_at\":\"2026-07-05T00:00:00Z\","
         "\"source_path\":\"/tmp/plain\","
         "\"source_path_flavor\":\"posix\"," +
         injected +
         "\"bivignore\":{\"source\":\"file\",\"builtin_id\":null,\"sha256\":\"def\"},"
         "\"repos\":[],\"agent_sessions\":[]"
         "}";
}

}  // namespace

TEST_CASE("packer_home serializes after source_path_flavor and round-trips") {
  auto manifest = fixed_manifest();
  manifest.packer_home = biv::manifest::PackerHome{
      .path = "/Users/jack", .flavor = biv::manifest::PathFlavor::posix};

  const auto json = biv::manifest::serialize(manifest);
  REQUIRE(json.find("\"packer_home\": \"/Users/jack\"") != std::string::npos);
  REQUIRE(json.find("\"packer_home_flavor\": \"posix\"") != std::string::npos);
  REQUIRE(json.find("\"source_path_flavor\"") < json.find("\"packer_home\""));

  const auto parsed = biv::manifest::parse(bytes_of(json));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->packer_home == manifest.packer_home);
  // ORACLE RULE: captured at BASE 2341667 for the engaged carrier.
  // NEVER regenerate this literal from the serializer.
  REQUIRE(json ==
          "{\n"
          "  \"format_version\": 1,\n"
          "  \"required_capabilities\": [],\n"
          "  \"image_id\": \"00000000-0000-4000-8000-000000000000\",\n"
          "  \"app_version\": \"0.1.0\",\n"
          "  \"created_at\": \"2026-07-05T00:00:00Z\",\n"
          "  \"source_path\": \"/mnt/c/tmp/plain\",\n"
          "  \"source_path_flavor\": \"wsl\",\n"
          "  \"packer_home\": \"/Users/jack\",\n"
          "  \"packer_home_flavor\": \"posix\",\n"
          "  \"bivignore\": {\n"
          "    \"source\": \"builtin\",\n"
          "    \"builtin_id\": \"builtin-v1\",\n"
          "    \"sha256\": \"abc123\"\n"
          "  },\n"
          "  \"repos\": [],\n"
          "  \"agent_sessions\": []\n"
          "}\n");
}

TEST_CASE("packer_home round-trips every flavor spelling") {
  struct Row {
    std::string path;
    biv::manifest::PathFlavor flavor;
  };
  for (const auto& row : std::array{
           Row{"/home/user", biv::manifest::PathFlavor::posix},
           Row{"/mnt/c/Users/x", biv::manifest::PathFlavor::wsl},
           Row{"C:/Users/x", biv::manifest::PathFlavor::windows},
           Row{"C:\\Users\\x", biv::manifest::PathFlavor::windows},
           Row{"\\\\?\\C:\\Users\\x", biv::manifest::PathFlavor::windows},
       }) {
    CAPTURE(row.path);
    auto manifest = fixed_manifest();
    manifest.packer_home = biv::manifest::PackerHome{row.path, row.flavor};
    const auto parsed =
        biv::manifest::parse(bytes_of(biv::manifest::serialize(manifest)));
    REQUIRE(parsed.has_value());
    REQUIRE(parsed->packer_home == manifest.packer_home);
  }

  struct FactoryRow {
    std::string_view path;
    std::optional<biv::manifest::PathFlavor> flavor;
  };
  for (const auto& row : std::array{
           FactoryRow{"/x", biv::manifest::PathFlavor::posix},
           FactoryRow{"/Users/x", biv::manifest::PathFlavor::posix},
           FactoryRow{"/mnt/c/x", biv::manifest::PathFlavor::wsl},
           FactoryRow{"/mnt/c/Users/x", biv::manifest::PathFlavor::wsl},
           FactoryRow{"C:/x", biv::manifest::PathFlavor::windows},
           FactoryRow{"C:/Users/x", biv::manifest::PathFlavor::windows},
           FactoryRow{R"(\\?\C:\Users\x)",
                      biv::manifest::PathFlavor::windows},
           FactoryRow{"", std::nullopt},
           FactoryRow{"relative/home", std::nullopt},
           FactoryRow{"/", std::nullopt},
           FactoryRow{"/mnt/c/", std::nullopt},
           FactoryRow{"C:/", std::nullopt},
           FactoryRow{"C:\\", std::nullopt},
           FactoryRow{"//?/", std::nullopt},
           FactoryRow{R"(\\?\)", std::nullopt},
           FactoryRow{R"(\\?\C:\)", std::nullopt},
           FactoryRow{"//?/C:/", std::nullopt},
           FactoryRow{R"(\\?\C:)", std::nullopt},
           FactoryRow{R"(\\?\C:\x)", biv::manifest::PathFlavor::windows},
           FactoryRow{"//?/C:/x", biv::manifest::PathFlavor::windows},
       }) {
    CAPTURE(row.path);
    const auto actual = biv::manifest::make_packer_home(row.path);
    REQUIRE(actual.has_value() == row.flavor.has_value());
    if (actual) {
      CHECK(actual->path == row.path);
      CHECK(actual->flavor == *row.flavor);
      CHECK(biv::manifest::packer_home_valid(*actual));
    }
  }
}

TEST_CASE("packer_home absent round-trips and pre-carrier fixtures stay clean") {
  auto manifest = fixed_manifest();
  manifest.packer_home = std::nullopt;
  const auto json = biv::manifest::serialize(manifest);
  REQUIRE(json.find("packer_home") == std::string::npos);
  const auto parsed = biv::manifest::parse(bytes_of(json));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->packer_home == std::nullopt);

  const auto pre_carrier = biv::manifest::parse(bytes_of(carrier_json("")));
  REQUIRE(pre_carrier.has_value());
  REQUIRE(pre_carrier->packer_home == std::nullopt);
}

TEST_CASE("packer_home invalid engaged values collapse to absent on serialize") {
  for (const auto& bad : std::array{
           biv::manifest::PackerHome{"", biv::manifest::PathFlavor::posix},
           biv::manifest::PackerHome{"relative/home",
                                     biv::manifest::PathFlavor::posix},
           biv::manifest::PackerHome{"/home/user",
                                     biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{"/", biv::manifest::PathFlavor::posix},
           biv::manifest::PackerHome{"/mnt/c/", biv::manifest::PathFlavor::wsl},
           biv::manifest::PackerHome{"C:/", biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{"C:\\", biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{"//?/", biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{R"(\\?\)", biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{R"(\\?\C:\)",
                                     biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{"//?/C:/",
                                     biv::manifest::PathFlavor::windows},
           biv::manifest::PackerHome{R"(\\?\C:)",
                                     biv::manifest::PathFlavor::windows},
       }) {
    CAPTURE(bad.path);
    auto manifest = fixed_manifest();
    manifest.packer_home = bad;
    REQUIRE(biv::manifest::serialize(manifest).find("packer_home") ==
            std::string::npos);
  }
}

TEST_CASE("packer_home JSON null is missing for both keys") {
  const auto lone_null =
      biv::manifest::parse(bytes_of(carrier_json("\"packer_home\":null,")));
  REQUIRE(lone_null.has_value());
  REQUIRE(lone_null->packer_home == std::nullopt);

  const auto null_with_flavor = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":null,\"packer_home_flavor\":\"posix\",")));
  REQUIRE_FALSE(null_with_flavor.has_value());
  REQUIRE(null_with_flavor.error().detail == "packer_home_flavor");

  const auto home_with_null_flavor = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":\"/x\",\"packer_home_flavor\":null,")));
  REQUIRE_FALSE(home_with_null_flavor.has_value());
  REQUIRE(home_with_null_flavor.error().detail == "packer_home_flavor");

  const auto both_null = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":null,\"packer_home_flavor\":null,")));
  REQUIRE(both_null.has_value());
  REQUIRE(both_null->packer_home == std::nullopt);

  const auto lone_null_flavor = biv::manifest::parse(
      bytes_of(carrier_json("\"packer_home_flavor\":null,")));
  REQUIRE(lone_null_flavor.has_value());
  REQUIRE(lone_null_flavor->packer_home == std::nullopt);
}

TEST_CASE("packer_home lone keys fail closed naming the flavor key") {
  const auto lone_home =
      biv::manifest::parse(bytes_of(carrier_json("\"packer_home\":\"/x\",")));
  REQUIRE_FALSE(lone_home.has_value());
  REQUIRE(lone_home.error().detail == "packer_home_flavor");

  const auto lone_flavor = biv::manifest::parse(
      bytes_of(carrier_json("\"packer_home_flavor\":\"posix\",")));
  REQUIRE_FALSE(lone_flavor.has_value());
  REQUIRE(lone_flavor.error().detail == "packer_home_flavor");
}

TEST_CASE("packer_home malformed values fail closed naming the home key") {
  for (const auto& injected : std::array<std::string, 16>{
           "\"packer_home\":42,\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"relative/home\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"relative/home\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"relative/home\",\"packer_home_flavor\":\"wsl\",",
           "\"packer_home\":\"/home/user\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"/mnt/c/Users/x\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"/\",\"packer_home_flavor\":\"posix\",",
           "\"packer_home\":\"/mnt/c/\",\"packer_home_flavor\":\"wsl\",",
           "\"packer_home\":\"C:/\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"C:\\\\\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"//?/\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"\\\\\\\\?\\\\\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"\\\\\\\\?\\\\C:\\\\\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"//?/C:/\",\"packer_home_flavor\":\"windows\",",
           "\"packer_home\":\"\\\\\\\\?\\\\C:\",\"packer_home_flavor\":\"windows\",",
       }) {
    CAPTURE(injected);
    const auto parsed = biv::manifest::parse(bytes_of(carrier_json(injected)));
    REQUIRE_FALSE(parsed.has_value());
    REQUIRE(parsed.error().detail == "packer_home");
  }

  const auto extended_control = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":\"\\\\\\\\?\\\\C:\\\\Users\\\\x\","
      "\"packer_home_flavor\":\"windows\",")));
  REQUIRE(extended_control.has_value());
  REQUIRE(extended_control->packer_home == biv::manifest::PackerHome{
                                                R"(\\?\C:\Users\x)",
                                                biv::manifest::PathFlavor::windows});

  struct ExtendedBoundaryControl {
    std::string injected;
    std::string expected;
  };
  for (const auto& control : std::array{
           ExtendedBoundaryControl{
               "\"packer_home\":\"\\\\\\\\?\\\\C:\\\\x\","
               "\"packer_home_flavor\":\"windows\",",
               R"(\\?\C:\x)"},
           ExtendedBoundaryControl{
               "\"packer_home\":\"//?/C:/x\","
               "\"packer_home_flavor\":\"windows\",",
               "//?/C:/x"},
       }) {
    CAPTURE(control.expected);
    const auto parsed =
        biv::manifest::parse(bytes_of(carrier_json(control.injected)));
    REQUIRE(parsed.has_value());
    REQUIRE(parsed->packer_home == biv::manifest::PackerHome{
                                       control.expected,
                                       biv::manifest::PathFlavor::windows});
  }
}

TEST_CASE("packer_home flavor errors name the flavor key not source_path_flavor") {
  const auto unknown = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":\"/x\",\"packer_home_flavor\":\"vms\",")));
  REQUIRE_FALSE(unknown.has_value());
  REQUIRE(unknown.error().detail == "packer_home_flavor");

  const auto wrong_type = biv::manifest::parse(bytes_of(carrier_json(
      "\"packer_home\":\"/x\",\"packer_home_flavor\":42,")));
  REQUIRE_FALSE(wrong_type.has_value());
  REQUIRE(wrong_type.error().detail == "packer_home_flavor");
}

TEST_CASE("classify_absolute covers every grammar branch") {
  using biv::manifest::PathFlavor;
  const auto classify = biv::manifest::classify_absolute;
  REQUIRE(classify("/home/user") == PathFlavor::posix);
  REQUIRE(classify("/mnt/c/Users/x") == PathFlavor::wsl);
  REQUIRE(classify("/mnt/C/Users/x") == PathFlavor::wsl);
  REQUIRE(classify("/mnt/cc/x") == PathFlavor::posix);
  REQUIRE(classify("C:/Users/x") == PathFlavor::windows);
  REQUIRE(classify("C:\\Users\\x") == PathFlavor::windows);
  REQUIRE(classify("\\\\?\\C:\\Users\\x") == PathFlavor::windows);
  REQUIRE(classify("//?/C:/Users/x") == PathFlavor::windows);
  REQUIRE(classify("") == std::nullopt);
  REQUIRE(classify("relative/home") == std::nullopt);
  REQUIRE(classify("mnt/c/x") == std::nullopt);
  REQUIRE(classify("C:") == std::nullopt);
  REQUIRE(classify("C:x") == std::nullopt);
  REQUIRE(classify("/mnt/c") == PathFlavor::posix);
  REQUIRE(classify("/mnt/1/x") == PathFlavor::posix);
  REQUIRE(classify("1:/x") == std::nullopt);
}

TEST_CASE("classify_absolute agrees with the adapter spelling classifier") {
  for (const auto spelling : std::array{
           "/home/user", "/mnt/c/Users/x", "/mnt/C/Users/x", "/mnt/cc/x",
           "C:/Users/x", "C:\\Users\\x", "\\\\?\\C:\\Users\\x", "//?/C:/Users/x",
       }) {
    CAPTURE(spelling);
    REQUIRE(biv::manifest::classify_absolute(spelling) ==
            biv::adapters::rewrite::path_flavor_for(spelling));
  }
}

TEST_CASE("Manifest serializes in the locked field order") {
  const auto json = biv::manifest::serialize(fixed_manifest());
  REQUIRE(json ==
          "{\n"
          "  \"format_version\": 1,\n"
          "  \"required_capabilities\": [],\n"
          "  \"image_id\": \"00000000-0000-4000-8000-000000000000\",\n"
          "  \"app_version\": \"0.1.0\",\n"
          "  \"created_at\": \"2026-07-05T00:00:00Z\",\n"
          "  \"source_path\": \"/mnt/c/tmp/plain\",\n"
          "  \"source_path_flavor\": \"wsl\",\n"
          "  \"bivignore\": {\n"
          "    \"source\": \"builtin\",\n"
          "    \"builtin_id\": \"builtin-v1\",\n"
          "    \"sha256\": \"abc123\"\n"
          "  },\n"
          "  \"repos\": [],\n"
          "  \"agent_sessions\": []\n"
          "}\n");
  REQUIRE(json.find("agent_memory") == std::string::npos);
}

TEST_CASE("Manifest serializes agent_sessions entries per seam lock") {
  auto manifest = fixed_manifest();
  const auto entry = codex_session_entry();
  manifest.agent_sessions.push_back(entry);

  const auto json = biv::manifest::serialize(manifest);

  CHECK(json.find("\"agent\": \"codex\"") != std::string::npos);
  CHECK(json.find("\"normalization_scheme\": \"codex-cwd/v1\"") != std::string::npos);
  CHECK(json.find("\"parent\":") == std::string::npos);
  CHECK(json.find("\"parent_in_image\"") == std::string::npos);
  CHECK(json.find("\"entry_schema\": 1") != std::string::npos);
}

TEST_CASE("Manifest parse round-trips serialized manifests") {
  const auto bytes = bytes_of(biv::manifest::serialize(fixed_manifest()));
  const auto parsed = biv::manifest::parse(bytes);

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->format_version == 1);
  REQUIRE(parsed->required_capabilities.empty());
  REQUIRE(parsed->image_id == fixed_manifest().image_id);
  REQUIRE(parsed->source_path_flavor == biv::manifest::PathFlavor::wsl);
  REQUIRE(parsed->bivignore.source == "builtin");
  REQUIRE(parsed->bivignore.builtin_id == "builtin-v1");
  REQUIRE(parsed->bivignore.sha256_hex == "abc123");
}

TEST_CASE("Manifest parser ignores unknown fields") {
  const std::string text =
      "{"
      "\"format_version\":1,"
      "\"required_capabilities\":[],"
      "\"image_id\":\"id\","
      "\"app_version\":\"0.1.0\","
      "\"created_at\":\"2026-07-05T00:00:00Z\","
      "\"source_path\":\"/tmp/plain\","
      "\"source_path_flavor\":\"posix\","
      "\"bivignore\":{\"source\":\"file\",\"builtin_id\":null,\"sha256\":\"def\"},"
      "\"repos\":[],\"agent_sessions\":[],"
      "\"extra\":{\"nested\":true}"
      "}";
  const auto parsed = biv::manifest::parse(bytes_of(text));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->source_path_flavor == biv::manifest::PathFlavor::posix);
  REQUIRE_FALSE(parsed->bivignore.builtin_id.has_value());
}

TEST_CASE("Manifest parser reports future format_version without caller gating") {
  auto manifest = fixed_manifest();
  manifest.format_version = 2;
  const auto parsed = biv::manifest::parse(bytes_of(biv::manifest::serialize(manifest)));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->format_version == 2);
}

TEST_CASE("Manifest parser refuses malformed or step-incompatible inputs") {
  const std::vector<std::byte> empty;
  REQUIRE_FALSE(biv::manifest::parse(empty).has_value());
  REQUIRE_FALSE(biv::manifest::parse(bytes_of("not-json")).has_value());

  std::vector<std::byte> too_large((17U << 20), std::byte{' '});
  REQUIRE_FALSE(biv::manifest::parse(too_large).has_value());

  REQUIRE_FALSE(biv::manifest::parse(bytes_of("{\"required_capabilities\":[]}")).has_value());
  REQUIRE_FALSE(biv::manifest::parse(bytes_of("{\"format_version\":\"1\"}")).has_value());
  REQUIRE_FALSE(biv::manifest::parse(bytes_of("{\"format_version\":4294967297}")).has_value());

  std::string bad_caps = biv::manifest::serialize(fixed_manifest());
  bad_caps.replace(bad_caps.find("\"required_capabilities\": []"), 27, "\"required_capabilities\": {}");
  REQUIRE_FALSE(biv::manifest::parse(bytes_of(bad_caps)).has_value());

  std::string bad_flavor = biv::manifest::serialize(fixed_manifest());
  bad_flavor.replace(bad_flavor.find("\"source_path_flavor\": \"wsl\""), 27, "\"source_path_flavor\": \"beos\"");
  REQUIRE_FALSE(biv::manifest::parse(bytes_of(bad_flavor)).has_value());

  std::string repos = biv::manifest::serialize(fixed_manifest());
  repos.replace(repos.find("\"repos\": []"), 11, "\"repos\": [1]");
  const auto repo_result = biv::manifest::parse(bytes_of(repos));
  REQUIRE_FALSE(repo_result.has_value());
  REQUIRE(repo_result.error().detail == "step2-plain-dir-only");
}

TEST_CASE("Manifest parser accepts agent_sessions entries per seam lock") {
  const auto entry = codex_session_entry();
  const auto parsed = biv::manifest::parse(bytes_of(manifest_json_with({entry})));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->agent_sessions.size() == 1);
  const auto& actual = parsed->agent_sessions.front();
  CHECK(actual.agent == entry.agent);
  CHECK(actual.agent_version_at_pack == entry.agent_version_at_pack);
  CHECK(actual.relpath_key == entry.relpath_key);
  CHECK(actual.original_path == entry.original_path);
  CHECK(actual.normalized_path_key == entry.normalized_path_key);
  CHECK(actual.normalization_scheme == entry.normalization_scheme);
  CHECK(actual.path_flavor == entry.path_flavor);
  CHECK(actual.provenance.store_root == entry.provenance.store_root);
  CHECK(actual.provenance.locator == entry.provenance.locator);
  CHECK(actual.provenance.discovery_tier == entry.provenance.discovery_tier);
  CHECK(actual.provenance.archived == entry.provenance.archived);
  CHECK(actual.original_session_ids.primary == entry.original_session_ids.primary);
  CHECK(actual.original_session_ids.parent == std::nullopt);
  CHECK(actual.original_session_ids.parent_in_image == std::nullopt);
  REQUIRE(actual.children.size() == 1);
  CHECK(actual.children.front().original_id == "019f-bbbb");
  CHECK(actual.children.front().artifacts == std::vector<std::string>{"agents/codex/019f-bbbb.jsonl"});
  CHECK(actual.artifacts == std::vector<std::string>{"agents/codex/019f-aaaa.jsonl"});
  CHECK(actual.live_at_pack == entry.live_at_pack);
  CHECK(actual.imported_at == entry.imported_at);
  CHECK(actual.entry_schema == entry.entry_schema);
}

TEST_CASE("Manifest parser accepts forward-compatible agent_sessions shapes") {
  auto unknown_agent = codex_session_entry();
  unknown_agent.agent = "future-tool";
  unknown_agent.artifacts = {"agents/future-tool/x.jsonl"};
  unknown_agent.children = {};
  auto parsed_unknown = biv::manifest::parse(bytes_of(manifest_json_with({unknown_agent})));
  REQUIRE(parsed_unknown.has_value());
  REQUIRE(parsed_unknown->agent_sessions.size() == 1);
  CHECK(parsed_unknown->agent_sessions.front().agent == "future-tool");

  auto future_schema = codex_session_entry();
  future_schema.entry_schema = 99;
  auto parsed_future_schema = biv::manifest::parse(bytes_of(manifest_json_with({future_schema})));
  REQUIRE(parsed_future_schema.has_value());
  REQUIRE(parsed_future_schema->agent_sessions.size() == 1);
  CHECK(parsed_future_schema->agent_sessions.front().entry_schema == 99);

  std::string entry_unknown_field = manifest_json_with({codex_session_entry()});
  entry_unknown_field.replace(entry_unknown_field.find("\"entry_schema\": 1"), 17,
                              "\"unknown_entry_field\": {\"x\": true},\n"
                              "      \"entry_schema\": 1");
  auto parsed_entry_unknown = biv::manifest::parse(bytes_of(entry_unknown_field));
  REQUIRE(parsed_entry_unknown.has_value());
  REQUIRE(parsed_entry_unknown->agent_sessions.size() == 1);

  std::string top_unknown_field = manifest_json_with({codex_session_entry()});
  top_unknown_field.replace(top_unknown_field.rfind("}\n"), 2,
                            ",\n"
                            "  \"agent_memory\": []\n"
                            "}\n");
  auto parsed_top_unknown = biv::manifest::parse(bytes_of(top_unknown_field));
  REQUIRE(parsed_top_unknown.has_value());
  REQUIRE(parsed_top_unknown->agent_sessions.size() == 1);

  std::string minimal_future = manifest_json_with({codex_session_entry()});
  const auto entry_begin = minimal_future.find("{", minimal_future.find("\"agent_sessions\""));
  const auto entry_end = minimal_future.find("\n  ]", entry_begin);
  REQUIRE(entry_begin != std::string::npos);
  REQUIRE(entry_end != std::string::npos);
  minimal_future.replace(entry_begin, entry_end - entry_begin,
                         "{\"agent\":\"future-tool\",\"entry_schema\":99}");
  auto parsed_minimal_future = biv::manifest::parse(bytes_of(minimal_future));
  REQUIRE(parsed_minimal_future.has_value());
  REQUIRE(parsed_minimal_future->agent_sessions.size() == 1);
  CHECK(parsed_minimal_future->agent_sessions.front().entry_schema == 99);
}

TEST_CASE("Manifest parser accepts null parents and rejects empty parent artifacts") {
  std::string explicit_null = manifest_json_with({codex_session_entry()});
  const auto primary_end = explicit_null.find("\n", explicit_null.find("\"primary\""));
  REQUIRE(primary_end != std::string::npos);
  explicit_null.insert(primary_end, ",\n        \"parent\": null");
  const auto parsed_null = biv::manifest::parse(bytes_of(explicit_null));
  REQUIRE(parsed_null.has_value());
  REQUIRE(parsed_null->agent_sessions.size() == 1);
  CHECK_FALSE(parsed_null->agent_sessions.front().original_session_ids.parent.has_value());

  auto empty_artifacts = codex_session_entry();
  empty_artifacts.artifacts.clear();
  const auto empty_result =
      biv::manifest::parse(bytes_of(manifest_json_with({empty_artifacts})));
  REQUIRE_FALSE(empty_result.has_value());
  CHECK(empty_result.error().detail == "artifacts-empty");
}

TEST_CASE("Manifest parser rejects mechanically invalid agent_sessions entries") {
  auto invalid_agent = codex_session_entry();
  invalid_agent.agent = "../evil";
  invalid_agent.artifacts = {"agents/../evil/x.jsonl"};
  auto agent_result = biv::manifest::parse(bytes_of(manifest_json_with({invalid_agent})));
  REQUIRE_FALSE(agent_result.has_value());
  CHECK(agent_result.error().detail == "agent-id-grammar");

  for (const auto& path :
       std::vector<std::string>{"agents/other/x", "agents/codex/../../x", "/abs/x", "C:\\x", "agents\\codex\\x",
                                "agents/codex/C:/rollout.jsonl",
                                std::string{"agents/codex/bad"} + '\x01' + ".jsonl",
                                std::string{"agents/codex/bad"} + '\x7f' + ".jsonl"}) {
    auto invalid_path = codex_session_entry();
    invalid_path.artifacts = {path};
    invalid_path.children = {};
    auto path_result = biv::manifest::parse(bytes_of(manifest_json_with({invalid_path})));
    REQUIRE_FALSE(path_result.has_value());
    CHECK(path_result.error().detail == "artifact-prefix");
  }

  auto duplicate_a = codex_session_entry();
  auto duplicate_b = codex_session_entry();
  duplicate_b.artifacts = {"agents/codex/dupe.jsonl"};
  auto duplicate_result = biv::manifest::parse(bytes_of(manifest_json_with({duplicate_a, duplicate_b})));
  REQUIRE_FALSE(duplicate_result.has_value());
  CHECK(duplicate_result.error().detail == "session-uniqueness");

  auto parent_true = codex_session_entry();
  parent_true.original_session_ids.parent_in_image = true;
  auto parent_result = biv::manifest::parse(bytes_of(manifest_json_with({parent_true})));
  REQUIRE_FALSE(parent_result.has_value());
  CHECK(parent_result.error().detail == "session-ids");

  auto dangling_without_marker = codex_session_entry();
  dangling_without_marker.original_session_ids.parent = "missing-parent";
  auto dangling_result = biv::manifest::parse(
      bytes_of(manifest_json_with({dangling_without_marker})));
  REQUIRE_FALSE(dangling_result.has_value());
  CHECK(dangling_result.error().detail == "session-parent-relationship");

  auto parent = codex_session_entry();
  auto child = codex_session_entry();
  child.original_session_ids.primary = "child";
  child.original_session_ids.parent = parent.original_session_ids.primary;
  child.original_session_ids.parent_in_image = false;
  child.artifacts = {"agents/codex/child.jsonl"};
  child.children.clear();
  auto in_image_marker =
      biv::manifest::parse(bytes_of(manifest_json_with({parent, child})));
  REQUIRE_FALSE(in_image_marker.has_value());
  CHECK(in_image_marker.error().detail == "session-parent-relationship");

  auto empty_primary = codex_session_entry();
  empty_primary.original_session_ids.primary.clear();
  auto empty_primary_result =
      biv::manifest::parse(bytes_of(manifest_json_with({empty_primary})));
  REQUIRE_FALSE(empty_primary_result.has_value());
  CHECK(empty_primary_result.error().detail == "session-ids");

  auto duplicate_member_a = codex_session_entry();
  auto duplicate_member_b = codex_session_entry();
  duplicate_member_b.original_session_ids.primary = "different-primary";
  duplicate_member_b.children.clear();
  auto duplicate_member_result = biv::manifest::parse(
      bytes_of(manifest_json_with({duplicate_member_a, duplicate_member_b})));
  REQUIRE_FALSE(duplicate_member_result.has_value());
  CHECK(duplicate_member_result.error().detail == "artifact-uniqueness");
}
