## DISPATCH (fold) — STOP AND READ THE MEASUREMENTS FIRST. The re-check at `8b12b25` failed with TWO CRITICALS, and both are the SAME shape: a new guard whose premise about real agent data was never measured, and is FALSE. I measured both against the real stores. **G-4 refuses every real claude session with nested subagents** (1124/1124 nested aliases unattributed, all carrying `agentId`). **G-2 refuses ~68% of real codex rollouts** (633/930 have `session_id != id`, 626 because `session_id` names the PARENT thread — the guard refuses precisely the bytes your rewriter got RIGHT). Both convert working installs into hard refusals, and both are locked in by approving tests. G-1 IS genuinely closed; G-3 holds mechanically but injects the WRONG VALUE from the wrong source and is not consent-gated.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-recheck2-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate at this hop — pair-scope fold; downstream gates unchanged (re-check of this delta, fresh paired hand-up, master's condition-3, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK-G1-G4-COMPLETE-PUBLISHED-20260810-170608.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-8b12b25.md (record; R-IDs and all four scout tables live there)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: FOLD — R-1 (G-4 needle-without-mint) and R-1b (G-2 false premise) are CRITICAL and measured; plus the G-3 value/scope items; measure any new guard's premise BEFORE you ship it

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- harness/bivharness/e3.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> R-1 mint pairs for unattributed aliases (:887-910); R-2/R-3/R-4/R-4b establish_transcript_version (:305-352, call :951-959); R-5 reason overwrite (:995-999)
- src/adapters/codex/install.cpp -> R-1b rollout_identities/guard (:195-231, :545-554) incl. the absence branch
- src/adapters/claude_code/claude_code.cpp -> R-a staged subtree tolerance (:471-480); reader-side alignment for R-2
- src/adapters/codex/codex.cpp -> reader-side mirror if R-1b's fix moves the accepted set
- tests/test_pack.cpp -> R-1/R-1b round-trip falsifiers; R-8 nested attribution assertion; R-9 version idempotence twin
- tests/test_adapter_claude_install.cpp -> RE-TARGET the approving G-4 test (:3009-3062); R-7 empty-first-object; R-2 non-string case
- tests/test_adapter_codex_install.cpp -> R-6 the untested `id` arm; R-1b parent-referencing falsifier
- tests/test_adapter_claude_collect.cpp -> reality-shaped nested collect fixture
- tests/test_adapter_codex_collect.cpp -> reality-shaped parent/child rollout fixture (session_id == parent)
- harness/bivharness/e3.py -> A3 both-anchor re-fire IF anchored collectors change

## THE MEASUREMENTS (mine, against the real stores — do not re-litigate these, build to them)
```
claude nested subagents   1124 nested transcripts, ALL carry agentId,
                          ALL 1124 stems absent from the flat child enumeration -> 100% unattributed
                          concentrated in 6 sessions (12% of subagent-bearing sessions, ~4% of all)
codex rollouts (930)      session_id != id: 633 (68%)  |  of those, == parent_thread_id: 626
claude main transcripts   127/135 carry a body version (119 on a LATER line); 8 carry none, and NONE of
                          those 8 has a live sessions/<id>.json -> G-3's injection branch is NOT reachable
                          from any observed real session (foreign/older images only)
```
**Standing instruction from here on: any guard you add must have its premise measured against the real
store before it ships, and the measurement goes in your report.** Last round's identity guard measured TRUE
and stands — that is exactly why these two, unmeasured, slipped through. A validated sibling is not
evidence.

## R-1 [CRITICAL] G-4: mint, don't just needle
The union became path-shaped (any `.jsonl` under `subagents/`, any depth) while the rewrite-pair mapping
stayed attribution-only, so an unattributed alias enters the needle set with no pair, survives rewriting,
and `verify_scan` is GUARANTEED to hit it (the needle came from that very file) → whole session refused.
Real images always populate that gap (`child_ids_for` is non-recursive; `collect_subtree_artifacts` is
recursive). **Fix: mint a replacement id per harvested alias regardless of attribution and push the pair**
— the `minted_message_uuid_pairs` precedent already does exactly this for message UUIDs found anywhere in a
body, so it needs no sidecar `id_map` row and is NOT an A9 shape change. (Making `child_ids_for` recursive
is the alternative; it changes manifest child cardinality, so prefer minting unless you can show otherwise.)
**Your test at `:3009-3062` currently asserts the refusal as intended — re-target it: the session must
INSTALL with the alias REWRITTEN, and a falsifier must show the origin alias absent from the recipient bytes.**
**I own the framing error:** my `160025` token worded the falsifier as "an unattributed subagent alias IS
needled", which is literally what you built. Needling without minting can only self-refuse.

