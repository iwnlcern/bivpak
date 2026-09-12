R-4.50 claude-discover parity — ONE PR, TWO COMMITS, TWO OWNERS (arm A of master 041131).

Design pins: m-2 fence rev2 m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f; iso rev8 sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af (live: iso rev13 sha256 f72919d984860684450d8394d74191a423f525fd5be787f64fe681dc7a13f9ce).
Plan pin: intg-r450-discover-parity-plan-20260906 sha256 777f8c20d1f19566bdd9096c40b70c0ce3b5136d865b6cf7eca70cb260ffbda7

B=bbf297e36a38a1fab8c2675f945098a0633f9f8b
P=54954281b30cae113f399055fff106963a37a443
C=961b1ccd0ba488f909357d4cac1abab8c77d2fa8
H=8509157c41c5ef66595d655f39eee5107081bd32 (H^ = C)

C touched (numstat):
2	2	.github/workflows/s2-harness.yml
12	13	src/adapters/claude_code/claude_code.cpp
183	0	tests/test_adapter_claude_collect.cpp

H touched (numstat):
1	1	harness/bivharness/e3.py
9	5	harness/selftest/stub_biv.py
2	2	harness/selftest/test_store_isolation.py

C tuples (macOS, Linux):
biv_subprocess_tests macos successes=12 failures=0 expectedFailures=0 skips=0 xml_sha256=038d4b8f6efa1eb99c342dcf854392b403f975965a94bafcfc1e9f8828302594
biv_repo_git_tests macos successes=6 failures=0 expectedFailures=0 skips=0 xml_sha256=a921052f007685d05b9639711861504dd264ea0c815af5f7d158b7d5c760c121
biv_repo_engine_tests macos successes=60 failures=0 expectedFailures=0 skips=0 xml_sha256=fe6fc10e672f56490cbeec20287d61203345ad96efe4b31e68efcefddb1d472d
biv_tests macos successes=419 failures=0 expectedFailures=0 skips=3 xml_sha256=78b8226ce1116bcf12f19f55f1498b8fd28f07895c3c4c1c6fe852a08554e4cb
biv_probe_tests macos successes=25 failures=0 expectedFailures=0 skips=0 xml_sha256=fbcace153a655c088858aa2ed60ca6726a06fc17b5651e9f383fdff2ec608873
expected_skips_observed macos n=3 pack computes foreign-flavor session relpaths without host path parsing | pack derives relpath from slash-form Windows extended paths | threshold-parity per-agent distribution self-activates at R-4.29
biv_subprocess_tests linux successes=12 failures=0 expectedFailures=0 skips=0 xml_sha256=96db60ae53c364f11e348dc5214af86969a03e0574f83269ba2d05ac48d39387
biv_repo_git_tests linux successes=6 failures=0 expectedFailures=0 skips=0 xml_sha256=40a07a9b3ad4281d860297abb4954f2dca6d7dbaa1bcda3789db90533ba1fb87
biv_repo_engine_tests linux successes=60 failures=0 expectedFailures=0 skips=0 xml_sha256=a1ba04d911eae434fd080e8a234316b4853ef5a92e824854aba728e54924db98
biv_tests linux successes=421 failures=0 expectedFailures=0 skips=1 xml_sha256=0f8bbad5d3f7c0d6cb8f8f834ebfbef2a4c42a9b3e877321d8b8ac03ac628218
biv_probe_tests linux successes=25 failures=0 expectedFailures=0 skips=0 xml_sha256=7d7b26bfdb0413431e1beea8635ee54e873cd082fe43b992e07d202364263b01
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
rcL=8 a_rows_rc=0 summary_H=parsed failed_H=2 names_H=selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite, foreign_H= d_tripwire_lines=0 d_family_files_rc=0 population_H=1013 rcB=8 base_rows=1 base_rows_rc=0 summary_B=parsed failed_B=3 names_B=selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite,selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open, foreign_B= population_B=1013 bar=pass-r435-disclosed-registered-red

Owner reviews: m-2 on C (V-CP-1..6); m-3 on C's two workflow lines (CG-R7.5) and on H (V-FT-1..8) — returned through master before this PR was opened.

This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews, and the operator's condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator's token; the landing push of main follows the merge under the R-4.52 landing rule as the merge packet's own step.
