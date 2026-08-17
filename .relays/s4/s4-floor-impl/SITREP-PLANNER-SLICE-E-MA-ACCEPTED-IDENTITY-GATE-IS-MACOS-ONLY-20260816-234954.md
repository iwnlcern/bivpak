## SITREP — M-a grant ACCEPTED and its four lines verified at the bytes; **one pre-fold cell: the `expected_skips` identity gate exists ONLY in the macOS block, so the two platforms have different dependency shapes and "the gates go green in ONE commit" is not symmetric** — **verified at `9729191`: `expected_skips` occurs at exactly three sites (`:73` definition, `:90` check, `:93` message) and ALL THREE are inside the macOS block. The Linux block runs from `want` at `:267-272` straight to `print` at `:273` and `if got != want` at `:274` — there is NO identity set on the Linux side to cut.** **CONSEQUENCE FOR THE COUPLED FOLD: the LINUX gate goes green on my two transcribed numbers ALONE (`:268` successes, `:271` skips 0→1). The macOS gate needs BOTH my two numbers (`:68`, `:71` skips 2→3) AND m-3's identity cut at `:73-76`, because `:90`'s `set(skipped) != expected_skips` fires on the NAME independently of the count. So if m-3's cut is not in the SAME commit as my transcribed values, macOS CI stays RED after the fold while Linux goes green — and the grant's "the gates go green in the ONE commit that makes the suite whole" holds for Linux but not for macOS.** **I am NOT asking to touch `:73-76` — the identity edit is m-3's and I accept that without reservation. I am flagging that the fold's green outcome DEPENDS on m-3's cut landing in that same commit, which is a scheduling fact neither m-3 nor I can settle alone, and it is a one-line answer now versus a red macOS row discovered after the fold.** **Leg (p)'s skip is platform-independent — its guard is a `constexpr` comparison of the two exported constants (`test_sessions.cpp:1747-1749`), not a runtime or host condition — so it skips on BOTH targets and both `skips` counts move.** Nothing owed from me until addendum L lands; no product byte, no `.github` byte, no token. `9729191` unchanged; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-ma-accepted-identity-asymmetry
PARENT_DISPATCH_ID: s4-floor-slice-e-ma-granted-four-lines
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-MA-GRANTED-FOUR-LINES-LOCAL-OBSERVED-RIDES-L-FOLD-20260816-224818.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — whether m-3's identity cut lands in the same coupled commit as my transcribed counts determines whether macOS CI is green or red after the fold. That is a scheduling dependency between two seats and neither can settle it alone. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: SITREP — M-a accepted, four lines verified; the expected_skips identity gate is macOS-ONLY, so Linux goes green on my numbers alone while macOS additionally needs m-3's cut in the same commit

## 1. Grant verified at the bytes — all seven lines are where the grant says

```text
AMENDABLE (mine, in the fold, transcribed)
  :68   macOS  "successes": 221      CONFIRMED
  :71   macOS  "skips": 2            CONFIRMED
  :268  Linux  "successes": 223      CONFIRMED
  :271  Linux  "skips": 0            CONFIRMED
OBSERVE-AND-ROUTE (never edit)
  :69  / :269  "failures": 0         CONFIRMED
  :70  / :270  "expectedFailures": 0 CONFIRMED
  :73-76       expected_skips        CONFIRMED — exactly two names today (the WSL pair)
```

**Accepted without reservation**, including that the skip NAME is m-3's and the skip COUNT is mine. I will not touch `:73-76`.

## 2. The asymmetry — `expected_skips` is macOS-only

```text
git grep -n expected_skips  ->  :73 (definition) · :90 (check) · :93 (message)
                                ALL THREE inside the macOS block

macOS  :88  if got != want:            -> COUNT gate
       :90  if set(skipped) != expected_skips:  -> IDENTITY gate   <-- m-3's
Linux  :274 if got != want:            -> COUNT gate ONLY; no identity set exists
```

**So the two platforms do not have the same dependency shape:**

```text
LINUX  green on MY two numbers alone (:268 successes, :271 skips 0 -> 1)
macOS  needs MY two numbers (:68, :71 skips 2 -> 3) AND m-3's cut at :73-76 —
       :90 fires on the NAME independently of the count, so a correct count with a
       stale identity set still exits non-zero
```

**Consequence the grant does not name:** *"the gates go green in the ONE commit that makes the suite whole"* holds for Linux under my grant alone, but for macOS **only if m-3's identity cut is in that same commit.** If it is not, the fold lands with Linux green and macOS red on `SKIP-IDENTITY GATE FAILED`.

**I am not asking for the identity line.** The reasoning for owner-cut is sound and a cardinality-preserving membership change being invisible to the count gate is exactly why. **What I am flagging is a scheduling dependency between two seats that neither can settle alone** — and it is a one-line answer now versus a red macOS row discovered after the fold.

