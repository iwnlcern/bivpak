#include <array>
#include <cstddef>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "core/support/cursor.hpp"
#include "core/support/error.hpp"

TEST_CASE("ErrKind spellings match envelope strings") {
  using biv::ErrKind;
  REQUIRE(std::string{biv::to_string(ErrKind::SourceUnreadableRoot)} == "SourceUnreadableRoot");
  REQUIRE(std::string{biv::to_string(ErrKind::FormatVersionUnsupported)} == "FormatVersionUnsupported");
  REQUIRE(std::string{biv::to_string(ErrKind::IntegrityFailureMidApply)} == "IntegrityFailureMidApply");
  REQUIRE(std::string{biv::to_string(ErrKind::UsageError)} == "UsageError");
}

TEST_CASE("BivError facts round-trip inserted keys") {
  biv::BivError err{biv::ErrKind::ArchiveWriteFailed};
  err.facts["partial_path"] = "/tmp/a.partial";
  err.facts["spool_path"] = "/tmp/a.spool";

  REQUIRE(err.facts.at("partial_path") == "/tmp/a.partial");
  REQUIRE(err.facts.at("spool_path") == "/tmp/a.spool");
}

TEST_CASE("Cursor take advances and returns exact bytes") {
  const std::array<std::byte, 4> bytes{std::byte{'a'}, std::byte{'b'}, std::byte{'c'}, std::byte{'d'}};
  biv::Cursor cursor{bytes};

  auto first = cursor.take(2);
  REQUIRE(first.has_value());
  REQUIRE(first->size() == 2);
  REQUIRE((*first)[0] == std::byte{'a'});
  REQUIRE((*first)[1] == std::byte{'b'});
  REQUIRE(cursor.pos() == 2);
  REQUIRE(cursor.remaining() == 2);

  auto second = cursor.take(2);
  REQUIRE(second.has_value());
  REQUIRE((*second)[0] == std::byte{'c'});
  REQUIRE((*second)[1] == std::byte{'d'});
  REQUIRE(cursor.remaining() == 0);
}

TEST_CASE("Cursor underrun returns ParseError and does not advance") {
  const std::array<std::byte, 1> bytes{std::byte{'x'}};
  biv::Cursor cursor{bytes};

  auto result = cursor.take(2);
  REQUIRE_FALSE(result.has_value());
  REQUIRE(result.error().kind == biv::ErrKind::ParseError);
  REQUIRE(result.error().detail == "eof");
  REQUIRE(cursor.pos() == 0);
  REQUIRE(cursor.remaining() == 1);
}

TEST_CASE("Cursor zero-length operations succeed") {
  const std::array<std::byte, 1> bytes{std::byte{'x'}};
  biv::Cursor cursor{bytes};

  auto take = cursor.take(0);
  REQUIRE(take.has_value());
  REQUIRE(take->empty());
  REQUIRE(cursor.pos() == 0);

  auto skip = cursor.skip(0);
  REQUIRE(skip.has_value());
  REQUIRE(cursor.pos() == 0);
}

TEST_CASE("Cursor skip advances within bounds and rejects overflow") {
  const std::array<std::byte, 3> bytes{std::byte{'a'}, std::byte{'b'}, std::byte{'c'}};
  biv::Cursor cursor{bytes};

  REQUIRE(cursor.skip(2).has_value());
  REQUIRE(cursor.pos() == 2);
  REQUIRE(cursor.remaining() == 1);

  auto result = cursor.skip(2);
  REQUIRE_FALSE(result.has_value());
  REQUIRE(result.error().kind == biv::ErrKind::ParseError);
  REQUIRE(cursor.pos() == 2);
}
