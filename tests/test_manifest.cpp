#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

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

std::string must_serialize(const biv::manifest::Manifest &manifest) {
  const auto serialized = biv::manifest::serialize(manifest);
  REQUIRE(serialized.has_value());
  return *serialized;
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
  return must_serialize(manifest);
}

std::string manifest_json_with_parent_edge(const int entry_schema) {
  auto entry = codex_session_entry();
  entry.children.push_back(
      {.original_id = "019f-cccc",
       .artifacts = {"agents/codex/019f-cccc.jsonl"}});
  auto json = manifest_json_with({entry});

  constexpr std::string_view child_id = "\"original_id\": \"019f-cccc\",";
  const auto child_id_pos = json.find(child_id);
  REQUIRE(child_id_pos != std::string::npos);
  json.insert(child_id_pos + child_id.size(),
              "\n        \"parent_id\": \"019f-bbbb\",");

  constexpr std::string_view schema_one = "\"entry_schema\": 1";
  const auto schema_pos = json.find(schema_one);
  REQUIRE(schema_pos != std::string::npos);
  json.replace(schema_pos, schema_one.size(),
               "\"entry_schema\": " + std::to_string(entry_schema));
  return json;
}

std::string replace_once(std::string text, const std::string_view needle,
                         std::string replacement) {
  const auto pos = text.find(needle);
  REQUIRE(pos != std::string::npos);
  text.replace(pos, needle.size(), std::move(replacement));
  return text;
}

std::string replace_last_once(std::string text, const std::string_view needle,
                              std::string replacement) {
  const auto pos = text.rfind(needle);
  REQUIRE(pos != std::string::npos);
  text.replace(pos, needle.size(), std::move(replacement));
  return text;
}

std::string as_stub(std::string text) {
  return replace_once(
      std::move(text), "\"entry_schema\": 1",
      "\"entry_schema\": " +
          std::to_string(biv::manifest::kEntrySchemaParseCeiling + 1));
}

std::string all_as_stubs(std::string text) {
  const std::string replacement =
      "\"entry_schema\": " +
      std::to_string(biv::manifest::kEntrySchemaParseCeiling + 1);
  std::size_t cursor = 0U;
  while (true) {
    const auto pos = text.find("\"entry_schema\": 1", cursor);
    if (pos == std::string::npos) {
      return text;
    }
    text.replace(pos, sizeof("\"entry_schema\": 1") - 1U, replacement);
    cursor = pos + replacement.size();
  }
}

std::string child_id(const std::size_t index) {
  return "child-" + std::to_string(index);
}

std::string child_artifact(const std::size_t child_index,
                           const std::size_t artifact_index) {
  return "agents/codex/child-" + std::to_string(child_index) + "-artifact-" +
         std::to_string(artifact_index) + ".jsonl";
}

biv::manifest::AgentSessionEntry entry_with_children(const std::size_t count) {
  auto entry = codex_session_entry();
  entry.children.clear();
  for (std::size_t i = 0; i < count; ++i) {
    entry.children.push_back({.original_id = child_id(i),
                              .artifacts = {child_artifact(i, 0)}});
  }
  return entry;
}

std::string manifest_json_with_parent_chain(const std::size_t depth) {
  auto entry = entry_with_children(depth);
  auto json = manifest_json_with({entry});
  for (std::size_t i = 1; i < depth; ++i) {
    const std::string needle = "\"original_id\": \"" + child_id(i) + "\",";
    const auto pos = json.find(needle);
    REQUIRE(pos != std::string::npos);
    json.insert(pos + needle.size(),
                "\n        \"parent_id\": \"" + child_id(i - 1) + "\",");
  }
  return replace_once(std::move(json), "\"entry_schema\": 1",
                      "\"entry_schema\": 2");
}

biv::manifest::AgentSessionEntry entry_with_total_artifacts(
    const std::size_t total) {
  auto entry = codex_session_entry();
  entry.children.clear();
  std::size_t remaining = total - entry.artifacts.size();
  for (std::size_t child_index = 0; remaining > 0; ++child_index) {
    const auto child_count = std::min<std::size_t>(remaining, 256U);
    std::vector<std::string> artifacts;
    artifacts.reserve(child_count);
    for (std::size_t artifact_index = 0; artifact_index < child_count;
         ++artifact_index) {
      artifacts.push_back(child_artifact(child_index, artifact_index));
    }
    entry.children.push_back({.original_id = child_id(child_index),
                              .artifacts = std::move(artifacts)});
    remaining -= child_count;
  }
  return entry;
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

std::string manifest_json_with_repo_rows(const std::string_view rows) {
  auto json = must_serialize(fixed_manifest());
  constexpr std::string_view empty_repos = "\"repos\": []";
  const auto pos = json.find(empty_repos);
  REQUIRE(pos != std::string::npos);
  json.replace(pos, empty_repos.size(),
               "\"repos\": [" + std::string{rows} + "]");
  return json;
}

std::string valid_shallow_repo_json() {
  return R"({
    "id":"shallow-row",
    "relpath":"vendor/shallow",
    "kind":"repo",
    "parent_id":null,
    "remote":"https://shallow.example/repo.git",
    "remotes":[{"name":"origin","url":"https://origin.example/shallow.git"}],
    "sha":"6666666666666666666666666666666666666666",
    "branch":null,
    "head_state":"detached",
    "dirty":false,
    "local_refs":[],
    "capture":{"staged_patch":null,"worktree_patch":null,"payload_prefix":"payload/shallow/","forced_payload":[],"capture_env":{"core_autocrlf":null,"core_filemode":null,"sparse":false}},
    "bundle":null,
    "sparse":null,
    "notes":[],
    "shallow":{"boundary":["7777777777777777777777777777777777777777"]}
  })";
}

std::string valid_payload_only_unborn_repo_json() {
  return R"({
    "id":"empty-unborn",
    "relpath":"empty-unborn",
    "kind":"repo",
    "parent_id":null,
    "remote":null,
    "remotes":[],
    "sha":null,
    "branch":"new-main",
    "head_state":"unborn",
    "dirty":false,
    "local_refs":[],
    "capture":{"staged_patch":null,"worktree_patch":null,"payload_prefix":"payload/empty-unborn/","forced_payload":[],"capture_env":{"core_autocrlf":null,"core_filemode":null,"sparse":false}},
    "bundle":null,
    "sparse":null,
    "notes":[]
  })";
}

std::string valid_born_overlay_repo_json() {
  return R"({
    "id":"born-row",
    "relpath":"born",
    "kind":"repo",
    "parent_id":null,
    "remote":"https://born.example/repo.git",
    "remotes":[{"name":"origin","url":"https://born.example/repo.git"}],
    "sha":"8888888888888888888888888888888888888888",
    "branch":"main",
    "head_state":"branch",
    "dirty":false,
    "capture_mode":"overlay",
    "eligibility":{"method":"ls-remote-ancestry","result":"proven","checked_at":"2026-08-30T01:02:03Z","proof":{"remote":"origin","url":"https://born.example/repo.git","ref":"refs/heads/main","tip_sha":"9999999999999999999999999999999999999999"}},
    "local_refs":[{"ref":"refs/heads/main","sha":"8888888888888888888888888888888888888888","availability":"remote-proven","proof":{"remote":"origin","url":"https://born.example/repo.git","ref":"refs/heads/main","tip_sha":"9999999999999999999999999999999999999999"}}],
    "capture":{"staged_patch":null,"worktree_patch":null,"payload_prefix":"payload/born/","forced_payload":[],"capture_env":{"core_autocrlf":null,"core_filemode":null,"sparse":false}},
    "bundle":null,
    "sparse":null,
    "notes":[]
  })";
}

std::set<std::string> member_names(const simdjson::dom::object object) {
  std::set<std::string> names;
  for (const auto field : object) {
    names.emplace(field.key);
  }
  return names;
}

void require_proof_equal(const std::optional<biv::repo::Proof> &actual,
                         const std::optional<biv::repo::Proof> &expected) {
  REQUIRE(actual.has_value() == expected.has_value());
  if (!expected) {
    return;
  }
  CHECK(actual->remote == expected->remote);
  CHECK(actual->url == expected->url);
  CHECK(actual->ref == expected->ref);
  CHECK(actual->tip_sha == expected->tip_sha);
}

struct ProjectedRow {
  std::vector<std::string> values;
  std::optional<biv::repo::CaptureMode> contextual_capture_mode;

  bool operator==(const ProjectedRow &) const = default;
};

ProjectedRow project_row(const biv::repo::RepoEntry &entry) {
  const bool emits_capture_mode =
      !entry.shallow &&
      !(entry.head_state == biv::repo::HeadState::unborn && !entry.bundle &&
        !entry.eligibility && entry.local_refs.empty());
  std::vector<std::string> values;
  const auto append = [&](const auto &value) { values.push_back(value); };
  const auto append_optional = [&](const auto &value) {
    append(value ? "1" : "0");
    if (value)
      append(*value);
  };
  const auto append_proof = [&](const auto &proof) {
    append(proof ? "1" : "0");
    if (proof) {
      append(proof->remote);
      append(proof->url);
      append(proof->ref);
      append(proof->tip_sha);
    }
  };
  append(entry.id);
  append(entry.relpath.generic_string());
  append(std::to_string(static_cast<int>(entry.kind)));
  append_optional(entry.parent_id);
  append_optional(entry.remote);
  for (const auto &remote : entry.remotes) {
    append(remote.name);
    append(remote.url);
  }
  append(std::to_string(entry.remotes.size()));
  append_optional(entry.sha);
  append_optional(entry.branch);
  append(std::to_string(static_cast<int>(entry.head_state)));
  append(entry.dirty ? "1" : "0");
  append(entry.eligibility ? "1" : "0");
  if (entry.eligibility) {
    append(entry.eligibility->method);
    append(std::to_string(static_cast<int>(entry.eligibility->result)));
    append(entry.eligibility->checked_at);
    append_proof(entry.eligibility->proof);
  }
  append(std::to_string(entry.local_refs.size()));
  for (const auto &ref : entry.local_refs) {
    append(ref.ref);
    append(ref.sha);
    append(std::to_string(static_cast<int>(ref.availability)));
    append_proof(ref.proof);
  }
  append(entry.local_refs_bundle ? "1" : "0");
  if (entry.local_refs_bundle)
    append(entry.local_refs_bundle->generic_string());
  append(entry.capture.staged_patch ? "1" : "0");
  if (entry.capture.staged_patch)
    append(entry.capture.staged_patch->generic_string());
  append(entry.capture.worktree_patch ? "1" : "0");
  if (entry.capture.worktree_patch)
    append(entry.capture.worktree_patch->generic_string());
  append(entry.capture.payload_prefix);
  append(std::to_string(entry.capture.forced_payload.size()));
  for (const auto &forced : entry.capture.forced_payload) {
    append(forced.path.generic_string());
    append(std::to_string(static_cast<int>(forced.reason)));
  }
  append_optional(entry.capture.capture_env.core_autocrlf);
  append(entry.capture.capture_env.core_filemode
             ? (*entry.capture.capture_env.core_filemode ? "1" : "0")
             : "null");
  append(entry.capture.capture_env.sparse ? "1" : "0");
  append(entry.bundle ? "1" : "0");
  if (entry.bundle)
    append(entry.bundle->generic_string());
  append(entry.shallow ? "1" : "0");
  if (entry.shallow) {
    append(std::to_string(entry.shallow->boundary.size()));
    for (const auto &boundary : entry.shallow->boundary)
      append(boundary);
  }
  append(entry.sparse == nullptr ? "null" : "present");
  append(std::to_string(entry.notes.size()));
  for (const auto &note : entry.notes) {
    append(std::to_string(note.index()));
    if (const auto *refs = std::get_if<biv::repo::NonCarriedRefsNote>(&note)) {
      append(std::to_string(refs->refs_p1.size()));
      for (const auto &ref : refs->refs_p1)
        append(ref);
      append(refs->omitted_count ? "1" : "0");
      if (refs->omitted_count)
        append(std::to_string(*refs->omitted_count));
    } else if (const auto *unknown =
                   std::get_if<biv::repo::UnknownNote>(&note)) {
      append(unknown->kind);
      append(unknown->verbatim_json);
    }
  }
  return ProjectedRow{.values = std::move(values),
                      .contextual_capture_mode =
                          emits_capture_mode ? std::optional{entry.capture_mode}
                                             : std::nullopt};
}

