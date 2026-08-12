## PLAN-REVIEW — rev1 closes the original five bounded defects, but its wave split violates the locked co-sequencing and its cap/A3 execution paths remain under-specified; MUST-REVISE on four bounded points

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-rev1
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for R1, R2, or R4; R3 exposes a locked carrier/control-flow ambiguity and routes to the design/orchestrator authority rather than being invented during implementation; the separate lineage cell is named-error disposed by addressed `154140`
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV1-EXACT-SCOPE-FOUR-CAPS-EIGHT-KEYS-WAVED-20260812-153157.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MUST-REVISE-20260812-151658.md; .relays/s4/s4-floor-impl/PROCEED-TO-PLAN-ORCHESTRATOR-PLANNER-SLICE-E-RELEASED-R418-COUPLED-DESIGN-LOCKED-20260812-150245.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-C1-RECAPTURE-GRANTED-B1-RELEASES-FOUR-CHECKS-20260806-002730.md; .relays/s4/s4-floor-impl/DISPOSITION-ORCHESTRATOR-PLANNER-SLICE-E-LINEAGE-NAMED-ERROR-DISPATCH-UNBLOCKED-20260812-154140.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: MUST-REVISE rev1 — do not activate transitive producer semantics on the flat writer; keep FX-A12-5 atomic; resolve cap refusal plus warning carrier; put A3 pin and anchored source on the same reviewed head with all four checks

PLAN_REVIEW_VERDICT: must-revise

The incoming relay is authentic for this seat and exact-file lint passes. The locked pins remain unchanged:

```text
Addendum-12 @ 3929c9c = 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
Addendum-J  @ e30f845 = 94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
product cut @ origin/main = 0db8fdd8424d27aad2c547614e9ebb95621a2794
```

Rev1 does close the prior review's R1-R5: it names the missing carrier/emitter files, binds all four caps,
deletes the unlicensed flag, separates `FX-A12-4a`, maps all eight literal keys, and supplies the required
actual-binary/local-Docker matrix. Those corrections stand. Four new execution defects prevent approval.

## R1 — Wave 1 activates transitive producer semantics before the manifest can carry their edges

The governing proceed-to-plan relay says this is **one coupled slice, not separable** and binds the
co-sequencing: “the adapter cannot emit transitive descendants before the manifest carries them.” Rev1
nevertheless calls Wave 1 “UNBLOCKED TODAY” and schedules the `child_ids` meaning change plus transitive
closure at `0db8fdd`, while edge emission waits for m-1 in Wave 2.

That intermediate product behavior is invalid at the bytes, not merely incomplete. At `0db8fdd`,
`manifest_entry_for` loops over every `session.child_ids` value and constructs a flat
`SessionChild{original_id, artifacts}` with no parent edge (`pack.cpp:379-423`). Once Wave 1 makes root R's
`child_ids` contain both P and transitive C, the current writer serializes both under R. Under J's absence
license, absence means “parent is the entry primary”; C is therefore represented as a direct child of R
rather than a child of P. Publication hold does not make a semantically false producer a valid checkpoint.

Required revision: do not green or wire any behavior-changing transitive `child_ids`/collector path into the
product binary until the named m-1 schema/writer/parser receipt is integrated and `pack.cpp` emits the real
edge on the same combined tree. RED fixtures, inert helpers, and carrier declarations may be prepared if they
cannot affect shipped behavior, but the coupled behavior must form one post-m-1 implementation wave. State
the exact combined-tree checkpoint where `1a`, `1b`, `2`, `4a`, `5`, and the E2E all become meaningful.

## R2 — `FX-A12-5` is one two-variant oracle and cannot be split across dependency states

Locked A12.6 defines key 5 as **one concrete artifact, two executed variants, both outcomes asserted**:
variant 0 has no edge and accepts by membership; variant E has the consistent edge and also accepts. The
pair is intentionally atomic so rev0's edge-derived grant and the vacuous both-refused implementation both
die in one instrument.

Rev1 assigns variant 0 to Wave 1 and variant E to Wave 2 (`§2`, `§5`). A lone variant-0 case does not measure
the locked key, and calling/counting it as `FX-A12-5` before variant E exists overstates evidence. The same
problem is visible in the plan's checkpoint order: Wave 1 can be declared green while the predicate that
distinguishes the two implementations has not been executed.

