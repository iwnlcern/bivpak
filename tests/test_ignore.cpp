#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include "core/ignore/builtin.hpp"
#include "core/ignore/matcher.hpp"

TEST_CASE("builtin-v1 bytes are pinned") {
  REQUIRE(std::string_view{biv::ignore::kBuiltinV1}.size() == 110);
  REQUIRE(std::string{biv::ignore::kBuiltinV1} ==
          "node_modules/\n"
          ".venv/\n"
          "venv/\n"
          "__pycache__/\n"
          "*.pyc\n"
          "target/\n"
          ".tox/\n"
          ".mypy_cache/\n"
          ".pytest_cache/\n"
          ".ruff_cache/\n"
          ".gradle/\n");
}

TEST_CASE("builtin matcher prunes directory patterns at any depth") {
  auto matcher = biv::ignore::Matcher::compile(biv::ignore::kBuiltinV1, true);
  REQUIRE(matcher.has_value());

  auto verdict = matcher->match("pkg/node_modules", true);
  REQUIRE(verdict.ignored);
  REQUIRE(verdict.source == "builtin-v1");

  REQUIRE_FALSE(matcher->match("pkg/node_modules", false).ignored);
  REQUIRE(matcher->match("a/b/c.pyc", false).ignored);
}

TEST_CASE("file matcher supports last-match negation and line provenance") {
  const std::string patterns = "*.pyc\n!keep.pyc\nbuild/\n/docs/*.tmp\n";
  auto matcher = biv::ignore::Matcher::compile(patterns, false);
  REQUIRE(matcher.has_value());

  REQUIRE(matcher->match("x/drop.pyc", false).ignored);
  REQUIRE(matcher->match("x/drop.pyc", false).source == ".bivignore:1");
  REQUIRE_FALSE(matcher->match("keep.pyc", false).ignored);

  auto build = matcher->match("sub/build", true);
  REQUIRE(build.ignored);
  REQUIRE(build.source == ".bivignore:3");

  REQUIRE(matcher->match("docs/a.tmp", false).ignored);
  REQUIRE_FALSE(matcher->match("sub/docs/a.tmp", false).ignored);
}

TEST_CASE("matcher supports double-star paths") {
  auto matcher = biv::ignore::Matcher::compile("logs/**/*.txt\n", false);
  REQUIRE(matcher.has_value());

  REQUIRE(matcher->match("logs/a/b/c.txt", false).ignored);
  REQUIRE_FALSE(matcher->match("other/logs/a.txt", false).ignored);
}
