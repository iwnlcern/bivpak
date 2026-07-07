#include <algorithm>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "adapters/registry.hpp"

TEST_CASE("Adapter registry exposes the Stage-A Claude adapter") {
  const auto adapters = biv::adapters::all_adapters();

  REQUIRE(adapters.size() == 1);
  REQUIRE(biv::adapters::find_adapter("claude-code") != nullptr);
  REQUIRE(biv::adapters::find_adapter("nope") == nullptr);

  const auto inventory = biv::adapters::find_adapter("claude-code")->state_inventory();
  CHECK(std::ranges::find(inventory.never_collect, ".credentials.json") != inventory.never_collect.end());
}
