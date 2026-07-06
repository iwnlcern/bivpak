#include <string>

#include <catch2/catch_test_macros.hpp>

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
