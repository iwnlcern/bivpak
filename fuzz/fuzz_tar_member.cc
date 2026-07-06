#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "core/container/tar_reader.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<std::byte> bytes(size);
  for (size_t i = 0; i < size; ++i) {
    bytes[i] = static_cast<std::byte>(data[i]);
  }

  bool served = false;
  biv::container::ZstdDecompressSource source{[&]() -> biv::expected<std::span<const std::byte>> {
    if (served) {
      return std::span<const std::byte>{};
    }
    served = true;
    return std::span<const std::byte>{bytes};
  }};
  biv::container::TarReader reader{source};
  std::array<std::byte, 4096> buffer {};
  for (size_t members = 0; members < 1024U; ++members) {
    auto next = reader.next();
    if (!next || !*next) {
      break;
    }
    while (true) {
      auto read = reader.read_data(buffer);
      if (!read || *read == 0U) {
        break;
      }
    }
  }
  return 0;
}
