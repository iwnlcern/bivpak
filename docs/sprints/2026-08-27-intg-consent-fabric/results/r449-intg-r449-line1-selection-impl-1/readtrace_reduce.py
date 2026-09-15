#!/usr/bin/env python3
# readtrace_reduce.py <trace.tsv> <prefix> — reduces the readtrace shim's appended rows ("<abs path>\t<bytes>", one set per process exit) to ONE row
# per file under <prefix>: path-relative-to-prefix<TAB>bytes_read, summed across processes, sorted by path. No content is involved at any point.
import sys
trace, prefix = sys.argv[1], sys.argv[2].rstrip("/") + "/"
acc = {}
for line in open(trace, encoding="utf-8", errors="replace"):
    line = line.rstrip("\n")
    if "\t" not in line: continue
    p, b = line.rsplit("\t", 1)
    if not p.startswith(prefix) or not b.isdigit(): continue
    rel = p[len(prefix):]; acc[rel] = acc.get(rel, 0) + int(b)
for p in sorted(acc): print("%s\t%d" % (p, acc[p]))
