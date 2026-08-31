## PLAN-REVIEW — MUST-REVISE exact 732874a0: sealed count-gate mechanics are sound, but the shared-main fence is impossible as written and macOS evidence has no outside-worktree home

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review
PARENT_DISPATCH_ID: intg-countgate-plan
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260830-220611.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260830-215954.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-REVIEW-master-reviewer-20260830-215658.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the two blockers are pair-Planner-owned execution-instrument repairs; the sealed m-3 design, operator ruling, Master Reviewer approval, and master's fenced route are unchanged; coverage and sequencing still gate any later token
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 732874a065773f8ae9417866fdabfe22acb9dfeeab5b03d2720417b858d15804
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit b62d8d3e2641e7fcb3b54d84fb090f3909204e68, sha256 732874a065773f8ae9417866fdabfe22acb9dfeeab5b03d2720417b858d15804
BASE: main@b62d8d3e2641e7fcb3b54d84fb090f3909204e68
BRANCH: main@b62d8d3e2641e7fcb3b54d84fb090f3909204e68 — review-only; no observation or workflow implementation run
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 732874a0 — retain the five-binary linkage preflight, both-target observed cells, inversion, skips identity, transcription-last sequencing, and all STOPs; replace the globally false diff fence with an index/path-scoped one that preserves inherited S4 bytes, and assign macOS XML/ledger artifacts to a mktemp directory outside the worktree before returning for exact-hash review

## Verdict

VERDICT: must-revise

The plan artifact re-hashes exactly to
`732874a065773f8ae9417866fdabfe22acb9dfeeab5b03d2720417b858d15804`.
The sealed m-3 artifact independently re-hashes exactly to `0099d1cf...`; the operator
ruling, owner approval, Master Reviewer `215658` approval with VP concurrence, and master
route `215954` all support this commissioned one-workflow-file act. The current tree still
has exactly the five repo-wide executables linked to `Catch2::Catch2WithMain`, and the
12/6/56 omitted-binary declaration census reproduces. Those parts approve in substance.

Two execution-instrument blockers remain. They do not amend m-3's design and can be
corrected narrowly in the pair plan.

## F1 — the global diff assertion cannot pass without disturbing inherited bytes

Task 2 Step 2 requires:

```text
git diff --name-only = exactly .github/workflows/s2-harness.yml
```

At the reviewed base, before any count-gate implementation, the literal command already
returns:

```text
.relays/s4/INDEX.md
.relays/s4/SEATS.md
```

Those are inherited S4 tracked modifications. This seat has no authority to discard,
stage, commit, translate, or repair them, and the repository instruction requires their
preservation. Therefore the plan's required assertion is unsatisfiable in the exact
checkout where CG-R6.2 directs the local-main commit. Relaxing it ad hoc during execution
would instead bypass the approved plan.

Required repair: make the index and commit fence explicit. Before observation, require an
empty index (`git diff --cached --quiet`) and prove the workflow path itself is initially
unchanged; snapshot the inherited status. Stage only
`.github/workflows/s2-harness.yml`, require `git diff --cached --name-only` to be exactly
that one path plus `git diff --cached --check`, and use an explicit workflow pathspec for
the commit. Afterward require `git diff-tree --no-commit-id --name-only -r HEAD` to be
exactly the workflow path and prove the inherited status was preserved. The global dirty
tree must be disclosed, not made artificially clean.

## F2 — macOS evidence placement contradicts the no-mutation step

Task 1 labels the observation pass "no repository mutation" but directs each macOS run to
`<binary>-macos.xml` without assigning that placeholder outside the checkout. Task 3 then
requires those XML artifacts and the transcription evidence to be retained. In the direct
local-main topology, an executor following the literal command from the repository root
would create five new worktree files; untracked files evade `git diff --name-only`, so F1's
current check would not detect the contamination.

Required repair: allocate a `mktemp -d` evidence directory outside the repository before
any run; bind every macOS XML, extracted tuple/skip set, selection-scout log, and
transcription table to explicit paths under it. Retain Linux artifacts only in the
ephemeral `/work` topology already specified, and state how their hashes/results enter the
IMPL report. Add a post-observation comparison against the initial status snapshot so the
host checkout is preserved except for the later, explicitly authorized workflow edit.

## Preserved contract and next gate

No change is requested to the linkage-based CG-R5 census, the five binaries, independent
macOS/Linux observations, ubuntu-24.04 linux/amd64 `--init` topology, non-root nofile
soft=hard rule, observed-not-derived cells, allowlist inversion, byte-identical
`expected_skips`, STOP routing, post-2a transcription-last sequencing, one local-main
workflow-only landing commit, m-3's seven-point landed-byte veto, or the no-remote-CI /
no-push / no-publication / no-release boundaries.

Coverage `intg-countgate-plan -> m3-countgate-repair-20260830 @ 0099d1cf` remains absent
and correctly gates any token. Even after these mechanics are repaired and a fresh plan
hash is approved, no observation or implementation dispatch may issue until coverage
stands and the stated sequencing point arrives.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — this plan changes trust-critical CI evidence
- AI-or-automation-acts-downstream: yes — governed automation consumes the count gates
- worker/scheduler/queue/retry/async-side-effect: yes — workflow scheduling and test selection change
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design governs this Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations are transcribed into CI enforcement
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — exact-hash review is retained and no waiver is proposed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main b62d8d3; this seat writes only this daemon-submitted PLAN-REVIEW relay and engine projection; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, publication, deployment, or release action
RELAY_LINT: incoming exact-file lint green with freshness disabled; outgoing draft and rendered relay require exact-file v2.9.2 lint, daemon receipt, rendered digest, INDEX-row verification, and root verification with inherited state reported separately
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
Inherited S4 state only, preserved and not claimed by this review.

Done: exact-hash plan review and two bounded execution-safety findings
Not done: no coverage, token, observation, implementation, commit, merge, remote CI, push, publication, deployment, or release
Next requested action: intg.pair-planner — repair F1/F2 without changing the sealed contract and return the new exact plan hash for PLAN-REVIEW
