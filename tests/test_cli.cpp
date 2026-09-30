#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
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
#include "cli_run.hpp"
#include "cli/url_consent.hpp"
#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"
#include "core/open/render.hpp"
#include "core/pack/pack.hpp"
#include "core/repo/capture.hpp"
#include "core/repo/classify.hpp"
#include "core/repo/discover.hpp"
#include "core/repo/eligibility.hpp"
#include "core/repo/restore.hpp"

// The parser otherwise belongs only to the CLI executable target.
#include "../src/cli/args.cpp"
// Exercise the actual CLI hook installer without adding a product test API.
#define main biv_cli_main_for_tests
#include "../src/cli/main.cpp"
#undef main

namespace open_repos_fixture {
// provenance=hand-built, interim: Task 7 replaces this builder with biv pack.
struct Member {
  biv::container::MemberMeta meta;
  std::vector<std::byte> data;
};

biv::repo::Git git() {
  auto resolved = biv::repo::Git::resolve([](std::string_view name)
      -> std::optional<std::string> {
    const auto* value = std::getenv(std::string{name}.c_str());
    return value ? std::optional<std::string>{value} : std::nullopt;
  });
  REQUIRE(resolved);
  return *resolved;
}

std::string run_git(const biv::repo::Git& git, const std::filesystem::path& cwd,
                    std::initializer_list<std::string> args) {
  auto result = git.run(args, {}, {.cwd = cwd,
                                   .ceiling = std::nullopt,
                                   .allow_user_protocol = true,
                                   .stdout_file = std::nullopt});
  REQUIRE(result);
  INFO(std::string(reinterpret_cast<const char*>(result->stderr_bytes.data()),
                   result->stderr_bytes.size()));
  REQUIRE(result->exit_code == 0);
  return {reinterpret_cast<const char*>(result->stdout_bytes.data()),
          result->stdout_bytes.size()};
}
}  // namespace open_repos_fixture

namespace {


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


std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> out(text.size());
  for (size_t index = 0; index < text.size(); ++index) {
    out[index] = static_cast<std::byte>(text[index]);
  }
  return out;
}

std::string payload_extent_digest(const biv::container::MemberMeta& meta,
                                  const std::vector<std::byte>& data) {
  biv::container::TarWriter writer{
      [](std::span<const std::byte>) -> biv::expected<void> { return {}; }};
  REQUIRE(writer.begin_member(meta));
  if (meta.kind == biv::scan::NodeKind::file) REQUIRE(writer.write_data(data));
  auto digest = writer.end_member();
  REQUIRE(digest);
  return *digest;
}

std::filesystem::path make_slice_e_consumer_image(
    const std::filesystem::path& root, std::span<const int> entry_schemas,
    std::span<const size_t> child_counts = {},
    const bool include_stub_payload = false,
    const bool stub_children_only = false) {
  REQUIRE((child_counts.empty() || child_counts.size() == entry_schemas.size()));
  std::filesystem::create_directories(root);
  biv::manifest::Manifest manifest{
      .format_version = 1,
      .required_capabilities = {},
      .image_id = "10000000-0000-4000-8000-000000000001",
      .app_version = "0.1.0",
      .created_at = "2026-08-15T00:00:00Z",
      .source_path = "/tmp/slice-e-source",
      .source_path_flavor = biv::manifest::PathFlavor::posix,
      .agent_sessions = {},
      .bivignore = {.source = "builtin", .builtin_id = "builtin-v1", .sha256_hex = "abc123"}};
  struct Member {
    biv::container::MemberMeta meta;
    std::vector<std::byte> data;
  };
  std::vector<Member> payload;
  const auto fixture = std::filesystem::path{BIV_SOURCE_DIR} / "tests" / "fixtures" /
                       "slice-e" / "data-only" / "successor-cardinality" / "session.jsonl";
  const auto fixture_bytes = bytes(read_text(fixture));
  biv::manifest::Checksums checksums;
  for (size_t index = 0; index < entry_schemas.size(); ++index) {
    const auto artifact = "agents/codex/stage1b-ii-" + std::to_string(index) + ".jsonl";
    biv::manifest::AgentSessionEntry entry;
    entry.agent = "codex";
    entry.agent_version_at_pack = "0.144.4";
    entry.relpath_key = ".";
    entry.original_path = "/tmp/slice-e-source";
    entry.normalized_path_key = "/tmp/slice-e-source";
    entry.normalization_scheme = "codex-cwd/v1";
    entry.path_flavor = biv::manifest::PathFlavor::posix;
    entry.provenance = {.store_root = "/tmp/codex", .locator = "sessions_root",
                        .discovery_tier = "default", .archived = false};
    entry.original_session_ids = {
        .primary = "10000000-0000-4000-8000-" + std::to_string(100000000000ULL + index),
        .parent = std::nullopt,
        .parent_in_image = std::nullopt};
    entry.artifacts = {artifact};
    const size_t child_count = child_counts.empty() ? 0U : child_counts[index];
    for (size_t child = 0; child < child_count; ++child) {
      entry.children.push_back({
          .original_id = "10000000-0000-4000-8000-" +
                         std::to_string(200000000000ULL + index * 100U + child),
          .artifacts = {"agents/codex/stage1b-ii-" + std::to_string(index) +
                        "-child-" + std::to_string(child) + ".jsonl"},
      });
    }
    entry.imported_at = "2026-08-15T00:00:00Z";
    entry.entry_schema = entry_schemas[index];
    if (stub_children_only &&
        entry.entry_schema > biv::manifest::kEntrySchemaParseCeiling) {
      entry.artifacts.clear();
    }
    const auto add_payload = [&](const std::string& path) {
      biv::container::MemberMeta meta{.path = path, .kind = biv::scan::NodeKind::file,
                                      .mode = 0600, .mtime_s = 1, .mtime_ns = 0,
                                      .size = fixture_bytes.size(), .symlink_target = {}};
      checksums.entries[path] = payload_extent_digest(meta, fixture_bytes);
      payload.push_back(Member{.meta = std::move(meta), .data = fixture_bytes});
    };
    if (entry_schemas[index] <= biv::manifest::kEntrySchemaParseCeiling ||
        include_stub_payload) {
      for (const auto& entry_artifact : entry.artifacts) {
        add_payload(entry_artifact);
      }
      for (const auto& child : entry.children) {
        for (const auto& child_artifact : child.artifacts) {
          biv::container::MemberMeta meta{.path = child_artifact,
                                          .kind = biv::scan::NodeKind::file,
                                          .mode = 0600,
                                          .mtime_s = 1,
                                          .mtime_ns = 0,
                                          .size = fixture_bytes.size(),
                                          .symlink_target = {}};
          checksums.entries[child_artifact] = payload_extent_digest(meta, fixture_bytes);
          payload.push_back(Member{.meta = std::move(meta), .data = fixture_bytes});
        }
      }
    }
    manifest.agent_sessions.push_back(std::move(entry));
  }

  const auto image = root / "slice-e-stage1b-ii.bvpk";
  std::ofstream out{image, std::ios::binary};
  REQUIRE(out);
  biv::container::ZstdCompressSink zstd{
      [&](std::span<const std::byte> chunk) -> biv::expected<void> {
        out.write(reinterpret_cast<const char*>(chunk.data()),
                  static_cast<std::streamsize>(chunk.size()));
        REQUIRE(out);
        return {};
      }};
  auto sink = zstd.as_sink();
  biv::container::TarWriter writer{sink};
  const auto write_member = [&](std::string path, std::string content) {
    REQUIRE(writer.begin_member(biv::container::MemberMeta{
        .path = std::move(path), .kind = biv::scan::NodeKind::file,
        .mode = 0644, .mtime_s = 1, .mtime_ns = 0,
        .size = content.size(), .symlink_target = {}}));
    REQUIRE(writer.write_data(std::as_bytes(std::span{content})));
    REQUIRE(writer.end_member());
  };
  auto serialized = biv::manifest::serialize(manifest);
  REQUIRE(serialized.has_value());
  auto manifest_json = std::move(*serialized);
  size_t schema_cursor = 0U;
  for (const int schema : entry_schemas) {
    const auto position = manifest_json.find("\"entry_schema\": 1", schema_cursor);
    REQUIRE(position != std::string::npos);
    if (schema != 1) {
      constexpr size_t value_offset = sizeof("\"entry_schema\": ") - 1U;
      manifest_json.replace(position + value_offset, 1U, std::to_string(schema));
    }
    schema_cursor = position + 1U;
  }
  write_member("manifest.json", std::move(manifest_json));
  write_member("checksums.json", biv::manifest::serialize(checksums));
  for (const auto& member : payload) {
    REQUIRE(writer.begin_member(member.meta));
    REQUIRE(writer.write_data(member.data));
    REQUIRE(writer.end_member());
  }
  REQUIRE(writer.finish());
  REQUIRE(zstd.finish());
  return image;
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

TEST_CASE("Stage 1b-ii all-skipped surfaces split eligible from skipped",
          "[slice-e][stage1b-ii]") {
  const auto root = make_tmp("slice-e-stage1b-ii-all-skipped");
  const auto all_skipped_root = root / "all-skipped";
  const auto mixed_root = root / "mixed";
  std::filesystem::create_directories(all_skipped_root);
  std::filesystem::create_directories(mixed_root);
  const std::array<int, 1> all_skipped_schemas{99};
  const std::array<int, 2> mixed_schemas{1, 99};
  const auto all_skipped = make_slice_e_consumer_image(all_skipped_root, all_skipped_schemas);
  const auto mixed = make_slice_e_consumer_image(mixed_root, mixed_schemas);
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex-home").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude-home").string()};
  const ScopedEnv home{"HOME", root.string()};

  constexpr std::string_view all_skipped_notice =
      "  codex: 0 session(s) can be imported; at least 1 session(s) will be skipped "
      "\u2014 the skipped session(s) are recorded in a format this version of "
      "biv cannot read and are not counted among the 0. Nothing has been "
      "written yet; a newer version of biv may be able to import them.";
  constexpr std::string_view all_skipped_summary =
      "  codex: 0 session(s) imported; at least 1 session(s) skipped \u2014 recorded in "
      "a format this version of biv cannot read.";

  const auto json = run_cmd("open '" + all_skipped.string() + "' --dest '" +
                                (root / "json-dest").string() + "' --json",
                            root);
  REQUIRE(json.code == 0);
  CHECK(json.err.find(all_skipped_notice) != std::string::npos);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(json.out).get(document) == simdjson::SUCCESS);
  bool prompt_shown = true;
  bool warning_shown = true;
  std::int64_t session_count = -1;
  std::int64_t primary_count = -1;
  std::int64_t descendant_count = -1;
  std::int64_t skipped_count = -1;
  std::int64_t unparsed_count = -1;
  REQUIRE(document["result"]["sessions"]["prompt_shown"].get(prompt_shown) == simdjson::SUCCESS);
  REQUIRE(document["result"]["sessions"]["warning_shown"].get(warning_shown) == simdjson::SUCCESS);
  const auto agent_summary = document["result"]["manifest"]["agent_sessions"].at(0);
  std::string_view outcome_kind;
  REQUIRE(document["result"]["sessions"]["agents"].at(0)["sessions"].at(0)["kind"].get(
              outcome_kind) == simdjson::SUCCESS);
  REQUIRE(agent_summary["session_count"].get(session_count) == simdjson::SUCCESS);
  REQUIRE(agent_summary["primary_count"].get(primary_count) == simdjson::SUCCESS);
  REQUIRE(agent_summary["descendant_count"].get(descendant_count) == simdjson::SUCCESS);
  REQUIRE(agent_summary["entry_schema_skipped_count"].get(skipped_count) == simdjson::SUCCESS);
  REQUIRE(agent_summary["entry_schema_unparsed_count"].get(unparsed_count) == simdjson::SUCCESS);
  CHECK_FALSE(prompt_shown);
  CHECK_FALSE(warning_shown);
  CHECK(outcome_kind == "EntrySchemaSkipped");
  CHECK(session_count == 0);
  CHECK(primary_count == 0);
  CHECK(descendant_count == 0);
  CHECK(skipped_count == 1);
  CHECK(unparsed_count == 1);

  const auto prewrite_dest = root / "closed-stderr-dest";
  const auto closed_stderr = run_cmd_closed_stderr(
      "open '" + all_skipped.string() + "' --dest '" + prewrite_dest.string() + "' --json", root);
  REQUIRE(closed_stderr.code == 4);
  CHECK_FALSE(std::filesystem::exists(prewrite_dest));
  check_disclosure_error_json(closed_stderr.out);

  const auto non_tty = run_cmd("open '" + all_skipped.string() + "' --dest '" +
                                   (root / "non-tty-dest").string() + "'",
                               root);
  REQUIRE(non_tty.code == 0);
  CHECK(non_tty.err.find(all_skipped_notice) != std::string::npos);
  CHECK(non_tty.err.find(biv::open_render::kTrustWarning) == std::string::npos);
  CHECK(non_tty.out.find(all_skipped_summary) != std::string::npos);

  const auto tty_no_flag = run_cmd_pty(
      "open '" + all_skipped.string() + "' --dest '" +
          (root / "tty-no-flag-dest").string() + "'",
      root, "n\n");
  REQUIRE(tty_no_flag.code == 0);
  CHECK(tty_no_flag.out.find(all_skipped_notice) != std::string::npos);
  CHECK(tty_no_flag.out.find("Import these sessions") == std::string::npos);
  CHECK(tty_no_flag.out.find(biv::open_render::kTrustWarning) == std::string::npos);
  CHECK(tty_no_flag.out.find(all_skipped_summary) != std::string::npos);

  const auto tty_consent_yes = run_cmd_pty(
      "open '" + all_skipped.string() + "' --dest '" +
          (root / "tty-consent-yes-dest").string() + "' --consent yes",
      root, "n\n");
  REQUIRE(tty_consent_yes.code == 0);
  CHECK(tty_consent_yes.out.find(all_skipped_notice) != std::string::npos);
  CHECK(tty_consent_yes.out.find("Import these sessions") == std::string::npos);
  CHECK(tty_consent_yes.out.find(biv::open_render::kTrustWarning) == std::string::npos);
  CHECK(tty_consent_yes.out.find(all_skipped_summary) != std::string::npos);

  constexpr std::string_view mixed_notice =
      "  codex: 1 session(s) can be imported; at least 1 session(s) will be skipped "
      "\u2014 the skipped session(s) are recorded in a format this version of "
      "biv cannot read and are not counted among the 1. Nothing has been "
      "written yet; a newer version of biv may be able to import them.";
  const auto flag_no = run_cmd("open '" + mixed.string() + "' --dest '" +
                                   (root / "flag-no-dest").string() + "' --consent no",
                               root);
  REQUIRE(flag_no.code == 2);
  CHECK(flag_no.err.find(mixed_notice) != std::string::npos);
  CHECK(flag_no.out.find("  codex: 0 session(s) imported; at least 1 session(s) skipped") !=
        std::string::npos);

  const auto prompt_no = run_cmd_pty(
      "open '" + mixed.string() + "' --dest '" + (root / "prompt-no-dest").string() + "'",
      root, "n\n");
  REQUIRE(prompt_no.code == 2);
  CHECK(prompt_no.out.find(mixed_notice) != std::string::npos);
  CHECK(prompt_no.out.find("Import these sessions") != std::string::npos);
  CHECK(prompt_no.out.find("  codex: 0 session(s) imported; at least 1 session(s) skipped") !=
        std::string::npos);

  std::filesystem::remove_all(root);
}

