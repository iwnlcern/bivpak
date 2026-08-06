#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "core/support/probe.hpp"

namespace {

namespace fs = std::filesystem;

class TempDir {
 public:
  explicit TempDir(const std::string_view name)
      : path_{fs::temp_directory_path() / ("biv-probe-" + std::string{name} +
                                           "-" + std::to_string(::getpid()))} {
    fs::remove_all(path_);
    fs::create_directories(path_);
  }

  ~TempDir() { fs::remove_all(path_); }

  TempDir(const TempDir&) = delete;
  TempDir& operator=(const TempDir&) = delete;

  const fs::path& path() const { return path_; }

 private:
  fs::path path_;
};

fs::path write_executable(const fs::path& path, const std::string_view body) {
  fs::create_directories(path.parent_path());
  std::ofstream out{path};
  REQUIRE(out);
  out << "#!/bin/sh\n" << body;
  out.close();
  REQUIRE(::chmod(path.c_str(), 0700) == 0);
  return path;
}

fs::path write_invalid_executable(const fs::path& path) {
  fs::create_directories(path.parent_path());
  constexpr std::array<unsigned char, 16> kInvalidElf{
      0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  std::ofstream out{path, std::ios::binary};
  REQUIRE(out);
  out.write(reinterpret_cast<const char*>(kInvalidElf.data()),
            static_cast<std::streamsize>(kInvalidElf.size()));
  out.close();
  REQUIRE(::chmod(path.c_str(), 0700) == 0);
  return path;
}

std::function<std::optional<std::string>(std::string_view)> getenv_with_path(
    const std::string& path) {
  return [path](const std::string_view name) -> std::optional<std::string> {
    return name == "PATH" ? std::optional<std::string>{path} : std::nullopt;
  };
}

std::optional<std::string> no_environment(const std::string_view) {
  return std::nullopt;
}

biv::expected<biv::support::ProbeEvidence> invoke_probe(
    std::string agent, const std::optional<fs::path>& pin,
    const biv::support::Getenv& getenv,
    const std::chrono::milliseconds timeout) {
  auto budgets = biv::support::ProbeBudgets{};
  budgets.probe_wall = timeout;
  return biv::support::run_version_probe(
      std::move(agent), pin, getenv, budgets);
}

bool process_is_gone(const pid_t pid) {
  for (size_t attempt = 0; attempt < 50; ++attempt) {
    if (::kill(pid, 0) == -1 && errno == ESRCH) {
      return true;
    }
    ::usleep(20'000);
  }
  return false;
}

std::chrono::microseconds process_cpu_time() {
  rusage usage{};
  REQUIRE(::getrusage(RUSAGE_SELF, &usage) == 0);
  const auto user = std::chrono::seconds{usage.ru_utime.tv_sec} +
                    std::chrono::microseconds{usage.ru_utime.tv_usec};
  const auto system = std::chrono::seconds{usage.ru_stime.tv_sec} +
                      std::chrono::microseconds{usage.ru_stime.tv_usec};
  return std::chrono::duration_cast<std::chrono::microseconds>(user + system);
}

std::size_t proven_pipe_capacity() {
#if defined(F_GETPIPE_SZ)
  std::array<int, 2> descriptors{-1, -1};
  REQUIRE(::pipe(descriptors.data()) == 0);
  const int capacity = ::fcntl(descriptors.front(), F_GETPIPE_SZ);
  ::close(descriptors.front());
  ::close(descriptors.back());
  REQUIRE(capacity > 0);
  return static_cast<std::size_t>(capacity);
#elif defined(__APPLE__)
  // Darwin pipes are bounded below this deliberately conservative test ceiling.
  return std::size_t{1024} * 1024U;
#else
#error "A proven pipe-capacity bound is required for the drain test"
#endif
}

}  // namespace

TEST_CASE("version probe owns one shared production timeout constant") {
  CHECK(biv::support::kProbeTimeout == std::chrono::milliseconds{2000});
}

TEST_CASE("UTF-8 sanitization preserves scalars and replaces invalid input") {
  std::string input{"A"};
  input.append("\xC2\x9B", 2);
  input.append("\xC4\x80", 2);
  input.push_back(static_cast<char>(0x9B));
  input.append("\xE2", 1);

  std::string expected{"A"};
  expected.append("\xC2\x9B", 2);
  expected.append("\xC4\x80", 2);
  expected.append("\xEF\xBF\xBD", 3);
  expected.append("\xEF\xBF\xBD", 3);

  CHECK(biv::support::sanitize_utf8(input) == expected);
}

TEST_CASE(
    "version probe selects the first PATH executable and records provenance") {
  TempDir root{"path"};
  const auto first =
      write_executable(root.path() / "first" / "probe-agent", "printf first\n");
  write_executable(root.path() / "second" / "probe-agent", "printf second\n");
  const auto path = (root.path() / "first").string() + ":" +
                    (root.path() / "second").string();

  const auto result = invoke_probe(
      "probe-agent", std::nullopt, getenv_with_path(path),
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK_FALSE(result->pinned);
  CHECK_FALSE(result->requested.has_value());
  CHECK(result->executed == fs::absolute(first).lexically_normal());
  CHECK(result->raw == "first");
  CHECK_FALSE(result->parsed.has_value());
}

TEST_CASE(
    "version probe gives a pinned executable precedence and records its "
    "exact path") {
  TempDir root{"pin"};
  write_executable(root.path() / "path" / "probe-agent", "printf path\n");
  const auto pinned = write_executable(root.path() / "pinned" / "probe-agent",
                                       "printf pinned\n");
  const auto requested =
      root.path() / "pinned" / ".." / "pinned" / "probe-agent";

  const auto result = invoke_probe(
      "probe-agent", requested,
      getenv_with_path((root.path() / "path").string()),
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(result->pinned);
  CHECK(result->requested == requested);
  CHECK(result->executed == requested);
  CHECK(result->raw == "pinned");
}

TEST_CASE(
    "version probe does not fall back to PATH when a pinned executable "
    "is missing") {
  TempDir root{"missing-pin"};
  write_executable(root.path() / "path" / "probe-agent", "printf path\n");
  const auto missing = root.path() / "missing" / "probe-agent";

  const auto result = invoke_probe(
      "probe-agent", missing, getenv_with_path((root.path() / "path").string()),
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::not_found);
  CHECK(result->pinned);
  CHECK(result->requested == fs::absolute(missing).lexically_normal());
  CHECK_FALSE(result->executed.has_value());
  CHECK(result->raw.empty());

  const auto loop = root.path() / "loop";
  fs::create_symlink(loop.filename(), loop);
  const auto loop_result = invoke_probe(
      "probe-agent", loop, getenv_with_path((root.path() / "path").string()),
      std::chrono::milliseconds{500});

  REQUIRE(loop_result.has_value());
  CHECK(loop_result->outcome ==
        biv::support::ProbeOutcome::not_accessible);
  CHECK(loop_result->pinned);
  CHECK(loop_result->requested == fs::absolute(loop).lexically_normal());
  CHECK_FALSE(loop_result->executed.has_value());
  CHECK(loop_result->raw.empty());
}

TEST_CASE(
    "version probe distinguishes present non-executable pins from missing "
    "pins") {
  TempDir root{"non-executable-pin"};
  const auto pinned =
      write_executable(root.path() / "probe-agent", "printf should-not-run\n");
  REQUIRE(::chmod(pinned.c_str(), 0600) == 0);

  const auto file_result = invoke_probe(
      "probe-agent", pinned, no_environment, std::chrono::milliseconds{500});

  REQUIRE(file_result.has_value());
  CHECK(file_result->outcome ==
        biv::support::ProbeOutcome::not_executable);
  CHECK(file_result->pinned);
  CHECK(file_result->requested == fs::absolute(pinned).lexically_normal());
  CHECK_FALSE(file_result->executed.has_value());
  CHECK(file_result->raw.empty());

  const auto directory = root.path() / "probe-directory";
  fs::create_directory(directory);
  const auto directory_result = invoke_probe(
      "probe-agent", directory, no_environment,
      std::chrono::milliseconds{500});

  REQUIRE(directory_result.has_value());
  CHECK(directory_result->outcome ==
        biv::support::ProbeOutcome::not_executable);
  CHECK(directory_result->pinned);
  CHECK(directory_result->requested ==
        fs::absolute(directory).lexically_normal());
  CHECK_FALSE(directory_result->executed.has_value());
  CHECK(directory_result->raw.empty());
}

TEST_CASE(
    "version probe does not fall back to PATH when a pinned executable "
    "cannot spawn") {
  TempDir root{"bad-pin"};
  write_executable(root.path() / "path" / "probe-agent", "printf path\n");
  const auto pinned =
      write_invalid_executable(root.path() / "pinned" / "probe-agent");

  const auto result = invoke_probe(
      "probe-agent", pinned, getenv_with_path((root.path() / "path").string()),
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
#if defined(__APPLE__)
  CHECK(result->outcome == biv::support::ProbeOutcome::spawn_error);
#else
  CHECK(result->outcome == biv::support::ProbeOutcome::nonzero_exit);
#endif
  CHECK(result->pinned);
  CHECK(result->requested == fs::absolute(pinned).lexically_normal());
  CHECK(result->executed == fs::absolute(pinned).lexically_normal());
  CHECK(result->raw.empty());
}

TEST_CASE("version probe API states the sole sanctioned exec boundary") {
  const auto header =
      fs::path{BIV_SOURCE_DIR} / "src" / "core" / "support" / "probe.hpp";
  std::ifstream in{header};
  REQUIRE(in);
  const std::string source{std::istreambuf_iterator<char>{in},
                           std::istreambuf_iterator<char>{}};
  const auto declaration = source.find("run_version_probe(");
  REQUIRE(declaration != std::string::npos);
  const auto comment = source.rfind(
      "biv never invokes an agent with a prompt, never starts/resumes a "
      "session, never spends",
      declaration);
  REQUIRE(comment != std::string::npos);
  CHECK(source.find(
            "the disclosed, pinnable, shell-free `<binary> --version` probe "
            "is the sole sanctioned exec (operator ruling 062318)",
            comment) < declaration);
  CHECK(source.find(
            "The probe places the child in its OWN process group and, on "
            "cleanup, sweeps THAT GROUP",
            comment) < declaration);
  CHECK(source.find(
            "is NOT portably killable on the target platforms and is NOT "
            "claimed to be reaped",
            comment) < declaration);
  CHECK(source.find(
            "Group members are swept; a self-detached descendant is "
            "acknowledged, not silently promised",
            comment) < declaration);
}

TEST_CASE("version probe merges stdout and stderr") {
  TempDir root{"merged"};
  write_executable(root.path() / "probe-agent",
                   "printf stdout; printf stderr >&2\n");

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(result->raw == "stdoutstderr");
}

TEST_CASE("version probe reports a nonzero child exit") {
  TempDir root{"nonzero"};
  write_executable(root.path() / "probe-agent", "printf failed >&2\nexit 1\n");

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::nonzero_exit);
  CHECK(result->exit_code == 1);
  CHECK(result->raw == "failed");
}

TEST_CASE("version probe reports an unresolvable executable as not found") {
  const auto result = invoke_probe(
      "absent-probe-agent", std::nullopt, no_environment,
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::not_found);
  CHECK_FALSE(result->executed.has_value());
}

TEST_CASE("version probe leaves parsing adapter-owned") {
  TempDir root{"unparseable"};
  write_executable(root.path() / "probe-agent", "printf not-a-version\n");

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{500});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK_FALSE(result->parsed.has_value());
}

TEST_CASE(
    "version probe times out, reaps its direct child, and kills the "
    "process group") {
  TempDir root{"timeout"};
  const auto marker = root.path() / "grandchild.pid";
  const auto script =
      "trap '' TERM\n"
      "( trap '' TERM; while :; do sleep 1; done ) &\n"
      "printf '%s %s' \"$$\" \"$!\" > '" +
      marker.string() +
      "'\n"
      "while :; do sleep 1; done\n";
  write_executable(root.path() / "probe-agent", script);

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{1000});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::timeout);
  CHECK(result->exit_code == -1);
  REQUIRE(fs::exists(marker));
  std::ifstream in{marker};
  pid_t direct_child = -1;
  pid_t grandchild = -1;
  in >> direct_child >> grandchild;
  REQUIRE(direct_child > 0);
  REQUIRE(grandchild > 0);
  CHECK(process_is_gone(direct_child));
  CHECK(process_is_gone(grandchild));
}

TEST_CASE(
    "version probe acknowledges a successfully detached descendant") {
  TempDir root{"setsid-descendant"};
  const auto marker = root.path() / "escapee.txt";
  const auto script =
      "python3 - '" + marker.string() +
      "' <<'PY' &\n"
      "import os\n"
      "import sys\n"
      "import time\n"
      "probe_group = os.getpgrp()\n"
      "pid = os.fork()\n"
      "if pid == 0:\n"
      "    before_sid = os.getsid(0)\n"
      "    before_pgid = os.getpgid(0)\n"
      "    os.setsid()\n"
      "    after_sid = os.getsid(0)\n"
      "    after_pgid = os.getpgid(0)\n"
      "    with open(sys.argv[1], 'w', encoding='ascii') as out:\n"
      "        out.write(f'{os.getpid()} {probe_group} {before_sid} "
      "{before_pgid} {after_sid} {after_pgid}')\n"
      "        out.flush()\n"
      "    time.sleep(8)\n"
      "    os._exit(0)\n"
      "while True:\n"
      "    time.sleep(1)\n"
      "PY\n"
      "while [ ! -s '" +
      marker.string() +
      "' ]; do sleep 0.01; done\n"
      "trap '' TERM\n"
      "while :; do sleep 1; done\n";
  write_executable(root.path() / "probe-agent", script);
  auto budgets = biv::support::ProbeBudgets{};
  budgets.probe_wall = std::chrono::milliseconds{2000};
  budgets.term_grace = std::chrono::milliseconds{50};

  const auto result = biv::support::run_version_probe(
      "probe-agent", root.path() / "probe-agent", no_environment, budgets);

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::timeout);
  REQUIRE(fs::exists(marker));
  std::ifstream in{marker};
  pid_t escapee = -1;
  pid_t probe_group = -1;
  pid_t before_sid = -1;
  pid_t before_pgid = -1;
  pid_t after_sid = -1;
  pid_t after_pgid = -1;
  in >> escapee >> probe_group >> before_sid >> before_pgid >> after_sid >>
      after_pgid;
  REQUIRE(escapee > 0);
  REQUIRE(probe_group > 0);
  CHECK(before_pgid == probe_group);
  CHECK(after_sid == escapee);
  CHECK(after_pgid == escapee);
  CHECK(after_sid != before_sid);
  CHECK(::kill(-probe_group, 0) == -1);
  CHECK(errno == ESRCH);
  CHECK(::kill(escapee, 0) == 0);

