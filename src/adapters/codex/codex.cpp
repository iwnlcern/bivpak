#include "adapters/codex/codex.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

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

struct RolloutFacts {
  std::optional<std::string> id;
  std::optional<std::string> cwd;
  std::optional<std::string> cli_version;
  std::optional<std::string> parent_id;
  std::string newest_timestamp;
};

struct Candidate {
  Store store;
  fs::path source;
  std::string id;
  std::string cwd;
  std::string normalized_path_key;
  manifest::PathFlavor path_flavor{manifest::PathFlavor::posix};
  std::string cli_version;
  std::optional<std::string> parent_id;
  std::string newest_timestamp;
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

std::string ascii_lower(std::string value) {
  for (char& character : value) {
    if (character >= 'A' && character <= 'Z') {
      character = static_cast<char>(character - 'A' + 'a');
    }
  }
  return value;
}

manifest::PathFlavor path_flavor_for(const std::string_view path) {
  if (path.size() >= 7 && path.starts_with("/mnt/") && path.at(6) == '/' && ascii_alpha(path.at(5))) {
    return manifest::PathFlavor::wsl;
  }
  if (path.size() >= 3 && ascii_alpha(path.at(0)) && path.at(1) == ':' &&
      (path.at(2) == '\\' || path.at(2) == '/')) {
    return manifest::PathFlavor::windows;
  }
  return manifest::PathFlavor::posix;
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

std::optional<simdjson::dom::object> parse_json_object(simdjson::dom::parser& parser,
                                                       simdjson::padded_string& padded) {
  simdjson::dom::element root;
  if (parser.parse(padded).get(root)) {
    return std::nullopt;
  }
  simdjson::dom::object object;
  if (root.get(object)) {
    return std::nullopt;
  }
  return object;
}

std::optional<std::string> object_string(simdjson::dom::object object, std::string_view key) {
  std::string_view value;
  if (object.at_key(key).get(value)) {
    return std::nullopt;
  }
  return std::string{value};
}

std::optional<simdjson::dom::object> object_object(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::object value;
  if (object.at_key(key).get(value)) {
    return std::nullopt;
  }
  return value;
}

std::optional<std::string> nested_parent_id(simdjson::dom::object payload) {
  auto source = object_object(payload, "source");
  if (!source) {
    return std::nullopt;
  }
  auto subagent = object_object(*source, "subagent");
  if (!subagent) {
    return std::nullopt;
  }
  auto thread_spawn = object_object(*subagent, "thread_spawn");
  if (!thread_spawn) {
    return std::nullopt;
  }
  return object_string(*thread_spawn, "parent_thread_id");
}

RolloutFacts inspect_rollout(const fs::path& rollout) {
  RolloutFacts facts;
  std::ifstream input{rollout};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
    }
    if (auto timestamp = object_string(*object, "timestamp"); timestamp.has_value() && *timestamp > facts.newest_timestamp) {
      facts.newest_timestamp = *timestamp;
    }
    auto type = object_string(*object, "type");
    if (!type || *type != "session_meta") {
      continue;
    }
    auto payload = object_object(*object, "payload");
    if (!payload) {
      continue;
    }
    if (!facts.id.has_value()) {
      facts.id = object_string(*payload, "id");
      if (!facts.id.has_value()) {
        facts.id = object_string(*payload, "session_id");
      }
    }
    if (!facts.cwd.has_value()) {
      facts.cwd = object_string(*payload, "cwd");
    }
    if (!facts.cli_version.has_value()) {
      facts.cli_version = object_string(*payload, "cli_version");
    }
    if (!facts.parent_id.has_value()) {
      facts.parent_id = object_string(*payload, "parent_thread_id");
      if (!facts.parent_id.has_value()) {
        facts.parent_id = nested_parent_id(*payload);
      }
    }
  }
  return facts;
}

