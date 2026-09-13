## IMPL RETURN — token 13 Tasks 0–7 at pinned C′/H′; Task 8 held

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
STATUS: RETURNED-TASK-7
DISPATCH_ID: intg-r450-discover-parity-impl13-return-1
PARENT_DISPATCH_ID: intg-r450-discover-parity-impl-13
IN_REPLY_TO: intg-r450/SITREP-pair-planner-20260913-030119.md
RELATED_CONTEXT: intg-r450/IMPL-pair-planner-20260913-022903.md; intg-r450/IMPL-pair-implementer-20260913-025611.md; intg-r450/SITREP-pair-planner-20260913-030440.md; intg-r450/PLAN-REVIEW-pair-implementer-20260913-022236.md; intg-r450/PLAN-pair-planner-20260913-020714.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: Task 8 requires the pair Planner's verification of this Task 7 return and an addressed relay saying its condition is met; no Task 8 authority is inferred from this return. C′/H′ owner re-reviews, merge packet rev3, Master Reviewer verification, operator bare merge token, landing push, and release retain separate gates; release hold ABSOLUTE.
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: R-4.50 discover-parity messages-only rewrite and re-acceptance under token 13; return through Task 7 only
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 dd7ec27bee1e45cf2226446f00c58c86efffbe67c20d1e56d4fc824f7661716f
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: IMPL RETURN token 13 — Tasks 0–7 controller rc=0 at C′ efb4caed / H′ e8a1128d, in-token Linux H′/B bar pass-r435-disclosed-registered-red with exact three-name sets disclosed; Task 8 NOT entered, no push/PR; pair Planner verification requested

## Outcome and boundaries

Under the pair Planner's addressed 030119 adjudication, I re-entered protocol (0) from its first line in a fresh Bash shell without readline editing. The abandoned `r450-runners-BMWAUy` remains sealed and unreferenced by this run. The fresh, resolved runners directory is `/Users/jack/Programming/bivpak-evidence/r450-runners-AJRnw2`; the fresh evidence home is `/Users/jack/Programming/bivpak-evidence/r450-intg-r450-discover-parity-impl-13-UoYDAE`. The live plan hash equals the token lock `dd7ec27bee1e45cf2226446f00c58c86efffbe67c20d1e56d4fc824f7661716f`. Before Task 0, the three must-be-equal receipts matched the planner's values: `plan_blocks.py` `9f0b5d6a37a731f14c97e3ad99db1832db24f26aed94323bbc8b8a988da5fb94`, `run-task.sh` `1905d36c67503cf91ebeae36ac94f6b6c18540bb61bd15cb88108fcd663ecf0a`, `blocks.txt` `f43cac66423a2c0639aa98156ddcd2905ab6b660b360af25a2fae2ede45e2961`.

Tasks 0, 1, 2, 3, 4, 5, 6, and 7 were each invoked once as `"$RUNNERS/run-task.sh" N`, in order. Every `runners/task-N.exit` and `.done` for N=0…7 reads `rc=0`; every `runners/proof-N.txt` ends `rc=0` and reports `bytes=equal`, `prologue=ok`, `omitted=0`, `out_of_order=0`. Task 0's proof has `run_blocks=10 lines=80 spans=283 gates=44`; Task 7's has `run_blocks=3 lines=39 spans=99 gates=18`. The home holds the copied authenticated task scripts, digests, invocation receipts, proof files, `runners/blocks.txt`, `helpers.sha256`, and `helpers.verify-1.txt` through `helpers.verify-7.txt`. Task 8 was NOT invoked: there is no `task-8.*` controller receipt. Task 9 and the tracked-record finalizer were NOT invoked. No push, PR creation/closure, merge, landing push, tag, deployment, or release occurred.

## Commit rewrite and scope

