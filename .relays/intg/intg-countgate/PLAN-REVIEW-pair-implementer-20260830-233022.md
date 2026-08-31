## PLAN-REVIEW — APPROVE revision 2 at exact f9f960aa: F1/F2 close at the execution mechanisms; sealed count-gate contract and every downstream gate remain intact

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-countgate-plan-review-2
PARENT_DISPATCH_ID: intg-countgate-plan
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260830-232012.md
RELATED_CONTEXT: intg-countgate/PLAN-REVIEW-pair-implementer-20260830-221938.md; intg-countgate/PLAN-pair-planner-20260830-220611.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260830-215954.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this exact-hash approval closes the pair-owned plan review only; coverage and the stated transcription-last sequencing point are still mandatory before a token, and m-3's seven-point landed-byte review remains the acceptance gate
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 f9f960aa9b78d752989bdb068803636cf107f2465224f62ed1ea78b1b227d953
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit cbd92dc152dbfbcd0cba7e35cb9870afed5016a3, sha256 f9f960aa9b78d752989bdb068803636cf107f2465224f62ed1ea78b1b227d953
BASE: main@cbd92dc152dbfbcd0cba7e35cb9870afed5016a3
BRANCH: main@cbd92dc152dbfbcd0cba7e35cb9870afed5016a3 — review-only; no observation or workflow implementation run
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact f9f960aa revision 2 — F1 closes with empty-index and workflow-clean preconditions, path-scoped edit review, exact one-path cached fence, one-path diff-tree proof, and inherited-status byte equality; F2 closes with an outside-checkout mktemp evidence home, all macOS artifacts bound there, Linux artifacts copied out and hashed, and measured no-mutation equality; no token until coverage and sequencing both stand

## Verdict

VERDICT: approve

The revision-2 plan artifact re-hashes exactly to
`f9f960aa9b78d752989bdb068803636cf107f2465224f62ed1ea78b1b227d953`
at commit `cbd92dc152dbfbcd0cba7e35cb9870afed5016a3`. The incoming relay passes
exact-file v2.9.2 lint. The sealed m-3 design independently re-hashes to
`0099d1cf...`; the operator ruling remains `544a01be...`, Master Reviewer approval
`215658` remains an exact-pin APPROVE with VP concurrence, and master route `215954`
still assigns only this fenced execution through the pair's own gates.

This is exact-digest PLAN-REVIEW approval only. It is not a coverage entry,
implementation token, observation authorization, verification-complete claim, merge
grant, remote-CI grant, push grant, publication grant, deployment grant, or release
grant.

## Delta review — both prior findings close

### F1 — shared-main fence: closed

Revision 2 replaces the unsatisfiable global-diff assertion with a complete
index/path-scoped chain:

1. Task 1 Step 0 snapshots the inherited status, requires an empty index, and requires
   the workflow path initially unchanged.
2. Task 1 Step 6 requires the post-observation status to be byte-identical to the initial
   snapshot before any workflow edit.
3. Task 2 Step 2 reads the workflow diff path-scoped, stages exactly that file, requires
   the cached name list to be exactly that one path, and requires cached diff-check clean.
4. Task 2 Step 4 proves the landed commit with `git diff-tree` equal to the workflow path
   only and requires the remaining status to equal the initial inherited snapshot.

The mechanism is executable in the current shared checkout: the index is empty and the
workflow path is clean, while `.relays/s4/INDEX.md`, `.relays/s4/SEATS.md`, and the
standing S4 untracked files remain disclosed and unstaged. Nothing requires cleaning,
discarding, staging, or committing those foreign bytes.

### F2 — observation evidence home: closed

Task 1 Step 0 now allocates `$EVID` with `mktemp -d` outside the repository and binds
every macOS XML, extracted tuple/skip set, scout log, run-head receipt, and transcription
table beneath it. Task 1 Step 4 keeps Linux outputs in ephemeral `/work`, copies the five
XML files and ledger to the outside evidence home before container exit, and records each
XML digest. Step 5 binds all ten cells to run identities and source-XML digests; Step 6
makes no-mutation a status-snapshot equality gate. Untracked evidence can no longer evade
the fence inside the checkout.

The revision changes only those two plan mechanisms plus their acceptance wording. The
sealed design, five-target census, target platforms, observations, inversion, skip
identity, STOPs, one-commit rule, and authority boundaries are unchanged.

## Whole-plan revalidation

- The live CMake tree still has exactly five repo-wide executables linked to
  `Catch2::Catch2WithMain`: `biv_subprocess_tests`, `biv_repo_git_tests`,
  `biv_repo_engine_tests`, `biv_tests`, and `biv_probe_tests`; the independent source
  recount remains 12/6/56 for the first three omitted binaries.
- Task 1 performs the linkage-based CG-R5 preflight before observation and stops upward
  on added, removed, or renamed inventory. Each of all five binaries receives an
  independently observed cell on macOS and chartered ubuntu-24.04 linux/amd64 with
  `--init` and non-root nofile soft=hard.
- Task 2 admits no summed/derived want, removes the include-list model, retains only
  explicit-or-absent exclusions, preserves `expected_skips` membership byte-for-byte,
  and lands one commit containing only `.github/workflows/s2-harness.yml`.
- Task 3 carries the run identities, XML hashes, preflight inventory, selection
  justification, skip proof, and Linux ledger to m-3's seven-point landed-byte veto.
- Remote CI, PR, push, publication, deployment, seal, and release remain out of scope;
  the release hold is absolute.

## Remaining prerequisites — approval does not satisfy them

Coverage `intg-countgate-plan -> m3-countgate-repair-20260830 @ 0099d1cf` is still absent
from the visible intg lane. The plan correctly forbids an implementation dispatch until
that coverage stands. The Planner's stated transcription-last ordering also forbids the
observation and landing until the 2a merge has occurred, unless master explicitly directs
the already-disclosed earlier arm. Any later token must be a fresh bare `DISPATCH IMPL`
handoff parented to this approving review and issued only after both prerequisites hold.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the count gate is trust-critical CI evidence
- AI-or-automation-acts-downstream: yes — governed automation consumes the workflow gates
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design governs the Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific runtime observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — no waiver, downgrade, or live-evidence substitution is proposed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main cbd92dc; this seat writes only this daemon-submitted PLAN-REVIEW relay and engine projection; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, publication, deployment, or release action
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

Done: exact-hash revision-2 PLAN approval with F1/F2 and whole-contract revalidation
Not done: no coverage, token, observation, implementation, commit, merge, remote CI, push, publication, deployment, or release
Next requested action: intg.pair-planner — wait for coverage and the stated sequencing point, then issue only the fresh bare token parented to this approval
