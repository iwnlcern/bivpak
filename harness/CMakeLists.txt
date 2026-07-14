cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(bivharness NONE)
  enable_testing()
endif()

set(BIVHARNESS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIVHARNESS_REPORT "${CMAKE_BINARY_DIR}/harness-e2-report.json")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED BIVHARNESS_PYTHON)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.venv-harness/bin/python3")
    set(BIVHARNESS_PYTHON "${CMAKE_SOURCE_DIR}/.venv-harness/bin/python3" CACHE FILEPATH "Python for bivharness")
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../.venv-harness/bin/python3")
    set(BIVHARNESS_PYTHON "${CMAKE_CURRENT_SOURCE_DIR}/../.venv-harness/bin/python3" CACHE FILEPATH "Python for bivharness")
  else()
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(BIVHARNESS_PYTHON "${Python3_EXECUTABLE}" CACHE FILEPATH "Python for bivharness")
  endif()
endif()

function(bivharness_skip_test name reason)
  add_test(NAME "${name}" COMMAND "${CMAKE_COMMAND}" -E echo "SKIP: ${reason}")
  set_tests_properties("${name}" PROPERTIES
    SKIP_REGULAR_EXPRESSION "^SKIP:"
    LABELS "harness-skip")
endfunction()

add_test(
  NAME harness-selftest
  COMMAND "${BIVHARNESS_PYTHON}" -m pytest selftest
  WORKING_DIRECTORY "${BIVHARNESS_SOURCE_DIR}")
set_tests_properties(harness-selftest PROPERTIES
  TIMEOUT 120
  LABELS "harness;selftest")

if(TARGET biv)
  add_test(
    NAME harness-e2
    COMMAND "${BIVHARNESS_PYTHON}" -m bivharness
            --biv "$<TARGET_FILE:biv>"
            --scenarios "${BIVHARNESS_SOURCE_DIR}/scenarios"
            --report "${BIVHARNESS_REPORT}"
    WORKING_DIRECTORY "${BIVHARNESS_SOURCE_DIR}")
  set_tests_properties(harness-e2 PROPERTIES
    TIMEOUT 180
    LABELS "harness;e2"
    ENVIRONMENT "BIVHARNESS_SCHEMA_ROOT=${CMAKE_SOURCE_DIR}/schemas")
else()
  bivharness_skip_test(harness-e2 "no biv target in this CMake build")
endif()

if(TARGET biv_tests)
  add_test(
    NAME safety-build-werror
    COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target biv_tests)
  set_tests_properties(safety-build-werror PROPERTIES
    TIMEOUT 180
    LABELS "safety;build")

  get_target_property(BIVHARNESS_BIV_TESTS_COMPILE_OPTIONS biv_tests COMPILE_OPTIONS)
  get_target_property(BIVHARNESS_BIV_TESTS_LINK_OPTIONS biv_tests LINK_OPTIONS)
  if(NOT BIVHARNESS_BIV_TESTS_COMPILE_OPTIONS)
    set(BIVHARNESS_BIV_TESTS_COMPILE_OPTIONS "")
  endif()
  if(NOT BIVHARNESS_BIV_TESTS_LINK_OPTIONS)
    set(BIVHARNESS_BIV_TESTS_LINK_OPTIONS "")
  endif()
  set(BIVHARNESS_SANITIZER_FLAGS
      "${CMAKE_CXX_FLAGS};${CMAKE_EXE_LINKER_FLAGS};${BIVHARNESS_BIV_TESTS_COMPILE_OPTIONS};${BIVHARNESS_BIV_TESTS_LINK_OPTIONS}")
  if(BIVHARNESS_SANITIZER_FLAGS MATCHES "sanitize")
    add_test(
      NAME safety-asan-ubsan
      COMMAND "$<TARGET_FILE:biv_tests>")
    set_tests_properties(safety-asan-ubsan PROPERTIES
      TIMEOUT 180
      LABELS "safety;sanitizer"
      ENVIRONMENT "ASAN_OPTIONS=halt_on_error=1:abort_on_error=1:detect_leaks=1;UBSAN_OPTIONS=halt_on_error=1:abort_on_error=1:print_stacktrace=1")
  else()
    bivharness_skip_test(safety-asan-ubsan "biv_tests not built with sanitizer flags")
  endif()
else()
  bivharness_skip_test(safety-build-werror "no biv_tests target")
  bivharness_skip_test(safety-asan-ubsan "no biv_tests target")
endif()

option(BIVHARNESS_REQUIRE_CLANG_TIDY "Fail configuration if the pinned clang-tidy is unusable" OFF)
set(BIVHARNESS_CLANG_TIDY_MAJOR 18 CACHE STRING "Required LLVM major version")

function(_tidy_unusable reason)
  if(BIVHARNESS_REQUIRE_CLANG_TIDY)
    message(FATAL_ERROR "safety-tidy-analyzer REQUIRED but unusable: ${reason}")
  endif()
  bivharness_skip_test(safety-tidy-analyzer "${reason}")
  set(_TIDY_OK FALSE PARENT_SCOPE)
endfunction()

set(_TIDY_OK TRUE)
find_program(BIVHARNESS_CLANG_TIDY NAMES "clang-tidy-${BIVHARNESS_CLANG_TIDY_MAJOR}")

if(NOT BIVHARNESS_CLANG_TIDY)
  _tidy_unusable("pinned clang-tidy-${BIVHARNESS_CLANG_TIDY_MAJOR} not found")
elseif(NOT EXISTS "${CMAKE_SOURCE_DIR}/src")
  _tidy_unusable("no project src tree in this build")
