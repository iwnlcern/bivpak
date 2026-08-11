## REVIEW-FOLD — corrected CB2 Option A Branch B complete and published at exact B2 `3762f37`; Claude child mappings now tell the truth

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-option-a-branch-b-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-option-a-branch-b
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the combined planner re-check, fresh paired hand-up, condition-3, and operator paired condition-4 remain downstream; the release hold remains ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-OPTION-A-BRANCH-B-CORRECTED-DISPATCH-IMPL-TOKEN-20260810-220856.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-GUARDED-PUBLICATION-DISPATCH-IMPL-TOKEN-20260810-154400.md; docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-e0d6c19.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: DONE_WITH_CONCERNS — corrected Branch B is complete at `3762f37`, host suite green, bounded Ubuntu amd64 parity green with registered exceptions disclosed, independent review CLEAR, and only draft PR #23 was guarded-published

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

The corrected Claude-only Branch B fold is implemented, reviewed, verified, and
published to the existing draft PR #23 branch. The concern is confined to the
repository's already-registered Docker/Rosetta exceptions and its stale exact-count
workflow assertion; neither is caused by this five-file fold. No GitHub Actions run or
check was invoked or inspected.

## Final topology and scope

- Exact B2: `3762f3722a1fcebfbaa25921c31ca2f10df4ddf4`.
- Exact parent C: `b8083be8529a97d1d3d5931a2c7b308335bbd09c`.
- B2 remains exactly one commit directly atop C, with preserved subject
  `feat(pack): collect torn tails and staged sidecars`.
- The cumulative C-to-B2 range remains exactly 17 tracked paths.
- The option-(a) end-state delta from `e0d6c19` is exactly the five paths declared
  before the first edit; 353 insertions and 468 deletions.
- The implementation worktree is clean and `git diff --check` passes.

FOLD_SCOPE:
- src/adapters/claude_code/install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
FOLD_SCOPE_RESULT: all-in

The conditional `harness/bivharness/e3.py` arm was not triggered because collector
production did not change. Codex, `rewrite_common.cpp/.hpp`, both collector production
surfaces, the harness, and `.github/**` are byte-identical to `e0d6c19`.

## Corrected Branch B result

- Claude `child_ids` now stores `{original_id, original_id}`. The sealed A9 member shape
  remains the same pair-list; only its values become identity. A consumer now learns
  truthfully that no child artifact was renamed. Whether `children` should continue to
  be emitted remains the install-result-shape owner's contract question, not changed
  here.
- `child_alias_ids`, recursive `agentId` harvesting/needling, and the now-dead
  `child_identity_shape` guard were removed. No `.pending-r415` marker remains.
- Installed-session IDs still mint UUIDs and still name the installed main filename and
  parent directory. Message UUIDs still mint and rewrite.
- Codex remains intentionally asymmetric and unchanged: its minted child ID names the
  child rollout artifact written by `codex/install.cpp`.
- Shared boundary-aware rewriting and strict substring verification remain byte-identical.
  L-3 therefore still governs the session/message/declared-ID pair surface. The former
  one-character Claude-only alias-shape scanner has no surviving input and was removed
  as dead code rather than kept by inventing a new input.
- The L-2 collision test now records the surviving shared rule accurately: when one
  session's identity child equals another session's primary origin, identity mapping
  itself does not alias-mint or cross-needle, while the shared strict verifier still
  refuses the owner whose exact session-origin bytes survive.
- Fixture shapes are flat bare-hex, flat slug-hex, and nested bare-hex under
  `subagents/<wf>/`, matching the discharged corpus basis: 578 flat plus 1,124 nested,
  1,702 total, with bare-hex at 83%.
- The standing stage -> pack -> open table proves all three shapes/layouts. Restored
  parent `senderTaskId`/`agentId` equals the actual restored `subagents/` filename stem;
  both staged and final Claude child maps are identity.
- The sessions consumer proof confirms `staged_path_caveats` can now find the real
  Claude child path through `child.second`.

Hard OUT remains untouched: slice E/X-1 and three-level pairing, R-4.18 widening,
WSL/A11, R-4.16, sealed A9 member shape, `.github/**`, merge, tag, deploy, seal, and
release.

## TDD and focused receipts

- Test-only RED at the old `e0d6c19` behavior: 14 cases, 852 assertions; 11 cases and
  43 assertions failed, exposing minted child-map values, rewritten `agentId` values,
  alias-union refusal, and unresolved filename references.
