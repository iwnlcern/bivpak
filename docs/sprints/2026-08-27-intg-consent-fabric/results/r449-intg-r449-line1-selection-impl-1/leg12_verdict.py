#!/usr/bin/env python3
# leg12_verdict.py <bytes-B.tsv> <bytes-H.tsv> <synth-manifest.json> — LEG 1 (bytes read per candidate BEFORE/AFTER with the bound NAMED per
# file) and LEG 2 (the filter's position: every non-selected file's read at H ends within one 8 KiB stream chunk of the end of the line that
# completes the head predicate; the store-proportional term collapses). Rules, per manifest class:
#   selected                      bytes_B >= size AND bytes_H >= size          (full reads retained — V-LS-4)
#   head_end != null, not selected  bytes_B >= size AND bytes_H <= ceil(head_end / 8192) * 8192 AND bytes_H < size   (the bound, per file)
#   head_end == null              bytes_B >= size AND bytes_H >= size          (the SEALED whole-file cases: claude-no-cwd, codex-no-meta)
# A file of S absent from a trace = a violation (it was never opened). Prints one row per file (path class selected size head_end bytes_B
# bytes_H rule verdict), the per-class totals, the store totals at B and at H, then VERDICT PASS|FAIL; exit 0 iff PASS.
import json, math, sys
def load(tsv):
    d = {}
    for line in open(tsv, encoding="utf-8"):
        p, b = line.rstrip("\n").split("\t"); d[p] = int(b)
    return d
B, H, man = load(sys.argv[1]), load(sys.argv[2]), json.load(open(sys.argv[3], encoding="utf-8"))
CHUNK = 8192; fails = 0; tot = {}; totB = totH = 0
print("path\tclass\tselected\tsize\thead_end\tbytes_B\tbytes_H\trule\tverdict")
for r in man["files"]:
    p, size, he, sel = r["path"], r["size"], r["head_end"], r["selected"]
    b, h = B.get(p), H.get(p)
    if b is None or h is None:
        rule, ok = "opened-at-both", False; b = -1 if b is None else b; h = -1 if h is None else h
    elif sel:
        rule, ok = "full-both", (b >= size and h >= size)
    elif he is None:
        rule, ok = "sealed-whole-file", (b >= size and h >= size)
    else:
        bound = int(math.ceil(he / CHUNK)) * CHUNK
        rule, ok = "head<=%d" % bound, (b >= size and h <= bound and h < size)
    fails += 0 if ok else 1
    t = tot.setdefault(r["class"], [0, 0, 0]); t[0] += 1; t[1] += max(b, 0); t[2] += max(h, 0); totB += max(b, 0); totH += max(h, 0)
    print("%s\t%s\t%s\t%d\t%s\t%d\t%d\t%s\t%s" % (p, r["class"], sel, size, he, b, h, rule, "ok" if ok else "VIOLATION"))
for c in sorted(tot): print("CLASS %s files=%d bytes_B=%d bytes_H=%d" % (c, *tot[c]))
print("TOTAL files=%d bytes_B=%d bytes_H=%d ratio_H_over_B=%.4f" % (len(man["files"]), totB, totH, (totH / totB) if totB else 0.0))
print("VERDICT %s violations=%d" % ("PASS" if fails == 0 else "FAIL", fails))
sys.exit(0 if fails == 0 else 1)
