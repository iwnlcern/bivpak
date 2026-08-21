## PLAN rev6 (T1 tidy repair — MR-11, MR-12, MR-13 all accepted; the recipe is now four complete inlined artifacts that I syntax-checked and gate-tested, and MR-13 is DEMONSTRATED not just conceded) — **MR-13 PROVEN AGAINST MY OWN REV5 GATE: I built the two must-be-NO logs you described and ran rev5's `sorted({...})` predicate on them. A fourth finding added on line 136 → `[136, 138, 220]` → **PASS**. The `220` check-id swapped to a different cppcoreguidelines check → `[136, 138, 220]` → **PASS**. Rev5's gate accepted both, exactly as you said. A set discards multiplicity and my regex discarded the check-id, so "exactly the three known findings and no fourth" was a sentence in my plan that the code did not implement. The tightened `(line, check-id)` list predicate now separates one must-be-YES from FIVE must-be-NO arms, and I ran all six.** **MR-11 ACCEPTED, AND THIS IS THE THIRD TIME: rev3 had a placeholder, rev4 had two, and rev5 had a labelled cross-reference sitting inside a `bash -c` program — which is still a string the shell tries to execute. Labelling an elision does not make it run. I have stopped hand-waving at rev4 and written the whole thing: a driver, a `phase.sh`, and two gate scripts, all four inlined below in full, `bash -n`/`ast.parse` clean, with `$STAGE_GATE` actually created and populated and both gates actually invoked with their exact arguments.** **MR-12 ACCEPTED and it is my own favourite defect pointed at me: `mkdir -p` on a FIXED evidence root plus a post-run `[ -s ]` check is absence-blind — on a retry, last attempt's non-empty `s3-tidy.xml` satisfies the check even if this run never wrote a byte, and a recorded source hash does not make stale bytes current. The root is now a checked `mktemp -d` per attempt, every expected file is asserted ABSENT before its run and non-empty after, and each is hashed into a `RECEIPTS.sha256`.** **ONE THING I FIXED IN MY OWN OUTER LAYER WHILE APPLYING YOURS: the container payload ends with `chown -R` on `/evidence` so the host can read it — but under `set -e` a failing `runuser` would have skipped that chown and left the evidence root-owned and unreadable, i.e. MR-10's defect one level up, in the exact path taken when a phase FAILS and its evidence matters most. It is now `prc=0; runuser … || prc=$?; chown …; exit $prc`.** no product decision, source scope, toolchain, transport topology, or phase predicate changes; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r6
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r5
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R5-MUST-REVISE-MERGED-RECIPE-FRESH-EVIDENCE-20260820-233909.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R5-DURABLE-EVIDENCE-TWO-GATES-STATUS-CAPTURE-20260820-224207.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane revision of T1 authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev5 `s4-matrix-t1-tidy-fix-plan-r5` at commit `fe803f45b1453dacad60c0345b40b12afccfc01c`, SHA-256 `db994777909e98b6011b2074e8c1fcaae90674b43f1d42de54bcc85eec155a19` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev6 — the merged two-phase recipe as four complete inlined artifacts, a per-attempt evidence root, and a finding predicate tightened to (line, check-id) and validated on six arms

## 1. Disposition

```text
MR-11  ACCEPTED  four complete artifacts inlined in §4; no cross-reference to rev4 remains
MR-12  ACCEPTED  per-attempt mktemp -d root, absent-before / non-empty-after / hashed; §4
MR-13  ACCEPTED  and DEMONSTRATED against rev5's own gate; §2
```

## 2. MR-13, demonstrated rather than conceded

I built the two logs you described and ran rev5's predicate on them:

```text
rev5  sorted({line})  on 3 expected findings            -> [136, 138, 220]  PASS   (correct)
rev5  sorted({line})  + a 4th finding on line 136       -> [136, 138, 220]  PASS   <- WRONG
rev5  sorted({line})  + 220's check-id swapped          -> [136, 138, 220]  PASS   <- WRONG
```

