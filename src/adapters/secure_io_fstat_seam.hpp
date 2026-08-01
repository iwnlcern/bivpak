#pragma once

// Test seam for the fstat outcome classification in secure_io.cpp.
//
// NOT part of the secure_io public contract. The only consumers are
// secure_io.cpp itself and the adapter install unit tests. It lives here
// rather than in secure_io.hpp so that <sys/stat.h> and a POSIX struct stat
// are not pulled into translation units that include the public header and
// never call this helper. Some of those already have the type transitively
// via core/support/portability.hpp; the ones that do not are the cost, and
// their number moves with the includer set, so it is deliberately not stated
// here.

#include <expected>
#include <filesystem>
#include <optional>
#include <type_traits>

#include <sys/stat.h>

#include "core/support/error.hpp"

namespace biv::adapters::secure_io::internal {

// The result of ONE fstat call, as a value: either the call succeeded and we
// hold its stat, or it failed and we hold the errno that explains why.
//
// The success arm carries NO errno, deliberately. A successful fstat leaves
// errno untouched, so a "succeeded, and here is an errno" pair is a stale-errno
// hazard: the classifier could report a leftover ambient errno on a branch whose
// correct answer is an explicit containment EINVAL. This type makes that pair
// UNREPRESENTABLE rather than documenting it. Before the ruling that introduced
// it, the hazard was guarded only by a comment and by an argument passed to a
// seam test. (m-2 ruling 162000.)
//
// NOTE: spelled std::expected deliberately. The project alias `expected<T>`
// (core/support/error.hpp) is std::expected<T, BivError>; writing
// `expected<struct stat>` here would silently bind the wrong error type.
using FstatObservation = std::expected<struct stat, int>;

static_assert(std::is_same_v<FstatObservation::value_type, struct stat>,
              "FstatObservation's success arm must carry the stat and nothing "
              "else — adding an errno beside it re-arms the stale-errno hazard");
static_assert(std::is_same_v<FstatObservation::error_type, int>,
              "FstatObservation's failure arm must carry the captured errno and "
              "nothing else");

// Deterministic observation seam for :289's two branches. Takes an observation
// the caller ALREADY HOLDS -- it performs no syscall and interposes none.
// Returns the COMPLETE constructed error so a direct unit test can assert
// route, exact err_no and detail on both error outcomes.
//
//   call failed            -> ambient error carrying the captured errno
//   succeeded, non-regular -> containment error, EINVAL (explicit, never the
//                             ambient errno, which may be stale)
//   succeeded, regular     -> no error
[[nodiscard]] std::optional<BivError> fstat_outcome(
    const std::filesystem::path& path, const FstatObservation& observed);

}  // namespace biv::adapters::secure_io::internal
