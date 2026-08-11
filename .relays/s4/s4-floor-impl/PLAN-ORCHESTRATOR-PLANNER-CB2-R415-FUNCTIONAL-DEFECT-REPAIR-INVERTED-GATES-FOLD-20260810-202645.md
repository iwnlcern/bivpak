## DISPOSITION (carry-down, fold-scope change) — master closed the R-4.15 fork at the bytes and it closes to a LIVE FUNCTIONAL RESTORE-CORRECTNESS DEFECT that now GATES the C/B2 merge (no longer a Step-4-exit confidentiality item): the fold's OWN child-alias minting rewrites the PARENT transcript's `senderTaskId`/`agentId` to `uuid4()`, while the child file on disk keeps its `agent-<origin-taskId>.jsonl` name — and the FILENAME is the only reference→file index (`.meta.json` has no id field), so the reference DANGLES = the operator's named "sessions re-seeking" failure. I re-verified the trace at my seat at `355aad6` (`child_alias_ids.push_back({alias, uuid4()})` :935 → folded into `ids` :965 → `rewrite_jsonl_bytes(IdPairsView{ids})` applied to EVERY jsonl destination, `main_transcript_artifact` checked INSIDE that loop = the parent is rewritten). m-2's measurement REFUTED the UUID model (taskIds are `<slug>-<hex16>`, 578/578) and **R-4.15's specified repair — rename to the minted id — is WITHDRAWN as AFFIRMATIVELY HARMFUL** (it would write `agent-<uuid4>`, a shape the harness never produces, into a filename-indexed dir, breaking the one pairing that still agrees). The correct repair is the INVERSE: DO NOT rewrite the value the resolver reads. Design belongs to you + m-2. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-cb2-r415-functional-defect
PARENT_DISPATCH_ID: s4-floor-cb2-fold-dispatch
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-FORK-CLOSED-AT-BYTES-LIVE-RESTORE-DEFECT-CONFIRMED-20260810-202209.md
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate to OPEN the work — the operator already stated the requirement this defect violates ("sessions installed and working, no re-seeking"), which is the authority the fix runs under; the operator sees it again at the C/B2 hand-up. The design of the repair is yours + m-2's. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 boundary held; the child-alias mechanism is install-side, not id_map)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN — R-4.15 is a LIVE functional restore defect gating C/B2; specified repair WITHDRAWN as harmful; repair direction inverted (don't rewrite the resolver-read value); coupled to L-1; acceptance = a round-trip check

## 1. What changed — R-4.15 is now IN the C/B2 fold's scope (verified at my seat)

R-4.15 was a Step-4-exit confidentiality item (child origin id as store filename). The operator dissolved the
confidentiality motive for opaque ids, and m-2 + master's byte-trace transformed the residual into a LIVE
FUNCTIONAL defect: the fold's child-alias minting (`{alias, uuid4()}`, install.cpp:935) is folded into the
single `ids` vector (:965) and `rewrite_jsonl_bytes(IdPairsView{ids})` is applied to EVERY jsonl destination
including the PARENT transcript (`main_transcript_artifact` sits INSIDE that loop). So the parent's reference
to its child (`senderTaskId`/`agentId`) is rewritten to `uuid4()`, the child file keeps `agent-<origin-taskId>.jsonl`,
and the filename is the only index → the reference resolves to a path that does not exist. **The merge cannot
be right while a restored session mis-resolves its subagents — this GATES the C/B2 merge, not Step-4 exit.**

## 2. The repair — direction only; you + m-2 own the mechanism

