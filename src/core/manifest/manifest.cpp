#include "core/manifest/manifest.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>
#include <set>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include "core/json/writer.hpp"
#include "core/manifest/agent_member.hpp"
#include "core/repo/git_exec.hpp"
#include "core/support/version.hpp"

namespace biv::manifest {

namespace {

constexpr std::size_t kSessionChildrenCap = 1024U;
constexpr std::size_t kSessionParentDepthCap = 64U;
constexpr std::size_t kSessionArtifactsPerNodeCap = 256U;
constexpr std::size_t kSessionArtifactsTotalCap = 4096U;

BivError entry_cap_error(const std::string_view primary_id,
                         const std::string_view cap) {
  return BivError{ErrKind::ParseError, {},
                  std::string{cap} + " entry=" + std::string{primary_id}};
}

expected<std::string> required_string(simdjson::dom::object object, std::string_view key) {
  std::string_view value;
  const auto error = object.at_key(key).get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::string{value};
}

expected<int> required_int(simdjson::dom::object object, std::string_view key) {
  int64_t value = 0;
  const auto error = object.at_key(key).get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return static_cast<int>(value);
}

expected<bool> required_bool(simdjson::dom::object object, std::string_view key) {
  bool value = false;
  const auto error = object.at_key(key).get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return value;
}

expected<simdjson::dom::object> required_object(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::object value;
  const auto error = object.at_key(key).get(value);
  if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return value;
}

expected<std::vector<std::string>> required_string_array(simdjson::dom::object object,
                                                         std::string_view key) {
  simdjson::dom::array array;
  if (const auto error = object.at_key(key).get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  std::vector<std::string> out;
  for (auto element : array) {
    std::string_view value;
    if (const auto error = element.get(value); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
    }
    out.emplace_back(value);
  }
  return out;
}

expected<std::vector<std::string>> optional_string_array(
    simdjson::dom::object object, const std::string_view key) {
  simdjson::dom::array array;
  if (const auto error = object.at_key(key).get(array);
      error == simdjson::NO_SUCH_FIELD) {
    return std::vector<std::string>{};
  } else if (error) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  std::vector<std::string> out;
  for (auto element : array) {
    std::string_view value;
    if (const auto error = element.get(value); error) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, std::string{key}});
    }
    out.emplace_back(value);
  }
  return out;
}

expected<std::optional<std::string>> optional_string(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element); error == simdjson::NO_SUCH_FIELD) {
    return std::optional<std::string>{};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }

  if (element.is_null()) {
    return std::optional<std::string>{};
  }
  std::string_view value;
  if (const auto error = element.get(value); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<std::string>{std::string{value}};
}

expected<std::optional<bool>> optional_bool(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element); error == simdjson::NO_SUCH_FIELD) {
    return std::optional<bool>{};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }

  bool value = false;
  if (const auto error = element.get(value); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<bool>{value};
}

expected<std::optional<std::string>> optional_nonnull_string(
    simdjson::dom::object object, const std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element);
      error == simdjson::NO_SUCH_FIELD) {
    return std::optional<std::string>{};
  } else if (error || element.is_null()) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, std::string{key}});
  }

  std::string_view value;
  if (const auto error = element.get(value); error) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<std::string>{std::string{value}};
}

bool starts_with_json_object(std::string_view text) {
  const auto pos = text.find_first_not_of(" \t\r\n");
  return pos != std::string_view::npos && text.at(pos) == '{';
}

bool is_agent_start(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

bool is_agent_char(const char c) {
  return is_agent_start(c) || c == '.' || c == '_' || c == '-';
}

bool agent_id_ok(std::string_view agent) {
  if (agent.empty() || !is_agent_start(agent.front())) {
    return false;
  }
  for (const char c : agent.substr(1)) {
    if (!is_agent_char(c)) {
      return false;
    }
  }
  return true;
}

expected<void> validate_artifacts(std::string_view agent, const std::vector<std::string>& artifacts) {
  for (const auto& artifact : artifacts) {
    if (!grammar::agent_member_ok(grammar::AgentId{agent},
                                  grammar::MemberPath{artifact})) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "artifact-prefix"});
    }
  }
  return {};
}

expected<void> validate_stub_entry_footprint_keys(
    simdjson::dom::object object) {
  bool artifacts_seen = false;
  bool children_seen = false;
  for (const auto field : object) {
    if (field.key == "artifacts") {
      if (artifacts_seen) {
        return std::unexpected(BivError{
            ErrKind::ParseError, {},
            "stub-footprint-entry-artifacts-duplicate-key"});
      }
      artifacts_seen = true;
    } else if (field.key == "children") {
      if (children_seen) {
        return std::unexpected(BivError{
            ErrKind::ParseError, {},
            "stub-footprint-entry-children-duplicate-key"});
      }
      children_seen = true;
    }
  }
  return {};
}

expected<void> validate_stub_child_footprint_keys(
    simdjson::dom::object child) {
  bool artifacts_seen = false;
  for (const auto field : child) {
    if (field.key != "artifacts") {
      continue;
    }
    if (artifacts_seen) {
      return std::unexpected(BivError{
          ErrKind::ParseError, {},
          "stub-footprint-child-artifacts-duplicate-key"});
    }
    artifacts_seen = true;
  }
  return {};
}

BivError stub_cap_error(const std::string_view cap) {
  return BivError{ErrKind::ParseError, {}, std::string{cap}};
}

expected<std::vector<std::string>> parse_stub_member_footprint(
    simdjson::dom::object object, const std::string_view agent) {
  if (auto unique_keys = validate_stub_entry_footprint_keys(object);
      !unique_keys) {
    return std::unexpected(unique_keys.error());
  }

  auto entry_artifacts = optional_string_array(object, "artifacts");
  if (!entry_artifacts) {
    return std::unexpected(entry_artifacts.error());
  }
  if (entry_artifacts->size() > kSessionArtifactsPerNodeCap) {
    return std::unexpected(
        stub_cap_error("entry-artifacts-per-node-cap"));
  }
  if (auto valid = validate_artifacts(agent, *entry_artifacts); !valid) {
    return std::unexpected(valid.error());
  }

  std::vector<std::string> footprint = std::move(*entry_artifacts);
  simdjson::dom::array children;
  if (const auto error = object.at_key("children").get(children);
      error == simdjson::NO_SUCH_FIELD) {
    return footprint;
  } else if (error) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, "children"});
  }

  std::size_t child_count = 0U;
  for (auto element : children) {
    if (child_count == kSessionChildrenCap) {
      return std::unexpected(stub_cap_error("children-node-cap"));
    }
    ++child_count;

    simdjson::dom::object child;
    if (const auto error = element.get(child); error) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "children"});
    }
    if (auto unique_keys = validate_stub_child_footprint_keys(child);
        !unique_keys) {
      return std::unexpected(unique_keys.error());
    }
    auto child_artifacts = optional_string_array(child, "artifacts");
    if (!child_artifacts) {
      return std::unexpected(child_artifacts.error());
    }
    if (child_artifacts->size() > kSessionArtifactsPerNodeCap) {
      return std::unexpected(
          stub_cap_error("children-artifacts-per-node-cap"));
    }
    if (auto valid = validate_artifacts(agent, *child_artifacts); !valid) {
      return std::unexpected(valid.error());
    }
    if (child_artifacts->size() >
        kSessionArtifactsTotalCap - footprint.size()) {
      return std::unexpected(
          stub_cap_error("entry-artifacts-total-cap"));
    }
    footprint.insert(footprint.end(),
                     std::make_move_iterator(child_artifacts->begin()),
                     std::make_move_iterator(child_artifacts->end()));
  }
  return footprint;
}

expected<PathFlavor> parse_entry_path_flavor(std::string_view value) {
  if (value == "posix") {
    return PathFlavor::posix;
  }
  if (value == "windows") {
    return PathFlavor::windows;
  }
  if (value == "wsl") {
    return PathFlavor::wsl;
  }
  return std::unexpected(BivError{ErrKind::ParseError, {}, "path_flavor"});
}

expected<void> validate_child_keys_unique(simdjson::dom::object child) {
  bool original_id_seen = false;
  bool artifacts_seen = false;
  bool parent_id_seen = false;
  for (const auto field : child) {
    bool* seen = nullptr;
    if (field.key == "original_id") {
      seen = &original_id_seen;
    } else if (field.key == "artifacts") {
      seen = &artifacts_seen;
    } else if (field.key == "parent_id") {
      seen = &parent_id_seen;
    }
    if (seen != nullptr && *seen) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "children-duplicate-key"});
    }
    if (seen != nullptr) {
      *seen = true;
    }
  }
  return {};
}

expected<std::vector<SessionChild>> parse_session_children(
    simdjson::dom::object object, const std::string& agent,
    const std::string_view primary_id) {
  simdjson::dom::array array;
  if (const auto error = object.at_key("children").get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
  }

  std::vector<SessionChild> out;
  for (auto element : array) {
    if (out.size() == kSessionChildrenCap) {
      return std::unexpected(
          entry_cap_error(primary_id, "children-node-cap"));
    }
    simdjson::dom::object child_object;
    if (const auto error = element.get(child_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
    }
    if (auto unique_keys = validate_child_keys_unique(child_object);
        !unique_keys) {
      return std::unexpected(unique_keys.error());
    }
    auto original_id = required_string(child_object, "original_id");
    auto artifacts = required_string_array(child_object, "artifacts");
    auto parent_id = optional_nonnull_string(child_object, "parent_id");
    if (!original_id || !artifacts || !parent_id ||
        !grammar::session_id_ok(*original_id) ||
        (parent_id->has_value() && !grammar::session_id_ok(**parent_id))) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
    }
    auto valid = validate_artifacts(agent, *artifacts);
    if (!valid) {
      return std::unexpected(valid.error());
    }
    if (artifacts->empty()) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "children-artifacts-empty"});
    }
    if (artifacts->size() > kSessionArtifactsPerNodeCap) {
      return std::unexpected(entry_cap_error(
          primary_id, "children-artifacts-per-node-cap"));
    }
    out.push_back(SessionChild{.original_id = std::move(*original_id),
                               .artifacts = std::move(*artifacts),
                               .parent_id = std::move(*parent_id)});
  }

  std::unordered_map<std::string, std::size_t> child_by_id;
  child_by_id.reserve(out.size());
  for (std::size_t i = 0; i < out.size(); ++i) {
    const auto& child = out.at(i);
    if (child.original_id == primary_id ||
        !child_by_id.emplace(child.original_id, i).second) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "children-node-uniqueness"});
    }
  }

  for (const auto& child : out) {
    if (!child.parent_id.has_value()) {
      continue;
    }
    if (*child.parent_id == primary_id ||
        !child_by_id.contains(*child.parent_id)) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "children-parent-tree"});
    }
  }

  for (std::size_t start = 0; start < out.size(); ++start) {
    std::unordered_set<std::size_t> visited;
    std::size_t current = start;
    std::size_t depth = 1U;
    while (true) {
      if (!visited.insert(current).second) {
        return std::unexpected(
            BivError{ErrKind::ParseError, {}, "children-parent-tree"});
      }
      if (depth > kSessionParentDepthCap) {
        return std::unexpected(
            entry_cap_error(primary_id, "children-depth-cap"));
      }
      const auto parent_id =
          out.at(current).parent_id.value_or(std::string{});
      if (parent_id.empty()) {
        break;
      }
      current = child_by_id.at(parent_id);
      ++depth;
    }
  }
  return out;
}

