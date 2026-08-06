#include "core/support/probe.hpp"

#include <sys/stat.h>
#include <unistd.h>

#if defined(__APPLE__)
#include <crt_externs.h>
#else
extern char** environ;
#endif

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstddef>
#include <filesystem>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "core/support/subprocess.hpp"

namespace biv::support {

namespace {

namespace fs = std::filesystem;

#if !defined(BIV_PROBE_TEST_SEAM_ONLY)
constexpr std::size_t kCaptureLimit = std::size_t{64} * 1024U;

class Utf8Capture {
 public:
  explicit Utf8Capture(const std::size_t limit) : limit_{limit} {}

  void write(const std::string_view input) {
    for (const unsigned char byte : input) {
      consume(byte);
    }
  }

  void finish() {
    if (pending_size_ != 0U) {
      append_replacement();
      reset_pending();
    }
  }

  std::string take() { return std::move(output_); }

 private:
  static bool is_continuation(const unsigned char byte) {
    return (byte & 0xc0U) == 0x80U;
  }

  static std::size_t sequence_width(const unsigned char lead) {
    if (lead >= 0xc2U && lead <= 0xdfU) {
      return 2U;
    }
    if (lead >= 0xe0U && lead <= 0xefU) {
      return 3U;
    }
    if (lead >= 0xf0U && lead <= 0xf4U) {
      return 4U;
    }
    return 0U;
  }

  bool pending_is_valid() const {
    const auto lead = pending_.front();
    const auto second = pending_.at(1);
    if (expected_size_ == 2U) {
      return true;
    }
    if (expected_size_ == 3U) {
      return !(lead == 0xe0U && second < 0xa0U) &&
             !(lead == 0xedU && second > 0x9fU);
    }
    return !(lead == 0xf0U && second < 0x90U) &&
           !(lead == 0xf4U && second > 0x8fU);
  }

  void append_bytes(const char* bytes, const std::size_t count) {
    if (!retaining_) {
      return;
    }
    if (count > limit_ - std::min(limit_, output_.size())) {
      retaining_ = false;
      return;
    }
    output_.append(bytes, count);
  }

  void append_replacement() {
    constexpr std::array<char, 3> replacement{static_cast<char>(0xef),
                                              static_cast<char>(0xbf),
                                              static_cast<char>(0xbd)};
    append_bytes(replacement.data(), replacement.size());
  }

  void reset_pending() {
    pending_size_ = 0;
    expected_size_ = 0;
  }

  void consume(const unsigned char byte) {
    if (pending_size_ == 0U) {
      if (byte < 0x80U) {
        const char value = static_cast<char>(byte);
        append_bytes(&value, 1U);
        return;
      }
      expected_size_ = sequence_width(byte);
      if (expected_size_ == 0U) {
        append_replacement();
        return;
      }
      pending_.front() = byte;
      pending_size_ = 1U;
      return;
    }

    if (!is_continuation(byte)) {
      append_replacement();
      reset_pending();
      consume(byte);
      return;
    }

    pending_.at(pending_size_) = byte;
    ++pending_size_;
    if (pending_size_ != expected_size_) {
      return;
    }
    if (pending_is_valid()) {
      std::array<char, 4> encoded{};
      std::transform(
          pending_.begin(), pending_.end(), encoded.begin(),
          [](const unsigned char value) { return static_cast<char>(value); });
      append_bytes(encoded.data(), expected_size_);
    } else {
      append_replacement();
    }
    reset_pending();
  }

