#include "adapters/secure_io.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstddef>
#include <filesystem>
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
    return std::unexpected(containment_error(path, errno));
  }
  for (std::size_t i = 0; i < components->size(); ++i) {
    const bool final = i + 1U == components->size();
    int flags = O_RDONLY | O_NOFOLLOW | O_CLOEXEC | O_NONBLOCK;
    if (!final || directory) {
      flags |= O_DIRECTORY;
    }
    Fd next{::openat(current.get(), components->at(i).c_str(), flags)};
    if (!next.valid()) {
      return std::unexpected(containment_error(path, errno));
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
  bool published{false};
};

expected<void> preflight_relative(const int root_fd, const fs::path& relative) {
  auto components = safe_components(relative, true);
  if (!components) {
    return std::unexpected(components.error());
  }
  Fd current{::dup(root_fd)};
  if (!current.valid()) {
    return std::unexpected(containment_error(relative, errno));
  }
  for (std::size_t i = 0; i + 1U < components->size(); ++i) {
    Fd next{::openat(current.get(), components->at(i).c_str(),
                     O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    if (!next.valid()) {
      if (errno == ENOENT) {
        return {};
      }
      return std::unexpected(containment_error(relative, errno));
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
    return std::unexpected(containment_error(relative, errno));
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
    return std::unexpected(containment_error(request.relative_path, errno));
  }
  for (std::size_t i = 0; i + 1U < components->size(); ++i) {
    Fd next{::openat(current.get(), components->at(i).c_str(),
                     O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    if (!next.valid() && errno == ENOENT) {
      if (::mkdirat(current.get(), components->at(i).c_str(), 0700) != 0) {
        return std::unexpected(containment_error(request.relative_path, errno));
      }
      Fd rollback_parent{::dup(current.get())};
      if (!rollback_parent.valid()) {
        ::unlinkat(current.get(), components->at(i).c_str(), AT_REMOVEDIR);
        return std::unexpected(containment_error(request.relative_path, errno));
      }
      created.push_back(CreatedDirectory{.parent = std::move(rollback_parent),
                                         .leaf = components->at(i)});
      next = Fd{::openat(current.get(), components->at(i).c_str(),
                         O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    }
    if (!next.valid()) {
      return std::unexpected(containment_error(request.relative_path, errno));
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
    return std::unexpected(containment_error(request.relative_path, errno));
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
    if (!target.temporary.empty()) {
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
    Fd temporary{::openat(target.parent.get(), target.temporary.c_str(),
                          O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC,
                          0600)};
    if (!temporary.valid()) {
      const auto error = containment_error(target.temporary, errno);
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
      const auto error = containment_error(target.leaf, errno);
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
    target.temporary.clear();
  }
  return {};
}

}  // namespace biv::adapters::secure_io
