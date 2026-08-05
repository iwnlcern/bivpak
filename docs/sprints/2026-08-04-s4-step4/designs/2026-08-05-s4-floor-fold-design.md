# s4-floor fold — integration-shape design under the LOCKED A7

DESIGN_DOC_ID: s4-floor-fold-design-20260805
Author seat: `s4-floor.planner`.
Dispatch: `s4-floor-design` (`.relays/s4/s4-floor-design/DESIGN-ORCHESTRATOR-PLANNER-20260804-235023.md`).
Basis (consumed, never edited): the LOCKED A7 (`2e402057…`, hash-verified at audit), m-2 `170500` §4, sealed `A3.3`, the reconciled audits (`RECONCILE.md` §s4-floor), the receipt plans (`170500` §3, `224200` §4, carrier §8 at `ce9ef8c`).
This document designs integration shape only.
Every behavioral semantic below is the locked text's; where a sentence restates one, the lock governs.

## 0. Holds honored (designed around, never closed here)

- H1 (nine-member CANON drift): §6 parameterizes exact-row comparators over the pending ruling.
  Finding recorded in §6: NONE of the eighteen receipt keys is an `…-exact` key, so H1 blocks the broader register build-out, not the receipts.
- H2 (old-reader containment contradiction): the archive-only marker is isolated in slice D and is the ONLY fenced-and-held slice.
- H3 (cross-repo same-commit): slice A carries the in-repo mirror per §A7.10; the pdc RUNCARD leg is excluded from every slice until master defines the cross-repo shape.
- Fence 2: slice D alone touches `manifest.cpp`; slices A/B/C are constructed to be landable ahead of it.

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

Why (b) wins: one mirror surface for the same-commit pin law (F-1: the constants, the consuming code, and the in-repo harness mirror move in ONE commit); one comparator; per-leg call sites preserve `FX-MG-7`'s per-leg falsifiability (the receipt's mutation removes ONE leg's call/wiring, not the shared function body — the shared body is exactly what makes "removing codex's check leaves claude green" a real per-leg claim).
MIN and `surveyed_through` remain DIFFERENT things end to end: MIN is consumed only by the pack dispositions (slice A pack leg); `surveyed_through` only by the disclosure trigger (slice A render leg); no code path consumes both for one decision.

## 2. Decision D2 — verdict vocabulary restructure (`adapter.hpp:108`)

**Decision: `enum class Verdict { readable, unreadable, absent }` plus a separate `bool newer_than_survey`,** meaningful only when `readable`.
The disclosure trigger is exactly `verdict == readable && newer_than_survey` (host line > `surveyed_through`).

Alternative considered: a four-value enum carrying `readable_newer_than_survey` as its own state — rejected: §A7.7's cardinality note names "verdict + host version + `newer_than_survey` boolean" separately, and an enum+boolean pair that can disagree (enum says newer, bool says no) is an inconsistent-state bug the two-field shape cannot express.

Consumer rewires (all named, all slice A): `sessions.cpp:229-243` (the gate keys on `unreadable`/`absent` for the agent-level refusals; `readable` proceeds), `render.cpp:187-241` (prompt wording moves from validated-range display to floor/watermark display — exact wording is the m-3 consumer surface, flagged for the consumer-review leg), `envelope.cpp:142-146` (verdict serialization), the JSON envelope schema.
The shipped `unvalidated_host` state (store exists, probe failed) maps to `unreadable` — §A7.4's fail-closed refuse — and the shipped `unvalidated` (probe ok, not in allowlist) ceases to exist: a readable host is readable; admission moves entirely to the per-session direction gate.
`validated_range` (display string) retires with the allowlist.

## 3. Decision D3 — the consent-no carrier wiring (R-VF.1/2/3)

**Decision: one pipeline, two destinations; the sidecar is written by the orchestration layer.**

- The adapters' existing consent-yes machinery (mint → derive pair set → read members → rewrite → verify → secure-write) is PROMOTED to run on BOTH consent values.
  The only consent-conditional is the WRITE DESTINATION and the outcome tag: consent-yes writes to the host store and returns `installed`; consent-no writes install-ready staged BYTES under `<WS>/.biv/agents/…` (the sealed dated layouts CANON-2 exercises) and returns `staged`.
  Nothing else forks — same mint, same rewrite, same verify.
- The A9 sidecar (`<WS>/.biv/agents/manifest.json`: id_map + provenance chain + pair-set applied — sealed content members only, no wire schema invented) is written ONCE by the orchestration layer (`sessions.cpp`), aggregated across agents after the per-agent install calls return.
  Rationale: the sealed path is a single file; two adapters writing one file is a collision by construction.
