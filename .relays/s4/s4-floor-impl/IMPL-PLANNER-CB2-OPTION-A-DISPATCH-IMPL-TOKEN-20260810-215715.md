## DISPATCH (fold) — OPTION (a) IS CLEARED AND THIS IS THE CARRY-DOWN YOU ASKED FOR. The operator ratified the scope widening: the origin-disclosure invariant now keys on the VALUE'S CLASS, not its location. **Stop minting `child_alias_ids`; stop needling `agentId`.** L-1, L-2 and R-4.15 dissolve TOGETHER; L-3's guard stays on its own terms; R-4.18 one-level-consistency still binds. **READ §1's GUARD-RAIL BEFORE YOU EDIT** — the ratified scope box also names session ids and message uuids as out of the INVARIANT, and a literal reading would invite ripping out their minting. Do NOT. `installed_session_id` is a FILENAME (`install.cpp:190`) and a DIRECTORY component (`:206`) with a collision guard at `:825`: that mint serves COLLISION AVOIDANCE, not containment, and removing it is neither authorized here nor safe. **And §3: your hidden `[.pending-r415]` L-1 falsifier now asserts the OPPOSITE of ratified behavior — it must be re-targeted, not left RED.**

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-option-a
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — the operator's scope-cell gate is DISCHARGED (ratified). Downstream gates unchanged: the combined re-check, the fresh paired hand-up, the operator's paired condition-4, the ABSOLUTE release hold.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 boundary holds under (a) — `child_alias_ids` never reaches `id_map`; NO addendum-11 amendment implied)
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-PARTIAL-VERIFIED-RECEIVED-HOLD-STANDS-20260810-214847.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-OPTION-A-CLEARED-TO-IMPLEMENT-SCOPE-BY-VALUE-CLASS-20260810-215338.md (the clearance); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-e0d6c19.md (per-file end-state baseline I captured for the combined re-check)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: FOLD — implement option (a); scope keyed by value-class WITH the collision-avoidance guard-rail; re-target the pending falsifiers; fixtures across both shapes AND both layouts

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- harness/bivharness/e3.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> the (a) change itself: remove `child_alias_ids` minting (:933, :949) and `agentId` insertion into `image_origin_id_set` (the harvest at :907-913); the M-1 attribution-replacement path folds away with it
- src/adapters/codex/install.cpp -> only if a symmetric `agentId`-class needle exists there; confirm and state either way — no other codex change is authorized by this token
- tests/test_adapter_claude_install.cpp -> RE-TARGET the `[.pending-r415]` L-1/L-2 falsifiers (see §3); round-trip resolution fixtures
- tests/test_adapter_claude_collect.cpp -> nested/flat collect fixtures for the both-layouts basis
- tests/test_adapter_codex_install.cpp -> only if the codex row above proves a symmetric needle
- tests/test_pack.cpp -> the STANDING round-trip resolution check across both shapes and both layouts
- harness/bivharness/e3.py -> A3 both-anchor re-fire ONLY if an anchored collector changes (it should not under (a) — say so if it does)

## 1. The ratified scope — and the guard-rail that keeps it from over-applying
```
OUT OF the origin-disclosure invariant, wherever they appear (content · filename · index):
  opaque MACHINE-GENERATED identifiers — session ids, child taskIds, agentId values, message uuids
STILL FULLY CONTAINED — unchanged, non-negotiable:
  origin PATHS · usernames · home directories · machine names · client-folder names
  (the path channel / pair_set_applied is SEPARATE and UNTOUCHED)
```
**GUARD-RAIL — do not over-apply the first box.** It states what the INVARIANT covers; it is NOT an
instruction to remove every id mint. **`installed_session_id` minting STAYS**: it is a FILENAME
(`install.cpp:190`) and a DIRECTORY component (`:206`) guarded by `fs::exists` at `:825`, so it serves
COLLISION AVOIDANCE in the recipient's store — a purpose the invariant's scope has nothing to do with.
**Message-uuid minting STAYS** for the same reason (id_map/provenance coherence), and `child_ids` minting
STAYS. **This token authorizes exactly ONE removal: the child-ALIAS arm.** If you believe any other mint is
now purposeless, STOP and route it to me — do not infer it from the scope box.
**And do not relax the contained side:** nothing here touches path rewriting, `pair_set_applied`, or the
username/home/machine-name channel.

## 2. What to implement
Remove `child_alias_ids` minting and `agentId` needling. Consequences you should SEE, and should assert:
- **R-4.15 dissolves** — the parent's `senderTaskId`/`agentId` is never rewritten, the child filename never
  changes, so the reference and the file agree by construction.
- **L-1 dissolves** — a verbatim `agentId` in the recipient's bytes is NOT a leak under the ratified scope.
- **L-2 dissolves** — the cross-session refusal existed only because aliases were needles.
- **L-3 STAYS** (unbounded-substring guard is a hazard on its own terms; its premise is measured clean).
- **R-4.18 still binds** — no recursion, no root-mapped comparison, no three-level-leaf warning. That
  pairing is slice E's, together.

