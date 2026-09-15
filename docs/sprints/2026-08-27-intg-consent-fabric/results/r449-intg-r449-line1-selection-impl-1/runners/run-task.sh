#!/usr/bin/env bash
# run-task.sh N — the CONTROLLER (protocol (a)–(c)): authenticate itself and the extractor against the lock-verified plan, materialize task-N.sh from the plan's RUN blocks, prove it, fix its mode and digest, invoke it BY PATH, record the exit.
set -u
N=${1-}
case "$N" in 0|1|2|3|4|5|6|7) ;; *) printf 'usage: run-task.sh N (0..7)\n' >&2; exit 2;; esac
RUNNERS=$(cd "$(dirname "$0")" && pwd -P) || exit 1
[ "$0" = "$RUNNERS/run-task.sh" ] || { printf 'STOP-controller-invoked-off-path %s\n' "$0" >&2; exit 1; }
STOP() { printf 'STOP-controller-task-%s line=%s\n' "$N" "${BASH_LINENO[0]}" >&2; exit 1; }
PLAN=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLAN" ] || STOP
h=0; shasum -a 256 "$PLAN" > "$RUNNERS/plan-hash-$N.txt" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan-hash-$N.txt" ] || STOP
d=$(cut -d' ' -f1 "$RUNNERS/plan-hash-$N.txt") || STOP; e=$(cat "$RUNNERS/plan-lock.txt") || STOP; [ -n "$d" ] && [ "$d" = "$e" ] || STOP
bx() { python3 -c 'import sys; t = open(sys.argv[1], encoding="utf-8").read(); m = "<!-- BLOCK: " + sys.argv[2] + " -->\n"; i = t.index(m) + len(m); j = t.index("\n", i) + 1; k = t.index("\n" + chr(96) * 3 + "\n", j); sys.stdout.write(t[j:k + 1])' "$PLAN" "$1"; }
x=0; bx run-task.sh > "$RUNNERS/run-task.fresh-$N.sh" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/run-task.fresh-$N.sh" ] || STOP; c=0; cmp "$0" "$RUNNERS/run-task.fresh-$N.sh" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-not-the-plan-bytes\n' "$N" >&2; exit 1; }
x=0; bx plan_blocks.py > "$RUNNERS/plan_blocks.fresh-$N.py" || x=$?; [ "$x" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.fresh-$N.py" ] || STOP; c=0; cmp "$RUNNERS/plan_blocks.py" "$RUNNERS/plan_blocks.fresh-$N.py" || c=$?; [ "$c" -eq 0 ] || { printf 'STOP-controller-task-%s-extractor-not-the-plan-bytes\n' "$N" >&2; exit 1; }
h=0; shasum -a 256 "$RUNNERS/plan_blocks.py" > "$RUNNERS/plan_blocks.sha256-$N" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/plan_blocks.sha256-$N" ] || STOP
if [ "$N" -gt 0 ]; then M=$((N - 1)); [ -s "$RUNNERS/task-$M.done" ] && [ "$(cat "$RUNNERS/task-$M.done")" = rc=0 ] || STOP; fi
[ ! -e "$RUNNERS/task-$N.done" ] && [ ! -e "$RUNNERS/task-$N.sh" ] && [ ! -e "$RUNNERS/task-$N.exit" ] || STOP
if [ "$N" -eq 6 ]; then [ -s "$RUNNERS/task-6-go.txt" ] || { printf 'STOP-controller-task-6-no-continuation\n' >&2; exit 1; }; a=0; ng=$(awk 'END { print NR }' "$RUNNERS/task-6-go.txt") || a=$?; [ "$a" -eq 0 ] && [ "$ng" -eq 1 ] || { printf 'STOP-controller-task-6-continuation-not-one-line\n' >&2; exit 1; }; GOP=$(sed -n '1p' "$RUNNERS/task-6-go.txt") || STOP; case "$GOP" in /*) GOF=$GOP;; *) GOF=$(cd "$(dirname "$PLAN")/../../../.." && pwd -P)/$GOP;; esac; [ -s "$GOF" ] || { printf 'STOP-controller-task-6-continuation-target-missing\n' >&2; exit 1; }; fi
m=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLAN" "task-$N" > "$RUNNERS/task-$N.sh" || m=$?; [ "$m" -eq 0 ] && [ -s "$RUNNERS/task-$N.sh" ] || STOP
c=0; python3 "$RUNNERS/plan_blocks.py" check "$PLAN" "$N" "$RUNNERS/task-$N.sh" > "$RUNNERS/proof-$N.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$RUNNERS/proof-$N.txt" ] || STOP
t=0; tail -n 1 "$RUNNERS/proof-$N.txt" > "$RUNNERS/proof-$N.tail" || t=$?; [ "$t" -eq 0 ] && [ "$(cat "$RUNNERS/proof-$N.tail")" = rc=0 ] || STOP
s=0; bash -n "$RUNNERS/task-$N.sh" || s=$?; [ "$s" -eq 0 ] || STOP
chmod 0500 "$RUNNERS/task-$N.sh" || STOP; [ -x "$RUNNERS/task-$N.sh" ] || STOP
h=0; shasum -a 256 "$RUNNERS/task-$N.sh" > "$RUNNERS/task-$N.sha256" || h=$?; [ "$h" -eq 0 ] && [ -s "$RUNNERS/task-$N.sha256" ] || STOP
if [ "$N" -eq 0 ]; then EVID=; printf '"%s/task-0.sh" "%s"\n' "$RUNNERS" "$RUNNERS" > "$RUNNERS/task-0.invocation.txt" || STOP; else EVID=$(cat "$RUNNERS/evid.txt") || STOP; [ -d "$EVID" ] || STOP; printf '"%s/task-%s.sh" "%s" "%s"\n' "$RUNNERS" "$N" "$RUNNERS" "$EVID" > "$RUNNERS/task-$N.invocation.txt" || STOP; fi
r=0; if [ "$N" -eq 0 ]; then "$RUNNERS/task-0.sh" "$RUNNERS" || r=$?; else "$RUNNERS/task-$N.sh" "$RUNNERS" "$EVID" || r=$?; fi
printf 'rc=%s\n' "$r" > "$RUNNERS/task-$N.exit" || exit 1
[ "$r" -eq 0 ] || { printf 'task-%s exited %s — STOP; the token ends here\n' "$N" "$r" >&2; exit 1; }
printf 'rc=0\n' > "$RUNNERS/task-$N.done" || exit 1
EVID=$(cat "$RUNNERS/evid.txt") || exit 1; c=0; cp -p "$RUNNERS/task-$N.done" "$RUNNERS/task-$N.exit" "$RUNNERS/proof-$N.tail" "$RUNNERS/plan_blocks.sha256-$N" "$EVID/runners/" || c=$?; [ "$c" -eq 0 ] || exit 1
printf 'task-%s done rc=0\n' "$N"
