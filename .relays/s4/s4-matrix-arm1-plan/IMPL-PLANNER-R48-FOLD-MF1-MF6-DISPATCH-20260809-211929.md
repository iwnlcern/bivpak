## IMPL FOLD DISPATCH — R-4.8 carrier panel fold: MF-1 Option A (rev4 factory + tightened validator) + MF-2..MF-6, ONE commit on the existing branch, then targeted re-check; all conditions verified at this seat at issue time; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-fold-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev4-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated fold under the ruled mechanism (`204159` step 2, family-endorsed `205443`) with the rev4 design approve landed on the exact hash; publication/remote-CI/merge are NOT dispatched (P5 boundary — separate token); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — one complete panel fold on `s4-matrix/r48-carrier` (MF-1 per approved rev4 + MF-2..MF-6 + optional tier at your discretion); ONE commit; branch stays LOCAL; completion report requests the targeted re-check

Delegated-condition verification (run at this seat at issue time, `211929`):

1. **Ruling chain:** MF-1 ruled Option A (`204159`), family-endorsed with residual
   sharpenings (`205443`); MF-2..MF-6 endorsed in both. Mechanism step 1 (design rev3→
   rev4 with its own approve) is complete; this is step 2.
2. **Design gate:** `DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-design-rev4-review`, on design
   bytes `c1c3188b…@91d6841` (IN_REPLY_TO above). Design file re-hashed at issue time:
   still `c1c3188be6f4b3de5db72555e285fd292697927adcb70cd2df6695a850260f57`.
3. **Plan lock:** rev2B unique chain stands (`438365bd…` re-hashed at issue time,
   unchanged); the fold is panel-directed scope ON TOP of the completed plan per the
   ruled mechanism — no plan re-review owed (B2 fold precedent; the ruling directs this
   dispatch shape directly).
4. **Branch:** `s4-matrix/r48-carrier` re-pinned at issue time =
   `29796bbe3929429d2d959278053089c5f852e5e2` (three task commits over BASE `6047ab03…`,
   LOCAL, unpublished, untouched since the panel).
5. **Lineage:** fresh unique DISPATCH_ID (cardinality 1 verified in INDEX); each chain
   link a sole ID holder: this → `…design-rev4-review` (`211611`, approve) →
   `…design-rev4` (`210907`, my rev4 request) → `…design-rev3-review` (`210140`,
   must-revise) → `…design-rev3` (`205408`) → `…mf1-ruled` (`204159`) →
   `…panel-verdict` (`202753`).
6. **Hard triggers:** none — wire shape unchanged by the fold (rev4 approve confirms);
   floor narrowing ruled compatible (floor's objection window open on the ruling CC, no
   objection on record at issue time); no new authority.

