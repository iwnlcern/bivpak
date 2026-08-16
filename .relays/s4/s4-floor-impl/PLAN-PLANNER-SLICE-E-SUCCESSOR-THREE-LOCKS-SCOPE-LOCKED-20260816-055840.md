## PLAN (successor to the must-revised `d7db861` — scope locked against all three locks, for your review) — **the scope moved in BOTH directions from Stage 1b-ii and the reversal is the part to check first: `tests/test_manifest.cpp`, which I proved OUT last stage on a measurement (its `child_count` was a local, not an `AgentPreview` member), comes back IN for an unrelated reason — it holds the `entry_schema == 99` future-schema assertions at `:595`/`:624`/`:643` that `FX-K-1` must BIND rather than replace. Same file, opposite disposition, different ground. And `src/cli/main.cpp` goes OUT: the five-surface split from 1b-ii already stands, and A4's kind never reaches the CLI — it flows row → `kind_for_row` → `exit_for_sessions` → envelope, entirely below it.** **I re-scanned the comparison-class baseline with a WIDER net than the claim that produced it — every `entry_schema` comparison in `src` AND `tests`, both directions — and it confirms exactly four production sites and no others: `manifest.cpp:347` (`< 1` validity floor, PRESERVED BY NAME per K-R3(1)), `manifest.cpp:350` (`> 2` → the K constant), `sessions.cpp:349`/`:419` (the two supported sites). I widened deliberately because I shipped a false enumeration two relays ago from a type-narrow grep, and because K's own rev2 folded a STOP that was already tripped by that same `< 1` site — m-1 named the identical one-directional-instrument fingerprint. Two seats, one instrument class, one baseline: it deserved a third look.** **THE SUPPORTED CEILING IS A NEW CONSTANT AT VALUE 1 — not 2. Cell 3 is closed on operator arm A, the schema-2-capable reader is `R-4.29`, and K-R2 makes the separation normative: two ceilings, two constants, NEVER one identifier, even when their values coincide. Legs {l, m, n, o} witness at this head; leg (p) is built and GATED, and I am binding its deferral to a guard keyed on the two constants themselves so it cannot outlive its world — a hidden tag would report success while asserting nothing.** **NO TOKEN HERE. The `DISPATCH IMPL` follows your approve, and W-1's seven-element tuple gets re-derived at that act, not this one.** Land order binds; branch LOCAL and UNPUBLISHED; release hold ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-three-locks
PARENT_DISPATCH_ID: s4-floor-slice-e-successor-released-three-locks
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-SUCCESSOR-RELEASED-ALL-THREE-LOCKS-CELLS-CLOSED-20260816-055058.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — your plan-review is the plan gate; m-1's byte review covers every `src/core/manifest/**` byte and m-3's successor re-review gates the hand-up. This relay grants no work authority and issues no token. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN — slice E successor scope locked against A4 9049de44 + A5 b8686c75 + K 5da667fa, each fold attributed; fourteen IN paths with per-row evidence; test_manifest.cpp reverses IN, main.cpp goes OUT; leg (p) deferral keyed to the two constants

## 1. Locks re-derived at my seat, and both docs read in full

```text
A4  9049de443e8ecc91ff72c291e85fd1c0c3c8876ac6deed28265fb10154600746 @ 40bd88a6   EQUAL
A5  b8686c75753558d5c8825403446afab70a3b18ffef8cdf65faf31763cc670545 @ c57067fe   EQUAL
K   5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667 @ 0e455ef5   EQUAL
    K LIVE post-stamp b715060935dce6fa9545a62a471e6189c080a71157cedc080633c520ea9e6a6b == declared
```

K read in full at the pinned blob. **Its own revision history is worth your attention before you review my scope:** rev3 folded *"K-R2 said 'after the A4 fold both equal 2' — A TEMPORAL CLAIM LOCKED A4 DOES NOT AUTHORIZE"*, tracing the premise back through the `035059`/`040222` chain; rev2 folded a STOP already tripped by `manifest.cpp:347`. **Both are the cells I routed, independently re-derived by m-1 and folded into normative text.** That is corroboration, not vindication — and it means the current K text is the one place where those two corrections are load-bearing rather than narrative.

