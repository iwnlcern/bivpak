## IMPL THIRD-FOLD DISPATCH — R-4.8 receipt-determinism fix: normalize every per-install nondeterministic token in the byte-identity receipts + prove them non-empty; ONE test-only commit, then a lead+tests verification sized to the delta; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-fold3-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold2-check-verdict
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-FOLD2-CHECK-PRODUCT-CLEAN-ONE-TEST-FLAKE-THIRD-FOLD-20260810-025909.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — test-only fold within pair authority (no sealed-behavior, design, grammar, or production contact; the check record `c1e7eb8d…` grades the gating finding fold-introduced and test-confined); the declined land-and-file arm is disclosed to the orchestrator in the parent SITREP with override open; publication/remote-CI/merge NOT dispatched; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — third bounded fold on `s4-matrix/r48-carrier` (TF-1 gating + TF-2/TF-3 riders, two test files); ONE commit; branch stays LOCAL; completion report requests the lead+tests verification

Delegated-condition verification (run at this seat at issue time, `030012`):

1. **Authority:** the fold-2 check record (`c1e7eb8d…` at `4c35f0f`, sealed this turn)
   grades TF-1 a fold-introduced TEST defect; fixing a test the pair's own fold rewrote
   is pair scope — no ruling owed, none requested; the alternative arm is disclosed
   upstream with override open.
2. **Branch:** `s4-matrix/r48-carrier` re-pinned at issue time =
   `4c35f0fec8f845500ef7220e0df323d4924c8265`, LOCAL, unpublished, untouched since the
   completion report.
3. **Lineage:** fresh unique DISPATCH_ID (cardinality 1 verified in INDEX); sole-holder
   chain: this → `…fold2-check-verdict` (`025909`) → `…fold2-impl-complete` (`020857`)
   → `…fold2-impl` (`233350`) → `…design-rev6-review` (`231944`, approve).
4. **Hard triggers:** none — two test files, zero production bytes.

SCOPE_DIFF:
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path):
- tests/test_adapter_codex_install.cpp: TF-1 (GATES) — normalize the minted rollout stamp (`%Y-%m-%dT%H-%M-%S`) AND the `sessions/<Y>/<M>/<D>/` date components alongside the installed id BEFORE the relative path enters `receipt.files` / the `receipt.contents` key (the fixed-width layout is already offset-parsed in this file — reuse that idiom); TF-2 — normalize every id in `result->id_map`, not `front()` only; TF-3 — `REQUIRE_FALSE(receipt.files.empty())` before returning; optional while the lines move: the named `constexpr std::string_view kIdPlaceholder` replacing the magic `14U`
- tests/test_adapter_claude_install.cpp: TF-2 + TF-3 (same riders; TF-1 does not apply — the claude destination path carries no time component, verified by the lens and the lead); same optional constant

The work, ONE commit on the branch: as evidenced above. TDD shape stated honestly: TF-1
is a FLAKE fix — a deterministic RED-first row is not constructible without clock
control, so the required evidence is instead (a) the normalizer provably blanking the
stamp/date fields on the receipt's own output, and (b) a repeat-run soak of the two
receipt cases (e.g. `--rng-seed`-independent loop, ≥50 iterations) green on macOS —
disclose the exact soak command and count. TF-3 IS RED-constructible (empty a receipt by
hand in a scratch build if you wish) but a source-visible assertion on a non-empty walk
suffices; your call, disclose it. The verification's charged cell: the WIDENED
normalization (stamp + dates + all ids) must be shown UNABLE to mask a carrier
divergence — `/Users/packer` shares no byte pattern with either token class; state the
argument in the completion report so the lens grades it rather than re-derives it.
Declines disclosed; silence is not a decline.

Boundaries: NO production file, NO manifest/validator/fixture-semantics contact, both
Step-3 fences and the parity pin untouched by construction (test-only scope). Gates,
then report: the four focused receipt/pack/manifest carrier commands + the soak; full
macOS product row; the Docker leg is NOT re-run for a two-test-file delta unless a
command you run contradicts that sizing (disclose either way — this is the lead's
sizing, overridable by the orchestrator). Completion report with the new head SHA
requests the LEAD+TESTS verification at that exact head. Branch stays LOCAL — no push,
PR, remote CI, merge, or release; publication by separate token; human lenses stay
unrouted until the verification is clean. Inline questions and blocker deviations route
back to me; the operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-030012 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-FOLD3-RECEIPT-DETERMINISM-DISPATCH-20260810-030012.md` → TO `s4-matrix.implementer`
- check record `c1e7eb8d…` at `4c35f0f` → the gating TF-1 + riders; two-test-file scope; ONE commit
- soak evidence + normalization-cannot-mask argument → owed in the completion report
- publication/CI/merge/release → NOT dispatched; release hold ABSOLUTE
