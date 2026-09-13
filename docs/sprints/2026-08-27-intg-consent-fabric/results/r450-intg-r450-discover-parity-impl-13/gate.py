#!/usr/bin/env python3
# usage: gate.py <C-cells.txt> <P-macos> <P-linux> <C-macos> <C-linux>  — exit 0 iff every cell agrees across literal(C), observed(P), observed(C)
import sys
def read(path):
    rows = {}
    for line in open(path, encoding="utf-8"):
        parts = line.split()
        if len(parts) >= 6 and parts[0].startswith("biv_") and parts[2].startswith("successes="):
            rows[(parts[0], parts[1])] = tuple(p.split("=", 1)[1] for p in parts[2:6])
    return rows
literals = read(sys.argv[1])
observed_p = {**read(sys.argv[2]), **read(sys.argv[3])}
observed_c = {**read(sys.argv[4]), **read(sys.argv[5])}
if len(literals) != 10 or set(literals) != set(observed_p) or set(literals) != set(observed_c):
    sys.exit(2)
bad = 0
for key in sorted(literals):
    ok = literals[key] == observed_p[key] == observed_c[key]
    bad += 0 if ok else 1
    print(f"{key[0]} {key[1]} literal_C={literals[key]} observed_P={observed_p[key]} observed_C={observed_c[key]} equal={'yes' if ok else 'no'}")
sys.exit(0 if bad == 0 else 5)
