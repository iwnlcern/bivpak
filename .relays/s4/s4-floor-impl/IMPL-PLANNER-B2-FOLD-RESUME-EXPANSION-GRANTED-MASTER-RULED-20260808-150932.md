## IMPL — RESUME the B2 fold: the two-path `rewrite_common.{hpp,cpp}` expansion is GRANTED (BL2-2/BL2-7 only, bounded); master ruled B2-1 per-session (BL2-4 kept, no radius change) and B2-2 as the matrix schema act (manifest.cpp OUT). Fold BL2-1..BL2-3 + BL2-5..BL2-7 in one commit; the targeted re-panel with m-4 gates the replacement head.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the expansion is granted at the seat the standing conditions name; master ruled B2-1/B2-2; the fold proceeds under the live s4-floor-impl-2 authority; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-SCOPE-DEVIATION-20260808-143549.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: RESUME — full authority for the B2 fold: the granted two-path expansion + master's B2-1/B2-2 ruling + the re-panel gate; resume the clean branch at 54a6c54

Every held item is disposed. Resume the clean fold branch at exact `54a6c54`.

## 1. Scope expansion — GRANTED, bounded (orchestrator `150142`)
`src/adapters/rewrite_common.hpp` and `src/adapters/rewrite_common.cpp` enter the B2
dispatch universe for EXACTLY:
- **BL2-2** (Critical): the INDEPENDENT raw-text `.txt` verifier (bare `matches_at`, NO
  reuse of `boundary_ok`) + relocating the raw-text rewrite/verify typed-span API out of
  root `adapter.hpp` (which also clears the `bugprone-*` swap-guard bypass).
- **BL2-7** (Important): ONE shared spelling of the staging-sidecar schema/parser (the 96
  byte-identical lines), homed in the charter-reserved shared module.
The grant confirms both files already build and are already included by both adapters, so
NO new translation unit and NO CMake edit are needed.
**Out of bound — a NEW deviation back to the orchestrator BEFORE an edit:** any THIRD file;
a new TU or CMake change; any manifest/schema/workflow edit; any refusal-radius or design
change. The relocation is a MOVE of existing API into its charter-reserved home, not a new
surface. Re-run the SCOPE_DIFF after the expansion and confirm `all-in` before editing.

## 2. Master's ruling on the two above-pair items (orchestrator `145219`)
- **B2-1 / BL2-4 — RULED per-session; BL2-4 RELEASES. KEEP the per-session radius the code
  already carries — do NOT change it.** Master's basis: containment (no packer identity
  reaches the store) is preserved because the leaking session refuses so its bytes never
  land, and a verified-clean sibling carries no packer identity by definition; whole-set
  refusal was only collateral over-refusal. Two binding conditions: (a) BL2-1/BL2-2 land
  (the sound scan is WHY "clean" is trustworthy — per-session is safe only atop it); (b) the
  targeted re-panel CONFIRMS scan soundness with **m-4 ADDRESSED** on the containment
  invariant (the radius of a containment refusal IS its containment guarantee). Operator
  retains countermand; nothing waits on it.
- **B2-2 — the matrix Arm-1 schema act's, NOT yours.** The `locator`/`tier` enum is sealed
  F64; the parser accepting any non-empty string is a code↔sealed-contract gap, closed as
  implementation hardening in Arm-1's schema window. `manifest.cpp` stays fence-2 OUT for
  the floor — do not touch it.

## 3. The fold set (one amended commit at the one-commit head)
- **BL2-1** (Critical): `never_rewrite` artifacts must be VERIFIED. Do NOT merely restore
  the old `verify_scan` call (base was over-strict — a multi-line `.meta.json` hit the
  `decoded=false` auto-refuse). Add a third arm that leaves `output` untouched but runs a
  WHOLE-DOCUMENT origin scan (`count_hits_bytes` over the member, fail-closed, no
  line-structure), restoring `artifacts_checked` to the destination count; and key the
  exemption off the DECLARED inventory (`claude_code.cpp:321`), not the suffix fallthrough.
- **BL2-2** (Critical): the independent `.txt` verifier, per §1. Correctness's binding
  fix-shape: ONE fail-closed origin-scan floor across ALL THREE handling arms, not two
  separate patches.
- **BL2-3** (Important): drop the `start != 0U` clause in `strict_jsonl_decodable`
  (`adapter.hpp:377`) so an empty `.jsonl` decodes (zero records); reconsider branch-3
  emitting a 0-byte member.
- **BL2-4**: per-session KEPT as ruled — no code change.
- **BL2-5** (Minor / hardening, discretion): replace the codex `assert`+deref
  (`install.cpp:397,423`) and the unchecked `rollouts.find` (:452-453) with `.value()`/
  `.at()` or carry-forward as the claude leg does. Not merge-blocking; recommended.
- **BL2-6** (Important, tests): add the missing/vacuous falsifiers — a live==true
  interior-segment control; whole-file torn-tail; a well-formed decodable escaped-origin
  fixture that the CORRECTED scan must catch; multi-artifact torn-tail; the non-staged
  identity-mismatch refusal. The sealing tests at `test_adapter_claude_install.cpp:1982`
  (and the `artifacts_checked` 3→2 edits) must now assert REFUSAL, not the leak.
- **BL2-7** (Important): the shared sidecar parser + API relocation, per §1.

## 4. Fold discipline and the gate this head owes
Re-write/confirm FOLD_SCOPE `all-in` after the expansion, BEFORE any edit; one-commit law
and the required subject preserved; if either C1-anchored collect file changes, the A3
four-check ceremony re-fires at the new head (both anchors, five-owner receipts). Run the
host suite + the standing local Ubuntu 24.04 `linux/amd64` Docker suite (Actions unused),
deltas disclosed. Republish PR #23 under the standing publication disposition. Because
BL2-1/BL2-2 change install-time VERIFY semantics, the replacement head owes a TARGETED
RE-PANEL on the rewrite/verify surface (security + correctness + tests, cold lenses,
cumulative-window record, **m-4 addressed** on the containment invariant) — master-endorsed;
I run it after your report. Merge and release remain the operator's alone.

ACTIONS_GIT_REF: no product/test edits at this seat — this resume relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the implementation branch is clean at 54a6c54 pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-B2-FOLD-RESUME-EXPANSION-GRANTED-MASTER-RULED-20260808-150932.md` → `s4-floor.implementer`
- granted expansion `src/adapters/rewrite_common.{hpp,cpp}` (BL2-2/BL2-7 only, bounded) → resume authority
- BL2-1..BL2-3 + BL2-5..BL2-7 fold at one commit; BL2-4 per-session KEPT; manifest.cpp OUT → the full fold set
- targeted re-panel with m-4 on the containment invariant → gates the replacement head; my job after your report
- PR #23 at `54a6c54` → resume now; merge/release the operator's, hold ABSOLUTE
