#include "core/open/sessions.hpp"

#include <algorithm>
#include <iterator>
#include <span>
#include <string_view>

#include "adapters/registry.hpp"
#include "adapters/secure_io.hpp"

namespace biv::core_sessions {

namespace {

bool decision_for(const ConsentDecision& consent, const std::string_view agent) {
  const auto found = std::ranges::find(consent.per_agent, agent, &std::pair<std::string, bool>::first);
  return found != consent.per_agent.end() && found->second;
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
      return ErrKind::UnknownAgentSkipped;
    case SessionRowReport::Row::sessions_consent_skipped:
      return ErrKind::SessionsConsentSkipped;
    case SessionRowReport::Row::agent_not_validated_failed:
      return ErrKind::AgentNotValidatedFailed;
    case SessionRowReport::Row::skipped:
      return reason == "consent-denied" ? ErrKind::SessionsConsentSkipped : ErrKind::UnknownAgentSkipped;
    case SessionRowReport::Row::failed:
      break;
  }
  if (reason == "containment_refused" || reason == "verify-hits") {
    return ErrKind::ContainmentRefused;
  }
  if (reason == "store-absent" || reason == "not-validated") {
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
    return agent.parent_count != 0U || agent.child_count != 0U;
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
    ++found->parent_count;
    found->child_count += entry.children.size();
    found->entry_schema_skipped = found->entry_schema_skipped || entry.entry_schema > 1;
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
      } else if (entry.entry_schema > 1) {
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
    if (!decision_for(consent, agent.agent)) {
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::sessions_consent_skipped,
                                                .reason = "consent-denied",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = std::nullopt});
      }
      continue;
    }
    const auto caps = agent.caps.value_or(adapters::Capabilities{});
    const auto target_store = agent.store.value_or(adapters::Store{});
    if (!agent.caps.has_value() || caps.verdict == adapters::Capabilities::Verdict::unvalidated ||
        caps.verdict == adapters::Capabilities::Verdict::absent || !agent.store.has_value()) {
      const bool absent = !agent.store.has_value() || caps.verdict == adapters::Capabilities::Verdict::absent;
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::agent_not_validated_failed,
                                                .reason = absent ? "store-absent" : "not-validated",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = true,
                                                .live_at_pack = entry.live_at_pack,
                                                .detail = std::nullopt});
      }
      continue;
    }
    if (store_write_bits_absent(target_store.root)) {
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
                                                       .capabilities = caps},
                               adapters::Consent::yes, std::span<const manifest::AgentSessionEntry>{eligible});
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
                              .activation_suppressed = verify_hits,
                              .live_at_pack = false,
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
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::installed) {
        report.row = SessionRowReport::Row::installed;
        report.reason.reset();
        any_clean = true;
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::staged) {
        report.row = SessionRowReport::Row::session_install_failed;
        report.reason = "error";
      }
      outcome.rows.push_back(std::move(report));
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
  return outcome;
}

}  // namespace biv::core_sessions
