## DISPATCH (fold) — the targeted re-panel at C `b8083be` / B2 `20e56bc` FAILED (M-4 and B1-round-trip lenses; A11-conformance and tests lenses PASS). Six gating findings fold at the pair: the B1 same-set invariant closed over PATHS but is OPEN over CONTENT (a `{}` subagent body — the product's own fixture shape — stages then hard-aborts the re-pack), and the A2 union closure missed the CHILD/alias dimension in both adapters. Panel record: `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-repanel-b8083be-20e56bc.md`. Three items route UP in the companion SITREP (WSL corridor → m-2; pre-existing store-filename child-id vector → master; restore-side `.biv` caveat). This relay carries a FRESH delegated token for ONE bounded fold cycle.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-repanel-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate at this hop — pair-scope fold under delegated authority; downstream gates unchanged (targeted re-check of the fold, fresh paired hand-up, master's condition-3, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-FOUR-FOLDS-ADDENDUM11-FILED-20260810-083626.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-repanel-b8083be-20e56bc.md (the panel record; finding IDs below refer to it)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: FOLD — F-1..F-6 (staged-reader content gates + refused-row child-alias union gaps + blast radius) in ONE bounded cycle on the pair; falsifiers named; WSL target semantics EXCLUDED (routed to m-2)

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/core/open/sessions.cpp -> in
- src/adapters/rewrite_common.cpp -> in
- src/adapters/rewrite_common.hpp -> in
- harness/bivharness/e3.py -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_sessions.cpp -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/install.cpp -> F-4 gate at :750-752 (spot-verified at 20e56bc by this seat); F-1..F-3 writer side if the fold chooses writer-establishes
- src/adapters/codex/install.cpp -> F-5 union loop :454-476 lacks identity_for_artifacts(child.artifacts, child.original_id) (spot-verified at 20e56bc by this seat)
- src/adapters/claude_code/claude_code.cpp -> F-1..F-3 staged-reader content gates at :435-443/:481-499; F-6 error propagation
- src/adapters/codex/codex.cpp -> the codex mirror of the content-gate class at :716-721 (prove unreachable or align, panel-required)
- src/core/open/sessions.cpp -> non-gating A11-lens #1 (call origin_spellings) if elected; any writer-establishes leg of F-1..F-3
- src/adapters/rewrite_common.cpp -> shared predicate/writer-helper surface for the elected fold shape; NOT the :982 target semantics (routed to m-2, hard OUT)
- src/adapters/rewrite_common.hpp -> declarations for the same
- harness/bivharness/e3.py -> A3 both-anchor re-fire when anchored collectors change
- tests/test_adapter_claude_install.cpp -> F-4 falsifier (NON-staged refused-row alias needled); tests-lens minors if elected
- tests/test_adapter_codex_install.cpp -> F-5 falsifier (staged+version-refused CHILD alias needled)
- tests/test_adapter_claude_collect.cpp -> fixture-shape reuse for the `{}` subagent case
- tests/test_adapter_codex_collect.cpp -> codex-mirror fixtures if the alignment leg lands
- tests/test_pack.cpp -> F-1/F-2/F-3 round-trip falsifiers; F-6 blast-radius falsifier; FX-A11-4 live section + 8a/8b byte-identity if elected
- tests/test_sessions.cpp -> writer-guard falsifiers (tests-lens #3) if elected

## The six gating folds (panel record has full detail; the bytes cited there govern)

**F-1 (Critical) / F-2 / F-3 — staged-reader CONTENT gates.** Governing invariant: **the
staged reader accepts every workspace the writer can legally produce** — the same-set bar
over CONTENT, not only paths. A `{}` subagent `.jsonl`, an id-less main transcript
(filename-stem identity), and a body-version-less transcript are all legally staged today
and all currently kill the whole re-pack. You choose the side that moves (reader
tolerates what install guarantees, or writer establishes the invariant at staging) — but
a PRESENT-and-MISMATCHED id must remain a typed refusal (that half is real integrity,
and the A11/planted-carrier posture leans on it), and no sealed A9 member may change
shape. **Codex mirror (panel-required): prove the codex staged reader's id gate
unreachable for legal writer output, or align it symmetrically — either way with
evidence in the report.**

**F-4 / F-5 — the A2 CHILD/alias union gaps.** F-4: remove/replace the staged-provenance
gate in the claude refusal-branch harvest so it matches the admitted branch's coverage.
F-5: insert the child artifact-derived identity into the codex all-records union loop.
Both are completions of the granted A2 fold (union completeness before version-floor
decisions), not new scope.

**F-6 — blast radius.** Master's original B1 grant already offered per-session
skip-and-warn as an alternative to whole-pack abort; with F-1..F-3 live the whole-pack
abort is load-bearing harm. Your choice within the grant, stated with rationale; if
alignment (F-1..F-3) genuinely empties the reachable refusal set for legal images, the
abort may stand — say so with the enumeration.

**Falsifiers required:** (1) `{}` subagent body round-trips (open consent-NO → pack
succeeds); (2) id-less main transcript round-trips; (3) missing-body-version case handled
per your elected shape (round-trips or per-session-refuses WITHOUT killing siblings);
(4) NON-staged version-refused claude row's child alias IS needled (the existing test
covers only the staged branch); (5) codex staged+version-refused CHILD artifact-derived
alias IS needled; (6) blast-radius: one refusing staged session must not lose unrelated
sessions/the other adapter (or the enumeration proving the refusal set empty for legal
images).

## Hard OUT of this token
- `rewrite_common.cpp:982` target semantics and the A11 PRESENT-membership formula (the
  WSL corridor) — routed to m-2 in the companion SITREP; do not touch, even fail-closed.
- R-b (subtree destination filenames carrying origin child ids) — routed to master.
- Any sealed A9 member shape change; any `.github` change; merge, push, release.

## Ceremony and the return
One bounded fold per owning head (C writer-side only if elected; readers/adapters on B2),
subjects preserved, A3 both-anchor re-fire when anchored collectors change, macOS +
Docker linux/amd64 suites honestly green with the standing disclosed classes, worktrees
clean, republish to PR #22/#23 with explicit leases, then REVIEW-FOLD report with
FOLD_SCOPE and the falsifier receipts. On it I convene the targeted re-check scoped to
the fold delta (byte-identical files carry). Non-gating items (panel record §Non-gating)
at your discretion with disclosure. Carry forward verbatim: C must never land without B2
(the A10.3 stacking observation). Nothing seals; `231437` stays WITHDRAWN; merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — panel convening + spot-verification at 20e56bc (claude install.cpp:739-763 vs :786-804; codex install.cpp:452-480; claude_code.cpp:435-443/:473-499; rewrite_common target check pre-existence at 0653fea); this relay + companion SITREP + panel record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-REPANEL-FAIL-FOLD-DISPATCH-IMPL-TOKEN-20260810-090631.md` → `s4-floor.implementer`
- targeted re-panel FAILED (M-4 + B1 lenses; A11 + tests PASS); F-1..F-6 fold in ONE bounded cycle under this token; six falsifiers named; codex content-gate mirror proven-or-aligned
- WSL corridor + store-filename child-id vector + `.biv` restore caveat routed UP (companion SITREP); hard OUT here
- return = REVIEW-FOLD with receipts → targeted re-check of the fold delta → fresh paired hand-up; C never lands without B2; release hold ABSOLUTE
