## IMPL DISPATCH — master's four gating folds (A1+A2 union under-seed; B1 staged-subtree class mismatch; B2 codex sidecar multi-path): the LIVE token for ONE bounded fold on the C/B2 pair, with falsifiers, the B2 STOP-and-route carrier-shape condition, and the A3 re-fire. The core HOLDS; these are the seams the scoped panels never tested.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-four-folds
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
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
- src/adapters/claude_code/install.cpp -> standing 34-row restack union (205244; both paneled ranges); FOLD A1/A2 + B1-writer side + the carve-out contradiction
- src/adapters/codex/install.cpp -> standing union (both paneled ranges); FOLD A2 + the non-gating fresh-InstallResult hazard
- src/adapters/claude_code/claude_code.cpp -> standing union (B2 paneled range); B1 re-collector class set (ANCHORED — A3 re-fires)
- src/adapters/codex/codex.cpp -> standing union (B2 paneled range); B2 resolver (ANCHORED — A3 re-fires)
- src/core/open/sessions.cpp -> standing union (slice C paneled range); the A9 sidecar WRITER, B2 within-shape side if elected
- src/adapters/rewrite_common.cpp -> standing union (150142 grant lineage); shared same-set predicate home + parse_staged_sidecar
- src/adapters/rewrite_common.hpp -> standing union (150142 grant lineage); declaration only if a shared predicate is elected
- harness/bivharness/e3.py -> standing union (B2 paneled range); the A3 both-anchor recapture that MUST re-fire when the collectors change
- tests/test_adapter_claude_install.cpp -> standing union; FOLD A falsifiers (claude)
- tests/test_adapter_codex_install.cpp -> standing union; FOLD A falsifiers (codex)
- tests/test_adapter_claude_collect.cpp -> standing union; B1 reader-side + round-trip falsifier support
- tests/test_adapter_codex_collect.cpp -> standing union; B2 resolver falsifier support
- tests/test_pack.cpp -> standing union; the ROUND-TRIP falsifiers (open consent-NO → pack succeeds), B1/B2
- tests/test_sessions.cpp -> standing union; sidecar-writer coverage if the B2 within-shape fix touches sessions.cpp
HUMAN_GATE_REQUIRED: no — pair-Planner conditional dispatch: orchestrator-delegated conditional dispatch at the initial PLAN dispatch; Implementer plan review = approve (`s4-floor-pair-plan-review-approve`); mechanical SCOPE_DIFF all-in (every row a member of the standing 34-row restack union, verified 205244/235707); no OPEN hard trigger — all four folds are RULED by master (`233408`, carried `234510`, I-3 precedent), and the ONE potentially inexpressible cell (a B2 carrier-SHAPE change) is an explicit STOP-AND-ROUTE inside this token, never a local answer. Merge and release remain the operator's alone; the release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-FOUR-GATING-FOLDS-CARRIED-DOWN-A1-A2-B1-B2-20260809-234510.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: the live token for master's four gating folds — analyze B2's shape question FIRST; fold A1+A2+B1 (and B2 if within-shape) with the four falsifiers; both heads amendable under their one-commit laws

Master's operator-directed global semantic check held the C/B2 pair and ruled four folds
(no deferral — the I-3 precedent). On the record before the work: the A2 cell is the codex
alias caveat I earlier routed as a candidate residual/non-blocker — master widened it to a
LIVE gating leak across both adapters, and the mis-weight was mine: an origin-ID leak
vector gates even when pre-existing and low-realism. Lesson recorded. This token makes the
fold live.

## Sequencing rule — analyze B2's shape question FIRST (cheap, before any edit)
Determine whether B2 (codex sidecar multi-path) closes WITHIN the sealed A9 shape — e.g.
per-row `original_path` recoverable from the EXISTING sealed members — or requires a
row-to-pair edge / any new field in the sealed content. **If a shape change is needed:
STOP on B2 immediately and route the cell up (it goes to m-2 for the addendum route via
the orchestrator); do NOT amend the sealed carrier shape at the pair.** A1/A2/B1 work
proceeds locally in the worktrees while B2's ruling is out; the COMMITS wait so the return
stays one bounded fold per head.

## FOLD A — union under-seeding (A1 truncation + A2 artifact-derived id); both adapters
Master's fold shape, verbatim in substance:
- derive the image-ID union from `records` — INCLUDING each record's artifact-derived
  primary identity — BEFORE the version-floor gate, never from `prepared`;
- collect-then-decide: needle harvesting NEVER `break`s on a refusal — collect ALL
  artifacts' origin uuids, THEN set the refusal (the claude destinations-loop
  `break` at the `undecodable_line` site is the confirmed A1 defect; the pre-refused
  branch's `continue` walk is the correct pattern).
