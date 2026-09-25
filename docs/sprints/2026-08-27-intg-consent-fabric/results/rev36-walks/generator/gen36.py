#!/usr/bin/env python3
# gen36.py <rev35.md> <task9-rev35.sh> <task9-rev36.sh> <out rev36.md> — the rev36 plan from rev35, every edit an exact unique replacement
import sys
src = open(sys.argv[1], encoding="utf-8").read()
r35 = open(sys.argv[2], encoding="utf-8").read(); r36 = open(sys.argv[3], encoding="utf-8").read()
def rep(old, new, n=1):
    global src
    k = src.count(old)
    if k != n:
        sys.exit("count %d != %d for: %s" % (k, n, old[:100]))
    src = src.replace(old, new)
cut = "# Runner plumbing (Task 9)\n"
b35 = r35[r35.index(cut):]; b36 = r36[r36.index(cut):]
assert r35[:r35.index(cut)] == r36[:r36.index(cut)]
# E1 the task-9 RUN body
rep("<!-- RUN: task-9 -->\n```bash\n" + b35, "<!-- RUN: task-9 -->\n```bash\n" + b36)
# E2 Task 9 Step 0 prose
rep("when `H0.txt` exists, it must be one `H0=<40-hex>` line beside a real `H/` directory and a real `helpers.verify-9.txt`; the three are recorded by a manifest (type, mode, size and sha256 of every entry, recursively, symlinks by target), renamed one by one into a fresh `mktemp -d` stage inside a confined `$EVID/attempts` (a real directory whose physical path is the home's own, on the home's device), the stage's manifest must equal the recorded one, and ONE rename publishes the stage as `attempts/task9-H0-<first seven of that H0>` (impl-10's → `task9-H0-a83657e`, the name master gave), re-verified after; then a fresh empty `H/` is made and `H/preserved-attempt.txt` names the attempt and the manifest's digest.",
    "when `H0.txt` exists, it must be one `H0=<40-hex>` line beside a real `H/` directory and a real `helpers.verify-9.txt`; rev36 (impl-11's STOP `intg-substep2b/IMPL-pair-implementer-20260925-130242.md`): the attempt also owns the B Linux leg it wrote into `B/` beside Task 0's fifteen macOS records — `BLEG` lists every `B/` entry outside those fifteen (`biv_{probe,repo_engine,repo_git,subprocess}_tests-macos.{stderr,xml}`, `biv_tests-macos.{stderr,xml}`, `build-B.log`, `configure-B.log`, `run-rcs-macos.txt`, `skipset-macos.txt`, `tuples-macos.txt` — the names Task 0's runner writes; all fifteen must be present as regular files, else a STOP) into the scratch `work/B-leg.names`, the only write before the preservation, and the list travels in the stage as `B-leg.names`; the three and the B leg are recorded by a manifest (type, mode, size and sha256 of every entry, recursively, symlinks by target), renamed one by one into a fresh `mktemp -d` stage inside a confined `$EVID/attempts` (a real directory whose physical path is the home's own, on the home's device, as are `H/` and `B/`) — the B leg into the stage's `B/` — the stage's manifest must equal the recorded one, and ONE rename publishes the stage as `attempts/task9-H0-<first seven of that H0>` (impl-10's → `task9-H0-a83657e`, the name master gave; impl-11's → `task9-H0-99136ca`, with its 36-file B leg), re-verified after; then a fresh empty `H/` is made and `H/preserved-attempt.txt` names the attempt, the manifest's digest and row count, and the B-leg file count.")
rep("When `H0.txt` is absent, `helpers.verify-9.txt` must be absent and `H/` absent or empty (anything else is an unrecognized earlier state — a STOP, routed up). An earlier attempt's `series/`, `H9/` or B-side Linux outputs are STOPs too (none exists in this home; a revision would preserve them). Nothing is copied or deleted; `s2b-runners-sK9rhy` and every runners directory are untouched;",
    "When `H0.txt` is absent, the B leg must be empty, `helpers.verify-9.txt` absent and `H/` absent or empty (anything else is an unrecognized earlier state — a STOP, routed up). An earlier attempt's `series/` or `H9/` is a STOP too (none exists in this home). After either branch `B/` holds exactly Task 0's fifteen (`BLEG` empty) or the runner STOPs, so the B leg this run writes starts empty. Nothing is copied or deleted; every runners directory (`s2b-runners-aY2Suc` included) is untouched;")
