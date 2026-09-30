# Merge packet — sub-step 2b wiring act (revision 2, 2026-09-30, at the pair-planner's seat; HELD at H)

Revision 2 supersedes revision 1 (sha256 `ac3186b47448cbdade776fd494853acec5eff9bbaa62fb48b0b1eecde6554b11`, commit `148ab1a`), which the Master Reviewer returned MUST-REVISE on F-2B-VP-1 (`MERGE-GATE-master-reviewer-20260929-041058.md`).
What moved: the plan of record (rev53), §7's pins and record clauses, the §7 walk, §4's snapshot, and the review rows. §§2 evidence at H, 3 residuals and 6 cells 1–3 are unchanged except where a line names what moved.

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
- Plan of record: `plans/PL-intg-substep2b-20260915.md` revision 53 @ sha256 `4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1` (commit `3a23e92`), APPROVED at the exact hash by the implementer (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md`, plan-review-54, covering the complete rev51→rev53 delta).
  - Master verified it at its own bytes and filed the fresh T-ORACLE carry (`PLAN-master-planner-20260930-012837.md`).
  - `t-oracle.txt` was rewritten from that carry with its predecessor preserved, and the real prefix returned rc 0 (`results/rev52-walks/t-oracle-rewrite-rev53.txt`). The first attempt used a scratch prefix a sweep had deleted: rc 127, no receipt. That record is kept as `t-oracle-rewrite-rev53.prev-20260930-013506.txt`, and the prefix was re-extracted from the plan by content (lines 1288–1343, `1c437ac4…`).
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
- THE §7 WALK, revision 2 (`landing-2b/landing-walk-7r2.txt`, driver `landing-walk-7r2.sh`): the driver EXTRACTS §7's fenced `zsh` blocks from THIS packet and runs them, unedited, in one `zsh -f`, in a scratch clone whose origin is a local bare repo holding main at B. The walked script `run.zsh` has sha256 prefix `29d2fd58`.
  - **YES** at main `d787f53`: three pins; pre-check and history pre-check ok; merge tree == predicted `7a243de7…`; census `result=PASS` (109 rows, accepted_set=4, product 3/2); `record-untracked-ok`; `record-history-clean-ok`; dry run and ONE push rc 0; remote main == M.
  - **NO-a** (a graft file): STOP at the step (1) pre-check, no merge made.
  - **NO-b** (a record committed then removed on main): the step (1) history pre-check STOPs `record-in-history-2`, no merge made.
  - **NO-d** (the same history with the pre-check removed): the step (4) gate STOPs after the merge.
  - **NO-c** (`$EVID/landing` present): STOP at step (0).
  - In every NO arm the remote stays at B.
  - The first draw of this walk (kept as `landing-walk-7r2.prev-*.txt`) had no history pre-check: its NO-b merged and then STOPped at step (4). That is why step (1) now runs the pinned history line on both parents. The revision 1 walk (`landing-2b/landing-walk-7.txt`) is kept as its record.
- THE RECORD-CLAUSE WALKS (plan rev51→rev53): `results/rev51-walks/walk51.out` (C1–C10) and `results/rev52-walks/walk53.out` (C1–C17). Committed-then-removed, TREESAME side history, replace refs, legacy grafts (in-repo and via `GIT_GRAFT_FILE`), shallow, a forged commit-graph, and every producer fault each STOP; the clean history passes before and after. The implementer independently re-ran walk53 at main `2a04ca1`, and master rebuilt F-2B-VP-1's own control at `70aa3840` (012837).
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
- **R-4.88 arm (b).** The 2,343-file record is local and unpublished (§2). The consequence is stated plainly: the evidence gating this merge cannot be verified off this host. The structural `.gitignore` entry for `results/s2b-*/` is a registered residual for the next sprint, not this landing. The landing guards the record with TWO pinned clauses (§7 step (4)): the rev48 index clause, and the rev53 history clause over the literal merge sha. R-4.95 (master 012837): arm (b) is RULED PATH-SCOPED; content elsewhere is the global value census's business.
- **F-2B-VP-1 (the Master Reviewer, 041058) and MUST-2B-59 (the implementer, 231628): CLOSED at rev53.** The index-only guard missed published history (rev51), and legacy grafts bent rev51's query (rev53). Master verified the closure at its own bytes (012837).
- **R-4.90, R-4.92 and R-4.93: the landing census re-shape.** The value set came from master 211118 and the location shape from operator arm (a) (master 212748). Both executed lines are pinned (master 233421). All are DISCHARGED at rev50 by master (`001609`).
- **The synthetic `ghp_`-shaped control (digest `f419886e…`), a consumed precedent.** I wrote it into rev42's walk as a secret-in-patch negative control. It is not a credential: 34 characters against a real token's 40, the lowercase alphabet then four digits. It is classified B, a non-product fixture copy. It is published by this landing, so it is disclosed here and never cited as green.
- **R-4.52: the landing rule.** The docs-lane commits above the pin ride the landing push; see §4.

## 4. Blast radius (measured, not assumed; 2026-09-30 at the pair-planner's seat, before this revision's own commit)

- `git merge-base main H` == B. `git rev-list --count origin/main..H^` = 25 is the branch's OWN lineage.
- Branch delta: `git rev-list --count B..H` = 26.
- Local `main` = `d787f53a57dedd3a10629571fc411b2c6d7eb434`. `git rev-list --count origin/main..main` = 369 commits ABOVE the published sha, ALL in the docs lane:
  - `git diff --numstat B main` over src, tests, CMakeLists.txt, harness, .github, schemas, tools and cmake gives 0 lines, and every path touched in B..main is under `docs/` or `.relays/`;
  - every one carries a placeholder `@local` author and committer (`intg.pair-implementer@local`, `intg.pair-planner@local`) and 0 `Co-Authored-By` lines;
  - they ride the landing push under R-4.52.
- `git merge-tree --write-tree main H` gives rc 0 with predicted tree `7a243de7d7faffa0a8ae3d646bf303488beec727` at this snapshot, and 0 conflicts. The path overlap between B..H and B..main (`comm -12`) is 0.
- The record at this snapshot: `git ls-files` on the record path gives 0, and the rev53 history query over `main` gives 0 commits. The effective graft file is absent, the repository is not shallow, there are 0 replace refs, and a commit-graph is present, which the history clause bypasses.
- THE BINDING FACE of this section is its INVARIANTS: H, B, `merge-base main H == B`, the non-docs delta B..main EMPTY, the overlap 0, and `merge-tree` clean. The counts and the predicted tree are a timestamped snapshot that moves with the docs lane; §7 step (1) RE-DERIVES them at landing.
- The census does not churn with this growth: the pinned population carries only the product rows (R-4.92 arm (a)).

## 5. Review record

```text
owner byte review  m-1 DESIGN-planner-20260927-033430.md          sha256 6b80add596bb1762e33081251c58628c9bb5c403febb5dd41d5401ad6dba9892  H cb19326a: no red
owner byte review  m-3 DESIGN-planner-20260927-033409.md          sha256 49ab6231dfcbd7d81698779f56bf50f3e5e98e2573c53420e85a65ffa195f2bd  H cb19326a: no red (MUST-H-1 closed at c10)
owner byte review  m-4 DESIGN-REVIEW-planner-20260927-033613.md   sha256 3513f437041490e8fcf05ac42e3682519d884b342b1bd07402e1284250d7c15e  H cb19326a: no-red (security)
                   each tracked and unmodified in ../pdc, re-hashed at this seat equal to master's pins (203750 §2); bound by the GO before Task 10
GO                 intg-substep2b/SITREP-pair-planner-20260927-202731.md   the protocol-(e) pointer consumed by the controller's Task 10 gate
plan               PLAN-REVIEW-pair-implementer-20260930-001212 (plan-review-54)   rev53 4832b147 APPROVED exact-hash; rev51 7c723a1b MUST-REVISED by plan-review-53 (MUST-2B-59); rev50 7a2b894a by plan-review-52 before it
packet rev 1       ac3186b4 @ 148ab1a   MUST-REVISE by the Master Reviewer, MERGE-GATE-master-reviewer-20260929-041058 (F-2B-VP-1)
master             233421 (rev49 verified + the census-line pin), 001609 (R-4.93 discharged), 163054 (F-2B-VP-1 accepted and routed), 012837 (rev53 verified; the T-ORACLE carry at rev53; R-4.95)
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

If the token issues, THE LANDING EXECUTES AS ONE SEQUENCE AT THE IMPLEMENTER'S SEAT UNDER R-4.52:
- It runs in ONE fresh `zsh -f` started for the landing. A STOP `exit`s that shell and nothing after it runs; any STOP means NO push.
- The working directory is the docs-lane root `/Users/jack/Programming/bivpak`.
- `EVID` is set to `/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB` and exported. Every receipt lands in `$EVID/landing/`, which step (0) creates, and every receipt is reported UP.
- Each step's expectation is written first. The blocks below are the exact commands; the §2 walk ran these same blocks, extracted from this file, unedited.

**(0) Three pins, per the plan's LANDING row (rev53).** Each executed line is the single plan line that, after `strip()`, begins with a backtick plus its prefix and ends with a backtick; the backticks are removed. The lines are checked BEFORE `<merge>` is substituted: index 327 bytes `2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5`, census 221 bytes `af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad`, history 1150 bytes `bcbb5c978ee3a6c8729734da1dca0aae5ab45538f60813e978fbc0726a177610`. Any other count, length or digest is a STOP.

```zsh
set -o pipefail
[ -n "${EVID:-}" ] || { print -r -- 'STOP evid-unset'; exit 1; }; export EVID
[ "$(git rev-parse --show-toplevel)" = "$(pwd -P)" ] || { print -r -- 'STOP not-at-repo-root'; exit 1; }
LD=$EVID/landing; [ ! -e "$LD" ] && [ ! -L "$LD" ] || { print -r -- 'STOP landing-dir-exists'; exit 1; }; mkdir "$LD" || exit 1
PLAN=docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
python3 - "$PLAN" "$LD" <<'PY' || exit 1
import sys, hashlib
plan, ld = sys.argv[1], sys.argv[2]
L = open(plan).read().split("\n")
pins = [("index", "STOP(){ printf", 327, "2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5"),
        ("census", "bash docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/intg-2b-landing-census.sh", 221, "af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad"),
        ("history", "HREF=<merge>;", 1150, "bcbb5c978ee3a6c8729734da1dca0aae5ab45538f60813e978fbc0726a177610")]
for name, pre, n, d in pins:
    m = [x.strip()[1:-1] for x in L if x.strip().startswith("`" + pre) and x.strip().endswith("`")]
    b = m[0].encode() if len(m) == 1 else b""
    if len(m) != 1 or len(b) != n or hashlib.sha256(b).hexdigest() != d:
        print("STOP pin-%s count=%d" % (name, len(m))); sys.exit(1)
    open("%s/pin-%s.txt" % (ld, name), "wb").write(b)
    print("pin-%s ok bytes=%d sha256=%s" % (name, n, d[:8]))
PY
```

**(1) Re-derive `main`-before and re-check §4's invariants, then the ADVISORY pre-check.** The invariants are `merge-base main H == B`, the non-docs delta B..main EMPTY, the overlap 0, and `git merge-tree --write-tree main H` clean, its tree recorded as PREDICTED. The advisory pre-check (master 012837 §7) asks, BEFORE the merge, the two repository-state conditions of the history clause, plus zero replace refs. It then runs the PINNED history line itself with `<merge>` = `main`-before and again with `<merge>` = H. Every commit reachable from the merge other than the merge commit itself is reachable from one of those two parents, so a record already in either history STOPs here rather than after a merge the token has paid for. The revision 2 walk's first draw measured that merge-then-STOP case. It is insurance, not a second authority: the pinned history line in step (4) remains the only record gate.

```zsh
H=cb19326a5596bf30eab2ec2b9baeda0bc77be895; B=186adf7d67171bd7afe621f39b657a1a113ce299
MB=$(git rev-parse --verify main) || exit 1
[ "$(git merge-base "$MB" "$H")" = "$B" ] || { print -r -- 'STOP merge-base'; exit 1; }
n=$(git diff --numstat "$B" "$MB" -- src tests CMakeLists.txt harness .github schemas tools cmake | wc -l | tr -d ' ') || exit 1; [ "$n" = 0 ] || { print -r -- "STOP nondocs-$n"; exit 1; }
a=$(git diff --name-only "$B" "$H" | sort) || exit 1; b=$(git diff --name-only "$B" "$MB" | sort) || exit 1
o=$(comm -12 <(print -r -- "$a") <(print -r -- "$b") | wc -l | tr -d ' ') || exit 1; [ "$o" = 0 ] || { print -r -- "STOP overlap-$o"; exit 1; }
PT=$(git merge-tree --write-tree "$MB" "$H") || { print -r -- 'STOP merge-tree'; exit 1; }; [[ $PT =~ '^[0-9a-f]{40}$' ]] || { print -r -- 'STOP merge-tree-shape'; exit 1; }
g=0; GF=$(git rev-parse --git-path info/grafts) || g=$?; s=0; SH=$(git rev-parse --is-shallow-repository) || s=$?; rr=$(git for-each-ref refs/replace | wc -l | tr -d ' ') || exit 1
[ "$g" -eq 0 ] && [ -n "$GF" ] && [ ! -e "$GF" ] && [ ! -L "$GF" ] && [ "$s" -eq 0 ] && [ "$SH" = false ] && [ "$rr" = 0 ] || { print -r -- "STOP precheck graft-rc=$g shallow=$SH replace=$rr"; exit 1; }
for ref in "$MB" "$H"; do
  python3 -c 'import sys; s=open(sys.argv[1]).read(); assert s.count("<merge>")==int(sys.argv[3]); sys.stdout.write(s.replace("<merge>", sys.argv[2]))' "$LD/pin-history.txt" "$ref" 1 > "$LD/pre-history-$ref.sh" || { print -r -- 'STOP precheck-history-subst'; exit 1; }
  r=0; o=$(bash "$LD/pre-history-$ref.sh" 2>&1) || r=$?; [ "$r" -eq 0 ] && [ "$o" = record-history-clean-ok ] || { print -r -- "STOP precheck-history-$ref rc=$r $o"; exit 1; }; done
print -r -- "main-before=$MB predicted=$PT precheck-ok precheck-history-ok" | tee "$LD/step1.txt"
```

**(2) The TRUE local merge on lane-local `main`, then the merge sha DERIVED ONCE.**
- `M` is read once from `HEAD` immediately after the merge, checked as 40 lowercase hex, and made read-only (`typeset -r`).
- That one value is substituted into the census (both positions) and the history clause, and it is the push refspec. It is never re-read.
- Because the history reachable from a given sha is immutable, this closes time-of-check/time-of-use by construction (master 012837).
- The parents are `main`-before and H, and the tree must equal PREDICTED.
- The message carries NO trailer.
- The product delta H..M is EMPTY.

```zsh
git merge --no-ff --no-edit -m 'Merge intg/substep2b-wiring at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (sub-step 2b wiring act: 26 commits B..H over 186adf7d67171bd7afe621f39b657a1a113ce299; PR #28)' "$H" || { print -r -- 'STOP merge'; exit 1; }
M=$(git rev-parse --verify HEAD) || exit 1; [[ $M =~ '^[0-9a-f]{40}$' ]] || { print -r -- 'STOP merge-sha-shape'; exit 1; }; typeset -r M
[ "$(git rev-parse "${M}^1")" = "$MB" ] && [ "$(git rev-parse "${M}^2")" = "$H" ] && ! git rev-parse -q --verify "${M}^3" >/dev/null || { print -r -- 'STOP parents'; exit 1; }
[ "$(git rev-parse "${M}^{tree}")" = "$PT" ] || { print -r -- 'STOP tree-not-predicted'; exit 1; }
t=$(git log -1 --format=%B "$M" | git interpret-trailers --parse) || exit 1; [ -z "$t" ] || { print -r -- 'STOP trailer'; exit 1; }
d=$(git diff --numstat "$H" "$M" -- src tests CMakeLists.txt harness .github schemas tools cmake) || exit 1; [ -z "$d" ] || { print -r -- 'STOP product-delta'; exit 1; }
print -r -- "M=$M" | tee "$LD/step2.txt"
```

**(3) The census of record at M, BEFORE the push.** It re-hashes the three inputs first (`fbdfd311…`, `79b89c38…`, and the producer `2d7dcdd6…` for provenance), then runs the pinned census line with `<merge>` = M in BOTH positions. Expect exit 0 and ONE last line ending `result=PASS`, with `product_tree_rows=3`, `product_history_paths=2` and `accepted_set=4`. `tree_rows`, `history_paths` and `commits` are DATA. The receipt is `$EVID/landing/landing-census.txt`. Exit 1 means NO push.

```zsh
LB=docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b
for pair in intg-2b-landing-census.sh:fbdfd311e73122e654b7afc1cc980b53bf41b0bfbfee7e56f292312de1be2ed4 population-product-2b.txt:79b89c382ab60a349bb2a529f616a7cb23c20e98115ecf60b0a844df1bb21c00 census_population.rev49.sh:2d7dcdd6d73928b13a11c16287febd95ba660b360991251c943f3e39a77c42c6; do
  f=${pair%%:*}; want=${pair##*:}; got=$(shasum -a 256 "$LB/$f" | cut -c1-64) || exit 1; [ "$got" = "$want" ] || { print -r -- "STOP input-$f"; exit 1; }; done
python3 -c 'import sys; s=open(sys.argv[1]).read(); assert s.count("<merge>")==int(sys.argv[3]); sys.stdout.write(s.replace("<merge>", sys.argv[2]))' "$LD/pin-census.txt" "$M" 2 > "$LD/run-census.sh" || { print -r -- 'STOP census-subst'; exit 1; }
r=0; bash "$LD/run-census.sh" > "$LD/landing-census.txt" || r=$?; last=$(tail -1 "$LD/landing-census.txt"); print -r -- "census rc=$r $last"
[ "$r" -eq 0 ] && [[ $last == *' result=PASS' ]] && [[ $last == *' accepted_set=4 '* ]] && [[ $last == *' product_tree_rows=3 product_history_paths=2 '* ]] || { print -r -- 'STOP census'; exit 1; }
```

**(4) The two R-4.88 record clauses, each as its own `bash`:**
- the index clause, which must print `record-untracked-ok` at rc 0;
- then the history clause with `<merge>` = M, which must print `record-history-clean-ok` at rc 0.

Anything else means NO push. The receipts are `record-index.txt` and `record-history.txt`.

```zsh
r=0; o=$(bash "$LD/pin-index.txt" 2>&1) || r=$?; print -r -- "index rc=$r $o" | tee "$LD/record-index.txt"; [ "$r" -eq 0 ] && [ "$o" = record-untracked-ok ] || { print -r -- 'STOP record-index'; exit 1; }
python3 -c 'import sys; s=open(sys.argv[1]).read(); assert s.count("<merge>")==int(sys.argv[3]); sys.stdout.write(s.replace("<merge>", sys.argv[2]))' "$LD/pin-history.txt" "$M" 1 > "$LD/run-history.sh" || { print -r -- 'STOP history-subst'; exit 1; }
r=0; o=$(bash "$LD/run-history.sh" 2>&1) || r=$?; print -r -- "history rc=$r $o" | tee "$LD/record-history.txt"; [ "$r" -eq 0 ] && [ "$o" = record-history-clean-ok ] || { print -r -- 'STOP record-history'; exit 1; }
```

**(5) The push of M.** The refspec is brace-quoted (`"${M}:refs/heads/main"`): in zsh a bare `$M:refs…` fires the `:r` history modifier (the revision 1 walk reproduced it). First the dry run, expecting rc 0 and `186adf7..<M>`. Then ONE non-force attempt. Immediately after, `git ls-remote origin refs/heads/main` must equal M (class a). The attempt is SPENT on use: no retry, no force, no tags, no `main:main`.

```zsh
r=0; git push --dry-run origin "${M}:refs/heads/main" > "$LD/push-dry-run.txt" 2>&1 || r=$?; cat "$LD/push-dry-run.txt"; [ "$r" -eq 0 ] || { print -r -- "STOP dry-run-rc-$r"; exit 1; }
r=0; git push origin "${M}:refs/heads/main" > "$LD/push.txt" 2>&1 || r=$?; cat "$LD/push.txt"; print -r -- "push rc=$r" | tee -a "$LD/push.txt"
rm_=$(git ls-remote origin refs/heads/main | cut -f1) || exit 1; print -r -- "ls-remote main=$rm_" | tee -a "$LD/push.txt"; [ "$r" -eq 0 ] && [ "$rm_" = "$M" ] || { print -r -- 'STOP push-not-class-a'; exit 1; }
```

**(6) Observe only:** `gh pr view 28 --json state,mergedAt,mergeCommit,headRefOid`, expecting MERGED at M. That is a remote observation; no forge merge act is taken. Then report UP through the pair-planner to master. Task 12 follows: the final pin, four worktrees disposed, and the closure SITREP citing the local record by `187a1a10…`.

Merge is not push is not release: no tag, no release act, no deployment. The operator's release hold remains ABSOLUTE.

## 8. Landed

(Written only after the fact.)
