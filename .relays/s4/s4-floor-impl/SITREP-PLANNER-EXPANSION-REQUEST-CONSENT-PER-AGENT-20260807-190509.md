## SITREP — expansion request: exactly `harness/scenarios/open-consent-per-agent.json`; the pair-level half of the A5 harness blocker is already disposed as Amendment A6 part (1)

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-expansion-request
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a dispatch-universe expansion is the orchestrator planner's to grant, not the pair's; the pair made no edit to the out-of-universe path and will make none absent the grant
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-A5-HARNESS-SCOPE-BLOCKER-20260807-185147.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer
SUBJECT: EXPANSION REQUESTED — one file, `harness/scenarios/open-consent-per-agent.json`, for the decided-not-deleted consent-no flip the already-locked A5 row makes mandatory; slice C's sole remaining red rows are these two stale expectations

## Where slice C stands (implementer's `185147`, verified where checkable at this seat)

Amendment A5 is implemented and focused-green in the held worktree: both authorized
scenarios (`open-consent-no`, `open-deny-default`) runnable-pass asserting
`outcome: staged`, `kind: SessionsStaged`, exit 0, host stores unchanged, no
activation; both locked-schema blob literals recaptured (envelope `4f842442…`,
exit-map `7ac7de89…` preserved). The worktree remains correctly uncommitted at base
`798526c` — the implementer stopped at both scope boundaries instead of editing
through them. The final locally applicable suite has exactly two red rows, split by
authority:

## Half 1 — DISPOSED at this seat (Amendment A6 part (1), no orchestrator action needed)

`harness/selftest/test_e3_asserts.py::test_drift_tripwire_ignores_write_side_install_change`
asserts the presence of the obsolete write-side expression
`target.target_store.root / "projects" / project_key` before mutating it to prove the
C1 collect-side drift tripwire ignores write-side install changes. Task 8's authorized
staging refactor replaced that destination expression, so the fixture's precondition
assert fails. I verified at the bytes: the file IS in the dispatch universe (plan
line 34, global Harness line — a Task-8 Files-list omission, same class as A5's
blocker 1), and the recapture is mechanical (swap anchor expression + its
`projects_moved` mutation to the current expression; the tripwire-clean assertion is
preserved; no `_ADAPTER_SOURCE_ANCHORS` entry moves, so no A3 ceremony fires). Granted
as plan Amendment A6 part (1); plan SHA-256 after A6 is
`d88a6b0275eae5a249c49eaf3cb4301383e8cd760aaf8a530995fa8e4932d3a6`.

## Half 2 — YOURS: dispatch-universe expansion by exactly one file

`harness/scenarios/open-consent-per-agent.json` appears NOWHERE in the locked plan
(mechanically checked — the grep for it returns nothing; the universe names only the
two flipped scenarios). Yet the already-locked A5 row makes its stale expectation
unreachable: the scenario still expects the Claude consent-no leg as
`skipped`/`consent-denied` with exact tree equality, while runtime now correctly
produces Claude `staged`/`SessionsStaged` plus the additive `.biv/agents` carrier and
sidecar, with the consent-yes Codex leg installed. This is the SAME wire change the
locked chosen-outcome row mandates, surfacing in the one mixed-consent scenario the
plan's authors did not enumerate.

Requested grant, exact: expand the dispatch universe by
`harness/scenarios/open-consent-per-agent.json` alone, admitting the
decided-not-deleted flip — Claude becomes `staged`/`SessionsStaged`; Codex remains
`installed`; host-target deltas remain Claude-unchanged/Codex-changed; the exact-tree
assertion changes ONLY to account for the intentional additive `.biv/agents` staging
carrier. The flip's terms are pre-recorded as Amendment A6 part (2), EFFECTIVE ONLY
UPON your grant; if you refuse, the scenario stays unedited and its red is disclosed
at the head as an out-of-universe stale expectation with your refusal cited.

## On grant (or refusal), the pair resumes without further upstream traffic

My resume relay to the implementer will cite your disposition; the implementer then
recaptures the granted expectations, reruns the focused checks and the locally
applicable suite, creates slice C's sole commit, runs the standing local Ubuntu 24.04
`linux/amd64` Docker containerized suite (the CI evidence of record while the Actions
quota is exhausted), and publishes under the standing publication disposition. Merge
and release remain the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: edits at this seat are docs-lane only — the A6 amendment appended to docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md, this relay, and its append-only INDEX row, riding one explicit-path docs-lane commit whose SHA lands in repository history after filing; no source/test/schema/scenario edit is claimed at this seat, and the out-of-universe scenario file is untouched
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (the held slice-C worktree is elsewhere at base 798526c); this seat's writes are confined to the three docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-EXPANSION-REQUEST-CONSENT-PER-AGENT-20260807-190509.md` → `s4.orchestrator-planner`
- `harness/scenarios/open-consent-per-agent.json` one-file expansion + decided-not-deleted flip terms → orchestrator grant or refusal requested
- plan Amendment A6 at plan SHA-256 d88a6b0275eae5a249c49eaf3cb4301383e8cd760aaf8a530995fa8e4932d3a6 → part (1) effective now; part (2) conditional on the grant
- held slice-C worktree at `s4-floor/c-consent-no-carrier` / base `798526c` → resumes on my relay after your disposition
