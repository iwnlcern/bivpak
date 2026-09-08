## PLAN-REVIEW — APPROVE exact rev7 3d09542c: both Task 7 census producers now execute at H and independently reproduce the branch-head expectations

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-r450-discover-parity-plan-review-7
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-7
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260907-162715.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260907-155514.md; intg-r450/PLAN-pair-planner-20260907-145505.md; intg-r450/SITREP-pair-implementer-20260906-201740.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260907-134909.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260907-134011.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this exact-hash review approves only the in-lane plan edge and permits the pair Planner to mint separately addressed `intg-r450-discover-parity-impl-3` with this review as parent. It does not itself grant implementation. The m-2 fenced review of C, m-3 reviews of C and H, merge bar, operator condition-4 token, landing-push rule, and absolute release hold remain
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f; m3-e2-store-isolation-20260901 @ sha256 00046a657abd6c5792e3c6222c8690b39f1a773ecbc2473ca9af2845a95813af
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee
TARGET_RELAY_SHA256: 0eae8d43aa47f9369ff0238a77d36ecce18599ef7b1dcd66ab48265b123d2d53
TARGET_PLAN_SHA256: 3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee
TARGET_PLAN_COMMIT: 07708bb7034e2c8748944ed79863150e75ad89fc
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 07708bb7034e2c8748944ed79863150e75ad89fc, sha256 3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee
BASE: review checkout main@f35e03cc6d2a6bee97b579794d2f27012a0c2428; published product base and retained candidate HEAD bbf297e36a38a1fab8c2675f945098a0633f9f8b
BRANCH: retained intg/r450-discover-parity worktree verified read-only at bbf297e36a38a1fab8c2675f945098a0633f9f8b with exactly the two prior unstaged in-scope files, sha256 4e105052a17b7e0d99bfeca28ac45cac1f6ed3c5ba0e9ba9ec62a34e530a3a51 and 90615eeb414c1cdcabeff124f95aafa6f729764860c9782f023f401a35d7a8e9; no P, C, or H authored in the governed worktree this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact rev7 3d09542c — the tree producer is git grep at H, the history producer is git rev-list at H, the stale one-sed template is gone, and independent bash/zsh executions at scratch H reproduce both written expectations

## Verdict

VERDICT: approve

The addressed carrier hashes exactly to `0eae8d43aa47f9369ff0238a77d36ecce18599ef7b1dcd66ab48265b123d2d53`, has one unique INDEX row, and passes both v2.9.2 and v2.9.3 exact-file lint with freshness disabled. Daemon-matched v2.9.2 root verification returned `ok=true`. The locked artifact hashes exactly to `3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee`, and commit `07708bb` contains those exact bytes.

The rev6-to-rev7 artifact delta is one file, six insertions and four deletions. It is confined to the title, the new revision-7 history paragraph, Task 7 Step 2's two revision arguments and stale template removal, and the revision-history entry. H's three-file surface, helper bytes, walk, P/C disclosures, H acceptance suites, owner reviews, two-commit vehicle, and downstream merge/release holds are unchanged.

## F1 — closed: both census producers execute at the branch head H

Task 7 Step 2 now binds H and executes the tree producer as `git grep ... "$H" -- .` and the history producer as `git rev-list "$H"`. The exact two-stage stripping form remains, while the unused superseded one-sed template is removed. The tree arm therefore observes H's tree; the history arm includes H, C, and their reachable ancestors. A forbidden alternation introduced in H can no longer evade both arms through the prior C selector.

Independent execution on a separately constructed scratch chain reproduced the written result in both bash and zsh. Scratch C was built by placing the retained two exact candidate files over B; scratch H was its child after applying the exact unchanged `h_stub.py`, `h_test.py`, and `h_e3pin.py` helpers. H was `61a002dda956e3ae547e6443c97c57f07c5aaadb`, its parent was C `0ac5641284a8709847005ccbb960149d08b05bfb`, and HEAD equaled H. In both shells:

- Tree `git grep` rc 0; three raw H-prefixed lines; stripped output exactly `tests/test_adapter_codex_collect.cpp:383`, `:385`, and `tests/test_cli.cpp:1188`; delta rc 0.
- History `git rev-list` rc 0; 1,250 reachable commits from H; xargs rc 0; sorted unique output exactly `tests/test_adapter_codex_collect.cpp` and `tests/test_cli.cpp`; delta rc 0.

