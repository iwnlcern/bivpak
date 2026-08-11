#include "adapters/claude_code/claude_code.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <limits>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
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
#include "adapters/version_floor.hpp"
#include "core/support/portability.hpp"

namespace biv::adapters {

namespace {

namespace fs = std::filesystem;

constexpr size_t kUnpinnedProjectKeyCap = 255;

struct DestinationPlan {
  std::string artifact;
  fs::path path;
  bool rewrite_content{true};
};

struct PreparedSession {
  manifest::AgentSessionEntry record;
  std::string installed_session_id;
  std::vector<DestinationPlan> destinations;
  bool host_version_unverified{false};
  InstallVerify verify;
  std::vector<std::vector<std::byte>> outputs;
  size_t skipped_non_utf8{0};
  std::optional<std::string> refusal_reason;
  std::optional<std::string> refusal_detail;
};

struct ProjectRoot {
  fs::path value;
};

struct CandidatePath {
  fs::path value;
};

struct SessionImageId {
  std::string_view value;
};

bool ascii_alpha(const char value) {
  return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

bool ascii_alnum(const char value) {
  return (value >= '0' && value <= '9') || (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

std::string project_key_for_path(const fs::path& path) {
  std::string key = path.generic_string();
  for (char& value : key) {
    if (!ascii_alnum(value)) {
      value = '-';
    }
  }
  return key;
}

manifest::PathFlavor path_flavor_for(const fs::path& path) {
  const std::string text = path.generic_string();
  if (text.size() >= 7 && text.starts_with("/mnt/") && text.at(6) == '/' && ascii_alpha(text.at(5))) {
    return manifest::PathFlavor::wsl;
  }
  return manifest::PathFlavor::posix;
}

std::string uuid4() {
  std::array<unsigned char, 16> bytes {};
  support::secure_random_bytes(bytes.data(), bytes.size());
  bytes.at(6) = static_cast<unsigned char>((bytes.at(6) & 0x0fU) | 0x40U);
  bytes.at(8) = static_cast<unsigned char>((bytes.at(8) & 0x3fU) | 0x80U);

  constexpr std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string out;
  out.reserve(36);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (i == 4U || i == 6U || i == 8U || i == 10U) {
      out.push_back('-');
    }
    out.push_back(hex.at((bytes.at(i) >> 4U) & 0x0fU));
    out.push_back(hex.at(bytes.at(i) & 0x0fU));
  }
  return out;
}

bool path_inside(const CandidatePath candidate, const ProjectRoot root) {
  const auto rel = candidate.value.lexically_normal().lexically_relative(root.value.lexically_normal());
  if (rel.empty()) {
    return false;
  }
  const auto begin = rel.begin();
  return begin != rel.end() && *begin != "..";
}

bool safe_relative_path(const std::string_view path) {
  if (path.empty() || path.front() == '/' || path.find('\\') != std::string_view::npos) {
    return false;
  }
  fs::path rel{std::string{path}};
  for (const auto& part : rel) {
    if (part.empty() || part == "." || part == "..") {
      return false;
    }
  }
  return true;
}

std::optional<DestinationPlan> destination_for_artifact(const std::string& artifact,
                                                        const SessionImageId original_session_id,
                                                        std::string_view installed_session_id,
                                                        const ProjectRoot project_root) {
  const std::string prefix = "agents/claude-code/";
  if (!artifact.starts_with(prefix)) {
    return std::nullopt;
  }
  const std::string_view rest = std::string_view{artifact}.substr(prefix.size());
  const std::string main_name = std::string{original_session_id.value} + ".jsonl";
  if (rest == main_name) {
    const auto path = project_root.value / (std::string{installed_session_id} + ".jsonl");
    if (!path_inside(CandidatePath{path}, project_root)) {
      return std::nullopt;
    }
    return DestinationPlan{.artifact = artifact, .path = path, .rewrite_content = true};
  }

  const std::string subtree_prefix = std::string{original_session_id.value} + "/";
  if (!rest.starts_with(subtree_prefix)) {
    return std::nullopt;
  }
  const std::string_view subtree_rel = rest.substr(subtree_prefix.size());
  if (!safe_relative_path(subtree_rel)) {
    return std::nullopt;
  }
  const auto path = project_root.value / std::string{installed_session_id} / fs::path{std::string{subtree_rel}};
  if (!path_inside(CandidatePath{path}, project_root)) {
    return std::nullopt;
  }
  return DestinationPlan{.artifact = artifact, .path = path, .rewrite_content = !artifact.ends_with(".meta.json")};
}

std::vector<std::string> all_artifacts(const manifest::AgentSessionEntry& record) {
  std::vector<std::string> artifacts = record.artifacts;
  for (const auto& child : record.children) {
    artifacts.insert(artifacts.end(), child.artifacts.begin(), child.artifacts.end());
  }
  return artifacts;
}

std::vector<std::pair<std::string, std::string>> id_pairs_for(const manifest::AgentSessionEntry& record,
                                                              std::string_view installed_session_id) {
  return {{record.original_session_ids.primary, std::string{installed_session_id}}};
}

bool message_uuid_field(const std::string_view key) {
  return key == "uuid" || key == "parentUuid" || key == "leafUuid" ||
         key == "sourceToolAssistantUUID";
}

std::string string_from_bytes(const std::span<const std::byte> bytes) {
  std::string out;
  out.reserve(bytes.size());
  for (const std::byte value : bytes) {
    out.push_back(static_cast<char>(value));
  }
  return out;
}

void collect_message_uuid_values(simdjson::dom::element element,
                                 std::set<std::string>& values);

void collect_message_uuid_object(simdjson::dom::object object,
                                 std::set<std::string>& values) {
  for (auto field : object) {
    if (message_uuid_field(field.key)) {
      std::string_view value;
      if (!field.value.get(value) && !value.empty()) {
        values.emplace(value);
      }
    }
    collect_message_uuid_values(field.value, values);
  }
}

void collect_message_uuid_values(simdjson::dom::element element,
                                 std::set<std::string>& values) {
  switch (element.type()) {
    case simdjson::dom::element_type::ARRAY: {
      simdjson::dom::array array;
      if (element.get(array)) {
        return;
      }
      for (auto item : array) {
        collect_message_uuid_values(item, values);
      }
      return;
    }
    case simdjson::dom::element_type::OBJECT: {
      simdjson::dom::object object;
      if (!element.get(object)) {
        collect_message_uuid_object(object, values);
      }
      return;
    }
    default:
      return;
  }
}

void collect_message_uuid_values_from_jsonl(std::span<const std::byte> bytes,
                                            std::set<std::string>& values) {
  const std::string input_storage = string_from_bytes(bytes);
  const std::string_view input{input_storage};
  size_t start = 0;
  while (start < input.size()) {
    const size_t newline = input.find('\n', start);
    const size_t end =
        newline == std::string_view::npos ? input.size() : newline;
    const std::string_view line = input.substr(start, end - start);
    simdjson::padded_string padded{line};
    simdjson::dom::parser parser;
    simdjson::dom::element root;
    if (!parser.parse(padded).get(root)) {
      collect_message_uuid_values(root, values);
    }
    if (newline == std::string_view::npos) {
      break;
    }
    start = newline + 1U;
  }
}

std::vector<std::pair<std::string, std::string>> minted_message_uuid_pairs(
    const std::set<std::string>& origins) {
  std::vector<std::pair<std::string, std::string>> pairs;
  pairs.reserve(origins.size());
  for (const auto& origin : origins) {
    pairs.push_back({origin, uuid4()});
  }
  return pairs;
}

std::vector<std::string> origin_ids_for_primary(
    const std::string_view primary,
    const std::vector<std::pair<std::string, std::string>>& message_ids) {
  std::vector<std::string> ids{std::string{primary}};
  for (const auto& pair : message_ids) {
    ids.push_back(pair.first);
  }
  return ids;
}

std::vector<std::string> origin_ids_for(
    const manifest::AgentSessionEntry& record,
    const std::vector<std::pair<std::string, std::string>>& message_ids) {
  return origin_ids_for_primary(record.original_session_ids.primary,
                                message_ids);
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

InstallSessionOutcome failed_outcome(
    const manifest::AgentSessionEntry& record, std::string reason,
    std::optional<std::string> detail = std::nullopt) {
  return InstallSessionOutcome{
      .image_session_id = record.original_session_ids.primary,
      .outcome = InstallSessionOutcome::Outcome::failed,
      .reason = std::move(reason),
      .content_rewrite = std::nullopt,
      .host_version_unverified = false,
      .verify = {},
      .detail = std::move(detail)};
}

fs::path claude_root_for_host(const Host& host) {
  if (host.env.getenv) {
    auto configured = host.env.getenv("CLAUDE_CONFIG_DIR");
    if (configured.has_value()) {
      return fs::path{*configured};
    }
  }
  if (!host.env.home.empty()) {
    return host.env.home / ".claude";
  }
  return host.home / ".claude";
}

std::optional<std::string> parse_claude_version(const std::string_view raw) {
  const auto begin = raw.find_first_not_of(" \t\r\n");
  if (begin == std::string_view::npos) {
    return std::nullopt;
  }
  auto version = version_floor::extract_single_version(raw);
  if (!version.has_value() || !raw.substr(begin).starts_with(*version)) {
    return std::nullopt;
  }
  auto suffix = begin + version->size();
  suffix = raw.find_first_not_of(" \t", suffix);
  if (suffix == std::string_view::npos || !raw.substr(suffix).starts_with("(Claude Code)")) {
    return std::nullopt;
  }
  return version;
}

std::optional<support::ProbeEvidence> observe_claude(const Host& host) {
  const auto pin = host.pinned_bins.find("claude-code");
  const std::optional<fs::path> requested =
      pin == host.pinned_bins.end() ? std::nullopt : std::optional<fs::path>{pin->second};
  if (!host.version_probe) {
    return std::nullopt;
  }
  auto observed = host.version_probe("claude", requested);
  if (!observed) {
    return support::ProbeEvidence{.agent = "claude-code",
                                  .requested = requested,
                                  .executed = std::nullopt,
                                  .pinned = requested.has_value(),
                                  .outcome = support::ProbeOutcome::spawn_error,
                                  .exit_code = -1,
                                  .raw = support::sanitize_utf8(observed.error().detail),
                                  .parsed = std::nullopt};
  }
  observed->agent = "claude-code";
  if (requested.has_value()) {
    observed->requested = requested;
    observed->pinned = true;
  }
  return std::move(*observed);
}

Capabilities probe_capabilities(const Host& host) {
  const auto root = claude_root_for_host(host);
  std::error_code error;
  const bool store_exists = fs::exists(root, error);
  auto probe = observe_claude(host);
  std::optional<std::string> parsed;
  if (probe.has_value() && probe->outcome == support::ProbeOutcome::ok) {
    probe->parsed = parse_claude_version(probe->raw);
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
        version_floor::row_for("claude-code").surveyed_through);
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
      newer_than_survey, false,
      {.collect = store_exists,
       .install = store_exists,
       .rewrite = store_exists},
      std::move(probe));
}

}  // namespace

expected<InstallResult> claude_code_install(const InstallTarget& target,
                                            const Consent consent,
                                            const std::span<const manifest::AgentSessionEntry> records) {
  InstallResult result;
  result.mode = consent == Consent::yes ? InstallResult::Mode::host_installed : InstallResult::Mode::staged;
  const auto project_key = project_key_for_path(target.workspace_root);
  if (project_key.size() > kUnpinnedProjectKeyCap) {
    for (const auto& record : records) {
      result.sessions.push_back(failed_outcome(record, "long_path_key_unpinned"));
    }
    return result;
  }

  const auto project_root = ProjectRoot{target.target_store.root / "projects" / project_key};
  constexpr std::string_view containment_probe_id =
      "00000000-0000-4000-8000-000000000000";
  for (const auto& record : records) {
    for (const auto& artifact : all_artifacts(record)) {
      if (!destination_for_artifact(
               artifact, SessionImageId{record.original_session_ids.primary},
               containment_probe_id, project_root)
               .has_value()) {
        for (const auto& refused : records) {
          result.sessions.push_back(
              failed_outcome(refused, "containment_refused"));
        }
        return result;
      }
    }
  }

  const auto& caps = target.capabilities;
  std::vector<PreparedSession> prepared;
  prepared.reserve(records.size());
  for (const auto& record : records) {
    const auto admission = version_floor::admit(
        {.agent = "claude-code",
         .host_version = caps.agent_version(),
         .image_version = record.agent_version_at_pack});
    if (!admission.admitted) {
      prepared.push_back(PreparedSession{
          .record = record,
          .installed_session_id = {},
          .destinations = {},
          .host_version_unverified = false,
          .verify = {},
          .outputs = {},
          .skipped_non_utf8 = 0,
          .refusal_reason = "not-validated",
          .refusal_detail = std::string{admission.detail}});
      continue;
    }
    PreparedSession session{.record = record,
                            .installed_session_id = uuid4(),
                            .destinations = {},
                            .host_version_unverified =
                                admission.host_version_unverified,
                            .verify = {},
                            .outputs = {},
                            .skipped_non_utf8 = 0,
                            .refusal_reason = std::nullopt,
                            .refusal_detail = std::nullopt};
    for (const auto& artifact : all_artifacts(record)) {
      auto destination = destination_for_artifact(artifact,
                                                 SessionImageId{record.original_session_ids.primary},
                                                 session.installed_session_id,
                                                 project_root);
      if (!destination.has_value()) {
        for (const auto& refused : records) {
          result.sessions.push_back(
              failed_outcome(refused, "containment_refused"));
        }
        return result;
      }
      std::error_code ec;
      if (fs::exists(destination->path, ec)) {
        session.refusal_reason = "error";
        session.refusal_detail = "collision_refused";
        break;
      }
      session.destinations.push_back(std::move(*destination));
    }
    prepared.push_back(std::move(session));
  }

  if (consent == Consent::yes) {
    for (auto& session : prepared) {
      if (session.refusal_reason.has_value()) {
        continue;
      }
      const auto pair_set = rewrite::derive_pair_set(
          session.record.original_path, session.record.path_flavor,
          target.workspace_root.generic_string(),
          path_flavor_for(target.workspace_root));
      const auto origins = rewrite::origins_from_pairs(pair_set);
      std::vector<std::vector<std::byte>> inputs;
      inputs.reserve(session.destinations.size());
      std::set<std::string> message_uuid_origins;
      for (const auto& destination : session.destinations) {
        auto data = target.member_read(destination.artifact);
        if (!data) {
          return std::unexpected(data.error());
        }
        if (destination.rewrite_content) {
          collect_message_uuid_values_from_jsonl(*data, message_uuid_origins);
        }
        inputs.push_back(std::move(*data));
      }
      auto message_ids = minted_message_uuid_pairs(message_uuid_origins);
      auto ids = id_pairs_for(session.record, session.installed_session_id);
      ids.insert(ids.end(), message_ids.begin(), message_ids.end());
      const auto origin_ids = origin_ids_for(session.record, message_ids);
      for (size_t i = 0; i < session.destinations.size(); ++i) {
        const auto& destination = session.destinations.at(i);
        auto output = std::move(inputs.at(i));
        if (destination.rewrite_content) {
          auto rewritten = rewrite::rewrite_jsonl_bytes(
              output, rewrite::PathPairsView{pair_set},
              rewrite::IdPairsView{ids});
          session.skipped_non_utf8 += rewritten.skipped_non_utf8;
          output = std::move(rewritten.bytes);
        }
        merge_verify(session.verify,
                     rewrite::verify_scan(output,
                         rewrite::OriginPathsView{origins},
                         rewrite::OriginIdsView{origin_ids}));
        session.outputs.push_back(std::move(output));
      }
    }
    if (std::ranges::any_of(prepared, [](const PreparedSession& session) {
          return session.verify.origin_path_hits != 0U ||
                 session.verify.origin_id_hits != 0U;
        })) {
      for (const auto& session : prepared) {
        if (session.refusal_reason.has_value()) {
          result.sessions.push_back(failed_outcome(
              session.record, *session.refusal_reason,
              session.refusal_detail));
          continue;
        }
        auto outcome = failed_outcome(session.record, "containment_refused",
                                      "rewrite_verify_failed");
        outcome.verify = session.verify;
        result.sessions.push_back(std::move(outcome));
      }
      return result;
    }

    std::vector<secure_io::WriteRequest> writes;
    for (const auto& session : prepared) {
      // A refused session contributes nothing to the batch. Its destinations
      // may be non-empty while outputs is empty, so indexing outputs.at(i)
      // here would otherwise throw std::out_of_range in the CLI.
      if (session.refusal_reason.has_value()) {
        continue;
      }
      for (size_t i = 0; i < session.destinations.size(); ++i) {
        writes.push_back(secure_io::WriteRequest{
            .relative_path = session.destinations.at(i).path.lexically_relative(
                target.target_store.root),
            .bytes = session.outputs.at(i)});
      }
    }
    if (!writes.empty()) {
      auto ok = secure_io::write_batch_no_replace(target.target_store.root, writes);
      if (!ok) {
        const bool containment = ok.error().detail == "containment_refused";
        // Type and reason first; errno detail attaches only to the ambient
        // cohort and never to a containment row.
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
        // No clear(): pre-publish refusals keep their own reason and detail;
        // only records whose writes joined the cohort inherit this fault.
        for (const auto& session : prepared) {
          if (session.refusal_reason.has_value()) {
            result.sessions.push_back(failed_outcome(
                session.record, *session.refusal_reason,
                session.refusal_detail));
            continue;
          }
          result.sessions.push_back(failed_outcome(
              session.record, cohort_reason, cohort_detail));
        }
        return result;
      }
    }
  }

  for (auto& session : prepared) {
    if (session.refusal_reason.has_value()) {
      result.sessions.push_back(failed_outcome(
          session.record, *session.refusal_reason, session.refusal_detail));
      continue;
    }
    result.id_map.push_back(IdMapEntry{.agent = "claude-code",
                                       .image_session_id = session.record.original_session_ids.primary,
                                       .installed_session_id = session.installed_session_id,
                                       .children = {}});
    if (consent == Consent::no) {
      result.sessions.push_back(InstallSessionOutcome{
          .image_session_id = session.record.original_session_ids.primary,
          .outcome = InstallSessionOutcome::Outcome::staged,
          .reason = std::nullopt,
          .content_rewrite = std::nullopt,
          .host_version_unverified = session.host_version_unverified,
          .verify = {},
          .detail = std::nullopt});
      continue;
    }

    result.sessions.push_back(InstallSessionOutcome{.image_session_id = session.record.original_session_ids.primary,
                                                    .outcome = InstallSessionOutcome::Outcome::installed,
                                                    .reason = std::nullopt,
                                                    .content_rewrite = "pair",
                                                    .host_version_unverified = session.host_version_unverified,
                                                    .verify = session.verify,
                                                    .detail = non_utf8_detail(session.skipped_non_utf8)});
    result.activation.push_back(
        Activation{.agent = "claude-code", .command = "claude --resume " + session.installed_session_id});
  }
  return result;
}

expected<RewriteReport> claude_code_rewrite(const std::span<const SessionRecord> records,
                                            const InstallTarget& target) {
  RewriteReport report;
  const auto target_flavor = path_flavor_for(target.workspace_root);
  for (const auto& record : records) {
    const auto pair_set = rewrite::derive_pair_set(record.original_path,
                                                   record.path_flavor,
                                                   target.workspace_root.generic_string(),
                                                   target_flavor);
    const auto origins = rewrite::origins_from_pairs(pair_set);
    std::vector<std::vector<std::byte>> inputs;
    inputs.reserve(record.artifacts.size());
    std::set<std::string> message_uuid_origins;
    for (const auto& artifact : record.artifacts) {
      auto data = target.member_read(artifact);
      if (!data) {
        return std::unexpected(data.error());
      }
      collect_message_uuid_values_from_jsonl(*data, message_uuid_origins);
      inputs.push_back(std::move(*data));
    }
    auto ids = std::vector<std::pair<std::string, std::string>>{
        {record.original_session_id, uuid4()}};
    auto message_ids = minted_message_uuid_pairs(message_uuid_origins);
    ids.insert(ids.end(), message_ids.begin(), message_ids.end());
    const auto origin_ids =
        origin_ids_for_primary(record.original_session_id, message_ids);
    for (size_t i = 0; i < record.artifacts.size(); ++i) {
      auto rewritten = rewrite::rewrite_jsonl_bytes(
          inputs.at(i), rewrite::PathPairsView{pair_set},
          rewrite::IdPairsView{ids});
      report.skipped_non_utf8 += rewritten.skipped_non_utf8;
      auto verify = rewrite::verify_scan(rewritten.bytes,
                                         rewrite::OriginPathsView{origins},
                                         rewrite::OriginIdsView{origin_ids});
      const auto& artifact = record.artifacts.at(i);
      report.per_artifact_hits.push_back({artifact, verify});
      merge_verify(report.verify, verify);
    }
  }
  return report;
}

Capabilities claude_code_capabilities(const Host& host) { return probe_capabilities(host); }

}  // namespace biv::adapters
