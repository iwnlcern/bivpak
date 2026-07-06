#pragma once

#include <cstdint>
#include <functional>
#include <span>
#include <string>

#include "core/scan/scan.hpp"
#include "core/support/error.hpp"
#include "core/support/sha256.hpp"

namespace biv::container {

struct MemberMeta {
  std::string path;
  scan::NodeKind kind{scan::NodeKind::file};
  uint32_t mode{0};
  int64_t mtime_s{0};
  uint32_t mtime_ns{0};
  uint64_t size{0};
  std::string symlink_target;
};

class TarWriter {
 public:
  using Sink = std::function<expected<void>(std::span<const std::byte>)>;

  explicit TarWriter(Sink sink);

  expected<void> begin_member(const MemberMeta& meta);
  expected<void> write_data(std::span<const std::byte> data);
  expected<std::string> end_member();
  expected<void> finish();

 private:
  expected<void> emit(std::span<const std::byte> bytes, bool hash_current);

  Sink sink_;
  support::Sha256 extent_hash_;
  MemberMeta current_;
  uint64_t data_written_{0};
  bool in_member_{false};
  bool finished_{false};
};

}  // namespace biv::container
