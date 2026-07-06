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

find_program(BIVHARNESS_CLANG_TIDY clang-tidy)
if(BIVHARNESS_CLANG_TIDY AND EXISTS "${CMAKE_SOURCE_DIR}/src")
  add_test(
    NAME safety-tidy-analyzer
    COMMAND "${BIVHARNESS_PYTHON}" "${BIVHARNESS_SOURCE_DIR}/ci/run_clang_tidy.py"
            --clang-tidy "${BIVHARNESS_CLANG_TIDY}"
            --compile-commands "${CMAKE_BINARY_DIR}/compile_commands.json"
            --source-root "${CMAKE_SOURCE_DIR}")
  set_tests_properties(safety-tidy-analyzer PROPERTIES
    TIMEOUT 240
    LABELS "safety;tidy")
else()
  bivharness_skip_test(safety-tidy-analyzer "clang-tidy unavailable or no project src tree in this build")
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
