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
WORKTREE=/Users/jack/Programming/bivpak-intg-r450-discover-parity
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-7.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
# Step 1
C=$(cat "$EVID/C.txt")
r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" > "$EVID/touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/touched.numstat" ] || STOP
s=0; awk '{print $3}' "$EVID/touched.numstat" > "$EVID/touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/touched.paths" > "$EVID/touched.paths.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf '.github/workflows/s2-harness.yml\nsrc/adapters/claude_code/claude_code.cpp\ntests/test_adapter_claude_collect.cpp\n' > "$EVID/touched.expected"; d=0; diff "$EVID/touched.expected" "$EVID/touched.paths.sorted" > "$EVID/touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP
g=0; k=$(grep -c -E '^2\t2\t\.github/workflows/s2-harness\.yml$' "$EVID/touched.numstat") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
h=0; git show "${C}:src/adapters/codex/codex.cpp" > "$EVID/codex-C.cpp" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/codex-C.cpp" ] || STOP
h=0; shasum -a 256 "$EVID/codex-C.cpp" > "$EVID/codex-C.sha" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/codex-C.sha" ] || STOP; x=$(cut -d' ' -f1 "$EVID/codex-C.sha") || STOP; g=0; k=$(grep -c -F -- "$x" "$EVID/base-hashes.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP
r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-C.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-C.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-C.diff" > "$EVID/claude-C.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-C.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-C.hunks" 570 596 > "$EVID/claude-C.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP
g=0; k=$(grep -c 'collect(' "$EVID/claude-C.diff") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -eq 0 ] || STOP
H=$(cat "$EVID/H.txt"); r=0; git diff --numstat "$C" "$H" > "$EVID/c-to-h.numstat.final" || r=$?; [ "$r" -eq 0 ] || STOP; d=0; diff "$EVID/H.numstat.expected" "$EVID/c-to-h.numstat.final" > "$EVID/c-to-h.numstat.final.delta" || d=$?; [ "$d" -eq 0 ] || STOP
r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$H" > "$EVID/touched-H.numstat" || r=$?; [ "$r" -eq 0 ] || STOP; s=0; awk '{print $3}' "$EVID/touched-H.numstat" > "$EVID/touched-H.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/touched-H.paths" > "$EVID/touched-H.paths.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf '.github/workflows/s2-harness.yml\nharness/bivharness/e3.py\nharness/selftest/stub_biv.py\nharness/selftest/test_store_isolation.py\nsrc/adapters/claude_code/claude_code.cpp\ntests/test_adapter_claude_collect.cpp\n' > "$EVID/touched-H.expected"; d=0; diff "$EVID/touched-H.expected" "$EVID/touched-H.paths.sorted" > "$EVID/touched-H.delta" || d=$?; [ "$d" -eq 0 ] || STOP
# Step 2
printf '%s\n' 'tests/test_adapter_codex_collect.cpp:383' 'tests/test_adapter_codex_collect.cpp:385' 'tests/test_cli.cpp:1188' > "$EVID/census-expected-tree.txt"
printf '%s\n' 'tests/test_adapter_codex_collect.cpp' 'tests/test_cli.cpp' > "$EVID/census-expected-history.txt"
H=$(cat "$EVID/H.txt"); e=0; git cat-file -e "${H}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP; [ "$(git rev-parse HEAD)" = "$H" ] || STOP
r=0; git grep -n -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$H" -- . > "$EVID/census-tree-raw.txt" || r=$?; [ "$r" -le 1 ] || STOP
s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-tree-raw.txt" > "$EVID/census-tree-stripped.txt" || s=$?; [ "$s" -eq 0 ] || STOP
s=0; sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/census-tree-stripped.txt" > "$EVID/census-tree.txt" || s=$?; [ "$s" -eq 0 ] || STOP
d=0; diff "$EVID/census-expected-tree.txt" "$EVID/census-tree.txt" > "$EVID/census-tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP
r=0; git rev-list "$H" > "$EVID/rl.txt" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/rl.txt" ] || STOP
x=0; xargs git grep -l -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' < "$EVID/rl.txt" > "$EVID/census-history-raw.txt" || x=$?; [ "$x" -le 1 ] || STOP
[ -s "$EVID/census-history-raw.txt" ] || STOP
s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-history-raw.txt" > "$EVID/census-history-paths.txt" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort -u "$EVID/census-history-paths.txt" > "$EVID/census-history.txt" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/census-history.txt" ] || STOP; d=0; diff "$EVID/census-expected-history.txt" "$EVID/census-history.txt" > "$EVID/census-history.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
