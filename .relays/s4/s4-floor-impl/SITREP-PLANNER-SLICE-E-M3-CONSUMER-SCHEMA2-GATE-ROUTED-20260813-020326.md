## SITREP — routing the m-3 consumer gate UP, and **the notable thing is HOW it surfaced: STOP #2 fired at PLAN-REVIEW time rather than at a keyboard.** The pre-named silences were bound precisely because a builder cannot see a silence in a document they did not author — and here the silence was found by a reviewer reading the CONSUMER, three files away from the schema we were authorized to write. **Measured: a J-capable manifest parser is not sufficient for the round trip, because `src/core/open/sessions.cpp` — m-3's surface, HARD-OUT for this pair — skips every `entry_schema > 1` entry at two sites, so `biv open` would validate the transitive entry and then decline to install it.** The three-level E2E cannot green without an m-3 receipt. **I am not widening into `sessions.cpp` and I am not inferring the threshold.**

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-m3-consumer-gate
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r3
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — an m-3 disposition/receipt defining the J-capable supported-schema threshold and its consumer obligations. Not this pair's to decide: `sessions.cpp` is m-3's surface and is hard-out under the current fence, which the operator's (A) ruling extended only to `src/core/manifest` for J's sealed text. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R3-MUST-REVISE-SCHEMA2-CONSUMER-GATE-20260813-014707.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-2.planner, m-3.planner
SUBJECT: SITREP — m-3's consumer skips every schema-2 entry at sessions.cpp:345/:410; the three-level E2E cannot green without an m-3 receipt; routed, not absorbed

## 1. Measured at `0db8fdd`, at my seat

```text
src/core/open/sessions.cpp:345
  found->entry_schema_skipped = found->entry_schema_skipped || entry.entry_schema > 1;
      -> the PREVIEW marks the agent as carrying skipped entries
src/core/open/sessions.cpp:410
  } else if (entry.entry_schema > 1) {
        rows.push_back(... Row::unknown_agent_skipped, .reason = "entry-schema" ...)
      -> the INSTALL path emits a skipped row and NEVER reaches the Codex installer
```

**So the chain breaks one file past our fence.** J-R3 has a J writer emit `entry_schema = 2` whenever a
child carries a present `parent_id`; our extended fence lets us make the manifest PARSER J-capable; and then
**m-3's consumer skips exactly those entries.** `biv open` would parse and validate the transitive tree and
then decline to install it, with reason `entry-schema`. **The honest `R←P←C` shipped-binary round trip — the
operator's own acceptance criterion for this slice — cannot green in that state.**

