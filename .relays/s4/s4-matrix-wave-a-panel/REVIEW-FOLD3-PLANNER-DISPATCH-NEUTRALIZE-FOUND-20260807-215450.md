## SITREP — third fold directed: finish the config-exec class STRUCTURALLY (neutralize-found), per the orchestrator disposition; one bounded fold, then a fourth targeted check

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/PLAN-ORCHESTRATOR-PLANNER-CONFIG-EXEC-STRUCTURAL-FOLD-DIRECTED-NEUTRALIZE-FOUND-20260807-215010.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the orchestrator DIRECTED option 1 under standing M1/S-1 endorsement (no new authority, no sealed tension); you write FOLD_SCOPE before any edit; merge stays the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD #3 — the neutralize-found structural fix for the filter.*.clean residual; exactly one item; deviation-back if unbuildable

The final check confirmed P-1 closed and S-1's two keys closed, but security proved (E2) a
newly-identified member of the same command-exec class: a hostile repo-local
`filter.<name>.clean` executes during `git status --porcelain=v2` in classify. The
orchestrator DIRECTED the structural fix (disposition `…-215010`): option 1,
NEUTRALIZE-FOUND, under the standing M1/S-1 endorsement — no new authority, no sealed
tension, and explicitly NOT a third fixed-key fold (that is provably futile against
arbitrary names). Do not wait on the operator's parallel trust-posture lever; THIS fold
completes the class.

FOLD (exactly one item, the directed shape):
- **Enumerate the DEFINED drivers, inject empty overrides — do NOT fail-closed.** At
  classify time (before the status/ls-files calls run over the untrusted repo), read the
  repo's defined command-executing driver keys via
  `git config --local --get-regexp '^filter\..*\.(clean|smudge|process)$'` (a config READ —
  it triggers no driver, so it is safe to run un-neutralized), plus the diff/merge driver
  families for defense-in-depth (`diff.*.command`, `diff.*.textconv`, `merge.*.driver`),
  and inject an EMPTY override (`GIT_CONFIG_KEY_n=<found key>`, `GIT_CONFIG_VALUE_n=`) for
  exactly each found key into the pack-side GIT_CONFIG set used by the subsequent
  status/ls-files/capture invocations.
  - **Repo-LOCAL scope, deliberately:** enumerate `--local` only. The threat is
    attacker-controlled repo-local config (a cloned hostile repo's `.git/config`); the
    user's GLOBAL filters (e.g. their own git-lfs) are trusted and must not be disturbed.
    And it is SAFE to neutralize even a legitimate repo-local filter during classify
    because classify is READ-ONLY — payload is captured as worktree bytes, so the clean
    filter's effect on packed CONTENT never runs; neutralizing it during `git status`
    changes nothing but the exec vector (the orchestrator's dispositive point).
  - **Why not fail-closed** (do not implement fail-closed): a typed refusal on any
    repo-local filter over tracked content would REFUSE legitimate filter repos (git-lfs,
    `ident`, keyword expansion), narrowing the sealed "pack any directory" promise.
    Neutralize-found closes the exec sink WITHOUT narrowing the promise — that is the whole
    reason it stays inside the orchestrator's existing authority.
  - The base static keys (hooksPath/credential.helper/sshCommand/fsmonitor/
    alternateRefsCommand) STAY; this adds the per-repo dynamic set on top. Expect the
    wrapper's injected config to become `static base + per-repo enumerated overrides`;
    compose the dynamic set where classify issues the status call (a git_exec helper taking
    extra overrides is the natural seam).
- **Verify the empty override actually suppresses the driver.** The whole fix rests on an
  empty `filter.<name>.clean` value defanging the program form (as empty did for fsmonitor).
  If git treats an empty driver value as an error or still executes — i.e. neutralize-found
  is UNBUILDABLE — that is a DEVIATION back to the orchestrator with the impossibility
  SHOWN, NOT a silent switch to fail-closed (the disposition is explicit on this).
- **Test (RED/GREEN, the proven vector):** a hostile repo with a repo-local
  `filter.evil.clean` writing a marker + in-tree `.gitattributes: * filter=evil`; run the
  same `git status --porcelain=v2 -z` classify issues under the fold env; assert the marker
  is ABSENT (GREEN) and prove it is CREATED without the fix (RED). Scope the test to
  clean-via-status (the one live vector); the record already states smudge-on-restore and
  diff/merge as confirmed NOT reachable, so those need no execution test — the defense
  enumeration covers them, the test covers the proven sink.

DO NOT expand beyond this item. The c52bcca-panel optionals/nits remain discretion. A row
outside the classify/git-wrapper config surface is a deviation to the orchestrator BEFORE
the edit. NOT folded, carried unchanged: the Wave-C exit-mapping flag; the zero-ref
`capture_mode` cell (still awaiting m-1).

Branch mechanics: lands on the T2 git-wrapper/classify branch; restack T3->T4; produces a
fourth replacement head. File your `PHASE: REVIEW-FOLD` report with FOLD_SCOPE,
`FOLD_SCOPE_RESULT: all-in`, and the new head; I run a FOURTH targeted check — lead
byte-verify + the security owning lens over the delta — and its record states the
cumulative window from `66250856` and incorporates the c52bcca + d11c49c records by
reference (the chain-audit discipline). On green, condition 1 is met at the final head.

ACTIONS_GIT_REF: none — no product/test edit by this seat; this routing relay + its INDEX row are the only writes, docs-lane.
FINAL_GIT_STATUS_SHORT: none — clean tree; fresh at 20260807-215450, this relay + INDEX row the only delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD3-PLANNER-DISPATCH-NEUTRALIZE-FOUND-20260807-215450.md` → TO `s4-matrix.implementer`
