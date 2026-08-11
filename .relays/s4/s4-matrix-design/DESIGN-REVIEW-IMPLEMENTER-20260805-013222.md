## DESIGN REVIEW — Arm 1 integration design rev0

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-design-review
PARENT_DISPATCH_ID: s4-matrix-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the required revisions apply already-sealed semantics; no sealed-design disagreement is raised by this review
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_REVIEW_VERDICT: must-revise
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-design/DESIGN-PLANNER-20260805-001317.md
RELAY_PATH: .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-20260805-013222.md
BASE: a5fb475f6808d3ce3fa5ec63e9b7d5d40bdacd88

Verdict: MUST-REVISE. The module split, one-runner decision, four-surface schema act, existing-staging ownership, one-harness direction, DR-3 ledger home, and reconcile sequencing are sound. Four control-flow/contract gaps block a design lock because rev0 does not yet show a safe and total Arm-1 apply path for every class it claims to accept.

## Blocking revisions

### B1 — Repository materialization must be manifest-driven, not bundle-arrival-driven

The design says the streaming apply “clones each repo as its bundle arrives” (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:104-106`). That cannot materialize a clean overlay repository whose HEAD and all local refs are remote-proven: the sealed entry permits `bundle: null` and absent `local_refs_bundle` (`../pdc/master/domains/m-1-format-engine/design/2026-07-02-manifest-format.md:149-162,183-192`), so that valid repo can have zero `repos/<id>/…` archive members. There is no arrival event to trigger its clone.

Required revision: define a manifest-driven repository phase inside the existing partial tree. It may first extract/account the complete `repos/` artifact area, but it must then iterate every manifest repo entry and dispatch by entry state before payload begins. The phase boundary must cover the zero-artifact overlay case and must prove that all manifest-required repo artifacts were accounted before any clone/fetch uses them. Preserve the single staging/finalization mechanism.

### B2 — Shallow and unborn repositories need explicit apply branches and precedence

Rev0 accepts shallow and unborn repositories (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:72-75`), but its apply chain has only overlay-clone and full-bundle-clone branches (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:108-112`). Neither branch applies:

- A shallow repo deliberately stores no cloneable bundle. Sealed Addendum D requires working-tree payload plus shallow metadata, an honest manual/re-clone history reconstruction pointer, and no dead bundle (`../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-D-offline-and-n3.md:124-140,163-169`).
- A zero-commit unborn repo is payload-only; sealed Addendum A requires no bundle, an equivalent restored tree, and optional re-init only when the recorded config subset exists (`../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-A-git-object-availability.md:170-195`).

The pack-side gate is also ambiguous: “any staged/unstaged/untracked dirt” refuses at `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:68`, while the fresh unborn case at `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:74` necessarily may contain untracked or staged files. A table without precedence can route the same repo to refusal or payload-only capture.

Required revision: add explicit, ordered classification and apply branches for `unborn` and `shallow` before the ordinary dirt/full/overlay branches. State their payload population, whether a git repository is materialized, their report/outcome rows, and their day-one fixtures. The unborn rule must distinguish zero-commit HEAD from the Addendum A case where commits exist on a non-HEAD ref.

### B3 — Do not weaken no-symlink-traversal containment at a materialized repo root

Rev0 proposes that a later payload member is accepted when its path is merely “inside a materialized repo root” (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:114`). That blanket predicate is weaker than the sealed rule: no member write may traverse a symlink component, followed by a final canonical containment assertion (`../pdc/master/domains/m-1-format-engine/design/2026-07-02-restore-apply-contract.md:121-140`). A checkout can create symlink parents inside its worktree; root membership alone does not prove a later penumbra member’s ancestry is directory-only.

The landed defense is deliberately ancestry-specific: `src/core/open/open.cpp:443-476@8981bfd` accepts a parent only when the created map records that exact prefix as a directory; symlink parents are not traversable. The proposed shortcut would remove that property for repo subtrees.

Required revision: retain no-follow ancestry validation for every post-checkout payload write. Define how materialized repository directories enter the trusted ancestry set without admitting symlinks—e.g. a no-follow directory inventory or dirfd-relative walk—and retain the final canonical containment assertion. Add a hostile fixture where checkout creates an in-repo symlink parent and a declared payload member attempts to write beneath it; the member must be refused without an out-of-root write.

### B4 — Freeze the public error/outcome membership in DESIGN, not PLAN

Rev0 labels D5 a “design-level set” but defers exact membership to PLAN (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:120-128`). These kinds feed the closed `ErrKind` enum, exit mapping, JSON schema, envelope oracle, and transitional flip ledger; changing membership changes public behavior, not implementation sequencing. The landed coupling is visible at `src/core/support/error.hpp:9-34@8981bfd` and `src/core/report/envelope.cpp:381-414@8981bfd`.

Required revision: make D5’s Arm-1 error/advisory/outcome membership exact in the design, including the new shallow/unborn results from B2 and the error/facts shape for B1/B3 failures. PLAN may enumerate edit/test steps but must not choose public semantic membership. Preserve the sealed restore outcome families and show the mapping from each Arm-1 branch/failure to exactly one family.

## Acceptance-criteria grading

1. Semantic traceability: PARTIAL — most claims are cited, but B1/B2/B3 do not trace to a complete safe apply path.
2. One process-safety implementation: PASS — generic runner plus thin probe/git adapters; probe contract/tests and the law-comment re-scope are explicit (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:14-50`).
3. Four-surface schema act: PASS AT DESIGN SHAPE — all four reconciled surfaces are present and Addendum F remains a hard predecessor (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:88-100`). Implementation remains gated on Addendum F actually landing.
4. Existing staging only: PASS on ownership, MUST-REVISE on safety mechanics — there is one partial-tree finalization path, but B3 weakens its member containment.
5. No silent-loss path: FAIL — artifactless overlay, shallow, and unborn control-flow gaps in B1/B2 leave accepted classes without total apply behavior.
6. One harness/tolerance surface: PASS with required fixture additions from B2/B3; the comparator consumes declared policies and fixture git identity/time are pinned (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:130-137`).
7. DR-3 ledger: PASS AT DESIGN SHAPE — both audits’ flip/retain/add populations and replacement-oracle rule are named (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:139-144`). The ledger must still be materially enumerated and frozen before any implementation dispatch.
8. Sequencing/ownership: PASS — Addendum F, matrix schema act, floor adjacent act, and separate rebased integration acts match the reconcile (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:161-165`).

## Re-review gate

Rev1 is reviewable when it:

1. makes repository materialization manifest-driven and total for zero-artifact overlay entries;
2. adds ordered shallow/unborn pack and apply branches with report rows and fixtures;
3. preserves no-symlink ancestry containment inside materialized repositories and adds the hostile regression fixture; and
4. freezes the exact Arm-1 public error/advisory/outcome set in DESIGN.

No design-doc, source, test, harness, schema, build, branch, or host-probing action was taken by this review seat. Only this review relay and its append-only INDEX row are claimed.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-20260805-013222.md and its .relays/s4/INDEX.md row; explicit paths only; commit SHA in the repository record; no product or design-doc edit
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-20260805-013222.md

RELAY_LINT: OK — author-side freshness lint and shared INDEX lint

CARRY LIST:
- .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-20260805-013222.md -> s4-matrix.planner
