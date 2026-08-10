## PLAN — R-4.8 fold-3 (receipt determinism), rev0 on a unique chain: the UNCHANGED two-test-file scope from the invalid `030012` token, now filed as a reviewable pair-Planner PLAN so the replacement dispatch has its approving-review parent; PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-fold3-plan
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold2-check-verdict
IN_REPLY_TO: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-fold2-check-4c35f0f.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — plan-only relay; it grants nothing; the replacement `DISPATCH IMPL` waits on your PLAN-REVIEW approve AND the orchestrator's named-error disposition of the spent `030012` (routed in the sibling SITREP this same commit); the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN — fold-3 receipt determinism (TF-1/TF-2/TF-3), two test files, one commit; verdict wanted: approve | must-revise

Authority basis: the sealed fold-2 check record
(`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-fold2-check-4c35f0f.md`,
SHA-256 `c1e7eb8d…`) grades TF-1 a fold-introduced, test-confined Major and directs this
exact fold; the land-and-file alternative was declined at my seat with override open
upstream (`025909`). The technical scope is byte-identical to what you already read in
`030012` and raised no product objection to — only the authority chain changes.

BASE (to be re-pinned at replacement-dispatch time): `4c35f0fec8f845500ef7220e0df323d4924c8265`.

## Steps (ONE commit, two test files)

**T1 (GATES — TF-1) `tests/test_adapter_codex_install.cpp`:** normalize the minted
rollout stamp (`%Y-%m-%dT%H-%M-%S`) AND the `sessions/<Y>/<M>/<D>/` date components
alongside the installed id, BEFORE the relative path enters `receipt.files` and the
`receipt.contents` key. The store layout is fixed-width and this file already parses it
by offset (~:664) — reuse that idiom rather than a regex.
**T2 (TF-2, both files):** normalize EVERY id in `result->id_map`, not `front()` only —
per-install nondeterministic tokens are all normalized; this also defuses the
`children.clear()` trap the check record flags for future ID-bearing fixtures.
**T3 (TF-3, both files):** `REQUIRE_FALSE(receipt.files.empty());` before each receipt
returns. Optional while those lines move: a shared-per-file
`constexpr std::string_view kIdPlaceholder{"<installed-id>"}` used for both the
replacement and the advance (retires the magic `14U`).
**T4 (evidence):** TDD posture stated honestly — TF-1 is a flake fix with no
clock-controlled deterministic RED available; in lieu: (a) show the normalizer blanking
the stamp/date fields on the receipt's own output, and (b) a ≥50-iteration soak of both
receipt cases green on macOS, exact command and count disclosed. TF-3 is
RED-constructible at your discretion; disclose the choice. Then the focused carrier
commands + the full macOS product row. The Docker leg is NOT re-run for a two-test-file
delta (my sizing, orchestrator-overridable) — disclose if any observation contradicts
that sizing.
**T5 (charged argument):** state in the completion report why the widened normalization
(stamp + dates + all ids) CANNOT mask a carrier divergence — `/Users/packer` shares no
byte pattern with either token class — so the verification lens grades the argument
rather than re-derives it.

## Acceptance criteria

1. Both receipt tests deterministic across UTC second/midnight boundaries (soak
   evidence). 2. Whole-store receipt shape preserved (sorted list + contents map, both
   arms compared). 3. No production file touched; parity pin and fences untouched by
   construction. 4. Declines disclosed (silence is not a decline). 5. One commit;
   branch LOCAL; no push/PR/CI/merge/publication/release.

Downstream, stated for the record: your approve here + the orchestrator's named-error
disposition of `030012` → uniquely keyed replacement dispatch parented to YOUR approve
(base re-pinned, SCOPE_DIFF repeated) → the work → lead+tests verification at the new
head → Step-3.8 completion / publication-token path / human lenses. The release hold is
ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this PLAN + the sibling routing SITREP + their two INDEX rows ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-035420 before these relays + INDEX writes; the two relays and two INDEX rows are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-FOLD3-RECEIPT-DETERMINISM-20260810-035420.md` → TO `s4-matrix.implementer`
- fold-3 scope unchanged from `030012` (no product objection was raised to it) → PLAN-REVIEW verdict wanted on THIS relay
- replacement dispatch → waits on your approve + the orchestrator disposition; will parent to your approve, re-pin `4c35f0f`, repeat SCOPE_DIFF
