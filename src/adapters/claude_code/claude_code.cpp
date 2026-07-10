#include "adapters/claude_code/claude_code.hpp"

#include <algorithm>
#include <fstream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include "adapters/rewrite_common.hpp"

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
    if (facts.cwd.has_value() && facts.session_id.has_value() &&
        facts.version.has_value()) {
      break;
    }
  }
  return facts;
}

bool terminal_status(const std::string_view status) {
  return status == "completed" || status == "exited" || status == "stopped" || status == "failed";
}

std::map<std::string, LiveFacts> live_facts_by_id(const fs::path& store_root) {
  std::map<std::string, LiveFacts> facts;
  const auto sessions_dir = store_root / "sessions";
  std::error_code ec;
  if (!fs::exists(sessions_dir, ec)) {
    return facts;
  }
  for (fs::directory_iterator it{sessions_dir, ec}, end; !ec && it != end;
       it.increment(ec)) {
    const auto& entry = *it;
    if (!entry.is_regular_file(ec) || entry.path().extension() != ".json") {
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
    if (!candidate.has_value()) {
      continue;
    }
    auto status = object_string(*object, "status");
    facts[*candidate] =
        LiveFacts{.live = !status.has_value() || !terminal_status(*status),
                  .version = object_string(*object, "version")};
  }
  return facts;
}

bool lexically_inside(const fs::path& candidate, const fs::path& root) {
  const auto rel =
      candidate.lexically_normal().lexically_relative(root.lexically_normal());
  if (rel.empty()) {
    return false;
  }
  const auto begin = rel.begin();
  return begin != rel.end() && *begin != "..";
}

std::vector<ArtifactRef> collect_subtree_artifacts(
    const fs::path& session_dir, const std::string_view session_id) {
  std::vector<ArtifactRef> artifacts;
  std::error_code ec;
  if (!fs::exists(session_dir, ec)) {
    return artifacts;
  }
  const auto canonical_session = fs::weakly_canonical(session_dir, ec);
  if (ec) {
    return artifacts;
  }
  for (fs::recursive_directory_iterator
           it{session_dir, fs::directory_options::none, ec},
       end;
       !ec && it != end; it.increment(ec)) {
    const auto& entry = *it;
    if (entry.is_symlink(ec) || !entry.is_regular_file(ec)) {
      continue;
    }
    const auto canonical_entry = fs::weakly_canonical(entry.path(), ec);
    if (ec || !lexically_inside(canonical_entry, canonical_session)) {
      ec.clear();
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
  std::error_code ec;
  if (!fs::exists(subagents, ec)) {
    return child_ids;
  }
  for (fs::directory_iterator it{subagents, ec}, end; !ec && it != end;
       it.increment(ec)) {
    const auto& entry = *it;
    if (!entry.is_symlink(ec) && entry.is_regular_file(ec) &&
        entry.path().extension() == ".jsonl") {
      child_ids.push_back(entry.path().stem().string());
    }
  }
  std::ranges::sort(child_ids);
  return child_ids;
}

const Inventory& claude_inventory() {
  static const Inventory inventory{
      .collect = {ArtifactClass{.name = "project-transcripts",
                                .globs = {"projects/*/*.jsonl"}}},
      .rewrite = {ArtifactClass{.name = "jsonl-session-fields",
                                .globs = {"agents/claude-code/**/*.jsonl"}}},
      .never_collect = {".credentials.json", ".claude.json", "settings.json",
                        "settings.local.json", "settings*.json",
                        "history.jsonl", "shell-snapshots", "memory",
                        "file-history", "tasks", "session-env"},
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
    std::error_code ec;
    if (env.getenv) {
      auto configured = env.getenv("CLAUDE_CONFIG_DIR");
      if (configured.has_value() && fs::exists(*configured, ec)) {
        const fs::path root{*configured};
        stores.push_back(Store{.root = root,
                               .locators = {StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
                               .tier = DiscoveryTier::env,
                               .archived = false});
        return stores;
      }
    }

    const auto root = env.home / ".claude";
    if (fs::exists(root, ec)) {
      stores.push_back(
          Store{.root = root,
                .locators = {StoreLocator{.kind = "sessions_root",
                                          .path = root / "projects"}},
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
        std::error_code ec;
        if (!fs::exists(projects_dir, ec)) {
          continue;
        }
        const auto live_by_id = live_facts_by_id(store.root);
        for (fs::directory_iterator project_it{projects_dir, ec}, project_end;
             !ec && project_it != project_end; project_it.increment(ec)) {
          const auto& project_dir = *project_it;
          if (!project_dir.is_directory(ec)) {
            continue;
          }
          const bool project_key_matches_source =
              project_dir.path().filename().generic_string() ==
              project_key_for_path(source_root);
          for (fs::directory_iterator entry_it{project_dir.path(), ec},
               entry_end;
               !ec && entry_it != entry_end; entry_it.increment(ec)) {
            const auto& entry = *entry_it;
            if (!entry.is_regular_file(ec) ||
                entry.path().extension() != ".jsonl") {
              continue;
            }
            auto facts = inspect_transcript(entry.path());
            if (!facts.cwd.has_value()) {
              if (project_key_matches_source) {
                report.no_cwd_record.push_back(entry.path().generic_string());
              }
              continue;
            }
            if (!rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = *facts.cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
            const std::string session_id = facts.session_id.value_or(entry.path().stem().string());
            const auto session_dir = project_dir.path() / session_id;
            const auto live_found = live_by_id.find(session_id);
            auto live = live_found == live_by_id.end() ? LiveFacts{}
                                                       : live_found->second;
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
                .parent_id = std::nullopt,
                .child_ids = child_ids_for(session_dir),
                .original_path = *facts.cwd,
                .normalized_path_key = rewrite::normalized_path_key(*facts.cwd),
                .normalization_scheme = "claude-cwd/v1",
                .path_flavor = rewrite::path_flavor_for(*facts.cwd),
                .provenance = {.store_root = store.root.generic_string(),
                               .locator = "sessions_root",
                               .discovery_tier =
                                   discovery_tier_string(store.tier),
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

  expected<InstallResult> install(const InstallTarget& target,
                                  Consent consent,
                                  std::span<const manifest::AgentSessionEntry> records) const override {
    return claude_code_install(target, consent, records);
  }

  expected<RewriteReport> rewrite(std::span<const SessionRecord> records, const InstallTarget& target) const override {
    return claude_code_rewrite(records, target);
  }

  Capabilities capabilities(const Host& host) const override {
    return claude_code_capabilities(host);
  }
};

}  // namespace

const AgentAdapter& claude_code_adapter() {
  static const ClaudeCodeAdapter adapter;
  return adapter;
}

}  // namespace biv::adapters