  std::size_t limit_;
  std::string output_;
  std::array<unsigned char, 4> pending_{};
  std::size_t pending_size_{0};
  std::size_t expected_size_{0};
  bool retaining_{true};
};

BivError invalid_probe_request(const std::string_view detail) {
  return BivError{ErrKind::InternalError, {}, std::string{detail}, EINVAL};
}

bool executable_regular_file(const fs::path& path) {
  struct stat status{};
  return ::stat(path.c_str(), &status) == 0 && S_ISREG(status.st_mode) &&
         ::access(path.c_str(), X_OK) == 0;
}

struct PathResolution {
  std::optional<fs::path> path;
  bool failed{false};
};

PathResolution resolve_from_path(const std::string_view agent,
                                 const Getenv& getenv) {
  if (!getenv) {
    return {};
  }
  const auto path_value = getenv("PATH");
  if (!path_value.has_value()) {
    return {};
  }

  std::size_t begin = 0;
  while (begin <= path_value->size()) {
    const auto end = path_value->find(':', begin);
    const auto component = path_value->substr(
        begin, end == std::string::npos ? std::string::npos : end - begin);
    const fs::path directory =
        component.empty() ? fs::path{"."} : fs::path{component};
    std::error_code error;
    const auto absolute = fs::absolute(directory / agent, error);
    if (error) {
      return {.path = std::nullopt, .failed = true};
    }
    const auto candidate = absolute.lexically_normal();
    if (executable_regular_file(candidate)) {
      return {.path = candidate, .failed = false};
    }
    if (end == std::string::npos) {
      break;
    }
    begin = end + 1U;
  }
  return {};
}

std::vector<std::string> parent_environment() {
#if defined(__APPLE__)
  char** entries = *_NSGetEnviron();
#else
  char** entries = environ;
#endif
  std::vector<std::string> result;
  if (entries == nullptr) {
    return result;
  }
  for (; *entries != nullptr; ++entries) {
    result.emplace_back(*entries);
  }
  return result;
}

std::string sanitize_capture(const std::vector<std::byte>& bytes,
                             const std::size_t limit) {
  const auto* data = reinterpret_cast<const char*>(bytes.data());
  Utf8Capture capture{limit};
  capture.write(std::string_view{data, bytes.size()});
  capture.finish();
  return capture.take();
}

#endif

}  // namespace

#if defined(BIV_PROBE_TESTING)
namespace probe_testing {

PostKillReapResult exercise_post_kill_reap(
    const ControlledWait& wait_child, const EstablishReaper& establish_reaper,
    const std::chrono::milliseconds polling_window, const ProbeClock& clock) {
  const auto result = subprocess_detail::settle_post_kill(
      [&wait_child](const bool blocking) {
        switch (wait_child(blocking)) {
          case ControlledWaitResult::pending:
            return subprocess_detail::WaitResult::pending;
          case ControlledWaitResult::reaped:
            return subprocess_detail::WaitResult::reaped;
          case ControlledWaitResult::failed:
            return subprocess_detail::WaitResult::failed;
        }
        return subprocess_detail::WaitResult::failed;
      },
      establish_reaper, polling_window, clock);
  return {.reaped = result.reaped, .transferred = result.transferred};
}

}  // namespace probe_testing
#endif

#if !defined(BIV_PROBE_TEST_SEAM_ONLY)

std::string sanitize_utf8(const std::string_view input) {
  Utf8Capture capture{std::numeric_limits<std::size_t>::max()};
  capture.write(input);
  capture.finish();
  return capture.take();
}

expected<ProbeEvidence> run_version_probe(
    std::string agent, const std::optional<fs::path>& pin, const Getenv& getenv,
    const ProbeBudgets& budgets, const ProbeClock& clock,
    const ProbeWaiter& wait_activity, const ProbePhaseSink& phase_sink) {
  if (agent.empty()) {
    return std::unexpected(
        invalid_probe_request("version probe agent is empty"));
  }
  if (budgets.probe_wall <= std::chrono::milliseconds::zero() ||
      budgets.term_grace < std::chrono::milliseconds::zero() ||
      budgets.post_exit_drain < std::chrono::milliseconds::zero() ||
      budgets.post_kill_reap < std::chrono::milliseconds::zero() ||
      budgets.poll_slice <= std::chrono::milliseconds::zero() || !clock.now ||
      !clock.sleep || !wait_activity) {
    return std::unexpected(
        invalid_probe_request("version probe runtime is invalid"));
  }

  ProbeEvidence evidence{.agent = std::move(agent),
                         .requested = std::nullopt,
                         .executed = std::nullopt,
                         .pinned = false,
                         .outcome = ProbeOutcome::not_found,
                         .exit_code = -1,
                         .raw = "",
                         .parsed = std::nullopt};
  if (pin.has_value()) {
    evidence.pinned = true;
    evidence.requested = *pin;
    struct stat status{};
    if (::stat(evidence.requested->c_str(), &status) != 0) {
      const int stat_error = errno;
      if (stat_error != ENOENT && stat_error != ENOTDIR) {
        evidence.outcome = ProbeOutcome::not_accessible;
      }
      return evidence;
    }
    constexpr mode_t kExecutableBits = S_IXUSR | S_IXGRP | S_IXOTH;
    if (!S_ISREG(status.st_mode) || (status.st_mode & kExecutableBits) == 0) {
      evidence.outcome = ProbeOutcome::not_executable;
      return evidence;
    }
    evidence.executed = evidence.requested;
  } else {
    auto resolved = resolve_from_path(evidence.agent, getenv);
    if (resolved.failed) {
      evidence.outcome = ProbeOutcome::spawn_error;
      return evidence;
    }
    evidence.executed = std::move(resolved.path);
    if (!evidence.executed.has_value()) {
      return evidence;
    }
  }

  const auto executable = evidence.executed->string();
  const SpawnRequest request{
      .executable = *evidence.executed,
      .argv = {executable, "--version"},
      .env = parent_environment(),
      .stderr_mode = StderrMode::merge_into_stdout,
      .stdout_file = std::nullopt,
      .stdout_cap = kCaptureLimit + 4U,
      .stderr_cap = 0U,
      .budgets = budgets};
  auto spawned = subprocess_detail::run_argv_traced(
      request, clock, wait_activity, phase_sink);
  if (!spawned.has_value()) {
    return std::unexpected(std::move(spawned.error()));
  }

  evidence.raw = sanitize_capture(spawned->stdout_bytes, kCaptureLimit);
  evidence.exit_code = spawned->exit_code;
  if (spawned->timed_out) {
    evidence.outcome = ProbeOutcome::timeout;
  } else if (spawned->io_failed) {
    evidence.outcome = ProbeOutcome::probe_io_error;
  } else if (spawned->spawn_failed) {
    evidence.outcome = ProbeOutcome::spawn_error;
  } else {
    evidence.outcome = spawned->exit_code == 0 ? ProbeOutcome::ok
                                               : ProbeOutcome::nonzero_exit;
  }
  return evidence;
}

#endif

}  // namespace biv::support
