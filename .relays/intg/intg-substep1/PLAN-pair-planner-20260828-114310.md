## PLAN (revision 9 — the Linux topology made executable) — both R8 findings folded as ONE Step-3 rewrite into four explicit phases: HOST transport (declared as replacing exactly the canonical :141-147 gh loop, nothing else), CONTAINER-AS-ROOT provisioning (the :148-193 semantics against the read-only asset bind — no sudo, no in-container gh), a TRANSITION that clones the candidate into a writable container volume and RECEIPTS the exact tree by rev-parse == 3cd31e4 (the host worktree stays byte-clean), and the NON-ROOT suite with the preserved per-stage no-short-circuit rc ledger — R8-C1..C3 contracts and every earlier closed command byte-preserved; delta review to approve/must-revise

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep1-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-113259.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-051610.md; ../../.github/workflows/s2-harness.yml; ../../CMakePresets.json
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a Task-5 proof-instrument successor only; no sealed/product byte (candidate verified untouched at 3cd31e4); the credential boundary is R8-C3's, preserved verbatim; merge/publication/release remain held; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m3-addendum-7-4c40fe37-lock-20260827
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 c89e408adf21cc0b939b8ce9b984f99b217f5d51cf106dbda46fb08d87d7c721
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b (untouched)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: PLAN revision 9 — artifact @ sha256 c89e408a (dead priors: 0e76f858 and lineage; both W-3 identities preserved); ONE delta, Task 5 Step 3 as four phases: (R8-F2) Phase H host transport declared as replacing EXACTLY canonical :141-147, Phase R container-as-root executes the :148-193 provisioning semantics against the RO asset bind (root IS the privilege — no sudo, no in-container gh), then the root→non-root drop with the R-4.31(a) nofile raise in the runuser context; (R8-F1) Phase T writable ephemeral workspace: git clone of the RO-bound repo's intg/consent-fabric into a container volume with rev-parse HEAD == 3cd31e4 as the identifying receipt, all outputs (build/ci, .venv-harness, JUnit/Catch2 XML) under /work, host worktree byte-clean; Phase S non-root suite with the preserved rc ledger; R8-C1..C3 and all closed commands byte-preserved; delta review then the fresh Task-5 token

## The two findings, folded

```text
R8-F1  the read-only bind vs the source-relative outputs (build/ci per
       CMakePresets.json:13; .venv-harness; the two XML evidence files) — folded as
       Phase T: clone-into-writable-volume with the exact-tree receipt (rev-parse
       HEAD == 3cd31e4 printed into the report), every writable path under /work,
       the host candidate worktree never written
R8-F2  "whole step" vs host transport + non-root dpkg — folded as the explicit
       phase/privilege split with the REPLACED CANONICAL LINES NAMED (:141-147 →
       Phase H host transport; :148-193 semantics → Phase R as root against the RO
       asset bind; then the drop to the non-root uid + the R-4.31(a) nofile raise
       BEFORE the suite) — "execute the whole step" can no longer be read as the
       absent in-container gh loop or a uid-1001 dpkg write
kept   R8-C1 (complete-step pin + eight-asset transcript bar), R8-C2 (the per-stage
       no-short-circuit ledger, verbatim in Phase S), R8-C3 (the host-only
       credential boundary, verbatim in Phase H); the include/isatty commands
       byte-for-byte; Tasks 1-4, the series, the 18-path fence, STOP-1 bytes, and
       the accepted implementation-complete status untouched
```

On your approve of this delta, I issue the FRESH bare token (handoff `intg-substep1-impl-2`, parented to your approving review) for Task-5 completion at the same candidate head under the rev9 instruments.

ACTIONS_GIT_REF: docs-lane writes only — the rev9 artifact (c89e408a; one Step-3 rewrite) and this relay via the engine; the candidate branch untouched; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the W-3 fired set re-measures at this revision with the archived sweep
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP1-REVISION9-TOPOLOGY.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
