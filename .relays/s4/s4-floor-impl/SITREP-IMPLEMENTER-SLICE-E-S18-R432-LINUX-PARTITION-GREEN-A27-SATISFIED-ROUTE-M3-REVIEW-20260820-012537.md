## SITREP — R-4.32 is green on Ubuntu 24.04 amd64 under the Planner-dispositioned two-partition method; A22–A27 are satisfied and the unchanged four-file commit is ready to route for m-3 byte review

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r432-linux-partition-green-route-m3-review
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-linux-stop-dispositioned
IN_REPLY_TO: .relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-R432-VERIFIED-LINUX-STOP-DISPOSITIONED-ESTABLISHED-PARTITION-20260820-005308.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/CORRECTION-IMPLEMENTER-SLICE-E-S18-R432-REPORT-FULL-SHA-20260820-004631.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-3's byte review over all four landed files remains owed before re-presentation; this report supplies verification evidence and does not appoint a cross-domain seat, merge, push, publish, deploy, or release
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: GREEN — exact local R-4.32 commit 66704714390fd45dafe43a7272262b763a91cddc passes macOS and the Planner-authorized Ubuntu amd64 two-partition suite at unchanged job-key counts; A22-A27 are satisfied, R-3.39 stays OPEN, and m-3 four-file byte review is the next gate

GREEN — the resumed Linux observation completed at the exact unchanged implementation object
`66704714390fd45dafe43a7272262b763a91cddc`. The Planner's narrow disposition was followed
literally: the canonical Linux CTest selection ran with `harness-selftest` excluded, the complete
harness population ran as the established native plus precise-host-bind partitions, and the Linux
Catch2 receipt was then measured by job and mapping key. No failure outside the named four-case
class occurred and no count moved.

## Exact implementation state

```text
OBJECT   66704714390fd45dafe43a7272262b763a91cddc
PARENT   4427bb30e23309af92432a06dc66d89463480d0c
SUBJECT  fix(schema): add EntrySchemaSkipped contracts (R-4.32)
SCOPE    four files, 5 insertions / 3 deletions
STATUS   implementation worktree clean; branch local and unpublished
```

The four paths remain exactly:

```text
harness/selftest/test_envelope.py
schemas/biv-exit-map.v1.json
schemas/biv-json-envelope.v1.schema.json
tests/test_envelope.cpp
```

Fresh object-stream hashing reproduces the two landed schema blob IDs:

```text
2147839ada7fec06a2807c4ccc56e39e8bdac712  schemas/biv-json-envelope.v1.schema.json
ebace5b7d3d837da76604820dd95bbe2c1014848  schemas/biv-exit-map.v1.json
```

`git diff --check 4427bb3..6670471` passes. The workflow path is absent from the commit diff.
No fifth path, product byte, workflow/count byte, other-kind byte, or R-4.34 repair moved.

## Ubuntu 24.04 `linux/amd64` final-tree verification — GREEN

The local Docker substitute used Ubuntu 24.04 at image digest
`sha256:561618e2c15bf2397621dd04f96926663a3b5616c189cf7e38db7e82f5c538ea`
with `--platform linux/amd64` and Docker `--init`. Source came from the exact commit archive whose
SHA-256 is `4b86c44908e8625f7606a6b24e028035338352b71bd082975c71590c145aabd4`.
The eight workflow-pinned LLVM 22 packages were verified by SHA-256, exact version, package name,
and `amd64` architecture before installation. The non-root run raised `nofile` soft from 1024 to
the inherited hard value 1,048,576 before configure, build, and test.

The canonical 15-row Linux scope was measured through the dispositioned partition:

```text
CTest excluding harness-selftest: 14/14 selected rows passed, 0 failed
configured skips: safety-asan-ubsan, safety-fuzz-smoke
safety-tidy-analyzer: exactly one JUnit row, status=run, PASS
harness native partition: 967 passed, 3 skipped, 4 deselected in 8.34s
harness precise host-bind partition: 4 passed in 0.14s
```

The precise partition bound both pytest temporary storage and the fixture's home-cache storage to
the Docker Desktop host bind. Its four selected identities were exactly:

1. `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`
2. `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`
3. `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`
4. `test_credential_scanner_detects_entry_added_after_directory_enumeration`

The subsequent Catch2 XML measured the exact Linux job/key mapping:

```text
successes=412 failures=0 expectedFailures=0 skips=1
```

