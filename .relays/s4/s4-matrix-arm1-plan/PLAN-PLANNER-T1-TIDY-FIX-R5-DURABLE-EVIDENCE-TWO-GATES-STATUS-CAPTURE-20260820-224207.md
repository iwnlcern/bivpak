## PLAN rev5 (T1 tidy repair — MR-8, MR-9, MR-10 all accepted; and MR-10 is not a style note, it is fatal, which I confirmed at the shell) — **MR-10 MEASURED: `bash -c 'set -euo pipefail; false; RC=$?; echo REACHED'` prints NOTHING and the shell exits 1. Under `set -e` the assignment is never reached. So rev4's recipe would have DIED at the S3 analyzer row — the one step whose entire purpose is to observe a nonzero exit — and the `trap` would then have deleted the stage on the way out. My recipe was structurally incapable of producing the S3 evidence it demanded. The workflow's own shape `rc=0; cmd || rc=$?` records `rc=1` and continues (measured), and file redirection captures the log with no pipe (measured). Every status capture in rev5 uses that shape.** **MR-9 IS THE SHARPEST FINDING IN THIS WHOLE REVIEW CHAIN AND IT IS AGAINST MY OWN "UPGRADE": in rev4 I replaced my prose observation with the workflow's JUnit gate and said to run it verbatim for BOTH phases. But that gate FAILS when the testcase has a `failure` or `error` child — it is a GREEN-only gate. Used verbatim at S3 it would refuse the very RED the plan requires, so the phase that proves the defect exists could never pass its own gate. I adopted a canonical instrument without checking that its predicate matched the phase I pointed it at — the exact error of using a real instrument on the wrong question. Rev5 freezes TWO gates: a RED-aware S3 predicate and the canonical GREEN predicate for S5.** **MR-8 ACCEPTED: `/work` is container-private, `docker run --rm` destroys it, and my §6 told the reader to run a gate "verbatim against `/work/tidy.xml`" AFTER the container had exited. The gate was never invoked anywhere inside the command. Rev5 mounts a read-write evidence directory, embeds both gates as staged script files invoked INSIDE the container before exit, verifies the artifacts exist and are non-empty on the host after each run, and retains them OUTSIDE the trap-removed stage.** **ONE GAP I FOUND WHILE FIXING YOURS: rev4 only ever described staging the POST-edit tree, but S3 must run the analyzer against PRE-EDIT bytes. There are TWO Linux containers, on two different heads, with two different gates and two different evidence prefixes. Rev4 never said so and a reader following it literally would have had no S3 tree at all.** **AND ONE DISCLOSURE I OWE, because I keep insisting on it from others: the S3 finding-membership regex is the ONE predicate in this plan I could NOT validate on a must-be-YES case at my seat — I have the three line numbers from your `180321`, not a captured clang-tidy log. It is fail-closed (zero matches fails the gate), which is the safe direction, but S3 IS its must-be-YES case: if it dies reporting `found []` while the row genuinely failed with the three findings, that is a GATE defect to correct and report, NOT a product finding, and the retained raw log is what makes that triage possible.** no product decision, source scope, toolchain, or transport topology changes; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r5
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r4
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R4-MUST-REVISE-PERSIST-AND-GRADE-JUNIT-20260820-222214.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R4-SELF-CONTAINED-CONTAINER-RECIPE-20260820-214100.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane revision of T1 authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev4 `s4-matrix-t1-tidy-fix-plan-r4` at commit `a1b93ba6230ae9f27b693d3301dc47daaa5e761e`, SHA-256 `610fec5b41a47c07dd04fa5a59502cca660c41c54d7b1ba20ecd9d1d01824755` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev5 — durable S3/S5 evidence graded inside the container, two phase-correct gates, and status capture that survives set -e; plus the missing pre-edit Linux stage

## 1. Disposition, and the measurement behind MR-10

```text
MR-8   ACCEPTED   evidence lifecycle, §4
MR-9   ACCEPTED   two phase-correct gates, §5 - and this one was against my own rev4 "upgrade"
MR-10  ACCEPTED   and MEASURED fatal, below; §3
```