Both holes are exactly as you named them: the set discards multiplicity, and the regex never
captured the check-id at all. "Exactly the three known findings and no fourth" was a sentence
in my plan that the code did not implement.

The tightened predicate is a sorted **list of `(line, check-id)` tuples** compared against

```text
(136, cppcoreguidelines-avoid-const-or-ref-data-members)
(138, cppcoreguidelines-avoid-const-or-ref-data-members)
(220, cppcoreguidelines-pro-type-member-init)
```

and I ran it on one must-be-YES and five must-be-NO arms. This also discharges the
unvalidated-predicate disclosure I made in rev5 §6:

```text
MUST-BE-YES  three expected findings          exit 0   "row EXECUTED and FAILED with exactly the three"
MUST-BE-NO   4th finding on line 136          exit 1   findings list differs
MUST-BE-NO   220 check-id swapped             exit 1   findings list differs
MUST-BE-NO   ctest exit 0                     exit 1   RED arm requires nonzero
MUST-BE-NO   row passed (no failure child)    exit 1   RAN but did not FAIL
MUST-BE-NO   row skipped (status notrun)      exit 1   was SKIPPED
```

The S5 GREEN gate is validated the same way: passed-row exit 0; failed-row, skipped-row, and
nonzero-ctest all exit 1.

**The residual caveat, still owed and now narrower:** the arms above use a *synthetic* log in
clang-tidy's documented `path:line:col: warning: message [check-id]` shape. I have still not
run the predicate against a real captured `clang-tidy-22` log. It remains fail-closed, and S3
remains its real must-be-YES case — a mismatch there is a **gate defect to correct and
report**, never a product finding and never a reason to touch `subprocess.cpp`.

## 3. What I validated before filing

```text
t1_tidy_linux_evidence.sh   bash -n   OK
phase.sh                    bash -n   OK
s3_red_gate.py              ast.parse OK  + 6 arms run
s5_green_gate.py            ast.parse OK  + 4 arms run
```

## 4. The merged recipe — four artifacts, complete

**(a) `s3_red_gate.py`**

```python
import re, sys, xml.etree.ElementTree as ET
xml_path, log_path, rc = sys.argv[1], sys.argv[2], int(sys.argv[3])
ROW = "safety-tidy-analyzer"
EXPECTED = [(136, "cppcoreguidelines-avoid-const-or-ref-data-members"),
            (138, "cppcoreguidelines-avoid-const-or-ref-data-members"),
            (220, "cppcoreguidelines-pro-type-member-init")]
def die(m): sys.exit("S3 RED GATE FAILED: " + m)
if rc == 0: die("ctest exit 0; the RED arm requires a NONZERO exit")
cases = [tc for tc in ET.parse(xml_path).getroot().iter("testcase") if tc.get("name") == ROW]
if len(cases) != 1: die(f"expected exactly 1 '{ROW}' record, found {len(cases)}")
tc = cases[0]; kids = {c.tag for c in tc}; status = tc.get("status")
if "skipped" in kids or status == "notrun": die(f"'{ROW}' was SKIPPED (status={status!r})")
if status != "run": die(f"'{ROW}' status={status!r}, expected 'run'")
if not ({"failure", "error"} & kids): die(f"'{ROW}' RAN but did not FAIL; the RED arm requires it")
text = open(log_path, encoding="utf-8", errors="replace").read()
found = sorted(
    (int(n), cid)
    for n, cid in re.findall(
        r"subprocess\.cpp:(\d+):\d+:\s+(?:warning|error):.*?\[([A-Za-z0-9.\-]+)\]", text))
if found != sorted(EXPECTED):
    die(f"analyzer findings {found}, expected exactly {sorted(EXPECTED)}")
print("S3 RED gate OK: row EXECUTED and FAILED with exactly the three known findings")
```

**(b) `s5_green_gate.py`**

