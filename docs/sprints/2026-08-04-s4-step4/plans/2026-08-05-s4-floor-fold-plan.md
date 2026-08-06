# s4-floor fold — Implementation Plan (slices B1 → A → C → B2 → E)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

PLAN_ID: s4-floor-fold-plan-20260805
Locked design: `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-floor-fold-design.md` — rev5, SHA-256 `42cdfd944c6d74e3a9d23b804cb700ee86ea3ed337922f4c3596e98aaa4d3eda`, approved `DESIGN-REVIEW-IMPLEMENTER-REV5-20260805-142752`.
Every behavioral semantic is the locked A7's (`2e402057…`), m-2 `170500` §4's, sealed A3.3's, and sealed G2/A9-F64's; the design (and through it this plan) only integrates them.

**Goal:** land the A7 version floor, the C1 grammar/order head, the consent-no carrier, codex liveness + torn-tail, and the A5 loud-install/migration surfaces — as five sequential heads, producing receipt evidence as each head lands.

**Architecture:** one shared version-floor unit consumed at per-leg call sites; verdict pair + derived wire spelling; one orchestration-layer A9 sidecar; a forward-usable pack-warning carrier landed in B1 and populated in B2; the agent-generic migration engine in E.

**Tech Stack:** C++ (existing core/adapters), the existing ctest suites under `tests/`, the Python harness under `harness/`.

## Global Constraints (verbatim from the locked design; every task inherits them)

- Baseline: work branches from `main@8981bfd` product state; docs-lane files are not product surfaces.
- Slice order is BINDING: B1 → A → C → B2 → E; slice D is NOT in this plan (post-fence, own plan pass; `src/core/manifest/manifest.cpp` and `manifest.hpp` are OUT of every task below).
- MIN vs `surveyed_through` are DIFFERENT things: MIN = pack floor (codex `0.142`, claude `2.1`); `surveyed_through` = disclosure watermark (codex `0.144`, claude `2.1`); no code path consumes both for one decision.
- §A7.10 same-commit law: the constants, their consuming code, and the FULL in-repo mirror set move in ONE commit (slice A task 4); the pdc RUNCARD leg is one-directional SHA binding and OUT of scope.
- EIGHTEEN is the operative receipt count; SEVENTEEN appears nowhere except explicitly marked candidate; `FX-MG-9/evaluability-red` is `DISSOLVED-PENDING-RATIFICATION` with burden pointer `FX-VF-O5`/`CANON-3`.
- Discriminating-input-class precheck: before building any receipt whose fixture predates A7, record the check "does the input class that discriminates the mutated from the correct implementation still exist?" in the receipt evidence.
- Exact-row (`…-exact`) assertions consume the m-2 pinned `detail` value as an INPUT once its scoped addendum lands; until then those comparators are built but marked pending-pin (never derived from the observed row).
- Chosen-outcome row + guidance SPELLINGS are m-3-owned: implement behind names marked `/* m-3 spelling at consumer review */`; the panel's consumer leg settles them.
- Receipt execution law, per receipt: fixture GREEN on correct code → ONE isolated mutation → observed RED (+ sibling-stays-green where required) → revert → post-revert GREEN; run-traceable evidence filed under `docs/sprints/2026-08-04-s4-step4/results/receipts/`.
- Verdict lines bare; describe-never-reproduce for instrument text; relay/lint discipline per charter; docs-lane commits explicit-path only.
- The release hold is ABSOLUTE; nothing here merges or ships — each slice ends at branch + PR + report; `DISPATCH MERGE` is the operator's alone.
- One owner per act window for: `src/cli/main.cpp` (B1's window), the error-enum/exit-map/envelope cluster (C's window, then D's later), the frozen open-envelope oracle (recaptured ONCE, after slice A's act lands, matrix-first at Arm 1).

## Dispatch-scope file set (the SCOPE_DIFF universe for delegated dispatch)

