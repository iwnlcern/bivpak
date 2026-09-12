#!/usr/bin/env bash
# task-9.sh — materialized VERBATIM from the plan's BLOCK task-9 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 9
set -u
STOP() { printf 'STOP-task-9 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-9.sh" ] || { printf 'STOP-task-9-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-9.txt" > "$RUNNERS/task-9.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-9.proof-tail")" = rc=0 ] || { printf 'STOP-task-9-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-9.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-9.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-9.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-9.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-9-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-9.sh" "$RUNNERS/proof-9.txt" "$RUNNERS/task-9.sha256" "$RUNNERS/task-9.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 9)
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
MAIN=/Users/jack/Programming/bivpak
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-9.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
[ -s "$EVID/runners/task-8.done" ] && [ "$(cat "$EVID/runners/task-8.done")" = rc=0 ] || STOP; [ -s "$EVID/runners/task-8.exit" ] && [ "$(cat "$EVID/runners/task-8.exit")" = rc=0 ] || STOP; [ -s "$EVID/runners/proof-8.tail" ] && [ -s "$EVID/runners/plan_blocks.sha256-8" ] || STOP
[ -s "$EVID/push-class.txt" ] && [ "$(cat "$EVID/push-class.txt")" = class=a ] || STOP; [ -s "$EVID/pr.rc" ] && [ "$(cat "$EVID/pr.rc")" = pr_rc=0 ] || STOP
TOKEN=$(sed -n 's/^token=//p' "$EVID/token.txt"); [ -n "$TOKEN" ] || STOP; RESDIR=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/r450-${TOKEN}; [ ! -e "$RESDIR" ] || STOP
# Step 2
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$RUNNERS/final-set.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -ge 1 ] || STOP
# Step 3
m=0; mkdir -p "$RESDIR" || m=$?; [ "$m" -eq 0 ] && [ -d "$RESDIR" ] || STOP
c=0; while IFS= read -r f; do d=$(dirname "$f") && mkdir -p "$RESDIR/$d" && cp -p "$EVID/$f" "$RESDIR/$f" || { c=1; break; }; done < "$RUNNERS/final-set.txt"; [ "$c" -eq 0 ] || STOP
# Step 4
h=0; (cd "$RESDIR" && find . -type f ! -name SHA256SUMS -exec shasum -a 256 {} + > "$RUNNERS/final-manifest.unsorted") || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/final-manifest.unsorted" ] || STOP; o=0; LC_ALL=C sort -k2 "$RUNNERS/final-manifest.unsorted" > "$RESDIR/SHA256SUMS" || o=$?; [ "$o" -eq 0 ] && [ -s "$RESDIR/SHA256SUMS" ] || STOP
k=0; python3 "$EVID/finalize.py" check "$EVID" "$RESDIR" "$RESDIR/SHA256SUMS" > "$RUNNERS/final-verdict.txt" 2>&1 || k=$?; printf 'finalize_check_rc=%s\n' "$k" > "$RUNNERS/final-verdict.rc"; [ "$k" -eq 0 ] && [ -s "$RUNNERS/final-verdict.txt" ] || STOP
v=0; (cd "$RESDIR" && shasum -a 256 -c --quiet SHA256SUMS) > "$RUNNERS/final-shasum-c.txt" 2>&1 || v=$?; printf 'shasum_c_rc=%s\n' "$v" > "$RUNNERS/final-shasum-c.rc"; [ "$v" -eq 0 ] || STOP
w=0; printf 'results_dir=%s set=%s finalize_check_rc=%s shasum_c_rc=%s\n' "$RESDIR" "$n" "$k" "$v" > "$RUNNERS/final-record.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/final-record.txt" ] || STOP
exit 0
