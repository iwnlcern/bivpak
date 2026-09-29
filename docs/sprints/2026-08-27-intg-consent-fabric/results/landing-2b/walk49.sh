#!/bin/bash
# walk49.sh <scratch-dir> — the rev49 census walk: produce the pinned product population at H, prove it equal when produced on the predicted merge,
# then run the instrument on the predicted merge (YES) and on one scratch commit per arm (master 212748 §3; arm 6 FIRST). Values are generated at
# RUNTIME (the accepted one copied from an existing docs row of the scanned tree; the undeclared one built by printf), so this file carries no literal.
set -u
set -o pipefail
S=$1; BIV=/Users/jack/Programming/bivpak; H=cb19326a5596bf30eab2ec2b9baeda0bc77be895
L=$BIV/docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b
PRODUCER=$L/census_population.rev49.sh; INST=$L/intg-2b-landing-census.sh
ALT='sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-'
REALGIT=$(command -v git)
[ ! -e "$S" ] || { echo "scratch exists"; exit 2; }
mkdir -p "$S" && cd "$S" || exit 2
git clone -q --shared "$BIV" repo && cd repo && git checkout -q main || exit 2
git -c user.name=walk -c user.email=walk@local merge -q --no-ff --no-edit -m walk-merge "$H" || exit 2
M=$(git rev-parse HEAD); echo "main=$(git rev-parse HEAD^1) H=$(git rev-parse HEAD^2) predicted_merge_tree=$(git rev-parse HEAD^{tree}) merge_tree_of_main_H=$(git -C "$BIV" merge-tree --write-tree main "$H" | head -1)"
bash "$PRODUCER" "$H" "$S/population.txt"; echo "producer@H rc=$?"
bash "$PRODUCER" "$M" "$S/population-at-merge.txt"; echo "producer@merge rc=$?"
cmp -s "$S/population.txt" "$S/population-at-merge.txt" && echo "population@H == population@merge (byte-equal)" || echo "POPULATION DIFFERS"
echo "population sha256=$(shasum -a 256 "$S/population.txt" | cut -d' ' -f1)"
run() { # run <label> <ref> [env...]  -> one line: label, rc, the last stdout/stderr line
  local lab=$1 ref=$2; shift 2; local o; o=$(env "$@" bash "$INST" "$ref" "$S/population.txt" "$S/out-$lab" "$ref" 2>&1); local rc=$?
  printf '%-34s rc=%s  %s\n' "$lab" "$rc" "$(printf '%s\n' "$o" | tail -n 1 | sed -E 's/ history_refs=[0-9a-f]+//')"; }
commit() { git add -A && git -c user.name=walk -c user.email=walk@local commit -q -m "$1"; }
ACC=$(git grep -h -o -E "$ALT" "$M" -- docs | head -n 1); [ -n "$ACC" ] || { echo "no accepted docs value"; exit 2; }
UND=$(printf 'sk-%040d' 9)
echo "--- YES and arm 6 (the positive churn control) first"
run yes-predicted-merge "$M"
git checkout -q -b a6 "$M"; printf 'churn %s\n' "$ACC" > docs/walk-arm6.md; commit a6; run arm6-docs-row-accepted-value HEAD
echo "--- must-be-NO arms, each on its own predicate"
git checkout -q -b a1 "$M"; printf 'x %s\n' "$UND" > docs/walk-arm1.md; commit a1; run arm1-undeclared-docs-tree HEAD
git checkout -q -b a2 "$M"; printf 'x %s\n' "$UND" > docs/walk-arm2.md; commit a2a; git rm -q docs/walk-arm2.md; commit a2b; run arm2-undeclared-history-only HEAD
git checkout -q -b a3 "$M"; printf '// %s\n' "$ACC" >> tests/test_cli.cpp; commit a3; run arm3-product-row-added HEAD
P1=$(sed -n -E 's/^(tests\/test_cli\.cpp):([0-9]+) \| A$/\2/p' "$S/population.txt" | head -n 1)
git checkout -q -b a4 "$M"; sed -i '' "${P1}d" tests/test_cli.cpp; commit a4; run arm4-product-row-removed HEAD
git checkout -q -b a5 "$M"; printf '// %s\n' "$ACC" > src/walk_arm5.cpp; commit a5a; git rm -q src/walk_arm5.cpp; commit a5b; run arm5-product-history-path HEAD
run mutant-row-1 "$M" CENSUS_MUTANT_ROW=1
mkdir -p "$S/shimA" "$S/shimB"
printf '#!/bin/bash\nif [ "$1" = grep ] && [ "$2" = -n ]; then "%s" "$@" | head -n 5; exit 2; fi\nexec "%s" "$@"\n' "$REALGIT" "$REALGIT" > "$S/shimA/git"
printf '#!/bin/bash\n/usr/bin/shasum "$@"; exit 1\n' > "$S/shimB/shasum"; chmod +x "$S/shimA/git" "$S/shimB/shasum"
run arm7a-tree-producer-partial-rc2 "$M" PATH="$S/shimA:$PATH"
run arm7b-digest-stage-full-then-rc1 "$M" PATH="$S/shimB:$PATH"
cp "$S/population.txt" "$S/pop-ok"; sed -E 's/^(== ACCEPTED VALUE SET: fixture=)([0-9a-f]{64})(.*)$/\1\2 fixture=\2\3/' "$S/pop-ok" > "$S/population.txt"; run control-set-duplicate "$M"; cp "$S/pop-ok" "$S/population.txt"
echo "--- the retention rule: no matched text under any OUT_DIR"
n=0; for f in "$S"/out-*/*; do grep -q -E "$ALT" "$f" && { echo "RETAINED TEXT in $f"; n=$((n+1)); }; done; echo "files_with_matched_text=$n"
