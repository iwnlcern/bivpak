#include <cstdint>
#include <limits>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "core/json/writer.hpp"

TEST_CASE("Writer emits nested objects and arrays with stable formatting") {
  biv::json::Writer writer;
  writer.begin_object();
  writer.key("name");
  writer.value_string("biv");
  writer.key("items");
  writer.begin_array();
  writer.value_int(1);
  writer.value_bool(true);
  writer.begin_object();
  writer.key("ok");
  writer.value_null();
  writer.end_object();
  writer.end_array();
  writer.end_object();

  REQUIRE(writer.take() ==
          "{\n"
          "  \"name\": \"biv\",\n"
          "  \"items\": [\n"
          "    1,\n"
          "    true,\n"
          "    {\n"
          "      \"ok\": null\n"
          "    }\n"
          "  ]\n"
          "}\n");
}

TEST_CASE("Writer escapes required characters and passes through UTF-8") {
  biv::json::Writer writer;
  writer.begin_object();
  writer.key("s");
  writer.value_string("quote \" slash \\ newline \n tab \t snowman \xE2\x98\x83");
  writer.end_object();

  REQUIRE(writer.take() ==
          "{\n"
          "  \"s\": \"quote \\\" slash \\\\ newline \\u000A tab \\u0009 snowman \xE2\x98\x83\"\n"
          "}\n");
}

TEST_CASE("Writer renders empty containers compactly") {
  biv::json::Writer writer;
  writer.begin_object();
  writer.key("o");
  writer.begin_object();
  writer.end_object();
  writer.key("a");
  writer.begin_array();
  writer.end_array();
  writer.end_object();

  REQUIRE(writer.take() ==
          "{\n"
          "  \"o\": {},\n"
          "  \"a\": []\n"
          "}\n");
}

TEST_CASE("Writer emits int64 bounds and one trailing newline") {
  biv::json::Writer writer;
  writer.begin_array();
  writer.value_int(std::numeric_limits<std::int64_t>::min());
  writer.value_int(std::numeric_limits<std::int64_t>::max());
  writer.end_array();

  const std::string out = writer.take();
  REQUIRE(out ==
          "[\n"
          "  -9223372036854775808,\n"
          "  9223372036854775807\n"
          "]\n");
  REQUIRE(out.ends_with('\n'));
  REQUIRE(out[out.size() - 2] != '\n');
}
