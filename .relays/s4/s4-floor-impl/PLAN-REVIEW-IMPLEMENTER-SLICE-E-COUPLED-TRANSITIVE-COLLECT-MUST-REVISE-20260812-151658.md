## PLAN-REVIEW — slice E coupled plan has the right locked mechanisms but is not executable without rediscovering scope; MUST-REVISE on six bounded points

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review
PARENT_DISPATCH_ID: s4-floor-slice-e-plan
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no new product decision for findings R1-R5; R6's cross-repo lineage/tooling disposition routes to the orchestrator before any delegated dispatch
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MONO-GATE-20260812-150913.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: MUST-REVISE slice E PLAN — exact scope/carrier and four-cap producer closure missing; unsupported flag escape; FX-A12-4a misclassified; fixture/verification matrix and cross-repo lint lineage must close before dispatch

PLAN_REVIEW_VERDICT: must-revise

The exact design hashes reproduce at the named PDC commits:

```text
Addendum-12 @ 3929c9c = 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
Addendum-J  @ e30f845 = 94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
```

The plan correctly carries the transitive gather, explicit rootless-component pass, least-cycle-member
break, mapped-node membership ground, `A(E) subset-of A(0)`, edge-only-refuses rule, real
`CollectReport.warnings` carrier, m-1 fence, three-level actual-binary E2E, live-store prohibition, and
R-4.24 exclusion. Those parts need no semantic redesign. The following are blockers to an executable
implementation plan.

## R1 — REQUIRED s4 carrier/emission surfaces are missing from an exact mechanical scope

Addendum-12 `A12.2.4` requires a NEW
`adapters::SessionRecord::child_parent_map` in `src/adapters/adapter.hpp`; `A12.2.5` requires
`manifest_entry_for` in `src/core/pack/pack.cpp` to emit each non-primary child edge. At `0db8fdd`,
`SessionRecord` has only `child_ids` and `child_artifact_map` (`adapter.hpp:71-100`), while
`manifest_entry_for` constructs flat `SessionChild` objects at `pack.cpp:384-433`.

The plan labels T1 only as `codex.cpp` and never provides a file-by-file implementation scope. That makes
the later mandatory `SCOPE_DIFF` unperformable and risks treating `adapter.hpp`/`pack.cpp` as an improvised
integration hook.

Required revision: enumerate every production, test, and fixture path in the locked plan, including at least:

- `src/adapters/adapter.hpp` — `child_parent_map` carrier;
- `src/adapters/codex/codex.cpp` — closure, rootless disposition, staged-reader gate, warning producer;
- `src/adapters/codex/install.cpp` — writer gate and mapped-node set;
- `src/core/pack/pack.cpp` — J-licensed edge emission and producer closure;
- `tests/test_adapter_codex_collect.cpp`;
- `tests/test_adapter_codex_install.cpp`;
- `tests/test_pack.cpp`;
- `tests/test_cli.cpp` and each new sanitized fixture subtree.

List conditional `core/open` or other consumers individually; anything not listed is OUT and routes before
dispatch. Keep `src/core/manifest/manifest.hpp`, `src/core/manifest/manifest.cpp`, `.github`, sealed docs,
and m-3 count/render surfaces explicitly OUT.

## R2 — producer closure names only two of J's four per-entry caps

Plan lines 40-41 bind only `nodes <= 1024` and `parent depth <= 64`. Addendum-J `J-R2:190-201` locks four:

```text
children per entry               <= 1024
parent-chain depth               <= 64
artifacts per declared node      <= 256
total artifacts across entry     <= 4096
```

All four are per-entry, all refuse the whole entry typed and loud, none truncates. J's calibration rider also
requires the refusal to name both the offending entry and cap; Addendum-12 `A12.4.1` requires a warnings line
for an entry refused over a J cap.

Required revision: assign ownership and RED/GREEN boundary/+1 tests for all four producer caps. If m-1's
implementation supplies any shared helper, name its exact receipt/SHA and the s4 call site; do not silently
delegate or duplicate the contract. The plan must assert zero partial entry emission and the named
entry/cap warning/refusal for each over-cap arm.

## R3 — the “or behind a flag” dependency escape is not in the locked design

Plan lines 105-111 say emission lands after m-1 schema work “or behind a flag the design permits.” Neither
locked design defines that flag; Addendum-12 `A12.9:379-382` instead says no adapter capability change, and
the orchestrator dispatch requires co-sequencing with m-1. A new flag would be a design and scope decision,
not a plan convenience.

