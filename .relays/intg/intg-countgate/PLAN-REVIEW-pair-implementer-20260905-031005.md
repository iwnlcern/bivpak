## PLAN-REVIEW — MUST-REVISE exact 61922feb: the rev5 findings close, but the log scan masks input failure and the pre-commit guard still aborts on its expected diff under fail-fast

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review-6
PARENT_DISPATCH_ID: intg-countgate-plan-6
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-025023.md
RELATED_CONTEXT: intg-countgate/SITREP-pair-planner-20260905-030113.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-023907.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev6-20260905.txt; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — two pair-Planner-owned execution-instrument corrections; m-3's ruling, sealed design, W-4 coverage, master's release and direction (a), landed-byte veto, and all downstream holds remain unchanged
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf
TARGET_RELAY_SHA256: 9e9bc1296639e76faed4c3ace2972a622226676c78434a151e284bc4d9e3e48b
TARGET_PLAN_SHA256: 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf
TARGET_PLAN_COMMIT: 018390b16962271b055b0590d59111c6e34c3e22
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit 018390b16962271b055b0590d59111c6e34c3e22, sha256 61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf
BASE: main@018390b16962271b055b0590d59111c6e34c3e22
BRANCH: main@018390b16962271b055b0590d59111c6e34c3e22 — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST-REVISE exact 61922feb — retain the closed rev5 F1/F2 repairs; make the concatenated-log scan fail closed on input-stage errors rather than accepting cat rc 1 as grep no-match data, and make Task 2 Step 3b's expected-difference and zero-removal checks state-contained so the valid pre-commit path survives caller fail-fast

## Verdict

VERDICT: must-revise

The revision-6 plan re-hashes live and at commit `018390b` exactly to
`61922feb603838294d5fb7680c8553105eb37227eaf1f37b56e98f317d3044cf`.
The incoming PLAN re-hashes to `9e9bc129...` and passes exact-file v2.9.2
lint with freshness disabled. The sealed design re-hashes exactly to
`0099d1cf...`. The replacement root archive re-hashes to `06e41d51...` and
contains the one disclosed current-carrier W-4 design-lineage red; no
`lineage-walk` text occurs.

Revision 6 closes both `023907` findings in its changed bytes. Step 3(c)
uses the state-contained `rc=0; command || rc=$?` and `g=0; assignment ||
g=$?` forms, accepts grep status 1 as zero-match data, and preserves real
grep status 2 as a STOP. Step 5, Task 2 Step 4, and acceptance criterion 6 now
carry both arm statuses, the presence count, and the recorded `iff=` and
`hygiene=` results. The addressed `030113` corrigendum accurately limits the
two false grading greps to descriptive/history text; the live plan identities
are `intg-countgate-plan-6`, and no executable step toggles fail-fast.

Two execution defects remain in the exact plan bytes.

## F1 — the concatenated-log pipeline masks an input failure as valid data

Task 1 Step 3(f) uses:

```text
g=0; secret_hits=$(cat "$EVID"/*.log | grep -c -E '<pattern>') || g=$?
[ "$g" -le 1 ] || STOP
```

The recorded `g` is the pipeline status, not a separately proven input-stage
status. With ordinary shell pipeline semantics, `cat` can fail with status 1
on a missing, broken, or unreadable input while `grep -c` sees the remaining
stream, prints `0`, and exits 1. The plan then classifies `g=1` as legitimate
zero-match data and continues. `pipefail` is neither required nor sufficient
to distinguish that case when both `cat` and the no-match grep return 1.

The exact shape reproduces at E2 in both target shells with one valid log and
one broken `.log` symlink:

```text
bash: cat reports missing input; g=1 hits=0 accepted=yes; overall rc 0
zsh:  cat reports missing input; g=1 hits=0 accepted=yes; overall rc 0
```

Required repair: prove the concatenation/input stage separately before the
zero-match-aware grep. One deterministic shape is to write the concatenated
bytes to a non-`.log` evidence file with a checked `cat` command, STOP on any
nonzero input-stage status, then run the existing `g=0; secret_hits=$(grep -c
...) || g=$?` classification against that proved regular file. Preserve one
aggregate integer, the token-free predicate, and the no-value-read boundary.

## F2 — the pre-commit guard aborts on its valid expected difference

Task 2 Step 3b requires the current status to differ from the initial status
by exactly one added staged workflow row. Its literal sequence first runs
`diff ... > status-delta.txt`; on precisely that expected difference, `diff`
returns 1. It then runs `grep -c '^<' status-delta.txt`; on the required zero
removed rows, grep prints `0` and returns 1. Neither expected status is
captured. Under the caller fail-fast state that revision 6 expressly preserves,
the valid path exits at `diff` before the row predicates and before the commit.

The plan's exact control-flow shape reproduces at E2 in bash and zsh with an
empty initial status and one added staged workflow row:

```text
bash: rc 1; zero later output; commit path not reached
zsh:  rc 1; zero later output; commit path not reached
```

Required repair: make Step 3b state-contained too. Capture `diff` status and
accept only its data statuses while rejecting a real diff error; capture the
zero-removal count with the same grep 0/1 classification used in Step 3(c),
then explicitly require removal count 0 and the sole added row to equal
`M  .github/workflows/s2-harness.yml`. Keep the HEAD guard, exact one-path
index guard, adjacency to the commit, and every existing STOP.

## Preserved contract and next gate

No revision is requested to m-3's `012332` ruling, sealed pin `0099d1cf`, W-4,
the derived tuple, by-name censuses, discriminator predicate, platform-only
exclusion rule, ten observed cells, skip identity, workflow-only scope,
run-head fence, one local-main commit, or m-3's seven-point review. Remote CI,
merge, push, PR, publication, deployment, seal, and release remain out of
scope; the release hold is absolute.

The current PLAN contains no live implementation token. This review grants no
observation or implementation. A successor PLAN under the next unique handoff
and its exact-hash review must precede any separately governed implementation
token.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the observer correction handles credential environment names and scans retained logs
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts are trust-critical evidence
- AI-or-automation-acts-downstream: yes — a later token may change workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design and m-3 ruling govern this Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — only deterministic shell execution-instrument corrections are requested
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main 018390b; this seat writes only this daemon-submitted PLAN-REVIEW and engine INDEX projection followed by one path-scoped docs commit; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file v2.9.2 lint green with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, INDEX-row verification, and engine verification; inherited root-wide historical noise remains out of scope
FINAL_GIT_STATUS_SHORT: review-start `git status --short` = 36 inherited rows, sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3; index empty and workflow path clean; the two modified S4 projections plus 34 untracked S4/migration/root-draft paths are preserved and not claimed clean

Done: exact-hash revision-6 PLAN review, confirmation that prior F1/F2 closed, consumption of the addressed grading-hint corrigendum, and two successor findings
Not done: no token, observation, Docker run, workflow/product/plan edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — repair F1/F2 without changing the ruled observer contract or sealed gate, issue the successor under the next unique PLAN handoff, and return its new exact hash for PLAN-REVIEW
