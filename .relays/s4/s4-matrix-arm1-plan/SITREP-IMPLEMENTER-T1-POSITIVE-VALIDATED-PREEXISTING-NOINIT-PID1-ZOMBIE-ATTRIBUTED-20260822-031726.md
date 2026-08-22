## SITREP — positive control validated; frozen base reproduces; descendant reds are pre-existing no-init PID-1 zombie retention, not T1-caused, and remain registered rather than closed

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t1-positive-validated-preexisting-pid1-zombies
PARENT_DISPATCH_ID: s4-matrix-wave-a-oracle-c-t1-intermittent-seek-positive
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-ORACLE-C-CONCURRED-T1-INTERMITTENT-SEEK-A-POSITIVE-DO-NOT-CLOSE-20260822-022336.md
RELATED_CONTEXT: SITREP-IMPLEMENTER-T1-LINUX-ATTRIBUTION-NONREPRODUCIBLE-NONZERO-CLAIMED-RULING-REQUESTED-20260822-015215.md; SITREP-PLANNER-MF1-ACCEPTED-ORACLE-CONCURRENCE-REQUESTED-ATTRIBUTION-DISCRIMINATOR-HAS-NO-POSITIVE-20260822-021222.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for the attribution — the conditional branch authorized at 022336 has resolved pre-existing; Orchestrator and master registry carriage is required before T1 Stage 5 so this observation remains disclosed and registered, not silently closed. Any source fix, local-Docker landmark edit, merge, push, PR mutation, schema act, or release remains separately unauthorized
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; final T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; exact observing T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.implementer
TO: s4.orchestrator-planner
CC: operator, s4-matrix.planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: POSITIVE FOUND AND ATTRIBUTED — the original Catch seeds reproduce 20 of 20 at exact T3; the shared probe reproduces 20 of 20 at frozen base before T1, so the condition is pre-existing; adding only Docker init makes both binaries pass 5 of 5 with zero zombies, isolating the no-init bash-PID-1 topology; register the residual, do not reopen T1 and do not call it closed

The missing must-be-YES has been found, and the now-meaningful base arm resolves the ordered
branch: **the descendant observation is pre-existing, not T1-caused.** It remains an open,
registered local-Docker-topology observation; attribution is resolved, but the observation is
not laundered into closed.

## Original topology recovered, not guessed

The exact corrected r1 outer command was recovered from the durable session record. It used
Ubuntu 24.04 amd64, bash as container PID 1, no Docker init, no CPU/memory/PID override, the
default PID namespace, UID 501 through `runuser`, `nofile` soft and hard 1048576, a fresh
single-head work copy, and serial `ctest --preset ci` with no `-j`. Tool versions match the
later green runs: GCC 13.3.0, CMake 3.28.3, Python 3.12.3, Git 2.43.0, and the same eight
checksum-verified LLVM 22.1.8 packages.

The original failure log supplied two controls the later focused runs did not preserve:

```text
subprocess Catch seed  3726052143
probe Catch seed       716421910
```

The green runs used fresh seeds and one-identity wildcard processes. The new runs execute the
whole Catch binaries with the original seeds in the original no-init topology.

## Positive at exact T3

Configure and build passed. On the first run, and on all 20 repetitions:

- `biv_subprocess_tests` failed the original descendant disappearance check: 20/20 positive;
- `biv_probe_tests` failed the original four test identities and seven assertions: 20/20
  positive. The timeout grandchild, detached group/escapee, clean-exit pipe holder, and both
  post-KILL handoff sections are the same assertion pattern as the retained original log.

The container began with zero zombies. After the first subprocess binary it held one PID-1
adopted zombie; after the first probe binary it held 30; after repetition 20 it held 585.
Those process snapshots contain shell, sleep, Python, and producer zombies with PPID 1.

## Positive at frozen base — ownership resolves pre-existing

The frozen base predates the standalone subprocess binary, so its shared probe tests run in
the monolithic `biv_tests` binary, as they did at that head. Configure and build passed.
With probe seed `716421910`, the same four probe identities and seven assertions failed on the
first run and all 20 repetitions: **20/20 positive at frozen base**. That container began
with zero zombies, held 29 after run 1, and 564 after run 20.

This is direct base evidence, not a probability bound. The condition exists before T1 and
must not reopen T1 Stage 4 for a guessed product edit. The T1-only subprocess test exposes the
same topology after T1, while the shared probe identities establish the pre-T1 existence.

## One-variable negative control isolates PID 1

At exact T3 I held source, package set, UID, limits, build, and original seeds fixed, adding
only Docker `--init`. `/proc/1/status` then names `docker-init` rather than bash. Results:

```text
exact-seed subprocess   5/5 pass
exact-seed probe        5/5 pass
zombies at initial, run 1, and run 5 snapshots   0
```

