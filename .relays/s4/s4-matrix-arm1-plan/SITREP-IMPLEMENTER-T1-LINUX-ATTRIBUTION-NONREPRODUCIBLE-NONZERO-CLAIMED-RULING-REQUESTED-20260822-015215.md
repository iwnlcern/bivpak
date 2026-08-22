## SITREP — Linux attribution measured at frozen base, final T1, and exact T3; descendant reds do not reproduce, so neither prescribed cause branch is proven; nonzero_exit is now claimed with real evidence

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t1-linux-attribution-nonreproducible
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-composition-accepted-date-oracle-authorized
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-T3-COMPOSITION-ACCEPTED-DATE-ORACLE-AUTHORIZED-PROBE-REDS-NEED-OWN-ATTRIBUTION-20260821-235525.md
RELATED_CONTEXT: SITREP-IMPLEMENTER-T3-RECONSTRUCTED-MACOS-GREEN-LINUX-DATE-ORACLE-BLOCKER-20260821-233755.md; SITREP-IMPLEMENTER-T1-TIDY-FIX-COMPLETE-20260821-052056.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the measured result fits neither prescribed attribution branch; Orchestrator disposition is required before the intermittent descendant observation is labeled pre-existing, T1-caused, fixed, or closed
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; final T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; exact observing T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.implementer
TO: s4.orchestrator-planner
CC: operator, s4-matrix.planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: ATTRIBUTION MEASURED — repeated full-suite and exact-identity runs do not reproduce the prior candidate-only descendant reds at base, final T1, or exact T3; deterministic T1 regression refuted but pre-existing and T1-caused branches both unproven; Linux nonzero_exit contract passes with real evidence and is claimed; request a third-outcome ruling

The measurement ordered at `235525` is complete, but it does not produce either of the two
forecast outcomes. I will not force it into one.

The original retained `a3501cc` Linux run named five descendant-cleanup failures:

- `run_argv timeout sweeps its process group and reaps its child` in the subprocess binary;
- `version probe times out, reaps its direct child, and kills the process group`;
- `version probe acknowledges a successfully detached descendant`;
- `version probe preserves clean exit while disposing a pipe-holding grandchild`;
- `post-KILL ownership falls back to blocking reap when handoff fails`.

I ran the full Ubuntu 24.04 amd64 suite from byte-pinned Git archives at the frozen base
`a02a65b` and final T1 `00c06d9` twice, then reran the full suite at the exact observing T3
head `a3501cc`. Every run used the same disposable-container topology, eight checksum-verified
Clang 22.1.8 packages, non-root user, and `nofile` soft raised to the inherited hard limit of
1048576.

All five configure/build arms passed. In all five valid full-suite runs, every C++ row passed:
no subprocess red and no probe red. The only red row was `harness-selftest`, with membership
rotating inside the already-owned R-4.35 family; at exact T3 it additionally included the
already-routed Git-date oracle. This full-suite comparison therefore does not reproduce the
observation at either side of the requested base/candidate comparison or at the exact head
that originally showed it.

I then ran the exact identities five times each in fresh test processes. The frozen base has
the four probe identities but predates the standalone `run_argv` subprocess case; that absence
is recorded, not called a pass. Results:

```text
                                  frozen base     final T1      exact T3
shared probe identity 1           5/5 pass        5/5 pass      5/5 pass
shared probe identity 2           5/5 pass        5/5 pass      5/5 pass
shared probe identity 3           5/5 pass        5/5 pass      5/5 pass
shared probe identity 4           5/5 pass        5/5 pass      5/5 pass
T1-only run_argv subprocess       not present     5/5 pass      5/5 pass
```

That is 60 passing shared-probe executions plus ten passing executions of the T1-only
subprocess identity after the full-suite comparisons. It refutes a deterministic regression
at T1 and rules out “the full suite always triggers it.” It does not prove the failure was
pre-existing, because no base arm failed. It also does not prove T1 causation, because final
T1 and exact T3 are repeatedly green and the original observation has not reproduced.