- `run_session_leg` consent-denied branch (today `sessions.cpp:215-227`, the bare skip) becomes: call `adapter->install(…, Consent::no)` with the staging-destination target, then map `staged` to the CHOSEN-OUTCOME row — a NEW distinct row + a 0-returning kind (F57: exit 0 AND the operation), with the staging report + printed guidance rendered default-visible.
  The exact row/guidance SPELLINGS are the m-3 consumer surface; this design pins the behavior (distinct row, exit 0, guidance present, no existing skip's exit changed) and routes spellings to the consumer-review leg of the panel.
- The dead mapper (`sessions.cpp:323-326`, `staged` → `session_install_failed`/`error`) is corrected to the chosen-outcome row in the same slice; it is never cited as precedent.
- Hardening row (from the audit): `sessions.cpp:308-314` — an adapter row whose manifest lookup misses must fail CLOSED for `live_at_pack` reporting (or refuse loudly), not default to `false`.

Alternative considered: a separate staging writer beside the adapters (leave `Consent::no` metadata-only, orchestration stages raw copies) — rejected by the lock itself: §A7.7 pins ONE end-to-end carrier and G2 requires paths rewritten IN the staged bytes at stage time; raw copies are the named defect, not a design option.

## 4. Decision D4 — slice partitioning and order (landability under the fences)

Each slice is its own head/PR under panel-at-SHA rules; the reconciled sequencing (Addendum F → Arm-1 schema act → floor `manifest.cpp` act) and the one-owner-per-act-window clusters bind throughout.

- **Slice B1 — codex liveness (R-3.25(a)). UNFENCED; land FIRST (smallest, unblocks the most).**
  `codex.cpp` collect derives `live_at_pack` from the rollout tail-record type: TERMINAL = `{task_complete, turn_aborted, thread_rolled_back}`; ANY other tail — dangling tool call, truncated final line, unparseable record, empty file — ⇒ `true` (fail-closed).
  Everything downstream is already pure propagation (audit-verified); the one default-visible warning rides the existing `SessionLiveAtPack` pack warning; wording carries MAY, never IS (R-3.36 class).
  NEGATIVE CONTROL fixture: terminal tail asserts the warning ABSENT.
- **Slice A — the floor core + C1 head, one head (F-3). UNFENCED.**
  `version_floor.{hpp,cpp}` (D1); allowlist deletion at both legs (`codex/install.cpp:194-196`, `claude_code/install.cpp:331`) with the diff NOT widened into below-MIN/non-version refusals (§A7.5); the three-step conjunction at both legs' admission sites — grammar gate BEFORE ordering, typed `basis_unorderable`/`basis_newer_than_host` details; verdict restructure (D2) + the unreadable agent-level gate (zero adapter calls, per-session rows, recovery text); the mapper's NEW `failed`-with-version-detail branch (`InstallSessionOutcome.detail` → closed `SessionRowReport.reason` spellings `basis-newer-than-host`/`basis-unorderable` on `agent_not_validated_failed`); pack-side MIN omit-loud disposition (skip-loud report rows — NO manifest change: an omitted session simply never enters the archive); the §A7.9 disclosure loud line; the in-repo §A7.10 mirror (`harness/scenarios-e3/e3-dual-resume.json`, `harness/selftest/test_e3_asserts.py`) in the SAME commit as the constants.
  Note: pack MIN omit-loud is deliberately IN slice A, not the fenced slice — it consumes only the constants and the pack report, never `manifest.cpp`.
- **Slice C — consent-no carrier (D3). UNFENCED; after A (it consumes the verdict shape).**
  Includes the F57 exit-0 chosen row + guidance, the A9 sidecar writer, the dead-mapper correction, the `sessions.cpp:308-314` hardening row, and the consent-no harness scenario flips (`open-consent-no.json`, `open-deny-default.json` — flip-ledger rows, decided-not-deleted).
- **Slice B2 — torn-tail (R-3.25(b)). UNFENCED; codex leg strictly after B1.**
  A3.3's four branches at collect, per leg, retained-prefix byte equality in every branch; branch 2 appends exactly one LF; branch 3 records `torn_tail_dropped = {artifact, bytes: len(T)}` exactly; branch 4 collects verbatim and refuses at install as `undecodable_line`; interior segments never inspected.
  A codex branch-3 test green while `live_at_pack` is hardcoded fails review (the dispatch law; B1 removes the hardcode first).
- **Slice D — archive-only marker. FENCED (behind Arm-1's schema act) AND HELD (H2).**
  Schema-2 writer (`entry_schema: 2` + required `archive_only` object + the exact `"unknown"` sentinel; admissible entries STAY at 1 — minimum-schema rule; writer today hardcodes 1 at `pack.cpp:405`), schema-2-aware reader (full schema-1 set + marker; `>known-max` skip preserved), pre-consent filter, `archive_only_skipped` row + the ONE new 0-returning `ErrKind` (shared error/exit-map/envelope cluster — one owner per act window per the reconcile ruling), `list`/`info` default rendering (today `NotYetImplemented`, `main.cpp:390-394` — the `list`/`info` verb implementation is a shared `main.cpp` cluster surface; scope minimally to archive-only status rendering).
  H2 may reshape the old-reader compatibility claims; nothing in A–C depends on D's shape.
- **Slice E — A5-surface completion (migration backstop + the A5 visibility surfaces).**
  §A7.8: the §A5.10 migration table (MG-1 REFUSE-with-recovery, FX-VF-M1) composes inside the admitted direction; plus the tier-2 loud-install surfaces the A5 receipts assert (announcement, created-paths listing, three-clause recovery block, the golden line, evaluability-keyed abstention) — all absent in src (audit instruments).
  HONESTY BOUND: addendum-5's exact surface specs were NOT read at this seat; the PLAN phase for slice E consumes addendum-5 directly before naming file targets.
  Sequenced after A (the loud-install path re-anchors on A's `readable && newer_than_survey` trigger — driving it by a retired tier concept reaches nothing, per `224200` §5.3).

Order: B1 → A → C → {B2, E} (parallel-safe: disjoint files) → D (post-fence, post-H2).
Cluster discipline (binding, from the reconcile): `main.cpp`, the error-enum/exit-map/envelope cluster, and the frozen open-envelope oracle each have ONE owner per act window; floor recapture of the frozen oracle happens once, after the floor's own act lands, matrix-first at Arm 1.

## 5. Boundary contracts (per slice, the writer/reader pairs)

- Slice B1 — Writes: `SessionRecord.live_at_pack` (true derivation). Reads: rollout tail record. Target entity: manifest `agent_sessions[]` entry. Downstream consumer: pack warning + open rows + render (all existing). Contract: `170500` §4. Proof: E2 fixtures incl. the negative control.
- Slice A — Writes: `Capabilities` (new shape), `InstallSessionOutcome.detail` version subset, pack skip-loud rows, disclosure line, refusal rows. Reads: host probe (unchanged §A7.6 oracle), image basis, the constants. Downstream consumers: sessions gate, render, envelope/JSON schema, harness mirror. Contract: §A7.3/4/5/7/9/10. Proof: E2 FX-VF O-family + P1/P2/P4 fixtures.
- Slice C — Writes: staged bytes under `<WS>/.biv/agents/…`, the A9 sidecar, chosen-outcome rows, guidance. Reads: image members, consent decision. Downstream consumers: re-pack provenance (`tier: staged` with original chain), m-3 report surface. Contract: sealed G2 + A9/F64 + F57. Proof: E2 FX-VF-O1 staged/sidecar/repack keys.
- Slice B2 — Writes: collected artifact bytes (branch-trimmed tail only), `torn_tail_dropped` record. Reads: raw session files. Downstream consumer: install (`undecodable_line` refusal on branch 4). Contract: sealed A3.3. Proof: E2 four-branch × two-leg fixtures with byte-equality.
- Slice D — held for H2; contract restated only after the ruling.
- No slice touches host stores outside the existing consent-bound install write; no slice adds a host-store surface (DNA rule; the floor reads host state via the existing probe only).

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

**H1 interaction, resolved shape:** none of the eighteen keys is an `…-exact` key — the receipts assert visibility/purity/ordering, and their `…-exact` SIBLINGS are observed-and-recorded, never assumed.
So H1 does not block any receipt.
The 30 `…-exact` fixture comparators are built PARAMETERIZED over the closed-row member list (eight members + `∅`-ninth vs an amended nine) and are asserted only after m-2's ruling lands.

**Flip ledger (decided-not-deleted, DR-3 discipline; owned per slice):** the allowlist-asserting tests (`test_adapter_codex_install.cpp`, `test_adapter_claude_install.cpp`, `test_envelope.cpp`, `test_render.cpp`, `test_sessions.cpp`, `tests/fixtures/probe-envelope-v1.json`) flip in slice A; the consent-no scenarios (`open-consent-no.json`, `open-deny-default.json`) flip in slice C; every flip is LISTED in the slice's plan ledger with its replacement assertion.

## 7. Testing and verification shape

- TDD per slice (RED first) with the FX-VF/FX-MG stable keys as fixture names wherever a key exists — the fixture register IS the test plan for the floor surfaces.
- Per-slice verification target: E2 (unit/fixture) at the slice head; the golden-harness E3 rows and the panel ride each head per panel-at-SHA rules; receipts execute at the slice that GREEN-ables them.
- The §A7.10 same-commit law is CI-checkable in-repo: a slice-A commit touching a constant without its mirror fails the pin-mirror check (existing `validated_version_prefixes` sites become the floor-constant mirror; exact mechanism per plan).
- Exit-map/envelope row-count pins (`test_envelope.cpp`, `schemas/biv-exit-map.v1.json`) move only inside the error-cluster act window with its single owner.

## 8. Out of scope (restated hard lines)

The five matrix arms; sealed-doc amendments (A7 consumed, not edited); host-store surfaces; R-4.1 arm (ii); R-4.2 sparse; everything H1/H2/H3 reserve; the pdc RUNCARD leg of the mirror; `list`/`info` beyond archive-only status rendering.

## 9. Open items this design leaves for named owners

- Chosen-outcome row + guidance SPELLINGS: m-3 consumer surface — panel consumer-review leg at slice C.
- Slice E file targets: PLAN phase reads addendum-5 first (honesty bound, §4).
- H1/H2/H3: upstream; slices constructed so no hold blocks A/B1/B2/C.
