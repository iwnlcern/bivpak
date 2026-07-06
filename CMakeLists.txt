cmake_minimum_required(VERSION 3.27)
project(bivpak CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(simdjson
  URL https://github.com/simdjson/simdjson/archive/refs/tags/v3.10.1.tar.gz
  URL_HASH SHA256=1e8f881cb2c0f626c56cd3665832f1e97b9d4ffc648ad9e1067c134862bba060
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_Declare(zstd
  URL https://github.com/facebook/zstd/releases/download/v1.5.6/zstd-1.5.6.tar.gz
  URL_HASH SHA256=8c29e06cf42aacc1eafc4077ae2ec6c6fcb96a626157e0593d5e82a34fd403c1
  SOURCE_SUBDIR build/cmake
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
set(ZSTD_BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
set(ZSTD_BUILD_SHARED OFF CACHE BOOL "" FORCE)
FetchContent_Declare(catch2
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.tar.gz
  URL_HASH SHA256=c991b247a1a0d7bb9c39aa35faf0fe9e19764213f28ffba3109388e62ee0269c
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

FetchContent_MakeAvailable(simdjson zstd catch2)

add_library(bivcore STATIC
  src/core/json/writer.cpp
  src/core/manifest/manifest.cpp
  src/core/support/error.cpp
  src/core/support/version.cpp)
target_include_directories(bivcore PUBLIC src)
target_link_libraries(bivcore PUBLIC simdjson libzstd_static)
target_compile_options(bivcore PRIVATE -Wall -Wextra -Werror)

add_executable(biv src/cli/main.cpp)
target_link_libraries(biv PRIVATE bivcore)
target_compile_options(biv PRIVATE -Wall -Wextra -Werror)

enable_testing()
add_executable(biv_tests
  tests/test_smoke.cpp
  tests/test_json_writer.cpp
  tests/test_manifest.cpp
  tests/test_support.cpp)
target_link_libraries(biv_tests PRIVATE bivcore Catch2::Catch2WithMain)
target_compile_options(biv_tests PRIVATE -Wall -Wextra -Werror)
add_test(NAME biv_tests COMMAND biv_tests)
