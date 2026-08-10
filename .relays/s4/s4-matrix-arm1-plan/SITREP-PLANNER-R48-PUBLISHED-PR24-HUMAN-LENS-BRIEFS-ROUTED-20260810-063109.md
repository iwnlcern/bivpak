## SITREP — R-4.8 PUBLISHED under the operator's P5 token: branch `s4-matrix/r48-carrier` pushed at the EXACT re-verified head `2341667` (remote ref and PR head OID both confirmed byte-exact) and DRAFT PR #24 opened per the substrate's production-risk shape; the two human-lens briefs at `2341667` are ROUTED via the operator in this same relay (publish-first order); publication ≠ merge ≠ release — every downstream gate stands

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-published
PARENT_DISPATCH_ID: s4-matrix-r48-p5-publication
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-P5-PUBLICATION-GRANTED-CARRIED-DOWN-20260810-061323.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the two human-lens reviews are the operator's to route to their readers (briefs below); the merge hand-up (condition-3 end-state-bytes + condition-4) and the ABSOLUTE release hold stand entirely ahead; nothing here grants merge or release
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — published ref + PR number routed UP; the two human-lens briefs routed via the operator; execution disclosures

## Execution report (the token's conditions, in order)

1. **Tip re-verified AT execution:** `git rev-parse s4-matrix/r48-carrier` =
   `234166722ef44f51db5740c2ac4e01301b5dc0c1` immediately before the push, checked
   atomically in the same command chain as the push itself (a moved tip would have
   short-circuited to STOP-and-route). Unmoved since your carry.
2. **Pushed the exact head:** `git ls-remote` confirms
   `refs/heads/s4-matrix/r48-carrier` = `234166722ef44f51db5740c2ac4e01301b5dc0c1`.
3. **DRAFT PR #24 opened:** https://github.com/iwnlcern/bivpak/pull/24 —
   `feat(manifest): pack-time packer-home carrier (R-4.8)`, base `main`, head OID
   verified byte-exact via the API after creation. Shape choice disclosed: the
   production-risk precedent (slices A/C/B2, PRs #21-#23) is DRAFT; the earlier OPEN
   matrix PRs (#19/#20) were lower-ceremony waves — DRAFT is also the shape that cannot
   be over-read as merge-ready. Body follows #23's section shape (Stack / Scope / Local
   verification / boundary / Review carry) with the six-commit lineage, the four sealed
   record hashes, both evidence legs with their disclosed ruled classes, and the merge
   boundary stated inside the PR itself.
4. **Remote Actions:** not invoked manually and not chased per the token; the red X is
   the known cosmetic under CI-leg (a); local Docker remains the governing Linux signal.
5. One reference note: the carry-down cites a `055615` plan of mine for the
   publish-first lens order; no relay with that stamp exists in my lane at my seat (my
   cycle-close was `055009`). Nothing turned on it — the carry-down restates the order
   inline and I executed that text; flagged only so the record does not point at a
   ghost.

## The two human-lens briefs at `2341667` (routed via the operator, publish-first)

**Shared packet (both lenses):** candidate = DRAFT PR #24, exact head `2341667`, BASE
`6047ab03` (pre-C/B2 main), delta = 10 paths (5 src, 5 tests), six commits. The full
machine-review trail is sealed in `docs/sprints/2026-08-04-s4-step4/reviews/`: panel
`006144b2…@29796bb` → re-check `e6a589a5…@2bc7a078` → check `c1e7eb8d…@4c35f0f` →
verification `4f90641f…@2341667` — each contains the verbatim lens reports, the lead
verifications, and the finding-by-finding dispositions. Design at rev6
(`e653457e…@2c7b887`); floor consumer contract ratified `050728`, narrowings ruled
compatible (`204159`, `224450`). Known-and-ruled evidence classes (NOT open findings):
the stale `harness-e2` 180s ceiling; the Docker-Desktop 5+3 emulation class
(BASE-control-measured); one non-reproducing probe timeout tracked in the harness
lineage.

**Brief A — product/security read:** the carrier's whole claim is transport-only
opacity with fail-closed validation. The load-bearing cells a human read adds most to:
(1) the sealed wire contract (§3/§5-§8 of the design) against `manifest.cpp`'s
serialize/parse at the head — especially that present ⇒ non-empty absolute in its
verified flavor with a non-degenerate root, and absence is the ONLY degrade path;
(2) the single grammar/root authority `classify_carrier_root` (no second discriminator
anywhere — the machine panels proved it; a human eye on whether the fail-closed default
and the `>7` extended bound match intent is the residual value); (3) the leak surface:
`git grep packer_home` at the head should show schema/serialize/parse/one-capture/
one-transport-copy and NOTHING that reads it into output — confirm no path renders or
derives from the value.

**Brief B — tests/receipts read:** the review cycle's recurring lesson was
falsifier honesty. Highest-value human checks: (1) the carrier-engaged exact-bytes
golden and the degenerate/boundary matrices in `tests/test_manifest.cpp` (11b/13b —
do the rows pin what the design claims, including the 8-byte accept controls);
(2) the two whole-store byte-identity receipts (engaged vs absent arms) — the
normalization is deliberately narrow (fixed date/stamp offsets + minted ids only);
judge whether anything it blanks could hide a carrier divergence (the machine argument:
lexically impossible — grade it); (3) the pack capture matrix's hermeticity (seven HOME
shapes, store guards engaged, per-row `agent_sessions.empty()`).

Lens verdicts ride the merge hand-up per the operator's order; nothing gates the draft
PR on them.

## Boundaries (restated, none moved)

Publication ≠ merge ≠ release. The four-condition merge bar stands entirely ahead —
condition-3 will re-verify per-file END-STATE bytes at the eventual merge base (this
branch predates C/B2; the sealed panels carry only where end-state bytes match
`2341667`). The local-`main` publication-timing question remains the operator's
separate open item. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: branch publication under the operator's P5 token — push of `s4-matrix/r48-carrier` at `2341667` + DRAFT PR #24 (no Actions invoked, no merge, no release); docs lane: this relay + its INDEX row ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no edit at this seat.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-063109 before this relay + INDEX write; this relay and the INDEX row are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-PUBLISHED-PR24-HUMAN-LENS-BRIEFS-ROUTED-20260810-063109.md` → TO `s4.orchestrator-planner`
- PUBLISHED: `s4-matrix/r48-carrier` @ `234166722ef44f51db5740c2ac4e01301b5dc0c1` (remote ref + PR head OID byte-verified) → DRAFT PR #24
- human-lens briefs A/B at `2341667` → routed via the OPERATOR (publish-first); verdicts ride the merge hand-up
- `055615` reference → not found at my seat (disclosed; carry-down text executed as restated inline)
- merge bar (condition-3 end-state-bytes) + release hold ABSOLUTE → entirely ahead, untouched
