## SITREP — F-URL-1 engine-only corrective complete: one six-path commit, fourteen real-Git units, both-platform local evidence, and the zero-m-3-surface absence bar measured

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-engine-only-impl-complete-r1
PARENT_DISPATCH_ID: s4-matrix-furl1-engine-only-impl-token
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-ENGINE-ONLY-TOKEN-SIX-PATHS-M-REV8-A6-REV14-20260825-164136.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-ENGINE-ONLY-M-REV8-A6-REV14-SIX-PATHS-FOURTEEN-UNITS-20260825-152627.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: audit-record
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
LOCKED_DESIGN_SHA256: c41d015fd867464aefc479e25f0fc7521b5e259cb88d79cb1d36fe05db19150c
POST_STAMP_SHA256: 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771
CONSUMED_CONTRACT: m1-addendum-M-2966b839-lock-20260825 (57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no — the authorized engine-only edit is complete; the next acts are the token-required m-1 engine-byte review and m-3 independent absence-byte review, while merge still requires a separate MERGE-GATE and remains unclaimed
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: Engine-only F-URL-1 corrective implemented at bb06d7ef801c5afa31a91155f45a520db6f4a64a as exactly one commit over 6ba01ef; the four network populations carry one typed endpoint, the central same-context pre-spawn gate and narrow comparator are bound, absent hook refuses, fourteen real-Git units and twelve named mutants separate, macOS canonical rows pass, Linux candidate rows pass with only registered R-4.35/R-4.38 disclosed, and the landed path set proves zero m-3 surface and zero wiring

The token, approving review, M rev8, A6 rev14, SR-URL, and all six base preimages were
re-derived before the first edit. The implementation is landed on the isolated candidate branch
`s4-matrix/arm1-t4` as exactly one commit:

```text
bb06d7ef801c5afa31a91155f45a520db6f4a64a
fix(repo): gate rewritten network endpoints
parent 6ba01ef92ef5052b317f6210fa202d5577e1e6c1
```

`git rev-list --count 6ba01ef..HEAD` returns `1`; the candidate worktree is clean.

## Implemented bytes

The landed commit contains exactly the six authorized paths:

```text
src/core/repo/git_exec.hpp
src/core/repo/git_exec.cpp
src/core/repo/types.hpp
src/core/repo/eligibility.cpp
src/core/repo/restore.cpp
tests/test_repo_engine.cpp
```

The engine now carries exactly one typed requested endpoint on every network-class invocation.
`invoke_git` refuses zero or multiple carriers before any resolution or network spawn, resolves the
effective endpoint with real `git ls-remote --get-url` under the same cwd/environment/options as the
pending call, and compares only the sealed equivalences: lowercase scheme/host, one trailing slash,
HTTP/HTTPS default ports, and restricted absolute scp-to-SSH equivalence with exact userinfo and no
URL port. Everything else diverges with both verbatim addresses retained.

The run-scoped hook/memo is keyed by requested/effective/repo, invokes once per triple, and defaults
to refusal when absent. Refusal is typed `url_divergence_refused`; restore refusal is entry-fatal and
retains the repo id/relpath. Population is closed over all four engine network sites: eligibility
advertisement, restore ref-proof fetch, root-overlay proof fetch, and non-full clone. Full bundle
clone remains outside the network class. No product consumer or m-3 surface was wired in this act.

## Real-Git and mutation evidence

Fourteen top-level `F-URL-1 real git ...` units execute actual Git processes at the engine seam:
sealed `(a)` non-interactive, `(b)`, `(c)`, and `(e)` through `(o)`, with both mandatory `(n)` arms.
The focused final receipt is 56 assertions in 14 cases; the full repo-engine binary is 408 assertions
in 55 cases. Leg `(d)` wholly and `(a)` interactive remain deferred to the later integration act as
sealed; neither is simulated or counted.

Each of the twelve named mutants was applied at its own leg, observed RED, then restored before the
final green run: `(b)` ref-proof carrier removal; `(e)` raw-string comparator; `(f)` scheme ignored;
`(h)` wrong resolution cwd; `(i)` overlay-proof carrier removal; `(j)` clone carrier removal; `(k)`
operand inference; `(m)` relative-scp widening; `(n.i)` scp explicit-22 equivalence; `(n.ii)` URL
SSH-22 elision; the broad SSH-22 default elision that REDded both mandatory arms; and `(o)` an
HTTPS-only default-port normalizer.

## Local platform receipts and honest residual accounting

macOS, on the final bytes:

- `cmake --build --preset ci-macos -j2` passed.
- The canonical selection passed 6/6 in 646.38 seconds: `biv_tests`, `harness-selftest`,
  `harness-e2`, `errno_table_gate`, `generated_envelope_conforms`, plus the generated reset
  dependency. `biv_tests` passed in 377.41 seconds and harness E2 in 256.12 seconds.
- The separate workflow count receipt is `{successes: 385, failures: 0, expectedFailures: 0,
  skips: 3}` with the exact three expected skip identities. The workflow's stale expectation is
  `410/0/0/3`; this is the registered R-4.38 single-binary count-gate defect, not hidden as green.
- A broader developer-preset run had one macOS-only infrastructure red: `safety-hardening` reports
  `readelf unavailable`; the functional rows passed and no whole-suite-green claim is made.

Linux, in a disposable Ubuntu 24.04 `linux/amd64` Docker container under `--init`, with nofile soft
raised to the inherited hard limit `1048576/1048576`:

- GCC 13.3.0 build passed under Werror after replacing four test-only partial aggregate initializers
  that GCC diagnosed and Clang accepted.
- The full 19-row CTest run has one red row: `harness-selftest`, containing exactly the registered
  R-4.35 flaky set
  `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`,
  `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`, and
  `test_credential_scanner_detects_entry_added_after_directory_enumeration`.
  `repo_engine`, `biv_tests`, harness E2, Werror, hardening, and all other executed rows passed;
  ASAN/UBSAN and fuzz-smoke were declared skips.
- The clang-tidy-22 row was present, executed, and passed; its JUnit gate reports `status='run'`.
- The separate Linux count receipt is `387/0/0/1` against the stale `412/0/0/1`, the same registered
  R-4.38 defect. No whole-suite-green claim is made.

Differences from the hosted workflow were bounded and disclosed: the container consumed the local
eight-package LLVM 22 mirror after verifying every SHA-256, package name, pinned version, and amd64
architecture instead of downloading those same assets through GitHub; plain `ubuntu:24.04` needed
`openssh-client`, which the hosted runner preinstalls; build parallelism was capped at `-j2`; and the
candidate was copied into the disposable container with host `.git`, build, and venv state excluded.
The exact named container was removed after evidence capture; no unrelated Docker resource was
pruned or removed. No remote CI was triggered.

## Landed absence bar and next gate

Over the landed commit, the exact path-set predicate returns `SCOPE_DIFF_RESULT=all-in` and
`ABSENCE_BAR=PASS`. There are zero changed bytes under `src/cli/**`, `src/core/report/**`,
`schemas/**`, `harness/**`, `src/core/manifest/**`, `src/core/pack/**`, `src/core/open/**`,
`.github/**`, `tests/test_cli.cpp`, or `tests/test_envelope.cpp`: zero envelope, schema, exit-map,
CLI, help, prompt, or reachability wiring. `git diff-tree --check HEAD^ HEAD` is clean.

Route commit `bb06d7ef801c5afa31a91155f45a520db6f4a64a` first to m-1 for engine-byte review and then to
m-3 for independent absence-byte review as the token requires. The candidate branch and isolated
worktree are preserved for those reviews. This relay is report-only: it grants no merge, push, PR
mutation, remote CI, publication, deployment, release, or T4 FINAL claim. A separate MERGE-GATE is
required; the operator's release hold remains ABSOLUTE.

ACTIONS_GIT_REF: candidate branch `s4-matrix/arm1-t4` moved exactly once from base `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` to one commit `bb06d7ef801c5afa31a91155f45a520db6f4a64a`, touching only the six authorized paths; local macOS and disposable Linux validation only; no remote CI, push, PR mutation, merge, publication, deployment, release, or T4 FINAL act. Docs lane: this daemon draft is submitted through relay-engine 2.9.2; the daemon alone renders the relay and owns INDEX/SEATS projections
FINAL_GIT_STATUS_SHORT: isolated candidate clean at `bb06d7ef801c5afa31a91155f45a520db6f4a64a`, exactly one commit over `6ba01ef`, six landed paths, no untracked bytes; shared main retains its pre-existing sibling-authored modified SEATS projection, untracked relay history, and docs path unchanged except for daemon-owned effects attributable to this submission
RELAY_LINT: submission is conditioned on relay-engine 2.9.2 admission; after rendering, exact-file lint, lane-root lint delta, digest/path receipt, and daemon pending-render state are re-measured before handoff; the pre-existing daemon status reports four conflicts and zero pending renders, disclosed and not repaired by this seat

CARRY LIST (D-8.5):
- the daemon-rendered completion relay -> TO `s4-matrix.planner`
- one candidate commit `bb06d7ef801c5afa31a91155f45a520db6f4a64a` over sealed base `6ba01ef`; exactly the six authorized engine/test paths; candidate worktree clean; zero push/merge/PR/remote-CI/publication/deployment/release act
- central same-context pre-spawn resolution, one typed endpoint carrier, sealed narrow comparator, run-scoped requested/effective/repo hook+memo, absent-hook fail-safe refusal, typed restore-fatal divergence, and population across all four engine network sites; full bundle clone out of class
- fourteen real-Git top-level units, 56 assertions; full repo-engine 408 assertions in 55 cases; twelve named mutants each RED at its own leg; `(d)` and `(a)` interactive remain honestly deferred
- macOS canonical selection 6/6 green on final bytes; macOS count `385/0/0/3` vs stale `410/0/0/3` disclosed as R-4.38; developer hardening row cannot run without `readelf`, so no whole-suite-green claim
- Linux GCC/Werror build, repo-engine, product tests, harness E2, hardening, and executed clang-tidy-22 gate pass; only exact R-4.35 harness-selftest flakes red; count `387/0/0/1` vs stale `412/0/0/1` disclosed as R-4.38; declared sanitizer/fuzz skips; no whole-suite-green claim
- landed `SCOPE_DIFF_RESULT=all-in` and `ABSENCE_BAR=PASS`: zero m-3 surface and zero wiring. Next: m-1 engine-byte review, then m-3 independent absence-byte review; MERGE-GATE still required; release hold ABSOLUTE