`B=bbf297e36a38a1fab8c2675f945098a0633f9f8b`; `P=54954281b30cae113f399055fff106963a37a443` (`git cat-file -e "${P}^{commit}"` rc 0); `C′=efb4caeda0533a81e7148dfd38462ae64704ec8a`; `H′=e8a1128d75cd4693d21269c4d040095df570f116`. Task 0's `rewrite.txt` records C original `961b1ccd0ba488f909357d4cac1abab8c77d2fa8` → C′ and H original `8509157c41c5ef66595d655f39eee5107081bd32` → H′. The trees are unchanged (`tree_C=1efd9ce26aba839b8c234cc8be9f31b7a37e1d20`, `tree_H=4a6075c9caa1d1b8757aa44a734675d1dc6d6ee4`), `diff_C_rc=0`, `diff_H_rc=0`, exactly one trailer line deleted from each message, `trailers_new=0`, `parent_C=B`, `parent_H=C′`. New local branch `intg/r450-discover-parity-v2` and worktree HEAD are H′; old branch `intg/r450-discover-parity` remains at original H. Worktree porcelain is empty. No file in either tree was edited by this token's rewrite.

B→C′ numstat is exactly `2/2 .github/workflows/s2-harness.yml`, `12/13 src/adapters/claude_code/claude_code.cpp`, `183/0 tests/test_adapter_claude_collect.cpp`; `touched.delta` is empty. P→C′ is only the workflow 2/2 row, with `exclude_workflow_quiet_rc=0`, `C_parent_is_B=yes`, `cutpoint_Cparent=0`. The Claude C′ hunks are `@@ -571,0 +572,6 @@`, `@@ -572,0 +579 @@`, `@@ -576,6 +583,2 @@`, `@@ -586,7 +589,3 @@`, inside 570–596; the hunk verdict is rc 0 and the Claude diff has zero `collect(` matches. Codex is byte-identical to B: SHA-256 `08480a19a7194f79078d01091f2f24d7d23abb8483c7a2bff0138d6de52e6d5d`. C′→H′ numstat is exactly `1/1 harness/bivharness/e3.py`, `9/5 harness/selftest/stub_biv.py`, `2/2 harness/selftest/test_store_isolation.py`; both C→H comparison deltas are empty. B→H′ is exactly those six paths, `touched-H.delta` empty. The only e3.py hunk is `@@ -75 +75 @@`, replacing Claude anchor `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` with `4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51`.

## P/C′ observation, tuple and gate record

Run identities are `P-macos-54954281b30cae113f399055fff106963a37a443`, `P-linux-54954281b30cae113f399055fff106963a37a443`, `C-macos-efb4caeda0533a81e7148dfd38462ae64704ec8a`, and `C-linux-efb4caeda0533a81e7148dfd38462ae64704ec8a`. The macOS observer is arm64; Linux is Ubuntu 24.04 linux/amd64 with `--init` and nofile soft==hard. The observer name-only record lists `ANTHROPIC_API_KEY`, `OPENAI_API_KEY`, `CODEX_ACCESS_TOKEN`; host presence is one present/two absent, while both actual P/C observed environments have all three unset. No value is carried.

The ten P tuples (each `failures=0 expectedFailures=0`; fields below are successes/skips/XML SHA-256):

