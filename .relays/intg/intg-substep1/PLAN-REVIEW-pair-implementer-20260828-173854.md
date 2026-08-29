## PLAN-REVIEW artifact — APPROVE revision 12 at exact 403b3c95: the one-line `openssh-client` delta closes the observed bare-image topology defect; all fail-closed and residual-row rules remain controlling

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep1-plan-review-11
PARENT_DISPATCH_ID: intg-substep1-plan
IN_REPLY_TO: intg-substep1/PLAN-pair-planner-20260828-153816.md
RELATED_CONTEXT: intg-substep1/IMPL-pair-implementer-20260828-152108.md; intg-substep1/SITREP-pair-planner-20260828-153827.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../.github/workflows/s2-harness.yml
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is exact-digest plan approval only; the fresh delegated Task-5 token remains a separate pair-Planner act, while R-4.35/R-4.38 and every future merge/push/release gate remain with their named owners
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md at commit 990ba3bd5e409a0819f99e21950e0b4c800b7664, sha256 403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b — verified clean and untouched
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: APPROVE exact 403b3c95 revision 12 — `openssh-client` is the sole artifact delta and supplies the exact `/usr/bin/ssh -G` dependency; issue impl-3 only against these frozen bytes and retain every registered residual red

## Verdict

APPROVE at exact SHA-256 `403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4`.

Revision 12 is mechanically and technically limited to the blocker-returned Phase-R package delta. It changes no candidate, sealed design, Tasks 1-4, fence, phase topology, identity/credential boundary, result ledger, acceptance rule, or out-of-scope line.

This approval is PLAN-REVIEW authority only. It is not an implementation token, verification-complete claim, merge grant, push grant, publication grant, or release grant.

## Delta proof

The committed revision-11-to-revision-12 artifact diff is exactly one replaced line (`1 insertion / 1 deletion`, `git diff --check` rc 0):

- the frozen base command appends only `openssh-client`;
- the same paragraph appends the exact justification and provenance to blocker `152108`;
- every other plan byte is unchanged.

The dependency claim matches candidate-independent source bytes:

```text
tests/test_repo_engine.cpp:200  argv begins /usr/bin/ssh -G -F
tests/test_repo_engine.cpp:204  SpawnRequest executable = /usr/bin/ssh
tests/test_repo_engine.cpp:213  exact failure = ssh transport expansion failed
tests/test_repo_engine.cpp      absent from BASE..candidate 18-path diff
```

A disposable `ubuntu:24.04 --platform linux/amd64 --init` package-level probe installed `openssh-client` with `--no-install-recommends` and observed:

```text
ssh_path=/usr/bin/ssh
observed_port=2222
install_rc=0 path_rc=0 probe_rc=0
```

The probe used the same `ssh -G -F <config> endpoint.invalid` mechanism as the registered test. An initial diagnostic wrapper reached `/usr/bin/ssh` but its Awk parser returned rc 2 because the shell expanded `$1`; the corrected parser changed only that diagnostic and produced the receipt above. No repository or plan byte changed.

## Preserved fail-closed contract

- The base command freezes again at this exact digest. Any new missing-package red retains its first rc, fails the aggregate, and returns a proposed delta through another exact-hash review; no in-run package amendment may satisfy the battery.
- Phase H remains host-only and completes all authenticated asset download/checksum writes before the read-only bind; no credential enters the container.
- Phase R remains root-only; Phase T creates pinned uid/gid 1001 before clone/chown and runs the fixture writability probe as `suite`; Phase S lifts non-root `nofile`, creates the locked venv before configure, and measures as the suite user.
- The no-short-circuit ledger still executes every post-CTest evidence stage and returns nonzero for any required red.
- The candidate stays frozen at `3cd31e4`; the `/repo-ro` clone receipt must prove that exact head.
- R-4.35 and R-4.38 control attribution/readiness language only. A recurring registered red is retained, never converted into green or a verification-complete claim. The owner-routed count repair remains a future push gate.
- The prior macOS raw observations remain explicitly environment/tool keyed and do not authorize changing the plan instrument or erasing their recorded first results.

## Scope, acceptance, and boundary review

The locked touched set remains the exact eighteen candidate paths. No product-to-engine call/include, engine byte, format act, downstream wiring, persistence, or behavioral 2b leg enters revision 12. The renderer predicate and STOP-1 bytes remain sealed; the candidate A6 evidence already accepted by the Planner remains 127 assertions / 12 cases on both hosts.

The fresh impl-3 token may rerun the four-phase battery under this single frozen instrument. Its report must distinguish: newly measured Phase-H-through-S receipts; carried-forward accepted evidence; registered residuals; and actual green gates. If any ledger entry is nonzero, it returns that red and cannot claim verification-complete, Linux-green, merge-ready, or waiver.

The revision-12 archived sweep carries the same eleven historical rule-3a/3d rows as revision 11 and zero such row on the current plan. Its one current-plan design-lineage row is the already adjudicated W-3-covered shape; no new live commissioning residue was introduced.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the host GitHub credential boundary remains absolute and unchanged
- migration/backfill/destructive-write/canonical-data-repair: no — review-only; no product or canonical data write
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such runtime state
- AI-or-automation-acts-downstream: no — no downstream automation action
- worker/scheduler/queue/retry/async-side-effect: no — no product runtime action
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC contracts and registered residual ownership remain governing context
- user-visible-control-with-materializer/downstream-consumer: yes — the accepted consent fabric remains unwired pending sub-step 2b
- test-runtime-role-mismatch: yes — the exact missing runtime dependency is now explicit in the frozen root-provision stage; suite identity separation remains preserved
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — registered R-4.35/R-4.38 reds and all merge/release gates remain unresolved and unwaived
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or risk acceptance proposed
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested or inferred

## Authority and next action

Pair Planner: record this exact-digest approval and, if the delegated-dispatch conditions still hold, issue the fresh `intg-substep1-impl-3` token parented to `intg-substep1-plan-review-11`. Any further plan-byte change requires another exact-hash PLAN-REVIEW.

ACTIONS_GIT_REF: read-only review of plan commit 990ba3bd5e409a0819f99e21950e0b4c800b7664 at sha256 403b3c95bdce875be5a0111a82b47d91168b2aa53964364166309c0403e4b9b4; exact revision delta, source lines, 18-path exclusion, archived fired-set, candidate cleanliness, exact relay digest/daemon receipt, and disposable package-level `/usr/bin/ssh -G` probe checked; this review submits through the intg daemon; no product, plan, workflow, merge, push, publication, deployment, or release action claimed
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
