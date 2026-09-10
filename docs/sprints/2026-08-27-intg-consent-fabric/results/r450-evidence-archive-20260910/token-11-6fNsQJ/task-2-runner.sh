#!/usr/bin/env bash
set -u

STOP() {
  printf 'STOP-task-2\n' >&2
  exit 1
}

PLAN_ARTIFACT=${1-}
COUNTGATE_ARTIFACT=${2-}
EVID_ARG=${3-}
[ -n "$PLAN_ARTIFACT" ] || STOP
[ -n "$COUNTGATE_ARTIFACT" ] || STOP
[ -n "$EVID_ARG" ] || STOP

plan_hash_rc=0
plan_hash_line=$(shasum -a 256 "$PLAN_ARTIFACT") || plan_hash_rc=$?
[ "$plan_hash_rc" -eq 0 ] || STOP
plan_hash=${plan_hash_line%% *}
[ "$plan_hash" = 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747 ] || STOP

countgate_hash_rc=0
countgate_hash_line=$(shasum -a 256 "$COUNTGATE_ARTIFACT") || countgate_hash_rc=$?
[ "$countgate_hash_rc" -eq 0 ] || STOP
countgate_hash=${countgate_hash_line%% *}
[ "$countgate_hash" = 652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55 ] || STOP

EVID=$(cd "$EVID_ARG" && pwd -P) || STOP
[ "$EVID" = /private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-evidence-6fNsQJ ] || STOP
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
MAIN_REPO=/Users/jack/Programming/bivpak
BRIEF="$EVID/task-2-plan-slice.md"
SUBSTEP_PATH=docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md

[ -s "$EVID/task-2-preexec-binding-sha256.txt" ] || STOP
bind_rc=0
(cd "$EVID" && shasum -a 256 -c task-2-preexec-binding-sha256.txt > task-2-binding-verify.txt 2>&1) || bind_rc=$?
[ "$bind_rc" -eq 0 ] && [ -s "$EVID/task-2-binding-verify.txt" ] || STOP

brief_hash_rc=0
brief_hash_line=$(shasum -a 256 "$BRIEF") || brief_hash_rc=$?
[ "$brief_hash_rc" -eq 0 ] || STOP
brief_hash=${brief_hash_line%% *}
[ "$brief_hash" = e846f1d47747de5bb805f00bf23fc9a25b920cd7848fc5ae06d018984dbf8afb ] || STOP
slice_rc=0
sed -n '769,778p' "$PLAN_ARTIFACT" > "$EVID/task-2-plan-slice.runtime.md" || slice_rc=$?
[ "$slice_rc" -eq 0 ] && [ -s "$EVID/task-2-plan-slice.runtime.md" ] || STOP
cmp_rc=0
cmp "$EVID/task-2-plan-slice.md" "$EVID/task-2-plan-slice.runtime.md" || cmp_rc=$?
[ "$cmp_rc" -eq 0 ] || STOP
brief_cmp_rc=0
cmp "$BRIEF" "$EVID/task-2-plan-slice.md" || brief_cmp_rc=$?
[ "$brief_cmp_rc" -eq 0 ] || STOP

count_slice_rc=0
sed -n '35,36p' "$COUNTGATE_ARTIFACT" > "$EVID/countgate-task1-step3-4-source.runtime.md" || count_slice_rc=$?
[ "$count_slice_rc" -eq 0 ] && [ -s "$EVID/countgate-task1-step3-4-source.runtime.md" ] || STOP
count_cmp_rc=0
cmp "$EVID/countgate-task1-step3-4-source.md" "$EVID/countgate-task1-step3-4-source.runtime.md" || count_cmp_rc=$?
[ "$count_cmp_rc" -eq 0 ] || STOP

substep_blob_rc=0
substep_blob=$(git -C "$MAIN_REPO" rev-parse "990ba3b:${SUBSTEP_PATH}") || substep_blob_rc=$?
[ "$substep_blob_rc" -eq 0 ] && [ "$substep_blob" = 2363e66b2cc480a74e3df034721bc1afc52f1b44 ] || STOP
substep_show_rc=0
git -C "$MAIN_REPO" show "990ba3b:${SUBSTEP_PATH}" > "$EVID/substep1-task5-step3-source.runtime.full.md" || substep_show_rc=$?
[ "$substep_show_rc" -eq 0 ] && [ -s "$EVID/substep1-task5-step3-source.runtime.full.md" ] || STOP
substep_slice_rc=0
sed -n '757,763p' "$EVID/substep1-task5-step3-source.runtime.full.md" > "$EVID/substep1-task5-step3-source.runtime.md" || substep_slice_rc=$?
[ "$substep_slice_rc" -eq 0 ] && [ -s "$EVID/substep1-task5-step3-source.runtime.md" ] || STOP
substep_cmp_rc=0
cmp "$EVID/substep1-task5-step3-source.md" "$EVID/substep1-task5-step3-source.runtime.md" || substep_cmp_rc=$?
[ "$substep_cmp_rc" -eq 0 ] || STOP

cd "$WORKTREE" || STOP
[ -s "$EVID/P.txt" ] || STOP
[ -s "$EVID/B-cells.txt" ] || STOP
[ -s "$EVID/tuples.py" ] || STOP
[ -s "$EVID/witness.py" ] || STOP
[ -s "$EVID/task-2-entry.py" ] || STOP
P_READ_RC=0
P=$(cat "$EVID/P.txt") || P_READ_RC=$?
P_READ_RECEIPT_RC=0
printf 'P_read_rc=%s\n' "$P_READ_RC" > "$EVID/P-observation-read.rc" || P_READ_RECEIPT_RC=$?
[ "$P_READ_RECEIPT_RC" -eq 0 ] && [ -s "$EVID/P-observation-read.rc" ] || STOP
[ "$P_READ_RC" -eq 0 ] && [ "$P" = 54954281b30cae113f399055fff106963a37a443 ] || STOP
e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP
head_rc=0
HEAD_NOW=$(git rev-parse HEAD) || head_rc=$?
[ "$head_rc" -eq 0 ] && [ "$HEAD_NOW" = "$P" ] || STOP
a=0; git merge-base --is-ancestor bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" || a=$?
[ "$a" -eq 0 ] || STOP
a2=0; git merge-base --is-ancestor b065de1107161bb5df9543c09b50091365338c1c "$P" || a2=$?
[ "$a2" -eq 0 ] || STOP
ancestry_write_rc=0
printf 'P=%s ancestor_bbf297e_rc=%s ancestor_b065de1_rc=%s\n' "$P" "$a" "$a2" > "$EVID/P-ancestry.txt" || ancestry_write_rc=$?
[ "$ancestry_write_rc" -eq 0 ] && [ -s "$EVID/P-ancestry.txt" ] || STOP

