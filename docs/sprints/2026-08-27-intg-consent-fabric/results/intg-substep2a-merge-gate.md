# Merge packet — sub-step 2a format act, tranche 2 (assembled 2026-09-04, held at completion)

Assembled by `intg.pair-planner` on master's carry `master/relays/intg-substep2a-format-act/PLAN-master-planner-20260904-185231.md`
("both owner reviews are green at the exact candidate — assemble the merge packet", the sub-step-1 §1–§8 shape).
This document is the packet of record.
It carries NO merge authority; the token is the operator's alone, presented by master on this packet's return.
Merged is not pushed, not published, not released; the release hold is ABSOLUTE.

## 1. Candidate identity

- Branch: `intg/format-act@a2f6fd1adf67fd86c8d0c692db34f113a9691135` (worktree `../bivpak-intg-format-act`; worktree and index EMPTY at assembly).
- Base: `main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996` (= the merge-base, measured; no hidden lineage).
- Series: exactly 4 commits, all authored `intg.pair-implementer`:
  `815677a` (N-R3 precedence lattice, Surface A) → `3618069` (born-shallow payload-only guards) → `363d812` (shallow_pointer before payload_only_unborn, N-R4) → `a2f6fd1` (THE ONE SYMMETRIC COMMIT: `repos[]` writer + parser + round-trip per sealed §2.3+G+H+N+O; fallible typed `serialize` (O-R1); one clause inventory at two enforcement points (O-R2/O-R3/O-R4); O-R6 label; the three ruled propagation sites (ASK-6 arm (a), `231935`); `require_empty_array("repos")` retired; no format_version bump).
- Superseded Task-3 commits retained by local tags, NOT on the branch: `retained-task3-9e6ebe8` → `9e6ebe8fca2454164051573323dd7adfa2901219`; `retained-task3b-b09e192` → `b09e1922c16da50b5bef0644d9923a567b98c468` (the Linux-red candidate of `181612`).
- Changed paths: exactly the TEN-path allowlist of record (membership and cardinality mechanically proved; sorted-list sha256 `431acfb6…`): `src/core/manifest/{manifest.cpp,manifest.hpp}`, `src/core/pack/pack.cpp`, `src/core/repo/{classify.cpp,restore.cpp,types.hpp}`, `tests/{test_cli.cpp,test_manifest.cpp,test_open.cpp,test_repo_engine.cpp}`.
- Sealed sources implemented: LOCKED O `m1-addendum-O-63c46631-lock-20260901` (bytes `63c46631…` @ `40b4f7a3`; post-stamp `0e990bac…`); LOCKED N `m1-addendum-N-82293732-lock-20260827`; LOCKED M rev8 `m1-addendum-M-2966b839-lock-20260825`; m-1's fence `151655` as extended by `045949`, the ASK-6 ruling `231935` (C-1..C-7), the C-4 correction `034802`, and the C-3 STOP ruling `183510` (route (A), T-1..T-5).
- Plan of record: `plans/PL-intg-substep2a-20260830.md` @ sha256 `beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265` (revision 15; approved exact-hash at `intg-substep2a-plan-review-15`, `PLAN-REVIEW-pair-implementer-20260904-043346.md`). Tokens consumed in order: `intg-substep2a-impl-2` (`055109`, STOP `063445`), `-impl-3` (`153402`, STOP `181612`), `-impl-4` (`211946`, STOP `222330`), `-impl-5` (`044638`, RETURN `062639`).
- Engine reach: parse-reach only — zero production callers of engine entrypoints (`git grep 'run_eligibility\|restore_entry\|repo::capture' -- src ':!src/core/repo'` empty at the candidate); verb-to-engine wiring is sub-step 2b behind R-4.48 + m-4's wiring bar.

## 2. Evidence chain (all at the exact SHA)

