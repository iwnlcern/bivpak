#include "adapters/codex/codex.hpp"

#include <algorithm>
#include <charconv>
#include <cerrno>
#include <cstdint>
#include <cstring>
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

#include <sqlite3.h>
#include <unistd.h>

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

struct RolloutFacts {
  std::optional<std::string> id;
  std::optional<std::string> cwd;
  std::optional<std::string> cli_version;
  std::optional<std::string> parent_id;
  std::string newest_timestamp;
  fs::file_time_type mtime{};
};

struct TimestampKey {
  enum class Kind { iso_utc, integer } kind{Kind::iso_utc};
  std::string whole;
  std::string fraction;
  std::int64_t integer{};
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
  bool live_at_pack{true};
  std::optional<TimestampKey> newest_timestamp;
  std::optional<TimestampKey> db_updated_at;
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

std::optional<std::string> terminal_tail_type(
    const std::string_view rollout) {
  if (rollout.empty()) {
    return std::nullopt;
  }
  std::size_t record_end = rollout.size();
  if (rollout.back() == '\n') {
    --record_end;
  }
  const auto delimiter =
      record_end == 0U ? std::string_view::npos
                       : rollout.rfind('\n', record_end - 1U);
  const auto record_start =
      delimiter == std::string_view::npos ? 0U : delimiter + 1U;
  const auto record =
      rollout.substr(record_start, record_end - record_start);

  simdjson::padded_string padded{record};
  simdjson::dom::parser parser;
  auto object = parse_json_object(parser, padded);
  if (!object) {
    return std::nullopt;
  }
  auto type = object_string(*object, "type");
  if (!type || (*type != "task_complete" && *type != "turn_aborted" &&
                *type != "thread_rolled_back")) {
    return std::nullopt;
  }
  return type;
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

std::optional<TimestampKey> timestamp_key(const std::string_view value) {
  std::int64_t integer = 0;
  const auto integer_result = std::from_chars(value.begin(), value.end(), integer);
  if (integer_result.ec == std::errc{} &&
      integer_result.ptr == value.end()) {
    return TimestampKey{.kind = TimestampKey::Kind::integer,
                        .whole = {},
                        .fraction = {},
                        .integer = integer};
  }
  if (value.size() < 20U || value.back() != 'Z' || value.at(4) != '-' ||
      value.at(7) != '-' || value.at(10) != 'T' || value.at(13) != ':' ||
      value.at(16) != ':') {
    return std::nullopt;
  }
  for (std::size_t index = 0; index < 19U; ++index) {
    if (index == 4U || index == 7U || index == 10U || index == 13U ||
        index == 16U) {
      continue;
    }
    if (value.at(index) < '0' || value.at(index) > '9') {
      return std::nullopt;
    }
  }
  std::string fraction;
  if (value.size() > 20U) {
    if (value.at(19) != '.') {
      return std::nullopt;
    }
    fraction = std::string{value.substr(20, value.size() - 21U)};
    if (fraction.empty() ||
        !std::ranges::all_of(fraction, [](const char character) {
          return character >= '0' && character <= '9';
        })) {
      return std::nullopt;
    }
    while (!fraction.empty() && fraction.back() == '0') {
      fraction.pop_back();
    }
  }
  return TimestampKey{.kind = TimestampKey::Kind::iso_utc,
                      .whole = std::string{value.substr(0, 19)},
                      .fraction = std::move(fraction),
                      .integer = 0};
}

std::optional<int> compare_timestamp(const std::optional<TimestampKey>& lhs,
                                     const std::optional<TimestampKey>& rhs) {
  if (!lhs.has_value() || !rhs.has_value() || lhs->kind != rhs->kind) {
    return std::nullopt;
  }
  if (lhs->kind == TimestampKey::Kind::integer) {
    return lhs->integer < rhs->integer ? -1 : lhs->integer > rhs->integer ? 1 : 0;
  }
  if (lhs->whole != rhs->whole) {
    return lhs->whole < rhs->whole ? -1 : 1;
  }
  const auto width = std::max(lhs->fraction.size(), rhs->fraction.size());
  for (std::size_t index = 0; index < width; ++index) {
    const char left = index < lhs->fraction.size() ? lhs->fraction.at(index) : '0';
    const char right = index < rhs->fraction.size() ? rhs->fraction.at(index) : '0';
    if (left != right) {
      return left < right ? -1 : 1;
    }
  }
  return 0;
}

std::optional<TimestampKey> newest_rollout_timestamp(
    const std::string_view rollout) {
  std::optional<TimestampKey> newest;
  std::istringstream input{std::string{rollout}};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    auto object = parse_json_object(parser, padded);
    if (!object) {
      continue;
    }
    if (auto timestamp = object_string(*object, "timestamp"); timestamp.has_value()) {
      auto candidate = timestamp_key(*timestamp);
      const auto order = compare_timestamp(candidate, newest);
      if (candidate.has_value() && (!newest.has_value() ||
                                    (order.has_value() && *order > 0))) {
        newest = std::move(candidate);
      }
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
    case DiscoveryTier::env:
      return 0;
    case DiscoveryTier::defaults:
      return 1;
    case DiscoveryTier::config:
      return 2;
    case DiscoveryTier::explicit_flag:
      return 3;
  }
  return 3;
}

bool better_candidate(const Candidate& candidate, const Candidate& current) {
  if (const auto order = compare_timestamp(candidate.newest_timestamp,
                                            current.newest_timestamp);
      order.has_value() && *order != 0) {
    return *order > 0;
  }
  if (const auto order = compare_timestamp(candidate.db_updated_at,
                                            current.db_updated_at);
      order.has_value() && *order != 0) {
    return *order > 0;
  }
  if (candidate.mtime != current.mtime) {
    return candidate.mtime > current.mtime;
  }
  if (tier_rank(candidate.store.tier) != tier_rank(current.store.tier)) {
    return tier_rank(candidate.store.tier) < tier_rank(current.store.tier);
  }
  if (candidate.store.root.generic_string() != current.store.root.generic_string()) {
    return candidate.store.root.generic_string() < current.store.root.generic_string();
  }
  return candidate.source.path.generic_string() < current.source.path.generic_string();
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
  const bool live_at_pack =
      candidate.live_at_pack ||
      std::ranges::any_of(children, &Candidate::live_at_pack);
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
      .live_at_pack = live_at_pack};
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
                         .notes = {{
                             "picker_gap",
                             "session may not appear in the default picker until first opened by id"}}}};
    value.caveat_facts.relocated_contents.push_back("sessions");
    value.caveat_facts.relocated_contents.insert(
        value.caveat_facts.relocated_contents.end(), value.never_collect.begin(),
        value.never_collect.end());
    return value;
  }();
  return inventory;
}

