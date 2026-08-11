## SITREP — Slice C targeted re-check PASSES at the bytes at ec9a2db: all seven panel blockers verified closed, BL-2 fix lands INSIDE the original A6 grant bound, scope/topology/held-items clean. Merge RECOMMENDED on the slice's own merits; the only gating caveats are the already-routed stale count gate and the two master-held follow-ons — neither a slice-C defect.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-recheck
PARENT_DISPATCH_ID: s4-floor-impl-2-c-review-fold-complete
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — this is a merge RECOMMENDATION only; merge and release are the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-REVIEW-FOLD-COMPLETE-20260807-225111.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: RE-CHECK PASS — slice C at ec9a2db2cfe55191f99efbcf12902a79d99e159e; fold verified at the bytes, not on the report's word; merge recommendation with the exact remaining caveats

I ran the dispatched targeted re-check (sized to the 13-path fold delta
`eadc88f..ec9a2db`), re-verifying every load-bearing claim at the committed bytes rather
than trusting the fold report. All pass.

## Structural (verified at the bytes)
- remote `origin/s4-floor/c-consent-no-carrier` and draft PR #22 = exact
  `ec9a2db2cfe55191f99efbcf12902a79d99e159e`;
- topology: `798526c..ec9a2db` = exactly ONE commit; required subject unchanged;
- full range = 24 paths; fold delta = 13 paths;
- HELD/ROUTED exclusions ABSENT from the delta: no `src/core/open/open.cpp`, no
  `.github/**`, and the sealed claude origin-layout is untouched (its pinning
  `CHECK_FALSE(fs::exists(final_workspace_project))` still present at
  `test_adapter_claude_install.cpp:665`; consent-no still origin-keyed, as required to
  be held);
- no A3-anchored collect file in the delta (`e3.py`, `manifest.cpp`, `scan.cpp`,
  `codex.cpp`, `claude_code.cpp` all untouched) — no anchor ceremony was owed, none
  fired; no CANON-2.6/B2 territory touched.

## BL-1..BL-7 verified closed (at the bytes)
- **BL-1** — `sessions.cpp:337-405`: a preflight over a pre-existing/foreign `.biv/agents`
  carrier yields a `containment_refused` row, reason `foreign_staging_carrier`, BEFORE
  any adapter write. The live pre-plant vector (security C1) is closed in-universe.
- **BL-2** — the grant-bound item, verified most carefully: all three scenarios are back
  to `"tree": true` with `tree_allowed_extra_roots: [".biv/agents"]`, and
  `compare.py:_allowed_extra` relaxes ONLY that root, its descendants, and the bare
  DIRECTORY ancestors needed to reach it. A file at `.biv/foreign.txt`, a wider root, any
  byte/mode/kind mismatch on a shared path, and any MISSING path all stay red;
  `_validated_additive_roots` rejects absolute/`..`/non-normalized roots. This is exactly
  the A6 part (2) bound ("ONLY the additive `.biv/agents` carrier") — the fix restores the
  E2E proof without exceeding the grant. Classes A/B/C active again.
- **BL-3** — `sessions.cpp:544-563`: the publish-failure handler now computes
  `install_failure_reason(...)`, branches `containment`, sets the row to
  `containment_refused` vs `session_install_failed` accordingly, and attaches an errno
  symbol ONLY on the non-containment branch.
- **BL-4** — `InstallResult::pair_set_applied` (`adapter.hpp:198`) carries each adapter's
  actual `derive_pair_set` output; orchestration aggregates the real pairs.
- **BL-5** — same handler: `row.detail = merged_detail(row.detail, detail)` preserves the
  staged row's non-UTF-8 disclosure through the failure flip instead of clobbering it.
- **BL-6** — `claude_code/install.cpp`: the project-key cap is now per-record
  (`if (project_key_for_record(record).size() > kUnpinnedProjectKeyCap)`), not the
  cohort-wide `any_of`.
- **BL-7** — the three requested falsifiers are present; the fold report's mutation
  receipts show RED→GREEN for the activation and disclosure falsifiers, and the delta
  touches the three named test files plus `test_compare.py` (the selftest for BL-2's new
  bounded tolerance — the compare.py fix site my BL-2 disposition explicitly named).

## Scope note (in-bounds)
The fold added `harness/bivharness/compare.py` and `harness/selftest/test_compare.py` —
not in the original 20-path slice-C set. These are the direct, required mechanism for
BL-2: my REVIEW-FOLD disposition explicitly authorized "an equivalent per-path tolerance
in `compare.py`," and its selftest is the falsifier for that mechanism. In-bounds as a
blocker-driven fold, not a new surface. The implementer's FOLD_SCOPE record maps every
edit and matches the delta.

## Evidence
Host suite at `ec9a2db`: `ctest --preset dev -E '^safety-hardening$'` exit 0, 14/14
selected pass. Local Ubuntu 24.04 `linux/amd64` Docker suite (the standing CI leg while
Actions is out): all non-environment workflow rows PASS incl. tidy/analyzer, e2,
build-werror, hardening; canonical result honestly non-green only on the two ESTABLISHED
and DISCLOSED substitution deltas (the single Rosetta invalid-executable case; the four
Docker-overlay filesystem mutation sentinels), which the narrow exclusion controls then
pass. No native GitHub x86_64 proof claimed. The implementer's own scoped exact-head
re-review returned clean.

## Blast radius / no re-panel
The fold is a bounded harness tolerance plus adapter/session fixes, each inside its
finding's scope, adding no production surface beyond what the blockers required. Blast
radius did not change in a way that warrants a full re-panel; this targeted re-check is
the gate per the standing discipline.

## MERGE RECOMMENDATION (merge is the operator's alone)
**Slice C is READY TO MERGE on its own merits** — all seven panel blockers verified
closed at the bytes, topology and scope clean, held/routed items correctly untouched, and
the CI leg meets the standing local-Docker bar (green modulo the disclosed environment
deltas). The remaining gating caveats are NOT slice-C defects:
1. the stale `.github` Catch2 count gate (now 223 required vs 262 enumerated) — hard OUT,
   routed upstream, still unowned; it will red any REMOTE run until its owner moves (the
   same gate that holds B1's PR #15);
2. ROUTED-2 (`open.cpp` extract-side `.biv` defense-in-depth) and ROUTED-3 (claude
   origin-path layout) are follow-on items HELD at master — the live vector is closed by
   BL-1 and the layout is sealed-as-is pending the master ruling; neither blocks slice C.

Recommended disposition: hold the merge button as ever with the operator; if the operator
wants a single clean remote CI cycle, sequence it after the count-gate owner moves (one
push then). The stack does not need the merge to proceed — B2 seeds from `ec9a2db` under
the restack rule and inherits the A3 anchor ceremony on the collect files it will touch,
plus the CANON-2.6 reader + repack-exact fixtures reassigned to it under A5.

ACTIONS_GIT_REF: no product/test edits at this seat — the re-check was read-only git plumbing (git show/grep/log at ec9a2db); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-C-RECHECK-PASS-MERGE-REC-20260807-230702.md` → `s4.orchestrator-planner`
- slice C at `ec9a2db2cfe55191f99efbcf12902a79d99e159e` → merge recommendation READY; merge/release the operator's, hold ABSOLUTE
- next: B2 seeds from `ec9a2db` (inherits A3 on both anchors; owns the CANON-2.6 reader + repack-exact fixtures per A5) → awaits sequencing
- unchanged: `.github` count gate + ROUTED-2 + ROUTED-3 held/routed upstream
