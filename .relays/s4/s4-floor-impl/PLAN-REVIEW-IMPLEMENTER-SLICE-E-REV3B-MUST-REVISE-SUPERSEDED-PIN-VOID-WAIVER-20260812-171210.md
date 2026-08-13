## PLAN-REVIEW — rev3b closes exact Stage-0 scope and key-2 classification; MUST-REVISE superseded design pin and void successor waiver

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-rev3b
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev3b
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the prior operator waiver was bounded to superseded Addendum-12 pin `154cd87e` and is void for successor bytes; the final successor needs a fresh exact-pin lineage disposition unless protocol v2.9 makes the cross-repo edge mechanically valid
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CURRENT_M2_CANDIDATE_SHA256: fcabe4fd635fc0556143fe5d5383e8b14490bf43cb221816670556c370e0084d
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3B-EXACT-STAGE0-PATHS-KEY2-GREEN-CONTROL-20260812-170013.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-MUST-REVISE-EXACT-STAGE0-SCOPE-KEY2-CONTROL-20260812-165204.md; ../pdc/master/relays/s4-build-standup/DESIGN-PLANNER-M2-CAP-CARRIER-RULED-MISLISTING-WAS-THE-DEFECT-REV3-20260812-164030.md; ../pdc/master/relays/s4-build-standup/DESIGN-REVIEW-IMPLEMENTER-M2-ADDENDUM12-REV5-MUST-REVISE-A1242-STALE-PREDICATE-20260812-170758.md; ../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-WAIVER-VALID-GRANTED-SLICE-E-TOKEN-UNBLOCKED-R427-TO-V29-WAIT-20260812-163217.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: MUST-REVISE rev3b — both requested corrections pass; old Addendum-12 lock is superseded and its pin-bounded lineage waiver cannot carry into rev4

PLAN_REVIEW_VERDICT: must-revise

The two requested rev3b corrections pass.

- Stage 0 is now closed to the exact five carried test files plus `tests/fixtures/slice-e/**`; `src/**`,
  `harness/**`, `.github/**`, and every unnamed path are explicitly forbidden. The six permitted path rows
  match rev1/rev2's carried test/fixture scope.
- Key 2 is correctly GREEN on both arms. At `0db8fdd`, both production `SessionChild` construction sites
  use designated initializers (`pack.cpp:400`, `manifest.cpp:201`). A trailing
  `std::optional<std::string> parent_id` omitted from those initializers is value-initialized to `nullopt`;
  a local C++23 compile-time assertion independently passes. A RED or required-member compile failure at
  the m-1 receipt is therefore correctly classified as a dependency-integrity stop, not an s4 RED.
- The corrected ordering is executable: Stage-0 assertion REDs `1a/3/4/6` plus GREEN controls, rebase,
  key-2 arm 2 GREEN plus assertion REDs `1b/4a/5`, then the single coupled implementation. Atomic key 5
  and the no-compile-failure-credit rule remain intact.

Those corrections stand. One newer gate-ledger defect prevents approval.

## R1 — the design pin was superseded, so gate 1 is no longer CLEAR for the successor

Rev3b still carries `DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812`, says the gate ledger is
unchanged, says lineage is CLEAR through the operator waiver, and promises to re-confirm those same pins at
token time.

That was already false when rev3b committed at `17:01:44`:

- m-2 commit `db1b216` at `16:41:39` amended the locked design, explicitly marked
  `m2-addendum12-154cd87e-lock-20260812` SUPERSEDED, and moved the candidate to `3c9c2ad9…`;
- the current m-2 candidate is unlocked rev5 `fcabe4fd…` at commit `d272c38` (`16:59:54`);
- m-2's exact-byte review at `3fad5b5` / `170758` remains MUST-REVISE, so no successor lock exists.

The operator waiver at master `163217` is bounded to Addendum-12 `154cd87e…` at `3929c9c`, consuming J
`94b6440c…`, states `VOID if any of those bytes move`, and expressly excludes any future plan. The design
bytes moved and the owning team superseded that lock. The old waiver therefore cannot establish lineage
clearance for rev4's future successor pin.

Required revision: record the old Addendum-12 lock and `163217` waiver as historical and void for successor
bytes. Gate state is now:

```text
old rev2 lineage waiver  VOID FOR SUCCESSOR — exact pin superseded
cap/design successor     OPEN — rev5 fcabe4fd is unlocked and MUST-REVISE at 170758
m-1 receipt              ABSENT
plan                     RED
token                    NONE
```

Rev4 must bind the eventual exact successor design lock and approval chain. Before delegated dispatch, it
must also carry either a fresh operator waiver/disposition for the cross-repo lineage red at that exact new
pin or fresh protocol-v2.9 lint evidence that closes the structural edge. Re-confirming `154cd87e…` cannot
discharge either obligation.

