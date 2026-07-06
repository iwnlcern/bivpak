#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "core/open/open.hpp"
#include "core/pack/pack.hpp"
#include "core/support/error.hpp"

namespace biv::report {

inline constexpr int kEnvelopeVersion = 1;

std::string envelope(std::string_view verb,
                     std::optional<pack::PackReport> pack_report,
                     std::optional<open::OpenReport> open_report,
                     std::optional<BivError> error,
                     int exit_code);

}  // namespace biv::report
