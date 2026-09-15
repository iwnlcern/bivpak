#!/usr/bin/env python3
# usage: cellgate.py <B-cells.txt> <target> <tuples-B-<target>.txt> <tuples-H-<target>.txt>  — the COUNT-GATE proof on one target: exit 0 iff for
# each of the five binaries the literal cell at B (the workflow's bytes), the tuple OBSERVED at B and the tuple OBSERVED at H are all EQUAL
# (successes, failures, expectedFailures, skips). A difference = exit 5 (each row printed) — a STOP UP in this act, never a transcription.
import sys
def rows(path, target):
    out = {}
    for line in open(path, encoding="utf-8"):
        p = line.split()
        if len(p) >= 6 and p[0].startswith("biv_") and p[1] == target and p[2].startswith("successes="):
            out[p[0]] = tuple(x.split("=", 1)[1] for x in p[2:6])
    return out
target = sys.argv[2]
lit, ob, oh = rows(sys.argv[1], target), rows(sys.argv[3], target), rows(sys.argv[4], target)
if len(lit) != 5 or set(lit) != set(ob) or set(lit) != set(oh):
    print("MALFORMED literal=%d observed_B=%d observed_H=%d" % (len(lit), len(ob), len(oh))); sys.exit(2)
bad = 0
for b in sorted(lit):
    ok = lit[b] == ob[b] == oh[b]; bad += 0 if ok else 1
    print("%s %s literal_B=%s observed_B=%s observed_H=%s equal=%s" % (b, target, lit[b], ob[b], oh[b], "yes" if ok else "NO"))
sys.exit(0 if bad == 0 else 5)
