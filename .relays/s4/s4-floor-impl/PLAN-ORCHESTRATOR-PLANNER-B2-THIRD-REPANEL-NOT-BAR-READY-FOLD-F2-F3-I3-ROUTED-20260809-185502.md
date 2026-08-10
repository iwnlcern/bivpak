## DISPOSITION (fold routing) — B2's third targeted re-panel is COMPLETE at `f9675ea` and B2 is NOT bar-ready: M-4 does NOT hold. Three material findings, all byte-verified at my seat. Fold F2 (Codex parent verify/rewrite self-refusal — B2-introduced, must-fix) and F3 (Codex child-id coverage gap) — both in-universe, yours. The Critical F1 (the I-3 jsonl key-arm origin leak) is routed UP to master with a fold recommendation; land it in the SAME amend if master concurs. The amended head owes a FOURTH targeted re-panel. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-third-repanel-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-third-repanel-request
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay for F2/F3 (in-universe folds, yours); F1 (I-3) is an origin-disclosure-family invariant routed to master; B2 is not bar-ready until M-4 holds and the fourth re-panel passes; merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-B2-PRECEDENCE-VERIFIED-THIRD-REPANEL-REQUESTED-20260809-183203.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-floor-b2-third-repanel-f9675ea.md (the full panel record); ../../../pdc/master/relays/s4-build-standup/SITREP-ORCHESTRATOR-PLANNER-B2-THIRD-REPANEL-M4-FAILS-I3-CONFIRMED-AT-SHA-FOLD-RECOMMENDED-20260809-185149.md (I-3 routed up)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — B2 not bar-ready; fold F2 (Codex parent self-refusal) + F3 (Codex child-id falsifier); I-3 routed up; fourth re-panel owed

The third re-panel (security + correctness + tests, cold read-only lenses, cumulative `ec9a2db..f9675ea`,
M-4 under union-scope acceptance) found M-4 does NOT hold. Full record:
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-floor-b2-third-repanel-f9675ea.md`. The
precedence fix, union assembly, store_root, decode logic, torn-tail wiring, and the precedence
falsifier all checked SOUND — good work there. Three material findings remain.

## Fold now (in-universe, yours)

**F2 — Correctness, MUST-FIX (byte-verified): Codex parent verify/rewrite asymmetry → self-refusal of a
legitimate session.** B2 ADDED `image_origin_id_set.insert(*record.original_session_ids.parent)`
(codex/install.cpp:473-474 — the verify/refusal set; confirmed added in the `ec9a2db..f9675ea` diff),
but the Codex rewrite id-map (`rewrite_ids`, :404-431) has primary/primary_identity/child ids and NO
parent. A genuinely-collected Codex session whose rollout head carries `parent_thread_id` (= the parent
id — that is how `parent` is populated, codex.cpp:258-262) will have that id in the verify set,
un-rewritten → `origin_id_hits>0` → `verify-hits` → the session REFUSES ITSELF. B2 converted a
pre-existing silent leak into a hard refusal of legitimate data — neither is correct. **Fix:** map the
parent id in the rewrite id-map to the parent's installed id when the parent is in the image, so it is
rewritten (not refused) and the session installs. Design the not-in-image case explicitly (a session's
own `parent_thread_id` referencing an un-collected parent) — if that raises an invariant-definition
question (does a session's OWN parent reference count as origin disclosure requiring rewrite, or is it a
self-reference), route it UP; do not guess. **De-mask the test:** `test_adapter_codex_install.cpp:1659-1717`
sets `parent` but crafts the origin body WITHOUT `parent_thread_id` (an input real `collect` cannot
produce), so it never exercises the self-refusal — make the fixture collect-realistic so it does.

**F3 — Tests, IMPORTANT: Codex child-id union member unverified.** Production inserts Codex child ids
into the union (codex/install.cpp:476-478) and Claude has a cross-session falsifier
(`test_adapter_claude_install.cpp:2210`), but Codex has none — every Codex union test clears children or
uses same-session children, so deleting the Codex child-id insert fails zero tests. Add a Codex
cross-session child-id falsifier mirroring the Claude one (a recipient session referencing another
session's `child.original_id`/staged `child_identity`, asserting `origin_id_hits>0`/refused).

## Routed up — F1 (the Critical), fold into the SAME amend if master concurs

**F1 — Security, CRITICAL: the I-3 jsonl key-arm origin-path leak.** `verify_scan` (rewrite_common.cpp:1044)
uses `decode_keys=false`, so JSON object KEYS are neither decode- nor raw-scanned, and rewrite leaves
keys verbatim — an origin PATH at a JSON key survives into the installed session (locked in by the
passing `test_adapter_claude_install.cpp:534-569`). This is the inherited I-3. It is an
origin-disclosure-family invariant = master's call (144700), so I routed it UP (`185149`) with a
recommendation to FOLD it into B2 — the fix is fully in-scope and symmetric with your own new
`verify_whole_document_bytes` (`decode_keys=true`): make `verify_scan` (and `rewrite_jsonl`) decode keys
too. **Hold the amend for master's I-3 ruling; if master concurs, land F1 + F2 + F3 in ONE commit** so a
single fourth re-panel covers all. If master defers I-3, fold F2 + F3 alone.

## Minors (note; your discretion / residual)
Two divergent `valid_utf8` definitions (adapter.hpp vs rewrite_common.cpp:650-683 — fail-closed, latent,
worth unifying); JSONL cross-pair re-scan vs raw single-pass (rare double-rewrite); blank-interior-line
refusal; live single-partial-record → empty artifact. All fail-closed/edge/non-corrupting — address at
discretion or record as residuals; not blocking.

## Consequence
B2 is NOT bar-ready. The amended head owes a FOURTH targeted re-panel (verify/rewrite semantics change
again) — request it on your republish as before. The C→B2-immediate pair does not proceed until it
passes. R-4.8 and the two disclosed Minors remain separately carried. Merge/release the operator's; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — the panel was read-only lenses + my byte-verification (verify_scan/verify_whole_document_bytes decode_keys, codex parent verify-insert vs rewrite_ids, the passing key test) at f9675ea. This relay + the panel record + the INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay, the reviews/ panel record, and .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-THIRD-REPANEL-NOT-BAR-READY-FOLD-F2-F3-I3-ROUTED-20260809-185502.md` → `s4-floor.planner`
- F2 (Codex parent verify/rewrite self-refusal, B2-introduced, must-fix) → fold: map parent in rewrite id-map + de-mask the test; route the not-in-image invariant question UP if it surfaces
- F3 (Codex child-id union coverage gap) → fold: add the cross-session Codex child-id falsifier
- F1/I-3 (jsonl key-arm origin leak, Critical) → routed UP to master (`185149`); if master concurs, fold symmetric verify_scan/rewrite_jsonl key-decode into the SAME amend
- fourth re-panel owed on the amend; B2 not bar-ready; C→B2 wave held; panel record in reviews/; release hold ABSOLUTE
