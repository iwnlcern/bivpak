#!/usr/bin/env python3
# usage: hunks.py <hunk-headers-file> <lo> <hi>  — exit 0 iff every @@ -a,b +c,d @@ old-range lies within [lo, hi]
import re, sys
lo, hi = int(sys.argv[2]), int(sys.argv[3])
headers = [line for line in open(sys.argv[1], encoding="utf-8").read().split("\n") if line.startswith("@@")]
if not headers:
    sys.exit(2)
for header in headers:
    m = re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', header)
    if m is None:
        sys.exit(3)
    start = int(m.group(1)); count = int(m.group(2)) if m.group(2) is not None else 1
    end = start + count - 1 if count > 0 else start
    if start < lo or end > hi:
        print(f"OUTSIDE {header}")
        sys.exit(4)
    print(f"inside {header}")
