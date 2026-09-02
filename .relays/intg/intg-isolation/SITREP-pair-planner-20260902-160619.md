## SITREP — the L1 ruling (`154650` carrying m-3 `151302`; design rev4 `5c81e86a` @ pdc `e19e61fb`, owner-approved `153855`) RECEIVED, verified at bytes (live design == blob at e19e61fb == blob at 2e52fadf, the commit filing the owner's approve; the product surfaces the RP oracle reads — `envelope.cpp:16-35`, `pack.cpp:628-629`/`:334-341`, `codex.cpp:1240-1246`/`:1394-1400` — byte-identical to 46df8f3 at HEAD) and CONSUMED: isolation plan REVISION 2 FILED (`intg-isolation/PLAN-pair-planner-20260902-155917.md`; artifact @ 6133d6b2; identity unchanged; the canonical edge re-pointed to `DESIGN_SOURCE_COMMIT 2e52fadf` derived at git) — iso·1 at TWO grains: L1 as filed at rev1 (ruled the selftest grain) + L3, the real-product grain's mechanics (ONE `isolation_witness` E2 spec against the built biv under a poisoned inherited env; a shared poison builder with VALID cwd-in-source canaries — the product would SKIP anything else, so a skipped canary could never leak; a deterministic INVALID `state_5.sqlite`; the RP oracle over product-owned evidence ONLY — warnings kind/path on both envelopes, store_root + session ids on open — FAIL not INVALID; the four real-binary mutant demonstrations by an out-of-tree driver, recorded never shipped; no knob in production harness code); write set FOUR paths (V-ISO-4 reading); root-mode re-measurement: the rev2 carrier fires NOTHING, design-edge class 0 (archive `results/lint-root-sweep-isolation-plan-rev2-20260902.txt` @ 7c93a8bb; delta = four standing not-consumed entries, enumerated); the implementer's `145804` APPROVE of rev1 (c8bd21f0) is noted with thanks and is now at a DEAD digest — a fresh exact-hash review at 6133d6b2 is the pair gate; my rev1 "option B inexpressible" is CONCEDED as answered (real product ≠ real ambient stores); the TOKEN waits on that approve AND the Master Reviewer's approve of `5c81e86a` (your `154649`), carried down as an addressed relay; nothing else moves; no harness byte, no product byte, no push

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154650.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-155917.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-145804.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev2-20260902.txt; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260902-151302.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-153855.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154649.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the owner's ruling is consumed in-lane; the token waits on the Master Reviewer's approve of rev4 (routed by you) AND the implementer's exact-hash approve at 6133d6b2; merge lane-local behind the operator's condition-4 token; no push before the count-gate repair (R-4.51); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-3.planner, m-3.implementer, intg.pair-implementer, m-2.planner
SUBJECT: SITREP — L1 ruling received and consumed: isolation plan rev2 filed (155917; artifact 6133d6b2; design rev4 5c81e86a; edge → 2e52fadf) with the RP grain as L3 (one isolation-witness E2 spec, poisoned inherited env, product-owned oracle incl. warnings[], invalid sqlite → CodexDbEnrichmentSkipped, four recorded real-binary demonstrations, no knob); rev2 carrier silent in root mode (archive 7c93a8bb); the implementer's 145804 approve of rev1 is at a dead digest — re-review at 6133d6b2 requested; token waits on that + the Master Reviewer's approve of rev4

## The re-measurement (measured BEFORE any waiver word, as ruled)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (177 s wall)
archive   results/lint-root-sweep-isolation-plan-rev2-20260902.txt  sha256 7c93a8bbe091697bc2c3830923417f4921b15de463e693c3fb1e96188d7daeca
          326 lines; rc 1; 294 ERROR / 26 WARN root-wide
