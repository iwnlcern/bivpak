#include "core/support/portability.hpp"

#include <random>

#include <sys/random.h>

namespace biv::support {

void secure_random_bytes(unsigned char* buf, const size_t len) {
  if (::getentropy(buf, len) != 0) {
    std::random_device rd;
    for (size_t i = 0; i < len; ++i) {
      buf[i] = static_cast<unsigned char>(rd());
    }
  }
}

int64_t stat_mtime_sec(const struct stat& st) {
#if defined(__APPLE__)
  return static_cast<int64_t>(st.st_mtimespec.tv_sec);
#else
  return static_cast<int64_t>(st.st_mtim.tv_sec);
#endif
}

uint32_t stat_mtime_nsec(const struct stat& st) {
#if defined(__APPLE__)
  return static_cast<uint32_t>(st.st_mtimespec.tv_nsec);
#else
  return static_cast<uint32_t>(st.st_mtim.tv_nsec);
#endif
}

}  // namespace biv::support
