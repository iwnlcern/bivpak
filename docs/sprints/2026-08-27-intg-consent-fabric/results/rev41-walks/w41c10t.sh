#!/bin/bash
# walk c10t.sh (rev41 bytes): case <name> [block-sed] [pre-cmd]; each case a fresh scratch EVID; the walk clone at c10
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad
WT=$S/r39/mw/wt; REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; C10=2291a46e7ff70c4c06055c8d0aab9e6709cb134d; C9=2893bc53ad0f9d4f3e6f45f7990c86d49f868138
W=$S/r41/wc; mkdir -p $W
run() { local name=$1 msed=${2-} pre=${3-} head=${4-$C10}
  local E=$W/$name; chmod -R u+w "$E" 2>/dev/null; rm -rf "$E"; mkdir -p "$E/receipts" "$E/work" "$E/heads"
  cp -p $REAL/receipts/c10-mutants.rev40.txt "$E/receipts/"; cp -Rp $REAL/heads/c10 "$E/heads/"; cp -p $REAL/commits.c9.txt $REAL/commits.c10.txt "$E/"
  local B=$E/block.sh; cp $S/r41/bl/c10t.sh "$B"; if [ -n "$msed" ]; then sed -i '' "$msed" "$B"; cmp -s $S/r41/bl/c10t.sh "$B" && { echo "case=$name WALK-ERROR mutant-no-op"; return; }; fi
  (cd $WT && git checkout -q -f "$head" && git clean -q -fd -e .venv-harness -e build) || { echo "case=$name WALK-ERROR checkout"; return; }
  [ -n "$pre" ] && (cd $WT && E="$E" bash -c "$pre")
  (cd $WT && EVID="$E" bash "$B") > "$E/out.txt" 2> "$E/err.txt"; local rc=$?
  local h=$(cd $WT && git rev-parse HEAD); local st=$(cd $WT && git status --short | grep -v -E 'venv-harness' | wc -l | tr -d ' ')
  printf 'case=%s rc=%s out="%s" stop="%s" head=%s dirty=%s c10t=%s red=%s\n' "$name" "$rc" "$(tail -1 "$E/out.txt")" "$(grep -m1 -o 'STOP-c10t.*' "$E/err.txt")" "${h:0:7}" "$st" "$([ -e "$E/commits.c10t.txt" ] && echo yes || echo no)" "$([ -e "$E/receipts/c10t-red.txt" ] && echo yes || echo no)"; }
LOG=heads/c10/H/linux-build.log
case "${1-all}" in
no)
run n-not-at-c10 "" "" $C9
run n-dirty "" 'printf "x\n" >> README.md'
run n-verdict "" 'sed -i "" "/^verdict=ok$/d" "$E/receipts/c10-mutants.rev40.txt"'
run n-headgate-present "" 'printf "x\n" > "$E/heads/c10/headgate.txt"'
run n-container-rc0 "" 'chmod u+w "$E/heads/c10/linux-container.rc"; printf "0\n" > "$E/heads/c10/linux-container.rc"'
run n-log-altered "" 'chmod u+w "$E/'$LOG'"; printf "x\n" >> "$E/'$LOG'"'
run n-exists-c10t "" 'printf "x\n" > "$E/commits.c10t.txt"'
# isolating mutants: the log edited AND the block's LS moved to the edited log's digest, so ONLY the red predicate under test can fire
run n-red-foreign "" 'chmod u+w "$E/'$LOG'"; printf "/work/repo/src/x.cpp:1:1: error: foreign [-Werror]\n" >> "$E/'$LOG'"; s=$(shasum -a 256 "$E/'$LOG'" | cut -d" " -f1); sed -i "" "s/^RS=\([0-9a-f]*\); LS=[0-9a-f]*;/RS=\1; LS=$s;/" "$E/block.sh"'
run n-red-shape "" 'chmod u+w "$E/'$LOG'"; sed -i "" "0,/RepoOutcomeRow::sha'"'"'/s//RepoOutcomeRow::shx'"'"'/" "$E/'$LOG'" 2>/dev/null || python3 -c "import sys;p=sys.argv[1];s=open(p).read();s=s.replace(\"RepoOutcomeRow::sha'"'"'\",\"RepoOutcomeRow::shx'"'"'\",1);open(p,\"w\").write(s)" "$E/'$LOG'"; s=$(shasum -a 256 "$E/'$LOG'" | cut -d" " -f1); sed -i "" "s/^RS=\([0-9a-f]*\); LS=[0-9a-f]*;/RS=\1; LS=$s;/" "$E/block.sh"'
run n-red-distinct "" 'chmod u+w "$E/'$LOG'"; python3 -c "import sys;p=sys.argv[1];s=open(p).read();a=\"test_envelope.cpp:85:25: error: missing initializer for member '"'"'biv::open::RepoOutcomeRow::sha'"'"'\";b=\"test_envelope.cpp:85:25: error: missing initializer for member '"'"'biv::open::RepoOutcomeRow::branch'"'"'\";assert s.count(a)==1;s=s.replace(a,b);open(p,\"w\").write(s)" "$E/'$LOG'"; s=$(shasum -a 256 "$E/'$LOG'" | cut -d" " -f1); sed -i "" "s/^RS=\([0-9a-f]*\); LS=[0-9a-f]*;/RS=\1; LS=$s;/" "$E/block.sh"'
run n-patch-sha 's/^RS=0508c70f/RS=1508c70f/'
run n-w3-case 's/want = {"failed row completeness rejects a missing kind"/want = {"failed row completeness rejects a missing kindX"/'
run n-index-tree 's/TREE=36331eb0/TREE=46331eb0/'
;;
yes)
run yes
E=$W/yes; cat "$E/receipts/c10t-red.txt"; T=$(cat "$E/commits.c10t.txt" 2>/dev/null); (cd $WT && echo "tree=$(git rev-parse "$T^{tree}") parent=$(git rev-parse "$T~1") msg=$(git log -1 --format=%s "$T")"); cat "$E/work/c10t-w3.txt"
;;
esac
case "${1-}" in
shape)
run n-red-shape "" 'chmod u+w "$E/heads/c10/H/linux-build.log"; python3 '"$S"'/r41/logedit.py "$E/heads/c10/H/linux-build.log" "RepoOutcomeRow::sha'"'"' [-Werror" "RepoOutcomeRow::shx'"'"' [-Werror"; s=$(shasum -a 256 "$E/heads/c10/H/linux-build.log" | cut -d" " -f1); sed -i "" "s/^RS=\([0-9a-f]*\); LS=[0-9a-f]*;/RS=\1; LS=$s;/" "$E/block.sh"; grep -c "LS=$s" "$E/block.sh"'
;;
esac
