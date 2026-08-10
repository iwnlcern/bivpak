## SITREP — C restacked and host-green; B2 replay STOPPED on a genuine rebuilt-A semantic conflict in verify-hit cohort handling; no Docker or republication

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-restack-semantic-conflict
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-restack
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — rule whether a verify-hit sibling retains rebuilt-A cohort-wide `containment_refused` / `rewrite_verify_failed` behavior or B2's paneled per-session `verify-hits` behavior; the replay-only token forbids choosing this semantic cell locally
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/IMPL-PLANNER-C-B2-RESTACK-DISPATCH-IMPL-TOKEN-20260809-205244.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: BLOCKED — C is mechanically restacked at d6e44d9 and host-green; B2 candidate b6c3fd7 exposes a reproducible semantic collision with rebuilt-A cohort-refusal tests, so the mandated stop-and-route fired before Docker or publication

BLOCKED / HUMAN SEMANTIC DISPOSITION REQUIRED

## Exact local topology

The execution-time base was local `main` at
`721eeaefd168c917e4ee4cadf7cd0366baa43514`; rebuilt A
`33153137bbf7640cdcf4576de7f41b17fe57ae99` is its ancestor.

Slice C replayed onto that exact base:

- local branch: `s4-floor/c-consent-no-carrier`;
- local head: `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`;
- parent: `721eeaefd168c917e4ee4cadf7cd0366baa43514`;
- exactly one commit, preserved subject
  `feat(open): stage consent-no sessions with provenance sidecar`;
- exact 24-path paneled range, no path outside the dispatch SCOPE_DIFF.

The B2 replay produced a local candidate:

- local branch: `s4-floor/b2-torn-tail`;
- local head: `b6c3fd754b6bfc3ab19debb821f9840accd3291e`;
- parent: `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`;
- exactly one commit, preserved subject
  `feat(pack): collect torn tails and staged sidecars`;
- exact 16-path paneled range, no path outside the dispatch SCOPE_DIFF.

Both worktrees are clean. Neither rewritten branch was pushed. Draft PR #22 remains at
remote `ec9a2db2cfe55191f99efbcf12902a79d99e159e`; draft PR #23 remains at remote
`6a8ea75a2d7ae072839940e69b16f6393c80ac32`, both still based on `main` under the
locked repository topology.

## Replay conflicts and the stop-rule finding

C had two textual conflicts. Both were mechanical and resolved without a new choice:

- `src/adapters/claude_code/install.cpp`: retain rebuilt A's shared
  `version_floor::admit` call and C's per-record staged project-root/key handling;
- `src/core/open/sessions.cpp`: retain rebuilt A's failed-row activation suppression and
  C's `live_at_pack` fallback change.

B2 then conflicted in the two anchored installers. The apparent B2-side resolution
retained B2's paneled replacement of cohort-wide verify-hit refusal with per-session
`verify_failure_detail` refusal. Fresh full-host testing proved that this is not merely
context drift on the rebuilt base:

- rebuilt A added `Claude rewrite verification preserves a sibling capability refusal`;
- rebuilt A added `Codex rewrite verification preserves a sibling capability refusal`;
- rebuilt A added `Codex session leg preserves a version refusal beside a verify-hit sibling`;
- those tests require the verify-hit sibling to remain cohort-refused as
  `containment_refused` with detail `rewrite_verify_failed` and its hit counters intact;
- paneled B2 intentionally converts the row per-session to reason `verify-hits`, detail
  `origin_path` or `origin_id`, and clears the cohort-style result surface.

The exact three-test reproduction selects three cases and returns three failures, ten
failed assertions out of 41. The full B2 product row independently returns 318 passed,
three failed, two skipped out of 323 cases, with 8,349 passed and ten failed assertions
out of 8,359. This is the dispatch's named genuine-semantic-conflict class, so execution
stopped and no attempt was made to alter production or inherited tests.

## Verification reached before the stop

At C `d6e44d9`:

