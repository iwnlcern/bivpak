#include <cstddef>
#include <cstdint>
#include <vector>

#include "core/manifest/manifest.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<std::byte> bytes(size);
  for (size_t i = 0; i < size; ++i) {
    bytes[i] = static_cast<std::byte>(data[i]);
  }
  static_cast<void>(biv::manifest::parse(bytes));
  return 0;
}
