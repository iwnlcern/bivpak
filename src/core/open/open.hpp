#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "adapters/adapter.hpp"
#include "core/manifest/manifest.hpp"
#include "core/support/error.hpp"
#include "core/support/url_divergence.hpp"

namespace biv::open {

enum class Collision { refuse, rename, abort_preset };

struct OpenOptions {
  std::filesystem::path image;
  std::optional<std::filesystem::path> dest;
  Collision collision{Collision::refuse};
  bool verify{false};
};

struct OpenReport {
  std::string image_path;
  std::string output_dir;
  std::string collision_action;
  uint64_t restored_member_count{0};
  bool checksums_verified{false};
  int manifest_format_version{0};
  std::vector<biv::UrlDivergenceEntryRefusal> url_divergence_refusals{};
  std::vector<biv::UrlDivergenceAcceptedEntry> url_divergence_accepted{};
};

struct PlannedAgentMember {
  std::string name;
  uint64_t size{0};
  std::array<std::byte, 32> sha256{};
};

struct AgentMemberTable {
  std::vector<PlannedAgentMember> members;
  const PlannedAgentMember* find(std::string_view name) const;
};

adapters::MemberRead make_member_read(std::filesystem::path image, AgentMemberTable table);

struct OpenDecisions {
  Collision collision{Collision::refuse};
};

class OpenPlanHandle {
 public:
  ~OpenPlanHandle();
  OpenPlanHandle(OpenPlanHandle&&) noexcept;
  OpenPlanHandle& operator=(OpenPlanHandle&&) noexcept;
  OpenPlanHandle(const OpenPlanHandle&) = delete;
  OpenPlanHandle& operator=(const OpenPlanHandle&) = delete;

  const manifest::Manifest& manifest() const;
  const std::filesystem::path& dest() const;
  const AgentMemberTable& agent_members() const;
  adapters::MemberRead make_reader() const;

 private:
  struct Impl;
  explicit OpenPlanHandle(std::unique_ptr<Impl> impl);
  friend expected<OpenPlanHandle> plan_open(const OpenOptions&);
  friend expected<OpenReport> execute_open(OpenPlanHandle&&, const OpenDecisions&);
  std::unique_ptr<Impl> impl_;
};

expected<OpenPlanHandle> plan_open(const OpenOptions& options);
expected<OpenReport> execute_open(OpenPlanHandle&& plan, const OpenDecisions& decisions);

expected<OpenReport> open(const OpenOptions& options);

}  // namespace biv::open
