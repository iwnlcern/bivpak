## PLAN-REVIEW — APPROVE exact rev9 652f0d73: both run-head ancestors are now measured, recorded, and bound through acceptance

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: intg-countgate-plan-review-9
PARENT_DISPATCH_ID: intg-countgate-plan-9
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-052047.md
RELATED_CONTEXT: intg-countgate/SITREP-pair-planner-20260905-053018.md; intg-countgate/SITREP-pair-implementer-20260905-053345.md; intg-countgate/PLAN-REVIEW-pair-implementer-20260905-042414.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-countgate-plan-rev9-20260905.txt; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md; intg-countgate/IMPL-pair-planner-20260904-221146.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this exact-hash approval closes the pair PLAN-REVIEW gate; the pair Planner may separately issue the already-named implementation token under the commissioned delegation, while m-3's landed-byte review, first push, publication, deployment, seal, and release remain gated
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55
TARGET_RELAY_SHA256: 41a7778be15a4f1cc7c1557d136580506079fdc99121ed5751043e405616e5bc
TARGET_PLAN_SHA256: 652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55
TARGET_PLAN_COMMIT: d27429740b82e8590756e4e39097ac12b65f204a
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit d27429740b82e8590756e4e39097ac12b65f204a, sha256 652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55
BASE: main@d27429740b82e8590756e4e39097ac12b65f204a
BRANCH: main@d27429740b82e8590756e4e39097ac12b65f204a — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: APPROVE exact rev9 652f0d73 at d274297 — the 042414 proof-flow finding closes: Task 1 Step 1 measures 81066ef and 29acc6c separately, requires both statuses zero, records both with the run head, and carries the recorded proof into run identity, commit evidence, and acceptance 1; prior repairs and all downstream holds remain

## Verdict

VERDICT: approve

The committed plan, live plan, and PLAN carrier re-hash exactly to their declared
digests: plan `652f0d73...`, carrier `41a7778...`, and sealed design
`0099d1cf...`. The incoming PLAN and filing SITREP pass exact-file v2.9.2 lint
with freshness disabled. Commit `d274297` contains exactly the PLAN carrier,
filing SITREP, plan artifact, root archive, ROADMAP projection, and daemon INDEX
projection; it contains no workflow or product byte.

## Review finding closure

The sole rev8 finding closes without a design, scope, or observer change:

- Task 1 Step 1 captures `RUN_HEAD`, executes one
  `git merge-base --is-ancestor` check for each of `81066ef` and `29acc6c`,
  captures their statuses as `a1` and `a2`, and requires both to equal zero.
  Non-ancestor rc `1` and unknown-revision rc `128` both take the STOP branch.
- The step records the head plus both status values in
  `run-head-ancestry.txt`. The file occurs on five artifact lines spanning its
  production, Step 3(g), Task 2 Step 4, and acceptance criterion 1. The run
  identity and commit message cite the recorded rc-zero facts, and acceptance
  criterion 1 binds both ancestors to those measured results.
- Independent bash and zsh probes at the review seat reproduced required
  ancestors `a1=0 a2=0`, non-ancestor rc `1`, and unknown-revision rc `128`,
  with the capture form reaching the comparison in each case.
- The rev8-to-rev9 diff is limited to this proof flow, the unique plan-9
  handoff references, and revision history. Step 0, Step 3(f), Step 3b, and
  Step 6 retain their checked producer/status repairs; no executable
  process-substitution diff or `cat ... | grep` form reappears.

## Locked-plan checks

- Locked design and boundary: the PDC design pin remains exact. The plan still
  implements observation-then-transcription for the five
  `Catch2::Catch2WithMain`-linked binaries on macOS and Linux, with every want
  cell sourced from its own run artifact and any census drift routed UP.
- Scope: only `.github/workflows/s2-harness.yml` may change in the later act;
  no workflow hygiene stanza, product, test, CMake, schema, harness, remote-CI,
  push, PR, publication, deployment, seal, or release action is admitted.
- Acceptance and tests: all ten cells, inverted selection, skip-set identity,
  exact linkage census, two-target observer bounds, run-head/parent guard,
  staged one-path guard, post-commit one-path proof, and m-3's seven-point
  landed-byte review remain explicit and fail closed.
- Sequencing: both `81066ef` and the landed 2a commit `29acc6c` must be ancestors
  of the captured run head. Any later head movement forces full re-observation,
  never rebase, cherry-pick, or carried-forward counts.

BOUNDARY_CONTRACT:
- Writes: exact per-binary macOS and Linux count gates in `.github/workflows/s2-harness.yml`
- Reads: ten observed XML-backed tuples, run identities, linkage census, skip-name identity, observer evidence, and sealed m-3 design
- Target entity: the macOS and Linux jobs in the S2 harness workflow
- Downstream consumer: local and later authorized CI execution of the five Catch2-linked binaries
- Contract: each target-binary want tuple equals that binary's own observed tuple; selection semantics align; expected-skips membership is byte-identical
- Proof: E2 observation artifacts, local gate self-checks, one-path commit proof, and m-3's seven-point landed-byte review
- No-consumer action: reject and STOP UP; no speculative or derived count is admitted

## W-4 and the cleared transient hold

The rev9 archive re-hashes to
`1039b015e685bec2633cfae96067b0f531c7993c5c18d231842d14aa4cac0e8d`:
487 lines, 450 errors, and 37 warnings root-wide. Exactly one error names the
`052047` carrier, the W-4-covered `0099d1cf` design-lineage class; zero
lineage-walk errors occur. The sorted delta from rev8 is +6/-0, and all six
added lines are the carrier/draft and newly unconsumed relay/draft entries
enumerated by `053018`. Exact-file clean is contrast, not root closure.

The report-only `053345` hold recorded the true earlier state: the archive was
then zero bytes, the filing SITREP absent, and rev9 uncommitted. During that
hold's verification, the Planner completed the filing at `d274297` and filed
`053018`. Those three conditions are now independently cleared. The hold was
not a PLAN-REVIEW verdict, consumed no review handoff id, and creates no plan
revision requirement; this relay is the unique review verdict for plan-9.

This approval is exact-hash and review-only. It is not observation or
implementation authority and grants no merge, remote CI, push, PR,
publication, deployment, seal, or release. The release hold is absolute.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the ruled observer correction handles credential environment names and retains token-scan evidence without reading values
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts, ancestry, and run provenance are trust-critical evidence
- AI-or-automation-acts-downstream: yes — the later token changes workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — PDC design authority and master sequencing govern the Bivpak act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — the plan remains within the ruled and sealed act
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only review at main d274297; this seat writes the daemon-submitted 053345 hold, this PLAN-REVIEW, and their daemon INDEX rows followed by one path-scoped docs commit; no observation, Docker run, workflow/product/plan edit, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
RELAY_LINT: incoming PLAN and filing SITREP exact-file v2.9.2 clean with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, unique INDEX row, path-scoped commit proof, and engine verification; the disclosed W-4 root red remains covered, not called green
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
?? .relays/intg/intg-countgate/SITREP-pair-implementer-20260905-053345.md
Literal path-scoped status for this seat's own filed hold before this review submission; the shared tree additionally carries 36 inherited S4/migration/root-draft rows, preserved and not claimed clean.

Done: exact-hash rev9 PLAN review; the 042414 proof-flow finding closes; W-4 current-revision evidence and the intervening filing commit reconcile
Not done: no token, observation, Docker run, workflow/product/plan edit, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — issue `intg-countgate-impl-2` only through the commissioned delegated lineage parented to this exact-hash approval and preserve every plan STOP and downstream hold
