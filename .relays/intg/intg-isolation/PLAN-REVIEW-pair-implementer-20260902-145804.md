## PLAN-REVIEW artifact — APPROVE exact isolation plan revision 1 at c8bd21f0; all four 035526 findings are closed in the plan; m-3's addressed L1 ruling remains a hard pre-token gate

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-isolation-plan-review
PARENT_DISPATCH_ID: intg-isolation-plan
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-144620.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md; intg-isolation/SITREP-pair-planner-20260902-144956.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260901-142647.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260901-155517.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-031727.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this exact-hash plan review is approve, but it does not adjudicate the synthetic L1 model for design owner m-3; the pair Planner may mint no implementation token until m-3's addressed exact pre-token ruling also approves that model, and a ruling for option B stops this plan for revision; all implementation, landed-sha review, merge, push, publication, deployment, and release gates remain; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 62a261819ca66ed93be174ecef3c0ce10441f085
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit 292a4483c06d8753951d1389cf5f9ed409c40fd8, sha256 c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed
TARGET_RELAY_SHA256: ea192a187912274ef762a4c749dc1849e26285101352df277ebac2193d33e7a3
BASE: main@56fe0fb at the reviewed carrier; review performed at main@292a4483c06d8753951d1389cf5f9ed409c40fd8; governed harness, adapter, and CLI bytes remain byte-identical to product pin 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: APPROVE exact c8bd21f0 — F1 final-command-env mutants, F2 exact owner-routed precedence model, F3 byte-level budget proofs, and F4 one positive oracle turned red by every mutant are plan-sound; m-3's affirmative pre-token L1 ruling remains required

## Verdict

APPROVE the exact plan artifact at SHA-256 `c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed`, carried by `intg-isolation/PLAN-pair-planner-20260902-144620.md` at SHA-256 `ea192a187912274ef762a4c749dc1849e26285101352df277ebac2193d33e7a3`.

Revision 1 closes all four findings in `035526`. Its three-path harness-only write set, one-local-main-commit boundary, no-calibration fence, two-platform evidence, and downstream release holds are executable and reviewable as written. This approval is one of two conjunctive preconditions for a token. It is not m-3's design ruling: silence, rejection, or an option-B ruling from m-3 keeps implementation stopped and requires a successor plan where applicable.

This is review-only. It authorizes no harness or product edit, plan edit, implementation, commit, branch/ref movement, merge, push, remote CI, publication, deployment, or release.

## Closure of the four returned findings

### F1 — closed — each mutant now acts on the final command environment

`scenario._run_json` copies ambient environment and then applies its final `env_overrides` (`scenario.py:134-150`). Named profile preparation writes staged `CLAUDE_CONFIG_DIR` and `CODEX_HOME` (`:290-291`, `:316-317`), and the pack/open call sites consume the merged environment at `:499` and `:535-545`.

The revised `_restore_poison(monkeypatch, locator)` therefore wraps `_run_json` and removes exactly the selected locator from a fresh copy of the final per-command overrides, after named-profile precedence and after `_probe_open_env`. Ambient poison reaches both pack and open for that coordinate; the other four locators remain fixed. The runtime guard executes before this test-only wrapper and remains active. This directly repairs the two masked rev0 arms.

### F2 — closed at plan-review scope — the synthetic model is source-faithful and owner-gated

The revised L1 transcription matches the pinned source boundaries it names:

- Claude uses an existing `CLAUDE_CONFIG_DIR` and returns without consulting HOME (`claude_code.cpp:573-582`); HOME fallback exists only otherwise (`:585-594`).
- Codex takes an existing `CODEX_HOME` and independently appends a distinct existing `$HOME/.codex` (`codex.cpp:1195-1206`); sessions and archived sessions are path identities (`:1177-1190`).
- `CODEX_SQLITE_HOME` is a directory locator (`:1158-1170`) and database identity is its `state_5.sqlite` path, never file contents (`:1226-1236`).
- TMPDIR is represented through `tempfile.gettempdir()` for the subprocess model, corresponding to `fs::temp_directory_path()` (`codex.cpp:1084`).

The plan explicitly excludes the `config.toml sqlite_home` fallback because `CODEX_SQLITE_HOME` remains set in the positive and every one-coordinate mutant. It also states the precise HOME-arm consequence: with an existing `CLAUDE_CONFIG_DIR`, a one-coordinate HOME mutant can expose Codex `$HOME/.codex` but cannot expose Claude `$HOME/.claude`; the oracle requires the former and asserts absence of the latter.

Most importantly, the plan withdraws the false claim that a getter census proves behavioral fidelity and routes this exact L1 model to design owner m-3 before token. That routing is the required resolution of F2 at PLAN-REVIEW. This relay does not substitute a pair-seat judgment for m-3's design authority. An affirmative addressed m-3 ruling is still mandatory; option B stops this exact plan.

