## SITREP — T3 panel PASS received; choose the divergent-SHA regression guard; bounded pair PLAN and token awaited; remaining findings registered without widening

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t3-panel-pass-ref-sha-test-chosen-await-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t3-panel-pass-close-ref-sha-gap
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-PANEL-PASS-3-NONBLOCKING-CLOSE-REF-SHA-TEST-GAP-BEFORE-STAGE5-20260822-060538.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T3-LINUX-AGGREGATE-RULED-ACCEPTABLE-PANEL-CONVENED-INDEX-REPAIR-AFFIRMED-20260822-060126.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for this bounded test-only cycle; a pair Planner PLAN, approving Implementer PLAN-REVIEW, and later literal implementation token are still required before any test or source keyboard act. Every merge remains a separate operator word; release hold ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted and panel-passed T3 d4068684e51f67d0a11fb6d2251178fb2a1a70ea
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T3 panel PASS received; choose the recommended divergent-SHA plus extra-ref regression guard in test_compare.py only; request bounded pair PLAN then review then token; register additive-root asymmetry and gitlink trust boundary as Stage-4 notes and retain Hostile-User assertion as informational

The two ordered rulings are received exactly as filed. The Linux aggregate is acceptable under
the disclose-don't-launder bar, T3 at `d406868` is accepted, and the three-lens Stage-3 panel
passes with no blocking or false-green finding. The repaired completion INDEX rows are affirmed.

## 1. Finding (3) disposition — add the regression guard

I choose the recommended small in-lane test rather than leaving the most safety-critical gap as
documentation only. Direct read at `d406868` confirms the implementation is already correct:
`harness/bivharness/compare.py:236-240` compares common carried-ref object IDs and emits
`D: repo ... ref mismatch for ...` when they differ. Direct read of
`harness/selftest/test_compare.py` confirms coverage for missing refs, HEAD mismatch, branch
mismatch, ignored non-carried refs, and explicit repo-state expectations, but no test moves a
same-name carried ref to a divergent SHA; no test covers the adjacent extra-ref arm either.

Requested bounded plan shape:

```text
scope       harness/selftest/test_compare.py only
fixture     existing _matching_git_trees(tmp_path)
mutation A  in the restored repo, update refs/heads/keep from the first commit to HEAD
mutation B  in the restored repo, create refs/heads/extra at HEAD
oracle      compare_trees returns the exact extra-ref finding and the exact ref-mismatch finding;
            the mismatch text binds the source keep SHA and restored HEAD SHA, not only a substring
control     in a scratch copy only, disable the common-ref SHA comparison and prove the new named
            test fails; restore-gate both compare.py and test_compare.py digests before later runs
proof       named test, all test_compare.py, full harness/selftest on macOS and local disposable
            ubuntu:24.04 linux/amd64 with Docker --init and non-root nofile soft-to-hard
scope gate  exactly one changed file relative to d406868; no compare.py product change
```

The extra-ref check belongs in the same test because it uses the same fixture mutation and the
same `compare_trees` call; a second test would duplicate setup without separating a different
contract. The exact two-finding oracle makes both perturbations load-bearing and prevents a
names-only comparison from passing.

If authorized and green, the new T3 head returns only for the focused re-lens on this test, as
`060538` requires. The already-cleared compare implementation, composition, fixture/date oracle,
and unrelated T1/T2 bytes are not reopened.

## 2. Other panel findings — disposed without expanding this cycle

- Finding (1), additive-root asymmetry at `compare.py:349`: register as a Stage-4 robustness
  note. It is over-strict and visibly fails rather than false-greens, and the current staging
  roots do not contain a nested repo. Passing `allowed_roots` into repo semantics is a product
  policy change and is outside this test-only cycle.
- Finding (2), the non-discriminating `Hostile User` assertion: informational. The sibling hook
  tests carry the discriminating config-isolation proof; no test edit is justified here.
- Finding (4), `.git` file/gitlink acceptance at `compare.py:156`: register as a Stage-4 latent
  trust-boundary note. There is no fixture or declared gitlink policy, so changing discovery now
  would make policy while pretending to harden mechanically.

All four findings are therefore explicitly disposed before Stage 5: one selected for a bounded
test cycle, two registered notes, and one informational observation. The eventual Stage-5 report
must carry these dispositions alongside R-4.35, R-4.38, R-4.40, and the permanent lineage-record
defects already named by the lane.

## 3. Authority and state

This relay is not a pair PLAN, not a PLAN-REVIEW, and not an implementation token. The incoming
relay is `AUTHORITY: plan-only` and says `No token issued`; panel acceptance does not authorize a
test edit. No source, test, branch, ref, evidence, container, or remote act occurs here.

T3 remains accepted, clean, local, and unpublished at `d406868` while the optional cycle awaits
the pair Planner. T4 remains held pending disposition of that cycle. No remote CI, push, PR
mutation, merge, publication, schema act, deployment, or release occurred. Merge is not push is
not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only verification of the exact 060126 and 060538 relays, their literal routing and historical lint; live .relays/s4/INDEX.md tail; clean s4-matrix/arm1-t3 at d406868; git show of d406868 compare.py common-ref SHA comparison and test_compare.py repo-semantic coverage. No source, test, worktree, ref, container, remote CI, push, PR mutation, merge, publication, schema, deployment, or release act. This relay plus one live-EOF INDEX row ride one explicit-path docs-lane commit
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read immediately before append; full INDEX lint compared against the pre-append baseline of 10 inherited errors and required to add none; cached diff check and explicit two-path commit are fail-fast gates; post-commit historical exact-file verification
FINAL_GIT_STATUS_SHORT: T3 worktree clean at d406868; shared docs checkout retains sibling-authored untracked paths, preserved and unclaimed; only this relay and its single INDEX append are claimed

CARRY LIST:
- Linux aggregate ruling and T3 Stage-3 PASS received; d406868 accepted; no blocking or false-green finding
- choose finding (3) test-only closure in test_compare.py: same-name divergent keep ref plus extra ref, exact two-finding oracle, scratch names-only false-green discriminator, one-file scope, both-host proof
- findings (1) and (4) registered as Stage-4 robustness and trust-boundary notes; finding (2) informational with sibling discriminating coverage
- await pair Planner PLAN, Implementer PLAN-REVIEW, then literal implementation token; no keyboard authority inferred from panel approval
- after an authorized green cycle, focused re-lens on the new test only; T4 held meanwhile
- no remote or integration act; every merge remains operator-gated; release hold ABSOLUTE
