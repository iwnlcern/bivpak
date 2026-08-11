## SITREP — B2 cycle-2 re-panel found M-4 does NOT hold; the in-universe fixes fold, but ONE cell is master's: does the origin-disclosure invariant require needling the bare packer home/username, or is it narrowed to the origin-path/id UNION? Routed with the security lens's narrowest-provable statement.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-m4-scope
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-review-fold-complete
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the invariant's SCOPE (what counts as packer identity the store must never receive) is a design/DNA definition, master's to set; the pair folds the mechanism, not the definition
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-REVIEW-FOLD-COMPLETE-20260808-162316.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: ROUTED — the M-4 invariant-scope cell from the B2 re-panel; the rest of cycle 2 folds in-universe

The master-endorsed B2 re-panel (security + correctness + tests, all executed) returned
MUST-FIX: M-4 (the containment invariant under the per-session radius you ruled) does NOT
hold at fold head `d6cceba`. Full record:
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-floor-slice-b2-repanel-d6cceba.md`.
Three Criticals; two are in-universe and folded to the implementer (companion REVIEW-FOLD
`REVIEW-FOLD-PLANNER-B2-CYCLE2-PANEL-DISPATCH-20260808-210909.md`): the never_rewrite scan
is encoding-blind (B2C2-1), and the nine staged pack tests measure the operator's real
stores (B2C2-3). One Critical has a cell above the pair.

## The routed cell — B2C2-2, invariant SCOPE

The origin-scan needle set today is each session's OWN origins/ids only
(`claude install.cpp:651-656/689-693`): `origins` from `session.record.original_path`,
`origin_ids` from this session's image id + its own message uuids + its own primary. A
sibling session's path, another session's id, and the bare packer username/home are never
needles. The security lens's key structural point (which retires part of your B2-1
reasoning): **widening the refusal RADIUS cannot fix this** — "a verified-clean sibling
carries no packer identity by definition" is false, because "clean" is measured against
that session's own needles only; session B is never scanned for session A's origin under
ANY radius.

Two parts, split by authority:
- **IN-UNIVERSE (folded, no ruling needed):** widen the needle set to the IMAGE UNION of
  all origin spellings and all origin ids across the manifest, so every session's output is
  scanned against every session's origins/ids. This closes the sibling-path and
  cross-session-id vectors and is a mechanism change the pair owns.
- **MASTER'S CELL (routed):** does the origin-disclosure invariant additionally require
  refusing the bare packer HOME/USERNAME prefix (not part of any session's original_path as
  a full string), or is the invariant explicitly NARROWED to "no origin-path spelling and
  no session/message id reaches the store"? The security lens's narrowest-provable
  statement of what the union scan will guarantee:
  > For each published session S, S's bytes contain no literal-or-decoded occurrence of any
  > origin-path spelling or any origin/message id present ANYWHERE in the image — but a bare
  > home/username substring not equal to a full origin-path spelling is not needled.
  If the DNA invariant ("username, client-folder name … must never reach the store") is to
  be met literally, a packer-home-prefix needle (or an explicit narrowing of the invariant
  text) is required. That is a definition call, not a code defect — routed to master.

## What proceeds without the ruling
The implementer folds B2C2-1 (decode keys+values + raw floor), B2C2-2's union widening,
B2C2-3 (pin HOME ×9), and the three Importants (B2C2-4 collector class-set, B2C2-5
retained-torn pack warning, B2C2-6 falsifiers) at the amended one-commit head; the
home/username needle waits only on your ruling and does not block the rest. Because
B2C2-1/B2C2-2 change verify semantics again, the amended head owes a THIRD targeted
re-panel (m-4 re-confirmed). Also carried up already: the inherited I-3 object-key leak is
in this same family — B2C2-1's fix decodes keys as well as values so B2 does not reintroduce
it in the new arm, but the jsonl-arm key leak remains your/master's I-3 call. Merge/release
the operator's; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — the re-panel was read-only/execution at d6cceba and my verification read-only git plumbing; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-B2-M4-INVARIANT-SCOPE-AUTHORITY-20260808-210909.md` → `s4.orchestrator-planner`
- M-4 invariant SCOPE (home/username needle vs narrowed invariant) → master ruling; the union-widening folds regardless
- companion REVIEW-FOLD `REVIEW-FOLD-PLANNER-B2-CYCLE2-PANEL-DISPATCH-20260808-210909.md` → `s4-floor.implementer` (B2C2-1..B2C2-6)
- inherited I-3 object-key leak → same family; B2C2-1 decodes keys+values so B2 doesn't reintroduce it; jsonl-arm key leak stays master's I-3 call