- Implementation return: `intg-substep2a/IMPL-pair-implementer-20260904-062639.md` (implementation complete; Step 0-quater → 4 → 4b → 5 → 6 → Task 4).
- Task-4 report of record: `results/intg-substep2a-task4-report-a2f6fd1.md` — TRACKED in this docs-lane commit as a byte-identical copy of the implementer's `.superpowers/sdd/PL-intg-substep2a-20260830/task-4-report.md`, sha256 **`7a4c9c96bb74f118e286e7ab029937d6f897fd8fd68cf9ad4c093f4cff2426b5`** (841 lines; re-hashed at assembly).
- Local suites, both platforms: macOS `ci-macos` configure/build 0; focused rows green (FX-O 803 assertions / 11 cases; FX-N 135 / 5; engine 452 / 60; E4 request trace 13 / 1); full `biv_tests` 16,343 assertions, 418 passed / 3 configured skips of 421. Ubuntu 24.04 amd64 four-phase parity instrument (`--platform linux/amd64 --init`, read-only mounts, pinned LLVM-22 assets `--strict` verified, suite uid 1001, `nofile` raised to the hard limit): configure 0, every-target `-Werror` build 0 (KEEP-GOING), the parity leg REACHED ctest; tidy row 0 with `clang-tidy coverage: 37 results == 37 sources`; hardening 0; E2 0; A6 0; Catch2 XML 0. Step-4b working-tree census (before the replacement commit): `missing_initializer_count=0`, `coverage_line_count=1`, `coverage_failure_count=0`, `tidy_rc=0`.
- Fences at the candidate (re-derived at the pair-planner's seat on 2026-09-04, `SITREP-pair-planner-20260904-135912.md`): ten-path census; six paths vs `9e6ebe8`, three vs `b09e192`; T-1 `manifest.hpp` 2/2 (the signature + `repos{}`); T-2 pack 5/2 · test_cli 3/1 · test_open 3/1 with zero `repos` lines; the `dot{}` line 1/1 vs the red tag; typed-error literal multiset byte-equal tag→HEAD; inventory 64 / 8 / 3; FX-O-INV 72 · CTRL 1 · FIELD 7 · LEG 6 · O-MUTANT 8 (+1 census marker) · NAMED MUTANT 9; C-1 exactly three sites; V-FA-6 empty; `src/cli`, `schemas/`, and the M surface byte-quiet; no `promisor`/`engine_source` key. Disclosed: `manifest.cpp` carries seven hunks vs the red tag mapping 1·1·3·1·1 to the four T-4 sites (the `:905` reference→pointer fold's three use sites) — graded within T-4 by m-1 (below).
- Owner byte review, m-1 (V-FA-1 as extended by `231935`, V-FA-2..8, O's cells, C-1..C-7, T-1..T-5, the (c)/(i)/(j) censuses, the label-correction target, the ondemand spelling): **APPROVE, NO FINDING** — `master/relays/intg-substep2a-format-act/DESIGN-REVIEW-planner-20260904-180655.md` (`DESIGN_REVIEW_VERDICT: approve`; `TARGET_DESIGN_COMMIT: a2f6fd1…`; every cell re-derived at m-1's bytes; WALKED on both platforms from a `git archive` of the exact sha — macOS Apple clang 17 16,343/16,343; Ubuntu 24.04 GCC 13.3.0 non-root uid 1001 every-target `-Werror` build 0, zero missing-initializer, 15,957/15,957; FOUR MUTANTS applied and KILLED where the plan said — M1 6 FX-O-INV arms, M2 the O-R1 mutant 7 arms, M3 exactly one presence oracle, M4 one shared clause removed → red at BOTH enforcement points; the seven-hunk map graded within T-4; the ondemand spelling no objection).
- Owner byte review, m-3 (C-6 window over the two test hunks): **APPROVE, GREEN, NO VETO** — `master/relays/intg-substep2a-format-act/DESIGN-planner-20260904-184740.md` (test_cli `:192` the move-deref right because the value is subsequently mutated; test_open `:131` the const-ref deref right because read-only and same-scope; C-2's shape met exactly; C-3's bound met; T-2 held; the one added assertion a strengthening; `src/cli`/`schemas` byte-quiet).
- Master's independent re-derivation at the candidate: `PLAN-master-planner-20260904-140627.md`; the carry naming both greens and this packet's shape: `PLAN-master-planner-20260904-185231.md`.
- Plan-review lineage: fifteen revisions; final APPROVE at exact `beba597c` (`intg-substep2a-plan-review-15`); W-5 EFFECTIVE at its frozen selector throughout, every revision's replacement root-mode measurement filed (rev15's: `results/lint-root-sweep-2a-rev15-verbose-tidy-20260903.txt` @ `2a10cad6`).

## 3. Registered residual reds — disclosed verbatim, with row attributions

**Neither red is cited as merge-readiness evidence anywhere in this packet.** Both ride disclosed under their registered rows; neither is converted to green; neither is waived. No remote-CI result is cited (unfunded; blocks nothing).

