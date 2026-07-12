cmake_minimum_required(VERSION 3.27)
project(bivpak CXX)

find_package(SQLite3 REQUIRED)

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

foreach(dep_target IN ITEMS simdjson libzstd_static)
  get_target_property(dep_includes ${dep_target} INTERFACE_INCLUDE_DIRECTORIES)
  if(dep_includes)
    set_target_properties(${dep_target} PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${dep_includes}"
      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${dep_includes}")
  endif()
endforeach()

option(BIV_ENABLE_FUZZ "Build libFuzzer targets" OFF)

add_library(bivcore STATIC
  src/core/json/writer.cpp
  src/core/container/tar_writer.cpp
  src/core/container/tar_reader.cpp
  src/core/container/zstd_stream.cpp
  src/core/ignore/matcher.cpp
  src/core/manifest/checksums.cpp
  src/core/manifest/manifest.cpp
  src/core/open/open.cpp
  src/core/open/render.cpp
  src/core/open/sessions.cpp
  src/core/pack/pack.cpp
  src/core/report/envelope.cpp
  src/core/scan/scan.cpp
  src/core/support/sha256.cpp
  src/core/support/error.cpp
  src/core/support/version.cpp)
target_include_directories(bivcore PUBLIC src)
target_link_libraries(bivcore PUBLIC simdjson libzstd_static)
target_compile_options(bivcore PRIVATE -Wall -Wextra -Werror)

# ADAPTER TARGETS
add_library(biv_adapters STATIC
  src/adapters/secure_io.cpp
  src/adapters/rewrite_common.cpp
  src/adapters/registry.cpp
  src/adapters/claude_code/claude_code.cpp
  src/adapters/claude_code/install.cpp
  src/adapters/codex/codex.cpp
  src/adapters/codex/install.cpp)
target_include_directories(biv_adapters PUBLIC src)
target_link_libraries(biv_adapters PUBLIC simdjson SQLite3::SQLite3)
target_compile_options(biv_adapters PRIVATE -Wall -Wextra -Werror)
target_link_libraries(bivcore PUBLIC biv_adapters)

add_executable(biv src/cli/main.cpp src/cli/args.cpp)
target_link_libraries(biv PRIVATE bivcore biv_adapters)
target_compile_options(biv PRIVATE -Wall -Wextra -Werror)

enable_testing()
add_executable(biv_tests
  tests/test_smoke.cpp
  tests/test_json_writer.cpp
  tests/test_checksums.cpp
  tests/test_ignore.cpp
  tests/test_manifest.cpp
  tests/test_scan.cpp
  tests/test_support.cpp)
target_sources(biv_tests PRIVATE tests/test_tar_writer.cpp)
target_sources(biv_tests PRIVATE tests/test_tar_reader.cpp)
target_sources(biv_tests PRIVATE tests/test_pack.cpp)
target_sources(biv_tests PRIVATE tests/test_open.cpp)
target_sources(biv_tests PRIVATE tests/test_envelope.cpp)
target_sources(biv_tests PRIVATE tests/test_cli.cpp)
target_sources(biv_tests PRIVATE tests/test_adapters_registry.cpp)
target_sources(biv_tests PRIVATE tests/test_adapter_claude_collect.cpp)
target_sources(biv_tests PRIVATE tests/test_adapter_claude_install.cpp)
target_sources(biv_tests PRIVATE tests/test_adapter_codex_collect.cpp)
target_sources(biv_tests PRIVATE tests/test_adapter_codex_install.cpp)
target_sources(biv_tests PRIVATE tests/test_sessions.cpp)
target_sources(biv_tests PRIVATE tests/test_render.cpp)
target_link_libraries(biv_tests PRIVATE bivcore biv_adapters Catch2::Catch2WithMain)
target_compile_options(biv_tests PRIVATE -Wall -Wextra -Werror)
target_compile_definitions(biv_tests PRIVATE
  BIV_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
  BIV_BINARY_PATH="$<TARGET_FILE:biv>")
add_test(NAME biv_tests COMMAND biv_tests)
add_test(NAME open_no_rewrite_gate
  COMMAND ${CMAKE_SOURCE_DIR}/tests/check_open_no_rewrite.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME core_adapter_purity_selftest
  COMMAND python3 ${CMAKE_SOURCE_DIR}/harness/ci/check_core_adapter_purity.py
          --self-test)

if(BIV_ENABLE_FUZZ)
  execute_process(
    COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libclang_rt.fuzzer-x86_64.a
    OUTPUT_VARIABLE BIV_FUZZER_RUNTIME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE BIV_FUZZER_RUNTIME_RESULT)
  if(NOT BIV_FUZZER_RUNTIME_RESULT EQUAL 0 OR NOT EXISTS "${BIV_FUZZER_RUNTIME}")
    message(FATAL_ERROR
      "BIV_ENABLE_FUZZ requires libclang_rt.fuzzer-x86_64.a from ${CMAKE_CXX_COMPILER}")
  endif()
  find_program(BIV_OBJCOPY NAMES objcopy llvm-objcopy REQUIRED)

  set(BIV_PATCHED_FUZZER "${CMAKE_CURRENT_BINARY_DIR}/patched_fuzzer.a")
  set(BIV_FUZZER_ALLOCATOR_SYMBOLS
    _ZdaPv
    _ZdaPvm
    _ZdaPvSt11align_val_t
    _ZdaPvmSt11align_val_t
    _ZdlPv
    _ZdlPvm
    _ZdlPvSt11align_val_t
    _ZdlPvmSt11align_val_t
    _Znam
    _Znwm
    _ZnamSt11align_val_t
    _ZnwmSt11align_val_t)
  set(BIV_FUZZER_LOCALIZE_COMMANDS)
  foreach(symbol IN LISTS BIV_FUZZER_ALLOCATOR_SYMBOLS)
    list(APPEND BIV_FUZZER_LOCALIZE_COMMANDS
      COMMAND "${BIV_OBJCOPY}" "--localize-symbol=${symbol}" "${BIV_PATCHED_FUZZER}")
  endforeach()

  # clang 22.1.6 on this distro ships a libFuzzer archive with weak exported
  # allocator symbols from its private C++ runtime. Localizing them preserves
  # ASan/UBSan while preventing libFuzzer from satisfying product delete[] refs.
  # REMOVE-WHEN: re-test unpatched libFuzzer at the next clang toolchain bump.
  add_custom_command(
    OUTPUT "${BIV_PATCHED_FUZZER}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${BIV_FUZZER_RUNTIME}" "${BIV_PATCHED_FUZZER}"
    ${BIV_FUZZER_LOCALIZE_COMMANDS}
    DEPENDS "${BIV_FUZZER_RUNTIME}"
    COMMENT "Patching clang libFuzzer allocator symbols for ASan-compatible fuzzing"
    VERBATIM)
  add_custom_target(biv_patched_fuzzer_runtime DEPENDS "${BIV_PATCHED_FUZZER}")

  add_executable(fuzz_manifest_json fuzz/fuzz_manifest_json.cc)
  add_dependencies(fuzz_manifest_json biv_patched_fuzzer_runtime)
  target_link_libraries(fuzz_manifest_json PRIVATE bivcore "${BIV_PATCHED_FUZZER}")
  target_compile_options(fuzz_manifest_json PRIVATE
    -fsanitize=address,undefined -fsanitize=fuzzer-no-link -fno-omit-frame-pointer)
  target_link_options(fuzz_manifest_json PRIVATE -fsanitize=address,undefined)

  add_executable(fuzz_tar_member fuzz/fuzz_tar_member.cc)
  add_dependencies(fuzz_tar_member biv_patched_fuzzer_runtime)
  target_link_libraries(fuzz_tar_member PRIVATE bivcore "${BIV_PATCHED_FUZZER}")
  target_compile_options(fuzz_tar_member PRIVATE
    -fsanitize=address,undefined -fsanitize=fuzzer-no-link -fno-omit-frame-pointer)
  target_link_options(fuzz_tar_member PRIVATE -fsanitize=address,undefined)
endif()

add_subdirectory(harness)
