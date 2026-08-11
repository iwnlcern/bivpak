## SITREP — B2 round-2 is code-approved and blocked ONLY on a stale verification budget: `harness-e2`'s fixed 180s CTest timeout (harness/CMakeLists.txt:47) vs a deterministic ~181.3s all-scenarios-PASS runtime. The budget is OUT-of-universe and a gate constant — routed with a recommendation: grant the one-line raise (180→360). The trend proves this recurs on every future head AND on merged main regardless of B2; an exception-only path fails next week.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-e2-budget
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-resume-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — `harness/CMakeLists.txt` is outside the dispatched universe AND the 180s row budget is a verification-gate constant (the operator's local-green bar under CI-leg (a)); neither the pair nor I may change or waive it
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B2-ROUND2-HOST-E2-TIMEOUT-BLOCKER-20260809-060723.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: ROUTED — the e2 budget disposition; recommend the one-line grant (TIMEOUT 180→360 in harness/CMakeLists.txt, folded into B2's head); narrow exception only as fallback, with its recurrence stated honestly

## What is actually blocked (verified where checkable)
B2's resume fold is COMPLETE and independently approved: the exact image-ID union (incl.
round 2's refused-row alias prepass with a RED→GREEN cross-row falsifier), the
store_root-path rewrite/verify, and Claude staged child-ownership mapping; reviewer verdict
ADDRESSED, no new Critical/Important. Held at local `9977a15` + a two-file unstaged round-2
delta. The ONLY red is the canonical `harness-e2` CTest row: fixed budget `TIMEOUT 180`
(verified at `harness/CMakeLists.txt:46-49`), repeated timeouts at 180.05-180.06s across
the worktree suite, two isolated retries, a FRESH short-path /tmp build, and a cooled
one-shot replay — while the instrumented exact runner completes EVERY row: 11/11 runnable
scenarios PASS, 6 expected XFAIL_PENDING, zero failed/invalid, total 181.312s. This is a
deterministic ~1.3s budget overage with full semantic pass — not a hang, not flakiness, and
the timeout's purpose (catching hangs) is not in play.

## Why this is structural, not a B2 pathology (the trend at the filed reports)
`harness-e2` durations across the Step-4 heads, from the implementers' own filed evidence:
B1 fold head ~160.9s → slice-C head 164.7s → B2 first head 165.6s → B1 merge verification
173.1s → slice-A candidate/merged main 175.05/175.45s → B2 round-2 181.3s. Each slice
legitimately GROWS the scenario battery (C added the consent-no scenarios; B2 adds the
staged/sidecar set; slice E is still to come). Merged main is already at 175.45s WITHOUT
C's and B2's scenarios — after the ratified C→B2 back-to-back merges, main's own canonical
suite will cross 180s regardless of any exception granted to this head. A one-head evidence
exception therefore recurs immediately: next head, and on main itself.

## The scope facts (why this is yours/the operator's, not the pair's)
- The budget lives in `harness/CMakeLists.txt` — NOWHERE in the dispatched universe (the
  plan's harness list is e3.py + scenarios + selftests; only the ROOT `CMakeLists.txt` is
  in, narrowed to "build wiring for the two new units only"). An edit is a universe
  expansion — yours to grant.
- The 180s row budget is a verification-gate constant — under CI-leg (a) the local suite IS
  the merge bar, so its budget is the operator's gate policy; neither the pair nor I will
  change or waive it unilaterally. The implementer held exactly correctly.
- `.github/workflows/s2-harness.yml` invokes ctest and rides the same property — no
  separate workflow timeout to reconcile, and no `.github` edit involved.
- `harness/selftest/test_cmake.py:27` asserts the `harness-e2 PROPERTIES` block exists; a
  TIMEOUT value change does not disturb it.

## Recommendation (and the fallback, stated honestly)
**Recommend: grant `harness/CMakeLists.txt` into the B2 universe for EXACTLY the one-line
property change `TIMEOUT 180` → `TIMEOUT 360`, folded into B2's one-commit head.**
Rationale: the budget exists to catch hangs — a hang manifests as minutes, and 360 still
catches it; 2x headroom absorbs slice E's growth so we are not back here in a week; the
change is one line, riding a head that already owes a third re-panel, so it lands reviewed.
(300 if the operator prefers tighter; the number is the operator's.)
**Fallback (the implementer's option 1): a narrow evidence exception for this amend** —
honest given the all-scenarios-pass diagnostic, but it puts a red canonical row under a
bar-ready candidate's evidence AND recurs on the next head and on merged main, so it should
be paired with a scheduled budget fix even if chosen.

## On the grant (either form), the sequence resumes unchanged
Implementer amends round 2 into the one commit (with the TIMEOUT line if granted), reruns
the focused set + full host suite (now honestly green), runs the standing local Ubuntu
24.04 amd64 Docker suite, republishes PR #23, and I convene the THIRD targeted re-panel
(M-4 under the union scope). R-4.8 and the two disclosed Minors remain separately carried.
Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification (harness/CMakeLists.txt:46-49 TIMEOUT 180; plan universe grep; workflow coupling); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (B2 worktree holds the held two-file round-2 delta; main carries the two local merges); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-E2-BUDGET-STALE-ROUTED-20260809-061403.md` → `s4.orchestrator-planner` (+ operator for the gate constant)
- recommended grant: `harness/CMakeLists.txt` one-line `TIMEOUT 180→360`, folded into B2's head → orchestrator expansion + operator budget disposition
- fallback: narrow evidence exception for this amend → recurs next head and on merged main; pair with a scheduled budget fix if chosen
- B2 held at `9977a15` + two-file round-2 delta (approved, unstaged) → resumes on the disposition; third re-panel after; merge/release the operator's, hold ABSOLUTE
