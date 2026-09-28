#!/usr/bin/env bash
# rev44 walk: resume.sh (rev44 BLOCK, c325718c) from a mirror of the pointer's directory (s2b-runners-j6w4EX: impl-15's task-9.done AND its failed task-10 records), the REAL t-oracle.txt / task-10-go.txt bytes, the rev44 lock, token impl-16
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r44
W=$S/rw; RS=$S/resume44.sh; PLAN=/Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; NEWLOCK=$(shasum -a 256 "$PLAN" | cut -d' ' -f1)
REAL_E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; REAL_R=$(cat "$REAL_E/runners-dir.txt")
ROOT=/Users/jack/Programming/bivpak-evidence; TOK=intg-substep2b-impl-16
echo "canonical=$REAL_R newlock=${NEWLOCK:0:16}"
mirror() { local d=$W/$1; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d/evid/runners" "$d/evid/code" "$d/old"
  for f in "$REAL_R"/*; do [ -f "$f" ] && cp -p "$f" "$d/old/"; done
  cp -Rp "$REAL_E"/runners/. "$d/evid/runners/"; printf '%s\n' "$d/old" > "$d/evid/runners-dir.txt"; printf '%s\n' "$d/evid" > "$d/old/evid.txt"; printf '%s\n' "$PLAN" > "$d/old/plan-path.txt"; cp -p "$d/evid/runners-dir.txt" "$d/ptr.before"; }
cnt() { ls -d "$ROOT"/s2b-runners-* 2>/dev/null | wc -l | tr -d ' '; }
run() { local d=$W/$1; local b; b=$(cnt); out=$(bash "$RS" "$d/evid" "$2" "$3" 2> "$d/err.txt"); rc=$?; local a; a=$(cnt)
  echo "$1 rc=$rc stderr=$(tail -1 "$d/err.txt" | cut -c1-80) new-dirs=$((a-b)) pointer-same=$(cmp -s "$d/ptr.before" "$d/evid/runners-dir.txt" && echo yes || echo no)" >&2; printf '%s' "$out"; }
mirror yes; d=$W/yes; cmp -s "$REAL_R/t-oracle.txt" "$d/old/t-oracle.txt" && echo "mirror t-oracle.txt == real ($(grep -c -x -F "plan_sha256=$NEWLOCK" "$d/old/t-oracle.txt") new-lock line)"
NEW=$(run yes "$NEWLOCK" $TOK)
if [ -n "$NEW" ] && [ -d "$NEW" ]; then
  echo "  published: pointer=$([ "$(cat "$d/evid/runners-dir.txt")" = "$NEW" ] && echo NEW || echo OTHER) carried-lines=$(wc -l < "$NEW/carried.sha256" | tr -d ' ') task-9.done=$(cat "$NEW/task-9.done") lock=$(cut -c1-16 "$NEW/plan-lock.txt") token=$(cat "$NEW/token-id.txt")"
  bad=0; for f in $(awk '{print $2}' "$NEW/carried.sha256"); do cmp -s "$NEW/$f" "$d/old/$f" || bad=$((bad+1)); done; echo "  carried files byte-equal to the old dir: $([ $bad -eq 0 ] && echo all || echo "$bad DIFFER")"
  echo "  carried: t-oracle.txt=$(grep -c ' t-oracle.txt$' "$NEW/carried.sha256") task-10-go.txt=$(grep -c ' task-10-go.txt$' "$NEW/carried.sha256")"
  echo "  task-10 records in the NEW dir (one-shot fence inputs): $(ls "$NEW" | grep -c -E '^task-10\.(done|sh|exit)$')"
  echo "  NEW path has no symlinked component: $([ "$(cd "$NEW" && pwd -P)" = "$NEW" ] && echo yes || echo NO)"
  rm -rf "$NEW"
fi
mirror stale-oracle; chmod u+w "$W/stale-oracle/old/t-oracle.txt"; cp -p "$REAL_R"/t-oracle.prev-20260927-202507.txt "$W/stale-oracle/old/t-oracle.txt"; run stale-oracle "$NEWLOCK" $TOK >/dev/null
echo "real pointer unchanged: $(cat "$REAL_E/runners-dir.txt")"
