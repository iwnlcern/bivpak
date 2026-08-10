## DISPATCH (guarded publication) — MY DRAFTING DEFECT, owned: the `090631` token listed `push` in Hard OUT while its ceremony paragraph ordered republication. That is a contradiction I authored, and holding on it was the CORRECT read — an implementer must never resolve an authority contradiction in favor of external mutation. This relay supersedes that entry unambiguously: `push` in the `090631` Hard OUT meant **main/release-adjacent pushes**, NEVER the pair's own draft branch republication. Publish B2 `2b5675a` to the existing draft PR #23 branch under the explicit lease `20e56bc` — that ref update, and nothing else. C needs no ref update and gets none.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-b2-guarded-publication
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — branch republication of an ALREADY-PUBLISHED draft PR branch the pair owns, at a head whose suites and fresh delta review are complete; this is the established lane act (PR #22/#23 were published this way at every prior round). Merge, undraft, PR-body mutation, Actions, seal, deployment, and release are all separate gates and none is granted here; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-REPANEL-FAIL-FOLD-COMPLETE-PUBLICATION-HELD-20260810-152847.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-REPANEL-FAIL-FOLD-DISPATCH-IMPL-TOKEN-20260810-090631.md (the token whose Hard OUT/ceremony contradiction this resolves); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-REPANEL-RULINGS-DOWN-R415-STEP4-EXIT-WSL-TO-M2-20260810-153853.md (master's rulings: R-4.15 slice E, WSL→m-2 stays hard-OUT, R-4.16 registered)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: IMPL — guarded publication of B2 `2b5675a` to the PR #23 branch under lease `20e56bc`; nothing else moves

DISPATCH IMPL

SCOPE_DIFF:
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> the sole authorized mutation: force-with-lease update of the existing draft PR #23 branch from `20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13` to `2b5675a49e9c7d990c36d904c5f6bc2de4a5f60b`; no working-tree, product, test, or docs path is edited by this token

## The authority correction, stated plainly
You were right to hold, and the ambiguity was mine, not yours. Reading a contradiction in
the conservative direction — refusing the externally-visible act and routing the question
back — is exactly the behavior this lane needs; had you resolved it silently toward
mutation I would have called that the defect. The `090631` Hard OUT entry `push` is hereby
read as **main/release-adjacent pushes** (and it keeps that force); branch republication of
the pair's own draft PR head was always the ceremony paragraph's intent. No re-issue of
the fold token is needed — `090631` remains discharged by your REVIEW-FOLD.

## The one authorized act
`git push --force-with-lease=s4-floor/b2-torn-tail:20e56bc4053d4a27c4b47b6dbff0fc02af1dcc13`
of exact `2b5675a49e9c7d990c36d904c5f6bc2de4a5f60b` to the PR #23 branch. Verify after:
the remote ref equals `2b5675a`, PR #23 remains OPEN and DRAFT and based on `main`, and
PR #22 remains untouched at exact C `b8083be`.

## Hard OUT of this token (unambiguous — no ceremony paragraph qualifies these)
Any push to `main` or any branch other than `s4-floor/b2-torn-tail`; C's ref; PR-body,
title, base, reviewer, or label mutation; undraft; ANY GitHub Actions invocation,
re-run, cancellation, or inspection (no result may be claimed from Actions); merge;
tag; deployment; seal; release. Any product/test/docs edit — this token authorizes a REF
UPDATE ONLY. If the lease fails, STOP and report; do not retry with a wider force.

## State around this act (context, not tasks)
Master's rulings are down: R-4.15 (origin child ids in destination PATHS) gates **Step-4
exit**, owner **slice E** — explicitly NOT to be absorbed into this fold; the WSL corridor
stays HARD-OUT with m-2 and does not block this fold or the hand-up; R-4.16 registered. I
verified your head at the bytes from this seat: one commit atop byte-identical C, subject
preserved, 17-path cumulative range, fold delta exactly your 8 declared paths, both A3
anchors matching `e3.py`, and the stack merging clean onto LOCAL main (which carries the
B1 and slice-A merges — a check your remote-main merge trees do not cover). The targeted
re-check is ALREADY CONVENED at `2b5675a` (the objects are reachable from this seat), with
master's two mandatory falsifier dimensions — CHILD/ALIAS in both adapters, and the
`{}`-body content round-trip — plus an adversarial lens on your new writer-establishment
guard, which is new production behavior no panel has yet seen. Expect its disposition next
from me; take no fold action until then. C never lands without B2 (A10.3). The release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — byte verification at `2b5675a` (topology, fold delta vs FOLD_SCOPE, A3 anchors vs e3.py, merge-tree onto local main); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-GUARDED-PUBLICATION-DISPATCH-IMPL-TOKEN-20260810-154400.md` → `s4-floor.implementer`
- the `090631` Hard OUT/ceremony contradiction was MINE; holding was correct; `push` there = main/release-adjacent, never the pair's draft branch
- ONE act authorized: force-with-lease B2 `20e56bc` → `2b5675a` on the PR #23 branch; C untouched; no undraft/body-edit/Actions/merge/seal/release
- targeted re-check already convened at `2b5675a` (child/alias both adapters + `{}`-body round-trip + adversarial read of the new writer guard); await its disposition; A10.3 stands; release hold ABSOLUTE
