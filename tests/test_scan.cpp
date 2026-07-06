#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#include <unistd.h>

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

TEST_CASE("scan refuses repo-bearing roots") {
  auto root = make_tmp("repo");
  std::filesystem::create_directory(root / ".git");

  auto result = biv::scan::scan(root);
  REQUIRE_FALSE(result.has_value());
  REQUIRE(result.error().kind == biv::ErrKind::RepoDiscoveredUnsupported);
  std::filesystem::remove_all(root);
}