The assertions fail when killed descendants remain as zombies visible to `kill(pid, 0)` under
non-reaping bash PID 1; Docker's init reaps them and the same assertions pass. This is a
seed-sensitive local-container test topology, not evidence that product descendants remain
running on a canonical Linux host. Local Docker parity runs should include `--init` when the
measurement target is product behavior rather than PID-1 zombie retention. No repository
instruction or workflow byte is edited under this report-only authority.

## Registration and the separate T1 claims

Please carry this as a **pre-existing local-Docker-topology observation**, not T1-owned and
not closed. The exact recurrence recipe is no-init bash PID 1 plus the retained Catch seeds;
the negative control is the same run with Docker init. This satisfies `022336`'s positive and
base-arm attribution branch. A master registry identity and any due point remain the
Orchestrator/master act before T1 Stage 5.

The Linux `nonzero_exit` obligation remains claimed on exactly one Linux-discriminating
witness, not two. The earlier three-head runs also re-verify closed R-3.40 item 13 at the new
heads. Those facts are separate from the descendant topology and are supported by the prior
`t1-full-attribution-4Mjx1hvV` evidence.

## Durable evidence and disclosures

Evidence root:

```text
/Users/jack/Programming/bivpak/.superpowers/sdd/t1-positive-seek-xIRkhygd
```

`RECEIPTS.sha256` has 110 entries and freshly verifies 110 of 110. Its SHA-256 is
`62d2bc05204c8e2773f8d5c20ee963f499748ec75c1ec1e52c45c4bccd4ec28c`.
`EVIDENCE-NOTES.md` carries the command/topology map, source identities, counts, and
disclosures. The original retained evidence manifest also freshly verifies 27 of 27.

Three instrument defects are retained:

1. `r0-host-venv-defect` reconstructed the original setup-defective r0 command and stopped at
   the host Homebrew venv before configure/build/test. Corrected r1 excludes the venv.
2. The first host toolchain check used unsupported `sha256sum --strict` and printed usage; a
   portable per-entry `shasum` comparison then verified all eight packages with zero failures.
3. A read-only object census initially used the known-bad zsh `"$ref:path"` form and failed
   loudly. It produced no relied-on count. The braced `"${ref}:path"` rerun was validated on
   known-present and known-absent paths before recording the source blobs.

No source, test, fixture, CMake, workflow, ref, remote, PR, merge, schema, deployment, or
release act occurred. Every test container was disposable; no unrelated Docker resource was
pruned, stopped, or removed. Separately, the Oracle C rev1 plan was approved in review commit
`713e790`; no date-oracle implementation token has arrived and the T3 branch remains unmoved
and clean at `a3501cc`. T3 is not final or panelable; T4 remains held. The release hold is
ABSOLUTE.

ACTIONS_GIT_REF: read-only source-object and retained-session verification plus disposable local Ubuntu 24.04 amd64 containers at frozen base and exact T3. No candidate/ref/remote/integration/schema/release act. This report and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX inherited defects preserved and disclosed; post-commit exact-file verification without freshness.
FINAL_GIT_STATUS_SHORT: isolated T3 branch clean and unmoved at a3501cc; shared main preserves sibling-authored untracked history unchanged and unclaimed; only this report and its INDEX append belong to this docs act.

CARRY LIST:
- positive validated: original subprocess and probe seeds reproduce 20 of 20 at exact T3, including run 1, with the original five identities
- frozen base probe reproduces the same four shared identities and seven assertions 20 of 20, including run 1, so attribution resolves PRE-EXISTING and T1 must not reopen for a guessed fix
- original topology was serial CTest, no Docker init, bash PID 1, default PID namespace, no CPU/memory/PID override, UID 501, and raised nofile; later green runs did not preserve the original Catch seeds or whole-binary context
- PID-1 mechanism isolated: no-init snapshots rise from zero to 585 T3 zombies and zero to 564 base zombies; adding only Docker init yields 5 of 5 subprocess and probe passes with zero zombies throughout
- register the residual as pre-existing local-Docker-topology, not T1-owned and not closed; master identity and due point remain routed up before T1 Stage 5
- Linux nonzero_exit remains claimed on one Linux-discriminating witness and prior runs re-verify R-3.40 item 13; separate from descendant attribution
- evidence 110 of 110 verified at RECEIPTS SHA-256 62d2bc05; r0 host-venv, unsupported checksum flag, and zsh refspec defects retained and excluded from conclusions
- Oracle C rev1 approved at commit 713e790 but no implementation token exists; T3 clean/unmoved at a3501cc, not final/panelable; T4 and every remote, integration, schema, deployment, and release act held; release hold ABSOLUTE
