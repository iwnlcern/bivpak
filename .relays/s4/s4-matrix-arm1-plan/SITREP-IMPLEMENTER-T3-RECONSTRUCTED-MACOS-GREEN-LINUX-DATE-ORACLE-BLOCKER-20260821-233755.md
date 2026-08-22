## SITREP — T3 reconstructed with the required compare.py composition; macOS green; Linux exposes one T3-owned Git-date presentation oracle blocker, so T3 stops before panel/final

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-reconstructed-linux-date-oracle-blocker
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-final-t3-unblocked
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-CONCUR-II-CONSEQUENCE-REFUTED-T2-FINAL-T3-UNBLOCKED-20260821-225425.md
RELATED_CONTEXT: SITREP-PLANNER-COMPARE-PY-COMPOSITION-SCOUTED-INCOMPATIBLE-SIGNATURES-NOT-A-CONFLICT-20260821-230628.md; IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: bounded pair Planner disposition is required before any T3 blocker edit; every merge, push, PR mutation, publication, deployment, and release remains separately held
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
CANDIDATE: reconstructed T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T3 RECONSTRUCTED — compare.py obligations composed and macOS green, but Ubuntu 24.04 Git 2.43.0 renders the new deterministic-date oracle as +00:00 where macOS Git 2.50.1 renders Z; T3-owned portability blocker stops final/panel/T4 pending a bounded ruling

T3 has been reconstructed locally onto final T2 under the existing Wave-A R1 implementation
token. The replay produced one semantic conflict in `harness/bivharness/compare.py`; the
pair Planner's independently scouted disposition was then applied exactly. I first resolved
production to T3-only behavior and added a composed-path test. It failed RED because
`compare_trees` accepted three arguments while the scenario contract passed four. I then
restored the additive-root parameter, validation helpers, guarded extra-path loop, and
four-argument scenario call while retaining T3's repository exclusions, tracked-file mtime
policy, and repo semantics. The composed test now proves both halves together: an allowed
additive root is ignored while a missing repository reference remains reported. That test
passes, and all 26 `test_compare.py` tests pass.

The append-only INDEX conflict was resolved by union, not side selection. Removing the one
historical T3 row from the reconstructed INDEX produces a byte-identical final-T2 INDEX, and
the inserted row is byte-identical to the replayed T3 row. The reconstructed branch is clean,
final T2 is its ancestor, and its three local commits are:

```text
2c89daa21c3dcfca4e58d80ccd6c0d7d1579fe55  feat(harness): git fixture builders, repo-aware compare, tolerance git rows
4af296945a1f5a2f0c14c293b2d01d3c92047411  docs(s4): report Arm-1 T3 implementation
a3501cc1728ca13289a8a4a96e49c9ee95e54698  fix(review): declare harness git tolerances
```

The T3 delta from final T2 is exactly the expected ten paths: the historical relay and its
INDEX row, fixture ledger, `compare.py`, `fixtures.py`, `scenario.py`, three selftest files,
and `tolerance-v1.json`. No T1/T2 product or test byte was changed by the reconstruction.

## macOS validation — green at the reconstructed head

```text
python3 -m pytest harness/selftest
  997 passed in 14.06s

python3 harness/ci/check_core_adapter_purity.py
  OK

cmake --preset ci-macos
cmake --build --preset ci-macos
  both passed

ctest --preset ci-macos -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$' --output-on-failure
  6/6 passed, 0 failed, 634.88s
```

## Linux validation — one real T3-owned portability blocker

The Linux arm reproduced the canonical environment locally in a disposable
`ubuntu:24.04` container with `--platform linux/amd64`, non-root user, inherited
`nofile` soft and hard limits both 1048576, GCC 13.3.0, Python 3.12.3, Git 2.43.0,
and the pinned verified clang-tidy 22.1.8 bundle. No unrelated Docker resource was
removed or pruned.

The first container attempt is retained as r0 and is classified as an instrument/setup
defect: the source archive accidentally carried the host `.venv-harness`, whose Python
symlink targets Homebrew. Linux could not execute it. The corrected r1 excluded that
host venv and changed no product byte or other validation variable.

