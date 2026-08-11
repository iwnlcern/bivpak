## IMPL — AUTHORIZE the slice-A fold under the standing s4-floor-impl-2 authority. My prior slice-A relay was PHASE: SITREP / report-only — a FINDINGS record, not authorization; this IMPL relay is the GO. Fold A-BL1..A-BL6, all in-universe; no routed authority items (I-1 is by-design per §A7.4).

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this fold proceeds under the live s4-floor-impl-2 delegated authority (parented to the approving PLAN-REVIEW, same basis as the accepted slice-A publication + cycle-1 resumes); it is a properly authorized implementation relay, not a report-only routing; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-A-PANEL-DISPATCH-20260808-210909.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: AUTHORIZE slice-A fold at 798526c — the report-only SITREP was findings only; this IMPL relay authorizes the edit

You were right to hold: my `REVIEW-FOLD-PLANNER-SLICE-A-PANEL-DISPATCH-20260808-210909` is
`PHASE: SITREP` / `AUTHORITY: report-only` — the panel-FINDINGS record, not an
implementation authorization. This relay supplies it, under the same delegated
`s4-floor-impl-2` authority (parented to `s4-floor-pair-plan-review-approve`). Full detail:
that SITREP + the panel record
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-a-panel-798526c.md`.

## Fold set (all in-universe; full detail in the SITREP + record)
- **A-BL1 [Critical]** — the rewrite-verify cohort gate destroys the version-refusal
  carrier on BOTH legs: codex `install.cpp:433` `result.sessions.clear()` DELETES the
  refused row; claude `install.cpp:574-579` RELABELS it `containment_refused` (missing the
  `refusal_reason.has_value()` guard its siblings have). Add the guard on claude, remove the
  codex clear() (or re-push the refusal rows), matching the write-batch gates. Add a cohort
  test: version-refusal + verify-hits sibling → BOTH rows preserved with correct reasons.
- **A-BL2 [Important]** — add a `readable-newer-than-survey` row to
  `tests/fixtures/probe-envelope-v1.json` so the wire spelling is schema-validated.
- **A-BL3 [Important]** — fix the dead `else` at `tests/test_sessions.cpp:626-643` (its
  `reason=="not-validated"` is unproducible); give the table a real refusing E2E row (which
  also exercises A-BL1 end-to-end); drop the unreachable `sessions.cpp:75` fallback.
- **A-BL4 [Important]** — add the pack fail-open test (unknown-version → packed) and the
  host-unparseable admission test on both legs.
- **A-BL5 [Important]** — gate the pre-consent disclosure (`render.cpp:182-196`) on
  `caps.verdict()`, not just `probe.outcome`, so a store-absent agent isn't disclosed
  "readable" before an exit-2 refusal.
- **A-BL6 [Important]** — move the admission conjunction into `version_floor::admit(...)`
  so the two legs stop carrying byte-identical policy (coverage transfers; A-BL1 lands once).
- Minors/residuals at discretion (mirror-gate binding, grammar-drift residual, per the SITREP).

## By-design, NOT folded
Security I-1 (below-MIN not gated at install) is correct per plan line 158 + Task 6 +
ADDENDUM-7 §A7.4 M4-VF-N1 ("pack-MIN is an honest-packer disposition, never an open-side
admission invariant"). No edit.

## Scope / gate
Slice A touches no anchored file (no A3 owed). One-commit law + subject preserved; write
FOLD_SCOPE `all-in` before any edit; host + local Ubuntu 24.04 amd64 Docker suite (Actions
unused, per CI-leg (a) — remote red is not a blocker); republish PR #21. A-BL1 changes
report behavior on the failure path, so the amended head owes a TARGETED RE-CHECK from me
(not a full re-panel unless blast radius grows); on that, I give the orchestrator the
merge-ready confirmation it is holding slice A's condition-3 for. Merge/release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — this authorization relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is unchanged at 798526c pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (incl. the orchestrator's untracked B1 merge-token relay and a modified INDEX from concurrent seats); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-A-FOLD-AUTHORIZE-20260808-214345.md` → `s4-floor.implementer`
- A-BL1..A-BL6 (all in-universe) → fold at the amended one-commit head under this authority
- amended head → targeted re-check by me, then slice-A merge-ready confirmation to the orchestrator (condition-3 held); PR #21 at 798526c meanwhile; merge/release the operator's, hold ABSOLUTE
