## REVIEW — Wave-A candidate panel COMPLETE at `66250856`: team-of-5, five must-fix, verdict REVIEW-FOLD required; record durable; one finding routed UP for a design ruling before it can fold

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-WAVE-A-PANEL-DISPATCHED-TEAM-OF-FIVE-AT-T4-HEAD-20260807-152510.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this relay — the panel is condition 1 of the four; the fold is the pair's under REVIEW-FOLD; condition 3 (merge-ready verify) is master's, condition 4 (merge token) the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: REVIEW — the Wave-A panel record, spawn reconciliation, and the ONE finding that cannot fold at the pair (sealed-design tension)

Panel executed exactly as dispatched. Record of record (durable):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-07-s4-matrix-wave-a-panel-66250856.md`
— team-of-5 C++ baseline, all five lenses COLD (fresh read-only subagents, no thread
context), every lens SHA-bound to `66250856` and instructed to read only via
`git show`/`git diff` at the SHA; both pair seats excluded from lenses per 5/5b; I served
non-lens LEAD (spawn/collect/synthesize, no findings of my own, no re-grading).
Record disciplines met: lens findings verbatim and separated; lens PROMPTS verbatim in the
appendix; verdict lines bare; PANEL_CHOSEN/DEFAULT_ROLES_CHANGED/WHY_THIS_PANEL/ROLES/
PANEL_COMPOSITION present.

SPAWN COUNT PER LENS SEAT (clause 6): each seat 1 spawn / 0 stalls / 1 finding-set;
5 spawns = 5 finding-sets + 0 stalls; no re-spawn, so no disclosed REVIEWER-RUN. The idle
notifications during collection were completion signals, not stalls (a stall = no
deliverable; all five produced one); each report was retrieved verbatim from its subagent
transcript.

Per-lens verdicts (bare):
correctness must-fix
security must-fix
performance must-fix
test-coverage must-fix
idiomaticity must-fix

PANEL VERDICT: REVIEW-FOLD required. Wave A is scope-clean and BOTH Step-3 fences are live
at the SHA (confirmed independently by correctness and security) — nothing is an absolute
merge blocker — but the must-fix set clusters on real seams and folds before this stack is
a bar candidate. The fold is bounded inside the Wave-A file universe, so per the
cumulative-diff rule the post-fold check is a TARGETED panel sized to the delta, recorded
as its own panel — not a full re-run.

The must-fix headline (fold at the pair; full detail + evidence in the record §"Consolidated must-fix"): git-wrapper env pinning is both too broad and too permissive — `GIT_CONFIG_GLOBAL=/dev/null` on the PACK side suppresses the user's global excludesFile and REFUSES a clean repo (correctness #1, E2-reproduced against git 2.50.1), while repo-local hooksPath/credential.helper stay in force (security #2); the `--` delimiter is bypassed at engine call sites where validation, not delimiting, is the control (security #4 / correctness #7); restore path containment is missing (security #3); no engine call sets a per-call budget so the minutes-class bundle bar is unmet (performance #2 / correctness #8); eligibility is O(refs×tips) subprocesses (performance #1); the promisor PRE-STEP policy does not propagate and is untested (correctness #3 / tests #2); the restore divergence vocabulary is unproducible with two dead fields (correctness #5); RefUncapturable/verify_bundle mis-mapped (correctness #2/#4); the comparator carries a second code-only tolerance surface (correctness #9); several tests assert their fixtures not the units (tests #1/#3/#4); helper duplication incl. the penumbra double-snapshot the oracle compares against itself (idiomaticity #1); four throwing filesystem calls (idiomaticity #3); a copyable double-removing TempDir (idiomaticity #4).

**ONE finding cannot fold at the pair — routed UP for your ruling (record §"LEAD FLAG"):**
security #1 recommends adding a git TRANSPORT-POLICY ALLOWLIST so manifest URLs are refused
rather than dispatched. But sealed addendum-D DELETED the SR-M14 URL allowlist/host-floor
deliberately ("Bivpak is a portability tool, not a git-URL firewall; networked open is
git-clone-grade trust"). Folding the allowlist half as written re-introduces a retired
mechanism. I did NOT re-grade the finding (it stays must-fix as the lens set it); I split
its fold path: the generic-hygiene half (`GIT_PROTOCOL_FROM_USER=0`, credential.helper
neutralization) is NOT URL policing and folds with the env fix; the ALLOWLIST half needs
your design ruling before it folds. This is the panel finding a live sealed-design tension —
exactly what routes across the bridge, not a pair decision.

**Design-intent questions the lenses raised (route with the above, may gate parts of the fold):**
the mutating eligibility `fetch` into the user's SOURCE repo during pack (sanctioned by
pack-engine §2 or must it use a scratch object store?); the root-repo relpath="." case,
which materializes via a SECOND staging mechanism design criterion 4 forbids (correctness #6 —
a candidate DEVIATION, not a clean fold: designed class or fence at Arm 1?); workspace-wide
vs subtree nested fencing; `capture_mode: full` for the zero-ref payload-only entry;
`reset --hard` vs `checkout` under §A2.

Proposed next step (your call): I open REVIEW-FOLD at the pair for the foldable must-fixes
(FOLD_SCOPE first, all inside the Wave-A universe), HOLDING the two items above pending your
ruling; a replacement SHA gets its own targeted panel record per the cumulative-diff rule.
The Wave-A stack (#16/#17/#19/#20) stays open; B/C/D remain F-fenced; the F signal is still
the separate next unlock and nothing about the fold waits on it.

ACTIONS_GIT_REF: docs lane only — the panel record + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit; the Wave-A stack is untouched by this filing.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260807-160037 before this relay + INDEX write; the panel record, this relay, and the INDEX row are the working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-PLANNER-PANEL-COMPLETE-20260807-160037.md` → TO `s4.orchestrator-planner`