## Boundary and holds

Writes: Stage 0 remains limited to the six exact test/fixture paths; Stage 1 remains the single coupled
producer, carrier, parser-consumer, identity-gate, warning, cap, and CLI change defined by the eventual
successor plan.

Reads: exact m-1 schema receipt, the eventual successor Addendum-12 lock, locked J, store-shaped fixtures,
and adapter/pack/manifest/install/CLI contracts.

Target entity: the restored rooted session tree. Downstream consumers: manifest parser, Codex installer and
staged reader, shipped `biv pack`/`biv open`, and CLI diagnostics. Contract: J-valid parent edges, MONO,
locally minted restore identities, whole-entry cap refusal, and no silent chain loss. Proof remains E2 local
macOS plus Ubuntu 24.04 `linux/amd64` Docker parity and the actual-binary sandboxed E2E.

No-consumer action: wait for a reviewed successor Addendum-12 lock, fresh lineage closure at that pin, and
m-1's receipt; then return one final rev4 for full review. No implementation or token may be inferred from
the two accepted rev3b corrections.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — recipient-minted destinations and sanitized fixtures remain binding
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: yes — a later approval can release delegated implementation
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — m-1 schema and m-2 design contracts are consumed
- user-visible-control-with-materializer/downstream-consumer: yes — archive outcome and restored sessions are CLI-visible
- test-runtime-role-mismatch: no — actual product/CLI and local Docker evidence remain required
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — successor cap design remains unlocked and lineage waiver is pin-bounded
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: prior waiver granted for superseded pin only; void for successor bytes
- scan_presented_to_operator: yes — master `162439`, carried at `163217`
- operator_reply_after_scan: “just waive it, its getting fixed in 2.9 of the protocol”
- valid_waiver: no for the successor — the recorded grant says VOID on byte movement and excludes future plans
WAIVED_RISK_ACCEPTANCE: none for the successor pin; the old manual-lineage risk acceptance remains historical at `154cd87e…` only

## Closeout

Preserve rev3b's exact Stage-0 path closure, key-2 GREEN controls, dependency stop, corrected RED order,
fixture-only first stage, coupled Stage 1, atomic key 5, A3 ceremony, sandbox/Docker proof, and absolute
release hold. Revise only the stale pin/waiver gate ledger above, or fold its exact successor into rev4 once
m-2 completes the design path.

No product, test, schema, harness, branch, PR, GitHub Actions, merge, publish, deploy, seal, release,
live-store, or credential action was taken.

ACTIONS_GIT_REF: review at bivpak docs-lane HEAD `93c98a5b8f430e8d8fa3bcf3392d219a46a5607d`; incoming rev3b exact bytes hash `d322924f02f3c837744a83c2a23b130844fa9b0c12d31549f95fa493d9d76c18`; source cut `0db8fdd8424d27aad2c547614e9ebb95621a2794`; pdc evidence `db1b216`, `d272c38`, `3fad5b5`; this PLAN-REVIEW plus one append-only INDEX row are the only seat-authored writes and will ride one explicit-path docs-lane commit
RELAY_LINT: incoming rev3b exact-file no-freshness PASS; outgoing exact-file freshness PASS after clock restamp; shared INDEX lint reports only inherited line 222 (`20260809-142630` follows `20260809-142708`), while this appended row is monotonic and filename-matched; active dispatch root `.relays/s4/s4-floor-impl` exits 1 with 34 disclosed errors (12 cross-repo same-owner design-lineage, now including rev3b; 18 unresolved historical dispatch parents; 4 merge-claim model errors) and no error on this PLAN-REVIEW; explicit-path `git diff --check` PASS
FINAL_GIT_STATUS_SHORT: captured after INDEX append; all non-review untracked paths are pre-existing sibling artifacts
```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3B-MUST-REVISE-SUPERSEDED-PIN-VOID-WAIVER-20260812-171210.md
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
```

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3B-MUST-REVISE-SUPERSEDED-PIN-VOID-WAIVER-20260812-171210.md` -> `s4-floor.planner`
- rev3b R1/R2 PASS: exact six-path Stage 0 and key-2 GREEN/dependency-stop classification stand
- MUST-REVISE: old Addendum-12 `154cd87e` lock is superseded; its exact-pin operator waiver is void for successor bytes and cannot leave lineage CLEAR
- current m-2 rev5 `fcabe4fd` is unlocked and MUST-REVISE at `170758`; rev4 must bind the eventual successor lock plus fresh lineage closure
- m-1 receipt absent; plan red; no token/product/PR/Actions/merge/release; hold ABSOLUTE
