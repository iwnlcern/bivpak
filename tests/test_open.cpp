#include <cstddef>
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/manifest/checksums.hpp"
#include "core/manifest/manifest.hpp"
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

std::vector<std::byte> bytes(std::string_view text) {
  std::vector<std::byte> out(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    out[i] = static_cast<std::byte>(text[i]);
  }
  return out;
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

biv::manifest::Manifest manifest_model(int format_version = 1) {
  return biv::manifest::Manifest{
      .format_version = format_version,
      .required_capabilities = {},
      .image_id = "00000000-0000-4000-8000-000000000000",
      .app_version = "0.1.0",
      .created_at = "2026-07-05T00:00:00Z",
      .source_path = "/tmp/source",
      .source_path_flavor = biv::manifest::PathFlavor::posix,
      .agent_sessions = {},
      .bivignore = {.source = "builtin", .builtin_id = "builtin-v1", .sha256_hex = "abc123"}};
}

biv::manifest::Manifest session_manifest(std::string artifact = "agents/codex/session.jsonl") {
  auto manifest = manifest_model();
  biv::manifest::AgentSessionEntry entry;
  entry.agent = "codex";
  entry.agent_version_at_pack = "0.142.5";
  entry.relpath_key = ".";
  entry.original_path = "/tmp/source";
  entry.normalized_path_key = "/tmp/source";
  entry.normalization_scheme = "codex-cwd/v1";
  entry.path_flavor = biv::manifest::PathFlavor::posix;
  entry.provenance = {.store_root = "/tmp/codex",
                      .locator = "sessions_root",
                      .discovery_tier = "default",
                      .archived = false};
  entry.original_session_ids = {.primary = "019f-aaaa", .parent = std::nullopt, .parent_in_image = std::nullopt};
  entry.artifacts = {std::move(artifact)};
  entry.imported_at = "2026-07-11T00:00:00Z";
  manifest.agent_sessions.push_back(std::move(entry));
  return manifest;
}

struct MemberFixture {
  biv::container::MemberMeta meta;
  std::vector<std::byte> data;
};

void write_bivpak(const std::filesystem::path& image,
                  const biv::manifest::Manifest& manifest,
                  const biv::manifest::Checksums& checksums,
                  const std::vector<MemberFixture>& payload) {
  std::ofstream out{image, std::ios::binary};
  REQUIRE(out);
  biv::container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    out.write(reinterpret_cast<const char*>(chunk.data()), static_cast<std::streamsize>(chunk.size()));
    REQUIRE(out);
    return {};
  }};
  auto sink = zstd.as_sink();
  biv::container::TarWriter writer{sink};

  const auto manifest_json = biv::manifest::serialize(manifest);
  REQUIRE(writer.begin_member(biv::container::MemberMeta{.path = "manifest.json",
                                                         .kind = biv::scan::NodeKind::file,
                                                         .mode = 0644,
                                                         .mtime_s = 1,
                                                         .mtime_ns = 0,
                                                         .size = manifest_json.size(),
                                                         .symlink_target = {}}));
  REQUIRE(writer.write_data(std::as_bytes(std::span<const char>{manifest_json.data(), manifest_json.size()})));
  REQUIRE(writer.end_member());

  const auto checksums_json = biv::manifest::serialize(checksums);
  REQUIRE(writer.begin_member(biv::container::MemberMeta{.path = "checksums.json",
                                                         .kind = biv::scan::NodeKind::file,
                                                         .mode = 0644,
                                                         .mtime_s = 1,
                                                         .mtime_ns = 0,
                                                         .size = checksums_json.size(),
                                                         .symlink_target = {}}));
  REQUIRE(writer.write_data(std::as_bytes(std::span<const char>{checksums_json.data(), checksums_json.size()})));
  REQUIRE(writer.end_member());

  for (const auto& member : payload) {
    REQUIRE(writer.begin_member(member.meta));
    if (!member.data.empty()) {
      REQUIRE(writer.write_data(member.data));
    }
    REQUIRE(writer.end_member());
  }
  REQUIRE(writer.finish());
  REQUIRE(zstd.finish());
}

std::string payload_extent_digest(const biv::container::MemberMeta& meta, const std::vector<std::byte>& data) {
  biv::container::TarWriter writer{[](std::span<const std::byte>) -> biv::expected<void> { return {}; }};
  REQUIRE(writer.begin_member(meta));
  if (!data.empty()) {
    REQUIRE(writer.write_data(data));
  }
  auto digest = writer.end_member();
  REQUIRE(digest.has_value());
  return *digest;
}

std::string read_binary_or_throw(const std::filesystem::path& source) {
  std::ifstream in{source, std::ios::binary};
  if (!in) {
    throw std::runtime_error("source-open");
  }
  return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}

