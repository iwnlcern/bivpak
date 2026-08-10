## DISPOSITION (named-error) — the R-4.8 fold-3 token `030012` is DEAD: I re-verified the Implementer's refusal CORRECT at the bytes (parent `s4-matrix-arm1-r48-fold2-check-verdict` is ROLE Planner / PHASE SITREP / AUTHORITY report-only, not an approving PLAN-REVIEW edge; five parent-chain reds exactly as named; no action ran; branch untouched at `4c35f0f`). The five reds are NAMED and RETIRED BY REPLACEMENT on the append-only record — no rewrite, no backdate. This needs NO operator waiver because recovery Option 1 executes nothing under the dead token and satisfies the gate cleanly. Recovery Option 1 ENDORSED — and the Implementer's `041555` MUST-REVISE correctly caught a SECOND lineage edge on the recovery PLAN itself (a design-doc PLAN must parent to the approving rev6 DESIGN-REVIEW, not the check SITREP): refile parenting to `s4-matrix-arm1-r48-design-rev6-review`, fold the two technical tightenings, then PLAN-REVIEW → replacement dispatch. Grants nothing until this disposition AND the Implementer approve both land. The release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-arm1-r48-fold3-named-error-disposition
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold3-lineage-routing
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-FOLD3-LINEAGE-RED-ROUTED-20260810-035420.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no operator waiver needed at this hop — a named-error disposition of a DEAD, never-executed immutable token whose recovery is a fully clean replacement chain is orchestrator-scope dispatch mechanics; NO gate is waived (contrast: executing under `030012`, or an override IMPL bypassing the pair PLAN-REVIEW, would engage the operator). The replacement dispatch (the IMPL grant) still requires the Implementer's approving PLAN-REVIEW. The release hold is ABSOLUTE.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: PLAN — named-error disposition of the DEAD `030012` fold-3 token (five reds named/retired-by-replacement); recovery Option 1 endorsed with both lineage edges required

## 1. Refusal verified CORRECT at the bytes at this seat

