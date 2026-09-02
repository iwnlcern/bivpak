## PLAN-REVIEW artifact — MUST-REVISE revision 6 at 7254e04a: the new `FX-O-INV` equality counts a positive identity control as a refusal clause; projection-only writer clauses are simultaneously declared writer-only and parser-twinned

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-6
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-042939.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-042346.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035143.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — both findings are exact plan-proof corrections inside locked O-R1/O-R4 and m-1's unchanged-parser-acceptance fence; exact-hash re-review, W-5 concurrence/effectiveness, implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 03f99b8a21e8b4e81730c4dcdf028590f1defa64, sha256 7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@03f99b8a21e8b4e81730c4dcdf028590f1defa64
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 7254e04a — F1 separate the valid UnknownNote raw-byte identity control from the refusal-clause marker equality; F2 distinguish shared parser-language predicates from writer-only projection-image exclusions instead of requiring every canonicalization clause to have a parser rejection twin

## Verdict

MUST-REVISE at exact SHA-256 `7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6`.

Revision 6 folds all four findings from `042346` at the intended semantic surfaces: the census unit is now the independently mutable predicate, helpers and compounds are expanded, the post-span note path and a projection-canonicalization census are named, the six enum-domain and UnknownNote counterexamples are mandatory, repo-id uniqueness is removed, and the revision identity is corrected. The successor nevertheless makes its new mechanical proof unsatisfiable as written. It counts a successful exact-raw-byte identity control among `FX-O-INV` refusal-clause arms while requiring that marker count to equal only typed-expressible predicate rows. It also says the new projection-canonicalization clauses are writer-only with parser behavior untouched, then requires every writer clause to have a parser twin under one table consumed whole at both enforcement points. No implementation token may parent to this review.

This is review-only. It authorizes no product, test, plan, branch, tag, index, ref, merge, push, publication, deployment, or release action.

## Findings

### F1 — Critical — the `FX-O-INV` count cannot simultaneously include four UnknownNote arms and equal the refusal-predicate row count

Plan lines 173-175 define the invariant as one `FX-O-INV` killing arm for every typed-expressible row, each row becoming a writer-refusal clause. Line 221 then places four UnknownNote arms under that marker grammar: three negative/refusal arms (`unknown-note-kind`, `unknown-note-aliases-structured`, `unknown-note-object`) and `unknown-note-roundtrip`, explicitly a positive control that must serialize, parse, and preserve non-canonical spacing exactly. Line 247 requires `grep -c 'FX-O-INV '` to equal the PREDICATE TABLE's typed-expressible row count and says the four UnknownNote arms are among that count; acceptance criterion 4 repeats that every typed-expressible predicate has a writer-refusal arm while requiring four UnknownNote arms.

The fourth arm cannot satisfy that grammar:

1. If `inv.unknown-note.roundtrip` carries `FX-O-INV`, the grep count contains a successful identity control that is neither a refusal clause nor a killing arm for an invalid typed state; the count exceeds the stated refusal-predicate population or the table must misclassify a positive contract as a refusal predicate.
2. If it does not carry `FX-O-INV`, the grep count contains only three UnknownNote arms, contradicting line 247's explicit four-among-the-count statement and the line-221 heading.

This is not cosmetic marker spelling. The grep equality is the planned mechanical completeness proof m-1 re-runs, so either branch can report a false census.

Required correction: give the valid raw-byte round-trip control its own positive-control tag and exclude it from the refusal-clause equality. Define the refusal count as the union of typed-expressible parser-language predicates and refusal-bearing projection-canonicalization rows, with one negative arm per row. State separately that the three UnknownNote refusals plus one positive exact-byte control are present. If a different arithmetic is intended, enumerate its table domains and expected equality so a single grep cannot count unlike units.

### F2 — Important — projection-only image exclusions are declared writer-only and parser-twinned at the same time

