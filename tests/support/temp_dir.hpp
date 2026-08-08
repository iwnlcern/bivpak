#pragma once

#include <unistd.h>

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <type_traits>

namespace biv::test_support {

class TempDir {
 public:
  explicit TempDir(const std::string_view name)
      : path_{std::filesystem::temp_directory_path() /
              ("biv-test-" + std::string{name} + "-" +
               std::to_string(::getpid()) + "-" +
               std::to_string(next_id_++))} {
    std::filesystem::remove_all(path_);
    std::filesystem::create_directories(path_);
  }

  ~TempDir() { std::filesystem::remove_all(path_); }

  TempDir(const TempDir&) = delete;
  TempDir& operator=(const TempDir&) = delete;
  TempDir(TempDir&&) = delete;
  TempDir& operator=(TempDir&&) = delete;

  [[nodiscard]] const std::filesystem::path& path() const noexcept {
    return path_;
  }

 private:
  inline static std::size_t next_id_{0};
  std::filesystem::path path_;
};

static_assert(!std::is_copy_constructible_v<TempDir>);
static_assert(!std::is_move_constructible_v<TempDir>);

}  // namespace biv::test_support
