## PLAN-REVIEW — MUST-REVISE: the bounded corrective content is reviewable, but its parent contradicts the dispatch's explicit master-authorization parent

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: s4-matrix-furl1-corrective-plan-review-r0
PARENT_DISPATCH_ID: s4-matrix-furl1-corrective-impl-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-BOUNDED-IMPL-SEALED-M-A6-33-LEGS-ONE-COMMIT-20260825-054648.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-FENCED-CORRECTIVE-DISPATCHED-SEALED-TEXTS-VERIFIED-AT-MY-BYTES-20260825-052643.md; ../../../../pdc/master/relays/s4-wave-a-operator-directs-furl1-fix-informed-consent/PLAN-orchestrator-planner-20260825-051923.md
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
REVIEWED_PLAN: blob `a92ae9464ffc1787d9495598655a06bc77e4d4b6`, SHA-256 `afec0f9e18fa2f3c4e39033651306740f0f5b7410f6e5937566aaf690e39dd86`, commit `b9f3ec23b1f4a44c9211584814de0b38992a2505`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MUST-REVISE one load-bearing relay-form defect — the Orchestrator dispatch requires the bounded pair PLAN's PARENT to be master authorization `s4-wave-a-operator-directs-furl1-fix-informed-consent` at `051923`, while the reviewed header instead parents `s4-matrix-furl1-fenced-corrective-dispatch`; RELATED_CONTEXT does not satisfy PARENT; correct forward in an immutable successor, preserve the reviewed scope and evidence, then return for re-review; no token

## Verdict

MUST-REVISE. The product scope, sealed-byte fences, 33-leg and 37-marker proof population, one-commit rule, two-platform local-CI posture, owner reviews, and off-lineage `b9bbdd8` disclosure survive this review round. Approval is nevertheless impossible because the relay's load-bearing parent contradicts the dispatch that authorizes the ceremony.

## MR-1 — bind the PLAN to the required master authorization parent

The Orchestrator dispatch states the ceremony three times, including its executable block:

```text
your Planner: bounded impl PLAN fenced to M + A6 (DESIGN_LOCK_IDs; PARENT = master 051923 authorization)
```

Master `051923` has dispatch id:

```text
s4-wave-a-operator-directs-furl1-fix-informed-consent
```

The reviewed PLAN instead carries:

```text
PARENT_DISPATCH_ID: s4-matrix-furl1-fenced-corrective-dispatch
```

and places master `051923` only in `RELATED_CONTEXT`. Context is not parentage. The plan's own ceremony prose also says it runs under master `051923`, so the header contradicts both its parent dispatch and itself.

**Required correction:** file an append-only successor PLAN whose literal header is:

```text
PARENT_DISPATCH_ID: s4-wave-a-operator-directs-furl1-fix-informed-consent
```

Keep the local Orchestrator dispatch and this review in `IN_REPLY_TO` or `RELATED_CONTEXT` as appropriate, but do not substitute either for the required parent. Do not edit the committed `054648` relay. Use a fresh unique dispatch id and return the successor's exact committed blob/SHA for review.

## Independent review evidence that carries

- The reviewed plan is exact at commit `b9f3ec23b1f4a44c9211584814de0b38992a2505`, blob `a92ae9464ffc1787d9495598655a06bc77e4d4b6`, SHA-256 `afec0f9e18fa2f3c4e39033651306740f0f5b7410f6e5937566aaf690e39dd86`; its dispatch id has one holder; exact-file v2.9.1 lint passes.
- Independent sealed-byte checks match: A6 locked `ae7ca0b2…c883` and live `9d2a915c…f295`, lock id once; M locked `681d351f…113e9` and live `4a61da22…913e9`; SR-URL live `a2f777c2…7798`.
- `git merge-base --is-ancestor b9bbdd8 6ba01ef` exits 1, confirming the cited CLI pin is off-lineage. Every plan-listed locus was inspected at `6ba01ef` and matches the described live shape.
- `git grep GitCallClass::network` at `6ba01ef` yields the four required call sites plus the central classifier switch, matching the class-closure population.
- The plan correctly counts M's 15 legs and 12 markers plus A6's 18 legs and 25 markers, and correctly keeps the schema/exit-map/parity/pin surfaces inside A6's one-commit rule.
- Candidate branch `s4-matrix/arm1-t4` remains isolated and clean at `6ba01ef`; no product or test byte moved during review.

## Revision boundary

MR-1 is a relay-lineage correction. Preserve the substantive plan unless the Planner independently discovers another defect while correcting forward. A later review is still required; this relay is not a conditional approval, and the Planner must not issue the bare token from it.

ACTIONS_GIT_REF: review-only docs-lane act — this review plus one append-only `.relays/s4/INDEX.md` row only. Read-only verification of the reviewed commit/blob/hash, dispatch-id holder count, exact-file lint, sealed hashes and lock-id count, base loci, class population, pin ancestry, and candidate cleanliness. No product, test, evidence, schema, exit-map, parity-row, pin, branch, ref, workflow, remote CI, merge, push, PR, publication, deployment, or release act. No bare token is issued.
RELAY_LINT: exact-file lint passes on final bytes with the v2.9.1 pair linter. Whole-INDEX lint reports exactly 222 inherited generated-projection ordering findings; they remain disclosed and untouched. This row is ten-cell and monotone at the live EOF.
FINAL_GIT_STATUS_SHORT: before filing, the review and INDEX target paths were clean and the candidate was clean; foreign untracked artifacts remain excluded and unclaimed. Post-commit verification is path-scoped to this review and INDEX.

CARRY LIST:
- VERDICT MUST-REVISE; no implementation token.
- MR-1: successor PLAN literal `PARENT_DISPATCH_ID` must be `s4-wave-a-operator-directs-furl1-fix-informed-consent`, not the local Orchestrator dispatch; RELATED_CONTEXT is not parentage.
- Preserve the substantive sealed-byte scope and proof obligations; correct forward, do not edit committed `054648`.
- Return the successor's exact committed blob/SHA for Implementer re-review. Candidate `6ba01ef` remains clean and untouched; release hold ABSOLUTE.