TEST_CASE("Slice E successor distinguishes exact and floor skipped cardinality",
          "[slice-e][successor]") {
  struct Case {
    std::string_view name;
    std::vector<int> schemas;
    std::vector<size_t> child_counts;
    size_t skipped;
    size_t unparsed;
    bool at_least;
  };
  const std::array cases{
      Case{"parsed-childed", {2}, {2}, 3U, 0U, false},
      Case{"stubbed-childed-wire", {3}, {2}, 1U, 1U, true},
      Case{"mixed-shapes", {2, 3}, {2, 2}, 4U, 1U, true},
  };

  const auto root = make_tmp("slice-e-successor-cardinality");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex-home").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude-home").string()};
  const ScopedEnv home{"HOME", root.string()};
  for (const auto& test_case : cases) {
    DYNAMIC_SECTION(test_case.name) {
      const auto case_root = root / test_case.name;
      std::filesystem::create_directories(case_root);
      const auto image = make_slice_e_consumer_image(
          case_root, test_case.schemas, test_case.child_counts);
      const auto prefix = test_case.at_least ? "at least " : "";
      const auto notice = "  codex: 0 session(s) can be imported; " +
                          std::string{prefix} + std::to_string(test_case.skipped) +
                          " session(s) will be skipped";
      const auto summary = "  codex: 0 session(s) imported; " +
                           std::string{prefix} + std::to_string(test_case.skipped) +
                           " session(s) skipped";

      const auto json = run_cmd(
          "open '" + image.string() + "' --dest '" +
              (case_root / "json-dest").string() + "' --json",
          root);
      REQUIRE(json.code == 0);
      CHECK(json.err.find(notice) != std::string::npos);
      simdjson::dom::parser parser;
      simdjson::dom::element document;
      REQUIRE(parser.parse(json.out).get(document) == simdjson::SUCCESS);
      const auto agent = document["result"]["manifest"]["agent_sessions"].at(0);
      std::int64_t session_count = -1;
      std::int64_t primary_count = -1;
      std::int64_t descendant_count = -1;
      std::int64_t skipped_count = -1;
      REQUIRE(agent["session_count"].get(session_count) == simdjson::SUCCESS);
      REQUIRE(agent["primary_count"].get(primary_count) == simdjson::SUCCESS);
      REQUIRE(agent["descendant_count"].get(descendant_count) == simdjson::SUCCESS);
      REQUIRE(agent["entry_schema_skipped_count"].get(skipped_count) == simdjson::SUCCESS);
      CHECK(session_count == 0);
      CHECK(primary_count == 0);
      CHECK(descendant_count == 0);
      CHECK(skipped_count == static_cast<std::int64_t>(test_case.skipped));
      if (test_case.unparsed == 0U) {
        simdjson::dom::element absent;
        CHECK(agent["entry_schema_unparsed_count"].get(absent) ==
              simdjson::NO_SUCH_FIELD);
      } else {
        std::int64_t unparsed_count = -1;
        REQUIRE(agent["entry_schema_unparsed_count"].get(unparsed_count) ==
                simdjson::SUCCESS);
        CHECK(unparsed_count == static_cast<std::int64_t>(test_case.unparsed));
      }

      const auto text = run_cmd(
          "open '" + image.string() + "' --dest '" +
              (case_root / "text-dest").string() + "'",
          root);
      REQUIRE(text.code == 0);
      CHECK(text.err.find(notice) != std::string::npos);
      CHECK(text.out.find(summary) != std::string::npos);
      CHECK(text.out.find("EntrySchemaSkipped") == std::string::npos);
    }
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("Slice E stub footprints admit present entry and child members without requiring absence",
          "[slice-e][stub-footprint]") {
  const auto root = make_tmp("slice-e-stub-footprint-members");
  const ScopedEnv codex_home{"CODEX_HOME", (root / "absent-codex-home").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR", (root / "absent-claude-home").string()};
  const ScopedEnv home{"HOME", root.string()};
  const std::array<int, 1> stub_schema{
      biv::manifest::kEntrySchemaParseCeiling + 1};
  const std::array<size_t, 1> one_child{1U};

  const auto entry_member = make_slice_e_consumer_image(
      root / "entry-member", stub_schema, {}, true);
  const auto child_member = make_slice_e_consumer_image(
      root / "child-member", stub_schema, one_child, true, true);
  const auto declared_absent = make_slice_e_consumer_image(
      root / "declared-absent", stub_schema);

  const auto run_open = [&](const std::filesystem::path& image,
                            const std::string_view name) {
    const auto dest = root / (std::string{name} + "-dest");
    const auto result = run_cmd("open '" + image.string() + "' --dest '" +
                                    dest.string() + "' --json",
                                root);
    CAPTURE(name, result.code, result.out, result.err);
    CHECK(result.code == 0);
    CHECK(result.err.find("at least 1 session(s) will be skipped") !=
          std::string::npos);
    CHECK(result.out.find("EntrySchemaSkipped") != std::string::npos);
  };

  run_open(entry_member, "entry-member");
  run_open(child_member, "child-member");
  run_open(declared_absent, "declared-absent");
  std::filesystem::remove_all(root);
}

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

TEST_CASE("CLI pack JSON keeps summary repos empty while archive carries rows",
          "[pack-repos]") {
  const auto root = make_tmp("pack-repos-json");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  auto handle = open_repos_fixture::git();
  open_repos_fixture::run_git(handle, source, {"init", "-b", "main"});
  write_file(source / "tracked.txt", "tracked\n");
  open_repos_fixture::run_git(handle, source, {"add", "tracked.txt"});
  open_repos_fixture::run_git(
      handle, source,
      {"-c", "user.name=Biv Test", "-c",
       "user.email=biv@example.invalid", "commit", "-m", "initial"});

  const auto packed = run_cmd(
      "pack '" + source.string() + "' --offline --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  simdjson::dom::parser parser;
  simdjson::dom::element document;
  REQUIRE(parser.parse(packed.out).get(document) == simdjson::SUCCESS);
  simdjson::dom::array summary_repos;
  REQUIRE(document["result"]["manifest"]["repos"].get(summary_repos) ==
          simdjson::SUCCESS);
  CHECK(summary_repos.size() == 0U);

  biv::open::OpenOptions options;
  options.image = root / "sample.bvpk";
  auto plan = biv::open::plan_open(options);
  REQUIRE(plan.has_value());
  REQUIRE(plan->manifest().repos.size() == 1U);
  CHECK(plan->manifest().repos.front().relpath == ".");
  std::filesystem::remove_all(root);
}

TEST_CASE("a6.15 zero state: no divergence -> both carriers absent on real verb envelopes", "[a6-fabric]") {
  // the exact fixture sequence of "CLI pack/open round-trip emits JSON envelopes"
  // (tests/test_cli.cpp:891-916), reused verbatim:
  const auto root = make_tmp("a6-15-zero");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");

  const auto packed = run_cmd("pack '" + source.string() + "' --json", root);
  REQUIRE(packed.code == 0);
  REQUIRE(std::filesystem::exists(root / "sample.bvpk"));
  CHECK(packed.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(packed.out.find("url_divergence_refusals") == std::string::npos);
  CHECK(packed.out.find("UrlDivergence") == std::string::npos);

  const auto opened = run_cmd("open '" + (root / "sample.bvpk").string() + "' --dest '" +
                                  (root / "restore").string() + "' --json",
                              root);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(opened.out.find("url_divergence_refusals") == std::string::npos);
  CHECK(opened.out.find("UrlDivergence") == std::string::npos);
  std::filesystem::remove_all(root);
}

namespace slice_e_controls {

class ScopedPackDiscoveryEnv {
 public:
  ScopedPackDiscoveryEnv(const std::filesystem::path& root,
                         const std::filesystem::path& claude_store)
      : home_{"HOME", (root / "home").string()},
        claude_{"CLAUDE_CONFIG_DIR", claude_store.string()},
        codex_{"CODEX_HOME", (root / "absent-codex").string()},
        codex_sqlite_{"CODEX_SQLITE_HOME",
                      (root / "absent-codex-sqlite").string()} {}

 private:
  ScopedEnv home_;
  ScopedEnv claude_;
  ScopedEnv codex_;
  ScopedEnv codex_sqlite_;
};

void require_store_roots_under(
    const std::filesystem::path& root,
    std::initializer_list<std::filesystem::path> store_roots) {
  const auto canonical_root = std::filesystem::canonical(root);
  for (const auto& store_root : store_roots) {
    const auto relative = std::filesystem::weakly_canonical(store_root)
                              .lexically_relative(canonical_root);
    CAPTURE(store_root, canonical_root, relative);
    REQUIRE_FALSE(relative.empty());
    REQUIRE_FALSE(relative.is_absolute());
    REQUIRE(*relative.begin() != "..");
  }
}

void copy_fixture_case(const std::filesystem::path& fixture,
                       const std::filesystem::path& store,
                       const std::filesystem::path& source,
                       const std::filesystem::path& child_relative) {
  constexpr std::string_view session_id =
      "aaaaaaaa-1111-4000-8000-00000000a120";
  const auto project = store / "projects" / "-ws-proj";
  auto main = read_text(fixture / "projects" / "-ws-proj" /
                        (std::string{session_id} + ".jsonl"));
  for (std::size_t position = 0;
       (position = main.find("/ws/proj", position)) != std::string::npos;) {
    main.replace(position, 8U, source.generic_string());
    position += source.generic_string().size();
  }
  write_file(project / (std::string{session_id} + ".jsonl"), main);
  const auto fixture_child = fixture / "projects" / "-ws-proj" /
                             std::string{session_id} / child_relative;
  write_file(project / std::string{session_id} / child_relative,
             read_text(fixture_child));
  write_file(store / "auth.json", "SLICE_E_CREDENTIAL_DECOY\n");
}

}  // namespace slice_e_controls

TEST_CASE("Claude reference resolution controls use the shipped CLI",
          "[slice-e][slice-e-control]") {
  struct Case {
    std::string_view name;
    std::string_view reference;
    std::string_view subtree;
    std::string_view marker;
  };
  constexpr std::string_view decoy = "SLICE_E_CREDENTIAL_DECOY";
  const auto fixture = std::filesystem::path{BIV_SOURCE_DIR} / "tests" /
                       "fixtures" / "slice-e" / "claude" /
                       "flat-subagents-unchanged";
  for (const auto& test : std::array{
           Case{"flat bare-hex", "a00e74f5f82549807",
                "subagents/agent-a00e74f5f82549807.jsonl",
                "SLICE_E_FLAT_BARE"},
           Case{"flat slug-hex", "explore-b00e74f5f82549807",
                "subagents/agent-explore-b00e74f5f82549807.jsonl",
                "SLICE_E_FLAT_SLUG"},
           Case{"nested subagents workflow", "c00e74f5f82549807",
                "subagents/workflows/wf-a/agent-c00e74f5f82549807.jsonl",
                "SLICE_E_NESTED_BARE"}}) {
    DYNAMIC_SECTION(test.name) {
      const auto root = std::filesystem::canonical(
          make_tmp("slice-e-claude-" + std::string{test.name}));
      const auto source = root / "proj";
      const auto store = root / "claude";
      const auto destination = root / "restore";
      std::filesystem::create_directories(source);
      write_file(source / "work.txt", "workspace\n");
      slice_e_controls::copy_fixture_case(fixture, store, source,
                                          test.subtree);
      const slice_e_controls::ScopedPackDiscoveryEnv discovery_env{root, store};
      const auto claude_probe = write_executable(
          root / "bin" / "claude", "printf '2.1.211 (Claude Code)\\n'\n");

      const auto packed =
          run_cmd("pack '" + source.string() + "' --json", root);

      REQUIRE((packed.code == 0 || packed.code == 2));
      const auto image = root / "proj.bvpk";
      REQUIRE(std::filesystem::is_regular_file(image));
      CHECK(read_text(image).find(decoy) == std::string::npos);
      const auto opened = run_cmd(
          "open '" + image.string() + "' --dest '" + destination.string() +
              "' --consent no --agent-bin 'claude-code=" +
              claude_probe.string() + "' --json",
          root);
      REQUIRE(opened.code == 0);
      std::optional<std::filesystem::path> restored_main;
      std::optional<std::filesystem::path> restored_child;
      for (const auto& entry :
           std::filesystem::recursive_directory_iterator(destination)) {
        if (!entry.is_regular_file() || entry.path().extension() != ".jsonl") {
          continue;
        }
        const auto content = read_text(entry.path());
        if (content.find("\"senderTaskId\":\"" +
                         std::string{test.reference} + "\"") !=
            std::string::npos) {
          restored_main = entry.path();
        }
        if (entry.path().filename() ==
                "agent-" + std::string{test.reference} + ".jsonl" &&
            entry.path().generic_string().ends_with(test.subtree)) {
          restored_child = entry.path();
        }
      }
      REQUIRE(restored_main.has_value());
      REQUIRE(restored_child.has_value());
      CHECK(read_text(*restored_child).find(test.marker) != std::string::npos);
      CHECK(restored_child->generic_string().find(
                "/" + restored_main->stem().generic_string() + "/") !=
            std::string::npos);
      slice_e_controls::require_store_roots_under(
          root, {source, store, destination});
      for (const auto& entry :
           std::filesystem::recursive_directory_iterator(destination)) {
        if (entry.is_regular_file()) {
          CHECK(read_text(entry.path()).find(decoy) == std::string::npos);
        }
      }
      std::filesystem::remove_all(root);
    }
  }
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

TEST_CASE("CLI pack carries a live torn tail into text and JSON warnings") {
  const auto root = std::filesystem::canonical(make_tmp("torn-tail-route"));
  const auto source = root / "proj";
  const auto store = root / "codex";
  constexpr std::string_view id = "019faaaa-bbbb-7ccc-8ddd-eeeeeeee7920";
  constexpr std::string_view tail = "{bad";
  const auto artifact = "agents/codex/" + std::string{id} + ".jsonl";
  std::filesystem::create_directories(source);
  write_file(source / "work.txt", "workspace");
  write_file(store / "sessions" / "2026" / "08" / "06" /
                 ("rollout-2026-08-06T01-00-00-" + std::string{id} + ".jsonl"),
             "{\"timestamp\":\"2026-08-06T01:00:00Z\",\"type\":\"session_meta\",\"payload\":{\"id\":\"" +
                 std::string{id} + "\",\"cwd\":\"" + source.generic_string() +
                 "\",\"cli_version\":\"0.142.5\"}}\n" + std::string{tail});
  const ScopedEnv codex_home{"CODEX_HOME", store.string()};
  const ScopedEnv claude_config{"CLAUDE_CONFIG_DIR", (root / "no-claude").string()};
  const auto text = run_cmd("pack '" + source.string() + "'", root);
  REQUIRE(text.code == 2);
  CHECK(text.out.find("warning: torn tail dropped from " + artifact + ": 4 bytes") != std::string::npos);
  std::filesystem::remove(root / "proj.bvpk");
  const auto json = run_cmd("pack '" + source.string() + "' --json", root);
  REQUIRE(json.code == 2);
  simdjson::dom::parser parser; simdjson::dom::element document;
  REQUIRE(parser.parse(json.out).get(document) == simdjson::SUCCESS);
  simdjson::dom::array warnings;
  REQUIRE(document["warnings"].get(warnings) == simdjson::SUCCESS);
  const auto found = std::ranges::find_if(warnings, [](const simdjson::dom::element warning) {
    std::string_view kind; return warning["kind"].get(kind) == simdjson::SUCCESS && kind == "TornTailDropped";
  });
  REQUIRE(found != warnings.end());
  std::string_view kind, path, member; std::uint64_t bytes = 0;
  REQUIRE((*found)["kind"].get(kind) == simdjson::SUCCESS);
  REQUIRE((*found)["path"].get(path) == simdjson::SUCCESS);
  REQUIRE((*found)["artifact"].get(member) == simdjson::SUCCESS);
  REQUIRE((*found)["bytes"].get(bytes) == simdjson::SUCCESS);
  CHECK(kind == "TornTailDropped"); CHECK(path == id); CHECK(member == artifact); CHECK(bytes == tail.size());
  std::filesystem::remove_all(root);
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
        "  --accept-url-divergence\n"
        "  --offline\n"
        "  --network\n"
        "  --agent-bin <claude-code|codex>=<absolute-or-relative-path>\n"
        "  --rename\n"
        "  --abort-on-collision\n"
        "  --verify\n"
        "  --json\n");
  CHECK(help.err.empty());
  std::filesystem::remove_all(root);
}

TEST_CASE("A6-R2 PROMPT D bytes are golden", "[a6-fabric]") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_prompt_d(facts) ==
        "  fetch: the address git will contact for /w/repo differs from the requested address:\n"
        "    requested: https://req\n"
        "    effective: https://eff\n"
        "  Contact the effective address? [y/N] ");
}

TEST_CASE("A6-R4 accepted notice bytes are golden", "[a6-fabric]") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  CHECK(biv::cli::render_accepted_notice(facts) ==
        "  fetch: contacting https://eff for /w/repo (requested: https://req — accepted for this run)\n");
}

TEST_CASE("A6-R4 refusal + guidance bytes are golden", "[a6-fabric]") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/w/repo", "https://req", "https://eff"};
  const auto machine_detail = biv::cli::render_entry_refusal_sentence(
      "a/b.txt", facts.op, facts.effective, facts.requested);
  CHECK(machine_detail ==
        "a/b.txt: restore failed — fetch would contact https://eff instead of the requested https://req; approval was not given.");
  CHECK(biv::cli::render_pack_refusal_detail(facts) ==
        "pack refused: fetch for /w/repo would contact https://eff instead of the requested https://req; approval was not given. Re-run interactively to review, or pass --accept-url-divergence to proceed.");
  CHECK(biv::cli::render_entry_refusal_line("a/b.txt", facts) ==
        "  " + machine_detail + "\n");
  CHECK(biv::cli::render_run_guidance_line(2) ==
        "  open: 2 restore entry(ies) refused — the effective address was not approved. Re-run interactively to review, or pass --accept-url-divergence to proceed.\n");
}

