#!/usr/bin/env bash
# Task 11 body walk: the derived runner's body (from "# Runner plumbing") on a full APFS clone of the real $EVID, MAIN re-pointed at a scratch dir holding the pinned instrument; the real candidate worktree read-only
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r44; W=$S/w11; REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB
chmod -R u+w "$W" 2>/dev/null; rm -rf "$W"; mkdir -p "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results" "$W/rn"
cp -cRp "$REAL" "$W/evid" || exit 9
cp -p /Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results/"
L=$(grep -n '^# Runner plumbing (Task 11)$' "$S/t11.sh" | cut -d: -f1)
{ echo 'set -u'; echo 'STOP() { printf "STOP-task-11 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'; tail -n +"$L" "$S/t11.sh" | sed "s#^MAIN=/Users/jack/Programming/bivpak\$#MAIN=$W/main#"; } > "$W/body.sh"
grep -n '^MAIN=' "$W/body.sh"; echo "body lines: $(wc -l < "$W/body.sh") (runner line = body line + $((L-3)))"
wt0=$(git -C /Users/jack/Programming/bivpak-intg-substep2b-wiring status --porcelain | wc -l | tr -d ' ')
(EVID=$W/evid RUNNERS=$W/rn bash "$W/body.sh") > "$W/out.txt" 2>&1; rc=$?
echo "task-11 body rc=$rc; tail: $(tail -2 "$W/out.txt" | tr '\n' ' ' | cut -c1-200)"
echo "worktree porcelain rows before/after: $wt0/$(git -C /Users/jack/Programming/bivpak-intg-substep2b-wiring status --porcelain | wc -l | tr -d ' ')"
cat "$W/evid/H/census-population.rc" "$W/evid/H/census-rehearsal.rc" 2>/dev/null; grep -E ' result=PASS$' "$W/evid/H/census-rehearsal.log" 2>/dev/null | cut -c1-160
cat "$W/evid/record-token-classes.txt" 2>/dev/null; cat "$W/rn/final-verdict.rc" 2>/dev/null
echo "final set: $(wc -l < "$W/rn/final-set.txt" 2>/dev/null) files; binary (.pyc) in set: $(grep -c '\.pyc$' "$W/rn/final-set.txt" 2>/dev/null); attempts/ rows: $(grep -c '^attempts/' "$W/rn/final-set.txt" 2>/dev/null)"
R=$(ls -d "$W"/main/docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-* 2>/dev/null); echo "resdir: ${R##*/} files=$(find "$R" -type f 2>/dev/null | wc -l | tr -d ' ') size=$(du -sh "$R" 2>/dev/null | cut -f1)"
