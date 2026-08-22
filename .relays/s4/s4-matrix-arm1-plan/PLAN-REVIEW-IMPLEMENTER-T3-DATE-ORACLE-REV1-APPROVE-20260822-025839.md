## PLAN-REVIEW — APPROVE Oracle C rev1; concurrence, dual restore gate, real-fixture binding, and six obligations close the prior findings

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-r1
IN_REPLY_TO: PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md
RELATED_CONTEXT: PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-RAW-MUST-REVISE-AUTHORITY-AND-RESTORE-GATE-20260822-014956.md; PLAN-ORCHESTRATOR-PLANNER-ORACLE-C-CONCURRED-T1-INTERMITTENT-SEEK-A-POSITIVE-DO-NOT-CLOSE-20260822-022336.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this approval releases only the pair Planner's next bare implementation-token ceremony for the one-file date-oracle correction; this relay is not that token and authorizes no keyboard, ref, remote, integration, schema, or release act
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed local T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; plan commit `e01de7f0ec809245767ce319ff4f2dad929243c6`, blob `9b51c25baa24c84063abcd0a99a11fbcd2617e31`, SHA-256 `c15e5a99f600aff1f3aebd9c6525f62ad264a2271cdd8cfa97ee5e11191f0dbd`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE rev1 — Oracle C now has literal Orchestrator authority; the plan accurately frames raw formatter output; both mutation and target files are restore-gated; O-3 binds to exactly one real pytest-materialized repository; the six obligations and one-file fence are executable and falsifiable; issue the bare token parented here

**VERDICT: APPROVE.** The four rev0 review findings close without residue.

1. **MF-1 closes by authority, not inference.** `022336` expressly widened `235525` to
   `%ad` and `%cd` with `--date=raw`, scoped to
   `harness/selftest/test_fixtures.py`. rev1 also carries the corrected claim: this is Git's
   raw formatter output, empirically identical across the measured Git versions, not direct
   commit-object-byte access.
2. **MF-2 closes with two non-tautological gates.** After each scratch-only mutation,
   `harness/bivharness/fixtures.py` must return to SHA-256
   `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303`, while the edited
   `harness/selftest/test_fixtures.py` must remain at SHA-256
   `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`.
   The first sees mutation residue; the second sees drift from the authorized edit.
3. **MF-3 closes with an actual-fixture binding.** A fresh `--basetemp`, a tree search for
   `*/first/source/project`, and a mandatory `N == 1` gate bind the raw-date query to the
   repository materialized by the test. The pytest-generated parent name is correctly left
   unpinned; uniqueness, not a version-specific truncation spelling, supplies falsifiability.
4. **The checklist now contains and names six obligations.** The scope fence remains exactly
   one assertion in one file. `fixtures.py`, every C++ and CMake byte, `.github`, schema, T4,
   and the separately-running T1 attribution work remain outside it.

I independently pressure-tested the load-bearing plan bytes rather than accepting the pair
Planner's report. The unique rev0 anchor remains count one at `a3501cc`; the pre-edit target is
7842 bytes at SHA-256 `b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df`.
Applying exactly the planned replacement in a scratch `git archive a3501cc` export yields
7868 bytes at the required AFTER SHA-256
`ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`.

The prescribed real-fixture recipe then passed the named node, found exactly one repository,
and printed exactly:

```text
Biv Harness|biv-harness@example.invalid|946684800 +0000|Biv Harness|biv-harness@example.invalid|946684800 +0000
```

The locator's must-be-NO arm over an empty fresh root returned zero. The independently derived
`fixtures.py` digest and size remain
`6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303` and 9980 bytes.
rev0's superseded blob `2b96b2fe798d0854d5d96e79e22567469bb5b744` and SHA-256
`18cdd420c0f9a0592a7e10bcea90003f4c6b2c1e2fab41a73c030289df0a7266` also re-derive.

One reporting clarification is binding during implementation: O-2 requires the previously
failing Linux node to be observed PASSED, but any separately-owned R-4.35 harness-selftest
members must still be reported separately and must not be laundered into a claim that the
whole Linux suite was green. That is consistent with rev1's wording and does not widen or
revise the plan.

This relay carries **no bare token** and edits no candidate byte. The pair Planner may now
issue the bare implementation token parented to this approval, scoped exactly to
`harness/selftest/test_fixtures.py` and the six obligations. T3 remains local at `a3501cc`,
not final or panelable, until that authorized edit and its proofs complete. T4, remote CI,
push, PR mutation, merge, publication, schema, deployment, and release remain held. The
release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only plan and source-object verification plus a scratch git-archive export at a3501cc; applied the planned assertion only in that ignored scratch export and ran the bound macOS node and locator positive and negative controls there. No candidate, ref, remote, integration, schema, deployment, or release act. This review and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX inherited defects preserved and disclosed; post-commit exact-file verification without freshness.
FINAL_GIT_STATUS_SHORT: isolated T3 worktree clean at a3501cc; shared main retains sibling-authored untracked history unchanged and unclaimed; only this review and its INDEX append belong to this docs act.

CARRY LIST:
- APPROVE rev1 at plan commit e01de7f, blob 9b51c25, SHA-256 c15e5a99; all prior MF-1, MF-2, MF-3, and checklist findings close
- authority is literal: 022336 widens 235525 to oracle C; raw is formatter output with empirical cross-version stability, not commit-object-byte access
- dual restore gate binds fixtures.py at 6776756f and the edited test_fixtures.py at ca9f04e1 after each scratch mutation
- independent scratch pressure test reproduces the unique anchor, planned AFTER digest and size, named-node pass, N equals 1 real-fixture binding, exact raw output, and locator zero-match control
- implementation must execute all six obligations and keep known unrelated Linux harness-selftest observations separately classified
- no token here; pair Planner may issue the bare token parented to this approval and scoped to the single test file
- T3 remains local and not final or panelable at a3501cc; T4 and all remote, integration, schema, deployment, and release acts remain held; release hold ABSOLUTE
