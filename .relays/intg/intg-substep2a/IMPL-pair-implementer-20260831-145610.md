## IMPL return — C3 still red after routed venv setup: ambient credential rejection plus three E2 pack timeouts; source untouched

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-return
PARENT_DISPATCH_ID: intg-substep2a-impl
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260831-141517.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-implementer-20260831-140506.md; intg-substep2a/IMPL-pair-planner-20260831-030859.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the pair Planner can route environment sanitation and a bounded rerun; no product-semantic or operator-waiver decision is requested
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996 in /Users/jack/Programming/bivpak-intg-format-act; clean; no implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: BLOCKED again before Task 1 RED — C1/C2 passed, but C3 is 16 pass / 3 fail / 3 skip: retained readelf red plus harness-selftest credential rejection and three harness-e2 pack timeouts

## Status

BLOCKED before the first test or production edit. I executed the exact PATH-1 setup and cache-routing conditions from `141517`. C1 and C2 are green. C3's explicit stop fired because two dependency-backed harness rows remain red in addition to the retained `readelf unavailable` row. No semantic byte changed; the isolated worktree is clean at the pinned base.

## C1/C2 — green

```text
python3 -m venv .venv-harness                                        rc 0
.venv-harness/bin/python -m pip install -r harness/requirements.lock rc 0
old cache preserved at /tmp/bivpak-ci-macos-cache.LTniWW/ci-macos
cmake --preset ci-macos                                              rc 0
cmake --build --preset ci-macos                                      rc 0
BIVHARNESS_PYTHON:FILEPATH=/Users/jack/Programming/bivpak-intg-format-act/.venv-harness/bin/python3
jsonschema==4.25.1; pytest==8.4.2; zstandard==0.25.0
```

`probe_envelope_schema` and `generated_envelope_conforms` both passed under that interpreter.

## C3 — stop fired

```text
ctest --preset ci-macos                         rc 8; 843.98 s
summary                                         16 passed / 3 failed / 3 skipped (84%)
repo_engine                                     pass, 22.47 s
biv_tests                                       pass, 480.66 s
probe                                           pass, 11.53 s
probe_envelope_schema                           pass
generated_envelope_conforms                     pass
safety-build-werror                             pass
harness-selftest                                fail, 119 failed / 884 passed
harness-e2                                      fail, 3 invalid / 8 runnable passed
safety-hardening                                fail: readelf unavailable (the permitted retained host red)
```

The full log is retained at `build/ci-macos/Testing/Temporary/LastTest.log`.

## Selftest cause and control

The process inherits the name `ANTHROPIC_API_KEY`; `OPENAI_API_KEY` is absent. No value was read or recorded. Failures converge on `detail='credential-env:ANTHROPIC_API_KEY'`. Removing only that ambient name proves the locked dependency environment is green:

```text
env -u ANTHROPIC_API_KEY ../.venv-harness/bin/python3 -m pytest selftest -q
1003 passed in 11.28s                                              rc 0
```

## E2 result

`build/ci-macos/harness-e2-report.json` contains no failed rows, but three invalid rows at one pack-side timeout boundary:

```text
open-deny-default       command timeout after 30s: pack <scratch>/open-deny-default/source
open-store-locked       command timeout after 30s: pack <scratch>/open-store-locked/source
open-unknown-agent      command timeout after 30s: pack <scratch>/open-unknown-agent/source
```

The other eight runnable rows passed; six registered pending rows stayed `xfail-pending`. CTest correctly marked `harness-e2` red after 308.99 s. This is not candidate-attributable because the branch still equals the pinned base.

## Routed decision requested

Please return one exact treatment for both non-permitted C3 reds. Recommended narrow path:

1. Admit value-free test-process sanitation (`env -u ANTHROPIC_API_KEY`) for macOS baseline and candidate CTest invocations.
2. Admit one isolated rerun of the three E2 timeout rows, then the full `harness-e2` row under the sanitized environment. If every runnable row passes, rerun full C3 sanitized and begin Task 1 only if its sole remaining red is `readelf unavailable`. If any timeout repeats, STOP and return the isolated receipt without beginning Task 1.

If that changes the canonical instrument rather than its clean-room environment, revise and re-route it. I infer neither choice.

## Boundary and not-done

- All seven authorized paths remain byte-identical to base; no Task 1 test or implementation commit exists.
- Only ignored `.venv-harness` and `build/ci-macos` state changed; tracked worktree status is empty.
- No format, M-surface, m-2, m-3, schema, harness, workflow, 2b wiring, merge, push, PR, publication, deployment, or release action occurred.
- Inherited primary-worktree S4 state was untouched.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — an ambient credential variable name, never its value, contaminated the test process; no credential access or mutation occurred
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked M/N remains the governing contract
- user-visible-control-with-materializer/downstream-consumer: yes — planned feature only; no implementation byte exists
- test-runtime-role-mismatch: yes — ambient credential inheritance and three base-tree E2 pack timeouts violate C3
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — proceeding would confound attribution
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: created ignored `.venv-harness` from `harness/requirements.lock`; preserved old cache at `/tmp/bivpak-ci-macos-cache.LTniWW/ci-macos`; freshly configured/built; verified exact interpreter route; ran full CTest to rc 8 and sanitized selftest to rc 0; worktree clean at intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; no source/test edit or implementation commit; submitting from primary main@5506e63b920c1877f142c6be3ab3864fb1113f39
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest reported externally
FINAL_GIT_STATUS_SHORT:
worktree `/Users/jack/Programming/bivpak-intg-format-act`: none — clean at intg/format-act@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
primary `/Users/jack/Programming/bivpak`: inherited S4-only dirt; no intg tracked dirt before this daemon submission
