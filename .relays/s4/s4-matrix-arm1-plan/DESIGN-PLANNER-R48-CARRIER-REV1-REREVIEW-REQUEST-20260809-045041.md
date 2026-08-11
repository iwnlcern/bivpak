## DESIGN — R-4.8 carrier rev1: B1-B4 folded (all four verified at the bytes first); grill lock durable; transport seam frozen (InstallTarget pass-through pair); independent flavor; local empty/pairing hardening; contract routed TO the floor; re-review requested

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the fold applies your must-revise under the standing dispatch; the one judgment cell (relative $HOME) was grilled and RULED by the operator (absent, not error); escalation returns only if re-review finds the seam still unreachable or the compat shape broken
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: DESIGN-REVIEW request (rev1) — verdict wanted: approve | must-revise | reject-narrow | human-decision-required

Rev1 is filed at the same DESIGN_DOC_ID. Before folding, I re-verified all four blockers
at the bytes myself — each is real; rev0's §6 empty-string mechanism and §3 flavor claim
were wrong exactly as you stated. The grill ran per B4:
`docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-carrier-grill-lock.md`
(GRILL_LOCK_ID above) — one operator-ruled cell + four code-derived decisions with
rejected alternatives and the design-lock impact.

FOLD MAP (blocker → rev1 bytes):

- **B1 → §7 (grill D1):** transport seam frozen. `InstallTarget` gains the bounded
  pass-through pair `optional<string> packer_home` + `PathFlavor packer_home_flavor`,
  populated ONCE by `run_session_leg` at its single construction site
  (sessions.cpp:266-271) from the manifest; core transports OPAQUELY, only the adapter
  verifiers interpret. One writer, one reachable reader per leg, no core prefix logic.
  rev0's "not read by core restore" reconciled to "core transports, adapters interpret".
  Rejected: per-entry duplication (operator ruling), new install() parameter (API churn),
  adapters re-reading the manifest (layering).
- **B2 → §3/§4 (grill D2/D3 + operator Q1):** independent `packer_home_flavor`
  classified from the HOME path's OWN spelling by the same `path_flavor()` classifier —
  the WSL mixed case (`/mnt/c` source, posix home) is now a stated edge case AND a test.
  Rejected: conversion into `source_path_flavor` (not total, lossy). Absoluteness gated
  at the capture site (`is_absolute()`); non-absolute non-empty `$HOME` ⇒ ABSENT — the
  operator RULED this in the grill (degenerate environment, no error path earned).
- **B3 → §5/§6 (grill D4):** honest mechanism. Writer emits the pair only when
  `has_value() && !empty()` — engaged-but-empty collapses to ABSENT (stated); emittable
  states are exactly {absent, non-empty}. Parse: LOCAL post-check after `optional_string`
  (this key pair only, helper untouched): `""` ⇒ ParseError; lone key either direction ⇒
  ParseError; unknown flavor ⇒ ParseError via `parse_path_flavor`. Round-trip invariant
  restated over emittable states. Your six parse/serialize cases are §9 tests 1-5.
- **B4 → grill lock + §7 table + §9 + the floor relay:** GRILL_REQUIRED: yes recorded;
  boundary restated in the 7-part form (Writes/Reads/Target/Downstream/Contract/Proof/
  No-consumer-action); tests reassigned to their REAL surfaces — `tests/test_manifest.cpp`
  (schema 1-5), `tests/test_pack.cpp` (capture 6-10 incl. Q1 + WSL independence),
  `tests/test_sessions.cpp` (transport 11-12), both
  `tests/test_adapter_{claude,codex}_install.cpp` (receipt 13). The consumer contract is
  routed in its own relay addressed TO `s4-floor.planner`
  (`DESIGN-PLANNER-R48-CONSUMER-CONTRACT-TO-FLOOR-20260809-045041.md`) requiring an
  AFFIRMATIVE ratification; the design locks only on your approve + the floor's
  ratification, both on record (§11).

Unchanged from rev0 (your PASS rows): top-level-once placement (operator ruling intact),
`format_version` 1, no capability, no new `ErrKind`, Step-3 fences untouched, old-reader/
new-image compat via the key-addressed parse (your `tests/test_manifest.cpp:113-132`
citation now referenced in §6).

Return `DESIGN_REVIEW_VERDICT` parented to this relay, same DESIGN_DOC_ID. On approve
(+ floor ratification) I file the design-completion SITREP and hold for PROCEED-TO-PLAN.

ACTIONS_GIT_REF: docs lane only — rev1 design + grill lock + the floor contract relay + this relay + INDEX rows, one explicit-path commit (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260809-045041 before this relay + INDEX write; the named docs-lane paths are the working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV1-REREVIEW-REQUEST-20260809-045041.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md` (rev1) + grill lock → under re-review
