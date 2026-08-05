# s4-floor fold — integration-shape design under the LOCKED A7 (rev2)

DESIGN_DOC_ID: s4-floor-fold-design-20260805
REVISION: rev2 — folds the three HOLD RELEASES of `DESIGN-ORCHESTRATOR-PLANNER-HOLDS-RELEASED-20260805-013542` (authoritative text: the master relay it cites): H1 exact-row criterion-closure; H2 released with the CORRECTED old-reader assumption (whole-archive refusal, exit 3); H3 one-directional SHA binding for the RUNCARD leg.
rev1 lineage — folded all five findings of `DESIGN-REVIEW-IMPLEMENTER-20260805-002131` (must-revise): R1 carrier ordering; R2 warning/torn-tail consumers + the B2/E disjointness proof; R3 the live E3 runtime in the mirror boundary; R4 the D2 invariant + wire mapping; R5 the slice-D list/info base-contract shape.
The rev0 accepted points (D1 shared unit; pack-MIN-omit manifest-free; single A9 writer ownership; B1-before-B2-branch-3; the §6 no-exact-key finding; hold handling) are preserved unchanged in substance.
Author seat: `s4-floor.planner`.
Dispatch: `s4-floor-design` (`.relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-20260804-235023.md`).
Basis (consumed, never edited): the LOCKED A7 (`2e402057…`, hash-verified at audit), m-2 `170500` §4, sealed `A3.3` (read in full at this seat for rev1), sealed A9/F64, the reconciled audits (`RECONCILE.md` §s4-floor), the receipt plans (`170500` §3, `224200` §4, carrier §8 at `ce9ef8c`).
This document designs integration shape only.
Every behavioral semantic below is the locked text's; where a sentence restates one, the lock governs.

## 0. Holds — ALL THREE RELEASED (013542); the binding answers folded here

- H1 RELEASED — exact-row criterion-closure (m-2 arm (a)): an `…-exact` row closes over EVERY member of the object AS IT EXISTS at the reviewed tree; CANON's "ALL EIGHT" was a lock-time count, not a cap.
  The executor READS `detail`'s actual value and ASSERTS what it read — `∅` asserted as `∅`; a POPULATED `detail` on an installed row is a FINDING returned up the bridge, never papered over.
  No CANON rewrite; receipt semantics wait on nothing.
  Standing finding kept from rev0: NONE of the eighteen receipt keys is an `…-exact` key.
- H2 RELEASED — with the CORRECTED binding assumption (orchestrator-verified at `envelope.cpp:407` return-3 group + `schemas/biv-exit-map.v1.json:16` `class: refusal, exit: 3`, both at `8981bfd`): an old schema-1-only reader meeting a schema-2 archive-only entry refuses the WHOLE ARCHIVE as `UnmanifestedMember`, EXIT 3, nothing installs, session layer and consent never run.
  Slice D designs against exactly that; partial-install-with-skip, a per-entry skip row, and exit 2 are NEVER assumed — A7's contrary compatibility text rode an unreachable path and is being corrected forward at m-2's seat (stricter direction; no arm narrows; no P5 key is a mutation arm, so the eighteen-receipt obligation is unchanged).
- H3 RELEASED — F-1's RUNCARD leg is a ONE-DIRECTIONAL SHA BINDING: product constants + harness pins move in ONE bivpak commit; the pdc RUNCARD update NAMES that exact SHA; no run consumes new pins until the RUNCARD row lands.
  The F-1 ledger carries the accepted limitation VERBATIM: "a bivpak constants change whose SHA no RUNCARD row names goes RED at the NEXT RUN GATE, not at change time — drift is detectable, not impossible."
- Fence 2 (still binding): slice D alone touches `manifest.cpp`; slices A/B/C land ahead of it. Addendum F's landing signal is still pending across the bridge.

## 1. Decision D1 — the constants' home: ONE shared version-floor unit

