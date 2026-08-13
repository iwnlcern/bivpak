## PLAN rev3b (slice E) — both defects confirmed at the bytes. **R1: my `tests/**` glob was an operative permission that silently widened the exact scope carried in the same plan** — a plan cannot say "everything else carries unchanged" and simultaneously grant more than it carries; replaced with the five named files and one fixture subtree. **R2 is the better catch and it corrects a misclassification that would have manufactured a false RED:** key 2's `parent_id`-absence arm passes the moment m-1's optional member compiles, because both production construction sites use designated initializers and leave an unset optional at `nullopt`. It is a **GREEN compatibility control**, and if it ever goes red at the receipt **that is m-1's contract breaking, not our RED — Stage 1 STOPS.** Rev4 remains reserved for m-2's cap ruling.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-rev3b
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-2's cap-carrier ruling (routed `163327`) gates the final approvable plan, which is rev4 and is not this relay. Lineage is cleared only by the bounded operator waiver (`163217`/`163555`), VOID if the pinned bytes move. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
TARGET_DESIGN_COMMIT: 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-MUST-REVISE-EXACT-STAGE0-SCOPE-KEY2-CONTROL-20260812-165204.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-STAGE0-FIXTURE-ONLY-SUCCESSOR-DISCIPLINE-20260812-164434.md (rev3, superseded); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-WAIVED-GATE1-CLEAR-CAP-CARRIER-GATE2-HOLDS-20260812-163555.md (gate 1 clear, gate 2 holds); .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-CAP-REFUSAL-CARRIER-SEAM-ROUTED-20260812-155122.md (the cap cell, OPEN)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: PLAN rev3b — Stage 0 scoped to five exact test files + one fixture subtree; key 2 reclassified as a GREEN compatibility control with a dependency-integrity stop; RED set is 1a/3/4/6 then 1b/4a/5

## 1. R1 — the exact Stage-0 scope, replacing the glob

```text
STAGE 0 — PERMITTED PATHS, EXHAUSTIVE
  tests/test_adapter_codex_collect.cpp     REDs 1a, 3, 4
  tests/test_adapter_codex_install.cpp     RED  6
  tests/test_adapter_claude_collect.cpp    CONTROL 7
  tests/test_pack.cpp                      CONTROL 2 (byte-identical two-level arm)
  tests/test_cli.cpp                       the three claude reference-resolution controls
  tests/fixtures/slice-e/**                fixture trees, incl. DATA ONLY for 1b / 4a / 5
STAGE 0 — FORBIDDEN
  src/**  (entirely — not a header, not a declaration, not an unused member)
  harness/**  ·  .github/**  ·  every path not named above
  ANY other test, helper or fixture path ROUTES through the scope-diff/deviation gate BEFORE dispatch
```

**My glob was not a summary, it was a permission**, and it sat in the same plan as an exact carried scope —
so the broader sentence would have governed at the moment someone needed it to. Replaced, not narrowed by
commentary.

## 2. R2 — key 2 is a GREEN compatibility control on BOTH arms, and its failure is a STOP

**Verified at the bytes.** `SessionChild` is constructed at exactly two production sites, both with
designated initializers:

```text
src/core/pack/pack.cpp:400        manifest::SessionChild{.original_id = child_id, .artifacts = …}   (ours)
src/core/manifest/manifest.cpp:201  SessionChild{.original_id = …, .artifacts = …}   (the PARSER — m-1's, fence-2)
```

A new `std::optional<std::string> parent_id` member is **value-initialized to `nullopt` at both** — omitted
designated initializers are value-initialized, and existing test construction sites (e.g.
`tests/test_sessions.cpp:392`) keep compiling for the same reason. **So the moment m-1's member exists and
before any s4 change, no `parent_id` is emitted for a two-level entry — the assertion PASSES.** Calling that
a RED would have been claiming a defect that the dependency's own correctness prevents from ever appearing.

```text
key 2, arm 1   byte-identical two-level round trip     GREEN at 0db8fdd
key 2, arm 2   no parent_id emitted for a two-level    GREEN immediately after the m-1 rebase,
               entry (J's absence license)             and GREEN AGAIN after the s4 implementation
```

**The dependency-integrity stop, stated so it cannot be re-read as a to-do.** If arm 2 is RED at the m-1
receipt, **m-1's writer is emitting `parent_id` where J's absence license forbids it — the locked
compatibility contract is broken upstream. STAGE 1 STOPS and it routes; it is never absorbed as an s4 RED to
be fixed here.** The same stop applies to the second failure mode: if the member lands as **required** rather
than optional, our construction site will not compile — also a dependency-integrity stop, also routed, and
also not a behavioral RED.

## 3. The corrected RED/GREEN ordering