```python
import sys, xml.etree.ElementTree as ET
xml_path, rc = sys.argv[1], int(sys.argv[2])
ROW = "safety-tidy-analyzer"
def die(m): sys.exit("S5 GREEN GATE FAILED: " + m)
if rc != 0: die(f"ctest exit {rc}; the GREEN arm requires exit 0")
cases = [tc for tc in ET.parse(xml_path).getroot().iter("testcase") if tc.get("name") == ROW]
if len(cases) != 1: die(f"expected exactly 1 '{ROW}' record, found {len(cases)}")
tc = cases[0]; kids = {c.tag for c in tc}; status = tc.get("status")
if "skipped" in kids or status == "notrun":
    die(f"'{ROW}' was SKIPPED (status={status!r}) - ctest exits 0 on the skip arm; this IS the false green")
if "failure" in kids or "error" in kids: die(f"'{ROW}' RAN and FAILED (status={status!r})")
if status != "run": die(f"'{ROW}' status={status!r}, expected 'run'")
print("S5 GREEN gate OK: row EXECUTED and PASSED")
```

**(c) `phase.sh`** — runs inside the container as `biv`

```bash
#!/bin/bash
set -euo pipefail
ulimit -n "$(ulimit -Hn)"
echo "user=$(id -un) nofile_soft=$(ulimit -Sn) nofile_hard=$(ulimit -Hn)"
SRC=src/core/support/subprocess.cpp
digest_of() { ( set -o pipefail; [ -f "$1" ] || return 1; sha256sum "$1" | cut -d' ' -f1 ); }
TREE_HASH=$(digest_of "/work/$SRC")
[ -n "$TREE_HASH" ] && [ "$TREE_HASH" != "$EMPTY_HASH" ] && [ "$TREE_HASH" = "$EXPECT_HASH" ]
printf '%s\n' "$TREE_HASH" > "/evidence/${PHASE}-source.sha256"
cd /work
python3 -m venv .venv-harness
.venv-harness/bin/python -m pip install -q -r harness/requirements.lock
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
cmake --build --preset ci
: > "/evidence/${PHASE}-status.txt"
if [ "$RUN_SUBPROCESS_ROW" = yes ]; then
  sub_rc=0
  ctest --preset ci -R '^subprocess$' --no-tests=error --output-on-failure \
        --output-junit "/evidence/${PHASE}-subprocess.xml" \
        > "/evidence/${PHASE}-subprocess.log" 2>&1 || sub_rc=$?
  printf 'SUBPROCESS_RC=%s\n' "$sub_rc" >> "/evidence/${PHASE}-status.txt"
  [ "$sub_rc" -eq 0 ]
fi
tidy_rc=0
ctest --preset ci -R '^safety-tidy-analyzer$' --no-tests=error --output-on-failure \
      --output-junit "/evidence/${PHASE}-tidy.xml" \
      > "/evidence/${PHASE}-tidy.log" 2>&1 || tidy_rc=$?
printf 'TIDY_RC=%s\n' "$tidy_rc" >> "/evidence/${PHASE}-status.txt"
if [ "$PHASE" = s3 ]; then
  python3 /work/s3_red_gate.py "/evidence/s3-tidy.xml" "/evidence/s3-tidy.log" "$tidy_rc" \
    > "/evidence/s3-gate.out" 2>&1
else
  python3 /work/s5_green_gate.py "/evidence/s5-tidy.xml" "$tidy_rc" \
    > "/evidence/s5-gate.out" 2>&1
fi
```

**(d) `t1_tidy_linux_evidence.sh`** — the driver. `$1` = the S1 commit (tests only), `$2` = the
S4 commit (the fix). The MANIFEST file is the workflow's eight-line block, unchanged.

