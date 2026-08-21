## PLAN (the T1 Linux reds are ruled — I re-verified BOTH at my own seat before ruling either, and your adjudication holds at every load-bearing byte: `safety-tidy-analyzer` is a REAL candidate-introduced T1 blocker, `harness-selftest` is a pre-existing flaky Linux residual that does NOT block Wave-A; the four supersession comments are complete and I verified all four live; the tidy fix is AUTHORIZED as a bounded in-lane revision of T1 under the Arm-1 plan, and your pair Planner issues the impl token — not me — once the Implementer plan-reviews it) — **VERIFIED AT MY SEAT, not accepted on report: (1) `harness/` is BYTE-IDENTICAL base→candidate — `git diff --quiet a02a65b9 76638a0 -- harness/` exits 0 — so the candidate structurally CANNOT have caused `harness-selftest`; the full candidate diff is ten paths, none under `harness/`. (2) `src/core/support/subprocess.cpp` is ADDED at the candidate (diff status `A`; base tree has no such blob) — attribution-by-existence holds, no control can overturn it. (3) The `{}` drop is real: candidate `subprocess.cpp:220` is `std::array<char, 8192> buffer;` while base `probe.cpp:366` is `std::array<char, 8192> buffer{};` — the extraction dropped the value-initializer (`cppcoreguidelines-pro-type-member-init` fires). (4) `ByteCapture` (candidate `subprocess.cpp:118`) holds TWO reference data members — `:136 std::vector<std::byte>& bytes_;` and `:138 bool& output_incomplete_;` — where base `probe.cpp` has ZERO `ByteCapture` and its `Utf8Capture` OWNS `output_`/`limit_` by value (`cppcoreguidelines-avoid-const-or-ref-data-members` fires). (5) Instrument canonical: `.clang-tidy` runs `cppcoreguidelines-*,bugprone-*,cert-*` minus three exclusions (none covering the two firing checks) with `WarningsAsErrors: '*'`, and your clang-tidy 22.1.8 matches the workflow pin — no drift. Your adjudication is correct, and I say so at the bytes.** **RULING #1 — `harness-selftest` DOES NOT BLOCK T1 OR WAVE-A: it is pre-existing at the frozen base (candidate-neutral by byte-identity, which I confirmed) with a flaky membership (your 8-run and 5-run distributions I take on your disclosed non-root Ubuntu 24.04 amd64 control — the byte-identity alone settles the blocking question; the flakiness is color for the residual). No Wave-A candidate is credited or debited for its movement. The RESIDUAL REGISTRATION is master's to write (RESIDUALS is master's registry, not mine) — I am routing it UP this same turn (a pre-existing Linux base red + a flaky-TOCTOU-detector finding as its own workstream); do not hold Wave-A on it.** **RULING #2 — `safety-tidy-analyzer` BLOCKS T1, and the fix is AUTHORIZED as a bounded in-lane revision of T1 under the Arm-1 plan (`s4-matrix-arm1-plan-20260806`): T1 is not merge-ready as it stands. The fix touches ONLY T1's own new file `src/core/support/subprocess.cpp` — no sealed, schema, charter, `.github`, or cross-lane surface — so it is squarely in your lane's plan and mine to authorize; it is the repair the re-verification exists to enable, and both you and the Implementer correctly REFUSED to self-grant the impl token (200142 and 200811 are report-only and confer none — exactly right). I delegate CONDITIONAL DISPATCH-IMPL authority to your PAIR PLANNER for this bounded scope: the token is YOURS to issue (a pair Planner is the DISPATCH-IMPL grantor; only merge tokens are orchestrator-level), NOT mine — the read-only re-verification dispatch gave you no in-scope plan to issue under, and THIS relay re-opens the bounded impl scope so you can.** **THE CEREMONY AND THE ACCEPTANCE BAR (do not shortcut it — the ByteCapture reshape is a bounded DESIGN decision, not a mechanical token, because those reference members ARE the mechanism of the review-fold's per-stream `output_incomplete` improvement the coverage lens asked for): your pair writes a bounded PLAN naming the chosen ByteCapture shape and the `{}` restore; your Implementer PLAN-REVIEWs it (that review is the gate, PARENT→the PLAN); your pair Planner then issues the bare `DISPATCH-IMPL` token (PARENT→the approving PLAN-REVIEW, TO exactly the one Implementer, SCOPE_DIFF as `- <path> -> in` rows with a SCOPE_ROW_EVIDENCE row per IN path, SCOPE_DIFF_RESULT: all-in) scoped to `subprocess.cpp` (+ its test file if the fix needs one). NO separate DESIGN gate — the PLAN carries the shape. THE PLAN MUST PROVE THREE PROPERTIES, or the Implementer PLAN-REVIEW withholds approve: (i) the chosen shape CLEARS BOTH firing checks (restore `{}`; and either give `ByteCapture` the owning shape `Utf8Capture` already uses, or hold the outputs in a form `avoid-const-or-ref-data-members` accepts — note reference_wrapper was already reduced to a plain reference upstream, so do not silently reintroduce it without saying so); (ii) it PRESERVES the per-stream `output_incomplete` behavior the review-fold introduced (the coverage-lens improvement must not regress); (iii) it does NOT regress the geometric capture growth that commit `76638a0` itself restored. Then re-run the Linux tidy leg to GREEN at the fixed head before resuming.** **SEQUENCING AFFIRMED: hold T2/T3/T4 and the T3 `compare.py` composition (with its test obligation) until T1's fix lands — you were right not to resume the dependent stack, because fixing T1 rebuilds the downstream reconstructions. The count-gate shape stays routed; Linux `nonzero_exit` stays owed; both ride T1's fixed head.** **DISCIPLINE AFFIRMED, not debited: "a leg is not redundant because its count cell is redundant" is exactly the right lesson and I am adopting it — a leg carries ROWS, and `safety-tidy-analyzer` is a Linux-only row macOS is structurally blind to; your holding the Linux leg would have carried a real defect past a green macOS gate, and you caught and stated that yourself. Your three refuted-before-filing control errors (harness-only extract, root run, the earlier `--target biv_tests`) are the freeze-the-artifact discipline WORKING — a control refuted at your own seat never left it. The Implementer's measure-before-post + no-duplicate check on the four comments is the same discipline on the keyboard side. This is the lane running as intended.** the supersession comments are complete and I verified all four LIVE at my seat (each carries the operator's verbatim text with its own correct measured head — #16 76638a0, #17 92a70c9c, #19 d7d32f9, #20 cb1f625 — no head push/close/label); I am receipting that UP to master this turn. origin/main untouched; the Arm-1 schema act F+G-fenced and untouched; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-t1-tidy-fix-authorized-in-lane
PARENT_DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
IN_REPLY_TO: SITREP-PLANNER-WAVE-A-T1-LINUX-REDS-ADJUDICATED-ONE-REAL-ONE-PREEXISTING-FLAKY-20260820-200142.md
RELATED_CONTEXT: SITREP-IMPLEMENTER-WAVE-A-SUPERSESSION-COMMENTS-COMPLETE-T1-TIDY-AWAITS-IMPL-TOKEN-20260820-200811.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — the T1 tidy fix is a bounded in-lane revision of T1 under the Arm-1 plan (subprocess.cpp only; no sealed/schema/charter/.github/cross-lane surface), authorized here; your pair Planner issues the DISPATCH-IMPL token after the Implementer PLAN-REVIEW approve. The harness-selftest RESIDUAL registration is master's to write (routed UP this turn). Each eventual Wave-A merge remains a NEW operator word. No merge/push/PR-mutation/schema/release at this ruling. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — T1 Linux reds ruled at the bytes (I re-verified both): harness-selftest is a pre-existing flaky Linux residual that does NOT block Wave-A (registration routed UP to master); safety-tidy-analyzer is a real candidate-introduced T1 blocker and the fix is AUTHORIZED as a bounded in-lane revision under the Arm-1 plan; your pair Planner issues the impl token after a bounded PLAN + Implementer PLAN-REVIEW proving three properties (clears both checks / preserves per-stream output_incomplete / no capture-growth regression); T2-T4 + compare.py held until T1 lands; four supersession comments verified live and receipted UP

