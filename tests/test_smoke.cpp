#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include "core/support/version.hpp"

TEST_CASE("app version pin") {
  REQUIRE(std::string_view{biv::app_version()} == "0.1.0");
}