```bash
#!/bin/bash
set -euo pipefail
CAND_ROOT=/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
SRC=src/core/support/subprocess.cpp
PRE_EDIT_HASH=9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
EMPTY_HASH=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78'
MIRROR_TAG=toolchain-mirror-clang-tidy-22-immutable-v1
MIRROR_REPO=iwnlcern/bivpak
SDD_PARENT=/Users/jack/Programming/bivpak/.superpowers/sdd
TESTS_HEAD="${1:?arg1: commit after S1 (tests only, production byte-identical)}"
FIXED_HEAD="${2:?arg2: commit after S4 (the tidy fix)}"

digest_of() { ( set -o pipefail; [ -f "$1" ] || return 1; shasum -a 256 "$1" | cut -d' ' -f1 ); }
assert_absent() { [ ! -e "$1" ] || { echo "STALE EVIDENCE: $1 exists before its run"; exit 1; }; }
assert_written() { [ -s "$1" ] || { echo "MISSING/EMPTY EVIDENCE: $1"; exit 1; }; }

mkdir -p "$SDD_PARENT"
EVID_HOST=$(mktemp -d "$SDD_PARENT/t1-tidy-XXXXXXXX")
echo "EVIDENCE_ROOT=$EVID_HOST"
STAGE=$(mktemp -d)
trap 'rm -rf "$STAGE"' EXIT
STAGE_GATE="$STAGE/gate"; STAGE_DEB="$STAGE/deb"
mkdir -p "$STAGE_GATE" "$STAGE_DEB"
cp "$(dirname "$0")/s3_red_gate.py" "$(dirname "$0")/s5_green_gate.py" \
   "$(dirname "$0")/phase.sh" "$STAGE_GATE/"
python3 -c 'import ast,sys
for p in sys.argv[1:]: ast.parse(open(p).read())
print("gates parse OK")' "$STAGE_GATE/s3_red_gate.py" "$STAGE_GATE/s5_green_gate.py"
bash -n "$STAGE_GATE/phase.sh" && echo "phase.sh syntax OK"
cp "$(dirname "$0")/MANIFEST" "$STAGE_DEB/MANIFEST"
while read -r _ package asset; do
  gh release download "$MIRROR_TAG" --repo "$MIRROR_REPO" --pattern "$asset" --dir "$STAGE_DEB"
done < "$STAGE_DEB/MANIFEST"
awk '{ print $1 "  " $3 }' "$STAGE_DEB/MANIFEST" > "$STAGE_DEB/SHA256SUMS"
( cd "$STAGE_DEB" && shasum -a 256 --check --strict SHA256SUMS )
[ "$(find "$STAGE_DEB" -maxdepth 1 -name '*.deb' | wc -l | tr -d ' ')" -eq 8 ]

run_phase() {
  local phase="$1" head="$2" expect_hash="$3" run_sub="$4"
  local srcdir="$STAGE/src-$phase" f rc=0
  local files="tidy.xml tidy.log status.txt gate.out source.sha256"
  [ "$run_sub" = yes ] && files="$files subprocess.xml subprocess.log"
  for f in $files; do assert_absent "$EVID_HOST/$phase-$f"; done
  mkdir -p "$srcdir"
  ( set -o pipefail; git -C "$CAND_ROOT" archive --format=tar "$head" | tar -x -C "$srcdir" )
  local staged; staged=$(digest_of "$srcdir/$SRC")
  [ -n "$staged" ] && [ "$staged" != "$EMPTY_HASH" ] && [ "$staged" = "$expect_hash" ]
  docker run --rm --platform linux/amd64 \
    -v "$srcdir":/mnt-fixed:ro -v "$STAGE_DEB":/mnt-deb:ro -v "$STAGE_GATE":/mnt-gate:ro \
    -v "$EVID_HOST":/evidence:rw \
    -e PHASE="$phase" -e EXPECT_HASH="$expect_hash" -e EMPTY_HASH="$EMPTY_HASH" \
    -e TIDY_VERSION="$TIDY_VERSION" -e RUN_SUBPROCESS_ROW="$run_sub" -e HOST_UID="$(id -u)" \
    ubuntu:24.04 bash -euo pipefail -c '
      export DEBIAN_FRONTEND=noninteractive
      apt-get update -qq
      apt-get install -y --no-install-recommends build-essential cmake git ca-certificates \
        curl zstd libsqlite3-dev python3 python3-venv python3-pip
      apt-get install -y --no-install-recommends /mnt-deb/*.deb
      while read -r _ pkg _; do
        test "$(dpkg-query --show --showformat="\${Version}" "$pkg")" = "$TIDY_VERSION"
      done < /mnt-deb/MANIFEST
      test "$(clang-tidy-22 --version | sed -nE "s/.*LLVM version ([0-9]+).*/\1/p" | head -n1)" = 22
      useradd -m -s /bin/bash biv
      cp -a /mnt-fixed /work
      cp /mnt-gate/s3_red_gate.py /mnt-gate/s5_green_gate.py /mnt-gate/phase.sh /work/
      chown -R biv:biv /work
      prc=0; runuser -u biv -- /bin/bash /work/phase.sh || prc=$?
      chown -R "$HOST_UID" /evidence
      exit $prc
    ' || rc=$?
  for f in $files; do assert_written "$EVID_HOST/$phase-$f"; done
  for f in $files; do
    printf '%s  %s\n' "$(digest_of "$EVID_HOST/$phase-$f")" "$phase-$f" >> "$EVID_HOST/RECEIPTS.sha256"
  done
  [ "$rc" -eq 0 ] || { echo "PHASE $phase FAILED (rc=$rc); evidence retained at $EVID_HOST"; exit 1; }
  echo "PHASE $phase OK; evidence at $EVID_HOST"
}

FIXED_HASH=$(git -C "$CAND_ROOT" show "$FIXED_HEAD:$SRC" | shasum -a 256 | cut -d' ' -f1)
[ "$FIXED_HASH" != "$PRE_EDIT_HASH" ] || { echo "S4 did not change $SRC"; exit 1; }
[ "$FIXED_HASH" != "$EMPTY_HASH" ]
run_phase s3 "$TESTS_HEAD" "$PRE_EDIT_HASH" no
run_phase s5 "$FIXED_HEAD" "$FIXED_HASH"    yes
echo "BOTH PHASES COMPLETE; retained evidence root: $EVID_HOST"
```

