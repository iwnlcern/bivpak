R-4.49 line-1 selection (m-2 fence 142000 §2 / rev2 144700; the operator grant 152118 "lets fix both please", 2 of 2): candidacy in both collect paths is decided from a HEAD-BOUNDED streamed read that stops at the predicate today's parsers already implement — the FIRST cwd-bearing record for claude (sealed ADDENDUM-1 §A1; no cwd anywhere = whole file + no_cwd_record, sealed) and the FIRST session_meta record for codex (sealed c1 §4) — and the whole-file read + the unchanged whole-text parsers run only for an in-root candidate. m-2 C-1/C-2 rulings (DESIGN-m2-planner-20260913-170000): selection identity by construction; the act is read-bounding only. ONE PR, TWO COMMITS, TWO OWNERS (the R-4.50 arm A shape): C = the lane's product commit under m-2's fence (SECTIONs inside existing TEST_CASEs; case census unchanged); H = m-3's harness commit (C-2 rule 4): the two S-CP-2 _ADAPTER_SOURCE_ANCHORS literals re-pinned to C's adapter digests, nothing else.

Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
Plan pin: intg-r449-line1-selection-plan-20260913 sha256 39b8966b7edd065b8612419d177648dfc11248ea0566c14f0ab16a875a98d5b6

B=4cf135ee97f57021c5fc5fd5343de6f655fb0d24 (origin/main, the R-4.50 landing merge)
C=6d64aab42637d437e0001d39da3e4fcf97b38855 (C^ = B; the product commit)
H=b74ec570e22646bfee6a0c554bcb766fffa6da19 (H^ = C; the harness commit)

C touched (numstat):
69	6	src/adapters/claude_code/claude_code.cpp
89	34	src/adapters/codex/codex.cpp
93	0	tests/test_adapter_claude_collect.cpp
81	0	tests/test_adapter_codex_collect.cpp

H touched (numstat):
2	2	harness/bivharness/e3.py

COUNT-GATE (the ten OverallResultsCases cells: literal at B == observed at B == observed at H):
biv_probe_tests macos literal_B=('25', '0', '0', '0') observed_B=('25', '0', '0', '0') observed_H=('25', '0', '0', '0') equal=yes
biv_repo_engine_tests macos literal_B=('60', '0', '0', '0') observed_B=('60', '0', '0', '0') observed_H=('60', '0', '0', '0') equal=yes
biv_repo_git_tests macos literal_B=('6', '0', '0', '0') observed_B=('6', '0', '0', '0') observed_H=('6', '0', '0', '0') equal=yes
biv_subprocess_tests macos literal_B=('12', '0', '0', '0') observed_B=('12', '0', '0', '0') observed_H=('12', '0', '0', '0') equal=yes
biv_tests macos literal_B=('419', '0', '0', '3') observed_B=('419', '0', '0', '3') observed_H=('419', '0', '0', '3') equal=yes
biv_probe_tests linux literal_B=('25', '0', '0', '0') observed_B=('25', '0', '0', '0') observed_H=('25', '0', '0', '0') equal=yes
biv_repo_engine_tests linux literal_B=('60', '0', '0', '0') observed_B=('60', '0', '0', '0') observed_H=('60', '0', '0', '0') equal=yes
biv_repo_git_tests linux literal_B=('6', '0', '0', '0') observed_B=('6', '0', '0', '0') observed_H=('6', '0', '0', '0') equal=yes
biv_subprocess_tests linux literal_B=('12', '0', '0', '0') observed_B=('12', '0', '0', '0') observed_H=('12', '0', '0', '0') equal=yes
biv_tests linux literal_B=('421', '0', '0', '1') observed_B=('421', '0', '0', '1') observed_H=('421', '0', '0', '1') equal=yes

LEG 1 / LEG 2 (bytes read per store file — the readtrace.c LD_PRELOAD read accountant inside the Linux parity container, validated first by a must-be-YES dd control, B vs H over the synthetic store S in place):
CLASS claude-bulk files=100 bytes_B=444699770 bytes_H=38582048
CLASS claude-cwd-no-enrichment files=10 bytes_B=41951050 bytes_H=81920
CLASS claude-no-cwd files=5 bytes_B=5248395 bytes_H=5248395
CLASS codex-bulk files=1500 bytes_B=395574933 bytes_H=14651931
CLASS codex-garbage-line1 files=20 bytes_B=5253640 bytes_H=163840
CLASS codex-no-meta files=10 bytes_B=2623500 bytes_H=2623500
TOTAL files=1645 bytes_B=895351288 bytes_H=61351634 ratio_H_over_B=0.0685
VERDICT PASS violations=0

LEG 3 (whole-record membership identity over S at B and at H, macOS and Linux: deltas empty) and the cost receipt:
LEG 3 cost receipt: biv pack over S (medians of three runs), macOS, B then H
label=B runs=3 times_s=4.042,3.883,3.953 median_s=3.953 rcs=2,2,2 oks=True,True,True image=/Users/jack/Programming/bivpak-evidence/r449-intg-r449-line1-selection-impl-1-CjLgkC/work/ws/proj-B.bvpk
label=H runs=3 times_s=0.701,0.474,0.450 median_s=0.474 rcs=2,2,2 oks=True,True,True image=/Users/jack/Programming/bivpak-evidence/r449-intg-r449-line1-selection-impl-1-CjLgkC/work/ws/proj-H.bvpk
membership_delta=empty no_cwd_record_warnings_equal=yes

Linux acceptance at H (two-outcome bar):
rcL=8 a_rows_rc=0 summary_H=parsed failed_H=3 names_H=selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop,selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite, foreign_H= d_tripwire_lines=0 d_family_files_rc=0 population_H=1013 rcB=8 base_rows=1 base_rows_rc=0 summary_B=parsed failed_B=3 names_B=selftest/test_e3_asserts.py::test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop,selftest/test_e3_asserts.py::test_credential_scanner_detects_entry_added_after_directory_enumeration,selftest/test_e3_asserts.py::test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open, foreign_B= population_B=1013 bar=pass-r435-disclosed-registered-red

Census at the branch head (both arms; paths only):
census_at=b74ec570e22646bfee6a0c554bcb766fffa6da19 tree_rows=69 history_paths=34 delta_vs_B=empty delta_B_vs_record_of_4cf135ee=empty record_sha256=858c6486e2ac7ba07dc73ad3b0ff532f03c34539fa8d933e2fa4d21d870e9a1c(accepted,R-4.50 packet rev5) classes=inherited_from_record(A=3,B=64,C=2) matched_text_in_record=none collation=LC_ALL=C

Owner reviews RETURNED through master before this PR (named in the pair Planner's go relay SITREP-pair-planner-20260914-191911.md): m-2 V-LS-1..6 of C — DESIGN-REVIEW-m2-planner-20260914-191300.md (m-2.planner); m-3 V-RP-1..8 of H — DESIGN-planner-20260914-191148.md (m-3.planner); the four-condition merge bar and the operator's condition-4 token follow.

This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites on both targets, the Docker parity leg, the three-leg witness, the owner byte review and the operator's token — a red remote CI is cited nowhere. Merge is local under the operator's token; the landing push of main follows under the R-4.52 landing rule as the merge packet's own step.
