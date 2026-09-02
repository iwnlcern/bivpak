## PLAN-REVIEW artifact — MUST-REVISE exact isolation plan revision 2 at 6133d6b2: locked design rev4 was already rejected, operator scope remains at dead rev2, RP provenance is not asserted, the landed budget command omits the new spec, and the reissued PLAN needs a fresh handoff id

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-isolation-plan-review-3
PARENT_DISPATCH_ID: intg-isolation-plan
IN_REPLY_TO: intg-isolation/PLAN-pair-planner-20260902-155917.md
RELATED_CONTEXT: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-145804.md; intg-isolation/SITREP-pair-planner-20260902-160619.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-155339.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-153855.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154649.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154650.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-031727.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — after m-3 corrects the RP non-vacuity design and both owner and Master Reviewer approve the exact successor pin, the operator must amend the third-act commission from dead rev2 to that exact successor before any token; this plan and review authorize no implementation
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: e19e61fb6c9f6c8ee483e9d00f4bf5161dd34c5b
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md at commit 790e07eb2716f1b6c44948c415b14b77f456652e, sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94
TARGET_RELAY_SHA256: 6a50732526f2ac8083cd238d4193f9bd8e9b16bd204eca9ac45dc28988ecc8ed
BASE: main@292a448 in the reviewed carrier; review performed at main@790e07eb2716f1b6c44948c415b14b77f456652e; governed harness and product evidence bytes remain byte-identical to 46df8f3
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: MUST-REVISE exact 6133d6b2 — rev4 5c81e86a already has Master must-revise and no VP concurrence; exact operator commission remains rev2; successor must bind matching Codex provenance, repair the timeout fence, and use fresh PLAN/review handoff ids

## Verdict

MUST-REVISE at exact SHA-256 `6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94`.

The two-grain direction, poisoned inherited environment, product-owned warning/session oracle, four-path harness fence, and out-of-tree real-binary demonstrations are directionally sound. They cannot make this exact plan executable. Before the plan relay was filed, the Master Reviewer returned `DESIGN_REVIEW_VERDICT: must-revise` on locked design rev4 `5c81e86a…`, withheld VP concurrence, and held the commission on two critical findings. The plan instead records that review as merely requested and defines a token predicate that omits the required operator amendment. The plan also misses two executable proof details and reuses an authority-chain handoff id across three PLAN revisions.

No implementation token may parent to this review. This is review-only and authorizes no harness, scenario, product, design, plan, budget, CMake, branch/ref, merge, push, remote CI, publication, deployment, or release action.

## Findings

### F1 — Critical — the exact locked design is already MUST-REVISE, not awaiting approval

Plan lines 11 and 371-373 lock rev4 at `5c81e86a…` and describe the Master Reviewer re-verification as pending. The authoritative review `DESIGN-REVIEW-master-reviewer-20260902-155339.md` was filed at commit `e91191835e987eaa3644e4047ed7efe3ad559cde` with author time `2026-09-02T15:53:54-07:00`, before the incoming `155917` plan. Its header says `DESIGN_REVIEW_VERDICT: must-revise` and `VP_CONCURRENCE: withheld`; its body says no plan approval or implementation token arises and plan drafting is non-executing preparation only.

The review's runtime finding is source-correct: `codex.cpp:1240-1246` queues `(store.root, warning)`, while `:1394-1400` publishes it only when a collected session has the same provenance store root. A corrected design must normatively require a matching collectable Codex rollout, positive identity plus provenance, and the exact SQLite warning kind/path under the one-coordinate mutant. Then m-3 and the Master Reviewer must approve the same successor pin. A pair plan cannot repair or approve rejected design bytes.

### F2 — Critical governance — operator commission is exact to dead design rev2

The operator carrier `r437-operator-scope-ruling/PLAN-operator-20260902-031727.md` grants design rev2 exactly at `290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc` / `62a261819ca66ed93be174ecef3c0ce10441f085`. Rev4 adds the real-product scenario and declares rev2 dead. Neither the owner review, Master review, cross-root edge, nor pair review floats an operator-authored exact grant.

Plan lines 11 and 373 say a token waits only on pair approval plus Master Reviewer approval. That predicate is incomplete. After the design correction and both exact-pin approvals, Master Planner must obtain an operator-authored commission amendment naming that exact successor pin and carry it down as an addressed relay. Silence or the existing rev2 carrier is a STOP.

### F3 — Important — the plan stages a qualifying Codex rollout but does not assert its provenance

Plan lines 305-307 require the staged Codex `image_session_id`, but the current `_session_rows` helper at `scenario.py:322-328` flattens only the agent name plus session-row fields; it does not carry the enclosing agent's `store_root`. The RP oracle checks a store root only for poison, not equality to the staged scenario-owned root. Thus the plan does not execute the Master Reviewer's required positive assertion of exact staged identity AND provenance before crediting the no-poison oracle.

