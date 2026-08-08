#pragma once

#include <filesystem>
#include <optional>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "adapters/adapter.hpp"
#include "core/manifest/manifest.hpp"
#include "core/open/consent.hpp"
#include "core/support/error.hpp"

namespace biv::core_sessions {

struct AgentPreview {
  std::string agent;
  size_t parent_count{0};
  size_t child_count{0};
  bool known_adapter{false};
  bool entry_schema_skipped{false};
  std::optional<adapters::Capabilities> caps;
  std::optional<adapters::Store> store;
  const adapters::AgentAdapter* adapter{nullptr};
};

struct SessionPreview {
  std::vector<AgentPreview> agents;
  bool any_sessions() const;
};

enum class ConsentSource { flag, prompt, deny_default };

struct ConsentDecision {
  ConsentSource source{ConsentSource::deny_default};
  std::vector<std::pair<std::string, bool>> per_agent;
};

struct SessionRowReport {
  std::string agent;
  std::string image_session_id;
  enum class Row {
    installed,
    skipped,
    failed,
    containment_refused,
    session_install_failed,
    unknown_agent_skipped,
    sessions_consent_skipped,
    sessions_staged, /* m-3 spelling at consumer review */
    agent_not_validated_failed,
  } row{Row::failed};
  std::optional<std::string> reason;
  std::optional<std::string> installed_session_id;
  bool host_version_unverified{false};
  bool activation_suppressed{false};
  bool live_at_pack{false};
  // Generic pass-through of the adapter row's detail. Copied VERBATIM at the
  // seam; emitted only when engaged. Appended last so existing designated
  // initializers stay valid.
  std::optional<std::string> detail;
};

struct AgentCaveat {
  std::string agent;
  std::string kind;
  std::string note;
};

struct SessionsOutcome {
  std::vector<SessionRowReport> rows;
  std::vector<adapters::Activation> activation;
  std::vector<adapters::IdMapEntry> id_map;
  std::vector<AgentCaveat> caveats;
};

std::optional<ErrKind> kind_for_row(SessionRowReport::Row row, std::string_view reason);
std::string install_failure_reason(const BivError& error);
std::vector<adapters::Activation> filter_activation(
    std::span<const adapters::Activation> activation,
    std::span<const SessionRowReport> rows);

expected<SessionPreview> build_preview(const manifest::Manifest& manifest, const adapters::Host& host);
expected<SessionPreview> build_preview(const manifest::Manifest& manifest, const adapters::Env& env);
ConsentDecision resolve_consent(const ConsentSpec& spec,
                                const SessionPreview& preview,
                                std::optional<bool> prompt_answer);
expected<SessionsOutcome> run_session_leg(const SessionPreview& preview,
                                          const ConsentDecision& consent,
                                          const manifest::Manifest& manifest,
                                          const std::filesystem::path& final_workspace_root,
                                          const adapters::MemberRead& member_read);

}  // namespace biv::core_sessions