TEST_CASE("A9 unclaimed git entry detail is byte-golden for every reason",
          "[a6-fabric]") {
  for (const auto reason : {"symlink", "special-file", "unreadable-marker"}) {
    CHECK(biv::cli::render_unclaimed_git_entry_detail(
              "/w/hostile\r-\xe2\x80\xae/.git", reason) ==
          "pack refused: /w/hostile\\r-\\u{202e}/.git is a .git-named "
          "entry that is not a repository boundary (" + std::string{reason} +
          "); remove or repair it and re-run.");
  }
}

TEST_CASE("A9 CLI emits the typed unclaimed git refusal", "[pack-repos]") {
  const auto root = make_tmp("unclaimed-git-cli");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  std::filesystem::create_symlink("missing-target", source / ".git");
  const ScopedEnv home{"HOME", root.string()};
  const ScopedEnv codex_home{"CODEX_HOME", (root / "no-codex").string()};
  const ScopedEnv claude_home{"CLAUDE_CONFIG_DIR",
                              (root / "no-claude").string()};

  const auto result =
      run_cmd("pack '" + source.string() + "' --json", root);
  CHECK(result.code == 3);
  CHECK(result.err.empty());
  CHECK(result.out.find("\"kind\": \"UnclaimedGitEntry\"") !=
        std::string::npos);
  CHECK(result.out.find("\"reason\": \"symlink\"") != std::string::npos);
  CHECK(result.out.find("pack refused: " +
                        (std::filesystem::canonical(source) / ".git")
                            .generic_string()) !=
        std::string::npos);
  CHECK_FALSE(std::filesystem::exists(root / "sample.bvpk"));
  std::filesystem::remove_all(root);
}

TEST_CASE("A6-R2 default N: empty answer refuses; y proceeds; wrapper renders byte-whole to err",
          "[a6-fabric]") {
  const biv::cli::UrlDivergenceFacts facts{"fetch", "/r", "https://q", "https://e"};
  const auto golden = biv::cli::render_prompt_d(facts);
  { std::istringstream in{"\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"y\n"}; std::ostringstream err;
    CHECK(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"Y\n"}; std::ostringstream err;
    CHECK(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"n\n"}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{""}; std::ostringstream err;
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
  { std::istringstream in{"y\n"}; std::ostringstream err;
    in.setstate(std::ios::failbit);
    CHECK_FALSE(biv::cli::prompt_url_divergence(facts, in, err));
    CHECK(err.str() == golden); }
}

TEST_CASE("a6-R3 pack and open accept --accept-url-divergence", "[a6-fabric]") {
  // open: flag parses alongside an image; no usage error
  {
    char prog[] = "biv", verb[] = "open", flag[] = "--accept-url-divergence", img[] = "x.bvpk";
    char* argv[] = {prog, verb, flag, img};
    const auto parsed = biv::cli::parse_args(std::span<char* const>{argv, 4});
    REQUIRE(parsed.has_value());
    CHECK(parsed->accept_url_divergence);
    CHECK(parsed->verb == biv::cli::Verb::open);
  }
  // pack: the ONE accepted flag; other flags still rejected
  {
    char prog[] = "biv", verb[] = "pack", flag[] = "--accept-url-divergence", dir[] = "srcdir";
    char* argv[] = {prog, verb, flag, dir};
    const auto parsed = biv::cli::parse_args(std::span<char* const>{argv, 4});
    REQUIRE(parsed.has_value());
    CHECK(parsed->accept_url_divergence);
  }
  {
    char prog[] = "biv", verb[] = "pack", flag[] = "--not-a-flag", dir[] = "srcdir";
    char* argv[] = {prog, verb, flag, dir};
    CHECK_FALSE(biv::cli::parse_args(std::span<char* const>{argv, 4}).has_value());
  }
}

namespace open_repos_fixture {

struct Image {
  biv::manifest::Manifest manifest{
      .image_id = "10000000-0000-4000-8000-000000000004",
      .app_version = "0.1.0", .created_at = "2026-09-19T00:00:00Z",
      .source_path = "/fixture", .agent_sessions = {},
      .bivignore = {.source = "builtin", .builtin_id = "builtin-v1",
                    .sha256_hex = "abc123"}};
  std::vector<Member> payload;
  std::vector<Member> artifacts;

  static Member member(const std::string& path, std::string_view content) {
    return {{.path = path, .kind = biv::scan::NodeKind::file, .mode = 0600,
             .mtime_s = 1, .mtime_ns = 0, .size = content.size(),
             .symlink_target = {}}, bytes(content)};
  }

  static Member directory(const std::string& path) {
    return {{.path = path, .kind = biv::scan::NodeKind::dir, .mode = 0755,
             .mtime_s = 1, .mtime_ns = 0, .size = 0,
             .symlink_target = {}}, {}};
  }

  static Member symlink(const std::string& path, std::string target) {
    return {{.path = path, .kind = biv::scan::NodeKind::symlink, .mode = 0777,
             .mtime_s = 1, .mtime_ns = 0, .size = 0,
             .symlink_target = std::move(target)}, {}};
  }

  void capture_repo(const std::filesystem::path& root, const std::string& id,
                    const std::string& relpath, bool penumbra = false,
                    bool overlay = false, bool tracked_symlink = false) {
    const auto source = root / ("source-" + id);
    std::filesystem::create_directories(source);
    const auto handle = git();
    run_git(handle, source, {"init", "-b", "main"});
    write_file(source / "a.txt", "committed\n");
    write_file(source / ".gitignore", "ignored.txt\n");
    if (tracked_symlink) {
      std::filesystem::create_symlink("../../outside-c6p", source / "evil");
    }
    run_git(handle, source, {"add", "."});
    run_git(handle, source, {"-c", "user.name=Fixture", "-c",
                           "user.email=fixture@example.invalid", "commit", "-m", "base"});
    run_git(handle, source, {"branch", "local-topic"});
    if (overlay) {
      const auto remote = root / ("remote-" + id);
      std::filesystem::create_directories(remote);
      run_git(handle, remote, {"init", "--bare", "--initial-branch=main"});
      run_git(handle, source, {"remote", "add", "origin", remote.string()});
      run_git(handle, source, {"push", "-u", "origin", "main"});
      run_git(handle, source, {"checkout", "local-topic"});
      write_file(source / "a.txt", "local topic\n");
      run_git(handle, source, {"add", "a.txt"});
      run_git(handle, source, {"-c", "user.name=Fixture", "-c",
                             "user.email=fixture@example.invalid", "commit", "-m", "topic"});
      run_git(handle, source, {"checkout", "main"});
    }
    if (penumbra) write_file(source / "ignored.txt", "ignored bytes\n");
    CHECK(run_git(handle, source, {"status", "--porcelain=v2"}).empty());
    auto matcher = biv::ignore::Matcher::compile("", true);
    REQUIRE(matcher);
    auto discovery = biv::repo::discover(source, *matcher);
    REQUIRE(discovery);
    REQUIRE(discovery->repos.size() == 1);
    auto classified = biv::repo::classify(handle, source, *discovery);
    REQUIRE(classified);
    REQUIRE(classified->fence == biv::repo::Classification::Fence::none);
    auto entry = std::move(classified->entry);
    entry.id = id;
    REQUIRE(biv::repo::run_eligibility(handle, entry, biv::repo::EligibilityMode::network));
    auto captured = biv::repo::capture(handle, entry, root / ("scratch-" + id));
    REQUIRE(captured);
    if (overlay) {
      REQUIRE(entry.capture_mode == biv::repo::CaptureMode::overlay);
      REQUIRE(entry.local_refs_bundle);
    } else {
      REQUIRE(entry.bundle);
    }
    for (const auto& artifact : captured->artifacts) {
      artifacts.push_back(member(artifact.archive_path.generic_string(), read_text(artifact.disk_path)));
    }
    entry.relpath = relpath;
    manifest.repos.push_back(std::move(entry));
    if (penumbra) {
      REQUIRE(relpath == ".");
      payload.push_back(member("payload/ignored.txt", "ignored bytes\n"));
    }
  }

  std::filesystem::path write(const std::filesystem::path& root,
                              const std::string& name = "repos.bvpk",
                              const bool bad_checksum = false,
                              const bool omit_checksum = false) const {
    const auto image = root / name;
    biv::manifest::Checksums checksums;
    for (const auto& group : {payload, artifacts}) {
      for (const auto& part : group) {
        checksums.entries[part.meta.path] = payload_extent_digest(part.meta, part.data);
      }
    }
    if (bad_checksum) {
      REQUIRE_FALSE(artifacts.empty());
      checksums.entries[artifacts.front().meta.path] = std::string(64, '0');
    }
    if (omit_checksum) {
      REQUIRE_FALSE(artifacts.empty());
      checksums.entries.erase(artifacts.front().meta.path);
    }
    auto serialized = biv::manifest::serialize(manifest);
    if (!serialized) INFO(serialized.error().detail);
    REQUIRE(serialized);
    std::ofstream out{image, std::ios::binary};
    biv::container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk)
        -> biv::expected<void> {
      out.write(reinterpret_cast<const char*>(chunk.data()), static_cast<std::streamsize>(chunk.size()));
      REQUIRE(out.good());
      return {};
    }};
    biv::container::TarWriter writer{zstd.as_sink()};
    const auto append = [&](const Member& part) {
      REQUIRE(writer.begin_member(part.meta));
      if (part.meta.kind == biv::scan::NodeKind::file) REQUIRE(writer.write_data(part.data));
      REQUIRE(writer.end_member());
    };
    append(member("manifest.json", *serialized));
    append(member("checksums.json", biv::manifest::serialize(checksums)));
    for (const auto& part : payload) append(part);
    for (const auto& part : artifacts) append(part);
    REQUIRE(writer.finish());
    REQUIRE(zstd.finish());
    return image;
  }
};

std::filesystem::path build_repo_image(const std::filesystem::path& root) {
  Image fixture;
  fixture.capture_repo(root, "r-main", ".", true);
  return fixture.write(root);
}

// The sealed git-shim.sh instrument, with its required variables set INSIDE
// the wrapper because Git deliberately forwards only its allowed environment.
void install_trace(const std::filesystem::path& root, const bool inject_divergence = false) {
  const auto real = git().executable();
  write_file(root / "trace", "");
  write_file(root / "bin" / "git",
      "#!/usr/bin/env bash\nBIV_GIT_TRACE='" + (root / "trace").string() +
      "'\nBIV_GIT_REAL='" + real.string() + "'\n"
      "[ -n \"${BIV_GIT_TRACE-}\" ] && [ -n \"${BIV_GIT_REAL-}\" ] && [ -x \"${BIV_GIT_REAL}\" ] || exit 97\n"
      "{ printf '%s' \"$PWD\"; for a in \"$@\"; do printf '\\t%s' \"$a\"; done; printf '\\n'; } >> \"$BIV_GIT_TRACE\" || exit 98\n" +
      (inject_divergence ?
       "for a in \"$@\"; do if [ \"$a\" = --get-url ]; then printf '%s\\n' 'https://effective.invalid/repo'; exit 0; fi; done\n" : "") +
      "exec \"$BIV_GIT_REAL\" \"$@\"\n");
  std::filesystem::permissions(root / "bin" / "git", std::filesystem::perms::owner_all);
}

}  // namespace open_repos_fixture

