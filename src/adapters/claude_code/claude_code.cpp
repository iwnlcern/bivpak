#include "adapters/claude_code/claude_code.hpp"

#include <algorithm>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace biv::adapters {

namespace {

namespace fs = std::filesystem;

struct TranscriptFacts {
  std::optional<std::string> cwd;
  std::optional<std::string> session_id;
  std::optional<std::string> version;
};

struct LiveFacts {
  bool live{false};
  std::optional<std::string> version;
};

struct ArtifactRef {
  fs::path source;
  std::string image_path;
};

std::optional<std::string> object_string(simdjson::dom::object object, const std::string_view key) {
  std::string_view value;
  if (const auto error = object.at_key(key).get(value); error) {
    return std::nullopt;
  }
  return std::string{value};
}

std::string discovery_tier_string(const DiscoveryTier tier) {
  switch (tier) {
    case DiscoveryTier::env:
      return "env";
    case DiscoveryTier::defaults:
      return "default";
    case DiscoveryTier::config:
      return "config";
    case DiscoveryTier::explicit_flag:
      return "flag";
  }
  return "default";
}

manifest::PathFlavor path_flavor_for(const std::string_view path) {
  if (path.size() >= 7 && path.starts_with("/mnt/") && path.at(6) == '/') {
    return manifest::PathFlavor::wsl;
  }
  if (path.size() >= 3 && path.at(1) == ':' && (path.at(2) == '\\' || path.at(2) == '/')) {
    return manifest::PathFlavor::windows;
  }
  return manifest::PathFlavor::posix;
}

std::string ascii_lower(std::string value) {
  for (char& character : value) {
    if (character >= 'A' && character <= 'Z') {
      character = static_cast<char>(character - 'A' + 'a');
    }
  }
  return value;
}

std::string normalized_key_for(std::string path) {
  if (path_flavor_for(path) == manifest::PathFlavor::wsl) {
    return ascii_lower(std::move(path));
  }
  return path;
}

std::string trimmed_source_root(const fs::path& source_root) {
  std::string source = source_root.generic_string();
  while (source.size() > 1 && source.ends_with('/')) {
    source.pop_back();
  }
  return source;
}

bool cwd_matches_source(std::string cwd, const fs::path& source_root) {
  std::string source = trimmed_source_root(source_root);
  if (path_flavor_for(cwd) == manifest::PathFlavor::wsl && path_flavor_for(source) == manifest::PathFlavor::wsl) {
    cwd = ascii_lower(std::move(cwd));
    source = ascii_lower(std::move(source));
  }
  return cwd == source || cwd.starts_with(source + '/');
}

bool ascii_alnum(const char value) {
  return (value >= '0' && value <= '9') || (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

std::string project_key_for_path(const fs::path& path) {
  std::string key = path.generic_string();
  for (char& value : key) {
    if (!ascii_alnum(value)) {
      value = '-';
    }
  }
  return key;
}

std::optional<simdjson::dom::object> parse_json_object(simdjson::dom::parser& parser,
                                                       simdjson::padded_string& padded) {
  simdjson::dom::element root;
  if (const auto error = parser.parse(padded).get(root); error) {
    return std::nullopt;
  }
  simdjson::dom::object object;
  if (const auto error = root.get(object); error) {
    return std::nullopt;
  }
  return object;
}

TranscriptFacts inspect_transcript(const fs::path& transcript) {
  TranscriptFacts facts;
  std::ifstream input{transcript};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object.has_value()) {
      continue;
    }
    if (!facts.session_id.has_value()) {
      facts.session_id = object_string(*object, "sessionId");
    }
    if (!facts.version.has_value()) {
      facts.version = object_string(*object, "version");
    }
    if (!facts.cwd.has_value()) {
      facts.cwd = object_string(*object, "cwd");
    }
  }
  return facts;
}

bool terminal_status(const std::string_view status) {
  return status == "completed" || status == "exited" || status == "stopped" || status == "failed";
}

LiveFacts live_facts_for(const fs::path& store_root, const std::string_view session_id) {
  LiveFacts facts;
  const auto sessions_dir = store_root / "sessions";
  if (!fs::exists(sessions_dir)) {
    return facts;
  }
  for (const auto& entry : fs::directory_iterator(sessions_dir)) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }
    std::ifstream input{entry.path()};
    std::string json{std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
    simdjson::padded_string padded{json};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object.has_value()) {
      continue;
    }
    auto candidate = object_string(*object, "sessionId");
    if (!candidate.has_value() || *candidate != session_id) {
      continue;
    }
    auto status = object_string(*object, "status");
    facts.live = !status.has_value() || !terminal_status(*status);
    facts.version = object_string(*object, "version");
  }
  return facts;
}

std::vector<ArtifactRef> collect_subtree_artifacts(const fs::path& session_dir, const std::string_view session_id) {
  std::vector<ArtifactRef> artifacts;
  if (!fs::exists(session_dir)) {
    return artifacts;
  }
  for (const auto& entry : fs::recursive_directory_iterator(session_dir)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    std::string artifact = "agents/claude-code/";
    artifact += session_id;
    artifact += '/';
    artifact += fs::relative(entry.path(), session_dir).generic_string();
    artifacts.push_back(ArtifactRef{.source = entry.path(), .image_path = std::move(artifact)});
  }
  std::ranges::sort(artifacts, {}, &ArtifactRef::image_path);
  return artifacts;
}

