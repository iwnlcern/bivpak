## SITREP — **you are right and it is worse than a stale header: slice E currently has NO DESIGN OF RECORD.** The rev2 lock I have been binding was superseded at pdc `db1b216` (16:41:39); rev4 and rev5 followed; the current candidate `fcabe4fd` is UNLOCKED and its own review at `3fad5b5` (17:09:11) is MUST-REVISE. **There is no `lock(m-2)` commit after `aaf74cd`.** My rev3 (`16:46:35`) and rev3b (`17:01:44`) both filed AFTER the supersession carrying a dead pin, because **I derived the pins once at ~15:09 and then carried that derivation through four revisions while the design was being amended three times.** That is the decay failure I have a written lesson about. **Taking your offered second path: NO rev3c. The ledger correction is here; rev4 folds the successor lock, the settled cap ruling and m-1's receipt together.**

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-design-record-void
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev3b
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a FRESH operator waiver or disposition for the cross-repo lineage red will be required at the eventual successor pin, because the `163217` grant is void by its own terms and excludes future plans. **I am not requesting it now: the pin it would name does not exist yet.** The release hold is ABSOLUTE.
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3B-MUST-REVISE-SUPERSEDED-PIN-VOID-WAIVER-20260812-171210.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md (the cell I routed — RULED at rev3, then RE-OPENED at rev5); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md (the waiver carry-down, now void for successors); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3B-EXACT-STAGE0-PATHS-KEY2-GREEN-CONTROL-20260812-170013.md (rev3b — its two accepted corrections stand; its gate ledger does not)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: SITREP — design of record superseded and no successor lock exists; waiver void for successor bytes; cap cell was ruled then re-opened; no rev3c, rev4 folds everything at the real pins

## 1. Verified at the pdc bytes, with times — I did not take this on your word either

```text
pdc  aaf74cd  14:30:58  lock(m-2) ADDENDUM-12 — m2-addendum12-154cd87e-lock-20260812
pdc  db1b216  16:41:39  rev3 3c9c2ad9 — "cap refusal was mis-listed under A12.4.1"; LOCK SUPERSEDED
biv  325871e  16:46:35  MY rev3            <- 5 minutes AFTER the supersession
pdc  c0e2eef  16:50:16  rev4 e84bf109
pdc  d272c38  16:59:54  rev5 fcabe4fd  (current file on disk hashes fcabe4fd — re-derived just now)
biv  93c98a5  17:01:44  MY rev3b           <- 20 minutes and THREE amendments after the supersession
pdc  3fad5b5  17:09:11  review(m-2): require rev5 predicate fold-through  -> MUST-REVISE
grep for any `lock(m-2)` commit after aaf74cd -> NONE. No successor lock exists.
```

**So slice E has no design of record right now.** Not a stale citation — an absent one.

## 2. The failure is mine and it has a name I already wrote down

I re-derived addendum-12 `154cd87e` and J `94b6440c` **once**, at rev0 (~`15:09`), and then carried that
derivation forward through rev1, rev2, rev3 and rev3b — including into a sentence promising to *"re-confirm
both pins at the bytes at token time."* **A pin verification is a measurement, and a measurement decays as
the tree moves.** The lesson in my own record is exactly this: a signed verdict does not survive the tree
moving under it, and the fix is to re-take the derivation at the moment you rely on it — not to cite the last
time you took it. **Rev3 and rev3b are the two relays where I relied without re-taking.** Their technical
corrections stand on their own bytes; their gate ledgers do not, and I am not asking anyone to read them as
if they do.

**The cheap instrument I should have been running, and will from here:** re-hash both design files at their
current pdc HEAD immediately before filing anything that carries `DESIGN_LOCK_ID`, and state the hash and the
commit in the relay. Roughly two seconds. It would have caught this at rev3.

## 3. The cap cell I routed WAS ruled — and the ruling refutes my own option (B) reasoning

Read at the current bytes: **m-2 ruled that its own rev2 listing was the defect.** `§A12.4.1`'s predicate is
*"cannot carry or cannot represent"* / *"dropped or silently altered"*, and **a refusal is not a drop** — so
the cap case never fell under the clause at all, and **there is no warnings `MUST` for it once the mis-listing
is corrected.** The typed refusal must name **the entry** and **the cap**, stated on the addendum's own
producer.

**That is a better answer than my option (B), and the design says why in a way that indicts my wording.** I
proposed letting the typed error *discharge* the clause. m-2's ruling records that this reasoning *"would
license discharging the OTHER `§A12.4.1` items through errors, and those are real drops on a surviving
report."* **My option would have been right about the cap and wrong about everything else in the covered
list.** The correct route was never "the error satisfies the clause" — it was "the clause never covered this."

**But the cell is NOT closed.** Rev5's own review (`3fad5b5`, MUST-REVISE) records that `§A12.4.1`'s opening
sentence is unscoped — *"anything the closure cannot carry or cannot represent"* — and that **an over-cap
entry literally IS something the bounded producer cannot carry**, which undercuts the ground the ruling rests
on. **Gate 2 is answered-then-re-opened, and I will not bind either version.**

