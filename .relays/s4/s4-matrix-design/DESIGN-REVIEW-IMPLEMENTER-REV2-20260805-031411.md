## DESIGN RE-REVIEW — Arm 1 integration design rev2

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-design-review-rev2
PARENT_DISPATCH_ID: s4-matrix-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — upstream m-1/orchestrator authority must resolve whether the sealed A6 unborn-with-refs class receives an honest eligibility result or an explicitly authorized fence; this pair cannot amend that behavior locally
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_REVIEW_VERDICT: human-decision-required
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-design/DESIGN-PLANNER-20260805-015241.md
RELAY_PATH: .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV2-20260805-031411.md
BASE: ac92424f9b824bcf263e5b4c3d99190bb7ebef71

Verdict: HUMAN-DECISION-REQUIRED. Rev2 closes R1, R3, and R4. Its diagnosis of R2 is also correct: the sealed manifest enum has no honest repo-level `eligibility.result` for an unborn HEAD whose commits live only on non-HEAD refs. The proposed transitional refusal is not locally approvable, however, because it changes the sealed class behavior rather than merely representing it.

## Required upstream decision — R2 eligibility cell versus sealed A6 behavior

Sealed Addendum A requires an unborn-HEAD repository with commits on a non-HEAD ref to be treated as normal (`../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-A-git-object-availability.md:180-190`). The orchestrator design dispatch independently binds this design to Arm-1 single-clean-repo end-to-end under sealed semantics and makes any sealed-doc amendment an UP-route, not a pair-local decision (`.relays/s4/s4-matrix-design/DESIGN-ORCHESTRATOR-PLANNER-20260804-235022.md:18-27,52-56`).

Rev2 instead routes that class to `RepoUnbornRefsUnsupported` at design lines 76-85, freezes the new refusal in D5 at lines 168-181, and makes the day-one fixture assert the fence at line 209. It also rewrites acceptance criterion 5 to accept “ruled or typed-fenced” at line 250. This is mechanically total, but it is not the sealed “treat as normal” behavior; a typed transitional error does not itself grant authority to defer a required class.

The underlying ambiguity is real. Manifest §2.3 closes `eligibility.result` over `proven | unknown-tip | no-remote | sha-unpushed | remote-unreachable | offline-declared`, while the eligibility method begins from the recorded HEAD SHA; for `head_state: unborn`, that SHA is null (`../pdc/master/domains/m-1-format-engine/design/2026-07-02-manifest-format.md:137-147,168-188`). Rev2 correctly refuses to invent a local enum meaning and otherwise derives a fail-safe full-capture/apply branch.

Required decision from the upstream semantic owner:

1. define the honest repo-level eligibility representation for this sealed A6 class and authorize the designed full-capture/no-SHA apply branch; or
2. explicitly authorize a bounded `RepoUnbornRefsUnsupported` fence despite A6’s current “treat as normal” text, including its scope and flip gate.

After that ruling, the Planner must cite it in D2/D5/D6/criterion 5 and either activate the already-designed branch or retain the expressly authorized fence. No new local design alternative is requested.

## Residual-fold grading

- R1 shallow+promisor composition: PASS. Promisor is now detected as a property before routing, every later git invocation is constrained by `GIT_NO_LAZY_FETCH=1`, shallow remains payload-only, and the combined fixture asserts zero fetch activity (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:67-83,209`; `../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-D-offline-and-n3.md:142-155`).
- R2 unborn-with-refs: UPSTREAM HOLD. The fail-safe capture/apply mechanics are coherent, and routing the inexpressible enum cell UP was correct; the interim refusal still needs authority because it contradicts the sealed behavioral sentence.
- R3 phase-exact ancestry failure: PASS. Plan-time lexical/tar ancestry remains `MemberPathUnsafe` refusal/3; checkout-created ancestry becomes `MemberAncestryUnsafe` failed-mid-apply/4 with exact facts, partial residue, and hostile oracle (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:143-181,209`; `../pdc/master/domains/m-1-format-engine/design/2026-07-02-restore-apply-contract.md:121-140,157-170`).
- R4 stage lifecycle and trigger: PASS. The repo phase triggers at payload, agents, or EOF, iterates the manifest, removes online `.biv-stage` before payload/seal, and maps cleanup failure to typed mid-apply residue (`docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md:118-130,179,209`; `../pdc/master/domains/m-1-format-engine/design/2026-07-02-restore-apply-contract.md:60-70`).

## Acceptance grading

1. Traceability: HOLD — all local folds trace, but the R2 fence has no governing authority and conflicts with A6.
2. One process-safety implementation: PASS.
3. Four-surface schema act: PASS AT DESIGN SHAPE; Addendum F remains the hard predecessor.
4. Existing staging only: PASS.
5. Ordered/total classification: MECHANICALLY PASS, SEMANTIC HOLD — the class is typed, but its refusal is not authorized under sealed A6.
6. Manifest-driven repo phase, trigger, and lifecycle: PASS.
7. Symlink ancestry containment: PASS.
8. Exact D5 membership and phase-consistent mapping: PASS except that membership of `RepoUnbornRefsUnsupported` is held on the upstream decision.
9. Harness/tolerance and exact fixture rows: PASS AT DESIGN SHAPE, with the R2 fixture branch held on the same decision.
10. DR-3 ledger: PASS AT DESIGN SHAPE.
11. Sequencing/ownership: PASS.

## Re-review gate

This review can return to a closed `approve` verdict after the upstream ruling is filed and the design cites/folds that exact ruling. R1/R3/R4 require no further revision. The absolute release hold remains unchanged.

No design-doc, source, test, harness, schema, build, branch, or host-probing action was taken by this review seat. Only this review relay and its append-only INDEX row are claimed.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV2-20260805-031411.md and its .relays/s4/INDEX.md row; explicit paths only; commit SHA in the repository record; no product or design-doc edit
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV2-20260805-031411.md

RELAY_LINT: OK — author-side freshness lint and shared INDEX lint

CARRY LIST:
- .relays/s4/s4-matrix-design/DESIGN-REVIEW-IMPLEMENTER-REV2-20260805-031411.md -> s4-matrix.planner
- R2 eligibility-cell / A6 fence authority question -> s4.orchestrator-planner via the Planner's design-complete-or-hold report
