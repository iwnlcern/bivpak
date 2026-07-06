#include "core/container/tar_reader.hpp"

#include <algorithm>
#include <charconv>
#include <cctype>
#include <cstdint>
#include <iterator>
#include <limits>
#include <map>
#include <string_view>

#include "core/support/sha256.hpp"

namespace biv::container {

namespace {

constexpr size_t kBlockSize = 512;
constexpr size_t kPaxByteCap = 1U << 20;
constexpr size_t kMemberCountCap = 1'000'000U;

struct Header {
  std::string name;
  std::string linkname;
  char typeflag{'0'};
  uint64_t size{0};
  uint32_t mode{0};
  int64_t mtime_s{0};
};

struct Pax {
  std::map<std::string, std::string> values;
};

struct ParseDetail {
  std::string_view value;
};

bool is_zero_block(std::span<const std::byte> block) {
  return std::ranges::all_of(block, [](std::byte byte) { return byte == std::byte{0}; });
}

std::string text_field(std::span<const std::byte> field) {
  std::string out;
  for (const auto byte : field) {
    const char ch = static_cast<char>(byte);
    if (ch == '\0') {
      break;
    }
    out.push_back(ch);
  }
  return out;
}

expected<uint64_t> octal_field(std::span<const std::byte> field, std::string_view detail) {
  if (!field.empty() && (std::to_integer<unsigned char>(field.front()) & 0x80U) != 0U) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail} + "-base256"});
  }

  size_t begin = 0;
  while (begin < field.size()) {
    const char ch = static_cast<char>(*std::next(field.begin(), static_cast<std::ptrdiff_t>(begin)));
    if (ch != ' ' && ch != '\0') {
      break;
    }
    ++begin;
  }
  size_t end = field.size();
  while (end > begin) {
    const char ch = static_cast<char>(*std::next(field.begin(), static_cast<std::ptrdiff_t>(end - 1U)));
    if (ch != ' ' && ch != '\0') {
      break;
    }
    --end;
  }

  uint64_t value = 0;
  for (size_t i = begin; i < end; ++i) {
    const char ch = static_cast<char>(*std::next(field.begin(), static_cast<std::ptrdiff_t>(i)));
    if (ch < '0' || ch > '7') {
      return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail} + "-octal"});
    }
    value = (value << 3U) + static_cast<uint64_t>(ch - '0');
  }
  return value;
}

expected<void> verify_checksum(std::span<const std::byte> block) {
  auto stored = octal_field(block.subspan(148, 8), "checksum");
  if (!stored) {
    return std::unexpected(stored.error());
  }
  uint64_t computed = 0;
  for (size_t i = 0; i < block.size(); ++i) {
    if (i >= 148U && i < 156U) {
      computed += static_cast<unsigned char>(' ');
    } else {
      computed += std::to_integer<unsigned char>(*std::next(block.begin(), static_cast<std::ptrdiff_t>(i)));
    }
  }
  if (*stored != computed) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "header-checksum"});
  }
  return {};
}

expected<Header> parse_header(std::span<const std::byte> block) {
  if (auto ok = verify_checksum(block); !ok) {
    return std::unexpected(ok.error());
  }
  auto mode = octal_field(block.subspan(100, 8), "mode");
  auto size = octal_field(block.subspan(124, 12), "size");
  auto mtime = octal_field(block.subspan(136, 12), "mtime");
  if (!mode || !size || !mtime) {
    return std::unexpected(!mode ? mode.error() : (!size ? size.error() : mtime.error()));
  }

  const std::string name = text_field(block.subspan(0, 100));
  const std::string prefix = text_field(block.subspan(345, 155));
  Header header;
  header.name = prefix.empty() ? name : prefix + "/" + name;
  header.linkname = text_field(block.subspan(157, 100));
  header.typeflag = static_cast<char>(*std::next(block.begin(), 156));
  if (header.typeflag == '\0') {
    header.typeflag = '0';
  }
  header.size = *size;
  header.mode = static_cast<uint32_t>(*mode & 07777U);
  header.mtime_s = static_cast<int64_t>(*mtime);
  return header;
}

size_t padded_size(size_t size) {
  const size_t remainder = size % kBlockSize;
  return remainder == 0U ? size : size + (kBlockSize - remainder);
}

