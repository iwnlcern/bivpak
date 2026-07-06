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

enum class PathFlavor { posix, windows, wsl };

struct BivignoreProvenance {
  std::string source;
  std::optional<std::string> builtin_id;
  std::string sha256_hex;
};

struct Manifest {
  int format_version{kFormatVersion};
  std::vector<std::string> required_capabilities{};
  std::string image_id;
  std::string app_version;
  std::string created_at;
  std::string source_path;
  PathFlavor source_path_flavor{PathFlavor::posix};
  BivignoreProvenance bivignore;
};

std::string to_string(PathFlavor flavor);
expected<PathFlavor> parse_path_flavor(std::string_view value);
std::string serialize(const Manifest& manifest);
expected<Manifest> parse(std::span<const std::byte> bytes);

}
