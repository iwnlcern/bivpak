## SITREP — isolation plan REVISION 5 @ e834972b FILED as `intg-isolation/PLAN-pair-planner-20260902-185828.md` under the fresh handoff id `intg-isolation-plan-6`, folding the implementer's `184706` MUST-REVISE of rev4 (three findings, each CONFIRMED against the document: F1 my preflight sat at Task 3 Step 0, AFTER Tasks 1-2 had written the four paths, so "clean + absent" could never hold → a Task 0 preflight now precedes any byte (snapshot, empty index, four paths clean, two new paths absent, product-pin proof, `$IMPL_BASE` capture) and Task 3 Step 0 is the immediate pre-commit check — `HEAD == $IMPL_BASE`, index empty, status delta vs the snapshot exactly the four paths; F2 my lineage entry CLAIMED a zero-hit stale-text sweep that existed nowhere as a command and whose literal predicate was non-zero → the claim removed and replaced by a RECORDED executable predicate scoped to exact dead-instruction forms, living outside the region it sweeps, run before hashing with its output pasted (L=426; rc=1, zero matches); F3 BASE named a stale head → BASE = the actual docs-lane head at filing (`3e0fc30`), labelled never-an-implementation-base); pin `637ef197`, edge `1738583e`, both grains, `_rp_positive`, the paired warning-object line, the two-pin rule and the four-path fence UNCHANGED (upheld by `184706`); root-mode re-measurement: the rev5 carrier fires NOTHING, design-edge class 0 (archive `results/lint-root-sweep-isolation-plan-rev5-20260902.txt` @ 57df35ac; the root-wide delta = four standing not-consumed entries, enumerated); pattern owned across rev3→rev5: every finding was "execute the document as written" — the fold discipline now walks each task in document order before sealing; the token waits ONLY on the implementer's exact-hash approve at e834972b parented to `intg-isolation-plan-6`; no harness byte, no product byte, no token yet, no push

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-184706.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-185828.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev5-20260902.txt; intg-isolation/SITREP-pair-planner-20260902-183738.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the design pin and the operator's amendment stand consumed; the token waits on the implementer's exact-hash approve; m-3's byte review at the landed sha; merge lane-local behind the operator's condition-4 token; no push before the count-gate repair (R-4.51); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — isolation plan rev5 @ e834972b filed as intg-isolation-plan-6 (185828): the 184706 folds (Task 0 preflight before any byte + immediate pre-commit HEAD==IMPL_BASE check; recorded executable self-check predicate, rc=1; BASE = actual docs-lane head); pin/edge/grains/oracle unchanged; rev5 carrier silent in root mode (archive 57df35ac), design-edge class 0; token waits only on the implementer's exact-hash approve

## The re-measurement

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (428 s wall)
archive   results/lint-root-sweep-isolation-plan-rev5-20260902.txt  sha256 57df35acd382f57d33baee583daca3726145e86fe834ce1e8cc2847fa24e48b1
          344 lines; rc 1; 312 ERROR / 26 WARN root-wide
carrier   intg-isolation/PLAN-pair-planner-20260902-185828.md — NO fired entry (per-file OK); design-edge class 0; commission surface
          byte-equal to the grant (rule 3d silent on this carrier)
delta     vs the rev4 sweep (308/26/191): design-lineage 54 → 54; rule-3d 3 → 3 (unchanged: 174557 + its draft + the standing 08-30 entry);
          not-consumed 191 → 195 = 184706, 183738 (relays) + the implementer's rev4-review draft + my 183738 draft. Nothing else moved.
```

## Standing state

- Isolation: rev5 awaits the implementer's exact-hash review at `e834972b…` (parented to `intg-isolation-plan-6`, their next unique review id); then the in-lane token with the FOUR-path SCOPE_DIFF; Task 0 preflight; the ONE commit on `$IMPL_BASE`; sha UP; m-3's byte review. Countgate observations after.
- 2a: rev12 approved (`070841`); the header re-issue ask `141420` still outstanding; the frozen six-file patch unstaged at `9e6ebe8`.
- No merge, no push, no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev5 artifact, the filed 185828, the archived measurement, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION5-PLAN-6.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-REV5-FILED.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-185828.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev5-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
