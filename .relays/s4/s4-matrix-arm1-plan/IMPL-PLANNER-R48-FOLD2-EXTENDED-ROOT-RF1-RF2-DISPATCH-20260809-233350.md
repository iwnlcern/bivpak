## IMPL SECOND-FOLD DISPATCH — R-4.8 re-check fold: rev6 extended-root fix (`classify_carrier_root` + `>7` + boundary controls) + RF-1 both halves + RF-2, ONE commit on the existing branch, then the sized lead+tests+security targeted check; all conditions verified at this seat at issue time; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-arm1-r48-fold2-impl
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated fold under the ruled mechanism (`224450` step 2) with the rev6 design approve landed on the exact hash; publication/remote-CI/merge are NOT dispatched (P5 boundary — separate token); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: IMPL — second bounded fold on `s4-matrix/r48-carrier` (rev6 validator fix + RF-1 + RF-2 + optional tier at your discretion); ONE commit; branch stays LOCAL; completion report requests the targeted check

Delegated-condition verification (run at this seat at issue time, `233350`):

1. **Ruling chain:** extended-root cell ruled Option A (`224450`, amending `204159` at
   the orchestrator's own hand); RF-1 (gating) + RF-2 endorsed there. Mechanism step 1
   (design rev5→rev6 with its own approve) is complete; this is step 2.
2. **Design gate:** `DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944`
   — verdict approve, sole holder of `s4-matrix-arm1-r48-design-rev6-review`, on design
   bytes `e653457e…@2c7b887` (IN_REPLY_TO above). Design file re-hashed at issue time:
   still `e653457e0d738b633d126debb7d839192aa391e6f4d273f95cb8180bfefe0efb`.
3. **Branch:** `s4-matrix/r48-carrier` re-pinned at issue time =
   `2bc7a078302f740721ac0d6412c843a8172368a5` (the re-checked fold-1 head; product PASS
   3/3 in the sealed record `e6a589a5…`), LOCAL, unpublished, untouched since.
4. **Lineage:** fresh unique DISPATCH_ID (cardinality 1 verified in INDEX); sole-holder
   chain: this → `…design-rev6-review` (`231944`, approve) → `…design-rev6` (`231310`) →
   `…design-rev5-review` (`230557`, must-revise) → `…design-rev5` (`225500`) →
   `…extended-root-ruled` (`224450`) → `…recheck-verdict` (`223724`).
5. **Hard triggers:** none — wire shape unchanged (rev6 approve confirms); the narrowing
   class ruled compatible and deepened in-direction with the floor CC'd throughout, no
   objection on record at issue time; no new authority.

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
- src/core/manifest/manifest.hpp: rev6 fix — only if `CarrierRoot`/`classify_carrier_root` needs a public declaration; keeping it TU-local beside the predicate is equally conformant (your call; disclose the choice)
- src/core/manifest/manifest.cpp: rev6 fix — `classify_carrier_root` single grammar/root authority ({wsl,7} | extended {windows,7} | drive {windows,3} | posix {posix,1} | nullopt FAIL-CLOSED); `classify_absolute` becomes its behavior-identical `.flavor` projection; `packer_home_valid` = classify-match + `size() > root_length`, the second extended discriminator DELETED
- src/core/pack/pack.cpp: no required change (capture already routes through `make_packer_home`); in-scope only if the optional tier touches it
- src/adapters/adapter.hpp: no required change
- src/core/open/sessions.cpp: no required change
- tests/test_manifest.cpp: rev6 rows — 11b gains the three degenerate extended roots (strict RED first: they PASS today) + BOTH 8-byte accept controls (`R"(\\?\C:\x)"`, `"//?/C:/x"` — regression pins, green both sides); 13b gains the same five factory rows; optional F-6 split of 13b into its own TEST_CASE
- tests/test_pack.cpp: RF-1 BOTH halves — `create_directories` the two guarded store dirs before the ScopedEnv guards AND `CHECK(report->agent_sessions.empty())` per row (the file's own idiom at :287); optional correctness-LOW precondition guard on the temp-derived HOME flavor
- tests/test_sessions.cpp: no required change
- tests/test_adapter_claude_install.cpp: RF-2 — capture the sorted relative-file LIST of the store in both arms and assert list equality + per-file byte equality (claude needs the file-list read added); optional: sibling temp roots (F-4), named `kIdPlaceholder` (F-5), full-`id_map` normalization (correctness LOW)
- tests/test_adapter_codex_install.cpp: RF-2 same (codex already computes `relative_files(store)` — extend to both arms + per-file compare); same optional tier

The work, ONE commit on the branch (strict TDD where behavior changes — the three
degenerate extended rows must be RED at `2bc7a078` before the validator moves):
rev6 fix + RF-1 + RF-2 as evidenced above; optional tier at your discretion with
declines DISCLOSED (silence is not a decline). Boundaries: `pack.cpp::path_flavor` and
`source_path_flavor` semantics remain the R-4.12 STOP-AND-ROUTE line; both Step-3
fences untouched; NO duplicated grammar/root-length discrimination anywhere (the check
will reject it); the parity pin (§9-14) must stay green unmodified — if the projection
form breaks it, STOP and route, do not adjust the pin.

Gates, then report: focused carrier suite (RED→GREEN shape for the degenerate rows);
full macOS product row; Ubuntu 24.04 amd64 Docker leg (R-3.48 verdict shape; the
measured emulation classes remain disclosed-not-relabeled — report exact observed
totals and label variance as variance, as you did with 5+2). Completion report with the
new head SHA and both evidence legs requests the TARGETED CHECK (lead + tests +
security at the exact new head; its rejection list per the rev6 approve: duplicated
grammar/root discrimination, `source_path_flavor` contact, a missing 8-byte control in
either spelling, a vacuous RF-1 guard, a one-file RF-2 receipt). Branch stays LOCAL —
no push, PR, remote CI, merge, or release; publication by separate token; human lenses
stay unrouted until the check is clean. Inline questions and blocker deviations route
back to me; the operator's release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's and orchestrator's untracked relays and floor-lane relays, preserved untouched)
Fresh at 20260809-233350 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-DISPATCH-20260809-233350.md` → TO `s4-matrix.implementer`
- design rev6 `e653457e…@2c7b887` (approved `231944`) → the one live second-fold authorization; ONE commit; targeted check downstream
- R-4.12 STOP-AND-ROUTE + parity-pin-stays-green-unmodified + Step-3 fences → untouched or route back
- publication/CI/merge/release → NOT dispatched; release hold ABSOLUTE
