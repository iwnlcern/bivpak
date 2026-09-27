#!/bin/bash
# walk Task 10's head through the REAL controller (run-task.sh 10) from a scratch copy of the runners, the plan = rev41, the evidence = a scratch home holding the sealed helpers; the GO path names no relay, so the runner must STOP at the GO relay's own check AFTER the producer
set -u
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad
REAL=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB; RR=/Users/jack/Programming/bivpak-evidence/s2b-runners-dv8k9v; W=$S/r41/t10; mkdir -p $W
FS=a9eec92599b4575b4c7b20a68a25da2ef645873fec75d4d7c8d5a30109f609c0
run() { local name=$1 plan=$2 pre=${3-}
  local d=$W/$name; chmod -R u+w "$d" 2>/dev/null; rm -rf "$d"; mkdir -p "$d"; cp -Rp "$RR" "$d/R"; chmod -R u+w "$d/R"
  local E=$d/E; mkdir -p "$E/work" "$E/R" "$E/runners"; (cd $REAL && cp -p $(awk '{print $2}' helpers.sha256) helpers.sha256 "$E/")
  printf 'H=2291a46e7ff70c4c06055c8d0aab9e6709cb134d\n' > "$E/R/H.txt"
  printf '%s\n' "$E" > "$d/R/evid.txt"; printf '%s\n' "$plan" > "$d/R/plan-path.txt"; shasum -a 256 "$plan" | cut -d' ' -f1 > "$d/R/plan-lock.txt"
  rm -f "$d/R"/task-10.* "$d/R"/proof-10.* "$d/R"/plan-hash-10.txt "$d/R"/plan_blocks.sha256-10; printf "x\n" > "$d/SITREP-pair-planner-20260101-000000.md"; printf '%s\n' "$d/SITREP-pair-planner-20260101-000000.md" > "$d/R/task-10-go.txt"
  [ -n "$pre" ] && E="$E" bash -c "$pre"
  "$d/R/run-task.sh" 10 > "$d/out.txt" 2> "$d/err.txt"; local rc=$?
  local f=$E/finalize.rev41.py
  printf 'case=%s rc=%s stop="%s" f41=%s f41sha=%s stages=%s exit=%s\n' "$name" "$rc" "$(grep -m1 -o -E 'STOP[^ ]* line=[0-9]+|STOP-controller[^ ]*' "$d/err.txt")" "$([ -L "$f" ] && echo symlink || { [ -f "$f" ] && echo file || echo absent; })" "$([ -f "$f" ] && shasum -a 256 "$f" | cut -c1-12)" "$(ls "$E/work" | grep -c '^finalize.rev41\.')" "$(cat "$d/R/task-10.exit" 2>/dev/null)"
  grep -n -m1 -E 'STOP' "$d/err.txt" | cut -c1-120 | sed 's/^/    /'; }
P41=$S/r41/rev41.md
run yes $P41
d=$W/yes; E=$d/E; echo "  producer line reached: $(grep -c . $d/R/task-10.sh) runner lines; stop after the producer: $(sed -n 's/.*line=\([0-9]*\).*/\1/p' $d/err.txt | head -1)"; grep -n 'F41=\|TASK10_GO\|\[ -s "\$GO" \]' $d/R/task-10.sh | cut -c1-60
run rerun-present $P41 'python3 /Users/jack/Programming/bivpak-evidence/s2b-runners-r9Akl6/plan_blocks.py extract '"$P41"' finalize.py > "$E/finalize.rev41.py"'
run n-f41-wrong $P41 'printf "x\n" > "$E/finalize.rev41.py"'
run n-f41-symlink $P41 'ln -s "$E/finalize.py" "$E/finalize.rev41.py"'
python3 - $P41 $S/r41/rev41-fzmut.md <<'PY'
import sys
t=open(sys.argv[1]).read(); a='"Re-gate at the c10t head (Task 9b, rev39; rev41): object %s;'; assert t.count(a)==1; open(sys.argv[2],'w').write(t.replace(a,'"Re-gate at the c10t head (Task 9b, rev39; rev41) MUTANT: object %s;'))
PY
run n-block-differs $S/r41/rev41-fzmut.md
