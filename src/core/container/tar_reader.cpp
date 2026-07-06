#include "core/container/tar_reader.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <cctype>
#include <cstdint>
#include <iterator>
#include <limits>
#include <map>
#include <string_view>

namespace biv::container {

namespace {

constexpr size_t kBlockSize = 512;
constexpr size_t kPaxByteCap = 1U << 20;
constexpr uint64_t kMemberPayloadByteCap = 2ULL << 30;
constexpr uint64_t kTotalDecompressedByteCap = 8ULL << 30;
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

expected<size_t> checked_size(uint64_t size, std::string_view detail) {
  if (size > static_cast<uint64_t>(std::numeric_limits<size_t>::max())) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail}});
  }
  return static_cast<size_t>(size);
}

expected<size_t> padded_size(uint64_t size, std::string_view detail) {
  auto concrete = checked_size(size, detail);
  if (!concrete) {
    return std::unexpected(concrete.error());
  }
  const size_t value = *concrete;
  const size_t remainder = value % kBlockSize;
  if (remainder == 0U) {
    return value;
  }
  const size_t pad = kBlockSize - remainder;
  if (value > std::numeric_limits<size_t>::max() - pad) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, std::string{detail}});
  }
  return value + pad;
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
    if (ec != std::errc{} || ptr != length_end || length == 0U || length > data.size() - pos) {
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

expected<int64_t> parse_i64(std::string_view text, ParseDetail detail) {
  const std::string value_text{text};
  int64_t value = 0;
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
    auto parsed_seconds = parse_i64(seconds, ParseDetail{"pax-mtime"});
    if (!parsed_seconds) {
      return std::unexpected(parsed_seconds.error());
    }
    meta.mtime_s = *parsed_seconds;
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

TarReader::TarReader(ZstdDecompressSource& source) : TarReader{[&source]() { return source.pull(); }} {}

TarReader::TarReader(Source source) : source_{std::move(source)} {}

expected<void> TarReader::fill_buffer(size_t count) {
  while (buffer_.size() < count) {
    auto chunk = source_();
    if (!chunk) {
      return std::unexpected(chunk.error());
    }
    if (chunk->empty()) {
      break;
    }
    buffer_.insert(buffer_.end(), chunk->begin(), chunk->end());
  }
  if (buffer_.size() < count) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "eof"});
  }
  return {};
}

expected<std::vector<std::byte>> TarReader::consume(size_t count, bool hash_current) {
  if (count > kTotalDecompressedByteCap - total_consumed_) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "decompressed-size"});
  }
  if (auto ok = fill_buffer(count); !ok) {
    return std::unexpected(ok.error());
  }
  std::vector<std::byte> out(buffer_.begin(), std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(count)));
  if (hash_current && count > 0U) {
    extent_hash_.update(std::span<const std::byte>{out});
  }
  buffer_.erase(buffer_.begin(), std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(count)));
  total_consumed_ += count;
  return out;
}

expected<void> TarReader::consume_into(std::span<std::byte> out, bool hash_current) {
  if (out.size() > kTotalDecompressedByteCap - total_consumed_) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "decompressed-size"});
  }
  if (auto ok = fill_buffer(out.size()); !ok) {
    return std::unexpected(ok.error());
  }
  std::ranges::copy(std::span<const std::byte>{buffer_}.first(out.size()), out.begin());
  if (hash_current && !out.empty()) {
    extent_hash_.update(std::span<const std::byte>{out.data(), out.size()});
  }
  buffer_.erase(buffer_.begin(), std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(out.size())));
  total_consumed_ += out.size();
  return {};
}

expected<void> TarReader::skip(size_t count, bool hash_current) {
  std::array<std::byte, 8192> scratch {};
  size_t remaining = count;
  while (remaining > 0U) {
    const size_t n = std::min(remaining, scratch.size());
    auto ok = consume_into(std::span<std::byte>{scratch}.first(n), hash_current);
    if (!ok) {
      return std::unexpected(ok.error());
    }
    remaining -= n;
  }
  return {};
}

