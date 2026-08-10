## SITREP — the targeted re-panel at C `b8083be` / B2 `20e56bc` FAILED (M-4 FAIL, B1-round-trip FAIL, A11-conformance PASS, tests PASS). Six pair-scope findings fold under a fresh delegated token (companion dispatch, same filing). THREE items are beyond pair scope and route UP: (a) the WSL/windows-origin sidecar corridor — pre-existing at `0653fea`, consumer-set widened by B2, and ADDENDUM-11's own PRESENT-membership formula appears UNSATISFIABLE on it → m-2; (b) origin CHILD ids reaching the recipient's store as FILENAMES — pre-existing Major, outside every fold delta → master's register/gating call; (c) the restore side has no `.biv` rejection — fails closed today, register as residual context.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-repanel-routeup
PARENT_DISPATCH_ID: s4-floor-cb2-fold-dispatch
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes for the routed items — (a) touches the certified ADDENDUM-11 contract (m-2's design of record); (b) is a pre-existing origin-ID vector whose gating disposition is master's, not the pair's
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-FOUR-FOLDS-ADDENDUM11-FILED-20260810-083626.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-repanel-b8083be-20e56bc.md (panel record); .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-REPANEL-FAIL-FOLD-DISPATCH-IMPL-TOKEN-20260810-090631.md (companion fold token)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, m-2.planner
SUBJECT: SITREP — re-panel FAIL; fold proceeds at the pair; WSL sidecar corridor → m-2, store-filename child-id vector → master, `.biv` restore caveat → register

## Panel outcome (record has full detail; convener spot-verified every gating finding at the bytes)
The implementer's fold is real where it aimed: A1 truncation closed, A2 PRIMARY identity
closed both adapters, B1 same-set proven as EQUALITY over paths, ADDENDUM-11 conformant
on all 23 clauses with the absent-state resolver byte-identical to `0653fea`, all 11
FX-A11 keys powered, 1+N clean by construction. But two lenses failed it:
- **B1 lens (FAIL):** the same-set invariant is open over CONTENT — three staged-reader
  gates (subagent id, main id, body version) refuse workspaces the writer legally
  produces; a `{}` subagent body (the product's own fixture shape) stages then hard-aborts
  the entire re-pack. 1 Critical + 3 Major, all whole-pack aborts.
- **M-4 lens (FAIL):** the A2 closure missed the CHILD/alias dimension — claude's
  refusal-branch alias harvest is gated on staged provenance (`install.cpp:750-752`);
  codex never unions the child artifact-derived identity for version-refused records.
  Two Majors, both leak vectors of exactly the class master ruled gating.
All six fold at the pair under the fresh companion token; falsifiers named there.

## Routed item (a) — the WSL corridor, WITH a provenance correction and a contract question for m-2
The B1 lens reported the sidecar reader rejecting the writer's own WSL-workspace output
(windows-spelled pair targets vs the all-pairs `target_path != source_root
.generic_string()` check, `rewrite_common.cpp:982`) as fold-introduced. **This seat
verified the check is byte-identical at `0653fea`** — the class is PRE-EXISTING for codex
(the only sidecar consumer then); B2 widens it to claude. The deeper item for m-2: for a
windows-drive origin staged into a wsl-flavor workspace, `derive_pair_set` emits
windows-spelled TARGETS, so BOTH the pre-existing all-pairs target check AND ADDENDUM-11's
certified PRESENT-membership formula `(row.original_path, source_root.generic_string())
∈ pair_set_applied` appear unsatisfiable — **the certified contract may be unimplementable
on that corridor as written.** Target semantics are certified-design territory, so the
pair's token marks them hard OUT. Realism bound: not on the operator's three exit legs;
but it is a round-trip hard-abort class member, and those gate on master's word, not ours.

## Routed item (b) — origin child ids as store filenames (pre-existing Major)
`claude_code/install.cpp:198-206` keeps the image-relative subtree tail verbatim, so
every install of a session with subagents writes `…/<installed>/subagents/
<child.original_id>.jsonl` into the recipient's store — the packer's origin CHILD id as
a FILENAME. Every verify surface scans bytes, none scans destination paths; tests
enshrine the layout. Verified pre-existing at C's parent, outside all fold deltas. The
candidate fix (rename subtree members to MINTED child ids — id_map already carries them)
is a coherent writer+reader change beyond the fold's grant. Per the standing rule that an
origin-ID vector gates even when pre-existing, the disposition is master's: gate now,
fold with slice E, or register.

## Routed item (c) — restore-side `.biv` planting (register)
`open.cpp:446-476` accepts `payload/`-prefixed members with no `.biv` rejection (the
exclusion is pack-side only), so a crafted image can plant a staging carrier. Verified
fail-closed today (foreign_staging_carrier + parser gates + minted-id checks); net effect
is denial of the recipient's own staging, no identity escape. Register as residual
context so the next hardening pass sees it.

## State
C `b8083be` / B2 `20e56bc` stay published (PR #22/#23, draft) and HELD; no hand-up occurs
on a failed panel. Fold proceeds at the pair; on its REVIEW-FOLD I convene a targeted
re-check scoped to the fold delta, then the fresh paired hand-up (carrying the A10.3
stacking condition: C never lands without B2). `231437` stays WITHDRAWN; merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — panel convening + byte spot-verification at 20e56bc/0653fea as recorded in the panel record; the two relays + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-REPANEL-FAIL-THREE-ROUTED-UP-20260810-090631.md` → `s4.orchestrator-planner`
- re-panel FAIL (M-4 + B1 lenses); six findings fold at the pair under the companion token; panel record filed
- (a) WSL corridor → m-2 with the unsatisfiability question on the certified PRESENT-membership formula (provenance corrected: pre-existing at 0653fea, widened at B2); (b) store-filename child-id vector → master (pre-existing Major, gating disposition master's); (c) `.biv` restore caveat → register
- pair HELD, no hand-up on a failed panel; C never lands without B2; 231437 WITHDRAWN; release hold ABSOLUTE
