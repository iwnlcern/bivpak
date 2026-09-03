## SITREP — isolation plan REVISION 4 @ e927c570 FILED as `intg-isolation/PLAN-pair-planner-20260902-183047.md` under the fresh handoff id `intg-isolation-plan-5`, folding the implementer's `182403` MUST-REVISE of rev3 (four findings, each CONFIRMED at my own bytes: F1 my SQLite exact-kind check filtered leak lines that only fire on a poison marker — a kind string alone never carries one, so the correct product envelope was rejected → ONE finding per leaking warning OBJECT with kind and path PAIRED, the demonstration asserts exactly one such exact line; F2 `<base>` was my authoring HEAD and seven docs-lane paths already sat between `31fb0fe` and the review commit → constraint 10: the product pin `46df8f3` for byte identity, `$IMPL_BASE` recorded at Task 3 Step 0 immediately before the ONE commit as the sole diff base, `HEAD~1 == $IMPL_BASE` proved; F3 `174557`/`175138` both carried `-4` → `-5`, every reissue increments; F4 Step 0 said three paths and Step 4's commit message said rev4 — my residual sweep had excluded those lines by GUESSING the lineage heading's position, owned; now four paths clean with the two new ones absent, rev5 `637ef197` in the message, and the self-check sweeps to the COMPUTED heading); the design pin `637ef197` @ `a07d84c`, the operator's exact-rev5 commission, the edge `1738583e`, both grains, `_rp_positive`, and the `161514` folds UNCHANGED (upheld by `182403`); root-mode re-measurement: the rev4 carrier fires NOTHING, design-edge class 0 (archive `results/lint-root-sweep-isolation-plan-rev4-20260902.txt` @ d82da72a; the root-wide delta = six standing not-consumed entries, enumerated); the token waits ONLY on the implementer's exact-hash approve at e927c570 parented to `intg-isolation-plan-5`; no harness byte, no product byte, no token yet, no push

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-5
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-182403.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-183047.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev4-20260902.txt; intg-isolation/SITREP-pair-planner-20260902-175831.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the design pin and the operator's amendment stand consumed; the token waits on the implementer's exact-hash approve; m-3's byte review at the landed sha; merge lane-local behind the operator's condition-4 token; no push before the count-gate repair (R-4.51); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — isolation plan rev4 @ e927c570 filed as intg-isolation-plan-5 (183047): the 182403 folds (paired warning objects; the two-pin IMPL_BASE rule; fresh id; four-path Step 0 + rev5 commit message); pin/edge/grains unchanged; rev4 carrier silent in root mode (archive d82da72a), design-edge class 0; token waits only on the implementer's exact-hash approve

## The re-measurement

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness   (355 s wall)
archive   results/lint-root-sweep-isolation-plan-rev4-20260902.txt  sha256 d82da72a159356858ae0821a8a5d3de33d8469c6ea7608330446f8747f488833
          340 lines; rc 1; 308 ERROR / 26 WARN root-wide
carrier   intg-isolation/PLAN-pair-planner-20260902-183047.md — NO fired entry (per-file OK); design-edge class 0; commission surface
          byte-equal to the grant (the four lines copied verbatim; rule 3d silent on this carrier)
delta     vs the rev3-refile sweep (302/26/185): design-lineage 54 → 54; rule-3d 3 → 3 (174557 + its draft + the standing 08-30 entry);
          not-consumed 185 → 191 = 182218, 182403, 175831 (relays) + the implementer's two rev3-review drafts + my 175831 draft.
```

## Standing state

- Isolation: rev4 awaits the implementer's exact-hash review at `e927c570…` (parented to `intg-isolation-plan-5`, their next unique review id); then the in-lane token with the FOUR-path SCOPE_DIFF; the ONE commit on `$IMPL_BASE` (recorded at Step 0); sha UP; m-3's byte review. Countgate observations after.
- 2a: rev12 approved (`070841`); the header re-issue ask `141420` still outstanding; the frozen six-file patch unstaged at `9e6ebe8`.
- No merge, no push, no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev4 artifact, the filed 183047, the archived measurement, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; every upstream route directory re-listed immediately before each submit; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION4-PLAN-5.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-REV4-FILED.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-183047.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev4-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
