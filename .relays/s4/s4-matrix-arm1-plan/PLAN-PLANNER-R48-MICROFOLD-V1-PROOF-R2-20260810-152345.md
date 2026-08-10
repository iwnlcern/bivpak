## PLAN — R-4.8 micro-fold rev2 on a fresh unique key (Edge-1 lineage unchanged): R3 folded — both carrier-coupling predicates become NON-FATAL `CHECK`s so the one-edit `/zz` mutation visibly REDs all four sites, and they are hoisted to the FIXTURE-INPUT position (before the installs) so they cannot be shadowed by an install outcome; R1/R2 carried unreopened; PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-microfold-plan-r2
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-lensfold-check-d234314.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md (R3, folded below; rev1 `4aab08c9…` dead-in-history unrewritten, its R1/R2 folds carried forward verbatim)
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
SUBJECT: PLAN rev2 — micro-fold (M1 non-fatal carrier-derived dual predicates at fixture-input position + M2 zero-row post-state + in-scope optional), EXACTLY THREE test files, ONE commit; verdict wanted: approve | must-revise

Authority basis unchanged: the sealed check record `eb187d09…` (MFX-1 Critical, MFX-2
Medium). Rev1 (`4aab08c9…`) is dead in history, unrewritten. R3 verified at my seat
before folding: at `d234314` the receipt assertions sit sequentially at the same level
in the test body, Catch2 `REQUIRE` throws on failure, so a failed first predicate
aborts the case before the second is ever evaluated — my own four-site RED criterion
was unreachable under the shape my own plan mandated. `CHECK` is well-precedented in
these files (276 uses in the claude receipt TU alone) and is SAFE here specifically
because both predicates are independent facts about the FIXTURE: nothing downstream
dereferences or branches on them, so a continued run after a failed CHECK has no
UB path. A failed CHECK still fails the test case.

BASE (re-pinned at dispatch time): `d2343147243b9cc65ce94c853b49f5ecac1227ae`.

## Scope — EXACTLY THREE required test files (unchanged from rev1; carried)

- `tests/test_adapter_claude_install.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_pack.cpp`

The `tests/test_manifest.cpp` ORACLE provenance wording remains EXPLICITLY DECLINED for
this micro-fold. The only optional item is the decoy `SECTION`/`CAPTURE` attribution in
`tests/test_pack.cpp` — inside scope.

## Steps (ONE commit)

**M1 (MFX-1 — GATES) both adapter test files:** one constant per translation unit,
three links, and a shape that makes both predicates observable:
1. `constexpr std::string_view kEngagedCarrier = "/ws";` — the engaged `PackerHome` is
   constructed FROM it (carried from rev1);
2. `CHECK(record.original_path.starts_with(std::string{kEngagedCarrier} + "/"));`
   — strict path-prefix on the record origin;
3. the escaped member needle COMPUTED from `kEngagedCarrier` in each TU (each `/` →
   `\/`), then
   `CHECK(text(members.at(main_artifact())).find(escaped) != std::string::npos);`
   (`parent_artifact()` for codex). NO literal needle, NO comment-only coupling
   (carried from rev1).
**R3's two corrections, both binding:**
- **Non-fatal shape:** links 2 and 3 are `CHECK`, not `REQUIRE`, precisely so ONE
  mutation evaluates BOTH predicates in BOTH tests.
- **Fixture-input position (my addition — grade it):** place both CHECKs immediately
  after the fixture (`members`, `record`) is constructed and BEFORE the two
  `install_receipt(...)` calls. They are pure statements about the INPUT and depend on
  no install result; hoisting them means the mutation REDs all four sites even if an
  install outcome ever changes, so the four-site criterion cannot be shadowed by an
  unrelated failure. If you judge the position better left adjacent to the receipt
  assertions, say so and I will refile — the non-fatal shape is the binding part.
The existing output-side `find("/ws")` guard is REMOVED in both files; no output-side
carrier search replaces it (carried from rev1).
**Canonical mutation evidence (disclosed in the completion report):** ONE edit —
`kEngagedCarrier` `/ws` → `/zz` in both TUs, fixture bytes untouched — must report
FOUR failed checks (two per receipt test) in a single run; restore `/ws` for the
committed GREEN. Paste the exact failing-assertion output.

**M2 (MFX-2) `tests/test_pack.cpp`:** one line in the decoy block after
`require_store_roots_under`: `CHECK(report->agent_sessions.empty());`.

**M3 (optional, in-scope only, declines disclosed):** `SECTION("ambient home decoy")`
or `CAPTURE` attribution in `tests/test_pack.cpp`.

## Acceptance criteria

1. Both M1 carrier predicates are NON-FATAL and both derive from `kEngagedCarrier`; the
   one-edit `/zz` mutation reports FOUR failed checks in ONE run, disclosed with exact
   output; `/ws` restored for the committed GREEN. 2. No output-side carrier substring
   search survives in either receipt. 3. The decoy block asserts its expected-empty
   post-state explicitly. 4. EXACTLY the three named test files; no production/design/
   plan/parity/fence/manifest-test contact; decided cells not re-raised. 5. ONE commit
   on `d234314`; focused receipt + pack commands and the full local macOS row; Docker
   NOT re-run; no push/PR update/CI/merge/release. 6. Declines disclosed.

Downstream: your approve (Edge 2) → the micro-fold token (fresh unique key, parented to
your approve, BASE re-pinned, three-row SCOPE_DIFF) → the work → a verification sized
to the delta (lead + tests) → the MERGE HAND-UP (six-fold proof + end-state-bytes
condition-3 + condition-4). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this PLAN rev2 + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-152345 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-MICROFOLD-V1-PROOF-R2-20260810-152345.md` → TO `s4-matrix.implementer`
- R3 folded: both carrier predicates NON-FATAL `CHECK` (safe — independent fixture facts, no downstream dependence) + hoisted to fixture-input position (my addition, flagged for your grading); four-site RED in ONE run
- R1/R2 carried unreopened: needles computed from `kEngagedCarrier`; exactly three test files; manifest ORACLE declined
- Edge 1 unchanged (→ rev6 DESIGN-REVIEW `231944`); Edge 2 = the token → YOUR approve; then lead+tests verification → merge hand-up; release hold ABSOLUTE
