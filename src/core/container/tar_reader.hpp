#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "core/container/tar_writer.hpp"
#include "core/container/zstd_stream.hpp"
#include "core/support/error.hpp"
#include "core/support/sha256.hpp"

namespace biv::container {

struct RMember {
  MemberMeta meta;
  bool has_pax{false};
};

class TarReader {
 public:
  using Source = std::function<expected<std::span<const std::byte>>()>;

  explicit TarReader(ZstdDecompressSource& source);
  explicit TarReader(Source source);

  expected<std::optional<RMember>> next();
  expected<size_t> read_data(std::span<std::byte> out);
  const std::string& extent_sha256_hex() const;

 private:
  struct Current {
    uint64_t size{0};
    uint64_t read{0};
    size_t padding{0};
    bool active{false};
  };

  expected<void> fill_buffer(size_t count);
  expected<std::vector<std::byte>> consume(size_t count, bool hash_current);
  expected<void> consume_into(std::span<std::byte> out, bool hash_current);
  expected<void> skip(size_t count, bool hash_current);
  expected<void> finish_current();

  Source source_;
  std::vector<std::byte> buffer_;
  uint64_t total_consumed_{0};
  size_t member_count_{0};
  Current current_;
  support::Sha256 extent_hash_;
  std::string extent_sha256_;
};

}  // namespace biv::container
