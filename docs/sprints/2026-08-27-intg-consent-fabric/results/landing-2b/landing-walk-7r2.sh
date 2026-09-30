#!/usr/bin/env bash
# packet revision 2 §7 walk: extracts the fenced zsh blocks of §7 from the packet and runs them UNEDITED in one `zsh -f`,
# in scratch clones whose origin is a local bare repo holding main at B. One YES arm, three must-be-NO arms.
set -u
SRC=$1; PK=$2; W=$3
H=cb19326a5596bf30eab2ec2b9baeda0bc77be895; B=186adf7d67171bd7afe621f39b657a1a113ce299
REC=docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1
die(){ printf 'WALK-ABORT %s\n' "$1"; exit 3; }
[ ! -e "$W" ] || die scratch-exists; mkdir -p "$W" || die mk
python3 - "$PK" "$W/run.zsh" <<'PY' || die extract
import sys,re
s=open(sys.argv[1]).read(); i=s.index("## 7. Hold"); j=s.index("## 8. Landed"); sec=s[i:j]
b=re.findall(r"```zsh\n(.*?)```", sec, re.S)
assert len(b)==6, len(b)
open(sys.argv[2],"w").write("".join(b)); print("extracted %d zsh blocks from §7" % len(b))
PY
printf 'run.zsh sha256=%s packet sha256=%s\n' "$(shasum -a 256 "$W/run.zsh" | cut -c1-16)" "$(shasum -a 256 "$PK" | cut -c1-16)"
mkclone(){ local n=$1; git clone -q --no-local "$SRC" "$W/$n" 2>/dev/null || die clone-$n
  ( cd "$W/$n" && git fetch -q "$SRC" "$H" && git checkout -q -B main origin/main && git config user.name walk7r2 && git config user.email walk7r2@invalid ) || die setup-$n
  git init -q --bare "$W/$n-remote.git" || die bare-$n; ( cd "$W/$n" && git push -q "$W/$n-remote.git" "${B}:refs/heads/main" && git remote set-url origin "$W/$n-remote.git" ) || die seed-$n
  mkdir -p "$W/$n-evid"; }
runarm(){ local n=$1; ( cd "$W/$n" && EVID=$W/$n-evid zsh -f "$W/run.zsh" ) > "$W/$n.out" 2>&1; local rc=$?
  sed -e "s#$W#<scratch>#g" "$W/$n.out" | grep -v '^hint:'; printf '  [%s] zsh rc=%s ; remote main=%s ; clone HEAD=%s\n' "$n" "$rc" "$(git -C "$W/$n-remote.git" rev-parse refs/heads/main)" "$(git -C "$W/$n" rev-parse HEAD)"; }
echo '== YES: the real lane state -> every step passes, ONE push, remote main == M'
mkclone yes; printf '  main-before=%s\n' "$(git -C "$W/yes" rev-parse main)"; runarm yes
M=$(git -C "$W/yes" rev-parse HEAD); [ "$(git -C "$W/yes-remote.git" rev-parse refs/heads/main)" = "$M" ] && echo '  remote==M: yes' || echo '  remote==M: NO'
ls "$W/yes-evid/landing" | tr '\n' ' '; echo
echo '== NO-a: an info/grafts file present -> STOP at the step (1) pre-check, BEFORE the merge; remote untouched'
mkclone noa; ( cd "$W/noa" && printf '' > "$(git rev-parse --git-path info/grafts)" ); MBa=$(git -C "$W/noa" rev-parse HEAD); runarm noa
[ "$(git -C "$W/noa" rev-parse HEAD)" = "$MBa" ] && echo '  no merge made: yes' || echo '  no merge made: NO'
echo '== NO-b: a record file committed then removed on main (docs lane only) -> the step (1) history pre-check STOPs BEFORE the merge; remote untouched'
mkclone nob; ( cd "$W/nob" && mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt" && git add -f "$REC/walk.txt" && git commit -q -m add && git rm -q "$REC/walk.txt" && git commit -q -m rm ) || die nob-commits; MBb=$(git -C "$W/nob" rev-parse HEAD); runarm nob
[ "$(git -C "$W/nob" rev-parse HEAD)" = "$MBb" ] && echo '  no merge made: yes' || echo '  no merge made: NO'
echo '== NO-d: the same history, with the step (1) pre-check blocks REMOVED from run.zsh (the rev-1-shaped sequence) -> the step (4) gate still STOPs, after the merge; remote untouched'
python3 - "$W/run.zsh" "$W/run-nopre.zsh" <<'PY' || die nopre
import sys
s=open(sys.argv[1]).read(); a=s.index('for ref in "$MB" "$H"; do'); b=s.index('REC "$LD/step1.txt"', a) if 'REC "$LD/step1.txt"' in s[a:] else s.index('print -r -- "main-before=$MB', a)   # rev3: step1 receipt written by REC
open(sys.argv[2],'w').write(s[:a]+s[b:])
PY
mkclone nod; ( cd "$W/nod" && mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt" && git add -f "$REC/walk.txt" && git commit -q -m add && git rm -q "$REC/walk.txt" && git commit -q -m rm ) || die nod-commits
( cd "$W/nod" && EVID=$W/nod-evid zsh -f "$W/run-nopre.zsh" ) > "$W/nod.out" 2>&1; rc=$?; grep -E '^(STOP|history|index|M=)' "$W/nod.out"; printf '  [nod] zsh rc=%s ; remote main=%s\n' "$rc" "$(git -C "$W/nod-remote.git" rev-parse refs/heads/main)"
echo '== NO-c: $EVID/landing already exists -> STOP at step (0); nothing else runs'
mkclone noc; mkdir "$W/noc-evid/landing"; runarm noc
echo 'walk-complete'
