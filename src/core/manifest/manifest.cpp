#include "core/manifest/manifest.hpp"

#include <cstdint>
#include <limits>
#include <set>
#include <string_view>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include "core/json/writer.hpp"
#include "core/support/version.hpp"

namespace biv::manifest {

namespace {

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

expected<void> require_empty_array(simdjson::dom::object object, std::string_view key) {
  simdjson::dom::element element;
  if (const auto error = object.at_key(key).get(element); error == simdjson::NO_SUCH_FIELD) {
    return {};
  } else if (error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }

  simdjson::dom::array array;
  if (const auto error = element.get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{key}});
  }
  if (array.size() != 0U) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "step2-plain-dir-only"});
  }
  return {};
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

bool is_ascii_alpha(const char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

struct AgentIdView {
  std::string_view value;
};

bool artifact_path_ok(AgentIdView agent, std::string_view path) {
  if (path.empty() || path.front() == '/' || path.find('\\') != std::string_view::npos) {
    return false;
  }
  if (path.size() >= 2 && is_ascii_alpha(path.at(0)) && path.at(1) == ':') {
    return false;
  }

  std::string prefix = "agents/";
  prefix += agent.value;
  prefix += '/';
  if (!path.starts_with(prefix)) {
    return false;
  }

  const std::string_view rest = path.substr(prefix.size());
  if (rest.empty()) {
    return false;
  }

  bool first_segment = true;
  size_t start = 0;
  while (start <= rest.size()) {
    const size_t slash = rest.find('/', start);
    const size_t end = slash == std::string_view::npos ? rest.size() : slash;
    const std::string_view segment = rest.substr(start, end - start);
    if (segment.empty() || segment == "." || segment == "..") {
      return false;
    }
    if (first_segment && segment.find(':') != std::string_view::npos) {
      return false;
    }
    if (slash == std::string_view::npos) {
      break;
    }
    first_segment = false;
    start = slash + 1;
  }
  return true;
}

expected<void> validate_artifacts(std::string_view agent, const std::vector<std::string>& artifacts) {
  for (const auto& artifact : artifacts) {
    if (!artifact_path_ok(AgentIdView{agent}, artifact)) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "artifact-prefix"});
    }
  }
  return {};
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

expected<std::vector<SessionChild>> parse_session_children(simdjson::dom::object object, std::string_view agent) {
  simdjson::dom::array array;
  if (const auto error = object.at_key("children").get(array); error) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
  }

  std::vector<SessionChild> out;
  for (auto element : array) {
    simdjson::dom::object child_object;
    if (const auto error = element.get(child_object); error) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
    }
    auto original_id = required_string(child_object, "original_id");
    auto artifacts = required_string_array(child_object, "artifacts");
    if (!original_id || !artifacts) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "children"});
    }
    auto valid = validate_artifacts(agent, *artifacts);
    if (!valid) {
      return std::unexpected(valid.error());
    }
    out.push_back(SessionChild{.original_id = std::move(*original_id), .artifacts = std::move(*artifacts)});
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
  if (entry.entry_schema > 1) {
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
  if (primary->empty() || (parent_in_image->has_value() && (!parent->has_value() || **parent_in_image))) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "session-ids"});
  }
  entry.original_session_ids = {
      .primary = std::move(*primary), .parent = std::move(*parent), .parent_in_image = *parent_in_image};

  auto children = parse_session_children(object, entry.agent);
  auto artifacts = required_string_array(object, "artifacts");
  auto live_at_pack = required_bool(object, "live_at_pack");
  auto imported_at = required_string(object, "imported_at");
  if (!children || !artifacts || !live_at_pack || !imported_at) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "agent-session-field"});
  }
  auto valid = validate_artifacts(entry.agent, *artifacts);
  if (!valid) {
    return std::unexpected(valid.error());
  }
  if (artifacts->empty()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "artifacts-empty"});
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
  writer.value_int(entry.entry_schema);
  writer.end_object();
}

}  // namespace

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

std::string serialize(const Manifest& manifest) {
  json::Writer writer;
  writer.begin_object();
  writer.key("format_version");
  writer.value_int(manifest.format_version);
  writer.key("required_capabilities");
  writer.begin_array();
  for (const auto& capability : manifest.required_capabilities) {
    writer.value_string(capability);
  }
  writer.end_array();
  writer.key("image_id");
  writer.value_string(manifest.image_id);
  writer.key("app_version");
  writer.value_string(manifest.app_version.empty() ? app_version() : manifest.app_version);
  writer.key("created_at");
  writer.value_string(manifest.created_at);
  writer.key("source_path");
  writer.value_string(manifest.source_path);
  writer.key("source_path_flavor");
  writer.value_string(to_string(manifest.source_path_flavor));
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
  writer.end_array();
  writer.key("agent_sessions");
  writer.begin_array();
  for (const auto& entry : manifest.agent_sessions) {
    write_agent_session(writer, entry);
  }
  writer.end_array();
  writer.end_object();
  return writer.take();
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

    auto repos = require_empty_array(object, "repos");
    if (!repos) {
      return std::unexpected(repos.error());
    }
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
