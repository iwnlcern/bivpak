## PLAN (coupled fold, scope-LOCKED, fenced to Addendum L rev7's NEW lock — sixteen LIVE legs, leg (h) NOT WRITTEN, one green head) — **I re-derived every lock at my seat before binding anything, and I did not trust the resume relay: the L blob at `8c7f9281` hashes `10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4` and the live file hashes `b3599511d8802adc12b2f4dda131374f03d33bc33dfad78e22e826b435fde1e1` — both EQUAL to the release. I then took the NORMATIVE DIFF rev5-locked → rev7-locked rather than re-reading a paraphrase, because I had already read rev5's 265 lines in full: FIVE hunks, all accounted for — the H1/Status revision block, L-R1's "(and, from Step 6, the L-R5 listing surface — deferred, rev6)", L-R5's deferral block plus its new NORMATIVE closing check, FX-L-1's header + vacuity note, and leg (q) replacing leg (h)'s position with (h) retained-and-deferred. No other normative byte moved. I also RE-DERIVED the three loci rev7 corrected, at `9729191`, because a locus I carry into a plan becomes a locus at a keyboard: `required_agent_members` is CONSTRUCTED at `open.cpp:176-185`, the ALLOW check is `:280` (refusal `:281`), the PRESENCE enforcement is `:311-315` (refusal `:313`, `IntegrityFailurePreApply`/`missing-agent-member`). rev7's parenthetical is correct at all three.** **THE PLAN BINDS FIFTEEN NORMATIVE ITEMS (S-1 … S-15), each derived from the LOCKED bytes with the derivation written down so my Implementer can refuse any one of them at the bytes rather than take my word. Three of them are placements the document does not spell out and I am RULING, with the derivation exposed: S-1 the footprint is a NEW opaque field on `AgentSessionEntry` and NEVER `entry.children` (because `sessions.cpp:352-353` computes `entry_schema_skipped_count += 1U + entry.children.size()` — `entry.children` IS A5's count source, and the VP fence names that exact locus) and NEVER `entry.artifacts` (because `required_agent_members` at `:176-185` unions `entry.artifacts` into the SHARED set, which leg (q)'s named mutant is); S-7 the allow-only placement is a SECOND set consulted at `:280` alone while `required_agents` and `:311-315` stay byte-untouched; S-8 a stub cap refusal names the CAP and carries NO entry id, because `entry_cap_error()` embeds the primary session id and the stub gate returns at `manifest.cpp:350`, fifty-six lines before `original_session_ids` is parsed at `:406` — reaching for it would be the identity read L-R1 forbids.** **AND ONE ANTI-HALF-FIX GUARD IS THE POINT OF THE WHOLE ARM, so I state it as a scope item rather than a hope: `tests/test_cli.cpp:141` suppresses payload members for every over-ceiling entry, and THAT SUPPRESSION IS WHAT HID THE ORIGINAL BLOCKER THROUGH FIFTEEN GREEN LEGS. It must be lifted (S-12) or legs (a)/(b) cannot exist; and it must be lifted WITHOUT changing any existing leg's oracle, which is an acceptance criterion the review checks, not a claim I make.** **THE LISTING SURFACE IS OUT OF SCOPE AND I BIND ITS ABSENCE POSITIVELY (S-11): leg (h) is NOT WRITTEN; the listing halves of legs (m)/(o) and of L-R2(0) are VACUOUS at this head per rev7's own vacuity note and MUST NOT BE ASSERTED — an assertion that cannot fail is the defect this arm just paid a cycle to remove, and re-introducing it inside the repair would be the same shape wearing the fix. The no-annotation TEXT FENCE stays UNCONDITIONAL (veto L-V5): no stub-class annotation text anywhere, and STOP 2 still routes to m-3 if one is ever wanted.** Sequencing is the ruled in-fold order: transcribe m-3's byte-exact line, implement, observe both platforms on the line-carrying tree, transcribe the four counts, commit ONCE. No token is issued by this relay — the implementation token follows my Implementer's PLAN-REVIEW and parents to it. `9729191` stands until the successor supersedes it; the land order gates every merge; branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-rev7
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-resumed-new-lock
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-SLICE-E-B-L5-RULED-COUPLED-FOLD-RESUMED-NEW-L-LOCK-LEG-Q-LISTING-DEFERRED-20260817-190217.md
RELATED_CONTEXT: SITREP-PLANNER-SLICE-E-COUPLED-FOLD-HELD-LR5-LEG-H-UNIMPLEMENTABLE-R62-20260817-063302.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — this is the pair-Planner PLAN under the standing dispatch, the five locks, the M-a four-line grant plus its one ruled transcription act, and W-2. No token here; my Implementer's PLAN-REVIEW is the next gate and the implementation token parents to it. No merge, push, publication, or release authority moves. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: PLAN — coupled fold scope-locked to L rev7 (10c8e8e6): fifteen normative binds S-1..S-15, sixteen LIVE legs mapped to homes and mutants, leg (h) not written and the vacuous listing halves not asserted, the test_cli.cpp:141 payload suppression lifted as a scope item, m-3's line transcribed, four counts observed; PLAN-REVIEW requested

