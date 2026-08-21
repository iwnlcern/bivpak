## SITREP — T2 reconstructed cleanly on T1 at `e172343`, then STOP: Linux GCC finds two missing `empty_config_keys` initializers; bounded corrective authority requested

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-reconstruct-linux-build-stop
PARENT_DISPATCH_ID: s4-matrix-wave-a-t1-accepted-resume-panel-first
IN_REPLY_TO: SITREP-IMPLEMENTER-T1-STAGE3-PANEL-PASS-EVIDENCE-REPAIRED-20260821-145821.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the relay's real-defect STOP rule fired; a new bounded in-lane corrective word is required before any T2 source or test edit, rerun, panel, or downstream reconstruction
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; old T2 `92a70c9cdf8a29f6591df558e04dbf26cf73d1ae`; reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T2 reconstruction completed as five commits on accepted T1, but Stage-2 STOPs on a candidate-caused Linux GCC Werror: test_repo_git.cpp designated initializers at 250 and 299 omit the newly added Git::Opts::empty_config_keys member; candidate clean/local at e172343, macOS canonical CTest 6/6 green, current count gate 410 versus observed 385 is candidate-neutral and matches T1 baseline, T3/T4 untouched; request one bounded two-site test correction and fresh local evidence, no integration or publication act

The ordered T2 reconstruction itself succeeded. Local branch `s4-matrix/arm1-t2`
is clean at `e17234356a53ef14b997a4cf038bd72898961424`, with accepted T1
`00c06d9` as its direct stack parent and exactly five replayed T2 commits:

```text
59ee009 -> ef2af9d  feat(repo): repo types + env-pinned git wrapper
9eb03d4 -> 97edc99  docs(s4): report Arm-1 T2 implementation
209c1c0 -> 24160f2  fix(review): scope git isolation to restore calls
792c110 -> 5a5c92e  fix(review): neutralize repo-local Git commands
92a70c9 -> e172343  fix(review): compose dynamic empty Git config overrides
```

The only replay conflict was the explicitly authorized `.relays/s4/INDEX.md` union.
All accepted-T1 rows were retained, the one historical T2 row remains exactly once in
its original time position, and no non-INDEX docs or product conflict occurred. The
reconstructed range is exactly the seven authorized paths and `git diff --check` is
clean. Candidate archive SHA-256 is
`16beb3f356f5c027fe5014ba7476e65b1679194bf3be50d56eacf2e3c6fb2cd8`.

## Stage-2 evidence and the real defect

macOS arm64 configured and built with the workflow harness environment. The canonical
selection passed 6/6 in 600.35 seconds: `biv_tests` 351.47s,
`harness-selftest` 5.41s, `harness-e2` 242.16s, plus the envelope and errno gates.
Catch XML records 385 successes, 0 failures, 0 expected failures, and 3 named skips.
The current workflow count contract expects 410/0/0/3 and therefore fires RED, but an
independent accepted-T1 run records the identical 385/0/0/3 and skip identities. This
is the already-routed count-gate shape class, not a T2 count movement, and is disclosed
rather than called green. The first macOS attempt used the host Python without the
locked harness modules and failed on missing `zstandard`; it is retained, and the
workflow-environment successor is the run relied upon.

The disposable `ubuntu:24.04 --platform linux/amd64` run verified all eight immutable
Clang-22 mirror hashes, installed clang-tidy 22.1.8, dropped to the non-root user, and
restored `nofile_soft=1048576` to `nofile_hard=1048576`. The canonical build then
stopped at 88 percent under GCC 13 `-Werror`:

```text
tests/test_repo_git.cpp:250:48: error: missing initializer for member
'biv::repo::Git::Opts::empty_config_keys' [-Werror=missing-field-initializers]
tests/test_repo_git.cpp:299:41: error: missing initializer for member
'biv::repo::Git::Opts::empty_config_keys' [-Werror=missing-field-initializers]
```

The exact cause is re-derived at the candidate bytes. Commit `e172343` adds
`std::vector<std::string> empty_config_keys;` between `isolate_global_config` and
`stderr_mode` in `Git::Opts`. The two designated aggregate initializers at
`tests/test_repo_git.cpp:244-250` and `:293-299` name every surrounding member but omit
the new vector. Apple Clang accepts them; the workflow Linux compiler's warning-as-error
does not. No Linux test executable or JUnit exists because compilation correctly failed.
This is candidate-caused and load-bearing, so Stage 2 is BLOCKED and no T2 panel begins.

## Requested narrow correction and holds

Requested authority is one bounded corrective commit touching only
`tests/test_repo_git.cpp`, adding `.empty_config_keys = {},` to exactly those two
designated initializers, followed by fresh macOS and local Docker Stage-2 evidence and
the required T2 panel at the corrected exact head. This preserves the public aggregate
shape and existing behavior. The broader alternative of changing `Git::Opts` itself is
not requested because it changes the production declaration when two test call sites
are the demonstrated defect.

T3 and T4 remain at their old heads and were not rebased or edited. `compare.py` remains
untouched. No remote CI, push, merge, PR mutation, publication, schema, deployment, or
release act occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: reconstructed only local `s4-matrix/arm1-t2` from old head `92a70c9` to `e172343` by replaying its five existing commits onto accepted T1 `00c06d9`; authorized INDEX union only; ran local macOS and disposable Ubuntu 24.04 amd64 validation; no correction after the real-defect STOP; no T3/T4 ref movement; no remote or integration act. This relay and one live-EOF INDEX row are the only shared-main writes and ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness before filing; live INDEX EOF re-read immediately before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T2 clean at `e172343`; T1 clean at `00c06d9`; main carries sibling-authored untracked relays and migration notes preserved and unclaimed; only this relay and its one INDEX append are this seat's docs-lane delta.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T2-RECONSTRUCTED-LINUX-BUILD-STOP-EMPTY-CONFIG-KEYS-20260821-153831.md` -> `s4-matrix.planner`, `s4.orchestrator-planner`
- T2 reconstructed cleanly on T1: `92a70c9 -> e172343`, exact five-commit replay, seven-path scope, authorized INDEX union only
- real candidate defect: Linux GCC Werror at test_repo_git.cpp 250 and 299 because both designated Git::Opts initializers omit new empty_config_keys; no test binary or JUnit produced
- requested narrow grant: two `.empty_config_keys = {},` test-site additions, one corrective commit, fresh local macOS/Linux Stage-2 evidence, then panel corrected T2; T3/T4 held
- count gate 410 versus observed 385 matches accepted T1 baseline and remains the routed shape finding; no merge, push, publication, schema, deployment, or release; release hold ABSOLUTE
