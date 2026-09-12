#include "adapters/claude_code/claude_code.hpp"

#include <algorithm>
#include <fstream>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include "adapters/rewrite_common.hpp"
#include "adapters/secure_io.hpp"

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
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
  SessionRecord::ArtifactSource source;
  std::string image_path;
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

SessionRecord::ArtifactSource text_source(const fs::path& path, std::string bytes) {
  return SessionRecord::ArtifactSource{
      .path = path,
      .size = static_cast<std::uint64_t>(bytes.size()),
      .stream = [bytes = std::move(bytes)](const secure_io::ByteSink& sink) {
        return sink(std::as_bytes(std::span<const char>{bytes.data(), bytes.size()}));
      }};
}

bool valid_json(const std::string_view text) {
  simdjson::padded_string padded{text};
  simdjson::dom::parser parser;
  simdjson::dom::element value;
  return !parser.parse(padded).get(value);
}

void apply_torn_tail_rule(std::vector<std::string>& artifacts,
                          std::vector<SessionRecord::ArtifactSource>& sources,
                          const bool live,
                          std::vector<SessionRecord::TornTail>& torn_tails) {
  for (std::size_t i = 0; i < sources.size(); ++i) {
    if (!artifacts.at(i).ends_with(".jsonl")) continue;
    auto bytes = source_text(sources.at(i));
    if (!bytes) continue;
    const auto split = bytes->rfind('\n');
    const auto tail_start = split == std::string::npos ? 0U : split + 1U;
    const auto tail = std::string_view{*bytes}.substr(tail_start);
    if (tail.empty()) continue;
    if (valid_json(tail)) {
      bytes->push_back('\n');
      sources.at(i) = text_source(sources.at(i).path, std::move(*bytes));
    } else if (live) {
      torn_tails.push_back(SessionRecord::TornTail{.artifact = artifacts.at(i),
                                                    .bytes = tail.size()});
      bytes->resize(tail_start);
      sources.at(i) = text_source(sources.at(i).path, std::move(*bytes));
    } else {
      torn_tails.push_back(SessionRecord::TornTail{.artifact = artifacts.at(i),
                                                    .bytes = tail.size(),
                                                    .retained = true});
    }
  }
}

