## DISPOSITION — the e2-budget catch is right and the implementer held exactly correctly. I GRANT the narrow universe expansion (mine): `harness/CMakeLists.txt` is in B2's universe for EXACTLY the one-line `harness-e2` `TIMEOUT` property, nothing else in that file, folded into B2's one-commit head. The VALUE (360 recommended / 300 / narrow exception) is the operator's gate policy — routed UP (`061811`). HOLD the amend until the operator's ruling; then fold at the granted value (or take the exception if the operator elects it) and the sequence resumes. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-impl-2-b2-e2-budget-disp
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-e2-budget
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay for the universe expansion (mine, granted below); YES upstream for the value — the TIMEOUT budget is the operator's gate policy under CI-leg (a), routed up; the pair holds the amend until the operator rules; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-PLANNER-B2-E2-BUDGET-STALE-ROUTED-20260809-061403.md
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — e2-budget: narrow universe expansion granted (TIMEOUT line only); value routed to the operator; hold the amend

## The catch is right; the hold was right

B2 round-2 is code-approved and blocked solely on the canonical `harness-e2` CTest row: fixed
`TIMEOUT 180` vs a deterministic all-scenarios-PASS runtime of 181.3s. The implementer holding rather
than touching an out-of-universe gate constant was exactly correct. I re-verified your load-bearing
claims at the bytes before disposing:
- `set_tests_properties(harness-e2 PROPERTIES TIMEOUT 180)` at `harness/CMakeLists.txt:46-47`;
- `harness/selftest/test_cmake.py:27` asserts `"harness-e2 PROPERTIES"` EXISTS (structural) — it does
  NOT pin the value, so a raise passes it (contrast the sibling assert that pins `safety-tidy-analyzer
  … TIMEOUT 600`);
- `s2-harness.yml:53` runs `harness-e2` via the CTest preset with NO `timeout-minutes` / `--timeout`
  override — the workflow inherits the CMake property, so **no `.github` edit is involved** (we stay
  hard-OUT of it);
- the raise is a gate-CORRECTNESS refresh, not a control disable — a genuine hang is minute-scale and
  360 still catches it.

## What I grant (mine) — the narrow universe expansion

`harness/CMakeLists.txt` is admitted into B2's universe for **EXACTLY the one-line `harness-e2`
`TIMEOUT` property change, nothing else in that file**, folded into B2's one-commit head. This is the
narrowest expansion that satisfies the mechanism; do not touch any other line, target, or property in
that file under this grant.

## What is the operator's (routed) — the value

The budget VALUE is a verification-gate constant that, under CI-leg (a), defines "local-green" = the
merge bar; that is the operator's gate policy, not mine to set. I routed it UP (`061811`) with the
structural case: merged `main` is already 175.45s WITHOUT C's and B2's scenarios, so after the ratified
C→B2 merges it crosses 180s regardless — a one-head exception recurs immediately. I recommended a
**durable raise to `TIMEOUT 360`** (300 if the operator prefers tighter), with the narrow evidence
exception as the fallback. **HOLD the amend until the operator's ruling.**

## On the ruling, the sequence resumes unchanged

- If RAISE: fold the one-line `TIMEOUT 180 → <operator's value>` into B2's single commit alongside the
  round-2 delta.
- If EXCEPTION: no file edit; carry the disclosed red canonical row as a recorded evidence exception
  (and note it recurs — pair it with the scheduled budget fix the operator directs).
- Either way: rerun the focused set + full host suite (now honestly green) + the standing local Ubuntu
  24.04 amd64 Docker suite, republish PR #23, and I convene the THIRD targeted re-panel (M-4 under the
  union scope). R-4.8 and the two disclosed Minors remain separately carried; do not fold them here.

Merge/release the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte verification (harness/CMakeLists.txt:46-47, test_cmake.py:27, s2-harness.yml:53). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (B2 worktree holds the held round-2 delta; main carries the two local merges); this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-B2-E2-BUDGET-UNIVERSE-GRANTED-VALUE-ROUTED-20260809-061951.md` → `s4-floor.planner`
- universe expansion GRANTED: harness/CMakeLists.txt, harness-e2 TIMEOUT line ONLY, nothing else, into B2's head
- value (360 rec / 300 / exception) → operator gate-policy, routed UP `061811`; HOLD the amend until the ruling
- on the ruling: amend one commit, rerun focused+host+Docker, republish PR #23, I convene the THIRD re-panel (M-4 union scope)
- R-4.8 + two disclosed Minors → separately carried; not folded here
