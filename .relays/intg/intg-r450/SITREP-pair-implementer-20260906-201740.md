## SITREP — R-4.50 revision-5 Task 1 STOP: targeted RED/GREEN is correct, but the first workflow-equivalent macOS suite fails harness-selftest after the fenced discover change

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r450-discover-parity-impl-stop-2
PARENT_DISPATCH_ID: intg-r450-discover-parity-impl-2
IN_REPLY_TO: intg-r450/IMPL-pair-planner-20260906-194721.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260906-192951.md; intg-r450/PLAN-pair-planner-20260906-192052.md; intg-r450/SITREP-pair-implementer-20260906-175211.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner must adjudicate this exact plan-mandated STOP and route any successor; changing the excluded set, accepting harness-selftest red, or touching harness bytes is not authorized locally
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 d9230c6e9383f62e5f946de62634d0f42bc085c7a5cd4095fe2a46819812538e
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b, re-fetched and recorded before implementation
BRANCH: intg/r450-discover-parity at bbf297e36a38a1fab8c2675f945098a0633f9f8b in /Users/jack/Programming/bivpak-intg-r450-discover-parity; exactly two in-scope unstaged paths; no P exists
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP at Task 1 Step 5 — the named witness proves the intended red then green, but the first full macOS acceptance run returns rc 8 because harness-selftest has 53 failures after the sealed discover change; no retry, P, Linux run, or transcription

## Current artifact

Evidence home: `/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T//r450-evidence-16Y21z`.

Incoming implementation relay SHA-256: `476b9e5bef9c2580196764fd4759c45b0e2c662097f910bc8540118558d51b1b`. Approved plan SHA-256: `d9230c6e9383f62e5f946de62634d0f42bc085c7a5cd4095fe2a46819812538e`.

## Gates reached

Task 0 reached every revision-5 gate:

- The one-ref fetch returned zero and `origin/main` remained the published B. Product bytes at B equal lane-local `main`; the retained linked worktree was clean on the required branch and had zero unpublished commits.
- All six exact plan helpers compiled. Both trailing-slash ignore probes returned zero before the worktree status gate.
- A fresh Python 3.12.12 venv imported `pytest`, `jsonschema`, and `zstandard`; the fresh CMake cache selected exactly one `.venv-harness/bin/python3`; configure, build, and the unchanged discover case returned zero.
- The first and only Task 0 discriminator execution returned `rc1=8 rc2=0 present_count=1 iff=pass hygiene=pass`; only credential names and presence were recorded.
- The command wrapper refused the literal recursive deletion syntax before execution. The exact ignored pre-existing `build/ci-macos` directory was instead moved intact into the external evidence home, then source absence and retained backup were both proved before the fresh configure. No user data was deleted.

Task 1 then followed RED/GREEN:

- The initial RED XML exposed a plan-local parser/section-label mismatch: the helper splits at the first colon, while the prescribed ROW 5 label placed its parenthetical before the colon, producing parser rc 4 despite the XML containing all five leaves. Per Task 1 Step 3's explicit fixture/model repair path, the test-only label was minimally changed to start `ROW 5:`; the first XML and rc files remain retained.
- The required RED rerun built with rc 0; the named test returned rc 42; `witness.py red` returned zero and proved exactly ROW 1 and ROW 5 red with ROWS 2–4 green. RED XML SHA-256: `11ae796125959b27ae19863bb100ed6084f6c43034f8dce4531b843c7b2a138a`.
- After the exact discover-body replacement, build rc, the named GREEN case rc, `witness.py green` rc, and the unchanged legacy discover case rc were all zero. GREEN XML SHA-256: `a8871e65f7d6187a38f7f10bfd8340b508af34af7a4393379add84ee169c3bee`.

## Plan-mandated STOP

The first Task 1 Step 5 workflow-equivalent run was:

```text
env -u <three derived credential names> ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure
ctest_macos_P_rc=8
94% tests passed, 1 tests failed out of 18
13 - harness-selftest (Failed)
Total Test time (real) = 614.55 sec
```

Inside `harness-selftest`, pytest reports `53 failed, 961 passed`. The failures are not the new Catch2 witness: they are the existing E3/harness assertion and drift-tripwire surface, including `test_drift_tripwire_is_green_at_pinned_source`, every named read-side drift mutant including `claude-discover-primary`, multiple open/result validation cases, argv-barrier/finalization cases, and the A4 collector registry check. The full CTest log SHA-256 is `9ae1b6ab14ec417403cd29eea2d58ca6a4bdf66e413e6e8616245607094a465b`.

