## IMPL — Stage 1b-ii DISPATCH: implement `M3-J-1..7` + `A3.1`/`A3.2(1..5)`/`A3.3` on the consumer half, under V1–V11, with the STOP-1 exit class carved out

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage1b-ii-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-stage1b-ii-rev1
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-STAGE1B-II-REV1-APPROVE-V11-OPEN-SIDE-20260815-050127.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Stage 1b-ii returns for the owning-domain byte review(s); the STOP-1 exit class stays held until the locked `m3-addendum-4` successor arrives; merge, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-1.planner
SUBJECT: IMPL — Stage 1b-ii delegated dispatch on approved rev0+rev1; twelve IN paths with per-row evidence, three WITHIN-FILE boundaries, test_manifest.cpp proven NOT collateral, STOP-1 exit class excluded

DISPATCH IMPL

## 1. Lineage, written out hop by hop

I have been wrong about this edge twice in this build, so it is enumerated rather than asserted:

```text
this token  s4-floor-slice-e-stage1b-ii-impl
  PARENT -> s4-floor-slice-e-plan-review-stage1b-ii-rev1
            PHASE PLAN-REVIEW · FROM s4-floor.implementer · PLAN_REVIEW_VERDICT: approve
    PARENT -> s4-floor-slice-e-plan-stage1b-ii-rev1
              PHASE PLAN · FROM s4-floor.planner · TO s4-floor.implementer
```

`IN_REPLY_TO` is the review because it also prompted this relay; **the authorizing edge is `PARENT_DISPATCH_ID`,** and it is the approving review, not the plan and not an orchestrator clearance.

## 2. Pins re-derived at THIS act

```text
m3-addendum-3   eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa @ a016f953   EQUAL
ADDENDUM J      94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18 @ e30f845    EQUAL
m3-addendum-4   13c61b9cc2ca318d2f744e40bc526e52a9a5d983fab5c9e903f14fd4aa67822b LIVE, "rev1 — NOT sealed"
                => STOP-1 HOLDS AT THE MOMENT OF THIS TOKEN
BASE            469d6d31f293415a2b8f44cd71d0782e61a13a35 (local, unpublished; parent c74c20b)
```

**`m2-addendum-12` is deliberately absent.** It is m-2's pack-side collect contract and is **not consumed by this stage**; the Stage 1b-ii fence is exactly the two documents above. Recording the omission so it does not read as a dropped pin. *(Instrument note: my first attempt to re-derive an A12 hash returned `e3b0c442…`, the digest of the EMPTY STRING, because `git show` failed on a guessed path and the empty output was hashed anyway. A hash command that fails still prints a hash. **Check that the bytes existed before believing the digest.**)*

## 3. SCOPE_DIFF — twelve IN paths

