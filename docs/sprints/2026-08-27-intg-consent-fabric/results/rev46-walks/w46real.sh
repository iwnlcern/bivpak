#!/usr/bin/env bash
# rev46 PRE-TOKEN walk on the REAL state (live plan, real t-oracle.txt unedited): resume.sh (rev46 BLOCK e0b5eed5) from mirrors of the REAL s2b-runners-V1jS1t (impl-16's task-10.done rc=0), lock = the rev46 artifact (scratch), token impl-17; YES continues into the sealed controller `run-task.sh 11` from the NEW directory against a full APFS clone of $EVID whose helper `cells.py` is tampered so Task 11's body STOPs at its helpers line (no RESDIR write into the real MAIN)
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r46
W=$S/rw; RS=$S/resume-live.sh; PLAN=/Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; NEWLOCK=$(shasum -a 256 "$PLAN" | cut -d' ' -f1)
REAL_E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; REAL_R=$(cat "$REAL_E/runners-dir.txt"); ROOT=/Users/jack/Programming/bivpak-evidence; TOK=intg-substep2b-impl-17
echo "canonical=$REAL_R newlock=${NEWLOCK:0:16}"
cnt() { ls -d "$ROOT"/s2b-runners-* 2>/dev/null | wc -l | tr -d ' '; }
mirror() { local d=$W/$1 full=${2-}; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d/old"
  if [ -n "$full" ]; then cp -cRp "$REAL_E" "$d/evid" || exit 9; else mkdir -p "$d/evid/runners" "$d/evid/code"; cp -Rp "$REAL_E"/runners/. "$d/evid/runners/"; fi
  for f in "$REAL_R"/*; do [ -f "$f" ] && cp -p "$f" "$d/old/"; done
  chmod u+w "$d/evid/runners-dir.txt" 2>/dev/null; printf '%s\n' "$d/old" > "$d/evid/runners-dir.txt"; printf '%s\n' "$d/evid" > "$d/old/evid.txt"; printf '%s\n' "$PLAN" > "$d/old/plan-path.txt"
  cmp -s "$REAL_R/t-oracle.txt" "$d/old/t-oracle.txt" || exit 8; cp -p "$d/evid/runners-dir.txt" "$d/ptr.before"; }
run() { local d=$W/$1; local b; b=$(cnt); out=$(bash "$RS" "$d/evid" "$NEWLOCK" "$TOK" 2> "$d/err.txt"); rc=$?; local a; a=$(cnt)
  echo "$1 rc=$rc stderr=$(tail -1 "$d/err.txt" | cut -c1-70) new-dirs=$((a-b)) pointer-same=$(cmp -s "$d/ptr.before" "$d/evid/runners-dir.txt" && echo yes || echo no)" >&2; printf '%s' "$out"; }
echo "(the mirror t-oracle.txt is the real published file, byte-equal)"
mirror yes full; d=$W/yes; chmod u+w "$d/evid/cells.py"; printf '# tampered by the walk\n' >> "$d/evid/cells.py"
NEW=$(run yes)
if [ -n "$NEW" ] && [ -d "$NEW" ]; then
  echo "  owner search (Task 10): $(for td in "$d"/evid/runners/intg-substep2b-impl-*/task-10; do m=1; for f in task-10.sh proof-10.txt task-10.sha256 task-10.invocation.txt; do cmp -s "$d/old/$f" "$td/$f" || m=0; done; [ $m -eq 1 ] && basename "$(dirname "$td")"; done | tr "\n" " ")"
  echo "  NEW ${NEW##*/}: carried-lines=$(wc -l < "$NEW/carried.sha256" | tr -d ' ') task-9.done=$(cat "$NEW/task-9.done") task-10.done=$(cat "$NEW/task-10.done" 2>/dev/null || echo ABSENT) task-10 receipts carried=$(grep -c -E ' (task-10\.|proof-10\.|plan-hash-10|plan_blocks\.sha256-10)' "$NEW/carried.sha256")"
  bad=0; for f in $(awk '{print $2}' "$NEW/carried.sha256"); do cmp -s "$NEW/$f" "$d/old/$f" || bad=$((bad+1)); done; echo "  carried byte-equal: $([ $bad -eq 0 ] && echo all || echo "$bad DIFFER")"
  "$NEW/run-task.sh" 11 > "$d/ctl.out" 2>&1; echo "  controller task 11 rc=$? : $(tr '\n' ' ' < "$d/ctl.out" | cut -c1-160)"
  echo "  proof-11 tail: $(cat "$NEW/proof-11.tail" 2>/dev/null) task-11.exit: $(cat "$NEW/task-11.exit" 2>/dev/null) prologue record: $(ls "$d/evid/runners/$TOK/task-11" 2>/dev/null | tr '\n' ' ') helpers.verify-11 FAILED lines: $(grep -c 'FAILED' "$d/evid/helpers.verify-11.txt" 2>/dev/null)"
  echo "  real MAIN results dir absent: $([ ! -e /Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1 ] && echo yes)"
  rm -rf "$NEW"
fi
echo "leftover walk dirs: $(ls -d "$ROOT"/s2b-runners-* | grep -v -E 'NCDBlS|PEazOQ|QzzQ11|P7xJDh|4BSBek|Xi2bWL|IvrESr|sK9rhy|aY2Suc|UG0MP0|r9Akl6|dv8k9v|j6w4EX|V1jS1t' | wc -l | tr -d ' ')  real pointer: $(cat "$REAL_E/runners-dir.txt")"
