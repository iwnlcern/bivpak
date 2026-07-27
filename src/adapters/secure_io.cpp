#include "adapters/secure_io.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace biv::adapters::secure_io {

namespace {

namespace fs = std::filesystem;

class Fd {
 public:
  Fd() = default;
  explicit Fd(const int value) : value_{value} {}
  ~Fd() {
    if (value_ >= 0) {
      ::close(value_);
    }
  }

  Fd(const Fd&) = delete;
  Fd& operator=(const Fd&) = delete;
  Fd(Fd&& other) noexcept : value_{std::exchange(other.value_, -1)} {}
  Fd& operator=(Fd&& other) noexcept {
    if (this != &other) {
      if (value_ >= 0) {
        ::close(value_);
      }
      value_ = std::exchange(other.value_, -1);
    }
    return *this;
  }

  [[nodiscard]] int get() const noexcept { return value_; }
  [[nodiscard]] bool valid() const noexcept { return value_ >= 0; }

 private:
  int value_{-1};
};

BivError containment_error(const fs::path& path, const int error_number) {
  return BivError{ErrKind::ArchiveWriteFailed, path.generic_string(),
                  "containment_refused", error_number};
}

expected<std::vector<std::string>> safe_components(const fs::path& path,
                                                   const bool require_relative) {
  if ((require_relative && path.is_absolute()) || path.empty()) {
    return std::unexpected(containment_error(path, EINVAL));
  }
  std::vector<std::string> out;
  for (const auto& component : path) {
    const auto value = component.generic_string();
    if (value.empty() || value == "/" || value == ".") {
      continue;
    }
    if (value == ".." || value.find('/') != std::string::npos ||
        value.find('\\') != std::string::npos) {
      return std::unexpected(containment_error(path, EINVAL));
    }
    out.push_back(value);
  }
  if (out.empty()) {
    return std::unexpected(containment_error(path, EINVAL));
  }
  return out;
}

expected<Fd> open_absolute_no_follow(const fs::path& path, const bool directory) {
  auto absolute = fs::absolute(path).lexically_normal();
  auto components = safe_components(absolute, false);
  if (!components) {
    return std::unexpected(components.error());
  }
  Fd current{::open("/", O_RDONLY | O_DIRECTORY | O_CLOEXEC)};
  if (!current.valid()) {
    const int captured = errno;
    return std::unexpected(internal::ambient_error(path, captured));
  }
  for (std::size_t i = 0; i < components->size(); ++i) {
    const bool final = i + 1U == components->size();
    int flags = O_RDONLY | O_NOFOLLOW | O_CLOEXEC | O_NONBLOCK;
    if (!final || directory) {
      flags |= O_DIRECTORY;
    }
    Fd next{::openat(current.get(), components->at(i).c_str(), flags)};
    if (!next.valid()) {
      const int captured = errno;
      if (internal::classify(internal::SiteKind::directory_walk, captured) ==
          internal::SiteClass::containment) {
        return std::unexpected(containment_error(path, captured));
      }
      return std::unexpected(internal::ambient_error(path, captured));
    }
    current = std::move(next);
  }
  return current;
}

expected<void> write_all(const int fd, std::span<const std::byte> bytes) {
  while (!bytes.empty()) {
    const auto written = ::write(fd, bytes.data(), bytes.size());
    if (written < 0) {
      if (errno == EINTR) {
        continue;
      }
      return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, {}, errno});
    }
    bytes = bytes.subspan(static_cast<std::size_t>(written));
  }
  return {};
}

struct CreatedDirectory {
  Fd parent;
  std::string leaf;
};

struct Target {
  Fd parent;
  std::string leaf;
  std::string temporary;
  std::span<const std::byte> bytes;
  bool temporary_owned{false};
  bool published{false};
};

