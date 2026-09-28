#!/usr/bin/env bash
# Task 11 body walk #2: as w11.sh, with the FIXED producer (cp45.sh) placed beside the sealed one as census_population.rev45.sh and the body's two producer lines pointed at it; everything downstream runs unmodified
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r44; W=$S/w11b; REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB
chmod -R u+w "$W" 2>/dev/null; rm -rf "$W"; mkdir -p "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results" "$W/rn"
cp -cRp "$REAL" "$W/evid" || exit 9; cp -p "$S/cp45.sh" "$W/evid/census_population.rev45.sh"
cp -p /Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results/"
L=$(grep -n '^# Runner plumbing (Task 11)$' "$S/t11.sh" | cut -d: -f1)
{ echo 'set -u'; echo 'STOP() { printf "STOP-task-11 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'; tail -n +"$L" "$S/t11.sh" | sed -e "s#^MAIN=/Users/jack/Programming/bivpak\$#MAIN=$W/main#" -e 's#"\$EVID/census_population\.sh"#"$EVID/census_population.rev45.sh"#g'; } > "$W/body.sh"
echo "producer refs now: $(grep -c 'census_population.rev45.sh' "$W/body.sh"); sealed refs left: $(grep -c '"\$EVID/census_population\.sh"' "$W/body.sh")"
(EVID=$W/evid RUNNERS=$W/rn bash "$W/body.sh") > "$W/out.txt" 2>&1; rc=$?
echo "task-11 body rc=$rc; tail: $(tail -2 "$W/out.txt" | tr '\n' ' ' | cut -c1-240)"
cat "$W/evid/H/census-population.rc" "$W/evid/H/census-rehearsal.rc" 2>/dev/null; grep -E ' result=PASS$' "$W/evid/H/census-rehearsal.log" 2>/dev/null | cut -c1-200
cat "$W/evid/record-token-classes.txt" "$W/rn/final-verdict.rc" 2>/dev/null
echo "final set: $(wc -l < "$W/rn/final-set.txt" 2>/dev/null) files; .pyc in set: $(grep -c '\.pyc$' "$W/rn/final-set.txt" 2>/dev/null); attempts/ rows: $(grep -c '^attempts/' "$W/rn/final-set.txt" 2>/dev/null); rev45 producer in set: $(grep -c 'census_population.rev45.sh' "$W/rn/final-set.txt" 2>/dev/null)"
R=$(ls -d "$W"/main/docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-* 2>/dev/null); echo "resdir: ${R##*/} files=$(find "$R" -type f 2>/dev/null | wc -l | tr -d ' ') size=$(du -sh "$R" 2>/dev/null | cut -f1)"
