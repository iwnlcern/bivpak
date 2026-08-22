## IMPL — token issued for the ref-SHA regression guard, parented to the rev1 approval whose verdict I confirmed PARSES before relying on it. Three tests, one file, no production byte. Unlike the date-oracle cycle there is no pre-existing artifact to adopt: nothing has been written yet, so this token authorizes the edit outright

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-impl
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-review-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-REF-SHA-GUARD-R1-APPROVE-LINUX-PREDICATE-SPLIT-DUAL-GATE-20260822-130354.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-GUARD-R1-LINUX-PREDICATE-SPLIT-DUAL-GATE-INLINED-20260822-125850.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-PANEL-PASS-3-NONBLOCKING-CLOSE-REF-SHA-TEST-GAP-BEFORE-STAGE5-20260822-060538.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — `060538` authorized the finding-(3) closure as a bounded in-lane test at my discretion, rev1 is approved, and this token is the pair Planner ceremony that approval releases. It authorizes ONE thing: the three tests in `harness/selftest/test_compare.py` and rev1's proof obligations. Adding them CHANGES T3's head, so the focused re-lens `060538` promised follows. No merge, push, PR mutation, `.github` edit, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted and panel-passed T3 head `d4068684e51f67d0a11fb6d2251178fb2a1a70ea`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL token for the ref-SHA regression guard, parented to the confirmed-parsing rev1 approval; scope is test_compare.py only from 5da5bd33 to a9d0a49f; rev1's O-1a/O-1b/O-2/O-3/O-4 bind in full including the split Linux predicate and the dual restore gate; no production byte and nothing to adopt

DISPATCH IMPL

## 1. Scope

SCOPE_DIFF:
- harness/selftest/test_compare.py -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `harness/selftest/test_compare.py` — the single authorized path. At the authorized pre-edit head `d406868` it is 12163 bytes, SHA-256 `5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43`, re-derived at this seat. rev1 §2 pins the required post-edit state at 13889 bytes, SHA-256 `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`, reproduced independently at both the Planner's and the Implementer's seats from the same three insertion blocks. `git diff --name-only d406868` against the fixed head must return this path and nothing else.

Nothing else is in scope. Explicitly out: `harness/bivharness/compare.py` — findings (1) and (4) are REGISTERED, not fixed, and no production byte moves under this token — plus `fixtures.py`, `scenario.py`, `test_fixtures.py`, every C++ and CMake byte, `.github/`, the schema, T4, and the T1 stage-4 items.

## 2. Lineage, checked rather than assumed

```text
parent approval  s4-matrix-t3-ref-sha-guard-plan-review-r1
  plan_review_approved       True     <- matcher re-validated on a must-be-YES and must-be-NO first
  DISPATCH_ID holders        1        <- no collision; the walk cannot guess
this token's id  s4-matrix-t3-ref-sha-guard-impl
  DISPATCH_ID holders        0        <- fresh
rev1 seal re-derived here before relying on the review's citation:
  commit 762052d, blob 07dc62999621b8f887562262b9968c155e7b415e,
  SHA-256 f372d71f1ea437ae26ba2a0467cb38a26f63e695de6679e6f11f5a4d7a24eee3
```

I check the approve parses now as standing practice, because this lane has twice produced an
approval that read as delivered to every human and returned False to the gate. This one returns
True.

**No adoption question here.** The date-oracle cycle had a candidate commit already sitting on
the branch and I had to decide explicitly what to do with it. Nothing has been written this
time: the branch is at `d406868`, the working tree is clean, and this token authorizes the edit
outright rather than blessing bytes that already exist.

## 3. What is bound

rev1's obligations bind in full and are not restated loosely here — the PLAN is the contract.
The three that carry the most weight:

```text
O-1b  the LINUX predicate is SEPARATE and is NOT an aggregate-green claim.  Pass condition is
      the three new node ids passing explicitly; the aggregate exit and counts are RECORDED
      VERBATIM; every remaining failure is CLASSIFIED against the registered R-4.35 family;
      and it STOPS AND ROUTES if a new node fails or any failure falls outside that family.
      The 3 failed / 993 passed / 3 skipped shape in rev1 is ORIENTATION, explicitly not a gate.
      Do not pin a Linux aggregate count -- R-4.35 membership rotates.

O-2   three must-be-NO controls, each with import sanity BEFORE any verdict is read, each
      mutated BY LINE NUMBER with the token asserted present first (the `extra ref` append
      text occurs twice), and a DUAL restore gate after EACH arm:
        compare.py       == afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4
        test_compare.py  == a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566

O-4   the fixed file must hash to a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566.
      A different digest means the edit is not the planned edit and the cycle STOPS.
```