TEST_CASE("open repos real bundle preserves clean HEAD branch ignored bytes and local refs", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-bundle");
  const ScopedEnv home{"HOME", root.string()};
  const auto image = build_repo_image(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  const auto opened = run_cmd("open '" + image.string() + "' --verify --dest out --network --json", root);
  INFO(opened.out);
  REQUIRE(opened.code == 0);
  const auto trace = read_text(root / "trace");
  CHECK(trace.find("out.bvpk-open.stage/repos/r-main/repo.bundle") != std::string::npos);
  const auto handle = git();
  CHECK(run_git(handle, root / "out", {"status", "--porcelain=v2"}).empty());
  CHECK(run_git(handle, root / "out", {"rev-parse", "HEAD"}) ==
        run_git(handle, root / "source-r-main", {"rev-parse", "HEAD"}));
  CHECK(run_git(handle, root / "out", {"symbolic-ref", "HEAD"}) == "refs/heads/main\n");
  CHECK(run_git(handle, root / "out", {"rev-parse", "local-topic"}) ==
        run_git(handle, root / "out", {"rev-parse", "HEAD"}));
  CHECK(read_text(root / "out" / "ignored.txt") == "ignored bytes\n");
  CHECK_FALSE(std::filesystem::exists(root / "out.bvpk-open.stage"));
}

TEST_CASE("open repos admits only named checksummed files and rejects missing artifacts", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-members");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-one", "repo");
  SECTION("named artifact restores real git") {
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() + "' --dest out --verify --network --json", root);
    INFO(opened.out);
    REQUIRE(opened.code == 0);
    CHECK(run_git(git(), root / "out/repo", {"rev-parse", "HEAD"}) == *fixture.manifest.repos.front().sha + "\n");
  }
  SECTION("stray checksummed member") {
    fixture.artifacts.push_back(Image::member("repos/r-one/stray.bin", "stray"));
    const auto image = fixture.write(root);
    const auto result = run_cmd("open '" + image.string() + "' --dest out --json", root);
    CHECK(result.code == 3);
    CHECK(result.out.find("UnmanifestedMember") != std::string::npos);
    CHECK(result.out.find("repos/r-one/stray.bin") != std::string::npos);
  }
  SECTION("named artifact without checksum") {
    const auto image = fixture.write(root, "unchecked.bvpk", false, true);
    const auto result = run_cmd("open '" + image.string() + "' --dest out --json", root);
    CHECK(result.code == 3);
    CHECK(result.out.find("UnmanifestedMember") != std::string::npos);
    CHECK(result.out.find("repos/r-one/repo.bundle") != std::string::npos);
    CHECK_FALSE(std::filesystem::exists(root / "out"));
  }
  SECTION("named artifact absent") {
    fixture.artifacts.clear();
    const auto image = fixture.write(root);
    const auto result = run_cmd("open '" + image.string() + "' --dest out --json", root);
    CHECK(result.code == 3);
    CHECK(result.out.find("IntegrityFailurePreApply") != std::string::npos);
    CHECK(result.out.find("missing-repo-artifact") != std::string::npos);
  }
  SECTION("checksum mismatch") {
    const auto image = fixture.write(root, "bad.bvpk", true);
    const auto result = run_cmd("open '" + image.string() + "' --dest out --verify --json", root);
    CHECK(result.code == 3);
    CHECK(result.out.find("checksum") != std::string::npos);
    CHECK_FALSE(std::filesystem::exists(root / "out"));
  }
}

TEST_CASE("open repos offline drains without touching stage and lists zero-git pointers", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-offline");
  const ScopedEnv home{"HOME", root.string()};
  const auto image = build_repo_image(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  write_file(root / "out.bvpk-open.stage", "stage sentinel\n");
  // Named mutant: stage every repos/ member even when stage is nullopt.
  const auto result = run_cmd("open '" + image.string() + "' --dest out --offline --verify", root);
  INFO(result.out);
  INFO(result.err);
  REQUIRE(result.code == 0);
  CHECK(read_text(root / "out.bvpk-open.stage") == "stage sentinel\n");
  CHECK(read_text(root / "trace").empty());
  CHECK(read_text(root / "out/ignored.txt") == "ignored bytes\n");
  CHECK(std::filesystem::is_regular_file(root / "out/.biv/repos/r-main/repo.bundle"));
  CHECK(result.err.starts_with("open --offline: repositories were not restored (no git, no network)."));
  CHECK(result.err.find(". · main · ") != std::string::npos);
  CHECK(result.err.find(" · (no stored remote)\n") != std::string::npos);
  CHECK(result.err.find(".: git init --initial-branch='bvpk-restore'") != std::string::npos);
  CHECK(result.err.find("'HEAD'") == std::string::npos);
  CHECK(result.err.find("   (partial/manual reconstruction — not a full restore)\n") != std::string::npos);
  write_file(root / "online.bvpk-open.stage", "online sentinel\n");
  const auto control = run_cmd("open '" + image.string() + "' --dest online --network --json", root);
  CHECK(control.code == 3);
  CHECK(control.out.find("OpenPartialPresent") != std::string::npos);
  CHECK(control.out.find("online.bvpk-open.stage") != std::string::npos);
}

TEST_CASE("A10 network consent renders its exact one-shot notice with hostile URLs", "[open-repos][a10]") {
  biv::repo::RepoEntry invokes;
  invokes.relpath = "repo\nname";
  invokes.sha = std::string(40, 'a');
  invokes.branch = "main";
  invokes.head_state = biv::repo::HeadState::branch;
  invokes.capture_mode = biv::repo::CaptureMode::overlay;
  invokes.eligibility = biv::repo::Eligibility{};
  invokes.remotes = {{"origin", "https://example.invalid/a\r\xe2\x80\xae"}};
  biv::repo::RepoEntry no_git;
  no_git.relpath = "unborn";
  no_git.head_state = biv::repo::HeadState::unborn;

  const std::vector rows{invokes, no_git};
  const auto notice = biv::cli::render_network_consent(rows, true);
  CHECK(notice ==
        "Opening this image will run git to clone/fetch its repositories. This is git clone-grade trust — only open images you trust.\n"
        "  manifest/stored URLs (informational):\n"
        "    repo\\nname · https://example.invalid/a\\r\\u{202e}\n"
        "  git may contact ADDITIONAL URLs found in repo metadata (.gitmodules, nested submodules, or host git config) that Bivpak does not see or police.\n"
        "Run `biv open --offline` to open with zero network access — files + sessions only, repos listed for manual clone.\n"
        "Run git for these repositories? [y/N] ");
  CHECK(biv::cli::render_network_consent(rows, false) ==
        notice.substr(0, notice.size() - std::string_view{"Run git for these repositories? [y/N] "}.size()));
}

TEST_CASE("A10 noninteractive open declines before git while network flag consents", "[open-repos][a10]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("a10-network-decision");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-full", "repo");
  fixture.manifest.repos.front().remotes = {{"origin", "https://stored.invalid/repo"}};
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};

  const auto declined = run_cmd("open '" + image.string() + "' --dest declined --json", root);
  REQUIRE(declined.code == 0);
  CHECK(declined.err.empty());
  CHECK(read_text(root / "trace").empty());
  CHECK(std::filesystem::is_regular_file(root / "declined/.biv/repos/r-full/repo.bundle"));
  simdjson::dom::parser parser;
  auto document = parser.parse(declined.out);
  const simdjson::dom::array declined_rows = document["result"]["repos"];
  REQUIRE(declined_rows.size() == 1);
  CHECK(std::string_view(declined_rows.at(0)["outcome"]) == "offline-pointer");
  CHECK(std::string_view(declined_rows.at(0)["capture_mode"]) == "full");
  CHECK(std::string_view(declined_rows.at(0)["bundle_path"]) == ".biv/repos/r-full/repo.bundle");
  CHECK(std::string_view(declined_rows.at(0)["reconstruct"]).find("git clone") == std::string_view::npos);

  const auto consented = run_cmd("open '" + image.string() + "' --dest consented --network --json", root);
  REQUIRE(consented.code == 0);
  CHECK(consented.err == biv::cli::render_network_consent(fixture.manifest.repos, false));
  CHECK(consented.err.find("[y/N]") == std::string::npos);
  CHECK_FALSE(read_text(root / "trace").empty());
  document = parser.parse(consented.out);
  const simdjson::dom::array consented_rows = document["result"]["repos"];
  REQUIRE(consented_rows.size() == 1);
  CHECK(std::string_view(consented_rows.at(0)["outcome"]) == "restored");
  simdjson::dom::element absent;
  CHECK(consented_rows.at(0).at_key("bundle_path").get(absent) == simdjson::NO_SUCH_FIELD);
}

TEST_CASE("A10 interactive decision is rendered once before a consented git run", "[open-repos][a10][cli-pty]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("a10-interactive-network");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-full", "repo");
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};

  const auto result = run_cmd_pty_split(
      "open '" + image.string() + "' --dest out --json", root, "y\n");
  REQUIRE(result.code == 0);
  const auto notice = biv::cli::render_network_consent(fixture.manifest.repos, true);
  const auto notice_at = result.err.find(
      "Opening this image will run git to clone/fetch its repositories.");
  REQUIRE(notice_at != std::string::npos);
  CHECK(result.err.find("Run git for these repositories? [y/N] ") != std::string::npos);
  CHECK(result.err.find("Opening this image will run git", notice_at + 1) == std::string::npos);
  CHECK_FALSE(read_text(root / "trace").empty());
  simdjson::dom::parser parser;
  const auto document = parser.parse(result.out);
  CHECK(std::string_view(document["result"]["repos"].at(0)["outcome"]) == "restored");
  CHECK(notice.ends_with("Run git for these repositories? [y/N] "));
}

TEST_CASE("A10 reconstruct quotes copy-safe shell hazards and rejects display-active operands", "[open-repos][a10]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("a10-reconstruct-safety");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-safe", "repo $(touch SENTINEL) ' *");
  const auto image = fixture.write(root, "safe.bvpk");
  const auto safe = biv::open::open({.image = image, .dest = root / "safe-out", .verify = true, .offline = true});
  REQUIRE(safe);
  REQUIRE(safe->repos.size() == 1);
  REQUIRE(safe->repos[0].bundle_path);
  REQUIRE(safe->repos[0].reconstruct);
  CHECK(safe->repos[0].reconstruct->find("$(touch SENTINEL)") != std::string::npos);
  CHECK(safe->repos[0].reconstruct->find("'\\''") != std::string::npos);
  const auto shell_rc = std::system(safe->repos[0].reconstruct->c_str());
  REQUIRE(shell_rc != -1);
  CHECK(WIFEXITED(shell_rc));
  CHECK(WEXITSTATUS(shell_rc) == 0);
  CHECK_FALSE(std::filesystem::exists(root / "SENTINEL"));
  CHECK(run_git(git(), root / "safe-out" / fixture.manifest.repos[0].relpath,
                {"rev-parse", "HEAD"}) == *fixture.manifest.repos[0].sha + "\n");

  fixture.manifest.repos[0].relpath = "unsafe\n\xe2\x80\xaerepo";
  const auto unsafe_image = fixture.write(root, "unsafe.bvpk");
  const auto unsafe = biv::open::open(
      {.image = unsafe_image, .dest = root / "unsafe-out", .verify = true, .offline = true});
  REQUIRE(unsafe);
  REQUIRE(unsafe->repos.size() == 1);
  REQUIRE(unsafe->repos[0].bundle_path);
  CHECK_FALSE(unsafe->repos[0].reconstruct);
  const auto absolute_bundle =
      (std::filesystem::path{unsafe->output_dir} / *unsafe->repos[0].bundle_path).generic_string();
  const auto fallback = biv::cli::render_offline_bundle_row({.relpath = unsafe->repos[0].relpath,
                                                             .absolute_bundle_path = absolute_bundle,
                                                             .reconstruct = unsafe->repos[0].reconstruct});
  CHECK(fallback.find("unsafe\\n\\u{202e}repo: bundle at ") == 0);
  CHECK(fallback.find("no copy-paste command") != std::string::npos);
  CHECK(fallback.find("git init") == std::string::npos);
}

