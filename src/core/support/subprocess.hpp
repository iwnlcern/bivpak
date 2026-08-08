#pragma once

#include <cstddef>
#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "core/support/probe.hpp"

namespace biv::support {

enum class StderrMode { separate, merge_into_stdout };

struct SpawnRequest {
  std::filesystem::path executable;
  std::vector<std::string> argv;
  std::vector<std::string> env;
  StderrMode stderr_mode{StderrMode::separate};
  std::optional<std::filesystem::path> stdout_file;
  std::size_t stdout_cap{0};
  std::size_t stderr_cap{0};
  ProbeBudgets budgets;
};

struct SpawnResult {
  int exit_code{-1};
  bool timed_out{false};
  bool spawn_failed{false};
  bool io_failed{false};
  bool output_incomplete{false};
  std::vector<std::byte> stdout_bytes;
  std::vector<std::byte> stderr_bytes;
};

expected<SpawnResult> run_argv(
    const SpawnRequest& request,
    const ProbeClock& clock = production_probe_clock(),
    const ProbeWaiter& wait_activity = production_probe_waiter());

namespace subprocess_detail {

enum class WaitResult { pending, reaped, failed };

struct PostKillResult {
  bool reaped{false};
  bool transferred{false};
};

using ControlledWait = std::function<WaitResult(bool blocking)>;
using EstablishReaper = std::function<bool()>;

PostKillResult settle_post_kill(
    const ControlledWait& wait_child, const EstablishReaper& establish_reaper,
    std::chrono::milliseconds polling_window, const ProbeClock& clock);

expected<SpawnResult> run_argv_traced(
    const SpawnRequest& request, const ProbeClock& clock,
    const ProbeWaiter& wait_activity, const ProbePhaseSink& phase_sink);

}  // namespace subprocess_detail

}  // namespace biv::support
