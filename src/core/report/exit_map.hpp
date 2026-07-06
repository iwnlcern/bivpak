#pragma once

#include "core/support/error.hpp"

namespace biv::report {

int exit_for_error(ErrKind kind) noexcept;
int exit_for_warnings(bool any_divergence_warning) noexcept;

}  // namespace biv::report
