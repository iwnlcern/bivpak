#include "adapters/rewrite_common.hpp"

#include <algorithm>
#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
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

enum class RawNeedleKind { path, id };

struct RawNeedle {
  std::string_view from;
  std::string_view to;
  RawNeedleKind kind{RawNeedleKind::path};
};

bool path_token_byte(const char value) {
  return (value >= 'A' && value <= 'Z') ||
         (value >= 'a' && value <= 'z') ||
         (value >= '0' && value <= '9') || value == '_' || value == '-' ||
         value == '.' || value == ':' || value == '/' || value == '\\';
}

bool id_token_byte(const char value) {
  return (value >= '0' && value <= '9') ||
         (value >= 'a' && value <= 'z') ||
         (value >= 'A' && value <= 'Z') || value == '-' || value == '_';
}

bool matches_at(const std::span<const std::byte> bytes,
                const std::size_t position, const std::string_view needle) {
  if (needle.empty() || position + needle.size() > bytes.size()) {
    return false;
  }
  for (std::size_t offset = 0; offset < needle.size(); ++offset) {
    if (static_cast<char>(
            bytes.subspan(position + offset, 1U).front()) !=
        needle.at(offset)) {
      return false;
    }
  }
  return true;
}

bool replacement_boundary_ok(const std::span<const std::byte> bytes,
                             const std::size_t position,
                             const RawNeedle needle) {
  const auto before = [&](const auto predicate) {
    return position == 0U ||
           !predicate(static_cast<char>(
               bytes.subspan(position - 1U, 1U).front()));
  };
  const auto after_position = position + needle.from.size();
  const auto after = [&](const auto predicate) {
    return after_position >= bytes.size() ||
           !predicate(static_cast<char>(
               bytes.subspan(after_position, 1U).front()));
  };
  if (needle.kind == RawNeedleKind::id) {
    return before(id_token_byte) && after(id_token_byte);
  }
  if (!before(path_token_byte)) {
    return false;
  }
  if (after_position >= bytes.size()) {
    return true;
  }
  const char next =
      static_cast<char>(bytes.subspan(after_position, 1U).front());
  return next == '/' || next == '\\' || !path_token_byte(next);
}

std::vector<RawNeedle> replacement_needles(
    const PathPairsView path_pairs, const IdPairsView id_pairs) {
  std::vector<RawNeedle> needles;
  needles.reserve(path_pairs.values.size() + id_pairs.values.size());
  for (const auto& [from, to] : path_pairs.values) {
    if (!from.empty()) {
      needles.push_back(
          RawNeedle{.from = from, .to = to, .kind = RawNeedleKind::path});
    }
  }
  for (const auto& [from, to] : id_pairs.values) {
    if (!from.empty()) {
      needles.push_back(
          RawNeedle{.from = from, .to = to, .kind = RawNeedleKind::id});
    }
  }
  std::stable_sort(needles.begin(), needles.end(),
                   [](const RawNeedle lhs, const RawNeedle rhs) {
                     return lhs.from.size() > rhs.from.size();
                   });
  return needles;
}

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

