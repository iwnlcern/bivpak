#include <fcntl.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "adapters/codex/codex.hpp"
#include "adapters/rewrite_common.hpp"
#include "adapters/secure_io.hpp"
#include "adapters/version_floor.hpp"
#include "core/support/portability.hpp"

namespace biv::adapters {

namespace {

namespace fs = std::filesystem;

struct RolloutName {
  std::string id;
  std::string file_stamp;
  std::string year;
  std::string month;
  std::string day;
};

struct WritePlan {
  std::string artifact;
  fs::path path;
  std::string installed_id;
};

struct PreparedSession {
  manifest::AgentSessionEntry record;
  std::string installed_id;
  std::vector<std::pair<std::string, std::string>> child_ids;
  std::vector<WritePlan> writes;
  bool host_version_unverified{false};
  InstallVerify verify;
  rewrite::ReplacementPairs pair_set_applied;
  std::vector<std::vector<std::byte>> outputs;
  size_t skipped_non_utf8{0};
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

manifest::PathFlavor path_flavor_for(const fs::path& path) {
  const std::string text = path.generic_string();
  if (text.size() >= 7 && text.starts_with("/mnt/") && text.at(6) == '/' && ascii_alpha(text.at(5))) {
    return manifest::PathFlavor::wsl;
  }
  return manifest::PathFlavor::posix;
}

uint64_t unix_ms_now() {
  const auto now = std::chrono::system_clock::now();
  return static_cast<uint64_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
}

std::tm gmtime_from_ms(const uint64_t ms) {
  const std::time_t seconds = static_cast<std::time_t>(ms / 1000U);
  std::tm tm {};
  gmtime_r(&seconds, &tm);
  return tm;
}

std::string strftime_utc(const std::tm& tm, std::string_view format) {
  std::array<char, 32> buffer {};
  const size_t written = std::strftime(buffer.data(), buffer.size(), std::string{format}.c_str(), &tm);
  if (written == 0U) {
    return {};
  }
  return buffer.data();
}

std::string hex_uuid(const std::array<unsigned char, 16>& bytes) {
  constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  out.reserve(36);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (i == 4U || i == 6U || i == 8U || i == 10U) {
      out.push_back('-');
    }
    out.push_back(hex.at((bytes.at(i) >> 4U) & 0x0FU));
    out.push_back(hex.at(bytes.at(i) & 0x0FU));
  }
  return out;
}

std::string uuidv7_from_ms(const uint64_t ms) {
  std::array<unsigned char, 16> bytes {};
  support::secure_random_bytes(bytes.data(), bytes.size());
  bytes.at(0) = static_cast<unsigned char>((ms >> 40U) & 0xffU);
  bytes.at(1) = static_cast<unsigned char>((ms >> 32U) & 0xffU);
  bytes.at(2) = static_cast<unsigned char>((ms >> 24U) & 0xffU);
  bytes.at(3) = static_cast<unsigned char>((ms >> 16U) & 0xffU);
  bytes.at(4) = static_cast<unsigned char>((ms >> 8U) & 0xffU);
  bytes.at(5) = static_cast<unsigned char>(ms & 0xffU);
  bytes.at(6) = static_cast<unsigned char>((bytes.at(6) & 0x0fU) | 0x70U);
  bytes.at(8) = static_cast<unsigned char>((bytes.at(8) & 0x3fU) | 0x80U);
  return hex_uuid(bytes);
}

RolloutName mint_rollout_name() {
  const uint64_t ms = unix_ms_now();
  const auto tm = gmtime_from_ms(ms);
  return RolloutName{.id = uuidv7_from_ms(ms),
                     .file_stamp = strftime_utc(tm, "%Y-%m-%dT%H-%M-%S"),
                     .year = strftime_utc(tm, "%Y"),
                     .month = strftime_utc(tm, "%m"),
                     .day = strftime_utc(tm, "%d")};
}

std::vector<std::string> all_artifacts(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> artifacts = record.artifacts;
  for (const auto& child : record.children) {
    artifacts.insert(artifacts.end(), child.artifacts.begin(), child.artifacts.end());
  }
  return artifacts;
}

std::optional<std::string> id_from_artifact(const std::string& artifact) {
  const std::string prefix = "agents/codex/";
  if (!artifact.starts_with(prefix) || !artifact.ends_with(".jsonl")) {
    return std::nullopt;
  }
  auto id =
      artifact.substr(prefix.size(), artifact.size() - prefix.size() - 6U);
  if (id.empty() || id == "." || id == ".." ||
      id.find_first_of("/\\") != std::string::npos) {
    return std::nullopt;
  }
  return id;
}

std::vector<std::pair<std::string, std::string>> id_pairs_for(const manifest::AgentSessionEntry& record,
                                                              std::string_view installed_id,
                                                              const std::vector<std::pair<std::string, std::string>>&
                                                                  child_ids) {
  std::vector<std::pair<std::string, std::string>> ids{{record.original_session_ids.primary, std::string{installed_id}}};
  ids.insert(ids.end(), child_ids.begin(), child_ids.end());
  return ids;
}

std::vector<std::string> origin_ids_for(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> ids{record.original_session_ids.primary};
  for (const auto& child : record.children) {
    ids.push_back(child.original_id);
  }
  return ids;
}

std::optional<std::string> non_utf8_detail(const size_t skipped_non_utf8) {
  if (skipped_non_utf8 == 0U) {
    return std::nullopt;
  }
  return "non_utf8_skipped=" + std::to_string(skipped_non_utf8);
}

void merge_verify(InstallVerify& total, const InstallVerify& next) {
  total.origin_path_hits += next.origin_path_hits;
  total.origin_id_hits += next.origin_id_hits;
  total.artifacts_checked += next.artifacts_checked;
}

fs::path codex_root_for_host(const Host& host) {
  if (host.env.getenv) {
    auto configured = host.env.getenv("CODEX_HOME");
    if (configured.has_value()) {
      return fs::path{*configured};
    }
  }
  if (!host.env.home.empty()) {
    return host.env.home / ".codex";
  }
  return host.home / ".codex";
}

std::optional<std::string> parse_codex_version(const std::string_view raw) {
  size_t position = raw.find_first_not_of(" \t\r\n");
  constexpr std::string_view prefix = "codex-cli";
  if (position == std::string_view::npos || !raw.substr(position).starts_with(prefix)) {
    return std::nullopt;
  }
  position += prefix.size();
  if (position >= raw.size() || (raw.at(position) != ' ' && raw.at(position) != '\t')) {
    return std::nullopt;
  }
  position = raw.find_first_not_of(" \t", position);
  if (position == std::string_view::npos) {
    return std::nullopt;
  }
  auto version = version_floor::extract_single_version(raw);
  if (!version.has_value() ||
      !raw.substr(position).starts_with(*version)) {
    return std::nullopt;
  }
  return version;
}

std::optional<support::ProbeEvidence> observe_codex(const Host& host) {
  const auto pin = host.pinned_bins.find("codex");
  const std::optional<fs::path> requested =
      pin == host.pinned_bins.end() ? std::nullopt : std::optional<fs::path>{pin->second};
  if (!host.version_probe) {
    return std::nullopt;
  }
  auto observed = host.version_probe("codex", requested);
  if (!observed) {
    return support::ProbeEvidence{.agent = "codex",
                                  .requested = requested,
                                  .executed = std::nullopt,
                                  .pinned = requested.has_value(),
                                  .outcome = support::ProbeOutcome::spawn_error,
                                  .exit_code = -1,
                                  .raw = support::sanitize_utf8(observed.error().detail),
                                  .parsed = std::nullopt};
  }
  observed->agent = "codex";
  if (requested.has_value()) {
    observed->requested = requested;
    observed->pinned = true;
  }
  return std::move(*observed);
}

Capabilities probe_capabilities(const Host& host) {
  const auto root = codex_root_for_host(host);
  std::error_code error;
  const bool store_exists = fs::exists(root, error);
  auto probe = observe_codex(host);
  std::optional<std::string> parsed;
  if (probe.has_value() && probe->outcome == support::ProbeOutcome::ok) {
    probe->parsed = parse_codex_version(probe->raw);
    if (probe->parsed.has_value()) {
      parsed = probe->parsed;
    } else {
      probe->outcome = support::ProbeOutcome::unparseable;
    }
  }
  const auto verdict = !store_exists
                           ? Capabilities::Verdict::absent
                           : parsed.has_value()
                                 ? Capabilities::Verdict::readable
                                 : Capabilities::Verdict::unreadable;
  bool newer_than_survey = false;
  if (verdict == Capabilities::Verdict::readable && parsed.has_value()) {
    const auto host_version = version_floor::parse_grammar(*parsed);
    const auto surveyed = version_floor::parse_grammar(
        version_floor::row_for("codex").surveyed_through);
    assert(host_version.has_value() && surveyed.has_value());
    if (host_version.has_value() && surveyed.has_value()) {
      newer_than_survey =
          version_floor::compare_line(*host_version, *surveyed) ==
          version_floor::Order::greater;
    }
  }
  return Capabilities::from_probe(
      verdict, verdict == Capabilities::Verdict::readable ? parsed
                                                           : std::nullopt,
      newer_than_survey, true,
      {.collect = store_exists,
       .install = store_exists,
       .rewrite = store_exists},
      std::move(probe));
}

}  // namespace

expected<InstallResult> codex_install(const InstallTarget& target,
                                      const Consent consent,
                                      const std::span<const manifest::AgentSessionEntry> records) {
  InstallResult result;
  result.mode = consent == Consent::yes ? InstallResult::Mode::host_installed : InstallResult::Mode::staged;
  const auto install_root = consent == Consent::yes
                                ? target.target_store.root
                                : target.workspace_root / ".biv" / "agents" /
                                      "codex";
  const auto publish_root = consent == Consent::yes ? target.target_store.root
                                                    : target.workspace_root;
  for (const auto& record : records) {
    std::set<std::string> image_ids{record.original_session_ids.primary};
    for (const auto& child : record.children) {
      image_ids.insert(child.original_id);
    }
    for (const auto& artifact : all_artifacts(record)) {
      const auto original_id = id_from_artifact(artifact);
      if (!original_id.has_value() || !image_ids.contains(*original_id)) {
        for (const auto& refused : records) {
          result.sessions.push_back(InstallSessionOutcome{
              .image_session_id = refused.original_session_ids.primary,
              .outcome = InstallSessionOutcome::Outcome::failed,
              .reason = "containment_refused",
              .content_rewrite = std::nullopt,
              .host_version_unverified = false,
              .verify = {},
              .detail = std::nullopt});
        }
        return result;
      }
    }
  }

  const auto& host_caps = target.capabilities;
  std::vector<PreparedSession> prepared_sessions;
  prepared_sessions.reserve(records.size());
  for (const auto& record : records) {
    const auto admission = version_floor::admit(
        {.agent = "codex",
         .host_version = host_caps.agent_version(),
         .image_version = record.agent_version_at_pack});
    if (!admission.admitted) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::failed,
          .reason = "not-validated",
          .content_rewrite = std::nullopt,
          .host_version_unverified = false,
          .verify = {},
          .detail = std::string{admission.detail}});
      continue;
    }
    std::map<std::string, RolloutName> rollouts;
    rollouts.emplace(record.original_session_ids.primary, mint_rollout_name());
    PreparedSession prepared{.record = record,
                             .installed_id = rollouts.at(record.original_session_ids.primary).id,
                             .child_ids = {},
                             .writes = {},
                             .host_version_unverified =
                                 admission.host_version_unverified,
                             .verify = {},
                             .pair_set_applied = {},
                             .outputs = {},
                             .skipped_non_utf8 = 0};
    for (const auto& child : record.children) {
      rollouts.emplace(child.original_id, mint_rollout_name());
      prepared.child_ids.push_back({child.original_id, rollouts.at(child.original_id).id});
    }
    for (const auto& artifact : all_artifacts(record)) {
      auto original_id = id_from_artifact(artifact);
      if (!original_id.has_value()) {
        InstallResult refused;
        refused.mode = result.mode;
        for (const auto& refused_record : records) {
          refused.sessions.push_back(InstallSessionOutcome{
              .image_session_id =
                  refused_record.original_session_ids.primary,
              .outcome = InstallSessionOutcome::Outcome::failed,
              .reason = "containment_refused",
              .content_rewrite = std::nullopt,
              .host_version_unverified = false,
              .verify = {},
              .detail = std::nullopt});
        }
        return refused;
      }
      const auto rollout_found = rollouts.find(*original_id);
      const auto& rollout = rollout_found->second;
      const auto path =
          install_root / "sessions" / rollout.year / rollout.month /
          rollout.day /
          ("rollout-" + rollout.file_stamp + "-" + rollout.id + ".jsonl");
      prepared.writes.push_back(WritePlan{
          .artifact = artifact, .path = path, .installed_id = rollout.id});
    }
    prepared_sessions.push_back(std::move(prepared));
  }

  {
    for (auto& prepared : prepared_sessions) {
      prepared.pair_set_applied = rewrite::derive_pair_set(
          prepared.record.original_path, prepared.record.path_flavor,
          target.workspace_root.generic_string(),
          path_flavor_for(target.workspace_root));
      const auto origins =
          rewrite::origins_from_pairs(prepared.pair_set_applied);
      const auto id_map = id_pairs_for(prepared.record, prepared.installed_id,
                                       prepared.child_ids);
      const auto origin_ids = origin_ids_for(prepared.record);
      for (const auto& write : prepared.writes) {
        auto data = target.member_read(write.artifact);
        if (!data) {
          return std::unexpected(data.error());
        }
        auto rewritten = rewrite::rewrite_jsonl_bytes(
            *data, rewrite::PathPairsView{prepared.pair_set_applied},
            rewrite::IdPairsView{id_map});
        prepared.skipped_non_utf8 += rewritten.skipped_non_utf8;
        merge_verify(prepared.verify,
                     rewrite::verify_scan(rewritten.bytes,
                         rewrite::OriginPathsView{origins},
                         rewrite::OriginIdsView{origin_ids}));
        prepared.outputs.push_back(std::move(rewritten.bytes));
      }
    }
    if (std::ranges::any_of(prepared_sessions,
                           [](const PreparedSession& prepared) {
          return prepared.verify.origin_path_hits != 0U ||
                 prepared.verify.origin_id_hits != 0U;
        })) {
      // Capability-refusal rows were emitted before preparation and must
      // survive a rewrite-verification failure in an admitted sibling.
      for (const auto& prepared : prepared_sessions) {
        result.sessions.push_back(InstallSessionOutcome{
            .image_session_id = prepared.record.original_session_ids.primary,
            .outcome = InstallSessionOutcome::Outcome::failed,
            .reason = "containment_refused",
            .content_rewrite = std::nullopt,
            .host_version_unverified = prepared.host_version_unverified,
            .verify = prepared.verify,
            .detail = "rewrite_verify_failed"});
      }
      return result;
    }

    std::vector<secure_io::WriteRequest> writes;
    for (const auto& prepared : prepared_sessions) {
      for (size_t i = 0; i < prepared.writes.size(); ++i) {
        writes.push_back(secure_io::WriteRequest{
            .relative_path = prepared.writes.at(i).path.lexically_relative(
                publish_root),
            .bytes = prepared.outputs.at(i)});
      }
    }
    if (!writes.empty()) {
      auto ok = secure_io::write_batch_no_replace(publish_root, writes);
      if (!ok) {
        const bool containment = ok.error().detail == "containment_refused";
        std::optional<std::string> cohort_detail;
        std::string cohort_reason;
        if (containment) {
          cohort_reason = "containment_refused";
          cohort_detail = ok.error().path;
        } else {
          cohort_reason = "error";
          if (const auto symbol = secure_io::errno_symbol(ok.error().err_no);
              symbol.has_value()) {
            cohort_detail = std::string{*symbol};
          }
        }
        // No clear(): capability-refusal rows never entered prepared_sessions
        // or the batch, and clearing here deleted them from the report.
        for (const auto& prepared : prepared_sessions) {
          result.sessions.push_back(InstallSessionOutcome{
              .image_session_id = prepared.record.original_session_ids.primary,
              .outcome = InstallSessionOutcome::Outcome::failed,
              .reason = cohort_reason,
              .content_rewrite = std::nullopt,
              .host_version_unverified = prepared.host_version_unverified,
              .verify = prepared.verify,
              .detail = cohort_detail});
        }
        return result;
      }
    }
  }

  for (auto& prepared : prepared_sessions) {
    result.id_map.push_back(IdMapEntry{
        .agent = "codex",
        .image_session_id = prepared.record.original_session_ids.primary,
        .installed_session_id = prepared.installed_id,
        .children = prepared.child_ids});
    result.pair_set_applied.insert(result.pair_set_applied.end(),
                                   prepared.pair_set_applied.begin(),
                                   prepared.pair_set_applied.end());
    if (consent == Consent::no) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = prepared.record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::staged,
          .reason = std::nullopt,
          .content_rewrite = "pair",
          .host_version_unverified = prepared.host_version_unverified,
          .verify = prepared.verify,
          .detail = non_utf8_detail(prepared.skipped_non_utf8)});
      continue;
    }

    result.sessions.push_back(InstallSessionOutcome{
        .image_session_id = prepared.record.original_session_ids.primary,
        .outcome = InstallSessionOutcome::Outcome::installed,
        .reason = std::nullopt,
        .content_rewrite = "pair",
        .host_version_unverified = prepared.host_version_unverified,
        .verify = prepared.verify,
        .detail = non_utf8_detail(prepared.skipped_non_utf8)});
    result.activation.push_back(Activation{
        .agent = "codex", .command = "codex resume " + prepared.installed_id});
  }
  return result;
}