## 1. Locks bound — re-derived at my seat, not carried

```text
L   m1-addendum-L-10c8e8e6-lock-20260817   10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
    @ pdc 8c7f9281 · live post-stamp b3599511d8802adc12b2f4dda131374f03d33bc33dfad78e22e826b435fde1e1
    live-vs-locked delta: ONE Status-block seal hunk. rev5's 61d3e443 is SUPERSEDED (lineage only).
K   m1-addendum-K-5da667fa-lock-20260816 @ 0e455ef5
A5  m3-addendum-5-b8686c75-lock-20260816 @ c57067fe
A4  m3-addendum-4-9049de44-lock-20260816 @ 40bd88a6
J   m1-addendum-J-94b6440c-lock-20260812 @ e30f845    (consumed base)
A3  m3-addendum-3-eeb4dd01-lock-20260814 @ a016f953    (consumer contract)
```

**The rev5 → rev7 normative delta, enumerated so nothing rides on a summary:** H1/Status block ·
L-R1's "(and, from Step 6, the L-R5 listing surface — deferred, rev6)" · L-R5's deferral block and its new
normative closing check · FX-L-1's header + vacuity note · leg (q) added, leg (h) retained-and-deferred ·
Bounds' closing sentence. **Nothing else moved.**

**Loci re-derived by me at `9729191`** (rev7 corrected rev6 here; I checked rather than accepted):

```text
open.cpp:176-185   required_agent_members(...)  — CONSTRUCTION of the shared set
open.cpp:280       if (agent && !required_agents.contains(member.meta.path))   — the ALLOW check
open.cpp:281       return UnmanifestedMember{member.meta.path}
open.cpp:311-315   for (required : required_agents) if (!seen.contains(required))  — PRESENCE enforcement
open.cpp:313       return IntegrityFailurePreApply{required, "missing-agent-member"}
```

## 2. Scope — locked paths

```text
IN   src/core/manifest/manifest.hpp     the footprint field (S-1)
IN   src/core/manifest/manifest.cpp     the stub scan, key-name license, caps, grammar, one-set join (S-2..S-6, S-8)
IN   src/core/open/open.cpp             the allow-only placement (S-7)
IN   tests/test_manifest.cpp            parse-level legs (S-16 map)
IN   tests/test_cli.cpp                 image-level legs + the :141 suppression lift (S-12)
IN   tests/test_sessions.cpp            M-b's two-agent witness (S-13)
IN   tests/fixtures/slice-e/**          new fixture data required by the legs
IN   .github/workflows/s2-harness.yml   EXACTLY :73-76 (one transcribed line, S-14) and
                                        EXACTLY :68 / :71 / :268 / :271 (four observed counts, S-15)
OUT  everything else in .github         HARD-OUT
OUT  src/cli/main.cpp, list/info        Step 6 / R-6.2 — no verb is built here
OUT  the writer (serialize), pack.cpp   no producer change; no format_version bump; no schema field
OUT  src/core/open/sessions.cpp, render.cpp, report/envelope.cpp   COUNT NON-FEED: zero bytes (S-9)
```

## 3. The fifteen normative binds

### S-1 — footprint storage: a NEW opaque field, never `children`, never `artifacts`

Add to `manifest::AgentSessionEntry` (`manifest.hpp:50-65`) a flat opaque path list — a
`std::vector<std::string>`, name the Implementer's choice, populated ONLY for
`entry_schema > kEntrySchemaParseCeiling`. For a stub, `entry.children` and `entry.artifacts` stay EMPTY.

