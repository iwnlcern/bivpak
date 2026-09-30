#include <array>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <sys/stat.h>
#include <unistd.h>

#include <catch2/catch_test_macros.hpp>

#include "cli_run.hpp"

namespace {

class WiringEnv {
 public:
  WiringEnv(std::string name, std::string value) : name_{std::move(name)} {
    if (const char* prior = std::getenv(name_.c_str())) prior_ = prior;
    REQUIRE(::setenv(name_.c_str(), value.c_str(), 1) == 0);
  }
  ~WiringEnv() {
    if (prior_) (void)::setenv(name_.c_str(), prior_->c_str(), 1);
    else (void)::unsetenv(name_.c_str());
  }

 private:
  std::string name_;
  std::optional<std::string> prior_;
};

std::filesystem::path wiring_tmp(std::string_view name) {
  static unsigned sequence = 0;
  const auto path = std::filesystem::temp_directory_path() /
                    ("biv-wiring-" + std::string{name} + "-" +
                     std::to_string(::getpid()) + "-" +
                     std::to_string(++sequence));
  std::filesystem::remove_all(path);
  std::filesystem::create_directories(path);
  return path;
}

void wiring_write(const std::filesystem::path& path, std::string_view bytes) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out{path, std::ios::binary};
  REQUIRE(out);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  REQUIRE(out.good());
}

void wiring_receipt(std::string_view id,
                    std::string_view detection = "product") {
  const char* directory = std::getenv("BIV_LEG_RECEIPTS");
  if (directory == nullptr || *directory == '\0') return;
  const auto path = std::filesystem::path{directory} /
                    (std::string{id} + ".txt");
  std::ofstream out{path, std::ios::trunc};
  REQUIRE(out);
  out << "leg=" << id << " provenance=product-packed verdict=PASS";
  if (detection == "shim") out << " detection=shim";
  out << '\n';
}

std::pair<std::pair<std::int64_t, std::int64_t>, std::uint32_t> node_facts(
    const std::filesystem::path& path) {
  struct stat status {};
  REQUIRE(::lstat(path.c_str(), &status) == 0);
#if defined(__APPLE__)
  return {{status.st_mtimespec.tv_sec, status.st_mtimespec.tv_nsec},
          static_cast<std::uint32_t>(status.st_mode & 07777U)};
#else
  return {{status.st_mtim.tv_sec, status.st_mtim.tv_nsec},
          static_cast<std::uint32_t>(status.st_mode & 07777U)};
#endif
}

std::vector<std::pair<std::filesystem::path, std::string>> tree_bytes(
    const std::filesystem::path& root) {
  std::vector<std::pair<std::filesystem::path, std::string>> rows;
  for (const auto& item : std::filesystem::recursive_directory_iterator(root)) {
    if (item.is_regular_file()) {
      rows.emplace_back(item.path().lexically_relative(root),
                        read_text(item.path()));
    }
  }
  std::ranges::sort(rows);
  return rows;
}

std::string q(const std::filesystem::path& path) {
  return GitFixture::quote(path.string());
}

void require_kind(const RunResult& result, std::string_view kind) {
  INFO(result.out);
  INFO(result.err);
  CHECK(result.out.find("\"kind\": \"" + std::string{kind} + "\"") !=
        std::string::npos);
}

struct PackedRemoteImage {
  std::filesystem::path root;
  GitFixture fixture;
  std::filesystem::path remote;
  std::filesystem::path source;
  std::filesystem::path image;
  std::string requested_url;
};

PackedRemoteImage pack_remote_image(const std::filesystem::path& root) {
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  const auto source = fixture.init_work(remote, root / "workspace/repo");
  const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  return {.root = root,
          .fixture = fixture,
          .remote = remote,
          .source = source,
          .image = root / "workspace.bvpk",
          .requested_url = "file://" + remote.generic_string()};
}

std::filesystem::path enclosing_repo_with_rewrite(
    PackedRemoteImage& packed, const std::filesystem::path& enclosing) {
  const auto other = packed.root / "other.git";
  packed.fixture.command("clone --bare " +
                         GitFixture::quote(packed.requested_url) + " " +
                         q(other));
  std::filesystem::create_directories(enclosing);
  packed.fixture.command("init -b main", enclosing);
  packed.fixture.set_instead_of(enclosing, packed.requested_url,
                                "file://" + other.generic_string());
  return other;
}

}  // namespace

