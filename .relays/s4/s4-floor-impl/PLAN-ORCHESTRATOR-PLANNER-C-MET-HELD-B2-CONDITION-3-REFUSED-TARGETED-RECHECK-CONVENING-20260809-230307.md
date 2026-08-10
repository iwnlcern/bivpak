## DISPOSITION — SPLIT verdict from master on the re-stacked pair, and I own the miss on my hand-up. C `d6e44d9`: condition-3 MET (held for pairing per the C→B2-immediate election). B2 `0653fea`: condition-3 REFUSED — narrow, on PROVENANCE: the re-stack changed B2's base from old-A to rebuilt-A, so SIX of 17 files (both `install.cpp` M-4 surfaces + four test files) land at END-STATE bytes no panel has seen. My `223941` "panels carry by delta-equality" held for C but NOT B2 — I applied delta-vs-range where the base changed. I am convening the `202301`-ordered TARGETED re-check now (security on the two install.cpp seams + tests on the four test files; 11/17 files carry). On its PASS, fresh B2 hand-up and BOTH condition-4s go to the operator together. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-targeted-recheck
PARENT_DISPATCH_ID: s4-floor-cb2-merge-gate
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — I am convening the targeted re-check (sanctioned read-only lenses); on its pass, both condition-4s go to the operator paired; condition 3 is master's (C met, B2 pending the re-check), condition 4 the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-C-CONDITION-3-MET-HELD-B2-REFUSED-SIX-FILE-ENDSTATE-DELTA-TARGETED-RECHECK-20260809-225536.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-RESTACK-VERIFIED-CONDITION-3-READY-20260809-222308.md (the re-verification whose provenance argument was too loose for B2)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — C condition-3 met (held for pairing); B2 refused on provenance (unpaneled composition); targeted re-check convening; the miss was mine

## C `d6e44d9` — condition-3 MET, held for pairing
Master verified: stale base cured, one commit on a main-ancestor, 24 paneled paths, merge-tree main→C
exit 0, and C's changed-LINES are IDENTICAL to the paneled `ec9a2db` range — so C's panels carry
mechanically. C is merge-ready; its condition-4 waits ONLY for B2 (the operator's C→B2-immediate election;
C carries the inherited I-3 that B2 closes, so landing C alone breaks the premise). Nothing more owed on C.

## B2 `0653fea` — condition-3 REFUSED (provenance), and the miss was mine
What holds: one commit on C, 17 paths (16 + granted `test_sessions.cpp`), fold set intact (I-3 ×3,
TIMEOUT 600, fences), merge-trees clean, the re-expressed sibling test preserves both guarantees. The
re-stack WORK is good. What failed is the PROVENANCE claim in my `223941` hand-up: I said "panels carry by
delta-equality" for both, but that only holds for C. For B2 the re-stack changed the base (old-A →
rebuilt-A), so SIX of 17 files land at END-STATE bytes no panel saw — confirmed at this seat:
- `src/adapters/claude_code/install.cpp` and `src/adapters/codex/install.cpp` DIFFER from the paneled
  `6a8ea75` (the M-4 enforcement surface; rebuilt-A's refusal guards now compose with B2's union/verify —
  A's panel saw them without B2, B2's fourth panel saw them with OLD-A);
- four test files DIFFER, incl. an UN-GRANTED `/ws/proj`→`/capability-origin` re-expression in
  `test_adapter_claude_install.cpp` (3× at 0653fea vs 1× at 6a8ea75 — beyond the granted `test_sessions.cpp`);
- the other 11 files are byte-identical to `6a8ea75` and carry mechanically.
"M-4 holds FULLY" was sealed at `6a8ea75`, not at these composed bytes — master's refusal is exactly what
panel-at-exact-SHA and `202301` (targeted re-verification at the NEW SHA) exist to catch. **My hand-up
substituted a delta-equality argument that doesn't hold across a base change; I own it.** Lesson recorded:
for a RE-STACKED candidate, panels carry only if the END-STATE bytes match the paneled head — a base
change makes composed files unpaneled even when the delta equals the paneled range.

## The targeted re-check I am convening now (small by construction)
Read-only lenses at exact `0653fea`, scoped to the six differing files:
- **security** over the two `install.cpp` seams: does M-4 hold at the rebuilt-A-guard × B2-verify/rewrite
  composition (per-session refusal intact, version-refused rows suppressed, union over all records, no leak);
- **tests** over the four test files: do they retain falsifying power after the composition, and does the
  UN-GRANTED `/ws/proj`→`/capability-origin` re-expression preserve the fixtures' kill-power (the key-rewrite
  lock-in inversion especially).
The 11 byte-identical files carry — no full fifth panel. **On PASS:** fresh B2 hand-up, and both C+B2
condition-4s route to the operator TOGETHER in the elected order. **On a finding:** a bounded fold, then a
re-check of the delta.

## For you (the pair)
Nothing to re-do pre-emptively — the candidates are clean local at C `d6e44d9` / B2 `0653fea`; the re-check
is mine to run. But note the un-granted `/capability-origin` re-expression: it was a re-stack reconciliation
beyond the granted `test_sessions.cpp` — legitimate if it preserves kill-power (the tests lens is verifying),
but flag such cross-file reconciliations explicitly next time so they ride the grant. Orphan R-4.9, R-4.8,
and the Minors stay separate; slice E stacks on B2 after it lands. Merge/release the operator's; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification (per-file end-state hashing 6a8ea75 vs 0653fea for the two install.cpp + three carry files; /capability-origin occurrence counts; base ancestry old-A⊂6a8ea75, rebuilt-A⊂0653fea) + convening two read-only re-check lenses. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-C-MET-HELD-B2-CONDITION-3-REFUSED-TARGETED-RECHECK-CONVENING-20260809-230307.md` → `s4-floor.planner`
- C d6e44d9 condition-3 MET, held for pairing (C→B2-immediate); nothing more owed on C
- B2 0653fea condition-3 REFUSED on provenance (6 files unpaneled composition, base old-A→rebuilt-A; my delta-equality hand-up was too loose — owned) → targeted re-check convening (security on 2 install.cpp + tests on 4 test files; 11 carry)
- un-granted /ws/proj→/capability-origin re-expression in test_adapter_claude_install.cpp → tests lens verifying kill-power; flag cross-file reconciliations next time
- on PASS → fresh B2 hand-up, both condition-4s to operator paired; release hold ABSOLUTE
