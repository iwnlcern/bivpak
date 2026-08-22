## PLAN-REVIEW — MUST REVISE: the three-test design, twin widening, target bytes, and all discriminators pass review; O-1 alone contradicts the standing Linux aggregate ruling and needs one precise rewrite

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: MUST REVISE
DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan-review-r0
PARENT_DISPATCH_ID: s4-matrix-t3-ref-sha-guard-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-REF-SHA-REGRESSION-GUARD-CLASS-COMPLETED-20260822-062355.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-CROSSED-PLAN-FILED-TWO-DIVERGENCES-FLAGGED-20260822-123504.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T3-PANEL-PASS-REF-SHA-TEST-CHOSEN-BOUNDED-PLAN-TOKEN-AWAITED-20260822-061758.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate; pair Planner rev1 must make the Linux aggregate contract internally consistent and carry the crossed-note dual restore gate into the PLAN itself, then a fresh Implementer PLAN-REVIEW and separate literal implementation token remain required. No source keyboard authority here; release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed PLAN commit 721bc2e057b609762cfd93768d61cb86f60947f5, blob 5b460f211bcfd42cb945542d706a7020ad789593, SHA-256 de6cb12ea7f7155cc957f918c9a0d87039e7d2bf2923461cfb87450f818827c7; accepted T3 remains d4068684e51f67d0a11fb6d2251178fb2a1a70ea
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE only O-1 Linux success wording and make the crossed dual restore gate self-contained; approve two isolated repo-semantic tests, the assert_repo_state twin widening, exact target digest, three must-fail controls, and findings 1 2 4 dispositions

The technical design is sound. I independently applied the PLAN's three exact insertions to a
fresh `git archive d406868` export. The before file reproduces at 12163 bytes and SHA-256
`5da5bd335f5b401676b54c24ff591b1ce4eb007ab9d2327218cade8a0c04ba43`; the proposed file
reproduces at 13889 bytes and SHA-256
`a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`. On macOS,
`test_compare.py` is 31 passed and the full selftest is 1000 passed.

## Accepted design decisions

**Divergence A — two tests: accepted.** The restored divergent-SHA mutation and the unexpected
ref mutation are independent contracts and exercise separate branches. The earlier combined
shape imported the load-bearing-composition standard from a test whose purpose was interaction;
there is no interaction to prove here. Separate nodes give the sharper failure identity at
negligible cost.

**Divergence B — the `assert_repo_state` twin: accepted.** Direct read confirms the existing
test covers HEAD mismatch and missing ref but never asserts a same-name ref with a different
object ID. `assert_repo_state` and `_compare_repo_semantics` expose the same carried-ref
integrity contract. Adding the third test completes the measured two-instance class without
widening beyond `test_compare.py` or changing production code.

**The three tests discriminate.** In independent scratch copies I neutered the intended
production branch only after confirming its exact line token, imported `bivharness.compare`
successfully, and ran the matching node:

```text
common-ref SHA comparison disabled       divergent-SHA compare_trees node     1 failed, exit 1
extra-ref append at compare.py:234       extra-restored-ref node              1 failed, exit 1
assert_repo_state SHA comparison disabled divergent-SHA expectation node      1 failed, exit 1
```

None reported a collection or import error. After each, `compare.py` restored to d406868
SHA-256 `afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` and
`test_compare.py` remained at proposed SHA-256
`a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566`.

Findings (1), (2), and (4) dispositions are accepted: register the visibly over-strict
additive-root asymmetry rather than soften a detector; retain the Hostile-User assertion as
informational beside discriminating sibling coverage; register and route the measured gitlink
trust-boundary/vacuous-semantic-check policy question rather than invent policy in T3.

## MF-1 — O-1 has mutually exclusive Linux success conditions

O-1 begins:

> MUST-BE-YES both platforms at the fixed head: python3 -m pytest harness/selftest -q GREEN
> and the count is 1000

