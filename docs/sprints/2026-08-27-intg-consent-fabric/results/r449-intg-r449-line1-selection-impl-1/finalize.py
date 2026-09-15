#!/usr/bin/env python3
# finalize.py — THE EVIDENCE-OF-RECORD SET and its proof (rev17; master 042340 ruling (2); F5 of 212145)
#   list  <evid>                      print the SET: every regular file under the evidence home, path relative to the home,
#                                     sorted bytewise, EXCLUDING any path whose components include one of the four declared
#                                     scratch classes (rederive-*, llvm22-assets-{P,C,H}.*, __pycache__, stale-ci-macos) and the
#                                     four finalizer controller receipts (runners/task-7.done|.exit, proof-7.tail, plan_blocks.sha256-7 — Task 7 is this plan's finalizer)
#   check <evid> <resdir> <manifest>  exit 0 iff SET == TRACKED TREE (every regular file under <resdir> except SHA256SUMS)
#                                     == MANIFEST PATHS, in order and multiplicity; every manifest digest equals the tracked
#                                     file's sha256 recomputed here (hashlib); every tracked file's digest equals its home
#                                     twin's. 5 = a difference (the first ones printed); 2 = usage or an unreadable input.
import hashlib, os, re, sys
SCRATCH = (re.compile(r"^work$"), re.compile(r"^census-raw$"), re.compile(r"^strace-[HB]\.log$"), re.compile(r"^llvm22-assets-[HB]\.[A-Za-z0-9]+$"),
           re.compile(r"^__pycache__$"), re.compile(r"^stale-ci-macos$"))
# the FINALIZER's own controller receipts: written by run-task.sh into the home AFTER the Task 7 runner exits, so they can never
# be in the tree the finalizer proves; excluded here (declared), so a re-check after the run reproduces the same set (the
# pair Planner runs that post-controller re-check on the completed home before committing the record — Task 7 prose)
FINALIZER_RECEIPTS = frozenset(("runners/task-7.done", "runners/task-7.exit", "runners/proof-7.tail", "runners/plan_blocks.sha256-7"))
def excluded(rel):
    return rel in FINALIZER_RECEIPTS or any(p.match(c) for c in rel.split("/") for p in SCRATCH)
def files(root, skip=()):
    out = []
    for d, _dirs, names in os.walk(root):
        for n in names:
            full = os.path.join(d, n)
            if os.path.islink(full) or not os.path.isfile(full):
                continue
            rel = os.path.relpath(full, root)
            if rel in skip:
                continue
            out.append(rel)
    return sorted(out)
def evidence_set(evid):
    return [r for r in files(evid) if not excluded(r)]
def sha(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()
def main(argv):
    if len(argv) == 3 and argv[1] == "list":
        s = evidence_set(argv[2])
        sys.stdout.write("".join(x + "\n" for x in s))
        return 0 if s else 5
    if len(argv) == 5 and argv[1] == "check":
        evid, res, man = argv[2], argv[3], argv[4]
        s = evidence_set(evid)
        tree = files(res, skip=("SHA256SUMS",))
        rows = []
        for ln in open(man, encoding="utf-8").read().split("\n"):
            if not ln:
                continue
            m = re.match(r"^([0-9a-f]{64})  (?:\./)?(.+)$", ln)
            if not m:
                print("BAD-MANIFEST-ROW: " + ln)
                return 5
            rows.append((m.group(2), m.group(1)))
        mpaths = [p for p, _ in rows]
        bad = 0
        def diff(name, first, second):
            nonlocal bad
            if first != second:
                bad = 1
                sa, sb = set(first), set(second)
                for x in sorted(sa - sb)[:5]:
                    print("%s: only in first: %s" % (name, x))
                for x in sorted(sb - sa)[:5]:
                    print("%s: only in second: %s" % (name, x))
                if sa == sb:
                    print("%s: same members, order or multiplicity differs" % name)
        diff("set-vs-tree", s, tree)
        diff("set-vs-manifest", s, mpaths)
        digests_bad = 0
        for p, dgst in rows:
            full = os.path.join(res, p)
            if not os.path.isfile(full):
                digests_bad += 1
                print("digest: missing in tree " + p)
                continue
            if sha(full) != dgst:
                digests_bad += 1
                print("digest: MISMATCH manifest-vs-tree " + p)
        copies_bad = 0
        for p in s:
            home, tracked = os.path.join(evid, p), os.path.join(res, p)
            if not os.path.isfile(tracked) or sha(home) != sha(tracked):
                copies_bad += 1
                print("copy: home-vs-tree differs or missing " + p)
        print("set=%d tree=%d manifest=%d equal=%s digests=%s copies=%s" % (
            len(s), len(tree), len(rows), "no" if bad else "yes", "ok" if digests_bad == 0 else "bad", "ok" if copies_bad == 0 else "bad"))
        return 0 if (bad == 0 and digests_bad == 0 and copies_bad == 0) else 5
    print("usage: finalize.py list <evid> | check <evid> <resdir> <manifest>")
    return 2
if __name__ == "__main__":
    sys.exit(main(sys.argv))