The faithful attribution is therefore: **one intermittent candidate-surface observation,
cause unresolved**. It is not eligible for the prescribed pre-existing residual branch, and
there is no reproducible defect on which to base the prescribed T1 fix branch. Please rule the
third outcome: retain/register it as an un-attributed flaky observation with a due point,
require a larger discriminator, or conservatively reopen T1 Stage 4 without authorizing a
guessed product edit. Until that ruling, I do not label it pre-existing, T1-owned, or closed.

## Linux nonzero_exit — real evidence now closes the separate owed contract

The `nonzero_exit` surface separated from the descendant observation. Two real Linux cases
were executed at frozen base, final T1, and exact T3 in the valid runs:

- `version probe reports a nonzero child exit`: 6 assertions, 1 case, pass;
- `version probe does not fall back to PATH when a pinned executable cannot spawn`: on Linux
  its expected outcome is `nonzero_exit`; 10 assertions, 1 case, pass.

Both pass repeatedly at every relevant head. I therefore claim the Linux `nonzero_exit`
contract that remained owed in T1 Stage 4. This claim does not dispose the unrelated intermittent
descendant-cleanup observation.

## Instrument disclosures and durable evidence

Evidence root:

```text
/Users/jack/Programming/bivpak/.superpowers/sdd/t1-full-attribution-4Mjx1hvV
```

`RECEIPTS.sha256` contains 146 entries and a fresh verification returns 146 of 146 OK. Its
SHA-256 is `05b1b2c0b31f2db4ca579a64d1c951166ddce8866dda87061675a3b980e402fb`.
`EVIDENCE-NOTES.md` maps every run.

Two instrument defects are preserved rather than laundered:

1. r0 omitted `libsqlite3-dev`; both heads stopped identically at configure before any build.
   It is setup evidence only.
2. r2's first stress selector used comma-bearing exact Catch2 names. Catch2 parsed the commas
   as filter separators, selected zero tests, and returned failure. r2's full-suite evidence is
   valid; its stress counts are not. r3 replaces those selectors with validated unique wildcard
   fragments, and every log shows five real `All tests passed` results.

The raw r0 through r3 outputs remain separate. Limitation disclosed: the scratch `phase.sh`
was evolved in place while correcting the r2 selector, so exact intermediate driver bytes were
not copied into each earlier subdirectory at run time; the raw logs, statuses, environments,
source archives, and final corrected driver are retained and hashed. No result depends on
retroactively reconstructing an intermediate script.

No candidate source, test, fixture, CMake, or ref changed during attribution. The T3 worktree
remains clean at `a3501cc`. The separate date-oracle PLAN is under MUST-REVISE review and no
token exists. T3 is not final or panelable; T4 remains held. No remote CI, push, PR mutation,
merge, publication, schema, deployment, or release occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only archive and diff resolution plus disposable local Ubuntu 24.04 amd64 full-suite and exact-identity measurements at frozen base a02a65b, final T1 00c06d9, and exact T3 a3501cc; no source/test/ref/remote/integration act. This report and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects preserved; post-commit exact-file no-freshness verification.
FINAL_GIT_STATUS_SHORT: T3 worktree clean at a3501cc; shared main retains sibling-authored untracked history unchanged and unclaimed; only this report and its one INDEX append belong to this docs act.

CARRY LIST:
- exact failing identities were read from the retained original log before measurement
- two valid full-suite runs at frozen base, two at final T1, and one at exact T3 have all C++ rows green; only known harness-selftest observations remain
- corrected stress gives every shared probe identity 5 of 5 at all three heads and the T1-only subprocess identity 5 of 5 at final T1 and exact T3
- result fits neither ordered branch: deterministic T1 regression refuted, but pre-existing and T1-caused attribution both unproven; request explicit third-outcome ruling and authorize no guessed edit
- Linux nonzero_exit contract is separately claimed with both real cases passing repeatedly at base, final T1, and exact T3
- evidence 146 of 146 verified; r0 missing-SQLite and r2 Catch-selector defects preserved and excluded from product conclusions
- T3 unchanged, not final or panelable; date plan has no token; T4 and all remote, integration, schema, deployment, and release acts held