1. **R-4.35** (registered pre-existing flaky E3 scandir-stop/TOCTOU family; attributed to NO candidate; the detector-correctness half = R-4.36, m-4's row; the attribution series for the isolation landing ruled NOT SHIFTED at master `135906`). Linux `harness-selftest` rc nonzero at the candidate: `3 failed, 996 passed, 3 skipped` — the family's members, counts inside the registered range.
2. **R-4.38** (the single-binary count gate; owner m-3; the repair is THIS commission's count-gate act, plan rev3 @ `6eee9b30` approved `141141`, direction (a) transcription-last per master `135906`). Linux count-read rc 1 at the candidate: `observed 420/0/0/1 vs pinned 412/0/0/1` — the **+8** Catch2 cases tranche 2 adds, exactly the delta the count-gate act TRANSCRIBES after this landing. Never readiness evidence.

macOS raw-CTest observations (host-environment-keyed, mechanism files outside the candidate census): the ambient-credential tripwire in `harness-selftest` firing on a real host env var (focused reruns under `env -u` green); `harness-e2` = the closed R-4.37 class (the store-isolation remedy `85f9c4d6` is on `main`, not on this branch's base — cited, not re-diagnosed); `readelf` absent on macOS; ASan/UBSan/tidy/fuzz configured skips. Recorded, not candidate-attributed.

## 4. Blast radius (measured, not assumed; 2026-09-04 at the pair-planner's seat)

- `git merge-base main a2f6fd1` = `46df8f3` (the declared base).
- Branch delta: `git rev-list --count main..a2f6fd1` = 4 (the four commits of §1, nothing else).
- Local `main` has advanced **89** commits since the base (`git rev-list --count 46df8f3..main`): docs-lane relay/plan commits plus ONE harness landing, `85f9c4d6` (the E2 store-isolation act, four `harness/` paths). Product-path overlap between main's delta and the candidate's ten paths (`comm -12`): **NONE**.
- Trial merge: `git merge-tree --write-tree main a2f6fd1` rc 0 — **conflict-free**; predicted merged tree `8b26f8274b763abd94f28fc8a31630be60affb5f`. `main` is NOT an ancestor of the candidate → a true (non-ff) merge commit, parents `main-before` + `a2f6fd1`, exactly the sub-step-1 topology.
- **The merge publishes nothing.** `origin/main..main` = 787 commits already unpublished; the candidate's cut-point cell `rev-list --count origin/main..a2f6fd1^` = 701, `origin/main..a2f6fd1` = 702. The first push of local `main` is master's routed one-time named act AFTER the count-gate repair lands (R-4.51), never this lane's initiative; this merge does not move it.
- Post-merge identity check the landing MUST record: `git diff --stat a2f6fd1 <merge> -- src tests` EMPTY (the landed product bytes are the reviewed bytes; `main`'s only non-docs delta is `harness/`, disjoint).

## 5. Review record (the cells master named for this packet)

No pair-tier adversarial panel was run at 2a. The reviews of record at the exact sha are:

```text
owner byte review  m-1 DESIGN-REVIEW-planner-20260904-180655  APPROVE, NO FINDING — re-derived + WALKED both platforms + FOUR mutants killed
owner byte review  m-3 DESIGN-planner-20260904-184740          APPROVE, GREEN, NO VETO — C-6 window, both hunks read with context
independent        Task-3 specification + code-quality review at a2f6fd1: CLEAN (Step 6, the implementer's fresh reviewer)
independent        Task-4 report review (841 lines): CLEAN, no Critical/Important/Minor
master             PLAN-master-planner-20260904-140627: every fence re-derived at master's bytes
pair-planner       SITREP-pair-planner-20260904-135912: every mechanical fence re-run at this seat
```

Disclosed for master's decision: the sub-step-1 packet's condition 1 was a team-of-5 panel; master's `185231` shape for this packet names the two owner byte reviews (one of them executed with mutants) as the review cells and no panel. A pair-tier panel at the exact sha remains available on master's word before condition 4; any panel finding would produce a new sha and re-run both owner predicates.

## 6. The condition census (the four-condition bar, master's `185231` cells)

```text
cell 1  local suites GREEN on both platforms at the exact sha — DONE (§2: macOS 16,343 assertions / 418+3 of 421; Ubuntu every-target build 0, product rows green;
        m-1's independent walk 16,343 + 15,957 assertions)
cell 2  the Docker parity leg REACHED ctest (V-FA-8 as read by m-1 183510 T-3) — DONE (§2: build 0 at every target; ctest ran; only the two registered rows red)
cell 3  the two owner byte reviews at the exact sha — DONE (m-1 180655 approve no finding; m-3 184740 green no veto) — each verified at this seat by relay stamp,
        verdict line, and sha binding
cell 4  the operator's condition-4 merge token — PENDING; presented by master on this packet's return; issues as a BARE token to intg.pair-implementer
        (grantor set excludes the pair-planner — relay-lint.py:1170, measured at sub-step 1); nothing in this packet is or substitutes for it
visibility  master.master-reviewer, m-1.planner/implementer, m-3.planner/implementer, the operator CC'd on the packet relay (visibility, not approval)
condition 3 (R-4.30 recast)  master's own-bytes verification of head/base/merge-tree/delta/packet-face — master's act on this packet's return (140627 already re-derived the fences)
```

The release hold is ABSOLUTE and untouched by any of the above. Merged is not pushed, not published, not released.

## 7. Hold

Assembled and HELD. Cells 1–3 DONE and verified at this seat; the ONLY remaining gate is cell 4 — the operator's merge token, issued as a bare token to `intg.pair-implementer` on master's presentation of this packet. The pair does not merge; the pair-planner never runs a merge.

If the token issues: the merge is a LANE-LOCAL act on unpublished `main` (DEVIATIONS row 1) executed by the implementer per §4's recorded topology (true merge, parents `main-before` + `a2f6fd1`; predicted tree `8b26f827…` re-derived immediately before the merge; product-root diff candidate..merge EMPTY; both retained tags untouched; `origin/main` untouched), reported UP with post-merge receipts. THEN, in order and unchanged: the count-gate token issues (approve `141141` in hand; one-path SCOPE_DIFF; the run head postdates the landing) → observation transcribes the +8 → ONE workflow-only commit under the run-head guard → m-3's seven-point review → the FIRST PUSH as master's routed named act (R-4.51) → the R-4.50 route → R-4.49. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

## 8. Landed

(projection pending — written on the landing receipt)