TEST_CASE("A10 durable bundle refuses a payload symlink at its private parent", "[open-repos][a10]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("a10-bundle-containment");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-full", "repo");
  fixture.payload.push_back({
      {.path = "payload/.biv", .kind = biv::scan::NodeKind::symlink, .mode = 0777,
       .mtime_s = 1, .mtime_ns = 0, .size = 0,
       .symlink_target = (root / "outside").string()},
      {}});
  const auto image = fixture.write(root);
  const auto opened = biv::open::open(
      {.image = image, .dest = root / "out", .offline = true});
  REQUIRE_FALSE(opened);
  CHECK(opened.error().kind == biv::ErrKind::MemberPathUnsafe);
  CHECK(opened.error().detail == "repo-artifact-parent");
  CHECK_FALSE(std::filesystem::exists(root / "outside"));
  CHECK_FALSE(std::filesystem::exists(root / "out"));
}

TEST_CASE("open repos typed refusal continues in encounter order to a clean entry", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-refusal");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-clean", "clean");
  auto refused = fixture.manifest.repos.front();
  refused.capture_mode = biv::repo::CaptureMode::overlay;
  refused.bundle.reset();
  refused.local_refs_bundle.reset();
  refused.local_refs.clear();
  refused.remote = "origin";
  refused.remotes = {{"origin", "https://requested.invalid/repo"}};
  refused.eligibility = biv::repo::Eligibility{
      .method = "ls-remote-ancestry",
      .result = biv::repo::EligibilityResult::proven,
      .checked_at = "2026-09-19T00:00:00Z",
      .proof = biv::repo::Proof{"origin", "https://requested.invalid/repo", "refs/heads/main", *refused.sha}};
  refused.id = "r-refused-one";
  refused.relpath = "refused-one";
  fixture.manifest.repos.insert(fixture.manifest.repos.begin(), refused);
  refused.id = "r-refused-two";
  refused.relpath = "refused-two";
  fixture.manifest.repos.insert(fixture.manifest.repos.begin() + 1, refused);
  const auto image = fixture.write(root);
  write_file(root / ".gitconfig", "[url \"https://effective.invalid/\"]\n\tinsteadOf = https://requested.invalid/\n");
  // Restore deliberately sets GIT_CONFIG_GLOBAL=/dev/null. At this engine pin,
  // inject only the URL-resolution result; all other calls execute real Git.
  install_trace(root, true);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  // Named mutant: compare the wire kind to url_divergence_refused (underscores).
  const auto result = run_cmd("open '" + image.string() + "' --dest out --network --json", root);
  INFO(result.out);
  REQUIRE(result.code == 2);
  simdjson::dom::parser parser;
  const auto document = parser.parse(result.out);
  CHECK(document["error"].is_null());
  const simdjson::dom::array refusals = document["result"]["url_divergence_refusals"];
  REQUIRE(refusals.size() == 2);
  CHECK(std::string_view(refusals.at(0)["relpath"]) == "refused-one");
  CHECK(std::string_view(refusals.at(1)["relpath"]) == "refused-two");
  CHECK(std::string_view(refusals.at(0)["kind"]) == "UrlDivergenceEntryRefused");
  const simdjson::dom::array repos = document["result"]["repos"];
  REQUIRE(repos.size() == 3);
  const auto expected_detail = [](const std::string_view relpath) {
    return std::string{relpath} +
           ": restore failed — clone would contact https://effective.invalid/repo "
           "instead of the requested https://requested.invalid/repo; approval was not given.";
  };
  for (std::size_t index = 0; index < 2; ++index) {
    const auto row = repos.at(index);
    CHECK(std::string_view{row["outcome"]} == "failed");
    CHECK(std::string_view{row["kind"]} == "UrlDivergenceEntryRefused");
    const auto detail = std::string_view{row["detail"]};
    const auto relpath = index == 0 ? std::string_view{"refused-one"}
                                    : std::string_view{"refused-two"};
    CHECK(detail == expected_detail(relpath));
    CHECK(result.err.find("  " + std::string{detail} + "\n") != std::string::npos);
  }
  {
    std::ofstream output{BIV_DIVERGENCE_ENVELOPE_PATH,
                         std::ios::binary | std::ios::trunc};
    REQUIRE(output);
    output << result.out;
    output.close();
    REQUIRE(output);
  }
  const auto trace = read_text(root / "trace");
  const std::string request = "\tls-remote\t--get-url\t--\thttps://requested.invalid/repo";
  const auto first_request = trace.find(request);
  REQUIRE(first_request != std::string::npos);
  const auto second_request = trace.find(request, first_request + 1);
  REQUIRE(second_request != std::string::npos);
  CHECK(trace.find(request, second_request + 1) == std::string::npos);
  CHECK(trace.find("\tclone\t--no-checkout\t--\thttps://requested.invalid/repo") == std::string::npos);
  CHECK(run_git(git(), root / "out/clean", {"rev-parse", "HEAD"}) == *refused.sha + "\n");
  CHECK_FALSE(std::filesystem::exists(root / "out.bvpk-open.stage"));
  const auto report = biv::open::open({.image = image, .dest = root / "core"});
  REQUIRE(report);
  REQUIRE(report->repos.size() == 3);
  CHECK(report->repos[0].outcome == "failed");
  CHECK(report->repos[1].outcome == "failed");
  CHECK(report->repos[2].outcome == "restored");
  REQUIRE(report->url_divergence_refusals.size() == 2);
  CHECK(report->url_divergence_refusals[0].repo_id == "r-refused-one");
  CHECK(report->url_divergence_refusals[1].repo_id == "r-refused-two");
}

TEST_CASE("open repos synthetic child-first manifest restores parents once before children", "[open-repos]") {
  // provenance=hand-built, registered-T-ARM: not re-executed by Task 7.
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-topology");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-child", "parent/child");
  fixture.capture_repo(root, "r-parent", "parent");
  fixture.manifest.repos.front().parent_id = "r-parent";
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  const auto result = biv::open::open({.image = image, .dest = root / "out", .verify = true});
  if (!result) INFO(result.error().detail);
  REQUIRE(result);
  REQUIRE(result->repos.size() == 2);
  CHECK(result->repos[0].id == "r-parent");
  CHECK(result->repos[1].id == "r-child");
  CHECK(result->repos[0].outcome == "restored");
  CHECK(result->repos[1].outcome == "restored");
  const auto trace = read_text(root / "trace");
  const auto canonical_root = std::filesystem::canonical(root);
  const auto parent = trace.find("\tclone\t--no-checkout\t--\t" + (canonical_root / "out.bvpk-open.stage/repos/r-parent/repo.bundle").string());
  const auto child = trace.find("\tclone\t--no-checkout\t--\t" + (canonical_root / "out.bvpk-open.stage/repos/r-child/repo.bundle").string());
  REQUIRE(parent != std::string::npos);
  REQUIRE(child != std::string::npos);
  CHECK(parent < child);
  CHECK(trace.find("\tclone\t", parent + 1) == child);
  CHECK(trace.find("\tclone\t", child + 1) == std::string::npos);
  CHECK(run_git(git(), root / "out/parent", {"rev-parse", "HEAD"}) == *fixture.manifest.repos[1].sha + "\n");
  CHECK(run_git(git(), root / "out/parent/child", {"rev-parse", "HEAD"}) == *fixture.manifest.repos[0].sha + "\n");
}

TEST_CASE("open repos offline preserves structural engine rows field for field with zero git", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-structural");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-born", "born");
  auto shallow = fixture.manifest.repos.front();
  shallow.id = "r-shallow";
  shallow.relpath = "shallow";
  shallow.bundle.reset();
  shallow.local_refs_bundle.reset();
  shallow.local_refs.clear();
  shallow.eligibility.reset();
  shallow.shallow = biv::repo::Shallow{{*shallow.sha}};
  auto unborn = shallow;
  unborn.id = "r-unborn";
  unborn.relpath = "unborn";
  unborn.shallow.reset();
  unborn.sha.reset();
  unborn.head_state = biv::repo::HeadState::unborn;
  fixture.manifest.repos = {shallow, unborn};
  fixture.artifacts.clear();
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  const auto online = biv::open::open({.image = image, .dest = root / "online"});
  REQUIRE(online);
  write_file(root / "offline.bvpk-open.stage", "untouched");
  const auto offline = biv::open::open({.image = image, .dest = root / "offline", .offline = true});
  REQUIRE(offline);
  REQUIRE(online->repos.size() == 2);
  REQUIRE(offline->repos.size() == 2);
  CHECK(offline->repos[0].outcome == "shallow-pointer");
  CHECK(offline->repos[0].sha == shallow.sha);
  CHECK(offline->repos[0].shallow_boundary == shallow.shallow->boundary);
  CHECK(offline->repos[1].outcome == "payload-only-unborn");
  CHECK_FALSE(offline->repos[1].sha);
  CHECK(offline->repos[1].advisories == std::vector<std::string>{"EmptyRepoPayloadOnly"});
  for (size_t index = 0; index < 2; ++index) {
    const auto& a = online->repos[index];
    const auto& b = offline->repos[index];
    CHECK(a.id == b.id);
    CHECK(a.relpath == b.relpath);
    CHECK(a.outcome == b.outcome);
    CHECK(a.sha == b.sha);
    CHECK(a.branch == b.branch);
    CHECK(a.capture_mode == b.capture_mode);
    CHECK(a.remotes == b.remotes);
    CHECK(a.local_refs.empty());
    CHECK(b.local_refs.empty());
    CHECK(a.advisories == b.advisories);
    CHECK(a.shallow_boundary == b.shallow_boundary);
  }
  CHECK(read_text(root / "trace").empty());
  CHECK(read_text(root / "offline.bvpk-open.stage") == "untouched");
  const auto cli = run_cmd("open '" + image.string() + "' --dest cli --offline", root);
  CHECK(cli.code == 0);
  // Named mutant: gating the header on any offline-pointer omits it for structural-only rows.
  CHECK(cli.err ==
        "open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.\n");
}

TEST_CASE("open repos zero state omits rows listing and stage access", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-zero");
  Image fixture;
  fixture.payload.push_back(Image::member("payload/plain.txt", "plain"));
  const auto image = fixture.write(root);
  write_file(root / "out.bvpk-open.stage", "untouched");
  const auto result = biv::open::open({.image = image, .dest = root / "out"});
  REQUIRE(result);
  CHECK(result->repos.empty());
  CHECK(result->url_divergence_refusals.empty());
  CHECK(read_text(root / "out.bvpk-open.stage") == "untouched");
  const auto cli = run_cmd("open '" + image.string() + "' --dest cli --offline", root);
  CHECK(cli.code == 0);
  CHECK(cli.err.find("open --offline:") == std::string::npos);
  CHECK(read_text(root / "cli/plain.txt") == "plain");
}

TEST_CASE("open repos removes its stage on checksum and restore failures", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-cleanup");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-one", "repo");
  SECTION("archive changed after plan online and offline") {
    for (const bool offline : {false, true}) {
      const auto dest = root / (offline ? "offline" : "online");
      const auto image = fixture.write(root);
      auto plan = biv::open::plan_open({.image = image, .dest = dest, .verify = true, .offline = offline});
      REQUIRE(plan);
      fixture.artifacts.front().data.front() ^= std::byte{1};
      fixture.write(root);
      const auto result = biv::open::execute_open(std::move(*plan), {});
      REQUIRE_FALSE(result);
      CHECK(result.error().kind == biv::ErrKind::IntegrityFailureMidApply);
      CHECK(result.error().detail == "checksum");
      CHECK(result.error().facts.at("partial_dir") == dest.string() + ".bvpk-open.partial");
      CHECK_FALSE(std::filesystem::exists(dest));
      CHECK_FALSE(std::filesystem::exists(dest.string() + ".bvpk-open.stage"));
      fixture.artifacts.front().data.front() ^= std::byte{1};
    }
  }
  SECTION("engine failure stays a whole operation error") {
    fixture.artifacts.front().data.front() ^= std::byte{1};
    const auto image = fixture.write(root);
    const auto result = biv::open::open({.image = image, .dest = root / "out", .verify = true});
    REQUIRE_FALSE(result);
    CHECK(result.error().facts.contains("partial_dir"));
    CHECK_FALSE(std::filesystem::exists(root / "out"));
    CHECK_FALSE(std::filesystem::exists(root / "out.bvpk-open.stage"));
  }
}

TEST_CASE("open repos offline renderers use sealed A9.4 text and display-safe values", "[open-repos]") {
  CHECK(biv::cli::render_offline_header() ==
        "open --offline: repositories were not restored (no git, no network). Stored remote URLs below are informational — recorded at pack, not vetted or complete. Cloning them is git-clone-grade trust: git may contact those URLs and additional URLs from repo metadata (.gitmodules, nested submodules, host git config) that Bivpak does not see or police. Clone only what you trust.\n");
  CHECK(biv::cli::render_offline_row("a\nb", std::nullopt, "(no commits)", {}) ==
        "a\\nb · (detached) · (no commits) · (no stored remote)\n");
  CHECK(biv::cli::render_offline_row("repo", "branch\t", "sha\r", {"url\n", "other\t"}) ==
        "repo · branch\\t · sha\\r · url\\n, other\\t\n");
}

TEST_CASE("open repos stages an engine captured overlay local refs bundle at its full path", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-overlay");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-overlay", "overlay", false, true);
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  const auto offline = biv::open::open({.image = image, .dest = root / "offline", .verify = true, .offline = true});
  REQUIRE(offline);
  REQUIRE(offline->repos.size() == 1);
  CHECK(offline->repos[0].outcome == "offline-pointer");
  CHECK(offline->repos[0].capture_mode == "overlay");
  CHECK(offline->repos[0].sha == fixture.manifest.repos[0].sha);
  CHECK(offline->repos[0].branch == "main");
  CHECK(offline->repos[0].remotes == std::vector<std::string>{(root / "remote-r-overlay").string()});
  CHECK(read_text(root / "trace").empty());
  CHECK_FALSE(std::filesystem::exists(root / "offline/.biv"));
  const auto online = biv::open::open({.image = image, .dest = root / "online", .verify = true});
  if (!online) INFO(online.error().detail);
  REQUIRE(online);
  REQUIRE(online->repos.size() == 1);
  CHECK(online->repos[0].outcome == "restored");
  CHECK(read_text(root / "trace").find("online.bvpk-open.stage/repos/r-overlay/local-refs.bundle") != std::string::npos);
  CHECK(run_git(git(), root / "online/overlay", {"rev-parse", "local-topic"}) ==
        run_git(git(), root / "source-r-overlay", {"rev-parse", "local-topic"}));
  CHECK(run_git(git(), root / "online/overlay", {"status", "--porcelain=v2"}).empty());
  CHECK_FALSE(std::filesystem::exists(root / "online.bvpk-open.stage"));
}