void require_repo_projection_equal(const biv::repo::RepoEntry &actual_entry,
                                   const biv::repo::RepoEntry &expected_entry) {
  const auto actual_projection = project_row(actual_entry);
  const auto expected_projection = project_row(expected_entry);
  CHECK(actual_projection == expected_projection);
  const auto &actual = actual_entry;
  const auto &expected = expected_entry;
  CHECK(actual.id == expected.id);
  CHECK(actual.relpath == expected.relpath);
  CHECK(actual.kind == expected.kind);
  CHECK(actual.parent_id == expected.parent_id);
  CHECK(actual.remote == expected.remote);
  REQUIRE(actual.remotes.size() == expected.remotes.size());
  for (std::size_t i = 0; i < expected.remotes.size(); ++i) {
    CHECK(actual.remotes.at(i).name == expected.remotes.at(i).name);
    CHECK(actual.remotes.at(i).url == expected.remotes.at(i).url);
  }
  CHECK(actual.sha == expected.sha);
  CHECK(actual.branch == expected.branch);
  CHECK(actual.head_state == expected.head_state);
  CHECK(actual.dirty == expected.dirty);
  const bool capture_mode_projected =
      !expected.shallow &&
      !(expected.head_state == biv::repo::HeadState::unborn &&
        !expected.bundle && !expected.eligibility && expected.local_refs.empty());
  if (capture_mode_projected) {
    CHECK(actual.capture_mode == expected.capture_mode);
  }
  REQUIRE(actual.eligibility.has_value() == expected.eligibility.has_value());
  if (expected.eligibility) {
    CHECK(actual.eligibility->method == expected.eligibility->method);
    CHECK(actual.eligibility->result == expected.eligibility->result);
    CHECK(actual.eligibility->checked_at == expected.eligibility->checked_at);
    require_proof_equal(actual.eligibility->proof, expected.eligibility->proof);
  }
  REQUIRE(actual.local_refs.size() == expected.local_refs.size());
  for (std::size_t i = 0; i < expected.local_refs.size(); ++i) {
    CHECK(actual.local_refs.at(i).ref == expected.local_refs.at(i).ref);
    CHECK(actual.local_refs.at(i).sha == expected.local_refs.at(i).sha);
    CHECK(actual.local_refs.at(i).availability ==
          expected.local_refs.at(i).availability);
    require_proof_equal(actual.local_refs.at(i).proof,
                        expected.local_refs.at(i).proof);
  }
  CHECK(actual.local_refs_bundle == expected.local_refs_bundle);
  CHECK(actual.capture.staged_patch == expected.capture.staged_patch);
  CHECK(actual.capture.worktree_patch == expected.capture.worktree_patch);
  CHECK(actual.capture.payload_prefix == expected.capture.payload_prefix);
  REQUIRE(actual.capture.forced_payload.size() ==
          expected.capture.forced_payload.size());
  for (std::size_t i = 0; i < expected.capture.forced_payload.size(); ++i) {
    CHECK(actual.capture.forced_payload.at(i).path ==
          expected.capture.forced_payload.at(i).path);
    CHECK(actual.capture.forced_payload.at(i).reason ==
          expected.capture.forced_payload.at(i).reason);
  }
  CHECK(actual.capture.capture_env.core_autocrlf ==
        expected.capture.capture_env.core_autocrlf);
  CHECK(actual.capture.capture_env.core_filemode ==
        expected.capture.capture_env.core_filemode);
  CHECK(actual.capture.capture_env.sparse ==
        expected.capture.capture_env.sparse);
  CHECK(actual.bundle == expected.bundle);
  REQUIRE(actual.shallow.has_value() == expected.shallow.has_value());
  if (expected.shallow) {
    CHECK(actual.shallow->boundary == expected.shallow->boundary);
  }
  CHECK(actual.sparse == nullptr);
  REQUIRE(actual.notes.size() == expected.notes.size());
  for (std::size_t i = 0; i < expected.notes.size(); ++i) {
    REQUIRE(actual.notes.at(i).index() == expected.notes.at(i).index());
    if (const auto *expected_refs =
            std::get_if<biv::repo::NonCarriedRefsNote>(&expected.notes.at(i))) {
      const auto *actual_refs =
          std::get_if<biv::repo::NonCarriedRefsNote>(&actual.notes.at(i));
      REQUIRE(actual_refs != nullptr);
      CHECK(actual_refs->refs_p1 == expected_refs->refs_p1);
      CHECK(actual_refs->omitted_count == expected_refs->omitted_count);
    } else if (const auto *expected_unknown =
                   std::get_if<biv::repo::UnknownNote>(&expected.notes.at(i))) {
      const auto *actual_unknown =
          std::get_if<biv::repo::UnknownNote>(&actual.notes.at(i));
      REQUIRE(actual_unknown != nullptr);
      CHECK(actual_unknown->kind == expected_unknown->kind);
      CHECK(actual_unknown->verbatim_json == expected_unknown->verbatim_json);
    }
  }
}

void require_repo_parse_error(const std::string &row,
                              const std::string_view detail) {
  const auto parsed =
      biv::manifest::parse(bytes_of(manifest_json_with_repo_rows(row)));
  REQUIRE_FALSE(parsed.has_value());
  CHECK(parsed.error().kind == biv::ErrKind::ParseError);
  CHECK(parsed.error().detail == detail);
}

biv::repo::RepoEntry repo_entry_from_json(const std::string &row) {
  const auto parsed = biv::manifest::parse(
      bytes_of(manifest_json_with_repo_rows(row)));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 1U);
  return parsed->repos.front();
}

biv::repo::RepoEntry valid_born_repo_entry() {
  return repo_entry_from_json(valid_born_overlay_repo_json());
}

biv::repo::RepoEntry valid_shallow_repo_entry() {
  return repo_entry_from_json(valid_shallow_repo_json());
}

biv::repo::RepoEntry valid_g_unborn_repo_entry() {
  biv::repo::RepoEntry entry;
  entry.id = "unborn-with-refs";
  entry.relpath = "unborn";
  entry.kind = biv::repo::RepoKind::nested;
  entry.parent_id = "repo-root";
  entry.remote = "https://unborn.example/repo.git";
  entry.remotes = {
      {.name = "origin", .url = "https://unborn.example/repo.git"}};
  entry.sha = std::nullopt;
  entry.branch = "new-main";
  entry.head_state = biv::repo::HeadState::unborn;
  entry.capture_mode = biv::repo::CaptureMode::full;
  entry.eligibility = biv::repo::Eligibility{
      .method = "ls-remote-ancestry",
      .result = biv::repo::EligibilityResult::unborn_head,
      .checked_at = "2026-08-30T02:03:04Z",
      .proof = std::nullopt};
  entry.local_refs = {{
      .ref = "refs/heads/side",
      .sha = "1212121212121212121212121212121212121212",
      .availability = biv::repo::RefAvailability::repo_bundle_carried,
      .proof = std::nullopt,
  }};
  entry.capture.payload_prefix = "payload/unborn/";
  entry.bundle = "repos/unborn-with-refs/repo.bundle";
  return entry;
}

void require_repo_write_error(const biv::repo::RepoEntry &entry,
                              const std::string_view field,
                              const std::string_view clause) {
  auto manifest = fixed_manifest();
  manifest.repos = {entry};
  const auto serialized = biv::manifest::serialize(manifest);
  REQUIRE_FALSE(serialized.has_value());
  CHECK(serialized.error().kind == biv::ErrKind::InternalError);
  CHECK(serialized.error().detail ==
        entry.id + ":" + std::string{field} + ":" + std::string{clause});
}

}  // namespace