SCOPE_DIFF:
- src/core/open/sessions.hpp -> in
- src/core/open/sessions.cpp -> in
- src/core/open/render.hpp -> in
- src/core/open/render.cpp -> in
- src/core/report/envelope.cpp -> in
- src/cli/main.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_render.cpp -> in
- tests/test_envelope.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_pack.cpp -> in
- tests/fixtures/slice-e/** -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `src/core/open/sessions.hpp` — carries `parent_count`/`child_count` (`:19-20`) and the lossy `entry_schema_skipped` bool (`:22`); J-2 renames both fields, J-6 replaces the bool with a per-agent cardinal.
- `src/core/open/sessions.cpp` — `build_preview` is the **sole production accumulation** at `:343-345`; J-4 excludes over-schema entries from both counts and J-6 makes the skip a count there. **`any_sessions()` at `:315-319` is a WITHIN-FILE hard-out.**
- `src/core/open/render.hpp` — `render_summary`'s declaration at `:22-25` takes `SessionsOutcome`/`bool`/`path` and cannot reach the per-agent skipped cardinal that `A3.2(5)` requires.
- `src/core/open/render.cpp` — J-1's single printed split at `:244-245`; `A3.1`'s notice must land in the agent loop at `:181` as a **peer of** the caps/probe guard at `:182`; `A3.2(5)`'s line lands between the row loop closing at `:298` and the activation block opening at `:299`.
- `src/core/report/envelope.cpp` — `write_open_manifest_summary` (`:108-130`, per-agent object `:120-127`, `session_count` expression `:125`) gains J-3's two keys and A3.3's cardinal. **`write_manifest_summary` (`:80-102`) and the entire exit composition are WITHIN-FILE hard-outs.**
- `src/cli/main.cpp` — the five predicate consumers at `:270`, `:274`, `:282`, `:370`, `:377`; the two pre-write emissions at `:295-296` and `:334-335`, both above `run_session_leg` at `:357`.
- `tests/test_sessions.cpp` — reads `AgentPreview::parent_count` at `:348`, `:459`, `:471`, `:533`, `:590`, `:633`, `:698`, `:749`; rename collateral plus the count legs.
- `tests/test_render.cpp` — reads `AgentPreview::parent_count`/`child_count` at `:13-14`, `:24`, `:33`, `:93`, `:114`, `:170`, `:194`; rename collateral plus the `A3.1`/`A3.2(5)` golden legs.
- `tests/test_envelope.cpp` — reads `preview.parent_count` at `:326`, `:370`, `:387`, `:464`, `:495`; rename collateral plus leg (f)'s key present/absent arms.
- `tests/test_cli.cpp` — drives real invocations (`run_cmd("open … --consent …")` at `:584`, `:881`, `:896-898`); the only measured host for legs (h1)/(h2)/(h3a)/(h3b) and leg (i)'s two refusal paths.
- `tests/test_pack.cpp` — **RENAME-ONLY.** `AgentPreview` designated initializers at `:269-272` and `:2647` break on J-2/J-6. **The local variable `child_count` at `:261-264` is NOT an `AgentPreview` member and MUST NOT be renamed** — leave it; a gratuitous rename inflates a reviewable diff. **No assertion semantics change in this file.**
- `tests/fixtures/slice-e/**` — the established slice-E fixture root; the eleven legs need populations that do not exist (all-skipped, mixed 3-primary-with-descendant + over-schema, staged+failed+over-schema, probe-failure with a skip).

**`tests/test_manifest.cpp` is OUT, and this is a measured exclusion, not an omission.** Its `child_count` at `:133-142` is a **local `std::size_t`**, not `AgentPreview::child_count`. A name-grep puts this file in the rename population; reading it takes it out. **Do not edit it. If it fails to compile, that is a finding — STOP and report, because it would mean the rename reached further than measured.**

## 4. Three WITHIN-FILE boundaries — a path grant is not a file grant

Two granted files contain hard-outs, and a path-set check cannot see an ungranted change riding a granted file. **Evidence for these is required at hand-up as function-scoped diffs, not as a path list.**

```text
sessions.cpp   SessionPreview::any_sessions() body (:315-319)  UNTOUCHED   STOP-3 / V3
envelope.cpp   write_manifest_summary (:80-102)                UNTOUCHED   V11
envelope.cpp   exit_for_sessions (:422-431) + kind_for_row +
               ErrKind / to_string / exit_for_error rows       UNTOUCHED   STOP-1
```

## 5. The STOP-1 carve-out — what is NOT built

The unnamed 0-returning kind is an **exit-class separation**, not a key string: the over-schema skip and the genuine unknown-agent skip share `Row::unknown_agent_skipped` (`sessions.cpp:401-419`), separated only by `.reason`. Excluded until `m3-addendum-4` LOCKS and arrives as m-3's scoped successor:

- the new `ErrKind` enumerator, its wire spelling, its `exit_for_error` row;
- the `kind_for_row` branch keyed on `reason == "entry-schema"`;
- any change to `exit_for_sessions`;
- **leg (e) EXIT COUPLING.**

**The over-schema run continues to exit 2, exactly as today.** That is pre-existing behaviour, not a regression introduced here — **state it explicitly in the hand-up** so the gap cannot read as an oversight. **m-3's proposed spelling is visible in an INDEX row; it is receipted, NOT locked, and MAY NOT BE TYPED.** Needing the name for any reason is STOP-1: halt and route UP through the orchestrator.

## 6. Behaviour to implement — determined, and bounded

**The five-surface split (`A3.2(4)`), V3-safe.** `any_sessions()` is neither widened nor modified: under J-4 it *becomes* the `eligible > 0` predicate. Add a sibling skipped predicate and disjoin it at the three OR-surfaces only.

```text
:270 disclosure  eligible>0 OR skipped>0      :274 prompt   eligible>0 ALONE
:370 envelope    eligible>0 OR skipped>0      :282 warning  eligible>0 ALONE
:377 summary     eligible>0 OR skipped>0
```

**All-skipped contract:** disclosure RENDER · envelope PRESENT · summary RENDER · prompt SUPPRESS · warning SUPPRESS.

**`A3.1` notice** — byte-exact, per agent, only when that agent's skipped count ≥ 1, **never nested under the caps/probe guard** (V2, leg (b)'s mutant). At 0 it does not render at all.

**`A3.2(5)` aggregate** — byte-exact, per agent, ≥ 1 only, between the row loop and the activation block, **in the agent order established by the rows above it** (independent sorting is a deviation). **`<imported>` = Σ over host-installed entries of `1 + that entry's id_map children count`.** Staged counts zero; every failure class counts zero. **Do not sum `outcome.id_map` blindly — it also receives staged mappings; count only entries whose row outcome is `installed`.**

**`J-3` + `A3.3` open-side keys** — `primary_count`, `descendant_count` additive; `entry_schema_skipped_count` **suppressed at zero** (leg (f); `FX-J-1(p)` conformance). `session_count` is **never** removed, re-typed or version-signalled, and **retaining the `parent_count + child_count` expression at `:125` satisfies the exclusion by construction** — do not recompute it independently.

**`J-1`/V9** — both printed halves change together in one edit: `(<p> parent + <c> child)` → `(<p> primary + <c> descendant)`.

**Do NOT "fix" `R-4.28`** (`session_count` absolute pack-side / reader-relative open-side). Registered, predates the fence, and V10 vetoes the rename. **The impulse to tidy it is the thing to suppress.**

## 7. Acceptance — legs (a)–(k) minus (e), each with its executed mutant

Every leg carries a named mutant that must be **run and observed RED**, then reverted. **A compile failure earns no behavioural-RED credit** — a leg that failed to build has not been watched fail. h3a and h3b are **separate fixtures**: one reaches the non-prompt branch by having no TTY, the other by explicit consent, and a disjunctive fixture satisfies one while leaving the other unobserved. Leg (g) is worthless run anywhere but the fixtures where the probe-failure and `readable-newer-than-survey` causes actually fire. Leg (c) must be asserted on a fixture where imports DO occur, so it cannot pass merely because nothing rendered.

## 8. STOPs, vetoes, and the standing bars

**V1–V11 bind**, m-3's byte review is a checklist against them. **STOP-1** (the name) · **STOP-3** (`any_sessions()` body or any count mechanism beyond the determined J-4/J-6 bytes) · **STOP-4** (`FX-J-1(p)` does not fold at the keyboard). **Default: ANY silence not on m-3's list is a STOP** — halt and route UP through the orchestrator to master; m-3 owns the answers and is **not** your addressee. Add nothing, remove nothing, reinterpret nothing.

RED-first with receipts. macOS canonical plus the **governing** local Ubuntu 24.04 `linux/amd64` Docker, with a base-container control at `469d6d3` on any change in the Linux failure count — known inherited rows expected, anything else is a finding. **Actions NOT invoked.** Branch stays **LOCAL and UNPUBLISHED**: no push, no PR, no merge, no seal, no publication. **The land order binds and the early-merge narrowing stays REFUSED.** Live `~/.claude` / `~/.codex` are never read-for-mutation or written — fixture trees or explicit disposable copies only. **No credential collection.**

**The token ends at a STOP covering Stage 1b-ii only.** Return for my byte verification and the owning-domain review(s); the `M3-J-1..3` review-owner cell is routed and must be answered before hand-up, not inferred at the keyboard.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — this relay delegates. Read-only measurement this pass at `469d6d3` establishing the scope rows: the `parent_count`/`child_count`/`entry_schema_skipped` reader population across `src` and `tests`, each hit classified as `AgentPreview` member or unrelated local (which is what excludes `tests/test_manifest.cpp`); `write_open_manifest_summary`/`write_manifest_summary` spans; `test_cli.cpp`'s invocation capability. pdc read-only: both fence pins re-derived EQUAL and `m3-addendum-4` re-read live as NOT sealed. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; **and `--relay-root` run against this token before filing**, because the exact-file arm false-greens a wrong lineage and has done so twice in this build. `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1B-II-DISPATCH-IMPL-TOKEN-20260815-051223.md` → `s4-floor.implementer` — **LIVE bare `DISPATCH IMPL` token**, parented to the approving PLAN-REVIEW `s4-floor-slice-e-plan-review-stage1b-ii-rev1`
- SCOPE: twelve IN paths with per-row evidence, `SCOPE_DIFF_RESULT: all-in`; `tests/test_pack.cpp` is **RENAME-ONLY** with its local `child_count` at `:261-264` explicitly NOT renamed
- MEASURED EXCLUSION: `tests/test_manifest.cpp` is OUT because its `child_count` is a **local variable**, not an `AgentPreview` member — a name-grep includes it, reading it excludes it; if it fails to compile that is a FINDING, not a licence to edit
- THREE WITHIN-FILE HARD-OUTS inside granted files — `any_sessions()` body, pack-side `write_manifest_summary`, the whole exit composition — with function-scoped diff evidence required at hand-up, since a path-set check cannot see an ungranted change riding a granted file
- STOP-1 carve-out: the exit CLASS and leg (e), until `m3-addendum-4` LOCKS (re-verified live as `13c61b9c…`, `rev1 — NOT sealed`); the over-schema run keeps exiting 2 and the hand-up must SAY SO; the receipted spelling MAY NOT BE TYPED
- DETERMINED and carried: open-side-only keys; `session_count` exclusion satisfied by RETAINING the `:125` expression; one printed relabel site; `R-4.28` not ours to fix
- V1–V11 + STOPs 2-4 + default-silence-is-a-STOP; legs (a)-(k) minus (e) each with an EXECUTED mutant and no behavioural-RED credit for a compile failure; h3a/h3b separate fixtures
- Pins re-derived EQUAL at this act; `m2-addendum-12` deliberately absent as not consumed by this stage
- Branch LOCAL and UNPUBLISHED at `469d6d3`; Actions NOT invoked; merge BLOCKED by the land order; publication, PR, seal, deployment and release HELD; release hold ABSOLUTE