expected<AgentSessionEntry> parse_agent_session(simdjson::dom::object object) {
  AgentSessionEntry entry;
  auto agent = required_string(object, "agent");
  if (!agent) {
    return std::unexpected(agent.error());
  }
  if (!agent_id_ok(*agent)) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent-id-grammar"});
  }
  entry.agent = std::move(*agent);

  auto entry_schema = required_int(object, "entry_schema");
  if (!entry_schema) {
    return std::unexpected(entry_schema.error());
  }
  entry.entry_schema = *entry_schema;
  if (entry.entry_schema < 1) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "entry_schema"});
  }
  if (entry.entry_schema > kEntrySchemaParseCeiling) {
    auto footprint = parse_stub_member_footprint(object, entry.agent);
    if (!footprint) {
      return std::unexpected(footprint.error());
    }
    entry.stub_member_footprint = std::move(*footprint);
    return entry;
  }

  auto agent_version = required_string(object, "agent_version_at_pack");
  auto relpath_key = required_string(object, "relpath_key");
  auto original_path = required_string(object, "original_path");
  auto normalized_path_key = required_string(object, "normalized_path_key");
  auto normalization_scheme = required_string(object, "normalization_scheme");
  auto path_flavor_value = required_string(object, "path_flavor");
  if (!agent_version || !relpath_key || !original_path || !normalized_path_key || !normalization_scheme ||
      !path_flavor_value) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent-session-field"});
  }
  entry.agent_version_at_pack = std::move(*agent_version);
  entry.relpath_key = std::move(*relpath_key);
  entry.original_path = std::move(*original_path);
  entry.normalized_path_key = std::move(*normalized_path_key);
  entry.normalization_scheme = std::move(*normalization_scheme);
  auto path_flavor = parse_entry_path_flavor(*path_flavor_value);
  if (!path_flavor) {
    return std::unexpected(path_flavor.error());
  }
  entry.path_flavor = *path_flavor;

  auto provenance = required_object(object, "provenance");
  if (!provenance) {
    return std::unexpected(provenance.error());
  }
  auto store_root = required_string(*provenance, "store_root");
  auto locator = required_string(*provenance, "locator");
  auto discovery_tier = required_string(*provenance, "discovery_tier");
  auto archived = required_bool(*provenance, "archived");
  if (!store_root || !locator || !discovery_tier || !archived) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "provenance"});
  }
  entry.provenance = {.store_root = std::move(*store_root),
                      .locator = std::move(*locator),
                      .discovery_tier = std::move(*discovery_tier),
                      .archived = *archived};

  auto ids = required_object(object, "original_session_ids");
  if (!ids) {
    return std::unexpected(ids.error());
  }
  auto primary = required_string(*ids, "primary");
  auto parent = optional_string(*ids, "parent");
  auto parent_in_image = optional_bool(*ids, "parent_in_image");
  if (!primary || !parent || !parent_in_image) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "session-ids"});
  }
  if (!grammar::session_id_ok(*primary) ||
      (parent->has_value() && !grammar::session_id_ok(**parent)) ||
      (parent_in_image->has_value() && (!parent->has_value() || **parent_in_image))) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "session-ids"});
  }
  entry.original_session_ids = {
      .primary = std::move(*primary), .parent = std::move(*parent), .parent_in_image = *parent_in_image};

  auto children = parse_session_children(
      object, entry.agent, entry.original_session_ids.primary);
  if (!children) {
    return std::unexpected(children.error());
  }
  auto artifacts = required_string_array(object, "artifacts");
  auto live_at_pack = required_bool(object, "live_at_pack");
  auto imported_at = required_string(object, "imported_at");
  if (!artifacts || !live_at_pack || !imported_at) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent-session-field"});
  }
  auto valid = validate_artifacts(entry.agent, *artifacts);
  if (!valid) {
    return std::unexpected(valid.error());
  }
  if (artifacts->empty()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "artifacts-empty"});
  }
  std::size_t artifact_count = artifacts->size();
  for (const auto& child : *children) {
    artifact_count += child.artifacts.size();
  }
  if (artifact_count > kSessionArtifactsTotalCap) {
    return std::unexpected(entry_cap_error(
        entry.original_session_ids.primary, "entry-artifacts-total-cap"));
  }
  entry.children = std::move(*children);
  entry.artifacts = std::move(*artifacts);
  entry.live_at_pack = *live_at_pack;
  entry.imported_at = std::move(*imported_at);
  return entry;
}

expected<std::vector<AgentSessionEntry>> parse_agent_sessions(simdjson::dom::object object) {
  simdjson::dom::element element;
  if (const auto error = object.at_key("agent_sessions").get(element); error == simdjson::NO_SUCH_FIELD) {
    return std::vector<AgentSessionEntry>{};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent_sessions"});
  }

  simdjson::dom::array array;
  if (const auto error = element.get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent_sessions"});
  }

  std::set<std::pair<std::string, std::string>> seen;
  std::set<std::string> seen_artifacts;
  std::vector<AgentSessionEntry> out;
  for (auto item : array) {
    simdjson::dom::object entry_object;
    if (const auto error = item.get(entry_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "agent_sessions"});
    }
    auto entry = parse_agent_session(entry_object);
    if (!entry) {
      return std::unexpected(entry.error());
    }
    if (!entry->original_session_ids.primary.empty() &&
        !seen.insert({entry->agent, entry->original_session_ids.primary}).second) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "session-uniqueness"});
    }
    for (const auto& artifact : entry->artifacts) {
      if (!seen_artifacts.insert(artifact).second) {
        return std::unexpected(BivError{ErrKind::ParseError, {},
                                        "artifact-uniqueness"});
      }
    }
    for (const auto& child : entry->children) {
      for (const auto& artifact : child.artifacts) {
        if (!seen_artifacts.insert(artifact).second) {
          return std::unexpected(BivError{ErrKind::ParseError, {},
                                          "artifact-uniqueness"});
        }
      }
    }
    for (const auto& artifact : entry->stub_member_footprint) {
      if (!seen_artifacts.insert(artifact).second) {
        return std::unexpected(BivError{ErrKind::ParseError, {},
                                        "artifact-uniqueness"});
      }
    }
    out.push_back(std::move(*entry));
  }
  for (const auto& entry : out) {
    if (!entry.original_session_ids.parent.has_value()) {
      continue;
    }
    const bool parent_in_set = seen.contains(
        {entry.agent, *entry.original_session_ids.parent});
    if ((parent_in_set && entry.original_session_ids.parent_in_image.has_value()) ||
        (!parent_in_set &&
         entry.original_session_ids.parent_in_image !=
             std::optional<bool>{false})) {
      return std::unexpected(BivError{ErrKind::ParseError, {},
                                      "session-parent-relationship"});
    }
  }
  return out;
}

void write_string_array(json::Writer& writer, const std::vector<std::string>& values) {
  writer.begin_array();
  for (const auto& value : values) {
    writer.value_string(value);
  }
  writer.end_array();
}

void write_agent_session(json::Writer& writer, const AgentSessionEntry& entry) {
  const bool has_parent_edge =
      std::ranges::any_of(entry.children, [&entry](const SessionChild& child) {
        return child.parent_id.has_value() &&
               *child.parent_id != entry.original_session_ids.primary;
      });
  writer.begin_object();
  writer.key("agent");
  writer.value_string(entry.agent);
  writer.key("agent_version_at_pack");
  writer.value_string(entry.agent_version_at_pack);
  writer.key("relpath_key");
  writer.value_string(entry.relpath_key);
  writer.key("original_path");
  writer.value_string(entry.original_path);
  writer.key("normalized_path_key");
  writer.value_string(entry.normalized_path_key);
  writer.key("normalization_scheme");
  writer.value_string(entry.normalization_scheme);
  writer.key("path_flavor");
  writer.value_string(to_string(entry.path_flavor));
  writer.key("provenance");
  writer.begin_object();
  writer.key("store_root");
  writer.value_string(entry.provenance.store_root);
  writer.key("locator");
  writer.value_string(entry.provenance.locator);
  writer.key("discovery_tier");
  writer.value_string(entry.provenance.discovery_tier);
  writer.key("archived");
  writer.value_bool(entry.provenance.archived);
  writer.end_object();
  writer.key("original_session_ids");
  writer.begin_object();
  writer.key("primary");
  writer.value_string(entry.original_session_ids.primary);
  if (entry.original_session_ids.parent.has_value()) {
    writer.key("parent");
    writer.value_string(*entry.original_session_ids.parent);
  }
  if (entry.original_session_ids.parent_in_image.has_value()) {
    writer.key("parent_in_image");
    writer.value_bool(*entry.original_session_ids.parent_in_image);
  }
  writer.end_object();
  writer.key("children");
  writer.begin_array();
  for (const auto& child : entry.children) {
    writer.begin_object();
    writer.key("original_id");
    writer.value_string(child.original_id);
    if (child.parent_id.has_value() &&
        *child.parent_id != entry.original_session_ids.primary) {
      writer.key("parent_id");
      writer.value_string(*child.parent_id);
    }
    writer.key("artifacts");
    write_string_array(writer, child.artifacts);
    writer.end_object();
  }
  writer.end_array();
  writer.key("artifacts");
  write_string_array(writer, entry.artifacts);
  writer.key("live_at_pack");
  writer.value_bool(entry.live_at_pack);
  writer.key("imported_at");
  writer.value_string(entry.imported_at);
  writer.key("entry_schema");
  writer.value_int(has_parent_edge ? 2 : 1);
  writer.end_object();
}

}  // namespace

namespace {

bool carrier_ascii_alpha(const char value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
}

struct CarrierRoot {
  PathFlavor flavor;
  std::size_t root_length;
};

std::optional<CarrierRoot> classify_carrier_root(const std::string_view path) {
  if (path.size() >= 7U && path.starts_with("/mnt/") &&
      carrier_ascii_alpha(path.at(5)) && path.at(6) == '/') {
    return CarrierRoot{.flavor = PathFlavor::wsl, .root_length = 7U};
  }
  if (path.starts_with(R"(\\?\)") || path.starts_with("//?/")) {
    return CarrierRoot{.flavor = PathFlavor::windows, .root_length = 7U};
  }
  if (path.size() >= 3U && carrier_ascii_alpha(path.at(0)) &&
      path.at(1) == ':' && (path.at(2) == '\\' || path.at(2) == '/')) {
    return CarrierRoot{.flavor = PathFlavor::windows, .root_length = 3U};
  }
  if (path.starts_with('/')) {
    return CarrierRoot{.flavor = PathFlavor::posix, .root_length = 1U};
  }
  return std::nullopt;
}

}  // namespace

