#!/usr/bin/env bash
# task-0.sh — materialized VERBATIM from the plan's BLOCK task-0 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 0
set -u
STOP() { printf 'STOP-task-0 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-0.sh" ] || { printf 'STOP-task-0-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-0.txt" > "$RUNNERS/task-0.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-0.proof-tail")" = rc=0 ] || { printf 'STOP-task-0-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-0.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-0.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-0.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-0.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-0-bytes-differ\n' >&2; exit 1; }
# Runner plumbing (Task 0)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
OLDWT=/Users/jack/Programming/bivpak-intg-r450-discover-parity
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
cd "$MAIN" || STOP
# Step 0
TOKEN=$(cat "$RUNNERS/token-id.txt") || STOP; [ -n "$TOKEN" ] || STOP
m=0; mkdir -p "$HOME/Programming/bivpak-evidence" || m=$?; [ "$m" -eq 0 ] && [ -d "$HOME/Programming/bivpak-evidence" ] || STOP
EVID_RAW=$(mktemp -d "$HOME/Programming/bivpak-evidence/r449-${TOKEN}-XXXXXX") || STOP
EVID=$(cd "$EVID_RAW" && pwd -P) || STOP
[ -d "$EVID" ] && [ "$EVID" = "$EVID_RAW" ] || STOP
case "$EVID/" in /var/folders/*|/private/var/folders/*|/tmp/*|/private/tmp/*) echo STOP-evid-in-temp-root; exit 1;; esac
case "$EVID/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac
m=0; mkdir "$EVID/runners" "$EVID/B" "$EVID/H" "$EVID/work" "$EVID/census-raw" || m=$?; [ "$m" -eq 0 ] && [ -d "$EVID/runners" ] && [ -d "$EVID/work" ] || STOP
w=0; printf '%s\n' "$EVID" > "$RUNNERS/evid.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$RUNNERS/evid.txt" ] || STOP; w=0; printf '%s\n' "$RUNNERS" > "$EVID/runners-dir.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/runners-dir.txt" ] || STOP
c=0; cp -p "$RUNNERS/task-0.sh" "$RUNNERS/proof-0.txt" "$RUNNERS/task-0.sha256" "$RUNNERS/task-0.invocation.txt" "$RUNNERS/plan_blocks.py" "$RUNNERS/run-task.sh" "$RUNNERS/run-task.sha256" "$RUNNERS/blocks.txt" "$RUNNERS/plan-lock.txt" "$RUNNERS/plan-path.txt" "$RUNNERS/plan-hash-0.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || STOP
w=0; printf 'token=%s\nevid=%s\n' "$TOKEN" "$EVID" > "$EVID/token.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/token.txt" ] || STOP
s0=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP
# Step 0b
for name in cells tuples cellgate skipset selftest_summary finalize synth_store membership readtrace_reduce leg12_verdict pack_run hunkwin head_reader_claude head_reader_codex tests_claude_r449 tests_codex_r449 e3pin_r449; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name.py" > "$EVID/$name.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name.py" ] || STOP; k=0; python3 -m py_compile "$EVID/$name.py" || k=$?; [ "$k" -eq 0 ] || STOP; done
for name in linux-container.sh linux-suite.sh; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name" > "$EVID/$name" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name" ] || STOP; s=0; bash -n "$EVID/$name" || s=$?; [ "$s" -eq 0 ] || STOP; done
for name in commit-message.txt commit-message-harness.txt readtrace.c; do x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "$name" > "$EVID/$name" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/$name" ] || STOP; done
h=0; (cd "$EVID" && shasum -a 256 cells.py tuples.py cellgate.py skipset.py selftest_summary.py finalize.py synth_store.py membership.py readtrace_reduce.py leg12_verdict.py pack_run.py hunkwin.py head_reader_claude.py head_reader_codex.py tests_claude_r449.py tests_codex_r449.py e3pin_r449.py linux-container.sh linux-suite.sh commit-message.txt commit-message-harness.txt readtrace.c > helpers.sha256) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/helpers.sha256" ] || STOP
x=0; python3 "$RUNNERS/plan_blocks.py" list "$PLAN" > "$EVID/blocks.txt" || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/blocks.txt" ] || STOP; c=0; cmp "$EVID/blocks.txt" "$RUNNERS/blocks.txt" || c=$?; [ "$c" -eq 0 ] || STOP
# Step 1
f=0; git -C "$MAIN" fetch --no-tags origin refs/heads/main:refs/remotes/origin/main || f=$?; [ "$f" -eq 0 ] || STOP
BASE=$(git -C "$MAIN" rev-parse origin/main) || STOP; [ "$BASE" = "$B" ] || STOP
w=0; git -C "$MAIN" show "${B}:.github/workflows/s2-harness.yml" > "$EVID/B-workflow.yml" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/B-workflow.yml" ] || STOP
c=0; python3 "$EVID/cells.py" "$EVID/B-workflow.yml" > "$EVID/B-cells.txt" || c=$?; printf 'cells_B_rc=%s\n' "$c" > "$EVID/B-cells.rc"; [ "$c" -eq 0 ] && [ -s "$EVID/B-cells.txt" ] || STOP
printf 'B=%s\n' "$BASE" > "$EVID/B.txt"
s=0; sed -n '167,174p' "$EVID/B-workflow.yml" > "$EVID/llvm-manifest-source.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest-source.txt" ] || STOP; s=0; sed 's/^          //' "$EVID/llvm-manifest-source.txt" > "$EVID/llvm-manifest.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/llvm-manifest.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/llvm-manifest.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 8 ] || STOP; g=0; k=$(grep -c -E '^[0-9a-f]{64} [a-z0-9-]+ [A-Za-z0-9._+~-]+\.deb$' "$EVID/llvm-manifest.txt") || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 8 ] || STOP
for p in src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp tests/test_adapter_codex_collect.cpp harness/bivharness/e3.py; do w=0; git -C "$MAIN" show "${B}:${p}" > "$EVID/base-$(basename "$p")" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/base-$(basename "$p")" ] || STOP; done; h=0; (cd "$EVID" && shasum -a 256 base-claude_code.cpp base-codex.cpp base-test_adapter_claude_collect.cpp base-test_adapter_codex_collect.cpp base-e3.py > base-hashes.txt) || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/base-hashes.txt" ] || STOP
# Step 2
[ -d "$OLDWT" ] || STOP; [ "$(git -C "$OLDWT" rev-parse HEAD)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP; [ "$(git -C "$OLDWT" rev-parse --abbrev-ref HEAD)" = intg/r450-discover-parity-v2 ] || STOP
s=0; git -C "$OLDWT" status --porcelain > "$EVID/oldwt-status.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/oldwt-status.txt" ] || STOP
[ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity)" = 8509157c41c5ef66595d655f39eee5107081bd32 ] && [ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity-v2)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP
l=0; git -C "$MAIN" ls-remote --heads origin intg/r450-discover-parity intg/r450-discover-parity-v2 > "$EVID/oldwt-remote-refs.txt" || l=$?; [ "$l" -eq 0 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/oldwt-remote-refs.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 2 ] || STOP
w=0; git -C "$MAIN" worktree remove "$OLDWT" > "$EVID/worktree-remove.log" 2>&1 || w=$?; [ "$w" -eq 0 ] && [ ! -e "$OLDWT" ] || STOP
[ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity)" = 8509157c41c5ef66595d655f39eee5107081bd32 ] && [ "$(git -C "$MAIN" rev-parse refs/heads/intg/r450-discover-parity-v2)" = e8a1128d75cd4693d21269c4d040095df570f116 ] || STOP
l=0; git -C "$MAIN" worktree list > "$EVID/worktree-list-after.txt" || l=$?; [ "$l" -eq 0 ] && [ -s "$EVID/worktree-list-after.txt" ] || STOP; g=0; k=$(grep -c -F -- "$OLDWT" "$EVID/worktree-list-after.txt") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
w=0; printf 'disposed=%s head_was=e8a1128d75cd4693d21269c4d040095df570f116 branch_was=intg/r450-discover-parity-v2 remove_rc=0 refs_unchanged=yes remote_heads=%s\n' "$OLDWT" "$n" > "$EVID/worktree-dispose.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/worktree-dispose.txt" ] || STOP
# Step 3
e=0; git -C "$MAIN" show-ref --verify -q refs/heads/intg/r449-line1-selection || e=$?; [ "$e" -ne 0 ] || STOP
l=0; git -C "$MAIN" ls-remote --heads origin intg/r449-line1-selection > "$EVID/remote-branch-initial.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-initial.txt" ] || STOP
[ ! -e "$WORKTREE" ] || STOP
a=0; git -C "$MAIN" worktree add -b intg/r449-line1-selection "$WORKTREE" "$B" > "$EVID/worktree-add.log" 2>&1 || a=$?; [ "$a" -eq 0 ] && [ -d "$WORKTREE" ] || STOP
cd "$WORKTREE" || STOP
[ "$(git rev-parse HEAD)" = "$B" ] && [ "$(git rev-parse --abbrev-ref HEAD)" = intg/r449-line1-selection ] || STOP
s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-worktree-0.txt" ] || STOP
c=0; n=$(git rev-list --count origin/main..HEAD) || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 0 ] || STOP; w=0; printf 'unpublished_commits_in_lineage=%s expected=0 cut_point=%s\n' "$n" "$B" > "$EVID/cutpoint.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/cutpoint.txt" ] || STOP
g=0; git check-ignore -q .venv-harness/ || g=$?; g2=0; git check-ignore -q build/ || g2=$?; printf 'venv_ignored_rc=%s build_ignored_rc=%s\n' "$g" "$g2" > "$EVID/ignore-proof.txt"; [ "$g" -eq 0 ] && [ "$g2" -eq 0 ] || STOP
# Step 4
v=0; /opt/homebrew/bin/python3.12 -m venv .venv-harness || v=$?; [ "$v" -eq 0 ] && [ -x .venv-harness/bin/python ] || STOP; i=0; .venv-harness/bin/python -m pip install -q -r harness/requirements.lock > "$EVID/venv-pip.log" 2>&1 || i=$?; [ "$i" -eq 0 ] || STOP
m=0; .venv-harness/bin/python -c 'import pytest, jsonschema, zstandard; print("imported", pytest.__name__, jsonschema.__name__, zstandard.__name__)' > "$EVID/venv-imports.txt" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/venv-imports.txt" ] || STOP
p=0; .venv-harness/bin/python --version > "$EVID/venv-python.txt" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/venv-python.txt" ] || STOP
s=0; git status --porcelain > "$EVID/status-post-venv.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-venv.txt" ] || STOP
b=0; cmake --preset ci-macos > "$EVID/B/configure-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP
g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] && [ "$k" -eq 1 ] || STOP; printf 'cache_k=%s\n' "$k" > "$EVID/B/cache-proof.txt"
b=0; cmake --build --preset ci-macos > "$EVID/B/build-B.log" 2>&1 || b=$?; [ "$b" -eq 0 ] && [ -x build/ci-macos/biv ] || STOP
# Step 5
n=0; (cd harness && ../.venv-harness/bin/python -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt" || n=$?; [ "$n" -eq 0 ] && [ -s "$EVID/observer-unset-names.txt" ] || STOP
g=0; k=$(grep -c -E '^[A-Z][A-Z0-9_]+$' "$EVID/observer-unset-names.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -ge 1 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/observer-unset-names.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq "$k" ] || STOP
while read -r n; do if printenv "$n" > /dev/null; then echo "$n present"; else echo "$n absent"; fi; done < "$EVID/observer-unset-names.txt" > "$EVID/observer-host-presence.txt"; [ -s "$EVID/observer-host-presence.txt" ] || STOP
g=0; present_count=$(grep -c present "$EVID/observer-host-presence.txt") || g=$?; [ "$g" -le 1 ] || STOP; printf 'present_count=%s\n' "$present_count" > "$EVID/observer-present-count.txt"
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
# Step 6
for binary in biv_subprocess_tests biv_repo_git_tests biv_repo_engine_tests biv_tests biv_probe_tests; do x=0; "${OBS_ENV[@]}" "./build/ci-macos/$binary" -r xml > "$EVID/B/$binary-macos.xml" 2> "$EVID/B/$binary-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/B/$binary-macos.rc"; [ -s "$EVID/B/$binary-macos.xml" ] || STOP; done
u=0; python3 "$EVID/tuples.py" macos "$EVID"/B/biv_subprocess_tests-macos.xml "$EVID"/B/biv_repo_git_tests-macos.xml "$EVID"/B/biv_repo_engine_tests-macos.xml "$EVID"/B/biv_tests-macos.xml "$EVID"/B/biv_probe_tests-macos.xml > "$EVID/B/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/B/tuples-macos.txt" ] || STOP
q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/B/tuples-macos.txt" macos > "$EVID/B/skipset-macos.txt" || q=$?; [ "$q" -eq 0 ] && [ -s "$EVID/B/skipset-macos.txt" ] || STOP
s=0; git status --porcelain > "$EVID/status-post-B.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-B.txt" ] || STOP
exit 0