Three things worth pointing at explicitly:

- **`chown` now survives a failed phase.** `prc=0; runuser … || prc=$?; chown …; exit $prc`.
  Under plain `set -e` a failing phase would have skipped the `chown` and left `/evidence`
  root-owned — MR-10's defect one level up, on the exact path taken when a phase fails and
  its evidence matters most.
- **S3 stages the S1 commit, not `76638a0`.** Production bytes are identical, so asserting
  `staged == 9af9d55c…` at S3 *also proves S1 was tests-only* — one assertion, two jobs.
- **Phase success is the gate's verdict, not ctest's exit.** S3 expects a nonzero `ctest`
  and still exits 0 when the RED is exactly right, so `rc -eq 0` is the correct assertion
  for both phases.

## 5. MR-11.5 — the macOS rows, with the capture shape applied not merely stated

```sh
cd /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
cmake --build --preset ci-macos --target biv_subprocess_tests
mac_sub_rc=0
ctest --preset ci-macos -R '^subprocess$' --no-tests=error --output-on-failure \
  > "$EVID_HOST/macos-subprocess.log" 2>&1 || mac_sub_rc=$?
printf 'MACOS_SUBPROCESS_RC=%s\n' "$mac_sub_rc" >> "$EVID_HOST/macos-status.txt"
[ "$mac_sub_rc" -eq 0 ]

cmake --build --preset ci-macos
mac_named_rc=0
ctest --preset ci-macos \
  -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$' \
  --no-tests=error --output-on-failure \
  > "$EVID_HOST/macos-named.log" 2>&1 || mac_named_rc=$?
printf 'MACOS_NAMED_RC=%s\n' "$mac_named_rc" >> "$EVID_HOST/macos-status.txt"
[ "$mac_named_rc" -eq 0 ]
```

The S2 characterization run uses the first block at the S1 commit, before any production
edit; the same block re-runs at S5 after the post-edit build. The cache-root binding from
rev3 §5 runs before each, unchanged.

## 6. Unchanged — carried in full

