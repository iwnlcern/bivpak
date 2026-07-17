#include "core/support/probe.hpp"

#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <spawn.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#if defined(__APPLE__)
#include <crt_externs.h>
#endif

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <limits>
#include <memory>
#include <new>
#include <string>
#include <string_view>
#include <thread>
#include <utility>

namespace biv::support {

namespace {

namespace fs = std::filesystem;

#if !defined(BIV_PROBE_TEST_SEAM_ONLY)
constexpr std::size_t kCaptureLimit = std::size_t{64} * 1024U;
#endif
constexpr auto kReapPollSlice = std::chrono::milliseconds{1};

enum class WaitResult { pending, reaped, failed };

struct PostKillResult {
  bool reaped{false};
  bool transferred{false};
};

PostKillResult settle_post_kill(
    const std::function<WaitResult(bool blocking)>& wait_child,
    const std::function<bool()>& establish_reaper,
    const std::chrono::milliseconds polling_window,
    const std::function<std::chrono::steady_clock::time_point()>& now,
    const std::function<void(std::chrono::milliseconds)>& sleep) {
  const auto deadline = now() + polling_window;
  while (true) {
    const auto result = wait_child(false);
    if (result == WaitResult::reaped) {
      return {.reaped = true, .transferred = false};
    }
    if (result == WaitResult::failed) {
      break;
    }
    if (now() >= deadline) {
      break;
    }
    const auto remaining =
        std::chrono::ceil<std::chrono::milliseconds>(deadline - now());
    if (remaining > std::chrono::milliseconds::zero()) {
      sleep(std::min(remaining, kReapPollSlice));
    }
  }

  if (establish_reaper()) {
    return {.reaped = false, .transferred = true};
  }

  for (;;) {
    const auto result = wait_child(true);
    if (result == WaitResult::reaped) {
      return {.reaped = true, .transferred = false};
    }
    sleep(kReapPollSlice);
  }
}

#if !defined(BIV_PROBE_TEST_SEAM_ONLY)

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

char** parent_environment() {
#if defined(__APPLE__)
  return *_NSGetEnviron();
#else
  return environ;
#endif
}

class Fd {
 public:
  Fd() = default;
  explicit Fd(const int value) : value_{value} {}
  ~Fd() {
    if (value_ >= 0) {
      ::close(value_);
    }
  }

  Fd(const Fd&) = delete;
  Fd& operator=(const Fd&) = delete;
  Fd(Fd&& other) noexcept : value_{std::exchange(other.value_, -1)} {}
  Fd& operator=(Fd&& other) noexcept {
    if (this != &other) {
      if (value_ >= 0) {
        ::close(value_);
      }
      value_ = std::exchange(other.value_, -1);
    }
    return *this;
  }

  [[nodiscard]] int get() const noexcept { return value_; }
  [[nodiscard]] bool valid() const noexcept { return value_ >= 0; }
  int release() noexcept { return std::exchange(value_, -1); }

 private:
  int value_{-1};
};

class SpawnActions {
 public:
  SpawnActions()
      : initialized_{::posix_spawn_file_actions_init(&value_) == 0} {}
  ~SpawnActions() {
    if (initialized_) {
      ::posix_spawn_file_actions_destroy(&value_);
    }
  }

  SpawnActions(const SpawnActions&) = delete;
  SpawnActions& operator=(const SpawnActions&) = delete;
  SpawnActions(SpawnActions&&) = delete;
  SpawnActions& operator=(SpawnActions&&) = delete;

  [[nodiscard]] bool valid() const noexcept { return initialized_; }
  [[nodiscard]] posix_spawn_file_actions_t* get() noexcept { return &value_; }

 private:
  posix_spawn_file_actions_t value_{};
  bool initialized_{false};
};

class SpawnAttributes {
 public:
  SpawnAttributes() : initialized_{::posix_spawnattr_init(&value_) == 0} {}
  ~SpawnAttributes() {
    if (initialized_) {
      ::posix_spawnattr_destroy(&value_);
    }
  }

  SpawnAttributes(const SpawnAttributes&) = delete;
  SpawnAttributes& operator=(const SpawnAttributes&) = delete;
  SpawnAttributes(SpawnAttributes&&) = delete;
  SpawnAttributes& operator=(SpawnAttributes&&) = delete;