## 1. Verified at my seat (your adjudication holds)

```text
harness/ diff     git diff --quiet a02a65b9 76638a0 -- harness/  -> EXIT 0 (byte-identical)
subprocess.cpp    diff status A (added at candidate); base tree has no such blob
{} drop           cand subprocess.cpp:220  std::array<char, 8192> buffer;
                  base probe.cpp:366        std::array<char, 8192> buffer{};
ByteCapture refs  cand :136 std::vector<std::byte>& bytes_;  :138 bool& output_incomplete_;
                  base probe.cpp ByteCapture count = 0; Utf8Capture owns output_/limit_ by value
instrument        .clang-tidy cppcoreguidelines-*,... WarningsAsErrors '*'; tidy 22.1.8 == pin
```

## 2. The two rulings

```text
harness-selftest      NOT a T1/Wave-A blocker (pre-existing, candidate-neutral by byte-identity,
                      flaky). Residual registration is MASTER's to write -> routed UP this turn.
                      No candidate credited/debited for its movement.
safety-tidy-analyzer  REAL candidate-introduced T1 blocker. Fix AUTHORIZED as a bounded in-lane
                      revision of T1 under the Arm-1 plan (subprocess.cpp only). Your pair Planner
                      issues DISPATCH-IMPL after the Implementer PLAN-REVIEW approve.
```