TEST_CASE("open repos offline pointers retain manifest order detached and unborn HEAD values", "[open-repos]") {
  using namespace open_repos_fixture;
  const auto root = make_tmp("open-repos-pointer-heads");
  const ScopedEnv home{"HOME", root.string()};
  Image fixture;
  fixture.capture_repo(root, "r-detached", "detached");
  fixture.capture_repo(root, "r-unborn", "unborn");
  auto& detached = fixture.manifest.repos[0];
  detached.head_state = biv::repo::HeadState::detached;
  detached.branch.reset();
  detached.remotes = {{"one", "https://one.invalid/\r"}, {"two", "https://two.invalid/\xe2\x80\xae"}};
  auto& unborn = fixture.manifest.repos[1];
  unborn.head_state = biv::repo::HeadState::unborn;
  unborn.sha.reset();
  unborn.branch = "empty";
  REQUIRE(unborn.eligibility);
  unborn.eligibility->result = biv::repo::EligibilityResult::unborn_head;
  const auto image = fixture.write(root);
  install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" + std::getenv("PATH")};
  const auto report = biv::open::open({.image = image, .dest = root / "out", .verify = true, .offline = true});
  REQUIRE(report);
  REQUIRE(report->repos.size() == 2);
  CHECK(report->repos[0].id == "r-detached");
  CHECK(report->repos[0].outcome == "offline-pointer");
  CHECK(report->repos[0].sha == detached.sha);
  CHECK_FALSE(report->repos[0].branch);
  CHECK(report->repos[1].id == "r-unborn");
  CHECK(report->repos[1].outcome == "offline-pointer");
  CHECK(report->repos[1].sha == "(no commits)");
  CHECK(report->repos[1].branch == "empty");
  const auto cli = run_cmd("open '" + image.string() + "' --dest cli --offline", root);
  REQUIRE(cli.code == 0);
  const std::string lines = "detached · (detached) · " + *detached.sha +
      " · https://one.invalid/\\r, https://two.invalid/\\u{202e}\n"
      "unborn · empty · (no commits) · (no stored remote)\n";
  CHECK(cli.err.starts_with(biv::cli::render_offline_header() + lines));
  CHECK(cli.err.find("detached: git init --initial-branch='bvpk-restore'") != std::string::npos);
  CHECK(cli.err.find(" 'HEAD' '+refs/heads/*:refs/heads/*'") != std::string::npos);
  CHECK(cli.err.find("unborn: git init --initial-branch='empty'") != std::string::npos);
  CHECK(read_text(root / "trace").empty());
  const auto json = run_cmd("open '" + image.string() + "' --dest json --offline --json", root);
  REQUIRE(json.code == 0);
  CHECK(json.err.empty());
  simdjson::dom::parser parser;
  const simdjson::dom::element document = parser.parse(json.out);
  const simdjson::dom::array rows = document["result"]["repos"];
  REQUIRE(rows.size() == 2);
  CHECK(std::string_view(rows.at(0)["bundle_path"]) == ".biv/repos/r-detached/repo.bundle");
  CHECK(std::string_view(rows.at(0)["reconstruct"]).find(" 'HEAD' ") != std::string_view::npos);
  CHECK(std::string_view(rows.at(1)["sha"]) == "(no commits)");
  CHECK(simdjson::dom::array(document["result"]["manifest"]["repos"]).size() == 0);
}

TEST_CASE("a6.14 list/info accept the flag inert: full-stream equality with flagless", "[a6-fabric]") {
  const auto root = make_tmp("a6-14-inert");
  // FULL code/out/err equality for EACH verb — a mutant emitting any A6 surface on any
  // stream, or shifting the exit, REDs here (flag-specific: only this spelling compared).
  const auto list_flag = run_cmd("list --accept-url-divergence missing.bvpk", root);
  const auto list_none = run_cmd("list missing.bvpk", root);
  CHECK(list_flag.code == list_none.code);
  CHECK(list_flag.out == list_none.out);
  CHECK(list_flag.err == list_none.err);
  const auto info_flag = run_cmd("info --accept-url-divergence missing.bvpk", root);
  const auto info_none = run_cmd("info missing.bvpk", root);
  CHECK(info_flag.code == info_none.code);
  CHECK(info_flag.out == info_none.out);
  CHECK(info_flag.err == info_none.err);
  std::filesystem::remove_all(root);
}

TEST_CASE("a6.18 inherited no-help boundary witnessed on pack/list/info", "[a6-fabric]") {
  const auto root = make_tmp("a6-18-nohelp");
  // The sealed leg requires the OTHER verbs' help ABSENCE witnessed, not assumed.
  // The witness is help-is-not-special FULL-STREAM equality: for each verb, `--help`
  // must produce EXACTLY what any other unknown/ignored flag produces (code, stdout,
  // stderr) — a mutant emitting ANY help production on ANY stream for that verb
  // diverges from its own unknown-flag baseline and REDs here. Belt: no usage/help
  // text on either stream.
  const std::vector<std::pair<std::string, std::string>> probes{
      {"pack --help", "pack --no-such-flag"},          // pack rejects every flag alike
      {"list --help x.bvpk", "list --no-such-flag x.bvpk"},  // stubs ignore trailing tokens alike
      {"info --help x.bvpk", "info --no-such-flag x.bvpk"}};
  // EXACT stable baselines at the reviewed base (kills the shared-baseline mutant --
  // a help-like block emitted on BOTH flag paths cannot match these):
  //   all three verbs: exit code 5, EMPTY stdout;
  //   pack stderr  == "biv: UsageError: unknown-flag\n"
  //   list/info stderr == "biv: UsageError: NotYetImplemented\n"
  const std::map<std::string, std::string> expected_err{
      {"pack", "biv: UsageError: unknown-flag\n"},
      {"list", "biv: UsageError: NotYetImplemented\n"},
      {"info", "biv: UsageError: NotYetImplemented\n"}};
  for (const auto& [help_form, baseline_form] : probes) {
    const auto verb = help_form.substr(0, help_form.find(' '));
    const auto help = run_cmd(help_form, root);
    const auto baseline = run_cmd(baseline_form, root);
    INFO(help_form);
    CHECK(help.code == 5);
    CHECK(help.out.empty());
    CHECK(help.err == expected_err.at(verb));
    // belt: help gets NO special treatment vs any other unknown/ignored flag
    CHECK(help.code == baseline.code);
    CHECK(help.out == baseline.out);
    CHECK(help.err == baseline.err);
  }
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
    REQUIRE(stat_text.code == 2);
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
    REQUIRE(stat_json.code == 2);
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
  REQUIRE(invalid_json.code == 2);
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
  CHECK(deny_text.out.find("-> staged", deny_summary) != std::string::npos);
  CHECK(deny_text.out.find(
            "Staged sessions were not installed into host stores; inspect the workspace staging area before use.",
            deny_summary) != std::string::npos);

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

TEST_CASE("c3 offline and network flags parse only for their supported verbs", "[cli-flags]") {
  for (const std::string verb : {"pack", "open"}) {
    std::vector<std::string> words{"biv", verb, "--offline", "source"};
    std::vector<char*> argv;
    for (auto& word : words) argv.push_back(word.data());
    const auto parsed = biv::cli::parse_args(argv);
    INFO(verb);
    INFO((parsed ? "parsed" : parsed.error().detail));
    REQUIRE(parsed.has_value());
    CHECK(parsed->offline);
    CHECK_FALSE(parsed->network);
  }
  char prog[] = "biv", verb[] = "open", flag[] = "--network", image[] = "image.bvpk";
  char* argv[] = {prog, verb, flag, image};
  const auto parsed = biv::cli::parse_args(argv);
  REQUIRE(parsed.has_value());
  CHECK(parsed->network);
  CHECK_FALSE(parsed->offline);
}

TEST_CASE("c3 conflicting flags and pack network are usage errors", "[cli-flags]") {
  const auto root = make_tmp("c3-conflicting-flags");
  for (const std::string flags : {"--offline --network", "--network --offline"}) {
    const auto result = run_cmd("open " + flags + " missing.bvpk --json", root);
    CHECK(result.code == 5);
    simdjson::dom::parser parser;
    simdjson::dom::element document;
    REQUIRE(parser.parse(result.out).get(document) == simdjson::SUCCESS);
    std::string_view kind, detail;
    REQUIRE(document["error"]["kind"].get(kind) == simdjson::SUCCESS);
    REQUIRE(document["error"]["detail"].get(detail) == simdjson::SUCCESS);
    CHECK(kind == "UsageError");
    CHECK(detail == "conflicting-flags");
    CHECK(result.err.empty());
  }
  const auto pack = run_cmd("pack --network source", root);
  CHECK(pack.code == 5);
  CHECK(pack.out.empty());
  CHECK(pack.err == "biv: UsageError: unknown-flag\n");
  std::filesystem::remove_all(root);
}

TEST_CASE("c3 list and info ignore offline and network with exact stream parity", "[cli-flags]") {
  const auto root = make_tmp("c3-stub-flags");
  for (const std::string verb : {"list", "info"}) {
    for (const std::string json : {"", " --json"}) {
      const auto baseline = run_cmd(verb + json, root);
      for (const std::string flag : {" --offline", " --network"}) {
        const auto result = run_cmd(verb + flag + json, root);
        CHECK(result.code == baseline.code);
        CHECK(result.out == baseline.out);
        CHECK(result.err == baseline.err);
      }
    }
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("c3 split PTY captures distinct streams and child TTY facts", "[cli-flags][cli-pty]") {
  const auto root = make_tmp("c3-split-pty");
  const std::string command = "sh -c 'test -t 0; echo $?; test -t 1; echo $?; test -t 2; echo $?'";
  const auto split = run_shell_pty_topology(command, root, "", true);
  CHECK(split.code == 0);
  CHECK(split.out == "0\n1\n0\n");
  CHECK(split.err.empty());
  CHECK(split.stdin_tty);
  CHECK_FALSE(split.stdout_tty);
  CHECK(split.stderr_tty);
  const auto merged = run_shell_pty_topology(command, root, "", false);
  CHECK(merged.code == 0);
  CHECK(merged.out.empty());
  CHECK(merged.err == "0\r\n0\r\n0\r\n");
  CHECK(merged.stdin_tty);
  CHECK(merged.stdout_tty);
  CHECK(merged.stderr_tty);
  const auto separated = run_shell_pty_topology("printf stdout; printf stderr >&2", root, "", true);
  CHECK(separated.out == "stdout");
  CHECK(separated.err == "stderr");
  const auto cli = run_cmd_pty_split("open --help", root, "");
  CHECK(cli.code == 0);
  CHECK(cli.out == run_cmd("open --help", root).out);
  CHECK(cli.err.empty());
  CHECK(cli.stdin_tty);
  CHECK_FALSE(cli.stdout_tty);
  CHECK(cli.stderr_tty);
  std::filesystem::remove_all(root);
}

TEST_CASE("c3 hook installer obeys preapproval and absent noninteractive hook", "[cli-flags][cli-hook]") {
  REQUIRE_FALSE(biv::cli::interactive_url_hook_installable());
  biv::cli::Command parsed;
  CHECK_FALSE(install_url_divergence_hook(parsed).run.hook);
  parsed.json = true;
  parsed.offline = true;
  CHECK_FALSE(install_url_divergence_hook(parsed).run.hook);
  parsed.offline = false;
  parsed.network = true;
  CHECK_FALSE(install_url_divergence_hook(parsed).run.hook);
  parsed.accept_url_divergence = true;
  auto consent = install_url_divergence_hook(parsed);
  REQUIRE(consent.run.hook);
  std::ostringstream captured;
  struct RestoreBuffer {
    std::streambuf* previous;
    ~RestoreBuffer() { std::cerr.rdbuf(previous); }
  } restore{std::cerr.rdbuf(captured.rdbuf())};
  // Called outside any assertion: a redirecting reporter (-r xml) re-points
  // std::cerr at each assertion boundary, which would bypass `captured`.
  const auto decision = consent.run.hook({"https://req", "https://eff", "fetch", "/w/repo"});
  CHECK(decision == biv::repo::UrlDivergenceDecision::proceed);
  CHECK(captured.str() ==
        "  fetch: contacting https://eff for /w/repo (requested: https://req — accepted for this run)\n");
}

TEST_CASE("c3 refusal writer preserves entry order and emits one run guidance", "[cli-flags][cli-hook]") {
  std::ostringstream err;
  emit_entry_refusals({}, err);
  CHECK(err.str().empty());
  emit_entry_refusals({{"repo-z", "z/file", "https://q1", "https://e1", "fetch"},
                       {"repo-a", "a/file", "https://q2", "https://e2", "clone"}}, err);
  CHECK(err.str() ==
        "  z/file: restore failed — fetch would contact https://e1 instead of the requested https://q1; approval was not given.\n"
        "  a/file: restore failed — clone would contact https://e2 instead of the requested https://q2; approval was not given.\n"
        "  open: 2 restore entry(ies) refused — the effective address was not approved. Re-run interactively to review, or pass --accept-url-divergence to proceed.\n");
  ConsentRun consent;
  consent.run.accepted.push_back({"https://q", "https://e", "fetch", "/w/repo"});
  std::vector<biv::UrlDivergenceAcceptedEntry> accepted;
  record_accepted(consent, accepted);
  REQUIRE(accepted.size() == 1);
  CHECK(accepted[0].requested == "https://q");
  CHECK(accepted[0].effective == "https://e");
  CHECK(accepted[0].op == "fetch");
  CHECK(accepted[0].repo == "/w/repo");
}

TEST_CASE("A11 engine errors render the locked sentences and hostile diagnostic slots", "[a11]") {
  std::map<std::string, std::string> facts{{"repo_relpath", "repo\r\xe2\x80\xae"},
                                           {"op", "fetch"},
                                           {"exit_code", "9"}};
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::RepoDirtyUnsupported, facts) ==
        "pack refused: repo\\r\\u{202e} has uncommitted changes; this build captures clean repositories only. Commit or stash the changes, or declare the path in .bivignore, and re-run.");
  facts["child"] = "child";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::RepoNestedUnsupported, facts).find("nested repository at child") != std::string::npos);
  facts["gitlink"] = "sub";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::RepoSubmoduleUnsupported, facts).find("submodule at sub") != std::string::npos);
  facts["unmerged_count"] = "4";
  facts["unmerged_paths"] = "a\nb\nc\nd";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::UnmergedIndexUnrepresentable, facts).find("a, b, c and 1 more") != std::string::npos);
  facts["ref"] = "refs/heads/local";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::RefUncapturable, facts).find("refs/heads/local") != std::string::npos);
  facts["offline"] = "true";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::PromisorObjectsUnavailable, facts).find(", offline") != std::string::npos);
  facts["verb"] = "open";
  facts["engine_detail"] = "fatal: hostile\r\xe2\x80\xae";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::GitInvocationFailed, facts).find("fatal: hostile\\r\\u{202e}") != std::string::npos);
  facts.erase("op");
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::GitBudgetExpired, facts).find("git call") != std::string::npos);
  facts["engine_detail"] = "RepoRestoreFailed: checkout: bad";
  CHECK(biv::cli::render_engine_refusal_detail(biv::ErrKind::RepoRestoreFailed, facts).find("checkout: bad") != std::string::npos);
}

