## PLAN (successor r6, slice E) — **the land order is BOUND, and I verified it at J's SEALED bytes rather than on the carry-down: `e30f845:288` "the obligation lands before any J-capable writer ships" and `:298` "Without M3-J-4..7 the bump is strictly worse than no-bump … silently absent from a count the user consented against."** Both verbatim. **This is J's own precondition, so it is not a new gate imposed on us — it is a clause we were already consuming and had not read to its consequence.** **AND: J MOVED while I was reading it.** The instrument I adopted after the addendum-12 supersession caught it: pdc HEAD now hashes `79d8dde5…`, not `94b6440c…`. **It is a LOCK STAMP** — commit `b8afc10` at `03:14:48`, ONE hunk, 27/6, in the status block — and **the locked bytes are unchanged at `e30f845`, so `CONSUMED_CONTRACT` is intact.** I checked the hunk count myself rather than accept the document's own "nothing else moved."

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r6
PARENT_DISPATCH_ID: s4-floor-slice-e-land-order-bound
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — two items sit above this seat and neither is mine: m-3's confirmation of whether M3-J-4..7's notice text and surface are determined at the sealed pin, and the operator's scope-generalization decision. I address neither seat. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LAND-ORDER-BOUND-SCHEMA2-NOT-AHEAD-OF-M3J47-20260813-025756.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R5-STAGE1B-SPLIT-ON-MEASURED-BOUNDARY-20260813-023240.md (r5 — its 1b-i/1b-ii BUILD split stands; its START-rule framing is amended here by the land order); .relays/s4/s4-floor-impl/CORRECTION-PLANNER-M3-CELL-ROUTES-VIA-MASTER-NOT-DIRECT-20260813-021028.md (routing: this pair routes UP only)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r6) — land order bound as a MERGE-gate predicate; J's lock stamp disclosed with the consumed pin intact; one narrowing question routed, not taken

## 0. Pins re-derived AT THIS ACT — and J moved

```text
addendum-12 @ 6eeeb157   29a5b3a3abb6777a…   == the lock                              MATCH
addendum-12 @ pdc HEAD   d0e2c6eba6047c3b…   the disclosed one-hunk lock post-stamp
J           @ e30f845    94b6440c6ea5342a…   == CONSUMED_CONTRACT — the LOCKED bytes    MATCH
J           @ pdc HEAD   79d8dde5f4242e52…   MOVED since my 023240 reading
  cause     b8afc10  03:14:48  "stamp J's lock — the document said NOT sealed for twenty-two hours"
  measured  ONE hunk (@@ -55,12 +55,33 @@), 27 insertions / 6 deletions, status block only
origin/main              0db8fdd             unchanged
```

**The consumed pin is INTACT** — `94b6440c` is still what `e30f845` holds, and that is what
`CONSUMED_CONTRACT` names. The live file carries a lock stamp that, by its own construction, cannot hash to
the locked value. **I counted the hunks myself rather than accept the stamp's "nothing else moved,"** because
a document certifying its own edit is the shape this team has been bitten by twice this week.

**Recorded here to pre-empt a false red at token time:** the seven-element tuple checks for "no later
unlocked normative edit." **There IS a later edit to J, and it is `b8afc10`, and it is a status-only lock
stamp.** A future check that finds `79d8dde5 ≠ 94b6440c` and stops has found this, not drift.

## 1. The land order — verified at the SEALED bytes, then bound

```text
J @ e30f845 :288   "…and the obligation lands before any J-capable writer ships. m-1 cannot rule
                    m-3's printed UX — the same boundary that made `child_count` their call and not mine."
J @ e30f845 :298   "**Without M3-J-4..7 the bump is strictly worse than no-bump**, because it converts a
                    session that would have failed loudly at install into one silently absent from a count
                    the user consented against."
J @ e30f845 :296   "It does **not** win because disclosure exists at the baseline — it does not
                    (`entry_schema_skipped` is set and never rendered)."
```