namespace {

using repo::CaptureMode;
using repo::EligibilityResult;
using repo::ForcedPayloadReason;
using repo::HeadState;
using repo::RefAvailability;
using repo::RepoEntry;
using repo::RepoKind;

struct RepoFieldTable {
  std::string_view id{"id"};
  std::string_view relpath{"relpath"};
  std::string_view kind{"kind"};
  std::string_view parent_id{"parent_id"};
  std::string_view remote{"remote"};
  std::string_view remotes{"remotes"};
  std::string_view sha{"sha"};
  std::string_view branch{"branch"};
  std::string_view head_state{"head_state"};
  std::string_view dirty{"dirty"};
  std::string_view capture_mode{"capture_mode"};
  std::string_view eligibility{"eligibility"};
  std::string_view local_refs{"local_refs"};
  std::string_view local_refs_bundle{"local_refs_bundle"};
  std::string_view capture{"capture"};
  std::string_view bundle{"bundle"};
  std::string_view sparse{"sparse"};
  std::string_view notes{"notes"};
  std::string_view shallow{"shallow"};
};

inline constexpr RepoFieldTable kRepoFields{};

template <typename Enum, std::size_t Size>
using EnumFieldTable = std::array<std::pair<Enum, std::string_view>, Size>;

constexpr EnumFieldTable<RepoKind, 3> kRepoKinds{{
    {RepoKind::repo, "repo"},
    {RepoKind::submodule, "submodule"},
    {RepoKind::nested, "nested"},
}};
constexpr EnumFieldTable<HeadState, 3> kHeadStates{{
    {HeadState::branch, "branch"},
    {HeadState::detached, "detached"},
    {HeadState::unborn, "unborn"},
}};
constexpr EnumFieldTable<CaptureMode, 2> kCaptureModes{{
    {CaptureMode::overlay, "overlay"},
    {CaptureMode::full, "full"},
}};
constexpr EnumFieldTable<EligibilityResult, 7> kEligibilityResults{{
    {EligibilityResult::proven, "proven"},
    {EligibilityResult::unknown_tip, "unknown-tip"},
    {EligibilityResult::no_remote, "no-remote"},
    {EligibilityResult::sha_unpushed, "sha-unpushed"},
    {EligibilityResult::remote_unreachable, "remote-unreachable"},
    {EligibilityResult::offline_declared, "offline-declared"},
    {EligibilityResult::unborn_head, "unborn-head"},
}};
constexpr EnumFieldTable<RefAvailability, 3> kRefAvailabilities{{
    {RefAvailability::remote_proven, "remote-proven"},
    {RefAvailability::bundle_carried, "bundle-carried"},
    {RefAvailability::repo_bundle_carried, "repo-bundle-carried"},
}};
constexpr EnumFieldTable<ForcedPayloadReason, 5> kForcedPayloadReasons{{
    {ForcedPayloadReason::eol_conversion, "eol-conversion"},
    {ForcedPayloadReason::filemode_unrepresentable, "filemode-unrepresentable"},
    {ForcedPayloadReason::rename_in_flight, "rename-in-flight"},
    {ForcedPayloadReason::binary_unstaged_intent, "binary-unstaged-intent"},
    {ForcedPayloadReason::adapter_other, "adapter-other"},
}};

template <typename Enum, std::size_t Size>
std::string_view enum_field_name(const Enum value,
                                 const EnumFieldTable<Enum, Size> &table) {
  const auto match = std::ranges::find_if(
      table, [value](const auto &row) { return row.first == value; });
  return match == table.end() ? table.front().second : match->second;
}

template <typename Enum, std::size_t Size>
bool enum_field_valid(const Enum value,
                      const EnumFieldTable<Enum, Size> &table) {
  return std::ranges::any_of(
      table, [value](const auto &row) { return row.first == value; });
}

template <typename Enum, std::size_t Size>
expected<Enum> parse_enum_field(const std::string_view value,
                                const char *const key,
                                const EnumFieldTable<Enum, Size> &table) {
  const auto match = std::ranges::find_if(
      table, [value](const auto &row) { return row.second == value; });
  if (match == table.end()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return match->first;
}

void write_nullable_string(json::Writer &writer,
                           const std::optional<std::string> &value) {
  if (value) {
    writer.value_string(*value);
  } else {
    writer.value_null();
  }
}

void write_nullable_path(json::Writer &writer,
                         const std::optional<std::filesystem::path> &value) {
  if (value) {
    writer.value_string(value->generic_string());
  } else {
    writer.value_null();
  }
}

void write_proof(json::Writer &writer,
                 const std::optional<repo::Proof> &proof) {
  if (!proof) {
    writer.value_null();
    return;
  }
  writer.begin_object();
  writer.key("remote");
  writer.value_string(proof->remote);
  writer.key("url");
  writer.value_string(proof->url);
  writer.key("ref");
  writer.value_string(proof->ref);
  writer.key("tip_sha");
  writer.value_string(proof->tip_sha);
  writer.end_object();
}

struct RawReplacement {
  std::string token;
  std::string value;
  std::size_t offset{};
};

bool payload_only_unborn(const RepoEntry &entry) {
  return !entry.shallow && entry.head_state == HeadState::unborn &&
         !entry.bundle && !entry.eligibility && entry.local_refs.empty();
}

bool is_hex_object_id(std::string_view value);
expected<std::string> p1_decode(std::string_view encoded);
bool valid_full_ref_name(std::string_view ref);
bool catch_all_ref(std::string_view ref);

struct Violation {
  std::string_view field;
  std::string_view clause;
};

struct RepoRowFacts {
  const RepoEntry *row;
  bool capture_mode_present;
  bool local_refs_present;
  bool sparse_present_non_null;
};

enum class RepoRowClauseKind {
  relpath,
  local_refs_bundle_path,
  bundle_path,
  staged_patch_path,
  worktree_patch_path,
  payload_prefix_path,
  forced_payload_path,
  utf8,
  sha_head_state,
  sha_hex,
  sparse_null,
  local_refs_presence,
  capture_mode_presence,
  eligibility_method,
  eligibility_proof_tip_sha,
  local_refs_sha,
  local_refs_proof_tip_sha,
  local_refs_proof_presence,
  shallow_eligibility,
  shallow_local_refs,
  shallow_local_refs_bundle,
  shallow_bundle,
  shallow_boundary_hex,
  unborn_bundle_eligibility,
  unborn_bundle_result,
  unborn_bundle_capture_mode,
  born_unborn_head_result,
  payload_only_unborn_eligibility,
  unborn_no_bundle_local_refs,
  non_carried_unique,
  non_carried_refs_cap,
  non_carried_omitted_positive,
  non_carried_omitted_max,
  non_carried_refs_or_omitted,
  non_carried_p1,
  non_carried_ref_bytes,
  non_carried_full_ref,
  non_carried_catch_all,
  non_carried_strict_order,
  unknown_note_json_valid,
  unknown_note_single_value,
  unknown_note_object,
  unknown_note_kind_present,
  unknown_note_kind_string,
  local_refs_bundle_biconditional,
};

struct RepoRowClause {
  RepoRowClauseKind kind;
  std::string_view field;
};

constexpr std::array kRepoRowClauses{
    RepoRowClause{RepoRowClauseKind::relpath, "relpath"},
    RepoRowClause{RepoRowClauseKind::local_refs_bundle_path,
                  "local_refs_bundle"},
    RepoRowClause{RepoRowClauseKind::bundle_path, "bundle"},
    RepoRowClause{RepoRowClauseKind::staged_patch_path, "staged_patch"},
    RepoRowClause{RepoRowClauseKind::worktree_patch_path, "worktree_patch"},
    RepoRowClause{RepoRowClauseKind::payload_prefix_path, "payload_prefix"},
    RepoRowClause{RepoRowClauseKind::forced_payload_path,
                  "forced_payload.path"},
    RepoRowClause{RepoRowClauseKind::utf8, "id"},
    RepoRowClause{RepoRowClauseKind::utf8, "relpath"},
    RepoRowClause{RepoRowClauseKind::utf8, "parent_id"},
    RepoRowClause{RepoRowClauseKind::utf8, "remote"},
    RepoRowClause{RepoRowClauseKind::utf8, "remotes.name"},
    RepoRowClause{RepoRowClauseKind::utf8, "remotes.url"},
    RepoRowClause{RepoRowClauseKind::utf8, "branch"},
    RepoRowClause{RepoRowClauseKind::utf8, "eligibility.method"},
    RepoRowClause{RepoRowClauseKind::utf8, "eligibility.checked_at"},
    RepoRowClause{RepoRowClauseKind::utf8, "eligibility.proof.remote"},
    RepoRowClause{RepoRowClauseKind::utf8, "eligibility.proof.url"},
    RepoRowClause{RepoRowClauseKind::utf8, "eligibility.proof.ref"},
    RepoRowClause{RepoRowClauseKind::utf8, "local_refs.ref"},
    RepoRowClause{RepoRowClauseKind::utf8, "local_refs.proof.remote"},
    RepoRowClause{RepoRowClauseKind::utf8, "local_refs.proof.url"},
    RepoRowClause{RepoRowClauseKind::utf8, "local_refs.proof.ref"},
    RepoRowClause{RepoRowClauseKind::utf8, "local_refs_bundle"},
    RepoRowClause{RepoRowClauseKind::utf8, "staged_patch"},
    RepoRowClause{RepoRowClauseKind::utf8, "worktree_patch"},
    RepoRowClause{RepoRowClauseKind::utf8, "capture.payload_prefix"},
    RepoRowClause{RepoRowClauseKind::utf8, "forced_payload.path"},
    RepoRowClause{RepoRowClauseKind::utf8, "capture.capture_env.core_autocrlf"},
    RepoRowClause{RepoRowClauseKind::utf8, "bundle"},
    RepoRowClause{RepoRowClauseKind::sha_head_state, "sha"},
    RepoRowClause{RepoRowClauseKind::sha_hex, "sha"},
    RepoRowClause{RepoRowClauseKind::eligibility_method, "eligibility"},
    RepoRowClause{RepoRowClauseKind::eligibility_proof_tip_sha,
                  "eligibility.proof.tip_sha"},
    RepoRowClause{RepoRowClauseKind::local_refs_sha, "local_refs.sha"},
    RepoRowClause{RepoRowClauseKind::local_refs_proof_tip_sha,
                  "local_refs.proof.tip_sha"},
    RepoRowClause{RepoRowClauseKind::local_refs_proof_presence,
                  "local_refs.proof"},
    RepoRowClause{RepoRowClauseKind::shallow_eligibility, "eligibility"},
    RepoRowClause{RepoRowClauseKind::shallow_local_refs, "local_refs"},
    RepoRowClause{RepoRowClauseKind::shallow_local_refs_bundle,
                  "local_refs_bundle"},
    RepoRowClause{RepoRowClauseKind::shallow_bundle, "bundle"},
    RepoRowClause{RepoRowClauseKind::shallow_boundary_hex, "boundary"},
    RepoRowClause{RepoRowClauseKind::unborn_bundle_eligibility, "eligibility"},
    RepoRowClause{RepoRowClauseKind::unborn_bundle_result, "eligibility"},
    RepoRowClause{RepoRowClauseKind::unborn_bundle_capture_mode,
                  "capture_mode"},
    RepoRowClause{RepoRowClauseKind::born_unborn_head_result, "eligibility"},
    RepoRowClause{RepoRowClauseKind::payload_only_unborn_eligibility,
                  "eligibility"},
    RepoRowClause{RepoRowClauseKind::unborn_no_bundle_local_refs,
                  "local_refs"},
    RepoRowClause{RepoRowClauseKind::non_carried_unique, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_refs_cap, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_omitted_positive, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_omitted_max, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_refs_or_omitted, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_p1, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_ref_bytes, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_full_ref, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_catch_all, "notes"},
    RepoRowClause{RepoRowClauseKind::non_carried_strict_order, "notes"},
    RepoRowClause{RepoRowClauseKind::unknown_note_json_valid, "notes"},
    RepoRowClause{RepoRowClauseKind::unknown_note_single_value, "notes"},
    RepoRowClause{RepoRowClauseKind::unknown_note_object, "notes"},
    RepoRowClause{RepoRowClauseKind::unknown_note_kind_present, "notes"},
    RepoRowClause{RepoRowClauseKind::unknown_note_kind_string, "notes"},
    RepoRowClause{RepoRowClauseKind::local_refs_bundle_biconditional,
                  "local_refs_bundle"},
};

constexpr std::array kRepoWireClauses{
    RepoRowClause{RepoRowClauseKind::sparse_null, "sparse"},
    RepoRowClause{RepoRowClauseKind::local_refs_presence, "local_refs"},
    RepoRowClause{RepoRowClauseKind::capture_mode_presence, "capture_mode"},
};

std::optional<Violation>
manifest_path_violation(const std::filesystem::path &path,
                        const std::string_view field,
                        const bool allow_dot = false) {
  if (repo::valid_manifest_path(path, allow_dot)) {
    return std::nullopt;
  }
  if (path.empty()) {
    return Violation{field, "empty"};
  }
  if (path.is_absolute() || path.has_root_name() || path.has_root_directory()) {
    return Violation{field, "absolute"};
  }
  if (!allow_dot && path.lexically_normal() == ".") {
    return Violation{field, "dot"};
  }
  return Violation{field, "traversal"};
}

std::optional<Violation>
repo_clause_violation(const RepoRowClause clause, const RepoRowFacts &facts) {
  const auto &row = *facts.row;
  const auto invalid_utf8 = [](const std::string_view field,
                               const std::string_view value)
      -> std::optional<Violation> {
    return simdjson::validate_utf8(value) ? std::nullopt
                                          : std::optional<Violation>{
                                                Violation{field, "utf8"}};
  };
  switch (clause.kind) {
  case RepoRowClauseKind::relpath:
    return manifest_path_violation(row.relpath, clause.field, true);
  case RepoRowClauseKind::local_refs_bundle_path:
    return row.local_refs_bundle
               ? manifest_path_violation(*row.local_refs_bundle, clause.field)
               : std::nullopt;
  case RepoRowClauseKind::bundle_path:
    return row.bundle ? manifest_path_violation(*row.bundle, clause.field)
                      : std::nullopt;
  case RepoRowClauseKind::staged_patch_path:
    return row.capture.staged_patch
               ? manifest_path_violation(*row.capture.staged_patch, clause.field)
               : std::nullopt;
  case RepoRowClauseKind::worktree_patch_path:
    return row.capture.worktree_patch
               ? manifest_path_violation(*row.capture.worktree_patch,
                                         clause.field)
               : std::nullopt;
  case RepoRowClauseKind::payload_prefix_path:
    return manifest_path_violation(row.capture.payload_prefix, clause.field);
  case RepoRowClauseKind::forced_payload_path:
    for (const auto &forced : row.capture.forced_payload) {
      if (auto violation = manifest_path_violation(forced.path, clause.field)) {
        return violation;
      }
    }
    return std::nullopt;
  case RepoRowClauseKind::utf8: {
    if (clause.field == "id")
      return invalid_utf8(clause.field, row.id);
    if (clause.field == "relpath")
      return invalid_utf8(clause.field, row.relpath.generic_string());
    if (clause.field == "parent_id")
      return row.parent_id ? invalid_utf8(clause.field, *row.parent_id)
                           : std::nullopt;
    if (clause.field == "remote")
      return row.remote ? invalid_utf8(clause.field, *row.remote)
                        : std::nullopt;
    if (clause.field == "branch")
      return row.branch ? invalid_utf8(clause.field, *row.branch)
                        : std::nullopt;
    if (clause.field == "remotes.name" || clause.field == "remotes.url") {
      for (const auto &remote : row.remotes) {
        if (auto violation = invalid_utf8(
                clause.field,
                clause.field == "remotes.name" ? remote.name : remote.url))
          return violation;
      }
      return std::nullopt;
    }
    if (row.eligibility) {
      if (clause.field == "eligibility.method")
        return invalid_utf8(clause.field, row.eligibility->method);
      if (clause.field == "eligibility.checked_at")
        return invalid_utf8(clause.field, row.eligibility->checked_at);
      if (row.eligibility->proof) {
        const auto &proof = *row.eligibility->proof;
        if (clause.field == "eligibility.proof.remote")
          return invalid_utf8(clause.field, proof.remote);
        if (clause.field == "eligibility.proof.url")
          return invalid_utf8(clause.field, proof.url);
        if (clause.field == "eligibility.proof.ref")
          return invalid_utf8(clause.field, proof.ref);
      }
    }
    if (clause.field.starts_with("eligibility.")) {
      return std::nullopt;
    }
    if (clause.field.starts_with("local_refs.")) {
      for (const auto &ref : row.local_refs) {
        if (clause.field == "local_refs.ref") {
          if (auto violation = invalid_utf8(clause.field, ref.ref))
            return violation;
        }
        if (ref.proof) {
          const auto &proof = *ref.proof;
          if (clause.field == "local_refs.proof.remote") {
            if (auto violation = invalid_utf8(clause.field, proof.remote))
              return violation;
          }
          if (clause.field == "local_refs.proof.url") {
            if (auto violation = invalid_utf8(clause.field, proof.url))
              return violation;
          }
          if (clause.field == "local_refs.proof.ref") {
            if (auto violation = invalid_utf8(clause.field, proof.ref))
              return violation;
          }
        }
      }
      if (clause.field != "local_refs_bundle")
        return std::nullopt;
    }
    if (clause.field == "local_refs_bundle")
      return row.local_refs_bundle
                 ? invalid_utf8(clause.field,
                                row.local_refs_bundle->generic_string())
                 : std::nullopt;
    if (clause.field == "staged_patch")
      return row.capture.staged_patch
                 ? invalid_utf8(clause.field,
                                row.capture.staged_patch->generic_string())
                 : std::nullopt;
    if (clause.field == "worktree_patch")
      return row.capture.worktree_patch
                 ? invalid_utf8(clause.field,
                                row.capture.worktree_patch->generic_string())
                 : std::nullopt;
    if (clause.field == "capture.payload_prefix")
      return invalid_utf8(clause.field, row.capture.payload_prefix);
    if (clause.field == "forced_payload.path") {
      for (const auto &forced : row.capture.forced_payload) {
        if (auto violation =
                invalid_utf8(clause.field, forced.path.generic_string()))
          return violation;
      }
      return std::nullopt;
    }
    if (clause.field == "capture.capture_env.core_autocrlf")
      return row.capture.capture_env.core_autocrlf
                 ? invalid_utf8(clause.field,
                                *row.capture.capture_env.core_autocrlf)
                 : std::nullopt;
    if (clause.field == "bundle")
      return row.bundle
                 ? invalid_utf8(clause.field, row.bundle->generic_string())
                 : std::nullopt;
    return Violation{"repos", "unknown-utf8-coordinate"};
  }
  case RepoRowClauseKind::sha_head_state:
    return (row.head_state == HeadState::unborn) == !row.sha.has_value()
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "head-state"}};
  case RepoRowClauseKind::sha_hex:
    return !row.sha || is_hex_object_id(*row.sha)
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "hex-object-id"}};
  case RepoRowClauseKind::sparse_null:
    return !facts.sparse_present_non_null
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "null"}};
  case RepoRowClauseKind::local_refs_presence:
    return facts.local_refs_present || row.shallow || payload_only_unborn(row)
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "presence"}};
  case RepoRowClauseKind::capture_mode_presence: {
    const bool required = !row.shallow && !payload_only_unborn(row);
    return facts.capture_mode_present == required
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "presence"}};
  }
  case RepoRowClauseKind::eligibility_method:
    return !row.eligibility || row.eligibility->method == "ls-remote-ancestry"
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "method"}};
  case RepoRowClauseKind::eligibility_proof_tip_sha:
    return !row.eligibility || !row.eligibility->proof ||
                   is_hex_object_id(row.eligibility->proof->tip_sha)
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "hex-object-id"}};
  case RepoRowClauseKind::local_refs_sha:
    return std::ranges::all_of(
               row.local_refs,
               [](const auto &ref) { return is_hex_object_id(ref.sha); })
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "hex-object-id"}};
  case RepoRowClauseKind::local_refs_proof_tip_sha:
    return std::ranges::all_of(row.local_refs,
                               [](const auto &ref) {
                                 return !ref.proof ||
                                        is_hex_object_id(ref.proof->tip_sha);
                               })
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "hex-object-id"}};
  case RepoRowClauseKind::local_refs_proof_presence:
    return std::ranges::all_of(row.local_refs, [](const auto &ref) {
             return (ref.availability == RefAvailability::remote_proven) ==
                    ref.proof.has_value();
           })
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field,
                                                     "availability"}};
  case RepoRowClauseKind::shallow_eligibility:
    return !row.shallow || !row.eligibility
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "shallow"}};
  case RepoRowClauseKind::shallow_local_refs:
    return !row.shallow || row.local_refs.empty()
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "shallow"}};
  case RepoRowClauseKind::shallow_local_refs_bundle:
    return !row.shallow || !row.local_refs_bundle
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "shallow"}};
  case RepoRowClauseKind::shallow_bundle:
    return !row.shallow || !row.bundle
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field, "shallow"}};
  case RepoRowClauseKind::shallow_boundary_hex:
    return !row.shallow ||
                   std::ranges::all_of(row.shallow->boundary,
                                       is_hex_object_id)
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field,
                                                     "hex-object-id"}};
  case RepoRowClauseKind::unborn_bundle_eligibility:
    return row.head_state != HeadState::unborn || row.shallow || !row.bundle ||
                   row.eligibility
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "unborn-bundle"}};
  case RepoRowClauseKind::unborn_bundle_result:
    return row.head_state != HeadState::unborn || row.shallow || !row.bundle ||
                   !row.eligibility ||
                   row.eligibility->result == EligibilityResult::unborn_head
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "unborn-head-result"}};
  case RepoRowClauseKind::unborn_bundle_capture_mode:
    return row.head_state != HeadState::unborn || row.shallow || !row.bundle ||
                   row.capture_mode == CaptureMode::full
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "unborn-bundle-full"}};
  case RepoRowClauseKind::born_unborn_head_result:
    return row.head_state == HeadState::unborn || !row.eligibility ||
                   row.eligibility->result != EligibilityResult::unborn_head
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "born-unborn-head"}};
  case RepoRowClauseKind::payload_only_unborn_eligibility:
    return row.head_state != HeadState::unborn || row.shallow || row.bundle ||
                   !row.local_refs.empty() || !row.eligibility
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "payload-only-unborn"}};
  case RepoRowClauseKind::unborn_no_bundle_local_refs:
    return row.head_state != HeadState::unborn || row.shallow || row.bundle ||
                   row.local_refs.empty()
               ? std::nullopt
               : std::optional<Violation>{
                     Violation{clause.field, "unborn-no-bundle-local-refs"}};
  case RepoRowClauseKind::non_carried_unique: {
    const auto count = std::ranges::count_if(row.notes, [](const auto &note) {
      return std::holds_alternative<repo::NonCarriedRefsNote>(note);
    });
    return count <= 1 ? std::nullopt
                      : std::optional<Violation>{
                            Violation{clause.field, "non-carried-unique"}};
  }
  case RepoRowClauseKind::non_carried_refs_cap:
  case RepoRowClauseKind::non_carried_omitted_positive:
  case RepoRowClauseKind::non_carried_omitted_max:
  case RepoRowClauseKind::non_carried_refs_or_omitted:
  case RepoRowClauseKind::non_carried_p1:
  case RepoRowClauseKind::non_carried_ref_bytes:
  case RepoRowClauseKind::non_carried_full_ref:
  case RepoRowClauseKind::non_carried_catch_all:
  case RepoRowClauseKind::non_carried_strict_order:
    for (const auto &note : row.notes) {
      const auto *refs = std::get_if<repo::NonCarriedRefsNote>(&note);
      if (!refs) {
        continue;
      }
      if (clause.kind == RepoRowClauseKind::non_carried_refs_cap &&
          refs->refs_p1.size() > 4096U) {
        return Violation{clause.field, "refs-cap"};
      }
      if (clause.kind == RepoRowClauseKind::non_carried_omitted_positive &&
          refs->omitted_count && *refs->omitted_count == 0U) {
        return Violation{clause.field, "omitted-count"};
      }
      if (clause.kind == RepoRowClauseKind::non_carried_omitted_max &&
          refs->omitted_count &&
          *refs->omitted_count > (UINT64_C(1) << 53U) - 1U) {
        return Violation{clause.field, "omitted-count"};
      }
      if (clause.kind == RepoRowClauseKind::non_carried_refs_or_omitted &&
          refs->refs_p1.empty() && !refs->omitted_count) {
        return Violation{clause.field, "refs-or-omitted"};
      }
      std::optional<std::string> previous;
      for (const auto &encoded : refs->refs_p1) {
        auto decoded = p1_decode(encoded);
        if (clause.kind == RepoRowClauseKind::non_carried_p1 && !decoded) {
          return Violation{clause.field, "p1-decodable"};
        }
        if (!decoded) {
          continue;
        }
        if (clause.kind == RepoRowClauseKind::non_carried_ref_bytes &&
            decoded->size() > 1024U) {
          return Violation{clause.field, "ref-bytes-cap"};
        }
        if (clause.kind == RepoRowClauseKind::non_carried_full_ref &&
            !valid_full_ref_name(*decoded)) {
          return Violation{clause.field, "full-ref-name"};
        }
        if (clause.kind == RepoRowClauseKind::non_carried_catch_all &&
            !catch_all_ref(*decoded)) {
          return Violation{clause.field, "catch-all-ref"};
        }
        if (clause.kind == RepoRowClauseKind::non_carried_strict_order &&
            previous && *previous >= *decoded) {
          return Violation{clause.field, "strict-order"};
        }
        previous = std::move(*decoded);
      }
    }
    return std::nullopt;
  case RepoRowClauseKind::unknown_note_json_valid:
  case RepoRowClauseKind::unknown_note_single_value:
  case RepoRowClauseKind::unknown_note_object:
  case RepoRowClauseKind::unknown_note_kind_present:
  case RepoRowClauseKind::unknown_note_kind_string:
    for (const auto &note : row.notes) {
      const auto *unknown = std::get_if<repo::UnknownNote>(&note);
      if (!unknown) {
        continue;
      }
      simdjson::dom::parser stream_parser;
      const simdjson::padded_string stream_padded{unknown->verbatim_json};
      std::size_t document_count = 0U;
      for (auto document : stream_parser.parse_many(stream_padded)) {
        simdjson::dom::element value;
        if (document.get(value)) {
          break;
        }
        ++document_count;
      }
      simdjson::dom::parser parser;
      const simdjson::padded_string padded{unknown->verbatim_json};
      simdjson::dom::element element;
      const auto parse_error = parser.parse(padded).get(element);
      if (clause.kind == RepoRowClauseKind::unknown_note_json_valid &&
          parse_error && document_count <= 1U) {
        return Violation{clause.field, "unknown-note-json-valid"};
      }
      if (clause.kind == RepoRowClauseKind::unknown_note_single_value &&
          document_count > 1U) {
        return Violation{clause.field, "unknown-note-single-value"};
      }
      if (parse_error) {
        continue;
      }
      simdjson::dom::object object;
      const auto object_error = element.get(object);
      if (clause.kind == RepoRowClauseKind::unknown_note_object &&
          object_error) {
        return Violation{clause.field, "unknown-note-object"};
      }
      if (object_error) {
        continue;
      }
      simdjson::dom::element kind_element;
      const auto kind_error = object.at_key("kind").get(kind_element);
      if (clause.kind == RepoRowClauseKind::unknown_note_kind_present &&
          kind_error == simdjson::NO_SUCH_FIELD) {
        return Violation{clause.field, "unknown-note-kind-present"};
      }
      if (kind_error) {
        continue;
      }
      std::string_view raw_kind;
      if (clause.kind == RepoRowClauseKind::unknown_note_kind_string &&
          kind_element.get(raw_kind)) {
        return Violation{clause.field, "unknown-note-kind-string"};
      }
    }
    return std::nullopt;
  case RepoRowClauseKind::local_refs_bundle_biconditional: {
    const bool bundle_carried =
        std::ranges::any_of(row.local_refs, [](const auto &ref) {
          return ref.availability == RefAvailability::bundle_carried;
        });
    return row.local_refs_bundle.has_value() == bundle_carried
               ? std::nullopt
               : std::optional<Violation>{Violation{clause.field,
                                                     "biconditional"}};
  }
  }
  return Violation{"repos", "unknown-clause"};
}

