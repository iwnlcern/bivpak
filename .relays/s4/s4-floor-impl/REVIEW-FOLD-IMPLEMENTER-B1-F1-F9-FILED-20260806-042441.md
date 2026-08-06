## REVIEW-FOLD — B1 F1-F9 folded at ff63e52; targeted Planner re-check requested; stale CI count gates disclosed

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this filing — the pair Planner's targeted re-check is the next governed action; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-V2-SUPERSEDING-20260806-033306.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — B1 F1-F9 folded at PR #15 head ff63e52; A3 ceremony and durable receipts complete; only hard-OUT stale workflow count gates remain; targeted re-check requested before Slice A restack

FOLD_SCOPE:
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/codex.hpp -> in
- src/cli/main.cpp -> in
- src/core/pack/pack.hpp -> in
- src/core/pack/pack.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_envelope.cpp -> in
- tests/fixtures/codex_store/tail_matrix/** -> in
- harness/bivharness/e3.py -> in
- docs/sprints/2026-08-04-s4-step4/results/receipts/B1-A3-C1-five-owner-receipts.md -> in
- PR #15 body -> in
- .relays/s4/s4-floor-impl/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

DONE_WITH_CONCERNS

The complete F1-F9 fold is committed and pushed at
`ff63e52605c7ab2f8749808643a26c0c65bc33ba` on
`s4-floor/b1-codex-liveness`; draft PR #15 points to that exact head. The semantic
fold is `80d6f79b41ce51c509e3e1e46dba2ba40a4a1cc8`. Three later same-scope commits
close diagnostics exposed only by the current-head Linux CI toolchain:

- `b1c64df6c4b709bd1c8518bf95b3ff4d31b9aa0` defaults the optional warning facts;
- `9854dcac41c5ea793d95c41b10014fbcadbaab42` defaults the omittable warning path;
- `ff63e52605c7ab2f8749808643a26c0c65bc33ba` collapses identical formatter-call
  branches while retaining both m-3 consumer spelling markers.

None of those follow-ups changes `src/adapters/codex/codex.cpp`, so the last-step C1
anchor recapture remains valid at the final PR head.

## Required fold findings

- **F1 complete:** a terminal parent with an absorbed dangling live child emits one
  live parent session and a matching CLI warning; fixture IDs 1014/1015 discriminate
  the aggregation.
- **F2 complete:** production warning formatting sanitizes `kind`, `path`, and
  `artifact` control bytes below `0x20` plus `0x7f` as uppercase `\\xNN`. The E2
  witness creates a real ESC-bearing FIFO filename and observes the sanitized CLI
  output.
- **F3 complete:** the terminal negative control now has a positive JSON witness in
  `manifest.agent_sessions`, proving Codex collection rather than only warning
  absence.
- **F4 complete:** zero-byte and lone-LF fixtures both pass through production
  `collect()` and yield no sessions, with direct polarity coverage of the public
  predicate.
- **F5 SATISFIED-BY-DISSOLUTION:** `has_terminal_tail_record` is one ordinary public
  production predicate used by collection and tests. The duplicated
  `codex_testing` wrapper is deleted; no CMake seam was added.
- **F6 complete:** the five-owner ceremony is durable at
  `docs/sprints/2026-08-04-s4-step4/results/receipts/B1-A3-C1-five-owner-receipts.md`.
- **F7 complete:** `src/cli/main.cpp` retains both exact m-3 consumer spelling
  markers while emitting all warnings through the one production formatter.
- **F8 complete:** envelope coverage uses `TornTailDropped` with path = session id
  and artifact = member path.
- **F9 complete:** production formatter shapes are direct-tested for live,
  torn-tail, generic-with-path, and generic-without-path output.

O1-O5/O7/O8 are accepted and folded. O6 remains deferred because extending the
locked generic kind+path line with optional artifact/bytes would change that
contract.

## A3 per-head C1 evidence

1. The fold changes Codex source and exactly one anchor-side literal:
   `codex_adapter_file`. The Claude anchor, envelope blob lock, and exit-map lock do
   not move.
2. `shasum -a 256 src/adapters/codex/codex.cpp` returns
   `6f8ec5721e7aed0950d6d2a16bc2463cf5f5085412594fafc338ea8ae1f318cf`, exactly
   matching the committed C1 literal at `ff63e52`.
3. The five executable owner cases pass together and the pinned-source control
   passes. Each disposable mutation of inventory glob, primary store, archived
   store, novel StoreLocator/Store insertion, and post-initializer ArtifactClass
   insertion produced the exact C1 RED:
   `C1 drift tripwire RED: adapter session-location source changed (codex_adapter_file)`.
   Each mutation was reverted to the exact folded hash before the next arm.
4. Re-running the class-scoped `fabc079..ff63e52` diff search emits no owner-class
   matches: the product diff touches none of inventory glob, primary-store
   discovery, archived-store discovery, novel StoreLocator/Store insertion, or
   post-initializer ArtifactClass insertion.

The five-arm ceremony remains materially burdensome and is reported rather than
silently absorbed, preserving the upstream R-3.40 item (11) trigger.

## Verification and CI disposition

- focused folded surfaces: 145 assertions in 7 test cases passed;
- C1 five-owner enumeration: 5 passed; pinned-source control: 1 passed;
- full harness selftests: 955 passed in 8.23 seconds;
- `cmake --build --preset dev -j 4`: passed;
- dedicated `harness-e2`: passed in 153.03 seconds;
- full local CTest: product, harness, E2, Werror, and every runnable gate passed;
  the sole local red was Linux/ELF-only `safety-hardening` on Darwin Mach-O because
  `readelf` is unavailable/inapplicable. It is not waived; both Linux CI runs pass
  that hardening row;
- GCC 15 full `biv_tests` target: passed after the warning defaults; focused generic
  formatter case: 4 assertions in 1 test case passed;
- both current-head Linux CI triggers build and pass full CTest, including pinned
  `safety-tidy-analyzer` and `safety-hardening`, then fail only the hard-coded
  Catch2 count assertion: expected 223 successes, observed 232 successes, with 0
  failures, 0 expected failures, and 0 skips;
- both current-head macOS CI triggers build and pass the product suite, then fail
  only the hard-coded count assertion: expected 221 successes, observed 230
  successes, with 0 failures, 0 expected failures, and 2 expected skips;
- harness-selftest and safety-fuzz-smoke pass independently on both current-head
  triggers.

The Linux and macOS count differences are exactly the nine added B1 test cases.
The correction lives under `.github/**`, which is hard OUT for this fold. Those
workflow assertions are therefore disclosed as concerns, not edited or waived.

## FOLD_SCOPE v1 process scar and supersession

V1 `REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-20260806-030052.md` incorrectly claimed
complete scope while omitting the already-authorized `harness/bivharness/e3.py`
recapture path. I self-caught the omission at the C1 gate before editing that path,
filed the blocker, and stopped. Pair Planner disposed it as supersede-and-proceed
without replay because every edit already performed had been covered before edit.
V2 `REVIEW-FOLD-SCOPE-IMPLEMENTER-B1-F1-F9-V2-SUPERSEDING-20260806-033306.md`
listed the complete scope before the one-literal anchor recapture. V1, the
self-catch/blocker, the Planner disposition, and V2 all remain append-only; this
report does not smooth over the scar.

## Requested next action and holds

Planner targeted re-check is requested at exact PR head
`ff63e52605c7ab2f8749808643a26c0c65bc33ba` for the F1 fixture, F2 control-byte
witness, F3 JSON witness, promoted-predicate relink/F5 dissolution, and the
post-fold panel-at-SHA record. Slice A is not restacked until that re-check and a
subsequent addressed re-dispatch. No merge or release action is taken or authorized.

ACTIONS_GIT_REF: B1 fold `80d6f79b41ce51c509e3e1e46dba2ba40a4a1cc8` plus current-head diagnostic closures `b1c64df6c4b709bd1c8518bf95b3ff4d31b9aa0`, `9854dcac41c5ea793d95c41b10014fbcadbaab42`, and `ff63e52605c7ab2f8749808643a26c0c65bc33ba`; PR #15 updated at exact head ff63e52; docs receipts committed at dd62e97; this relay and append-only INDEX row are committed on the docs lane after author-side lint, with SHA in the commit record
FINAL_GIT_STATUS_SHORT: B1 worktree clean at ff63e52 and equal to origin/s4-floor/b1-codex-liveness; docs lane clean at dd62e97 before this relay and INDEX append

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-B1-F1-F9-FILED-20260806-042441.md` → `s4-floor.planner`
- `https://github.com/iwnlcern/bivpak/pull/15` at `ff63e52605c7ab2f8749808643a26c0c65bc33ba` → targeted re-check only; merge/release held
