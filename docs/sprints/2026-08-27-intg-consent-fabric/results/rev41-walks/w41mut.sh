#!/bin/bash
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad
WT=$S/r39/mw/wt; REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; YE=$S/r41/wc/yes; C10T=$(cat $YE/commits.c10t.txt); C10=2291a46e7ff70c4c06055c8d0aab9e6709cb134d
W=$S/r41/wm; mkdir -p $W
run() { local name=$1 pre=${2-} head=${3-$C10T}
  local E=$W/$name; chmod -R u+w "$E" 2>/dev/null; rm -rf "$E"; mkdir -p "$E/receipts" "$E/code" "$E/work"
  cp -p $REAL/receipts/c10-mutants.rev40.txt "$E/receipts/"; cp -Rp $REAL/code/c10-mutants.rev40 "$E/code/"; cp -p $REAL/code/c10-M-H1-F4.patch "$E/code/"; cp -p $REAL/commits.c9.txt $REAL/commits.c10.txt "$E/"; cp -p $YE/commits.c10t.txt "$E/"
  (cd $WT && git checkout -q -f "$head") || { echo "case=$name WALK-ERROR checkout"; return; }
  [ -n "$pre" ] && (cd $WT && E="$E" bash -c "$pre")
  (cd $WT && EVID="$E" bash $S/r41/bl/c10t-mutants.sh) > "$E/out.txt" 2> "$E/err.txt"; local rc=$?
  printf 'case=%s rc=%s out="%s" stop="%s" head=%s dirty=%s record=%s\n' "$name" "$rc" "$(tail -1 "$E/out.txt" | sed "s|$S|\$S|")" "$(grep -m1 -o 'STOP-c10t-mutants.*' "$E/err.txt")" "$(cd $WT && git rev-parse --short HEAD)" "$(cd $WT && git status --short | wc -l | tr -d ' ')" "$([ -e "$E/receipts/c10t-mutants.txt" ] && echo yes || echo no)"; }
case "$1" in
no)
run n-not-at-c10t "" $C10
run n-grandparent 'printf "%s\n" 99136ca635cd4c59b456606aed7d448e1c25a509 > "$E/commits.c9.txt"'
run n-rev40-moved 'chmod u+w "$E/receipts/c10-mutants.rev40.txt"; printf "x\n" >> "$E/receipts/c10-mutants.rev40.txt"'
run n-rev40-work-absent 'chmod -R u+w "$E/code/c10-mutants.rev40"; rm -rf "$E/code/c10-mutants.rev40"'
run n-record-exists 'printf "x\n" > "$E/receipts/c10t-mutants.txt"'
run n-dirty 'printf "x\n" >> README.md'
(cd $WT && git checkout -q -f $C10T)
;;
yes) run yes; cat $W/yes/receipts/c10t-mutants.txt; for n in M-H1-PRE M-H1-F4; do echo "$n:"; cat $W/yes/code/c10t-mutants/$n.failed-cases.txt; done ;;
esac
