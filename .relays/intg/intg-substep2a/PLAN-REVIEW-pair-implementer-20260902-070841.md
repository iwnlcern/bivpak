## PLAN-REVIEW artifact — APPROVE revision 12 at e5875e8e: all three rev11 findings are folded, the frozen continuation checkpoint is exact, and the remaining authority chain is internally consistent

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260902-070149.md
RELATED_CONTEXT: intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-065217.md; intg-substep2a/PLAN-pair-planner-20260902-064236.md; intg-substep2a/IMPL-pair-implementer-20260902-063445.md; intg-substep2a/SITREP-pair-planner-20260902-070348.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035616.md; ../../../pdc/master/relays/intg-substep2a-format-act/PLAN-REVIEW-master-reviewer-20260902-033153.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — this approval closes only the exact-hash plan review at e5875e8e; W-5 is already effective and revision 12's replacement measurement is filed; implementation remains prohibited until a fresh addressed bare token `intg-substep2a-impl-3` stands, and byte reviews, merge, push, publication, deployment, and release retain their separate gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc
TARGET_RELAY_SHA256: e295b4a627fef166d37a816ceaa8a733e8f2b4d98f317664c16615f400e05738
TARGET_PLAN_SHA256: e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc
TARGET_PLAN_COMMIT: 9e6bccf679cbf2f7e4fe8f2fb50888c8afa6dcc3
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996; exact review filed from the docs lane after plan commit 9e6bccf6
BRANCH: intg/format-act@9e6ebe8fca2454164051573323dd7adfa2901219; retained-task3-9e6ebe8 resolves to the same sha; index clean; exactly six Task-3 paths unstaged; frozen patch sha256 fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7; NOT a candidate; no product byte moves under this review
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE exact e5875e8e — revision 12 removes the last remotes refusal obligation, encodes the exact frozen six-file Step 0-bis continuation, and states effective W-5 plus the fresh-token boundary correctly; issue no product instruction except through the promised fresh addressed token

## Verdict

APPROVE exact SHA-256 `e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc`.

Revision 12 folds all three findings from `065217` without changing sealed semantics or product bytes. The plan is now internally consistent and mechanically executable once, and only once, a fresh addressed implementation token stands.

This approval is review-only. It authorizes no correction to the frozen patch, staging, commit, Task 4, candidate submission, branch/tag/ref move, merge, push, PR, remote CI, publication, deployment, seal, or release.

## Finding-by-finding closure

### F1 — remotes refusal population: closed

The mandatory-arm paragraph now says the remaining population includes forced-payload and NonCarriedRefsNote rows and explicitly says there is NO remotes row. The stale “the remotes and” obligation is absent from current normative prose. The plan consistently classifies remotes absence/type/element-shape rejections as parser-local and empty `name`/`url` strings as accepted. The Step 0-bis correction therefore removes exactly the two unsupported table-A clauses and their two negative arms; it does not change parser acceptance.

### F2 — frozen continuation checkpoint: closed

The Branch paragraph now states the actual governed product state:

```text
HEAD/tag  9e6ebe8fca2454164051573323dd7adfa2901219
index     empty
unstaged  exactly manifest.cpp, manifest.hpp, pack.cpp,
          test_cli.cpp, test_manifest.cpp, test_open.cpp
diff      fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7
tranche 1 preserved separately as patch sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf
```

Task 3 Steps 0 through 3 are marked executed evidence under consumed token `055109`, not continuation instructions. New Step 0-bis runs first under the future fresh token and binds the exact HEAD/tag/index/path/digest checkpoint, the two-clause/two-arm deletion, table-derived recount, and then Steps 4 through 6 followed by Task 4 only on a clean Task 3. A mismatch remains a STOP. The no-byte-before-token boundary is explicit.

The expected mechanical census transition is coherent with the frozen bytes: table A 42 to 40, table B unchanged at 8, and `FX-O-INV` 50 to 48. Those are check values read back from the corrected tables, not replacement sources of truth.

### F3 — W-5 and remaining authority chain: closed

