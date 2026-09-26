# rev33 (master 215035 R3(iii), 224030): an EARLIER Task 9 attempt's outputs are PRESERVED before this run writes anything — three renames into a stage, verified, ONE publishing rename, re-verified; never a copy, never a delete; a fault before the publish renames everything back and proves the originals byte-identical
PMANI() { python3 - "$1" "$3" > "$2" <<'PY'
import hashlib, os, stat, sys
root = sys.argv[1]; out = []
def row(rel):
    p = os.path.join(root, rel); st = os.lstat(p); mode = stat.S_IMODE(st.st_mode)
    if stat.S_ISLNK(st.st_mode):
        out.append("l %o - %s %s" % (mode, os.readlink(p), rel))
    elif stat.S_ISDIR(st.st_mode):
        out.append("d %o - - %s" % (mode, rel))
        for n in sorted(os.listdir(p)):
            row(os.path.join(rel, n))
    elif stat.S_ISREG(st.st_mode):
        h = hashlib.sha256()
        with open(p, "rb") as f:
            for chunk in iter(lambda: f.read(1 << 20), b""):
                h.update(chunk)
        out.append("f %o %d %s %s" % (mode, st.st_size, h.hexdigest(), rel))
    else:
        out.append("x %o - - %s" % (mode, rel))
for rel in ["H", "H0.txt", "helpers.verify-9.txt"] + ["B/" + n for n in open(sys.argv[2], encoding="utf-8").read().split("\n") if n]:
    row(rel)
sys.stdout.write("".join(x + "\n" for x in out))
PY
}
# rev36 (impl-11's STOP 130242): an earlier attempt's B Linux leg lives in B/ beside Task 0's fifteen macOS records — BLEG prints every B/ entry
# outside those fifteen (sorted), exit 3 unless all fifteen are present as regular files
BLEG() { python3 - "$EVID/B" > "$1" <<'PY'
import os, sys
T0 = frozenset(("biv_probe_tests-macos.stderr", "biv_probe_tests-macos.xml", "biv_repo_engine_tests-macos.stderr", "biv_repo_engine_tests-macos.xml", "biv_repo_git_tests-macos.stderr", "biv_repo_git_tests-macos.xml", "biv_subprocess_tests-macos.stderr", "biv_subprocess_tests-macos.xml", "biv_tests-macos.stderr", "biv_tests-macos.xml", "build-B.log", "configure-B.log", "run-rcs-macos.txt", "skipset-macos.txt", "tuples-macos.txt"))
d = sys.argv[1]
if any(os.path.islink(os.path.join(d, n)) or not os.path.isfile(os.path.join(d, n)) for n in T0):
    sys.exit(3)
sys.stdout.write("".join(n + "\n" for n in sorted(os.listdir(d)) if n not in T0))
PY
}
for x in series H9 H.txt commits.c9.txt; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done
[ -d "$EVID/B" ] && [ ! -L "$EVID/B" ] && [ -d "$EVID/work" ] && [ ! -L "$EVID/work" ] || STOP
# rev38 (MUST-2B-52): CONFINEMENT before the first write — work/ and B/ physically the home's own, and no symlink directly under the home, work/ or B/, so no fixed name this runner writes with > can be redirected (H/, H9/ and series/ are made fresh)
p=0; RH=$(cd "$EVID" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ -n "$RH" ] && [ "$(cd "$EVID/work" && pwd -P)" = "$RH/work" ] && [ "$(cd "$EVID/B" && pwd -P)" = "$RH/B" ] || STOP
b=0; BLEG "$EVID/work/B-leg.names" || b=$?; [ "$b" -eq 0 ] || STOP
if [ -e "$EVID/H0.txt" ] || [ -L "$EVID/H0.txt" ]; then
  [ -f "$EVID/H0.txt" ] && [ ! -L "$EVID/H0.txt" ] && [ -d "$EVID/H" ] && [ ! -L "$EVID/H" ] && [ -f "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
  a=0; n=$(awk 'END { print NR }' "$EVID/H0.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP
  g=0; PH0=$(sed -n -E 's/^H0=([0-9a-f]{40})$/\1/p' "$EVID/H0.txt") || g=$?; [ "$g" -eq 0 ] && [ -n "$PH0" ] || STOP
  PN=task9-H0-${PH0:0:7}; PT=$EVID/attempts/$PN
  if [ ! -e "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ]; then m=0; mkdir "$EVID/attempts" || m=$?; [ "$m" -eq 0 ] || STOP; fi
  [ -d "$EVID/attempts" ] && [ ! -L "$EVID/attempts" ] || STOP
  p=0; AP=$(cd "$EVID/attempts" && pwd -P) || p=$?; [ "$p" -eq 0 ] && [ "$AP" = "$(cd "$EVID" && pwd -P)/attempts" ] || STOP
  d=0; DE=$(stat -f %d "$EVID") || d=$?; [ "$d" -eq 0 ] && [ -n "$DE" ] && [ "$(stat -f %d "$EVID/attempts")" = "$DE" ] && [ "$(stat -f %d "$EVID/H")" = "$DE" ] && [ "$(stat -f %d "$EVID/B")" = "$DE" ] || STOP
  [ ! -e "$PT" ] && [ ! -L "$PT" ] || STOP
  PS=$(mktemp -d "$EVID/attempts/stage-$PN.XXXXXX") || STOP; [ -d "$PS" ] && [ ! -L "$PS" ] || STOP
  c=0; cp "$EVID/work/B-leg.names" "$PS/B-leg.names" || c=$?; [ "$c" -eq 0 ] && cmp -s "$EVID/work/B-leg.names" "$PS/B-leg.names" || STOP
  m=0; mkdir "$PS/B" || m=$?; [ "$m" -eq 0 ] || STOP
  q=0; PMANI "$EVID" "$PS/MANIFEST.pre" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] && [ -s "$PS/MANIFEST.pre" ] || STOP
  PBACK() { local y; for y in helpers.verify-9.txt H0.txt H; do if [ -e "$PS/$y" ] || [ -L "$PS/$y" ]; then { [ ! -e "$EVID/$y" ] && [ ! -L "$EVID/$y" ] && mv "$PS/$y" "$EVID/$y"; } || { printf 'STOP-task-9 preserve-rollback %s (%s)\n' "$y" "$1" >&2; exit 1; }; fi; done
    while IFS= read -r y; do [ -n "$y" ] || continue; if [ -e "$PS/B/$y" ] || [ -L "$PS/B/$y" ]; then { [ ! -e "$EVID/B/$y" ] && [ ! -L "$EVID/B/$y" ] && mv "$PS/B/$y" "$EVID/B/$y"; } || { printf 'STOP-task-9 preserve-rollback B/%s (%s)\n' "$y" "$1" >&2; exit 1; }; fi; done < "$PS/B-leg.names"
    local q=0; PMANI "$EVID" "$PS/MANIFEST.back" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] && cmp -s "$PS/MANIFEST.pre" "$PS/MANIFEST.back" || { printf 'STOP-task-9 preserve-rollback-verify (%s)\n' "$1" >&2; exit 1; }
    printf 'STOP-task-9 preserve-fault %s: rolled back, originals byte-identical\n' "$1" >&2; exit 1; }
  for x in H H0.txt helpers.verify-9.txt; do v=0; mv "$EVID/$x" "$PS/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-$x"; done
  while IFS= read -r x; do [ -n "$x" ] || continue; v=0; mv "$EVID/B/$x" "$PS/B/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-B/$x"; done < "$PS/B-leg.names"
  q=0; PMANI "$PS" "$PS/MANIFEST.stage" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] || PBACK stage-manifest
  c=0; cmp -s "$PS/MANIFEST.pre" "$PS/MANIFEST.stage" || c=$?; [ "$c" -eq 0 ] || PBACK stage-differs
  [ ! -e "$PT" ] && [ ! -L "$PT" ] || PBACK target-appeared
  v=0; mv "$PS" "$PT" || v=$?; [ "$v" -eq 0 ] || PBACK publish
  [ -d "$PT" ] && [ ! -L "$PT" ] && [ ! -e "$PS" ] && [ ! -L "$PS" ] || STOP
  q=0; PMANI "$PT" "$PT/MANIFEST.post" "$PT/B-leg.names" || q=$?; [ "$q" -eq 0 ] || STOP
  c=0; cmp -s "$PT/MANIFEST.pre" "$PT/MANIFEST.post" || c=$?; [ "$c" -eq 0 ] || STOP
  m=0; mkdir "$EVID/H" || m=$?; [ "$m" -eq 0 ] || STOP
  h=0; PMS=$(shasum -a 256 "$PT/MANIFEST.pre" | cut -d' ' -f1) || h=$?; [ "$h" -eq 0 ] && [ -n "$PMS" ] || STOP
  a=0; PMN=$(awk 'END { print NR }' "$PT/MANIFEST.pre") || a=$?; [ "$a" -eq 0 ] || STOP
  a=0; PBN=$(awk 'END { print NR }' "$PT/B-leg.names") || a=$?; [ "$a" -eq 0 ] || STOP
  printf 'preserved=attempts/%s manifest_sha256=%s manifest_rows=%s b_leg_files=%s\n' "$PN" "$PMS" "$PMN" "$PBN" > "$EVID/H/preserved-attempt.txt" || STOP
else
  [ ! -s "$EVID/work/B-leg.names" ] || STOP
  [ ! -e "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
  if [ ! -e "$EVID/H" ] && [ ! -L "$EVID/H" ]; then m=0; mkdir "$EVID/H" || m=$?; [ "$m" -eq 0 ] || STOP; fi
  [ -d "$EVID/H" ] && [ ! -L "$EVID/H" ] || STOP
  f=0; find "$EVID/H" -mindepth 1 -maxdepth 1 > "$EVID/work/H-prior-entries.txt" || f=$?; [ "$f" -eq 0 ] && [ ! -s "$EVID/work/H-prior-entries.txt" ] || STOP
  printf 'preserved=none\n' > "$EVID/H/preserved-attempt.txt" || STOP
fi
[ -s "$EVID/H/preserved-attempt.txt" ] || STOP
b=0; BLEG "$EVID/work/B-leg.post" || b=$?; [ "$b" -eq 0 ] && [ ! -s "$EVID/work/B-leg.post" ] || STOP
