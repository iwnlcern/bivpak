#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

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
