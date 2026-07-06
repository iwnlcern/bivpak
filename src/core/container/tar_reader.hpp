#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/support/error.hpp"

namespace biv::container {

struct RMember {
  MemberMeta meta;
  bool has_pax{false};
};

class TarReader {
 public:
  explicit TarReader(ZstdDecompressSource& source);

  expected<std::optional<RMember>> next();
  expected<size_t> read_data(std::span<std::byte> out);
  const std::string& extent_sha256_hex() const;

 private:
  struct Current {
    size_t data_start{0};
    size_t size{0};
    size_t read{0};
    size_t extent_start{0};
    size_t extent_end{0};
    bool active{false};
  };

  expected<void> ensure_loaded();
  expected<void> finish_current();

  ZstdDecompressSource* source_;
  std::vector<std::byte> raw_;
  size_t cursor_{0};
  size_t member_count_{0};
  Current current_;
  std::string extent_sha256_;
  bool loaded_{false};
};

}  // namespace biv::container
