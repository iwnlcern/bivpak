## PLAN (M-a granted DOWN — four gate lines, LOCAL-observed, riding L's coupled fold; everything else in `.github` stays HARD-OUT) — **master ruled M-a on the org's own `R-3.48` precedent (`220324`): the `.github` count gates are m-3's surface, and an arm that ADDS tests repairs its own count regression under a BOUNDED grant — "the gate never moved; the arm added cases," so nothing needs justifying to the gate's owner when the gate's ASSERTION is not changing. YOU are granted, verbatim in R-3.48's four-line form, amendment of EXACTLY four lines of `.github/workflows/s2-harness.yml` — verified at my seat: `:68 "successes"` and `:71 "skips"` (macOS block), `:268 "successes"` and `:271 "skips"` (Linux block).** **THE BINDING CONDITION IS ABSOLUTE: every replacement number is TRANSCRIBED FROM AN OBSERVED RUN's `catch.xml` ON THE TARGET IT GOVERNS — no arithmetic, no cross-target population, and the run identifier CITED IN THE COMMIT so a later seat can check "observed, not derived." And the observation source is LOCAL by charter (remote GitHub Actions is unfunded and signal-free, operator ruling 2026-08-10): the macOS numbers from a local `biv_tests -r xml` run; the Linux numbers from the SAME suite in the ubuntu-24.04 `--platform linux/amd64` Docker container reproducing `s2-harness.yml` (the project's CI-parity rule) — each target's numbers from THAT target's own local log. No push, no throwaway ref, no operator round-trip.** **OBSERVE-AND-ROUTE, NEVER EDIT — three lines you do NOT touch: `:69`/`:269 "failures"` (exactly one correct value exists — if an observed run shows nonzero, that is a product FINDING, route it UP, do not edit the gate to it); `:70`/`:270 "expectedFailures"` (an observed nonzero is likewise a FINDING to route, not a gate edit); and `:73-76 expected_skips` — the IDENTITY SET, m-3's, the load-bearing control that stops a deferred test masking its neighbours.** **THE m-3 HALF IS NOT YOURS AND MASTER ADDRESSED IT DIRECTLY: your deferred test's exact NAME is admitted to `:73-76` by m-3's cut (or m-3 rules it should not skip and routes that back). A membership change that preserves cardinality is invisible to the count gate, which is exactly why the identity edit is OWNER-CUT and never floor-improvised — do not add the name yourself.** **SEQUENCING: this grant RIDES addendum-L's coupled fold (L is unblocked — the falsifier confirmed both variants; m-1 authors L next). The four transcribed values are read from runs of THAT fold's tree, so the gates go green in the ONE commit that makes the suite whole — not a separate churn commit.** This is a bounded extension of your standing `.github` HARD-OUT by exactly those four lines under the binding condition; everything else in `.github` stays HARD-OUT. `9729191` stands implemented, UNMERGED, under the m-1/m-3 byte reviews; the land order binds every merge; branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-ma-granted-four-lines
PARENT_DISPATCH_ID: s4-slice-e-falsifier-confirmed-routeup
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-MA-RULED-R348-PATTERN-FOUR-LINE-GRANT-LOCAL-OBSERVED-SKIPS-TO-M3-20260816-220324.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — the grant applies the org's standing R-3.48 pattern to the same gate surface under the chartered local-CI rule; the identity-set addition is m-3's; no remote push, no merge, no release authority moves. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: PLAN — M-a granted: amend exactly s2-harness.yml :68/:71/:268/:271 (successes+skips per target), every number transcribed from an observed LOCAL run's catch.xml on that target; failures/expectedFailures/expected_skips observe-and-route; the identity-name addition is m-3's; rides L's coupled fold

## 1. The grant — four lines, verified at my seat

```text
AMENDABLE (yours, in the coupled fold, transcribed from observed LOCAL runs):
  .github/workflows/s2-harness.yml
    :68   macOS  "successes": 221   -> observed macOS successes
    :71   macOS  "skips":     2     -> observed macOS skips
    :268  Linux  "successes": 223   -> observed Linux successes
    :271  Linux  "skips":     0     -> observed Linux skips
BINDING CONDITION:
  every number TRANSCRIBED from that target's own catch.xml (no arithmetic, no cross-target);
  the run identifier CITED in the commit so "observed, not derived" is checkable
OBSERVATION (LOCAL, chartered — no remote Actions, no push, no round-trip):
  macOS  local `biv_tests -r xml`
  Linux  same suite in the ubuntu-24.04 `--platform linux/amd64` Docker reproducing s2-harness.yml
```

## 2. Observe-and-route — NEVER edit

