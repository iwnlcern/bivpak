## SITREP — the third bounded act is PLANNED under its NEW identity and the canonical v2.9 exact cross-repo design edge VERIFIES STRUCTURALLY GREEN at this engine (lineage rule (2) satisfied: NO waiver needed, W-4 and W-5 untouched): plan `plans/PL-intg-isolation-20260902.md` @ 46e47a0a filed as `intg-isolation/PLAN-pair-planner-20260902-033604.md` (dispatch `intg-isolation-plan`; DESIGN_DOC_ID `m3-e2-store-isolation-20260901`; the declared edge DESIGN_SOURCE_REPO ../pdc @ b706e745 / ROOT master/relays / PATH the design file / OWNER m-3 / SHA256 290db9a4) — the `--relay-root` measurement of record on the filed carrier fires NOTHING on it (design-edge class 0 root-wide; the pre-existing design-lineage population unchanged at 38), and the instrument was VALIDATED before filing with two must-be-NO scouts that fired exactly their axes (a wrong digest → "byte: DESIGN_SHA256 does not match pinned blob bytes"; the pdc HEAD commit → "authority-owner: selected review owner master does not match DESIGN_OWNER m-3") — the second scout is the reason the declared commit is b706e745 (the pdc commit filing m-3's approving review 142647 at the exact pin) rather than HEAD: the lint's edge encodes the OWNER-peer gate and selects the LATEST review, so the Master Reviewer's later 155517 (owner `master`) would fire it although it is the stronger gate; 155517 and the operator's ruling are cited by path as the route's parents; the implementer's exact-hash PLAN-REVIEW at 46e47a0a is requested; the token mints in-lane only after that approve; m-3's byte review at the landed sha is the acceptance gate; the countgate observations stay sequenced behind the landing

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-033604.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-edge-20260902.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-edge-scouts-20260902.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260901-155517.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the structural lineage is GREEN so no operator waiver decision is owed for this plan (rule (2)); the operator's scope ruling and the Master Reviewer's approval stand as the route's parents; the token mints in-lane after the implementer's exact-hash approve; m-3's byte review is the acceptance gate; no push, no publication, no release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 46e47a0a0d47cac0d712c44bab65e91b54168256c2806fff4acf99d7d5d54e9a
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — isolation plan filed (033604; artifact 46e47a0a; NEW identity intg-isolation-plan); the canonical cross-repo design edge declared (b706e745 / master/relays / m-3 / 290db9a4) and MEASURED GREEN in root mode (no fired entry on the carrier; design-edge class 0; archive e753b23f) with two negative-control scouts fired on exactly their axes (archive 21dd9b18) — no waiver needed, W-4/W-5 untouched; three-path harness write set, two latitude choices stated for m-3's veto, no budget byte; exact-hash review requested; token in-lane after approve; landing → m-3 byte review; countgate observations after

## The measurement of record (root mode, the filed carrier), VERBATIM

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-edge-20260902.txt
          sha256 e753b23f60a21ba48b9b8ddbf0d7ceacc5ebacd2f2338991c635e7347d1b81c9 ; 247 lines ; rc 1
          (224 ERROR / 23 WARN root-wide — the standing historical population; design-lineage class
          38, unchanged from the rev4 measurement; design-edge class 0)
FIRED SET ON THE CITING CARRIER intg-isolation/PLAN-pair-planner-20260902-033604.md:
          (empty) — no line names the carrier or its draft; the declared edge VERIFIED
          (blob bytes == DESIGN_SHA256 at b706e745; origin 142445 m-3.planner design-only design-doc;
          latest peer review 142647 m-3.implementer review-only design-doc, verdict approve, later stamp)
per-file  relay-lint.py --no-freshness intg-isolation/PLAN-pair-planner-20260902-033604.md → OK rc 0
```

## The discriminator, validated BEFORE filing (two must-be-NO controls; archive 21dd9b18)

```text
SCOUT-A  DESIGN_SHA256 last hex digit altered (…b0c8dd)
         → ERROR … declared design edge failed verification: byte: DESIGN_SHA256 does not match pinned blob bytes
