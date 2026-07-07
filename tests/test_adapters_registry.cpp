#include <algorithm>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "adapters/registry.hpp"

TEST_CASE("Adapter registry exposes Claude and Codex adapters") {
  const auto adapters = biv::adapters::all_adapters();

  REQUIRE(adapters.size() == 2);
  REQUIRE(biv::adapters::find_adapter("claude-code") != nullptr);
  REQUIRE(biv::adapters::find_adapter("codex") != nullptr);
  REQUIRE(biv::adapters::find_adapter("nope") == nullptr);

  const auto inventory = biv::adapters::find_adapter("claude-code")->state_inventory();
  CHECK(std::ranges::find(inventory.never_collect, ".credentials.json") != inventory.never_collect.end());
  const auto codex_inventory = biv::adapters::find_adapter("codex")->state_inventory();
  CHECK(std::ranges::find(codex_inventory.never_collect, "auth.json") != codex_inventory.never_collect.end());
}