## 2. The three folds, each attributed to its OWN lock (cross-identity fence)

```text
A4 9049de44   ErrKind::EntrySchemaSkipped · wire "EntrySchemaSkipped" · exit 0 EARNED by the
              pre-write M3-J-5 notice · UnknownAgentSkipped stays distinct at exit 2 ·
              worst-outcome std::max composition preserved
A5 b8686c75   A5.2 <skipped> = Σ (1 + children_known) · A5.3 both at-least golden variants ·
              A5.4 entry_schema_unparsed_count (per-agent, additive, suppressed at zero) ·
              legs {l,m,n,o} witnessed · leg (p) implemented-and-gated
K  5da667fa   kEntrySchemaParseCeiling, int, value 2, in manifest.hpp beside kFormatVersion/
              kManifestByteCap · manifest.cpp's OWN gate uses it · the preview's stub
              discriminator uses the SAME identifier and never a copy · FX-K-1 (a)+(b)
m-3 065233    the ONE shared SUPPORTED-ceiling constant across sessions.cpp:349 and :419,
              AT VALUE 1, in one commit
```

**No lock authorizes another's fold.** A4's identity does not grant A5's key or K's export; K's export does not grant the supported constant, which is m-3's.

## 3. Scope

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/support/error.hpp -> in
- src/core/support/error.cpp -> in
- src/core/report/envelope.cpp -> in
- src/core/open/sessions.hpp -> in
- src/core/open/sessions.cpp -> in
- src/core/open/render.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_render.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_cli.cpp -> in
- tests/fixtures/slice-e/** -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `src/core/manifest/manifest.hpp` — K-R1 LOCATION names this header explicitly, "beside `kFormatVersion` / `kManifestByteCap`, `inline constexpr int`"; both siblings verified present at `:13-14`.
- `src/core/manifest/manifest.cpp` — K-R1 mandatory use (1): the `> 2` literal at `:350` is REPLACED by the constant. `:347`'s `< 1` validity floor is PRESERVED BY NAME per K-R3(1) and is explicitly NOT a STOP.
- `src/core/support/error.hpp` — the `ErrKind` enum; `UnknownAgentSkipped` sits at `:28` and the new member joins it (A4.1).
- `src/core/support/error.cpp` — `to_string`'s wire spellings; `"UnknownAgentSkipped"` at `:43-44` and the new `"EntrySchemaSkipped"` beside it (A4.1, PascalCase per that file's convention).
- `src/core/report/envelope.cpp` — `exit_for_error` at `:390` gains the new kind's row at **0** (A4.1/A4.2); the open-side per-agent object gains `entry_schema_unparsed_count` (A5.4). **Pack-side `write_manifest_summary` remains a within-file hard-out (V11).**
- `src/core/open/sessions.hpp` — the ONE shared supported-ceiling constant's declaration site, and `entry_schema_unparsed_count` on `AgentPreview` beside `entry_schema_skipped_count` at `:22`.
- `src/core/open/sessions.cpp` — `:349`/`:419` unified under the shared supported constant at value 1 (m-3 `065233`); the stub discriminator comparing against `kEntrySchemaParseCeiling` (K-R1 use 2); the unparsed accumulator; A5.2's `1 + children_known`; and `kind_for_row` at `:259-268` splitting on `reason == "entry-schema"` — **it already takes `reason`, so the A4 split needs no signature change.**
- `src/core/open/render.cpp` — A5.3's at-least prefix in BOTH golden lines (the A3.1 notice at `:235-242`, the A3.2(5) aggregate at `:309+`).
- `tests/test_manifest.cpp` — **the reversal.** FX-K-1 lives here: `(a)` boundary both sides and `(b)` stub shape, and the release's instruction is to BIND the existing baseline assertions (`entry_schema == 99` at `:595`, `:624`, `:643`) to the constant rather than author a fresh shape.
- `tests/test_sessions.cpp` — the count-source, the two discriminators, the unparsed accumulator, `kind_for_row`'s split.
- `tests/test_render.cpp` — A5.3's exact/at-least golden pairs.
- `tests/test_envelope.cpp` — A5.4's key present/absent, and the A4 wire string in the envelope.
- `tests/test_cli.cpp` — A4 legs (a)–(d) need whole-run invocations (exit codes, composition, the coupling mutant); A5 legs (l)/(m)/(n)/(o) assert notice + summary + envelope together on one run.
- `tests/fixtures/slice-e/**` — the leg populations do not exist: childed parsed-but-held, childed-wire stubbed at schema 3, mixed shapes, the two-agent asymmetric distribution for (p), and FX-K-1's boundary pair.

**OUT, each with its ground — a discovered need for any of these is a STOP, not a licence:**

```text
src/cli/main.cpp            the five-surface split from 1b-ii already stands; A4's kind never
                            reaches the CLI — row -> kind_for_row -> exit_for_sessions ->
                            envelope, entirely below it. TIGHTER than 1b-ii, deliberately.
src/core/open/render.hpp    NO signature change: render_summary already takes the preview
                            (added 1b-ii) and render_probe_disclosure always did, so the
                            at-least prefix reads entry_schema_unparsed_count from data both
                            renderers already receive. Any helper must be FILE-LOCAL.
src/core/pack/**            K-R2: "the writer's stamp domain (1..2) is J-R3's and does not
                            move with the parse ceiling."
manifest-format.md          NOT IN THIS REPO — verified; K's identity site 3 is m-1's pdc
                            annotation and already applied at K's rev.
```

## 4. Three WITHIN-FILE boundaries — function-scoped evidence required at hand-up

A path grant is not a file grant, and two of these ride inside newly-granted files:

```text
manifest.cpp    ONLY the :350 gate literal -> constant. The :347 `< 1` floor is preserved BY
                NAME. K-R3(3): NO other export-surface change — no moving, renaming or
                re-typing any existing exported symbol while landing this one.
envelope.cpp    write_manifest_summary (pack-side) UNTOUCHED — V11. exit_for_error gains
                exactly ONE row.
sessions.cpp    any_sessions() body UNTOUCHED. K-R3(2): a THIRD adjacent discriminator in
                build_preview's skipped branch is a STOP — we will have exactly TWO, the skip
                test and the stub test.
```

## 5. K's vetoes and STOPs — the review is a checklist

```text
K-R4(1)  any surviving literal parse-ceiling comparison at ANY site, INCLUDING manifest's own gate
K-R4(2)  the constant defined in more than one place, or the preview holding a copy
K-R4(3)  both ceilings expressed through ONE identifier (K-R2's merge)
K-R4(4)  a type mismatch forcing a cast at any comparison site — TYPE is int, entry_schema's own
K-R4(5)  any silent filling of a K-R3 STOP
K-R3(1)  a NEW upper-boundary/discriminator class over entry_schema -> STOP to m-1
         (the `< 1` validity floor is EXPLICITLY preserved and is NOT this)
K-R3(2)  a third adjacent discriminator in build_preview's skipped branch -> STOP
K-R3(3)  any export-surface change beyond the one addition -> STOP
```

**V1–V11 continue to bind** from the m-3 side, and **A5's own boundaries**: `A5.4`'s cause vocabulary retained, suppress-at-zero conforming to `FX-J-1(p)`, and `A3.7(1)` still governing if m-1's cardinality facts move.

## 6. Acceptance — determined at supported = 1

| Lock | Leg | Assertion | Mutant that must go RED |
|---|---|---|---|
| K | FX-K-1(a) | `== kEntrySchemaParseCeiling` parses FULLY (children materialized); `== +1` returns the STUB | a parser gate drifted from the constant |
| K | FX-K-1(b) | the stub carries grammar-validated `agent` + wire `entry_schema` and NOTHING else materialized | — (pinned where produced) |
| A4 | (a) | wire `"EntrySchemaSkipped"` byte-exact; run exits **0** | any other spelling; or riding `UnknownAgentSkipped` with a reason string |
| A4 | (b) | unknown-*agent* cause ⇒ `UnknownAgentSkipped`, exit **2**, on the fixture where that cause fires | map the unknown-agent cause to the new kind |
| A4 | (c) | mixed run, one install FAILS beside the skip ⇒ worst outcome by `std::max`, BOTH kinds in the envelope | let the 0-kind overwrite the composition |
| A4 | (d) | remove the `M3-J-5` notice ⇒ the exit-0 leg reddens **with the kind present** | (the mutant IS the leg) |
| A5 | (l) | childed parsed-but-held: `3 session(s)`, EXACT form, key = 3, unparsed ABSENT | count entries ⇒ 1; emit the at-least prefix |
| A5 | (m) | childed wire, STUBBED (schema 3): `at least 1 session(s)`; skipped 1, unparsed 1 | exact form; count the wire's children into the floor |
| A5 | (n) | mixed shapes, one agent: `at least 4`; skipped 4, unparsed 1 | exact form |
| A5 | (o) | co-located on (l): `primary_count`/`descendant_count` unchanged by skip arithmetic | add skipped children to `descendant_count` |
| A5 | (p) | **IMPLEMENTED AND GATED** — two-agent asymmetric distribution (A: 1/at-least-2, skipped 2, unparsed 2 · B: 1/at-least-1, skipped 1, unparsed 1) | aggregate A+B; duplicate; bleed — **witnessed at the R-4.29 flip gate, not here** |

**The at-least rule, per agent:** the prefix appears in BOTH golden lines iff that agent's `entry_schema_unparsed_count > 0`; every other byte of both templates is unchanged from `eeb4dd01`. **`children_known` is `entry.children.size()` uniformly** — A5.4's biconditional makes it exact for the parsed class and zero for stubs without a branch.

**Leg (p)'s deferral must not false-green.** A hidden tag reports success while asserting nothing. Repo precedent that does not: `[!mayfail][pending-<gate>]` (`test_adapter_claude_install.cpp:1792`) and a conditional `SKIP("…")` (`test_tar_writer.cpp:127`; the WSL cases) — **both still RUN and are still counted**, which is why "2 configured skips" was reportable as a number last stage. **Bind (p)'s guard to the two constants themselves** — deferred while the supported ceiling is below `kEntrySchemaParseCeiling` — so the day `R-4.29` flips it the leg activates with no human remembering. **Note for the byte reviewers, flagged rather than buried: that guard READS both constants in one expression. K-R4(3) vetoes both ceilings expressed through one IDENTIFIER, which this is not — but it is the nearest thing in the change to that veto, so look at it deliberately.**

## 7. Evidence and standing bars

E2. **RED-first with receipts; a compile failure earns no behavioural-RED credit.** Every mutant executed, observed RED, reverted. macOS canonical plus the **governing** local Ubuntu 24.04 `linux/amd64` Docker, with the exact-base control at `d7db861` on any change in the Linux failure count. **Actions NOT invoked.** Branch stays **LOCAL and UNPUBLISHED**. **The land order binds** and the early-merge narrowing stays REFUSED. Live `~/.claude` / `~/.codex` never read-for-mutation or written — fixture trees or explicit disposable copies only. **No credential collection.**

**Sequencing is ours:** the K export lands BEFORE or WITH the coupled commit. My recommendation is **one commit** — the export, the gate replacement, the two supported sites, the kind, the count-source, the key and the legs — because K-R4(1) vetoes any surviving literal at ANY site, and a two-commit split leaves an intermediate head where the preview's discriminator and the gate disagree. If you disagree at the bytes, say so; sequencing is a plan choice and this is the one I am least certain of.

**Returns to TWO byte reviews:** m-1 for every `src/core/manifest/**` byte, m-3 for the supported sites, stub discriminator, per-agent counts and the deferred-leg disposition together. **Any unlisted silence is a STOP** routed UP through the orchestrator.

## 8. What I want from your review

1. **§3's OUT rows** — especially `render.hpp`. I argue no signature change is needed because both renderers already receive the preview. If a file-local helper cannot express the at-least prefix, that is a STOP before you write it, not after.
2. **§4's `manifest.cpp` boundary** — is "only the `:350` literal" achievable, or does the constant's introduction force any other export-surface motion K-R3(3) would STOP?
3. **§6's leg-(p) guard** — the right shape, and whether reading both constants in one test expression is clean under K-R4(3).
4. **§7's one-commit recommendation** — the weakest judgement in this plan.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — read-only measurement this pass. pdc at the pinned blobs: all three locks re-derived EQUAL, K read IN FULL and its live post-stamp re-hashed EQUAL to the declared value. bivpak at `d7db861`: the comparison class re-scanned with a bidirectional pattern over `src` AND `tests` (four production sites confirmed, no others); `manifest.hpp`'s complete export set; the `ErrKind`/`to_string`/`exit_for_error`/`kind_for_row` sites enumerated; `render.hpp`'s current signatures read to ground the OUT row; `manifest-format.md` confirmed absent from this repo. No token issued; no work authority granted. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing; `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. **ONE ROOT-ARM RED IS MINE AND IS DISCLOSED VERBATIM, not inherited:** `DESIGN_LOCK_ID 'm1-addendum-K-5da667fa-lock-20260816' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID` — the cross-repo class B (`R-4.27`): K is a pdc-authored m-1 design and cannot produce the strictly LOCAL pair DESIGN→REVIEW→PLAN chain the walk demands, so no green is available here and none is claimed. It is exactly the class W-1 covers, **and W-1 is VOID until re-derived — the pins have moved twice, so its seven-element tuple gets re-derived against the CURRENT identities at TOKEN time, not asserted here; INAPPLICABLE/NO-TOKEN on any mismatch.** Disclosure is not a waiver and this red does not unblock a dispatch. It is 1 of 62 root errors at this root; the other 61 are the inherited historical/external-lineage classes. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — those are not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-THREE-LOCKS-SCOPE-LOCKED-20260816-055840.md` → `s4-floor.implementer` for plan-review
- SCOPE LOCKED against all three locks (A4 `9049de44` · A5 `b8686c75` · K `5da667fa`, all re-derived EQUAL, K read in full), each fold attributed to its own identity; fourteen IN paths with per-row evidence and `SCOPE_DIFF_RESULT: all-in`
- **SCOPE MOVED BOTH WAYS:** `tests/test_manifest.cpp` reverses IN — I proved it OUT last stage on a measurement, and it returns for an unrelated reason, the `entry_schema == 99` assertions at `:595`/`:624`/`:643` that FX-K-1 must BIND. `src/cli/main.cpp` goes OUT: A4's kind never reaches the CLI, flowing row → `kind_for_row` → `exit_for_sessions` → envelope below it
- BASELINE re-scanned with a WIDER, bidirectional net over `src` AND `tests`: exactly four production comparison sites (`manifest.cpp:347` `< 1` floor preserved BY NAME, `:350` `> 2` → K constant, `sessions.cpp:349`/`:419` supported), no others — widened because I shipped a false enumeration from a type-narrow grep and K's own rev2 folded a STOP tripped by that same `:347` site with m-1 naming the identical instrument fingerprint
- SUPPORTED CEILING = new constant AT VALUE 1 (not 2); cell 3 closed on operator arm A, flip deferred to `R-4.29`, and K-R2 makes two-ceilings-two-constants normative even at value coincidence
- THREE WITHIN-FILE boundaries needing function-scoped evidence: `manifest.cpp` only the `:350` literal with `:347` preserved by name and K-R3(3) barring other export motion; `envelope.cpp` pack-side untouched (V11) with `exit_for_error` gaining exactly one row; `sessions.cpp` `any_sessions()` untouched and K-R3(2) barring a third adjacent discriminator
- ACCEPTANCE determined at supported=1: FX-K-1(a)/(b), A4 (a)–(d), A5 {l,m,n,o} witnessed, (p) IMPLEMENTED-AND-GATED with its deferral **keyed to the two constants** so it cannot outlive its world — hidden tags false-green, and the repo precedent that does not is `[!mayfail][pending-…]`/conditional `SKIP`, both of which still RUN and are counted
- FLAGGED FOR THE BYTE REVIEWERS rather than buried: (p)'s guard READS both constants in one expression; K-R4(3) vetoes one IDENTIFIER expressing both, which this is not, but it is the nearest thing in the change to that veto
- Returns to TWO byte reviews (m-1 manifest bytes, m-3 consumer surface); one-commit sequencing RECOMMENDED and named as my weakest judgement; NO TOKEN — the `DISPATCH IMPL` follows your approve with W-1's seven-element tuple re-derived at THAT act; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
