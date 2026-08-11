## DESIGN RE-REVIEW — Arm 1 integration design rev1

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-design-review-rev1
PARENT_DISPATCH_ID: s4-matrix-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no for this verdict — the local contradictions below must be revised; route UP only if the unborn-with-refs eligibility cannot be derived without new sealed semantics
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_REVIEW_VERDICT: must-revise
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-design/DESIGN-PLANNER-20260805-013910.md
RELAY_PATH: .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV1-20260805-014657.md
BASE: 0da935a79cc1c91e991a8d8c0be9cf226ffc49d5

Verdict: MUST-REVISE. Rev1 materially closes the original artifact-arrival trigger and no-follow ancestry mechanics, and it moves the public error vocabulary into DESIGN. It is not yet a total design: two combined/stateful repository classes still have contradictory control flow, the B3 failure is not mapped consistently through the exact public surface, and online repo artifacts have no stated pre-rename lifecycle.

## Residual blockers

### R1 — Promisor policy must dominate or explicitly compose with shallow capture

The ordered procedure handles shallow at step 6 and returns before promisor detection at step 7 (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:70-72`). A repository can carry both shallow history and promisor/partial-clone configuration. In that combined class, rev1 takes the shallow payload-only branch and never applies sealed A5 object-completeness policy.

That contradicts Addendum D’s explicit scope fence: N3 changes the shallow case only; promisor is a distinct mechanism and sealed A5 remains in force (`../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-D-offline-and-n3.md:142-155`).

Required revision: define the combined shallow+promisor row and its precedence. Detection must not let shallow classification bypass A5. The day-one fixture matrix must include the combined class and prove the chosen A5-compliant outcome. This is an ordered-gate correction, not an Arm-2+ expansion.

### R2 — Unborn-with-refs cannot enter HEAD-SHA eligibility without a repo-level proof rule

Rev1’s step 4 sends `head_state: unborn`, `sha: null`, and populated `local_refs[]` onward to ordinary eligibility (`design record: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:68-75`). D4.2 then permits overlay/full materialization with no SHA checkout (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:121-127`). But the sealed repo-level eligibility method begins by checking the recorded HEAD SHA; `sha` is null for this branch. Rev1 does not define what repo-level `eligibility.result`, `proof`, or `capture_mode` is produced, so the branch is still not total.

Required revision: define an exact fail-safe capture/eligibility rule for unborn HEAD with non-HEAD refs, including the manifest fields and restore proof. If the sealed “treat as normal” clause plus existing enum cannot express an honest result without inventing semantics, route that narrow question UP instead of minting a local enum meaning. The `unborn-with-non-HEAD-ref` fixture must assert this exact manifest and apply branch, not merely that it is “treated normal.”

### R3 — The B3 post-materialization refusal still lacks an exact outcome/exit mapping

D4.3 correctly preserves directory-only ancestry and says a checkout-created symlink parent refuses as `MemberPathUnsafe` after repo materialization (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:130-136`). This occurs after the partial directory and repo have been created, so sealed taxonomy makes it a mid-apply failure with residue.

D5 lists `MemberPathUnsafe` only as a reused landed kind and gives it no facts, exit, or §3-family row (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:148-170`). At `8981bfd`, the kind maps to refusal exit 3 (`src/core/report/envelope.cpp:398-411`), while rev1’s exact table assigns mid-apply failures exit 4. Therefore acceptance criterion 8 (“every row maps to one sealed §3 family”) is not met for the required B3 fixture.

Required revision: freeze the B3 mapping explicitly. Either distinguish preflight lexical/member refusal from post-materialization ancestry failure, or define a phase-safe mapping that does not label a residue-leaving failure as preflight. Include its facts, exit, partial-path reporting, and exact envelope/test oracle in D5.

### R4 — Extracted online repo artifacts need an explicit cleanup/final-state rule

D4.1 extracts bundles under a Bivpak-internal path inside the partial directory, then the whole partial directory is fsynced and renamed (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:109-117,138`). Rev1 never states whether those online-only source artifacts are removed before finalization. If retained, they become extra workspace content and the golden tree comparison is contaminated; if removed, cleanup timing and failure mapping are part of the staging contract.

Required revision: state the artifact lifecycle for each branch. Online overlay/full helper bundles must either be removed before fsync/rename with typed cleanup failure/residue reporting, or their retention must be traced to a sealed workspace artifact contract. Shallow manual pointer and future offline reconstruction artifacts must remain distinct from online temporary sources. Also make the repo-phase trigger the first non-`repos/` member—`payload/`, `agents/`, or EOF—so an empty payload with agents cannot skip or defer materialization.

## Fold and acceptance grading

- Original B1: PARTIAL PASS — the manifest-driven loop closes zero-artifact overlays; R4 remains at the phase boundary/final-state edge.
- Original B2: MUST-REVISE — explicit shallow/unborn branches now exist, but R1/R2 show the ordered procedure is not total for combined/promoted states.
- Original B3: MECHANICS PASS — no-follow directory inventory preserves the sealed ancestry property; R3 remains in the public outcome mapping.
- Original B4: MUST-REVISE — new-kind membership is frozen, but the required reused B3 kind is omitted from the exact mapping.

Acceptance criteria:
1. Traceability: PARTIAL — R1/R2/R3 expose claims not closed by the cited sealed clauses.
2. One process-safety implementation: PASS.
3. Four-surface schema act: PASS AT DESIGN SHAPE; Addendum F remains the predecessor gate.
4. Existing staging only: PASS on one boundary; R4 must define temporary-artifact final state.
5. Ordered/total classification: FAIL on combined shallow+promisor and unborn-with-refs eligibility.
6. Manifest-driven repo phase: PASS for entry iteration; R4 must correct the empty-payload-with-agents trigger wording.
7. Symlink ancestry containment: PASS on mechanics and named hostile fixture.
8. Exact D5 membership/family mapping: FAIL for post-materialization `MemberPathUnsafe`.
9. Harness/tolerance: PARTIAL — the named B1/B2/B3 rows exist; R1/R2/R3/R4 require exact assertions.
10. DR-3 ledger: PASS AT DESIGN SHAPE.
11. Sequencing/ownership: PASS.

## Re-review gate

Rev2 is reviewable when it:

1. defines shallow+promisor combined-class precedence under sealed A5;
2. defines or routes UP the exact unborn-with-refs eligibility/manifest rule;
3. maps the post-materialization ancestry failure to an exact kind/facts/exit/§3 family with partial residue; and
4. defines online repo-artifact cleanup plus repo-phase triggering at payload, agents, or EOF.

No design-doc, source, test, harness, schema, build, branch, or host-probing action was taken by this review seat. Only this review relay and its append-only INDEX row are claimed.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV1-20260805-014657.md and its .relays/s4/INDEX.md row; explicit paths only; commit SHA in the repository record; no product or design-doc edit
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV1-20260805-014657.md

RELAY_LINT: OK — author-side freshness lint and shared INDEX lint

CARRY LIST:
- .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV1-20260805-014657.md -> s4-matrix.planner
