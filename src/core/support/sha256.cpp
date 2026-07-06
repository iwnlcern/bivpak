#include "core/support/sha256.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <iterator>

namespace biv::support {

namespace {

constexpr std::array<uint32_t, 64> kRoundConstants{
    0x428a2f98U, 0x71374491U, 0xb5c0fbcfU, 0xe9b5dba5U, 0x3956c25bU, 0x59f111f1U, 0x923f82a4U,
    0xab1c5ed5U, 0xd807aa98U, 0x12835b01U, 0x243185beU, 0x550c7dc3U, 0x72be5d74U, 0x80deb1feU,
    0x9bdc06a7U, 0xc19bf174U, 0xe49b69c1U, 0xefbe4786U, 0x0fc19dc6U, 0x240ca1ccU, 0x2de92c6fU,
    0x4a7484aaU, 0x5cb0a9dcU, 0x76f988daU, 0x983e5152U, 0xa831c66dU, 0xb00327c8U, 0xbf597fc7U,
    0xc6e00bf3U, 0xd5a79147U, 0x06ca6351U, 0x14292967U, 0x27b70a85U, 0x2e1b2138U, 0x4d2c6dfcU,
    0x53380d13U, 0x650a7354U, 0x766a0abbU, 0x81c2c92eU, 0x92722c85U, 0xa2bfe8a1U, 0xa81a664bU,
    0xc24b8b70U, 0xc76c51a3U, 0xd192e819U, 0xd6990624U, 0xf40e3585U, 0x106aa070U, 0x19a4c116U,
    0x1e376c08U, 0x2748774cU, 0x34b0bcb5U, 0x391c0cb3U, 0x4ed8aa4aU, 0x5b9cca4fU, 0x682e6ff3U,
    0x748f82eeU, 0x78a5636fU, 0x84c87814U, 0x8cc70208U, 0x90befffaU, 0xa4506cebU, 0xbef9a3f7U,
    0xc67178f2U};

uint32_t load_be32(std::span<const std::byte> bytes) {
  auto it = bytes.begin();
  const uint32_t b0 = std::to_integer<uint32_t>(*it);
  ++it;
  const uint32_t b1 = std::to_integer<uint32_t>(*it);
  ++it;
  const uint32_t b2 = std::to_integer<uint32_t>(*it);
  ++it;
  const uint32_t b3 = std::to_integer<uint32_t>(*it);
  return (b0 << 24U) | (b1 << 16U) | (b2 << 8U) | b3;
}

void store_be64(std::span<std::byte> out, uint64_t value) {
  for (size_t i = 0; i < out.size(); ++i) {
    const auto shift = static_cast<unsigned>((out.size() - 1U - i) * 8U);
    *std::next(out.begin(), static_cast<std::ptrdiff_t>(i)) =
        static_cast<std::byte>((value >> shift) & 0xffU);
  }
}

std::string hex_digest(const std::array<uint32_t, 8>& state) {
  std::string out;
  out.resize(64);
  size_t pos = 0;
  for (const uint32_t word : state) {
    for (int shift = 28; shift >= 0; shift -= 4) {
      const uint32_t nibble = (word >> static_cast<unsigned>(shift)) & 0x0fU;
      out.at(pos) = static_cast<char>(nibble < 10U ? ('0' + nibble) : ('a' + (nibble - 10U)));
      ++pos;
    }
  }
  return out;
}

}  // namespace

Sha256::Sha256()
    : state_{0x6a09e667U,
             0xbb67ae85U,
             0x3c6ef372U,
             0xa54ff53aU,
             0x510e527fU,
             0x9b05688cU,
             0x1f83d9abU,
             0x5be0cd19U} {}

void Sha256::update(const std::span<const std::byte> data) {
  if (finished_ || data.empty()) {
    return;
  }

  bit_count_ += static_cast<uint64_t>(data.size()) * 8U;
  size_t offset = 0;
  while (offset < data.size()) {
    const size_t take = std::min(buffer_.size() - buffer_size_, data.size() - offset);
    std::ranges::copy(data.subspan(offset, take),
                      std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(buffer_size_)));
    buffer_size_ += take;
    offset += take;
    if (buffer_size_ == buffer_.size()) {
      transform(std::span<const std::byte, 64>{buffer_});
      buffer_size_ = 0;
    }
  }
}

std::string Sha256::finish_hex() {
  if (finished_) {
    return finished_hex_;
  }

  buffer_.at(buffer_size_) = std::byte{0x80};
  ++buffer_size_;
  if (buffer_size_ > 56U) {
    std::ranges::fill(std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(buffer_size_)),
                      buffer_.end(),
                      std::byte{0});
    transform(std::span<const std::byte, 64>{buffer_});
    buffer_size_ = 0;
  }
  std::ranges::fill(std::next(buffer_.begin(), static_cast<std::ptrdiff_t>(buffer_size_)),
                    std::next(buffer_.begin(), 56),
                    std::byte{0});
  store_be64(std::span<std::byte>{buffer_}.last(8), bit_count_);
  transform(std::span<const std::byte, 64>{buffer_});

  finished_ = true;
  finished_hex_ = hex_digest(state_);
  return finished_hex_;
}

void Sha256::transform(const std::span<const std::byte, 64> block) {
  std::array<uint32_t, 64> words {};
  for (size_t i = 0; i < 16U; ++i) {
    words.at(i) = load_be32(block.subspan(i * 4U, 4U));
  }
  for (size_t i = 16U; i < words.size(); ++i) {
    const uint32_t s0 =
        std::rotr(words.at(i - 15U), 7U) ^ std::rotr(words.at(i - 15U), 18U) ^ (words.at(i - 15U) >> 3U);
    const uint32_t s1 =
        std::rotr(words.at(i - 2U), 17U) ^ std::rotr(words.at(i - 2U), 19U) ^ (words.at(i - 2U) >> 10U);
    words.at(i) = words.at(i - 16U) + s0 + words.at(i - 7U) + s1;
  }

  uint32_t a = state_.at(0);
  uint32_t b = state_.at(1);
  uint32_t c = state_.at(2);
  uint32_t d = state_.at(3);
  uint32_t e = state_.at(4);
  uint32_t f = state_.at(5);
  uint32_t g = state_.at(6);
  uint32_t h = state_.at(7);

  for (size_t i = 0; i < words.size(); ++i) {
    const uint32_t sum1 = std::rotr(e, 6U) ^ std::rotr(e, 11U) ^ std::rotr(e, 25U);
    const uint32_t choose = (e & f) ^ (~e & g);
    const uint32_t temp1 = h + sum1 + choose + kRoundConstants.at(i) + words.at(i);
    const uint32_t sum0 = std::rotr(a, 2U) ^ std::rotr(a, 13U) ^ std::rotr(a, 22U);
    const uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
    const uint32_t temp2 = sum0 + majority;
    h = g;
    g = f;
    f = e;
    e = d + temp1;
    d = c;
    c = b;
    b = a;
    a = temp1 + temp2;
  }

  state_.at(0) += a;
  state_.at(1) += b;
  state_.at(2) += c;
  state_.at(3) += d;
  state_.at(4) += e;
  state_.at(5) += f;
  state_.at(6) += g;
  state_.at(7) += h;
}

}  // namespace biv::support
