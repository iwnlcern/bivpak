## IMPL — coupled-fold DISPATCH on the approved L rev7 plan: four delegation preconditions verified at the bytes, the review's four answers adopted as binds, ONE editorial correction carried and ONE REFUTED

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-coupled-fold-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-plan-review-rev7
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-FOLD-L-REV7-APPROVE-20260817-192103.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-B-L5-RULED-COUPLED-FOLD-RESUMED-NEW-L-LOCK-LEG-Q-LISTING-DEFERRED-20260817-190217.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the successor returns for m-1's byte review and veto AND m-3's COMBINED successor re-review, both of which gate the hand-up and neither of which this token discharges. Merge, push, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: IMPL — coupled fold dispatched on the 192103 approve; eight IN paths with per-row evidence and all-in; the review's S-12/S-3/S-7/leg-(e) answers adopted as binds; the S-16 correction carried and the leg-(a) duplication claim REFUTED at the bytes; one green head, both platforms

DISPATCH IMPL

## 1. The four delegation preconditions — verified, not assumed

```text
1 DELEGATION GRANTED   190217 §3: "NOW (pair) issue your fresh coupled-fold DISPATCH-IMPL through your
                       local gates (PARENT = your plan-review)". Explicit, to this pair, for this act.
2 PLAN-REVIEW APPROVE  192103, PLAN_REVIEW_VERDICT: approve, FROM s4-floor.implementer, TO s4-floor.planner,
                       PARENT_DISPATCH_ID s4-floor-slice-e-coupled-fold-plan-rev7 — my plan.
                       It reviewed the RIGHT bytes: it declares the plan's SHA-256 as
                       1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5, and I re-derived
                       that hash from BOTH the committed blob at 1b1b855 and the worktree file — EQUAL,
                       and equal to each other, so the review is on the filed bytes with no drift.
3 SCOPE_DIFF           all-in, eight rows, per-row evidence — §5 below.
4 NO HARD TRIGGER      no new operator gate, no owner-surface act beyond the two already-granted ones
                       (M-a's four count lines; the ONE ruled transcription of m-3's line).
```

**The token is LIVE and covers the coupled fold only.**

## 2. Lineage, hop by hop

```text
this token  s4-floor-slice-e-coupled-fold-impl
  PARENT -> s4-floor-slice-e-coupled-fold-plan-review-rev7
            PHASE PLAN-REVIEW · FROM s4-floor.implementer · PLAN_REVIEW_VERDICT: approve
    PARENT -> s4-floor-slice-e-coupled-fold-plan-rev7
              PHASE PLAN · FROM s4-floor.planner · TO s4-floor.implementer
      PARENT -> s4-floor-slice-e-coupled-fold-resumed-new-lock  (the delegating orchestrator PLAN)
```

## 3. The review's four answers — ADOPTED as binds

I checked each against the bytes before adopting it; none is taken on the review's word.

### S-12a — parameterize, off by default

One helper control on `make_slice_e_consumer_image` (`test_cli.cpp:83-85`), default OFF; the `:141` condition
admits payload when the entry is within the parse ceiling **OR** that control is true. **Adopted, and the
reasoning is better than a global lift:** the default preserves the existing branch for every current caller,
so A10 holds by CONSTRUCTION rather than by inspection. Caller sweep confirmed at my seat — `:655`, `:656`,
`:789`, and no fourth. Legs (a)/(b) opt IN; **leg (q) stays OFF, which is exactly right** — the default
suppresses both the payload member and its `checksums.entries` row, so a declared footprint path is absent
from tar and checksums alike, and nothing along `open.cpp:304-309` or `:311-315` may refuse it.

### S-3a — three exact details, equality-asserted

```text
stub-footprint-entry-artifacts-duplicate-key
stub-footprint-entry-children-duplicate-key
stub-footprint-child-artifacts-duplicate-key
```

Legs (i)/(j)/(k) assert **equality**, not substring containment. All three are distinct from J's
`children-duplicate-key` (`manifest.cpp:228`), so the child-arm leg cannot pass on the parsed-graph helper —
which is the whole point of leg (k). Duplicate NON-footprint keys stay first-wins; `R-4.22` is not widened.

### S-7a — a separate function and a separate set

`allowed_stub_agent_members(const manifest::Manifest&)` file-local beside `required_agent_members`
(`open.cpp:176-185`), returning only the opaque footprint paths; its set built beside `required_agents` in
`read_archive_plan`; **only** the `:280` admission predicate widened to accept membership in either.
`required_agent_members` and the `:311-315` loop take ZERO diff. **Adopted with the review's ground endorsed:**
a paired return would couple presence policy and admission policy at one function boundary and make leg (q)'s
forbidden union easy to reintroduce during maintenance. Two functions, two policies, visible in the diff.

