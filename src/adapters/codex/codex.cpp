#include "adapters/codex/codex.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "adapters/rewrite_common.hpp"
#include "adapters/secure_io.hpp"

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
  fs::file_time_type mtime{};
};

struct Candidate {
  Store store;
  SessionRecord::ArtifactSource source;
  std::string id;
  std::string cwd;
  std::string normalized_path_key;
  manifest::PathFlavor path_flavor{manifest::PathFlavor::posix};
  std::string cli_version;
  std::optional<std::string> parent_id;
  std::string newest_timestamp;
  fs::file_time_type mtime{};
};

expected<SessionRecord::ArtifactSource> open_artifact_source(const fs::path& path) {
  auto handle = secure_io::open_read_no_follow(path);
  if (!handle) {
    return std::unexpected(handle.error());
  }
  return SessionRecord::ArtifactSource{
      .path = path,
      .size = handle->size(),
      .stream = [handle = std::move(*handle)](
                    const secure_io::ByteSink& sink) { return handle.stream(sink); }};
}

std::optional<simdjson::dom::object> parse_json_object(
    simdjson::dom::parser& parser, simdjson::padded_string& padded) {
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

expected<std::string> source_text(const SessionRecord::ArtifactSource& source) {
  std::string text;
  text.reserve(static_cast<size_t>(source.size));
  auto read = source.stream(
      [&](const std::span<const std::byte> chunk) -> expected<void> {
        for (const auto byte : chunk) {
          text.push_back(static_cast<char>(byte));
        }
        return {};
      });
  if (!read) {
    return std::unexpected(read.error());
  }
  return text;
}

RolloutFacts inspect_rollout_head(const std::string_view rollout) {
  RolloutFacts facts;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
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
    return facts;
  }
  return facts;
}

std::string newest_rollout_timestamp(const std::string_view rollout) {
  std::string newest;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
    }
    if (auto timestamp = object_string(*object, "timestamp");
        timestamp.has_value() && *timestamp > newest) {
      newest = *timestamp;
    }
  }
  return newest;
}

