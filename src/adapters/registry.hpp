#pragma once

#include <span>
#include <string_view>

#include "adapters/adapter.hpp"

namespace biv::adapters {

std::span<const AgentAdapter* const> all_adapters();
const AgentAdapter* find_adapter(std::string_view agent_id);

}  // namespace biv::adapters
