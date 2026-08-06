#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>
#include <simdjson.h>

#include "cli/args.hpp"
#include "core/open/render.hpp"
#include "core/pack/pack.hpp"

// The parser otherwise belongs only to the CLI executable target.
#include "../src/cli/args.cpp"

namespace {

struct RunResult {
  int code{0};
  std::string out;
  std::string err;
};

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() /
              ("biv-cli-" + std::string{name} + "-" + std::to_string(::getpid()));
  std::filesystem::remove_all(base);
  std::filesystem::create_directories(base);
  return base;
}

void write_file(const std::filesystem::path& path, std::string_view content) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  out << content;
}

std::string read_text(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  REQUIRE(in);
  return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}

RunResult run_cmd(const std::string& args, const std::filesystem::path& cwd) {
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

RunResult run_cmd_closed_stderr(const std::string& args,
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

std::string snapshot_metadata(const std::filesystem::path& path) {
  struct stat status{};
  REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
  const auto seconds = status.st_mtimespec.tv_sec;
  const auto nanoseconds = status.st_mtimespec.tv_nsec;
#else
  const auto seconds = status.st_mtim.tv_sec;
  const auto nanoseconds = status.st_mtim.tv_nsec;
#endif
  return ":mode=" + std::to_string(status.st_mode) +
         ":mtime=" + std::to_string(seconds) + "." +
         std::to_string(nanoseconds);
}

std::map<std::string, std::string> recursive_byte_snapshot(
    const std::filesystem::path& root) {
  std::map<std::string, std::string> snapshot;
  const auto root_status = std::filesystem::symlink_status(root);
  if (!std::filesystem::exists(root_status)) {
    snapshot.emplace(".", "absent");
    return snapshot;
  }
  snapshot.emplace(
      ".",
      (std::filesystem::is_directory(root_status) ? "directory" : "present") +
          snapshot_metadata(root));
  if (!std::filesystem::is_directory(root_status)) {
    return snapshot;
  }
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(root)) {
    const auto relative =
        entry.path().lexically_relative(root).generic_string();
    const auto status = entry.symlink_status();
    if (std::filesystem::is_symlink(status)) {
      snapshot.emplace(
          relative,
          "symlink:" +
              std::filesystem::read_symlink(entry.path()).generic_string() +
              snapshot_metadata(entry.path()));
    } else if (std::filesystem::is_directory(status)) {
      snapshot.emplace(relative, "directory" + snapshot_metadata(entry.path()));
    } else if (std::filesystem::is_regular_file(status)) {
      snapshot.emplace(relative, "file:" + read_text(entry.path()) +
                                     snapshot_metadata(entry.path()));
    } else {
      snapshot.emplace(relative, "other" + snapshot_metadata(entry.path()));
    }
  }
  return snapshot;
}

void check_internal_error_json(const std::string& output,
                               std::string_view expected_detail) {
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(output).get(document) == simdjson::SUCCESS);
  std::string_view verb;
  bool ok = true;
  std::int64_t exit_code = 0;
  std::string_view kind;
  std::string_view detail;
  REQUIRE(document["verb"].get(verb) == simdjson::SUCCESS);
  REQUIRE(document["ok"].get(ok) == simdjson::SUCCESS);
  REQUIRE(document["exit_code"].get(exit_code) == simdjson::SUCCESS);
  REQUIRE(document["error"]["kind"].get(kind) == simdjson::SUCCESS);
  REQUIRE(document["error"]["detail"].get(detail) == simdjson::SUCCESS);
  CHECK(verb == "open");
  CHECK_FALSE(ok);
  CHECK(exit_code == 4);
  CHECK(kind == "InternalError");
  CHECK(detail == expected_detail);
}

void check_disclosure_error_json(const std::string& output) {
  check_internal_error_json(output, "probe-disclosure-write-failed");
}

std::filesystem::path write_executable(const std::filesystem::path& path,
                                       std::string_view body) {
  write_file(path, "#!/bin/sh\n" + std::string{body});
  REQUIRE(::chmod(path.c_str(), 0755) == 0);
  return path;
}

RunResult run_cmd_broken_stderr_pipe(const std::string& args,
                                     const std::filesystem::path& cwd) {
  const auto out = cwd / "stdout.txt";
  const auto pipe = cwd / "broken-stderr.pipe";
  const auto closed = cwd / "broken-stderr.closed";
  const auto runner = write_executable(
      cwd / "broken-stderr-runner",
      "while [ ! -e '" + closed.string() +
          "' ]; do sleep 0.01; done\nexec '" + std::string{BIV_BINARY_PATH} +
          "' " + args + "\n");
  std::filesystem::remove(pipe);
  std::filesystem::remove(closed);
  REQUIRE(::mkfifo(pipe.c_str(), 0600) == 0);
  const std::string command =
      "cd '" + cwd.string() + "' && (dd bs=1 count=0 <'" + pipe.string() +
      "' 2>/dev/null; : >'" + closed.string() + "') & reader=$!; '" +
      runner.string() + "' >'" + out.string() + "' 2>'" + pipe.string() +
      "'; rc=$?; wait $reader; rm -f '" + pipe.string() + "'; exit $rc";
  const int rc = std::system(command.c_str());
  int code = rc;
  if (WIFEXITED(rc)) {
    code = WEXITSTATUS(rc);
  }
  return RunResult{.code = code, .out = read_text(out), .err = ""};
}

int run_cmd_broken_shared_pipe(const std::string& args,
                               const std::filesystem::path& cwd) {
  const auto pipe = cwd / "broken-shared.pipe";
  const auto closed = cwd / "broken-shared.closed";
  const auto runner = write_executable(
      cwd / "broken-shared-runner",
      "while [ ! -e '" + closed.string() + "' ]; do sleep 0.01; done\nexec '" +
          std::string{BIV_BINARY_PATH} + "' " + args + "\n");
  std::filesystem::remove(pipe);
  std::filesystem::remove(closed);
  REQUIRE(::mkfifo(pipe.c_str(), 0600) == 0);
  const std::string command =
      "cd '" + cwd.string() + "' && (dd bs=1 count=0 <'" + pipe.string() +
      "' 2>/dev/null; : >'" + closed.string() + "') & reader=$!; '" +
      runner.string() + "' >'" + pipe.string() + "' 2>&1; rc=$?; " +
      "wait $reader; rm -f '" + pipe.string() + "'; exit $rc";
  const int rc = std::system(command.c_str());
  return WIFEXITED(rc) ? WEXITSTATUS(rc) : rc;
}

class LimitedStderrChild {
 public:
  LimitedStderrChild(const pid_t child, std::array<int, 2>& stdout_pipe)
      : child_{child}, stdout_pipe_{stdout_pipe} {}

  ~LimitedStderrChild() {
    for (int& fd : stdout_pipe_) {
      if (fd >= 0) {
        (void)close_endpoint(fd);
      }
    }
    if (child_ > 0) {
      int status = 0;
      while (::waitpid(child_, &status, 0) < 0 && errno == EINTR) {
      }
    }
  }

