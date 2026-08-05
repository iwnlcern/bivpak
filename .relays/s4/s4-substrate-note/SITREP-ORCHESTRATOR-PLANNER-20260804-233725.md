## SITREP — two operator rulings land: sprint docs ride a docs-only lane on `main`; `.relays/` is GIT-TRACKED (supersedes the gitignore line in the prior substrate note)

ROLE: Orchestrator Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-substrate-note
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — both rulings are RECEIVED here, not requested; no work authority, no token; the release hold is ABSOLUTE
FROM: s4.orchestrator-planner
TO: s4.orchestrator-reviewer, s4-matrix.planner, s4-matrix.implementer, s4-floor.planner, s4-floor.implementer
CC: operator
SUBJECT: SITREP — docs lane + relay tracking rulings; one line of the prior substrate note superseded

The operator ruled on both open substrate questions (typed message, 2026-08-04). What
changes against the prior substrate note (`…-231722`), which otherwise stands:

1. **Docs lane on `main` (master's recommended arm 1):** commits path-scoped to
   `docs/sprints/**` + `.relays/**` land on `main` directly, OUTSIDE the product merge
   bar. The fence is absolute: a docs-lane commit that touches ANYTHING else —
   `src/`, `tests/`, `.github/`, build config, anything — is bar-governed by definition.
   Sprint docs and relay files are the lane's whole universe.
2. **`.relays/` is GIT-TRACKED, not gitignored** (the operator chose tracking over the
   transport-pack recommendation): the relay record rides bivpak history and survives
   host moves in every clone. The `.gitignore` line the prior note mentioned is REMOVED
   (`.gitignore` is back to pristine `build/`). Where `…-231722` said "gitignored on
   purpose", THIS note supersedes that line; everything else there stands.
3. Practical consequence for every seat: your relay filings and INDEX appends in
   `.relays/s4/` are now COMMITS on the docs lane. Commit with explicit paths only
   (never a directory-level `git add`), keep each commit inside the lane fence, and
   commit relay files promptly after author-side lint so the history stays honest to
   filing order.

No other change. Audit dispatches, charter, bridge discipline, and your boot relays are
untouched.

ACTIONS_GIT_REF: this repo — .gitignore restored to pristine (line removed), ROADMAP.md + local INDEX header wording updated, this note filed; the sprint tree + .relays/s4/ enter history on the docs lane in the commit this note rides in (SHA in the commit record)
FINAL_GIT_STATUS_SHORT:
?? .relays/
?? docs/
Path-scoped at write time, pre-commit; .gitignore no longer modified (restored to pristine).
