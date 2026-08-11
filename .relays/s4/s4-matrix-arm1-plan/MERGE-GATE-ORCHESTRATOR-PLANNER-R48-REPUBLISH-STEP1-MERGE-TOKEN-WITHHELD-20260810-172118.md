## MERGE-GATE (carry-down, STEP 1 of a HARD SEQUENCE) — the OPERATOR GRANTED BOTH, ORDER-BOUND: the P5 REPUBLICATION of the reviewed head `0ab998d` to PR #24, and the condition-4 MERGE authorization for PR #24 at `0ab998d`. But the ordering is a HARD SEQUENCE: **REPUBLISH → VERIFY the published head is `0ab998d` byte-exact → THEN MERGE.** This relay carries you STEP 1 (the republish) ONLY — **the condition-4 merge token is WITHHELD and rides NO relay yet; I issue it to the implementer in a SEPARATE relay AFTER the published head verifies at `0ab998d` at my seat.** Merging the currently-published `2341667` would land the exact test bytes this review window FAILED — which is the whole reason the sequence exists. I re-verified at my seat: branch tip still `0ab998d`, published head still stale at `2341667`, merge-tree into current `origin/main` CLEAN. Merge ≠ release — the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-matrix-r48-republish-then-merge
PARENT_DISPATCH_ID: s4-matrix-r48-merge-handup
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-REPUBLISH-AND-MERGE-GRANTED-ORDER-BOUND-20260810-171659.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: the operator's grants are DISCHARGED (P5 republication + condition-4, order-bound); this relay carries only STEP 1 (republish). The merge token is withheld pending the published-head verification. The release hold is ABSOLUTE (merge ≠ release), and the local-main publication-timing question is a SEPARATE open operator item this does not touch.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: MERGE-GATE — republish 0ab998d to PR #24 (STEP 1); report the published head; the merge token follows separately ONLY on published==reviewed

## The hard sequence (do NOT collapse it)

```text
STEP 1  REPUBLISH   push 0ab998d to PR #24. Re-verify the branch tip AT EXECUTION;
                    a moved tip STOPS and routes up — a new tip is a new review, not a push target.
STEP 2  VERIFY      git ls-remote + gh pr view 24 → published head MUST equal
                    0ab998d8431a20de80b8d769fb82c1350ed0728d, byte-exact. Report it UP to me.
STEP 3  MERGE       WITHHELD here. On my independent re-verification that published==0ab998d, I issue the
                    bare condition-4 token to you (the matrix implementer) in a SEPARATE relay. Only then do
                    you merge PR #24 into main, re-verifying clean at the ACTUAL merge tip (main is docs-lane
                    advancing); any surprise conflict STOPS and routes up.
STEP 4  REPORT      route the published ref + the landed merge commit SHA UP for condition-3-of-record closure.
```

**Hard stop:** if the republication does not land, or lands at any OID other than `0ab998d`, the merge
authorization DOES NOT ACTIVATE — STOP and route up. The authorization is bound to the reviewed head AND to
the published-head-equals-reviewed-head precondition, not to "PR #24" as a moving target.

## Carry-time re-verification (at my seat, this pass)

```text
branch tip        0ab998d8431a20de80b8d769fb82c1350ed0728d  == reviewed head        ✓
published head    2341667…                                   (still stale — republish genuinely owed)  ✓
origin/main       8981bfd0… (docs-lane advanced past master's 0e401a36 carry-time read)
merge-tree        origin/main ← 0ab998d  CLEAN (no conflict markers)  ✓
conditions        1+2 (panel/lenses+CC) · 3 (end-state-bytes DISJOINT, master 165050) · 4 (operator grant, order-bound)
```

## What this does NOT do

No condition-4 token rides this relay — I am withholding it by design until STEP 2 verifies, exactly so a
stale-head merge is impossible. Not a release (the hold is ABSOLUTE). Not the local-`main` publication
decision (the operator's separate open item). Not a C/B2 act (that pair is mid-fold under its own token;
`231437` stays WITHDRAWN). The two aggregate items (harness probe flake OPEN, `harness-e2` stale ceiling)
stay OPEN after the merge and are not this branch's debt; INFO-3 stands — the byte-identity receipts are
fixture non-vacuity guards, and nothing about this merge converts them into a behavioral pin (that arrives at
the needle head, R-4.10/R-4.11).

ACTIONS_GIT_REF: no product/test edits at this seat — carry-time re-verification only (git rev-parse s4-matrix/r48-carrier == 0ab998d; git ls-remote published head == 2341667 stale; merge-tree origin/main ← 0ab998d clean) + this relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. The push and the eventual merge are your acts under the operator's grants; I push nothing and merge nothing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Expected `--index` reds: the R-4.8 design/plan path-style-lock false-reds (relay-lint.py:1639; referents exist at repo-root) + the line-222 sibling inversion — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-REPUBLISH-STEP1-MERGE-TOKEN-WITHHELD-20260810-172118.md` → `s4-matrix.planner`
- operator granted BOTH order-bound (P5 republish 0ab998d + condition-4 merge at 0ab998d); this relay = STEP 1 republish only
- REPUBLISH 0ab998d to PR #24 (re-verify tip at execution, moved → STOP), VERIFY published==0ab998d byte-exact, REPORT the published head UP
- the condition-4 merge token is WITHHELD — I issue it separately ONLY on published==reviewed at my seat; a stale-2341667 merge would land the failed test bytes → hard stop + route up
- merge ≠ release (hold ABSOLUTE); local-main timing separate; C/B2 231437 WITHDRAWN; aggregate items OPEN not this branch's debt; INFO-3 receipts are fixture-non-vacuity not a behavioral pin
