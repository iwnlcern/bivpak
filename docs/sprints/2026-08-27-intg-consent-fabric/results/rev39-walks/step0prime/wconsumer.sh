#!/usr/bin/env bash
# rev39 walk: resume.sh (rev39's BLOCK) from a mirror of the pointer's directory (s2b-runners-UG0MP0, holding impl-12's task-9.done), with the rev39 lock
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r39
W=$S/w/rw; RS=$S/b/resume.sh; PLAN=$S/rev39.md; NEWLOCK=$(shasum -a 256 "$PLAN" | cut -d' ' -f1)
REAL_E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; REAL_R=$(cat "$REAL_E/runners-dir.txt")
ROOT=/Users/jack/Programming/bivpak-evidence; TOK=intg-substep2b-impl-13
echo "canonical=$REAL_R newlock=${NEWLOCK:0:16}"
mirror() { local d=$W/$1; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d/evid/runners" "$d/evid/code" "$d/old"
  for f in "$REAL_R"/*; do [ -f "$f" ] && cp -p "$f" "$d/old/"; done
  cp -Rp "$REAL_E"/runners/. "$d/evid/runners/"; printf '%s\n' "$d/old" > "$d/evid/runners-dir.txt"; printf '%s\n' "$d/evid" > "$d/old/evid.txt"; printf '%s\n' "$PLAN" > "$d/old/plan-path.txt"
  chmod u+w "$d/old/t-oracle.txt"; sed -i '' -E "s/^plan_sha256=[0-9a-f]{64}$/plan_sha256=$NEWLOCK/" "$d/old/t-oracle.txt"; cp -p "$d/evid/runners-dir.txt" "$d/ptr.before"; }
cnt() { ls -d "$ROOT"/s2b-runners-* 2>/dev/null | wc -l | tr -d ' '; }
run() { local d=$W/$1; local b; b=$(cnt); out=$(bash "$RS" "$d/evid" "$2" "$3" 2> "$d/err.txt"); rc=$?; local a; a=$(cnt)
  echo "$1 rc=$rc stderr=$(tail -1 "$d/err.txt" | cut -c1-70) new-dirs=$((a-b)) pointer-same=$(cmp -s "$d/ptr.before" "$d/evid/runners-dir.txt" && echo yes || echo no)" >&2; printf '%s' "$out"; }
verify() { local d=$1 NEW=$2 want=$3
  echo "  published: pointer=$([ "$(cat "$d/evid/runners-dir.txt")" = "$NEW" ] && echo NEW || echo OTHER) carried-lines=$(wc -l < "$NEW/carried.sha256" | tr -d ' ') (want $want) task-9.done=$(cat "$NEW/task-9.done" 2>/dev/null || echo absent) lock=$(cut -c1-16 "$NEW/plan-lock.txt") token=$(cat "$NEW/token-id.txt")"
  local bad=0; for f in $(awk '{print $2}' "$NEW/carried.sha256"); do cmp -s "$NEW/$f" "$d/old/$f" || bad=$((bad+1)); done; echo "  carried files byte-equal to the old dir: $([ $bad -eq 0 ] && echo all || echo "$bad DIFFER")"
  printf '  carried t-oracle names the new lock: %s\n' "$(grep -c -x -F "plan_sha256=$NEWLOCK" "$NEW/t-oracle.txt")"
  printf '  task-9.sh mode: %s\n' "$(stat -f %Lp "$NEW/task-9.sh" 2>/dev/null || echo none)"
  o=$("$NEW/run-task.sh" 10 2>&1); echo "  consumer run-task.sh 10: rc=$? $(echo "$o" | tail -1 | cut -c1-80)"; rm -rf "$NEW"; }
mirror yes; d=$W/yes; NEW=$(run yes "$NEWLOCK" $TOK); [ -n "$NEW" ] && [ -d "$NEW" ] && verify "$d" "$NEW" 31
mirror no9; d=$W/no9; rm -f "$d"/old/task-9.* "$d"/old/proof-9.* "$d"/old/plan-hash-9.txt "$d"/old/plan_blocks.sha256-9; NEW=$(run no9 "$NEWLOCK" $TOK); [ -n "$NEW" ] && [ -d "$NEW" ] && verify "$d" "$NEW" 20
echo "leftover new dirs: $(ls -d "$ROOT"/s2b-runners-* | grep -v -E "NCDBlS|PEazOQ|QzzQ11|P7xJDh|4BSBek|Xi2bWL|IvrESr|sK9rhy|aY2Suc|UG0MP0" | wc -l | tr -d ' ')  real pointer: $(cat "$REAL_E/runners-dir.txt")"