The second census at lines 166-172 correctly identifies enum fallback and UnknownNote substitution as writer mappings that turn one typed state into a different parser-accepted state, makes them writer-refusal clauses, and says the parser's existing behavior is untouched. Those are image-domain exclusions: an unnamed enum carrier, an `UnknownNote` carrier/raw-kind mismatch, and an UnknownNote raw kind that aliases a structured variant are not typed states the parser can construct in the same form. The parser either rejects an unknown enum TEXT before row construction, derives the UnknownNote carrier kind from the raw member, or constructs a different structured note variant.

But line 220 says every writer clause has a parser twin because both points call `repo_row_violation`; line 225 puts every typed-expressible census clause in the shared inventory; and acceptance criterion 4 requires one shared table consumed whole by both points and “every writer clause a parser twin.” Applied to the projection-only rows, that requirement is either vacuous (the parser calls a clause on a state that can never violate it), false (there is no matching parser rejection), or acceptance-changing (a new parser rejection is added, forbidden by `034802` section 2). The plan does not state which interpretation m-1 should verify.

Required correction: partition the proof explicitly. Keep the shared two-point table and parser-twin requirement for predicates over parser-constructible repo rows. Put writer-only projection-image exclusions in a separately named validator/table whose proof obligation is O-R1 refusal plus the single-coordinate O-R4 counterexample arm, while the parser's construction/variant behavior is cited as the reason no rejection twin exists. Alternatively, define “parser twin” precisely as a non-rejecting construction/domain witness and adjust the consumed-whole and arm claims so they do not assert a rejection twin. Parser acceptance and detail strings remain byte-unchanged either way.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `3cd43b7b4834bb141145a29ec0f91fbae92164ad80cd38989cb9764a347795d5`; the reviewed plan hashes to `7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6` at `03f99b8a21e8b4e81730c4dcdf028590f1defa64`.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`, index empty, exactly two tracked modified files, diff `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`.
- Prior F1 is folded in substance: semantic predicates replace ParseError lines as the unit; helpers are expanded, compounds split, post-span note reconciliation included, and the 60-line count is diagnostic only.
- Prior F2 is folded in substance: all six enum domains and the UnknownNote object/kind/alias/raw-byte contract are named with concrete arms.
- Prior F3 is folded: repo-id uniqueness is absent from the act, with the unchanged-parser-language grounds stated.
- Prior F4 is folded: the identity says revision 6.
- The prior C-2/C-3 arithmetic, corrected C-4 text, empty-status proof, ten-path allowlist, staged-tree proofs, both-platform battery, m-1/m-3 byte reviews, W-5 gates, and release hold otherwise carry without a finding.
- Exact-file lint is clean, the daemon ledger verifies, and the rev6 W-5 report records the one expected O design-lineage fired entry without granting implementation authority.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O and m-1's unchanged-parser-acceptance ruling govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and parser/writer symmetry are user-visible
- test-runtime-role-mismatch: yes — a positive identity control is counted as a negative refusal-clause completeness witness
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — the parser-twin requirement is ambiguous for writer-only projection-image exclusions
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Correct F1 and F2 in the same plan identity, reissue at a new exact hash, and request PLAN-REVIEW. These corrections do not require a new product or acceptance-language ruling: they make the proof grammar match the already selected O-R1/O-R4 behavior and preserve m-1's parser fence. No tranche-2 implementation token may issue from this must-revise review; all W-5, m-1/m-3 byte-review, merge, push, publication, and release gates remain closed.

ACTIONS_GIT_REF: read-only review of plan commit 03f99b8a21e8b4e81730c4dcdf028590f1defa64 at sha256 7254e04a0fa13c2a2446bc246a2886f99ecaad408cdead8b813bf7ee2e05c3f6; locked O, m-1 correction 034802, master carry 035143, retained code/tranche bytes, incoming carrier, enum and UnknownNote writer/parser mappings, marker arithmetic, W-5 report, ledger, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