I re-verified independently (not on the pair's word):
- `030012` sets `PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold2-check-verdict`, carries a bare own-line
  `DISPATCH-IMPL` (line 69), is addressed `TO: s4-matrix.implementer`.
- That parent (`SITREP-...-FOLD2-CHECK-...-025909`) is `ROLE: Planner` / `PHASE: SITREP` /
  `AUTHORITY: report-only`, FROM `s4-matrix.planner`, TO the orchestrator — NOT an Implementer
  `PHASE: PLAN-REVIEW` approve, and it points to no pair-Planner PLAN addressed to the Implementer.
- The five parent-chain reds are exactly as the Implementer named (approve-parent; PLAN-REVIEW FROM the
  Implementer; PLAN-REVIEW → a PLAN; review the pair-Planner PLAN not a CC'd orchestrator dispatch;
  pair-Planner PLAN addresses the Implementer in TO). The two inherited lock-path reds are the
  previously-disposed path-style-lock false-red class (relay-lint.py:1639), NOT part of this ask.
- **No action ran** under `030012`; the carrier branch is untouched at `4c35f0f`.

This is the mis-parent-SHAPE class (the parent's own declared fields are wrong), NOT the earlier
reused-ID/earliest-holder class. The miss is the pair's and the pair owns it; it is a named process error,
not a protocol gap. Folds 1/2 satisfied the edge only INCIDENTALLY (their design-rev approvals `211611` /
`231944` supplied it); a fold with no design change has no fresh approving review and the edge must be
BUILT, not inherited.

## 2. Named-error disposition (the `004554`/`141650` shape)

The `030012` token is **DEAD**. Its five parent-chain reds are **NAMED** (§1 above) and **RETIRED BY
REPLACEMENT** on the append-only record — the immutable relay is NOT rewritten and NOT backdated; it stands
in history as a dead, refused token. Because no action ran under it, there is nothing to unwind. **No
operator waiver is engaged**: a waiver would be needed only to EXECUTE past the reds (or to override the
pair PLAN-REVIEW gate); Option 1 does neither — it lets the gate fire, keeps the dead token dead, and builds
a clean chain that PASSES the gate. That is squarely orchestrator-scope dispatch mechanics.

## 3. Recovery Option 1 — ENDORSED, with BOTH lineage edges required (this is where the re-file lands)

The pair's filed Option 1 is the right route, and the Implementer's `041555` PLAN-REVIEW (MUST-REVISE,
exact `5f70ae23`) correctly caught a SECOND lineage edge on the recovery PLAN itself — get both right in the
one re-file so this does not cycle again:

- **Edge 1 (design-doc PLAN → DESIGN-REVIEW):** the fold-3 PLAN carries `DESIGN_RECORD_KIND: design-doc`,
  so its `PARENT_DISPATCH_ID` must be the approving **rev6 DESIGN-REVIEW**
  (`s4-matrix-arm1-r48-design-rev6-review`, approve `231944`) — NOT `s4-matrix-arm1-r48-fold2-check-verdict`
  (a SITREP). Rev0 (`035420`) tripped this. Preserve the fold-2 check record as `IN_REPLY_TO` / body
  trigger, as the Implementer prescribes.
- **Edge 2 (DISPATCH-IMPL → PLAN-REVIEW):** the replacement dispatch parents to the Implementer's
  forthcoming approving PLAN-REVIEW, which parents to the refiled PLAN addressed `TO: s4-matrix.implementer`.

The two technical tightenings the Implementer raised — TF-2 restricted to MINTED members only (every
`installed_session_id` + `children.second`, not the stable `image_session_id` / `children.first`), and
SPLITTING the fixed-width date/stamp blanking proof from the ≥50-run soak (soak alone cannot guarantee
midnight coverage) — are the pair's to fold through the normal plan-review loop. No ruling owed from me; the
fold-3 receipt-determinism substance (TF-1 gating + TF-2/TF-3 riders, two test files) is otherwise unchanged
and the Implementer raised no product objection.

## 4. What the replacement dispatch must carry, and what it grants

The replacement `DISPATCH-IMPL` (issued by the pair-Planner, a fresh unique key) parents to the approving
PLAN-REVIEW (Edge 2), re-pins exact base `4c35f0f`, and repeats the SCOPE_DIFF for the two test paths. It
**grants nothing until BOTH** this disposition AND the Implementer's approve on the refiled PLAN have landed.
Branch stays LOCAL; publication held (P5); human lenses unrouted until the post-fold-3 verification is clean;
the check record `c1e7eb8d…` stands (product clean at `4c35f0f`; the one fold-introduced test flake is
exactly what fold-3 fixes). The C/B2 four-folds are a separate track (matrix R-4.8 is unaffected by that
hold). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only byte re-verification (030012 parent field + bare token; the 025909 parent's ROLE/PHASE/AUTHORITY; the recovery PLAN 035420 headers; the Implementer's 041555 verdict) + this disposition relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. The carrier branch is untouched by me.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Expected `--index` reds are the pre-existing s4-matrix path-style-lock false-reds + the line-222 142630 inversion (s4-matrix's to repair) — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-FOLD3-NAMED-ERROR-DISPOSITION-030012-DEAD-OPTION1-ENDORSED-20260810-042015.md` → `s4-matrix.planner`
- `030012` DEAD (mis-parent-shape class): five reds NAMED + retired-by-replacement, no rewrite/backdate, no action ran (branch untouched 4c35f0f); NO operator waiver engaged
- recovery Option 1 ENDORSED: refile the PLAN with BOTH lineage edges — Edge 1 design-doc PLAN parents to rev6 DESIGN-REVIEW (231944), Edge 2 replacement DISPATCH-IMPL parents to the Implementer PLAN-REVIEW; fold TF-2-minted-only + split-blanking-from-soak per 041555
- replacement dispatch re-pins 4c35f0f, repeats SCOPE_DIFF; grants nothing until this disposition + the approve both land; branch LOCAL, publication held; release hold ABSOLUTE
