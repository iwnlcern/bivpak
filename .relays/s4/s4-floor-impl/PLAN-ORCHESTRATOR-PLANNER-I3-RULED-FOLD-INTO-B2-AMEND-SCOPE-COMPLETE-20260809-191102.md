## DISPOSITION — master RULED I-3: FOLD into B2's amend (symmetric key-decode); deferral REFUSED. This completes the amend scope I held pending. Fold ALL of it in ONE commit: I-3 (verify_scan + rewrite_jsonl decode/rewrite JSON KEYS, modeled on your own verify_whole_document_bytes) + INVERT the lock-in test + F2 (Codex parent map + de-mask) + F3 (Codex child-id falsifier) + the already-authorized TIMEOUT 600 line. Then request the FOURTH targeted re-panel — M-4 must hold FULLY. B2 stays HELD until it passes; the C→B2 wave holds behind it. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-i3-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-third-repanel-fold
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — master ruled I-3 folds (it STRENGTHENS enforcement; no scope/wave/policy election moves); the amend is the pair lifecycle; the fourth re-panel gates bar-readiness; merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-I3-RULED-FOLD-INTO-B2-SYMMETRIC-KEY-DECODE-20260809-190203.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-floor-b2-third-repanel-f9675ea.md (panel record); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-THIRD-REPANEL-NOT-BAR-READY-FOLD-F2-F3-I3-ROUTED-20260809-185502.md (F2/F3 fold + I-3 routed up)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — I-3 ruled FOLD (symmetric key-decode + invert the lock-in test); complete B2 amend scope; fourth re-panel next

## The ruling (master `190203`, family-invariant owner)

I-3 folds into B2 — deferral refused (no carrier blocker, unlike R-4.8; a confirmed Critical
origin-PATH disclosure with an in-scope one-mechanism fix does not sit open behind the hold). The fix,
modeled on B2's OWN `verify_whole_document_bytes` (`decode_keys=true`):
- **`verify_scan`:** decode JSON object KEYS (`decode_keys=true`), apply the needle set to the decoded
  keys — the two verify arms symmetric.
- **`rewrite_jsonl`:** rewrite keys under the pair-set exactly as values are rewritten.
- **INVERT the lock-in test:** `test_adapter_claude_install.cpp:534-569` asserts
  `"/ws/proj":"key-must-not-change"` SURVIVES with `outcome==installed` — that assertion enshrines the
  leak and is PART OF THE DEFECT. The amended test must assert the origin key is REWRITTEN under the
  pair-set (or the row REFUSES). A test enshrining a Critical is never a constraint on its fix.

## Complete B2 amend scope — ONE commit

Land all of the following in the single amend on the held line, then rerun suites honestly green and
republish PR #23:
1. **I-3** — symmetric `verify_scan`/`rewrite_jsonl` key decode+rewrite + the inverted lock-in test.
2. **F2** — map the Codex parent id in the rewrite id-map to the parent's installed id when the parent
   is in the image (so it rewrites, not refuses), and de-mask `test_adapter_codex_install.cpp:1659-1717`
   (collect-realistic body carrying `parent_thread_id`). **Master pre-flagged, per my routing:** if the
   fix surfaces the definition question — is a session's OWN `parent_thread_id` an origin disclosure to
   rewrite, or a self-reference to preserve — that is family-invariant territory; **route it UP BEFORE
   folding an answer**, do not guess.
3. **F3** — add the Codex cross-session child-id union falsifier (mirror
   `test_adapter_claude_install.cpp:2210`).
4. **TIMEOUT 600** — the already-authorized one-line `harness/CMakeLists.txt` change, if not already on
   this line.
Minors (valid_utf8 divergence, cross-pair re-scan, blank-line/empty-artifact edges) at your discretion
or recorded as residuals — not blocking.

## Then the fourth re-panel
On republish, request the **FOURTH targeted re-panel** — M-4 must hold FULLY at that head (I-3 closed,
no key-arm leak; F2 self-refusal gone; F3 covered). On its pass B2 is bar-ready and the
C→B2-immediate pair proceeds to condition-3 hand-ups + per-candidate operator authorizations. All
operator elections stand unmoved (C→B2 back-to-back; scope + session-only line; TIMEOUT 600). R-4.8 and
the disclosed Minors remain separately carried. Merge/release the operator's; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing; the amend is your act.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-I3-RULED-FOLD-INTO-B2-AMEND-SCOPE-COMPLETE-20260809-191102.md` → `s4-floor.planner`
- I-3 RULED FOLD → verify_scan + rewrite_jsonl key decode/rewrite (model: verify_whole_document_bytes) + INVERT the lock-in test (key rewrites or row refuses)
- complete amend scope, ONE commit: I-3 + F2 (parent map + de-mask; route the self-reference invariant question UP if it surfaces) + F3 (Codex child-id falsifier) + TIMEOUT 600
- then the FOURTH re-panel (M-4 must hold fully) → on pass B2 bar-ready, C→B2-immediate proceeds
- R-4.8 + Minors separate; operator elections unmoved; release hold ABSOLUTE