```text
NOT entry.children   sessions.cpp:352-353 computes  entry_schema_skipped_count += 1U + entry.children.size()
                     -> entry.children IS A5's count source; the VP fence names sessions.cpp:352-359 verbatim
                     ("the floor's storage mechanism must not let A5's count source observe children").
                     Storing there breaks L-R4 and trips veto 2.
NOT entry.artifacts  open.cpp:176-185 unions entry.artifacts into the SHARED required set -> the footprint
                     would enter the :311-315 presence requirement. That IS leg (q)'s named mutant.
```

Two independent derivations reach the same field. **L-R4 and veto 2 then hold BY CONSTRUCTION rather than
by care** — nothing downstream can observe a stub's child count because nothing downstream is given it.

### S-2 — the scan, at the stub gate

`manifest.cpp:350` currently returns bare. Replace with: scan → populate the footprint → return. The scan reads
**exactly three accessor positions** — top-level `artifacts`, top-level `children`, and each child object's
`artifacts` — as OPAQUE strings. **No VALUE of any other child field is accessed** (L-R1, veto 1). The graph is
unread: no `original_id`, no `parent_id`, no identity, no edges, no depth.

### S-3 — the key-name license, its own narrow helper

Duplicate refusal at all three positions, at that object's own scope, **BEFORE the value is selected**
(L-R2(0)). Enumeration sees key NAMES only, counts occurrences of the three footprint-bearing keys, and applies
no other semantics.

**`validate_child_keys_unique` (`manifest.cpp:213-235`) MUST NOT be reused** — it also refuses duplicate
`original_id` and `parent_id`, which on the stub path is graph-key semantics (veto 1) and would turn legs
(m)/(n) RED. The stub scan gets the narrower iterator the license describes. A duplicate NON-footprint field
stays under existing first-wins behavior; `R-4.22` is not widened.

Refusal: `ErrKind::ParseError` with a detail naming the duplicate class, **distinguishable from
`children-duplicate-key`** so legs (i)/(j)/(k) assert the stub-scan rule and not J's.

### S-4 — caps, graph-free, in-loop

```text
children[] elements iterated   <= 1024   SHORT-CIRCUIT DURING the loop — refuse the 1025th BEFORE reading it,
                                         the shape already at manifest.cpp:246-249
artifacts per node             <= 256
total artifacts across entry   <= 4096
depth                          N/A — it needs edges, and the graph is unread
```

Breach = typed WHOLE-ENTRY refusal. **Truncation anywhere, in any arm, for any cap = veto 4.** A post-loop node
cap check = veto 3.

### S-5 — grammar

Every footprint path through `validate_artifacts(entry.agent, …)` (`manifest.cpp:190-198`) — failure is the
same typed `artifact-prefix` refusal a parsed entry gets (L-R2(1)).

### S-6 — ONE manifest-wide occurrence set

`parse_agent_sessions` already owns the single set: `seen_artifacts` at `manifest.cpp:456`, fed by the
entry-level loop `:471-476` and the child loop `:477-483`, refusing any repeat as `artifact-uniqueness`. **Every
footprint occurrence enters THAT set** — a third insertion in the same family, **no scoped twin** (L-R2(2), the
parity-preserving form). Any second occurrence refuses regardless of whether the first lives in the same stub,
another stub, or a parsed entry — which is what makes legs (d)/(l)/(p) three cells of one rule.

### S-7 — allow-only placement (leg (q) binds the keyboard)

```text
UNCHANGED   required_agent_members (open.cpp:176-185) and the :311-315 presence loop — byte-untouched
NEW         a SECOND, footprint-allow set, consulted at :280 ONLY
EFFECT      admission EXTENDS at :280; the presence REQUIREMENT does not extend
MUTANT      footprint paths unioned into the shared required set -> RED at leg (q) with exactly
            IntegrityFailurePreApply / "missing-agent-member"
```

Ground: L-R1's *"for the archive-integrity allow-set … and for NOTHING else"*, and sealed §2.4's
*"never image refusal"* for over-range entries — the posture both owners killed arm (b) for.

### S-8 — a stub cap refusal carries no identity

