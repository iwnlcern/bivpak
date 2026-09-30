#!/usr/bin/env bash
# packet revision 3 §7 walk: extracts the six fenced zsh blocks of §7 and runs them UNEDITED in one `zsh -f` per arm, in scratch
# clones whose origin is a local bare repo holding main at B. Receipt-sink arms insert ONE line after block 0, `mkdir "$LD/<receipt>"`,
# which makes that receipt's write fail at the real filesystem boundary; no packet command is edited. A pass-through git wrapper
# logs every `push` invocation (dry runs included) so push attempts are COUNTED, not inferred. Arms run in parallel.
set -u
SRC=$1; PK=$2; W=$3
H=cb19326a5596bf30eab2ec2b9baeda0bc77be895; B=186adf7d67171bd7afe621f39b657a1a113ce299
REC=docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1
die(){ printf 'WALK-ABORT %s\n' "$1"; exit 3; }
[ ! -e "$W" ] || die scratch-exists; mkdir -p "$W/blocks" "$W/gw" || die mk
python3 - "$PK" "$W" <<'PY' || die extract
import sys,re,hashlib
s=open(sys.argv[1]).read(); i=s.index("## 7. Hold"); j=s.index("## 8. Landed")
b=re.findall(r"```zsh\n(.*?)```", s[i:j], re.S); assert len(b)==6, len(b)
for k,x in enumerate(b): open("%s/blocks/%d.zsh"%(sys.argv[2],k),"w").write(x)
open(sys.argv[2]+"/run.zsh","w").write("".join(b)); print("extracted 6 zsh blocks from §7; run.zsh sha256=%s" % hashlib.sha256("".join(b).encode()).hexdigest())
PY
RG=$(command -v git); printf '#!/bin/bash\nfor a in "$@"; do [ "$a" = push ] && { printf "%%s\\n" "$*" >> "$GITLOG"; break; }; done\nexec %s "$@"\n' "$RG" > "$W/gw/git"; chmod +x "$W/gw/git"
mkclone(){ local n=$1; git clone -q --no-local "$SRC" "$W/$n" 2>/dev/null || return 1
  ( cd "$W/$n" && git fetch -q "$SRC" "$H" && git checkout -q -B main origin/main && git config user.name walk7r3 && git config user.email walk7r3@invalid ) || return 1
  git init -q --bare "$W/$n-remote.git" || return 1; ( cd "$W/$n" && git push -q "$W/$n-remote.git" "${B}:refs/heads/main" && git remote set-url origin "$W/$n-remote.git" ) || return 1
  mkdir -p "$W/$n-evid"; : > "$W/$n.gitlog"; }
arm(){ local n=$1 script=$2; mkclone "$n" || { echo "[$n] setup-failed" > "$W/$n.res"; return; }
  ( cd "$W/$n" && GITLOG=$W/$n.gitlog PATH=$W/gw:$PATH EVID=$W/$n-evid zsh -f "$script" ) > "$W/$n.out" 2>&1; local rc=$?
  { printf '== %s\n' "$n"; sed -e "s#$W#<scratch>#g" "$W/$n.out" | grep -v -E '^hint:|^ [^ ].*\||^ (create|delete) mode'
    printf '  [%s] zsh rc=%s ; push invocations logged=%s ; remote main=%s\n' "$n" "$rc" "$(grep -c . "$W/$n.gitlog")" "$(git -C "$W/$n-remote.git" rev-parse refs/heads/main)"; } > "$W/$n.res"; }
sink(){ local name=$1 out=$2; { cat "$W/blocks/0.zsh"; printf 'mkdir "$LD/%s" || exit 9\n' "$name"; cat "$W/blocks/1.zsh" "$W/blocks/2.zsh" "$W/blocks/3.zsh" "$W/blocks/4.zsh" "$W/blocks/5.zsh"; } > "$out"; }
for r in step1.txt step2.txt record-index.txt record-history.txt push-dry-run.txt push-attempt.txt push-result.txt; do sink "$r" "$W/sink-$r.zsh"; done
arm yes "$W/run.zsh" &
for r in step1.txt step2.txt record-index.txt record-history.txt push-dry-run.txt push-attempt.txt push-result.txt; do arm "sink-$r" "$W/sink-$r.zsh" & done
wait
echo "# expected: yes -> landing-pushed-ok, 2 push invocations (dry run + one), remote == M"
echo "# expected: every PRE-push sink -> STOP receipt-write <name>, rc 1, 0 push invocations, remote == B"
echo "# expected: sink-push-result.txt (post-push) -> the push happens (2 invocations, remote == M), then STOP post-push ... receipt-write-failed=1 ... NO retry, rc 1"
for n in yes sink-step1.txt sink-step2.txt sink-record-index.txt sink-record-history.txt sink-push-dry-run.txt sink-push-attempt.txt sink-push-result.txt; do cat "$W/$n.res"; done
echo 'walk-complete'
