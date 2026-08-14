## PLAN (successor r7, slice E) — **three pins, all re-derived at this act, all three live files carrying disclosed one-hunk lock stamps.** The consumer half is no longer an undetermined cell: m3-addendum-3 locks the notice **byte-exact** and the envelope key. **And reading it at the sealed bytes rather than the carry-down paid for itself immediately — `A3.2(2)` is a rule the document itself calls "the load-bearing rule of this document and INVISIBLE FROM J ALONE": the skip notice MUST NOT be nested under the capability/probe guard, because the obvious place to put it is inside that block and that is the WRONG place.** Nested, an unprobed agent emits no notice, and since **exit 0 is coupled to the notice**, exit 0 gets earned with the loss unannounced. **I have made that a killing test rather than a warning.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r7
PARENT_DISPATCH_ID: s4-floor-slice-e-design-complete
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this PLAN — the design side is complete at three pins. The operator's scope generalization is OPEN and NON-BLOCKING; it settles only WHO writes the consumer half. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-DESIGN-COMPLETE-THREE-PINS-FLOOR-IS-YOURS-20260814-130122.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R6-LAND-ORDER-BOUND-J-MOVED-DISCLOSED-20260813-033817.md (r6 — the merge-gate predicate and the refused narrowing carry forward); .relays/s4/s4-floor-impl/CORRECTION-PLANNER-M3-CELL-ROUTES-VIA-MASTER-NOT-DIRECT-20260813-021028.md (routing: UP only)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r7) — three pins bound; consumer notice/envelope key read at the sealed bytes with A3.2(2) as a killing test; stages and land order carried

## 0. Three pins, RE-DERIVED AT THIS ACT

```text
addendum-12    @ 6eeeb157   29a5b3a3abb6777a…   == DESIGN_LOCK_ID                      MATCH
J              @ e30f845    94b6440c6ea5342a…   == CONSUMED_CONTRACT                   MATCH
m3-addendum-3  @ a016f953   eeb4dd01cc907b5d…   == the consumer contract               MATCH
  path  master/domains/m-3-restore-cli/design/2026-08-13-addendum-3-j-consumer-notice-and-envelope-key.md
  live  cefd3f799b571bea…   post-stamp; ONE commit after (5a07a2d 12:48:23 "lock taken"),
        ONE hunk, 15 insertions / 4 deletions, head region — hunk count verified BY ME
origin/main    0db8fdd      unchanged; 0 `parent_id` hits under src/core/manifest
```

**All three live files now carry disclosed one-hunk lock stamps** (`d0e2c6eb`, `79d8dde5`, `cefd3f79`), and
**none can hash to its locked value by construction.** Recorded together so the token-time "no later unlocked
normative edit" check meets three expected post-stamps rather than three phantom drifts.

## 1. The consumer contract, read at the sealed bytes

```text
A3.1  THE NOTICE IS GOLDEN / BYTE-EXACT — "<agent>: <eligible> session(s) can be imported;
      <skipped> session(s) will be skipped — the skipped session(s) are recorded in a format this
      version of biv cannot read and are not counted among the <eligible>. Nothing has been written
      yet; a newer version of biv may be able to import them."
      Two-space indent, "<agent>: " prefix — a SIBLING of the existing per-agent notice family.
A3.2(1)  renders when that agent's skipped count is >= 1. At 0 IT DOES NOT RENDER AT ALL — no
      "will skip 0". A zero line teaches the reader the line is usually noise, which is exactly the
      training you do not want on the one line that discloses loss.
A3.2(2)  ** THE LOAD-BEARING RULE, AND THE DOCUMENT SAYS IT IS INVISIBLE FROM J ALONE **
      The emission MUST NOT be nested under the capability/probe guard. At 0db8fdd every line
      render_probe_disclosure emits sits under `agent.caps.has_value() && agent.caps->probe.has_value()`
      (or the readable-newer-than-survey branch). THE OBVIOUS PLACE TO ADD THE LINE IS INSIDE THAT
      BLOCK AND THAT IS THE WRONG PLACE: an agent whose host version could not be probed would emit
      NO skip notice — suppressed by a condition with NOTHING to do with the skip.
A3.3  ENVELOPE KEY `entry_schema_skipped_count`, per-agent, beside `primary_count` and
      `descendant_count` (M3-J-3's additive keys: no removal, no re-type). Renamed from
      `skipped_count` because J requires that these MUST NOT share a counter.
A3.4/A3.7  fact boundaries — what the notice must NOT say, stated so they cannot be over-read.
NOT m-3's  the count SOURCE and its cardinality are m-1's.
```

**The consequence that makes A3.2(2) a test and not a note:** J couples **exit 0** to this notice — *"exit 0
must be UNREACHABLE without M3-J-5's notice,"* mutation-enforced. **A notice suppressible by an unrelated
guard lets exit 0 be earned with the outcome unannounced — the exact property the coupling exists to
prevent.** So:

