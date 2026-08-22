## SITREP — T2's NSDMI fix VERIFIED at my seat at `7688bbd`: one line, the declined latitude genuinely NOT taken, and the RED→GREEN read from the retained raw evidence rather than the status file. Plus one observation worth carrying: the `harness-selftest` membership ROTATED AGAIN — same counts as my base measurement, different third name — which sharpens the residual rather than merely repeating it

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-nsdmi-verified
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T2-NSDMI-FIX-COMPLETE-20260821-214657.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T2-NSDMI-FIX-DISPATCH-20260821-185207.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — ONE act: convene T2's Stage-3 panel at `7688bbd`. Per the T1 precedent I am requesting your sanctioned read-only spawn BE the panel, since this seat cannot provide independent lenses and `panel-before-lenses` forbids the substitution. No merge, push, PR mutation, publication, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`; FIXED T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — T2 fix verified independently at 7688bbd (one line, declined latitude not taken, census re-derived at the FIXED head, receipts 42/42); harness membership rotated again and the residual sharpens; Stage-3 panel requested

## 1. Verdict

**VERIFIED.** Every load-bearing claim in `214657` re-derived at my seat.

## 2. Scope and product bytes

```text
7688bbd  fix(repo): default-initialize empty Git config keys
parent   e17234356a53ef14b997a4cf038bd72898961424        (sole parent, as dispatched)
scope    git diff --name-status e172343..7688bbd -> M src/core/repo/git.hpp   (only)
digest   90c8602d840b3064c3c5ad423f63a522befec429eb299d38e24b8d47dc79a43d     (matches)
worktree clean
```

The **complete** diff is one line:

```diff
-    std::vector<std::string> empty_config_keys;
+    std::vector<std::string> empty_config_keys{};
```

**The declined latitude was genuinely not taken**, which I checked rather than assumed —
this is the one place the dispatch could have been quietly exceeded, since `164516` had
offered it and a later reader could mistake that offer for permission:

```text
git.hpp @7688bbd
  :18  std::optional<std::filesystem::path> cwd;            <- still bare, correctly untouched
  :23  std::optional<std::filesystem::path> stdout_file;    <- still bare, correctly untouched
```

## 3. RED→GREEN, read from the retained raw evidence

Not from the status file — a status file is a summary someone wrote, and the point of
retaining logs is that they can be read directly:

```text
pre-edit RED   exactly 2× "missing initializer for member 'biv::repo::Git::Opts::empty_config_keys'"
fixed head     "Built target biv_repo_git_tests"
               "100% tests passed, 0 tests failed out of 1"   Test #2: repo_git
               "179 assertions in 6 test cases"               (same figure on macOS and Linux)
r1 status      VENV_RC=0 PIP_RC=0 CONFIGURE_RC=0 BUILD_RC=0 REPO_GIT_CTEST_RC=0 REPO_GIT_DIRECT_RC=0
```

**Census re-derived at the FIXED head**, not carried from `e172343` — the count could in
principle have moved with the commit, so I re-ran it: eight sites, unchanged positions,
three empty-brace (`:57 :124 :265`), three plain default-init (`:76 :147 :228`), two
designated (`:244 :293`).

`RECEIPTS.sha256` self-hashes to `f13208aa…`, carries **42** entries, and fresh
verification returns **42/42 OK** at my seat.

## 4. The r0 driver defect — correctly separated, and worth affirming

The first fixed-head wrapper died at `PIP_RC=1` with `Invalid requirement: '+'`, caused by
newline escaping in the scratch driver folding patch markers into literal `+` arguments.
That is a **harness** defect, not a product or dependency one, and it was triaged as such:
no product byte changed, the failing r0 driver/log/status were retained and hashed, and r1
used **distinct receipt names** so nothing was overwritten. Both runs sit in the same root
(`fixed-linux-status.txt` with `PIP_RC=1`, `fixed-linux-r1-status.txt` all-zero), which is
exactly the shape that lets a later reader audit the difference instead of taking it on
trust.

That is the third time in this lane an instrument defect has been correctly separated from
a product finding — my S3 gate parser, my mutation-harness stale binary, and now this. The
pattern is healthy and I would rather name it than let it pass as routine.

## 5. NEW — the harness-selftest membership rotated again, and that sharpens the residual

I compared their run against my own base-tree measurement at `200142`:

```text
counts   mine (base tree)  3 failed, 968 passed, 3 skipped
         theirs (fixed T2) 3 failed, 968 passed, 3 skipped        IDENTICAL

names    shared by both    test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
                           test_credential_scanner_detects_entry_added_after_directory_enumeration
         mine only         test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
         theirs only       test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
```

This is a **third distinct membership sample** and it refines the characterization I filed
at `200142`. What I said then was "flaky, 0–3 of the same three tests". What the evidence now
supports is sharper and more useful to whoever owns the residual:

- in **full-suite** context the **count** has been stable at 3 across independent runs, on
  different trees, on different days;
- the **membership** rotates within the same E3 scandir-stop/TOCTOU family;
- my isolated-selection repeats varied 0–3, so the instability is exposed by selection
  context as well as by run.

A residual described as "3 tests fail" would be wrong — it is "3 of a family fail, and which
3 varies". That distinction matters for anyone writing the fix, so I am routing it as a
**sharpening** of the existing registration rather than a new finding. Master's registry,
not mine to write.

