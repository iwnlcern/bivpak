## PLAN-REVIEW artifact — MUST-REVISE exact isolation plan at 46e47a0a: two locator mutants are masked; the stub contradicts product precedence; the timeout fence is impossible; the mutant protocol does not prove the positive oracle reds

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-isolation-plan-review
PARENT_DISPATCH_ID: intg-isolation-plan
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-033604.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260901-142647.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260901-155517.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-031727.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the authorized act and exact design pin stand; F2 requires the design owner m-3 to approve a precisely product-faithful synthetic oracle if the successor retains L1; all other corrections and the new exact-hash re-review remain in-lane; implementation, commit, merge, push, publication, deployment, and release remain separately gated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 62a261819ca66ed93be174ecef3c0ce10441f085
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit e1b3e77db74866c25f479fbbee3547806ae8c674, sha256 46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a
BASE: main@42cc085; review filed from main@e1b3e77db74866c25f479fbbee3547806ae8c674; relevant code remains byte-identical to 46df8f3 as the incoming plan records
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: MUST-REVISE exact 46e47a0a — F1 mutate after final profile merge; F2 replace or owner-approve the synthetic oracle; F3 replace the impossible timeout-token grep; F4 prove the same positive oracle turns red under each mutant

## Verdict

MUST-REVISE at exact SHA-256 `46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a`.

The plan is well fenced at the design, write-set, platform, and release boundaries, but its central isolation witness is not executable as claimed. Two of four store-locator mutants are overwritten by named-profile env. The stub then claims product-faithful discovery while enumerating a Claude fallback the product cannot reach and exposing SQLite bytes the product does not report. Independently, the required timeout-constant test makes the zero-timeout-token fence impossible, and the mutant tests assert the leak instead of demonstrating that the positive no-poison oracle turns red. No implementation token may parent to this review.

This is review-only. It authorizes no harness or product edit, plan edit, commit, branch/ref movement, implementation, merge, push, publication, deployment, or release.

## Findings

### F1 — Critical — named-profile precedence masks the `CODEX_HOME` and `CLAUDE_CONFIG_DIR` mutants

Plan lines 33 and 97 prescribe `{**overlay, **profile_env}`. At baseline, `_prepare_agent_profiles` writes staged `CLAUDE_CONFIG_DIR` for named Claude (`scenario.py:290-291`) and staged `CODEX_HOME` for named Codex (`:316-317`). Plan line 53 names both agents, then says each mutant removes one key from `_hermetic_overlay` so `os.environ.copy()` restores poison.

That is false for two required arms. Removing `CODEX_HOME` or `CLAUDE_CONFIG_DIR` from the overlay does not expose inherited poison: the later profile merge puts the staged value back, and `_run_json` overlays that final env on its ambient copy (`scenario.py:140-142`). The canaries required by lines 55 and 57 therefore cannot surface.

Required correction: mutate the final per-command environment after profile precedence, restoring exactly one locator to its poison value while fixing the other four. The positive oracle and guard must exercise the same final env used by pack and open.

### F2 — Critical — L1 contradicts product discovery and cannot substantiate ISO-R2

Plan lines 32 and 98 say the stub enumerates ingress paths “as the product resolves them”; lines 53-54 require a HOME mutant to surface both Codex and Claude HOME canaries. Product Claude instead returns immediately when existing `CLAUDE_CONFIG_DIR` is selected (`src/adapters/claude_code/claude_code.cpp:573-582`); only otherwise can it consult `$HOME/.claude` (`:585-594`). The sealed design records that precedence at lines 141-146. The unconditional stub scan creates a false-positive Claude canary unreachable under the named-profile env.

The SQLite arm is also synthetic content, not product behavior. Line 98 echoes the first 32 raw bytes of `state_5.sqlite`; product treats `CODEX_SQLITE_HOME` as a directory locator (`codex.cpp:1158-1177`) and does not publish arbitrary database bytes as a discovery identity. The invalid raw file can satisfy the stub without proving real E2 behavior. Iso-3 checks getter names, not precedence or payload semantics; iso-4 is only a positive real-suite green. Neither catches this drift.

Required correction: observe actual product discovered/session results with valid locator-distinct fixtures. If synthetic L1 remains, route its exact precedence, existence, and SQLite/session semantics to m-3 before token; do not defer this materially unfaithful latitude to landed-sha veto or claim static census catches behavioral drift.

### F3 — Important — the zero-timeout-token fence is impossible under the required test

Plan lines 18 and 106 require `git diff <base>..HEAD -- harness | grep -ci 'timeout'` to return zero. Line 61 mandates a new selftest referencing `scenario.COMMAND_TIMEOUT_S` and `e3.COMMAND_TIMEOUT_S`. That required test necessarily adds `TIMEOUT` tokens even when production constants remain unchanged.

Required correction: prove budget-bearing production bytes unchanged by exact base-to-landed comparisons. Bind `e3.py` byte-equal to base and compare the existing `scenario.py` constant at its semantic location, or use a path/changed-line proof that permits test assertions while rejecting a budget edit.

### F4 — Important — the mutant tests do not prove the positive oracle turns red

Plan lines 53-59 prescribe tests that break the overlay, disable the guard, and REQUIRE poison to appear. Those tests remain green when leakage occurs. They prove synthetic-log observability, not acceptance line 119's stronger claim that each live mutant “REDs the positive oracle.”

Required correction: factor one positive no-poison oracle and execute that same oracle under each one-coordinate mutation, requiring its failure, or retain a red/green transcript that removes each production clause and shows the ordinary positive test fail. Couple this to F1 so every mutant acts on the final command env.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `3c1ba5edece3f229936acc25661c9b45cb85c28a7968419cab1f95c8ff587ab8`; plan hashes to `46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a` at `e1b3e77db74866c25f479fbbee3547806ae8c674`.
- Design pin re-verifies at the live PDC file and declared source commit: both hash to `290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc`. Incoming structural report and root verification are green; no lineage finding is raised.
- Operator ruling, Master route, Master Reviewer approval with VP concurrence, and m-3 approval stand. This review does not reopen them.
- Three-path harness-only write set, no product/spec/CMake/E3 byte, one local-main implementation commit, both-platform validation, m-3 landed-sha review, and no-push/no-release fences otherwise carry.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — exact PDC design and m-3 ownership govern
- user-visible-control-with-materializer/downstream-consumer: yes — future discovery/restoration semantics are user-visible
- test-runtime-role-mismatch: yes — L1 substitutes a synthetic, presently incorrect stub model
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — L1 and mutant evidence block execution
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade requested
- scan_presented_to_operator: no — m-3 owns the synthetic-model ruling if retained
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Reissue `intg-isolation-plan` at a new exact hash after F1-F4. If L1 remains synthetic, obtain m-3's exact pre-token ruling that it faithfully witnesses ISO-R2; otherwise prescribe a real-product mutant witness. Request a new exact-hash PLAN-REVIEW. No implementation token may issue from this review.

ACTIONS_GIT_REF: read-only review of plan commit e1b3e77db74866c25f479fbbee3547806ae8c674 at sha256 46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a; carrier, design pin/source blob, route, scenario precedence, product discovery, timeout constants, root verification, and index/worktree checked; daemon submission only; no harness, product, plan, branch, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified; inherited root-mode S4 state remains untouched
FINAL_GIT_STATUS_SHORT: none — scoped intg and plan status was empty before daemon submission; inherited s4 state exists outside scope and was untouched