expected<void> TarReader::finish_current() {
  if (!current_.active) {
    return {};
  }
  std::array<std::byte, 8192> scratch {};
  while (current_.read < current_.size) {
    const uint64_t remaining = current_.size - current_.read;
    const size_t n = static_cast<size_t>(std::min<uint64_t>(remaining, scratch.size()));
    if (auto ok = consume_into(std::span<std::byte>{scratch}.first(n), true); !ok) {
      return std::unexpected(ok.error());
    }
    current_.read += n;
  }
  if (auto ok = skip(current_.padding, true); !ok) {
    return std::unexpected(ok.error());
  }
  extent_sha256_ = extent_hash_.finish_hex();
  extent_hash_ = support::Sha256{};
  current_ = Current{};
  return {};
}

expected<std::optional<RMember>> TarReader::next() {
  if (auto ok = finish_current(); !ok) {
    return std::unexpected(ok.error());
  }

  if (member_count_ >= kMemberCountCap) {
    return std::unexpected(BivError{ErrKind::ParseError, {}, "member-count"});
  }

  auto first_block = consume(kBlockSize, false);
  if (!first_block) {
    return std::unexpected(first_block.error());
  }
  if (is_zero_block(*first_block)) {
    return std::optional<RMember>{};
  }

  extent_hash_ = support::Sha256{};
  extent_hash_.update(std::span<const std::byte>{*first_block});
  auto header = parse_header(std::span<const std::byte>{*first_block});
  if (!header) {
    return std::unexpected(header.error());
  }
  bool has_pax = false;
  Pax pax;

  if (header->typeflag == 'x') {
    has_pax = true;
    if (header->size > kPaxByteCap) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-size"});
    }
    auto pax_total = padded_size(header->size, "pax-size");
    if (!pax_total) {
      return std::unexpected(pax_total.error());
    }
    auto pax_size = checked_size(header->size, "pax-size");
    if (!pax_size) {
      return std::unexpected(pax_size.error());
    }
    auto pax_bytes = consume(*pax_size, true);
    if (!pax_bytes) {
      return std::unexpected(pax_bytes.error());
    }
    if (auto ok = skip(*pax_total - *pax_size, true); !ok) {
      return std::unexpected(ok.error());
    }
    auto parsed_pax = parse_pax(std::span<const std::byte>{*pax_bytes});
    if (!parsed_pax) {
      return std::unexpected(parsed_pax.error());
    }
    pax = std::move(*parsed_pax);

    auto member_block = consume(kBlockSize, false);
    if (!member_block) {
      return std::unexpected(member_block.error());
    }
    if (is_zero_block(*member_block)) {
      return std::unexpected(BivError{ErrKind::ParseError, {}, "pax-without-member"});
    }
    extent_hash_.update(std::span<const std::byte>{*member_block});
    header = parse_header(std::span<const std::byte>{*member_block});
    if (!header) {
      return std::unexpected(header.error());
    }
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
  if (meta.size > kMemberPayloadByteCap) {
    return std::unexpected(BivError{ErrKind::ParseError, meta.path, "payload-size"});
  }

  auto payload_total = padded_size(meta.size, "payload-size");
  if (!payload_total) {
    return std::unexpected(payload_total.error());
  }
  auto payload_size = checked_size(meta.size, "payload-size");
  if (!payload_size) {
    return std::unexpected(payload_size.error());
  }
  current_ = Current{
      .size = meta.size,
      .read = 0,
      .padding = *payload_total - *payload_size,
      .active = true,
  };
  ++member_count_;
  return RMember{.meta = std::move(meta), .has_pax = has_pax};
}

expected<size_t> TarReader::read_data(std::span<std::byte> out) {
  if (!current_.active || out.empty()) {
    return 0U;
  }
  const uint64_t remaining = current_.size - current_.read;
  if (remaining == 0U) {
    if (auto ok = finish_current(); !ok) {
      return std::unexpected(ok.error());
    }
    return 0U;
  }
  const size_t n = static_cast<size_t>(std::min<uint64_t>(out.size(), remaining));
  if (auto ok = consume_into(out.first(n), true); !ok) {
    return std::unexpected(ok.error());
  }
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
