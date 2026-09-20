#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#include <unistd.h>
#include <sys/stat.h>

#include <catch2/catch_test_macros.hpp>

#include "core/ignore/builtin.hpp"
#include "core/manifest/manifest.hpp"
#include "core/scan/scan.hpp"

namespace {

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() / ("biv-scan-" + std::string{name} + "-" + std::to_string(::getpid()));
  std::filesystem::remove_all(base);
  std::filesystem::create_directories(base);
  return base;
}

void write_file(const std::filesystem::path& path, std::string_view content = "x") {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out{path};
  out << content;
}

}  // namespace

TEST_CASE("scan enumerates payload in lexicographic byte order") {
  auto root = make_tmp("lex");
  write_file(root / "b.txt");
  write_file(root / "a.txt");
  std::filesystem::create_directory(root / "dir");
  write_file(root / "dir" / "c.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->payload.size() == 4);
  REQUIRE(result->payload[0].relpath == "a.txt");
  REQUIRE(result->payload[1].relpath == "b.txt");
  REQUIRE(result->payload[2].relpath == "dir");
  REQUIRE(result->payload[3].relpath == "dir/c.txt");
  std::filesystem::remove_all(root);
}

TEST_CASE("root .bivignore prunes directories and records file provenance") {
  auto root = make_tmp("file-ignore");
  write_file(root / ".bivignore", "node_modules/\n");
  std::filesystem::create_directories(root / "node_modules");
  write_file(root / "node_modules" / "skip.txt");
  write_file(root / "keep.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->bivignore.source == "file");
  REQUIRE_FALSE(result->bivignore.builtin_id.has_value());
  REQUIRE(result->bivignore.sha256_hex == "4d56952b0fb13bf8f9b6c13a6d4c34a075bac3af447636a1df4335d7576e2f97");
  REQUIRE(result->pruned.size() == 1);
  REQUIRE(result->pruned[0].relpath == "node_modules");
  REQUIRE(result->pruned[0].source == ".bivignore:1");
  REQUIRE(result->payload[0].relpath == ".bivignore");
  REQUIRE(result->payload.back().relpath == "keep.txt");
  std::filesystem::remove_all(root);
}

TEST_CASE("root .bivignore prunes files and cannot prune itself") {
  auto root = make_tmp("file-prune");
  write_file(root / ".bivignore", "*\n!.bivignore\n");
  write_file(root / "skip.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->payload.size() == 1);
  CHECK(result->payload[0].relpath == ".bivignore");
  REQUIRE(result->pruned.size() == 1);
  CHECK(result->pruned[0].relpath == "skip.txt");
  CHECK(result->pruned[0].source == ".bivignore:1");
  std::filesystem::remove_all(root);
}

TEST_CASE("root .bivignore can prune .git before repo refusal") {
  auto root = make_tmp("git-pruned");
  write_file(root / ".bivignore", ".git/\n");
  std::filesystem::create_directory(root / ".git");
  write_file(root / "keep.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->pruned.size() == 1);
  CHECK(result->pruned[0].relpath == ".git");
  CHECK(result->payload.back().relpath == "keep.txt");
  std::filesystem::remove_all(root);
}

TEST_CASE("builtin ignore prunes target directory when root ignore is absent") {
  auto root = make_tmp("builtin");
  std::filesystem::create_directories(root / "target");
  write_file(root / "target" / "skip.txt");
  write_file(root / "keep.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->bivignore.source == "builtin");
  REQUIRE(result->bivignore.builtin_id == "builtin-v1");
  REQUIRE(result->bivignore.sha256_hex == biv::ignore::kBuiltinV1Sha256);
  REQUIRE(result->pruned.size() == 1);
  REQUIRE(result->pruned[0].relpath == "target");
  REQUIRE(result->pruned[0].source == "builtin-v1");
  std::filesystem::remove_all(root);
}

TEST_CASE("scan records symlinks and nested .bivignore advisories") {
  auto root = make_tmp("symlink");
  write_file(root / "data.txt", "payload");
  std::filesystem::create_directories(root / "sub");
  write_file(root / "sub" / ".bivignore", "*.tmp\n");
  std::filesystem::create_symlink("data.txt", root / "link.txt");

  auto result = biv::scan::scan(root);
  REQUIRE(result.has_value());
  REQUIRE(result->nested_bivignore == std::vector<std::string>{"sub/.bivignore"});
  auto link = std::ranges::find(result->payload, "link.txt", &biv::scan::Node::relpath);
  REQUIRE(link != result->payload.end());
  REQUIRE(link->kind == biv::scan::NodeKind::symlink);
  REQUIRE(link->symlink_target == "data.txt");
  std::filesystem::remove_all(root);
}

TEST_CASE("scan exclusions canonicalize and claim repository roots", "[pack-repos]") {
  auto root = make_tmp("repo");
  std::filesystem::create_directory(root / ".git");
  write_file(root / "src/main.cpp");
  write_file(root / "README");

  auto matcher = biv::scan::prepare_matcher(root);
  REQUIRE(matcher.has_value());
  for (const auto& spelling : {std::filesystem::path{"."}, std::filesystem::path{}}) {
    biv::scan::ScanExclusions exclusions{
        .repo_subtrees = {biv::scan::ScanExclusions::canonical(spelling)}};
    auto result = biv::scan::scan(root, matcher->matcher, exclusions);
    REQUIRE(result.has_value());
    CHECK(result->payload.empty());
    CHECK(result->pruned.empty());
  }
  std::filesystem::remove_all(root);
}

TEST_CASE("scan excludes a nested repository subtree as one writer", "[pack-repos]") {
  auto root = make_tmp("nested-repo");
  std::filesystem::create_directories(root / "lib/vendored/.git");
  write_file(root / "lib/vendored/x.c");
  write_file(root / "lib/other.c");

  auto matcher = biv::scan::prepare_matcher(root);
  REQUIRE(matcher.has_value());
  auto result = biv::scan::scan(
      root, matcher->matcher,
      biv::scan::ScanExclusions{.repo_subtrees = {"lib/vendored"}});
  REQUIRE(result.has_value());
  CHECK(std::ranges::any_of(result->payload, [](const auto& node) {
    return node.relpath == "lib/other.c";
  }));
  CHECK_FALSE(std::ranges::any_of(result->payload, [](const auto& node) {
    return node.relpath.starts_with("lib/vendored") ||
           node.relpath.find(".git") != std::string::npos;
  }));
  std::filesystem::remove_all(root);
}

TEST_CASE("scan refuses only unclaimed hostile git markers", "[pack-repos]") {
  auto root = make_tmp("unclaimed-git");
  std::filesystem::create_symlink("target", root / ".git");

  auto result = biv::scan::scan(root);
  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::UnclaimedGitEntry);
  CHECK(result.error().facts.at("reason") == "symlink");

  std::filesystem::remove(root / ".git");
  REQUIRE(::mkfifo((root / ".git").c_str(), 0600) == 0);
  result = biv::scan::scan(root);
  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::UnclaimedGitEntry);
  CHECK(result.error().facts.at("reason") == "special-file");

  std::filesystem::remove(root / ".git");
  std::filesystem::create_directory(root / ".git");
  result = biv::scan::scan(root);
  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().kind == biv::ErrKind::UnclaimedGitEntry);
  CHECK(result.error().facts.at("reason") == "unreadable-marker");

  std::filesystem::remove_all(root);
}
