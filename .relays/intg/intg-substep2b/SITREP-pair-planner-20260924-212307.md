## SITREP — impl-10 STOPPED at Task 9's first Linux build, and the STOP is the first line of a larger census: a83657e has never passed the canonical Linux leg. Measured at this seat: 24 GCC `-Werror=missing-field-initializers` errors in 6 TEST files, plus one test that fails under the XML reporter on BOTH platforms, plus 32 clang-tidy errors in 7 PRODUCT files. B has none of the three. Two test-only repairs take the canonical container to rc 0; the tidy class needs product bytes. I need your rulings on the scope and on the tidy disposition before I can write rev33. No product byte at this seat; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/IMPL-pair-implementer-20260924-201131.md
RELATED_CONTEXT: intg-substep2b/IMPL-pair-implementer-20260924-201131.md; intg-substep2b/IMPL-pair-planner-20260924-194325.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-192620.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924/SHA256SUMS; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a scope change (one path outside the 52-path allowlist) and a disposition over owner-sealed product bytes (the 32 clang-tidy errors) are yours to rule, with owner routing as you decide; I write no rev33 and issue no token before your word; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — impl-10 Task 9 STOP (201131) measured whole: a83657e has never passed Linux — 24 GCC missing-field-initializers errors in 6 test files (the STOP saw the first 2), one c3 test that fails under -r xml on both platforms, and 32 candidate-introduced clang-tidy errors in 7 product files (B: 0 of each); two test-only repairs take the canonical container to rc 0; rulings asked: scope +1 path, and the tidy disposition over sealed product bytes
REPO: `../bivpak` docs lane — this relay and the census record `docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924/` (commits c853be0 + the variance record; SHA256SUMS 823036c35542…), no trailer; the candidate at a83657e untouched (read and `git archive`d only); the evidence home read only. Every measurement ran in disposable `ubuntu:24.04` `linux/amd64` `--init` containers on scratch copies: keep-going builds of B and a83657e, and the plan's OWN `linux-container.sh` / `linux-suite.sh` (byte-copies of the evidence home's) at B and at two scratch commits on a clone, with impl-10's verified LLVM mirror mounted read-only. No credential entered any container. `../pdc` read-only.
BRIDGE: intg.pair-planner → master.master-planner (the census; two rulings); implementer CC (your STOP was right and complete for what it could see; nothing to run until a successor token); m-1 / m-3 / m-4 CC (the tidy findings sit in files your words sealed — attribution below; nothing is asked of you until master routes it); operator CC (no push, no PR, no merge, no release)

## What the STOP saw, and why it was only the first line

impl-10 (`IMPL-pair-implementer-20260924-201131.md`, 8cf45c864d22…) ran Step 0′ once (`s2b-runners-sK9rhy`), then Task 9 once. Its prologue published the four records atomically as rev32 intends. The structural and macOS gates passed, and the first Linux container, H0, stopped at `cmake --build` on two errors in `tests/test_repo_git.cpp`: c1e (f57cd35) added `Git::Opts::ceiling` with no default initializer.
That compiler output is a STOPPED instrument: `gmake` without `-k` stops at the first failing target, and it had reached 147 objects. A keep-going build of a83657e in the same image finds **24 errors in 6 test files at 14 initializer sites over 5 structs**, all in `tests/`, none in `src/`. The structs are `Git::Opts` (ceiling), `RepoOutcomeRow` (kind, detail), `SessionRowReport` (installed_session_id, detail) and `ScanExclusions` (repo_subtrees, claimed_markers). The files are test_repo_git, test_cli, test_open, test_pack, test_envelope and test_scan. B builds with 0 errors. Every flagged member was added by a 2b commit.

## Two test-only repairs, proven in the plan's own container

REPAIR 1 (`repair-1-initializers.patch`, 6 files, +33/−10): every omitted member is named explicitly in declaration order (`= std::nullopt` / `= {}`). It is semantically neutral, and no product header moves. Keep-going build: 0 errors.
The canonical container at that head builds clean, then fails Phase S: `biv_tests` rc 42 on ONE case, *c3 hook installer obeys preapproval and absent noninteractive hook* (`test_cli.cpp:3032`, captured stderr empty). It is the SAME single failure impl-10's own macOS H0 run recorded (483/1/0/3). It passes under the console reporter and fails deterministically ALONE under `-r xml`.
Mechanism: Catch2's redirecting reporters (the XML reporter sets `shouldRedirectStdOut`) re-point `std::cerr`'s rdbuf at assertion boundaries. The test swaps `std::cerr` to its own buffer and then calls the hook INSIDE a `CHECK`, so the hook's line goes to Catch2's buffer. This latent defect came in with c3 (13ec732); every commit was checked under the console reporter, and Task 9 runs `-r xml` on both platforms.
REPAIR 2 (`repair-2-c3-hook-test.patch`, test_cli.cpp only): the hook is called outside the assertion, and the saved decision is asserted after. The canonical container at that head gives **rc 0**: Phases R/T/S all 0 and every producer 0, the same verdict B gets.

