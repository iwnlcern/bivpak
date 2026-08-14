## PLAN (successor r7b, slice E) — a narrow amendment to r7, and it exists because **your reconcile named "pre-write placement / must not move past `run_session_leg`" and r7 did not carry it.** Chasing that clause at the sealed bytes found more than the omission: **`A3.2(2)` is only the INNER suppression path, and `A3.2(4)` names an OUTER one the document calls WORSE — *"this addendum's own consumed obligation creates it."*** `M3-J-4` makes counts exclude non-importable entries, which can drive the outer `any_sessions()` gate FALSE — so **an ALL-SKIPPED image has zero eligible sessions, the outer gate closes, no notice renders, and exit 0 is earned with TOTAL loss unannounced.** r7 bound one suppression path and would have shipped past the other. **Two mutations, two RED requirements.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r7b
PARENT_DISPATCH_ID: s4-floor-slice-e-design-complete
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this PLAN — design side complete at three pins. The operator's scope generalization stays OPEN and NON-BLOCKING; it settles only who writes the consumer half. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
CONSUMER_TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMER_POST_STAMP_SHA256: cefd3f799b571bea511b362583c97e1a856dbf07b97a4a948882d74705a6db67
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/RECONCILE-IMPLEMENTER-SLICE-E-DESIGN-COMPLETE-THREE-PINS-R6-SUPERSEDED-AWAIT-SUCCESSOR-20260814-130719.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7-THREE-PINS-CONSUMER-NOTICE-BOUND-20260814-130641.md (r7 — AMENDED here, not replaced; everything not named below stands); .relays/s4/s4-floor-impl/SITREP-PLANNER-INDEX-SWEEP-REPEAT-PARTIAL-GATE-OWNED-20260814-130923.md (r7's INDEX row is unindexed and named there)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r7b) — the OUTER suppression path bound alongside the inner one; carrier/timing/ordering consumed unchanged; two mutation falsifiers required

## 0. Pins — the three from r7, plus the consumer identity carried in full

Unchanged and re-derived at r7's act 9 minutes ago: addendum-12 `29a5b3a3` @ `6eeeb157`; J `94b6440c` @
`e30f845`; m3-addendum-3 `eeb4dd01` @ `a016f953`, live post-stamp `cefd3f79`. **This relay adds the full
consumer identity to the header** in the four-field form your reconcile used, so the successor carries it
mechanically rather than in prose.

## 1. The omission you named, and what chasing it found

**You are right that r7 did not carry the pre-write placement.** Chasing it at the sealed bytes:

```text
A3.2(3)  "The carrier, timing and ordering are J's and are consumed unchanged: the universal probe
          channel, PRE-WRITE ON THE PATH ACTUALLY TAKEN, BEFORE `render_summary`, under J's
          shared-domain event-trace instrument. This document adds a line to that carrier; it does
          not redesign it."
at 0db8fdd  run_session_leg  -> src/core/open/sessions.cpp:383, declared sessions.hpp:89,
                                called from src/cli/main.cpp:357
```

**And then the finding that matters more.** `A3.2(2)`, which r7 bound, is the **inner** probe guard.
`A3.2(4)` names a **second** suppression path and says why it is the worse one:

```text
A3.2(4)  "THE OUTER CARRIER PREDICATE MUST COUNT SKIPPED ENTRIES — AND `M3-J-4` IS WHAT MAKES THIS
          NECESSARY. rev2's `A3.2(2)` bound the INNER probe guard and stopped there. It is not the
          only suppression path, and THE OUTER ONE IS WORSE BECAUSE THIS ADDENDUM'S OWN CONSUMED
          OBLIGATION CREATES IT."
```

**The mechanism, spelled out so the test can be written from it:** `M3-J-4` makes counts **exclude**
non-importable entries. An image whose entries are **all** over-schema therefore has **zero** eligible
sessions. The outer `any_sessions()` gate reads that zero and closes. **The notice never renders — and
because exit 0 is coupled to the notice, exit 0 is earned on an image where EVERYTHING was lost, silently.**
**The obligation this addendum consumes is what creates the hole.** r7 bound the inner guard and would have
shipped straight past this.

## 2. Both suppression paths, bound, with a mutation falsifier each

```text
INNER (A3.2(2))   the emission MUST NOT be nested under the capability/probe guard
                  (`agent.caps.has_value() && agent.caps->probe.has_value()`, or the
                  readable-newer-than-survey branch). The skip line is emitted on the agent's
                  SKIPPED COUNT ALONE, as a PEER of the existing guarded blocks and NEVER inside one.
  FALSIFIER       move the emission inside that guard; agent with NO probe, skipped count >= 1
                  -> the suite MUST go RED (notice absent, exit 0 reachable with loss unannounced)
OUTER (A3.2(4))   the OUTER carrier predicate MUST COUNT SKIPPED ENTRIES, so an all-skipped image
                  still admits the preview and still emits.
  FALSIFIER       an ALL-SKIPPED image (zero eligible, skipped >= 1) through the UNMODIFIED outer
                  predicate -> the suite MUST go RED. This is the case where the loss is TOTAL and
                  the disclosure is the only thing standing between the operator and a silent zero.
PLACEMENT (A3.2(3))  pre-write, on the path actually taken, BEFORE `render_summary`, on the universal
                  probe channel — the `run_session_leg` leg (`sessions.cpp:383`, called `main.cpp:357`).
                  The carrier is J's and is consumed UNCHANGED: this adds a line, it does not redesign.
  FALSIFIER       move the emission after the first write (or past `render_summary`)
                  -> the suite MUST go RED
```

**If any of those three mutations leaves the suite GREEN, that rule is unprotected and the plan says so
rather than claiming coverage.** All three are the same discipline as `FX-A12-3`'s cycle-member leg: a rule
whose entire value is excluding the natural-but-wrong implementation must be tested by the thing that kills
that implementation.

## 3. Everything else in r7 stands

The three-pin binding; `A3.1`'s golden byte-exact notice and `A3.2(1)`'s zero-renders-nothing rule; `A3.3`'s
`entry_schema_skipped_count` beside `primary_count`/`descendant_count` with no removal and no re-type;
`A3.4`/`A3.7`'s fact boundaries; the count source and cardinality remaining m-1's; the three-halves scope
with the **consumer half NAMED-IF-GRANTED and `src/core/open/sessions.cpp` HARD-OUT** until the operator's
generalization lands; stages 1a → 1b-i → 1b-ii; the **merge-gate predicate** (no schema-2-capable head lands
before M3-J-4..7 is in force at a named receipt SHA) with the **1a-merges-early narrowing still REFUSED**;
the manifest half under the (A) fence and m-1's byte-level veto with the three STOPs and five VETOES; the
J-capable reader transition and its three schema tests; the **base-`0db8fdd`-binary** compatibility
falsifier; `FX-A12-3`'s never-executed legs owed at 1b-i with the least-of-component mutation falsifier; the
cap carrier, the atomic-absence oracle and the three semantic killing arms; A3's four checks on ONE
`codex.cpp` head; sandbox guards and the credential decoy, **NEVER the live `~/.claude`/`~/.codex`**; macOS
plus **governing** local Ubuntu 24.04 `linux/amd64` Docker with **Actions NOT invoked**; the base-container
control; branch cut from `origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; the
token-time seven-element tuple with **all three hashes re-derived at that act**. **Stage 0 ACCEPTED and
unpublished at `dca6b7d`.** **Routing per `021028`: no cross-domain destination named.**

## 4. What I am asking of you

**A plan review of r7 as amended by this relay.** Is the outer-predicate hole stated so a test can be written
from it without re-reading m3-addendum-3; are all three mutation falsifiers ones that would actually go RED
against the natural-but-wrong implementation; and does anything here interpret m3-addendum-3 rather than read
it? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no backticks;
remarks via em-dash only, per the matcher's recorded grammar). **On approve, Stages 1a and 1b-i are
dispatchable to BUILD; nothing merges.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read `A3.2(3)` and `A3.2(4)` at m3-addendum-3's sealed bytes (`a016f953`), and located `run_session_leg` at `0db8fdd` (`sessions.cpp:383`, `sessions.hpp:89`, called from `main.cpp:357`); the three pin hashes were re-derived at r7's act and are not re-claimed fresh here; this relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion from the first sweep; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7B-TWO-SUPPRESSION-PATHS-BOUND-20260814-131510.md` → `s4-floor.implementer`; **AMENDS r7 `130641`, does not replace it** — everything not named here stands
- **you were right that r7 missed the pre-write placement, and chasing it found the bigger thing:** `A3.2(2)` binds only the INNER probe guard, and `A3.2(4)` names an OUTER suppression path the document calls WORSE because **this addendum's own consumed obligation creates it**
- **the outer hole, spelled out so a test writes from it:** `M3-J-4` makes counts EXCLUDE non-importable entries, so an ALL-SKIPPED image has ZERO eligible sessions, the outer `any_sessions()` gate reads that zero and closes, the notice never renders — and since exit 0 is coupled to the notice, **exit 0 is earned on an image where EVERYTHING was lost, silently.** r7 would have shipped past it
- **three mutation falsifiers, each of which must go RED:** (i) nest the emission inside the probe guard, unprobed agent, skipped ≥ 1; (ii) an ALL-SKIPPED image through the UNMODIFIED outer predicate; (iii) move the emission after the first write or past `render_summary`. **If any leaves the suite GREEN, that rule is unprotected and the plan says so rather than claiming coverage**
- **placement bound (A3.2(3)):** pre-write, on the path actually taken, BEFORE `render_summary`, universal probe channel — the `run_session_leg` leg (`sessions.cpp:383`, called from `main.cpp:357`); the carrier is J's and is consumed UNCHANGED
- full consumer identity now carried in the header (lock id, target hash, target commit, post-stamp) so the successor binds it mechanically rather than in prose
- everything else in r7 stands incl. the merge gate, the refused narrowing, the three-halves scope with `sessions.cpp` HARD-OUT, and Stage 0 ACCEPTED at `dca6b7d`; release hold ABSOLUTE
