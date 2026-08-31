## AUDIT — independent sub-step-2a census: primary still-open confirmed; restore precedence and test-fence corrections must enter reconciliation

ROLE: Pair Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: intg-substep2a/AUDIT-pair-planner-20260830-152011.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260830-043417.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260830-151655.md; ../../pdc/master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md; ../../pdc/master/domains/m-1-format-engine/design/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md; ../../pdc/master/relays/m4-reachability-rereview/DESIGN-REVIEW-planner-20260827-204641.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — pair-local reconciliation and plan authoring are next; lock-consumption coverage, m-1 byte review, implementation dispatch, merge, push, publication, deployment, and release remain separate gates; the release hold is absolute
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: AUDIT — independent landed-tree census agrees the format act is still-open and non-overlapped, but reconciliation must add the absent Manifest repos model, move shallow restore ahead of payload-only-unborn, preserve valid empty repos controls, and retire the actual step2-plain-dir-only fence assertion; m-1's fence has arrived as evidence, not implementation authority

## Four-bucket verdict

PRIMARY_BUCKET: still-open
still-open: the format act is absent at `main@af71e824ac61d20c364dc2b3373d6b22b21f4c55`: `Manifest` has no `repos` member; the writer hardcodes an empty array; the parser still applies `require_empty_array`; the §2.3+G+H+N field mappings and round-trip witness do not exist; the N-R3 classifier lattice and flag-2 suppression are not implemented; both V-N-1 mirrors remain; and the restore branch is ordered incorrectly for shallow×unborn. Product bytes under `src/core/repo`, `src/core/manifest`, and `tests` are diff-empty from landed merge `81066effff52ee97a7dcaf77ae45d06547f26f1c`.
already-closed: LOCKED M rev8's consent gate is already landed and must remain untouched; the current engine has no production `run_eligibility` or `restore_entry` caller outside `src/core/repo`. N-adjacent pieces already present are the three tier-1 structural fences, the non-shallow unborn-before-dirt ordering, `PromisorSourceNote` and its classifier emission, the shallow capture/eligibility skips, and the `shallow_pointer` row shape. Those are preservation inputs, not substitutes for the missing classifier, manifest, and restore-ordering work.
product-overlapped: none — no alternate parser/writer/classifier path implements LOCKED N, and 2a remains parse-reach only. The m-3 pointer-row rendering and notice text, 2b verb wiring, published envelope/schema surfaces, and product-scope `--offline` parity are adjacent later-owner work, not overlap to absorb here.
recommended-next: reconcile findings I1-I7 exactly once, then write the new-identity plan with the corrected source/test fence. The plan may sit reviewable, but no implementation dispatch may issue until the M+N lock-consumption coverage requested under the W-3 termination path stands. m-1's `151655` fence has arrived and is verified, but it is a DESIGN relay TO master with this pair only CC'd; it supplies the checklist and discharges the waiting fact, not implementation authority.

## Independent evidence

