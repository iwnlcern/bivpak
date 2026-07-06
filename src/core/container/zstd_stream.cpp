#include "core/container/zstd_stream.hpp"

#include <algorithm>
#include <iterator>

namespace biv::container {

namespace {

expected<void> zstd_error(size_t code, std::string_view context) {
  if (!ZSTD_isError(code)) {
    return {};
  }
  return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{context} + ": " + ZSTD_getErrorName(code)});
}

}  // namespace

ZstdCompressSink::ZstdCompressSink(TarWriter::Sink raw_out)
    : raw_out_{std::move(raw_out)}, context_{ZSTD_createCCtx()} {
  if (context_ != nullptr) {
    static_cast<void>(ZSTD_CCtx_setParameter(context_, ZSTD_c_compressionLevel, 3));
    static_cast<void>(ZSTD_CCtx_setParameter(context_, ZSTD_c_checksumFlag, 1));
  }
}

ZstdCompressSink::~ZstdCompressSink() {
  ZSTD_freeCCtx(context_);
}

TarWriter::Sink ZstdCompressSink::as_sink() {
  return [this](std::span<const std::byte> bytes) -> expected<void> {
    return pump(bytes, ZSTD_e_continue);
  };
}

expected<void> ZstdCompressSink::finish() {
  if (finished_) {
    return {};
  }
  auto done = pump({}, ZSTD_e_end);
  if (!done) {
    return done;
  }
  finished_ = true;
  return {};
}

expected<void> ZstdCompressSink::pump(const std::span<const std::byte> input, const ZSTD_EndDirective directive) {
  if (context_ == nullptr || finished_) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, "zstd-compress-state"});
  }

  ZSTD_inBuffer in{input.data(), input.size(), 0};
  std::vector<std::byte> out(ZSTD_CStreamOutSize());
  size_t remaining = 0;
  bool should_pump = true;
  while (should_pump) {
    ZSTD_outBuffer output{out.data(), out.size(), 0};
    remaining = ZSTD_compressStream2(context_, &output, &in, directive);
    if (auto err = zstd_error(remaining, "zstd-compress"); !err) {
      return std::unexpected(err.error());
    }
    if (output.pos > 0U) {
      auto written = raw_out_(std::span<const std::byte>{out.data(), output.pos});
      if (!written) {
        return written;
      }
    }
    should_pump = in.pos < in.size || (directive == ZSTD_e_end && remaining != 0U);
  }
  return {};
}

ZstdDecompressSource::ZstdDecompressSource(std::function<expected<std::span<const std::byte>>()> pull)
    : pull_{std::move(pull)}, context_{ZSTD_createDCtx()} {}

ZstdDecompressSource::~ZstdDecompressSource() {
  ZSTD_freeDCtx(context_);
}

expected<std::span<const std::byte>> ZstdDecompressSource::pull() {
  if (delivered_) {
    return std::span<const std::byte>{};
  }
  if (loaded_) {
    delivered_ = true;
    return std::span<const std::byte>{decompressed_};
  }
  if (context_ == nullptr) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "zstd-decompress-state"});
  }

  std::vector<std::byte> out(ZSTD_DStreamOutSize());
  size_t last = 0;
  bool saw_input = false;
  while (true) {
    auto input_chunk = pull_();
    if (!input_chunk) {
      return std::unexpected(input_chunk.error());
    }
    if (input_chunk->empty()) {
      break;
    }
    saw_input = true;
    ZSTD_inBuffer in{input_chunk->data(), input_chunk->size(), 0};
    while (in.pos < in.size) {
      ZSTD_outBuffer output{out.data(), out.size(), 0};
      last = ZSTD_decompressStream(context_, &output, &in);
      if (auto err = zstd_error(last, "zstd-decompress"); !err) {
        return std::unexpected(err.error());
      }
      decompressed_.insert(decompressed_.end(), out.begin(), std::next(out.begin(), static_cast<std::ptrdiff_t>(output.pos)));
    }
  }

  if (saw_input && last != 0U) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "zstd-truncated"});
  }
  loaded_ = true;
  delivered_ = true;
  return std::span<const std::byte>{decompressed_};
}

}  // namespace biv::container
