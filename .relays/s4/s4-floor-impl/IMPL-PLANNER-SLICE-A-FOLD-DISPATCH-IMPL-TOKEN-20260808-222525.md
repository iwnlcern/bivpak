## IMPL DISPATCH — slice-A fold: the LIVE token. Under pair-Planner delegated conditional dispatch (approve review + SCOPE_DIFF all-in + parent chain, no hard trigger). Fold content is fixed by `214345`; the bare token below makes it live.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-a-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: A
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/version_floor.hpp -> in
- src/adapters/version_floor.cpp -> in
- src/core/open/render.cpp -> in
- src/core/open/sessions.cpp -> in
- src/core/report/envelope.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_render.cpp -> in
- tests/fixtures/probe-envelope-v1.json -> in
- harness/selftest/test_envelope.py -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/codex/install.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/version_floor.hpp -> plan dispatch-scope file set (production, new) L30
- src/adapters/version_floor.cpp -> plan dispatch-scope file set (production, new) L30
- src/core/open/render.cpp -> plan dispatch-scope file set (production) L30-31
- src/core/open/sessions.cpp -> plan dispatch-scope file set (production) L30-31
- src/core/report/envelope.cpp -> plan dispatch-scope file set (production) L30-31
- tests/test_sessions.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_pack.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_claude_install.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_codex_install.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_cli.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_envelope.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_render.cpp -> plan dispatch-scope file set (tests) L33
- tests/fixtures/probe-envelope-v1.json -> plan dispatch-scope tests/fixtures/** glob L33
- harness/selftest/test_envelope.py -> plan dispatch-scope file set (harness, A2 recapture) L34
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: the orchestrator delegated conditional dispatch at the initial PLAN dispatch; the Implementer's plan review returned approve (`s4-floor-pair-plan-review-approve`); the mechanical SCOPE_DIFF over the slice-A fold file set returns all-in (rows above; verified at this seat 20260808-222131); no hard trigger — the below-MIN cell (security I-1) is settled by-design per §A7.4, no routed item. Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-A-PANEL-DISPATCH-20260808-210909.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for the slice-A fold — content fixed by 214345; this relay supplies the authorization you correctly held for

You were right: my `214345` slice-A relay declared implementation authority but carried no
live token. This relay issues the token under my delegated conditional-dispatch authority
(the four conditions are met and recorded in the header; SCOPE_DIFF all-in with per-row
evidence above). The fold CONTENT is unchanged and fixed by
`IMPL-PLANNER-SLICE-A-FOLD-AUTHORIZE-20260808-214345.md` and the panel record
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-a-panel-798526c.md`:

- **A-BL1 [Critical]** — the rewrite-verify cohort gate destroys the version-refusal
  carrier on BOTH legs (codex `install.cpp:433` clear() deletes; claude `install.cpp:574`
  relabels): add the `refusal_reason.has_value()` guard on claude, remove the codex clear()
  (or re-push), + a cohort test.
- **A-BL2..A-BL6** — schema-validate `readable-newer-than-survey` (fixture row); fix the
  dead `else` at test_sessions.cpp:626-643 with a real refusing E2E row; add the pack
  fail-open + host-unparseable tests; gate the disclosure on `caps.verdict()`; move the
  admission conjunction into `version_floor::admit(...)`.
- **By-design, NOT folded:** security I-1 below-MIN-at-open (§A7.4).

The token authorizes exactly the SCOPE_DIFF above. Any file outside it is a NEW deviation
routed up BEFORE an edit. Write FOLD_SCOPE `all-in` before editing.

DISPATCH IMPL

## Gate after the fold
Slice A touches no anchored file (no A3 owed). One-commit law + subject preserved; host +
local Ubuntu 24.04 amd64 Docker suite (Actions unused, per CI-leg (a) — remote red is not a
blocker); republish PR #21. A-BL1 changes failure-path report behavior, so the amended head
owes a TARGETED RE-CHECK from me (not a full re-panel unless blast radius grows); on that, I
give the orchestrator the merge-ready confirmation it is holding slice A's condition-3 for.
Merge/release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is unchanged at 798526c pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (incl. the merged-locally main and the orchestrator's untracked B1 relay); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-A-FOLD-DISPATCH-IMPL-TOKEN-20260808-222525.md` → `s4-floor.implementer`
- live token for the slice-A fold; content fixed by 214345; SCOPE_DIFF all-in with per-row evidence
- amended head owes a targeted re-check by me, then slice-A merge-ready confirmation to the orchestrator (condition-3 held); merge/release the operator's, hold ABSOLUTE
