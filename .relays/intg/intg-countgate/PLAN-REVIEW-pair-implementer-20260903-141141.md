## PLAN-REVIEW — APPROVE revision 3 at exact 6eee9b30: the run-head fence is executable, the sealed five-binary mechanics are preserved, and the released transcription-last order is bound without widening scope

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-countgate-plan-review-3
PARENT_DISPATCH_ID: intg-countgate-plan-3
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260903-061927.md
RELATED_CONTEXT: intg-countgate/PLAN-REVIEW-pair-implementer-20260830-233022.md; intg-countgate/SITREP-pair-planner-20260903-062948.md; intg-countgate/SITREP-pair-planner-20260903-140314.md; intg-isolation/SITREP-pair-implementer-20260903-060252.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev3-20260903.txt; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260903-135906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — this exact-hash approval closes only the pair-owned plan review at 6eee9b30; W-4 stands only for the frozen current-revision lineage and master has separately released observations and directed order (a); any implementation still requires a fresh addressed bare token, executes only after 2a tranche 2 lands, and retains m-3's landed-byte veto plus separate push, publication, deployment, and release gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d
TARGET_RELAY_SHA256: 4d8208d68086f05c579fcf59b7d8ca21f13fdd550ccafb875f3a3e6d73cb42ba
TARGET_PLAN_SHA256: 6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d
TARGET_PLAN_COMMIT: 00584b1d1b6fcc67b3e01980f0c08db394341287
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit 00584b1d1b6fcc67b3e01980f0c08db394341287, sha256 6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d
BASE: main@9e1a72d050b306c0629138e0c37f8474901ab604
BRANCH: main@9e1a72d050b306c0629138e0c37f8474901ab604 — review-only; no observation, Docker run, workflow edit, product byte, staging, or commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: APPROVE exact 6eee9b30 revision 3 — the sealed five-binary observed-not-derived mechanics remain intact; the run-head and two-sided status guards now bind the observations to the landing parent; W-4's current-revision replacement contains exactly the disclosed covered carrier red; master has released observations and selected transcription-last order (a); issue no observation or workflow instruction except through the fresh token, and execute it only after 2a tranche 2 lands

## Verdict

VERDICT: approve

The revision-3 plan artifact re-hashes exactly to
`6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d`
live and at commit `00584b1d1b6fcc67b3e01980f0c08db394341287`. The incoming
PLAN relay re-hashes to `4d8208d6...` and passes exact-file v2.9.2 lint. The
sealed m-3 design independently re-hashes to `0099d1cf...`; its owner and
Master Reviewer approvals remain at the exact pin.

This approval is review-only. It is not an implementation token, observation
instruction, workflow edit, commit grant, merge grant, remote-CI grant, push
grant, PR grant, publication grant, deployment grant, seal, or release grant.

## Revision-3 delta review

The previously approved revision-2 mechanics remain intact: the linkage-based
five-binary preflight, ten independently observed target cells, macOS selection
inversion, byte-identical `expected_skips` membership, outside-checkout
evidence home, one-path index fence, one local-main workflow commit, and m-3's
seven-point landed-byte veto.

Revision 3 adds the missing execution binding:

1. Task 1 Step 1 records `run-head.txt` before the preflight and observations,
   requires `81066ef` ancestry, and makes a moved main a STOP followed by
   re-observation rather than rebase or cherry-pick.
2. Task 2 Step 3b is adjacent to the commit and checks HEAD equals the recorded
   run head, the index contains exactly the workflow path, no inherited
   porcelain row vanished, and the sole new row is exactly the staged workflow
   modification.
3. Task 2 Step 4 proves after commit that the sole parent equals the recorded
   run head, records the landed sha, proves the one-path tree, and requires the
   inherited status snapshot byte-equal.

Those checks close the observation-to-parent race identified in the isolation
lane without changing the sealed workflow scope.

## Independent whole-plan evidence

- `81066ef` is an ancestor of plan commit `00584b1`; workflow and CMake
  bytes are unchanged from the revision-2 approval baseline.
- The live CMake file still has exactly five repo-wide executables linked to
  `Catch2::Catch2WithMain` at the five cited link sites. The binding Master
  Reviewer clarification confirms that linkage, not a raw all-executable
  census, is CG-R5's criterion.
- The Linux leg preserves Ubuntu 24.04 on linux/amd64 with `--init`, pinned
  non-root uid 1001, and restoration of the runuser `nofile` soft limit to
  the inherited hard limit before measurement.
- The replacement root-sweep archive re-hashes to `8ed2cdd5...`: 344 inherited
  ERROR rows and 28 WARN rows overall, with exactly one ERROR on the revision-3
  carrier, the disclosed W-4-covered `0099d1cf` design-lineage identity.
- Master relay `135906` releases the observations and binds direction (a):
  execution follows 2a tranche 2 and transcribes once. The canonical-edge
  alternative remains untaken; W-4 is neither widened nor treated cumulatively.
- The plan keeps every byte outside `.github/workflows/s2-harness.yml`,
  remote CI, push, PR, publication, deployment, seal, and release out of scope.

## Remaining execution gates

This approval satisfies only the exact-hash review predicate. The pair Planner
may issue the fresh countgate implementation token parented to this review, but
the directed execution order remains:

```text
2a tranche 2 lands
  -> countgate observations at the then-current stated run head
  -> one workflow-only transcription commit under the run-head guard
  -> m-3 seven-point landed-byte review
  -> master's separately routed first-push act
```

No countgate observation or repository byte may move under this review relay.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — review closure can permit the Planner to issue the separately gated fresh implementation token
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts are trust-critical evidence
- AI-or-automation-acts-downstream: yes — a later token may change workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design governs the Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — revision 3 narrows execution provenance and preserves all sealed boundaries
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: W-4 already effective for the frozen countgate lineage and exact current-revision design row; no new waiver requested
- valid_waiver: yes — only for the preserved lineage at revision 3 and the exact 0099d1cf eligible row
WAIVED_RISK_ACCEPTANCE: unchanged from W-4; this review neither expands nor reopens it

ACTIONS_GIT_REF: read-only exact-byte review at main 9e1a72d; this seat writes only this daemon-submitted PLAN-REVIEW relay and engine projection; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file lint green with freshness disabled; outgoing draft and rendered relay require exact-file v2.9.2 lint, daemon receipt, rendered digest, INDEX-row verification, and root verification with inherited root state reported separately
FINAL_GIT_STATUS_SHORT: inherited 35-row shared-tree state at review start, sha256 aee3eac8aa0a74221c8a386b27ef04a081284e89fafbb8e1d57f2a26632925f5; index empty and workflow path clean; preserved and not claimed by this review

Done: exact-hash revision-3 PLAN approval with whole-contract, run-head, sequencing, and current-revision coverage revalidation
Not done: no token, observation, Docker run, workflow/product edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — issue the fresh countgate token parented to this approval, preserve order (a), and do not execute it until 2a tranche 2 has landed
