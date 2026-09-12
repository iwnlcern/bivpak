# Merge packet — R-4.50 claude-discover parity (assembled 2026-09-12 06:21 PDT, HELD at cell 4)

Every value below was MEASURED at the pair-planner's seat by the command named beside it immediately before this file was written; a failed check would have withheld the file.
The candidate worktree, the evidence home and the runners directory were read only.
Merged is not pushed; pushed is not released. The release hold is ABSOLUTE.

## 1. Candidate identity

- Candidate head H = `8509157c41c5ef66595d655f39eee5107081bd32` (`git -C ../bivpak-intg-r450-discover-parity rev-parse HEAD`; status EMPTY); H^ = C = `961b1ccd0ba488f909357d4cac1abab8c77d2fa8`; H^^ = B = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` (the cut point == the PUBLISHED pin).
- B = origin/main = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` (`git ls-remote origin refs/heads/main`, re-read at assembly).
- Remote branch `refs/heads/intg/r450-discover-parity` = `8509157c41c5ef66595d655f39eee5107081bd32` (== H; pushed ONCE under token 12 Task 8, class a).
- PR #25 `https://github.com/iwnlcern/bivpak/pull/25` — `gh pr view 25 --json state,isDraft,baseRefName,headRefOid,mergeable`: `OPEN false main 8509157c41c5ef66595d655f39eee5107081bd32 MERGEABLE` (the VEHICLE under R-4.51 clause (2); remote CI is not evidence and is cited nowhere in this packet).
- Two commits, two owners (arm A of master `041131`): C = m-2's fence (`m2-r450-discover-fence-rev2-20260903` @ `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`) + the two count-gate cells (m-3, CG-R7.5); H = m-3's harness follow-through under the iso design (write set designed at iso rev8 `00046a65…`; ACCEPTED under the approved iso rev13 `f72919d984860684450d8394d74191a423f525fd5be787f64fe681dc7a13f9ce` @ pdc `2b24e40`, Master Reviewer `133947`).
- B→C numstat (`git diff --numstat B C`): `2 2 .github/workflows/s2-harness.yml;12 13 src/adapters/claude_code/claude_code.cpp;183 0 tests/test_adapter_claude_collect.cpp;`
- C→H numstat (`git diff --numstat C H`): `1 1 harness/bivharness/e3.py;9 5 harness/selftest/stub_biv.py;2 2 harness/selftest/test_store_isolation.py;`
- Plan of record: `plans/PL-intg-r450-discover-parity-20260906.md` revision 19 @ sha256 `777f8c20d1f19566bdd9096c40b70c0ce3b5136d865b6cf7eca70cb260ffbda7` (commit `af88bec`), APPROVED at the exact hash by the implementer (`intg-r450/PLAN-REVIEW-pair-implementer-20260911-172709.md`).
- Tokens, in order (every one a bare token from the pair-planner to the implementer under the grant's delegated conditional dispatch): impl `173252`, impl-2 `194721`, impl-3 `170416`, impl-4 `181632`, impl-5 `032041`, impl-6 `060748`, impl-7 `143301`, impl-8 `021109`, impl-9 `031538`, impl-10 `080920`, impl-11 `125456` (tokens 1–11 CONSUMED by STOPs; C and H were created under token 11 outside the runner protocol — the breach of record, master `164408` state (iii)); impl-12 `intg-r450/IMPL-pair-planner-20260911-173616.md` — Tasks 0 → 9 EXECUTED through the per-task runner protocol, every controller receipt rc 0 (`intg-r450/IMPL-pair-implementer-20260912-041415.md`, `intg-r450/SITREP-pair-implementer-20260912-061500.md`).
- Disclosed, not corrected: C's and H's commit messages each carry one `Co-Authored-By: Claude …` trailer (against the operator's global no-co-author rule); H's message pins iso rev8 and plan rev11 `97bef383` — history of its creation under token 11, superseded on the record by the pins above. Master `055933` / m-3: do NOT rewrite (every pin, receipt and review binds these shas); the operator rules.

## 2. Evidence chain (all at the exact SHA)

- THE TRACKED RECORD `results/r450-intg-r450-discover-parity-impl-12/` — 696 files = the 695-file evidence-of-record SET + `SHA256SUMS` (695 lines; sha256 `fc41034c0f86a4861d457526f8d77d4e3b2c81a0e200b7fb8701540360f125b8`), committed `1ef791a3cf7f07abbadc9161ecdc089b96836188` (696 files, 0 outside the directory, no trailer). Re-verified at this seat: `shasum -a 256 -c --quiet SHA256SUMS` rc 0; the plan's own `finalize.py check <home> <resdir> <manifest>` rc 0 — `set=695 tree=695 manifest=695 equal=yes digests=ok copies=ok`.
- The controller receipts (`r450-runners-NYQq7P`): `task-0.done` … `task-9.done` and every `.exit` `rc=0`; every `proof-N.txt` `bytes=equal … rc=0`; the ten materialized `task-N.sh` hash EQUAL to the runners the pair-planner derived from the approved artifact (10 of 10); `plan-lock.txt` == `plan-hash.txt` == `777f8c20…`.
- macOS acceptance at H: `ctest --preset ci-macos` rc 0 (`H/ctest-macos-H.rc` = `ctest_macos_H_rc=0`); the whole harness selftest at H `1014 passed in 14.88s` rc 0; discriminator `rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS`; the HOME demonstration `rp_rc=0`, four mutants red on exactly their own locator.
- Linux acceptance at H (the parity container, CG-R2 topology, `--init`, nofile soft == hard): Phase-S ledger 26 required identities 0 + `suite_aggregate_rc=0 ledger_write_failed=0`, head receipt `expected == observed` at H; ctest rc 8 with the failing set EXACTLY `harness-selftest`; the iso rev13 (a)–(h) bar receipt: `rcL=8 a_rows_rc=0 summary_H=parsed failed_H=2 names_H=selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite, foreign_H= d_tripwire_lines=0 d_family_files_rc=0 population_H=1013 rcB=8 base_rows=1 base_rows_rc=0 summary_B=parsed failed_B=3 names_B=selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite,selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open, foreign_B= population_B=1013 bar=pass-r435-disclosed-registered-red` — a VALID CANDIDATE RED (2 == 2 ⊆ the four) with clause (f)'s base draw taken IN THIS TOKEN at B (a fourth container run; VALID, SHOWS 3 == 3 ⊆ the four), C-1 disjoint touch and C-2 populations 1013 == 1013 holding → `pass-r435-disclosed-registered-red`, the plan's second admitted outcome under the ACCEPTANCE GATE OF RECORD (master `134909`).
- P and C observed on both targets (ten tuples each, `gate.py` 10/10 `equal=yes` at C and at H); the census of record at H: `census-tree.delta` and `census-history.delta` EMPTY (tree: the three known fixture-filename locations; history: the two known test files; nothing undisclosed).
- The pair-planner's verifications: `intg-r450/SITREP-pair-planner-20260912-044104.md` (Tasks 0–7) and this packet (Tasks 8–9); the rev19 validation on the plan's bytes before any token: controls 34/34, fixtures 18/18 incl. the real green-log cases, the whole protocol rehearsed Task 0 → 9 (`results/rehearsal-r450-rev19-{controls,fbar,flow}-20260911.txt`).

## 3. Registered residual reds — disclosed, with row attributions; none cited as green

- R-4.35 — the Linux `harness-selftest` R-4.35 family reds are PRE-EXISTING, flaky in their per-draw subset, attributed to no candidate (registry row; the base draw at B in this token showed 3 of the four, H 2 of the four — every name inside the family). The bar's outcome `pass-r435-disclosed-registered-red` is that disclosure, not a pass of the test.
- R-4.36 — the correctness question underneath R-4.35 (the TOCTOU detector's timing dependence) is m-4's row, NOT SHIFTED by this act (m-4's `165351` ground held: C-2 populations equal; samples receipted by m-3 `053914`).
- R-4.38 — the count gate's two `biv_tests` `successes` cells were transcribed in C (`:85` 418→419, `:326` 420→421) from the OBSERVED P tuples — R-4.38's own principle ("a pin is a transcription of the merged bytes"); m-3's hunk review NO FINDING.
- Not a registry row: the `Co-Authored-By` trailers on C and H (§1); the operator rules; no rewrite.
- No remote-CI result and no waiver is cited anywhere in this packet.

## 4. Blast radius (measured, not assumed; 2026-09-12 06:21 PDT at the pair-planner's seat)

- `git merge-base main H` = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` == B (the branch cut point IS the published pin; `git rev-list --count B..H^` counts the branch's OWN lineage — no unpublished base rides in from the branch side).
- Branch delta: `git rev-list --count B..H` = 2 (C and H).
- Local `main` = `1ef791a3cf7f07abbadc9161ecdc089b96836188`, `git rev-list --count origin/main..main` = 139 commits ABOVE the published sha — ALL docs-lane (`git diff --numstat B main -- src tests CMakeLists.txt cmake harness .github` = 0 lines): these ride the landing push under the R-4.52 rule (operator option A, master `015102`).
- `git merge-tree --write-tree main H` rc 0, predicted tree `ed11fcd1c3ec97071e36ceb9e52e2368681ac227`, conflict lines 0; path overlap between B..H and B..main (`comm -12`) = 0.
- Landing topology (R-4.52): the local merge is a TRUE merge (parents `main`-before and H; `main` and H have diverged since B); then the census of record at `main`'s post-merge head; then ONE fast-forward push of local `main` to `origin/main` — pinned sha, one attempt, receipt — publishing 139 docs-lane commits + 2 product commits + 1 merge commit. No tag, no release.

## 5. Review record

```text
owner byte review  m-2 DESIGN-REVIEW-m2-planner-20260912-053700     APPROVE — V-CP-1..6 green at the bytes of C; S-CP-5 held; three non-blocking notes
owner reviews      m-3 DESIGN-planner-20260912-053914               (A) hunk review of C's two cells NO FINDING; (B) byte review of H under rev13 NO VETO / NO STOP — H ACCEPTED
master             PLAN-master-planner-20260912-055933              both verdicts carried down; Task 8 gate MET
design (bar)       DESIGN-REVIEW-master-reviewer-20260911-133947    iso rev13 f72919d9 APPROVED at the exact pin (VP concurrence approve)
plan               PLAN-REVIEW-pair-implementer-20260911-172709     plan rev19 777f8c20 APPROVED exact-hash; 28/28 independent decision-line cases
pair-planner       SITREP-pair-planner-20260912-044104 + this packet every mechanical fact re-derived at this seat
```

No pair-tier adversarial panel was run on C/H (as at 2a: master's shape names the owner byte reviews as the review cells). A panel at the exact sha remains available on master's word before cell 4; a panel finding would produce a new sha and re-run both owner predicates.

## 6. The condition census (the four-condition bar)

```text
cell 1  local suites at the exact sha, both platforms — DONE: macOS ctest rc 0 at H (whole selftest 1014 passed); Linux ctest rc 8 with EXACTLY the one registered R-4.35 row, admitted by the approved iso rev13 bar as pass-r435-disclosed-registered-red (the plan's two-outcome acceptance gate of record, master 134909) — every other Linux row green
cell 2  the Docker parity leg REACHED ctest — DONE: four parity-container runs (P, C, H, and the in-token base draw at B); Phase-S ledgers aggregate 0; every JUnit read
cell 3  the owner byte reviews at the exact sha — DONE: m-2 053700 approve; m-3 053914 no finding / H accepted — each verified at this seat by relay stamp, verdict line and sha binding; carried by master 055933
cell 4  the operator's condition-4 merge token — PENDING; presented by master on this packet's return; issues as a BARE token to intg.pair-implementer (grantor set excludes the pair-planner); nothing in this packet is or substitutes for it
visibility  master.master-reviewer, m-2 / m-3 / m-4 planners, the operator CC'd on the packet relay (visibility, not approval)
master's own-bytes verification of head / base / merge-tree / delta / packet-face — master's act on this packet's return
```

## 7. Hold

Assembled and HELD. Cells 1–3 DONE and verified at this seat; the ONLY remaining gate is cell 4 — the operator's merge token, issued as a bare token to `intg.pair-implementer` on master's presentation of this packet. The pair does not merge on its own word; the pair-planner never runs a merge.

If the token issues: the merge is a LANE-LOCAL act on unpublished `main` executed by the implementer per §4's recorded topology (true merge, parents `main`-before + H; the predicted tree re-derived immediately before the merge; product-root diff H..merge EMPTY; `origin/main` untouched by the merge itself), reported UP with post-merge receipts; then the R-4.52 landing as the packet's own step: the census of record at `main`'s head, ONE fast-forward push of local `main`, pinned sha, one attempt, receipt — reported UP. No tag, no release; the release hold is ABSOLUTE.
