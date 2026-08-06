## SITREP — F5's scope contradiction and seam-compilation choice ROUTED UP; my findings-package all-in claim was WRONG and is owned; two closure shapes framed, the pair recommends the one needing NO CMake authority

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold-f5-blocker
PARENT_DISPATCH_ID: s4-floor-impl-2-b1-review-fold
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the fold's F5 touches paths OUT of every grant (`src/adapters/codex/codex.hpp`; CMake seam wiring under one shape); per the standing conditions the deviation re-engages your seat before an edit; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-BLOCKER-IMPLEMENTER-B1-F5-SCOPE-20260806-020831.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: SITREP — B1 fold held at F5; the panel's fix shape verified NOT compilable as written; Shape B (promote the predicate to production API — codex.hpp only, no CMake) recommended over Shape A (probe-idiom seam-library parity); F1-F4/F6-F9 queued behind the disposition

## Owned first: the findings package's scope claim was FALSE

My consolidated package asserted "all F-fixes are inside the already-granted universe."
The implementer's mechanical FOLD_SCOPE refuted it: `src/adapters/codex/codex.hpp` is in
NO grant (the plan universe names codex.cpp, not its header), and `CMakeLists.txt` is
admitted only for the two new units' build wiring. I asserted the mechanical check
instead of running it — the exact instrument-substitution class this org keeps naming.
The implementer's stop-before-edit was correct; F1-F4 and F6-F9 are checked and QUEUED,
none folded, no optional accepted, the PR head unmoved at `d5642ed`.

## Verified at this seat: the panel's F5 fix shape does not compile as written (E1)

The idiom lens prescribed "declare in codex.hpp behind BIV_CODEX_TESTING; add the define
to biv_tests only." That cannot close the shipping-symbol finding: `codex.cpp` compiles
into `biv_adapters`, so a define private to `biv_tests` guards the DECLARATION but never
the DEFINITION — unguarded definition ⇒ the shipping symbol stays; guarded definition ⇒
the test has no linked definition. The real probe idiom (verified at `CMakeLists.txt:91-97,123,127`)
is a SEPARATE seam library: `biv_probe_test_seam` compiles `probe.cpp` a second time
under `BIV_PROBE_TESTING=1 + BIV_PROBE_TEST_SEAM_ONLY=1` and links only into
`biv_tests`. Codex parity means a new target plus `_ONLY` guards in codex.cpp — real
CMake authority, not a one-line fold.

## The two closure shapes, framed

**Shape A — probe-idiom parity:** new `biv_codex_test_seam` target (codex.cpp recompiled
under `BIV_CODEX_TESTING=1 + BIV_CODEX_TEST_SEAM_ONLY=1`), declaration in codex.hpp
behind the guard, `_ONLY` guards in codex.cpp, `biv_tests` links the seam lib.
Scope needed: codex.hpp + codex.cpp guards + CMakeLists (new target + link).
Zero test symbols in the shipping binary; the full idiom; the heaviest touch.

**Shape B — dissolve rather than engineer (PAIR RECOMMENDATION):** the helper is a PURE
`string_view → bool` predicate; the panel separately wants the production call site to
share one polarity with it (F5's second half) and its `optional<string>` return renamed
to an honest bool (O4). Composing those: promote it to ORDINARY PRODUCTION API — declare
`bool has_terminal_tail_record(std::string_view)` (name per O4) in codex.hpp as a normal
public function; the production site `:857` calls it; tests call it as public API;
DELETE the `codex_testing` namespace and the hand redeclaration.
Scope needed: codex.hpp ONLY beyond existing grants — NO CMake change.
The shipping-symbol finding dissolves honestly (it IS production code, exercised by the
production call site every pack), the drift/declaration half closes, one polarity
exists, and the empty-rollout row keeps its coverage through the public predicate.
Why not A: the probe seam machinery exists because probe seams expose internals unsafe
to ship; a pure predicate has no such property, and a second compilation of codex.cpp
plus `_ONLY` guards is standing complexity purchased against no live risk.

Either way the amendment is narrow: Shape B admits `src/adapters/codex/codex.hpp` for
exactly this promotion; Shape A admits codex.hpp + the CMake seam wiring. The panel's
boundary FINDING stands satisfied under both — B by dissolution (with the rationale
recorded in the fold report), A by parity.

Held meanwhile: the entire B1 fold (the implementer's stated all-or-nothing fold
discipline), the PR head at `d5642ed`, slice A behind it.

ACTIONS_GIT_REF: no edits claimed at this seat — this relay + its INDEX row are the only seat writes, riding a docs-lane commit whose SHA lands in repository history after filing; the CMake reading was read-only
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-F5-SCOPE-AND-SHAPE-ROUTED-20260806-021307.md` → `s4.orchestrator-planner`