TEST_CASE("packer_home serializes after source_path_flavor and round-trips") {
  auto manifest = fixed_manifest();
  manifest.packer_home = biv::manifest::PackerHome{
      .path = "/Users/jack", .flavor = biv::manifest::PathFlavor::posix};

  const auto json = must_serialize(manifest);
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
        biv::manifest::parse(bytes_of(must_serialize(manifest)));
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
  const auto json = must_serialize(manifest);
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
    REQUIRE(must_serialize(manifest).find("packer_home") ==
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
  const auto json = must_serialize(fixed_manifest());
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

  const auto json = must_serialize(manifest);

  CHECK(json.find("\"agent\": \"codex\"") != std::string::npos);
  CHECK(json.find("\"normalization_scheme\": \"codex-cwd/v1\"") != std::string::npos);
  CHECK(json.find("\"parent\":") == std::string::npos);
  CHECK(json.find("\"parent_in_image\"") == std::string::npos);
  CHECK(json.find("\"entry_schema\": 1") != std::string::npos);
}

TEST_CASE("Manifest parse round-trips serialized manifests") {
  const auto bytes = bytes_of(must_serialize(fixed_manifest()));
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
  const auto parsed = biv::manifest::parse(bytes_of(must_serialize(manifest)));

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

  std::string bad_caps = must_serialize(fixed_manifest());
  bad_caps.replace(bad_caps.find("\"required_capabilities\": []"), 27, "\"required_capabilities\": {}");
  REQUIRE_FALSE(biv::manifest::parse(bytes_of(bad_caps)).has_value());

  std::string bad_flavor = must_serialize(fixed_manifest());
  bad_flavor.replace(bad_flavor.find("\"source_path_flavor\": \"wsl\""), 27, "\"source_path_flavor\": \"beos\"");
  REQUIRE_FALSE(biv::manifest::parse(bytes_of(bad_flavor)).has_value());

  std::string repos = must_serialize(fixed_manifest());
  repos.replace(repos.find("\"repos\": []"), 11, "\"repos\": [1]");
  const auto repo_result = biv::manifest::parse(bytes_of(repos));
  REQUIRE_FALSE(repo_result.has_value());
  REQUIRE(repo_result.error().kind == biv::ErrKind::ParseError);
  REQUIRE(repo_result.error().detail == "repos");
}

TEST_CASE("Manifest repos populated round-trip is symmetric and row-bound") {
  biv::repo::RepoEntry exemplar;
  exemplar.id = "repo-root";
  exemplar.relpath = ".";
  exemplar.kind = biv::repo::RepoKind::repo;
  exemplar.parent_id = std::nullopt;
  exemplar.remote = "https://primary.example/root.git";
  exemplar.remotes = {
      {.name = "origin", .url = "https://origin.example/root.git"},
      {.name = "backup", .url = "ssh://backup.example/root.git"}};
  exemplar.sha = "1111111111111111111111111111111111111111";
  exemplar.branch = "main";
  exemplar.head_state = biv::repo::HeadState::branch;
  exemplar.dirty = true;
  exemplar.capture_mode = biv::repo::CaptureMode::overlay;
  exemplar.eligibility = biv::repo::Eligibility{
      .method = "ls-remote-ancestry",
      .result = biv::repo::EligibilityResult::proven,
      .checked_at = "2026-08-30T01:02:03Z",
      .proof = biv::repo::Proof{
          .remote = "backup",
          .url = "ssh://backup.example/root.git",
          .ref = "refs/tags/proof-tip",
          .tip_sha = "2222222222222222222222222222222222222222"}};
  exemplar.local_refs = {
      {.ref = "refs/heads/remote-proven",
       .sha = "3333333333333333333333333333333333333333",
       .availability = biv::repo::RefAvailability::remote_proven,
       .proof =
           biv::repo::Proof{.remote = "origin",
                            .url = "https://origin.example/root.git",
                            .ref = "refs/heads/upstream-tip",
                            .tip_sha =
                                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}},
      {.ref = "refs/heads/bundle-carried",
       .sha = "4444444444444444444444444444444444444444",
       .availability = biv::repo::RefAvailability::bundle_carried,
       .proof = std::nullopt},
      {.ref = "refs/tags/repo-bundle-carried",
       .sha = "5555555555555555555555555555555555555555",
       .availability = biv::repo::RefAvailability::repo_bundle_carried,
       .proof = std::nullopt}};
  exemplar.local_refs_bundle = "repos/repo-root/local-refs.bundle";
  exemplar.capture.staged_patch = "repos/repo-root/staged.patch";
  exemplar.capture.worktree_patch = "repos/repo-root/worktree.patch";
  exemplar.capture.payload_prefix = "payload/root/";
  exemplar.capture.forced_payload = {
      {.path = "docs/eol.txt",
       .reason = biv::repo::ForcedPayloadReason::eol_conversion},
      {.path = "bin/tool",
       .reason = biv::repo::ForcedPayloadReason::filemode_unrepresentable}};
  exemplar.capture.capture_env = {
      .core_autocrlf = "input", .core_filemode = false, .sparse = true};
  exemplar.bundle = std::nullopt;
  exemplar.notes.emplace_back(biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/a", "refs/notes/b"}, .omitted_count = 7U});
  const std::string unknown_raw =
      R"({ "kind" : "future-note", "value" : 17, "nested" : [true, null, "v"] })";
  exemplar.notes.emplace_back(biv::repo::UnknownNote{
      .kind = "future-note", .verbatim_json = unknown_raw});

  biv::repo::RepoEntry shallow;
  shallow.id = "shallow-row";
  shallow.relpath = "vendor/shallow";
  shallow.kind = biv::repo::RepoKind::repo;
  shallow.parent_id = std::nullopt;
  shallow.remote = "https://shallow.example/repo.git";
  shallow.remotes = {
      {.name = "origin", .url = "https://origin.example/shallow.git"}};
  shallow.sha = "6666666666666666666666666666666666666666";
  shallow.branch = std::nullopt;
  shallow.head_state = biv::repo::HeadState::detached;
  shallow.capture.payload_prefix = "payload/shallow/";
  shallow.shallow = biv::repo::Shallow{
      .boundary = {"7777777777777777777777777777777777777777"}};

  auto manifest = fixed_manifest();
  manifest.repos = {exemplar, shallow};
  const auto json = must_serialize(manifest);
  const auto parsed = biv::manifest::parse(bytes_of(json));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 2U);
  require_repo_projection_equal(parsed->repos.at(0), exemplar);
  require_repo_projection_equal(parsed->repos.at(1), shallow);

  simdjson::dom::parser dom_parser;
  const simdjson::padded_string padded{json};
  const auto document = dom_parser.parse(padded);
  simdjson::dom::array repos;
  REQUIRE_FALSE(document["repos"].get(repos));
  REQUIRE(repos.size() == 2U);
  simdjson::dom::object first;
  simdjson::dom::object second;
  REQUIRE_FALSE(repos.at(0).get(first));
  REQUIRE_FALSE(repos.at(1).get(second));
  CHECK(member_names(first) ==
        std::set<std::string>{"id", "relpath", "kind", "parent_id", "remote",
                              "remotes", "sha", "branch", "head_state", "dirty",
                              "capture_mode", "eligibility", "local_refs",
                              "local_refs_bundle", "capture", "bundle",
                              "sparse", "notes"});
  // FX-N (a) NAMED MUTANT: a shallow writer emitting either mode member.
  CHECK(member_names(second) ==
        std::set<std::string>{"id", "relpath", "kind", "parent_id", "remote",
                              "remotes", "sha", "branch", "head_state", "dirty",
                              "local_refs", "capture", "bundle", "sparse",
                              "notes", "shallow"});
  simdjson::dom::object eligibility;
  simdjson::dom::object eligibility_proof;
  simdjson::dom::object capture;
  simdjson::dom::object capture_env;
  REQUIRE_FALSE(first.at_key("eligibility").get(eligibility));
  REQUIRE_FALSE(eligibility.at_key("proof").get(eligibility_proof));
  REQUIRE_FALSE(first.at_key("capture").get(capture));
  REQUIRE_FALSE(capture.at_key("capture_env").get(capture_env));
  CHECK(member_names(eligibility) ==
        std::set<std::string>{"method", "result", "checked_at", "proof"});
  CHECK(member_names(eligibility_proof) ==
        std::set<std::string>{"remote", "url", "ref", "tip_sha"});
  CHECK(member_names(capture) ==
        std::set<std::string>{"staged_patch", "worktree_patch",
                              "payload_prefix", "forced_payload",
                              "capture_env"});
  CHECK(member_names(capture_env) ==
        std::set<std::string>{"core_autocrlf", "core_filemode", "sparse"});

  simdjson::dom::array remotes;
  REQUIRE_FALSE(first.at_key("remotes").get(remotes));
  REQUIRE(remotes.size() == 2U);
  simdjson::dom::object origin_remote;
  simdjson::dom::object backup_remote;
  REQUIRE_FALSE(remotes.at(0).get(origin_remote));
  REQUIRE_FALSE(remotes.at(1).get(backup_remote));
  CHECK(member_names(origin_remote) == std::set<std::string>{"name", "url"});
  CHECK(member_names(backup_remote) == std::set<std::string>{"name", "url"});
  std::string_view text;
  REQUIRE_FALSE(origin_remote.at_key("name").get(text));
  CHECK(text == "origin");
  REQUIRE_FALSE(origin_remote.at_key("url").get(text));
  CHECK(text == "https://origin.example/root.git");
  REQUIRE_FALSE(backup_remote.at_key("name").get(text));
  CHECK(text == "backup");
  REQUIRE_FALSE(backup_remote.at_key("url").get(text));
  CHECK(text == "ssh://backup.example/root.git");

  simdjson::dom::array shallow_remotes;
  REQUIRE_FALSE(second.at_key("remotes").get(shallow_remotes));
  REQUIRE(shallow_remotes.size() == 1U);
  simdjson::dom::object shallow_origin_remote;
  REQUIRE_FALSE(shallow_remotes.at(0).get(shallow_origin_remote));
  CHECK(member_names(shallow_origin_remote) ==
        std::set<std::string>{"name", "url"});
  REQUIRE_FALSE(shallow_origin_remote.at_key("name").get(text));
  CHECK(text == "origin");
  REQUIRE_FALSE(shallow_origin_remote.at_key("url").get(text));
  CHECK(text == "https://origin.example/shallow.git");

  simdjson::dom::array local_refs;
  REQUIRE_FALSE(first.at_key("local_refs").get(local_refs));
  REQUIRE(local_refs.size() == 3U);
  for (const auto ref : local_refs) {
    simdjson::dom::object ref_object;
    REQUIRE_FALSE(ref.get(ref_object));
    CHECK(member_names(ref_object) ==
          std::set<std::string>{"ref", "sha", "availability", "proof"});
  }
  simdjson::dom::object remote_proven_ref;
  simdjson::dom::object bundle_carried_ref;
  simdjson::dom::object repo_bundle_carried_ref;
  REQUIRE_FALSE(local_refs.at(0).get(remote_proven_ref));
  REQUIRE_FALSE(local_refs.at(1).get(bundle_carried_ref));
  REQUIRE_FALSE(local_refs.at(2).get(repo_bundle_carried_ref));
  REQUIRE_FALSE(remote_proven_ref.at_key("ref").get(text));
  CHECK(text == "refs/heads/remote-proven");
  REQUIRE_FALSE(remote_proven_ref.at_key("sha").get(text));
  CHECK(text == "3333333333333333333333333333333333333333");
  REQUIRE_FALSE(remote_proven_ref.at_key("availability").get(text));
  CHECK(text == "remote-proven");
  simdjson::dom::object local_ref_proof;
  REQUIRE_FALSE(remote_proven_ref.at_key("proof").get(local_ref_proof));
  CHECK(member_names(local_ref_proof) ==
        std::set<std::string>{"remote", "url", "ref", "tip_sha"});
  REQUIRE_FALSE(local_ref_proof.at_key("remote").get(text));
  CHECK(text == "origin");
  REQUIRE_FALSE(local_ref_proof.at_key("url").get(text));
  CHECK(text == "https://origin.example/root.git");
  REQUIRE_FALSE(local_ref_proof.at_key("ref").get(text));
  CHECK(text == "refs/heads/upstream-tip");
  REQUIRE_FALSE(local_ref_proof.at_key("tip_sha").get(text));
  CHECK(text == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  REQUIRE_FALSE(bundle_carried_ref.at_key("ref").get(text));
  CHECK(text == "refs/heads/bundle-carried");
  REQUIRE_FALSE(bundle_carried_ref.at_key("sha").get(text));
  CHECK(text == "4444444444444444444444444444444444444444");
  REQUIRE_FALSE(bundle_carried_ref.at_key("availability").get(text));
  CHECK(text == "bundle-carried");
  simdjson::dom::element proof;
  REQUIRE_FALSE(bundle_carried_ref.at_key("proof").get(proof));
  CHECK(proof.is_null());
  REQUIRE_FALSE(repo_bundle_carried_ref.at_key("ref").get(text));
  CHECK(text == "refs/tags/repo-bundle-carried");
  REQUIRE_FALSE(repo_bundle_carried_ref.at_key("sha").get(text));
  CHECK(text == "5555555555555555555555555555555555555555");
  REQUIRE_FALSE(repo_bundle_carried_ref.at_key("availability").get(text));
  CHECK(text == "repo-bundle-carried");
  REQUIRE_FALSE(repo_bundle_carried_ref.at_key("proof").get(proof));
  CHECK(proof.is_null());

  simdjson::dom::array forced_payload;
  REQUIRE_FALSE(capture.at_key("forced_payload").get(forced_payload));
  REQUIRE(forced_payload.size() == 2U);
  for (const auto forced : forced_payload) {
    simdjson::dom::object forced_object;
    REQUIRE_FALSE(forced.get(forced_object));
    CHECK(member_names(forced_object) ==
          std::set<std::string>{"path", "reason"});
  }
  simdjson::dom::object eol_payload;
  simdjson::dom::object filemode_payload;
  REQUIRE_FALSE(forced_payload.at(0).get(eol_payload));
  REQUIRE_FALSE(forced_payload.at(1).get(filemode_payload));
  REQUIRE_FALSE(eol_payload.at_key("path").get(text));
  CHECK(text == "docs/eol.txt");
  REQUIRE_FALSE(eol_payload.at_key("reason").get(text));
  CHECK(text == "eol-conversion");
  REQUIRE_FALSE(filemode_payload.at_key("path").get(text));
  CHECK(text == "bin/tool");
  REQUIRE_FALSE(filemode_payload.at_key("reason").get(text));
  CHECK(text == "filemode-unrepresentable");

  simdjson::dom::array notes;
  REQUIRE_FALSE(first.at_key("notes").get(notes));
  REQUIRE(notes.size() == 2U);
  simdjson::dom::object non_carried_refs_note;
  simdjson::dom::object unknown_note;
  REQUIRE_FALSE(notes.at(0).get(non_carried_refs_note));
  REQUIRE_FALSE(notes.at(1).get(unknown_note));
  CHECK(member_names(non_carried_refs_note) ==
        std::set<std::string>{"kind", "refs", "omitted_count"});
  CHECK(member_names(unknown_note) ==
        std::set<std::string>{"kind", "value", "nested"});
  REQUIRE_FALSE(non_carried_refs_note.at_key("kind").get(text));
  CHECK(text == "non-carried-refs");
  simdjson::dom::array non_carried_refs;
  REQUIRE_FALSE(non_carried_refs_note.at_key("refs").get(non_carried_refs));
  REQUIRE(non_carried_refs.size() == 2U);
  REQUIRE_FALSE(non_carried_refs.at(0).get(text));
  CHECK(text == "refs/custom/a");
  REQUIRE_FALSE(non_carried_refs.at(1).get(text));
  CHECK(text == "refs/notes/b");
  std::uint64_t omitted_count = 0U;
  REQUIRE_FALSE(non_carried_refs_note.at_key("omitted_count").get(omitted_count));
  CHECK(omitted_count == 7U);
  REQUIRE_FALSE(unknown_note.at_key("kind").get(text));
  CHECK(text == "future-note");
  std::int64_t unknown_value = 0;
  REQUIRE_FALSE(unknown_note.at_key("value").get(unknown_value));
  CHECK(unknown_value == 17);
  simdjson::dom::array unknown_nested;
  REQUIRE_FALSE(unknown_note.at_key("nested").get(unknown_nested));
  REQUIRE(unknown_nested.size() == 3U);
  bool nested_true = false;
  REQUIRE_FALSE(unknown_nested.at(0).get(nested_true));
  CHECK(nested_true);
  simdjson::dom::element nested_null;
  REQUIRE_FALSE(unknown_nested.at(1).get(nested_null));
  CHECK(nested_null.is_null());
  REQUIRE_FALSE(unknown_nested.at(2).get(text));
  CHECK(text == "v");

  simdjson::dom::object shallow_object;
  REQUIRE_FALSE(second.at_key("shallow").get(shallow_object));
  CHECK(member_names(shallow_object) == std::set<std::string>{"boundary"});
  simdjson::dom::array boundary;
  REQUIRE_FALSE(shallow_object.at_key("boundary").get(boundary));
  REQUIRE(boundary.size() == 1U);
  REQUIRE_FALSE(boundary.at(0).get(text));
  CHECK(text == "7777777777777777777777777777777777777777");
}

TEST_CASE("Manifest repos G unborn-with-refs shape round-trips") {
  biv::repo::RepoEntry unborn;
  unborn.id = "unborn-with-refs";
  unborn.relpath = "unborn";
  unborn.kind = biv::repo::RepoKind::nested;
  unborn.parent_id = "repo-root";
  unborn.remote = "https://unborn.example/repo.git";
  unborn.remotes = {
      {.name = "origin", .url = "https://unborn.example/repo.git"}};
  unborn.sha = std::nullopt;
  unborn.branch = "new-main";
  unborn.head_state = biv::repo::HeadState::unborn;
  unborn.capture_mode = biv::repo::CaptureMode::full;
  unborn.eligibility = biv::repo::Eligibility{
      .method = "ls-remote-ancestry",
      .result = biv::repo::EligibilityResult::unborn_head,
      .checked_at = "2026-08-30T02:03:04Z",
      .proof = std::nullopt};
  unborn.local_refs = {
      {.ref = "refs/heads/side",
       .sha = "1212121212121212121212121212121212121212",
       .availability = biv::repo::RefAvailability::repo_bundle_carried,
       .proof = std::nullopt}};
  unborn.capture.payload_prefix = "payload/unborn/";
  unborn.bundle = "repos/unborn-with-refs/repo.bundle";

  auto manifest = fixed_manifest();
  manifest.repos = {unborn};
  const auto json = must_serialize(manifest);
  const auto parsed = biv::manifest::parse(bytes_of(json));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 1U);
  require_repo_projection_equal(parsed->repos.front(), unborn);
  CHECK(json.find("\"sha\": null") != std::string::npos);
  CHECK(json.find("\"head_state\": \"unborn\"") != std::string::npos);
  CHECK(json.find("\"result\": \"unborn-head\"") != std::string::npos);
}

TEST_CASE("Manifest repos never serialize transient engine state") {
  auto entry = biv::repo::RepoEntry{};
  entry.id = "transient-proof";
  entry.relpath = "transient-proof";
  entry.remote = "https://example.invalid/repo.git";
  entry.sha = "abababababababababababababababababababab";
  entry.branch = "main";
  entry.head_state = biv::repo::HeadState::branch;
  entry.capture_mode = biv::repo::CaptureMode::full;
  entry.capture.payload_prefix = "payload/transient-proof/";
  entry.bundle = "repos/transient-proof/repo.bundle";
  entry.promisor = true;
  entry.engine_source = biv::repo::EngineSourceState{
      .repo_path = "/Users/jack/private/transient-proof",
      .penumbra_paths = {"/Users/jack/private/secret.txt"},
      .neutralized_git_config_keys = {"remote.origin.promisor"}};
  auto manifest = fixed_manifest();
  manifest.repos = {entry};

  const auto json = must_serialize(manifest);

  CHECK(json.find("promisor") == std::string::npos);
  CHECK(json.find("engine_source") == std::string::npos);
  CHECK(json.find("/Users/jack/private") == std::string::npos);
}

TEST_CASE("FX-N capture_mode absence is licensed only by disjoint markers") {
  // FX-N (b.i): H's marker-free zero-ref unborn cell remains valid.
  REQUIRE(biv::manifest::parse(bytes_of(manifest_json_with_repo_rows(
                                   valid_payload_only_unborn_repo_json())))
              .has_value());
  // FX-N (b.ii): N's shallow marker licenses absence for a born row.
  REQUIRE(biv::manifest::parse(
              bytes_of(manifest_json_with_repo_rows(valid_shallow_repo_json())))
              .has_value());

  // FX-N (b.iii) NAMED MUTANT: unconditional absence licensing.
  auto born_without_mode = replace_once(valid_born_overlay_repo_json(),
                                        "\"capture_mode\":\"overlay\",", "");
  require_repo_parse_error(born_without_mode, "capture_mode");

  // FX-N (b.iv) NAMED MUTANT: rev1's XOR predicate rejects this composite.
  auto shallow_unborn = replace_once(
      valid_shallow_repo_json(),
      "\"sha\":\"6666666666666666666666666666666666666666\"", "\"sha\":null");
  shallow_unborn = replace_once(std::move(shallow_unborn), "\"branch\":null",
                                "\"branch\":\"new-main\"");
  shallow_unborn =
      replace_once(std::move(shallow_unborn), "\"head_state\":\"detached\"",
                   "\"head_state\":\"unborn\"");
  REQUIRE(biv::manifest::parse(
              bytes_of(manifest_json_with_repo_rows(shallow_unborn)))
              .has_value());
}

TEST_CASE("FX-N local_refs absence is licensed only by H and N") {
  // NAMED MUTANT: parse_local_refs treats absence as an empty array for all rows.
  require_repo_parse_error(
      replace_once(valid_born_overlay_repo_json(), "\"local_refs\":[{\"ref\":\"refs/heads/main\",\"sha\":\"8888888888888888888888888888888888888888\",\"availability\":\"remote-proven\",\"proof\":{\"remote\":\"origin\",\"url\":\"https://born.example/repo.git\",\"ref\":\"refs/heads/main\",\"tip_sha\":\"9999999999999999999999999999999999999999\"}}],", ""),
      "local_refs");

  const auto h_without_local_refs = replace_once(
      valid_payload_only_unborn_repo_json(), "\"local_refs\":[],", "");
  REQUIRE(biv::manifest::parse(
              bytes_of(manifest_json_with_repo_rows(h_without_local_refs)))
              .has_value());

  const auto n_without_local_refs =
      replace_once(valid_shallow_repo_json(), "\"local_refs\":[],", "");
  REQUIRE(biv::manifest::parse(
              bytes_of(manifest_json_with_repo_rows(n_without_local_refs)))
              .has_value());
}

TEST_CASE("Manifest parser refuses unsafe member paths but retains URL data") {
  // NAMED MUTANT: typed member-path fields bypass valid_manifest_path.
  const auto valid = valid_born_overlay_repo_json();
  struct PathMutation {
    std::string_view detail;
    std::string absolute;
    std::string traversal;
    std::string dot{};
  };
  const auto mutations = std::array{
      PathMutation{
          .detail = "relpath",
          .absolute = replace_once(valid, "\"relpath\":\"born\"",
                                   "\"relpath\":\"/absolute\""),
          .traversal = replace_once(valid, "\"relpath\":\"born\"",
                                    "\"relpath\":\"../escape\"")},
      PathMutation{
          .detail = "local_refs_bundle",
          .absolute = replace_once(
              valid, "\"capture\":",
              "\"local_refs_bundle\":\"/absolute\",\"capture\":"),
          .traversal = replace_once(
              valid, "\"capture\":",
              "\"local_refs_bundle\":\"../escape\",\"capture\":"),
          .dot = replace_once(valid, "\"capture\":",
                              "\"local_refs_bundle\":\".\",\"capture\":")},
      PathMutation{.detail = "bundle",
                   .absolute = replace_once(valid, "\"bundle\":null",
                                            "\"bundle\":\"/absolute\""),
                   .traversal = replace_once(valid, "\"bundle\":null",
                                             "\"bundle\":\"../escape\""),
                   .dot = replace_once(valid, "\"bundle\":null",
                                       "\"bundle\":\".\"")},
      PathMutation{.detail = "staged_patch",
                   .absolute = replace_once(valid, "\"staged_patch\":null",
                                            "\"staged_patch\":\"/absolute\""),
                   .traversal = replace_once(valid, "\"staged_patch\":null",
                                             "\"staged_patch\":\"../escape\""),
                   .dot = replace_once(valid, "\"staged_patch\":null",
                                       "\"staged_patch\":\".\"")},
      PathMutation{.detail = "worktree_patch",
                   .absolute = replace_once(valid, "\"worktree_patch\":null",
                                            "\"worktree_patch\":\"/absolute\""),
                   .traversal = replace_once(valid, "\"worktree_patch\":null",
                                             "\"worktree_patch\":\"../escape\""),
                   .dot = replace_once(valid, "\"worktree_patch\":null",
                                       "\"worktree_patch\":\".\"")},
      PathMutation{.detail = "payload_prefix",
                   .absolute = replace_once(valid, "\"payload_prefix\":\"payload/born/\"",
                                            "\"payload_prefix\":\"/absolute\""),
                   .traversal = replace_once(valid, "\"payload_prefix\":\"payload/born/\"",
                                             "\"payload_prefix\":\"../escape\""),
                   .dot = replace_once(valid, "\"payload_prefix\":\"payload/born/\"",
                                       "\"payload_prefix\":\".\"")},
      PathMutation{.detail = "path",
                   .absolute = replace_once(
                       valid, "\"forced_payload\":[]",
                       "\"forced_payload\":[{\"path\":\"/absolute\",\"reason\":\"adapter-other\"}]"),
                   .traversal = replace_once(
                       valid, "\"forced_payload\":[]",
                       "\"forced_payload\":[{\"path\":\"../escape\",\"reason\":\"adapter-other\"}]"),
                   .dot = replace_once(
                       valid, "\"forced_payload\":[]",
                       "\"forced_payload\":[{\"path\":\".\",\"reason\":\"adapter-other\"}]")},
  };
  for (const auto &mutation : mutations) {
    CAPTURE(mutation.detail);
    require_repo_parse_error(mutation.absolute, mutation.detail);
    require_repo_parse_error(mutation.traversal, mutation.detail);
    if (!mutation.dot.empty()) {
      require_repo_parse_error(mutation.dot, mutation.detail);
    }
  }

  REQUIRE(biv::manifest::parse(bytes_of(manifest_json_with_repo_rows(
              replace_once(valid, "\"relpath\":\"born\"", "\"relpath\":\".\""))))
              .has_value());

  const auto file_url_row = replace_once(
      valid, "\"remote\":\"https://born.example/repo.git\"",
      "\"remote\":\"file:///home/user/repo\"");
  const auto parsed = biv::manifest::parse(
      bytes_of(manifest_json_with_repo_rows(file_url_row)));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 1U);
  CHECK(parsed->repos.front().remote == "file:///home/user/repo");
  auto manifest = fixed_manifest();
  manifest.repos = parsed->repos;
  const auto reparsed =
      biv::manifest::parse(bytes_of(must_serialize(manifest)));
  REQUIRE(reparsed.has_value());
  require_repo_projection_equal(reparsed->repos.front(), parsed->repos.front());
}

