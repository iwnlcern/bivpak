#include "adapters/registry.hpp"

#include <array>

#include "adapters/claude_code/claude_code.hpp"
#include "adapters/codex/codex.hpp"

namespace biv::adapters {

std::span<const AgentAdapter* const> all_adapters() {
  static const std::array adapters{&claude_code_adapter(), &codex_adapter()};
  return std::span<const AgentAdapter* const>{adapters};
}

const AgentAdapter* find_adapter(const std::string_view agent_id) {
  for (const auto* adapter : all_adapters()) {
    if (adapter->id() == agent_id) {
      return adapter;
    }
  }
  return nullptr;
}

}  // namespace biv::adapters