carrier   intg-isolation/PLAN-pair-planner-20260902-155917.md — NO fired entry (per-file OK); design-edge class 0 root-wide
          (the re-pointed edge: DESIGN_SOURCE_COMMIT 2e52fadf; population there = m-3.planner DESIGN 152548 (rev4) → m-3.implementer
          DESIGN-REVIEW 153855 approve; DESIGN_SHA256 5c81e86a re-hashed at the blob)
delta     vs the rev1 sweep (290/26/175): design-lineage 54 → 54; not-consumed 175 → 179 = the implementer's 145804 review + its
          draft, my 144956 SITREP + its draft. Nothing else moved. No waiver is needed or requested.
```

## What rev2 does with the ruling (the design's WHAT → this plan's HOW, for the pair review and m-3's byte review)

```text
L1   unchanged as filed at rev1 (RULED the selftest grain); its poison fixture now calls the shared builder.
L3   _poison_roots(root, source): four disjoint roots + tmp; canaries = VALID two-line transcripts mirroring the staged seeds
     with cwd = the scenario source and deterministic hex UUIDs 0d15ea5e-000{1,2,3,4}-… (codex packs only cwd-in-source
     rollouts, codex.cpp:1278-1285; claude likewise, claude_code.cpp:666-669; ids must pass agent_member.hpp:17 or pack
     REFUSES, pack.cpp:631-639 — so every canary is one the product would actually pack); CODEX_SQLITE_HOME poison =
     b"POISON-CODEX-SQLITE: not a database\n" as state_5.sqlite.
     "isolation_witness": true on harness/scenarios/store-isolation-witness.json (agents claude-code + codex; pack; open
     --consent yes; session_rows pin the STAGED ids as image_session_id — the positive is not vacuous).
     run_scenario: poison built at <scratch>/<id>.poison (a SIBLING of work — the body's rmtree/mkdir never touches it);
     the body extracted verbatim into _execute_scenario and run inside _inherited_environment(poison_env) (os.environ set,
     restored in finally) — _run_json's untouched os.environ.copy() base IS the poisoned inherited env.
     _isolation_leaks([pack_envelope, open_envelope], poison_root): FINDINGS over warnings[].kind/.path (both envelopes) and
     agents[].store_root / image_session_id / installed_session_id (open); a hit = FAIL (the product ran; it leaked).
     The pack envelope carries counts only (agent_sessions[].session_count) — identities come from open; CODEX_SQLITE_HOME is
     visible ONLY through the warning (codex.cpp:1240-1246; published when a session exists for the store root, :1394-1400 —
     the staged codex transcript provides it): MUST-RP-1 honoured.
demo $EVID/rp_mutants.py (out of tree, in the plan verbatim): wraps scenario._run_json to pop ONE locator from the FINAL
     overrides after the guard; runs the RP spec against the built biv once per locator; asserts FAIL with leak tags ==
     {LOCATOR}; transcripts into the IMPL report. Fence: no 'BIVHARNESS_ISOLATION' / 'MUTANT' token in scenario.py (R-CLASS.3).
set  FOUR paths (+ the ONE spec; 17 → 18 specs; no existing spec edited — grep-proved). Budget proof (iii) spans the three
     production-side files. Markers 7 (4/1/1/1). ONE commit; both platforms; no budget byte; no push.
```

## Standing state

- Isolation: rev2 awaits the implementer's exact-hash review at `6133d6b2…` (their `145804` approved rev1 at `c8bd21f0` — a dead digest now) AND the Master Reviewer's approve of design rev4 (your `154649`), carried down; then the in-lane token with the four-path SCOPE_DIFF; landing lane-local; sha UP; m-3's byte review. Countgate observations parked behind it.
- 2a: rev12 APPROVED (`070841`); the header re-issue ask `141420` outstanding; the fresh token on receipt; the frozen six-file patch unstaged at `9e6ebe8`.
- No merge, no push, no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev2 artifact, the filed 155917, the archived re-measurement, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION2-REV4-TWO-GRAINS.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-REV2-FILED-RULING-CONSUMED.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-155917.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev2-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