TEST_CASE("FX-N shallow member validity is presence-aware") {
  // FX-N (c) NAMED MUTANT: null treated as marker absence.
  require_repo_parse_error(
      replace_once(valid_shallow_repo_json(),
                   "\"shallow\":{\"boundary\":["
                   "\"7777777777777777777777777777777777777777\"]}",
                   "\"shallow\":null"),
      "shallow");
  // FX-N (d.i): boundary is required.
  require_repo_parse_error(
      replace_once(valid_shallow_repo_json(),
                   "\"shallow\":{\"boundary\":["
                   "\"7777777777777777777777777777777777777777\"]}",
                   "\"shallow\":{}"),
      "boundary");
  // FX-N (d.ii): every boundary member is exactly 40 hex.
  require_repo_parse_error(
      replace_once(valid_shallow_repo_json(),
                   "7777777777777777777777777777777777777777", "not-40-hex"),
      "boundary");
  // FX-N (d.iii) NAMED MUTANT: a parser requiring non-empty boundary.
  const auto empty_boundary = replace_once(
      valid_shallow_repo_json(),
      "\"boundary\":[\"7777777777777777777777777777777777777777\"]",
      "\"boundary\":[]");
  REQUIRE(biv::manifest::parse(
              bytes_of(manifest_json_with_repo_rows(empty_boundary)))
              .has_value());
}