TranscriptFacts inspect_transcript(const std::string_view transcript) {
  TranscriptFacts facts;
  std::istringstream input{std::string{transcript}};
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

bool never_collect_path(const fs::path& relative) {
  const auto& denied = claude_code_adapter().state_inventory().never_collect;
  for (const auto& component : relative) {
    const auto name = component.generic_string();
    if (std::ranges::find(denied, name) != denied.end() ||
        (name.starts_with("settings") && name.ends_with(".json"))) {
      return true;
    }
  }
  return false;
}

bool supported_subtree_artifact(const fs::path& relative) {
  return rewrite::claude_staged_subtree_artifact(relative.generic_string());
}

expected<std::vector<ArtifactRef>> collect_subtree_artifacts(
    const fs::path& session_dir, const std::string_view session_id) {
  std::vector<ArtifactRef> artifacts;
  std::error_code ec;
  if (!fs::exists(session_dir, ec)) {
    return artifacts;
  }
  if (auto valid = secure_io::validate_directory_no_follow(session_dir); !valid) {
    return std::unexpected(valid.error());
  }
  for (fs::recursive_directory_iterator
           it{session_dir, fs::directory_options::none, ec},
       end;
       !ec && it != end; it.increment(ec)) {
    const auto& entry = *it;
    if (entry.is_symlink(ec) || !entry.is_regular_file(ec)) {
      continue;
    }
    const auto relative = entry.path().lexically_relative(session_dir);
    if (!lexically_inside(entry.path(), session_dir) ||
        never_collect_path(relative)) {
      continue;
    }
    if (!supported_subtree_artifact(relative)) {
      return std::unexpected(BivError{ErrKind::ArchiveWriteFailed,
                                      entry.path().generic_string(),
                                      "unsupported_subtree_artifact"});
    }
    auto source = open_artifact_source(entry.path());
    if (!source) {
      return std::unexpected(source.error());
    }
    std::string artifact = "agents/claude-code/";
    artifact += session_id;
    artifact += '/';
    artifact += relative.generic_string();
    artifacts.push_back(ArtifactRef{.source = std::move(*source),
                                    .image_path = std::move(artifact)});
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
  static const Inventory inventory = [] {
    Inventory value{
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
                         .relocated_contents = {},
                         .login_flow_owner = "claude-code",
                         .notes = {}}};
    value.caveat_facts.relocated_contents.push_back("projects");
    value.caveat_facts.relocated_contents.insert(
        value.caveat_facts.relocated_contents.end(), value.never_collect.begin(),
        value.never_collect.end());
    return value;
  }();
  return inventory;
}

expected<std::pair<fs::path, std::string>> locate_claude_staged_artifact(
    const fs::path& root, const rewrite::StagedMapRow& row,
    const rewrite::StagedSidecar& staged) {
  std::vector<fs::path> matches;
  std::error_code error;
  if (!fs::exists(root, error)) {
    return std::unexpected(BivError{ErrKind::ParseError, root.string(),
                                    "missing_staged_artifact"});
  }
  for (fs::recursive_directory_iterator it{root, fs::directory_options::none,
                                            error},
       end;
       !error && it != end; it.increment(error)) {
    if (it->path().filename() != row.minted + ".jsonl") continue;
    if (it->is_symlink(error) || !it->is_regular_file(error)) {
      return std::unexpected(BivError{ErrKind::ContainmentRefused,
                                      it->path().string(),
                                      "containment_refused"});
    }
    matches.push_back(it->path().lexically_normal());
  }
  if (error) {
    return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                    root.string(), error.message()});
  }
  if (matches.size() != 1U) {
    return std::unexpected(BivError{ErrKind::ParseError, root.string(),
                                    "missing_staged_artifact"});
  }

  if (row.original_path.has_value()) {
    return std::pair{matches.front(), *row.original_path};
  }

  std::optional<std::string> original_path;
  for (const auto& pair : staged.path_pairs) {
    const auto expected =
        (root / "projects" / project_key_for_path(fs::path{pair.first}) /
         (row.minted + ".jsonl"))
            .lexically_normal();
    if (expected == matches.front()) {
      if (original_path) {
        return std::unexpected(BivError{ErrKind::ParseError, root.string(),
                                        "missing_staged_artifact"});
      }
      original_path = pair.first;
    }
  }
  if (!original_path) {
    return std::unexpected(BivError{ErrKind::ParseError, root.string(),
                                    "missing_staged_artifact"});
  }
  return std::pair{matches.front(), std::move(*original_path)};
}

