## AUDIT RETURN — R-4.50 remains open; the cross-repo design edge is a real structural stop; the count-gate question narrows to an in-fence N=0 test shape and need not remain a blocker

ROLE: Pair Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-r450-discover-parity
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/AUDIT-pair-planner-20260905-215317.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260905-212735.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260903-151001.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-edge-scouts-20260905.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — Q1 remains a fired cross-repo design-edge STOP and must return through master to the operator before PLAN or product bytes. Q2 does not independently require authority expansion if the plan binds the required matrix to SECTION leaves inside the existing discover TEST_CASE, states N=0, and changes no workflow byte. Merge, push, publication, deployment, release, and closure remain separately held; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-2.planner, m-2.implementer, m-3.planner, operator
SUBJECT: AUDIT RETURN — still-open and overlap findings concur; Q1 independently confirmed as a structural stop; Q2 corrected to an in-fence SECTION-based N=0 plan constraint, so no workflow count transcription or additional authority is necessary

## Independent reconciliation

```text
still-open        CONCUR. src/adapters/claude_code/claude_code.cpp:570-595 appends the
                  CLAUDE_CONFIG_DIR store and returns at :581, suppressing an existing
                  $HOME/.claude. src/adapters/codex/codex.cpp:1193-1206 appends the env
                  store first, then appends the distinct normalized default. The three
                  pinned product/test files have identical SHA-256 at HEAD and 9e1a72d,
                  and git log 9e1a72d..HEAD names no commit touching them.
already-closed    NONE for R-4.50. The only Claude discover test at
                  tests/test_adapter_claude_collect.cpp:97-117 covers env-present /
                  default-absent and returns one store before and after the required fix;
                  no existing test asserts the suppression. No alternate Claude discover
                  implementation or already-built matrix was found.
product-overlap   CONCUR. open uses stores->front() at sessions.cpp:340-345, so env-first
                  order preserves selection. pack.cpp:603-640 iterates every discovered
                  store and refuses duplicate (agent, original_session_id) as
                  adapter-session-invalid. install.cpp:507-518 resolves its own Claude
                  root and is not a discover consumer. harness/selftest/stub_biv.py:140-146
                  still transcribes the old early-return behavior, so S-CP-2 remains live
                  at landing and harness stays outside this act.
recommended-next  Resolve Q1 through master/operator. Then file a plan whose product body
                  follows the Codex reference shape and whose rows 1-4 plus parity are
                  SECTION/DYNAMIC_SECTION leaves inside the existing Claude discover
                  TEST_CASE. Bind N=0 and prohibit .github/workflows/s2-harness.yml bytes.
                  Keep row 5 as the required executed E2 pack witness, expressly not c1
                  section 7 compliance. No implementation begins under this AUDIT.
```

## Q1 — confirmed structural stop

The fence rev2 blob at pdc commit `8bebc064` re-hashes to `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`. Its header is PHASE DESIGN / AUTHORITY design-only / FROM m-2.planner, but it carries neither `DESIGN_DOC_ID` nor `DESIGN_RECORD_KIND`. At that pinned tree every `DESIGN_DOC_ID` under `master/relays/r437-pack-timeout-diagnosis` is the unrelated `m3-e2-store-isolation-20260901`. The cited approving review is FROM master.master-reviewer and also carries neither design identity field.

The current v2.9.2 verifier independently inspected at `relay-lint.py:3512-3613` selects a DESIGN origin by declared `DESIGN_DOC_ID`, requires `DESIGN_RECORD_KIND: design-doc`, matching owner and design-only authority, then selects a same-owner DESIGN-REVIEW parented to that origin and requires a peer role. For a planner origin, the admitted peers are implementer or pair-implementer. Thus the archived root-mode result is structurally explained and confirmed:

```text
ERROR .relays/intg: .engine/drafts/intg.pair-planner/SCOUT-R450-FENCE-EDGE.md: declared design edge failed verification: authority-population: no DESIGN origin found for DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903
```

No consumer-plan header supplied by this pair can populate those missing authority carriers. Q1 therefore remains a mandatory STOP. The upstream choice remains either a record-specific operator waiver with the red disclosed at each filing, or a canonical m-2.planner DESIGN origin plus later m-2.implementer peer approval for the exact fence bytes. This audit does not choose or mint either arm.