TEST_CASE("FX-N shallow composition cluster rejects each hostile coordinate") {
  const auto valid = valid_shallow_repo_json();
  // FX-N (e.i) NAMED MUTANT: a parser checking only the bundle clause.
  require_repo_parse_error(
      replace_once(valid, "\"local_refs\":[]",
                   "\"eligibility\":{\"method\":\"ls-remote-ancestry\","
                   "\"result\":\"proven\",\"checked_at\":\"2026-08-30T03:04:"
                   "05Z\",\"proof\":null},\"local_refs\":[]"),
      "eligibility");
  // FX-N (e.ii): bundle promise is forbidden for shallow payload-only rows.
  require_repo_parse_error(
      replace_once(valid, "\"bundle\":null",
                   "\"bundle\":\"repos/shallow-row/repo.bundle\""),
      "bundle");
  // FX-N (e.iii): no local ref availability state is honest here.
  require_repo_parse_error(
      replace_once(
          valid, "\"local_refs\":[]",
          "\"local_refs\":[{\"ref\":\"refs/heads/"
          "main\",\"sha\":\"8888888888888888888888888888888888888888\","
          "\"availability\":\"bundle-carried\",\"proof\":null}]"),
      "local_refs");
  // FX-N (e.iv): no thin local-ref bundle is honest here.
  require_repo_parse_error(
      replace_once(valid, "\"local_refs\":[]",
                   "\"local_refs\":[],\"local_refs_bundle\":\"repos/"
                   "shallow-row/local-refs.bundle\""),
      "local_refs_bundle");
  // FX-N (e.v/e.vi) NAMED MUTANT: absence-only capture_mode checking.
  for (const std::string_view mode : {"overlay", "full"}) {
    CAPTURE(mode);
    require_repo_parse_error(
        replace_once(valid, "\"dirty\":false",
                     "\"dirty\":false,\"capture_mode\":\"" + std::string{mode} +
                         "\""),
        "capture_mode");
  }
}

TEST_CASE("FX-N promisor-source and unknown notes round-trip") {
  auto row = replace_once(valid_shallow_repo_json(), "\"notes\":[]",
                          "\"notes\":[{\"kind\":\"promisor-source\"},{\"kind\":"
                          "\"future-note\",\"value\":17}]");
  const auto parsed =
      biv::manifest::parse(bytes_of(manifest_json_with_repo_rows(row)));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 1U);
  REQUIRE(parsed->repos.front().notes.size() == 2U);
  CHECK(std::holds_alternative<biv::repo::PromisorSourceNote>(
      parsed->repos.front().notes.at(0)));
  const auto *unknown =
      std::get_if<biv::repo::UnknownNote>(&parsed->repos.front().notes.at(1));
  REQUIRE(unknown != nullptr);
  CHECK(unknown->kind == "future-note");
  CHECK(unknown->verbatim_json == R"({"kind":"future-note","value":17})");

  auto manifest = fixed_manifest();
  manifest.repos = parsed->repos;
  const auto reparsed =
      biv::manifest::parse(bytes_of(must_serialize(manifest)));
  REQUIRE(reparsed.has_value());
  require_repo_projection_equal(reparsed->repos.front(), parsed->repos.front());
}

TEST_CASE("FX-O writer refuses unsafe member paths without emitting bytes") {
  auto entry = valid_born_repo_entry();

  // FX-O-LEG (a)
  // O-MUTANT: an asserting, UB, or silently-emitting writer => RED here.
  entry.bundle = "/abs/repo.bundle";
  require_repo_write_error(entry, "bundle", "absolute");

  // FX-O-LEG (b)
  // O-MUTANT: a prefix-only checker misses traversal while absolute stays green.
  entry = valid_born_repo_entry();
  entry.capture.staged_patch = "../x";
  require_repo_write_error(entry, "staged_patch", "traversal");

  entry = valid_born_repo_entry();
  entry.relpath = "../x";
  // FX-O-FIELD 1 relpath
  // FX-O-INV path-relpath
  require_repo_write_error(entry, "relpath", "traversal");

  entry = valid_born_repo_entry();
  entry.local_refs.front().availability =
      biv::repo::RefAvailability::bundle_carried;
  entry.local_refs.front().proof = std::nullopt;
  entry.local_refs_bundle = "../x";
  // FX-O-FIELD 2 local_refs_bundle
  // FX-O-INV path-local-refs-bundle
  require_repo_write_error(entry, "local_refs_bundle", "traversal");

  entry = valid_born_repo_entry();
  entry.bundle = "../x";
  // FX-O-FIELD 3 bundle
  // FX-O-INV path-bundle
  require_repo_write_error(entry, "bundle", "traversal");

  entry = valid_born_repo_entry();
  entry.capture.staged_patch = "../x";
  // FX-O-FIELD 4 capture.staged_patch
  // FX-O-INV path-staged-patch
  require_repo_write_error(entry, "staged_patch", "traversal");

  entry = valid_born_repo_entry();
  entry.capture.worktree_patch = "../x";
  // FX-O-FIELD 5 capture.worktree_patch
  // FX-O-INV path-worktree-patch
  require_repo_write_error(entry, "worktree_patch", "traversal");

  entry = valid_born_repo_entry();
  entry.capture.payload_prefix = "../x";
  // FX-O-FIELD 6 capture.payload_prefix
  // FX-O-INV path-payload-prefix
  require_repo_write_error(entry, "payload_prefix", "traversal");

  entry = valid_born_repo_entry();
  entry.capture.forced_payload = {{
      .path = "../x",
      .reason = biv::repo::ForcedPayloadReason::adapter_other,
  }};
  // FX-O-FIELD 7 capture.forced_payload.path
  // FX-O-INV path-forced-payload
  require_repo_write_error(entry, "forced_payload.path", "traversal");

  entry = valid_born_repo_entry();
  entry.relpath = ".";
  auto manifest = fixed_manifest();
  manifest.repos = {entry};
  REQUIRE(biv::manifest::serialize(manifest).has_value());
}

TEST_CASE("FX-O local refs bundle relation is enforced in both directions") {
  auto entry = valid_born_repo_entry();
  entry.local_refs_bundle = "repos/born/local-refs.bundle";
  // FX-O-LEG (d.i)
  // FX-O-INV local-refs-bundle-biconditional
  // O-MUTANT: enforcement at one point only => RED at the unchecked point.
  require_repo_write_error(entry, "local_refs_bundle", "biconditional");

  entry = valid_born_repo_entry();
  entry.local_refs.front().availability =
      biv::repo::RefAvailability::bundle_carried;
  entry.local_refs.front().proof = std::nullopt;
  // FX-O-LEG (d.ii)
  // O-MUTANT: rev1's licensing-only rule => RED here while d.i stays green.
  require_repo_write_error(entry, "local_refs_bundle", "biconditional");

  const auto valid = valid_born_overlay_repo_json();
  require_repo_parse_error(
      replace_once(valid, "\"capture\":",
                   "\"local_refs_bundle\":\"repos/born/local-refs.bundle\","
                   "\"capture\":"),
      "local_refs_bundle");
  auto row_without_bundle = replace_once(
      valid, "\"availability\":\"remote-proven\"",
      "\"availability\":\"bundle-carried\"");
  row_without_bundle =
      replace_last_once(std::move(row_without_bundle),
                        "\"proof\":{\"remote\":\"origin\",\"url\":"
                        "\"https://born.example/repo.git\",\"ref\":"
                        "\"refs/heads/main\",\"tip_sha\":"
                        "\"9999999999999999999999999999999999999999\"}",
                        "\"proof\":null");
  require_repo_parse_error(row_without_bundle, "local_refs_bundle");
}

TEST_CASE("FX-O refuses unnamed serialized enum values") {
  auto entry = valid_born_repo_entry();
  entry.kind = static_cast<biv::repo::RepoKind>(99);
  // FX-O-INV enum-repo-kind
  require_repo_write_error(entry, "kind", "enum-domain");

  entry = valid_born_repo_entry();
  entry.head_state = static_cast<biv::repo::HeadState>(99);
  // FX-O-INV enum-head-state
  require_repo_write_error(entry, "head_state", "enum-domain");

  entry = valid_born_repo_entry();
  entry.capture_mode = static_cast<biv::repo::CaptureMode>(99);
  // FX-O-INV enum-capture-mode
  require_repo_write_error(entry, "capture_mode", "enum-domain");

  entry = valid_born_repo_entry();
  entry.eligibility->result =
      static_cast<biv::repo::EligibilityResult>(99);
  // FX-O-INV enum-eligibility-result
  require_repo_write_error(entry, "eligibility.result", "enum-domain");

  entry = valid_born_repo_entry();
  entry.local_refs.front().availability =
      static_cast<biv::repo::RefAvailability>(99);
  // FX-O-INV enum-ref-availability
  require_repo_write_error(entry, "local_refs.availability", "enum-domain");

  entry = valid_born_repo_entry();
  entry.capture.forced_payload = {{
      .path = "payload/x",
      .reason = static_cast<biv::repo::ForcedPayloadReason>(99),
  }};
  // FX-O-INV enum-forced-payload-reason
  require_repo_write_error(entry, "forced_payload.reason", "enum-domain");
}

TEST_CASE("FX-O writer refuses invalid UTF-8 in every carried repo string") {
  const auto invalid_utf8 = std::string{"\xFF"};
  struct Mutation {
    std::string_view field;
    std::function<void(biv::repo::RepoEntry &)> apply;
  };
  const auto mutations = std::array<Mutation, 23>{
      Mutation{"id", [&](auto &entry) { entry.id = invalid_utf8; }},
      Mutation{"relpath", [&](auto &entry) { entry.relpath = invalid_utf8; }},
      Mutation{"parent_id", [&](auto &entry) { entry.parent_id = invalid_utf8; }},
      Mutation{"remote", [&](auto &entry) { entry.remote = invalid_utf8; }},
      Mutation{"remotes.name", [&](auto &entry) { entry.remotes.front().name = invalid_utf8; }},
      Mutation{"remotes.url", [&](auto &entry) { entry.remotes.front().url = invalid_utf8; }},
      Mutation{"branch", [&](auto &entry) { entry.branch = invalid_utf8; }},
      Mutation{"eligibility.method", [&](auto &entry) { entry.eligibility->method = invalid_utf8; }},
      Mutation{"eligibility.checked_at", [&](auto &entry) { entry.eligibility->checked_at = invalid_utf8; }},
      Mutation{"eligibility.proof.remote", [&](auto &entry) { entry.eligibility->proof->remote = invalid_utf8; }},
      Mutation{"eligibility.proof.url", [&](auto &entry) { entry.eligibility->proof->url = invalid_utf8; }},
      Mutation{"eligibility.proof.ref", [&](auto &entry) { entry.eligibility->proof->ref = invalid_utf8; }},
      Mutation{"local_refs.ref", [&](auto &entry) { entry.local_refs.front().ref = invalid_utf8; }},
      Mutation{"local_refs.proof.remote", [&](auto &entry) { entry.local_refs.front().proof->remote = invalid_utf8; }},
      Mutation{"local_refs.proof.url", [&](auto &entry) { entry.local_refs.front().proof->url = invalid_utf8; }},
      Mutation{"local_refs.proof.ref", [&](auto &entry) { entry.local_refs.front().proof->ref = invalid_utf8; }},
      Mutation{"local_refs_bundle", [&](auto &entry) {
                 entry.local_refs.front().availability = biv::repo::RefAvailability::bundle_carried;
                 entry.local_refs.front().proof.reset();
                 entry.local_refs_bundle = invalid_utf8;
               }},
      Mutation{"staged_patch", [&](auto &entry) { entry.capture.staged_patch = invalid_utf8; }},
      Mutation{"worktree_patch", [&](auto &entry) { entry.capture.worktree_patch = invalid_utf8; }},
      Mutation{"capture.payload_prefix", [&](auto &entry) { entry.capture.payload_prefix = invalid_utf8; }},
      Mutation{"forced_payload.path", [&](auto &entry) {
                 entry.capture.forced_payload = {{.path = invalid_utf8,
                                                   .reason = biv::repo::ForcedPayloadReason::adapter_other}};
               }},
      Mutation{"capture.capture_env.core_autocrlf", [&](auto &entry) { entry.capture.capture_env.core_autocrlf = invalid_utf8; }},
      Mutation{"bundle", [&](auto &entry) { entry.bundle = invalid_utf8; }},
  };
  for (const auto &mutation : mutations) {
    auto entry = valid_born_repo_entry();
    mutation.apply(entry);
    CAPTURE(mutation.field);
    // FX-O-INV utf8-id
    // FX-O-INV utf8-relpath
    // FX-O-INV utf8-parent-id
    // FX-O-INV utf8-remote
    // FX-O-INV utf8-remotes-name
    // FX-O-INV utf8-remotes-url
    // FX-O-INV utf8-branch
    // FX-O-INV utf8-eligibility-method
    // FX-O-INV utf8-eligibility-checked-at
    // FX-O-INV utf8-eligibility-proof-remote
    // FX-O-INV utf8-eligibility-proof-url
    // FX-O-INV utf8-eligibility-proof-ref
    // FX-O-INV utf8-local-refs-ref
    // FX-O-INV utf8-local-refs-proof-remote
    // FX-O-INV utf8-local-refs-proof-url
    // FX-O-INV utf8-local-refs-proof-ref
    // FX-O-INV utf8-local-refs-bundle
    // FX-O-INV utf8-staged-patch
    // FX-O-INV utf8-worktree-patch
    // FX-O-INV utf8-payload-prefix
    // FX-O-INV utf8-forced-payload-path
    // FX-O-INV utf8-core-autocrlf
    // FX-O-INV utf8-bundle
    require_repo_write_error(entry, mutation.field, "utf8");
  }
}

