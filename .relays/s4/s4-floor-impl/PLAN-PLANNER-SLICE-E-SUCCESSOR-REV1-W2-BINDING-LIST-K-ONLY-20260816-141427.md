## PLAN rev1 (SUPPLEMENT to `055840` — adds the W-2 literal binding list; nothing else moves) — **I confirmed the measurement at my own seat as instructed and it lands on `{K}` alone, but the stronger result is that I validated the DISCRIMINATOR rather than just re-running the count: the lineage gate `continue`s unless `DESIGN_LOCK_ID` is present (`relay-lint.py:1432`) and reads exactly that one field (`:1440`), and `SECOND_DESIGN_LOCK`, `CONSUMED_CONTRACT` and `CONSUMER_DESIGN_LOCK_ID` DO NOT APPEAR ANYWHERE IN THE INSTRUMENT — grep returns zero. So A4/A5/J/A3 do not merely pass the check; THE CHECK CANNOT SEE THEM.** **And I ran it on a must-be-YES case rather than resting on a negative: `m3-addendum-3` DOES fire this red — twice — on the two superseded Stage 1b-ii revisions `044233` and `044942`, where it was the `DESIGN_LOCK_ID`. Same identity, fires as `DESIGN_LOCK_ID`, silent as `CONSUMED_CONTRACT`. That is the separation a count alone would not have shown, and it is why I can state the negative on A4/A5 as measured rather than assumed.** **MY DEFINITIVE MEASUREMENT: exactly ONE lineage red fires on the current approved plan blob `055840`/`00be8e0`, on `m1-addendum-K-5da667fa-lock-20260816`. The binding list is therefore ONE item.** **I AM DECLINING TO LIST A4/A5, AND NOT ONLY BECAUSE THE SELECTOR SAYS "EXACTLY": over-listing would be a silent WIDENING of an operator risk acceptance. A waiver's coverage is a risk decision taken against a scan; listing an identity whose red does not fire pre-authorizes a FUTURE red on that identity — the day a later revision makes A4 the `DESIGN_LOCK_ID`, the list would already cover it with no fresh scan and no operator act. The registry's own "never resolved by choosing the larger set" is pointing at exactly this, and it is why the informative expected list should not be copied forward as if it were the measurement.** **THE TOKEN STAYS REFUSED and this revision does not change that: W-2 is INEFFECTIVE until VP concurrence is recorded at a named relay, and the registry says it "authorizes NOTHING" meanwhile.** `d7db861` untouched; land order binds; branch LOCAL and UNPUBLISHED; release hold ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-three-locks-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-w2-binding-list-routed
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-W2-BINDING-LIST-ROUTED-MEASURED-K-ONLY-20260816-140516.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this revision supplies W-2's coverage selector input, but W-2 remains INEFFECTIVE pending `master.orchestrator-reviewer` concurrence and authorizes nothing until it is recorded. The token stays REFUSED. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
SUPERSEDES_IN_PART: s4-floor-slice-e-plan-successor-three-locks
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: PLAN rev1 — carry the W-2 literal binding list, measured at my seat as {K} alone with the discriminator validated on a must-be-YES case; declining to list A4/A5 because over-listing silently widens an operator risk acceptance

## 1. Review this with `055840`, as one plan

`055840` (`00be8e0`) is **not withdrawn**. Its scope, folds, within-file boundaries, acceptance matrix and OUT rows all stand unchanged. **This revision adds one thing: the literal binding list W-2's selector reads.** Nothing else in the plan moves.

## 2. THE W-2 LITERAL BINDING LIST

The design identities whose foreign-lock lineage red this plan waives under W-2, each an explicit `DESIGN_DOC_ID -> DESIGN_LOCK_ID` pair:

- m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816

**That is the complete list. One item.**

## 3. How I measured it, and how I checked the instrument could return the other answer

**The count, at my seat, on the current approved plan blob:**

```text
root arm, errors naming PLAN-…-SUCCESSOR-THREE-LOCKS-SCOPE-LOCKED-20260816-055840.md   ->  1
the one red   DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816' has no earlier
              same-owner DESIGN relay carrying matching DESIGN_DOC_ID
```

**The instrument, read rather than characterised:**

```text
relay-lint.py:1432   for f, order, phase, fields, text in phases:
                         if phase != "PLAN" or not fields.get("DESIGN_LOCK_ID"): continue
relay-lint.py:1440   lock_id = fields.get("DESIGN_LOCK_ID", "")
grep SECOND_DESIGN_LOCK / CONSUMED_CONTRACT / CONSUMER_DESIGN_LOCK_ID over relay-lint.py -> ZERO hits
```

**So A4/A5/J/A3 do not pass this check — the check has no way to see them.** That is a stronger statement than "they do not fire," and it is the one the binding list rests on.

**The discriminator, run on a must-be-YES case (D-5.5(a)) — because a rule that only ever returns NO is a ritual:**

```text
m3-addendum-3 as CONSUMED_CONTRACT on plan 055840          -> 0 errors
m3-addendum-3 as DESIGN_LOCK_ID on plans 044233 / 044942   -> 2 errors, one each
```

**Same identity. Fires in one field, silent in the other.** The gate separates on the field, exactly as the source says, and the negative result on A4/A5 is therefore measured rather than assumed. Those two hits are on **superseded** Stage 1b-ii revisions; W-2's model is CURRENT-REVISION, not cumulative, so they are not list candidates — and no token ever rested on them, which I established across the whole root at `131839`.

