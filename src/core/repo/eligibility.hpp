#pragma once

#include "core/repo/git.hpp"
#include "core/repo/types.hpp"
#include "core/support/error.hpp"

namespace biv::repo {

expected<void> run_eligibility(const Git& git, RepoEntry& entry);

}  // namespace biv::repo
