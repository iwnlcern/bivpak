#include <algorithm>
#include <array>
#include <cstddef>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <optional>
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
#include "core/repo/git.hpp"
#include "core/support/sha256.hpp"

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

class ScopedEnv {
 public:
  ScopedEnv(std::string name, std::string value) : name_{std::move(name)} {
    if (const char* old = std::getenv(name_.c_str())) old_ = std::string{old};
    setenv(name_.c_str(), value.c_str(), 1);
  }
  ~ScopedEnv() {
    if (old_) setenv(name_.c_str(), old_->c_str(), 1);
    else unsetenv(name_.c_str());
  }
 private:
  std::string name_;
  std::optional<std::string> old_;
};

biv::repo::Git test_git() {
  auto git = biv::repo::Git::resolve([](const std::string_view name) -> std::optional<std::string> {
    if (const char* value = std::getenv(std::string{name}.c_str())) return std::string{value};
    return std::nullopt;
  });
  REQUIRE(git);
  return *git;
}

void init_repo(const biv::repo::Git& git, const std::filesystem::path& path) {
  std::filesystem::create_directories(path);
  auto run = [&](std::vector<std::string> args) {
    auto result = git.run(args, {}, {.cwd = path,
                                     .ceiling = std::nullopt,
                                     .allow_user_protocol = true,
                                     .stdout_file = std::nullopt});
    REQUIRE(result);
    REQUIRE(result->exit_code == 0);
  };
  run({"init", "-b", "main"});
  write_file(path / "tracked.txt", "tracked\n");
  run({"add", "tracked.txt"});
  run({"-c", "user.name=Biv Test", "-c", "user.email=biv@example.invalid",
       "commit", "-m", "initial"});
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

  const auto serialized = biv::manifest::serialize(manifest);
  REQUIRE(serialized.has_value());
  const auto& manifest_json = *serialized;
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

std::vector<std::byte> decompress_image(const std::filesystem::path& image) {
  const auto text = read_binary_or_throw(image);
  const auto compressed = std::as_bytes(std::span<const char>{text.data(), text.size()});
  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return compressed;
  }};
  std::vector<std::byte> raw;
  while (true) {
    auto chunk = source.pull();
    REQUIRE(chunk);
    if (chunk->empty()) {
      break;
    }
    raw.insert(raw.end(), chunk->begin(), chunk->end());
  }
  return raw;
}

void recompute_header_checksum(std::span<std::byte> header) {
  std::fill(header.begin() + 148, header.begin() + 156, static_cast<std::byte>(' '));
  uint64_t sum = 0;
  for (const auto value : header) {
    sum += std::to_integer<unsigned char>(value);
  }
  std::array<char, 8> encoded{};
  std::snprintf(encoded.data(), encoded.size(), "%06llo", static_cast<unsigned long long>(sum));
  for (size_t index = 0; index < 6; ++index) {
    header[148 + index] = static_cast<std::byte>(encoded[index]);
  }
  header[154] = std::byte{0};
  header[155] = static_cast<std::byte>(' ');
}