std::vector<fs::path> rollout_paths(const fs::path& sessions_dir) {
  std::vector<fs::path> paths;
  if (!fs::exists(sessions_dir)) {
    return paths;
  }
  for (const auto& entry : fs::recursive_directory_iterator(sessions_dir)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    const auto filename = entry.path().filename().generic_string();
    if (filename.starts_with("rollout-") &&
        (entry.path().extension() == ".jsonl" || filename.ends_with(".jsonl.zst"))) {
      paths.push_back(entry.path());
    }
  }
  std::ranges::sort(paths);
  return paths;
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

int tier_rank(const DiscoveryTier tier) {
  switch (tier) {
    case DiscoveryTier::explicit_flag:
      return 0;
    case DiscoveryTier::env:
      return 1;
    case DiscoveryTier::config:
      return 2;
    case DiscoveryTier::defaults:
      return 3;
  }
  return 3;
}

bool better_candidate(const Candidate& candidate, const Candidate& current) {
  if (candidate.newest_timestamp != current.newest_timestamp) {
    return candidate.newest_timestamp > current.newest_timestamp;
  }
  if (tier_rank(candidate.store.tier) != tier_rank(current.store.tier)) {
    return tier_rank(candidate.store.tier) < tier_rank(current.store.tier);
  }
  return candidate.source.generic_string() < current.source.generic_string();
}

std::string artifact_for(std::string_view id) {
  return "agents/codex/" + std::string{id} + ".jsonl";
}

SessionRecord session_for(const Candidate& candidate, const std::vector<Candidate>& children) {
  std::vector<std::string> child_ids;
  std::vector<std::string> artifacts{artifact_for(candidate.id)};
  std::vector<fs::path> artifact_sources{candidate.source};
  for (const auto& child : children) {
    child_ids.push_back(child.id);
    artifacts.push_back(artifact_for(child.id));
    artifact_sources.push_back(child.source);
  }
  std::ranges::sort(child_ids);
  return SessionRecord{.agent = "codex",
                       .original_session_id = candidate.id,
                       .child_ids = std::move(child_ids),
                       .original_path = candidate.cwd,
                       .normalized_path_key = candidate.normalized_path_key,
                       .normalization_scheme = "codex-cwd/v1",
                       .path_flavor = candidate.path_flavor,
                       .provenance = {.store_root = candidate.store.root.generic_string(),
                                      .locator = "sessions",
                                      .discovery_tier = discovery_tier_string(candidate.store.tier),
                                      .archived = candidate.store.archived},
                       .artifacts = std::move(artifacts),
                       .artifact_sources = std::move(artifact_sources),
                       .agent_version_at_pack = candidate.cli_version,
                       .live_at_pack = false};
}

const Inventory& codex_inventory() {
  static const Inventory inventory{
      .collect = {ArtifactClass{.name = "rollouts", .globs = {"sessions/**/rollout-*.jsonl"}}},
      .rewrite = {ArtifactClass{.name = "jsonl-session-fields", .globs = {"agents/codex/*.jsonl"}}},
      .never_collect = {"auth.json",
                        "config.toml",
                        "history.jsonl",
                        "state_5.sqlite",
                        "state_5.sqlite-wal",
                        "state_5.sqlite-shm",
                        "session_index.jsonl",
                        "shell_snapshots",
                        "goals_1.sqlite",
                        "logs_2.sqlite",
                        "memories_1.sqlite"},
      .never_rewrite = {},
      .caveat_facts = {.env_var = "CODEX_HOME",
                       .relocated_contents = {"sessions"},
                       .login_flow_owner = "codex",
                       .notes = {}}};
  return inventory;
}

class CodexAdapter final : public AgentAdapter {
 public:
  std::string_view id() const override { return "codex"; }

  expected<std::vector<Store>> discover(const Env& env) const override {
    std::vector<Store> stores;
    if (env.getenv) {
      auto configured = env.getenv("CODEX_HOME");
      if (configured.has_value() && fs::exists(*configured)) {
        const fs::path root{*configured};
        stores.push_back(Store{.root = root,
                               .locators = {StoreLocator{.kind = "sessions_root", .path = root / "sessions"}},
                               .tier = DiscoveryTier::env,
                               .archived = false});
        return stores;
      }
    }

    const auto root = env.home / ".codex";
    if (fs::exists(root)) {
      stores.push_back(Store{.root = root,
                             .locators = {StoreLocator{.kind = "sessions_root", .path = root / "sessions"}},
                             .tier = DiscoveryTier::defaults,
                             .archived = false});
    }
    return stores;
  }

  const Inventory& state_inventory() const override { return codex_inventory(); }

  expected<CollectReport> collect(const fs::path& source_root, std::span<const Store> stores) const override {
    try {
      CollectReport report;
      std::map<std::string, std::vector<Candidate>> grouped;
      for (const auto& store : stores) {
        if (fs::exists(store.root / "state_5.sqlite")) {
          report.warnings.push_back("CodexDbEnrichmentSkipped:" + (store.root / "state_5.sqlite").generic_string());
        }
        for (const auto& path : rollout_paths(store.root / "sessions")) {
          auto facts = inspect_rollout(path);
          if (!facts.id || !facts.cwd || !cwd_matches_source(*facts.cwd, source_root)) {
            continue;
          }
          grouped[*facts.id].push_back(Candidate{.store = store,
                                                 .source = path,
                                                 .id = *facts.id,
                                                 .cwd = *facts.cwd,
                                                 .normalized_path_key = normalized_key_for(*facts.cwd),
                                                 .path_flavor = path_flavor_for(*facts.cwd),
                                                 .cli_version = facts.cli_version.value_or("unknown"),
                                                 .parent_id = std::move(facts.parent_id),
                                                 .newest_timestamp = std::move(facts.newest_timestamp)});
        }
      }

      std::map<std::string, Candidate> winners;
      for (auto& [id, candidates] : grouped) {
        std::set<std::string> roots;
        for (const auto& candidate : candidates) {
          roots.insert(candidate.store.root.generic_string());
        }
        if (roots.size() > 1U) {
          report.warnings.push_back("SessionDuplicateStorePending:" + id);
          continue;
        }
        auto best = candidates.front();
        for (const auto& candidate : candidates) {
          if (better_candidate(candidate, best)) {
            best = candidate;
          }
        }
        winners.emplace(id, std::move(best));
      }

      std::set<std::string> child_ids;
      std::map<std::string, std::vector<Candidate>> children_by_parent;
      for (const auto& [id, candidate] : winners) {
        if (candidate.parent_id.has_value() && winners.contains(*candidate.parent_id)) {
          children_by_parent[*candidate.parent_id].push_back(candidate);
          child_ids.insert(id);
        }
      }
      for (auto& [parent, children] : children_by_parent) {
        std::ranges::sort(children, {}, &Candidate::id);
      }
      for (const auto& [id, candidate] : winners) {
        if (child_ids.contains(id)) {
          continue;
        }
        report.sessions.push_back(session_for(candidate, children_by_parent[id]));
      }
      std::ranges::sort(report.sessions, {}, &SessionRecord::original_session_id);
      return report;
    } catch (const fs::filesystem_error& error) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, error.what()});
    }
  }

  expected<InstallResult> install(const InstallTarget& target,
                                  Consent consent,
                                  std::span<const manifest::AgentSessionEntry> records) const override {
    return codex_install(target, consent, records);
  }

  expected<RewriteReport> rewrite(std::span<const SessionRecord> records, const InstallTarget& target) const override {
    return codex_rewrite(records, target);
  }

  Capabilities capabilities(const Host& host) const override {
    return codex_capabilities(host);
  }
};

}  // namespace

const AgentAdapter& codex_adapter() {
  static const CodexAdapter adapter;
  return adapter;
}

}  // namespace biv::adapters