[ -s "$EVID/observer-unset-names.txt" ] || STOP
observer_read_rc=0
{ OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"; } || observer_read_rc=$?
observer_receipt_write_rc=0
printf 'observer_env_read_rc=%s\n' "$observer_read_rc" > "$EVID/P-observer-env-read.rc" || observer_receipt_write_rc=$?
[ "$observer_receipt_write_rc" -eq 0 ] && [ -s "$EVID/P-observer-env-read.rc" ] || STOP
[ "$observer_read_rc" -eq 0 ] || STOP
[ ! -e "$EVID/P" ] || STOP
p_dir_rc=0
mkdir "$EVID/P" || p_dir_rc=$?
[ "$p_dir_rc" -eq 0 ] && [ -d "$EVID/P" ] || STOP

run_macos_binary() {
  binary=$1
  x=0
  "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/P/$binary-macos.xml" 2> "$EVID/P/$binary-macos.stderr" || x=$?
  binary_receipt_rc=0
  printf '%s\n' "$x" > "$EVID/P/$binary-macos.rc" || binary_receipt_rc=$?
  [ "$binary_receipt_rc" -eq 0 ] && [ -s "$EVID/P/$binary-macos.rc" ] || STOP
  [ -s "$EVID/P/$binary-macos.xml" ] && [ -f "$EVID/P/$binary-macos.stderr" ] || STOP
}
run_macos_binary biv_subprocess_tests
run_macos_binary biv_repo_git_tests
run_macos_binary biv_repo_engine_tests
run_macos_binary biv_tests
run_macos_binary biv_probe_tests

mac_hash_rc=0
shasum -a 256 "$EVID"/P/*-macos.xml > "$EVID/P/xml-sha256-macos.txt" || mac_hash_rc=$?
[ "$mac_hash_rc" -eq 0 ] && [ -s "$EVID/P/xml-sha256-macos.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" macos "$EVID"/P/biv_subprocess_tests-macos.xml "$EVID"/P/biv_repo_git_tests-macos.xml "$EVID"/P/biv_repo_engine_tests-macos.xml "$EVID"/P/biv_tests-macos.xml "$EVID"/P/biv_probe_tests-macos.xml > "$EVID/P/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-macos.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-macos.xml" green > "$EVID/P/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-macos.verdict" ] || STOP

k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/P/tuples-macos.txt" macos > "$EVID/P/skipset-macos.txt" || k=$?; printf 'skipset_P_macos_rc=%s\n' "$k" > "$EVID/P/skipset-macos.rc"; [ "$k" -eq 0 ] && [ -s "$EVID/P/skipset-macos.txt" ] || STOP

scout_rc=0
"${OBS_ENV[@]}" ctest --preset ci-macos --output-on-failure > "$EVID/P/scout-macos.log" 2>&1 || scout_rc=$?
scout_receipt_rc=0
printf '%s\n' "$scout_rc" > "$EVID/P/scout-macos.rc" || scout_receipt_rc=$?
[ "$scout_receipt_rc" -eq 0 ] && [ -s "$EVID/P/scout-macos.rc" ] || STOP
[ "$scout_rc" -ne 0 ] && [ -s "$EVID/P/scout-macos.log" ] || STOP
scout_failed_rc=0
grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/P/scout-macos.log" > "$EVID/P/scout-macos.failed" || scout_failed_rc=$?
[ "$scout_failed_rc" -eq 0 ] && [ -s "$EVID/P/scout-macos.failed" ] || STOP
scout_names_rc=0
sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/P/scout-macos.failed" > "$EVID/P/scout-macos.failed-names.unsorted" || scout_names_rc=$?
[ "$scout_names_rc" -eq 0 ] && [ -s "$EVID/P/scout-macos.failed-names.unsorted" ] || STOP
scout_sort_rc=0
sort "$EVID/P/scout-macos.failed-names.unsorted" > "$EVID/P/scout-macos.failed-names" || scout_sort_rc=$?
[ "$scout_sort_rc" -eq 0 ] && [ -s "$EVID/P/scout-macos.failed-names" ] || STOP
scout_expected_write_rc=0
printf 'harness-selftest\nsafety-hardening\n' > "$EVID/P/scout-macos.expected" || scout_expected_write_rc=$?
[ "$scout_expected_write_rc" -eq 0 ] && [ -s "$EVID/P/scout-macos.expected" ] || STOP
scout_delta_rc=0
diff "$EVID/P/scout-macos.expected" "$EVID/P/scout-macos.failed-names" > "$EVID/P/scout-macos.failed.delta" || scout_delta_rc=$?
[ "$scout_delta_rc" -eq 0 ] || STOP

for mac_log_input in \
  "$EVID/P/scout-macos.log" \
  "$EVID/P/biv_subprocess_tests-macos.stderr" \
  "$EVID/P/biv_repo_git_tests-macos.stderr" \
  "$EVID/P/biv_repo_engine_tests-macos.stderr" \
  "$EVID/P/biv_tests-macos.stderr" \
  "$EVID/P/biv_probe_tests-macos.stderr"; do
  [ -f "$mac_log_input" ] || STOP
done
c=0; cat -- "$EVID"/P/*.log "$EVID"/P/*.stderr > "$EVID/P/all-logs-P-macos.txt" || c=$?; [ "$c" -eq 0 ] && [ -f "$EVID/P/all-logs-P-macos.txt" ] || STOP
g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/P/all-logs-P-macos.txt") || g=$?; [ "$g" -le 1 ] || STOP
token_scan_macos_write_rc=0
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$c" "$g" "$secret_hits" > "$EVID/P/token-scan-macos.txt" || token_scan_macos_write_rc=$?
[ "$token_scan_macos_write_rc" -eq 0 ] && [ -s "$EVID/P/token-scan-macos.txt" ] || STOP
[ "$secret_hits" -eq 0 ] || STOP

[ -s "$EVID/observer-host-presence.txt" ] || STOP
[ -s "$EVID/observer-present-count.txt" ] || STOP
for mac_identity_input in \
  "$EVID/P-ancestry.txt" \
  "$EVID/observer-unset-names.txt" \
  "$EVID/observer-host-presence.txt" \
  "$EVID/observer-present-count.txt" \
  "$EVID/P/tuples-macos.txt" \
  "$EVID/P/xml-sha256-macos.txt" \
  "$EVID/P/token-scan-macos.txt"; do
  [ -s "$mac_identity_input" ] || STOP
done
mac_identity_fn() {
  printf 'run_id=P-macos-%s\nplatform=macos\nP=%s\n' "$P" "$P" || return 61
  sw_vers || return 62
  uname -m || return 63
  cat "$EVID/P-ancestry.txt" || return 64
  printf '%s\n' 'observer_unset_names:' || return 65
  cat "$EVID/observer-unset-names.txt" || return 66
  printf '%s\n' 'observer_host_presence_names_only:' || return 67
  cat "$EVID/observer-host-presence.txt" || return 68
  cat "$EVID/observer-present-count.txt" || return 69
  cat "$EVID/P/tuples-macos.txt" || return 70
  cat "$EVID/P/xml-sha256-macos.txt" || return 71
  cat "$EVID/P/token-scan-macos.txt" || return 72
}
mac_identity_rc=0
mac_identity_fn > "$EVID/P/run-identity-macos.txt" || mac_identity_rc=$?
[ "$mac_identity_rc" -eq 0 ] && [ -s "$EVID/P/run-identity-macos.txt" ] || STOP

p_workflow_show_rc=0
git show "${P}:.github/workflows/s2-harness.yml" > "$EVID/P/workflow-P.runtime.yml" || p_workflow_show_rc=$?
[ "$p_workflow_show_rc" -eq 0 ] && [ -s "$EVID/P/workflow-P.runtime.yml" ] || STOP
p_workflow_slice_rc=0
sed -n '167,174p' "$EVID/P/workflow-P.runtime.yml" > "$EVID/P/llvm-manifest-source.runtime.txt" || p_workflow_slice_rc=$?
[ "$p_workflow_slice_rc" -eq 0 ] && [ -s "$EVID/P/llvm-manifest-source.runtime.txt" ] || STOP
p_workflow_cmp_rc=0
cmp "$EVID/llvm-manifest-source.yml-lines-167-174.txt" "$EVID/P/llvm-manifest-source.runtime.txt" || p_workflow_cmp_rc=$?
[ "$p_workflow_cmp_rc" -eq 0 ] || STOP
manifest_strip_rc=0
sed 's/^          //' "$EVID/P/llvm-manifest-source.runtime.txt" > "$EVID/P/llvm-manifest.runtime.txt" || manifest_strip_rc=$?
[ "$manifest_strip_rc" -eq 0 ] && [ -s "$EVID/P/llvm-manifest.runtime.txt" ] || STOP
manifest_cmp_rc=0
cmp "$EVID/llvm-manifest.txt" "$EVID/P/llvm-manifest.runtime.txt" || manifest_cmp_rc=$?
[ "$manifest_cmp_rc" -eq 0 ] || STOP

llvm_dir_rc=0
LLVM_DIR=$(mktemp -d "$EVID/llvm22-assets-P.XXXXXX") || llvm_dir_rc=$?
[ "$llvm_dir_rc" -eq 0 ] && [ -d "$LLVM_DIR" ] || STOP
llvm_dir_resolve_rc=0
LLVM_DIR=$(cd "$LLVM_DIR" && pwd -P) || llvm_dir_resolve_rc=$?
[ "$llvm_dir_resolve_rc" -eq 0 ] || STOP
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
phase_h_fn > "$EVID/P/phase-H.log" 2>&1 || phase_h=$?
phase_h_receipt_rc=0
printf 'phase_H_transport_rc=%s\n' "$phase_h" > "$EVID/P/phase-H.rc" || phase_h_receipt_rc=$?
[ "$phase_h_receipt_rc" -eq 0 ] && [ -s "$EVID/P/phase-H.rc" ] || STOP
[ "$phase_h" -eq 0 ] && [ -s "$EVID/P/phase-H.log" ] || STOP

linux_outer_rc=0
docker run --rm --platform linux/amd64 --init \
  -v "$LLVM_DIR:/llvm-mirror:ro" \
  -v "$MAIN_REPO:/repo-ro:ro" \
  -v "$EVID:/evidence" \
  ubuntu:24.04 bash /evidence/task-2-linux-container.sh "$P" \
  > "$EVID/P/linux-container.log" 2>&1 || linux_outer_rc=$?
linux_outer_receipt_rc=0
printf '%s\n' "$linux_outer_rc" > "$EVID/P/linux-container.rc" || linux_outer_receipt_rc=$?
[ "$linux_outer_receipt_rc" -eq 0 ] && [ -s "$EVID/P/linux-container.rc" ] || STOP
[ "$linux_outer_rc" -eq 0 ] && [ -s "$EVID/P/linux-container.log" ] || STOP

for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
  [ -s "$EVID/P/$binary-linux.xml" ] || STOP
done
[ -s "$EVID/P/linux-ledger.txt" ] || STOP
[ -s "$EVID/P/linux-suite-ledger.txt" ] || STOP
[ -s "$EVID/P/linux-observer-name-proof.txt" ] || STOP
[ -s "$EVID/P/linux-nofile.txt" ] || STOP
[ -s "$EVID/P/linux-run-head-receipt.txt" ] || STOP
[ -s "$EVID/P/container-payload.rc" ] || STOP
[ -s "$EVID/P/container-copy-out.rc" ] || STOP
container_payload_read_rc=0
container_payload_receipt=$(cat "$EVID/P/container-payload.rc") || container_payload_read_rc=$?
[ "$container_payload_read_rc" -eq 0 ] && [ "$container_payload_receipt" = container_payload_rc=0 ] || STOP
container_copy_read_rc=0
container_copy_receipt=$(cat "$EVID/P/container-copy-out.rc") || container_copy_read_rc=$?
[ "$container_copy_read_rc" -eq 0 ] && [ "$container_copy_receipt" = 'copy_out_rc=0 payload_receipt_rc=0' ] || STOP
[ -s "$EVID/P/ctest-linux-P.log" ] || STOP
[ -s "$EVID/P/ctest-linux-P.rc" ] || STOP

for linux_ledger_expected in \
  phase_R_base_provision_rc=0 \
  phase_R_asset_provision_rc=0 \
  phase_T_transition_fixture_rc=0 \
  phase_S_suite_rc=0; do
  linux_ledger_check_rc=0
  grep -F -x -- "$linux_ledger_expected" "$EVID/P/linux-ledger.txt" >/dev/null || linux_ledger_check_rc=$?
  [ "$linux_ledger_check_rc" -eq 0 ] || STOP
done
for linux_suite_expected in \
  nofile_hard_read_rc=0 \
  nofile_raise_rc=0 \
  nofile_soft_read_rc=0 \
  nofile_soft_equals_hard_rc=0 \
  nofile_receipt_write_rc=0 \
  venv_rc=0 \
  requirements_rc=0 \
  configure_rc=0 \
  build_rc=0 \
  observer_name_proof_create_rc=0 \
  observer_name_input_nonempty_rc=0 \
  observer_name_present_rc=0 \
  observer_name_proof_write_rc=0 \
  observer_name_proof_nonempty_rc=0 \
  ctest_P_log_nonempty_rc=0 \
  ctest_P_receipt_write_rc=0 \
  'suite_aggregate_rc=0 ledger_write_failed=0'; do
  linux_suite_check_rc=0
  grep -F -x -- "$linux_suite_expected" "$EVID/P/linux-suite-ledger.txt" >/dev/null || linux_suite_check_rc=$?
  [ "$linux_suite_check_rc" -eq 0 ] || STOP
done
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do
  binary_ledger_rc=0
  grep -E -x -- "${binary}_producer_rc=[0-9]+" "$EVID/P/linux-suite-ledger.txt" >/dev/null || binary_ledger_rc=$?
  [ "$binary_ledger_rc" -eq 0 ] || STOP
  binary_xml_ledger_rc=0
  grep -F -x -- "${binary}_xml_nonempty_rc=0" "$EVID/P/linux-suite-ledger.txt" >/dev/null || binary_xml_ledger_rc=$?
  [ "$binary_xml_ledger_rc" -eq 0 ] || STOP
done
ctest_ledger_rc=0
grep -E -x -- 'ctest_P_producer_rc=[0-9]+' "$EVID/P/linux-suite-ledger.txt" >/dev/null || ctest_ledger_rc=$?
[ "$ctest_ledger_rc" -eq 0 ] || STOP

for linux_log_input in \
  "$EVID/P/phase-H.log" \
  "$EVID/P/linux-container.log" \
  "$EVID/P/phase-R-base.log" \
  "$EVID/P/phase-R-assets.log" \
  "$EVID/P/phase-T-transition.log" \
  "$EVID/P/phase-S-suite.log" \
  "$EVID/P/linux-venv.log" \
  "$EVID/P/linux-requirements.log" \
  "$EVID/P/linux-configure.log" \
  "$EVID/P/linux-build.log" \
  "$EVID/P/ctest-linux-P.log" \
  "$EVID/P/biv_subprocess_tests-linux.stderr" \
  "$EVID/P/biv_repo_git_tests-linux.stderr" \
  "$EVID/P/biv_repo_engine_tests-linux.stderr" \
  "$EVID/P/biv_tests-linux.stderr" \
  "$EVID/P/biv_probe_tests-linux.stderr"; do
  [ -f "$linux_log_input" ] || STOP
done
linux_cat_rc=0
cat -- \
  "$EVID/P/phase-H.log" \
  "$EVID/P/linux-container.log" \
  "$EVID/P/phase-R-base.log" \
  "$EVID/P/phase-R-assets.log" \
  "$EVID/P/phase-T-transition.log" \
  "$EVID/P/phase-S-suite.log" \
  "$EVID/P/linux-venv.log" \
  "$EVID/P/linux-requirements.log" \
  "$EVID/P/linux-configure.log" \
  "$EVID/P/linux-build.log" \
  "$EVID/P/ctest-linux-P.log" \
  "$EVID"/P/*-linux.stderr \
  > "$EVID/P/all-logs-P-linux.txt" || linux_cat_rc=$?
[ "$linux_cat_rc" -eq 0 ] && [ -f "$EVID/P/all-logs-P-linux.txt" ] || STOP
linux_grep_rc=0
linux_secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/P/all-logs-P-linux.txt") || linux_grep_rc=$?
[ "$linux_grep_rc" -le 1 ] || STOP
token_scan_linux_write_rc=0
printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s grep_rc=%s hits=%s\n' "$linux_cat_rc" "$linux_grep_rc" "$linux_secret_hits" > "$EVID/P/token-scan-linux.txt" || token_scan_linux_write_rc=$?
[ "$token_scan_linux_write_rc" -eq 0 ] && [ -s "$EVID/P/token-scan-linux.txt" ] || STOP
[ "$linux_secret_hits" -eq 0 ] || STOP

linux_hash_rc=0
shasum -a 256 "$EVID"/P/*-linux.xml > "$EVID/P/xml-sha256-linux.txt" || linux_hash_rc=$?
[ "$linux_hash_rc" -eq 0 ] && [ -s "$EVID/P/xml-sha256-linux.txt" ] || STOP
u=0; python3 "$EVID/tuples.py" linux "$EVID"/P/biv_subprocess_tests-linux.xml "$EVID"/P/biv_repo_git_tests-linux.xml "$EVID"/P/biv_repo_engine_tests-linux.xml "$EVID"/P/biv_tests-linux.xml "$EVID"/P/biv_probe_tests-linux.xml > "$EVID/P/tuples-linux.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-linux.txt" ] || STOP
p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-linux.xml" green > "$EVID/P/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-linux.verdict" ] || STOP

ctest_linux_read_rc=0
ctest_linux_rc=$(cat "$EVID/P/ctest-linux-P.rc") || ctest_linux_read_rc=$?
[ "$ctest_linux_read_rc" -eq 0 ] && [ -n "$ctest_linux_rc" ] && [ "$ctest_linux_rc" -ne 0 ] || STOP
f=0; grep -E '^[[:space:]]+[0-9]+ - .*\(Failed\)' "$EVID/P/ctest-linux-P.log" > "$EVID/P/ctest-linux-P.failed" || f=$?; [ "$f" -le 1 ] || STOP
[ -s "$EVID/P/ctest-linux-P.failed" ] || STOP
s=0; sed -E 's/^[[:space:]]*[0-9]+ - ([^ ]+) .*/\1/' "$EVID/P/ctest-linux-P.failed" > "$EVID/P/ctest-linux-P.failed-names" || s=$?; [ "$s" -eq 0 ] || STOP
[ -s "$EVID/P/ctest-linux-P.failed-names" ] || STOP
[ -s "$EVID/ctest-failed.expected" ] || STOP
d=0; diff "$EVID/ctest-failed.expected" "$EVID/P/ctest-linux-P.failed-names" > "$EVID/P/ctest-linux-P.failed.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'claude_adapter_file' "$EVID/P/ctest-linux-P.log") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -ge 1 ] || STOP

linux_skip_b_rc=0
linux_skip_b=$(sed -n 's/^biv_tests linux .* skips=\([0-9][0-9]*\)$/\1/p' "$EVID/B-cells.txt") || linux_skip_b_rc=$?
[ "$linux_skip_b_rc" -eq 0 ] && [ -n "$linux_skip_b" ] || STOP
linux_skip_p_rc=0
linux_skip_p=$(sed -n 's/^expected_skips_observed linux n=\([0-9][0-9]*\) .*/\1/p' "$EVID/P/tuples-linux.txt") || linux_skip_p_rc=$?
[ "$linux_skip_p_rc" -eq 0 ] && [ -n "$linux_skip_p" ] || STOP
[ "$linux_skip_p" -eq "$linux_skip_b" ] || STOP
linux_skip_proof_write_rc=0
printf 'baseline_linux_skips=%s observed_linux_skips=%s\n' "$linux_skip_b" "$linux_skip_p" > "$EVID/P/skips-linux-proof.txt" || linux_skip_proof_write_rc=$?
[ "$linux_skip_proof_write_rc" -eq 0 ] && [ -s "$EVID/P/skips-linux-proof.txt" ] || STOP

name_expected_rc=0
sed 's/$/ absent/' "$EVID/observer-unset-names.txt" > "$EVID/P/linux-observer-name-proof.expected" || name_expected_rc=$?
[ "$name_expected_rc" -eq 0 ] && [ -s "$EVID/P/linux-observer-name-proof.expected" ] || STOP
name_diff_rc=0
diff "$EVID/P/linux-observer-name-proof.expected" "$EVID/P/linux-observer-name-proof.txt" > "$EVID/P/linux-observer-name-proof.delta" || name_diff_rc=$?
[ "$name_diff_rc" -eq 0 ] || STOP

for linux_identity_input in \
  "$EVID/P/linux-run-head-receipt.txt" \
  "$EVID/P/linux-ledger.txt" \
  "$EVID/P/linux-suite-ledger.txt" \
  "$EVID/P/linux-nofile.txt" \
  "$EVID/P/linux-observer-name-proof.txt" \
  "$EVID/P/skips-linux-proof.txt" \
  "$EVID/P/tuples-linux.txt" \
  "$EVID/P/xml-sha256-linux.txt" \
  "$EVID/P/token-scan-linux.txt"; do
  [ -s "$linux_identity_input" ] || STOP
done
linux_identity_fn() {
  printf 'run_id=P-linux-%s\nplatform=ubuntu:24.04 linux/amd64 --init\nP=%s\n' "$P" "$P" || return 81
  cat "$EVID/P/linux-run-head-receipt.txt" || return 82
  cat "$EVID/P/linux-ledger.txt" || return 83
  cat "$EVID/P/linux-suite-ledger.txt" || return 84
  cat "$EVID/P/linux-nofile.txt" || return 85
  cat "$EVID/P/linux-observer-name-proof.txt" || return 86
  cat "$EVID/P/skips-linux-proof.txt" || return 87
  cat "$EVID/P/tuples-linux.txt" || return 88
  cat "$EVID/P/xml-sha256-linux.txt" || return 89
  cat "$EVID/P/token-scan-linux.txt" || return 90
}
linux_identity_rc=0
linux_identity_fn > "$EVID/P/run-identity-linux.txt" || linux_identity_rc=$?
[ "$linux_identity_rc" -eq 0 ] && [ -s "$EVID/P/run-identity-linux.txt" ] || STOP

r=0; git diff bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" -- tests > "$EVID/tests-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/tests-P.diff" ] || STOP; g=0; added=$(grep -c '^+TEST_CASE(' "$EVID/tests-P.diff") || g=$?; [ "$g" -le 1 ] || STOP; g2=0; removed=$(grep -c '^-TEST_CASE(' "$EVID/tests-P.diff") || g2=$?; [ "$g2" -le 1 ] || STOP; predictor_write_rc=0; printf 'added=%s removed=%s\n' "$added" "$removed" > "$EVID/predictor.txt" || predictor_write_rc=$?; [ "$predictor_write_rc" -eq 0 ] && [ -s "$EVID/predictor.txt" ] || STOP
[ "$added" -eq 1 ] && [ "$removed" -eq 0 ] || STOP
entry_rc=0
python3 "$EVID/task-2-entry.py" "$EVID/B-cells.txt" "$EVID/P/tuples-macos.txt" "$EVID/P/tuples-linux.txt" "$EVID/predictor.txt" "$EVID/bpc-table.txt" > "$EVID/P/entry-verdict.txt" 2>&1 || entry_rc=$?
[ "$entry_rc" -eq 0 ] && [ -s "$EVID/P/entry-verdict.txt" ] && [ -s "$EVID/bpc-table.txt" ] || STOP

s=0; git status --porcelain > "$EVID/status-post-P-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P-obs.txt" ] || STOP
s=0; git -C /Users/jack/Programming/bivpak status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-P.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-P.txt" > "$EVID/status-main-post-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP

