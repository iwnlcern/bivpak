## SITREP — c4a STOPped on an UNTOUCHED probe fixture (implementer 171145): the final credential-clean floor at the ten-path candidate went red on `tests/test_probe.cpp:671` (`version probe preserves clean exit while disposing a pipe-holding grandchild`, `REQUIRE(ledger_child > 0)` saw `-1`) with every other test green (full `biv_tests` 443/3; probe suite 24/25); the case is byte-identical at B and touched last on 2026-08-07; the registry has no row for it; my host scout could not reproduce it (isolation ×20, CPU-saturated ×20, all green). Dispositioned at my seat (173140): D1/D2 classification runs at the unchanged candidate binary, then ONE fresh floor iff D1 is 20/20; a D1 red or a second red floor STOPs again. Asked of master: register the observation as a residual candidate (fixture real-time budget: 200 × 5 ms marker poll around a 50 ms shell fixture) and name its owner; no gate on c4a beyond the plan's own green floor; no ask of m-x. Separately, the carry (162750) still stands as the other hold on c4a's commit.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/IMPL-pair-implementer-20260919-171145.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260919-173140.md; intg-substep2b/SITREP-pair-planner-20260919-162750.md; intg-substep2b/IMPL-pair-planner-20260919-162507.md; ../../pdc/master/RESIDUALS.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a STOP report and a residual candidate for master's registry; the disposition is inside Task 4 Step 4 under the live token; no plan byte moves; no product byte at this seat; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — c4a floor red on the untouched probe fixture test_probe.cpp:671 (single observation; not reproduced at this seat ×40); dispositioned D1/D2 + one fresh floor (173140); residual candidate for the registry with an owner to name; the carry still awaited
REPO: `../bivpak` docs lane — this relay and the disposition 173140 (6938fcd, path-scoped, no trailer), RECONCILE §R25 + a roadmap row; product bytes untouched at this seat; the candidate untouched at 13ec732 + ten unstaged paths (the implementer's 171145). Host scout read-only on the 2026-09-04 host test binary. `../pdc` untouched (HEAD b8c29807 re-read; nothing newer than 155534).
BRIDGE: intg.pair-planner → master.master-planner (the observation; the residual candidate; the owner question); implementer CC (the disposition is at 173140); m-1 / m-3 / m-4 CC (nothing asked; the probe suite's owner is master's to name); operator CC (no push, no PR, no merge, no release; the hold stands)

## The observation, with what is and is not established

- The red: `env -u ANTHROPIC_API_KEY ctest --preset ci-macos -E '^safety-hardening$'` at the ten-path c4a candidate (after the A9.4 header fix the implementer's independent review approved) — rc 8, 14 passed / 1 failed / 3 skipped; the one failure `probe` at `tests/test_probe.cpp:671`; `harness-selftest` green (not the credential scanner). Receipts in the evidence home: `code/c4a-fix1-ctest-credential-clean.log`, `code/c4a-fix1-ctest-probe-red-LastTest.log`.
- The case: origin 2537eb6, last touched d87d83a (2026-08-07); byte-identical at B and at the candidate; `biv_probe_tests` compiles only `tests/test_probe.cpp` and exercises `biv_support`'s `run_version_probe`, which no c4a path touches. The fixture script sleeps 50 ms, forks a background grandchild, writes its PID to a marker and exits; the injected waiter polls the marker for at most 200 × 5 ms of real time; `ledger_child` stays `-1` if the marker is not readable in that window. The floor ran serially (no `-j`; the preset has no `execution.jobs`); the probe suite took 12.28 s against 10.56 s in the c3-era green floor.
- The registry: no row names the case, `ledger_child` or the grandchild fixture; R-4.40 (Linux no-init zombie retention) does not describe this macOS observation.
- At this seat (read-only, the host build at B): the case ×20 in isolation → 20 pass; ×20 under 2× core-count `yes` load → 20 pass. NOT established: the mechanism of the one red. No cause is asserted; the disposition measures.

## The disposition (173140) in one paragraph

D0 pins the candidate (write set == the ten paths; `git diff HEAD` digest; the probe binary's digest — no rebuild). D1 runs the exact case ×20 in isolation at that binary; D2 ×20 under CPU load; every run's log kept, the failing-assertion inventory written. Rule: D1 `fail=0` → classified OBSERVED-NOT-REPRODUCED-IN-ISOLATION, D2's count the supporting datum → D3, ONE fresh complete credential-clean floor at the unchanged candidate (diff digest re-taken and compared; rc 0 is Step 4's final-byte evidence; a red second floor STOPs with no third run). D1 `fail>=1`, or any assertion other than `:671`/`:672` → STOP to me, no D3. Every block was walked at this seat before filing (D0 against the candidate worktree into a scratch home; D1/D2 shortened; D3's four branches with the floor stubbed — red floor, green floor, unclean D1, changed candidate — each separating; D2's load-process cleanup verified after my first draft leaked them).

## Asked of master

1. Register the observation as a residual candidate in `master/RESIDUALS.md` (this seat proposes the row text: "`tests/test_probe.cpp:580` `version probe preserves clean exit while disposing a pipe-holding grandchild` — one red on macOS 2026-09-19 17:00 at an unrelated candidate, `REQUIRE(ledger_child > 0)` saw -1: the marker written by a 50 ms shell fixture was not readable inside the waiter's 200 × 5 ms real-time poll; not reproduced ×40 at the pair Planner's seat (isolation, CPU load); D1/D2 counts at the candidate binary to follow") and name the probe suite's owner for any fixture-budget change — the pair proposes none and edits nothing there.
2. Confirm, or correct, that a green D3 floor at the unchanged candidate is Task 4 Step 4's completion evidence under the plan (the plan's Step 4 states `ctest … rc 0` and no re-run rule; the disposition adds no gate beyond one bounded re-run after a classification that the implementer refused to make unilaterally — correctly).
3. The T-ORACLE carry (162750) remains the other hold on c4a's commit; nothing about it changes here.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), RECONCILE §R25 + a roadmap row, no trailer; the disposition 173140 committed 6938fcd; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written; every newer upstream file opened before this submit (listing run as its own command: none newer than 155534).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
