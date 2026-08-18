## PLAN-REVIEW — APPROVE rev3 S-17 with exact comment placement and two content-anchor clarifications bound into the token

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-r431-recipe-plan-review-rev3
PARENT_DISPATCH_ID: s4-floor-slice-e-r431-recipe-plan-rev3
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-S17-R431-RECIPE-COMMIT-SCOPE-LOCKED-20260818-144504.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — this review clears only the local pair PLAN-REVIEW gate; a fresh floor-Planner implementation token parented to this review remains mandatory, and the landed two-file commit returns to m-3 for byte review before R-4.31 can close
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: APPROVE — exact rev3 bytes and charter source match; place one Python comment immediately above the Linux want mapping; carry content-key evidence and the fresh m-3-owned workflow review as two binding clarifications in the token

PLAN_REVIEW_VERDICT: approve

## Exact review basis

The committed rev3 plan at docs-lane commit `3099cee` and the worktree file both hash
`c681315d95200202a7afa6b9d07de8e55ea2d78bea29b1b93728ce49af61a4d6`.
Exact-file relay lint passes. Its `TO`, parent, two-row SCOPE_DIFF, no-token authority,
one-commit form, no-rerun rule, m-3 return gate, and operator merge/release holds are
internally executable.

I independently resolved `184a9c2` to
`184a9c2e676d59150e4a220be4c2829a54b019e1`, proved it is an ancestor of current pdc
HEAD, extracted `pdc/CLAUDE.md:206-210` from that object, and re-derived the exact
five-line bullet hash as
`6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd`.
It matches the plan and the required `runuser`/`nofile`/content-key shape.

The isolated implementation worktree remains clean at
`e8aabc4077a3aad07d48fdc184f32271049e19aa`. `bivpak/CLAUDE.md` lacks the bullet, and
the Linux `want` mapping remains `successes=412`, `failures=0`,
`expectedFailures=0`, `skips=1`. No implementation or test act occurred in this review.

## Answers and adopted binds

### 1. Exact comment placement and text shape

Place one multi-line Python comment immediately above the Linux count gate's `want = {`
mapping, inside the existing Python heredoc. That is closer than the step heading to the
content the condition qualifies, remains statement-only, and cannot alter YAML or shell
execution.

Use this self-relative content shape in the token and implementation:

```text
# The `want` counts in this job were observed with the `nofile` soft limit equal
# to the hard limit. The chartered local substitute raises the soft limit to the
# inherited hard limit inside its `runuser` drop before invoking the suite.
```

The repository indentation needed by the heredoc is not part of the prose. The content
states both ruled halves and contains no workflow or source line number.

### 2. Charter bullet hash

Yes. Independent result:

`6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd`.

The implementation must copy the five lines from the charter object itself and then hash
the landed five-line block; the plan, this review, and the hash are checks, not typing
sources.

### 3. Two clarifications the token must carry

The S-17 implementation and A16-A21 are approved with these two precise readings:

1. **Content anchors govern evidence too.** The plan's historical `:68/:71/:268/:271`
   references identify the `e8aabc4` cells but are not durable acceptance evidence. A20
   is executed and reported by job plus mapping key: macOS `want.successes=410` and
   `want.skips=3`; Linux `want.successes=412` and `want.skips=1`; both jobs retain
   `failures=0` and `expectedFailures=0`; m-3's identity line is compared by exact
   content. Neither the landed comment nor the implementation report may cite those
   cells only by living line position.
2. **The new comment is on m-3's owned workflow surface.** The plan's phrase that S-17
   touches neither owner's reviewed surface means only that it lies outside the prior
   `e8aabc4` verdict fences and does not reopen their substance. It does touch the
   m-3-owned workflow surface, so the plan's separately stated fresh m-3 byte review is
   mandatory and cannot be elided by quoting the earlier combined PASS.

These clarifications resolve wording tension without changing the permitted paths,
comment semantics, mirror bytes, acceptance outcome, or ordered gates. The fresh token
must adopt them as binds; any token that instead treats positions as acceptance anchors
or treats the prior m-3 PASS as covering the new comment is invalid.

## Scope and gate verdict

The scope is exactly complete for S-17: `.github/workflows/s2-harness.yml` for the
statement-only comment and `CLAUDE.md` for the byte-identical charter mirror. Every other
workflow byte, every `want` value, every expected-skip identity, every run line, all
product/test/fixture bytes, and all pdc bytes remain OUT. A need for any third path or an
executable workflow change is a STOP to the floor Planner.

This approval grants no implementation authority. The next lawful act is one fresh
floor-Planner token parented to this review, carrying the exact placement/text shape and
the two clarifications above. No rerun is owed. After the one commit naming R-4.31 lands,
it returns to m-3 for byte review; merge remains a separate operator gate and the release
hold remains ABSOLUTE.

No Docker run, local test, GitHub Actions, remote CI, push, PR, merge, publication,
deployment, or release occurred.

ACTIONS_GIT_REF: review-only at docs-lane HEAD `3099cee`; incoming plan worktree and committed blob SHA-256 both `c681315d95200202a7afa6b9d07de8e55ea2d78bea29b1b93728ce49af61a4d6`; pdc charter commit full SHA `184a9c2e676d59150e4a220be4c2829a54b019e1`, ancestor check PASS, exact bullet SHA-256 `6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd`; implementation worktree clean at `e8aabc4077a3aad07d48fdc184f32271049e19aa`; this review plus one live-EOF INDEX row are the only seat-authored writes and will ride one explicit-path docs-lane commit
RELAY_LINT: incoming exact-file no-freshness PASS; outgoing exact-file freshness required; live INDEX EOF re-read immediately before append; dedicated INDEX lint run after append; inherited INDEX reds disclosed separately; explicit-path stage and commit only
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling-authored untracked state; this seat's writes are confined to this review and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-S17-R431-APPROVE-CONTENT-ANCHORS-20260818-144652.md` -> `s4-floor.planner`
- `PLAN_REVIEW_VERDICT: approve`; no implementation token inferred
- comment: immediately above Linux `want = {`, Python comment, exact self-relative three-line content shape above
- charter bullet: independently re-derived SHA-256 `6f245a90`, copy from pdc object `184a9c2`
- token binds: acceptance evidence by job/key rather than living positions; new workflow comment always receives fresh m-3 byte review
- next: fresh token parented to this review; one two-path R-4.31 commit; no rerun; route to m-3
