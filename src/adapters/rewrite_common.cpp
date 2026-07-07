#include "adapters/rewrite_common.hpp"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <optional>
#include <string>
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

namespace biv::adapters::rewrite {

namespace {

enum class SpellingKind { literal, wsl_lower, windows_backslash, windows_slash };

struct Spelling {
  std::string value;
  SpellingKind kind{SpellingKind::literal};
};

struct ReplacementText {
  std::string_view from;
  std::string_view to;
};

struct Haystack {
  std::string_view value;
};

struct Needle {
  std::string_view value;
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

bool wsl_mount_path(const std::string_view path) {
  return path.size() >= 7 && path.starts_with("/mnt/") && path.at(6) == '/' && ascii_alpha(path.at(5));
}

bool windows_drive_path(const std::string_view path) {
  return path.size() >= 3 && ascii_alpha(path.at(0)) && path.at(1) == ':' &&
         (path.at(2) == '\\' || path.at(2) == '/');
}

std::string ascii_lower(std::string value) {
  for (char& character : value) {
    if (character >= 'A' && character <= 'Z') {
      character = static_cast<char>(character - 'A' + 'a');
    }
  }
  return value;
}

char ascii_upper(const char value) {
  if (value >= 'a' && value <= 'z') {
    return static_cast<char>(value - 'a' + 'A');
  }
  return value;
}

void append_unique(std::vector<Spelling>& values, Spelling spelling) {
  const auto found = std::ranges::find_if(values, [&](const Spelling& existing) {
    return existing.value == spelling.value;
  });
  if (found == values.end()) {
    values.push_back(std::move(spelling));
  }
}

std::string windows_from_wsl(const std::string_view path, const char separator) {
  std::string out;
  out.push_back(ascii_upper(path.at(5)));
  out += ':';
  out.push_back(separator);
  for (const char character : path.substr(7)) {
    out.push_back(character == '/' ? separator : character);
  }
  return out;
}

std::string wsl_from_windows(const std::string_view path) {
  std::string out = "/mnt/";
  out.push_back(ascii_lower(std::string{path.substr(0, 1)}).front());
  out.push_back('/');
  for (const char character : path.substr(3)) {
    out.push_back(character == '\\' ? '/' : character);
  }
  return out;
}

std::string swap_windows_separator(std::string path, const char separator) {
  for (char& character : path) {
    if (character == '\\' || character == '/') {
      character = separator;
    }
  }
  return path;
}

std::vector<Spelling> origin_spellings(const std::string_view original_path,
                                       const manifest::PathFlavor original_flavor) {
  std::vector<Spelling> out;
  if ((original_flavor == manifest::PathFlavor::windows || windows_drive_path(original_path)) &&
      windows_drive_path(original_path)) {
    append_unique(out, Spelling{.value = swap_windows_separator(std::string{original_path}, '\\'),
                                .kind = SpellingKind::windows_backslash});
    append_unique(out, Spelling{.value = swap_windows_separator(std::string{original_path}, '/'),
                                .kind = SpellingKind::windows_slash});
    append_unique(out, Spelling{.value = wsl_from_windows(original_path), .kind = SpellingKind::literal});
    return out;
  }
  append_unique(out, Spelling{.value = std::string{original_path}, .kind = SpellingKind::literal});
  if ((original_flavor == manifest::PathFlavor::wsl || wsl_mount_path(original_path)) &&
      wsl_mount_path(original_path)) {
    append_unique(out, Spelling{.value = ascii_lower(std::string{original_path}), .kind = SpellingKind::wsl_lower});
    append_unique(out,
                  Spelling{.value = windows_from_wsl(original_path, '\\'), .kind = SpellingKind::windows_backslash});
    append_unique(out, Spelling{.value = windows_from_wsl(original_path, '/'), .kind = SpellingKind::windows_slash});
  }
  return out;
}

std::string target_for_spelling(const SpellingKind kind,
                                const std::string_view target_path,
                                const manifest::PathFlavor target_flavor) {
  if (target_flavor != manifest::PathFlavor::wsl || !wsl_mount_path(target_path)) {
    return std::string{target_path};
  }
  switch (kind) {
    case SpellingKind::wsl_lower:
      return ascii_lower(std::string{target_path});
    case SpellingKind::windows_backslash:
      return windows_from_wsl(target_path, '\\');
    case SpellingKind::windows_slash:
      return windows_from_wsl(target_path, '/');
    case SpellingKind::literal:
      break;
  }
  return std::string{target_path};
}

void append_unique_pair(ReplacementPairs& pairs, std::pair<std::string, std::string> pair) {
  const auto found = std::ranges::find(pairs, pair);
  if (found == pairs.end()) {
    pairs.push_back(std::move(pair));
  }
}

void replace_all(std::string& text, const ReplacementText replacement) {
  if (replacement.from.empty()) {
    return;
  }
  size_t pos = 0;
  while ((pos = text.find(replacement.from, pos)) != std::string::npos) {
    text.replace(pos, replacement.from.size(), replacement.to);
    pos += replacement.to.size();
  }
}

std::string apply_replacements(std::string value,
                               const PathPairsView pair_set,
                               const IdPairsView id_map) {
  for (const auto& pair : pair_set.values) {
    replace_all(value, ReplacementText{.from = pair.first, .to = pair.second});
  }
  for (const auto& pair : id_map.values) {
    replace_all(value, ReplacementText{.from = pair.first, .to = pair.second});
  }
  return value;
}

bool valid_utf8(const std::string_view text) {
  size_t index = 0;
  while (index < text.size()) {
    const auto byte = static_cast<unsigned char>(text.at(index));
    if (byte == 0U) {
      return false;
    }
    size_t needed = 0;
    if (byte <= 0x7FU) {
      ++index;
      continue;
    }
    if (byte >= 0xC2U && byte <= 0xDFU) {
      needed = 1;
    } else if (byte >= 0xE0U && byte <= 0xEFU) {
      needed = 2;
    } else if (byte >= 0xF0U && byte <= 0xF4U) {
      needed = 3;
    } else {
      return false;
    }
    if (index + needed >= text.size()) {
      return false;
    }
    for (size_t offset = 1; offset <= needed; ++offset) {
      const auto continuation = static_cast<unsigned char>(text.at(index + offset));
      if ((continuation & 0xC0U) != 0x80U) {
        return false;
      }
    }
    index += needed + 1;
  }
  return true;
}

void write_element(json::Writer& writer,
                   simdjson::dom::element element,
                   const PathPairsView pair_set,
                   const IdPairsView id_map) {
  switch (element.type()) {
    case simdjson::dom::element_type::ARRAY: {
      simdjson::dom::array array;
      if (element.get(array)) {
        writer.value_null();
        return;
      }
      writer.begin_array();
      for (auto item : array) {
        write_element(writer, item, pair_set, id_map);
      }
      writer.end_array();
      return;
    }
    case simdjson::dom::element_type::OBJECT: {
      simdjson::dom::object object;
      if (element.get(object)) {
        writer.value_null();
        return;
      }
      writer.begin_object();
      for (auto field : object) {
        writer.key(field.key);
        write_element(writer, field.value, pair_set, id_map);
      }
      writer.end_object();
      return;
    }
    case simdjson::dom::element_type::INT64: {
      int64_t value = 0;
      if (element.get(value)) {
        writer.value_null();
      } else {
        writer.value_int(value);
      }
      return;
    }
    case simdjson::dom::element_type::UINT64: {
      uint64_t value = 0;
      if (element.get(value) || value > static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
        writer.value_null();
      } else {
        writer.value_int(static_cast<int64_t>(value));
      }
      return;
    }
    case simdjson::dom::element_type::DOUBLE:
      writer.value_null();
      return;
    case simdjson::dom::element_type::STRING: {
      std::string_view value;
      if (element.get(value)) {
        writer.value_null();
      } else {
        writer.value_string(apply_replacements(std::string{value}, pair_set, id_map));
      }
      return;
    }
    case simdjson::dom::element_type::BOOL: {
      bool value = false;
      if (element.get(value)) {
        writer.value_null();
      } else {
        writer.value_bool(value);
      }
      return;
    }
    case simdjson::dom::element_type::NULL_VALUE:
      writer.value_null();
      return;
  }
  writer.value_null();
}

size_t count_hits(const Haystack haystack, const Needle needle) {
  if (needle.value.empty()) {
    return 0;
  }
  size_t hits = 0;
  size_t pos = 0;
  while ((pos = haystack.value.find(needle.value, pos)) != std::string_view::npos) {
    ++hits;
    pos += needle.value.size();
  }
  return hits;
}

}  // namespace

ReplacementPairs derive_pair_set(const std::string_view original_path,
                                  const manifest::PathFlavor original_flavor,
                                  const std::string_view target_path,
                                  const manifest::PathFlavor target_flavor) {
  ReplacementPairs pairs;
  for (const auto& spelling : origin_spellings(original_path, original_flavor)) {
    append_unique_pair(pairs, {spelling.value, target_for_spelling(spelling.kind, target_path, target_flavor)});
  }
  return pairs;
}

RewriteLineResult rewrite_jsonl_line(const std::string_view line,
                                      const PathPairsView pair_set,
                                      const IdPairsView id_map) {
  if (!valid_utf8(line)) {
    return RewriteLineResult{.line = std::string{line}, .skipped_non_utf8 = true};
  }
  simdjson::padded_string padded{line};
  simdjson::dom::parser parser;
  simdjson::dom::element root;
  if (parser.parse(padded).get(root)) {
    return RewriteLineResult{.line = std::string{line}};
  }
  json::Writer writer;
  write_element(writer, root, pair_set, id_map);
  std::string out = writer.take();
  if (!out.empty() && out.back() == '\n') {
    out.pop_back();
  }
  return RewriteLineResult{.line = std::move(out)};
}

InstallVerify verify_scan(const std::span<const std::byte> artifact_bytes,
                          const OriginPathsView pair_set_origins,
                          const OriginIdsView origin_ids) {
  std::string content;
  content.reserve(artifact_bytes.size());
  for (const std::byte value : artifact_bytes) {
    content.push_back(static_cast<char>(value));
  }
  InstallVerify verify;
  verify.artifacts_checked = 1;
  for (const auto& origin : pair_set_origins.values) {
    verify.origin_path_hits += count_hits(Haystack{content}, Needle{origin});
  }
  for (const auto& id : origin_ids.values) {
    verify.origin_id_hits += count_hits(Haystack{content}, Needle{id});
  }
  return verify;
}

std::vector<std::string> origins_from_pairs(const std::span<const std::pair<std::string, std::string>> pair_set) {
  std::vector<std::string> origins;
  for (const auto& pair : pair_set) {
    if (std::ranges::find(origins, pair.first) == origins.end()) {
      origins.push_back(pair.first);
    }
  }
  return origins;
}

}  // namespace biv::adapters::rewrite
