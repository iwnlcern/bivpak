#!/usr/bin/env python3
# patch9.py <rev35 task-9 runner> <out> — the rev36 task-9 runner edits, each an exact unique replacement
import sys
src = open(sys.argv[1], encoding="utf-8").read()
def rep(old, new, n=1):
    global src
    k = src.count(old)
    if k != n:
        sys.exit("count %d != %d for: %s" % (k, n, old[:90]))
    src = src.replace(old, new)
T0 = ("biv_probe_tests-macos.stderr", "biv_probe_tests-macos.xml", "biv_repo_engine_tests-macos.stderr", "biv_repo_engine_tests-macos.xml",
      "biv_repo_git_tests-macos.stderr", "biv_repo_git_tests-macos.xml", "biv_subprocess_tests-macos.stderr", "biv_subprocess_tests-macos.xml",
      "biv_tests-macos.stderr", "biv_tests-macos.xml", "build-B.log", "configure-B.log", "run-rcs-macos.txt", "skipset-macos.txt", "tuples-macos.txt")
# 1. PMANI takes the B-leg list as a third argument; its rows cover the B leg too
rep('''PMANI() { python3 - "$1" > "$2" <<'PY'
''', '''PMANI() { python3 - "$1" "$3" > "$2" <<'PY'
''')
rep('''for rel in ("H", "H0.txt", "helpers.verify-9.txt"):
    row(rel)''', '''for rel in ["H", "H0.txt", "helpers.verify-9.txt"] + ["B/" + n for n in open(sys.argv[2], encoding="utf-8").read().split("\\n") if n]:
    row(rel)''')
# 2. BLEG, after PMANI's definition
bleg = '''# rev36 (impl-11's STOP 130242): an earlier attempt's B Linux leg lives in B/ beside Task 0's fifteen macOS records — BLEG prints every B/ entry
# outside those fifteen (sorted), exit 3 unless all fifteen are present as regular files
BLEG() { python3 - "$EVID/B" > "$1" <<'PY'
import os, sys
T0 = frozenset((%s))
d = sys.argv[1]
if any(os.path.islink(os.path.join(d, n)) or not os.path.isfile(os.path.join(d, n)) for n in T0):
    sys.exit(3)
sys.stdout.write("".join(n + "\\n" for n in sorted(os.listdir(d)) if n not in T0))
PY
}
''' % ", ".join('"%s"' % n for n in T0)
rep('''sys.stdout.write("".join(x + "\\n" for x in out))
PY
}
for x in series H9 B/linux-container.log B/linux-container.rc; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done
''', '''sys.stdout.write("".join(x + "\\n" for x in out))
PY
}
''' + bleg + '''for x in series H9; do [ ! -e "$EVID/$x" ] && [ ! -L "$EVID/$x" ] || STOP; done
[ -d "$EVID/B" ] && [ ! -L "$EVID/B" ] && [ -d "$EVID/work" ] && [ ! -L "$EVID/work" ] || STOP
b=0; BLEG "$EVID/work/B-leg.names" || b=$?; [ "$b" -eq 0 ] || STOP
''')
# 3. device check covers B/
rep('''[ "$(stat -f %d "$EVID/H")" = "$DE" ] || STOP''', '''[ "$(stat -f %d "$EVID/H")" = "$DE" ] && [ "$(stat -f %d "$EVID/B")" = "$DE" ] || STOP''')
# 4. the list travels in the stage; every manifest reads it
rep('''  PS=$(mktemp -d "$EVID/attempts/stage-$PN.XXXXXX") || STOP; [ -d "$PS" ] && [ ! -L "$PS" ] || STOP
  q=0; PMANI "$EVID" "$PS/MANIFEST.pre" || q=$?; [ "$q" -eq 0 ] && [ -s "$PS/MANIFEST.pre" ] || STOP
''', '''  PS=$(mktemp -d "$EVID/attempts/stage-$PN.XXXXXX") || STOP; [ -d "$PS" ] && [ ! -L "$PS" ] || STOP
  c=0; cp "$EVID/work/B-leg.names" "$PS/B-leg.names" || c=$?; [ "$c" -eq 0 ] && cmp -s "$EVID/work/B-leg.names" "$PS/B-leg.names" || STOP
  m=0; mkdir "$PS/B" || m=$?; [ "$m" -eq 0 ] || STOP
  q=0; PMANI "$EVID" "$PS/MANIFEST.pre" "$PS/B-leg.names" || q=$?; [ "$q" -eq 0 ] && [ -s "$PS/MANIFEST.pre" ] || STOP
''')
rep('''fi; done
    local q=0; PMANI "$EVID" "$PS/MANIFEST.back" || q=$?;''', '''fi; done
    while IFS= read -r y; do [ -n "$y" ] || continue; if [ -e "$PS/B/$y" ] || [ -L "$PS/B/$y" ]; then { [ ! -e "$EVID/B/$y" ] && [ ! -L "$EVID/B/$y" ] && mv "$PS/B/$y" "$EVID/B/$y"; } || { printf 'STOP-task-9 preserve-rollback B/%s (%s)\\n' "$y" "$1" >&2; exit 1; }; fi; done < "$PS/B-leg.names"
    local q=0; PMANI "$EVID" "$PS/MANIFEST.back" "$PS/B-leg.names" || q=$?;''')