# E3 Task 9 Step 4 prose: the Linux skip set and E3
span = [l for l in b36.split("\n") if l.startswith("q=0; cmp \"$EVID/H/skipset-linux-B.txt\"")]
assert len(span) == 1 and "`" not in span[0]
rep("`cellgate.py … linux` (data) and the Linux skip set UNCHANGED (STOP otherwise); E3 from the H0 `biv_tests-linux.xml` (`[E3]`-tagged cases all successful);",
    "`cellgate.py … linux` (data) and the Linux skip set UNCHANGED (STOP otherwise) — rev36 (impl-11's STOP): B's workflow pins NO Linux skip-name set (its Linux `checks` block carries only the count `\"skips\": 1`, which `cellgate.py` gates; `cells.py` records the missing set as `expected_skips linux absent `, a form `skipset.py` does not parse — it raised `IndexError` at impl-11's line 219), so UNCHANGED on Linux is H0's OBSERVED set against B's OBSERVED set: the `absent` row asserted exactly once first (a B-cells file that pins a Linux set STOPs here instead of passing unread), then each tree's one `expected_skips_observed linux n=<k> …` line from `tuples.py` (names sorted, so byte equality is set-and-count equality) compared — `" + span[0] + "`; `skipset.py` stays the macOS gate, verbatim; E3 from the H0 `biv_tests-linux.xml` (`[E3]`-tagged cases all successful) — rev36: read by the runner itself, because `xmlcases.py e3` tests an Element's truth value (`tc.find(\"OverallResult\") or {}`) and a childless `<OverallResult>` is falsy, so it reads a green case as `success=None` (measured on impl-11's `H/biv_tests-linux.xml`: one `[E3]` case, `success=\"true\"`, and `xmlcases.py e3` rc 5); `xmlcases.py ctest-row` is unaffected and stays;")
# E4 acceptance 7 and 14, the PRV topology row
rep("skip sets unchanged on both platforms (a change is a STOP);",
    "skip sets unchanged on both platforms (a change is a STOP; macOS against B's pinned names, Linux — where B pins none — H0's observed set against B's, rev36);")
rep("impl-10's Task 9 outputs preserved byte-identical in `attempts/task9-H0-a83657e/` (`H/preserved-attempt.txt`, MANIFEST.pre == MANIFEST.post);",
    "impl-10's Task 9 outputs preserved byte-identical in `attempts/task9-H0-a83657e/` and impl-11's — with its 36-file B Linux leg — in `attempts/task9-H0-99136ca/` (`H/preserved-attempt.txt` names the latest, MANIFEST.pre == MANIFEST.post in each; `B/` holds exactly Task 0's fifteen before the B leg is re-measured);")
rep("PRV    impl-10's Task 9 outputs preserved (rev33): H/, Task 9 (its first act)          the evidence home     E1     the implementer's exact-hash review\n       H0.txt, helpers.verify-9.txt renamed through a stage into attempts/task9-H0-a83657e/, manifest-verified (`H/preserved-attempt.txt`)",
    "PRV    an earlier Task 9 attempt preserved (rev33;   Task 9 (its first act)          the evidence home     E1     the implementer's exact-hash review\n       rev36 adds its B leg): H/, H0.txt, helpers.verify-9.txt and every B/ entry outside Task 0's fifteen renamed through a stage into\n       attempts/task9-H0-<H0:7>/ (impl-10's a83657e, impl-11's 99136ca), manifest-verified (`H/preserved-attempt.txt`)")
# E5 the instruments list
rep("- `cells.py`, `tuples.py`, `skipset.py`, `selftest_summary.py` — verbatim.",
    "- `cells.py`, `tuples.py`, `skipset.py`, `selftest_summary.py` — verbatim. (rev36: `skipset.py` gates macOS only — B's workflow pins no Linux name set and `cells.py` writes that as `expected_skips linux absent `, which `skipset.py` does not parse; Task 9 compares the two Linux observed sets directly.)")
rep("- `xmlcases.py` — reads a Catch2 XML for the `[E3]`-tagged cases' results and a CTest JUnit for one named row's status (the E3 Linux witness and the `harness-e2` receipts).",
    "- `xmlcases.py` — reads a Catch2 XML for the `[E3]`-tagged cases' results and a CTest JUnit for one named row's status (the E3 Linux witness and the `harness-e2` receipts). rev36: the block is unchanged (Task 0 materialized it and `helpers.sha256` pins it), but Task 9 no longer calls its `e3` mode — `(tc.find(\"OverallResult\") or {})` tests an Element's truth value, a childless `<OverallResult>` is falsy, and a green case reads `success=None`; the runner reads the `[E3]` cases itself with `is None`. The `ctest-row` mode stays in use.")
# E6 revision history
rep("## Revision history\n\n", "## Revision history\n\n" + open(sys.argv[5], encoding="utf-8").read().rstrip("\n") + "\n")
open(sys.argv[4], "w", encoding="utf-8").write(src)
print("ok")