  // The escapee is not this test's child. Disposal is kill + disappearance
  // observation only; its bounded self-lifetime is the abrupt-run backstop.
  CHECK(::kill(escapee, SIGKILL) == 0);
  CHECK(process_is_gone(escapee));
}

TEST_CASE("version probe preserves a UTF-8 scalar split across pipe reads") {
  TempDir root{"split-utf8"};
  write_executable(root.path() / "probe-agent",
                   "printf '\\303'; sleep 0.05; printf '\\251'\n");

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{1000});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(result->raw == std::string{"\xC3\xA9", 2});
}

TEST_CASE(
    "version probe replaces invalid and incomplete UTF-8 from the child") {
  TempDir root{"invalid-utf8"};
  write_executable(root.path() / "probe-agent", "printf '\\233A\\342'\n");

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{1000});

  std::string expected{"\xEF\xBF\xBD", 3};
  expected.push_back('A');
  expected.append("\xEF\xBF\xBD", 3);
  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(result->raw == expected);
}

TEST_CASE(
    "version probe caps on whole UTF-8 scalars and drains beyond pipe "
    "capacity") {
  TempDir root{"cap"};
  const auto marker = root.path() / "completed";
  const auto capacity = proven_pipe_capacity();
  const auto spew_size = std::size_t{65'535} + 2U + capacity + 1U;
  const auto script =
      "set -e\n"
      "head -c 65535 /dev/zero | tr '\\0' X\n"
      "printf '\\304\\200'\n"
      "head -c " +
      std::to_string(spew_size - 65'537U) +
      " /dev/zero | tr '\\0' Y\n"
      "printf completed > '" +
      marker.string() + "'\n";
  write_executable(root.path() / "probe-agent", script);

  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{3000});

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(fs::exists(marker));
  CHECK(result->raw.size() == 65'535);
  CHECK(result->raw.find_first_not_of('X') == std::string::npos);
  CHECK(biv::support::sanitize_utf8(result->raw) == result->raw);
}

TEST_CASE("version probe does not spin after pipe EOF before child exit") {
  TempDir root{"eof-before-exit"};
  write_executable(root.path() / "probe-agent",
                   "exec 1>&- 2>&-\n"
                   "sleep 0.25\n");

  const auto cpu_started = process_cpu_time();
  const auto wall_started = std::chrono::steady_clock::now();
  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{1000});
  const auto elapsed = std::chrono::steady_clock::now() - wall_started;
  const auto cpu_elapsed = process_cpu_time() - cpu_started;

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(elapsed >= std::chrono::milliseconds{200});
  CHECK(elapsed < std::chrono::milliseconds{800});
  CHECK(cpu_elapsed < std::chrono::milliseconds{100});

  TempDir ledger_root{"eof-fallback-ledger"};
  write_executable(ledger_root.path() / "probe-agent",
                   "exec 1>&- 2>&-\n"
                   "trap '' TERM\n"
                   "while :; do sleep 1; done\n");
  auto now = std::chrono::steady_clock::time_point{};
  std::vector<biv::support::ProbePhaseEvent> events;
  const biv::support::ProbeClock clock{
      .now = [&] { return now; },
      .sleep = [&](const std::chrono::milliseconds duration) {
        now += duration;
      }};
  const auto production_waiter = biv::support::production_probe_waiter();
  const biv::support::ProbeBudgets budgets{
      .probe_wall = std::chrono::milliseconds{10},
      .term_grace = std::chrono::milliseconds{0},
      .post_exit_drain = std::chrono::milliseconds{2},
      .post_kill_reap = std::chrono::milliseconds{2},
      .poll_slice = std::chrono::milliseconds{10}};

  const auto ledger_result = biv::support::run_version_probe(
      "probe-agent", ledger_root.path() / "probe-agent", no_environment,
      budgets, clock,
      [&](const int fd, const std::chrono::milliseconds) {
        return production_waiter(fd, std::chrono::milliseconds{500});
      },
      [&](const biv::support::ProbePhaseEvent& event) {
        events.push_back(event);
      });

  REQUIRE(ledger_result.has_value());
  CHECK(ledger_result->outcome == biv::support::ProbeOutcome::timeout);
  std::vector<biv::support::ProbePhaseEvent> fallback_events;
  for (const auto& event : events) {
    if (event.phase == "readiness" && event.result == "slept") {
      fallback_events.push_back(event);
    }
  }
  REQUIRE(fallback_events.size() == 1U);
  CHECK(fallback_events.front().requested == budgets.probe_wall);
  CHECK(fallback_events.front().elapsed == budgets.probe_wall);
  CHECK(fallback_events.front().result == "slept");
}

TEST_CASE(
    "version probe preserves clean exit while disposing a pipe-holding "
    "grandchild") {
  TempDir root{"clean-grandchild"};
  const auto marker = root.path() / "grandchild.pid";
  const auto script =
      "( trap '' TERM; while :; do sleep 1; done ) &\n"
      "printf '%s' \"$!\" > '" +
      marker.string() +
      "'\n"
      "exit 0\n";
  write_executable(root.path() / "probe-agent", script);

  const auto started = std::chrono::steady_clock::now();
  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{1000});
  const auto elapsed = std::chrono::steady_clock::now() - started;

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(result->exit_code == 0);
  REQUIRE(fs::exists(marker));
  std::ifstream in{marker};
  pid_t grandchild = -1;
  in >> grandchild;
  REQUIRE(grandchild > 0);
  CHECK(process_is_gone(grandchild));
  CHECK(elapsed < std::chrono::milliseconds{800});

  TempDir ledger_root{"post-exit-drain-ledger"};
  const auto exiting = ledger_root.path() / "direct-child-exiting";
  const auto ledger_script =
      "sleep 0.05\n"
      "( trap '' TERM; while :; do sleep 1; done ) &\n"
      "printf '%s' \"$$\" > '" +
      exiting.string() +
      "'\n"
      "exit 0\n";
  write_executable(ledger_root.path() / "probe-agent", ledger_script);
  auto now = std::chrono::steady_clock::time_point{};
  std::vector<biv::support::ProbePhaseEvent> events;
  std::size_t waiter_calls = 0;
  pid_t ledger_child = -1;
  bool child_waitable = false;
  const biv::support::ProbeClock clock{
      .now = [&] { return now; },
      .sleep = [&](const std::chrono::milliseconds duration) {
        now += duration;
      }};
  const biv::support::ProbeWaiter waiter =
      [&](int, const std::chrono::milliseconds requested) {
        ++waiter_calls;
        if (waiter_calls == 1U) {
          for (std::size_t attempt = 0; attempt < 200U && ledger_child <= 0;
               ++attempt) {
            std::ifstream marker_in{exiting};
            marker_in >> ledger_child;
            ::usleep(5'000);
          }
          for (std::size_t attempt = 0;
               attempt < 200U && ledger_child > 0 && !child_waitable;
               ++attempt) {
            siginfo_t info{};
            child_waitable =
                ::waitid(P_PID, static_cast<id_t>(ledger_child), &info,
                         WEXITED | WNOHANG | WNOWAIT) == 0 &&
                info.si_pid == ledger_child;
            if (!child_waitable) {
              ::usleep(5'000);
            }
          }
          return child_waitable ? biv::support::ReadinessResult::timed_out
                                : biv::support::ReadinessResult::failed;
        }
        now += requested;
        return biv::support::ReadinessResult::timed_out;
      };
  const biv::support::ProbeBudgets budgets{
      .probe_wall = std::chrono::milliseconds{1000},
      .term_grace = std::chrono::milliseconds{0},
      .post_exit_drain = std::chrono::milliseconds{7},
      .post_kill_reap = std::chrono::milliseconds{2},
      .poll_slice = std::chrono::milliseconds{10}};

  const auto ledger_result = biv::support::run_version_probe(
      "probe-agent", ledger_root.path() / "probe-agent", no_environment,
      budgets, clock, waiter,
      [&](const biv::support::ProbePhaseEvent& event) {
        events.push_back(event);
      });

  REQUIRE(ledger_result.has_value());
  REQUIRE(ledger_child > 0);
  REQUIRE(child_waitable);
  CHECK(ledger_result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(ledger_result->exit_code == 0);
  std::vector<biv::support::ProbePhaseEvent> drain_events;
  for (const auto& event : events) {
    if (event.phase == "post-exit-drain") {
      drain_events.push_back(event);
    }
  }
  REQUIRE(drain_events.size() == 1U);
  CHECK(drain_events.front().requested == budgets.post_exit_drain);
  CHECK(drain_events.front().elapsed == budgets.post_exit_drain);
  CHECK(drain_events.front().result == "timed_out");
}

TEST_CASE("post-KILL ownership transfers only after a reaper is established") {
  bool established = false;
  std::size_t owner_waits = 0;
  auto now = std::chrono::steady_clock::time_point{};
  const auto started = now;
  const biv::support::ProbeClock clock{
      .now = [&] { return now; },
      .sleep = [&](const std::chrono::milliseconds duration) {
        now += duration;
      }};
  const auto result = biv::support::probe_testing::exercise_post_kill_reap(
      [&](const bool blocking) {
        CHECK_FALSE(blocking);
        CHECK_FALSE(established);
        ++owner_waits;
        return biv::support::probe_testing::ControlledWaitResult::pending;
      },
      [&] {
        CHECK(now - started == std::chrono::milliseconds{5});
        established = true;
        return true;
      },
      std::chrono::milliseconds{5}, clock);

  CHECK(owner_waits > 0);
  CHECK(now - started == std::chrono::milliseconds{5});
  CHECK(established);
  CHECK(result.transferred);
  CHECK_FALSE(result.reaped);
}

TEST_CASE(
    "post-KILL ownership falls back to blocking reap when handoff fails") {
  std::size_t nonblocking_waits = 0;
  std::size_t blocking_waits = 0;
  const auto result = biv::support::probe_testing::exercise_post_kill_reap(
      [&](const bool blocking) {
        if (blocking) {
          ++blocking_waits;
          return biv::support::probe_testing::ControlledWaitResult::reaped;
        }
        ++nonblocking_waits;
        return biv::support::probe_testing::ControlledWaitResult::pending;
      },
      [] { return false; }, std::chrono::milliseconds{5},
      biv::support::production_probe_clock());

  CHECK(nonblocking_waits > 0);
  CHECK(blocking_waits == 1);
  CHECK(result.reaped);
  CHECK_FALSE(result.transferred);

  constexpr std::size_t kPacedWaits = 40;
  for (const auto wait_result :
       {biv::support::probe_testing::ControlledWaitResult::pending,
        biv::support::probe_testing::ControlledWaitResult::failed}) {
    DYNAMIC_SECTION(static_cast<int>(wait_result)) {
      std::size_t blocking_waits = 0;
      const auto cpu_started = process_cpu_time();
      const auto wall_started = std::chrono::steady_clock::now();
      const auto result =
          biv::support::probe_testing::exercise_post_kill_reap(
              [&](const bool blocking) {
                if (!blocking) {
                  return biv::support::probe_testing::ControlledWaitResult::
                      pending;
                }
                ++blocking_waits;
                return blocking_waits <= kPacedWaits
                           ? wait_result
                           : biv::support::probe_testing::
                                 ControlledWaitResult::reaped;
              },
              [] { return false; }, std::chrono::milliseconds{0},
              biv::support::production_probe_clock());
      const auto wall_elapsed =
          std::chrono::steady_clock::now() - wall_started;
      const auto cpu_elapsed = process_cpu_time() - cpu_started;

      CHECK(blocking_waits == kPacedWaits + 1U);
      CHECK(result.reaped);
      CHECK_FALSE(result.transferred);
      CHECK(wall_elapsed >= std::chrono::milliseconds{30});
      CHECK(cpu_elapsed < std::chrono::milliseconds{20});
    }
  }

  TempDir root{"saturating-grandchild"};
  const auto marker = root.path() / "grandchild.pid";
  const auto script =
      "pids=''\n"
      "i=0\n"
      "while [ \"$i\" -lt 8 ]; do\n"
      "  ( trap '' TERM; exec yes X ) &\n"
      "  pids=\"$pids $!\"\n"
      "  i=$((i + 1))\n"
      "done\n"
      "set -- $pids\n"
      "printf '%s' \"$1\" > '" +
      marker.string() +
      "'\n"
      "sleep 0.5\n"
      "exit 0\n";
  write_executable(root.path() / "probe-agent", script);

  const auto started = std::chrono::steady_clock::now();
  const auto saturating_result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{2000});
  const auto elapsed = std::chrono::steady_clock::now() - started;

  REQUIRE(saturating_result.has_value());
  REQUIRE(fs::exists(marker));
  CHECK(saturating_result->outcome == biv::support::ProbeOutcome::ok);
  CHECK(saturating_result->exit_code == 0);
  CHECK(saturating_result->raw.size() == 65'536);
  CHECK(elapsed < std::chrono::milliseconds{1500});
  std::ifstream in{marker};
  pid_t grandchild = -1;
  in >> grandchild;
  REQUIRE(grandchild > 0);
  CHECK(process_is_gone(grandchild));
}

TEST_CASE(
    "version probe enforces its wall timeout while the pipe stays readable") {
  TempDir root{"continuous-output-timeout"};
  const auto ready = root.path() / "producers-ready";
  write_executable(root.path() / "probe-agent",
                   "trap '' TERM\n"
                   "target=$$\n"
                   "( sleep 8; kill -KILL \"$target\" ) &\n"
                   "printf ready > '" +
                       ready.string() +
                       "'\n"
                       "exec yes X\n");

  const auto started = std::chrono::steady_clock::now();
  const auto result = invoke_probe(
      "probe-agent", root.path() / "probe-agent", no_environment,
      std::chrono::milliseconds{2000});
  const auto elapsed = std::chrono::steady_clock::now() - started;

  REQUIRE(result.has_value());
  REQUIRE(fs::exists(ready));
  CHECK(result->outcome == biv::support::ProbeOutcome::timeout);
  CHECK(result->raw.size() == 65'536);
  CHECK(elapsed < std::chrono::milliseconds{2600});
}

TEST_CASE(
    "version probe records post-call elapsed time across an EINTR retry") {
  TempDir root{"eintr-ledger"};
  write_executable(root.path() / "probe-agent",
                   "trap '' TERM\nwhile :; do sleep 1; done\n");
  auto now = std::chrono::steady_clock::time_point{};
  std::vector<biv::support::ProbePhaseEvent> events;
  std::size_t waiter_calls = 0;
  const biv::support::ProbeClock clock{
      .now = [&] { return now; },
      .sleep = [&](const std::chrono::milliseconds duration) {
        now += duration;
      }};
  const biv::support::ProbeWaiter waiter =
      [&](int, const std::chrono::milliseconds requested) {
        ++waiter_calls;
        if (waiter_calls == 1U) {
          now += std::chrono::milliseconds{2};
          return biv::support::ReadinessResult::interrupted;
        }
        now += requested;
        return biv::support::ReadinessResult::timed_out;
      };
  const biv::support::ProbeBudgets budgets{
      .probe_wall = std::chrono::milliseconds{10},
      .term_grace = std::chrono::milliseconds{3},
      .post_exit_drain = std::chrono::milliseconds{2},
      .post_kill_reap = std::chrono::milliseconds{2},
      .poll_slice = std::chrono::milliseconds{10}};

  const auto result = biv::support::run_version_probe(
      "probe-agent", root.path() / "probe-agent", no_environment, budgets,
      clock, waiter,
      [&](const biv::support::ProbePhaseEvent& event) {
        events.push_back(event);
      });

  REQUIRE(result.has_value());
  CHECK(result->outcome == biv::support::ProbeOutcome::timeout);
  REQUIRE(events.size() >= 2U);
  CHECK(events[0].phase == "readiness");
  CHECK(events[0].requested == std::chrono::milliseconds{10});
  CHECK(events[0].elapsed == std::chrono::milliseconds{2});
  CHECK(events[0].result == "interrupted");
  CHECK(events[1].phase == "readiness");
  CHECK(events[1].requested == std::chrono::milliseconds{8});
  CHECK(events[1].elapsed == std::chrono::milliseconds{8});
  CHECK(events[1].result == "timed_out");
  CHECK(waiter_calls == 2U);

  auto remaining = budgets.probe_wall;
  auto elapsed = std::chrono::milliseconds::zero();
  std::size_t interrupted = 0;
  for (const auto& event : events) {
    if (event.phase != "readiness") {
      continue;
    }
    CHECK(event.requested <= remaining);
    remaining -= std::min(remaining, event.elapsed);
    elapsed += event.elapsed;
    interrupted += event.result == "interrupted" ? 1U : 0U;
  }
  CHECK(elapsed == budgets.probe_wall);
  CHECK(interrupted == 1U);

  std::vector<biv::support::ProbePhaseEvent> term_grace_events;
  for (const auto& event : events) {
    if (event.phase == "term-grace") {
      term_grace_events.push_back(event);
    }
  }
  REQUIRE(term_grace_events.size() == 1U);
  CHECK(term_grace_events.front().requested == budgets.term_grace);
  CHECK(term_grace_events.front().elapsed == budgets.term_grace);
  CHECK(term_grace_events.front().result == "slept");
}

TEST_CASE("fatal readiness failure is a typed probe I/O outcome") {
  TempDir root{"readiness-failed"};
  const auto marker = root.path() / "direct-child.pid";
  write_executable(root.path() / "probe-agent", "printf '%s' \"$$\" > '" +
                                                    marker.string() +
                                                    "'\ntrap '' TERM\n"
                                                    "while :; do sleep 1; done\n");
  auto now = std::chrono::steady_clock::time_point{};
  std::vector<biv::support::ProbePhaseEvent> events;
  pid_t direct_child = -1;
  bool marker_ready = false;
  const biv::support::ProbeClock clock{
      .now = [&] { return now; },
      .sleep = [&](const std::chrono::milliseconds duration) {
        now += duration;
      }};
  const biv::support::ProbeBudgets budgets{
      .probe_wall = std::chrono::milliseconds{10},
      .term_grace = std::chrono::milliseconds{2},
      .post_exit_drain = std::chrono::milliseconds{2},
      .post_kill_reap = std::chrono::milliseconds{2},
      .poll_slice = std::chrono::milliseconds{10}};

  const auto result = biv::support::run_version_probe(
      "probe-agent", root.path() / "probe-agent", no_environment, budgets,
      clock,
      [&](int, const std::chrono::milliseconds requested) {
        for (std::size_t attempt = 0; attempt < 1'000U && direct_child <= 0;
             ++attempt) {
          std::ifstream marker_in{marker};
          marker_in >> direct_child;
          ::usleep(5'000);
        }
        marker_ready = direct_child > 0;
        now += std::min(requested, std::chrono::milliseconds{1});
        return biv::support::ReadinessResult::failed;
      },
      [&](const biv::support::ProbePhaseEvent& event) {
        events.push_back(event);
      });

  REQUIRE(result.has_value());
  REQUIRE(marker_ready);
  CHECK(result->outcome ==
        biv::support::ProbeOutcome::probe_io_error);
  REQUIRE_FALSE(events.empty());
  CHECK(events.front().phase == "readiness");
  CHECK(events.front().result == "failed");
  CHECK(events.front().elapsed == std::chrono::milliseconds{1});
  REQUIRE(direct_child > 0);
  CHECK(process_is_gone(direct_child));
}

TEST_CASE("version probe has one traced readiness primitive") {
  const auto waiter = biv::support::production_probe_waiter();
  std::array<int, 2> descriptors{-1, -1};
  REQUIRE(::pipe(descriptors.data()) == 0);
  CHECK(waiter(descriptors.front(), std::chrono::milliseconds{1}) ==
        biv::support::ReadinessResult::timed_out);
  REQUIRE(::close(descriptors.back()) == 0);
  CHECK(waiter(descriptors.front(), std::chrono::milliseconds{10}) ==
        biv::support::ReadinessResult::ready);
  const int invalid_descriptor = descriptors.front();
  REQUIRE(::close(descriptors.front()) == 0);
  CHECK(waiter(invalid_descriptor, std::chrono::milliseconds{1}) ==
        biv::support::ReadinessResult::failed);

  // The one-traced-readiness-primitive seal moved with its machinery from
  // probe.cpp to subprocess.cpp; probe.cpp's half strengthened to
  // zero-primitives.
  const auto source_path = fs::path{BIV_SOURCE_DIR} / "src" / "core" /
                           "support" / "subprocess.cpp";
  std::ifstream in{source_path};
  REQUIRE(in);
  const std::string source{std::istreambuf_iterator<char>{in},
                           std::istreambuf_iterator<char>{}};
  const auto probe_path =
      fs::path{BIV_SOURCE_DIR} / "src" / "core" / "support" / "probe.cpp";
  std::ifstream probe_in{probe_path};
  REQUIRE(probe_in);
  const std::string probe_source{std::istreambuf_iterator<char>{probe_in},
                                 std::istreambuf_iterator<char>{}};
  const auto occurrence_count = [](const std::string_view text,
                                   const std::string_view token) {
    std::size_t count = 0;
    for (std::size_t offset = 0;
         (offset = text.find(token, offset)) != std::string_view::npos;
         offset += token.size()) {
      ++count;
    }
    return count;
  };
  const auto waiter_begin =
      source.find("ReadinessResult production_wait_activity");
  const auto waiter_end = source.find("\n}\n", waiter_begin);
  REQUIRE(waiter_begin != std::string::npos);
  REQUIRE(waiter_end != std::string::npos);
  const auto waiter_source =
      source.substr(waiter_begin, waiter_end - waiter_begin);
  constexpr std::string_view kTimeoutBinding =
      "const auto timeout = std::clamp<std::int64_t>(\n"
      "      requested.count(), 0, std::numeric_limits<int>::max());";
  constexpr std::string_view kPollBinding =
      "::poll(&descriptor, 1, static_cast<int>(timeout))";
  CHECK(occurrence_count(waiter_source, "::poll(") == 1U);
  CHECK(occurrence_count(waiter_source, kTimeoutBinding) == 1U);
  CHECK(occurrence_count(waiter_source, kPollBinding) == 1U);

  auto without_waiter = source;
  without_waiter.erase(waiter_begin, waiter_end - waiter_begin);
  CHECK(without_waiter.find("::poll(") == std::string::npos);
  CHECK(without_waiter.find("::select(") == std::string::npos);
  CHECK(without_waiter.find("::ppoll(") == std::string::npos);
  CHECK(probe_source.find("::poll(") == std::string::npos);
  CHECK(probe_source.find("::select(") == std::string::npos);
  CHECK(probe_source.find("::ppoll(") == std::string::npos);

  const auto clock_begin = source.find("ProbeClock production_probe_clock()");
  const auto clock_end = source.find("\n}\n", clock_begin);
  REQUIRE(clock_begin != std::string::npos);
  REQUIRE(clock_end != std::string::npos);
  const auto clock_source =
      source.substr(clock_begin, clock_end - clock_begin);
  CHECK(occurrence_count(clock_source, "std::this_thread::sleep_for(") == 1U);
  CHECK(occurrence_count(clock_source,
                         "std::this_thread::sleep_for(duration);") == 1U);

  const auto reap_begin =
      source.find("static_cast<void>(settle_post_kill(");
  const auto reap_end =
      source.find("result.spawn_failed = ownership_failed;", reap_begin);
  REQUIRE(reap_begin != std::string::npos);
  REQUIRE(reap_end != std::string::npos);
  const auto reap_source = source.substr(reap_begin, reap_end - reap_begin);
  CHECK(occurrence_count(reap_source, "settle_post_kill(") == 1U);
  CHECK(occurrence_count(reap_source,
                         "request.budgets.post_kill_reap, clock));") == 1U);
}
