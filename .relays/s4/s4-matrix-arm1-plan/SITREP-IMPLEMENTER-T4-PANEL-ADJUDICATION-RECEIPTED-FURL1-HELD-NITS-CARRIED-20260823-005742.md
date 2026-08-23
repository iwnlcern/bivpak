## SITREP — T4 panel adjudication receipted: NSDMI fix cleared; F-URL-1 master hold preserved; three nits carried without scope widening

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-panel-adjudication-implementer-receipt
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-panel-adjudicated
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-PANEL-ADJUDICATED-FIX-CLEARED-SECURITY-FINDING-UP-NITS-DISCLOSED-20260822-233156.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: master and the operator dispose F-URL-1 as block-and-fix or ship-with-registered-residual plus owner sign-off. No pair-local corrective, product edit, test edit, fold, branch, push, PR, remote CI, merge, schema, registry, publication, deployment, or release is authorized by this receipt. If master chooses fix-in-lane, this seat waits for a new exact scoped dispatch and Orchestrator fence ruling. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — panel-adjudicated, clean, unpublished, and unmoved by this receipt
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Report-only receipt — panel cleared the authorized NSDMI fix; F-URL-1 remains a master/operator disposition with no pair fix authority; runtime-test limitation and three non-blocking nits carried to triage and stage-5; candidate 6ba01ef unchanged

## 1. Panel disposition received at its stated weight

The Orchestrator's Stage-3 adjudication clears the authorized NSDMI fix at candidate
`6ba01ef`: Lens A accepted the three NSDMIs as designated-initializer no-ops and the class guard
as a real compile-time discriminator; Lens C reproduced O-5, retained the exact three-file fence,
and accepted the GCC-only disclosure. This receipt does not claim a fourth lens or an independent
rerun of the panel. It carries the Orchestrator's adjudicated E2 result without inflating it.

The fix-local nit is accepted at the same non-blocking weight: the runtime doctest documents the
post-fix default values but does not discriminate base from candidate because value initialization
equals the NSDMIs for these members. The compile-time warning guard, proven by O-4's RED/GREEN and
negative control, is the regression discriminator. No test change is required or authorized here.

## 2. F-URL-1 hold preserved; no naive fold

Read-only inspection of the unchanged candidate confirms the structural premises cited by the
panel:

```text
src/core/repo/eligibility.cpp:178-182
  ls-remote uses GitInvokeOptions with allow_user_protocol=true and no empty_config_keys

src/core/repo/git_exec.cpp:97
  repo-local command-key census covers filter, diff and merge driver families, not url.*
```

The end-to-end redirect and multivalued-empty-override results remain attributed to the panel and
Orchestrator verification; this receipt does not claim a separate reproduction. F-URL-1 remains
routed UP because config isolation versus effective-URL resolution is a design and security-posture
choice, and the reported empty-key approach does not clear a multivalued `url.insteadOf` entry.

T4 FINAL remains HELD pending master's choice and the required owner sign-off. If master chooses a
pair-local fix, no byte moves until a new exact dispatch states the file fence and proof contract.

## 3. Non-blocking nits carried without ownership inference

The following lens-reported nits remain disclosed for `s4-matrix.planner` triage and the Stage-5
merge-readiness record. This Implementer receipt does not deep-verify, fix, or assign them:

1. `git_exec.cpp:222-223`: broad promisor error reclassification may mislabel a real object-store
   failure while preserving the failure.
2. `classify.cpp:344-345`: direct `.git/shallow` reading misses a gitlink `.git` file checkout;
   carry with the related T3 Stage-4 gitlink finding.
3. `restore.cpp`: captured `core.autocrlf` and `core.filemode` are unused by restore verification,
   potentially producing a spurious divergence; payload-layer ownership remains unresolved.

## 4. State and next actor

```text
NSDMI fix   CLEARED by Stage-3 panel at 6ba01ef
F-URL-1     OPEN above the pair; master/operator disposition required
T4 FINAL    HELD pending F-URL-1 disposition
candidate   6ba01ef clean, local, unpublished, unchanged
```

No source, test, evidence, branch, ref, worktree, remote, Docker, or CI state moved. No merge,
schema act, registry edit, publication, deployment, or release occurred. The release hold is
ABSOLUTE.

ACTIONS_GIT_REF: report-only receipt after exact-relay lint, live candidate-head and worktree-status verification, and read-only inspection of the two F-URL-1 structural loci. The panel reproduction remains attributed to the Orchestrator; this relay and one live-EOF INDEX row are the only claimed docs-lane writes; all sibling-authored tracked and untracked state is preserved and unclaimed
FINAL_GIT_STATUS_SHORT: candidate worktree clean at 6ba01ef; shared docs checkout preserves unrelated tracked and untracked state; only this relay and its one INDEX append belong to this Implementer act
RELAY_LINT: exact-file freshness; current INDEX diagnostics path-normalized and compared against the pre-append HEAD blob; root mode required to name no error against this relay; unique dispatch census; cached diff check and explicit two-path commit; post-commit exact-file no-freshness verification

CARRY LIST:
- Stage-3 panel CLEARED the authorized NSDMI fix at unchanged `6ba01ef`; this receipt carries the adjudicated result without claiming another lens
- runtime doctest limitation disclosed and non-blocking; compile-time O-4 warning guard is the discriminator; no test change authorized
- F-URL-1 remains routed UP and T4 FINAL remains HELD; no naive empty-key fold and no pair-local fix authority
- three nits preserved for Planner triage and Stage-5 carry without deep-verification or ownership inference at this seat
- candidate clean, local and unpublished; no product, test, evidence, branch, push, PR, remote CI, merge, schema, registry, publication, deployment or release act; release hold ABSOLUTE
