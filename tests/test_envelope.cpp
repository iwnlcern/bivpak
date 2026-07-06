#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "core/report/envelope.hpp"
#include "core/report/exit_map.hpp"

TEST_CASE("exit map classifies refusal, mid-fail, and usage") {
  CHECK(biv::report::exit_for_error(biv::ErrKind::PartialPresent) == 3);
  CHECK(biv::report::exit_for_error(biv::ErrKind::IntegrityFailurePreApply) == 3);
  CHECK(biv::report::exit_for_error(biv::ErrKind::ArchiveWriteFailed) == 4);
  CHECK(biv::report::exit_for_error(biv::ErrKind::RestoreWriteFailed) == 4);
  CHECK(biv::report::exit_for_error(biv::ErrKind::UsageError) == 5);
  CHECK(biv::report::exit_for_warnings(false) == 0);
  CHECK(biv::report::exit_for_warnings(true) == 2);
}

TEST_CASE("pack success envelope includes advisories") {
  biv::pack::PackReport report;
  report.image_path = "/tmp/sample.bvpk";
  report.source_path = "/tmp/sample";
  report.image_id = "00000000-0000-4000-8000-000000000000";
  report.member_count = 2;
  report.payload_bytes = 5;
  report.advisories.push_back(biv::pack::Advisory{
      .kind = "prune-summary",
      .entries = {biv::scan::PruneEntry{.relpath = "target", .source = "builtin-v1"}},
      .paths = {}});

  const auto json = biv::report::envelope("pack", report, std::nullopt, std::nullopt, 0);
  CHECK(json.find("\"ok\": true") != std::string::npos);
  CHECK(json.find("\"verb\": \"pack\"") != std::string::npos);
  CHECK(json.find("\"exit_code\": 0") != std::string::npos);
  CHECK(json.find("\"app_version\": \"0.1.0\"") != std::string::npos);
  CHECK(json.find("\"kind\": \"prune-summary\"") != std::string::npos);
  CHECK(json.find("\"path\": \"target\"") != std::string::npos);
  CHECK(json.find("\"source\": \"builtin-v1\"") != std::string::npos);
  CHECK(json.find("\"manifest\"") != std::string::npos);
  CHECK(json.find("\"error\": null") != std::string::npos);
}

TEST_CASE("error envelope carries failure facts in result") {
  biv::BivError error{biv::ErrKind::PartialPresent};
  error.facts["partial_path"] = "/tmp/sample.bvpk.partial";
  error.facts["spool_path"] = "/tmp/sample.bvpk.spool";

  const auto json = biv::report::envelope("pack", std::nullopt, std::nullopt, error, 3);
  CHECK(json.find("\"ok\": false") != std::string::npos);
  CHECK(json.find("\"result\": null") != std::string::npos);
  CHECK(json.find("\"kind\": \"PartialPresent\"") != std::string::npos);
  CHECK(json.find("\"partial_path\": \"/tmp/sample.bvpk.partial\"") != std::string::npos);
  CHECK(json.find("\"spool_path\": \"/tmp/sample.bvpk.spool\"") != std::string::npos);
}

TEST_CASE("schema artifacts reserve envelope and exit-map contracts") {
  std::ifstream exit_map{std::string{BIV_SOURCE_DIR} + "/schemas/biv-exit-map.v1.json"};
  REQUIRE(exit_map);
  const std::string exit_text{std::istreambuf_iterator<char>{exit_map}, std::istreambuf_iterator<char>{}};
  const std::vector<std::pair<biv::ErrKind, std::string_view>> rows{
      {biv::ErrKind::SourceUnreadableRoot, "SourceUnreadableRoot"},
      {biv::ErrKind::RepoDiscoveredUnsupported, "RepoDiscoveredUnsupported"},
      {biv::ErrKind::OutputInsideSource, "OutputInsideSource"},
      {biv::ErrKind::PartialPresent, "PartialPresent"},
      {biv::ErrKind::ArchiveWriteFailed, "ArchiveWriteFailed"},
      {biv::ErrKind::NotABivpakImage, "NotABivpakImage"},
      {biv::ErrKind::ImageUnreadable, "ImageUnreadable"},
      {biv::ErrKind::FormatVersionUnsupported, "FormatVersionUnsupported"},
      {biv::ErrKind::UnknownRequiredCapability, "UnknownRequiredCapability"},
      {biv::ErrKind::IntegrityFailurePreApply, "IntegrityFailurePreApply"},
      {biv::ErrKind::UnmanifestedMember, "UnmanifestedMember"},
      {biv::ErrKind::MemberPathUnsafe, "MemberPathUnsafe"},
      {biv::ErrKind::CollisionRefused, "CollisionRefused"},
      {biv::ErrKind::OpenPartialPresent, "OpenPartialPresent"},
      {biv::ErrKind::IntegrityFailureMidApply, "IntegrityFailureMidApply"},
      {biv::ErrKind::RestoreWriteFailed, "RestoreWriteFailed"},
      {biv::ErrKind::InternalError, "InternalError"},
      {biv::ErrKind::UsageError, "UsageError"},
      {biv::ErrKind::ParseError, "ParseError"}};
  for (const auto& [kind, name] : rows) {
    const std::string needle = "\"kind\": \"" + std::string{name} + "\"";
    INFO(name);
    CHECK(exit_text.find(needle) != std::string::npos);
    CHECK(exit_text.find("\"exit\": " + std::to_string(biv::report::exit_for_error(kind)),
                         exit_text.find(needle)) != std::string::npos);
  }
  CHECK(exit_text.find("\"RepoDiscoveredUnsupported\", \"class\": \"refusal\", \"exit\": 3, \"transitional\": true") !=
        std::string::npos);
  CHECK(exit_text.find("NotYetImplemented") != std::string::npos);
  CHECK(exit_text.find("CredentialFloorExcluded") != std::string::npos);

  std::ifstream envelope{std::string{BIV_SOURCE_DIR} + "/schemas/biv-json-envelope.v1.schema.json"};
  REQUIRE(envelope);
  const std::string envelope_text{std::istreambuf_iterator<char>{envelope}, std::istreambuf_iterator<char>{}};
  CHECK(envelope_text.find("prune-summary") != std::string::npos);
  CHECK(envelope_text.find("exit_code") != std::string::npos);
  CHECK(envelope_text.find("partial_dir") != std::string::npos);
}
