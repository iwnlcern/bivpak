#pragma once

#include <string>
#include <utility>
#include <vector>

namespace biv::core_sessions {

enum class ConsentValue { unset, yes, no };

struct ConsentSpec {
  ConsentValue global{ConsentValue::unset};
  std::vector<std::pair<std::string, ConsentValue>> per_agent;
};

}  // namespace biv::core_sessions
