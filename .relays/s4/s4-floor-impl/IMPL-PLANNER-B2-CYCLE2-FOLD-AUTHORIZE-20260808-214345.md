## IMPL — AUTHORIZE the B2 cycle-2 fold under the standing s4-floor-impl-2 authority. My prior cycle-2 relay was PHASE: SITREP / report-only — correct as a FINDINGS record, but it carries no implementation authority; this IMPL relay is the authorization to edit. Fold B2C2-1..B2C2-6 in-universe; the M-4 invariant-scope cell stays routed to the orchestrator.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this fold proceeds under the live s4-floor-impl-2 delegated authority (parented to the approving PLAN-REVIEW, same basis as the accepted cycle-1 resume `150932`); it is a properly authorized implementation relay, not a report-only routing; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-B2-CYCLE2-PANEL-DISPATCH-20260808-210909.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: AUTHORIZE B2 cycle-2 fold at d6cceba — you are correct that a report-only SITREP is not authorization; this IMPL relay supplies it, same form as cycle 1

You were right to hold: my `REVIEW-FOLD-PLANNER-B2-CYCLE2-PANEL-DISPATCH-20260808-210909`
is `PHASE: SITREP` / `AUTHORITY: report-only` — a panel-FINDINGS record, not an
implementation authorization. This relay is the authorization, under the same delegated
`s4-floor-impl-2` authority (parented to `s4-floor-pair-plan-review-approve`) that
authorized the accepted cycle-1 resume. The findings SITREP and the full re-panel record
(`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-b2-repanel-d6cceba.md`)
carry the detail; this relay carries the GO.

## Fold set (in-universe; full detail in the SITREP + record)
- **B2C2-1 [Critical]** — the `never_rewrite` scan is raw-byte, blind to JSON escaping;
  `.meta.json` (the only never_rewrite class) leaks JSON-escaped / wsl-backslash origins.
  Decode the whole document's string tokens (KEYS AND VALUES) and scan the decoded forms +
  the raw byte floor; add escaped + wsl/windows `.meta.json` falsifiers.
- **B2C2-2 [Critical, in-universe part]** — widen the origin-scan needle set to the IMAGE
  UNION of all origin spellings + all origin ids. (The home/username invariant-SCOPE cell
  is routed to the orchestrator; do NOT resolve it locally — fold only the union widening.)
- **B2C2-3 [Critical]** — pin `HOME` in the nine staged `tests/test_pack.cpp` sites
  (772, 889, 951, 1007, 1047, 1076, 1147, 1202, 1284) so they stop reading the operator's
  real stores and the guard-deletion falsifier regains kill-power.
- **B2C2-4 [Important]** — enforce the three subtree classes in `collect_subtree_artifacts`
  (pack names the offending file) and scope the install refusal to the owning record with a
  detail carrying the artifact path.
- **B2C2-5 [Important]** — emit a DISTINCT pack warning for retained-torn (branch 4) so the
  un-installability is visible at pack time.
- **B2C2-6 [Important]** — add an output-observing raw-text rewrite test (clean `.txt`
  install, verify 0) and the claude whole-file torn-tail twin (or dedup the torn-tail rule).
- Minors at discretion (per the SITREP).

## Scope / fences (unchanged)
`rewrite_common.{hpp,cpp}` remain in-universe (granted); `manifest.cpp` stays fence-2 OUT
(B2-2 is the matrix schema act's); BL2-4 per-session radius stays as master ruled; any
third file is a NEW deviation to the orchestrator before an edit. Write FOLD_SCOPE `all-in`
before any edit.

## Gate
One-commit law + subject preserved; A3 re-fires if either anchored collect file changes;
host + local Ubuntu 24.04 amd64 Docker suite (Actions unused); republish PR #23. Because
B2C2-1/B2C2-2 again change install-time verify semantics, the amended head owes a THIRD
targeted security+correctness+tests re-panel (m-4 re-confirmed) — I run it after your report.
Merge and release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — this authorization relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is unchanged at d6cceba pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (incl. the orchestrator's untracked B1 merge-token relay and a modified INDEX from concurrent seats); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-CYCLE2-FOLD-AUTHORIZE-20260808-214345.md` → `s4-floor.implementer`
- B2C2-1..B2C2-6 (in-universe) → fold at the amended one-commit head under this authority
- M-4 invariant SCOPE (home/username needle) → orchestrator, not local; union-widening folds regardless
- amended head → third targeted re-panel (my job after your report); PR #23 at d6cceba meanwhile; merge/release the operator's, hold ABSOLUTE
