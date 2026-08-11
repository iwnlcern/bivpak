## SITREP — final check at d11c49c is NOT panel-clean: P-1 approved, but security found a NEWLY-identified config-exec class member (filter.*.clean, E2-proven) the fixed-key strategy structurally cannot cover; the class disposition is ROUTED UP — third fixed-key fold would be provably futile

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/PLAN-ORCHESTRATOR-PLANNER-SECOND-FOLD-ENDORSED-FINAL-CHECK-STATES-CUMULATIVE-WINDOW-20260807-205729.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a security-boundary-vs-trust-posture question the pair cannot settle; it decides whether the fix is a structural fold or a posture ruling (parallel to the allowlist); merge conditions 3/4 stay master/operator; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — final check NOT clean; the config-exec class needs a disposition (structural fold vs trust ruling) before any third fold; record built in the cumulative-window shape you specified

Final-check record (durable, built in your cumulative-window shape — window 66250856→d11c49c,
c52bcca record incorporated by reference, the clause-3 no-design/no-blast-radius line stated):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-final-check-d11c49c.md`.

The bounded check ran as endorsed: lead byte-verification + the two owning lenses (security S-1,
performance P-1) over the ~3-file delta; both pair seats excluded; 2/0/2 spawn reconciliation.

Verdicts (bare):
performance approve
security must-fix

- **P-1 CLOSED (performance approve):** the O(N^2) per-drain reserve is deleted, amortized O(N)
  restored, caps/raw-bytes/output_incomplete bit-for-bit unchanged, no new issue.
- **S-1 as dispatched CLOSED and non-vacuous:** fsmonitor/alternateRefsCommand proven neutralized,
  RED-without-fix demonstrated at the bytes.
- **BUT the class is NOT closed.** Checking the class for completeness, security found a
  NEWLY-identified member the first two panels never enumerated: a hostile repo-local
  `filter.<name>.clean` driver (+ in-tree `.gitattributes`) EXECUTES during `git status
  --porcelain=v2` in classify — the identical sink and threat model already accepted for
  `core.hooksPath` — and the FIXED-KEY GIT_CONFIG injection STRUCTURALLY CANNOT cover it because
  filter names are arbitrary. E2-reproduced under the exact d11c49c env. Tightly scoped by the
  lens: smudge-on-restore and diff/merge drivers are NOT reachable; the one live vector is
  clean-filter via status.

This is the THIRD round on the hostile-repo-local-config code-execution class (M1: 3 keys; S-1:
2 keys; now unbounded filter names). The Implementer folded S-1 exactly right — this is the class
being DEEPER than any prior enumeration, not a fold defect. And the lens's own finding proves a
third fixed-key fold is FUTILE. So the fix is one of two shapes, and the choice is above the pair:

1. **Structural fold (keep the neutralization posture):** enumerate the DEFINED filter/diff
   drivers from the repo config at classify time (`git config --get-regexp
   '^filter\\..*\\.(clean|smudge|process)$'` — names are unpredictable but the DEFINED set is
   readable), inject empty overrides for exactly those, OR fail-closed (typed refusal) when a
   repo-local filter is assigned to tracked content. Consistent with the M1/S-1 folds you already
   endorsed; a real but bounded fold with one design choice (neutralize-found vs fail-closed).
2. **Trust-posture ruling (no fold):** rule that pack-side plumbing over a repo the user CHOSE to
   pack is git-status-grade trust — the same code that already runs in their normal
   `git status`/shell-prompt on that repo — parallel to addendum-D's git-clone-grade open ruling.
   Under it the whole class is ANSWERED-BY-TRUST-POSTURE and M1/S-1 were belt-and-suspenders.

Lead recommendation (NOT a re-grade — the lens's must-fix stands): option 2 is in TENSION with
your own endorsement — you ruled neutralizing command-exec config keys in-scope, so consistency
points to option 1 (finish the class with the structural fix). But option 2 is a legitimate
posture the operator/m-1 could rule exactly as the allowlist was ruled ANSWERED-BY-SEALED-RECORD.
The fix PATH depends on the ruling, so I route it before dispatching — I will NOT fire a provably-
futile third fixed-key fold, and I will NOT unilaterally declare a trust posture that would
retroactively demote your endorsed folds.

Candidate d11c49c is NOT panel-clean — condition 1 unmet by exactly this one residual. Everything
else in the cumulative window is verified (14 M-fixes by reference; P-1; S-1's two keys). On your
disposition I either (1) dispatch the bounded structural fold + a fourth targeted check, or
(2) record the class ANSWERED-BY-TRUST-POSTURE and the candidate is clean at d11c49c with the
finding dispositioned. Carried unchanged: the Wave-C exit-mapping flag; the zero-ref capture_mode
cell (still awaiting m-1). Stack open; B/C/D F-fenced.

ACTIONS_GIT_REF: docs lane only — the final-check record + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit; the stack is untouched.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260807-213446 before this relay + INDEX write; the record, this relay, and the INDEX row are the working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/SITREP-PLANNER-FINAL-CHECK-NOT-CLEAN-CONFIG-CLASS-ROUTED-20260807-213446.md` → TO `s4.orchestrator-planner`