In r1, venv, pip, configure, build, and purity all returned zero. `biv_tests` passed in
6.72s, `harness-e2` passed in 1.18s, and `safety-tidy-analyzer` passed in 51.40s. Full
CTest returned 8 because three rows were red. The one T3-owned failure is:

```text
harness/selftest/test_fixtures.py::test_git_repo_builder_is_deterministic_and_host_config_isolated
expected author and committer dates: 2000-01-01T00:00:00Z
actual on Git 2.43.0:               2000-01-01T00:00:00+00:00
```

The fixture pins the same UTC instant with `GIT_AUTHOR_DATE` and `GIT_COMMITTER_DATE`.
Repository construction and repeat-head determinism pass; only the raw `%aI` and `%cI`
presentation assertion differs. macOS Git 2.50.1 emits `Z`; Ubuntu Git 2.43.0 emits
`+00:00`. This test is introduced by T3, so the failure belongs to T3 even though it is
a test-oracle portability defect rather than a product failure. The current test hardcodes
one Git version's spelling at `harness/selftest/test_fixtures.py:105-107`.

I recommend a bounded fix that asserts the semantic instant with a version-stable oracle,
such as epoch output, rather than admitting a list of observed spellings. I have not made
that edit: the incoming plan says a genuine conflict stops and routes, and Linux has now
shown that T3 is not portable as written. T3 is therefore not Stage-2 green, not final, and
not panelable; T4 remains held pending the pair Planner's disposition.

The other Linux observations are carried without laundering them into T3 causation:

- the T1-owned subprocess and probe binaries still report descendant-process cleanup reds
  in the full-suite context; T3 changes no C++ source or test byte;
- `harness-selftest` also has three rotating R-4.35 E3 scandir/TOCTOU-family failures;
- the direct Catch2 binary itself returns zero with 387 successes, 0 failures,
  0 expected failures, and 1 skip, while the workflow expects 412/0/0/1. This is the
  already-carried R-4.38 single-binary count-gate inventory shape after T1 split tests into
  separately executed CTest binaries, not missing execution.

The durable Linux evidence root is
`.superpowers/sdd/t3-reverify-MNIpkPxh` in the isolated T3 worktree. Its
`RECEIPTS.sha256` carries 27 entries and verifies 27 of 27. r0 and r1 logs remain distinct.

No remote CI, ref publication, push, force-push, PR mutation, merge, schema, deployment, or
release act occurred. The reconstructed T3 branch and all evidence remain local. The release
hold is ABSOLUTE.

ACTIONS_GIT_REF: locally rebased only `s4-matrix/arm1-t3` onto final T2 7688bbd, resolved compare.py and INDEX by composition/union under the live Wave-A R1 token, and ran macOS plus disposable local Linux validation. No remote/ref-publication/push/PR/merge/schema/deploy/release act. This report and one live-EOF INDEX row ride one explicit-path docs-lane commit on main.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects disclosed and preserved; post-commit exact-file no-freshness verification.
FINAL_GIT_STATUS_SHORT: isolated T3 branch clean at a3501cc; shared main retains sibling-authored untracked history unchanged and unclaimed; only this receipt and its one INDEX append belong to this docs act.

CARRY LIST:
- reconstructed T3 local head `a3501cc` is based on final T2 `7688bbd`; exactly the expected ten T3 paths differ
- compare.py is composed, not side-selected: additive-root handling and T3 repo semantics coexist; the combined RED-to-GREEN test and all 26 compare tests pass
- macOS candidate rows are green: 997 selftests, purity, configure/build, and the selected six CTest rows
- Linux r0 is a retained host-venv packaging defect; corrected r1 has green setup/build/purity/biv_tests/harness-e2/tidy
- BLOCKER: T3's new Git-date test asserts macOS Git's `Z` spelling while Ubuntu Git 2.43.0 emits equivalent `+00:00`; request a bounded version-stable semantic-time oracle ruling before editing
- candidate-neutral Linux observations remain separately owned/carried: T1 descendant cleanup, three rotating R-4.35 cases, and R-4.38 single-binary count 387 versus 412
- T3 is not final/panelable and T4 stays held; no remote CI, publication, integration, schema, deployment, or release act; release hold ABSOLUTE
