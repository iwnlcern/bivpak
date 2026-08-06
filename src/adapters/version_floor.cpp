#include "adapters/version_floor.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace biv::adapters::version_floor {

namespace {

constexpr FloorRow kCodexFloor{"0.142", "0.144"};
constexpr FloorRow kClaudeCodeFloor{"2.1", "2.1"};

bool ascii_alnum(const char value) {
  return (value >= '0' && value <= '9') ||
         (value >= 'A' && value <= 'Z') ||
         (value >= 'a' && value <= 'z');
}

bool grammar_character(const char value) {
  return ascii_alnum(value) || value == '.' || value == '+' || value == '-';
}

bool valid_suffix(const std::string_view suffix) {
  if (suffix.empty()) {
    return false;
  }
  bool component_has_value = false;
  for (const char value : suffix) {
    if (value == '.') {
      if (!component_has_value) {
        return false;
      }
      component_has_value = false;
      continue;
    }
    if (!ascii_alnum(value) && value != '-') {
      return false;
    }
    component_has_value = true;
  }
  return component_has_value;
}

}  // namespace

FloorRow row_for(const std::string_view agent) {
  if (agent == "codex") {
    return kCodexFloor;
  }
  if (agent == "claude-code") {
    return kClaudeCodeFloor;
  }
  return {};
}

std::optional<Parsed> parse_grammar(std::string_view version) {
  if (version.empty()) {
    return std::nullopt;
  }
  if (version.front() == 'v') {
    version.remove_prefix(1U);
  }
  if (version.empty()) {
    return std::nullopt;
  }

  const auto build_at = version.find('+');
  if (build_at != std::string_view::npos) {
    if (version.find('+', build_at + 1U) != std::string_view::npos ||
        !valid_suffix(version.substr(build_at + 1U))) {
      return std::nullopt;
    }
    version = version.substr(0U, build_at);
  }

  const auto prerelease_at = version.find('-');
  if (prerelease_at != std::string_view::npos) {
    if (!valid_suffix(version.substr(prerelease_at + 1U))) {
      return std::nullopt;
    }
    version = version.substr(0U, prerelease_at);
  }
  if (version.empty()) {
    return std::nullopt;
  }

  Parsed parsed;
  std::size_t begin = 0U;
  while (begin < version.size()) {
    if (parsed.component_count == parsed.components.size()) {
      return std::nullopt;
    }
    const auto dot = version.find('.', begin);
    const auto end = dot == std::string_view::npos ? version.size() : dot;
    const auto component = version.substr(begin, end - begin);
    if (component.empty() || component.size() > 9U) {
      return std::nullopt;
    }
    std::uint32_t value = 0U;
    for (const char digit : component) {
      if (digit < '0' || digit > '9') {
        return std::nullopt;
      }
      value = value * 10U + static_cast<std::uint32_t>(digit - '0');
    }
    parsed.components.at(parsed.component_count++) = value;
    if (dot == std::string_view::npos) {
      break;
    }
    begin = dot + 1U;
    if (begin == version.size()) {
      return std::nullopt;
    }
  }
  return parsed.component_count == 0U ? std::nullopt
                                      : std::optional<Parsed>{parsed};
}

std::optional<std::string> extract_single_version(const std::string_view raw) {
  if (raw.find('\0') != std::string_view::npos) {
    return std::nullopt;
  }
  std::optional<std::string> found;
  for (std::size_t begin = 0U; begin < raw.size();) {
    const bool can_start = raw.at(begin) == 'v' ||
                           (raw.at(begin) >= '0' && raw.at(begin) <= '9');
    const bool left_boundary =
        begin == 0U || !grammar_character(raw.at(begin - 1U));
    if (!can_start || !left_boundary) {
      ++begin;
      continue;
    }
    auto end = begin;
    while (end < raw.size() && grammar_character(raw.at(end))) {
      ++end;
    }
    const auto candidate = raw.substr(begin, end - begin);
    if (parse_grammar(candidate).has_value()) {
      if (found.has_value()) {
        return std::nullopt;
      }
      found = std::string{candidate};
    }
    begin = end;
  }
  return found;
}

Order compare_line(const Parsed& a, const Parsed& b) {
  for (std::size_t index = 0U; index < 2U; ++index) {
    const auto left = index < a.component_count ? a.components.at(index) : 0U;
    const auto right =
        index < b.component_count ? b.components.at(index) : 0U;
    if (left < right) {
      return Order::less;
    }
    if (left > right) {
      return Order::greater;
    }
  }
  return Order::equal;
}

Admission admit(const AdmissionInput& input) {
  const auto basis = parse_grammar(input.image_version);
  if (!basis.has_value()) {
    return {.detail = kBasisUnorderable};
  }
  const auto host = parse_grammar(input.host_version);
  if (!host.has_value()) {
    return {.detail = kBasisUnorderable};
  }
  if (compare_line(*host, *basis) == Order::less) {
    return {.detail = kBasisNewerThanHost};
  }
  const auto surveyed = parse_grammar(row_for(input.agent).surveyed_through);
  if (!surveyed.has_value()) {
    return {.detail = kBasisUnorderable};
  }
  return {.admitted = true,
          .host_version_unverified =
              compare_line(*host, *surveyed) == Order::greater,
          .detail = {}};
}

}  // namespace biv::adapters::version_floor