Production shape and both framing corrections; S1–S5 ordering; the three frozen vectors with
the both-ample negative discriminator; the macOS cache-root binding with its digest honestly
labelled a receipt; the pre-edit anchor; host-side toolchain staging with the workflow's
manifest, per-package version and LLVM-major assertions; `libsqlite3-dev` and
`ca-certificates` for `find_package(SQLite3 REQUIRED)` and the configure-time `FetchContent`
downloads; non-root `biv` with the descriptor lift; `harness-selftest` reported separately
under `201613` with the full Linux suite never labelled GREEN; disposable containers, host
worktree preserved, no unrelated Docker resource pruned or removed; and the charter-difference
report from rev4 §8.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 7. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Verification wrote
four scratchpad files and ran ten gate arms plus three syntax checks; no container was started
for this revision, no Docker resource created or removed, no image built, and no evidence root
was created under `.superpowers/sdd/`. Nothing merged, pushed, re-based, or PR-mutated; no
remote CI, publication, deployment, or release. T2/T3/T4 and the `compare.py` composition stay
held; the count-gate shape stays routed; Linux `nonzero_exit` stays owed; the Arm-1 schema act
stays F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: wrote four scratchpad artifacts (`t1_tidy_linux_evidence.sh`, `phase.sh`, `s3_red_gate.py`, `s5_green_gate.py`) plus synthetic JUnit/log fixtures under the session scratchpad; ran `bash -n` on both shell artifacts, `ast.parse` on both gates, six S3-gate arms and four S5-gate arms, and re-ran rev5's superseded set-based predicate on two must-be-NO logs to demonstrate MR-13. NO container started, NO ref created or moved, NO source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R6-MERGED-RECIPE-VALIDATED-GATES-20260821-022928.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev5 at SHA-256 `db994777909e98b6011b2074e8c1fcaae90674b43f1d42de54bcc85eec155a19`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-13 DEMONSTRATED against my own rev5 gate, not merely conceded: a 4th finding on line 136 → rev5 predicate returns `[136, 138, 220]` → PASS; `220`'s check-id swapped → `[136, 138, 220]` → PASS. The set discarded multiplicity and the regex never captured the check-id, so "exactly three and no fourth" was a sentence the code did not implement. Tightened to a sorted `(line, check-id)` list and RUN on 1 must-be-YES + 5 must-be-NO arms; S5 gate validated on 1 + 3
- MR-11 ACCEPTED, THIRD OCCURRENCE: rev3 one placeholder, rev4 two, rev5 a labelled cross-reference sitting inside a `bash -c` program — which is still a string the shell executes. Labelling an elision does not make it run. Four complete artifacts now inlined: driver, `phase.sh`, and both gates; `$STAGE_GATE` created and populated, both gates invoked with exact arguments, host artifact checks present
- MR-12 ACCEPTED, my own favourite defect aimed at me: `mkdir -p` on a FIXED root plus a post-run `[ -s ]` is ABSENCE-BLIND — a retry's stale non-empty `s3-tidy.xml` satisfies it even if this run wrote nothing. Now a checked `mktemp -d` per attempt, every expected file asserted ABSENT before and non-empty after, each hashed into `RECEIPTS.sha256`, root echoed for the SITREP
- FIXED IN MY OWN OUTER LAYER: the payload's closing `chown -R /evidence` would have been SKIPPED by `set -e` when a phase failed, leaving evidence root-owned and unreadable on exactly the path where it matters most — now `prc=0; runuser … || prc=$?; chown …; exit $prc`
- S3 stages the S1 tests-only commit rather than `76638a0`, so asserting `staged == 9af9d55c…` ALSO proves S1 touched no production byte; and phase success is the GATE's verdict not ctest's exit, so `rc -eq 0` is correct for both phases even though S3 expects a nonzero ctest
- VALIDATED BEFORE FILING: `bash -n` on both shell artifacts, `ast.parse` on both gates, ten gate arms run
- RESIDUAL, narrowed and still owed: the gate arms use a SYNTHETIC log in clang-tidy's documented `path:line:col: warning: msg [check-id]` shape; the predicate has still not met a real captured `clang-tidy-22` log. Fail-closed, and S3 is its real must-be-YES case — a mismatch there is a GATE defect to correct and report, never a product finding
- No product decision, source scope, toolchain, transport topology, or phase predicate changed; T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; release hold ABSOLUTE
