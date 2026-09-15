#!/usr/bin/env bash
# task-1.sh — materialized VERBATIM from the plan's BLOCK task-1 by plan_blocks.py extract; proved by plan_blocks.py check; invoked by run-task.sh 1
set -u
STOP() { printf 'STOP-task-1 line=%s\n' "${BASH_LINENO[0]}" >&2; exit 1; }
RUNNERS=${1-}; [ -n "$RUNNERS" ] && [ -d "$RUNNERS" ] || exit 1
[ "$0" = "$RUNNERS/task-1.sh" ] || { printf 'STOP-task-1-invoked-off-path %s\n' "$0" >&2; exit 1; }
t=0; tail -n 1 "$RUNNERS/proof-1.txt" > "$RUNNERS/task-1.proof-tail" 2>/dev/null || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/task-1.proof-tail")" = rc=0 ] || { printf 'STOP-task-1-unproved\n' >&2; exit 1; }
h=0; shasum -a 256 "$0" > "$RUNNERS/task-1.self.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-1.self.sha256" ] || exit 1
a=$(cut -d' ' -f1 "$RUNNERS/task-1.self.sha256") || exit 1; b=$(cut -d' ' -f1 "$RUNNERS/task-1.sha256") || exit 1; [ -n "$a" ] && [ "$a" = "$b" ] || { printf 'STOP-task-1-bytes-differ\n' >&2; exit 1; }
EVID=${2-}; [ -n "$EVID" ] && [ -d "$EVID" ] || exit 1; [ "$EVID" = "$(cat "$RUNNERS/evid.txt")" ] || exit 1
c=0; cp -p "$RUNNERS/task-1.sh" "$RUNNERS/proof-1.txt" "$RUNNERS/task-1.sha256" "$RUNNERS/task-1.invocation.txt" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
# Runner plumbing (Task 1)
WORKTREE=/Users/jack/Programming/bivpak-intg-r449-line1-selection
MAIN=/Users/jack/Programming/bivpak
B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24
cd "$WORKTREE" || STOP
v=0; (cd "$EVID" && shasum -a 256 -c helpers.sha256 > helpers.verify-1.txt 2>&1) || v=$?; [ "$v" -eq 0 ] || STOP
[ -s "$EVID/observer-unset-names.txt" ] || STOP
OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"
[ "$(git rev-parse HEAD)" = "$B" ] && [ -x build/ci-macos/biv ] || STOP
# Step 1
w=0; printf '20260913\n' > "$EVID/synth-seed.txt" || w=$?; [ "$w" -eq 0 ] && [ -d "$EVID/work" ] || STOP
# Step 2
x=0; python3 "$EVID/synth_store.py" "$EVID/work" "$(cat "$EVID/synth-seed.txt")" > "$EVID/synth-build.log" 2>&1 || x=$?; [ "$x" -eq 0 ] && [ -s "$EVID/work/synth-manifest.json" ] || STOP
c=0; cp -p "$EVID/work/synth-manifest.json" "$EVID/synth-manifest.json" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/synth-manifest.json" ] || STOP
k=0; python3 -c 'import json, sys; m = json.load(open(sys.argv[1])); c = m["counts"]; want = {"codex-bulk": 1500, "codex-garbage-line1": 20, "codex-no-meta": 10, "claude-bulk": 100, "claude-cwd-no-enrichment": 10, "claude-no-cwd": 5}; assert c == want, c; assert len(m["selected"]["codex"]) == 3 and len(m["selected"]["claude"]) == 3, m["selected"]; print("classes ok total_bytes=%d files=%d" % (m["total_bytes"], len(m["files"])))' "$EVID/synth-manifest.json" > "$EVID/synth-classes.txt" || k=$?; [ "$k" -eq 0 ] && [ -s "$EVID/synth-classes.txt" ] || STOP
w=0; git show "${B}:harness/bivharness/scenario.py" > "$EVID/scenario-B.py" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/scenario-B.py" ] || STOP; o=0; grep -o -E '[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}' "$EVID/scenario-B.py" > "$EVID/poison-ids.txt" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/poison-ids.txt" ] || STOP; g=0; k=$(grep -c -F -f "$EVID/poison-ids.txt" "$EVID/synth-manifest.json") || g=$?; [ "$g" -eq 1 ] && [ "$k" -eq 0 ] || STOP
w=0; printf 'HOME=%s/work/home\nCODEX_HOME=%s/work/codex-home\nCLAUDE_CONFIG_DIR=%s/work/claude-config\nTMPDIR=%s/work/tmp\nsource=%s/work/ws/proj\n' "$EVID" "$EVID" "$EVID" "$EVID" "$EVID" > "$EVID/locators.txt" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/locators.txt" ] || STOP
# Step 3
p=0; "${OBS_ENV[@]}" python3 "$EVID/pack_run.py" "$WORKTREE/build/ci-macos/biv" "$EVID/work" B "$EVID/B" > "$EVID/B/pack-run.log" 2>&1 || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/B/pack-B.json" ] && [ -s "$EVID/B/time-B.txt" ] && [ -s "$EVID/work/ws/proj-B.bvpk" ] || STOP
m=0; python3 "$EVID/membership.py" "$EVID/work/ws/proj-B.bvpk" "$EVID/B/membership-B.json" > "$EVID/B/membership-B.log" 2>&1 || m=$?; [ "$m" -eq 0 ] && [ -s "$EVID/B/membership-B.json" ] || STOP
g=0; k=$(grep -c -F -- ' "count": 6,' "$EVID/B/membership-B.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -F 'SessionNoCwdRecord' "$EVID/B/pack-B.json") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 5 ] || STOP; printf 'no_cwd_record_warnings=%s\n' "$k" > "$EVID/B/no-cwd-count.txt"
s=0; git status --porcelain > "$EVID/status-post-1.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-1.txt" ] || STOP
s=0; git -C "$MAIN" status --porcelain -- . ':(exclude).relays' ':(exclude)docs/sprints' > "$EVID/status-main-post-1.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-1.txt" > "$EVID/status-main-post-1.delta" || d=$?; [ "$d" -eq 0 ] || STOP
exit 0
