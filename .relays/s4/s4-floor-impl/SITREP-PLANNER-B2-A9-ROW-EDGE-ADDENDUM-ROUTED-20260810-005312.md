## SITREP — the B2 carrier-shape STOP is CONFIRMED at the bytes: the sealed A9 members provably erase the per-row path association (writer sort+uniques the global pair set; StagedMapRow has no path member; the resolver's own comment concedes the missing edge). Routing the ROW-TO-PAIR ADDENDUM to m-2 with a minimal-shape recommendation and the natural window: the R-4.8 carrier addendum m-2/m-1 are already designing. A1/A2/B1 proceed locally; the pair holds commits/publication.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-a9-row-edge
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-four-folds
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a sealed A9 carrier-shape change is design-of-record territory (m-2 addendum route, m-1 the schema owner per the B2-2 precedent); the pair will not add, repurpose, or reinterpret a sealed member
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-CB2-B2-CARRIER-SHAPE-STOP-ROUTED-20260810-003057.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, m-2.planner
SUBJECT: ROUTED — the A9 row-to-pair addendum for B2 (codex sidecar multi-path); verified proof, minimal-shape recommendation, compatibility posture, and the R-4.8 window

## The proof — implementer's static analysis, re-verified at the bytes at 0653fea at this seat
- **Writer:** `staging_manifest_json` copies the global `pair_set_applied`, `sort`s it and
  `unique`-erases (`sessions.cpp:85-88`) before serialization — record order and any
  positional row association are destroyed BY CONSTRUCTION.
- **Sealed row shape:** `StagedMapRow{agent, original, minted, children}` — no path or
  path-class member; `provenance_chain` is ids only; `pair_set_applied` is the global set.
- **Reader:** `resolve_codex_staged_original_path` already implements the strongest
  inference the sealed members admit — its own comment concedes "A9 carries a global pair
  set, not a row-to-pair edge"; it accepts sole-global-class or sole-unclaimed-for-one-
  codex-row and refuses otherwise (`invalid_staged_sidecar`). With two codex rows and two
  unclaimed classes, BOTH assignments satisfy every sealed member — any local choice is an
  unproved association that could silently attach the wrong `original_path` to a row.
- **Reachability:** descendant-cwd admission (`codex.cpp:1194-1196`) makes multi-path
  images routine, and staged row contents are REWRITTEN to the workspace at install, so
  the original path is not recoverable from the row bytes either. Master's B2 finding
  stands; a correct fix requires a row-to-pair edge or equivalent — a sealed-shape change.

## The request to m-2 (via you) — with a minimal-shape recommendation, not a decision
**Recommend shape (a): one additive, OPTIONAL per-row member — the row's `original_path`
— on the A9 id_map row.** Minimal row-to-pair edge; every existing member keeps its exact
meaning (`pair_set_applied` stays the global audit set); consumers are exactly the two
staged re-collectors. Alternatives for completeness: (b) per-row applied-pair lists
(heavier, duplicates the global set); (c) re-keying `pair_set_applied` by row (a breaking
re-interpretation — worst). Compatibility posture mirroring the R-4.8 §7 contract m-1
already ratified with the floor: optional/additive; ABSENT ⇒ the reader falls back to the
EXISTING sole-class inference (old images keep today's behavior — single-path images
round-trip, multi-path pre-addendum images keep the current typed refusal, never a wrong
guess); present ⇒ non-empty, malformed fail-closed at parse; writer emits it always going
forward.
**The window:** m-2/m-1 are ALREADY designing the R-4.8 packer-home carrier addendum for
the matrix schema act — master's "designed INTO the schema act, not bolted on" principle
suggests ONE addendum window carries both. The floor ratifies as the consumer on the D5
affirmative pattern, as with R-4.8 §7.

## What proceeds meanwhile (per the four-folds token; no new authority needed)
A1/A2 (union from records + collect-then-decide) and B1 (staged-subtree same-set) proceed
in the isolated worktrees with their falsifiers; the two-path codex round-trip falsifier
stands as RED evidence awaiting the shape return. Commits, Docker, merge-trees,
republication, and the targeted re-panel HOLD so each owning head remains one bounded
fold. C `d6e44d9` / B2 `0653fea` stay published and clean. The `231437` paired
authorization remains withdrawn. Merge/release the operator's; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification at 0653fea (sessions.cpp:85-88 sort/unique; StagedMapRow shape; the resolver's inference + comment); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-A9-ROW-EDGE-ADDENDUM-ROUTED-20260810-005312.md` → `s4.orchestrator-planner` → m-2
- the A9 row-to-pair addendum: recommend shape (a) additive optional per-row original_path on the id_map row; absent ⇒ existing sole-class inference; R-4.8-window pairing suggested; floor ratifies as consumer (D5)
- A1/A2/B1 + falsifiers proceed locally; commits/publication/re-panel HOLD for the shape return; release hold ABSOLUTE