expected<void> append_staged_session(CollectReport& report,
                                     const fs::path& source_root) {
  const auto sidecar = source_root / ".biv/agents/manifest.json";
  std::error_code exists_error;
  const auto status = fs::symlink_status(sidecar, exists_error);
  if (status.type() == fs::file_type::not_found) {
    if (exists_error &&
        exists_error != std::errc::no_such_file_or_directory) {
      return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                      sidecar.string(),
                                      exists_error.message()});
    }
    return {};
  }
  auto input = open_artifact_source(sidecar);
  if (!input) return std::unexpected(input.error());
  auto json = source_text(*input);
  if (!json) return std::unexpected(json.error());
  auto staged = rewrite::parse_staged_sidecar(sidecar, *json, source_root);
  if (!staged) return std::unexpected(staged.error());

  const auto root = source_root / ".biv/agents/claude-code";
  for (const auto& row : staged->rows) {
    if (row.agent != "claude-code") continue;
    auto located = locate_claude_staged_artifact(root, row, *staged);
    if (!located) return std::unexpected(located.error());
    const auto& [main_path, original_path] = *located;
    auto main_source = open_artifact_source(main_path);
    if (!main_source) return std::unexpected(main_source.error());
    auto main_text = source_text(*main_source);
    if (!main_text) return std::unexpected(main_text.error());
    const auto facts = inspect_transcript(*main_text);
    if (facts.session_id.has_value() && *facts.session_id != row.minted) {
      return std::unexpected(BivError{ErrKind::ParseError, main_path.string(),
                                      "staged_identity_mismatch"});
    }
    if (!facts.version.has_value()) {
      report.warnings.push_back("StagedSessionVersionMissing:" +
                                main_path.generic_string());
      continue;
    }

    std::vector<std::string> artifacts{
        "agents/claude-code/" + row.minted + ".jsonl"};
    std::vector<SessionRecord::ArtifactSource> sources{
        std::move(*main_source)};
    std::vector<std::string> child_ids;
    std::vector<std::pair<std::string, std::string>> child_artifact_map;
    for (const auto& [child_original, child_minted] : row.children) {
      static_cast<void>(child_minted);
      child_ids.push_back(child_original);
    }
    const auto subtree = main_path.parent_path() / row.minted;
    std::error_code subtree_error;
    if (fs::exists(subtree, subtree_error)) {
      for (fs::recursive_directory_iterator
               it{subtree, fs::directory_options::none, subtree_error},
           end;
           !subtree_error && it != end; it.increment(subtree_error)) {
        if (it->is_symlink(subtree_error)) {
          return std::unexpected(BivError{ErrKind::ContainmentRefused,
                                          it->path().string(),
                                          "staged_subtree_class"});
        }
        if (it->is_directory(subtree_error)) continue;
        if (!it->is_regular_file(subtree_error)) {
          return std::unexpected(BivError{ErrKind::ContainmentRefused,
                                          it->path().string(),
                                          "staged_subtree_class"});
        }
        const auto relative_path = it->path().lexically_relative(subtree);
        const auto relative = relative_path.generic_string();
        if (never_collect_path(relative_path) ||
            !rewrite::claude_staged_subtree_artifact(relative)) {
          report.warnings.push_back(
              "StagedSessionArtifactSkipped:" + it->path().generic_string());
          continue;
        }
        const auto extension = it->path().extension().string();
        const bool subagent_jsonl =
            relative.starts_with("subagents/") && extension == ".jsonl";
        const bool subagent_meta = relative.starts_with("subagents/") &&
                                   relative.ends_with(".meta.json");
        auto artifact_source = open_artifact_source(it->path());
        if (!artifact_source) {
          return std::unexpected(artifact_source.error());
        }
        if (subagent_jsonl) {
          auto artifact_text = source_text(*artifact_source);
          if (!artifact_text) return std::unexpected(artifact_text.error());
          const auto artifact_facts = inspect_transcript(*artifact_text);
          if (artifact_facts.session_id.has_value() &&
              *artifact_facts.session_id != row.minted) {
            return std::unexpected(BivError{ErrKind::ParseError,
                                            it->path().string(),
                                            "staged_identity_mismatch"});
          }
        }
        auto artifact =
            "agents/claude-code/" + row.minted + "/" + relative;
        if (subagent_jsonl || subagent_meta) {
          const auto owner = std::ranges::find_if(
              row.children, [&](const auto& child) {
                return relative == "subagents/" + child.first + ".jsonl" ||
                       relative ==
                           "subagents/" + child.first + ".meta.json";
              });
          if (owner != row.children.end()) {
            child_artifact_map.emplace_back(owner->first, artifact);
          }
        }
        artifacts.push_back(std::move(artifact));
        sources.push_back(std::move(*artifact_source));
      }
      if (subtree_error) {
        return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                        subtree.string(),
                                        subtree_error.message()});
      }
    } else if (subtree_error) {
      return std::unexpected(BivError{ErrKind::SourceUnreadableRoot,
                                      subtree.string(),
                                      subtree_error.message()});
    }

    std::vector<std::size_t> order(artifacts.size());
    std::iota(order.begin(), order.end(), 0U);
    std::ranges::sort(order, {}, [&](const std::size_t index) {
      return artifacts.at(index);
    });
    std::vector<std::string> sorted_artifacts;
    std::vector<SessionRecord::ArtifactSource> sorted_sources;
    for (const auto index : order) {
      sorted_artifacts.push_back(std::move(artifacts.at(index)));
      sorted_sources.push_back(std::move(sources.at(index)));
    }
    artifacts = std::move(sorted_artifacts);
    sources = std::move(sorted_sources);
    std::vector<SessionRecord::TornTail> tails;
    apply_torn_tail_rule(artifacts, sources, false, tails);
    report.sessions.push_back(SessionRecord{
        .agent = "claude-code",
        .original_session_id = row.original,
        .parent_id = std::nullopt,
        .child_ids = std::move(child_ids),
        .child_artifact_map = std::move(child_artifact_map),
        .original_path = original_path,
        .normalized_path_key = rewrite::normalized_path_key(original_path),
        .normalization_scheme = "claude-cwd/v1",
        .path_flavor = rewrite::path_flavor_for(original_path),
        .provenance = {.store_root = source_root.generic_string(),
                       .locator = "staging",
                       .discovery_tier = "staged",
                       .archived = false},
        .artifacts = std::move(artifacts),
        .artifact_sources = std::move(sources),
        .torn_tails = std::move(tails),
        .agent_version_at_pack = *facts.version,
        .live_at_pack = false});
  }
  return {};
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
      if (auto staged = append_staged_session(report, source_root); !staged) {
        return std::unexpected(staged.error());
      }
      for (const auto& store : stores) {
        if (auto valid = secure_io::validate_directory_no_follow(store.root);
            !valid) {
          return std::unexpected(valid.error());
        }
        const auto projects_dir = store.root / "projects";
        std::error_code ec;
        if (!fs::exists(projects_dir, ec)) {
          continue;
        }
        if (auto valid = secure_io::validate_directory_no_follow(projects_dir);
            !valid) {
          return std::unexpected(valid.error());
        }
        const auto sessions_dir = store.root / "sessions";
        if (fs::exists(sessions_dir, ec)) {
          if (auto valid = secure_io::validate_directory_no_follow(sessions_dir);
              !valid) {
            return std::unexpected(valid.error());
          }
        }
        const auto live_by_id = live_facts_by_id(store.root);
        for (fs::directory_iterator project_it{projects_dir, ec}, project_end;
             !ec && project_it != project_end; project_it.increment(ec)) {
          const auto& project_dir = *project_it;
          if (project_dir.is_symlink(ec)) {
            return std::unexpected(BivError{ErrKind::ArchiveWriteFailed,
                                            project_dir.path().generic_string(),
                                            "containment_refused"});
          }
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
            if (entry.is_symlink(ec) || !entry.is_regular_file(ec) ||
                entry.path().extension() != ".jsonl" ||
                never_collect_path(entry.path().lexically_relative(store.root))) {
              continue;
            }
            auto main_source = open_artifact_source(entry.path());
            if (!main_source) {
              return std::unexpected(main_source.error());
            }
            auto main_text = source_text(*main_source);
            if (!main_text) {
              return std::unexpected(main_text.error());
            }
            auto facts = inspect_transcript(*main_text);
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
            std::vector<SessionRecord::ArtifactSource> artifact_sources;
            artifacts.push_back("agents/claude-code/" + session_id + ".jsonl");
            artifact_sources.push_back(std::move(*main_source));
            auto subtree_artifacts = collect_subtree_artifacts(session_dir, session_id);
            if (!subtree_artifacts) {
              return std::unexpected(subtree_artifacts.error());
            }
            for (auto& artifact : *subtree_artifacts) {
              artifact_sources.push_back(std::move(artifact.source));
              artifacts.push_back(std::move(artifact.image_path));
            }
            std::vector<SessionRecord::TornTail> torn_tails;
            apply_torn_tail_rule(artifacts, artifact_sources, live.live, torn_tails);

            report.sessions.push_back(SessionRecord{
                .agent = "claude-code",
                .original_session_id = session_id,
                .parent_id = std::nullopt,
                .child_ids = child_ids_for(session_dir),
                .child_artifact_map = {},
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
                .torn_tails = std::move(torn_tails),
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