expected<void> preflight_relative(const int root_fd, const fs::path& relative) {
  auto components = safe_components(relative, true);
  if (!components) {
    return std::unexpected(components.error());
  }
  Fd current{::dup(root_fd)};
  if (!current.valid()) {
    const int captured = errno;
    return std::unexpected(internal::ambient_error(relative, captured));
  }
  for (std::size_t i = 0; i + 1U < components->size(); ++i) {
    Fd next{::openat(current.get(), components->at(i).c_str(),
                     O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    if (!next.valid()) {
      if (errno == ENOENT) {
        return {};
      }
      const int captured = errno;
      if (internal::classify(internal::SiteKind::directory_walk, captured) ==
          internal::SiteClass::containment) {
        return std::unexpected(containment_error(relative, captured));
      }
      return std::unexpected(internal::ambient_error(relative, captured));
    }
    current = std::move(next);
  }
  struct stat status {};
  const int stat_result = ::fstatat(current.get(), components->back().c_str(),
                                    &status, AT_SYMLINK_NOFOLLOW);
  if (stat_result == 0) {
    return std::unexpected(containment_error(relative, EEXIST));
  }
  if (errno != ENOENT) {
    const int captured = errno;
    return std::unexpected(internal::ambient_error(relative, captured));
  }
  return {};
}

expected<Target> prepare_target(const int root_fd, const WriteRequest& request,
                                std::vector<CreatedDirectory>& created,
                                const std::size_t ordinal) {
  auto components = safe_components(request.relative_path, true);
  if (!components) {
    return std::unexpected(components.error());
  }
  Fd current{::dup(root_fd)};
  if (!current.valid()) {
    const int captured = errno;
    return std::unexpected(
        internal::ambient_error(request.relative_path, captured));
  }
  for (std::size_t i = 0; i + 1U < components->size(); ++i) {
    Fd next{::openat(current.get(), components->at(i).c_str(),
                     O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    if (!next.valid() && errno == ENOENT) {
      if (::mkdirat(current.get(), components->at(i).c_str(), 0700) != 0) {
        const int captured = errno;
        if (internal::classify(internal::SiteKind::intermediate_create,
                               captured) ==
            internal::SiteClass::containment) {
          return std::unexpected(
              containment_error(request.relative_path, captured));
        }
        return std::unexpected(
            internal::ambient_error(request.relative_path, captured));
      }
      Fd rollback_parent{::dup(current.get())};
      if (!rollback_parent.valid()) {
        const int captured = errno;
        ::unlinkat(current.get(), components->at(i).c_str(), AT_REMOVEDIR);
        return std::unexpected(
            internal::ambient_error(request.relative_path, captured));
      }
      created.push_back(CreatedDirectory{.parent = std::move(rollback_parent),
                                         .leaf = components->at(i)});
      next = Fd{::openat(current.get(), components->at(i).c_str(),
                         O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    }
    if (!next.valid()) {
      const int captured = errno;
      if (internal::classify(internal::SiteKind::directory_walk, captured) ==
          internal::SiteClass::containment) {
        return std::unexpected(
            containment_error(request.relative_path, captured));
      }
      return std::unexpected(
          internal::ambient_error(request.relative_path, captured));
    }
    current = std::move(next);
  }

  struct stat status {};
  const int stat_result = ::fstatat(current.get(), components->back().c_str(),
                                    &status, AT_SYMLINK_NOFOLLOW);
  if (stat_result == 0) {
    return std::unexpected(containment_error(request.relative_path, EEXIST));
  }
  if (errno != ENOENT) {
    const int captured = errno;
    return std::unexpected(
        internal::ambient_error(request.relative_path, captured));
  }
  return Target{.parent = std::move(current),
                .leaf = components->back(),
                .temporary = ".bivpak-install-" + std::to_string(::getpid()) +
                             "-" + std::to_string(ordinal) + ".tmp",
                .bytes = request.bytes};
}

void rollback(std::vector<Target>& targets,
              std::vector<CreatedDirectory>& created) {
  for (auto& target : targets) {
    if (target.temporary_owned) {
      ::unlinkat(target.parent.get(), target.temporary.c_str(), 0);
    }
    if (target.published) {
      ::unlinkat(target.parent.get(), target.leaf.c_str(), 0);
    }
  }
  for (auto it = created.rbegin(); it != created.rend(); ++it) {
    ::unlinkat(it->parent.get(), it->leaf.c_str(), AT_REMOVEDIR);
  }
}

}  // namespace

std::optional<std::string_view> errno_symbol(const int err_no) noexcept {
  switch (err_no) {
    // EXACTLY ONE case per equal-valued GROUP, carrying that group's canonical
    // spelling from tests/errno_pins.txt. A group's non-canonical members get
    // NO case label. Rule 3 -- an unpinned group cannot ship -- is enforced by
    // the compiler-derived gate.
#ifdef E2BIG
    case E2BIG: return "E2BIG";
#endif
#ifdef EACCES
    case EACCES: return "EACCES";
#endif
#ifdef EADDRINUSE
    case EADDRINUSE: return "EADDRINUSE";
#endif
#ifdef EADDRNOTAVAIL
    case EADDRNOTAVAIL: return "EADDRNOTAVAIL";
#endif
#ifdef EADV
    case EADV: return "EADV";
#endif
#ifdef EAFNOSUPPORT
    case EAFNOSUPPORT: return "EAFNOSUPPORT";
#endif
#ifdef EAGAIN
    case EAGAIN: return "EAGAIN";
#endif
#ifdef EALREADY
    case EALREADY: return "EALREADY";
#endif
#ifdef EAUTH
    case EAUTH: return "EAUTH";
#endif
#ifdef EBADARCH
    case EBADARCH: return "EBADARCH";
#endif
#ifdef EBADE
    case EBADE: return "EBADE";
#endif
#ifdef EBADEXEC
    case EBADEXEC: return "EBADEXEC";
#endif
#ifdef EBADF
    case EBADF: return "EBADF";
#endif
#ifdef EBADFD
    case EBADFD: return "EBADFD";
#endif
#ifdef EBADMACHO
    case EBADMACHO: return "EBADMACHO";
#endif
#ifdef EBADMSG
    case EBADMSG: return "EBADMSG";
#endif
#ifdef EBADR
    case EBADR: return "EBADR";
#endif
#ifdef EBADRPC
    case EBADRPC: return "EBADRPC";
#endif
#ifdef EBADRQC
    case EBADRQC: return "EBADRQC";
#endif
#ifdef EBADSLT
    case EBADSLT: return "EBADSLT";
#endif
#ifdef EBFONT
    case EBFONT: return "EBFONT";
#endif
#ifdef EBUSY
    case EBUSY: return "EBUSY";
#endif
#ifdef ECANCELED
    case ECANCELED: return "ECANCELED";
#endif
#ifdef ECHILD
    case ECHILD: return "ECHILD";
#endif
#ifdef ECHRNG
    case ECHRNG: return "ECHRNG";
#endif
#ifdef ECOMM
    case ECOMM: return "ECOMM";
#endif
#ifdef ECONNABORTED
    case ECONNABORTED: return "ECONNABORTED";
#endif
#ifdef ECONNREFUSED
    case ECONNREFUSED: return "ECONNREFUSED";
#endif
#ifdef ECONNRESET
    case ECONNRESET: return "ECONNRESET";
#endif
#ifdef EDEADLK
    case EDEADLK: return "EDEADLK";
#endif
#ifdef EDESTADDRREQ
    case EDESTADDRREQ: return "EDESTADDRREQ";
#endif
#ifdef EDEVERR
    case EDEVERR: return "EDEVERR";
#endif
#ifdef EDOM
    case EDOM: return "EDOM";
#endif
#ifdef EDOTDOT
    case EDOTDOT: return "EDOTDOT";
#endif
#ifdef EDQUOT
    case EDQUOT: return "EDQUOT";
#endif
#ifdef EEXIST
    case EEXIST: return "EEXIST";
#endif
#ifdef EFAULT
    case EFAULT: return "EFAULT";
#endif
#ifdef EFBIG
    case EFBIG: return "EFBIG";
#endif
#ifdef EFTYPE
    case EFTYPE: return "EFTYPE";
#endif
#ifdef EHOSTDOWN
    case EHOSTDOWN: return "EHOSTDOWN";
#endif
#ifdef EHOSTUNREACH
    case EHOSTUNREACH: return "EHOSTUNREACH";
#endif
#ifdef EHWPOISON
    case EHWPOISON: return "EHWPOISON";
#endif
#ifdef EIDRM
    case EIDRM: return "EIDRM";
#endif
#ifdef EILSEQ
    case EILSEQ: return "EILSEQ";
#endif
#ifdef EINPROGRESS
    case EINPROGRESS: return "EINPROGRESS";
#endif
#ifdef EINTR
    case EINTR: return "EINTR";
#endif
#ifdef EINVAL
    case EINVAL: return "EINVAL";
#endif
#ifdef EIO
    case EIO: return "EIO";
#endif
#ifdef EISCONN
    case EISCONN: return "EISCONN";
#endif
#ifdef EISDIR
    case EISDIR: return "EISDIR";
#endif
#ifdef EISNAM
    case EISNAM: return "EISNAM";
#endif
#ifdef EKEYEXPIRED
    case EKEYEXPIRED: return "EKEYEXPIRED";
#endif
#ifdef EKEYREJECTED
    case EKEYREJECTED: return "EKEYREJECTED";
#endif
#ifdef EKEYREVOKED
    case EKEYREVOKED: return "EKEYREVOKED";
#endif
#ifdef EL2HLT
    case EL2HLT: return "EL2HLT";
#endif
#ifdef EL2NSYNC
    case EL2NSYNC: return "EL2NSYNC";
#endif
#ifdef EL3HLT
    case EL3HLT: return "EL3HLT";
#endif
#ifdef EL3RST
    case EL3RST: return "EL3RST";
#endif
#ifdef ELIBACC
    case ELIBACC: return "ELIBACC";
#endif
#ifdef ELIBBAD
    case ELIBBAD: return "ELIBBAD";
#endif
#ifdef ELIBEXEC
    case ELIBEXEC: return "ELIBEXEC";
#endif
#ifdef ELIBMAX
    case ELIBMAX: return "ELIBMAX";
#endif
#ifdef ELIBSCN
    case ELIBSCN: return "ELIBSCN";
#endif
#ifdef ELNRNG
    case ELNRNG: return "ELNRNG";
#endif
#ifdef ELOOP
    case ELOOP: return "ELOOP";
#endif
#ifdef EMEDIUMTYPE
    case EMEDIUMTYPE: return "EMEDIUMTYPE";
#endif
#ifdef EMFILE
    case EMFILE: return "EMFILE";
#endif
#ifdef EMLINK
    case EMLINK: return "EMLINK";
#endif
#ifdef EMSGSIZE
    case EMSGSIZE: return "EMSGSIZE";
#endif
#ifdef EMULTIHOP
    case EMULTIHOP: return "EMULTIHOP";
#endif
#ifdef ENAMETOOLONG
    case ENAMETOOLONG: return "ENAMETOOLONG";
#endif
#ifdef ENAVAIL
    case ENAVAIL: return "ENAVAIL";
#endif
#ifdef ENEEDAUTH
    case ENEEDAUTH: return "ENEEDAUTH";
#endif
#ifdef ENETDOWN
    case ENETDOWN: return "ENETDOWN";
#endif
#ifdef ENETRESET
    case ENETRESET: return "ENETRESET";
#endif
#ifdef ENETUNREACH
    case ENETUNREACH: return "ENETUNREACH";
#endif
#ifdef ENFILE
    case ENFILE: return "ENFILE";
#endif
#ifdef ENOANO
    case ENOANO: return "ENOANO";
#endif
#ifdef ENOATTR
    case ENOATTR: return "ENOATTR";
#endif
#ifdef ENOBUFS
    case ENOBUFS: return "ENOBUFS";
#endif
#ifdef ENOCSI
    case ENOCSI: return "ENOCSI";
#endif
#ifdef ENODATA
    case ENODATA: return "ENODATA";
#endif
#ifdef ENODEV
    case ENODEV: return "ENODEV";
#endif
#ifdef ENOENT
    case ENOENT: return "ENOENT";
#endif
#ifdef ENOEXEC
    case ENOEXEC: return "ENOEXEC";
#endif
#ifdef ENOKEY
    case ENOKEY: return "ENOKEY";
#endif
#ifdef ENOLCK
    case ENOLCK: return "ENOLCK";
#endif
#ifdef ENOLINK
    case ENOLINK: return "ENOLINK";
#endif
#ifdef ENOMEDIUM
    case ENOMEDIUM: return "ENOMEDIUM";
#endif
#ifdef ENOMEM
    case ENOMEM: return "ENOMEM";
#endif
#ifdef ENOMSG
    case ENOMSG: return "ENOMSG";
#endif
#ifdef ENONET
    case ENONET: return "ENONET";
#endif
#ifdef ENOPKG
    case ENOPKG: return "ENOPKG";
#endif
#ifdef ENOPOLICY
    case ENOPOLICY: return "ENOPOLICY";
#endif
#ifdef ENOPROTOOPT
    case ENOPROTOOPT: return "ENOPROTOOPT";
#endif
#ifdef ENOSPC
    case ENOSPC: return "ENOSPC";
#endif
#ifdef ENOSR
    case ENOSR: return "ENOSR";
#endif
#ifdef ENOSTR
    case ENOSTR: return "ENOSTR";
#endif
#ifdef ENOSYS
    case ENOSYS: return "ENOSYS";
#endif
#ifdef ENOTBLK
    case ENOTBLK: return "ENOTBLK";
#endif
#ifdef ENOTCAPABLE
    case ENOTCAPABLE: return "ENOTCAPABLE";
#endif
#ifdef ENOTCONN
    case ENOTCONN: return "ENOTCONN";
#endif
#ifdef ENOTDIR
    case ENOTDIR: return "ENOTDIR";
#endif
#ifdef ENOTEMPTY
    case ENOTEMPTY: return "ENOTEMPTY";
#endif
#ifdef ENOTNAM
    case ENOTNAM: return "ENOTNAM";
#endif
#ifdef ENOTRECOVERABLE
    case ENOTRECOVERABLE: return "ENOTRECOVERABLE";
#endif
#ifdef ENOTSOCK
    case ENOTSOCK: return "ENOTSOCK";
#endif
#ifdef ENOTSUP
    case ENOTSUP: return "ENOTSUP";
#endif
#ifdef ENOTTY
    case ENOTTY: return "ENOTTY";
#endif
#ifdef ENOTUNIQ
    case ENOTUNIQ: return "ENOTUNIQ";
#endif
#ifdef ENXIO
    case ENXIO: return "ENXIO";
#endif
#ifdef EOVERFLOW
    case EOVERFLOW: return "EOVERFLOW";
#endif
#ifdef EOWNERDEAD
    case EOWNERDEAD: return "EOWNERDEAD";
#endif
#ifdef EPERM
    case EPERM: return "EPERM";
#endif
#ifdef EPFNOSUPPORT
    case EPFNOSUPPORT: return "EPFNOSUPPORT";
#endif
#ifdef EPIPE
    case EPIPE: return "EPIPE";
#endif
#ifdef EPROCLIM
    case EPROCLIM: return "EPROCLIM";
#endif
#ifdef EPROCUNAVAIL
    case EPROCUNAVAIL: return "EPROCUNAVAIL";
#endif
#ifdef EPROGMISMATCH
    case EPROGMISMATCH: return "EPROGMISMATCH";
#endif
#ifdef EPROGUNAVAIL
    case EPROGUNAVAIL: return "EPROGUNAVAIL";
#endif
#ifdef EPROTO
    case EPROTO: return "EPROTO";
#endif
#ifdef EPROTONOSUPPORT
    case EPROTONOSUPPORT: return "EPROTONOSUPPORT";
#endif
#ifdef EPROTOTYPE
    case EPROTOTYPE: return "EPROTOTYPE";
#endif
#ifdef EPWROFF
    case EPWROFF: return "EPWROFF";
#endif
#ifdef EQFULL
    case EQFULL: return "EQFULL";
#endif
#ifdef ERANGE
    case ERANGE: return "ERANGE";
#endif
#ifdef EREMCHG
    case EREMCHG: return "EREMCHG";
#endif
#ifdef EREMOTE
    case EREMOTE: return "EREMOTE";
#endif
#ifdef EREMOTEIO
    case EREMOTEIO: return "EREMOTEIO";
#endif
#ifdef ERESTART
    case ERESTART: return "ERESTART";
#endif
#ifdef ERFKILL
    case ERFKILL: return "ERFKILL";
#endif
#ifdef EROFS
    case EROFS: return "EROFS";
#endif
#ifdef ERPCMISMATCH
    case ERPCMISMATCH: return "ERPCMISMATCH";
#endif
#ifdef ESHLIBVERS
    case ESHLIBVERS: return "ESHLIBVERS";
#endif
#ifdef ESHUTDOWN
    case ESHUTDOWN: return "ESHUTDOWN";
#endif
#ifdef ESOCKTNOSUPPORT
    case ESOCKTNOSUPPORT: return "ESOCKTNOSUPPORT";
#endif
#ifdef ESPIPE
    case ESPIPE: return "ESPIPE";
#endif
#ifdef ESRCH
    case ESRCH: return "ESRCH";
#endif
#ifdef ESRMNT
    case ESRMNT: return "ESRMNT";
#endif
#ifdef ESTALE
    case ESTALE: return "ESTALE";
#endif
#ifdef ESTRPIPE
    case ESTRPIPE: return "ESTRPIPE";
#endif
#ifdef ETIME
    case ETIME: return "ETIME";
#endif
#ifdef ETIMEDOUT
    case ETIMEDOUT: return "ETIMEDOUT";
#endif
#ifdef ETOOMANYREFS
    case ETOOMANYREFS: return "ETOOMANYREFS";
#endif
#ifdef ETXTBSY
    case ETXTBSY: return "ETXTBSY";
#endif
#ifdef EUCLEAN
    case EUCLEAN: return "EUCLEAN";
#endif
#ifdef EUNATCH
    case EUNATCH: return "EUNATCH";
#endif
#ifdef EUSERS
    case EUSERS: return "EUSERS";
#endif
#ifdef EXDEV
    case EXDEV: return "EXDEV";
#endif
#ifdef EXFULL
    case EXFULL: return "EXFULL";
#endif

    // MULTI-MEMBER GROUPS -- conditional, because group membership is a
    // PER-TARGET fact. Equal names are covered by the canonical case above;
    // distinct names become singleton groups and need their own spelling.
#if defined(ENOTSUP) && defined(EOPNOTSUPP) && (ENOTSUP) != (EOPNOTSUPP)
    case EOPNOTSUPP: return "EOPNOTSUPP";
#endif
#if defined(EAGAIN) && defined(EWOULDBLOCK) && (EAGAIN) != (EWOULDBLOCK)
    case EWOULDBLOCK: return "EWOULDBLOCK";
#endif
#if defined(EDEADLK) && defined(EDEADLOCK) && (EDEADLK) != (EDEADLOCK)
    case EDEADLOCK: return "EDEADLOCK";
#endif
#if defined(EBADMSG) && defined(EFSBADCRC) && (EBADMSG) != (EFSBADCRC)
    case EFSBADCRC: return "EFSBADCRC";
#endif
#if defined(EUCLEAN) && defined(EFSCORRUPTED) && (EUCLEAN) != (EFSCORRUPTED)
    case EFSCORRUPTED: return "EFSCORRUPTED";
#endif
    default:
      break;
  }
  // Unreachable from any errno capture under Reading B. Reaching it means a
  // non-errno integer was placed in BivError::err_no -- a capture-site defect.
  assert(err_no == 0 && "errno_symbol: nonzero value outside the target namespace");
  return std::nullopt;
}

namespace internal {

SiteClass classify(const SiteKind kind, const int err_no) noexcept {
  switch (kind) {
    case SiteKind::directory_walk:
      // The errno IS the I7 signal here: a symlink or a non-directory was
      // interposed in a walk that refused to follow one.
      return (err_no == ELOOP || err_no == ENOTDIR) ? SiteClass::containment
                                                    : SiteClass::ambient;
    case SiteKind::intermediate_create:
    case SiteKind::temporary_create:
    case SiteKind::publish_link:
      // EEXIST at each of these three is a no-replace refusal: a node occupied
      // a name this operation had established was free, or must be free.
      return err_no == EEXIST ? SiteClass::containment : SiteClass::ambient;
  }
  return SiteClass::ambient;
}

BivError ambient_error(const fs::path& path, const int err_no) {
  return BivError{ErrKind::ArchiveWriteFailed, path.generic_string(), "",
                  err_no};
}

}  // namespace internal

struct ReadHandle::State {
  Fd fd;
  std::uint64_t size{0};
};

ReadHandle::ReadHandle(std::shared_ptr<State> state) : state_{std::move(state)} {}

std::uint64_t ReadHandle::size() const noexcept {
  return state_ ? state_->size : 0;
}

expected<void> ReadHandle::stream(const ByteSink& sink) const {
  if (!state_) {
    return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, "invalid-read-handle"});
  }
  std::array<std::byte, 8192> buffer{};
  off_t offset = 0;
  while (static_cast<std::uint64_t>(offset) < state_->size) {
    const auto remaining = state_->size - static_cast<std::uint64_t>(offset);
    const auto count = ::pread(state_->fd.get(), buffer.data(),
                               std::min<std::uint64_t>(buffer.size(), remaining),
                               offset);
    if (count < 0) {
      if (errno == EINTR) {
        continue;
      }
      return std::unexpected(BivError{ErrKind::ArchiveWriteFailed, {}, {}, errno});
    }
    if (count == 0) {
      return std::unexpected(
          BivError{ErrKind::ArchiveWriteFailed, {}, "source-size-changed"});
    }
    auto ok = sink(std::span<const std::byte>{buffer.data(),
                                              static_cast<std::size_t>(count)});
    if (!ok) {
      return ok;
    }
    offset += count;
  }
  return {};
}

expected<void> validate_directory_no_follow(const fs::path& path) {
  auto directory = open_absolute_no_follow(path, true);
  if (!directory) {
    return std::unexpected(directory.error());
  }
  return {};
}

expected<ReadHandle> open_read_no_follow(const fs::path& path) {
  auto file = open_absolute_no_follow(path, false);
  if (!file) {
    return std::unexpected(file.error());
  }
  struct stat status {};
  if (::fstat(file->get(), &status) != 0 || !S_ISREG(status.st_mode)) {
    return std::unexpected(containment_error(path, errno == 0 ? EINVAL : errno));
  }
  auto state = std::make_shared<ReadHandle::State>();
  state->fd = std::move(*file);
  state->size = static_cast<std::uint64_t>(status.st_size);
  return ReadHandle{std::move(state)};
}

expected<void> write_batch_no_replace(const fs::path& root,
                                      const std::span<const WriteRequest> requests) {
  auto root_fd = open_absolute_no_follow(root, true);
  if (!root_fd) {
    return std::unexpected(root_fd.error());
  }
  for (const auto& request : requests) {
    if (auto ok = preflight_relative(root_fd->get(), request.relative_path); !ok) {
      return ok;
    }
  }

  std::vector<CreatedDirectory> created;
  std::vector<Target> targets;
  targets.reserve(requests.size());
  std::size_t ordinal = 0;
  for (const auto& request : requests) {
    auto target = prepare_target(root_fd->get(), request, created, ordinal);
    if (!target) {
      rollback(targets, created);
      return std::unexpected(target.error());
    }
    targets.push_back(std::move(*target));
    ++ordinal;
  }

  for (auto& target : targets) {
    Fd temporary;
    const std::string base_name = target.temporary;
    for (std::size_t attempt = 0; attempt < 1024U; ++attempt) {
      target.temporary =
          attempt == 0U ? base_name : base_name + "." + std::to_string(attempt);
      temporary = Fd{::openat(target.parent.get(), target.temporary.c_str(),
                              O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW |
                                  O_CLOEXEC,
                              0600)};
      if (temporary.valid()) {
        target.temporary_owned = true;
        break;
      }
      if (errno != EEXIST) {
        break;
      }
    }
    if (!temporary.valid()) {
      const int captured = errno;
      const auto error =
          internal::classify(internal::SiteKind::temporary_create, captured) ==
                  internal::SiteClass::containment
              ? containment_error(target.temporary, captured)
              : internal::ambient_error(target.temporary, captured);
      rollback(targets, created);
      return std::unexpected(error);
    }
    if (auto ok = write_all(temporary.get(), target.bytes); !ok ||
        ::fsync(temporary.get()) != 0) {
      const auto error = ok ? BivError{ErrKind::ArchiveWriteFailed, {}, {}, errno}
                            : ok.error();
      rollback(targets, created);
      return std::unexpected(error);
    }
  }

  for (auto& target : targets) {
    if (::linkat(target.parent.get(), target.temporary.c_str(), target.parent.get(),
                 target.leaf.c_str(), 0) != 0) {
      const int captured = errno;
      const auto error =
          internal::classify(internal::SiteKind::publish_link, captured) ==
                  internal::SiteClass::containment
              ? containment_error(target.leaf, captured)
              : internal::ambient_error(target.leaf, captured);
      rollback(targets, created);
      return std::unexpected(error);
    }
    target.published = true;
    if (::unlinkat(target.parent.get(), target.temporary.c_str(), 0) != 0 ||
        ::fsync(target.parent.get()) != 0) {
      const auto error = BivError{ErrKind::ArchiveWriteFailed,
                                  std::string{target.leaf}, {}, errno};
      rollback(targets, created);
      return std::unexpected(error);
    }
    target.temporary_owned = false;
    target.temporary.clear();
  }
  return {};
}

}  // namespace biv::adapters::secure_io