```text
KILLING TEST (consumer half): move the notice emission INSIDE the capability/probe guard as a disposable
mutation, with an agent whose probe is absent and whose skipped count is >= 1.
  EXPECT: the suite goes RED — the notice is missing and exit 0 is reachable with loss unannounced.
  If the suite stays GREEN, the guard placement is unprotected and the rule is decoration.
Plus: byte-exact notice text (golden); zero-count renders NOTHING; `entry_schema_skipped_count` present
in the envelope beside `primary_count`/`descendant_count`, no removal and no re-type of either.
```

**This is the same shape as `FX-A12-3`'s cycle-member leg** — a rule whose whole value is that it excludes
the natural-but-wrong implementation, so the test must be the one that kills that implementation.

## 2. Scope — three halves, two writable now

```text
MANIFEST HALF (writable now, (A) fence + m-1 BYTE-LEVEL VETO, J's sealed text ONLY)
  src/core/manifest/manifest.hpp   SessionChild gains std::optional<std::string> parent_id
  src/core/manifest/manifest.cpp   parse_session_children validation + the four caps + the writer's
                                   absence-licensed emission + the entry_schema bump + the J-capable
                                   reader transition (supported max -> 2)
  tests/test_manifest.cpp
ADAPTER HALF (writable now)
  src/adapters/adapter.hpp · src/adapters/codex/codex.cpp (ANCHORED — A3 fires) ·
  src/adapters/codex/install.cpp · src/core/pack/pack.cpp
  tests/test_adapter_codex_collect.cpp · tests/test_adapter_codex_install.cpp ·
  tests/test_adapter_claude_collect.cpp · tests/test_pack.cpp · tests/fixtures/slice-e/** ·
  harness/bivharness/e3.py (codex pin ONLY, inside the single anchored head)
CONSUMER HALF (NOT writable at this seat yet — see §3)
  src/core/open/sessions.cpp and its render/envelope surfaces — M3-J-4..7 against m3-addendum-3
  tests/test_cli.cpp · tests/test_sessions.cpp · tests/test_render.cpp · tests/test_envelope.cpp
STILL HARD-OUT
  .github/** · sealed docs · every path not named above
```

## 3. Who writes the consumer half — OPEN above me, and I plan for both without choosing

**The operator's scope generalization is not mine and I do not pre-empt it.** The plan is written so that
either answer costs one revision of the SCOPE table and nothing else:

```text
IF GENERALIZED   the consumer half becomes ours on `core/open`, under m-3's byte-level veto exactly as the
                 manifest half sits under m-1's, with m3-addendum-3's STOPs treated the way m-1's are.
IF NOT           m-3 implements it; our Stage 1b-ii COUPLES to their landed SHA and we write only the
                 E2E that consumes it.
UNTIL IT LANDS   `src/core/open/sessions.cpp` and its render/envelope surfaces are HARD-OUT. I name them
                 above as scope-IF-granted, NOT as scope taken.
```

## 4. Stages and the land order

```text
STAGE 1a   manifest half. Own exact commit. STOPS for m-1's byte-level approval/veto before any 1b byte.
STAGE 1b-i adapter half. Starts on m-1's approval; receipt-independent per r5's measured include-boundary
           (test_adapter_codex_install.cpp does not include core/open/sessions.hpp; test_cli.cpp drives
           BIV_BINARY_PATH). Seven of the eight keys complete here, plus the caps and the cap carrier.
STAGE 1b-ii consumer half + the shipped-binary R<-P<-C E2E. Gated on §3's answer and, if m-3 writes it,
           on their landed SHA.
MERGE GATE (r6, carried) NO head that CAN PRODUCE a schema-2 image merges to origin/main until M3-J-4..7
           are IN FORCE at a named SHA. Building is not shipping. The narrowing I refused in r6 — that 1a
           alone cannot emit schema 2 and might merge early — STAYS REFUSED pending the orchestrator's
           answer; until then nothing merges.
```

## 5. The killing tests, complete

`FX-A12-1a/1b/2/3/4/4a/5/6/7` per r5, **with `FX-A12-3`'s never-executed legs owed at 1b-i**: the
cycle-member primary, exactly-once carriage and named-omitted-edge assertions must be shown **executing and
passing**, and the cycle-member leg shown **failing against a least-of-component implementation** — an
assertion nobody has watched run protects nothing. Plus the manifest half's three schema tests (schema 2
accepted in full, 3 and 99 still skipped) and the **base-`0db8fdd`-binary** compatibility falsifier, since
the new head cannot impersonate the pre-J reader. Plus §1's four consumer-side tests when that half is ours.

## 6. Carried unchanged

