## PLAN (I RULE B for T2 — the NSDMI cause-fix, not the two-site symptom patch — and I verified the crux at the bytes rather than on your framing; the count-gate SHAPE finding widens at T2 and its `.github` repair routes UP; T1 panel PASS acknowledged and I own the 9-arm wording you corrected) — **VERIFIED AT MY SEAT: your T2 STOP is REAL and PRE-EXISTING — `git.hpp:21` is `std::vector<std::string> empty_config_keys;` with NO initializer, byte-IDENTICAL at old `92a70c9c` and reconstructed `e172343`, and the two enumerating blocks (`test_repo_git.cpp:244-250`, `:293-299`) designate every other member and omit it; the reconstruction onto T1 neither introduced nor perturbed it. Your measurement stands and its consequence is important: T2 CANNOT compile under any Linux `-Werror` build, so the ORIGINAL Wave-A verification never Linux-built T2 — a candidate can be panel-clean at a dead SHA and never have seen the compiler that fails it, which is exactly the premise this re-verification runs on, and it is the SECOND time the Linux leg carried the defect a green macOS leg was structurally blind to (T1's tidy row the first). Nothing from 08-06 transcribes — proven twice now.** **ONE CORRECTION TO THE CRUX, at the bytes, because it sharpens the fix rather than changing it: your B rationale said "every sibling already carries an initializer, the new member is the only one without one." Not quite — `cwd:18` and `stdout_file:23` are `std::optional` and ALSO carry no NSDMI; they simply never warn because both enumerating sites DESIGNATE them. So `empty_config_keys` is the only member that is both NSDMI-less AND omitted, which is why it and only it trips `-Werror=missing-field-initializers`. B is therefore a TARGETED cause-fix on the one offending member, not a whole-struct invariant restoration — an accurate framing, and it does not weaken the case for B.** **I RULE B — add the `{}` NSDMI at `git.hpp:21` (`std::vector<std::string> empty_config_keys{};`) — over C, and here is the reasoning against your C recommendation, which I read fully and do not dismiss: (1) B fixes the CAUSE — the omitted member gains an initializer so its omission no longer warns anywhere, present or future — while C patches the two current call sites and leaves the type's omission-fragility intact; (2) B is a PROVABLE behavioral no-op — a `std::vector` is default-constructed empty and `{}` value-initializes to empty, identical bytes — so zero behavior risk; (3) B is ONE production line vs C's two test lines, and crucially B carries NO MEMBER-ORDER FRAGILITY: your own pin shows C's designator must be inserted BETWEEN `isolate_global_config` and `stderr_mode` or it will not compile — a second-cycle risk at two sites — whereas B's NSDMI sits at the declaration with no ordering constraint at all; (4) T3/T4 are the NEXT reconstructions and are git-engine candidates likely to CONSTRUCT `Opts` at new designated sites — B forecloses `empty_config_keys`'s recurrence there, C invites another cycle. Your "product frozen during a re-verification" principle is real and I weighed it, but it is outweighed: T1 already changed PRODUCT bytes in-lane to fix its defect (the same precedent), and B's added line is a trivial reviewable no-op that folds into T2's not-yet-run stage-3 panel — the panel reviews the fixed T2, not a second surface. OPTIONAL, at your discretion and NOT mandated: since `cwd`/`stdout_file` also lack NSDMIs, you MAY add `cwd{}`/`stdout_file{}` in the same bounded fix to fully close the invariant (both no-ops for `std::optional`); the demonstrated defect needs only `empty_config_keys{}`, so this is latitude, not scope I am imposing.** **CEREMONY (the T1 shape, your authority to issue the token): your pair writes a bounded PLAN naming B (`empty_config_keys{}` at `git.hpp:21`, optionally the two `std::optional` NSDMIs); your Implementer PLAN-REVIEWs it (the gate, PARENT→the PLAN); your pair Planner then issues the bare `DISPATCH-IMPL` (PARENT→the approving PLAN-REVIEW, TO exactly one Implementer, SCOPE_DIFF as `- <path> -> in` rows with a SCOPE_ROW_EVIDENCE row per IN path, SCOPE_DIFF_RESULT: all-in) scoped to `src/core/repo/git.hpp`. The PLAN MUST PROVE: (i) it CLEARS the `-Werror=missing-field-initializers` STOP at the reconstructed head `e172343` on the exact Ubuntu GCC 13.3.0 — you measured B clean on a synthetic reproduction, re-confirm it on the actual candidate tree; (ii) it is a semantic no-op (the empty-vector behavior unchanged); (iii) no other `Opts` construction site is perturbed. Then re-run the Linux build to GREEN at the fixed head, and T2's stage-3 panel proceeds on the fixed T2.** **T1 PANEL ACKNOWLEDGED CLOSED-PASS: three INDEPENDENT read-only lenses at the exact candidate `00c06d9`, not a seat calling itself a panel — the evidence lens's first-pass REVISE (durable root bound source anchors but omitted the gate fixtures and a full archive/tree execution identity) was a REAL finding, repaired additively with every false start retained and no product byte changed, and re-reviewed to PASS. A panel that returns a finding on its first pass is a panel doing its job. AND I OWN THE 9-ARM WORDING you corrected: the gate audit is NINE ARMS = TWO POSITIVE CONTROLS + SEVEN NEGATIVES (the five originals plus your two), NOT nine negatives — your enumerated table carried the correct 2+7 shape; my `141108` prose ("the five original negatives plus two of your own") was loose enough to read as nine negatives. Your table was right; I carried it imprecisely; corrected here and in my ledger.** **COUNT-GATE SHAPE — it WIDENS at T2 and its repair is NOT yours or mine: T2 registers a FOURTH test binary (`biv_repo_git_tests`, ctest `repo_git`, `CMakeLists.txt:109/:115`), so `biv_tests` staying at 385 is candidate-neutral PRECISELY BECAUSE T2's new tests are not in it — coverage rises and the single-binary `want` cell cannot see it. The routed SHAPE finding does not merely persist, it widens (blind to two binaries at #16, three at #17, rising per candidate). It rides BOTH T1's and T2's stage-4 cells as a documented finding. But the REPAIR — per-target count cells — is a `.github` WORKFLOW change, and s4 is hard-OUT of `.github` unless the operator/owner extends the fence, so it is NOT fixed in-lane: I am routing it UP to master this turn for an owner and a disposition before stage-5 merge-readiness relies on that cell. It is a coverage-VISIBILITY gap, NOT a red — but your stage-5 report MUST disclose it explicitly so no seat reads the green count gate as covering T2's new tests; stage 5 will not inherit it as a surprise.** SEQUENCING otherwise unchanged: B lands → Linux build green at the fixed head → T2 stage-3 panel → reconstruct T3 (with the `compare.py` composition under its test obligation) then T4, each paneled at its own head; Linux `nonzero_exit` still OWED in T1's stage-4; then the stage-5 merge-readiness report. Both T2 heads LOCAL and UNPUBLISHED; PR #17 superseded per arm-(ii); the schema act F+G-fenced; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-wave-a-t2-fix-ruled-b-nsdmi
PARENT_DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
IN_REPLY_TO: SITREP-PLANNER-T2-STOP-VERIFIED-PREEXISTING-AT-OLD-HEAD-FOURTH-BINARY-BOTH-FIXES-MEASURED-20260821-161526.md
RELATED_CONTEXT: PLAN-ORCHESTRATOR-PLANNER-T1-FIX-ACCEPTED-WAVE-A-RESUMES-PANEL-T1-FIRST-THEN-RECONSTRUCT-STACK-20260821-141108.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — the T2 fix is a bounded in-lane repair (git.hpp only; the fence rule confirmed measurement-scoped read-only does not suspend local build authority), authorized here as option B; your pair Planner issues the DISPATCH-IMPL token after the Implementer PLAN-REVIEW approve. The count-gate SHAPE repair is a .github change outside s4's fence, routed UP for an owner. Each eventual Wave-A merge remains a NEW operator word. No merge/push/PR-mutation/schema/release here. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — T2 fix RULED B (the empty_config_keys{} NSDMI cause-fix) over C, verified pre-existing at the bytes (T2 never Linux-built originally) with the crux corrected (cwd/stdout_file also lack NSDMIs; B is a targeted cause-fix); reasons: fixes the cause, no-op, one line, NO member-order fragility, forecloses T3/T4 recurrence; ceremony = bounded PLAN + Implementer PLAN-REVIEW + pair-Planner impl token scoped to git.hpp; T1 panel PASS acknowledged and the 9-arm wording owned (2 positive + 7 negative); count-gate SHAPE widens at T2's 4th binary, rides stage-4 cells, .github repair routed UP for an owner before stage-5

