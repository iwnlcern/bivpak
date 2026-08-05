## DESIGN REVIEW — floor-fold integration shape must revise before plan

ROLE: Implementer
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-design-review
PARENT_DISPATCH_ID: s4-floor-design
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — pair Planner revision is sufficient; H1/H2/H3 and fence 2 remain upstream holds
DESIGN_DOC_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: must-revise
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-REVISE — correct carrier ordering, warning/torn-tail consumers, E3 mirror runtime, and verdict-state contract

## Review basis

- Exact design doc: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md`, SHA-256 `32bdf2a3c0e162b10e77df05576d12451ce090d624a3e2f2e610cd6535c34bfb`.
- Design filing commit: `666768e98c8766fbbd9ba096f9f46180aa7896c8`.
- Locked A7 SHA-256: `2e4020571d464b6a61d7d7eba3e7966987932494bb355b10bff4a8fb4b6624da`.
- Sealed A3.3: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-12-ADDENDUM-3-real-session-import.md:206-233`.
- Sealed A9/F64: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md:278-298`.
- R-3.25 disposition: `../pdc/master/relays/s375-build-standup/DESIGN-PLANNER-M2-GATE3-MEASURED-TWELVE-RECEIPTS-CIRCULARITY-G5-DISPOSED-20260804-170500.md:135-217`.
- Reconciled audit base: `docs/sprints/2026-08-04-s4-step4/RECONCILE.md:64-120`.

The `DESIGN_DOC_ID` and parent lineage match the review request. The holds are not silently closed. No product semantics are invented for H1/H2/H3.

## Required revisions

### R1 — D3 must place admission before consent-no staging

The design says the current consent-denied branch becomes an adapter call (`design:55`), but that branch currently executes at `src/core/open/sessions.cpp:213-225`, before capability/store admission at `:227-243` and before the store-write gate at `:245-258`. Replacing it in place would call `install(..., Consent::no)` for an unreadable or absent host/store.

That contradicts locked A7's five-stage table:

- absent/unreadable are agent-level gates with zero adapter calls (`A7:433-440`);
- consent-no staging is reachable only after the readable host is admitted (`A7:442`);
- direction and basis-grammar refusals remain per-session adapter outcomes (`A7:444-445`).

Required design correction: state the reordered carrier explicitly. Archive-only filtering remains pre-consent in held slice D; for ordinary entries, absent/unreadable/store-missing terminates before consent dispatch; only a readable, present target reaches the adapter; then consent selects host-store versus workspace-staging destination. Define which successful staged results contribute to the one A9 sidecar and what happens to staged bytes if the aggregate sidecar write fails or a sibling adapter returns failure.

The D3 ownership choice itself is compatible with the seals: A9 pins one path and three content members, not a per-adapter writer. A single orchestration writer is acceptable once its ordering, aggregation, publication, and failure boundary are explicit.

### R2 — B1/B2 omit required default-output consumers and therefore invalidate the disjoint-slice claim

The design says B1's warning rides the existing `SessionLiveAtPack` warning (`design:68`). At the pinned product tree, `src/cli/main.cpp:44-50` renders only prune advisories for non-JSON `pack`; it never emits `PackReport.warnings`. Merely appending the existing warning in `src/core/pack/pack.cpp:563-566` is not the required default-visible warning from the `170500` acceptance criteria (`:173-183`).

The B2 boundary says its downstream consumer is install only (`design:94`). Sealed A3.3 additionally requires branch 3 to record `torn_tail_dropped`, surface it in the pack summary, and derive the open-time caveat from persisted `live_at_pack` (`A3.3:220-225`). Those writer/reader pairs and their structured report/envelope/text surfaces are absent from the boundary contract.

Required design correction:

- assign the non-JSON and JSON/default pack rendering ownership for B1's MAY warning;
- name the structured carrier for `torn_tail_dropped {artifact, bytes}` from collect through `PackReport` and pack output;
- retain A3.3's open caveat and branch-4 install refusal as separate consumers;
- replace `B2`/`E` “parallel-safe: disjoint files” (`design:86`) with an exact cluster/ownership statement. B2 now demonstrably reaches pack reporting and likely the shared CLI/report surfaces; parallel safety must be proven from named files, not asserted from slice labels.

### R3 — §A7.10's in-repo mirror must migrate the live E3 runtime, not only its scenario and scraper

Slice A names only `harness/scenarios-e3/e3-dual-resume.json` and `harness/selftest/test_e3_asserts.py` (`design:71,127`). The actual E3 runtime still consumes `validated_version_prefixes` in `harness/bivharness/e3.py:758-778` and calls that predicate on the live host path. Its rule is literal prefix membership; a readable forward host above the old prefix set remains rejected even if the product allowlist is deleted.

Required design correction: include `harness/bivharness/e3.py` and its schema/selftest consumers in slice A's same-commit mirror boundary. Replace the retired prefix-admission contract with a representation that mirrors both MIN and `surveyed_through` while preserving the CLI-probe grammar/readability oracle. The scenario, product constants/call sites, runtime E3 consumer, and in-repo pin check must move together. H3 still holds the external PDC RUNCARD leg.

### R4 — D2 needs a canonical state and wire mapping

The proposed `Verdict {readable, unreadable, absent}` plus `newer_than_survey` is a defensible interpretation of A7's cardinality note (`A7:556-560`), but `design:37-44` leaves two ambiguities:

1. the struct can still represent `unreadable + true` or `absent + true`; “meaningful only when readable” is not a normalization invariant;
2. locked §A7.9 names the externally meaningful state `readable_newer_than_survey` (`A7:575-583`), while the design names envelope/schema rewires without specifying whether the wire carries a verdict spelling, a separate boolean, or both.

Required design correction: pin the construction invariant (`newer_than_survey == false` unless verdict is `readable`), the host-version presence rule, and the JSON/text mapping. If the public verdict remains `readable-newer-than-survey`, define its deterministic derivation from the internal pair; if the wire changes to verdict plus boolean, state that contract and its compatibility/test consequences.

### R5 — slice D cannot scope an entirely absent verb to one status without a base contract

The design scopes `list`/`info` “minimally to archive-only status rendering” (`design:79,132`), but `src/cli/main.cpp:390-394` rejects both verbs wholesale as `NotYetImplemented`. There is no existing ordinary-entry list/info surface into which archive-only status can be inserted.

Required design correction: while D remains H2-held, name one of these shapes for its later restatement:

- a dependency on a separately owned base `list`/`info` implementation, with its landed SHA/interface; or
- the minimum complete semantics for ordinary plus archive-only entries needed to make the verbs coherent, explicitly routed if that expands ownership.

Do not describe implementing a whole missing verb as archive-status-only scope.

## Reviewed and accepted design points

- **D1 shared unit:** acceptable. One parser/comparator/constants home with per-leg call sites preserves per-leg mutation falsifiability, provided R3's full live mirror is included.
- **Pack MIN omission in slice A:** genuinely manifest-free. `src/core/pack/pack.cpp:533-575` can classify and omit a session before `manifest_entry_for` and before artifact spooling; omitted sessions never reach `Manifest.agent_sessions`. The skip-loud report still needs an explicit report/render contract.
- **D3 single A9 writer:** compatible in ownership with sealed A9/F64; revise ordering and failure semantics per R1.
- **B1 before Codex B2 branch 3:** correct and sealed-disposition compliant.
- **Receipt denominator:** §6 expands to 18 exactly, and none of the 18 mutation-receipt keys itself ends in `-exact`. The parameterized 30 exact-row comparators preserve H1. For the O4 receipts, retain raw observed sibling state while the exact-row comparator remains unasserted; do not call that sibling green before the H1 ruling.
- **H2/H3/fence handling:** correctly held rather than self-resolved.

## Boundary and acceptance review

Boundary contracts exist for all unheld slices, but B2 is incomplete until R2 and D is intentionally deferred under H2. Acceptance shape is adequate for B1 and receipt mutation cadence; R1, R2, R3, and R4 need explicit tests added to the revised design so the later PLAN can be mechanically reviewed.

Required revised-design tests at minimum:

- unreadable/absent/store-missing plus consent-no produces zero adapter calls and zero staging;
- readable admitted consent-no stages bytes, aggregates exactly one sealed-member sidecar, and defines sidecar-publication failure behavior;
- non-JSON pack displays exactly one MAY warning for live Codex and none for terminal negative control;
- B2 branch 3 emits exact artifact/byte facts in default pack output; open caveat and branch-4 typed refusal remain separately asserted;
- E3 accepts a grammar-valid readable forward host outside the retired prefixes while the constants and scenario mirror remain exact;
- every serialized D2 state obeys the proposed invariant and has one deterministic wire spelling.

ACTIONS_GIT_REF: no product/test/harness/schema/design-doc edits claimed; this review relay and its append-only INDEX row are the only seat writes, for an explicit-path docs-lane commit after author-side lint.

FINAL_GIT_STATUS_SHORT: filing snapshot before the required explicit-path docs-lane commit; exact output follows.

```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-design/DESIGN-REVIEW-IMPLEMENTER-20260805-002131.md
```

## Next action

Revise the same `DESIGN_DOC_ID`, preserving the accepted decisions and all upstream holds. Return a new DESIGN review request; do not advance to PLAN from this verdict.
