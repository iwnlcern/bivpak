## PLAN-REVIEW artifact — MUST-REVISE revision 5 at 90187646: the 60-line census is not a semantic acceptance census; concrete enum and UnknownNote projection asymmetries remain; repo-id uniqueness contradicts unchanged parser acceptance

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-substep2a-plan-review-5
PARENT_DISPATCH_ID: intg-substep2a-plan
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-035914.md
RELATED_CONTEXT: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-025301.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035143.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — F1/F2 are exact plan corrections under O-R1/O-R4; F3 must route through master to m-1 if repo-id uniqueness is retained because adding it changes the currently accepted parser language despite the owner's unchanged-acceptance fence; the exact-hash re-review, W-5 concurrence/effectiveness, implementation, byte reviews, merge, push, publication, deployment, and release remain separately gated
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
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md at commit 3660fd7177a967baad69167164734ded68046534, sha256 90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; review filed from main@3660fd7177a967baad69167164734ded68046534
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index clean; uncommitted tranche-1 diff remains exactly 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over src/core/manifest/manifest.cpp and tests/test_manifest.cpp; no product byte or ref changed by this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MUST-REVISE exact 90187646 — F1 replace the ParseError-line count with a predicate-level, helper-expanded, outer-raw-note-aware acceptance census; F2 add writer clauses and refusal arms for invalid typed enum values and UnknownNote kind/raw canonicalization; F3 remove repo-id uniqueness or obtain m-1 authority to change parser acceptance; F4 correct the revision identity line

## Verdict

MUST-REVISE at exact SHA-256 `90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c`.

Revision 5 folds the prior four findings, including the owner's corrected C-4 text, the satisfiable C-2/C-3 arithmetic, and the empty status proof. Its replacement for prior F1 is still incomplete. Counting 60 `ErrKind::ParseError` emission lines cannot enumerate the parser acceptance language: individual lines combine several predicates, helper predicates live outside the span, and raw unknown-note reconciliation lives after it. Two concrete typed states then pass through gaps in the planned inventory while violating O-R4 projection identity. The plan also adds repo-id uniqueness although the retained parser does not enforce it, contradicting the owner-required unchanged acceptance language. No implementation token may parent to this review.

This is review-only. It authorizes no product, test, plan, branch, tag, index, ref, merge, push, publication, deployment, or release action.

## Findings

### F1 — Critical — a `ParseError` line census is not a census of semantic acceptance predicates

Plan lines 130-151 make the anchored count of 60 `ErrKind::ParseError` lines the census of record and require each line to map to one inventory clause or one parser-local category. That unit is not the parser language's semantic unit.

- One emission line can combine several independent predicates. At the retained tranche tree, `manifest.cpp:1150-1151` combines four required proof fields with `tip_sha` hex validity; `:1236-1244` combines required local-ref fields, SHA form, enum parsing, and the proof-presence relation; `:1520-1525` combines P1 decoding, byte cap, ref grammar, catch-all class, and strict ordering. One row cannot map one-to-one to those independently mutable clauses.
- Several called predicates are implemented outside the anchored span. `required_string`, `required_object`, `required_string_array`, and `parse_enum_field` reject through helpers whose own error sites precede line 1077. Counting the callers' aggregate return lines does not expand or prove those predicates.
- Repo-note raw preservation is completed outside the span. `raw_repo_note_values(text)` and the size/reconciliation checks at `manifest.cpp:1969-1984`, plus the outer simdjson refusal at `:1994-1997`, participate in whether a `repos[].notes[]` row is accepted and reconstructed, but the census stops before `parse_repo_entries` at line 1701.

The plan's Step-0 table can therefore classify all 60 counted rows while still omitting acceptance predicates and projection-only canonicalizations. The `FX-O-INV` count would then agree with an incomplete inventory.

Required correction: census semantic predicates, not error-emission lines. Expand shared helpers into the repo-field call sites, split compound conditions into independently mutable clauses, include the outer raw-note extraction/reconciliation path, and add a separate projection-canonicalization census for writer mappings that the parser accepts after changing the typed value. Bind each typed-expressible predicate/canonicalization to one writer refusal clause and one killing arm; retain the 60-line count only as a reproducible diagnostic, not completeness proof.

### F2 — Critical — invalid typed enums and `UnknownNote` mismatches are live O-R4 counterexamples omitted by the plan

The incompleteness is executable at the reviewed bytes, not theoretical.

**Typed enum values.** Plan lines 123-126 classify an unknown enum discriminant text as parser-local because “the enum is typed.” A scoped C++ enum can still hold an underlying value that is not one of its named enumerators. The writer helper `enum_field_name` maps every such value to `table.front()` (`manifest.cpp:821-825`) and is used for `RepoKind`, `HeadState`, `CaptureMode`, `EligibilityResult`, `RefAvailability`, and `ForcedPayloadReason` (`:896`, `:917`, `:922`, `:930-931`, `:947`, `:972`). A carrier with one out-of-domain typed enum value is silently serialized as a different valid enumerator; the parser accepts it; `pi_repo(parse(serialize(e))) != pi_repo(e)`. No parser rejection line exposes this writer canonicalization, so the planned 60-row classification and “unknown text is parser-local” rule omit it.

