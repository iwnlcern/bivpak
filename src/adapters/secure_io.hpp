#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

#include "core/support/error.hpp"

namespace biv::adapters::secure_io {

// Converts a POSIX errno value to its exact uppercase symbol.
//
// NAMESPACE (m-3, DESIGN-PLANNER-M3-ERRNO-NAMESPACE-RULED-READING-B-20260727-010403):
// every E* macro this build target defines -- 131 distinct values on the
// reference host. "Closed by reference" means the reference authority is the
// target's <errno.h>, not the POSIX specification list, because the criterion
// is REACHABILITY: what openat/linkat/fstat can place in errno is decided by
// the kernel and the mounted filesystem.
//
// PRESENCE: engaged iff err_no is a NONZERO MEMBER of that namespace. Absence
// covers BOTH err_no == 0 and the nonzero-out-of-namespace case truthfully.
// It NEVER returns an engaged empty string -- that is a third state no contract
// admits, and it is what a bare string_view return produced.
//
// Reaching the out-of-namespace arm means a non-errno integer was stored in
// BivError::err_no: a CAPTURE-SITE DEFECT, asserted in debug builds. Every
// err_no this converter sees originates from an errno capture in secure_io.
//
// err_no is preserved numerically elsewhere; the symbol is an added rendering,
// never a replacement. strerror() is rejected as localized prose.
[[nodiscard]] std::optional<std::string_view> errno_symbol(int err_no) noexcept;

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

namespace internal {

// Deterministic observation and classification seam for testing.
// NOT a supported product API. Nothing outside secure_io.cpp and the adapter
// install tests may depend on these declarations.

// The named AMBIENT constructor. Its BivError::detail is EXACTLY the empty
// string at every site -- never a reason word, never the errno symbol. The
// user-facing symbol is derived later from the preserved numeric err_no.
[[nodiscard]] BivError ambient_error(const std::filesystem::path& path,
                                     int err_no);

}  // namespace internal

}  // namespace biv::adapters::secure_io
