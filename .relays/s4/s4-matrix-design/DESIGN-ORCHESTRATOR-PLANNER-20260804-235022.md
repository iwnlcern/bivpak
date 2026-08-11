## DESIGN DISPATCH — s4-matrix: local design for Arm 1 (+ arm-plan skeleton), on the reconciled audit base

ROLE: Orchestrator Planner
PHASE: DESIGN
AUTHORITY: design-only
DISPATCH_ID: s4-matrix-design
PARENT_DISPATCH_ID: s4-matrix-audit
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: not by this relay — FU-1's three-arm ruling is the OPERATOR's and comes due before Arm 2's design closes (routed separately); the release hold is ABSOLUTE
GRILL_REQUIRED: no — the design basis is sealed (pack-engine, restore-apply contract, addenda A/B/D); this is integration-shape design under it
FROM: s4.orchestrator-planner
TO: s4-matrix.planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: DESIGN — Arm 1 end-to-end under the sealed contracts, all four schema-act surfaces, harness day one

Both audits are reconciled — `docs/sprints/2026-08-04-s4-step4/RECONCILE.md` (§s4-matrix)
is now part of your design basis and its rulings BIND. Your seat designs the LOCAL
integration shape; sealed docs govern semantics and are not reopened.

### Scope of this design

1. **Arm 1 single-clean-repo end-to-end**, per package §2: two-phase discovery replacing
   fence 1; overlay eligibility gate (fail-safe: not-provably-pushed ⇒ full-capture);
   bundle capture; the schema act; restore-side clone/apply INTO the existing partial-dir
   staging; golden round-trip row 1.
2. **The schema act scopes FOUR surfaces** (reconciled ruling): fence 1, fence 2
   (`require_empty_array` → §2.3 parser), the member-namespace gate (`open.cpp:275-279`
   admits a `repos/` family), and the envelope repos summaries + frozen-oracle recapture
   (a DECISION recorded in the ledger, never a regeneration).
3. **Golden harness from day one:** extend `tolerance-v1.json` + `compare.py`
   (repo-boundary walk, §5 acceptable-difference classes) + `fixtures.py` (git repo
   builder under a controlled git env) + scenario ops; promote `d-git-restore`. One
   tolerance surface — never a second harness.
4. **Named design decisions your doc must carry:**
   - the git subprocess runner: extract `probe.cpp`'s spawn/pipe/timeout machinery into a
     generic argv runner vs a separately-owned git runner — ONE process-safety
     implementation either way (implementer audit §2);
   - the DR-3 fixture ledger structure (merge BOTH audits' flip/retain/add lists: planner
     F1–F7/C1–C9/green-side seams + implementer's scenario retentions, schema
     `maxItems`/`minItems`, selftest coverage);
   - partial-lifecycle (`detect_partial`/`clean_partial`) and plan-time representability
     homes (ruled in-scope, Arm 1/Arm 5 rows — reconcile §disagreement);
   - arm-plan skeleton for Arms 2–5 (design depth only for Arm 1; the later arms get
     their own design passes).
5. **Sequencing that binds you:** your `manifest.cpp` schema act starts only after
   addendum F lands (signal comes across the bridge — do not poll). The three shared
   clusters (main.cpp; error-enum/exit-map/envelope cluster; frozen oracle) are
   single-owner per act window, YOURS at the Arm-1 window; floor follows.

### Out of scope

Dirty-state/nested/submodule/quarantine design depth (later arms); the A7 floor and
adapter legs (s4-floor's); any sealed-doc amendment (escalate UP); R-4.1 arm (ii); R-4.2
sparse implementation; FU-1's ruling itself (operator's, due before Arm 2's design close).

### Process

Superpowers brainstorming owns the how; produce a design doc under
`docs/sprints/2026-08-04-s4-step4/designs/`, then address your DESIGN-REVIEW request
`TO: s4-matrix.implementer` (this seat and operator on CC only). On an approve verdict,
report design-complete to this seat and await PROCEED-TO-PLAN. Lint author-side WITH
freshness; INDEX rows at the tail; commit your filings on the docs lane (explicit paths
only — the shared tree carries sibling in-flight files); CARRY LIST every turn.

ACTIONS_GIT_REF: no product edits by this relay; this dispatch + its INDEX row are this seat's writes, committed on the docs lane
FINAL_GIT_STATUS_SHORT: not claimed here — see the reconcile SITREP of record for this seat's path-scoped status at filing
