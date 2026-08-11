## DISPATCH (re-stack) — THE HAND-UP WAS REFUSED AND THE ERROR IS MINE. I verified the stack "merges clean at every hop including onto LOCAL main" — but LOCAL main does not contain R-4.8, and the PRs' base is `origin/main` (`38a4702`), which does. R-4.8 is a 275-file landing that modified `src/core/open/sessions.cpp` and four of the test files this fold also touched, so **both C and B2 CONFLICT into their real merge target.** I even used `origin/main` for the blast radius while using local `main` for the merge check — that inconsistency is the whole defect, and it is mine, not yours. **Re-stack C then B2 onto `38a4702`.** Note what is different this time: **C itself must move** (`sessions.cpp` is C's file and it conflicts), so C — byte-identical since its own panel — gets a new SHA, and **both PR branches need republication, which my `154400` token never authorized. §6 authorizes both explicitly so you are not blocked on my omission twice.**

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-restack-post-r48
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — a re-stack under delegated pair authority. Downstream gates unchanged: re-run the combined re-check, fresh paired hand-up, master's condition-3, the operator's paired condition-4, the ABSOLUTE release hold.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 shape unchanged by the re-stack; if R-4.8's landed bytes turn out to move the A9 contract, STOP and route — do not reconcile a sealed contract in a merge conflict)
IN_REPLY_TO: .relays/s4/s4-floor-impl/MERGE-GATE-ORCHESTRATOR-PLANNER-CB2-HANDUP-REFUSED-STACK-CONFLICTS-ORIGIN-MAIN-RESTACK-OWED-20260810-235506.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-3762f37-PANELED.md (the paneled-pair baseline I captured for your carry adjudication); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-combined-recheck-3762f37.md (the PASS verdict those bytes carry)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: RE-STACK — C and B2 onto post-R-4.8 `origin/main` `38a4702`; reconcile per hunk, do not take a side wholesale; both branches authorized for republication

DISPATCH IMPL