## R-1b [CRITICAL] G-2: the premise is false — `session_id` names the PARENT
Compare `payload.id` to `write.installed_id`; validate `session_id`/`parent_thread_id` against the installed
id of the session they legitimately reference (the parent's). Note codex folds children into the parent
record, so today's refusal takes down the whole parent+children family. Also give the ABSENCE branch its own
disposition (`rollout_identities` returns default `{}` when there is no `session_meta` or neither key, so the
guard silently passes exactly the artifacts lacking identity evidence — the recorded absence-blind shape),
and close the untested `id` arm (R-6). Falsifier must use a REALITY-SHAPED parent/child pair
(`session_id == parent's origin id`) and prove it INSTALLS.

## R-2..R-5, R-6..R-9, R-a (fold in the same pass; detail in the record)
R-2 align the non-string `version` handling with the reader (skip and keep scanning, as your own
`transcript_session_id` already does). R-3 apply the floor to the INJECT branch, not just the present
branch. R-4 gate the injection on `Consent::no` (or report the body mutation honestly instead of
`content_rewrite = "pair"`). **R-4b use the RECIPIENT's `caps.agent_version()` as the injected value, not
the packer's** — the packer's value freezes into the manifest on every future hop and, once the floor rises
past it, `pack.cpp:576-590` silently OMITS the session; without injection the next pack fails LOUDLY, so
injecting the wrong value is worse than not injecting. R-5 guard the typed reason against the verify
relabel. R-7 the empty-first-object branch (inverting the ternary emits `{,"version":…}`, invalid JSON, and
the whole suite stays green). R-8 assert nested CHILD ATTRIBUTION, not just byte carriage. R-9 a
version-dimension idempotence twin. **R-a ELECTED IN:** make the staged re-collector tolerate unknown files
(skip-and-warn) instead of aborting the entire pack — today a single `.DS_Store` under the staged subtree
kills `biv pack` on a legal workspace; this is inside your standing B1 grant and strictly widens reader
acceptance with no containment cost.

## Scope ruling — do NOT file the version items as M-4
A version string is not packer identity (the origin-invariant ruling names path/id/key-shaped artifacts).
R-2/R-3/R-4/R-4b/R-4c are provenance-integrity, not containment. R-4c (`admit` never consults `min_line`) is
a PRE-EXISTING gap — register it, do not widen scope to fix it here beyond not writing below-floor values.

## Hard OUT (unchanged)
WSL corridor / ADDENDUM-11 membership formula (m-2); R-4.15 destination paths (slice E — note the lens
confirmed this fold neither widened nor fixed it); R-4.16; sealed A9 member shape; `.github/**`; merge; tag;
deploy; seal; release. Publication only on the `154400` terms.

## Return
One bounded fold on B2's head; C stays byte-identical (say so BEFORE editing if a fix belongs to the writer
slice). Suites honestly green macOS + Docker linux/amd64; REVIEW-FOLD with FOLD_SCOPE, per-finding falsifier
receipts, AND the premise measurements for every guard. Then I convene the re-check. C never lands without
B2 (A10.3). Nothing seals; `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses at `8b12b25`, convener byte-verification of both Critical chains, and four E1 scouts against the real claude/codex stores (identity/version fields only, read-only); this relay + the companion SITREP + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RECHECK2-TWO-CRITICALS-DISPATCH-IMPL-TOKEN-20260810-172910.md` → `s4-floor.implementer`
- TWO CRITICALS, both measured: R-1 G-4 needle-without-mint refuses real nested-subagent sessions; R-1b G-2 false premise refuses 68% of real codex rollouts — both locked by approving tests that must be re-targeted
- fix shapes: mint a pair per harvested alias (message-UUID precedent, no A9 change); compare `id` to this artifact and `session_id`/`parent_thread_id` to the PARENT's installed id
- G-1 confirmed closed; G-3 mechanically sound but wrong VALUE (use recipient `caps.agent_version()`), not consent-gated, floor-asymmetric; R-a elected (staged reader skip-and-warn)
- STANDING: measure every new guard's premise against the real store and report it; version items are provenance-integrity, NOT M-4; A10.3 stands; release hold ABSOLUTE
