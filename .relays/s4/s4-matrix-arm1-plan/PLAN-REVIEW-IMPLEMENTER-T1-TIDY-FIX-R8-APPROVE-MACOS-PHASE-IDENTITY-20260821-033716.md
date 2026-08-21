## PLAN-REVIEW — APPROVE: rev8 closes MR-15 with an exact macOS phase-identity pair gate before every write, and refused preconditions now leave the one evidence root byte-untouched

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r8
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r8
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R8-MACOS-PHASE-IDENTITY-PAIR-GATE-20260821-033237.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R7-MUST-REVISE-MACOS-LABEL-ANCHOR-DOMAIN-20260821-031405.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this approves the bounded plan only. Rev8 carries no token and authorizes no keyboard; the pair Planner may next issue the bare `DISPATCH IMPL` parented to this exact approval. Merge, push, publication, schema, deployment, and release remain separately held
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed PLAN commit `5bbf403be9b0363bc3299c8a636bd43433652a69`; frozen product base and T1 head remain `a02a65b9ea2c1ce6ff149a914c50f965531d443d` and `76638a00332fc9dd674f0cf952e28be4fa0507e8`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — APPROVE T1 tidy plan rev8; MR-1 through MR-15 closed, bare implementation token is the next gate

## 1. Verdict

**APPROVE.** Rev8 closes MR-15 without changing the accepted product, test, phase, toolchain, container, or evidence topology. `cmd_macos` now validates `"$label:$anchor"` as one identity before `assert_absent`, cache inspection, or any evidence write; exactly `s2:eq` and `s5mac:ne` are admitted. Unknown, swapped, empty, and traversal-shaped inputs are rejected by the same executable predicate. The cache-root and source receipts moved below every identity, cache, containment, digest, and anchor precondition, so a refused precondition cannot poison the later legitimate phase through its own absent-before gate.

The revision boundary is acceptable: the changed function is inlined completely, while the driver remainder and three sibling artifacts are bound to the already-reviewed rev7 bytes rather than substituted as text inside an executable command. The one-root S1-S5 sequence, one-Linux-phase invocation, exact analyzer identities, RED/GREEN gates, and two-path product scope therefore carry unchanged.

This review is not an implementation dispatch. The next authorized act is the pair Planner's bare `DISPATCH IMPL` token parented to this exact approval and carrying the already-frozen two-path scope. No implementation may begin from rev8 alone.

## 2. Independent verification

The rev8 SHA-256 is `fbab31f5aae430a843c80b792796ebe467f44c61928f0db8121ba0c39ca733d1`, Git blob is `d7f13e6c2485d81c9f329e470a73726bc5d0cc0f`, and containing commit is `5bbf403be9b0363bc3299c8a636bd43433652a69`. Historical exact-file lint passes, the relay is correctly addressed to this seat, and it carries no token.

I reconstructed the executable only from rev7's accepted unchanged driver bytes plus rev8's filed replacement function; the composite passes `bash -n`. Against one fresh ignored root:

```text
required NO arms
  bogus:garbage   refused with the pair-gate message
  s2:ne           refused with the pair-gate message
  s5mac:eq        refused with the pair-gate message
  s2:GARBAGE      refused with the pair-gate message
  nosuchlabel:eq  refused with the pair-gate message
  ../ESCAPED:eq   refused with the pair-gate message; no outside file appeared
  empty pair      refused with the pair-gate message

controls
  s5mac:ne  passed identity, then refused at the correct pre-edit source anchor;
             root contents and hashes remained byte-identical
  s2:eq     passed identity and source anchor, recorded source SHA-256
             9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b,
             and reached the real incremental build before the two-second bound expired
```

All probe files, captured output, and the exact probe root were removed. The candidate worktree remained porcelain-clean with HEAD unchanged at `76638a00332fc9dd674f0cf952e28be4fa0507e8`. No container or remote CI was started.

## 3. Approved scope and execution obligations

The implementation token remains limited to:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

Execute S1 through S5 in the frozen order using one `init` root and the exact rev8 pair gate. Preserve the pre-edit source anchor at S2/S3, the committed fixed-byte binding at S5, absent-before/non-empty-after receipts, exact analyzer finding identities, non-root Docker execution with nofile soft raised to inherited hard, and the separate RED/GREEN predicates.

The declared real-log residual remains an execution-time gate, not a plan blocker: the S3 parser has only seen synthetic clang-tidy-shaped logs. Its first real S3 mismatch is a gate defect to report and correct without touching product bytes or waiving an extra finding. `harness-selftest` remains separately adjudicated under `201613`; the Linux full suite must not be labelled GREEN on that residual. Linux `nonzero_exit` remains owed. T2/T3/T4 and `compare.py` remain held.

## 4. State

No source, test, harness, workflow, candidate ref, container, image, retained evidence directory, PR, remote CI, merge, push, publication, deployment, or release was changed. The bounded `s2:eq` control ran incremental builds inside the pre-existing ignored `build/ci-macos` cache; the candidate remained clean and unmoved. Every exact probe artifact was removed. Schema remains F+G-fenced. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: exact-plan identity/historical lint, reconstruction of rev7 accepted bytes plus the rev8 replacement function, composite `bash -n`, seven required rejection arms plus one redundant unknown-pair control, both valid-pair controls, before/after root hashing, traversal absence, candidate head/status, live INDEX EOF, and repository-status inspection. All exact probe roots, receipts, and captured outputs removed. No source/test/workflow/ref/container/image/retained-evidence/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts remain preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- PLAN-REVIEW VERDICT APPROVE at PLAN commit `5bbf403be9b0363bc3299c8a636bd43433652a69`, blob `d7f13e6c2485d81c9f329e470a73726bc5d0cc0f`, SHA-256 `fbab31f5aae430a843c80b792796ebe467f44c61928f0db8121ba0c39ca733d1`
- MR-1 through MR-15 are CLOSED; preserve the exact product shape, three test cases, one-root chronology, one Linux phase per invocation, phase-correct receipts, analyzer identities, and RED/GREEN gates
- This approval carries NO token and authorizes NO keyboard; the pair Planner's bare `DISPATCH IMPL`, parented to this review with all scope rows IN, is the next gate
- S3's first real clang-tidy log remains the declared fail-closed parser check; a format mismatch is a reported gate correction, never permission for a product change or finding waiver
- T2-T4 and `compare.py` held; count gate routed; Linux `nonzero_exit` owed; harness residual separate; schema fenced; no merge, push, publication, deployment, or release; release hold ABSOLUTE
