#pragma once

#include <chrono>
#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <string_view>

#include "core/support/error.hpp"

namespace biv::support {

inline constexpr std::chrono::milliseconds kProbeTimeout{2000};

enum class ProbeOutcome {
  ok,
  not_found,
  not_executable,
  not_accessible,
  spawn_error,
  nonzero_exit,
  timeout,
  unparseable,
  probe_io_error
};

struct ProbeEvidence {
  std::string agent;
  std::optional<std::filesystem::path> requested;
  std::optional<std::filesystem::path> executed;
  bool pinned{false};
  ProbeOutcome outcome{ProbeOutcome::not_found};
  int exit_code{-1};
  std::string raw;
  std::optional<std::string> parsed;
};

using Getenv = std::function<std::optional<std::string>(std::string_view name)>;

struct ProbeBudgets {
  std::chrono::milliseconds probe_wall{kProbeTimeout};
  std::chrono::milliseconds term_grace{200};
  std::chrono::milliseconds post_exit_drain{100};
  std::chrono::milliseconds post_kill_reap{100};
  std::chrono::milliseconds poll_slice{20};
};

struct ProbeClock {
  std::function<std::chrono::steady_clock::time_point()> now;
  std::function<void(std::chrono::milliseconds)> sleep;
};

enum class ReadinessResult { ready, timed_out, interrupted, failed };

using ProbeWaiter = std::function<ReadinessResult(
    int fd, std::chrono::milliseconds requested)>;

struct ProbePhaseEvent {
  std::string_view phase;
  std::chrono::milliseconds requested;
  std::chrono::milliseconds elapsed;
  std::string_view result;
};

using ProbePhaseSink = std::function<void(const ProbePhaseEvent&)>;

ProbeClock production_probe_clock();
ProbeWaiter production_probe_waiter();

std::string sanitize_utf8(std::string_view input);

// biv never invokes an agent with a prompt, never starts/resumes a session, never spends;
// the disclosed, pinnable, shell-free `<binary> --version` probe is the sole sanctioned exec (operator ruling 062318).
// That ruling is absolute for agent execution; git is not an agent and its argv-only execution is governed separately by the sealed Step-4 contracts.
// The probe places the child in its OWN process group and, on cleanup, sweeps THAT GROUP (TERM → 200ms grace → KILL to `-pgid`).
// A descendant that REMOVES ITSELF from the group before the sweep — e.g. via `setsid()` or `setpgid()` — is NOT portably killable on the target platforms and is NOT claimed to be reaped.
// Group members are swept; a self-detached descendant is acknowledged, not silently promised.
expected<ProbeEvidence> run_version_probe(
    std::string agent, const std::optional<std::filesystem::path>& pin,
    const Getenv& getenv, const ProbeBudgets& budgets,
    const ProbeClock& clock = production_probe_clock(),
    const ProbeWaiter& wait_activity = production_probe_waiter(),
    const ProbePhaseSink& phase_sink = ProbePhaseSink{});

#if defined(BIV_PROBE_TESTING)
namespace probe_testing {

enum class ControlledWaitResult { pending, reaped, failed };

struct PostKillReapResult {
  bool reaped{false};
  bool transferred{false};
};

using ControlledWait = std::function<ControlledWaitResult(bool blocking)>;
using EstablishReaper = std::function<bool()>;

PostKillReapResult exercise_post_kill_reap(
    const ControlledWait& wait_child, const EstablishReaper& establish_reaper,
    std::chrono::milliseconds polling_window, const ProbeClock& clock);

}  // namespace probe_testing
#endif

}  // namespace biv::support