- A3 drift-tripwire/control cohort: 12 passed, 844 deselected;
- compare selftests: 15 passed;
- staged/consent focused product cohort: 333 assertions across 12 cases passed;
- fresh host `ctest --preset dev -E '^safety-hardening$' --output-on-failure`:
  14 of 14 selected rows passed, zero failures, 443.69 seconds; three configured safety
  rows skipped.

At B2 candidate `b6c3fd7`:

- anchored collector bytes and `harness/bivharness/e3.py` are byte-identical to paneled
  head `6a8ea75`, so anchor recapture did not fire;
- A3 drift-tripwire/control cohort: 12 passed, 844 deselected;
- exact I-3/F2/F3/key focused cohort: 43 assertions across four cases passed;
- fresh full-host product row: FAILED on the three rebuilt-A cohort cases above;
- the remaining preset was interrupted after the authoritative product failure rather
  than treated as completion evidence.

The required Ubuntu 24.04 `linux/amd64` Docker suites on both heads did not run because
the host gate is red and the dispatch says stop on a semantic conflict. `git merge-tree`
acceptance, force-with-lease republication, and remote-head verification likewise did not
run. GitHub Actions was not invoked, rerun, or managed. No merge, release, deployment, or
R-4.9/R-4.8 work occurred.

## Requested ruling

Rule the exact cohort cell before any resume token:

1. retain rebuilt A's cohort-wide verify-hit result (`containment_refused`,
   `rewrite_verify_failed`, hit counters intact) and authorize the bounded B2 replay
   adaptation needed to preserve that behavior alongside B2's I-3/F2/F3 work; or
2. affirm B2's per-session `verify-hits` result and explicitly authorize amendment of the
   three inherited rebuilt-A assertions/session mapping.

Either option is a logical semantic choice outside the replay-only token. On a ruling and
fresh token, resume from the two clean local candidates, amend only the explicitly granted
paths, rerun focused + full host + both Docker heads, verify both merge trees, and only
then republish PRs #22/#23.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — local adapter/session replay only
- migration/backfill/destructive-write/canonical-data-repair: no — no persisted data mutation
- money/inventory/orders/planning/accounting/trust-critical-state: no — not in scope
- AI-or-automation-acts-downstream: no — no downstream automated act
- worker/scheduler/queue/retry/async-side-effect: no — not in scope
- cross-repo/service-contract/generated-schema/shared-API-event: no — repository-local replay; schema bytes are unchanged by the conflict response
- user-visible-control-with-materializer/downstream-consumer: no — no new control or materializer
- test-runtime-role-mismatch: no — the conflict reproduces in the canonical host product row
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — inherited rebuilt-A and paneled-B2 refusal semantics disagree; explicit ruling required
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed blocker report presents the semantic-conflict trigger
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: local-only history rewrite produced `s4-floor/c-consent-no-carrier@d6e44d9e5ec4ff48e5121a9674ef7788eca9e881` over `721eeaefd168c917e4ee4cadf7cd0366baa43514` and `s4-floor/b2-torn-tail@b6c3fd754b6bfc3ab19debb821f9840accd3291e` over `d6e44d9e5ec4ff48e5121a9674ef7788eca9e881`; both worktrees are clean; origin branches and draft PRs remain at ec9a2db and 6a8ea75 respectively; this report and its append-only INDEX row are the only shared docs-lane writes; no push, PR edit, Actions operation, Docker run, merge, release, or deployment
FINAL_GIT_STATUS_SHORT: C worktree clean at d6e44d9; B2 worktree clean at b6c3fd7; shared main docs checkout contains pre-existing untracked sibling relay artifacts plus this report and its INDEX append, with no product/test source edit

CARRY LIST:
- semantic ruling + fresh bounded resume token -> `s4-floor.planner`
- clean local C head `d6e44d9` -> host-green, unpublished, Docker and merge-tree still pending
- clean local B2 candidate `b6c3fd7` -> focused-green but full-host red on three inherited rebuilt-A cohort cases
- PR #22 at `ec9a2db`, PR #23 at `6a8ea75` -> unchanged; no remote CI management
- orphan R-4.9, R-4.8, merge, and release -> untouched and held