**Unknown notes.** The writer ignores `UnknownNote.kind` and substitutes `verbatim_json` directly (`manifest.cpp:1018-1023`). The parser derives `kind` from the raw object's member (`:1479-1491`) and only later restores raw bytes (`:1969-1984`). A typed `UnknownNote{kind = "future-a", verbatim_json = {"kind":"future-b"}}` is accepted by the proposed object-only check, serializes `future-b`, and parses with kind `future-b`, breaking the notes projection. If the raw kind is `promisor-source` or `non-carried-refs`, the parsed variant can change as well. Plan line 120 names only the requirement that unknown-note bytes form a JSON object; that is insufficient.

Required correction: enumerate the domain of every serialized enum and refuse unnamed typed values before emission, with per-field writer-refusal arms. For `UnknownNote`, validate one complete JSON object, require its string `kind` to equal the carrier's `kind`, require the discriminant to remain unknown rather than aliasing a structured known variant, and prove exact raw-byte round-trip. Add single-coordinate counterexamples for kind mismatch and recognized-kind aliasing. These are O-R1/O-R4 clauses even though no existing parser rejection line represents the writer-side canonicalization.

### F3 — Critical — repo-id uniqueness is not in the retained parser language and cannot coexist with the unchanged-acceptance fence

Plan line 120 places “repos[] id uniqueness” in the one inventory. The retained `parse_repo_entries` implementation (`manifest.cpp:1701-1719`) only parses and appends rows; it maintains no ID set and performs no duplicate-ID rejection. No such rejection appears in the 60-row census. Consequently either:

1. the writer alone refuses duplicate IDs, making its accepted projection narrower than the parser language and violating the stated O-R4 equality; or
2. the implementation adds a parser duplicate-ID refusal, changing parser acceptance and adding a new detail/error site, contrary to plan lines 123-127, 154, 170, and acceptance criterion 4, all of which bind parser acceptance and detail strings byte-unchanged under m-1 `034802` section 2.

Required correction: remove repo-id uniqueness from this act if it is not an existing sealed parser predicate, or route the exact conflict through master to m-1 for an explicit acceptance-language amendment and corresponding parser/test scope. Do not classify a predicate absent from the retained parser as “determined by the parser's acceptance language.”

### F4 — Important — the identity section still calls this artifact revision 4

Plan line 223 says “this artifact at revision 4,” while the banner, digest, carrier, and dead-prior list identify revision 5 and revision 4 as superseded. The exact digest prevents byte ambiguity, but the identity-of-record prose is false.

Required correction: change that one identity statement to revision 5 in the successor.

## Verified folds and unaffected surfaces

- Incoming carrier hashes to `77375232609324d1cae7778de87ed74bd20e3dd9dc9f944cd8d92be452e5c1e3`; the plan hashes to `90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c` at `3660fd7177a967baad69167164734ded68046534`.
- Sealed O re-verifies: live post-stamp `0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2`; blob at `40b4f7a3dbfc60e5ab742678bc4e77198845c243` = locked `63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577`.
- Retained tranche 1 is unchanged: HEAD `9e6ebe8fca2454164051573323dd7adfa2901219`, index empty, exactly two tracked modified files, diff `72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf`; file hashes remain `db50039e...` and `de98adc4...`.
- The plan's anchored count reproduces: 55 on the immutable `9e6ebe8` blob and 60 on the tranche-1 tree; fixed lines 1077-1700 reproduce 57 and 60. This finding challenges completeness of the unit counted, not those observed counts.
- Prior F2 is folded: the braced pack propagation arithmetic is `+5/-2`, each test TU is `+3/-1`, and the changed-line grep permits bare braces.
- Prior F3 is folded: m-1's corrected C-4 text is carried verbatim in substance and the writer-unit-only witness disclosure is explicit.
- Prior F4 is folded: the postcondition now requires an empty default `git status --short`.
- The ten-path allowlist, explicit staging/staged-tree proofs, no format bump/caller widening, both-platform battery, m-1/m-3 byte reviews, W-5 and release gates otherwise carry without a finding.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — review-only
- migration/backfill/destructive-write/canonical-data-repair: no — no product or canonical-data write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC O and m-1's unchanged-parser-acceptance ruling govern
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and restore parser semantics are user-visible
- test-runtime-role-mismatch: yes — line-count evidence is being used as a semantic-language proof
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — F3 would either narrow writer acceptance alone or change parser acceptance
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — not requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Correct F1/F2/F4 in the same plan identity. Route F3 through master to m-1 if repo-id uniqueness is retained; otherwise remove the unsupported clause. Reissue at a new exact hash and request PLAN-REVIEW. No tranche-2 implementation token may issue from this must-revise review; all W-5, m-1/m-3 byte-review, merge, push, publication, and release gates remain closed.

ACTIONS_GIT_REF: read-only review of plan commit 3660fd7177a967baad69167164734ded68046534 at sha256 90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c; sealed O, m-1 correction 034802, master carry 035143, retained code/tranche bytes, incoming carrier, parser helpers and raw-note reconstruction, enum writer mapping, pack propagation arithmetic, W-5 report, relay ledger, and current index/worktree state checked; daemon submission only; no product, test, plan, branch, tag, ref, merge, push, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result and digest will be re-verified after filing; inherited intg root-mode reds remain separately registered and are not changed by this review
FINAL_GIT_STATUS_SHORT: none — scoped status for the intg root and reviewed plan was empty before daemon submission; inherited s4 state exists outside this review scope and was untouched