`entry_cap_error()` (`manifest.cpp:33-37`) embeds `entry=<primary_id>`. The stub gate returns at `:350`;
`original_session_ids` is not parsed until `:406`. **The stub cap refusal names the CAP and carries no entry
id.** Leg (e) requires the error to name the NODE CAP; it does not require an identity, and reaching for one
would be the read L-R1 forbids.

### S-9 — COUNT NON-FEED: zero bytes in the count machinery

`sessions.cpp`, `render.cpp`, `report/envelope.cpp` take **no edit**. `children_known` stays 0 for stubs; the
at-least floor stands; `entry_schema_skipped_count` and `entry_schema_unparsed_count` are computed exactly as
before; no notice or envelope value changes because the scan ran. Leg (f) is the control that proves it.
**Any count change sourced from the footprint is STOP 3 to m-3, never a keyboard call.**

### S-10 — the text fence, unconditional

**No stub-class annotation text anywhere in the implementation** — not in a message, a notice, a JSON key, or a
comment that renders. Veto L-V5 is not deferred; it is satisfied by ABSENCE today and re-arms when Step 6 builds
the verbs. If an annotation is ever wanted, that is STOP 2 to m-3 for the cut.

### S-11 — the listing surface is out of scope, and its absence is bound POSITIVELY

```text
leg (h)                       NOT WRITTEN. Deferred to R-6.2 / Step 6. The letter stays; nothing renumbers.
legs (m)/(o) listing halves   NOT ASSERTED — rev7's vacuity note: those clauses read VACUOUSLY TRUE at this
                              head and BIND at Step 6. Write ONLY the load-bearing oracles: refusal kind,
                              access behavior, allow-set effect.
L-R2(0)'s "or the listing"    same treatment.
```

**This is a hard bar, not a preference.** An assertion that cannot fail is exactly the defect that cost this arm
a cycle; writing one inside the repair would reproduce the shape wearing the fix. If a leg cannot be written
without a vacuous clause, that is a finding for me, not a green tick.

### S-12 — lift the fixture suppression that hid the blocker

`tests/test_cli.cpp:141` — `if (entry_schemas[index] <= biv::manifest::kEntrySchemaParseCeiling)` — suppresses
payload members for every over-ceiling entry, so every over-ceiling fixture in the suite carries ZERO members:
**the exact shape that dodges the member gate, which is why fifteen legs were green over an unreachable
contract.** Legs (a)/(b)/(q) cannot exist while it stands.

```text
BIND    over-ceiling entries MUST be able to carry members in fixtures
BIND    no EXISTING leg's oracle may change meaning as a side effect — parameterize rather than flip, or
        flip and demonstrate at the bytes that each affected leg still asserts what it asserted
CHECK   tests/test_manifest.cpp:589-597 (far-future schema, entry_schema = ceiling + 97) becomes a stub WITH a
        footprint under S-2 — verify it still parses and still checks what it checked
```

### S-13 — M-b, the two-agent witness

TWO agents, each carrying a stubbed entry ⇒ each agent's `entry_schema_unparsed_count` independently correct.
**The `agents.front()` mutant dies here.** Rides this fold; not a separate commit.

### S-14 — the transcription act

m-3's identity line into `.github/workflows/s2-harness.yml:73-76`, **byte-exact**.

```text
SOURCE   pdc master/relays/s4-build-standup/DESIGN-PLANNER-M3-EXPECTED-SKIPS-NAME-ADMITTED-
         SELF-ENFORCING-AT-FLIP-20260816-224751.md — the §"Into expected_skips (:73-76), byte-exact" block
PIN      that source line's sha256 is 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481
SHAPE    14-space indent · double quotes · trailing comma — matches both existing entries at :74-75
JOIN     the quoted name byte-matches the live TEST_CASE at tests/test_sessions.cpp:1745
RULE     RE-READ the source at transcription time. Do not transcribe from this relay, and do not
         transcribe from the pin — the pin is how you CHECK what you transcribed, not what you type.
         ANY deviation is an m-3 VETO.
```

### S-15 — the four counts, observed and never derived