**Falsifiers (required, both adapters where applicable):**
(1) a staged+version-refused sibling whose artifact-derived ALIAS id IS needled;
(2) a refused-mid-collection session that still FULLY seeds the union (an early-artifact
refusal must not drop a later artifact's origin uuid).

## FOLD B1 — claude staged-subtree class mismatch (round-trip HARD-ABORT, exit 4)
The installer writes any safe subtree artifact ending `.jsonl`/`.txt`/`.meta.json` with no
directory constraint; the staged RE-collector accepts only `subagents/*.jsonl`,
`subagents/*.meta.json`, `tool-results/*.txt` and hard-errors (`staged_subtree_class`)
FIRST in `collect()` — so a legal consent-NO open produces an unpackable workspace.
**My proposal (the side that moves): the READER widens to the WRITER's set** — the
re-collector accepts exactly what the installer places (safe-relative + the three
suffixes, directory-unconstrained), preserving already-paneled install behavior and the
class check's real intent (refusing foreign/unsafe members). Prefer ONE shared predicate
(rewrite_common) consumed by both sides so the same-set invariant is structural; a
duplicated predicate with a writer/reader parity falsifier is acceptable if the shared
home forces more surface. If you find same-set genuinely unworkable, skip-and-warn
per-session is master's sanctioned alternative — say so in the report, do not silently
elect it. **Round-trip falsifier required:** open a legal image consent-NO (incl. e.g.
`<id>/notes.txt`) → `biv pack` the workspace → SUCCEEDS with the staged sessions carried.

## FOLD B2 — codex sidecar multi-path (subject to the shape analysis above)
One image routinely holds distinct `original_path` values (descendant-cwd admission);
consent-NO unions their pair sets into ONE sidecar, which
`resolve_codex_staged_original_path` then rejects (`invalid_staged_sidecar`) — same
hard-abort at re-pack. If per-row `original_path` is recoverable within the sealed
members, fold it (writer side in `sessions.cpp` on C's head if needed, reader side in
`codex.cpp`); otherwise STOP-and-route as above. **Round-trip falsifier required either
way** (two codex sessions with distinct original paths → consent-NO → pack succeeds).

## Non-gating (your discretion; DISCLOSE dispositions in the report)
The fresh-InstallResult report-integrity hazard (both adapters; unreachable today — fold
cheaply or register a condition); the slice-E coherence items (claude parent mapping;
version-refused parent vs clean child — both fail-closed, cosmetic); the
`unsupported_subtree_class` batch-wide-vs-per-session carve-out contradiction (clarify
intent; if skip-the-artifact is intended the prepare pass needs the same predicate).
Consent-NO "clean skip" drift: CONFIRMED INTENDED at master — no action.

## Placement, ceremony, gate
- Edits land on the OWNING head: `sessions.cpp` (writer) changes on C's commit at the
  `d6e44d9` line; everything else on B2's commit at the `0653fea` line. One-commit law per
  head, subjects preserved. Delta-equality bars grow only by the SCOPE_DIFF files placed
  on each head — report the exact per-head path sets.
- **A3 re-fires:** B1/B2 change the anchored collectors — run the four-check ceremony with
  BOTH-anchor recapture in `e3.py` at the final B2 head (five-owner mutation receipts, the
  standing 11-check shape). Run it, never assert it.
- FOLD_SCOPE `all-in` before any edit; any file beyond the SCOPE_DIFF is a NEW deviation
  routed up BEFORE the edit.
- Then: focused sets + full host suites at both final heads; the standing local Ubuntu
  24.04 `linux/amd64` Docker suites at both heads; merge-trees (main→C', C'→B2') clean;
  republish PRs #22/#23; report with both exact SHAs and the four falsifiers' RED→GREEN
  receipts. The fold's targeted re-panel (M-4 **and ROUND-TRIP lenses** at the new SHAs)
  follows via the orchestrator; on its pass, the fresh paired hand-up and master re-issues
  the paired condition-4. The `231437` paired authorization is WITHDRAWN until then.

DISPATCH IMPL

ACTIONS_GIT_REF: no product/test edits at this seat — this dispatch relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the candidates remain at C d6e44d9 / B2 0653fea (published) pending your fold
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state (two implementer SITREPs sit untracked awaiting their own lane commits; matrix relays untracked); this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-FOUR-FOLDS-DISPATCH-IMPL-TOKEN-20260810-000215.md` → `s4-floor.implementer`
- live token: ONE bounded fold — A1+A2 (union from records, collect-then-decide) + B1 (same-set, reader widens, shared predicate preferred) + B2 (within-shape or STOP-and-route to m-2 BEFORE touching the sealed shape) + four falsifiers; non-gating at discretion with disclosure
- A3 both-anchor ceremony re-fires (collectors change); placement per owning head; one-commit law each; suites + Docker + merge-trees + republish
- then the targeted re-panel (M-4 + ROUND-TRIP lenses) via the orchestrator → fresh paired hand-up → master re-issues the paired condition-4; release hold ABSOLUTE