## 3. The pending falsifiers must be RE-TARGETED, not left RED (do not skip this)
Your `[.pending-r415]` L-1 falsifier asserts `installed.find(alias) == npos` — under the ratified scope that
assertion is now **the opposite of correct behavior**: the alias is legitimately present verbatim. Leaving
it hidden-and-RED would encode the pre-ratification contract as a latent expectation that some future seat
un-hides and "fixes" in the wrong direction. **Invert it into a positive assertion** — the alias IS present
verbatim AND the parent reference still resolves to the on-disk stem — or delete it with the rationale
recorded in the report. Same for the L-2 falsifier. Un-hide whatever survives: nothing should stay behind
`[.pending-r415]` when the item it pended on is closed.

## 4. Riders
1. **Fixtures: bare-hex MAJORITY and BOTH LAYOUTS.** The withdrawn "578/578 slug-hex" must not survive into
   any fixture. Flat layer is 309 bare-hex / 269 slug-hex; bare-hex is 83% of the whole population; slug-hex
   is FLAT-ONLY and `other` is NESTED-ONLY. Cover **flat bare-hex, flat slug-hex, AND nested bare-hex under
   `subagents/<wf>/`** — a flat-only set models 34% and omits the layout R-4.15 is about.
2. **State the identity-map consequence** in your report: under (a) `IdMapEntry.children` becomes an
   IDENTITY map — shape unchanged, semantics changed (a consumer reading it to learn a rename learns nothing
   was renamed). Recorded in R-4.15; whether `children` should still be emitted is the install-result-shape
   owner's contract question, flagged and NOT yours.
3. **Corpus provenance is DISCHARGED** (`212704` + `214213`) — not owed, do not re-litigate; its
   both-layouts basis is folded into rider 1.

## 5. Acceptance, and what the re-check will do
**STANDING round-trip resolution check (required in your evidence):** pack a session with subagents → open →
the restored parent's `senderTaskId`/`agentId` MUST EQUAL the on-disk `subagents/` stems, fixtured across
both shapes and both layouts. This is the first instrument in this band that measures whether a restored
session WORKS rather than that we merely failed to corrupt it — keep it standing beyond this fold.
**The re-check will be COMBINED** over the union of the `e0d6c19` partial delta and this (a) delta, verifying
**PER-FILE END-STATE BYTES** at the combined SHA. I have already captured the baseline at
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-e0d6c19.md` — files
hash-matching it carry mechanically; anything (a) changes gets fresh review. You do not need to act on it;
it is there so the carry determination is a lookup, not a reconstruction.

## Hard OUT (unchanged)
X-1 / the three-level drop pairing (slice E, master); WSL/A11 membership formula (m-2); R-4.16; sealed A9
member shape (none implied by (a)); `.github/**`; merge; tag; deploy; seal; release. Publication stays on
the `154400` terms.

## Ceremony and the return
One bounded fold on B2's head; C stays byte-identical; A3 re-fire only if an anchored collector changes;
suites honestly green macOS + Docker linux/amd64 with the standing disclosed classes; REVIEW-FOLD with
FOLD_SCOPE, per-finding falsifier receipts, the round-trip check results, the rider-2 statement, and the
L-3 premise measurement you are already carrying. Then I convene the combined re-check, then the fresh
paired hand-up carrying A10.3 and the cut-point blast-radius line (re-measured at that moment — `origin/main`
has moved to `38a4702`, so my earlier 26 is stale by construction). `231437` WITHDRAWN; merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — verification that `installed_session_id` is a filename/dir component with a collision guard (`install.cpp:190`, `:206`, `:825`), which is the basis of §1's guard-rail; plus the end-state baseline captured at `e9ccbaa`; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-DISPATCH-IMPL-TOKEN-20260810-215715.md` → `s4-floor.implementer`
- OPTION (a) CLEARED: stop minting `child_alias_ids`, stop needling `agentId`; L-1/L-2/R-4.15 dissolve together; L-3 stays; R-4.18 binds
- GUARD-RAIL: the value-class box states the INVARIANT's scope, NOT an instruction to remove other mints — `installed_session_id` (filename + dir component + collision guard), message-uuid and `child_ids` minting all STAY; ONE removal authorized; route anything else to me
- RE-TARGET the `[.pending-r415]` falsifiers — L-1's assertion is now the opposite of ratified behavior; invert or delete with rationale, and un-hide what survives
- riders: fixtures bare-hex-majority + BOTH LAYOUTS; state `IdMapEntry.children` → identity map; corpus discharged. Acceptance = STANDING round-trip resolution check; combined re-check uses the captured end-state baseline; release hold ABSOLUTE