std::optional<Violation> repo_row_violation(const RepoRowFacts &facts) {
  for (const auto clause : kRepoWireClauses) {
    if (auto violation = repo_clause_violation(clause, facts)) {
      return violation;
    }
  }
  for (const auto clause : kRepoRowClauses) {
    if (auto violation = repo_clause_violation(clause, facts)) {
      return violation;
    }
  }
  return std::nullopt;
}

enum class WriterImageExclusionKind {
  repo_kind,
  head_state,
  capture_mode,
  eligibility_result,
  ref_availability,
  forced_payload_reason,
  unknown_note_kind,
  unknown_note_alias,
};

struct WriterImageExclusion {
  WriterImageExclusionKind kind;
  std::string_view field;
};

constexpr std::array kWriterImageExclusions{
    WriterImageExclusion{WriterImageExclusionKind::repo_kind, "kind"},
    WriterImageExclusion{WriterImageExclusionKind::head_state, "head_state"},
    WriterImageExclusion{WriterImageExclusionKind::capture_mode,
                         "capture_mode"},
    WriterImageExclusion{WriterImageExclusionKind::eligibility_result,
                         "eligibility.result"},
    WriterImageExclusion{WriterImageExclusionKind::ref_availability,
                         "local_refs.availability"},
    WriterImageExclusion{WriterImageExclusionKind::forced_payload_reason,
                         "forced_payload.reason"},
    WriterImageExclusion{WriterImageExclusionKind::unknown_note_kind, "notes"},
    WriterImageExclusion{WriterImageExclusionKind::unknown_note_alias, "notes"},
};

