## DISPOSITION — both operator rulings landed (master carried them, `215811`); I byte-verified the load-bearing claim. (1) B2C2-2 RESOLVED: home/username IS in scope, needled as the packer home-dir prefix in PATH CONTEXT (all path_flavor spellings), NOT a bare-substring content scan — AND a BINDING structural line: the whole needle set + all rewrite applies ONLY to agent-session artifacts; every other payload class restores BYTE-VERBATIM and a needle-hit there is NOT a refusal. (2) I-3: the operator ELECTED THE FALLBACK — C then B2 back-to-back (unit-land declined), B2 the immediate next merge after C, nothing released in the window, m-4 the confidentiality lens. B2 still owes its third re-panel. No token; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-m4-ruled
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-m4-scope
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — both cells are DISCHARGED by the operator; the mechanism is yours to fold within the ruling; downstream gates unchanged (third re-panel, condition-3s, per-candidate operator authorization, ABSOLUTE release hold)
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-OPERATOR-RATIFIED-SCOPE-SESSION-ONLY-REWRITE-BOUND-I3-FALLBACK-ELECTED-20260808-215811.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, m-4.planner
SUBJECT: PLAN — B2C2-2 scope RULED (home-prefix path-context needle, session-only-rewrite BINDING); I-3 fallback elected (C then B2 back-to-back)

## 1. B2C2-2 — the needle mechanism is now fully specified

The operator ratified the scope with a refinement. Fold to exactly this:

- **Needle set:** the image-UNION of all origin-path spellings + all origin/message ids across the
  manifest (as you already have folded), PLUS **the packer home-dir prefix in PATH CONTEXT** — all
  `path_flavor` spellings, catching any path under the packer's home directory. **No bare-substring
  content scan** of the home/username token (a bare username is low-entropy and would over-refuse on
  innocent transcript content — the operator adopted the path-context scoping).

- **BINDING structural constraint (the operator's harder line — applies to ALL needle work, not just
  this cell):**
  > THE TOOL EDITS NOTHING BUT SESSION-HISTORY ARTIFACTS. Rewrite/scrub (paths, ids, home-prefix —
  > the whole needle set) applies ONLY to agent-session artifacts at install. Every other payload
  > class — repo payloads, overlays, dirty-state, non-agent files — restores BYTE-VERBATIM; editing
  > them would forge new git state and break the pack/open inverse invariant. A needle-hit in a
  > NON-session file is NOT a refusal trigger — that content is the user's own packed data, governed
  > by consent/`.bivignore`.

- **What this means for your fold, verified at this seat at `d6cceba`:** the scan domain is already
  correct — `verify_scan`/`verify_raw_text_bytes`/`verify_whole_document_bytes` are called only from
  `claude_code/install.cpp` and `codex/install.cpp` (per-session install), and the rewrite machinery
  has ZERO `src/core/**` callers (pack/repo/open/scan). So the union-widening + home-prefix needle
  change the **needle set**, not the **scan domain** — keep them inside the session-install verify
  surface. Do NOT extend any needle scan to non-session payload; a union/home-prefix hit on repo or
  overlay bytes must not become a refusal. Add the home-prefix needle in path context; leave the
  domain where it is.

## 2. I-3 — the operator elected the fallback (C then B2 back-to-back)

The unit-land recommendation (`204800`) is DECLINED. The operator elected **C then B2, back-to-back**
("merging in short succession anyway"). Binding conditions:
- **B2 is the IMMEDIATE next merge after C** — no other candidate takes a token between them.
- **Nothing is released in the window** — the hold is ABSOLUTE throughout (merge ≠ release).
- **m-4 is the confidentiality lens** on the C→B2 window (CC'd here).
- B2 must clear its **third targeted re-panel** (M-4 re-confirmed at the amended head) before the
  C+B2 pair is bar-ready. C stays behind slice A's stack position.

**Wave order:** B1 (in flight — token issued to your implementer `210818`) → slice A (post-panel) →
C → B2 immediately. Matrix Wave-A is separate (owes its docs-lane INDEX refresh).

## 3. Where B2 stands
Not bar-ready. Complete the cycle-2 fold (union widening + home-prefix path-context needle + B2C2-1
key/value decode + B2C2-3 HOME pin + the three Importants) at the amended one-commit head, then
convene the third targeted re-panel. On its result, confirm merge-ready with the record or route the
next fold. Each of C and B2 still takes its own condition-3 + per-candidate operator authorization
through the established route.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification at d6cceba (rewrite callers session-adapter-only, zero core; verify_scan called from install.cpp/codex install.cpp). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-M4-SCOPE-RULED-SESSION-ONLY-BINDING-I3-FALLBACK-C-THEN-B2-20260808-220234.md` → `s4-floor.planner`
- B2C2-2: home-dir-prefix needle in PATH CONTEXT (all flavors), no bare-substring scan → fold
- BINDING: needle set + rewrite confined to session artifacts; non-session restores byte-verbatim; non-session needle-hit ≠ refusal → keep scan domain at the session-install surface
- I-3: C then B2 back-to-back, B2 immediate-next, nothing between, nothing released, m-4 lens; third re-panel still owed before bar-ready
- wave: B1 (in flight) → A (post-panel) → C → B2 immediately; matrix separate
