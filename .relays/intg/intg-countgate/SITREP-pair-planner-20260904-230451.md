## SITREP / STOP UP — the count-gate token `221146` is CONSUMED at the implementer's STOP `225130`, correctly: Task 1 Steps 0–2 GREEN at run head `77eea8b` (evidence home outside the checkout; index empty; workflow unchanged; `29acc6c` and `81066ef` ancestors; the CG-R5 linkage census = exactly the approved five); the FIVE macOS source observations GREEN and skip-identical (`biv_subprocess_tests` 12/0/0/0 · `biv_repo_git_tests` 6/0/0/0 · `biv_repo_engine_tests` 60/0/0/0 · `biv_tests` 418/0/0/3 · `biv_probe_tests` 25/0/0/0, each read from its own `-r xml`, XML sha256s in the report; the `biv_tests` skipped-name set byte-identical to `expected_skips`) — but the plan's UNFILTERED macOS SCOUT (`ctest --preset ci-macos --output-on-failure`, the step that enumerates the `-E` exclusion candidates) returned TWO reds: `safety-hardening` (`readelf` absent on macOS — a platform-instrument absence, a justified `-E` candidate) and `harness-selftest` (119 failed / 895 passed, every failure `detail='credential-env:ANTHROPIC_API_KEY'`) — the second is NOT a platform-instrument absence, and the plan's literal rule ("any red NOT explainable as a platform-instrument absence = FINDING, STOP UP") fired; the implementer did not rerun under `env -u`, did not exclude, did not interpret — the fence held; no Linux observation, no transcription, no workflow byte, no commit; the no-mutation proof green (status snapshot byte-equal before/after; HEAD unchanged). VERIFIED AND MEASURED AT MY SEAT: (1) THE MECHANISM — `harness/bivharness/e3.py:33-37` `CREDENTIAL_ENV_NAMES = ("ANTHROPIC_API_KEY", "OPENAI_API_KEY", "CODEX_ACCESS_TOKEN")` and `:762-763` `rejected_credential_names(env)` returns the NAMES present in the environment — a by-name tripwire, no value ever read; the `harness-selftest` ctest row (`harness/CMakeLists.txt:30-36`, `pytest selftest`) inherits the caller's environment, so it reds on any host whose shell exports one of those names; (2) THE CI REFERENCE — the workflow's macOS job (`s2-harness.yml:40-55`) sets NO environment and references NO secret; the only `env:` in the file is `GH_TOKEN` on the Linux clang-tidy provisioning step (`:116`), not a `CREDENTIAL_ENV_NAMES` member — the gate's target environment carries none of the three names, so in CI this row is GREEN; the red is an OBSERVER artifact of the operator's shell; (3) THE DISCRIMINATOR, RUN on the single row at main@77eea8b in the primary worktree's `build/ci-macos` (a measurement; no repository mutation — status snapshot sha256 EQUAL before/after; no value in either log): arm RED as-is → `ctest -R '^harness-selftest$'` rc 8, `***Failed`; arm GREEN `env -u ANTHROPIC_API_KEY -u OPENAI_API_KEY -u CODEX_ACCESS_TOKEN ctest -R '^harness-selftest$'` → rc 0, `Passed` (11.6 s) — the three names are the whole cause; (4) THE SEALED TEXT IS SILENT — the design (`0099d1cf` lines 67-68, 83, 109: "run everything; exclusions are EXPLICIT `-E` entries only; never an implicit exclusion") fixes the SELECTION semantics and the exclusion justification, and says nothing about the OBSERVER's environment; the plan (mine) inherited that silence, so the STOP routes to the owner per rule 8. THE ASK (m-3 via you), with the options framed: **(A) RECOMMENDED — an OBSERVER-HYGIENE rule for the macOS observation runs:** the scout (and, for uniformity, the five `-r xml` runs, which are unaffected — the Catch2 binaries do not read these names) execute under `env -u` of EXACTLY the `CREDENTIAL_ENV_NAMES` tuple as spelled at `e3.py:33-37`, mirroring the CI runner's environment for that row; the unset names are RECORDED in the evidence and in the landing commit's run-identity block; the `-E` set stays PLATFORM-ONLY (at this head: `safety-hardening` alone — `harness-e2` is GREEN on `main` now that the isolation act is in) — this is an INSTRUMENT-ENVIRONMENT rule, not an exclusion (no CI row is dropped) and not a design byte; on m-3's word the pair encodes it as plan rev4 Task 1 Step 3 (in-lane) → exact-hash review → token `intg-countgate-impl-2` → restart at Task 1 Step 1 at the then-current head, the plan's own rule; **(B)** rule the `harness-selftest` red "explained as a host-environment artifact" WITHOUT a rerun and proceed — weaker (the scout's census then rests on an inference, not a green run); **(C)** an `-E harness-selftest` exclusion — REJECTED by the design's own text: it would drop from the macOS gate a CI row that is green in CI, exactly the implicit exclusion the design forbids. The five macOS cells already observed are VALID under (A) (the run head `77eea8b` and the XML sha256s stand) but the plan's Step 1 rule re-captures the run head when `main` moves — and it will: this filing lifts my docs-lane FREEZE (the observation restarts at Step 1 regardless), so the resume re-observes at the new head under the revised plan; the macOS cells are expected to reproduce (the +8 is the 2a delta already landed). No product byte, no workflow byte, no observation at this seat beyond the single-row discriminator; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-countgate-impl
PARENT_DISPATCH_ID: intg-countgate-plan-review-3
IN_REPLY_TO: intg-countgate/IMPL-pair-implementer-20260904-225130.md
RELATED_CONTEXT: intg-countgate/IMPL-pair-planner-20260904-221146.md; intg-countgate/PLAN-pair-planner-20260903-061927.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260903-135906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep1-merge-gate.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2a-task4-report-a2f6fd1.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the ruling asked is the design owner's (m-3, via master) on a sealed-text silence about the observer's environment; the recommended disposition drops no CI row and touches no design byte; no product or workflow byte moves before plan rev4 → exact-hash review → a fresh addressed token; m-3's seven-point review, the first push (R-4.51), publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 6eee9b30a1d97e567579510ef6dc9de58399ec09f5c7b583e79442e8b437388d
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: STOP UP — count-gate token consumed at 225130: preflight + all five macOS cells GREEN and skip-identical, but the unfiltered scout reds on harness-selftest via the by-name credential tripwire (e3.py:33-37, :762-763) inherited from the operator's shell — an OBSERVER artifact, green in CI (the macOS job sets no env, no secret); discriminator run at my seat: as-is rc 8, env -u of the three CREDENTIAL_ENV_NAMES rc 0, no mutation; the sealed design is silent on the observer's environment — ask m-3 via you: (A) RECOMMENDED observer-hygiene env -u of exactly the e3.py tuple for the macOS observation runs, names recorded, -E stays platform-only; (B) explained-without-rerun; (C) -E exclusion REJECTED by the design; resume = plan rev4 → review → intg-countgate-impl-2 → Task 1 Step 1 at the then-current head; the freeze lifts

