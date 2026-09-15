#!/usr/bin/env bash
# task-6.sh — materialized VERBATIM from the plan's BLOCK task-6 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 6
set -u
STOP() { printf 'STOP-task-6 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-6.sh" ] || { printf 'STOP-task-6-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-6.txt" > "$RUNNERS/task-6.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-6.proof-tail")" = rc=0 ] || { printf 'STOP-task-6-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-6.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-6.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-6.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-6.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-6-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-6.sh" "$RUNNERS/proof-6.txt" "$RUNNERS/task-6.sha256" "$RUNNERS/task-6.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 6)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-6.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
H=$(cat "$EVID/H.txt") || STOP; C=$(cat "$EVID/C.txt") || STOP; [ "$(git rev-parse HEAD)" = "$H" ] && [ "$(git rev-parse "${H}^")" = "$C" ] && [ "$(git rev-parse "${C}^")" = "$B" ] || STOP
[ -s "$RUNNERS/task-6-go.txt" ] || STOP; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-6-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || STOP; GOP=$(sed -n '1p' "$RUNNERS/task-6-go.txt") || STOP; case "$GOP" in /*) GO=$GOP;; *) GO=$MAIN/$GOP;; esac; [ -s "$GO" ] || STOP
GOD=$(cd "$(dirname "$GO")" && pwd -P) || STOP; RR=$(cd "$MAIN/.relays/intg/intg-r449" && pwd -P) || STOP; [ "$GOD" = "$RR" ] || STOP
GOB=$(basename "$GO") || STOP; case "$GOB" in SITREP-pair-planner-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9][0-9][0-9].md) :;; *) STOP;; esac
g=0; k=$(grep -c -F -- "intg-r449/$GOB" "$MAIN/.relays/intg/INDEX.md") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP
g=0; k=$(grep -c -E '^FROM: intg\.pair-planner$' "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^TO: intg\.pair-implementer$' "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^PHASE: SITREP$' "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^TASK6_GO: yes$' "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- "TASK6_C: $C" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- "TASK6_H: $H" "$GO") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
PDC=$(cd "$MAIN/../pdc/master/relays" && pwd -P) || STOP
M2P=$(sed -n -E 's/^OWNER_REVIEW_C: ([^ |]+) \| FROM=(m-2\.(planner|implementer)) \| VERDICT=no-red$/\1/p' "$GO") || STOP; M2F=$(sed -n -E 's/^OWNER_REVIEW_C: [^ |]+ \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p' "$GO") || STOP; [ -n "$M2P" ] && [ -n "$M2F" ] || STOP
case "$M2P" in /*) M2=$M2P;; *) M2=$MAIN/$M2P;; esac; [ -s "$M2" ] || STOP
M2D=$(cd "$(dirname "$M2")" && pwd -P) || STOP; case "$M2D" in "$PDC"/*) :;; *) STOP;; esac
M3P=$(sed -n -E 's/^OWNER_REVIEW_H: ([^ |]+) \| FROM=(m-3\.(planner|implementer)) \| VERDICT=no-red$/\1/p' "$GO") || STOP; M3F=$(sed -n -E 's/^OWNER_REVIEW_H: [^ |]+ \| FROM=([^ |]+) \| VERDICT=no-red$/\1/p' "$GO") || STOP; [ -n "$M3P" ] && [ -n "$M3F" ] || STOP
case "$M3P" in /*) M3=$M3P;; *) M3=$MAIN/$M3P;; esac; [ -s "$M3" ] || STOP
M3D=$(cd "$(dirname "$M3")" && pwd -P) || STOP; case "$M3D" in "$PDC"/*) :;; *) STOP;; esac
g=0; k=$(grep -c -x -F -- "FROM: $M2F" "$M2") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^PHASE: [A-Z-]+$' "$M2") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- "R449_REVIEW_OBJECT: C=$C" "$M2") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- 'R449_REVIEW_SCOPE: V-LS-1..6' "$M2") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- 'R449_REVIEW_VERDICT: no-red' "$M2") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -i -E '^([A-Z0-9_]*VERDICT|STATUS): *(must-revise|reject|reject-narrow|red|blocked|pending|hold|human-decision-required)' "$M2") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
g=0; k=$(grep -c -x -F -- "FROM: $M3F" "$M3") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -E '^PHASE: [A-Z-]+$' "$M3") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- "R449_REVIEW_OBJECT: H=$H" "$M3") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- 'R449_REVIEW_SCOPE: V-RP-1..8 S-RP-1..4' "$M3") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F -- 'R449_REVIEW_VERDICT: no-red' "$M3") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -i -E '^([A-Z0-9_]*VERDICT|STATUS): *(must-revise|reject|reject-narrow|red|blocked|pending|hold|human-decision-required)' "$M3") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
w=0; printf 'go=%s\nm2_review_of_C=%s FROM=%s\nm3_review_of_H=%s FROM=%s\n' "$GO" "$M2" "$M2F" "$M3" "$M3F" > "$EVID/task-6-go.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/task-6-go.txt" ] || STOP
u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP
l=0; git ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP
v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP
[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP
for f in census-tree.delta census-history.delta census-record-tree.delta census-record-history.delta H/membership.delta H/membership-linux.delta; do [ -f "$EVID/$f" ] && [ ! -s "$EVID/$f" ] || STOP; done
[ "$(cat "$EVID/H/leg12-verdict.rc")" = leg12_rc=0 ] && [ "$(cat "$EVID/H/count-gate-macos.rc")" = count_gate_macos_rc=0 ] && [ "$(cat "$EVID/H/count-gate-linux.rc")" = count_gate_linux_rc=0 ] && [ "$(cat "$EVID/H/ctest-macos-H.rc")" = ctest_macos_H_rc=0 ] || STOP
g=0; k=$(grep -c -E ' bar=(pass-green|pass-r435-disclosed-registered-red)$' "$EVID/H/linux-selftest-bar.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
printf '%s %s\n' "$0" "${ZSH_VERSION:-${BASH_VERSION:-unknown}}" > "$EVID/shell.txt"
# Step 2
y=0; git push --dry-run --no-tags origin intg/r449-line1-selection > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP
g=0; k=$(grep -c -F 'intg/r449-line1-selection -> intg/r449-line1-selection' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
p=0; git push --no-tags origin intg/r449-line1-selection > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"
o=0; git ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")
if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$H" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$H" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=e; fi; printf 'class=%s\n' "$class" > "$EVID/push-class.txt"
[ "$class" = a ] || STOP
# Step 3
w=0; { printf '%s\n\n' 'R-4.49 line-1 selection (m-2 fence 142000 §2 / rev2 144700; the operator grant 152118 "lets fix both please", 2 of 2): candidacy in both collect paths is decided from a HEAD-BOUNDED streamed read that stops at the predicate today'"'"'s parsers already implement — the FIRST cwd-bearing record for claude (sealed ADDENDUM-1 §A1; no cwd anywhere = whole file + no_cwd_record, sealed) and the FIRST session_meta record for codex (sealed c1 §4) — and the whole-file read + the unchanged whole-text parsers run only for an in-root candidate. m-2 C-1/C-2 rulings (DESIGN-m2-planner-20260913-170000): selection identity by construction; the act is read-bounding only. ONE PR, TWO COMMITS, TWO OWNERS (the R-4.50 arm A shape): C = the lane'"'"'s product commit under m-2'"'"'s fence (SECTIONs inside existing TEST_CASEs; case census unchanged); H = m-3'"'"'s harness commit (C-2 rule 4): the two S-CP-2 _ADAPTER_SOURCE_ANCHORS literals re-pinned to C'"'"'s adapter digests, nothing else.'; printf 'Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f\nPlan pin: intg-r449-line1-selection-plan-20260913 sha256 %s\n\n' "$(cat "$RUNNERS/plan-lock.txt")"; printf 'B=%s (origin/main, the R-4.50 landing merge)\nC=%s (C^ = B; the product commit)\nH=%s (H^ = C; the harness commit)\n\n' "$B" "$C" "$H"; printf 'C touched (numstat):\n'; cat "$EVID/H/touched.numstat"; printf '\nH touched (numstat):\n'; cat "$EVID/H/harness.numstat"; printf '\nCOUNT-GATE (the ten OverallResultsCases cells: literal at B == observed at B == observed at H):\n'; cat "$EVID/H/count-gate-macos.txt" "$EVID/H/count-gate-linux.txt"; printf '\nLEG 1 / LEG 2 (bytes read per store file — the readtrace.c LD_PRELOAD read accountant inside the Linux parity container, validated first by a must-be-YES dd control, B vs H over the synthetic store S in place):\n'; cat "$EVID/H/leg12-summary.txt"; printf '\nLEG 3 (whole-record membership identity over S at B and at H, macOS and Linux: deltas empty) and the cost receipt:\n'; cat "$EVID/H/cost-receipt.txt"; printf '\nLinux acceptance at H (two-outcome bar):\n'; cat "$EVID/H/linux-selftest-bar.txt"; printf '\nCensus at the branch head (both arms; paths only):\n'; cat "$EVID/census-summary.txt"; printf '\nOwner reviews RETURNED through master before this PR (named in the pair Planner'"'"'s go relay %s): m-2 V-LS-1..6 of C — %s (%s); m-3 V-RP-1..8 of H — %s (%s);' "$(basename "$GO")" "$(basename "$M2")" "$M2F" "$(basename "$M3")" "$M3F"; printf ' the four-condition merge bar and the operator'"'"'s condition-4 token follow.\n\nThis PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites on both targets, the Docker parity leg, the three-leg witness, the owner byte review and the operator'"'"'s token — a red remote CI is cited nowhere. Merge is local under the operator'"'"'s token; the landing push of main follows under the R-4.52 landing rule as the merge packet'"'"'s own step.\n'; } > "$EVID/pr-body.md" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/pr-body.md" ] || STOP
g=0; k=$(grep -c -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$EVID/pr-body.md") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
q=0; gh pr create --base main --head intg/r449-line1-selection --title "adapters(claude, codex): decide candidacy from a head-bounded read; full reads only for selected sessions (R-4.49)" --body-file "$EVID/pr-body.md" > "$EVID/pr.txt" 2>&1 || q=$?; printf 'pr_rc=%s\n' "$q" > "$EVID/pr.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/pr.txt" ] || STOP
exit 0
