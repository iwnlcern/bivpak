## SITREP — R-4.32 landed in one four-file commit and macOS is green, but the required Linux harness self-test hits the four registered Docker metadata sentinels; STOP before m-3 review

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r432-linux-harness-stop
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-impl
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-S18-R432-DISPATCH-IMPL-TOKEN-20260819-235119.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the live token makes any test failure a STOP. The Planner must disposition the registered Docker Desktop metadata-sentinel class or provide a qualifying Linux runtime before m-3 byte review; this seat does not infer a waiver or widen the four-file fence
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
SUBJECT: BLOCKED — local R-4.32 commit 6670471 satisfies the exact four-file fence and macOS is green at unchanged counts, but Linux harness-selftest is 967 passed / 4 failed / 3 skipped on the four registered metadata sentinels, so A25 and A27 remain unsatisfied and m-3 review is not yet routed

BLOCKED / STOP — HUMAN DISPOSITION REQUIRED

## Exact landed state

The authorized implementation is one local, unpublished commit:

```text
66704716e819d5be3e52a1d031c62e0eb4dc25e8
fix(schema): add EntrySchemaSkipped contracts (R-4.32)
```

It is based directly on `4427bb30e23309af92432a06dc66d89463480d0c` and changes exactly the
four authorized paths, with 5 insertions and 3 deletions:

```text
harness/selftest/test_envelope.py
schemas/biv-exit-map.v1.json
schemas/biv-json-envelope.v1.schema.json
tests/test_envelope.cpp
```

`git diff --check 4427bb3..6670471` passes. The implementation worktree is clean.
No fifth path, product byte, workflow byte, count cell, other test byte, or R-4.34 repair
moved. No push, PR, GitHub Actions run, merge, publication, deployment, or release occurred.

## RED-first and landed contract receipts

The first test edit added only the new C++ `ExpectedRow`. The targeted schema-contract
case then failed for the intended reason: `EntrySchemaSkipped` was absent from both the
exit-map and envelope kind enum, and the existing cardinality check observed `26 == 27`.

After the two schema additions and the mechanically derived blob-pin updates:

- the exit-map row is `EntrySchemaSkipped / advisory / 0`, immediately after
  `UnknownAgentSkipped`;
- the envelope enum gains exactly one `EntrySchemaSkipped` member, immediately after
  `UnknownAgentSkipped`;
- the C++ expected row uses
  `exit_for_error(biv::ErrKind::EntrySchemaSkipped)`, immediately after
  `UnknownAgentSkipped`;
- the exit map has 27 rows and the envelope session-row kind enum has 7 members;
- the targeted C++ case passes with 95 assertions;
- the targeted Python schema-byte test passes.

Both final schema blob IDs were recomputed only after the final schema bytes existed:

```text
git hash-object schemas/biv-json-envelope.v1.schema.json
2147839ada7fec06a2807c4ccc56e39e8bdac712

git hash-object schemas/biv-exit-map.v1.json
ebace5b7d3d837da76604820dd95bbe2c1014848
```

## Acceptance status A22–A27

```text
A22  PASS — exactly four authorized paths and no other changed byte
A23  PASS — one exit-0 advisory row; SessionsStaged and every other row byte-exact
A24  PASS — one member at the single measured session-row kind enum; no other enum moved
A25  STOP — both landed blob IDs were recomputed and the targeted pin test passes, but the
            required full Linux harness-selftest is not green
A26  PASS — C++ rows size and exit-map kind count are both 27; cardinality test passes and
            the exit column uses exit_for_error(...)
A27  STOP — macOS re-observed unchanged counts; Linux CTest is red before the workflow's
            later Catch2 count gate, so no Linux count is claimed or borrowed
```

## macOS final-tree verification — GREEN and unchanged

At commit `6670471`, the canonical macOS selector completed 6 of 6 rows green:

```text
generated_envelope_reset          PASS
biv_tests                         PASS
errno_table_gate                  PASS
generated_envelope_conforms       PASS
harness-selftest                  PASS
harness-e2                        PASS
100% tests passed, 0 failed out of 6; total 599.85s
```

The final-tree Catch2 XML measured the exact job/key mapping:

```text
successes=410 failures=0 expectedFailures=0 skips=3
```

The three skip identities were unchanged: the two `/mnt/c` portability cases and
`threshold-parity per-agent distribution self-activates at R-4.29`.