**There is also no named threshold to move.** The supported-schema boundary is a bare literal `1` in three
places (`manifest.cpp:222` `< 1`, `:225` `> 1`, `manifest.hpp:62`'s default) plus the two `sessions.cpp`
sites above. **Deciding what the supported maximum IS, and what a consumer does with entries above it, is a
contract question — not a mechanical edit.**

## 2. Why this is a STOP and not a judgement call — the mechanism worked

**This is STOP #2 firing.** The bound text says J-R6 and J-R7 **originate on m-3's surface**, are carried in
J but **owned there**, must be implemented as written and **never re-derived from J's reasoning**, and that a
question goes **to m-3, not to the keyboard**. J's own disclosed-skip exit class is derived in its text from
m-3's `213920` on sealed `m3-addendum-1 §A1.2b` — so the consumer half was always m-3's.

**What is worth recording is the timing.** The STOP list exists because a silence is invisible from outside
the authoring seat. **It fired at PLAN-REVIEW, before a line was written, found by a reviewer reading the
CONSUMER rather than the contract.** That is the pre-named-silence mechanism doing exactly what it was bound
to do, and it is the second time this cycle that reading three files away from the authorized surface has
caught something the authorized surface could not show.

## 3. What the m-3 receipt must define (stated so it is checkable, not approximate)

```text
(a) the J-CAPABLE SUPPORTED-SCHEMA THRESHOLD — what maximum entry_schema this consumer supports, and
    therefore which entries are parsed/installed vs disclosed-and-skipped
(b) the CONSUMER OBLIGATIONS for J-R3 / J-R6 / J-R7 on m-3's surface: the disclosed-skip class, its
    COUNT vs BOOLEAN rendering (J notes entry_schema_skipped becomes a COUNT because a boolean cannot
    say how many), the envelope's treatment of skipped entries, and the exit class
(c) whether sessions.cpp:345 and :410 change, and IF SO WHO WRITES THEM — this pair has no authority
    over that surface and is not requesting any
(d) the RECEIPT SHA on origin/main at which the above is implemented, so Stage 1b and the E2E can gate
    on a fact rather than an expectation
```

**I am asking for a disposition, not proposing one.** Two things I explicitly am NOT doing: inferring the
threshold from J's reasoning (STOP #2 forbids exactly that), and quietly widening this pair into
`sessions.cpp` because the E2E needs it. **"Required for the granted act" is not "authorized" — that lesson
is already on this lane's record and cost a hand-up.**

## 4. What this does and does not block

```text
BLOCKED on the m-3 receipt   Stage 1b's shipped-binary R<-P<-C E2E (the acceptance instrument)
NOT BLOCKED                  Stage 1a (J's sealed manifest schema) — parser, writer, caps, the bump —
                             under m-1's byte-level veto, and its own killing tests at the manifest layer
```

**So the slice is not parked again; it is narrowed.** Stage 1a can proceed on its own merits once my
successor plan clears review, with the E2E and Stage 1b gated behind the receipt. My revised plan (filing
immediately after this) makes that conditionality explicit rather than leaving the E2E as an unqualified
deliverable.

## 5. Holds

Stage 0 remains ACCEPTED and UNPUBLISHED at `dca6b7d`. No token has issued. No product byte exists for
Stage 1. No push, PR, Actions, merge, seal, deployment or release. Merge ≠ push ≠ release; the release hold
is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only measurement at `0db8fdd` of `sessions.cpp:345` and `:410`, the `entry_schema` literals at `manifest.cpp:222`/`:225` and `manifest.hpp:62`, and the absence of any named supported-schema constant; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read immediately before appending; `--index`; **and the append→lint→commit chain is `&&`-GATED end to end this time**, per my `014257` disclosure. Disclosed reds: INDEX line 222 (inherited) and the tail inversion at `013935`/`014004` that I caused and disclosed at `014257`. **That `014257` disclosure relay is deliberately UNINDEXED** — its stamp now precedes the INDEX tail, so appending it would create a SECOND inversion; it is discoverable via this row instead, at `.relays/s4/s4-floor-impl/SITREP-PLANNER-INDEX-SWEEP-AND-INVERSION-DISCLOSED-20260813-014257.md`
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-M3-CONSUMER-SCHEMA2-GATE-ROUTED-20260813-020326.md` → `s4.orchestrator-planner` → `m-3.planner`
- **MEASURED: `sessions.cpp:345` sets `entry_schema_skipped` and `:410` emits `unknown_agent_skipped` reason `entry-schema` for every `entry_schema > 1`** — so a J-capable PARSER is NOT sufficient; `biv open` would validate the transitive tree and then decline to install it, and the shipped-binary `R←P←C` round trip CANNOT GREEN
- there is no named threshold to move: the supported boundary is a bare literal `1` at `manifest.cpp:222`/`:225`, `manifest.hpp:62` and the two `sessions.cpp` sites — **what the supported maximum IS, and what a consumer does above it, is a CONTRACT question**
- **this is STOP #2 firing at PLAN-REVIEW time, before a line was written**, found by a reviewer reading the CONSUMER three files past the authorized surface — the pre-named-silence mechanism doing exactly what it was bound to do
- the receipt must define: (a) the J-capable supported-schema threshold; (b) the J-R3/J-R6/J-R7 consumer obligations incl. the disclosed-skip class, its COUNT-not-boolean rendering, envelope treatment and exit class; (c) whether `sessions.cpp:345`/`:410` change and WHO WRITES THEM; (d) the receipt SHA on `origin/main`
- **NOT inferring the threshold (STOP #2 forbids it) and NOT widening into `sessions.cpp` because the E2E needs it — "required for the granted act" is not "authorized"**
- BLOCKED: Stage 1b's shipped-binary E2E. NOT BLOCKED: Stage 1a (J's sealed schema) under m-1 veto. **The slice is narrowed, not parked**
- Stage 0 ACCEPTED and UNPUBLISHED at `dca6b7d`; no token, no PR, no Actions; release hold ABSOLUTE
