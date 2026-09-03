## SITREP — isolation plan REVISION 6 @ 9eb01448 FILED as `intg-isolation/PLAN-pair-planner-20260902-194515.md` under the fresh handoff id `intg-isolation-plan-7`, folding the implementer's `193327` MUST-REVISE of rev5 (two Criticals, each CONFIRMED against the document: F1 Task 3 had no executable order — a guard claiming "immediately before the commit" with four evidence steps between it and the commit, and a Linux leg requiring a landed sha the commit had not yet created → Task 3 is now ONE literal order: pre-commit fence in working-tree forms → macOS pre-commit → the four demonstrations → THE GUARD adjacent to the commit → THE ONE COMMIT recording `$LANDED` → the landed-sha fence (proofs of record) → Linux at `$LANDED`, the sole consumer of that sha, with an explicit red rule (a red un-lands nothing, authorizes no second commit, goes UP with the sha) → the IMPL report; F2 my status-delta pipeline projected added rows only, so a vanished inherited entry was invisible → the guard is TWO-SIDED (zero removed rows; the added rows == exactly the four porcelain rows WITH status codes) and the post-commit proof is byte-equality of the full sorted status with the pre-write snapshot); the recorded self-check predicate gains the rev5 dead forms and re-runs at rc=1 (zero matches); Task 0, the paired warning-object witness, the two-pin rule, the four-path fence, the rev5 commit text, the design pin `637ef197`, the edge `1738583e`, both grains and `_rp_positive` UNCHANGED (upheld by `193327`); root-mode re-measurement: the rev6 carrier fires NOTHING, design-edge class 0 (archive `results/lint-root-sweep-isolation-plan-rev6-20260902.txt` @ d803d0bf; the root-wide delta = four standing not-consumed entries, enumerated); the token waits ONLY on the implementer's exact-hash approve at 9eb01448 parented to `intg-isolation-plan-7`; no harness byte, no product byte, no token yet, no push

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-193327.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-194515.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev6-20260902.txt; intg-isolation/SITREP-pair-planner-20260902-190629.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
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
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — isolation plan rev6 @ 9eb01448 filed as intg-isolation-plan-7 (194515): the 193327 folds (Task 3 in one literal order with the guard adjacent to the commit and Linux at the landed sha; two-sided status proof); predicate re-run rc=1; pin/edge/grains/oracle/Task 0 unchanged; rev6 carrier silent in root mode (archive d803d0bf), design-edge class 0; token waits only on the implementer's exact-hash approve

## The re-measurement

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (493 s wall)
archive   results/lint-root-sweep-isolation-plan-rev6-20260902.txt  sha256 d803d0bf9c50b3ea680541edd9279d7d5ffb78b93a9792d855e6e204b08fa7b0
          348 lines; rc 1; 316 ERROR / 26 WARN root-wide
carrier   intg-isolation/PLAN-pair-planner-20260902-194515.md — NO fired entry (per-file OK); design-edge class 0; commission surface
          byte-equal to the grant (rule 3d silent on this carrier)
delta     vs the rev5 sweep (312/26/195): design-lineage 54 → 54; rule-3d 3 → 3 (unchanged); not-consumed 195 → 199 = 193327, 190629
          (relays) + the implementer's rev5-review draft + my 190629 draft. Nothing else moved.
```

## Standing state

- Isolation: rev6 awaits the implementer's exact-hash review at `9eb01448…` (parented to `intg-isolation-plan-7`, their next unique review id); then the in-lane token with the FOUR-path SCOPE_DIFF; Task 0; the ONE commit on `$IMPL_BASE`; Linux at `$LANDED`; sha UP; m-3's byte review. Countgate observations after.
- 2a: rev12 approved (`070841`); the header re-issue ask `141420` still outstanding; the frozen six-file patch unstaged at `9e6ebe8`.
- No merge, no push, no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact, the filed 194515, the archived measurement, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION6-PLAN-7.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-REV6-FILED.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-194515.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev6-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
