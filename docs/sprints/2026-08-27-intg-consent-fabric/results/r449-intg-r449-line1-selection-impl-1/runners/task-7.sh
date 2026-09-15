#!/usr/bin/env bash
# task-7.sh — materialized VERBATIM from the plan's BLOCK task-7 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 7
set -u
STOP() { printf 'STOP-task-7 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-7.sh" ] || { printf 'STOP-task-7-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-7.txt" > "$RUNNERS/task-7.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-7.proof-tail")" = rc=0 ] || { printf 'STOP-task-7-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-7.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-7.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-7.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-7.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-7-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-7.sh" "$RUNNERS/proof-7.txt" "$RUNNERS/task-7.sha256" "$RUNNERS/task-7.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 7)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-7.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
[ -s "$EVID/runners/task-6.done" ] && [ "$(cat "$EVID/runners/task-6.done")" = rc=0 ] || STOP; [ -s "$EVID/runners/task-6.exit" ] && [ "$(cat "$EVID/runners/task-6.exit")" = rc=0 ] || STOP; [ -s "$EVID/runners/proof-6.tail" ] && [ -s "$EVID/runners/plan_blocks.sha256-6" ] || STOP
[ -s "$EVID/push-class.txt" ] && [ "$(cat "$EVID/push-class.txt")" = class=a ] || STOP; [ -s "$EVID/pr.rc" ] && [ "$(cat "$EVID/pr.rc")" = pr_rc=0 ] || STOP
TOKEN=$(sed -n 's/^token=//p' "$EVID/token.txt"); [ -n "$TOKEN" ] || STOP; RESDIR=$MAIN/docs/sprints/2026-08-27-intg-consent-fabric/results/r449-${TOKEN}; [ ! -e "$RESDIR" ] || STOP
# Step 2
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set-pre.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set-pre.txt" ] || STOP; a=0; n0=$(awk 'END { print NR }' "$RUNNERS/final-set-pre.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n0" -ge 1 ] || STOP
g=0; k=$(grep -c -E '^(work/|census-raw/)' "$RUNNERS/final-set-pre.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
# Step 2b
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
r=0; git grep -h -o -E "$ALT" "$B" -- tests/test_adapter_codex_collect.cpp tests/test_cli.cpp > "$EVID/census-raw/fixture-tokens.raw" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/census-raw/fixture-tokens.raw" ] || STOP; o=0; LC_ALL=C sort -u "$EVID/census-raw/fixture-tokens.raw" > "$EVID/census-raw/fixture-tokens.set" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/census-raw/fixture-tokens.set" ] || STOP
: > "$EVID/census-raw/record-hits.raw"; : > "$EVID/record-token-files.txt"; while IFS= read -r f; do g=0; grep -o -E "$ALT" "$EVID/$f" >> "$EVID/census-raw/record-hits.raw" || g=$?; [ "$g" -le 1 ] || STOP; [ "$g" -eq 0 ] && printf '%s\n' "$f" >> "$EVID/record-token-files.txt"; done < "$RUNNERS/final-set-pre.txt"
o=0; LC_ALL=C sort -u "$EVID/census-raw/record-hits.raw" > "$EVID/census-raw/record-hits.set" || o=$?; [ "$o" -eq 0 ] || STOP; c=0; LC_ALL=C comm -23 "$EVID/census-raw/record-hits.set" "$EVID/census-raw/fixture-tokens.set" > "$EVID/census-raw/record-hits.foreign" || c=$?; [ "$c" -eq 0 ] && [ ! -s "$EVID/census-raw/record-hits.foreign" ] || STOP
a=0; nf=$(awk 'END { print NR }' "$EVID/record-token-files.txt") || a=$?; nd=$(awk 'END { print NR }' "$EVID/census-raw/record-hits.set") || a=$?; nt=$(awk 'END { print NR }' "$EVID/census-raw/fixture-tokens.set") || a=$?; [ "$a" -eq 0 ] || STOP
w=0; printf 'set_files_scanned=%s record_files_carrying_a_fixture_token_copy=%s distinct_matched_strings=%s product_fixture_token_set_size=%s foreign_matched_strings=0 class=B-fixture-copies-only note=matched strings live only under census-raw (excluded from the record); this receipt and record-token-files.txt carry paths and counts only and are the two files added to the set after this scan\n' "$n0" "$nf" "$nd" "$nt" > "$EVID/record-token-classes.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/record-token-classes.txt" ] || STOP
g=0; k=$(grep -c -E "$ALT" "$EVID/record-token-classes.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP; g=0; k=$(grep -c -E "$ALT" "$EVID/record-token-files.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
# Step 2c
x=0; python3 "$EVID/finalize.py" list "$EVID" > "$RUNNERS/final-set.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/final-set.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$RUNNERS/final-set.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq "$((n0 + 2))" ] || STOP; d=0; LC_ALL=C comm -13 "$RUNNERS/final-set-pre.txt" "$RUNNERS/final-set.txt" > "$RUNNERS/final-set.added" || d=$?; [ "$d" -eq 0 ] || STOP; printf 'record-token-classes.txt\nrecord-token-files.txt\n' > "$RUNNERS/final-set.added.expected"; c=0; cmp "$RUNNERS/final-set.added" "$RUNNERS/final-set.added.expected" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 3
m=0; mkdir -p "$RESDIR" || m=$?; [ "$m" -eq 0 ] && [ -d "$RESDIR" ] || STOP
c=0; while IFS= read -r f; do d=$(dirname "$f") && mkdir -p "$RESDIR/$d" && cp -p "$EVID/$f" "$RESDIR/$f" || { c=1; break; }; done < "$RUNNERS/final-set.txt"; [ "$c" -eq 0 ] || STOP
# Step 4
h=0; (cd "$RESDIR" && find . -type f ! -name SHA256SUMS -exec shasum -a 256 {} + > "$RUNNERS/final-manifest.unsorted") || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/final-manifest.unsorted" ] || STOP; o=0; LC_ALL=C sort -k2 "$RUNNERS/final-manifest.unsorted" > "$RESDIR/SHA256SUMS" || o=$?; [ "$o" -eq 0 ] && [ -s "$RESDIR/SHA256SUMS" ] || STOP
k=0; python3 "$EVID/finalize.py" check "$EVID" "$RESDIR" "$RESDIR/SHA256SUMS" > "$RUNNERS/final-verdict.txt" 2>&1 || k=$?; printf 'finalize_check_rc=%s\n' "$k" > "$RUNNERS/final-verdict.rc"; [ "$k" -eq 0 ] && [ -s "$RUNNERS/final-verdict.txt" ] || STOP
v=0; (cd "$RESDIR" && shasum -a 256 -c --quiet SHA256SUMS) > "$RUNNERS/final-shasum-c.txt" 2>&1 || v=$?; printf 'shasum_c_rc=%s\n' "$v" > "$RUNNERS/final-shasum-c.rc"; [ "$v" -eq 0 ] || STOP
w=0; printf 'results_dir=%s set=%s finalize_check_rc=0 shasum_c_rc=0 token_classes=B-fixture-copies-only foreign=0 post_controller_recheck=owed-by-the-pair-planner-before-commit\n' "$RESDIR" "$n" > "$RUNNERS/final-record.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/final-record.txt" ] || STOP
exit 0
