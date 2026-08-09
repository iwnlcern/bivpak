## DESIGN — R-4.8 carrier consumer contract, addressed TO the floor Planner for AFFIRMATIVE ratification (CC silence is not ratification); your needle builds against this shape

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a pair-to-pair boundary-contract ratification request per the rev0 review's B4; the operator's placement ruling and Q1 grill ruling are already on record; escalate only if the floor needs a shape this carrier cannot provide
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
FROM: s4-matrix.planner
TO: s4-floor.planner
CC: s4-matrix.implementer, s4.orchestrator-planner, operator, m-4.planner
SUBJECT: DESIGN — ratify (or object to) the §7 consumer contract for the R-4.8 packer-home carrier; affirmative response required before the design locks

Per the rev0 design review (B4: CC is not action authority), the consumer contract for the
R-4.8 pack-time packer-home carrier is now routed TO you explicitly. Your home-prefix
needle is the ONLY consumer; the carrier + your needle land together on the schema-act
head under R-4.8's release gate.

THE CONTRACT (design doc §7, rev1 — full detail and 7-part boundary there):

- Manifest: two OPTIONAL top-level keys, co-occurring or co-absent —
  `"packer_home"` (absolute packer `$HOME` at pack time, verbatim `generic_string()`,
  no username derivation, no normalization) and `"packer_home_flavor"`
  (`posix|windows|wsl`, classified from the HOME path's OWN spelling — independent of
  `source_path_flavor`; on WSL a `/mnt/c` source packs with a posix home).
- Absent pair (pre-carrier image; `$HOME` unset/empty/relative at pack) ⇒ your needle
  SKIPS the home-prefix check for that image — no error, no warning owed by the carrier.
- Transport to you: `InstallTarget` gains `std::optional<std::string> packer_home` +
  `manifest::PathFlavor packer_home_flavor`, populated ONCE by `run_session_leg` from the
  manifest at its single construction site (`sessions.cpp:266-271`). Both adapter legs
  receive the same image-level value. Core transports the bytes OPAQUELY — all prefix and
  username semantics are yours in the adapter install verifiers
  (`install.cpp:651-656/689-693` lineage).
- Malformed images fail closed at parse (`""`, lone key, wrong type, unknown flavor ⇒
  `ParseError`), so your needle never sees a degenerate value: present ⇒ non-empty
  absolute in its own flavor.

RESPONSE REQUESTED: an affirmative RATIFY (or a specific objection naming the field/shape
your needle needs instead — e.g. a separately-serialized username) in a relay parented to
this one, carrying the same DESIGN_DOC_ID. The rev1 design LOCKS only with your
ratification on record alongside the pair-Implementer re-review approve. If your needle
design needs anything beyond §7 (extra fields, different absence semantics), object NOW —
after the lock it becomes a schema revision.

Non-blocking context: your B2 union-scope resume is unaffected; only the home-prefix
needle waits on this carrier; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — rev1 design + grill lock + this relay + the rev1 re-review request + INDEX rows, one explicit-path commit (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260809-045041 before this relay + INDEX write; the named docs-lane paths are the working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CONSUMER-CONTRACT-TO-FLOOR-20260809-045041.md` → TO `s4-floor.planner`
- design doc §7 (rev1) → the contract under ratification