SCOPE_DIFF:
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- src/core/pack/pack.cpp -> in
- src/adapters/adapter.hpp -> in
- src/core/open/sessions.cpp -> in
- tests/test_manifest.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE (per IN path — which fix lands where):
- src/core/manifest/manifest.hpp: MF-1 — `non_degenerate` in the validity predicate; `make_packer_home` factory declaration
- src/core/manifest/manifest.cpp: MF-1 — tightened `packer_home_valid` + factory definition; MUST reuse the ONE predicate core (no duplicated threshold branches — the approve's hard constraint)
- src/core/pack/pack.cpp: MF-1 — `packer_home_carrier` body collapses to the one-line factory call; optional P1 move-nit at your discretion
- src/adapters/adapter.hpp: no required change — in-scope only if the optional tier touches it
- src/core/open/sessions.cpp: no required change — transport untouched
- tests/test_manifest.cpp: MF-1 tests 11b/13b; MF-2 carrier-engaged exact-bytes golden; MF-3 flavor wrong-type row; optional idiom tier
- tests/test_pack.cpp: MF-1 test 18b honest-reach retitle; MF-5 hermeticization; optional ScopedEnv generalization
- tests/test_sessions.cpp: MF-6 both-legs per-call seam + absent-arm falsifier
- tests/test_adapter_claude_install.cpp: MF-4 dual-arm byte-identity receipt
- tests/test_adapter_codex_install.cpp: MF-4 dual-arm byte-identity receipt

The work, ONE commit on the branch (strict TDD — RED first where behavior changes):

- **MF-1 (per approved rev4, `c1c3188b…`):** `non_degenerate` thresholds posix `>1`,
  wsl `>7`, windows drive `>3`, windows extended `>4`; `make_packer_home` public
  factory (engaged iff classify + non_degenerate; postcondition `valid()`); capture =
  one-line factory call. §9 rows 11b (degenerate parse matrix + positive control
  `\\?\C:\Users\x` + serialize collapse extension), 13b (factory unit rows — the
  capture-boundary falsifier), 18b (`HOME=/` → wire absent, integration arm).
- **MF-2:** carrier-ENGAGED exact-bytes golden pinning position, adjacency, and
  home-before-flavor order (the existing golden stays as the absent-layout pin).
- **MF-3:** one row `"packer_home":"/x","packer_home_flavor":42` expecting detail
  exactly `packer_home_flavor`, in a flavor-detail case (NOT the `packer_home`-detail
  array).
- **MF-4:** replace BOTH adapter "receipt" tests with dual-arm inertness receipts:
  install twice against identical fixtures — engaged vs `nullopt` — and assert the
  produced store bytes are IDENTICAL (fails the day an adapter starts interpreting the
  value).
- **MF-5:** hermeticize the pack capture case: temp-dir guards for `CLAUDE_CONFIG_DIR`
  AND `CODEX_HOME` alongside the HOME guard; replace the real `/Users/jack` row with
  the file's own hermetic idiom (e.g. `(root / "home").string()`); no unit test may
  walk the operator's live stores.
- **MF-6:** second agent + per-call vector of observed values on the `CountingAdapter`
  seam; assert BOTH legs receive the identical value, and give the absent arm its own
  falsifier (it must fail if the `.packer_home` copy is deleted).
- **Optional tier at your discretion** (panel record `006144b2…` lists them verbatim):
  tests #3/#4/#6 matrix-completion rows, perf P1 move, idiom I1-I7. Fold what you
  judge worth it; disclose what you decline — silence is not a decline.

Boundaries: `pack.cpp::path_flavor` and `source_path_flavor` semantics are a
STOP-AND-ROUTE line (R-4.12, `205443`) — any forced contact stops and routes back to
me, never a silent consolidation. Both Step-3 fences untouched. No duplicated threshold
logic anywhere (the re-check is instructed to reject it). Wire shape byte-identical for
every non-degenerate value.

Gates, then report: focused carrier suite strict RED→GREEN for the new behavior; full
macOS product row (the `harness-e2` 180.06s stale-timeout red remains the disclosed
ruled class — durable-600 fix rides B2); Ubuntu 24.04 amd64 Docker leg (R-3.48 verdict
shape; the 5+3 emulation reds remain the measured disclosed class per `183936` +
`192358` — report exact observed totals). Completion report with the new head SHA and
both evidence legs requests the TARGETED RE-CHECK (lead + owning lenses at the exact
new head; it will reject duplicated thresholds, `source_path_flavor` contact, or a
factory/capture shape diverging from rev4). Branch stays LOCAL — no push, PR, remote
CI, merge, or release; publication by separate token; human lenses stay unrouted until
the re-check is clean. Inline questions and blocker deviations route back to me; the
operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's and orchestrator's untracked relays and one s4-floor relay, preserved untouched)
Fresh at 20260809-211929 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-FOLD-MF1-MF6-DISPATCH-20260809-211929.md` → TO `s4-matrix.implementer`
- design rev4 `c1c3188b…@91d6841` (approved `211611`) + plan `438365bd…` (rev2B chain) → the one live fold authorization; ONE commit; targeted re-check downstream
- R-4.12 STOP-AND-ROUTE boundary + Step-3 fences → untouched or route back
- publication/CI/merge/release → NOT dispatched; release hold ABSOLUTE
