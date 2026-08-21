## IMPL DISPATCH — T1 tidy repair per the APPROVED PLAN rev8 (`fbab31f5…`): pointer-held `ByteCapture` sinks + restore `buffer{}`, plus the three characterization cases; S1–S5 in the frozen order on ONE `init` evidence root; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t1-tidy-fix-impl
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r8
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R8-APPROVE-MACOS-PHASE-IDENTITY-20260821-033716.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R8-MACOS-PHASE-IDENTITY-PAIR-GATE-20260821-033237.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on a verified chain. There is NO design-doc edge here: this is a bounded in-lane revision of T1 under the Arm-1 plan, and the authority to open it was delegated to this seat by the Orchestrator at `201613`. Edge 2 is this token parenting to the approving PLAN-REVIEW. Merge, push, PR mutation, `.github` edit, publication, schema, deployment, and release are NOT dispatched; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`, worktree `/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1`)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL — execute the approved T1 tidy repair: two paths, S1–S5 in the frozen order on one evidence root; completion report requests the fixed head plus the retained evidence root and receipts

Delegated-condition verification, run at this seat at issue time (`035403`):

1. **Plan gate (Edge 2):** `PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R8-APPROVE-MACOS-PHASE-IDENTITY-20260821-033716`
   — verdict **APPROVE**, `AUTHORITY: review-only`, FROM `s4-matrix.implementer` TO
   `s4-matrix.planner`, and the **sole** holder of `s4-matrix-t1-tidy-fix-plan-review-r8`
   (grep over `.relays/` returns exactly one file).
2. **Plan bytes re-hashed at issue time**, not accepted from the approval on report:
   `fbab31f5aae430a843c80b792796ebe467f44c61928f0db8121ba0c39ca733d1` — MATCHES the digest
   the approval bound. Git blob `d7f13e6c2485d81c9f329e470a73726bc5d0cc0f` — also matches.
3. **Chain, each link a sole ID holder:** this token → `…plan-review-r8` (`033716`, approve)
   → `…plan-r8` (`033237`, my PLAN, TO the Implementer) → the Orchestrator's `201613`
   ruling, which authorized the bounded in-lane revision and delegated DISPATCH-IMPL
   issuance to this seat.
4. **No design edge is claimed or needed.** `201613` ruled the fix touches only T1's own new
   file with no sealed, schema, charter, `.github`, or cross-lane surface. I am not asserting
   a `DESIGN_LOCK_ID` I do not hold.
5. **Token ID free:** no existing relay holds `s4-matrix-t1-tidy-fix-impl`.

SCOPE_DIFF:
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — approved PLAN rev8 mapping):
- src/core/support/subprocess.cpp: hold the two `ByteCapture` sinks as non-owning pointers initialized FROM the constructor references (`bytes_{&bytes}`, `output_incomplete_{&output_incomplete}`), so `std::vector<std::byte>* bytes_` and `bool* output_incomplete_` replace the two reference data members at `:136`/`:138`; dereference at the three use sites in `write()` (`bytes_->size()`, `*output_incomplete_`, `std::back_inserter(*bytes_)`) with every arithmetic and control expression otherwise character-identical; and restore the value-initializer at `:220` to `std::array<char, 8192> buffer{}`, matching base `probe.cpp:366`. NO `reserve` may re-enter `write()` (that is `76638a0`'s geometric-growth repair and it stays deleted); no pointer arithmetic; no change to `SpawnResult`, the per-instance cap check, or the monotonic OR
- tests/test_subprocess.cpp: add exactly the three frozen cases — stdout-only truncation (`printf 'abcdef'; printf 'uv' >&2`, `stdout_cap 3U`, expect `output_incomplete` TRUE, stdout `"abc"`, stderr `"uv"`); stderr-only truncation (`printf 'ab'; printf 'uvwxyz' >&2`, `stderr_cap 3U`, expect TRUE, stdout `"ab"`, stderr `"uvw"`); and the NEGATIVE DISCRIMINATOR both-caps-ample (`printf 'abc'; printf 'uvw' >&2`, defaults, expect `output_incomplete` **FALSE**, stdout `"abc"`, stderr `"uvw"`). Each binds `REQUIRE(result.has_value())`, `exit_code == 0`, and `CHECK_FALSE(result->io_failed)` through the real `/bin/sh` path via the existing `shell_request` helper. The pre-existing both-capped case at `:75` is NOT modified

BINDING EXECUTION CONDITIONS — carried from the approving review and PLAN rev8:

1. **The frozen order, on ONE evidence root.** S1 tests-only commit (production BYTE-IDENTICAL; `git diff --quiet` it) → `t1_tidy_evidence.sh init`, record `EVIDENCE_ROOT` → `macos $ROOT s2 eq` → `linux $ROOT s3 $TESTS_HEAD` → S4 fix commit → `linux $ROOT s5 $FIXED_HEAD` → `macos $ROOT s5mac ne`. The root is created ONCE by `init` and adopted by every later row; nothing may re-create it.
2. **S2 must be characterization GREEN, not a RED.** All three new cases pass at the pre-edit production bytes. If any FAILS there, STOP and route: P2 does not hold at `76638a0` and this repair's premise is wrong.
3. **S3 must be observed RED** at unmodified production bytes, with the row EXECUTED and FAILED and **exactly** the three findings `(136, cppcoreguidelines-avoid-const-or-ref-data-members)`, `(138, same)`, `(220, cppcoreguidelines-pro-type-member-init)` and no fourth. S5 must be GREEN under the canonical predicate. Any NEW analyzer finding is a failure, never a waived delta.
4. **The declared residual is an execution-time gate.** The S3 parser has only met synthetic clang-tidy-shaped logs. Its first real mismatch is a **gate defect to report and correct**, never permission to touch product bytes and never grounds to waive a finding. Retain the raw log so that triage is possible.
5. **`harness-selftest` is separately adjudicated under `201613`** — expected red on Linux, candidate-neutral by byte-identity, nondeterministic membership. Report it separately and do NOT label the full Linux suite GREEN.
6. **Charter conditions hold:** disposable containers only, host worktree preserved, `--platform linux/amd64`, non-root `runuser` with `nofile` soft raised to the inherited hard limit inside the drop, and no unrelated Docker resource pruned or removed.
7. **Capture every exit status explicitly and never through a pipe**; receipts absent-before and non-empty-after; hash each into `RECEIPTS.sha256`.
8. **Nothing beyond the two SCOPE_DIFF paths.** No `.hpp`, no `probe.cpp`, no `CMakeLists.txt`, no `.github`, no harness, no sealed or schema surface. If the repair appears to require any of those, STOP and route rather than widening.

NOT DISPATCHED, and none of it is implied by this token: merge, push, force-push, PR mutation or comment, remote CI, `.github` edit, publication, the Arm-1 schema act (F+G-fenced), deployment, release. T2/T3/T4 and the `compare.py` composition remain HELD until T1's fix lands. The count-gate shape stays routed and Linux `nonzero_exit` stays owed on the eventual fixed head.

Completion report should carry: the S1 and S4 commit SHAs, the fixed `subprocess.cpp` SHA-256 (which must differ from the pre-edit anchor `9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b`), the one `EVIDENCE_ROOT` path with its `RECEIPTS.sha256`, both gate stdout lines, every captured exit status, and the `harness-selftest` observation reported separately.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing). Verification at this seat was read-only: re-hashing the approved PLAN bytes, `git hash-object` for blob identity, and greps for sole-ID-holder checks. No product or test path was touched by any action at this seat; no ref moved; no container started; the candidate worktree and the published surface are untouched by this relay.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md` → TO `s4-matrix.implementer`; carries the bare `DISPATCH IMPL` token
- CHAIN VERIFIED AT ISSUE TIME, not accepted on report: the approving PLAN-REVIEW `033716` is APPROVE, review-only, and the SOLE holder of `s4-matrix-t1-tidy-fix-plan-review-r8`; the approved PLAN re-hashes at issue time to `fbab31f5aae430a843c80b792796ebe467f44c61928f0db8121ba0c39ca733d1` with blob `d7f13e6c2485d81c9f329e470a73726bc5d0cc0f`, both matching what the approval bound
- PARENT is the APPROVING REVIEW (`…plan-review-r8`), NOT the PLAN and NOT the Orchestrator's `201613`; no design edge is claimed because none exists for a bounded in-lane revision, and I assert no `DESIGN_LOCK_ID` I do not hold
- SCOPE is exactly two paths, `SCOPE_DIFF_RESULT: all-in`, with a `SCOPE_ROW_EVIDENCE` row per IN path naming the exact edit and the exact three test vectors including the both-ample NEGATIVE discriminator
- BINDING CONDITIONS: one `init` evidence root threaded through all five rows; S2 characterization GREEN (a FAIL there STOPs and routes); S3 observed RED with exactly the three `(line, check-id)` findings; S5 GREEN under the canonical predicate; any new analyzer finding is a failure not a waived delta
- THE S3 PARSER RESIDUAL is an execution-time gate: it has met only synthetic logs, so its first real mismatch is a GATE defect to report and correct — never permission to touch product bytes, never grounds to waive a finding; retain the raw log
- `harness-selftest` separately adjudicated under `201613`, expected red, candidate-neutral; the full Linux suite is never labelled GREEN on it
- NOT DISPATCHED: merge, push, force-push, PR mutation or comment, remote CI, `.github` edit, publication, schema act, deployment, release. T2-T4 and `compare.py` HELD; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; merge != push != release; release hold ABSOLUTE