The independent resolved scratch is `/private/var/folders/hq/f0qq8v_103q9y8prfn20rzx80000gn/T/r450-planreview7-LYPUOA`. It is external evidence and did not mutate the governed worktree.

## Independent scope and state evidence

- Incoming relay exact sha256 `0eae8d43aa47f9369ff0238a77d36ecce18599ef7b1dcd66ab48265b123d2d53`; one INDEX row; dual exact-file lint clean; daemon root verify `ok=true`.
- Plan exact sha256 `3d09542c3bc9bbb66dede9910eeb52cdd8bb817f08a6bd334cd1bbefc3163aee`, equal in the working tree and at commit `07708bb`.
- Mechanical rev7 delta: six insertions, four deletions, one plan artifact; no helper, inventory, product, test, workflow, or harness byte changed by the revision.
- Retained governed candidate: branch `intg/r450-discover-parity`, HEAD `bbf297e36a38a1fab8c2675f945098a0633f9f8b`, exactly the two prior unstaged paths, both resume hashes equal.
- The rev6 helper/fidelity/disclosure evidence remains applicable to byte-unchanged forms: stale fidelity rc 5; helper-applied fidelity rc 0; all three helpers second-apply rc 3 with no write; real P log failing set exactly `harness-selftest`, cause hits 33.

BOUNDARY_CONTRACT:
- Writes: the separately dispatched implementation may write C's three ruled files and H's exact three harness files, in separate commits and under their separate owner fences
- Reads: sealed c1 section 7, exact m-2 fence, iso rev8 follow-through, m-3 CG-R7, and observed P/C/H evidence
- Target entity: Claude store discovery parity, corresponding two count-gate literals, and the H harness model/re-pin follow-through
- Downstream consumer: open, pack, E3 tripwire, harness selftest, count gate, branch-head census, PR vehicle, and owner review gates
- Contract: P then C then H; acceptance and both census arms at H; two commits, two owners, one PR
- Proof: exact candidate hashes; fail-closed witness; P/C disclosures; H green suites; P/C/H tuple equality; exact C and H file fences; both H census arms against written expectations
- No-consumer action: reject and STOP UP; no out-of-fence byte, tag, push, PR, merge, landing push, publication, or release expansion

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, governed worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes wrote external temporary evidence only. The outgoing daemon-filed PLAN-REVIEW and append-only INDEX projection are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the reviewed step is the secrets-pattern census, but no matched values were printed or retained in this review
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and branch-head census evidence are trust-critical
- AI-or-automation-acts-downstream: yes — later separately authorized work changes workflow count gates and opens a PR vehicle
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test and one-attempt remote push steps remain gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and two owner surfaces govern this act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — the revision selector determines which commit the census observes
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — rev7 closes the exact defect without accepting residual risk or broadening scope
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main f35e03cc6d2a6bee97b579794d2f27012a0c2428; retained R-4.50 worktree read-only at intg/r450-discover-parity@bbf297e36a38a1fab8c2675f945098a0633f9f8b with its exact two prior unstaged files; external scratch C/H evidence only. No product/test/workflow/harness/plan/design edit, governed worktree or branch mutation, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file clean under v2.9.2 and v2.9.3 with freshness disabled; daemon-matched v2.9.2 root verification ok. Outgoing draft/render require both exact-file linters clean, daemon v2.9.2 admission/render through its matching client, draft/render byte equality, one unique INDEX row, and engine verification. Full-root historical noise is not represented as exact-file truth.
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
 ?? .relays/intg/intg-r450/PLAN-REVIEW-pair-implementer-20260907-155514.md
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
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-PUBLISHED-20260809-192358.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
 ?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
 ?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
 ?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
 ?? relay-draft-intg-task4-stop.md
 ?? .relays/intg/.engine/drafts/intg.pair-implementer/PLAN-REVIEW-R450-REV7-APPROVE.md
Literal status captured before daemon submission. Every listed path except this draft is inherited or a prior own-seat rendered relay. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash revision-7 PLAN-REVIEW approve; the sole `155514` finding independently reproduced closed in bash and zsh; authority, scope, owner reviews, merge, landing, and release holds preserved.
Not done: no implementation token, R-4.50 implementation continuation, product/test/workflow/harness edit, governed worktree or branch mutation, P/C/H governed commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — mint the separately addressed `intg-r450-discover-parity-impl-3` token with this approving review as parent; do not broaden any owner or downstream authority.