  LimitedStderrChild(const LimitedStderrChild&) = delete;
  LimitedStderrChild& operator=(const LimitedStderrChild&) = delete;

  bool close_endpoint(int& fd) noexcept {
    if (fd < 0 || ::close(fd) != 0) {
      return false;
    }
    fd = -1;
    return true;
  }

  void dismiss_child() noexcept { child_ = -1; }

 private:
  pid_t child_;
  std::array<int, 2>& stdout_pipe_;
};

RunResult run_cmd_limited_stderr(const std::vector<std::string>& args,
                                 const std::filesystem::path& cwd,
                                 const std::filesystem::path& stderr_path,
                                 rlim_t cap) {
  std::vector<std::string> child_args;
  child_args.reserve(args.size() + 1U);
  child_args.emplace_back(BIV_BINARY_PATH);
  child_args.insert(child_args.end(), args.begin(), args.end());
  std::vector<char*> child_argv;
  child_argv.reserve(child_args.size() + 1U);
  for (auto& arg : child_args) {
    child_argv.push_back(arg.data());
  }
  child_argv.push_back(nullptr);

  std::array<int, 2> stdout_pipe{};
  REQUIRE(::pipe(stdout_pipe.data()) == 0);
  const pid_t child = ::fork();
  if (child == 0) {
    (void)::close(stdout_pipe[0]);
    const int stderr_fd =
        ::open(stderr_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
    const struct rlimit limit{cap, cap};
    if (stderr_fd < 0 || ::signal(SIGXFSZ, SIG_IGN) == SIG_ERR ||
        ::setrlimit(RLIMIT_FSIZE, &limit) != 0 ||
        ::dup2(stdout_pipe[1], STDOUT_FILENO) < 0 ||
        ::dup2(stderr_fd, STDERR_FILENO) < 0 || ::chdir(cwd.c_str()) != 0) {
      _exit(127);
    }
    (void)::close(stdout_pipe[1]);
    (void)::close(stderr_fd);

    ::execv(BIV_BINARY_PATH, child_argv.data());
    _exit(127);
  }

  LimitedStderrChild cleanup{child, stdout_pipe};
  REQUIRE(child >= 0);
  REQUIRE(cleanup.close_endpoint(stdout_pipe[1]));
  std::string output;
  std::array<char, 4096> buffer{};
  while (true) {
    const ssize_t count = ::read(stdout_pipe[0], buffer.data(), buffer.size());
    if (count > 0) {
      output.append(buffer.data(), static_cast<size_t>(count));
      continue;
    }
    if (count < 0 && errno == EINTR) {
      continue;
    }
    REQUIRE(count == 0);
    break;
  }
  REQUIRE(cleanup.close_endpoint(stdout_pipe[0]));
  int status = 0;
  while (::waitpid(child, &status, 0) < 0) {
    REQUIRE(errno == EINTR);
  }
  cleanup.dismiss_child();
  REQUIRE(WIFEXITED(status));
  return RunResult{.code = WEXITSTATUS(status),
                   .out = std::move(output),
                   .err = read_text(stderr_path)};
}

std::string line_containing(std::string_view text, std::string_view needle) {
  const auto position = text.find(needle);
  REQUIRE(position != std::string_view::npos);
  const auto begin = text.rfind('\n', position);
  const auto end = text.find('\n', position);
  return std::string{
      text.substr(begin == std::string_view::npos ? 0U : begin + 1U,
                  (end == std::string_view::npos ? text.size() : end) -
                      (begin == std::string_view::npos ? 0U : begin + 1U))};
}

void check_probe_outcome(simdjson::dom::element document,
                         std::string_view requested_path,
                         std::string_view expected_outcome) {
  simdjson::dom::array agents;
  REQUIRE(document["result"]["sessions"]["agents"].get(agents) ==
          simdjson::SUCCESS);
  bool found = false;
  for (const auto agent : agents) {
    std::string_view requested;
    if (agent["probe"]["requested"].get(requested) != simdjson::SUCCESS ||
        requested != requested_path) {
      continue;
    }
    found = true;
    std::string_view outcome;
    std::string_view raw;
    simdjson::dom::element executed;
    REQUIRE(agent["probe"]["outcome"].get(outcome) == simdjson::SUCCESS);
    REQUIRE(agent["probe"]["executed"].get(executed) == simdjson::SUCCESS);
    REQUIRE(agent["probe"]["raw"].get(raw) == simdjson::SUCCESS);
    CHECK(outcome == expected_outcome);
    CHECK(executed.is_null());
    CHECK(raw.empty());
  }
  REQUIRE(found);
}

void check_successful_probe_outcome(simdjson::dom::element document,
                                    std::string_view requested_path) {
  simdjson::dom::array agents;
  REQUIRE(document["result"]["sessions"]["agents"].get(agents) ==
          simdjson::SUCCESS);
  bool found = false;
  for (const auto agent : agents) {
    std::string_view requested;
    if (agent["probe"]["requested"].get(requested) != simdjson::SUCCESS ||
        requested != requested_path) {
      continue;
    }
    found = true;
    bool pinned = false;
    std::string_view outcome;
    std::string_view executed;
    std::int64_t exit_code = -1;
    REQUIRE(agent["probe"]["pinned"].get(pinned) == simdjson::SUCCESS);
    REQUIRE(agent["probe"]["outcome"].get(outcome) == simdjson::SUCCESS);
    REQUIRE(agent["probe"]["executed"].get(executed) == simdjson::SUCCESS);
    REQUIRE(agent["probe"]["exit_code"].get(exit_code) == simdjson::SUCCESS);
    CHECK(pinned);
    CHECK(outcome == "ok");
    CHECK(executed == requested_path);
    CHECK(exit_code == 0);
  }
  REQUIRE(found);
}

std::set<std::string> regular_paths(const std::filesystem::path& root) {
  std::set<std::string> paths;
  if (!std::filesystem::exists(root)) {
    return paths;
  }
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(root)) {
    if (entry.is_regular_file()) {
      paths.insert(entry.path().generic_string());
    }
  }
  return paths;
}

std::string claude_project_key(const std::filesystem::path& path) {
  auto key = path.generic_string();
  for (char& value : key) {
    const bool alphanumeric =
        (value >= '0' && value <= '9') ||
        (value >= 'A' && value <= 'Z') ||
        (value >= 'a' && value <= 'z');
    if (!alphanumeric) {
      value = '-';
    }
  }
  return key;
}

std::string display_path(const std::filesystem::path& path) {
  std::string displayed;
  for (const char value : path.generic_string()) {
    if (value == ' ') {
      displayed += "\\x20";
    } else {
      displayed.push_back(value);
    }
  }
  return displayed;
}

class ScopedEnv {
 public:
  ScopedEnv(std::string name, std::string value) : name_{std::move(name)} {
    if (const char* old = std::getenv(name_.c_str()); old != nullptr) {
      old_value_ = std::string{old};
    }
    REQUIRE(::setenv(name_.c_str(), value.c_str(), 1) == 0);
  }