## 3. The ceremony and the three-property acceptance bar

```text
plan       your pair writes a bounded PLAN naming the ByteCapture shape + the {} restore
review     your Implementer PLAN-REVIEWs it (the gate; PARENT->the PLAN)
token      your pair Planner issues bare DISPATCH-IMPL (PARENT->the PLAN-REVIEW, TO one Implementer,
           SCOPE_DIFF `- <path> -> in` rows + SCOPE_ROW_EVIDENCE per IN path + SCOPE_DIFF_RESULT all-in),
           scoped to subprocess.cpp (+ test file if needed); NO separate DESIGN gate
prove      (i) clears BOTH firing checks; (ii) preserves per-stream output_incomplete (coverage-lens
           improvement not regressed); (iii) no regression of 76638a0's geometric capture growth
then       re-run the Linux tidy leg to GREEN at the fixed head before resuming
```

## 4. Sequencing

```text
hold       T2/T3/T4 + the T3 compare.py composition (with its test obligation) until T1's fix lands
ride       count-gate shape (routed) + Linux nonzero_exit (owed) ride T1's fixed head
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/branch/ref/merge/push/PR act at this seat — read-only verification in the local repo: `git diff --quiet a02a65b9 76638a0 -- harness/` (exit 0); `git diff --name-status` (subprocess.cpp = A, probe.cpp = M); `git show` of the buffer decls (cand subprocess.cpp:220 vs base probe.cpp:366), the ByteCapture reference members, base Utf8Capture value-ownership, and `.clang-tidy`; and read-only `gh pr view` of the four live supersession comments (each carries its own correct measured SHA). The tidy fix is YOUR keyboard under a token YOUR pair Planner issues after the Implementer PLAN-REVIEW; I issue NO bare token here (this PLAN delegates conditional impl authority, it does not itself carry a token). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read at 201613 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222) + the v2.9 historical embedded-pipe cell-count class (R-4.27); none mine; my appended row is 10-cell clean, status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md` → `s4-matrix.planner`, `s4-matrix.implementer`
- BOTH T1 Linux reds re-verified at my seat (harness/ byte-identical exit 0; subprocess.cpp added A; {} drop cand :220 vs base probe.cpp:366; ByteCapture two reference members vs base Utf8Capture value-ownership, base ByteCapture count 0; .clang-tidy WarningsAsErrors '*' + tidy 22.1.8 == pin) — your adjudication holds at every load-bearing byte
- RULING #1 harness-selftest: pre-existing flaky Linux residual, candidate-neutral by byte-identity; does NOT block T1 or Wave-A; no candidate credited/debited for its movement; RESIDUAL REGISTRATION is master's to write, routed UP this turn (pre-existing Linux base red + a flaky-TOCTOU-detector finding as its own workstream)
- RULING #2 safety-tidy-analyzer: REAL candidate-introduced T1 blocker (subprocess.cpp is T1's own new file, no sealed/schema/charter/.github/cross-lane surface); fix AUTHORIZED as a bounded in-lane revision of T1 under the Arm-1 plan; you and the Implementer correctly refused to self-grant the impl token; I delegate CONDITIONAL DISPATCH-IMPL authority to your PAIR PLANNER for this bounded scope — the token is YOURS to issue (pair Planner is the impl-token grantor), the read-only re-verification dispatch gave you no in-scope plan and THIS relay re-opens the bounded impl scope
- CEREMONY: bounded PLAN naming the ByteCapture shape + {} restore -> Implementer PLAN-REVIEW (the gate, PARENT->PLAN) -> pair Planner bare DISPATCH-IMPL (PARENT->PLAN-REVIEW, TO one Implementer, SCOPE_DIFF rows + SCOPE_ROW_EVIDENCE + all-in) scoped to subprocess.cpp (+ test file if needed), NO separate DESIGN gate; PLAN MUST PROVE (i) clears both firing checks, (ii) preserves per-stream output_incomplete (coverage-lens improvement not regressed; note reference_wrapper was already reduced to a plain reference upstream), (iii) no regression of 76638a0's geometric capture growth; then re-run the Linux tidy leg GREEN at the fixed head
- SEQUENCING: hold T2/T3/T4 + T3 compare.py composition (with test obligation) until T1's fix lands (dependent stack; fixing T1 rebuilds downstream); count-gate shape routed + Linux nonzero_exit owed ride T1's fixed head
- DISCIPLINE AFFIRMED not debited: "a leg is not redundant because its count cell is redundant" adopted; three refuted-before-filing control errors = freeze-the-artifact discipline working; Implementer measure-before-post + no-duplicate check same discipline on the keyboard
- SUPERSESSION COMPLETE + verified live at my seat (four comments, each with its own correct measured head, verbatim text, no head push/close/label); receipted UP to master this turn
- origin/main untouched; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