## 4. Why I am declining to list A4 and A5 — the substantive reason, not the formal one

The selector says list *"exactly the design identities whose foreign-lock lineage red the plan waives"*, and the registry adds that ambiguity resolves to `INAPPLICABLE / NO TOKEN`, **"never resolved by choosing the larger set."** Compliance alone would settle it. But the reason the rule is written that way is worth stating, because the informative expected list `{K, A4, A5}` is sitting in the registry and the path of least resistance is to copy it forward:

**A waiver's coverage is an operator risk acceptance taken against a presented scan.** Listing an identity whose red does not fire waives nothing today and **pre-authorises a red on that identity tomorrow.** If a later revision made `m3-addendum-4` the `DESIGN_LOCK_ID`, a list already naming it would supply coverage with **no fresh scan and no operator act** — the waiver would have silently grown while appearing to stand still. **Over-listing is not harmless redundancy; it is a widening with no decision behind it.**

**Nothing about A4/A5 goes unverified by their absence here.** Their lock identities are re-derived EQUAL at every act and will be again at token time under the three-lock verification; they are simply not this red's subject. **If master or the VP intends W-2 to cover them despite no red firing, that is a deliberate widening and should be recorded as one at the concurrence step** — I am not effecting it by list construction.

## 5. What has NOT changed

```text
TOKEN         REFUSED. W-2 is INEFFECTIVE — VP concurrence REQUIRED and NOT YET GIVEN; the
              registry states it "authorizes NOTHING until it is recorded at a named relay."
              This revision supplies a selector input; it does not make anything effective.
ON CONCURRENCE the token-time join runs PER LISTED IDENTITY at the registry/locked bytes,
              never from a summary (D-5.17 inst 2) — for this list, that is K alone
PLAN          055840's scope, folds, boundaries, acceptance matrix and OUT rows all stand
BRANCH        d7db861 untouched; LOCAL and UNPUBLISHED; no push, no PR, no Actions
MERGE         BLOCKED by the land order; release hold ABSOLUTE
```

## 6. What I want from your review

1. **The list itself** — one item, `{K}`. Re-run the count at your seat; if any identity fires that I have missed, the list is wrong in the under-listing direction, which is the more dangerous one.
2. **§4's reasoning** — is the over-listing harm stated correctly, or is there a reading under which listing A4/A5 is required rather than merely permitted?
3. **That this revision introduces no new red** — the binding-list lines are body text, not header fields, and are not `SCOPE_DIFF`-row-shaped. Confirm the root arm still reports exactly one red on the current revision.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only measurement this pass. pdc: W-2 read IN FULL at `master/RESIDUALS.md:1885-1956` (status, five-element coverage, field dispositions, A12 withdrawal, extension rule, token-time join, two failure modes) rather than the relay characterising it. bivpak: the dispatch-root third arm run and filtered for errors naming the current plan blob (exactly one); `relay-lint.py:1432`/`:1440` read for the lineage gate's field keying and grepped for the three non-appearing field names (zero hits); the discriminator run on `m3-addendum-3` in both field positions to confirm the gate separates. No token issued; no work authority granted. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing. **The same single cross-repo lineage red is expected to fire on THIS revision too, on the same `DESIGN_LOCK_ID`, and is disclosed here rather than claimed clean** — it is the very red the binding list exists to scope, and W-2 is INEFFECTIVE, so no green is available and none is claimed. `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — those are not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-REV1-W2-BINDING-LIST-K-ONLY-20260816-141427.md` → `s4-floor.implementer` for plan-review; **review with `055840` as one plan**, which is not withdrawn
- **THE W-2 LITERAL BINDING LIST, one item:** `m1-addendum-K-20260816 -> m1-addendum-K-5da667fa-lock-20260816`
- MEASURED at my seat: exactly ONE lineage red on the current approved plan blob `055840`/`00be8e0`, on K's `DESIGN_LOCK_ID`
- **DISCRIMINATOR VALIDATED, not just re-counted:** the gate `continue`s unless `DESIGN_LOCK_ID` is present (`relay-lint.py:1432`) and reads only that field (`:1440`), and `SECOND_DESIGN_LOCK`/`CONSUMED_CONTRACT`/`CONSUMER_DESIGN_LOCK_ID` have ZERO occurrences in the instrument — A4/A5/J/A3 do not pass the check, **the check cannot see them**. Run on a must-be-YES case per D-5.5(a): `m3-addendum-3` fires TWICE as `DESIGN_LOCK_ID` (superseded revisions `044233`/`044942`) and ZERO times as `CONSUMED_CONTRACT` — same identity, separates on the field
- **DECLINING to list A4/A5, on substance not just the "exactly" rule:** a waiver's coverage is an operator risk acceptance taken against a scan, so listing an identity whose red does not fire waives nothing now and **pre-authorises a red on it later** — if a future revision made A4 the `DESIGN_LOCK_ID`, an already-naming list would supply coverage with no fresh scan and no operator act. Over-listing is a widening with no decision behind it. Nothing about A4/A5 goes unverified by their absence — their locks are re-derived EQUAL at token time regardless. **If a widening IS intended, record it as one at concurrence; I will not effect it by list construction**
- TOKEN STILL REFUSED — W-2 INEFFECTIVE pending VP concurrence and "authorizes NOTHING" until recorded; this revision supplies a selector input only. On concurrence the token-time join runs per LISTED identity at the registry/locked bytes, never a summary
- `055840`'s scope, folds, within-file boundaries, acceptance matrix and OUT rows all STAND; `d7db861` untouched; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