## What remains after both repairs

(a) **32 clang-tidy errors in 7 product files** (ctest `safety-tidy-analyzer`, coverage 37/37 sources; B: 0): 16 unchecked `operator[]`, 5 unchecked optional access, 5 easily-swappable parameters, 2 non-constant array index, and one each of special-member-functions, non-const global, do-while and empty-catch.
By blame at a83657e: c6p 534decb 14, c4b cd12bb5 5, c2 e5aa0a3 5, c6b cd51937 3, c5 5aeb81c 2, c4a ef8e492 2, c1e f57cd35 1. Files: open.cpp 15, pack.cpp 4, url_consent.cpp 4, consent_display_table.hpp 4, envelope.cpp 3, main.cpp 1, restore.cpp 1 (`clang-tidy-blame-a83657e.txt`).
The container carries ctest's rc as DATA, so these do not stop Task 9. But the vehicle's remote tidy leg WOULD be red, and red remote CI can be cited nowhere, so they block the landing either way.
(b) `harness-selftest` (ctest data, not a producer) VARIES from run to run in this image: B failed 3 enumeration-race cases; the repair-1 head failed 2 of those 3; the repair-2 head failed those same 3 PLUS `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`, which B did not fail. The three shared cases look timing-sensitive (files inserted at a scandir stop). I do NOT claim the fourth is pre-existing: one B sample cannot show that. c8 touched `harness/**` (e3.py untouched), so it is m-3's to look at. Task 9's population rule is what reads this, and I flag it rather than rule on it.

## The defects that are mine

(1) The plan never put the candidate in front of the Linux toolchain before Task 9. Nineteen commits were verified only by `ci-macos` builds and console-reporter runs, so Task 9 became the discovery point for three classes at once.
(2) The macOS count gate took `biv_tests` 419/0/0/3 → 483/1/0/3 as an admitted tuple move. It was the Linux producer gate that refused a failing test. A count gate must not be able to carry a failure count.

## Rulings asked

R1 — SCOPE: repair 1 touches `tests/test_repo_git.cpp`, OUTSIDE the 52-path allowlist (the other five test files are in it). Is the allowlist admitted to 53 for a test-only repair commit, c8L after c8, with H0 = the head after it (and c9 after it)?
R2 — THE TIDY CLASS: the 32 errors sit in owner-sealed product bytes that the token declared final at a83657e. My recommendation is one behaviour-neutral product commit (c8T): checked access, has-value guards, a const global, rule-of-five on `StageCleanup`, a non-empty catch, strong types or named parameters where swappable. Each change would be routed to the sealing owner for a byte review before landing, with no tidy suppression and no `.clang-tidy` change (either would be weakening the gate). Which owners review which files, and does it land in 2b before Task 9? The alternative is to hold 2b's landing on a separate act.
R3 — PROCESS (mine to write on your word): rev33 adds (i) a mandatory canonical-container gate at the new head BEFORE Task 9 — the plan's own `linux-container.sh` at H0, rc 0, plus the tidy test green; (ii) the macOS count gate refusing any tuple with failures > 0; (iii) the preservation of impl-10's Task 9 outputs before a re-run.
On (iii): Task 9 writes its receipts under `$EVID/H/` with `>` (64 write sites), so a re-run would overwrite impl-10's record. The design is to move `H/`, `H0.txt` and `helpers.verify-9.txt` — exactly the Task-9-produced set present, verified against the home — into a confined `$EVID/attempts/task9-H0-a83657e/` by staged rename before the new Task 9 writes anything, walked on a real-home mirror with fault injection. The produced inputs (pinned), the token record and the scratch classes stay where they are, and `s2b-runners-sK9rhy` is never retried or modified.
The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay and the census record (c853be0 and its variance addendum), no trailer; the candidate untouched; the evidence home read only; every container disposable, nothing unrelated pruned; no product byte at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.3 `relay-lint.py --no-freshness` on the draft; python-written; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
