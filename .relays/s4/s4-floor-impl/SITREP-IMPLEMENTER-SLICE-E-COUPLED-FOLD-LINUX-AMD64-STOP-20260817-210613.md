## SITREP — Slice E coupled fold implemented and host-green, but the required Ubuntu 24.04 amd64 count run has one inherited emulation-only product failure; STOP before count transcription or product commit

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-linux-amd64-stop
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-impl
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the live token requires one green head on both target platforms before count transcription and its one coherent product commit; the required Linux XML instead reports one failure in an OUT-of-scope inherited probe, so the Planner must disposition the runtime or the named exception and no product commit is inferred
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-DISPATCH-IMPL-TOKEN-20260817-193748.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: BLOCKED — coupled-fold bytes and every named mutant are implemented and macOS-green, but Linux target-local XML is 411/1/0/1 because amd64 emulation classifies one inherited invalid executable as nonzero_exit rather than spawn_error; workflow failure count is observe-and-route, so no counts or product commit land

BLOCKED / STOP — HUMAN DISPOSITION REQUIRED

## Exact state

The coupled-fold implementation is complete in the authorized local worktree, but it is
deliberately **uncommitted** because step 3 of the live token did not produce the required
green Linux head:

- branch: `s4-floor/slice-e-stage1a`;
- unchanged HEAD/base: `972919137203cb2ecb1d9f4bba8d8cd31e27befc`;
- worktree: `/Users/jack/.config/superpowers/worktrees/bivpak/s4-floor-slice-e-stage1a`;
- exact uncommitted delta: 7 authorized paths, 460 insertions and 4 deletions;
- `git diff --check`: PASS at 2026-08-17T21:06:13-0700;
- no product commit, count transcription, push, PR, GitHub Actions run, merge,
  publication, deployment, or release.

The seven changed paths are:

```text
.github/workflows/s2-harness.yml
src/core/manifest/manifest.cpp
src/core/manifest/manifest.hpp
src/core/open/open.cpp
tests/test_cli.cpp
tests/test_manifest.cpp
tests/test_sessions.cpp
```

`tests/fixtures/slice-e/**` was an optional IN row and was not needed. Every OUT row remains
zero-diff, including `src/core/pack/**`, `src/core/open/sessions.cpp`,
`src/core/open/render.cpp`, `src/core/report/envelope.cpp`, `src/cli/main.cpp`, and the
harness.

The workflow diff is still only m-3's exact ruled skip-identity line. The four count lines
remain untouched. This is intentional: Linux `failures=1` is an OBSERVE-AND-ROUTE finding,
never a number this seat may normalize or hide.

## Implemented contract

The implementation follows locked Addendum L rev7 rather than the dispatch paraphrase:

- `AgentSessionEntry` gains a separate flat `stub_member_footprint` carrier. It has an
  explicit empty in-class default so the unchanged Linux `pack.cpp` aggregate remains
  Werror-clean.
- At the over-ceiling stub gate, the parser reads only entry `artifacts`, entry `children`
  names, and each child `artifacts`; graph values remain unread. Missing arrays preserve the
  existing minimal future stub.
- Entry, child, children-count, and total caps fail without truncation. The children cap is
  checked in-loop before reading child 1,025. Cap details are identity-free.
- Artifact grammar uses the existing validator. Stub-vs-parsed, same-stub, and two-stub
  collisions join the existing manifest-wide uniqueness set.
- Three duplicate-bearing-key details are distinct and equality-tested:
  `stub-footprint-entry-artifacts-duplicate-key`,
  `stub-footprint-entry-children-duplicate-key`, and
  `stub-footprint-child-artifacts-duplicate-key`.
- `open.cpp` builds a separate allow-only stub-member set and widens only member admission.
  `required_agent_members` and its presence-enforcement loop remain semantically unchanged,
  so a declared-but-absent stub member is not required.
- CLI fixtures use one off-by-default payload control. Existing callers retain their old
  image shape by construction. Entry-carried and child-only present members open at exit 0;
  the declared-absent control also opens at exit 0.