## Ubuntu 24.04 `linux/amd64` Docker verification — STOP

The local substitute used Ubuntu 24.04 at image digest
`sha256:561618e2c15bf2397621dd04f96926663a3b5616c189cf7e38db7e82f5c538ea`
with `--platform linux/amd64` and Docker `--init`. The committed source was supplied from a
`git archive` of `6670471`, SHA-256
`4b86c44908e8625f7606a6b24e028035338352b71bd082975c71590c145aabd4`, so no host build
artifact entered the run.

The eight pinned LLVM packages were reused from the local immutable cache instead of being
downloaded through GitHub. Every workflow SHA-256, package name, exact version, and `amd64`
architecture was freshly verified before install. `clang-tidy-22 --version` reported LLVM
22.1.8. The non-root `runuser` drop reset `nofile` soft to 1024; it was raised back to the
inherited hard value 1,048,576 before configuration and tests. CMake's required-clang-tidy
probe and the complete build passed.

The full 15-row Linux CTest preset completed with one failed row:

```text
12 rows passed
2 configured rows skipped: safety-asan-ubsan, safety-fuzz-smoke
1 row failed: harness-selftest
safety-tidy-analyzer: exactly one JUnit row, executed with status run, PASS
```

The harness result was:

```text
967 passed, 4 failed, 3 skipped out of 974
```

The four failures are exactly the previously registered Docker native-filesystem metadata
sentinels, not a new or partial identity set:

1. `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`
2. `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`
3. `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`
4. `test_credential_scanner_detects_entry_added_after_directory_enumeration`

A separate classification run put pytest's temporary tree on a Docker Desktop host bind;
those exact four cases then passed 4 of 4 in 0.14 seconds. That supports the registered
native-filesystem timestamp-coalescing diagnosis, but it is diagnostic only: the live token
says **any test failure is a STOP**, and no existing history is treated as a waiver.

Because CTest returned nonzero, the workflow-equivalent sequence stopped before its later
Linux Catch2 count step. This report therefore does not invent, infer, borrow, or transcribe
`successes=412 / failures=0 / expectedFailures=0 / skips=1`; the Linux four-value receipt is
unmeasured on this run and A27 remains open.

## Requested disposition

Planner: either provide a qualifying Ubuntu 24.04 amd64 runtime on which the complete
canonical suite is green, or obtain and state an explicit ruling for the already-registered
Docker Desktop metadata-sentinel partition and authorize a resumed Linux observation. The
four-file commit remains local and unwindable. No product or harness fix is proposed: every
such path is OUT, and the implementation delta does not touch any failing test or mechanism.

m-3 byte review over the four landed files is deliberately **not** routed as complete while
A25 and A27 are red. After an authorized Linux disposition and a qualifying unchanged-count
receipt, the normal m-3 review path may resume.

ACTIONS_GIT_REF: local unpublished implementation commit `66704716e819d5be3e52a1d031c62e0eb4dc25e8` exists on `s4-floor/slice-e-stage1a`; implementation worktree clean; two task-owned Docker containers were disposable and removed automatically; the unrelated pre-existing `bivpak-slice-a-d885530-ci` container was left untouched; this report and one live-EOF INDEX row ride one explicit-path coordination commit; no push, PR, GitHub Actions, merge, publication, deployment, or release
RELAY_LINT: exact report freshness-linted before INDEX append; live INDEX EOF re-read before one append; exact report re-linted with `--no-freshness` after filing; inherited INDEX/root findings preserved and disclosed rather than rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree is clean at `6670471`; coordination checkout foreign untracked relay and migration history is preserved and excluded; only this report and its one INDEX append are staged for this seat

CARRY LIST:
- R-4.32 four-file implementation commit `6670471` -> LANDED LOCAL, UNPUBLISHED, unwindable
- macOS canonical suite and count mapping -> GREEN at 410 / 0 / 0 / 3
- Linux canonical suite -> STOP at harness-selftest, 967 passed / 4 failed / 3 skipped
- four exact registered metadata sentinels -> 4 of 4 PASS only on host-bind temporary storage; diagnostic, not a waiver
- Linux Catch2 job/key count mapping -> NOT REACHED and NOT CLAIMED
- m-3 all-four-file byte review -> HELD until Planner dispositions the token's failure STOP
- push, PR, GitHub Actions, merge, publication, deployment, and release -> not authorized; release hold remains absolute