Required revision: author the two variants as one test artifact and first run/credit key 5 only on the
combined m-1+s4 tree. If an absent-edge helper is useful before then, name it as preparation, not a completed
or partial key-5 receipt. Preserve `FX-A12-4a` as the separate edge-narrowing refusal arm.

## R3 — the cap refusal and required warning have no coherent observable carrier

The locked documents jointly require both:

```text
J:       over any cap -> typed refusal of the whole entry; pack fails typed and loud
A12.4:   any entry refused for exceeding J's caps -> a line on CollectReport.warnings
```

Rev1 assigns cap detection to `pack.cpp` but asserts that every cap+1 case observes a
`CollectReport.warnings` line. At current `pack.cpp:541-550`, collection has already returned and its warnings
are immediately translated into `PackReport.warnings`; session validation and `manifest_entry_for` happen
afterward at `:552-610`. `pack()` returns `expected<PackReport>`: a typed fatal error has no successful report
from which the CLI or test can observe the warning. Appending to the local `collected->warnings` after a
pack-side cap failure would create an unreachable transient line, not the locked warning channel's visible
evidence.

Required revision: route and record the authoritative resolution of this exact control-flow seam. The revised
plan must name (a) where all four producer caps are detected, (b) the typed failure kind and whole-entry/whole-
pack behavior, (c) how the `CollectReport.warnings` line remains observable through the real CLI path when
`pack()` fails, and (d) which exact test kills a fatal error with no warning and a warning-only skip with no
typed failure. Do not silently move the caps into each adapter, add a new result carrier, or reinterpret
“pack fails” versus “entry refused” inside implementation; those are design/API decisions if the locked
contracts cannot be satisfied by an existing path.

## R4 — A3 is not a later anchor-only commit; its four checks bind the same reviewed head

The standing A3 grant is explicit: per recapture head H changing anchored file F, one review on the same head
must prove all four checks:

1. H's diff contains F's change plus exactly one corresponding anchor-literal update and nothing else
   anchor-side;
2. F's whole-file hash at H is re-derived and matches the new literal;
3. every `153958` §4 read-side session-literal class for F is mutation-checked with a disposable mutation,
   observed RED, reverted, and recorded as mutation diff plus failing assertion;
4. the review names those literal classes and proves H's own diff touches none of them.

Rev1 instead schedules E1-E4 as separate product commits and then E6 “A3 codex anchor recapture” as its own
commit. That E6 commit changes only the pin, so its commit diff cannot show F's change plus the corresponding
pin; the earlier product heads change anchored `codex.cpp` without their matching pin. Rev1 also names only
the tripwire RED/recapture/GREEN shape and omits checks 3 and 4.

Required revision: cite the `002730` A3 authority and make the final reviewed candidate head obey the grant.
Either combine/squash the anchored `codex.cpp` change with its one pin update into the same reviewed commit,
or provide a per-head recapture/check ceremony for every reviewed head that changes F; do not batch a later
anchor-only repair. List all four checks and the exact `153958` literal classes/mutation commands/receipts.
The Claude anchor remains byte-identical.

## Lineage and authorization state

The orchestrator's addressed `154140` relay now disposes the cross-repo relay-root predicate as a named known
instrument error after independently re-verifying the PDC blobs. The red remains disclosed rather than
silenced, and this structural cell no longer blocks dispatch. The **plan gate still fails on R1-R4**, so no
implementation authority exists until a revised plan receives `approve` and the pair Planner then issues a
fresh addressed `DISPATCH-IMPL` relay carrying the valid bare token and referencing `154140`.

## Boundary contract review

Writes: one J-valid transitive Codex session tree, child-parent carrier/edge, mapped-node install results, and
observable typed warnings/refusals; no intermediate flat misrepresentation.

Reads: Codex rollout ids/parents/artifacts, m-1's validated child-edge schema, and the recipient-minted mapping
over the entry's closed node set.

Target entity: one rooted session tree whose reachable artifacts are carried exactly once, whose edge absence
retains J's exact meaning, and whose root/immediate-parent identities remain distinct.

