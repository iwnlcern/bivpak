#include "core/support/subprocess.hpp"

#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <string>
#include <string_view>
#include <thread>
#include <utility>

namespace biv::support {

namespace {

constexpr auto kReapPollSlice = std::chrono::milliseconds{1};

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

struct Pipe {
  Fd read;
  Fd write;
};

struct ChildState {
  bool reaped{false};
  bool status_available{false};
  int status{0};
};

class ByteCapture {
 public:
  ByteCapture(std::vector<std::byte>& bytes, const std::size_t cap,
              bool& output_incomplete)
      : bytes_{&bytes}, cap_{cap}, output_incomplete_{&output_incomplete} {}

  void write(const char* data, const std::size_t size) {
    const auto retained =
        std::min(size, cap_ - std::min(cap_, bytes_->size()));
    *output_incomplete_ = *output_incomplete_ || retained != size;
    const std::string_view input{data, retained};
    std::ranges::transform(
        input, std::back_inserter(*bytes_), [](const unsigned char value) {
          return static_cast<std::byte>(value);
        });
  }

 private:
  std::vector<std::byte>* bytes_;
  std::size_t cap_;
  bool* output_incomplete_;
};

BivError invalid_request(const std::string_view detail) {
  return BivError{ErrKind::InternalError, {}, std::string{detail}, EINVAL};
}

SpawnResult spawn_failure() {
  auto result = SpawnResult{};
  result.spawn_failed = true;
  return result;
}

bool valid_runtime(const SpawnRequest& request, const ProbeClock& clock,
                   const ProbeWaiter& wait_activity) {
  return !request.executable.empty() && !request.argv.empty() && clock.now &&
         clock.sleep && wait_activity &&
         request.budgets.probe_wall > std::chrono::milliseconds::zero() &&
         request.budgets.term_grace >= std::chrono::milliseconds::zero() &&
         request.budgets.post_exit_drain >=
             std::chrono::milliseconds::zero() &&
         request.budgets.post_kill_reap >=
             std::chrono::milliseconds::zero() &&
         request.budgets.poll_slice > std::chrono::milliseconds::zero();
}

bool contains_nul(const std::string& value) {
  return value.find('\0') != std::string::npos;
}

bool valid_strings(const SpawnRequest& request) {
  if (std::ranges::any_of(request.argv, contains_nul)) {
    return false;
  }
  return std::ranges::none_of(request.env, [](const std::string& item) {
    const auto delimiter = item.find('=');
    return contains_nul(item) || delimiter == std::string::npos ||
           delimiter == 0U;
  });
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
  return Fd{::fcntl(fd.get(), F_DUPFD_CLOEXEC, STDERR_FILENO + 1)};
}

std::optional<Pipe> make_pipe() {
  std::array<int, 2> descriptors{-1, -1};
  if (::pipe(descriptors.data()) != 0) {
    return std::nullopt;
  }
  Pipe pipe{.read = move_above_standard_streams(Fd{descriptors.front()}),
            .write = move_above_standard_streams(Fd{descriptors.back()})};
  if (!pipe.read.valid() || !pipe.write.valid() ||
      !set_close_on_exec(pipe.read.get()) ||
      !set_close_on_exec(pipe.write.get()) ||
      !set_nonblocking(pipe.read.get())) {
    return std::nullopt;
  }
  return pipe;
}

bool add_close(SpawnActions& actions, const Fd& fd) {
  return !fd.valid() ||
         ::posix_spawn_file_actions_addclose(actions.get(), fd.get()) == 0;
}

enum class DrainStatus { idle, progress, failed };

DrainStatus drain_once(Fd& fd, ByteCapture& capture) {
  std::array<char, 8192> buffer{};
  for (;;) {
    const auto count = ::read(fd.get(), buffer.data(), buffer.size());
    if (count > 0) {
      capture.write(buffer.data(), static_cast<std::size_t>(count));
      return DrainStatus::progress;
    }
    if (count == 0) {
      fd = Fd{};
      return DrainStatus::idle;
    }
    if (errno == EINTR) {
      continue;
    }
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return DrainStatus::idle;
    }
    fd = Fd{};
    return DrainStatus::failed;
  }
}

subprocess_detail::WaitResult reap_nonblocking(const pid_t pid,
                                                ChildState& child) {
  if (child.reaped) {
    return subprocess_detail::WaitResult::reaped;
  }
  for (;;) {
    const auto waited = ::waitpid(pid, &child.status, WNOHANG);
    if (waited == pid) {
      child.reaped = true;
      child.status_available = true;
      return subprocess_detail::WaitResult::reaped;
    }
    if (waited == 0) {
      return subprocess_detail::WaitResult::pending;
    }
    if (waited < 0 && errno == ECHILD) {
      child.reaped = true;
      return subprocess_detail::WaitResult::reaped;
    }
    if (waited < 0 && errno == EINTR) {
      continue;
    }
    return subprocess_detail::WaitResult::failed;
  }
}

subprocess_detail::WaitResult reap_direct(const pid_t pid,
                                          const bool blocking,
                                          ChildState& child) {
  if (!blocking) {
    return reap_nonblocking(pid, child);
  }
  if (child.reaped) {
    return subprocess_detail::WaitResult::reaped;
  }
  for (;;) {
    const auto waited = ::waitpid(pid, &child.status, 0);
    if (waited == pid) {
      child.reaped = true;
      child.status_available = true;
      return subprocess_detail::WaitResult::reaped;
    }
    if (waited < 0 && errno == ECHILD) {
      child.reaped = true;
      return subprocess_detail::WaitResult::reaped;
    }
    if (waited < 0 && errno == EINTR) {
      continue;
    }
    return subprocess_detail::WaitResult::failed;
  }
}

bool process_group_exists(const pid_t pid) {
  if (::kill(-pid, 0) == 0) {
    return true;
  }
  return errno == EPERM;
}

void* reap_detached_child(void* opaque_pid) {
  const std::unique_ptr<pid_t> owned_pid{static_cast<pid_t*>(opaque_pid)};
  int status = 0;
  for (;;) {
    const auto waited = ::waitpid(*owned_pid, &status, 0);
    if (waited == *owned_pid || (waited < 0 && errno == ECHILD)) {
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

void settle_exit_code(SpawnResult& result, const ChildState& child) {
  if (child.status_available && WIFEXITED(child.status)) {
    result.exit_code = WEXITSTATUS(child.status);
  } else if (child.status_available && WIFSIGNALED(child.status)) {
    result.exit_code = 128 + WTERMSIG(child.status);
  } else {
    result.spawn_failed = true;
  }
}

}  // namespace

ProbeClock production_probe_clock() {
  return ProbeClock{
      .now = [] { return std::chrono::steady_clock::now(); },
      .sleep = [](const std::chrono::milliseconds duration) {
        std::this_thread::sleep_for(duration);
      }};
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
  return (descriptor.revents & (POLLIN | POLLHUP | POLLERR)) != 0
             ? ReadinessResult::ready
             : ReadinessResult::timed_out;
}

ProbeWaiter production_probe_waiter() {
  return production_wait_activity;
}

namespace subprocess_detail {

PostKillResult settle_post_kill(
    const ControlledWait& wait_child, const EstablishReaper& establish_reaper,
    const std::chrono::milliseconds polling_window, const ProbeClock& clock) {
  const auto deadline = clock.now() + polling_window;
  while (true) {
    const auto result = wait_child(false);
    if (result == WaitResult::reaped) {
      return {.reaped = true, .transferred = false};
    }
    if (result == WaitResult::failed || clock.now() >= deadline) {
      break;
    }
    const auto remaining =
        std::chrono::ceil<std::chrono::milliseconds>(deadline - clock.now());
    if (remaining > std::chrono::milliseconds::zero()) {
      clock.sleep(std::min(remaining, kReapPollSlice));
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
    clock.sleep(kReapPollSlice);
  }
}

expected<SpawnResult> run_argv_traced(
    const SpawnRequest& request, const ProbeClock& clock,
    const ProbeWaiter& wait_activity, const ProbePhaseSink& phase_sink) {
  if (!valid_runtime(request, clock, wait_activity) ||
      !valid_strings(request)) {
    return std::unexpected(invalid_request("subprocess request is invalid"));
  }

  std::optional<Pipe> stdout_pipe;
  Fd stdout_file;
  if (request.stdout_file.has_value()) {
    stdout_file = move_above_standard_streams(Fd{::open(
        request.stdout_file->c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
        0600)});
    if (!stdout_file.valid()) {
      auto failure = spawn_failure();
      failure.io_failed = true;
      return failure;
    }
  } else {
    stdout_pipe = make_pipe();
    if (!stdout_pipe.has_value()) {
      return spawn_failure();
    }
  }

  std::optional<Pipe> stderr_pipe;
  if (request.stderr_mode == StderrMode::separate) {
    stderr_pipe = make_pipe();
    if (!stderr_pipe.has_value()) {
      return spawn_failure();
    }
  }

  Fd null_input{::open("/dev/null", O_RDONLY | O_CLOEXEC)};
  null_input = move_above_standard_streams(std::move(null_input));
  if (!null_input.valid()) {
    return spawn_failure();
  }

  SpawnActions actions;
  SpawnAttributes attributes;
  if (!actions.valid() || !attributes.valid()) {
    return spawn_failure();
  }

  const int stdout_target = request.stdout_file.has_value()
                                ? stdout_file.get()
                                : stdout_pipe.value().write.get();
  int stderr_target = stdout_target;
  if (request.stderr_mode == StderrMode::separate) {
    if (!stderr_pipe.has_value()) {
      return spawn_failure();
    }
    stderr_target = stderr_pipe->write.get();
  }
  const bool actions_ok =
      ::posix_spawn_file_actions_adddup2(actions.get(), null_input.get(),
                                         STDIN_FILENO) == 0 &&
      ::posix_spawn_file_actions_adddup2(actions.get(), stdout_target,
                                         STDOUT_FILENO) == 0 &&
      ::posix_spawn_file_actions_adddup2(actions.get(), stderr_target,
                                         STDERR_FILENO) == 0 &&
      (!stdout_pipe.has_value() ||
       (add_close(actions, stdout_pipe->read) &&
        add_close(actions, stdout_pipe->write))) &&
      (!stderr_pipe.has_value() ||
       (add_close(actions, stderr_pipe->read) &&
        add_close(actions, stderr_pipe->write))) &&
      add_close(actions, stdout_file) && add_close(actions, null_input);
  if (!actions_ok ||
      ::posix_spawnattr_setflags(attributes.get(), POSIX_SPAWN_SETPGROUP) !=
          0 ||
      ::posix_spawnattr_setpgroup(attributes.get(), 0) != 0) {
    return spawn_failure();
  }

  auto argv_storage = request.argv;
  std::vector<char*> argv;
  argv.reserve(argv_storage.size() + 1U);
  for (auto& item : argv_storage) {
    argv.push_back(item.data());
  }
  argv.push_back(nullptr);

  auto env_storage = request.env;
  std::vector<char*> env;
  env.reserve(env_storage.size() + 1U);
  for (auto& item : env_storage) {
    env.push_back(item.data());
  }
  env.push_back(nullptr);

  const auto executable = request.executable.string();
  pid_t pid = -1;
  const int spawn_result =
      ::posix_spawn(&pid, executable.c_str(), actions.get(), attributes.get(),
                    argv.data(), env.data());
  if (spawn_result != 0) {
    return spawn_failure();
  }

  if (stdout_pipe.has_value()) {
    stdout_pipe->write = Fd{};
  }
  if (stderr_pipe.has_value()) {
    stderr_pipe->write = Fd{};
  }
  stdout_file = Fd{};
  null_input = Fd{};

  SpawnResult result;
  ByteCapture stdout_capture{result.stdout_bytes, request.stdout_cap,
                             result.output_incomplete};
  ByteCapture stderr_capture{result.stderr_bytes, request.stderr_cap,
                             result.output_incomplete};
  ChildState child;
  bool ownership_failed = false;

  const auto wait_once = [&](const std::string_view phase, const int fd,
                             const std::chrono::milliseconds requested) {
    const auto before = clock.now();
    const auto readiness = wait_activity(fd, requested);
    const auto elapsed =
        std::chrono::ceil<std::chrono::milliseconds>(clock.now() - before);
    if (phase_sink) {
      phase_sink(ProbePhaseEvent{.phase = phase,
                                 .requested = requested,
                                 .elapsed = elapsed,
                                 .result = readiness_name(readiness)});
    }
    return readiness;
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
  const auto next_slice = [&](const auto deadline) {
    const auto now = clock.now();
    if (now >= deadline) {
      return std::chrono::milliseconds::zero();
    }
    return std::min(
        request.budgets.poll_slice,
        std::chrono::ceil<std::chrono::milliseconds>(deadline - now));
  };
  const auto read_fd = [&]() {
    if (stdout_pipe.has_value() && stdout_pipe->read.valid()) {
      return stdout_pipe->read.get();
    }
    return stderr_pipe.has_value() && stderr_pipe->read.valid()
               ? stderr_pipe->read.get()
               : -1;
  };
  const auto drain = [&]() {
    bool failed = false;
    bool progress = false;
    if (stdout_pipe.has_value() && stdout_pipe->read.valid()) {
      const auto status = drain_once(stdout_pipe->read, stdout_capture);
      failed = status == DrainStatus::failed;
      progress = status == DrainStatus::progress;
    }
    if (stderr_pipe.has_value() && stderr_pipe->read.valid()) {
      const auto status = drain_once(stderr_pipe->read, stderr_capture);
      failed = status == DrainStatus::failed || failed;
      progress = status == DrainStatus::progress || progress;
    }
    return std::pair{!failed, progress};
  };
  const auto close_reads = [&]() {
    if (stdout_pipe.has_value()) {
      stdout_pipe->read = Fd{};
    }
    if (stderr_pipe.has_value()) {
      stderr_pipe->read = Fd{};
    }
  };
  const auto terminate_group = [&]() {
    if (!process_group_exists(pid)) {
      return;
    }
    static_cast<void>(::kill(-pid, SIGTERM));
    if (request.budgets.term_grace > std::chrono::milliseconds::zero()) {
      sleep_once("term-grace", request.budgets.term_grace);
    }
    if (process_group_exists(pid)) {
      static_cast<void>(::kill(-pid, SIGKILL));
    }
  };

  const auto deadline = clock.now() + request.budgets.probe_wall;
  while (!child.reaped) {
    if (reap_nonblocking(pid, child) == WaitResult::failed) {
      ownership_failed = true;
      break;
    }
    if (child.reaped) {
      break;
    }
    const auto [drain_ok, drain_progress] = drain();
    if (!drain_ok) {
      result.io_failed = true;
      break;
    }
    if (reap_nonblocking(pid, child) == WaitResult::failed) {
      ownership_failed = true;
      break;
    }
    if (child.reaped) {
      break;
    }
    const auto requested = next_slice(deadline);
    if (requested <= std::chrono::milliseconds::zero()) {
      result.timed_out = true;
      break;
    }
    if (drain_progress) {
      continue;
    }
    const auto fd = read_fd();
    if (fd < 0) {
      sleep_once("readiness", requested);
      continue;
    }
    const auto readiness = wait_once("readiness", fd, requested);
    if (readiness == ReadinessResult::failed) {
      result.io_failed = true;
      break;
    }
  }

  if (child.reaped && !result.io_failed && !ownership_failed) {
    settle_exit_code(result, child);
    const auto drain_deadline =
        clock.now() + request.budgets.post_exit_drain;
    while (read_fd() >= 0) {
      const auto [drain_ok, drain_progress] = drain();
      if (!drain_ok) {
        result.io_failed = true;
        break;
      }
      const auto fd = read_fd();
      if (fd < 0) {
        break;
      }
      const auto requested = next_slice(drain_deadline);
      if (requested <= std::chrono::milliseconds::zero()) {
        break;
      }
      if (drain_progress) {
        continue;
      }
      const auto readiness = wait_once("post-exit-drain", fd, requested);
      if (readiness == ReadinessResult::failed) {
        result.io_failed = true;
        break;
      }
    }
    close_reads();
    terminate_group();
    return result;
  }

  terminate_group();
  close_reads();
  static_cast<void>(reap_nonblocking(pid, child));
  if (!child.reaped) {
    static_cast<void>(settle_post_kill(
        [&child, pid](const bool blocking) {
          return reap_direct(pid, blocking, child);
        },
        [pid] { return establish_eventual_reaper(pid); },
        request.budgets.post_kill_reap, clock));
  }
  result.spawn_failed = ownership_failed;
  return result;
}

}  // namespace subprocess_detail

expected<SpawnResult> run_argv(const SpawnRequest& request,
                               const ProbeClock& clock,
                               const ProbeWaiter& wait_activity) {
  return subprocess_detail::run_argv_traced(request, clock, wait_activity,
                                             ProbePhaseSink{});
}

}  // namespace biv::support
