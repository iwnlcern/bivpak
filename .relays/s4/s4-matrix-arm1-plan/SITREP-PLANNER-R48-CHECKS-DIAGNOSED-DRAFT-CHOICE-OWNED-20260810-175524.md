## SITREP — R-4.8 merge blocker: I MEASURED the eight failed checks rather than assuming them cosmetic — ALL FOUR jobs on ALL THREE branches (three different code contents, including this one at both heads) completed with **ZERO STEPS EXECUTED** in 2-15 seconds, so no runner ever ran a single line of any build or test; the failures are infrastructure-level and code-independent, evidenced not inferred. And the DRAFT blocker traces to MY choice at publication — I own it and frame the options; I have NOT undrafted (that is the same ancillary mutation the Implementer correctly refused, and it is not mine to self-grant either)

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-checks-diagnosed
PARENT_DISPATCH_ID: s4-matrix-r48-condition4-merge-blocked
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — both blockers are YOURS/the operator's to disposition: (1) who performs or authorizes the DRAFT→ready transition, and (2) whether the measured check state is accepted. This relay supplies EVIDENCE for (2) and OWNERSHIP plus options for (1); it grants nothing, waives nothing, and mutates nothing. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — the eight failures measured (zero-step, code-independent); the draft choice was mine; two dispositions requested

## First: the Implementer's stop was CORRECT and its reasoning was the right reasoning

It refused to manufacture readiness under a merge-only token, and it explicitly declined
to treat the failed checks as cosmetic on the strength of the carried aggregate items —
"the carried two aggregate items do not by themselves authorize interpreting every
current failed check as cosmetic or non-gating." That is exactly right, and it is why I
went and MEASURED them instead of repeating the assumption.

## Blocker (2) — the eight checks, MEASURED (read-only; no rerun, no mutation)

The eight are four distinct jobs × two near-simultaneous runs (a push event and a
pull_request event 2 seconds apart). The four: `harness-selftest`, `safety-fuzz-smoke`,
`build-linux-x86_64`, `build-macos-arm64`.

**The decisive fact: not one of them executed a single step.**

```text
run 31446163556  (s4-matrix/r48-carrier @ 0ab998d, event=pull_request)
  harness-selftest    concl failure  steps 0   00:28:35 -> 00:28:37   labels [ubuntu-latest]
  safety-fuzz-smoke   concl failure  steps 0   00:28:35 -> 00:28:38   labels [ubuntu-latest]
  build-linux-x86_64  concl failure  steps 0   00:28:35 -> 00:28:37   labels [ubuntu-24.04]
  build-macos-arm64   concl failure  steps 0   00:28:35 -> 00:28:37   labels [macos-15]
```

Every job: `steps 0`, completed 2-3 seconds after start. A job that fails having run no
steps did not fail a build or a test — it was never picked up and executed.

**Cross-branch control (this is what makes it code-independent rather than a guess).**
The same shape holds on branches carrying entirely different content:

```text
run 31444725258  (s4-floor/b2-torn-tail  @ 8b12b25)  all 4 jobs, steps 0, 2-4s
run 31404485362  (s4-floor/c-consent-no-carrier @ b8083be)  all 4 jobs, steps 0, 2-15s
run 31393283971/31393239758  (this branch @ the PREVIOUS head 2341667)  same class
```

Three branches, three different diffs, one identical failure signature. A code-caused
failure cannot be invariant across unrelated code; a runner/startup-level failure is.
So the "known cosmetic under CI-leg (a)" characterization is now MEASURED for this PR,
not carried on faith — and the measurement is reproducible at your seat with
`gh api repos/iwnlcern/bivpak/actions/runs/<id>/jobs`.

**What I am NOT claiming.** I am not claiming the workflow is healthy — it is not; no CI
signal exists for any branch right now, and that is its own (pre-existing, non-R-4.8)
problem worth its own item. I am not claiming the product passes CI — CI never ran. The
governing Linux signal remains the local Docker leg, exactly as the publication token
ruled. And I am not waiving anything: the disposition is yours.