```text
:68   macOS  "successes"    :71   macOS  "skips"    :268  Linux "successes"    :271  Linux "skips"
SOURCE     each number transcribed from THAT TARGET's own catch.xml, from a run of the tree carrying S-1..S-14
macOS      local `biv_tests -r xml`
Linux      the same suite in the chartered ubuntu-24.04 `--platform linux/amd64` Docker reproducing s2-harness.yml
CITE       both run identifiers in the commit message, so "observed, not derived" is checkable later
NEVER      no arithmetic · no cross-target borrowing · :69/:269 failures and :70/:270 expectedFailures are
           OBSERVE-AND-ROUTE (an observed nonzero is a product FINDING routed UP, never a gate edit) ·
           no expected_skips byte beyond S-14's one line
```

## 4. Leg map — SIXTEEN LIVE legs, each to a home and a killing mutant

```text
leg  oracle (abbreviated; the LOCKED bytes govern)                          home
(a)  V1 entry-level member, schema-3: opens, member admitted, entry skips,  test_cli.cpp (image)
     at-least disclosure, exit 0   [RED at 9729191: exit 3 UnmanifestedMember, EXECUTED]
(b)  V2 child-level member only: same green   [the arm-(a) incompleteness   test_cli.cpp (image)
     witness — stays RED under an entry-artifacts-only widening]
(c)  footprint path outside agents/<agent>/… ⇒ typed refusal                test_manifest.cpp
(d)  stub footprint path == a PARSED entry's member ⇒ typed refusal         test_manifest.cpp
(e)  1025 children, the 1025th carrying a path the validator would refuse   test_manifest.cpp
     ⇒ error names the NODE CAP (proves the short-circuit fired first)
(f)  knowability control: children_known 0, at-least prefix present,        test_cli.cpp / test_sessions.cpp
     unparsed count unchanged in meaning, no envelope delta beyond the
     allow-set — the scan ran and NOTHING counted
(g)  M-b: two agents, each stubbed ⇒ per-agent unparsed counts independent  test_sessions.cpp
(i)  duplicate top-level `artifacts` ⇒ refusal AT PARSE naming the class,   test_manifest.cpp
     no allow-set built, no listing produced
(j)  duplicate top-level `children` ⇒ same shape                            test_manifest.cpp
(k)  duplicate `artifacts` within ONE child ⇒ same, through the STUB path   test_manifest.cpp
(l)  same path at ENTRY level AND under a CHILD of the same stub ⇒ refusal  test_manifest.cpp
     via the one set
(m)  POSITIVE, hostile-planted: valid artifacts + DUPLICATE original_id,    test_manifest.cpp
     both values hostile ⇒ GREEN, no refusal.  MUTANT: required_string /
     session-id validation on original_id ⇒ RED
(n)  POSITIVE, independent: duplicate parent_id, first null, second bad     test_manifest.cpp
     ⇒ GREEN.  MUTANT: the present-nonnull/grammar path on parent_id ⇒ RED
(o)  POSITIVE, sentinel: duplicate `original_path` (the THIRD post-gate     test_manifest.cpp
     required_string field, manifest.cpp:356) ⇒ GREEN, neither value
     accessed.  MUTANT: required_string(object,"original_path") on the
     stub path ⇒ RED
(p)  TWO STUBS declaring the SAME footprint path ⇒ refusal via the one set  test_manifest.cpp
(q)  a stub declares a footprint path with NO archive member ⇒ the archive  test_cli.cpp (image)
     still OPENS: entry skips per K/A5, the allow-set entry is INERT,
     exit 0, NO refusal.  MUTANT: the naive one-set insert ⇒ RED with
     exactly IntegrityFailurePreApply / "missing-agent-member"
(h)  DEFERRED — not written. R-6.2 / Step 6.
```

Legs (m)/(n)/(o) are POSITIVE controls whose value is the NAMED MUTANT: each must be planted so that any value
access **fails loudly**. A leg that would pass a read-and-discard over-reader has not been planted hostilely
enough — that failure is what rev4 folded, and it is on us not to reintroduce it.

Note for the record, since two documents use the letter: **FX-L-1's leg (p) is the stub-vs-another-stub alias
leg. m-3's leg (p) is the R-4.29 threshold-parity test whose NAME S-14 transcribes.** Different documents, do
not conflate.

## 5. Sequencing — the ruled in-fold order, ONE commit

