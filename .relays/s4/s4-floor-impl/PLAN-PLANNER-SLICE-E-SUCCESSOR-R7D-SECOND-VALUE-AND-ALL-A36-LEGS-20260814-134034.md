## PLAN (successor r7d, slice E) — **third time you have found a survivor in a plan built on falsifiers, and this one has a name in the sealed text: the SECOND-VALUE RULE.** Every population I bound is all-skipped, so `<imported>` is `0` in all of them, and **a renderer hardcoding `0` passes r7 + r7b + r7c entire.** The design says it exactly: *"A quantity witnessed at exactly one value is not tested, it is transcribed."* **rev6 exists because rev5 had this hole — I re-created a defect the document had already paid to close.** r7d carries the exact `<imported>` membership, legs `(j)` and `(k)` with every mutant, **and the five `A3.6` legs I abbreviated away** — because you are right that shipping them serially is its own defect.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r7d
PARENT_DISPATCH_ID: s4-floor-slice-e-design-complete
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operator's consumer-scope assignment stays open and non-blocking to planning; every domain veto, the implementation token, publication and release keep their own gates. The release hold is ABSOLUTE.
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
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R7C-MUST-REVISE-IMPORTED-SECOND-VALUE-MEMBERSHIP-20260814-133118.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7C-FIVE-SURFACE-ALL-SKIPPED-CONTRACT-20260814-132749.md (r7c — five-surface matrix, MUTANT A/B and the four invocations PASSED and carry)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: PLAN (successor r7d) — `<imported>` membership + legs (j)/(k) second-value witnesses + the five omitted A3.6 legs, all with their sealed mutants

## 1. The pattern, named — because three is a pattern and not bad luck

```text
r7   bound the notice, missed A3.2(4) entirely
r7b  bound the INNER suppression path, missed the OUTER one
r7c  bound the five surfaces, missed that every one of them witnesses <imported> at ZERO
```

**Each time I bound the thing the previous review named and stopped at its edge.** The sealed text has a rule
for exactly this failure and I had read past it: **"Any operand this document introduces into a golden text
MUST be witnessed by at least one leg at a SECOND, non-trivial value, and that leg must carry a mutant that
a constant would fail."** `rev6` exists *because rev5 had this hole.* **I reproduced a defect the document
had already paid to close, one revision after it closed it.** r7d therefore carries `A3.6` **entire**, not
the next slice of it.

## 2. `<imported>` — the exact membership

```text
<imported> = SUM over HOST-INSTALLED entries of (1 + that entry's id_map children count)
  installed                    counts 1 + children
  sessions_staged              counts ZERO
  failed                       ZERO
  containment_refused          ZERO
  session_install_failed       ZERO
  unknown_agent_skipped        ZERO
  sessions_consent_skipped     ZERO
  agent_not_validated_failed   ZERO
  skipped (over-schema)        ZERO
```

**The unit is HOST-INSTALLED SESSIONS INCLUDING DESCENDANTS** — not top-level rows, not the eligible
population, not the staged population, not the attempted population. Every one of those four is a mutant
below.

## 3. The two second-value legs, carried whole

```text
(j) MIXED, CONSENT-YES, NONZERO <imported> — THE SECOND-VALUE WITNESS
    fixture  three eligible primaries, ONE OF WHICH CARRIES ONE DESCENDANT (four sessions),
             plus one over-schema entry; run with --consent yes
    assert   the A3.2(5) line reads "4 session(s) imported; 1 session(s) skipped — …" BYTE-EXACT
    MUTANT   hardcode <imported> to 0            => RED   <- the mutant every rev5 leg survived
    MUTANT   count TOP-LEVEL ROWS not sessions   => prints 3 => RED
             ^ the DESCENDANT-MEMBERSHIP witness, and the reason the fixture carries a descendant at all
    MUTANT   report <eligible> instead of installed => RED on (k)'s fixture, where the two provably differ
(k) MEMBERSHIP CONTROLS, CO-LOCATED
    fixture  two INSTALLED sessions, one that STAGES, one that FAILS, plus one over-schema entry
    assert   <imported> counts 2 — staged and failed contribute NOTHING
    MUTANT   count sessions_staged as imported  => prints 3 => RED
             ^ also proves the line does not contradict render_summary's own "Staged sessions were not
               installed into host stores" ON THE SAME SCREEN
    MUTANT   count eligible rather than installed => prints 4 => RED
    "Without this leg the membership prose in A3.2(5) is classification with no oracle."
```

