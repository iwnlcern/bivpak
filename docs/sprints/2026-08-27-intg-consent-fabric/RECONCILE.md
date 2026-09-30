# RECONCILE — intg consent-fabric sprint

The sole tracked durable reconciliation projection for this sprint root.
`PHASE: RECONCILE` relays cite the exact section they append, or state projection-pending.

## R1 — sub-step-1 audit reconciliation (2026-08-27)

Inputs: planner audit `intg-substep1/AUDIT-pair-planner-20260827-152923.md`; implementer independent audit `intg-substep1/AUDIT-pair-implementer-20260827-231149.md`.
Verdict: NO disagreements; one planner omission corrected (I3); one coverage refinement (I2); two plan traps adopted (I4, I5); every implementer finding mapped exactly once below.
Basis re-pinned by the implementer and adopted: product bytes at HEAD `b59861f` proven IDENTICAL to the confirmed base `02b51435` (`git diff --quiet 02b51435..HEAD -- src schemas tests harness CMakeLists.txt` exit 0) — audits bind to the current bytes with no stale pin.

| Finding | Agreement | Disposition (exactly one) |
|---|---|---|
| I1 headline (fabric still-open; engine already-closed, zero production callers) | agree — both seats measured independently, same result | VERIFIED CLOSURE here, against the implementer's code anchors (args.hpp:17-25, args.cpp:165-181/193-255/130-146, error.hpp:9-36, envelope.cpp, both schema artifacts) and the planner's census |
| I2 list/info inert acceptance incidentally present via the stub path (args.cpp:267-273 + main.cpp:396-400) | agree — different coverage: planner censused the stubs but did not surface the a6·14 implication | OWNED PLAN CONSTRAINT: the plan does NOT build explicit list/info flag parsing (R-6.2 owns the closed grammar); the a6·14 landing regression pins the inert observable (flagged invocation ≡ flagless) WITHOUT contractualizing arbitrary trailing-token acceptance |
| I3 `schemas/biv-exit-map.v1.json` absent from the planner's Writes inventory | agree — planner omission, verified at the bytes this seat (distinct artifact; separate selftest blob pin test_envelope.py:15; asserted test_envelope.cpp:200-203) | PLAN FENCE + ACCEPTANCE CRITERIA: the exit-map path joins the write fence, and the one-commit rule names it (both exit rows + three envelope-schema sites + derived parity rows + BOTH recomputed blob pins in the ErrKind commit) |
| I4 PROMPT B's json suppressor is a NEGATIVE pattern for PROMPT D (main.cpp:275-277 `!parsed->json` in `prompt_requested`; render-side suppression) | agree — verified at the bytes this seat; A7-R2 requires PROMPT D to render under `--json` | OWNED PLAN CONSTRAINT + review check: PROMPT D gets its OWN hook-install predicate (A7-R1 stdin+stderr TTY pair, no json term); the structural review asserts no reuse of `prompt_requested` or any json-gated prompt helper on the PROMPT D path |
| I5 the one-PTY test helper (test_cli.cpp:226-239) cannot witness A7's split-stream leg | agree — matches A7 rev1's own F1 verification | NAMED 2b DUE POINT in the plan: all five A7 behavioral legs + a7·3's split-stream topology are due at wiring sub-step 2b; sub-step 1 claims NO E2 coverage for them and makes no helper edit absent an independent locked criterion |
| I6 wiring fence reconfirmed (engine unreachable; repos fence intact at manifest.cpp:971) | agree | PLAN FENCE: zero engine bytes, zero product call sites to `run_eligibility`/`restore_entry`/`repo::capture`/any network-class engine path; POST-IMPLEMENTATION GREP PROOF rides the acceptance criteria (R-4.47 V1 / V-A6-6 shadow) |

Planner-side items already standing (no new disposition): the R-4.47 bar mapping (OBLIGATIONS §B2), the W-3 at-filing checklist (ROADMAP), the sub-step-1 leg set per the `200932` spine (a6·14/15/17/18 + zero-state half of a6·16).

## R2 — sub-step-2a (format act) audit reconciliation (2026-08-30)

Inputs: planner opening audit `intg-substep2a/AUDIT-pair-planner-20260830-152011.md`; implementer independent audit `intg-substep2a/AUDIT-pair-implementer-20260830-180353.md`; m-1's fence pre-statement `pdc:master/relays/intg-substep2a-format-act/DESIGN-planner-20260830-151655.md` (arrived between the audits; verified at both seats; EVIDENCE and checklist, not an authority edge — implementation authority remains this lane's plan→review→coverage→token machinery).
Verdict: NO disagreements on the primary bucket (still-open, non-overlapped); THREE planner census defects corrected by the implementer, each re-verified at the planner's own bytes before folding; every implementer finding mapped exactly once below.
Basis: both audits at `main@af71e82`, product roots diff-empty from the landed merge `81066ef`.

