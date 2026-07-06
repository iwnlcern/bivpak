#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/container/tar_reader.hpp"
#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"

namespace {

std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> out(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    out[i] = static_cast<std::byte>(text[i]);
  }
  return out;
}

std::vector<std::byte> compress_raw(std::span<const std::byte> raw) {
  std::vector<std::byte> compressed;
  biv::container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    compressed.insert(compressed.end(), chunk.begin(), chunk.end());
    return {};
  }};
  auto sink = zstd.as_sink();
  REQUIRE(sink(raw));
  REQUIRE(zstd.finish());
  return compressed;
}

std::vector<std::byte> make_raw_archive(std::vector<std::string>& extents) {
  std::vector<std::byte> raw;
  biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    raw.insert(raw.end(), chunk.begin(), chunk.end());
    return {};
  }};

  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "dir",
      .kind = biv::scan::NodeKind::dir,
      .mode = 0755,
      .mtime_s = 10,
      .mtime_ns = 1,
      .size = 0,
      .symlink_target = {}}));
  extents.push_back(*writer.end_member());

  const auto data = bytes("hello");
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "dir/file.txt",
      .kind = biv::scan::NodeKind::file,
      .mode = 0640,
      .mtime_s = 11,
      .mtime_ns = 2,
      .size = data.size(),
      .symlink_target = {}}));
  REQUIRE(writer.write_data(data));
  extents.push_back(*writer.end_member());

  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "link.txt",
      .kind = biv::scan::NodeKind::symlink,
      .mode = 0777,
      .mtime_s = 12,
      .mtime_ns = 3,
      .size = 0,
      .symlink_target = "dir/file.txt"}));
  extents.push_back(*writer.end_member());

  const std::string long_name(150, 'x');
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = long_name,
      .kind = biv::scan::NodeKind::file,
      .mode = 0600,
      .mtime_s = 13,
      .mtime_ns = 4,
      .size = 0,
      .symlink_target = {}}));
  extents.push_back(*writer.end_member());

  REQUIRE(writer.finish());
  return raw;
}

void recompute_header_checksum(std::span<std::byte> header) {
  std::ranges::fill(header.subspan(148, 8), static_cast<std::byte>(' '));
  uint64_t checksum = 0;
  for (const auto byte : header) {
    checksum += std::to_integer<unsigned char>(byte);
  }
  auto octal = std::string(6, '0');
  for (size_t i = 0; i < octal.size(); ++i) {
    const auto pos = octal.size() - 1U - i;
    octal[pos] = static_cast<char>('0' + (checksum & 07U));
    checksum >>= 3U;
  }
  for (size_t i = 0; i < octal.size(); ++i) {
    header[148 + i] = static_cast<std::byte>(octal[i]);
  }
  header[154] = std::byte{0};
  header[155] = static_cast<std::byte>(' ');
}

std::vector<biv::container::RMember> read_all(const std::vector<std::byte>& compressed,
                                              std::vector<std::string>& extent_hashes,
                                              std::string& file_payload) {
  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{compressed};
  }};
  biv::container::TarReader reader{source};

  std::vector<biv::container::RMember> members;
  while (true) {
    auto next = reader.next();
    REQUIRE(next.has_value());
    if (!*next) {
      break;
    }
    members.push_back(**next);
    std::array<std::byte, 16> buffer {};
    while (true) {
      auto n = reader.read_data(buffer);
      REQUIRE(n.has_value());
      if (*n == 0U) {
        break;
      }
      for (size_t i = 0; i < *n; ++i) {
        file_payload.push_back(static_cast<char>(buffer[i]));
      }
    }
    extent_hashes.push_back(reader.extent_sha256_hex());
  }
  return members;
}

}  // namespace

TEST_CASE("zstd magic and tar reader round-trip writer extents") {
  std::vector<std::string> writer_extents;
  const auto raw = make_raw_archive(writer_extents);
  const auto compressed = compress_raw(raw);
  REQUIRE(compressed.size() > 4);
  CHECK(std::ranges::equal(std::span<const std::byte>{compressed}.first<4>(),
                           std::as_bytes(std::span<const unsigned char>{biv::container::kZstdMagic})));

  std::vector<std::string> reader_extents;
  std::string file_payload;
  const auto members = read_all(compressed, reader_extents, file_payload);
  REQUIRE(members.size() == 4);
  CHECK(members[0].meta.path == "dir");
  CHECK(members[0].meta.kind == biv::scan::NodeKind::dir);
  CHECK(members[1].meta.path == "dir/file.txt");
  CHECK(members[1].meta.mode == 0640);
  CHECK(members[1].meta.mtime_s == 11);
  CHECK(members[1].meta.mtime_ns == 2);
  CHECK(members[2].meta.symlink_target == "dir/file.txt");
  CHECK(members[3].meta.path == std::string(150, 'x'));
  CHECK(file_payload == "hello");
  CHECK(reader_extents == writer_extents);
}

