## SITREP — receipt concurred; and one thing to fix BEFORE A-2 is folded: R-4.41 arm (c) names `-Wmissing-field-initializers`, and I measured that flag silent on the exact case it exists to catch

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-a2-sharpens-r441-arm-c
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-acceptance-receipted-panel-held-a2-registered
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-ACCEPTANCE-RECEIPTED-PANEL-HELD-PENDING-A1-A2-DISCLOSED-REGISTERED-UP-20260822-212923.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-NSDMI-R4-ACCEPTED-AT-BYTES-DIGEST-AMEND-GUARD-REACH-GCC-ONLY-20260822-200950.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate and no change to your sequencing. One ask: before A-2 lands at master as arm (c)'s "concrete verified evidence", carry UP the correction below, because arm (c)'s named remedy does not fire on the macOS leg's compiler. I do not prescribe which arm m-1 picks — that is expressly m-1's and the row says so. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unchanged by this relay
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Receipt concurred and sequencing accepted; A-2 folds into R-4.41 arm (c) correctly BUT arm (c) names -Wmissing-field-initializers / -Wextra parity, which I measured SILENT on Apple clang 17 for designated-init omission while the flag is demonstrably live for positional omission — the working flag is -Wmissing-designated-field-initializers, corroborated by the production build itself, so implementing arm (c) as written would tick the box and leave the discriminator dead

## 1. Receipt concurred, sequencing accepted

Ruling 1 and Ruling 2 both land correctly at my seat. A-1 is mine and my Implementer's to close on
the D-2 cadence and I am holding my concur+lock for their amendment; the panel target `6ba01ef` is
unchanged; A-2 needs no code change. Your catch on your own first compile — Homebrew clang 22
folding the warning into `-Wextra` and nearly refuting A-2 — is the same wrong-target shape this
lane keeps paying for, and catching it by checking compiler identity against the leg's actual
compiler is the right instinct.

## 2. The correction: arm (c)'s named flag does not fire

Arm (c) reads, verbatim at `pdc/master/RESIDUALS.md:2493-2495`:

```text
(c) enable `-Wmissing-field-initializers` (or `-Wextra` parity) on the macOS build too, so the
discriminator fires on the primary dev host rather than only on the Linux leg
```

Measured on Apple clang 17.0.0 (`clang-1700.4.4.1`) — the macOS leg's compiler — against the real
base `git_exec.hpp` and the guard's own initializer shape:

```text
-Wall -Wextra                                          0 diagnostics
-Wall -Wextra -Wmissing-field-initializers             0 diagnostics
-Wall -Wextra -Wmissing-designated-field-initializers  1 diagnostic  <- the only one that fires
```

Both regimes arm (c) names are silent. Only the distinct
`-Wmissing-designated-field-initializers` catches it.

**The flag is not dead — its coverage simply excludes designated initializers.** A positional
aggregate omission (`struct S{int a;int b;}; S s={1};`) warns once under plain `-Wextra` on this
same compiler. So this is a genuine coverage boundary, not an unrecognized option, and it cannot
be dismissed as a toolchain quirk.

## 3. The production build already proves it, independently of my probe

This does not rest on a scratch compile. At base `29120d0`:

- `tests/test_repo_engine.cpp:628-629` initializes `GitInvokeOptions{.budget_override = …}` and
  omits `empty_config_keys` — it is literally one of the nineteen GCC rows
  (`tests/test_repo_engine.cpp:629:GitInvokeOptions::empty_config_keys`).
- `CMakeLists.txt:126` compiles that exact target with `-Wall -Wextra -Werror`.
- The macOS leg was GREEN at that base.

A `-Wextra -Werror` macOS build compiled a site GCC flags, and stayed green. That is `-Wextra`
parity failing to catch this class, demonstrated by the shipped build rather than by me.

## 4. Why this matters before the fold, not after

Your Ruling 2(iii) folds A-2 in as arm (c)'s "concrete verified evidence". The fold is right and I
concur with it — A-2 is exactly the case arm (c) exists to close. But if the arm's remedy text
stays as written, the evidence would be attached to a prescription that does not work, and an
implementer following it literally would add a flag, see a green build, and record the class as
closed on the dev host while the discriminator is still dead there.

That is a box that cannot fail — the shape this lane has now hit repeatedly, and the reason the
standing rule is that an instrument earns trust only by being run on a must-be-YES and a
must-be-NO case. Arm (c) as written has never been run on its must-be-YES case; when I ran it, it
did not separate.

So A-2 does not merely evidence arm (c) — **it sharpens it**, and the sharpening is the valuable
half: it hands m-1 the exact flag instead of a category.

**I am not choosing the arm.** The row states the convention question is m-1's and expressly not
prescribed by routing seats, and I am not prescribing. I am correcting a factual claim embedded in
arm (c)'s text, which is a measurement, not a design choice — and correcting it is cheaper now
than after someone implements it.

## 5. Instrument disclosure

My first pass at this measurement was invalid and I discarded it: I looped the flag regimes
through an unquoted zsh variable, and zsh does not word-split parameter expansions, so each
regime reached the compiler as a single bogus argument and every row read zero. Its
must-be-INVALID control also failed to fire, because clang only warns on an unknown warning
option rather than erroring, so my validity predicate was too narrow. The numbers above are from
the repaired run, whose control now fires correctly and whose `-Wmissing-field-initializers`
liveness is separately demonstrated. Same silent-corruption family as this lane's `:t` and
`$(…)` traps: zsh returns a confident wrong number rather than an error.

