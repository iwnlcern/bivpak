#!/usr/bin/env bash
# rev51 walk: the three pinned landing lines extracted by the plan's rule; the history clause's controls on a scratch clone.
set -u
SRC=$1; PLAN=$2; W=$3            # SRC = the bivpak repo, PLAN = plan path (absolute), W = fresh scratch dir (absolute, pwd -P)
H=cb19326a5596bf30eab2ec2b9baeda0bc77be895
REC=docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1
die(){ printf 'WALK-ABORT %s\n' "$1"; exit 3; }
G(){ git -c user.name=walk51 -c user.email=walk51@invalid -c commit.gpgsign=false "$@"; }
[ ! -e "$W" ] || die scratch-exists
extract(){ python3 - "$PLAN" "$1" <<'PY'
import sys; L=open(sys.argv[1]).read().split("\n"); pre=sys.argv[2]
m=[x.strip()[1:-1] for x in L if x.strip().startswith("`"+pre) and x.strip().endswith("`")]
if len(m)!=1: sys.exit("count-%d"%len(m))
sys.stdout.write(m[0])
PY
}
L1=$(extract 'STOP(){ printf') || die l1; L2=$(extract 'bash docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/intg-2b-landing-census.sh') || die l2; L3=$(extract 'HREF=<merge>;') || die l3
for n in 1 2 3; do eval "v=\$L$n"; printf 'pin L%s bytes=%s sha256=%s\n' "$n" "$(printf '%s' "$v" | wc -c | tr -d ' ')" "$(printf '%s' "$v" | shasum -a 256 | cut -c1-64)"; done
mkdir -p "$W" && cd "$W" || die mk
git clone -q --no-local "$SRC" repo 2>/dev/null || die clone
cd repo && G fetch -q "$SRC" "$H" && [ "$(git cat-file -t $H)" = commit ] || die fetch-h
G checkout -q -B main origin/main || die co
MB=$(git rev-parse main); TMB=$(git rev-parse "main^{tree}"); printf 'main-before=%s tree=%s\n' "$MB" "$TMB"
r1(){ local o rc=0; o=$(bash -c "$L1" 2>&1) || rc=$?; printf '  L1 rc=%s out=%s\n' "$rc" "$o"; }
r3(){ local o rc=0; o=$(bash -c "${L3//<merge>/$1}" 2>&1) || rc=$?; printf '  L3[%s] rc=%s out=%s\n' "${2:-$1}" "$rc" "$o"; }
plain(){ printf '  replace-honouring plain rev-list count=%s ; --full-history count=%s\n' "$(git rev-list "$1" -- "$REC" | wc -l | tr -d ' ')" "$(git rev-list --full-history "$1" -- "$REC" | wc -l | tr -d ' ')"; }
mergeH(){ G merge -q --no-ff --no-edit -m "walk merge" "$H" >/dev/null 2>&1 || die "merge-$1"; }
echo 'C1 real clean history (merge main+H) -> PASS both'
G checkout -q -B land "$MB"; mergeH c1; M=$(git rev-parse HEAD); TM=$(git rev-parse "HEAD^{tree}"); printf '  merge=%s tree=%s\n' "$M" "$TM"; r1; r3 "$M" merge; plain "$M"
echo 'C2 untracked record file on disk -> PASS both'
mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt"; r1; r3 "$M" merge; rm -rf "$REC"
echo 'C3a staged record -> L1 STOP'
mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt"; G add -f "$REC/walk.txt"; r1; G reset -q; rm -rf "$REC"
echo 'C3b committed now -> L1 STOP, L3 STOP'
G checkout -q -B c3 "$M"; mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt"; G add -f "$REC/walk.txt"; G commit -q -m c3 || die c3; M3=$(git rev-parse HEAD); [ "$M3" != "$M" ] || die c3-moved; r1; r3 "$M3" c3; G checkout -q land; rm -rf "$REC"
echo 'C4 committed-then-removed, final tree unchanged (THE FINDING) -> L1 PASS, L3 STOP'
G checkout -q -B c4 "$MB"; mkdir -p "$REC" && printf 'benign\n' > "$REC/walk.txt"; G add -f "$REC/walk.txt"; G commit -q -m add || die c4a; A=$(git rev-parse HEAD); [ "$A" != "$MB" ] || die c4a-moved
G rm -q "$REC/walk.txt"; G commit -q -m rm || die c4b; B=$(git rev-parse HEAD); [ "$B" != "$A" ] || die c4b-moved
[ "$(git rev-parse "$B^{tree}")" = "$TMB" ] || die c4-tree; mergeH c4; M4=$(git rev-parse HEAD); [ "$(git rev-parse "$M4^{tree}")" = "$TM" ] || die c4-mtree
printf '  add=%s rm=%s tree(rm)==tree(main-before) merge=%s tree==C1 tree\n' "$A" "$B" "$M4"; r1; r3 "$M4" c4; plain "$M4"
echo 'C5 history query fails with EMPTY output (shim rev-list: rc 128, no output) -> STOP'
SH_DIR=$W/shim5; mkdir -p "$SH_DIR"; RG=$(command -v git)
printf '#!/usr/bin/env bash\nfor a in "$@"; do [ "$a" = rev-list ] && { echo "fatal: shim" >&2; exit 128; }; done\nexec %s "$@"\n' "$RG" > "$SH_DIR/git"; chmod +x "$SH_DIR/git"
( PATH=$SH_DIR:$PATH; r3 "$M" "merge,shim-empty" )
echo 'C6 history query fails with PARTIAL output (shim: first real line, then rc 141) -> STOP'
SH_DIR=$W/shim6; mkdir -p "$SH_DIR"
printf '#!/usr/bin/env bash\nfor a in "$@"; do [ "$a" = rev-list ] && { %s "$@" | head -1; exit 141; }; done\nexec %s "$@"\n' "$RG" "$RG" > "$SH_DIR/git"; chmod +x "$SH_DIR/git"
( PATH=$SH_DIR:$PATH; r3 "$M4" "c4,shim-partial" ); ( PATH=$SH_DIR:$PATH; r3 "$M" "merge,shim-partial-on-clean" )
echo 'C7 add+remove on a SIDE branch merged TREESAME, then merge H (trap 2) -> L3 STOP'
G checkout -q -B c7 "$MB"; G merge -q --no-ff --no-edit -m side "$B" >/dev/null 2>&1 || die c7-side; [ "$(git rev-parse "HEAD^{tree}")" = "$TMB" ] || die c7-tree; mergeH c7; M7=$(git rev-parse HEAD); printf '  merge=%s\n' "$M7"; r1; r3 "$M7" c7; plain "$M7"
echo 'C8 replace ref grafts rm onto main-before, hiding add from a replace-honouring query -> L3 STOP; push publishes add'
G replace --graft "$B" "$MB" || die c8-graft; plain "$M4"; r3 "$M4" "c4,replaced"
git init -q --bare "$W/bare.git"; G push -q "$W/bare.git" "${M4}:refs/heads/main" 2>/dev/null; printf '  push rc=%s ; add commit in bare: ' "$?"; git -C "$W/bare.git" cat-file -e "$A" 2>/dev/null && echo present || echo absent
G replace -d "$B" >/dev/null || die c8-undo
echo 'C9 ref guards -> each STOP'
r3 main 'main'; r3 "${M:0:12}" 'abbrev12'; r3 "$(printf '%s' "$M" | tr a-f A-F)" 'uppercase'; r3 '' 'empty'; r3 "$TM" 'tree-sha'; r3 0000000000000000000000000000000000000001 'absent-sha'
o=$(bash -c "$L3" 2>&1); printf '  L3[unsubstituted] rc=%s out=%s\n' "$?" "$(printf '%s' "$o" | head -1)"
echo 'C10 pin mutants (the extraction rule) -> STOP'
cp "$PLAN" "$W/mut-dup.md"; python3 - "$W/mut-dup.md" <<'PY'
import sys;p=sys.argv[1];L=open(p).read().split("\n");i=[k for k,x in enumerate(L) if x.strip().startswith("`HREF=<merge>;")][0];L.insert(i,L[i]);open(p,"w").write("\n".join(L))
PY
cp "$PLAN" "$W/mut-drop.md"; sed -i '' 's/ --full-history "\$HREF"/ "$HREF"/' "$W/mut-drop.md"
for f in mut-dup mut-drop; do c=$(python3 -c 'import sys;L=open(sys.argv[1]).read().split("\n");m=[x.strip()[1:-1] for x in L if x.strip().startswith("`HREF=<merge>;") and x.strip().endswith("`")];import hashlib;print(len(m), hashlib.sha256(m[0].encode()).hexdigest()[:8] if m else "-")' "$W/$f.md"); printf '  %s: count,sha8=%s (pin 08e2ce06 count 1)\n' "$f" "$c"; done
echo 'walk-complete'