expected<Pax> parse_pax(std::span<const std::byte> data) {
  if (data.size() > kPaxByteCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-size"});
  }
  Pax pax;
  size_t pos = 0;
  while (pos < data.size()) {
    size_t space = pos;
    while (space < data.size() &&
           static_cast<char>(*std::next(data.begin(), static_cast<std::ptrdiff_t>(space))) != ' ') {
      const char ch = static_cast<char>(*std::next(data.begin(), static_cast<std::ptrdiff_t>(space)));
      if (ch < '0' || ch > '9') {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-length"});
      }
      ++space;
    }
    if (space == data.size() || space == pos) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-length"});
    }
    size_t length = 0;
    const std::string length_text = text_field(data.subspan(pos, space - pos));
    const char* length_end = std::next(length_text.data(), static_cast<std::ptrdiff_t>(length_text.size()));
    const auto [ptr, ec] = std::from_chars(length_text.data(), length_end, length);
    if (ec != std::errc{} || ptr != length_end || length == 0U ||
        pos + length > data.size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-length"});
    }
    if (static_cast<char>(*std::next(data.begin(), static_cast<std::ptrdiff_t>(pos + length - 1U))) != '\n') {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-newline"});
    }

    const auto record = data.subspan(space + 1U, pos + length - space - 2U);
    const auto equals = std::ranges::find(record, static_cast<std::byte>('='));
    if (equals == record.end()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-key"});
    }
    const size_t key_len = static_cast<size_t>(equals - record.begin());
    std::string key = text_field(record.first(key_len));
    std::string value = text_field(record.subspan(key_len + 1U));
    pax.values[std::move(key)] = std::move(value);
    pos += length;
  }
  return pax;
}

bool path_is_safe(std::string_view path) {
  if (path.empty() || path.front() == '/' || path.find('\\') != std::string_view::npos) {
    return false;
  }
  if (path.size() >= 2U && std::isalpha(static_cast<unsigned char>(path.front())) != 0 && path.at(1) == ':') {
    return false;
  }

  size_t segment_start = 0;
  while (segment_start <= path.size()) {
    const size_t slash = path.find('/', segment_start);
    const auto segment = slash == std::string_view::npos
                             ? path.substr(segment_start)
                             : path.substr(segment_start, slash - segment_start);
    if (segment == "..") {
      return false;
    }
    for (const char ch : segment) {
      if (static_cast<unsigned char>(ch) < 0x20U) {
        return false;
      }
    }
    if (slash == std::string_view::npos) {
      break;
    }
    segment_start = slash + 1U;
  }
  return true;
}

expected<uint64_t> parse_u64(std::string_view text, ParseDetail detail) {
  const std::string value_text{text};
  uint64_t value = 0;
  const char* text_end = std::next(value_text.data(), static_cast<std::ptrdiff_t>(value_text.size()));
  const auto [ptr, ec] = std::from_chars(value_text.data(), text_end, value);
  if (ec != std::errc{} || ptr != text_end) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail.value}});
  }
  return value;
}

expected<void> apply_pax(const Pax& pax, MemberMeta& meta) {
  if (const auto path = pax.values.find("path"); path != pax.values.end()) {
    meta.path = path->second;
  }
  if (const auto link = pax.values.find("linkpath"); link != pax.values.end()) {
    meta.symlink_target = link->second;
  }
  if (const auto size = pax.values.find("size"); size != pax.values.end()) {
    auto parsed = parse_u64(size->second, ParseDetail{"pax-size"});
    if (!parsed) {
      return std::unexpected(parsed.error());
    }
    meta.size = *parsed;
  }
  if (const auto mtime = pax.values.find("mtime"); mtime != pax.values.end()) {
    const auto dot = mtime->second.find('.');
    const std::string_view seconds{mtime->second.data(), dot == std::string::npos ? mtime->second.size() : dot};
    auto parsed_seconds = parse_u64(seconds, ParseDetail{"pax-mtime"});
    if (!parsed_seconds) {
      return std::unexpected(parsed_seconds.error());
    }
    meta.mtime_s = static_cast<int64_t>(*parsed_seconds);
    if (dot != std::string::npos) {
      std::string ns = mtime->second.substr(dot + 1U);
      if (ns.size() > 9U) {
        ns.resize(9U);
      }
      while (ns.size() < 9U) {
        ns.push_back('0');
      }
      auto parsed_ns = parse_u64(ns, ParseDetail{"pax-mtime-ns"});
      if (!parsed_ns || *parsed_ns > 999'999'999U) {
        return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-mtime-ns"});
      }
      meta.mtime_ns = static_cast<uint32_t>(*parsed_ns);
    }
  }
  return {};
}

expected<scan::NodeKind> kind_from_typeflag(char typeflag) {
  switch (typeflag) {
    case '0':
    case '\0':
      return scan::NodeKind::file;
    case '5':
      return scan::NodeKind::dir;
    case '2':
      return scan::NodeKind::symlink;
    default:
      return std::unexpected(BivError{ErrKind::ParseError, {}, "unsupported-typeflag"});
  }
}

}  // namespace

TarReader::TarReader(ZstdDecompressSource& source) : source_{&source} {}