  [[nodiscard]] bool valid() const noexcept { return initialized_; }
  [[nodiscard]] posix_spawnattr_t* get() noexcept { return &value_; }

 private:
  posix_spawnattr_t value_{};
  bool initialized_{false};
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

bool set_close_on_exec(const int fd) {
  const int flags = ::fcntl(fd, F_GETFD);
  return flags >= 0 && ::fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == 0;
}

bool set_nonblocking(const int fd) {
  const int flags = ::fcntl(fd, F_GETFL);
  return flags >= 0 && ::fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0;
}

Fd move_above_standard_streams(Fd fd) {
  if (!fd.valid() || fd.get() > STDERR_FILENO) {
    return fd;
  }
  const int duplicate = ::fcntl(fd.get(), F_DUPFD_CLOEXEC, STDERR_FILENO + 1);
  return Fd{duplicate};
}

enum class DrainStatus { drained, failed };

DrainStatus drain_pipe(const int fd, Utf8Capture& capture, bool& eof) {
  std::array<char, 8192> buffer{};
  for (;;) {
    const auto count = ::read(fd, buffer.data(), buffer.size());
    if (count > 0) {
      capture.write(
          std::string_view{buffer.data(), static_cast<std::size_t>(count)});
      return DrainStatus::drained;
    }
    if (count == 0) {
      eof = true;
      return DrainStatus::drained;
    }
    if (errno == EINTR) {
      continue;
    }
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return DrainStatus::drained;
    }
    eof = true;
    return DrainStatus::failed;
  }
}

struct ChildState {
  bool reaped{false};
  bool status_available{false};
  int status{0};
};

WaitResult reap_nonblocking(const pid_t pid, ChildState& child) {
  if (child.reaped) {
    return WaitResult::reaped;
  }
  for (;;) {
    const auto waited = ::waitpid(pid, &child.status, WNOHANG);
    if (waited == pid) {
      child.reaped = true;
      child.status_available = true;
      return WaitResult::reaped;
    }
    if (waited == 0) {
      return WaitResult::pending;
    }
    if (waited < 0 && errno == ECHILD) {
      child.reaped = true;
      return WaitResult::reaped;
    }
    if (waited < 0 && errno == EINTR) {
      continue;
    }
    return WaitResult::failed;
  }
}

WaitResult reap_direct(const pid_t pid, const bool blocking,
                       ChildState& child) {
  if (!blocking) {
    return reap_nonblocking(pid, child);
  }
  if (child.reaped) {
    return WaitResult::reaped;
  }
  for (;;) {
    const auto waited = ::waitpid(pid, &child.status, 0);
    if (waited == pid) {
      child.reaped = true;
      child.status_available = true;
      return WaitResult::reaped;
    }
    if (waited < 0 && errno == ECHILD) {
      child.reaped = true;
      return WaitResult::reaped;
    }
    if (waited < 0 && errno == EINTR) {
      continue;
    }
    return WaitResult::failed;
  }
}

bool process_group_exists(const pid_t pid) {
  if (::kill(-pid, 0) == 0) {
    return true;
  }
  return errno == EPERM;
}

ReadinessResult production_wait_activity(
    const int fd, const std::chrono::milliseconds requested) {
  if (fd < 0 || requested <= std::chrono::milliseconds::zero()) {
    return ReadinessResult::timed_out;
  }
  pollfd descriptor{.fd = fd,
                    .events = static_cast<short>(POLLIN | POLLHUP | POLLERR),
                    .revents = 0};
  const auto timeout = std::clamp<std::int64_t>(
      requested.count(), 0, std::numeric_limits<int>::max());
  const int result = ::poll(&descriptor, 1, static_cast<int>(timeout));
  if (result == 0) {
    return ReadinessResult::timed_out;
  }
  if (result < 0) {
    return errno == EINTR ? ReadinessResult::interrupted
                          : ReadinessResult::failed;
  }
  if ((descriptor.revents & POLLNVAL) != 0) {
    return ReadinessResult::failed;
  }
  if ((descriptor.revents & (POLLIN | POLLHUP | POLLERR)) != 0) {
    return ReadinessResult::ready;
  }
  return ReadinessResult::timed_out;
}

std::string_view readiness_name(const ReadinessResult result) {
  switch (result) {
    case ReadinessResult::ready:
      return "ready";
    case ReadinessResult::timed_out:
      return "timed_out";
    case ReadinessResult::interrupted:
      return "interrupted";
    case ReadinessResult::failed:
      return "failed";
  }
  return "failed";
}

ProbeEvidence spawn_failure(ProbeEvidence evidence) {
  evidence.outcome = ProbeOutcome::spawn_error;
  return evidence;
}

void settle_outcome(ProbeEvidence& evidence, const ChildState& child) {
  if (!child.status_available) {
    evidence.outcome = ProbeOutcome::spawn_error;
    return;
  }
  if (WIFEXITED(child.status)) {
    evidence.exit_code = WEXITSTATUS(child.status);
    evidence.outcome =
        evidence.exit_code == 0 ? ProbeOutcome::ok : ProbeOutcome::nonzero_exit;
    return;
  }
  if (WIFSIGNALED(child.status)) {
    evidence.exit_code = 128 + WTERMSIG(child.status);
    evidence.outcome = ProbeOutcome::nonzero_exit;
    return;
  }
  evidence.outcome = ProbeOutcome::spawn_error;
}

void* reap_detached_child(void* opaque_pid) {
  const std::unique_ptr<pid_t> owned_pid{
      static_cast<pid_t*>(opaque_pid)};
  const pid_t pid = *owned_pid;
  int status = 0;
  for (;;) {
    const auto waited = ::waitpid(pid, &status, 0);
    if (waited == pid || (waited < 0 && errno == ECHILD)) {
      return nullptr;
    }
    if (waited < 0 && errno == EINTR) {
      continue;
    }
    return nullptr;
  }
}

bool establish_eventual_reaper(const pid_t pid) {
  try {
    auto owned_pid = std::make_unique<pid_t>(pid);
    pthread_attr_t attributes{};
    if (::pthread_attr_init(&attributes) != 0) {
      return false;
    }
    const int detach_result = ::pthread_attr_setdetachstate(
        &attributes, PTHREAD_CREATE_DETACHED);
    if (detach_result != 0) {
      static_cast<void>(::pthread_attr_destroy(&attributes));
      return false;
    }
    pthread_t reaper{};
    const int create_result = ::pthread_create(
        &reaper, &attributes, reap_detached_child, owned_pid.get());
    static_cast<void>(::pthread_attr_destroy(&attributes));
    if (create_result != 0) {
      return false;
    }
    [[maybe_unused]] const auto reaper_owned_pid = owned_pid.release();
    return true;
  } catch (const std::bad_alloc&) {
    return false;
  }
}

#endif

}  // namespace

#if !defined(BIV_PROBE_TEST_SEAM_ONLY)
ProbeClock production_probe_clock() {
  return ProbeClock{
      .now = [] { return std::chrono::steady_clock::now(); },
      .sleep = [](const std::chrono::milliseconds duration) {
        std::this_thread::sleep_for(duration);
      }};
}

ProbeWaiter production_probe_waiter() {
  return production_wait_activity;
}
#endif

#if defined(BIV_PROBE_TESTING)
namespace probe_testing {

PostKillReapResult exercise_post_kill_reap(
    const ControlledWait& wait_child, const EstablishReaper& establish_reaper,
    const std::chrono::milliseconds polling_window, const ProbeClock& clock) {
  const auto result = settle_post_kill(
      [&wait_child](const bool blocking) {
        switch (wait_child(blocking)) {
          case ControlledWaitResult::pending:
            return WaitResult::pending;
          case ControlledWaitResult::reaped:
            return WaitResult::reaped;
          case ControlledWaitResult::failed:
            return WaitResult::failed;
        }
        return WaitResult::failed;
      },
      establish_reaper, polling_window, clock.now, clock.sleep);
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
      budgets.poll_slice <= std::chrono::milliseconds::zero() ||
      !clock.now || !clock.sleep || !wait_activity) {
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
    if (!S_ISREG(status.st_mode) ||
        (status.st_mode & kExecutableBits) == 0) {
      evidence.outcome = ProbeOutcome::not_executable;
      return evidence;
    }
    evidence.executed = evidence.requested;
  } else {
    auto resolved = resolve_from_path(evidence.agent, getenv);
    if (resolved.failed) {
      return spawn_failure(std::move(evidence));
    }
    evidence.executed = std::move(resolved.path);
    if (!evidence.executed.has_value()) {
      return evidence;
    }
  }

