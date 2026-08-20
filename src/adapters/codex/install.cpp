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

#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

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
  std::optional<std::string> expected_parent_id;
};

struct PreparedSession {
  manifest::AgentSessionEntry record;
  std::string installed_id;
  std::vector<std::pair<std::string, std::string>> child_ids;
  std::vector<std::pair<std::string, std::string>> rewrite_ids;
  std::map<std::string, std::string> installed_by_original;
  std::vector<std::string> origin_ids;
  std::vector<WritePlan> writes;
  std::optional<std::string> installed_parent_id;
  bool host_version_unverified{false};
  InstallVerify verify;
  rewrite::ReplacementPairs pair_set_applied;
  std::vector<std::vector<std::byte>> outputs;
  size_t skipped_non_utf8{0};
  std::optional<std::string> refusal_reason;
  std::optional<std::string> refusal_detail;
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

std::optional<std::string> identity_for_artifacts(
    const std::vector<std::string>& artifacts,
    const std::string_view fallback) {
  if (artifacts.empty()) return std::string{fallback};
  std::set<std::string> identities;
  for (const auto& artifact : artifacts) {
    const auto identity = id_from_artifact(artifact);
    if (!identity.has_value()) return std::nullopt;
    identities.insert(*identity);
  }
  if (identities.size() != 1U) return std::nullopt;
  return *identities.begin();
}

std::optional<std::string> non_utf8_detail(const size_t skipped_non_utf8) {
  if (skipped_non_utf8 == 0U) {
    return std::nullopt;
  }
  return "non_utf8_skipped=" + std::to_string(skipped_non_utf8);
}

bool jsonl_decodable(const std::span<const std::byte> bytes) {
  return strict_jsonl_decodable(bytes, [](const std::string_view line) {
    simdjson::padded_string padded{line}; simdjson::dom::parser parser;
    simdjson::dom::element value; return !parser.parse(padded).get(value);
  });
}

struct RolloutIdentities {
  std::optional<std::string> id;
  std::optional<std::string> session_id;
  std::vector<std::string> parent_thread_ids;
};

RolloutIdentities rollout_identities(const std::span<const std::byte> bytes) {
  std::string input;
  input.reserve(bytes.size());
  for (const auto byte : bytes) input.push_back(static_cast<char>(byte));
  size_t start = 0U;
  while (start < input.size()) {
    const auto newline = input.find('\n', start);
    const auto end = newline == std::string::npos ? input.size() : newline;
    simdjson::padded_string padded{
        std::string_view{input}.substr(start, end - start)};
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    simdjson::dom::object object;
    std::string_view type;
    simdjson::dom::object payload;
    if (!parser.parse(padded).get(root) && !root.get(object) &&
        !object.at_key("type").get(type) && type == "session_meta" &&
        !object.at_key("payload").get(payload)) {
      RolloutIdentities identities;
      std::string_view value;
      if (!payload.at_key("id").get(value)) {
        identities.id = std::string{value};
      }
      if (!payload.at_key("session_id").get(value)) {
        identities.session_id = std::string{value};
      }
      if (!payload.at_key("parent_thread_id").get(value)) {
        identities.parent_thread_ids.emplace_back(value);
      }
      simdjson::dom::object source;
      simdjson::dom::object subagent;
      simdjson::dom::object thread_spawn;
      if (!payload.at_key("source").get(source) &&
          !source.at_key("subagent").get(subagent) &&
          !subagent.at_key("thread_spawn").get(thread_spawn) &&
          !thread_spawn.at_key("parent_thread_id").get(value)) {
        identities.parent_thread_ids.emplace_back(value);
      }
      return identities;
    }
    if (newline == std::string::npos) break;
    start = newline + 1U;
  }
  return {};
}

void merge_verify(InstallVerify& total, const InstallVerify& next) {
  total.origin_path_hits += next.origin_path_hits;
  total.origin_id_hits += next.origin_id_hits;
  total.artifacts_checked += next.artifacts_checked;
}

std::optional<std::string> verify_failure_detail(const InstallVerify& verify) {
  if (verify.origin_path_hits != 0U) return "origin_path";
  if (verify.origin_id_hits != 0U) return "origin_id";
  return std::nullopt;
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
    const bool staged = record.provenance.locator == "staging" &&
                        record.provenance.discovery_tier == "staged";
    std::set<std::string> image_ids;
    const auto primary = identity_for_artifacts(
        record.artifacts, record.original_session_ids.primary);
    bool valid = primary.has_value() &&
                 (staged || *primary == record.original_session_ids.primary) &&
                 image_ids.insert(*primary).second;
    for (const auto& child : record.children) {
      const auto child_identity =
          identity_for_artifacts(child.artifacts, child.original_id);
      valid = valid && child_identity.has_value() &&
              (staged || *child_identity == child.original_id) &&
              image_ids.insert(*child_identity).second;
    }
    if (!valid) {
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
    const auto primary_identity =
        identity_for_artifacts(record.artifacts,
                               record.original_session_ids.primary)
            .value();
    std::map<std::string, RolloutName> rollouts;
    rollouts.emplace(primary_identity, mint_rollout_name());
    PreparedSession prepared{.record = record,
                             .installed_id = rollouts.at(primary_identity).id,
                             .child_ids = {},
                             .rewrite_ids = {{record.original_session_ids.primary,
                                              rollouts.at(primary_identity).id}},
                             .installed_by_original = {
                                 {record.original_session_ids.primary,
                                  rollouts.at(primary_identity).id}},
                             .origin_ids = {record.original_session_ids.primary},
                             .writes = {},
                             .installed_parent_id = std::nullopt,
                             .host_version_unverified =
                                 admission.host_version_unverified,
                             .verify = {},
                             .pair_set_applied = {},
                             .outputs = {},
                             .skipped_non_utf8 = 0,
                             .refusal_reason = std::nullopt,
                             .refusal_detail = std::nullopt};
    if (primary_identity != record.original_session_ids.primary) {
      prepared.rewrite_ids.push_back(
          {primary_identity, prepared.installed_id});
      prepared.origin_ids.push_back(primary_identity);
    }
    for (const auto& child : record.children) {
      const auto child_identity =
          identity_for_artifacts(child.artifacts, child.original_id).value();
      rollouts.emplace(child_identity, mint_rollout_name());
      const auto& installed_child = rollouts.at(child_identity).id;
      prepared.child_ids.push_back({child.original_id, installed_child});
      prepared.installed_by_original.insert_or_assign(child.original_id,
                                                       installed_child);
      prepared.rewrite_ids.push_back({child.original_id, installed_child});
      prepared.origin_ids.push_back(child.original_id);
      if (child_identity != child.original_id) {
        prepared.rewrite_ids.push_back({child_identity, installed_child});
        prepared.origin_ids.push_back(child_identity);
      }
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
      const auto& rollout = rollouts.at(*original_id);
      const auto path =
          install_root / "sessions" / rollout.year / rollout.month /
          rollout.day /
          ("rollout-" + rollout.file_stamp + "-" + rollout.id + ".jsonl");
      std::optional<std::string> expected_parent_id;
      const auto owning_child = std::ranges::find_if(
          record.children, [&](const auto& child) {
            return std::ranges::find(child.artifacts, artifact) !=
                   child.artifacts.end();
          });
      if (owning_child != record.children.end() &&
          owning_child->parent_id.has_value()) {
        const auto installed_parent = prepared.installed_by_original.find(
            *owning_child->parent_id);
        if (installed_parent == prepared.installed_by_original.end()) {
          prepared.refusal_reason = "containment_refused";
          prepared.refusal_detail = "staged_identity_mismatch";
        } else {
          expected_parent_id = installed_parent->second;
        }
      }
      prepared.writes.push_back(WritePlan{
          .artifact = artifact,
          .path = path,
          .installed_id = rollout.id,
          .expected_parent_id = std::move(expected_parent_id)});
    }
    prepared_sessions.push_back(std::move(prepared));
  }

  for (auto& prepared : prepared_sessions) {
    const auto& parent = prepared.record.original_session_ids.parent;
    if (!parent.has_value()) continue;
    const auto installed_parent = std::ranges::find_if(
        prepared_sessions, [&](const PreparedSession& candidate) {
          return candidate.record.original_session_ids.primary == *parent;
        });
    if (installed_parent != prepared_sessions.end()) {
      prepared.rewrite_ids.push_back({*parent, installed_parent->installed_id});
      prepared.installed_parent_id = installed_parent->installed_id;
    }
  }

  std::set<std::string> image_origin_path_set;
  std::set<std::string> image_origin_id_set;
  for (const auto& record : records) {
    const auto pairs = rewrite::derive_install_pair_set(
        record,
        target.workspace_root.generic_string(),
        path_flavor_for(target.workspace_root));
    const auto origins = rewrite::origins_from_pairs(pairs);
    image_origin_path_set.insert(origins.begin(), origins.end());
    image_origin_id_set.insert(record.original_session_ids.primary);
    if (record.original_session_ids.parent.has_value()) {
      image_origin_id_set.insert(*record.original_session_ids.parent);
    }
    for (const auto& child : record.children) {
      image_origin_id_set.insert(child.original_id);
      image_origin_id_set.insert(
          identity_for_artifacts(child.artifacts, child.original_id).value());
    }
    image_origin_id_set.insert(
        identity_for_artifacts(record.artifacts,
                               record.original_session_ids.primary)
            .value());
  }
  for (const auto& prepared : prepared_sessions) {
    image_origin_id_set.insert(prepared.origin_ids.begin(),
                               prepared.origin_ids.end());
  }
  const std::vector<std::string> image_origin_paths{
      image_origin_path_set.begin(), image_origin_path_set.end()};
  const std::vector<std::string> image_origin_ids{
      image_origin_id_set.begin(), image_origin_id_set.end()};

  {
    for (auto& prepared : prepared_sessions) {
      if (prepared.refusal_reason.has_value()) continue;
      prepared.pair_set_applied = rewrite::derive_install_pair_set(
          prepared.record,
          target.workspace_root.generic_string(),
          path_flavor_for(target.workspace_root));
      std::set<std::string> mapped_node_ids;
      for (const auto& [original, installed] :
           prepared.installed_by_original) {
        (void)original;
        mapped_node_ids.insert(installed);
      }
      for (const auto& write : prepared.writes) {
        auto data = target.member_read(write.artifact);
        if (!data) {
          return std::unexpected(data.error());
        }
        if (!jsonl_decodable(*data)) {
          prepared.refusal_reason = "verify-hits";
          prepared.refusal_detail = "undecodable_line";
          prepared.outputs.clear();
          break;
        }
        auto rewritten = rewrite::rewrite_jsonl_bytes(
            *data, rewrite::PathPairsView{prepared.pair_set_applied},
            rewrite::IdPairsView{prepared.rewrite_ids});
        prepared.skipped_non_utf8 += rewritten.skipped_non_utf8;
        const auto identities = rollout_identities(rewritten.bytes);
        const bool primary_write =
            std::ranges::find(prepared.record.artifacts, write.artifact) !=
            prepared.record.artifacts.end();
        const auto identity_is_member = [&](const std::string& id) {
          return mapped_node_ids.contains(id) ||
                 (primary_write && prepared.installed_parent_id.has_value() &&
                  id == *prepared.installed_parent_id);
        };
        const bool recoverable_separate_parent =
            !primary_write || !prepared.installed_parent_id.has_value() ||
            (identities.session_id.has_value() &&
             *identities.session_id == *prepared.installed_parent_id) ||
            std::ranges::any_of(
                identities.parent_thread_ids,
                [&](const auto& parent_thread_id) {
                  return parent_thread_id == *prepared.installed_parent_id;
                });
        const bool edge_disagrees =
            write.expected_parent_id.has_value() &&
            std::ranges::any_of(
                identities.parent_thread_ids,
                [&](const auto& parent_thread_id) {
                  return parent_thread_id != *write.expected_parent_id;
                });
        if ((identities.id.has_value() &&
             *identities.id != write.installed_id) ||
            (identities.session_id.has_value() &&
             *identities.session_id != write.installed_id &&
             !identity_is_member(*identities.session_id)) ||
            std::ranges::any_of(
                identities.parent_thread_ids,
                [&](const auto& parent_thread_id) {
                  return !identity_is_member(parent_thread_id);
                }) ||
            edge_disagrees ||
            !recoverable_separate_parent) {
          prepared.refusal_reason = "containment_refused";
          prepared.refusal_detail = "staged_identity_mismatch";
          prepared.outputs.clear();
          break;
        }
        merge_verify(prepared.verify,
                     rewrite::verify_scan(rewritten.bytes,
                         rewrite::OriginPathsView{image_origin_paths},
                         rewrite::OriginIdsView{image_origin_ids}));
        prepared.outputs.push_back(std::move(rewritten.bytes));
      }
      if (const auto detail = verify_failure_detail(prepared.verify);
          detail.has_value() && !prepared.refusal_reason.has_value()) {
        prepared.refusal_reason = "verify-hits";
        prepared.refusal_detail = detail;
        prepared.outputs.clear();
      }
    }

    std::vector<secure_io::WriteRequest> writes;
    for (const auto& prepared : prepared_sessions) {
      if (prepared.refusal_reason.has_value()) continue;
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
          if (prepared.refusal_reason.has_value()) {
            result.sessions.push_back(InstallSessionOutcome{
                .image_session_id =
                    prepared.record.original_session_ids.primary,
                .outcome = InstallSessionOutcome::Outcome::failed,
                .reason = prepared.refusal_reason,
                .content_rewrite = std::nullopt,
                .host_version_unverified = prepared.host_version_unverified,
                .verify = prepared.verify,
                .detail = prepared.refusal_detail});
            continue;
          }
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
    if (prepared.refusal_reason.has_value()) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = prepared.record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::failed,
          .reason = prepared.refusal_reason,
          .content_rewrite = std::nullopt,
          .host_version_unverified = prepared.host_version_unverified,
          .verify = prepared.verify,
          .detail = prepared.refusal_detail});
      continue;
    }
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
