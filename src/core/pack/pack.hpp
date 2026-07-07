#pragma once

#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

#include "core/manifest/manifest.hpp"
#include "core/scan/scan.hpp"
#include "core/support/error.hpp"

namespace biv::pack {

struct Advisory {
  std::string kind;
  std::vector<scan::PruneEntry> entries;
  std::vector<std::string> paths;
};

struct Warning {
  std::string kind;
  std::string path;
};

struct AgentSessionsSummary {
  std::string agent;
  size_t session_count{0};
};

struct PackReport {
  std::string image_path;
  std::string source_path;
  manifest::PathFlavor flavor{manifest::PathFlavor::posix};
  std::string image_id;
  uint64_t member_count{0};
  uint64_t payload_bytes{0};
  std::vector<AgentSessionsSummary> agent_sessions_summary;
  std::vector<manifest::AgentSessionEntry> agent_sessions;
  std::vector<Warning> warnings;
  std::vector<Advisory> advisories;
};

expected<PackReport> pack(const std::filesystem::path& source_dir);

}  // namespace biv::pack
