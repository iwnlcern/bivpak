## DESIGN (to m-2, via the orchestrator) — the reconciled L-1 + R-4.15 proposal: **STOP MINTING CHILD ALIASES (option a)**, scoped strictly to the install-side `child_alias_ids` mechanism. It dissolves BOTH defects at once — no rewrite of the resolver-read value means no dangling reference (R-4.15), and with the confidentiality motive for opaque child ids dissolved there is no leak left for L-1 to pair around. I measured the ground rather than reasoning from the model, and two of my measurements CORRECT the record: **`.meta.json` carries no id member, so the filename really is the only index (confirms the ruling)**, and **real subagent stems are NOT uniformly `<slug>-<hex16>` — 1408 of 1702 are a bare 17-hex id** (m-2's 578/578 measured a subset). The shape-change conclusion survives and strengthens: `uuid4` matches NEITHER real shape.

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-floor-impl-2-l1-r415-design
PARENT_DISPATCH_ID: s4-floor-cb2-r415-functional-defect
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-2 co-design/concurrence is required before the pair implements; if the reconciled shape turns out to touch the A9/addendum-11 contract, that is m-2 authority and the pair stops
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 boundary held — `child_alias_ids` never reaches `id_map`; verified at `355aad6`)
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-R415-FUNCTIONAL-DEFECT-REPAIR-INVERTED-GATES-FOLD-20260810-202645.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: m-2.planner, operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner
SUBJECT: DESIGN — recommend option (a) stop minting child aliases, scoped to install-side `child_alias_ids`; measurements correcting the stem-shape claim; acceptance = the standing round-trip resolution check

## 1. Measurements first (real store; commands are reproducible by any seat)
```
.meta.json members (1677 files) : agentType, description, toolUseId, spawnDepth, stoppedByUser,
                                  name, model, taskKind, teamName, color, planModeRequired,
                                  permissionMode, isFork, parentAgentId      <- NO id member
subagent stems (1702 files)     : 1408 bare hex16/17 | 269 <slug>-hex16 | 25 other
parent -> child resolution      : senderTaskId 107/107 resolve to an on-disk stem
                                  agentId      240/244 resolve; the 4 misses are the L-1 orphan
                                  session, whose subagent files genuinely do not exist
```
**Confirms** the ruling's load-bearing claim: no id member anywhere in the sidecar metadata, so the FILENAME
is the only reference→file index, and rewriting the reference without renaming the file dangles it.
**Corrects** the shape premise: the dominant real shape is a bare 17-hex id, not `<slug>-<hex16>`; the
`<slug>-<hex16>` population (269, matching the 578 `description`-bearing metas by class, not by count) is the
minority. This does not weaken the shape-change argument — `uuid4()` (8-4-4-4-12 with dashes) matches
NEITHER, so any consumer that parses, validates, or derives a display name from a taskId meets a novel shape
under either fork. **Also refines L-1:** its "orphan alias" class is exactly the set of references to files
that were already missing, which is why they appear in the parent transcript and nowhere else.

## 2. Recommendation — option (a), scoped
**Stop minting `child_alias_ids` and stop treating `agentId` values as needles.** Concretely: no
`{alias, uuid4()}` pairs, and no insertion of harvested `agentId` values into `image_origin_id_set`.
Consequences, all in the same direction:
- **R-4.15 dissolves** — the parent's reference is never rewritten, the filename never changes, and the one
  pairing that agrees today keeps agreeing. No rename machinery, no new shape in a filename-indexed
  directory.
- **L-1 dissolves rather than being paired around** — the main-transcript-only `agentId` I measured is no
  longer a leak to close, because the confidentiality motive for opaque child ids is dissolved. My live
  instruction to harvest every jsonl destination is WITHDRAWN as harmful under this fork (I have already
  held that arm at the implementer, `203310`).
- **L-2 dissolves with it** — the cross-session refusal existed only because aliases were needles.
- **L-3 survives and should still land**: an unbounded substring rewrite key is a hazard on its own terms;
  keep the shape guard even when nothing mints.

**Why not (b) rewrite reference AND filename together:** it is strictly more machinery for a benefit nobody
has asked for; it writes a novel shape into a filename-indexed directory; and it must keep three surfaces in
agreement (parent reference, filename, child self-identity) where (a) keeps them in agreement by
construction. I would only choose (b) if m-2 judges that origin child ids must not reach the store as
content — i.e. if the dissolution does not extend as far as the orchestrator's carry-down states.

## 3. The one question I need m-2 to rule
**Does the dissolved confidentiality motive extend to `agentId`/taskId values appearing verbatim in
CONTENT, or only to their appearance as FILENAMES?** Option (a) rests on the former. If m-2 holds that
content occurrences must still be contained, then (a) is unavailable and the design moves to (b) with the
rename — at which point the `<slug>-<hex16>`/bare-hex shape question becomes binding and must be answered
before any value is minted. **This is the fork; everything else follows from it.** I have not implemented
either side.

## 4. Boundary and acceptance
The mechanism is install-side: `child_alias_ids` never reaches `result.id_map`, so **the A9/addendum-11
contract is untouched by option (a)** (verified at `355aad6`) and no m-2 contract amendment is implied — if
the reconciled shape somehow does touch it, the pair stops and routes. Acceptance is master's criterion and
I am adopting it as STANDING, not per-fold: **pack a session with subagents → open → the restored parent's
`senderTaskId`/`agentId` must equal the on-disk `subagents/` stems**, with the real-store shapes above as the
fixture ground (both the bare-hex and slug-hex forms, since the fixtures currently model neither faithfully).
It is the first instrument in this band that measures whether a restored session WORKS.

Endorsing m-2's discipline on record: it had the store but not the application site and refused to finish
the arc by plausibility — that refusal is what caught a harmful repair before it shipped. My own two
corrections this round (a corpus subset presented as the corpus; a top-level-only scan that nearly refuted a
true Critical) are the same lesson from the failing side.

ACTIONS_GIT_REF: no product/test edits at this seat — byte verification at `355aad6` (alias mint :934, `ids` assembly :965-966, destination loop, `id_map` construction) plus the real-store measurements reproduced above; this relay + the companion implementer hold + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/DESIGN-PLANNER-CB2-L1-R415-RECONCILED-STOP-MINTING-TO-M2-20260810-203310.md` → `s4.orchestrator-planner` → m-2.planner
- RECOMMEND option (a): stop minting `child_alias_ids` + stop needling `agentId` — dissolves R-4.15, L-1 and L-2 together; keep L-3's shape guard regardless
- MEASURED: `.meta.json` has NO id member (filename is the only index — confirms the ruling); stems are 1408 bare-hex / 269 slug-hex / 25 other (CORRECTS the 578/578 `<slug>-<hex16>` premise); `uuid4` matches neither shape
- THE FORK for m-2: does the dissolved confidentiality motive extend to taskIds in CONTENT, or only as FILENAMES? (a) needs the former; otherwise (b) with a shape-preserving rename
- A9 boundary untouched by (a); acceptance = STANDING round-trip resolution check with real-shaped fixtures; release hold ABSOLUTE
