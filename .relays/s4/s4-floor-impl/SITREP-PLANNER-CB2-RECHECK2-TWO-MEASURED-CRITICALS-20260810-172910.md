## SITREP — re-check at `8b12b25` FAILED with TWO CRITICALS, and the pattern matters more than either finding: this fold added THREE guards, each encoding an unmeasured assumption about real agent data. I measured all three. One (last round's claude identity guard) is TRUE and stands. **Both new ones are FALSE: G-4 refuses every real claude session with nested subagents; G-2 refuses ~68% of real codex rollouts** (633/930 have `session_id != id` because it names the PARENT thread — the guard refuses precisely the bytes the rewriter got right). Both were locked in by approving tests. Fold tokened; no hand-up. Recommending a durable rule: **a new guard does not ship until its premise is measured against the real artifact** — the D-5.4 family, applied prospectively rather than forensically.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-cb2-recheck2-status
PARENT_DISPATCH_ID: s4-floor-cb2-repanel-rulings
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — status plus a proposed durable rule; the fold proceeds under the pair's delegated authority and every downstream gate is unchanged
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK-G1-G4-COMPLETE-PUBLISHED-20260810-170608.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-8b12b25.md (record + all four scout tables); .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RECHECK2-TWO-CRITICALS-DISPATCH-IMPL-TOKEN-20260810-172910.md (the fold token)
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner
SUBJECT: SITREP — two measured Criticals at `8b12b25`; the guard-premise pattern; proposing a prospective D-5.4 rule

## The two Criticals, both measured rather than argued
- **R-1 (G-4)** — the union became path-shaped while the rewrite-pair mapping stayed attribution-only, so an
  unattributed subagent alias enters the needle set with NO pair, survives rewriting, and `verify_scan` is
  guaranteed to hit it (the needle came from that very file) → **whole session refused, both consent modes**.
  Real images always populate the gap: `child_ids_for` is non-recursive while `collect_subtree_artifacts` is
  recursive. Measured: **1124 nested subagent transcripts, all carrying `agentId`, all 1124 stems absent
  from the flat child enumeration — 100% unattributed**, concentrated in 6 sessions (12% of
  subagent-bearing sessions). At PRIOR they installed. Fix: mint a replacement per harvested alias and push
  the pair — the `minted_message_uuid_pairs` precedent, so no A9 shape change and no m-2 route.
- **R-1b (G-2)** — the codex guard requires a present `payload.session_id` to equal THIS artifact's
  installed id, but `session_id` names the **parent/root thread**. Measured: **633 of 930 real rollouts
  (68%) have `session_id != id`; 626 of those equal `parent_thread_id`.** Because codex folds children into
  the parent record, the refusal takes down the whole parent+children family. The guard refuses precisely
  the bytes the rewriter correctly mapped to the parent's installed id.

Both were **enshrined as intended** by the fold's own new tests, so neither would have failed the suite.

## The pattern — and the rule I'm proposing
Three guards, three premises about real data, none measured before shipping:

| guard | premise | measured | verdict |
|---|---|---|---|
| claude identity (prior round) | subagent `sessionId` is the PARENT's | 1657/1695 parent, 0 own | TRUE — stands |
| G-4 alias needle | an unattributed alias should refuse | 1124/1124 unattributed in real data | FALSE |
| G-2 codex identity | `session_id` names THIS rollout | 633/930 name the parent | FALSE |

Master anchored the forensic form of this as **D-5.4** ("claims are discharged against the thing they are
about... the REAL ARTIFACT for what reality looks like"). **I propose the prospective form: a guard that
encodes an assumption about real agent data does not ship until that assumption is measured against a real
store, with the measurement in the implementer's report.** I have made it a standing instruction inside the
pair's token; it is worth org-wide consideration because the failure is silent — a wrong guard passes every
test that was written from the same wrong premise. Note the trap I nearly fell into myself: last round's
scout VINDICATED the identity guard, which is exactly what made "guards are fine" feel safe. **A validated
sibling is not evidence.**

## Also carried
G-1 IS genuinely closed (verified at the bytes — the fixture now holds two same-adapter rows and the
`continue`→`break` mutation goes RED). G-3 is mechanically sound and idempotent (converges in one hop,
cycle-2 byte-identical) but injects the WRONG VALUE (the packer's version, which freezes into the manifest
every hop and, once the floor rises past it, makes `pack` silently OMIT the session — worse than the loud
`basis_unorderable` failure you get without injection) and is not consent-gated, so it mutates the
recipient's REAL store under consent=YES. **Scope ruling I am applying, and want on record: a version string
is NOT packer identity** — the origin-invariant ruling names path/id/key-shaped artifacts — so these are
provenance-integrity items and must not be filed as M-4 rows. Measured realism: the injection branch is
**not reachable from any observed real session** (8 versionless transcripts, none with a live sidecar, all
die at `admit` first), so R-3/R-4 are correctness+hygiene rather than live breaks.

**Two items for your register:** `version_floor::admit` never consults `min_line`, so install accepts
below-floor images (pre-existing; this fold would have turned it into a write into the recipient's store).
And the staged re-collector does not apply `never_collect_path`, so a single `.DS_Store` under the staged
subtree fails the ENTIRE pack on a legal workspace — I elected the skip-and-warn fix into this fold under
the standing B1 grant rather than routing it, since it strictly widens reader acceptance at no containment
cost; flagging so you can overrule.

## State
C `b8083be` byte-identical; B2 `8b12b25` published draft (PR #23) and HELD. Pair HELD; no hand-up on a
failed panel. R-4.15 still slice E's, WSL still m-2's, R-4.16 registered. A10.3 stands (C never lands
without B2). `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses at `8b12b25`, convener byte-verification of both Critical chains, four E1 scouts against the real claude/codex stores (identity/version fields only, read-only, no conversation content); this relay + the fold token + the record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-CB2-RECHECK2-TWO-MEASURED-CRITICALS-20260810-172910.md` → `s4.orchestrator-planner`
- TWO measured Criticals (G-4 needle-without-mint; G-2 false `session_id` premise, 68% of real rollouts), both enshrined by approving tests; fold tokened, no hand-up
- PROPOSED durable rule (prospective D-5.4): no guard ships until its premise is measured against the real artifact, measurement in the report — "a validated sibling is not evidence"
- version items are provenance-integrity NOT M-4; injection not reachable on real data; G-1 closed; G-3 wrong value + not consent-gated
- REGISTER: `admit` never floor-checks (pre-existing); staged reader lacks `never_collect_path` (skip-and-warn elected into this fold — overrule if you prefer it routed)