TEST_CASE("FX-O omits contextual capture_mode before enum validation") {
  for (auto entry : {valid_shallow_repo_entry(),
                     repo_entry_from_json(valid_payload_only_unborn_repo_json())}) {
    entry.capture_mode = static_cast<biv::repo::CaptureMode>(99);
    auto manifest = fixed_manifest();
    manifest.repos = {entry};
    const auto serialized = biv::manifest::serialize(manifest);
    REQUIRE(serialized.has_value());
    const auto parsed = biv::manifest::parse(bytes_of(*serialized));
    REQUIRE(parsed.has_value());
    REQUIRE(parsed->repos.size() == 1U);
    require_repo_projection_equal(parsed->repos.front(), entry);
  }
}

TEST_CASE("FX-O validates unknown note shape and projection before emission") {
  auto entry = valid_born_repo_entry();
  entry.notes = {biv::repo::UnknownNote{
      .kind = "future", .verbatim_json = R"({"kind":"future")"}};
  // FX-O-INV unknown-note-json-valid
  require_repo_write_error(entry, "notes", "unknown-note-json-valid");

  entry.notes = {biv::repo::UnknownNote{
      .kind = "future",
      .verbatim_json = R"({"kind":"future"}{"kind":"later"})"}};
  // FX-O-INV unknown-note-single-value
  require_repo_write_error(entry, "notes", "unknown-note-single-value");

  entry.notes = {biv::repo::UnknownNote{
      .kind = "future", .verbatim_json = "[1]"}};
  // FX-O-INV unknown-note-object
  require_repo_write_error(entry, "notes", "unknown-note-object");

  entry.notes = {biv::repo::UnknownNote{.kind = "future", .verbatim_json = "{}"}};
  // FX-O-INV unknown-note-kind-present
  require_repo_write_error(entry, "notes", "unknown-note-kind-present");

  entry.notes = {biv::repo::UnknownNote{
      .kind = "future", .verbatim_json = R"({"kind":7})"}};
  // FX-O-INV unknown-note-kind-string
  require_repo_write_error(entry, "notes", "unknown-note-kind-string");

  entry.notes = {biv::repo::UnknownNote{
      .kind = "future-a", .verbatim_json = R"({"kind":"future-b"})"}};
  // FX-O-INV unknown-note-kind
  require_repo_write_error(entry, "notes", "unknown-note-kind");

  entry.notes = {biv::repo::UnknownNote{
      .kind = "promisor-source",
      .verbatim_json = R"({"kind":"promisor-source"})"}};
  // FX-O-INV unknown-note-aliases-structured
  require_repo_write_error(entry, "notes", "unknown-note-aliases-structured");

  const std::string raw = R"({ "kind" : "future", "value" : 7 })";
  entry.notes = {biv::repo::UnknownNote{.kind = "future", .verbatim_json = raw}};
  auto manifest = fixed_manifest();
  manifest.repos = {entry};
  const auto serialized = biv::manifest::serialize(manifest);
  REQUIRE(serialized.has_value());
  const auto parsed = biv::manifest::parse(bytes_of(*serialized));
  REQUIRE(parsed.has_value());
  const auto *unknown =
      std::get_if<biv::repo::UnknownNote>(&parsed->repos.front().notes.front());
  REQUIRE(unknown != nullptr);
  // FX-O-CTRL unknown-note-roundtrip
  CHECK(unknown->verbatim_json == raw);
}

TEST_CASE("FX-O shared predicate inventory refuses typed parser-invalid rows") {
  auto entry = valid_born_repo_entry();
  entry.head_state = biv::repo::HeadState::unborn;
  // FX-O-INV sha-head-state
  require_repo_write_error(entry, "sha", "head-state");

  entry = valid_born_repo_entry();
  entry.sha = "not-40-hex";
  // FX-O-INV sha-hex
  require_repo_write_error(entry, "sha", "hex-object-id");

  entry = valid_born_repo_entry();
  entry.eligibility->method = "other";
  // FX-O-INV eligibility-method
  require_repo_write_error(entry, "eligibility", "method");

  entry = valid_born_repo_entry();
  entry.eligibility->proof->tip_sha = "not-40-hex";
  // FX-O-INV eligibility-proof-tip-sha
  require_repo_write_error(entry, "eligibility.proof.tip_sha",
                           "hex-object-id");

  entry = valid_born_repo_entry();
  entry.local_refs.front().sha = "not-40-hex";
  // FX-O-INV local-refs-sha
  require_repo_write_error(entry, "local_refs.sha", "hex-object-id");

  entry = valid_born_repo_entry();
  entry.local_refs.front().proof->tip_sha = "not-40-hex";
  // FX-O-INV local-refs-proof-tip-sha
  require_repo_write_error(entry, "local_refs.proof.tip_sha",
                           "hex-object-id");

  entry = valid_born_repo_entry();
  entry.local_refs.front().proof = std::nullopt;
  // FX-O-INV local-refs-proof-presence
  require_repo_write_error(entry, "local_refs.proof", "availability");

  entry = valid_shallow_repo_entry();
  entry.eligibility = valid_born_repo_entry().eligibility;
  // FX-O-INV shallow-eligibility
  require_repo_write_error(entry, "eligibility", "shallow");

  entry = valid_shallow_repo_entry();
  entry.local_refs = valid_born_repo_entry().local_refs;
  // FX-O-INV shallow-local-refs
  require_repo_write_error(entry, "local_refs", "shallow");

  entry = valid_shallow_repo_entry();
  entry.local_refs_bundle = "repos/shallow/local-refs.bundle";
  // FX-O-INV shallow-local-refs-bundle
  require_repo_write_error(entry, "local_refs_bundle", "shallow");

  entry = valid_shallow_repo_entry();
  entry.bundle = "repos/shallow/repo.bundle";
  // FX-O-INV shallow-bundle
  require_repo_write_error(entry, "bundle", "shallow");

  entry = valid_shallow_repo_entry();
  entry.shallow->boundary = {"not-40-hex"};
  // FX-O-INV shallow-boundary-hex
  require_repo_write_error(entry, "boundary", "hex-object-id");

  entry = valid_g_unborn_repo_entry();
  entry.eligibility.reset();
  // FX-O-INV unborn-bundle-eligibility
  require_repo_write_error(entry, "eligibility", "unborn-bundle");

  entry = valid_g_unborn_repo_entry();
  entry.eligibility->result = biv::repo::EligibilityResult::proven;
  // FX-O-INV unborn-bundle-result
  require_repo_write_error(entry, "eligibility", "unborn-head-result");

  entry = valid_g_unborn_repo_entry();
  entry.capture_mode = biv::repo::CaptureMode::overlay;
  // FX-O-INV unborn-bundle-capture-mode
  require_repo_write_error(entry, "capture_mode", "unborn-bundle-full");

  entry = valid_born_repo_entry();
  entry.eligibility->result = biv::repo::EligibilityResult::unborn_head;
  // FX-O-INV born-unborn-head-result
  require_repo_write_error(entry, "eligibility", "born-unborn-head");

  entry = repo_entry_from_json(valid_payload_only_unborn_repo_json());
  entry.eligibility = valid_born_repo_entry().eligibility;
  // FX-O-INV payload-only-unborn-eligibility
  require_repo_write_error(entry, "eligibility", "payload-only-unborn");

  entry = repo_entry_from_json(valid_payload_only_unborn_repo_json());
  entry.local_refs = valid_born_repo_entry().local_refs;
  // FX-O-INV unborn-no-bundle-local-refs
  require_repo_write_error(entry, "local_refs", "unborn-no-bundle-local-refs");
}

TEST_CASE("FX-O parser preserves legacy shared-validator details") {
  const auto valid = valid_born_overlay_repo_json();
  require_repo_parse_error(
      replace_once(valid, "9999999999999999999999999999999999999999",
                   "not-40-hex"),
      "eligibility");
  require_repo_parse_error(
      replace_once(valid, "8888888888888888888888888888888888888888",
                   "not-40-hex"),
      "sha");
  require_repo_parse_error(
      replace_last_once(valid, "8888888888888888888888888888888888888888",
                        "not-40-hex"),
      "local_refs");
  require_repo_parse_error(
      replace_last_once(valid, "9999999999999999999999999999999999999999",
                        "not-40-hex"),
      "local_refs");
  const auto payload = valid_payload_only_unborn_repo_json();
  auto payload_with_refs = replace_once(
      payload, "\"local_refs\":[]",
      "\"local_refs\":[{\"ref\":\"refs/heads/"
      "main\",\"sha\":\"8888888888888888888888888888888888888888\","
      "\"availability\":\"bundle-carried\",\"proof\":null}]");
  payload_with_refs = replace_once(payload_with_refs, "\"dirty\":false",
                                   "\"dirty\":false,\"capture_mode\":\"full\"");
  require_repo_parse_error(payload_with_refs, "eligibility");
}

TEST_CASE("FX-O validates every typed non-carried-refs predicate") {
  auto entry = valid_born_repo_entry();
  const auto valid_note = biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/a"}, .omitted_count = std::nullopt};

  entry.notes = {valid_note, valid_note};
  // FX-O-INV non-carried-unique
  require_repo_write_error(entry, "notes", "non-carried-unique");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = std::vector<std::string>(4097U, "refs/custom/a"),
      .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-refs-cap
  require_repo_write_error(entry, "notes", "refs-cap");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/a"}, .omitted_count = 0U}};
  // FX-O-INV non-carried-omitted-positive
  require_repo_write_error(entry, "notes", "omitted-count");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/a"},
      .omitted_count = (UINT64_C(1) << 53U)}};
  // FX-O-INV non-carried-omitted-max
  require_repo_write_error(entry, "notes", "omitted-count");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {}, .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-nonempty
  require_repo_write_error(entry, "notes", "refs-or-omitted");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {R"(refs/custom/\q)"}, .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-p1
  require_repo_write_error(entry, "notes", "p1-decodable");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/" + std::string(1013U, 'a')},
      .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-ref-bytes
  require_repo_write_error(entry, "notes", "ref-bytes-cap");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"not-a-full-ref"}, .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-full-ref
  require_repo_write_error(entry, "notes", "full-ref-name");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/heads/main"}, .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-catch-all
  require_repo_write_error(entry, "notes", "catch-all-ref");

  entry.notes = {biv::repo::NonCarriedRefsNote{
      .refs_p1 = {"refs/custom/z", "refs/custom/a"},
      .omitted_count = std::nullopt}};
  // FX-O-INV non-carried-strict-order
  require_repo_write_error(entry, "notes", "strict-order");
}