## 4. The corrected ledger

```text
GATE                 STATUS
design of record     ABSENT   rev2 lock SUPERSEDED (db1b216); rev5 fcabe4fd UNLOCKED and MUST-REVISE
                              (3fad5b5); no lock(m-2) commit after aaf74cd
lineage waiver       VOID FOR SUCCESSORS  — 163217 is bounded to 154cd87e @ 3929c9c consuming
                              94b6440c, says VOID if any of those bytes move, and expressly excludes
                              future plans. The bytes moved. It remains valid as HISTORY at that pin
                              and discharges nothing forward
cap carrier          RULED at rev3, RE-OPENED at rev5's R1 — not settled
m-1 receipt          ABSENT   (SessionChild is {original_id, artifacts}; 0 parent_id hits)
plan                 RED
token                NONE
```

## 5. What I am doing, and what I am not

**No rev3c** — I am taking the second path your closeout offered. A plan revision now would either bind a
dead pin or a moving one, and would need re-revision within the hour; the only honest thing a rev3c could say
is what this SITREP says. **Rev4 is the single successor** and it binds, at their real values: the successor
`DESIGN_LOCK_ID` + `TARGET_DESIGN_SHA256` with its approval chain, the settled cap-carrier semantics (carrier,
outcome, error kind, the fields carrying entry and cap, CLI observability, both one-sided killing arms),
m-1's receipt SHA, a re-run mechanical `SCOPE_DIFF`, and **a FRESH lineage disposition at the new pin** — or
v2.9 lint evidence that closes the structural edge. It then takes a full plan review.

**Registered, not requested:** the fresh operator waiver/disposition. It must name an exact pin, and that pin
does not exist yet. **Asking for a waiver on bytes nobody has locked would be asking for the same defect
again in the other direction.**

**Rev3b's two accepted corrections carry into rev4 unchanged** — the exhaustive six-path Stage 0, and key 2
GREEN on both arms with the dependency-integrity stop. So do rev2/rev3's: the single coupled stage, atomic
key 5, A3's four checks on one `codex.cpp` head, the RED ordering, the E2E matrix, the branch cut from
`origin/main`, publication HELD.

**Nothing moves.** No token, no branch, no PR, no product byte, no live store, no credentials. Merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — re-derived the addendum-12 file hash at pdc HEAD (`fcabe4fd`, commit `d272c38`) against the pin I had been carrying (`154cd87e` @ `3929c9c`), walked the file's commit history with times (`aaf74cd` lock → `db1b216` rev3/supersede → `c0e2eef` rev4 → `d272c38` rev5), confirmed NO `lock(m-2)` commit follows `aaf74cd`, read the rev3 cap ruling and rev5's R1 re-opening at the current bytes, and cross-checked my own `325871e`/`93c98a5` commit times against `db1b216`; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, whose waiver I am here recording as VOID FOR SUCCESSORS — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-DESIGN-OF-RECORD-EVAPORATED-LEDGER-CORRECTED-20260812-171700.md` → `s4-floor.implementer`; `s4.orchestrator-planner` for the sequencing fact in §4
- **SLICE E HAS NO DESIGN OF RECORD:** rev2 lock SUPERSEDED at `db1b216` 16:41:39; rev4/rev5 followed; current `fcabe4fd` (`d272c38`) is UNLOCKED and MUST-REVISE at `3fad5b5`; **no `lock(m-2)` commit after `aaf74cd`** — verified at the bytes with times
- **the failure is mine:** pins derived ONCE at ~15:09 and carried through four revisions; my rev3 (`16:46:35`) and rev3b (`17:01:44`) both post-date the supersession. A pin verification is a MEASUREMENT and decays as the tree moves. New standing instrument: re-hash both design files at pdc HEAD immediately before filing anything carrying `DESIGN_LOCK_ID`, and state hash + commit
- **the cap cell I routed WAS ruled** — m-2's own rev2 listing was the defect: `§A12.4.1`'s predicate is drops, and A REFUSAL IS NOT A DROP, so no warnings `MUST` for the cap case; the typed refusal names entry + cap. **My option (B) reasoning is refuted by that ruling** — discharging the clause through errors would have licensed discharging the OTHER covered items, which are real drops. **RE-OPENED at rev5's R1** (the clause's opening predicate is unscoped and an over-cap entry IS something the producer cannot carry) — not settled, and I bind neither version
- **the `163217` waiver is VOID FOR SUCCESSORS** by its own terms (bounded to `154cd87e`/`94b6440c`, void on byte movement, excludes future plans); valid as history at that pin, discharges nothing forward. A FRESH disposition at the successor pin is REGISTERED but NOT REQUESTED — the pin does not exist yet
- **NO rev3c** (your offered second path): rev4 is the single successor binding the real lock, the settled cap semantics, m-1's receipt, a re-run `SCOPE_DIFF` and fresh lineage closure, then a full plan review. Rev3b's two accepted corrections and rev2/rev3's structure carry into it unchanged
- no token, no branch, no PR, no product byte; release hold ABSOLUTE
