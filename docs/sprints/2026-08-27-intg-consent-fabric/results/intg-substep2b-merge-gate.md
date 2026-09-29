# Merge packet — sub-step 2b wiring act (assembled 2026-09-29 at the pair-planner's seat; HELD at H)

Every value below was MEASURED at the pair-planner's seat by the command named beside it, immediately before this file was written.
The candidate worktree, the evidence home and the runners directory were read only.
No remote CI result and no waiver is cited anywhere in this packet.
Census values are named by DIGEST ONLY (master 211118 §5): a spelled-out value would become a row in the census this packet declares.
Merged is not pushed; pushed is not released. The release hold is ABSOLUTE.

## 1. Candidate identity

- Candidate head H = `cb19326a5596bf30eab2ec2b9baeda0bc77be895` (`git -C ../bivpak-intg-substep2b-wiring rev-parse HEAD`; branch `intg/substep2b-wiring`; `status --short` EMPTY).
- B = origin/main = `186adf7d67171bd7afe621f39b657a1a113ce299` (`git ls-remote origin refs/heads/main` after a fetch). This is the R-4.49 landing merge, the published pin.
- `git merge-base main H` = B.
- Remote branch `refs/heads/intg/substep2b-wiring` = H. It was pushed ONCE under impl-16 (Task 10): `push_rc=0`, `class=a`, `remote-branch-before` EMPTY, `remote-branch-after` == H. There was one push URL and one fetch URL, both `https://github.com/iwnlcern/bivpak.git`; the url-rewrite set was EMPTY; the repository visibility is `PUBLIC` under the operator's word "2".
- PR #28 `https://github.com/iwnlcern/bivpak/pull/28`, read with `gh pr view 28 --json state,isDraft,headRefOid,mergeable`: OPEN, isDraft TRUE, head H, MERGEABLE. It is the VEHICLE under R-4.51 clause (2).
- `git rev-list --count B..H` = 26, of which 24 are authored `intg.pair-implementer` and 2 are m-3's (the R-4.62 probe-fixture commit `3431bb7` and the harness commit `a83657e`). The commit messages carry 0 `Co-Authored-By` lines (`git log --format=%B B..H | grep -ci co-authored-by`). The exposure census at Task 10 found `commits=26` and `secret_hits=0`, with every author identity under the placeholder `@local` domain.
- B→H: 55 files, +8195 −374 (`git diff --numstat B H`), under src/ (26), tests/ (11), harness/ (13), schemas/ (2), tools/ (1), CMakeLists.txt and .github/ (1 each).
- Plan of record: `plans/PL-intg-substep2b-20260915.md` revision 50 @ sha256 `7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f` (commit `df2935e`), APPROVED at the exact hash by the implementer (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md`, plan-review-52, covering the complete rev48→rev50 landing delta). Master verified it at its own bytes (`233421`, `001609`) and filed the fresh T-ORACLE carry (`023528`). `t-oracle.txt` was rewritten from that carry with its predecessor preserved, and the real prefix returned rc 0 (`docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/t-oracle-rewrite-rev50.txt`).
- Tokens: seventeen implementation tokens (`intg-substep2b-impl-1` … `-impl-17`), each PARENT-bound to its approving review. The candidate was built through Task 9b; Task 10 pushed the branch and opened the PR (impl-16); Task 11 finalized the local record (impl-17, returned `021324` rc 0, accepted by master `023917`).

## 2. Evidence chain (all at the exact SHA)

- THE HEAD GATE AT H (`heads/c11/headgate.txt` in the evidence home): `headgate label=c11 head=cb19326a5596bf30eab2ec2b9baeda0bc77be895 tidy_expected=none tidy_findings=0 coverage=37/37 macos_rc0=5 macos_failures=0 container_rc=0 linux_failures=0`. The container is ubuntu:24.04, linux/amd64, `--init`, with nofile soft raised to hard (`linux-suite.sh`), and the observer variables unset.
- Tuples at H (successes/failures/expectedFailures/skips):
  - macOS: subprocess 12/0/0/0, repo_git 6/0/0/0, repo_engine 82/0/0/0, biv_tests 486/0/0/3, probe 25/0/0/0;
  - Linux: subprocess 12/0/0/0, repo_git 6/0/0/0, repo_engine 82/0/0/0, biv_tests 488/0/0/1, probe 25/0/0/0.
  - The expected skips are exactly the pinned names: macOS 3, Linux 1.
- Final count gates: `count_gate_final_macos_rc=0` and `count_gate_final_linux_rc=0`, every cell `UNCHANGED` against the workflow cells at H (`R/count-gate-final-*.txt`). Both skip sets are unchanged (`skipset_linux_rc=0`).
- ctest at H (`heads/c11/ctest-status.txt`): every row passed except `harness-selftest`. `safety-asan-ubsan` and `safety-fuzz-smoke` did not run, as in the canonical workflow. The foreign set is EMPTY.
- The Linux `harness-selftest` bar: `failed=3 passed=1049 skipped=3 population=1055`. All three names are inside the R-4.35 family: `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`, `test_credential_scanner_detects_entry_added_after_directory_enumeration` and `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`. The foreign names file is EMPTY, `population_equal_rc=0`, and the bar is `pass-r435-disclosed-registered-red` (§3).
- E3 and harness receipts: `e3_linux_rc=0`, `harness_e2_linux_rc=0`, `harness_e2_macos_rc=0`.
- FX legs (`legs/`): 34 receipts carry `verdict=PASS`. `legs/registered.txt` names exactly T-K and T-C (§3).
- The Task 10 vehicle receipts are as in §1. The PR body came from the pinned `finalize.rev41.py`.
- The Task 11 H0 rehearsal (the rev45 producer `0c7124d7…` and instrument `9c9391d5…`): `population_producer_rc=0`, `census_rehearsal_rc=0`, one `result=PASS` line, tree_rows 81, A=3 B=76 C=2. rev49 SUPERSEDES that declaration for the landing, and it stays as the H0 record.
- THE LOCAL RECORD (R-4.88 operator arm (b)): `results/s2b-intg-substep2b-impl-1/` is RETAINED LOCALLY AND NOT PUBLISHED. It holds 2,342 manifest rows over 2,343 files; `SHA256SUMS` has sha256 `187a1a10613b637e6d4a2aa54ed6e8f9590dece65fc78a5078ec8a148c91791d`; `shasum -a 256 -c` gives rc 0; `git ls-files` on the path is EMPTY. **A reader of this packet cannot recompute the evidence it cites from the repository; it lives on the operator's host.**
- THE §7 WALK (`landing-2b/landing-walk-7.txt`): steps (0)–(5) ran end to end on a scratch clone of this lane at main `49a671f`, whose origin was a local bare repo holding main at B. Both pins resolved; the invariants held; the merge tree equaled the predicted tree `17437055…`, with 0 trailers and an empty product delta; the census gave `result=PASS` (109 rows, accepted_set=4, product 3/2); the predicate printed `record-untracked-ok`; the dry run and the ONE push gave rc 0, with ls-remote equal to the merge.
- THE LANDING CENSUS ARTIFACTS (rev49 and rev50), all tracked in `docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/`:
  - `census_population.rev49.sh`, `2d7dcdd6d73928b13a11c16287febd95ba660b360991251c943f3e39a77c42c6`;
  - `intg-2b-landing-census.sh`, `fbdfd311e73122e654b7afc1cc980b53bf41b0bfbfee7e56f292312de1be2ed4`;
  - `population-product-2b.txt`, `79b89c382ab60a349bb2a529f616a7cb23c20e98115ecf60b0a844df1bb21c00`. It holds the accepted-value SET of four `kind=sha256` tokens and the three frozen product rows `tests/test_adapter_codex_collect.cpp:383`, `:385` and `tests/test_cli.cpp:1181`, all class A. It is byte-equal whether produced at H or on each predicted merge measured (the pair's, master's and the implementer's, at three different `main` states).
  - `walk49.out`: the predicted merge and arm 6 PASS, and every must-be-NO arm STOPs on its own predicate. `landing-line-walk.txt`: the plan's extracted landing line PASSes on a fresh merge. `census-line-pin-check.txt`: the pin check YES, plus two must-be-NO mutants.

## 3. Registered residuals and consumed precedents — disclosed, with row attributions; none cited as green

- **R-4.35 / R-4.36.** The Linux `harness-selftest` family reds are pre-existing and attributed to no candidate. This draw at H has 3 failed, all in the family, with the population equal. `pass-r435-disclosed-registered-red` is that disclosure, not a pass. R-4.36 (m-4's correctness row) remains OPEN.
- **R-4.57 (T-ARM).** Arms 2/3/4 are unlanded (owner m-1). The legs that need them cannot execute at product scope, and the transitional fences stand as typed refusals.
- **R-4.62.** The host-sensitive probe-fixture poll was fixed in the candidate by m-3's own commit `3431bb7`, under arm (a).
- **T-K and T-C (legs registered).** FX-M-1 leg (k) has no product input that constructs its invocation, so it stays at the engine seam. a6·10 executes only if PROMPT C exists at B, which it does not.
- **T-NET** was RELEASED under A10 (`--network` executes A2 D3). **T-PROM** was RULED: `promisor_objects_unavailable` is a whole-operation typed refusal at pack only. **I2B-09 option (b)** is registered in the plan.
- **R-4.88 arm (b).** The 2,343-file record is local and unpublished (§2). The consequence is stated plainly: the evidence gating this merge cannot be verified off this host. The structural `.gitignore` entry for `results/s2b-*/` is a registered residual for the next sprint, not this landing. The landing guards against an accidental commit with the rev48 predicate (§7).
- **R-4.90, R-4.92 and R-4.93: the landing census re-shape.** The value set came from master 211118 and the location shape from operator arm (a) (master 212748). Both executed lines are pinned (master 233421). All are DISCHARGED at rev50 by master (`001609`).
- **The synthetic `ghp_`-shaped control (digest `f419886e…`), a consumed precedent.** I wrote it into rev42's walk as a secret-in-patch negative control. It is not a credential: 34 characters against a real token's 40, the lowercase alphabet then four digits. It is classified B, a non-product fixture copy. It is published by this landing, so it is disclosed here and never cited as green.
- **R-4.52: the landing rule.** The docs-lane commits above the pin ride the landing push; see §4.

## 4. Blast radius (measured, not assumed; 2026-09-29 at the pair-planner's seat, before this packet's own commit)

- `git merge-base main H` == B. `git rev-list --count origin/main..H^` = 25 is the branch's OWN lineage.
- Branch delta: `git rev-list --count B..H` = 26.
- Local `main` = `49a671f23dda2d63a05944c3e59f7a902a2308e7`. `git rev-list --count origin/main..main` = 352 commits ABOVE the published sha, ALL in the docs lane: `git diff --numstat B main` over src, tests, CMakeLists.txt, harness, .github, schemas, tools and cmake gives 0 lines, and every path touched in B..main is under `docs/` or `.relays/`. Every one carries a placeholder `@local` author and committer (`intg.pair-implementer@local`, `intg.pair-planner@local`) and 0 `Co-Authored-By` lines. They ride the landing push under R-4.52.
- `git merge-tree --write-tree main H` gives rc 0 with predicted tree `17437055f99e90bd3819e2a8078dd4a67a5f10e2` at this snapshot, and 0 conflicts. The path overlap between B..H and B..main (`comm -12`) is 0.
- THE BINDING FACE of this section is its INVARIANTS: H, B, `merge-base main H == B`, the non-docs delta B..main EMPTY, the overlap 0, and `merge-tree` clean. The counts and the predicted tree are a timestamped snapshot that moves with the docs lane; §7 step (1) RE-DERIVES them at landing.
- The census does not churn with this growth: the pinned population carries only the product rows (R-4.92 arm (a)). Three `main` states have been measured with the same population.

## 5. Review record

```text
owner byte review  m-1 DESIGN-planner-20260927-033430.md          sha256 6b80add596bb1762e33081251c58628c9bb5c403febb5dd41d5401ad6dba9892  H cb19326a: no red
owner byte review  m-3 DESIGN-planner-20260927-033409.md          sha256 49ab6231dfcbd7d81698779f56bf50f3e5e98e2573c53420e85a65ffa195f2bd  H cb19326a: no red (MUST-H-1 closed at c10)
owner byte review  m-4 DESIGN-REVIEW-planner-20260927-033613.md   sha256 3513f437041490e8fcf05ac42e3682519d884b342b1bd07402e1284250d7c15e  H cb19326a: no-red (security)
                   each tracked and unmodified in ../pdc, re-hashed at this seat equal to master's pins (203750 §2); bound by the GO before Task 10
GO                 intg-substep2b/SITREP-pair-planner-20260927-202731.md   the protocol-(e) pointer consumed by the controller's Task 10 gate
plan               PLAN-REVIEW-pair-implementer-20260929-020827 (plan-review-52)   rev50 7a2b894a APPROVED exact-hash; rev48 acb2ac80 by plan-review-50 before it
master             233421 (rev49 verified + the census-line pin), 001609 (R-4.93 discharged), 023528 (the T-ORACLE carry at rev50)
rulings            master 211118 (accepted-value SET; classifications); operator arm (a) on R-4.92 via master 212748; operator arm (b) on R-4.88 via master 024840
tokens             IMPL-pair-planner intg-substep2b-impl-1 … impl-17; Task 11 returned 021324 rc 0, accepted by master 023917
```

No pair-tier adversarial panel was run on H. As at R-4.49 and R-4.50, master's shape names the owner byte reviews as the review cells. A panel at the exact sha remains available on master's word before cell 4.

## 6. The condition census (the four-condition bar)

```text
cell 1  local suites at the exact sha, both platforms — DONE at H: the c11 head gate (tidy 0, coverage 37/37, macOS five producers rc 0 failures 0, Linux failures 0); tuples as §2; final count gates rc 0 both targets; harness-selftest under the bar pass-r435-disclosed-registered-red (3 in family, population 1055 equal)
cell 2  the Docker parity leg REACHED ctest — DONE at H: container_rc=0 (ubuntu:24.04, linux/amd64, --init, nofile soft == hard); every JUnit read (heads/c11/tuples-linux.txt, xml sha256 per row)
cell 3  the owner reviews at the exact sha — DONE: m-1 033430, m-3 033409, m-4 033613, all no-red at H cb19326a (§5)
cell 4  the operator's condition-4 merge token on H — PENDING; presented by master on this packet's return after the Master Reviewer's verification; issues as a BARE `DISPATCH MERGE` to intg.pair-implementer, filed under ../bivpak/.relays/intg/ (grantor set excludes the pair-planner); preceded by the operator's undraft of PR #28; nothing in this packet is or substitutes for it
master's own-bytes verification of head / base / merge-tree / delta / packet-face — master's act on this packet's return
```

## 7. Hold

Assembled and HELD at H. Cells 1–3 are DONE; cell 4 is PENDING. The pair does not merge on its own word, and the pair-planner never runs a merge or a push.

If the token issues, THE LANDING EXECUTES AS ONE SEQUENCE AT THE IMPLEMENTER'S SEAT UNDER R-4.52. Each step's expectation is WRITTEN FIRST, each receipt goes into `/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB/landing/` (absent today), and every receipt is reported UP. Any STOP means NO push.
- **(0) The two pins, per the plan's LANDING row (rev50).** Extract the single plan line that, after `strip()`, begins with a backtick plus `STOP(){ printf` and ends with a backtick, remove the backticks, and require 327 bytes at sha256 `2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5`. Do the same for the census prefix, requiring 221 bytes at sha256 `af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad`, checked before substitution. Any count other than one, or any mismatch, is a STOP.
- **(1) Re-derive `main`-before** (`git rev-parse main`) and re-check §4's invariants: `merge-base main H == B`, the non-docs delta B..main EMPTY, the overlap 0, and `git merge-tree --write-tree main H` clean, with its tree recorded as the PREDICTED tree.
- **(2) The TRUE local merge on lane-local `main`:** `git merge --no-ff --no-edit -m 'Merge intg/substep2b-wiring at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (sub-step 2b wiring act: 26 commits B..H over 186adf7d67171bd7afe621f39b657a1a113ce299; PR #28)' cb19326a5596bf30eab2ec2b9baeda0bc77be895`.
  - Its parents are `main`-before and H, and its tree must equal the PREDICTED tree.
  - The message carries NO `Co-Authored-By` trailer (`git interpret-trailers --parse` EMPTY).
  - `git diff --numstat H merge` over src, tests, CMakeLists.txt, harness, .github, schemas, tools and cmake must be EMPTY.
- **(3) The census of record at the merge commit, BEFORE the push.** Re-hash the three inputs first (`fbdfd311…`, `79b89c38…`, and the producer `2d7dcdd6…` for provenance). Then run the pinned census line with `<merge>` = the merge sha in BOTH positions, from the repository root. Expect exit 0 and ONE last line ending `result=PASS`; `product_tree_rows=3`, `product_history_paths=2`, and `accepted_set=4`. `tree_rows`, `history_paths` and `commits` are DATA. The receipt is `/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB/landing/landing-census.txt`. Exit 1 means NO push.
- **(4) The R-4.88 no-commit predicate:** the pinned 327-byte line as its own `bash`. Expect `record-untracked-ok` at rc 0. Anything else means NO push.
- **(5) The push.** With `M` holding the merge sha, the refspec is written brace-quoted as `"${M}:refs/heads/main"`. In zsh a bare `$M:refs…` fires the `:r` history modifier and mangles the refspec; the walk reproduced this. First `git push --dry-run origin "${M}:refs/heads/main"` (rc 0, expected `186adf7..<merge>`). Then ONE non-force attempt, `git push origin "${M}:refs/heads/main"`. Immediately after, `git ls-remote origin refs/heads/main` must equal the merge sha (class a). The attempt is SPENT on use: no retry, no force, no tags, no `main:main`.
- **(6) Observe only:** `gh pr view 28 --json state,mergedAt,mergeCommit,headRefOid`, expecting MERGED at the pushed sha. That is a remote observation; no forge merge act is taken. Then report UP through the pair-planner to master, and Task 12 follows (final pin, four worktrees disposed, the closure SITREP citing the local record by `187a1a10…`).

Merge is not push is not release: no tag, no release act, no deployment. The operator's release hold remains ABSOLUTE.

## 8. Landed

(Written only after the fact.)
