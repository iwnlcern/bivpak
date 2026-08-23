## PLAN (concurrence + receipt — the arm (c) flag correction is CONFIRMED at my seat with a validated instrument, and I am carrying it UP to master this turn; nothing here disturbs the panel hold, A-1, or the target `6ba01ef`) — **YOUR CORRECTION IS RIGHT AND I RE-MEASURED IT RATHER THAN ACCEPTING IT: R-4.41 arm (c) at `pdc/master/RESIDUALS.md:2493-2494` names `-Wmissing-field-initializers` (or `-Wextra` parity), and that flag is SILENT on the designated-initializer omission the guard actually catches. On Apple clang 17.0.0 (`clang-1700.4.4.1`), the macOS leg's compiler, against a designated-init omission: `-Wall -Wextra` → 0; `-Wall -Wextra -Wmissing-field-initializers` → 0; `-Wall -Wextra -Wmissing-designated-field-initializers` → 1. And the named flag is LIVE — a POSITIONAL aggregate omission warns under plain `-Wextra` (1 diagnostic) — so it is a genuine coverage boundary excluding designated initializers, exactly as you measured, not an unknown option. My must-be-INVALID control (a bogus flag) now fires correctly; the instrument separates.** **AND I HIT THE SAME TRAP YOU DISCLOSED, which is worth saying plainly: my FIRST repaired-looking run read the three designated regimes as 0/0/0 — because I looped the flag strings through an UNQUOTED variable and zsh does not word-split parameter expansions, so each regime reached clang as one bogus argument, and my grep then FALSE-MATCHED the flag name inside clang's "unknown warning option" message. Only re-running with literal separate arguments and a validity guard (reject output containing "unknown warning") made it separate. Your disclosed `:t`/`$(…)` zsh-silent-corruption family caught me one level over; the discriminator run is what surfaced it. Your instrument disclosure was not ceremony — it was a live warning I needed.** **THE PRODUCTION-BUILD COROBORATION HOLDS at facts I have verified: base `tests/test_repo_engine.cpp:628` omits `empty_config_keys` (a designated-init omission, one of the nineteen GCC rows), `CMakeLists.txt:126` compiles that target with `-Wall -Wextra -Werror`, and the macOS leg was green there — so `-Wextra` parity demonstrably failed to catch this class in the SHIPPED build, independent of any scratch compile.** **CARRIED UP THIS TURN: I route the flag correction to master (`230144`, master CC), recommending arm (c)'s prescription text name `-Wmissing-designated-field-initializers` for the Apple-clang case — a FACTUAL correction to a measurement embedded in the arm's text, NOT a choice of which arm m-1 picks (the convention remains expressly m-1's, and I prescribe nothing). As written, arm (c) is a box-that-cannot-fail: an implementer adds a flag already in `-Wextra`, sees green, records the class closed while the discriminator is dead — the shape this lane keeps naming. A-2 does not merely evidence arm (c); it SHARPENS it, handing m-1 the exact flag instead of a category.** NOTHING ELSE MOVES: A-1 remains yours and your Implementer's on the D-2 cadence (I await your concur+lock report); the Stage-3 panel stays HELD on `6ba01ef` and I convene the moment you report A-1 LOCKED; A-2 needs no code change and `6ba01ef` is untouched. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, not yet panelable. origin/main untouched; schema F+G-fenced; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-a2-arm-c-flag-correction-concurred
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-acceptance-receipted-panel-held-a2-registered
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-A2-SHARPENS-R441-ARM-C-NAMES-A-FLAG-THAT-DOES-NOT-FIRE-ROUTED-UP-20260822-224135.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — a concurrence receipt on a factual flag correction I re-verified at my seat and am carrying UP to master (RESIDUALS is master's pen); no code change, `6ba01ef` unmoved, the panel hold and A-1 undisturbed. Each eventual Wave-A merge remains a NEW operator word. No merge/push/PR-mutation/schema/release. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unchanged by this relay
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — concurrence: arm (c) names -Wmissing-field-initializers which I re-measured SILENT on the designated-init omission under Apple clang 17 (firing flag is -Wmissing-designated-field-initializers; the named flag is live on positional omission so a genuine coverage boundary); I hit the same zsh unquoted-variable trap you disclosed and the discriminator run caught it; production build corroborates; carried UP to master this turn (230144); panel hold/A-1/target undisturbed

## 1. Confirmed at my seat (Apple clang 17.0.0, the macOS leg's compiler)

```text
designated-init omission (the guard's shape):
  -Wall -Wextra                                          0
  -Wall -Wextra -Wmissing-field-initializers             0   <- arm (c)'s named flag: SILENT
  -Wall -Wextra -Wmissing-designated-field-initializers  1   <- the only one that fires
positional omission (liveness control):
  -Wall -Wextra                                          1   <- named flag IS live, coverage excludes designated
invalid control (bogus flag)                             fires -> instrument separates
```

## 2. I hit the same trap; the discriminator caught it

```text
first run   looped flag strings through an UNQUOTED var; zsh does not word-split parameter expansions ->
            each regime reached clang as ONE bogus arg; grep false-matched the flag NAME in the
            "unknown warning option" message -> read 0/0/0 (a dead instrument)
repair      literal separate args + validity guard rejecting "unknown warning" -> separates correctly
```

## 3. Disposition

```text
UP     carried to master 230144 (CC): arm (c) prescription should name -Wmissing-designated-field-initializers
       for the Apple-clang case; FACTUAL correction to the arm's text, NOT a choice among arms (m-1's, unprescribed)
hold   A-1 yours on D-2; panel HELD on 6ba01ef, I convene on your A-1-LOCKED report; 6ba01ef untouched
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product/test/branch/ref/worktree moved and `6ba01ef` is untouched. Read-only verification at my seat: syntax-only Apple clang 17.0.0 compiles of a designated-init-omission and a positional-omission shape under three flag regimes with literal separate args, a must-be-INVALID bogus-flag control confirmed firing, and a discarded first run corrupted by an unquoted-zsh-variable + grep-substring false match, all in `$CLAUDE_JOB_DIR/tmp` outside every worktree; `git show 29120d0:tests/test_repo_engine.cpp` :628 (omits empty_config_keys) and `CMakeLists.txt` :126 (-Wall -Wextra -Werror); a verbatim read of `pdc/master/RESIDUALS.md` R-4.41 arm (c) at :2493-2494. No merge, push, PR mutation, or remote CI. I issue NO bare token here. This relay + its INDEX row ride ONE explicit-path docs-lane commit.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read at 230032 immediately before writing); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; `--relay-root`; add and commit path-scoped. Standing INDEX reds (R-4.27 class + sibling time inversions) disclosed, none mine; my appended row 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored untracked state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-A2-ARM-C-FLAG-CORRECTION-CONCURRED-CARRIED-UP-20260822-230032.md` → `s4-matrix.planner`, `s4-matrix.implementer`
- ARM (c) FLAG CORRECTION CONFIRMED at my seat with a validated instrument: R-4.41 arm (c) (RESIDUALS.md:2493-2494) names -Wmissing-field-initializers / -Wextra parity, SILENT on the designated-init omission under Apple clang 17.0.0 (macOS leg's compiler): -Wall -Wextra 0, +-Wmissing-field-initializers 0, +-Wmissing-designated-field-initializers 1; the named flag is LIVE on a POSITIONAL omission (1 under plain -Wextra) so a genuine coverage boundary not an unknown option; must-be-INVALID control fires, instrument separates
- I HIT THE SAME TRAP YOU DISCLOSED: my first run looped flag strings through an UNQUOTED variable and zsh does not word-split parameter expansions, so each regime reached clang as one bogus arg and my grep false-matched the flag NAME in the unknown-warning-option message -> read 0/0/0; repaired with literal separate args + a validity guard rejecting unknown-warning output; your :t/$(…) zsh-silent-corruption family caught me one level over and the discriminator run surfaced it
- PRODUCTION BUILD COROBORATES at verified facts: base tests/test_repo_engine.cpp:628 omits empty_config_keys (a designated-init omission, one of the 19 GCC rows), CMakeLists.txt:126 compiles it with -Wall -Wextra -Werror, macOS leg green there -> -Wextra parity failed this class in the SHIPPED build, independent of any scratch compile
- CARRIED UP to master 230144 (CC): arm (c) prescription should name -Wmissing-designated-field-initializers for the Apple-clang case; a FACTUAL correction to a measurement embedded in the arm's text, NOT a choice of which arm m-1 picks (convention expressly m-1's, I prescribe nothing); as written arm (c) is a box-that-cannot-fail (add a flag already in -Wextra, see green, record the class closed while the discriminator is dead); A-2 does not merely evidence arm (c), it SHARPENS it, handing m-1 the exact flag instead of a category
- NOTHING ELSE MOVES: A-1 yours and your Implementer's on D-2 (I await your concur+lock report); Stage-3 panel HELD on 6ba01ef, I convene on your A-1-LOCKED report; A-2 needs no code change, 6ba01ef untouched; T1 00c06d9 / T2 7688bbd / T3 70601fc FINAL; T4 IMPLEMENTED at 6ba01ef not yet panelable; origin/main untouched; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
