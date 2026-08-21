## PLAN-REVIEW — MUST REVISE: MR-14 closes, but the new macOS command accepts arbitrary receipt labels and treats every non-`eq` anchor as `ne`, so its phase identity and evidence-root containment are not fail-closed

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r7
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r7
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R7-ONE-EVIDENCE-CHAIN-INIT-MACOS-LINUX-20260821-025323.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R6-MUST-REVISE-UNIFIED-EVIDENCE-SEQUENCE-20260821-023353.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this verdict — the bounded in-lane repair remains authorized under `201613`, but rev7 carries no token and no implementation token may parent to this review; merge, push, publication, schema, deployment, and release remain separately held
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed PLAN commit `ad7c3b522b92b37d26df3987d96b1b4a886e9ad8`; frozen product base and T1 head remain `a02a65b9ea2c1ce6ff149a914c50f965531d443d` and `76638a00332fc9dd674f0cf952e28be4fa0507e8`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev7; one-root chronology approved, but macOS label and anchor domains are prose-only and allow mislabeled or escaped receipts

## 1. Verdict

**MUST REVISE, NARROWLY.** Rev7 closes MR-14. `init` creates one unique root before S2; `require_root` adopts rather than recreates it; Linux now runs one phase per invocation, so S3 no longer depends on the future S4 commit; and the S2/S5mac receipts are absent-before, non-empty-after, and hashed into the shared receipt chain. I independently ran the filed `init` block, confirmed a mode-0700 root beneath the required parent, and confirmed `linux <that-root> s3` passes root adoption before asking for its head. The root and output were removed. Those chronology and root-lifetime mechanics are approved and must not be redesigned.

The new `cmd_macos` interface is not fail-closed at the boundary that gives those receipts their meaning. The comment and usage line advertise `label=(s2|s5mac)` and `anchor=(eq|ne)`, but the executable code accepts any non-empty values. `label` is interpolated directly into `$EVID/$label-*`; `anchor` uses `if eq; else ne`, so every string other than literal `eq` receives `ne` semantics.

I ran the exact filed script as `macos <fresh-valid-root> bogus garbage`. It did not reject either argument. It wrote `bogus-cache-root.txt` and then failed later with `S5 expects production CHANGED`, proving that `garbage` had silently selected the `ne` arm. The probe file, root, and captured output were removed. No implementation token may parent to this review.

## 2. Findings closed

```text
MR-1 through MR-13  CLOSED  product, proof, provenance, container, gates, and exact findings
MR-14                 CLOSED  one root initialized before S2 and one Linux phase per invocation
```

The rev7 SHA-256 is `831aba9911ea1e96a11c68b632e13b5e516f22893ebf210dc4b5f5801c153a1b`, Git blob is `058001ac94c5acd1dc17455f52b780fcaba5508d`, and containing commit is `ad7c3b522b92b37d26df3987d96b1b4a886e9ad8`. Historical exact-file lint passes. Both shell artifacts pass `bash -n` when re-extracted at the filed byte boundaries, both Python gates pass `ast.parse`, the input is correctly addressed to this seat, and it carries no token.

## 3. Must-fix MR-15 — bind the macOS label and anchor as one exact phase identity

Rev8 must validate the pair before `assert_absent`, cache inspection, or any evidence write. The only accepted pairs are:

```text
s2:eq
s5mac:ne
```

A single executable case over `"$label:$anchor"` is sufficient. Reject every other pair before touching the evidence root. This closes three concrete holes at once:

1. `s2:ne` can otherwise produce receipts labelled as pre-edit S2 while applying post-edit semantics.
2. `s5mac:eq` can otherwise produce receipts labelled as S5 while applying pre-edit semantics.
3. An unrestricted label such as `../outside` is path material, so `$EVID/$label-cache-root.txt` resolves outside the unique attempt root despite `require_root` having validated the root itself.

Validate the new gate on the real filed artifact with must-be-NO arms for an unknown label, unknown anchor, both swapped valid labels/anchors, and a traversal label. Each refusal must occur before any receipt is created inside or outside the root. Retain must-be-YES controls showing `s2:eq` and `s5mac:ne` pass this argument gate and reach the next expected precondition. Do not weaken the accepted source-anchor assertions or change the already-approved phase order.

This is evidence-domain validation only. Do not alter the product shape, two-path scope, analyzer identities, toolchain, Docker topology, source-hash anchors, RED/GREEN gates, or one-root sequence while fixing it.

## 4. Held scope and state

Scope remains:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

T2/T3/T4 and `compare.py` remain held. Count-gate shape remains routed; Linux `nonzero_exit` remains owed; `harness-selftest` remains separately reported under `201613`; schema remains F+G-fenced. No source, test, harness, workflow, candidate ref, container, image, retained evidence directory, PR, remote CI, merge, push, publication, deployment, or release was changed. Review diagnostics created and removed two exact ignored evidence roots, one cache-root probe receipt, and two captured-output files; no Docker resource was created, pruned, or removed. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: exact-plan identity/historical lint, filed-block `bash -n` and `ast.parse`, candidate-head/source/cache inspection, live INDEX EOF, repository-status inspection, one successful init/adoption probe, and one invalid-label/invalid-anchor falsifier. Every exact probe root, receipt, and captured-output file was removed. No source/test/workflow/ref/container/image/retained-evidence/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts remain preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `ad7c3b522b92b37d26df3987d96b1b4a886e9ad8`, blob `058001ac94c5acd1dc17455f52b780fcaba5508d`, SHA-256 `831aba9911ea1e96a11c68b632e13b5e516f22893ebf210dc4b5f5801c153a1b`; no implementation token may parent to this review
- MR-1 through MR-14 are CLOSED; preserve the one-root S1-S5 chronology, one Linux phase per invocation, macOS/Linux receipts, exact analyzer gates, product proof, and two-path scope
- MR-15: `cmd_macos` accepts arbitrary labels and silently maps every non-`eq` anchor to `ne`; the exact filed probe `bogus garbage` wrote a bogus-labelled receipt before failing on the later source assertion
- Rev8 must accept only the exact pairs `s2:eq` and `s5mac:ne` before any evidence write, reject unknown/swapped/traversal inputs on demonstrated NO arms, and retain both valid-pair YES controls
- No token, product edit, ref movement, container, CI, PR mutation, merge, push, schema, deployment, or release; T2-T4 held, count shape routed, Linux `nonzero_exit` owed, release hold ABSOLUTE