std::optional<Violation>
writer_image_exclusion_violation(const WriterImageExclusion exclusion,
                                 const RepoEntry &entry) {
  switch (exclusion.kind) {
  case WriterImageExclusionKind::repo_kind:
    return enum_field_valid(entry.kind, kRepoKinds)
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::head_state:
    return enum_field_valid(entry.head_state, kHeadStates)
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::capture_mode:
    return entry.shallow || payload_only_unborn(entry) ||
                   enum_field_valid(entry.capture_mode, kCaptureModes)
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::eligibility_result:
    return !entry.eligibility ||
                   enum_field_valid(entry.eligibility->result,
                                    kEligibilityResults)
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::ref_availability:
    return std::ranges::all_of(entry.local_refs, [](const auto &ref) {
             return enum_field_valid(ref.availability, kRefAvailabilities);
           })
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::forced_payload_reason:
    return std::ranges::all_of(
               entry.capture.forced_payload, [](const auto &forced) {
                 return enum_field_valid(forced.reason, kForcedPayloadReasons);
               })
               ? std::nullopt
               : std::optional<Violation>{Violation{exclusion.field,
                                                     "enum-domain"}};
  case WriterImageExclusionKind::unknown_note_kind:
  case WriterImageExclusionKind::unknown_note_alias:
    for (const auto &note : entry.notes) {
      const auto *unknown = std::get_if<repo::UnknownNote>(&note);
      if (!unknown) {
        continue;
      }
      simdjson::dom::parser parser;
      const simdjson::padded_string padded{unknown->verbatim_json};
      simdjson::dom::element element;
      if (parser.parse(padded).get(element)) {
        continue;
      }
      simdjson::dom::object object;
      if (element.get(object)) {
        continue;
      }
      std::string_view raw_kind;
      if (object.at_key("kind").get(raw_kind)) {
        continue;
      }
      if (exclusion.kind == WriterImageExclusionKind::unknown_note_kind &&
          raw_kind != unknown->kind) {
        return Violation{exclusion.field, "unknown-note-kind"};
      }
      if (exclusion.kind == WriterImageExclusionKind::unknown_note_alias &&
          (raw_kind == "promisor-source" ||
           raw_kind == "non-carried-refs")) {
        return Violation{exclusion.field,
                         "unknown-note-aliases-structured"};
      }
    }
    return std::nullopt;
  }
  return Violation{"repos", "unknown-image-exclusion"};
}

std::optional<Violation> writer_image_violation(const RepoEntry &entry) {
  for (const auto exclusion : kWriterImageExclusions) {
    if (auto violation = writer_image_exclusion_violation(exclusion, entry)) {
      return violation;
    }
  }
  return std::nullopt;
}

expected<void> validate_repo_entry(const RepoEntry &entry) {
  const RepoRowFacts facts{
      .row = &entry,
      .capture_mode_present = !entry.shallow && !payload_only_unborn(entry),
      .local_refs_present = true,
      .sparse_present_non_null = false,
  };
  auto violation = writer_image_violation(entry);
  if (!violation) {
    violation = repo_row_violation(facts);
  }
  if (!violation) {
    return {};
  }
  return std::unexpected(BivError{
      ErrKind::InternalError,
      {},
      entry.id + ":" + std::string{violation->field} + ":" +
          std::string{violation->clause},
  });
}

