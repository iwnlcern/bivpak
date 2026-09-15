#!/usr/bin/env bash
# task-2.sh — materialized VERBATIM from the plan's BLOCK task-2 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 2
set -u
STOP() { printf 'STOP-task-2 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-2.sh" ] || { printf 'STOP-task-2-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-2.txt" > "$RUNNERS/task-2.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-2.proof-tail")" = rc=0 ] || { printf 'STOP-task-2-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-2.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-2.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-2.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-2.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-2-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-2.sh" "$RUNNERS/proof-2.txt" "$RUNNERS/task-2.sha256" "$RUNNERS/task-2.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 2)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-2.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
[ "$(git rev-parse HEAD)" = "$B" ] || STOP; s=0; git status --porcelain > "$EVID/H/status-pre-patch.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-pre-patch.txt" ] || STOP
# Step 1
x=0; python3 "$EVID/head_reader_claude.py" src/adapters/claude_code/claude_code.cpp > "$EVID/H/patch-claude.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/head_reader_codex.py" src/adapters/codex/codex.cpp > "$EVID/H/patch-codex.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/tests_claude_r449.py" tests/test_adapter_claude_collect.cpp > "$EVID/H/patch-tests-claude.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
x=0; python3 "$EVID/tests_codex_r449.py" tests/test_adapter_codex_collect.cpp > "$EVID/H/patch-tests-codex.log" 2>&1 || x=$?; [ "$x" -eq 0 ] || STOP
r=0; git diff --numstat > "$EVID/H/touched-wt.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/touched-wt.numstat" ] || STOP; s=0; awk '{print $3}' "$EVID/H/touched-wt.numstat" > "$EVID/H/touched-wt.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/touched-wt.paths" > "$EVID/H/touched-wt.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf 'src/adapters/claude_code/claude_code.cpp\nsrc/adapters/codex/codex.cpp\ntests/test_adapter_claude_collect.cpp\ntests/test_adapter_codex_collect.cpp\n' > "$EVID/touched.expected"; d=0; diff "$EVID/touched.expected" "$EVID/H/touched-wt.sorted" > "$EVID/H/touched-wt.delta" || d=$?; [ "$d" -eq 0 ] || STOP
# Step 2
g=0; k=$(grep -c '^TEST_CASE' tests/test_adapter_claude_collect.cpp) || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 15 ] || STOP; g=0; k2=$(grep -c '^TEST_CASE' tests/test_adapter_codex_collect.cpp) || g=$?; [ "$g" -eq 0 ] && [ "$k2" -eq 25 ] || STOP; printf 'claude_test_cases=%s codex_test_cases=%s\n' "$k" "$k2" > "$EVID/H/test-case-census.txt"
# Step 3
b=0; cmake --build --preset ci-macos > "$EVID/H/build-H.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -r xml > "$EVID/H/biv_tests-pre-commit.xml" 2> "$EVID/H/biv_tests-pre-commit.stderr" || t=$?; printf '%s\n' "$t" > "$EVID/H/biv_tests-pre-commit.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/H/biv_tests-pre-commit.xml" ] || STOP
g=0; k=$(grep -c '<Section name="R-4.49' "$EVID/H/biv_tests-pre-commit.xml") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 9 ] || STOP; printf 'r449_sections_run=%s\n' "$k" > "$EVID/H/sections-run.txt"
# Step 4
w=0; { cat "$EVID/commit-message.txt" && printf '\nDesign pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f (142000 section 2 preserved by reference); C-1/C-2 rulings: pdc master/relays/intg-r449-line1-selection-act/DESIGN-m2-planner-20260913-170000.md\nPlan pin: intg-r449-line1-selection-plan-20260913 sha256 %s\nBase: %s\n' "$(cat "$RUNNERS/plan-lock.txt")" "$B"; } > "$EVID/H/message-C.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H/message-C.txt" ] || STOP
g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-C.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
a=0; git add src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp tests/test_adapter_codex_collect.cpp || a=$?; [ "$a" -eq 0 ] || STOP; c=0; git commit -q -F "$EVID/H/message-C.txt" || c=$?; [ "$c" -eq 0 ] || STOP
C=$(git rev-parse HEAD) || STOP; [ -n "$C" ] && [ "$(git rev-parse "HEAD^")" = "$B" ] || STOP; w=0; printf '%s\n' "$C" > "$EVID/C.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/C.txt" ] || STOP
m=0; git log -1 --format=%B "$C" > "$EVID/H/message-C.committed" || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/H/message-C.committed" ] || STOP; g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-C.committed") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-C.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-C.txt" ] || STOP
# Step 4b
x=0; python3 "$EVID/e3pin_r449.py" harness/bivharness/e3.py src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp > "$EVID/H/repin.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/H/repin.txt" ] || STOP
r=0; git diff --numstat > "$EVID/H/repin.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/repin.numstat" ] || STOP; printf '2\t2\tharness/bivharness/e3.py\n' > "$EVID/H/repin.expected"; d=0; diff "$EVID/H/repin.expected" "$EVID/H/repin.numstat" > "$EVID/H/repin.delta" || d=$?; [ "$d" -eq 0 ] || STOP
w=0; { cat "$EVID/commit-message-harness.txt" && printf '\nLane commit re-pinned to: %s (m-2 fence rev2 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f). Authority: m-3 C-2 rule 4 (143638) — a harness byte the act needs is m-3 surface, routed, under m-3 byte review, one commit; the R-4.50 arm A shape (one PR, two commits, two owners).\nPlan pin: intg-r449-line1-selection-plan-20260913 sha256 %s\n' "$C" "$(cat "$RUNNERS/plan-lock.txt")"; } > "$EVID/H/message-H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H/message-H.txt" ] || STOP
g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-H.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
a=0; git add harness/bivharness/e3.py || a=$?; [ "$a" -eq 0 ] || STOP; c=0; git commit -q -F "$EVID/H/message-H.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 5
H=$(git rev-parse HEAD) || STOP; [ -n "$H" ] && [ "$(git rev-parse "HEAD^")" = "$C" ] && [ "$(git rev-parse "HEAD^^")" = "$B" ] || STOP; w=0; printf '%s\n' "$H" > "$EVID/H.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/H.txt" ] || STOP
m=0; git log -1 --format=%B "$H" > "$EVID/H/message-H.committed" || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/H/message-H.committed" ] || STOP; g=0; k=$(grep -c -F 'Co-Authored-By' "$EVID/H/message-H.committed") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
r=0; git diff --numstat "$B" "$C" > "$EVID/H/touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/touched.numstat" ] || STOP; s=0; awk '{print $3}' "$EVID/H/touched.numstat" > "$EVID/H/touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; LC_ALL=C sort "$EVID/H/touched.paths" > "$EVID/H/touched.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; d=0; diff "$EVID/touched.expected" "$EVID/H/touched.sorted" > "$EVID/H/touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP
r=0; git diff --numstat "$C" "$H" > "$EVID/H/harness.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/H/harness.numstat" ] || STOP; d=0; diff "$EVID/H/repin.expected" "$EVID/H/harness.numstat" > "$EVID/H/harness.delta" || d=$?; [ "$d" -eq 0 ] || STOP
s=0; git status --porcelain > "$EVID/H/status-post-commit.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/H/status-post-commit.txt" ] || STOP
exit 0