  std::array<int, 2> pipe_fds{-1, -1};
  if (::pipe(pipe_fds.data()) != 0) {
    return spawn_failure(std::move(evidence));
  }
  Fd read_end{pipe_fds.front()};
  Fd write_end{pipe_fds.back()};
  read_end = move_above_standard_streams(std::move(read_end));
  write_end = move_above_standard_streams(std::move(write_end));
  if (!read_end.valid() || !write_end.valid()) {
    return spawn_failure(std::move(evidence));
  }
  if (!set_close_on_exec(read_end.get()) ||
      !set_close_on_exec(write_end.get()) || !set_nonblocking(read_end.get())) {
    return spawn_failure(std::move(evidence));
  }

  Fd null_input{::open("/dev/null", O_RDONLY | O_CLOEXEC)};
  null_input = move_above_standard_streams(std::move(null_input));
  if (!null_input.valid()) {
    return spawn_failure(std::move(evidence));
  }

  SpawnActions actions;
  SpawnAttributes attributes;
  if (!actions.valid() || !attributes.valid()) {
    return spawn_failure(std::move(evidence));
  }

  const auto action_failed =
      ::posix_spawn_file_actions_adddup2(actions.get(), null_input.get(),
                                         STDIN_FILENO) != 0 ||
      ::posix_spawn_file_actions_adddup2(actions.get(), write_end.get(),
                                         STDOUT_FILENO) != 0 ||
      ::posix_spawn_file_actions_adddup2(actions.get(), write_end.get(),
                                         STDERR_FILENO) != 0 ||
      ::posix_spawn_file_actions_addclose(actions.get(), read_end.get()) != 0 ||
      ::posix_spawn_file_actions_addclose(actions.get(), write_end.get()) !=
          0 ||
      ::posix_spawn_file_actions_addclose(actions.get(), null_input.get()) != 0;
  if (action_failed ||
      ::posix_spawnattr_setflags(attributes.get(), POSIX_SPAWN_SETPGROUP) !=
          0 ||
      ::posix_spawnattr_setpgroup(attributes.get(), 0) != 0) {
    return spawn_failure(std::move(evidence));
  }

