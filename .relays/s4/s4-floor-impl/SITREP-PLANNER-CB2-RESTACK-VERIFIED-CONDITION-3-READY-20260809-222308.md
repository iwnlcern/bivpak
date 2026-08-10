## SITREP — targeted re-verification PASSES at both restacked heads: C `d6e44d9` and final B2 `0653fea` are delta-EXACT to their paneled ranges, fold sets intact, anchors byte-carried, fences live, merge trees clean into current main. Both are merge-ready; requesting fresh condition-3 hand-ups, C first, B2 immediately after.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-condition3-ready
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack-resume
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — condition-3 is master's per candidate and condition-4 the operator's; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-RESTACK-RESUME-COMPLETE-20260809-221130.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: RE-VERIFICATION PASS — C d6e44d9e5ec4ff48e5121a9674ef7788eca9e881 (PR #22) and B2 0653fea400e83a59f4c3a9d7983510222e9159ec (PR #23); route the fresh condition-3s in the elected order

The restack resume is complete and I ran the dispatched targeted re-verification at the
committed bytes at both new exact SHAs (not on the report's word). Every check passes.

## Verified at the bytes at this seat
- **Heads and topology:** remote branches + draft PRs at exactly C `d6e44d9` / B2
  `0653fea`; each exactly ONE commit, subjects preserved; C's parent is an ancestor of
  current `main`; rebuilt-A `33153137` is in C's ancestry (the stale-base defect is gone).
- **Delta-equality EXACT:** C's range = its paneled 24 paths byte-for-byte (diff of the
  sorted lists is empty); B2's range = its paneled 16 paths + the one granted
  `tests/test_sessions.cpp`, no eighteenth path. Fences live: no `manifest.*`, no
  `.github/**` in either range.
- **Fold set intact at 0653fea:** `decode_keys=true` at all three `JsonValueRewriter`
  sites (I-3); `TIMEOUT 600`; the F2 prepared-parent map; the longest-source-first pair
  sort; the HOME pins in `test_pack.cpp`. The re-expressed sibling test asserts the ruled
  per-session surface (`verify-hits`/`origin_path`, counters intact) alongside the
  preserved refusal row — master's B2-1 ruling and A-BL1's guarantee both hold, per the
  orchestrator's `214526` concurrence.
- **Anchors carried byte-for-byte:** both collectors AND `harness/bivharness/e3.py` are
  byte-identical between paneled `6a8ea75` and final `0653fea` (hashed both sides at this
  seat), and the recomputed collector SHA-256s match the e3.py literals — the
  no-anchor-refire claim is TRUE, and the A3 ceremony's pins remain exact at the merging
  bytes.
- **Merge path clean:** `git merge-tree` at CURRENT `main` → C: conflict-free; C → B2:
  conflict-free. The implementer's receipts also cover remote `8981bfd` → C.
- **Evidence chain (implementer's `221130`, spot-verified):** host suites 14/14 at both
  heads; both heads' local Ubuntu 24.04 amd64 Docker runs green on every substantive and
  narrowed gate, with only the standing ruled exceptions (the one Rosetta probe case; the
  overlay sentinels; the separately-routed historical `223/0` count gate — canonical
  Catch2 now 268/1 at C and 322/1 at B2); three-test repro 41/41 GREEN; ESCALATION_SCAN
  all-no.

## The request
Route the FRESH condition-3 hand-ups for the restacked pair in the elected order:
**C `d6e44d9` (PR #22) first, B2 `0653fea` (PR #23) immediately after** — each then takes
the operator's per-candidate condition-4 through the established route. Content
provenance for master's check: C's panel record at `eadc88f` + re-check at `ec9a2db`
carry to `d6e44d9` by delta-equality (the delta is byte-exact to the paneled range on a
rebased base); B2's four panels (final PASS at `6a8ea75`, M-4 holds fully) carry to
`0653fea` the same way, with the one authorized test re-expression executed under master's
standing per-session ruling and the orchestrator's explicit concurrence.

Orphan R-4.9, R-4.8, and the disclosed Minors remain separately carried. After B2 lands,
the floor's remaining plan work is slice E (Tasks 10-11), which stacks on B2 per the plan.
Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — the re-verification was read-only git plumbing (rev-parse/log/diff/show/shasum/merge-tree at d6e44d9 and 0653fea); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-RESTACK-VERIFIED-CONDITION-3-READY-20260809-222308.md` → `s4.orchestrator-planner`
- C `d6e44d9` (PR #22) + B2 `0653fea` (PR #23) → re-verification PASS; fresh condition-3 hand-ups requested, C first, B2 immediately after
- panel provenance carries by byte-exact delta-equality; the one test re-expression executed under the standing ruling with concurrence on record
- orphan R-4.9 / R-4.8 / Minors separate; slice E next after B2 lands; merge/release the operator's, hold ABSOLUTE
