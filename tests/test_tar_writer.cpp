#include <array>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/container/tar_writer.hpp"
#include "core/ignore/builtin.hpp"
#include "core/support/sha256.hpp"

namespace {

std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> out(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    out[i] = static_cast<std::byte>(text[i]);
  }
  return out;
}

std::string sha256_hex(std::span<const std::byte> data) {
  biv::support::Sha256 sha;
  sha.update(data);
  return sha.finish_hex();
}

std::string field_string(std::span<const std::byte> block, size_t offset, size_t length) {
  std::string out;
  out.reserve(length);
  for (size_t i = 0; i < length; ++i) {
    const auto ch = static_cast<char>(block[offset + i]);
    if (ch == '\0') {
      break;
    }
    out.push_back(ch);
  }
  return out;
}

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() /
              ("biv-tar-" + std::string{name} + "-" + std::to_string(::getpid()));
  std::filesystem::remove_all(base);
  std::filesystem::create_directories(base);
  return base;
}

int run_command(const std::string& command) {
  const int rc = std::system(command.c_str());
  if (rc == -1) {
    return -1;
  }
  if (WIFEXITED(rc)) {
    return WEXITSTATUS(rc);
  }
  return rc;
}

}  // namespace

TEST_CASE("sha256 matches NIST vectors and builtin-v1") {
  CHECK(sha256_hex({}) == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
  const auto abc = bytes("abc");
  CHECK(sha256_hex(abc) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

  std::vector<std::byte> million(1'000'000, static_cast<std::byte>('a'));
  CHECK(sha256_hex(million) == "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");

  const auto builtin = bytes(biv::ignore::kBuiltinV1);
  CHECK(sha256_hex(builtin) == biv::ignore::kBuiltinV1Sha256);
}

TEST_CASE("tar writer emits pax record, ustar header, and extent hash") {
  std::vector<std::byte> archive;
  biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    archive.insert(archive.end(), chunk.begin(), chunk.end());
    return {};
  }};

  const auto payload = bytes("abc");
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "payload/a.txt",
      .kind = biv::scan::NodeKind::file,
      .mode = 0640,
      .mtime_s = 123,
      .mtime_ns = 45,
      .size = payload.size(),
      .symlink_target = {}}));
  REQUIRE(writer.write_data(payload));
  auto extent = writer.end_member();
  REQUIRE(extent.has_value());
  REQUIRE(writer.finish());

  REQUIRE(archive.size() == 3072);
  const std::span<const std::byte> member_extent{archive.data(), 2048};
  CHECK(*extent == sha256_hex(member_extent));

  const std::span<const std::byte> pax_header{archive.data(), 512};
  CHECK(field_string(pax_header, 0, 100) == "PaxHeaders/payload/a.txt");
  CHECK(field_string(pax_header, 124, 12) == "00000000055");
  CHECK(static_cast<char>(pax_header[156]) == 'x');

  const std::span<const std::byte> pax_data{archive.data() + 512, 45};
  CHECK(field_string(pax_data, 0, 45) == "22 path=payload/a.txt\n23 mtime=123.000000045\n");

  const std::span<const std::byte> ustar{archive.data() + 1024, 512};
  CHECK(field_string(ustar, 0, 100) == "payload/a.txt");
  CHECK(field_string(ustar, 100, 8) == "0000640");
  CHECK(field_string(ustar, 124, 12) == "00000000003");
  CHECK(field_string(ustar, 136, 12) == "00000000173");
  CHECK(static_cast<char>(ustar[156]) == '0');
  CHECK(field_string(ustar, 257, 6) == "ustar");
  CHECK(field_string(ustar, 265, 32) == "root");
  CHECK(field_string(ustar, 297, 32) == "root");
}

TEST_CASE("tar writer archives extract with GNU tar") {
  if (run_command("tar --version >/dev/null 2>&1") != 0) {
    SKIP("GNU tar is not available");
  }

  const auto root = make_tmp("extract");
  const auto archive_path = root / "sample.tar";
  const auto out_dir = root / "out";
  std::filesystem::create_directories(out_dir);

  std::ofstream out{archive_path, std::ios::binary};
  REQUIRE(out);
  biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    out.write(reinterpret_cast<const char*>(chunk.data()), static_cast<std::streamsize>(chunk.size()));
    if (!out) {
      return std::unexpected(biv::BivError{biv::ErrKind::ArchiveWriteFailed, archive_path.generic_string()});
    }
    return {};
  }};

  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "dir",
      .kind = biv::scan::NodeKind::dir,
      .mode = 0755,
      .mtime_s = 1000,
      .mtime_ns = 1,
      .size = 0,
      .symlink_target = {}}));
  REQUIRE(writer.end_member());

  const auto file_data = bytes("payload\n");
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "dir/file.txt",
      .kind = biv::scan::NodeKind::file,
      .mode = 0640,
      .mtime_s = 1001,
      .mtime_ns = 2,
      .size = file_data.size(),
      .symlink_target = {}}));
  REQUIRE(writer.write_data(file_data));
  REQUIRE(writer.end_member());

  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "link.txt",
      .kind = biv::scan::NodeKind::symlink,
      .mode = 0777,
      .mtime_s = 1002,
      .mtime_ns = 3,
      .size = 0,
      .symlink_target = "dir/file.txt"}));
  REQUIRE(writer.end_member());

  const std::string long_name(150, 'a');
  const auto long_data = bytes("long");
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = long_name,
      .kind = biv::scan::NodeKind::file,
      .mode = 0600,
      .mtime_s = 1003,
      .mtime_ns = 4,
      .size = long_data.size(),
      .symlink_target = {}}));
  REQUIRE(writer.write_data(long_data));
  REQUIRE(writer.end_member());
  REQUIRE(writer.finish());
  out.close();

  REQUIRE(run_command("tar -xf '" + archive_path.string() + "' -C '" + out_dir.string() + "'") == 0);
  CHECK(std::filesystem::is_directory(out_dir / "dir"));
  std::ifstream restored{out_dir / "dir" / "file.txt", std::ios::binary};
  REQUIRE(restored);
  CHECK(std::string{std::istreambuf_iterator<char>{restored}, std::istreambuf_iterator<char>{}} == "payload\n");
  CHECK(std::filesystem::read_symlink(out_dir / "link.txt").generic_string() == "dir/file.txt");
  CHECK(std::filesystem::exists(out_dir / long_name));

  std::filesystem::remove_all(root);
}
