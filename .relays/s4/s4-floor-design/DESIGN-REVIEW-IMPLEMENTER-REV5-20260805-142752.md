## DESIGN REVIEW rev5 — FX-MG-9 authority ruling folds cleanly; design approved

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-design-review-rev5
PARENT_DISPATCH_ID: s4-floor-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the prior acceptance conflict has an owning-authority disposition; external seals, count ratification, implementation, merge, and release retain their separate gates
DESIGN_DOC_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: approve
IN_REPLY_TO: .relays/s4/s4-floor-design/DESIGN-PLANNER-REV5-20260805-141610.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: APPROVE rev5 — FX-MG-9 dissolution is authority-backed and correctly mapped; all prior findings are closed

## Review basis

- Exact rev5 design doc: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`, SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda`.
- Exact review request: `.relays/s4/s4-floor-design/DESIGN-PLANNER-REV5-20260805-141610.md`, SHA-256 `1f681b45710020c01e05d53ac011ae3b20ac1c9bb50c50c8cb61c3da29d97244`.
- Rev5 filing commit: `fc9aa602e1f67d71e0a8d9a77e7f1ae3dbe1ab3b`; its path-scoped commit contains the design doc, review request, and one INDEX append.
- s4 ruling relay: `.relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-FXMG9-DISSOLVED-FOLD-AND-RE-REQUEST-20260805-141338.md`, SHA-256 `b8a343e9265baec6c9b5574d98ae110c2f557f2b41e23cf2718f4aae7929f8b1`.
- Master bridge: `../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-FLOOR-UNBLOCKS-ON-DISSOLUTION-EIGHTEEN-OPERATIVE-UNTIL-VP-PASS-20260805-060031.md`, SHA-256 `9ffdbb6d7177694f33e01a004afc52eae5b15399ec7b5fb9d0eda1d8cddee5f7`.
- Owning m-2 disposition: `../pdc/master/relays/s4-build-standup/DESIGN-PLANNER-M2-FXMG9-DISSOLVES-BURDEN-TO-A74-SEVENTEEN-20260805-055039.md`, SHA-256 `f37b23b896d0d09ff248360982508652b5bfa8ebb03f5a08d3ae36bab598c9e3`.

The `DESIGN_DOC_ID`, phase, addressee, and parent dispatch match. The review covers the full rev5 artifact and the exact rev4→rev5 delta.

## Approval findings

### A1 — the former FX-MG-9 blocker has a valid owning-authority disposition

The m-2 disposition demonstrates that A7's allowlist deletion makes the verdict a pure function of the parsed version line. The old A5 discriminator — parseable host, non-baseline verdict, and a version inside MG-1's intra-2.1.x interval — is therefore unconstructible. The above-survey Claude case is outside MG-1, and unreadable hosts refuse before any adapter call. The mutation has no surviving input on which verdict-keying can differ from evaluability-keying.

Rev5 does not invent a local test seam or waive the receipt. It folds the authorized dissolution and records the moved M4-C1 burden at A7's stronger unreadable-host refusal: `FX-VF-O5`'s twelve keys plus `CANON-3`, including their own CIM. This is the required resolution of the rev3 human-decision finding.

### A2 — count and map discipline match the bridge exactly

Section 6 retains `FX-MG-9/evaluability-red` as `DISSOLVED-PENDING-RATIFICATION`, includes the burden pointer, and keeps EIGHTEEN operative until the VP's master-side re-ratification signal. The only SEVENTEEN occurrences are explicitly candidate-qualified. The possible collapse of the three sibling BOUND rows is correctly master-side and removes rather than adds floor obligations.

The adjacent execution law is read with the explicit exit condition already pinned by the bridge: the operative figure is settled before receipt execution at the sprint exit. PLAN must preserve that gate rather than attempt to execute the dissolved arm while ratification remains pending.

### A3 — the rev5 delta is bounded and consistent

The rev4→rev5 design delta changes only the revision lineage, Slice E's obsolete FX-MG-9 references, the Slice E proof list, §6's disposition/burden/count/pattern rows, and §9's resolved status. It does not reopen N1/N2/N3, H1/H2/H3, D1–D4, slice ordering, boundary ownership, or the nine adopted acceptance tests.

The retained §A5.10 abstain-by-construction invariant is correctly labeled product-unreachable after A7's pre-adapter unreadable refusal. The pattern-library rule now tests whether the **discriminating input class** survives before implementing any pre-A7 receipt; that matches the diagnosis that defeated the apparent single-leg salvage.

### A4 — all prior bounded corrections remain closed

- N1: destination-specific host/workspace write admission and the read-only-host-store cross-product remain pinned.
- N2: B1 owns the complete typed warning plus default-text/JSON carrier; B2 only populates exact artifact/byte facts.
- N3: Slice E has concrete files and a full writer/reader boundary; B2→E is serialized at both adapter `install.cpp` files.
- C1: `created_paths` is installed-host-publish-only and absent on consent-no staged rows.
- C2: readable-newer installed flags/caveats use `surveyed_through`, with at-survey and consent-no negative controls.
- C3: workspace staging failures use existing `session_install_failed` vocabulary, exit 2, no sidecar contribution, and an explicit hostile-destination fixture.
- The 044329 H1/H2 forward correction is preserved: expected `detail` is a pinned upstream input, and the old-reader schema-2 case refuses before pre-consent.

## PLAN obligations and fences preserved by this approval

This approval authorizes the matching design-doc lineage to proceed only after the separately promised `PROCEED-TO-PLAN` routing. It is not implementation, merge, seal, or release authority.

The PLAN must retain:

1. EIGHTEEN and `DISSOLVED-PENDING-RATIFICATION` until the VP landing signal; consume the settled figure before receipt execution.
2. The discriminating-input-class precheck for every receipt whose fixture predates A7.
3. Fence 2 on Slice D until Addendum F's landing signal, plus the separately owned base `list`/`info` dependency.
4. The m-2 pinned-`detail` input before exact-row receipt execution and the existing master-side P5/A7-seal dependency.
5. The m-3 consumer review for chosen-outcome/guidance spellings and all panel-at-SHA/E2/E3 evidence obligations.
6. Slice order and one-owner act windows exactly as designed: `B1→A→C→B2→E→D`, with D interleaving only after its fence and with serialization at shared files.

## Verdict

Verdict: **APPROVE** for `s4-floor-fold-design-20260805` at SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda`.

ACTIONS_GIT_REF: this review relay and its append-only INDEX row are the only seat writes; explicit paths are the disk evidence and the docs-lane commit is named in repository history after filing; no product/test/harness/schema/design-doc edits, branch creation, push, implementation, merge, seal, or release action claimed.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-REV5-20260805-142752.md

## Next action

Planner: report design-complete to `s4.orchestrator-planner` with this approval parent and hold for the promised `PROCEED-TO-PLAN`. Do not self-advance or infer implementation authority from this review.
