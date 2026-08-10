## PLAN — R-4.8 micro-fold rev0 (Edge-1 lineage: parented to the approving rev6 DESIGN-REVIEW): re-prove the V1 carrier non-vacuity on the INPUT side with the guard coupled to the carrier constant (MFX-1, the check's Critical), plus the decoy block's explicit zero-row post-state (MFX-2); two test files, ONE commit; PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-microfold-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-lensfold-check-d234314.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-LENSFOLD-CHECK-FIVE-OF-SIX-MICRO-FOLD-20260810-144720.md (the verdict this plan executes; same commit)
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — plan-only, grants nothing; the micro-fold token waits on your approving PLAN-REVIEW (Edge 2); the merge hand-up waits on the post-fold verification; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN — micro-fold (MFX-1 + MFX-2 + optional tier), tests/test_adapter_claude_install.cpp + tests/test_adapter_codex_install.cpp + tests/test_pack.cpp, ONE commit; verdict wanted: approve | must-revise

Authority basis: the sealed lens-fold check record
(`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-lensfold-check-d234314.md`,
SHA-256 `eb187d09…`) — MFX-1 graded Critical (the V1 guard passes on two false
witnesses: the workspace directory name contains `/ws`, the sealed `"/ws/proj"` key
survives every rewrite; and the `find("/ws")` literal is uncoupled from the carrier),
MFX-2 Medium (the decoy block's post-state is two vacuous universal quantifiers). Both
were lead-re-verified at the bytes. Test-only, pair scope, no sealed contact.

BASE (re-pinned at dispatch time): `d2343147243b9cc65ce94c853b49f5ecac1227ae`.

## Steps (ONE commit)

**M1 (MFX-1 — GATES) `tests/test_adapter_claude_install.cpp` + `tests/test_adapter_codex_install.cpp`:**
per the lens's prescription, in both receipt tests:
- hoist the engaged carrier to a named constant (`constexpr std::string_view
  kEngagedCarrier = "/ws";`) and construct the engaged `PackerHome` FROM it — one
  authority for value and proof;
- REPLACE the unfalsifiable output-side `any_of(find("/ws"))` guard with the two
  INPUT-side assertions, both derived from the constant:
  (a) `REQUIRE(record.original_path.starts_with(std::string{kEngagedCarrier} + "/"));`
      — strict path-prefix, not substring;
  (b) the input member bytes carry the carrier in the ENCODED spelling the installer
      sees (the fixture cwd is `"\/ws\/proj"`): assert the raw member text
      contains the escaped `\/ws\/` form (main_artifact for claude, parent_artifact
      for codex), derived from the constant where practical — if the escaped spelling
      must be a literal, a comment ties it to `kEngagedCarrier` so they cannot drift
      silently;
- if any post-install content search is retained, it MUST be boundary-aware and MUST
  exclude `workspace.generic_string()` from the searched text — otherwise drop the
  output-side search entirely (the input-side pair is the proof; the byte-identity
  equality is the receipt).
Falsifier honesty check the verification will grade: with the fixture's carrier-rooted
bytes removed (or the carrier changed to `/zz` without touching the fixture), BOTH new
assertions must go RED — run that mutation once and disclose it (strict-TDD analog:
the RED is constructible here).

**M2 (MFX-2) `tests/test_pack.cpp`:** one line in the decoy block after
`require_store_roots_under`: `CHECK(report->agent_sessions.empty());` — the file's own
idiom; the post-state stops being vacuously quantified.

**M3 (optional tier, discretion, declines disclosed):** decoy block attribution
(`SECTION("ambient home decoy")` or `CAPTURE`); ORACLE comment provenance wording
(name the literal's introducing commit rather than the fold baseline).

## Acceptance criteria

1. The V1 proof is input-side, carrier-coupled, and satisfiable by NEITHER false
   witness; the `/zz` (or fixture-stripped) mutation goes RED on both assertions,
   disclosed. 2. No output-side substring search survives unless workspace-excluded.
3. The decoy block asserts its expected-empty post-state explicitly. 4. Two (three
   with M2) test files only; no production/design/plan/parity/fence contact; the
   decided cells are not re-raised. 5. ONE commit on `d234314`; focused receipt +
   pack + manifest commands and the full local macOS row; Docker NOT re-run
   (test-only); no push/PR update/CI/merge/release. 6. Declines disclosed.

Downstream: your approve (Edge 2) → the micro-fold token (fresh unique key, parented
to your approve, BASE re-pinned, SCOPE_DIFF: the three test files) → the work → a
verification sized to the delta (lead + tests) → the MERGE HAND-UP (six-fold proof +
end-state-bytes condition-3 + condition-4). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this PLAN + the sibling verdict SITREP + the sealed check record + their INDEX rows ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-144720 before these relays + INDEX writes; the two relays, two INDEX rows, and the record are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-MICROFOLD-V1-PROOF-20260810-144720.md` → TO `s4-matrix.implementer`
- MFX-1 → input-side carrier-coupled proof replacing the false-witness guard, with the disclosed RED mutation; MFX-2 → explicit empty post-state; M3 optional
- Edge 1 = this PLAN → rev6 DESIGN-REVIEW (`231944`); Edge 2 = the token → YOUR approve; then lead+tests verification → merge hand-up
- PR #24 untouched; release hold ABSOLUTE
