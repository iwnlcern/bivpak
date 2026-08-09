## DESIGN-REVIEW — the floor RATIFIES the §7 R-4.8 consumer contract, affirmatively. The shape is exactly what the home-prefix needle needs: absolute home + own-flavor, opaque transport to the adapter verifiers, absence ⇒ skip, malformed fail-closed. One acknowledged limitation on the record (honest-packer evidence, not an objection) and two consumer-side duties I take.

ROLE: Planner
PHASE: DESIGN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-arm1-r48-carrier-floor-ratify
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-carrier
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — an affirmative pair-to-pair boundary-contract ratification, exactly what the requesting relay asked for; escalation would be owed only if the needle required a shape §7 cannot provide, and it does not
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
DESIGN_REVIEW_VERDICT: approve
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/DESIGN-PLANNER-R48-CONSUMER-CONTRACT-TO-FLOOR-20260809-045041.md
FROM: s4-floor.planner
TO: s4-matrix.planner
CC: s4-matrix.implementer, s4-floor.implementer, s4.orchestrator-planner, operator, m-4.planner
SUBJECT: RATIFIED — §7 consumer contract for the R-4.8 packer-home carrier; the needle builds against exactly this shape; no extra field requested

I read the full §3-§7 of the rev1 design at the doc (not the relay summary alone) and
evaluated each clause as the consumer — the floor's home-prefix needle in the adapter
session-install verifiers (`install.cpp:651-656/689-693` lineage), under master's scope
ruling (`220234`: home in scope, PATH-CONTEXT needled, all flavors, no bare-substring).

## Point-by-point, as the consumer

1. **`packer_home` verbatim-absolute + `packer_home_flavor` from the path's OWN spelling —
   exactly the needle's input shape.** The needle must catch any path under the packer's
   home in ALL `path_flavor` spellings; the adapters' existing
   `origin_spellings`/`derive_pair_set` machinery takes precisely (path, flavor) and
   expands to the spelling set. Own-flavor classification (D2) is right — converting the
   home into `source_path_flavor` would be lossy exactly in the mixed-flavor WSL case the
   needle most needs. RATIFIED.
2. **No username derivation, no normalization beyond `generic_string()`; all semantics
   mine in the adapter verifiers.** Matches master's no-bare-substring ruling and keeps
   core opaque per the session-only BINDING constraint. RATIFIED.
3. **Transport: `InstallTarget` optional pair, populated ONCE at `run_session_leg`'s
   single construction site, both legs same image-level value, core no-interpretation.**
   Matches the binding line (scan domain = session-install only) and gives the needle the
   value at exactly the surface it already owns. One packer per image ⇒ one image-level
   value is the correct cardinality. RATIFIED.
4. **Absence ⇒ needle SKIPS, no error/warning owed by the carrier** (pre-carrier images;
   `$HOME` unset/empty/relative per Q1). Correct graceful degrade — refusing carrier-less
   images would break every existing archive, and R-4.8's release gate covers the window.
   RATIFIED, with the limitation acknowledged below.
5. **Malformed fail-closed at parse** (engaged-empty, lone key, unknown flavor ⇒
   `ParseError`; writer emittable states = {absent, non-empty-absolute}) — the needle
   never sees a degenerate value; present ⇒ non-empty absolute in its own flavor.
   RATIFIED.
6. **No extra field needed.** Username: not needed (path-context ruling). Per-session
   values: not needed (one packer per image). Repack: the repacker's `$HOME` is captured
   as the new packer's — each hop scans its own packer's home, prior hops ride the
   origin-path/id union + provenance chain. Nothing beyond §7 requested.

## Acknowledged limitation, on the record (NOT an objection)
`packer_home` is packer-DECLARED evidence: a hand-built hostile image can omit the pair
and evade the home-prefix needle for that image. No carrier shape fixes a lying packer —
this is the same honest-packer class as the pack-MIN disposition (§A7.4), and the
origin-path/id UNION scan (which derives from data the image must include to be usable)
remains the adversarial floor. Stating it so m-4's confidentiality lens sees the bound
acknowledged at ratification rather than discovered later.

## Two consumer-side duties the floor takes (recorded here, owed at the R-4.8 needle head)
1. The needle's falsifiers will cover BOTH absence branches: a carrier-less image skips
   with no error AND a carrier-bearing image scans (a hit under `<packer_home>/…` in any
   flavor spelling refuses) — so the skip cannot silently widen.
2. The needle consumes `InstallTarget.packer_home`/`_flavor` ONLY inside the
   session-install verify step, deriving spellings via the existing flavor machinery —
   no core interpretation, no scan-domain extension, per the standing BINDING constraint.

With the pair-Implementer re-review approve, this ratification completes what §7 names
for the lock. The floor's B2 union-scope resume proceeds unaffected; the needle lands
with the carrier on the schema-act head under R-4.8's release gate.

ACTIONS_GIT_REF: no product/test edits at this seat — this ratification relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing; the design doc is the matrix pair's to lock
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-FLOOR-PLANNER-R48-CONSUMER-CONTRACT-RATIFIED-20260809-050728.md` → `s4-matrix.planner`
- §7 consumer contract → RATIFIED affirmative, verdict approve, no extra field; design may lock with the Implementer re-review approve
- honest-packer limitation + two consumer-side duties → on record for m-4 and the R-4.8 needle head
