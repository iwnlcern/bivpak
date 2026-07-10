#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <span>
#include <vector>

#include "core/support/error.hpp"

namespace biv::adapters::secure_io {

using ByteSink =
    std::function<expected<void>(std::span<const std::byte>)>;

class ReadHandle {
 public:
  ReadHandle() = default;

  [[nodiscard]] std::uint64_t size() const noexcept;
  expected<void> stream(const ByteSink& sink) const;

 private:
  struct State;
  explicit ReadHandle(std::shared_ptr<State> state);

  std::shared_ptr<State> state_;

  friend expected<ReadHandle> open_read_no_follow(
      const std::filesystem::path& path);
};

struct WriteRequest {
  std::filesystem::path relative_path;
  std::span<const std::byte> bytes;
};

expected<void> validate_directory_no_follow(
    const std::filesystem::path& path);
expected<ReadHandle> open_read_no_follow(
    const std::filesystem::path& path);
expected<void> write_batch_no_replace(
    const std::filesystem::path& root,
    std::span<const WriteRequest> requests);

}  // namespace biv::adapters::secure_io
