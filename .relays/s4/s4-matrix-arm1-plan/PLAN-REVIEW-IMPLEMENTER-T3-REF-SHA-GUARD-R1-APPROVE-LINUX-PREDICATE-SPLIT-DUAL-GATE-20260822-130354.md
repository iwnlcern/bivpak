## PLAN-REVIEW — APPROVE: rev1 resolves the Linux aggregate contradiction and makes every mutation restore both governed files

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-GUARD-R1-LINUX-PREDICATE-SPLIT-DUAL-GATE-INLINED-20260822-125850.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-REF-SHA-GUARD-MUST-REVISE-LINUX-AGGREGATE-CONTRACT-20260822-124939.md; .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-CROSSED-PLAN-FILED-TWO-DIVERGENCES-FLAGGED-20260822-123504.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate; this approval grants no source keyboard authority. A later separate literal implementation token parented to this exact approval remains required before any candidate byte changes. Release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed rev1 commit 762052db9d5dfd112e97b0c3f92a8356550a1734, blob 07dc62999621b8f887562262b9968c155e7b415e, SHA-256 f372d71f1ea437ae26ba2a0467cb38a26f63e695de6679e6f11f5a4d7a24eee3; accepted T3 remains d4068684e51f67d0a11fb6d2251178fb2a1a70ea
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE rev1; Linux is three-node candidate green with exact aggregate and R-4.35 classification, macOS remains exactly 1000 green, and both governed files restore after every mutation

Rev1 resolves both requirements from review-r0 without changing the accepted test design.
The rev0-to-rev1 diff changes the review lineage, adds the explicit MF-1 acceptance, splits O-1
into platform-specific predicates, and inlines the two-file restore gate in O-2. The three test
insertions, unique anchors, before and target digests, twin-surface widening, negative controls,
one-file fence, and findings (1), (2), and (4) dispositions remain unchanged.

## MF-1 closed — Linux is not represented as aggregate green

O-1a binds macOS to a full `harness/selftest` result of exactly 1000 passed and also requires
the three new node IDs to be recorded explicitly as passed. O-1b is a separate Linux predicate
under the already-bound Ubuntu 24.04 linux/amd64 container topology. Its candidate-owned success
condition is that all three new node IDs pass. It requires the exact aggregate exit status and
counts to be recorded verbatim and every remaining failure to be classified against the registered
R-4.35 E3 scandir and TOCTOU family. Any new-node failure or any failure outside that family stops
and routes. The orientation count is explicitly non-normative, so the PLAN neither pins a rotating
Linux total nor launders a non-green aggregate into a whole-suite-green claim.

## Crossed dual restore gate closed

O-2 now stands alone: after EACH of the three scratch mutations, the runner must restore and gate
both `harness/bivharness/compare.py` at SHA-256
`afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` and
`harness/selftest/test_compare.py` at SHA-256
`a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`
before continuing. The proof no longer depends on the report-only crossed note for a load-bearing
restore condition.

## Accepted implementation contract

- edit only `harness/selftest/test_compare.py` from SHA-256 `5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43`, 12163 bytes, to SHA-256 `a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`, 13889 bytes
- retain two isolated `compare_trees` tests for divergent common-ref SHA and unexpected restored ref, plus the measured divergent-SHA twin for `assert_repo_state`
- require all three exact mutation controls to produce the intended single failed node with successful import and no collection error, restoring and hashing both governed files after each arm
- keep `compare.py`, fixtures, scenario bytes, C++, CMake, workflows, schema, T4, refs, and remotes outside the implementation fence
- register findings (1) and (4), retain finding (2) as informational, and make no production widening

The earlier independent archive reproduction remains applicable because the proposed insertion
blocks and target digest are unchanged: `test_compare.py` reached 31 passed, full macOS selftest
reached 1000 passed, and each of the three production-branch neuters made its matching exact node
fail once without collection or import error. This review adds no claim that those scratch results
discharge the later platform and durable-evidence obligations.

No candidate source, test, workflow, branch, ref, container, or remote state changed in this
review. T3 remains clean, local, and unpublished at `d406868`; T4 remains held. No remote CI,
push, PR mutation, merge, publication, schema act, deployment, or release occurred.

ACTIONS_GIT_REF: review-only exact-byte comparison of rev1 against rev0 and review-r0; rev1 commit, blob, SHA-256, size, parent, headers, authority, and lineage verified; accepted insertion blocks and digests confirmed unchanged; candidate T3 worktree verified clean at d406868. This review plus one live-EOF INDEX row ride one explicit-path docs-lane commit
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint compared against the inherited 10-error baseline and required to add none; root mode required to name no error against this review; approval matcher and no-token checks required; cached diff and explicit two-path commit fail-fast; post-commit historical exact-file verification
FINAL_GIT_STATUS_SHORT: T3 worktree clean at d406868; shared docs checkout retains sibling-authored untracked paths, preserved and unclaimed; only this review and its single INDEX append are claimed

CARRY LIST:
- VERDICT approve; rev1 closes review-r0 MF-1 and the self-contained dual restore requirement
- accepted test contract and exact target bytes unchanged; three isolated nodes and three exact negative controls remain required
- macOS exact 1000 plus explicit new-node passes; Linux explicit new-node passes plus exact aggregate and R-4.35 classification, never aggregate-green wording
- restore and hash compare.py plus test_compare.py after every mutation arm
- no implementation authority in this review; await the separate literal token parented to this approval
- T3 unchanged at d406868; T4 held; no remote or integration authority or act; release hold ABSOLUTE