```text
P biv_subprocess_tests macos 12/0 06b88b29bdabe24f9bac1cc69ab4bdc6f8ac6f7b44eb8cb5b5e8a5b3cabfcf29
P biv_repo_git_tests macos 6/0 81138bbaf897fb21f3da04c59ac7683993193bbff3e7d5c587a7f07562cba3e9
P biv_repo_engine_tests macos 60/0 8372e2d052a17f9dfc3ac1019f180bd213d08fcad18580080a541d8fa296a397
P biv_tests macos 419/3 ad10052b2ca77e4c4a61aa76d3d490c54dc19a4e4aa5f78c843f569566bb5250
P biv_probe_tests macos 25/0 d1fffc5e937600fff8a0bc7c071853008a028fe8d55190ec43c4eac75688d861
P biv_subprocess_tests linux 12/0 a3050ddeb6c6b56a5e57844528344c858426d10a7b0b21f17d8bd9b23f1b4963
P biv_repo_git_tests linux 6/0 4b8291ef44c3fe131bae8830b1c2d85fdf90fda1cdaa023099add37d771eb20e
P biv_repo_engine_tests linux 60/0 bd4e1d132d487591b984e2e059c417093aed7e621657bcdb62171c2971e0d921
P biv_tests linux 421/1 ae59384506591fc243cb40414eb920170422c92b0f5a3dd93738f6f06ad57b44
P biv_probe_tests linux 25/0 b5fd66c306627c079e3d98e9f374fd1f729d61c47f354dfd3506da3366e77ad2
```

The ten C′ tuples (same zero failure/expectedFailure fields):

```text
C biv_subprocess_tests macos 12/0 c7fb03b06e3bf82b70476201d872b27a4d9c945b0d0705e14cce5810a710ea59
C biv_repo_git_tests macos 6/0 1220344d68dc01743d0134fc517211428b5c5e95c824de4c524fa7463d3ebe3c
C biv_repo_engine_tests macos 60/0 36258ec8efa46e381096385003b0173e5b58b550c31c09e4ea758a0d76dd576b
C biv_tests macos 419/3 f5954f8b82bfc1dd0ba6d7189734f31438c9ac135ce3f8bbaaf522d232147367
C biv_probe_tests macos 25/0 80b312a9fcf2ac20a07a9009bb54e151d10d3d67a6098d91a9ae9838e18483d6
C biv_subprocess_tests linux 12/0 841aea454abb44d5dde24e8c0fbee30566530006a604e4e04958094a233298ed
C biv_repo_git_tests linux 6/0 a148fe248b391ac69b2e47dda47333146d169751c435975d6c1a576e98af1569
C biv_repo_engine_tests linux 60/0 18eff3c422c41bfc486a0ac583399d544ae8c6ce0deeb652aedcb910200ab47c
C biv_tests linux 421/1 2eca1878930b513b26ef803e8e7344a3d32e778b108e751b84adf6de042fe4c7
C biv_probe_tests linux 25/0 c88fd482665818050262dd0136707b3bcc14e06c0a8a791c2d2a6412a57b1c04
```

The old(B)/observed(P)/new(C′) successes table has 25/25/25 probe, 60/60/60 repo_engine, 6/6/6 repo_git, 12/12/12 subprocess on both OSes; `biv_tests` is 418/419/419 on macOS and 420/421/421 on Linux. All ten C′ gate rows read `literal_C == observed_P == observed_C`, `equal=yes`; H′ re-checks all ten `equal=yes`. MacOS expected skips are three named baseline tests; Linux expected skip is the one named baseline test. B-tree RED: witness rc 42, parse rc 0, rows 1 and 5 red, rows 2–4 green; B discriminator `rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS`. P, C′, H′ green witness verdicts on both OSes end `green verdict ok`; B/P/C′/H′ token scans each record `hits=0`. P and C′ disclosure ctest rc 8 on both OSes, failed-name set exactly `harness-selftest`, all failing-set deltas empty. P/C′ Linux suite ledgers end `suite_aggregate_rc=0 ledger_write_failed=0`. `status-post-C-obs.txt` and `status-post-H-obs.txt` are empty.

## H′ acceptance and Linux bar

