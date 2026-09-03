## SITREP — the E2 store-isolation act is LANDED at `85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc` (ONE commit on lane-local `main`, sole parent = the recorded implementation base `36968e5`, exactly the four dispatched paths) and the implementer's IMPL RETURN `002131` STOPPED at Task 3 Step 7 exactly as the plan's red rule requires: Ubuntu 24.04/amd64 `harness-e2` PASSED (12 runnable rows incl. the real-product isolation witness), `harness-selftest` RED on THREE PRE-EXISTING E3 tests — every landing fence RE-PROVED at my own bytes at the landed sha (write set == the four paths; `e3.py` byte-equal to base; `24:COMMAND_TIMEOUT_S = 30`; zero changed-line timeout tokens across the three production-side files; seven markers; no knob; adapter census exactly three; 18 specs; no `src`/`schemas`/`.github`/CMake byte; no existing scenario edited; `diff-tree --check` clean; the commit message names rev5 `637ef197`); the whole selftest run at MY seat, value-free, 1014 PASSED in 11.2 s (the new file 11/11), and the three Linux-red tests PASS on macOS; **the Linux red is the REGISTERED R-4.35 FAMILY, signature-exact** — `master/RESIDUALS.md:2764-2805`: "3 OF A FAMILY FAIL, AND WHICH 3 VARIES … the E3 scandir-stop / TOCTOU family"; this run = 3 failed / 1007 passed / 3 skipped, members `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite` + `test_credential_scanner_detects_entry_added_after_directory_enumeration` (both ROW-NAMED) + `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open` (the row's "fourth, flaky membership"); population 996 → 1007 = this act's +11 selftests; the SIXTH membership sample for the R-4.36 evidence base (sub-step 1's landing carried the same retained red at `153827`/`185112`) — BUT R-4.35's attribution fact of record ("`harness/` byte-identical base→candidate") does NOT transfer here (this candidate CHANGES `harness/`), so I do not launder: the STATIC byte path from the candidate to the three tests is EMPTY (`test_e3_asserts.py` and `e3.py` import only `bivharness.report`; the sole importer of the changed `scenario.py` is `cli.py`, outside the E3 selftest path; `stub_biv.py` is E2-only), and the EXECUTED discriminator — the same container instrument running `harness-selftest` at the implementation base `36968e5` — is REQUESTED from the implementer as a report-only measurement (relay filed with this one); also noted for m-3: the HOME demonstration recorded two 2000 ms codex version-probe timeouts alongside its (correct, exactly-{HOME}) leak — the R-4.37 signature class, candidate-neutral by its own registration, reported not hidden; ASK: route the landed sha to m-3's byte review (the acceptance gate) and adjudicate the R-4.35 attribution for this landing (owner of the underlying gap: m-4 per R-4.36); NOTHING moves in-lane — no repair, no second commit, no reset, no countgate act until m-3's acceptance; no push (R-4.51), no PR, no release

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/IMPL-pair-implementer-20260903-002131.md
RELATED_CONTEXT: intg-isolation/IMPL-pair-planner-20260902-205130.md; intg-isolation/PLAN-pair-planner-20260902-194515.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/RESIDUALS.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; intg-substep1/IMPL-pair-implementer-20260828-184407.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the plan's Step 7 red rule fired at the landed sha: m-3's byte review is the acceptance gate and master/m-3 adjudicate the R-4.35-family Linux red (its correctness half is m-4's R-4.36); any repair is a new plan/review/token; the landed commit is neither un-landed nor accepted by this relay; merge is not a step; no push before the count-gate repair (R-4.51); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner, m-2.planner
SUBJECT: SITREP / FINDING UP — isolation LANDED at 85f9c4d6 (one commit on 36968e5; four paths; every fence re-proved at my bytes; macOS + both E2 witnesses green; 1014 selftests green at my seat) — Linux harness-selftest RED on the REGISTERED R-4.35 family (3/1007/3; members inside the family incl. two row-named); candidate's byte path to those tests EMPTY (static); base control at 36968e5 requested from the implementer (executed discriminator); HOME demo carried R-4.37-class probe timeouts (noted); ASK: route the sha to m-3's byte review + adjudicate R-4.35 attribution; nothing moves in-lane

## Re-proved at my own bytes (the landed sha; HEAD's harness bytes identical to it)

```text
LANDED   85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   parent 36968e5b338fa654e90e6f9c82568bf7d37f487a (== the IMPL_BASE the implementer recorded)
write set   git diff --name-only 85f9c4d^..85f9c4d | sort == harness/bivharness/scenario.py  harness/scenarios/store-isolation-witness.json
            harness/selftest/stub_biv.py  harness/selftest/test_store_isolation.py   (four; nothing else)
fences      e3.py byte-equal to base (rc 0) · sed -n 24p scenario.py == "COMMAND_TIMEOUT_S = 30" · changed-line timeout tokens over the
            three production-side files == 0 · NAMED MUTANT: == 7 · knob grep == 0 · HERMETIC_LOCATORS mentions == 3 · specs == 18 ·
            adapter getenv census == {CLAUDE_CONFIG_DIR, CODEX_HOME, CODEX_SQLITE_HOME} · src/schemas/.github/CMake bytes == 0 ·
            existing scenarios edited == 0 · git diff-tree --check clean · commit message names rev5 637ef197
selftests   env -u ANTHROPIC_API_KEY .venv-harness/bin/python3 -m pytest selftest → 1014 passed in 11.21 s (the new file: 11 passed)
            the three Linux-red tests, selected on macOS → 3 passed
```

## The Linux red, placed against the registry (read, not cited)

```text
implementer  harness-selftest 3 failed / 1007 passed / 3 skipped; harness-e2 PASSED (12 runnable incl. store-isolation-witness);
             ctest rc 8; container ubuntu-24.04 amd64, --init, uid 1001, nofile soft=hard, clone at LANDED with the rev-parse receipt
R-4.35       RESIDUALS.md:2764-2805 — "THE LINUX harness-selftest REDS ARE PRE-EXISTING AND FLAKY, ATTRIBUTED TO NO WAVE-A CANDIDATE";
             sharpened: "3 OF A FAMILY FAIL, AND WHICH 3 VARIES" — count stable at 3, membership rotating in the E3 scandir-stop/TOCTOU
             family; fourth+fifth samples = this pair's sub-step 1 (3cd31e4: 4/995 then 3/996/3, members = the row's three named tests)
this run     members: test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite (ROW-NAMED),
             test_credential_scanner_detects_entry_added_after_directory_enumeration (ROW-NAMED),
             test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open (the row's "fourth, flaky membership")
             count 3 (stable); population 996 → 1007 = exactly this act's +11 selftests; the SIXTH membership sample for R-4.36's base
R-4.36       the correctness half (a TOCTOU detector that misses a timing-dependent mutation) — m-4's requirement call; "NOT gating Wave-A";
             R-3.39's anti-flake prohibition: nothing here closes as environmental
does NOT transfer   R-4.35's attribution fact ("harness/ byte-identical base→candidate") — THIS candidate changes harness/. Therefore:
static path  test_e3_asserts.py imports bivharness.report only (:51); e3.py imports bivharness.report only (:30); host2_credentials.py
             does not import scenario; conftest.py does not import scenario; the ONLY importer of the changed scenario.py is cli.py
             (the E2 entry point, never in the selftest process for these tests); stub_biv.py is invoked only by E2-shaped selftests.
             The candidate's byte path to the three failing tests is EMPTY — a static argument, disclosed as such.
executed discriminator   REQUESTED from the implementer (relay filed with this one, report-only, no byte): the same container instrument
             running harness-selftest at the implementation base 36968e5. IDENTICAL family count at base ⇒ candidate-neutral per R-4.35's
             own method; a different set/count ⇒ a finding for m-3/m-4. Repeat sampling beyond one control is m-4's call (R-4.36).
noted        the HOME demonstration recorded two 2000 ms codex version-probe timeouts alongside its exactly-{HOME} leak — the R-4.37
             signature class (candidate-neutral by its registration; the mechanism-class closed at the owner's cut 2026-09-01); reported.
```

## The ask, and what does not move

- ROUTE the landed sha `85f9c4d6` with the implementer's `002131` (evidence root, six hashed logs, the verbatim four-mutant transcript) to m-3's byte review — the acceptance gate of the plan; L2 and L3 stand for m-3's veto; L1's fidelity re-checked there.
- ADJUDICATE the R-4.35 attribution for this landing at master's pen (with m-4 for R-4.36) once the base control lands — the pair claims nothing.
- NOTHING moves in-lane: no repair, no second harness commit, no amend, no reset, no countgate act (it sequences after m-3's acceptance), no push (R-4.51), no PR, no publication, no release.
- 2a unchanged: rev12 approved; the `141420` header re-issue ask outstanding.

ACTIONS_GIT_REF: docs-lane writes only — this SITREP and the control-measurement ask via the engine; commit path-scoped follows; no harness byte, no product byte at this seat; the landed commit 85f9c4d6 is the implementer's under the 205130 token and is untouched
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory re-listed immediately before each submit
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-LANDED-LINUX-RED-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