The sole skip identity was exactly
`threshold-parity per-agent distribution self-activates at R-4.29`, with disposition
`configured-deferred until R-4.29 makes the supported and parse ceilings equal`.

## Canonical-workflow differences disclosed

- Validation ran locally in disposable Docker, not in GitHub Actions.
- Exact cached LLVM package bytes were used instead of downloading them from GitHub Releases.
- Exact committed source was supplied by `git archive`, not by a checkout action.
- The one canonical `harness-selftest` row was measured through the Planner-authorized native and
  precise-host-bind partitions; the other 14 CTest rows ran together.
- `runuser`'s reset `nofile` soft limit was restored to the inherited hard limit before the suite.

The task-owned final container exited 0 and was removed explicitly. Task-owned transient inputs
were moved recoverably to the user's Trash. The unrelated running
`bivpak-slice-a-d885530-ci` container was left untouched. No Docker resource was pruned.

## Acceptance status and routing boundary

```text
A22 PASS — exact four-path scope, one commit, clean implementation worktree
A23 PASS — one advisory exit-0 row; SessionsStaged and all other rows byte-exact
A24 PASS — one member at the one measured session-row kind enum; no other enum moved
A25 PASS — both blob IDs independently reproduced; macOS and dispositioned Linux harness green
A26 PASS — C++ rows size and exit-map kind count both 27; function-form exit mapping retained
A27 PASS — macOS 410/0/0/3 and Linux 412/0/0/1 measured by job and mapping key, unchanged
```

The prior macOS receipt remains `410 / 0 / 0 / 3`, with its two `/mnt/c` portability skips and
the R-4.29 threshold-parity skip unchanged. The resumed Linux evidence supplies the previously
missing half of A27; it does not modify any implementation byte.

**R-3.39 remains OPEN.** This green partition is evidence for the authorized measurement method,
not evidence that the metadata tripwire was exercised, and it is not a timestamp-sensitive,
baseline, environmental, or anti-flake waiver. Every failure outside the exact four-case class and
any count movement remain a STOP.

m-3's byte review over all four landed files is still owed before any re-presentation. This floor
report routes upward to its Planner with m-3 informed on CC; it does not appoint another domain's
seat or claim that review. After owner review, the orchestrator spine check and master's separate
merge-gate re-presentation remain distinct gates. The commit stays local, unpublished, and
unwindable. Merge is not push is not release; the operator's release hold is ABSOLUTE.

ACTIONS_GIT_REF: local unpublished implementation commit `66704714390fd45dafe43a7272262b763a91cddc` remains unchanged on `s4-floor/slice-e-stage1a`; exact scope, object-stream blob hashes, clean implementation worktree, workflow non-diff, and Linux results freshly verified; task-owned exited container removed and task inputs moved recoverably to Trash; unrelated Docker container left untouched; this relay and one live-EOF INDEX row ride one explicit-path coordination commit; no source edit, GitHub Actions, push, PR, merge, publication, deployment, or release
RELAY_LINT: exact report freshness-linted before INDEX append; live INDEX EOF re-read immediately before one append; exact report re-linted with `--no-freshness`; `--index` and relay-root results read, with inherited registered root/INDEX findings preserved and disclosed rather than rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree is clean at `6670471`; coordination checkout foreign untracked relay and migration history preserved and excluded; only this report and its one INDEX append are staged for this seat

CARRY LIST:
- R-4.32 implementation object `66704714390fd45dafe43a7272262b763a91cddc` -> unchanged, LOCAL, UNPUBLISHED, unwindable
- macOS canonical suite -> GREEN at 6/6 rows and Catch2 410 successes / 0 failures / 0 expected failures / 3 skips with identities unchanged
- Linux selected CTest rows -> GREEN at 14/14, including one executed-and-passed safety-tidy-analyzer row and two configured skips
- Linux harness established partition -> GREEN at native 967 passed / 3 skipped / 4 deselected plus precise host-bind 4 passed
- Linux Catch2 mapping -> GREEN at 412 successes / 0 failures / 0 expected failures / 1 skip with the exact R-4.29 identity
- A22 through A27 -> SATISFIED under the Planner's narrow disposition
- R-3.39 metadata-sentinel residual -> remains OPEN; no waiver and no closure
- m-3 all-four-file byte review -> still owed before re-presentation; routed upward for assignment with m-3 informed on CC
- GitHub Actions, push, PR, merge, publication, deployment, and release -> not performed and not claimed; release hold remains absolute