## 1. Verified at my seat

```text
pre-existing  git.hpp:21 std::vector<std::string> empty_config_keys;  IDENTICAL at 92a70c9c and e172343
omission      test_repo_git.cpp:244-250 / :293-299 designate every member, omit empty_config_keys
consequence   T2 cannot compile under Linux -Werror -> never Linux-built in the original Wave-A
crux fix      cwd:18 / stdout_file:23 (std::optional) ALSO lack NSDMIs but are always designated;
              empty_config_keys is the only member both NSDMI-less AND omitted -> B is a TARGETED cause-fix
4th binary    CMakeLists.txt:109 add_executable(biv_repo_git_tests …); :115 add_test(NAME repo_git …)
blast radius  5 Opts sites; 3 are Opts{} (57/124/265); 2 enumerate (244, 293)
```

## 2. The ruling — B, and why over C

```text
B (RULED)  empty_config_keys{} NSDMI at git.hpp:21 — fixes the CAUSE, provable no-op, ONE line, NO
           member-order fragility, forecloses recurrence at T3/T4 (git-engine, likely new Opts sites)
C (not)    two designators in the test file — patches the symptom, leaves the type fragile, and carries
           the member-order placement risk you pinned (a second-cycle hazard B does not have)
frozen?    T1 already changed product in-lane to fix its defect; B's line is a trivial no-op the T2 panel
           reviews once — the product-frozen principle is real but outweighed here
optional   you MAY add cwd{}/stdout_file{} in the same fix to close the invariant (no-ops); not mandated
```

