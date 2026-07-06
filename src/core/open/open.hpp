#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

#include "core/support/error.hpp"

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
};

expected<OpenReport> open(const OpenOptions& options);

}  // namespace biv::open