## Q2 — collision premise confirmed, blocker conclusion narrowed

The premise is correct: a new `TEST_CASE` in `tests/test_adapter_claude_collect.cpp` would increment the `biv_tests` case totals pinned at 418 on macOS and 420 on Linux in `.github/workflows/s2-harness.yml`; those workflow bytes are outside the fence's discover-body-plus-tests touchable set. That optional N=1 shape therefore requires authority expansion and must not be used under the current fence.

It is not necessary. The current macOS `biv_tests` binary was run read-only against an existing multi-leaf test (`staged sidecars resolve only path associations proven by the global sidecar`). Catch2 executed four nested/peer SECTION paths and reported:

```text
<OverallResults successes="16" failures="0" expectedFailures="0" skips="0"/>
<OverallResultsCases successes="1" failures="0" expectedFailures="0" skips="0"/>
```

The existing Claude discover test also reports `OverallResultsCases successes="1"`. Therefore rows 1-4 plus parity can be independent SECTION leaves inside that existing test case while the workflow-visible case count remains one: delta N=0 on both platforms. This stays wholly within `tests/test_adapter_claude_collect.cpp`, which the fence authorizes. Q2 should become a hard plan constraint—N=0, no new TEST_CASE, no workflow byte—not an outstanding owner decision or a reason to delay the post-Q1 plan.

## Duplicate gate and witness boundary

- `tests/test_adapter_claude_collect.cpp` contains 14 `TEST_CASE` declarations. Only the case at :97-117 calls Claude `discover`; its home is the fixture parent, where `.claude` is absent.
- Repository search found no second Claude adapter discover implementation and no discover test with both `CLAUDE_CONFIG_DIR` and `$HOME/.claude` present.
- Existing `.claude` directory construction occurs in Claude install capability tests, not discover coverage. Pack/CLI fixtures that set `CLAUDE_CONFIG_DIR` do not construct the adjacent default store.
- The required row-5 duplicate witness exercises an already-live pack consumer boundary. It proves the pinned interim refusal only; it must not be relabelled as discover-contract compliance or dedupe authority.

## Scope, holds, and status

Read-only audit only. No source, test, workflow, harness, schema, branch, commit, PR, remote-CI, merge, push, publication, deployment, release, or closure action occurred. Existing build artifacts were executed read-only for the two filtered Catch2 observations; no build or source mutation was performed. Inherited S4 and root-draft worktree entries were preserved untouched. This daemon-filed relay and its INDEX row are the only own-seat repository writes.

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no such surface is touched by this read-only audit
- migration/backfill/destructive-write/canonical-data-repair: no — no mutation or repair occurred
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such state is in scope
- AI-or-automation-acts-downstream: no — no downstream act was launched
- worker/scheduler/queue/retry/async-side-effect: no — no worker or external side effect ran
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the pdc design fence is a consumed cross-repo authority record and its canonical edge fails authority population
- user-visible-control-with-materializer/downstream-consumer: no — no new user-facing control or materializer behavior is introduced by the audit
- test-runtime-role-mismatch: no — the Q2 observation used the product Catch2 binary and the same OverallResultsCases field pinned by the workflow
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — Q1 is unresolved, S-CP-2 remains live, and all downstream gates remain held
ESCALATION_SCAN_RESULT: trigger-present
OPERATOR_WAIVER: none requested or inferred
WAIVED_RISK_ACCEPTANCE: none

ACTIONS_GIT_REF: none — read-only AUDIT; no product or remote action. The daemon-filed AUDIT relay and INDEX append are the sole own-seat repository writes.
RELAY_LINT: to be engine-rendered; draft exact-file lint, daemon admission, rendered-byte equality, rendered exact-file lint, unique INDEX receipt, daemon status, and engine verification follow submission
FINAL_GIT_STATUS_SHORT:
Before filing, HEAD was `27429e5dccf5fcc617086a7c640b9dc9f6eadb27`; status contained only inherited S4 and root-draft entries, with no intg path dirty. After filing, `.relays/intg/INDEX.md` and this rendered AUDIT relay are the only expected additional own-seat paths; all inherited entries remain preserved.
