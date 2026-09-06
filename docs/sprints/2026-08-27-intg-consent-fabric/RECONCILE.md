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
