## SITREP — ASK (report-only measurement; no byte, no token needed): your `002131` IMPL RETURN is RECEIVED, every landing fence re-proved at my own bytes at `85f9c4d6`, and the sha + the Linux red are routed UP to master for m-3's byte review; the Linux red is the REGISTERED R-4.35 family signature-exact (count 3, members inside the E3 scandir-stop/TOCTOU family, two of them row-named) — but R-4.35's attribution fact of record ("`harness/` byte-identical base→candidate") does not transfer to a candidate that CHANGES `harness/`, so the executed discriminator is owed: RUN THE SAME CONTAINER INSTRUMENT (Ubuntu 24.04 amd64, `--init`, uid 1001, nofile soft=hard, `/repo-ro` clone) with Phase T cloning local `main` at the IMPLEMENTATION BASE `36968e5b338fa654e90e6f9c82568bf7d37f487a` (the rev-parse receipt against that sha), measurement stage `ctest -R 'harness-selftest'` (harness-e2 optional), ONE run, and report the failed/passed/skipped counts and the exact failing test names beside your `002131` LANDED numbers (3 failed / 1007 passed / 3 skipped; the three names) — identical family count at base ⇒ candidate-neutral per R-4.35's own method; a different set or count ⇒ a finding; NO repair, NO second commit, NO reset, NO byte anywhere; the landed commit stays frozen; report-only SITREP back to me, CC master and m-3/m-4

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/IMPL-pair-implementer-20260903-002131.md
RELATED_CONTEXT: intg-isolation/IMPL-pair-planner-20260902-205130.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/RESIDUALS.md; intg-substep1/IMPL-pair-implementer-20260828-184407.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a read-only measurement at the frozen implementation base; it edits nothing and authorizes nothing; the landed commit's acceptance is m-3's byte review via master; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP — ASK: one report-only Linux control of harness-selftest at the implementation base 36968e5 (same container instrument; rev-parse receipt; counts + exact failing names beside the LANDED 3/1007/3) — the executed discriminator for the R-4.35 attribution, since this candidate changes harness/; no byte, no repair, no second commit; the landed 85f9c4d6 stays frozen; report back to me, CC master/m-3/m-4

## Why the control, exactly

```text
R-4.35 (RESIDUALS.md:2764-2805) attributes the Linux harness-selftest reds to no candidate BY THE METHOD "harness/ byte-identical
base→candidate AND the non-root ubuntu control produces the IDENTICAL failure set at base and candidate". Your 002131 red matches the
family signature exactly (3 failed; two row-named members + the row's flaky fourth), and the static byte path from the candidate to
those tests is empty (test_e3_asserts.py / e3.py import only bivharness.report; scenario.py's only importer is cli.py) — but the
byte-identity half of the method is FALSE for this candidate, so the control half must be EXECUTED, not inferred.

instrument   the four-phase container you ran at LANDED (your linux-container.log / linux-ctest.log topology), unchanged, with
             Phase T: clone local main at 36968e5b338fa654e90e6f9c82568bf7d37f487a; receipt: git -C /repo-ro rev-parse HEAD == that sha
measurement  ctest -R 'harness-selftest' (add harness-e2 if cheap); ONE run; the pytest summary line and the exact failing test names
report       a report-only SITREP to me (CC master, m-3, m-4): base counts/names beside LANDED 3/1007/3 (+ the three names); the log
             hashed into your evidence root. No interpretation owed beyond "identical family set/count" or "differs".
not asked    no repeat sampling (m-4's call under R-4.36); no repair; no byte; no touch of the landed commit or the inherited S4 state.
```

ACTIONS_GIT_REF: docs-lane writes only — this ask via the engine; no harness byte, no product byte at either seat under this relay
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ASK-LINUX-BASE-CONTROL.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-LANDED-LINUX-RED-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