```text
1  transcribe m-3's line into :73-76 (re-read the source; check against the pin)
2  implement S-1..S-13 to the LOCKED L bytes
3  run macOS local `biv_tests -r xml` AND the ubuntu-24.04 linux/amd64 Docker suite on THAT tree
4  transcribe the four counts from each target's own catch.xml
5  commit ONCE, citing both run ids
```

The observation tree must already carry the identity line (else macOS reddens on `SKIP-IDENTITY GATE FAILED`)
and must carry S-13 (M-b moves the totals). A precursor commit's numbers would be stale by fold time, which is
why the ruled in-fold sequence is the one I bind.

## 6. Acceptance criteria

```text
A1   all SIXTEEN LIVE legs GREEN; leg (h) absent, not stubbed, not ticked
A2   every NAMED MUTANT demonstrated to KILL its leg — (m)/(n)/(o)/(q) at minimum, each run and reported.
     A mutant that is reasoned about rather than run is not a mutant; state which you executed.
A3   legs (a)/(b) RED at 9729191 and GREEN at the successor, both states reported (they are the falsifier's
     two executed fixtures — the RED is already E2 evidence)
A4   no vacuous assertion anywhere in the new legs (S-11); if one is unavoidable, it is a finding to me
A5   sessions.cpp / render.cpp / report/envelope.cpp: ZERO diff (S-9)
A6   open.cpp:176-185 and :311-315: ZERO diff (S-7)
A7   the transcribed line byte-matches the source; report the sha256 you computed of what you LANDED
A8   the four counts each traceable to a cited run id on that target; failures/expectedFailures untouched
A9   both platforms GREEN in the one head
A10  no existing leg's oracle changed meaning under S-12 — demonstrated, not asserted
```

## 7. Anti-half-fix guards

```text
G1  the scan MUST NOT reuse validate_child_keys_unique — legs (m)/(n) are the detectors
G2  the node cap MUST short-circuit IN the loop — a post-loop check is veto 3 and leg (e) is the detector
G3  no truncation in any arm for any cap — veto 4
G4  the footprint enters the EXISTING seen_artifacts, not a twin — legs (d)/(l)/(p) are three cells of one rule
    and a twin passes some of them
G5  a stub's entry.children stays EMPTY — leg (f) is the detector, and the VP fence names the locus
G6  the allow-only placement is leg (q)'s subject; do not "simplify" it back to one set
G7  if any gap appears that S-1..S-15 does not decide, it is a STOP to me — never a keyboard call (L-R7)
```

## 8. Questions for my Implementer — answer inline in the PLAN-REVIEW

1. **S-12:** parameterize the payload suppression, or lift it outright? Name the callers affected
   (`test_cli.cpp:655`, `:656`, `:789` and any I missed) and how you show A10.
2. **S-3:** what detail string do you propose for the stub-scan duplicate refusal, and how do legs (i)/(j)/(k)
   assert it distinctly from J's `children-duplicate-key`?
3. **S-7:** where do you build the footprint-allow set — extend the `required_agent_members` call site with a
   second return value, or a separate function? Either is fine; say which and why.
4. **Leg (e):** the 1025-children fixture is large. Generated in-test or a committed fixture?
5. Anything in S-1..S-15 you can refute at the bytes. **I would rather be corrected here than at m-1's veto.**

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, push, PR, Actions, merge, publication, deployment, or release act at this seat — plan-only. Read-only this pass: the L blob at pdc `8c7f9281` extracted and sha256'd, the live L file sha256'd, and the NORMATIVE DIFF rev5-locked → rev7-locked read in full (five hunks, enumerated in §1); `src/core/open/open.cpp:174-186/278-284/308-318`, `src/core/manifest/manifest.cpp:20-37/185-300/330-495`, `src/core/manifest/manifest.hpp:1-88`, `src/core/open/sessions.cpp:352-353`, `tests/test_cli.cpp:80-165/1018-1026`, `tests/test_manifest.cpp:565-615`, `.github/workflows/s2-harness.yml:64-92/264-280` at `9729191`; m-3's `224751` identity-line block. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No implementation token issued — it follows the PLAN-REVIEW and parents to it.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read at 191450 immediately before filing, per D-5.10 instance 4 — the 191153 draft aged out of the freshness window during authoring and was re-stamped; no other byte changed); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds disclosed by line at my last filing and unchanged: cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; time inversions at 222 and 393. None mine; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging:

