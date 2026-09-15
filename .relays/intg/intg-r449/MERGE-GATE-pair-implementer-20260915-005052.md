## MERGE-GATE RETURN — R-4.49 STOP before merge: operator carrier is outside the active intg relay root

ROLE: Pair Implementer
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-r449-merge-token
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r449-merge-token/MERGE-GATE-operator-20260915-004138.md
RELATED_CONTEXT: intg-r449/MERGE-GATE-pair-planner-20260914-225755.md; ../../pdc/master/relays/intg-commission-charter/DESIGN-master-planner-20260827-144023.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — operator must supply a live merge dispatch under this seat's active relay root or directly to this sole Implementer; the present sibling-root carrier does not satisfy location-binding.
MERGE_STATUS: merge-blocked
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-r449-line1-selection-plan-20260913 @ sha256 39b8966b7edd065b8612419d177648dfc11248ea0566c14f0ab16a875a98d5b6
BRANCH: intg/r449-line1-selection at b74ec570e22646bfee6a0c554bcb766fffa6da19
TARGET_BRANCH: main
BASE: 4cf135ee97f57021c5fc5fd5343de6f655fb0d24
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer
SUBJECT: R-4.49 merge STOP — 004138 passes literal/address/phase and artifact hashes, but is in sibling pdc/master/relays rather than active bivpak/.relays/intg; no merge or push attempted; request live operator gate

## Discriminating authority check

The operator carrier resolves to `/Users/jack/Programming/pdc/master/relays/intg-r449-merge-token/MERGE-GATE-operator-20260915-004138.md`. It contains the bare own-line merge token, `FROM: operator`, `TO: intg.pair-implementer` as the sole addressee, and `PHASE: MERGE-GATE`; standalone 2.9.3 exact-file lint returns OK. The pdc master INDEX lists it at row 1957.

However, the commission charter's LAYOUT fixes this seat's active root to `../bivpak/.relays/intg/`. Both charter-pinned v2.9.2 protocol.md lines 237–243 and the loaded v2.9.3 protocol's literal-merge section require all five properties, including location under the active root, and explicitly classify sibling relay trees as inert. Searching the intg INDEX and operational Markdown found no carrier with this merge-handoff id and no root override. A user-supplied path is transport to the file, not a direct own-line token. The existing landing precedent and standalone lint success do not waive this predicate; I have not copied, re-authored or relocated the operator's FROM.

## Checks completed before STOP

All three live file hashes equal the carrier's pins:

```text
packet     67106a12066642ce76d6aa6bece390f1fa85aaf4977293e3077c189651bfee38
population d8b37f247dd2217c125c5c674ee94eb35221398d7d180d11920446472f67bbc1
instrument 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6
```

PR #27 read-back: OPEN, non-draft, base main, head intg/r449-line1-selection at H `b74ec570e22646bfee6a0c554bcb766fffa6da19`, MERGEABLE, mergeStateStatus UNSTABLE (the unfunded remote observation is not a gate). Remote main is still B `4cf135ee97f57021c5fc5fd5343de6f655fb0d24`; local lane main is `b4f1028199bb3bd9a550334966ce5d480063d5d1`; the candidate linked worktree's status is empty.

No local merge, census-at-merge invocation, dry-run push or real push occurred. No merge or push attempt is spent. I stopped before packet §7 step (1)'s executable sequence; therefore I do not claim its pre-merge invariants or the post-merge census have passed.

## Requested correction

Pair Planner: route this location mismatch UP to master/operator. Have the operator issue the same exact H and packet/instrument/population-bound grant through an operator-authored engine carrier under the active intg root, or send a direct bare own-line `DISPATCH MERGE` addressed only to this Implementer and binding the same 004138 scope. An explicit operator resolution of the root conflict is another governed path; do not treat this report, a copy, a CC or the packet as that resolution. After a live gate arrives, re-check current state and follow the four written steps once; STOP on any required witness failure. Merge ≠ push ≠ release; release hold ABSOLUTE.

Boundary contract: this report writes only the durable blocker for the Pair Planner's routing; it reads the operator carrier, charter/protocol, exact artifact hashes and read-only Git/forge observations. Product and publication state remain unchanged.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — merge authority location mismatch, reported without weakening it
- migration/backfill/destructive-write/canonical-data-repair: no — no merge or push performed
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such surface
- AI-or-automation-acts-downstream: no — planned downstream mutation stopped
- worker/scheduler/queue/retry/async-side-effect: no — no runtime launched
- cross-repo/service-contract/generated-schema/shared-API-event: yes — operator carrier crosses the master/intg root boundary
- user-visible-control-with-materializer/downstream-consumer: no — no product byte changed this turn
- test-runtime-role-mismatch: no — no new test evidence claimed
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — accepting a sibling-root gate would require operator resolution
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none requested or inferred
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: this draft and its engine-rendered blocker relay only; main remains b4f1028199bb3bd9a550334966ce5d480063d5d1; remote main remains B 4cf135ee97f57021c5fc5fd5343de6f655fb0d24; remote candidate remains H b74ec570e22646bfee6a0c554bcb766fffa6da19. No merge, push, tag, deployment or release.
RELAY_LINT: draft and rendered exact-file lint required; no inherited INDEX bytes repaired.
FINAL_GIT_STATUS_SHORT:
```text
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/intg/intg-r449/AUDIT-pair-implementer-20260913-165828.md
?? .relays/intg/intg-r449/IMPL-pair-implementer-20260914-174929.md
?? .relays/intg/intg-r449/IMPL-pair-implementer-20260914-192821.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-010344.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-023545.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-040639.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-052443.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-151913.md
?? .relays/intg/intg-r449/PLAN-REVIEW-pair-implementer-20260914-162558.md
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
?? relay-draft-intg-task4-stop.md
```

CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-planner

