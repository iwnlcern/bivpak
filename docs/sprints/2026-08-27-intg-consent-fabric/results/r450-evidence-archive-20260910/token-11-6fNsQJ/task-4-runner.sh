#!/usr/bin/env bash
set -u

STOP() {
  printf 'STOP-task-4\n' >&2
  exit 1
}

PLAN_ARTIFACT=${1-}
EVID_ARG=${2-}
[ -n "$PLAN_ARTIFACT" ] || STOP
[ -n "$EVID_ARG" ] || STOP
plan_hash_rc=0
plan_hash_line=$(shasum -a 256 "$PLAN_ARTIFACT") || plan_hash_rc=$?
[ "$plan_hash_rc" -eq 0 ] || STOP
[ "${plan_hash_line%% *}" = 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747 ] || STOP
EVID=$(cd "$EVID_ARG" && pwd -P) || STOP
[ "$EVID" = /private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-6fNsQJ ] || STOP
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
MAIN_REPO=/Users/jack/Programming/bivpak
cd "$WORKTREE" || STOP

bind_rc=0
(cd "$EVID" && shasum -a 256 -c task-4-preexec-binding-sha256.txt > task-4-binding-verify.txt 2>&1) || bind_rc=$?
[ "$bind_rc" -eq 0 ] && [ -s "$EVID/task-4-binding-verify.txt" ] || STOP

[ -s "$EVID/C.txt" ] || STOP
C_READ_RC=0
C=$(cat "$EVID/C.txt") || C_READ_RC=$?
[ "$C_READ_RC" -eq 0 ] && [ -n "$C" ] || STOP
e=0; git cat-file -e "${C}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP
[ "$(git rev-parse HEAD)" = "$C" ] || STOP
[ ! -e "$EVID/C" ] || STOP
mkdir_rc=0
mkdir "$EVID/C" || mkdir_rc=$?
[ "$mkdir_rc" -eq 0 ] && [ -d "$EVID/C" ] || STOP

