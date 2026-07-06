#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/ignore/builtin.hpp"
#include "core/ignore/matcher.hpp"

namespace {

std::vector<std::string> split_tsv(const std::string& line) {
  std::vector<std::string> fields;
  std::stringstream stream{line};
  std::string field;
  while (std::getline(stream, field, '\t')) {
    fields.push_back(field);
  }
  if (!line.empty() && line.back() == '\t') {
    fields.emplace_back();
  }
  return fields;
}

std::string decode_field(std::string value) {
  std::string out;
  out.reserve(value.size());
  for (size_t i = 0; i < value.size(); ++i) {
    if (value.at(i) == '\\' && (i + 1U) < value.size() && value.at(i + 1U) == 's') {
      out.push_back(' ');
      ++i;
    } else {
      out.push_back(value.at(i));
    }
  }
  return out;
}

}  // namespace

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

  REQUIRE(matcher->match("logs/a.txt", false).ignored);
  REQUIRE(matcher->match("logs/a/b/c.txt", false).ignored);
  REQUIRE_FALSE(matcher->match("other/logs/a.txt", false).ignored);
}

TEST_CASE("matcher strips unescaped trailing spaces") {
  auto matcher = biv::ignore::Matcher::compile("build  \nliteral\\ \n", false);
  REQUIRE(matcher.has_value());

  REQUIRE(matcher->match("build", false).ignored);
  REQUIRE_FALSE(matcher->match("build  ", false).ignored);
  REQUIRE(matcher->match("literal ", false).ignored);
}

TEST_CASE("matcher replays ignore parity corpus") {
  const std::map<std::string, std::string> pattern_sets{
      {"builtin-v1", std::string{biv::ignore::kBuiltinV1}},
      {"custom-v1",
       "*.pyc\n"
       "!keep.pyc\n"
       "build/\n"
       "/docs/*.tmp\n"
       "logs/**/*.txt\n"
       "trail  \n"
       "literal\\ \n"
       "space name\n"
       "/root-only.tmp\n"
       "*.log\n"
       "!important/*.log\n"}};
  std::map<std::string, biv::ignore::Matcher> matchers;
  for (const auto& [name, patterns] : pattern_sets) {
    auto matcher = biv::ignore::Matcher::compile(patterns, name == "builtin-v1");
    REQUIRE(matcher.has_value());
    matchers.emplace(name, std::move(*matcher));
  }

  std::ifstream corpus{std::string{BIV_SOURCE_DIR} + "/tests/fixtures/ignore-parity/corpus.tsv"};
  REQUIRE(corpus);
  std::string line;
  REQUIRE(std::getline(corpus, line));
  REQUIRE(line == "pattern_set\tpath\tis_dir\tverdict\tsource");

  size_t rows = 0;
  while (std::getline(corpus, line)) {
    const auto fields = split_tsv(line);
    REQUIRE(fields.size() == 5);
    const auto& matcher = matchers.at(fields.at(0));
    const std::string path = decode_field(fields.at(1));
    const bool is_dir = fields.at(2) == "true";
    const bool ignored = fields.at(3) == "ignored";
    const std::string expected_source = fields.at(4) == "-" ? std::string{} : fields.at(4);
    const auto verdict = matcher.match(path, is_dir);
    CHECK(verdict.ignored == ignored);
    CHECK(verdict.source == expected_source);
    ++rows;
  }
  CHECK(rows >= 40);
}
