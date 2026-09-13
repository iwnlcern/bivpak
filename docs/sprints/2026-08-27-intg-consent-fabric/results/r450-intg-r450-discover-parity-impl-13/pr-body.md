R-4.50 claude-discover parity — ONE PR, TWO COMMITS, TWO OWNERS (arm A of master 041131). SUPERSEDES PR #25: C 961b1ccd and H 8509157c were REWRITTEN as C-prime and H-prime (commit MESSAGES only — the Co-Authored-By trailer line removed per the operator ruling 164309; trees 1efd9ce2 / 4a6075c9 byte-identical; author and committer identity and dates preserved); PR #25 is to be closed UNMERGED by this runner's next step, with a comment naming this PR (receipt pr25-close.rc); the old branch intg/r450-discover-parity is left in place.

Rewrite: C_orig=961b1ccd0ba488f909357d4cac1abab8c77d2fa8 C_new=efb4caeda0533a81e7148dfd38462ae64704ec8a H_orig=8509157c41c5ef66595d655f39eee5107081bd32 H_new=e8a1128d75cd4693d21269c4d040095df570f116

Design pins: m-2 fence rev2 m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f; iso rev8 sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af (live: iso rev13 sha256 f72919d984860684450d8394d74191a423f525fd5be787f64fe681dc7a13f9ce).
Plan pin: intg-r450-discover-parity-plan-20260906 sha256 dd7ec27bee1e45cf2226446f00c58c86efffbe67c20d1e56d4fc824f7661716f

B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
P=54954281b30cae113f399055fff106963a37a443
C=efb4caeda0533a81e7148dfd38462ae64704ec8a
H=e8a1128d75cd4693d21269c4d040095df570f116 (H^ = C)

C touched (numstat):
2	2	.github/workflows/s2-harness.yml
12	13	src/adapters/claude_code/claude_code.cpp
183	0	tests/test_adapter_claude_collect.cpp

H touched (numstat):
1	1	harness/bivharness/e3.py
9	5	harness/selftest/stub_biv.py
2	2	harness/selftest/test_store_isolation.py

C tuples (macOS, Linux):
biv_subprocess_tests macos successes=12 failures=0 expectedFailures=0 skips=0 xml_sha256=c7fb03b06e3bf82b70476201d872b27a4d9c945b0d0705e14cce5810a710ea59
biv_repo_git_tests macos successes=6 failures=0 expectedFailures=0 skips=0 xml_sha256=1220344d68dc01743d0134fc517211428b5c5e95c824de4c524fa7463d3ebe3c
biv_repo_engine_tests macos successes=60 failures=0 expectedFailures=0 skips=0 xml_sha256=36258ec8efa46e381096385003b0173e5b58b550c31c09e4ea758a0d76dd576b
biv_tests macos successes=419 failures=0 expectedFailures=0 skips=3 xml_sha256=f5954f8b82bfc1dd0ba6d7189734f31438c9ac135ce3f8bbaaf522d232147367
biv_probe_tests macos successes=25 failures=0 expectedFailures=0 skips=0 xml_sha256=80b312a9fcf2ac20a07a9009bb54e151d10d3d67a6098d91a9ae9838e18483d6
expected_skips_observed macos n=3 pack computes foreign-flavor session relpaths without host path parsing | pack derives relpath from slash-form Windows extended paths | threshold-parity per-agent distribution self-activates at R-4.29
biv_subprocess_tests linux successes=12 failures=0 expectedFailures=0 skips=0 xml_sha256=841aea454abb44d5dde24e8c0fbee30566530006a604e4e04958094a233298ed
biv_repo_git_tests linux successes=6 failures=0 expectedFailures=0 skips=0 xml_sha256=a148fe248b391ac69b2e47dda47333146d169751c435975d6c1a576e98af1569
biv_repo_engine_tests linux successes=60 failures=0 expectedFailures=0 skips=0 xml_sha256=18eff3c422c41bfc486a0ac583399d544ae8c6ce0deeb652aedcb910200ab47c
biv_tests linux successes=421 failures=0 expectedFailures=0 skips=1 xml_sha256=2eca1878930b513b26ef803e8e7344a3d32e778b108e751b84adf6de042fe4c7
biv_probe_tests linux successes=25 failures=0 expectedFailures=0 skips=0 xml_sha256=c88fd482665818050262dd0136707b3bcc14e06c0a8a791c2d2a6412a57b1c04
expected_skips_observed linux n=1 threshold-parity per-agent distribution self-activates at R-4.29

H cell equality (gate.py):
biv_probe_tests linux literal_C=('25', '0', '0', '0') observed_P=('25', '0', '0', '0') observed_C=('25', '0', '0', '0') equal=yes
biv_probe_tests macos literal_C=('25', '0', '0', '0') observed_P=('25', '0', '0', '0') observed_C=('25', '0', '0', '0') equal=yes
biv_repo_engine_tests linux literal_C=('60', '0', '0', '0') observed_P=('60', '0', '0', '0') observed_C=('60', '0', '0', '0') equal=yes
biv_repo_engine_tests macos literal_C=('60', '0', '0', '0') observed_P=('60', '0', '0', '0') observed_C=('60', '0', '0', '0') equal=yes
biv_repo_git_tests linux literal_C=('6', '0', '0', '0') observed_P=('6', '0', '0', '0') observed_C=('6', '0', '0', '0') equal=yes
biv_repo_git_tests macos literal_C=('6', '0', '0', '0') observed_P=('6', '0', '0', '0') observed_C=('6', '0', '0', '0') equal=yes
biv_subprocess_tests linux literal_C=('12', '0', '0', '0') observed_P=('12', '0', '0', '0') observed_C=('12', '0', '0', '0') equal=yes
biv_subprocess_tests macos literal_C=('12', '0', '0', '0') observed_P=('12', '0', '0', '0') observed_C=('12', '0', '0', '0') equal=yes
biv_tests linux literal_C=('421', '0', '0', '1') observed_P=('421', '0', '0', '1') observed_C=('421', '0', '0', '1') equal=yes
biv_tests macos literal_C=('419', '0', '0', '3') observed_P=('419', '0', '0', '3') observed_C=('419', '0', '0', '3') equal=yes

Linux acceptance at H (two-outcome bar):
rcL=8 a_rows_rc=0 summary_H=parsed failed_H=3 names_H=selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite,selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open, foreign_H= d_tripwire_lines=0 d_family_files_rc=0 population_H=1013 rcB=8 base_rows=1 base_rows_rc=0 summary_B=parsed failed_B=3 names_B=selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop,selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite, foreign_B= population_B=1013 bar=pass-r435-disclosed-registered-red

Owner reviews: of the ORIGINAL C 961b1ccd and H 8509157c — m-2 on C (V-CP-1..6; 053700) and m-3 on C's two workflow lines (CG-R7.5) and on H (V-FT-1..8; 053914) — returned through master before PR #25 was opened; the REWRITTEN C-prime and H-prime this PR carries (the same trees) are PENDING their own owner re-reviews through master, which precede any merge packet or merge token.

This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews (PENDING for C-prime and H-prime at this PR's creation), and the operator's condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator's token; the landing push of main follows the merge under the R-4.52 landing rule as the merge packet's own step.
