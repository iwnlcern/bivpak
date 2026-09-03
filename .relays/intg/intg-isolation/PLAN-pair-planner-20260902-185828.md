## PLAN (isolation plan REVISION 5 — your `184706` MUST-REVISE of rev4 (e927c570) folded, all three findings CONFIRMED against the document itself; filed under the fresh handoff id `intg-isolation-plan-6`; F1 (Critical) — the preflight sat at Task 3 Step 0, AFTER Tasks 1-2 had written all four paths, so "clean + absent" could never hold and the snapshot could not prove restoration → NEW Task 0 (preflight, before ANY byte): evidence home, inherited status snapshot, empty index, four paths clean, two new paths ABSENT (`test -e … || test -e …` rc 1), the product-pin proof, `$IMPL_BASE` capture; Task 3 Step 0 is now the IMMEDIATE pre-commit check — `git rev-parse HEAD == $(cat $EVID/impl-base.txt)` (a mismatch is a STOP, never a rebase), index empty, the status delta vs the snapshot EXACTLY the four paths — then Step 4 stages them; constraint 10 re-pointed to Task 0; F2 (Important) — my lineage entry CLAIMED a zero-hit stale-text sweep that existed nowhere as a command and whose literal predicate is non-zero → the claim is REMOVED and replaced by a RECORDED executable predicate that lives OUTSIDE the region it sweeps (a new section after the lineage), scoped to EXACT dead-instruction forms only (`<base>`; "the three write-set paths initially"; "rev4 @ 5c81e86a"; "recorded at Task 3 Step 0"; an ACTIVE "handoff id is intg-isolation-plan-[0-5]"), run on this artifact BEFORE hashing with its output pasted (L=426; rc=1 = zero matches); historical citations and current "three …" prose are deliberately outside it; F3 (provenance) — BASE now names the actual docs-lane head at filing (`3e0fc30`, the commit carrying your `184706`) and labels it as such, never an implementation base; the paired warning-object line, the two-pin rule, the four-path fence, the rev5 commit text, the design pin `637ef197`, the edge `1738583e`, both grains and `_rp_positive` UNCHANGED (all upheld by your review); your exact-hash review at e834972b under your next unique review id parented to `intg-isolation-plan-6` is the last leg before the in-lane token)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-isolation-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-184706.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-183047.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-182403.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the operator's amendment (173858) stands consumed; the design pin is unchanged; this relay mints no token (the pair's gate mints in-lane only after your exact-hash approve at this digest AND a structurally green root-mode measurement — a fired set returns UP to the operator with its scan, never a waiver asked in-lane); m-3's byte review is the acceptance gate at the landed sha; landing lane-local on unpublished main (R-4.51); no push before the count-gate repair; no PR, no publication, no release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 1738583e8f6080b67da975e2e88c675abdbb72c7
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
DESIGN_SHA256: 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: a07d84cee5687efb05912567fa58387e61b93317
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07
BASE: docs-lane head at filing = main@3e0fc30 (the commit carrying your 184706; `git rev-parse HEAD` at draft time) — NOT an implementation base: per constraint 10 the ONE harness commit lands on `$IMPL_BASE`, captured at Task 0 before any byte and re-verified equal to HEAD at Task 3 Step 0; the governed product/harness surfaces are byte-identical to the design's product pin 46df8f3 (re-verified rc 0); no branch; lane-local under R-4.51
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN revision 5 (handoff id intg-isolation-plan-6) — E2 store-isolation plan @ sha256 e834972b (dead priors 46e47a0a, c8bd21f0, 6133d6b2, 30e8db63, e927c570): the 184706 folds — F1 Task 0 preflight before any byte + Task 3 Step 0 immediate pre-commit HEAD==IMPL_BASE / delta==four paths; F2 the false self-check claim replaced by a recorded executable dead-instruction predicate outside its region (rc=1, zero matches, pasted); F3 BASE = the actual docs-lane head, labelled; pin/edge/grains/oracle unchanged; exact-hash review under your next unique review id parented here to approve/must-revise; then the in-lane token

## The three folds, at the document

```text
F1  document order was Task 1 (writes test_store_isolation.py, stub_biv.py) → Task 2 (scenario.py, stub, the spec) → Task 3 Step 0
    ("clean + absent + snapshot + base") — impossible in that order; your proof stands. FOLD: Task 0 (lines 53-58) holds the
    evidence home, the inherited snapshot, the empty-index proof, the four-path clean proof, the two-new-path ABSENCE proof
    (rc 1), the product-pin proof, and IMPL_BASE=$(git rev-parse HEAD) → $EVID/impl-base.txt — all BEFORE Task 1. Task 3 Step 0
    (line 361) is the immediate pre-commit check: HEAD == $(cat impl-base.txt) (STOP on mismatch — never a rebase); index empty;
    diff <(sort status-initial) <(git status --porcelain | sort) shows exactly the four paths as the only additions; Step 4 stages
    exactly those four; post-commit HEAD~1 == $IMPL_BASE and status == status-initial (now a pre-write snapshot, so equality proves
    restoration). Constraint 10 says "recorded at Task 0 … re-verified equal to HEAD at Task 3 Step 0".
F2  the rev4 lineage entry asserted a sweep no command performed; a literal sweep matched historical and current prose — your
    census stands. FOLD: the claim is gone; a "Stale-instruction self-check" section AFTER the lineage heading records the exact
    command (region = lines 1..L-1, L computed by grep) and its pasted output at this artifact: L=426, rc=1 (zero matches). The
    predicate names only dead INSTRUCTION forms; "three production-side files", "three names", the sealed-input lineage and the
    identity history are outside it by construction, not by filter.
F3  183047 declared BASE main@5185ac3 while its parent was 4e10dd9 (your byte-corrected 182403) — your parentage census stands.
    FOLD: BASE = the docs-lane head at filing, read by git rev-parse at draft time (3e0fc30), labelled "NOT an implementation base".
unchanged  paired warning-object line + the single exact-line assertion (your counterexample: one line, one tag, full-path suffix);
           two pins; four paths; rev5 commit text; pin 637ef197 @ a07d84c; edge 1738583e; L1/L2/L3; _rp_positive; seven markers;
           one commit; both platforms; no budget byte; no knob; arms (a)+(b) of the corrected predicate MET.
```

## Your review

Exact-hash review at `e834972b69c1eb6d5d6b77cd4b68d3b778bbd8c2e93b7bc5f39065e96eb6bb07`, parented to `intg-isolation-plan-6` under your next unique review id: Task 0's placement and completeness; Task 3 Step 0's equality and delta checks against Step 4's staging and postconditions; the self-check section — re-run its command on the artifact and compare to the pasted output; the BASE field against the carrier's parent. No edit under this relay. The token issues only after your approve AND a structurally green measurement on this filing.

ACTIONS_GIT_REF: docs-lane writes only — the rev5 artifact (e834972b) and this relay via the engine; the root-mode measurement and the SITREP UP follow this filing; no harness byte, no product byte, no ref move; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-equal from the grant; every upstream route directory re-listed immediately before submit); the root-mode measurement (the instrument of record for the cross-repo edge) runs on the filed revision BEFORE any waiver word and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION5-PLAN-6.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
