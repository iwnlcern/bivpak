# Sub-step 2a — the format act — implementation plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:executing-plans, task-by-task, steps as checkboxes.

**Goal:** Execute sealed §2.3+G+H+N — the `repos[]` manifest cell lands (writer + parser + round-trip in ONE symmetric commit, the `require_empty_array("repos")` fence retiring inside it), and the engine conforms to LOCKED N (the N-R3 precedence lattice, the V-N-1 mirror retirement, flag-2 `bundle_carried` suppression, and the restore-side `shallow_pointer`-before-`payload_only_unborn` ordering) — with parse-reach only: zero new engine callers, zero format-version bump, zero bytes outside m-1's two pre-stated surfaces.

**Architecture:** Surface A (engine, `src/core/repo/`) and Surface B (manifest, `src/core/manifest/`) stay decoupled at 2a: the classifier/restore work lands against the engine harness; the manifest work lands against manifest tests with constructed entries; nothing wires verbs to the engine (that is 2b, behind R-4.48 + m-4's wiring bar). **Carrier decision (this plan's one engineering choice, grounds stated):** `Manifest` gains `std::vector<repo::RepoEntry> repos` — `types.hpp:189-191`'s own comment anticipates RepoEntry as the wire carrier ("T5 serializes only the schema members below"), the include edge `manifest.hpp → core/repo/types.hpp` is cycle-free (verified: core/repo includes only core/support), a single carrier removes the two-sources-of-truth divergence class V-N-1 polices, and 2b consumes the parse result conversion-free. Any RepoEntry↔schema mismatch met mid-build is S-FA-1: STOP UP, never a local mapping invention.

**Tech stack:** C++23, simdjson (parse), the project's expected<>-style typed errors, Catch2 (`tests/test_manifest.cpp`, `tests/test_repo_engine.cpp`), the `git_exec` seam as the E4 request-trace instrument.

**Sealed inputs (execution-not-amendment; where they defer or are silent → STOP UP):**
- LOCKED N `m1-addendum-N-82293732-lock-20260827` (post-stamp `3ba71be1…`) — N-R1..N-R5, V-N-1, V-N-2 (three clauses), FX-N legs (a)–(j), flags 1–3.
- LOCKED M rev8 `m1-addendum-M-2966b839-lock-20260825` (post-stamp `57d89625…`) — CONSUMED, never edited; any need to touch an M surface is S-FA-5.
- Sealed manifest-format §2.3 as amended by G (unborn `head_state`, `sha` null ⟺ unborn, `notes[]` + first member + `UnknownNote` protocol) and H (`capture_mode` absence license).
- m-1's fence pre-statement `pdc:master/relays/intg-substep2a-format-act/DESIGN-planner-20260830-151655.md` — V-FA-1..8, S-FA-1..6, both E4/V5 readings; the checklist this plan is written against, verbatim.
- m-4's bar (`204641`): E4 executed at this act (zero-git/zero-network by request trace); any format-version bump is a VETO.

## Global constraints (every task implicitly includes these)

1. **Scope**: bytes ONLY in `src/core/repo/{classify.cpp,types.hpp,restore.cpp}`, `src/core/manifest/{manifest.hpp,manifest.cpp}`, `tests/{test_repo_engine.cpp,test_manifest.cpp}`. Any other byte — any M-surface (`git_exec`/consent seam), m-2 seam (`agent_sessions[]`), m-3 surface, `schemas/`, `harness/`, `.github/` — is V-FA-1 red. New user-facing wording, envelope kinds, exit rows, or schema-artifact rows are S-FA-4 (parse errors follow the EXISTING manifest typed-error patterns).
2. **The one symmetric commit** (V-FA-2/V-M-INT-2): writer + parser + round-trip witness + fence retirement land together in Task 3's single commit; no interim fence-less or asymmetric state exists at any commit boundary.
3. **Never serialized** (V-M-INT-1/V-FA-3): `promisor`, `engine_source`, any host-absolute path. Nothing beyond §2.3+G+H+N (V-M-INT-3).
4. **No `format_version` bump** (V-FA-5/N-R5). `kFormatVersion` and every version literal untouched.
5. **Parse-reach only** (V-FA-6): zero new callers of engine entrypoints; the census `git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- ':!src/core/repo' ':!tests'` returns empty at the candidate head.
6. **Evidence grep-derived at the head under review** (V-FA-7); FX-M-1's fourteen engine-seam legs stay green as the regression floor; all ten FX-N legs execute ((i)/(j) as m-1's review censuses — this plan PREPARES their exact commands as evidence).
7. **Two platforms** (V-FA-8): macOS suite + the chartered Ubuntu 24.04 amd64 parity container at the candidate head, per the proven four-phase instrument (Task 4).
8. **STOPs**: S-FA-1..6 + the generic defer-or-silence rule — route UP through the pair-planner; never a keyboard call.

