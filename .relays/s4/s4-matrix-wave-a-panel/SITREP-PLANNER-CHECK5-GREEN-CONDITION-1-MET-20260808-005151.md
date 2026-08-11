## SITREP — check #5 GREEN at cb1f6254: the neutralize-found command-exec class is CLOSED across {direct, include, worktree} with the ordinary-repo negative control green; condition 1 (panel) MET at the final head; stack routes UP for condition 3

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/PLAN-ORCHESTRATOR-PLANNER-CHECK4-COMPLETION-AFFIRMED-CHECK5-NEGATIVE-CONTROL-REQUIRED-20260807-230516.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — reporting a green bounded check and routing the panel-clean stack up for condition 3; merge conditions 3/4 stay master/operator; the trust-posture lever stays the operator's, non-blocking; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — check #5 GREEN; condition 1 met at cb1f6254; both bypasses RED, negative control GREEN; one low non-blocking note carried as Implementer-discretion

The fifth targeted check ran exactly as dispatched and endorsed: LEAD byte-verification + the
SECURITY owning lens over the a3c5454..cb1f6254 delta, grading BOTH directions per your added
criterion. Durable record, built in your cumulative-window shape (window 66250856->cb1f6254;
c52bcca + d11c49c + a3c5454 records incorporated BY REFERENCE; the clause-3 no-design/no-blast-
radius line stated on its face):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-08-s4-matrix-wave-a-check5-cb1f6254.md`.

CANDIDATE_SHA: cb1f6254e1a275fd5e56ba91547d762145b32fa7 (PR #20 head, open into s4-matrix/arm1-t3;
clean fast-forward over the fourth head 5be90ed6, fold-3 commit a3c5454 preserved as ancestor).

Verdict (bare):
security approve

- **(A) COVERAGE — PASS.** The completed enumeration reads the union of `git config --local
  --includes ... --get-regexp <pattern>` and `git config --worktree --includes ...`, driver-family
  pattern unchanged, results unioned/sorted/deduped. The lens's escape attempt found NO still-open
  repo-local exec path: the {local, worktree} scopes plus their include chains are the entire surface
  git honors during classify (system off via `GIT_CONFIG_NOSYSTEM=1`, global trusted); precedence is
  irrelevant because every matched key is emptied regardless of value (key-set union is the correct
  superset). Both hostile TEST_CASEs (include-delivered and worktree-delivered `filter.evil.clean`)
  genuinely trap — RED without the fix.
- **(B) NEGATIVE CONTROL — PASS (your added criterion).** The `--worktree` exit-128 fatal is caught
  ONLY when both C-locale stderr anchors are present (`LC_ALL=C` pinned, git.cpp:77), mapped to
  empty-set for that scope; every other nonzero — and all `--local` failures — still propagate as a
  typed failure. Not too broad, not too narrow (single-worktree/extension-off treats `--worktree` as
  `--local` and does not error; git also ignores `config.worktree` there, so nothing executable is
  left unneutralized). The added TEST_CASE "classification treats disabled worktree config as empty in
  linked worktrees" creates a REAL linked worktree with worktreeConfig disabled, drives `git config
  --worktree` to exit 128, and asserts classify stays GREEN exit 0 with an EMPTY neutralization set —
  RED without the special-case. Ordinary repos are not broken.

**Disposition: candidate cb1f6254 IS panel-clean; condition 1 (adversarial panel) MET at the final
head.** The full cumulative window 66250856..cb1f6254 is verified — 14 M-fixes + P-1 + S-1's two keys
(by reference) + the neutralize-found command-exec class closed across all three repo-local delivery
paths {direct, include, worktree} with the ordinary-repo negative control green. Both Step-3 fences
live at cb1f6254 (scan.cpp:138 RepoDiscoveredUnsupported; manifest.cpp:597 require_empty_array repos).
The a3c5454..cb1f6254 product delta is two files (git_exec.cpp enumeration + test_repo_engine.cpp);
NEITHER design NOR blast radius changed.

**One LOW-severity, non-blocking note — carried as Implementer-discretion, NOT a fold requirement and
NOT reopening condition 1:** an attacker-controlled repo-local `include.path` pointing at the absolute
path of the user's global gitconfig would make `--local --includes` enumerate the user's trusted
global filter keys (e.g. `filter.lfs.clean`) and add them to the empty-override/neutralized-keys set.
It is exec-SAFE and read-only — an empty override only, never execution; the on-disk global config is
untouched. The wrinkle is a slight widening of the neutralization/report set beyond attacker-defined
keys (could suppress the user's git-lfs clean during that one hostile-repo pack and surface a
surprising `filter.lfs.clean` in the neutralized-keys report). It does not touch the exec boundary. I
carry it to the Implementer as discretion; if you or the operator want it addressed it becomes a
directed item, but nothing waits on it.

**Routing UP for condition 3:** with condition 1 met at cb1f6254, the Arm-1 Wave-A stack (PR #20 head)
is panel-clean and ready for your MERGE/LIVE-VERIFY gate — conditions 3 (master verification) and 4
(one staging mechanism / operator merge) are master/operator-owned, unchanged. The release hold is
ABSOLUTE regardless. Carried unchanged: the Wave-C exit-mapping flag; the zero-ref `capture_mode`
cell (still awaiting m-1); B/C/D remain F-fenced. The trust-posture lever you routed to master as the
R-4.6 refinement stays the operator's and is now strictly belt-and-suspenders (the class closes
either way).

ACTIONS_GIT_REF: docs lane only — the check-#5 record + this relay + its INDEX row, committed on main with explicit paths (SHA in the commit record); no product edit; the stack is untouched.
FINAL_GIT_STATUS_SHORT:
none — clean tree
Fresh at 20260808-005151 before this relay + INDEX write; the check-#5 record, this relay, and the INDEX row are the working-tree delta at commit time and are named above.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/SITREP-PLANNER-CHECK5-GREEN-CONDITION-1-MET-20260808-005151.md` → TO `s4.orchestrator-planner`