TEST_CASE("FX-O projection oracle preserves carried state and ignores context") {
  // FX-O-LEG (e)
  auto entry = valid_shallow_repo_entry();
  auto manifest = fixed_manifest();
  manifest.repos = {entry};
  const auto plain = biv::manifest::serialize(manifest);
  REQUIRE(plain.has_value());

  entry.promisor = true;
  entry.capture_mode = biv::repo::CaptureMode::overlay;
  entry.engine_source = biv::repo::EngineSourceState{
      .repo_path = "/private/repo",
      .penumbra_paths = {"/private/repo/secret"},
      .neutralized_git_config_keys = {"remote.origin.promisor"},
  };
  manifest.repos = {entry};
  const auto with_context = biv::manifest::serialize(manifest);
  REQUIRE(with_context.has_value());
  CHECK(*with_context == *plain);
  const auto parsed = biv::manifest::parse(bytes_of(*with_context));
  REQUIRE(parsed.has_value());
  require_repo_projection_equal(parsed->repos.front(), entry);
  CHECK_FALSE(parsed->repos.front().promisor);
  CHECK_FALSE(parsed->repos.front().engine_source.has_value());
  CHECK(parsed->repos.front().capture_mode == biv::repo::CaptureMode::full);
  // O-MUTANT: full typed equality or refusal of non-carried state => RED here.

  auto full_carrier = valid_born_repo_entry();
  full_carrier.promisor = true;
  full_carrier.engine_source = biv::repo::EngineSourceState{
      .repo_path = "/private/full", .penumbra_paths = {"/private/full/x"}};
  manifest.repos = {full_carrier};
  const auto full_json = biv::manifest::serialize(manifest);
  REQUIRE(full_json.has_value());
  const auto full_parsed = biv::manifest::parse(bytes_of(*full_json));
  REQUIRE(full_parsed.has_value());
  require_repo_projection_equal(full_parsed->repos.front(), full_carrier);
  CHECK_FALSE(full_parsed->repos.front().promisor == full_carrier.promisor);
  CHECK_FALSE(full_parsed->repos.front().engine_source.has_value());

  auto unborn = valid_g_unborn_repo_entry();
  manifest.repos = {unborn};
  const auto unborn_json = biv::manifest::serialize(manifest);
  REQUIRE(unborn_json.has_value());
  const auto unborn_parsed = biv::manifest::parse(bytes_of(*unborn_json));
  REQUIRE(unborn_parsed.has_value());
  require_repo_projection_equal(unborn_parsed->repos.front(), unborn);
  CHECK(unborn_parsed->repos.front().capture_mode ==
        biv::repo::CaptureMode::full);
  CHECK(unborn_json->find("\"capture_mode\": \"full\"") !=
        std::string::npos);
  const auto projected_unborn = project_row(unborn);
  REQUIRE(projected_unborn.contextual_capture_mode.has_value());
  CHECK(*projected_unborn.contextual_capture_mode ==
        biv::repo::CaptureMode::full);

  auto payload_only = repo_entry_from_json(valid_payload_only_unborn_repo_json());
  manifest.repos = {payload_only};
  const auto payload_only_json = biv::manifest::serialize(manifest);
  REQUIRE(payload_only_json.has_value());
  const auto payload_only_parsed =
      biv::manifest::parse(bytes_of(*payload_only_json));
  REQUIRE(payload_only_parsed.has_value());
  require_repo_projection_equal(payload_only_parsed->repos.front(),
                                payload_only);
  // O-MUTANT: a born-only projection => RED at the direct presence oracle.
  // O-MUTANT: drop one writer clause => parser rejection reds a round-trip.
}

TEST_CASE("FX-O URL fields remain data") {
  // FX-O-LEG (f)
  auto entry = valid_born_repo_entry();
  entry.remote = "file:///home/user/repo";
  entry.remotes.front().url = "file:///home/user/repo";
  entry.eligibility->proof->url = "file:///home/user/repo";
  entry.local_refs.front().proof->url = "file:///home/user/repo";
  auto manifest = fixed_manifest();
  manifest.repos = {entry};
  const auto serialized = biv::manifest::serialize(manifest);
  REQUIRE(serialized.has_value());
  const auto parsed = biv::manifest::parse(bytes_of(*serialized));
  REQUIRE(parsed.has_value());
  require_repo_projection_equal(parsed->repos.front(), entry);
  // O-MUTANT: an over-broad path validator rejects absolute URL data.
}

TEST_CASE("Manifest preserves unknown notes containing later placeholders") {
  auto manifest = fixed_manifest();
  auto entry = biv::repo::RepoEntry{};
  entry.id = "unknown-collision";
  entry.relpath = "unknown-collision";
  entry.remote = "https://example.invalid/unknown-collision.git";
  entry.sha = "abababababababababababababababababababab";
  entry.branch = "main";
  entry.head_state = biv::repo::HeadState::branch;
  entry.capture_mode = biv::repo::CaptureMode::full;
  entry.capture.payload_prefix = "payload/unknown-collision/";
  entry.bundle = "repos/unknown-collision/repo.bundle";
  entry.notes.emplace_back(biv::repo::UnknownNote{
      .kind = "future-early",
      .verbatim_json =
          R"({"kind":"future-early","collision":"__biv_repo_unknown_note_0_1"})"});
  entry.notes.emplace_back(biv::repo::UnknownNote{
      .kind = "future-later", .verbatim_json = R"({"kind":"future-later"})"});
  manifest.repos = {entry};

  const auto parsed = biv::manifest::parse(bytes_of(must_serialize(manifest)));

  REQUIRE(parsed.has_value());
  REQUIRE(parsed->repos.size() == 1U);
  require_repo_projection_equal(parsed->repos.front(), entry);
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
  const int far_future_schema = biv::manifest::kEntrySchemaParseCeiling + 97;
  auto unknown_agent = codex_session_entry();
  unknown_agent.agent = "future-tool";
  unknown_agent.artifacts = {"agents/future-tool/x.jsonl"};
  unknown_agent.children = {};
  auto parsed_unknown = biv::manifest::parse(bytes_of(manifest_json_with({unknown_agent})));
  REQUIRE(parsed_unknown.has_value());
  REQUIRE(parsed_unknown->agent_sessions.size() == 1);
  CHECK(parsed_unknown->agent_sessions.front().agent == "future-tool");

  const auto future_schema_json = replace_once(
      manifest_json_with({codex_session_entry()}), "\"entry_schema\": 1",
      "\"entry_schema\": " + std::to_string(far_future_schema));
  auto parsed_future_schema =
      biv::manifest::parse(bytes_of(future_schema_json));
  REQUIRE(parsed_future_schema.has_value());
  REQUIRE(parsed_future_schema->agent_sessions.size() == 1);
  CHECK(parsed_future_schema->agent_sessions.front().entry_schema ==
        far_future_schema);
  CHECK(parsed_future_schema->agent_sessions.front().stub_member_footprint ==
        std::vector<std::string>{"agents/codex/019f-aaaa.jsonl",
                                 "agents/codex/019f-bbbb.jsonl"});

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
  minimal_future.replace(
      entry_begin, entry_end - entry_begin,
      "{\"agent\":\"future-tool\",\"entry_schema\":" +
          std::to_string(far_future_schema) + "}");
  auto parsed_minimal_future = biv::manifest::parse(bytes_of(minimal_future));
  REQUIRE(parsed_minimal_future.has_value());
  REQUIRE(parsed_minimal_future->agent_sessions.size() == 1);
  CHECK(parsed_minimal_future->agent_sessions.front().entry_schema ==
        far_future_schema);
  CHECK(parsed_minimal_future->agent_sessions.front().stub_member_footprint.empty());
}

TEST_CASE("Manifest reader accepts schema 2 entries in full and skips newer schemas") {
  const auto schema_two =
      biv::manifest::parse(bytes_of(manifest_json_with_parent_edge(
          biv::manifest::kEntrySchemaParseCeiling)));
  REQUIRE(schema_two.has_value());
  REQUIRE(schema_two->agent_sessions.size() == 1U);
  CHECK(schema_two->agent_sessions.front().agent_version_at_pack == "0.142.5");
  CHECK(schema_two->agent_sessions.front().children.size() == 2U);
  CHECK(schema_two->agent_sessions.front().children.back().parent_id ==
        std::optional<std::string>{"019f-bbbb"});

  for (const int schema : {biv::manifest::kEntrySchemaParseCeiling + 1,
                           biv::manifest::kEntrySchemaParseCeiling + 97}) {
    CAPTURE(schema);
    const auto newer =
        biv::manifest::parse(bytes_of(manifest_json_with_parent_edge(schema)));
    REQUIRE(newer.has_value());
    REQUIRE(newer->agent_sessions.size() == 1U);
    CHECK(newer->agent_sessions.front().agent == "codex");
    CHECK(newer->agent_sessions.front().entry_schema == schema);
    CHECK(newer->agent_sessions.front().agent_version_at_pack.empty());
    CHECK(newer->agent_sessions.front().children.empty());
    CHECK(newer->agent_sessions.front().artifacts.empty());
    CHECK(newer->agent_sessions.front().stub_member_footprint ==
          std::vector<std::string>{"agents/codex/019f-aaaa.jsonl",
                                   "agents/codex/019f-bbbb.jsonl",
                                   "agents/codex/019f-cccc.jsonl"});
  }
}

TEST_CASE("Manifest stub footprint validates paths and one manifest-wide occurrence set",
          "[slice-e][stub-footprint]") {
  const auto require_error = [](const std::string& json,
                                const std::string_view detail) {
    const auto parsed = biv::manifest::parse(bytes_of(json));
    REQUIRE_FALSE(parsed.has_value());
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
    CHECK(parsed.error().detail == detail);
  };

  SECTION("footprint paths use the parsed-entry artifact grammar") {
    auto entry = codex_session_entry();
    entry.children.clear();
    entry.artifacts = {"../must-not-be-admitted"};
    require_error(as_stub(manifest_json_with({entry})), "artifact-prefix");
  }

  SECTION("a stub cannot alias a parsed entry member") {
    auto parsed_entry = codex_session_entry();
    parsed_entry.children.clear();
    auto stub_entry = codex_session_entry();
    stub_entry.original_session_ids.primary = "019f-cccc";
    stub_entry.children.clear();
    stub_entry.artifacts = parsed_entry.artifacts;
    auto json = manifest_json_with({parsed_entry, stub_entry});
    json = replace_last_once(
        std::move(json), "\"entry_schema\": 1",
        "\"entry_schema\": " +
            std::to_string(biv::manifest::kEntrySchemaParseCeiling + 1));
    require_error(json, "artifact-uniqueness");
  }

  SECTION("entry and child occurrences within one stub cannot alias") {
    auto entry = codex_session_entry();
    entry.children.front().artifacts = entry.artifacts;
    require_error(as_stub(manifest_json_with({entry})),
                  "artifact-uniqueness");
  }

  SECTION("two stubs cannot claim the same member") {
    auto first = codex_session_entry();
    first.children.clear();
    auto second = first;
    second.original_session_ids.primary = "019f-cccc";
    require_error(all_as_stubs(manifest_json_with({first, second})),
                  "artifact-uniqueness");
  }
}