void copy_file_to_fifo(const std::filesystem::path& source, const std::filesystem::path& fifo) {
  const auto bytes_to_write = read_binary_or_throw(source);
  std::ofstream out{fifo, std::ios::binary};
  if (!out) {
    throw std::runtime_error("fifo-open");
  }
  out.write(bytes_to_write.data(), static_cast<std::streamsize>(bytes_to_write.size()));
  if (!out) {
    throw std::runtime_error("fifo-write");
  }
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

TEST_CASE("open refuses payload writes through a created symlink parent") {
  const auto root = make_tmp("zip-slip");
  const auto outside = root / "outside";
  std::filesystem::create_directories(outside / "tmp");
  const auto image = root / "evil.bvpk";

  biv::manifest::Checksums checksums;
  checksums.entries["payload/a"] = std::string(64, '0');
  checksums.entries["payload/a/tmp/evil"] = std::string(64, '0');
  write_bivpak(image,
               manifest_model(),
               checksums,
               std::vector<MemberFixture>{
                   MemberFixture{.meta = biv::container::MemberMeta{.path = "payload/a",
                                                                     .kind = biv::scan::NodeKind::symlink,
                                                                     .mode = 0777,
                                                                     .mtime_s = 1,
                                                                     .mtime_ns = 0,
                                                                     .size = 0,
                                                                     .symlink_target = outside.generic_string()},
                                 .data = {}},
                   MemberFixture{.meta = biv::container::MemberMeta{.path = "payload/a/tmp/evil",
                                                                     .kind = biv::scan::NodeKind::file,
                                                                     .mode = 0644,
                                                                     .mtime_s = 1,
                                                                     .mtime_ns = 0,
                                                                     .size = 4,
                                                                     .symlink_target = {}},
                                 .data = bytes("evil")}});

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = root / "restore"});
  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::MemberPathUnsafe);
  CHECK_FALSE(std::filesystem::exists(outside / "tmp" / "evil"));
  std::filesystem::remove_all(root);
}

TEST_CASE("open gates manifest version before later hostile members") {
  const auto root = make_tmp("version-gate");
  const auto image = root / "future.bvpk";
  biv::manifest::Checksums checksums;
  checksums.entries["payload/../evil"] = std::string(64, '0');
  write_bivpak(image,
               manifest_model(2),
               checksums,
               std::vector<MemberFixture>{MemberFixture{.meta = biv::container::MemberMeta{.path = "payload/../evil",
                                                                                           .kind = biv::scan::NodeKind::file,
                                                                                           .mode = 0644,
                                                                                           .mtime_s = 1,
                                                                                           .mtime_ns = 0,
                                                                                           .size = 0,
                                                                                           .symlink_target = {}},
                                                        .data = {}}});

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = root / "restore"});
  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::FormatVersionUnsupported);
  std::filesystem::remove_all(root);
}

TEST_CASE("open verify rejects checksum mismatches before apply") {
  const auto root = make_tmp("verify");
  const auto image = root / "bad-checksum.bvpk";
  biv::manifest::Checksums checksums;
  checksums.entries["payload/file.txt"] = std::string(64, '0');
  write_bivpak(image,
               manifest_model(),
               checksums,
               std::vector<MemberFixture>{MemberFixture{.meta = biv::container::MemberMeta{.path = "payload/file.txt",
                                                                                           .kind = biv::scan::NodeKind::file,
                                                                                           .mode = 0644,
                                                                                           .mtime_s = 1,
                                                                                           .mtime_ns = 0,
                                                                                           .size = 5,
                                                                                           .symlink_target = {}},
                                                        .data = bytes("hello")}});

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = root / "restore", .verify = true});
  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::IntegrityFailurePreApply);
  CHECK_FALSE(std::filesystem::exists(root / "restore"));
  std::filesystem::remove_all(root);
}

TEST_CASE("open verify rechecks payload digest during apply pass") {
  const auto root = make_tmp("verify-apply");
  const auto good_image = root / "good.bvpk";
  const auto bad_image = root / "bad.bvpk";
  const auto fifo_image = root / "stream.bvpk";
  const auto dest = root / "restore";

  const biv::container::MemberMeta meta{.path = "payload/file.txt",
                                        .kind = biv::scan::NodeKind::file,
                                        .mode = 0644,
                                        .mtime_s = 1,
                                        .mtime_ns = 0,
                                        .size = 5,
                                        .symlink_target = {}};
  const auto good_payload = bytes("hello");
  const auto bad_payload = bytes("HELLO");
  biv::manifest::Checksums checksums;
  checksums.entries[meta.path] = payload_extent_digest(meta, good_payload);
  write_bivpak(good_image, manifest_model(), checksums, {MemberFixture{.meta = meta, .data = good_payload}});
  write_bivpak(bad_image, manifest_model(), checksums, {MemberFixture{.meta = meta, .data = bad_payload}});
  REQUIRE(::mkfifo(fifo_image.c_str(), 0600) == 0);

  std::exception_ptr writer_error;
  std::thread writer{[&]() {
    try {
      copy_file_to_fifo(good_image, fifo_image);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      copy_file_to_fifo(bad_image, fifo_image);
    } catch (...) {
      writer_error = std::current_exception();
    }
  }};

  auto opened = biv::open::open(biv::open::OpenOptions{.image = fifo_image, .dest = dest, .verify = true});
  writer.join();
  if (writer_error) {
    std::rethrow_exception(writer_error);
  }

  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::IntegrityFailureMidApply);
  CHECK(opened.error().path == "payload/file.txt");
  CHECK(std::filesystem::exists(root / "restore.bvpk-open.partial"));
  CHECK_FALSE(std::filesystem::exists(dest));
  std::filesystem::remove_all(root);
}