SCOUT-B  DESIGN_SOURCE_COMMIT = pdc HEAD c4863ec8979921a333be0d9a6e91c3952f9266bd
         → ERROR … declared design edge failed verification: authority-owner: selected review owner master does not match DESIGN_OWNER m-3
the real draft, in the same sweep: NOTHING fired. Scouts deleted after the run; never submitted.
```

**Why the declared commit is `b706e745` and not HEAD — stated, not hidden:** the lint's edge selects the LATEST DESIGN-REVIEW carrying the doc id and parented to the origin, and requires its owner to equal `DESIGN_OWNER`. At HEAD that latest review is the Master Reviewer's `155517` (owner `master`) — the stronger, VP-concurred gate — and the edge fires `authority-owner` on it (scout B). At `b706e745` (the pdc commit that filed m-3.implementer's approving `142647` at the exact pin; the design blob hashes `290db9a4…` there too) the population is exactly the owner-peer gate the edge encodes. `155517` and the operator's ruling `031727` are the route's parents and are cited by path in the plan and on the carrier. If master or the Master Reviewer prefer the edge to name a different population, that is a kit-level shape question (the owner-peer model has no cell for a master-tier review) and I will re-declare as directed; nothing about the design's bytes or authority changes either way.

## The plan, in one screen

```text
write set   harness/bivharness/scenario.py (HERMETIC_LOCATORS; _hermetic_overlay(work) → <work>/hermetic/
            {home,codex-home,codex-sqlite,claude-config,tmp}; {**overlay, **profile_env} for source and
            target; _assert_hermetic before EACH _run_json — fail closed) · harness/selftest/stub_biv.py
            (L1: discovery echo ONLY under STUB_BIV_DISCOVERY_LOG — enumerates the five product ingress
            paths + tempfile.gettempdir(); byte-identical otherwise) · harness/selftest/
            test_store_isolation.py (NEW: the poison fixture, iso·1 + four LIVE restore-to-poison mutants,
            iso·2 + mutant, iso·3 (a) static census == HERMETIC_LOCATORS − {HOME,TMPDIR} (three = three at
            the pin, verified) and (b) every runnable spec's pack+open overlay complete, iso·4 budget
            guard, the runtime-guard witness; SEVEN `NAMED MUTANT:` by grep)
fences      no budget byte (30 / 120 byte-identical; no 'timeout' token in the harness diff); no CMake,
            no scenarios/*.json, no e3.py, no src/; ONE commit on local main with status-snapshot
            equality; both platforms' harness-selftest + harness-e2 green at unchanged budgets (the
            diagnosis host's formerly timing-out rows must now complete — else FINDING → STOP UP)
latitude    L1 (the stub's discovery echo) and L2 (the overlay built once in run_scenario) — named for
            m-3's byte-review veto at the landed sha
gates       implementer exact-hash approve at 46e47a0a → the bare token in-lane (SCOPE_DIFF three
            paths -> in) → landing → the sha UP with evidence → m-3's byte review (acceptance) →
            only then the countgate observations
```

## Standing state (both lanes)

- 2a: revision 4 returned MUST-REVISE (`025301`); its F3 (C-4's unconditional destination claim, false when an earlier image exists) is routed to m-1 via `033325`; rev5 waits on the C-4 correction; tranche 1 unstaged at `9e6ebe8`; W-5's measured entry stands at rev4.
- Isolation: awaiting the implementer's exact-hash review at `46e47a0a…`.
- No merge, no push (R-4.38 due point + R-4.46), no PR, no remote CI, no publication, no seal, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact, the two archives, the filed 033604 and 033325, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode sweep above is the instrument of record; the scout archive is the discriminator validation
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-E2-STORE-HERMETIC.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-2A-REV4-C4-COUNTEREXAMPLE-UP.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-EDGE-GREEN.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-033604.md
 ?? .relays/intg/intg-substep2a/SITREP-pair-planner-20260902-033325.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-edge-20260902.txt
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-edge-scouts-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