void replace_id_all(std::string& text, const ReplacementText replacement) {
  if (replacement.from.empty()) {
    return;
  }
  size_t pos = 0;
  while ((pos = text.find(replacement.from, pos)) != std::string::npos) {
    const auto before_ok =
        pos == 0U || !id_token_byte(text.at(pos - 1U));
    const auto after = pos + replacement.from.size();
    const auto after_ok =
        after >= text.size() || !id_token_byte(text.at(after));
    if (!before_ok || !after_ok) {
      pos += replacement.from.size();
      continue;
    }
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

std::string json_string_content(const std::string_view value) {
  constexpr std::string_view hex = "0123456789ABCDEF";
  std::string out;
  for (const unsigned char character : value) {
    if (character == '"' || character == '\\') {
      out.push_back('\\');
      out.push_back(static_cast<char>(character));
    } else if (character < 0x20U) {
      out += "\\u00";
      out.push_back(hex.at(character >> 4U));
      out.push_back(hex.at(character & 0x0FU));
    } else {
      out.push_back(static_cast<char>(character));
    }
  }
  return out;
}

std::string apply_replacements(std::string value, const PathPairsView pair_set,
                               const IdPairsView id_map) {
  std::vector<const std::pair<std::string, std::string>*> path_pairs;
  path_pairs.reserve(pair_set.values.size());
  for (const auto& pair : pair_set.values) {
    path_pairs.push_back(&pair);
  }
  std::stable_sort(path_pairs.begin(), path_pairs.end(),
                   [](const auto* lhs, const auto* rhs) {
                     return lhs->first.size() > rhs->first.size();
                   });
  for (const auto* pair : path_pairs) {
    replace_path_all(value,
                     ReplacementText{.from = pair->first, .to = pair->second});
  }
  for (const auto& pair : id_map.values) {
    replace_id_all(value,
                   ReplacementText{.from = pair.first, .to = pair.second});
  }
  return value;
}

int hex_value(const char value) {
  if (value >= '0' && value <= '9') return value - '0';
  if (value >= 'a' && value <= 'f') return value - 'a' + 10;
  if (value >= 'A' && value <= 'F') return value - 'A' + 10;
  return -1;
}

void append_utf8(std::string& output, const std::uint32_t codepoint) {
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

std::optional<std::uint32_t> unicode_escape(const std::string_view content,
                                            const std::size_t start) {
  if (start + 4U > content.size()) return std::nullopt;
  std::uint32_t value = 0;
  for (std::size_t offset = 0; offset < 4U; ++offset) {
    const int digit = hex_value(content.at(start + offset));
    if (digit < 0) return std::nullopt;
    value = (value << 4U) | static_cast<std::uint32_t>(digit);
  }
  return value;
}

std::optional<std::string> decode_json_string(const std::string_view content) {
  std::string output;
  output.reserve(content.size());
  for (std::size_t index = 0; index < content.size(); ++index) {
    const char character = content.at(index);
    if (character != '\\') {
      output.push_back(character);
      continue;
    }
    if (++index >= content.size()) return std::nullopt;
    switch (content.at(index)) {
      case '"': output.push_back('"'); break;
      case '\\': output.push_back('\\'); break;
      case '/': output.push_back('/'); break;
      case 'b': output.push_back('\b'); break;
      case 'f': output.push_back('\f'); break;
      case 'n': output.push_back('\n'); break;
      case 'r': output.push_back('\r'); break;
      case 't': output.push_back('\t'); break;
      case 'u': {
        auto codepoint = unicode_escape(content, index + 1U);
        if (!codepoint.has_value()) return std::nullopt;
        index += 4U;
        if (*codepoint >= 0xd800U && *codepoint <= 0xdbffU) {
          if (index + 6U >= content.size() || content.at(index + 1U) != '\\' ||
              content.at(index + 2U) != 'u') {
            return std::nullopt;
          }
          auto low = unicode_escape(content, index + 3U);
          if (!low.has_value() || *low < 0xdc00U || *low > 0xdfffU) {
            return std::nullopt;
          }
          *codepoint = 0x10000U + ((*codepoint - 0xd800U) << 10U) +
                       (*low - 0xdc00U);
          index += 6U;
        } else if (*codepoint >= 0xdc00U && *codepoint <= 0xdfffU) {
          return std::nullopt;
        }
        append_utf8(output, *codepoint);
        break;
      }
      default: return std::nullopt;
    }
  }
  return output;
}

class JsonValueRewriter {
 public:
  JsonValueRewriter(const std::string_view input, const PathPairsView pair_set,
                    const IdPairsView id_map,
                    std::vector<std::string>* decoded_values = nullptr,
                    const bool decode_keys = false)
      : input_{input},
        pair_set_{pair_set},
        id_map_{id_map},
        decoded_values_{decoded_values},
        decode_keys_{decode_keys} {
    output_.reserve(input.size());
  }

  std::optional<std::string> run() {
    if (!value()) return std::nullopt;
    whitespace();
    if (position_ != input_.size()) return std::nullopt;
    return output_;
  }

 private:
  void whitespace() {
    while (position_ < input_.size() &&
           (input_.at(position_) == ' ' || input_.at(position_) == '\t' ||
            input_.at(position_) == '\r' || input_.at(position_) == '\n')) {
      output_.push_back(input_.at(position_++));
    }
  }

  std::optional<std::size_t> string_end() const {
    if (position_ >= input_.size() || input_.at(position_) != '"') {
      return std::nullopt;
    }
    std::size_t end = position_ + 1U;
    while (end < input_.size()) {
      if (input_.at(end) == '\\') {
        end += 2U;
      } else if (input_.at(end) == '"') {
        return end;
      } else {
        ++end;
      }
    }
    return std::nullopt;
  }

  bool key_string() {
    const auto end = string_end();
    if (!end.has_value()) return false;
    if (!decode_keys_) {
      output_.append(input_.substr(position_, *end - position_ + 1U));
      position_ = *end + 1U;
      return true;
    }
    auto decoded = decode_json_string(
        input_.substr(position_ + 1U, *end - position_ - 1U));
    if (!decoded.has_value()) return false;
    if (decoded_values_ != nullptr) decoded_values_->push_back(*decoded);
    output_.push_back('"');
    output_ += json_string_content(
        apply_replacements(std::move(*decoded), pair_set_, id_map_));
    output_.push_back('"');
    position_ = *end + 1U;
    return true;
  }

  bool string_value() {
    const auto end = string_end();
    if (!end.has_value()) return false;
    auto decoded = decode_json_string(
        input_.substr(position_ + 1U, *end - position_ - 1U));
    if (!decoded.has_value()) return false;
    if (decoded_values_ != nullptr) decoded_values_->push_back(*decoded);
    output_.push_back('"');
    output_ += json_string_content(
        apply_replacements(std::move(*decoded), pair_set_, id_map_));
    output_.push_back('"');
    position_ = *end + 1U;
    return true;
  }

  bool object() {
    output_.push_back(input_.at(position_++));
    whitespace();
    if (position_ < input_.size() && input_.at(position_) == '}') {
      output_.push_back(input_.at(position_++));
      return true;
    }
    while (position_ < input_.size()) {
      if (!key_string()) return false;
      whitespace();
      if (position_ >= input_.size() || input_.at(position_) != ':') return false;
      output_.push_back(input_.at(position_++));
      if (!value()) return false;
      whitespace();
      if (position_ < input_.size() && input_.at(position_) == '}') {
        output_.push_back(input_.at(position_++));
        return true;
      }
      if (position_ >= input_.size() || input_.at(position_) != ',') return false;
      output_.push_back(input_.at(position_++));
      whitespace();
    }
    return false;
  }

  bool array() {
    output_.push_back(input_.at(position_++));
    whitespace();
    if (position_ < input_.size() && input_.at(position_) == ']') {
      output_.push_back(input_.at(position_++));
      return true;
    }
    while (position_ < input_.size()) {
      if (!value()) return false;
      whitespace();
      if (position_ < input_.size() && input_.at(position_) == ']') {
        output_.push_back(input_.at(position_++));
        return true;
      }
      if (position_ >= input_.size() || input_.at(position_) != ',') return false;
      output_.push_back(input_.at(position_++));
    }
    return false;
  }

  bool primitive() {
    const std::size_t start = position_;
    while (position_ < input_.size() && input_.at(position_) != ',' &&
           input_.at(position_) != ']' && input_.at(position_) != '}' &&
           input_.at(position_) != ' ' && input_.at(position_) != '\t' &&
           input_.at(position_) != '\r' && input_.at(position_) != '\n') {
      ++position_;
    }
    if (position_ == start) return false;
    output_.append(input_.substr(start, position_ - start));
    return true;
  }

  bool value() {
    whitespace();
    if (position_ >= input_.size()) return false;
    switch (input_.at(position_)) {
      case '{': return object();
      case '[': return array();
      case '"': return string_value();
      default: return primitive();
    }
  }

  std::string_view input_;
  PathPairsView pair_set_;
  IdPairsView id_map_;
  std::vector<std::string>* decoded_values_;
  bool decode_keys_{false};
  std::size_t position_{0};
  std::string output_;
};

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

size_t count_hits_text(const std::string_view haystack, const Needle needle) {
  if (needle.value.empty()) return 0;
  size_t hits = 0;
  size_t position = 0;
  while ((position = haystack.find(needle.value, position)) !=
         std::string_view::npos) {
    ++hits;
    position += needle.value.size();
  }
  return hits;
}

InstallVerify verify_bare_bytes(const std::span<const std::byte> input,
                                const OriginPathsView origin_paths,
                                const OriginIdsView origin_ids) {
  InstallVerify verify{.artifacts_checked = 1U};
  for (const auto& origin : origin_paths.values) {
    verify.origin_path_hits += count_hits_bytes(input, Needle{origin});
  }
  for (const auto& id : origin_ids.values) {
    verify.origin_id_hits += count_hits_bytes(input, Needle{id});
  }
  return verify;
}

}  // namespace

bool claude_staged_subtree_artifact(const std::string_view relative) {
  return relative.ends_with(".jsonl") || relative.ends_with(".txt") ||
         relative.ends_with(".meta.json");
}

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

ReplacementPairs derive_install_pair_set(
    const manifest::AgentSessionEntry& record,
    const std::string_view target_path,
    const manifest::PathFlavor target_flavor) {
  auto pairs = derive_pair_set(record.original_path, record.path_flavor,
                               target_path, target_flavor);
  const bool staged = record.provenance.locator == "staging" &&
                      record.provenance.discovery_tier == "staged";
  if (!staged || record.provenance.store_root.empty()) {
    return pairs;
  }
  auto staging_pairs = derive_pair_set(
      record.provenance.store_root,
      path_flavor_for(record.provenance.store_root), target_path,
      target_flavor);
  for (auto& pair : staging_pairs) {
    append_unique_pair(pairs, std::move(pair));
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
  auto rewritten =
      JsonValueRewriter{line, pair_set, id_map, nullptr, true}.run();
  return RewriteLineResult{
      .line = rewritten.has_value() ? std::move(*rewritten) : std::string{line}};
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

std::vector<std::byte> rewrite_raw_text_bytes(const RawTextBytesView input,
                                              const PathPairsView path_pairs,
                                              const IdPairsView id_pairs) {
  const auto needles = replacement_needles(path_pairs, id_pairs);
  std::vector<std::byte> output;
  output.reserve(input.values.size());
  for (std::size_t position = 0; position < input.values.size();) {
    const auto match = std::ranges::find_if(needles, [&](const RawNeedle needle) {
      return matches_at(input.values, position, needle.from) &&
             replacement_boundary_ok(input.values, position, needle);
    });
    if (match == needles.end()) {
      output.push_back(input.values.subspan(position, 1U).front());
      ++position;
      continue;
    }
    for (const char value : match->to) {
      output.push_back(static_cast<std::byte>(value));
    }
    position += match->from.size();
  }
  return output;
}

InstallVerify verify_raw_text_bytes(const RawTextBytesView input,
                                    const OriginPathsView origin_paths,
                                    const OriginIdsView origin_ids) {
  return verify_bare_bytes(input.values, origin_paths, origin_ids);
}

InstallVerify verify_whole_document_bytes(const ArtifactBytesView input,
                                          const OriginPathsView origin_paths,
                                          const OriginIdsView origin_ids) {
  auto verify = verify_bare_bytes(input.values, origin_paths, origin_ids);
  const std::string document = string_from_bytes(input.values);
  if (!valid_utf8(document)) return verify;

  simdjson::padded_string padded{document};
  simdjson::dom::parser parser;
  simdjson::dom::element root;
  if (parser.parse(padded).get(root)) return verify;

  std::vector<std::string> decoded_strings;
  const auto decoded = JsonValueRewriter{
      document, PathPairsView{}, IdPairsView{}, &decoded_strings, true}
                           .run();
  if (!decoded.has_value()) return verify;
  for (const auto& value : decoded_strings) {
    for (const auto& origin : origin_paths.values) {
      verify.origin_path_hits += count_hits_text(value, Needle{origin});
    }
    for (const auto& id : origin_ids.values) {
      verify.origin_id_hits += count_hits_text(value, Needle{id});
    }
  }
  return verify;
}

expected<StagedSidecar> parse_staged_sidecar(
    const std::filesystem::path& sidecar, const std::string_view json,
    const std::filesystem::path& source_root) {
  const auto invalid = [&]() -> expected<StagedSidecar> {
    return std::unexpected(BivError{ErrKind::ParseError, sidecar.string(),
                                    "invalid_staged_sidecar"});
  };
  simdjson::padded_string padded{json};
  simdjson::dom::parser parser;
  simdjson::dom::element root;
  simdjson::dom::object document;
  simdjson::dom::array maps;
  simdjson::dom::array provenance_values;
  simdjson::dom::array pair_values;
  if (parser.parse(padded).get(root) || root.get(document) ||
      document.at_key("id_map").get(maps) ||
      document.at_key("provenance_chain").get(provenance_values) ||
      document.at_key("pair_set_applied").get(pair_values) ||
      maps.size() == 0U || provenance_values.size() == 0U ||
      pair_values.size() == 0U) {
    return invalid();
  }

  std::set<std::string> provenance;
  for (const auto value : provenance_values) {
    std::string_view id;
    if (value.get(id) || id.empty() || !provenance.emplace(id).second) {
      return invalid();
    }
  }

  StagedSidecar parsed;
  std::set<std::pair<std::string, std::string>> unique_pairs;
  for (const auto value : pair_values) {
    simdjson::dom::array pair;
    std::string_view original_path;
    std::string_view target_path;
    if (value.get(pair) || pair.size() != 2U ||
        pair.at(0).get(original_path) || pair.at(1).get(target_path) ||
        original_path.empty() || target_path != source_root.generic_string()) {
      return invalid();
    }
    std::pair<std::string, std::string> owned{original_path, target_path};
    if (!unique_pairs.insert(owned).second) {
      return invalid();
    }
    parsed.path_pairs.push_back(std::move(owned));
  }

  std::set<std::string> required_provenance;
  std::set<std::string> image_ids;
  std::set<std::string> installed_ids;
  std::size_t rows_with_original_path = 0U;
  for (const auto value : maps) {
    simdjson::dom::object object;
    std::string_view agent;
    std::string_view original;
    std::string_view minted;
    simdjson::dom::array children;
    if (value.get(object) || object.at_key("agent").get(agent) ||
        object.at_key("image_session_id").get(original) ||
        object.at_key("installed_session_id").get(minted) ||
        object.at_key("children").get(children) ||
        (agent != "codex" && agent != "claude-code") || original.empty() ||
        minted.empty() || !image_ids.emplace(original).second ||
        !installed_ids.emplace(minted).second) {
      return invalid();
    }
    std::optional<std::string> original_path;
    std::size_t original_path_members = 0U;
    for (const auto field : object) {
      if (field.key != "original_path") {
        continue;
      }
      ++original_path_members;
      std::string_view candidate;
      if (original_path_members != 1U || field.value.get(candidate) ||
          candidate.empty()) {
        return invalid();
      }
      original_path = std::string{candidate};
    }
    if (original_path.has_value()) {
      const auto audited = std::pair{*original_path,
                                     source_root.generic_string()};
      if (!unique_pairs.contains(audited)) {
        return invalid();
      }
      ++rows_with_original_path;
    }
    StagedMapRow row{.agent = std::string{agent},
                     .original = std::string{original},
                     .minted = std::string{minted},
                     .original_path = std::move(original_path),
                     .children = {}};
    required_provenance.emplace(original);
    for (const auto child_value : children) {
      simdjson::dom::array child;
      std::string_view child_original;
      std::string_view child_minted;
      if (child_value.get(child) || child.size() != 2U ||
          child.at(0).get(child_original) || child.at(1).get(child_minted) ||
          child_original.empty() || child_minted.empty() ||
          !image_ids.emplace(child_original).second ||
          !installed_ids.emplace(child_minted).second) {
        return invalid();
      }
      required_provenance.emplace(child_original);
      row.children.emplace_back(child_original, child_minted);
    }
    parsed.rows.push_back(std::move(row));
  }
  if (rows_with_original_path != 0U &&
      rows_with_original_path != parsed.rows.size()) {
    return invalid();
  }
  if (required_provenance != provenance) {
    return invalid();
  }
  std::ranges::sort(parsed.path_pairs);
  return parsed;
}

InstallVerify verify_scan(const std::span<const std::byte> artifact_bytes,
                          const OriginPathsView pair_set_origins,
                          const OriginIdsView origin_ids) {
  InstallVerify verify;
  verify.artifacts_checked = 1;
  const std::string input = string_from_bytes(artifact_bytes);
  size_t start = 0;
  while (start < input.size()) {
    const size_t newline = input.find('\n', start);
    const size_t end = newline == std::string::npos ? input.size() : newline;
    const std::string_view line = std::string_view{input}.substr(start, end - start);
    bool decoded = false;
    if (valid_utf8(line)) {
      simdjson::padded_string padded{line};
      simdjson::dom::parser parser;
      simdjson::dom::element root;
      if (!parser.parse(padded).get(root)) {
        std::vector<std::string> values;
        auto parsed = JsonValueRewriter{line, PathPairsView{}, IdPairsView{},
                                        &values, true}
                          .run();
        if (parsed.has_value()) {
          decoded = true;
          for (const auto& value : values) {
            for (const auto& origin : pair_set_origins.values) {
              verify.origin_path_hits += count_hits_text(value, Needle{origin});
            }
            for (const auto& id : origin_ids.values) {
              verify.origin_id_hits += count_hits_text(value, Needle{id});
            }
          }
        }
      }
    }
    if (!decoded) {
      // A line that cannot complete decoded verification is not safe to
      // publish. Reuse the existing nonzero-hit install refusal contract.
      if (!pair_set_origins.values.empty()) {
        ++verify.origin_path_hits;
      } else if (!origin_ids.values.empty()) {
        ++verify.origin_id_hits;
      }
      const auto line_bytes = artifact_bytes.subspan(start, end - start);
      for (const auto& origin : pair_set_origins.values) {
        verify.origin_path_hits += count_hits_bytes(line_bytes, Needle{origin});
      }
      for (const auto& id : origin_ids.values) {
        verify.origin_id_hits += count_hits_bytes(line_bytes, Needle{id});
      }
    }
    if (newline == std::string::npos) break;
    start = newline + 1U;
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
