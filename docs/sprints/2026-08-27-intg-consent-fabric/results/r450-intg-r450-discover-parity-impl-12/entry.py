#!/usr/bin/env python3
# usage: entry.py <B-cells.txt> <tuples-macos.txt> <tuples-linux.txt> <predictor.txt> <bpc-table.txt>
# ENTRY (CG-R7.1) + the consistency CHECK (T-4) on the record: exit 0 iff on BOTH targets the biv_tests successes differ from B's cell by exactly
# (added - removed) read from predictor.txt (a nonzero delta), failures = expectedFailures = 0, skips == B's cell, and the other four binaries'
# cells equal B's; writes the old(B)/observed(P) table (one line per binary per target; new(C) filled at Task 3). exit 5 = a FINDING (each row
# printed); 2 = a missing line / malformed input. The literals written at Task 3 come from the XML, never from this check.
import sys
def cells(path):
    rows = {}
    for line in open(path, encoding="utf-8"):
        p = line.split()
        if len(p) >= 6 and p[0].startswith("biv_") and p[2].startswith("successes="):
            rows[(p[0], p[1])] = {k: int(v) for k, v in (x.split("=", 1) for x in p[2:6])}
    return rows
b = cells(sys.argv[1])
o = {**cells(sys.argv[2]), **cells(sys.argv[3])}
pred = dict(x.split("=", 1) for x in open(sys.argv[4], encoding="utf-8").read().split())
if len(b) != 10 or set(b) != set(o) or set(pred) != {"added", "removed"}:
    sys.exit(2)
delta = int(pred["added"]) - int(pred["removed"])
bad = 0
out = []
for key in sorted(b):
    B, O = b[key], o[key]
    if key[0] == "biv_tests":
        ok = delta != 0 and O["successes"] - B["successes"] == delta and O["failures"] == 0 and O["expectedFailures"] == 0 and O["skips"] == B["skips"]
    else:
        ok = O == B
    bad += 0 if ok else 1
    out.append(f"{key[0]} {key[1]} old_B={B['successes']} observed_P={O['successes']} new_C=pending {'ok' if ok else 'FINDING'}")
open(sys.argv[5], "w", encoding="utf-8").write("\n".join(out) + "\n")
print("\n".join(out))
sys.exit(0 if bad == 0 else 5)