TEST_CASE("c6m a payload directory above a restored repository keeps its archived mtime", "[cli][c6m]") {
  const auto root = make_tmp("c6m-directory-mtime");
  const auto workspace = root / "workspace";
  const auto docs = workspace / "docs";
  const auto inner = docs / "inner";
  std::filesystem::create_directories(inner);
  write_file(workspace / "README.md", "root\n");
  write_file(docs / "notes.txt", "notes\n");
  const auto handle = open_repos_fixture::git();
  open_repos_fixture::run_git(handle, inner, {"init", "-b", "main"});
  write_file(inner / "sub" / "t.txt", "tracked\n");
  open_repos_fixture::run_git(handle, inner, {"add", "."});
  open_repos_fixture::run_git(handle, inner,
                              {"-c", "user.name=Biv Test", "-c",
                               "user.email=biv@example.invalid", "commit", "-m", "initial"});
  const timespec archived[2]{{1577836800, 123456789}, {1577836800, 123456789}};
  for (const auto& path : {workspace / "README.md", docs / "notes.txt",
                           inner / "sub" / "t.txt", inner / "sub", inner, docs, workspace}) {
    REQUIRE(::utimensat(AT_FDCWD, path.c_str(), archived, AT_SYMLINK_NOFOLLOW) == 0);
  }
  const auto mtime = [](const std::filesystem::path& path) {
    struct stat status{};
    REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
    return std::pair{status.st_mtimespec.tv_sec, status.st_mtimespec.tv_nsec};
#else
    return std::pair{status.st_mtim.tv_sec, status.st_mtim.tv_nsec};
#endif
  };
  const auto docs_mtime = mtime(docs);
  const auto notes_mtime = mtime(docs / "notes.txt");
  const auto packed = run_cmd("pack '" + workspace.string() + "' --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);

  const auto run_leg = [&](const std::string& leg, const std::string& flag) {
    const auto dest = root / leg;
    const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                    "' --dest '" + dest.string() + "' " + flag + " --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 0);
    const auto restored_docs_mtime = mtime(dest / "docs");
    const auto restored_notes_mtime = mtime(dest / "docs" / "notes.txt");
    INFO("docs expected=" << docs_mtime.first << "." << docs_mtime.second
                           << " actual=" << restored_docs_mtime.first << "."
                           << restored_docs_mtime.second);
    INFO("notes expected=" << notes_mtime.first << "." << notes_mtime.second
                            << " actual=" << restored_notes_mtime.first << "."
                            << restored_notes_mtime.second);
    CHECK(restored_docs_mtime == docs_mtime);
    CHECK(restored_notes_mtime == notes_mtime);
    if (leg == "network") {
      CHECK(open_repos_fixture::run_git(handle, dest / "docs" / "inner",
                                        {"status", "--porcelain=v2"}).empty());
    }
    if (const char* receipts = std::getenv("BIV_LEG_RECEIPTS")) {
      std::ofstream out{receipts, std::ios::app};
      out << "leg=c6m-" << leg << " provenance=product-packed\n";
    }
  };
  run_leg("network", "--network");
  run_leg("offline", "--offline");
  std::filesystem::remove_all(root);
}

TEST_CASE("c6q payload-only repository trees round trip without git",
          "[cli][c6q]") {
  const auto handle = open_repos_fixture::git();
  const auto make_remote = [&](const std::filesystem::path& root) {
    const auto remote = root / "remote.git";
    const auto seed = root / "seed";
    std::filesystem::create_directories(remote);
    std::filesystem::create_directories(seed);
    open_repos_fixture::run_git(handle, remote,
                                 {"init", "--bare", "--initial-branch=main"});
    open_repos_fixture::run_git(handle, seed, {"init", "-b", "main"});
    write_file(seed / ".gitignore", "*.log\n");
    write_file(seed / "sub/t.txt", "one\n");
    write_file(seed / "b.txt", "first\n");
    open_repos_fixture::run_git(handle, seed, {"add", "."});
    open_repos_fixture::run_git(
        handle, seed,
        {"-c", "user.name=Biv Test", "-c",
         "user.email=biv@example.invalid", "commit", "-m", "one"});
    write_file(seed / "b.txt", "second\n");
    open_repos_fixture::run_git(handle, seed, {"add", "b.txt"});
    open_repos_fixture::run_git(
        handle, seed,
        {"-c", "user.name=Biv Test", "-c",
         "user.email=biv@example.invalid", "commit", "-m", "two"});
    open_repos_fixture::run_git(handle, seed,
                                 {"remote", "add", "origin", remote.string()});
    open_repos_fixture::run_git(handle, seed, {"push", "origin", "main"});
    return remote;
  };
  const auto clone_shallow = [&](const std::filesystem::path& root,
                                 const std::filesystem::path& remote,
                                 const std::filesystem::path& dest) {
    open_repos_fixture::run_git(
        handle, root,
        {"clone", "--depth", "1", "file://" + remote.generic_string(),
         dest.generic_string()});
  };
  const auto stat_pair = [](const std::filesystem::path& path) {
    struct stat status{};
    REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
    return std::pair{std::pair{status.st_mtimespec.tv_sec,
                               status.st_mtimespec.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#else
    return std::pair{std::pair{status.st_mtim.tv_sec, status.st_mtim.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#endif
  };
  const auto assert_tree = [&](const std::filesystem::path& source,
                               const std::filesystem::path& dest,
                               const std::vector<std::string>& relpaths) {
    for (const auto& relpath : relpaths) {
      const auto from = source / relpath;
      const auto to = dest / relpath;
      INFO(relpath);
      CHECK(stat_pair(to) == stat_pair(from));
      if (std::filesystem::is_regular_file(from)) {
        CHECK(read_text(to) == read_text(from));
      }
    }
  };
  const auto assert_json = [](const std::string& output,
                              const std::map<std::string, std::string>& outcomes,
                              const int64_t restored_members) {
    simdjson::dom::parser parser;
    const simdjson::dom::element document = parser.parse(output);
    CHECK(int64_t(document["result"]["restored_member_count"]) ==
          restored_members);
    const simdjson::dom::array rows = document["result"]["repos"];
    REQUIRE(rows.size() == outcomes.size());
    for (const auto row : rows) {
      const std::string rel{std::string_view(row["relpath"])};
      REQUIRE(outcomes.contains(rel));
      CHECK(std::string_view(row["outcome"]) == outcomes.at(rel));
    }
  };

  SECTION("non-root shallow and unborn rows") {
    const auto root = make_tmp("c6q-nonroot");
    const auto workspace = root / "workspace";
    const auto remote = make_remote(root);
    write_file(workspace / "README.md", "root\n");
    clone_shallow(root, remote, workspace / "shal");
    write_file(workspace / "shal/x.log", "ignored bytes\n");
    std::filesystem::create_directories(workspace / "fresh");
    open_repos_fixture::run_git(handle, workspace / "fresh",
                                 {"init", "-b", "main"});
    write_file(workspace / "fresh/sub/f.txt", "fresh\n");
    const auto packed = run_cmd("pack '" + workspace.string() +
                                    "' --offline --json",
                                root);
    INFO(packed.out);
    INFO(packed.err);
    REQUIRE(packed.code == 0);
    open_repos_fixture::install_trace(root);
    const ScopedEnv path{"PATH", (root / "bin").string() + ":" +
                                     std::getenv("PATH")};
    const std::vector<std::string> shal{
        "shal", "shal/.gitignore", "shal/b.txt", "shal/sub",
        "shal/sub/t.txt", "shal/x.log"};
    const std::vector<std::string> fresh{
        "fresh", "fresh/sub", "fresh/sub/f.txt"};
    for (const auto& [name, flag] :
         std::array<std::pair<std::string, std::string>, 2>{{
             {"online", ""}, {"offline", "--offline"}}}) {
      write_file(root / "trace", "");
      const auto dest = root / name;
      const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                      "' --dest '" + dest.string() + "' " +
                                      flag + " --json",
                                  root);
      INFO(opened.out);
      INFO(opened.err);
      REQUIRE(opened.code == 0);
      assert_tree(workspace, dest, shal);
      assert_tree(workspace, dest, fresh);
      CHECK_FALSE(std::filesystem::exists(dest / "shal/.git"));
      CHECK_FALSE(std::filesystem::exists(dest / "fresh/.git"));
      CHECK(read_text(root / "trace").empty());
      assert_json(opened.out,
                  {{"shal", "shallow-pointer"},
                   {"fresh", "payload-only-unborn"}},
                  10);
      if (const char* receipts = std::getenv("BIV_LEG_RECEIPTS")) {
        std::ofstream out{receipts, std::ios::app};
        out << "leg=c6q-" << name << " provenance=product-packed\n";
      }
    }
    std::filesystem::remove_all(root);
  }

  SECTION("root shallow row") {
    const auto root = make_tmp("c6q-root-shallow");
    const auto remote = make_remote(root);
    const auto workspace = root / "workspace";
    clone_shallow(root, remote, workspace);
    write_file(workspace / "x.log", "ignored bytes\n");
    write_file(workspace / "extra.txt", "extra\n");
    const auto packed = run_cmd("pack '" + workspace.string() +
                                    "' --offline --json",
                                root);
    REQUIRE(packed.code == 0);
    open_repos_fixture::install_trace(root);
    const ScopedEnv path{"PATH", (root / "bin").string() + ":" +
                                     std::getenv("PATH")};
    const std::vector<std::string> expected{
        ".gitignore", "b.txt", "extra.txt", "sub", "sub/t.txt", "x.log"};
    for (const auto& [name, flag] :
         std::array<std::pair<std::string, std::string>, 2>{{
             {"online", ""}, {"offline", "--offline"}}}) {
      write_file(root / "trace", "");
      const auto dest = root / ("dest-" + name);
      const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                      "' --dest '" + dest.string() + "' " +
                                      flag + " --json",
                                  root);
      REQUIRE(opened.code == 0);
      assert_tree(workspace, dest, expected);
      CHECK_FALSE(std::filesystem::exists(dest / ".git"));
      CHECK(read_text(root / "trace").empty());
      assert_json(opened.out, {{".", "shallow-pointer"}}, 6);
    }
    std::filesystem::remove_all(root);
  }

  SECTION("root unborn row") {
    const auto root = make_tmp("c6q-root-unborn");
    const auto workspace = root / "workspace";
    std::filesystem::create_directories(workspace);
    open_repos_fixture::run_git(handle, workspace, {"init", "-b", "main"});
    write_file(workspace / "sub/f.txt", "fresh\n");
    const auto packed = run_cmd("pack '" + workspace.string() +
                                    "' --offline --json",
                                root);
    REQUIRE(packed.code == 0);
    open_repos_fixture::install_trace(root);
    const ScopedEnv path{"PATH", (root / "bin").string() + ":" +
                                     std::getenv("PATH")};
    const std::vector<std::string> expected{"sub", "sub/f.txt"};
    for (const auto& [name, flag] :
         std::array<std::pair<std::string, std::string>, 2>{{
             {"online", ""}, {"offline", "--offline"}}}) {
      write_file(root / "trace", "");
      const auto dest = root / ("dest-" + name);
      const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                      "' --dest '" + dest.string() + "' " +
                                      flag + " --json",
                                  root);
      REQUIRE(opened.code == 0);
      assert_tree(workspace, dest, expected);
      CHECK_FALSE(std::filesystem::exists(dest / ".git"));
      CHECK(read_text(root / "trace").empty());
      assert_json(opened.out, {{".", "payload-only-unborn"}}, 2);
    }
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("c6p repository penumbra is placed after its row outcome",
          "[cli][c6p]") {
  const auto root = make_tmp("c6p-penumbra-placement");
  const auto workspace = root / "workspace";
  const auto repo = workspace / "lib";
  write_file(workspace / "README.md", "root\n");
  const auto handle = open_repos_fixture::git();
  std::filesystem::create_directories(repo);
  open_repos_fixture::run_git(handle, repo, {"init", "-b", "main"});
  write_file(repo / ".gitignore", "ign/\n*.log\n");
  write_file(repo / "sub/t.txt", "tracked\n");
  open_repos_fixture::run_git(handle, repo,
                              {"add", ".gitignore", "sub/t.txt"});
  open_repos_fixture::run_git(handle, repo,
                              {"-c", "user.name=Biv Test", "-c",
                               "user.email=biv@example.invalid", "commit",
                               "-m", "base"});
  write_file(repo / "ign/penumbra.txt", "one\n");
  write_file(repo / "ign/deep/d.txt", "two\n");
  write_file(repo / "sub/x.log", "three\n");
  REQUIRE(open_repos_fixture::run_git(handle, repo,
                                      {"status", "--porcelain=v2"}).empty());

  const auto packed = run_cmd(
      "pack '" + workspace.string() + "' --offline --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  const auto image = root / "workspace.bvpk";
  open_repos_fixture::install_trace(root);
  const ScopedEnv path{"PATH", (root / "bin").string() + ":" +
                                   std::getenv("PATH")};
  const auto stat_pair = [](const std::filesystem::path& path) {
    struct stat status{};
    REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
    return std::pair{std::pair{status.st_mtimespec.tv_sec,
                               status.st_mtimespec.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#else
    return std::pair{std::pair{status.st_mtim.tv_sec, status.st_mtim.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#endif
  };
  const auto assert_fidelity = [&](const std::filesystem::path& dest,
                                   const std::string& relative) {
    const auto original = repo / relative;
    const auto restored = dest / "lib" / relative;
    CHECK(read_text(restored) == read_text(original));
    CHECK(stat_pair(restored) == stat_pair(original));
  };
  const auto run_leg = [&](const std::string& leg, const std::string& flag) {
    write_file(root / "trace", "");
    const auto dest = root / leg;
    const auto opened = run_cmd("open '" + image.string() + "' --dest '" +
                                    dest.string() + "' " + flag + " --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 0);
    assert_fidelity(dest, "ign/penumbra.txt");
    assert_fidelity(dest, "ign/deep/d.txt");
    assert_fidelity(dest, "sub/x.log");
    CHECK(stat_pair(dest / "lib/ign") == stat_pair(repo / "ign"));
    CHECK(stat_pair(dest / "lib/ign/deep") == stat_pair(repo / "ign/deep"));
    CHECK(std::filesystem::is_directory(dest / "lib/sub"));
    CHECK(opened.out.find("\"restored_member_count\": 6") !=
          std::string::npos);
    if (leg == "network") {
      CHECK(open_repos_fixture::run_git(handle, dest / "lib",
                                        {"status", "--porcelain=v2"}).empty());
    } else {
      CHECK(std::filesystem::is_directory(dest / "lib"));
      CHECK(read_text(root / "trace").empty());
    }
    if (const char* receipts = std::getenv("BIV_LEG_RECEIPTS")) {
      std::ofstream out{receipts, std::ios::app};
      out << "leg=c6p-" << leg << " provenance=product-packed\n";
    }
  };
  run_leg("network", "--network");
  run_leg("offline", "--offline");
  std::filesystem::remove_all(root);
}

TEST_CASE("c6p nested and root repository penumbra survives real CLI open",
          "[cli][c6p]") {
  const auto handle = open_repos_fixture::git();
  const auto stat_pair = [](const std::filesystem::path& path) {
    struct stat status{};
    REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
    return std::pair{std::pair{status.st_mtimespec.tv_sec,
                               status.st_mtimespec.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#else
    return std::pair{std::pair{status.st_mtim.tv_sec, status.st_mtim.tv_nsec},
                     static_cast<uint32_t>(status.st_mode & 07777U)};
#endif
  };

  SECTION("P3 nested row under a payload directory") {
    const auto root = make_tmp("c6p-nested-penumbra");
    const auto workspace = root / "workspace";
    const auto repo = workspace / "docs/inner";
    write_file(workspace / "docs/outer.txt", "outer\n");
    std::filesystem::create_directories(repo);
    open_repos_fixture::run_git(handle, repo, {"init", "-b", "main"});
    write_file(repo / ".gitignore", "ign/\n");
    write_file(repo / "tracked.txt", "tracked\n");
    open_repos_fixture::run_git(handle, repo,
                                {"add", ".gitignore", "tracked.txt"});
    open_repos_fixture::run_git(handle, repo,
                                {"-c", "user.name=Biv Test", "-c",
                                 "user.email=biv@example.invalid", "commit",
                                 "-m", "base"});
    write_file(repo / "ign/p.txt", "penumbra\n");
    REQUIRE(open_repos_fixture::run_git(
                handle, repo, {"status", "--porcelain=v2"})
                .empty());
    const auto packed = run_cmd("pack '" + workspace.string() +
                                    "' --offline --json",
                                root);
    REQUIRE(packed.code == 0);
    const auto dest = root / "dest";
    const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                    "' --dest '" + dest.string() +
                                    "' --network --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 0);
    CHECK(read_text(dest / "docs/inner/ign/p.txt") == "penumbra\n");
    CHECK(stat_pair(dest / "docs/inner/ign/p.txt") ==
          stat_pair(repo / "ign/p.txt"));
    CHECK(stat_pair(dest / "docs") == stat_pair(workspace / "docs"));
    std::filesystem::remove_all(root);
  }

  SECTION("P4 root row is verified before its penumbra placement") {
    const auto root = make_tmp("c6p-root-penumbra");
    const auto workspace = root / "workspace";
    std::filesystem::create_directories(workspace);
    open_repos_fixture::run_git(handle, workspace, {"init", "-b", "main"});
    write_file(workspace / ".gitignore", "*.o\n");
    write_file(workspace / "src/a.c", "tracked\n");
    open_repos_fixture::run_git(handle, workspace,
                                {"add", ".gitignore", "src/a.c"});
    open_repos_fixture::run_git(handle, workspace,
                                {"-c", "user.name=Biv Test", "-c",
                                 "user.email=biv@example.invalid", "commit",
                                 "-m", "base"});
    write_file(workspace / ".git/info/exclude", "local.txt\n");
    write_file(workspace / "src/a.o", "ignored\n");
    write_file(workspace / "local.txt", "local\n");
    REQUIRE(open_repos_fixture::run_git(
                handle, workspace, {"status", "--porcelain=v2"})
                .empty());
    const auto packed = run_cmd("pack '" + workspace.string() +
                                    "' --offline --json",
                                root);
    REQUIRE(packed.code == 0);
    const auto dest = root / "dest";
    const auto opened = run_cmd("open '" + (root / "workspace.bvpk").string() +
                                    "' --dest '" + dest.string() +
                                    "' --network --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 0);
    for (const auto& rel : {std::string{"src/a.o"}, std::string{"local.txt"}}) {
      CHECK(read_text(dest / rel) == read_text(workspace / rel));
      CHECK(stat_pair(dest / rel) == stat_pair(workspace / rel));
    }
    CHECK(open_repos_fixture::run_git(
              handle, dest, {"status", "--porcelain=v2", "-z"}) ==
          std::string{"? local.txt\0", 12});
    const auto ignored = open_repos_fixture::run_git(
        handle, dest, {"status", "--porcelain=v2", "--ignored", "-z"});
    CHECK(ignored.find("! src/a.o\0") != std::string::npos);
    std::filesystem::remove_all(root);
  }
}

TEST_CASE("c6p deferred and first-pass writers refuse protected paths",
          "[cli][c6p]") {
  using namespace open_repos_fixture;
  const auto require_unsafe = [](const RunResult& opened) {
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 3);
    CHECK(opened.out.find("\"kind\": \"MemberPathUnsafe\"") !=
          std::string::npos);
  };

  SECTION("W2 and W3 folded dot-git are refused by the deferred writer") {
    for (const auto& [leg, flag] :
         std::array<std::pair<std::string, std::string>, 2>{{
             {"network", "--network"}, {"offline", "--offline"}}}) {
      const auto root = make_tmp("c6p-folded-dotgit-" + leg);
      const ScopedEnv home{"HOME", root.string()};
      Image fixture;
      fixture.capture_repo(root, "r-lib", "lib");
      fixture.payload.push_back(
          Image::member("payload/lib/.GIT/hooks/post-checkout", "hook\n"));
      const auto image = fixture.write(root);
      const auto opened = run_cmd("open '" + image.string() +
                                      "' --dest out " + flag + " --json",
                                  root);
      require_unsafe(opened);
      const auto partial = root / "out.bvpk-open.partial";
      CHECK_FALSE(std::filesystem::exists(
          partial / "lib/.GIT/hooks/post-checkout"));
      CHECK_FALSE(std::filesystem::exists(
          partial / "lib/.git/hooks/post-checkout"));
#if !defined(__APPLE__)
      CHECK_FALSE(std::filesystem::exists(partial / "lib/.GIT"));
#endif
      std::filesystem::remove_all(root);
    }
  }

  SECTION("W5 a placed symlink cannot become an ancestor") {
    const auto root = make_tmp("c6p-owned-symlink");
    const ScopedEnv home{"HOME", root.string()};
    const auto outside = root / "outside-c6p";
    std::filesystem::create_directories(outside);
    Image fixture;
    fixture.capture_repo(root, "r-lib", "lib");
    fixture.payload.push_back(
        Image::symlink("payload/lib/ln", "../../outside-c6p"));
    fixture.payload.push_back(Image::member("payload/lib/ln/x", "escape\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --offline --json",
                                root);
    require_unsafe(opened);
    const auto partial = root / "out.bvpk-open.partial";
    CHECK(std::filesystem::is_symlink(partial / "lib/ln"));
    CHECK(std::filesystem::is_empty(outside));
    std::filesystem::remove_all(root);
  }

  SECTION("H1 a restored symlink cannot become an ancestor") {
    const auto root = make_tmp("c6p-restored-symlink");
    const ScopedEnv home{"HOME", root.string()};
    const auto outside = root / "outside-c6p";
    std::filesystem::create_directories(outside);
    Image fixture;
    fixture.capture_repo(root, "r-lib", "lib", false, false, true);
    fixture.payload.push_back(
        Image::member("payload/lib/evil/x", "escape\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --network --json",
                                root);
    require_unsafe(opened);
    CHECK(std::filesystem::is_symlink(
        root / "out.bvpk-open.partial/lib/evil"));
    CHECK(std::filesystem::is_empty(outside));
    std::filesystem::remove_all(root);
  }

  SECTION("H2 a deferred member cannot overwrite a tracked path") {
    const auto root = make_tmp("c6p-no-overwrite");
    const ScopedEnv home{"HOME", root.string()};
    Image fixture;
    fixture.capture_repo(root, "r-lib", "lib");
    fixture.payload.push_back(
        Image::member("payload/lib/a.txt", "replacement\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --network --json",
                                root);
    require_unsafe(opened);
    CHECK(read_text(root / "out.bvpk-open.partial/lib/a.txt") ==
          "committed\n");
    std::filesystem::remove_all(root);
  }

  SECTION("H3 a member equal to a row path stays in the first pass") {
    const auto root = make_tmp("c6p-row-path-member");
    const ScopedEnv home{"HOME", root.string()};
    Image fixture;
    fixture.capture_repo(root, "r-inner", "docs/inner");
    fixture.payload.push_back(Image::directory("payload/docs"));
    fixture.payload.push_back(Image::member("payload/docs/inner", "file\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --network --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 4);
    CHECK(opened.out.find("materialization target already exists") !=
          std::string::npos);
    std::filesystem::remove_all(root);
  }

  SECTION("H4 parent placement precedes child restore") {
    const auto root = make_tmp("c6p-parent-before-child");
    const ScopedEnv home{"HOME", root.string()};
    Image fixture;
    fixture.capture_repo(root, "r-parent", "a");
    fixture.capture_repo(root, "r-child", "a/c");
    fixture.manifest.repos.at(1).parent_id = "r-parent";
    fixture.payload.push_back(Image::member("payload/a/c", "owned\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --network --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 4);
    CHECK(opened.out.find("materialization target already exists") !=
          std::string::npos);
    CHECK(opened.out.find("a/c") != std::string::npos);
    CHECK(read_text(root / "out.bvpk-open.partial/a/c") == "owned\n");
    std::filesystem::remove_all(root);
  }

  SECTION("H5 exact dot-git is refused after a root restore") {
    const auto root = make_tmp("c6p-root-dotgit");
    const ScopedEnv home{"HOME", root.string()};
    Image fixture;
    fixture.capture_repo(root, "r-root", ".");
    fixture.payload.push_back(
        Image::member("payload/.git/c6p-sentinel", "sentinel\n"));
    const auto image = fixture.write(root);
    const auto opened = run_cmd("open '" + image.string() +
                                    "' --dest out --network --json",
                                root);
    require_unsafe(opened);
    CHECK_FALSE(std::filesystem::exists(
        root / "out.bvpk-open.partial/.git/c6p-sentinel"));
    std::filesystem::remove_all(root);
  }

  SECTION("H6 and H6b root dot-biv spellings are refused") {
    for (const auto& spelling : {std::string{".biv"}, std::string{".BIV"}}) {
      const auto root = make_tmp("c6p-root-dotbiv-" + spelling);
      const ScopedEnv home{"HOME", root.string()};
      Image fixture;
      fixture.capture_repo(root, "r-root", ".");
      fixture.payload.push_back(Image::directory("payload/" + spelling));
      fixture.payload.push_back(Image::member(
          "payload/" + spelling + "/c6p-sentinel", "sentinel\n"));
      const auto image = fixture.write(root);
      const auto opened = run_cmd("open '" + image.string() +
                                      "' --dest out --network --json",
                                  root);
      require_unsafe(opened);
      CHECK_FALSE(std::filesystem::exists(
          root / "out.bvpk-open.partial" / spelling));
      std::filesystem::remove_all(root);
    }
  }

  SECTION("FP1 and FP2 protect every first-pass dot-git component") {
    for (const auto& [name, prefix] :
         std::array<std::pair<std::string, std::string>, 2>{{
             {"root", ".git"}, {"nested", "docs/.Git"}}}) {
      const auto root = make_tmp("c6p-first-pass-" + name);
      Image fixture;
      if (name == "nested") {
        fixture.payload.push_back(Image::directory("payload/docs"));
      }
      fixture.payload.push_back(Image::directory("payload/" + prefix));
      fixture.payload.push_back(
          Image::member("payload/" + prefix + "/config", "config\n"));
      const auto image = fixture.write(root);
      const auto opened = run_cmd("open '" + image.string() +
                                      "' --dest out --offline --json",
                                  root);
      require_unsafe(opened);
      CHECK_FALSE(std::filesystem::exists(
          root / "out.bvpk-open.partial" / prefix));
      std::filesystem::remove_all(root);
    }
  }
}