rep('''  for x in H H0.txt helpers.verify-9.txt; do v=0; mv "$EVID/$x" "$PS/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-$x"; done
  q=0; PMANI "$PS" "$PS/MANIFEST.stage" || q=$?;''', '''  for x in H H0.txt helpers.verify-9.txt; do v=0; mv "$EVID/$x" "$PS/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-$x"; done
  while IFS= read -r x; do [ -n "$x" ] || continue; v=0; mv "$EVID/B/$x" "$PS/B/$x" || v=$?; [ "$v" -eq 0 ] || PBACK "move-B/$x"; done < "$PS/B-leg.names"
  q=0; PMANI "$PS" "$PS/MANIFEST.stage" "$PS/B-leg.names" || q=$?;''')
rep('''  q=0; PMANI "$PT" "$PT/MANIFEST.post" || q=$?;''', '''  q=0; PMANI "$PT" "$PT/MANIFEST.post" "$PT/B-leg.names" || q=$?;''')
rep('''  a=0; PMN=$(awk 'END { print NR }' "$PT/MANIFEST.pre") || a=$?; [ "$a" -eq 0 ] || STOP
  printf 'preserved=attempts/%s manifest_sha256=%s manifest_rows=%s\\n' "$PN" "$PMS" "$PMN" > "$EVID/H/preserved-attempt.txt" || STOP''',
'''  a=0; PMN=$(awk 'END { print NR }' "$PT/MANIFEST.pre") || a=$?; [ "$a" -eq 0 ] || STOP
  a=0; PBN=$(awk 'END { print NR }' "$PT/B-leg.names") || a=$?; [ "$a" -eq 0 ] || STOP
  printf 'preserved=attempts/%s manifest_sha256=%s manifest_rows=%s b_leg_files=%s\\n' "$PN" "$PMS" "$PMN" "$PBN" > "$EVID/H/preserved-attempt.txt" || STOP''')
# 5. the fresh branch refuses a B leg; after either branch B/ holds exactly Task 0's fifteen
rep('''else
  [ ! -e "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
''', '''else
  [ ! -s "$EVID/work/B-leg.names" ] || STOP
  [ ! -e "$EVID/helpers.verify-9.txt" ] && [ ! -L "$EVID/helpers.verify-9.txt" ] || STOP
''')
rep('''[ -s "$EVID/H/preserved-attempt.txt" ] || STOP
''', '''[ -s "$EVID/H/preserved-attempt.txt" ] || STOP
b=0; BLEG "$EVID/work/B-leg.post" || b=$?; [ "$b" -eq 0 ] && [ ! -s "$EVID/work/B-leg.post" ] || STOP
''')
# 6. the Linux skip set UNCHANGED = H0's observed set equals B's observed set (B pins none: cells.py's `absent` form, asserted)
rep('''q=0; python3 "$EVID/skipset.py" "$EVID/B-cells.txt" "$EVID/H/tuples-linux.txt" linux > "$EVID/H/skipset-linux.txt" || q=$?; [ "$q" -eq 0 ] || STOP
''', '''g=0; k=$(grep -c -E '^expected_skips linux ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F 'expected_skips linux absent ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
for T in B H; do g=0; grep -E '^expected_skips_observed linux n=[0-9]+ ' "$EVID/$T/tuples-linux.txt" > "$EVID/H/skipset-linux-$T.txt" || g=$?; [ "$g" -eq 0 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/H/skipset-linux-$T.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP; done
q=0; cmp "$EVID/H/skipset-linux-B.txt" "$EVID/H/skipset-linux-H.txt" > "$EVID/H/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\\n' "$q" > "$EVID/H/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP
''')
# 7. E3 read in the runner (xmlcases.py e3 tests an Element's truth value: a childless <OverallResult> is falsy, so a green case read success=None)
rep('''x=0; python3 "$EVID/xmlcases.py" e3 "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" || x=$?; printf 'e3_linux_rc=%s\\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
''', '''x=0; python3 - "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" <<'PY' || x=$?
import sys, xml.etree.ElementTree as ET
rows = []
for tc in ET.fromstring(open(sys.argv[1], "rb").read()).iter("TestCase"):
    if "[E3]" in (tc.get("tags") or ""):
        o = tc.find("OverallResult")
        rows.append((tc.get("name"), None if o is None else o.get("success")))
if not rows:
    print("E3 cases=0"); sys.exit(3)
for name, ok in rows:
    print("E3 case=%r success=%s" % (name, ok))
sys.exit(0 if all(ok == "true" for _, ok in rows) else 5)
PY
printf 'e3_linux_rc=%s\\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
''')
# 8. the fence-proofs carry the Linux skip-set receipt
rep('''"$EVID/H/E3-linux.rc" "$EVID/H/harness-e2-macos.rc"''', '''"$EVID/H/E3-linux.rc" "$EVID/H/skipset-linux.rc" "$EVID/H/harness-e2-macos.rc"''')
open(sys.argv[2], "w", encoding="utf-8").write(src)
print("ok")
