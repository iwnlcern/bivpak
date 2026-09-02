## SITREP — master's `161810` CORRECTION of the isolation token predicate RECEIVED and BOUND (OBLIGATIONS §C), and the implementer's `161514` MUST-REVISE of rev2 (6133d6b2) RECEIVED — both verified at my own bytes: the Master Reviewer's `155339` (DESIGN_REVIEW_VERDICT must-revise, VP_CONCURRENCE withheld) was filed at pdc `e9119183` 15:53:54, SIX MINUTES BEFORE my rev2 filing (`155917`) — I listed the route directory at 15:50 and did not re-list before sealing; that is my defect, owned, and my filing gate now re-sweeps every upstream route directory IMMEDIATELY before submit; the operator's `031727` is EXACT to rev2 `290db9a4` @ `62a26181` on its face — rev4 does not float under it; the design is at a rev5 DRAFT in m-3's working tree (uncommitted, "UNDER REVIEW at m-3.implementer", hash 637ef197 at my read — NOT a pin, not consumed); rev2 stands as record, dead-in-waiting; THE CORRECTED PREDICATE bound verbatim in substance: token = (a) successor pin owner-approved + Master-Reviewer-approved with VP AND (b) the operator's commission amendment naming that exact pin AND (c) the plan revised to it, root-mode measured before any waiver word, exact-hash approved under a fresh handoff id — until then NON-EXECUTING preparation only; the implementer's F3/F4/F5 are VERIFIED and their folds PREPARED (below) for revision 3, which files ONLY when the successor pin and the operator's amendment are carried down; F1/F2 are the governance facts above (not plan-repairable); no harness byte, no product byte, no token, no landing

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-161810.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-161514.md; intg-isolation/PLAN-pair-planner-20260902-155917.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-155339.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-161809.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-031727.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the operator's commission amendment to the exact successor design pin precedes any isolation token (master presents it at design closure); this relay mints nothing and moves no byte; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — 161810 correction received and bound (token = successor pin owner+VP approved AND operator amendment to that exact pin AND plan revised/measured/approved under a fresh handoff id; non-executing prep until then); 161514 must-revise of rev2 received — F1/F2 are the governance facts, F3 (manifest provenance positive assertion) / F4 (unified budget command) / F5 (handoff id intg-isolation-plan-4) verified and prepared for rev3, which files only on the carried successor pin + amendment; my rev2 filed six minutes after 155339 without a re-sweep — owned; rev2 dead-in-waiting; no byte moves

## Verified at bytes

```text
155339   DESIGN-REVIEW-master-reviewer  sha256 f98123e9…  pdc commit e9119183  author 2026-09-02T15:53:54-07:00
         DESIGN_REVIEW_VERDICT: must-revise   VP_CONCURRENCE: withheld   two findings (SQLite publication precondition; exact rev2 commission)
155917   my rev2 PLAN filed 15:59:17 — AFTER 155339; my last listing of the route directory was 15:50 (154650 newest). Defect owned.
031727   operator carrier, on its face: "exact: design m3-e2-store-isolation-20260901 rev2 at pin 290db9a4… @ commit 62a26181…"
design   working tree at pdc: "(rev5) … Status: rev5 — UNDER REVIEW at m-3.implementer", sha256 637ef197…, UNCOMMITTED — a draft, not a pin;
         its RP paragraph binds the four-point non-vacuity shape (staged collectable codex rollout at the warned store root; identity +
         provenance asserted before crediting the oracle; exact kind + exact poisoned path on the mutant; same oracle red with only that tag)
product  codex.cpp:1240-1246 QUEUES (store.root, warning); :1394-1400 PUBLISHES only when report.sessions holds a session with that
         provenance.store_root — re-read; byte-identical to 46df8f3 at HEAD.
```

## The three plan-repairable findings, verified and their folds prepared (held for revision 3)

```text
F3  VERIFIED: _session_rows (scenario.py:322-328) flattens agent + row fields; the open envelope's store_root is the TARGET store; my
    rev2 oracle checked store_root for poison only, never asserted the staged identity's PROVENANCE. The product-owned carrier that
    DOES record pack-side provenance is the image's own manifest.json (extracted by the runner already at Task 3's artifact
    assertions): manifest.cpp:658-720 writes each agent_sessions[] entry with "agent", "provenance": {"store_root", "locator",
    "discovery_tier", "archived"}, "original_session_ids": {"primary", …}. PREPARED FOLD (rev3, the RP positive assertion, executed
    BEFORE the no-poison oracle is credited): _rp_positive(manifest, targets_source) REQUIRES an agent_sessions entry with
    agent == "codex", original_session_ids.primary == "019faaaa-bbbb-7ccc-8ddd-eeeeeeee0001", provenance.store_root ==
    <work>/profiles/source-codex (the staged CODEX_HOME for pack; compared as resolved paths), provenance.discovery_tier == "env";
    and the claude twin (primary "aaaaaaaa-1111-4000-8000-000000000001", store_root <work>/profiles/source-claude, tier "env");
    a miss = FINDING "isolation-positive missing: …" (FAIL). The open-side session_rows pin stays. On the CODEX_SQLITE_HOME mutant the
    driver REQUIRES exactly one warnings[] entry with kind == "CodexDbEnrichmentSkipped" AND path == <poison>/codex-sqlite/state_5.sqlite
    (exact equality, not substring) and leak tags == {"CODEX_SQLITE_HOME"} — the design rev5 shape (2)-(3), executable.
F4  VERIFIED: constraint 2 (iii) names three production-side paths; Task 3 Step 1's command named two — a contradiction I introduced at
    rev2 by widening one site and not the other. PREPARED FOLD: ONE identical command string in both places, including
    harness/scenarios/store-isolation-witness.json; the selftest exemption retained.
F5  VERIFIED: three PLAN relays hold DISPATCH_ID intg-isolation-plan (033604, 144620, 155917); the kit rule increments a reissued PLAN's
    handoff id. PREPARED FOLD: rev3 files as DISPATCH_ID intg-isolation-plan-4 (the fourth PLAN; the cycle directory intg-isolation
    unchanged), PARENT intg-commission-grant, and requests a uniquely identified exact-hash review parented to it; the token's walk is
    then unambiguous. (2a's PLANs share this shape under W-5's frozen dispatch identity — a waiver-bound exception, not a precedent.)
```

## What moves now, and what does not

- NOW: this receipt; OBLIGATIONS §C carries the corrected predicate; the three folds above are prepared text, applied in one pass at revision 3.
- NOT NOW: no plan revision (there is no successor pin to consume — a plan cannot lock a draft); no harness byte, no product byte, no token, no landing. Rev2 (`6133d6b2`) and its archived measurement stand as record, dead-in-waiting.
- REVISION 3 FILES WHEN master carries down, as addressed relays: the successor pin (owner-approved + Master-Reviewer-approved with VP) AND the operator's commission amendment naming that exact pin. It re-points the canonical edge to the commit filing the owner's approving review (derived at git), consumes the rev5 binding verbatim, folds F3/F4/F5, is root-mode measured BEFORE any waiver word, and goes to the implementer for an exact-hash review under fresh ids.
- 2a unchanged (rev12 approved; the `141420` header re-issue ask outstanding). Countgate parked behind isolation. No push before the count-gate repair (R-4.51). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — OBLIGATIONS §C (one predicate clause) and this SITREP via the engine; commit path-scoped follows; no plan byte, no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (draft pre-linted per-file); no root-mode measurement owed — no PLAN filed
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-PREDICATE-CORRECTED-REV2-DEAD-IN-WAITING.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