TEST_CASE("Manifest stub footprint refuses bearing-key duplicates without reading graph values",
          "[slice-e][stub-footprint]") {
  const auto base = as_stub(manifest_json_with({codex_session_entry()}));
  const auto require_error = [](const std::string& json,
                                const std::string_view detail) {
    const auto parsed = biv::manifest::parse(bytes_of(json));
    REQUIRE_FALSE(parsed.has_value());
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
    CHECK(parsed.error().detail == detail);
  };

  SECTION("duplicate entry artifacts names their own class") {
    require_error(
        replace_once(base, "\"agent\": \"codex\",",
                     "\"agent\": \"codex\",\n"
                     "      \"artifacts\": [\"agents/codex/extra.jsonl\"],"),
        "stub-footprint-entry-artifacts-duplicate-key");
  }

  SECTION("duplicate entry children names their own class") {
    require_error(
        replace_once(base, "\"agent\": \"codex\",",
                     "\"agent\": \"codex\",\n"
                     "      \"children\": [],"),
        "stub-footprint-entry-children-duplicate-key");
  }

  SECTION("duplicate child artifacts names their own class") {
    require_error(
        replace_once(base, "\"original_id\": \"019f-bbbb\",",
                     "\"original_id\": \"019f-bbbb\",\n"
                     "        \"artifacts\": [\"agents/codex/extra.jsonl\"],"),
        "stub-footprint-child-artifacts-duplicate-key");
  }

  SECTION("duplicate hostile original_id values remain unread") {
    const auto parsed = biv::manifest::parse(bytes_of(replace_once(
        base, "\"original_id\": \"019f-bbbb\",",
        "\"original_id\": 7,\n        \"original_id\": false,")));
    REQUIRE(parsed.has_value());
    CHECK(parsed->agent_sessions.front().children.empty());
    CHECK(parsed->agent_sessions.front().stub_member_footprint ==
          std::vector<std::string>{"agents/codex/019f-aaaa.jsonl",
                                   "agents/codex/019f-bbbb.jsonl"});
  }

  SECTION("duplicate hostile parent_id values remain unread") {
    const auto parsed = biv::manifest::parse(bytes_of(replace_once(
        base, "\"original_id\": \"019f-bbbb\",",
        "\"original_id\": \"019f-bbbb\",\n"
        "        \"parent_id\": null,\n        \"parent_id\": false,")));
    REQUIRE(parsed.has_value());
    CHECK(parsed->agent_sessions.front().children.empty());
    CHECK(parsed->agent_sessions.front().stub_member_footprint ==
          std::vector<std::string>{"agents/codex/019f-aaaa.jsonl",
                                   "agents/codex/019f-bbbb.jsonl"});
  }

  SECTION("duplicate hostile original_path values remain unread") {
    const auto parsed = biv::manifest::parse(bytes_of(replace_once(
        base, "\"original_path\": \"/mnt/c/Users/x/proj\",",
        "\"original_path\": null,\n      \"original_path\": false,")));
    REQUIRE(parsed.has_value());
    CHECK(parsed->agent_sessions.front().original_path.empty());
    CHECK(parsed->agent_sessions.front().stub_member_footprint ==
          std::vector<std::string>{"agents/codex/019f-aaaa.jsonl",
                                   "agents/codex/019f-bbbb.jsonl"});
  }
}

TEST_CASE("Manifest stub footprint enforces graph-free caps before reading excess nodes",
          "[slice-e][stub-footprint]") {
  const auto require_cap = [](const std::string& json,
                              const std::string_view detail) {
    const auto parsed = biv::manifest::parse(bytes_of(json));
    REQUIRE_FALSE(parsed.has_value());
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
    CHECK(parsed.error().detail == detail);
    CHECK(parsed.error().detail.find("entry=") == std::string::npos);
  };

  SECTION("the 1025th child is refused before its invalid path is read") {
    const auto at_cap = biv::manifest::parse(bytes_of(as_stub(
        manifest_json_with({entry_with_children(1024)}))));
    REQUIRE(at_cap.has_value());
    CHECK(at_cap->agent_sessions.front().stub_member_footprint.size() ==
          1025U);

    auto json = as_stub(manifest_json_with({entry_with_children(1025)}));
    json = replace_once(std::move(json), child_artifact(1024, 0),
                        "../must-not-be-read");
    require_cap(json, "children-node-cap");
  }

  SECTION("entry artifacts retain the per-node cap") {
    auto entry = codex_session_entry();
    entry.children.clear();
    entry.artifacts.clear();
    for (std::size_t i = 0; i < 257U; ++i) {
      entry.artifacts.push_back("agents/codex/entry-artifact-" +
                                std::to_string(i) + ".jsonl");
    }
    require_cap(as_stub(manifest_json_with({entry})),
                "entry-artifacts-per-node-cap");
  }

  SECTION("child artifacts retain the per-node cap") {
    auto entry = entry_with_children(1);
    entry.children.front().artifacts.clear();
    for (std::size_t i = 0; i < 256U; ++i) {
      entry.children.front().artifacts.push_back(child_artifact(0, i));
    }
    const auto at_cap = biv::manifest::parse(
        bytes_of(as_stub(manifest_json_with({entry}))));
    REQUIRE(at_cap.has_value());
    CHECK(at_cap->agent_sessions.front().stub_member_footprint.size() ==
          257U);
    entry.children.front().artifacts.push_back(child_artifact(0, 256));
    require_cap(as_stub(manifest_json_with({entry})),
                "children-artifacts-per-node-cap");
  }

  SECTION("the entry total cap includes entry and child artifacts") {
    const auto at_cap = biv::manifest::parse(bytes_of(as_stub(
        manifest_json_with({entry_with_total_artifacts(4096)}))));
    REQUIRE(at_cap.has_value());
    CHECK(at_cap->agent_sessions.front().stub_member_footprint.size() ==
          4096U);
    require_cap(as_stub(manifest_json_with({entry_with_total_artifacts(4097)})),
                "entry-artifacts-total-cap");
  }
}

TEST_CASE("Manifest reader enforces the complete parent-edge tree contract") {
  constexpr std::string_view parent_edge =
      "\"parent_id\": \"019f-bbbb\",";
  const auto base = manifest_json_with_parent_edge(2);

  const auto direct = biv::manifest::parse(
      bytes_of(manifest_json_with({codex_session_entry()})));
  REQUIRE(direct.has_value());
  REQUIRE(direct->agent_sessions.front().children.size() == 1U);
  CHECK_FALSE(
      direct->agent_sessions.front().children.front().parent_id.has_value());

  const auto require_refused = [](const std::string& json) {
    const auto parsed = biv::manifest::parse(bytes_of(json));
    REQUIRE_FALSE(parsed.has_value());
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
  };

  SECTION("explicit primary parent is not a second encoding of absence") {
    require_refused(replace_once(
        base, parent_edge, "\"parent_id\": \"019f-aaaa\","));
  }
  SECTION("parent must name another member of the same entry") {
    require_refused(replace_once(
        base, parent_edge, "\"parent_id\": \"019f-dddd\","));
  }
  SECTION("child ids are unique") {
    require_refused(replace_once(
        base, "\"original_id\": \"019f-cccc\"," ,
        "\"original_id\": \"019f-bbbb\","));
  }
  SECTION("child id cannot collide with the primary") {
    require_refused(replace_once(
        base, "\"original_id\": \"019f-cccc\"," ,
        "\"original_id\": \"019f-aaaa\","));
  }
  SECTION("self loops are refused") {
    require_refused(replace_once(
        base, parent_edge, "\"parent_id\": \"019f-cccc\","));
  }
  SECTION("longer cycles are refused by an iterative walk") {
    auto cycle = replace_once(
        base, "\"original_id\": \"019f-bbbb\"," ,
        "\"original_id\": \"019f-bbbb\",\n"
        "        \"parent_id\": \"019f-cccc\",");
    require_refused(cycle);
  }
  SECTION("declared children carry at least one artifact") {
    require_refused(replace_once(
        base, "\"agents/codex/019f-cccc.jsonl\"", ""));
  }
  SECTION("present null is refused rather than aliased to absence") {
    require_refused(
        replace_once(base, parent_edge, "\"parent_id\": null,"));
  }
  SECTION("duplicate parent_id is refused before first-wins access") {
    require_refused(replace_once(
        base, parent_edge,
        "\"parent_id\": \"019f-bbbb\",\n"
        "        \"parent_id\": \"019f-bbbb\","));
  }
  SECTION("duplicate original_id is refused before first-wins access") {
    require_refused(replace_once(
        base, "\"original_id\": \"019f-bbbb\"," ,
        "\"original_id\": \"019f-bbbb\",\n"
        "        \"original_id\": \"019f-bbbb\","));
  }
  SECTION("duplicate artifacts is refused before first-wins access") {
    auto duplicate_artifacts = base;
    const auto child_pos =
        duplicate_artifacts.find("\"original_id\": \"019f-bbbb\"");
    REQUIRE(child_pos != std::string::npos);
    const auto artifacts_pos =
        duplicate_artifacts.find("\"artifacts\":", child_pos);
    REQUIRE(artifacts_pos != std::string::npos);
    duplicate_artifacts.insert(artifacts_pos, "\"artifacts\": [],\n        ");
    require_refused(duplicate_artifacts);
  }
}

TEST_CASE("Manifest reader enforces all four per-entry graph caps") {
  constexpr std::string_view primary_id = "019f-aaaa";
  const auto require_cap_refused = [primary_id](const std::string& json,
                                                 const std::string_view cap) {
    const auto parsed = biv::manifest::parse(bytes_of(json));
    REQUIRE_FALSE(parsed.has_value());
    CHECK(parsed.error().kind == biv::ErrKind::ParseError);
    CHECK(parsed.error().detail.find(cap) != std::string::npos);
    CHECK(parsed.error().detail.find(primary_id) != std::string::npos);
  };

  SECTION("node cap accepts 1024 and short-circuits on the 1025th element") {
    const auto at_cap = biv::manifest::parse(
        bytes_of(manifest_json_with({entry_with_children(1024)})));
    REQUIRE(at_cap.has_value());
    REQUIRE(at_cap->agent_sessions.front().children.size() == 1024U);

    auto over_cap = manifest_json_with({entry_with_children(1025)});
    over_cap = replace_once(std::move(over_cap), child_artifact(1024, 0),
                            "../must-not-be-read");
    require_cap_refused(over_cap, "children-node-cap");
  }

  SECTION("parent depth accepts 64 and refuses 65") {
    const auto at_cap = biv::manifest::parse(
        bytes_of(manifest_json_with_parent_chain(64)));
    REQUIRE(at_cap.has_value());
    require_cap_refused(manifest_json_with_parent_chain(65),
                        "children-depth-cap");
  }

  SECTION("artifacts per child accepts 256 and refuses 257") {
    auto at_cap_entry = entry_with_children(1);
    at_cap_entry.children.front().artifacts.clear();
    for (std::size_t i = 0; i < 256U; ++i) {
      at_cap_entry.children.front().artifacts.push_back(child_artifact(0, i));
    }
    const auto at_cap = biv::manifest::parse(
        bytes_of(manifest_json_with({at_cap_entry})));
    REQUIRE(at_cap.has_value());

    auto over_cap_entry = at_cap_entry;
    over_cap_entry.children.front().artifacts.push_back(child_artifact(0, 256));
    require_cap_refused(manifest_json_with({over_cap_entry}),
                        "children-artifacts-per-node-cap");
  }

  SECTION("total artifacts accepts 4096 and refuses 4097") {
    const auto at_cap = biv::manifest::parse(
        bytes_of(manifest_json_with({entry_with_total_artifacts(4096)})));
    REQUIRE(at_cap.has_value());
    require_cap_refused(
        manifest_json_with({entry_with_total_artifacts(4097)}),
        "entry-artifacts-total-cap");
  }
}

TEST_CASE("Manifest writer emits only non-primary parent edges and bumps schema conditionally") {
  auto transitive = codex_session_entry();
  transitive.children.push_back(
      {.original_id = "019f-cccc",
       .artifacts = {"agents/codex/019f-cccc.jsonl"},
       .parent_id = "019f-bbbb"});
  transitive.entry_schema = 1;

  const auto transitive_json = manifest_json_with({transitive});
  CHECK(transitive_json.find("\"parent_id\": \"019f-bbbb\"") !=
        std::string::npos);
  CHECK(transitive_json.find("\"entry_schema\": 2") != std::string::npos);
  const auto transitive_round_trip =
      biv::manifest::parse(bytes_of(transitive_json));
  REQUIRE(transitive_round_trip.has_value());
  REQUIRE(transitive_round_trip->agent_sessions.front().children.size() == 2U);
  CHECK(transitive_round_trip->agent_sessions.front().children.back().parent_id ==
        std::optional<std::string>{"019f-bbbb"});

  auto direct = codex_session_entry();
  direct.children.front().parent_id = direct.original_session_ids.primary;
  direct.entry_schema = 2;
  const auto direct_json = manifest_json_with({direct});
  CHECK(direct_json.find("\"parent_id\"") == std::string::npos);
  CHECK(direct_json.find("\"entry_schema\": 1") != std::string::npos);
  const auto direct_round_trip = biv::manifest::parse(bytes_of(direct_json));
  REQUIRE(direct_round_trip.has_value());
  REQUIRE(direct_round_trip->agent_sessions.front().children.size() == 1U);
  CHECK_FALSE(
      direct_round_trip->agent_sessions.front().children.front().parent_id.has_value());
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
