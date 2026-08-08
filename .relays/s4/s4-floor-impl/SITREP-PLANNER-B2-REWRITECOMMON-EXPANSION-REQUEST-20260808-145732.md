## SITREP — B2 fold is scope-blocked on two out-of-universe paths (`rewrite_common.{hpp,cpp}`) that BL2-2/BL2-7 require; requesting the narrow expansion. Owning the miss: my fold prescribed the shared-module home without flagging it as outside the locked universe.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-rewritecommon-expansion
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-review-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — admitting paths absent from the locked dispatch universe is a universe expansion, the orchestrator's to grant (the A6-part-2 precedent), not the pair's
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-SCOPE-DEVIATION-20260808-143549.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: EXPANSION REQUESTED — exactly `src/adapters/rewrite_common.hpp` + `.cpp` for BL2-2/BL2-7; recommend grant (existing charter-reserved files, no new TU/CMake); master's B2-1/B2-2 ruling received and reconciled

## The block (verified at the plan bytes)

The implementer wrote FOLD_SCOPE before any edit (git-ignored artifact SHA-256
`eecc736c…`) and it returned `deviation-present`. The branch is clean at exact
`54a6c54`. The deviation is exactly two paths: `src/adapters/rewrite_common.hpp` and
`src/adapters/rewrite_common.cpp`. I confirmed at the plan bytes: the Dispatch-scope file
set (plan lines 30-33) names `adapter.hpp`, both adapters, sessions/render/pack/envelope/
error/main, the schemas and `CMakeLists.txt` — but `rewrite_common` appears NOWHERE in the
plan. So this is a genuine universe-boundary crossing, not a Task-Files-list omission — the
same class as slice C's `open-consent-per-agent.json` (A6 part 2), which was yours to grant.

## Why the fix genuinely needs these two paths

- **BL2-2 (Critical)** requires an INDEPENDENT `.txt` verifier (count bare `matches_at`,
  no `boundary_ok`). The correctness lens's binding fix-shape is a SINGLE fail-closed
  origin-scan floor across all three handling arms — and the raw-text rewrite/verify API is
  the 208-line block that BL2-7 must move OUT of the root `adapter.hpp` (where it also
  bypasses the `bugprone-*` swap guard, idiom I-2). Fixing the verifier and moving the API
  land together.
- **BL2-7 (Important, with a silent-failure edge)** requires ONE shared spelling of the
  staging-sidecar schema/parser — today 96 byte-identical lines in both adapters for a
  document `sessions.cpp` writes; rename a writer key and both readers silently drop staged
  sessions. `rewrite_common` is the module the charter reserves for exactly this shared
  logic; any in-universe substitute creates a competing owner or an adapter↔core cycle.

The implementer confirms no honest in-universe substitute satisfies either finding, and
that both files ALREADY build and are ALREADY included by both adapters — so the grant
needs no new translation unit, no CMake change, no manifest/schema/workflow edit.

## Owning the miss
My REVIEW-FOLD said "every required BL2 row is inside the B2 universe" — mechanically false
for these two paths; my fold prescribed the `rewrite_common` home without flagging it as
outside the locked universe. The implementer caught it on the mandatory pre-edit FOLD_SCOPE
exactly as the discipline intends. Same instrument-substitution class the run keeps naming;
the answer is the standing rule (run the SCOPE_DIFF, never assert it), which the implementer
did.

## Requested grant (narrow)
Admit EXACTLY `src/adapters/rewrite_common.hpp` and `src/adapters/rewrite_common.cpp` to
the B2 dispatch universe, limited to BL2-2 (independent raw-text verifier + typed-span API)
and BL2-7 (shared staging-sidecar schema/parser owner). No new TU, no CMake, no
manifest/schema/workflow edit, no refusal-radius or design change. Recommend GRANT — these
are the charter-reserved shared module, already linked, and the minimal honest home for a
Critical-adjacent fix.

## Master's B2-1 / B2-2 ruling received and reconciled (no conflict with this request)
Your `145219` relay landed: B2-1 RULED per-session — **BL2-4 releases**, keep the
per-session radius the code already carries, gated on BL2-1/BL2-2 landing (the sound scan)
and the targeted re-panel confirming soundness with **m-4 addressed** on the containment
invariant; the operator retains countermand. B2-2 (manifest.cpp enum) is the matrix Arm-1
schema act's — `manifest.cpp` stays fence-2 OUT for the floor. Both fold into my resume to
the implementer once this expansion is disposed; neither changes the two paths requested
here. On grant, the implementer resumes the clean branch, folds BL2-1..BL2-3 + BL2-5..BL2-7
(BL2-4 per-session kept as-is) in one amended commit, re-fires the both-anchor A3 ceremony
if the collect files change, runs host + local Docker verification, republishes PR #23, and
the targeted security/correctness/tests re-panel (m-4 addressed) gates the replacement head.

ACTIONS_GIT_REF: no product/test edits at this seat — this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is clean at 54a6c54 with zero fold edits pending this disposition
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-REWRITECOMMON-EXPANSION-REQUEST-20260808-145732.md` → `s4.orchestrator-planner`
- exact two-path expansion `src/adapters/rewrite_common.{hpp,cpp}` for BL2-2/BL2-7 → orchestrator grant or refusal requested
- master B2-1 (per-session, BL2-4 released) + B2-2 (matrix schema act) → received; fold into the implementer resume on grant
- clean PR #23 head `54a6c54` → resume only after the expansion disposition; merge/release the operator's, hold ABSOLUTE
