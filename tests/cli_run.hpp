#pragma once

#include <array>
#include <cerrno>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
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

struct GitFixture {
  std::filesystem::path root;
  std::filesystem::path git{"/usr/bin/git"};

  static std::string quote(std::string_view value) {
    std::string out{"'"};
    for (const char byte : value) {
      if (byte == '\'') out += "'\\''";
      else out += byte;
    }
    return out + '\'';
  }

  void command(const std::string& args,
               const std::optional<std::filesystem::path>& cwd = std::nullopt) const {
    const auto command_line =
        (cwd ? "cd " + quote(cwd->string()) + " && " : std::string{}) +
        quote(git.string()) + " " + args;
    const int status = std::system(command_line.c_str());
    INFO(command_line);
    REQUIRE(status != -1);
    REQUIRE(WIFEXITED(status));
    REQUIRE(WEXITSTATUS(status) == 0);
  }

  std::string output(
      const std::string& args,
      const std::optional<std::filesystem::path>& cwd = std::nullopt) const {
    static unsigned sequence = 0;
    const auto capture = root / ("git-output-" + std::to_string(++sequence));
    const auto command_line =
        (cwd ? "cd " + quote(cwd->string()) + " && " : std::string{}) +
        quote(git.string()) + " " + args + " >" + quote(capture.string());
    const int status = std::system(command_line.c_str());
    INFO(command_line);
    REQUIRE(status != -1);
    REQUIRE(WIFEXITED(status));
    REQUIRE(WEXITSTATUS(status) == 0);
    const auto result = read_text(capture);
    REQUIRE(std::filesystem::remove(capture));
    return result;
  }

  std::filesystem::path init_bare(const std::filesystem::path& path) const {
    std::filesystem::create_directories(path.parent_path());
    command("init --bare --initial-branch=main " + quote(path.string()));
    return path;
  }

  std::filesystem::path init_work(const std::filesystem::path& remote,
                                  const std::filesystem::path& work) const {
    std::filesystem::create_directories(work);
    command("init -b main", work);
    {
      std::ofstream ignore{work / ".gitignore"};
      ignore << "ignored.log\n";
      std::ofstream tracked{work / "tracked.txt"};
      tracked << "tracked bytes\n";
    }
    command("add .", work);
    command("-c user.name='Wiring Fixture' -c user.email=wiring@example.invalid "
            "commit -m base", work);
    const auto requested = "file://" + remote.generic_string();
    command("remote add origin " + quote(requested), work);
    command("push -u origin main", work);
    command("branch local-topic", work);
    {
      std::ofstream ignored{work / "ignored.log"};
      ignored << "ignored bytes\n";
    }
    REQUIRE(output("rev-parse --verify HEAD", work).size() == 41U);
    REQUIRE(output("remote get-url origin", work) == requested + "\n");
    return work;
  }

  void set_instead_of(const std::filesystem::path& repo,
                      std::string_view requested,
                      std::string_view effective) const {
    command("config " + quote("url." + std::string{effective} + ".insteadOf") +
                " " + quote(requested),
            repo);
  }

  std::filesystem::path temp_home_with_instead_of(
      const std::filesystem::path& home, std::string_view requested,
      std::string_view effective) const {
    std::filesystem::create_directories(home);
    command("config --file " + quote((home / ".gitconfig").string()) + " " +
            quote("url." + std::string{effective} + ".insteadOf") + " " +
            quote(requested));
    return home;
  }

  std::filesystem::path shim_path(
      const std::filesystem::path& trace_file) const {
    const auto bin = trace_file.parent_path() / "bin";
    const auto shim = bin / "git";
    std::filesystem::create_directories(bin);
    {
      std::ofstream trace{trace_file, std::ios::trunc};
    }
    {
      std::ofstream script{shim};
      script << "#!/bin/sh\n"
             << "{ printf '%s' \"$PWD\"; for a in \"$@\"; do printf '\\t%s' \"$a\"; done; printf '\\n'; } >> "
             << quote(trace_file.string()) << " || exit 98\n"
             << "exec " << quote(git.string()) << " \"$@\"\n";
    }
    std::filesystem::permissions(shim, std::filesystem::perms::owner_all);
    return bin;
  }

  std::filesystem::path labelled_divergence_shim(
      const std::filesystem::path& shim_root) const {
    const auto bin = shim_root / "bin";
    const auto trace = shim_root / "trace";
    const auto shim = bin / "git";
    std::filesystem::create_directories(bin);
    std::ofstream{trace, std::ios::trunc};
    {
      std::ofstream script{shim};
      script << "#!/usr/bin/env bash\nBIV_GIT_TRACE='" << trace.string()
             << "'\nBIV_GIT_REAL='" << git.string() << "'\n"
             << "[ -n \"${BIV_GIT_TRACE-}\" ] && [ -n \"${BIV_GIT_REAL-}\" ] && [ -x \"${BIV_GIT_REAL}\" ] || exit 97\n"
             << "{ printf '%s' \"$PWD\"; for a in \"$@\"; do printf '\\t%s' \"$a\"; done; printf '\\n'; } >> \"$BIV_GIT_TRACE\" || exit 98\n"
             << "for a in \"$@\"; do if [ \"$a\" = --get-url ]; then printf '%s\\n' 'https://effective.invalid/repo'; exit 0; fi; done\n"
             << "exec \"$BIV_GIT_REAL\" \"$@\"\n";
    }
    std::filesystem::permissions(shim, std::filesystem::perms::owner_all);
    return bin;
  }
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
