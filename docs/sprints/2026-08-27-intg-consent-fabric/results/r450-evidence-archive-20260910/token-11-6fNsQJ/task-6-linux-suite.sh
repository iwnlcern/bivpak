#!/usr/bin/env bash
set -u

STOP() {
  printf 'STOP-task-6-linux-suite\n' >&2
  exit 1
}

REPO_ROOT=${1-}
OUT=${2-}
[ "$REPO_ROOT" = /work/repo ] || STOP
[ "$OUT" = /work/out ] || STOP
cd "$REPO_ROOT" || STOP
[ -d "$OUT" ] && [ -w "$OUT" ] || STOP
SUITE_LEDGER="$OUT/linux-suite-ledger.txt"
ledger_create_rc=0
: > "$SUITE_LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$SUITE_LEDGER" ] || STOP
ledger_write_failed=0

record_status() {
  status_name=$1
  status_value=$2
  printf '%s=%s\n' "$status_name" "$status_value" >> "$SUITE_LEDGER" || ledger_write_failed=1
}

run_binary() {
  binary=$1
  binary_rc=0
  "./build/ci/$binary" -r xml > "$OUT/$binary-linux.xml" 2> "$OUT/$binary-linux.stderr" || binary_rc=$?
  record_status "${binary}_producer_rc" "$binary_rc"
  binary_xml_nonempty_rc=1
  [ -s "$OUT/$binary-linux.xml" ] && binary_xml_nonempty_rc=0
  record_status "${binary}_xml_nonempty_rc" "$binary_xml_nonempty_rc"
}

hard_limit_rc=0
HARD_LIMIT=$(ulimit -Hn) || hard_limit_rc=$?
record_status nofile_hard_read_rc "$hard_limit_rc"
nofile_raise_rc=125
if [ "$hard_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ]; then
  nofile_raise_rc=0
  ulimit -Sn "$HARD_LIMIT" || nofile_raise_rc=$?
fi
record_status nofile_raise_rc "$nofile_raise_rc"
soft_limit_rc=0
SOFT_LIMIT=$(ulimit -Sn) || soft_limit_rc=$?
record_status nofile_soft_read_rc "$soft_limit_rc"
nofile_equal_rc=1
if [ "$hard_limit_rc" -eq 0 ] && [ "$soft_limit_rc" -eq 0 ] && [ -n "$HARD_LIMIT" ] && [ "$SOFT_LIMIT" = "$HARD_LIMIT" ]; then
  nofile_equal_rc=0
fi
record_status nofile_soft_equals_hard_rc "$nofile_equal_rc"
nofile_receipt_rc=0
printf 'soft=%s hard=%s\n' "${SOFT_LIMIT-UNREADABLE}" "${HARD_LIMIT-UNREADABLE}" > "$OUT/linux-nofile.txt" || nofile_receipt_rc=$?
record_status nofile_receipt_write_rc "$nofile_receipt_rc"

venv_rc=0
python3 -m venv .venv-harness > "$OUT/linux-venv.log" 2>&1 || venv_rc=$?
record_status venv_rc "$venv_rc"
requirements_rc=0
.venv-harness/bin/python -m pip install -r harness/requirements.lock > "$OUT/linux-requirements.log" 2>&1 || requirements_rc=$?
record_status requirements_rc "$requirements_rc"
configure_rc=0
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON > "$OUT/linux-configure.log" 2>&1 || configure_rc=$?
record_status configure_rc "$configure_rc"
build_rc=0
cmake --build --preset ci > "$OUT/linux-build.log" 2>&1 || build_rc=$?
record_status build_rc "$build_rc"

name_proof_create_rc=0
: > "$OUT/linux-observer-name-proof.txt" || name_proof_create_rc=$?
record_status observer_name_proof_create_rc "$name_proof_create_rc"
observer_input_rc=0
[ -s "$REPO_ROOT/observer-unset-names.txt" ] || observer_input_rc=$?
record_status observer_name_input_nonempty_rc "$observer_input_rc"
observer_name_present_rc=0
observer_name_proof_write_rc=0
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ]; then
  while read -r observer_name; do
    if [ -z "$observer_name" ]; then
      observer_name_present_rc=1
      continue
    fi
    if printenv "$observer_name" >/dev/null; then
      printf '%s present\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
      observer_name_present_rc=1
    else
      printf '%s absent\n' "$observer_name" >> "$OUT/linux-observer-name-proof.txt" || observer_name_proof_write_rc=$?
    fi
  done < "$REPO_ROOT/observer-unset-names.txt"