The Identity section now states W-5 as effective at registry `16e56c7b… @ b30a54c…`, cites concurrence `033153` and addressed notice `035616`, preserves the frozen selector and exact M-rev8/N/O eligible row, and retains termination on any identity/row expansion. Revision 12's root-mode replacement measurement is filed in `070348` with the same one O design-lineage red on the citing carrier.

The remaining chain is now accurate: this exact-hash approval, then a fresh addressed bare tranche-2 token `intg-substep2a-impl-3` parented to this review. No second operator grant is requested or implied. The consumed `055109` token is not reusable.

## Exact review evidence

- Incoming relay SHA-256: `e295b4a627fef166d37a816ceaa8a733e8f2b4d98f317664c16615f400e05738`; exact-file lint clean.
- Reviewed plan: commit `9e6bccf679cbf2f7e4fe8f2fb50888c8afa6dcc3`, SHA-256 `e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc`.
- Immutable rev11 comparison: commit `3eaebfc3d855d4f7a0c07e419c6d4ce5d5addbcf`, SHA-256 `0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16`; rev11 to rev12 changes one plan file, 11 insertions and 10 deletions; `git diff --check` is clean.
- Dead-current scan finds no surviving `the remotes and`, no W-5 `PROPOSED`/awaiting language, and no live two-file checkpoint outside the Step-0 historical evidence explicitly marked executed and not to be recreated.
- Revision-12 measurement SITREP `070348` records the preserved selector, filed replacement measurement, and exact e5875e8e digest.
- Product state was freshly reverified: HEAD/tag `9e6ebe8`; index empty; exact six paths; live diff SHA-256 `fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7`.
- No product, test, plan, branch, tag, ref, merge, push, PR, remote-CI, publication, deployment, seal, or release action was taken by this review.

## Boundary and execution review

- The future edit is exactly two table-A clauses plus two `FX-O-INV` arms, with any table member-name correction mechanically limited by the Step 0-bis instruction.
- Parser bytes, parser acceptance, and parser detail strings remain frozen.
- The ten-path scope, three bounded propagation hunks, explicit staging proofs, one replacement commit, and retained `9e6ebe8` tag remain unchanged.
- Steps 4 through 6 and Task 4 retain the focused/full, staged-tree, confinement, two-platform, census, and m-1/m-3 downstream review gates.
- Merge, push, publication, deployment, seal, and release remain outside this plan approval.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — review closure can permit the planner to issue the separately gated fresh implementation token
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — the exact plan controls downstream archive-format implementation
- AI-or-automation-acts-downstream: yes — a later fresh token may resume product edits
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — locked PDC O/N/M and effective W-5 govern
- user-visible-control-with-materializer/downstream-consumer: yes — writer/parser behavior controls archive bytes
- test-runtime-role-mismatch: no — historical evidence and continuation work are now explicitly partitioned
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the three exact-artifact contradictions are closed without widening scope
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: W-5 already granted and effective at the exact pinned row; no new waiver requested
- valid_waiver: yes — only within the existing frozen selector and eligible row
WAIVED_RISK_ACCEPTANCE: unchanged from W-5; this review neither expands nor reopens it

## Next gate

The pair Planner may now issue the promised fresh addressed bare implementation token `intg-substep2a-impl-3`, parented to this exact-hash approval and carrying the ten-path structured `SCOPE_DIFF`. Until that relay stands literally addressed to this seat, the six-file patch remains frozen and no Step 0-bis correction or Task 4 begins.

ACTIONS_GIT_REF: review-only inspection of plan commit 9e6bccf6 at sha256 e5875e8e, immutable rev11 at 3eaebfc3/0929edb3, the rev11 must-revise, effective W-5 notices, revision-12 measurement SITREP, and frozen product bytes; daemon submission only; no product/test/plan/ref/merge/push/PR/remote-CI/publication/deployment/seal/release action
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT: none — scoped status for the reviewed plan and intg root was clean before daemon submission; inherited S4 state exists outside this review and was untouched; the isolated product worktree remains intentionally dirty in exactly six unstaged paths as recorded above
