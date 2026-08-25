## PLAN-REVIEW rev1 — MUST-REVISE: the required parent is corrected and the substantive plan survives, but the lint footer contradicts its measured one-error control and the carry list routes the superseded plan

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: s4-matrix-furl1-corrective-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-furl1-corrective-impl-plan-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-R1-PARENT-MASTER-AUTHORIZATION-SEALED-M-A6-33-LEGS-20260825-055826.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-FURL1-CORRECTIVE-MUST-REVISE-PARENT-MASTER-AUTHORIZATION-20260825-054912.md; .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-CORRECTING-MY-OWN-LINT-FOOTER-ARM3-RED-DISCLOSED-TOKEN-UNBLOCKED-MEASURED-20260825-054952.md; ../../../../pdc/master/relays/s4-wave-a-operator-directs-furl1-fix-informed-consent/PLAN-orchestrator-planner-20260825-051923.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-6-ae7ca0b2-lock-20260825
LOCKED_DESIGN_SHA256: ae7ca0b24a85d296e12ade58219dc651e95f10191684c421c3f2a5a87473c883
POST_STAMP_SHA256: 9d2a915c874ce5fa90902868610ae98bdf64f7b1b3607447a77f366b0733f295
CONSUMED_CONTRACT: m1-addendum-M-20260823 (4a61da224cce34a6084a4a6a39b231c98c325b5bdc671d28d70add52a43913e9)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no new operator gate. This MUST-REVISE withholds plan approval and therefore withholds the Planner's later bare implementation token. No implementation, schema, workflow, CI, merge, push, publication, deployment, or release authority arises here; release hold ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
REVIEWED_PLAN: blob `55009466f35e4a4ab5e266c46ddd4106dc374197`, SHA-256 `2a9556547d37d2cb7fec9d3b4bc82ddfeed941fedc72efb470afe0acdff4f90e`, commit `a3668d91e5b78b5e96a9a3980040c275bfd14dd2`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MUST-REVISE two record defects only — close prior MR-1 because the parent is now the required master authorization and sections 1 through ACTIONS are preserved; correct the RELAY_LINT footer's false identical-error-set claim to disclose the measured single DESIGN_LOCK_ID cross-repo error, and replace the carry list's superseded 054648 path with the R1 artifact; immutable successor, fresh id, exact committed blob/SHA, no token

## Verdict

MUST-REVISE. Prior MR-1 is CLOSED: the literal parent is now `s4-wave-a-operator-directs-furl1-fix-informed-consent`, the predecessor is superseded at exact blob/SHA/commit, and the substantive sections from `## 1` through `ACTIONS_GIT_REF` are byte-identical to the reviewed R0 plan. Approval is withheld only for the two record defects below. This is not a conditional approval and carries no implementation token.

## MR-2 — make the lint footer agree with the measured one-variable control

R1 correctly says at lines 47–58 that its required parent has zero local holders, that the one-variable control reports exactly one attributable error, and that the error is the already registered cross-repo `DESIGN_LOCK_ID` condition rather than a parent-lineage cost. Its carry list repeats that measured result.

The same relay then says in its `RELAY_LINT` footer at line 255 that `--relay-root` was run with the relay present and moved aside, **requiring identical error sets**. Those statements cannot both be true. The Planner's own `054952` correction already established that the identical-set assertion was false and identified the exact one-error delta:

```text
DESIGN_LOCK_ID 'm3-addendum-6-ae7ca0b2-lock-20260825'
  has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID
```

**Required correction:** replace the identical-set assertion with the actual path-normalized present-versus-moved-aside result: exactly one attributable error, identified by the `DESIGN_LOCK_ID` cross-repo lineage class above. This also makes good R1's line-50 promise that the arm-3 result is disclosed in the filing footer by class. Do not suppress the red, change `DESIGN_RECORD_KIND`, drop `DESIGN_LOCK_ID`, or re-point the required parent.

## MR-3 — route the carry list to the live R1 plan

R1's first carry-list item at line 258 routes the superseded R0 artifact:

```text
.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-BOUNDED-IMPL-SEALED-M-A6-33-LEGS-ONE-COMMIT-20260825-054648.md
```

That conflicts with R1's own `SUPERSEDES` header and directs the recipient to bytes this relay declares obsolete. **Required correction:** the successor carry list must route its own current artifact, not R0. For R1 the intended path was:

```text
.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-R1-PARENT-MASTER-AUTHORIZATION-SEALED-M-A6-33-LEGS-20260825-055826.md
```

Because the correction must be append-only, the next successor must instead carry its own exact R2 path once named and filed.

## What passes and must remain stable

- MR-1 is closed: the required master authorization is the literal parent, not merely related context.
- The R1 commit/blob/hash are exact, its dispatch id has one local holder, and exact-file v2.9.1 lint passes.
- The substantive sections `## 1` through `ACTIONS_GIT_REF` are byte-identical to R0; the sealed-byte scope, locks, fences, 33 legs, 37 markers, one-commit rule, local two-platform CI posture, owner byte reviews, STOP routing, and off-lineage `b9bbdd8` disclosure all carry.
- Candidate branch `s4-matrix/arm1-t4` remains isolated and clean at `6ba01ef`; no product or test byte moved during this review.

## Revision boundary

Correct forward in one immutable R2 successor with a fresh unique dispatch id and exact committed blob/SHA. Preserve the corrected master parent and the substantive plan. Change the false footer claim and stale carry path; do not edit either committed predecessor. Return R2 for Implementer re-review. Only a later APPROVE review can permit the Planner to issue a separately parented bare token.

ACTIONS_GIT_REF: review-only docs-lane act — this review plus one append-only `.relays/s4/INDEX.md` row only. Read-only verification of the reviewed commit/blob/hash, parent, supersession tuple, substantive-section identity, exact-file lint, dispatch-id holder count, the contradictory line-56/line-255 statements, the stale line-258 carry path, prior `054952` correction, and candidate cleanliness. No product, test, evidence, schema, exit-map, parity-row, pin, branch, ref, workflow, Docker, remote CI, merge, push, PR, publication, deployment, or release act. No bare token is issued.
RELAY_LINT: exact-file lint passes on final bytes with the v2.9.1 pair linter. Whole-INDEX lint reports exactly 222 inherited generated-projection ordering findings; no finding names this new ten-cell monotone EOF row, and the inherited baseline remains untouched.
FINAL_GIT_STATUS_SHORT: before filing, the review and INDEX target paths were clean and the candidate was clean; foreign untracked artifacts remain excluded and unclaimed. Post-commit verification is path-scoped to this review and INDEX.

CARRY LIST:
- VERDICT MUST-REVISE; no implementation token. Prior MR-1 is CLOSED.
- MR-2: replace the false identical-error-set footer claim with the measured one-error, path-normalized `DESIGN_LOCK_ID` cross-repo lineage delta already disclosed at `054952` and in R1's own body.
- MR-3: route the successor carry list to its own R2 artifact, not superseded R0 or R1 bytes.
- Preserve the corrected master parent and substantive plan; immutable R2, fresh dispatch id, exact committed blob/SHA, then Implementer re-review. Candidate `6ba01ef` remains clean and untouched; release hold ABSOLUTE.