void write_repo_entry(json::Writer &writer, const RepoEntry &entry,
                      const std::string_view raw_token_prefix,
                      std::vector<RawReplacement> &raw_replacements) {
  writer.begin_object();
  writer.key(kRepoFields.id);
  writer.value_string(entry.id);
  writer.key(kRepoFields.relpath);
  writer.value_string(entry.relpath.generic_string());
  writer.key(kRepoFields.kind);
  writer.value_string(enum_field_name(entry.kind, kRepoKinds));
  writer.key(kRepoFields.parent_id);
  write_nullable_string(writer, entry.parent_id);
  writer.key(kRepoFields.remote);
  write_nullable_string(writer, entry.remote);
  writer.key(kRepoFields.remotes);
  writer.begin_array();
  for (const auto &remote : entry.remotes) {
    writer.begin_object();
    writer.key("name");
    writer.value_string(remote.name);
    writer.key("url");
    writer.value_string(remote.url);
    writer.end_object();
  }
  writer.end_array();
  writer.key(kRepoFields.sha);
  write_nullable_string(writer, entry.sha);
  writer.key(kRepoFields.branch);
  write_nullable_string(writer, entry.branch);
  writer.key(kRepoFields.head_state);
  writer.value_string(enum_field_name(entry.head_state, kHeadStates));
  writer.key(kRepoFields.dirty);
  writer.value_bool(entry.dirty);
  if (!entry.shallow && !payload_only_unborn(entry)) {
    writer.key(kRepoFields.capture_mode);
    writer.value_string(enum_field_name(entry.capture_mode, kCaptureModes));
  }
  if (entry.eligibility) {
    writer.key(kRepoFields.eligibility);
    writer.begin_object();
    writer.key("method");
    writer.value_string(entry.eligibility->method);
    writer.key("result");
    writer.value_string(
        enum_field_name(entry.eligibility->result, kEligibilityResults));
    writer.key("checked_at");
    writer.value_string(entry.eligibility->checked_at);
    writer.key("proof");
    write_proof(writer, entry.eligibility->proof);
    writer.end_object();
  }
  writer.key(kRepoFields.local_refs);
  writer.begin_array();
  for (const auto &ref : entry.local_refs) {
    writer.begin_object();
    writer.key("ref");
    writer.value_string(ref.ref);
    writer.key("sha");
    writer.value_string(ref.sha);
    writer.key("availability");
    writer.value_string(enum_field_name(ref.availability, kRefAvailabilities));
    writer.key("proof");
    write_proof(writer, ref.proof);
    writer.end_object();
  }
  writer.end_array();
  if (entry.local_refs_bundle) {
    writer.key(kRepoFields.local_refs_bundle);
    writer.value_string(entry.local_refs_bundle->generic_string());
  }
  writer.key(kRepoFields.capture);
  writer.begin_object();
  writer.key("staged_patch");
  write_nullable_path(writer, entry.capture.staged_patch);
  writer.key("worktree_patch");
  write_nullable_path(writer, entry.capture.worktree_patch);
  writer.key("payload_prefix");
  writer.value_string(entry.capture.payload_prefix);
  writer.key("forced_payload");
  writer.begin_array();
  for (const auto &forced : entry.capture.forced_payload) {
    writer.begin_object();
    writer.key("path");
    writer.value_string(forced.path.generic_string());
    writer.key("reason");
    writer.value_string(enum_field_name(forced.reason, kForcedPayloadReasons));
    writer.end_object();
  }
  writer.end_array();
  writer.key("capture_env");
  writer.begin_object();
  writer.key("core_autocrlf");
  write_nullable_string(writer, entry.capture.capture_env.core_autocrlf);
  writer.key("core_filemode");
  if (entry.capture.capture_env.core_filemode) {
    writer.value_bool(*entry.capture.capture_env.core_filemode);
  } else {
    writer.value_null();
  }
  writer.key("sparse");
  writer.value_bool(entry.capture.capture_env.sparse);
  writer.end_object();
  writer.end_object();
  writer.key(kRepoFields.bundle);
  write_nullable_path(writer, entry.bundle);
  writer.key(kRepoFields.sparse);
  writer.value_null();
  writer.key(kRepoFields.notes);
  writer.begin_array();
  for (const auto &note : entry.notes) {
    if (const auto *refs = std::get_if<repo::NonCarriedRefsNote>(&note)) {
      writer.begin_object();
      writer.key("kind");
      writer.value_string("non-carried-refs");
      writer.key("refs");
      writer.begin_array();
      for (const auto &ref : refs->refs_p1) {
        writer.value_string(ref);
      }
      writer.end_array();
      if (refs->omitted_count) {
        writer.key("omitted_count");
        writer.value_uint(*refs->omitted_count);
      }
      writer.end_object();
    } else if (std::holds_alternative<repo::PromisorSourceNote>(note)) {
      writer.begin_object();
      writer.key("kind");
      writer.value_string("promisor-source");
      writer.end_object();
    } else {
      const auto &unknown = std::get<repo::UnknownNote>(note);
      const auto token = std::string{raw_token_prefix} +
                         std::to_string(raw_replacements.size());
      writer.value_string(token);
      raw_replacements.push_back(
          RawReplacement{.token = token, .value = unknown.verbatim_json});
    }
  }
  writer.end_array();
  if (entry.shallow) {
    writer.key(kRepoFields.shallow);
    writer.begin_object();
    writer.key("boundary");
    writer.begin_array();
    for (const auto &boundary : entry.shallow->boundary) {
      writer.value_string(boundary);
    }
    writer.end_array();
    writer.end_object();
  }
  writer.end_object();
}

std::size_t occurrence_count(const std::string_view text,
                             const std::string_view needle) {
  std::size_t count = 0U;
  std::size_t position = 0U;
  while ((position = text.find(needle, position)) != std::string_view::npos) {
    ++count;
    position += needle.size();
  }
  return count;
}

bool is_hex_object_id(const std::string_view value) {
  return value.size() == 40U &&
         std::ranges::all_of(value, [](const unsigned char ch) {
           return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') ||
                  (ch >= 'A' && ch <= 'F');
         });
}

expected<std::optional<std::string>>
required_nullable_string(simdjson::dom::object object,
                         const std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (element.is_null()) {
    return std::optional<std::string>{};
  }
  std::string_view value;
  if (const auto error = element.get(value); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<std::string>{std::string{value}};
}

expected<std::optional<std::filesystem::path>>
optional_nullable_path(simdjson::dom::object object,
                       const std::string_view key,
                       const bool allow_dot = false) {
  auto value = optional_string(object, key);
  if (!value) {
    return std::unexpected(value.error());
  }
  if (!*value) {
    return std::optional<std::filesystem::path>{};
  }
  const auto path = std::filesystem::path{**value};
  if (!repo::valid_manifest_path(path, allow_dot)) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<std::filesystem::path>{path};
}

expected<std::optional<std::filesystem::path>>
required_nullable_path(simdjson::dom::object object,
                       const std::string_view key,
                       const bool allow_dot = false) {
  auto value = required_nullable_string(object, key);
  if (!value) {
    return std::unexpected(value.error());
  }
  if (!*value) {
    return std::optional<std::filesystem::path>{};
  }
  const auto path = std::filesystem::path{**value};
  if (!repo::valid_manifest_path(path, allow_dot)) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<std::filesystem::path>{path};
}

expected<std::optional<bool>>
required_nullable_bool(simdjson::dom::object object,
                       const std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (element.is_null()) {
    return std::optional<bool>{};
  }
  bool value = false;
  if (const auto error = element.get(value); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<bool>{value};
}

expected<std::optional<repo::Proof>>
parse_optional_proof(simdjson::dom::object object, const std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element);
      error == simdjson::NO_SUCH_FIELD) {
    return std::optional<repo::Proof>{};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (element.is_null()) {
    return std::optional<repo::Proof>{};
  }
  simdjson::dom::object proof_object;
  if (const auto error = element.get(proof_object); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  auto remote = required_string(proof_object, "remote");
  auto url = required_string(proof_object, "url");
  auto ref = required_string(proof_object, "ref");
  auto tip_sha = required_string(proof_object, "tip_sha");
  if (!remote || !url || !ref || !tip_sha) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  return std::optional<repo::Proof>{repo::Proof{
      .remote = std::move(*remote),
      .url = std::move(*url),
      .ref = std::move(*ref),
      .tip_sha = std::move(*tip_sha),
  }};
}

expected<std::optional<repo::Eligibility>>
parse_optional_eligibility(simdjson::dom::object object) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(kRepoFields.eligibility).get(element);
      error == simdjson::NO_SUCH_FIELD) {
    return std::optional<repo::Eligibility>{};
  } else if (error || element.is_null()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eligibility"});
  }
  simdjson::dom::object eligibility_object;
  if (const auto error = element.get(eligibility_object); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eligibility"});
  }
  auto method = required_string(eligibility_object, "method");
  auto result_text = required_string(eligibility_object, "result");
  auto checked_at = required_string(eligibility_object, "checked_at");
  auto proof = parse_optional_proof(eligibility_object, "proof");
  if (!method || !result_text || !checked_at || !proof) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eligibility"});
  }
  auto result =
      parse_enum_field(*result_text, "eligibility", kEligibilityResults);
  if (!result) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eligibility"});
  }
  return std::optional<repo::Eligibility>{repo::Eligibility{
      .method = std::move(*method),
      .result = *result,
      .checked_at = std::move(*checked_at),
      .proof = std::move(*proof),
  }};
}

expected<std::vector<repo::Remote>>
parse_remotes(simdjson::dom::object object) {
  simdjson::dom::array array;
  if (const auto error = object.at_key(kRepoFields.remotes).get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "remotes"});
  }
  std::vector<repo::Remote> remotes;
  for (const auto element : array) {
    simdjson::dom::object remote_object;
    if (const auto error = element.get(remote_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "remotes"});
    }
    auto name = required_string(remote_object, "name");
    auto url = required_string(remote_object, "url");
    if (!name || !url) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "remotes"});
    }
    remotes.push_back(
        repo::Remote{.name = std::move(*name), .url = std::move(*url)});
  }
  return remotes;
}

expected<std::vector<repo::LocalRef>>
parse_local_refs(simdjson::dom::object object) {
  simdjson::dom::array array;
  if (const auto error = object.at_key(kRepoFields.local_refs).get(array);
      error == simdjson::NO_SUCH_FIELD) {
    return std::vector<repo::LocalRef>{};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "local_refs"});
  }
  std::vector<repo::LocalRef> refs;
  for (const auto element : array) {
    simdjson::dom::object ref_object;
    if (const auto error = element.get(ref_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "local_refs"});
    }
    auto ref = required_string(ref_object, "ref");
    auto sha = required_string(ref_object, "sha");
    auto availability_text = required_string(ref_object, "availability");
    auto proof = parse_optional_proof(ref_object, "proof");
    if (!ref || !sha || !availability_text || !proof) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "local_refs"});
    }
    auto availability =
        parse_enum_field(*availability_text, "local_refs", kRefAvailabilities);
    if (!availability) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "local_refs"});
    }
    refs.push_back(repo::LocalRef{.ref = std::move(*ref),
                                  .sha = std::move(*sha),
                                  .availability = *availability,
                                  .proof = std::move(*proof)});
  }
  return refs;
}

expected<repo::Capture> parse_capture(simdjson::dom::object object) {
  auto capture_object_result = required_object(object, kRepoFields.capture);
  if (!capture_object_result) {
    return std::unexpected(capture_object_result.error());
  }
  const auto capture_object = *capture_object_result;
  auto staged_patch = required_nullable_path(capture_object, "staged_patch");
  auto worktree_patch =
      required_nullable_path(capture_object, "worktree_patch");
  auto payload_prefix = required_string(capture_object, "payload_prefix");
  if (!staged_patch) {
    return std::unexpected(staged_patch.error());
  }
  if (!worktree_patch) {
    return std::unexpected(worktree_patch.error());
  }
  if (!payload_prefix ||
      !repo::valid_manifest_path(std::filesystem::path{*payload_prefix})) {
    return std::unexpected(
        BivError{ErrKind::ParseError, {}, "payload_prefix"});
  }

  simdjson::dom::array forced_array;
  if (const auto error =
          capture_object.at_key("forced_payload").get(forced_array);
      error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "forced_payload"});
  }
  std::vector<repo::ForcedPayload> forced_payload;
  for (const auto element : forced_array) {
    simdjson::dom::object forced_object;
    if (const auto error = element.get(forced_object); error) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "forced_payload"});
    }
    auto path = required_string(forced_object, "path");
    auto reason_text = required_string(forced_object, "reason");
    if (!path ||
        !repo::valid_manifest_path(std::filesystem::path{*path})) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "path"});
    }
    if (!reason_text) {
      return std::unexpected(
          BivError{ErrKind::ParseError, {}, "forced_payload"});
    }
    auto reason =
        parse_enum_field(*reason_text, "forced_payload", kForcedPayloadReasons);
    if (!reason) {
      return std::unexpected(reason.error());
    }
    forced_payload.push_back(repo::ForcedPayload{
        .path = std::filesystem::path{*path}, .reason = *reason});
  }

  auto capture_env_result = required_object(capture_object, "capture_env");
  if (!capture_env_result) {
    return std::unexpected(capture_env_result.error());
  }
  const auto capture_env_object = *capture_env_result;
  auto core_autocrlf =
      required_nullable_string(capture_env_object, "core_autocrlf");
  auto core_filemode =
      required_nullable_bool(capture_env_object, "core_filemode");
  auto sparse = required_bool(capture_env_object, "sparse");
  if (!core_autocrlf || !core_filemode || !sparse) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "capture_env"});
  }
  return repo::Capture{
      .staged_patch = std::move(*staged_patch),
      .worktree_patch = std::move(*worktree_patch),
      .payload_prefix = std::move(*payload_prefix),
      .forced_payload = std::move(forced_payload),
      .capture_env =
          repo::CaptureEnvironment{
              .core_autocrlf = std::move(*core_autocrlf),
              .core_filemode = std::move(*core_filemode),
              .sparse = *sparse,
          },
  };
}

