## IMPL REPORT — Arm-1 Wave A T1 complete: generic argv runner extracted, probe reduced to adapter, PR #16 open

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1-t1
PARENT_DISPATCH_ID: s4-matrix-arm1-impl-wave-a-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-WAVE-A-DISPATCH-R1-20260806-021238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the durable T1 completion report under the live corrected Wave-A dispatch; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: T1 COMPLETE — one generic argv runner, thin probe adapter, relocated successor seal, reviewed and fresh-green at E2; stacked PR #16 ready, merge/release held

### Result

T1 is complete on `s4-matrix/arm1-t1`, based on the live local docs lane at
`main@285cfc4758fab77f70832555eb8461ac0ed86251`. The implementation commits are:

- `2908b09dd2ae67f3b6a5173ce77b334ad02b9d38` — `feat(support): extract generic argv runner; probe becomes adapter`
- `44953a9798a39f6e55734fa831982e98d3270ed1` — `fix(support): drain separate subprocess streams fairly`

The ready-for-review stacked PR is
https://github.com/iwnlcern/bivpak/pull/16, targeting `main`. No merge or
release action was taken.

### Implemented surface

- Added `src/core/support/subprocess.{hpp,cpp}` with caller-supplied executable,
  argv, and environment; split or spawn-time merged stderr; raw capped capture;
  optional direct stdout-file streaming; exit-as-data; own-process-group
  lifecycle; and timeout TERM-to-grace-to-KILL cleanup with direct-child reap.
- Kept one process-safety implementation and one `posix_spawn` call site, in
  `subprocess.cpp`.
- Reduced `run_version_probe` to path/pin resolution, request construction,
  phase tracing, UTF-8 sanitation/capping, and mapping runner flags into the
  existing `ProbeEvidence` outcomes. The existing spawn-time merged topology is
  preserved.
- Re-scoped the `probe.hpp` law comment without weakening the agent-execution
  prohibition: the operator ruling remains absolute for agents; argv-only git
  execution is separately governed by the sealed Step-4 contracts.
- Added the dedicated `subprocess` and `probe` CTest gates and all seven planned
  runner behaviors. The separate-stream test also carries a 1 MiB stderr / quiet
  stdout saturation regression, which exposed and closed a real starvation bug.

### T1.5a bounded relocation

The only `tests/test_probe.cpp` delta is inside the granted test case, `version
probe has one traced readiness primitive`: its source anchors now inspect
`subprocess.cpp`, its `probe.cpp` half asserts zero `poll`/`select`/`ppoll`
primitives, and its successor note was added. No behavioral probe assertion was
changed.

the one-traced-readiness-primitive seal moved with its machinery from probe.cpp to subprocess.cpp; probe.cpp's half strengthened to zero-primitives.

### Verification and review

- TDD RED witnessed before implementation: missing runner header/target, then
  seven behavioral failures against the declaration stub.
- `cmake --build --preset dev -j2` — PASS.
- `ctest --preset dev -R '^(subprocess|probe.*)$' --output-on-failure` — PASS,
  3/3 (`subprocess`, `probe`, `probe_envelope_schema`) in 12.14s.
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure` — PASS,
  15/15 supported tests in 395.46s; `biv_tests` 217.03s, `probe` 10.61s,
  `harness-e2` 160.50s, and `safety-build-werror` green. The existing
  platform-gated `safety-asan-ubsan`, `safety-tidy-analyzer`, and
  `safety-fuzz-smoke` cases reported SKIPPED.
- Structural guard — PASS: exactly one `posix_spawn(` under
  `src/core/support/`, in `subprocess.cpp`; none of `poll(`/`select(`/`ppoll(`
  occur in `probe.cpp`.
- Independent scoped review — APPROVE, no remaining Critical or Important
  findings. The first review found split-stream starvation and a missing exact
  `probe` CTest gate; both were reproduced RED, fixed, regression-tested, and
  approved on re-review.
- The final restack from `56df1d9` to `44953a9` added only the concurrently
  filed `.relays/s4/**` docs-lane bytes from `main@285cfc4`; product and test
  bytes are identical to the full-green reviewed tree.

### Boundary and continuation

Only T1 and the bounded T1.5a relocation were implemented. No `src/core/repo/`,
harness, manifest, scan, pack, open, schema, ledger-status, Wave-B/C/D, merge,
or release surface was changed. T2 remains next on the required linear stack,
based on this T1 head; all F-fenced work remains held.

ACTIONS_GIT_REF: `s4-matrix/arm1-t1@44953a9798a39f6e55734fa831982e98d3270ed1`; code commits `2908b09dd2ae67f3b6a5173ce77b334ad02b9d38`, `44953a9798a39f6e55734fa831982e98d3270ed1`; PR https://github.com/iwnlcern/bivpak/pull/16; this report and its append-only INDEX row are the only post-code filing delta, with carrying commit recorded in branch history after filing; no merge or release.

FINAL_GIT_STATUS_SHORT:
none — clean at the code head before this report + INDEX write; those two governed filing paths are the only intended delta and are committed together after fresh exact-file and INDEX lint.

Fresh at 20260806-030233 before this report + INDEX write.
