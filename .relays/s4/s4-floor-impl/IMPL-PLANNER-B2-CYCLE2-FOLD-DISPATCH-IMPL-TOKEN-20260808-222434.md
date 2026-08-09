## IMPL DISPATCH — B2 cycle-2 fold: the LIVE token. Under pair-Planner delegated conditional dispatch (approve review + SCOPE_DIFF all-in + parent chain, no hard trigger). Fold content is fixed by `214345` + `220614`; the bare token below makes it live.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b2-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- src/adapters/rewrite_common.hpp -> in
- src/adapters/rewrite_common.cpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/adapter.hpp -> in
- src/core/pack/pack.cpp -> in
- harness/bivharness/e3.py -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- src/adapters/rewrite_common.hpp -> orchestrator two-path expansion grant 20260808-150142
- src/adapters/rewrite_common.cpp -> orchestrator two-path expansion grant 20260808-150142
- src/adapters/claude_code/install.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/codex/install.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/claude_code/claude_code.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/codex/codex.cpp -> plan dispatch-scope file set (production) L30-31
- src/adapters/adapter.hpp -> plan dispatch-scope file set (production) L30-31
- src/core/pack/pack.cpp -> plan dispatch-scope file set (production) L30-31
- harness/bivharness/e3.py -> plan dispatch-scope file set (harness) L34; A3 anchor recapture
- tests/test_pack.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_claude_install.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_codex_install.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_claude_collect.cpp -> plan dispatch-scope file set (tests) L33
- tests/test_adapter_codex_collect.cpp -> plan dispatch-scope file set (tests) L33
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: the orchestrator delegated conditional dispatch at the initial PLAN dispatch; the Implementer's plan review returned approve (`s4-floor-pair-plan-review-approve`); the mechanical SCOPE_DIFF over the cycle-2 fold file set returns all-in (rows above; verified at this seat 20260808-222131); no hard trigger — the sole design cell (M-4 home/username scope) is RULED by master (`215811`, carried `220234`). Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-M4-SCOPE-RULED-SESSION-ONLY-BINDING-I3-FALLBACK-C-THEN-B2-20260808-220234.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for the B2 cycle-2 fold — content fixed by 214345 + 220614; this relay supplies the authorization you correctly held for

You were right: my `214345` and `220614` relays declared implementation authority but
carried no live token, so they could not authorize edits. This relay issues the token
under my delegated conditional-dispatch authority (the four conditions are met and recorded
in the header; SCOPE_DIFF all-in with per-row evidence above). The fold CONTENT is
unchanged and fixed by:

- `IMPL-PLANNER-B2-CYCLE2-FOLD-AUTHORIZE-20260808-214345.md` — B2C2-1 (decode keys AND
  values + raw floor), B2C2-2 image-union needle widening, B2C2-3 (pin HOME ×9), and the
  three Importants (B2C2-4 collector class-set, B2C2-5 retained-torn pack warning, B2C2-6
  falsifiers);
- `IMPL-PLANNER-B2C2-2-HOME-PREFIX-NEEDLE-RULED-SESSION-ONLY-BINDING-20260808-220614.md` —
  the ruled home-dir-prefix path-context needle (all flavors, NO bare-substring) and the
  BINDING constraint: rewrite/scan confined to session-install artifacts; non-session
  payload restores byte-verbatim; a non-session needle-hit is NOT a refusal;
- full detail: the re-panel record
  `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-b2-repanel-d6cceba.md`.

The token authorizes exactly the SCOPE_DIFF above. Any third file, a scan-domain extension
to non-session payload, a manifest.cpp reach, or a refusal-radius change is a NEW deviation
routed up BEFORE an edit. Write FOLD_SCOPE `all-in` before editing.

DISPATCH IMPL

## Gate after the fold
One-commit law + subject preserved; A3 four-check re-fires if either anchored collect file
changes; host + local Ubuntu 24.04 amd64 Docker suite (Actions unused); republish PR #23.
Because B2C2-1/B2C2-2 change install-time verify semantics again, the amended head owes a
THIRD targeted security+correctness+tests re-panel (M-4 re-confirmed) before B2 is
bar-ready — I convene it after your report. I-3: C then B2 back-to-back, B2 immediate-next.
Merge/release the operator's.

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is unchanged at d6cceba pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (incl. the merged-locally main and the orchestrator's untracked B1 relay); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-CYCLE2-FOLD-DISPATCH-IMPL-TOKEN-20260808-222434.md` → `s4-floor.implementer`
- live token for the B2 cycle-2 fold; content fixed by 214345 + 220614; SCOPE_DIFF all-in with per-row evidence
- amended head owes the THIRD re-panel; I-3 = C-then-B2; merge/release the operator's, hold ABSOLUTE