else()
  execute_process(
    COMMAND "${BIVHARNESS_CLANG_TIDY}" --version
    OUTPUT_VARIABLE _v
    ERROR_QUIET)
  string(REGEX MATCH "LLVM version ([0-9]+)" _ "${_v}")
  set(_major "${CMAKE_MATCH_1}")
  message(STATUS "clang-tidy: ${BIVHARNESS_CLANG_TIDY} (LLVM major ${_major})")
  if(NOT _major STREQUAL "${BIVHARNESS_CLANG_TIDY_MAJOR}")
    _tidy_unusable("LLVM major ${_major}, required ${BIVHARNESS_CLANG_TIDY_MAJOR}")
  else()
    set(_probe "${CMAKE_CURRENT_BINARY_DIR}/tidy_probe.cpp")
    file(WRITE "${_probe}"
"#include <expected>
#include <string>
#if !defined(_GLIBCXX_RELEASE)
#  error \"BIVPAK: analyzer did NOT resolve libstdc++ (no _GLIBCXX_RELEASE)\"
#endif
#if _GLIBCXX_RELEASE < 13
#  error \"BIVPAK: libstdc++ release < 13 - no <expected>\"
#endif
#define BIV_STR2(x) #x
#define BIV_STR(x) BIV_STR2(x)
#pragma message(\"BIVPAK_TIDY_PAIRING: libstdc++ _GLIBCXX_RELEASE=\" BIV_STR(_GLIBCXX_RELEASE))
std::expected<int,std::string> p(){return 1;}
")
    message(STATUS "clang-tidy probe cmd: ${BIVHARNESS_CLANG_TIDY} "
                   "--checks=-*,misc-unused-alias-decls,clang-diagnostic-* --quiet ${_probe} -- -std=c++23")
    execute_process(
      COMMAND "${BIVHARNESS_CLANG_TIDY}"
              "--checks=-*,misc-unused-alias-decls,clang-diagnostic-*" --quiet "${_probe}"
              -- -std=c++23
      RESULT_VARIABLE _prc
      OUTPUT_VARIABLE _pout
      ERROR_VARIABLE _perr)
    if(NOT _prc EQUAL 0)
      _tidy_unusable("analyzer cannot parse <expected> under C++23, or resolved a non-libstdc++ / pre-13 stdlib (probe rc=${_prc})\n--- clang-tidy STDOUT (diagnostics + pairing marker) ---\n${_pout}\n--- clang-tidy STDERR (summary) ---\n${_perr}")
    else()
      string(REGEX MATCH "BIVPAK_TIDY_PAIRING: libstdc\\+\\+ _GLIBCXX_RELEASE=([0-9]+)"
             _ "${_pout}${_perr}")
      set(BIVHARNESS_TIDY_GLIBCXX "${CMAKE_MATCH_1}")
      if(NOT BIVHARNESS_TIDY_GLIBCXX)
        _tidy_unusable("probe passed but did not REPORT a libstdc++ release - pairing unobservable")
      else()
        message(STATUS "clang-tidy resolved libstdc++ _GLIBCXX_RELEASE=${BIVHARNESS_TIDY_GLIBCXX}")
      endif()
    endif()
  endif()
endif()

if(_TIDY_OK)
  add_test(
    NAME safety-tidy-analyzer
    COMMAND "${BIVHARNESS_PYTHON}" "${BIVHARNESS_SOURCE_DIR}/ci/run_clang_tidy.py"
            --clang-tidy "${BIVHARNESS_CLANG_TIDY}"
            --compile-commands "${CMAKE_BINARY_DIR}/compile_commands.json"
            --source-root "${CMAKE_SOURCE_DIR}")
  set_tests_properties(safety-tidy-analyzer PROPERTIES
    TIMEOUT 240
    LABELS "safety;tidy")
endif()

if(TARGET biv)
  add_test(
    NAME safety-hardening
    COMMAND "${BIVHARNESS_PYTHON}" "${BIVHARNESS_SOURCE_DIR}/ci/check_hardening.py"
            "$<TARGET_FILE:biv>")
  set_tests_properties(safety-hardening PROPERTIES
    TIMEOUT 60
    LABELS "safety;hardening"
    ENVIRONMENT "BIVHARNESS_HARDENING_FLAGS=${CMAKE_CXX_FLAGS} ${CMAKE_EXE_LINKER_FLAGS}")
else()
  bivharness_skip_test(safety-hardening "no biv target")
endif()

if(TARGET fuzz_manifest_json AND TARGET fuzz_tar_member)
  # run_fuzz_smoke.py expands the fixed budget to libFuzzer -runs=100000 -seed=1.
  add_test(
    NAME safety-fuzz-smoke
    COMMAND "${BIVHARNESS_PYTHON}" "${BIVHARNESS_SOURCE_DIR}/ci/run_fuzz_smoke.py"
            --runs 100000
            --seed 1
            --manifest-corpus "${BIVHARNESS_SOURCE_DIR}/fuzz/corpus/manifest"
            --tar-corpus "${BIVHARNESS_SOURCE_DIR}/fuzz/corpus/tar"
            --manifest-target "$<TARGET_FILE:fuzz_manifest_json>"
            --tar-target "$<TARGET_FILE:fuzz_tar_member>")
  set_tests_properties(safety-fuzz-smoke PROPERTIES TIMEOUT 180 LABELS "safety;fuzz")
else()
  bivharness_skip_test(safety-fuzz-smoke "fuzz_manifest_json and fuzz_tar_member targets unavailable")
endif()
