## SITREP — T3 ref-SHA guard complete: exact one-file candidate, three discriminators fire, macOS 1000 green, Linux three nodes green with non-green R-4.35 aggregate retained

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-complete
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T3-REF-SHA-GUARD-DISPATCH-20260822-131430.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-GUARD-R1-LINUX-PREDICATE-SPLIT-DUAL-GATE-INLINED-20260822-125850.md; .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-REF-SHA-GUARD-R1-APPROVE-LINUX-PREDICATE-SPLIT-DUAL-GATE-20260822-130354.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: Planner adjudicates this completion and routes the focused re-lens promised at 060538 before any stack reconstruction or integration act. This report grants no push, PR mutation, merge, publication, schema act, deployment, or release. Release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T3 d4068684e51f67d0a11fb6d2251178fb2a1a70ea; local candidate 70601fc201b3c41d2542d82399787b5febcbf03c
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ref-SHA guard implementation complete at 70601fc; one test file 57 insertions; macOS 1000 passed; Linux three new nodes passed and aggregate 3 failed 993 passed 3 skipped only within registered rotating R-4.35; three mutation controls and all dual restore gates passed

## 1. Authority and exact artifact

The actionable durable token is the live `131430` relay. It carries exactly one bare token,
addresses `s4-matrix.implementer`, parents to the unique rev1 approval holder, whose verdict
matcher returns True, and binds base `d406868`. Candidate work occurred only in the existing
linked worktree `/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t3` on branch
`s4-matrix/arm1-t3`.

Local candidate `70601fc201b3c41d2542d82399787b5febcbf03c` has parent
`d4068684e51f67d0a11fb6d2251178fb2a1a70ea` and exactly one changed path:
`harness/selftest/test_compare.py`, 57 insertions, zero deletions. The target is 13889 bytes,
SHA-256 `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`,
and Git blob `8eedaad7b55e619cea5c9ac715140329db0295c5`. The production oracle
`harness/bivharness/compare.py` remains at SHA-256
`afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4`.

## 2. O-1a — macOS

Fresh post-commit evidence on Darwin arm64, Python 3.12.5 and pytest 8.4.2:

- `test_ref_restored_to_a_divergent_sha_reports_a_ref_mismatch` — PASSED
- `test_extra_restored_ref_reports_a_repo_finding` — PASSED
- `test_repo_state_expectation_reports_a_divergent_ref_sha` — PASSED
- all three explicit nodes together — 3 passed, exit 0
- `harness/selftest/test_compare.py` — 31 passed, exit 0
- full `harness/selftest` — exactly 1000 passed, exit 0

## 3. O-1b — Linux is a separate predicate, not an aggregate-green claim

The bounded run used disposable `ubuntu:24.04`, `--platform linux/amd64`, Docker `--init`,
and a non-root test process `biv` at uid/gid 501. PID 1 was `docker-init`; the host reported
x86_64/amd64, Python 3.12.3, git 2.43.0, and pytest 8.4.2. The non-root nofile limits were
1024 soft / 1048576 hard before the gate and 1048576 / 1048576 after raising soft to hard.

All three new node IDs passed explicitly: **3 passed in 1.85s, exit 0**.

The full Linux aggregate is explicitly NOT green: **3 failed, 993 passed, 3 skipped in
20.83s, exit 1**. The exact failing members were:

- `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`
- `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`
- `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`

All three are within the registered four-member R-4.35 E3 scandir/TOCTOU family; the corrected
classifier reports `outside_r435_count=0`. No new ref-SHA node failed and no failure fell outside
that family.

### Classifier correction retained rather than hidden

My first classifier incorrectly allowlisted only the prior Linux sample's three observed names.
It stopped when this run rotated in
`test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`. Direct registry read then
confirmed master R-4.35 names that exact test as the flaky-membership fourth and sharpens the
contract to three of a four-member family with rotating membership. The r0 output and status are
preserved. The r1 classifier uses the exact registered four-member census against the unchanged
retained Linux log and returns zero outside-family failures. No test result, aggregate, or log was
rewritten, and the aggregate remains reported non-green.