## 4. The five `A3.6` legs I abbreviated away — carried with their mutants

```text
(d) CARDINALITY            2 over-schema entries => the line says 2
    MUTANT  derive the quantity from the pre-M3-J-6 BOOLEAN => RED
            ^ this is what proves M3-J-6's COUNT is actually consumed, not merely available
(e) EXIT COUPLING          removing the notice must redden the exit-0 leg on EVERY path —
                           prompt, flag, non-TTY and --json — FOUR paths, not three, because the
                           carrier is universal. Inherits J's "exit 0 must be UNREACHABLE without
                           M3-J-5's notice"; restated because A3.2(2) creates a NEW way to lose it
(f) ENVELOPE               entry_schema_skipped_count present and correct; skipped entries EXCLUDED
                           from totals
    MUTANT  include skipped entries in the totals => RED
    CO-LOCATED NEGATIVE  with ZERO over-schema entries the key is ABSENT (FX-J-1(p))
    MUTANT  emit the key carrying 0 => RED
            ^ mutation-proven rather than stated, so if m-1 later scopes FX-J-1(p) to the printed
              surface, THIS is the leg that must be revised deliberately and visibly
(g) CROSS-ARM CONTROL      this notice's text does NOT appear for the probe-failure or
                           readable-newer-than-survey causes, EVALUATED ON THE FIXTURES WHERE THOSE
                           CAUSES ACTUALLY FIRE — "worthless run anywhere else"
(i) CONSENT-NO TRUTH       same fixture as (a), run TWICE: prompt-no and explicit --consent no.
                           The notice is BYTE-IDENTICAL to (a) — it is a PRE-CONSENT disclosure and
                           the answer cannot retroactively change what was printed — and NO session
                           is imported on either run
    MUTANT  restore rev2's "will be imported" => the line asserts an import that provably did not
            occur => RED   ^ the leg that makes the eligibility wording LOAD-BEARING, not stylistic
```

**Also carried from `A3.6` and not re-abbreviated:** `(a)` positive byte-exact on a 4-eligible + 1-over-schema
image; `(b)` guard-independence with the nest-inside-`caps`/`probe` mutant — *"without this mutant the rule in
A3.2(2) is an assertion, not a test"*; `(c)` zero-skip co-located negative **asserted on a fixture where
imports DO occur, so the leg cannot pass merely because nothing rendered**; and `(h1)`/`(h2)`/`(h3a)`/`(h3b)`
per r7c, with `h3a`/`h3b` separate because one reaches the non-prompt branch by having no TTY and the other
by explicit consent, and **a single disjunctive fixture may satisfy one and leave the other unobserved.**

## 5. Carried unchanged from r7c and earlier

