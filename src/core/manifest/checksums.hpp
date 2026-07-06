#pragma once

#include <cstddef>
#include <map>
#include <span>
#include <string>

#include "core/support/error.hpp"

namespace biv::manifest {

inline constexpr size_t kChecksumsByteCap = 64U << 20;

struct Checksums {
  std::map<std::string, std::string> entries;
};

std::string serialize(const Checksums& checksums);
expected<Checksums> parse_checksums(std::span<const std::byte> bytes);
bool is_sha256_hex(std::string_view value);

}
