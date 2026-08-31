# Count-gate repair (R-4.38 + R-3.37) — implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:executing-plans, task-by-task, steps as checkboxes.

**Goal:** Execute `m3-countgate-repair-20260830` rev1 at exact pin `0099d1cf…` verbatim — the five-binary per-target observed count gates land in `.github/workflows/s2-harness.yml` in ONE commit on local main, with the macOS allowlist inverted and `expected_skips` membership untouched.

**Architecture:** Observation-then-transcription. Nothing is derived: every gate cell is transcribed from an observed run of its own binary on its own target at the stated run head. The fail-closed CG-R5 preflight (linkage-based inventory census) runs before any observation or commit.

**Sealed input (execution-not-amendment; defer-or-silence → STOP UP, m-3 owns the answer):** `pdc:master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md` @ sha256 `0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875` (commit `9763658e…`; live file re-hashed EQUAL at plan authoring) — CG-R1..CG-R6, V-CG-1..5, the seven-point m-3 byte review. The Master Reviewer's binding CG-R5 clarification rides: the inventory is the repo-wide executable set LINKED TO `Catch2::Catch2WithMain` (a raw `add_executable`-minus-fuzz census does NOT satisfy it).

**Baseline pre-verified at plan authoring (main@46df8f3, product == 81066ef):** exactly five `Catch2WithMain`-linked executables (`CMakeLists.txt` link sites :105/:118/:125/:161/:173 for `biv_subprocess_tests`/`biv_repo_git_tests`/`biv_repo_engine_tests`/`biv_tests`/`biv_probe_tests`); fuzz targets :242/:249 outside; declaration counts 12/6/56 confirmed for the three omitted binaries; the `:53` macOS `-R` include allowlist confirmed; the macOS count step reads only `biv_tests -r xml` today. These are plan-time facts — CG-R5's preflight RE-DERIVES the inventory at the actual run head and STOPs on any drift.

## Global constraints

1. **Single path** (CG-R6.1/V-CG-4): the landing commit touches `.github/workflows/s2-harness.yml` and NOTHING else.
2. **ONE commit on local main** (CG-R6.2) — no branch, no merge commit; the commit lands at the implementer's seat under this lane's token.
3. **Observed-not-derived** (CG-R2/V-CG-2): every want cell equals an observed run output of that binary on that target; summed/derived cells rejected; 413-conservation is diagnosis, never source.
4. **`expected_skips` membership byte-identical** (CG-R4/V-CG-5): any observed membership change = FINDING routed UP through the pair line to m-3.planner — never adjusted.
5. **Fail-closed preflight** (CG-R5/V-CG-3): the linkage census at the run head vs the approved five, BEFORE observation and BEFORE commit; any added/removed/renamed binary = STOP UP; the enumerated inventory rides the landing commit.
6. **Run provenance** (CG-R2): runs POSTDATE the intg merge; the execution head is stated in the commit with `81066ef` an ancestor; run identities (platform, container recipe, run ids) in the commit.
7. **No push/publication/release** (CG-R6.4): the repair is the PRECONDITION of any push; R-4.46 stays operator-gated; the release hold is ABSOLUTE. No remote CI ever (unfunded, no signal, never cited).
8. STOP routing: pair-implementer → pair-planner → master → m-3.

**SEQUENCING (this lane's delegated judgment, stated per the route; reversible by master):** this plan proceeds to review NOW in parallel with 2a; the OBSERVATION+LANDING execute at a local-main head that POSTDATES the 2a format-act merge (if 2a lands) or at the then-current head if master directs earlier. Grounds: the transcription-last ordering master recorded on the R-4.38 row ("observed-runs-at-merged-bytes sees the +N exactly once") — transcribing before the in-flight 2a merge would guarantee immediate cell staleness and a fresh red of the very class this repair discharges. Nothing is push-blocked by the wait: no push can occur before BOTH this repair lands AND R-4.46 opens.

---

### Task 1 — CG-R5 preflight + both-target observation runs (no repository mutation)

- [ ] **Step 1: state the run head** — `RUN_HEAD=$(git rev-parse main)`; verify `git merge-base --is-ancestor 81066ef "$RUN_HEAD"` rc 0; record both.
- [ ] **Step 2: the linkage-census preflight** — `grep -n 'Catch2::Catch2WithMain' CMakeLists.txt` at the run head; map each hit to its `add_executable` target; REQUIRE the set == exactly {biv_subprocess_tests, biv_repo_git_tests, biv_repo_engine_tests, biv_tests, biv_probe_tests}; ANY difference → STOP UP (V-CG-3), no observation, no commit. Retain the enumerated inventory verbatim for the commit.
- [ ] **Step 3: macOS observation** — `cmake --preset ci-macos && cmake --build --preset ci-macos`; for EACH of the five: `./build/ci-macos/<binary> -r xml > <binary>-macos.xml` and extract `successes/failures/expectedFailures/skips` + the skipped-test NAME SET; verify the biv_tests skipped-name set is byte-identical to the workflow's current `expected_skips` (CG-R4; a difference = FINDING, STOP UP). Also run the inverted-selection scout: `ctest --preset ci-macos --output-on-failure` WITHOUT `-R` to enumerate which rows red for platform-instrument reasons (e.g. the ELF-only hardening row's `readelf` absence) — the explicit `-E` exclusion candidates, each justified; any red NOT explainable as a platform-instrument absence = FINDING, STOP UP.
- [ ] **Step 4: Linux observation** — the proven four-phase container instrument (the rev12 text at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3: Phase H host transport, Phase R frozen base command incl. openssh-client + deb provisioning, Phase T pinned uid 1001 + `/repo-ro` clone of main at the RUN HEAD with the rev-parse receipt, Phase S nofile raise + venv + configure/build), with Phase S's measurement stage = the five `-r xml` runs + the same tuple/skip extraction; per-stage rc ledger retained; the frozen-command fail-closed rule rides unchanged.
- [ ] **Step 5: transcription table** — one table, ten cells (five binaries × two targets), each cell the observed 4-tuple with its run id; NO arithmetic anywhere.