Any obligation that fails stops the cycle and routes. None may be reconciled into a pass. The
scratch reproductions at my seat and yours de-risk the plan; they discharge nothing — the
durable evidence, both platforms, and the receipts are this cycle's work.

## 4. State

T3's head changes when this lands, so the focused re-lens `060538` promised follows on the new
tests alone; the rest of T3 is panel-cleared and is not reopened. T4 stays HELD. T2 head FINAL
at `7688bbd`. Both T3 heads LOCAL and UNPUBLISHED. R-4.38's binary inventory stays my stage-5
obligation, which must also carry the findings-(1)/(2)/(4) dispositions, the R-4.35 and R-4.40
disclosures, and the three permanent root-mode lineage record-defects (`040750`, `050546`,
T1's `035403`). Schema F+G-fenced. Merge is not push is not release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; the candidate branch is unmoved at `d406868` and the working tree is clean. Read-only verification: `git cat-file -s` and `git show` piped to `shasum` on `harness/selftest/test_compare.py` and `harness/bivharness/compare.py` at `d406868`; `git rev-parse` for the rev1 blob and `git show` for its SHA-256; `DISPATCH_ID` holder counts for the parent approval and this token's id; and a re-validated `plan_review_approved` call on the parent. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob; `--relay-root` run over the lane before commit, required to name no error against this relay, with a one-variable control confirming the lane error set is identical with and without it; the bare token verified present exactly ONCE outside any fence via `operational_token_text` with the detector validated on a must-be-YES and a must-be-NO; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes. Commit gated on all of it by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T3-REF-SHA-GUARD-DISPATCH-20260822-131430.md` → TO `s4-matrix.implementer`
- TOKEN ISSUED, parented to `s4-matrix-t3-ref-sha-guard-plan-review-r1` whose approve I confirmed PARSES (`plan_review_approved` True) with the matcher re-validated on a must-be-YES and a must-be-NO FIRST — standing practice now, because this lane has twice produced an approval that read as delivered to every human and returned False to the gate. Parent id has exactly 1 holder so the walk cannot guess; this token's id `s4-matrix-t3-ref-sha-guard-impl` has 0 holders
- rev1's SEAL RE-DERIVED HERE before relying on the review's citation: commit `762052d`, blob `07dc62999621b8f887562262b9968c155e7b415e`, SHA-256 `f372d71f1ea437ae26ba2a0467cb38a26f63e695de6679e6f11f5a4d7a24eee3` — all three match
- NO ADOPTION QUESTION THIS TIME, unlike the date-oracle cycle: nothing has been written, the branch is at `d406868` with a clean working tree, so this token authorizes the EDIT OUTRIGHT rather than blessing bytes that already exist
- SCOPE is `harness/selftest/test_compare.py` ONLY, from `5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43` at 12163 bytes to `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566` at 13889 bytes. NO production byte moves — findings (1) and (4) are REGISTERED, not fixed — and `compare.py`, `fixtures.py`, `scenario.py`, `test_fixtures.py`, all C++/CMake, `.github/`, the schema, T4 and the T1 stage-4 items are all OUT
- rev1's OBLIGATIONS BIND IN FULL and are not restated loosely — the PLAN is the contract. O-1b's Linux predicate is SEPARATE and is NOT an aggregate-green claim: the three new node ids must pass explicitly, the aggregate exit and counts are RECORDED VERBATIM, every remaining failure is CLASSIFIED against the registered R-4.35 family, and it STOPS AND ROUTES on a new-node failure or any out-of-family failure; the `3 failed / 993 passed / 3 skipped` shape is ORIENTATION and explicitly NOT a gate, and no Linux aggregate count may be pinned because R-4.35 membership rotates
- O-2's three must-be-NO controls each need IMPORT SANITY BEFORE any verdict is read and mutation BY LINE NUMBER with the token asserted present first (the `extra ref` append text occurs TWICE), with the DUAL restore gate after EACH arm on `compare.py` `afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` and `test_compare.py` `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`. O-4's digest gate stops the cycle on any difference. Any failure STOPS and routes; none may be reconciled into a pass
- THE SCRATCH REPRODUCTIONS AT BOTH SEATS DE-RISK THE PLAN AND DISCHARGE NOTHING: the durable evidence, both platforms, and the receipts are this cycle's work
- STATE: T3's head CHANGES when this lands so the focused re-lens `060538` promised follows on the NEW TESTS ALONE, with the rest of T3 panel-cleared and not reopened; T4 HELD; T2 head FINAL at `7688bbd`; both T3 heads LOCAL and UNPUBLISHED; R-4.38 binary inventory my stage-5 obligation, which must also carry the findings-(1)/(2)/(4) dispositions, the R-4.35 and R-4.40 disclosures, and the three permanent root-mode lineage record-defects `040750`, `050546` and T1's `035403`; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
