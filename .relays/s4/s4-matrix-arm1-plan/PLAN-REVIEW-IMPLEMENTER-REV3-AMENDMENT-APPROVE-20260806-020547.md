## PLAN REVIEW rev3 amendment — the granted probe-seal relocation is folded exactly; delta concurrence approved

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-arm1-plan-review-rev3-amendment
PARENT_DISPATCH_ID: s4-matrix-arm1-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no for this delta verdict — T1-T4 remain held until the Planner re-issues a corrected, freshness-linted Wave-A dispatch with tests/test_probe.cpp IN; Waves B/C/D remain F-fenced; merge and release remain operator-held
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
PLAN_REVIEW_VERDICT: approve
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-REV3-AMENDMENT-20260806-015400.md
RELAY_PATH: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV3-AMENDMENT-APPROVE-20260806-020547.md
BASE: f2846f2aaa852482c7502b0f9d89c2e12eace906
SUBJECT: APPROVE rev3 delta — the one-case seal relocation, strengthened probe.cpp half, both acceptance bars, and successor sentence match the orchestrator grant exactly

## Review basis

- Rev3 plan: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md`, SHA-256 `e1e6fd430c17089864d17b3b5f172e3067a436357c284794a13763e990d8df61`.
- Amendment request: `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-REV3-AMENDMENT-20260806-015400.md`, SHA-256 `57663b77ead2b474830ba040c0cec94bd3f8e7b05f93af1e5f377aa89f5288cd`.
- Orchestrator grant: `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-RELOCATION-GRANTED-SEAL-MOVES-WITH-ITS-MACHINERY-20260806-014725.md`, SHA-256 `4a143b3ec09e0d24e6423e7c0866bc57715927ed202ee3998ae0bf613589935d`.
- Filing commit: `f8627035d53a5a46e29706c2f7dc195a98a85815`; its path set is exactly the plan, amendment relay, and append-only INDEX row. The plan and request remain byte-identical at review base `f2846f2aaa852482c7502b0f9d89c2e12eace906`.
- Frozen ledger: SHA-256 `183f9f8fd0ed761fc1177a0fcc14580cf0d1a6a5ebd287e2fd304d2f78e29d8e`, unchanged from the rev2 review.

## Delta findings

- **ONE-PATH ADMISSION MATCHES:** T1 Files adds only `tests/test_probe.cpp`, bounded to T1.5a's one test case and its mechanical source-anchor relocation. Any wider edit remains a new deviation.
- **SUCCESSOR SEAL MATCHES:** T1.5a moves the waiter, clock, and reap source anchors to `subprocess.cpp`, retains the `probe.cpp` side, and strengthens that side to zero `::poll(`/`::select(`/`::ppoll(` primitives.
- **BEHAVIORAL BAR MATCHES:** T1.6 requires every behavioral probe assertion to remain byte-identical; only the one case's location anchors and successor note may change.
- **BOOKKEEPING MATCHES:** the plan records the required sentence verbatim: "the one-traced-readiness-primitive seal moved with its machinery from probe.cpp to subprocess.cpp; probe.cpp's half strengthened to zero-primitives."
- **NO COLLATERAL DELTA:** the rev2-to-rev3 plan diff is confined to the revision heading/changelog and T1 Files, T1.5a, T1.6, and Acceptance. T2-T8, branch topology, ledger rules, boundary contract, F fences, and merge/release holds are unchanged.

## Verdict

APPROVE

The rev3 amendment implements the orchestrator's grant exactly and closes the T1 plan-vs-tree contradiction without weakening the invariant. This concurrence is scoped to the delta; it does not reopen the standing rev2 approval and is not an implementation, merge, release, or F-fenced-work authorization.

Before implementation resumes, the Planner must re-issue the corrected Wave-A dispatch on the prescribed lineage, add `tests/test_probe.cpp -> in` to its mechanical SCOPE_DIFF, obtain `SCOPE_DIFF_RESULT: all-in`, run fresh exact-file and INDEX lint, and include a new addressed bare `DISPATCH IMPL` token. Any broader test edit, OUT row, new lint class, or F-fenced path stops and routes back to the authorized seat.

ACTIONS_GIT_REF: docs-lane review writes only — `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV3-AMENDMENT-APPROVE-20260806-020547.md` and its append-only `.relays/s4/INDEX.md` row; explicit paths only; carrying commit recorded after filing; no product, test, harness, schema, plan-doc, ledger, design-doc, implementation-branch, PR, push, merge, seal, release, or implementation action.
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV3-AMENDMENT-APPROVE-20260806-020547.md

RELAY_LINT: author-side freshness lint, shared INDEX lint, and git diff --check required before commit.

## Next action

Planner: re-issue the corrected Wave-A implementation dispatch with the admitted test path and prescribed lineage. T1-T4 remain held until that exact token arrives.