[ -s "$EVID/observer-unset-names.txt" ] || STOP
observer_read_rc=0
{ OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"; } || observer_read_rc=$?
[ "$observer_read_rc" -eq 0 ] || STOP

run_macos_binary() {
  binary=$1
  x=0
  "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/C/$binary-macos.xml" 2> "$EVID/C/$binary-macos.stderr" || x=$?
  printf '%s\n' "$x" > "$EVID/C/$binary-macos.rc" || STOP
  [ -s "$EVID/C/$binary-macos.xml" ] && [ -f "$EVID/C/$binary-macos.stderr" ] || STOP
}
run_macos_binary biv_subprocess_tests
run_macos_binary biv_repo_git_tests
run_macos_binary biv_repo_engine_tests
run_macos_binary biv_tests
run_macos_binary biv_probe_tests

mac_hash_rc=0
shasum -a 256 "$EVID"/C/*-macos.xml > "$EVID/C/xml-sha256-macos.txt" || mac_hash_rc=$?
[ "$mac_hash_rc" -eq 0 ] && [ -s "$EVID/C/xml-sha256-macos.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" macos "$EVID"/C/biv_subprocess_tests-macos.xml "$EVID"/C/biv_repo_git_tests-macos.xml "$EVID"/C/biv_repo_engine_tests-macos.xml "$EVID"/C/biv_tests-macos.xml "$EVID"/C/biv_probe_tests-macos.xml > "$EVID/C/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/C/tuples-macos.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/C/biv_tests-macos.xml" green > "$EVID/C/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/C/witness-green-macos.verdict" ] || STOP

r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/C/ctest-macos-C.log" 2>&1 || r=$?
printf 'ctest_macos_C_rc=%s\n' "$r" > "$EVID/C/ctest-macos-C.rc" || STOP
[ "$r" -ne 0 ] && [ -s "$EVID/C/ctest-macos-C.log" ] || STOP
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/C/ctest-macos-C.log" > "$EVID/C/ctest-macos-C.failed" || f=$?; [ "$f" -le 1 ] || STOP
[ -s "$EVID/C/ctest-macos-C.failed" ] || STOP
s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/C/ctest-macos-C.failed" > "$EVID/C/ctest-macos-C.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP
[ -s "$EVID/C/ctest-macos-C.failed-names" ] || STOP
d=0; diff "$EVID/ctest-failed.expected" "$EVID/C/ctest-macos-C.failed-names" > "$EVID/C/ctest-macos-C.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; cause_count=$(grep -c -F 'claude_adapter_file' "$EVID/C/ctest-macos-C.log") || g=$?; [ "$g" -le 1 ] && [ "$cause_count" -ge 1 ] || STOP

mac_cat_rc=0
cat -- "$EVID/C/ctest-macos-C.log" "$EVID"/C/*-macos.stderr > "$EVID/C/all-logs-C-macos.txt" || mac_cat_rc=$?
[ "$mac_cat_rc" -eq 0 ] && [ -f "$EVID/C/all-logs-C-macos.txt" ] || STOP
mac_grep_rc=0
mac_secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/C/all-logs-C-macos.txt") || mac_grep_rc=$?
[ "$mac_grep_rc" -le 1 ] && [ "$mac_secret_hits" -eq 0 ] || STOP
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$mac_cat_rc" "$mac_grep_rc" "$mac_secret_hits" > "$EVID/C/token-scan-macos.txt" || STOP

mac_identity_fn() {
  printf 'run_id=C-macos-%s\nplatform=macos\nC=%s\n' "$C" "$C" || return 61
  sw_vers || return 62
  uname -m || return 63
  printf '%s\n' 'observer_unset_names:' || return 64
  cat "$EVID/observer-unset-names.txt" || return 65
  printf '%s\n' 'observer_host_presence_names_only:' || return 66
  cat "$EVID/observer-host-presence.txt" || return 67
  cat "$EVID/observer-present-count.txt" || return 68
  cat "$EVID/C/tuples-macos.txt" || return 69
  cat "$EVID/C/xml-sha256-macos.txt" || return 70
  cat "$EVID/C/token-scan-macos.txt" || return 71
}
mac_identity_rc=0
mac_identity_fn > "$EVID/C/run-identity-macos.txt" || mac_identity_rc=$?
[ "$mac_identity_rc" -eq 0 ] && [ -s "$EVID/C/run-identity-macos.txt" ] || STOP

LLVM_DIR_RC=0
LLVM_DIR=$(mktemp -d "$EVID/llvm22-assets-C.XXXXXX") || LLVM_DIR_RC=$?
[ "$LLVM_DIR_RC" -eq 0 ] && [ -d "$LLVM_DIR" ] || STOP
LLVM_DIR=$(cd "$LLVM_DIR" && pwd -P) || STOP
phase_h_fn() {
  cp "$EVID/llvm-manifest.txt" "$LLVM_DIR/MANIFEST" || return 51
  while read -r _ package asset; do
    printf 'mirror asset package=%s asset=%s\n' "$package" "$asset"
    gh release download toolchain-mirror-clang-tidy-22-immutable-v1 --repo iwnlcern/bivpak --pattern "$asset" --dir "$LLVM_DIR" || return 52
  done < "$LLVM_DIR/MANIFEST"
  awk '{ print $1 "  " $3 }' "$LLVM_DIR/MANIFEST" > "$LLVM_DIR/SHA256SUMS" || return 53
  (cd "$LLVM_DIR" && sha256sum --check --strict SHA256SUMS) || return 54
}
phase_h=0
phase_h_fn > "$EVID/C/phase-H.log" 2>&1 || phase_h=$?
printf 'phase_H_transport_rc=%s\n' "$phase_h" > "$EVID/C/phase-H.rc" || STOP
[ "$phase_h" -eq 0 ] && [ -s "$EVID/C/phase-H.log" ] || STOP

linux_outer_rc=0
docker run --rm --platform linux/amd64 --init \
  -v "$LLVM_DIR:/llvm-mirror:ro" \
  -v "$MAIN_REPO:/repo-ro:ro" \
  -v "$EVID:/evidence" \
  ubuntu:24.04 bash /evidence/task-4-linux-container.sh "$C" \
  > "$EVID/C/linux-container.log" 2>&1 || linux_outer_rc=$?
printf '%s\n' "$linux_outer_rc" > "$EVID/C/linux-container.rc" || STOP
[ "$linux_outer_rc" -eq 0 ] && [ -s "$EVID/C/linux-container.log" ] || STOP

for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
  [ -s "$EVID/C/$binary-linux.xml" ] || STOP
done
for required_file in linux-ledger.txt linux-suite-ledger.txt linux-observer-name-proof.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc container-copy-out.rc ctest-linux-C.log ctest-linux-C.rc; do
  [ -s "$EVID/C/$required_file" ] || STOP
done
[ "$(cat "$EVID/C/container-payload.rc")" = container_payload_rc=0 ] || STOP
[ "$(cat "$EVID/C/container-copy-out.rc")" = 'copy_out_rc=0 payload_receipt_rc=0' ] || STOP
for expected in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do
  grep -F -x -- "$expected" "$EVID/C/linux-ledger.txt" >/dev/null || STOP
done
for expected in nofile_hard_read_rc=0 nofile_raise_rc=0 nofile_soft_read_rc=0 nofile_soft_equals_hard_rc=0 nofile_receipt_write_rc=0 venv_rc=0 requirements_rc=0 configure_rc=0 build_rc=0 observer_name_proof_create_rc=0 observer_name_input_nonempty_rc=0 observer_name_present_rc=0 observer_name_proof_write_rc=0 observer_name_proof_nonempty_rc=0 ctest_C_log_nonempty_rc=0 ctest_C_receipt_write_rc=0 'suite_aggregate_rc=0 ledger_write_failed=0'; do
  grep -F -x -- "$expected" "$EVID/C/linux-suite-ledger.txt" >/dev/null || STOP
done

linux_cat_rc=0
cat -- "$EVID/C/phase-H.log" "$EVID/C/linux-container.log" "$EVID/C/phase-R-base.log" "$EVID/C/phase-R-assets.log" "$EVID/C/phase-T-transition.log" "$EVID/C/phase-S-suite.log" "$EVID/C/linux-venv.log" "$EVID/C/linux-requirements.log" "$EVID/C/linux-configure.log" "$EVID/C/linux-build.log" "$EVID/C/ctest-linux-C.log" "$EVID"/C/*-linux.stderr > "$EVID/C/all-logs-C-linux.txt" || linux_cat_rc=$?
[ "$linux_cat_rc" -eq 0 ] && [ -f "$EVID/C/all-logs-C-linux.txt" ] || STOP
linux_grep_rc=0
linux_secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/C/all-logs-C-linux.txt") || linux_grep_rc=$?
[ "$linux_grep_rc" -le 1 ] && [ "$linux_secret_hits" -eq 0 ] || STOP
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$linux_cat_rc" "$linux_grep_rc" "$linux_secret_hits" > "$EVID/C/token-scan-linux.txt" || STOP

linux_hash_rc=0
shasum -a 256 "$EVID"/C/*-linux.xml > "$EVID/C/xml-sha256-linux.txt" || linux_hash_rc=$?
[ "$linux_hash_rc" -eq 0 ] && [ -s "$EVID/C/xml-sha256-linux.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" linux "$EVID"/C/biv_subprocess_tests-linux.xml "$EVID"/C/biv_repo_git_tests-linux.xml "$EVID"/C/biv_repo_engine_tests-linux.xml "$EVID"/C/biv_tests-linux.xml "$EVID"/C/biv_probe_tests-linux.xml > "$EVID/C/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/C/tuples-linux.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/C/biv_tests-linux.xml" green > "$EVID/C/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/C/witness-green-linux.verdict" ] || STOP

ctest_linux_rc=$(cat "$EVID/C/ctest-linux-C.rc") || STOP
[ -n "$ctest_linux_rc" ] && [ "$ctest_linux_rc" -ne 0 ] || STOP
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/C/ctest-linux-C.log" > "$EVID/C/ctest-linux-C.failed" || f=$?; [ "$f" -le 1 ] || STOP
[ -s "$EVID/C/ctest-linux-C.failed" ] || STOP
s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/C/ctest-linux-C.failed" > "$EVID/C/ctest-linux-C.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/ctest-failed.expected" "$EVID/C/ctest-linux-C.failed-names" > "$EVID/C/ctest-linux-C.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; cause_count=$(grep -c -F 'claude_adapter_file' "$EVID/C/ctest-linux-C.log") || g=$?; [ "$g" -le 1 ] && [ "$cause_count" -ge 1 ] || STOP

linux_skip_b=$(sed -n 's/^biv_tests linux .* skips=\([0-9][0-9]*\)$/\1/p' "$EVID/B-cells.txt") || STOP
linux_skip_c=$(sed -n 's/^expected_skips_observed linux n=\([0-9][0-9]*\) .*/\1/p' "$EVID/C/tuples-linux.txt") || STOP
[ -n "$linux_skip_b" ] && [ "$linux_skip_c" -eq "$linux_skip_b" ] || STOP
printf 'baseline_linux_skips=%s observed_linux_skips=%s\n' "$linux_skip_b" "$linux_skip_c" > "$EVID/C/skips-linux-proof.txt" || STOP
sed 's/$/ absent/' "$EVID/observer-unset-names.txt" > "$EVID/C/linux-observer-name-proof.expected" || STOP
d=0; diff "$EVID/C/linux-observer-name-proof.expected" "$EVID/C/linux-observer-name-proof.txt" > "$EVID/C/linux-observer-name-proof.delta" || d=$?; [ "$d" -eq 0 ] || STOP

linux_identity_fn() {
  printf 'run_id=C-linux-%s\nplatform=ubuntu:24.04 linux/amd64 --init\nC=%s\n' "$C" "$C" || return 81
  cat "$EVID/C/linux-run-head-receipt.txt" || return 82
  cat "$EVID/C/linux-ledger.txt" || return 83
  cat "$EVID/C/linux-suite-ledger.txt" || return 84
  cat "$EVID/C/linux-nofile.txt" || return 85
  cat "$EVID/C/linux-observer-name-proof.txt" || return 86
  cat "$EVID/C/skips-linux-proof.txt" || return 87
  cat "$EVID/C/tuples-linux.txt" || return 88
  cat "$EVID/C/xml-sha256-linux.txt" || return 89
  cat "$EVID/C/token-scan-linux.txt" || return 90
}
linux_identity_rc=0
linux_identity_fn > "$EVID/C/run-identity-linux.txt" || linux_identity_rc=$?
[ "$linux_identity_rc" -eq 0 ] && [ -s "$EVID/C/run-identity-linux.txt" ] || STOP

q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/P/tuples-macos.txt" "$EVID/P/tuples-linux.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" > "$EVID/C/gate-equality.txt" || q=$?
printf 'gate_rc=%s\n' "$q" > "$EVID/C/gate.rc" || STOP
[ "$q" -eq 0 ] && [ -s "$EVID/C/gate-equality.txt" ] || STOP
k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/C/tuples-macos.txt" macos > "$EVID/C/skipset-macos.txt" || k=$?
printf 'skipset_C_macos_rc=%s\n' "$k" > "$EVID/C/skipset-macos.rc" || STOP
[ "$k" -eq 0 ] && [ -s "$EVID/C/skipset-macos.txt" ] || STOP

s=0; git status --porcelain > "$EVID/status-post-C-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-C-obs.txt" ] || STOP
s=0; git -C "$MAIN_REPO" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-C.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-C.txt" > "$EVID/status-main-post-C.delta" || d=$?; [ "$d" -eq 0 ] || STOP
[ "$(git rev-parse HEAD)" = "$C" ] || STOP
printf 'TASK_4_COMPLETE C=%s\n' "$C"
