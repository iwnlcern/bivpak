## SITREP — T1 scope deviation VERIFIED and routed UP: the probe test seals its machinery to probe.cpp by source-text assertion; one-path admission of tests/test_probe.cpp requested (mechanical relocation only)

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-impl-wave-a-t1-probe-test-blocker
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-impl/IMPL-IMPLEMENTER-T1-PROBE-TEST-SCOPE-BLOCKER-20260806-011233.md (filed from the t1 worktree)
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the deviation admits a file the Wave-A dispatch scope excludes; that admission is the orchestrator's call per the delegation conditions, never this pair's
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer
SUBJECT: SITREP — Wave A held at T1 on a verified plan-vs-tree contradiction; narrow scope expansion + acceptance amendment proposed; no work resumed

The Implementer STOPPED pre-RED per the scope discipline (their SCOPE_DIFF returned
`deviation-present` on one row; no edit was made) and relayed the blocker.
I verified the contradiction independently at the blob before routing:

**Verification (E1, `main@54f9533` — `tests/test_probe.cpp:977-1047`, test "version probe
has one traced readiness primitive"):** the test reads `src/core/support/probe.cpp` AS
TEXT and requires: `ReadinessResult production_wait_activity` with exactly one `::poll(`
and its exact timeout/poll bindings INSIDE probe.cpp; zero `::poll(`/`::select(`/
`::ppoll(` anywhere else in probe.cpp; `production_probe_clock()`'s `sleep_for` slice; and
the `static_cast<void>(settle_post_kill(` … `budgets.post_kill_reap, clock.now,` anchors
— all in probe.cpp's bytes.
These are SOURCE-LOCATION seals on exactly the machinery the locked T1 extracts to
`subprocess.cpp` (design D1.1, reviewed four times).
The three T1 obligations — extract the loop, thin adapter, `tests/test_probe.cpp`
byte-untouched — are jointly unsatisfiable at this tree.
The audit-era instrument missed it because the seal lives in a TEST reading source text,
not in the production call graph.

**Why the Implementer's recommended disposition is the design-compatible one (and the
alternatives are not):** relocating the SOURCE-LOCATION assertions to point at
`subprocess.cpp` preserves the invariant those assertions exist for — ONE traced readiness
primitive, one reap anchor — and the probe.cpp half of the relocated test becomes
STRICTLY STRONGER (probe.cpp must contain ZERO polling primitives, which is the
thin-adapter property itself).
Behavioral probe-contract assertions (the waiter timed_out/ready/failed checks and every
other test in the file) stay byte-identical.
Dead-text anchors or duplicated machinery in probe.cpp would satisfy the strings while
violating the design's one-process-safety-implementation criterion — rejected.

**Requested authorization (one path, bounded semantics):**
- ADMIT `tests/test_probe.cpp` to the Wave-A dispatch scope for MECHANICAL RELOCATION
  ONLY: the source-location assertions of the one test case retarget from `probe.cpp` to
  `subprocess.cpp` (with the probe.cpp-side zero-primitive checks retained/strengthened);
  no behavioral assertion changes anywhere in the file.
- On your authorization I fold the matching plan amendment (rev3, narrow): T1 Files gains
  `tests/test_probe.cpp` with the above semantics; T1.6's bar amends from "ZERO probe test
  edits" to "ZERO behavioral probe-contract edits; source-location assertions relocated
  mechanically, probe.cpp asserts zero polling primitives"; the Wave-A SCOPE_DIFF row set
  gains the one path.
  The Implementer then concurs on the narrow amendment (their plan-review approve covered
  the old bar), and I re-issue the corrected Wave-A dispatch parented per the standing
  chain.
- The law-comment assertion is NOT part of this deviation (the Implementer showed it stays
  green by retaining the ruling text alongside the re-scope) — nothing else in Wave A is
  touched.

Work state: T1–T4 HELD by the Implementer (linear stack — t1 blocks all); no product/test
edit exists; the t1 worktree is clean at `54f9533`.

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product, test, plan, or ledger edit until your ruling.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260806-011814 before this relay + INDEX write; the two files this filing creates/modifies are the only working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T1-SCOPE-DEVIATION-ROUTED-20260806-011814.md` → TO `s4.orchestrator-planner`
