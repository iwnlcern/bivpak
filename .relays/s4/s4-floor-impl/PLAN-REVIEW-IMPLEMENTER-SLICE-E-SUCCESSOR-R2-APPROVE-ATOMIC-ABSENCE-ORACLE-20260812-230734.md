## PLAN-REVIEW — APPROVE successor R2; the atomic-absence oracle is executable and mutation-discriminating

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r2
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — W-1 remains effective; this verdict clears only the successor PLAN gate
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R2-ATOMIC-ABSENCE-ORACLE-20260812-224433.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R1-MUST-REVISE-NO-IMAGE-ORACLE-20260812-221451.md; .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R1-ARCHIVEWRITEFAILED-CARRIER-BOUND-20260812-220539.md; ../pdc/master/domains/m-1-format-engine/design/2026-08-11-ADDENDUM-J-session-child-parent-edge.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: APPROVE successor R2 — source-derived atomic absence plus the at-cap positive arm closes R3; carrier and checkpoints remain accepted

PLAN_REVIEW_VERDICT: approve

## R3 — PASS

The replacement oracle is executable at the real boundary and corrects the imprecise filename in my prior
review. At `origin/main` `0db8fdd`, `pack_impl` derives `name` from the source directory, then derives
`<source.parent_path()>/<name>.bvpk`, `.bvpk.partial`, and `.bvpk.spool`. Every post-derivation failure
flows through `cleanup_error`, which removes the partial and spool paths; the final image is created only by
the success-end partial-to-image rename. The plan now asserts those exact source-derived paths, never the
unrelated session-entry id, and starts each arm in a fresh parent directory. The assertions therefore observe
the files a broken producer would actually publish and cannot pass merely because the test named a path the
packer never uses.

The cap+1 in-process arm is complete: error rather than `PackReport`, exact `ArchiveWriteFailed`, both cap
and entry in operator-visible `detail`, correct `entry`/`cap`/`limit`/`observed` facts, and atomic absence of
all three output paths. The actual-binary text and JSON arms assert exit 4, their respective visible carrier
surfaces, and the same atomic absence. `with_temp_facts` adds only `partial_path` and `spool_path`; the four
selected cap fact keys do not collide and JSON already serializes the full facts map. These checks remain in
the already-authorized `tests/test_pack.cpp` and `tests/test_cli.cpp` paths.

The paired at-cap arm succeeds and round-trips the complete entry. That positive control makes the mutant
argument discriminating: truncation and whole-over-cap emission necessarily leave a final archive and fail
the absence arms, while refuse-everything fails the at-cap arm. No failed arm attempts to inspect a report or
archive whose required behavior is non-production. J's whole-entry, never-truncate producer closure is
therefore measured directly.

## Carried findings — PASS

R1 remains closed by the existing `ArchiveWriteFailed` carrier: exit 4, entry plus cap in `detail`, entry in
`path`, structured duplicate facts, and no error/report/CLI production-path widening. R2 remains closed by
the consistent checkpoints: Stage-0 assertion REDs `1a/3/4/6` and named GREEN controls at `0db8fdd`; after
the m-1 rebase, key-2 arm 2 GREEN as a dependency-integrity gate and assertion REDs `1b/4a/5`; only then the
single coupled Stage 1 and actual-binary E2E. Compile failure earns no behavioral-RED credit, and no
implementation byte may precede the RED observation for each key it greens.

Fresh evidence matches the plan's pins. Addendum-12 at `6eeeb157be249792d61774016485d97c303e2c8f`
hashes to full `29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb`; its live
status-stamped file hashes to disclosed `d0e2c6eb...`; J remains full `94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18`.
`origin/main` remains `0db8fdd8424d27aad2c547614e9ebb95621a2794`, where `SessionChild` still has only
`original_id` and `artifacts`; the m-1 receipt is absent.

## Gate result

The successor PLAN gate is approved. The Planner may dispatch the already-bounded Stage 0 under its standing
authority after the required token-time tuple re-verification. Stage 1 remains blocked on the m-1 receipt and
its post-rebase dependency checks. This verdict issues no implementation token itself and authorizes no
product/test write, branch publication, GitHub Actions, PR, merge, seal, publication, deployment, or release.
The release hold remains ABSOLUTE.

ACTIONS_GIT_REF: review-only — verified the incoming relay, current design/J hashes, origin/main and absent m-1 receipt, source-derived pack output paths and cleanup/rename order, existing BivError text/JSON/exit surfaces, and the exact mutant discrimination; this relay and its append-only INDEX row are the only writes from this act
RELAY_LINT: per D-3.4 — exact-file freshness lint before filing; INDEX tail re-read immediately before append; exact-file no-freshness and `--index` after append; active-root inherited structural results disclosed separately and never claimed green under W-1
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R2-APPROVE-ATOMIC-ABSENCE-ORACLE-20260812-230734.md
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
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R2-APPROVE-ATOMIC-ABSENCE-ORACLE-20260812-230734.md` -> `s4-floor.planner`
- APPROVE: the source-derived `.bvpk`/`.bvpk.partial`/`.bvpk.spool` absence oracle is executable in fresh directories for in-process and actual-binary text/JSON cap+1 arms
- APPROVE: the at-cap successful full round trip distinguishes required cap refusal from refuse-everything and completes the truncation/whole-emission mutant kill
- PASS carried: exact ArchiveWriteFailed carrier and corrected Stage-0/post-rebase checkpoints; no path widening
- m-1 receipt absent; Stage 0 may be dispatched only after the Planner's token-time checks; Stage 1 blocked; no Actions/merge/publication/release; hold ABSOLUTE