Downstream consumers: `manifest_entry_for`, J's parser, Codex staged reader/installer, `PackReport`/CLI error
and warning surfaces, and actual `biv open` restore.

Contract: producer and reader co-sequence; the declared edge only removes acceptances; all four caps produce
typed whole-entry refusal without truncation and the locked warning line; A3 attests the exact reviewed head.

Proof required: atomic two-variant FX-A12-5; separate 4a; four cap at/+1 plus fatal-without-warning and
warning-without-fatal killing arms; actual-binary disposable-store E2E; all four A3 checks; full macOS and
local Ubuntu 24.04 `linux/amd64` Docker parity after implementation. GitHub Actions remains untouched.

No-consumer action: keep behavior-changing transitive emission stopped until the m-1 receipt and cap-carrier
resolution are integrated; route any schema, result-carrier, error-semantics, `core/open`, or harness scope
change before editing.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — destinations remain recipient-minted; fixtures are sanitized and credential access is prohibited
- migration/backfill/destructive-write/canonical-data-repair: no — live stores and migrations remain out
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — restore remains explicitly user-invoked
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — s4 consumes m-1's schema and the warning/error seam crosses adapter, pack, and CLI contracts
- user-visible-control-with-materializer/downstream-consumer: yes — produced images and restored sessions are consumed by the real CLI and Codex
- test-runtime-role-mismatch: no — local product and actual-binary/Docker evidence is required; remote CI does not substitute
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — cap refusal plus warning delivery cannot be invented from the current plan/API
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed review presents the shared-schema, downstream-consumer, and carrier ambiguity
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Closeout

No implementation dispatch may issue from this review. Revise only R1-R4 and preserve the rev1 scope, four
caps, exact key matrix, sandbox, local-Docker parity, publication hold, and locked design bytes. No product,
test, schema, harness, branch, PR, Actions, merge, publish, deploy, seal, release, live-store, or credential
action was taken. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only semantic review on reconciled docs-lane HEAD `22345f31aa312e09571b9696c078e05aa47c1e0c` / product cut `0db8fdd8424d27aad2c547614e9ebb95621a2794`; re-read Addendum-12 at PDC `3929c9c`, J at `e30f845`, current `pack.cpp`, the orchestrator co-sequencing relay, the addressed `154140` lineage disposition, and the A3 `002730` four-check grant; this review relay and one append-only s4 INDEX row are the only seat-authored repository writes and will ride one explicit-path docs-lane commit
RELAY_LINT: incoming rev1 and addressed `154140` disposition exact-file no-freshness PASS; outgoing exact-file freshness PASS; shared INDEX lint reports only inherited line 222 (`20260809-142630` follows `20260809-142708`), while this appended row is monotonic and filename-matched; the target-specific relay-root red remains disclosed and is named-error disposed by `154140`
FINAL_GIT_STATUS_SHORT: recorded immediately before lint/commit in the final filed bytes; seat-authored paths are the modified s4 INDEX and this new PLAN-REVIEW relay, while all other untracked paths are pre-existing sibling artifacts
```text
 M .relays/s4/INDEX.md
?? .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV1-MUST-REVISE-COSEQUENCE-CARRIER-A3-20260812-154600.md
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
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV1-MUST-REVISE-COSEQUENCE-CARRIER-A3-20260812-154600.md` -> `s4-floor.planner`
- MUST-REVISE R1: no behavior-changing transitive `child_ids`/collector producer before the m-1 edge schema and `pack.cpp` emission coexist on the combined tree
- MUST-REVISE R2: `FX-A12-5` is one concrete artifact with two executed variants and cannot be split or credited across waves
- MUST-REVISE R3: route the exact typed-fatal plus observable `CollectReport.warnings` carrier/control-flow seam; kill both one-sided outcomes
- MUST-REVISE R4: A3 requires anchored F plus its one pin on the same reviewed head and all four mutation/class checks; a later anchor-only commit is invalid
- lineage cell is disposed by addressed `154140`, but this plan gate remains MUST-REVISE; no implementation/product/test/schema/harness/PR/Actions/merge/release action; hold ABSOLUTE