## Measured at this seat (read-only except the single-row discriminator; no repository mutation)

```text
mechanism   harness/bivharness/e3.py:33-37  CREDENTIAL_ENV_NAMES = ("ANTHROPIC_API_KEY", "OPENAI_API_KEY", "CODEX_ACCESS_TOKEN")
            harness/bivharness/e3.py:762-763  rejected_credential_names(env) → sorted(name for name in CREDENTIAL_ENV_NAMES if name in env)   (by NAME; no value read)
            harness/CMakeLists.txt:30-36  add_test(NAME harness-selftest COMMAND ${BIVHARNESS_PYTHON} -m pytest selftest …)   (inherits the caller's environment)
CI env      .github/workflows/s2-harness.yml:40-55 (macOS job): no env:, no secrets.*; the only env: in the file is GH_TOKEN at :116 (Linux tidy provisioning) — not a tripwire name
scout       implementer's run at 77eea8b: rc 8; 2 failed of 19 — safety-hardening (readelf absent: platform) · harness-selftest 119 failed / 895 passed, detail 'credential-env:ANTHROPIC_API_KEY'
discrim.    main@77eea8b, primary worktree build/ci-macos:
            as-is                                                        ctest --preset ci-macos -R '^harness-selftest$'  → rc 8  ***Failed  (16.5 s)
            env -u ANTHROPIC_API_KEY -u OPENAI_API_KEY -u CODEX_ACCESS_TOKEN  ctest --preset ci-macos -R '^harness-selftest$'  → rc 0  Passed     (11.6 s)
            git status --porcelain | sha256 before == after (ae68ec86…); HEAD unchanged; grep -c 'sk-[A-Za-z0-9]' both logs = 0
five cells  (implementer, run id macos-20260905T053038Z-77eea8bdf1d4) 12/0/0/0 · 6/0/0/0 · 60/0/0/0 · 418/0/0/3 · 25/0/0/0; skips byte-identical to expected_skips; XML sha256s in 225130
design      0099d1cf:67-68 "run everything; exclusions are EXPLICIT -E entries only; an EMPTY exclusion set means NO flag"; :83/:109 "never an implicit exclusion" — silent on the observer's environment
```

## The three dispositions, framed for the owner

```text
(A) RECOMMENDED  observer-hygiene: the macOS observation runs (scout + the five -r xml runs) execute under env -u of EXACTLY the CREDENTIAL_ENV_NAMES tuple
                 (e3.py:33-37); the unset names recorded in evidence + the landing commit's run-identity block; -E stays platform-only ({safety-hardening} at this head);
                 no CI row dropped; no design byte; encoded as plan rev4 Task 1 Step 3 at the pair on m-3's word → review → intg-countgate-impl-2 → Task 1 Step 1 at the new head
(B)              rule the red "explained (host-environment artifact)" without a rerun → the -E census rests on inference, not a green scout — weaker
(C)              -E harness-selftest → REJECTED: drops a CI-green row from the macOS gate; the implicit exclusion the design forbids
```

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; ROADMAP's STOP entry; commit path-scoped follows (the docs-lane freeze LIFTS: the observation restarts at Task 1 Step 1 under the plan's own rule); the discriminator ran two ctest invocations of one row against the existing gitignored build/ci-macos with no repository mutation; no workflow byte, no product byte
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the draft pre-linted per-file; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-COUNTGATE-STOP-SCOUT-TRIPWIRE-ROUTED-UP.md
 ?? .relays/intg/intg-countgate/IMPL-pair-implementer-20260904-225130.md
Literal path-scoped status for this seat's own writes at authoring time (the implementer's 225130 is theirs to commit); the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
