## PLAN-REVIEW — MUST REVISE: MR-11 through MR-13 close, but the macOS S2 row consumes `$EVID_HOST` before the only command that creates it, and the later Linux driver replaces it with a different root

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r6
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r6
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R6-MERGED-RECIPE-VALIDATED-GATES-20260821-022928.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R5-MUST-REVISE-MERGED-RECIPE-FRESH-EVIDENCE-20260820-233909.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this verdict — the bounded in-lane repair remains authorized under `201613`, but rev6 carries no token and no implementation token may parent to this review; merge, push, publication, schema, deployment, and release remain separately held
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed PLAN commit `85ff80ecb6d672ea34a58ad15691d9f61063683c`; frozen product base and T1 head remain `a02a65b9ea2c1ce6ff149a914c50f965531d443d` and `76638a00332fc9dd674f0cf952e28be4fa0507e8`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN-REVIEW — MUST REVISE T1 tidy plan rev6; merged Linux recipe and exact finding gate approved, but the retained evidence root is created after its first required consumer and then silently replaced

## 1. Verdict

**MUST REVISE, NARROWLY.** Rev6 closes MR-11 through MR-13. The four inlined artifacts are complete at their stated boundary; `$STAGE_GATE` is created and populated; both phase gates are invoked with exact arguments; Linux artifacts are absent-before, non-empty-after, and hashed beneath a unique `mktemp -d` root; and the RED predicate compares a multiplicity-preserving list of exact `(line, check-id)` identities. The one required YES plus five required NO S3 arms and the S5 arms are a sound synthetic falsification set. Those pieces are approved and must not be redesigned.

The remaining defect is the exact S1-S5 execution order. Section 5 requires the first macOS block at S2, before the production edit, and writes both outputs to `$EVID_HOST`. The only assignment to `EVID_HOST`, however, is inside `t1_tidy_linux_evidence.sh`. That driver cannot be run merely to initialize S2: it requires the future S4 commit as argument 2, derives `FIXED_HASH` before either Linux phase, and then runs both S3 and S5. When it eventually runs after S4 exists, it unconditionally creates a new root, so any independently initialized S2 root would be replaced rather than joined.

As filed, the first macOS command therefore consumes an undefined variable in the stated sequence, or an operator must invent an unfiled initialization and accept two unrelated attempt roots. The recipe is not yet one executable, fresh-by-construction evidence chain. No implementation token may parent to this review.

## 2. Findings closed

```text
MR-1 through MR-10  CLOSED  product, proof, provenance, container, evidence model, and status capture
MR-11                 CLOSED  complete staged two-phase Linux recipe and explicit macOS status capture
MR-12                 CLOSED  unique Linux root plus absent-before, non-empty-after, and hashes
MR-13                 CLOSED  exact finding identities with multiplicity and falsifier arms
```

The rev6 SHA-256 is `defb5d2fce121dd1643226c0561c401cfd14f0cbf8123f0964db306e8ff90f4d`, Git blob is `5c9824e30ff6a6d3c0ac6aa2dcdce233d476671d`, and containing commit is `85ff80ecb6d672ea34a58ad15691d9f61063683c`. Historical exact-file lint passes. The input is correctly addressed to this seat and carries no token.

I also tested the tempting `/evidence` permission objection instead of filing it speculatively. On the required Docker Desktop path, a host `mktemp -d` root was mode `0700`; inside `ubuntu:24.04` the bind appeared root-owned, yet `runuser -u biv -- touch /evidence/probe` succeeded and the host file landed as uid 501. The disposable container and exact temporary directory were removed. There is no permission finding from this review.

## 3. Must-fix MR-14 — create one evidence root before S2 and carry it unchanged through S5

Rev7 must make the evidence-root lifetime executable in the frozen phase order. Choose one exact shape:

1. Create and validate the unique retained root in a bootstrap step before the S2 macOS characterization, then pass that exact absolute path into the Linux driver and prohibit the driver from reassigning it; or
2. Split initialization from execution so the same filed driver can initialize the root before S2 and later resume S3/S5 against that exact root without creating another.

In either shape, require the supplied root to be beneath the ignored `.superpowers/sdd/` parent, bind it to this attempt, prove each macOS receipt absent before its producing row and non-empty after, hash the macOS logs/status alongside the Linux receipt hashes, and record the one exact root in the successor SITREP. The S2 first block must run at the S1 commit before the S4 edit; its S5 rerun and the named macOS rows must land under the same root. A shell-local variable created only inside a later subprocess is not available to the earlier parent shell and cannot satisfy this requirement.

This is evidence plumbing only. Do not alter the product shape, two-path scope, S1-S5 predicates, analyzer identities, toolchain, container topology, or accepted gate scripts while fixing it.

## 4. Held scope and state

Scope remains:

```text
src/core/support/subprocess.cpp  pointer-held sinks and buffer{} only
tests/test_subprocess.cpp        three exact characterization cases only
```

T2/T3/T4 and `compare.py` remain held. Count-gate shape remains routed; Linux `nonzero_exit` remains owed; `harness-selftest` remains separately reported under `201613`; schema remains F+G-fenced. No source, test, harness, workflow, candidate ref, image, retained evidence directory, PR, remote CI, merge, push, publication, deployment, or release was changed. The diagnostic used one disposable `ubuntu:24.04` container and one exact temporary directory, both removed; no unrelated Docker resource was pruned or removed. Merge is not push is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-plan identity/historical lint, phase-order and shell-variable-lifetime inspection, live INDEX EOF, repository-status inspection, plus one disposable Docker Desktop bind-permission falsifier whose exact container and temporary directory were removed. No source/test/workflow/ref/image/retained-evidence/PR/remote mutation. Docs-lane delta is this review relay plus one live-EOF INDEX row only; all pre-existing sibling artifacts remain preserved unchanged and unclaimed.
FINAL_GIT_STATUS_SHORT: this review relay and its appended INDEX row are this seat's only new delta; all pre-existing untracked sibling artifacts remain preserved and unclaimed

CARRY LIST (D-8.5):
- VERDICT MUST REVISE at PLAN commit `85ff80ecb6d672ea34a58ad15691d9f61063683c`, blob `5c9824e30ff6a6d3c0ac6aa2dcdce233d476671d`, SHA-256 `defb5d2fce121dd1643226c0561c401cfd14f0cbf8123f0964db306e8ff90f4d`; no implementation token may parent to this review
- MR-1 through MR-13 are CLOSED; preserve the product proof, two-path scope, complete Linux recipe, fresh Linux receipts, RED/GREEN gates, exact finding identities, and validated falsifier arms
- MR-14: `$EVID_HOST` is first created inside the later two-head Linux driver, but S2 already writes to it before S4 exists; the driver then replaces any independently created root. Rev7 must initialize one unique root before S2 and pass that exact root unchanged through all macOS and Linux rows to S5
- The Docker Desktop `0700` bind-permission concern was independently falsified and is not a finding
- No token, product edit, ref movement, CI, PR mutation, merge, push, schema, deployment, or release; T2-T4 held, count shape routed, Linux `nonzero_exit` owed, release hold ABSOLUTE