void mutate_member_header(const std::filesystem::path& image,
                          const std::string_view member,
                          const std::function<void(std::span<std::byte>)>& mutate) {
  auto raw = decompress_image(image);
  bool found = false;
  for (size_t offset = 0; offset + 512U <= raw.size(); offset += 512U) {
    auto header = std::span<std::byte>{raw}.subspan(offset, 512U);
    std::string name;
    for (size_t index = 0; index < 100U && header[index] != std::byte{0}; ++index) {
      name.push_back(static_cast<char>(header[index]));
    }
    if (name == member) {
      mutate(header);
      recompute_header_checksum(header);
      found = true;
      break;
    }
  }
  REQUIRE(found);
  std::ofstream out{image, std::ios::binary | std::ios::trunc};
  biv::container::ZstdCompressSink zstd{[&](std::span<const std::byte> chunk) -> biv::expected<void> {
    out.write(reinterpret_cast<const char*>(chunk.data()), static_cast<std::streamsize>(chunk.size()));
    return {};
  }};
  REQUIRE(zstd.as_sink()(raw));
  REQUIRE(zstd.finish());
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

TEST_CASE("open treats dangling destination leaves as occupied names") {
  const auto root = make_tmp("dangling-destination");
  const auto image = make_image(root);
  const auto dest = root / "restore";
  std::filesystem::create_symlink(root / "missing-target", dest);

  auto renamed = biv::open::open(
      biv::open::OpenOptions{.image = image,
                             .dest = dest,
                             .collision = biv::open::Collision::rename});

  REQUIRE(renamed.has_value());
  CHECK(renamed->output_dir == (root / "restore(1)").generic_string());
  CHECK(read_text(root / "restore(1)" / "a.txt") == "alpha");
  CHECK(std::filesystem::is_symlink(dest));
  CHECK_FALSE(std::filesystem::exists(root / "restore.bvpk-open.partial"));
  std::filesystem::remove_all(root);
}

TEST_CASE("open skips dangling rename candidates") {
  const auto root = make_tmp("dangling-rename-candidate");
  const auto image = make_image(root);
  const auto dest = root / "restore";
  std::filesystem::create_directories(dest);
  std::filesystem::create_symlink(root / "missing-target",
                                  root / "restore(1)");

  auto renamed = biv::open::open(
      biv::open::OpenOptions{.image = image,
                             .dest = dest,
                             .collision = biv::open::Collision::rename});

  REQUIRE(renamed.has_value());
  CHECK(renamed->output_dir == (root / "restore(2)").generic_string());
  CHECK(read_text(root / "restore(2)" / "a.txt") == "alpha");
  CHECK(std::filesystem::is_symlink(root / "restore(1)"));
  CHECK_FALSE(std::filesystem::exists(
      root / "restore(1).bvpk-open.partial"));
  std::filesystem::remove_all(root);
}

TEST_CASE("Task 4 open occupancy and destination contracts stay bounded") {
  {
    const auto source =
        read_text(std::filesystem::path{BIV_SOURCE_DIR} / "src" / "core" /
                  "open" / "open.cpp");

    CHECK(source.find(
              "std::filesystem::exists(\n"
              "            std::filesystem::symlink_status(candidate, ec))") !=
          std::string::npos);
    CHECK(source.find(
              "std::filesystem::exists(std::filesystem::symlink_status(dest, "
              "ec))") != std::string::npos);

    const auto plan_begin =
        source.find("expected<OpenPlanHandle> plan_open");
    const auto plan_end =
        source.find("expected<OpenReport> execute_open", plan_begin);
    REQUIRE(plan_begin != std::string::npos);
    REQUIRE(plan_end != std::string::npos);
    const auto plan_source =
        source.substr(plan_begin, plan_end - plan_begin);
    const auto write_begin = source.find("const auto partial_dir =");
    const auto write_end = source.find("\n}\n", write_begin);
    REQUIRE(write_begin != std::string::npos);
    REQUIRE(write_end != std::string::npos);
    const auto write_path = source.substr(write_begin, write_end - write_begin);
    // Catch premature writes/publication and writers aimed at the destination.
    constexpr std::array<std::string_view, 7> calls{
        "std::filesystem::exists(partial_dir, ec)",
        "std::filesystem::create_directories(partial_dir, ec)",
        "apply_archive(image, plan, partial_dir, dirs, verify, stage, row_rels)",
        "restore_repos(image, plan, partial_dir, stage, dirs, verify, report)",
        "set_mtime(partial_dir / std::filesystem::path{rel}, it->mtime_s, it->mtime_ns)",
        "fsync_tree(partial_dir)",
        "std::filesystem::rename(partial_dir, dest, ec)"};
    std::array<std::size_t, calls.size()> positions{};
    for (std::size_t index = 0; index < calls.size(); ++index) {
      INFO(calls[index]);
      positions[index] = write_path.find(calls[index]);
      REQUIRE(positions[index] != std::string::npos);
      CHECK(write_path.find(calls[index], positions[index] + 1) == std::string::npos);
      if (index != 0) CHECK(positions[index - 1] < positions[index]);
    }
    CHECK(write_path.find("ErrKind::OpenPartialPresent") != std::string::npos);
    CHECK(write_path.find("absolute") == std::string::npos);
    CHECK(write_path.find("weakly_canonical") == std::string::npos);
    const auto suffix = write_path.find("\".bvpk-open.partial\"");
    REQUIRE(suffix != std::string::npos);
    CHECK(write_path.find("\".bvpk-open.partial\"", suffix + 1) == std::string::npos);
    CHECK(plan_source.find(
              "options.dest.value_or(default_dest_for(options.image))"
              ".lexically_normal()") != std::string::npos);
    CHECK(plan_source.find("absolute") == std::string::npos);
    CHECK(plan_source.find("weakly_canonical") == std::string::npos);

    const auto owner_begin = source.find("std::optional<std::string> owning_row(");
    const auto owner_end = source.find("\n}\n", owner_begin);
    REQUIRE(owner_begin != std::string::npos);
    REQUIRE(owner_end != std::string::npos);
    const auto owner_source = source.substr(owner_begin, owner_end - owner_begin);
    CHECK(owner_source.find("payload_rel == row") != std::string::npos);
    CHECK(owner_source.find("payload_rel.at(row.size()) == '/'") !=
          std::string::npos);

    const auto restore_begin = source.find("expected<void> restore_repos(");
    const auto restore_end = source.find("\n}\n", restore_begin);
    REQUIRE(restore_begin != std::string::npos);
    REQUIRE(restore_end != std::string::npos);
    const auto restore_source =
        source.substr(restore_begin, restore_end - restore_begin);
    const auto restore_entry = restore_source.find("restore_entry(");
    const auto apply_owned = restore_source.find("apply_owned_members(");
    REQUIRE(restore_entry != std::string::npos);
    REQUIRE(apply_owned != std::string::npos);
    CHECK(restore_entry < apply_owned);
  }
}

TEST_CASE("c6p ownership rows and protected components are behavioral",
          "[open][c6p]") {
  using biv::open::detail::is_dotbiv_component;
  using biv::open::detail::is_dotgit_component;
  using biv::open::detail::owning_row;
  using biv::open::detail::row_relpaths;

  CHECK(owning_row("lib/x", {"lib"}) == std::optional<std::string>{"lib"});
  CHECK_FALSE(owning_row("libx/y", {"lib"}).has_value());
  CHECK(owning_row("a/b/c", {"a", "a/b"}) ==
        std::optional<std::string>{"a/b"});
  CHECK(owning_row("x", {""}) == std::optional<std::string>{""});
  CHECK_FALSE(owning_row("docs/inner", {"docs/inner"}).has_value());

  biv::repo::RepoEntry full;
  full.relpath = "lib";
  biv::repo::RepoEntry shallow;
  shallow.relpath = "shal";
  shallow.shallow = biv::repo::Shallow{};
  biv::repo::RepoEntry unborn;
  unborn.relpath = "fresh";
  unborn.head_state = biv::repo::HeadState::unborn;
  CHECK(row_relpaths({full, shallow, unborn}) ==
        std::vector<std::string>{"lib"});
  full.relpath = ".";
  CHECK(row_relpaths({full}) == std::vector<std::string>{""});

  const std::string zw_non_joiner{"\xE2\x80\x8C"};
  const std::string right_to_left_mark{"\xE2\x80\x8F"};
  const std::string byte_order_mark{"\xEF\xBB\xBF"};
  const std::string e_acute{"\xC3\xA9"};
  const std::string malformed =
      std::string{".g"} + static_cast<char>(0xFF) + "it";
  // Invalid UTF-8 never decodes into a protected alias: a continuation byte failing the mask (its low bits spell U+200C),
  // a 2-byte and a 3-byte overlong '.', and a truncated sequence.
  const std::string bad_continuation{"\xE2\x80\x0C"};
  const std::string overlong_dot_2{"\xC0\xAE"};
  const std::string overlong_dot_3{"\xE0\x80\xAE"};
  const std::string truncated{"\xE2\x80"};
  for (const auto& value : std::vector<std::string>{
           ".git", ".GIT", ".gIt", ".g" + zw_non_joiner + "it",
           byte_order_mark + ".git", ".git" + right_to_left_mark,
           "git~1", "GIT~1", ".git.", ".git ", ".git. .", ".git:x",
           "git~1:y"}) {
    INFO(value);
    CHECK(is_dotgit_component(value));
  }
  for (const auto& value : std::vector<std::string>{
           ".gitx", "git", ".gi", "x.git", ".git~1", "git~2",
           ".gitignore", ".g" + e_acute + "t", malformed,
           ".g" + bad_continuation + "it", overlong_dot_2 + "git",
           overlong_dot_3 + "git", ".git" + truncated}) {
    INFO(value);
    CHECK_FALSE(is_dotgit_component(value));
  }

  for (const auto& value : std::vector<std::string>{
           ".biv", ".BIV", ".bIv", ".b" + zw_non_joiner + "iv",
           byte_order_mark + ".biv", ".biv" + right_to_left_mark,
           "biv~1", "BIV~1", ".biv.", ".biv ", ".biv. .", ".biv:x",
           "biv~1:y"}) {
    INFO(value);
    CHECK(is_dotbiv_component(value));
  }
  for (const auto& value : std::vector<std::string>{
           ".bivx", "biv", ".bi", "x.biv", ".biv~1", "biv~2",
           ".bivignore", ".b" + e_acute + "v",
           std::string{".b"} + static_cast<char>(0xFF) + "iv",
           ".b" + bad_continuation + "iv", overlong_dot_2 + "biv",
           overlong_dot_3 + "biv", ".biv" + truncated}) {
    INFO(value);
    CHECK_FALSE(is_dotbiv_component(value));
  }
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

TEST_CASE("open engine failure leaves ordered failed-mid-apply inventory", "[a11-open]") {
  const auto root = make_tmp("a11-engine-inventory");
  const auto source = root / "source";
  const auto git = test_git();
  init_repo(git, source / "repo-a");
  init_repo(git, source / "repo-b");
  auto packed = biv::pack::pack(source, {.offline = true});
  REQUIRE(packed);
  const auto image = root / "source.bvpk";
  const auto dest = root / "restore";
  const auto partial = root / "restore.bvpk-open.partial";

  const auto shim_dir = root / "shim";
  const auto shim = shim_dir / "git";
  std::filesystem::create_directories(shim_dir);
  write_file(shim,
             "#!/bin/sh\n"
             "case \" $* \" in *'/repo-b '*) printf '%s\\n' 'hostile restore diagnostic' >&2; exit 42;; esac\n"
             "exec '" + git.executable().string() + "' \"$@\"\n");
  std::filesystem::permissions(
      shim, std::filesystem::perms::owner_read |
                std::filesystem::perms::owner_write |
                std::filesystem::perms::owner_exec);
  const ScopedEnv path{"PATH", shim_dir.string()};

  auto opened = biv::open::open({.image = image, .dest = dest});
  REQUIRE_FALSE(opened);
  CHECK(opened.error().kind == biv::ErrKind::RepoRestoreFailed);
  CHECK(opened.error().path == "repo-b");
  CHECK(opened.error().facts.at("repo_id").size() > 0U);
  CHECK(opened.error().facts.at("repo_relpath") == "repo-b");
  CHECK(opened.error().facts.at("partial_path") == partial.generic_string());
  CHECK(opened.error().facts.at("verb") == "open");
  CHECK(opened.error().facts.at("engine_detail") ==
        "RepoRestoreFailed: clone: hostile restore diagnostic");
  CHECK(opened.error().detail ==
        "open failed while restoring repo-b: clone: hostile restore diagnostic.");
  CHECK(std::filesystem::exists(partial / "inventory.json"));
  CHECK_FALSE(std::filesystem::exists(dest));
  const auto inventory = read_text(partial / "inventory.json");
  const auto completed = inventory.find("\"relpath\": \"repo-a\"");
  const auto failing = inventory.find("\"relpath\": \"repo-b\"");
  const auto outcome = inventory.find("\"kind\": \"failed-mid-apply\"");
  REQUIRE(completed != std::string::npos);
  REQUIRE(failing != std::string::npos);
  REQUIRE(outcome != std::string::npos);
  CHECK(completed < failing);
  CHECK(failing < outcome);
  CHECK(inventory.find("\"kind\": \"RepoRestoreFailed\"", failing) !=
        std::string::npos);
  CHECK(inventory.find("\"detail\": \"" + opened.error().detail + "\"", failing) !=
        std::string::npos);
  CHECK(inventory.find("\"sha\": ", completed) < failing);
  CHECK(inventory.find("\"capture_mode\": \"full\"", completed) < failing);
  CHECK(inventory.find("\"local_refs\": [", completed) < failing);
  CHECK(inventory.find("\"advisories\": [", completed) < failing);
  CHECK(inventory.find("\"step\": \"clone\"", outcome) != std::string::npos);
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
  auto unknown = reader("agents/codex/not-planned.jsonl");
  REQUIRE_FALSE(unknown);
  CHECK(unknown.error().kind == biv::ErrKind::UnmanifestedMember);
  auto report = biv::open::execute_open(std::move(*plan), {.collision = biv::open::Collision::refuse});
  REQUIRE(report);
  auto read = reader(meta.path);
  REQUIRE(read);
  CHECK(*read == data);
  CHECK_FALSE(std::filesystem::exists(dest / "agents"));
  std::filesystem::remove_all(root);
}

TEST_CASE("planned agent reader refuses bytes changed after planning") {
  const auto root = make_tmp("agent-reader-corrupt");
  const auto image = root / "session.bvpk";
  const auto good = bytes("session-data");
  const auto bad = bytes("tampered-dat");
  const biv::container::MemberMeta meta{.path = "agents/codex/session.jsonl",
                                        .kind = biv::scan::NodeKind::file,
                                        .mode = 0600,
                                        .mtime_s = 1,
                                        .mtime_ns = 0,
                                        .size = good.size(),
                                        .symlink_target = {}};
  biv::manifest::Checksums checksums;
  checksums.entries[meta.path] = payload_extent_digest(meta, good);
  write_bivpak(image, session_manifest(), checksums, {{.meta = meta, .data = good}});
  auto plan = biv::open::plan_open({.image = image, .dest = root / "restore", .verify = true});
  REQUIRE(plan);
  auto reader = plan->make_reader();
  write_bivpak(image, session_manifest(), checksums, {{.meta = meta, .data = bad}});

  auto read = reader(meta.path);
  REQUIRE_FALSE(read);
  CHECK(read.error().kind == biv::ErrKind::IntegrityFailurePreApply);
  CHECK(read.error().detail == "checksum");
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

  for (const char typeflag : {'1', '3', '6'}) {
    const auto kind_image = root / ("kind-" + std::string{typeflag} + ".bvpk");
    write_bivpak(kind_image, session_manifest(), checksums, {{.meta = biv::container::MemberMeta{
                                                                .path = "agents/codex/session.jsonl",
                                                                .kind = biv::scan::NodeKind::file,
                                                                .mode = 0600,
                                                                .mtime_s = 1,
                                                                .mtime_ns = 0,
                                                                .size = 0,
                                                                .symlink_target = {}},
                                                            .data = {}}});
    mutate_member_header(kind_image, "agents/codex/session.jsonl", [&](std::span<std::byte> header) {
      header[156] = static_cast<std::byte>(typeflag);
    });
    auto refused = biv::open::plan_open({.image = kind_image, .dest = root / "kind"});
    REQUIRE_FALSE(refused);
    CHECK(refused.error().kind == biv::ErrKind::MemberPathUnsafe);
  }

  const auto large_image = root / "large.bvpk";
  write_bivpak(large_image, session_manifest(), checksums, {{.meta = biv::container::MemberMeta{
                                                               .path = "agents/codex/session.jsonl",
                                                               .kind = biv::scan::NodeKind::file,
                                                               .mode = 0600,
                                                               .mtime_s = 1,
                                                               .mtime_ns = 0,
                                                               .size = 0,
                                                               .symlink_target = {}},
                                                           .data = {}}});
  mutate_member_header(large_image, "agents/codex/session.jsonl", [](std::span<std::byte> header) {
    constexpr std::string_view oversized = "00400000001";
    for (size_t index = 0; index < oversized.size(); ++index) {
      header[124 + index] = static_cast<std::byte>(oversized[index]);
    }
    header[135] = std::byte{0};
  });
  auto large = biv::open::plan_open({.image = large_image, .dest = root / "large"});
  REQUIRE_FALSE(large);
  CHECK(large.error().kind == biv::ErrKind::MemberPathUnsafe);
  CHECK(large.error().detail == "agent-member-size");
  std::filesystem::remove_all(root);
}
