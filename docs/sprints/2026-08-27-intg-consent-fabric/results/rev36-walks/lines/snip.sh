g=0; k=$(grep -c -E '^expected_skips linux ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
g=0; k=$(grep -c -x -F 'expected_skips linux absent ' "$EVID/B-cells.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP
for T in B H; do g=0; grep -E '^expected_skips_observed linux n=[0-9]+ ' "$EVID/$T/tuples-linux.txt" > "$EVID/H/skipset-linux-$T.txt" || g=$?; [ "$g" -eq 0 ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/H/skipset-linux-$T.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP; done
q=0; cmp "$EVID/H/skipset-linux-B.txt" "$EVID/H/skipset-linux-H.txt" > "$EVID/H/skipset-linux.cmp" 2>&1 || q=$?; printf 'skipset_linux_rc=%s\n' "$q" > "$EVID/H/skipset-linux.rc"; [ "$q" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" linux "$EVID/B/tuples-linux.txt" > "$EVID/B/count-gate-linux.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
c=0; python3 "$EVID/cellgate.py" "$EVID/B-cells.txt" macos "$EVID/B/tuples-macos.txt" > "$EVID/B/count-gate-macos.txt" 2>&1 || c=$?; [ "$c" -eq 0 ] || STOP
x=0; python3 - "$EVID/H/biv_tests-linux.xml" > "$EVID/H/E3-linux.txt" <<'PY' || x=$?
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
printf 'e3_linux_rc=%s\n' "$x" > "$EVID/H/E3-linux.rc"; [ "$x" -eq 0 ] || STOP
