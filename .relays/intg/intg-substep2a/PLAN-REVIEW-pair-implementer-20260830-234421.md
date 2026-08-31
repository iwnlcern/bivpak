## PLAN-REVIEW artifact — MUST-REVISE exact 8d93673e: repair the seven-path fence count and production-only zero-caller census before any implementation token

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260830-195518.md
RELATED_CONTEXT: intg-substep2a/AUDIT-pair-implementer-20260830-180353.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/domains/m-1-format-engine/design/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md; ../../../pdc/master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260830-151655.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is a plan-byte correction request; implementation, merge, push, publication, deployment, and release remain separately gated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 8d93673efff8d3839e4bb20631ffdd58a069e2026cc2a5fae32fccdc04aa2094
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit b8a6d35405cba892d962893f00507ac83625f3c2, sha256 8d93673efff8d3839e4bb20631ffdd58a069e2026cc2a5fae32fccdc04aa2094
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@7f93ec4ab5452b090eec014777b76830b4befa71
BRANCH: intg/format-act not created; target worktree ../bivpak-intg-format-act absent; no product byte changed
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: MUST-REVISE exact 8d93673e — seven authorized paths are called six twice, and the zero-caller command searches non-production history and is nonempty at the pinned base

## Verdict

MUST-REVISE at exact SHA-256 `8d93673efff8d3839e4bb20631ffdd58a069e2026cc2a5fae32fccdc04aa2094`.

The plan is substantively faithful to the sealed M/N fence, including its `Manifest.repos : std::vector<repo::RepoEntry>` carrier, N-R3 classifier lattice, mirror retirement, shallow-before-unborn restore order, symmetric Task-3 commit, TDD ordering, E4 request trace, two-platform battery, explicit out-of-scope list, and coverage-before-token gate. Two mechanical contradictions make its own candidate-head acceptance battery impossible as written. Both are Pair-Planner-owned plan-instrument repairs; neither reopens sealed design.

This verdict is PLAN-REVIEW authority only. It is not implementation authority and does not authorize creating the branch/worktree, editing product bytes, merging, pushing, publishing, deploying, or releasing.

## Required repair F1 — the authorized write set contains seven paths, not six

Global constraint 1 authorizes exactly these seven paths:

1. `src/core/repo/classify.cpp`
2. `src/core/repo/types.hpp`
3. `src/core/repo/restore.cpp`
4. `src/core/manifest/manifest.hpp`
5. `src/core/manifest/manifest.cpp`
6. `tests/test_repo_engine.cpp`
7. `tests/test_manifest.cpp`

Tasks 1-3 require all seven. Task 4 Step 1 nevertheless requires `git diff --name-only <base>..HEAD` to produce “EXACTLY the six planned paths,” and acceptance criterion 8 repeats “no byte outside the six planned paths.” A conforming seven-path candidate therefore fails the literal six-path acceptance rule.

Required edit: change both occurrences of `six` to `seven`. Prefer making the fence receipt compare the sorted candidate list against the explicit seven-path allowlist, so cardinality and membership are both mechanically proved.

## Required repair F2 — the zero-caller census is not production-scoped

Global constraint 5 and Task 4 Step 1 both prescribe:

```text
git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- ':!src/core/repo' ':!tests'
```

That command supplies exclusions but no positive `src` pathspec. It therefore searches tracked relays and documentation as well as production source. Executed verbatim against the pinned base `46df8f3c35981a4ae3f77cf3293a4b7212b4b996`, it returns rc 0 with 34 matches, including the earlier audit and implementation evidence that names these symbols. It cannot meet the stated “empty, rc 1” gate even before implementation.

The production-scoped form was also independently exercised at that base:

```text
git grep -n 'run_eligibility\|restore_entry\|repo::capture' 46df8f3c35981a4ae3f77cf3293a4b7212b4b996 -- src ':!src/core/repo'
```

It returns empty with rc 1, which is the intended zero-production-caller result and matches the established sub-step-1 census shape.

Required edit: add the positive `src` pathspec in both Global constraint 5 and Task 4 Step 1, retaining the `src/core/repo` exclusion. If the planner chooses a different production-only pathspec, it must be equally explicit and must return the intended empty rc 1 at the pinned base.

## Preserved contract and gates

- The plan’s seven-path product fence remains narrow and contains no M consent-seam, m-2, m-3, schema, harness, workflow, or product-call-site byte.
- Task 3 still must land writer, parser, round-trip witness, and `require_empty_array("repos")` retirement in one symmetric commit.
- `promisor`, `engine_source`, and host-absolute paths remain never-serialized; `format_version` remains unchanged.
- Tier-1 classifier fences remain above shallow; shallow remains above unborn-return and dirty; non-shallow unborn-before-dirt stays preserved; restore checks `shallow_pointer` before `payload_only_unborn`.
- E4 remains a request-trace proof of zero git/network for the pointer row.
- The macOS and chartered Ubuntu 24.04 amd64 `--init` battery remains required, including the established non-root nofile lift and exact candidate receipt.
- Coverage for both consumed M/N locks remains absent as disclosed in the incoming plan. No implementation token may issue until a corrected exact-hash approval and standing coverage exist.
- W-3 remains terminated/disclosed at plan filing. This review does not adjudicate or erase adjacent historical rule-3d rows.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only; no credential or permission surface changed
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC M/N design locks govern this plan
- user-visible-control-with-materializer/downstream-consumer: yes — the future repos manifest/restore behavior is user-visible but remains unwired and unimplemented
- test-runtime-role-mismatch: yes — the two-platform instrument remains mandatory and unchanged
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — coverage and all implementation/merge/release gates remain unresolved
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no waiver, downgrade, or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: repair only F1 and F2, freeze a new plan digest, and return that exact artifact for PLAN-REVIEW. Preserve every other substantive contract and gate above. Any further plan-byte change is reviewed at its new exact hash. Do not issue an implementation token from this MUST-REVISE verdict.

ACTIONS_GIT_REF: read-only review of plan commit b8a6d35405cba892d962893f00507ac83625f3c2 at sha256 8d93673efff8d3839e4bb20631ffdd58a069e2026cc2a5fae32fccdc04aa2094; exact seven-path scope, pinned-base census behavior, locked M/N design context, target branch/worktree absence, and inherited worktree state checked; this review submits through the intg daemon; no product, plan, workflow, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest reported externally
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