  ~ScopedEnv() {
    if (old_value_.has_value()) {
      (void)::setenv(name_.c_str(), old_value_->c_str(), 1);
    } else {
      (void)::unsetenv(name_.c_str());
    }
  }

  ScopedEnv(const ScopedEnv&) = delete;
  ScopedEnv& operator=(const ScopedEnv&) = delete;

 private:
  std::string name_;
  std::optional<std::string> old_value_;
};

}  // namespace

TEST_CASE("CLI pack/open round-trip emits JSON envelopes") {
  const auto root = make_tmp("roundtrip");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / ".bivignore", "target/\n");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");
  std::filesystem::create_directories(source / "target");
  write_file(source / "target" / "skip.txt", "skip");

  auto packed = run_cmd("pack '" + source.string() + "' --json", root);
  REQUIRE(packed.code == 0);
  REQUIRE_FALSE(packed.out.empty());
  CHECK(packed.out.front() == '{');
  CHECK(packed.out.find("\"verb\": \"pack\"") != std::string::npos);
  CHECK(std::filesystem::exists(root / "sample.bvpk"));

  auto opened = run_cmd("open '" + (root / "sample.bvpk").string() + "' --dest '" + (root / "restore").string() +
                            "' --json",
                        root);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("\"verb\": \"open\"") != std::string::npos);
  CHECK(read_text(root / "restore" / "a.txt") == "alpha");
  CHECK(read_text(root / "restore" / "dir" / "b.txt") == "beta");
  CHECK_FALSE(std::filesystem::exists(root / "restore" / "target"));
  std::filesystem::remove_all(root);
}