- First implementation GREEN exposed one real integration issue: identity-valued child
  IDs remained in the image-origin verification set and therefore self-refused. The
  production fix removed only those out-of-invariant identity values from that set;
  session and message origins remain verified.
- Final named cohort at exact `3762f37`: 15 cases, 875 assertions, PASS.
- Wider `*Claude*` cohort at exact final bytes: 89 cases, 2,841 assertions, PASS.
- Independent read-only final review: CLEAR — no Critical, Important, or Minor findings;
  its focused verification passed 4 cases and 612 assertions.

## Final host verification

At exact `3762f37` on macOS, the fresh canonical host selection
`ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure` passed 14/14 in
555.25 seconds. That includes:

- `biv_tests`: PASS in 337.24 seconds;
- open-no-rewrite, adapter purity, version mirror, errno, probe schema, generated
  envelope, and harness selftest: PASS;
- harness E2: PASS in 188.69 seconds;
- Werror: PASS in 22.97 seconds.

ASan/UBSan, tidy/analyzer, and fuzz smoke remained preset-configured macOS skips.
Safety hardening was excluded from this host selection and was exercised on Linux.

## Final Ubuntu 24.04 linux/amd64 Docker parity

A fresh disposable archive of exact `3762f37` ran under `ubuntu:24.04` with
`--platform linux/amd64`. The image reported Ubuntu 24.04.4 x86_64; all eight workflow
LLVM 22.1.8 amd64 packages matched their pinned SHA-256 values; CMake selected
`/usr/bin/clang-tidy-22`; and the hardened build passed. `libsqlite3-dev` was added as
environment provisioning after the first configure exposed its absence; no product
result preceded the corrected configure.

The first root-user CTest invocation was diagnostic and noncanonical because permission
tests cannot exercise their refusal under uid 0. The canonical rerun used the image's
non-root `ubuntu` user:

- product: 369/370 cases and 10,553/10,554 assertions passed; sole failure was the
  registered Docker/Rosetta invalid-executable spawn-semantics case;
- harness selftest: 968 passed, three failed, three skipped; the three failures were
  registered overlay mutation sentinels. The fourth registered sentinel did not fail in
  this run;
- harness E2: PASS in 1.10 seconds;
- Werror: PASS in 1.55 seconds;
- LLVM tidy: PASS in 45.36 seconds; its JUnit contained exactly one executed row and no
  skipped or failed child;
- hardening: PASS in 0.14 seconds;
- ASan/UBSan and fuzz smoke: configured skips;
- canonical CTest duration: 73.15 seconds, exit 8 solely from the registered exceptions.

Bounded controls passed: product excluding exactly the registered Rosetta case was
369/369; harness excluding exactly the four registered Docker mutation sentinels was
967 passed, three skipped, four deselected; direct generated-envelope schema validation
passed. The workflow Catch XML measured 369 successes and one failure, while its stale
exact-count assertion still expects 223/0/0/0. `.github/**` is Hard OUT, so that count
gate is reported as `STALE_FAIL` and was not edited.

The disposable container `bivpak-cb2-option-a-3762f37` and its task-only LLVM download
directory were removed. No unrelated Docker resource was pruned or removed.

## Combined re-check: per-file end-state bytes

The required combined scope is the full 17-path cumulative C-to-B2 union. Twelve files
hash-match the planner's `e0d6c19` baseline and mechanically carry; the five marked
FRESH differ and require review at exact `3762f37`.

