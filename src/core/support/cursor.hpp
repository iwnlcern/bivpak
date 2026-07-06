#pragma once

#include <cstddef>
#include <span>

#include "core/support/error.hpp"

namespace biv {

class Cursor {
 public:
  explicit Cursor(std::span<const std::byte> bytes) noexcept : bytes_{bytes} {}

  [[nodiscard]] size_t remaining() const noexcept {
    return bytes_.size() - offset_;
  }

  [[nodiscard]] size_t pos() const noexcept {
    return offset_;
  }

  expected<std::span<const std::byte>> take(const size_t count) noexcept {
    if (count > remaining()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "eof"});
    }
    auto result = bytes_.subspan(offset_, count);
    offset_ += count;
    return result;
  }

  expected<void> skip(const size_t count) noexcept {
    if (count > remaining()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "eof"});
    }
    offset_ += count;
    return {};
  }

 private:
  std::span<const std::byte> bytes_;
  size_t offset_{0};
};

}
