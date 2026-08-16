## IMPL — Stage 1b-ii successor DISPATCH: the K token-time join PASSES on every element, and the coupled A4+A5+K commit is authorized

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-successor-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-rev1-w2-k-only
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-W2-EFFECTIVE-PATH-OPEN-RUN-K-JOIN-THEN-DISPATCH-20260816-152021.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the successor returns for m-1's byte-level MANIFEST veto AND m-3's COMBINED successor re-review, both of which gate the hand-up and neither of which this token discharges. Merge, seal, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
TARGET_DESIGN_SHA256: 5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667
TARGET_DESIGN_COMMIT: 0e455ef5bf9b48870f6d061146a0dbd80dd2de96
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: IMPL — Stage 1b-ii successor dispatch on the rev1-approved plan; K token-time join run at the registry/locked bytes and PASSES on all seven elements; fourteen IN paths, three within-file fences, one coupled commit

DISPATCH IMPL

## 1. The K token-time join — run at my seat, at the bytes, never from a summary

`D-5.17` instance 2, and the discipline that refused this token at `131839`. **Every element re-derived here, not carried:**

```text
1  W-2 STATUS          RESIDUALS.md:1885  "CONCURRED / EFFECTIVE"                          PASS
2  COVERAGE            rev1 @ 73d4b22 hashes 3178243a0af66eaf1fb85685651cbb0b6880d1ccd8
                       4517fd1ac1860ec9054d15 — EQUAL to the folded coverage AND to
                       142742's TARGET_PLAN_SHA256                                          PASS
3  OWNER LOCK DECL     054533, FROM m-1.planner — the complete three-field tuple:
                       lock m1-addendum-K-5da667fa-lock-20260816
                       SHA  5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667
                       cmt  0e455ef5bf9b48870f6d061146a0dbd80dd2de96
                       post-stamp b715060935dce6fa9545a62a471e6189c080a71157cedc080633c520ea9e6a6b
                       ALL FOUR equal to my own re-derivation                               PASS
4  VP ASSOCIATION      142742, FROM master.orchestrator-reviewer — same three-field identity,
                       PLAN_REVIEW_VERDICT approve, VP_CONCURRENCE granted, and it names the
                       one-item {K} list verbatim                                           PASS
5  GATE DISPOSITIONS   051727 m-1.implementer approve · 053722 VP approve — BOTH at
                       5da667fa… @ 0e455ef5…, and 053722 names NO DESIGN_LOCK_ID, which is
                       correct: a pre-lock review cannot name a later lock                  PASS
6  NO SUPERSESSION     exactly one K lock exists across RESIDUALS + ARCHITECTURE            PASS
7  NO UNLOCKED EDIT    live-vs-locked diff is ONE hunk, STATUS block only — every byte
                       outside it identical to 0e455ef5 by construction                     PASS
   ORDERING            051727 < 053722 < 054533 < 141427 (rev1) < 141549 (approve) <
                       142742 (concurrence) < this token — every artifact precedes it       PASS
```

**No mismatch. The join holds, so W-2's coverage attaches and the token issues.**

## 2. Lineage, hop by hop

```text
this token  s4-floor-slice-e-successor-impl
  PARENT -> s4-floor-slice-e-plan-review-successor-rev1-w2-k-only
            PHASE PLAN-REVIEW · FROM s4-floor.implementer · PLAN_REVIEW_VERDICT: approve
    PARENT -> s4-floor-slice-e-plan-successor-three-locks-rev1
              PHASE PLAN · FROM s4-floor.planner · TO s4-floor.implementer
```

