#!/usr/bin/env bash
# rev45 walk: Step 0' (resume.sh c325718c) from a mirror of the REAL s2b-runners-V1jS1t (impl-16's task-10.done rc=0), the rev45 lock, token impl-17; THEN the sealed controller for Task 11 from the NEW directory (it STOPs before any task body if its preconditions fail)
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r45
W=$S/rw; RS=$S/resume45.sh; PLAN=/Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; NEWLOCK=$(shasum -a 256 "$PLAN" | cut -d' ' -f1)
REAL_E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; REAL_R=$(cat "$REAL_E/runners-dir.txt"); TOK=intg-substep2b-impl-17
echo "canonical=$REAL_R newlock=${NEWLOCK:0:16} old task-10.done=$(cat "$REAL_R/task-10.done")"
d=$W/yes; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d/evid/runners" "$d/evid/code" "$d/old"
for f in "$REAL_R"/*; do [ -f "$f" ] && cp -p "$f" "$d/old/"; done
cp -Rp "$REAL_E"/runners/. "$d/evid/runners/"; printf '%s\n' "$d/old" > "$d/evid/runners-dir.txt"; printf '%s\n' "$d/evid" > "$d/old/evid.txt"; printf '%s\n' "$PLAN" > "$d/old/plan-path.txt"
NEW=$(bash "$RS" "$d/evid" "$NEWLOCK" "$TOK" 2> "$d/err.txt"); echo "resume rc=$? stderr=$(tail -1 "$d/err.txt" | cut -c1-80) NEW=${NEW##*/}"
[ -n "$NEW" ] && [ -d "$NEW" ] || exit 1
echo "  NEW: carried-lines=$(wc -l < "$NEW/carried.sha256" | tr -d ' ') lock=$(cut -c1-16 "$NEW/plan-lock.txt") token=$(cat "$NEW/token-id.txt") task-9.done=$(cat "$NEW/task-9.done" 2>/dev/null || echo absent) task-10.done=$(cat "$NEW/task-10.done" 2>/dev/null || echo ABSENT)"
"$NEW/run-task.sh" 11 > "$d/ctl.out" 2>&1; echo "controller task 11 rc=$? : $(tail -1 "$d/ctl.out")"
echo "  task-11.sh created: $([ -e "$NEW/task-11.sh" ] && echo yes || echo no)"
rm -rf "$NEW"; echo "walk dir removed; real pointer: $(cat "$REAL_E/runners-dir.txt")"