int toml_hex_value(const char value) {
  if (value >= '0' && value <= '9') return value - '0';
  if (value >= 'a' && value <= 'f') return value - 'a' + 10;
  if (value >= 'A' && value <= 'F') return value - 'A' + 10;
  return -1;
}

void append_toml_utf8(std::string& output, const std::uint32_t codepoint) {
  if (codepoint <= 0x7fU) {
    output.push_back(static_cast<char>(codepoint));
  } else if (codepoint <= 0x7ffU) {
    output.push_back(static_cast<char>(0xc0U | (codepoint >> 6U)));
    output.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
  } else if (codepoint <= 0xffffU) {
    output.push_back(static_cast<char>(0xe0U | (codepoint >> 12U)));
    output.push_back(static_cast<char>(0x80U | ((codepoint >> 6U) & 0x3fU)));
    output.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
  } else {
    output.push_back(static_cast<char>(0xf0U | (codepoint >> 18U)));
    output.push_back(static_cast<char>(0x80U | ((codepoint >> 12U) & 0x3fU)));
    output.push_back(static_cast<char>(0x80U | ((codepoint >> 6U) & 0x3fU)));
    output.push_back(static_cast<char>(0x80U | (codepoint & 0x3fU)));
  }
}

struct TomlString {
  std::string value;
  std::size_t next{};
};

std::optional<TomlString> parse_toml_string(const std::string_view text,
                                            const std::size_t start) {
  if (start >= text.size() || (text.at(start) != '"' && text.at(start) != '\'')) {
    return std::nullopt;
  }
  const char quote = text.at(start);
  std::string value;
  for (std::size_t index = start + 1U; index < text.size(); ++index) {
    const char character = text.at(index);
    if (character == quote) {
      return TomlString{.value = std::move(value), .next = index + 1U};
    }
    if (quote == '\'' || character != '\\') {
      value.push_back(character);
      continue;
    }
    if (++index >= text.size()) return std::nullopt;
    const char escaped = text.at(index);
    switch (escaped) {
      case '"': value.push_back('"'); break;
      case '\\': value.push_back('\\'); break;
      case 'b': value.push_back('\b'); break;
      case 't': value.push_back('\t'); break;
      case 'n': value.push_back('\n'); break;
      case 'f': value.push_back('\f'); break;
      case 'r': value.push_back('\r'); break;
      case 'u':
      case 'U': {
        const std::size_t digits = escaped == 'u' ? 4U : 8U;
        if (index + digits >= text.size()) return std::nullopt;
        std::uint32_t codepoint = 0;
        for (std::size_t offset = 1U; offset <= digits; ++offset) {
          const int digit = toml_hex_value(text.at(index + offset));
          if (digit < 0) return std::nullopt;
          codepoint = (codepoint << 4U) | static_cast<std::uint32_t>(digit);
        }
        if (codepoint > 0x10ffffU ||
            (codepoint >= 0xd800U && codepoint <= 0xdfffU)) {
          return std::nullopt;
        }
        append_toml_utf8(value, codepoint);
        index += digits;
        break;
      }
      default: return std::nullopt;
    }
  }
  return std::nullopt;
}