**Decision: a new `src/adapters/version_floor.hpp` + `version_floor.cpp` owning, for both legs:**
- the per-agent line-grain constants — MIN (pack floor: codex `0.142`, claude `2.1`) and `surveyed_through` (disclosure watermark: codex `0.144`, claude `2.1`) — as one table keyed by agent id;
- the version grammar parser (full-grammar validity, per the locked conjunction);
- the total-order comparator (line-grain, forward);
- the typed outcome vocabulary the two gates share (`basis_newer_than_host`, `basis_unorderable`).

Each adapter's `install.cpp` calls this unit at its OWN call sites; the unit never dispatches per-agent behavior internally beyond the constant lookup.

Alternatives considered:
- (a) per-adapter constants beside the retired allowlist — rejected: two comparator implementations is the drift class the matrix reconcile names for `probe.cpp`, and the §A7.10 mirror sweep would span two files;
- (c) constants in `adapter.hpp` — rejected: pollutes the cross-adapter interface header with m-2 line-grain data.

Why (b) wins: one mirror surface for the same-commit pin law (F-1: the constants, the consuming code, and the in-repo mirror — §4 slice A's full list — move in ONE commit); one comparator; per-leg call sites preserve `FX-MG-7`'s per-leg falsifiability (the receipt's mutation removes ONE leg's call/wiring, not the shared function body).
MIN and `surveyed_through` remain DIFFERENT things end to end: MIN is consumed only by the pack dispositions (slice A pack leg); `surveyed_through` only by the disclosure trigger (slice A render leg); no code path consumes both for one decision.

## 2. Decision D2 — verdict vocabulary restructure (`adapter.hpp:108`), with the R4 invariant and wire mapping

**Decision: `enum class Verdict { readable, unreadable, absent }` plus a separate `bool newer_than_survey`.**

**Construction invariant (normative, R4.1):** `newer_than_survey == false` unless `verdict == readable`.
The pair is produced only through one construction path (a factory/normalizing constructor in the capabilities probe); a state of `unreadable + true` or `absent + true` is unrepresentable through that path, debug-asserted at the type, and test-asserted for every serialized state.

**Host-version presence rule:** `agent_version` carries a parsed version iff `verdict == readable`; for `unreadable` and `absent` the field holds the existing `"unknown"` sentinel and the raw probe evidence rides the existing `probe` member untouched.

**Wire mapping (R4.2):** the JSON envelope and any text surface carry ONE derived verdict spelling, deterministically:
`readable && newer_than_survey` → `readable-newer-than-survey`; `readable` → `readable`; `unreadable` → `unreadable`; `absent` → `absent`.
No separate boolean is serialized; the internal pair is not a wire shape.
This preserves §A7.9's externally named state (`readable_newer_than_survey`) exactly, and the envelope schema enumerates the four spellings.
The disclosure trigger is exactly the first spelling's condition (host line > `surveyed_through`).

Alternative considered: a four-value enum carrying `readable_newer_than_survey` as its own state — rejected: §A7.7's cardinality note names "verdict + host version + `newer_than_survey` boolean" separately, and the derived-wire-spelling shape above gives the external four-state vocabulary without an internal enum/bool pair that can disagree.

Consumer rewires (all named, all slice A): `sessions.cpp` agent gate (keys on `unreadable`/`absent`; `readable` proceeds), `render.cpp:187-241` (prompt wording moves to floor/watermark display — exact wording is the m-3 consumer surface, flagged for the consumer-review leg), `envelope.cpp:142-146` + `schemas/biv-json-envelope.v1.schema.json` (the four derived spellings).
The shipped `unvalidated_host` state maps to `unreadable` (§A7.4 fail-closed); the shipped `unvalidated` ceases to exist — a readable host is readable, and admission moves entirely to the per-session direction gate.
`validated_range` (display string) retires with the allowlist.

## 3. Decision D3 — the consent-no carrier, with the R1 ordering made explicit

**The reordered per-agent carrier in `run_session_leg` (normative order, R1):**

1. Entry-level rows first, as today: unknown-adapter and entry-schema rows (slice-D note: archive-only pre-consent filtering, when D lands, slots here — held).
2. **Agent-level admission gates, BEFORE consent dispatch, zero adapter calls, regardless of the consent answer:** `absent` (store/agent), `unreadable` (probe), and the store-write-bits check — each terminates with its per-session `SessionRowReport` rows (`store-absent` / `host-version-unreadable` / `store_locked`), exit 2, exactly as locked (§A7.7 rows 1–2).
   A consent-no answer never converts these into staging: an unreadable or absent target stages nothing.
3. **Consent dispatch, only for a readable, present, writable target:** consent-yes → `install(…, Consent::yes)` with the host-store destination; consent-no → `install(…, Consent::no)` with the workspace-staging destination.
4. **Per-session version admission inside the adapter call, both consent values:** grammar gate BEFORE ordering; `basis_unorderable` / `basis_newer_than_host` refusals are per-session `failed` outcomes with typed details regardless of consent; only admitted sessions proceed to write (host or staged).

**One pipeline, two destinations (unchanged from rev0):** the adapters' consent-yes machinery (mint → derive pair set → read members → rewrite → verify → secure-write) runs on BOTH consent values; only the write destination and outcome tag fork (host store + `installed` vs `<WS>/.biv/agents/…` staged bytes + `staged`, sealed dated layouts).

**Sidecar aggregation, publication, and failure boundary (R1, made explicit):**
- The A9 sidecar (`<WS>/.biv/agents/manifest.json`; sealed content members: id_map, provenance chain, pair-set applied; no wire schema invented) is written ONCE by the orchestration layer, after ALL agents' install calls return and before rows are finalized for rendering.
- It aggregates exactly the sessions whose staging SUCCEEDED (`Outcome::staged` with staged bytes on disk), across all agents.
- Per-agent isolation holds: one agent's install failure never aborts a sibling agent's staging; failed agents contribute their failure rows and nothing to the sidecar.
- **Sidecar-publication failure is DIVERGENCE, not a chosen outcome:** if the sidecar write fails, the affected staged sessions' rows become `session_install_failed` (typed to the sidecar failure), exit 2, and the report DISCLOSES the staged byte paths already on disk — they are not silently deleted (the recovery path is a re-run; destroying user-visible staged bytes on a bookkeeping failure is the worse failure).
  F57 is honored in both directions: exit 0 requires the WHOLE operation (bytes + sidecar + report + guidance); an incomplete operation is a genuine failure.
- On success: the chosen-outcome row (a NEW distinct row + a 0-returning kind; spellings are the m-3 consumer surface, routed to the consumer-review leg), staging report + printed guidance default-visible, exit 0.
- The dead mapper (`sessions.cpp:323-326`) is corrected to the chosen-outcome row in the same slice; never cited as precedent.
- Hardening row (from the audit): the `sessions.cpp:308-314` manifest-lookup miss must fail CLOSED for `live_at_pack` reporting, not default to `false`.

Review-accepted ownership stands: A9 pins one path and three content members, not a per-adapter writer; the single orchestration writer with the ordering above is the design.

## 4. Decision D4 — slices, with the R2/R3 consumer and cluster corrections

Each slice is its own head/PR under panel-at-SHA rules; the reconciled sequencing (Addendum F → Arm-1 schema act → floor `manifest.cpp` act) and the one-owner-per-act-window clusters bind throughout.

- **Slice B1 — codex liveness (R-3.25(a)) + the pack-warning render surface. UNFENCED; land FIRST.**
  `codex.cpp` collect derives `live_at_pack` from the rollout tail-record type: TERMINAL = `{task_complete, turn_aborted, thread_rolled_back}`; ANY other tail — dangling tool call, truncated final line, unparseable record, empty file — ⇒ `true` (fail-closed).
  **R2 correction — the render consumer is IN this slice:** at the pinned tree, non-JSON `pack` renders only prune advisories (`main.cpp:44-50`); `PackReport.warnings` reaches only the exit code and the JSON envelope.
  B1 therefore adds default-visible rendering of `PackReport.warnings` to the non-JSON pack text output (a GENERIC warnings renderer, so later warning kinds — including B2's — ride it with no further `main.cpp` change), and the `SessionLiveAtPack` warning text carries MAY, never IS (R-3.36 class), exactly once per live session.
  Cluster note: this is B1's one `src/cli/main.cpp` touch; B1 owns that cluster for its act window.
  NEGATIVE CONTROL fixture: terminal tail asserts the warning line ABSENT from default output (not merely a zero count).
- **Slice A — the floor core + C1 head, one head (F-3). UNFENCED.**
  `version_floor.{hpp,cpp}` (D1); allowlist deletion at both legs (`codex/install.cpp:194-196`, `claude_code/install.cpp:331`) with the diff NOT widened into below-MIN/non-version refusals (§A7.5); the three-step conjunction at both legs' admission sites — grammar BEFORE ordering, typed details; verdict restructure (D2) + the unreadable agent-level gate; the mapper's NEW `failed`-with-version-detail branch (closed `reason` spellings `basis-newer-than-host`/`basis-unorderable` on `agent_not_validated_failed`); pack-side MIN omit-loud disposition (review-verified manifest-free: classification and omission happen before `manifest_entry_for` and artifact spooling, `pack.cpp:533-575`; the skip-loud report rows get an explicit report/render contract in the plan); the §A7.9 disclosure loud line.
  **R3 correction — the §A7.10 in-repo mirror boundary is the FULL live set, one commit:** the product constants + call sites; `harness/scenarios-e3/e3-dual-resume.json` (the scenario pins); `harness/bivharness/e3.py` — whose `version_in_validated_range` (`:766-778`) is a LIVE runtime prefix predicate on the host path, and which is REPLACED by a mirror-derived contract: grammar-valid single version AND line-grain `≥ MIN`, with newer-than-`surveyed_through` recorded for disclosure expectations — the CLI-probe grammar/readability oracle preserved; plus every schema/selftest consumer of the retired `validated_version_prefixes` key (`harness/selftest/test_e3_asserts.py`, the scenario schema).
  A slice-A commit touching a constant without this full mirror set fails the pin check.
  **The RUNCARD leg (H3 release, one-directional SHA binding):** the pdc RUNCARD update NAMES the exact bivpak SHA of the constants commit; no run consumes new pins until that RUNCARD row lands.
  The slice-A F-1 ledger carries the accepted limitation VERBATIM: "a bivpak constants change whose SHA no RUNCARD row names goes RED at the NEXT RUN GATE, not at change time — drift is detectable, not impossible."
- **Slice C — consent-no carrier (D3). UNFENCED; after A (it consumes the verdict shape and the reordered gates).**
  Includes the F57 exit-0 chosen row + guidance, the orchestration A9 sidecar writer with the §3 failure boundary, the dead-mapper correction, the `sessions.cpp:308-314` hardening row, and the consent-no harness scenario flips (`open-consent-no.json`, `open-deny-default.json` — flip-ledger rows, decided-not-deleted).
- **Slice B2 — torn-tail (R-3.25(b)). UNFENCED; codex leg strictly after B1; sequenced after B1 for the render surface too.**
  A3.3's four branches at collect, per leg: branch 1 verbatim; branch 2 appends exactly one LF (the only byte collect may add); branch 3 drops exactly T and records `torn_tail_dropped = {artifact, bytes: len(T)}`; branch 4 collects verbatim and refuses at install typed `undecodable_line`; interior segments never inspected; retained-prefix byte equality in every branch.
  **R2 correction — the full consumer set is in the boundary contract (§5):** the structured carrier runs collect → `SessionRecord` (per-artifact torn-tail facts) → `PackReport` summary rows → BOTH pack outputs (default text via B1's generic warnings/summary renderer — no new `main.cpp` touch — and the JSON envelope); the open-time caveat derives from the persisted `live_at_pack` flag (the existing row suffix surface, wording per A3.3); the branch-4 typed install refusal is a separate consumer (its `undecodable_line` spelling is today absent from src — 0 grep hits — so the typed-refusal vocabulary is B2 work on the install side).
  If the summary row needs a field the shipped `Warning{kind, path}` cannot carry (the byte count), B2 extends the pack report structure (`pack.hpp`) — named here so the plan costs it.
  **R2 correction — B2∥E disjointness by NAMED files, not labels:** B2 touches `src/adapters/codex/codex.cpp`, `src/adapters/claude_code/claude_code.cpp` (collect), `src/core/pack/pack.{hpp,cpp}`, the install-side refusal site, and their owner tests; E touches the open-side install/report surfaces (§A5.10 migration composition, announcement/created-paths/recovery rendering, evaluability abstention) and their owner tests.
  The only shared surfaces are `CMakeLists.txt` and any common test fixture scaffolding — explicit-path, rebase-before-land discipline; neither slice touches `main.cpp` (B1 owns that window) and only E touches `render.cpp`.
  If the plan discovers E needs an install-side file B2 also touches, the two serialize at that file — the claim is per-file, revisable at plan, not a label.
- **Slice D — archive-only marker. FENCED (behind Arm-1's schema act); hold RELEASED, designed against the corrected old-reader assumption.**
  Schema-2 writer + schema-2-aware reader + pre-consent filter + `archive_only_skipped` row + the ONE new 0-returning `ErrKind` (shared error/exit-map/envelope cluster — one owner per act window).
  **Binding old-reader assumption (H2 release, corrected):** an old reader refuses the WHOLE ARCHIVE (`UnmanifestedMember`, exit 3, nothing installs, no session layer, no consent) on any schema-2 archive-only entry.
  Slice D's fixtures assert THAT behavior for the old-reader leg; the FX-VF-P5 keys' contrary shapes follow m-2's forward correction (its register disposition runs at the VP's seat — no s4 dependency).
  The safety property (an old reader cannot auto-install an archive-only session) holds trivially under the corrected direction; the degradation story is stricter than A7 claimed, and slice D introduces no mitigation for it (any softening is m-2/master design, not this pair's).
  **R5 correction — the `list`/`info` base contract:** both verbs are wholesale `NotYetImplemented` (`main.cpp:390-394`); there is no base surface to insert archive-only status into, and this design does not smuggle a whole verb in as "status rendering."
  Shape chosen for D's post-H2 restatement: **D DEPENDS on a separately-owned base `list`/`info` implementation** — ownership routed through `s4.orchestrator-planner` (it is a shared `main.cpp` cluster and an m-3 consumer surface, not this pair's to absorb).
  D's own scope on that base is archive-only status rendering only.
  If no base exists when D unfences, D's restatement escalates the dependency rather than absorbing the verb.
- **Slice E — A5-surface completion (migration backstop + the A5 visibility surfaces).**
  §A7.8: the §A5.10 migration table (MG-1 REFUSE-with-recovery, FX-VF-M1) composes inside the admitted direction; plus the tier-2 loud-install surfaces the A5 receipts assert (announcement, created-paths listing, three-clause recovery block, the golden line, evaluability-keyed abstention) — all absent in src (audit instruments).
  HONESTY BOUND: addendum-5's exact surface specs were NOT read at this seat; the PLAN phase for slice E consumes addendum-5 directly before naming file targets.
  Sequenced after A (the loud-install path re-anchors on A's derived `readable-newer-than-survey` state).

Order: B1 → A → C → {B2, E} (disjoint by the named-file statement above) → D (post-fence).
Cluster discipline (binding, from the reconcile): `main.cpp` (B1's window in this design), the error-enum/exit-map/envelope cluster (slice A's version-reason rows; slice D's new kind — separate windows), and the frozen open-envelope oracle (recaptured ONCE, after the floor's act lands, matrix-first at Arm 1) each have ONE owner per act window.

## 5. Boundary contracts (per slice, the writer/reader pairs)

- Slice B1 — Writes: `SessionRecord.live_at_pack` (true derivation); the default-visible pack-warnings TEXT surface (generic renderer). Reads: rollout tail record. Target entity: manifest `agent_sessions[]` entry + the pack report. Downstream consumers: non-JSON pack text (NEW — today warnings reach only exit code + JSON), JSON envelope warnings, open rows + render suffix (existing). Contract: `170500` §4 acceptance criteria incl. exactly-one MAY-worded warning + negative control. Proof: E2 fixtures.
- Slice A — Writes: `Capabilities` (D2 shape + derived wire spelling), `InstallSessionOutcome.detail` version subset, pack skip-loud rows, disclosure line, refusal rows, the full in-repo mirror set (constants, scenario pins, `e3.py` runtime contract, selftest/schema consumers). Reads: host probe (unchanged §A7.6 oracle), image basis, the constants. Downstream consumers: sessions gate, render, envelope/JSON schema, the E3 runtime. Contract: §A7.3/4/5/7/9/10. Proof: E2 FX-VF O-family + P1/P2/P4 fixtures; the E3 forward-host acceptance test (§7).
- Slice C — Writes: staged bytes under `<WS>/.biv/agents/…`, the ONE A9 sidecar (aggregation + failure boundary per §3), chosen-outcome rows, guidance. Reads: image members, consent decision, the admission-gate results (order per §3). Downstream consumers: re-pack provenance (`tier: staged` with original chain), m-3 report surface. Contract: sealed G2 + A9/F64 + F57. Proof: E2 FX-VF-O1 staged/sidecar/repack keys + the §7 ordering tests.
- Slice B2 — Writes: collected artifact bytes (branch-trimmed tail only), per-artifact `torn_tail_dropped {artifact, bytes}` facts, pack summary rows. Reads: raw session files, the session's live flag (B1's derivation on codex). Downstream consumers: pack default text (via B1's renderer) + JSON envelope; the open-time caveat from persisted `live_at_pack`; the branch-4 typed install refusal (`undecodable_line`, new vocabulary). Contract: sealed A3.3 (all four branches + the surfacing sentence). Proof: E2 four-branch × two-leg fixtures with byte-equality + the §7 default-output test.
- Slice D — Writes: schema-2 entries (marker object + sentinel), the archive-only skip row + new 0-returning kind, default `list`/`info` status rendering (on the R5 base dependency). Reads: pack dispositions' unknown-parseable classification. Downstream consumers: the NEW reader's pre-consent filter and open rows; the OLD reader per the corrected assumption (whole-archive `UnmanifestedMember` refusal, exit 3 — asserted, not mitigated). Contract: pins P1–P5 as forward-corrected at m-2's seat. Proof: E2 P3/P6 fixtures + the corrected old-reader fixture; full restatement at slice D's own plan, post-fence.
- No slice touches host stores outside the existing consent-bound install write; no slice adds a host-store surface (DNA rule).

## 6. Receipts-as-you-go — the EIGHTEEN mapped to their GREEN-abling slice

| receipt | slice that makes its fixture GREEN-able |
|---|---|
| `FX-VF-O3/{codex,claude}/disclosure-default-visible` | A |
| `FX-VF-O6/{codex,claude}/no-image-field-in-derivation` | A |
| `FX-VF-O4/{codex,claude}/basis-nul-bearing/refuses-before-comparison` | A |
| `FX-MG-7/{codex,claude}/full-grammar-red` | A |
| `A5.8/silent-promotion` (§8-operative; O7 falsifier, inputs FROZEN) | A |
| `A5.8/tier2-announcement/default-visibility` | A (trigger) + E (surface) |
| `A5.8/tier2-createdpaths/default-visibility` | E |
| `A5.8/tier2-recovery/{identify,removes-ours,vendor-warning}-visibility` | E |
| `FX-MG-6/default-visibility` | E |
| `FX-MG-1R/recovery-visibility`, `FX-MG-3a/recovery-visibility` | E (migration backstop) |
| `FX-MG-9/evaluability-red` | E |

Execution law restated per receipt: fixture GREEN on correct code → ONE isolated mutation → observed RED (with sibling-stays-green where the plan requires it) → revert → post-revert green; run-traceable evidence; produced AS SLICES LAND.
The NUL-bearing O4 fixtures carry a REAL NUL byte and are never normalized by hygiene sweeps.

**H1 resolved (criterion-closure, per the release):** none of the eighteen keys is an `…-exact` key — the receipts assert visibility/purity/ordering — and the 30 `…-exact` comparators are now ASSERTABLE without waiting: each closes over EVERY member of the shipped carrier at the reviewed tree (today: all nine, `detail` included), asserting the value actually read — `∅` as `∅`.
A populated `detail` on an installed row is a FINDING routed up the bridge, never absorbed into the expectation.
For the O4 receipts the sibling `…-exact` keys' observed state is recorded per that criterion in the receipt evidence.

**Flip ledger (decided-not-deleted, DR-3 discipline; owned per slice):** the allowlist-asserting tests (`test_adapter_codex_install.cpp`, `test_adapter_claude_install.cpp`, `test_envelope.cpp`, `test_render.cpp`, `test_sessions.cpp`, `tests/fixtures/probe-envelope-v1.json`) flip in slice A — joined by the E3 mirror set (`e3-dual-resume.json`, `test_e3_asserts.py` prefix assertions, per R3); the consent-no scenarios (`open-consent-no.json`, `open-deny-default.json`) flip in slice C; every flip is LISTED in the slice's plan ledger with its replacement assertion.

## 7. Testing and verification shape

- TDD per slice (RED first) with the FX-VF/FX-MG stable keys as fixture names wherever a key exists — the fixture register IS the test plan for the floor surfaces.
- Per-slice verification target: E2 at the slice head; golden-harness E3 rows and the panel ride each head per panel-at-SHA rules; receipts execute at the slice that GREEN-ables them.
- The §A7.10 same-commit law is CI-checkable in-repo over the FULL R3 mirror set: a slice-A commit touching a constant without the complete set fails the pin-mirror check.
- Exit-map/envelope row-count pins move only inside the error-cluster act window with its single owner.

**Required revised-design tests (from the review, adopted verbatim as plan obligations):**
1. unreadable / absent / store-missing × consent-no ⇒ zero adapter calls and zero staging (the §3 ordering, both legs);
2. readable admitted × consent-no ⇒ staged bytes on disk, exactly ONE sealed-member sidecar aggregated across agents, and the defined sidecar-publication-failure behavior (rows flip to typed failure, exit 2, staged paths disclosed, bytes not deleted);
3. non-JSON pack displays exactly one MAY-worded warning for a live codex session and NONE for the terminal negative control (absence asserted on the output, not a count);
4. B2 branch 3 emits exact artifact/byte facts in default pack output; the open caveat and the branch-4 typed refusal are separately asserted;
5. E3 accepts a grammar-valid readable forward host OUTSIDE the retired prefixes while the constants and scenario mirror remain exact (the R3 runtime-contract proof);
6. every serialized D2 state obeys the construction invariant and has exactly one deterministic wire spelling (all four spellings enumerated).

## 8. Out of scope (restated hard lines)

The five matrix arms; sealed-doc amendments (A7 consumed, not edited — its old-reader compatibility correction is m-2's, not ours); host-store surfaces; R-4.1 arm (ii); R-4.2 sparse; the pdc RUNCARD write itself (pdc-side, named-SHA per H3's binding); any mitigation of the corrected old-reader whole-archive refusal; `list`/`info` beyond the R5 dependency statement.

## 9. Open items this design leaves for named owners

- Chosen-outcome row + guidance SPELLINGS: m-3 consumer surface — panel consumer-review leg at slice C.
- The base `list`/`info` implementation D depends on: ownership routed through `s4.orchestrator-planner` (R5).
- Slice E file targets: PLAN phase reads addendum-5 first (honesty bound, §4).
- Holds: all three RELEASED (013542) and folded (§0); the remaining external signals are Addendum F's landing (fence 2's upstream) and the P5/A7 forward correction at m-2's seat (no s4 dependency).
