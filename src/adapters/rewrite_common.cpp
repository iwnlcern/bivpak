#include "adapters/rewrite_common.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <limits>
#include <optional>
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

bool windows_extended_path(const std::string_view path) {
  return path.starts_with("\\\\?\\") || path.starts_with("//?/");
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

struct CanonicalPath {
  manifest::PathFlavor flavor{manifest::PathFlavor::posix};
  bool drive_mapped{false};
  std::vector<std::string> segments;
};

bool case_insensitive(const manifest::PathFlavor flavor) {
  return flavor == manifest::PathFlavor::windows ||
         flavor == manifest::PathFlavor::wsl;
}

bool append_segment(CanonicalPath& path, std::string segment) {
  if (segment.empty() || segment == ".") {
    return true;
  }
  if (segment == "..") {
    if (path.segments.empty()) {
      return false;
    }
    path.segments.pop_back();
    return true;
  }
  if (case_insensitive(path.flavor)) {
    segment = ascii_lower(std::move(segment));
  }
  path.segments.push_back(std::move(segment));
  return true;
}

std::optional<CanonicalPath> canonical_path(const std::string_view input) {
  CanonicalPath out{
      .flavor = path_flavor_for(input), .drive_mapped = false, .segments = {}};
  std::string text{input};
  size_t start = 0;
  if (out.flavor == manifest::PathFlavor::windows) {
    if (windows_extended_path(text)) {
      text.erase(0, 4);
    }
    text = swap_windows_separator(std::move(text), '/');
    if (windows_drive_path(text)) {
      out.drive_mapped = true;
      if (!append_segment(out, text.substr(0, 1))) {
        return std::nullopt;
      }
      start = 3;
    }
  } else if (out.flavor == manifest::PathFlavor::wsl) {
    out.drive_mapped = true;
    if (!append_segment(out, text.substr(5, 1))) {
      return std::nullopt;
    }
    start = 7;
  }

  while (start <= text.size()) {
    const size_t slash = text.find('/', start);
    const size_t end = slash == std::string::npos ? text.size() : slash;
    if (!append_segment(out, text.substr(start, end - start))) {
      return std::nullopt;
    }
    if (slash == std::string::npos) {
      break;
    }
    start = slash + 1U;
  }
  return out;
}

bool compatible_flavors(const CanonicalPath& lhs, const CanonicalPath& rhs) {
  if (lhs.flavor == rhs.flavor) {
    return true;
  }
  const bool wsl_windows_pair = (lhs.flavor == manifest::PathFlavor::wsl &&
                                 rhs.flavor == manifest::PathFlavor::windows) ||
                                (lhs.flavor == manifest::PathFlavor::windows &&
                                 rhs.flavor == manifest::PathFlavor::wsl);
  return wsl_windows_pair && lhs.drive_mapped && rhs.drive_mapped;
}

std::vector<Spelling> origin_spellings(
    const std::string_view original_path,
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

bool path_token_char(const char value) {
  return ascii_alpha(value) || (value >= '0' && value <= '9') || value == '_' ||
         value == '-' || value == '.' || value == ':' || value == '/' ||
         value == '\\';
}

bool path_replacement_boundary_ok(const std::string_view text, const size_t pos,
                                  const size_t match_size) {
  if (pos > 0U && path_token_char(text.at(pos - 1U))) {
    return false;
  }
  const size_t after = pos + match_size;
  if (after >= text.size()) {
    return true;
  }
  const char next = text.at(after);
  return next == '/' || next == '\\' || !path_token_char(next);
}

void replace_path_all(std::string& text, const ReplacementText replacement) {
  if (replacement.from.empty()) {
    return;
  }
  size_t pos = 0;
  while ((pos = text.find(replacement.from, pos)) != std::string::npos) {
    if (!path_replacement_boundary_ok(text, pos, replacement.from.size())) {
      pos += replacement.from.size();
      continue;
    }
    text.replace(pos, replacement.from.size(), replacement.to);
    pos += replacement.to.size();
  }
}

std::string apply_replacements(std::string value, const PathPairsView pair_set,
                               const IdPairsView id_map) {
  for (const auto& pair : pair_set.values) {
    replace_path_all(value,
                     ReplacementText{.from = pair.first, .to = pair.second});
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

class RewriteWriter {
 public:
  void begin_object() { begin_value(); out_.push_back('{'); frames_.push_back({true, true, false}); }
  void end_object() { end_container('}', true); }
  void begin_array() { begin_value(); out_.push_back('['); frames_.push_back({false, true, false}); }
  void end_array() { end_container(']', false); }
  void key(const std::string_view value) {
    before_item();
    write_string(value);
    out_ += ": ";
    frames_.back().pending_key = true;
  }
  void value_string(const std::string_view value) { begin_value(); write_string(value); end_value(); }
  void value_int(const std::int64_t value) { value_number(value); }
  void value_uint(const std::uint64_t value) { value_number(value); }
  void value_double(const double value) {
    begin_value();
    std::array<char, 64> buffer{};
    const auto result = std::to_chars(buffer.begin(), buffer.end(),
                                      value, std::chars_format::general,
                                      std::numeric_limits<double>::max_digits10);
    if (result.ec != std::errc{} || !std::isfinite(value)) {
      out_ += "null";
    } else {
      out_.append(buffer.data(), result.ptr);
    }
    end_value();
  }
  void value_bool(const bool value) { begin_value(); out_ += value ? "true" : "false"; end_value(); }
  void value_null() { begin_value(); out_ += "null"; end_value(); }
  std::string take() { out_.push_back('\n'); return std::move(out_); }

 private:
  struct Frame { bool object; bool first; bool pending_key; };

  template <typename Integer>
  void value_number(const Integer value) {
    begin_value();
    std::array<char, 32> buffer{};
    const auto result = std::to_chars(buffer.begin(), buffer.end(), value);
    out_.append(buffer.data(), result.ptr);
    end_value();
  }
  void begin_value() {
    if (frames_.empty()) return;
    if (frames_.back().object) return;
    before_item();
  }
  void end_value() {
    if (!frames_.empty() && frames_.back().object) frames_.back().pending_key = false;
  }
  void before_item() {
    auto& frame = frames_.back();
    if (!frame.first) out_.push_back(',');
    out_.push_back('\n');
    out_.append(frames_.size() * 2U, ' ');
    frame.first = false;
  }
  void end_container(const char close, const bool object) {
    const auto frame = frames_.back();
    frames_.pop_back();
    if (!frame.first) {
      out_.push_back('\n');
      out_.append(frames_.size() * 2U, ' ');
    }
    out_.push_back(close);
    if (!frames_.empty() && frames_.back().object) frames_.back().pending_key = false;
    (void)object;
  }
  void write_string(const std::string_view value) {
    constexpr std::string_view hex = "0123456789ABCDEF";
    out_.push_back('"');
    for (const unsigned char character : value) {
      if (character == '"' || character == '\\') {
        out_.push_back('\\');
        out_.push_back(static_cast<char>(character));
      } else if (character < 0x20U) {
        out_ += "\\u00";
        out_.push_back(hex.at(character >> 4U));
        out_.push_back(hex.at(character & 0x0FU));
      } else {
        out_.push_back(static_cast<char>(character));
      }
    }
    out_.push_back('"');
  }

  std::string out_;
  std::vector<Frame> frames_;
};

void write_element(RewriteWriter& writer,
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
      if (element.get(value)) {
        writer.value_null();
      } else {
        writer.value_uint(value);
      }
      return;
    }
    case simdjson::dom::element_type::DOUBLE: {
      double value = 0.0;
      if (element.get(value)) {
        writer.value_null();
      } else {
        writer.value_double(value);
      }
      return;
    }
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

std::string string_from_bytes(const std::span<const std::byte> bytes) {
  std::string out;
  out.reserve(bytes.size());
  for (const std::byte value : bytes) {
    out.push_back(static_cast<char>(value));
  }
  return out;
}

size_t count_hits_bytes(const std::span<const std::byte> haystack,
                        const Needle needle) {
  if (needle.value.empty()) {
    return 0;
  }
  size_t hits = 0;
  for (size_t pos = 0; pos + needle.value.size() <= haystack.size(); ++pos) {
    bool matched = true;
    size_t offset = 0;
    for (const std::byte value : haystack.subspan(pos, needle.value.size())) {
      if (static_cast<char>(value) != needle.value.at(offset)) {
        matched = false;
        break;
      }
      ++offset;
    }
    if (matched) {
      ++hits;
      pos += needle.value.size() - 1U;
    }
  }
  return hits;
}

}  // namespace

manifest::PathFlavor path_flavor_for(const std::string_view path) {
  if (wsl_mount_path(path)) {
    return manifest::PathFlavor::wsl;
  }
  if (windows_drive_path(path) || windows_extended_path(path)) {
    return manifest::PathFlavor::windows;
  }
  return manifest::PathFlavor::posix;
}

std::string normalized_path_key(const std::string_view path) {
  const auto flavor = path_flavor_for(path);
  if (flavor == manifest::PathFlavor::wsl) {
    return ascii_lower(std::string{path});
  }
  if (flavor != manifest::PathFlavor::windows) {
    return std::string{path};
  }
  std::string normalized{path};
  if (windows_extended_path(normalized)) {
    normalized.erase(0, 4);
  }
  normalized = ascii_lower(swap_windows_separator(std::move(normalized), '/'));
  while (normalized.size() > 3U && normalized.ends_with('/')) {
    normalized.pop_back();
  }
  return normalized;
}

bool path_is_same_or_descendant(const PathMembership membership) {
  const auto candidate_path = canonical_path(membership.candidate);
  const auto root_path = canonical_path(membership.root);
  if (!candidate_path.has_value() || !root_path.has_value() ||
      !compatible_flavors(*candidate_path, *root_path) ||
      candidate_path->segments.size() < root_path->segments.size()) {
    return false;
  }
  for (size_t i = 0; i < root_path->segments.size(); ++i) {
    if (root_path->segments.at(i) != candidate_path->segments.at(i)) {
      return false;
    }
  }
  return true;
}

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
  RewriteWriter writer;
  write_element(writer, root, pair_set, id_map);
  std::string out = writer.take();
  if (!out.empty() && out.back() == '\n') {
    out.pop_back();
  }
  return RewriteLineResult{.line = std::move(out)};
}

RewriteBytesResult rewrite_jsonl_bytes(const std::span<const std::byte> bytes,
                                       const PathPairsView pair_set,
                                       const IdPairsView id_map) {
  const std::string input_storage = string_from_bytes(bytes);
  const std::string_view input{input_storage};
  std::string output;
  output.reserve(input.size());
  size_t skipped_non_utf8 = 0;
  size_t start = 0;
  while (start < input.size()) {
    const size_t newline = input.find('\n', start);
    const size_t end =
        newline == std::string_view::npos ? input.size() : newline;
    const std::string_view line = input.substr(start, end - start);
    auto rewritten = rewrite_jsonl_line(line, pair_set, id_map);
    if (rewritten.skipped_non_utf8) {
      ++skipped_non_utf8;
    }
    output += rewritten.line;
    if (newline == std::string_view::npos) {
      break;
    }
    output.push_back('\n');
    start = newline + 1U;
  }

  RewriteBytesResult result{.bytes = {}, .skipped_non_utf8 = skipped_non_utf8};
  result.bytes.reserve(output.size());
  for (const char value : output) {
    result.bytes.push_back(static_cast<std::byte>(value));
  }
  return result;
}

InstallVerify verify_scan(const std::span<const std::byte> artifact_bytes,
                          const OriginPathsView pair_set_origins,
                          const OriginIdsView origin_ids) {
  InstallVerify verify;
  verify.artifacts_checked = 1;
  for (const auto& origin : pair_set_origins.values) {
    verify.origin_path_hits += count_hits_bytes(artifact_bytes, Needle{origin});
  }
  for (const auto& id : origin_ids.values) {
    verify.origin_id_hits += count_hits_bytes(artifact_bytes, Needle{id});
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
