#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <span>
#include <sys/stat.h>
#include <vector>

#include "core/support/portability.hpp"

namespace {

std::vector<std::size_t> entropy_chunk_sizes;

int fill_test_entropy(const std::span<unsigned char> bytes) {
  entropy_chunk_sizes.push_back(bytes.size());
  std::ranges::fill(bytes, 0x5A);
  return 0;
}

}  // namespace

TEST_CASE("secure_random_bytes honors bounds, chunking, and fallback") {
  SECTION("fills the requested region within bounds") {
    std::array<unsigned char, 18> canvas;
    canvas.fill(0xAB);

    biv::support::secure_random_bytes(canvas.data() + 1, 16);

    CHECK(canvas.front() == 0xAB);
    CHECK(canvas.back() == 0xAB);

    const auto written = std::span{canvas}.subspan(1, 16);
    CHECK(std::ranges::any_of(written,
                              [](const auto byte) { return byte != 0xAB; }));

    std::array<unsigned char, 16> second;
    second.fill(0xAB);
    biv::support::secure_random_bytes(second.data(), second.size());

    CHECK(std::ranges::any_of(second,
                              [](const auto byte) { return byte != 0xAB; }));
    CHECK_FALSE(std::ranges::equal(written, second));
  }

  SECTION("fills requests larger than getentropy's limit") {
    std::array<unsigned char, 300> bytes{};

    biv::support::secure_random_bytes(bytes.data(), bytes.size());

    CHECK(
        std::ranges::any_of(bytes, [](const auto byte) { return byte != 0; }));
  }

  SECTION("chunks getentropy requests at the platform limit") {
    std::array<unsigned char, 300> bytes{};
    entropy_chunk_sizes.clear();

    REQUIRE(
        biv::support::detail::fill_from_getentropy(bytes, fill_test_entropy));

    CHECK(entropy_chunk_sizes == std::vector<std::size_t>{256, 44});
    CHECK(std::ranges::all_of(bytes,
                              [](const auto byte) { return byte == 0x5A; }));
  }

  SECTION("fills independent random_device fallback sequences") {
    std::array<unsigned char, 32> first{};
    std::array<unsigned char, 32> second{};

    biv::support::detail::fill_from_random_device(first);
    biv::support::detail::fill_from_random_device(second);

    CHECK(
        std::ranges::any_of(first, [](const auto byte) { return byte != 0; }));
    CHECK(
        std::ranges::any_of(second, [](const auto byte) { return byte != 0; }));
    CHECK_FALSE(first == second);
  }
}

TEST_CASE("stat_mtime accessors return the struct's mtime fields") {
  struct stat st {};
#if defined(__APPLE__)
  st.st_mtimespec.tv_sec = 123456;
  st.st_mtimespec.tv_nsec = 789;
#else
  st.st_mtim.tv_sec = 123456;
  st.st_mtim.tv_nsec = 789;
#endif

  CHECK(biv::support::stat_mtime_sec(st) == 123456);
  CHECK(biv::support::stat_mtime_nsec(st) == 789U);
}
