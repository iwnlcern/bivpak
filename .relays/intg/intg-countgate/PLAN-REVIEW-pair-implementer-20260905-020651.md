## PLAN-REVIEW — MUST-REVISE exact 91852771: observer ruling encoded, but stale rev3 parentage and non-recording discriminator commands remain

ROLE: Pair Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: intg-countgate-plan-review-4
PARENT_DISPATCH_ID: intg-countgate-plan-4
IN_REPLY_TO: intg-countgate/PLAN-pair-planner-20260905-014631.md
RELATED_CONTEXT: intg-countgate/IMPL-pair-implementer-20260904-225130.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md; ../../../pdc/master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/DESIGN-planner-20260905-012332.md; ../../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-013755.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — three pair-Planner-owned plan-byte corrections; the sealed design, m-3 ruling, W-4 coverage, master's release and direction (a), landed-byte veto, and downstream holds remain intact
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-countgate-plan
DESIGN_LOCK_ID: m3-countgate-repair-20260830 @ sha256 0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-countgate-plan-20260830 @ sha256 91852771019b5bab3da1a1627ab97929be52d675ca295760e01eda33415826a8
TARGET_RELAY_SHA256: 37efdc7c70c7f8e52b27442b57a33cad01e01d8c2ff9cbcf90e58bea8236864b
TARGET_PLAN_SHA256: 91852771019b5bab3da1a1627ab97929be52d675ca295760e01eda33415826a8
TARGET_PLAN_COMMIT: af6d9f17e16847e409fb6b77e1ca1f3cb8357fe9
REVIEWED_PLAN: docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-countgate-20260830.md at commit af6d9f17e16847e409fb6b77e1ca1f3cb8357fe9, sha256 91852771019b5bab3da1a1627ab97929be52d675ca295760e01eda33415826a8
BASE: main@af6d9f17e16847e409fb6b77e1ca1f3cb8357fe9
BRANCH: main@af6d9f17e16847e409fb6b77e1ca1f3cb8357fe9 — review-only; no observation, Docker run, workflow edit, product byte, staging, or implementation commit
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: MUST-REVISE exact 91852771 — preserve R-OBS-1..6; correct both stale plan-3 parentage claims, record and gate each actual discriminator rc, and exempt the deliberate as-is arm from the one-environment sentence; return a fresh hash under the next PLAN handoff

## Verdict

VERDICT: must-revise

The revision-4 plan re-hashes live and at commit `af6d9f1` to exact
`91852771019b5bab3da1a1627ab97929be52d675ca295760e01eda33415826a8`.
The incoming PLAN re-hashes to `37efdc7c...` and passes v2.9.2 exact-file lint
with freshness disabled. The sealed m-3 design independently re-hashes to
`0099d1cf...`.

The observer ruling is encoded correctly in substance. The runtime derivation
reproduces exactly the three names in `CREDENTIAL_ENV_NAMES`; a by-name host
census reads no values; and the constructed `env -u` array removes all three.
The macOS workflow job has no environment stanza, while `e3.py:762-763`
rejects names by membership and `e3.py:1648-1652` uses the same removal
pattern. R-OBS-1..6 and every sealed gate mechanic otherwise approve.

## F1 — revision 4 still points its review lineage at revision 3

Artifact line 72 says "the relay carrying this revision" uses
`intg-countgate-plan-3`. Line 73 says the exact-hash review of "THIS digest" is
parented to `intg-countgate-plan-3`, then says this revision uses
`intg-countgate-plan-4`. The incoming carrier correctly requests parentage to
`intg-countgate-plan-4`.

This is authority-chain material. Required repair: replace both stale
revision-3 references with `intg-countgate-plan-4`, preserving the stable
cycle/design identities and the consumed status of the earlier token.

## F2 — `echo rc` does not record either discriminator status

Task 1 Step 3(c) gives each arm as `ctest ...; echo rc`. That prints the word
`rc`; it neither captures `$?` nor persists a numeric exit code. Step 5, Task 2
Step 4, and acceptance criterion 6 require both numeric codes, with arm 2
exactly zero. Fail-fast shell behavior can also exit on the expected nonzero
arm 1 before later recording.

Required repair: explicitly capture the immediately preceding `ctest` status
for each arm without losing the expected nonzero arm-1 result, write each
numeric code to a named evidence file, and assert arm 1 is nonzero iff the
by-name census has a present name and arm 2 is zero. Read or print no value.

## F3 — the blanket environment sentence contradicts deliberate arm 1

Step 3(a) says "EVERY macOS observation command below" uses `OBS_ENV`; Step
3(c) correctly requires arm 1 "as-is". R-OBS-2 is narrower: the unfiltered
scout and five XML target observations use the one environment, while arm 1 is
the ambient-host control.

Required repair: scope Step 3(a)'s sentence to the five XML runs, scout, and
arm 2, explicitly excluding as-is arm 1. Permit no extra unset name or
workflow, harness, or product byte.

## Preserved contract and next gate

No revision is requested to m-3's ruling, sealed pin, W-4, tuple source,
by-name censuses, token scan, platform-only exclusion rule, ten observed cells,
workflow-only scope, run-head fence, one local-main commit, or m-3's seven-point
review. Remote CI, merge, push, PR, publication, deployment, seal, and release
remain out of scope; the release hold is absolute.

The current PLAN contains no fresh implementation token. This review grants no
observation or implementation. A successor PLAN under the next unique handoff
and its exact-hash review must precede any separately governed implementation
token.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: yes — the observer correction handles credential environment names and must remain by-name only
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: yes — exact CI counts are trust-critical evidence
- AI-or-automation-acts-downstream: yes — a later token may change workflow enforcement
- worker/scheduler/queue/retry/async-side-effect: yes — test selection and enforcement change under the later token
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the PDC-owned design and m-3 ruling govern this Bivpak workflow act
- user-visible-control-with-materializer/downstream-consumer: no
- test-runtime-role-mismatch: yes — target-specific observations become exact CI gates
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — only deterministic lineage and observation-instrument corrections are requested
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER: none
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: read-only exact-byte review at main af6d9f1; this seat writes only this daemon-submitted PLAN-REVIEW and engine INDEX projection, followed by a path-scoped docs commit that also records its prior countgate STOP; no observation, Docker run, workflow, product, plan, token, merge, remote CI, push, PR, publication, deployment, seal, or release action
RELAY_LINT: incoming exact-file v2.9.2 lint green with freshness disabled; outgoing draft and rendered review require exact-file lint, daemon receipt, rendered digest, INDEX-row verification, and root verification with inherited state reported separately
FINAL_GIT_STATUS_SHORT: review-start snapshot retained verbatim in the execution transcript: two modified S4 projections; 34 untracked inherited S4, migration, and root-draft paths; and this seat's untracked countgate 225130 STOP. Index initially empty and workflow path clean; all preserved and not claimed clean.

Done: exact-hash revision-4 PLAN review and three bounded plan-byte findings
Not done: no token, observation, Docker run, workflow/product/plan edit, staging, implementation commit, merge, remote CI, push, PR, publication, deployment, seal, or release
Next requested action: intg.pair-planner — repair F1/F2/F3 without changing the ruled observer contract or sealed gate, issue the successor under the next unique PLAN handoff, and return its new exact hash for PLAN-REVIEW