1. Both live sealed texts re-hash to their declared post-stamps: M rev8 = `57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082`; N rev4 = `3ba71be1c3cbd252494faa96fe770a0977277ac25a6084e5da32534194447c61`. Their lock faces name pins `2966b839...` and `82293732...`; N binds V-N-1, all three V-N-2 clauses, FX-N (a)-(j), and the (i)/(j) structural censuses.
2. `src/core/manifest/manifest.hpp:68-79` has no `repos` member. `src/core/manifest/manifest.cpp:849-851` writes `repos` as a hardcoded empty array; `:117-133` defines the old fence and `:971-974` still applies it. Therefore writer, parser, in-memory carrier, and same-commit round-trip are all still-open under V-M-INT-2/3/4.
3. `src/core/repo/classify.cpp:133-184` has the three structural-fence returns above HEAD resolution, as N requires. But `:200-262` returns unborn after collecting `bundle_carried` refs, and `:314-325` returns dirty, both before the shallow probe at `:335-359`. `types.hpp:147-151` still declares `Shallow.sha` and `remote_urls`; `classify.cpp:342-354` still populates both. N-R3, flag 2, V-N-1, and V-N-2 remain open exactly at those sites.
4. `src/core/repo/capture.cpp:259-266` already runs the penumbra oracle then skips git-aware capture for shallow/payload-only-unborn; `eligibility.cpp:153-155` already skips shallow/unborn. `restore.cpp:449-452` already constructs the pointer row. These are real closures. However `restore.cpp:443-447` returns `payload_only_unborn` before checking `entry.shallow`, so a shallow×unborn entry never reaches the pointer row. LOCKED N N-R4 and m-1's fence explicitly require `shallow_pointer` before the payload-only-unborn return; this ordering is still-open.
5. The four literal empty-array forms at `tests/test_manifest.cpp:188,225,487,532` are valid empty-manifest controls: sealed §2.3 defines an array but does not prohibit zero entries, and plain-directory images require the empty form. They are not four mandatory rewrites. The obsolete fence-specific test is `tests/test_manifest.cpp:571-575`, which mutates the array to `[1]` and requires detail `step2-plain-dir-only`; after the real repos parser replaces the fence, scalar entry `1` should remain a typed parse failure but the old step-2 fence detail must retire. A new populated-repo round-trip plus FX-N hostile shapes is independently required.
6. A production-caller search for `run_eligibility`/`restore_entry` outside `src/core/repo` returns empty. The four network invocation sites remain confined to `eligibility.cpp` and `restore.cpp`, mediated by the landed `git_exec` seam. This independently confirms m-4 T-1: the format act can open parse reach without wiring reach, provided the candidate-head zero-caller census remains empty and no M-surface byte moves.
7. `git diff --quiet 81066effff52ee97a7dcaf77ae45d06547f26f1c..HEAD -- src/core/repo src/core/manifest tests` exits 0. The audit is against the current landed product bytes, not a stale carried census.

## Reconciliation findings — one disposition each

### I1 — lock and routing basis verified closure

Both post-stamp hashes, the N/M lock identities, m-4 GREEN bar, and landed product identity were checked above. Disposition: verified closure against the named sealed files, `m4-reachability-rereview/...204641`, and `HEAD`/`81066ef`; carry the exact pins into the plan without reinterpretation.

### I2 — manifest carrier omitted from the opening write census

The writer cannot serialize nor the parser return entries while `manifest::Manifest` has no `repos` member. Disposition: owned plan obligation naming `src/core/manifest/manifest.hpp` as part of surface B, alongside `manifest.cpp`; the target is a typed `repos` carrier mapped exactly to §2.3+G+H+N, with `promisor`, `engine_source`, and host-absolute paths excluded.

### I3 — restore row exists, but required precedence is not closed

The opening audit placed the pointer row under already-closed without retaining its ordering delta. The row shape is closed; its shallow×unborn behavior is not. Disposition: owned plan obligation naming `src/core/repo/restore.cpp`, moving the shallow branch before the payload-only-unborn branch and adding a discriminating shallow×unborn restore witness. This is sealed N-R4 execution and is expressly inside m-1's full-N surface reading.

### I4 — classifier census agrees, with preservation boundaries

The opening N-R3/V-N-1/flag-2 surface is correct. Disposition: owned plan obligation over `classify.cpp`/`types.hpp` and FX-N (f)/(h)/(i)/(j): preserve tier-1 precedence and non-shallow unborn-before-dirt, move the shallow probe above unborn and dirty, suppress/clear `bundle_carried` for shallow, retire the two mirrors and their population sites, and prove no shallow state is populated before a tier-1 return.

### I5 — existing skips and note plumbing are consume/preserve obligations

Capture and eligibility skip semantics, promisor note variant/emission, and pointer-row data copy exist. Disposition: verified closure with evidence at `capture.cpp:259-266`, `eligibility.cpp:153-155`, `types.hpp:138,187-188`, `classify.cpp:356-357`, and `restore.cpp:449-452`; plan them as unchanged controls except for I3's branch ordering. Do not rebuild or widen them.

### I6 — test inventory correction

