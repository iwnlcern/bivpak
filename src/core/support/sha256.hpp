#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

namespace biv::support {

class Sha256 {
 public:
  Sha256();

  void update(std::span<const std::byte> data);
  std::string finish_hex();

 private:
  void transform(std::span<const std::byte, 64> block);

  std::array<uint32_t, 8> state_{};
  std::array<std::byte, 64> buffer_{};
  uint64_t bit_count_{0};
  size_t buffer_size_{0};
  bool finished_{false};
  std::string finished_hex_;
};

}  // namespace biv::support
