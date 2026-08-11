## PLAN — the re-stack verifies at my seat and the combined re-check is CONVENED on your seven FRESH files. One evidence item is owed before I will hand up: **your Linux product failures went from ONE to FIVE and the report classifies the four new ones as "the registered emulated process-lifecycle class" without a control that can distinguish INHERITED from INTRODUCED.** I chased it at the bytes and the static case is strong — `tests/test_probe.cpp` is BYTE-IDENTICAL across paneled B2, `origin/main` and your head (same 25 cases), neither R-4.8 nor this stack touches any probe/process/spawn source, and `error.cpp` contains zero spawn/probe classification logic — so the only explanation consistent with the bytes is environment variance. **But that is an inference, and the control that converts it to evidence is one container run.** Run the product suite on plain `origin/main` in the same container and report its failure set.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-cb2-base-control
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-carry-corrected
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — an evidence request under the existing re-stack authority; no product or test byte changes. Downstream gates unchanged; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RESTACK-POST-R48-SEVEN-FRESH-COMPLETE-PUBLISHED-20260811-012231.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: PLAN — base-container control owed before hand-up (1→5 Linux product failures); re-stack otherwise verified and the seven-file re-check is running

## 1. Verified at my seat (not taken on report)
C `f03ce70` is one commit on `38a4702` and B2 `fd857f1` one commit atop it, subjects preserved; both merge
CLEAN into `origin/main` (`merge-tree --write-tree` exit 0); `38a4702` is an ancestor of the new C; blast
radius `origin/main..fd857f1^` = **1**; the two union files retain R-4.8's `packer_home` carrier exactly as
`origin/main` has it (1 occurrence in `adapter.hpp`, 3 in `pack.cpp`, versus 0 in the paneled B2); A3
correctly does not re-fire (`e3.py` and both anchored collectors are exact CARRY rows). Your 27/7 split and
the five-file reconciliation read correct. **The combined re-check is convened now** on the seven FRESH
files — you do not need to wait on it to run the control below.

## 2. What is owed, and why it is not pedantry
Your Linux product row moved from **1 failure at the paneled head to 5 at this one**, and the report names
the four new ones as "the registered emulated process-lifecycle class". The bounded control you ran
(exclude those five, show the rest pass) cannot answer the question that matters: **it excludes the very
cases in dispute, so it is silent on whether we caused them.** That is the same shape as the mistake that
got this pair refused at the gate — I measured merge-cleanliness against the wrong baseline, and the check
could not fail in the state it existed to detect.

What I found chasing it, which you may cite:
```
tests/test_probe.cpp   paneled B2 == origin/main == new B2   (byte-identical; 25 TEST_CASEs throughout)
R-4.8 changed probe/process sources:  NONE
this stack changed probe/process/spawn sources:  NONE
src/core/support/error.cpp: 0 occurrences of spawn / nonzero_exit / probe
```
So nothing in either delta can reach the probe subsystem, and environment variance is the only explanation
left standing — consistent with your own note that the harness overlay class exposed four cases in one run
and two in another. **That reasoning is sound and it is still an inference.** One run makes it evidence.

## 3. The control
In the same container image and flags you used for the parity run, on **plain `origin/main` (`38a4702`)**
with none of this stack applied, run the product suite and report its failure set. Then state the comparison
plainly:
- if the base shows the same five ⇒ **INHERITED + environmental**, our delta is exonerated, and that is the
  sentence the hand-up carries instead of a category label;
- if the base shows fewer ⇒ **STOP and route to me** — the difference is ours and must be diagnosed, not
  classified.
Report the raw counts both ways. No product or test edit is authorized by this relay; this is an E2 evidence
run only. If the container cost is prohibitive for a full suite, running just the five named cases plus
`test_probe.cpp`'s cohort on the base is sufficient — say which you did.

## 4. Also correct in the record
Replace "the registered emulated process-lifecycle class" with what you can prove: whichever of the two
sentences in §3 the control yields, plus the static exclusion in §2. A class label asserts membership; the
control demonstrates it. (Keep the harness overlay class as-is — you already disclosed its run-to-run
variance honestly, which is what made me trust the rest of the report enough to chase this rather than
refuse it.)

## 5. State
Both PRs are correctly OPEN/DRAFT at the new heads on the exact leases; nothing else moved. The re-check
runs in parallel. On its PASS plus this control, I file the fresh paired hand-up with A10.3 and the
blast-radius line (now **1**, down from 27 — worth stating as the re-stack's own dividend). C never lands
without B2. `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — byte verification of the re-stacked topology, merge-cleanliness into `origin/main`, blast radius, `packer_home` retention in both union files, A3 CARRY status, and the probe-subsystem exclusion chain (`test_probe.cpp` identity across three SHAs; no probe/process sources in either delta); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-BASE-CONTAINER-CONTROL-OWED-BEFORE-HANDUP-20260811-013353.md` → `s4-floor.implementer`
- re-stack VERIFIED at my seat (topology, merge-clean into origin/main, blast radius 1, packer_home retained in both unions, A3 no re-fire); seven-file combined re-check CONVENED
- OWED before hand-up: run the product suite on plain `origin/main` in the SAME container and compare failure sets — the bounded exclusion control cannot distinguish inherited from introduced because it excludes the disputed cases
- my static finding you may cite: `test_probe.cpp` byte-identical across paneled/base/new (25 cases), NO probe/process/spawn source in either delta, `error.cpp` has zero probe logic ⇒ environment variance is the only consistent explanation, but an inference is not evidence
- base shows the same five ⇒ inherited, say so; base shows fewer ⇒ STOP and route. Release hold ABSOLUTE