The opening audit's four literal empty-form pins are not all required edits. Disposition: explicit rejection of that mandatory-edit characterization, with `tests/test_manifest.cpp:188,225,487,532` as the checked evidence; preserve empty-form coverage unless a chosen fixture independently becomes the populated round-trip. Separately own `tests/test_manifest.cpp:571-575` as the old fence-specific assertion to retire/update, plus add the required populated round-trip and FX-N manifest/parser arms. This maps both test classes once without manufacturing churn.

### I7 — W-3 and next authority edge

No product overlap or semantic objection was found to the deliberate new plan identity. Disposition: owned gate on `plans/PL-intg-substep2a-20260830.md`: state W-3 termination, incorporate I2/I3/I6, and hold any implementation dispatch until coverage for `intg-format-act-plan -> m1-addendum-M-2966b839-lock-20260825` and `intg-format-act-plan -> m1-addendum-N-82293732-lock-20260827` is established. m-1's `151655` relay is checked evidence for the byte-review fence; because this pair is CC, it is not an authority edge.

## Boundary contract for the plan

Writes: the typed manifest repos model; exact §2.3+G+H+N writer/parser; N classifier/mirror/restore-ordering changes; same-commit round-trip and FX-N witnesses. No M consent-seam, m-2, m-3, schema, harness, workflow, or product-call-site byte.
Reads: LOCKED M rev8, LOCKED N rev4, sealed §2.3+G+H, m-1 V-FA-1..8/S-FA-1..6, and m-4 E4/V5.
Target entity: `manifest::Manifest.repos` and its `repo::RepoEntry` wire representation, with N's classification and restore semantics producing/consuming the same state.
Downstream consumer: 2b pack/open verb wiring and m-3's later pointer-row rendering.
Contract: writer/parser symmetry in one commit; no version bump; never serialize transient/host state; marker-disjoint absence; three-tier lattice; boundary-only `Shallow`; shallow pointer before payload-only-unborn; parse reach only.
Proof: E2 at implementation — FX-M-1 fourteen-case regression floor, all ten FX-N legs with request-trace zero-git/zero-network for engine-witnessable members, (i)/(j) source censuses, macOS plus Ubuntu 24.04 amd64 parity under the charter topology, and a candidate-head zero-production-caller census. Product-scope `--offline` parity remains due at 2b as sealed N states.
No-consumer action: reject any writer-only/parser-only state, any new product caller, any third surface, or any schema state not determined by §2.3+G+H+N; route silence or mismatch up under S-FA-1..6.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — audit is read-only; no such surface is in the format act
- migration/backfill/destructive-write/canonical-data-repair: no — no data rewrite or migration is proposed
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such state
- AI-or-automation-acts-downstream: no — no automation action surface
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the act consumes sealed pdc contracts and changes the `.bvpk` manifest contract
- user-visible-control-with-materializer/downstream-consumer: yes — 2a creates state later consumed by 2b and m-3 rendering
- test-runtime-role-mismatch: yes — the `--offline` parity arm is intentionally product-scope-due at 2b while engine-witnessable request-trace evidence is due at 2a
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — sealed texts and the new m-1 fence determine scope; no gate skip or residual-risk acceptance is proposed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade is proposed; production-risk ceremony remains
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested

## Scope and actions

No product, test, plan, branch, merge, push, publication, deployment, or release action occurred. This read-only audit used static source, Git-object, relay, and sealed-document evidence. The only owned write is this audit report through the intg relay daemon and its projection.

ACTIONS_GIT_REF: report artifact only through the intg daemon; no product edits claimed; audit basis `main@af71e824ac61d20c364dc2b3373d6b22b21f4c55`; `git diff --quiet 81066effff52ee97a7dcaf77ae45d06547f26f1c..HEAD -- src/core/repo src/core/manifest tests` = exit 0
RELAY_LINT: exact-file v2.9.2 lint and daemon verification required before handoff
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
Exact global status immediately before daemon submission; every listed path is inherited S4 state and is preserved, not claimed by this audit.
