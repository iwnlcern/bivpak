#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "core/support/error.hpp"

namespace biv::manifest {

inline constexpr int kFormatVersion = 1;
inline constexpr size_t kManifestByteCap = 16U << 20;
inline constexpr int kEntrySchemaParseCeiling = 2;

enum class PathFlavor { posix, windows, wsl };

struct BivignoreProvenance {
  std::string source;
  std::optional<std::string> builtin_id;
  std::string sha256_hex;
};

struct PackerHome {
  std::string path;
  PathFlavor flavor{PathFlavor::posix};
  friend bool operator==(const PackerHome&, const PackerHome&) = default;
};

struct SessionProvenance {
  std::string store_root;
  std::string locator;
  std::string discovery_tier;
  bool archived{false};
};

struct SessionIds {
  std::string primary;
  std::optional<std::string> parent;
  std::optional<bool> parent_in_image;
};

struct SessionChild {
  std::string original_id;
  std::vector<std::string> artifacts;
  std::optional<std::string> parent_id = std::nullopt;
};

struct AgentSessionEntry {
  std::string agent;
  std::string agent_version_at_pack;
  std::string relpath_key;
  std::string original_path;
  std::string normalized_path_key;
  std::string normalization_scheme;
  PathFlavor path_flavor{PathFlavor::posix};
  SessionProvenance provenance;
  SessionIds original_session_ids;
  std::vector<SessionChild> children;
  std::vector<std::string> artifacts;
  std::vector<std::string> stub_member_footprint{};
  bool live_at_pack{false};
  std::string imported_at;
  int entry_schema{1};
};

struct Manifest {
  int format_version{kFormatVersion};
  std::vector<std::string> required_capabilities{};
  std::string image_id;
  std::string app_version;
  std::string created_at;
  std::string source_path;
  PathFlavor source_path_flavor{PathFlavor::posix};
  std::optional<PackerHome> packer_home{std::nullopt};
  std::vector<AgentSessionEntry> agent_sessions;
  BivignoreProvenance bivignore;
};

std::string to_string(PathFlavor flavor);
expected<PathFlavor> parse_path_flavor(std::string_view value);
std::optional<PathFlavor> classify_absolute(std::string_view path);
bool packer_home_valid(const PackerHome& value);
std::optional<PackerHome> make_packer_home(std::string_view path);
std::string serialize(const Manifest& manifest);
expected<Manifest> parse(std::span<const std::byte> bytes);

}
