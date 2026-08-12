## PLAN rev3 (slice E) — **my Stage-0 invariant contradicted itself inside its own paragraph.** I wrote "no commit may change any value `collect()` returns" and then, four lines later, permitted a new `SessionRecord` member — and `CollectReport.sessions` is `vector<SessionRecord>`, so every returned record gains a value the moment that member exists. I stated a rule and did not re-read it against the next paragraph. **Stage 0 is now test/fixture ONLY: no production header byte moves.** The latent "cap arms wait, the rest doesn't depend on them" sentence is deleted — it contradicted "all four caps land together." **The gate ledger is corrected to the append-only four-row sequence: `154140` → `162257` → `163217` → `163555`.** Lineage is CLEAR only through the operator's bounded waiver, VOID if the pins move.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-rev3
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-2's normative ruling on the cap-refusal disclosure carrier (routed at `163327`) gates the FINAL approvable plan, and this rev3 does not claim to be it. The lineage red is DISCHARGED by the operator's bounded post-scan waiver (master `163217`, carried at `163555`), void if the pins move. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
TARGET_DESIGN_COMMIT: 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV2-MUST-REVISE-STAGE0-CAP-REENTRY-20260812-164019.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md (waiver carry-down; gate 1 clear, gate 2 holds); .relays/s4/s4-floor-impl/CORRECTION-ORCHESTRATOR-PLANNER-SLICE-E-NAMED-ERROR-IS-NOT-A-WAIVER-TOKEN-STILL-BLOCKED-20260812-162257.md (the withdrawn unblock); .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md (the cap cell, OPEN); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV2-ONE-COUPLED-WAVE-ATOMIC-KEY5-A3-SAME-HEAD-20260812-155307.md (rev2, superseded)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: PLAN rev3 — Stage 0 is test/fixture only (production carrier moves to Stage 1); per-key RED classification with assertion-level REDs named; successor-plan discipline for m-2's cap ruling; gate ledger corrected

## 0. Your two findings, re-derived at the bytes

```text
R1  adapter.hpp at 0db8fdd:  struct SessionRecord  :71-100
                             struct CollectReport  :102-106,  warnings at :105,
                             sessions at :103 = std::vector<SessionRecord>
    => a new SessionRecord member changes the ELEMENT TYPE of what collect() returns. Every
       collected record gains a value, empty or not, and the change is visible to BOTH adapters
       through the shared contract. My invariant said no value collect() returns changes.
       The permission and the guard were written in the same paragraph and I re-read neither
       against the other.                                                            CONFIRMED
R2  rev2 said all four caps land TOGETHER in Stage 1, and also that "the cap arms wait; the
    rest of Stage 1 does not depend on them." Both sentences are mine and they contradict.
    A later reader would have had a licensed partial stage.                          CONFIRMED
```

**A precision note, not a challenge:** you cite `adapter.hpp:70-96` for `SessionRecord` and I measure `:71-100`
(`live_at_pack` at `:99`, closing brace `:100`). The design cites the struct as `:71-100` too. Your finding is
unaffected — the mechanism is the shared element type, not the span.

## 1. R1 — Stage 0 is TEST AND FIXTURE ONLY

```text
STAGE 0 — cut from origin/main = 0db8fdd
  INVARIANT (now consistent with what it permits): NO PRODUCTION BYTE CHANGES. Not a header,
  not a declaration, not an unused member. src/** is untouched in its entirety.
  PERMITTED: tests/** and tests/fixtures/slice-e/** only.
  PROOF: the stage-0 diff touches no path under src/, and the full suite is green apart from the
  intended, enumerated REDs.

STAGE 1 — opens on the m-1 receipt. ONE coupled behavior change, now including the carrier.
  SessionRecord::child_parent_map DECLARED, POPULATED and CONSUMED here, together with the
  closure, the rootless disposition, both identity gates, the warning producers,
  manifest_entry_for's edge emission and all four producer caps.
```

Moving the declaration out of Stage 0 also removes the last thing that made Stage 0 look like a slice of the
coupled change. **Stage 0 now proves exactly one thing — that the failures we are about to fix are real —
and it cannot affect a single byte the product emits.**

## 2. Per-key RED classification — and a compile failure is NOT a credited RED

Your rule is right and I am binding it: **an assertion-level RED requires a test that COMPILES, SELECTS, RUNS
and FAILS on an assertion.** A key whose test cannot compile at `0db8fdd` has not been RED-proven there, and
saying otherwise would be a receipt for something nobody watched fail.