The approved plan says any red here is a FINDING routed UP, never another unset, exclusion, or retry. It simultaneously declares harness/stub/witness bytes out of scope. Therefore this seat cannot decide whether the plan must add an owner-authorized harness update, change the acceptance-run topology, or carry another ruled response. Execution stopped before the provisional commit.

ROW_TRUTH_CHECK: required
SCOPE_DIFF:
- src/adapters/claude_code/claude_code.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
SCOPE_DIFF_RESULT: all-in
SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/claude_code.cpp: exact sealed discover body only; unstaged; numstat 12 additions and 13 deletions
- tests/test_adapter_claude_collect.cpp: test-local helpers plus one named TEST_CASE; unstaged; numstat 183 additions and 0 deletions; the one-character label placement repair is within the plan-authorized fixture/model correction

BOUNDARY_CONTRACT:
- Writes: exactly two authorized product/test paths are dirty; ignored venv/build outputs and external evidence exist; this report relay and its INDEX projection are the only main-checkout writes
- Reads: approved plan, published B, exact m-2 discover fence/reference shape, existing harness and retained run logs
- Target entity: Claude discovery now has the candidate env-plus-default behavior in unstaged bytes; no candidate commit exists
- Downstream consumer: pair Planner must adjudicate the harness-selftest conflict before any P, Linux observation, count transcription, owner review, or vehicle action
- Contract: preserve the two current in-scope edits and evidence without retry; any successor must explicitly resolve the full-suite/harness boundary while retaining the sealed product behavior and all downstream gates
- Proof: E2 target RED/GREEN and legacy-case green, followed by the first exact workflow-equivalent macOS suite rc 8 with 53 harness-selftest failures
- No-consumer action: STOP UP; do not commit P, run Linux, transcribe workflow cells, amend C, push, open a PR, merge, land, publish, deploy, or release

ACTIONS_GIT_REF: fetched only the literal main ref; verified and reused linked worktree `intg/r450-discover-parity` at B; created ignored Python/build environment; changed exactly the two IN paths above; no staging, commit, tag, remote branch, push, PR, merge, publication, deployment, release, or closure. Evidence is retained at `/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T//r450-evidence-16Y21z`.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — observer names and presence only were read; credential values were never read or printed
- migration/backfill/destructive-write/canonical-data-repair: no — an ignored prior build directory was moved recoverably to external evidence; no repository or user data was deleted
- money/inventory/orders/planning/accounting/trust-critical-state: yes — full-suite and count-gate evidence are trust-critical
- AI-or-automation-acts-downstream: yes — later transcription changes workflow-enforced count gates
- worker/scheduler/queue/retry/async-side-effect: yes — the plan expressly bars retry after this red
- cross-repo/service-contract/generated-schema/shared-API-event: yes — m-2/m-3 and master own adjacent surfaces
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the pinned interpreter repair is green, while the product change invalidates the harness-selftest's pinned/read-side assumptions
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — locally excluding harness-selftest, accepting red, or modifying harness would expand or waive the locked plan
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade or waiver is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

RELAY_LINT: daemon-rendered submission; draft and render require v2.9.2 and v2.9.3 exact-file lint, byte equality, one INDEX row, and daemon verification.
FINAL_GIT_STATUS_SHORT:
main checkout:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-PUBLISHED-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
R-4.50 worktree:
 M src/adapters/claude_code/claude_code.cpp
 M tests/test_adapter_claude_collect.cpp

The main checkout rows above are inherited S4/root state. The R-4.50 worktree rows are the exact retained, unstaged, in-scope Task 1 bytes. After daemon render, `.relays/intg/INDEX.md` and the rendered SITREP are the expected additional own-seat main-checkout changes.

Done: exact token/plan/base gates; Task 0 complete; Task 1 RED and targeted GREEN complete; the first full macOS suite executed once and stopped fail-closed.
Not done: no P, Linux observation, workflow transcription, C, owner candidate review, tag, remote branch, push, PR, merge, landing push, publication, deployment, release, or closure.
Blocked: Task 1 Step 5 requires the workflow-equivalent macOS suite rc 0; observed rc 8 from 53 existing harness-selftest failures after the fenced discover change, while harness edits and local exclusion are out of scope.
Next requested action: intg.pair-planner — adjudicate this STOP and issue an exact ruled successor only after resolving the harness-selftest/locked-scope conflict. Preserve the current two-path unstaged bytes and evidence; do not treat targeted GREEN as authority to bypass the failed full-suite gate.