TEST_CASE("zstd checksum corruption returns typed error") {
  std::vector<std::string> writer_extents;
  const auto raw = make_raw_archive(writer_extents);
  auto compressed = compress_raw(raw);
  compressed[compressed.size() / 2U] ^= std::byte{0x01};

  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{compressed};
  }};
  biv::container::TarReader reader{source};
  auto next = reader.next();
  REQUIRE_FALSE(next.has_value());
  CHECK(next.error().kind == biv::ErrKind::ParseError);
}

TEST_CASE("tar reader refuses unsafe member paths") {
  const std::vector<std::string> unsafe_paths{"../evil", ".", "a/./b", "a//b", "a/"};
  for (const auto& path : unsafe_paths) {
    CAPTURE(path);
    std::vector<std::byte> raw;
    biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
      raw.insert(raw.end(), chunk.begin(), chunk.end());
      return {};
    }};
    REQUIRE(writer.begin_member(biv::container::MemberMeta{
        .path = path,
        .kind = biv::scan::NodeKind::file,
        .mode = 0644,
        .mtime_s = 1,
        .mtime_ns = 0,
        .size = 0,
        .symlink_target = {}}));
    REQUIRE(writer.end_member());
    REQUIRE(writer.finish());
    const auto compressed = compress_raw(raw);

    bool served = false;
    biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
      if (served) {
        return std::span<const std::byte>{};
      }
      served = true;
      return std::span<const std::byte>{compressed};
    }};
    biv::container::TarReader reader{source};
    auto next = reader.next();
    REQUIRE_FALSE(next.has_value());
    CHECK(next.error().kind == biv::ErrKind::MemberPathUnsafe);
  }
}

TEST_CASE("tar reader refuses GNU long-name typeflag") {
  std::vector<std::string> writer_extents;
  auto raw = make_raw_archive(writer_extents);
  raw[1024 + 156] = static_cast<std::byte>('L');
  recompute_header_checksum(std::span<std::byte>{raw}.subspan(1024, 512));
  const auto compressed = compress_raw(raw);

  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{compressed};
  }};
  biv::container::TarReader reader{source};
  auto next = reader.next();
  REQUIRE_FALSE(next.has_value());
  CHECK(next.error().kind == biv::ErrKind::ParseError);
}

TEST_CASE("tar reader accepts signed pax mtime emitted by writer") {
  std::vector<std::byte> raw;
  biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    raw.insert(raw.end(), chunk.begin(), chunk.end());
    return {};
  }};
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "old.txt",
      .kind = biv::scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = -1,
      .mtime_ns = 123,
      .size = 0,
      .symlink_target = {}}));
  REQUIRE(writer.end_member());
  REQUIRE(writer.finish());
  const auto compressed = compress_raw(raw);

  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{compressed};
  }};
  biv::container::TarReader reader{source};
  auto next = reader.next();
  REQUIRE(next.has_value());
  REQUIRE(*next);
  CHECK(next->value().meta.mtime_s == -1);
  CHECK(next->value().meta.mtime_ns == 123);
}

TEST_CASE("tar reader rejects oversized pax payload size before reading payload") {
  std::vector<std::byte> raw;
  biv::container::TarWriter writer{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    raw.insert(raw.end(), chunk.begin(), chunk.end());
    return {};
  }};
  REQUIRE(writer.begin_member(biv::container::MemberMeta{
      .path = "huge.bin",
      .kind = biv::scan::NodeKind::file,
      .mode = 0644,
      .mtime_s = 1,
      .mtime_ns = 0,
      .size = 1ULL << 63U,
      .symlink_target = {}}));
  const auto compressed = compress_raw(raw);

  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{compressed};
  }};
  biv::container::TarReader reader{source};
  auto next = reader.next();
  REQUIRE_FALSE(next.has_value());
  CHECK(next.error().kind == biv::ErrKind::ParseError);
  CHECK(next.error().detail == "payload-size");
}