std::optional<std::size_t> toml_equals(const std::string_view line,
                                       const std::size_t start) {
  char quote = '\0';
  bool escaped = false;
  for (std::size_t index = start; index < line.size(); ++index) {
    const char character = line.at(index);
    if (quote != '\0') {
      if (quote == '"' && !escaped && character == '\\') {
        escaped = true;
      } else if (!escaped && character == quote) {
        quote = '\0';
      } else {
        escaped = false;
      }
    } else if (character == '"' || character == '\'') {
      quote = character;
    } else if (character == '=') {
      return index;
    }
  }
  return std::nullopt;
}

std::optional<std::string> parse_toml_key(const std::string_view text) {
  const auto first = text.find_first_not_of(" \t");
  if (first == std::string_view::npos) return std::nullopt;
  const auto last = text.find_last_not_of(" \t");
  if (text.at(first) == '"' || text.at(first) == '\'') {
    auto parsed = parse_toml_string(text, first);
    if (!parsed.has_value() || parsed->next - 1U != last) return std::nullopt;
    return std::move(parsed->value);
  }
  const auto key = text.substr(first, last - first + 1U);
  if (!std::ranges::all_of(key, [](const char character) {
        return (character >= 'A' && character <= 'Z') ||
               (character >= 'a' && character <= 'z') ||
               (character >= '0' && character <= '9') || character == '_' ||
               character == '-';
      })) {
    return std::nullopt;
  }
  return std::string{key};
}

std::optional<std::string> config_string(const fs::path& path,
                                         const std::string_view wanted_key) {
  std::ifstream input{path};
  std::string line;
  bool in_table = false;
  bool found = false;
  std::optional<std::string> result;
  while (std::getline(input, line)) {
    if (line.ends_with('\r')) {
      line.pop_back();
    }
    const auto first = line.find_first_not_of(" \t");
    if (first == std::string::npos || line.at(first) == '#') {
      continue;
    }
    if (line.at(first) == '[') {
      in_table = true;
      continue;
    }
    if (in_table) {
      continue;
    }
    const auto equals = toml_equals(line, first);
    if (!equals.has_value()) {
      continue;
    }
    auto key = parse_toml_key(std::string_view{line}.substr(first, *equals - first));
    if (!key.has_value() || *key != wanted_key) {
      continue;
    }
    const auto value_start = line.find_first_not_of(" \t", *equals + 1U);
    if (found || value_start == std::string::npos) {
      return std::nullopt;
    }
    auto parsed = parse_toml_string(line, value_start);
    if (!parsed.has_value()) {
      return std::nullopt;
    }
    const auto trailing = line.find_first_not_of(" \t", parsed->next);
    if (trailing != std::string::npos && line.at(trailing) != '#') {
      return std::nullopt;
    }
    result = std::move(parsed->value);
    found = true;
  }
  return result;
}

class TemporaryDatabaseCopy {
 public:
  TemporaryDatabaseCopy() = default;
  ~TemporaryDatabaseCopy() {
    if (!path_.empty()) {
      ::unlink(path_.c_str());
    }
  }
  TemporaryDatabaseCopy(const TemporaryDatabaseCopy&) = delete;
  TemporaryDatabaseCopy& operator=(const TemporaryDatabaseCopy&) = delete;
  TemporaryDatabaseCopy(TemporaryDatabaseCopy&&) = delete;
  TemporaryDatabaseCopy& operator=(TemporaryDatabaseCopy&&) = delete;

  fs::path path_;
};