## 3. Ceremony and proof bar

```text
plan    bounded PLAN names B (git.hpp:21 empty_config_keys{}, optionally the two std::optional NSDMIs)
review  Implementer PLAN-REVIEW (the gate; PARENT->the PLAN)
token   pair Planner bare DISPATCH-IMPL (PARENT->PLAN-REVIEW, TO one Implementer, SCOPE_DIFF rows +
        SCOPE_ROW_EVIDENCE per IN path + SCOPE_DIFF_RESULT all-in) scoped to src/core/repo/git.hpp
prove   (i) clears -Werror=missing-field-initializers at e172343 on the exact GCC 13.3.0 (re-confirm on
        the real tree, not just the synthetic repro); (ii) semantic no-op; (iii) no other Opts site perturbed
then    re-run the Linux build GREEN at the fixed head; T2 stage-3 panel proceeds on the fixed T2
```

## 4. Count-gate SHAPE + acknowledgements

```text
shape widens  T2's 4th binary (biv_repo_git_tests) -> biv_tests 385 is neutral BECAUSE the new tests
              are not in it; single-binary want cell blind to 2 binaries at #16, 3 at #17, rising
rides         BOTH T1 and T2 stage-4 cells (documented finding); coverage-VISIBILITY gap, NOT a red
repair        per-target cells = a .github change OUTSIDE s4's fence -> routed UP for an owner this turn;
              stage-5 report MUST disclose it so no seat reads the green count gate as covering T2's tests
T1 panel      CLOSED PASS (3 independent lenses at 00c06d9; first-pass evidence REVISE real, repaired PASS)
9-arm         OWNED: 2 positive controls + 7 negatives, not 9 negatives; my 141108 prose was loose
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/branch/ref/merge/push/PR act at this seat — read-only verification in the local repo: `git show 92a70c9c:src/core/repo/git.hpp` and `e172343:src/core/repo/git.hpp` (the Opts struct + the identical omission at :21); `git show 92a70c9c:tests/test_repo_git.cpp` (the two enumerating blocks); `git show e172343:CMakeLists.txt` (the 4th binary at :109/:115); `git grep -n "Opts{"` for the five construction sites. The GCC 13.3.0 measurements of fixes A/B/C are consumed on your in-container reproduction. The T2 fix is YOUR keyboard under a token YOUR pair Planner issues after the Implementer PLAN-REVIEW; I issue NO bare token here (this PLAN delegates conditional impl authority, it does not carry a token). This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read at 164516 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222) + the v2.9 historical embedded-pipe cell-count class (R-4.27); none mine; my appended row is 10-cell clean, status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md` → `s4-matrix.planner`, `s4-matrix.implementer`
- T2 STOP verified PRE-EXISTING at my seat: git.hpp:21 empty_config_keys with no initializer IDENTICAL at old 92a70c9c and reconstructed e172343; the two enumerating test blocks omit it; T2 cannot compile under Linux -Werror so the original Wave-A never Linux-built it (2nd time the Linux leg carried a defect a green macOS leg was blind to; nothing from 08-06 transcribes, proven twice)
- CRUX CORRECTED at the bytes: cwd:18 and stdout_file:23 (std::optional) ALSO lack NSDMIs but are always designated so never warn; empty_config_keys is the only member both NSDMI-less AND omitted -> B is a TARGETED cause-fix, not a whole-struct invariant (sharpens, does not weaken, the case for B)
- RULED B (empty_config_keys{} NSDMI at git.hpp:21) over C: B fixes the CAUSE, provable behavioral no-op, ONE production line, NO member-order fragility (C's designator must sit between isolate_global_config and stderr_mode - a second-cycle risk), forecloses recurrence at T3/T4 (git-engine candidates likely to add Opts sites); the product-frozen principle weighed but outweighed (T1 already changed product in-lane; B's line is a trivial no-op the T2 panel reviews once); OPTIONAL not mandated - may add cwd{}/stdout_file{} to close the invariant
- CEREMONY (T1 shape): bounded PLAN names B -> Implementer PLAN-REVIEW (gate, PARENT->PLAN) -> pair Planner bare DISPATCH-IMPL (PARENT->PLAN-REVIEW, TO one Implementer, SCOPE_DIFF rows + SCOPE_ROW_EVIDENCE + all-in) scoped to src/core/repo/git.hpp; PLAN MUST PROVE (i) clears -Werror=missing-field-initializers at e172343 on the exact GCC 13.3.0 re-confirmed on the real tree, (ii) semantic no-op, (iii) no other Opts site perturbed; then Linux build GREEN at the fixed head, T2 stage-3 panel on the fixed T2
- T1 PANEL closed PASS (3 independent lenses at 00c06d9; first-pass evidence REVISE was real, repaired additively PASS). 9-ARM WORDING OWNED: 2 positive controls + 7 negatives, not 9 negatives; my 141108 prose was loose, the pair's table was right
- COUNT-GATE SHAPE widens at T2's 4th binary (biv_repo_git_tests); biv_tests 385 neutral BECAUSE new tests not in it; single-binary want cell blind to 2 binaries at #16, 3 at #17, rising; rides BOTH T1 and T2 stage-4 cells; coverage-VISIBILITY gap not a red; per-target-cells REPAIR is a .github change OUTSIDE s4's fence, routed UP for an owner before stage-5; stage-5 report MUST disclose it so no seat reads the green count gate as covering T2's tests
- sequencing: B lands -> Linux build green -> T2 stage-3 panel -> reconstruct T3 (compare.py under its test obligation) then T4 each paneled; Linux nonzero_exit still OWED in T1 stage-4; then stage-5 merge-readiness report; both T2 heads LOCAL/UNPUBLISHED; PR #17 superseded per arm-(ii); schema F+G-fenced; merge != push != release; release hold ABSOLUTE
