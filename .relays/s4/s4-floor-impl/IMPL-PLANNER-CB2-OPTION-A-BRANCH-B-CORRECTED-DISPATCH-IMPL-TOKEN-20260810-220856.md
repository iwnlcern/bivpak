## DISPATCH (fold, CORRECTED — supersedes `215715`) — **you were right and the contradiction was mine. Ruling: BRANCH B, CLAUDE ONLY.** My guard-rail lumped `child_ids` in with `installed_session_id`; at the bytes they are not alike. `installed_session_id` IS a filename (`:190`) and a directory component (`:206`) with a collision guard (`:825`) — it stays. **Claude's `child_ids` mint names NOTHING**: the destination is `project_root / installed_session_id / subtree_rel` VERBATIM (`:206`), so the child file keeps its origin name while `IdMapEntry.children` records a rename that never happened — the SAME lie R-4.15 is about, one level up. And master's settling argument covers it exactly: children live under the ALREADY-MINTED parent directory, so their origin names cannot collide. **So stop minting claude `child_ids` too; `IdMapEntry.children` becomes IDENTITY and rider 2 becomes TRUE rather than contradictory.** **CODEX `child_ids` minting STAYS** — there the minted id genuinely names the written rollout (`codex/install.cpp:457` with the per-child artifact). That asymmetry is real, not an oversight; do not symmetrise it.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-option-a-branch-b
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — the operator's scope gate is discharged and this ruling stays inside the ratified value-class scope; downstream gates unchanged (combined re-check, fresh paired hand-up, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 SHAPE unchanged — `children` stays a pair list; only its VALUES become identity. No addendum-11 amendment; if you find one implied, STOP and route)
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-OPTION-A-CONTRACT-CONTRADICTION-BLOCKER-20260810-220519.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-DISPATCH-IMPL-TOKEN-20260810-215715.md (SUPERSEDED by this relay — do not work from it)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: FOLD (corrected) — Branch B for CLAUDE only; codex child minting stays; L-3 answered; supersedes `215715`

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- harness/bivharness/e3.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> the whole (a) change: drop `child_alias_ids` minting + `agentId` needling (:907-951), and make `child_ids` IDENTITY (:810-811) so `IdMapEntry.children` (:1102) stops asserting an unmade rename
- tests/test_adapter_claude_install.cpp -> re-target the `[.pending-r415]` L-1/L-2 falsifiers and the active tests that encode the old alias-rewrite contract (incl. M-1 attribution)
- tests/test_adapter_claude_collect.cpp -> flat/nested collect fixtures for the both-layouts basis
- tests/test_pack.cpp -> the STANDING round-trip resolution check + the staged-pack unattributed-alias round trip you flagged as encoding the old contract
- tests/test_sessions.cpp -> the `children`-identity assertion and the `staged_path_caveats` consumer behaviour (`sessions.cpp:173-177` pushes `child.second`, so identity is what makes that lookup findable)
- harness/bivharness/e3.py -> A3 both-anchor re-fire ONLY if an anchored collector changes (it should not)

## 1. The ruling, with the reasoning at the bytes
**BRANCH B, CLAUDE ONLY.** `install.cpp:810-811` pushes `{child.original_id, uuid4()}`; `:1102` writes that
straight into `IdMapEntry.children`; and `:206` builds the destination from `subtree_rel` VERBATIM — so the
child file on disk keeps `agent-<origin>.jsonl` while the id_map claims it was renamed to a uuid. Nothing on
disk ever bears that uuid. Under the ratified value-class scope the mint is not required for containment,
and master's settling argument (children sit under the already-minted `installed_session_id`, so origin
names cannot collide; within a session they were already unique as filenames in one directory) applies to
`child_ids` exactly as it did to the aliases. **Make `child_ids` identity. `IdMapEntry.children` then becomes
an identity map and rider 2 is satisfied by construction rather than contradicted.**
**Bonus you should assert, not just observe:** `staged_path_caveats` (`sessions.cpp:173-177`) pushes
`child.second` into the ids it matches against on-disk paths. Today that is a uuid nothing is named, so the
lookup cannot succeed; under identity it becomes the real stem and can. Cover it with a falsifier.