Required revision: remove the flag alternative unless an addressed design amendment explicitly licenses it.
Define the actual stop gate and topology: the exact m-1 implementation receipt/SHA that provides
`SessionChild.parent_id` and parser/writer contract, how the s4 branch is based/restacked onto it while
retaining `0db8fdd` as the audit cut, and which tests prove producer+reader closure at the combined tree.
Until that receipt exists, T1/T2 archive emission and the E2E are dependency-blocked, not flaggable.

## R4 — the fixture section misclassifies 4a and delegates three normative oracles back to the design

Plan lines 83-88 group `FX-A12-4` and `FX-A12-4a` as “uncarryable descendant warns.” The locked design says:

- `FX-A12-4` — unreadable descendant produces a warnings line;
- `FX-A12-4a` — PRESENT declared edge disagrees with the artifact's `parent_thread_id` and REFUSES;
- `FX-A12-5` — two executed otherwise-identical variants, absent edge ACCEPTS and consistent edge ACCEPTS;
- `FX-A12-6` — grandchild bytes naming its immediate parent ACCEPT by mapped-node membership;
- `FX-A12-7` — Claude flat enumeration compatibility control.

“Read them at the blob” is correct for design verification but insufficient as an execution plan: the
Implementer must not rediscover test placement, RED symptom, expected outcome, or task order after dispatch.

Required revision: spell out all eight literal keys (`1`, `2`, `3`, `4`, `4a`, `5`, `6`, `7`) with exact
test file, fixture shape, RED command and expected failing assertion, implementation task that greens it,
GREEN command, and commit/checkpoint boundary. Preserve the non-vacuous paired expectations for 5 and keep
4a independent so edge narrowing cannot be lost while the grant arm is killed.

## R5 — the E2E and verification plan needs an exact fixture/command matrix

The plan names the right acceptance outcome but does not map the Codex three-level chain to the separate
Claude filename/layout basis. “Both layouts” and “bare-hex majority” are not executable without exact cases,
and one sample cannot establish a corpus distribution.

Required revision:

- identify the actual-binary Codex `R<-P<-C` fixture and assert all three installed rollouts plus mapped-root
  and immediate-parent references resolve and the leaf marker bytes are readable;
- enumerate sanitized Claude reference-resolution controls for flat bare-hex, flat slug-hex, and nested
  `subagents/<wf>/` layout, with realistic unprefixed reference ids and prefixed child filenames;
- state that these cases cover axes but do not claim corpus representativeness;
- name the sandbox-root assertions and credential-decoy negative assertion;
- provide exact targeted CTest filters, full macOS command, `git diff --check`, and the Ubuntu 24.04
  `linux/amd64` Docker parity command reproducing `.github/workflows/s2-harness.yml` locally;
- keep GitHub CI/CD untouched until all implementation is complete and separately authorized;
- name both A3 anchors and their re-fire command if any anchored collector changes, plus the exact
  base-container comparison trigger.

Also name the isolated worktree/branch, target branch, commit checkpoints, publication hold, and the point at
which D-5.5(a) blast radius is measured.

## R6 — delegated-dispatch lineage is not mechanically resolvable in the local relay root

The plan's exact-file lint passes. A relay-root lint against `.relays/s4` reports, among inherited historical
noise, a target-specific error: this pair-authored `DESIGN_RECORD_KIND: design-doc` plan has no earlier
same-owner DESIGN relay carrying the external m-2 `DESIGN_DOC_ID`. The semantic lineage is independently
verified by the exact PDC blob, the `145249` approval, and the local orchestrator proceed-to-plan relay, but
the current tool cannot resolve that cross-repo design chain. Protocol says an unwaived relay-lint structural
error blocks delegated dispatch.

Required revision/action: route this exact structural cell to `s4.orchestrator-planner` and obtain a
mechanically resolvable local lineage shape or an explicit structural disposition before the pair Planner
issues a token. Do not self-label the pair-authored plan `direct-override`; that record kind is reserved to
operator/orchestrator authors. This finding does not challenge the locked design hash; it blocks only a dirty
delegated-dispatch path.

## Boundary contract review

