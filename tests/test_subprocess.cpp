#include <signal.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include "core/support/subprocess.hpp"

namespace {

namespace fs = std::filesystem;

class TempDir {
 public:
  explicit TempDir(const std::string_view name)
      : path_{fs::temp_directory_path() /
              ("biv-subprocess-" + std::string{name} + "-" +
               std::to_string(::getpid()) + "-" +
               std::to_string(next_id_++))} {
    fs::remove_all(path_);
    fs::create_directories(path_);
  }

  ~TempDir() { fs::remove_all(path_); }

  TempDir(const TempDir&) = delete;
  TempDir& operator=(const TempDir&) = delete;

  const fs::path& path() const { return path_; }

 private:
  inline static std::size_t next_id_{0};
  fs::path path_;
};

biv::support::SpawnRequest shell_request(const std::string& script) {
  return biv::support::SpawnRequest{
      .executable = "/bin/sh",
      .argv = {"/bin/sh", "-c", script},
      .env = {},
      .stderr_mode = biv::support::StderrMode::separate,
      .stdout_file = std::nullopt,
      .stdout_cap = 64U * 1024U,
      .stderr_cap = 64U * 1024U,
      .budgets = biv::support::ProbeBudgets{}};
}

std::string as_string(const std::vector<std::byte>& bytes) {
  std::string output;
  output.reserve(bytes.size());
  for (const auto byte : bytes) {
    output.push_back(static_cast<char>(byte));
  }
  return output;
}

bool process_is_gone(const pid_t pid) {
  for (std::size_t attempt = 0; attempt < 50U; ++attempt) {
    if (::kill(pid, 0) == -1 && errno == ESRCH) {
      return true;
    }
    ::usleep(20'000);
  }
  return false;
}

}  // namespace

TEST_CASE("run_argv echoes caller argv and full environment") {
  auto request = shell_request("printf '%s\\n' \"$MARK\"");
  request.env = {"MARK=x1"};

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK_FALSE(result->spawn_failed);
  CHECK_FALSE(result->timed_out);
  CHECK_FALSE(result->io_failed);
  CHECK(result->exit_code == 0);
  CHECK(as_string(result->stdout_bytes) == "x1\n");
  CHECK(result->stderr_bytes.empty());
}

TEST_CASE("run_argv separate topology keeps streams apart") {
  const auto request =
      shell_request("printf 'out\\n'; printf 'err\\n' >&2");

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK(result->exit_code == 0);
  CHECK(as_string(result->stdout_bytes) == "out\n");
  CHECK(as_string(result->stderr_bytes) == "err\n");
}

TEST_CASE("run_argv drains ready stderr while stdout stays quiet and open") {
  auto request =
      shell_request("/usr/bin/head -c 1048576 /dev/zero >&2");
  request.stderr_cap = 2U * 1024U * 1024U;

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK_FALSE(result->timed_out);
  CHECK_FALSE(result->spawn_failed);
  CHECK_FALSE(result->io_failed);
  CHECK(result->exit_code == 0);
  CHECK(result->stdout_bytes.empty());
  CHECK(result->stderr_bytes.size() == 1024U * 1024U);
}

TEST_CASE("run_argv merge topology preserves source write order") {
  auto request =
      shell_request("printf 'a\\n'; printf 'b\\n' >&2; printf 'c\\n'");
  request.stderr_mode = biv::support::StderrMode::merge_into_stdout;

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK(result->exit_code == 0);
  CHECK(as_string(result->stdout_bytes) == "a\nb\nc\n");
  CHECK(result->stderr_bytes.empty());
}

TEST_CASE("run_argv returns a nonzero exit code as data") {
  const auto result = biv::support::run_argv(shell_request("exit 7"));

  REQUIRE(result.has_value());
  CHECK_FALSE(result->spawn_failed);
  CHECK_FALSE(result->timed_out);
  CHECK_FALSE(result->io_failed);
  CHECK(result->exit_code == 7);
}

TEST_CASE("run_argv timeout sweeps its process group and reaps its child") {
  TempDir root{"timeout"};
  const auto marker = root.path() / "pids";
  auto request = shell_request(
      "trap '' TERM\n"
      "sleep 30 &\n"
      "printf '%s %s' \"$$\" \"$!\" > '" +
      marker.string() + "'\nwait\n");
  request.budgets.probe_wall = std::chrono::milliseconds{200};
  request.budgets.term_grace = std::chrono::milliseconds{50};

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK(result->timed_out);
  CHECK(result->exit_code == -1);
  REQUIRE(fs::exists(marker));
  std::ifstream input{marker};
  pid_t direct = -1;
  pid_t descendant = -1;
  input >> direct >> descendant;
  REQUIRE(direct > 0);
  REQUIRE(descendant > 0);
  CHECK(process_is_gone(direct));
  CHECK(process_is_gone(descendant));
}

TEST_CASE("run_argv streams stdout to the requested file") {
  TempDir root{"stdout-file"};
  const auto output = root.path() / "stdout.bin";
  auto request = shell_request("printf 'file-output'");
  request.stdout_file = output;

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK(result->exit_code == 0);
  CHECK(result->stdout_bytes.empty());
  std::ifstream input{output, std::ios::binary};
  REQUIRE(input);
  const std::string contents{std::istreambuf_iterator<char>{input},
                             std::istreambuf_iterator<char>{}};
  CHECK(contents == "file-output");
}

TEST_CASE("run_argv preserves raw bytes on both separate streams") {
  const auto request =
      shell_request("printf '\\377\\000'; printf '\\376\\000' >&2");

  const auto result = biv::support::run_argv(request);

  REQUIRE(result.has_value());
  CHECK(result->stdout_bytes ==
        std::vector<std::byte>{static_cast<std::byte>(0xff),
                               static_cast<std::byte>(0x00)});
  CHECK(result->stderr_bytes ==
        std::vector<std::byte>{static_cast<std::byte>(0xfe),
                               static_cast<std::byte>(0x00)});
}