## 3. Scope — the plan's fourteen rows, unchanged

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
- `src/core/manifest/manifest.hpp` — K-R1 LOCATION: `kEntrySchemaParseCeiling`, `inline constexpr int`, value 2, beside `kFormatVersion` and `kManifestByteCap` (both verified present at `:13-14`).
- `src/core/manifest/manifest.cpp` — K-R1 use (1): the `> 2` literal at `:350` REPLACED by the constant; `:347`'s `< 1` validity floor PRESERVED BY NAME per K-R3(1).
- `src/core/support/error.hpp` — A4.1: the new `ErrKind` member beside `UnknownAgentSkipped` (`:28`).
- `src/core/support/error.cpp` — A4.1: wire `"EntrySchemaSkipped"`, PascalCase per that file's convention (`:43-44`).
- `src/core/report/envelope.cpp` — A4: `exit_for_error` (`:390`) gains ONE row at **0**; A5.4: the open-side per-agent object gains `entry_schema_unparsed_count`.
- `src/core/open/sessions.hpp` — the ONE shared supported-ceiling constant, and `entry_schema_unparsed_count` on `AgentPreview` beside `entry_schema_skipped_count` (`:22`).
- `src/core/open/sessions.cpp` — `:349`/`:419` unified under the shared supported constant AT VALUE 1; the stub discriminator comparing against `kEntrySchemaParseCeiling` (K-R1 use 2, never a copy); the unparsed accumulator; A5.2's `1 + children_known`; and `kind_for_row` (`:259-268`) splitting on `reason == "entry-schema"` — it already takes `reason`, so no signature change.
- `src/core/open/render.cpp` — A5.3's at-least prefix in BOTH golden lines (notice `:235-242`, aggregate `:309+`).
- `tests/test_manifest.cpp` — FX-K-1 (a)/(b); BIND the existing `entry_schema == 99` assertions (`:595`, `:624`, `:643`) to the constant rather than authoring a fresh shape.
- `tests/test_sessions.cpp` — count-source, both discriminators, unparsed accumulator, `kind_for_row`'s split.
- `tests/test_render.cpp` — A5.3's exact/at-least golden pairs.
- `tests/test_envelope.cpp` — A5.4 key present/absent; the A4 wire string in the envelope.
- `tests/test_cli.cpp` — A4 legs (a)–(d) need whole-run invocations; A5 legs (l)/(m)/(n)/(o) assert notice + summary + envelope together.
- `tests/fixtures/slice-e/**` — the leg populations do not exist yet: childed parsed-but-held, childed-wire stubbed at schema 3, mixed shapes, the two-agent asymmetric distribution for (p), FX-K-1's boundary pair.