printf 'TASK_2_COMPLETE P=%s\n' "$P"
exit 0

: <<'TASK2_PLAN_SOURCE'
### Task 2 — observation at P on BOTH targets (the SOURCE of the literals; CG-R7.3/7.7, T-1)

**Files:** none modified. Execute `PL-intg-countgate-20260830.md` Task 1 Steps 3(d)–(g) and 4 (the PROVEN instrument — the five `-r xml` runs per target under `"${OBS_ENV[@]}"` (derived in Task 0 Step 5; NOT re-derived), the inverted-selection scout (e), the R-OBS-5 token scan (f) over the concatenated logs (`cat` stage status-proved, then the zero-match-aware `grep -c`), the run identity (g); the four-phase Linux container: Phase H / R / T / S at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3 :757-763 with R-OBS-6's in-container name-free proof) VERBATIM with these retargets ONLY: (a) the run head is `P` (`$(cat "$EVID/P.txt")`, `git cat-file -e "${P}^{commit}"` re-proved first), the working tree is the r450 worktree, and Phase T clones the BRANCH `intg/r450-discover-parity` from `/repo-ro` with the receipt `rev-parse HEAD == P`; (b) XMLs land in `$EVID/P/<binary>-<target>.xml` and tuples in `$EVID/P/tuples-<target>.txt` (each XML `[ -s ]`-checked; each sha256 recorded); (c) the ancestry proofs are `a=0; git merge-base --is-ancestor bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" || a=$?` (REQUIRE 0) and `a2=0; git merge-base --is-ancestor b065de1107161bb5df9543c09b50091365338c1c "$P" || a2=$?` (REQUIRE 0 — the count-gate repair is in the lineage), both recorded.

- [ ] **Step 1: macOS observation at P** — the five `-r xml` runs under `"${OBS_ENV[@]}"` (each `x=0; "${OBS_ENV[@]}" ./build/ci-macos/<binary> -r xml > "$EVID/P/<binary>-macos.xml" 2> "$EVID/P/<binary>-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/P/<binary>-macos.rc"; [ -s "$EVID/P/<binary>-macos.xml" ] || STOP` — the rc is DATA here: a binary with failures exits nonzero and its tuple still transcribes; a MISSING or empty XML is the STOP), then `u=0; python3 "$EVID/tuples.py" macos "$EVID"/P/biv_subprocess_tests-macos.xml "$EVID"/P/biv_repo_git_tests-macos.xml "$EVID"/P/biv_repo_engine_tests-macos.xml "$EVID"/P/biv_tests-macos.xml "$EVID"/P/biv_probe_tests-macos.xml > "$EVID/P/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-macos.txt" ] || STOP` → `$EVID/P/tuples-macos.txt` (five lines `binary target successes failures expectedFailures skips xml_sha256` + one `expected_skips_observed macos n=… <names>` line); the per-SECTION green proof on the full-suite XML (acceptance criterion 2): `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-macos.xml" green > "$EVID/P/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-macos.verdict" ] || STOP` (the helper selects the named case inside the full run — VALIDATED 2026-09-06 on a synthetic full-suite XML with other cases present → 0); REQUIRE the `biv_tests` skipped-name SET == B's `expected_skips` names for macOS — by MEMBERSHIP, through the helper (rev8; the two producers order the names differently by construction): `k=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/P/tuples-macos.txt" macos > "$EVID/P/skipset-macos.txt" || k=$?; printf 'skipset_P_macos_rc=%s\n' "$k" > "$EVID/P/skipset-macos.rc"; [ "$k" -eq 0 ] && [ -s "$EVID/P/skipset-macos.txt" ] || STOP` (5 = a set or count difference = the V-CG-5 routed FINDING, STOP UP — never an edit; 2 = a missing line, a producer defect, STOP). The scout (e) and token scan (f) as in the countgate plan (both under `"${OBS_ENV[@]}"`, statuses captured, `hits=0` REQUIRED).

- [ ] **Step 2: Linux observation at P** — the four-phase container (ubuntu:24.04 `--platform linux/amd64` `--init`; `nofile` soft raised to hard inside the runuser drop; R-OBS-6 name-free proof by name inside the container before the measurement stage; `cmake --preset ci` + build + the five `-r xml` runs + the workflow-equivalent `ctest --preset ci` run — at P the ctest stage's rc is DATA (nonzero EXPECTED, the C1 tripwire) and its log is copied out as `$EVID/P/ctest-linux-P.log`, then the failing set is extracted EXACTLY as Task 1 Step 5 (iv) (files `ctest-linux-P.failed`, `.failed-names`, `.failed.delta`; REQUIRED == `harness-selftest`; the `claude_adapter_file` cause grep ≥ 1) — each stage's rc in the ledger), XMLs + ctest log + per-stage rc ledger copied out to `$EVID/P/`, then the same `tuples.py linux` invocation over the five copied-out XMLs with `u=0; … || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-linux.txt" ] || STOP` → `$EVID/P/tuples-linux.txt`; the per-SECTION green proof on the copied-out Linux XML: `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-linux.xml" green > "$EVID/P/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-linux.verdict" ] || STOP`; REQUIRE the Linux `biv_tests` observed skip COUNT == B's Linux `skips` cell (1) — the Linux job has no `expected_skips` identity block; the observed skipped NAME(s) are recorded in the tuples file and the report (a count difference = FINDING, STOP UP).
- [ ] **Step 3: ENTRY + the consistency CHECK (CG-R7.1/7.3, T-4) — observed trigger, syntactic predictor** — (i) ENTRY: compare P's `biv_tests` tuples (both targets) with B's cells from `$EVID/B-cells.txt`: a DIFFERENCE in `successes` on both targets = census-changing act → Task 3 transcribes; EQUAL on either target = zero-delta on that target, which contradicts the predictor → FINDING, STOP UP (no transcription, no commit); `failures` and `expectedFailures` MUST be 0 and `skips` MUST equal B's on both targets; the other four binaries' tuples MUST equal B's cells (any difference = FINDING, STOP UP). (ii) the PREDICTOR, materialized: `r=0; git diff bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" -- tests > "$EVID/tests-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/tests-P.diff" ] || STOP; g=0; added=$(grep -c '^+TEST_CASE(' "$EVID/tests-P.diff") || g=$?; [ "$g" -le 1 ] || STOP; g2=0; removed=$(grep -c '^-TEST_CASE(' "$EVID/tests-P.diff") || g2=$?; [ "$g2" -le 1 ] || STOP; printf 'added=%s removed=%s\n' "$added" "$removed" > "$EVID/predictor.txt"` (zero matches exit 1 = VALID; 2+ = STOP); REQUIRE `added=1 removed=0`; (iii) the check: `observed_P(successes) − old_B(successes)` per target must equal `added − removed` = 1 — a CHECK on the record, never a source (the literal written in Task 3 is the XML value); any mismatch in either direction = FINDING routed UP (never a quiet re-observation, never an exclusion). Write `$EVID/bpc-table.txt` NOW with the old(B)/observed(P) columns (new(C) filled at Task 3 Step 3), values copied from `B-cells.txt` and `tuples-*.txt`.
- [ ] **Step 4: no-mutation proof** — `s=0; git status --porcelain > "$EVID/status-post-P-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P-obs.txt" ] || STOP` (the worktree is EMPTY after observation; the evidence lives under `$EVID`; build dirs are ignored); main-repo status vs `status-initial.txt` (rev10: the SAME pathspec as the snapshot — the two shared write surfaces excluded, everything else compared): `s=0; git -C /Users/jack/Programming/bivpak status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-P.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-P.txt" > "$EVID/status-main-post-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.
TASK2_PLAN_SOURCE

: <<'COUNTGATE_SOURCE'
- [ ] **Step 3: macOS observation — under the RULED observer environment (R-OBS-1..5):** (a) DERIVE the unset set at the run head: `(cd harness && python3 -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt"` (R-OBS-1: read from `e3.py` at the run head, never hard-coded; cross-check the file's `:33-37` block by eye and record the line range); record the HOST PRESENCE census BY NAME ONLY — for each derived name, whether the host shell has it set (`printenv <name> >/dev/null && echo present || echo absent`, values never printed) → `$EVID/observer-host-presence.txt`; build the one environment: `OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"` — the FIVE `-r xml` runs (d), the unfiltered scout (e), and discriminator ARM 2 (c) run as `"${OBS_ENV[@]}" <command>` (R-OBS-2: one environment, named once in the run identity); discriminator ARM 1 (c) runs AS-IS in the ambient host environment by design — it is the control; nothing else is unset and no workflow, harness, or product byte carries any of this. (b) `cmake --preset ci-macos && cmake --build --preset ci-macos` (build artifacts land in the gitignored `build/ci-macos`, unchanged from every prior battery). (c) **R-OBS-3 the discriminator, EXECUTED at this head:** ONE exact, state-contained capture form for every status below — the caller's fail-fast state is NEVER changed (no `set +e`, no subshell toggles): `rc=0; <command> || rc=$?` (a failing command in an `||` list does not trigger `-e`; the status lands in the variable). Arm 1 as-is: `rc1=0; ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/discriminator-as-is.log" 2>&1 || rc1=$?; printf '%s\n' "$rc1" > "$EVID/discriminator-as-is.rc"`. Arm 2: `rc2=0; "${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/discriminator-unset.log" 2>&1 || rc2=$?; printf '%s\n' "$rc2" > "$EVID/discriminator-unset.rc"`. The presence count with the same form — `grep -c` PRINTS the count and exits 1 on zero matches, which is VALID DATA here, so the exit is captured, not trusted: `g=0; present_count=$(grep -c present "$EVID/observer-host-presence.txt") || g=$?; [ "$g" -le 1 ] || STOP` (g 2+ = a real grep/input error, STOP; g 0 or 1 = a count); `printf '%s\n' "$present_count" > "$EVID/observer-present-count.txt"`. THEN THE PREDICATE, evaluated from the recorded files and RECORDED as data: `rc2 == 0` (a nonzero arm 2 = FINDING, STOP UP — the hygiene did not explain the red) AND (`rc1 != 0` iff `present_count > 0`) (a red arm 1 with no present name, or a green arm 1 with a present name, = FINDING, STOP UP — the classification did not reproduce); write `discriminator-predicate.txt` = `rc1=<n> rc2=<n> present_count=<n> iff=<PASS|FAIL> hygiene=<PASS|FAIL>`; both `PASS` is the gate to continue. The two numeric codes, the presence count, and the two predicate results are the evidence Step 5's table, Task 2 Step 4's commit message, and acceptance criterion 6 carry; no value is read or printed at any step (validated 2026-09-05 at the pair-planner's seat in bash AND zsh: zero-match → n=0 g=1 reached; one-match → n=1 g=0; missing file → g=2; the `|| rc=$?` arm form → rc captured, script continues). (d) for EACH of the five: `"${OBS_ENV[@]}" ./build/ci-macos/<binary> -r xml > "$EVID/<binary>-macos.xml"` and extract `successes/failures/expectedFailures/skips` + the skipped-test NAME SET into `$EVID/tuples-macos.txt`; verify the biv_tests skipped-name set is byte-identical to the workflow's current `expected_skips` (CG-R4; a difference = FINDING, STOP UP). (e) the inverted-selection scout UNDER THE SAME ENVIRONMENT: `"${OBS_ENV[@]}" ctest --preset ci-macos --output-on-failure > "$EVID/scout-macos.log" 2>&1` WITHOUT `-R`, to enumerate which rows red for platform-instrument reasons (e.g. the ELF-only hardening row's `readelf` absence) — the explicit `-E` exclusion candidates, each justified as a platform-instrument ABSENCE (R-OBS-4: `{safety-hardening}` expected at this head); any red NOT explainable as a platform-instrument absence = FINDING, STOP UP — never a further `env -u`, never an exclusion. (f) R-OBS-5 value hygiene over the CONCATENATED logs (one integer; per-file `grep -c` would print filename-qualified lines), in TWO SEPARATELY PROVED STAGES — a `cat | grep` pipeline would report a failed input stage as a zero-match "success", so the input stage stands alone with its own status: `c=0; cat -- "$EVID"/*.log > "$EVID/all-logs.txt" || c=$?; [ "$c" -eq 0 ] || STOP` (any nonzero `cat` — an unreadable, missing, or unexpanded input — is an INPUT failure, STOP before any count is read; `all-logs.txt` is deliberately not a `.log` name so the glob can never include its own output); THEN the zero-match-aware classification against that proved regular file: `g=0; secret_hits=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN' "$EVID/all-logs.txt") || g=$?; [ "$g" -le 1 ] || STOP` (g 2+ = a real grep error); `printf 'pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=%s hits=%s\n' "$c" "$secret_hits" > "$EVID/token-scan.txt"`; `secret_hits` MUST be 0 — zero matches is the SUCCESSFUL state and exits the grep with 1, which the form captures rather than aborts on; a nonzero count = FINDING, STOP UP; the observation reads no value at any step (validated 2026-09-05 at the pair-planner's seat in bash AND zsh: a broken-symlink `.log` input → `c=1`, STOP reached before any grep; clean inputs → `c=0`, `hits=0`, `g=1`, continue). (g) the run identity for macOS = platform + `sw_vers`/`uname -m` + the run id + the derived unset-name list + the host presence census (names only) + `81066ef`/`29acc6c` ancestry of the run head (both rc 0, copied from `run-head-ancestry.txt` — a measured fact, never restated from memory).
- [ ] **Step 4: Linux observation** — the proven four-phase container instrument (the rev12 text at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3: Phase H host transport, Phase R frozen base command incl. openssh-client + deb provisioning, Phase T pinned uid 1001 + `/repo-ro` clone of main at the RUN HEAD with the rev-parse receipt, Phase S nofile raise + venv + configure/build), with Phase S's measurement stage = the five `-r xml` runs + the same tuple/skip extraction; every container artifact lives under the ephemeral `/work`; before the container exits, copy the five XMLs + the per-stage rc ledger out to `$EVID/` (docker cp or a bind of `$EVID` itself — never a repo path) and record each XML's sha256 into `$EVID/tuples-linux.txt`; the frozen-command fail-closed rule rides unchanged. **R-OBS-6:** inside the container, immediately before the measurement stage, prove the observer name-free BY NAME: for each name in `$EVID/observer-unset-names.txt`, `printenv <name> >/dev/null && echo present || echo absent` → all `absent` (a `present` = STOP: the container recipe leaked a host name); the proof rides the per-stage ledger and the Linux run identity — both targets observed under the CI-equivalent environment.
COUNTGATE_SOURCE

: <<'SUBSTEP1_SOURCE'
  **Phase H (HOST — credential boundary; owns EXACTLY canonical `3cd31e4:.github/workflows/s2-harness.yml:141-151` — the `gh` download loop AND the `SHA256SUMS` derivation/strict check, which write into the asset directory and therefore must complete BEFORE it is mounted read-only):** derive the eight-asset manifest from the pinned candidate bytes (:126-140); with the already-authenticated host `gh`, `gh release download toolchain-mirror-clang-tidy-22-immutable-v1` into a `mktemp -d` directory OUTSIDE the worktree; generate `SHA256SUMS` from the manifest and run `sha256sum --check --strict` THERE (the :149-151 semantics, host-side); only then does the directory bind read-only. The token never enters any container, is never echoed, persisted, or included in evidence; no remote CI (R-4.17).

  **Phase R (CONTAINER AS ROOT — `ubuntu:24.04 --platform linux/amd64 --init`, the verified asset dir bind-mounted READ-ONLY, the MAIN repository bind-mounted READ-ONLY at `/repo-ro`):** install the ENUMERATED base set for bare 24.04 (the hosted runner presupplies these; this container must install them): `apt-get update && apt-get install -y --no-install-recommends ca-certificates git g++ make cmake python3 python3-venv python3-pip libsqlite3-dev binutils zstd openssh-client` — covering clone (git), configure/build (cmake + default-Makefiles + g++ + system SQLite3 per CMakeLists:4 + binutils objcopy per :205 + network/ca-certs for the FetchContent deps at :14-32), harness venv (python3/venv/pip), the Linux runtime `zstd` binary the E2 verbs require, and the real-Git SSH transport expansion (`tests/test_repo_engine.cpp:200`/`:204` hardcode `/usr/bin/ssh -G`; `git` under `--no-install-recommends` does not pull `openssh-client` — the omission was caught fail-closed by the first impl-2 battery run, blocker `intg-substep1/IMPL-pair-implementer-20260828-152108.md`, and folded here through the frozen-command rule's own fresh-review path); capture this base-provision rc as its OWN ledger entry. The package command is FROZEN at this revision's bytes: if any later stage fails on a missing package, that stage's nonzero rc is RETAINED as first observed, the aggregate fails, and the report returns a BLOCKER carrying the proposed package delta for a fresh exact-hash plan review — nothing is installed in-run beyond the frozen command, and any exploratory amended rerun is separately labeled evidence that never satisfies this approved battery. Then execute the canonical provisioning semantics FROM :153 (the first read-only-safe operation; :141-151 are Phase H's) against the read-only asset bind — dpkg package/version/architecture metadata validation per row, install the eight verified debs, prove installed-version equality and the `clang-tidy-22 --version` major-22 probe. (The WSL fixture root is NOT provisioned here: its writability must be proven as the suite identity, which does not exist until Phase T.)

  **Phase T (TRANSITION — writable ephemeral workspace; the host worktree stays byte-clean):** still as root, FIRST create the suite identity at fixed numbers — `groupadd -g 1001 suite && useradd -m -u 1001 -g 1001 suite` — so every later ownership act and probe names an existing, numerically pinned uid/gid; then `git clone --no-hardlinks --branch intg/consent-fabric /repo-ro /work` — the source is the READ-ONLY bind of the MAIN repository (whose common `.git` holds the branch), NEVER the linked candidate worktree (its `.git` is a `gitdir:` pointer to a host-absolute path that does not exist in the container); verify `git -C /work rev-parse HEAD` equals the candidate `3cd31e4823d40c1c9ea020fcb51917618368533b` — the report identifies the exact tree by that receipt. All writable outputs live under `/work` (source-relative `build/ci` per `CMakePresets.json:13`, the harness venv, and the JUnit/Catch2 XML evidence files); `chown -R 1001:1001 /work`. Then the WSL fixture root (`:198-202` semantics, identity-corrected): root runs `mkdir -p /mnt/c/tmp` and `chown -R 1001:1001 /mnt/c` (root may create and chown the path), and the writability probe runs AS THE SUITE IDENTITY — `runuser -u suite -- test -w /mnt/c/tmp` — because a root `test -w` is vacuously true and proves nothing about the uid that will run the cross-flavor cases; capture this fixture provision+probe rc as its OWN ledger entry. Root is never the identity that proves writability.

  **Phase S (SUITE AS NON-ROOT — the measurement):** drop to the suite uid; raise that runuser context's `nofile` soft limit to the inherited hard limit BEFORE the suite (R-4.31(a)); FIRST the harness dependency setup — the canonical `:194-197` step, owned HERE, executed as the suite user and BEFORE CMake configure: `python3 -m venv /work/.venv-harness` then `/work/.venv-harness/bin/python -m pip install -r /work/harness/requirements.lock` (the literal `:196` spells `python`, absent in this bare topology where only `python3` exists — `python3` is the justified substitution rather than adding `python-is-python3`; `harness/CMakeLists.txt:12-20` selects `${CMAKE_SOURCE_DIR}/.venv-harness/bin/python3` when it exists and otherwise falls through SILENTLY to a system interpreter without `pytest`/`jsonschema`/`zstandard`, so this stage is what makes the harness rows measure anything) — captured as its OWN ledger rc; then configure/build with the `ci` preset in `/work`; then the NO-SHORT-CIRCUIT RESULT LEDGER — capture and RETAIN a separate rc per stage: base-provision + deb-provision (Phase R receipts), fixture provision+probe (Phase T receipt), harness-venv, configure, build, CTest (`--output-junit /work/ctest.xml`), the tidy XML row gate, `[a6-fabric] --success`, Catch2 XML generation (`/work/catch.xml`), the count read — running EVERY post-CTest evidence stage regardless of earlier reds; print the full ledger (stage → rc/result) into the report; the battery's final aggregate rc is nonzero if ANY required gate is red. R-4.35 (the registered pre-existing mutation-adversary family, attributed to NO candidate; correctness = R-4.36, m-4's row) and R-4.38 (the disclosed count red, never merge-readiness) control ATTRIBUTION AND READINESS LANGUAGE ONLY — the ledger records observed nonzero results verbatim, never erased.
SUBSTEP1_SOURCE