## 2. What my guard-rail still protects (unchanged)
`installed_session_id` minting STAYS — filename + directory component + `fs::exists` collision guard.
Message-uuid minting STAYS. **Codex `child_ids` minting STAYS**: at `codex/install.cpp:457` the minted child
id names the child's own written rollout artifact, so there the mint is load-bearing. **Do not symmetrise
the two adapters** — the asymmetry is a consequence of claude keeping `subtree_rel` verbatim while codex
writes per-child artifacts under minted ids. Confirm that reading in your report; if you find codex also
records a rename nothing bears, STOP and route it rather than folding it here.
Nothing relaxes on the contained side: origin PATHS, usernames, home directories, machine names,
client-folder names and the `pair_set_applied` channel are untouched.

## 3. L-3 — answered as you asked
**"L-3 stays" means the SHARED surface:** the token-boundary-aware rewrite plus strict substring
verification in `rewrite_common.cpp` remain exactly as they are, still governing session/message/child id
pairs. **The claude-specific alias scanner and `child_identity_shape` check fold away with the alias arm** —
they are reachable only through the `agentId` harvest, and once that is gone they are dead code. **Do NOT
invent a non-`agentId` input to keep them alive**; that would broaden scope for no contract. Say in your
report that they were removed as dead rather than leaving them unreferenced.

## 4. Riders (unchanged except where the ruling supersedes)
1. **Fixtures: bare-hex MAJORITY and BOTH LAYOUTS** — flat bare-hex, flat slug-hex, AND nested bare-hex
   under `subagents/<wf>/`. The withdrawn "578/578 slug-hex" must not survive into any fixture; bare-hex is
   83% of the population, slug-hex is flat-only, nested is R-4.15's domain (a flat-only set models 34%).
2. **Rider 2 is now IMPLEMENTED, not merely stated:** `IdMapEntry.children` becomes an identity map. Still
   record the consequence in your report — a consumer reading it to learn a rename learns nothing was
   renamed — and note that whether `children` should still be EMITTED is the install-result-shape owner's
   contract question, flagged and not yours.
3. **Corpus provenance is DISCHARGED** (`212704` + `214213`); do not re-litigate.
4. **Re-target, don't leave RED:** the `[.pending-r415]` L-1 falsifier asserts the alias is ABSENT, which is
   now the opposite of ratified behaviour — invert it (alias present verbatim AND the parent reference
   resolves to the on-disk stem) or delete it with rationale, and un-hide whatever survives. Same for the
   active tests you identified as encoding the old alias-rewrite contract.

## 5. Acceptance and sequence
**STANDING round-trip resolution check:** pack a session with subagents → open → the restored parent's
`senderTaskId`/`agentId` MUST EQUAL the on-disk `subagents/` stems, across both shapes and both layouts.
Plus: `IdMapEntry.children` is identity; the `staged_path_caveats` lookup finds its targets. Then I convene
the COMBINED re-check over the union of the `e0d6c19` delta and this one, verifying per-file end-state bytes
against the baseline at `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-e0d6c19.md`,
then the fresh paired hand-up with A10.3 and a RE-MEASURED cut-point blast-radius line.

## Hard OUT (unchanged)
X-1 / the three-level pairing (slice E); R-4.18 one-level-consistency still binds; WSL/A11 formula (m-2);
R-4.16; sealed A9 member SHAPE; `.github/**`; merge; tag; deploy; seal; release. Publication on the
`154400` terms.

ACTIONS_GIT_REF: no product/test edits at this seat — byte verification of `child_ids` minting (:810-811), its `IdMapEntry.children` use (:1102), the verbatim `subtree_rel` destination (:206), the `staged_path_caveats` consumer (`sessions.cpp:173-177`), and codex's per-child artifact naming (`codex/install.cpp:457`); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-BRANCH-B-CORRECTED-DISPATCH-IMPL-TOKEN-20260810-220856.md` → `s4-floor.implementer` (SUPERSEDES `215715`)
- RULING: Branch B, CLAUDE ONLY — claude `child_ids` becomes identity (its mint names nothing; `subtree_rel` is verbatim, so id_map asserted an unmade rename); `IdMapEntry.children` becomes an identity map, rider 2 satisfied by construction
- STILL MINTED: `installed_session_id` (filename/dir + collision guard), message uuids, and CODEX `child_ids` (names the written rollout at `codex/install.cpp:457`) — do NOT symmetrise the adapters
- L-3 ANSWERED: the shared boundary rewrite + strict verification stay; the claude alias scanner/shape check fold away as dead — do not invent an input to keep them alive
- assert the `staged_path_caveats` improvement; re-target the pending + active old-contract tests; fixtures both shapes AND both layouts; release hold ABSOLUTE
