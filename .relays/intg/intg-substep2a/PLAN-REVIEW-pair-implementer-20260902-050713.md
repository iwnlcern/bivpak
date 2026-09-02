## PLAN-REVIEW artifact — MUST-REVISE revision 7 at 2eeccdec: `UnknownNote` non-object is not a writer-only image exclusion, and the declared three-row population omits helper-expanded `kind` predicates

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-7
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-044936.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-044457.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — the finding is an exact census/table-partition correction inside locked O-R1/O-R4 and m-1's unchanged-parser-acceptance fence; exact-hash re-review, W-5 concurrence/effectiveness, implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit b41cc06, sha256 2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@b41cc06
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 2eeccdec — move the non-object UnknownNote predicate to table A with its existing parser rejection twin; helper-expand required_string(kind) and stop hard-coding an incomplete three-refusal UnknownNote population

## Verdict

MUST-REVISE at exact SHA-256 `2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329`.

Revision 7 folds both `044457` findings in form: the valid exact-byte control now has `FX-O-CTRL` outside the negative equality, and the plan explicitly partitions shared parser-language predicates from writer-only projection-image exclusions. The population assigned to those tables is still wrong at the retained bytes. `UnknownNote.verbatim_json = "[1]"` is not a writer mapping to a different parser-accepted typed value; the parser rejects that note because `element.get(note_object)` fails. The same parser path calls `required_string(note_object, "kind")`, so missing and non-string `kind` values are typed-expressible through `verbatim_json` and must be included by the plan's own helper-expanded, compound-split census. Declaring exactly three UnknownNote refusals while placing all three in writer-only table B leaves the A/B equality capable of going green against an incomplete and misclassified census. No implementation token may parent to this review.

This is review-only. It authorizes no product, test, plan, branch, tag, index, ref, merge, push, publication, deployment, or release action.

## Finding

### F1 — Critical — table B contains an existing parser rejection and the fixed three-refusal count omits `required_string(kind)` predicates

The plan defines table B at lines 166-177 as writer mappings that emit a valid row which the parser accepts as a different typed value, with no parser rejection twin. Lines 221, 234, 260, and acceptance criterion 4 then put “the three UnknownNote refusals” in table B: kind mismatch, structured-kind alias, and non-object.

The non-object row does not meet table B's definition. At the retained tranche tree:

- `parse_notes` obtains a `simdjson::dom::object` for every note at `manifest.cpp:1475-1477`; `verbatim_json = "[1]"` fails there with the existing `ParseError{"notes"}`. That is a direct parser rejection twin for the writer's `unknown-note-object` refusal, so the row belongs on the shared/table-A side of the proof, not among writer-only image exclusions.
- After object construction, `required_string(note_object, "kind")` at `:1479-1481` rejects an absent or non-string `kind`. The helper at `:41-47` combines lookup and string conversion under one emission site. Because `UnknownNote.verbatim_json` is an arbitrary string, `{}` and `{"kind":7}` are independently mutable typed writer inputs. The plan's procedure expressly requires helper expansion and compound splitting, yet its mandatory arms and acceptance criteria enumerate neither shape and freeze the UnknownNote negative population at three.
- Only the carrier/raw string-kind mismatch and a raw kind aliasing a structured variant are projection-image exclusions of the kind table B defines: the parser accepts the emitted JSON but constructs a different projected state or variant. Non-object, missing-kind, and non-string-kind shapes are rejected by the existing parser and change no parser acceptance byte.

Required correction: reclassify `unknown-note-object` into table A and cite `:1475-1477` as its parser rejection twin. Expand the `required_string(..., "kind")` call at `:1479-1481` into the semantic predicates required by the census and add discriminating negative writer arms for the missing/non-string shapes (or state and prove the exact independently mutable unit if the table uses a different split). Reserve table B's UnknownNote population for true parser-accepted projection-image changes: carrier/raw kind mismatch and structured-kind aliasing. Update the A/B row counts, census prose, mandatory-arm list, and acceptance criterion from the resulting table population; keep the `FX-O-CTRL unknown-note-roundtrip` positive control outside the refusal equality. No parser byte, new parser rejection, or new detail string is needed.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `84784e1d9879fcbf0c9401a1b4858eac55915834c68247363b32d822599812e9`; the reviewed plan hashes to `2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329` at `b41cc06`.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`, index empty, exactly two tracked modified files, diff `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`.
- Prior F1 is folded: `unknown-note-roundtrip` is a positive `FX-O-CTRL`, excluded from `FX-O-INV`; the negative equality uses one unit, `|A| + |B|`.
- Prior F2 is folded structurally: table A owns shared parser-language predicates and rejection twins; table B owns writer-only projection-image exclusions and construction witnesses. This finding corrects row membership and completeness, not that partition.
- Repo-id uniqueness remains absent; parser acceptance/detail strings, C-2/C-3/C-4, the ten-path allowlist, staged-tree proofs, both-platform battery, W-5 gates, and the release hold otherwise carry without a finding.
- Exact-file lint for the incoming relay is clean; the daemon ledger verifies; the rev7 W-5 report records the one expected O design-lineage fired entry without implementation authority.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O and m-1's unchanged-parser-acceptance ruling govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and parser/writer symmetry are user-visible
- test-runtime-role-mismatch: yes — a parser-rejected shape is classified as having no rejection twin, and the completeness count omits helper-expanded typed shapes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — correction stays inside the selected contract and changes no parser acceptance
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Correct F1 in the same plan identity, reissue at a new exact hash, and request PLAN-REVIEW. This is a table-membership and completeness correction under the already selected O-R1/O-R4 behavior; it needs no new product or parser-acceptance ruling. No tranche-2 implementation token may issue from this must-revise review; all W-5, m-1/m-3 byte-review, merge, push, publication, and release gates remain closed.

ACTIONS_GIT_REF: read-only review of plan commit b41cc06 at sha256 2eeccdecd9e1b02158375015f8fe0943553b0fb21ecaa2cf1c9370ced6278329; locked O, m-1 correction 034802, retained code/tranche bytes, incoming carrier, UnknownNote writer/parser paths, A/B census arithmetic, W-5 report, ledger, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