**Both quotes are verbatim at the sealed pin. The third line is the one that stings:** J states the baseline
we measured — the flag is set and never rendered — as a known fact of its own reasoning. **The dependency was
never a gap we discovered; it was a clause we were consuming and had not read to its consequence.** My
`020326` framed it as a newly-found consumer gap. It is not. **That framing is corrected here.**

**BOUND:** the schema-2 stamp does not land ahead of M3-J-4..7 being in force. rev2's one-coupled-wave
concept **extends across the consumer half**: writer and consumer land together, or consumer-first, **never
writer-first.**

## 2. Making "does not ship" checkable — the binding is a MERGE-gate predicate

**"Ships" needs an event, or it is an instruction nobody can test.** Nothing leaves this pair from an
unpublished branch; the event at which a writer becomes real for an operator is **the merge to
`origin/main`.** So:

```text
MERGE-GATE PRECONDITION (new, binds every slice-E head):
  NO head that CAN PRODUCE a schema-2 image merges to origin/main until M3-J-4..7 are IN FORCE.
  "In force" = implemented and landed on origin/main, at a SHA named in a receipt — not designed, not
  planned, not agreed.
BUILD (unchanged from r5):
  Stage 1a and Stage 1b-i may be BUILT and RED/GREEN-tested on the unpublished branch. Building is not
  shipping, and the REDs are worthless if taken after the fix.
```

**A narrowing I can see and am NOT taking.** The bump fires only when a child carries a present `parent_id`
(J-R3), which requires the transitive collector — so **Stage 1a alone cannot produce a schema-2 image**, and
a strict reading would let 1a merge early. **I am not acting on that.** It is precisely the inference class
that has been corrected twice at this seat today, and the cost of being wrong is J's own "strictly worse than
no-bump." **Routed as a question to `s4.orchestrator-planner`: does the merge gate bind at the capability
(1a) or at the first head that can emit (1b-i)?** Until answered, **the conservative rule governs and nothing
merges.**

## 3. What is pending above this seat — named, not addressed

```text
m-3        whether M3-J-4..7's exact notice STRING and SURFACE are DETERMINED at the sealed pin, or what
           is not. STOP #2 territory; master routed it.
operator   whether to GENERALIZE the (A) ruling so a build team may implement sealed design text in ANY
           domain under that domain's byte-level veto. If generalized, the DETERMINED M3-J-4..7
           obligations become implementable at this pair on `core/open` under m-3 veto.
```

**I address neither seat, name no cross-domain destination, and propose no onward sequence** — per the
operative `021028` correction and `D-5.11(a)`. **`src/core/open/sessions.cpp` stays HARD-OUT and I do not
widen into it.** If the generalization lands, this plan needs another revision to scope that work properly;
**I am not pre-writing it against a decision that has not been made.**

## 4. What this changes in r5, and what it does not

```text
AMENDED   r5's "Stage 1a is dispatchable / 1b-i starts on m-1's approval" now carries the merge-gate
          predicate above. BUILD order is unchanged; the LANDING of any such head is gated.
AMENDED   r5 §2's receipt-dependence line is no longer the ONLY gate — it governs which ASSERTIONS need the
          consumer; the land order governs which HEADS may merge. Two different questions, both answered.
UNCHANGED r5's 1b-i / 1b-ii split on the measured include-boundary (test_adapter_codex_install.cpp does not
          include core/open/sessions.hpp; test_cli.cpp drives BIV_BINARY_PATH), and the seven-of-eight-keys
          allocation
UNCHANGED the honest hand-up sentence: if the consumer half never lands, slice E completes with seven of
          eight keys green and THE ACCEPTANCE INSTRUMENT OWED, reported in those words
```

## 5. Carried unchanged

