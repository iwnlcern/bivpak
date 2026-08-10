## IMPL DISPATCH — the complete B2 amend: the LIVE token. Master ruled I-3 FOLDS (symmetric key decode/rewrite + INVERT the lock-in test); with F2 (Codex parent map + de-mask) and F3 (Codex child-id falsifier), ONE commit on the f9675ea line. Then suites, Docker, republish — and the FOURTH targeted re-panel, where M-4 must hold FULLY.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b2-i3-amend-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
SCOPE_DIFF:
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- src/adapters/codex/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- src/adapters/rewrite_common.cpp -> orchestrator expansion grant 20260808-150142 lineage (exercised under tokens 222434/025646/161206, CC'd unobjected); I-3 ruled FOLD by master 190203 (carried 191102) — the symmetric key decode/rewrite lands here
- src/adapters/rewrite_common.hpp -> same 150142 grant; touch ONLY if the key-decode symmetry forces a declaration change — no new public surface; if more than that is forced, STOP and route
- src/adapters/codex/install.cpp -> plan dispatch-scope file set (production) L30-31; F2 site (parent verify/rewrite asymmetry, byte-verified at f9675ea)
- tests/test_adapter_claude_install.cpp -> plan dispatch-scope file set (tests) L33; the lock-in test to INVERT per master's ruling
- tests/test_adapter_codex_install.cpp -> plan dispatch-scope file set (tests) L33; F2 de-mask + F3 falsifier
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: orchestrator-delegated conditional dispatch at the initial PLAN dispatch; Implementer plan review = approve (`s4-floor-pair-plan-review-approve`); mechanical SCOPE_DIFF all-in (rows above; verified at this seat 20260809-191503; F1/F2/F3 byte-verified at f9675ea at this seat 183203-185502 window); no hard trigger — every finding's disposition is RULED (master 190203 for I-3; the orchestrator's 185502 for F2/F3), EXCEPT the pre-flagged F2 self-reference cell which is an explicit STOP-AND-ROUTE inside this token, not a guess. Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-I3-RULED-FOLD-INTO-B2-AMEND-SCOPE-COMPLETE-20260809-191102.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for the complete B2 amend — I-3 symmetric key decode/rewrite + inverted lock-in test + F2 parent map/de-mask + F3 falsifier, one commit on the f9675ea line

Master ruled I-3 folds (deferral refused — a confirmed Critical with an in-scope
one-mechanism fix does not sit open behind the hold). The amend scope is complete; this
token makes it live.

## The fold set (ONE commit on the `f9675ea` line, subject preserved)

**1. I-3 — symmetric key decode/rewrite (Critical; master's ruling verbatim in substance):**
- `verify_scan`: decode JSON object KEYS (`decode_keys=true`, exactly as B2's own
  `verify_whole_document_bytes` already does) and apply the full needle set to the decoded
  keys — the two verify arms become symmetric.
- `rewrite_jsonl`: rewrite keys under the pair-set exactly as values are rewritten
  (longest-source-first — the ruled precedence applies to keys too).
- **INVERT the lock-in test** (`test_adapter_claude_install.cpp:534-569`): it currently
  asserts the origin-path KEY survives verbatim with `outcome==installed` — that assertion
  enshrines the leak and is part of the defect. The amended test asserts the origin key is
  REWRITTEN under the pair-set (or the row refuses). A test enshrining a Critical is never
  a constraint on its fix.

**2. F2 — Codex parent verify/rewrite asymmetry (must-fix; byte-verified):** map the parent
id in the rewrite id-map to the parent's INSTALLED id when the parent is in the image, so
it rewrites instead of self-refusing; de-mask `test_adapter_codex_install.cpp:1659-1717`
with a collect-realistic body actually carrying `parent_thread_id`.
**PRE-FLAGGED STOP-AND-ROUTE (master + orchestrator, binding):** if the fix surfaces the
definition question — is a session's OWN `parent_thread_id` referencing a NOT-in-image
parent an origin disclosure to rewrite, or a self-reference to preserve — that is
family-invariant territory: STOP and route it up BEFORE folding an answer. Do not guess.

**3. F3 — Codex cross-session child-id falsifier (Important):** mirror
`test_adapter_claude_install.cpp:2210` — a recipient session referencing another session's
`child.original_id`/staged `child_identity` must show `origin_id_hits>0`/refused; deleting
the codex child-id union insert must fail this test.

**4. TIMEOUT 600:** already landed on this line at `f9675ea` (verified) — no further edit;
carry it forward in the amend unchanged.

Minors (the two `valid_utf8` definitions, cross-pair re-scan, blank-line/empty-artifact
edges): your discretion or record as residuals — not blocking.

## Bounds
Exactly the five SCOPE_DIFF files. `rewrite_common.hpp` only if the key-decode symmetry
forces a declaration change, with no new public surface — more than that is a
stop-and-route. No `manifest.*`, no `.github`, no R-4.8/home-prefix work, no radius/domain
change, no `claude_code/install.cpp` or collector reach (nothing in the fold set needs
them). Re-write FOLD_SCOPE `all-in` before editing. Any file beyond these five is a NEW
deviation routed up BEFORE an edit.

DISPATCH IMPL

## Then (the standing gate sequence)
Strict TDD per finding (the inverted lock-in test and the two new falsifiers must be RED
against the pre-fix behavior and GREEN after); amend into the SINGLE commit over `ec9a2db`,
subject preserved; run the A3 mechanical check (no anchored collect file in this scope —
run it, never assert it); scoped independent re-review of the amend delta; the full host
suite (honestly green under the durable 600s budget); the standing local Ubuntu 24.04
`linux/amd64` Docker suite (Actions unused); republish PR #23; report per the standing
shape. On your republish I request the orchestrator's FOURTH targeted re-panel — M-4 must
hold FULLY at that head (I-3 closed, no key-arm leak; F2 self-refusal gone; F3 covered).
On its pass B2 is bar-ready and the C→B2-immediate pair proceeds. R-4.8 and the disclosed
Minors stay separately carried. Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; B2 remains at published `f9675ea` pending your amend
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (main holds the two local merges; the matrix pair's R-4.8 relays sit untracked); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-I3-F2-F3-AMEND-DISPATCH-IMPL-TOKEN-20260809-191503.md` → `s4-floor.implementer`
- live token: I-3 symmetric key decode/rewrite + inverted lock-in test + F2 parent map/de-mask (self-reference cell = STOP-AND-ROUTE) + F3 falsifier; ONE commit; SCOPE_DIFF all-in w/ evidence
- then suites + Docker green, republish PR #23 → I request the FOURTH re-panel (M-4 must hold FULLY)
- on its pass → B2 bar-ready; C→B2-immediate proceeds; R-4.8 + Minors separate; merge/release the operator's, hold ABSOLUTE
