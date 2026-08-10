## PLAN — R-4.8 fold-3 (receipt determinism) rev1 on a fresh unique key: R1-R3 folded (design-review parent edge repaired per the disposition's Edge 1; TF-2 restricted to the MINTED id-map members; blanking-proof and soak given their honest separate reaches); rev0 stands dead-in-history unrewritten; PLAN-REVIEW requested

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-fold3-plan-r1
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-design-rev6-review
IN_REPLY_TO: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-fold2-check-4c35f0f.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md (R1-R3, folded below); .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-FOLD3-NAMED-ERROR-DISPOSITION-030012-DEAD-OPTION1-ENDORSED-20260810-042015.md (030012 DEAD, Option 1 endorsed, both edges required)
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — plan-only relay; it grants nothing; the replacement `DISPATCH IMPL` parents to your approving PLAN-REVIEW on THIS relay (Edge 2) and issues only with the disposition (already landed, `042015`) and that approve both on record; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: PLAN rev1 — fold-3 receipt determinism (TF-1/TF-2-minted/TF-3), two test files, one commit; verdict wanted: approve | must-revise

Lineage, both edges per the disposition: THIS design-doc PLAN parents to the approving
rev6 DESIGN-REVIEW (`231944`, the design gate for the locked doc — Edge 1); the fold-2
check record (`c1e7eb8d…`, IN_REPLY_TO above) is the technical TRIGGER, in the body as
evidence, not the gate edge. Rev0 (`035420`, exact hash `5f70ae23…` per your review) is
DEAD in history, unrewritten, superseded by this fresh key. The spent `030012` token is
DEAD per the disposition; its five reds are named and retired by replacement.

BASE (re-pinned at replacement-dispatch time): `4c35f0fec8f845500ef7220e0df323d4924c8265`.

## Steps (ONE commit, two test files — unchanged scope; R2/R3 folded)

**T1 (GATES — TF-1) `tests/test_adapter_codex_install.cpp`:** normalize the minted
rollout stamp (`%Y-%m-%dT%H-%M-%S`) AND the `sessions/<Y>/<M>/<D>/` date components
alongside the installed id, BEFORE the relative path enters `receipt.files` and the
`receipt.contents` key. The store layout is fixed-width and this file already parses it
by offset (~:664) — reuse that idiom rather than a regex. The remainder of the relative
path stays compared byte-for-byte.

**T2 (TF-2 per R2, both files):** normalize exactly the MINTED id-map members — for
every `IdMapEntry`, `installed_session_id` and every `children.second`. Do NOT
normalize `image_session_id` or `children.first`: those are stable image/source
identifiers, and blanking them would build an avoidable normalizer able to erase
stable-input differences. This keeps the receipt broad enough for future child-bearing
fixtures without widening past the per-install token class.

**T3 (TF-3, both files):** `REQUIRE_FALSE(receipt.files.empty());` before each receipt
returns. Optional while those lines move: a per-file
`constexpr std::string_view kIdPlaceholder{"<installed-id>"}` used for both the
replacement and the advance (retires the magic `14U`).

**T4 (evidence per R3 — two SEPARATE proofs with their honest reaches):**
1. **Boundary-token proof (this is what covers the second/midnight class):** direct
   receipt-output evidence that the fixed-width `sessions/YYYY/MM/DD/` components and
   the 19-character rollout stamp are replaced before list/map insertion, while the
   rest of the relative path remains compared. This proof, not the soak, carries the
   UTC-second and midnight token class — a run cannot be scheduled onto a midnight
   crossing.
2. **Repeat-run evidence:** an exact-command macOS soak of BOTH receipt cases, ≥50
   iterations, command and count disclosed. Attributed as repeat-run stability only.
Plus the focused carrier commands and the full macOS product row. The Docker leg is NOT
re-run for a two-test-file delta (my sizing, orchestrator-overridable) — disclose if
any observation contradicts it. TF-3 is RED-constructible at your discretion; disclose
the choice. TDD posture for TF-1 stated honestly as before: no clock-controlled
deterministic RED exists; the two proofs above replace it.

**T5 (charged argument, sharpened by your own review):** state in the completion report
that normalization is restricted to the fixed date/stamp token classes and the MINTED
ids — `/Users/packer` cannot equal or contain those token classes, so a carrier-derived
divergence remains visible. The verification lens grades the argument as stated.

## Acceptance criteria

1. Both receipt tests deterministic across UTC second/midnight boundaries (T4.1 proof +
   T4.2 soak, separately attributed). 2. Whole-store receipt shape preserved (sorted
   list + contents map, both arms compared). 3. Stable ids (`image_session_id`,
   `children.first`) NEVER normalized. 4. No production file touched; parity pin and
   fences untouched by construction. 5. Declines disclosed (silence is not a decline).
6. One commit; branch LOCAL; no push/PR/CI/merge/publication/release.

Downstream: your approve on THIS relay → the replacement dispatch (fresh unique key,
parented to your approve per Edge 2, base re-pinned, SCOPE_DIFF repeated for the two
test paths) → the work → lead+tests verification at the new head → Step-3.8 completion /
publication-token path / human lenses. The release hold is ABSOLUTE.

Lint note, disclosed: the known inherited lock-path reds and the INDEX line-222
`142630` ordering inversion remain on record under their existing dispositions; the
INDEX is append-only and this seat performs no rewrite absent explicit direction.

ACTIONS_GIT_REF: docs lane only — this PLAN rev1 + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-043239 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-R48-FOLD3-RECEIPT-DETERMINISM-R1-20260810-043239.md` → TO `s4-matrix.implementer`
- Edge 1 repaired: this PLAN parents to `s4-matrix-arm1-r48-design-rev6-review` (approve `231944`); check record stays trigger/IN_REPLY_TO
- R2 folded: minted-members-only normalization (installed_session_id + children.second; stable ids untouched); R3 folded: blanking proof carries the boundary class, soak is repeat-run only
- replacement dispatch → parents to YOUR approve (Edge 2), re-pins `4c35f0f`, repeats SCOPE_DIFF; disposition `042015` already landed