The J-capable reader transition and its three killing tests; the base-`0db8fdd`-binary compatibility
falsifier; the two-halves Stage-1a claim; the three STOPs and five VETOES verbatim under m-1's byte-level
veto; the manifest-only fence with `.github`, sealed docs, m-3's surfaces and every unnamed path out; J's
determining text at the sealed bytes; the `parse_session_children` primary-threading fact to be NAMED; the
`ArchiveWriteFailed` cap carrier at exit 4 with both names in `detail`; the atomic-absence cap+1 oracle on
the three source-derived paths with its at-cap positive arm; the three semantic killing arms; key 5 atomic
and `FX-A12-3`'s never-executed legs owed at 1b-i; A3's four checks on ONE `codex.cpp` head with its ONE pin;
sandbox guards and the credential decoy, **NEVER the live `~/.claude`/`~/.codex`**; macOS plus **governing**
local Ubuntu 24.04 `linux/amd64` Docker, **Actions NOT invoked**; the base-container control; branch cut from
`origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; the token-time seven-element tuple
with **both design hashes re-derived at that act** and J's lock stamp expected. **Stage 0 remains ACCEPTED
and unpublished at `dca6b7d`.**

## 6. What I am asking of you

**A plan review.** Is the merge-gate predicate stated so it can actually be applied — "can produce a schema-2
image," "in force at a named SHA" — rather than felt; is the build/land separation clean enough that no byte
is ambiguously authorized; and have I correctly refused the 1a-merges-early narrowing rather than quietly
relying on it? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no
backticks; remarks via em-dash only, per the matcher's recorded grammar). **On approve, Stage 1a is
dispatchable to BUILD; nothing merges.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed addendum-12 at `6eeeb157` and pdc HEAD, re-hashed J at `e30f845` (`94b6440c`, the consumed pin, INTACT) and at pdc HEAD (`79d8dde5`, MOVED), identified the cause as `b8afc10` and measured it as ONE hunk / 27+6 / status block only, and read J's land-order clauses at `e30f845:288`, `:296` and `:298` verbatim; re-measured `origin/main`; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read immediately before appending; `--index`; `&&`-gated append→lint→commit. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion I caused and disclosed at `014257`, which stays deliberately unindexed to avoid a second inversion
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R6-LAND-ORDER-BOUND-J-MOVED-DISCLOSED-20260813-033817.md` → `s4-floor.implementer`; r5 `023240` amended as to the start rule, its 1b-i/1b-ii split unchanged
- **J MOVED and my adopted instrument caught it:** pdc HEAD is `79d8dde5…`, not `94b6440c…`. Cause `b8afc10` `03:14:48`, a LOCK STAMP — ONE hunk, 27/6, status block only, hunk count verified BY ME not accepted from the stamp. **The consumed pin is INTACT at `e30f845`.** Recorded now so the token-time "no later unlocked normative edit" check finds this and not a phantom drift
- **land order verified at J's SEALED bytes and bound:** `:288` "the obligation lands before any J-capable writer ships"; `:298` "without M3-J-4..7 the bump is strictly worse than no-bump … silently absent from a count the user consented against"; `:296` states the very baseline we measured. **So this was never a gap we found — it was a clause we were consuming and had not read to its consequence, and my `020326` framing is corrected**
- **BOUND as a MERGE-GATE PREDICATE so it is testable:** no head that CAN PRODUCE a schema-2 image merges to `origin/main` until M3-J-4..7 are IN FORCE — implemented and landed at a NAMED SHA, not designed or agreed. **BUILD is unchanged: 1a and 1b-i may be built and RED/GREEN-tested unpublished, because building is not shipping and REDs taken after the fix are worthless**
- **a narrowing I can see and REFUSE to take:** the bump fires only with a present `parent_id`, so 1a alone cannot emit schema 2 and a strict reading would let it merge early — **not acting on it**, since that is the inference class corrected twice at this seat today and the cost of being wrong is J's own "strictly worse than no-bump." **Routed as a question: does the gate bind at capability (1a) or at first-emit (1b-i)? Until answered, nothing merges**
- pending above this seat and NOT addressed: m-3's notice determinacy; the operator's scope generalization. `sessions.cpp` stays HARD-OUT, no widening, no cross-domain destination named (`021028`, `D-5.11(a)`); if generalization lands the plan needs another revision and I am not pre-writing it
- everything else carries; Stage 0 ACCEPTED at `dca6b7d`; **on approve Stage 1a is dispatchable to BUILD and NOTHING MERGES**; release hold ABSOLUTE
