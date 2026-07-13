#pragma once

#include <cstddef>
#include <cstdint>

#include <sys/stat.h>

namespace biv::support {

void secure_random_bytes(unsigned char* buf, size_t len);

int64_t stat_mtime_sec(const struct stat& st);
uint32_t stat_mtime_nsec(const struct stat& st);

}  // namespace biv::support
