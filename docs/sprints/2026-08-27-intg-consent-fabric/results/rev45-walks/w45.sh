#!/usr/bin/env bash
# rev45 walk: the DERIVED Task 11 runner's body (from "# Runner plumbing") on full APFS clones of the real $EVID; RUNNERS = scratch dir with plan-path.txt -> rev45 and the canonical plan_blocks.py; MAIN re-pointed at a scratch dir holding the pinned instrument; the candidate worktree read-only
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r45; REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; CAN=/Users/jack/Programming/bivpak-evidence/s2b-runners-V1jS1t
L=$(grep -n '^# Runner plumbing (Task 11)$' "$S/t11.sh" | cut -d: -f1)
setup() { local W=$S/w/$1; chmod -R u+w "$W" 2>/dev/null; rm -rf "$W"; mkdir -p "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results" "$W/rn"; cp -cRp "$REAL" "$W/evid" || exit 9
  cp -p /Users/jack/Programming/bivpak/docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r449-landing-census.sh "$W/main/docs/sprints/2026-08-27-intg-consent-fabric/results/"
  cp -p "$CAN/plan_blocks.py" "$W/rn/"; printf '%s\n' "$S/rev45.md" > "$W/rn/plan-path.txt"
  { echo 'set -u'; echo 'STOP() { printf "STOP-task-11 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'; tail -n +"$L" "$S/t11.sh" | sed "s#^MAIN=/Users/jack/Programming/bivpak\$#MAIN=$W/main#"; } > "$W/body.sh"; }
go() { local W=$S/w/$1; (EVID=$W/evid RUNNERS=$W/rn bash "$W/body.sh") > "$W/out.txt" 2>&1; echo "$1 rc=$? $(tail -1 "$W/out.txt" | cut -c1-80) | rev45 file: $( [ -L "$W/evid/census_population.rev45.sh" ] && echo symlink || { [ -f "$W/evid/census_population.rev45.sh" ] && shasum -a 256 "$W/evid/census_population.rev45.sh" | cut -c1-16 || echo absent; } ) | census-population.rc: $(cat "$W/evid/H/census-population.rc" 2>/dev/null || echo absent) | stage leftovers in work/: $(ls "$W/evid/work" | grep -c '^census_population.rev45\.')"; }
echo "body map: runner line = body line + $((L-3))"
setup tamper; printf '# tampered\n' > "$S/w/tamper/evid/census_population.rev45.sh"; go tamper
setup link; ln -s "$S/../r44/cp45.sh" "$S/w/link/evid/census_population.rev45.sh"; go link
setup yes; sb=$(shasum -a 256 "$S/w/yes/evid/census_population.sh" | cut -d' ' -f1); go yes
W=$S/w/yes; echo "  sealed census_population.sh unchanged: $([ "$(shasum -a 256 "$W/evid/census_population.sh" | cut -d' ' -f1)" = "$sb" ] && echo yes) (${sb:0:16})"
cat "$W/evid/H/census-rehearsal.rc"; grep -E ' result=PASS$' "$W/evid/H/census-rehearsal.log" | cut -c1-120; grep -c 'census_population.rev45.sh <merge>' "$W/evid/receipts/landing-census-declaration.txt"; grep -o 'producer sha256 [0-9a-f]*' "$W/evid/receipts/landing-census-declaration.txt" | cut -c1-32
cat "$W/evid/record-token-classes.txt" "$W/rn/final-verdict.rc"; echo "final set: $(wc -l < "$W/rn/final-set.txt") files; rev45 producer in set: $(grep -c -x 'census_population.rev45.sh' "$W/rn/final-set.txt")"
