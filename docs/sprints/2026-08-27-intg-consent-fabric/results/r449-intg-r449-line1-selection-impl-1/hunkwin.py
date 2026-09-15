#!/usr/bin/env python3
# usage: hunkwin.py <unified-diff-U0> <lo1>-<hi1>[,<lo2>-<hi2>...]  — exit 0 iff EVERY hunk's OLD-side span (`@@ -a[,n]`) lies inside one of the
# windows (base-file line numbers); prints each hunk with its verdict. A hunk outside every window = exit 5: a byte landed outside the TOUCHABLE
# functions (the discover bodies, the sqlite enrichment, the install side stay byte-identical because no hunk reaches them).
import re, sys
wins = [tuple(int(x) for x in w.split("-")) for w in sys.argv[2].split(",")]
bad = 0; n = 0
for line in open(sys.argv[1], encoding="utf-8"):
    m = re.match(r"^@@ -(\d+)(?:,(\d+))? \+", line)
    if not m: continue
    n += 1; a = int(m.group(1)); cnt = int(m.group(2)) if m.group(2) is not None else 1; b = a + max(cnt, 1) - 1
    ok = any(lo <= a and b <= hi for lo, hi in wins); bad += 0 if ok else 1
    print("hunk old=%d..%d %s" % (a, b, "ok" if ok else "OUTSIDE"))
print("hunks=%d outside=%d" % (n, bad))
sys.exit(0 if (n >= 1 and bad == 0) else 5)
