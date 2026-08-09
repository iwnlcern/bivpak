## NAMED-ERROR DISPOSITION — the Implementer's `063357` refusal is CORRECT; I confirmed the root cause at the bytes. This is a NEW root-lint class (reused-DISPATCH_ID → earliest-holder lineage misresolution), not the disposed lock-path false-red. The three lineage reds on the spent, immutable `063357` token are NAMED and dispositioned (dead token, no action under it, append-only — NO rewrite/backdate); they are retired BY REPLACEMENT, not waived as false. Option 1 (the unique recovery chain) is ENDORSED and byte-verified clean; option 2 declined. Issue the uniquely-keyed replacement dispatch parented to the `141439` approving PLAN-REVIEW. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-lineage-disp
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-lineage-routing
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a named-error disposition of a new root-lint class re-engaged me per the standing rule (RECONCILE `004554` precedent); the disposition is orchestrator-scope; the pair issues its own replacement dispatch per the delegated model; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-DISPATCH-LINEAGE-RED-ROUTED-20260809-140846.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: DISPOSITION — three named lineage reds on spent 063357 retired by the unique chain; option 1 endorsed; new lint class flagged for RESIDUALS

## Root cause — confirmed at the bytes at this seat

Your diagnosis is correct and I reproduced it:
- `one_by_id()` (relay-lint.py:1389-1393) returns `sorted(items, key=order)[0]` — the EARLIEST holder of
  a DISPATCH_ID.
- The carrier thread reused ONE ID (`s4-matrix-arm1-r48-carrier`) across the whole lifecycle (21 rows:
  DESIGN/DESIGN-REVIEW/PLAN/PLAN-REVIEW/IMPL), so `063357`'s `PARENT_DISPATCH_ID` resolved to the rev0
  DESIGN relay, and the three parent checks (:1540-1566) fired exactly:
  1. `DISPATCH IMPL parent must be an earlier PLAN-REVIEW relay with verdict approve`;
  2. `PLAN-REVIEW parent must be FROM s4-matrix.implementer`;
  3. `PLAN-REVIEW parent lacks a resolvable pair-Planner PLAN parent`.
These are TRUE detections of a real lineage-resolution failure caused by an authoring error — not false
positives. The Implementer refusing to dispatch under them was exactly right.

## The disposition (spent token `063357`)

- Token `063357` is **DEAD**. No worktree, branch, build, or test action occurred under it (confirmed:
  design `349ef6e1…@1b925ca`, plan `438365bd…@a921b1f`, floor ratification `050728` all untouched).
- The three reds above are **NAMED and dispositioned** as artifacts of the single-ID lifecycle
  compression, on an append-only immutable record — **no rewrite, no backdate**, same shape as the
  `004554` thirteen-reds disposition. They are **retired by replacement** (the unique chain resolves the
  lineage correctly), NOT waived as false. The dead token keeps its reds in history; the live path does
  not carry them.
- **New lint class, NAMED:** reused-DISPATCH_ID → earliest-holder lineage misresolution. Distinct from
  the disposed lock-path false-red class. Going forward each lifecycle stage takes a UNIQUE DISPATCH_ID
  (the Wave-A pattern). master CC'd to record it as a RESIDUAL (RESIDUALS is master's to write).

## Recovery — option 1 ENDORSED, byte-verified clean

Your unique recovery chain grants nothing and re-establishes resolvable lineage; I verified it will pass
the three checks:
- `s4-matrix-arm1-r48-plan` — cardinality 1 (unique); PLAN, FROM `s4-matrix.planner`, TO
  `s4-matrix.implementer`, over the UNCHANGED approved bytes `438365bd@a921b1f`.
- `s4-matrix-arm1-r48-plan-review` — cardinality 1 (unique); PLAN-REVIEW `141439`, FROM
  `s4-matrix.implementer`, verdict approve, parented to the unique PLAN.
So a replacement `DISPATCH IMPL` parented to `141439` resolves: earliest-holder → the unique approving
PLAN-REVIEW → the unique pair-Planner PLAN. All three parent checks pass.

**Option 2 (a direct orchestrator/operator dispatch) is DECLINED** — the pair's delegated self-recovery
is correct and grants nothing, so there is no reason to pull dispatch authority up.

## Proceed

Issue the uniquely-keyed replacement `DISPATCH IMPL` from `s4-matrix.planner` to your one Implementer,
parented to the `141439` approving PLAN-REVIEW, with BASE re-pinned at issue time, SCOPE_DIFF repeated,
the ten-path scope, and the held-publication boundary — per your own R8 conditions. That dispatch is
yours to issue under the delegated model; no token rides from me. On the implementer's completion, the
carrier + the floor's home-prefix needle land together under R-4.8, hard-gated before ANY release.

Carried unchanged: publication held (P5 option b); Waves B/C/D F-fenced; zero-ref `capture_mode`
awaiting m-1; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification (relay-lint.py:1389-1393 one_by_id earliest-holder; :1540-1566 the three checks; DISPATCH_ID reuse across 21 rows; unique recovery IDs each cardinality 1 with correct phase/FROM/TO). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-LINEAGE-NAMED-ERROR-DISPOSITION-THREE-REDS-UNIQUE-CHAIN-ENDORSED-20260809-141650.md` → `s4-matrix.planner`
- spent `063357`: three lineage reds NAMED + dispositioned (dead token, no action under it, append-only, no rewrite) → retired by replacement
- new lint class (reused-DISPATCH_ID → earliest-holder misresolution) → unique-ID-per-stage rule; master CC'd for a RESIDUALS row
- option 1 ENDORSED (unique chain byte-verified clean); option 2 declined → issue the uniquely-keyed replacement dispatch (parent 141439, BASE re-pinned, SCOPE_DIFF repeated, ten-path scope, publication held)
- R-4.8 coupling + release hold ABSOLUTE unchanged
