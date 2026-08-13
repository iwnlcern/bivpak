## PLAN-REVIEW — R1 carrier and R2 checkpoint are closed; MUST-REVISE one impossible cap+1 archive oracle

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r1
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r1
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — this is one local executable-oracle correction; W-1 and the exact successor design approval remain effective and independent
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R1-ARCHIVEWRITEFAILED-CARRIER-BOUND-20260812-220539.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-MUST-REVISE-CARRIER-CHECKPOINT-20260812-213906.md; ../pdc/master/domains/m-1-format-engine/design/2026-08-11-ADDENDUM-J-session-child-parent-edge.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: MUST-REVISE successor r1 — keep ArchiveWriteFailed carrier and corrected checkpoints, but assert no output files after cap refusal instead of inspecting an archive J requires not to exist

PLAN_REVIEW_VERDICT: must-revise

## Prior R1 and R2 — PASS

The carrier choice is now executable without rediscovery or scope widening. At `0db8fdd`, text mode emits
only `ErrKind` plus `detail`, while JSON emits `kind`, `path`, `detail`, `errno`, and `facts`.
`ArchiveWriteFailed` is an existing typed enum used by pack-side producer validation and maps to exit 4.
The plan binds the offending entry and cap into operator-visible `detail`, duplicates the structured values
into `facts`, binds `path` to the entry, names both in-process and actual-binary assertions, and stops/routes
instead of inventing a new kind if review or implementation cannot preserve that four-file production scope.
That closes the prior carrier finding.

The checkpoint is also consistent now: key `1a` is a Stage-0 assertion RED at `0db8fdd`; only `1b`, key 2
arm 2, `4a`, `5`, and the schema-dependent E2E first become creditable on the combined tree. The compile-
failure exclusion, key-2 dependency stop, atomic key 5, and no-implementation-before-RED order all stand.

Fresh pin evidence also matches: Addendum-12 at `6eeeb157` hashes to full `29a5b3a3...`; its live stamped
file is `d0e2c6eb...` with only lock commit `6f2de0d` after the target; J remains full `94b6440c...`;
`origin/main` remains `0db8fdd` with `SessionChild {original_id, artifacts}` and no manifest `parent_id`.
Stage 1 therefore remains blocked on the m-1 receipt.

## R3 — the cap+1 oracle tries to inspect an archive that must not exist

The in-process oracle first correctly requires `pack()` to return an error rather than a `PackReport`, but
then requires that “no `agent_sessions` entry for that session exists **in the image**, and no truncated
`children[]` survives anywhere.” There is no image or report available to inspect under the behavior being
tested. J's producer-closure leg is explicit: cap+1 means **no `.bvpk` is produced**, no truncated tree is
emitted, and the error names cap plus entry.

The current pack implementation has the matching observable boundary. A failure flows through
`cleanup_error`, which removes `.bvpk.partial` and `.bvpk.spool`; the final `.bvpk` appears only after the
partial is renamed at the successful end. Existing atomic-refusal tests already prove this shape with
`CHECK_FALSE(std::filesystem::exists(root / "proj.bvpk"))`. Asking a failing test to parse the nonexistent
archive is therefore not executable and invites either a false fixture artifact or a weakened assertion.

Required revision — replace only that oracle, without reopening R1 or R2:

- Each in-process cap+1 arm starts with a fresh output directory, asserts the exact `BivError` contract,
  and asserts **absence** of `<entry>.bvpk`, `<entry>.bvpk.partial`, and `<entry>.bvpk.spool` after refusal.
- Each actual-binary text and JSON cap+1 arm uses a fresh output directory, asserts exit 4 and both names on
  the selected surface, and asserts the same three output paths absent.
- The matching at-cap arm still succeeds and round-trips the complete entry. That positive arm proves the
  fixture is packable at the boundary; the cap+1 no-output arms kill both truncation and whole over-cap
  emission because either mutant necessarily publishes an archive.
- Do not claim that an `agent_sessions` vector or `children[]` was inspected after an error. There is no
  successful report/archive to inspect. The observable is atomic absence, exactly as J specifies.

No production or test path widens: the correction stays within `tests/test_pack.cpp` and
`tests/test_cli.cpp`. The selected `ArchiveWriteFailed` kind, detail/path/facts mapping, exit 4, wording
constraint, three semantic killing arms, exact Stage-0 scope, coupled Stage 1, A3, macOS/local-Docker
verification, remote-Actions hold, W-1 tuple recheck, publication hold, and release hold otherwise stand.

## Gate result

The PLAN gate remains red for this single successor correction. No Stage-0 dispatch and no Stage-1 token
follow from this verdict. No product, fixture, schema, harness, branch, PR, GitHub Actions, merge, seal,
publication, deployment, or release action is authorized; the release hold remains ABSOLUTE.

ACTIONS_GIT_REF: review-only — verified incoming relay structure, exact current design/J hashes, origin/main and absent m-1 schema receipt, current BivError rendering/exit mapping, J's no-bvpk producer-closure leg, pack.cpp cleanup/rename order, and existing atomic-refusal test precedent; this relay and its append-only INDEX row are the only writes from this act
RELAY_LINT: per D-3.4 — exact-file freshness lint before filing; INDEX tail re-read immediately before append; exact-file no-freshness and `--index` after append; active-root inherited structural results disclosed separately and never claimed green under W-1
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R1-MUST-REVISE-NO-IMAGE-ORACLE-20260812-221451.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R1-MUST-REVISE-NO-IMAGE-ORACLE-20260812-221451.md` -> `s4-floor.planner`
- PASS: exact `ArchiveWriteFailed`/detail/path/facts/exit-4 carrier with text and JSON oracles; no scope widening
- PASS: key `1a` at Stage 0 and the combined-tree checkpoint restricted to schema-dependent arms
- MUST-REVISE R3: cap+1 refusal asserts no `.bvpk`, `.bvpk.partial`, or `.bvpk.spool`; do not inspect an archive/report that the required failure does not produce
- m-1 receipt absent; plan red; no dispatch/token/Actions/merge/publication/release; hold ABSOLUTE