### S-Ea — leg (e) generated in-test

1,025 children generated in `tests/test_manifest.cpp`; positions 1–1,024 minimal and valid; the invalid-path
sentinel **only** in child 1,025. The expected detail is the **identity-free node-cap detail** (S-8), NOT
`artifact-prefix` — and that is the entire discriminator: `artifact-prefix` would prove the 1,025th element was
READ, i.e. that the short-circuit did not fire, i.e. veto 3.

## 4. Editorial — one correction CARRIED, one REFUTED at the bytes

```text
CARRIED   §2's scope row reads "tests/test_manifest.cpp   parse-level legs (S-16 map)". There is no S-16;
          it means the §4 LEG MAP. Confirmed: exactly one occurrence of "S-16" in the plan, at line 61.
          No keyboard act may depend on resolving a nonexistent bind.

REFUTED   The review's second editorial finding — leg (a)'s "at-least disclosure, exit 0" line "appears
          twice" — is NOT TRUE of the filed bytes, and I checked rather than carried it:
            grep -n "at-least"  -> THREE hits, all different: :163 S-9's "at-least floor"
                                   :240 leg (a)'s "at-least disclosure, exit 0"
                                   :247 leg (f)'s "at-least prefix present"
            grep -n "exit 0"    -> TWO hits: :240 leg (a), :269 leg (q)
            leg (a) occupies :239-240 as ONE two-line entry with ONE oracle.
          There is no duplication, no seventeenth leg, and nothing to correct. I am not recording a false
          claim about my own plan's bytes into a live token — a correction is a measurement like any other.
          The approve stands; this finding simply does not land.
```

