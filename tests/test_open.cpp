#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/open/open.hpp"
#include "core/pack/pack.hpp"

namespace {

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() /
              ("biv-open-" + std::string{name} + "-" + std::to_string(::getpid()));
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

std::filesystem::path make_image(const std::filesystem::path& root) {
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / ".bivignore", "target/\n");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");
  std::filesystem::create_symlink("a.txt", source / "link.txt");
  auto packed = biv::pack::pack(source);
  REQUIRE(packed.has_value());
  return root / "sample.bvpk";
}

}  // namespace

TEST_CASE("open restores packed tree to explicit destination") {
  const auto root = make_tmp("roundtrip");
  const auto image = make_image(root);
  const auto dest = root / "restore";

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = dest});
  REQUIRE(opened.has_value());
  CHECK(opened->output_dir == dest.generic_string());
  CHECK(opened->restored_member_count == 5);
  CHECK(opened->checksums_verified == false);
  CHECK(read_text(dest / "a.txt") == "alpha");
  CHECK(read_text(dest / "dir" / "b.txt") == "beta");
  CHECK(std::filesystem::read_symlink(dest / "link.txt").generic_string() == "a.txt");
  CHECK_FALSE(std::filesystem::exists(dest / "target"));
  std::filesystem::remove_all(root);
}

TEST_CASE("open collision modes refuse or rename") {
  const auto root = make_tmp("collision");
  const auto image = make_image(root);
  const auto dest = root / "restore";
  std::filesystem::create_directories(dest);
  write_file(dest / "existing.txt", "keep");

  auto refused = biv::open::open(biv::open::OpenOptions{.image = image, .dest = dest});
  REQUIRE_FALSE(refused.has_value());
  CHECK(refused.error().kind == biv::ErrKind::CollisionRefused);
  CHECK(read_text(dest / "existing.txt") == "keep");

  auto renamed =
      biv::open::open(biv::open::OpenOptions{.image = image, .dest = dest, .collision = biv::open::Collision::rename});
  REQUIRE(renamed.has_value());
  CHECK(renamed->output_dir == (root / "restore(1)").generic_string());
  CHECK(read_text(root / "restore(1)" / "a.txt") == "alpha");
  std::filesystem::remove_all(root);
}

TEST_CASE("open refuses pre-existing partial dir") {
  const auto root = make_tmp("partial");
  const auto image = make_image(root);
  const auto dest = root / "restore";
  std::filesystem::create_directories(root / "restore.bvpk-open.partial");

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = dest});
  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::OpenPartialPresent);
  CHECK(opened.error().facts.at("partial_dir") == (root / "restore.bvpk-open.partial").generic_string());
  std::filesystem::remove_all(root);
}