**Three ways it can resolve, none of them mine to pick:** m-3 cuts the name into the fold branch before I fold; or m-3's cut lands as its own commit and macOS is knowingly red for that interval; or master sequences the fold to wait on the cut. **Routed for the call.**

## 3. Leg (p) skips on BOTH targets — so both counts move

```text
test_sessions.cpp:1747-1749
  if (biv::core_sessions::kEntrySchemaSupportedCeiling <
      biv::manifest::kEntrySchemaParseCeiling) { SKIP(...); }
```

A `constexpr` comparison of the two exported constants — **no host, runtime or platform condition.** It skips identically on macOS and Linux, which is why `:71` moves 2→3 *and* `:271` moves 0→1. Consistent with the Implementer's observed Linux selection (17 cases = 16 passed + 1 configured-deferred).

## 4. What I will do when L lands, and what I will not

```text
WILL   fold in ONE commit: the a′ remedy + M-b + the four transcribed values, every number
       READ FROM that fold tree's own catch.xml on the target it governs — macOS from a local
       `biv_tests -r xml`, Linux from the ubuntu-24.04 linux/amd64 Docker reproducing the
       workflow — with both run identifiers CITED in the commit message so a later seat can
       check "observed, not derived". No arithmetic. No cross-target borrowing.
WILL   route, never edit, if an observed run shows nonzero at :69/:269 or :70/:270 —
       that is a product FINDING, not a gate to adjust
WILL NOT touch :73-76, or any other .github line; the HARD-OUT stands but for those four
```

**Nothing is owed from me until addendum L lands at m-1.** No product byte, no `.github` byte, no token this pass.

ACTIONS_GIT_REF: no product, test, fixture or `.github` edit at this seat — read-only verification at `9729191`: the seven gate lines confirmed at their stated numbers; `git grep -n expected_skips` returning exactly three sites, all macOS-block; the Linux block read from `want` through its `got != want` check confirming no identity set; `tests/test_sessions.cpp:1745-1750` read to confirm leg (p)'s guard is a `constexpr` constant comparison rather than a host condition. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) plus, since v2.9, the historical embedded-pipe cell-count class (`R-4.27`) — none mine.
FINAL_GIT_STATUS_SHORT:
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-MA-ACCEPTED-IDENTITY-GATE-IS-MACOS-ONLY-20260816-234954.md` → `s4.orchestrator-planner`
- **M-a ACCEPTED; all seven named lines verified at `9729191`** — amendable `:68`/`:71`/`:268`/`:271`, observe-and-route `:69`/`:70`/`:269`/`:270` and `:73-76`. The skip NAME is m-3's and the skip COUNT is mine; I will not touch `:73-76`
- **PRE-FOLD CELL — the identity gate is macOS-ONLY:** `git grep -n expected_skips` returns exactly three sites (`:73` definition, `:90` check, `:93` message), ALL inside the macOS block. The Linux block runs `want` → `print` → `if got != want` with NO identity set to cut
- **THE TWO PLATFORMS THEREFORE HAVE DIFFERENT DEPENDENCY SHAPES:** Linux goes green on MY two numbers alone; macOS needs my two numbers AND m-3's `:73-76` cut, because `:90` fires on the NAME independently of the count. **So "the gates go green in the ONE commit that makes the suite whole" holds for Linux but NOT for macOS unless m-3's cut is in that same commit** — otherwise the fold lands Linux-green / macOS-red on `SKIP-IDENTITY GATE FAILED`
- **NOT asking for the identity line** — owner-cut is right and I accept it. Flagging a SCHEDULING dependency between two seats that neither can settle alone: m-3 cuts into the fold branch first, or the cut lands separately and macOS is knowingly red for that interval, or master sequences the fold to wait. **Routed for the call; a one-line answer now versus a red row discovered after the fold**
- **LEG (p) SKIPS ON BOTH TARGETS** — its guard is a `constexpr` comparison of the two exported constants (`test_sessions.cpp:1747-1749`), not a host condition — so `:71` moves 2→3 AND `:271` moves 0→1, consistent with the Implementer's observed Linux 17 = 16 + 1
- WHEN L LANDS I fold ONE commit (a′ remedy + M-b + four transcribed values), every number read from THAT tree's own `catch.xml` on the target it governs, macOS local and Linux in the `linux/amd64` Docker, BOTH run ids cited, no arithmetic and no cross-target borrowing; an observed nonzero at `:69`/`:269`/`:70`/`:270` is routed as a product FINDING, never a gate edit
- Nothing owed until addendum L lands at m-1; no product byte, no `.github` byte, no token; `9729191` unchanged; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
