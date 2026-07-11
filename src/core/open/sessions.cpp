#include "core/open/sessions.hpp"

#include <algorithm>
#include <map>
#include <span>
#include <string_view>

#include "adapters/registry.hpp"

namespace biv::core_sessions {

namespace {

bool decision_for(const ConsentDecision& consent, const std::string_view agent) {
  const auto found = std::ranges::find(consent.per_agent, agent, &std::pair<std::string, bool>::first);
  return found != consent.per_agent.end() && found->second;
}

std::string failure_reason(const BivError& error) {
  for (const std::string_view reason : {"store_locked", "write_protected", "containment_refused"}) {
    if (error.detail.find(reason) != std::string::npos) {
      return std::string{reason};
    }
  }
  return "error";
}

std::optional<std::string> installed_id(const std::vector<adapters::IdMapEntry>& ids,
                                        const std::string_view image_id) {
  const auto found = std::ranges::find(ids, image_id, &adapters::IdMapEntry::image_session_id);
  if (found == ids.end()) {
    return std::nullopt;
  }
  return found->installed_session_id;
}

}  // namespace

bool SessionPreview::any_sessions() const {
  return std::ranges::any_of(agents, [](const AgentPreview& agent) {
    return agent.parent_count != 0U || agent.child_count != 0U;
  });
}

expected<SessionPreview> build_preview(const manifest::Manifest& manifest, const adapters::Env& env) {
  SessionPreview preview;
  for (const auto& entry : manifest.agent_sessions) {
    auto found = std::ranges::find(preview.agents, entry.agent, &AgentPreview::agent);
    if (found == preview.agents.end()) {
      AgentPreview next;
      next.agent = entry.agent;
      next.adapter = adapters::find_adapter(entry.agent);
      next.known_adapter = next.adapter != nullptr;
      if (next.adapter != nullptr) {
        auto stores = next.adapter->discover(env);
        if (!stores) {
          return std::unexpected(stores.error());
        }
        if (!stores->empty()) {
          next.store = stores->front();
        }
        next.caps = next.adapter->capabilities(adapters::Host{.home = env.home, .env = env});
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

ConsentDecision resolve_consent(const ConsentSpec& spec,
                                const SessionPreview& preview,
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
                                                .row = SessionRowReport::Row::skipped,
                                                .reason = "unknown-agent",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack});
      } else if (entry.entry_schema > 1) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::skipped,
                                                .reason = "entry-schema",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack});
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
                                                .row = SessionRowReport::Row::skipped,
                                                .reason = "consent-denied",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = false,
                                                .live_at_pack = entry.live_at_pack});
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
                                                .row = SessionRowReport::Row::failed,
                                                .reason = absent ? "store-absent" : "not-validated",
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = true,
                                                .live_at_pack = entry.live_at_pack});
      }
      continue;
    }

    auto installed = agent.adapter->install(adapters::InstallTarget{.workspace_root = final_workspace_root,
                                                                     .target_store = target_store,
                                                                     .member_read = member_read},
                                            adapters::Consent::yes,
                                            std::span<const manifest::AgentSessionEntry>{eligible});
    if (!installed) {
      for (const auto& entry : eligible) {
        outcome.rows.push_back(SessionRowReport{.agent = entry.agent,
                                                .image_session_id = entry.original_session_ids.primary,
                                                .row = SessionRowReport::Row::failed,
                                                .reason = failure_reason(installed.error()),
                                                .installed_session_id = std::nullopt,
                                                .host_version_unverified = false,
                                                .activation_suppressed = true,
                                                .live_at_pack = entry.live_at_pack});
      }
      continue;
    }

    bool any_clean = false;
    for (const auto& row : installed->sessions) {
      const bool verify_hits = row.verify.origin_path_hits != 0U || row.verify.origin_id_hits != 0U;
      SessionRowReport report{.agent = agent.agent,
                              .image_session_id = row.image_session_id,
                              .row = SessionRowReport::Row::failed,
                              .reason = row.reason,
                              .installed_session_id = installed_id(installed->id_map, row.image_session_id),
                              .host_version_unverified = row.host_version_unverified,
                              .activation_suppressed = verify_hits,
                              .live_at_pack = false};
      const auto source = std::ranges::find_if(manifest.agent_sessions, [&](const auto& entry) {
        return entry.agent == agent.agent && entry.original_session_ids.primary == row.image_session_id;
      });
      if (source != manifest.agent_sessions.end()) {
        report.live_at_pack = source->live_at_pack;
      }
      if (verify_hits) {
        report.reason = "verify-hits";
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::installed) {
        report.row = SessionRowReport::Row::installed;
        report.reason.reset();
        any_clean = true;
      } else if (row.outcome == adapters::InstallSessionOutcome::Outcome::staged) {
        report.row = SessionRowReport::Row::failed;
        report.reason = "error";
      }
      outcome.rows.push_back(std::move(report));
    }
    outcome.id_map.insert(outcome.id_map.end(), installed->id_map.begin(), installed->id_map.end());
    if (any_clean) {
      outcome.activation.insert(outcome.activation.end(), installed->activation.begin(), installed->activation.end());
    }
    for (const auto& note : agent.adapter->state_inventory().caveat_facts.notes) {
      outcome.caveats.push_back(note);
    }
  }
  return outcome;
}

}  // namespace biv::core_sessions