| Finding | Agreement | Disposition (exactly one) |
|---|---|---|
| I1 lock/routing basis (both post-stamps re-hashed EQUAL at both seats; m-4 GREEN; landed identity) | agree — independent measurement, same result | VERIFIED CLOSURE; the exact pins carry into the plan without reinterpretation |
| I2 `manifest::Manifest` has NO `repos` member (manifest.hpp:68-79) — the in-memory carrier missing from the planner's census | agree — planner omission, re-verified at these bytes | OWNED PLAN OBLIGATION: manifest.hpp joins Surface B's write set; a typed repos carrier mapped exactly to §2.3+G+H+N; promisor/engine_source/host-absolute excluded (V-M-INT-1/V-FA-3) |
| I3 restore ordering: restore.cpp:443-447 returns `payload_only_unborn` BEFORE the `entry.shallow` check at :449 — a shallow×unborn entry (which satisfies the first condition under N-R2's own cluster) never reaches the pointer row | agree — planner had binned the restore row already-closed whole; the ordering delta re-verified at these bytes; m-1's fence independently binds it (`shallow_pointer` precedes the payload-only-unborn return, Surface A) | OWNED PLAN OBLIGATION: restore.cpp joins Surface A; the shallow branch moves above the payload-only-unborn branch; a discriminating shallow×unborn restore witness is mandatory |
| I4 classifier census (N-R3 lattice, flag-2 suppression, V-N-1 mirrors, tier-1/unborn-before-dirt preservation boundaries) | agree — same census both seats | OWNED PLAN OBLIGATION over classify.cpp/types.hpp with FX-N (f)/(h) arms and the (i)/(j) censuses as m-1's review instruments |
| I5 capture/eligibility skips, promisor note plumbing, pointer-row shape | agree | VERIFIED CLOSURE (capture.cpp:259-266, eligibility.cpp:153-155, types.hpp:138/187-188, classify.cpp:356-357, restore.cpp:449-452); planned as UNCHANGED CONTROLS except I3's ordering |
| I6 test inventory: the four empty-form pins (test_manifest.cpp:188/225/487/532) are VALID CONTROLS, not mandatory rewrites (empty repos stays legal under §2.3); the actual retirement is the fence-specific assertion test_manifest.cpp:571-575 (`[1]` → detail `step2-plain-dir-only`) | agree — the planner's mandatory-edit characterization REJECTED, re-verified at these bytes; scalar `1` must remain a typed parse failure under the real parser, with the step-2 detail retired | OWNED PLAN OBLIGATION: preserve empty-form controls; retire/update :571-575; add the populated round-trip + the FX-N manifest/parser arms |
| I7 W-3/new-identity + authority edges (fence relay = evidence; coverage before token) | agree — matches the planner's stated choice and sequencing | OWNED GATE on the plan: W-3 termination stated; no implementation dispatch until `intg-format-act-plan -> M lock` + `-> N lock` coverage stands |

## R3 — R-4.50 claude-discover parity audit reconciliation (2026-09-06)

Verdict: NO disagreement on the still-open, already-closed, or product-overlapped buckets; Q1 confirmed independently at both seats; Q2 was DIFFERENT COVERAGE (planner: N=1 recommended; implementer: N=0 measured as sufficient) and is SUPERSEDED by the fence owner's ruling — m-2 rules the witness shape and chose N=1 EXACTLY (master `004023`, m-2 `002200` §2, m-3 `002436` T-1..T-5, CG-R7 rev2 `70600364`).
Basis: planner audit `intg-r450/AUDIT-pair-planner-20260905-215317.md`; implementer audit `intg-r450/AUDIT-pair-implementer-20260905-234709.md`; both at bivpak `8d8b7fa`/`27429e5` with product bytes equal to the fence pin `9e1a72d` and to `origin/main` `bbf297e`.

| Finding | Agreement | Disposition (exactly one) |
|---|---|---|
| still-open at `claude_code.cpp:581` (early return in the env arm; body :570-596) vs codex `:1193-1206`; three fenced files byte-identical to the fence pin | agree — same bytes, same hashes, both seats | VERIFIED CLOSURE; the plan's Task 1 Step 4 replaces exactly :570-596 with the reference shape |
| no test asserts the suppression; the only discover test (:97-116) is env-present/default-absent and stays green | agree | VERIFIED CLOSURE; the existing case is unchanged (plan Task 0 Step 4, Task 1 Step 5) |
| overlap: open `front()` env-first unchanged; pack duplicate gate = ROW 5's interim; install.cpp has its own resolution; stub_biv.py:140-146 = S-CP-2 live | agree | VERIFIED CLOSURE; S-CP-2 routes to m-3 at landing; no harness byte in-lane |
| Q1 the canonical cross-repo edge fires structurally (no DESIGN origin for the fence id; approve not an m-2 peer) | agree — independently confirmed at the lint bytes (relay-lint.py xroot_authority) | CURED UPSTREAM: m-2 origin `002200` filed; m-2.implementer peer approve pending; the plan pins that commit and re-measures root-mode before filing |
| Q2 count-gate cells: planner N=1 (arm a) vs implementer N=0 (SECTIONs in the existing case; OverallResultsCases=1 measured on a multi-SECTION case) | different coverage — the implementer's SECTION measurement is CONFIRMED and is the basis for rows-as-SECTIONs INSIDE the one new case | SUPERSEDED BY OWNER RULING: N=1 exactly (m-2: tests are never shaped to hold a pin); cells transcribed in the same commit under m-3's T-1..T-5 / CG-R7; the plan's Tasks 2–4 carry it |
| O-1 lexically_normal trailing-slash property of the reference shape | agree (disclosed, not a STOP) | DISPOSED by m-2: inherited by parity; tightening = V-CP-2 red; ROW 2 uses a collapsing spelling |

Plan artifact: `plans/PL-intg-r450-discover-parity-20260906.md` rev1 DRAFT @ sha256 `3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee` (files for review only after the approve lands and the edge re-measures GREEN).

## R4 — sub-step 2b (wiring at product scope) audit reconciliation (2026-09-15)

Verdict: AGREE on all four buckets and on every reachability measurement (both seats re-derived the same zero-hit greps at `186adf7d`).
The implementer's nine findings I2B-01..09 are each dispositioned EXACTLY ONCE below; seven are ACCEPTED as corrections to the planner audit's boundary/design text (the audit relay stays immutable; the corrections bind the PLAN), two are DIFFERENT COVERAGE routed to owners through master.
Basis: planner audit `intg-substep2b/AUDIT-pair-planner-20260915-040846.md`; implementer audit `intg-substep2b/AUDIT-pair-implementer-20260915-041820.md`; master's Q1 ruling `intg-2b-wiring-act/PLAN-master-planner-20260915-041518.md` (both verbs); every evidence line below re-read by the planner at `186adf7d` before disposition.

| Finding | Agreement | Evidence checked (planner, this turn) | Disposition (exactly one) |
|---|---|---|---|
| I2B-01 A8 is still OWED inside the four consent renderers (clauses 1–5 composed, consent-local; callers pass RAW facts; generated Unicode 15.0.0 static table; machine carriers byte-exact for valid values) — not a `display()` question | agree (planner's (w7) hedged it to m-3's word; the sealed A8-R1 text owes it regardless) | A8-R1 lines 92–160 ("display-encoded INSIDE the renderer boundary… EXACT GENERATED STATIC TABLE… does NOT edit the shared `display()`"); `url_consent.cpp:13-38` at P concatenates raw strings; `envelope.cpp:63-85, 399-442` machine carriers via `value_string` | OWNED OBLIGATION → PLAN tranche A task "A8 consent-render policy": composed encoding inside the four renderers, the generated static table pinned to its two source files, a8·1–a8·4 unit legs, a8·5 arms A/B1/B2, machine carriers byte-exact; file list gains `src/cli/url_consent.{hpp,cpp}` + the table asset + the bounded carrier path; m-3 confirms the asset shape (Q3(a) REFRAMED: not "does display() discharge clause 5" — it cannot — but "the table asset's file/generator shape and the R-4.48 (ii)–(iv) witnesses"), m-4 at cell (v) |
| I2B-02 `--json` is not an absent-hook suppressor; the hook predicate is stdin TTY AND stderr TTY only; PROMPT B's `!json` is never copied into D | agree (the audit's "non-TTY / --json" phrase was wrong) | A7-R1/R2 lines 57–95; `main.cpp:277` (B's conjunction incl. `!parsed->json`) vs `url_consent.cpp:9-10` (D's predicate) | OWNED OBLIGATION → PLAN hook truth table (flag → always-proceed hook regardless of TTY; no flag + both TTYs → interactive hook; otherwise NO hook → engine refusal; `--json` absent from every row) + a7·1–a7·3 named-mutant controls; the `:277` dedup touches ONLY the two-isatty conjunction of B |
| I2B-03 accepted notice / refusal rows do NOT join the human summary (A6-R4: notice on the diagnostic stream at first proceed; summary SUPPRESS; per-entry lines + one guidance line on the diagnostic stream); the diagnostic reader must exist with ZERO sessions | agree (the audit's render.cpp target was wrong) | A6-R4 lines 502–548 (surface table: summary SUPPRESS, warning SUPPRESS); A6-R6; `main.cpp:372-385` (session summary only when sessions/skipped exist; `render.hpp` receives no OpenReport) | OWNED OBLIGATION → PLAN writer→reader boundary: consent surfaces are stderr-only writers in the CLI layer (notice at first proceed; per-entry lines in encounter order; guidance once, after the last line, before exit), emitted whether or not sessions exist; `src/core/open/render.cpp` LEAVES the write set; a6·11 (no summary line, no warnings row), a6·12, the TC-3 nonzero-sessions arm and a zero-session control; a B→D stdin handoff control (B reads `operator>>`, D `getline`). Consequence: Q4 to m-2 is WITHDRAWN as moot — no byte of the human summary changes |
| I2B-04 a7·3 topology = stdin TTY + stderr TTY + stdout NOT a TTY; stderr is captured from the PTY master, never replaced by a pipe | agree (the audit's "separate stderr pipe" would have tested a7·2) | FX-A7 a7·3 text lines 149–160; `test_cli.cpp:230-277` one slave dup2'd onto all three descriptors | OWNED OBLIGATION → PLAN helper task BEFORE a7·3: `run_cmd_pty_split` (stdin+stderr on the pty slave, stdout a pipe), recording all three child descriptor TTY states, with its must-be-YES / must-be-NO discriminator run and both a7·3 mutants (JSON-suppressor; three-stream predicate) |
| I2B-05 the adapter fence must name the real path `src/adapters/**` (no `src/core/adapters/` exists); `schemas/**` exists | agree | `git ls-tree -d` at P: `src/adapters src/cli src/core/{container,ignore,json,manifest,open,pack,repo,report,scan,support}` | OWNED OBLIGATION → PLAN ZERO-BYTES fence corrected to `src/adapters/**`, `harness/**`; schema bytes ONLY where a sealed shape requires them (see I2B-09); adapter-anchor applicability re-run against the declared file set at the plan face and against the candidate's diff stat |
| I2B-06 the shipped refusal fires on an UNPRUNED entry NAMED `.git` (dir or file form), after `.bivignore`/builtin pruning; "any depth" is bounded by pruning | agree (precision on the planner's (w5)) | `scan.cpp:129-138` (matcher.match + `continue` precede the name test) | OWNED OBLIGATION → PLAN tranche C states the shipped behavior exactly and witnesses: retained dir marker, file-style marker, pruned branch (not discovered — pack-engine §1.1's `.bivignore` rule), under m-1's word on the retirement |
| I2B-07 a product-command test against a hand-built image is E2 (executable local fixture), not E1; it proves bounded open behavior, never a pack→open round trip | agree (the audit's tier label was wrong; master's 041518 condition already binds the re-execution) | protocol evidence ladder; FX-A7 preamble ("E2 at the wiring sub-step") | OWNED OBLIGATION → PLAN claim-by-claim evidence matrix: open-side witnesses on hand-built images = E2 / provenance hand-built / interim; each RE-EXECUTED against a product-packed image after tranche C inside the candidate before the packet (master's condition); the round trip itself is its own row |
| I2B-08 the workflow cells count Catch2 CASES (`OverallResultsCases`), not legs or assertions; a leg inside an existing case moves no cell | agree | `s2-harness.yml:67-94`; R3 row Q2 (SECTION measurement precedent) | OWNED OBLIGATION → PLAN count gate = observed case tuples at the exact candidate sha on both platforms (macOS native; Linux parity container `--platform linux/amd64`, Ubuntu 24.04, `--init`, nofile raised), a companion count-cell commit ONLY if a tuple moved, the unchanged result reported otherwise; no remote CI |
| I2B-09 populated `repos[]` needs a REPORT-READER disposition: `envelope.cpp:111-149` emits a literal empty `manifest.repos` array for pack and open; the schema declares `result.manifest.repos` only as `{"type":"array"}` | different coverage (planner's boundary omitted `src/core/report/**`) | `envelope.cpp:105-150, 395-400`; `schemas/biv-json-envelope.v1.schema.json:194-197`; arm-1 design (LOCAL, s4 step-4) item 4 anticipated "the envelope schema gains the repo-row shape; the frozen open-envelope oracle RECAPTURED" | OVERLAP EDGE → Q7 to m-3 through master: the `result.manifest.repos` row shape at 2b (a sealed shape to execute, or KEEP the empty array with the population reported elsewhere), plus the envelope oracle recapture rule; the plan carries a `src/core/report/envelope.cpp` + schema task ONLY under that word, else the reader stays as landed and the gap is a registered residual, never silent |

Standing bar carried from the implementer's return (agreed): no direct git spawn in product code; exactly one carrier endpoint per new network path through `invoke_git`; refusal never laundered into a downgrade; whole-corpus + `--offline`-parity with E5 at wiring; same-sha owner reviews; census population FOR the merge head; the operator's merge token filed under `.relays/intg`; no release.
Plan artifact: NOT YET DRAFTED — freezes only after m-1's and m-3's pre-statements (with Q2, Q3-reframed, Q7) land; Q4 withdrawn; Q1/Q5/Q6 ruled 041518.

## R5 — sub-step 2b plan rev2 exact-hash review reconciliation (2026-09-15)

Verdict: the implementer's MUST-REVISE of rev2 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-140509.md`, MUST-2B-01..11) is ACCEPTED in full; every finding re-verified at the pin by the planner before disposition; rev3 of `plans/PL-intg-substep2b-20260915.md` folds all eleven, each exactly once.

| Finding | Evidence checked (planner) | Disposition in rev3 |
|---|---|---|
| MUST-2B-01 typed refusal mapping | `types.hpp:56-110`: wire string `url-divergence-refused`; typed accessor `engine_error_kind` | OWNED: Tasks 4 and 5 map through `engine_error_kind(err) == EngineErrorKind::url_divergence_refused`; pack control (kind UrlDivergenceRefused, exit 3) and open control (row + continue, exit 2) with the underscore-string mutant named |
| MUST-2B-02 stage path / offline rows | `restore.cpp:138-145` (`stage_root / <artifact relpath>` + containment); `restore.cpp:444-452` structural branches | OWNED: members staged at the FULL manifest-relative path; a real bundle + both patch classes restore witnessed; offline = three branches (shallow-pointer / payload-only-unborn identical with and without `--offline`; offline-pointer only for rows that would clone/fetch) |
| MUST-2B-03 machine carriers / renderer tests | A8 :195-220, :307-339 (valid byte-exact; malformed visibly replaced; no display escape); `writer.cpp:142-163` passes ≥0x20 raw | OWNED: `machine_text` (= `sanitize_utf8`) at every A8-census emission in envelope.cpp; a8·5 B1/B2 oracles restated (U+FFFD in JSON, never raw, never an escape); Task 2 tests assert whole-byte-golden renders and scan only the encoded slot |
| MUST-2B-04 contingent authority | plan rev2 text vs boundary "no-consumer action: STOP" | OWNED: RULE — HOLD before BYTES for undetermined cells (T-JSON, T-HELP, T-STAGE, T-FENCE, T-KIND); SEALED-as-cut/measured/recorded for T-NET, T-LIST, T-PROM; no vocabulary alternatives; an owner word changing a task ⇒ new hash-bound revision |
| MUST-2B-05 file lists / test boundaries / schema enum | plan rev2 Tasks 4/6 Files vs bodies; A9.3 (`error.kind` free string) | OWNED: Files and `git add` lists complete (url_consent, main.cpp, cli_run.hpp, test_wiring.cpp, test_url_consent.cpp); raw core contract vs rendered CLI contract tested at their boundaries; no envelope-schema enum invented — the exit-map row is the published contract |
| MUST-2B-06 runner proof / pipefail / census / greps | `plan_blocks.py` listing loop `"0123456789"`; rev2 proofs `gates=0`; B grep of the field regex = 26 unrelated hits | OWNED: listing enumerates present RUN tasks; prose gate spans bound (rev3 proofs: gates 3/13/4/2, omitted 0); `set -o pipefail` + `PIPEOK` + runner controls (Task 9 Step 0); `repoentry_census.py` type-scoped with mutant/control; network class compared by content; `invoke_git(`/spawn closure greps; C-2 hunk `cmp`; A8/predicate/hook censuses executed; fence-proofs file assembled |
| MUST-2B-07 stale H | rev2 Task 9 wrote H.txt before c9 | OWNED: H0 = suite object; `cellpatch.py` + c9 committed INSIDE the Task 9 runner; `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` EMPTY proven; H written LAST; reviews/GO/vehicle bind H |
| MUST-2B-08 harness bar / series | m-3 130818 §5 (both targets) §6 (population rule); 015244 (K-1/K-2/K-3) read at this seat | OWNED: `harness-e2` receipts on macOS (Task 9 Step 3) and inside the Linux container (Step 4); the equal-population branch applies the single-sample bar (r449 form); `series_verdict.py` implements 015244 exactly (validity → K-1 → K-2 → K-3), NOT-SHIFTED required, no deselection arm |
| MUST-2B-09 owner set / push destination | rev2 Task 10 predicates | OWNED: exactly one no-red review from EACH of m-1, m-3, m-4, three distinct pdc paths, per-relay object/scope/verdict/no-red-status checks; ONE push URL pinned to `https://github.com/iwnlcern/bivpak.git`; no process substitution |
| MUST-2B-10 census pin / population / finalize order | packet §8 (`9c9391d5…` full digest); instrument header (population file required); r449 finalize ordering | OWNED: the full digest literal; `census_population.sh` PRODUCES the population on H0 in the instrument's form (A/B/C by value digest; unclassifiable ⇒ STOP); H0 as tree AND history ref; the landing declaration for the merge head; classify → freeze → copy |
| MUST-2B-11 canonical cross-repo edge | relay-lint 2.9.3 `xroot_*` (per-file: not engaged; root mode: origin/review selection under DESIGN_SOURCE_ROOT); the pdc authority population emulated for M/A6/A7/A8/N/O/SR-URL/A9 | OWNED + UP: the rev3 PLAN carrier declares the edge (M rev8 at pdc `1e987860`, `DESIGN_SHA256 57d89625…`, owner m-1, root `master/relays`); the root-mode measurement launched 14:28:59 with the carrier in scope (result archived to `results/` and reported by SITREP); the planner's emulation predicts the AUTHORITY axis fires for every consumed design id (the latest DESIGN origin for each doc id under the root has no parented approve — the fence relays reuse the doc ids as PHASE DESIGN relays) — a structural fact about the authority population, reported UP for master's word, never removed to gain green |

## R6 — rev3 gate-limited MUST-REVISE (2026-09-15, `intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-152914.md`)

Verdict: ACCEPTED. The implementer graded rev3 (b6e837f2…) at master 034525's FIRST gate only ("the canonical cross-repo edge measured root-mode first") and stopped there: MUST-2B-11 is OPEN as a measured `authority-parent` failure (the field grammar is closed; the authority is not), and MUST-2B-01..10 are UNGRADED (no closure inferred from the rev3 face or the extractor proofs).

| Item | Planner disposition |
|---|---|
| MUST-2B-11 reframed | AGREE. The planner's root sweep (results/lint-root-sweep-s2b-plan-edge-20260915.txt) and the implementer's independent selector reproduction agree on the one fired line and its cause: the latest PHASE-DESIGN carrier of `m1-addendum-M-20260823` under `master/relays` at pdc `1e987860` is m-1's 2b fence `DESIGN-planner-20260915-042531.md`; zero DESIGN-REVIEW relays are parented to it. The declaration stays; nothing is removed, narrowed or relabelled. |
| The planner's "the review and the token do not wait on Q15" (144707, 144857, 151650) | WITHDRAWN. pair-planner protocol.md :591 — "A relay-lint error blocks delegated dispatch, merge, or automated adapter consumption unless the operator explicitly waives the structural error." The fired line is a relay-lint ERROR on the plan's own carrier class; the approve and the token therefore WAIT on an authorized disposition of Q15. The waiver, if that is the disposition, is the OPERATOR's explicit waiver (not a master ruling by analogy to the r449 lock-id class, which fired no declared-edge line). |
| Option (b) mechanics (implementer) | AGREE. A review filed now cannot appear inside immutable `1e987860`; the carrier must float `DESIGN_SOURCE_COMMIT` to a pdc commit that contains the parented approve (design byte pin unchanged — `DESIGN_SHA256 57d89625…`), on a new hash-bound PLAN carrier (`intg-substep2b-plan-4`; plan bytes may stay at b6e837f2… since the edge lives on the relay, not the plan), then re-measured root-mode and archived. The review must satisfy the declared owner m-1 and the origin's peer-role rule (`planner` → `implementer`/`pair-implementer`); a master-authored review is not automatically m-1's peer. |
| MUST-2B-01..10 | UNGRADED by 152914; the R5 dispositions stand as the planner's claims and await the resumed substantive review at the exact hash (or at a re-acknowledged revision if any planned byte changes). |
| Next hop | Q15 UP with the corrected framing (SITREP); no revision, no approve, no token until the authorized disposition lands. |

**R6 addendum (2026-09-15 16:41, master 164151):** Q15 RULED route (b) — the Domain Reviewer's (m-1.implementer's) parented approve of 042531 on its merits; no waiver; the 153727 correction accepted (approve and token wait). The pair holds at b6e837f2 until master names the pinned pdc sha; then plan-4 carrier + one re-sweep + archive; the implementer resumes MUST-2B-01..10 at the same hash. Standing rule registered (a PHASE DESIGN relay with DESIGN_DOC_ID is a design origin owing its peer review).

## R7 — Q15 resolved and m-1's fence rev2 folded (2026-09-16, master `intg-2b-wiring-act/PLAN-master-planner-20260916-051652.md`)

| Item | Planner disposition |
|---|---|
| Q15 (MUST-2B-11) | CLOSED on measurement. Master named the pinned pdc sha `631aae8298801245f6281ae012cd06498576e671` (m-1.implementer's binding approve `intg-2b-wiring-act-m1-fence-review-r2/DESIGN-REVIEW-implementer-20260916-044559.md` of fence rev2 `171041`). Verified at this seat with the linter's own function: `xroot_authority` PASS at 631aae82 (must-be-YES) and FIRES `authority-parent` at 1e987860 (must-be-NO); the M-doc population at the pin enumerated (69 carriers; latest DESIGN stamp 171041; parented approve 044559 unique-latest). The plan-4 carrier (`intg-substep2b/PLAN-pair-planner-20260916-054308.md`) floats DESIGN_SOURCE_COMMIT to that pin; the root sweep re-runs ONCE with the filed carrier in scope (no scout) and is archived beside the first. |
| m-1 fence rev2 (171041) — the fence of record | FOLDED into plan rev4 (`34c126f`, sha `3f0a051a…`): c1 → c1a (offline mode after the unborn/shallow return; born non-shallow lane only; R-4.1 arm (i) scoped) + c1b (`discover.cpp` `.biv` skip root-scoped via a depth parameter; nested `.biv` walked; `.git` dirs and symlinks unwalked; marker test unchanged); the runner's commit walk pins each of the first two commits to its exact path set; RCPT-P and E4+RCPT-O rows; W-O1..3 (snapshot-and-compare unit cases + product-scope manifest diff) and W-D1..3 (unit) / W-D1..4 (product); V-2b-5 rev2 as a runner gate (`git diff B HEAD -- scan.cpp` carries no `".biv"` line); T-PROM scoped. Per 044559: W-D3's provenance half is product-scope only; W-D4 is credited with V-2b-5 + byte review, never alone. |
| Q12 / T-HELP, T-KIND, T-LIST, T-JSON (offline fields) | Unchanged: bind to A9's LOCK id. Rev2 `40eaea22` passed its pair gate on the merits (044325) but does not bind under the linter (parent = commission grant); m-3's binding re-file is pending (051138/051139). A9 and A6 are NOT declared as edges on any pair carrier until their binding reviews land (master measured both firing at 631aae82). |
| Standing rule, second half (m-3's adoption, master concurs) | Bound: a PHASE DESIGN relay carries DESIGN_DOC_ID + DESIGN_RECORD_KIND ONLY when it is the design origin routed for review; receipts, rulings, answers and fence pre-statements cite by pin in prose and RELATED_CONTEXT. This seat files no PHASE DESIGN relays; the rule binds any future one. |
| Gate ledger FINAL (051652) | (i) IN; (ii) m-4 IN, m-1 IN at rev2, m-3 IN, m-2 not a touch; (iii) in-as-scoped. Next: the implementer's exact-hash review of rev4 (MUST-2B-01..10 re-presented; MUST-2B-11 closed) → the pair's token. |

## R8 — rev4 exact-hash review reconciliation (2026-09-16, `intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md`)

Verdict: the implementer's whole-plan MUST-REVISE of rev4 (`3f0a051a…`) is ACCEPTED in full; MUST-2B-01..03 and 05..11 graded CLOSED there (MUST-2B-11 on the implementer's own official-selector positive/negative reproduction at 631aae82 / 1e987860); the three open items are folded into rev5 (`138a322`, sha `5aabe373…`), filed as `intg-substep2b-plan-5` (`intg-substep2b/PLAN-pair-planner-20260916-070942.md`).

| Finding | Evidence checked (planner) | Disposition in rev5 |
|---|---|---|
| MUST-2B-04 (reopened) — T-STAGE | `open.cpp:544-611` at B: `apply_archive` extracts every non-`agents/` member via `apply_member`; rev4 added `repos/` as a third extracted branch with no offline routing | OWNED: `apply_archive` gains `const std::optional<std::filesystem::path>& stage`; online ⇒ `repos/` members extracted into `*stage/<full member path>`; offline ⇒ drained + checksum-verified like `agents/` members, never materialized; `execute_archive` computes `stage` as `nullopt` under `--offline` (or no repos) and touches the stage path only when it has a value. Discriminator: a regular FILE pre-created at the stage path — `open --offline` exits 0 and leaves it unchanged; the online control reports `OpenPartialPresent` naming it; the extract-regardless mutant reds. The owner word (Q13) changes exactly this routing in the revision that carries it. |
| MUST-2B-04 (reopened) — T-FENCE | rev4 Task 5 Step 3 wrote `InternalError` + `STOP-T-FENCE …` text — a product behavior and wording under a HOLD | OWNED: the branch and its wording REMOVED (grep count 0); Task 5 Step 0 is a hold-before-bytes gate — Task 5 does not start until `$RUNNERS/m1-fence-word.txt` holds m-1's disposition per class; the candidate HOLDS at c4; the fence branch is transcribed from the word in the revision that carries it. |
| MUST-2B-12 — root-repo exclusion | `scan.cpp:74-84` (`child_relpath`: the root is `""`), `walk(source_root, {}, …)` :228; `discover.cpp:88-91` reports the root boundary as `"."`; rev4's test used `{""}` while production would carry `"."` | OWNED: `ScanExclusions::canonical()` (lexically_normal generic string; `"."`/`""` → `""`; no trailing slash), `claims_root()`, `claims()` on canonical strings; a ROOT-CLAIMED FAST PATH in `scan()` returning an empty `ScanResult` before any read; pack canonicalizes each discover relpath; test (a) on the PRODUCTION value + the `{""}` twin + a nested arm, fast-path mutant named; Task 7's workspace-root leg (tracked + untracked + subdir ⇒ ZERO `payload/` members; the repo restored with its untracked penumbra) is the product discriminator. |
| MUST-2B-13 — task numbering / scope | Identity LANDING/CLOSURE said Task 10/11; the CEN row said Task 10; the bodies put the vehicle at 10, the rehearsal at 11, closure at 12 | OWNED: identity + CEN now name Task 12 (POST-merge, after the operator's token; Task 11 pre-merge rehearsal + declaration); Task 12 opens with an ORDER line and the landing census on the merge head with its population re-produced there; the `--offline` claims scoped to the born non-shallow lane in Task 5 Step 1 and the file-structure line. |
| Carrier disclosure | the plan-5 relay's runner-proof note still reads "(rev4: gates 3/13/4/2, omitted 0)" — the rev5 proofs are identical (3/13/4/2, omitted 0, rc=0 ×4) and the label is stale, not the numbers; the M edge fields on plan-5 are byte-identical to plan-4's (pinned 631aae82), so the single re-sweep master asked for (archived 2026-09-16) is not re-run for rev5 unless master asks | disclosed on the SITREP |

## R9 — rev5 approved; every owner cell ruled; plan rev6 (2026-09-16, master `intg-2b-wiring-act/PLAN-master-planner-20260916-080937.md`)

The implementer APPROVED rev5 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-072353.md`, HOLDs intact — the diff baseline). Master then carried every open owner word and directed rev6 before the token (an owner word that changes a task is a new hash-bound revision). Rev6 = `164cc48`, sha `114eabe6…`, filed as `intg-substep2b-plan-6` (`intg-substep2b/PLAN-pair-planner-20260916-082515.md`).

| Cell | Word (source, verified at the bytes) | Rev6 disposition |
|---|---|---|
| Q11 fences | m-1 074712 §1: whole-operation typed refusal per class; `unmerged` permanent (B §B1, F56); `dirty`/`nested`/`submodule` transitional Arm-1 boundaries (R-4.57) | T-FENCE RULED; Task 5 starts; c5 surfaces a fence through `make_engine_error` (InternalError + `repo_engine_kind`, no image); the refusal bytes are A11's at c6b |
| Q10 promisor | 074712 §2: pack-only whole-op, both arms; open unreachable | T-PROM RULED; `PromisorObjectsUnavailable` at c6b with `facts.offline` from the CLI flag |
| Q13 offline artifact | 074712 §2 (apply half) + A10 rev2 §A10.6 (UX half, 080306/080308): durable `<dest>/.biv/repos/<id>/repo.bundle` via the §2.1 staging; two URL-free reconstruct forms | T-STAGE HOLD→A10 (c4b); rev5's drain-only routing stands at c4a; overlay rows write nothing (R-4.58) |
| Q8 `--network` | m-3 075225 + A10 rev2 §A10.2: NOT inert; D3 executes at 2b | T-NET HOLD→A10 (c4b); the notice/prompt bytes quoted verbatim; PROMPT D untouched (V-A10-3) |
| Q9 rows | A10 rev2 §A10.1 | T-JSON HOLD→A10 (c4b); schema in the same commit |
| The gap | A11 rev1 (080307): nine wire kinds; whole-op grain; A11.2/A11.3 | T-A11 HOLD→A11 (c6b); ErrKind 27→36, exit map 29→38 |
| Order | 080937: token prefix c1a c1b c2 c3 c4a c5; c6a/c4b/c6b in lock order; c7–c9 after all three | topology + identity TOKEN line |
| ARM-1 consequence (planner's reading, surfaced UP in SITREP 082516/082602) | `classify.cpp:347-357` fences ANY porcelain-v2 output — an untracked file is the dirty fence; `capture.cpp` writes bundles only | every packed fixture clean with `.gitignore`d penumbra; MUST-2B-02 leg corrected (real bundle + local-refs); W-D1 product form = the nested-fence refusal; T-ARM registrations (patch round trip; two-row images; leaves-first / parents-before-children at product scope; submodules); the hand-built ordering witness kept and labelled |
| Carrier note | SITREP 082516's title lost two backtick spans to an unquoted heredoc | corrected by SITREP 082602; drafts are written by python from now on |

## R10 — rev6 exact-hash review reconciliation (2026-09-16, `intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-085404.md`)

Verdict: MUST-REVISE on four executable contradictions; one is the planner's and is folded into the working rev7 (`19460b2`, sha `48a59462…`, NOT filed until the routed words settle — the implementer's ask); three are A10/A11 owner cells routed UP (SITREP `intg-substep2b/SITREP-pair-planner-20260916-090252.md`).

| Finding | Evidence checked | Disposition |
|---|---|---|
| MUST-2B-14 c3 not unconditional | rev6 identity/ORDER put c3 in the unconditional prefix while T-HELP + Task 3 Step 0 held its commit on A9 | OWNED, FIXED (rev7): c3 (unconditional; no help byte, golden untouched) + c3h (A9 lock: the two help lines + the golden re-pin; lands after c5 in lock order, before c6a); identity, ORDER RULE, topology, T-HELP, Task 3 now one topology; "a working-tree partial is not a history prefix" written into the ORDER RULE |
| MUST-2B-15 A8 encoding ≠ shell quoting | the implementer's git controls (refs with `"`, `$()`, backticks, `$`; a newline path); rev6 quoted A10 rev2's double-quoted forms | ROUTED (A10, m-3): A10 rev4 §A10.6 (718fd6ec, 08:57) cuts POSIX sh, single-quoted raw operands, the copy-safe predicate and the fallback line — closes at A10's review; rev7's A10-REV term records the drift; c4b re-planned from the reviewed pin at the next filed revision |
| MUST-2B-16 unborn full row has no form | the implementer's discriminator (in-place `git checkout main` exits 1 on an unborn branch; clone maps side refs to `refs/remotes/origin/*`); A10 rev4 gives only branch/detached endings | ROUTED (A10, m-3): an unborn form or the fallback line for the G row, with empty/absent and non-empty witnesses; rev7 ROUTED term holds the c4b bytes |
| MUST-2B-17 A11's failed row is lost | `open.hpp:79` `expected<OpenReport> execute_open`; `main.cpp:353-356` `emit_error(report.error())`; `envelope.cpp:541-543` `result` null iff `error` | ROUTED (A10 + A11 composition, m-3 with m-1's seam): the typed report+error carrier, layer ownership, signatures, the envelope call and a discriminator; until then c6b keeps the failed row in memory and the error as today, no envelope byte for rows-with-error; the pair does not stringify rows into facts |
| Surfaced with the review | A10 rev4 §A10.2: the D3 trigger is an ENGINE-exposed per-row fact (S-A10-1); m-3 085709 asks master to route INVOKES-GIT / ARTIFACT-PRESENT to m-1 | UP: if the exposure needs an engine byte it is a third engine diff V-2b-1 rev2 does not authorize — master's word; rev6's manifest-derivation sentence WITHDRAWN (rev7); T-NET HOLDS on it. 085709 (b): m-3.implementer's engine-client E-VERSION-MISMATCH → the operator's |

## R11 — master's status carry 135421 folded into the working rev7 (2026-09-16; NOT filed — the hold stands)

| Item | Source (verified at the bytes) | Working rev7 (`a1b4417`, sha `356747b2…`) |
|---|---|---|
| Third engine commit c1c | m-1 fence rev3 `131522` §1 (binding approve asked 135409); `restore.hpp:39-42` / `restore.cpp:443-452` at the pin | Task 1 Steps 11–15: `restore_invokes_git` exported (+2/-0) and used by `restore_entry`'s guard; W-G1..3; the runner walks THREE engine commits at exact path sets and checks restore.hpp's numstat `2 0`; token prefix `c1a c1b c1c c2 c3 c4a c5`; written only after the approve + master's sha (gate `$RUNNERS/m1-fence-rev3.txt`) |
| The exact `--offline` / DECLINED partition | fence rev3 §2 (corrects 074712 §2's "never called"); A10 rev6 `17fda846` §A10.2 verbatim | Task 4: predicate FALSE ⇒ CALL `restore_entry` (zero git by construction — shallow-pointer per N-R4, payload-only-unborn per H); TRUE ⇒ offline-pointer row; D3 trigger = ∃ row with the predicate TRUE, READ; ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership |
| MUST-2B-16 | A10 rev5 §A10.6 (approved binding 132531; rev6 byte-identical there): one `git init` idiom per stored HEAD state — born on `bvpk-restore` with `--update-head-ok`; unborn on `--initial-branch='<branch>'` with NO checkout; detached; `git clone` printed for no row | CLOSED with a form; the A10-REV term quotes the three idioms; binds at A10's lock |
| MUST-2B-17 | master's ruling (b) via 135413; A11 rev5 `33c69913` OPEN INVARIANT (m-3 140044/140045) | CLOSED: the result-null-iff-error invariant KEPT; the orchestrator writes `<target>.bvpk-open.partial/inventory.json` (rows, the failing row with kind + detail, the outcome, §2.2 order); `facts.partial_path` + `facts.repo_id`; no `result.repos` on failure; `execute_open`'s signature untouched (a fourth engine diff no fence authorizes); c6b's leg (h) rewritten; leg (m) the three carriers (A11 rev4) |
| m-3 fence origin | `134813` approved binding 135230 (130818 history; §4 retired → A9.4 / A10.6) | the owner-fences line reads 134813 for the CLI half |
| The M edge | fence rev3 is the new unique-latest origin — the declared edge fires until its approve; master names the sha then | identity ENGINE FENCE line; the plan-7 carrier re-pins once more; one root sweep after filing |

## R12 — plan rev7 FILED on master's 010159 (2026-09-17 01:22; `intg-substep2b/PLAN-pair-planner-20260917-012204.md`, `intg-substep2b-plan-7`)

| Item | Evidence checked | Rev7 (`a603108`, sha `03819d1f…`) |
|---|---|---|
| The M edge | pin `a1ce40a9` = m-1.planner's route of the approve; `…-m1-fence-review-r4/DESIGN-REVIEW-implementer-20260916-171135.md` present at the pin; 73 M-doc carriers, latest DESIGN origin 161701, unique-latest parented approve 171135; `xroot_authority` PASS at a1ce40a9 (must-be-YES) and FIRES `ordering` at 4636fcef / 74810810 (must-be-NO); the M blob 57d89625 at the pin | `DESIGN_SOURCE_COMMIT: a1ce40a9…` on the carrier; one root sweep started 01:22:04 with the filed carrier in scope |
| MUST-2B-14 | 085404 | c3 / c3h split; ONE topology |
| fence rev4 (c1c) | 161701 §1–§2; 171135; erratum 171446 (27 returns — re-run here: 27) | c1c RELEASED (gate file `$RUNNERS/m1-fence-rev4.txt` = approve path + pin + fence sha `cf3190ab…`); the git-capable wording; W-G1/G1c/G1n/G2/G3; the count rule (the grep at the candidate head) |
| A9 | sealed (170242; 165214) | c3h / c6a released terms; the VP boundaries transcribed |
| A10 rev6 / A11 rev5 | 17fda846 / 33c69913 unchanged at HEAD | contingent on their locks; MUST-2B-15/16/17 closed by owners; the failure inventory distinct from §2.3's quarantine inventory; `execute_open` untouched |
| Order | 010159 | c1a c1b c1c c2 c3 c4a c5 → c3h c6a → c4b c6b (lock order) → c7 c8 c9 |

## R13 — rev7 exact-hash review reconciliation + rev8 FILED (2026-09-17/18; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260917-025941.md`; relay `intg-substep2b/PLAN-pair-planner-20260918-140706.md`, `intg-substep2b-plan-8`)

| Finding | Reviewer's claim | Checked at | Verdict | Rev8 (`7bc661f`, sha `baf70d5d…`) |
|---|---|---|---|---|
| MUST-2B-18 | c3's steps still carried help-line / golden bytes double-assigned with c3h | rev7 Task 3 Steps 1–5 vs Steps 6–8 | agree | c3 carries NO help/golden byte: Step 1(ii) = unchanged-golden control; Step 3 `help_text` UNTOUCHED; the c3 commit block greps the `args.cpp` + `test_cli.cpp` diff for help/golden hunks and STOPs on any; c3h alone carries both |
| MUST-2B-19 | T-STAGE / Task 4 carried A10's superseded double-quoted two-form reconstruct text, not rev6's | A10 rev6 §A10.6 + §A10.4 (j)–(m) at `17fda846` | agree | one single-quoted POSIX-sh idiom per stored HEAD state (born / unborn / detached), `git clone` for no row, copy-safe predicate + fallback line, legs (j)(k)(l)(m) verbatim; MUST-2B-15/16 now closed IN the plan |
| MUST-2B-20 | lock baselines named stale revisions | RULE; Task 4 Step 0; Task 6b title + Step 0 | agree | baselined on A10 rev6 `17fda846` / A11 rev5 `33c69913` / A9 rev2 LOCKED; a differing locked byte = a new hash-bound revision |
| MUST-2B-21 | the plan named `<target>.bvpk-open.partial` while A11 rev5 + 010159 name `<target>.bvpk-partial`; STEP4 DR-2 records the collision | A11 rev5 line 82; `open.cpp:637` at B; DR-2 line 52 | agree — an owner decision, not the pair's | HOLD term T-PARTIAL keyed on `partial_suffix=` in A11's lock file; no c6b byte names a suffix; ROUTED to master → m-1 / m-3 by SITREP `intg-substep2b/SITREP-pair-planner-20260918-141053.md` with both options pre-wired ((A) A11 adopts the landed spelling per DR-2; (B) `open.cpp:637` changes under c6b as an m-1-authorized byte → rev9) |
| The M edge | — | `a1ce40a9` byte-identical to plan-7's | unchanged | not re-swept for rev8 (the 2026-09-17 sweep fired nothing on the rev7 carrier); disclosed in the relay |
| Runner proofs | — | Task 0 / 1 / 4 / 6b extracts | 3/13/4/2, rc=0 ×4 | unchanged |

## R14 — rev8 exact-hash review reconciliation, rev9 fold, m-1's MUST-2B-21 ruling, rev10 (2026-09-18; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-153551.md`; ruling `intg-2b-wiring-act/DESIGN-planner-20260918-162306.md`; relays `intg-substep2b/PLAN-pair-planner-20260918-162803.md` (plan-9, withdrawn) and `intg-substep2b/PLAN-pair-planner-20260918-162953.md` (plan-10))

| Finding | Reviewer's claim | Checked at | Verdict | Rev9 (`e83dea8`, sha `ff24233b…`) → rev10 (`8eb33bd`, sha `ce5e9df7…`) |
|---|---|---|---|---|
| MUST-2B-22 | the c3 split proof grepped the UNSTAGED diff with a pattern the golden rows never match; no cached check on `test_cli.cpp`; no producer status; two orphaned topology lines under c3h | `tests/test_cli.cpp:1455-1469` at B (the golden is usage/option bytes only); plan lines 823-826, 124-125 | agree | the gate grades `git diff --cached -U0` with three discriminators (funcname `help_text(`; funcname the golden `TEST_CASE`; usage/help-row literal), each validated must-be-YES/must-be-NO on synthetic diffs in the same block; `git add` + diff producer rc-checked; counts recorded. EXECUTED by the pair in a throwaway worktree at B: missing c3 file ⇒ STOP; clean ⇒ pass; staged help row ⇒ STOP; staged golden row ⇒ STOP; parse-only + EOF test ⇒ pass. Orphaned lines removed |
| MUST-2B-23 | `RepoOutcomeRow` lacked `reconstruct`; Task 7 re-executed (a)–(j) "two forms"; c4b commit text said `clone \| in-place forms` | plan lines 844, 887, 1018; E1-A10 row 189 | agree | `reconstruct` declared with its presence rule; commit text = one idiom per stored HEAD state; Task 7 + E1-A10 = (a)–(m) with the (j)–(m) discriminators |
| MUST-2B-24 | the ROUTED paragraph still named `.bvpk-open.partial`; Task 6b Step 0 never required `partial_suffix=`; the SITREP over-claimed the gate | plan lines 359, 965 | agree (the SITREP 141053 claim was ahead of the bytes — mine) | ROUTED writes `<partial_dir>/inventory.json`; Step 0 fails closed on `partial_suffix=` + `partial_suffix_relay=`; one-site consumption with two open.cpp grep gates; leg (h) reads the suffix from the lock file |
| MUST-2B-21 RULED | m-1 162306: (A) `.bvpk-open.partial` (landed, verb-scoped; pack's FILE is `.bvpk.partial`, R-4.61 — two objects sharing a stem must not share a suffix); (B) rejected; open.cpp:637 untouched by 2b; DR-2 executed on restore-apply §2.1 status-only (9/0) | open.cpp:637, pack.cpp:550 at B; restore-apply §2.1/§3; RENAME :33; DR-2 :52-56 | taken | rev10: T-PARTIAL narrowed to (A); Step 0 admits exactly `.bvpk-open.partial`; (B) text removed; release still = the lock-file fields (m-3's act) |
| Process miss | — | plan-9 submitted 16:28; 162306 landed 16:23 in the listed directory, unopened | mine | plan-9 withdrawn unreviewed; listing and submit now separate commands; disclosed in SITREP 163112 |

## R15 — rev10 exact-hash review reconciliation, rev11 (2026-09-18; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-164316.md`; relay `intg-substep2b/PLAN-pair-planner-20260918-164800.md`, plan-11)

| Finding | Reviewer's claim | Checked at | Verdict | Rev11 (`42b2660`, sha `30278d51…`) |
|---|---|---|---|---|
| MUST-2B-25 | Task 6b Step 0 said "the block below STOPs" but no block existed; `partial_suffix_relay` only had to name an existing file, so any pdc path satisfied it; the Files prose still said the suffix was routed | plan lines 1002, 1004, 1009-1031 (only the sentence fence and the commit fence in Task 6b) | agree — my SITREP 141053 and rev9/10 prose were ahead of the bytes | an executable bash block run `MODE=pre` (before Step 1) and `MODE=post` (before Step 5): exactly-one-field parsing; `lock_id` fixed; A11 re-hashed at its pdc path; both relay paths pdc-relative, `..`-free, beneath `master/relays` by real dir; the owner word bound by BYTES — arm 1 the 162306 ruling (sha256 `82e37092…`, FROM/TO/PHASE/AUTHORITY lines, the RULED (A) sentence), arm 2 A11's lock relay from an m-3 seat carrying the spelling and the doc sha; any other path STOPs; one-site counts with producer rc apart; receipts compared pre/post. Executed at B against a synthetic lock file: pre + post pass (site 637, counts 1/1); seven controls STOP with distinct reasons. Step 5 refuses without a newer `mode=post` receipt. Files prose = the ruled state |
| Master 163608 (to m-3) | A11's lock file to carry `partial_suffix=.bvpk-open.partial` + `partial_suffix_relay=` naming 162306 | read before the plan-11 submit | consistent | = the gate's arm 1; no byte needed |

## R16 — rev11 exact-hash review reconciliation, rev12 (2026-09-18; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-165800.md`; relay `intg-substep2b/PLAN-pair-planner-20260918-170622.md`, plan-12)

| Finding | Reviewer's claim | Checked at | Verdict | Rev12 (`4ffd8cf`, sha `f65000bf…`) |
|---|---|---|---|---|
| MUST-2B-26 | `relay` was resolved as `R1` and never read; the reviewer's synthetic lock file with `relay` = master 010159 + the true ruling passed pre and post; arm 2 accepted any m-3 text containing two strings | the rev11 block (sole `R1` use = its assignment); the reviewer's execution witness | agree — the reviewer ran the bypass I had not | three carriers bound, none by existence: the A11 LOCK carrier (m-3.planner DESIGN relay: exact FROM/TO/PHASE/AUTHORITY lines, the lock id as a whole word, the doc sha, the A11 document cited), a new SEAL carrier `seal_relay` (master PLAN TO the pair, `IN_REPLY_TO` exactly the lock relay, same id + sha, SEALED, ≠ `relay`), the suffix word (arm 1 by sha256; arm 2 on the bound lock carrier); every relay path tracked + unmodified in pdc. Must-be-YES = the REAL A9 ceremony (165214 → 170242, `ae272647…`) via the block plus two constant substitutions: pre + post pass. Nine controls STOP with distinct reasons, the reviewer's bypass first (`lock-from`, no receipt). Block byte-equal to the executed one |
| Lesson | — | — | mine | a NO control must mutate EACH independent input the gate consumes; I mutated the field I had just added and left the older one untested — and a gate for a ceremony that has not happened yet is validated on the last ceremony that did |

## R17 — rev12 APPROVED; the delegated dispatch issued (2026-09-18; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-172324.md`, `intg-substep2b-plan-review-10`; token `intg-substep2b/IMPL-pair-planner-20260918-184804.md`, `intg-substep2b-impl-1`; SITREP `intg-substep2b/SITREP-pair-planner-20260918-184913.md`)

| Item | Evidence checked at issuance | Disposition |
|---|---|---|
| The approve | 172324: STATUS approve + PLAN_REVIEW_VERDICT approve at exact `f65000bf…`; the reviewer replayed the Task 6b gate on the A9 ceremony (pass ×2) and the nine controls independently; MUST-2B-22..26 closed | consumed as the token's PARENT |
| The artifact | live plan == `git show 4ffd8cf:<plan>` == `f65000bf…` (re-hashed) | the digest on the token |
| Lineage | token PARENT `intg-substep2b-plan-review-10` (FROM intg.pair-implementer) → its PARENT `intg-substep2b-plan-12` (my PLAN 170622, TO the implementer); walked with the 2.9.3 linter in root mode on a three-relay mini-root: clean; a wrong PARENT fires three errors (must-be-NO) | condition (4) |
| SCOPE_DIFF | 37 paths = the union of Tasks 0–9's Files + the c1c pair + the two schema paths; all-in; a SCOPE_ROW_EVIDENCE row per path naming its task and whether this token EXPECTS the edit or the path HOLDS at a gate file | condition (3) |
| Gate files carried | `m3-addendum-9-lock.txt` (id, post-stamp `ae272647…` live, pin `40eaea22…` @ c2f7a6c7 — both re-hashed), `m1-fence-rev4.txt` (approve 171135, pin a1ce40a9, fence sha `cf3190ab…` at 74810810 — re-hashed), `m3-help-order.txt` (§A9.4 HELP lines 150–158 verbatim + the eleven-line golden) | c3h / c6a released in lock order |
| Holds | c4b at `m3-addendum-10-lock.txt`; c6b at `m3-addendum-11-lock.txt` with `seal_relay=` + the two T-PARTIAL fields; c7–c9 after all four | the SITREP names the A11 seal shape master's relay must have (170242's) |
| Lint | per-file 2.9.2 / 2.9.3 OK on the token (the `DELEGATED_DISPATCH_AUTHORITY: yes` field engages the SCOPE_DIFF checks; `DESIGN_SHA256` replaced by `LOCKED_DESIGN_SHA256` on an IMPL carrier — the plan-relay edge form does not resolve on an IMPL relay); the mini-root shows only the inherited rule-3 line (fires on every relay in this root) | no new red class |

## R18 — the c4a STOP reconciled; rev13 (2026-09-19; STOP `intg-substep2b/IMPL-pair-implementer-20260919-021304.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-025144.md`, plan-13; SITREP `intg-substep2b/SITREP-pair-planner-20260919-025257.md`)

| Item | Implementer's claim | Checked at | Verdict | Rev13 (`36b6b7d`, sha `16722d72…`) |
|---|---|---|---|---|
| The STOP | c4a's nine-path candidate is focused-GREEN; the full suite fails ONE case, `tests/test_open.cpp:343`, which sha-pins two `open.cpp` slices sealed c4a must change; Task 4 authorizes nine paths; Step 4 demands the whole floor | the case at B (origin 2537eb6, s3 Task 4); the candidate read-only at 13ec732+9 (`return OpenReport{` gone) | agree — the plan carried the contradiction (a freeze over bytes it rewrites + a nine-path set + the whole floor); the shape-6 lesson (grep tests for the source PATH) was not applied when locking | `tests/test_open.cpp` = c4a's tenth path; a ten-path write-set gate before `git add` (executed: 10 pass / 9 STOP / 11 STOP) |
| The oracle | re-pin bounded regions or replace the sha pins with behavioural assertions, keeping the three controls | the case's name (occupancy, destination boundedness, staging atomicity); m-1 restore-apply §2.1 | replaced, not re-pinned: a sha recomputed in the commit that moves the bytes grades nothing, and c4b/c6b would recompute it twice more | Step 3b: sha pins deleted; the two `symlink_status` finds + `plan_open`'s three controls verbatim (same anchors); a write slice `const auto partial_dir =` → the function's column-0 `}` asserting occupancy, `OpenPartialPresent`, `create_directories`, `fsync_tree`, `rename`, no `absolute`/`weakly_canonical`, the suffix once; five named mutants; verified read-only on the candidate (every assertion holds) |
| The fixture | the temp-HOME insteadOf refusal fixture cannot fire (restore sets `GIT_CONFIG_GLOBAL=/dev/null`); a request-trace shim substituted | the plan's Step 1; the engine isolation byte | affirmed | Step 1 names the shim (answers only `remote get-url`, forwards the rest, records argv); product-scope form = Task 7 M (h) |
| Census | — | `git grep '"src"' -- tests` at B | the suite's only sha pin over product source; test_cli :1382/:1605 are order checks c3 passed | recorded in Step 3b |
| Token | — | — | `intg-substep2b-impl-1` consumed through c3; a fresh token after the approve | the plan-13 relay says so |
| Disclosure | — | — | the pair re-oracled an s3-era test over m-3's open surface; routed for objection via master (SITREP 025257) | rev14 would carry a kept freeze if an owner wants it |

## R19 — rev13 exact-hash review reconciliation, rev14 + T-ORACLE (2026-09-19; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-032618.md`; master `intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-033109.md`, plan-14)

| Finding | Reviewer's claim | Checked at | Verdict | Rev14 (`4ac2574`, sha `1804f2b4…`) |
|---|---|---|---|---|
| MUST-2B-27 | deleting the two pins leaves `sha256_hex` (test_open.cpp:54-58) uncalled under `-Werror`; the one-hunk rule forbade the cleanup | the candidate's helper and its two callers; the compile flags | agree | the helper deleted in a second hunk; `grep -c '^@@'` == 2; every other case byte-identical; no fake call, no re-pin |
| MUST-2B-28 | presence-only checks miss a writer retargeted to `dest` and an order inversion | the candidate's six-call sequence (positions 113 < 1125 < 2072 < 2871 < 3018 < 3273, each once) | agree | six exact forms REQUIREd once each and CHECKed strictly increasing; four new mutants (two retargets, rename-before-fsync, occupancy-after-create); a later form change updates the spelling in that commit, the order is the contract |
| MUST-2B-29 | `git diff --name-only` omits staged and untracked paths | the gate | agree | `git diff HEAD --name-only` + `git ls-files --others --exclude-standard` empty, producers rc-checked; executed in a throwaway worktree: ten with a staged subset pass; an extra staged path, an extra untracked path and nine each STOP |
| MUST-2B-30 | the census text was not the named command's output | `git grep -n '"src"' 186adf7d -- tests` (nine lines) | agree | the full nine-line output + two targeted producer-checked searches; conclusion unchanged (one sha pin over product source; one `open.cpp` reader) |
| T-ORACLE (master 032924) | the objection window to m-3 / m-1 on the re-oracle; master recommends no objection; silence is not consent | read before the plan-14 submit | taken | c4a's commit waits on the approve AND both owner words, carried by the pair Planner in `$RUNNERS/t-oracle.txt`; the Step 5 block refuses without it (executed: absent / keep-the-freeze STOP, no-objection pass); Steps 1–4 proceed under the next token, no commit |

## R20 — rev14 exact-hash review reconciliation, the owner words, rev15 (2026-09-19; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-034009.md`; owner words m-3 `intg-2b-wiring-act/DESIGN-planner-20260919-033307.md`, m-1 `intg-2b-wiring-act/DESIGN-planner-20260919-033215.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-034752.md`, plan-15; SITREP `intg-substep2b/SITREP-pair-planner-20260919-034859.md`)

| Finding | Reviewer's claim | Checked at | Verdict | Rev15 (`d57d927`, sha `cc087667…`) |
|---|---|---|---|---|
| MUST-2B-31 | master 032924 is `TO: m-3.planner`; m-1 only in CC; no addressed request can require m-1's word | 032924's header; m-1's 033215 (FROM m-1.planner, TO master, IN_REPLY_TO 032924, NO OBJECTION, in its own voice; names the gate fields itself) | agree on the routing; the word exists regardless | the gate binds master's CARRY TO the pair as the addressed act that adopts both words; the SITREP asks master for the TO-m-1 form as well; both owner words read verbatim from their files |
| MUST-2B-32 | the regex gate authenticated a caller-written line — three fabricated inputs passed | the rev14 block | agree — a fail-open commit authorization, mine | an executable evidence gate over four pdc carriers: the window pinned by sha256; each owner word by exact FROM/TO/PHASE/AUTHORITY lines, `IN_REPLY_TO:` the window, the case path, the window id, a SUBJECT saying NO OBJECTION and not objecting; the carry by exact header lines, both owner paths, `T-ORACLE`, the live plan's sha256 (re-hashed from the primary checkout), no keep-the-freeze; every path `..`-free, non-symlink, beneath `master/relays`, tracked + unmodified; `t-oracle.txt` holds locators only. Executed in a scratch clone of pdc + a throwaway worktree: the real words + a synthetic carry pass (four digests recorded); twelve controls STOP with distinct reasons (nonexistent, `..`, symlink, swapped owners, missing owner, unrelated m-3 relay 033306, carry naming another plan, plan sha ≠ live, modified carrier, untracked carrier, owner keeps the freeze, carry keeps the freeze, carry not naming m-1). A first draft required the literal `T-ORACLE` in the owner words — m-3's says `032924` instead — caught by the YES run, fixed to the window id |
| The words | m-3 (a)–(f): same commit, controls verbatim, contract-named assertions with the ruled suffix, no new source-hash pin over src/core/open at c4a/c4b/c6b, red mutants, objects to KEEPING the freeze; m-1: behavioural halves witnessed at the candidate head (Task 7), the owners' byte reviews discharge the freeze's residual function | both relays whole | every condition already in the plan's shape | no plan byte for them beyond the term's citation |
| A11 rev6 | m-3 033306: three sites respelled; lock-file binding stated; otherwise byte-identical to rev5 | the relay | noted | Task 6b's baseline stays rev5 with the respelling carve-out; m-3.implementer reviews rev6 |

## R21 — rev15 exact-hash review reconciliation, rev16 (2026-09-19; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-040334.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-042044.md`, plan-16; SITREP `intg-substep2b/SITREP-pair-planner-20260919-042044`-adjacent, the correction)

| Finding | Reviewer's claim | Checked at | Verdict | Rev16 (`fc22ef5`, sha `7f538d82…`) |
|---|---|---|---|---|
| MUST-2B-31 (open) | a later carry cannot retroactively address m-1; TO acts, CC informs; my SITREP had called the TO-m-1 form optional | the relay contract; 032924's TO line | agree — my 034859 was wrong to call it optional | the gate binds master's request `TO: m-1.planner` and m-1's reply in that lineage; the CC-answered 033215 is refused on lineage; the approve waits on the exchange existing; the correction SITREP asks master as a requirement |
| MUST-2B-33 | owner digests were recorded after acceptance; a committed textual-predicate-preserving mutation passes | the rev15 block | agree | the window and m-3's word pinned by sha256 as plan constants; m-1's reply and the request pinned by digests the carry affirms and the gate re-hashes; control: m-3 committed-but-changed ⇒ `m3-bytes` |
| MUST-2B-34 | the carry only rejected the literal `keep the freeze`; a `NOT CLEARED; do not commit` carrier passed | the rev15 predicate | agree | exactly one `T_ORACLE_VERDICT:` line, value `cleared`; NOT CLEARED / blocked / objection-without-the-phrase / absent / duplicate each STOP |
| Execution | — | scratch clone of pdc + throwaway worktree | — | the real pinned m-3 word + a synthetic addressed exchange + carry pass (six digests); nineteen controls STOP on their own predicates (a wrong `git revert` flag in the first control run left m-3 changed for eight controls — re-run in a fresh clone, each firing on its own predicate) |

## R22 — rev16 review: HOLD on the absent m-1 exchange (2026-09-19 13:06; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-130657.md`)

| Item | Reviewer's finding | Checked at | Verdict | Disposition |
|---|---|---|---|---|
| Design | MUST-2B-31/33/34 closed at plan level; 27–30/32 closed; no further redesign | rev16 at fc22ef5 | — | the plan stays byte-identical; plan-16 042044 remains the carrier of record |
| MUST-2B-35 | at pdc HEAD 2bbaf68f no relay is FROM master + TO m-1.planner + the case + T-ORACLE; no m-1 reply in that lineage; no carry can name the pair | the wiring-act directory (newest 033307) | agree — the prerequisite is master's act | the hold SITREP asks master again (032924's own rule); the implementer re-grades plan-16 as filed once the exchange exists, or a rev17 if the word changes a task |

## R23 — the addressed m-1 exchange exists; rev16 re-carried (2026-09-19 15:55; master `intg-2b-wiring-act/PLAN-master-planner-20260919-155534.md`; request `…/PLAN-master-planner-20260919-131720.md`; reply `…/DESIGN-planner-20260919-155106.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-<plan-17>.md`)

| Object | Checked at | Result |
|---|---|---|
| request 131720 | headers FROM master / TO m-1.planner / PLAN / plan-only; names the window path, the case (×3) and T-ORACLE (×2); tracked, unmodified; sha256 `6e5b3023…` | the addressed request the gate binds |
| reply 155106 | FROM m-1.planner / TO master / DESIGN / design-only; IN_REPLY_TO exactly the request; names the case; SUBJECT NO OBJECTION; sha256 `e706797e…` | the governed m-1 word |
| the gate on the real objects | scratch clone + throwaway worktree; real request + reply + pinned m-3; a synthetic carry naming `7f538d82…` | `t-oracle OK`, six digests; 033215 as the reply ⇒ `m1-lineage` STOP |
| the artifact | live == blob at fc22ef5 == `7f538d82…` | byte-identical; plan-17 is a re-carry, not a revision |

## R24 — rev16 APPROVED at the exact hash; token impl-2 issued; the word for the carry; the runner-lock gap (2026-09-19 16:13–16:28; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-161307.md`; token `intg-substep2b/IMPL-pair-planner-20260919-162507.md`; SITREP `intg-substep2b/SITREP-pair-planner-20260919-162750.md`)

| Object | Checked at | Result |
|---|---|---|
| the approve 161307 | `intg-substep2b-plan-review-15`, PARENT `intg-substep2b-plan-17`; STATUS approve + PLAN_REVIEW_VERDICT approve at `7f538d82…`; lint OK 2.9.2/2.9.3; its own gate run: real objects pass, 033215-as-reply STOPs `m1-lineage` | MUST-2B-35 closed by the reviewer on the real lineage; no plan byte requested |
| the delegated conditions | grant 144459; approve at the digest (live == fc22ef5 blob, re-hashed); SCOPE_DIFF 37 paths all-in (every rev16 path name outside the list is a fence or a mention); lineage token → review-15 → plan-17 walked on a three-relay mini-root (only the mini-root artifact classes fire; a wrong-PARENT control fires the lineage error); M edge a1ce40a9 unchanged; A9 SEALED, gate files re-hashed on disk (`1372ab46…`, `69208d32…`, `b6cd498f…`); A10/A11 unlocked | token `intg-substep2b-impl-2` issued (a07c269): resume at c4a Step 3b on the retained candidate; c4a's commit HOLDS at `$RUNNERS/t-oracle.txt`; c5, c3h/c6a in lock order; c4b/c6b/c7/c8 HOLD |
| the word to master | SITREP 162750 TO master: the digest `7f538d82…`; the five carry lines COMPUTED from the objects (033307 `20c9f24d…`, 155106 `e706797e…`, 131720 `6e5b3023…`) and EXECUTED through the plan's gate in scratch clones (pass; `TO: intg.pair-planner, intg.pair-implementer` ⇒ `carry-to` STOP) | master's carry must carry the TO line exactly `TO: intg.pair-planner` |
| the runner-lock gap | `run-task.sh` re-hashes the plan against `$RUNNERS/plan-lock.txt` (= the rev12 digest `f65000bf…`, bound at Task 0); rev13–rev16 moved the digest; no plan step re-binds the runners while carrying Task 0's receipts | Tasks 9–11 NOT reachable under impl-2 (disclosed on the token, not a term it adds); fix = a plan step (0') with must-be-YES/NO cases, folded with the A10/A11 lock transcriptions into ONE revision/review/token; master may ask for it sooner |

Lesson (this seat): a plan whose measurement tasks bind the plan digest needs a resumption step from the first revision after Task 0 — every revision after execution begins orphans the runners. Registered here; the fold lands with the next revision.

## R25 — c4a STOP on the untouched probe fixture; dispositioned (2026-09-19 17:11–17:32; STOP `intg-substep2b/IMPL-pair-implementer-20260919-171145.md`; disposition `intg-substep2b/PLAN-pair-planner-20260919-173140.md`; SITREP `intg-substep2b/SITREP-pair-planner-20260919-173246.md`)

| Object | Checked at | Result |
|---|---|---|
| the red | the final credential-clean floor at the ten-path candidate (after the review-approved A9.4 header fix): rc 8, `probe` the only failure, `tests/test_probe.cpp:671` `REQUIRE(ledger_child > 0)` saw -1; `harness-selftest` green; `biv_tests` 443/3 | not the credential scanner; one case in an untouched suite |
| the case | origin 2537eb6, last touched d87d83a 2026-08-07; byte-identical at B and the candidate; `biv_probe_tests` = `tests/test_probe.cpp` + `biv_support`, no c4a path; fixture: 50 ms shell script writes a marker, the waiter polls it 200 × 5 ms real time; floor serial (no `-j`, no `execution.jobs`); probe suite 12.28 s vs 10.56 s at c3 | timing-shaped; cause NOT established |
| the registry | `master/RESIDUALS.md` grepped for the case, `ledger_child`, grandchild — no row; R-4.40 is the Linux no-init zombie topology | unregistered; routed TO master as a residual candidate |
| host scout (read-only, the 2026-09-04 host binary at B) | isolation ×20 → 20 pass; 2× core-count `yes` load ×20 → 20 pass | not reproduced at this seat; the load hypothesis unsupported here |
| the disposition | D0 pin (write set, diff digest, binary digest); D1 isolation ×20; D2 load ×20; rule: D1 clean → D3 ONE fresh floor at the unchanged candidate (diff re-compared; rc 0 = Step 4's final-byte evidence; a red D3 STOPs, no third run); D1 red or a foreign assertion → STOP, no D3 | every block walked: D0 on the candidate worktree into a scratch home; D1/D2 shortened; D3's four branches with the floor stubbed (red / green / unclean D1 / changed candidate) each separating |
| my own defects caught by the walk | the D3 guard read field 2 (`pass=`) instead of field 3 (`fail=`) and would have refused a clean D1; `(yes > /dev/null) &` leaked the load processes past `kill $!` (the subshell died, `yes` survived — 30 orphans on the host from my scout, killed) | fixed before filing; `yes_left` recorded in D2's receipt |

Asked of master (173246): register the observation and name the probe suite's owner; confirm a green D3 is Step 4's completion evidence; the carry (162750) stands as the other hold on c4a's commit.

## R26 — the carry filed; t-oracle.txt written; D1 reproduces the probe red; R-4.62 arm (a) triggers (2026-09-19 17:49–18:04; carry `intg-2b-wiring-act/PLAN-master-planner-20260919-174907.md`; answers `…175324.md`; m-3 owner receipt `…DESIGN-planner-20260919-180036.md`; implementer STOP `intg-substep2b/IMPL-pair-implementer-20260919-175439.md`; my relays 180215 (TO implementer) and 180426 (TO master))

| Object | Checked at | Result |
|---|---|---|
| the carry 174907 | tracked, unmodified at pdc 259d0e03, sha256 `de79f1a1…`; the five fields byte-equal to the lines I named in 162750; `TO: intg.pair-planner` exact | the plan's T-ORACLE block run from the candidate worktree with the real file → `t-oracle OK`, six-digest receipt; request-as-carry control → `relays-not-distinct` STOP |
| `$RUNNERS/t-oracle.txt` | written 17:59 (four lines; sha256 `b8c8c8fc…`); bytes embedded in 180215 and re-compared | the plan's assignment to this seat; Step 5's file gate now passes; Step 5 still closed on Step 4 |
| D1/D2 (175439) | D1 18/20 at the D0-pinned candidate binary (run 16 `:671` -1 = absent marker; run 17 `:606` 1179 ms > 800 ms — the case's first half, same real-time class); D2 20/20 under 30 `yes` workers; candidate diff and binary digests unchanged | both STOP rules fired as ruled; no D3; reproduced in isolation |
| host A/B scout (this seat) | the host binary at B and the candidate binary, the same case ×20 each interleaved in one window | 20/20 + 20/20 — the candidate build not shown implicated; the reds sit in one two-second window on the implementer's host (log mtimes 17:45:27/28; ~0.9 s per run) |
| m-3's arms (180036) | (a) ≥1/40 → test-only fixture-bounded wait at m-3, Domain Reviewer approves, recipe re-run as witness; (b) 0/40 → adequate + host artifact; (c) second observation → escalate | (a) TRIGGERED by m-3's own rule (2/40); the :606 budget is the same class — m-3's call whether (a) bounds it |
| the discriminators 180036 asks | -1 → absent file: ESTABLISHED (run 16 log); wall time: from log mtimes only (no durations printed); host load: NOT recorded; marker post-run: not recoverable | carried as far as the receipts reach; the rev17 recipe records all three per run |
| the vehicle (asked of master) | recommended: the Task 8 shape — m-3's test-only commit carried into the branch under `$RUNNERS/m3-r462-patch.txt` as a Task 4 Step 3c BEFORE the floor; rev17 = Step 3c + the resumption step 0' (+ A10/A11 only if locked by then — both reviews still open per m-3's 180409); one review; token impl-3 | alternative (land on main, re-pin B) re-cuts every prefix receipt — not recommended |
| my miss | 180215 submitted in the same command as the listing that showed 180036 (unopened at submit) — the plan-9 class, second instance | content unaffected; disclosed in 180426; the listing was its own command for 180426 |

## R27 — rev17 filed as plan-18: R-4.62 arm (a) as Task 4 Step 3c; the resumption step 0′ (2026-09-19 19:10–19:34; master `intg-2b-wiring-act/PLAN-master-planner-20260919-191012.md` (the fields), `…182240.md` (the vehicle), m-3 `…DESIGN-planner-20260919-183855.md` (the patch), m-3.implementer `…DESIGN-REVIEW-implementer-20260919-190602.md` (the approve); relay `intg-substep2b/PLAN-pair-planner-20260919-193414.md`; artifact `0161c7dd…` at 8f9e391, 2718 lines)

| Object | Checked at | Result |
|---|---|---|
| the patch | `master/domains/m-3-restore-cli/patches/2026-09-19-r462-test-probe-fixture-bounds.patch` tracked, unmodified, sha256 `69e8db84…` == the approve's `TARGET_PATCH_SHA256`; mailbox author `m-3.planner <m-3.planner@local>`; `--numstat` `11 5 tests/test_probe.cpp`; `--check` rc 0 at the candidate worktree (ten dirty paths) and at the host main; content: both waiter polls 200 → 6000 × 5 ms, first-half wall 1000 → 10000 ms, promptness 800 → 5000 ms, the sibling `:943` poll the same guard; `:531` untouched by m-3's scope ruling | the fields transcribed into `$RUNNERS/m3-r462-patch.txt` (three lines, sha256 `e15e226a…`) |
| `git am` on a dirty unrelated tree | scratch clone at 13ec732 with a dirty `src/cli/main.cpp` | applies; author preserved; the dirty path untouched — the shape Step 3c relies on |
| the marker capture | `TempDir` uses `temp_directory_path()` (honours `TMPDIR`) and `remove_all` in its destructor; the marker lives ~10 ms; one clock call (perl) costs ~5 ms | a black-box witness cannot read the marker after the run; the watcher reads FIRST (1 ms re-reads until content or gone), THEN takes the clock — the walk saw empty reads when the clock came first; the assertion's `-1`/`0`/`>0` stays the primary discriminator; stated in the plan prose |
| Step 3c walk (scratch clone at c3 + the candidate's exact ten-path diff, `../pdc` symlinked) | five pre-commit mutants: wrong `sha256=` → `patch-sha`; the authoring relay 183855 as `relay=` → `relay-from`; the probe file dirty and an eleventh dirty path → `pre-write-set`; the pre-image altered at HEAD → `preimage` — each before any commit; the must-be-YES: ONE commit d752b88 by m-3.planner touching only `tests/test_probe.cpp`, post-image `fbaee3bf…`, ten dirty paths unchanged, rebuild rc 0, binary digest changed, witness (shortened) green with the marker's PID captured; a mutated case name → `witness-red`, no retry | the block as filed |
| Step 0′ walk (a scratch mirror of the REAL runners + evidence directories; the plan-rev17 file as the plan on disk) | the must-be-YES: a new runners directory (lock = the plan on disk, token id, the two instruments re-extracted, `blocks.txt` 22 entries, fourteen carried receipts and gate files re-compared, `carried.sha256`, `previous-runners/lock`, the pointer preserved then rewritten, the sealed copy under `$EVID/runners/resume-<token>/`), the controller's lock line and Task 9 predecessor gate satisfied in it; six mutants (the old rev12 lock typed; the same lock; `task-0.done` absent; `task-0.sh` altered; a malformed token id; the sealed copy differing) STOP before any write | the block as filed; the walk's scratch runner directories removed from the evidence root |
| the four runner proofs | Tasks 0/9/10/11 extract + check at rev17: gates 3/13/4/2, omitted 0, rc 0 | unchanged |
| A10/A11 rev7 | approved by m-3.implementer 190600/190601; MUST-REVISED by the Master Reviewer 192826 (A10 bundle command rc 128; A11 oracle counts 37/6) at the binding re-verify | NOT transcribed; c4b / c6b HOLD; the relay says must-revised, not approved-not-locked |
| my defects caught by the walks | the generator's quoting (a double-quoted span inside a Python string); the 0′ walk harness (a 0500 file it could not mutate; the YES summary captured into a variable); the watcher's clock-before-read | fixed before filing; none in the filed bytes |

The docs title still reads "(rev8)" as it has since rev8 — the revision of record is the history's first bullet and the relay's PLAN_LOCK_ID; left as is.

## R28 — rev17 MUST-REVISED on the runner side (MUST-2B-36/37); rev18 filed as plan-19 (2026-09-19 21:32–22:20; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-213206.md`; master `intg-2b-wiring-act/PLAN-master-planner-20260919-211410.md` (A10/A11 rev8 routed to m-3); relay `intg-substep2b/PLAN-pair-planner-20260919-222008.md`; artifact `4168c6da…` at 9c6156d, 2735 lines)

The implementer walked rev17's `resume.sh` and found two defects the pair Planner's own walk did not see.
MUST-2B-36: the T-ORACLE carry binds the LIVE plan digest (`T_ORACLE_PLAN_SHA256:` in master's 174907 = the rev16 digest `7f538d82…`), so the `t-oracle.txt` written 17:59 is stale for every later revision, and rev17's `resume.sh` carried it byte-for-byte into a deterministic Step-5 STOP (`plan-sha-mismatch-live-0161c7dd…`, reproduced by the reviewer).
The pair Planner's walk had run the resumption positive without pushing the new directory through the T-ORACLE prefix, so it could not see that a carried gate file can be valid in form and stale in binding.
MUST-2B-37: rev17 preserved and rewrote the canonical pointer `$EVID/runners-dir.txt` BEFORE creating the seal, so a `seal-dir` failure left an unsealed directory canonical and the retry died on `same-lock` (the reviewer's scratch negative: `POINTER_ADVANCED=yes`, `SEAL_FILE_COUNT=0`).

| Object | Checked at | Result |
|---|---|---|
| rev18 `resume.sh` order | pre-flight (every check, no write, incl. `t-oracle-stale` on a carried locator without exactly one `plan_sha256=<new lock>` line, and `seal-exists`) → build unpublished (the new directory, both instruments, the carried receipts, the seal assembled inside it) → seal (`cp -R`, no clobber, 8 files, the note re-compared) → publish LAST (`runners-dir.prev-<stamp>.txt` no clobber; `runners-dir.txt.new-<stamp>` staged in the same directory, verified, `mv -f` over `runners-dir.txt`) | a STOP before the last act removes ONLY what the run created and has not published (the seal copy, the staged pointer, the new directory) |
| the process rule (Step 0′ prose) | every revision after a carry needs a FRESH five-field carry: after the exact-hash approve the pair Planner names the new digest to master (042216's rule), master carries, the pair Planner rewrites `$RUNNERS/t-oracle.txt` (the old preserved as `t-oracle.prev-<stamp>.txt`) BEFORE the token | `intg-substep2b-impl-3` mints only once the file on disk names the digest the token names |
| the positive walk | a scratch mirror of the REAL runners + evidence directories, a fresh `t-oracle.txt` naming the rev18 digest; scratch clones of bivpak (the plan at rev18 bytes) and pdc (a synthetic COMMITTED carry `PLAN-master-planner-20260919-221700.md` naming the rev18 digest — a fixture in the clone only, nothing under `../pdc`) | binds, seals, publishes (pointer = the new directory; the prev file = the old; seal 8 files equal to `<new>/seal/`; 15 carried; the Task 9 preconditions met); the EXACT Step-5 T-ORACLE prefix from the new directory → `t-oracle OK`, the receipt naming the lock |
| the stale negative | the real rev16 `t-oracle.txt` carried | `t-oracle-stale` at pre-flight, no write; pushed through the T-ORACLE prefix → `plan-sha-mismatch-live-4168c6da…` |
| six early mutants | the rev12 lock typed; the same lock; `task-0.done` absent; `task-0.sh` altered; a malformed token id; the sealed copy differing | each STOPs on its own predicate with no write (no new directory, pointer byte-identical, no seal) |
| four late mutants, each retried | the seal path pre-existing → `seal-exists`; `$EVID/runners` chmod 555 → `seal-copy`; a `cp` shim on PATH corrupting the copied note → `seal-note-mismatch`; `$EVID` chmod 555 → `preserve-pointer` (AFTER the seal was copied) | each leaves the pointer byte-identical, no seal, no staged pointer, no directory in the evidence root; each retries to success once the cause is removed |
| the four runner proofs | Tasks 0/9/10/11 extract + check at rev18: gates 3/13/4/2, omitted 0, rc 0 | unchanged |
| the delta | rev17 → rev18: the Step 0′ paragraph, the `resume.sh` block, the history; Step 3c / Step 4 / Task 4 Files byte-identical | the reviewer's 213206 Step 3c positive stands on the same bytes |
| my defects caught this round | the generator's unique-anchor lookup tripped on the block's closing fence (eight follow); `cmp` printing a difference to stdout on a STOP (the script's only-stdout-line property) | fixed before filing; none in the filed bytes |

Master 211410 routed A10/A11 rev7 to m-3.planner for rev8 with master's own reproduction; nothing moves at the pair on it (c4b / c6b hold; untranscribed).
The lesson is the reviewer's, not mine: a carried gate file must be pushed through the gate that consumes it, and a canonical pointer is published after everything it points at exists.

## R29 — rev18 MUST-REVISED on three more resume.sh defects (MUST-2B-38/39/40); rev19 filed as plan-20 (2026-09-19 22:48–23:08; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-224817.md`; relay `intg-substep2b/PLAN-pair-planner-20260919-230821.md`; artifact `7c3b5a54…` at f22a16b, 2737 lines)

The implementer walked rev18's `resume.sh` with three controls of their own and each separated a defect my walk had not reached.
MUST-2B-38: the pre-flight counted the MATCHING `plan_sha256=` line, not the field's cardinality, so a locator holding a current line beside the stale rev16 line passed pre-flight and published; Step 5's `field` parser would then refuse it (`field-plan_sha256-count-2`) only after publication.
MUST-2B-39: after the recursive seal copy only the note was compared, so a copier that altered any of the seven binding files published (their shim changed the sealed `plan-lock.txt`; my note-corrupting shim could not see it).
MUST-2B-40: the `mv` was followed by a fallible read-back inside the unpublished window, so a failed read after a successful `mv` cleaned up the seal and the directory the canonical pointer already named — a dangling pointer, the very class MUST-2B-37 required the successor to close.

| Object | Checked at | Result |
|---|---|---|
| the T-ORACLE pre-flight | total `^plan_sha256=` lines == 1 AND exact current lines == 1, each producer's rc checked apart from its predicate, before any write | a current line beside the stale one (fields 2, current 1) and two current lines → `t-oracle-stale`, no write, pointer byte-identical |
| the seal | every one of the eight files compared byte-for-byte to the built seal after the copy (`seal-<file>-mismatch`), before pointer preservation | a `cp` shim copying faithfully except the sealed `plan-lock.txt` → `seal-plan-lock.txt-mismatch`, the unpublished seal and directory removed, the pointer byte-identical; the retry with the real `cp` publishes |
| the publication boundary | `PUBLISHED=1` the instant `mv` returns 0, before any later operation; the read-back STOPs `published-verify` with everything retained and prints the by-hand disposition; the STOP handler removes nothing once published | a path-sensitive `cat` shim failing the first read of `runners-dir.txt` holding the new value → `published-verify`, the pointer AT the new directory, that directory and the 8-file seal retained, a rerun → `same-lock`, the T-ORACLE prefix passing from the published directory |
| the rev18 set re-run | the positive through the exact Step-5 T-ORACLE prefix; the stale file; six early mutants; the four late mutants (the note shim now `seal-resume.txt-mismatch`) each retried | all as at rev18 |
| the four runner proofs | Tasks 0/9/10/11 extract + check at rev19: gates 3/13/4/2, omitted 0, rc 0 | unchanged |
| the delta | rev18 → rev19: the Step 0′ paragraph, the `resume.sh` block, the history; nothing else | Step 3c / Step 4 / Task 4 Files byte-identical to rev17 |

Three consecutive runner-side must-revises on one block (rev17 → rev18 → rev19) after my own walks passed each revision.
The reviewer's controls were the ones I had not written: a cardinality mutant of the field my gate greps, a copier that alters a file my compare does not read, and a fault AFTER the act I called the last one.
The pattern: my mutants tested the predicates I had written; theirs tested the predicates I had not.

## R30 — rev19 APPROVED at the exact hash; the word for the fresh carry (2026-09-20 04:46–04:49; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-044621.md`; word `intg-substep2b/SITREP-pair-planner-20260920-044918.md`)

The implementer approved rev19 (`7c3b5a54…` at f22a16b, 2737 lines) after re-running every control at the exact bytes: the two cardinality negatives, the `plan-lock.txt`-corrupting copier with retry, the failing post-`mv` read with the pointer, directory and seal retained and a rerun on `same-lock`, the six early and four late mutants, and the positive through the exact Step-5 T-ORACLE prefix.
The approve grants the governance transition only: master's fresh five-field carry for this digest, then the rewrite of `$RUNNERS/t-oracle.txt`, then the token.

| Object | Checked at | Result |
|---|---|---|
| the live plan | re-hashed at the word's filing; `git show f22a16b:<plan>` | equal, `7c3b5a54…` |
| the three owner objects | pdc HEAD aebf4325, each tracked and `git diff --quiet HEAD` clean | 033307 `20c9f24d…`, 155106 `e706797e…`, 131720 `6e5b3023…` — byte-identical to 174907's three lines |
| the T-ORACLE block on the new five lines | scratch clones of bivpak and pdc, a synthetic COMMITTED carry with `TO: intg.pair-planner` | `t-oracle OK`, the receipt naming the digest; the same carry with the implementer added to the TO line → `carry-to` |
| the word | TO master, python-written from the computed fields; upstream listed as its own command (nothing newer than 211410) | filed 044918 |

WAITING on master's carry.
On its path: preserve `t-oracle.txt` as `t-oracle.prev-<stamp>.txt`, rewrite it with exactly one `plan_sha256=` line, run the gate from the candidate worktree against the real file, then token `intg-substep2b-impl-3` (PARENT `intg-substep2b-plan-review-18`; Step 0′ first).

## R31 — the fresh carry; t-oracle.txt rewritten; token impl-3 issued (2026-09-20 04:57–05:10; carry `intg-2b-wiring-act/PLAN-master-planner-20260920-045732.md`; token `intg-substep2b/IMPL-pair-planner-20260920-051031.md`)

Master filed the fresh five-field carry within the turn: `T_ORACLE_PLAN_SHA256:` = the rev19 digest, the three owner-object lines byte-identical to 174907's, tracked and unmodified at pdc HEAD cb107a13.
The stale rev16 `t-oracle.txt` was preserved as `t-oracle.prev-20260920-050633.txt` and the file rewritten with four lines and exactly one `plan_sha256=` line naming the rev19 digest.
The plan's T-ORACLE gate block, re-extracted from the live plan and byte-equal to the walk copy, ran from the candidate worktree against the real file with a scratch evidence directory and passed.

| Object | Checked at | Result |
|---|---|---|
| the carry | tracked, unmodified, `TO: intg.pair-planner`, the five fields once each | sha `99bf54b0…` |
| `$RUNNERS/t-oracle.txt` | rewritten; the previous preserved beside it | sha `9d2847bb…` (0400); prev `b8c8c8fc…` |
| the gate | the live block from the candidate worktree, scratch `$EVID` | `t-oracle OK`, the receipt naming the digest |
| the token | `intg-substep2b-impl-3`, PARENT `intg-substep2b-plan-review-18`, plan `7c3b5a54…`, 38-path SCOPE_DIFF all-in (impl-2's 37 + `tests/test_probe.cpp` for Step 3c), every digest computed at issuance; lineage walked on a mini-root (only the known-red classes) | filed 051031, sha `8373c7f3…` |
| A10/A11 | m-3 rev8 pins 050201/050202 → m-3.implementer approves 050925/050926 → master 050824 flags the `(rev7)` line-1 titles (owner's call; rev9 possible) → the Master Reviewer owed | NOT locked; c4b/c6b/c7/c8 hold |

The token's order: Step 0′ (`resume.sh` once, the new runners directory bound to this lock and id) → Task 4 Step 3c → Step 4 → Step 5 (c4a's commit) → c5 → c3h/c6a.
WAITING on the implementer's execution.

## R32 — impl-3 returned: the rev19 prefix committed through c6a; R-4.62 arm (a) closed (2026-09-20 06:07–06:20; return `intg-substep2b/IMPL-pair-implementer-20260920-060738.md`; SITREP `intg-substep2b/SITREP-pair-planner-20260920-062016.md`)

The implementer ran Step 0′ as walked and then the released order: m-3's R-4.62 patch as one m-3-authored commit, c4a with the fresh T-ORACLE gate, c5, c3h and c6a under A9's lock.
The branch stands at `1065872`, ten commits after B, worktree clean, `git diff --check` clean.
Every mechanical claim of the return was verified at this seat before the word went up.

| Object | Checked at | Result |
|---|---|---|
| the commits | `3431bb7` (m-3.planner, one file, 11/5, post-image `fbaee3bf…`), `ef8e492` c4a 10 paths, `5aeb81c` c5 8, `09563d3` c3h 2, `1065872` c6a 13 | as returned |
| R-4.62 | rebuilt binary `e0a716e3…`; D1 20/20, D2 20/20, rc 0 in 40/40, no retry; wall 782–973 ms | arm (a) CLOSES on m-3's rule; the 5 ms watcher saw the marker in 35/40 and captured content in 22/40 — the black-box sidecar limit the plan states, not a red |
| Step 0′ | new runners `s2b-runners-PEazOQ` (lock rev19, token impl-3, 15 carried, 22 blocks); the 8-file seal equal to the built one; pointer moved last, old preserved as `runners-dir.prev-20260920-051612.txt` | as walked |
| the T-ORACLE receipt | `c4a-t-oracle.txt` names carry 045732 and the rev19 digest once | pass |
| c6a | exit map 29 rows; `RepoDiscoveredUnsupported` absent under src/ schemas/ tests/; the A9 lock gate live/pin re-hashed | pass |
| the suite (the implementer's receipts) | 454 cases, 451 passed, 3 skips; ctest 15/0/3; pytest envelope 6 (`.venv-harness`) | E2 |
| holds | c4b / c6b (no A10/A11 lock file), c7 / c8, Tasks 9–11 | correct |

Two plan evidence-command defects to fold into the lock revision: Task 3 Step 8's `[cli]` Catch2 tag names no case, and Task 5 Step 2's `.biv` line rule reads a context line under the default diff context.
Both were preserved by the implementer, not normalized.

Engine note: the relay daemon now runs kit 2.9.3 from the codex plugin cache (fingerprint `32d92727…`); the 2.9.2 client and the claude-cache 2.9.3 client are both refused (`E-VERSION-MISMATCH`), and this seat files through the daemon's own client at `~/.codex/plugins/cache/agentic-dev-team-skills/adt-master/2.9.3/tools/relay`.
The refused attempts filed nothing.

WAITING on master: the owner byte reviews of `3431bb7..1065872` (recommended now) and the A10/A11 chain (rev8 pins approved by m-3.implementer; the title finding at the owner; the Master Reviewer owed).

## R33 — master's rulings on the prefix (2026-09-20 12:16; master `intg-2b-wiring-act/PLAN-master-planner-20260920-121637.md`; the owner invitations `…121632.md` TO m-3 and `…121635.md` TO m-1)

Master verified the prefix at its own bytes and ruled:
the owner byte reviews open now on `3431bb7..1065872`, with the plan's Task 10 gate read exactly (the GO carries exactly one no-red byte review OF H from each of m-1, m-3 and m-4, so a prefix reading banks and each owner's H review confines its delta to c4b..c8; m-4 stays at H);
R-4.62 arm (a) is CLOSED on m-3's rule, the sidecar counts recorded as the plan's stated black-box limit;
the two evidence-command defects are accepted for the lock revision as proposed;
the A10/A11 chain waits on m-3's title word, then the Master Reviewer, the locks, the two lock files, the lock revision, the exact-hash review, the fresh carry, the `t-oracle.txt` rewrite and impl-4.

Prep executed at this seat, read-only at the head:

| Command | At | Result |
|---|---|---|
| `biv_tests '[cli-flags]'` | 1065872 | rc 0, 6 cases, 190 assertions; `'[cli]'` rc 2, no tests ran |
| `git show --format= --unified=0 5aeb81c -- src/core/scan/scan.cpp \| grep -c '^[+-].*"\.biv"'` | 5aeb81c | 0; the default-context form 1 (an unchanged context line); an added-literal mutant line 1 |

The branch holds at `1065872`; nothing owed from the pair until the lock words.


## R34 — the LOCK revision rev20 filed as plan-21 (2026-09-20 18:56–19:27; master's seal `intg-2b-wiring-act/PLAN-master-planner-20260920-185625.md`; the lock relays `…DESIGN-planner-20260920-184029.md` (A10) and `…184104.md` (A11); the Master Reviewer's `…DESIGN-REVIEW-master-reviewer-20260920-182105.md`; this seat's `intg-substep2b/PLAN-pair-planner-20260920-192708.md`)

Master SEALED both addenda in one act: A10 rev10 `m3-addendum-10-6cba59d3-lock-20260920` (pin `6cba59d3…` at pdc `5cbb59d7…`, post-stamp `56abe662…`) and A11 rev11 `m3-addendum-11-fce9cbfa-lock-20260920` (pin `fce9cbfa…` at `2ce699d7…`, post-stamp `e2776381…`; `partial_suffix=.bvpk-open.partial`, `partial_suffix_relay` = m-1's 162306).
Every pin and post-stamp was re-hashed at this seat; the seal and both lock relays are tracked and clean in pdc.

The two lock gate files were written into the canonical runners `s2b-runners-PEazOQ` (the plan's assignment to this seat), one field per line, with `pin_sha256` / `pin_commit` beside the carrier fields (sha256 `7e1a4157…` / `c38b0580…`, mode 0444).
The seal spells `partial_suffix_relay` without `master/relays/`; the file carries the plan's pdc-relative form, which the block's arm 1 resolves — the reviewer is asked to grade that reading.

Plan rev20 (`f710b39a…` at e3c13a4, 2814 lines) transcribes the A10 rev6→rev10 and A11 rev5→rev11 deltas under the RULE, makes Task 4 Step 0 an executable A10 gate, binds the pin in both gate blocks, spells the lock ids in the c4b / c6b commit messages, and repairs the two evidence commands master 121637 accepted.
The scan.cpp repair reached the Task 9 RUN BLOCK line as well as the prose: the rev19 block measured the default-context diff, which carries scan.cpp's one unchanged `".biv"` line, so it would have STOPped at H on compliant bytes (1 with context, 0 under `--unified=0` at 1065872).

Walked from the candidate at 1065872 with a scratch `$EVID` (no receipt in the implementer's home):

| Gate | Must-be-YES | Must-be-NO (each STOPs before any receipt) |
|---|---|---|
| A11 block (rev19, unmodified) on the real file | pre + post PASS | wrong doc sha, seal = lock, the suffix relay without `master/relays/` STOP; a wrong `pin_sha256` PASSES (the block did not bind the pin — the rev20 reason) |
| A11 block (rev20) | pre + post PASS; the receipt names open.cpp:785 | wrong doc sha `a11-sha-mismatch`; wrong pin sha `a11-pin-mismatch`; wrong pin commit `a11-pin-show`; seal = lock; the suffix relay without the prefix `suffix-relay-unbound`; the A10 lock relay as `relay` `lock-id-absent-in-lock-relay`; a duplicated `lock_id` `field-lock_id-count-2` |
| A10 block (rev20) | pre + post PASS | wrong doc sha; wrong pin sha; wrong pin commit; seal = lock; the carry 045732 as seal `seal-lineage`; the A11 lock relay as `relay`; the planned id `m3-addendum-10-20260916` `lock-id-absent-in-seal`; a duplicated field; a missing field |
| Task 9 scan.cpp line (rev20) | 0 at 1065872 | STOP (1) on a scratch clone with an added `".biv"` literal; the rev19 line reads 1 at the compliant head |

Block census 22 with only task-9's digest moved; runner proofs 3 / 13 / 4 / 2; `resume.sh`, `run-task.sh` and the T-ORACLE block byte-identical to rev19.
`t-oracle.txt` on disk binds the rev19 digest and is STALE for rev20 by design until master's fresh carry.

Filed as `intg-substep2b-plan-21` (192708; sha256 `60a94d2a…`; commit ec59f96) with IN_REPLY_TO the seal; lint OK under 2.9.2 and 2.9.3; no upstream relay newer than 062016 (intg) or 185625 (pdc) at the sweep.
NEXT on the approve: the digest word TO master → the fresh five-field carry at `f710b39a…` → the `t-oracle.txt` rewrite in PEazOQ (the rev19 file preserved) → the token `intg-substep2b-impl-4` (Step 0′ first, then c4b, c6b, c7, c8, Tasks 9–11) → the GO with the three H reviews.

## R35 — rev20 must-revised on two stale count terms; rev21 filed as plan-22 (2026-09-20 19:39–19:43; review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-193911.md`; this seat's `intg-substep2b/PLAN-pair-planner-20260920-194332.md`)

The implementer must-revised rev20 (MUST-2B-41): the c6b commit-topology row still read `ErrKind 27→36` and T-A11's COUNTS still read `27 → 36 (after A9's 27 → 27) … transitional 4 → 7` — A11 rev7's rejected arithmetic, contradicting the locked rev11 census and the plan's own Task 6b leg (l).
Every other rev20 delta passed at the reviewer's seat: both gate blocks pre + post on the real lock files with the reviewer's own controls (a differing pinned blob, whitespace and empty values, a lock-relay path on a non-header line or nowhere), the A11 arm-2 reading, the Task 9 line, the CLI selections.

rev21 (`ab109825…` at 564589c, 2818 lines) rewrites the two terms to the stage-and-membership census (28/29/4 → 28/29/3 → 37/38/6, the six transitional named) and adds the history bullet; no BLOCK moves (census 22 byte-identical to rev20; proofs 3 / 13 / 4 / 2 re-run).
The rev20 sweep had grepped `27->36` and `ErrKind 36` but not the arrow spellings; rev21 swept every spelling of the retired numbers, with hits only in leg (l)'s named mutant and the history bullet.

Filed as `intg-substep2b-plan-22` (194332; sha256 `14d5f50d…`; commit c2aef65, which also carries the daemon's projection of the implementer's 193911 row); lint OK under 2.9.2 and 2.9.3; no upstream relay newer than 193911 (intg) or 185625 (pdc) at the sweep.
NEXT on the approve: the digest word TO master → the fresh carry at `ab109825…` → the `t-oracle.txt` rewrite → `intg-substep2b-impl-4`.

## R36 — rev21 APPROVED at the exact hash; the digest word TO master (2026-09-20 19:47–20:13; approve `intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-194742.md`; this seat's `intg-substep2b/SITREP-pair-planner-20260920-201324.md`)

The implementer approved rev21 at `ab109825…` (`intg-substep2b-plan-review-20`, PARENT `intg-substep2b-plan-22`): MUST-2B-41 closed, the 22-entry block manifest byte-identical to rev20, the 193911 gate walks carried, the lock files re-hashed unchanged.
The approve authorizes no product byte: the fresh five-field carry at this digest, the `t-oracle.txt` rewrite and a separately addressed `intg-substep2b-impl-4` remain the pre-token gates.

The digest word went TO master with the five field lines computed from the files (the three owner objects re-hashed at pdc HEAD 4f1ab9a8, tracked and clean; only `T_ORACLE_PLAN_SHA256:` changes from 045732).
Before filing, the T-ORACLE prefix (byte-identical since rev18) ran in scratch clones on a synthetic committed carry at the new digest: `t-oracle OK`; the TO line with a second addressee STOPs `carry-to`; a locator holding the rev20 digest STOPs `plan-sha-mismatch-live-…`; nothing written under `../pdc`.

Filed at 201324 (sha256 `be4870ae…`; commit f162ecb, which also carries the daemon's projection of the implementer's 194742 row).
NEXT: master's carry → preserve + rewrite `t-oracle.txt` in `s2b-runners-PEazOQ` → the gate run against the real file with a scratch `$EVID` → the token `intg-substep2b-impl-4` (PARENT `intg-substep2b-plan-review-20`).

## R37 — master's fresh carry; `t-oracle.txt` rewritten; Step 0′ walked; token impl-4 issued; the c8 ask (2026-09-20 20:32–20:5x; carry `intg-2b-wiring-act/PLAN-master-planner-20260920-203219.md`; token `intg-substep2b/IMPL-pair-planner-20260920-205111.md`; the ask `intg-substep2b/SITREP-pair-planner-20260920-205256.md`)

Master carried the five T-ORACLE fields at the rev21 digest (203219; sha256 `cc4379d4…`, tracked and clean at pdc HEAD f2616486; only the plan line changed from 045732).
The canonical `t-oracle.txt` in `s2b-runners-PEazOQ` was preserved as `t-oracle.prev-20260920-204502.txt` (`9d2847bb…`) and rewritten (`1aad9ef7…`, four lines, exactly one `plan_sha256=` line); the T-ORACLE prefix run from the candidate worktree against the real file with a scratch `$EVID` printed `t-oracle OK`.

Step 0′ (`resume.sh`, byte-identical since rev19) was walked on a scratch mirror of the real runners and evidence directories: the positive built, sealed (8 files) and published with 17 carried lines, every carried file byte-equal to the canonical directory, and the prefix passed from the new directory against the real carry; the preserved rev19 locator STOPped `t-oracle-stale`, an old lock equal to the new STOPped `same-lock`, a malformed id STOPped `token-form`; no directory was left in the evidence root and the real pointer was untouched.

Token `intg-substep2b-impl-4` issued (205111; sha256 `2aa5590a…`; commit 8e0908c): PARENT `intg-substep2b-plan-review-20`, `T_ORACLE_CARRY` 203219 by digest, `T_ORACLE_FILE_SHA256` the rewritten file, the 38-path SCOPE_DIFF all-in with every row's evidence rewritten for the landed prefix, the two lock files quoted by bytes; order Step 0′ → c4b (A10 gate pre/post) → c6b (A11 gate pre/post) → c7; the delegated-dispatch lineage walked on a three-relay mini-root.
Task 8 HOLDS: m-3's harness patch (arm-A shape, `harness/scenarios/**` only) is not on record in pdc, so `$RUNNERS/m3-harness-patch.txt` cannot be written; the ask went TO master (20260920-205256; sha256 `ab5f83e4…`), routed through master to m-3, so the file can exist when c7 lands.

## R38 — R-4.65: two reds in landed lane bytes; the c8 gate file; rev22 (2026-09-21 16:50–17:20; master `intg-2b-wiring-act/PLAN-master-planner-20260921-143755.md` + `…-165137.md`; this seat's `intg-substep2b/SITREP-pair-planner-20260921-170127.md`, `…-170128.md`, `intg-substep2b/PLAN-pair-planner-20260921-171525.md`, `intg-substep2b/SITREP-pair-planner-20260921-171624.md`)

Master routed m-3's approved c8 harness patch (rev3 `8517aaf6…`, m-3.implementer's approve 133052, m-1's `C8_DIR_MTIME_RULING: a` 141529) and two reds m-1 found one fixture wider than c8's, both reproduced at master and at m-3's seat and both execution of sealed text.
RED-1 (c5 `5aeb81c`): `biv pack` drops a clean repository's `.gitignore`d penumbra silently — pack-engine §1.1 / §1.3 / §3.2 say payload always, never silent; the scan excludes the whole repo subtree and nothing reads the engine's `penumbra_paths`.
RED-2 (c4a `ef8e492`): the directory-mtime pass runs before `restore_repos`, so a payload directory above a restored repository loses its archived mtime (restore-apply §5).
m-3 confirmed both open halves with veto conditions V2-1..6 / V1-1..7 (164214 + face lines 164238, carried by 165137); V1-6 keeps the workspace-root row out of its word.

`$RUNNERS/m3-harness-patch.txt` was written into `s2b-runners-PEazOQ` (three pdc-relative lines like the R-4.62 file, 0444, `86d8d7e3…`) after verifying the patch hash, the approve's seven face lines, the mailbox author and `git apply --check` at the candidate head.
Under rev21 the file could not be consumed: Task 8 said `harness/scenarios/**` only, and the patch has twelve paths, nine admitted outside by m-3's explicit line.

Reading the code for the fix, this seat found the root-row case the owners' words left open: under the kept root order, an ignored file inside a tracked directory needs that directory as an image member for the first pass, and a file ignored only by the source's `.git/info/exclude` is laid before the root checkout and fails its worktree verification.
That is a STOP under V1-6, routed to master (170128) with a recommended arm (`RED1_ROOT_ROW: defer`, m-3's word) and one derived pack cell (`RED1_PENUMBRA_DIRS`, m-1's word: directory members are the untracked-only directories strictly inside each repo).
The plan's own Task 7 workspace-root leg carried the same omission as V-2b-5 ("the ignored file returns through the engine's penumbra, not payload") — owned and corrected.

rev22 (`84e48e71…` at 9d2ba96, 2994 lines) adds Task 6c `c6m` and Task 6d `c6p` after c6b as new commits, holds c6p before its first byte on `$RUNNERS/red1-owner-words.txt`, widens Task 8 to the twelve paths with an executable gate, and makes `resume.sh` carry the new gate file.
Every changed block was walked on scratch clones before filing: the T-RED1 gate (YES pre and post; 17 NO cases, each at its own predicate), the Task 8 block (YES: one commit authored m-3.planner touching exactly twelve paths; 8 NO cases, a synthetic thirteen-path patch isolating the numstat predicate), and `resume.sh` (19 carried lines with the new file, 18 without; the three controls; impl-4's lock against rev22 STOPs `plan-not-the-new-lock`).
Tasks 0 / 4 / 5 / 6a / 6b / 9 / 10 / 11 are byte-identical to rev21.

Sequencing: the hold point told to the implementer (170127) was Step 0′ → c4b → c6b under impl-4, then hold before c7; rev22 went live before the implementer ran Step 0′, so by that notice's own rule impl-4 runs nothing and c4b / c6b move under impl-5 (reported to master, 20260921-171624; sha256 `5d065c25…`).
Lesson recorded: `/tmp/s2b/rv6/plan_blocks.py` had been swept from `$TMPDIR`; the walks used the runners' own copy from the scratchpad.

## R39 — rev22 must-revised (MUST-2B-42); rev23 filed (2026-09-21 17:32–17:40; `intg-substep2b/PLAN-REVIEW-pair-implementer-20260921-173212.md`; `intg-substep2b/PLAN-pair-planner-20260921-173710.md`)

The implementer must-revised rev22 on one finding: Task 8 admitted three `harness/bivharness` paths from m-3's rev3 patch, but Task 9 Step 2's zero-byte fence still covered the whole `harness/bivharness` directory, in its runner line and its prose, and Out-of-scope still forbade every `harness/bivharness` byte.
The valid c8 commit would therefore have stopped Task 9 every time.
rev22's sweep checked `harness/scenarios` phrasings but not the fences on the newly admitted directories — the same class as the rev20 arrow miss: a widened scope must be swept against every existing prohibition of the newly admitted paths.

rev23 (`4bb33063…` at b555cbf, 2997 lines) replaces the one fence line with three, each also a prose gate span: the zero-byte fence names `harness/bivharness/e3.py`; the changed `harness/bivharness` paths since B must be exactly c8's three; and their bytes must equal c8's (the tree at c8's parent equals B there, and HEAD equals c8).
Out-of-scope forbids only bytes beyond the c8 commit.
Only the task-9 block moved; its proof reads 16 gates with none omitted or out of order.
Walked on a scratch clone with c8 made by Task 8's own block: YES passes; e3.py touched, an adapters file touched, a fourth path, a change after c8, a change before c8, and a missing c8 record each STOP at the intended line.
Filed as plan-24 (sha256 `b496220e…`).

## R40 — rev23 approved; the digest word TO master (2026-09-21 17:50–17:58; `intg-substep2b/PLAN-REVIEW-pair-implementer-20260921-175012.md`; `intg-substep2b/SITREP-pair-planner-20260921-175351.md`)

The implementer approved rev23 at the exact hash `4bb33063…` (175012, `intg-substep2b-plan-review-22`), replaying the three new Task 9 fence lines on disposable clones and carrying rev22's positive evidence on byte-identical bytes.
The word TO master carries the five T-ORACLE field lines; the three owner objects re-hash unchanged at pdc HEAD 7090bc6a, and only the plan digest moves from 203219's.
Before filing, the T-ORACLE prefix (byte-equal to the first 56 lines of rev23's Task 4 Step 5 block) was run on scratch clones against a synthetic committed carry made from 203219 with only the digest changed: YES passed with its receipt; a two-seat TO line and a rev22-digest locator each STOPped with no receipt.
Next: master's fresh carry, then the `t-oracle.txt` rewrite in the current canonical runners (previous preserved), the consumer walk, and `intg-substep2b-impl-5` (PARENT 175012). c6p additionally waits on master's carry of the two T-RED1 face lines (170128). Filed sha256 `f1cf21cb…`.

## R41 — master's carry at rev23; `t-oracle.txt` rewritten; impl-5 issued with c6p held for rev24 (2026-09-21 19:37–20:13; master `intg-2b-wiring-act/PLAN-master-planner-20260921-193745.md`; m-3 `…/DESIGN-planner-20260921-200917.md`; m-1 `…/DESIGN-planner-20260921-200936.md`; token `intg-substep2b/IMPL-pair-planner-20260921-201255.md`)

Master carried the five T-ORACLE fields at `4bb33063…` (193745, sha256 `a49b311f…`, tracked and clean at pdc HEAD 9497d7f2); each field was checked against the files before use.
`t-oracle.txt` in `s2b-runners-PEazOQ` was preserved as `t-oracle.prev-20260921-200707.txt` (`1aad9ef7…`) and rewritten (`920a64cd…`, one `plan_sha256=` line).
The T-ORACLE prefix run from the candidate worktree against the real file passed; Step 0′ walked on a scratch mirror published with 18 carried lines, all byte-equal, and the prefix passed from the new directory; the stale-locator, same-lock and token-form controls stopped with no directory left.

While the token was being built, both T-RED1 owners answered master: m-3 `RED1_ROOT_ROW: defer` (200917) and m-1 `RED1_PENUMBRA_DIRS: confirm` (200936) — the words the plan names.
m-3's word adds root-row veto conditions V1-8..12 (the deferred writer refuses `.git`-segment and `payload/.biv/…` members; verification unchanged before placement; an exact joint root witness with a kept-order mutant), and m-1's names the DIRECT reading of the directory rule as the c6p witness's mutant, with a ground-truth fixture; rev23's Task 6d carries none of these.
An owner word that changes a planned task needs a plan revision, so c6p waits on rev24 and a later token, and `red1-owner-words.txt` is not written before then.

`intg-substep2b-impl-5` was issued (201255, sha256 `49c268c7…`, commit 00607e9; PARENT `intg-substep2b-plan-review-22`; 47-path SCOPE_DIFF all-in — impl-4's 38 plus c8's nine admitted harness paths; the mini-root lineage walk showed only impl-4's four known mini-root classes).
It releases Step 0′ → c4b → c6b → c6m; c6p's own gate stops `file-absent`; c7, c8 and Tasks 9–11 follow under the next token.
rev24 will be committed only after the implementer's Step 0′ has published under impl-5 (read from the evidence home's runners pointer), so the resume step is never orphaned; c4b / c6b / c6m do not re-hash the plan.
Registered by the owners, not this lane's to act on: m-1's R-a (empty directories inside a repository not carried), R-b (step 6's Arm-1 form), R-c (`exclude-rules-local` never emitted); m-3's `.git`-segment observation on the first pass (for m-4 / m-1).

## R42 — impl-5 returned; the T-RED1 words carried; rev24 filed (2026-09-22 00:00–01:25; `intg-substep2b/IMPL-pair-implementer-20260921-224404.md`; master `intg-2b-wiring-act/PLAN-master-planner-20260921-211701.md`; `intg-substep2b/PLAN-pair-planner-20260922-012027.md`; `intg-substep2b/SITREP-pair-planner-20260922-012122.md`)

impl-5 returned: Step 0′ published `s2b-runners-QzzQ11` (18 carried lines), then c4b `cd12bb5`, c6b `cd51937` and c6m `e5afe9d` landed in order; c6p's gate stopped `file-absent` as dispatched, with no c6p byte.
Verified at this seat: the path sets, the gate receipts, a clean worktree, and `ctest --preset ci-macos -E '^safety-hardening$'` re-run at `e5afe9d` (18 tests, 100% passed, three safety tests skipped, rc 0).
One undisclosed path: c6b's commit carries `src/core/open/open.hpp` (`RepoOutcomeRow` gains `kind` / `detail`), which Task 6b's Files line and commit block do not list; it is inside impl-5's SCOPE_DIFF and additive, and is reported to master, recorded in rev24's history bullet, and put to the implementer and the owners' byte reviews.

Master carried both T-RED1 words (211701). `red1-owner-words.txt` was written into `s2b-runners-QzzQ11` (`5431f3d1…`) and the plan's Task 6d gate passed pre and post against the real carriers; a carry citing neither word stopped at `carry-cites-m3`.
rev24 (`265ec83c…` at 4a54e2b) folds m-3's V1-8..12 and m-1's direct-reading mutant into Task 6d only, with every block byte-identical; it was committed after impl-5's Step 0′ had published.
V1-12's status claim and m-1's fixture were executed before filing and matched.

## R43 — rev24 must-revised (MUST-2B-43..46); rev25 filed (2026-09-22 01:50–02:50; `intg-substep2b/PLAN-REVIEW-pair-implementer-20260922-015007.md`; `intg-substep2b/PLAN-pair-planner-20260922-024604.md`)

The implementer must-revised rev24 on four findings, retaining the positive T-RED1 evidence (the gate replayed pre and post; the V1-12 and m-1 fixtures corroborated independently).
MUST-2B-43: a broad token allowlist does not amend a narrower task contract — c6b's `open.hpp` had to enter Task 6b's own record, and master's disposition had to gate the next carry.
MUST-2B-44 and -45: H5 and H6 did not bind discriminating mutants — H5's root hook had no baseline, and H6's `.biv` path could collide with c4b's offline artifact, so removing either refusal could still stop at the ordinary final-path guard.
MUST-2B-46: the carrier's BRIDGE still named impl-5.
The implementer also registered a live INDEX append inversion (its 015007 row landed before this seat's 012122 row); it stands as registered.

rev25 (`f2b2943f…` at cd83db5) records `open.hpp` in Task 6b's Files line, commit block and topology row; adds T-C6B (the carry request and the next token wait on a master relay disposing of the deviation); splits H5 into a root arm on `payload/.git/c6p-sentinel` (no baseline file; `.git` always exists) and a lib arm on the existing `lib/.git/config`, opened `--network`, with M6 discriminating on the created sentinel; and gives H6 unique `payload/.biv` + `payload/.biv/c6p-sentinel` members under `--network`, with M7 discriminating on their creation.
H6's premise was executed: the candidate's built `biv` opening a clean root repository with `--network` creates no `.biv`.
Every block is byte-identical to rev24. Lesson recorded: a mutant is evidence only if the guard it removes is the ONLY one that can fire on its fixture.

## R44 — rev25 approved; T-C6B disposition asked before the carry word (2026-09-22 03:35–03:50; `intg-substep2b/PLAN-REVIEW-pair-implementer-20260922-033502.md`; `intg-substep2b/SITREP-pair-planner-20260922-040233.md`)

The implementer approved rev25 at `f2b2943f…` (033502, `intg-substep2b-plan-review-24`), closing MUST-2B-43..46 and replaying the Task 6d gate on the real carriers.
T-C6B holds the carry request and the next token on a master relay disposing of c6b's `open.hpp` deviation, so the relay to master reports the approve and asks ONLY for that disposition; the digest word with the five T-ORACLE fields follows the disposition, then the `t-oracle.txt` rewrite in `s2b-runners-QzzQ11` and impl-6 (PARENT 033502).
INDEX data integrity: two implementer relays exist on disk with no INDEX row — `IMPL-pair-implementer-20260921-224404.md` and `PLAN-REVIEW-pair-implementer-20260922-015007.md`; no INDEX commit ever carried either row, so they left the daemon-written working file before any path-scoped commit. This seat never hand-edits INDEX; the register went to master for the engine's owner.

## R45 — T-C6B disposed; the rev25 digest word TO master (2026-09-22 04:26–04:5x; master `intg-2b-wiring-act/PLAN-master-planner-20260922-042625.md`; `intg-substep2b/SITREP-pair-planner-20260922-170119.md`)

Master disposed of the c6b `open.hpp` deviation: `T_C6B_DISPOSITION: accept-as-recorded cd51937… src/core/open/open.hpp`, verified at master against A11 rev11's failed-row composition, with rev25's record correction called the right repair.
Two conditions came with it: (1) `RepoOutcomeRow::kind` and `::detail` are named in the GO's review asks and in m-3's byte review of H — this seat writes that GO at Task 10; (2) from impl-6 on, every implementer return enumerates each commit's paths against its task's Files line — carried on the impl-6 token as master's condition citing 042625, never as a plan gate invented here.
Master also took the INDEX register as a relay-engine housekeeping item for the operator; it blocks nothing.

The digest word then went up with the five T-ORACLE field lines at `f2b2943f…`; the three owner objects re-hash unchanged at pdc HEAD 06e735ee, and only the plan digest moves from 193745's.
The T-ORACLE prefix was run first on scratch clones against a synthetic carry at the new digest: PASS with its receipt; a two-seat TO line and a rev23-digest locator each STOPped with no receipt.
TOOLING CHANGE, disclosed on the relay: the 2.9.2 kit is no longer installed on this host (only 2.9.3 remains, for both the claude and codex caches), so this seat's standing dual-kit pre-lint is 2.9.3-only from this relay on; no 2.9.2 pass is claimed.

## R46 — master's carry at rev25; `t-oracle.txt` rewritten; impl-6 issued with c6p released (2026-09-22 17:10–17:3x; master `intg-2b-wiring-act/PLAN-master-planner-20260922-171038.md`; token `intg-substep2b/IMPL-pair-planner-20260922-171639.md`)

Master carried the five T-ORACLE fields at `f2b2943f…` (171038, sha256 `45f69b17…`, tracked and clean at pdc HEAD 939c6274) and took the 2.9.3-only lint disclosure for the record: 2.9.3 is the linter of record for this commission and no gate reads a 2.9.2 pass.
Each field was checked against the files before use. `t-oracle.txt` in `s2b-runners-QzzQ11` was preserved as `t-oracle.prev-20260922-171228.txt` (`920a64cd…`) and rewritten (`194bfbbe…`, one `plan_sha256=` line).
The prefix run from the candidate worktree against the real file passed, naming the new carry and digest; Step 0′ walked on a scratch mirror published with 19 carried lines (`red1-owner-words.txt` joins), every carried file byte-equal, the prefix passing from the new directory, and the stale / same-lock / token-form controls stopping with nothing left behind.

`intg-substep2b-impl-6` was issued (PARENT `intg-substep2b-plan-review-24`; 47-path SCOPE_DIFF all-in; the mini-root lineage walk showing only the four known mini-root classes).
It resumes at Task 6d: c6p is RELEASED because T-RED1 is satisfied — the gate file is on disk and its gate ran pre and post on the real carriers at this seat — then c7, c8 and Tasks 9–11.
Master's two T-C6B conditions travel on the token's face as HIS, citing 042625: the two `RepoOutcomeRow` fields are named in the GO's asks and m-3's byte review of H, and every return from this token on enumerates each commit's paths against its task's Files line.

## R47 — the impl-6 return is a STOP UP, VERIFIED: Task 6d's c6p contract is self-contradictory (my rev22 defect); one containment cell routed to m-4 through master (2026-09-22 18:13 return, 20:29 routed; `intg-substep2b/IMPL-pair-implementer-20260922-181342.md` → `intg-substep2b/SITREP-pair-planner-20260922-202943.md`)

The implementer returned impl-6 with NOTHING committed: the Step 0 owner-word gate ran `MODE=pre` before the first c6p test byte, the TDD candidate was written to the eight authorized Task 6d paths, the offline arm of P2 went red at exit 3 (`MemberPathUnsafe` at `payload/lib/sub/x.log`), and the seat STOPPED UP rather than invent an offline exception.
Verified here by execution, not from the return: the candidate head is UNCHANGED at `e5afe9d…` (so c6p, c7, c8 and Tasks 9–11 are all unstarted), `git status --porcelain` lists exactly the eight authorized paths as modified with nothing staged and no non-ignored untracked path, `git diff --check` is rc 0; the pre-gate receipt's three carriers were RE-HASHED against the live files (`75c132b7…`, `3729bb4c…`, `936a8d27…`, all equal); and the hash the return quotes is `c6p-mutants.txt` at `3d5010a5…`, holding the Step 2 named-mutant run.
THE CONTRADICTION, derived at rev25's own bytes: Step 1 (b) pins `payload/lib/sub/x.log` as a member and `payload/lib/sub` as ABSENT (a tracked ancestor); P2 is P1's `--offline` twin and demands the same penumbra fidelity with zero git; Step 3 refuses an absent ancestor BELOW the row relpath with `MemberPathUnsafe`, which is fatal to the whole open.
Offline the row is never materialized — `open.cpp`'s offline-pointer branch writes a report row and the `.biv` bundle and nothing at the relpath — so `lib/sub` can come from neither the archive nor git, and P2 is unsatisfiable as written.
TWO CORRECTIONS carried against the return and against me: the prohibition is NOT rev25's — it is byte-identical at rev22 `9d2ba96`, rev23, rev24 and rev25 and absent before, so it entered with Task 6d itself, PREDATES both rounds of owner words, and survived four implementer exact-hash reviews and my own walks; and the blast radius is not P2 but every non-materialized row — the offline pointer, `shallow_pointer`, `payload_only_unborn` (`restore.cpp:424-457`) and the url-divergence-refused row, whose loop records the refusal, pushes the row, continues, and then runs the placement.
It is a PRODUCT defect in my rule, not a fixture inconsistency: the trigger is the commonest penumbra shape there is, an ignored file beside a tracked file in one directory (the plan's own root fixture, `src/a.o` next to `src/a.c`, survives only because P4 opens `--network`), so a correct product-packed image would abort the entire open and retain the partial.
WHAT WAS DERIVED rather than asked: m-1's confirmed RECURSIVE directory rule makes a directory holding a tracked descendant never a member, and git creates precisely those directories — so the refusal is UNREACHABLE for a materialized row and fires on every image of that shape for a non-materialized one; against that, m-3's V1-2 requires a non-materialized row's members to land at its relpath with no git.
Both escapes are therefore closed already: archiving `payload/lib/sub` is barred by m-1's rule (and by rev25's own final-path ENOENT clause, which would break P1 where the clone has made `lib/sub`), and accepting the abort is barred by V1-2 — the only arm left creates the missing ancestor.
THE ONE CELL routed to master for m-4 (V1-3 is m-4's surface; m-3 and m-1 confirming): V1-3 as sealed names two refusals only, `on a symlink or non-directory`, and an absent ancestor is neither — may the deferred writer CREATE a missing ancestor below a row's relpath, one component at a time, each after its parent is `lstat`-verified a real directory, never `create_directories`, never stamped, with the `.git`-segment, `.biv`-prefix, symlink/non-directory and final-path-ENOENT refusals unchanged and evaluated first?
Arm A (unconditional) is RECOMMENDED over arm A-prime (restricted to non-materialized rows), because A-prime's distinguishing cell is unreachable by any fixture a clean pack can produce, so no mutant can validate it — an untestable branch in a security-relevant writer.
On the word: rev26 touches Task 6d only (Step 3's sentence, a new Step 4 mutant, the Step 0 gate gains a FOURTH carrier field, one acceptance line, the bullet), then the fresh five-field T-ORACLE carry at the rev26 digest, the `t-oracle.txt` rewrite with the rev25 file preserved, the implementer's exact-hash review, and `intg-substep2b-impl-7`.
Plan rev25 stays UNTOUCHED until the word; the candidate's eight retained paths are the implementer's, neither committed nor reverted by this seat; master's 042625 conditions ride forward unchanged; the release hold is ABSOLUTE.

## R48 — master takes the STOP and routes three owner asks; my runners-pointer correction; m-1 answers `C6P_MEMBER_SET: stop` with a second, larger red (2026-09-22 21:54 master; 22:50/22:51 owners; 22:56 my correction)

Master's `intg-2b-wiring-act/PLAN-master-planner-20260922-215436.md` (`f0d9acf5…`) TAKES the STOP, re-derives it at his own bytes — the candidate at `e5afe9d` with the eight authorized paths, the clause byte-present at rev22 `9d2ba96` and absent earlier, four non-materializing row kinds, V1-3's two refusals — and calls the decision to return c6p uncommitted the right one.
He routed three asks, each to be answered as ONE whole line: `C6P_ABSENT_ANCESTOR: <arm-a|arm-a-prime|stop>` to m-4 (`…-215321.md`, with arm A recommended in master's own voice), `C6P_V1_READING: <confirm|stop>` to m-3 (`…-215323.md`), `C6P_MEMBER_SET: <unchanged|stop>` to m-1 (`…-215326.md`); rev26 binds those three field names in the Step 0 gate, written ONLY from his single carry citing all three. Registered at master as R-4.69, owner-at-open m-4.
MY CORRECTION, filed as `intg-substep2b/SITREP-pair-planner-20260922-225657.md`: the canonical runners is NOT `s2b-runners-QzzQ11`. impl-6's Step 0 prime published `s2b-runners-P7xJDh` at 17:40 before it stopped — `runners-dir.txt` names it, `previous-runners.txt` reads QzzQ11, `carried.sha256` holds 19 lines, and the gate files carried forward byte-equal (`t-oracle.txt` `194bfbbe…`, `red1-owner-words.txt` `5431f3d1…`, `m3-harness-patch.txt` `86d8d7e3…`); QzzQ11 is intact and nothing was lost.
My 202943 named the superseded directory and master's 215436 took the name from me, so the error is mine in two filed relays; had the rev26 `t-oracle.txt` rewrite gone to QzzQ11, impl-7's gate would have read the canonical P7xJDh copy still bound to the rev25 digest.
The cause is owned: the implementer's return said Step 0 prime published the canonical runners and I verified the STOP's substance without chasing the pointer. The rule from here is that `$EVID/runners-dir.txt` is read as a command before every gate-file write, and I asked master's carry not to name a runners directory at all.
Master's four cites were re-verified exact at the committed head (`open.cpp:794-800`, `:850-856`, `restore.cpp:448-457`); my earlier numbers differed only because I read the worktree carrying the uncommitted candidate.
ONE MEASUREMENT offered because it sizes my fixtures: a DECLINED network consent is not a third branch — `stage` is `(offline || repos.empty()) ? nullopt : …` at `open.cpp:889-891` and the `offline` argument is `impl->offline || decisions.offline` at `:1168`, so a declined consent enters the SAME offline-pointer branch at `:794` as `--offline`, and `:850`'s url-divergence row is the only typed refusal that pushes a row and continues (its sibling `else` at `:856` is fatal).
TWO OWNER ANSWERS LANDED, both addressed to master and NOT acted on at this seat: m-3 `…/DESIGN-planner-20260922-225041.md` `C6P_V1_READING: confirm` (V1-2 licenses no git at a non-materialized row; V1-3 refuses a symlink or an existing non-directory only; the absent-ancestor clause is the plan's own from rev22; creation is m-4's, and the relpath itself is also absent), and m-1 `…/DESIGN-planner-20260922-225134.md` **`C6P_MEMBER_SET: stop`**.
m-1's stop carries a SECOND red, larger than mine and reproduced at their seat: for the two PAYLOAD-ONLY row kinds the sealed text (Addendum-N N-R3/N-R4 on the shallow cell; Addendum-A §A6 with H on the zero-ref unborn repo) archives the WHOLE working tree, but c5 excludes every discovered boundary unconditionally, so a depth-1 clone and a fresh `git init` packed rc 0 SILENT with the image holding neither tree and the open restoring nothing of either repository.
m-1 also corrects their own 200936 rule as wrong for those rows: the corrected member set is (1) payload-only rows (`shallow`, or H's zero-ref unborn — both `!restore_invokes_git`) scanned like residue, directories included, minus `.bivignore`, deeper rows' subtrees, `.git` and `.biv`, restored as ordinary payload with zero git; (2) git-capable rows keep 200936's recursive rule unchanged, so the rejected escape route stays closed.
Their cure (1) removes the two engine-returned pointer rows (`restore.cpp:448-457`) from the containment cell, leaving m-4 the offline-pointer branch and the url-divergence row — the two this seat measured.
DISCLOSED to master in the same relay: rev26 will NOT be `Task 6d only` under m-1's stop (the corrected member set is a new pack obligation, plausibly its own commit); the gate will bind the three field names in the `RED1_ROOT_ROW` pattern from the ANSWER relays his carry cites; I intend to rewrite the single existing c6p owner-words gate file with the current file preserved as a dated prev rather than add a second file, because a new filename would join the Step 0 prime carried list and move that block's pinned sha; and I will not keep a gate binding `RED1_PENUMBRA_DIRS` as a rule for EVERY row when its own owner has just narrowed it to git-capable rows.
Nothing committed at the candidate, plan rev25 `f2b2943f…` unmodified, no gate file written, m-4's word outstanding; the release hold is ABSOLUTE.

## R49 — master carries T-C6P (011148); rev26 cut and sent for exact-hash review (2026-09-23 01:11 carry; 02:03 PLAN `intg-substep2b/PLAN-pair-planner-20260923-020311.md`, plan-27; artifact `fcbbabd52f8d890131cf6fbc890e9ad29368b7c2360dc33682e4c49104e036a7` at 824e062)

Master's `intg-2b-wiring-act/PLAN-master-planner-20260923-011148.md` (`5181d841…`) carried all three words in one relay: m-4 `C6P_ABSENT_ANCESTOR: arm-a` (`…-225418.md`, `b35b2043…`: AA-1 the one-component primitive, AA-2 refusals before the walk and existing ancestors lstat'd before any creation, AA-3 the precondition, AA-4 five witnesses), m-3 `C6P_V1_READING: confirm` (`…-225041.md`, `8472103d…`: V1-3 refuses a symlink or an EXISTING non-directory only; at a non-materialized row the relpath itself is absent too), m-1 `C6P_MEMBER_SET: stop` (`…-225134.md`, `979b64f5…`: R-4.70).
Master ruled that m-4's requirement word on m-3's first-pass observation rides c6p — one dot-git predicate, two call sites — and verified my runners correction at his seat; his relays will not name a runners directory again.
Each word was verified here before use: tracked and unmodified, FROM its owner, the word a whole line exactly once, no rival line of its field. My first field grep used `C6P_[A-Z_]+` and reported m-3's word ABSENT; the field is `C6P_V1_READING`, which carries a digit — the false absence was my instrument's, so the gate matches literal field names and the walk includes a digit-field cardinality case.
F-C6P-1, m-4's live finding, stands as the precondition: the impl-6 candidate's `.git` refusal is byte-exact, and on macOS's case-insensitive volume `payload/<row>/.GIT/hooks/<name>` under a materialized row walks into the restored `.git` and is written; the absent-ancestor refusal had been masking it below a row.
R-4.70 was reproduced WHOLE at this seat from a clean `biv` built from a `git archive` of `e5afe9d`: pack rc 0, stderr empty, no warnings or advisories, both rows recorded, the members `manifest.json`, `checksums.json`, `payload/README.md` only; open with and without `--offline` rc 0, restoring README only, zero git spawns.
The premise that c6q is complete at its own head rests on READING, not execution: `restore_entry` returns a payload-only row right after `validate_entry`, which validates fields only (`restore.cpp:95-135`, `:448-457`); a hand-built image could not be made byte-faithful to biv's extent hashes (the extent covers biv's own PAX-plus-header layout), so the attempt was abandoned rather than reimplementing the writer.
Two further premises were measured: classify records `penumbra_paths` for a shallow row (its shallow branch calls `record_penumbra` and returns), so without an explicit skip c6p would archive each ignored file of a payload-only row TWICE; and the scan's `.git` test raises `UnclaimedGitEntry` for any `.git` whose directory is not excluded, so c6q needs a claimed-marker notion, not merely a smaller exclusion list.
The partition (`restore_invokes_git`) reads `bundle` and `eligibility`, set only by capture and `run_eligibility`, so c6q walks each payload-only row with a new `scan_subtree` AFTER capture and leaves the residue scan byte-unchanged — moving the whole scan after capture was rejected because it would reorder errors on every failing pack and put network probes before a scan failure.
The predicate was transcribed from git `3bc0341126508f78f5869cbfc0005e987efdf0c7`, downloaded and re-downloaded at that pinned commit (byte-equal): `read-cache.c` `verify_dotfile` (case-insensitive `.git` on every platform), `utf8.c` `next_hfs_char` (sixteen ignorable code points) with `is_hfs_dot_generic`, `path.c` `is_ntfs_dotgit` (`.git` or `git~1`, then dots or spaces, then end or `:`). Two transcriptions are flagged for m-4's byte review rather than decided silently: the `:` stop, which is git's but not in m-4's words, and `biv~1` as the `.biv` analogue of `git~1`.
TWO DEFECTS OF MINE found while cutting rev26, both folded: rev25 declared `owning_row` and `row_relpaths` file-local while demanding behavioural cases, which left the implementer only a source-text search (it passes whatever the function computes) — rev26 declares them and the predicates in `open.hpp`'s `detail` namespace so the tests call them; and Task 7's N (a) asserted the shallow row's outcome and zero git but never its working tree, so it would have passed with the whole tree dropped, which is exactly what c5 does.
A third, of the same family: my rev25 carrier's face counts (placeholders 0, token phrases 0, census alternation 0) had been TYPED by the generator, not run. Run now with explicit commands and must-be-YES controls: placeholders first read 6, all six being `mktemp -d …-XXXXXX` templates identical in rev25, so the pattern was narrowed to exclude six-X templates (control still fires) and reads 0 on both revisions; token phrases 0; census alternation 0 using the `ALT=` line of the plan's own `census_population.sh` BLOCK.
The widening swept every prohibition it could contradict: the "repo subtree is excluded WHOLE" guard and the scan file-structure bullet were amended; the E2/E5 census pattern does not include `restore_invokes_git` (and c4b already calls it at `open.cpp:794`), so the new calls move no census; the BLOCK census is 22 with every digest byte-identical to rev25 and `resume.sh` still `639c72cb…`, so Step 0 prime's carried list does not move.
rev26: T-C6P; NEW Task 6q (c6q, R-4.70) after c6m and before c6p; Task 6d's seven-carrier gate with rev26-named receipts (impl-6's `c6p-owner-words.pre.txt` is never overwritten), the four-stage walk under arm A, behavioural `detail` tests with the predicate tables, W2/W3/W5/FP1/FP2/H6b, M3 redefined for arm A (the ancestor check following links) and M6′/M8–M11, AA-1's race conditions stated as NOT witnessed; Task 7 N (a) with the tree assertion and H at product scope; Task 6c's `biv open <image> <dest>` corrected to `--dest` (the CLI refuses a positional destination with `too-many-args`, found while reproducing).
The gate was walked YES pre and post on the REAL carriers from the candidate worktree (receipt nine lines, the digests equal to the ones verified independently, the candidate's eight retained paths untouched) and on a synthetic pdc, plus 24 NO cases each stopping on exactly its own token; the Step 5 receipt guard was walked YES and two NO, and bash 5.3's `-nt` was confirmed to compare nanoseconds.
Registered in Out of scope and to go to master on the digest word, not folded: m-4's TOCTOU observation, nested payload-only rows (unreachable at 2b), and an image whose only rows are payload-only failing at `Git::resolve` on a host with no `git` on `PATH` although no git would run.
NEXT: the implementer's exact-hash review → my digest word TO master (with the git-less observation and the two flags) → master's fresh five-field carry at `fcbbabd5…` → the `t-oracle.txt` rewrite in the directory `$EVID/runners-dir.txt` names at that moment and the `red1-owner-words.txt` rewrite from 011148 (prev preserved) → `intg-substep2b-impl-7`. Nothing committed at the candidate; the release hold is ABSOLUTE.

## R50 — rev26 must-revised on MUST-2B-47 (Task 6q's root row); rev27 cut and sent (2026-09-23 02:38 review `intg-substep2b/PLAN-REVIEW-pair-implementer-20260923-023855.md`; 02:59 PLAN `intg-substep2b/PLAN-pair-planner-20260923-025902.md`, plan-28; artifact `57fd97f9fd0a72097f6c0c6dae3d93278fe3444eb8add5be98317f44e73fa2c4` at e9a1bf5)

The implementer must-revised rev26 at `fcbbabd5…` on ONE finding, MUST-2B-47, and confirmed the rest positively: the block manifest byte-identical, the seven-carrier gate passing pre and post with four controls stopping, the owner carriers bound, and the predicate transcription agreeing with git `3bc0341…` including the `:` stop.
MUST-2B-47, verified at `e5afe9d` and correct: Task 6q applied `scan_subtree` to EVERY payload-only row and required it to emit the row directory itself, but a root row canonicalizes to `""` (`scan.cpp:202-205`), so the plan mandated the bare member `payload/`, which the open-side path refuses as an empty remainder (`open.cpp:520-523`). The root form had no fixture, and Mq3 would have pressed an implementation toward the invalid node. The defect is mine: I wrote Task 6q from m-1's non-root fixture and never asked what the rule does at `.`.
One fact further, measured here: when the root boundary is claimed the residue `scan()` returns EMPTY before walking (`scan.cpp:278`), so from the clean `e5afe9d` build a workspace that is itself a depth-1 clone (plus an untracked file) and one that is itself a fresh `git init` (holding an untracked file) each packed rc 0, empty stderr, no warnings, with ONLY `manifest.json` and `checksums.json` — rows `.` shallow and `.` unborn. That is R-4.70's worst form: the whole workspace lost silently. It goes to master on the digest word.
rev27, Task 6q only: `scan_subtree(…, "", …)` emits no node for the root itself while a non-root call still emits its row directory first; a ROOT unit case; ROOT-SHALLOW and ROOT-UNBORN exact member multisets with no bare `payload/`; their round trips with and without `--offline` (the destination root excluded from fidelity, `.git` absent, zero git); Step 2's measured RED shape; Mq4 (the root exception deleted) with Mq3 kept for the non-root node; evidence row R2-Q; acceptance 12; the history bullet.
Task 6d and Step 0 prime compared section by section: byte-identical to rev26; the BLOCK census 22 unchanged; placeholders, token phrases and census alternation all 0 by their commands.
NEXT: the implementer's exact-hash review of `57fd97f9…` → my digest word TO master (with R-4.70's root form, the git-less observation and the two transcription flags) → master's fresh five-field carry → the `t-oracle.txt` rewrite in the directory the pointer names and the gate-file rewrite from 011148 → `intg-substep2b-impl-7`. The release hold is ABSOLUTE.

## R51 — rev27 APPROVED (030843); the digest word TO master (2026-09-23 03:08 approve `intg-substep2b/PLAN-REVIEW-pair-implementer-20260923-030843.md`, plan-review-26; 03:16 SITREP `intg-substep2b/SITREP-pair-planner-20260923-031601.md`)

The implementer approved rev27 at the exact digest `57fd97f9fd0a72097f6c0c6dae3d93278fe3444eb8add5be98317f44e73fa2c4` (commit e9a1bf5, 3088 lines): the commit confined to Task 6q, evidence row R2-Q, acceptance 12 and the history bullet; the block list byte-identical (22); Task 6d and Step 0 prime byte-identical by section digest; MUST-2B-47 closed (no root node, root children supplied once, ROOT unit/pack/round-trip cases, Mq4 discriminating with Mq3 leaving the root cases green); the four T-C6P carriers unmodified at their digests.
The digest word carries the five T-ORACLE field lines with only `T_ORACLE_PLAN_SHA256:` moving from 171038; the three owner objects were re-hashed at pdc HEAD de20f4f3, tracked and unmodified, byte-identical.
The T-ORACLE prefix, extracted from rev27 and byte-identical to rev25's walk copy, was walked in scratch clones on a synthetic committed carry at the new digest: YES rc 0 with its receipt; a two-seat `TO` stops `carry-to`; the rev26-digest locator stops `plan-sha-mismatch-live`; neither writes a receipt.
A first walk was INVALID and is disclosed, not counted: my fixture builder used a BSD-`sed` `\|` alternation, which matches nothing, so the fixture lost its two `m1_` lines and all three runs stopped on `field-m1_request-count-0` — a harness fault, recognised before reading any verdict; the fixture was rebuilt with `grep -E` and all three re-run.
One sentence of the draft was wrong and was corrected before submit: it said c6p adds `src/core/open/open.hpp` to the SCOPE_DIFF, but every c6q and c6p path, `open.hpp` included, is already among impl-6's 47 (checked against the filed 171639).
Three items went to master for the record, none gating the carry: R-4.70's root form measured as a total silent loss; the git-on-PATH observation; the two transcriptions (`:` stop, `biv~1`) for m-4's byte review. The carry was asked NOT to name a runners directory.
NEXT: master's fresh carry at `57fd97f9…` → read the pointer → preserve and rewrite `t-oracle.txt` and `red1-owner-words.txt` (seven lines from 011148) → both gates from the candidate on the real files with a scratch EVID → Step 0′ walk → `intg-substep2b-impl-7` (PARENT 030843). The release hold is ABSOLUTE.

## R52 — master's carry at rev27 (033242); both gate files rewritten; impl-7 issued (2026-09-23 03:32 carry `intg-2b-wiring-act/PLAN-master-planner-20260923-033242.md`; 04:06 token `intg-substep2b/IMPL-pair-planner-20260923-040651.md`, sha256 `5594a7f62b845118ed41c1563d220b5de554a5144a500738ac0d1e7b24eb2c7e`)

Master carried the five T-ORACLE fields at `57fd97f9…` (033242, sha256 `e75d86be…`, tracked and clean), each field equal to the digest word's; he named no runners directory, took R-4.70's root form into the registry (reproduced at his seat), registered the git-on-PATH observation as R-4.71 and routed it to m-1 (033244), and flagged the two transcriptions for m-4's byte review at H.
m-1 answered R-4.71 at `…/DESIGN-planner-20260923-040154.md` (TO master): arm (a), an engine byte — a Git-free function for the no-git outcome that `restore_entry`'s guard calls, the orchestrator resolving git only for git-capable rows — and stated explicitly that it is NOT folded into rev27 and does NOT touch the running lane; impl-7 proceeds as carried, and R-4.71 lands in a later act with its own fence. Cited on the token.
The pointer was read as its own command: `s2b-runners-P7xJDh`. `t-oracle.txt` was preserved as `t-oracle.prev-20260923-040132.txt` (`194bfbbe…`) and rewritten to four lines naming carry 033242 and the rev27 digest (`65c80bbf9994adf8…`, 0400); `red1-owner-words.txt` was preserved as `red1-owner-words.prev-20260923-040132.txt` (`5431f3d1…`) and rewritten to the seven lines of 211701 + 011148 (`14c25d2c0ce48eeb…`, 0444); each rewrite atomic, each prev verified byte-equal to the file it replaced.
Both consuming gates ran from the candidate worktree against the REAL files with a scratch EVID: the T-ORACLE prefix `t-oracle OK` rc 0 (receipt naming 033242 and the rev27 digest), and Task 6d's Step 0 gate — extracted from rev27, byte-identical to the block walked at rev26 — PASS in `MODE=pre` and `MODE=post`; the candidate kept exactly its eight retained paths.
Step 0 prime was walked on a scratch mirror of P7xJDh with `resume.sh` extracted from rev27 (`639c72cb…`, identical to rev25's walk copy): the positive published with 19 carried lines, lock `57fd97f9…`, token `intg-substep2b-impl-7`, every carried file byte-equal (both rewritten gate files included), and BOTH gates passed from the new directory; the rev25 locator stopped `t-oracle-stale`, the same lock `same-lock`, an impl-6 id `token-form`, none creating a directory; nothing left in the evidence root; the real pointer untouched.
The token was built from the filed impl-6 token. Two stale carry-overs in impl-6 were found and corrected rather than inherited: its SCOPE_ROW_EVIDENCE still listed c4b and c6b as "EXPECTED under this token" though both landed under impl-5, and its runners section ended with an impl-5 sentence saying `red1-owner-words.txt` did not exist, contradicting its own section above. impl-7's 47 rows were re-derived from `git log B..e5afe9d` (each path with the commits that landed it, and the c6q / c6p / c7 / c8 / c9 expectation stated per path); the SCOPE_DIFF is the same 47 paths as impl-6.
The lineage (token → plan-review-26 → plan-28) was walked on a three-relay mini-root with the 2.9.3 linter: the same four error classes impl-6's mini-root produced (artifacts of an isolated root with no grant relays and outside git) and nothing else; the token lints rc 0 on its own, one bare token line, 47 rows.
impl-7's order: Step 0 prime ONCE → Task 6q (c6q) → Task 6d (c6p, the seven-carrier gate pre/post, receipts `c6p-owner-words.rev26.*`) → Task 7 → Task 8 → Tasks 9–11; the implementer's eight retained paths are theirs, but no c6p byte may ride c6q and the draft is reworked to rev27 before it is committed. Master's 042625 conditions ride as his. The release hold is ABSOLUTE.

## R53 — impl-7 returned: c6q and c6p LANDED and verified; c7 STOPPED; the STOP is larger than returned — at product scope neither verb can see a URL divergence (2026-09-23 13:34 return `intg-substep2b/IMPL-pair-implementer-20260923-133444.md`; 13:49 SITREP `intg-substep2b/SITREP-pair-planner-20260923-134901.md`)

Under impl-7 the implementer ran Step 0 prime once (runners `s2b-runners-4BSBek`, previous P7xJDh, 19 carried, lock `57fd97f9…`, token impl-7), committed c6q `fe2053ff…` (exactly Task 6q's six paths) and c6p `534decb9…` (exactly Task 6d's nine), parked impl-6's retained draft in a stash applied to neither, and reached c7's real-CLI red phase, where the plan's two named divergence fixtures exit 0 instead of refusing. The return enumerates paths against Files lines exactly, as master's 042625 condition (2) requires.
VERIFIED HERE: the path sets by `git show --name-only`; the evidence log `c7-plan-fixture-red.log` at its quoted digest (7 cases, 2 failed); and the landed code rebuilt from a `git archive` of `534decb`. ctest passed every test but `harness-e2`, which failed on MY environment (the system Python lacks `zstandard`) — an invalid run, recognised as such before reading it; re-run from a venv built from `harness/requirements.lock` it exits 0 (18 rows: 12 passed, 0 failed, 0 invalid, 6 declared pending), and `[c6q]`, `[c6p]`, `[c6m]` pass (926 / 1303 / 36 assertions).
THE PACK HALF, reproduced from my clean `e5afe9d` build: the engine records each remote's URL with `git remote get-url` (`classify.cpp:318-326`; no commit of this lane touches that file), and on git 2.50.1 that command returns the URL AFTER `insteadOf` while `git config --get remote.origin.url` returns the configured one. A repo-LOCAL rewrite packs rc 0 and the manifest records `origin` as the rewritten `effective.git`; the SAME rewrite in GLOBAL config gives the identical result; the no-rewrite control probes `remote.git`. Sealed M-R1 makes the comparator's inputs (requested-as-passed, effective-as-resolved) and FX-M-1 (h) requires a local-only rewrite to be detected; so M (h) fails at product scope, no rewrite at any scope is detected at pack, and the image carries the redirected endpoint — M-R2's "false silence".
THE OPEN HALF: restore sets `isolate_global_config` (`git_exec.cpp:264` → `GIT_CONFIG_GLOBAL=/dev/null`, `git.cpp:132-134`), system config is always off, and a clone runs where no repository config exists, so no user configuration can produce a restore-site divergence. My plan had recorded this for Task 4 at rev13 (line 1065) yet mandated the impossible temp-HOME fixture in Task 7 (line 1535) — my defect since rev13.
CONSEQUENCE: every Task 7 leg needing a divergence is unreachable at product scope (M (a), (b)/(i)/(j), (d) both verbs, (g)/E3 both grains, (h); the DIVERGE sub-arms of M (e)(f)(l)(m)(n)(o), whose SILENT sub-arms would pass for the wrong reason; a6·1/2/5/6/7/12/13/16-divergence; a7·1–5; a8·5 arms A/B1; a8·6). The consent fabric is exercised today only by the hand-built and shim tests of Tasks 2–4.
ROUTED to master: Cell 1 (the pack-side carrier: an engine byte in `classify.cpp`, the fix, what the manifest records as `remotes[].url`, and where it lands) to m-1 with m-4 — my recommendation IN this lane before c7, because c7 is M's product-scope witness, stated against master's 040728 scheduling R-4.71 after 2b (R-4.71 has no 2b witness; Cell 1 does), with the fallback that Task 7 REGISTERS the M legs as unwitnessed-pending if they defer; Cell 2 (open-side reachability under the isolation) to m-3 and m-4 with m-1 — my recommendation an isolation witness at product scope plus the labelled Task-4 shim for the machinery, never claimed as product detection. The implementer's third question answered: a shim proves machinery, not detection.
Newer relays opened before submit: master 040728 (R-4.71 as its own act after 2b, before the release gate) and the implementer's BOOT 133415. c6q/c6p stay local and unpushed; c7, c8, Tasks 9–11 held; rev28 follows the owner words. Severity recorded for master's registry: Cell 1 is live in code landed on main at B (unreleased under the hold). The release hold is ABSOLUTE.

## R54 — master takes the c7 STOP as R-4.72 and routes four words; the cited ask paths corrected (2026-09-23 14:02 `intg-2b-wiring-act/PLAN-master-planner-20260923-140251.md`; 14:08 SITREP `intg-substep2b/SITREP-pair-planner-20260923-140840.md`)

Master reproduced the silent rewrite at his own seat at both config scopes with a control, read `classify.cpp` and the isolation at the bytes, accepted c6q / c6p as sound on my evidence (including the disclosed invalid first `harness-e2` run), registered R-4.72 (live in code on `origin/main`, unreleased under the hold; my plan-fixture defect registered with it, standing since rev13), and backed in-lane placement in his own voice.
Four words asked, each one whole line: `R472_PLACEMENT: <in-lane|later-act>` and `R472_MANIFEST_URL: <configured|effective>` to m-1; `R472_ISOLATION: <stands|revisit>` to m-4; `R472_OPEN_WITNESS: <isolation-plus-shim|other>` to m-3. If m-1 defers, Task 7 REGISTERS the M legs as unwitnessed-pending rather than claiming them. Not asked: A6's PROMPT D text; R-4.71's failure surface.
RECORD CORRECTION, measured: the three ask paths 140251 cites (…140059 / 140200 / 140201) do not exist; the filed asks are …140244 (m-1), …140247 (m-4), …140249 (m-3), each checked by its `TO:` line and its field names. My gate binds the answer relays through the carry, so nothing breaks, but the record is corrected on the filed SITREP.
Gate design stated to master before the carry: a Task 7 Step 0 gate over a NEW file `r472-owner-words.txt` (carry + m-1 + m-4 + m-3, five whole-line words), new rather than an extension of `red1-owner-words.txt` because it guards c7 and any engine task, not the landed c6p; it joins Step 0 prime's carried list, moving `resume.sh`'s pinned digest, to be re-walked before the review. Owner-independent Task 7 corrections (the impossible temp-HOME restore fixture removed) are prepared; nothing is filed before the carry. The release hold is ABSOLUTE.

## R55 — master carries three R-4.72 words (142025); one rev28 promised on the fifth; m-4 answers `ceiling` before the carry (2026-09-23 14:20 `intg-2b-wiring-act/PLAN-master-planner-20260923-142025.md`; 14:49 SITREP `intg-substep2b/SITREP-pair-planner-20260923-144923.md`)

Master carried m-1 `…/DESIGN-planner-20260923-140916.md` (`R472_PLACEMENT: in-lane`, `R472_MANIFEST_URL: configured`), m-4 `…-140901.md` (`R472_ISOLATION: stands`) and m-3 `…-141015.md` (`R472_OPEN_WITNESS: other`); each verified here with the gate's predicates (tracked, clean, FROM the owner, one whole line, no rival line) and the carry cites all three.
m-1's fence, read verbatim: c1d = ONE engine-only commit on `src/core/repo/classify.cpp` + `tests/test_repo_engine.cpp`; both capture sites (`:258` unborn-with-refs, `:319` born) read `git config --get-all remote.<name>.url` and take the FIRST line; `config --get` (last value) and today's `remote get-url` are the named mutants; W-U1..W-U5 at the engine seat; the existing typed error, no new kind; m-1 re-ruled its own 042531 history-order form so c1d may follow c4–c6. R-4.73 (configured-URL shorthand cost) is registered and gates nothing here.
m-4's conditions carried: the dot-git refusal at both writers named in the same witness family; the two-part shape where it applies; M's open-grain gate stays wired as fail-safe; E3 rebound to the PACK verb. SR-URL-5 routed as its own requirement act.
m-3 overturned master's 140249 premise: open-grain divergence IS product-reachable through an ENCLOSING repository's config (git's upward discovery; the non-root clone runs at the partial root; no `GIT_CEILING_DIRECTORIES` under `src`), verified at master. Master held the open half on one more word to m-4 (`R472_ENCLOSING_REPO`, ask …142023).
The six plan places m-1's re-ruling obliges me to amend were located: the VETO 9 MECHANICAL and ENGINE BYTES constraints, the ZERO BYTES line, acceptance 1, Out of scope, and Task 9 Step 2's RUN-block runner, which STOPs on any engine commit after the third; the SCOPE_DIFF grows 47 → 48. I told master I will cut ONE rev28, not a pack-only one, and offered a split if he prefers.
PROCESS BREACH, mine: the upstream listing and the submit ran in ONE command, so the listing showed m-4's `…/DESIGN-planner-20260923-144917.md` only after my SITREP was already filed. Opened immediately afterwards: `R472_ENCLOSING_REPO: ceiling` (TO master; EC-1 — no restore-site call of any class reads outside the partial, a canonical-parent ceiling on m-1's mechanics; EC-2 witnesses). My filed relay stated both outcomes conditionally, so nothing in it is false, but the sweep existed to prevent exactly this ordering. From here the listing is its own command and the submit a separate one.
`ceiling` means the open half needs more words before rev28 can be cut: m-1's mechanics and placement for the ceiling (an engine byte in the restore path), and m-3's re-worded witness cell. Waiting on master's carry. c6q and c6p stay local and unpushed; c7 onward held. The release hold is ABSOLUTE.

## R56 — master confirms ONE cut and holds it for two more words; the cited-path defect recurs (2026-09-23 14:55 `intg-2b-wiring-act/PLAN-master-planner-20260923-145548.md`; 15:06 SITREP `intg-substep2b/SITREP-pair-planner-20260923-150636.md`)

Master confirmed one rev28, no split, and held it for his ONE carry of `R472_CEILING_PLACEMENT` (m-1: the ceiling rides with c1d, takes its own in-lane engine commit before c7, or defers to the R-4.71 act; master's own reading is own-commit-in-lane) and `R472_OPEN_WITNESS_REWORD` (m-3). He verified m-4's `ceiling` at his seat (with `GIT_CEILING_DIRECTORIES` at the canonical parent, `ls-remote --get-url` returns the recorded URL and `rev-parse --show-toplevel` no longer finds the enclosing repository).
Consequences taken for rev28: m-3's W-1 loses its product trigger, so the open-grain prompt, refusal, row and accept-flag legs fall back to the labelled shim; m-3's fixture becomes the ceiling's RED witness (NAMED MUTANT: ceiling removed ⇒ the prompt returns); EC-2 adds three legs (the enclosing `.git` byte-unchanged by checksum; a SYMLINKED destination still bounded; the no-enclosing control); EC-4 names the ceiling and the dot-git refusal at both writers as ONE property in one witness family. My six plan changes were accepted as consequences; the veto-9 arm's wording is held, because a ceiling commit of its own would make it admit a sixth engine commit and take the SCOPE_DIFF to 49.
RECORD DEFECT, SECOND TIME: 145548 cites the asks as …145423 / …145425, which do not exist; the filed asks are …145544 (m-1) and …145546 (m-3). With 140251's identical slip, this looks like a drafting practice (citing draft-time stamps the engine replaces at render); I suggested citing siblings only by the submit JSON's `path`.
The upstream listing ran as its own command and was read before the submit this time. c6q and c6p stay local and unpushed; c7 onward held. The release hold is ABSOLUTE.

## R57 — both R-4.72 words carried; rev28 cut with two engine commits and a rewritten Task 7 (2026-09-23 15:12 `intg-2b-wiring-act/PLAN-master-planner-20260923-151255.md`; 18:07 PLAN `intg-substep2b/PLAN-pair-planner-20260923-180713.md`)

Master carried m-1's `R472_CEILING_PLACEMENT: own-commit-in-lane` (150702) and m-3's `R472_OPEN_WITNESS_REWORD: shim-fallback` (150622) in one relay citing both by their rendered paths, and owned the cited-path defect with a concordance for the five affected relays.
I verified both words with the gate's predicates, and every path 151255 cites resolves.
rev28 (`ccb63bcf…` at 11c0721, 3387 lines) admits c1d (Task 6e: classify reads `config --get-all remote.<name>.url`, first line, at both sites) and c1e (Task 6f: `GIT_CEILING_DIRECTORIES` = the canonical parent of the partial root on every restore invocation), both engine-only after c6p and before c7, under m-1's re-ruled veto-9 form.
One executable R-4.72 gate binds nine carriers for c1d, c1e and c7.
Task 7 now runs the pack grain on real config, the open grain on the labelled shim, and the ISO family (W-1′ inverted, W-C2..W-C5, W-2, W-4, W-5), with E3 at the pack verb.
F-RESTORE-DIVERGE is removed: it had contradicted Task 4's rev13 record of the landed isolation since rev13, which was my defect.
Task 9's network-class census is split at c1e, because c1e changes restore.cpp's network-class call lines, and its veto-9 arm admits exactly c1d and c1e by recorded sha in the order c6p < c1d < c1e < c7.
`resume.sh` carries `r472-owner-words.txt`; its prose list had also omitted `red1-owner-words.txt` since rev22, another prose/code drift of mine, now fixed.
FOUR MEASUREMENTS of this seat, written into the plan and to be flagged to m-1 on the digest word, none a stop:
(i) a config remote with no url is refused whole-pack under c1d's fence, where at B it recorded the remote's name (W-U6 pins the fence's stated arm);
(ii) c1e's canonical and no-empty-entry clauses are invisible at product scope, so only the W-C3s seam witness can red them;
(iii) W-C5's named mutant is visible only at the seam, because pack runs git at the repository top;
(iv) without the ceiling the clone itself still fetched the recorded url, so the defect is a false divergence at the gate's `--get-url`, and W-1′ reds by the refusal, never by content.
Also: the landed F-URL-1 engine case configures its rewrite AFTER classify, the order that hid R-4.72.
The gate walk caught a dead guard of mine before filing (the post-vs-pre comparison sat behind the c1d anchor); it was reordered and walked again: 54 PASS, 0 FAIL, plus six real-relay YES runs.
The veto-9 and census walk ran 17 PASS, 0 FAIL, and the `resume.sh` mirror walk behaved as intended with zero leftovers.
Next: the implementer's exact-hash review, then my digest word, master's fresh carry, the `t-oracle.txt` rewrite and the new `r472-owner-words.txt` in the pointer's directory, and then impl-8.
c6q and c6p stay local and unpushed; c7 onward is held. The release hold is ABSOLUTE.

## R58 — rev28 approved at the exact hash; the word filed (2026-09-23 18:21 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260923-182123.md`; 18:25 SITREP `intg-substep2b/SITREP-pair-planner-20260923-182553.md`)

The implementer approved rev28 `ccb63bcf…` at 11c0721 with no must-revise, after replaying the R-4.72 gate on the nine real carriers (six OK and one real NO) and checking the task-9 runner (`check` rc 0, 17 gates) and `resume.sh` digests.
I re-ran the T-ORACLE prefix at the rev28 digest in scratch clones: YES, plus two NOs (`carry-to`, `plan-sha-mismatch`), with no receipt on either NO.
The word asks master for the fresh five-field carry, with only the plan digest changing from 033242.
It states that I will write `r472-owner-words.txt` from his three R-4.72 carries, since those words are already on the record.
It routes the four c1d/c1e measurements to m-1 and adds the F-URL-1 test-order note.
COUNT CORRECTED BEFORE FILING: impl-8's SCOPE_DIFF is 52 rows, not 49. impl-7's 47 already hold `restore.cpp` and the engine test file; c1d adds `classify.cpp` and c1e adds four files (`git.{hpp,cpp}`, `git_exec.{hpp,cpp}`).
Master's 49 and my own earlier "49 with a ceiling file" both assumed one file. rev28 states no row count, so no plan byte moves.
Next: master's carry, then the `t-oracle.txt` rewrite and the new `r472-owner-words.txt` in the pointer's directory, both gates run from the candidate against the real files, the Step 0′ mirror walk, and impl-8.
The release hold is ABSOLUTE.

## R59 — master's fresh carry; both gate files on disk; impl-8 issued (2026-09-23 18:43 `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-184303.md`; 2026-09-24 06:04 IMPL `intg-substep2b/IMPL-pair-planner-20260924-060401.md`)

Master's carry 184303 cleared the T-ORACLE at `ccb63bcf…` (`T_ORACLE_VERDICT: cleared`); the three owner-object lines are byte-identical to 033242's.
His routing 184409 took R-4.74 and the three seam-only measurements to m-1 and held nothing.
I rewrote `t-oracle.txt` in `s2b-runners-4BSBek`, the directory the pointer names: four lines, `carry_relay=` 184303, sha256 `2081de72…`, mode 0400. The rev27 file is preserved as `t-oracle.prev-20260924-055739.txt` (`65c80bbf…`).
I wrote `r472-owner-words.txt` new beside it: nine lines from the carries 142025 / 145548 / 151255, sha256 `76553e71…`, mode 0444.
From the candidate at `534decb` with a scratch `$EVID`: the T-ORACLE prefix returned `t-oracle OK`, and the R-4.72 gate with `LABEL=c1d MODE=pre` returned OK.
The Step 0′ walk ran on a scratch mirror of the real files. YES published 20 carried lines. The NOs were stale locator → `t-oracle-stale`, unreadable r472 file → `carry-r472`, `same-lock`, `token-form`, and r472 absent → the gate fails closed. Nothing was left behind.
impl-8 was issued at PARENT plan-review-27 (182123). SCOPE_DIFF is 52 rows, all-in; every row was re-derived from `git log B..534decb`, and the c1d/c1e/c7 paths are marked EXPECTED.
The delegated lineage was walked on a three-relay mini-root with the 2.9.3 linter and was clean apart from the mini-root's known environment errors. The wrong-parent negative control fired three lineage errors.
UPSTREAM MOVED BEFORE SUBMIT: m-1's R-4.74 word 060131 (TO master, pdc 833bca2f) landed minutes before filing and was opened before the submit.
It rules `R474_URLLESS_REMOTE: narrow`, and the measurement behind it is worse than a garbage field. The recorded name reaches `ls-remote` as a repo-relative path, so an ignored bare repo of that name can falsely prove an unpushed tip. The pack is then silent and the clone fails at open.
c1d and W-U6 execute as fenced as the interim. The narrow act is m-1's own later engine act, due before the release gate, and it holds neither the Task 10 GO nor any c-commit.
The token cites the word as filed, not carried, and my GO will cite master's carry of it.
m-1 also routed a sibling to master for registration: a relative configured url is proven at pack and fails the clone at open.
No plan byte moves.
Next: the implementer's Step 0′ and c1d → c1e → c7 → c8 → Tasks 9–11 under impl-8; the GO waits on the three H reviews and master's carry of 060131.
The release hold is ABSOLUTE.

## R60 — impl-8 STOPPED at Task 9 on my defect; rev29 filed (2026-09-24 07:25 `intg-substep2b/IMPL-pair-implementer-20260924-072544.md`; 07:47 PLAN `intg-substep2b/PLAN-pair-planner-20260924-074742.md`; 07:48 SITREP `intg-substep2b/SITREP-pair-planner-20260924-074858.md`)

Under impl-8 the implementer committed c1d 116697f, c1e f57cd35, c7 9081149 and c8 a83657e, each on its exact Files-line paths. The branch is 19 commits past B, clean and unpushed.
Task 9 then stopped at its line 21, before any control or H0. `observer-unset-names.txt` and `llvm-manifest.txt` had a consumer since rev1 and no producer.
The R-4.49 and R-4.50 plans produced both in their Task 0; the 2b plan carried the consumers (Task 9, Step 4's `MANIFEST`, the container's name proof) without the producers.
Every review since rev1 read past it, mine included. The implementer correctly refused to synthesize either file.
rev29 (`6ef818b3…` at 7774feb) replaces line 21 with fifteen lines that produce both inputs at Task 9's head. They use R-4.50's own producer lines, run only when a file is absent, and pin each digest either way: source slice `53bbdd42…`, manifest `22724f78…`, names `e12d5d0a…`.
The pins were measured before the revision and are byte-equal to the R-4.50 archive. B's workflow is re-proved against its blob, and the status is re-proved clean.
The walk ran 2 YES and 10 NO cases, each stopping at its own line, on runner lines `cmp`-equal to the materialized task-9.
The census is 22 BLOCKs with only task-9 moving (`81185bba…`, 188 lines); `resume.sh` is unchanged.
The macOS observation stays ambient: Task 0's ambient B run reproduced every pinned cell.
The c8 class set (`A,B,C,D,E,K` and `E,K` declared by m-3's rev3 patch, against m-3's §5 `A/B/D/E/H/K`) is corrected in the plan as a record only and asked of m-3 through master, due before the GO.
Master's 060842 took R-4.74 `narrow` (R-4.75 registered; one m-1 seam act after 2b; nothing held in the lane).
The implementer's 072544 has no INDEX row (it was not submitted through the engine); I asked them to submit it.
My first submit of the PLAN refused E-ID-COLLISION because I passed `--admits-against` for a NEW id; it was resubmitted without the flag.
CLASS SWEEP after filing: every `$EVID` path read by rev29's task-9 / task-10 / task-11 runners (141 / 30 / 23 paths) was traced to a writer.
A first-pass regex left 23 without an explicit writer, and each resolved by reading: the helpers are hashed into `helpers.sha256` by Task 0 and verified at Task 9's head; the Linux outputs come from `linux-suite.sh` / `linux-container.sh` under `$OUT` and `selftest_summary.py`'s prefix; the per-label files are written through `$LABEL`; and `runners/task-10.done` is copied in by `run-task.sh`.
No other producerless input exists in Tasks 9–11.
Next: the implementer's exact-hash review; on approve, the carry word; then the `t-oracle.txt` rewrite in `s2b-runners-Xi2bWL` and impl-9.
The release hold is ABSOLUTE.

## R61 — master takes the impl-8 STOP; the producer gate cut (2026-09-24 08:07 `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-080734.md`)

Master verified the four commits path by path, confirmed the two-input defect (five reads, no writer at rev28), and measured rev29's fold as `+18/-3` on one path.
He routed the c8 class question to m-3 in `PLAN-master-planner-20260924-080645.md`.
The facts there: m-3's §5 bar binds H (one `UnclaimedGitEntry` error-path row: the `.git`-symlink recipe, kind, exit 3, JSON shape), and the rev3 patch carries no H at all.
H's substance is landed at CLI level (`tests/test_cli.cpp`, and c7's `unclaimed git symlink` witness, receipt `F-UNCLAIMED`).
m-3 answers `discharged` or `h-owed` before my GO.
No carry comes before the implementer's approve, and master will not name a runners directory.
MY FIRST CUT OF THE GATE WAS BLIND to the case it exists for: it checked only `[ -s … ]` guards, so with the names producer deleted the file was still READ (grep, shasum) and the gate passed.
Rebuilt, every literal read is a requirement and each must have an earlier writer. The writers a textual scan cannot see (25) are classified one row each against their real writer, and the gate fails on any orphan outside that set or any stale row.
The discriminator was run: rev28 rc 1 (exactly the two real orphans); rev29 rc 0; the names-only mutant rc 1 (that file); the manifest-only mutant rc 1 (its pair).
It is installed at `results/producer-gate/` and is a standing step before every token; it will be announced on my next word.

## R62 — rev29 approved at the exact hash; the word filed (2026-09-24 08:09 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-080955.md`; 08:25 SITREP `intg-substep2b/SITREP-pair-planner-20260924-082513.md`)

The implementer approved rev29 `6ef818b3…` at 7774feb (`intg-substep2b-plan-review-28`, PARENT plan-30) with no must-revise.
Their own replay of Task 9's lines 21–35 (2 YES, 10 NO at their own guards) matched mine, and they traced every consumer of the two inputs.
The approve relies on Task 9's zero-byte fence proving `e3.py` unchanged B..H0 before any consumer; verified here: the fence is runner line 100, the first Docker consumer line 122.
The T-ORACLE prefix (sha `1c437ac4…`, present once in rev29) was replayed at the new digest in scratch clones: YES `t-oracle OK` with one receipt; `carry-to` NO and stale-digest NO, each with no receipt.
My first replay was INVALID: a zsh glob left the synthetic carries uncommitted, so all three cases stopped `untracked-carry`. It was discarded and re-run with the carries committed by explicit path.
The word asks master for the five fields; only `T_ORACLE_PLAN_SHA256` moves from 184303, and the owner-object digests were recomputed at pdc 5fcc90ce, unchanged.
m-3's 081947 answers `C8_CLASS_SET: discharged`. m-3 owned H's silent drop across rev1–rev3; H's kind and exit 3 are landed at CLI level with the exact recipe, and m-3 measured the envelope valid. The harness H row is an m-3 residual for a later act. It reaches my GO through master's carry.
The word also adopts the producer gate as a standing pre-token step.
INDEX disclosure: commit 46627ef carries the implementer's 080955 row beside mine (their relay file stays theirs, untracked). Their 072544 STOP relay still has no INDEX row.
Next: master's fresh carry, then the `t-oracle.txt` rewrite in the pointer's directory, both gates, the Step 0′ mirror walk, the producer gate, and impl-9.
The release hold is ABSOLUTE.

## R63 — master's fresh carry; impl-9 issued (2026-09-24 14:07 `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-140701.md`; 14:13 IMPL `intg-substep2b/IMPL-pair-planner-20260924-141340.md`)

Master's 140701 cleared the T-ORACLE at `6ef818b3…`; the three owner-object lines are byte-identical to 184303's, and the prefix is present once at `1c437ac4…`.
It carries m-3's `C8_CLASS_SET: discharged`. The bar V-2b-8(iv) reads is the rev3 receipt for A/B/C/D/E/K plus the landed CLI witnesses for H; the harness H row is registered as R-4.76 (m-3's later H error-matrix act, since the runner has no pack-refusal branch).
Master verified that the 534decb→a83657e `src` delta is confined to `src/core/repo`, and he re-ran the producer gate himself: rev29 rc 0, and rev28 rc 1 on exactly the two orphans.
The pointer (read as its own command) names `s2b-runners-Xi2bWL`. `t-oracle.txt` was preserved as `t-oracle.prev-20260924-141042.txt` (`2081de72…`) and rewritten: four lines, `carry_relay=` 140701, sha `2ee21122…`, 0400.
From the candidate at a83657e with scratch `$EVID`s: T-ORACLE `t-oracle OK`, and the R-4.72 gate `LABEL=c1d MODE=pre` OK.
The Step 0′ mirror walk published 20 carried lines, every carried file byte-equal, lock `6ef818b3…`, token `impl-9`. The R-4.72, c6p and T-ORACLE gates all passed FROM the new directory. The NO cases were `carry-r472`, `t-oracle-stale`, `same-lock`, `token-form`, and r472 absent failing closed. Nothing was left behind.
The producer gate on the live plan returned rc 0 (0 orphans, 25 classified).
impl-9 was issued at PARENT plan-review-28 with SCOPE_DIFF 52 all-in; every row but `.github/workflows/s2-harness.yml` is LANDED. The lineage was walked on a mini-root, and the wrong-parent control fired 3 errors.
Its order is Step 0′, then `run-task.sh 9` (a STOP ends the token, with no retry); Task 10 waits on my GO with the three H reviews, 042625 (1), 060842 and 140701's carry of m-3's word.
The token discloses that Task 9's re-run rewrites the EMPTY `$EVID/H/status-pre.txt` (identical bytes) and re-copies its runner files into `$EVID/runners/`; impl-8's authoritative copies stay in `Xi2bWL`, never modified.
Next: the implementer's Task 9 return.
The release hold is ABSOLUTE.

## R64 — impl-9 STOPPED at Task 9's prologue on my defect; rev30 filed (2026-09-24 14:30 `intg-substep2b/IMPL-pair-implementer-20260924-143008.md`; 14:34 PLAN `intg-substep2b/PLAN-pair-planner-20260924-143458.md`)

Step 0′ published `s2b-runners-IvrESr`. Task 9's derived line 11 (`plan_blocks.py`'s `PROLOGUE_EVID`) then copied the four runner records FLAT into `$EVID/runners/`, where impl-8's rev28 `task-9.sh` sits at 0500. The multi-source `cp` failed on that name after writing the other three, leaving a mixed flat record.
My impl-9 token had asserted the re-copy without running the prologue against the real home, so this is the same class as rev29's defect: a claim about evidence-home state never executed against it.
rev30 (`cf58433e…` at 2455293) changes ONE line: the copy goes to `$EVID/runners/<token-id>/` (the id is form-checked and a pre-existing `task-N.sh` is refused). The flat remnants are preserved verbatim and recorded in §Per-task runner protocol, and `run-task.sh`'s success receipts stay flat.
Only `plan_blocks.py` moved among the 22 BLOCKs. Tasks 9/10/11 differ by that line; task-0, `resume.sh` and `run-task.sh` are unchanged; every `check` is rc 0 and the producer gate is rc 0.
Walked on a `cp -Rp` mirror of the real `$EVID/runners`: YES (records in the token directory, flat unchanged; task-10 under the same token too) and three NOs, each rc 1 with flat unchanged. The rev29 prologue as control reproduced `Permission denied` and mutated the flat record.
Class check: the home has 4 non-writable files, and no rev30 runner writes any of them.
Next: the implementer's exact-hash review; then the word, master's carry, the `t-oracle.txt` rewrite in `s2b-runners-IvrESr`, the gates, the Step 0′ walk, the producer gate and the prologue walk, then impl-10.
The release hold is ABSOLUTE.

## R65 — rev30 must-revised on MUST-2B-48 (the record copy was redirected but not confined); rev31 filed (2026-09-24 14:55 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-145529.md`; 15:12 PLAN `intg-substep2b/PLAN-pair-planner-20260924-151216.md`)

The implementer's replay showed that rev30's prologue followed a symlinked `$EVID/runners/<token-id>` out of the home (rc 0, body run, four records outside, `finalize.py list` 0 token records). A dangling `task-N.sh` symlink passed `-e` and was written through, and the other three names were never checked.
I reproduced both on a mirror of the real home. The finding is right and the defect is mine: rev30 redirected the copy without confining it.
rev31 (`5054cf89…` at ee94b61, 3411 lines) turns `PROLOGUE_EVID`'s one line into six. The runners directory and the token directory must be real non-symlink directories whose physical paths are the home's; the token directory is created with a plain `mkdir`. All four names must be lexically absent (dangling symlinks included) before the one copy, and each must be a regular `cmp`-equal file after it.
The residual is stated in the plan: only an I/O fault inside `cp` after every check could leave a partial record. The post-copy check stops on it, and the partial record is kept.
Only `plan_blocks.py` moved (`f26901ef…` → `0c365092…`). Tasks 9/10/11 differ by that prologue line, task-0, `resume.sh` and `run-task.sh` are unchanged, every `check` is rc 0, the producer gate is rc 0, and the placeholder, token and alternation counts are 0.
Walked on a `cp -Rp` mirror of the real `$EVID/runners` (83 assertions, 0 failing):
- NO: a symlinked token directory, a dangling token directory, a symlinked runners directory, a token path that is a file, and 4× dangling plus 4× existing names. Each stops before the body with the outside, the flat records and the evidence tree unchanged.
- YES: Task 9 then Task 10 under one token, with `finalize.py list` = 8 records, then a same-token re-run refused.
- Controls: rev29 hits `Permission denied`, and rev30 reproduces both findings.
- Mutants redden exactly their own cases. The two token-directory symlink guards overlap by design, so removing either alone stays green. The post-copy check is shown to be a guard by a short-copy fault injection.
Next: the implementer's exact-hash review; then the word, master's carry, the `t-oracle.txt` rewrite in `s2b-runners-IvrESr`, the gates, the Step 0′ walk, the producer gate and the prologue walk, then impl-10.
The release hold is ABSOLUTE.

## R66 — rev31 must-revised on MUST-2B-49 (a mid-copy fault left a permanent partial record); rev32 filed (2026-09-24 15:36 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-153636.md`; 16:01 PLAN `intg-substep2b/PLAN-pair-planner-20260924-160113.md`)

rev31 copied the four records straight into their final names. A `cp` that failed after a prefix exited before the post-copy check, leaving a partial record under the final names, and a same-token retry was refused forever.
rev31's paragraph had accepted that state even though 145529 had ruled it out, and its claim that the post-copy check "stops on" a `cp` fault was false. Both defects are mine. I reproduced the finding with the rev31 prologue and a prefix-3 `cp` shim.
rev32 (`90b5274d…` at 783dd49, 3414 lines) publishes the four records as one unit, `runners/<token-id>/task-N/`. They are copied into a fresh `mktemp -d` stage inside the token directory, verified exactly, renamed onto `task-N` once, and re-verified.
A fault leaves `task-N` absent, with its own `stage-task-N.*` as the durable fault record. A same-token retry publishes cleanly. The stated residual is concurrency, which this lane excludes.
Only `plan_blocks.py` moved (`0c365092…` → `8331c944…`). task-0, `resume.sh` and `run-task.sh` are unchanged, every `check` is rc 0, the producer gate is rc 0, and the scans are 0.
Walked on real-home mirrors with a planted prior token record (213 assertions, 0 failing):
- Fault matrix, each case followed by a retry: `cp` prefixes 0–3, all four copied with rc 1, a corrupt copy, and an `mv` failure.
- NO cases on the confinement and on a present record name.
- The all-four legacy-leaf table, which proves those names inert.
- YES: Task 9 + Task 10 = 8 records; a same-task re-run is refused with the tree unchanged.
- Controls: rev29, rev30 and rev31.
- Mutants: each isolates its guard. The post-rename check is proved only paired with the stage check (an overlap by design), and a fixed-name stage reddens every retry.
Next: the implementer's exact-hash review; then the word, master's carry, the `t-oracle.txt` rewrite in `s2b-runners-IvrESr`, the gates and walks against the real home, then impl-10.
The release hold is ABSOLUTE.

## R67 — rev32 APPROVED; the word to master filed (2026-09-24 16:42 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-164230.md`; 19:18 SITREP `intg-substep2b/SITREP-pair-planner-20260924-191800.md`)

The implementer approved rev32 (`90b5274d…` at 783dd49; plan-review-32) with no must-revise. Their own fault replay covered `cp` prefixes 0–4, a corrupt copy returning 0 and a failed rename, each with a clean same-token retry, plus `finalize.py`'s path-level split of the fault stage from `task-9/`. MUST-2B-49 is closed, and so is MUST-2B-48.
The word to master asks for the five carry fields verbatim; only `T_ORACLE_PLAN_SHA256` moves from 140701. The three owner-object digests were recomputed at pdc b2e2740b and are unchanged.
The T-ORACLE prefix (`1c437ac4…`, byte-present once in rev32) was replayed in fresh scratch clones (bivpak 8099acd, pdc b2e2740b) against synthetic carries committed by explicit path. Tracking was asserted with `git ls-files` after a zsh glob broke my first assertion line.
Results: YES rc 0 with one receipt; carry-to STOP rc 1 with no receipt; stale rev31 digest STOP rc 1 with no receipt.
The pointer still names `s2b-runners-IvrESr`.
Next: master's carry; then the `t-oracle.txt` rewrite in IvrESr (prev preserved), the T-ORACLE prefix and R-4.72 gate from the candidate, the `resume.sh` mirror walk, the producer gate and rev32's prologue walk on a fresh real-home mirror; then impl-10 at PARENT plan-review-32.
The release hold is ABSOLUTE.

## R68 — master's carry 192620; the locator rewritten; gates and walks green; impl-10 issued (2026-09-24 19:26 `master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-192620.md`; 19:43 IMPL `intg-substep2b/IMPL-pair-planner-20260924-194325.md`)

Master's carry 192620 (`6b32407b…`, committed in pdc 092239d5, `TO: intg.pair-planner`) clears T-ORACLE at `90b5274d…`. Only the plan digest moves from 140701.
Master measured the arc himself: the impl-9 STOP's cause in the real home, the rev29→rev32 delta bounded to one BLOCK constant, and rev32's prologue read line by line.
The pointer (read as its own command) names `s2b-runners-IvrESr`. `t-oracle.txt` was preserved as `t-oracle.prev-20260924-193739.txt` (`2ee21122…`, hard-linked, bytes and mtime kept) and re-created exclusively at 0400 (`8d42bdc2…`, carry_relay 192620).
Gates from the candidate at a83657e with scratch `$EVID`s:
- T-ORACLE OK; the preserved rev29 locator STOPs on the plan-digest mismatch.
- R-4.72 (c1d pre) OK.
Step 0′ walk on scratch mirrors:
- YES publishes with 20 carried lines and passes the R-4.72, c6p and T-ORACLE gates from the new directory.
- The stale, unreadable-r472, same-lock and token-form cases STOP; an absent r472 fails the gate closed.
- Nothing was left in the evidence root.
Producer gate rc 0. rev32 prologue walk on a fresh real-home mirror: 213 assertions, 0 failing.
The SCOPE_ROW_EVIDENCE path-to-commit map was re-derived from `git log B..a83657e` and is byte-equal to impl-9's.
The mini-root lineage walk shows the three dispatch-lineage errors only under the wrong parent.
impl-10 issued at PARENT plan-review-32 (`507f86d2…`): Step 0′, then Task 9, with Task 10 on my GO.
The release hold is ABSOLUTE.

## R69 — impl-10 STOPPED at Task 9's first Linux build; the whole Linux census measured; rulings asked of master (2026-09-24 20:11 `intg-substep2b/IMPL-pair-implementer-20260924-201131.md`; 21:23 SITREP `intg-substep2b/SITREP-pair-planner-20260924-212307.md`)

impl-10 ran Step 0′ (`s2b-runners-sK9rhy`) and Task 9 once. The rev32 prologue published atomically, and the structural and macOS gates passed. The H0 Linux container then stopped at `cmake --build` on 2 GCC `-Werror=missing-field-initializers` errors in `tests/test_repo_git.cpp` (c1e's `Git::Opts::ceiling`).
That was a stopped instrument, 147 objects reached. A keep-going build of a83657e finds 24 errors in 6 test files (14 sites, 5 structs); B finds 0. All the flagged members were added by 2b commits.
Two test-only repairs, recorded in `results/linux-census-20260924/`, were proven in the plan's own `linux-container.sh` at scratch commits:
- repair 1 names each omitted member;
- repair 2 moves the c3 hook call out of a `CHECK`. The test failed under `-r xml` on both platforms because Catch2's redirecting reporter re-points `std::cerr` at assertion boundaries; it was the one macOS failure impl-10 recorded.
The container is rc 0 at that head, the same as B.
Still open:
- 32 candidate-introduced clang-tidy errors in 7 product files from 7 commits (B: 0). ctest carries them as data, but they would red the vehicle's remote tidy leg.
- `harness-selftest` varies across runs (B 3, the heads 2 and 4), including one case B did not fail; flagged for m-3.
Mine: no Linux contact before Task 9; the macOS count gate admitted a failure count as a tuple move.
Asked of master:
- R1: scope +1 path (`tests/test_repo_git.cpp`) for a test-only c8L.
- R2: the tidy class over owner-sealed bytes — a recommended behaviour-neutral c8T with owner byte reviews, no suppression.
- R3: rev33 adds a pre-Task-9 canonical-container gate, the count gate refusing failures, and staged preservation of impl-10's `H/`, `H0.txt` and `helpers.verify-9.txt`.
No rev33 and no token until master's word. `s2b-runners-sK9rhy` is never retried.
The release hold is ABSOLUTE.

## R70 — master ruled R1/R2/R3; c8T scouted whole; three asks back before rev33 (2026-09-24 21:50 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-215035.md`; 22:29 SITREP `intg-substep2b/SITREP-pair-planner-20260924-222944.md`)

Master's rulings:
- R1: SCOPE is admitted to 53 for two test-only commits, c8L then c8H.
- R2: the tidy class is fixed inside 2b as a behaviour-neutral c8T, with no suppression, owner byte review by file, and m-4's security read. Interface-level findings STOP up.
- R3: all three process items, plus the container gate at every new head.
- R-4.77 (harness variance): at least five samples before the GO.
- The remote-CI justification is corrected to the LOCAL tidy gate.
The scout at scratch head `8532d0c` (c8L, c8H, c8Tr, c8T; record commit f4af9a2):
- 23 of 32 findings repaired behaviour-neutrally;
- canonical container rc 0, with `safety-tidy-analyzer` showing exactly the 9 held findings (coverage 37/37);
- macOS `-r xml` green on all five binaries (biv_tests 484/0/0/3);
- `harness-selftest` failed the same 4 cases as the repair-2 head.
Asked back:
- A: sealed per-commit veto 9 forces `restore.cpp` into its own commit, c8Tr, before c8T.
- B: the owners' word on the 9 interface-level findings: 4 in the generated consent table (m-3's generator) and 5 swappable-parameter signatures, each with a proposal. Until they are ruled, no head can pass R3's tidy-green gate.
- C: the owner byte-review list by file:line.
rev33 waits on A and B. No token; `s2b-runners-sK9rhy` is never retried.
The release hold is ABSOLUTE.

## R71 — rev33 written and walked but held; two cells asked of master (2026-09-24 22:40 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-224030.md`; 23:24 SITREP `intg-substep2b/SITREP-pair-planner-20260924-232402.md`)

Master 224030:
- Ask A ruled: c8Tr, then c8T, under veto 9, unamended.
- R3 corrected: each intermediate head must match its pinned tidy list byte for byte, and the landing head must be GREEN.
- Ask B routed to the owners; Ask C ratified.

rev33 was generated from the committed rev32 blob:
- NEW Task 8b applies the census patches verbatim and pins each resulting tree. A per-head gate runs at each head: the canonical container, the pinned tidy list, and macOS `-r xml` rc 0 with failures=0.
- Task 9 preserves impl-10's outputs by staged renames, refuses failure counts, requires tidy green at H0, and always runs the series.
- The c8Tr-head list (31 lines) was measured in the canonical container and committed at d318a92.

Walks:
- Preservation: 37 real-home mirrors, the fault matrix and mutants, all as designed.
- Step 0′ from a mirror of `s2b-runners-sK9rhy`: YES published; stale, same-lock, token-form and wrong-lock cases all STOP.
- Per-head gate: PASS at the c8H, c8Tr and c8T scout heads. STOP at the c8L head: the one c3 `-r xml` case fails on both platforms. c8H applied first does not compile under GCC.
So master's R1 (two commits) and R3 (green at every head) conflict.
The three owner words also landed with no decline: m-1 224747, m-4 225018, m-3 225029. m-4's C-U4 binds c8T's own `next_utf8` hunks.
Asked of master:
- (A) one test-only commit for c8L+c8H (recommended), or a pinned expected red at c8L;
- (B) one c8T carrying every ruled item, the witnesses and the mutant records, tidy green at its head, which dissolves T-C8B (recommended);
- the carry of the three words.
rev33 is not committed or filed; the docs-tree plan is still rev32. No token.
The release hold is ABSOLUTE.

## R72 — rev33 filed for the implementer's exact-hash review (2026-09-25 00:34 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260925-003436.md`; 02:10 PLAN `intg-substep2b/PLAN-pair-planner-20260925-021025.md`)

Master 003436:
- Cell (A): the initializer and c3-hook repairs are ONE test-only commit c8L.
- Cell (B): ONE c8T carries the 22 mechanical repairs, the owners' words B1–B6 and the decoder witnesses, tidy GREEN at its head; T-C8B and c8B are dissolved.
- w1–w3 with their `.biv` twins and their mutants gate; M-SEC gates on the existing positives; w4 does not gate (R-4.78 to m-3).

Census record `dfffc49`:
- repair-12 (c8L) and repair-5 (c8T folded), with the three patches reproducing the pinned trees in order on a83657e.
- The c8T scout head `c97843d` is GREEN in the canonical container: rc 0, tidy zero findings with the row passed, coverage 37/37; only harness-selftest failed (6th variance sample).
- The c8Tr and c8T mutant records and the B1 regeneration diff.

rev33 (`7bbd6270…` at `1095d19`):
- NEW Task 8b: c8L, c8Tr, c8T verbatim from the census record, tree-pinned, each head gated (container rc 0, tidy 32 / 31 / EMPTY, macOS `-r xml` failures=0).
- m-1's pre-stated c8Tr condition is a block at the c8Tr head: W-C6 green, Mc5 and M-SEAM red.
- At c8T: the B1 reproduce check and the mutant block (M-MASK, minimum, M-SEC, B6-swap gating; truncation and B5-bix recorded).
- Task 9 starts at the c8T head with every Task 8b receipt; only task-9's runner moves.

Walks:
- The commit block, the c8Tr record, the B1 block, the c8T mutant block, Task 9's first lines and veto 9's c8 order: YES and NO, all as designed.
- The per-head gate: 3 YES and 31 NO. The matrix showed that a status-attribute edit never reaches the `xmlcases` row guard, so two further cases replayed real outputs, and that guard fires in both.
- Step 0′ with the new lock: YES published; four NO cases STOP.
- The preservation snippet is byte-identical to the one walked before.

Recorded for master as data: the truncation mutant terminates only when w4 is present; B5-bix stays green (a RESIDUALS row under m-1); B5-bix's assertion total differed between two runs, and it is not pinned.
No token.
The release hold is ABSOLUTE.

## R73 — MUST-2B-50 folded; rev34 filed (2026-09-25 06:33 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-063356.md`; 06:41 PLAN `intg-substep2b/PLAN-pair-planner-20260925-064145.md`)

The implementer must-revised rev33 `7bbd6270…`, and was right: VETO 9 MECHANICAL still said "exactly FIVE engine commits … no commit other than those five", while Task 8b, the order rule, Task 9's runner and acceptance 1 require c8Tr.
My generator had moved the ENGINE BYTES line to six but not the veto's closing clause.

rev34 (`80ea88f4…` at `e18ea66`), prose only, four lines:
- The veto now reads exactly SIX engine commits (c1a, c1b, c1c, c1d, c1e, c8Tr), c8Tr at `restore.cpp` alone after c7 between c8L and c8T, no spanning.
- The exclusive "ONLY c1d then c1e" wording is repaired in Task 9's Step 2 prose and in acceptance 1.
- A rev34 history entry.

Measured: the block list is identical to rev33's; `check` rc 0 on tasks 0/9/10/11; the producer gate rc 0; placeholder, token and census scans 0 with controls; Step 0′ re-walked on the new lock.
Disclosed in the carrier: four grading-table rows the rev33 carrier had left stale (commit order, count gate, population rule, zero-byte fences), now re-cut.
Disclosed here: the relay commit `458b176` also carried the implementer's uncommitted INDEX row for 063356 (the shared-INDEX sweep).
No token.
The release hold is ABSOLUTE.

## R74 — MUST-2B-51 folded; rev35 filed (2026-09-25 06:54 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-065407.md`; 07:41 PLAN `intg-substep2b/PLAN-pair-planner-20260925-074108.md`)

The implementer must-revised rev34 `80ea88f4…`, and was right.
My MUST-2B-50 correction widened acceptance 1's first subject to c8Tr, so c8Tr fell under that clause's "after c6p and before c7" while the same sentence placed it after c7.
Task 9's Step 2 prose had the same shape (not named by the review), through my rev34 parenthetical inside the c1d/c1e subject.

rev35 (`6781eae1…` at `6322f89`), prose only, three lines:
- Both sentences are partitioned by c7: c1d then c1e are the only engine commits before c7; c8Tr is the only engine commit after c7, at `restore.cpp` alone, between c8L and c8T, met once; exactly six.
- A rev35 history entry; rev34's entry and VETO 9 MECHANICAL line are unchanged.

Sweep: every operative sentence was scanned for c8Tr with a before-c7 predicate and for c1d/c1e with after-c7; the only hit is the partitioned clause itself.
Measured: the block list is identical to rev33's; `check` rc 0 on tasks 0/9/10/11; the producer gate rc 0; scans 0 with controls; Step 0′ re-walked on the new lock.
Disclosed: the relay commit `aa3b9b8` also carried the implementer's uncommitted INDEX row for 065407 (the shared-INDEX sweep).
No token.
The release hold is ABSOLUTE.

## R75 — rev35 approved; the word sent to master (2026-09-25 07:54 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-075455.md`; 08:13 SITREP `intg-substep2b/SITREP-pair-planner-20260925-081348.md`)

The implementer approved rev35 `6781eae1…` at `6322f89` (plan-review-35), with no must-revise.
The word to master carries the five T-ORACLE fields verbatim; only the plan digest moves from 192620, and the three owner-object digests are byte-identical at pdc `c40e61e5`.
The plan's T-ORACLE prefix (`1c437ac4…`, present once) was replayed in scratch clones against synthetic committed carries: YES `t-oracle OK` with one receipt; the carry-to and stale-digest (rev34) controls STOP with no receipt.
Measured for the token: all 15 paths the three Task 8b commits touch are inside impl-10's 52 SCOPE_DIFF rows plus `tests/test_repo_git.cpp` (53).
For R-4.78, as data: at c8T's own `.at()` bytes the truncation mutant terminates (rc 134) in all three runs, only with w4 present; master's 003436 measured red=0 on a83657e's decoder.
Next: master's fresh carry → the `t-oracle.txt` rewrite in `s2b-runners-sK9rhy` → impl-11 at PARENT plan-review-35.
The relay commit `3fb8f8f` also carried the implementer's 075455 INDEX row.
No token.
The release hold is ABSOLUTE.

## R76 — master's carry; impl-11 dispatched (2026-09-25 08:32 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260925-083232.md`; 09:21 IMPL `intg-substep2b/IMPL-pair-planner-20260925-092148.md`)

Master cleared T-ORACLE for rev35 `6781eae1…`: it ran the plan's own gate with two controls at its seat, proved rev33 → rev35 prose-only, and re-derived the 15-path Task 8b union independently.
It amended R-4.78 on my counter-measurement (reproduced: at c8T's `.at()` bytes the truncation mutant terminates only with w4; w4 stays non-gating) and registered R-4.79 (B5-bix green, owner m-1).

Before the token, at this seat:
- `t-oracle.txt` in `s2b-runners-sK9rhy` rewritten from 083232 (`f94c899c…`, a staged file renamed into place); the rev32 file preserved byte-identical as `t-oracle.prev-20260925-091248.txt`.
- The T-ORACLE prefix from the candidate against the real file: OK; the preserved locator STOPs with no receipt.
- The R-4.72 gate from the candidate: OK; an eight-line carrier STOPs.
- Step 0′ walked on a mirror with the real locator: YES published (ten gate files byte-equal); stale, same-lock, token-form and wrong-lock STOP; the real pointer untouched.
- The producer gate with the committed rev33 baseline (`ed3fb96`): rc 0; the 25-row baseline rc 1 with exactly the 13 new rows; an unwritten read rc 1.
- The real evidence home read against every Task 8b precondition: inputs present, every created name absent, the candidate's build configured.
- The lineage mini-root: YES shows only mini-root environment errors; a wrong-parent control raises the three lineage errors. (My first run passed a directory without `--relay-root` and both "results" were tracebacks — caught by reading the output, re-run correctly.)

impl-11 at PARENT `intg-substep2b-plan-review-35`, SCOPE_DIFF 53 all-in (impl-10's 52 plus `tests/test_repo_git.cpp`; 15 rows EXPECTED for Task 8b), order Step 0′ → Task 8b → Task 9; Task 10 waits on my GO.
The release hold is ABSOLUTE.

## R77 — impl-11's Task 9 STOP folded; rev36 filed (2026-09-25 12:56 `intg-substep2b/IMPL-pair-implementer-20260925-130242.md`; 14:24 PLAN `intg-substep2b/PLAN-pair-planner-20260925-142447.md`; 14:25 SITREP `intg-substep2b/SITREP-pair-planner-20260925-142508.md`)

impl-11 landed Task 8b (c8L `c47eb322`, c8Tr `889d8130`, c8T `99136ca6`; every head gate rc 0) and stopped Task 9 at derived line 219, after both Linux containers rc 0: the pinned `skipset.py` cannot parse B-cells' `expected_skips linux absent ` (B's workflow pins no Linux skip names; `cells.py` writes that form by design).
The defect is mine: my rev33–rev35 walks covered the new runner lines, never the body past them against the real `B-cells.txt`.
Running every consumer after line 219 on a mirror of the real home found a second stop one line later (`xmlcases.py e3` reads a childless `<OverallResult>` as falsy, rc 5 on the green case).

rev36 `e87c999a…` at `d181bfb` (Task 9 only; no helper block moves):
- the Linux skip set UNCHANGED = H0's observed set against B's observed set (the `absent` row asserted once first); macOS stays on `skipset.py`;
- the runner reads the `[E3]` cases itself (`is None`);
- Step 0 also preserves the attempt's B Linux leg (every `B/` entry outside Task 0's fifteen), so impl-11's attempt keeps as `attempts/task9-H0-99136ca/` and `B/` holds exactly the fifteen afterwards.

Walked before filing, records at `results/rev36-walks/` (same commit): a 49-line preservation matrix with fault injection and guard-isolating mutants; the new lines on YES and eight NO cases; every other consumer after line 219; Step 0′ from `s2b-runners-aY2Suc`; ONE real series draw through the loop's exact mounts (rc 0, population 1013, 4 family failures).
The producer gate needed a rev36 baseline (+2 rows: `BLEG` writes its argument), with the discriminator run.

To master (SITREP 142508): (A) the Linux skip-set definition, for objection before the carry; (B) K-3's `landed min ≥ base max` tie on equal constant counts — rev36 keeps it verbatim, I recommend strict `>`, master's to rule.
Observations left to the implementer: `finalize.py prbody`'s partial commit list; a stale comment in `linux-container.sh`.
Next: the implementer's exact-hash review → my digest word → master's carry → the `t-oracle.txt` rewrite in `s2b-runners-aY2Suc` → impl-12 (Step 0′ → Task 9). The release hold is ABSOLUTE.

## R78 — master's answer to 142508 (2026-09-25 14:51 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260925-145141.md`)

(A) NO OBJECTION to rev36's Linux skip-set definition, on master's own reading of the real home: B-cells' Linux row is literally `expected_skips linux absent `, and the one observed name is byte-identical in five `tuples-linux.txt` files (B, H0, and the three Task 8b heads).
Master registered the inherent blind spot as R-4.81: an observed-against-observed comparison cannot see a skip present at BOTH trees; the count arm catches it only if the count moves.
Master also checked what I had not claimed: `skipset.py`'s two remaining call sites are both macOS, where B pins names, so the crash cannot recur there (it still dies rather than STOPs on `absent` — harden it when that block next moves); `xmlcases.py ctest-row` (four live sites) uses `is None` and is immune.
Task 8b verified by master at the candidate's bytes: veto 9 PASS on c8L, c8Tr and c8T; union 15; B1's regeneration exactly 3 lines; tidy GREEN corroborated from impl-11's own junit.

(B) CORRECTION — my attribution was wrong: `015244` is `FROM: m-4.planner`; master's `135905` applied it. SITREP 142508 called it master's clause twice, and plan-37's carrier once; the plan artifact does not attribute it. Master asked m-4 for `K3_TIE` (`…/PLAN-master-planner-20260925-145028.md`) and reproduced the tie with the plan's own `series_verdict.py`; m-4's twenty r437 draws are NOT-SHIFTED under all three arms.
rev36 keeps K-3 verbatim. Sequencing, adopted: the `K3_TIE` word must be in hand before impl-12's Task 9 series draws, so impl-12 is not issued until it lands; a strict-`>` ruling means rev37 (the `series_verdict.py` block moves and needs its own materialization under `$EVID` and a walk).

Master's suggestion, taken for the next revision of the producer gate: a FORM leg — for each pinned consumer, run one real producer sample from the evidence home through it; it would have caught both stops before Task 9.
Next unchanged: the implementer's exact-hash review of plan-37 → my digest word → master's carry → `K3_TIE` → the `t-oracle.txt` rewrite in `s2b-runners-aY2Suc` → impl-12. The release hold is ABSOLUTE.

## R79 — rev36 approved, then K3_TIE strict; rev37 filed (2026-09-25 14:38 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-143819.md`; 15:46 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260925-154632.md`; 17:08 PLAN `intg-substep2b/PLAN-pair-planner-20260925-170847.md`)

The implementer approved rev36 `e87c999a…` (plan-review-36), replaying the new lines and the preservation on disposable copies of the real home, and declined to reinterpret K-3 — noting an owner change moves the digest and the approve does not carry.
m-4, the clause's author, ruled `K3_TIE: strict` (`…/DESIGN-planner-20260925-151817.md`): K-3's separation arm becomes `landed min > base max`; its deciding series ([2, 3×9] → [3×10], delta 0.10) reads SHIFTED under `>=` and under master's (b2), NOT-SHIFTED under strict; a real one-failure shift still fires. Master carried it (154632), withdrew its own (b2), and corrected its own reason: the series runs ALWAYS in Task 9, so the fold precedes the token.

rev37 `82d2780a…` at `6f84c3a`: the three sites (code, the block's comment, the description); Task 9 produces the corrected reducer at `$EVID/series_verdict.rev37.py` (staged in `work/`, digest `09b6cb76…` checked, renamed; pinned either way; compiled) because Task 0's `$EVID/series_verdict.py` (the old block, `e4abc66c…`, equal to master's pin) is pinned and never overwritten; the series calls it. rev36's Task 9 fold is byte-unchanged.
Walked (records at `results/rev37-walks/`): the producer lines (absent, present, stale bytes, symlinks, the wrong plan, injected faults, and a mutant proving the stage check load-bearing); the reducer on the three nulls (NOT-SHIFTED) and the real shift (SHIFTED); Step 0′ on the new lock. The producer gate needed a rev37 baseline (+2 variable-written rows), discriminator run.

Next: the implementer's exact-hash review of plan-38 → my digest word → master's five-field carry → the `t-oracle.txt` rewrite in `s2b-runners-aY2Suc` → impl-12 (Step 0′ → Task 9). The release hold is ABSOLUTE.

## R80 — MUST-2B-52 folded; rev38 filed (2026-09-25 17:17 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-171756.md`; 17:45 PLAN `intg-substep2b/PLAN-pair-planner-20260925-174517.md`)

The implementer must-revised rev37: its reducer producer redirected into a FIXED stage name with no symlink or absence check, so a planted stage symlink carried the write outside the home before any STOP (reproduced by the implementer); a regular stage from an earlier failure was silently truncated. My matrix had tested symlinks at the final path only — the class my own confine-don't-redirect lesson names.
The class reached further: the rev29 inputs are guarded by `[ ! -e ]` (true for a DANGLING symlink), and every other fixed name Task 9 writes at the home root, in `work/` and in `B/` had no symlink test; a mutant without the new guard shows rev36's approved `BLEG` write creating an 802-byte file outside the home through a dangling `work/B-leg.names`.

rev38 `a342a9c5…` at `e95be95` (Task 9 only): the stage is a fresh `mktemp` file checked regular before and after the extract; CONFINEMENT before the first write (`work/` and `B/` physically the home's, no symlink directly under the home, `work/` or `B/`); `H.txt` and `commits.c9.txt` must be absent at the start. Disclosed behaviour change: a symlink inside `B/` now STOPs instead of moving with the B leg (the real home has none).
Walked (records at `results/rev38-walks/`): 56 preservation/confinement cases + 4 mutants; the producer with the implementer's reproduction as control (rev37 writes outside, rev38 does not); Step 0′ on the new lock; producer gate on a rev38 baseline with its discriminator.

Next: the implementer's exact-hash review of plan-39 → my digest word → master's carry → the `t-oracle.txt` rewrite in `s2b-runners-aY2Suc` → impl-12. The release hold is ABSOLUTE.

## R81 — rev38 approved; the word sent to master (2026-09-25 17:58 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260925-175832.md`; 18:24 SITREP `intg-substep2b/SITREP-pair-planner-20260925-182450.md`)

The implementer approved rev38 `a342a9c5…` at `e95be95` (plan-review-38, PARENT plan-39), with no must-revise; its own disposable replay confirmed that MUST-2B-52 is closed at the class boundary.
The word to master carries the five T-ORACLE fields verbatim; only the plan digest moves from 083232, and the generator asserted that the three owner-object digests equal 083232's lines at pdc `6f08a54d`.
The plan's T-ORACLE prefix (`1c437ac4…`, present once) was replayed in scratch clones (bivpak `9ec746b`) against synthetic committed carries: YES `t-oracle OK` with one receipt; the carry-to and stale-digest (rev35) controls STOP with no receipt.
Next: master's fresh carry → the `t-oracle.txt` rewrite in the directory `$EVID/runners-dir.txt` names (today `s2b-runners-aY2Suc`, predecessor preserved) → impl-12 at PARENT plan-review-38 with the same 53-path SCOPE_DIFF; Step 0′ → Task 9; Task 10 waits on a later GO.
The relay commit `eb015d9` also carried the implementer's 175832 INDEX row.
No token.
The release hold is ABSOLUTE.

## R82 — master's carry; impl-12 dispatched (2026-09-25 18:52 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260925-185232.md`; 2026-09-26 00:17 IMPL `intg-substep2b/IMPL-pair-planner-20260926-001717.md`)

Master cleared T-ORACLE for rev38 `a342a9c5…` (carry `e0f2ead7…`, committed at pdc `4c3ab243`; its addendum at `5689e538` re-ran the prefix against the real carry).
It ran the plan's gate with two controls, the rev35→rev38 block census with the canonical extractor, the strict K-3 block over seven fixture series and 400 000 random series, the producer over seven cases, and MUST-2B-52's closure with a guard-removed mutant.
It registered R-4.82 as a watch item for my next Task 9 revision: `series/`'s three targets are covered only by the start fence, because `mkdir -p` accepts an existing directory or a symlink to one.
It also noted that rev38's lead under-describes the coverage of fixed output names; each one is covered, some by other mechanisms.

Before the token, at this seat:
- `t-oracle.txt` in `s2b-runners-aY2Suc` rewritten from 185232 (`1910b60c…`, a staged file renamed into place); impl-11's file preserved byte-identical as `t-oracle.prev-20260926-000012.txt`.
- The T-ORACLE prefix from the candidate (`99136ca`) against the real file: OK, the receipt naming 185232 at `e0f2ead7…`; the preserved locator STOPs with no receipt.
- The R-4.72 gate, re-extracted from rev38 (byte-equal to the rev33 extraction): OK; an eight-line carrier STOPs.
- Step 0′ walked on a mirror with the real locator and `resume.sh` from the live plan: YES published (ten gate files byte-equal, 20 carried lines); stale, same-lock, token-form and wrong-lock STOP; the real pointer untouched.
- The producer gate with the committed rev38 baseline: rc 0 (42 classified); the rev37 baseline rc 1.
- The real home against Task 9's start fences: every created name absent, zero symlinks at depth one, `work/` and `B/` confined, helpers verifying, `B/` 51 entries.
- The lineage mini-root: YES shows only the four mini-root environment errors; a wrong-parent control raises the three lineage errors.

impl-12 at PARENT `intg-substep2b-plan-review-38`, the same 53-path SCOPE_DIFF all-in (the 15 Task 8b paths now LANDED; the only EXPECTED row is c9), order Step 0′ → Task 9; Task 10 waits on my GO.
The relay commit is `1f069f1`.
The release hold is ABSOLUTE.

## R83 — Task 9 accepted; m-3 MUST-REVISE (MUST-H-1) withholds the GO; the engine at 2.9.5 (2026-09-26 15:21 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-152147.md`; 16:47 `…/PLAN-master-planner-20260926-164725.md`; 17:05 SITREP `intg-substep2b/SITREP-pair-planner-20260926-170555.md`)

impl-12 ran Task 9 once to rc 0: FINAL H `2893bc53`, c9 = four `successes` cells (macOS 60→82, 419→484; Linux 60→82, 421→486).
I verified it at the bytes, and master re-measured and accepted it (152147).
The implementer's return is still an unadmitted draft (`.engine/drafts/intg.pair-implementer/IMPL-pair-implementer-20260926-145636.md`, sha256 `457b14fa…`); the engine now matches its 2.9.5 client.
My SITREP (drafted 15:08) was refused twice by the old daemon's fingerprint and filed at 17:05 after master's 2.9.5 migration; its commit `ab6f89c` carries the engine's recovery back-fill of four implementer rows (2026-09-21/22/24 stamps, appended out of time order).

Owner reviews of H: m-1 no-red (160158), m-4 no-red (160548), m-3 MUST-REVISE (160359).
MUST-H-1: a url-divergence-refused row renders `kind` / `detail` as null into a schema whose row object admits neither, so the envelope fails its own schema exactly when the consent fail-safe fires.
m-3's fix: F1 `kind: "UrlDivergenceEntryRefused"`; F2 `detail` = A6 `:537`'s per-entry sentence; F3 the schema gains both, required iff `failed`, with the selftest schema pins recomputed; F4 the writer never emits a null, and a `failed` row lacking either is a typed internal error; F5 whole-envelope validation witnesses plus two named mutants.
Master widened it: the two-argument `repo_row` overload (`open.cpp:1143`, `restore_entry`'s `failed` default) is a second door, so F4 is the load-bearing arm.
The fix moves H: m-1's and m-4's no-reds go stale, and all three reviews are retaken at the true final head, after any count-cell re-cut.
The fix paths are inside the 53 but outside impl-12's token, so a plan revision and a fresh dispatch are needed.
R-4.83 accepted as m-3 ruled it (the only-red census belongs in both branches); R-4.77 NOT-SHIFTED stands (Fisher p 0.47 / 0.58 / 1.00 / 1.00).
Next: rev39 — the MUST-H-1 fix as a new CODE task (tests first), its per-head gate, then Task 9 again at the new head (count gate, companion iff moved, FINAL H), with R-4.83's hoist and R-4.82's fence folded.
The release hold is ABSOLUTE.

## R84 — master's crossing correction; "lighter regate pls"; rev39 filed for review (2026-09-26 17:43 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-174349.md`; the operator's word; 18:29 PLAN `intg-substep2b/PLAN-pair-planner-20260926-182900.md`)

Master's 174349: my 17:05 SITREP crossed its 164725, so its ask was already discharged, and two of its statements were false as filed (a verbatim re-file of a 15:08 draft; the engine is 2.9.5 on the operator's word, and a 2.9.3 client cannot submit).
The correction lives in master's relay; mine stands as filed. Lesson saved: re-read every state claim before re-filing a stale draft, and cite an unadmitted relay by digest, never by a draft path.
The operator directed "lighter regate pls": Task 9 is not re-run. That changes R83's "Task 9 again at the new head".
rev39 `d5a868d3…` (4024 lines) is committed at `12ee0f9e` with its walk records (`results/rev39-walks/`) and the rev39 producer-gate baseline (`5a4f3620…`).
Task 8c is c10, the MUST-H-1 fix: tests RED first, F1–F4 with F4's `failed_rows_complete` returning a typed `InternalError`, three gating mutants, and the head gate at c10.
Task 9b (`regate.sh`) is the lighter re-gate at c10. It re-runs the censuses c10 could move, checks `failures=0`, the count gate against c9, both skip sets, E3 and `harness-e2`, and R-4.83's row census in both branches. The population must EQUAL Task 9's (a moved one STOPs and routes up; no series). c11 lands iff a count cell moved, and `R/H.txt` is written last.
`resume.sh` now carries Task 9's receipts. rev38's carried Task 0's only, which would have stopped Task 10 at its controller (walked both ways).
Disclosed: the `c10-mutants.sh` mutant arm is walkable only at the real c10.
plan-40 is filed TO the implementer for its exact-hash review (commit `8adc0a8`).
Next: the implementer's review; then my digest word to master, master's five-field carry, the `t-oracle.txt` rewrite in `s2b-runners-UG0MP0`, and impl-13 (Step 0′ → Task 8c → Task 9b); then the three owner reviews at the FINAL H, the GO, and Task 10.
The implementer's impl-12 return is still unadmitted (`457b14fa…`); only that seat can submit it.
The release hold is ABSOLUTE.

## R85 — rev39 must-revised (MUST-2B-53/54); the operator waives the 2.9.5 Plan contract for this plan; plan-41 re-carries rev39 (2026-09-26 18:59 review draft sha256 `ddb7cdc0…`, unadmitted; the operator's word `a`; 19:05 PLAN `intg-substep2b/PLAN-pair-planner-20260926-190529.md`; 19:06 SITREP `intg-substep2b/SITREP-pair-planner-20260926-190611.md`)

The implementer returned must-revise on rev39 `d5a868d3…`, with no design, scope, order or acceptance defect found in its declarations.
MUST-2B-54 was my defect: plan-40's grading heading still named rev38's `a342a9c5…`. It is fixed in plan-41.
MUST-2B-53: the 2.9.5 pair protocol's §Plan contract (new since 2.9.3; not in master's migration note) forbids implementation bodies, test bodies and operational scripts in a PLAN, and says execution does not bind snippet bytes. This plan is body-bearing by design, since its measurement tasks run byte-exact from the locked plan.
The operator chose (a), verbatim `a`: the contract's body clauses are waived for `PL-intg-substep2b-20260915` only, through sub-step 2b's close. The waiver covers all 21 named BLOCKs (including `c10-mutants.sh` and `regate.sh`), RUN blocks task-0/9/10/11 and the inline code of Tasks 1–8c. The contract applies from the next sub-step's plan.
rev39 is unchanged, so its walks stand. plan-41 carries it for the exact-hash verdict, and the SITREP asks master for the register row.
Both implementer drafts (impl-12 return `457b14fa…`, review `ddb7cdc0…`) are still unadmitted.
The release hold is ABSOLUTE.

## R86 — rev39 approved; the word for the fresh carry sent to master (2026-09-26 19:17 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260926-191703.md`; 19:22 SITREP `intg-substep2b/SITREP-pair-planner-20260926-192228.md`)

The implementer's seat submitted its three drafts once it used its current key (`68614683…`). Each filed relay is byte-identical to the draft digest I had reviewed: impl-12 return 191650 (`457b14fa…`), plan-review-39 191657 (must-revise, `ddb7cdc0…`), plan-review-40 191703 (approve, `ed732a71…`).
plan-review-40 approves rev39 `d5a868d3…` at 12ee0f9e under the operator's Plan-contract waiver, read narrowly (an override for this plan, not conformance, and no precedent), and closes MUST-2B-54.
The word to master (192228) carries the five T-ORACLE fields, with only the plan digest moved from 185232.
The prefix replay ran in scratch clones (bivpak a7c7b9b, pdc 42e8bd05): YES rc 0 with one receipt; carry-to and stale-digest each rc 1 with none. The three owner objects are tracked, unmodified and equal to 185232's digests.
The INDEX's pre-existing non-monotonic rows (including the migration back-fill at lines 582/584) fire `relay-lint --index`. They are not this seat's rows and not this seat's to repair.
Next: master's five-field carry TO intg.pair-planner, then the `t-oracle.txt` rewrite in `s2b-runners-UG0MP0` (predecessor kept), the prefix and R-4.72 gates on the real files, Step 0′ walked, the producer gate, and impl-13 at PARENT `intg-substep2b-plan-review-40` (SCOPE 53: Step 0′ → Task 8c → Task 9b, STOP before Task 10).
The release hold is ABSOLUTE.

## R87 — master's carry 203312 (+ addendum 203555); impl-13 dispatched (2026-09-26 20:33 / 20:35 `../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-203312.md`, `…-203555.md`; 20:47 IMPL `intg-substep2b/IMPL-pair-planner-20260926-204715.md`)

Master cleared T-ORACLE for rev39 (five fields; only the plan digest moved from 185232) and re-ran the gate on the filed carry itself (203555, carry sha256 `dbf5d9c3…`).
Master registered the operator's Plan-contract waiver, reading it to cover the snippet-byte-binding clause for this artifact through 2b ("narrow it if wider than meant").
Master corrected its migration note: 2.9.5 adds §Plan contract and §Delivery mode to every seat's protocol. Under 2.9.5, MUST-2B-54 (a carrier-only defect) could have ridden an `-erratum-N` with a delta review instead of a full re-carry; I use that path next time.
Master also pre-stated four items: the Task 9b population STOP is designed; the owner reviews retake at `R/H.txt`; the host-path coupling (15 absolute paths in the runner blocks) is due at the next sub-step's plan; the standing conditions are unchanged.
`t-oracle.txt` in `s2b-runners-UG0MP0` was rewritten from 203312 (sha256 `ccbec7ea…`); impl-12's file is kept as `t-oracle.prev-20260926-204313.txt` (`1910b60c…`).
From the candidate with scratch `$EVID`s: T-ORACLE prefix OK, and the preserved locator gives plan-sha-mismatch. R-4.72 is OK (owner words equal to the real c1d.pre receipt), and an eight-line carrier gives field-count-8.
Step 0′ was walked on a fresh mirror of the real runners directory: 31 carried lines, the six NO cases STOP, and the consumer reaches only the absent GO. The producer gate is rc 0 (52). All of Task 8c's and Task 9b's start fences are clean on the real home.
The lineage was walked on a mini-root: 0 lineage errors with the true parent, 2 with a wrong parent.
impl-13 (PARENT `intg-substep2b-plan-review-40`, SCOPE 53, all-in; EXPECTED rows = c10's ten Files-line paths, and c11 on the workflow count cells iff moved) runs Step 0′ → Task 8c → Task 9b, then STOPs before Task 10.
Next: the implementer's return. Then the three owner reviews at `R/H.txt`, my GO, and Task 10.
The release hold is ABSOLUTE.

## R88 — impl-13 STOPped in the c10 mutant gate; rev40 filed (2026-09-26 21:18 `intg-substep2b/IMPL-pair-implementer-20260926-211822.md`; 21:48 PLAN `intg-substep2b/PLAN-pair-planner-20260926-214841.md`)

impl-13: Step 0′ published `s2b-runners-r9Akl6` (31 carried lines). Task 8c Steps 0–4 ran red → green, and c10 `2291a46` was committed at exactly its ten paths.
Then `c10-mutants.sh` STOPped `survived-M-H1-PRE`. rev39 demanded a `divergence_envelope_conforms` failure under M-H1-PRE, but that consumer requires the `biv_tests` fixture and is `Not Run` whenever `biv_tests` fails.
Every mutant was killed (M-H1-PRE by (w1), M-H1-SCHEMA by the conforms row, M-H1-F4 by (w3)), measured from the retained logs. The defect is mine, in the one arm rev39 disclosed as unwalked.
rev40 `682ceb88…` (e86c891) has three block changes:
- `c10-mutants.sh`: each mutant is killed by the witness it names (CTest row statuses plus failed Catch2 cases by name), in `receipts/c10-mutants.rev40.txt` ending in `verdict=ok`; the rev39 record is kept, pinned by digest.
- `regate.sh`: reads that verdict. rev39's `[ -s ]` check would have admitted impl-13's FAILED record.
- `resume.sh`: binds Task 9's records by content. Found by walking Step 0′ for impl-14 from a mirror of `r9Akl6`: rev39's binding to the previous directory's token holds only for the first successor.
This time the mutant arm was walked FOR REAL, on a scratch clone at c10 with its own venv and build (7 min; `verdict=ok`), with ten NO cases served the real artifacts.
plan-42 is filed TO the implementer for the exact-hash review.
Next: review; then digest word, master carry, t-oracle in `r9Akl6`, and impl-14 (Step 0′ → Task 8c from Step 5 → Task 9b).
The release hold is ABSOLUTE.

## R89 — rev40 approved; the word for the fresh carry sent (2026-09-26 22:06 `intg-substep2b/PLAN-REVIEW-pair-implementer-20260926-220656.md`; SITREP `intg-substep2b/SITREP-pair-planner-20260926-221324.md`)

plan-review-41 approves rev40 `682ceb88…` at e86c891 under the registered waiver: the named mutant witnesses, the verdict-bearing regate and the content-bound resume.
The word to master carries the five T-ORACLE fields with only the digest moved from 203312. The prefix replay (bivpak 0a4cab4, pdc d9c0d298): YES rc 0 with one receipt; carry-to and stale-digest each rc 1 with none. The three owner objects are equal to 203312's digests.
Next: master's carry, then `t-oracle.txt` in `s2b-runners-r9Akl6` (predecessor kept), the gates, and impl-14 at PARENT `intg-substep2b-plan-review-41` (Step 0′ → Task 8c from Step 5 → Task 9b; STOP before Task 10).
The release hold is ABSOLUTE.

## R90 — master's rev40 carry received and verified; impl-14 HELD on m-3's F5 word (2026-09-26 22:23 master `PLAN-master-planner-20260926-222327.md` sha256 11e4c37e…; owner notice `PLAN-master-planner-20260926-222418.md` sha256 9367efc2…, pdc 7b8ef3c7)

The five T-ORACLE fields differ from 203312 only in `T_ORACLE_PLAN_SHA256`, which is `682ceb88…`, equal to the live plan. The three owner objects re-hash equal at pdc HEAD, and both relays are tracked and clean.
The prefix gate was run from the candidate against the real committed carry with scratch homes. YES `t-oracle OK` rc 0 with one receipt. The stale-digest control gave `plan-sha-mismatch`, the old-carry control (203312) `carry-plan-sha`, and the notice control (222418, TO m-3) `carry-to`; each rc 1 with no receipt. The candidate stayed clean.
Master routed m-3's F5 M-H1-PRE witness (the (w1) kill with `conforms=notrun`) to m-3 as an owner question, and said Task 8c Step 5's record is governed by that answer.
impl-14 would run Step 5 and write `receipts/c10-mutants.rev40.txt`, so I hold the dispatch until m-3's word arrives, rather than record a witness the owner may amend.
Nothing is written to `s2b-runners-r9Akl6` yet: an `amend` means rev41, and the `t-oracle.txt` rewrite would then bind a different digest.
On `accept`: the t-oracle rewrite (carry 222327), the gates, then impl-14 as in R89. On `amend`: a rev41 that folds m-3's witness into Step 5, then review and a fresh carry.
The release hold is ABSOLUTE.

## R91 — m-3's F5 accept in; impl-14 issued (master `PLAN-master-planner-20260926-223404.md` sha256 7a424f0e… carrying m-3 `DESIGN-planner-20260926-222938.md`; IMPL `intg-substep2b/IMPL-pair-planner-20260926-224119.md` sha256 56f3a38a…)

m-3 answered `F5_M_H1_PRE: accept` (one whole line; FROM m-3.planner, TO master, IN_REPLY_TO 222418). Master re-derived m-3's four schema cells at c10 and carried the word down: Step 5 records exactly as rev40 writes it, with no plan change and no re-carry.
`s2b-runners-r9Akl6/t-oracle.txt` was rewritten from carry 222327 by a staged file renamed into place (sha256 621c5988…, mode 0400). impl-13's file is preserved byte-identical as `t-oracle.prev-20260926-223546.txt` (ccbec7ea…).
Gates on the real files from the candidate at 2291a46, with scratch `$EVID`s:
- the prefix passes (`t-oracle OK`); the carry-to and stale-digest controls STOP with no receipt;
- R-4.72 `c1d pre`, `c1d post` and `c7 pre` pass; the eight-line control gives `field-count-8`.
(A first `c7`-only run STOPped `anchor-absent`. That was my harness skipping the plan's c1d-first order, not a gate defect.)
The rev40 `resume.sh` walk from fresh mirrors of r9Akl6 publishes 31 lines, and 20 without Task 9. The eight NO cases STOP with no new directory and the pointer untouched, and nothing was left behind.
The producer gate is rc 0 (52 classified). The start fences on the real home hold: the rev40 record and work directory, `heads/c10`, `heads/c11`, `commits.c11.txt` and `R/` are absent, and impl-13's rev39 record and work directory are present.
impl-14 was issued at PARENT `intg-substep2b-plan-review-41`: Step 0′ → Task 8c Steps 5–7 at c10 → Task 9b → STOP before Task 10. The lineage was walked on a mini-root: 0 lineage errors with the true parent, and the two expected ones with plan-42 as the parent.
The release hold is ABSOLUTE.

## R92 — impl-14 STOPped at c10's canonical Linux build; rev41 filed as plan-43 (impl-14 return `intg-substep2b/IMPL-pair-implementer-20260926-231301.md` sha256 779bff88…; PLAN `intg-substep2b/PLAN-pair-planner-20260927-001730.md` sha256 7d56aded…)

impl-14 ran Step 0′ (published `s2b-runners-dv8k9v`) and Task 8c Step 5: `receipts/c10-mutants.rev40.txt` ends in `verdict=ok`, each mutant killed by its named witness. Step 6's one head gate at c10 then STOPped in the canonical Linux container on GCC 13 `-Werror=missing-field-initializers` at c10's two new failed-row test initializers (`tests/test_envelope.cpp:75`, `:85`) — c8L's class re-introduced.
The miss is shared. The plan checked c10 green on macOS only, and I issued impl-14 without scouting c10 on the canonical Linux toolchain, which my standing rule requires before a gate token.
The scout was measured before any plan byte (`results/c10t-scout-20260926/`, dbea9b75): the retained log's error lines are exactly the 18, and c10 plus repair-13 passed the WHOLE canonical container (tidy 0 at 37/37, only harness-selftest red, population EQUAL to Task 9's 1055). macOS tuples equal c10's, and the mutant record reproduces impl-14's rows.
rev41 `0140f69e…` (df0b928) adds NEW Task 8d, c10t on `tests/test_envelope.cpp` only: the RED is taken from the retained log, repair-13 is pinned with the tree pinned before the commit, and the mutant record and head gate are re-taken at c10t. `regate.sh` and Task 10 are retargeted to c10t.
It also folds a latent rev39 defect found by tracing Task 10's inputs. Task 0's sealed `finalize.py` (`helpers.sha256`) made rev39's edits dead: the sealed PR body lists 6 of 24 commits and omits the veto-9 engine commits. Task 10 now produces `finalize.rev41.py` beside it with the rev37 pattern.
Walks are in `results/rev41-walks/`, with every invalid run named. The producer baseline is rev41 (`e34d8895…`, 54). Host touch: one stray append to the main repo's `.git/info/exclude` (a relative git-dir), removed exactly.
Next: the implementer's exact-hash review of plan-43, then the digest word, master's carry, `t-oracle.txt` in `s2b-runners-dv8k9v`, and impl-15 (Step 0′ → Task 8d → Task 9b).
The release hold is ABSOLUTE.

## R93 — plan-43 APPROVED; the rev41 digest word sent (PLAN-REVIEW `intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-003803.md`, `intg-substep2b-plan-review-43`; SITREP `intg-substep2b/SITREP-pair-planner-20260927-004149.md` sha256 bb2ede69…, commit 14fe54c)

The implementer approved rev41 `0140f69e…` at the exact hash. 003803 supersedes its own duplicated-body 003628, with the same verdict, and records the operator's registered Plan-contract waiver as covering rev41.
The word asks master for the five-field carry TO intg.pair-planner. Only `T_ORACLE_PLAN_SHA256` moves from 222327. The three owner-object lines are byte-identical to 222327's and were re-hashed at pdc 5138396e at filing.
The T-ORACLE prefix replayed at the new digest in scratch clones (bivpak 72c4875, pdc 5138396e, synthetic committed carries). YES: rc 0, one receipt. Widened TO: `STOP-t-oracle carry-to`, no receipt. rev40 digest: `plan-sha-mismatch`, no receipt.
The word's commit carried both 003628/003803 INDEX rows (the known shared-INDEX sweep; the daemon wrote them, none hand-edited).
Next: master's carry, then `t-oracle.txt` rewritten in `s2b-runners-dv8k9v` (predecessor kept), the gates walked on the real files, and impl-15 at PARENT plan-review-43 (Step 0′ → Task 8d → Task 9b → STOP before Task 10).
The release hold is ABSOLUTE.

## R94 — master's rev41 carry verified; impl-15 issued (master `PLAN-master-planner-20260927-004908.md` sha256 24a4d933…, pdc d76f09e8; IMPL `intg-substep2b/IMPL-pair-planner-20260927-005826.md` sha256 2cb8d637…, commit 8800f7e)

The carry is tracked and clean, TO intg.pair-planner. Only `T_ORACLE_PLAN_SHA256` moves from 222327 (to `0140f69e…`); the three owner-object lines re-hash equal.
Master also censused the sealed-helper class over all fifteen `helpers.sha256` rows: thirteen byte-identical to their rev41 blocks, and exactly two drifted (`finalize.py`, `series_verdict.py`), both routed through a beside-copy. I re-ran the comparison at issuance with the same result, and every home copy equals its seal.
`s2b-runners-dv8k9v/t-oracle.txt` was rewritten from carry 004908 by a staged file renamed into place (sha256 8e3fbe3a…, 0400). impl-14's file is preserved byte-identical as `t-oracle.prev-20260927-005250.txt` (621c5988…, 0400).
Gates on the real files from the candidate at 2291a46, with scratch `$EVID`s:
- the prefix passes with one receipt; the stale-digest, old-carry (222327) and notice (222418) controls STOP `plan-sha-mismatch`, `carry-plan-sha` and `carry-to`, with no receipt;
- R-4.72 `c1d pre`, `c1d post` and `c7 pre` pass, and the eight-line control gives `field-count-8`.
The `resume.sh` walk from fresh mirrors of dv8k9v, with the real locator unedited, publishes 31 lines, and 20 without Task 9. Nine NO cases STOP with no new directory and the pointer untouched; the new one puts the rev40-digest predecessor back and gets `t-oracle-stale`.
The producer gate is rc 0 (54 classified, rev41 baseline). The start fences on the real home hold: every c10t, c11 and `R/` name is absent, and Task 8c's rev40 record and `heads/c10/` (build log 6b0c66e5…) are present.
impl-15 was issued at PARENT `intg-substep2b-plan-review-43`: Step 0′ → Task 8d → Task 9b → STOP before Task 10. On the mini-root, the true parent gives 0 lineage errors and plan-43 as the parent gives the three expected ones.
The first submit refused `E-ID-COLLISION` because I again passed `--admits-against` for a new id (the same slip as the PLAN filing noted earlier in this file). Nothing was admitted; the resubmission without the flag filed bytes equal to the draft by digest.
The release hold is ABSOLUTE.

## R95 — impl-15 returned green at FINAL H cb19326a; owner re-reviews asked of master (return `intg-substep2b/IMPL-pair-implementer-20260927-021356.md` sha256 b64e85a4…; SITREP `intg-substep2b/SITREP-pair-planner-20260927-022041.md` sha256 3923adea…, commit 8a2db62)

impl-15 ran Step 0′ (`s2b-runners-j6w4EX`, 31 carried lines), Task 8d and Task 9b once each, then STOPped before Task 10 as dispatched.
Verified at my seat:
- c10t `b303950` is repair-13 on `tests/test_envelope.cpp` only, at the pinned tree `36331eb0`.
- Its mutant record (`725ee7fd…`) ends in one `verdict=ok` and is byte-identical to the rev40 record.
- Both head gates are green: tidy 0, 37/37, container rc 0, 0 failures.
- Task 9b's count gates moved (code 5), so c11 `cb19326` changed only the two `biv_tests` successes cells (macOS 484 → 486, Linux 486 → 488; Linux 488 is the scout's number).
- Every final `R/` receipt is rc 0: both count gates, E3 Linux, both `harness-e2`, the population EQUAL (1055 = 1055), and the Linux skipset.
- `R/H.txt` names cb19326a; the candidate is clean, 26 past B, unpushed.
The SITREP asks master to re-route the three owner byte reviews at cb19326a, with the same `S2B_REVIEW_*` lines and traps; the 2893bc53 reviews are stale (m-1 and m-4 no-red; m-3 must-revise, answered by c10). It names the scope delta since 2893bc53: c10's MUST-H-1 hunks, c10t and c11.
Next: the three reviews through master, then my Task 10 GO relay (`TASK10_GO: yes`, `TASK10_H: cb19326a…`, three `OWNER_REVIEW_H:` lines, master's standing conditions).
The release hold is ABSOLUTE.

## R96 — master ACCEPTED Task 9b at FINAL H cb19326a; owner reviews routed; F-H1-DOOR2 registered (master `PLAN-master-planner-20260927-032725.md` sha256 ba4385fd…, pdc 280fe84c)

`TASK_9B: accepted`. Master re-measured the chain, both boundaries and all six cited digests.
- He re-derived c11 from the sealed `cellpatch.py` and c10t's tuples: byte-identical to c11's workflow blob (`da599e34…`), with a c8T-tuple control differing in exactly the two cells. So the workflow at H differs from the base only in cell literals.
- c10t's tree equals rev41's pre-computed pin.
- veto 9 over `186adf7d..H`: 26 commits, six engine commits, zero spanning.
- The ctest row set at H equals c8T's plus exactly the two MUST-H-1 conformance rows, with the same fail/notrun triple.
Two notes for the record:
- The c10t mutant receipt equals the rev40 record because the format carries no timestamp; its freshness is its write time and the c10t-vintage logs.
- The R-4.35 family failed 4 names at c10t and 3 at c11 (a workflow-only commit): R-4.77 variance, recorded as data. `R/linux-selftest-bar.txt` is c10t-vintage, and the empty `R/c10t-H.delta` compares count cells, not selftest names.
F-H1-DOOR2 (under m-3, m-1 CC): MUST-H-1's invariant is gated at the envelope (open.cpp:1309, exit 4) but holds at the failed inventory (`write_failed_inventory`, which substitutes `value_or`) only by construction. c10 fixed the divergence-refused row at its producer, so the inventory is correct at H. It has no schema, consumer or composition witness. Master registered it as not a red and seeks no change in this scope (it is sealed ADDENDUM 11 text).
The owner reviews are asked at H in `032730` (m-1), `032734` (m-3) and `032738` (m-4). None has arrived yet.
Next: collect the three no-red reviews, walk the GO against Task 10's Step 1 gate lines, then file the GO SITREP (`TASK10_GO: yes`, `TASK10_H: cb19326a…`, three `OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/<file> | FROM=m-N.planner | VERDICT=no-red` lines).
The release hold is ABSOLUTE.

## R97 — the three owner no-reds in at H cb19326a; the Task 10 GO filed (master `PLAN-master-planner-20260927-040214.md` sha256 3519ce0c…; GO `intg-substep2b/SITREP-pair-planner-20260927-043411.md` sha256 d9eb0f9b…)

The reviews: m-1 `DESIGN-planner-20260927-033430.md`, m-3 `DESIGN-planner-20260927-033409.md` and m-4 `DESIGN-REVIEW-planner-20260927-033613.md`. Each is `no-red`, tracked and clean, and passes every Task 10 per-file predicate at my seat with zero red lines.
Master's 040214 replayed the owner-set gate. It also corrected two points of his own trace: `render.cpp:301` is a session-row printer, and the envelope renders `sha`/`capture_mode` null by schema.
R-4.85's arms, consolidated across m-1, m-3 and m-4, are for a future ADDENDUM 11 scope and hold nothing.
The GO carries `TASK10_GO: yes`, `TASK10_H: cb19326a…` and the three `OWNER_REVIEW_H:` lines verbatim from 040214. It was walked through Task 10's own Step 1 lines (block 39–66) on a scratch mirror before filing.
- YES passes.
- The NO cases each STOP at the intended line: relative path (40), relay not in INDEX (43), stale `TASK10_H` (45), an owner line dropped or duplicated (47), m-3's stale must-revise review (60).
- After filing, the filed bytes (equal to the draft) pass the same lines against the real root and INDEX. The receipts Step 1 reads next (lines 67–69) pass on the real home.
Two facts the GO states for the operator and the implementer:
- The typed path must be ABSOLUTE. The controller would accept a relative one, but the runner `cd`s into the worktree first, so line 40 STOPs.
- Task 10 continues under impl-15's runners (`j6w4EX`, token-id impl-15), because `resume.sh` STOPs `same-lock` on an unchanged plan. The runner records land under that token by design (line 593). The GO invites the implementer to STOP up if it reads the authority as short.
Next: the operator's typed act into `/Users/jack/Programming/bivpak-evidence/s2b-runners-j6w4EX/task-10-go.txt`, then Task 10 (ONE push, ONE draft PR), then the return.
The release hold is ABSOLUTE.

## R98 — the operator waived the typed act; `task-10-go.txt` written by this seat (notice `intg-substep2b/SITREP-pair-planner-20260927-043806.md` sha256 8c5b3bed…, commit 5950186)

The operator's word, verbatim (2026-09-27): "just cite it, you dont need my typed ack".
`s2b-runners-j6w4EX/task-10-go.txt` was created (none existed; a staged file renamed into place) with one line, the GO 043411's absolute path, mode 0400, sha256 86890681….
The controller's continuation check (plan line 3604) and Task 10's Step 1 GO/owner lines (block 39–66) both pass on the real file.
The notice records the waiver for the implementer. The GO is unchanged except for its release condition.
Next: the implementer runs Task 10 once (ONE push, ONE draft PR) and returns.
The release hold is ABSOLUTE.

## R99 — Task 10's first attempt STOPped at the controller's entry guard (no write, no remote act); successor GO filed with the exact invocation (return `intg-substep2b/IMPL-pair-implementer-20260927-044136.md` sha256 902851f6…; GO `intg-substep2b/SITREP-pair-planner-20260927-044557.md` sha256 86219667…)

The implementer ran `./run-task.sh 10` once from the runners directory. The controller's line 7 requires `$0` to be exactly the absolute `$RUNNERS/run-task.sh`, so it STOPped `controller-invoked-off-path` before its first write (`plan-hash-10.txt`, line 10, absent) and before any remote probe. The implementer did not retry or reinterpret.
The defect is mine. My GO 043411 said "runs `run-task.sh 10` ONCE from that runners directory". I walked Task 10's gate lines and the controller's continuation check, but not the controller's entry line, so the relative form went unwalked.
The successor GO gives the exact invocation `/Users/jack/Programming/bivpak-evidence/s2b-runners-j6w4EX/run-task.sh 10`. Walk results:
- The controller's lines 1–7, run on a mirror, pass for the absolute path (direct and via `bash`, from `/`), and STOP for `./run-task.sh` and a bare `run-task.sh`.
- The gate lines pass YES and all six NO cases on the successor's bytes.
The GO cites the operator's standing authorization (043806); the first attempt never reached Task 10.
`task-10-go.txt` was re-cited to 044557 (809eec72…, 0400), the predecessor preserved as `task-10-go.prev-20260927-044608.txt` (86890681…). The continuation check and the gate lines pass on the real file.
Next: Task 10 once by the exact invocation (ONE push, ONE draft PR), then the return.
The release hold is ABSOLUTE.

## R100 — Task 10 (successor) STOPped at the live visibility preflight: the repository is PUBLIC, the gate requires PRIVATE; no push or PR (return `intg-substep2b/IMPL-pair-implementer-20260927-045007.md` sha256 1def0e50…)

The exact absolute invocation ran once. The controller authenticated and materialized Task 10 (`task-10.sh` 7f6069cd…), and the GO, owner set, final receipts, pinned push URL and remote-branch-absent checks all passed.
Line 73's `gh repo view --json visibility` then succeeded and returned `PUBLIC` (`visibility.txt` 8527237a…), so the `= PRIVATE` predicate STOPped as designed.
It stopped before the pre-push hook check, the dry-run, the push and the PR. None of their receipts exists; the candidate is clean at cb19326a, with no upstream.
Consequence: `task-10.exit` (rc=1) and `task-10.sh` now exist in `s2b-runners-j6w4EX`, so the controller's one-shot fence (line 19) refuses a re-run there. `resume.sh` refuses a new runners directory on the unchanged lock (`same-lock`). Any continuation therefore needs a plan revision (rev42), whatever the visibility decision.
Pushing the candidate to a PUBLIC repository would publish unreleased code, which the release hold and the plan's PRIVATE predicate both exclude. This is the operator's decision; it has been put to the operator. No relay has been filed yet.
The release hold is ABSOLUTE.

## R101 — the operator chose to publish ("2"); rev42 filed as plan-44 (plan `37ca6530…` at 78e87b3; PLAN `intg-substep2b/PLAN-pair-planner-20260927-144310.md`, commit fba3011)

The operator's word, verbatim (2026-09-27): "2": keep the repository public and publish the branch. That discharges the charter's operator-gated publication act (charter rev3 :54) for this push. The undraft, the merge and release stay the operator's.
Measured before any plan byte:
- GitHub's `main` is B (`git ls-remote`, a read), so the push adds exactly the 26 B..H commits.
- All 26 carry `@local` placeholder identities.
- The census alternation has 0 hits in the B..H patches. The H tree's 40 hit files are identical at B, all the `sk-complete` false positive, already public.
- The real PR body from `finalize.rev41.py` has 0 hits and no local path. Its `H0=H0=` line is cosmetic, left unfixed so the sealed helper does not drift.
rev42 changes Task 10 only:
- Step 0 preserves a prior attempt by rename into `attempts/task10-<k>/` (manifest-verified) and STOPs on any push/PR receipt.
- Visibility accepts `PRIVATE` or `PUBLIC`.
- The exposure census runs before the dry-run.
- Protocol (e) records the typed-act waiver and the absolute invocation.
Walked (`results/rev42-walks/`, the invalid run named). The producer gate is rc 0 against the unchanged rev41 baseline, and `check` passes for tasks 0, 9, 10 and 11.
One slip: the exposure scout wrote two file-list temp files under `/tmp` rather than the scratchpad; they were deleted.
Next: the implementer's exact-hash review. Then the digest word, master's carry, `t-oracle.txt` and `task-10-go.txt` in `s2b-runners-j6w4EX` (predecessors kept), and impl-16: Step 0′ → Task 10 via `"$RUNNERS"/run-task.sh 10` → return.
The release hold is ABSOLUTE.

## R102 — rev42 MUST-REVISE (plan-review-44: MUST-2B-55, MUST-2B-56) folded as rev43; filed as plan-45 (plan `096e47b4…` at e8b3ab2; PLAN `intg-substep2b/PLAN-pair-planner-20260927-154540.md`, commit 1776056)

The implementer's review (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-151814.md`) accepted the operator's "2" and found two runner-contract defects.
MUST-2B-55: the census read the fetch side of `origin` while the push wrote the push side; a split remote passed every gate.
MUST-2B-56: Step 0 omitted impl-15's `finalize.rev41` pyc, and rev42's `py_compile` rewrote it; the prose overclaimed "before any `$EVID` write".
rev43 changes Task 10 only:
- One destination: `URL`/`REPO` pinned; exact fetch-URL, no-`url.*`-rewrite and push-URL gates before any remote read; every `ls-remote`, the dry-run, the push, the post-push classifier and both `gh` calls name it.
- Step 0 moves any `__pycache__/finalize.rev41.*.pyc` (regular files only) with the attempt; the syntax check compiles in memory.
- The prose states the body-receipt boundary and `finalize.rev41.py` as the shared, digest-pinned helper that stays in place.
Walked (`results/rev43-walks/`): destination YES on the real candidate, and NO for split fetch/push, `insteadOf`, `pushInsteadOf` and an env-injected rewrite, each stopping before any remote read.
Retention was walked on a full clone of the real `$EVID`: the pyc moves byte-equal and no pyc is written; the rev42 `py_compile` control writes one.
The producer gate is rc 0 against the rev41 baseline, and `check` passes for tasks 0, 9, 10 and 11.
Two slips, both named in the records:
- The first retention run used a hand-picked file subset and stopped before the compile line, so its reading was void; it was superseded by the full-clone run.
- The inline diff could not be carried because a context line is a fence marker, so it is committed as `rev42-to-rev43.diff` (eb4a711) and cited by digest.
The `GH_REPO` control did not red (the unqualified `gh repo view` also returned PUBLIC); this is recorded, not claimed as a demonstrated exposure.
Next: the implementer's exact-hash review of rev43. Then the digest word, master's carry, `t-oracle.txt` and `task-10-go.txt` in `s2b-runners-j6w4EX` (predecessors kept), and impl-16.
The release hold is ABSOLUTE.

## R103 — rev43 MUST-REVISE (plan-review-45: MUST-2B-57) folded as rev44; filed as plan-46 (plan `7d55f0b8…` at 2c795a2; PLAN `intg-substep2b/PLAN-pair-planner-20260927-163504.md`, commit ce42f81)

The implementer's review (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-162852.md`) closed MUST-2B-55 and MUST-2B-56 and found one more destination gap.
MUST-2B-57: rev43 gave `gh` only `OWNER/REPO`, and `GH_HOST` supplies the host when none is given, so the visibility read and the draft PR could reach a different host from the literal git push.
rev44 changes one Task 10 runner line: `REPO=github.com/iwnlcern/bivpak`, used by both `gh` calls; the prose, acceptance item 18 and the history follow.
Walked (`results/rev44-walks/`): under an injected `GH_HOST`, rev44 reads PUBLIC from github.com, and the rev43 control follows the injected host and STOPs.
`gh pr create` was not run (a write, and its dry-run may push); its `--repo` takes `[HOST/]OWNER/REPO`.
The producer gate is rc 0 against the rev41 baseline, and `check` passes for tasks 0, 9, 10 and 11.
My miss: rev43 pinned the git host but left the `gh` host to the environment, so the one-destination contract covered only one of its two clients.
Next: the implementer's exact-hash review of rev44. Then the digest word, master's carry, `t-oracle.txt` and `task-10-go.txt` in `s2b-runners-j6w4EX` (predecessors kept), and impl-16.
The release hold is ABSOLUTE.

## R104 — rev44 APPROVED (plan-review-46); the digest word sent to master (SITREP `intg-substep2b/SITREP-pair-planner-20260927-173226.md`, commit 9c4b38f)

The implementer approved rev44 `7d55f0b8…` (2c795a2) at the exact hash (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-163843.md`) and confirmed MUST-2B-55, -56 and -57 closed.
The word asks master for a fresh carry of the five T-ORACLE fields TO intg.pair-planner, with only the plan digest moved from 004908.
The T-ORACLE prefix (`1c437ac4…`, byte-present once in rev44) was replayed in scratch clones at the new digest: YES `t-oracle OK` with one receipt; `carry-to` and stale-digest NO cases STOP with no receipt.
The three owner no-reds at H `cb19326a` (master 040214) still bind: H has not moved.
Next, on the carry: preserve and rewrite `t-oracle.txt` in `s2b-runners-j6w4EX`; file a fresh GO and re-cite `task-10-go.txt`; issue impl-16 at PARENT plan-review-46 (Step 0′ → Task 10 once via `"$RUNNERS"/run-task.sh 10` → return).
The release hold is ABSOLUTE.

## R105 — master's carry 181059 consumed; fresh Task 10 GO filed; impl-16 ISSUED (GO `intg-substep2b/SITREP-pair-planner-20260927-202731.md`, token `intg-substep2b/IMPL-pair-planner-20260927-203134.md`, commits 4f8f4cd, c415ed8)

Master's `PLAN-master-planner-20260927-181059.md` cleared T-ORACLE for rev44 `7d55f0b8…` and re-measured the exposure independently (26 commits, 55 product files, two `@local` identities, zero secret or host-path hits, nothing under `docs/` or `.relays/`); it reproduced MUST-2B-57's control on both forms.
Its §4 notes that the operator's bare "2" is recorded only through my restatement of the question; master re-gates nothing, and the GO and the token surface it to the operator (CC) before the push.
In `s2b-runners-j6w4EX`, `t-oracle.txt` (→ `t-oracle.prev-20260927-202507.txt`) and `task-10-go.txt` (→ `task-10-go.prev-20260927-202744.txt`) were preserved by rename and rewritten (0400).
Walked before issuance (`results/rev44-walks/`): the real T-ORACLE prefix on the published file (OK); Step 0′ from a mirror of the real runners (32 carried lines, no task-10 records; the stale-oracle control STOPs unpublished); Task 10's GO gate on the filed GO (OK; the no-GO-lines control STOPs); the three-relay mini-root lineage walk with a wrong-parent control.
One slip: the first GO-gate run omitted the prologue's `PIPEOK`, so it proved nothing; it was superseded by a run with the prologue's functions.
impl-16 = Step 0′ on the rev44 lock, then Task 10 ONCE via `"$RUNNERS"/run-task.sh 10` (ONE push to `https://github.com/iwnlcern/bivpak.git`, ONE draft PR on `github.com/iwnlcern/bivpak`), then return; no commit under the token.
Next: impl-16's return (the PR URL and the remote head). The undraft, the merge and the release stay with the operator.
The release hold is ABSOLUTE.

## R106 — Task 10 COMPLETE (impl-16: FINAL H pushed once, class a; draft PR #28); the pre-token Task 11 walk found a census-producer defect; rev45 filed as plan-47 (plan `bd2d21f5…` at 31a6123; PLAN `intg-substep2b/PLAN-pair-planner-20260927-221259.md`, commit 8e45baf)

impl-16's return (`intg-substep2b/IMPL-pair-implementer-20260927-213948.md`) was verified at my seat: task-10 rc 0, push class a, remote `intg/substep2b-wiring` == H `cb19326a`, remote `main` == B, PR https://github.com/iwnlcern/bivpak/pull/28 OPEN and DRAFT at H, the candidate clean.
Before issuing a Task 11 token I walked its body on a full clone of the real evidence home: the census rehearsal STOPs `tree-delta` at H0. The sealed Task 0 producer (`git grep -n -o`, one row per match) and the pinned instrument (`git grep -n`, one row per line) disagree on 3 lines holding two matches; the sets are identical.
The landing census would have STOPped the same way at the merge head.
rev45 fixes the `census_population.sh` block (one row per line, first match) and has Task 11 produce `census_population.rev45.sh` beside the sealed copy, pinned `0c7124d7…` (the rev41 finalize pattern); the population and the landing declaration use it.
Walked (`results/rev45-walks/`): the fix PASSes the pinned instrument at H0 and H; the derived rev45 Task 11 body runs rc 0 on a clone (finalize check rc 0; 2,329 files); tampered and symlinked beside-copies STOP. Producer gate rc 0 on the new `baseline-substep2b-rev45.txt` (rev41's plus two classified rows).
My miss: the plan pinned the producer to the instrument without running the pair on this repository's real tree; the consumer-without-producer mirror form again, this time caught before a token.
Next: the implementer's exact-hash review of rev45; then the digest word, master's carry, `t-oracle.txt` in `s2b-runners-V1jS1t`, and impl-17 (Step 0′ → Task 11 once → return). PR #28's undraft, the merge and the release stay with the operator.
The release hold is ABSOLUTE.

## R107 — rev45 APPROVED (plan-review-47); the digest word sent to master (SITREP `intg-substep2b/SITREP-pair-planner-20260927-224915.md`, commit 31633c7)

The implementer approved rev45 `bd2d21f5…` (31a6123) at the exact hash (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-224421.md`) and independently re-ran the fixed producer against the pinned instrument at H0 and H: PASS.
The word reports Task 10 complete (PR #28 draft at H) and the census-producer fold to master, whose instrument is untouched, and asks for the five T-ORACLE fields with only the plan digest moved from 181059.
The T-ORACLE prefix replay at `bd2d21f5` in scratch clones: YES with one receipt; `carry-to` and stale-digest NO with none.
Next, on the carry: preserve and rewrite `t-oracle.txt` in `s2b-runners-V1jS1t`; issue impl-17 at PARENT plan-review-47 (Step 0′ → Task 11 once → return).
The release hold is ABSOLUTE.

## R108 — master's rev45 carry 231805 consumed; the next token's handoff walk found resume.sh never carries Task 10's receipts; rev46 filed as plan-48 (plan `86f0f7d3…` at 885e754; PLAN `intg-substep2b/PLAN-pair-planner-20260928-011122.md`, commit 21cb42f)

Master's `PLAN-master-planner-20260927-231805.md` carried T-ORACLE at rev45, verified Task 10 at the published objects, ruled the census-producer fold correct as the instrument's owner (three mutants; one residual registered: at a multi-match line only the first match's class is recorded), and asked impl-17's return for the declaration lines verbatim and the rehearsal's H0 numbers.
`t-oracle.txt` in `s2b-runners-V1jS1t` was rewritten to 231805 (predecessor `t-oracle.prev-20260928-010712.txt`); the real prefix passed on it.
Walking impl-17's handoff (Step 0′ from a mirror of the real runners, then the sealed controller `run-task.sh 11`) STOPped at the controller's predecessor check (line 16): `resume.sh` carried Task 0's and Task 9's receipts but never Task 10's.
rev46 changes `resume.sh` only (`c325718c…` → `e0b5eed5…`): Task 10's eleven receipts bound and carried as rev39 did Task 9's. Walked (`results/rev46-walks/`): YES through the controller into Task 11's prologue (43 carried lines); four NO cases in pre-flight; the no-Task-10 regression.
My miss: rev45's walks ran Step 0′ and the Task 11 body separately and never the controller between them.
Next: the implementer's exact-hash review of rev46; the digest word; master's fresh carry; `t-oracle.txt` rewritten again; impl-17.
The release hold is ABSOLUTE.

## R109 — rev46 APPROVED (plan-review-48); the digest word sent to master (SITREP `intg-substep2b/SITREP-pair-planner-20260928-012153.md`, commit 6290753)

The implementer approved rev46 `86f0f7d3…` (885e754) at the exact hash (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-012006.md`), independently adding a `task-10-without-task-9` control, and noted the real oracle correctly still names rev45 until master's fresh carry.
The T-ORACLE prefix replay at `86f0f7d3` in scratch clones: YES with one receipt; `carry-to` and stale-digest NO with none.
Next, on the carry: preserve and rewrite `t-oracle.txt` in `s2b-runners-V1jS1t`; issue impl-17 at PARENT plan-review-48 (Step 0′ with 43 carried lines → `"$RUNNERS"/run-task.sh 11` once → return with master's two 231805 conditions).
The release hold is ABSOLUTE.

## R110 — master's rev46 carry 012951 consumed; impl-17 ISSUED (token `intg-substep2b/IMPL-pair-planner-20260928-014937.md`)

Master's `PLAN-master-planner-20260928-012951.md` carried T-ORACLE at rev46, confirmed by the plan's own extractor that rev46 is `resume.sh` only, measured the Task 10 owner search at n=1 (impl-16), hit the t-oracle ordering fence for real on a mirror, and added a third return condition (the carried-line count and the owner token).
`t-oracle.txt` in `s2b-runners-V1jS1t` was rewritten to 012951 (rev45's file kept as `t-oracle.prev-20260928-014723.txt`); the real prefix passed on it.
Pre-token handoff walk on the REAL state (`results/rev46-walks/w46real.*`, commit 3140314): Step 0′ 43 carried lines, owner `intg-substep2b-impl-16`; the sealed controller proves Task 11 and runs its prologue; the body STOPs only at a deliberately tampered helper. Producer gate rc 0 on the live plan.
impl-17 = Step 0′ on the rev46 lock → `"$RUNNERS"/run-task.sh 11` once (local: the H0 rehearsal with `census_population.rev45.sh`, the landing declaration, the results record written uncommitted into the docs lane) → return with master's three conditions.
Next: impl-17's return. PR #28's undraft, the merge token and the release stay with the operator.
The release hold is ABSOLUTE.

## R111 — impl-17 returned rc0: TASK 11 COMPLETE; reported to master (`intg-substep2b/SITREP-pair-planner-20260928-021758.md`)

The implementer's `IMPL-pair-implementer-20260928-021324.md` returned rc 0: Step 0′ published `s2b-runners-fr9fJW`, then Task 11 ran once.
Re-measured at this seat, not copied from the return:
- `carried.sha256` has 43 lines and `shasum -c` over them returns 0; `task-11.exit` and `task-11.done` read rc=0.
- `H/census-rehearsal.rc` is 0, and exactly one rehearsal line ends in `result=PASS` (81 rows, A=3 B=76 C=2, H0 as history ref).
- The declaration's two lines name `census_population.rev45.sh` at 0c7124d7 and the instrument at 9c9391d5.
- `results/s2b-intg-substep2b-impl-1/` holds 2,342 files plus `SHA256SUMS`, and `shasum -c` over it returns 0.
- The rev45 walk predicted 2,329 files; a sorted-list comparison finds exactly 13 more in the real set and none missing. All 13 are impl-17's Step 0′ and token-directory records.
- Remote `main` is at B and the branch at H; PR #28 is an OPEN draft; the candidate is clean.
The record stays untracked, as the plan orders; Task 12 adds `landing-census.txt` and seals it after the merge.
Next: the operator undrafts PR #28 and files the bare merge token under `.relays/intg`; Task 12 (landing census on the merge head, worktree disposal, closure SITREP) follows.
The release hold is ABSOLUTE.

## R112 — master ACCEPTED Task 11 (`PLAN-master-planner-20260928-023917.md`); R-4.88 opened for the operator; sequencing gap reported (`intg-substep2b/SITREP-pair-planner-20260928-024612.md`)

Master re-measured all three conditions and the +13 reconciliation, and placed one Task 12 condition under any option: commit the record by explicit path, with the file count and `SHA256SUMS` digest stated in the receipt. Accepted.
R-4.88 (operator): publish the 2,343-file record? (a) publish with precedent (master's recommendation), (b) keep local, (c) reduced record.
The gap, reported to master: under rev46, (a)'s "rides the landing push" is unreachable, because Task 12 starts after the merge head is on main (after the push) and the plan never pushes main. Also, Task 12's `landing-census.txt` inside RESDIR makes `finalize.py check` fail against the sealed manifest 187a1a10.
Forms: (a1) commit the 2,343 paths pre-landing by explicit path and write the census beside the record (recommended); (a2) re-seal plus a second authorized push. The census-outside-RESDIR change is needed under any option, which means a rev47 Task 12 byte before the token.
Next: the operator's option word and sequencing form (via master), then rev47, then the implementer's exact-hash review, then the undraft and bare merge token. The release hold is ABSOLUTE.

## R113 — the operator's R-4.88 word is (b), keep the record local (master `PLAN-master-planner-20260928-024840.md`); rev47 filed as plan-49 (`intg-substep2b/PLAN-pair-planner-20260928-032237.md`)

Arm (b): the 2,343-file record is never committed and is cited by `SHA256SUMS` 187a1a10…, 2,342 rows and 2,343 files. Master's 023917 §5 is superseded by a single no-commit predicate (`git ls-files` on the record path must be empty).
rev47 `32c93d2a` (8ef5d10) changes Task 12's prose and the LANDING row only:
- the predicate runs in the landing act BEFORE the push of main, not in Task 12, which runs post-push;
- the merge-head census receipt moves to `$EVID/landing/landing-census.txt`, carrying my 024612 seal point, which 024840 did not cite;
- the closure cites the record by identity and states that it is local.
Checks: 27/27 blocks equal; producer gate rc 0; T-ORACLE prefix present once. Predicate walk: absent and untracked PASS; add -A and committed each `STOP record-tracked-2343`; the real worktree untouched.
Next: the implementer's exact-hash review of 32c93d2a, then the operator's undraft of PR #28 and the bare merge token, then the landing, then Task 12. The release hold is ABSOLUTE.

## R114 — rev47 MUST-REVISE (MUST-2B-58, `intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-040246.md`); rev48 filed as plan-50 (`intg-substep2b/PLAN-pair-planner-20260928-061445.md`)

MUST-2B-58: rev47's pre-push predicate `n=$(git ls-files … | wc -l | tr -d ' ')` returned `tr`'s status, so a failed `git ls-files` read as n=0 and PASSED. That shape came from master's 024840, and I carried it without a failing-producer control, which is my miss.
rev48 `acb2ac80` (b127a02) changes the LANDING row only. The predicate is now one physical line, run as its own bash: `r=0; L=$(git ls-files -- "$REC") || r=$?`; a nonzero rc STOPs `record-ls-files-rc-<r>`, and only empty output at rc 0 PASSes.
Walk: absent and untracked PASS; add -A and committed STOP record-tracked-2343; exit 91 with empty output, partial output then 91, and no repository (128) each STOP. Control: rev47's predicate PASSes under the failing git.
Checks: 27/27 blocks equal; producer gate rc 0; T-ORACLE prefix present once.
Engine: the kit auto-migrated 2.9.5 → 2.9.6 at 04:39 and removed the 2.9.5 install, so the submit failed with E-VERSION-MISMATCH. On the operator's word "restart it", this root's daemon (PID 29141, 2.9.5) was stopped and restarted on adt-master 2.9.6 (PID 34551, ready). Master's pdc daemon (PID 30006, 2.9.5) was not touched.
Next: the implementer's exact-hash review of acb2ac80, then the operator's undraft and bare merge token, then the landing, then Task 12. The release hold is ABSOLUTE.

## R115 — master accepted rev48 and owned the 024840 fail-open shape (`PLAN-master-planner-20260928-062658.md`); extraction pin concurred (`intg-substep2b/SITREP-pair-planner-20260928-065620.md`)

Master reproduced MUST-2B-58 in seven arms: their form PASSes under a git exiting 91 with no output and outside any repository, and rev48 STOPs in all three failing-producer arms. rev48's facts were verified at master's bytes.
New finding (correct, and mine): 061445 said the line "starts with" the backtick form. Measured: 0 raw starts, 2 lines containing the text (46, 4237), 1 after strip().
Master pins the body as a LANDING-ACT condition, with no rev49: 327 bytes, sha256 `2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5`, occurring once. Re-measured here and concurred; the prose folds at the next plan touch.
Next: the implementer's exact-hash review of acb2ac80, then the operator's undraft and bare merge token, then the landing (the pin is checked before the predicate runs), then Task 12. The release hold is ABSOLUTE.

## R116 — master accepted the narrowing and corrected its own daemon claim (`PLAN-master-planner-20260928-070542.md`); nothing asked

Master withdrew 062658 §3's attribution: the plan states no extraction rule, and the sentence lived in my relay 061445. Master verified the corrected rule (after strip(), plan line 46, count 1; line 4237 fails it), the 327-byte body at `2df745ff…`, and `results/rev48-walks/pred.sh` equal to the body plus a newline. The pin condition stands, with no rev49.
My 065620 environment paragraph was stale: it repeated 062658 §5's "pdc daemon on 2.9.5" without re-measuring at submit. Re-measured now: pid 30006 is dead; the pdc daemon is pid 38916, kit 2.9.6, ready; the intg daemon is pid 34551, kit 2.9.6, ready. 065620 is immutable, and this entry is the correction of record.
Next: the implementer's exact-hash review of acb2ac80, then the operator's undraft and bare merge token. The release hold is ABSOLUTE.

## R117 — rev48 APPROVED (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-174833.md`, plan-review-50); the digest word sent (`intg-substep2b/SITREP-pair-planner-20260928-175741.md`)

The implementer approved `acb2ac80` at b127a02 and closed MUST-2B-58. Independent runs of the extracted line matched the walk, rev47's form failed open under exit 91, and 27/27 blocks are equal.
The word to master carries the five carry fields; only the plan digest moves from 012951, and the three owner objects re-hashed equal at pdc d02790be.
T-ORACLE prefix replay (`results/rev48-walks/t-oracle-replay.txt`, 6b829a0): yes gives rc 0 with one receipt; carry-to STOPs at line 28 with no receipt; stale-digest (012951 unchanged) STOPs plan-sha-mismatch with no receipt.
Next: master's carry for acb2ac80. Then I rewrite `t-oracle.txt` (the predecessor kept by rename) and run the real prefix. Then the operator's undraft of PR #28 and the bare merge token, then the landing (pin 2df745ff checked first), then Task 12. The release hold is ABSOLUTE.

## R118 — master's rev48 carry consumed (`PLAN-master-planner-20260928-181421.md`); `t-oracle.txt` rewritten; the real prefix passes

Master's carry has TO `intg.pair-planner`, one `T_ORACLE_VERDICT: cleared`, and the five fields as sent in 175741; only the plan digest moved, to `acb2ac80`. It is tracked in pdc at bf04c95e. Master's stale control ran against the real installed file (012951, rev46 digest) and STOPped with plan-sha-mismatch.
In `s2b-runners-fr9fJW`, the old `t-oracle.txt` (ed67b42a) is kept as `t-oracle.prev-20260928-182626.txt` (0400), and the new one (2ab8c840, 0400) names carry 181421 at `acb2ac80`. fr9fJW's `carried.sha256` row 36 still records the carried ed67b42a. That is by design: `resume.sh` builds a fresh `carried.sha256` in the next directory, and its line 40 requires the old directory's `t-oracle.txt` to name the new lock (k=1 now).
The real prefix gives `t-oracle OK`, rc 0, one receipt, with the receipt written to scratch so the sealed `$EVID/code/c4a-t-oracle.txt` stays unchanged. Record: `results/rev48-walks/t-oracle-rewrite.txt`.
Next: the operator's undraft of PR #28 and a bare `DISPATCH MERGE` addressed to `intg.pair-implementer` under `.relays/intg`. Then the landing (extract the predicate line, check sha256 `2df745ff…`, run it, then merge and push), then Task 12. The release hold is ABSOLUTE.

## R119 — master routes the owed 2b landing packet (`PLAN-master-planner-20260928-203750.md`, operator arm (a)); the landing-census scout BLOCKS it (`intg-substep2b/SITREP-pair-planner-20260928-204855.md`)

Master's 203750: no 2b merge packet exists, and plan line 129 orders the packet (Master Reviewer-verified) BEFORE the operator's token. Operator arm (a): the packet is routed to the pair. The owner cells (m-1 033430, m-3 033409, m-4 033613) are DONE at H. Master's finding: the declaration names a producer that resolves only inside the untracked record, and a tracked twin exists at `rev45-walks/…candidate.sh` (0c7124d7).
Routing precedent: the r449 MERGE-GATE relays were FROM the pair Planner TO master. The git author reads `intg.pair-implementer` because that is the checkout's default identity.
The scout (f5af6a6, `results/landing-scout-2b/`) ran the tracked producer on the PREDICTED merge (tree 30cecdaa == merge-tree main H), and it STOPs `unclassified-value-at-…/OBLIGATIONS.md:112`. Two values are outside the instrument's two accepted digests, in tree and history (1,853 commits):
- `sk-changing` (English, "task-changing"): 290 blobs;
- a SYNTHETIC `ghp_` string from my rev42 secret-in-patch control: 47 blobs.
The instrument's header holds only `fixture=` and `english=`. The H0 rehearsal passed only because H0 lacks the docs lane; this is the R-4.50 class, where the rehearsed object differs from the scanned object.
Options put to master: (A) an accepted-value set in both producer and instrument (`sk-changing` → C, synthetic `ghp_` → B), rehearsed on the predicted merge, with rev49 (recommended); (B) an override (not recommended); (C) a bar change (theirs and the operator's). The GitHub push-protection risk of the synthetic `ghp_` string is named.
The packet is HELD, unassembled. Next: master's ruling. The release hold is ABSOLUTE.

## R120 — master RULES arm (A) for the accepted-value SET (`PLAN-master-planner-20260928-211118.md`); the location-expectation SHAPE goes to the operator (`…-211128.md`)

Ruled by master (the instrument is master's): the accepted-value header becomes a SET of `(class, sha256)` pairs in both the producer and the instrument. Digest `6b5faf37…` is class C (English false positive) and digest `f419886e…` is class B (synthetic control, non-product fixture copy). Both are re-exercised with the r449 rev3 discipline, including a must-STOP mutant value.
Master's second finding: the `path:line` location expectation churns with the governance record. At main 82792d7a the predicted tree is 8ffff803 with 109 rows (85 docs, 21 .relays, 3 frozen product rows), against my scout's 94 at 30cecdaa. The producer's first STOP is now my own SITREP 204855 line 21, which spelled a value out. So (A) alone leaves a tree-delta STOP.
Shape put to the operator: (a) a global value guard with the location list pinned over product prefixes only (master's recommendation); (b) regenerate the list at landing (a tautology); (c) scan product only.
Discipline from here: census values are named BY DIGEST ONLY in the governance record. My R119 above spelled them out; it is left as filed, and this entry is the correction.
Next: the operator's shape word. The value-set revision (rev49, both artifacts) is written against that word, so each file is revised once. The packet's §7 stays HELD. The release hold is ABSOLUTE.

## R121 — R-4.92 operator arm (a) carried by master with the rev49 spec (`PLAN-master-planner-20260928-212748.md`); rev49 filed as plan-51 (`intg-substep2b/PLAN-pair-planner-20260928-215755.md`)

Master's 212748: the value guard currently runs THROUGH the location list, since rev3 classifies row i by expected row i. So (a) re-roots class onto the value digest; it is not a deletion. The spec: remove the two global location diffs, derive class from digest plus path, derive the product views by grep, record the distinct counts rather than assert them, and walk seven must-be-NO arms with arm 6 first.
rev49 `6b9c507e` (45a75da; extracted-line walk 71c7314), all in `results/landing-2b/`:
- `census_population.rev49.sh` (2d7dcdd6);
- `intg-2b-landing-census.sh` (fbdfd311);
- the PINNED `population-product-2b.txt` (79b89c38): the SET plus the three frozen product rows, byte-equal whether produced at H or on the predicted merge.
The census moves into the landing act BEFORE the push (the r449 §7 order; rev48 had it in post-push Task 12).
walk49: the predicted merge and arm 6 PASS; arms 1–5, the mutant, 7a, 7b and a duplicate-set control each STOP on their own predicate; no matched text retained. The plan's extracted landing line PASSes on a fresh merge.
Checks: 27/27 blocks equal; producer gate rc 0; R-4.90 pin intact; no census literal added (digest-only naming).
Next: the implementer's exact-hash review of 6b9c507e, then the digest word, master's carry, the t-oracle rewrite, the packet, the Master Reviewer, the undraft and bare token, then the landing. The release hold is ABSOLUTE.

## R122 — master verified rev49 at its own bytes (`PLAN-master-planner-20260928-233421.md`); rev50 folds its one condition, filed as plan-52 (`intg-substep2b/PLAN-pair-planner-20260928-233952.md`)

Master re-measured rev49. Both rulings are implemented (precise-pattern audit), the three artifacts are tracked at the claimed digests (R-4.91 discharged), and 27/27 blocks are equal. On a DIFFERENT predicted merge (main 0ac8aca1), population@H == population@merge == the pinned 79b89c38. Master ran arm 6 (PASS) and arm 1 (STOP) themselves, and confirmed choice (ii): rev48's census sat after the push.
Condition: pin the census invocation as R-4.90 pins the predicate, because re-hashing the inputs does not protect the arguments.
rev50 `7a2b894a` (df2935e) changes the LANDING row only: both executed lines are extracted and pinned (327 bytes `2df745ff…` and 221 bytes `af8c1927…`), with the extraction rule stated as it runs. Neither line's bytes moved.
Pin check: the plan gives rc 0; a pre-merge-history-ref mutant STOPs census-line-digest; a duplicated line STOPs census-line-count-2. 27/27 blocks equal; producer gate rc 0; no literal added. Plan-51 (rev49) is superseded unreviewed.
Next: the implementer's exact-hash review of 7a2b894a, then the digest word, master's fresh carry, the t-oracle rewrite, the packet, and onward. The release hold is ABSOLUTE.

## R123 — R-4.93 DISCHARGED at rev50 by master (`PLAN-master-planner-20260929-001609.md`); nothing asked

Master implemented the plan's stated extraction rule from the prose before reading my checker, and got exactly one line per prefix: line 46 (327 bytes, `2df745ff…`) and line 51 (221 bytes, `af8c1927…`). My checker's line 4 is the same rule. Master re-ran both mutants: history ref rewritten gives STOP census-line-digest, a duplicated line gives STOP census-line-count-2, and the plan gives rc 0.
Master noted that the rule now lives in the artifact, not in a relay. One nuance was recorded: the rule's backtick halves discriminate for the predicate prefix, since line 59 contains it and fails, but they are not yet exercised for the census prefix, which only one line contains.
Next: the implementer's exact-hash review of 7a2b894a, then the digest word and master's fresh carry. The release hold is ABSOLUTE.

## R124 — rev50 APPROVED (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md`, plan-review-52); the digest word sent (`intg-substep2b/SITREP-pair-planner-20260929-023044.md`)

The implementer approved `7a2b894a` at df2935e over the complete rev48→rev50 landing delta. On a fresh merge of main 03441bd (tree 52d2468c == merge-tree), the population is byte-equal to the pinned 79b89c38. The census gives PASS at 109 rows, arm 6 PASS at 110, and the undeclared docs value STOPs. Fault controls STOP on tree-producer-rc-2 and row-digest-stage-status-1. Both pins resolve uniquely, the pin mutants STOP, and 27/27 blocks are equal.
T-ORACLE replay (`results/landing-2b/t-oracle-replay-rev50.txt`, 4885b88): yes gives rc 0 with one receipt; carry-to STOPs with no receipt; the REAL installed 181421 STOPs plan-sha-mismatch with no receipt.
Next: master's carry at 7a2b894a, then the t-oracle rewrite, then the packet, the Master Reviewer and master's presentation, then the operator's undraft and bare token, then the landing. The release hold is ABSOLUTE.

## R125 — MERGE-GATE filed (`intg-substep2b/MERGE-GATE-pair-planner-20260929-025641.md`, sha256 `5b5af65f…`, new id `intg-substep2b-merge-packet`)

The packet `results/intg-substep2b-merge-gate.md` (sha256 `ac3186b4…`, 148ab1a) is presented to master for the Master Reviewer's verification and master's own-bytes presentation, per 203750 arm (a).
It is HELD at H `cb19326a`: cells 1–3 are DONE and cell 4 is PENDING.
The §7 landing walk (`results/landing-2b/landing-walk-7.txt`) passed end to end against a local bare remote; the zsh refspec trap is fixed in §7 (5).
Before filing, the relay's cited facts were grepped against the packet bytes, the draft was scanned (zero census literals), and the filed digest was compared to the draft (equal).
Next: the Master Reviewer's verification, then master's presentation, then the operator's undraft of PR #28 and the bare DISPATCH MERGE, then the implementer's landing act per §7, then Task 12. The release hold is ABSOLUTE.

## R126 — F-2B-VP-1 folded as plan rev51 (`7c723a1b…`, f27cb29); PLAN plan-53 filed TO the implementer (`intg-substep2b/PLAN-pair-planner-20260929-214526.md`, sha256 `712c7f2a…`)

The Master Reviewer's `MERGE-GATE-master-reviewer-20260929-041058.md` found the rev48 no-commit line tests the INDEX, not the published HISTORY; master accepted it and routed it in `PLAN-master-planner-20260929-163054.md`.
rev51 keeps the rev48 line and the census line unchanged and adds a third pinned line (704 bytes, `08e2ce06…`): no commit reachable from the literal 40-hex merge sha may touch the record path, with rev-list's rc bound, `--full-history`, `--no-replace-objects` and a commit-ref guard.
Walk `results/rev51-walks/walk51.out`: C4 (the finding) STOPs where the index line passes; C5/C6 query failures STOP; C7 (trap 2) and C8 (replace refs) both discriminate; C9 ref guards and C10 pin mutants STOP. Blocks 27/27 equal, producer gate rc 0, T-ORACLE replay as rev50's (d0ae71e).
Two design additions beyond master's §3 ((a) `--no-replace-objects`, (b) the ref guard) and the path-scope reading of arm (b) are put to the reviewer explicitly.
Next: the implementer's exact-hash review, then the digest word, master's fresh carry, the t-oracle rewrite, the packet §7 revision with a re-walk, and one successor TO the Master Reviewer. The release hold is ABSOLUTE.

## R127 — MUST-2B-59 folded as plan rev53 (`4832b147…`, 3a23e92; supersedes unfiled rev52 `1ae099f6…`); PLAN plan-54 filed TO the implementer (`intg-substep2b/PLAN-pair-planner-20260929-233408.md`, sha256 `fe30b4db…`)

The implementer's `PLAN-REVIEW-pair-implementer-20260929-231628.md` showed legacy `info/grafts` still bends `rev-list` under `--no-replace-objects`, so rev51's history line passed a grafted committed-then-removed record.
rev53's history line (1150 bytes, `bcbb5c97…`) STOPs when the effective graft file exists in any form (rc-bound `rev-parse --git-path info/grafts`, honouring `GIT_GRAFT_FILE`) or the repository is shallow, and runs the query with `-c core.commitGraph=false` after I found a forged commit-graph parent hides the add commit the same way (0 vs raw 2; the probe push was then rejected for missing objects).
Walk `results/rev52-walks/walk53.out` C1–C17: C11 (the reviewer's graft) and C12 (the env graft) pass rev51 and STOP at rev53; C17 (the forged graph) passes rev52 and STOPs at rev53; C13–C16 STOP. Blocks 27/27, producer gate rc 0, T-ORACLE replay as before (bb6a2b9).
Class note: the fake-ancestry sources are replace refs, grafts, shallow and commit-graph; the four pathspec env modes and alternates were measured and cannot narrow the query.
The .relays/intg INDEX carries pre-existing historical ordering inversions (lines 22–584) that the relay-guard hook reports; the file is a daemon projection and is not hand-edited.
Next: the implementer's exact-hash review of rev53, then the cascade unchanged. The release hold is ABSOLUTE.

## R128 — rev53 APPROVED (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md`, plan-review-54); the digest word sent (`intg-substep2b/SITREP-pair-planner-20260930-011027.md`, sha256 `b26849cf…`)

The implementer approved `4832b147` at 3a23e92 over the full rev51→rev53 delta; they independently re-ran walk53 C1–C17 at main `2a04ca1`, and MUST-2B-59 is closed.
The three T_ORACLE objects and master's 023528 were re-hashed equal at pdc 9228cba7; only the plan digest moves in the requested carry.
Next: master's fresh carry at `4832b147`, then the t-oracle rewrite, the packet §7 revision (three pins; both record clauses) with a re-walk, and ONE successor TO master.master-reviewer. The release hold is ABSOLUTE.

## R129 — master's rev53 carry (012837) installed; packet revision 2 (`147c5c0d…`, 9aac28b) sent TO the Master Reviewer for re-verification (`intg-substep2b/MERGE-GATE-pair-planner-20260930-020200.md`, sha256 `b484b329…`)

`t-oracle.txt` was rewritten from 012837 (predecessor `t-oracle.prev-20260930-013405.txt`, 0400), and the real prefix gives rc 0 (`results/rev52-walks/t-oracle-rewrite-rev53.txt`, d787f53).
Disclosed defect: my first run invoked a scratch prefix copy that a midnight sweep had deleted, which gave rc 127, and I committed that record (236587a) without reading its rc. It is kept as `.prev-20260930-013506`; the prefix was re-extracted from the plan by content (lines 1288–1343, `1c437ac4…`).
Packet §7 is now six runnable zsh blocks. They carry master's two 012837 asks (the advisory pre-check before the merge; M derived once and read-only) plus the pinned history line on both parents before the merge. The walk's first draw showed a committed-then-removed record merging and only then STOPping.
Walk `results/landing-2b/landing-walk-7r2.txt`: YES pushes M to a local bare repo; NO-a/b STOP before the merge, NO-c at step (0), NO-d (pre-check removed) at step (4); the remote stays at B in every NO arm.
Next: the Master Reviewer's re-verification, then master's presentation, then the operator's undraft of PR #28 and the bare DISPATCH MERGE, then the landing and Task 12. The release hold is ABSOLUTE.

## R130 — F-2B-VP-2 folded; packet revision 3 (`07418d95…`, d1552ff) sent TO the Master Reviewer (`intg-substep2b/MERGE-GATE-pair-planner-20260930-025912.md`)

The Master Reviewer's `MERGE-GATE-master-reviewer-20260930-021153.md` closed F-2B-VP-1 on rev53 and found F-2B-VP-2: §7's `| tee` receipt writes were unchecked, so a failed receipt could reach the push with rc 0.
Every receipt now goes through `REC` (write, read-back, exit). Step (5) holds the push output in memory, and its one post-push receipt uses `PREC`, ending `STOP post-push … SPENT … NO retry`.
Walk `landing-walk-7r3.txt` (receipt sinks at the real filesystem boundary, push invocations counted): the pre-push sinks STOP with the remote at B (0 invocations for the step and record receipts; 1, the dry run, for the dry-run and attempt receipts); the post-push sink lands and then STOPs rc 1; YES gives `landing-pushed-ok`. `landing-walk-7r2-on-rev3.txt` re-ran NO-a/b/c/d; its first run aborted on a stale driver anchor and is kept.
Next: the Master Reviewer's re-verification of `07418d95`, then master's presentation, then the operator's undraft and bare token. The release hold is ABSOLUTE.
