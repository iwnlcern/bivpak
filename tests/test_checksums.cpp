#include <cstddef>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/manifest/checksums.hpp"

namespace {

std::vector<std::byte> bytes_of(const std::string& text) {
  std::vector<std::byte> bytes(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    bytes[i] = static_cast<std::byte>(static_cast<unsigned char>(text[i]));
  }
  return bytes;
}

constexpr const char* kDigestA = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
constexpr const char* kDigestB = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";

}  // namespace

TEST_CASE("Checksums serialize sorted entries exactly") {
  biv::manifest::Checksums checksums;
  checksums.entries["payload/z.txt"] = kDigestB;
  checksums.entries["payload/a.txt"] = kDigestA;

  REQUIRE(biv::manifest::serialize(checksums) ==
          "{\n"
          "  \"algo\": \"sha256\",\n"
          "  \"entries\": {\n"
          "    \"payload/a.txt\": \"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\",\n"
          "    \"payload/z.txt\": \"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\"\n"
          "  }\n"
          "}\n");
}

TEST_CASE("Checksums parse round-trips serialized models") {
  biv::manifest::Checksums checksums;
  checksums.entries["payload/a.txt"] = kDigestA;
  checksums.entries["payload/z.txt"] = kDigestB;

  const auto parsed = biv::manifest::parse_checksums(bytes_of(biv::manifest::serialize(checksums)));
  REQUIRE(parsed.has_value());
  REQUIRE(parsed->entries == checksums.entries);
}

TEST_CASE("Checksums parser refuses bad algo and bad digests") {
  REQUIRE_FALSE(biv::manifest::parse_checksums(bytes_of(
                    "{\"algo\":\"sha1\",\"entries\":{\"payload/a\":\"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\"}}"))
                    .has_value());
  REQUIRE_FALSE(biv::manifest::parse_checksums(bytes_of(
                    "{\"algo\":\"sha256\",\"entries\":{\"payload/a\":\"abc\"}}"))
                    .has_value());
  REQUIRE_FALSE(biv::manifest::parse_checksums(bytes_of(
                    "{\"algo\":\"sha256\",\"entries\":{\"payload/a\":\"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg\"}}"))
                    .has_value());
}

TEST_CASE("Checksums parser enforces byte cap") {
  std::vector<std::byte> too_large((65U << 20), std::byte{' '});
  REQUIRE_FALSE(biv::manifest::parse_checksums(too_large).has_value());
}
