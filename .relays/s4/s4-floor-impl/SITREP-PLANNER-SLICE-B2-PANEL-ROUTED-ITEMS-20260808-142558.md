## SITREP — Slice B2 panel (MUST-FIX, two Criticals, folded to the implementer) raised two items ABOVE the pair: an authority call on the origin-leak refusal RADIUS, and a fence-2 hardening caveat (image-controlled rekey privilege). Plus a linkage note: B2's Criticals are the same origin-disclosure family as slice C's master-held ROUTED-3.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b2-panel-routed
PARENT_DISPATCH_ID: s4-floor-impl-2-b2-complete
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the refusal-radius scope is an authority call the dispatch reserved; the fence-2 caveat touches manifest.cpp (master-held); neither is the pair's to resolve
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-B2-COMPLETE-20260808-065636.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: ROUTED — two above-pair items from the B2 team-of-5 panel at 54a6c54; the in-universe fold (BL2-1..BL2-7) proceeds in parallel

The B2 panel returned MUST-FIX with two confirmed Criticals (origin bytes reach the
recipient's persistent host store un-scanned, via two independent vectors — a
`never_rewrite` default arm with no verify call, and a tautological `.txt` verifier that
reuses the rewriter's own boundary predicate; both reproduced by RUNNING the committed
code and re-confirmed at the bytes at this seat). Seven blockers are folded to the
implementer (companion REVIEW-FOLD
`REVIEW-FOLD-PLANNER-SLICE-B2-PANEL-DISPATCH-20260808-142558.md`). Two items are above the
pair.

## ROUTED-B2-1 — AUTHORITY: the origin-leak refusal RADIUS narrowed whole-set → per-session

Base refused the ENTIRE record set when an install-time origin scan found the packer's
absolute path or original session id in the bytes. B2 narrowed that to per-session: a
session with real origin hits now refuses ALONE and clean siblings publish
(`codex/install.cpp:494-504`, `claude_code/install.cpp:705-720`), sealed by a new test
("mixed verify failures preserve rows and publish clean siblings"). The row CLASS is still
forced to `containment_refused` (`sessions.cpp:485-489`), so this is refusal RADIUS + wire
detail (`rewrite_verify_failed`→`origin_path`/`origin_id`), not misclassification. The B2
dispatch authorized per-session scope ONLY for the `undecodable_line` (torn-tail) class;
extending per-session scope to the ORIGIN-LEAK class weakens a containment guarantee that
was previously whole-set. This is a design/authority call, not a coding fix. Question for
you (or master, via you): for the origin-leak class specifically, is per-session refusal
acceptable (clean siblings still install), or must an origin leak refuse the WHOLE image as
at base? I have HELD the radius at the pair (BL2-4) — the implementer will not change it
under the current fold — pending your ruling. The other two fix arms (restore verification
coverage for `never_rewrite`; make the `.txt` verifier independent) proceed regardless;
only the radius waits on you.

## ROUTED-B2-2 — fence-2 HARDENING CAVEAT: image-controlled rekey privilege

Security C-6 and correctness both surfaced (as a caveat, not a graded B2 finding): the
`staged` rekey privilege — which lets a staged record install under a minted identity
different from its manifest id — is derived from `record.provenance.locator` /
`discovery_tier`, which `src/core/manifest/manifest.cpp:256-263` reads via `required_string`
with NO enum validation. So a crafted `.bvpk` can DECLARE its own rekey privilege by
setting `locator: "staging"` / `discovery_tier: "staged"`. The B2 rekey guard is sound
against ACCIDENTAL mismatch but not against a hostile image. The fix lives in
`manifest.cpp` (validate the enum on read), which is fence-2 OUT for this pair. Routed for
an owner assignment (its own hardening head, or folded into Arm-1's schema act, your call);
not a B2 blocker (B2's guard behaves correctly given the field values it is handed).

## LINKAGE NOTE — B2's Criticals are slice C's ROUTED-3 family

Slice C's ROUTED-3 (master-held, your option-(a) recommendation) is the claude staged-tree
origin-PATH-keyed-directory leak. B2's BL2-1/BL2-2 are origin path + original session id in
un-scanned/undetected CONTENT installed to the store. Different mechanism, same
origin-disclosure family and the same DNA confidentiality concern. Flagging so master's
ROUTED-3 ruling and B2's content-scan fix land as ONE coherent origin-disclosure posture
rather than two divergent ones.

## What proceeds without you
The implementer folds BL2-1..BL2-3 and BL2-5..BL2-7 (in-universe) at the amended
one-commit head; because BL2-1/BL2-2 change install-time verify semantics, the replacement
head owes a TARGETED re-panel on the rewrite/verify surface (security + correctness + tests
on the fold delta), not merely my targeted re-check. PR #23 HELD at `54a6c54`; merge and
release the operator's; the release hold is ABSOLUTE. B2's A3 ceremony, `missing_staged_version`
fail-closed, the rekey-restricted-to-staged guard, the CANON-2.6 symlink/TOCTOU posture,
and the re-pack identity handling are all checked-clean with evidence across the panel.

ACTIONS_GIT_REF: no product/test edits at this seat — the panel was read-only at 54a6c54 and my verification read-only git plumbing; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-B2-PANEL-ROUTED-ITEMS-20260808-142558.md` → `s4.orchestrator-planner`
- ROUTED-B2-1 refusal-radius authority call (origin-leak class: per-session vs whole-set) → orchestrator/master ruling; HELD at the pair as BL2-4
- ROUTED-B2-2 manifest.cpp enum-validation for locator/discovery_tier (image-controlled rekey privilege) → fence-2 owner assignment
- ROUTED-3 family linkage → keep slice-C layout ruling + B2 content-scan fix consistent
- companion REVIEW-FOLD `REVIEW-FOLD-PLANNER-SLICE-B2-PANEL-DISPATCH-20260808-142558.md` → `s4-floor.implementer` (BL2-1..BL2-7)