**Branch:** `intg/format-act` cut from the pinned current `main` (product roots byte-identical to landed `81066ef` — re-verify at cut: `git diff --quiet 81066ef..HEAD -- src schemas tests harness CMakeLists.txt`). Worktree `../bivpak-intg-format-act`. The primary worktree's branch is never switched.

---

### Task 1 — Surface A: the N-R3 lattice in the classifier, the V-N-1 mirror retirement, flag-2 suppression

**Files:** Modify `src/core/repo/classify.cpp`, `src/core/repo/types.hpp` (the `Shallow` struct only). Test `tests/test_repo_engine.cpp`.

**Interfaces:** Produces `Shallow` = `{ std::vector<std::string> boundary; }` EXACTLY (both mirrors retired); `RepoEntry.shallow` engaged for every shallow source that produces an entry, any `head_state`. Consumers (Task 2 restore, Task 3 writer) read `sha`/`branch`/`remotes` from the ENTRY only.

- [ ] **Step 1: write the four failing real-source tests** — FX-N (f·i), (f·ii), (h·i), (h·ii), each constructing a REAL source per N's sealed recipes (temp HOME + `GIT_CONFIG_GLOBAL` + `GIT_CONFIG_NOSYSTEM`, `file://` only, matching the existing test_repo_engine fixture idiom):
  - (f·i) `clone --depth 1 file://…` + `checkout --orphan` + delete surviving refs → classify → REQUIRE: `entry.shallow` engaged with the non-empty boundary, `head_state == unborn`, `!entry.sha`, orphan branch name recorded, `entry.local_refs.empty()`, no bundle, no eligibility. *(Named mutant pinned: the return-before-probe ordering — this test is its red.)*
  - (f·ii) the P-N2 shape (refs survive) → the SAME cell; REQUIRE no bundle artifact, `local_refs` empty *(mutant: bundling-branch routing)*.
  - (h·i) `clone --depth 1` (NO orphan) + one modified tracked file → REQUIRE: N's cell, `fence == Fence::none`, no `repo_dirty_unsupported` issue *(mutant: dirty-before-shallow retained)*.
  - (h·ii) shallow + orphan (staged content makes `status --porcelain=v2` non-empty) → N's cell via the unborn path, dirt never consulted *(mutant: dirty-hoisted-above-all)*.
  - Plus the preservation controls: the existing "unborn before dirt" test (`test_repo_engine.cpp:798`) stays untouched and green; one non-shallow control per tier-1 fence already exists — verify by name, do not rewrite.
