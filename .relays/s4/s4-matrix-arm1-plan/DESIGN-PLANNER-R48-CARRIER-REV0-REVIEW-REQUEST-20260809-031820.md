## DESIGN — R-4.8 packer-home carrier rev0: one optional top-level `Manifest.packer_home` (operator ruled placement), captured from `Env.home` at pack, tolerated-absent both directions; DESIGN-REVIEW requested from the pair Implementer; floor CC'd to ratify the §7 consumer contract

ROLE: Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-PACKER-HOME-CARRIER-INTO-ARM1-SCHEMA-ACT-SCOPE-20260809-024150.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — the one design-level fork (placement) was ruled by the operator inline (option 1: top-level, written once); everything else is derived from the audited bytes; escalation returns only if the Implementer review finds the carrier cannot be made backward-compatible
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator, s4-floor.planner, m-4.planner
SUBJECT: DESIGN-REVIEW request — R-4.8 carrier rev0; verdict wanted: approve | must-revise | reject-narrow | human-decision-required

The master-directed R-4.8 scope addition (`…024150`) is designed. Doc (rev0):
`docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md`.

Shape in one paragraph: one OPTIONAL top-level field `Manifest.packer_home`
(`std::optional<std::string>`, JSON key `"packer_home"` after `source_path_flavor`),
captured at pack from the existing `Env.home` (`pack.cpp:239`), absolute pack-time home in
`source_path_flavor`'s flavor (same process, same host — no new flavor field). `$HOME`
unset/empty ⇒ field ABSENT (writer never emits empty; no third state). Parse via the
EXISTING `optional_string` helper (manifest.cpp:99 — the `SessionIds.parent` prior art):
absent/`null` ⇒ `nullopt`, wrong-type ⇒ `ParseError`, present-but-empty ⇒ `ParseError`
(malformed by construction). `format_version` stays 1, no `required_capabilities` entry,
no new `ErrKind` (D5 freeze untouched), both Step-3 fences untouched. Consumed ONLY by the
floor's session-install home-prefix needle (read once per image; absent ⇒ skip) — metadata,
never a rewrite target, never read by core restore; inside the operator's binding line.

Grounding: every upstream claim was re-verified at the bytes before design
(`SessionProvenance` home-less at manifest.hpp:24; `original_path` = workspace;
`Env.home` transient at pack.cpp:239; serialize cluster :481-484; parse cluster :553-557;
`optional_string` semantics :99-115). The placement fork (top-level vs per-entry
`SessionProvenance`) was the one genuinely design-level cell; the OPERATOR RULED option 1
(top-level, written once — the per-entry copy would make an impossible disagreement state
representable). That ruling is recorded in doc §2.

REVIEW ASKS (pair Implementer):
1. Compatibility: confirm at the bytes that the key-addressed dom parse ignores unknown
   top-level keys (old binary + new image) and that `optional_string` covers the new-binary
   + old-image direction — the F+G/enum-hardening posture in §6.
2. The empty-string-⇒-ParseError cell (§6/§8): agree it is the right hardening (writer
   never emits it) or argue the tolerate-as-absent alternative.
3. Test plan §9 sufficiency for the schema-act surface, incl. the pack-side env-controlled
   capture case.
4. Anything in §10's hard lines you believe the carrier cannot honor.

FLOOR (s4-floor.planner, CC — ratify or object at this review): §7 is your consumer
contract — key `"packer_home"`, top-level, optional string, absolute pack-time home in
`source_path_flavor`'s flavor, absent ⇒ skip the home-prefix check. Object NOW if your
needle needs a different shape (e.g. a separately-serialized username); silence past the
review is ratification per the landing gate (carrier + needle land together under R-4.8).

Return `DESIGN_REVIEW_VERDICT: approve | must-revise | reject-narrow |
human-decision-required`, parented to this relay, carrying the same DESIGN_DOC_ID. On
approve I file the design-completion SITREP and hold for PROCEED-TO-PLAN per lifecycle.
Non-blocking context unchanged: Wave-A is panel-clean and with master; B/C/D F-fenced;
zero-ref `capture_mode` cell awaiting m-1; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — the design doc (rev0) + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product/test edit.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260809-031820 before this relay + INDEX write; the design doc, this relay, and the INDEX row are the working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CARRIER-REV0-REVIEW-REQUEST-20260809-031820.md` → TO `s4-matrix.implementer`
- `docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md` → DESIGN_DOC_ID under review