**OUT — a discovered need is a STOP, not a licence:** `src/cli/main.cpp` (A4's kind never reaches the CLI); `src/core/open/render.hpp` (no signature change — both renderers already receive the preview; any helper must be FILE-LOCAL); `src/core/pack/**` (K-R2: the writer's 1..2 stamp domain is J-R3's and does not move with the parse ceiling); `manifest-format.md` (not in this repo); `.github/**`; sealed design bytes; harness.

## 4. Three WITHIN-FILE fences — function-scoped diffs required at hand-up

```text
manifest.cpp   ONLY the :350 gate literal -> constant. :347's `< 1` floor preserved BY NAME.
               K-R3(3): NO other export-surface change — nothing moved, renamed or re-typed.
envelope.cpp   pack-side write_manifest_summary UNTOUCHED (V11). exit_for_error gains EXACTLY one row.
sessions.cpp   any_sessions() body UNTOUCHED. K-R3(2): a THIRD adjacent discriminator in
               build_preview's skipped branch is a STOP — there will be exactly TWO.
```

## 5. K's fences, VP-verbatim from the lock stamp

> *"Any lock may release only a successor floor PLAN fenced to K, locked A4, and locked A5. The export must land before or with the coupled implementation, m-1's byte-level veto and m-3's successor-byte review remain due, and the filed cell-3 arm-A / R-4.29 disposition remains unchanged."*

**And the non-ceremonial clause, carried because it is aimed at exactly this stage:** m-3's byte-level re-review at the successor implementation commit verifies the supported-ceiling sites, the new stub discriminator, the per-agent counts **AND** the deferred-leg disposition **TOGETHER** — the earlier approvals do not make that later gate ceremonial.

**K's vetoes:** K-R4(1) any surviving literal parse-ceiling comparison at ANY site including manifest's own gate · (2) the constant defined in more than one place, or the preview holding a copy · (3) both ceilings through ONE identifier · (4) a type mismatch forcing a cast · (5) silent STOP-filling. **K's STOPs:** K-R3(1) a NEW upper-boundary/discriminator class over `entry_schema` (the `< 1` floor is EXPLICITLY not this) · (2) a third adjacent discriminator · (3) any export-surface change beyond the one addition. **m-3's V1–V11 continue to bind.**

## 6. What implements, and the sequencing

**One coupled commit** — the export, the gate replacement, the two supported sites at VALUE 1, the kind, the count-source line, the unparsed key, both at-least variants, and the legs. K-R4(1) vetoes any surviving literal at ANY site, so a split would leave an intermediate head where the gate and the discriminator disagree. RED-first worktree states may exist during implementation; **no incoherent state may be committed.**

**Supported stays 1.** Cell 3 is closed on operator arm A; the schema-2-capable reader is `R-4.29` and is NOT this stage. **Legs {l, m, n, o} witness at this head; leg (p) is IMPLEMENTED AND GATED**, its guard keyed to the two constants — deferred while the supported ceiling is below `kEntrySchemaParseCeiling` — so it self-activates at the flip and cannot outlive its world. **It must remain an executable, countable unit whose conditional `SKIP` cannot abort or mask legs (l)–(o); a hidden pending tag, an unconditional skip, or a guard on anything other than the two exported constants is outside this authorization.** The hand-up reports (p) as **configured-deferred**, never as behaviourally witnessed.

**`<imported>`/`<skipped>` membership:** `1 + children_known` per A5.2, `children_known` = `entry.children.size()` uniformly by A5.4's biconditional. **Do not blind-sum `outcome.id_map`** — staged mappings live there too; count only rows whose outcome is `installed`, matched on agent AND image-session id.

## 7. Evidence and the standing bars

E2. **RED-first with receipts.** Every named mutant executed against the fixture that kills it, observed RED, reverted, then GREEN. **A compile failure earns no behavioural-RED credit.** macOS canonical plus the **governing** local Ubuntu 24.04 `linux/amd64` Docker, with the exact-base control at `d7db861` on any change in the Linux failure count. **Actions NOT invoked.** Branch stays **LOCAL and UNPUBLISHED** — no push, no PR, no merge, no seal, no publication. **The land order binds** and the early-merge narrowing stays REFUSED. Live `~/.claude` / `~/.codex` are never read-for-mutation or written — fixture trees or explicit disposable copies only. **No credential collection.**

**The token ends at a STOP covering the Stage 1b-ii successor only.** Return for my byte verification, then m-1's manifest veto and m-3's combined re-review — both gate the hand-up. **Any silence not on m-3's or K's lists is a STOP** routed UP through the orchestrator.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat — this relay delegates. Read-only this pass: the K token-time join run in full at the registry and locked bytes (W-2 status at `RESIDUALS.md:1885`; rev1 re-hashed at `73d4b22`; K re-hashed at `0e455ef5` and live; the live-vs-locked diff confined to one STATUS hunk; `054533`, `142742`, `053722`, `051727` each opened and their identity fields read; supersession checked across RESIDUALS and ARCHITECTURE). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; **and `--relay-root` run against this token before filing**, because the exact-file arm false-greens a wrong lineage and did so twice in this build. **The K cross-repo lineage red is now WAIVED under W-2's effective `{K}` coverage** — the join above is the evidence that entitles it, and it is disclosed rather than claimed absent. `.relays/s4/INDEX.md` tail re-read before appending; the file→lint→append→add→commit sequence runs as ONE unbroken `&&` chain. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — not mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-SUCCESSOR-DISPATCH-IMPL-TOKEN-20260816-152630.md` → `s4-floor.implementer` — **LIVE bare `DISPATCH IMPL` token**, parented to the rev1 plan-review approve
- **THE K TOKEN-TIME JOIN PASSES ON ALL SEVEN ELEMENTS**, run at the registry/locked bytes and never from a summary: W-2 EFFECTIVE; rev1 `3178243a…` equal to the folded coverage and to `142742`'s `TARGET_PLAN_SHA256`; `054533`'s complete three-field tuple + post-stamp equal to my own re-derivation; `142742` naming the same identity with concurrence granted; `051727`/`053722` both at the locked pin with `053722` correctly naming NO lock ID; exactly one K lock in existence; live-vs-locked confined to ONE STATUS hunk; every artifact preceding this token
- SCOPE: the plan's fourteen IN rows with per-row evidence, `SCOPE_DIFF_RESULT: all-in`; OUT rows unchanged (`main.cpp`, `render.hpp`, `pack/**`, `manifest-format.md`, `.github/**`, sealed bytes, harness) and a discovered need for any of them is a STOP
- THREE WITHIN-FILE FENCES needing function-scoped diffs at hand-up: `manifest.cpp` only the `:350` literal with `:347` preserved by name; `envelope.cpp` pack-side untouched and `exit_for_error` gaining exactly one row; `sessions.cpp` `any_sessions()` untouched and no third adjacent discriminator
- ONE COUPLED COMMIT (K-R4(1) forbids a surviving literal at any site, so a split leaves the gate and the discriminator disagreeing); supported stays at VALUE 1; legs {l,m,n,o} witnessed, leg (p) IMPLEMENTED-AND-GATED on the two constants and reported as CONFIGURED-DEFERRED, never as witnessed
- K's VP-verbatim fences carried, plus the NON-CEREMONIAL clause: m-3's re-review checks the supported sites, stub discriminator, per-agent counts AND the deferred-leg disposition TOGETHER; K-R3 STOPs and K-R4 vetoes carried; m-3's V1–V11 still bind
- Returns for my byte verification, then m-1's manifest veto AND m-3's combined re-review — both gate the hand-up; branch LOCAL and UNPUBLISHED; Actions NOT invoked; merge BLOCKED by the land order; release hold ABSOLUTE
