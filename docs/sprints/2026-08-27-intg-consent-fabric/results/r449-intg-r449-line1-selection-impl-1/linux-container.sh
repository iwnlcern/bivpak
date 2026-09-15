#!/usr/bin/env bash
# linux-container.sh <expected-head> <label B|H> <evidence-host-path> — Phases R / T / S / L inside ubuntu:24.04 (linux/amd64, --init); /llvm-mirror and /repo-ro read-only, /evidence writable AND the evidence home mounted a second time at its HOST path (S carries host-path cwd values and project keys, so Phase L packs it IN PLACE at that path under the readtrace shim after a must-be-YES control).
# The container exits 0 ONLY IF Phase R, T and S all exited 0 AND the payload/copy-out receipts wrote and copied; the ctest rc is carried as DATA by Phase S.
set -u
WORK_ROOT=/work
REPO_ROOT=/work/repo
OUT=/work/out
LEDGER="$OUT/linux-ledger.txt"
EXPECTED=${1-}
LABEL=${2-}
EVID_HOST=${3-}
STOP() { printf 'STOP-linux-container-%s line=%s\n' "$LABEL" "${BASH_LINENO[0]}" >&2; exit 1; }
finalize_container() {
  payload_rc=$?
  trap - EXIT
  payload_receipt_rc=0
  printf 'container_payload_rc=%s\n' "$payload_rc" > "$OUT/container-payload.rc" || payload_receipt_rc=$?
  copy_out_rc=0
  cp -p "$OUT"/* "/evidence/$LABEL/" || copy_out_rc=$?
  copy_receipt_rc=0
  printf 'copy_out_rc=%s payload_receipt_rc=%s\n' "$copy_out_rc" "$payload_receipt_rc" > "$OUT/container-copy-out.rc" || copy_receipt_rc=$?
  final_receipt_copy_rc=0
  cp -p "$OUT/container-copy-out.rc" "/evidence/$LABEL/container-copy-out.rc" || final_receipt_copy_rc=$?
  if [ "$payload_rc" -ne 0 ] || [ "$payload_receipt_rc" -ne 0 ] || [ "$copy_out_rc" -ne 0 ] || [ "$copy_receipt_rc" -ne 0 ] || [ "$final_receipt_copy_rc" -ne 0 ]; then
    exit 1
  fi
  exit 0
}
[ -n "$EXPECTED" ] || STOP
case "$LABEL" in P|C|H|B) ;; *) STOP;; esac
[ -d "/evidence/$LABEL" ] && [ -w "/evidence/$LABEL" ] || STOP
work_root_rc=0
mkdir -p "$OUT" || work_root_rc=$?
[ "$work_root_rc" -eq 0 ] && [ -d "$OUT" ] || STOP
ledger_create_rc=0
: > "$LEDGER" || ledger_create_rc=$?
[ "$ledger_create_rc" -eq 0 ] && [ -f "$LEDGER" ] || STOP
trap finalize_container EXIT
phase_r_base=0
apt-get update > "$OUT/phase-R-base.log" 2>&1 && apt-get install -y --no-install-recommends ca-certificates git g++ make cmake strace python3 python3-venv python3-pip libsqlite3-dev binutils zstd openssh-client >> "$OUT/phase-R-base.log" 2>&1 || phase_r_base=$?
phase_r_base_record_rc=0
printf 'phase_R_base_provision_rc=%s\n' "$phase_r_base" >> "$LEDGER" || phase_r_base_record_rc=$?
[ "$phase_r_base_record_rc" -eq 0 ] || STOP
[ "$phase_r_base" -eq 0 ] || STOP
phase_r_assets_fn() {
  LLVM_TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78'
  while read -r _ expected_package asset; do
    packaged_name=$(dpkg-deb --field "/llvm-mirror/$asset" Package) || return 11
    packaged_version=$(dpkg-deb --field "/llvm-mirror/$asset" Version) || return 12
    packaged_arch=$(dpkg-deb --field "/llvm-mirror/$asset" Architecture) || return 13
    [ "$packaged_name" = "$expected_package" ] || return 14
    [ "$packaged_version" = "$LLVM_TIDY_VERSION" ] || return 15
    [ "$packaged_arch" = amd64 ] || return 16
  done < /llvm-mirror/MANIFEST
  set -- /llvm-mirror/*.deb
  [ "$#" -eq 8 ] || return 18
  apt-get install -y --no-install-recommends /llvm-mirror/*.deb || return 19
  while read -r _ package _; do
    installed_package_version=$(dpkg-query --show --showformat='${Version}' "$package") || return 20
    [ "$installed_package_version" = "$LLVM_TIDY_VERSION" ] || return 21
  done < /llvm-mirror/MANIFEST
  installed_version=$(dpkg-query --show --showformat='${Version}' clang-tidy-22) || return 22
  [ "$installed_version" = "$LLVM_TIDY_VERSION" ] || return 23
  clang-tidy-22 --version > "$OUT/clang-tidy-version.txt" || return 24
  [ -s "$OUT/clang-tidy-version.txt" ] || return 25
  observed_major=$(sed -nE 's/.*LLVM version ([0-9]+).*/\1/p' "$OUT/clang-tidy-version.txt") || return 26
  [ "$observed_major" = 22 ] || return 27
}
phase_r_assets=0
phase_r_assets_fn > "$OUT/phase-R-assets.log" 2>&1 || phase_r_assets=$?
phase_r_assets_record_rc=0
printf 'phase_R_asset_provision_rc=%s\n' "$phase_r_assets" >> "$LEDGER" || phase_r_assets_record_rc=$?
[ "$phase_r_assets_record_rc" -eq 0 ] || STOP
[ "$phase_r_assets" -eq 0 ] || STOP
phase_t_transition_fn() {
  groupadd -g 1001 suite || return 31
  useradd -m -u 1001 -g 1001 suite || return 32
  git config --global --add safe.directory /repo-ro || return 33
  git clone --no-hardlinks --branch intg/r449-line1-selection /repo-ro "$REPO_ROOT" || return 34
  git -C "$REPO_ROOT" checkout -q --detach "$EXPECTED" || return 35
  observed_head=$(git -C "$REPO_ROOT" rev-parse HEAD) || return 36
  printf 'expected=%s observed=%s\n' "$EXPECTED" "$observed_head" > "$OUT/linux-run-head-receipt.txt" || return 37
  [ -s "$OUT/linux-run-head-receipt.txt" ] || return 38
  [ "$observed_head" = "$EXPECTED" ] || return 39
  cp /evidence/linux-suite.sh "$REPO_ROOT/linux-suite.sh" || return 40
  cp /evidence/observer-unset-names.txt "$REPO_ROOT/observer-unset-names.txt" || return 41
  chown -R 1001:1001 "$REPO_ROOT" "$OUT" || return 42
  mkdir -p /mnt/c/tmp || return 43
  chown -R 1001:1001 /mnt/c || return 44
  runuser -u suite -- test -w /mnt/c/tmp || return 45
}
phase_t_transition=0
phase_t_transition_fn > "$OUT/phase-T-transition.log" 2>&1 || phase_t_transition=$?
phase_t_record_rc=0
printf 'phase_T_transition_fixture_rc=%s\n' "$phase_t_transition" >> "$LEDGER" || phase_t_record_rc=$?
[ "$phase_t_record_rc" -eq 0 ] || STOP
[ "$phase_t_transition" -eq 0 ] || STOP
phase_s_suite=0
runuser -u suite -- bash "$REPO_ROOT/linux-suite.sh" "$REPO_ROOT" "$OUT" "$LABEL" > "$OUT/phase-S-suite.log" 2>&1 || phase_s_suite=$?
phase_s_record_rc=0
printf 'phase_S_suite_rc=%s\n' "$phase_s_suite" >> "$LEDGER" || phase_s_record_rc=$?
[ "$phase_s_record_rc" -eq 0 ] || STOP
[ "$phase_s_suite" -eq 0 ] || STOP
phase_l_leg_fn() {
  [ -n "$EVID_HOST" ] && [ -d "$EVID_HOST/work/ws/proj" ] && [ -s /evidence/synth-manifest.json ] && [ -s /evidence/readtrace.c ] || return 51
  [ "$(cd "$EVID_HOST" && pwd -P)" = "$(cd /evidence && pwd -P)" ] || [ -s "$EVID_HOST/synth-manifest.json" ] || return 52
  WORK_HOST=$EVID_HOST/work
  rm -f "$WORK_HOST/ws/proj.bvpk" "$WORK_HOST/ws/proj.bvpk.partial" "$WORK_HOST/ws/proj.bvpk.spool" || return 53
  mkdir -p "$WORK_HOST/tmp" || return 54
  gcc -shared -fPIC -O2 -o "$WORK_ROOT/readtrace.so" /evidence/readtrace.c -ldl || return 55
  chmod 0755 "$WORK_ROOT/readtrace.so" || return 56
  control_file=$(runuser -u suite -- python3 -c 'import json,sys; m=json.load(open(sys.argv[1])); r=[f for f in m["files"] if f["class"]=="codex-bulk" and not f["selected"]][0]; print(r["path"], r["size"])' /evidence/synth-manifest.json) || return 57
  control_path=${control_file% *}; control_size=${control_file##* }
  runuser -u suite -- env LD_PRELOAD="$WORK_ROOT/readtrace.so" READTRACE_OUT="$OUT/readtrace-control-$LABEL.tsv" READTRACE_PREFIX="$WORK_HOST" dd if="$WORK_HOST/$control_path" of=/dev/null bs=8192 > "$OUT/readtrace-control-$LABEL.log" 2>&1 || return 58
  python3 /evidence/readtrace_reduce.py "$OUT/readtrace-control-$LABEL.tsv" "$WORK_HOST" > "$OUT/readtrace-control-$LABEL.reduced" || return 59
  printf '%s\t%s\n' "$control_path" "$control_size" > "$OUT/readtrace-control-$LABEL.expected" || return 60
  cmp "$OUT/readtrace-control-$LABEL.reduced" "$OUT/readtrace-control-$LABEL.expected" || return 61
  runuser -u suite -- env HOME="$WORK_HOST/home" CODEX_HOME="$WORK_HOST/codex-home" CLAUDE_CONFIG_DIR="$WORK_HOST/claude-config" TMPDIR="$WORK_HOST/tmp" LD_PRELOAD="$WORK_ROOT/readtrace.so" READTRACE_OUT="$OUT/readtrace-$LABEL.tsv" READTRACE_PREFIX="$WORK_HOST" "$REPO_ROOT/build/ci/biv" pack "$WORK_HOST/ws/proj" --json > "$OUT/pack-linux-$LABEL.json" 2> "$OUT/pack-linux-$LABEL.stderr" || pack_rc=$?
  printf '%s\n' "${pack_rc-0}" > "$OUT/pack-linux-$LABEL.rc" || return 62
  case "${pack_rc-0}" in 0|2) ;; *) return 63;; esac
  grep -c -F '"ok": true' "$OUT/pack-linux-$LABEL.json" > "$OUT/pack-linux-$LABEL.ok" || return 64
  [ -s "$OUT/readtrace-$LABEL.tsv" ] || return 65
  python3 /evidence/readtrace_reduce.py "$OUT/readtrace-$LABEL.tsv" "$WORK_HOST" > "$OUT/bytes-$LABEL.tsv" || return 66
  [ -s "$OUT/bytes-$LABEL.tsv" ] || return 67
  mv "$WORK_HOST/ws/proj.bvpk" "$WORK_HOST/ws/proj-linux-$LABEL.bvpk" || return 68
  python3 /evidence/membership.py "$WORK_HOST/ws/proj-linux-$LABEL.bvpk" "$OUT/membership-linux-$LABEL.json" > "$OUT/membership-linux-$LABEL.log" 2>&1 || return 69
  [ -s "$OUT/membership-linux-$LABEL.json" ] || return 70
  wc -l < "$OUT/readtrace-$LABEL.tsv" > "$OUT/readtrace-$LABEL.rows" || return 71
}
phase_l_leg=0
pack_rc=0
phase_l_leg_fn > "$OUT/phase-L-leg.log" 2>&1 || phase_l_leg=$?
phase_l_record_rc=0
printf 'phase_L_leg_rc=%s\n' "$phase_l_leg" >> "$LEDGER" || phase_l_record_rc=$?
[ "$phase_l_record_rc" -eq 0 ] || STOP
[ "$phase_l_leg" -eq 0 ] || STOP
printf 'LINUX_FOUR_PHASE_COMPLETE %s=%s\n' "$LABEL" "$EXPECTED"
exit 0
