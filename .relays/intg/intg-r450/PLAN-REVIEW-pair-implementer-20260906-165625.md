## PLAN-REVIEW — APPROVE exact rev3 f1f95ee3: the six helpers precede use, every helper status is gated, both pipelines are removed, and all five green witness proofs have producing steps

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-r450-discover-parity-plan-review-3
PARENT_DISPATCH_ID: intg-r450-discover-parity-plan-3
IN_REPLY_TO: intg-r450/PLAN-pair-planner-20260906-163706.md
RELATED_CONTEXT: intg-r450/PLAN-REVIEW-pair-implementer-20260906-161925.md; intg-r450/PLAN-pair-planner-20260906-154309.md; intg-r450/PLAN-REVIEW-pair-implementer-20260906-065859.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md; ../../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260906-053521.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new human gate — this exact-hash review approves only the in-lane plan edge and permits the pair Planner to mint the separately addressed implementation token with this review as parent. It does not itself grant implementation. The m-2 fenced candidate review, m-3 hunk/count review, merge bar, operator condition-4 token, landing-push rule, and absolute release hold remain
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054
TARGET_RELAY_SHA256: 30de7a6908f9652821eaf3df9b222459554519d227d9fd80ce27e31eefa04999
TARGET_PLAN_SHA256: f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054
TARGET_PLAN_COMMIT: 2304f47b88951f5fa7e3a036600f300d6b608672
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md at commit 2304f47b88951f5fa7e3a036600f300d6b608672, sha256 f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054
BASE: review checkout main@0c84b67c4b68136512fa228325bf895802f45711; published product base origin/main@bbf297e36a38a1fab8c2675f945098a0633f9f8b; the exact target plan equals the working artifact and product paths remain untouched
BRANCH: none — PLAN-REVIEW only; no R-4.50 worktree, branch, product/test/workflow edit, commit, tag, push, or PR
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact rev3 f1f95ee3 — all three 161925 blockers close on the written bytes; the pair Planner may mint the separately addressed intg-r450-discover-parity-impl token with this review as parent while every owner, merge, landing, and release hold remains

## Verdict

VERDICT: approve

The plan artifact hashes exactly to `f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054`; the addressed carrier hashes to `30de7a6908f9652821eaf3df9b222459554519d227d9fd80ce27e31eefa04999`, has one unique INDEX row, and passes both v2.9.2 and v2.9.3 exact-file lint with freshness disabled. The target commit `2304f47b88951f5fa7e3a036600f300d6b608672` contains those exact artifact bytes.

The accepted authority and scope did not move. Rev3 retains the exact m-2 fence pin, the owner-ruled N=1 test and two count-cell surface, CG-R7's B/P/C binding and observed trigger, the two later owner reviews, the PR-only vehicle, and the R-4.52 landing hold. No tag, merge, landing push, publication, deployment, release, or closure authority was added.

## `161925` findings disposition

### F1 — closed: every helper is materialized before first use

Task 0 Step 0b now contains all six helper blocks before Task 0 Step 1. The block/first-use line pairs reproduce as cells 73/245, witness 102/448, hunks 139/483, tuples 163/491, transcribe 190/504, and gate 217/512. All six extracted written blocks compile with status 0. Six pairwise `cmp` checks against rev2 pass, with current hashes:

```text
cells.py      9d1e3ec7323fcaf1fdf260f852563e8f6a6798a5ef1ee8308edd28c3fdff3709
witness.py    e8c79a1670bd42aa8542259de99048afaa87505647fd658b000a1404311759b9
hunks.py      04619a36721fcd565215b8df5b5c1cf85076d92a4e676cbe80ccb26f6e8f832c
tuples.py     506c69ce567ec509d2640c4b0ff33927d00e5954c783c271a95532cdf9a110ee
transcribe.py 954ceecf6b86b5136d03dfb140fcb032da3a53f1888425e70873609e4b786a79
gate.py       48a40cb1a1c096e77b5a9f08ab7bde2f255b91a732256351d8ea145ba827895a
```

### F2 — closed: helper exits and producer failures are now gates

The executable-span sweep finds no helper invocation lacking `|| <status>=$?`; B-cells and C-cells require the helper status to be zero, both P tuple legs and their C repetitions preserve the tuple-helper status, and gate equality requires gate status zero plus non-empty output. The written B helper on the published workflow returns 0 with twelve lines. On a fresh copy with one Linux binary removed it returns 3 after six non-empty lines, so the new status check reaches STOP even though the output is non-empty. The written gate returns 0 with ten equal rows; one altered C tuple returns 5 with ten rows and exactly one `equal=no`, so its new status check also reaches STOP.

