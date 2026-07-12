#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "core/open/open.hpp"
#include "core/open/sessions.hpp"
#include "core/pack/pack.hpp"
#include "core/support/error.hpp"

namespace biv::report {

inline constexpr int kEnvelopeVersion = 1;

struct OpenSessionsReport {
  bool prompt_shown{false};
  bool warning_shown{false};
  core_sessions::ConsentDecision consent;
  core_sessions::SessionPreview preview;
  core_sessions::SessionsOutcome outcome;
};

std::string envelope(std::string_view verb,
                     std::optional<pack::PackReport> pack_report,
                     std::optional<open::OpenReport> open_report,
                     std::optional<BivError> error,
                     int exit_code,
                     std::optional<OpenSessionsReport> sessions = std::nullopt);

}  // namespace biv::report
