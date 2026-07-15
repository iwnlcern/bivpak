#include "core/support/portability.hpp"

#include <algorithm>
#include <random>
#include <span>

#include <sys/random.h>

namespace biv::support {

namespace {

constexpr size_t kGetentropyMax = 256;

int system_getentropy(const std::span<unsigned char> bytes) {
  return ::getentropy(bytes.data(), bytes.size());
}

} // namespace

bool detail::fill_from_getentropy(const std::span<unsigned char> bytes,
                                  const EntropyFill fill) {
  for (size_t offset = 0; offset < bytes.size();) {
    const size_t chunk_size = std::min(bytes.size() - offset, kGetentropyMax);
    const auto chunk = bytes.subspan(offset, chunk_size);
    if (fill(chunk) != 0) {
      return false;
    }
    offset += chunk_size;
  }
  return true;
}

void detail::fill_from_random_device(const std::span<unsigned char> bytes) {
  std::random_device rd;
  for (auto &byte : bytes) {
    byte = static_cast<unsigned char>(rd());
  }
}

void secure_random_bytes(unsigned char *buf, const size_t len) {
  const std::span<unsigned char> bytes{buf, len};
  if (!detail::fill_from_getentropy(bytes, system_getentropy)) {
    detail::fill_from_random_device(bytes);
  }
}

int64_t stat_mtime_sec(const struct stat &st) {
#if defined(__APPLE__)
  return static_cast<int64_t>(st.st_mtimespec.tv_sec);
#else
  return static_cast<int64_t>(st.st_mtim.tv_sec);
#endif
}

uint32_t stat_mtime_nsec(const struct stat &st) {
#if defined(__APPLE__)
  return static_cast<uint32_t>(st.st_mtimespec.tv_nsec);
#else
  return static_cast<uint32_t>(st.st_mtim.tv_nsec);
#endif
}

} // namespace biv::support