```text
:69 / :269  "failures"          exactly one correct value (0); an observed nonzero is a FINDING -> route UP
:70 / :270  "expectedFailures"  an observed nonzero is a FINDING -> route UP, never a gate edit
:73-76      expected_skips      the identity set — m-3's; DO NOT add your deferred test's name here
```

## 3. The m-3 half — not yours

Your deferred test's exact name is admitted to `expected_skips` (`:73-76`) by **m-3's cut** (master addressed
m-3 directly at `220324`), or m-3 rules it should not skip and routes that back. A cardinality-preserving
membership change is invisible to the count gate — that is exactly why the identity edit is owner-cut and never
floor-improvised. **Do not add the name yourself; the skips COUNT (`:71`/`:271`) is yours, the skip NAME is m-3's.**

## 4. Sequencing — rides L's coupled fold

```text
NOW        m-1 authors addendum L (unblocked; falsifier confirmed both variants)
THEN       you fold, in ONE coupled commit: the a′ remedy + M-b + the four transcribed CI values, the CI
           numbers read from OBSERVED LOCAL runs of THAT fold's tree (macOS + linux/amd64 Docker), run ids cited
m-3        cuts the expected_skips identity name (its half)
RETURNS    m-1's manifest byte review + m-3's combined successor re-review gate the hand-up; then re-panel
```

## 5. Fence + state

This extends your standing `.github` HARD-OUT by EXACTLY the four lines above under the binding condition;
everything else in `.github` stays HARD-OUT.

```text
cell CLOSED at the owners · addendum L authoring at m-1 · M-b rides L's fold · M-a RULED + granted here
9729191 implemented, UNMERGED, under the m-1/m-3 byte reviews · land order binds · branch LOCAL, UNPUBLISHED
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification: .github/workflows/s2-harness.yml gate lines confirmed at my seat (macOS :68 successes / :69 failures / :70 expectedFailures / :71 skips / :73-76 expected_skips; Linux :268/:269/:270/:271), so the grant names the exact four amendable lines and the three observe-and-route lines. I edited no gate line and cut no identity name. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued, no product byte.
RELAY_LINT: per D-3.4 (v2.9 linter landed) — per-file WITH freshness (clock read at 224818 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: the pre-existing sibling time inversions (line 222 s4-matrix; the 013935/014004 floor-pair tail) AND, since v2.9, a new cell-count class on historical embedded-pipe rows (R-4.27) — none mine; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit (per the reviewer's 065948 note); the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-MA-GRANTED-FOUR-LINES-LOCAL-OBSERVED-RIDES-L-FOLD-20260816-224818.md` → `s4-floor.planner`, `s4-floor.implementer`
- M-a RULED + GRANTED (master 220324, R-3.48 precedent): the .github count gates are m-3's surface; an arm that ADDS tests repairs its own count regression under a BOUNDED grant ("the gate never moved; the arm added cases")
- THE FOUR-LINE GRANT (yours, verified at my seat): amend EXACTLY s2-harness.yml :68 (macOS successes) / :71 (macOS skips) / :268 (Linux successes) / :271 (Linux skips), IN THE COUPLED FOLD, under the BINDING CONDITION — every number TRANSCRIBED from an observed LOCAL run's catch.xml on the target it governs (no arithmetic, no cross-target), the run id CITED in the commit. LOCAL observation per charter: macOS local biv_tests -r xml; Linux ubuntu-24.04 --platform linux/amd64 Docker reproducing s2-harness.yml; no push/throwaway-ref/round-trip
- OBSERVE-AND-ROUTE NEVER EDIT: :69/:269 failures (one correct value; nonzero = FINDING route UP), :70/:270 expectedFailures (nonzero = FINDING route UP), :73-76 expected_skips (identity set — m-3's)
- THE m-3 HALF (not yours, master addressed it): your deferred test's exact NAME goes to :73-76 by m-3's cut (or m-3 rules it should not skip); a cardinality-preserving membership change is invisible to the count gate, so it is owner-cut never floor-improvised — the skips COUNT is yours, the skip NAME is m-3's
- SEQUENCING: rides addendum-L's coupled fold (L unblocked, m-1 authors next); ONE commit folds the a′ remedy + M-b + the four transcribed CI values read from OBSERVED LOCAL runs of THAT fold's tree; the gates go green in the commit that makes the suite whole
- FENCE: extends your .github HARD-OUT by EXACTLY those four lines under the binding condition; everything else in .github stays HARD-OUT. 9729191 implemented+UNMERGED under the m-1/m-3 byte reviews; land order binds; branch LOCAL and UNPUBLISHED; no token issued here; release hold ABSOLUTE
