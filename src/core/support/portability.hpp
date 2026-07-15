#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include <sys/stat.h>

namespace biv::support {

namespace detail {

using EntropyFill = int (*)(std::span<unsigned char>);

bool fill_from_getentropy(std::span<unsigned char> bytes, EntropyFill fill);
void fill_from_random_device(std::span<unsigned char> bytes);

}  // namespace detail

// Fills exactly len bytes, using getentropy in supported chunks and falling
// back to std::random_device. The fallback may throw; if it does, the buffer
// may already be partially modified.
void secure_random_bytes(unsigned char* buf, size_t len);

int64_t stat_mtime_sec(const struct stat& st);
uint32_t stat_mtime_nsec(const struct stat& st);

}  // namespace biv::support
