#pragma once

#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "core/manifest/manifest.hpp"
#include "core/scan/scan.hpp"
#include "core/support/error.hpp"
#include "core/support/url_divergence.hpp"

namespace biv::pack {

inline constexpr std::string_view kWarningSessionLiveAtPack =
    "SessionLiveAtPack";
inline constexpr std::string_view kWarningTornTailDropped =
    "TornTailDropped";
inline constexpr std::string_view kWarningUnsupportedFileTypeSkipped =
    "UnsupportedFileTypeSkipped";

struct Advisory {
  std::string kind;
  std::vector<scan::PruneEntry> entries;
  std::vector<std::string> paths;
};

struct Warning {
  std::string kind;
  std::string path{};
  std::optional<std::string> artifact{};
  std::optional<std::uint64_t> bytes{};
};

std::string warning_text(const Warning& warning);

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
  std::vector<biv::UrlDivergenceAcceptedEntry> url_divergence_accepted{};
};

expected<PackReport> pack(const std::filesystem::path& source_dir);

}  // namespace biv::pack