- [ ] **Step 2: run, verify FAIL** — (f·i)/(f·ii) fail on the missing cell (unborn returns first); (h·i) fails on `Fence::dirty`; compile failures on `Shallow` member changes come with Step 3.
- [ ] **Step 3: implement** — in `classify.cpp`: run the shallow probe (`rev-parse --is-shallow-repository` + `.git/shallow` read) after HEAD/ref resolution and BEFORE the unborn return (today `:262`) and BEFORE the dirty probe (today `:314`); tier-1 structural fences stay strictly above (no shallow state populated before a tier-1 return — leg (j) clause 2); for shallow entries suppress/clear the unborn branch's `bundle_carried` collection (today `:209-215`) per flag 2; `types.hpp`: `Shallow` becomes boundary-only (retire `sha`, `remote_urls`); delete the population copies (today `classify.cpp:342, 352-354`). Non-shallow control flow byte-preserved (unborn-before-dirt untouched). Penumbra-recording placement is implementation latitude; any SEMANTIC interaction discovered is S-FA-6 → STOP.
- [ ] **Step 4: run green** — the four new arms + the full `test_repo_engine` binary (the FX-M-1 fourteen must stay green; the existing shallow tests updated only where they asserted the retired mirrors — assert entry-sourced facts instead).
- [ ] **Step 5: commit** — `feat(engine): N-R3 precedence lattice — shallow detection above the unborn return and the dirty fence; Shallow reduced to boundary-only (V-N-1); bundle_carried suppressed for shallow (LOCKED N flag 2)`

### Task 2 — Surface A: restore ordering — `shallow_pointer` precedes `payload_only_unborn` (reconcile I3)

