#include "adapters/claude_code/claude_code.hpp"

namespace biv::adapters {

namespace {

const Inventory& claude_inventory() {
  static const Inventory inventory{
      .collect = {ArtifactClass{.name = "project-transcripts", .globs = {"projects/*/*.jsonl"}}},
      .rewrite = {ArtifactClass{.name = "jsonl-session-fields", .globs = {"agents/claude-code/**/*.jsonl"}}},
      .never_collect = {".credentials.json",
                        "settings.json",
                        "settings.local.json",
                        "history.jsonl",
                        "shell-snapshots",
                        "memory",
                        "file-history",
                        "tasks",
                        "session-env"},
      .never_rewrite = {".meta.json"},
      .caveat_facts = {.env_var = "CLAUDE_CONFIG_DIR",
                       .relocated_contents = {"projects"},
                       .login_flow_owner = "claude-code",
                       .notes = {}}};
  return inventory;
}

class ClaudeCodeAdapter final : public AgentAdapter {
 public:
  std::string_view id() const override { return "claude-code"; }

  expected<std::vector<Store>> discover(const Env& /*env*/) const override { return std::vector<Store>{}; }

  const Inventory& state_inventory() const override { return claude_inventory(); }

  expected<CollectReport> collect(const std::filesystem::path& /*source_root*/,
                                  std::span<const Store> /*stores*/) const override {
    return CollectReport{};
  }

  expected<InstallResult> install(const InstallTarget& /*target*/,
                                  Consent /*consent*/,
                                  std::span<const manifest::AgentSessionEntry> /*records*/) const override {
    return InstallResult{};
  }

  expected<RewriteReport> rewrite(std::span<const SessionRecord> /*records*/,
                                  const InstallTarget& /*target*/) const override {
    return RewriteReport{};
  }

  Capabilities capabilities(const Host& /*host*/) const override {
    return Capabilities{.agent_version = "unknown",
                        .validated_range = "2.1.x",
                        .verdict = Capabilities::Verdict::unvalidated_host,
                        .long_path_keys_pinned = false,
                        .per_verb = {.collect = false, .install = false, .rewrite = false}};
  }
};

}  // namespace

const AgentAdapter& claude_code_adapter() {
  static const ClaudeCodeAdapter adapter;
  return adapter;
}

}  // namespace biv::adapters
