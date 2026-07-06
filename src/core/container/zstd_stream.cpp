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
  if (finished_) {
    return std::span<const std::byte>{};
  }
  if (context_ == nullptr) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "zstd-decompress-state"});
  }

  while (true) {
    if (input_pos_ >= input_.size()) {
      if (input_eof_) {
        if (saw_input_ && last_result_ != 0U) {
          return std::unexpected(BivError{ErrKind::ParseError, {}, "zstd-truncated"});
        }
        finished_ = true;
        return std::span<const std::byte>{};
      }

      auto input_chunk = pull_();
      if (!input_chunk) {
        return std::unexpected(input_chunk.error());
      }
      if (input_chunk->empty()) {
        input_eof_ = true;
        continue;
      }
      input_.assign(input_chunk->begin(), input_chunk->end());
      input_pos_ = 0;
      saw_input_ = true;
    }

    output_.assign(ZSTD_DStreamOutSize(), std::byte{0});
    ZSTD_inBuffer in{input_.data(), input_.size(), input_pos_};
    ZSTD_outBuffer out{output_.data(), output_.size(), 0};
    last_result_ = ZSTD_decompressStream(context_, &out, &in);
    input_pos_ = in.pos;
    if (auto err = zstd_error(last_result_, "zstd-decompress"); !err) {
      return std::unexpected(err.error());
    }
    if (out.pos > 0U) {
      output_.resize(out.pos);
      return std::span<const std::byte>{output_};
    }
    if (last_result_ == 0U && input_pos_ >= input_.size()) {
      finished_ = true;
      return std::span<const std::byte>{};
    }
  }
}

}  // namespace biv::container