Production: `src/adapters/version_floor.hpp` (new), `src/adapters/version_floor.cpp` (new), `src/adapters/migration.hpp` (new), `src/adapters/migration.cpp` (new), `src/adapters/adapter.hpp`, `src/adapters/codex/codex.cpp`, `src/adapters/codex/install.cpp`, `src/adapters/claude_code/claude_code.cpp`, `src/adapters/claude_code/install.cpp`, `src/core/open/sessions.hpp`, `src/core/open/sessions.cpp`, `src/core/open/render.hpp`, `src/core/open/render.cpp`, `src/core/pack/pack.hpp`, `src/core/pack/pack.cpp`, `src/core/report/envelope.cpp`, `src/core/support/error.hpp`, `src/core/support/error.cpp`, `src/cli/main.cpp`, `schemas/biv-json-envelope.v1.schema.json`, `schemas/biv-exit-map.v1.json`, `CMakeLists.txt` (build wiring for the two new units only).
Tests: `tests/test_adapter_codex_collect.cpp`, `tests/test_adapter_claude_collect.cpp`, `tests/test_adapter_codex_install.cpp`, `tests/test_adapter_claude_install.cpp`, `tests/test_pack.cpp`, `tests/test_manifest.cpp` (assertion flips only — no parser change), `tests/test_open.cpp`, `tests/test_sessions.cpp`, `tests/test_render.cpp`, `tests/test_envelope.cpp`, `tests/test_cli.cpp`, new fixture files under `tests/fixtures/**` (incl. the NUL-bearing corpus and the MG-FX double; new fixture SUBDIRECTORIES under `tests/fixtures/` are in-scope by this glob, but any NEW test translation unit not named above is OUT until rerouted).
Harness: `harness/scenarios-e3/e3-dual-resume.json`, `harness/bivharness/e3.py` (the in-file validators are the complete set — `version_in_validated_range` `:766-778`, the `_version_gate_agents` call `:1684-1687`, the scenario required-field/type checks `:2359-2374`; NO separate scenario schema file exists for this key), `harness/selftest/test_e3_asserts.py`, `harness/scenarios/open-consent-no.json`, `harness/scenarios/open-deny-default.json`, `harness/ci/check_version_floor_mirror.py` (new — the §A7.10 pin check).
Docs-lane evidence writes (a SEPARATELY AUTHORIZED evidence step, included in the SCOPE_DIFF universe so it can return all-in): receipt evidence under `docs/sprints/2026-08-04-s4-step4/results/receipts/**`; the implementation report relays under the DEDICATED dispatch directory `.relays/s4/s4-floor-impl/**` ONLY, plus append-only END-of-file rows in the single shared `.relays/s4/INDEX.md` (R3 — no wildcard over the rest of `.relays/s4/`; an edit to any sibling relay tree is OUT). These are docs-lane commits (explicit paths, per the operator's lane ruling), never on the implementation branches.
OUT (hard lines): `src/core/manifest/*`, `.github/`, host stores, `src/core/scan/*`, everything slice D, the pdc RUNCARD, R-4.1(ii), R-4.2, any path not enumerated above or in Amendment A1.

**AMENDMENT A1 (2026-08-05, orchestrator grant `…TASK1-EXPANSION-GRANTED…-182217`, additive-only):**
three paths are ADMITTED to the dispatch universe for exactly one addition — `src/core/json/writer.hpp`, `src/core/json/writer.cpp`, `tests/test_json_writer.cpp`.
The bound, verbatim from the grant: ONE new public unsigned JSON integer emitter (`value_uint(std::uint64_t)` or equivalent) beside the existing emitters; its unit boundary test including `UINT64_MAX`; the Task-1 envelope/schema regression.
NO existing emitter, signature, or serialization behavior changes; a change to any existing writer surface — or any fourth file — is a NEW deviation routed to `s4.orchestrator-planner` before an edit.
Task 1's serializer emits `bytes` through the new unsigned emitter (the `static_cast<int64_t>` narrowing is the defect this amendment exists to fix), and its test matrix gains the `UINT64_MAX` regression asserting the exact unquoted non-negative JSON integer.
Shared-infra note carried from the grant: the writer is repo-shared leaf infrastructure; this addition rides the floor's act window under the single-owner rule; the matrix pair rebases over it.

**AMENDMENT A2 (2026-08-05, orchestrator ruling `…B1-SCHEMA-LOCK-RECAPTURE-RULE-GRANTED-BOTH-PAIRS-20260805-200505`, the lock-recapture discipline of record for BOTH pairs):**
`harness/selftest/test_envelope.py` is ADMITTED to the dispatch universe for MECHANICAL LOCK RECAPTURE ONLY.
At each slice head that changes a locked schema artifact, update ONLY the corresponding `CURRENT_LOCKED_SCHEMA_BLOBS` literal to that slice's reviewed git blob id, in the SAME head — composing with the one-commit laws (B1 now: the envelope entry to the reviewed blob; Task 5/slice A: the envelope entry again; Task 7/slice C: the exit-map entry).
No harness behavior, scenario logic, or other selftest surface changes; any other edit to the file — or a recapture of a literal whose schema the head did NOT change — is a NEW deviation routed to `s4.orchestrator-planner` before an edit.
The rule preserves what the lock IS: a staleness tripwire making locked-schema changes decided, never accidental — the recapture rides the review that approved the schema change.
Distinct instrument, distinct discipline: the frozen open-envelope ORACLE's once-per-window recapture ruling stands unchanged.

## Five-head topology (P4.3 — locked; no merge authority is assumed anywhere)

Stacked branches, each PR targeting `main`; merges happen only per-PR on the operator's own authority, in order:

| head | branch | base |
|---|---|---|
| B1 | `s4-floor/b1-codex-liveness` | `main` at branch time (product bytes proven equal to `8981bfd` via `git diff --exit-code 8981bfd HEAD -- src tests harness schemas CMakeLists.txt` before branching) |
| A | `s4-floor/a-floor-core` | head of `s4-floor/b1-codex-liveness` |
| C | `s4-floor/c-consent-no-carrier` | head of `s4-floor/a-floor-core` |
| B2 | `s4-floor/b2-torn-tail` | head of `s4-floor/c-consent-no-carrier` |
| E | `s4-floor/e-a5-surfaces` | head of `s4-floor/b2-torn-tail` |

Restack rule: when a predecessor gains review-fold commits, every later branch rebases onto the updated predecessor BEFORE its own PR review; a later slice never starts its panel on a stale parent.
If the operator merges predecessors as the stack proceeds, later branches may rebase onto `main` equivalently — either way the base is stated in that head's PR body.

---

## SLICE B1 — codex liveness + the pack-warning carrier (own head/PR)

### Task 1: extend `Warning` and its JSON mapping (the forward-usable carrier)

**Files:** Modify `src/core/pack/pack.hpp:21-24`, `src/core/report/envelope.cpp` (pack-report serialization), `schemas/biv-json-envelope.v1.schema.json`; Test `tests/test_envelope.cpp`, `tests/test_pack.cpp`.
**Interfaces — Produces:** `struct Warning { std::string kind; std::string path; std::optional<std::string> artifact; std::optional<std::uint64_t> bytes; };` JSON: `artifact`/`bytes` OMITTED when unset; `bytes` unit is bytes.

- [ ] Write the failing test: a `Warning` with `artifact`+`bytes` serializes both fields; one without them serializes neither (assert key ABSENCE, not null).
- [ ] Run it; expect FAIL (fields don't exist).
- [ ] Add the two optional members + serializer branches + schema properties.
- [ ] Run the full envelope/pack suites; expect PASS with zero changes to existing warning expectations.
- [ ] Commit (`feat(pack): extend Warning with optional artifact/bytes`).

### Task 2: default-visible warnings rendering in non-JSON pack output

**Files:** Modify `src/cli/main.cpp:44-50` (`emit_pack_text`); Test `tests/test_cli.cpp`.
**Interfaces — Produces:** default text renders every `PackReport.warnings` row; kind-specific shapes: `SessionLiveAtPack` → one MAY-worded line naming the session (`/* m-3 spelling at consumer review */`; the line MUST contain "may" and MUST NOT assert the session IS active); `TornTailDropped` → one line naming the artifact and the exact byte count; unknown kinds → a generic kind+path line (forward-usable).

- [ ] Write the failing test: a report carrying one `SessionLiveAtPack` warning renders exactly one MAY line in default output; a warnings-free report renders NO warning line (absence asserted on the output text).
- [ ] Run; expect FAIL (prune advisories only today).
- [ ] Implement the renderer loop in `emit_pack_text`.
- [ ] Run; expect PASS. Exit codes unchanged (`exit_for_warnings` untouched).
- [ ] Commit.

### Task 3: codex tail-record liveness derivation

**Files:** Modify `src/adapters/codex/codex.cpp` (the rollout reader + the `SessionRecord` builder at the `.live_at_pack = false` literal, `:374-392` at baseline); Test `tests/test_adapter_codex_collect.cpp` + new rollout fixtures under `tests/fixtures/codex_store/`.
**Interfaces — Produces:** `live_at_pack` derived per m-2 `170500` §4: TERMINAL tail types = `{task_complete, turn_aborted, thread_rolled_back}` ⇒ `false`; ANY other tail — other type, dangling tool call, truncated final line, unparseable record, EMPTY file — ⇒ `true` (fail-closed). Downstream propagation untouched.

- [ ] Write the failing tests over the FULL tail matrix (P3 + R1's paired delimiter controls — one fixture per row, all asserting the derived flag): `task_complete` WITH its terminating LF ⇒ false; `task_complete` WITHOUT a final LF ⇒ false; `turn_aborted` ⇒ false; `thread_rolled_back` ⇒ false; an ordinary nonterminal type (`session_meta`) ⇒ true; dangling `custom_tool_call` ⇒ true; a COMPLETE but malformed final JSON line ⇒ true; a TRUNCATED final JSON line ⇒ true; a ZERO-BYTE file ⇒ true; and the decisive regression row — an EARLIER terminal `task_complete` record followed by a corrupt final tail ⇒ true (no scan-back may rescue it).
- [ ] Run; expect FAIL (hardcoded false makes every ⇒-true case fail).
- [ ] Implement `terminal_tail_type()` with NO SCAN-BACK and EXACT record extraction (R1): the final RECORD is the last LF-delimited line, where a single terminating LF terminates the preceding record and is NOT itself an empty record (canonical JSONL — the shipped rollout fixtures end in byte `10`); zero-byte input is the empty-file LIVE case; a genuine trailing blank or malformed record is LIVE and is never scanned past; only a final record that parses AND whose `type` is one of the three terminal spellings yields false. Replace the literal.
- [ ] Run collect suite; expect PASS incl. the regression row; claude suite untouched-green.
- [ ] End-to-end pack test: live codex fixture ⇒ exactly one `SessionLiveAtPack` warning rendered (task 2's line); terminal fixture ⇒ the NEGATIVE CONTROL — warning line ABSENT from default output (design §7 test 3).
- [ ] Commit. **Slice head exit:** suites green; PR; panel per panel-at-SHA; receipts: none GREEN-abled here.

## SLICE A — floor core + C1 head, one head (own head/PR; the same-commit task is 4)

### Task 4: the version-floor unit + allowlist deletion + mirror (checkpoint 1 of Slice A's ONE commit)

**Slice-A commit law (P1):** tasks 4–6 are RED/GREEN CHECKPOINTS that accumulate into ONE commit, made at the end of task 6 — no intermediate commit exists, so no commit ever touches a floor constant while leaving a consumer or the mirror behind.

**Files:** Create `src/adapters/version_floor.{hpp,cpp}`, `harness/ci/check_version_floor_mirror.py`; Modify `src/adapters/codex/install.cpp` (delete `validated_codex_version` `:194-196`; admission call sites), `src/adapters/claude_code/install.cpp` (delete `:331`), `CMakeLists.txt`; Modify the FULL mirror set (exact in-file consumers — no separate schema file exists): `harness/scenarios-e3/e3-dual-resume.json:24,42`, `harness/bivharness/e3.py` — `version_in_validated_range` `:766-778` (→ the mirror contract), the `_version_gate_agents` call site `:1684-1687`, the scenario required-field/type checks `:2359-2374` (retired key replaced everywhere), `harness/selftest/test_e3_asserts.py` (its prefix assertions); Test `tests/test_adapter_codex_install.cpp`, `tests/test_adapter_claude_install.cpp` (flip ledger rows), `harness/selftest/`.
**Pin check (exact mechanism):** `harness/ci/check_version_floor_mirror.py` parses the `FloorRow` constants out of `src/adapters/version_floor.cpp` and the mirror table in `harness/bivharness/e3.py` and exits nonzero on any mismatch; wired beside the existing `harness/ci/` checks. Run: `python3 harness/ci/check_version_floor_mirror.py` — expected: exit 0.
**Interfaces — Produces:**
```cpp
namespace biv::adapters::version_floor {
struct FloorRow { std::string_view min_line; std::string_view surveyed_through; };
FloorRow row_for(std::string_view agent);            // "codex" -> {"0.142","0.144"}; "claude-code" -> {"2.1","2.1"}
struct Parsed { /* numeric components */ };
std::optional<Parsed> parse_grammar(std::string_view version);   // full grammar or nullopt
enum class Order { less, equal, greater };
Order compare_line(const Parsed& a, const Parsed& b);            // line-grain total order
inline constexpr std::string_view kBasisNewerThanHost = "basis_newer_than_host";
inline constexpr std::string_view kBasisUnorderable  = "basis_unorderable";
}
```
Per-session admission at each leg's call site: `parse_grammar(basis)` fails ⇒ `failed` + `kBasisUnorderable` (BEFORE any comparison); else `compare_line(host, basis) == less` ⇒ `failed` + `kBasisNewerThanHost`; else admitted.
E3 mirror contract: grammar-valid single version AND line ≥ MIN, `newer_than_surveyed` recorded; probe oracle preserved.

- [ ] Failing unit tests for `parse_grammar` (accept real semvers; reject absent/null-shaped/NUL-bearing/non-numeric — the FX-VF-O4 input classes) and `compare_line`.
- [ ] Implement the unit; unit tests PASS.
- [ ] Failing install tests per leg: FX-VF-O2 (direction refuse, detail transported), FX-VF-O4's 32 keys (grammar-before-ordering: the NUL-bearing fixture carries a REAL NUL byte), FX-MG-7 both legs (hostile basis set, per-leg).
- [ ] Delete both allowlist gates; wire admission; flip-ledger rows updated in the SAME change (list every flipped assertion in the PR ledger); diff NOT widened into below-MIN/non-version refusals.
- [ ] Update the mirror set (all four in-file consumer sites + the scenario pins + selftests) and write the pin-check script; harness selftests green incl. the forward-host acceptance (design §7 test 5); pin check exit 0.
- [ ] CHECKPOINT — no commit; proceed to task 5 (Slice A commits once, at task 6).

### Task 5: verdict restructure + the unreadable gate + mapper branch (checkpoint 2 of Slice A's ONE commit)

**Files:** Modify `src/adapters/adapter.hpp:108` (Verdict), both `probe_capabilities`, `src/core/open/sessions.cpp:229-243` (gate) and `:318-326` region (mapper's new `failed`-with-version-detail branch), `src/core/open/render.cpp:187-241`, `src/core/report/envelope.cpp:142-146`, `schemas/biv-json-envelope.v1.schema.json`; Test `tests/test_sessions.cpp`, `tests/test_render.cpp`, `tests/test_envelope.cpp`.
**Interfaces — Produces:** `enum class Verdict { readable, unreadable, absent }` + `bool newer_than_survey` with the construction invariant (`newer_than_survey==false` unless readable; single factory path; debug-asserted); wire spelling derived deterministically (`readable-newer-than-survey` / `readable` / `unreadable` / `absent`); `agent_version` parsed iff readable, else `"unknown"`; sessions gate: `unreadable`/`absent` ⇒ per-session `agent_not_validated_failed` rows, reasons `host-version-unreadable`/`store-absent`, zero adapter calls, exit 2; mapper: adapter `failed` + version detail ⇒ `agent_not_validated_failed` + reason `basis-newer-than-host`/`basis-unorderable` (hyphenated); non-version `failed` rows unchanged.

- [ ] Failing tests: FX-VF-O5's 12 keys + CANON-3 row vectors (the FX-MG-9 burden — record its own CIM in the fixture comment); the invariant/wire test (design §7 test 6, all four spellings); the mapper transport test (O2's exact-row keys, comparator marked pending-pin for `detail`).
- [ ] Implement; suites green; flip-ledger rows for `test_envelope`/`test_render`/`probe-envelope-v1.json` listed.
- [ ] CHECKPOINT — no commit; proceed to task 6.

### Task 6: pack MIN omit-loud + watermark disclosure (checkpoint 3 + Slice A's ONE commit)

**Files:** Modify `src/core/pack/pack.cpp:533-575` region (classify before `manifest_entry_for`; omitted sessions never reach `agent_sessions`), `src/core/open/render.cpp` (the §A7.9 loud line on `readable-newer-than-survey`); Test `tests/test_pack.cpp`, `tests/test_render.cpp`, fixtures for FX-VF-P1 (below-MIN inputs codex `0.61.0`, claude `2.0.5`), P2, P4 (above-survey `0.300.0`/`2.9.0`), O3, O7 (boundary inputs at/above survey, FROZEN spellings from CANON-7).
**Interfaces — Produces:** pack skip-loud report rows naming id + version + MIN + reason; disclosure line fires iff derived state is `readable-newer-than-survey`.

- [ ] Failing tests: P1's 10 keys; P2/P4 entry-schema-1 keys (writer stays at 1 — no manifest change); O3's 8 keys; O7's 8 keys (at-survey no-loud-line is the negative control).
- [ ] Implement; suites green.
- [ ] **THE ONE SLICE-A COMMIT** — tasks 4+5+6 together: constants + EVERY MIN and `surveyed_through` consumer (admission call sites, verdict/watermark state, pack-MIN disposition, disclosure line) + the full mirror set + the pin check (`feat(adapters): version floor + C1 conjunction, one head — allowlist retired, mirror + pin check same-commit`). **Slice head exit:** PR + panel; then EXECUTE receipts GREEN-abled by A (mutation→RED→revert, evidence filed): `FX-VF-O3/{codex,claude}/disclosure-default-visible`, `FX-VF-O6/{codex,claude}/no-image-field-in-derivation` (the CANON-4 sweep test rides task 5's derivation purity), `FX-VF-O4/{codex,claude}/basis-nul-bearing/refuses-before-comparison`, `FX-MG-7/{codex,claude}/full-grammar-red`, `A5.8/silent-promotion` (raise `surveyed_through` only, oracle + O7 inputs FROZEN, confirm inputs not retuned). Each carries the discriminating-input-class precheck note (all five predate-or-straddle A7).

## SLICE C — consent-no carrier (own head/PR)

### Task 7: carrier reorder + chosen row (checkpoint 1 of Slice C's ONE commit)

**Slice-C commit law (P2):** tasks 7–8 are RED/GREEN checkpoints accumulating into ONE commit at the end of task 8 — task 7 alone cannot green the staging-dependent tests and does not claim to.

**Files:** Modify `src/core/open/sessions.cpp` (the `run_session_leg` order per design §3: entry rows → absent/unreadable gates → consent fork; consent-no calls `adapter->install(…, Consent::no)` with the workspace-staging target; `store_write_bits_absent` moves inside the consent-yes branch; the dead mapper `:323-326` becomes the chosen row; the `:308-314` lookup-miss hardening — fail closed, not default-false), `src/core/open/sessions.hpp` (new `Row::sessions_staged` `/* m-3 spelling at consumer review */`), `src/core/support/error.hpp`/`error.cpp` + `src/core/report/envelope.cpp` + `schemas/biv-exit-map.v1.json` (ONE new 0-returning kind — C's error-cluster window), `src/core/open/render.cpp` (staging report + guidance); Test `tests/test_sessions.cpp`, `tests/test_envelope.cpp` (row-count pin moves inside this window), `tests/test_cli.cpp`.
**Interfaces — Produces:** the §3 normative order; `Outcome::staged` ⇒ the chosen row ⇒ new kind ⇒ exit 0; workspace-staging write failure ⇒ existing `session_install_failed` + errno convention, exit 2.

- [ ] Failing tests EXECUTABLE AT THIS CHECKPOINT (the shipped adapters suffice — no staging behavior is asserted): design §7 test 1 in ALL THREE legs — unreadable, absent-agent, AND store-missing — × consent-no ⇒ zero adapter calls, zero staging (provable from the gate reorder alone); the chosen-row/kind mapping unit tests (`Outcome::staged` ⇒ the chosen row ⇒ the new 0-returning kind); the `:308-314` fail-closed hardening test.
- [ ] Implement the reorder + row + kind + hardening; the checkpoint tests green.
- [ ] DEFERRED to task 8 (they need real staging): design §7 tests 2, 7, 8, and the F57 operation pair (consent-no exit 0 WITH staged bytes + same-run refusal/quarantine exit 2).
- [ ] CHECKPOINT — no commit; proceed to task 8.

### Task 8: adapter consent-no staging + the A9 sidecar (checkpoint 2 + Slice C's ONE commit)

**Files:** Modify `src/adapters/codex/install.cpp` (the consent-yes pipeline `:406-480` runs for both consents; destination = `<WS>/.biv/agents/codex/sessions/YYYY/MM/DD/…` sealed dated layout under consent-no; the metadata-only branch `:499-509` deleted), `src/adapters/claude_code/install.cpp` (same, `:533-613`/`:650-660`, layout `<WS>/.biv/agents/claude-code/projects/<key>/…`), `src/core/open/sessions.cpp` (the ONE sidecar writer: aggregate succeeded staging across agents after all install calls, write `<WS>/.biv/agents/manifest.json` with the three sealed members — id_map, provenance chain, pair-set applied — no envelope pinned; publication failure ⇒ divergence per design §3); Test `tests/test_adapter_codex_install.cpp`, `tests/test_adapter_claude_install.cpp`, `tests/test_sessions.cpp` (FX-VF-O1's staged/minted/rewritten/sidecar/idmap/repack keys per CANON-2/2.5/2.6 — `…-exact` comparators built, marked pending-pin on `detail` only where a row object is asserted), harness scenario flips (`open-consent-no.json`, `open-deny-default.json` — flip-ledger rows).
**Interfaces — Produces:** staged bytes install-ready (ids minted AND written, in-pair paths rewritten at stage time, verify run); sidecar content per sealed A9/F64. Exact test map (R2): task 8 closes design §7 tests 2, 7, 8 and the operation-complete F57 pair; ALL of test 9 belongs to task 11 (the fields it asserts first exist there).

- [ ] Failing tests first: staged-artifact-set, identity binding, path-pair set, sidecar members (CANON-2/2.5/2.6), PLUS the task-7 deferrals — design §7 tests 2 (one sidecar + publication-failure divergence), 7 (read-only host store cross-product), 8 (unwritable workspace), and the F57 operation pair. (The C1 `created_paths`-absent-on-staged assertion moves to task 11, where the field first exists.)
- [ ] Implement; ALL slice-C tests green; harness scenario flips listed.
- [ ] **THE ONE SLICE-C COMMIT** — tasks 7+8 together. **Slice head exit:** PR + panel (consumer leg reviews the chosen-row/guidance spellings); no receipts GREEN-abled here (O1 keys are BOUND arms, not mutation arms).

## SLICE B2 — torn-tail (own head/PR; codex branch 3 only after B1)

### Task 9: A3.3 four branches at collect + facts to pack + branch-4 refusal

**Files:** Modify `src/adapters/adapter.hpp` (`SessionRecord` gains `struct TornTail { std::string artifact; std::uint64_t bytes; }; std::vector<TornTail> torn_tails;`), `src/adapters/codex/codex.cpp` + `src/adapters/claude_code/claude_code.cpp` (jsonl-artifact tail rule at collect for live-flagged sessions: T = final segment after last LF; branch 1 empty ⇒ verbatim; branch 2 valid JSON ⇒ retain + append exactly one LF; branch 3 invalid AND live ⇒ drop exactly T + record fact; branch 4 invalid AND not-live ⇒ verbatim; interior segments never inspected), `src/core/pack/pack.cpp` (each fact ⇒ `Warning{kind:"TornTailDropped", path:<session id>, artifact, bytes}`), both `install.cpp` (branch-4 decode refusal typed `undecodable_line` `/* m-3 spelling at consumer review */`); Test collect suites (four branches × two legs, retained-prefix BYTE EQUALITY in every branch; `torn_tail_dropped.bytes == len(T)` exactly; mid-file invalid line + clean tail ⇒ verbatim, no fact), `tests/test_pack.cpp` + `tests/test_cli.cpp` (design §7 test 4: exact artifact/bytes in structure, default text, JSON).

- [ ] Failing tests per branch per leg (8 fixtures + the interior-segment control + the empty-file compose with B1's liveness); implement; green.
- [ ] Codex branch-3 fixture MUST drive liveness through B1's real derivation (a branch-3 test green on a hardcoded flag fails review — the standing law).
- [ ] Commit. **Slice head exit:** PR + panel; no mutation receipts here.

## SLICE E — migration engine + loud-install transport (own head/PR; after B2 at `install.cpp`)

### Task 10: the migration unit + MG-FX + reporting

**Files:** Create `src/adapters/migration.{hpp,cpp}` (agent-generic: table row = `{agent, source_interval, target_interval, record_signature, field, vendor_default, verdict: MIGRATE|REFUSE}`; evaluation pre-publish inside install; abstain-by-construction when host version unparseable — retained sealed invariant, product-unreachable post-A7; idempotent; no-op on source==target; the shipping table = MG-1 REFUSE for claude ≤2.1.202-shape onto ≥2.1.207 line), Modify both `install.cpp` (call sites), `src/adapters/adapter.hpp` (`migrations_applied` on the result row), `src/core/open/render.cpp` (the FX-MG-6 golden line — sentence SHAPE binding: actor-subject "Bivpak's migration", positive write clause, negative attached to conversation RECORDS; token spelling tunable), `CMakeLists.txt`; Test new fixture corpus (MG-FX per its exact constants: `fixture-agent`, `[1.0.0,1.0.5]`→`[1.1.0,1.1.9]`, `fx-meta`/`fx_required`/`""`; the 2.1.202-shape image), FX-MG-1/2/3a/3b/3c/4/5/6/8 fixtures + FX-MG-1R.

- [ ] Failing tests first (the four interval-boundary legs; byte-identity FX-MG-4 hostile leg; idempotency FX-MG-5; golden line + default visibility FX-MG-6; FX-MG-8 unreadable control is product-unreachable — implement as a unit test on the engine, labeled so); implement; green.
- [ ] Commit.

### Task 11: `created_paths` + caveat + announcement/recovery rendering

**Files:** Modify `src/adapters/adapter.hpp` (`created_paths` on `InstallSessionOutcome`: store-relative, files-only, sorted, present EXACTLY on installed host-publish-succeeded rows — ABSENT on refusals and consent-no staged rows), both `install.cpp` (populate on publish), `src/core/open/sessions.cpp` (exactly one `AgentCaveat{kind:"host-version-unverified"}` per agent iff ≥1 readable-newer session INSTALLED), `src/core/open/render.cpp` (pre-consent announcement naming V + `surveyed_through` uncertainty + resume-unvalidated — never the retired prefix set; created-paths listing; the three-clause recovery paragraph, each clause separately rendered); Test install/session/render suites (the C2 pins incl. `host_version_unverified` true/false split and the at-survey negative control — design §7 test 9's second half).

- [ ] Failing tests — including the RELOCATED C1 pin (staged consent-no rows carry NO `created_paths`, asserted now that the field exists; P2's relocation) and the C2 pins; implement; green; commit.
- [ ] **Slice head exit:** PR + panel; then EXECUTE the E-GREEN-abled receipts: `FX-MG-1R/recovery-visibility`, `FX-MG-3a/recovery-visibility`, `FX-MG-6/default-visibility`, `A5.8/tier2-announcement/default-visibility`, `A5.8/tier2-createdpaths/default-visibility` (content arms stay green — sibling rule), `A5.8/tier2-recovery/{identify,removes-ours,vendor-warning}-visibility` (one clause hidden per mutation, other two GREEN) — each with the discriminating-input-class precheck note and the loud path driven by A's trigger, never a tier concept.

## Verification & exit ledger

- Per-slice: full ctest + harness selftests green at the head; panel-at-SHA; E2 evidence at the head; flip ledger in the PR body (decided-not-deleted).
- Receipts after this plan completes: NINE executed at slice A (`FX-VF-O3`×2, `FX-VF-O6`×2, `FX-VF-O4`-nul×2, `FX-MG-7`×2, `A5.8/silent-promotion`) + EIGHT at slice E (`FX-MG-1R`, `FX-MG-3a`, `FX-MG-6`, the five `A5.8/tier2-*` visibility arms) = SEVENTEEN executed, + `FX-MG-9` DISSOLVED-PENDING-RATIFICATION (burden proof = the O5/CANON-3 fixtures landing in task 5) = the EIGHTEEN accounted, every one. Receipt evidence format per the execution law, filed under `results/receipts/`.
- The frozen open-envelope oracle: recaptured ONCE after slice A's act lands (coordinate with the matrix Arm-1 window through the orchestrator; not a per-slice action).

## Out of scope (restated)

Slice D and all `src/core/manifest/*`; the base `list`/`info` verb; the five matrix arms; sealed-doc edits; host-store surfaces; R-4.1(ii); R-4.2; the pdc RUNCARD write; `.github/`; any mitigation of the corrected old-reader refusal.

## Operator-judgment items

None open at plan time — the m-3 spellings ride the consumer-review leg; merge is the operator's; the VP count pass and the pinned-`detail` addendum are upstream signals consumed when they land.