It then correctly says the registered R-4.35 Linux members must be reported separately and
never laundered into a whole-suite-green claim. Both cannot govern the same Linux run. At
`d406868`, the accepted Linux aggregate is 3 failed / 990 passed / 3 skipped, and adding these
three passing nodes does not make that aggregate green or yield 1000 Linux passes. The
`060126` ruling explicitly defines the bar as candidate surface green plus the fix target green
on both hosts, with registered candidate-neutral residuals disclosed rather than converted to
either a pass or a blocker.

Rev1 must split the platform predicates explicitly:

```text
macOS   full harness/selftest GREEN at exactly 1000 passed; all three new node IDs PASSED
Linux   run the full harness/selftest under the bound container topology; all three new node
        IDs must PASS explicitly. Record the exact aggregate exit/count and classify only the
        already-registered R-4.35 family separately; never claim the whole Linux suite green.
STOP    any new node fails, or any Linux failure falls outside the registered R-4.35 family
```

Do not pin a Linux aggregate pass count: platform skips and rotating R-4.35 membership make
that neither the candidate-owned oracle nor a stable contract. Pin the three new node IDs and
the allowed residual family instead.

## Required self-contained carry from the crossed note

The `123504` crossed-note accepts my dual restore-gate phrasing, but the artifact under review
still says only `compare.py` must restore after each mutation and leaves the test target to a
separate final digest obligation. Rev1 should put the adopted rule in O-2 itself: after EACH
scratch mutation, gate BOTH `compare.py` at
`afda520510161b353ead3bb596e5b26bf249866bc593b6632a20f7436cfe1aa4` and
`test_compare.py` at
`a9d0a49fce30623c12e9be5520da717f9f62abebde8cc2d9cca7e62569217566` before continuing.
That makes the reviewed PLAN self-contained and prevents the token from depending on a
report-only side amendment for a proof obligation.

No candidate source, test, workflow, branch, ref, container, or durable evidence root changed
in this review. All proposed edits and negative controls occurred in throwaway archive copies.
T3 remains accepted, clean, local, and unpublished at `d406868`; T4 remains held pending this
optional test cycle. No remote CI, push, PR mutation, merge, publication, schema act,
deployment, or release occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: review-only verification of the exact 062355 PLAN and 123504 crossed note; fresh git archive d406868 scratch application of all three proposed insertions; target digest and size reproduction; macOS test_compare.py 31 passed and harness/selftest 1000 passed; three independent scratch mutation controls with import sanity and exactly one failed node each; dual restore digest measurement. No candidate source/test/worktree/ref/container/remote/integration act. This review plus one live-EOF INDEX row ride one explicit-path docs-lane commit
RELAY_LINT: exact-file with freshness; live INDEX EOF immediately re-read before append; full INDEX lint compared against the pre-append 10-error inherited baseline and required to add none; root mode required to name no error against this review; cached diff check and explicit two-path commit are fail-fast gates; post-commit historical exact-file verification
FINAL_GIT_STATUS_SHORT: T3 worktree clean at d406868; shared docs checkout retains sibling-authored untracked paths, preserved and unclaimed; only this review and its single INDEX append are claimed

CARRY LIST:
- VERDICT MUST REVISE; no implementation token may parent to this review
- accepted: two isolated compare_trees tests, assert_repo_state twin widening, exact a9d0a49f target, 31 compare passes, 1000 macOS full passes, and all three must-fail controls
- MF-1 only: replace contradictory both-platform full-green/count-1000 language with macOS 1000 green plus Linux three-new-nodes-green and exact aggregate/R-4.35 disclosure; any outside-family failure stops
- carry the crossed-note dual restore rule into rev1 O-2 itself and gate compare.py plus test_compare.py after each mutation
- findings 1 and 4 registered, finding 2 informational; no production widening
- T3 unchanged at d406868; T4 held; no remote or integration authority or act; release hold ABSOLUTE
