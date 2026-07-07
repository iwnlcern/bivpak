#pragma once

#include <cstddef>
#include <filesystem>
#include <functional>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "core/manifest/manifest.hpp"
#include "core/support/error.hpp"

namespace biv::adapters {

enum class DiscoveryTier { env, defaults, config, explicit_flag };

struct Env {
  std::function<std::optional<std::string>(std::string_view)> getenv;
  std::filesystem::path home;
};

struct Host {
  std::filesystem::path home;
  Env env;
};

struct StoreLocator {
  std::string kind;
  std::filesystem::path path;
};

struct Store {
  std::filesystem::path root;
  std::vector<StoreLocator> locators;
  DiscoveryTier tier{DiscoveryTier::defaults};
  bool archived{false};
};

struct ArtifactClass {
  std::string name;
  std::vector<std::string> globs;
};

struct CaveatFacts {
  std::optional<std::string> env_var;
  std::vector<std::string> relocated_contents;
  std::string login_flow_owner;
  std::vector<std::pair<std::string, std::string>> notes;
};

struct Inventory {
  std::vector<ArtifactClass> collect;
  std::vector<ArtifactClass> rewrite;
  std::vector<std::string> never_collect;
  std::vector<std::string> never_rewrite;
  CaveatFacts caveat_facts;
};

struct SessionRecord {
  std::string agent;
  std::string original_session_id;
  std::vector<std::string> child_ids;
  std::string original_path;
  std::string normalized_path_key;
  manifest::PathFlavor path_flavor{manifest::PathFlavor::posix};
  manifest::SessionProvenance provenance;
  std::vector<std::string> artifacts;
  std::vector<std::filesystem::path> artifact_sources;
  std::string agent_version_at_pack;
  bool live_at_pack{false};
};

struct CollectReport {
  std::vector<SessionRecord> sessions;
  std::vector<std::string> no_cwd_record;
  std::vector<std::string> warnings;
};

using MemberRead = std::function<expected<std::vector<std::byte>>(std::string_view archive_path)>;

struct InstallTarget {
  std::filesystem::path workspace_root;
  Store target_store;
  MemberRead member_read;
};

enum class Consent { yes, no };

struct InstallVerify {
  size_t origin_path_hits{0};
  size_t origin_id_hits{0};
  size_t artifacts_checked{0};
};

struct InstallSessionOutcome {
  std::string image_session_id;
  enum class Outcome { installed, staged, failed } outcome{Outcome::failed};
  std::optional<std::string> reason;
  std::optional<std::string> content_rewrite;
  bool host_version_unverified{false};
  InstallVerify verify;
  std::optional<std::string> detail;
};

struct IdMapEntry {
  std::string agent;
  std::string image_session_id;
  std::string installed_session_id;
  std::vector<std::pair<std::string, std::string>> children;
};

struct Activation {
  std::string agent;
  std::string command;
};

struct InstallResult {
  enum class Mode { host_installed, staged } mode{Mode::staged};
  std::vector<InstallSessionOutcome> sessions;
  std::vector<IdMapEntry> id_map;
  std::vector<Activation> activation;
};

struct RewriteReport {
  std::vector<std::pair<std::string, InstallVerify>> per_artifact_hits;
  size_t skipped_non_utf8{0};
  InstallVerify verify;
};

struct PerVerb {
  bool collect{false};
  bool install{false};
  bool rewrite{false};
};

struct Capabilities {
  std::string agent_version;
  std::string validated_range;
  enum class Verdict { validated, unvalidated_host, unvalidated, absent } verdict{Verdict::absent};
  bool long_path_keys_pinned{false};
  PerVerb per_verb;
};

class AgentAdapter {
 public:
  AgentAdapter() = default;
  virtual ~AgentAdapter() = default;
  AgentAdapter(const AgentAdapter&) = delete;
  AgentAdapter& operator=(const AgentAdapter&) = delete;
  AgentAdapter(AgentAdapter&&) = delete;
  AgentAdapter& operator=(AgentAdapter&&) = delete;

  virtual std::string_view id() const = 0;
  virtual expected<std::vector<Store>> discover(const Env& env) const = 0;
  virtual const Inventory& state_inventory() const = 0;
  virtual expected<CollectReport> collect(const std::filesystem::path& source_root,
                                          std::span<const Store> stores) const = 0;
  virtual expected<InstallResult> install(const InstallTarget& target,
                                          Consent consent,
                                          std::span<const manifest::AgentSessionEntry> records) const = 0;
  virtual expected<RewriteReport> rewrite(std::span<const SessionRecord> records,
                                          const InstallTarget& target) const = 0;
  virtual Capabilities capabilities(const Host& host) const = 0;
};

}  // namespace biv::adapters
