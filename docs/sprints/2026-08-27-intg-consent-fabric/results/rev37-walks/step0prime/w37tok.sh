#!/usr/bin/env bash
# Step 0' walk (rev37, before filing; the carry's t-oracle rewrite SIMULATED in yes only): resume.sh (rev36's BLOCK, unchanged 192369f3) from a mirror of the pointer's directory s2b-runners-aY2Suc, with the rev36 lock
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r36
W=$S/rw37; RS=$S/g/resume36.sh
REAL_E=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; REAL_R=$(cat "$REAL_E/runners-dir.txt")
PLAN=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r37/rev37.md; NEWLOCK=$(shasum -a 256 "$PLAN" | cut -d' ' -f1)
ROOT=/Users/jack/Programming/bivpak-evidence; TOK=intg-substep2b-impl-12
echo "canonical=$REAL_R newlock=${NEWLOCK:0:16}"
mirror() { local d=$W/$1; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d/evid/runners" "$d/evid/code" "$d/old"
  for f in "$REAL_R"/*; do [ -f "$f" ] && cp -p "$f" "$d/old/"; done
  cp -Rp "$REAL_E"/runners/. "$d/evid/runners/"; printf '%s\n' "$d/old" > "$d/evid/runners-dir.txt"; printf '%s\n' "$d/evid" > "$d/old/evid.txt"; printf '%s\n' "$PLAN" > "$d/old/plan-path.txt"
  chmod u+w "$d/old/t-oracle.txt"; cp -p "$d/evid/runners-dir.txt" "$d/ptr.before"; }
carry() { sed -i '' -E "s/^plan_sha256=[0-9a-f]{64}$/plan_sha256=$NEWLOCK/" "$W/$1/old/t-oracle.txt"; }
cnt() { ls -d "$ROOT"/s2b-runners-* 2>/dev/null | wc -l | tr -d ' '; }
run() { local d=$W/$1; local b; b=$(cnt); out=$(bash "$RS" "$d/evid" "$2" "$3" 2> "$d/err.txt"); rc=$?; local a; a=$(cnt)
  echo "$1 rc=$rc stderr=$(tail -1 "$d/err.txt" | cut -c1-70) new-dirs=$((a-b)) pointer-same=$(cmp -s "$d/ptr.before" "$d/evid/runners-dir.txt" && echo yes || echo no)" >&2; printf '%s' "$out"; }
mirror yes; carry yes; d=$W/yes; NEW=$(run yes "$NEWLOCK" $TOK)
if [ -n "$NEW" ] && [ -d "$NEW" ]; then
  echo "  published: pointer=$([ "$(cat "$d/evid/runners-dir.txt")" = "$NEW" ] && echo NEW || echo OTHER) seal-files=$(ls "$d/evid/runners/resume-$TOK" | wc -l | tr -d ' ') carried-lines=$(wc -l < "$NEW/carried.sha256" | tr -d ' ') lock=$(cut -c1-16 "$NEW/plan-lock.txt") token=$(cat "$NEW/token-id.txt")"
  for f in m3-harness-patch.txt m3-addendum-10-lock.txt m3-addendum-11-lock.txt m3-addendum-9-lock.txt m3-r462-patch.txt m1-fence-rev4.txt m3-help-order.txt red1-owner-words.txt r472-owner-words.txt task-0.done; do printf '  carried %s: %s\n' "$f" "$(cmp -s "$NEW/$f" "$REAL_R/$f" && echo byte-equal-to-canonical || echo DIFFERS)"; done
  printf '  carried t-oracle.txt names the new lock: %s\n' "$(grep -c -x -F "plan_sha256=$NEWLOCK" "$NEW/t-oracle.txt")"
  printf '  plan_blocks.py in NEW == rev33 extractor: %s\n' "$(python3 "$NEW/plan_blocks.py" extract "$PLAN" plan_blocks.py | cmp -s - "$NEW/plan_blocks.py" && echo yes || echo NO)"
  rm -rf "$NEW"; fi
mirror stale; run stale "$NEWLOCK" $TOK >/dev/null
mirror same; carry same; printf '%s\n' "$NEWLOCK" > "$W/same/old/plan-lock.txt"; run same "$NEWLOCK" $TOK >/dev/null
mirror tok; carry tok; run tok "$NEWLOCK" impl-12 >/dev/null
mirror wronglock; carry wronglock; run wronglock "$(printf '%064d' 0)" $TOK >/dev/null
echo "leftover new dirs: $(ls -d "$ROOT"/s2b-runners-* | grep -v -E "NCDBlS|PEazOQ|QzzQ11|P7xJDh|4BSBek|Xi2bWL|IvrESr|sK9rhy|aY2Suc" | wc -l | tr -d ' ')  real pointer: $(cat "$REAL_E/runners-dir.txt")"