**Do not rewrite the value the resolver reads.** R-4.15's specified rename-to-minted-id is WITHDRAWN as
affirmatively harmful. Candidate shapes (design is yours + m-2's, I choose no mechanism):
- **(a) stop minting child aliases entirely** — parent reference, filename, and child self-identity all keep
  the origin taskId and agree by construction; simplest, and consistent with the dissolved confidentiality
  motive; OR
- **(b) rewrite reference AND filename together**, preserving the `<slug>-<hex16>` shape — strictly more
  machinery for no benefit the operator has asked for.
**Holds on EITHER fork, do not lose it:** `uuid4()` is minted where 578/578 real taskIds are `<slug>-<hex16>`
— a SHAPE change any consumer that parses / validates / derives a display name from a taskId will meet,
independent of where the rewrite lands.

## 3. COUPLING — L-1 and R-4.15 are the SAME mechanism; design them together

The child-alias minting is BOTH the L-1 fold's pairing arm (harvest every jsonl `agentId` → pair-or-refuse)
AND the cause of this R-4.15 dangling reference. With the confidentiality motive dissolved, option (a) —
stop minting — changes L-1's disposition too (a verbatim `agentId` is no longer a confidentiality leak the
minting existed to prevent). **Reconcile L-1 and R-4.15 as one design with m-2**, do not fix one in a way
that re-breaks the other; the R-4.18 one-level-consistency constraint is unchanged and still binds. If the
reconciled design needs an A9/addendum-11 contract touch, STOP and route up (m-2 authority) — but the trace
shows the child-alias mechanism is install-side and the A9 boundary held, so likely not.

## 4. Acceptance — the round-trip check (must be in the fold's evidence; make it standing)

Master's criterion, which is ALSO the operator's stated acceptance and the first instrument in this band that
measures whether a restored session WORKS (not merely that we failed to corrupt it):
**pack a session that has subagents → open it → compare the restored parent's `senderTaskId`/`agentId` against
the on-disk `subagents/` stems; EQUAL ⇒ resolution intact, DIFFERENT ⇒ the defect.** Put it in the fold's
re-check evidence and keep it as a STANDING round-trip check (it outlives R-4.15).

## 5. State + the good process note

C/B2 stays HELD — no hand-up while this functional defect + the live L-1 leak stand. Fold L-1 + the riders +
this R-4.15 repair as one reconciled design (one-level-consistent per R-4.18), with m-2 co-designing; on the
fold's REVIEW-FOLD convene the re-check (L-1 harvest-every-destination falsifier + the round-trip resolution
check §4), then the fresh paired hand-up (A10.3 + the cut-point blast-radius line per the corrected D-5.5).
Endorsed on record: m-2 applied D-5.4 exactly — it had the store, not the application site, and REFUSED to
finish the arc by plausibility; that refusal is what caught the harmful repair before it shipped. `231437`
stays WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — re-verification of master's alias-application trace at 355aad6 (install.cpp:935 child_alias_ids uuid4 mint, :965 ids assembly, :968-980 destination loop with main_transcript_artifact inside) + this carry-down relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. No fold executed here; the branch is yours.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Token-style locks; other reds are the pre-existing sibling classes — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-R415-FUNCTIONAL-DEFECT-REPAIR-INVERTED-GATES-FOLD-20260810-202645.md` → `s4-floor.planner`
- R-4.15 closed at bytes to a LIVE FUNCTIONAL restore defect (fold's child-alias uuid4 minting rewrites the parent reference; child filename stays origin-id; filename is the only index → DANGLES) — re-verified at my seat; now GATES the C/B2 merge (not Step-4 exit)
- specified repair (rename to minted id) WITHDRAWN as harmful; correct direction = do NOT rewrite the resolver-read value: (a) stop minting child aliases, or (b) rewrite reference+filename together preserving <slug>-<hex16>; you + m-2 design; uuid4-vs-<slug>-<hex16> shape-change holds either way
- COUPLING: child-alias minting is BOTH the L-1 pairing arm AND the R-4.15 cause — reconcile L-1 + R-4.15 as ONE design with m-2 (confidentiality motive dissolved; option a changes L-1 too), one-level-consistent per R-4.18; A9 boundary held (likely no m-2 contract touch, else stop-and-route)
- acceptance = round-trip check (pack-with-subagents → open → restored parent senderTaskId/agentId == on-disk subagents/ stems) in the fold evidence + STANDING; m-2's D-5.4 refusal endorsed; release hold ABSOLUTE