SCOPE_DIFF:
- src/core/open/sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- .git/refs/remotes/origin/s4-floor/c-consent-no-carrier -> in
- .git/refs/remotes/origin/s4-floor/b2-torn-tail -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/open/sessions.cpp -> conflicts with R-4.8; C's file, so C's own head moves
- tests/test_adapter_claude_install.cpp -> conflicts (R-4.8 +410 lines vs the fold's re-targeted assertions)
- tests/test_adapter_codex_install.cpp -> conflicts (R-4.8 +527 lines); conflicts on BOTH C and B2
- tests/test_pack.cpp -> conflicts (R-4.8 +341 lines vs the acceptance instrument and round-trip cases)
- tests/test_sessions.cpp -> conflicts (R-4.8 +443 lines vs the identity-map and caveat assertions); on BOTH C and B2
- .git/refs/.../c-consent-no-carrier -> republication of C's new head (PR #22), lease = current remote head
- .git/refs/.../b2-torn-tail -> republication of B2's new head (PR #23), lease = current remote head
Any file NOT listed must come out of the re-stack byte-identical to its `3762f37` value in the baseline; if
the merge moves one that is not listed, STOP and report before resolving it.

## 1. The task
Re-stack **C first, then B2 atop the new C**, onto `origin/main = 38a4702`. Rebase or merge-in as you judge
best, but the end state must be: C one commit on `38a4702` with its subject preserved
(`feat(open): stage consent-no sessions with provenance sidecar`), and B2 one commit atop the new C with its
subject preserved (`feat(pack): collect torn tails and staged sidecars`).

## 2. Conflict resolution — the trap to avoid
R-4.8 added 341–527 lines to each conflicting test file while the fold re-targeted assertions in the same
regions. **The temptation in a conflict that large is to take one side wholesale. Do not.** Taking "ours"
silently deletes R-4.8's new coverage; taking "theirs" silently reverts the option-(a) re-targeting and
resurrects assertions that are now the OPPOSITE of ratified behaviour. **Reconcile per hunk**, and in your
report state, for each of the five files, what each side contributed and how you know nothing was dropped —
a line count is not that evidence; name the cases from each side that survive. If any hunk cannot be
reconciled without a judgement about which behaviour is correct, STOP and route it to me rather than
choosing.
**Specifically re-verify after resolution:** the `[.pending-r415]` markers stay gone; no assertion asserting
the alias is ABSENT comes back; `IdMapEntry.children` identity assertions survive; the acceptance instrument
(`test_pack.cpp`, the three-layout stage→pack→open case) survives intact with all three fixture classes.

## 3. Verify the merge target — the check I got wrong
```
git merge-tree --write-tree --name-only origin/main <new-C>   -> MUST exit 0
git merge-tree --write-tree --name-only origin/main <new-B2>  -> MUST exit 0
git merge-base --is-ancestor 38a4702 <new-C>                  -> MUST be true
```
Use `origin/main`, not local `main` — local `main` is 139 commits ahead on the docs lane and 9 behind on
product, so it is not the merge target and never was. Report the exit codes.

## 4. Carry adjudication — against the baseline I captured for you
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-endstate-baseline-3762f37-PANELED.md`
holds the per-file end-state hashes of the PANELED pair over the union of C's and B2's deltas (34 rows).
At the re-stacked heads: a file whose end-state bytes hash-match **carries the combined re-check PASS**; a
file that differs needs **FRESH review**. The five conflict files are pre-marked and will certainly be
fresh; report the full table so the count is evidence rather than assertion.

## 5. Re-verification owed at the re-stacked heads
The re-stacked tree now CONTAINS R-4.8's 275-file landing, so prior suite evidence does not transfer:
full macOS suite and the bounded Ubuntu 24.04 `linux/amd64` Docker parity, both at the exact new SHAs, with
the standing disclosed exception classes. A3 both-anchor re-fire **if** R-4.8 moved either anchored collector
or your resolution did — check and say either way. Re-measure the blast radius as
`git rev-list --count origin/main..<new-B2>^` and report the number (it will differ from 27).

## 6. Publication — BOTH branches, explicitly (closing my own omission)
My `154400` token authorized the B2 draft branch only. C's head moves this time, so that token does not
cover it and you would be right to hold. **Authorized here, same narrow terms, one act each:**
```
git push --force-with-lease=s4-floor/c-consent-no-carrier:b8083be8529a97d1d3d5931a2c7b308335bbd09c \
    origin <new-C>:s4-floor/c-consent-no-carrier
git push --force-with-lease=s4-floor/b2-torn-tail:3762f3722a1fcebfbaa25921c31ca2f10df4ddf4 \
    origin <new-B2>:s4-floor/b2-torn-tail
```
Verify after: both PRs remain OPEN, DRAFT, based on `main`, at the exact new heads. **Hard OUT and
unqualified by any sentence elsewhere:** any other branch or `main`; PR body/title/base/label/reviewer
mutation; undraft; ANY GitHub Actions invocation, re-run, or inspection; merge; tag; deploy; seal; release.
Lease failure ⇒ STOP and report; never a wider force.

## 7. What survives, so it is not re-earned
For files whose end-state bytes are unchanged: the option-(a) logic (`child_ids` identity, alias-arm
removal, A9-safety), the acceptance instrument's genuineness, the contained-side intactness, and the routed
items (E-1/E-2/E-3 → slice E, R-a → residual). **The struck convener-error line stays struck** — do not
resurrect the `staged_path_caveats` "proof"; its premise was false. R-4.18 one-level-consistency still binds:
do not let a merge resolution introduce recursion, a root-mapped comparison, or a three-level-leaf warning.

## Return
REVIEW-FOLD with the new SHAs, the five-file reconciliation evidence (§2), the three merge-target exit codes
(§3), the full carry table (§4), suite + Docker evidence at the new heads, the A3 determination, the
re-measured blast radius, and the publication receipts. Then I re-run the combined re-check scoped to the
FRESH files and file a fresh paired hand-up. C never lands without B2 (A10.3). `231437` WITHDRAWN;
merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — reproduction of the orchestrator's conflict finding against `origin/main` (both heads, exit 1, files named), `git merge-base --is-ancestor 38a4702 main` false, R-4.8's 275-file delta inspected, divergence measured (139 ahead / 9 behind), and the paneled-pair baseline captured and committed; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay, the reviews/ baseline, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RESTACK-ONTO-POST-R48-ORIGIN-MAIN-DISPATCH-IMPL-TOKEN-20260810-235910.md` → `s4-floor.implementer`
- MY ERROR: the merge-clean leg tested LOCAL main (no R-4.8) while the blast radius used `origin/main` — the PRs' base is `origin/main` `38a4702`; both heads CONFLICT there on `sessions.cpp` + 4 test files
- RE-STACK C then B2 onto `38a4702`; C ITSELF MOVES (sessions.cpp is C's); reconcile PER HUNK — taking either side wholesale drops R-4.8 coverage or resurrects pre-ratification assertions; STOP-and-route any hunk needing a correctness judgement
- verify with `git merge-tree --write-tree origin/main <head>` exit 0 (NOT local main); carry-adjudicate against the captured 34-row baseline; re-run full macOS + Docker at the new SHAs; A3 if anchors moved; re-measure blast radius
- BOTH branches authorized for republication (§6) — my `154400` covered B2 only; same narrow terms, leases named; release hold ABSOLUTE