std::vector<fs::path> rollout_paths(const fs::path& sessions_dir,
                                    std::vector<std::string>& warnings) {
  std::vector<fs::path> paths;
  std::error_code ec;
  if (!fs::exists(sessions_dir, ec)) {
    return paths;
  }
  for (fs::recursive_directory_iterator
           it{sessions_dir, fs::directory_options::none, ec},
       end;
       !ec && it != end; it.increment(ec)) {
    const auto& entry = *it;
    if (entry.is_symlink(ec) || !entry.is_regular_file(ec)) {
      continue;
    }
    const auto filename = entry.path().filename().generic_string();
    if (!filename.starts_with("rollout-")) {
      continue;
    }
    if (filename.ends_with(".jsonl.zst")) {
      warnings.push_back("CompressedRolloutSkipped:" +
                         entry.path().generic_string());
      continue;
    }
    if (entry.path().extension() == ".jsonl") {
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
  if (candidate.mtime != current.mtime) {
    return candidate.mtime > current.mtime;
  }
  if (tier_rank(candidate.store.tier) != tier_rank(current.store.tier)) {
    return tier_rank(candidate.store.tier) < tier_rank(current.store.tier);
  }
  return candidate.source.path.generic_string() <
         current.source.path.generic_string();
}

std::string artifact_for(std::string_view id) {
  return "agents/codex/" + std::string{id} + ".jsonl";
}

SessionRecord session_for(const Candidate& candidate, const std::vector<Candidate>& children) {
  std::vector<std::string> child_ids;
  std::vector<std::string> artifacts{artifact_for(candidate.id)};
  std::vector<SessionRecord::ArtifactSource> artifact_sources{candidate.source};
  for (const auto& child : children) {
    child_ids.push_back(child.id);
    artifacts.push_back(artifact_for(child.id));
    artifact_sources.push_back(child.source);
  }
  std::ranges::sort(child_ids);
  return SessionRecord{
      .agent = "codex",
      .original_session_id = candidate.id,
      .parent_id = candidate.parent_id,
      .child_ids = std::move(child_ids),
      .original_path = candidate.cwd,
      .normalized_path_key = candidate.normalized_path_key,
      .normalization_scheme = "codex-cwd/v1",
      .path_flavor = candidate.path_flavor,
      .provenance = {.store_root = candidate.store.root.generic_string(),
                     .locator = "sessions_root",
                     .discovery_tier =
                         discovery_tier_string(candidate.store.tier),
                     .archived = candidate.store.archived},
      .artifacts = std::move(artifacts),
      .artifact_sources = std::move(artifact_sources),
      .agent_version_at_pack = candidate.cli_version,
      .live_at_pack = false};
}

const Inventory& codex_inventory() {
  static const Inventory inventory = [] {
    Inventory value{
        .collect = {ArtifactClass{.name = "rollouts",
                                  .globs = {"sessions/**/rollout-*.jsonl"}}},
        .rewrite = {ArtifactClass{.name = "jsonl-session-fields",
                                  .globs = {"agents/codex/*.jsonl"}}},
        .never_collect = {"auth.json", "config.toml", "history.jsonl",
                          "installation_id", "state_5.sqlite",
                          "state_5.sqlite-wal", "state_5.sqlite-shm",
                          "session_index.jsonl", "shell_snapshots",
                          "goals_1.sqlite", "logs_2.sqlite", "memories_1.sqlite"},
        .never_rewrite = {},
        .caveat_facts = {.env_var = "CODEX_HOME",
                         .relocated_contents = {},
                         .login_flow_owner = "codex",
                         .notes = {}}};
    value.caveat_facts.relocated_contents.push_back("sessions");
    value.caveat_facts.relocated_contents.insert(
        value.caveat_facts.relocated_contents.end(), value.never_collect.begin(),
        value.never_collect.end());
    return value;
  }();
  return inventory;
}

std::optional<std::string> config_string(const fs::path& path,
                                         const std::string_view wanted_key) {
  std::ifstream input{path};
  std::string line;
  while (std::getline(input, line)) {
    const auto first = line.find_first_not_of(" \t");
    if (first == std::string::npos || line.at(first) == '#') {
      continue;
    }
    const auto equals = line.find('=', first);
    if (equals == std::string::npos) {
      continue;
    }
    auto key_end = line.find_last_not_of(" \t", equals - 1U);
    if (key_end == std::string::npos ||
        std::string_view{line}.substr(first, key_end - first + 1U) != wanted_key) {
      continue;
    }
    const auto value_start = line.find_first_not_of(" \t", equals + 1U);
    if (value_start == std::string::npos || line.at(value_start) != '"') {
      return std::nullopt;
    }
    std::string value;
    bool escaped = false;
    for (std::size_t i = value_start + 1U; i < line.size(); ++i) {
      const char character = line.at(i);
      if (escaped) {
        if (character == '"' || character == '\\') {
          value.push_back(character);
        } else {
          return std::nullopt;
        }
        escaped = false;
      } else if (character == '\\') {
        escaped = true;
      } else if (character == '"') {
        return value;
      } else {
        value.push_back(character);
      }
    }
    return std::nullopt;
  }
  return std::nullopt;
}

class CodexAdapter final : public AgentAdapter {
 public:
  std::string_view id() const override { return "codex"; }

  expected<std::vector<Store>> discover(const Env& env) const override {
    std::vector<Store> stores;
    auto sqlite_locator = [&](const fs::path& root) -> std::optional<StoreLocator> {
      auto configured = env.getenv ? env.getenv("CODEX_SQLITE_HOME")
                                   : std::nullopt;
      if (!configured.has_value()) {
        configured = config_string(root / "config.toml", "sqlite_home");
      }
      if (!configured.has_value()) {
        return std::nullopt;
      }
      std::error_code ec;
      if (!fs::exists(*configured, ec)) {
        return std::nullopt;
      }
      return StoreLocator{.kind = "sqlite_home", .path = fs::path{*configured}};
    };
    auto append_store_set = [&](const fs::path& root, DiscoveryTier tier) {
      std::vector<StoreLocator> locators{
          StoreLocator{.kind = "sessions_root", .path = root / "sessions"}};
      if (auto sqlite = sqlite_locator(root); sqlite.has_value()) {
        locators.push_back(std::move(*sqlite));
      }
      stores.push_back(Store{.root = root,
                             .locators = std::move(locators),
                             .tier = tier,
                             .archived = false});
      std::error_code ec;
      if (fs::exists(root / "archived_sessions", ec)) {
        stores.push_back(Store{
            .root = root,
            .locators = {StoreLocator{.kind = "sessions_root",
                                      .path = root / "archived_sessions"}},
            .tier = tier,
            .archived = true});
      }
    };
    std::error_code ec;
    std::optional<fs::path> env_root;
    if (env.getenv) {
      auto configured = env.getenv("CODEX_HOME");
      if (configured.has_value() && fs::exists(*configured, ec)) {
        env_root = fs::path{*configured};
        append_store_set(*env_root, DiscoveryTier::env);
      }
    }

    const auto root = env.home / ".codex";
    if (fs::exists(root, ec) &&
        (!env_root.has_value() || root.lexically_normal() != env_root->lexically_normal())) {
      append_store_set(root, DiscoveryTier::defaults);
    }
    return stores;
  }

  const Inventory& state_inventory() const override { return codex_inventory(); }

  expected<CollectReport> collect(const fs::path& source_root, std::span<const Store> stores) const override {
    try {
      CollectReport report;
      std::vector<std::pair<std::string, std::string>> db_warnings;
      std::map<std::string, std::vector<Candidate>> grouped;
      for (const auto& store : stores) {
        if (auto valid = secure_io::validate_directory_no_follow(store.root);
            !valid) {
          return std::unexpected(valid.error());
        }
        std::error_code ec;
        for (const auto& locator : store.locators) {
          if (locator.kind == "sqlite_home" &&
              fs::exists(locator.path / "state_5.sqlite", ec)) {
            db_warnings.push_back({
                store.root.generic_string(),
                "CodexDbEnrichmentSkipped:" +
                    (locator.path / "state_5.sqlite").generic_string()});
          }
        }
        if (fs::exists(store.root / "state_5.sqlite", ec) &&
            std::ranges::none_of(store.locators, [](const StoreLocator& locator) {
              return locator.kind == "sqlite_home";
            })) {
          db_warnings.push_back({
              store.root.generic_string(),
              "CodexDbEnrichmentSkipped:" +
                  (store.root / "state_5.sqlite").generic_string()});
        }
        std::vector<fs::path> session_roots;
        for (const auto& locator : store.locators) {
          if (locator.kind == "sessions_root") {
            session_roots.push_back(locator.path);
          }
        }
        if (session_roots.empty()) {
          session_roots.push_back(store.root / "sessions");
        }
        for (const auto& sessions_root : session_roots) {
          if (!fs::exists(sessions_root, ec)) {
            ec.clear();
            continue;
          }
          if (auto valid = secure_io::validate_directory_no_follow(sessions_root);
              !valid) {
            return std::unexpected(valid.error());
          }
          for (const auto& path :
               rollout_paths(sessions_root, report.warnings)) {
            auto source = open_artifact_source(path);
            if (!source) {
              return std::unexpected(source.error());
            }
            auto text = source_text(*source);
            if (!text) {
              return std::unexpected(text.error());
            }
            auto facts = inspect_rollout_head(*text);
            if (!facts.id || !facts.cwd ||
                !rewrite::path_is_same_or_descendant(rewrite::PathMembership{
                    .candidate = *facts.cwd,
                    .root = source_root.generic_string()})) {
              continue;
            }
            const auto mtime = fs::last_write_time(path, ec);
            grouped[*facts.id].push_back(Candidate{
                .store = store,
                .source = std::move(*source),
                .id = *facts.id,
                .cwd = *facts.cwd,
                .normalized_path_key = rewrite::normalized_path_key(*facts.cwd),
                .path_flavor = rewrite::path_flavor_for(*facts.cwd),
                .cli_version = facts.cli_version.value_or("unknown"),
                .parent_id = std::move(facts.parent_id),
                .newest_timestamp = newest_rollout_timestamp(*text),
                .mtime = ec ? fs::file_time_type{} : mtime});
            ec.clear();
          }
        }
      }

      std::map<std::string, Candidate> winners;
      for (auto& [id, candidates] : grouped) {
        std::set<std::string> roots;
        for (const auto& candidate : candidates) {
          roots.insert(candidate.store.root.generic_string());
        }
        if (roots.size() > 1U) {
          report.warnings.push_back("SessionDuplicateStore:" + id);
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
      for (const auto& [store_root, warning] : db_warnings) {
        if (std::ranges::any_of(
                report.sessions, [&](const SessionRecord& session) {
                  return session.provenance.store_root == store_root;
                })) {
          report.warnings.push_back(warning);
        }
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
