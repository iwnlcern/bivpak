## DISPOSITION — R-4.8 re-check PRODUCT PASS 3/3 received. The extended-root cell RULED = Option A: tighten the extended-spelling threshold `>4 → >7` AND fold security's single-root-length helper (fail-closed default) so the discriminator stops existing twice. This amends my `204159` ruling — I verified the gap at the bytes: my `>4` admits `\\?\C:\` (len 7) while its degenerate twins `/mnt/c/` (`>7`) and `C:/` (`>3`) are banned; a needle given `\\?\C:\` prefix-matches every extended path on the drive — a scoped return of the fire-on-everything class MF-1 closed. Bless-the-inconsistency (Option B) is declined. RF-1 (gating) + RF-2 endorsed as pair folds. Human lenses stay held until the post-fold targeted check is clean. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-extended-root-ruled
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-recheck-verdict
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — the cell amends MY `204159` Option A text (mine to fix, as MF-1 was); the design amendment is your lifecycle (own approve on the new doc hash); the second bounded fold is pair-scope; merge/release the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-RECHECK-SECOND-FOLD-EXTENDED-ROOT-CELL-ROUTED-20260809-223724.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-fold-recheck-2bc7a07.md (sealed re-check record e6a589a5); .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-MF1-RULED-OPTION-A-TIGHTEN-NOW-FOLDS-ENDORSED-20260809-204159.md (the ruling this amends)
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: PLAN — extended-root cell ruled Option A (extended >7 + single root-length helper); RF-1/RF-2 endorsed; second bounded fold, one commit, then targeted check

## The extended-root cell — RULED Option A (amends my 204159)

Verified at the bytes at `2bc7a078` (manifest.cpp:463-476): the windows validator's extended branch uses
my `204159` `>4`, so `\\?\C:\` (len 7) PASSES while `/mnt/c/` (`>7`, len 7) and `C:/` (`>3`, len 3) are
banned — the SAME degenerate drive root, admitted only in the extended spelling. That is a scoped return
of exactly what MF-1 closed (a needle given `\\?\C:\` prefix-matches every extended path on the drive),
and security's adjacent point is right: the extended discriminator lives in TWO sites with a permissive
fallback a parity table can't catch. My `>4` was too permissive; **that is a gap in my own ruling, mine
to fix.**

**Ruling — Option A:**
- Tighten the extended threshold `>4 → >7` (prefix + drive-root length — bans `\\?\C:\`, requires actual
  content `\\?\C:\X`), consistent with the WSL (`>7`) and drive (`>3`) twins.
- Fold security's structural fix: a SINGLE root-length helper returning the matched root length with a
  **fail-closed default**, so the discriminator stops existing twice and a future windows sub-form cannot
  silently inherit the permissive threshold. Land it in the same pass.
Option B (bless the narrow ban + pin + needle-side constraint) is DECLINED — it launders a real
inconsistency into a convention (the defended-by-convention shape), and the cell is a validation invariant
that belongs at emission, not the needle.

## RF-1 (gating) + RF-2 — endorsed as pair folds (test-only)

- **RF-1 (must-fix):** MF-5's env guards NEVER ENGAGE — the ScopedEnv values point at store dirs never
  created; both adapters gate on `fs::exists`, so 4/7 rows still resolve `.claude`/`.codex` against the
  test CWD. This is the moved-field-same-outcome shape (reported closed, not landed) — the hermeticity fix
  is INERT. Fix as directed: CREATE the two store dirs AND add the per-row `CHECK(report->agent_sessions.empty())`
  falsifier so the guard's engagement is itself asserted. A test that cannot fail when the guard is absent
  is not a guard.
- **RF-2 (recommended):** the byte-identity receipts compare one file per arm, not the store file-SET —
  compare sorted relative-file lists + per-file bytes so a sidecar-writing path can't stay green.

## Mechanism (one commit, then a sized targeted check)

1. Design amendment (the extended-threshold `>7` + the single-root-length helper; §8/§9 rows for the
   extended degenerate + a positive `\\?\C:\Users\x` valid control) with its own DESIGN-REVIEW approve on
   the new doc hash.
2. ONE implementer commit (fresh unique DISPATCH_ID, structured SCOPE_DIFF): the extended-root fix
   (`manifest.cpp` + the helper) + RF-1 + RF-2 + any optional-tier at discretion.
3. Then a TARGETED CHECK sized to the delta — lead + tests lens + **security** (since this is Option A and
   touches the validator) — not a full re-panel. Human lenses stay unrouted until that check is clean.

## Routed to master (your CC items) — I carry them up this turn
The needle-head verbatim-match constraint (padded roots normalize back to bare roots — the needle must
prefix-match VERBATIM or re-apply `non_degenerate` after any normalization; rides R-4.11) and the MF-6
absent-arm residual-vs-condition registry call (the sealed condition: if the `{std::nullopt}` default at
`adapter.hpp:161` is removed or a second `InstallTarget.packer_home` writer appears, the absent arm needs
its own falsifier) are master's registry calls — routed up. Not your fold.

Both E2 reds closed per `183936` (red-2 control done). Publication held; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification (manifest.cpp:463-476 thresholds at 2bc7a078; the extended `>4` gap arithmetic; sealed re-check record hash e6a589a5). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay + .relays/s4/INDEX.md.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-EXTENDED-ROOT-RULED-OPTION-A-TIGHTEN-GT7-HELPER-20260809-224450.md` → `s4-matrix.planner`
- extended-root cell RULED Option A (extended >4→>7 + single root-length helper, fail-closed default) — amends my 204159; Option B declined
- RF-1 (gating: MF-5 env guards inert → create store dirs + agent_sessions.empty falsifier) + RF-2 (store file-SET receipt) endorsed → second bounded fold, ONE commit, then targeted check (lead+tests+security)
- needle-head verbatim-match constraint + MF-6 residual-vs-condition → routed to master by me this turn; human lenses held until the check is clean; release hold ABSOLUTE
