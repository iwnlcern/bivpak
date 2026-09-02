## SITREP — 2a plan revision 5 FILED ON RECEIPT of the C-4 correction (`intg-substep2a/PLAN-pair-planner-20260902-035914.md`, artifact @ 90187646; identities UNCHANGED — W-5's frozen selector holds), the `025301` MUST-REVISE folded whole under `034802`/`035143` (C-4 carried VERBATIM as the evidence term; F1's semantic ONE inventory with the determined typed-expressible rule and the census RECONCILED — the owner's 57 reproduces at 9e6ebe8 and this seat's 60 at the tranche-1 tree by the same fixed-range command, the delta being the tree (tranche 1 adds six / removes one ParseError line), the anchored command of record giving 60 rows to classify; the O-R2 helpers KEPT with acceptance and detail strings byte-unchanged; C-2 in the codebase's braced idiom with +5/-2 stated once; empty-status postcondition); the W-5 replacement re-measurement on the filed revision fires EXACTLY ONE entry on the citing carrier (the O design-lineage red, verbatim below; per-file OK) — archive `results/lint-root-sweep-2a-rev5-c4-corrected-20260902.txt` @ e2606cc3; the isolation carrier (033604) stays silent in the same sweep; the implementer's exact-hash approve at 90187646 is the next gate; the token still behind that + the operator-granted W-5's Master Reviewer concurrence + the effectiveness notice; tranche 1 stands unstaged at 9e6ebe8

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-audit
PARENT_DISPATCH_ID: intg-substep2a-format-act
IN_REPLY_TO: ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035143.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev5-c4-corrected-20260902.txt; intg-substep2a/PLAN-pair-planner-20260902-035914.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-025301.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the standing ones: the operator-granted W-5's Master Reviewer concurrence and the effectiveness notice (master's), then the tranche-2 token after the implementer's exact-hash approve; no product byte, no ref move, no merge/push/publication/release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 90187646c43406b8c8ecdd9b964e0651da7d50a7dfbf24de643854282017951c
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: SITREP — rev5 filed (035914; artifact 90187646; identities frozen as W-5 selects): C-4 verbatim, F1 semantic inventory + reconciled reproducible census (57 @ 9e6ebe8 / 60 @ the tranche-1 tree, same command — the tree explains the delta), helpers kept, C-2 braced idiom +5/-2 stated once, empty status; the W-5 replacement re-measurement = ONE fired entry on the citing carrier (the O design-lineage red, verbatim; per-file OK) archived @ e2606cc3; token waits on the exact-hash approve at 90187646 + concurrence + notice

## The W-5 replacement re-measurement, VERBATIM (the instrument of record)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev5-c4-corrected-20260902.txt
          sha256 e2606cc35e966c77b547bac10c7b40df14bd74f9c2d53f2af7695947a04307c1 ; 255 lines ; rc 1
          (232 ERROR / 23 WARN root-wide — the standing historical population; design-lineage class 40
          = 38 prior + the rev5 carrier + its draft echo; design-edge class 0 — the isolation carrier
          033604 remains silent in this same sweep)

FIRED SET ON THE CITING CARRIER (exactly one line):
ERROR .relays/intg: intg-substep2a/PLAN-pair-planner-20260902-035914.md: DESIGN_LOCK_ID 'm1-addendum-O-63c46631-lock-20260901' has no earlier same-owner DESIGN relay carrying matching DESIGN_DOC_ID

per-file contrast (NOT closure): relay-lint.py --no-freshness intg-substep2a/PLAN-pair-planner-20260902-035914.md → OK, rc 0
```

The fired identity is unchanged (O); N and M rev8 ride `SECOND/THIRD_CONSUMED_LOCK` exactly as W-5's row states; both frozen identities preserved at 035914 — the entry replaces to rev5 under the replacement rule.

## The census reconciliation (the owner's ask (i)), reproduced both ways at this seat

```text
owner's command   sed -n '1077,1700p' src/core/manifest/manifest.cpp | grep -c ParseError
   @ 9e6ebe8 blob (git show 9e6ebe8:…)                                     57   (the owner's number)
   @ the tranche-1 tree (9e6ebe8 + the unstaged 72fd3dc6 diff)             60   (this seat's number)
anchored command  awk '/^expected<std::optional<std::filesystem::path>>$/{f=1}
                       /^expected<std::vector<RepoEntry>>$/{f=0} f && /ErrKind::ParseError/{c++}
                       END{print c+0}' src/core/manifest/manifest.cpp
   @ 9e6ebe8 blob                                                          55
   @ the tranche-1 tree                                                    60   ← the census of record
delta = the TREE: tranche 1's manifest.cpp diff adds six and removes one ErrKind::ParseError line
  (git diff -- src/core/manifest/manifest.cpp | grep -c '^+.*ErrKind::ParseError' → 6; '^-' → 1)
```

## Standing state (both lanes)

- 2a: awaiting the implementer's exact-hash review at `90187646…`; then the token behind the operator-granted W-5's concurrence + the effectiveness notice. Tranche 1 unstaged at `9e6ebe8` (`72fd3dc6…`).
- Isolation: plan `033604` @ `46e47a0a` awaiting the implementer's exact-hash review; the cross-repo edge structurally green (`033843`).
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev5 artifact, the archived re-measurement, the filed 035914, and this SITREP via the engine; commit path-scoped follows; no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION5-C4-CORRECTED.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-REV5-FILED-REMEASURED.md
 ?? .relays/intg/intg-substep2a/PLAN-pair-planner-20260902-035914.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-2a-rev5-c4-corrected-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
