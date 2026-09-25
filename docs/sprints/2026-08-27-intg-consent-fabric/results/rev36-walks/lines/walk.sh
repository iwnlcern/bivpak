#!/bin/bash
set -u
W=$(cd "$(dirname "$0")" && pwd -P); CASE=$1; MIR=$(cd "$W/../mirror" && pwd -P)
[ "$(awk 'END{print NR}' "$W/snip.sh")" -ge 20 ] || { echo "WALK-INVALID"; exit 9; }
R=$W/runs/$CASE; rm -rf "$R"; mkdir -p "$R"; M=$R/home; mkdir "$M"; for x in B H B-cells.txt cellgate.py; do cp -Rp "$MIR/$x" "$M/$x"; done
X=$M/H/biv_tests-linux.xml
case "$CASE" in
  yes) :;;
  h-name) sed -i '' 's/^expected_skips_observed linux n=1 .*/expected_skips_observed linux n=1 some other skipped case/' "$M/H/tuples-linux.txt";;
  h-count) sed -i '' 's/^\(expected_skips_observed linux \)n=1 \(.*\)/\1n=2 \2 | zz extra/' "$M/H/tuples-linux.txt";;
  b-pinned) sed -i '' 's/^expected_skips linux absent $/expected_skips linux n=1 threshold-parity per-agent distribution self-activates at R-4.29/' "$M/B-cells.txt";;
  b-two-rows) printf 'expected_skips linux absent \n' >> "$M/B-cells.txt";;
  h-dup) grep '^expected_skips_observed linux' "$M/H/tuples-linux.txt" >> "$M/H/tuples-linux.txt";;
  b-missing) sed -i '' '/^expected_skips_observed linux/d' "$M/B/tuples-linux.txt";;
  e3-false) python3 - "$X" <<'PY'
import sys,re;p=sys.argv[1];t=open(p,encoding="utf-8").read()
i=t.index('[E3]'); j=t.index('<OverallResult success="true"',i); t=t[:j]+'<OverallResult success="false"'+t[j+len('<OverallResult success="true"'):]; open(p,"w",encoding="utf-8").write(t)
PY
  ;;
  e3-none) python3 - "$X" <<'PY'
import sys;p=sys.argv[1];t=open(p,encoding="utf-8").read(); t=t.replace('[E3]','[E-THREE]'); open(p,"w",encoding="utf-8").write(t)
PY
  ;;
esac
rc=$( cd "$M" && EVID="$M" bash -c 'set -u; set -o pipefail; STOP() { printf "STOP-task-9 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }; source "$1"; echo DONE' _ "$W/snip.sh" > "$R/out" 2> "$R/err"; echo $? )
printf 'case=%s rc=%s done=%s stop="%s" skipset_rc="%s" e3_rc="%s"\n' "$CASE" "$rc" "$(grep -c DONE "$R/out")" "$(grep -m1 -o 'STOP-task-9.*' "$R/err")" "$(cat "$M/H/skipset-linux.rc" 2>/dev/null)" "$(cat "$M/H/E3-linux.rc" 2>/dev/null)"