```text
STAGE 0 @ 0db8fdd     assertion-level REDs   1a, 3, 4, 6      (each named in rev3 §2, unchanged)
                      GREEN controls          2 arm 1, 7, the three claude reference controls
        ↓ rebase onto the m-1 receipt SHA (0db8fdd stays the AUDIT cut)
POST-REBASE           GREEN control           2 arm 2         ← a stop, not a RED, if it fails
                      assertion-level REDs    1b, 4a, 5 (atomic: both variants authored and run together)
        ↓
STAGE 1               the single coupled implementation
        ↓
AFTER                 every key GREEN, including 2 arm 2 re-run; controls still green
```

**No implementation byte lands before every key it greens has been observed failing on an assertion.** A
compile failure is not a credited behavioral RED — your rule, and it stays bound.

## 4. Unchanged and still binding

Everything in rev3 §§1, 4, 5 and in rev2 that rev3 carried: Stage 0 = no production byte; `child_parent_map`
declared, populated and consumed in Stage 1 with the closure, rootless disposition, both root-mapped monotone
gates, the warning producers, `manifest_entry_for`'s edge emission and all four caps as ONE change, with
Stage 1 WAITING rather than splitting if the ruling lags the receipt; `FX-A12-5` atomic; A3's four checks on
ONE `codex.cpp` head carrying its ONE pin, `codex/install.cpp` moving no pin, the claude pin frozen, the five
codex read-side literal classes mutation-checked and check 4 class-scoped; the exact IN/OUT/CONDITIONAL-OUT
production scope for Stage 1; the E2E and verification matrix, sandbox guards and credential decoy, macOS plus
governing local Ubuntu 24.04 `linux/amd64` Docker with Actions untouched, the base-container control, the
`.github` count gates as an inherited stale pin; branch cut from `origin/main` (= `0db8fdd`), never local
`main`; publication HELD; D-5.5(a) at hand-up; R-4.20's mint sites; MONO; M4-CG-0; R-4.24 not ours.

**Gate ledger, unchanged from rev3 §4:** `154140` WITHDRAWN → `162257` disclosure-is-not-waiver → `163217`
operator waiver bounded to `154cd87e`/`94b6440c`, VOID IF MOVED → `163555` gate 1 CLEAR / gate 2 OPEN.
Lineage CLEAR via the waiver only; cap carrier OPEN; m-1 receipt ABSENT; plan review RED. **At token time I
re-confirm both pins at the bytes and say so in the token relay.**

## 5. What I am asking of you

**A plan review of these two corrections.** Is the Stage-0 path list now exhaustive and closed, and is key 2's
reclassification right in both arms — including that its failure at the receipt is a dependency stop rather
than work for us? **An approve still opens no token:** gate 2 holds at m-2, and rev4 folds that ruling and is
reviewed on its own. Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold,
no backticks; remarks via em-dash only, per the matcher's recorded grammar). Merge ≠ push ≠ release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — both `SessionChild` production construction sites enumerated at `0db8fdd` (`pack.cpp:400`, `manifest.cpp:201`, both designated-initializer) plus the test sites that keep compiling, confirming an added optional member is value-initialized to `nullopt`; the rev3 review read in full; the exact carried scope list reconciled against rev1/rev2; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, WAIVED for this lineage at these pins (`163217`/`163555`) and still disclosed — no green claimed, no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3B-EXACT-STAGE0-PATHS-KEY2-GREEN-CONTROL-20260812-170013.md` → `s4-floor.implementer`; rev3 `164434` SUPERSEDED; **rev4 stays reserved for m-2's cap ruling**
- **R1:** `tests/**` was an operative permission that outranked the exact scope carried in the same plan — replaced with an EXHAUSTIVE five files + `tests/fixtures/slice-e/**`; `src/**`, harness and `.github` forbidden in Stage 0; any other path routes before dispatch
- **R2 verified at the bytes:** both production `SessionChild` sites (`pack.cpp:400`, `manifest.cpp:201`) use designated initializers, so an added optional `parent_id` is value-initialized to `nullopt` and key 2's absence arm PASSES at the m-1 receipt with no s4 change — a GREEN compatibility control on BOTH arms, not a RED
- **dependency-integrity STOP recorded:** if arm 2 is RED at the receipt, m-1's writer breaks J's absence license and STAGE 1 STOPS and ROUTES; same stop if the member lands REQUIRED rather than optional (our site would not compile). Neither is an s4 RED to absorb
- **corrected ordering:** Stage-0 REDs `1a/3/4/6` + controls → rebase → key-2 arm 2 GREEN + REDs `1b/4a/5` (5 atomic) → Stage 1 → all green. A compile failure is NOT a credited behavioral RED
- gates unchanged: lineage CLEAR via the bounded waiver only, cap carrier OPEN at m-2, m-1 receipt ABSENT, plan review RED; pins re-confirmed at token time; release hold ABSOLUTE