TEST_CASE("CLI reports usage and reserved verbs with exit 5") {
  const auto root = make_tmp("usage");
  auto unknown = run_cmd("--bad --json", root);
  CHECK(unknown.code == 5);
  CHECK(unknown.out.find("\"kind\": \"UsageError\"") != std::string::npos);

  auto list = run_cmd("list missing.bvpk --json", root);
  CHECK(list.code == 5);
  CHECK(list.out.find("NotYetImplemented") != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("CLI reports warning and refusal exit classes") {
  const auto root = make_tmp("exits");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  write_file(source / "keep.txt", "keep");
  REQUIRE(::mkfifo((source / "pipe").c_str(), 0600) == 0);

  auto packed = run_cmd("pack '" + source.string() + "' --json", root);
  CHECK(packed.code == 2);
  CHECK(packed.out.find("\"kind\": \"UnsupportedFileTypeSkipped\"") != std::string::npos);

  auto missing = run_cmd("open '" + (root / "missing.bvpk").string() + "' --json", root);
  CHECK(missing.code == 3);
  CHECK(missing.out.find("\"kind\": \"ImageUnreadable\"") != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("CLI pack text renders live session warnings and omits warnings-free output") {
  const auto root = std::filesystem::canonical(make_tmp("text-warnings"));
  const auto live_source = root / "proj";
  const auto clean_source = root / "clean";
  const auto claude_store = root / "claude-store";
  std::filesystem::create_directories(live_source);
  std::filesystem::create_directories(clean_source);
  write_file(live_source / "work.txt", "workspace");
  write_file(clean_source / "work.txt", "workspace");

  const auto fixture = std::filesystem::path{BIV_SOURCE_DIR} / "tests" /
                       "fixtures" / "claude_store" / "projects" / "-ws-proj" /
                       "aaaaaaaa-1111-4000-8000-000000000001.jsonl";
  auto transcript = read_text(fixture);
  for (size_t position = 0;
       (position = transcript.find("/ws/proj", position)) != std::string::npos;) {
    transcript.replace(position, 8, live_source.generic_string());
    position += live_source.generic_string().size();
  }
  write_file(claude_store / "projects" / "-ws-proj" / fixture.filename(), transcript);
  auto live_fact = read_text(std::filesystem::path{BIV_SOURCE_DIR} / "tests" /
                             "fixtures" / "claude_store" / "sessions" / "12345.json");
  const auto cwd_position = live_fact.find("/ws/proj");
  REQUIRE(cwd_position != std::string::npos);
  live_fact.replace(cwd_position, 8, live_source.generic_string());
  write_file(claude_store / "sessions" / "12345.json", live_fact);

  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", claude_store.string()};
  const ScopedEnv codex_home{"CODEX_HOME", (root / "no-codex-store").string()};
  const ScopedEnv home{"HOME", root.string()};

  const auto live = run_cmd("pack '" + live_source.string() + "'", root);
  REQUIRE(live.code == 2);
  const auto live_line = line_containing(live.out, "aaaaaaaa-1111-4000-8000-000000000001");
  CHECK(live_line.find("may") != std::string::npos);
  CHECK(live_line.find(" is active") == std::string::npos);
  CHECK(live.out.find("aaaaaaaa-1111-4000-8000-000000000001", live.out.find(
      "aaaaaaaa-1111-4000-8000-000000000001") + 1U) == std::string::npos);

  const auto clean = run_cmd("pack '" + clean_source.string() + "'", root);
  REQUIRE(clean.code == 0);
  CHECK(clean.out.find("warning:") == std::string::npos);

  std::filesystem::remove_all(root);
}

TEST_CASE("CLI pack text derives Codex live and terminal warning controls") {
  const auto root = std::filesystem::canonical(make_tmp("codex-tail-warnings"));
  const auto live_source = root / "proj";
  const auto terminal_source = root / "terminal";
  const auto aggregate_source = root / "aggregate";
  const auto codex_store = root / "codex-store";
  std::filesystem::create_directories(live_source);
  std::filesystem::create_directories(terminal_source);
  std::filesystem::create_directories(aggregate_source / "sub");
  write_file(live_source / "work.txt", "workspace");
  write_file(terminal_source / "work.txt", "workspace");
  write_file(aggregate_source / "work.txt", "workspace");

  const auto fixtures = std::filesystem::path{BIV_SOURCE_DIR} / "tests" /
                        "fixtures" / "codex_store" / "tail_matrix";
  const auto live_fixture =
      fixtures /
      "rollout-session-meta-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1005.jsonl";
  const auto terminal_fixture =
      fixtures /
      "rollout-task-complete-with-lf-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1001.jsonl";
  const auto terminal_parent_fixture =
      fixtures /
      "rollout-terminal-parent-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1014.jsonl";
  const auto live_child_fixture =
      fixtures /
      "rollout-live-child-019faaaa-bbbb-7ccc-8ddd-eeeeeeee1015.jsonl";
  for (const auto& [fixture, source] :
       std::array<std::pair<std::filesystem::path, std::filesystem::path>, 4>{
           {{live_fixture, live_source},
            {terminal_fixture, terminal_source},
            {terminal_parent_fixture, aggregate_source},
            {live_child_fixture, aggregate_source}}}) {
    auto rollout = read_text(fixture);
    const auto cwd_position = rollout.find("/ws/proj");
    REQUIRE(cwd_position != std::string::npos);
    rollout.replace(cwd_position, 8, source.generic_string());
    write_file(codex_store / "sessions" / "2026" / "08" / "05" /
                   fixture.filename(),
               rollout);
  }

  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR",
                                (root / "no-claude-store").string()};
  const ScopedEnv codex_home{"CODEX_HOME", codex_store.string()};
  const ScopedEnv home{"HOME", root.string()};

  const auto live = run_cmd("pack '" + live_source.string() + "'", root);
  REQUIRE(live.code == 2);
  constexpr std::string_view live_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1005";
  const auto live_line = line_containing(live.out, live_id);
  CHECK(live_line.find("may") != std::string::npos);
  CHECK(live_line.find(" is active") == std::string::npos);
  const auto first_live_id = live.out.find(live_id);
  REQUIRE(first_live_id != std::string::npos);
  CHECK(live.out.find(live_id, first_live_id + live_id.size()) ==
        std::string::npos);

  const auto terminal =
      run_cmd("pack '" + terminal_source.string() + "'", root);
  REQUIRE(terminal.code == 0);
  CHECK(terminal.out.find("warning:") == std::string::npos);
  CHECK(terminal.out.find("019faaaa-bbbb-7ccc-8ddd-eeeeeeee1001") ==
        std::string::npos);

  std::filesystem::remove(root / "terminal.bvpk");
  const auto terminal_json =
      run_cmd("pack '" + terminal_source.string() + "' --json", root);
  REQUIRE(terminal_json.code == 0);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(terminal_json.out).get(document) == simdjson::SUCCESS);
  simdjson::dom::array agent_sessions;
  REQUIRE(document["result"]["manifest"]["agent_sessions"].get(agent_sessions) ==
          simdjson::SUCCESS);
  REQUIRE(std::distance(agent_sessions.begin(), agent_sessions.end()) == 1);
  std::string_view agent;
  REQUIRE(agent_sessions.at(0)["agent"].get(agent) == simdjson::SUCCESS);
  CHECK(agent == "codex");
  std::uint64_t session_count = 0;
  REQUIRE(agent_sessions.at(0)["session_count"].get(session_count) ==
          simdjson::SUCCESS);
  CHECK(session_count == 1U);

  const auto aggregate =
      run_cmd("pack '" + aggregate_source.string() + "'", root);
  REQUIRE(aggregate.code == 2);
  constexpr std::string_view aggregate_parent_id =
      "019faaaa-bbbb-7ccc-8ddd-eeeeeeee1014";
  const auto aggregate_line =
      line_containing(aggregate.out, aggregate_parent_id);
  CHECK(aggregate_line.find("may have been live") != std::string::npos);

  std::filesystem::remove_all(root);
}

TEST_CASE("CLI warning text covers live torn and generic shapes") {
  CHECK(biv::pack::warning_text(biv::pack::Warning{
            .kind = std::string{biv::pack::kWarningSessionLiveAtPack},
            .path = std::string{"id\x1b", 3}}) ==
        "warning: session id\\x1B may have been live at pack time");
  CHECK(biv::pack::warning_text(biv::pack::Warning{
            .kind = std::string{biv::pack::kWarningTornTailDropped},
            .path = "session-id",
            .artifact = std::string{"agents/\x7f.jsonl", 14},
            .bytes = 42U}) ==
        "warning: torn tail dropped from agents/\\x7F.jsonl: 42 bytes");
  CHECK(biv::pack::warning_text(biv::pack::Warning{
            .kind = std::string{"Odd\x01", 4}, .path = "bad\tpath"}) ==
        "warning: Odd\\x01: bad\\x09path");
  CHECK(biv::pack::warning_text(
            biv::pack::Warning{.kind = "GenericWithoutPath"}) ==
        "warning: GenericWithoutPath");
}

TEST_CASE("CLI warning text sanitizes a real control-byte filename") {
  const auto root = std::filesystem::canonical(make_tmp("control-byte-warning"));
  const auto source = root / "source";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  std::string filename{"bad"};
  filename.push_back('\x1b');
  filename += "fifo";
  REQUIRE(::mkfifo((source / filename).c_str(), 0600) == 0);
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR",
                                (root / "no-claude-store").string()};
  const ScopedEnv codex_home{"CODEX_HOME", (root / "no-codex-store").string()};
  const ScopedEnv home{"HOME", root.string()};

  const auto packed = run_cmd("pack '" + source.string() + "'", root);

  REQUIRE(packed.code == 2);
  CHECK(packed.out.find('\x1b') == std::string::npos);
  CHECK(packed.out.find("bad\\x1Bfifo") != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("CLI parses open consent specifications") {
  const auto root = make_tmp("consent-valid");
  for (const std::string value : {"yes", "no", "claude-code=yes,codex=no"}) {
    auto result = run_cmd("open missing.bvpk --consent " + value + " --json", root);
    CHECK(result.code == 3);
    CHECK(result.out.find("\"kind\": \"ImageUnreadable\"") != std::string::npos);
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("CLI rejects invalid consent specifications") {
  const auto root = make_tmp("consent-invalid");
  const auto check_detail = [&](std::string_view args, std::string_view detail) {
    auto result = run_cmd(std::string{args} + " --json", root);
    CHECK(result.code == 5);
    CHECK(result.out.find("\"kind\": \"UsageError\"") != std::string::npos);
    CHECK(result.out.find(std::string{detail}) != std::string::npos);
  };
  check_detail("open image.bvpk --consent bogus", "consent-value-invalid");
  check_detail("open image.bvpk --consent claude=yes,claude=no", "consent-duplicate-agent");
  check_detail("open image.bvpk --consent BadAgent=yes", "consent-agent-grammar");
  check_detail("pack workspace --consent yes", "unknown-flag");
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 CLI parses strict absolute agent binary pins") {
  const auto root = make_tmp("agent-bin-valid");
  const auto parsed =
      run_cmd("open image.bvpk "
              "--agent-bin 'codex=./bin/../codex' "
              "--agent-bin 'claude-code=tools/claude' --json",
              root);
  CHECK(parsed.code == 3);
  CHECK(parsed.out.find("\"kind\": \"ImageUnreadable\"") !=
        std::string::npos);

  const auto source =
      read_text(std::filesystem::path{BIV_SOURCE_DIR} / "src" / "cli" /
                "args.cpp");
  CHECK(source.find("std::filesystem::absolute(std::filesystem::path{path})") !=
        std::string::npos);
  CHECK(source.find(".lexically_normal()") != std::string::npos);
  CHECK(source.find("weakly_canonical") == std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 CLI rejects malformed unknown empty and duplicate pins") {
  const auto root = make_tmp("agent-bin-invalid");
  struct InvalidCase {
    std::string value;
    std::string detail;
  };
  const std::array cases{
      InvalidCase{"codex", "agent-bin-assignment-invalid"},
      InvalidCase{"=tool", "agent-bin-agent-invalid"},
      InvalidCase{"codex=", "agent-bin-path-empty"},
      InvalidCase{"future-agent=/tmp/tool", "agent-bin-agent-invalid"},
      InvalidCase{"codex=/tmp/a=/tmp/b", "agent-bin-assignment-invalid"}};
  for (const auto& invalid : cases) {
    DYNAMIC_SECTION(invalid.value) {
      const auto parsed =
          run_cmd("open image.bvpk --agent-bin '" + invalid.value +
                      "' --json",
                  root);
      CHECK(parsed.code == 5);
      CHECK(parsed.out.find("\"kind\": \"UsageError\"") !=
            std::string::npos);
      CHECK(parsed.out.find(invalid.detail) != std::string::npos);
    }
  }

  const auto duplicate =
      run_cmd("open image.bvpk --agent-bin 'codex=/tmp/one' "
              "--agent-bin 'codex=/tmp/two' --json",
              root);
  CHECK(duplicate.code == 5);
  CHECK(duplicate.out.find("agent-bin-duplicate") != std::string::npos);

  const auto missing =
      run_cmd("open image.bvpk --agent-bin --json", root);
  CHECK(missing.code == 5);
  CHECK(missing.out.find("agent-bin-assignment-invalid") !=
        std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 CLI rejects an explicitly empty destination in the parser") {
  std::array<std::string, 5> arguments{
      "biv", "open", "image.bvpk", "--dest", ""};
  std::array<char*, 5> argv{};
  for (size_t index = 0; index < arguments.size(); ++index) {
    argv.at(index) = arguments.at(index).data();
  }
  const auto direct =
      biv::cli::parse_args(std::span<char* const>{argv});
  REQUIRE_FALSE(direct.has_value());
  CHECK(direct.error().kind == biv::ErrKind::UsageError);
  CHECK(direct.error().detail == "dest-empty");

  const auto root = make_tmp("dest-empty");
  const auto parsed =
      run_cmd("open image.bvpk --dest '' --json", root);

  CHECK(parsed.code == 5);
  CHECK(parsed.out.find("\"kind\": \"UsageError\"") !=
        std::string::npos);
  CHECK(parsed.out.find("dest-empty") != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 CLI help documents the strict agent binary pin syntax") {
  const auto root = make_tmp("agent-bin-help");
  const auto help = run_cmd("open --help", root);

  CHECK(help.code == 0);
  CHECK(help.out ==
        "usage: biv open <image> [options]\n"
        "  --dest <path>\n"
        "  --consent <yes|no|agent=yes,...>\n"
        "  --agent-bin <claude-code|codex>=<absolute-or-relative-path>\n"
        "  --rename\n"
        "  --abort-on-collision\n"
        "  --verify\n"
        "  --json\n");
  CHECK(help.err.empty());
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 CLI normalizes only destination ancestors before plan_open") {
  const auto source =
      read_text(std::filesystem::path{BIV_SOURCE_DIR} / "src" / "cli" /
                "main.cpp");
  const auto absolute = source.find(
      "fs::absolute(dest_or_default).lexically_normal()");
  const auto trailing = source.find(
      "while (dest_candidate.filename().empty() &&");
  const auto empty = source.find(
      "if (dest_candidate.filename().empty())");
  const auto parent = source.find(
      "fs::weakly_canonical(dest_candidate.parent_path()");
  const auto leaf = source.find(
      "resolved_parent / dest_candidate.filename()");
  const auto plan = source.find("biv::open::plan_open");
  REQUIRE(absolute != std::string::npos);
  REQUIRE(trailing != std::string::npos);
  REQUIRE(empty != std::string::npos);
  REQUIRE(parent != std::string::npos);
  REQUIRE(leaf != std::string::npos);
  REQUIRE(plan != std::string::npos);
  CHECK(absolute < trailing);
  CHECK(trailing < empty);
  CHECK(empty < parent);
  CHECK(parent < leaf);
  CHECK(leaf < plan);
  CHECK(source.find("biv::support::run_version_probe") !=
        std::string::npos);
  CHECK(source.find("biv::support::kProbeTimeout") !=
        std::string::npos);
  CHECK(source.find("std::chrono::milliseconds{2000}") ==
        std::string::npos);
  CHECK(source.find("\"claude-code\"") == std::string::npos);
  CHECK(source.find("\"codex\"") == std::string::npos);
  CHECK(source.find(".pinned_bins = std::move(pinned_bins)") !=
        std::string::npos);
  const auto disclosure =
      source.find("biv::open_render::render_probe_disclosure");
  const auto consent_branch =
      source.find("if (consent_prompt.has_value())");
  const auto resolve = source.find("biv::core_sessions::resolve_consent");
  const auto execute = source.find("biv::open::execute_open");
  REQUIRE(disclosure != std::string::npos);
  REQUIRE(consent_branch != std::string::npos);
  REQUIRE(resolve != std::string::npos);
  REQUIRE(execute != std::string::npos);
  CHECK(disclosure < consent_branch);
  CHECK(disclosure < resolve);
  CHECK(disclosure < execute);
}

TEST_CASE("Task 4 CLI restores through one normalized absolute destination") {
  const auto root = make_tmp("absolute-destinations");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  write_file(source / "a.txt", "alpha");
  const auto packed = run_cmd("pack '" + source.string() + "'", root);
  REQUIRE(packed.code == 0);
  const auto image = root / "sample.bvpk";
  const auto process_root = std::filesystem::canonical(root);

  const std::array<std::pair<std::string, std::filesystem::path>, 4> cases{{
      {"work/", process_root / "work"},
      {"relative", process_root / "relative"},
      {"nested/../dotdot", process_root / "dotdot"},
      {(root / "absolute").string(), process_root / "absolute"},
  }};
  for (const auto& [argument, expected] : cases) {
    DYNAMIC_SECTION(argument) {
      const auto opened = run_cmd(
          "open '" + image.string() + "' --dest '" + argument + "' --json",
          root);
      REQUIRE(opened.code == 0);
      CHECK(read_text(expected / "a.txt") == "alpha");
      CHECK(opened.out.find("\"output_dir\": \"" +
                            expected.generic_string() + "\"") !=
            std::string::npos);
    }
  }

  std::filesystem::create_directories(root / "collision");
  const auto renamed =
      run_cmd("open '" + image.string() +
                  "' --dest './collision/' --rename --json",
              root);
  REQUIRE(renamed.code == 0);
  const auto final_path = process_root / "collision(1)";
  CHECK(read_text(final_path / "a.txt") == "alpha");
  CHECK_FALSE(std::filesystem::exists(root / "collision" / "collision(1)"));
  CHECK(renamed.out.find("\"output_dir\": \"" +
                         final_path.generic_string() + "\"") !=
        std::string::npos);

  const auto controlled = root / "controlled" / "nested";
  std::filesystem::create_directories(controlled);
  const auto dot = run_cmd("open '" + image.string() +
                               "' --dest '.' --rename --json",
                           controlled);
  REQUIRE(dot.code == 0);
  const auto dot_final = process_root / "controlled" / "nested(1)";
  CHECK(read_text(dot_final / "a.txt") == "alpha");
  CHECK(dot.out.find("\"output_dir\": \"" +
                     dot_final.generic_string() + "\"") !=
        std::string::npos);

  const auto dotdot = run_cmd("open '" + image.string() +
                                  "' --dest '..' --rename --json",
                              controlled);
  REQUIRE(dotdot.code == 0);
  const auto dotdot_final = process_root / "controlled(1)";
  CHECK(read_text(dotdot_final / "a.txt") == "alpha");
  CHECK(dotdot.out.find("\"output_dir\": \"" +
                        dotdot_final.generic_string() + "\"") !=
        std::string::npos);

  const auto root_like =
      run_cmd("open '" + image.string() +
                  "' --dest '/' --rename --json",
              root);
  CHECK(root_like.code == 5);
  CHECK(root_like.out.find("\"kind\": \"UsageError\"") !=
        std::string::npos);
  CHECK(root_like.out.find("dest-root-like") != std::string::npos);

  std::filesystem::create_directories(root / "physical-parent");
  std::filesystem::create_directory_symlink(root / "physical-parent",
                                            root / "linked-parent");
  REQUIRE(std::filesystem::is_symlink(root / "linked-parent"));
  const auto lexical_path = process_root / "linked-parent" / "through-link";
  const auto physical_path = process_root / "physical-parent" / "through-link";
  const auto through_symlink =
      run_cmd("open '" + image.string() +
                  "' --dest './linked-parent/through-link' --json",
              root);
  REQUIRE(through_symlink.code == 0);
  CHECK(read_text(lexical_path / "a.txt") == "alpha");
  CHECK(std::filesystem::equivalent(lexical_path, physical_path));
  CHECK(through_symlink.out.find("\"output_dir\": \"" +
                                  physical_path.generic_string() + "\"") !=
        std::string::npos);
  CHECK(lexical_path != physical_path);

  std::filesystem::create_directories(root / "leaf-target");
  std::filesystem::create_directory_symlink(
      root / "leaf-target", root / "leaf-alias");
  const auto through_leaf_symlink =
      run_cmd("open '" + image.string() +
                  "' --dest './leaf-alias' --rename --json",
              root);
  REQUIRE(through_leaf_symlink.code == 0);
  const auto lexical_sibling = process_root / "leaf-alias(1)";
  CHECK(read_text(lexical_sibling / "a.txt") == "alpha");
  CHECK_FALSE(std::filesystem::exists(root / "leaf-target(1)"));
  CHECK(through_leaf_symlink.out.find("\"output_dir\": \"" +
                                      lexical_sibling.generic_string() +
                                      "\"") != std::string::npos);
  std::filesystem::remove_all(root);
}

TEST_CASE(
    "Task 4 CLI carries probe and final destination through both agent "
    "imports") {
  const auto root = make_tmp("session-destination-e2");
  const auto process_root = std::filesystem::canonical(root);
  const auto source = process_root / "source with spaces";
  const auto codex_store = process_root / "codex-store";
  const auto claude_store = process_root / "claude-store";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  const auto codex_fixture =
      std::filesystem::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
      "codex_store" / "sessions" / "2026" / "07" / "06" /
      "rollout-2026-07-06T01-00-00-019faaaa-bbbb-7ccc-8ddd-"
      "eeeeeeee0001.jsonl";
  auto codex_content = read_text(codex_fixture);
  for (size_t position = 0;
       (position = codex_content.find("/ws/proj", position)) !=
       std::string::npos;) {
    codex_content.replace(position, 8, source.generic_string());
    position += source.generic_string().size();
  }
  write_file(codex_store / "sessions" / "2026" / "07" / "06" /
                 codex_fixture.filename(),
             codex_content);
  const auto claude_fixture =
      std::filesystem::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
      "claude_store" / "projects" / "-ws-proj" /
      "aaaaaaaa-1111-4000-8000-000000000001.jsonl";
  auto claude_content = read_text(claude_fixture);
  for (size_t position = 0;
       (position = claude_content.find("/ws/proj", position)) !=
       std::string::npos;) {
    claude_content.replace(position, 8, source.generic_string());
    position += source.generic_string().size();
  }
  for (const auto& [short_id, uuid] :
       std::array<std::pair<std::string_view, std::string_view>, 2>{{
           {"\"u1\"", "\"11111111-1111-4111-8111-111111111111\""},
           {"\"a1\"", "\"22222222-2222-4222-8222-222222222222\""},
       }}) {
    for (size_t position = 0;
         (position = claude_content.find(short_id, position)) !=
         std::string::npos;) {
      claude_content.replace(position, short_id.size(), uuid);
      position += uuid.size();
    }
  }
  write_file(claude_store / "projects" / "-ws-proj" /
                 claude_fixture.filename(),
             claude_content);

  const auto bin = root / "bin";
  const auto codex_marker = root / "codex-probe.txt";
  const auto claude_marker = root / "claude-probe.txt";
  const auto codex_probe = write_executable(
      bin / "codex-probe",
      "printf '%s|%s\\n' \"$0\" \"$1\" > '" +
          codex_marker.generic_string() +
          "'\nprintf 'codex-cli 0.144.4\\n'\n");
  const auto claude_probe = write_executable(
      bin / "claude",
      "printf '%s|%s\\n' \"$0\" \"$1\" > '" +
          claude_marker.generic_string() +
          "'\nprintf '2.1.211 (Claude Code)\\n'\n");
  const auto invalid_output_probe = write_executable(
      bin / "codex-invalid-output",
      "printf '\\233codex-cli 0.144.4\\n'\n");
  std::string non_utf8_missing_pin =
      (bin / "claude-missing-").string();
  non_utf8_missing_pin.push_back(static_cast<char>(0x9b));
  const auto loop_pin = bin / "codex-loop";
  std::filesystem::create_symlink(loop_pin.filename(), loop_pin);
  const auto missing_pin = bin / "claude-missing";
  const std::string inherited_path =
      std::getenv("PATH") == nullptr ? "" : std::getenv("PATH");
  const ScopedEnv codex_home{"CODEX_HOME", codex_store.string()};
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", claude_store.string()};
  const ScopedEnv home{"HOME", root.string()};
  const ScopedEnv path{"PATH", bin.string() + ":" + inherited_path};

  const auto packed = run_cmd("pack '" + source.string() + "'", root);
  REQUIRE((packed.code == 0 || packed.code == 2));
  const auto image = root / "source with spaces.bvpk";
  REQUIRE(std::filesystem::exists(image));
  const auto codex_before = regular_paths(codex_store);
  const auto claude_before = regular_paths(claude_store);

  SECTION("pin stat text binds each path to its outcome") {
    const auto parent = root / "stat-text-parent";
    std::filesystem::create_directories(parent);
    const auto stat_text = run_cmd(
        "open '" + image.string() + "' --dest '" + (parent / "dest").string() +
            "' --consent no --agent-bin 'codex=" + loop_pin.string() +
            "' --agent-bin 'claude-code=" + missing_pin.string() + "'",
        root);
    REQUIRE(stat_text.code == 0);
    const auto loop_line =
        line_containing(stat_text.err, loop_pin.generic_string());
    CHECK(loop_line.find("pinned path resolution failed") != std::string::npos);
    CHECK(loop_line.find("executable not found") == std::string::npos);
    const auto missing_line =
        line_containing(stat_text.err, missing_pin.generic_string());
    CHECK(missing_line.find("executable not found") != std::string::npos);
    CHECK(missing_line.find("pinned path resolution failed") ==
          std::string::npos);
  }

  SECTION("pin stat JSON binds each path to its outcome") {
    const auto parent = root / "stat-json-parent";
    std::filesystem::create_directories(parent);
    const auto stat_json = run_cmd(
        "open '" + image.string() + "' --dest '" + (parent / "dest").string() +
            "' --consent no --agent-bin 'codex=" + loop_pin.string() +
            "' --agent-bin 'claude-code=" + missing_pin.string() + "' --json",
        root);
    REQUIRE(stat_json.code == 0);
    simdjson::dom::parser stat_parser;
    simdjson::dom::element stat_document;
    REQUIRE(stat_parser.parse(stat_json.out).get(stat_document) ==
            simdjson::SUCCESS);
    check_probe_outcome(stat_document, loop_pin.generic_string(),
                        "not_accessible");
    check_probe_outcome(stat_document, missing_pin.generic_string(),
                        "not_found");
  }

  struct ClosedStderrCase {
    std::string_view name;
    std::string_view consent;
    bool json;
  };
  for (const auto& test_case : std::array{
           ClosedStderrCase{"closed-global-text", "yes", false},
           ClosedStderrCase{"closed-global-json", "yes", true},
           ClosedStderrCase{"closed-per-agent-text",
                            "codex=yes,claude-code=yes", false},
           ClosedStderrCase{"closed-per-agent-json",
                            "codex=yes,claude-code=yes", true},
       }) {
    DYNAMIC_SECTION("closed stderr " << test_case.name) {
      const auto parent = root / (std::string{test_case.name} + "-parent");
      std::filesystem::create_directories(parent);
      const auto parent_before = recursive_byte_snapshot(parent);
      const auto codex_store_before = recursive_byte_snapshot(codex_store);
      const auto claude_store_before = recursive_byte_snapshot(claude_store);
      const auto closed = run_cmd_closed_stderr(
          "open '" + image.string() + "' --dest '" +
              (parent / "dest").string() + "' --consent '" +
              std::string{test_case.consent} +
              "' --agent-bin 'codex=" + codex_probe.string() +
              "' --agent-bin 'claude-code=" + claude_probe.string() + "'" +
              (test_case.json ? " --json" : ""),
          root);

      CHECK(closed.code == 4);
      CHECK(recursive_byte_snapshot(parent) == parent_before);
      CHECK(recursive_byte_snapshot(codex_store) == codex_store_before);
      CHECK(recursive_byte_snapshot(claude_store) == claude_store_before);
      if (test_case.json) {
        check_disclosure_error_json(closed.out);
      } else {
        CHECK(closed.out.empty());
      }
    }
  }

  for (const bool json : {false, true}) {
    DYNAMIC_SECTION("broken stderr pipe " << (json ? "JSON" : "text")) {
      const auto parent =
          root / (json ? "broken-pipe-json-parent" : "broken-pipe-text-parent");
      std::filesystem::create_directories(parent);
      const auto parent_before = recursive_byte_snapshot(parent);
      const auto codex_store_before = recursive_byte_snapshot(codex_store);
      const auto claude_store_before = recursive_byte_snapshot(claude_store);
      const auto broken_pipe = run_cmd_broken_stderr_pipe(
          "open '" + image.string() + "' --dest '" +
              (parent / "dest").string() +
              "' --consent yes --agent-bin 'codex=" + codex_probe.string() +
              "' --agent-bin 'claude-code=" + claude_probe.string() + "'" +
              (json ? " --json" : ""),
          root);
      CHECK(broken_pipe.code == 4);
      CHECK(recursive_byte_snapshot(parent) == parent_before);
      CHECK(recursive_byte_snapshot(codex_store) == codex_store_before);
      CHECK(recursive_byte_snapshot(claude_store) == claude_store_before);
      if (json) {
        check_disclosure_error_json(broken_pipe.out);
      } else {
        CHECK(broken_pipe.out.empty());
      }
    }
  }

  SECTION("shared broken output sink exits 4 under JSON") {
    const auto parent = root / "broken-shared-json-parent";
    std::filesystem::create_directories(parent);
    const auto parent_before = recursive_byte_snapshot(parent);
    const auto codex_store_before = recursive_byte_snapshot(codex_store);
    const auto claude_store_before = recursive_byte_snapshot(claude_store);
    const auto code = run_cmd_broken_shared_pipe(
        "open '" + image.string() + "' --dest '" + (parent / "dest").string() +
            "' --consent yes --agent-bin 'codex=" + codex_probe.string() +
            "' --agent-bin 'claude-code=" + claude_probe.string() + "' --json",
        root);
    CHECK(code == 4);
    CHECK(recursive_byte_snapshot(parent) == parent_before);
    CHECK(recursive_byte_snapshot(codex_store) == codex_store_before);
    CHECK(recursive_byte_snapshot(claude_store) == claude_store_before);
  }

  SECTION("trust warning second write failure refuses before mutation") {
    const auto warning = std::string{biv::open_render::kTrustWarning} + '\n';
    const auto calibration =
        run_cmd("open '" + image.string() +
                    "' --dest './rlimit-calibration' --consent no "
                    "--agent-bin 'codex=" +
                    codex_probe.string() + "' --agent-bin 'claude-code=" +
                    claude_probe.string() + "' --json",
                root);
    REQUIRE(calibration.code == 0);
    simdjson::dom::parser calibration_parser;
    simdjson::dom::element calibration_document;
    REQUIRE(calibration_parser.parse(calibration.out).get(calibration_document) ==
            simdjson::SUCCESS);
    check_successful_probe_outcome(calibration_document,
                                   codex_probe.generic_string());
    check_successful_probe_outcome(calibration_document,
                                   claude_probe.generic_string());
    REQUIRE(calibration.err.size() > warning.size());
    REQUIRE(calibration.err.ends_with(warning));
    const auto cap = calibration.err.size() - warning.size();

    const auto parent = root / "rlimit-capped-parent";
    std::filesystem::create_directories(parent);
    const auto parent_before = recursive_byte_snapshot(parent);
    const auto codex_store_before = recursive_byte_snapshot(codex_store);
    const auto claude_store_before = recursive_byte_snapshot(claude_store);
    const auto stderr_path = root / "rlimit-capped-stderr.txt";
    const auto capped = run_cmd_limited_stderr(
        {"open", image.string(), "--dest", (parent / "dest").string(),
         "--consent", "yes", "--agent-bin", "codex=" + codex_probe.string(),
         "--agent-bin", "claude-code=" + claude_probe.string(), "--json"},
        root, stderr_path, static_cast<rlim_t>(cap));
    CHECK(capped.code == 4);
    CHECK(recursive_byte_snapshot(parent) == parent_before);
    CHECK(recursive_byte_snapshot(codex_store) == codex_store_before);
    CHECK(recursive_byte_snapshot(claude_store) == claude_store_before);
    check_internal_error_json(capped.out, "consent-surface-write-failed");
    CHECK(capped.out.find("\"envelope_version\"",
                          capped.out.find("\"envelope_version\"") + 1U) ==
          std::string::npos);
    REQUIRE(capped.err.size() == cap);
    CHECK(capped.err == calibration.err.substr(0, cap));
  }

  SECTION("CLI restores with probe output and normalized destination") {
  const auto invalid_json = run_cmd(
      "open '" + image.string() +
          "' --dest './invalid-json-restore' --consent no "
          "--agent-bin 'codex=" +
          invalid_output_probe.string() +
          "' --agent-bin 'claude-code=" + non_utf8_missing_pin + "' --json",
      root);
  REQUIRE(invalid_json.code == 0);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  CHECK(parser.parse(invalid_json.out).get(document) == simdjson::SUCCESS);
  const std::string replacement{"\xEF\xBF\xBD"};
  CHECK(invalid_json.out.find("claude-missing-" + replacement) !=
        std::string::npos);
  CHECK(invalid_json.out.find(replacement + "codex-cli 0.144.4") !=
        std::string::npos);
  CHECK(invalid_json.err.find(
            invalid_output_probe.generic_string() +
            " --version -> " + replacement + "codex-cli 0.144.4") !=
        std::string::npos);
  CHECK(invalid_json.err.find(
            "claude-missing-" + replacement +
            " --version -> <no output>") != std::string::npos);

  const auto deny_text = run_cmd(
      "open '" + image.string() +
          "' --dest './deny-text' --consent no "
          "--agent-bin 'codex=" +
          codex_probe.string() + "' --agent-bin 'claude-code=" +
          claude_probe.string() + "'",
      root);
  REQUIRE(deny_text.code == 0);
  CHECK(deny_text.err.find(codex_probe.generic_string() +
                           " --version -> codex-cli 0.144.4") !=
        std::string::npos);
  CHECK(deny_text.err.find(claude_probe.generic_string() +
                           " --version -> 2.1.211 (Claude Code)") !=
        std::string::npos);
  const auto deny_summary = deny_text.out.find("Session import summary:");
  REQUIRE(deny_summary != std::string::npos);
  CHECK(deny_text.out.find("Session import summary:", deny_summary + 1U) ==
        std::string::npos);

  const auto per_agent_json = run_cmd(
      "open '" + image.string() +
          "' --dest './per-agent-json' "
          "--consent codex=no,claude-code=no "
          "--agent-bin 'codex=" +
          codex_probe.string() + "' --agent-bin 'claude-code=" +
          claude_probe.string() + "' --json",
      root);
  REQUIRE(per_agent_json.code == 0);
  simdjson::dom::element per_agent_document;
  REQUIRE(parser.parse(per_agent_json.out).get(per_agent_document) ==
          simdjson::SUCCESS);
  bool prompt_shown = true;
  bool warning_shown = false;
  REQUIRE(per_agent_document["result"]["sessions"]["prompt_shown"].get(
              prompt_shown) == simdjson::SUCCESS);
  REQUIRE(per_agent_document["result"]["sessions"]["warning_shown"].get(
              warning_shown) == simdjson::SUCCESS);
  CHECK_FALSE(prompt_shown);
  CHECK(warning_shown);
  CHECK(per_agent_json.err.find(codex_probe.generic_string() +
                                " --version -> codex-cli 0.144.4") !=
        std::string::npos);
  CHECK(per_agent_json.err.find(
            claude_probe.generic_string() +
            " --version -> 2.1.211 (Claude Code)") != std::string::npos);

  std::filesystem::create_directories(root / "physical-destination");
  std::filesystem::create_directory_symlink(
      root / "physical-destination", root / "linked-destination");
  std::filesystem::create_directories(
      root / "physical-destination" / "restored sessions");

  const auto opened = run_cmd(
      "open '" + image.string() +
          "' --dest './linked-destination/restored sessions' --rename "
          "--consent yes "
          "--agent-bin 'codex=./bin/../bin/codex-probe'",
      root);

  REQUIRE(opened.code == 0);
  const auto final_path =
      process_root / "physical-destination" / "restored sessions(1)";
  const auto lexical_final =
      process_root / "linked-destination" / "restored sessions(1)";
  REQUIRE(read_text(final_path / "work.txt") == "workspace");
  CHECK(std::filesystem::equivalent(final_path, lexical_final));
  CHECK(read_text(codex_marker) ==
        (process_root / "bin" / "codex-probe").generic_string() +
            "|--version\n");
  CHECK(read_text(claude_marker) ==
        (root / "bin" / "claude").generic_string() + "|--version\n");
  CHECK(opened.out.find("resume from " + display_path(final_path) + ": ") !=
        std::string::npos);
  CHECK(opened.out.find("&&") == std::string::npos);
  CHECK(opened.err.find(codex_probe.generic_string() +
                        " --version -> codex-cli 0.144.4") !=
        std::string::npos);
  CHECK(opened.err.find(claude_probe.generic_string() +
                        " --version -> 2.1.211 (Claude Code)") !=
        std::string::npos);
  const auto opened_summary = opened.out.find("Session import summary:");
  REQUIRE(opened_summary != std::string::npos);
  CHECK(opened.out.find("Session import summary:", opened_summary + 1U) ==
        std::string::npos);

  bool saw_codex = false;
  for (const auto& path_text : regular_paths(codex_store)) {
    if (codex_before.contains(path_text)) {
      continue;
    }
    const std::filesystem::path path_value{path_text};
    if (path_value.extension() != ".jsonl") {
      continue;
    }
    const auto content = read_text(path_value);
    if (content.find(final_path.generic_string()) == std::string::npos) {
      continue;
    }
    const auto id_start = content.find("\"id\":\"");
    REQUIRE(id_start != std::string::npos);
    const auto id = content.substr(id_start + 6U, 36U);
    CHECK(opened.out.find("codex resume " + id) != std::string::npos);
    saw_codex = true;
  }
  CHECK(saw_codex);

  const auto claude_project =
      claude_store / "projects" / claude_project_key(final_path);
  REQUIRE(std::filesystem::is_directory(claude_project));
  bool saw_claude = false;
  for (const auto& entry :
       std::filesystem::directory_iterator(claude_project)) {
    if (!entry.is_regular_file() || entry.path().extension() != ".jsonl" ||
        claude_before.contains(entry.path().generic_string())) {
      continue;
    }
    const auto content = read_text(entry.path());
    CHECK(content.find(final_path.generic_string()) != std::string::npos);
    CHECK(opened.out.find("claude --resume " +
                          entry.path().stem().generic_string()) !=
          std::string::npos);
    saw_claude = true;
  }
  CHECK(saw_claude);
  CHECK(std::filesystem::equivalent(
      codex_probe, process_root / "bin" / "codex-probe"));
  CHECK(std::filesystem::equivalent(
      claude_probe, process_root / "bin" / "claude"));
  }
  std::filesystem::remove_all(root);
}