| disposition | sha256 at `3762f37` | path |
|---|---|---|
| CARRY | `21d348285d54d2d1cb1f17b8d9d9f388816de719258f5eac0d4fa5475ff49505` | `harness/CMakeLists.txt` |
| CARRY | `2fb295a67ab2dd95388579e05513b1901b5db528e73faa4ad6e2ba097d3df6ec` | `harness/bivharness/e3.py` |
| CARRY | `1c96d3ac7b86b7836296475b2da3d6fd07b1806a70268a5a9981f237b713fcb4` | `src/adapters/adapter.hpp` |
| CARRY | `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` | `src/adapters/claude_code/claude_code.cpp` |
| FRESH | `5802406ee272ed496d005a8c8010fe08e21d336dd2e5e562c5177aedf27a2c11` | `src/adapters/claude_code/install.cpp` |
| CARRY | `2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d` | `src/adapters/codex/codex.cpp` |
| CARRY | `5e829ff7b391f8a06ff637f902a4a33cb1b7b56db3a363b31f12be7ba4b783b7` | `src/adapters/codex/install.cpp` |
| CARRY | `cfcd49111ff9a4c9deabcd249d10ed9996d7c4adf597c86fb864309a41f60c96` | `src/adapters/rewrite_common.cpp` |
| CARRY | `4a0e77b7d7331f7419e87cf7746ce31428d17af3e1351500139a4d93a7ab48f3` | `src/adapters/rewrite_common.hpp` |
| CARRY | `0f5cabfd755eea473e76c047c4ad47d1b0f7127de1da3f95d550731b85a1ea33` | `src/core/pack/pack.cpp` |
| FRESH | `2131cc80a628d8a2a6de67a8e10c29ba00389a08b42c32daa4bfa1eb473b3a64` | `tests/test_adapter_claude_collect.cpp` |
| FRESH | `152b82df86da61e55c7410f94d55251c0080e60deb4025a9869c9b7fd8b45b2a` | `tests/test_adapter_claude_install.cpp` |
| CARRY | `6b52a282387d12eff55d5718767d176e7c45b923faed4455f92609eff08b4d6e` | `tests/test_adapter_codex_collect.cpp` |
| CARRY | `35506db97b7af78b49b770301a3f027dc40a5a7b5463e15fad1dc3b01e1bd0f5` | `tests/test_adapter_codex_install.cpp` |
| CARRY | `1c74fd06693577039d91d87c4a69dc42386888baa27ae3288dc7bb573453f8ae` | `tests/test_cli.cpp` |
| FRESH | `38d790c1b185e7757d03d1b17e13592cebf46065b7c9ed84218d12a16c8b57ff` | `tests/test_pack.cpp` |
| FRESH | `cbb4cdf17775fe8c51687d2a5c8efb26f0d51fdc8d523db21c930cb9c58e0883` | `tests/test_sessions.cpp` |

The re-measured D-5.5(a) cut-point blast radius is **27** using
`git rev-list --count origin/main..HEAD^` at current remote target
`origin/main = 38a4702bdc6c0fe82a102ebf58977ca7ad67623a`. This is informational,
not a merge grant.

## Guarded draft publication

Preflight verified remote B2 at exact
`e0d6c1994e286291cc7ab3439228edbb65f048a4`, remote C at exact
`b8083be8529a97d1d3d5931a2c7b308335bbd09c`, PR #23 OPEN/DRAFT/base `main`,
and PR #22 OPEN/DRAFT/base `main`.

Under the carried `154400` terms, the only remote mutation was:

`git push --force-with-lease=s4-floor/b2-torn-tail:e0d6c1994e286291cc7ab3439228edbb65f048a4 origin 3762f3722a1fcebfbaa25921c31ca2f10df4ddf4:s4-floor/b2-torn-tail`

Postflight verified remote B2 and PR #23 at exact `3762f37`; PR #23 remains OPEN,
DRAFT, and based on `main`. Remote C and PR #22 remain byte-identical at exact
`b8083be`, OPEN, DRAFT, and based on `main`. No PR body or draft-state mutation,
GitHub Actions invocation/inspection, merge, tag, deploy, seal, or release occurred.

Requested next action: convene the combined re-check over all 17 per-file end-state
hashes above, reviewing the five FRESH files and carrying only the twelve exact matches;
include the standing round-trip result. On PASS, issue the fresh paired hand-up with
A10.3 and the measured blast-radius line.

C must never land without B2 (A10.3). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: local and remote B2 `3762f3722a1fcebfbaa25921c31ca2f10df4ddf4` atop exact C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`; guarded force-with-lease updated only `origin/s4-floor/b2-torn-tail`; this report and its append-only INDEX row are the only docs-lane writes from this filing
FINAL_GIT_STATUS_SHORT: product worktree clean; shared docs checkout retains unrelated pre-existing untracked relay files, preserved; this filing adds only the named report and its INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-OPTION-A-BRANCH-B-COMPLETE-PUBLISHED-20260810-230434.md` -> `s4-floor.planner`
- exact B2 `3762f37` / draft PR #23 -> combined 17-file re-check using the per-file hashes above; five FRESH, twelve CARRY
- independent review CLEAR; standing round-trip and staged caveat proofs green; host 14/14; bounded local Linux parity green with registered exceptions and stale count gate disclosed
- A10.3: C never lands without B2; no merge/seal/release; release hold ABSOLUTE