TEST_CASE("c7 real CLI round trip restores branch refs and penumbra",
          "[wiring][round-trip]") {
  const auto root = wiring_tmp("round-trip");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  const auto source = fixture.init_work(remote, root / "workspace/repo");
  REQUIRE(fixture.output("status --porcelain=v2", source).empty());

  const auto packed = run_cmd("pack " + q(root / "workspace") +
                                  " --offline --json",
                              root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  const auto image = root / "workspace.bvpk";
  REQUIRE(std::filesystem::is_regular_file(image));

  const auto opened = run_cmd("open " + q(image) + " --dest " +
                                  q(root / "restored") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  const auto restored = root / "restored/repo";
  CHECK(fixture.output("status --porcelain=v2", restored).empty());
  CHECK(fixture.output("symbolic-ref --short HEAD", restored) == "main\n");
  CHECK(fixture.output("rev-parse local-topic", restored) ==
        fixture.output("rev-parse local-topic", source));
  CHECK(read_text(restored / "ignored.log") == read_text(source / "ignored.log"));
  CHECK(node_facts(restored / "ignored.log") == node_facts(source / "ignored.log"));
  CHECK(opened.out.find("\"recreated\": true") != std::string::npos);
  wiring_receipt("R-T");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 root repository penumbra is payload and lands after checkout",
          "[wiring][root-row]") {
  const auto root = wiring_tmp("root-row");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  const auto source = fixture.init_work(remote, root / "workspace");
  wiring_write(source / "tracked-dir/inside.txt", "inside\n");
  fixture.command("add tracked-dir/inside.txt", source);
  fixture.command("-c user.name='Wiring Fixture' -c user.email=wiring@example.invalid commit -m nested", source);
  wiring_write(source / ".gitignore", "ignored.log\ntracked-dir/*.tmp\n");
  fixture.command("add .gitignore", source);
  fixture.command("-c user.name='Wiring Fixture' -c user.email=wiring@example.invalid commit -m ignore", source);
  wiring_write(source / "tracked-dir/ignored.tmp", "nested ignored\n");
  REQUIRE(fixture.output("status --porcelain=v2", source).empty());

  const auto packed = run_cmd("pack " + q(source) + " --offline --json", root);
  REQUIRE(packed.code == 0);
  const auto opened = run_cmd("open " + q(root / "workspace.bvpk") +
                                  " --dest " + q(root / "restored") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(read_text(root / "restored/ignored.log") == "ignored bytes\n");
  CHECK(read_text(root / "restored/tracked-dir/ignored.tmp") ==
        "nested ignored\n");
  CHECK(fixture.output("status --porcelain=v2", root / "restored").empty());
  wiring_receipt("root-row");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 shallow and zero-ref unborn rows restore whole trees without git",
          "[wiring][N-a][H]") {
  const auto root = wiring_tmp("structural");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  fixture.init_work(remote, root / "seed");
  std::filesystem::create_directories(root / "workspace");
  fixture.command("clone --depth 1 " + GitFixture::quote("file://" + remote.generic_string()) +
                      " " + q(root / "workspace/shal"));
  wiring_write(root / "workspace/shal/ignored.log", "shallow ignored\n");
  std::filesystem::create_directories(root / "workspace/fresh");
  fixture.command("init -b main", root / "workspace/fresh");
  wiring_write(root / "workspace/fresh/sub/f.txt", "fresh bytes\n");

  const auto packed = run_cmd("pack " + q(root / "workspace") +
                                  " --offline --json",
                              root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  const auto trace = root / "git-trace";
  const auto bin = fixture.shim_path(trace);
  const char* inherited = std::getenv("PATH");
  REQUIRE(inherited != nullptr);
  WiringEnv path{"PATH", bin.string() + ":" + inherited};
  const auto image = root / "workspace.bvpk";
  for (const auto& [name, flag] :
       std::array<std::pair<std::string, std::string>, 2>{{
           {"online", "--network"}, {"offline", "--offline"}}}) {
    wiring_write(trace, "");
    const auto dest = root / name;
    const auto opened = run_cmd("open " + q(image) + " --dest " + q(dest) +
                                    " " + flag + " --json",
                                root);
    INFO(opened.out);
    INFO(opened.err);
    REQUIRE(opened.code == 0);
    CHECK(opened.out.find("\"outcome\": \"shallow-pointer\"") !=
          std::string::npos);
    CHECK(opened.out.find("\"outcome\": \"payload-only-unborn\"") !=
          std::string::npos);
    CHECK(read_text(trace).empty());
    for (const auto& rel : {std::string{"shal/tracked.txt"},
                            std::string{"shal/ignored.log"},
                            std::string{"fresh/sub/f.txt"}}) {
      CHECK(read_text(dest / rel) == read_text(root / "workspace" / rel));
      CHECK(node_facts(dest / rel) == node_facts(root / "workspace" / rel));
    }
    CHECK_FALSE(std::filesystem::exists(dest / "shal/.git"));
    CHECK_FALSE(std::filesystem::exists(dest / "fresh/.git"));
  }
  wiring_receipt("N-a");
  wiring_receipt("H-payload-only-unborn");
  wiring_receipt("E4-parity");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 pack URL divergence is fail-safe interactive and flag-scoped",
          "[wiring][M-a][a6][E3]") {
  const auto root = wiring_tmp("pack-divergence");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  const auto source = fixture.init_work(remote, root / "workspace/repo");
  const auto effective = root / "effective.git";
  fixture.command("clone --bare " + GitFixture::quote("file://" + remote.generic_string()) +
                      " " + q(effective));
  const auto requested_url = "file://" + remote.generic_string();
  const auto effective_url = "file://" + effective.generic_string();
  fixture.set_instead_of(source, requested_url, effective_url);
  REQUIRE(fixture.output("remote get-url origin", source) == effective_url + "\n");
  const auto trace = root / "git-trace";
  const auto bin = fixture.shim_path(trace);
  const char* inherited = std::getenv("PATH");
  REQUIRE(inherited != nullptr);
  WiringEnv path{"PATH", bin.string() + ":" + inherited};

  const auto refused = run_cmd("pack " + q(root / "workspace") + " --json", root);
  INFO(refused.out);
  INFO(refused.err);
  REQUIRE(refused.code == 3);
  require_kind(refused, "UrlDivergenceRefused");
  CHECK(refused.out.find(requested_url) != std::string::npos);
  CHECK(refused.out.find(effective_url) != std::string::npos);
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk"));
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk.partial"));
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk.scratch"));

  const auto pty_refused = run_cmd_pty_split(
      "pack " + q(root / "workspace"), root, "n\n");
  CHECK(pty_refused.stdin_tty);
  CHECK_FALSE(pty_refused.stdout_tty);
  CHECK(pty_refused.stderr_tty);
  CHECK(pty_refused.code == 3);
  CHECK(pty_refused.err.find("Contact the effective address? [y/N]") !=
        std::string::npos);

  const auto accepted = run_cmd("pack " + q(root / "workspace") +
                                    " --accept-url-divergence --json",
                                root);
  INFO(accepted.out);
  INFO(accepted.err);
  REQUIRE(accepted.code == 0);
  CHECK(accepted.out.find("url-divergence-accepted") != std::string::npos);
  CHECK(accepted.out.find(requested_url) != std::string::npos);
  CHECK(accepted.out.find(effective_url) != std::string::npos);
  const auto inspected = run_cmd("open " + q(root / "workspace.bvpk") +
                                     " --dest " + q(root / "inspect") +
                                     " --offline --json",
                                 root);
  REQUIRE(inspected.code == 0);
  CHECK(inspected.out.find(requested_url) != std::string::npos);
  CHECK(inspected.out.find(effective_url) == std::string::npos);
  wiring_receipt("M-a");
  wiring_receipt("M-a-interactive");
  wiring_receipt("M-d-pack");
  wiring_receipt("M-h");
  wiring_receipt("E3-macos");
  wiring_receipt("a6-1");
  wiring_receipt("a6-2");
  wiring_receipt("a6-7");
  wiring_receipt("a6-11");
  wiring_receipt("a6-13");
  wiring_receipt("a7-3");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 pack detects a global configured-url rewrite",
          "[wiring][M-h-global][W-U2]") {
  const auto root = wiring_tmp("pack-global-divergence");
  const auto global_home = root / "global-home";
  WiringEnv home{"HOME", global_home.string()};
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  fixture.init_work(remote, root / "workspace/repo");
  const auto effective = root / "effective.git";
  const auto requested_url = "file://" + remote.generic_string();
  const auto effective_url = "file://" + effective.generic_string();
  fixture.command("clone --bare " + GitFixture::quote(requested_url) + " " +
                  q(effective));
  fixture.temp_home_with_instead_of(global_home, requested_url, effective_url);

  const auto refused = run_cmd("pack " + q(root / "workspace") + " --json", root);
  INFO(refused.out);
  INFO(refused.err);
  REQUIRE(refused.code == 3);
  require_kind(refused, "UrlDivergenceRefused");
  CHECK(refused.out.find(requested_url) != std::string::npos);
  CHECK(refused.out.find(effective_url) != std::string::npos);
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk"));
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk.partial"));
  CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk.scratch"));

  const auto accepted = run_cmd("pack " + q(root / "workspace") +
                                    " --accept-url-divergence --json",
                                root);
  INFO(accepted.out);
  INFO(accepted.err);
  REQUIRE(accepted.code == 0);
  CHECK(accepted.out.find("url-divergence-accepted") != std::string::npos);
  const auto inspected = run_cmd("open " + q(root / "workspace.bvpk") +
                                     " --dest " + q(root / "inspect") +
                                     " --offline --json",
                                 root);
  REQUIRE(inspected.code == 0);
  CHECK(inspected.out.find(requested_url) != std::string::npos);
  CHECK(inspected.out.find(effective_url) == std::string::npos);
  wiring_receipt("M-h-global");
  wiring_receipt("W-U2");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 open divergence produces per-entry refusal and explicit acceptance",
          "[wiring][M-g]") {
  const auto root = wiring_tmp("open-divergence");
  const auto pack_home = root / "pack-home";
  std::filesystem::create_directories(pack_home);
  WiringEnv home{"HOME", pack_home.string()};
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  fixture.init_work(remote, root / "workspace/repo");
  const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);

  const auto requested_url = "file://" + remote.generic_string();
  const std::string effective_url{"https://effective.invalid/repo"};
  const auto shim_root = root / "labelled-shim";
  const auto trace = shim_root / "trace";
  const auto bin = fixture.labelled_divergence_shim(shim_root);
  const char* inherited = std::getenv("PATH");
  REQUIRE(inherited != nullptr);
  WiringEnv path{"PATH", bin.string() + ":" + inherited};
  const auto image = root / "workspace.bvpk";

  const auto refused = run_cmd("open " + q(image) + " --dest " +
                                   q(root / "refused") +
                                   " --network --json",
                               root);
  INFO(refused.out);
  INFO(refused.err);
  REQUIRE(refused.code == 2);
  CHECK(refused.out.find("UrlDivergenceEntryRefused") != std::string::npos);
  CHECK(refused.out.find(requested_url) != std::string::npos);
  CHECK(refused.out.find(effective_url) != std::string::npos);
  CHECK(refused.out.find("\"error\": null") != std::string::npos);

  wiring_write(trace, "");
  const auto accepted = run_cmd(
      "open " + q(image) + " --dest " + q(root / "accepted") +
          " --network --accept-url-divergence --json",
      root);
  INFO(accepted.out);
  INFO(accepted.err);
  REQUIRE(accepted.code == 0);
  CHECK(accepted.out.find("url-divergence-accepted") != std::string::npos);
  CHECK(read_text(root / "accepted/repo/ignored.log") == "ignored bytes\n");
  wiring_receipt("M-g", "shim");
  wiring_receipt("M-d-open", "shim");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 W-1-prime bounds restore below an enclosing repository",
          "[wiring][ISO][W-1-prime][W-C1]") {
  const auto root = wiring_tmp("restore-enclosing");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  auto packed = pack_remote_image(root);
  const auto enclosing = root / "encl";
  enclosing_repo_with_rewrite(packed, enclosing);

  const auto opened = run_cmd("open " + q(packed.image) + " --dest " +
                                  q(enclosing / "sub/out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("UrlDivergenceEntryRefused") == std::string::npos);
  CHECK(opened.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(opened.err.find("would contact") == std::string::npos);
  CHECK(packed.fixture.output("config --get remote.origin.url",
                              enclosing / "sub/out/repo") ==
        packed.requested_url + "\n");
  wiring_receipt("W-1-prime");
  wiring_receipt("W-C1");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 W-C2 leaves the enclosing repository byte-identical",
          "[wiring][ISO][W-C2]") {
  const auto root = wiring_tmp("restore-enclosing-host-write");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  auto packed = pack_remote_image(root);
  const auto enclosing = root / "encl";
  enclosing_repo_with_rewrite(packed, enclosing);
  const auto before = tree_bytes(enclosing / ".git");

  const auto opened = run_cmd("open " + q(packed.image) + " --dest " +
                                  q(enclosing / "sub/out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(tree_bytes(enclosing / ".git") == before);
  wiring_receipt("W-C2");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 W-C3 bounds restore through a symlinked destination",
          "[wiring][ISO][W-C3]") {
  const auto root = wiring_tmp("restore-enclosing-link");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  auto packed = pack_remote_image(root);
  const auto enclosing = root / "encl";
  enclosing_repo_with_rewrite(packed, enclosing);
  const auto link = root / "encl-link";
  std::filesystem::create_directory_symlink(enclosing, link);

  const auto opened = run_cmd("open " + q(packed.image) + " --dest " +
                                  q(link / "sub/out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("UrlDivergenceEntryRefused") == std::string::npos);
  CHECK(packed.fixture.output("config --get remote.origin.url",
                              enclosing / "sub/out/repo") ==
        packed.requested_url + "\n");
  wiring_receipt("W-C3");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 W-C4 is unchanged without an enclosing repository",
          "[wiring][ISO][W-C4]") {
  const auto root = wiring_tmp("restore-no-enclosing-control");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  auto packed = pack_remote_image(root);

  const auto opened = run_cmd("open " + q(packed.image) + " --dest " +
                                  q(root / "plain/out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("UrlDivergenceEntryRefused") == std::string::npos);
  CHECK(packed.fixture.output("rev-parse HEAD", root / "plain/out/repo") ==
        packed.fixture.output("rev-parse HEAD", packed.source));
  wiring_receipt("W-C4");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 W-5 keeps accept-url-divergence inert when the gate is bounded",
          "[wiring][ISO][W-5]") {
  const auto root = wiring_tmp("restore-enclosing-flag-inert");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  auto packed = pack_remote_image(root);
  const auto enclosing = root / "encl";
  enclosing_repo_with_rewrite(packed, enclosing);

  const auto opened = run_cmd(
      "open " + q(packed.image) + " --dest " + q(enclosing / "sub/out") +
          " --network --accept-url-divergence --json",
      root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("url-divergence-accepted") == std::string::npos);
  CHECK(opened.err.find("would contact") == std::string::npos);
  CHECK(packed.fixture.output("config --get remote.origin.url",
                              enclosing / "sub/out/repo") ==
        packed.requested_url + "\n");
  wiring_receipt("W-5");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 restore isolation ignores a temporary HOME rewrite",
          "[wiring][ISO][W-2]") {
  const auto root = wiring_tmp("restore-temp-home");
  const auto pack_home = root / "pack-home";
  std::filesystem::create_directories(pack_home);
  WiringEnv home{"HOME", pack_home.string()};
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  fixture.init_work(remote, root / "workspace/repo");
  const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
  REQUIRE(packed.code == 0);
  const auto requested_url = "file://" + remote.generic_string();
  const auto other = root / "other.git";
  fixture.command("clone --bare " + GitFixture::quote(requested_url) + " " +
                  q(other));
  const auto restore_home = fixture.temp_home_with_instead_of(
      root / "restore-home", requested_url,
      "file://" + other.generic_string());
  WiringEnv restore_home_env{"HOME", restore_home.string()};

  const auto opened = run_cmd("open " + q(root / "workspace.bvpk") +
                                  " --dest " + q(root / "out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(opened.out.find("UrlDivergenceEntryRefused") == std::string::npos);
  CHECK(fixture.output("config --get remote.origin.url", root / "out/repo") ==
        requested_url + "\n");
  wiring_receipt("W-2");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 pack classifies an inner repository from its own configuration",
          "[wiring][ISO][W-C5]") {
  const auto root = wiring_tmp("pack-inner-config");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto outer_remote = fixture.init_bare(root / "outer.git");
  fixture.init_work(outer_remote, root / "outer");
  const auto inner_remote = root / "inner.git";
  fixture.init_bare(inner_remote);
  fixture.init_work(inner_remote, root / "outer/src");
  const auto inner_url = "file://" + inner_remote.generic_string();

  const auto packed = run_cmd("pack " + q(root / "outer/src") + " --json", root);
  INFO(packed.out);
  INFO(packed.err);
  REQUIRE(packed.code == 0);
  const auto opened = run_cmd("open " + q(root / "outer/src.bvpk") +
                                  " --dest " + q(root / "out") +
                                  " --network --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(fixture.output("config --get remote.origin.url", root / "out") ==
        inner_url + "\n");
  CHECK(fixture.output("config --get remote.origin.url", root / "out") !=
        "file://" + outer_remote.generic_string() + "\n");
  wiring_receipt("W-C5");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 offline pointer is durable and performs zero git",
          "[wiring][A10][RCPT-Q]") {
  const auto root = wiring_tmp("offline-pointer");
  WiringEnv home{"HOME", (root / "home").string()};
  std::filesystem::create_directories(root / "home");
  GitFixture fixture{.root = root};
  const auto remote = fixture.init_bare(root / "remote.git");
  fixture.init_work(remote, root / "workspace/repo");
  const auto packed = run_cmd("pack " + q(root / "workspace") +
                                  " --offline --json",
                              root);
  REQUIRE(packed.code == 0);
  const auto trace = root / "git-trace";
  const auto bin = fixture.shim_path(trace);
  const char* inherited = std::getenv("PATH");
  REQUIRE(inherited != nullptr);
  WiringEnv path{"PATH", bin.string() + ":" + inherited};
  const auto opened = run_cmd("open " + q(root / "workspace.bvpk") +
                                  " --dest " + q(root / "out") +
                                  " --offline --json",
                              root);
  INFO(opened.out);
  INFO(opened.err);
  REQUIRE(opened.code == 0);
  CHECK(read_text(trace).empty());
  CHECK(opened.out.find("\"outcome\": \"offline-pointer\"") !=
        std::string::npos);
  CHECK(opened.out.find("\"bundle_path\": \".biv/repos/") !=
        std::string::npos);
  CHECK(std::filesystem::is_regular_file(
      root / "out/.biv/repos/repo/repo.bundle"));
  CHECK(read_text(root / "out/repo/ignored.log") == "ignored bytes\n");
  wiring_receipt("A10-offline");
  wiring_receipt("RCPT-Q");
  std::filesystem::remove_all(root);
}

TEST_CASE("c7 discovery fences dirty nested and unclaimed repositories",
          "[wiring][discovery][A11]") {
  SECTION("dirty") {
    const auto root = wiring_tmp("dirty");
    WiringEnv home{"HOME", (root / "home").string()};
    std::filesystem::create_directories(root / "home");
    GitFixture fixture{.root = root};
    const auto remote = fixture.init_bare(root / "remote.git");
    fixture.init_work(remote, root / "workspace/repo");
    wiring_write(root / "workspace/repo/untracked.txt", "dirty\n");
    const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
    REQUIRE(packed.code == 3);
    require_kind(packed, "RepoDirtyUnsupported");
    CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk"));
    wiring_receipt("A11-dirty");
    std::filesystem::remove_all(root);
  }

  SECTION("nested") {
    const auto root = wiring_tmp("nested");
    WiringEnv home{"HOME", (root / "home").string()};
    std::filesystem::create_directories(root / "home");
    GitFixture fixture{.root = root};
    const auto remote = fixture.init_bare(root / "remote.git");
    fixture.init_work(remote, root / "workspace/parent");
    std::filesystem::create_directories(root / "workspace/parent/child");
    fixture.command("init -b main", root / "workspace/parent/child");
    wiring_write(root / "workspace/parent/child/a.txt", "child\n");
    fixture.command("add a.txt", root / "workspace/parent/child");
    fixture.command("-c user.name='Wiring Fixture' -c user.email=wiring@example.invalid commit -m child",
                    root / "workspace/parent/child");
    const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
    REQUIRE(packed.code == 3);
    require_kind(packed, "RepoNestedUnsupported");
    CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk"));
    wiring_receipt("A11-nested");
    wiring_receipt("F-NESTED");
    std::filesystem::remove_all(root);
  }

  SECTION("unclaimed git symlink") {
    const auto root = wiring_tmp("unclaimed");
    std::filesystem::create_directories(root / "workspace/plain");
    std::filesystem::create_symlink("missing", root / "workspace/plain/.git");
    const auto packed = run_cmd("pack " + q(root / "workspace") + " --json", root);
    REQUIRE(packed.code == 3);
    require_kind(packed, "UnclaimedGitEntry");
    CHECK(packed.out.find("\"reason\": \"symlink\"") != std::string::npos);
    CHECK_FALSE(std::filesystem::exists(root / "workspace.bvpk"));
    wiring_receipt("F-UNCLAIMED");
    std::filesystem::remove_all(root);
  }
}
