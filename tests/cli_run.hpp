#pragma once

#include <array>
#include <cerrno>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <fcntl.h>
#include <poll.h>
#include <sys/wait.h>
#include <unistd.h>
#include <catch2/catch_test_macros.hpp>

namespace {

struct RunResult {
  int code{0};
  std::string out;
  std::string err;
};

static inline std::string read_text(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  REQUIRE(in);
  return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}

static inline RunResult run_cmd(const std::string& args, const std::filesystem::path& cwd) {
  const auto out = cwd / "stdout.txt";
  const auto err = cwd / "stderr.txt";
  const std::string command = "cd '" + cwd.string() + "' && '" + std::string{BIV_BINARY_PATH} + "' " + args +
                              " >'" + out.string() + "' 2>'" + err.string() + "'";
  const int rc = std::system(command.c_str());
  int code = rc;
  if (WIFEXITED(rc)) {
    code = WEXITSTATUS(rc);
  }
  return RunResult{.code = code, .out = read_text(out), .err = read_text(err)};
}

static inline RunResult run_cmd_pty(const std::string& args, const std::filesystem::path& cwd,
                      std::string_view input) {
  const int master = ::posix_openpt(O_RDWR | O_NOCTTY);
  REQUIRE(master >= 0);
  REQUIRE(::grantpt(master) == 0);
  REQUIRE(::unlockpt(master) == 0);
  const char* const slave_name = ::ptsname(master);
  REQUIRE(slave_name != nullptr);
  const pid_t child = ::fork();
  REQUIRE(child >= 0);
  if (child == 0) {
    const int slave = ::open(slave_name, O_RDWR);
    if (slave < 0 || ::dup2(slave, STDIN_FILENO) < 0 || ::dup2(slave, STDOUT_FILENO) < 0 ||
        ::dup2(slave, STDERR_FILENO) < 0 || ::chdir(cwd.c_str()) != 0) {
      _exit(127);
    }
    (void)::close(slave);
    (void)::close(master);
    const std::string command = "exec '" + std::string{BIV_BINARY_PATH} + "' " + args;
    ::execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
    _exit(127);
  }
  REQUIRE(::write(master, input.data(), input.size()) == static_cast<ssize_t>(input.size()));
  std::string output;
  std::array<char, 4096> buffer{};
  while (true) {
    const ssize_t count = ::read(master, buffer.data(), buffer.size());
    if (count > 0) {
      output.append(buffer.data(), static_cast<size_t>(count));
      continue;
    }
    if (count < 0 && errno == EINTR) {
      continue;
    }
    if (count < 0 && errno == EIO) {
      break;
    }
    REQUIRE(count == 0);
    break;
  }
  REQUIRE(::close(master) == 0);
  int status = 0;
  while (::waitpid(child, &status, 0) < 0) {
    REQUIRE(errno == EINTR);
  }
  REQUIRE(WIFEXITED(status));
  return {.code = WEXITSTATUS(status), .out = output, .err = output};
}

static inline RunResult run_cmd_closed_stderr(const std::string& args,
                                const std::filesystem::path& cwd) {
  const auto out = cwd / "stdout.txt";
  const std::string command =
      "cd '" + cwd.string() + "' && '" + std::string{BIV_BINARY_PATH} +
      "' " + args + " >'" + out.string() + "' 2>&-";
  const int rc = std::system(command.c_str());
  int code = rc;
  if (WIFEXITED(rc)) {
    code = WEXITSTATUS(rc);
  }
  return RunResult{.code = code, .out = read_text(out), .err = ""};
}

struct SplitRunResult {
  int code;
  std::string out;
  std::string err;
  bool stdin_tty;
  bool stdout_tty;
  bool stderr_tty;
};

// The legacy runners above stay verbatim. This shell runner also provides the
// identical-child one-PTY negative control for the split descriptor topology.
static inline SplitRunResult run_shell_pty_topology(
    const std::string& command, const std::filesystem::path& cwd,
    std::string_view input, bool split) {
  const int master = ::posix_openpt(O_RDWR | O_NOCTTY);
  REQUIRE(master >= 0);
  REQUIRE(::grantpt(master) == 0);
  REQUIRE(::unlockpt(master) == 0);
  const char* const slave_name = ::ptsname(master);
  REQUIRE(slave_name != nullptr);
  int stdout_pipe[2];
  REQUIRE(::pipe(stdout_pipe) == 0);
  std::string facts_name = (cwd / "tty-facts-XXXXXX").string();
  const int facts_fd = ::mkstemp(facts_name.data());
  REQUIRE(facts_fd >= 0);
  const pid_t child = ::fork();
  REQUIRE(child >= 0);
  if (child == 0) {
    const int slave = ::open(slave_name, O_RDWR);
    if (slave < 0 || ::dup2(slave, STDIN_FILENO) < 0 ||
        ::dup2(split ? stdout_pipe[1] : slave, STDOUT_FILENO) < 0 ||
        ::dup2(slave, STDERR_FILENO) < 0 || ::chdir(cwd.c_str()) != 0) {
      _exit(127);
    }
    // Record facts in the child after dup2, before exec; never infer from the parent.
    const char facts[]{static_cast<char>('0' + (::isatty(0) != 0)),
                       static_cast<char>('0' + (::isatty(1) != 0)),
                       static_cast<char>('0' + (::isatty(2) != 0))};
    if (::write(facts_fd, facts, sizeof(facts)) != sizeof(facts)) _exit(127);
    (void)::close(facts_fd);
    (void)::close(slave);
    (void)::close(master);
    (void)::close(stdout_pipe[0]);
    (void)::close(stdout_pipe[1]);
    ::execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
    _exit(127);
  }
  REQUIRE(::close(facts_fd) == 0);
  REQUIRE(::close(stdout_pipe[1]) == 0);
  REQUIRE(::write(master, input.data(), input.size()) == static_cast<ssize_t>(input.size()));
  SplitRunResult result{};
  std::array<pollfd, 2> readers{{{stdout_pipe[0], POLLIN, 0}, {master, POLLIN, 0}}};
  std::array<char, 4096> buffer{};
  while (readers[0].fd >= 0 || readers[1].fd >= 0) {
    const int ready = ::poll(readers.data(), readers.size(), 30000);
    if (ready < 0 && errno == EINTR) continue;
    REQUIRE(ready > 0);
    for (size_t index = 0; index < readers.size(); ++index) {
      auto& reader = readers[index];
      if (reader.fd < 0 || reader.revents == 0) continue;
      const ssize_t count = ::read(reader.fd, buffer.data(), buffer.size());
      if (count > 0) {
        (index == 0 ? result.out : result.err).append(buffer.data(), static_cast<size_t>(count));
      } else if (count == 0 || (count < 0 && index == 1 && errno == EIO)) {
        REQUIRE(::close(reader.fd) == 0);
        reader.fd = -1;
      } else {
        REQUIRE(errno == EINTR);
      }
    }
  }
  int status = 0;
  while (::waitpid(child, &status, 0) < 0) REQUIRE(errno == EINTR);
  REQUIRE(WIFEXITED(status));
  result.code = WEXITSTATUS(status);
  const auto facts = read_text(facts_name);
  REQUIRE(facts.size() == 3);
  result.stdin_tty = facts[0] == '1';
  result.stdout_tty = facts[1] == '1';
  result.stderr_tty = facts[2] == '1';
  REQUIRE(std::filesystem::remove(facts_name));
  return result;
}

static inline SplitRunResult run_cmd_pty_split(
    const std::string& args, const std::filesystem::path& cwd, std::string_view input) {
  return run_shell_pty_topology("exec '" + std::string{BIV_BINARY_PATH} + "' " + args,
                               cwd, input, true);
}

}  // namespace