**Files:** Modify `src/core/repo/restore.cpp` (the branch order at today's `:443-452`). Test `tests/test_repo_engine.cpp`.

- [ ] **Step 1: write the failing discriminating test** — a shallow×unborn `RepoEntry` (shallow engaged, `head_state: unborn`, no bundle, no eligibility — N-R2's own cluster) through `restore_entry` → REQUIRE `outcome == shallow_pointer` (today it returns `payload_only_unborn` — the defect verified at reconcile I3), boundary on the row, AND the request-trace instrument (the `git_exec` seam's recorded invocations) shows ZERO git calls and ZERO network class for the entry — E4's oracle asserted by instrument, never by absence of effect. Control: H's zero-ref payload-only-unborn entry WITHOUT `shallow` still returns `payload_only_unborn`.
- [ ] **Step 2: run, verify FAIL** on the outcome.
- [ ] **Step 3: implement** — move the `if (entry.shallow)` branch above the payload-only-unborn branch; nothing else moves.
- [ ] **Step 4: run green** (both arms + full binary).
- [ ] **Step 5: commit** — `fix(engine): shallow_pointer precedes payload_only_unborn — a shallow×unborn entry restores as the pointer row (sealed N-R4; fence Surface A)`

### Task 3 — Surface B: THE ONE SYMMETRIC COMMIT — carrier + writer + parser + round-trip + fence retirement

**Files:** Modify `src/core/manifest/manifest.hpp` (the `repos` carrier + `#include "core/repo/types.hpp"`), `src/core/manifest/manifest.cpp` (writer + parser), `tests/test_manifest.cpp`.

**Interfaces:** Produces `Manifest.repos : std::vector<repo::RepoEntry>`; `serialize` emits §2.3-as-amended exactly; `parse` fills the same carrier with transient members defaulted. Consumed by 2b unchanged.

- [ ] **Step 1: write the failing tests** (all in `tests/test_manifest.cpp`, simdjson-DOM row-bound, the sub-step-1 discipline — exact cardinality, exact member sets, distinct values; each FX-N named mutant noted in a comment beside its killing assertion):
  - **the populated round-trip**: a two-entry manifest — entry 1 the §2.3 exemplar shape (born, `capture_mode: overlay`, eligibility object with structured proof, `local_refs` with all three availability states' fields, capture object with two patches + `forced_payload` + `capture_env`, `sparse: null`, one `NonCarriedRefsNote` + one `UnknownNote` with verbatim bytes); entry 2 N's cell (shallow `{boundary: [<40-hex>]}`, `capture_mode` ABSENT, no eligibility, `local_refs` empty, `bundle` null, born + 40-hex sha) — serialize → parse → REQUIRE field-for-field equality (the witness V-M-INT-2 mandates in THIS commit).
  - **G's shapes still round-trip inside repos[]**: an unborn entry (`head_state: "unborn"`, `sha: null`, branch name) — G's nullability rule reused verbatim.
  - **FX-N manifest/parser arms**: (b·i)–(b·iv) the marker-disjoint absence license (b·iii RED: born non-shallow ref-bearing entry with `capture_mode` absent = typed parse error); (c) `shallow: null` RED; (d·i) missing `boundary` RED, (d·ii) one non-40-hex element RED, (d·iii) `boundary: []` GREEN; (e·i)–(e·vi) the cluster one-hostile-coordinate-per-arm (eligibility / bundle / non-empty local_refs / local_refs_bundle / `capture_mode:"overlay"` / `"full"` each RED with the error attributable to the violating member); (g) the promisor note member `{"kind":"promisor-source"}` round-trips + the `UnknownNote` control.
  - **never-serialized proof** (V-M-INT-1): serialize an entry with `promisor=true` and an engaged `engine_source` → REQUIRE the output contains NEITHER key and no host-absolute path (byte-scan of the serialized form).
  - **fence retirement's negative**: retire `tests/test_manifest.cpp:571-575`'s `step2-plain-dir-only` assertion; REPLACE with: `"repos": [1]` still a typed parse failure whose detail follows the existing manifest error patterns (no new wording class — S-FA-4).
  - **empty-form controls PRESERVED**: `:188/:225/:487/:532` stay as-is (empty `repos` remains valid §2.3).
- [ ] **Step 2: run, verify FAIL** — compile failures on the missing carrier first; then parse failures on the fence.
- [ ] **Step 3: implement in ONE commit-scoped change**: the carrier member; the writer replacing `manifest.cpp:849-851`'s hardcoded empty array — per-entry emission of exactly: `id, relpath, kind, parent_id, remote, remotes[], sha (null ⟺ unborn), branch, head_state ∈ {branch,detached,unborn}, dirty, capture_mode (ABSENT iff shallow-present OR H's zero-ref payload-only-unborn shape; else the enum), eligibility?, local_refs[], local_refs_bundle?, capture{staged_patch,worktree_patch,payload_prefix,forced_payload[],capture_env}, bundle?, sparse: null, notes[] (G member protocol + promisor-source + UnknownNote verbatim), shallow? {boundary[]}` — and NOTHING else; the parser replacing the `:971` fence call with full acceptance + the N-R2 cluster BOTH directions + G/H licenses + typed errors (the `:117` `require_empty_array` helper retires with its sole caller). Writer and parser share one field table; asymmetry is V-FA-2 red.
- [ ] **Step 4: run green** — `test_manifest` whole + `test_repo_engine` whole (floor).
- [ ] **Step 5: THE commit** — `feat(format): repos[] lands — writer + parser + round-trip per sealed §2.3+G+H+N in one symmetric commit; require_empty_array("repos") retires (V-M-INT-2/4; execution of sealed text, no format_version bump)`

### Task 4 — the evidence battery + IMPL report

- [ ] **Step 1: fence transcript at the candidate head** (each command + rc retained verbatim):
  - zero-caller census: `git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- ':!src/core/repo' ':!tests'` → empty, rc 1 (V-FA-6);
  - no-bump: `git diff <base>..HEAD -- src/core/manifest | grep -c 'format_version\|kFormatVersion'` → 0 semantic changes (the carrier addition aside, assert `kFormatVersion` literal unchanged: `grep -n 'kFormatVersion = ' src/core/manifest/manifest.hpp` byte-equal to base);
  - scope census: `git diff --name-only <base>..HEAD` → EXACTLY the six planned paths (V-FA-1);
  - never-serialized greps on the writer TU: no `promisor`/`engine_source` key emission (`grep -n '"promisor"\|"engine_source"' src/core/manifest/manifest.cpp` → empty);
  - the M-surface untouched: `git diff --quiet <base>..HEAD -- src/core/repo/git_exec.hpp src/core/repo/git_exec.cpp src/core/repo/eligibility.cpp` → rc 0 *(eligibility.cpp is out of the write set entirely)*;
  - the (i)/(j) census commands PREPARED and EXECUTED as report evidence (m-1 re-runs them at the byte review): (i) `grep -c ';' `-style member count on `struct Shallow` (exactly one member), zero mirror population sites, zero consumers of shallow-carried sha/remotes; (j) control-flow order derivation over `classify.cpp` (each tier-1 return precedes the shallow probe's first site; no shallow population before a tier-1 return; no writer path serializes a cell for `Classification::Fence` results).
- [ ] **Step 2: macOS suite** — `cmake --preset ci-macos` + build + `ctest --preset ci-macos`; candidate-attributable rows green; host-environment observations retained-labeled per the sub-step-1 precedent.
- [ ] **Step 3: the four-phase Linux parity leg** — execute the PROVEN sub-step-1 instrument verbatim (the rev12 text at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md`, Task 5 Step 3 — Phases H/R/T/S with the frozen base command incl. `openssh-client`, the pinned suite identity, the no-short-circuit rc ledger), retargeted: clone branch `intg/format-act`, receipt `rev-parse HEAD == <candidate sha>`; registered rows (R-4.35 family, R-4.38 count) retained-not-cited exactly as before.
- [ ] **Step 4: the IMPL report** (file-first): partitioned per the sub-step-1 discipline — newly measured receipts / carried evidence / registered residuals / green gates; the fence transcript; the (i)/(j) census outputs; the E4 request-trace outputs; the exact candidate sha for m-1's byte review; explicit NOT-DONE (no 2b wiring, no `--offline`-parity arm — product-scope-due per sealed N, no m-3 rendering, no merge claim).