The five-surface all-skipped matrix with both suppression rationales; MUTANT A (eligible-only gate) and
MUTANT B (shared widening); the behavioral split stated without choosing m-1's mechanism (disclosure /
envelope / summary on eligible-or-skipped; prompt / warning on eligible alone; count source and predicate
mechanism remain m-1's); r7b's inner-guard and pre-write placement mutants at the `run_session_leg` leg;
`A3.1`'s golden notice, `A3.2(1)`'s zero-renders-nothing, `A3.3`'s envelope key with no removal or re-type,
`A3.4`/`A3.7`'s fact boundaries. The three pins and full consumer identity. **The three-halves scope with the
consumer half NAMED-IF-GRANTED and `src/core/open/sessions.cpp` HARD-OUT** until the operator assigns it.
Stages 1a → 1b-i → 1b-ii; the **merge-gate predicate** with the **1a-merges-early narrowing still REFUSED**.
The manifest half under the (A) fence and m-1's byte-level veto with the three STOPs and five VETOES; the
J-capable reader transition and its three schema tests; the **base-`0db8fdd`-binary** compatibility
falsifier; `FX-A12-3`'s never-executed legs owed at 1b-i with the least-of-component mutant; the cap carrier,
the atomic-absence oracle and the three semantic killing arms; A3's four checks on ONE `codex.cpp` head;
sandbox guards and the credential decoy, **NEVER the live `~/.claude`/`~/.codex`**; macOS plus **governing**
local Ubuntu 24.04 `linux/amd64` Docker, **Actions NOT invoked**; the base-container control; branch cut from
`origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; the token-time seven-element tuple
with all three hashes re-derived at that act. **Stage 0 ACCEPTED and unpublished at `dca6b7d`.** **Routing
per `021028`: no cross-domain destination named.**

## 6. What I am asking of you

**A plan review.** Is `A3.6` now carried **entire** — `(a)` through `(k)` with every sealed mutant — rather
than sliced; is the `<imported>` membership stated so the unit cannot be misread as rows or eligible or
staged; and do `(j)` and `(k)` together actually kill all four wrong units? **And the question I most want
answered: is there any operand or predicate left in this plan witnessed at exactly one value?** That is the
class that has beaten me three times, and the check I want run against the whole plan rather than the newest
paragraph. Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no
backticks; remarks via em-dash only, per the matcher's recorded grammar). **On approve, Stages 1a and 1b-i
are dispatchable to BUILD; nothing merges.** Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read the SECOND-VALUE RULE, the `<imported>` membership, legs `(a)`-`(k)` and every named mutant at m3-addendum-3's sealed bytes `a016f953`; the three pin hashes were re-derived at r7's act and are not re-claimed fresh; this relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion from the first sweep; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7D-SECOND-VALUE-AND-ALL-A36-LEGS-20260814-134034.md` → `s4-floor.implementer`; amends r7/r7b/r7c, everything not named here stands
- **THE PATTERN NAMED:** r7 missed `A3.2(4)`; r7b bound the inner path and missed the outer; r7c bound five surfaces and missed that all of them witness `<imported>` at ZERO. **Each time I bound what the previous review named and stopped at its edge.** The sealed **SECOND-VALUE RULE** covers exactly this — *"a quantity witnessed at exactly one value is not tested, it is transcribed"* — and **rev6 exists BECAUSE rev5 had this hole, so I re-created a defect the document had already paid to close.** r7d carries `A3.6` ENTIRE rather than the next slice
- **`<imported>` membership exact:** sum over HOST-INSTALLED entries of (1 + id_map children); staged, failed, containment_refused, session_install_failed, unknown_agent_skipped, sessions_consent_skipped, agent_not_validated_failed and skipped all count ZERO. **Unit = host-installed sessions INCLUDING DESCENDANTS** — not rows, not eligible, not staged, not attempted
- **(j) second-value witness:** 3 eligible primaries (one carrying a descendant) + 1 over-schema, `--consent yes` ⇒ "4 imported; 1 skipped" byte-exact. Mutants: hardcode 0 ⇒ RED (**the mutant every rev5 leg survived**); count top-level rows ⇒ 3 ⇒ RED (the descendant-membership witness); report eligible ⇒ RED on (k)
- **(k) membership controls:** 2 installed + 1 staged + 1 failed + 1 over-schema ⇒ `<imported>` = 2. Mutants: count staged ⇒ 3 ⇒ RED (**also proves the line does not contradict `render_summary`'s own "Staged sessions were not installed" ON THE SAME SCREEN**); count eligible ⇒ 4 ⇒ RED
- **the five omitted legs carried with mutants:** (d) cardinality 2 with the boolean-derived mutant; (e) exit coupling on FOUR paths; (f) envelope correctness + skipped-excluded totals + zero-key ABSENCE with both mutants; (g) cross-arm negatives **on the fixtures where those causes actually fire**; (i) prompt-no and `--consent no` with the `will be imported` mutant. Plus (a)/(b)/(c) unabbreviated and r7c's four `(h)` invocations
- everything else carries; **and I have asked the review to run the second-value check against the WHOLE plan rather than the newest paragraph** — that is the class that has beaten me three times; release hold ABSOLUTE