**One mechanical fact for your ruling:** `main` has NO branch protection
(`GET /branches/main/protection` → 404 "Branch not protected"), and the PR reports
`mergeable=MERGEABLE`, `mergeStateStatus=UNSTABLE`. UNSTABLE means non-required checks
are failing — it is not a merge-blocking state. So the checks are, mechanically, not
what blocks this merge. **DRAFT is.**

## Blocker (1) — the DRAFT status is MY choice, and I own it

At publication (`063109`) I chose to open PR #24 as a DRAFT and disclosed the reasoning
at the time: the production-risk precedent (slices A/C/B2, PRs #21-#23) is draft, and
draft is the shape that cannot be over-read as merge-ready. That was right for a branch
whose review window was still open. It is now the thing standing between a fully
reviewed head and the merge you authorized — the cost of my own conservatism, surfacing
one step later than it should have. The condition-4 token was scoped "merge only, no
ancillary mutation," which is correct and which no acting seat should quietly widen.

**I have not undrafted it.** The Implementer refused that exact mutation for want of a
grant; my performing it instead would be the same ungranted act moved to a seat that
also lacks the grant — which is precisely the shape this team refuses. So it comes to
you with options rather than a fait accompli:

- **(a) You or the operator perform the ready transition**, then the standing
  condition-4 token is satisfiable as written (merge only) and the Implementer proceeds
  after its own fresh head/base/mergeability preflight. Narrowest change; the token's
  boundary stays intact.
- **(b) Issue a renewed condition-4 token that explicitly includes the single
  `gh pr ready 24` transition** as an in-scope prerequisite, bounded to that one call
  at exact head `0ab998d`. One relay instead of two acts, at the cost of widening a
  token boundary — state it explicitly if you take it, so it is a grant and not a drift.
- **(c) Merge from a draft** — GitHub does not permit it; not an option, listed only so
  the enumeration is complete.

My recommendation is (a): it leaves the merge token exactly as scoped, and the draft
transition sits with the seat that owns the PR-lifecycle decision rather than being
absorbed into an implementation token.

## State at my seat right now (re-verified this pass)

```text
branch tip / published head / PR #24 head   0ab998d8431a20de80b8d769fb82c1350ed0728d   (all three agree)
PR #24                                       OPEN, DRAFT, base main, mergeable=MERGEABLE, mergeStateStatus=UNSTABLE
main (remote)                                8981bfd0848039d533d9bb2a96301d4d81b564fa
branch protection on main                    none (404)
```

## Carried unchanged

Six sealed records describe exactly these bytes. The two aggregate items stay OPEN and
are not this branch's debt. INFO-3 stands. Merge ≠ release; the release hold is
ABSOLUTE. STEP 4 (published ref + landed merge SHA for condition-3-of-record closure)
remains owed by me once a merge actually lands.

ACTIONS_GIT_REF: read-only investigation only — `gh pr view`, `gh run list`, `gh api .../runs/<id>/jobs` across three branches, and `gh api .../branches/main/protection`. NO merge, NO ready/undraft, NO rerun of any check, NO push, NO release, NO PR edit of any kind. Docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no edit at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-175524 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-CHECKS-DIAGNOSED-DRAFT-CHOICE-OWNED-20260810-175524.md` → TO `s4.orchestrator-planner`
- blocker (2) MEASURED: all 4 jobs, ALL THREE branches, `steps 0`, 2-15s — no runner executed anything; failure signature invariant across unrelated diffs ⇒ infrastructure-level, code-independent; reproducible at your seat; NOT a waiver, and NOT a claim that CI is healthy (no CI signal exists for any branch — its own pre-existing item)
- mechanical: `main` unprotected, `mergeable=MERGEABLE`, `mergeStateStatus=UNSTABLE` ⇒ the checks do not block the merge; DRAFT does
- blocker (1) OWNED: the draft choice was mine at `063109` and its reasoning is on record; I did NOT undraft (same ungranted mutation the Implementer refused); options (a)/(b)/(c) framed, (a) recommended
- STEP 4 still owed by me on the landed merge SHA; release hold ABSOLUTE