  std::string executable = evidence.executed->string();
  std::string version_flag = "--version";
  std::array<char*, 3> argv{executable.data(), version_flag.data(), nullptr};
  pid_t pid = -1;
  const int spawn_result =
      ::posix_spawn(&pid, executable.c_str(), actions.get(), attributes.get(),
                    argv.data(), parent_environment());
  if (spawn_result != 0) {
    return spawn_failure(std::move(evidence));
  }

  write_end = Fd{};
  null_input = Fd{};
  const auto wait_once = [&](const std::string_view phase, const int fd,
                             const std::chrono::milliseconds requested) {
    const auto before = clock.now();
    const auto result = wait_activity(fd, requested);
    const auto elapsed =
        std::chrono::ceil<std::chrono::milliseconds>(clock.now() - before);
    if (phase_sink) {
      phase_sink(ProbePhaseEvent{.phase = phase,
                                 .requested = requested,
                                 .elapsed = elapsed,
                                 .result = readiness_name(result)});
    }
    return result;
  };
  const auto sleep_once = [&](const std::string_view phase,
                              const std::chrono::milliseconds requested) {
    const auto before = clock.now();
    clock.sleep(requested);
    const auto elapsed =
        std::chrono::ceil<std::chrono::milliseconds>(clock.now() - before);
    if (phase_sink) {
      phase_sink(ProbePhaseEvent{.phase = phase,
                                 .requested = requested,
                                 .elapsed = elapsed,
                                 .result = "slept"});
    }
  };
  const auto next_slice =
      [&](const std::chrono::steady_clock::time_point deadline) {
        const auto now = clock.now();
        if (now >= deadline) {
          return std::chrono::milliseconds::zero();
        }
        return std::min(
            budgets.poll_slice,
            std::chrono::ceil<std::chrono::milliseconds>(deadline - now));
      };
  const auto terminate_group = [&](const pid_t group) {
    if (!process_group_exists(group)) {
      return;
    }
    static_cast<void>(::kill(-group, SIGTERM));
    if (budgets.term_grace > std::chrono::milliseconds::zero()) {
      sleep_once("term-grace", budgets.term_grace);
    }
    if (process_group_exists(group)) {
      static_cast<void>(::kill(-group, SIGKILL));
    }
  };