- The two-agent sessions witness independently reports one Codex and two Claude unparsed
  entries. No footprint value feeds A5 counts, notices, summaries, or envelopes.
- No stub-class annotation text was added; leg (h) and the forbidden listing halves remain
  absent rather than vacuously asserted.

## RED-first and named mutant receipts

The original implementation-free tree produced the required behavioral RED:

- `[stub-footprint]`: 5 cases, 1 passed and 4 failed; 11 manifest assertions exposed the
  accepting old parser, and both present-member CLI variants returned exit 3
  `UnmanifestedMember` with the exact member path.
- Declared-absent leg (q) and the two-agent leg (g) controls were green before the repair.

Every named mutant compiled, executed against its killing fixture, reddened behaviorally,
was removed, and returned GREEN:

- (m), reading hostile child `original_id`: its positive graph-unread fixture failed;
- (n), reading hostile child `parent_id`: its positive graph-unread fixture failed;
- (o), reading hostile entry `original_path`: its positive graph-unread fixture failed;
- (q), unioning the footprint into `required_agent_members`: the declared-absent CLI leg
  returned exit 3 `IntegrityFailurePreApply`, exact path
  `agents/codex/stage1b-ii-0.jsonl`, detail `missing-agent-member`.

Final targeted GREEN on macOS and Linux is identical:

```text
[stub-footprint]                                                   5 cases, 152 assertions PASS
Manifest parser accepts forward-compatible agent_sessions shapes  1 case,   18 assertions PASS
Manifest reader accepts schema 2 entries in full and skips newer   1 case,   27 assertions PASS
```

## Final-tree macOS verification — GREEN

The exact final uncommitted tree ran the canonical local selector:

```text
generated_envelope_reset          PASS    0.00s
biv_tests                         PASS  360.08s
errno_table_gate                  PASS    1.03s
generated_envelope_conforms       PASS    0.10s
harness-selftest                  PASS    4.86s
harness-e2                        PASS  233.73s
100% tests passed, 0 failed out of 6; total 599.82s
```

Before the Linux Werror correction added the semantically-empty field default, a separate
macOS Catch XML run measured `410 successes, 0 failures, 0 expectedFailures, 3 skips`.
Because that XML predates the final header byte, it is retained as diagnostic evidence and
is **not** used for count transcription. Its skips were exactly the two writable-`/mnt/c`
portability cases plus m-3's ruled threshold-parity identity. The six portability selectors
were all nonempty and their combined run passed 4,075 assertions across 81 cases, with only
the two expected `/mnt/c` cases skipped.

## Ubuntu 24.04 `linux/amd64` Docker verification — one hard finding

The local Docker substitution followed the repository instruction:

- image: `ubuntu:24.04`, exact pulled digest
  `sha256:561618e2c15bf2397621dd04f96926663a3b5616c189cf7e38db7e82f5c538ea`;
- platform: `--platform linux/amd64`; container `uname` reported `x86_64`;
- non-root test account: image-provided `ubuntu` UID 1000;
- Docker `--init` supplied the missing PID-1 reaper required by the process-group probes;
- writable `/mnt/c/tmp` provisioned;
- all eight pinned LLVM mirror package hashes, package names, exact version, and `amd64`
  architecture verified; `clang-tidy-22 --version` reported LLVM 22.1.8;
- CMake required-clang-tidy probe passed and resolved libstdc++ `_GLIBCXX_RELEASE=13`;
- complete Werror build passed after the new vector gained its explicit empty default;
- `safety-tidy-analyzer` executed as one JUnit row with status `run` and passed;
- hardening, Werror, harness E2, errno, probe-envelope, purity, mirror, and no-rewrite gates
  passed; configured ASan/UBSan and fuzz skip arms stayed configured skips.

The full target-local Catch XML on the exact final tree measured:

```text
successes=411 failures=1 expectedFailures=0 skips=1
```

The sole skip is the exact ruled m-3 identity. The sole failure is:

