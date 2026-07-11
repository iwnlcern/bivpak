#pragma once

#include <filesystem>
#include <optional>
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
  enum class Row { installed, skipped, failed } row{Row::failed};
  std::optional<std::string> reason;
  std::optional<std::string> installed_session_id;
  bool host_version_unverified{false};
  bool activation_suppressed{false};
};

struct SessionsOutcome {
  std::vector<SessionRowReport> rows;
  std::vector<adapters::Activation> activation;
  std::vector<adapters::IdMapEntry> id_map;
  std::vector<std::pair<std::string, std::string>> caveats;
  bool warning_shown{false};
};

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