This bounded proof matched the plan's Ubuntu, amd64, Python 3.12, locked-dependency, full-selftest,
init, non-root, and nofile topology. It was not full `.github/workflows/s2-harness.yml` parity:
clang-tidy-22 provisioning, product configure/build, CTest product rows, and Catch2 count gates
were intentionally outside this test-only cycle. No remote workflow ran.

## 4. O-2 — three must-be-NO controls and dual restore gates

Each scratch arm asserted the exact source line token before mutation, preserved original
indentation, imported `bivharness.compare` successfully before reading the test verdict, and made
only its matching node fail exactly once with exit 1 and no collection or import error:

```text
compare.py:236 common-ref SHA comparison neutered       divergent-SHA compare_trees node   1 failed
compare.py:234 extra-ref append neutered                extra-restored-ref node             1 failed
compare.py:287 assert_repo_state SHA check neutered     divergent expectation node          1 failed
```

After EACH arm, both files passed the inlined restore gate before continuing:

```text
compare.py       afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4
test_compare.py  a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566
```

## 5. O-3, O-4, evidence, and state

`git diff --name-only d406868..70601fc` returns exactly
`harness/selftest/test_compare.py`. `compare.py`, `fixtures.py`, `test_fixtures.py`, and
`scenario.py` are byte-identical to `d406868`. The required target digest and 13889-byte size
both reproduce after commit, and `git diff --check d406868..70601fc` is clean.

Durable evidence root:
`/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t3/.superpowers/sdd/t3-ref-sha-guard-Gf8L5cRv`.
Its `RECEIPTS.sha256` covers 42 artifacts, verifies 42/42, and has SHA-256
`5805748acb8f31d1054b238dead621a2a36d21652a14fbd5e133bca24d6b2b87`.

The candidate worktree is clean at `70601fc`. The branch and both T3 heads remain local and
unpublished. The disposable proof container is gone; the unrelated long-running container
`bivpak-slice-a-d885530-ci` remains preserved. T4 remains held and the focused re-lens is owed
on the three new tests alone. No remote CI, push, PR mutation, merge, publication, schema act,
deployment, or release occurred.

ACTIONS_GIT_REF: under the 131430 implementation token, changed only harness/selftest/test_compare.py and committed local candidate 70601fc201b3c41d2542d82399787b5febcbf03c parented directly to d406868; ran three exact scratch mutation controls with import sanity and dual restore gates; ran explicit target nodes and full macOS selftest; ran the separate bound Linux predicate in disposable Ubuntu 24.04 amd64 Docker; preserved and corrected forward the initial under-enumerated R-4.35 classifier; generated and verified a 42-entry receipt manifest. No remote or integration act
FINAL_GIT_STATUS_SHORT: candidate branch s4-matrix/arm1-t3 clean at 70601fc; shared docs checkout retains sibling-authored untracked paths, preserved and unclaimed; only this report and its live-EOF INDEX append are claimed here
RELAY_LINT: exact-file freshness; live INDEX EOF re-read before append; full INDEX lint compared against the inherited 10-error baseline and required to add none; root mode required to name no error against this report; cached diff check and explicit two-path docs commit fail-fast; post-commit historical exact-file verification

CARRY LIST:
- local candidate 70601fc, parent d406868, exactly one test file and exact target digest a9d0a49f; no production byte
- macOS three named nodes passed, test_compare.py 31 passed, full selftest exactly 1000 passed
- Linux three named nodes passed; aggregate explicitly non-green at 3 failed 993 passed 3 skipped, exit 1; all failures within registered rotating R-4.35 and zero outside-family
- classifier r0 under-enumeration preserved and corrected forward from the exact four-member R-4.35 registry; retained test log unchanged
- three must-fail controls each produced exactly one failed matching node; dual restore gate passed after every arm
- 42/42 durable receipts, manifest SHA-256 5805748acb8f31d1054b238dead621a2a36d21652a14fbd5e133bca24d6b2b87
- branch kept local and unpublished for focused re-lens; T4 held; no remote or integration authority or act; release hold ABSOLUTE