```text
version probe does not fall back to PATH when a pinned executable cannot spawn
expected: ProbeOutcome::spawn_error
observed under amd64 emulation: ProbeOutcome::nonzero_exit
```

This case does not intersect the seven-path delta. It is the same inherited emulated-probe
class already registered and exact-base-controlled in the prior successor report at
`.relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-SUCCESSOR-IMPLEMENTED-VERIFIED-STOP-BYTE-REVIEWS-20260816-163751.md`.
The current run independently narrowed the environment:

- without an init reaper, child/process-group probes also left zombies;
- with Docker `--init`, the complete `*version probe*` selection was 21 cases,
  20 passed and only this invalid-executable classification failed;
- excluding exactly this one inherited case, the product suite passed 411 cases plus the
  one configured-deferred skip, with all 14,551 assertions passing;
- every Slice E targeted selection passed under the same Linux build.

Docker Desktop amd64 emulation also exposes two incompatible filesystem properties: its
native Linux storage enforces chmod but coalesces same-tick metadata, while its precise
host bind observes same-tick mutations but does not enforce Linux chmod. No test byte was
patched and no failure was waived. The harness was therefore measured as two disjoint,
complete partitions:

```text
native permission surface: 967 passed, 3 configured skips, 4 clock-sensitive deselected
precise metadata surface:     4 passed (the four named clock-sensitive cases)
```

Those diagnostics complete the harness population but do not turn the canonical Catch
failure into a green head. The Linux XML remains red and governs this STOP.

## Why no product commit exists

The token's sequence is explicit: observe both targets on the line-carrying tree, transcribe
each target's own four counts, then commit once citing both run identifiers. It also says
failure and expected-failure counts are OBSERVE-AND-ROUTE and never edited. Therefore:

1. `failures=1` prevents a green Linux head;
2. Linux success/skip counts are not transcribed while that hard finding stands;
3. the earlier macOS XML is not borrowed across the final header byte;
4. no incoherent or partially-counted product state is committed.

`src/core/support/probe.cpp`, `tests/test_probe.cpp`, the harness, and Docker/CI policy are
all OUT. Changing any of them would be a new scope act and is not inferred.

## Requested disposition

Planner: choose and route one of these explicitly:

1. provide a canonical Ubuntu 24.04 native-amd64 runtime that preserves the workflow's
   invalid-executable semantics, then authorize resumption at step 3; or
2. obtain the required authority for a named inherited-emulation exception and specify how
   the four workflow counts are to be observed without laundering `failures=1`.

Remote GitHub Actions are not a fallback inferred by this report. The operator required
local Linux Docker substitution, and the repository instructions forbid remote CI unless
explicitly requested. No source fix is proposed for an OUT path.

ACTIONS_GIT_REF: implementation worktree remains at unchanged local unpublished HEAD `972919137203cb2ecb1d9f4bba8d8cd31e27befc` with exactly seven authorized tracked files modified and no staged product byte; this report and one live-EOF INDEX row ride one explicit-path coordination commit whose SHA lands after filing; no push, PR, Actions, merge, publication, deployment, or release
RELAY_LINT: exact report freshness-linted before INDEX append; live INDEX EOF re-read before one append; report re-linted with `--no-freshness`; INDEX standing historical cell-count and timestamp findings preserved and not rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree has exactly seven tracked unstaged authorized paths; coordination checkout contains foreign untracked relay history preserved and excluded; only this report and its one INDEX append are staged for this seat

CARRY LIST:
- Linux amd64 hard finding and runtime/exception disposition -> `s4-floor.planner` then UP through `s4.orchestrator-planner`
- seven-path coherent implementation delta -> HELD unstaged and uncommitted at `9729191`
- four workflow count lines -> UNTOUCHED until both target-local final-tree XML receipts are eligible
- m-3 ruled skip identity -> transcribed exactly and retained in the held workflow diff
- pair-Planner byte review, m-1 veto, and m-3 combined successor review -> not yet eligible because no product commit exists
- push, PR, GitHub Actions, merge, publication, deployment, and release -> not authorized; release hold remains absolute