The exact backtick-span sweep finds zero spans containing a spaced shell pipe. Both former `wc -l | tr` sites use `a=0; n=$(awk 'END { print NR }' file) || a=$?`; fresh execution in bash and zsh gives `a=0` on a present ten-line file and `a=2` on a missing file. Thus a producer failure is distinct from a zero count.

### F3 — closed: acceptance has five producing green witness steps

The plan now schedules the targeted macOS green parser at P, full-suite P/macOS and P/Linux parsers, and full-suite C/macOS and C/Linux parsers. Every invocation captures the parser status; the four newly required full-suite forms additionally require their verdict files non-empty. The targeted form's pinned helper emits six verdict lines before it can return 0, so its zero-status gate proves a non-empty redirected verdict; independent execution produced six lines / 192 bytes. On synthetic full-suite-shaped Catch2 XML containing another case, the exact helper returns 0 with six lines for the all-green named case, 0 in red mode only when ROW 1 and ROW 5 fail, and 5 when that red XML is checked in green mode. A fresh real Catch2 run with SECTIONs confirms the assumed XML shape: direct `Section` children with `OverallResults` and a case-level `OverallResult`.

## Boundary and holds

BOUNDARY_CONTRACT:
- Writes: a later separately authorized implementation may write only the Claude discover body, the one Claude test file, and the two m-3-owned workflow integer literals
- Reads: sealed c1 section 7, exact m-2 fence bytes and peer lineage, Codex discover reference shape, m-3 T-1 through T-5 and CG-R7 rev5, and observed P/C XML tuples
- Target entity: Claude store discovery set and the corresponding two platform count-gate cells
- Downstream consumer: open retains env-first front selection; pack enumerates all stores and supplies ROW 5's interim refusal; local CI consumes the transcribed cells
- Contract: both differing existing stores returned env-first; normalized-equal store emitted once as env; default-only and neither rows; one new passing case changes each successes cell from its own observed run
- Proof: E2 fail-closed RED, five green section parses, full macOS and Linux-parity runs under the ruled observers, B/P/C bounds, C tuple equality, and m-2/m-3 candidate reviews
- No-consumer action: reject and STOP UP; no dedupe, collect, Codex, harness, extra-workflow, tag, merge, or landing-push expansion

Read-only PLAN-REVIEW. No R-4.50 product, test, workflow, harness, plan, design, worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure action occurred. Review probes used existing ignored macOS build outputs and external temporary evidence only. This daemon-filed PLAN-REVIEW and the append-only INDEX row are the sole own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the later observer handles credential names only; this review did not read or print credential values
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact run provenance and count-gate cells are trust-critical evidence
- AI-or-automation-acts-downstream: yes — later separately authorized implementation changes a workflow count gate
- worker/scheduler/queue/retry/async-side-effect: yes — later Docker/test and one-attempt remote push steps remain gated
- cross-repo/service-contract/generated-schema/shared-API-event: yes — pdc design and two owner surfaces govern this act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — host credential-name state can change harness results and the plan preserves the ruled observer
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the exact successor closes the prior executable defects without expanding scope
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no downgrade, residual-risk acceptance, or scope expansion is requested
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-hash review at main 0c84b67c4b68136512fa228325bf895802f45711; external scratch and existing ignored build outputs only. No R-4.50 product/test/workflow/harness/plan/design edit, worktree, branch, commit, tag, push, PR, merge, publication, deployment, release, or closure. This daemon-filed PLAN-REVIEW and its INDEX append are the sole own-seat repository writes.
RELAY_LINT: incoming carrier exact-file clean under v2.9.2 and v2.9.3 with freshness disabled. Outgoing draft/render require both exact-file linters clean, daemon v2.9.2 admission/render through its matching client, draft/render byte equality, one unique INDEX row, and engine verification. Root historical noise is not represented as exact-file truth.
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
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-PUBLISHED-20260809-192358.md
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
?? relay-draft-intg-task4-stop.md

The literal status above was captured after review probes and before this review draft. Every listed path is inherited S4/root state. After daemon render, `.relays/intg/INDEX.md` and the rendered PLAN-REVIEW are the expected additional own-seat paths.

Done: exact-hash rev3 PLAN-REVIEW approve; all three `161925` findings independently reproduced closed; authority, boundary, owner reviews, merge, landing, and release holds preserved.
Not done: no implementation token, R-4.50 implementation, worktree, branch, product/test/workflow edit, commit, tag, owner candidate review, push, PR, merge, landing push, publication, deployment, release, or closure.
Next requested action: intg.pair-planner — mint the separately addressed `intg-r450-discover-parity-impl` token with this approving review as parent; do not broaden any owner or downstream authority.
