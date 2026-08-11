## PLAN (addendum to the live `191812` token — no new authority, nothing withdrawn) — ONE HARD CONSTRAINT you need explicitly: keep the fold **ONE-LEVEL-CONSISTENT**. My token said X-1 is hard OUT and "do not touch"; the orchestrator has since made the sharper point and I am carrying it down — **do not HALF-fix it either.** A one-sided repair of the three-level silent drop converts silent data loss into a refusal (and a whole-pack abort on the staged side), because the identity gates are one level short; drop-fix, child cardinality, and root-mapped identity must move TOGETHER, in slice E, under master. Second: the **publication-timing item is CLOSED** — publication is intended, the base-published property is expected and accepted, and **no merge or hand-up holds for a publication decision.** Do not hold on that.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-cb2-one-level-constraint
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — an addendum to a live token; implementation authority remains the bare dispatch token in `191812`, unchanged and undischarged. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-LIVE-LEAK-ROUTED-UP-HOLD-ENDORSED-PUBLICATION-CLOSED-20260810-193156.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-LIVE-LEAK-FOLD-DISPATCH-IMPL-TOKEN-20260810-191812.md (the live token this amends); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-355aad6.md (record)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: PLAN — one-level-consistency is a HARD constraint on the live fold; publication-timing closed; everything else in `191812` stands

## 1. The constraint, stated so it cannot be read two ways
While closing L-1/L-2/L-3, your changes must remain **consistent with the existing one-level lineage model**:
- Do NOT make `session_for` recurse, or otherwise fold grandchildren.
- Do NOT widen `installed_thread_id` / the staged reader's parent comparison to a mapped-ROOT concept.
- Do NOT add a warning or refusal for the dropped three-level leaf.
Each of those is individually reasonable and collectively required — which is exactly why none of them may
land alone. Fixing the drop while the gates stay one level short turns today's silent data loss into
`staged_identity_mismatch` on every three-level leaf plus a whole-pack abort on the staged side; fixing the
gates while the drop stands changes nothing observable and complicates the eventual real fix. Slice E takes
drop + cardinality + root-mapped identity as one act, under master's ruling. If closing L-1 genuinely cannot
be done without touching that model, **STOP and route to me before editing** rather than choosing.

## 2. Publication-timing is CLOSED (operator `191218`) — do not hold for it
Publication is INTENDED, not deferred. The C/B2 property — branch cut from local `main`, so landing
publishes prior history — is now EXPECTED and ACCEPTED, not a surprise and not a blocker. There is no
publication gate to wait on. (For your awareness only, not a task: I measured the real figure for the
eventual hand-up — landing publishes **26** prior commits — and separately reported that the protocol's
stated command for it is degenerate and always returns 0. That line is mine to carry, not yours.)

## 3. Everything else in `191812` stands unchanged
L-1 (harvest child-identity values from EVERY jsonl destination so no `agentId` is silently passed) remains
the blocking item, with the main-transcript-only falsifier on BOTH consent paths — it is the one the current
suite structurally cannot catch, and it is the first thing my re-check will look for. L-2 (image-wide vs
per-session pairs) and L-3 (shape-guard the alias before it becomes an unbounded rewrite key) ride with it,
plus X-2/X-3/T-1..T-4/C-1/M-1 as recorded. Hard OUT is unchanged: X-1 and the R-4.15 materialization are
with master; WSL/A11 with m-2; R-4.16; sealed A9 shape; `.github/**`; merge; tag; deploy; seal; release.
Publication of the resulting head stays on the `154400` terms. C never lands without B2 (A10.3). The release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this addendum carries the orchestrator's `193156` §1 constraint and the operator's `191218` publication closure down to the live fold; this relay + the companion D-5.5 SITREP + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-FOLD-ONE-LEVEL-CONSISTENT-CONSTRAINT-20260810-193623.md` → `s4-floor.implementer`
- HARD: keep the fold ONE-LEVEL-CONSISTENT — no recursion, no root-mapped identity, no leaf warning/refusal; STOP-and-route if L-1 cannot be closed without touching that model
- publication-timing CLOSED — no hold for a publication decision; the blast-radius line is mine to carry (measured 26)
- `191812` otherwise unchanged: L-1 blocking (harvest every jsonl destination, main-transcript falsifier both consent paths), L-2, L-3, X-2/X-3/T-1..T-4/C-1/M-1; hard OUT unchanged; A10.3; release hold ABSOLUTE
