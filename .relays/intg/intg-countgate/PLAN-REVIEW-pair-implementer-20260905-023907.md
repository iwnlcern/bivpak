## PLAN-REVIEW — MUST-REVISE exact b2c92956: the three prior findings close, but revision 5 introduces a fail-fast zero-match trap and does not carry its new discriminator predicate through acceptance

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review-5
PARENT_DISPATCH_ID: intg-countgate-plan-5
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-022403.md
RELATED_CONTEXT: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-020651.md; intg-countgate/PLAN-pair-planner-20260905-014631.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev5-20260905.txt; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — two pair-Planner-owned execution-instrument corrections; m-3's ruling, sealed design, W-4 coverage, master's release and direction (a), landed-byte veto, and all downstream holds remain unchanged
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e
TARGET_RELAY_SHA256: 2322b81fdafa94ec3a78e9fdb1ed20b97142b725eec10899ecce7ad41182223a
TARGET_PLAN_SHA256: b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e
TARGET_PLAN_COMMIT: 02a7db1eb214d5c6310be15a801cd14c248da605
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit 02a7db1eb214d5c6310be15a801cd14c248da605, sha256 b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e
BASE: main@02a7db1eb214d5c6310be15a801cd14c248da605
BRANCH: main@02a7db1eb214d5c6310be15a801cd14c248da605 — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST-REVISE exact b2c92956 — retain the closed rev4 F1/F2/F3 mechanics; replace the optional stateful set +e/set -e path with one deterministic status-capture form that survives legitimate zero-match counts and distinguishes grep error from zero, then explicitly carry the arm-1 iff predicate and presence count through Step 5, Task 2 Step 4, and acceptance 6

## Verdict

VERDICT: must-revise

The revision-5 plan re-hashes live and at commit `02a7db1` exactly to
`b2c9295647188ff97fd0a4846562031c9c9a8ddfe84a9d67e10ff112143efc2e`.
The incoming PLAN re-hashes to `2322b81f...` and passes exact-file v2.9.2
lint with freshness disabled. The sealed design remains exact at `0099d1cf...`.

Revision 5 closes all three `020651` findings in the changed lines: both live
identity references now name `intg-countgate-plan-5`; each arm captures its
immediate `$?` into a named numeric file; and `OBS_ENV` is scoped to the five
XML runs, scout, and arm 2 while arm 1 remains the as-is control. The root-sweep
archive `b5fe79ca...` shows exactly the disclosed W-4 design-lineage red on the
new PLAN carrier and zero lineage-walk text. Those parts approve in substance.

Two execution defects remain in the new exact bytes.

## F1 — the permitted fail-fast form aborts on the valid zero state

Step 3(c) permits either a subshell or `set +e` followed by unconditional
`set -e`. After that restoration, its predicate uses `grep -c present`.
When no derived name is present — an explicitly valid arm where rc1 must be
zero — `grep -c` prints `0` but returns status 1. Under the permitted `set -e`
form, the shell exits before the comparison. The same defect recurs at Step
3(f): the required secret scan prints zero matches and returns status 1, so a
clean scan aborts the task.

The behavior reproduces directly at E2:

```text
zsh -c 'set -e; n=$(printf "absent\n" | grep -c present); echo reached'
=> rc 1; "reached" absent

zsh -c 'set -e; printf "ordinary log\n" | grep -c -E "sk-[A-Za-z0-9]{8,}|-----BEGIN"; echo reached'
=> prints 0, rc 1; "reached" absent
```

Required repair: select one exact, state-contained capture form rather than an
unsafe alternative. Preserve the caller's fail-fast state, make zero presence
and zero secret matches successful data, and still distinguish a real grep or
input error from the expected no-match status. The two ctest statuses must
still be captured immediately and all STOP predicates retained.

## F2 — the new predicate is asserted only inside Step 3

Step 3(c) says the two numeric codes and presence count flow into Step 5, Task
2 Step 4, and acceptance criterion 6. Those three surfaces were not updated:
Step 5 and Task 2 carry the census plus both rc values but do not name the
presence count or predicate result, and acceptance 6 requires only arm 2 rc 0;
it does not require `rc1 != 0` iff presence count is greater than zero.

Required repair: explicitly add the recorded presence count and arm-1 iff
predicate result to Step 5's environment block and Task 2's commit evidence,
and bind both arms plus the iff result in acceptance criterion 6. This is an
evidence-flow correction only; no design, workflow, harness, or product byte
changes.

## Preserved contract and next gate

No revision is requested to m-3's `012332` ruling, sealed pin `0099d1cf`, W-4,
the derived tuple, by-name censuses, platform-only exclusion rule, ten observed
cells, skip identity, workflow-only scope, run-head guard, one local-main
commit, or m-3's seven-point review. Remote CI, merge, push, PR, publication,
deployment, seal, and release remain out of scope; the release hold is
absolute.

The current PLAN contains no fresh implementation token. This review grants no
observation or implementation. A successor PLAN under the next unique handoff
and its exact-hash review must precede any separately governed implementation
token.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the observer correction handles credential environment names and scans retained logs
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts are trust-critical evidence
- AI-or-automation-acts-downstream: yes — a later token may change workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design and m-3 ruling govern this Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — only deterministic shell and evidence-flow corrections are requested
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main 02a7db1; this seat writes only this daemon-submitted PLAN-REVIEW and engine INDEX projection followed by one path-scoped docs commit; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file v2.9.2 lint green with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, INDEX-row verification, and engine verification; the inherited root INDEX inversions remain out of scope
FINAL_GIT_STATUS_SHORT: review-start `git status --short` = 36 inherited rows, sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3; index empty and workflow path clean; the two modified S4 projections plus 34 untracked S4/migration/root-draft paths are preserved and not claimed clean

Done: exact-hash revision-5 PLAN review, confirmation that prior F1/F2/F3 closed, and two successor findings
Not done: no token, observation, Docker run, workflow/product/plan edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — repair F1/F2 without changing the ruled observer contract or sealed gate, issue the successor under the next unique PLAN handoff, and return its new exact hash for PLAN-REVIEW