### Task 2 — the workflow rewrite and THE ONE COMMIT on local main

- [ ] **Step 1: edit `.github/workflows/s2-harness.yml` ONLY** —
  - macOS job: replace the `:53` `-R` include with the inverted form (run everything; explicit `-E '<row>|<row>'` listing exactly the Task-1-justified platform exclusions; if the set is empty, NO filter flag); replace the single-binary count step with five per-binary steps/blocks, each running its binary `-r xml` and enforcing exact equality against ITS observed macOS cell; `expected_skips` block byte-identical.
  - Linux job: the same five per-binary exact-equality blocks against the observed Linux cells (the existing `:272` biv_tests block becomes one of five); selection semantics identical to macOS's inverted form; `expected_skips` byte-identical.
  - Every want literal traceable to Task 1's table; no summed or derived number anywhere (V-CG-2).
- [ ] **Step 2: verify the diff** — `git diff --name-only` = exactly the workflow file; `git diff` read whole against the design's cells.
- [ ] **Step 3: local gate self-check** — re-run each new count check against the Task-1 XML artifacts (the transcription validates against its own source run: must be green by construction; a red = transcription defect, fix before commit).
- [ ] **Step 4: THE commit on local main** — message carries: the stated run head + the 81066ef-ancestor fact, the preflight inventory, all ten run identities (platform/container recipe/run ids), and the design pin. `git show --stat` retained as evidence.

### Task 3 — evidence + IMPL report

- [ ] Fence transcript: single-path proof (`git show --name-only HEAD` = the workflow only); the preflight evidence; the ten observed cells + XML artifacts; the `-E` exclusion justifications; the skips-identity proof; the ledger from the container run.
- [ ] The partitioned IMPL report at the landed sha, routed UP for m-3.planner's SEVEN-POINT byte review (CG-R6.3 (i)–(vii)) via master — m-3 holds the veto (V-CG-1..5). No push, no release; explicit NOT-DONE list.

## Acceptance criteria

1. The landing is ONE commit on local main touching only `.github/workflows/s2-harness.yml`, at a stated run head with `81066ef` an ancestor.
2. Ten observed cells (five binaries × two targets), each byte-traceable to its own run artifact; no derived number.
3. The macOS include-allowlist is gone; exclusions explicit-or-absent; selection semantics identical across the two jobs.
4. `expected_skips` membership byte-identical; the preflight inventory equals the approved five and rides the commit.
5. The new gates green against their own source runs; m-3's seven points each satisfiable at the landed bytes.

## Out of scope (hard)

Any byte outside the workflow file; any product/test/CMake/schema/harness change; any Catch2 skip-membership adjustment; remote CI; push/PR/publication/deployment/seal/release; the 2a lane's surfaces (parallel and untouched).

## Identity, coverage, and gates

- Plan identity: dispatch `intg-countgate-plan`, `DESIGN_DOC_ID: intg-countgate-plan`, this artifact. W-3 is ALREADY TERMINATED (at the 2a plan's filing, disclosed); this plan's design-lineage red for `m3-countgate-repair-20260830` is EXPECTED and UNCOVERED until master establishes coverage (`intg-countgate-plan → m3-countgate-repair-20260830 @ 0099d1cf`); **no implementation dispatch until that coverage stands.**
- The token: this lane's delegated conditional machinery (exact-hash PLAN-REVIEW approve → coverage → the bare token; handoff-to-be `intg-countgate-impl`).
- Acceptance gate: m-3.planner's seven-point byte review at the landed sha (the veto's home). Push stays behind this repair + R-4.46; the release hold is ABSOLUTE.