```text
KEY   RED WHERE            EXPECTED ASSERTION-LEVEL RED (the assertion that must FAIL)
1a    STAGE 0 @ 0db8fdd    R's record does not carry C: the assertion that C ∈ R's carried
                           descendants (and C's artifact ∈ the record) FAILS
3     STAGE 0 @ 0db8fdd    the rootless component is emitted NOWHERE: the assertion that a
                           primary exists for it FAILS (and with it: primary is a CYCLE MEMBER,
                           the omitted edge is NAMED, artifacts carried exactly once)
4     STAGE 0 @ 0db8fdd    no warnings line exists for an unreadable descendant: the assertion
                           that CollectReport.warnings contains that line FAILS
6     STAGE 0 @ 0db8fdd    install REFUSES the grandchild with staged_identity_mismatch: the
                           assertion that it is ACCEPTED FAILS
2     STAGE 0 CONTROL      byte-identical two-level round trip — GREEN at 0db8fdd and must stay
                           green; credited as a CONTROL, not as key 2
7     STAGE 0 CONTROL      claude flat subagents enumeration — GREEN at 0db8fdd and must stay
                           green; credited as a CONTROL, not as key 7

  --- the following CANNOT compile at 0db8fdd: SessionChild has no parent_id member ---

1b    POST-REBASE          FIXTURE DATA ONLY in stage 0. Test authored and RUN after the rebase
2's   POST-REBASE          onto the m-1 receipt and BEFORE the s4 implementation, so each still
 parent_id-absence arm     has a real observed assertion-level RED on the combined tree.
4a    POST-REBASE          1b: children[] for C carries no parent_id.  2's arm: no parent_id is
5     POST-REBASE          emitted for a two-level entry (J's absence license).  4a: a PRESENT
                           disagreeing edge is not refused.  5: BOTH variants authored together
                           and run together — key 5 is atomic and is never credited in halves.
```

**The RED-first order therefore has three points, not two:** stage-0 REDs at `0db8fdd` → rebase onto the m-1
receipt → the remaining REDs on the combined tree → the s4 implementation. **No implementation byte lands
before every key it greens has been observed failing.**

## 3. R2 — the contradiction is deleted, and the successor plan is the approvable one

**Deleted verbatim: "the cap arms wait; the rest of Stage 1 does not depend on them."** It licensed exactly the
partial stage the rest of the plan forbids. **The four caps are part of the single Stage-1 change. If m-2's
ruling has not landed when the m-1 receipt does, STAGE 1 WAITS — the change is not split to make progress
visible.**

**The successor plan (rev4) is the approvable one, and this rev3 does not pretend to be.** When m-2 rules, I
fold the exact pin and semantics and return it for a full plan review naming:

```text
- the SELECTED carrier and the normative sentence that selected it (quoted, with its pin)
- the user-visible outcome: does pack SUCCEED or FAIL on an over-cap entry
- the error kind and the exact fields carrying the ENTRY and the CAP
- CLI observability: what an operator actually sees, measured, not asserted
- exact production and test paths, with the mechanical SCOPE_DIFF re-run
- BOTH one-sided killing tests: a fatal with NO disclosure FAILS; a disclosure with NO fatal FAILS
- if the ruling selects option C (a widened result carrier), the new surface is OUT of the current
  list and ROUTES BEFORE review — it does not enter by way of the answer
```

**m-2's answer is not token authority and I will not treat it as such.** It is an input to a plan that must
itself be reviewed.

## 4. The gate ledger, append-only and corrected

```text
154140  named-error disposition — claimed the token was unblocked                    WITHDRAWN
162257  correction: disclosure is NOT a waiver; token blocked pending operator        BINDING
163217  operator post-scan waiver granted (master), bounded to the slice-E lineage
        red at pins 154cd87e (@3929c9c) consuming 94b6440c — VOID IF ANY BYTE MOVES   BINDING
163555  carry-down: GATE 1 lineage CLEAR; GATE 2 cap-carrier OPEN at m-2 (163327)     BINDING

GATE            STATUS
lineage red     CLEAR   via the bounded waiver only — not via disclosure, which never conferred it
cap carrier     OPEN    m-2's normative ruling on A12.4.1
m-1 receipt     ABSENT  measured: SessionChild is {original_id, artifacts}; 0 parent_id hits
plan review     RED     this relay closes two bounded defects; rev4 folds the ruling
```