expected<void> TarReader::ensure_loaded() {
  if (loaded_) {
    return {};
  }
  auto bytes = source_->pull();
  if (!bytes) {
    return std::unexpected(bytes.error());
  }
  raw_.assign(bytes->begin(), bytes->end());
  loaded_ = true;
  return {};
}

expected<void> TarReader::finish_current() {
  if (!current_.active) {
    return {};
  }
  support::Sha256 sha;
  sha.update(std::span<const std::byte>{raw_}.subspan(current_.extent_start, current_.extent_end - current_.extent_start));
  extent_sha256_ = sha.finish_hex();
  current_ = Current{};
  return {};
}

expected<std::optional<RMember>> TarReader::next() {
  if (auto ok = ensure_loaded(); !ok) {
    return std::unexpected(ok.error());
  }
  if (auto ok = finish_current(); !ok) {
    return std::unexpected(ok.error());
  }

  if (member_count_ > kMemberCountCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "member-count"});
  }
  if (cursor_ + kBlockSize > raw_.size()) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eof"});
  }

  size_t extent_start = cursor_;
  auto block = std::span<const std::byte>{raw_}.subspan(cursor_, kBlockSize);
  if (is_zero_block(block)) {
    return std::optional<RMember>{};
  }

  auto header = parse_header(block);
  if (!header) {
    return std::unexpected(header.error());
  }
  cursor_ += kBlockSize;
  bool has_pax = false;
  Pax pax;

  if (header->typeflag == 'x') {
    has_pax = true;
    const size_t pax_size = static_cast<size_t>(header->size);
    const size_t pax_padded = padded_size(pax_size);
    if (pax_size > kPaxByteCap || cursor_ + pax_padded > raw_.size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-eof"});
    }
    auto parsed_pax = parse_pax(std::span<const std::byte>{raw_}.subspan(cursor_, pax_size));
    if (!parsed_pax) {
      return std::unexpected(parsed_pax.error());
    }
    pax = std::move(*parsed_pax);
    cursor_ += pax_padded;

    if (cursor_ + kBlockSize > raw_.size()) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "eof"});
    }
    block = std::span<const std::byte>{raw_}.subspan(cursor_, kBlockSize);
    if (is_zero_block(block)) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-without-member"});
    }
    header = parse_header(block);
    if (!header) {
      return std::unexpected(header.error());
    }
    cursor_ += kBlockSize;
  }

  auto kind = kind_from_typeflag(header->typeflag);
  if (!kind) {
    return std::unexpected(kind.error());
  }

  MemberMeta meta;
  meta.path = header->name;
  meta.kind = *kind;
  meta.mode = header->mode;
  meta.mtime_s = header->mtime_s;
  meta.mtime_ns = 0;
  meta.size = meta.kind == scan::NodeKind::file ? header->size : 0U;
  meta.symlink_target = header->linkname;
  if (auto ok = apply_pax(pax, meta); !ok) {
    return std::unexpected(ok.error());
  }
  if (meta.kind != scan::NodeKind::file) {
    meta.size = 0;
  }
  if (!path_is_safe(meta.path)) {
    return std::unexpected(BivError{ErrKind::MemberPathUnsafe, meta.path});
  }

  const size_t payload_size = static_cast<size_t>(meta.size);
  const size_t payload_padded = padded_size(payload_size);
  if (cursor_ + payload_padded > raw_.size()) {
    return std::unexpected(BivError{ErrKind::ParseError, meta.path, "payload-eof"});
  }
  current_ = Current{
      .data_start = cursor_,
      .size = payload_size,
      .read = 0,
      .extent_start = extent_start,
      .extent_end = cursor_ + payload_padded,
      .active = true,
  };
  cursor_ += payload_padded;
  ++member_count_;
  return RMember{.meta = std::move(meta), .has_pax = has_pax};
}

expected<size_t> TarReader::read_data(std::span<std::byte> out) {
  if (!current_.active || out.empty()) {
    if (auto ok = finish_current(); !ok) {
      return std::unexpected(ok.error());
    }
    return 0U;
  }
  const size_t remaining = current_.size - current_.read;
  if (remaining == 0U) {
    if (auto ok = finish_current(); !ok) {
      return std::unexpected(ok.error());
    }
    return 0U;
  }
  const size_t n = std::min(out.size(), remaining);
  std::ranges::copy(std::span<const std::byte>{raw_}.subspan(current_.data_start + current_.read, n), out.begin());
  current_.read += n;
  if (current_.read == current_.size) {
    if (auto ok = finish_current(); !ok) {
      return std::unexpected(ok.error());
    }
  }
  return n;
}

const std::string& TarReader::extent_sha256_hex() const {
  return extent_sha256_;
}

}  // namespace biv::container