expected<RewriteReport> codex_rewrite(const std::span<const SessionRecord> records, const InstallTarget& target) {
  RewriteReport report;
  for (const auto& record : records) {
    const auto pair_set = rewrite::derive_pair_set(record.original_path,
                                                   record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   path_flavor_for(target.workspace_root));
    const auto origins = rewrite::origins_from_pairs(pair_set);
    std::vector<std::pair<std::string, std::string>> id_map{
        {record.original_session_id, uuidv7_from_ms(unix_ms_now())}};
    std::vector<std::string> origin_ids{record.original_session_id};
    for (const auto& child_id : record.child_ids) {
      id_map.push_back({child_id, uuidv7_from_ms(unix_ms_now())});
      origin_ids.push_back(child_id);
    }
    for (const auto& artifact : record.artifacts) {
      auto data = target.member_read(artifact);
      if (!data) {
        return std::unexpected(data.error());
      }
      auto rewritten =
          rewrite::rewrite_jsonl_bytes(*data, rewrite::PathPairsView{pair_set},
                                       rewrite::IdPairsView{id_map});
      report.skipped_non_utf8 += rewritten.skipped_non_utf8;
      auto verify = rewrite::verify_scan(rewritten.bytes,
                                         rewrite::OriginPathsView{origins},
                                         rewrite::OriginIdsView{origin_ids});
      report.per_artifact_hits.push_back({artifact, verify});
      merge_verify(report.verify, verify);
    }
  }
  return report;
}

Capabilities codex_capabilities(const Host& host) { return probe_capabilities(host); }

}  // namespace biv::adapters
