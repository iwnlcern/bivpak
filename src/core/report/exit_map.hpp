#pragma once

#include "core/support/error.hpp"
#include "core/open/sessions.hpp"

namespace biv::report {

int exit_for_error(ErrKind kind) noexcept;
int exit_for_warnings(bool any_divergence_warning) noexcept;
int exit_for_sessions(const core_sessions::SessionsOutcome& outcome) noexcept;

}  // namespace biv::report
