#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

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

}  // namespace

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
