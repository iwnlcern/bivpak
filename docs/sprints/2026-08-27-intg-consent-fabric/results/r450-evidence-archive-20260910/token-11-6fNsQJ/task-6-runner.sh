#!/usr/bin/env bash
set -u

STOP() {
  printf 'STOP-task-6\n' >&2
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
(cd "$EVID" && shasum -a 256 -c task-6-preexec-binding-sha256.txt > task-6-binding-verify.txt 2>&1) || bind_rc=$?
[ "$bind_rc" -eq 0 ] && [ -s "$EVID/task-6-binding-verify.txt" ] || STOP

[ -s "$EVID/H.txt" ] || STOP
H_READ_RC=0
H=$(cat "$EVID/H.txt") || H_READ_RC=$?
[ "$H_READ_RC" -eq 0 ] && [ -n "$H" ] || STOP
e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP
[ "$(git rev-parse HEAD)" = "$H" ] || STOP
[ ! -e "$EVID/H" ] || STOP
mkdir_rc=0
mkdir "$EVID/H" || mkdir_rc=$?
[ "$mkdir_rc" -eq 0 ] && [ -d "$EVID/H" ] || STOP

[ -s "$EVID/observer-unset-names.txt" ] || STOP
observer_read_rc=0
{ OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"; } || observer_read_rc=$?
[ "$observer_read_rc" -eq 0 ] || STOP

b=0
cmake --build --preset ci-macos > "$EVID/H/build-H.log" 2>&1 || b=$?
[ "$b" -eq 0 ] || STOP

rc1=0
ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-as-is.log" 2>&1 || rc1=$?
rc2=0
"${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/H/discriminator-unset.log" 2>&1 || rc2=$?
present_count=$(cut -d= -f2 "$EVID/observer-present-count.txt") || STOP
iff=FAIL
hygiene=FAIL
[ "$rc2" -eq 0 ] && hygiene=PASS
if { [ "$present_count" -gt 0 ] && [ "$rc1" -ne 0 ]; } || { [ "$present_count" -eq 0 ] && [ "$rc1" -eq 0 ]; }; then
  iff=PASS
fi
printf 'rc1=%s rc2=%s present_count=%s iff=%s hygiene=%s\n' "$rc1" "$rc2" "$present_count" "$iff" "$hygiene" > "$EVID/H/discriminator-predicate.txt" || STOP
[ "$iff" = PASS ] && [ "$hygiene" = PASS ] || STOP

r=0
"${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/H/ctest-macos-H.log" 2>&1 || r=$?
printf 'ctest_macos_H_rc=%s\n' "$r" > "$EVID/H/ctest-macos-H.rc" || STOP
[ "$r" -eq 0 ] || STOP

run_macos_binary() {
  binary=$1
  x=0
  "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/H/$binary-macos.xml" 2> "$EVID/H/$binary-macos.stderr" || x=$?
  printf '%s\n' "$x" > "$EVID/H/$binary-macos.rc" || STOP
  [ -s "$EVID/H/$binary-macos.xml" ] && [ -f "$EVID/H/$binary-macos.stderr" ] || STOP
}
run_macos_binary biv_subprocess_tests
run_macos_binary biv_repo_git_tests
run_macos_binary biv_repo_engine_tests
run_macos_binary biv_tests
run_macos_binary biv_probe_tests

mac_hash_rc=0
shasum -a 256 "$EVID"/H/*-macos.xml > "$EVID/H/xml-sha256-macos.txt" || mac_hash_rc=$?
[ "$mac_hash_rc" -eq 0 ] && [ -s "$EVID/H/xml-sha256-macos.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" macos "$EVID"/H/biv_subprocess_tests-macos.xml "$EVID"/H/biv_repo_git_tests-macos.xml "$EVID"/H/biv_repo_engine_tests-macos.xml "$EVID"/H/biv_tests-macos.xml "$EVID"/H/biv_probe_tests-macos.xml > "$EVID/H/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-macos.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/H/biv_tests-macos.xml" green > "$EVID/H/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/witness-green-macos.verdict" ] || STOP

scout_rc=0
"${OBS_ENV[@]}" ctest --preset ci-macos --output-on-failure > "$EVID/H/scout-macos.log" 2>&1 || scout_rc=$?
printf '%s\n' "$scout_rc" > "$EVID/H/scout-macos.rc" || STOP
[ "$scout_rc" -ne 0 ] && [ -s "$EVID/H/scout-macos.log" ] || STOP
scout_failed_rc=0
grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/H/scout-macos.log" > "$EVID/H/scout-macos.failed" || scout_failed_rc=$?
[ "$scout_failed_rc" -eq 0 ] && [ -s "$EVID/H/scout-macos.failed" ] || STOP
sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/H/scout-macos.failed" > "$EVID/H/scout-macos.failed-names" || STOP
printf 'safety-hardening\n' > "$EVID/H/scout-macos.expected" || STOP
d=0; diff "$EVID/H/scout-macos.expected" "$EVID/H/scout-macos.failed-names" > "$EVID/H/scout-macos.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP

mac_cat_rc=0
cat -- "$EVID"/H/*.log "$EVID"/H/*.stderr > "$EVID/H/all-logs-H-macos.txt" || mac_cat_rc=$?
[ "$mac_cat_rc" -eq 0 ] && [ -f "$EVID/H/all-logs-H-macos.txt" ] || STOP
mac_grep_rc=0
mac_secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/H/all-logs-H-macos.txt") || mac_grep_rc=$?
[ "$mac_grep_rc" -le 1 ] && [ "$mac_secret_hits" -eq 0 ] || STOP
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$mac_cat_rc" "$mac_grep_rc" "$mac_secret_hits" > "$EVID/H/token-scan-macos.txt" || STOP

mac_identity_fn() {
  printf 'run_id=H-macos-%s\nplatform=macos\nH=%s\n' "$H" "$H" || return 61
  sw_vers || return 62
  uname -m || return 63
  printf '%s\n' 'observer_unset_names:' || return 64
  cat "$EVID/observer-unset-names.txt" || return 65
  printf '%s\n' 'observer_host_presence_names_only:' || return 66
  cat "$EVID/observer-host-presence.txt" || return 67
  cat "$EVID/observer-present-count.txt" || return 68
  cat "$EVID/H/tuples-macos.txt" || return 69
  cat "$EVID/H/xml-sha256-macos.txt" || return 70
  cat "$EVID/H/token-scan-macos.txt" || return 71
}
mac_identity_rc=0
mac_identity_fn > "$EVID/H/run-identity-macos.txt" || mac_identity_rc=$?
[ "$mac_identity_rc" -eq 0 ] && [ -s "$EVID/H/run-identity-macos.txt" ] || STOP

LLVM_DIR_RC=0
LLVM_DIR=$(mktemp -d "$EVID/llvm22-assets-H.XXXXXX") || LLVM_DIR_RC=$?
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
phase_h_fn > "$EVID/H/phase-H.log" 2>&1 || phase_h=$?
printf 'phase_H_transport_rc=%s\n' "$phase_h" > "$EVID/H/phase-H.rc" || STOP
[ "$phase_h" -eq 0 ] && [ -s "$EVID/H/phase-H.log" ] || STOP

linux_outer_rc=0
docker run --rm --platform linux/amd64 --init \
  -v "$LLVM_DIR:/llvm-mirror:ro" \
  -v "$MAIN_REPO:/repo-ro:ro" \
  -v "$EVID:/evidence" \
  ubuntu:24.04 bash /evidence/task-6-linux-container.sh "$H" \
  > "$EVID/H/linux-container.log" 2>&1 || linux_outer_rc=$?
printf '%s\n' "$linux_outer_rc" > "$EVID/H/linux-container.rc" || STOP
[ "$linux_outer_rc" -eq 0 ] && [ -s "$EVID/H/linux-container.log" ] || STOP

for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
  [ -s "$EVID/H/$binary-linux.xml" ] || STOP
done
for required_file in linux-ledger.txt linux-suite-ledger.txt linux-observer-name-proof.txt linux-nofile.txt linux-run-head-receipt.txt container-payload.rc container-copy-out.rc ctest-linux-H.log ctest-linux-H.rc; do
  [ -s "$EVID/H/$required_file" ] || STOP
done
[ "$(cat "$EVID/H/container-payload.rc")" = container_payload_rc=0 ] || STOP
[ "$(cat "$EVID/H/container-copy-out.rc")" = 'copy_out_rc=0 payload_receipt_rc=0' ] || STOP
for expected in phase_R_base_provision_rc=0 phase_R_asset_provision_rc=0 phase_T_transition_fixture_rc=0 phase_S_suite_rc=0; do
  grep -F -x -- "$expected" "$EVID/H/linux-ledger.txt" >/dev/null || STOP
done
for expected in nofile_hard_read_rc=0 nofile_raise_rc=0 nofile_soft_read_rc=0 nofile_soft_equals_hard_rc=0 nofile_receipt_write_rc=0 venv_rc=0 requirements_rc=0 configure_rc=0 build_rc=0 observer_name_proof_create_rc=0 observer_name_input_nonempty_rc=0 observer_name_present_rc=0 observer_name_proof_write_rc=0 observer_name_proof_nonempty_rc=0 ctest_H_producer_rc=0 ctest_H_log_nonempty_rc=0 ctest_H_receipt_write_rc=0 'suite_aggregate_rc=0 ledger_write_failed=0'; do
  grep -F -x -- "$expected" "$EVID/H/linux-suite-ledger.txt" >/dev/null || STOP
done

linux_cat_rc=0
cat -- "$EVID/H/phase-H.log" "$EVID/H/linux-container.log" "$EVID/H/phase-R-base.log" "$EVID/H/phase-R-assets.log" "$EVID/H/phase-T-transition.log" "$EVID/H/phase-S-suite.log" "$EVID/H/linux-venv.log" "$EVID/H/linux-requirements.log" "$EVID/H/linux-configure.log" "$EVID/H/linux-build.log" "$EVID/H/ctest-linux-H.log" "$EVID"/H/*-linux.stderr > "$EVID/H/all-logs-H-linux.txt" || linux_cat_rc=$?
[ "$linux_cat_rc" -eq 0 ] && [ -f "$EVID/H/all-logs-H-linux.txt" ] || STOP
linux_grep_rc=0
linux_secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/H/all-logs-H-linux.txt") || linux_grep_rc=$?
[ "$linux_grep_rc" -le 1 ] && [ "$linux_secret_hits" -eq 0 ] || STOP
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$linux_cat_rc" "$linux_grep_rc" "$linux_secret_hits" > "$EVID/H/token-scan-linux.txt" || STOP

linux_hash_rc=0
shasum -a 256 "$EVID"/H/*-linux.xml > "$EVID/H/xml-sha256-linux.txt" || linux_hash_rc=$?
[ "$linux_hash_rc" -eq 0 ] && [ -s "$EVID/H/xml-sha256-linux.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" linux "$EVID"/H/biv_subprocess_tests-linux.xml "$EVID"/H/biv_repo_git_tests-linux.xml "$EVID"/H/biv_repo_engine_tests-linux.xml "$EVID"/H/biv_tests-linux.xml "$EVID"/H/biv_probe_tests-linux.xml > "$EVID/H/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/H/tuples-linux.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/H/biv_tests-linux.xml" green > "$EVID/H/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/H/witness-green-linux.verdict" ] || STOP

ctest_linux_rc=$(cat "$EVID/H/ctest-linux-H.rc") || STOP
[ -n "$ctest_linux_rc" ] && [ "$ctest_linux_rc" -eq 0 ] || STOP

linux_skip_b=$(sed -n 's/^biv_tests linux .* skips=\([0-9][0-9]*\)$/\1/p' "$EVID/B-cells.txt") || STOP
linux_skip_c=$(sed -n 's/^expected_skips_observed linux n=\([0-9][0-9]*\) .*/\1/p' "$EVID/H/tuples-linux.txt") || STOP
[ -n "$linux_skip_b" ] && [ "$linux_skip_c" -eq "$linux_skip_b" ] || STOP
printf 'baseline_linux_skips=%s observed_linux_skips=%s\n' "$linux_skip_b" "$linux_skip_c" > "$EVID/H/skips-linux-proof.txt" || STOP
sed 's/$/ absent/' "$EVID/observer-unset-names.txt" > "$EVID/H/linux-observer-name-proof.expected" || STOP
d=0; diff "$EVID/H/linux-observer-name-proof.expected" "$EVID/H/linux-observer-name-proof.txt" > "$EVID/H/linux-observer-name-proof.delta" || d=$?; [ "$d" -eq 0 ] || STOP

linux_identity_fn() {
  printf 'run_id=H-linux-%s\nplatform=ubuntu:24.04 linux/amd64 --init\nH=%s\n' "$H" "$H" || return 81
  cat "$EVID/H/linux-run-head-receipt.txt" || return 82
  cat "$EVID/H/linux-ledger.txt" || return 83
  cat "$EVID/H/linux-suite-ledger.txt" || return 84
  cat "$EVID/H/linux-nofile.txt" || return 85
  cat "$EVID/H/linux-observer-name-proof.txt" || return 86
  cat "$EVID/H/skips-linux-proof.txt" || return 87
  cat "$EVID/H/tuples-linux.txt" || return 88
  cat "$EVID/H/xml-sha256-linux.txt" || return 89
  cat "$EVID/H/token-scan-linux.txt" || return 90
}
linux_identity_rc=0
linux_identity_fn > "$EVID/H/run-identity-linux.txt" || linux_identity_rc=$?
[ "$linux_identity_rc" -eq 0 ] && [ -s "$EVID/H/run-identity-linux.txt" ] || STOP

q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" "$EVID/H/tuples-macos.txt" "$EVID/H/tuples-linux.txt" > "$EVID/H/gate-equality-H.txt" || q=$?
printf 'gate_H_rc=%s\n' "$q" > "$EVID/H/gate-H.rc" || STOP
[ "$q" -eq 0 ] && [ -s "$EVID/H/gate-equality-H.txt" ] || STOP
k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-macos.txt" macos > "$EVID/H/skipset-macos.txt" || k=$?
printf 'skipset_H_macos_rc=%s\n' "$k" > "$EVID/H/skipset-macos.rc" || STOP
[ "$k" -eq 0 ] && [ -s "$EVID/H/skipset-macos.txt" ] || STOP

mkdir -p "$EVID/H/rp" || STOP
m=0
(cd harness && BIVHARNESS_SCHEMA_ROOT="$PWD/../schemas" "${OBS_ENV[@]}" ../.venv-harness/bin/python3 "$EVID/rp_mutants.py" /Users/jack/Programming/bivpak-intg-r450-discover-parity/build/ci-macos/biv "$EVID/H/rp/rp-mutants") > "$EVID/H/rp/rp-mutants.log" 2>&1 || m=$?
printf 'rp_rc=%s\n' "$m" > "$EVID/H/rp/rp.rc" || STOP
[ "$m" -eq 0 ] && [ -s "$EVID/H/rp/rp-mutants.log" ] || STOP
g=0; k=$(grep -c -F 'ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -F "MUTANT HOME: status=fail leak_tags=['HOME']" "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0002-4000-8000-0000000c1a0d' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP
g=0; k=$(grep -c -E '^isolation-leak HOME: .*0d15ea5e-0001-4000-8000-00000000c0de' "$EVID/H/rp/rp-mutants.log") || g=$?; [ "$g" -le 1 ] && [ "$k" -ge 1 ] || STOP
shasum -a 256 "$EVID/H/rp/rp-mutants.log" > "$EVID/H/rp/rp-mutants.log.sha256" || STOP

s=0; git status --porcelain > "$EVID/status-post-H-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-H-obs.txt" ] || STOP
s=0; git -C "$MAIN_REPO" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-H.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-H.txt" > "$EVID/status-main-post-H.delta" || d=$?; [ "$d" -eq 0 ] || STOP
[ "$(git rev-parse HEAD)" = "$H" ] || STOP
printf 'TASK_6_COMPLETE H=%s\n' "$H"
