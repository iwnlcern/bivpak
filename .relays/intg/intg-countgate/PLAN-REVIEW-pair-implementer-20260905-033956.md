## PLAN-REVIEW — MUST-REVISE exact ef60ca22: the rev6 findings close, but Step 3b process substitution still masks a missing sort input and can approve the invalid guard state

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review-7
PARENT_DISPATCH_ID: intg-countgate-plan-7
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-032325.md
RELATED_CONTEXT: intg-countgate/PLAN-REVIEW-pair-implementer-20260905-031005.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev7-20260905.txt; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — one pair-Planner-owned execution-instrument correction; m-3's ruling, sealed design, W-4 coverage, master's release and direction (a), landed-byte veto, and all downstream holds remain unchanged
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b
TARGET_RELAY_SHA256: 09c3c8d1e63babb6cd2ebf2fc3ad8d1717e652b53bcdc92aa081c200ac5a627b
TARGET_PLAN_SHA256: ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b
TARGET_PLAN_COMMIT: 407d66d19cbaf34e51a542a89428c755b67a3a82
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit 407d66d19cbaf34e51a542a89428c755b67a3a82, sha256 ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b
BASE: main@407d66d19cbaf34e51a542a89428c755b67a3a82
BRANCH: main@407d66d19cbaf34e51a542a89428c755b67a3a82 — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST-REVISE exact ef60ca22 — retain the closed rev6 repairs and Step 6 sweep fix; replace Step 3b's fallible sort process substitutions with separately checked/materialized inputs before direct diff, because a missing producer input currently becomes accepted d=1 data and can pass the entire guard

## Verdict

VERDICT: must-revise

The revision-7 plan re-hashes live and at commit `407d66d` exactly to
`ef60ca2239de64dcadf71a4b5de47c6203d6ee36056dd2fd1339c5447e4ef02b`.
The incoming PLAN re-hashes to `09c3c8d1...` and passes exact-file v2.9.2
lint with freshness disabled. The sealed design re-hashes exactly to
`0099d1cf...`. The replacement root archive re-hashes to `af7b8d25...` and
contains the one disclosed current-carrier W-4 design-lineage red; no
`lineage-walk` text occurs.

Revision 7 closes both `031005` findings on their nominal and named failure
branches. Step 3(f) proves `cat` separately before classifying grep status 1
as valid zero-match data; clean and broken-log cases reproduce correctly in
bash and zsh, and macOS `/bin/cat` accepts the recorded `--`. Step 3b captures
the expected `diff` 1 and zero-match grep 1 without changing fail-fast, then
requires zero removals and the sole exact staged workflow row. Step 6's direct
file-to-file diff also captures and distinguishes its statuses correctly. The
artifact grading counts and live `intg-countgate-plan-7` identities reproduce.

One fail-closed execution defect remains in the new Step 3b bytes.

## F1 — process-substitution producer failure is invisible to diff

Step 3b runs:

```text
d=0; diff <(sort "$EVID/status-initial.txt")
          <(sort "$EVID/status-pre-commit.txt")
          > "$EVID/status-delta.txt" || d=$?
[ "$d" -le 1 ] || STOP
```

The captured `d` is only the `diff` status. A failure in either `sort`
producer is asynchronous process-substitution state and is not propagated as
`diff` status 2. If `status-initial.txt` is missing while the checked current
status contains exactly the intended staged workflow row, the failed first
`sort` supplies an empty stream. `diff` reports the row as an ordinary added
line and exits 1; removal count is 0 with grep status 1; `added` equals the
required workflow row. Every recorded guard predicate passes despite the
missing input.

The exact Step 3b shape reproduces at E2 in both target shells:

```text
bash: sort reports missing input; d=1 removed=0 g=1
      added=M  .github/workflows/s2-harness.yml accepted=yes
zsh:  sort reports missing input; d=1 removed=0 g=1
      added=M  .github/workflows/s2-harness.yml accepted=yes
```

This contradicts the incoming relay's claim that the actual missing-input
case yields `d=2` and STOPs. A direct `diff missing-file existing-file` does
yield 2, but that is not the plan's process-substitution command.

Required repair: prove each fallible sort/input stage separately. For example,
materialize `status-initial.sorted.txt` and `status-pre-commit.sorted.txt` with
individually captured sort statuses required to be 0, then run the existing
captured-status `diff` against those regular files. An equivalent form is fine
only if producer failures are observably bound into the STOP predicate. Keep
the current status-write proof, exact HEAD and index guards, removal/addition
predicates, recorded guard fields, adjacency to commit, and all existing STOPs.

## Preserved contract and next gate

No revision is requested to the independently sound Step 3(f) repair, Step 6
sweep repair, m-3's `012332` ruling, sealed pin `0099d1cf`, W-4, the derived
tuple, by-name censuses, discriminator predicate, platform-only exclusion
rule, ten observed cells, skip identity, workflow-only scope, run-head fence,
one local-main commit, or m-3's seven-point review. Remote CI, merge, push, PR,
publication, deployment, seal, and release remain out of scope; the release
hold is absolute.

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
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — only one deterministic shell execution-instrument correction is requested
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main 407d66d; this seat writes only this daemon-submitted PLAN-REVIEW and engine INDEX projection followed by one path-scoped docs commit; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file v2.9.2 lint green with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, INDEX-row verification, and engine verification; inherited root-wide historical noise remains out of scope
FINAL_GIT_STATUS_SHORT: review-start `git status --short` = 36 inherited rows, sha256 fbf103180652d03846545754546a457eb7fa74d491b68acebc0f27bda83e75d3; index empty and workflow path clean; the two modified S4 projections plus 34 untracked S4/migration/root-draft paths are preserved and not claimed clean

Done: exact-hash revision-7 PLAN review, confirmation that the rev6 findings close on their named branches, verification of the Step 6 same-class sweep repair, and one successor finding
Not done: no token, observation, Docker run, workflow/product/plan edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — repair F1 without changing the ruled observer contract or sealed gate, issue the successor under the next unique PLAN handoff, and return its new exact hash for PLAN-REVIEW