The three STOPs and five VETOES verbatim under m-1's veto; J's determining text at the sealed bytes
(J-R1's wire shape and explicit-primary refusal, J-R5's present-null refusal, J-R3's conditional bump,
M4-CG-6's validation order with the iterative visited-set validator, M4-CG-4's four caps with the
1025th-element short-circuit); the `parse_session_children` primary-threading fact to be NAMED in the report;
the `ArchiveWriteFailed` cap carrier at exit 4 with both names in `detail` and `facts` as the structured
duplicate; the atomic-absence cap+1 oracle on the three source-derived paths with its at-cap positive arm;
the three semantic killing arms; key 5 atomic; A3's four checks on ONE `codex.cpp` head with its ONE pin,
`codex/install.cpp` moving no pin and the claude pin frozen; sandbox guards and the credential decoy,
**NEVER the live `~/.claude`/`~/.codex`**; the corpus basis as locked with `1702` cited nowhere; macOS plus
**governing** local Ubuntu 24.04 `linux/amd64` Docker, **Actions NOT invoked**; the base-container control;
branch cut from `origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; the token-time
seven-element tuple with **all three hashes re-derived at that act**. **Stage 0 remains ACCEPTED and
unpublished at `dca6b7d`.** **Routing per `021028`: this plan names no cross-domain destination.**

## 7. What I am asking of you

**A plan review.** Is `A3.2(2)` bound as a test that actually kills the nested-guard implementation rather
than as a caution; is the three-halves scope table honest about what is taken versus what is named-if-granted;
does the merge gate still read unambiguously with a third pin in play; and is anything in §1 an
interpretation of m3-addendum-3 rather than a reading of it? Reply with `PLAN_REVIEW_VERDICT: approve` or
`must-revise` (verdict line BARE — no bold, no backticks; remarks via em-dash only, per the matcher's
recorded grammar). **On approve, Stages 1a and 1b-i are dispatchable to BUILD; nothing merges.** Merge ≠
push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed addendum-12 at `6eeeb157`, J at `e30f845` and m3-addendum-3 at `a016f953` (all three MATCH their locks), identified m3-addendum-3's live post-stamp `cefd3f79` and measured its cause `5a07a2d` as ONE hunk / 15+4 / head region, read `A3.1`'s golden text, `A3.2(1)`/`A3.2(2)`'s emission rules and the exit-0 coupling, and `A3.3`'s envelope key at the sealed bytes; re-measured `origin/main` (`0db8fdd`, 0 `parent_id` hits); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read immediately before appending; `--index`; `&&`-gated append→lint→commit. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion I caused and disclosed at `014257`, which stays deliberately unindexed to avoid a second inversion
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7-THREE-PINS-CONSUMER-NOTICE-BOUND-20260814-130641.md` → `s4-floor.implementer`; r6 `033817` superseded
- **THREE PINS RE-DERIVED AT THIS ACT** — addendum-12 `29a5b3a3` @ `6eeeb157`, J `94b6440c` @ `e30f845`, m3-addendum-3 `eeb4dd01` @ `a016f953`; all three live files carry DISCLOSED ONE-HUNK LOCK STAMPS (`d0e2c6eb`, `79d8dde5`, `cefd3f79`) and none can hash to its locked value by construction — recorded together so the token-time check meets three EXPECTED post-stamps, not three phantom drifts. m3's stamp measured by me at ONE hunk / 15+4
- **reading m3-addendum-3 at the sealed bytes paid for itself:** `A3.2(2)` is the document's own "load-bearing rule … INVISIBLE FROM J ALONE" — the notice MUST NOT be nested under the capability/probe guard, because the OBVIOUS place to add it is inside that block and that is the WRONG place; nested, an unprobed agent emits no notice, and **exit 0 is coupled to the notice** (J: "exit 0 must be UNREACHABLE without M3-J-5's notice"), so exit 0 gets earned with the loss unannounced
- **made a KILLING TEST, not a caution:** move the emission inside the probe guard as a disposable mutation with an unprobed agent and skipped count ≥ 1 — the suite MUST go RED; if it stays green the placement is unprotected and the rule is decoration. Plus byte-exact golden notice, zero-count renders NOTHING, and `entry_schema_skipped_count` beside `primary_count`/`descendant_count` with no removal or re-type
- **three halves, two writable now:** manifest (under (A) + m-1 veto), adapter (ours), consumer (NAMED as scope-IF-GRANTED, NOT taken — `sessions.cpp` and its render/envelope surfaces stay HARD-OUT until the operator's generalization lands). Either answer costs one revision of the scope table and nothing else
- stages 1a → 1b-i → 1b-ii with r6's **MERGE-GATE predicate carried**: no head that can produce a schema-2 image merges until M3-J-4..7 are in force at a named SHA; **the 1a-merges-early narrowing STAYS REFUSED** pending the orchestrator's answer
- `FX-A12-3`'s never-executed legs still owed at 1b-i (executing+passing, and the cycle-member leg failing vs a least-of-component impl); the three schema tests and the **base-binary** compatibility falsifier; everything else carries; Stage 0 ACCEPTED at `dca6b7d`; **on approve 1a and 1b-i are dispatchable to BUILD and nothing merges**; release hold ABSOLUTE
