#include "adapters/codex/codex.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <fcntl.h>
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-literal-operator"
#endif
#include <simdjson.h>
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif
#include <unistd.h>

#include "adapters/rewrite_common.hpp"
#include "adapters/secure_io.hpp"
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

std::optional<std::string> string_field_from_json_file(const fs::path& path, std::string_view key) {
  std::ifstream input{path, std::ios::binary};
  if (!input) {
    return std::nullopt;
  }
  std::string json{std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
  simdjson::padded_string padded{json};
  simdjson::dom::parser parser;
  simdjson::dom::element root;
  if (parser.parse(padded).get(root)) {
    return std::nullopt;
  }
  simdjson::dom::object object;
  if (root.get(object)) {
    return std::nullopt;
  }
  std::string_view value;
  if (object.at_key(key).get(value)) {
    return std::nullopt;
  }
  return std::string{value};
}

std::optional<std::string> rollout_cli_version(const fs::path& path) {
  std::ifstream input{path};
  std::string line;
  while (std::getline(input, line)) {
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (parser.parse(padded).get(root)) {
      continue;
    }
    simdjson::dom::object object;
    if (root.get(object)) {
      continue;
    }
    simdjson::dom::object payload;
    if (object.at_key("payload").get(payload)) {
      continue;
    }
    std::string_view version;
    if (!payload.at_key("cli_version").get(version)) {
      return std::string{version};
    }
  }
  return std::nullopt;
}

std::optional<std::string> codex_version_from_store(const fs::path& root) {
  if (auto version = string_field_from_json_file(root / "version.json", "version"); version.has_value()) {
    return version;
  }
  const auto sessions = root / "sessions";
  std::error_code ec;
  if (!fs::exists(sessions, ec)) {
    return std::nullopt;
  }
  for (fs::recursive_directory_iterator
           it{sessions, fs::directory_options::none, ec},
       end;
       !ec && it != end; it.increment(ec)) {
    const auto& entry = *it;
    if (!entry.is_symlink(ec) && entry.is_regular_file(ec) &&
        entry.path().filename().generic_string().starts_with("rollout-") &&
        entry.path().extension() == ".jsonl") {
      if (auto version = rollout_cli_version(entry.path());
          version.has_value()) {
        return version;
      }
    }
  }
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

bool validated_codex_version(std::string_view version) {
  return version.starts_with("0.142.") || version.starts_with("0.144.");
}

std::optional<bool> host_version_unverified_for_install(
    const Capabilities& caps, const std::string_view image_version) {
  if (caps.verdict == Capabilities::Verdict::validated) {
    return false;
  }
  if (caps.verdict == Capabilities::Verdict::unvalidated_host &&
      validated_codex_version(image_version)) {
    return true;
  }
  return std::nullopt;
}

Capabilities capabilities_for_root(const fs::path& root) {
  Capabilities caps{
      .agent_version = "unknown",
      .validated_range = "0.142.x, 0.144.x",
      .verdict = Capabilities::Verdict::absent,
      .long_path_keys_pinned = true,
      .per_verb = {.collect = false, .install = false, .rewrite = false}};
  std::error_code ec;
  if (!fs::exists(root, ec)) {
    return caps;
  }
  caps.per_verb = {.collect = true, .install = true, .rewrite = true};
  auto version = codex_version_from_store(root);
  if (!version) {
    caps.verdict = Capabilities::Verdict::unvalidated_host;
    return caps;
  }
  caps.agent_version = *version;
  caps.verdict = validated_codex_version(*version) ? Capabilities::Verdict::validated
                                                   : Capabilities::Verdict::unvalidated;
  return caps;
}

}  // namespace

expected<InstallResult> codex_install(const InstallTarget& target,
                                      const Consent consent,
                                      const std::span<const manifest::AgentSessionEntry> records) {
  InstallResult result;
  result.mode = consent == Consent::yes ? InstallResult::Mode::host_installed : InstallResult::Mode::staged;
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

  const auto host_caps = capabilities_for_root(target.target_store.root);
  std::vector<PreparedSession> prepared_sessions;
  prepared_sessions.reserve(records.size());
  for (const auto& record : records) {
    const auto host_version_unverified =
        host_version_unverified_for_install(host_caps,
                                            record.agent_version_at_pack);
    if (!host_version_unverified.has_value()) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::failed,
          .reason = "error",
          .content_rewrite = std::nullopt,
          .host_version_unverified = false,
          .verify = {},
          .detail = "capability_refused"});
      continue;
    }
    std::map<std::string, RolloutName> rollouts;
    rollouts.emplace(record.original_session_ids.primary, mint_rollout_name());
    PreparedSession prepared{.record = record,
                             .installed_id = rollouts.at(record.original_session_ids.primary).id,
                             .child_ids = {},
                             .writes = {},
                             .host_version_unverified =
                                 *host_version_unverified,
                             .verify = {},
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
          target.target_store.root / "sessions" / rollout.year / rollout.month /
          rollout.day /
          ("rollout-" + rollout.file_stamp + "-" + rollout.id + ".jsonl");
      prepared.writes.push_back(WritePlan{
          .artifact = artifact, .path = path, .installed_id = rollout.id});
    }
    prepared_sessions.push_back(std::move(prepared));
  }

  if (consent == Consent::yes) {
    for (auto& prepared : prepared_sessions) {
      const auto pair_set = rewrite::derive_pair_set(
          prepared.record.original_path, prepared.record.path_flavor,
          target.workspace_root.generic_string(),
          path_flavor_for(target.workspace_root));
      const auto origins = rewrite::origins_from_pairs(pair_set);
      const auto id_map = id_pairs_for(prepared.record, prepared.installed_id,
                                       prepared.child_ids);
      const auto origin_ids = origin_ids_for(prepared.record);
      for (const auto& write : prepared.writes) {
        auto data = target.member_read(write.artifact);
        if (!data) {
          return std::unexpected(data.error());
        }
        auto rewritten = rewrite::rewrite_jsonl_bytes(
            *data, rewrite::PathPairsView{pair_set},
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
      result.sessions.clear();
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
                target.target_store.root),
            .bytes = prepared.outputs.at(i)});
      }
    }
    if (!writes.empty()) {
      auto ok = secure_io::write_batch_no_replace(target.target_store.root, writes);
      if (!ok) {
        if (ok.error().detail != "containment_refused") {
          return std::unexpected(ok.error());
        }
        result.sessions.clear();
        for (const auto& prepared : prepared_sessions) {
          result.sessions.push_back(InstallSessionOutcome{
              .image_session_id = prepared.record.original_session_ids.primary,
              .outcome = InstallSessionOutcome::Outcome::failed,
              .reason = "containment_refused",
              .content_rewrite = std::nullopt,
              .host_version_unverified = prepared.host_version_unverified,
              .verify = prepared.verify,
              .detail = ok.error().path});
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
    if (consent == Consent::no) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = prepared.record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::staged,
          .reason = std::nullopt,
          .content_rewrite = std::nullopt,
          .host_version_unverified = prepared.host_version_unverified,
          .verify = {},
          .detail = std::nullopt});
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

Capabilities codex_capabilities(const Host& host) {
  return capabilities_for_root(codex_root_for_host(host));
}

}  // namespace biv::adapters
