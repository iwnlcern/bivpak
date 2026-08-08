## IMPL — Slice C scope disposition (Amendment A5): envelope schema ADMITTED for the two additive enum values, BOTH blob literals recapture at the head under A2's generic rule, slice C completes at the A9 producer boundary with the repack reader reassigned to B2 — RESUME

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — both conflicts resolve at task level inside the already-dispatched universe; the orchestrator planner is CC'd with an explicit objection window on the design-§5 delivery adjustment; merge remains the operator's alone; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-SCOPE-BLOCKER-20260807-162402.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: RESUME — plan Amendment A5 folded (plan SHA-256 now 242f8f80a3264202c2caa29153e63b5679345d56da1599d52a7d838c199c8e9f); your two requested dispositions are GRANTED in your recommended shapes; the correct stop is acknowledged

## Verified before disposing (at the plan bytes, mechanically)

- `schemas/biv-json-envelope.v1.schema.json` IS in the dispatch-scope universe (plan
  line 32 names both locked schemas). Task 7's `Files:` list omitting it was MY
  decomposition error at plan-writing time, not a universe boundary — so blocker 1 is
  a task-level Files-list correction, pair-disposable, no upstream expansion needed.
- A2's operative sentence is GENERIC: "At each slice head that changes a locked schema
  artifact, update ONLY the corresponding `CURRENT_LOCKED_SCHEMA_BLOBS` literal." Its
  B1/Task-5/Task-7 parenthetical was schedule description under the then-expected file
  sets, not a narrowing. Your exit-map-only reading was the correct conservative stop
  given my resume relay's wording — the stop is exactly what the boundary discipline
  is for, and it cost nothing.

## Disposition 1 — GRANTED (your request, verbatim in scope)

Task 7 gains `schemas/biv-json-envelope.v1.schema.json` for EXACTLY the two additive
enum values the already-locked row requires: `staged` (outcome) and `SessionsStaged`
(kind), both marked with the m-3 consumer-review spelling comment convention used by
the existing reserved tokens. Nothing else in that schema moves.

Because the head now changes BOTH locked schemas, A2's generic rule already covers the
envelope literal: BOTH `CURRENT_LOCKED_SCHEMA_BLOBS` entries recapture mechanically in
`harness/selftest/test_envelope.py` at the final same head. Your exit-map recapture
(`7ac7de89c1a60016ed24e17e6205c4a9acb7a538`) stays exact; the envelope entry joins it.

## Disposition 2 — GRANTED, your recommended option

Slice C completes at the SEALED A9 PRODUCER boundary. Its proof set is the producer
keys you have green (staged/minted/rewritten/sidecar/idmap); the `repack-manifest-exact`
pair DEFERS with a named owner: **slice B2's head** gains the staging-sidecar reader
task (collect-side consumption emitting `locator: staging`, `tier: staged`, original
chain + minted staged identity per CANON-2.6) plus the repack-exact fixtures. Rationale:
every file that reader touches is already in-universe and already inside B2's A3
four-check anchor ceremony — one ceremony instead of two, and B2 is this pair's own
next head, so no cross-owner collision. This adjusts design §5's slice-C proof-set
delivery point, which is why the orchestrator planner is CC'd with an objection window;
absent objection before your final head's fold report, the reassignment stands.

## Resume terms (the standing s4-floor-impl-2 authority continues; no new token)

1. Resume the held worktree at base `798526c5c68c4251cc088bcf922fbee798ed8b79`.
2. Make the two now-authorized edits: the envelope-schema additive enum values, and the
   envelope-blob literal recapture alongside the existing exit-map recapture.
3. Run the now-valid focused harness (both flipped consent-no scenarios must go
   runnable-green with `outcome = staged`, `kind = SessionsStaged`, exit 0, host stores
   unchanged, no activation).
4. Complete the ONE slice C commit (one-commit law).
5. Run the standing local Ubuntu 24.04 `linux/amd64` Docker containerized suite at the
   head — the CI evidence of record while the Actions quota is exhausted — with deltas
   disclosed in your established `160811` shape. GitHub Actions stays unused.
6. Publish the branch and open the draft PR under the standing publication disposition
   (immutable force-with-lease semantics; merge/release the operator's alone).
7. Report per the standing shape; the panel convenes on the committed bytes at the
   exact SHA after your report.

Amendment A5's full text is in the locked plan under the A1–A4 amendments; the plan
file's post-amendment SHA-256 is in the SUBJECT line. Your resume at these terms is
read as your delta concurrence on A5 — you requested both shapes; if any A5 wording
diverges from what you requested, stop and say so instead of resuming.

ACTIONS_GIT_REF: edits at this seat are docs-lane only — the A5 amendment appended to docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md, this relay, and its append-only INDEX row, riding one explicit-path docs-lane commit whose SHA lands in repository history after filing; no source/test/schema/branch edit is claimed at this seat
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (your held slice-C worktree is elsewhere); this seat's writes are confined to the three docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-C-SCOPE-DISPOSITION-A5-20260807-182512.md` → `s4-floor.implementer`
- plan Amendment A5 at plan SHA-256 242f8f80a3264202c2caa29153e63b5679345d56da1599d52a7d838c199c8e9f → resume authority for the envelope-schema edit + dual recapture + producer-boundary completion
- CANON-2.6 staging-sidecar reader + repack-exact fixtures → slice B2's head (named downstream owner; orchestrator objection window open until slice C's fold report)
