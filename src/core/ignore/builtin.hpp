#pragma once

#include <string_view>

namespace biv::ignore {

inline constexpr std::string_view kBuiltinV1 =
    "node_modules/\n.venv/\nvenv/\n__pycache__/\n*.pyc\ntarget/\n.tox/\n.mypy_cache/\n.pytest_cache/\n.ruff_cache/\n.gradle/\n";

inline constexpr std::string_view kBuiltinV1Sha256 =
    "e271561320eecb76b6736a4b85bfc98069e1259b8fc9609ebea926e8aa5bb1d3";

}
