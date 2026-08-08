## IMPL — Slice B2 (torn-tail A3.3 + the A5-reassigned CANON-2.6 staging-sidecar reader) proceeds from `ec9a2db` under the orchestrator's standing delegation; A3 four-check ceremony owed on BOTH anchors; `manifest.cpp` stays fence-2 OUT

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — B2 is in the locked plan (Task 9) plus the A5-reassigned reader; the orchestrator authorized it to proceed from `ec9a2db` under standing delegation with no new grant (`…-004229`); merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-C-VERIFIED-ROUTED-UP-B2-PROCEEDS-20260808-004229.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: DISPATCH — Slice B2 from exact base `ec9a2db2cfe55191f99efbcf12902a79d99e159e`; scope = Task 9 (torn-tail) + the A5 CANON-2.6 reader; the standing verification laws and the two ceremonies that bind this head

Slice C is verified and routed up; the orchestrator authorized B2 under standing
delegation (no new token — this sequences on the live `s4-floor-impl-2` authority, as
slices A and C did). Proceed.

## Base and branch
- Seed branch `s4-floor/b2-torn-tail` from EXACT `ec9a2db2cfe55191f99efbcf12902a79d99e159e`
  (head of `s4-floor/c-consent-no-carrier`) per the plan's restack rule (plan line 87).
- I confirmed at the bytes that B1 (`ff63e52`) is an ancestor of `ec9a2db`, so the plan's
  "codex branch 3 only after B1" dependency (line 203) is satisfied by the stack — B2 may
  proceed though B1's PR #15 is not yet merged (its merge is blocked only on the routed
  `.github` count gate, not on anything B2 needs).

## Scope — TWO components, both plan-covered

**Component 1 — Task 9 (torn-tail A3.3), plan line 205-211, verbatim scope:**
- `src/adapters/adapter.hpp`: `SessionRecord` gains
  `struct TornTail { std::string artifact; std::uint64_t bytes; }; std::vector<TornTail> torn_tails;`.
- `src/adapters/codex/codex.cpp` + `src/adapters/claude_code/claude_code.cpp`: the
  jsonl-artifact tail rule at collect for LIVE-flagged sessions — T = final segment after
  the last LF; branch 1 empty ⇒ verbatim; branch 2 valid JSON ⇒ retain + append exactly
  one LF; branch 3 invalid AND live ⇒ drop exactly T + record the fact; branch 4 invalid
  AND not-live ⇒ verbatim; interior segments NEVER inspected.
- `src/core/pack/pack.cpp`: each fact ⇒
  `Warning{kind:"TornTailDropped", path:<session id>, artifact, bytes}`.
- both `install.cpp`: branch-4 decode refusal typed `undecodable_line`
  (m-3 spelling marker at the consumer-review site).
- Tests: the collect suites (four branches × two legs, retained-prefix BYTE EQUALITY in
  EVERY branch; `torn_tail_dropped.bytes == len(T)` EXACTLY; a mid-file invalid line with
  a clean tail ⇒ verbatim, no fact), `tests/test_pack.cpp` + `tests/test_cli.cpp`
  (design §7 test 4: exact artifact/bytes in structure, default text, and JSON).

**Component 2 — the A5-reassigned CANON-2.6 staging-sidecar reader + repack-exact fixtures
(plan Amendment A5 part (3), line 72):**
- the collect-side consumer that reads the A9 staging sidecar and emits
  `locator: staging`, `tier: staged`, the ORIGINAL provenance chain + the MINTED staged
  identity, per CANON-2.6, plus the O1 `repack-manifest-exact` fixtures deferred out of
  slice C. Touched files per A5: `codex.cpp`, `claude_code.cpp`, `pack.cpp`, owner tests
  — all already in-universe and all overlapping Task 9's file set, so this folds into the
  same head cleanly.

## The two ceremonies that BIND this head
1. **A3 four-check anchor ceremony on BOTH anchors** (plan line 58: "B2 both anchors"):
   B2 touches both `codex.cpp` and `claude_code.cpp` (the C1-anchored collect files), so
   run the per-head four-check ceremony and recapture BOTH `_ADAPTER_SOURCE_ANCHORS`
   entries in `harness/bivharness/e3.py` at the final head — never batched, five-owner
   mutation receipts as established, burden-report duty per R-3.40 item (11). This is the
   head where the claude anchor recapture finally lands (line 59). Any edit to the anchor
   set or `e3.py` beyond this recapture is a NEW deviation, routed up before the edit.
2. **Fence-2**: `src/core/manifest/manifest.cpp` and `manifest.hpp` are OUT of every task
   (plan line 18) and stay fence-2-bound behind Arm-1's schema act. Per the orchestrator's
   direction: keep any fenced surface as a `SCOPE_DIFF` OUT row until the F+G signal — do
   not reach into `manifest.*`. The CANON-2.6 reader as scoped by A5 touches
   `codex.cpp`/`claude_code.cpp`/`pack.cpp` only, NOT `manifest.*`, so it stays inside the
   fence; if you find it cannot be built without a `manifest.*` reach, STOP and route up
   rather than crossing the fence.

## Standing verification laws (non-negotiable, cost-earned this run)
- The mechanical check is RUN, never asserted — every branch, every leg, exit status not
  printed text.
- The codex branch-3 fixture MUST drive liveness through B1's REAL derivation (plan line
  210); a branch-3 test green on a hardcoded liveness flag fails review.
- Retained-prefix byte equality in all four branches; `bytes == len(T)` exactly.
- Trace the runtime loop at the candidate bytes before calling any call-site
  single-shot; bind the production forwarding edge behind any injected test seam.

## Head exit
Failing tests per branch per leg first (8 fixtures + the interior-segment control + the
empty-file compose with B1's liveness), implement, green; one commit (one-commit law);
the A3 recapture at the final head; then the standing local Ubuntu 24.04 `linux/amd64`
Docker containerized suite as the CI leg (Actions unused), deltas disclosed in the `160811`
shape; publish the branch + draft PR under the standing publication disposition. Report per
the standing shape; I convene the team-of-5 panel on the committed bytes at the exact SHA.
No mutation receipts on the torn-tail rows themselves (plan line 211), but the A3 ceremony
DOES carry its five-owner mutation receipts.

ACTIONS_GIT_REF: no product/test edits at this seat — this is a dispatch relay; it + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the plan is unchanged since A6 (SHA d88a6b02…)
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-B2-DISPATCH-20260808-010412.md` → `s4-floor.implementer`
- Slice B2 from `ec9a2db2cfe55191f99efbcf12902a79d99e159e` → Task 9 (torn-tail) + A5 CANON-2.6 reader/repack-exact, one head
- A3 four-check ceremony on BOTH anchors + claude-anchor recapture at this head → binds; `manifest.*` fence-2 OUT
- slice C at `ec9a2db` → bar candidate at master; merge/release the operator's, hold ABSOLUTE