  const auto deadline = clock.now() + budgets.probe_wall;
  Utf8Capture capture{kCaptureLimit};
  bool pipe_eof = false;
  ChildState child;
  bool timed_out = false;
  bool io_failed = false;
  bool ownership_failed = false;

  while (!child.reaped) {
    if (reap_nonblocking(pid, child) == WaitResult::failed) {
      ownership_failed = true;
      break;
    }
    if (child.reaped) {
      break;
    }

    if (read_end.valid()) {
      const auto drain = drain_pipe(read_end.get(), capture, pipe_eof);
      if (drain == DrainStatus::failed) {
        io_failed = true;
        read_end = Fd{};
        break;
      }
      if (pipe_eof) {
        read_end = Fd{};
      }
      if (reap_nonblocking(pid, child) == WaitResult::failed) {
        ownership_failed = true;
        break;
      }
      if (child.reaped) {
        break;
      }
    }

    const auto requested = next_slice(deadline);
    if (requested <= std::chrono::milliseconds::zero()) {
      timed_out = true;
      break;
    }
    if (!read_end.valid()) {
      sleep_once("readiness", requested);
      continue;
    }
    const auto readiness =
        wait_once("readiness", read_end.get(), requested);
    if (readiness == ReadinessResult::failed) {
      io_failed = true;
      read_end = Fd{};
      break;
    }
    if (readiness == ReadinessResult::interrupted) {
      continue;
    }
  }

  if (child.reaped && !timed_out && !io_failed && !ownership_failed) {
    settle_outcome(evidence, child);
    const auto drain_deadline = clock.now() + budgets.post_exit_drain;
    while (read_end.valid()) {
      const auto drain = drain_pipe(read_end.get(), capture, pipe_eof);
      if (drain == DrainStatus::failed || pipe_eof) {
        io_failed = drain == DrainStatus::failed;
        read_end = Fd{};
        break;
      }
      const auto requested = next_slice(drain_deadline);
      if (requested <= std::chrono::milliseconds::zero()) {
        break;
      }
      const auto readiness =
          wait_once("post-exit-drain", read_end.get(), requested);
      if (readiness == ReadinessResult::failed) {
        io_failed = true;
        read_end = Fd{};
        break;
      }
      if (readiness == ReadinessResult::interrupted) {
        continue;
      }
    }
    read_end = Fd{};
    terminate_group(pid);
    capture.finish();
    evidence.raw = capture.take();
    if (io_failed) {
      evidence.outcome = ProbeOutcome::probe_io_error;
    }
    return evidence;
  }

  if (timed_out || io_failed || ownership_failed) {
    terminate_group(pid);
    read_end = Fd{};
    static_cast<void>(reap_nonblocking(pid, child));
    if (!child.reaped) {
      static_cast<void>(settle_post_kill(
          [&child, pid](const bool blocking) {
            return reap_direct(pid, blocking, child);
          },
          [pid] { return establish_eventual_reaper(pid); },
          budgets.post_kill_reap, clock.now,
          [&](const std::chrono::milliseconds requested) {
            sleep_once("post-kill-reap", requested);
          }));
    }
    capture.finish();
    evidence.raw = capture.take();
    evidence.outcome = timed_out
                           ? ProbeOutcome::timeout
                           : io_failed ? ProbeOutcome::probe_io_error
                                       : ProbeOutcome::spawn_error;
    return evidence;
  }

  capture.finish();
  evidence.raw = capture.take();
  evidence.outcome = ProbeOutcome::spawn_error;
  return evidence;
}

#endif

}  // namespace biv::support
