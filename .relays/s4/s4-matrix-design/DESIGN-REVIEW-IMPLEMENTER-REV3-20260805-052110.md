## DESIGN RE-REVIEW — Arm 1 integration design rev3

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-design-review-rev3
PARENT_DISPATCH_ID: s4-matrix-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — option 1 is decided; the pair must fold the current upstream Addendum G semantics after its renewed review, without inventing another local choice
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_REVIEW_VERDICT: must-revise
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-design/DESIGN-PLANNER-20260805-045526.md
RELAY_PATH: .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-052110.md
BASE: af2f8be1bd433bec1839a31779c0017041baf84d

Verdict: MUST-REVISE. The option-1 authority is valid and rev3 correctly removes the unshipped fence, but the reviewed design is already stale against its governing Addendum G. The design at `af2f8be` folds G rev1 (`3a9a09e`, 2026-08-05 04:54:14-07:00); G advanced through two material review folds to rev3 at `c32de412776f6c2160d9d0aba529fa3e612bd24b` (2026-08-05 05:15:10-07:00, SHA-256 `b507d982c0d15aa4603040f422f1fe82f360a58a39db6c26cedb0f87883e2ee6`). Rev3 is still awaiting its m-1 Implementer re-review and VP verification. Approval cannot freeze the superseded rev1 semantics.

## Required revisions

### N1 — Bind the class to G rev3’s any-ref / zero-ref semantics

The submitted design calls step 4 “commits on a non-HEAD ref,” claims commits make `bundle --all` valid, cites G rev1, and names `refs/notes/*` as a non-carried rationale (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:76-79@af2f8be`). Its actual predicate, `for-each-ref` non-empty, already matches G rev3’s chosen arm; the surrounding semantics do not.

G rev3 explicitly widens the class to ANY ref of ANY object type and narrows payload-only to ZERO refs, preserving C3’s blob/annotated-tag arm; it withdraws the notes rationale and retains sealed `refs/stash` as the non-carried witness (`../pdc/master/domains/m-1-format-engine/design/2026-08-05-ADDENDUM-G-unborn-head-eligibility.md:47-61,95-106@c32de41`).

Required fold: rename steps 3/4 and all outcomes from zero-commit/with-commits to zero-ref/any-ref where G governs, cite G rev3, state bundle validity from ref presence rather than commit presence, remove the notes claim, and add the non-commit tag positive behavior. Criterion 5 must bind the reviewed G revision rather than rev1.

### N2 — Freeze the complete parser-observable license, not only rev1 legs c/d/e

D3 currently promises bidirectional validation but enumerates only FX-G-1 legs c/d/e (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:101-104@af2f8be`). G rev3’s invariant is stronger and fully parser-observable: for an unborn entry, recorded bundle iff `eligibility.result: unborn-head` (plus null sha/full); no bundle iff no eligibility object AND `local_refs[]` absent-or-empty; wrong-head-state, wrong/missing result, result-without-bundle, and payload-only-with-carried-refs are all schema-invalid (`../pdc/master/domains/m-1-format-engine/design/2026-08-05-ADDENDUM-G-unborn-head-eligibility.md:62-82@c32de41`, legs c/d/g/e/j).

Required fold: state both equivalences and every constrained field in D3; name parser negatives g and j alongside c/d/e. A hostile no-bundle/no-eligibility/non-empty-`local_refs[]` manifest must be rejected before apply, never silently ignored.

### N3 — Replace the now-forbidden source-ref materialization instruction

D4.2 still directs the engine to “materialize objects/refs from the extracted bundle” and still uses `refs/notes/*` in the discriminator rationale (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:138-140@af2f8be`). G rev3 replaced that exact wording after m-1 review: the special branch imports the bundle’s OBJECT CLOSURE without installing any source ref, then installs only manifest-carried `local_refs[]` and the recorded HEAD symref; `refs/stash` must remain absent while its pack-time C3 advisory survives (`../pdc/master/domains/m-1-format-engine/design/2026-08-05-ADDENDUM-G-unborn-head-eligibility.md:95-127@c32de41`).

Required fold: use the singular object-closure instruction in D4.2, state that non-carried source refs are never installed, remove the notes rationale, and pin the stash-absent/advisory-survives postcondition.

### N4 — Carry the current ten-leg FX-G-1 oracle

D6 carries engine legs a/b/f and parser legs c/d/e only (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:205-213@af2f8be`). G rev3’s ten-leg matrix adds the load-bearing stash-only cardinality witness (b2), result-without-bundle negative (g), lightweight and annotated non-commit-tag positive (i), and payload-only/non-empty-`local_refs[]` negative (j) (`../pdc/master/domains/m-1-format-engine/design/2026-08-05-ADDENDUM-G-unborn-head-eligibility.md:137-182@c32de41`). Those are exactly the legs that caught the rev1/rev2 ambiguities.

Required fold: map all ten current legs into engine/schema/harness ownership; do not summarize them back down to the superseded six-leg set.

## Fold and acceptance grading

- R1 shallow+promisor: PASS, unchanged by rev3.
- R2 upstream decision: AUTHORITY PASS; SEMANTIC FOLD FAIL on N1-N4.
- R3 phase-exact ancestry mapping: PASS, unchanged.
- R4 stage lifecycle/trigger: PASS, unchanged.

Acceptance criteria:

1. Traceability: FAIL — the design cites and implements superseded G rev1 bytes.
2. One process-safety implementation: PASS.
3. Four-surface schema act: PARTIAL — surface ownership is correct; N2 omits current license constraints and negative rows.
4. Existing staging only: PASS.
5. Ordered/total classification: FAIL — the executable predicate points the right way, but its named class, object-type semantics, restore action, and locked revision are stale.
6. Manifest-driven repo phase/lifecycle: PASS.
7. Symlink ancestry containment: PASS.
8. Exact D5 membership and phase mapping: PASS; the obsolete fence remains deleted.
9. Harness/tolerance: FAIL on N4’s omitted current ruling legs.
10. DR-3 ledger: PASS AT DESIGN SHAPE; the current G legs must enter its add rows.
11. Sequencing/ownership: PASS — implementation remains gated on F and G reviews closing.

## Re-review gate

Rev4 is reviewable after the current Addendum G revision receives its renewed m-1 review (or any resulting successor is filed), and the design binds that immutable revision while folding N1-N4. R1/R3/R4 need no further change. Addendum F+G review closure remains a hard schema-act predecessor, and the absolute release hold remains unchanged.

No design-doc, source, test, harness, schema, build, branch, or host-probing action was taken by this review seat. Only this review relay and its append-only INDEX row are claimed.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-052110.md and its .relays/s4/INDEX.md row; explicit paths only; commit SHA in the repository record; no product or design-doc edit
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 D .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-051848.md
?? .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-052110.md

RELAY_LINT: OK — author-side freshness lint and shared INDEX lint

CARRY LIST:
- .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-052110.md -> s4-matrix.planner
- Addendum G rev3 renewed review state -> s4.orchestrator-planner (CC context; Planner carries it in the next hold/fold report)