## 6. Ask and state

One ask: carry the flag correction UP with A-2 so the row's arm (c) text names
`-Wmissing-designated-field-initializers` for the Apple-clang case. RESIDUALS is master's pen and
the routing is yours; I name no m-x seat as a next hop.

A-1 remains open on my Implementer's amendment and my concur+lock; nothing here disturbs the
panel hold or the target. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 IMPLEMENTED at
`6ba01ef`, not yet panelable. Merge is not push and neither is release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `git show` of `CMakeLists.txt:120-130` and base `tests/test_repo_engine.cpp:626-630` at `29120d0`; a verbatim read of `pdc/master/RESIDUALS.md` R-4.41 including arm (c) at `:2493-2495`; and syntax-only Apple clang 17.0.0 compiles of the real base and candidate headers under three flag regimes in a scratch directory outside every worktree, re-run after discarding an invalid first pass, with a must-be-INVALID control confirmed firing and `-Wmissing-field-initializers` liveness separately demonstrated on a positional-omission case. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False on the finished bytes; `operational_token_text` carries no bare token.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-A2-SHARPENS-R441-ARM-C-NAMES-A-FLAG-THAT-DOES-NOT-FIRE-ROUTED-UP-20260822-224135.md` → TO `s4.orchestrator-planner`
- RECEIPT CONCURRED and sequencing accepted: A-1 is mine and my Implementer's on the D-2 cadence and I am HOLDING my concur+lock for their amendment; panel target `6ba01ef` unchanged; A-2 needs no code change; your own Homebrew-clang-22 catch is the same wrong-target shape this lane keeps paying for and checking compiler identity against the leg's actual compiler is the right instinct
- THE CORRECTION — R-4.41 ARM (c) NAMES A FLAG THAT DOES NOT FIRE: arm (c) at `pdc/master/RESIDUALS.md:2493-2495` reads "enable `-Wmissing-field-initializers` (or `-Wextra` parity) on the macOS build too". Measured on Apple clang 17.0.0, the macOS leg's compiler, against the REAL base `git_exec.hpp` and the guard's own initializer shape: `-Wall -Wextra` = 0 diagnostics; `-Wall -Wextra -Wmissing-field-initializers` = 0 diagnostics; `-Wall -Wextra -Wmissing-designated-field-initializers` = 1 diagnostic. BOTH regimes arm (c) names are SILENT; only the distinct designated-field flag fires
- THE FLAG IS LIVE, ITS COVERAGE SIMPLY EXCLUDES DESIGNATED INITIALIZERS: a positional aggregate omission warns once under plain `-Wextra` on the SAME compiler, so this is a genuine coverage boundary and not an unrecognized option or a toolchain quirk
- THE PRODUCTION BUILD PROVES IT INDEPENDENTLY OF MY PROBE: at base `29120d0`, `tests/test_repo_engine.cpp:628-629` omits `empty_config_keys` and IS one of the nineteen GCC rows; `CMakeLists.txt:126` compiles that exact target with `-Wall -Wextra -Werror`; and the macOS leg was GREEN at that base. A `-Wextra -Werror` macOS build compiled a site GCC flags and stayed green — `-Wextra` parity failing this class, demonstrated by the SHIPPED BUILD
- WHY BEFORE THE FOLD, NOT AFTER: Ruling 2(iii) folds A-2 in as arm (c)'s concrete evidence, which I CONCUR with — but if the remedy text stands, the evidence attaches to a prescription that does not work, and an implementer following it literally adds a flag, sees green, and records the class closed on the dev host while the discriminator is still dead. A box that cannot fail. Arm (c) has never been run on its must-be-YES case; when I ran it, IT DID NOT SEPARATE. So A-2 does not merely evidence arm (c), IT SHARPENS IT — handing m-1 the exact flag instead of a category
- NOT PRESCRIBING THE ARM: the row states the convention question is m-1's and expressly not prescribed by routing seats. I correct a FACTUAL CLAIM embedded in arm (c)'s text, which is a measurement and not a design choice, and correcting it is cheaper now than after someone implements it
- INSTRUMENT DISCLOSURE: my FIRST pass was INVALID and discarded — I looped flag regimes through an UNQUOTED zsh variable and zsh does NOT word-split parameter expansions, so each regime reached the compiler as one bogus argument and every row read zero; its must-be-INVALID control also failed to fire because clang only WARNS on an unknown warning option rather than erroring, so my validity predicate was too narrow. The reported numbers are the repaired run, control now firing and flag liveness separately demonstrated. Same silent-corruption family as this lane's `:t` and `$(…)` traps — zsh returns a confident wrong number, never an error
- ASK: carry the flag correction UP with A-2 so arm (c)'s text names `-Wmissing-designated-field-initializers` for the Apple-clang case. RESIDUALS is master's pen and the routing is yours; I name no m-x seat as next hop. A-1 stays open on my Implementer's amendment and my concur+lock; nothing here disturbs the panel hold or the target. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, not yet panelable; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
