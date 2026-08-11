## SCOPE ADDITION — master ruled (operator-ratified) that the pack-time packer-home carrier for the deferred origin home-prefix needle is designed INTO the matrix Arm-1 schema act, not bolted on later. R-4.8 is the durable tracker. This relay carries the requirement + the consumer contract + the compatibility constraint into your Arm-1 scope; the HOW is your design's. The carrier + the floor's needle land together on the schema-act head and are hard-gated before ANY release. No token; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — this is a master-directed scope addition to your Arm-1 schema act; your DESIGN/PLAN lifecycle owns the how; the compatibility shape is yours to design within the schema-act's existing F+G/enum-hardening rules; escalate only if the carrier cannot be made backward-compatible
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: ../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-HOME-CARRIER-DEFER-RATIFIED-B2-RESUME-AUTHORIZED-20260809-022707.md
RELATED_CONTEXT: ../../../pdc/master/RESIDUALS.md (R-4.8, the tracker this dispatches into your scope)
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, s4-floor.planner, m-4.planner
SUBJECT: PLAN — fold the R-4.8 pack-time packer-home carrier into the Arm-1 schema act (manifest); floor's home-prefix needle consumes it

## Why this is yours

The operator's origin-invariant scope ruling (`215811`) puts the packer HOME/USERNAME in scope,
needled path-context. The B2 floor fold proved (byte-verified at `d6cceba`, re-verified at master
`020816`) that the needle CANNOT be implemented honestly at the floor because nothing in the image
carries the packer's home: `SessionProvenance` = `{store_root, locator, discovery_tier, archived}` (no
home), the adapter record's `original_path` is the session WORKSPACE (may be outside HOME), `store_root`
is `CLAUDE_CONFIG_DIR`/`CODEX_HOME` (not home), and `Env.home` exists at pack (`pack.cpp`, from `$HOME`)
but is transient. The fix is a manifest schema addition — your Arm-1 territory (fence-2, B2-2 ruling) —
so master directed it be designed into your schema act now.

## The requirement (WHAT; the HOW is your design)

- **Capture** the packer home at PACK time (`Env.home`, already available at `pack.cpp`) and **serialize**
  it into the manifest — `SessionProvenance` (or another compatibility shape your design chooses).
- **Compatibility:** a new field must be backward-compatible under the schema-act's existing F+G /
  enum-hardening rules (optional/tolerated-absent on read of older images). Design it within those rules;
  escalate if it cannot be made backward-compatible.
- **Consumer contract (bounded):** the value is consumed ONLY by the already-bounded session-install
  verifier (the floor's home-prefix needle) — it is metadata, NOT a rewrite target and NOT read by the
  core restore path. This keeps it inside the operator's binding line ("the tool edits nothing but
  session-history artifacts"): capturing pack-time metadata is not editing a restored payload.
- **Landing:** the carrier and the floor's home-prefix needle land TOGETHER on the schema-act head
  (R-4.8), so no image ever carries the field without the needle that uses it, and vice versa.

## Sequencing / non-blocking

This does NOT block your current Arm-1 work or B2's current resume — B2 is completing its image-ID
union scope now under the ratified defer; only the home-prefix needle waits on this carrier. Run your
normal DESIGN → design-review → PLAN → IMPL lifecycle for the carrier; I reconcile the R-4.8 pointer
across the floor (consumer) and this act (author). R-4.8 is hard-gated before any release, so this
cannot be silently dropped. Matrix Wave-A's separate docs-lane INDEX refresh is unaffected by this.

ACTIONS_GIT_REF: no product/test edits at this seat — this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing; no bivpak code read/written this pass.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-PACKER-HOME-CARRIER-INTO-ARM1-SCHEMA-ACT-SCOPE-20260809-024150.md` → `s4-matrix.planner`
- R-4.8 pack-time packer-home carrier → into the Arm-1 schema act (manifest); backward-compatible; consumed only by the session-install verifier; carrier + needle land together, hard-gated before any release
- non-blocking: B2's current union-scope resume and your current Arm-1 work proceed; only the home-prefix needle waits on the carrier
