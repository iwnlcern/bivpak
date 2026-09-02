## PLAN-REVIEW artifact — MUST-REVISE revision 8 at ed066822: `UnknownNote.verbatim_json` validity/full-consumption predicates remain unenumerated, and its rejection twins cannot be consumed post-build as claimed

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-8
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-051116.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-050713.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — both findings are executable-census corrections inside locked O-R1/O-R4 and m-1's unchanged-parser-acceptance fence; exact-hash re-review, W-5 concurrence/effectiveness, implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit c81c1a1, sha256 ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@c81c1a1
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact ed066822 — split the `UnknownNote.verbatim_json` object rule into its independently mutable JSON-validity, single-value/full-consumption, and object-type predicates with discriminating refusal arms; describe the raw-note parser twins as pre-build enforcement rather than impossible post-build table consumption

## Verdict

MUST-REVISE at exact SHA-256 `ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f`.

Revision 8 correctly folds `050713`: non-object, absent-kind, and non-string-kind are now table-A rows with their retained parser rejection twins; carrier/raw kind mismatch and structured-kind aliasing remain the two table-B image exclusions; the control is outside the negative equality; no A/B total is hard-coded. The remaining `unknown-note-object` row nevertheless bundles independently mutable raw-JSON predicates while its sole mandatory arm, `[1]`, exercises only object type. Because `UnknownNote.verbatim_json` is an arbitrary typed string and the writer substitutes it into the complete manifest without escaping, malformed JSON and an object followed by another JSON value are additional typed-expressible states whose emitted manifests the retained parser rejects. A validator that checks only top-level object shape can pass every named rev8 arm while still silently emitting either invalid image. The plan's own helper-expanded, compound-split census and locked O-R1/O-R4 therefore are not yet executable-complete.

The same rows expose a structural contradiction: lines 187-189 and acceptance criterion 4 require table A to be consumed whole by parser-side `repo_row_violation` post-build, but a malformed/non-object/absent-kind/non-string-kind note never constructs an `UnknownNote` row. `RepoRowFacts` contains only the built `RepoEntry` plus three unrelated wire-presence bits. As m-1's `034802` ruling already permits for O-R2, these raw-note predicates can share the semantic inventory while their parser twins execute pre-build; the plan must say that explicitly rather than require impossible post-build consumption.

This is review-only. It authorizes no product, test, plan, branch, tag, index, ref, merge, push, publication, deployment, or release action.

## Findings

### F1 — Critical — the single `[1]` arm does not cover JSON validity or exact-one-value consumption

The carrier permits any `std::string` at `types.hpp:180-184`. The retained writer places a quoted placeholder at `manifest.cpp:1017-1021`, then replaces that quoted token directly with `unknown.verbatim_json` at `:1806-1809`. Thus at least these coordinates are independently mutable:

- syntactic validity: a string such as `{"kind":"future"` is not a complete JSON value;
- full consumption / exactly one value: `{"kind":"future"}{"kind":"later"}` begins with a valid object but contains trailing JSON;
- top-level object type: `[1]` is valid one-value JSON but not an object.

The complete manifest parser rejects the first two before or during its DOM/on-demand parse (`parse` catch at `:1952-1955`; `raw_repo_note_values` at `:1415-1436`), while `parse_notes` rejects the third at `:1451-1454`. All are typed-expressible through `UnknownNote.verbatim_json`, so `034802` lines 60-66 and O-R1/O-R4 require writer-refusal witnesses. Rev8 line 133 calls the combined clause “exactly ONE JSON object,” but the procedure at lines 157-170 requires one row per independently mutable predicate and the mandatory inventory at line 243 supplies only `[1]`. That arm cannot kill a validator that accepts any string beginning with `{`, parses only the first value, or otherwise omits full-consumption validation.

Required correction: split and name the semantic predicates needed to establish (1) valid JSON, (2) exactly one fully consumed JSON value, and (3) object type, or state an equivalent mechanically testable decomposition. Add one single-coordinate negative writer arm per independently mutable row, cite the retained parser rejection path for each, and let `|A|` derive from the corrected Step-0 table. Preserve the existing `{}`, `{"kind":7}`, kind-mismatch, structured-alias, and exact-byte positive-control arms. No parser byte, rejection, kind, or detail string needs to change.

### F2 — Major — parser-side whole-table post-build consumption is impossible for the raw-note rejection rows

Rev8 lines 187-189 say every table-A row is “shared, consumed whole at both enforcement points.” Line 230 says `kRepoRowClauses` holds the predicates over parser-constructible rows and that parser post-build enforcement is through `repo_row_violation(const RepoRowFacts&)`; acceptance criterion 4 again says the shared table is consumed whole by that post-build function, carving out pre-build execution only for the seven O-R2 paths.

The three already named raw-note rejection rows, plus F1's validity/full-consumption rows, cannot satisfy that structure. A rejected raw note produces no `UnknownNote`, and the declared `RepoRowFacts` at lines 83-88 carries neither raw note values nor a pre-build note object. The retained rejection sites are necessarily pre-build (`element.get(note_object)` and `required_string`), just as the O-R2 path predicates are pre-build. m-1 `034802` lines 75-88 explicitly rules that O requires one SEMANTIC inventory, not one function, and permits pre-build parser enforcement while holding acceptance/details unchanged.

Required correction: extend the helper-path carve to the raw-note shape predicates. State that their table-A membership is semantic, the writer consumes their clauses over `verbatim_json`, and the parser twins execute at the existing pre-build/raw-parse sites; do not require `repo_row_violation(RepoRowFacts)` to consume rows it cannot observe. Update lines 187-189, 230, 242, Step 3, the (c) census, and acceptance criterion 4 consistently. Keep the one-inventory proof, rejection twins, and unchanged-parser fence.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `585979785664984e37373a2a0b69ac9f99da10a1de129e246baa0a4b7a87976e`; the reviewed plan hashes to `ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f` at `c81c1a1`.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`, index empty, exactly two tracked modified files, diff `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`.
- Prior F1 is fully folded in row membership: non-object, missing-kind, and non-string-kind are A; mismatch and structured alias are B; the exact-byte control is outside `FX-O-INV`; A/B populations derive from Step 0.
- Repo-id uniqueness remains absent; parser acceptance/detail strings, C-2/C-3/C-4, the ten-path allowlist, staged-tree proofs, both-platform battery, W-5 gates, and the release hold otherwise carry without a finding.
- Exact-file lint for the incoming relay is clean; the daemon ledger verifies; the rev8 W-5 report records the one expected O design-lineage fired entry without implementation authority.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O and m-1's unchanged-parser-acceptance ruling govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and parser/writer symmetry are user-visible
- test-runtime-role-mismatch: yes — the arm set cannot distinguish object type from JSON validity/full consumption, and post-build enforcement cannot observe rejected raw-note shapes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — corrections stay inside the selected contract and change no parser acceptance
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Correct F1/F2 in the same plan identity, reissue at a new exact hash, and request PLAN-REVIEW. These are census completeness and enforcement-location corrections under the already selected O-R1/O-R4 behavior; they need no new product or parser-acceptance ruling. No tranche-2 implementation token may issue from this must-revise review; all W-5, m-1/m-3 byte-review, merge, push, publication, and release gates remain closed.

ACTIONS_GIT_REF: read-only review of plan commit c81c1a1 at sha256 ed06682276d6e55993a6d9db909f62c852c0398cf1b3b7d3c4cde3d36c06210f; locked O, m-1 correction 034802, retained code/tranche bytes, incoming carrier, UnknownNote writer/parser/raw-replacement paths, A/B census semantics, W-5 report, ledger, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