**Two obligations I am recording so they cannot be lost.** (i) **The waiver is void if the pins move** — at
token time I re-confirm addendum-12 `154cd87e` @ `3929c9c` and J `94b6440c` at the bytes before issuing
anything, and say so in the token relay. (ii) **`DESIGN_RECORD_KIND: design-doc` stays**; `audit-record`
remains rejected and `direct-override` remains not mine to author. The waiver changed who may proceed, not
what the artifact is.

**On `154140`: my seat held the token before that relay and held it after.** The orchestrator has owned that
its unblock line handed me by the back door what I had refused at the front. I record it only because the
ledger has to be readable by someone who was not here.

## 5. Everything else carries unchanged from rev2 (re-read it there; do not re-litigate it here)

The coupled-stage rationale (transitive `child_ids` on the flat writer emits C as a DIRECT CHILD of R under
J's absence license — false data, not missing data); the combined-tree checkpoint as the first creditable
point; `FX-A12-5`'s atomicity; A3's four checks on ONE `codex.cpp` head carrying its ONE pin, with the five
codex read-side literal classes named for mutation-checking, `codex/install.cpp` moving no pin, the claude pin
frozen, and the burden reported per the grant's own R-3.40(11) trigger; the exact IN/OUT/CONDITIONAL-OUT
scope; the E2E and verification matrix with the sandbox guards, the credential decoy, macOS + governing local
Ubuntu 24.04 `linux/amd64` Docker, Actions untouched, the base-container control, and the `.github` count
gates named as an inherited stale pin; the branch cut from `origin/main` (= `0db8fdd`), never local `main`;
publication HELD; D-5.5(a) measured at hand-up; R-4.20's mint sites; MONO; M4-CG-0; R-4.24 not ours.

## 6. What I am asking of you

**A plan review of the two bounded corrections** — is Stage 0 now genuinely inert (does "no production byte"
close the hole that "no returned value" left open), and is the per-key RED classification honest about which
keys can be RED-proven where? **Even an approve does not open the token**: gate 2 holds at m-2 and rev4 must
fold the ruling and be reviewed on its own. Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise`
(verdict line BARE — no bold, no backticks; remarks via em-dash only, per the matcher's recorded grammar).
Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — `SessionRecord` `:71-100` and `CollectReport` `:102-106` (`warnings` `:105`, `sessions` `:103` = `vector<SessionRecord>`) re-measured at `0db8fdd`; the waiver carry-down `163555`, the correction `162257`, and the review `164019` read in full; `SessionChild` and the 0 `parent_id` hits re-confirmed; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; and the third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, now WAIVED for this lineage at these pins by the operator (`163217`/`163555`) and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-STAGE0-FIXTURE-ONLY-SUCCESSOR-DISCIPLINE-20260812-164434.md` → `s4-floor.implementer`; rev2 `155307` SUPERSEDED
- **R1 accepted:** `CollectReport.sessions` is `vector<SessionRecord>`, so a new member changes the returned element type for BOTH adapters — my invariant forbade exactly what my next paragraph permitted. **Stage 0 is now TEST/FIXTURE ONLY, `src/**` untouched entirely**; `child_parent_map` is declared, populated and consumed in Stage 1 with the rest of the coupled change
- **per-key RED classification added, with your rule bound:** a compile failure is NOT a credited behavioral RED. Assertion-level REDs at `0db8fdd` for `1a/3/4/6` (each named), controls `2`/`7` green there; `1b`, `2`'s absence arm, `4a` and `5` are fixture-data-only in stage 0 and get their observed REDs after the rebase and BEFORE implementation — **three RED points, not two**
- **R2 accepted:** the "cap arms wait" sentence is DELETED; the four caps are part of the single Stage-1 change and **Stage 1 WAITS if the ruling lags the receipt**. Rev4 folds m-2's exact ruling (carrier, outcome, error kind + entry/cap fields, CLI observability, paths, re-run SCOPE_DIFF, both one-sided killing tests) and is reviewed on its own; **an option-C surface ROUTES BEFORE review**; the answer alone is NOT token authority
- **gate ledger corrected append-only:** `154140` WITHDRAWN → `162257` disclosure-is-not-waiver → `163217` operator waiver bounded to `154cd87e`/`94b6440c`, VOID IF MOVED → `163555` gate 1 CLEAR / gate 2 OPEN. **Obligation recorded: re-confirm both pins at the bytes at token time**; `design-doc` stays, `audit-record` rejected, `direct-override` not mine
- release hold ABSOLUTE; no token, no branch, no product byte
