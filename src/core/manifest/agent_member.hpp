#pragma once

#include <algorithm>
#include <string>
#include <string_view>

namespace biv::manifest::grammar {

struct AgentId {
  std::string_view value;
};

struct MemberPath {
  std::string_view value;
};

inline bool session_id_ok(const std::string_view value) {
  return !value.empty() && value != "." && value != ".." &&
         std::ranges::all_of(value, [](const unsigned char character) {
           return character >= 0x20U && character != 0x7fU && character != '/' &&
                  character != '\\';
         });
}

inline bool member_segment_ok(const std::string_view segment) {
  return !segment.empty() && segment != "." && segment != ".." &&
         std::ranges::all_of(segment, [](const unsigned char character) {
           return character >= 0x20U && character != 0x7fU && character != '\\';
         });
}

inline bool agent_member_ok(const AgentId agent, const MemberPath path) {
  const std::string prefix = "agents/" + std::string{agent.value} + "/";
  if (!path.value.starts_with(prefix) || path.value.size() == prefix.size()) {
    return false;
  }
  const std::string_view rest = path.value.substr(prefix.size());
  bool first = true;
  size_t start = 0;
  while (start <= rest.size()) {
    const size_t slash = rest.find('/', start);
    const size_t end = slash == std::string_view::npos ? rest.size() : slash;
    const auto segment = rest.substr(start, end - start);
    if (!member_segment_ok(segment) ||
        (first && segment.find(':') != std::string_view::npos)) {
      return false;
    }
    if (slash == std::string_view::npos) break;
    first = false;
    start = slash + 1U;
  }
  return true;
}

}  // namespace biv::manifest::grammar