expected<std::optional<repo::Shallow>>
parse_optional_shallow(simdjson::dom::object object) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(kRepoFields.shallow).get(element);
      error == simdjson::NO_SUCH_FIELD) {
    return std::optional<repo::Shallow>{};
  } else if (error || element.is_null()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "shallow"});
  }
  simdjson::dom::object shallow_object;
  if (const auto error = element.get(shallow_object); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "shallow"});
  }
  auto boundary = required_string_array(shallow_object, "boundary");
  if (!boundary) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "boundary"});
  }
  return std::optional<repo::Shallow>{
      repo::Shallow{.boundary = std::move(*boundary)}};
}

expected<std::string> p1_decode(const std::string_view encoded) {
  auto lower_hex = [](const char ch) -> std::optional<unsigned char> {
    if (ch >= '0' && ch <= '9') {
      return static_cast<unsigned char>(ch - '0');
    }
    if (ch >= 'a' && ch <= 'f') {
      return static_cast<unsigned char>(10 + ch - 'a');
    }
    return std::nullopt;
  };
  std::string decoded;
  for (std::size_t i = 0; i < encoded.size();) {
    const auto ch = static_cast<unsigned char>(encoded.at(i));
    if (ch != '\\') {
      if (ch < 0x20U || ch > 0x7eU) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
      }
      decoded.push_back(static_cast<char>(ch));
      ++i;
      continue;
    }
    if (i + 1U >= encoded.size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    if (encoded.at(i + 1U) == '\\') {
      decoded.push_back('\\');
      i += 2U;
      continue;
    }
    if (encoded.at(i + 1U) != 'x' || i + 3U >= encoded.size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    const auto high = lower_hex(encoded.at(i + 2U));
    const auto low = lower_hex(encoded.at(i + 3U));
    if (!high || !low) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    const auto octet = static_cast<unsigned char>((*high << 4U) | *low);
    if (octet >= 0x20U && octet <= 0x7eU) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    decoded.push_back(static_cast<char>(octet));
    i += 4U;
  }
  return decoded;
}

bool valid_full_ref_name(const std::string_view ref) {
  if (!ref.starts_with("refs/") || ref.size() <= 5U || ref.ends_with('/') ||
      ref.ends_with('.') || ref.ends_with(".lock") ||
      ref.find("..") != std::string_view::npos ||
      ref.find("@{") != std::string_view::npos ||
      ref.find("//") != std::string_view::npos) {
    return false;
  }
  std::size_t component_begin = 0U;
  while (component_begin < ref.size()) {
    const auto component_end = ref.find('/', component_begin);
    const auto component =
        ref.substr(component_begin, component_end == std::string_view::npos
                                        ? std::string_view::npos
                                        : component_end - component_begin);
    if (component.empty() || component.starts_with('.') ||
        component.ends_with(".lock")) {
      return false;
    }
    if (component_end == std::string_view::npos) {
      break;
    }
    component_begin = component_end + 1U;
  }
  return std::ranges::none_of(ref, [](const unsigned char ch) {
    return ch <= 0x20U || ch == 0x7fU || ch == '~' || ch == '^' || ch == ':' ||
           ch == '?' || ch == '*' || ch == '[' || ch == '\\';
  });
}

bool catch_all_ref(const std::string_view ref) {
  return !ref.starts_with("refs/heads/") && !ref.starts_with("refs/tags/") &&
         !ref.starts_with("refs/remotes/") && ref != "refs/stash";
}

std::vector<std::vector<std::string>>
raw_repo_note_values(const std::string_view text) {
  simdjson::ondemand::parser parser;
  simdjson::padded_string padded{text.data(), text.size()};
  auto document = parser.iterate(padded);
  std::vector<std::vector<std::string>> rows;
  simdjson::ondemand::array repo_array;
  if (const auto error =
          document.find_field_unordered("repos").get(repo_array);
      error) {
    throw simdjson::simdjson_error{error};
  }
  for (auto repo_value : repo_array) {
    std::vector<std::string> notes;
    auto repo_object = repo_value.get_object();
    simdjson::ondemand::array note_array;
    if (const auto error =
            repo_object.find_field_unordered("notes").get(note_array);
        error) {
      throw simdjson::simdjson_error{error};
    }
    for (auto note_value : note_array) {
      std::string_view raw;
      if (const auto error = note_value.raw_json().get(raw); error) {
        throw simdjson::simdjson_error{error};
      }
      while (!raw.empty() && (raw.back() == ' ' || raw.back() == '\t' ||
                              raw.back() == '\r' || raw.back() == '\n')) {
        raw.remove_suffix(1U);
      }
      notes.emplace_back(raw);
    }
    rows.push_back(std::move(notes));
  }
  return rows;
}

expected<std::vector<repo::RepoNote>>
parse_notes(simdjson::dom::object object) {
  simdjson::dom::array array;
  if (const auto error = object.at_key(kRepoFields.notes).get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
  }
  std::vector<repo::RepoNote> notes;
  for (const auto element : array) {
    simdjson::dom::object note_object;
    if (const auto error = element.get(note_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    auto kind = required_string(note_object, "kind");
    if (!kind) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    if (*kind == "promisor-source") {
      notes.emplace_back(repo::PromisorSourceNote{});
      continue;
    }
    if (*kind != "non-carried-refs") {
      notes.emplace_back(repo::UnknownNote{
          .kind = std::move(*kind),
          .verbatim_json = simdjson::to_string(element),
      });
      continue;
    }
    auto refs_p1 = required_string_array(note_object, "refs");
    if (!refs_p1) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    std::optional<std::uint64_t> omitted_count;
    simdjson::dom::element omitted_element;
    if (const auto error =
            note_object.at_key("omitted_count").get(omitted_element);
        !error) {
      std::uint64_t value = 0U;
      if (const auto value_error = omitted_element.get(value); value_error) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
      }
      omitted_count = value;
    } else if (error != simdjson::NO_SUCH_FIELD) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
    }
    notes.emplace_back(repo::NonCarriedRefsNote{
        .refs_p1 = std::move(*refs_p1), .omitted_count = omitted_count});
  }
  return notes;
}

expected<RepoEntry> parse_repo_entry(simdjson::dom::object object) {
  auto id = required_string(object, kRepoFields.id);
  auto relpath = required_string(object, kRepoFields.relpath);
  auto kind_text = required_string(object, kRepoFields.kind);
  auto parent_id = required_nullable_string(object, kRepoFields.parent_id);
  auto remote = required_nullable_string(object, kRepoFields.remote);
  auto remotes = parse_remotes(object);
  auto sha = required_nullable_string(object, kRepoFields.sha);
  auto branch = required_nullable_string(object, kRepoFields.branch);
  auto head_state_text = required_string(object, kRepoFields.head_state);
  auto dirty = required_bool(object, kRepoFields.dirty);
  if (!id || !relpath || !kind_text || !parent_id || !remote || !remotes ||
      !sha || !branch || !head_state_text || !dirty) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "repos"});
  }
  if (!repo::valid_manifest_path(std::filesystem::path{*relpath}, true)) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "relpath"});
  }
  auto kind = parse_enum_field(*kind_text, "kind", kRepoKinds);
  auto head_state =
      parse_enum_field(*head_state_text, "head_state", kHeadStates);
  if (!kind || !head_state) {
    return std::unexpected(!kind ? kind.error() : head_state.error());
  }
  std::optional<CaptureMode> capture_mode;
  simdjson::dom::element capture_mode_element;
  if (const auto error =
          object.at_key(kRepoFields.capture_mode).get(capture_mode_element);
      !error) {
    if (capture_mode_element.is_null()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "capture_mode"});
    }
    std::string_view mode_text;
    if (const auto value_error = capture_mode_element.get(mode_text);
        value_error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "capture_mode"});
    }
    auto parsed_mode =
        parse_enum_field(mode_text, "capture_mode", kCaptureModes);
    if (!parsed_mode) {
      return std::unexpected(parsed_mode.error());
    }
    capture_mode = *parsed_mode;
  } else if (error != simdjson::NO_SUCH_FIELD) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "capture_mode"});
  }

  auto eligibility = parse_optional_eligibility(object);
  auto local_refs = parse_local_refs(object);
  simdjson::dom::element local_refs_element;
  const bool local_refs_present =
      object.at_key(kRepoFields.local_refs).get(local_refs_element) !=
      simdjson::NO_SUCH_FIELD;
  auto local_refs_bundle =
      optional_nullable_path(object, kRepoFields.local_refs_bundle);
  auto capture = parse_capture(object);
  auto bundle = optional_nullable_path(object, kRepoFields.bundle);
  auto shallow = parse_optional_shallow(object);
  auto notes = parse_notes(object);
  if (!eligibility || !local_refs || !local_refs_bundle || !capture ||
      !bundle || !shallow || !notes) {
    if (!eligibility)
      return std::unexpected(eligibility.error());
    if (!local_refs)
      return std::unexpected(local_refs.error());
    if (!local_refs_bundle)
      return std::unexpected(local_refs_bundle.error());
    if (!capture)
      return std::unexpected(capture.error());
    if (!bundle)
      return std::unexpected(bundle.error());
    if (!shallow)
      return std::unexpected(shallow.error());
    return std::unexpected(notes.error());
  }

  simdjson::dom::element sparse_element;
  const auto sparse_error =
      object.at_key(kRepoFields.sparse).get(sparse_element);
  const bool sparse_present_non_null =
      sparse_error != simdjson::NO_SUCH_FIELD &&
      (sparse_error || !sparse_element.is_null());

  RepoEntry entry;
  entry.id = std::move(*id);
  entry.relpath = std::filesystem::path{*relpath};
  entry.kind = *kind;
  entry.parent_id = std::move(*parent_id);
  entry.remote = std::move(*remote);
  entry.remotes = std::move(*remotes);
  entry.sha = std::move(*sha);
  entry.branch = std::move(*branch);
  entry.head_state = *head_state;
  entry.dirty = *dirty;
  entry.capture_mode = capture_mode.value_or(CaptureMode::full);
  entry.promisor = false;
  entry.eligibility = std::move(*eligibility);
  entry.local_refs = std::move(*local_refs);
  entry.local_refs_bundle = std::move(*local_refs_bundle);
  entry.capture = std::move(*capture);
  entry.bundle = std::move(*bundle);
  entry.shallow = std::move(*shallow);
  entry.sparse = nullptr;
  entry.notes = std::move(*notes);
  entry.engine_source = std::nullopt;
  if (const auto violation = repo_row_violation(RepoRowFacts{
          .row = &entry,
          .capture_mode_present = capture_mode.has_value(),
          .local_refs_present = local_refs_present,
          .sparse_present_non_null = sparse_present_non_null,
      })) {
    const bool legacy_eligibility_detail =
        violation->clause == "unborn-bundle-full" ||
        violation->clause == "method" ||
        (violation->clause == "hex-object-id" &&
         violation->field.starts_with("eligibility")) ||
        violation->clause == "unborn-no-bundle-local-refs";
    const bool legacy_local_refs_detail =
        violation->field == "local_refs.sha" ||
        violation->field == "local_refs.proof" ||
        violation->field == "local_refs.proof.tip_sha";
    const auto detail = legacy_eligibility_detail
                            ? std::string{"eligibility"}
                            : legacy_local_refs_detail
                                  ? std::string{"local_refs"}
                                  : std::string{violation->field};
    return std::unexpected(BivError{ErrKind::ParseError, {}, detail});
  }
  return entry;
}

