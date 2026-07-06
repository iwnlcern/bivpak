#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <memory>
#include <span>
#include <vector>

#include <zstd.h>

#include "core/container/tar_writer.hpp"

namespace biv::container {

inline constexpr std::array<unsigned char, 4> kZstdMagic{0x28, 0xB5, 0x2F, 0xFD};

class ZstdCompressSink {
 public:
  explicit ZstdCompressSink(TarWriter::Sink raw_out);
  ~ZstdCompressSink();

  ZstdCompressSink(const ZstdCompressSink&) = delete;
  ZstdCompressSink& operator=(const ZstdCompressSink&) = delete;
  ZstdCompressSink(ZstdCompressSink&&) = delete;
  ZstdCompressSink& operator=(ZstdCompressSink&&) = delete;

  TarWriter::Sink as_sink();
  expected<void> finish();

 private:
  expected<void> pump(std::span<const std::byte> input, ZSTD_EndDirective directive);

  TarWriter::Sink raw_out_;
  ZSTD_CCtx* context_{nullptr};
  bool finished_{false};
};

class ZstdDecompressSource {
 public:
  explicit ZstdDecompressSource(std::function<expected<std::span<const std::byte>>()> pull);
  ~ZstdDecompressSource();

  ZstdDecompressSource(const ZstdDecompressSource&) = delete;
  ZstdDecompressSource& operator=(const ZstdDecompressSource&) = delete;
  ZstdDecompressSource(ZstdDecompressSource&&) = delete;
  ZstdDecompressSource& operator=(ZstdDecompressSource&&) = delete;

  expected<std::span<const std::byte>> pull();

 private:
  std::function<expected<std::span<const std::byte>>()> pull_;
  ZSTD_DCtx* context_{nullptr};
  std::vector<std::byte> input_;
  std::vector<std::byte> output_;
  size_t input_pos_{0};
  size_t last_result_{0};
  bool saw_input_{false};
  bool input_eof_{false};
  bool finished_{false};
};

}  // namespace biv::container