H′ run IDs are `H-macos-e8a1128d75cd4693d21269c4d040095df570f116` and `H-linux-e8a1128d75cd4693d21269c4d040095df570f116`. The ten H′ tuple values equal C′ on the four measured counts (individual H′ XML hashes reside in `H/tuples-macos.txt` and `H/tuples-linux.txt`); all ten `H/gate-equality-H.txt` rows are `equal=yes`. `fidelity-pre-H.rc=5` (rows 1 and 5 mismatch; rows 2–4 ok); `fidelity-H.rc=0` (all five rows ok). Inventory is `markers=7 tests=11`; Claude/Codex anchors each count 1; `walk-A.delta` and `walk-B.delta` are empty. Targeted store-isolation pytest rc 0, `11 passed in 1.50s`; full harness selftest rc 0, `1014 passed in 13.81s`. H′ discriminator is `rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS`. H′ macOS full ctest rc 0. The HOME demonstration records `rp_rc=0`, a `MUTANT HOME` failure with `leak_tags=['HOME']`, both Claude/Codex image identity lines, and all four mutants red on their own locator; these are in the evidence home, not restated as credential values.

H′ Linux full ctest rc 8; B Linux full ctest rc 8. Both suite ledgers end `suite_aggregate_rc=0 ledger_write_failed=0` and both head receipts match their pinned commits. The *current token* `H/linux-selftest-bar.txt` records `bar=pass-r435-disclosed-registered-red`, `population_H=1013`, `population_B=1013`, three registered failing names on each tree, `foreign_H=` and `foreign_B=` empty, and the clause receipts `a_rows_rc=0`, `base_rows_rc=0`, `d_tripwire_lines=0`, `d_family_files_rc=0`. The two names common to H′ and B are `test_credential_scanner_detects_entry_added_after_directory_enumeration` and `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`. H′ additionally names `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`; B additionally names `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop` (all under `selftest/test_e3_asserts.py`). This is NOT the prior token's two-H/three-B summary; the current token's three/three named sets are the evidence of record. `H/selftest-H.kv` and `B/selftest-B.kv` each parse `failed=3 passed=1007 skipped=3 population=1013`; their `.names` files, the B ledger, B head receipt and `B/ctest-linux-B.rc` are present. No unexpected red was waived; the controller accepted the plan's named registered-red outcome.

## Resume and census record

`resume-state.txt` records `resume_state=iii`, original H `8509157c41c5ef66595d655f39eee5107081bd32`. C and H were created under token 11 outside the per-task runner protocol (master `164408`); their evidence was NOT resumed (master `042340`). This token verified the retained H by status/hash, then rewrote only the messages in Task 0. `rederive-H.txt` has three `diff_rc=0` and `rederive_mismatch=0`; `rederive-C.txt` has `MAC=419 k85=1 LIN=421 k326=1` against this token's fresh P; `task-3-iii.txt` says no transcription or amend. `B-tree.txt`, `P-tree.txt`, `C-tree.txt`, `btree-test.sha256` (`90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9`) and `btree-claude.sha256` (`cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851`) are present. The H′ tree census equals exactly the three written fixture-filename locations and the history census equals the two written paths; both delta files are empty and no matched value is reproduced in this relay.

## Requested next act

Pair Planner: verify the durable home and this Task 7 return. An addressed relay satisfying the plan's Task 8 condition is required before this seat may enter `run-task.sh 8`; owner re-reviews of the NEW C′/H′ identities and all merge/landing/release gates remain downstream. The evidence-of-record tracked copy is finalized only by Task 9 after Task 8, not by this return.

ACTIONS_GIT_REF: Task 0 created only the pinned C′/H′ commit objects and local `intg/r450-discover-parity-v2` branch and switched the retained worktree to H′; no file-byte change, no remote write. Tasks 1–7 wrote fresh durable evidence and disposable build/container outputs. This relay is the only docs-lane write of this return; no push/PR/merge/landing/release.
RELAY_LINT: engine-rendered per-file lint required; exact-file status to be checked on render. Root-wide inherited findings are not rewritten.
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-planner
FINAL_GIT_STATUS_SHORT: Candidate worktree at H′ has empty porcelain; docs lane retains inherited S4 changes/untracked files and prior intg relay projection, none staged or cleaned by this task.
