## MERGE-GATE (carry-down) — the OPERATOR GRANTED the DRAFT→READY transition, BOUNDED: ONE `gh pr ready 24` at head `0ab998d8431a20de80b8d769fb82c1350ed0728d`, a P5 publication-lifecycle transition ONLY — no other PR mutation, no title/base/body/label edit, no rerun, no force, no release. The four-seat refusal chain is DISCHARGED BY GRANT. On the ready transition verifying, the STANDING condition-4 token (`1fb3287`) MERGES AS WRITTEN — no re-issue, no token boundary moved (the (a) shape). I re-verified at my seat: PR #24 still `isDraft=true` at head `0ab998d` (`mergeable=MERGEABLE`, `mergeStateStatus=UNSTABLE`), branch tip unmoved, merge-tree into current `origin/main` CLEAN. The full sequence is specified so nothing is inferred: ready → verify not-draft AND head still `0ab998d` → merge under the standing token → re-verify at the ACTUAL merge tip → route the landed SHA UP. `UNSTABLE` is expected and is NOT a stop condition (the unfunded-runner checks were ruled non-blocking at master `181552`; do not rerun, wait, or chase green). Merge ≠ release — the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-matrix-r48-ready-then-merge
PARENT_DISPATCH_ID: s4-matrix-r48-condition4-token
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-READY-GRANTED-P5-MERGE-SEQUENCE-CARRIED-20260810-182041.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED — the operator granted the bounded ready transition; conditions 1+2+3+4 were already satisfied at 0ab998d and the republication verified. The release hold remains a SEPARATE, still-closed gate (merge ≠ release); the local-`main` publication-timing question is the operator's separate open item this does not touch.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: MERGE-GATE — ready transition granted (bounded); standing token 1fb3287 merges as written; full sequence + hard stops

## The sequence (do NOT infer a step; do NOT collapse it)

```text
STEP 1  READY     gh pr ready 24  — the granted P5 act, at head 0ab998d, ONE call, nothing else.
                  No title/base/body/label edit, no rerun, no force, no release.
STEP 2  VERIFY    gh pr view 24 → isDraft FALSE **AND** headRefOid == 0ab998d8431a20de80b8d769fb82c1350ed0728d
                  byte-exact. A head that moved is a NEW head and a new review — STOP and route up.
STEP 3  MERGE     the STANDING condition-4 token (1fb3287) authorizes this merge AS WRITTEN — no re-issue.
                  s4-matrix.implementer merges PR #24 (head 0ab998d) into main. Immediately before merging,
                  re-verify the PR head OID == 0ab998d (per 1fb3287's own condition) AND isDraft==false.
                  Re-verify CLEAN at the ACTUAL merge tip (main is docs-lane advancing); any surprise
                  conflict STOPS and routes up — do not resolve a conflict under the token.
STEP 4  REPORT    route the landed merge commit SHA UP (to me → master) → master closes condition-3-of-record
                  against the merged bytes.
```

**`mergeStateStatus=UNSTABLE` is expected and is NOT a stop condition.** It reflects the non-required,
unfunded-runner checks ruled non-blocking at master `181552` (`main` is unprotected; there is no required
check). Do not rerun them, do not wait on them, do not chase green. The governing Linux signal is the local
Docker leg, as ruled.

## Carry-time re-verification (my seat, this pass)

```text
PR #24     isDraft TRUE · headRefOid 0ab998d… == reviewed head · MERGEABLE · UNSTABLE · base main   ✓
branch     s4-matrix/r48-carrier tip 0ab998d… — unmoved                                             ✓
mechanics  merge-tree origin/main (8981bfd0) ← 0ab998d  CLEAN (no conflict markers)                 ✓
standing   condition-4 token 1fb3287 issued to s4-matrix.implementer, merge-only, bound to 0ab998d  ✓
```

## Scope of the grant, stated plainly

**Authorized:** the single `gh pr ready 24` transition at `0ab998d` + the already-granted merge of `0ab998d`
into `main` under the standing token `1fb3287`. **NOT authorized:** any other PR mutation (title/base/body/
labels), any rerun or CI action, any force-push, any release act, any local-`main` push (the
publication-timing question is the operator's separate open item, untouched). No new bare token rides this
relay — the standing token is the merge authorization and its boundary does not move. `231437` (C/B2) stays
WITHDRAWN and is a separate track. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits and NO ready/merge at this seat — carry-time re-verification only (gh pr view 24 draft/head/mergeable; git ls-remote tip == 0ab998d; merge-tree origin/main ← 0ab998d clean) + this relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. The ready transition and the merge are your acts under the operator's grants + the standing token; I perform neither, push nothing, merge nothing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Expected `--index` reds: the R-4.8 design/plan path-style-lock false-reds (relay-lint.py:1639; referents exist at repo-root) + the line-222 sibling inversion — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-READY-GRANTED-STANDING-TOKEN-MERGES-20260810-182605.md` → `s4-matrix.planner`
- operator GRANTED the bounded ready transition (ONE gh pr ready 24 at 0ab998d, P5-lifecycle only, nothing else); four-seat refusal chain discharged by grant
- sequence: READY (gh pr ready 24 @0ab998d) → VERIFY isDraft FALSE + head==0ab998d (moved→STOP) → MERGE under the STANDING token 1fb3287 (no re-issue; re-verify head+not-draft immediately before merge; re-verify clean at ACTUAL merge tip; conflict→STOP) → REPORT landed SHA UP for condition-3-of-record
- UNSTABLE is expected, NOT a stop condition (181552 non-blocking; don't rerun/wait/chase green); local Docker governs
- re-verified at my seat: PR draft@0ab998d, tip unmoved, merge-tree clean; scope: no other PR mutation/rerun/force/release/local-main push; 231437 WITHDRAWN; merge ≠ release; hold ABSOLUTE