expected<std::vector<RepoEntry>>
parse_repo_entries(simdjson::dom::object object) {
  simdjson::dom::array array;
  if (const auto error = object.at_key("repos").get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "repos"});
  }
  std::vector<RepoEntry> entries;
  for (const auto element : array) {
    simdjson::dom::object repo_object;
    if (const auto error = element.get(repo_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "repos"});
    }
    auto entry = parse_repo_entry(repo_object);
    if (!entry) {
      return std::unexpected(entry.error());
    }
    entries.push_back(std::move(*entry));
  }
  return entries;
}

} // namespace

std::optional<PathFlavor> classify_absolute(const std::string_view path) {
  const auto root = classify_carrier_root(path);
  return root ? std::optional<PathFlavor>{root->flavor} : std::nullopt;
}

bool packer_home_valid(const PackerHome& value) {
  const auto root = classify_carrier_root(value.path);
  return root && root->flavor == value.flavor &&
         value.path.size() > root->root_length;
}

std::optional<PackerHome> make_packer_home(const std::string_view path) {
  const auto flavor = classify_absolute(path);
  if (!flavor) {
    return std::nullopt;
  }
  PackerHome value{.path = std::string{path}, .flavor = *flavor};
  return packer_home_valid(value) ? std::optional<PackerHome>{std::move(value)}
                                  : std::nullopt;
}

std::string to_string(const PathFlavor flavor) {
  switch (flavor) {
    case PathFlavor::posix:
      return "posix";
    case PathFlavor::windows:
      return "windows";
    case PathFlavor::wsl:
      return "wsl";
  }
  return "posix";
}

expected<PathFlavor> parse_path_flavor(const std::string_view value) {
  if (value == "posix") {
    return PathFlavor::posix;
  }
  if (value == "windows") {
    return PathFlavor::windows;
  }
  if (value == "wsl") {
    return PathFlavor::wsl;
  }
  return std::unexpected(BivError{ErrKind::ParseError, {}, "source_path_flavor"});
}

expected<std::string> serialize(const Manifest& manifest) {
  for (const auto &entry : manifest.repos) {
    if (auto valid = validate_repo_entry(entry); !valid) {
      return std::unexpected(valid.error());
    }
  }
  for (std::uint64_t nonce = 0U;; ++nonce) {
    const auto raw_token_prefix =
        "__biv_repo_unknown_note_" + std::to_string(nonce) + "_";
    std::vector<RawReplacement> raw_replacements;
    json::Writer writer;
    writer.begin_object();
    writer.key("format_version");
    writer.value_int(manifest.format_version);
    writer.key("required_capabilities");
    writer.begin_array();
    for (const auto &capability : manifest.required_capabilities) {
      writer.value_string(capability);
    }
    writer.end_array();
    writer.key("image_id");
    writer.value_string(manifest.image_id);
    writer.key("app_version");
    writer.value_string(manifest.app_version.empty() ? app_version()
                                                     : manifest.app_version);
    writer.key("created_at");
    writer.value_string(manifest.created_at);
    writer.key("source_path");
    writer.value_string(manifest.source_path);
    writer.key("source_path_flavor");
    writer.value_string(to_string(manifest.source_path_flavor));
    if (manifest.packer_home && packer_home_valid(*manifest.packer_home)) {
      writer.key("packer_home");
      writer.value_string(manifest.packer_home->path);
      writer.key("packer_home_flavor");
      writer.value_string(to_string(manifest.packer_home->flavor));
    }
    writer.key("bivignore");
    writer.begin_object();
    writer.key("source");
    writer.value_string(manifest.bivignore.source);
    writer.key("builtin_id");
    if (manifest.bivignore.builtin_id.has_value()) {
      writer.value_string(*manifest.bivignore.builtin_id);
    } else {
      writer.value_null();
    }
    writer.key("sha256");
    writer.value_string(manifest.bivignore.sha256_hex);
    writer.end_object();
    writer.key("repos");
    writer.begin_array();
    for (const auto &entry : manifest.repos) {
      write_repo_entry(writer, entry, raw_token_prefix, raw_replacements);
    }
    writer.end_array();
    writer.key("agent_sessions");
    writer.begin_array();
    for (const auto &entry : manifest.agent_sessions) {
      write_agent_session(writer, entry);
    }
    writer.end_array();
    writer.end_object();
    auto result = writer.take();
    bool unique_tokens = true;
    for (const auto &replacement : raw_replacements) {
      const auto quoted = "\"" + replacement.token + "\"";
      if (occurrence_count(result, quoted) != 1U) {
        unique_tokens = false;
        break;
      }
    }
    if (!unique_tokens) {
      continue;
    }
    for (auto &replacement : raw_replacements) {
      const auto quoted = "\"" + replacement.token + "\"";
      replacement.offset = result.find(quoted);
    }
    std::ranges::sort(raw_replacements,
                      [](const auto &left, const auto &right) {
                        return left.offset > right.offset;
                      });
    for (const auto &replacement : raw_replacements) {
      const auto quoted = "\"" + replacement.token + "\"";
      result.replace(replacement.offset, quoted.size(), replacement.value);
    }
    return result;
  }
}

expected<Manifest> parse(const std::span<const std::byte> bytes) {
  if (bytes.empty() || bytes.size() > kManifestByteCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "manifest-size"});
  }

  try {
    std::string text;
    text.reserve(bytes.size());
    for (const std::byte byte : bytes) {
      text.push_back(static_cast<char>(byte));
    }
    if (!starts_with_json_object(text)) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "root"});
    }

    simdjson::padded_string padded{text.data(), text.size()};
    if (padded.data() == nullptr) {
      return std::unexpected(BivError{ErrKind::InternalError, {}, "manifest-alloc"});
    }
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (const auto error = parser.parse(padded).get(root); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, error_message(error)});
    }
    simdjson::dom::object object;
    if (const auto error = root.get(object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "root"});
    }

    Manifest manifest;
    auto version = required_int(object, "format_version");
    if (!version) {
      return std::unexpected(version.error());
    }
    manifest.format_version = *version;

    auto capabilities = required_string_array(object, "required_capabilities");
    if (!capabilities) {
      return std::unexpected(capabilities.error());
    }
    manifest.required_capabilities = std::move(*capabilities);

    auto image_id = required_string(object, "image_id");
    auto app_version_value = required_string(object, "app_version");
    auto created_at = required_string(object, "created_at");
    auto source_path = required_string(object, "source_path");
    auto source_flavor = required_string(object, "source_path_flavor");
    if (!image_id || !app_version_value || !created_at || !source_path || !source_flavor) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "manifest-field"});
    }
    manifest.image_id = std::move(*image_id);
    manifest.app_version = std::move(*app_version_value);
    manifest.created_at = std::move(*created_at);
    manifest.source_path = std::move(*source_path);
    auto flavor = parse_path_flavor(*source_flavor);
    if (!flavor) {
      return std::unexpected(flavor.error());
    }
    manifest.source_path_flavor = *flavor;

    auto packer_home_text = optional_string(object, "packer_home");
    if (!packer_home_text) {
      return std::unexpected(packer_home_text.error());
    }
    auto packer_home_flavor_text = optional_string(object, "packer_home_flavor");
    if (!packer_home_flavor_text) {
      return std::unexpected(packer_home_flavor_text.error());
    }
    if (packer_home_text->has_value() != packer_home_flavor_text->has_value()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "packer_home_flavor"});
    }
    if (packer_home_text->has_value()) {
      auto packer_home_flavor = parse_path_flavor(**packer_home_flavor_text);
      if (!packer_home_flavor) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "packer_home_flavor"});
      }
      PackerHome value{.path = std::move(**packer_home_text), .flavor = *packer_home_flavor};
      if (!packer_home_valid(value)) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "packer_home"});
      }
      manifest.packer_home = std::move(value);
    }

    simdjson::dom::object bivignore;
    if (const auto error = object.at_key("bivignore").get(bivignore); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "bivignore"});
    }
    auto bivignore_source = required_string(bivignore, "source");
    auto bivignore_sha = required_string(bivignore, "sha256");
    if (!bivignore_source || !bivignore_sha) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "bivignore-field"});
    }
    manifest.bivignore.source = std::move(*bivignore_source);
    manifest.bivignore.sha256_hex = std::move(*bivignore_sha);
    simdjson::dom::element builtin_id;
    if (const auto error = bivignore.at_key("builtin_id").get(builtin_id); !error) {
      if (builtin_id.is_null()) {
        manifest.bivignore.builtin_id = std::nullopt;
      } else {
        std::string_view value;
        if (const auto string_error = builtin_id.get(value); string_error) {
          return std::unexpected(BivError{ErrKind::ParseError, {}, "builtin_id"});
        }
        manifest.bivignore.builtin_id = std::string{value};
      }
    } else if (error != simdjson::NO_SUCH_FIELD) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "builtin_id"});
    }

    auto repos = parse_repo_entries(object);
    if (!repos) {
      return std::unexpected(repos.error());
    }
    const auto raw_notes = raw_repo_note_values(text);
    if (raw_notes.size() != repos->size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "repos"});
    }
    for (std::size_t repo_index = 0; repo_index < repos->size(); ++repo_index) {
      if (raw_notes.at(repo_index).size() !=
          repos->at(repo_index).notes.size()) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "notes"});
      }
      for (std::size_t note_index = 0;
           note_index < repos->at(repo_index).notes.size(); ++note_index) {
        if (auto *unknown = std::get_if<repo::UnknownNote>(
                &repos->at(repo_index).notes.at(note_index))) {
          unknown->verbatim_json = raw_notes.at(repo_index).at(note_index);
        }
      }
    }
    manifest.repos = std::move(*repos);
    auto sessions = parse_agent_sessions(object);
    if (!sessions) {
      return std::unexpected(sessions.error());
    }
    manifest.agent_sessions = std::move(*sessions);

    return manifest;
  } catch (const simdjson::simdjson_error& error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, error.what()});
  } catch (...) {
    return std::unexpected(BivError{ErrKind::InternalError, {}, "manifest-parse"});
  }
}

}  // namespace biv::manifest
