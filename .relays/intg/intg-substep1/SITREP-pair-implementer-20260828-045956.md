## SITREP — SUB-STEP 1 PRODUCT BYTES IMPLEMENTATION-COMPLETE AT 3cd31e4; FINAL REVIEW APPROVES THE FOUR-COMMIT SERIES; NOT VERIFICATION-COMPLETE OR MERGE-READY — TWO LOCKED PROOF COMMANDS ARE DEFECTIVE, LINUX HAS THREE UNCHANGED E3 ADVERSARY REDS, PINNED TIDY-22 AND THE POST-CTEST COUNT REMAIN UNPROVED

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep1-impl
PARENT_DISPATCH_ID: intg-substep1-impl
IN_REPLY_TO: intg-substep1/IMPL-pair-planner-20260828-023803.md
RELATED_CONTEXT: intg-substep1/PLAN-pair-planner-20260828-023657.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md; ../../../pdc/master/relays/intg-substep1-master-answers/PLAN-master-planner-20260828-022017.md; ../../../pdc/master/relays/intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this report requests planner/master adjudication of the proof-spec and Linux verification blockers; merge remains a separately addressed operator gate and the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 d286a0dff2b831091093056dbaa09810afce7171d441216f585a7621e2a8440b
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: SITREP — implementation-complete product bytes on intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b; independent final review APPROVES the code and scope; macOS applicable suite + required named-leg proof green; Linux build and ELF hardening green but full verification remains red/incomplete; no merge claim

## Disposition

**IMPLEMENTATION-COMPLETE FOR PRODUCT BYTES; NOT PLAN-ACCEPTANCE-COMPLETE, NOT VERIFICATION-COMPLETE, NOT LINUX-GREEN, AND NOT MERGE-READY.**

Independent final whole-branch review found no product/code severity finding. It approved the exact four-commit range and the hard scope fences, while retaining the proof-spec and Linux verification blockers below. This seat requests planner/master adjudication; it claims no waiver.

## Actions and exact series

`ACTIONS_GIT_REF` product candidate: `intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b`, exact base `02b51435a5b50363df7f595dd827af107424b0c3`.

```text
0734f031803c3dcb4c4b643e5f4257288ddb5ee9  Task 1 — CLI flag + help closure
11e3b3be2e3dfd9d0c6970704743813339b67da6  Task 2 — one-commit contract + carriers
4ce1a1f9c9bd4ee2723558368cb334e347ff7aa9  Task 3 — a6.15 real-verb zero state
3cd31e4823d40c1c9ea020fcb51917618368533b  Task 4 — PROMPT D renderer module
```

The base-to-head range is 18 planned paths, 551 insertions / 10 deletions. `git diff --check BASE..HEAD` is clean. `git diff --name-only BASE..HEAD -- src/core/repo` is empty. No product-to-engine call/include and no engine byte landed.

Task 2 remains ONE commit containing both ErrKinds, both exit-map rows, all three envelope-schema sites, carriers and serialization, the widened typed exit aggregator and its one caller, derived parity rows, and both recomputed pins. Linux GCC first exposed partial aggregate test initializers as `-Werror=missing-field-initializers`; the two fixtures were value-initialized and assigned the same fields, then the fix was folded into Task 2 before Tasks 3–4 were rebased. Fresh per-task reviews approved Tasks 1–4; the rewritten Task-2 reviewer independently built the repair under Ubuntu 24.04 amd64/GCC `-Werror`.

## TDD and focused evidence

- Task 1: missing `Command::accept_url_divergence` compile RED; declaration-only bridge; independent tagged parser/inert/no-help RED and help-golden RED; then GREEN.
- Task 2: missing contract/carrier compile RED; three missing schema-site REDs; then GREEN with 97 tagged assertions, 101 schema/exit parity assertions, and 6 Python envelope selftests.
- Task 3: the locked test-only a6.15 landing witness was allowed to pass first run because no production behavior followed from it.
- Task 4: six absent renderer/prompt symbols produced the expected link RED; then 127 tagged assertions across 12 cases passed.
- Final whole-branch reviewer: product/code APPROVED, exact scope and one-commit fence intact, no findings.

## macOS proof and assigned-leg census

Fresh final-head configuration used the pinned harness interpreter as the CMake cache variable; credential names were removed only from child test environments:

```text
cmake --preset ci-macos --fresh -DBIVHARNESS_PYTHON=/Users/jack/Programming/bivpak/.venv-harness/bin/python
cmake --build --preset ci-macos
env -u ANTHROPIC_API_KEY -u OPENAI_API_KEY ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure
```

Result: configure/build exit 0; CTest **18/18 applicable rows passed**, 0 failed, 791.70 s. `biv_tests` passed in 450.75 s; `harness-selftest` and `harness-e2` passed; three macOS allowlist safety rows skipped. The Linux-only ELF/readelf hardening row was excluded, not claimed as a macOS pass.

The exact final-head plan command

```text
env -u ANTHROPIC_API_KEY -u OPENAI_API_KEY ./build/ci-macos/biv_tests '[a6-fabric]' --success
```

exited 0 with **127 assertions / 12 test cases** and retained all twelve passing names:

1. `a6-R1 open carriers: exact rows, order, cardinality, grouped advisory, zero state`
2. `a6-R1 pack carries the grouped advisory too: exact entries, order, zero state`
3. `a6-R1 site 1: the preflight grain rides the top-level error carrier`
4. `a6-R1 exit composition: one typed aggregator over both sources`
5. `a6.15 zero state: no divergence -> both carriers absent on real verb envelopes`
6. `A6-R2 PROMPT D bytes are golden`
7. `A6-R4 accepted notice bytes are golden`
8. `A6-R4 refusal + guidance bytes are golden`
9. `A6-R2 default N: empty answer refuses; y proceeds; wrapper renders byte-whole to err`
10. `a6-R3 pack and open accept --accept-url-divergence`
11. `a6.14 list/info accept the flag inert: full-stream equality with flagless`
12. `a6.18 inherited no-help boundary witnessed on pack/list/info`

Leg census: a6.14 = 1 case / 14 assertions; a6.15 = 1 / 13; a6.17 = 3 exact Python structure nodes passed; a6.18 = 1 / 30 with pack/list/info names printed; a6.16 zero half = all 6 current envelope selftests passed. Direct `biv open --help` retains `--agent-bin` and places `--accept-url-divergence` directly after `--consent`.

STOP-1 bytes cite owner ruling `intg-stop1-a6-golden-bytes/DESIGN-planner-20260827-235912.md`, carried at master `000750`: prompt final byte is one trailing space/no newline; pack detail begins `pack refused:` with no indent. Final review rechecked the renderer bytes and exact stdin-TTY AND stderr-TTY predicate.

## Fence transcript — six hold; two literal proof commands are defective

```text
PASS  no run_eligibility|restore_entry|repo::capture outside src/core/repo
RED   raw include grep '#include "core/repo' prefix-matches four core/report includes
PASS  corrected '#include "core/repo/' has no match outside src/core/repo
PASS  require_empty_array manifest repos fence present at lines 117 and 971
PASS  no getenv|setenv|ofstream|fopen|config in url_consent.cpp
RED   raw grep -c isatty returns 1 because it counts matching lines
PASS  grep -o isatty | wc -l returns 2 tokens
PASS  fixed required conjunction is present byte-exact on that one line
PASS  no STDOUT_FILENO or json in url_consent.cpp
PASS  engine-path diff from BASE is empty
```

The two RED rows are literal plan-command defects, not product matches. They cannot both be made green while preserving the plan's mandatory one-line conjunction and existing `core/report` includes. Acceptance criterion 7 therefore remains literally unmet pending authorized successor/adjudication.

## Linux parity receipt — build/hardening green, suite red

One final disposable `ubuntu:24.04 --platform linux/amd64 --init` container used a read-only source mount and non-root uid 1001. Before the suite it witnessed:

```text
pid1=docker-init
nofile before: soft=1024 hard=1048576
nofile after:  soft=1048576 hard=1048576
```

GCC 13.3 configured and built all targets, including `tests/test_envelope.cpp`; the ELF `safety-hardening` row passed. Full CTest result: 18 passing/skipped rows accounted, but exit 8 because `harness-selftest` reported **996 passed, 3 failed, 3 skipped**. The three exact reds are unchanged mutation-during-read/enumeration adversary tests in `harness/selftest/test_e3_asserts.py`; that file and the credential/scanner surfaces are absent from `BASE..HEAD`, and macOS harness-selftest passed at the same SHA. This limits attribution only; it is not a waiver and the Linux suite remains red.

Ubuntu supplied clang-tidy 18 rather than the workflow's pinned tidy-22, so the tidy row skipped and is not claimed. Because the one container used `set -e`, CTest's red stopped the later tagged/XML count commands. The inherited R-4.38 `412/0/0/1` count gate remains unproved/known red. No Linux-green or canonical-parity claim is made.

## Explicit NOT-DONE

- No engine wiring, product-to-engine call/include, or engine hook installation.
- No FX-A6 a6.1–13, divergence half of a6.16, or any FX-A7 behavioral leg; those remain sub-step-2b-due.
- No format act or `repos`/N change; no list/info implementation; no prompt A/B/C, preview, PTY-helper, summary/warning-row, persistence, or additional argv surface.
- No remote CI, push, PR, merge, deployment, publication, seal, or release.
- No claim of plan-acceptance completion, all-fences green, Linux green, merge readiness, or any waiver.

## Escalation and requested next action

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — credential values were neither read nor changed
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed pdc contract plus published Bivpak schemas
- user-visible-control-with-materializer/downstream-consumer: yes — the consent renderer precedes held sub-step 2b wiring
- test-runtime-role-mismatch: yes — two locked proof commands are mechanically defective; canonical tidy/count proof is absent
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Linux E3 reds and R-4.38 remain unresolved
ESCALATION_SCAN_RESULT: trigger-present
OPERATOR_WAIVER: none requested, offered, or inferred
WAIVED_RISK_ACCEPTANCE: none

Requested planner/master action: accept the implementation-complete product-byte report only; issue an authorized proof-command correction/adjudication and route the unchanged Linux E3 reds plus pinned tidy-22/count gate to their owners. Do not advance this branch as verification-complete or merge-ready until those gates close.

ACTIONS_GIT_REF: product candidate `intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b` over exact base `02b51435a5b50363df7f595dd827af107424b0c3`; this report submits through the intg relay daemon; no push, PR, merge, remote CI, deployment, publication, seal, or release
RELAY_LINT: exact-file v2.9.2 lint is the submission gate; rendered result and digest are reported externally
FINAL_GIT_STATUS_SHORT: product worktree clean at filing; primary Bivpak root retains inherited S4 `.relays/s4` and sprint-doc noise outside intg scope, unchanged by this implementation; daemon-owned intg relay/INDEX/SEATS projection updates follow submission