## 5. Scope — eight rows

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/open/open.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_sessions.cpp -> in
- tests/fixtures/slice-e/** -> in
- .github/workflows/s2-harness.yml -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `src/core/manifest/manifest.hpp` — S-1: the new flat opaque footprint field on `AgentSessionEntry` (`:50-65`), which today has no safe carrier: `children` is A5's count source and `artifacts` feeds the shared required set.
- `src/core/manifest/manifest.cpp` — S-2 the scan at the stub gate (`:350`); S-3a the narrow key-name helper, distinct from `validate_child_keys_unique` (`:213-235`); S-4 the graph-free caps with the in-loop short-circuit shaped like `:246-249`; S-5 grammar through `validate_artifacts` (`:190-198`); S-6 the join into the EXISTING `seen_artifacts` (`:456`, loops `:471-483`); S-8 the identity-free cap detail.
- `src/core/open/open.cpp` — S-7a ONLY: the new file-local `allowed_stub_agent_members`, its set built beside `required_agents`, and the `:280` predicate widened. `:176-185` and `:311-315` are ZERO-DIFF and the hand-up shows it.
- `tests/test_manifest.cpp` — parse-level legs (c), (d), (e), (i), (j), (k), (l), (m), (n), (o), (p) per the plan's §4 leg map; plus re-verifying `:589-597`, whose far-future entry becomes a stub WITH a footprint under S-2.
- `tests/test_cli.cpp` — S-12a's off-by-default control at `:83-85`/`:141`; image-level legs (a), (b), (q) and the (f) half that needs a whole-run invocation; the three existing callers `:655`, `:656`, `:789` keep today's shape by omitting the argument.
- `tests/test_sessions.cpp` — S-13 / leg (g): M-b's two-agent `entry_schema_unparsed_count` witness, the `agents.front()` mutant's killer; plus the (f) knowability half.
- `tests/fixtures/slice-e/**` — permissive: the leg populations may need new fixture data. If every leg is satisfied by in-test construction, this row goes unused; an unused IN row is not a licence to widen elsewhere.
- `.github/workflows/s2-harness.yml` — S-14 the ONE ruled transcription into `:73-76`, and S-15 the four observed counts at `:68`, `:71`, `:268`, `:271`. NOTHING ELSE in this file, and nothing else in `.github` at all.

**OUT — a discovered need is a STOP to me, never a licence:** `src/core/open/sessions.cpp`, `src/core/open/render.cpp`, `src/core/report/envelope.cpp` (S-9, COUNT NON-FEED, zero diff); `src/cli/main.cpp` and the `list`/`info` verbs (R-6.2 / Step 6 — no verb is built here); `src/core/pack/**` and `serialize` (no writer change, no schema field, no `format_version` bump); every other byte of `.github/**`; sealed design bytes; the harness.

## 6. Zero-diff files and within-file fences — function-scoped diffs required at hand-up

```text
sessions.cpp · render.cpp · envelope.cpp    ZERO DIFF (S-9). Leg (f) is the behavioural control.
open.cpp:176-185 · open.cpp:311-315         ZERO DIFF (S-7a). Leg (q) is the behavioural control.
manifest.cpp                                the stub path only; the parsed-entry path unchanged, and
                                            validate_child_keys_unique NOT reused (legs (m)/(n) detect it)
s2-harness.yml                              :73-76 one transcribed line · :68/:71/:268/:271 four observed
                                            numbers · :69/:269/:70/:270 OBSERVE-AND-ROUTE, never edited
```

## 7. Sequencing — the ruled in-fold order, ONE commit

```text
1  transcribe m-3's identity line into :73-76 — RE-READ the source at 224751 at transcription time
   (the pin 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 is how you CHECK what you
   landed, never what you type). Any deviation is an m-3 VETO.
2  implement S-1..S-13 to the LOCKED L bytes (10c8e8e6… @ 8c7f9281), not to this relay's paraphrase
3  run macOS local `biv_tests -r xml`, then the chartered ubuntu-24.04 `--platform linux/amd64` Docker
   suite, BOTH on the tree carrying steps 1-2
4  transcribe the four counts from each target's OWN catch.xml — no arithmetic, no cross-target borrowing
5  commit ONCE, citing both run identifiers
```

RED-first worktree states may exist during implementation; **no incoherent state may be committed.**

## 8. Evidence and the standing bars

E2. **RED-first with receipts.** Every NAMED MUTANT — (m), (n), (o), (q) — **executed** against the fixture
that kills it, observed RED, reverted, then GREEN. Report which you ran. **A compile failure earns no
behavioural-RED credit.** Legs (a)/(b) carry the already-executed RED at `9729191` and must report GREEN at the
successor. **No vacuous assertion anywhere in the new legs (S-11)** — leg (h) absent, not stubbed, not ticked;
the listing halves of (m)/(o) and of L-R2(0) NOT asserted. **No stub-class annotation text anywhere** (veto
L-V5, unconditional).

**Actions NOT invoked.** Branch stays **LOCAL and UNPUBLISHED** — no push, no PR, no merge, no seal, no
publication. **The land order binds.** Live `~/.claude` / `~/.codex` are never read-for-mutation or written —
fixture trees or explicit disposable copies only. **No credential collection.**

## 9. The fences and vetoes carried

**L's vetoes:** (1) graph reading in the footprint scan — any non-`artifacts` child field's VALUE accessed, or
semantics beyond L-R2(0)'s name-count licence · (2) the footprint feeding any count, notice, or envelope value
· (3) a post-loop node-cap check instead of the in-loop short-circuit · (4) truncation anywhere, in any arm,
for any cap · (5) a stub-class annotation not cut by m-3 · (6) any silent filling of the three STOPs.
**L's STOPs:** (1) any read beyond `{agent, entry_schema, footprint}`, or name enumeration beyond the licence →
m-1 · (2) any listing annotation for the stub class → m-3 · (3) any count-machinery touch sourced from the
footprint → m-3. **All three route through me, then UP through the orchestrator — never sideways to an m-x
seat.** **K's one-identifier rule, A5's biconditional and at-least floor, A3.1's notice, and m-3's V1–V11
continue to bind.**

**The token ends at a STOP covering the coupled fold only.** Return for my byte verification, then m-1's byte
veto and m-3's combined successor re-review — both gate the hand-up. **Any gap S-1…S-15 plus the four adopted
binds do not decide is a STOP to me**, never a keyboard call (L-R7).

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, push, PR, Actions, merge, publication, deployment, or release act at this seat — this relay delegates. Read-only this pass: the `192103` review read in full and its declared plan SHA-256 re-derived by me from BOTH the committed blob at `1b1b855` and the worktree file (`1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5`, EQUAL to each other and to the review's claim); the review's two editorial findings measured against the plan's bytes — the `S-16` one CONFIRMED at line 61, the leg-(a) duplication one REFUTED (`grep -n "at-least"` → :163/:240/:247, three DIFFERENT phrases; `grep -n "exit 0"` → :240 leg (a) and :269 leg (q); leg (a) is one entry at :239-240); the `make_slice_e_consumer_image` caller sweep re-run (`:655`, `:656`, `:789`, no fourth). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before filing (D-5.10), per-file WITH freshness and the exit status checked un-piped; **`--relay-root` run against this token before filing**, because the exact-file arm false-greens a wrong lineage and has done so twice in this build. `.relays/s4/INDEX.md` tail re-read before appending; file → lint → append → add → commit runs as one chain. Standing INDEX reds, disclosed by line and unchanged: cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; time inversions at 222 and 393. None mine.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` reports EMPTY `git status --short`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-DISPATCH-IMPL-TOKEN-20260817-193748.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-DISPATCH-IMPL-TOKEN-20260817-193748.md` → `s4-floor.implementer` — **LIVE bare implementation token**, parented to the `192103` plan-review approve
- FOUR DELEGATION PRECONDITIONS VERIFIED, not assumed: the orchestrator's explicit delegation at 190217 §3; the 192103 approve addressed to this seat and parented to my plan; SCOPE_DIFF all-in over eight rows with per-row evidence; no hard trigger. The review was on the RIGHT bytes — its declared plan SHA-256 1b9c6930e35ded4bffd5e34002d3101786190fc7b1dde104a2265c163aa11ec5 re-derived by me from both the committed blob at 1b1b855 and the worktree file, EQUAL, so no drift
- FOUR ANSWERS ADOPTED AS BINDS after checking each at the bytes: S-12a an off-by-default payload control on make_slice_e_consumer_image so A10 holds BY CONSTRUCTION for the three existing callers :655 :656 :789 (no fourth), with legs (a)/(b) opting IN and leg (q) correctly staying OFF since the default suppresses the checksums row as well as the member; S-3a three exact stub-footprint duplicate details asserted by EQUALITY and all distinct from J's children-duplicate-key at manifest.cpp:228; S-7a a separate file-local allowed_stub_agent_members and a separate set widening ONLY the :280 predicate, with :176-185 and :311-315 zero-diff, because a paired return would couple presence and admission policy at one boundary; S-Ea leg (e) generated in-test with the sentinel only in child 1,025 and the expected detail the IDENTITY-FREE node-cap detail, never artifact-prefix, which is the entire short-circuit discriminator
- EDITORIAL: the S-16 correction is CARRIED (exactly one occurrence, plan line 61; it means the §4 leg map). The leg-(a) duplication finding is REFUTED at the bytes and NOT carried — "at-least" appears three times as three DIFFERENT phrases (:163 S-9's floor, :240 leg (a)'s disclosure, :247 leg (f)'s prefix), "exit 0" twice (:240 leg (a), :269 leg (q)), and leg (a) is ONE two-line entry at :239-240 with one oracle. A correction is a measurement like any other, and a live token will not record a false claim about the plan's own bytes; the approve stands regardless
- SCOPE: eight IN rows with per-row evidence and SCOPE_DIFF_RESULT all-in. OUT and ZERO-DIFF: sessions.cpp, render.cpp, envelope.cpp (S-9 count non-feed, leg (f) is the control); open.cpp:176-185 and :311-315 (S-7a, leg (q) is the control); main.cpp and the list/info verbs (R-6.2/Step 6); pack/** and serialize; every other .github byte; sealed design bytes; the harness. A discovered need for an OUT path is a STOP to me
- SEQUENCE, ONE COMMIT: transcribe m-3's line re-read at transcription time (the pin 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 CHECKS what you landed and is never what you type) → implement to the LOCKED L bytes 10c8e8e6 at 8c7f9281 and not to this relay's paraphrase → observe macOS local and ubuntu-24.04 linux/amd64 Docker on that tree → transcribe the four counts from each target's own catch.xml → commit ONCE citing both run ids. RED-first states may exist in the worktree; no incoherent state may be committed
- EVIDENCE E2: named mutants (m)/(n)/(o)/(q) EXECUTED, observed RED, reverted, then GREEN, and reported — a compile failure earns no behavioural-RED credit; legs (a)/(b) carry the executed RED at 9729191 and must report GREEN at the successor; NO vacuous assertion anywhere, leg (h) absent not stubbed not ticked, the listing halves unasserted, no stub-class annotation text (veto L-V5 unconditional)
- L's six vetoes and three STOPs carried, all routing through me and then UP through the orchestrator, never sideways to an m-x seat; K's one-identifier rule, A5's biconditional and at-least floor, A3.1's notice and m-3's V1–V11 continue to bind. Returns for my byte verification, then m-1's byte veto AND m-3's combined re-review — both gate the hand-up. Actions NOT invoked; branch LOCAL and UNPUBLISHED; merge BLOCKED by the land order; merge is not push is not release; release hold ABSOLUTE
