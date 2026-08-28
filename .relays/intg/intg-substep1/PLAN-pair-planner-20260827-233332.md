## PLAN — the ONE W-3-bound sub-step-1 plan: land the SEALED A6 rev14 consumer fabric (engine unwired) on `intg/consent-fabric` over base `02b51435`, in five tasks with the V-A6-3 one-commit contract landing, only the spine-assigned landing legs claimed, and one golden-byte STOP (STOP-1) gating the renderer task — routed to you for PLAN-REVIEW

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep1-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep1/RECONCILE-pair-planner-20260827-232251.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep1-master-answers/PLAN-master-planner-20260827-221931.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the W-3 waiver is EFFECTIVE for exactly this plan identity; your PLAN-REVIEW is the next gate; implementation starts only on my later bare dispatch token under the grant's delegated conditional authority; owner byte reviews, merge, publication, and release all stand ahead; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m3-addendum-7-4c40fe37-lock-20260827 (SEALED A7 rev2 — locked pin 4c40fe37…, post-stamp e4a6b982…, re-verified this seat)
THIRD_CONSUMED_CONTRACT: m1-addendum-M-2966b839-lock-20260825 (READ-ONLY hook contract M-R3; post-stamp 57d89625…)
PLAN_LOCK_ID: intg-substep1-plan-20260827
PLAN_ARTIFACT: PL-intg-substep1-20260827
PLAN_SHA256: b741eae21584ea9c774acb8c27dab09fea9e8bc545e91ce4dff2e0bf3fb020b6
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3 (master-confirmed; no rebase without a routed STOP)
BRANCH: intg/consent-fabric (dedicated worktree; the primary worktree's branch is never switched)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: PLAN — sub-step 1 in five tasks at docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md @ sha256 b741eae2: T1 flag+help closure (a6.18 golden home + a6.14 inert regression), T2 the ONE-COMMIT contract landing (both ErrKinds + both exit-map rows + all three schema sites + carriers + widened exit aggregator + derived parity rows + BOTH recomputed selftest pins + a6.17 structural selftests), T3 verb-scope a6.15 zero-state, T4 the PROMPT D renderer module BLOCKED on STOP-1 (two golden-byte cells routed to m-3 via master), T5 fence greps + macOS suite + Linux parity + IMPL report; only the spine-assigned landing legs claimed; review to approve/must-revise

## W-3 arm-(d) disclosure-by-class (on this plan's face, per the effective waiver)

This gated design-doc PLAN consumes SEALED designs whose DESIGN/DESIGN-REVIEW lineage lives in the pdc master tree, not this relay root, so relay-lint's cross-repo lineage class fires here by construction: the design-doc lineage gate cannot see a local same-owner `PHASE: DESIGN` or an approving `PHASE: DESIGN-REVIEW` for `DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825`.
The assurance of record is MANUAL BYTES-AND-APPROVAL VERIFICATION, already executed and re-executable: A6 rev14 live post-stamp `7ce2251d…` re-hashed EQUAL at this seat (pre-stamp blob re-derived EQUAL to the locked pin `c41d015f…` at commit `a633981`; approving chain m-3.implementer `100126` + VP package verdict `150851`); A7 rev2 live post-stamp `e4a6b982…` re-hashed EQUAL (locked pin `4c40fe37…` at `516a36c`; approving chain m-3.implementer `042911` + Master Reviewer `163228`; seal commit `3329bdf`).
The MEASURED fired set at this filed revision is reported UP to master in the accompanying fired-set relay for the W-3 coverage append; W-3 substitutes ONLY for this lint class — every other gate stands.

## The plan, bound

The locked plan is `docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` at the header digest; this relay summarizes, the artifact governs.

```text
scope      T1 src/cli/args.{hpp,cpp} + tests/test_cli.cpp (flag on pack/open; help
           line after --consent; a6.18 byte-whole golden; a6.14 inert-observable
           regression; NO explicit list/info parsing — RECONCILE I2)
           T2 ONE COMMIT (V-A6-3/R-3.43): error.{hpp,cpp} (+2 ErrKinds appended, kinds
           to_string'd), envelope.cpp exit rows (Refused->3, EntryRefused->2) +
           writer carriers (refusals array present<=>non-empty in encounter order;
           grouped url-divergence-accepted advisory on BOTH verbs, one outer object)
           + exit_for_open aggregator, main.cpp:363 call, NEW support/url_divergence.hpp
           structs, OpenReport/PackReport fields, schemas/biv-exit-map.v1.json +2 rows,
           schemas/biv-json-envelope.v1.schema.json all THREE A6-R1 sites,
           tests/test_envelope.cpp +2 DERIVED parity rows + carrier/aggregator units,
           harness/selftest/test_envelope.py BOTH pins recomputed + a6.17 (i)/(ii)/(iii)
           structural tests (RECONCILE I3 honored: the exit-map artifact is in the fence)
           T3 tests/test_cli.cpp a6.15 zero-state at real verb scope
           T4 NEW src/cli/url_consent.{hpp,cpp} + byte-equality units — BLOCKED on
           STOP-1; A7-R1 predicate is exactly isatty(stdin)&&isatty(stderr), NO json
           term (RECONCILE I4: prompt_requested / json-gated helpers are a forbidden
           pattern on the PROMPT D path, asserted at review)
           T5 fence greps (zero engine refs/includes/callers; repos fence intact; no
           persistence tokens; engine diff from base empty) + macOS suite with the new
           cases named-in-output + Linux parity (R-4.31 nofile, R-4.40 --init) + the
           IMPL report with the leg census and NOT-DONE list
legs       claimed at landing: a6.14, a6.15, a6.17, a6.18, zero-state half of a6.16
           (the 200932 spine's assignment); ALL behavioral legs due 2b (RECONCILE I5);
           R-3.4 honored — no executed-coverage claim for interactive arms
bars       R-4.47 folded: S3 + V3-shadow on every new text/predicate byte; V1-V5
           untouchable surfaces enumerated in the plan's Global Constraints
stop       STOP-1 (two golden-byte cells: PROMPT D terminal bytes; refusal-template
           leading-indent across its two carriers) — filed by this seat to master for
           m-3's cut; ONLY T4 waits on it
out        engine wiring/includes; format act; list/info impl; unlanded flags;
           PROMPT A/B/C + build_preview/render_prompt_b (R-4.24); persistence; PTY
           helper edits; behavioral legs; merge/push/publication/release
```

Boundary contract, acceptance criteria, out-of-scope lines, and the verification battery are in the plan artifact (§Global Constraints, §Acceptance criteria, §Out of scope, Task 5).

## Review asks

1. Verify the plan against the sealed bytes you already audited: does any task exceed what A6/A7 DETERMINE (V-A6-2/3 both directions), and does any R1 disposition fail to appear where you placed it (I2 T1, I3 T2, I4 T4, I5 legs table, I6 T5)?
2. The T2 one-commit boundary: confirm the commit's file set is exactly the V-A6-3 inventory and nothing contract-bearing leaks into T1/T3.
3. The a6·14 regression as written: inert-observable only — confirm it cannot be read as contractualizing stub trailing-token acceptance.
4. STOP-1's two cells: confirm they are the ONLY undetermined bytes you can find on the fabric's golden surfaces.
5. Verdict: `DESIGN_REVIEW_VERDICT`-style PLAN-REVIEW verdict (approve | must-revise) with findings at the exact plan bytes (`PLAN_SHA256` above).

On your approve, I issue the bare dispatch token under the grant's delegated conditional authority with the mechanical `SCOPE_DIFF` over the plan's file fence; deviation-present routes UP instead.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact at plans/PL-intg-substep1-20260827.md (sha256 above) and this relay via the engine; no product byte, no branch created yet (Task 0 belongs to the dispatched implementer)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the cross-repo lineage class this relay draws is the W-3-covered red, measured at the filed revision and reported UP
FINAL_GIT_STATUS_SHORT:
 ?? docs/sprints/2026-08-27-intg-consent-fabric/plans/
Literal path-scoped status for this seat's own writes at authoring time (RECONCILE.md's R1 section is already committed at b030d81; the plan artifact commits path-scoped with this relay); the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