## Acceptance criteria (ALL must hold)

1. Branch over the pinned base; commits exactly as tasked; Task 3 is ONE symmetric commit carrying writer + parser + round-trip + fence retirement together.
2. All ten FX-N legs executed at their 2a-due points: manifest arms (b)(c)(d)(e)(g) + the round-trip (a)-manifest-half at `test_manifest`; (f·i)(f·ii)(h·i)(h·ii) at the real classifier; (i)/(j) census commands executed and their outputs in the report (m-1's review re-runs them); (a)'s `--offline`-parity arm explicitly NOT claimed (product-scope-due).
3. E4: zero-git/zero-network for the pointer row asserted by request trace at the restore test.
4. `Shallow` is boundary-only; zero mirror population sites; consumers read entry fields (the (i) census green).
5. Tier-1 fences above shallow; shallow above unborn-return and dirty; unborn-before-dirt preserved for non-shallow (the (j) census + (h) arms green; `test_repo_engine.cpp:798` untouched and green).
6. `shallow_pointer` precedes `payload_only_unborn`; H's control still green.
7. FX-M-1's fourteen green (floor); full suites green on candidate-attributable rows on BOTH platforms; registered reds retained-not-cited.
8. Every global-constraint fence grep holds at the candidate head; no format_version bump; no new engine caller; no byte outside the six planned paths.

## Out of scope (hard)

Any M-surface/consent-seam byte; `agent_sessions[]`/m-2 seam; m-3 wording/rendering (the pointer-row print); `schemas/` (the biv-json envelope + exit map are m-3-reviewed artifacts of sub-step 1 — NOT this act); `harness/`; `.github/`; verb-to-engine wiring or ANY new product call site (2b, behind R-4.48 + m-4's wiring bar); the `--offline` CLI surface; the three deferred sub-step-1 Minors; merge/push/publication/release.

## Identity, coverage, and gates

- Plan identity: dispatch `intg-substep2a-plan`, `DESIGN_DOC_ID: intg-format-act-plan`, this artifact. **W-3 TERMINATED at this plan's filing, by its own clause — disclosed and chosen (audit `152011`).** The design-lineage lint red this plan's relays fire for m-1's locks is EXPECTED and UNCOVERED until master establishes coverage (`intg-format-act-plan → m1-addendum-M-2966b839-lock-20260825` and `→ m1-addendum-N-82293732-lock-20260827`); **no implementation dispatch issues until that coverage stands** (reconcile I7).
- m-1's byte review (V-FA-1..8) engages at the submitted candidate sha with the Task-4 evidence; the (i)/(j) censuses re-execute there.
- Implementation authority: the pair's delegated conditional dispatch machinery (exact-hash plan review approve → coverage standing → the bare token).
- Merge/push/release: separately gated exactly as sub-step 1; the release hold is ABSOLUTE.
