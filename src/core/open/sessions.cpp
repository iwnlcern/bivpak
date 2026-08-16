#include "core/open/sessions.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "adapters/registry.hpp"
#include "adapters/secure_io.hpp"
#include "adapters/version_floor.hpp"
#include "core/json/writer.hpp"

namespace biv::core_sessions {

namespace {

bool decision_for(const ConsentDecision& consent, const std::string_view agent) {
  const auto found = std::ranges::find(consent.per_agent, agent, &std::pair<std::string, bool>::first);
  return found != consent.per_agent.end() && found->second;
}

std::vector<std::byte> bytes(const std::string_view text) {
  std::vector<std::byte> out;
  out.reserve(text.size());
  for (const char value : text) {
    out.push_back(static_cast<std::byte>(value));
  }
  return out;
}

bool windows_drive_path(const std::string_view path) {
  const auto alpha = [](const char value) {
    return (value >= 'A' && value <= 'Z') ||
           (value >= 'a' && value <= 'z');
  };
  return path.size() >= 3U && alpha(path.at(0)) && path.at(1) == ':' &&
         (path.at(2) == '\\' || path.at(2) == '/');
}

expected<std::string> staged_original_path(
    const manifest::AgentSessionEntry& record,
    const std::span<const std::pair<std::string, std::string>>
        pair_set_applied) {
  std::string representative = record.original_path;
  if (windows_drive_path(representative)) {
    std::ranges::replace(representative, '/', '\\');
  }
  if (std::ranges::find(pair_set_applied, representative,
                        &std::pair<std::string, std::string>::first) ==
      pair_set_applied.end()) {
    return std::unexpected(BivError{ErrKind::RestoreWriteFailed,
                                    ".biv/agents/manifest.json",
                                    "invalid_staged_sidecar"});
  }
  return representative;
}

expected<std::string> staging_manifest_json(
    const std::vector<adapters::IdMapEntry>& id_map,
    const std::vector<manifest::AgentSessionEntry>& records,
    const std::vector<std::pair<std::string, std::string>>&
        pair_set_applied) {
  json::Writer writer;
  writer.begin_object();
  writer.key("id_map");
  writer.begin_array();
  for (const auto& entry : id_map) {
    const manifest::AgentSessionEntry* matched_record = nullptr;
    for (const auto& record : records) {
      if (record.agent != entry.agent ||
          record.original_session_ids.primary != entry.image_session_id) {
        continue;
      }
      if (matched_record != nullptr) {
        return std::unexpected(BivError{ErrKind::RestoreWriteFailed,
                                        ".biv/agents/manifest.json",
                                        "invalid_staged_sidecar"});
      }
      matched_record = &record;
    }
    if (matched_record == nullptr) {
      return std::unexpected(BivError{ErrKind::RestoreWriteFailed,
                                      ".biv/agents/manifest.json",
                                      "invalid_staged_sidecar"});
    }
    auto original_path =
        staged_original_path(*matched_record, pair_set_applied);
    if (!original_path) {
      return std::unexpected(original_path.error());
    }
    writer.begin_object();
    writer.key("agent");
    writer.value_string(entry.agent);
    writer.key("image_session_id");
    writer.value_string(entry.image_session_id);
    writer.key("installed_session_id");
    writer.value_string(entry.installed_session_id);
    writer.key("original_path");
    writer.value_string(*original_path);
    writer.key("children");
    writer.begin_array();
    for (const auto& [image_id, installed_id] : entry.children) {
      writer.begin_array();
      writer.value_string(image_id);
      writer.value_string(installed_id);
      writer.end_array();
    }
    writer.end_array();
    writer.end_object();
  }
  writer.end_array();

  writer.key("provenance_chain");
  writer.begin_array();
  std::vector<std::string> provenance_chain;
  for (const auto& record : records) {
    provenance_chain.push_back(record.original_session_ids.primary);
    for (const auto& child : record.children) {
      provenance_chain.push_back(child.original_id);
    }
  }
  std::ranges::sort(provenance_chain);
  const auto provenance_end =
      std::ranges::unique(provenance_chain).begin();
  provenance_chain.erase(provenance_end, provenance_chain.end());
  for (const auto& original_id : provenance_chain) {
    writer.value_string(original_id);
  }
  writer.end_array();

  writer.key("pair_set_applied");
  writer.begin_array();
  auto pair_set = pair_set_applied;
  std::ranges::sort(pair_set);
  const auto pair_end = std::ranges::unique(pair_set).begin();
  pair_set.erase(pair_end, pair_set.end());
  for (const auto& [original_path, staged_path] : pair_set) {
    writer.begin_array();
    writer.value_string(original_path);
    writer.value_string(staged_path);
    writer.end_array();
  }
  writer.end_array();
  writer.end_object();
  return writer.take();
}

expected<void> publish_staging_manifest(
    const std::filesystem::path& workspace_root,
    const std::vector<adapters::IdMapEntry>& id_map,
    const std::vector<manifest::AgentSessionEntry>& records,
    const std::vector<std::pair<std::string, std::string>>&
        pair_set_applied) {
  auto json = staging_manifest_json(id_map, records, pair_set_applied);
  if (!json) {
    return std::unexpected(json.error());
  }
  const auto payload = bytes(*json);
  const std::vector<adapters::secure_io::WriteRequest> writes{
      {.relative_path = ".biv/agents/manifest.json", .bytes = payload}};
  return adapters::secure_io::write_batch_no_replace(workspace_root, writes);
}

std::vector<AgentCaveat> staged_path_caveats(
    const std::filesystem::path& workspace_root,
    const std::vector<adapters::IdMapEntry>& id_map) {
  std::vector<AgentCaveat> out;
  for (const auto& ids : id_map) {
    const auto agent_root =
        workspace_root / ".biv" / "agents" / ids.agent;
    std::vector<std::string> installed_ids{ids.installed_session_id};
    for (const auto& child : ids.children) {
      installed_ids.push_back(child.second);
    }
    std::error_code error;
    std::filesystem::recursive_directory_iterator current{agent_root, error};
    const std::filesystem::recursive_directory_iterator end;
    while (!error && current != end) {
      const auto path = current->path();
      if (current->is_regular_file(error) && !error) {
        const auto relative =
            path.lexically_relative(workspace_root).generic_string();
        if (std::ranges::any_of(installed_ids, [&](const auto& id) {
              return relative.find(id) != std::string::npos;
            })) {
          out.push_back(AgentCaveat{.agent = ids.agent,
                                    .kind = "staged-byte-path",
                                    .note = relative});
        }
      }
      current.increment(error);
    }
  }
  std::ranges::sort(out, [](const AgentCaveat& left,
                            const AgentCaveat& right) {
    return std::tie(left.agent, left.note) < std::tie(right.agent, right.note);
  });
  return out;
}

std::optional<std::string> installed_id(const std::vector<adapters::IdMapEntry>& ids,
                                        const std::string_view image_id) {
  const auto found = std::ranges::find(ids, image_id, &adapters::IdMapEntry::image_session_id);
  if (found == ids.end()) {
    return std::nullopt;
  }
  return found->installed_session_id;
}

bool store_write_bits_absent(const std::filesystem::path& root) {
  std::error_code error;
  const auto permissions = std::filesystem::status(root, error).permissions();
  if (error) {
    return false;
  }
  constexpr auto write_bits = std::filesystem::perms::owner_write |
                              std::filesystem::perms::group_write |
                              std::filesystem::perms::others_write;
  return (permissions & write_bits) == std::filesystem::perms::none;
}

bool staging_carrier_preexists(const std::filesystem::path& workspace_root) {
  std::error_code error;
  const auto status = std::filesystem::symlink_status(
      workspace_root / ".biv" / "agents", error);
  if (!error) {
    return status.type() != std::filesystem::file_type::not_found;
  }
  return error != std::errc::no_such_file_or_directory;
}

std::optional<std::string> merged_detail(
    const std::optional<std::string>& existing,
    const std::optional<std::string>& additional) {
  if (!additional.has_value() || existing == additional) {
    return existing;
  }
  if (!existing.has_value()) {
    return additional;
  }
  return *existing + "; " + *additional;
}

}  // namespace

std::string install_failure_reason(const BivError& error) {
  for (const std::string_view reason : {"store_locked", "write_protected", "containment_refused"}) {
    if (error.detail.find(reason) != std::string::npos) {
      return std::string{reason};
    }
  }
  return "error";
}

std::optional<ErrKind> kind_for_row(const SessionRowReport::Row row, const std::string_view reason) {
  switch (row) {
    case SessionRowReport::Row::installed:
      return std::nullopt;
    case SessionRowReport::Row::containment_refused:
      return ErrKind::ContainmentRefused;
    case SessionRowReport::Row::session_install_failed:
      return ErrKind::SessionInstallFailed;
    case SessionRowReport::Row::unknown_agent_skipped:
      return reason == "entry-schema" ? ErrKind::EntrySchemaSkipped : ErrKind::UnknownAgentSkipped;
    case SessionRowReport::Row::sessions_consent_skipped:
      return ErrKind::SessionsConsentSkipped;
    case SessionRowReport::Row::sessions_staged:
      return ErrKind::SessionsStaged;
    case SessionRowReport::Row::agent_not_validated_failed:
      return ErrKind::AgentNotValidatedFailed;
    case SessionRowReport::Row::skipped:
      if (reason == "consent-denied") {
        return ErrKind::SessionsConsentSkipped;
      }
      return reason == "entry-schema" ? ErrKind::EntrySchemaSkipped : ErrKind::UnknownAgentSkipped;
    case SessionRowReport::Row::failed:
      break;
  }
  if (reason == "containment_refused" || reason == "verify-hits") {
    return ErrKind::ContainmentRefused;
  }
  if (reason == "store-absent") {
    return ErrKind::AgentNotValidatedFailed;
  }
  return ErrKind::SessionInstallFailed;
}

std::vector<adapters::Activation> filter_activation(
    const std::span<const adapters::Activation> activation,
    const std::span<const SessionRowReport> rows) {
  std::vector<adapters::Activation> safe;
  for (const auto& candidate : activation) {
    bool belongs_to_clean = false;
    bool belongs_to_rejected = false;
    for (const auto& row : rows) {
      if (row.agent != candidate.agent || !row.installed_session_id.has_value()) {
        continue;
      }
      if (candidate.command.find(*row.installed_session_id) == std::string::npos) {
        continue;
      }
      const bool clean =
          row.row == SessionRowReport::Row::installed && !row.activation_suppressed;
      belongs_to_clean = belongs_to_clean || clean;
      belongs_to_rejected = belongs_to_rejected || !clean;
    }
    if (belongs_to_clean && !belongs_to_rejected) {
      safe.push_back(candidate);
    }
  }
  return safe;
}

bool SessionPreview::any_sessions() const {
  return std::ranges::any_of(agents, [](const AgentPreview& agent) {
    return agent.primary_count != 0U || agent.descendant_count != 0U;
  });
}

bool SessionPreview::any_entry_schema_skipped() const {
  return std::ranges::any_of(agents, [](const AgentPreview& agent) {
    return agent.entry_schema_skipped_count != 0U;
  });
}

expected<SessionPreview> build_preview(const manifest::Manifest& manifest, const adapters::Host& host) {
  SessionPreview preview;
  for (const auto& entry : manifest.agent_sessions) {
    auto found = std::ranges::find(preview.agents, entry.agent, &AgentPreview::agent);
    if (found == preview.agents.end()) {
      AgentPreview next;
      next.agent = entry.agent;
      next.adapter = adapters::find_adapter(entry.agent);
      next.known_adapter = next.adapter != nullptr;
      if (next.adapter != nullptr) {
        auto stores = next.adapter->discover(host.env);
        if (!stores) {
          return std::unexpected(stores.error());
        }
        if (!stores->empty()) {
          next.store = stores->front();
        }
        next.caps = next.adapter->capabilities(host);
      }
      preview.agents.push_back(std::move(next));
      found = std::prev(preview.agents.end());
    }
    if (entry.entry_schema > kEntrySchemaSupportedCeiling) {
      found->entry_schema_skipped_count += 1U + entry.children.size();
      if (entry.entry_schema > manifest::kEntrySchemaParseCeiling) {
        ++found->entry_schema_unparsed_count;
      }
    } else {
      ++found->primary_count;
      found->descendant_count += entry.children.size();
    }
  }
  return preview;
}

expected<SessionPreview> build_preview(const manifest::Manifest& manifest, const adapters::Env& env) {
  return build_preview(
      manifest,
      adapters::Host{.home = env.home,
                     .env = env,
                     .version_probe = {},
                     .pinned_bins = {}});
}

ConsentDecision resolve_consent(const ConsentSpec& spec, const SessionPreview& preview,
                                const std::optional<bool> prompt_answer) {
  ConsentDecision result;
  if (spec.global != ConsentValue::unset || !spec.per_agent.empty()) {
    result.source = ConsentSource::flag;
  } else if (prompt_answer.has_value()) {
    result.source = ConsentSource::prompt;
  }
  for (const auto& agent : preview.agents) {
    bool allowed = false;
    if (spec.global != ConsentValue::unset) {
      allowed = spec.global == ConsentValue::yes;
    } else if (!spec.per_agent.empty()) {
      const auto found = std::ranges::find(spec.per_agent, agent.agent,
                                           &std::pair<std::string, ConsentValue>::first);
      allowed = found != spec.per_agent.end() && found->second == ConsentValue::yes;
    } else if (prompt_answer.has_value()) {
      allowed = *prompt_answer;
    }
    result.per_agent.emplace_back(agent.agent, allowed);
  }
  return result;
}

expected<SessionsOutcome> run_session_leg(const SessionPreview& preview,
                                          const ConsentDecision& consent,
                                          const manifest::Manifest& manifest,
                                          const std::filesystem::path& final_workspace_root,
                                          const adapters::MemberRead& member_read) {
  SessionsOutcome outcome;
  std::vector<adapters::IdMapEntry> staged_id_map;
  std::vector<manifest::AgentSessionEntry> staged_records;
  std::vector<std::pair<std::string, std::string>> staged_pair_set;
  const bool foreign_staging_carrier =
      staging_carrier_preexists(final_workspace_root);
  for (const auto& agent : preview.agents) {
    std::vector<manifest::AgentSessionEntry> eligible;
    for (const auto& entry : manifest.agent_sessions) {
      if (entry.agent != agent.agent) {
        continue;
      }
      if (!agent.known_adapter) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::unknown_agent_skipped,
                                                .reason = "unknown-agent",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = std::nullopt});
      } else if (entry.entry_schema > kEntrySchemaSupportedCeiling) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::unknown_agent_skipped,
                                                .reason = "entry-schema",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = std::nullopt});
      } else {
        eligible.push_back(entry);
      }
    }
    if (eligible.empty()) {
      continue;
    }
    const bool absent = !agent.caps.has_value() || !agent.store.has_value() ||
                        agent.caps->verdict() ==
                            adapters::Capabilities::Verdict::absent;
    const bool unreadable =
        agent.caps.has_value() &&
        agent.caps->verdict() == adapters::Capabilities::Verdict::unreadable;
    if (absent || unreadable) {
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{
            .agent = entry.agent,
            .image_session_id = entry.original_session_ids.primary,
            .row = SessionRowReport::Row::agent_not_validated_failed,
            .reason = absent ? "store-absent" : "host-version-unreadable",
            .installed_session_id = std::nullopt,
            .host_version_unverified = false,
            .activation_suppressed = true,
            .live_at_pack = entry.live_at_pack,
            .detail = std::nullopt});
      }
      continue;
    }
    const auto& caps = *agent.caps;
    const auto& target_store = *agent.store;
    const auto adapter_consent = decision_for(consent, agent.agent)
                                     ? adapters::Consent::yes
                                     : adapters::Consent::no;
    if (adapter_consent == adapters::Consent::no &&
        foreign_staging_carrier) {
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{
            .agent = entry.agent,
            .image_session_id = entry.original_session_ids.primary,
            .row = SessionRowReport::Row::containment_refused,
            .reason = "foreign_staging_carrier",
            .installed_session_id = std::nullopt,
            .host_version_unverified = false,
            .activation_suppressed = true,
            .live_at_pack = entry.live_at_pack,
            .detail = std::nullopt});
      }
      continue;
    }
    if (adapter_consent == adapters::Consent::yes &&
        store_write_bits_absent(target_store.root)) {
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::session_install_failed,
                                                .reason = "store_locked",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = true,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = std::nullopt});
      }
      continue;
    }

    auto installed =
        agent.adapter->install(adapters::InstallTarget{.workspace_root = final_workspace_root,
                                                       .target_store = target_store,
                                                       .member_read = member_read,
                                                       .capabilities = caps,
                                                       .packer_home = manifest.packer_home},
                               adapter_consent,
                               std::span<const manifest::AgentSessionEntry>{eligible});
    if (!installed) {
      const auto reason = install_failure_reason(installed.error());
      const bool containment = reason == "containment_refused";
      // Type and reason are determined first. The errno detail attaches only
      // to session_install_failed rows and never to containment rows.
      std::optional<std::string> detail;
      if (!containment) {
        if (const auto symbol =
                adapters::secure_io::errno_symbol(installed.error().err_no);
            symbol.has_value()) {
          detail = std::string{*symbol};
        }
      }
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = containment
                                                           ? SessionRowReport::Row::containment_refused
                                                           : SessionRowReport::Row::session_install_failed,
                                                .reason = reason,
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = true,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = detail});
      }
      continue;
    }

    bool any_clean = false;
    bool any_staged = false;
    const size_t first_adapter_row = outcome.rows.size();
    for (const auto& row : installed->sessions) {
      const bool verify_hits = row.verify.origin_path_hits != 0U || row.verify.origin_id_hits != 0U;
      SessionRowReport report{.agent = agent.agent,
                              .image_session_id = row.image_session_id,
                              .row = row.reason == "containment_refused"
                                         ? SessionRowReport::Row::containment_refused
                                         : SessionRowReport::Row::session_install_failed,
                              .reason = row.reason,
                              .installed_session_id = installed_id(installed->id_map, row.image_session_id),
                              .host_version_unverified = row.host_version_unverified,
                              .activation_suppressed =
                                  row.outcome == adapters::InstallSessionOutcome::Outcome::failed ||
                                  verify_hits,
                              .live_at_pack = true,
                              .detail = row.detail};
      const auto source = std::ranges::find_if(manifest.agent_sessions, [&](const auto& entry) {
        return entry.agent == agent.agent && entry.original_session_ids.primary == row.image_session_id;
      });
      if (source != manifest.agent_sessions.end()) {
        report.live_at_pack = source->live_at_pack;
      }
      if (verify_hits) {
        report.row = SessionRowReport::Row::containment_refused;
        report.reason = "verify-hits";
      } else if (row.outcome ==
                     adapters::InstallSessionOutcome::Outcome::failed &&
                 row.detail == adapters::version_floor::kBasisNewerThanHost) {
        report.row = SessionRowReport::Row::agent_not_validated_failed;
        report.reason = "basis-newer-than-host";
      } else if (row.outcome ==
                     adapters::InstallSessionOutcome::Outcome::failed &&
                 row.detail == adapters::version_floor::kBasisUnorderable) {
        report.row = SessionRowReport::Row::agent_not_validated_failed;
        report.reason = "basis-unorderable";
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::installed) {
        report.row = SessionRowReport::Row::installed;
        report.reason.reset();
        any_clean = true;
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::staged) {
        report.row = SessionRowReport::Row::sessions_staged;
        report.reason.reset();
        any_staged = true;
        const auto map_entry = std::ranges::find(
            installed->id_map, row.image_session_id,
            &adapters::IdMapEntry::image_session_id);
        if (map_entry != installed->id_map.end() &&
            source != manifest.agent_sessions.end()) {
          staged_id_map.push_back(*map_entry);
          staged_records.push_back(*source);
        }
      }
      outcome.rows.push_back(std::move(report));
    }
    if (any_staged) {
      staged_pair_set.insert(staged_pair_set.end(),
                             installed->pair_set_applied.begin(),
                             installed->pair_set_applied.end());
    }
    outcome.id_map.insert(outcome.id_map.end(), installed->id_map.begin(), installed->id_map.end());
    if (any_clean) {
      const auto adapter_rows = std::span<const SessionRowReport>{outcome.rows}.subspan(first_adapter_row);
      auto safe = filter_activation(installed->activation, adapter_rows);
      outcome.activation.insert(outcome.activation.end(), safe.begin(), safe.end());
    }
    for (const auto& note : agent.adapter->state_inventory().caveat_facts.notes) {
      outcome.caveats.push_back(AgentCaveat{.agent = agent.agent, .kind = note.first, .note = note.second});
    }
  }
  if (!staged_id_map.empty()) {
    if (auto published = publish_staging_manifest(
            final_workspace_root, staged_id_map, staged_records,
            staged_pair_set);
        !published) {
      auto disclosures =
          staged_path_caveats(final_workspace_root, staged_id_map);
      outcome.caveats.insert(outcome.caveats.end(), disclosures.begin(),
                             disclosures.end());
      const auto reason = install_failure_reason(published.error());
      const bool containment = reason == "containment_refused";
      std::optional<std::string> detail;
      if (!containment) {
        if (const auto symbol =
                adapters::secure_io::errno_symbol(published.error().err_no);
            symbol.has_value()) {
          detail = std::string{*symbol};
        }
      }
      for (auto& row : outcome.rows) {
        if (row.row != SessionRowReport::Row::sessions_staged) {
          continue;
        }
        row.row = containment
                      ? SessionRowReport::Row::containment_refused
                      : SessionRowReport::Row::session_install_failed;
        row.reason = reason;
        row.detail = merged_detail(row.detail, detail);
        row.activation_suppressed = true;
      }
    }
  }
  return outcome;
}

}  // namespace biv::core_sessions
