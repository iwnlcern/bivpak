## PLAN REVIEW — re-key is correct, but append-only historical root errors require operator disposition before delegated dispatch

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-pair-plan-review
PARENT_DISPATCH_ID: s4-floor-pair-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — operator must either issue a direct implementation dispatch, explicitly waive the named historical relay-root errors for a replacement delegated dispatch, or authorize a tooling/history remediation path
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
PLAN_REVIEW_VERDICT: human-decision-required
IN_REPLY_TO: .relays/s4/s4-floor-plan/PLAN-PLANNER-REKEYED-20260805-155200.md
FROM: s4-floor.implementer
TO: operator
CC: s4-floor.planner, s4.orchestrator-planner
SUBJECT: HUMAN-DECISION-REQUIRED — unique pair PLAN lineage is correct, but the append-only voided dispatch keeps full relay-root lint red

## Review basis

- Re-keyed pair PLAN relay: `.relays/s4/s4-floor-plan/PLAN-PLANNER-REKEYED-20260805-155200.md`, SHA-256 `09387dfa4a78fe48fb464dac87ec1c022814e8329c2871018170db8bd55389ca`.
- Re-key filing commit: `43c463323b3bf41c8c98ac79f06c82bfcf9ba18c`.
- Locked plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md`, unchanged SHA-256 `5e88a538b26d8318d3a6260dc4f988e644bcf3ed153a7c0a970cbd25918cfecb`.
- `git diff --exit-code 7a8e1c61d613f53dbd06afb93eaaa8c5e5f7db71 HEAD -- docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md` returns zero: no plan-byte drift from the rev2-approved filing.
- `git diff --exit-code 8981bfd HEAD -- src tests harness schemas CMakeLists.txt` returns zero: no product/test/harness/schema drift.
- `rg -l '^DISPATCH_ID: s4-floor-pair-plan$' .relays/s4 --glob '*.md'` returns exactly this one re-keyed pair PLAN relay.
- Historical exact-file lint passes with `--no-freshness`.

## Substantive grade

The re-key is correct. `DISPATCH_ID: s4-floor-pair-plan` is unique, the relay is FROM the pair Planner and addressed TO this Implementer, its parent remains the approved design-review lineage, and the locked plan bytes are exactly those approved in `s4-floor-plan-review-rev2`. No design, plan, scope, acceptance, topology, or hold finding is reopened.

## Blocking gate

The relay says the Planner will verify the full chain with `relay-lint --relay-root` before filing a replacement delegated dispatch. That check cannot currently return clean while the append-only historical root remains as filed.

Fresh command:

`python3 /Users/jack/Programming/agentic-dev-team-skills/tools/relay-lint.py --relay-root .relays/s4`

returns nonzero and still reports against the voided `.relays/s4/s4-floor-plan/IMPL-PLANNER-DISPATCH-20260805-154105.md`:

- `PLAN-REVIEW must review the pair Planner's PLAN, not a CC'd orchestrator dispatch`
- `pair-Planner PLAN must address the Implementer in TO for review`

The linter scans every Markdown file under the root and contains no VOID/supersession exclusion for a historical bare token. Appending this correct lineage therefore does not remove the old errors. In this checkout, root mode also passes `.relays/s4/INDEX.md` through relay-file lint and reports its missing relay headers; the dedicated `--index` mode remains the correct clean check for that file.

The protocol states that a relay-lint structural error blocks delegated dispatch unless the operator explicitly waives it. The pair cannot edit append-only historical bytes, self-waive the error, change the linter in this plan's scope, or truthfully claim a clean full-root result.

## Verdict

HUMAN-DECISION-REQUIRED

The plan is substantively approved and correctly re-keyed, but another pair-Planner delegated token would remain blocked by known historical root errors. Operator disposition is required through one of these bounded paths:

1. issue a direct operator/orchestrator implementation dispatch under the protocol override path;
2. explicitly waive the named historical root errors for a replacement delegated dispatch while requiring exact-file lint and verification of the new unique chain; or
3. authorize a separate tooling/history remediation that makes full-root lint recognize voided artifacts and excludes `INDEX.md` from relay-file lint.

No implementation authority issues from this review. No worktree, implementation branch, product edit, PR, push, merge, seal, or release action is authorized or claimed.

ACTIONS_GIT_REF: this review relay and its append-only INDEX row are the only seat writes; explicit paths are disk evidence and the docs-lane commit is named in repository history after filing.

FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-plan/PLAN-REVIEW-IMPLEMENTER-REKEYED-20260805-155619.md

## Next action

Operator: select one of the three bounded authority/remediation paths above. Planner and orchestrator are copied for routing; the Implementer remains held.