std::optional<std::map<std::string, TimestampKey>> thread_updates(
    const fs::path& database_path) {
  auto source = secure_io::open_read_no_follow(database_path);
  if (!source) {
    return std::nullopt;
  }
  std::string pattern =
      (fs::temp_directory_path() / "bivpak-codex-state-XXXXXX").string();
  std::vector<char> mutable_pattern(pattern.begin(), pattern.end());
  mutable_pattern.push_back('\0');
  const int output = ::mkstemp(mutable_pattern.data());
  if (output < 0) {
    return std::nullopt;
  }
  TemporaryDatabaseCopy copy;
  copy.path_ = mutable_pattern.data();
  auto copied = source->stream([&](std::span<const std::byte> bytes) -> expected<void> {
    while (!bytes.empty()) {
      const auto count = ::write(output, bytes.data(), bytes.size());
      if (count < 0) {
        if (errno == EINTR) continue;
        return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, {}, errno});
      }
      bytes = bytes.subspan(static_cast<std::size_t>(count));
    }
    return {};
  });
  const int close_result = ::close(output);
  if (!copied || close_result != 0) {
    return std::nullopt;
  }

  sqlite3* raw_database = nullptr;
  if (sqlite3_open_v2(copy.path_.c_str(), &raw_database,
                      SQLITE_OPEN_READONLY | SQLITE_OPEN_NOMUTEX, nullptr) !=
      SQLITE_OK) {
    if (raw_database != nullptr) sqlite3_close(raw_database);
    return std::nullopt;
  }
  sqlite3_stmt* statement = nullptr;
  if (sqlite3_prepare_v2(raw_database, "SELECT id, updated_at FROM threads", -1,
                         &statement, nullptr) != SQLITE_OK) {
    sqlite3_close(raw_database);
    return std::nullopt;
  }
  std::map<std::string, TimestampKey> updates;
  int step = SQLITE_ROW;
  while ((step = sqlite3_step(statement)) == SQLITE_ROW) {
    const auto sqlite_text = [&](const int column) -> std::optional<std::string> {
      const auto* data = sqlite3_column_text(statement, column);
      if (data == nullptr) return std::nullopt;
      const auto size = static_cast<std::size_t>(sqlite3_column_bytes(statement, column));
      std::string text;
      text.reserve(size);
      for (const unsigned char byte : std::span{data, size}) {
        text.push_back(static_cast<char>(byte));
      }
      return text;
    };
    const auto id = sqlite_text(0);
    const auto updated = sqlite_text(1);
    if (!id.has_value() || !updated.has_value()) continue;
    if (auto key = timestamp_key(*updated); key.has_value()) {
      updates.emplace(*id, std::move(*key));
    }
  }
  sqlite3_finalize(statement);
  sqlite3_close(raw_database);
  if (step != SQLITE_DONE) {
    return std::nullopt;
  }
  return updates;
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
        std::optional<fs::path> database_path;
        for (const auto& locator : store.locators) {
          if (locator.kind == "sqlite_home" &&
              fs::exists(locator.path / "state_5.sqlite", ec)) {
            database_path = locator.path / "state_5.sqlite";
            break;
          }
        }
        if (!database_path.has_value() &&
            fs::exists(store.root / "state_5.sqlite", ec)) {
          database_path = store.root / "state_5.sqlite";
        }
        std::map<std::string, TimestampKey> db_updates;
        if (database_path.has_value()) {
          auto loaded = thread_updates(*database_path);
          if (loaded.has_value()) {
            db_updates = std::move(*loaded);
          } else {
            db_warnings.push_back({
                store.root.generic_string(),
                "CodexDbEnrichmentSkipped:" + database_path->generic_string()});
          }
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
            const auto db_update = db_updates.find(*facts.id);
            grouped[*facts.id].push_back(Candidate{
                .store = store,
                .source = std::move(*source),
                .id = *facts.id,
                .cwd = *facts.cwd,
                .normalized_path_key = rewrite::normalized_path_key(*facts.cwd),
                .path_flavor = rewrite::path_flavor_for(*facts.cwd),
                .cli_version = facts.cli_version.value_or("unknown"),
                .parent_id = std::move(facts.parent_id),
                .live_at_pack = !has_terminal_tail_record(*text),
                .newest_timestamp = newest_rollout_timestamp(*text),
                .db_updated_at = db_update == db_updates.end()
                                     ? std::nullopt
                                     : std::optional<TimestampKey>{
                                           db_update->second},
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

bool has_terminal_tail_record(const std::string_view rollout) {
  return terminal_tail_type(rollout).has_value();
}

const AgentAdapter& codex_adapter() {
  static const CodexAdapter adapter;
  return adapter;
}

}  // namespace biv::adapters
