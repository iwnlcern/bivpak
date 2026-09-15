/* readtrace.c — LEG 1/2 instrument: an in-process read accountant (LD_PRELOAD; no ptrace, so valid under CPU emulation where strace is not).
   Wraps read/pread/pread64 from libc, resolves the fd's path via /proc/self/fd/N at each call, and sums the BYTES RETURNED per path for paths
   under READTRACE_PREFIX; at process exit appends "path<TAB>bytes" rows to READTRACE_OUT. No content is ever recorded — only counts.
   Validated in Phase L by a must-be-YES control (dd over one store file → its row equals its size) before the pack run is read. */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
typedef ssize_t (*read_fn)(int, void*, size_t);
typedef ssize_t (*pread_fn)(int, void*, size_t, off_t);
static read_fn real_read;
static pread_fn real_pread;
static pread_fn real_pread64;
struct ent { char path[1024]; unsigned long long bytes; };
static struct ent table[16384];
static int count;
static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
static void account(int fd, ssize_t r) {
  if (r <= 0) return;
  char link[64]; char path[1024];
  snprintf(link, sizeof link, "/proc/self/fd/%d", fd);
  ssize_t l = readlink(link, path, sizeof path - 1);
  if (l <= 0) return;
  path[l] = 0;
  const char* pre = getenv("READTRACE_PREFIX");
  if (pre && strncmp(path, pre, strlen(pre)) != 0) return;
  pthread_mutex_lock(&mu);
  for (int i = 0; i < count; i++) {
    if (strcmp(table[i].path, path) == 0) { table[i].bytes += (unsigned long long)r; pthread_mutex_unlock(&mu); return; }
  }
  if (count < 16384) { strncpy(table[count].path, path, sizeof table[count].path - 1); table[count].bytes = (unsigned long long)r; count++; }
  pthread_mutex_unlock(&mu);
}
ssize_t read(int fd, void* buf, size_t n) {
  if (!real_read) real_read = (read_fn)dlsym(RTLD_NEXT, "read");
  ssize_t r = real_read(fd, buf, n); account(fd, r); return r;
}
ssize_t pread(int fd, void* buf, size_t n, off_t off) {
  if (!real_pread) real_pread = (pread_fn)dlsym(RTLD_NEXT, "pread");
  ssize_t r = real_pread(fd, buf, n, off); account(fd, r); return r;
}
ssize_t pread64(int fd, void* buf, size_t n, off_t off) {
  if (!real_pread64) real_pread64 = (pread_fn)dlsym(RTLD_NEXT, "pread64");
  ssize_t r = real_pread64(fd, buf, n, off); account(fd, r); return r;
}
__attribute__((destructor)) static void readtrace_dump(void) {
  const char* out = getenv("READTRACE_OUT");
  if (!out) return;
  FILE* f = fopen(out, "a");
  if (!f) return;
  for (int i = 0; i < count; i++) fprintf(f, "%s\t%llu\n", table[i].path, table[i].bytes);
  fclose(f);
}
