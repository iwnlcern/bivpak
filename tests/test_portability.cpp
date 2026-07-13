#include <catch2/catch_test_macros.hpp>

#include <array>
#include <sys/stat.h>

#include "core/support/portability.hpp"

TEST_CASE("secure_random_bytes writes within bounds and does not overrun") {
  std::array<unsigned char, 18> canvas;
  canvas.fill(0xAB);

  biv::support::secure_random_bytes(canvas.data() + 1, 16);

  CHECK(canvas.front() == 0xAB);
  CHECK(canvas.back() == 0xAB);
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
