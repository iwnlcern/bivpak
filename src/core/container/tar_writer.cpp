#include "core/container/tar_writer.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <cstddef>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string_view>
#include <vector>

namespace biv::container {

namespace {

constexpr size_t kBlockSize = 512;
constexpr uint64_t kMaxOctalSize = 077777777777ULL;

struct OctalWidth {
  size_t value;
};

struct HeaderSpec {
  std::string path;
  char typeflag;
  uint32_t mode;
  uint64_t size;
  int64_t mtime_s;
  std::string_view link_target;
};

std::span<const std::byte> as_bytes(const std::string& text) {
  return std::as_bytes(std::span<const char>{text.data(), text.size()});
}

std::span<const std::byte> as_bytes(const std::vector<char>& data) {
  return std::as_bytes(std::span<const char>{data.data(), data.size()});
}

std::string octal(uint64_t value, OctalWidth width) {
  std::string out(width.value, '0');
  for (size_t i = 0; i < width.value; ++i) {
    const size_t pos = width.value - 1U - i;
    out.at(pos) = static_cast<char>('0' + (value & 07U));
    value >>= 3U;
  }
  return out;
}

void write_octal(std::span<std::byte> field, uint64_t value) {
  const std::string digits = octal(value, OctalWidth{field.size() - 1U});
  for (size_t i = 0; i < digits.size(); ++i) {
    *std::next(field.begin(), static_cast<std::ptrdiff_t>(i)) = static_cast<std::byte>(digits.at(i));
  }
  *std::next(field.begin(), static_cast<std::ptrdiff_t>(field.size() - 1U)) = std::byte{0};
}

void write_checksum(std::span<std::byte> field, uint64_t value) {
  const std::string digits = octal(value, OctalWidth{6});
  for (size_t i = 0; i < digits.size(); ++i) {
    *std::next(field.begin(), static_cast<std::ptrdiff_t>(i)) = static_cast<std::byte>(digits.at(i));
  }
  *std::next(field.begin(), 6) = std::byte{0};
  *std::next(field.begin(), 7) = static_cast<std::byte>(' ');
}

void write_text(std::span<std::byte> field, std::string_view value) {
  const size_t n = std::min(field.size(), value.size());
  for (size_t i = 0; i < n; ++i) {
    *std::next(field.begin(), static_cast<std::ptrdiff_t>(i)) = static_cast<std::byte>(value.at(i));
  }
}

char typeflag(scan::NodeKind kind) {
  switch (kind) {
    case scan::NodeKind::file:
      return '0';
    case scan::NodeKind::dir:
      return '5';
    case scan::NodeKind::symlink:
      return '2';
  }
  return '0';
}

std::string pax_member_name(std::string_view path) {
  std::string name = "PaxHeaders/";
  name.append(path);
  if (name.size() > 100U) {
    name.resize(100U);
  }
  return name;
}

std::string pax_mtime(int64_t seconds, uint32_t nanoseconds) {
  std::ostringstream out;
  out << seconds << '.' << std::setw(9) << std::setfill('0') << nanoseconds;
  return out.str();
}

std::string pax_record(std::string_view key, std::string_view value) {
  const std::string body = std::string{key} + "=" + std::string{value} + "\n";
  size_t length = body.size() + 2U;
  while (true) {
    const std::string prefix = std::to_string(length);
    const size_t next = prefix.size() + 1U + body.size();
    if (next == length) {
      return prefix + " " + body;
    }
    length = next;
  }
}

std::string pax_data(const MemberMeta& meta) {
  std::string data;
  data += pax_record("path", meta.path);
  data += pax_record("mtime", pax_mtime(meta.mtime_s, meta.mtime_ns));
  if (meta.kind == scan::NodeKind::symlink) {
    data += pax_record("linkpath", meta.symlink_target);
  }
  if (meta.size > kMaxOctalSize || meta.kind == scan::NodeKind::file) {
    data += pax_record("size", std::to_string(meta.size));
  }
  return data;
}

std::array<std::byte, kBlockSize> header_block(const HeaderSpec& spec) {
  std::array<std::byte, kBlockSize> block {};
  write_text(std::span<std::byte>{block}.subspan(0, 100), spec.path.substr(0, 100));
  write_octal(std::span<std::byte>{block}.subspan(100, 8), spec.mode & 07777U);
  write_octal(std::span<std::byte>{block}.subspan(108, 8), 0);
  write_octal(std::span<std::byte>{block}.subspan(116, 8), 0);
  write_octal(std::span<std::byte>{block}.subspan(124, 12), spec.size <= kMaxOctalSize ? spec.size : 0U);
  write_octal(std::span<std::byte>{block}.subspan(136, 12),
              spec.mtime_s < 0 ? 0U : static_cast<uint64_t>(spec.mtime_s));
  std::ranges::fill(std::span<std::byte>{block}.subspan(148, 8), static_cast<std::byte>(' '));
  block.at(156) = static_cast<std::byte>(spec.typeflag);
  write_text(std::span<std::byte>{block}.subspan(157, 100), spec.link_target.substr(0, 100));
  write_text(std::span<std::byte>{block}.subspan(257, 6), "ustar");
  write_text(std::span<std::byte>{block}.subspan(263, 2), "00");
  write_text(std::span<std::byte>{block}.subspan(265, 32), "root");
  write_text(std::span<std::byte>{block}.subspan(297, 32), "root");
  write_octal(std::span<std::byte>{block}.subspan(329, 8), 0);
  write_octal(std::span<std::byte>{block}.subspan(337, 8), 0);

  uint64_t checksum = 0;
  for (const auto byte : block) {
    checksum += std::to_integer<unsigned char>(byte);
  }
  write_checksum(std::span<std::byte>{block}.subspan(148, 8), checksum);
  return block;
}

std::vector<char> zero_padding(size_t size) {
  const size_t remainder = size % kBlockSize;
  if (remainder == 0U) {
    return {};
  }
  return std::vector<char>(kBlockSize - remainder, '\0');
}

}  // namespace

TarWriter::TarWriter(Sink sink) : sink_{std::move(sink)} {}

expected<void> TarWriter::emit(const std::span<const std::byte> bytes, const bool hash_current) {
  if (hash_current) {
    extent_hash_.update(bytes);
  }
  auto written = sink_(bytes);
  if (!written) {
    return std::unexpected(written.error());
  }
  return {};
}

expected<void> TarWriter::begin_member(const MemberMeta& meta) {
  if (finished_ || in_member_) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, meta.path, "tar-writer-state"});
  }

  current_ = meta;
  current_.size = current_.kind == scan::NodeKind::file ? current_.size : 0U;
  data_written_ = 0;
  extent_hash_ = support::Sha256{};
  in_member_ = true;

  const std::string pax = pax_data(current_);
  const auto pax_header = header_block(HeaderSpec{.path = pax_member_name(current_.path),
                                                 .typeflag = 'x',
                                                 .mode = 0644,
                                                 .size = pax.size(),
                                                 .mtime_s = current_.mtime_s,
                                                 .link_target = {}});
  if (auto out = emit(std::span<const std::byte, kBlockSize>{pax_header}, true); !out) {
    return out;
  }
  if (auto out = emit(as_bytes(pax), true); !out) {
    return out;
  }
  const auto pax_pad = zero_padding(pax.size());
  if (!pax_pad.empty()) {
    if (auto out = emit(as_bytes(pax_pad), true); !out) {
      return out;
    }
  }

  const auto member_header = header_block(HeaderSpec{.path = current_.path,
                                                    .typeflag = typeflag(current_.kind),
                                                    .mode = current_.mode,
                                                    .size = current_.size,
                                                    .mtime_s = current_.mtime_s,
                                                    .link_target = current_.symlink_target});
  if (auto out = emit(std::span<const std::byte, kBlockSize>{member_header}, true); !out) {
    return out;
  }
  return {};
}

expected<void> TarWriter::write_data(const std::span<const std::byte> data) {
  if (!in_member_ || current_.kind != scan::NodeKind::file || data_written_ + data.size() > current_.size) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, current_.path, "tar-member-size"});
  }
  data_written_ += data.size();
  return emit(data, true);
}

expected<std::string> TarWriter::end_member() {
  if (!in_member_) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, "tar-writer-state"});
  }
  if (current_.kind == scan::NodeKind::file && data_written_ != current_.size) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, current_.path, "tar-member-size"});
  }

  const auto payload_pad = zero_padding(static_cast<size_t>(data_written_));
  if (!payload_pad.empty()) {
    if (auto out = emit(as_bytes(payload_pad), true); !out) {
      return std::unexpected(out.error());
    }
  }

  in_member_ = false;
  return extent_hash_.finish_hex();
}

expected<void> TarWriter::finish() {
  if (in_member_) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, current_.path, "tar-writer-state"});
  }
  if (finished_) {
    return {};
  }
  std::array<std::byte, kBlockSize * 2U> zeros {};
  if (auto out = emit(std::span<const std::byte>{zeros}, false); !out) {
    return out;
  }
  finished_ = true;
  return {};
}

}  // namespace biv::container