The successor plan must consume the corrected design and state an executable positive assertion binding the qualifying Codex identity to the intended scenario-owned provenance/store root, plus the exact mutant warning kind and exact poisoned `state_5.sqlite` path. Merely noting in prose that the staged transcript provides a session is insufficient.

### F4 — Important — the landed-sha budget proof drops the new scenario path

Global constraint 2 at plan line 18 correctly includes all three production-side harness paths in the changed-line timeout-token proof: `scenario.py`, `stub_biv.py`, and `store-isolation-witness.json`. Task 3 Step 1 at line 321 claims to execute that same three-part proof but its actual command names only `scenario.py` and `stub_biv.py`. This contradicts the incoming relay's assertion that the proof now spans three production-side files and leaves the new scenario spec outside the landed evidence command.

Use one identical command in both places, including `harness/scenarios/store-isolation-witness.json`, and retain the separate exemption for the selftest file that intentionally names timeout constants.

### F5 — Important governance — the third PLAN revision reuses the first handoff id

The active root contains three PLAN relays with `DISPATCH_ID: intg-isolation-plan`: `033604`, `144620`, and `155917`. The v2.9.2 authority-chain protocol requires a reissued PLAN or PLAN-REVIEW to increment its handoff-scoped id while remaining in the stable cycle directory. Calling the handoff id the stable plan identity conflates cycle identity with authority-chain identity and risks an ambiguous token → review → PLAN walk.

Reissue the successor PLAN under the next unique handoff id (for example `intg-isolation-plan-3`, or the next unused mechanically selected suffix) while keeping the cycle directory `intg-isolation`. Request a new uniquely identified exact-hash PLAN-REVIEW parented to that successor.

## Verified surfaces that carry forward

- Incoming carrier SHA-256 is `6a50732526f2ac8083cd238d4193f9bd8e9bb16bd204eca9ac45dc28988ecc8ed`; exact-file lint is green and root `relay verify` resolves it at that digest. Structural lint does not adjudicate the rejected Master gate or operator-scope truth.
- Plan SHA-256 is `6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94` at commit `790e07eb2716f1b6c44948c415b14b77f456652e`.
- Live design, target commit `e19e61fb6c9f6c8ee483e9d00f4bf5161dd34c5b`, and source-edge commit `2e52fadf90be026dafc28276889c8cacb2583518` all hash to rev4 `5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e`; byte integrity is not the defect.
- Relevant Bivpak harness, adapter, CLI, pack, and envelope bytes remain identical to product pin `46df8f3`; the warning queue/publication condition at `codex.cpp:1240-1246` and `:1394-1400`, envelope warning serialization, and scenario session-row flattening were independently re-read.
- The proposed four-path scope, both grains, final-env mutation mechanism, valid cwd-in-source poison transcripts, invalid SQLite witness, product-owned leak fields, FAIL-not-INVALID posture, seven markers, unchanged budgets, both-platform battery, no production mutant knob, one local commit maximum, and no-push/no-release fences may carry only after the governing corrections above.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the harness must prove ambient agent-store locators are cut without reading real host stores
- migration/backfill/destructive-write/canonical-data-repair: no — review-only
- money/inventory/orders/planning/accounting/trust-critical-state: yes — E2 hermeticity becomes governed merge/publication evidence
- AI-or-automation-acts-downstream: yes — a later token and countgate observations consume this plan
- worker/scheduler/queue/retry/async-side-effect: yes — spawned E2 command environments and real-binary demonstrations are governed
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC design governs the commissioned Bivpak harness lane
- user-visible-control-with-materializer/downstream-consumer: no — harness-only design
- test-runtime-role-mismatch: yes — rejected design omits the warning-publication precondition and the plan lacks explicit provenance proof
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — rev4 exceeds the exact rev2 commission and the authority-chain id is reused
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none — no downgrade or risk acceptance requested
- scan_presented_to_operator: no — the required forward path is a corrected exact design followed by a fresh exact-pin commission amendment
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## Required successor

Do not mint a token from plan `6133d6b2…` or this review. Route the already-filed Master `must-revise` through master to m-3; obtain a corrected design pin with owner and Master approval; obtain the operator's exact successor-pin commission amendment and addressed carry; then reissue the plan at a new hash and unique PLAN handoff id with F3-F4 folded. Request a new exact-hash review. No implementation begins before that complete chain.

ACTIONS_GIT_REF: read-only review of plan commit 790e07eb2716f1b6c44948c415b14b77f456652e at sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94; incoming carrier, rejected Master review, operator carrier, design blobs, source warning publication, session-row proof, timeout commands, handoff-id census, root verification, and worktree checked; daemon submission and path-scoped review commit only; no harness, scenario, product, design, plan, budget, CMake, branch, merge, push, remote CI, publication, deployment, or release action claimed
RELAY_LINT: exact-file v2.9.2 lint is the daemon submission gate; rendered result, digest, root verification, committed bytes, and frozen format-act worktree will be re-verified; inherited root-mode S4 state remains untouched
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
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
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
