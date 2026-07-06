#include <algorithm>
#include <array>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <map>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/container/tar_reader.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"
#include "core/pack/pack.hpp"

namespace {

struct ArchiveMember {
  biv::container::MemberMeta meta;
  std::vector<std::byte> data;
  std::string extent;
};

std::filesystem::path make_tmp(std::string_view name) {
  auto base = std::filesystem::temp_directory_path() /
              ("biv-pack-" + std::string{name} + "-" + std::to_string(::getpid()));
  std::filesystem::remove_all(base);
  std::filesystem::create_directories(base);
  return base;
}

void write_file(const std::filesystem::path& path, std::string_view content) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  out << content;
}

std::vector<std::byte> read_file_bytes(const std::filesystem::path& path) {
  std::ifstream in{path, std::ios::binary};
  REQUIRE(in);
  std::string bytes{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
  std::vector<std::byte> out(bytes.size());
  for (size_t i = 0; i < bytes.size(); ++i) {
    out[i] = static_cast<std::byte>(bytes[i]);
  }
  return out;
}

std::span<const std::byte> as_span(const std::vector<std::byte>& bytes) {
  return std::span<const std::byte>{bytes.data(), bytes.size()};
}

std::vector<ArchiveMember> read_archive(const std::filesystem::path& path) {
  auto compressed = read_file_bytes(path);
  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return as_span(compressed);
  }};
  biv::container::TarReader reader{source};

  std::vector<ArchiveMember> members;
  while (true) {
    auto next = reader.next();
    REQUIRE(next.has_value());
    if (!*next) {
      break;
    }
    ArchiveMember member{.meta = next->value().meta, .data = {}, .extent = {}};
    std::array<std::byte, 32> buffer {};
    while (true) {
      auto n = reader.read_data(buffer);
      REQUIRE(n.has_value());
      if (*n == 0U) {
        break;
      }
      member.data.insert(member.data.end(), buffer.begin(), buffer.begin() + static_cast<std::ptrdiff_t>(*n));
    }
    member.extent = reader.extent_sha256_hex();
    members.push_back(std::move(member));
  }
  return members;
}

std::string byte_string(std::span<const std::byte> bytes) {
  std::string out;
  out.reserve(bytes.size());
  for (const auto byte : bytes) {
    out.push_back(static_cast<char>(byte));
  }
  return out;
}

}  // namespace

TEST_CASE("pack writes manifest, checksums, and payload extents") {
  const auto root = make_tmp("happy");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / "dir");
  write_file(source / ".bivignore", "target/\n");
  write_file(source / "a.txt", "alpha");
  write_file(source / "dir" / "b.txt", "beta");
  std::filesystem::create_directories(source / "target");
  write_file(source / "target" / "skip.txt", "skip");
  std::filesystem::create_symlink("a.txt", source / "link.txt");

  auto report = biv::pack::pack(source);
  REQUIRE(report.has_value());
  CHECK(report->image_path == (root / "sample.bvpk").generic_string());
  CHECK(std::filesystem::exists(root / "sample.bvpk"));
  CHECK_FALSE(std::filesystem::exists(source / "sample.bvpk"));
  REQUIRE(report->advisories.size() == 1);
  CHECK(report->advisories[0].kind == "prune-summary");
  CHECK(report->advisories[0].entries[0].relpath == "target");

  const auto members = read_archive(root / "sample.bvpk");
  REQUIRE(members.size() == 7);
  CHECK(members[0].meta.path == "manifest.json");
  CHECK(members[1].meta.path == "checksums.json");
  CHECK(members[2].meta.path == "payload/.bivignore");
  CHECK(members[3].meta.path == "payload/a.txt");
  CHECK(members[4].meta.path == "payload/dir");
  CHECK(members[5].meta.path == "payload/dir/b.txt");
  CHECK(members[6].meta.path == "payload/link.txt");
  CHECK(std::ranges::none_of(members, [](const ArchiveMember& member) {
    return member.meta.path.find(".bvpk") != std::string::npos;
  }));

  auto manifest = biv::manifest::parse(as_span(members[0].data));
  REQUIRE(manifest.has_value());
  CHECK(manifest->format_version == 1);
  CHECK(manifest->bivignore.source == "file");

  auto checksums = biv::manifest::parse_checksums(as_span(members[1].data));
  REQUIRE(checksums.has_value());
  for (const auto& member : members) {
    if (!member.meta.path.starts_with("payload/")) {
      continue;
    }
    REQUIRE(checksums->entries.contains(member.meta.path));
    CHECK(checksums->entries.at(member.meta.path) == member.extent);
  }
  CHECK(byte_string(as_span(members[3].data)) == "alpha");

  std::filesystem::remove_all(root);
}

TEST_CASE("pack refuses stale partial and reports facts") {
  const auto root = make_tmp("partial");
  const auto source = root / "sample";
  std::filesystem::create_directories(source);
  write_file(source / "a.txt", "alpha");
  write_file(root / "sample.bvpk.partial", "stale");

  auto report = biv::pack::pack(source);
  REQUIRE_FALSE(report.has_value());
  CHECK(report.error().kind == biv::ErrKind::PartialPresent);
  CHECK(report.error().facts.at("partial_path") == (root / "sample.bvpk.partial").generic_string());
  CHECK(std::filesystem::exists(root / "sample.bvpk.partial"));
  std::filesystem::remove_all(root);
}

TEST_CASE("pack refuses repo-bearing source") {
  const auto root = make_tmp("repo");
  const auto source = root / "sample";
  std::filesystem::create_directories(source / ".git");
  auto report = biv::pack::pack(source);
  REQUIRE_FALSE(report.has_value());
  CHECK(report.error().kind == biv::ErrKind::RepoDiscoveredUnsupported);
  CHECK_FALSE(std::filesystem::exists(root / "sample.bvpk"));
  std::filesystem::remove_all(root);
}