```text
bash -c 'set -euo pipefail; false; RC=$?; echo "REACHED, RC=$RC"'    -> NO OUTPUT, exit 1
bash -c 'set -euo pipefail; rc=0; false || rc=$?; echo "rc=$rc"'      -> "rc=1",  exit 0
bash -c 'set -euo pipefail; rc=0; ls /nope > /tmp/o.txt 2>&1 || rc=$?; echo "rc=$rc"'  -> rc=1, 37-byte log, exit 0
```

The first arm is rev4's shape. It does not merely fail to record the status — it kills the
payload, at S3, immediately before the evidence step, with a `trap` waiting to remove the
stage. Every status capture below uses the second shape, and every log is captured by file
redirection rather than a pipe.

## 2. Two Linux runs, not one — the gap rev4 left

S3 grades the analyzer at **pre-edit** bytes; S5 grades it at **fixed** bytes. Rev4 only
described staging the post-edit tree. Both stages use the identical mechanics from rev4 §4-§5
(host-side `gh release download` of the 8 pinned debs, read-only mounts, root provisions then
`runuser` drop, `ulimit -n` raised inside the drop, `mktemp` checked, `git archive | tar`
under `pipefail`, trap removing only this recipe's stage), parameterised by three values:

```text
run  HEAD                                        gate                evidence prefix
S3   76638a00332fc9dd674f0cf952e28be4fa0507e8    s3_red_gate.py      s3-
S5   the S4 fix commit on s4-matrix/arm1-t1      s5_green_gate.py    s5-
```

At S3 the pre-edit anchor assertion **inverts**: the staged digest must EQUAL
`9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b`. At S5 it must DIFFER
from it, as rev3 established. Same gate function, opposite arm, and stating both is what
stops S3 from being run against fixed bytes by accident.

## 3. MR-10 — status capture, everywhere

```sh
rc=0; ctest --preset ci -R '^safety-tidy-analyzer$' --no-tests=error --output-on-failure \
        --output-junit "$EVID/s3-tidy.xml" > "$EVID/s3-tidy.log" 2>&1 || rc=$?
```

Applied identically to the macOS focused row, the macOS named selection, the Linux
`subprocess` row, and both analyzer runs. No pipes anywhere in a status-bearing command.

## 4. MR-8 — durable evidence, graded before the container dies

```sh
# RETAINED root, deliberately OUTSIDE $STAGE so the trap cannot remove it.
# .superpowers/ is excluded via .git/info/exclude, so this pollutes no lane and
# dirties no `git status --porcelain` (which the archive step asserts is empty).
EVID_HOST=/Users/jack/Programming/bivpak/.superpowers/sdd/s4-matrix-t1-tidy-fix-impl
mkdir -p "$EVID_HOST"

docker run --rm --platform linux/amd64 \
  -v "$STAGE_SRC":/mnt-fixed:ro -v "$STAGE_DEB":/mnt-deb:ro \
  -v "$STAGE_GATE":/mnt-gate:ro -v "$EVID_HOST":/evidence:rw \
  -e HOST_HASH="$HOST_HASH" -e PRE_EDIT_HASH="$PRE_EDIT_HASH" -e EMPTY_HASH="$EMPTY_HASH" \
  -e TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78' \
  -e EVID=/evidence \
  ubuntu:24.04 bash -euo pipefail -c '<the rev4 §5 payload, unchanged except that the
     gate scripts come from /mnt-gate and every status capture uses rc=0; cmd || rc=$?>'
```

The two added mounts and `-e EVID` are the ONLY changes to the rev4 §5 `docker run`
invocation; its image, payload structure, provisioning, `useradd`/`chown`, and `runuser`
drop are unchanged. I am flagging that this last line is a deliberate cross-reference to
rev4 §5 rather than an elision of unspecified content — the payload is fully written there
and is not being left to the reader to invent.

Inside the container, `EVID=/evidence`, so the XML and log are written **straight onto the
host mount** and never live only in `/work`. Both gates are staged as real files in
`$STAGE_GATE`, mounted at `/mnt-gate`, and invoked **inside** the container immediately
after their row, before exit. The analyzer CTest run and the gate both execute under `biv`
with the descriptor lift; root may `chown` the evidence afterwards.

After each container exits, on the host:

```sh
for f in "$EVID_HOST/s3-tidy.xml" "$EVID_HOST/s3-tidy.log"; do
  [ -s "$f" ] || exit 1                      # exists AND non-empty
done
```

The SITREP records, for each phase: the file paths, their SHA-256, the `ctest` rc, the gate's
stdout line, and the `subprocess.cpp` source hash for that phase (`9af9d55c…` at S3, the
fixed digest at S5). Those hashes are what make the retained files bindable later.

## 5. MR-9 — two gates, both exact, both staged as files

**`s3_red_gate.py`** — the RED arm. Takes the XML, the log, and the ctest rc:

```python
import re, sys, xml.etree.ElementTree as ET
xml_path, log_path, rc = sys.argv[1], sys.argv[2], int(sys.argv[3])
ROW = "safety-tidy-analyzer"
def die(m): sys.exit("S3 RED GATE FAILED: " + m)
if rc == 0: die("ctest exit 0; the RED arm requires a NONZERO exit")
cases = [tc for tc in ET.parse(xml_path).getroot().iter("testcase") if tc.get("name") == ROW]
if len(cases) != 1: die(f"expected exactly 1 '{ROW}' record, found {len(cases)}")
tc = cases[0]; kids = {c.tag for c in tc}; status = tc.get("status")
if "skipped" in kids or status == "notrun": die(f"'{ROW}' was SKIPPED (status={status!r})")
if status != "run": die(f"'{ROW}' status={status!r}, expected 'run'")
if not ({"failure", "error"} & kids): die(f"'{ROW}' RAN but did not FAIL; the RED arm requires it")
text = open(log_path, encoding="utf-8", errors="replace").read()
found = sorted({int(n) for n in re.findall(r"subprocess\.cpp:(\d+):\d+:\s+(?:warning|error):", text)})
if found != [136, 138, 220]: die(f"subprocess.cpp findings {found}, expected exactly [136, 138, 220]")
print("S3 RED gate OK: row EXECUTED and FAILED with exactly the three known findings")
```

**`s5_green_gate.py`** — the canonical workflow predicate, plus the exit assertion:

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

The exact-list comparison `found != [136, 138, 220]` is what refuses a fourth or moved
finding, satisfying "no new analyzer finding is accepted as a waived delta".

## 6. The one unvalidated predicate in this plan — disclosed, not buried

The S3 regex `subprocess\.cpp:(\d+):\d+:\s+(?:warning|error):` is derived from the line
numbers in your `180321`, **not** from a clang-tidy log I have captured. I have not run it
on a must-be-YES case, and by my own standard elsewhere in this chain that makes it a claim
rather than a validated discriminator. Two consequences, both required:

- It is **fail-closed**: zero matches yields `found == []`, which fails the gate. That is
  the safe direction, so an unvalidated predicate cannot manufacture a false GREEN.
- **S3 is its must-be-YES case.** If the gate dies reporting `found []` (or a different
  set) while the row genuinely failed with the three findings, that is a **GATE defect to
  correct and report** — not a product finding, and not a reason to touch `subprocess.cpp`.
  The retained `s3-tidy.log` is what makes that triage possible, which is a second reason
  §4 keeps the raw log and not only the XML.

## 7. Unchanged — carried from rev4 in full

Production shape and both framing corrections; S1–S5 ordering; the three frozen vectors with
the both-ample negative discriminator; post-edit builds on both hosts; the macOS cache-root
binding with its digest honestly labelled a receipt; the fresh fixed-byte Linux tree distinct
from the RED tree; `--no-tests=error --output-on-failure` on every row; host-side toolchain
staging with the workflow's manifest, per-package version and LLVM-major assertions re-run
in-container; `libsqlite3-dev` and `ca-certificates` for `find_package(SQLite3 REQUIRED)` and
the configure-time `FetchContent` downloads; non-root `biv` with `ulimit -n` raised inside
the drop; `harness-selftest` reported separately under `201613` with the full Linux suite
never labelled GREEN; disposable containers, host worktree preserved, no unrelated Docker
resource pruned or removed; and the §8 charter-difference report.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 8. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Verification was
three `bash -c` shell-semantics probes and a read of `.git/info/exclude`; no container was
started for this revision, no Docker resource created or removed, no image built. Nothing
merged, pushed, re-based, or PR-mutated; no remote CI, publication, deployment, or release.
T2/T3/T4 and the `compare.py` composition stay held; the count-gate shape stays routed;
Linux `nonzero_exit` stays owed; the Arm-1 schema act stays F+G-fenced. Merge != push !=
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: three read-only `bash -c` probes of `set -e` status-capture semantics (rev4's `cmd; rc=$?` shape, the workflow's `rc=0; cmd || rc=$?` shape, and file-redirect capture), plus `git check-ignore` of `.superpowers`. NO container started, NO ref created or moved, NO source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R5-DURABLE-EVIDENCE-TWO-GATES-STATUS-CAPTURE-20260820-224207.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev4 at SHA-256 `610fec5b41a47c07dd04fa5a59502cca660c41c54d7b1ba20ecd9d1d01824755`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-10 ACCEPTED and MEASURED FATAL: `set -euo pipefail; false; RC=$?; echo` prints NOTHING and exits 1 — rev4's shape would have KILLED the payload at the S3 analyzer row, the one step whose purpose is to observe a nonzero exit, with the stage-removing trap waiting on the way out. The workflow shape `rc=0; cmd || rc=$?` records rc=1 and continues (measured); file redirection captures the log with no pipe (measured). Applied to every status-bearing command
- MR-9 ACCEPTED, and it is against my own rev4 "upgrade": the workflow JUnit gate FAILS on a `failure`/`error` child, so it is GREEN-ONLY and cannot grade S3 — the phase that proves the defect exists could never pass its own gate. I adopted a canonical instrument without checking its predicate matched the phase I aimed it at. TWO gates now frozen: RED-aware `s3_red_gate.py` (nonzero exit, row present once, status run, HAS failure/error, findings exactly `[136, 138, 220]`) and the canonical `s5_green_gate.py` (exit 0, row present once, status run, NO failure/error)
- MR-8 ACCEPTED: `/work` is container-private and `--rm` destroys it, while my §6 told the reader to run a gate "verbatim" against it AFTER the container exited, and the gate was never invoked inside the command. Rev5 mounts `/evidence` read-write onto a RETAINED host root under `.superpowers/sdd/` (excluded via `.git/info/exclude`, so it dirties no lane and keeps `git status --porcelain` empty for the archive step), stages both gates as real files mounted at `/mnt-gate`, invokes them INSIDE the container before exit, and verifies `[ -s ]` on the host after each run
- GAP I FOUND FIXING YOURS: rev4 only described staging the POST-edit tree, but S3 must analyze PRE-EDIT bytes. TWO Linux runs on two heads, two gates, two evidence prefixes — and the anchor assertion INVERTS (S3 must EQUAL `9af9d55c…`, S5 must DIFFER), which is what stops S3 being run against fixed bytes by accident
- DISCLOSED, NOT BURIED: the S3 finding-membership regex is the ONE predicate here I could not validate on a must-be-YES case — it comes from your `180321` line numbers, not a captured log. It is FAIL-CLOSED so it cannot manufacture a false GREEN, and S3 IS its must-be-YES case: a `found []` while the row genuinely failed is a GATE defect to correct and report, NOT a product finding and NOT a reason to touch `subprocess.cpp`. The retained raw log is what makes that triage possible
- Everything else carries from rev4 unchanged; no product decision, source scope, toolchain, or transport topology changed; T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; release hold ABSOLUTE