### F3 — closed — budget integrity is now proved over budget-bearing bytes

The revised evidence separates the required iso-4 selftest names from production-side timeout bytes: all of `e3.py` must remain equal to base; `scenario.py`'s existing `COMMAND_TIMEOUT_S = 30` line and value must remain equal to base; and changed lines in `scenario.py` plus `stub_biv.py` must contain no timeout token. The new selftest is intentionally outside the third predicate. These three checks allow the required guard while vetoing calibration edits.

### F4 — closed — every live mutant must fail the same positive oracle

The plan factors one `_assert_hermetic_discovery` positive oracle. The ordinary iso-1/iso-2 path must pass it with non-vacuous staged transcript evidence. Each of the five one-coordinate mutants runs that same oracle inside `pytest.raises(AssertionError)` and then proves `_leak_tags == {LOCATOR}`. Thus each mutant demonstrates the positive property becoming false for exactly its own canary; it no longer treats leakage as a green assertion.

## Scope and acceptance review

- Write set is exactly `harness/bivharness/scenario.py`, `harness/selftest/stub_biv.py`, and new `harness/selftest/test_store_isolation.py`.
- No `src/`, `harness/scenarios/`, CMake, `e3.py`, product behavior, schema, or persisted-contract byte is writable.
- Seven markers remain exact: iso-1 x4, iso-2 x1, iso-3 x1, iso-4 x1.
- Positive isolation, five one-coordinate mutant failures, source-aware locator census, timeout guards, full harness selftests, real E2, and local Ubuntu 24.04 amd64 parity are all acceptance evidence; the canonical Docker run must use `--init` and restore non-root nofile soft to hard.
- The plan's `<base>` proof operand is bound by the eventual token/landing attempt. The artifact's authoring baseline `42cc085`, carrier baseline `56fe0fb`, and review HEAD `292a4483` contain no governed code drift: `harness`, `src/adapters`, and `src/cli/main.cpp` remain byte-identical to product pin `46df8f3`.
- One local-main implementation commit is the maximum authorized landing form after both preconditions. No remote CI, push, PR, publication, deployment, or release follows from this review.

## Exact evidence

- Incoming carrier SHA-256: `ea192a187912274ef762a4c749dc1849e26285101352df277ebac2193d33e7a3`; exact-file relay lint green; root `relay verify` green.
- Plan SHA-256: `c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed` at commit `292a4483c06d8753951d1389cf5f9ed409c40fd8`; dead rev0 is `46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a` at `e1b3e77db74866c25f479fbbee3547806ae8c674`.
- Live design, declared target commit `62a261819ca66ed93be174ecef3c0ce10441f085`, and declared source commit `b706e745c1890ce43c117a756103c415b4d0c29a` all resolve the design bytes at SHA-256 `290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc`.
- Relevant product and harness bytes are unchanged from the reviewed product pin; the source-aware model was independently checked against the cited Claude, Codex, scenario merge, profile, pack, open, and probe locations.
- `intg-isolation/SITREP-pair-planner-20260902-144956.md` separately carries the exact L1 text to master/m-3. No addressed m-3 ruling was visible at this review filing; absence is a stop, not latitude.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — exact PDC design and m-3 ownership govern
- user-visible-control-with-materializer/downstream-consumer: yes — future discovery/restoration semantics are user-visible
- test-runtime-role-mismatch: yes — L1 is a synthetic source model, expressly gated on m-3's exact ruling
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — unresolved L1 ownership is a hard pre-token stop, not waived risk
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade requested
- scan_presented_to_operator: no — m-3 owns the exact model ruling and master carries the route
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Handoff

The pair Planner may consume this APPROVE only together with an affirmative addressed m-3 ruling on the exact L1 model. If and only if both are present and all standing scope conditions remain met, the Planner may perform the mechanical scope diff and issue the separately linted implementation token parented to this `intg-isolation-plan-review` dispatch. Any option-B ruling or model amendment requires a newly hashed plan and a new exact-hash review.

ACTIONS_GIT_REF: read-only review of plan commit 292a4483c06d8753951d1389cf5f9ed409c40fd8 at sha256 c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed; carrier, design pin/source blob, prior findings, scenario precedence, product discovery, budget proofs, oracle coupling, scope, root verification, and worktree checked; daemon submission and path-scoped relay commit only; no harness, product, plan, branch, ref, merge, push, remote CI, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, root verification, and committed bytes will be re-verified; inherited root-mode S4 state remains untouched
FINAL_GIT_STATUS_SHORT: none — scoped intg status and the reviewed plan were clean before daemon submission; inherited S4 state exists outside scope and was untouched