TEST_CASE("open refuses payload members absent from checksums") {
  const auto root = make_tmp("unmanifested");
  const auto image = root / "unmanifested.bvpk";
  biv::manifest::Checksums checksums;
  write_bivpak(image,
               manifest_model(),
               checksums,
               std::vector<MemberFixture>{MemberFixture{.meta = biv::container::MemberMeta{.path = "payload/file.txt",
                                                                                           .kind = biv::scan::NodeKind::file,
                                                                                           .mode = 0644,
                                                                                           .mtime_s = 1,
                                                                                           .mtime_ns = 0,
                                                                                           .size = 5,
                                                                                           .symlink_target = {}},
                                                        .data = bytes("hello")}});

  auto opened = biv::open::open(biv::open::OpenOptions{.image = image, .dest = root / "restore"});
  REQUIRE_FALSE(opened.has_value());
  CHECK(opened.error().kind == biv::ErrKind::UnmanifestedMember);
  CHECK_FALSE(std::filesystem::exists(root / "restore"));
  std::filesystem::remove_all(root);
}

TEST_CASE("planned agent member reader survives execute without materializing agents") {
  const auto root = make_tmp("agent-reader");
  const auto image = root / "session.bvpk";
  const auto dest = root / "restore";
  const auto data = bytes("session-data");
  const biv::container::MemberMeta meta{.path = "agents/codex/session.jsonl",
                                        .kind = biv::scan::NodeKind::file,
                                        .mode = 0600,
                                        .mtime_s = 1,
                                        .mtime_ns = 0,
                                        .size = data.size(),
                                        .symlink_target = {}};
  biv::manifest::Checksums checksums;
  checksums.entries[meta.path] = payload_extent_digest(meta, data);
  write_bivpak(image, session_manifest(), checksums, {{.meta = meta, .data = data}});

  auto plan = biv::open::plan_open({.image = image, .dest = dest, .verify = true});
  REQUIRE(plan);
  REQUIRE(plan->manifest().agent_sessions.size() == 1U);
  REQUIRE(plan->agent_members().members.size() == 1U);
  auto reader = plan->make_reader();
  auto report = biv::open::execute_open(std::move(*plan), {.collision = biv::open::Collision::refuse});
  REQUIRE(report);
  auto read = reader(meta.path);
  REQUIRE(read);
  CHECK(*read == data);
  CHECK_FALSE(std::filesystem::exists(dest / "agents"));
  std::filesystem::remove_all(root);
}

TEST_CASE("open rejects checksummed unreferenced agent members") {
  const auto root = make_tmp("agent-smuggle");
  const auto image = root / "smuggle.bvpk";
  const auto data = bytes("smuggled");
  const biv::container::MemberMeta meta{.path = "agents/codex/smuggled.jsonl",
                                        .kind = biv::scan::NodeKind::file,
                                        .mode = 0600,
                                        .mtime_s = 1,
                                        .mtime_ns = 0,
                                        .size = data.size(),
                                        .symlink_target = {}};
  biv::manifest::Checksums checksums;
  checksums.entries[meta.path] = payload_extent_digest(meta, data);
  write_bivpak(image, manifest_model(), checksums, {{.meta = meta, .data = data}});

  auto opened = biv::open::plan_open({.image = image, .dest = root / "restore"});
  REQUIRE_FALSE(opened);
  CHECK(opened.error().kind == biv::ErrKind::UnmanifestedMember);
  std::filesystem::remove_all(root);
}

TEST_CASE("open rejects missing and non-regular referenced agent members") {
  const auto root = make_tmp("agent-invalid");
  const auto missing_image = root / "missing.bvpk";
  write_bivpak(missing_image, session_manifest(), {}, {});
  auto missing = biv::open::plan_open({.image = missing_image, .dest = root / "missing"});
  REQUIRE_FALSE(missing);
  CHECK(missing.error().kind == biv::ErrKind::IntegrityFailurePreApply);

  const auto link_image = root / "link.bvpk";
  const biv::container::MemberMeta link{.path = "agents/codex/session.jsonl",
                                        .kind = biv::scan::NodeKind::symlink,
                                        .mode = 0777,
                                        .mtime_s = 1,
                                        .mtime_ns = 0,
                                        .size = 0,
                                        .symlink_target = "../../escape"};
  biv::manifest::Checksums checksums;
  checksums.entries[link.path] = payload_extent_digest(link, {});
  write_bivpak(link_image, session_manifest(), checksums, {{.meta = link, .data = {}}});
  auto linked = biv::open::plan_open({.image = link_image, .dest = root / "link"});
  REQUIRE_FALSE(linked);
  CHECK(linked.error().kind == biv::ErrKind::MemberPathUnsafe);
  std::filesystem::remove_all(root);
}