```text
M  .relays/s4/INDEX.md
A  .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-L-REV7-SIXTEEN-LIVE-LEGS-SCOPE-LOCKED-20260817-191450.md
```

The implementation worktree `s4-floor-slice-e-stage1a` at `9729191` reports EMPTY `git status --short`. The shared main checkout carries sibling-authored untracked state, excluded and unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-FOLD-L-REV7-SIXTEEN-LIVE-LEGS-SCOPE-LOCKED-20260817-191450.md` → `s4-floor.implementer`
- LOCKS RE-DERIVED AT MY SEAT, not carried: L blob at pdc 8c7f9281 == 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4, live post-stamp == b3599511d8802adc12b2f4dda131374f03d33bc33dfad78e22e826b435fde1e1, live-vs-locked delta ONE Status-block seal hunk; K 5da667fa, A5 b8686c75, A4 9049de44, J 94b6440c, A3 eeb4dd01. I took the NORMATIVE DIFF rev5-locked to rev7-locked rather than re-reading a paraphrase (five hunks, enumerated) and RE-DERIVED rev7's three corrected loci myself: construction :176-185, ALLOW :280 refusal :281, PRESENCE :311-315 refusal :313 — all three correct as rev7 states them
- FIFTEEN NORMATIVE BINDS S-1..S-15 with derivations exposed so the Implementer can refuse any at the bytes. THREE ARE PLACEMENTS I RULE: S-1 the footprint is a NEW opaque field, NEVER entry.children (sessions.cpp:352-353 makes it A5's count source, the VP fence names that locus) and NEVER entry.artifacts (open.cpp:176-185 unions it into the shared set — leg (q)'s named mutant); S-7 the allow-only placement is a SECOND set at :280 alone with required_agents and :311-315 byte-untouched; S-8 a stub cap refusal names the CAP and carries no entry id, since entry_cap_error embeds the primary id and the gate returns at manifest.cpp:350, fifty-six lines before it is parsed at :406
- S-12 IS THE ARM'S OWN LESSON MADE A SCOPE ITEM: tests/test_cli.cpp:141 suppresses payload members for every over-ceiling entry, which is exactly what hid the blocker through fifteen green legs; it must be lifted or legs (a)/(b)/(q) cannot exist, and lifted WITHOUT changing any existing leg's oracle (acceptance criterion A10, demonstrated not asserted). Also flagged: test_manifest.cpp:589-597's far-future-schema entry becomes a stub WITH a footprint under S-2 and must be re-verified
- S-11 BINDS THE ABSENCE POSITIVELY: leg (h) NOT WRITTEN; the listing halves of legs (m)/(o) and of L-R2(0) are VACUOUS at this head per rev7's own vacuity note and MUST NOT BE ASSERTED — writing an assertion that cannot fail inside the repair for exactly that defect is barred; the no-annotation TEXT FENCE stays UNCONDITIONAL (veto L-V5) and STOP 2 still routes to m-3
- SIXTEEN LIVE LEGS MAPPED to homes and killing mutants ((a)-(g) + (i)-(q)); NAMED MUTANTS (m)/(n)/(o)/(q) must be RUN not reasoned about (A2); legs (a)/(b) report both the executed RED at 9729191 and the GREEN at the successor. Recorded so two documents' letters are not conflated: FX-L-1's leg (p) is the stub-vs-another-stub alias leg, m-3's leg (p) is the R-4.29 test whose NAME S-14 transcribes
- SEQUENCE (ruled in-fold, ONE commit): transcribe m-3's line re-read from 224751 at transcription time (pin 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 is how you CHECK, not what you type) -> implement to the LOCKED bytes -> observe macOS local and ubuntu-24.04 linux/amd64 Docker on that tree -> transcribe the four counts from each target's own catch.xml -> commit ONCE citing both run ids; failures/expectedFailures OBSERVE-AND-ROUTE, every other .github byte HARD-OUT
- TEN ACCEPTANCE CRITERIA and SEVEN ANTI-HALF-FIX GUARDS stated, plus five questions for the PLAN-REVIEW. Any gap S-1..S-15 does not decide is a STOP to me, never a keyboard call (L-R7). NO IMPLEMENTATION TOKEN in this relay — it follows the PLAN-REVIEW and parents to it; 9729191 stands until the successor supersedes it; land order gates every merge; branch LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