fi
record_status observer_name_present_rc "$observer_name_present_rc"
record_status observer_name_proof_write_rc "$observer_name_proof_write_rc"
observer_name_proof_nonempty_rc=1
[ -s "$OUT/linux-observer-name-proof.txt" ] && observer_name_proof_nonempty_rc=0
record_status observer_name_proof_nonempty_rc "$observer_name_proof_nonempty_rc"

measurement_missing=0
if [ "$name_proof_create_rc" -eq 0 ] && [ "$observer_input_rc" -eq 0 ] && [ "$observer_name_present_rc" -eq 0 ] && [ "$observer_name_proof_write_rc" -eq 0 ] && [ "$observer_name_proof_nonempty_rc" -eq 0 ]; then
  run_binary biv_subprocess_tests
  run_binary biv_repo_git_tests
  run_binary biv_repo_engine_tests
  run_binary biv_tests
  run_binary biv_probe_tests

  ctest_rc=0
  ctest --preset ci --output-junit "$OUT/ctest-linux-H.junit.xml" --output-on-failure > "$OUT/ctest-linux-H.log" 2>&1 || ctest_rc=$?
  record_status ctest_H_producer_rc "$ctest_rc"
  ctest_log_nonempty_rc=1
  [ -s "$OUT/ctest-linux-H.log" ] && ctest_log_nonempty_rc=0
  record_status ctest_H_log_nonempty_rc "$ctest_log_nonempty_rc"
  ctest_receipt_rc=0
  printf '%s\n' "$ctest_rc" > "$OUT/ctest-linux-H.rc" || ctest_receipt_rc=$?
  record_status ctest_H_receipt_write_rc "$ctest_receipt_rc"
else
  for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
    record_status "${binary}_producer_rc" 125
    record_status "${binary}_xml_nonempty_rc" 1
  done
  record_status ctest_H_producer_rc 125
  record_status ctest_H_log_nonempty_rc 1
  record_status ctest_H_receipt_write_rc 125
  ctest_rc=125
  ctest_log_nonempty_rc=1
  ctest_receipt_rc=125
  measurement_missing=1
fi

suite_aggregate_rc=0
for required_rc in \
  "$hard_limit_rc" \
  "$nofile_raise_rc" \
  "$soft_limit_rc" \
  "$nofile_equal_rc" \
  "$nofile_receipt_rc" \
  "$venv_rc" \
  "$requirements_rc" \
  "$configure_rc" \
  "$build_rc" \
  "$name_proof_create_rc" \
  "$observer_input_rc" \
  "$observer_name_present_rc" \
  "$observer_name_proof_write_rc" \
  "$observer_name_proof_nonempty_rc" \
  "$measurement_missing" \
  "$ctest_rc" \
  "$ctest_log_nonempty_rc" \
  "$ctest_receipt_rc"; do
  [ "$required_rc" -eq 0 ] || suite_aggregate_rc=1
done
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
  binary_xml_nonempty_rc=1
  [ -s "$OUT/$binary-linux.xml" ] && binary_xml_nonempty_rc=0
  [ "$binary_xml_nonempty_rc" -eq 0 ] || suite_aggregate_rc=1
done
[ "$ledger_write_failed" -eq 0 ] || suite_aggregate_rc=1
aggregate_record_rc=0
printf 'suite_aggregate_rc=%s ledger_write_failed=%s\n' "$suite_aggregate_rc" "$ledger_write_failed" >> "$SUITE_LEDGER" || aggregate_record_rc=$?
[ "$aggregate_record_rc" -eq 0 ] || exit 1
exit "$suite_aggregate_rc"
