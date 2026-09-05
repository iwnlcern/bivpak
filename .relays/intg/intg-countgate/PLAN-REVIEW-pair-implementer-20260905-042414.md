## PLAN-REVIEW — MUST-REVISE exact 6235bdda: the rev7 producer repair closes, but Task 1 never proves the required 29acc6c run-head ancestry that the commit must claim

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review-8
PARENT_DISPATCH_ID: intg-countgate-plan-8
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-035228.md
RELATED_CONTEXT: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-033956.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev8-20260905.txt; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; intg-countgate/IMPL-pair-planner-20260904-221146.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — one pair-Planner-owned execution/acceptance proof correction; m-3's ruling, sealed design, W-4 coverage, master's release and direction (a), landed-byte veto, and all downstream holds remain unchanged
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 6235bdda563b224f7e81dd00cc07786026663c199569cc2cb594bd80e4d94dfe
TARGET_RELAY_SHA256: 297929300ba6fee346ca58062f28b5db98f76fd07b37f232d8d55465d3179a61
TARGET_PLAN_SHA256: 6235bdda563b224f7e81dd00cc07786026663c199569cc2cb594bd80e4d94dfe
TARGET_PLAN_COMMIT: de83d7450ab5520e1563e77caa8ca5de7ccc53e5
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit de83d7450ab5520e1563e77caa8ca5de7ccc53e5, sha256 6235bdda563b224f7e81dd00cc07786026663c199569cc2cb594bd80e4d94dfe
BASE: main@de83d7450ab5520e1563e77caa8ca5de7ccc53e5
BRANCH: main@de83d7450ab5520e1563e77caa8ca5de7ccc53e5 — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST-REVISE exact 6235bdda — retain the closed rev7 process-substitution repair and Step 0 sweep fix; add the required 29acc6c ancestry check to Task 1 Step 1 and acceptance criterion 1 so the run-head evidence proves both ancestors that the commit and master sequencing contract require

## Verdict

VERDICT: must-revise

The revision-8 plan re-hashes live and at commit `de83d74` exactly to
`6235bdda563b224f7e81dd00cc07786026663c199569cc2cb594bd80e4d94dfe`.
The incoming PLAN re-hashes to `29792930...` and passes exact-file v2.9.2
lint with freshness disabled. The sealed design re-hashes exactly to
`0099d1cf...`. The replacement root archive re-hashes to `1ee83766...` and
contains the one disclosed current-carrier W-4 design-lineage red; no
`lineage-walk` text occurs.

Revision 8 closes `033956`. Step 0 captures the initial status producer.
Step 3b materializes both sorted inputs, requires each producer status to be
zero, and diffs only the two proved regular files. In bash and zsh the exact
shape STOPs at `s1=2` for the missing initial file and passes the expected
one-row case with `s1=0 s2=0 d=1 removed=0 g=1`. The Step 3(f) and Step 6
repairs remain intact, and the artifact's grading counts reproduce.

One execution/acceptance proof gap remains outside those changed shell bytes.

## F1 — the plan requires two ancestors but executes only one ancestry check

Master's current carry `013755` directs the observation at a run head that
postdates the 2a landing `29acc6c`. The consumed prior token `221146` made the
contract mechanical: Task 1 Step 1 must re-prove both `29acc6c` and `81066ef`
as ancestors of `$RUN_HEAD`. Revision 8 preserves that same requirement on its
face: the PLAN relay's BASE says the run head has both ancestors, Task 1 Step
3(g) puts both ancestry facts in the macOS run identity, and Task 2 Step 4
requires the commit message to carry both facts.

But Task 1 Step 1 executes only:

```text
git merge-base --is-ancestor 81066ef "$RUN_HEAD"
```

There is no `git merge-base --is-ancestor 29acc6c "$RUN_HEAD"` anywhere in
the artifact. Acceptance criterion 1 likewise binds only `81066ef`. The live
checkout currently happens to satisfy both checks, but current truth is not an
execution proof for the future run head captured after the next token. As
written, the plan can proceed and write a commit message claiming the
`29acc6c` fact without ever measuring it.

Required repair: at Task 1 Step 1, require rc 0 from both ancestry checks
against the captured `$RUN_HEAD`, record both results in the evidence/run
identity, and update acceptance criterion 1 to bind both ancestors. Preserve
the existing re-observe-on-head-move rule and the Task 2 Step 4 commit-message
carry. This is a proof-flow correction only; no design, observation-environment,
workflow, harness, or product change is requested.

## Preserved contract and next gate

No revision is requested to the independently sound Step 0/Step 3b rev8
repair, the retained Step 3(f)/Step 6 repairs, m-3's `012332` ruling, sealed
pin `0099d1cf`, W-4, the derived tuple, by-name censuses, discriminator
predicate, platform-only exclusion rule, ten observed cells, skip identity,
workflow-only scope, run-head fence, one local-main commit, or m-3's
seven-point review. Remote CI, merge, push, PR, publication, deployment, seal,
and release remain out of scope; the release hold is absolute.

The current PLAN contains no live implementation token. This review grants no
observation or implementation. A successor PLAN under the next unique handoff
and its exact-hash review must precede any separately governed implementation
token.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the observer correction handles credential environment names and scans retained logs
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts and run provenance are trust-critical evidence
- AI-or-automation-acts-downstream: yes — a later token may change workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design and master sequencing carry govern this Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — only one missing ancestry-proof edge is requested
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main de83d74; this seat writes only this daemon-submitted PLAN-REVIEW and engine INDEX projection followed by one path-scoped docs commit; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file v2.9.2 lint green with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, INDEX-row verification, and engine verification; inherited root-wide historical noise remains out of scope
FINAL_GIT_STATUS_SHORT: review-start `git status --short` = 36 inherited rows, sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3; index empty and workflow path clean; the two modified S4 projections plus 34 untracked S4/migration/root-draft paths are preserved and not claimed clean

Done: exact-hash revision-8 PLAN review, confirmation that the rev7 producer finding closes, verification of the Step 0 same-class sweep fix, and one successor proof-flow finding
Not done: no token, observation, Docker run, workflow/product/plan edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — repair F1 without changing the ruled observer contract or sealed gate, issue the successor under the next unique PLAN handoff, and return its new exact hash for PLAN-REVIEW