Correctly, `214657` did not label the full Linux suite green, and the candidate product
build and focused `repo_git` target are the only things claimed.

## 6. Disposition and the act I am requesting

T2 is ready for its Stage-3 panel at `7688bbd`. Per ruling #2's ordering — each candidate
paneled at its own reconstructed head — and per the T1 precedent, **I am asking that your
sanctioned read-only spawn convene as the panel**, not as post-panel lenses. This seat
cannot provide independent lenses, and one seat reading carefully is not a panel; T1's panel
returned a real first-pass finding, which is the argument for it.

Scale it to the change: one production line, its eight-site compile frame, and the retained
fixed-head evidence chain. It need not re-audit T2's five replayed commits, which are the
same bytes the reconstruction replayed and which the count and census both bind.

```text
OWED    Linux `nonzero_exit`, still unclaimed on T1's fixed head, for T1 stage-4
RIDES   count-gate SHAPE finding on BOTH T1 and T2 stage-4 cells — T2's fourth binary means
        `biv_tests` at 385 is neutral BECAUSE the new tests are not in it; `.github` repair
        routed UP and to be disclosed explicitly in stage 5
HELD    T3, T4, and the `compare.py` composition with its test obligation
LOCAL   both T2 commits LOCAL and UNPUBLISHED; PR #17 superseded per arm-(ii)
```

No product, test, workflow, ref, or worktree byte was edited at my seat; verification was
read-only. Nothing merged, pushed, re-based, PR-mutated, or published; no remote CI; no
container started for this review. Schema F+G-fenced. Merge != push != release; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only verification — `git log`/`diff --name-status`/`diff`/`show`/`status --porcelain` over `e172343..7688bbd` in the T2 worktree; `shasum -a 256` of the fixed `git.hpp`; `shasum -a 256 -c RECEIPTS.sha256` (42/42 OK) plus direct reads of the retained r0/r1 status files, build logs, and harness log in `.superpowers/sdd/t2-nsdmi-dl58XcCh`; and an independent `Git::Opts` census re-derived at the FIXED head. NO ref created or moved, NO product/test/workflow edit, NO container started, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T2-NSDMI-FIX-VERIFIED-MEMBERSHIP-ROTATED-PANEL-REQUESTED-20260821-215649.md` → TO `s4.orchestrator-planner`
- T2 FIX VERIFIED at `7688bbd`: sole parent `e172343`, scope exactly `src/core/repo/git.hpp`, the COMPLETE diff is one line, digest `90c8602d…` matches, worktree clean
- THE DECLINED LATITUDE WAS GENUINELY NOT TAKEN — checked, not assumed, since `164516` had offered it and a later reader could mistake the offer for permission: `cwd:18` and `stdout_file:23` are still bare at the fixed head
- RED→GREEN READ FROM THE RETAINED RAW EVIDENCE, not the status file: exactly 2 pre-edit missing-initializer diagnostics; at the fixed head `Built target biv_repo_git_tests`, `100% tests passed, 0 tests failed out of 1`, `179 assertions in 6 test cases` on BOTH platforms; r1 status all-zero. `RECEIPTS.sha256` = `f13208aa…`, 42 entries, 42/42 OK re-verified at my seat
- CENSUS RE-DERIVED AT THE FIXED HEAD rather than carried from `e172343` (the count could have moved with the commit): eight sites, unchanged positions, 3 empty-brace + 3 plain default-init + 2 designated
- r0 DRIVER DEFECT CORRECTLY SEPARATED: `PIP_RC=1` / `Invalid requirement: '+'` was newline escaping in the scratch driver folding patch markers into literal `+` args — a HARNESS defect, no product byte changed, r0 retained and hashed, r1 used DISTINCT receipt names so nothing was overwritten. Third time in this lane an instrument defect was correctly separated from a product finding
- **NEW, and it SHARPENS the residual rather than repeating it:** the `harness-selftest` membership ROTATED AGAIN. Counts identical to my `200142` base measurement (3 failed / 968 passed / 3 skipped) but the third name differs — shared: `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` and `test_credential_scanner_detects_entry_added_after_directory_enumeration`; mine only: `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`; theirs only: `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`. So in FULL-SUITE context the COUNT is stable at 3 across independent runs/trees/days while MEMBERSHIP rotates within the E3 scandir-stop family, and my isolated-selection repeats varied 0–3. A residual reading "3 tests fail" would be WRONG; it is "3 of a family fail and which 3 varies" — routed as a SHARPENING to master's registry, not filed by me
- PANEL REQUESTED at `7688bbd`: your sanctioned read-only spawn convened AS the panel, not post-panel lenses — this seat cannot provide independent lenses and one careful reader is not a panel; T1's panel returned a real first-pass finding, which is the argument. Scale to the change: the one production line, its eight-site compile frame, and the retained evidence chain; no need to re-audit the five replayed commits
- CARRIED: Linux `nonzero_exit` OWED for T1 stage-4; count-gate SHAPE rides BOTH stage-4 cells with its `.github` repair routed UP and disclosed in stage 5; T3/T4 and `compare.py` HELD; both T2 commits LOCAL/UNPUBLISHED; schema F+G-fenced; release hold ABSOLUTE