std::vector<std::string> child_ids_for(const fs::path& session_dir) {
  std::vector<std::string> child_ids;
  const auto subagents = session_dir / "subagents";
  if (!fs::exists(subagents)) {
    return child_ids;
  }
  for (const auto& entry : fs::directory_iterator(subagents)) {
    if (entry.is_regular_file() && entry.path().extension() == ".jsonl") {
      child_ids.push_back(entry.path().stem().string());
    }
  }
  std::ranges::sort(child_ids);
  return child_ids;
}

const Inventory& claude_inventory() {
  static const Inventory inventory{
      .collect = {ArtifactClass{.name = "project-transcripts", .globs = {"projects/*/*.jsonl"}}},
      .rewrite = {ArtifactClass{.name = "jsonl-session-fields", .globs = {"agents/claude-code/**/*.jsonl"}}},
      .never_collect = {".credentials.json",
                        "settings.json",
                        "settings.local.json",
                        "history.jsonl",
                        "shell-snapshots",
                        "memory",
                        "file-history",
                        "tasks",
                        "session-env"},
      .never_rewrite = {".meta.json"},
      .caveat_facts = {.env_var = "CLAUDE_CONFIG_DIR",
                       .relocated_contents = {"projects"},
                       .login_flow_owner = "claude-code",
                       .notes = {}}};
  return inventory;
}

class ClaudeCodeAdapter final : public AgentAdapter {
 public:
  std::string_view id() const override { return "claude-code"; }

  expected<std::vector<Store>> discover(const Env& env) const override {
    std::vector<Store> stores;
    if (env.getenv) {
      auto configured = env.getenv("CLAUDE_CONFIG_DIR");
      if (configured.has_value() && fs::exists(*configured)) {
        const fs::path root{*configured};
        stores.push_back(Store{.root = root,
                               .locators = {StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
                               .tier = DiscoveryTier::env,
                               .archived = false});
        return stores;
      }
    }

    const auto root = env.home / ".claude";
    if (fs::exists(root)) {
      stores.push_back(Store{.root = root,
                             .locators = {StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
                             .tier = DiscoveryTier::defaults,
                             .archived = false});
    }
    return stores;
  }

  const Inventory& state_inventory() const override { return claude_inventory(); }

  expected<CollectReport> collect(const std::filesystem::path& source_root,
                                  std::span<const Store> stores) const override {
    try {
      CollectReport report;
      for (const auto& store : stores) {
        const auto projects_dir = store.root / "projects";
        if (!fs::exists(projects_dir)) {
          continue;
        }
        for (const auto& project_dir : fs::directory_iterator(projects_dir)) {
          if (!project_dir.is_directory()) {
            continue;
          }
          const bool project_key_matches_source =
              project_dir.path().filename().generic_string() == project_key_for_path(source_root);
          for (const auto& entry : fs::directory_iterator(project_dir.path())) {
            if (!entry.is_regular_file() || entry.path().extension() != ".jsonl") {
              continue;
            }
            auto facts = inspect_transcript(entry.path());
            if (!facts.cwd.has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!cwd_matches_source(*facts.cwd, source_root)) {
              continue;
            }
            const std::string session_id = facts.session_id.value_or(entry.path().stem().string());
            const auto session_dir = project_dir.path() / session_id;
            auto live = live_facts_for(store.root, session_id);
            std::vector<std::string> artifacts;
            std::vector<fs::path> artifact_sources;
            artifacts.push_back("agents/claude-code/" + session_id + ".jsonl");
            artifact_sources.push_back(entry.path());
            auto subtree_artifacts = collect_subtree_artifacts(session_dir, session_id);
            for (auto& artifact : subtree_artifacts) {
              artifact_sources.push_back(std::move(artifact.source));
              artifacts.push_back(std::move(artifact.image_path));
            }

            report.sessions.push_back(SessionRecord{
                .agent = "claude-code",
                .original_session_id = session_id,
                .child_ids = child_ids_for(session_dir),
                .original_path = *facts.cwd,
                .normalized_path_key = normalized_key_for(*facts.cwd),
                .path_flavor = path_flavor_for(*facts.cwd),
                .provenance = {.store_root = store.root.generic_string(),
                               .locator = "projects",
                               .discovery_tier = discovery_tier_string(store.tier),
                               .archived = store.archived},
                .artifacts = std::move(artifacts),
                .artifact_sources = std::move(artifact_sources),
                .agent_version_at_pack = facts.version.value_or(live.version.value_or("unknown")),
                .live_at_pack = live.live});
          }
        }
      }
      return report;
    } catch (const fs::filesystem_error& error) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, error.what()});
    }
  }

  expected<InstallResult> install(const InstallTarget& /*target*/,
                                  Consent /*consent*/,
                                  std::span<const manifest::AgentSessionEntry> /*records*/) const override {
    return InstallResult{};
  }

  expected<RewriteReport> rewrite(std::span<const SessionRecord> /*records*/,
                                  const InstallTarget& /*target*/) const override {
    return RewriteReport{};
  }

  Capabilities capabilities(const Host& /*host*/) const override {
    return Capabilities{.agent_version = "unknown",
                        .validated_range = "2.1.x",
                        .verdict = Capabilities::Verdict::unvalidated_host,
                        .long_path_keys_pinned = false,
                        .per_verb = {.collect = false, .install = false, .rewrite = false}};
  }
};

}  // namespace

const AgentAdapter& claude_code_adapter() {
  static const ClaudeCodeAdapter adapter;
  return adapter;
}

}  // namespace biv::adapters