Writes: transitive Codex `SessionRecord` closure + child-parent carrier; J-valid manifest child edges through
the m-1 schema; installed rollout bytes under recipient-minted ids; warnings/refusals for uncarryable or
over-cap entries.

Reads: Codex rollout `id`, `session_id`, `parent_thread_id`, artifact bytes, J-validated
`agent_sessions[].children[]`, and the recipient-generated mapping over the entry's closed node set.

Target entity: one restored, rooted session tree whose reachable artifacts are present exactly once and whose
root/immediate-parent identities remain distinct.

Downstream consumer: Codex staged reader/installer and actual `biv open` restore flow; Claude controls guard
the adjacent reference-resolution shapes.

Contract: declared edges provide consistency refusals only; membership supplies the acceptance ground;
destinations remain locally minted; all four J producer caps refuse whole-entry typed and loud; no silent
drop/truncation; no live-store or credential access.

Proof required: RED/GREEN E2 for all eight FX-A12 keys, cap boundary/+1 oracles, targeted gate tests, full
macOS + canonical local Ubuntu Docker parity, actual-binary disposable-store E2E, and killing mutations for
non-transitive gather, least-component cycle break, edge-derived grant, both-refused MONO, and silent drop.

No-consumer action: reject/defer the writer change until m-1's reader/schema receipt is integrated; route any
new consumer, flag, manifest, render/count, or consent surface before editing.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — host-minted paths remain authoritative; tests must use sanitized fixtures and prohibit credential collection
- migration/backfill/destructive-write/canonical-data-repair: no — no live-store mutation or migration is in scope
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — restore data is user-invoked; no autonomous downstream act added
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — s4 consumes m-1's PDC-locked manifest schema and the current relay linter cannot resolve the cross-repo design lineage
- user-visible-control-with-materializer/downstream-consumer: yes — restored session identities/files are consumed by Codex resume behavior
- test-runtime-role-mismatch: no — local product and actual-binary/container evidence is required; remote CI is not substituted for local Linux
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — an unlicensed flag and under-specified dependency/scope would force design and scope choices during implementation
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed PLAN-REVIEW presents the shared-schema, downstream-consumer, and lineage triggers
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Closeout

No implementation dispatch may issue from this review. Revise only the bounded PLAN defects above; do not
change the locked Addendum-12/J bytes. Product/test/schema/workflow files, branches, PRs, live stores,
credentials, Actions, merge, publish, deploy, seal, and release were untouched. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only review at bivpak `HEAD fcca4f68774469ff390abfc3166795052ee4e7b3` / product baseline `0db8fdd8424d27aad2c547614e9ebb95621a2794`; verified PDC blobs `3929c9c:154cd87e...` and `e30f845:94b6440c...`; this review relay and one append-only s4 INDEX row are the only seat-authored repository writes and will ride one explicit-path docs-lane commit
RELAY_LINT: exact-file freshness PASS (`OK ...151658.md`); shared INDEX lint reports only inherited line 222 (`20260809-142630` follows `20260809-142708`), while this appended row is monotonic and filename-matched; the incoming PLAN exact-file no-freshness lint passed; relay-root lint disclosed the target-specific cross-repo design-lineage error in R6 plus inherited root noise
FINAL_GIT_STATUS_SHORT: full literal output follows; this seat's writes are the modified s4 INDEX and new PLAN-REVIEW relay, while the remaining untracked paths are pre-existing sibling artifacts
```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MUST-REVISE-20260812-151658.md
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
```

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MUST-REVISE-20260812-151658.md` -> `s4-floor.planner`
- MUST-REVISE R1: enumerate exact s4 scope including `adapter.hpp` child-parent carrier and `pack.cpp` edge emission; hard-outs stay OUT
- MUST-REVISE R2: bind all four J producer caps (1024 nodes, depth 64, 256 artifacts/node, 4096 total) with whole-entry typed refusal + named warning tests
- MUST-REVISE R3: delete the unlicensed flag escape; name exact m-1 implementation receipt/base/restack and combined-tree stop gate
- MUST-REVISE R4: `FX-A12-4a` is edge-inconsistency refusal, not uncarryable-warning; specify all eight keys with exact RED/GREEN files/commands/checkpoints
- MUST-REVISE R5/R6: exact Codex+Claude E2E/verification matrix and branch mechanics; route the cross-repo relay-lint lineage cell before delegated dispatch
- no code/schema/design/PR/Actions/merge/release action; hold ABSOLUTE
