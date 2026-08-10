## PLAN — R-4.8 micro-fold rev1 on a fresh unique key (Edge-1 lineage unchanged: parented to the approving rev6 DESIGN-REVIEW): R1-R2 folded — BOTH receipt-input needles now derive from `kEngagedCarrier` (the one-edit `/zz` mutation REDs both assertions in both adapter tests; no comment-only coupling), and the scope is EXACTLY THREE test files everywhere (the manifest ORACLE wording explicitly declined); PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-microfold-plan-r1
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-lensfold-check-d234314.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md (R1-R2, folded below; rev0 `5f1375ce…` dead-in-history unrewritten)
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
SUBJECT: PLAN rev1 — micro-fold (M1 carrier-derived dual needles + M2 zero-row post-state + in-scope-only optional tier), EXACTLY THREE test files, ONE commit; verdict wanted: approve | must-revise

Authority basis unchanged: the sealed check record `eb187d09…` (MFX-1 Critical, MFX-2
Medium). Rev0 (`5f1375ce…`) is dead in history, unrewritten, superseded by this fresh
key. Both R1 and R2 verified at my seat before folding: rev0's comment-only fallback
indeed breaks its own one-edit falsifier (a literal `\/ws\/` needle stays green when
the constant moves), and rev0 indeed said "two test files" in the title while AC4 said
"Two (three with M2)" and M3 offered a fourth path — my own scope arithmetic, caught by
your R2.

BASE (re-pinned at dispatch time): `d2343147243b9cc65ce94c853b49f5ecac1227ae`.

## Scope — EXACTLY THREE required test files (title, steps, ACs, and the downstream three-row SCOPE_DIFF all agree)

- `tests/test_adapter_claude_install.cpp`
- `tests/test_adapter_codex_install.cpp`
- `tests/test_pack.cpp`

The optional ORACLE provenance wording in `tests/test_manifest.cpp` is EXPLICITLY
DECLINED for this micro-fold (a fourth path outside the contract; it rides whenever
that file is next legitimately touched). The only optional item is the decoy
`SECTION`/`CAPTURE` attribution, which touches `tests/test_pack.cpp` — inside scope.

## Steps (ONE commit)

**M1 (MFX-1 — GATES) both adapter test files:** the proof chain, all three links
derived from ONE constant per translation unit:
1. `constexpr std::string_view kEngagedCarrier = "/ws";` — and the engaged
   `PackerHome` is constructed FROM it;
2. `REQUIRE(record.original_path.starts_with(std::string{kEngagedCarrier} + "/"));`
   — strict path-prefix on the record origin;
3. the encoded member needle is COMPUTED from `kEngagedCarrier` in each TU — build the
   slash-escaped spelling by transforming the constant (each `/` → `\/`), then
   `REQUIRE(text(members.at(main_artifact())).find(escaped) != npos);`
   (`parent_artifact()` for codex). NO literal needle, NO comment-only coupling.
The current output-side `find("/ws")` guard is REMOVED in both files; no output-side
carrier search replaces it (the input-side pair is the proof; the byte-identity
equality is the receipt).
**Canonical mutation evidence (disclosed in the completion report):** ONE edit —
`kEngagedCarrier` `/ws` → `/zz`, fixture bytes untouched — must make BOTH assertion
sites RED in BOTH receipt tests (four failing assertions); restore `/ws` for GREEN.

**M2 (MFX-2) `tests/test_pack.cpp`:** one line in the decoy block after
`require_store_roots_under`: `CHECK(report->agent_sessions.empty());`.

**M3 (optional, in-scope only, declines disclosed):** `SECTION("ambient home decoy")`
or `CAPTURE` attribution in `tests/test_pack.cpp`.

## Acceptance criteria

1. All three M1 links derive from `kEngagedCarrier`; the one-edit `/zz` mutation REDs
   both assertions in both adapter tests (four failures), disclosed with the exact
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

ACTIONS_GIT_REF: docs lane only — this PLAN rev1 + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-150219 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-MICROFOLD-V1-PROOF-R1-20260810-150219.md` → TO `s4-matrix.implementer`
- R1 folded: encoded needle COMPUTED from `kEngagedCarrier` per TU; one-edit `/zz` mutation REDs all four assertion sites; output guard removed outright
- R2 folded: exactly three test files everywhere; manifest ORACLE wording explicitly declined; only in-scope optional remains
- Edge 1 unchanged (→ rev6 DESIGN-REVIEW `231944`); Edge 2 = the token → YOUR approve; then lead+tests verification → merge hand-up; release hold ABSOLUTE
