## PLAN-REVIEW — Stage 1b-ii rev0 + rev1 APPROVE: M3-J-1..7 executable under V1–V11; STOP-1 exit class remains carved out

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-stage1b-ii-rev1
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-stage1b-ii-rev1
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — STOP-1 remains held until the locked m3-addendum-4 successor arrives; Stage 1b-ii returns for the owning-domain byte review(s); merge, publication, deployment and release retain separate gates
DESIGN_DOC_ID: m3-addendum-3-20260813
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-STAGE1B-II-REV1-V9-V11-AND-THREE-DETERMINED-PLACEMENTS-FOLDED-20260815-044942.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-STAGE1B-II-CONSUMER-HALF-M3J1-7-SCOPE-LOCKED-EXIT-CLASS-CARVED-20260815-044233.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1B-II-FENCE-TERMS-REFRESHED-V9-V11-OPEN-SIDE-ONLY-20260815-044250.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-1.planner
SUBJECT: APPROVE — combined rev0 plus rev1 plan carries M3-J-1..7, V1–V11, the three determined placements, full A3.6-minus-e matrix and a correctly widened STOP-1 carve-out; no implementation authority in this review

PLAN_REVIEW_VERDICT: approve

## Review basis

I reviewed `044233` and `044942` as one plan, with rev1 governing its three additions. Both exact files pass
isolated relay lint. The implementation base is the clean local unpublished head
`469d6d31f293415a2b8f44cd71d0782e61a13a35`, direct parent
`c74c20b62503c5d11398e71c2573fc9a8af0818f`.

The two normative pins were independently re-derived at this review act:

```text
m3-addendum-3 @ a016f953  eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
ADDENDUM J   @ e30f845   94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
```

The live m3-addendum-4 remains exactly `13c61b9c...67822b`, last authored at `eeda2b4`, with status
`rev1 — NOT sealed`; it does not discharge STOP-1.

## The four requested attacks

### 1. STOP-3 boundary — PASS

The plan's distinction is valid. The five-surface split leaves
`SessionPreview::any_sessions()` unchanged and introduces a sibling skipped predicate only at the three
OR-surfaces. That is the mechanism m-3 determined at the call sites.

The changes at `sessions.cpp:343-345` are different: M3-J-4 and M3-J-6 directly require the count source
to exclude every over-schema entry and replace the lossy boolean with a per-agent cardinal. Locked J names
those exact current bytes as the live R-4.24 defect, and master ruled all M3-J-1..7 into the fence. Applying
those determined obligations is not a choice to implement the predicate split by altering the shared
predicate. If implementation needs any additional count mechanism beyond those J-4/J-6 bytes, STOP-3 fires.

### 2. Widened STOP-1 carve-out — PASS

The current tree routes both genuine unknown-agent and entry-schema skips through
`Row::unknown_agent_skipped`; only `reason` separates them. `exit_for_sessions` maps each row through
`kind_for_row` and `exit_for_error`. Therefore the unnamed contract reaches the enum member, wire spelling,
exit-map row, reason-sensitive row mapping and leg (e), not merely the envelope emitter.

All of that stays carved out. The remaining notice, counts, summary, five-surface gating and open-side keys
can be implemented while the pre-existing entry-schema row continues to exit 2. The hand-up must state that
temporary retained behavior explicitly. No proposed addendum-4 spelling may be typed before its locked
successor arrives.

### 3. `render_summary` plumbing — PASS, bounded

The current signature receives `SessionsOutcome`, consent state and output path but not the per-agent skipped
cardinal. Adding read-only plumbing needed to render the sealed aggregate line is observationally neutral
outside the required new output. The placement is not free: after the complete row loop, before activation,
in the established agent order.

The implementation must not sum `outcome.id_map` blindly: that vector also receives staged mappings.
`<imported>` is the sum of `1 + children.size()` only for entries whose corresponding row outcome is
`installed`. Legs (j) and (k) kill constant-zero, row-count, eligible-count and staged-count survivors.

### 4. Anchor freshness at `469d6d3` — PASS

The live anchors remain where the plan says in substance:

- `sessions.hpp`: the two count fields and lossy skipped boolean;
- `sessions.cpp`: the sole production preview-count accumulation, unchanged `any_sessions()`, skip row before
  the `eligible.empty()` continuation;
- `src/cli/main.cpp`: the five predicate consumers and both pre-write emissions before `run_session_leg`;
- `render.cpp`: exactly one printed parent/child split and the summary row/activation seam;
- `envelope.cpp`: separate pack/open emitters plus the exit-composition path.

The plan correctly treats line numbers as head-local anchors rather than normative identities.

## Rev1 fence refresh — PASS

- V9 binds both printed relabel halves as one edit.
- V10 retains and does not re-type or version-signal `session_count`; the two split keys are additive.
- V11 leaves pack-side `write_manifest_summary` untouched. Only
  `write_open_manifest_summary` gains reader-relative counts and the suppressed-at-zero skip cardinal.
- Retaining open-side `primary_count + descendant_count` is sufficient by construction. Those operands have
  one production accumulation path, so J-4 exclusion reaches `session_count` without a second computation.
- R-4.28 remains registered and untouched; post-fold pack/open shape asymmetry is intentional.

## Acceptance matrix — PASS

The plan carries A3.6 legs (a)–(k) except the explicitly carved-out (e), with the required mutants:

- skip count is witnessed at zero, one and two;
- eligible count is witnessed at zero and four;
- imported count is witnessed at zero, two and four;
- primary/descendant composition is witnessed with a nonzero descendant;
- failed-probe, readable-newer, JSON, TTY prompt, non-TTY, explicit yes, prompt-no and explicit-no paths are
  separately observable;
- h3a and h3b stay separate;
- zero-key absence, skipped-total exclusion, guard independence, shared-predicate widening, row counting,
  staged counting, eligible counting and constant-zero implementations each have a named killing arm.

No introduced operand or predicate is protected at only one value. A compile failure earns no behavioral RED
credit, and each named mutant must be executed against the exact fixture that kills it.

## Scope and boundary

The approved production surface is the measured M3-J-1..7/A3 consumer path in
`src/core/open/{sessions,render}.{hpp,cpp}`, `src/core/report/envelope.cpp`, and the five call sites in
`src/cli/main.cpp`, plus the exact test/fixture paths the dispatch must enumerate mechanically.

Hard-outs remain:

- pack-side `write_manifest_summary`;
- `SessionPreview::any_sessions()` body;
- the entire STOP-1 exit class and leg (e);
- `src/core/manifest/**` and `src/core/pack/**`;
- reuse of the notice/key for another cause or use of the process exit code as a skip count;
- `.github/**`, sealed design bytes, live stores and credential collection.

The delegated dispatch must carry one explicit `SCOPE_DIFF` covering every planned source, test and fixture
path and must be parented to this approving review. Any OUT row or any newly discovered silence stops and
routes upward.

## Review-owner residual

The plan correctly does not decide the final byte-review owner for the J-1..3/count-source split. Master
describes all seven as m-3-surface obligations, while locked J also reserves count source and cardinality to
m-1. That does not prevent executing the determined bytes, but it must be resolved before hand-up so no
completed half enters an unowned review gate. Stage 1b-ii still returns at minimum for m-3's V1–V11 review;
any required m-1 bounded count-source review must be routed, not inferred at the keyboard.

## Relay instrumentation disclosure

Exact-file lint passes for rev0 and rev1. Full-root lint reports the known cross-owner design-lineage modeling
class against both plans: their external m-3 `DESIGN_LOCK_ID` has no same-owner floor DESIGN relay. The same
class already names the approved R7D plan for its external m-2 lock. This review does not represent that
mechanical limitation as semantic design drift; the external pins and addressed orchestrator clearance were
verified directly. The pair-Planner dispatch still owes a clean exact-file lint and the established
plan-review parent edge.

## Gate state

This approval clears only the pair plan-review gate. It is not implementation authority. The pair Planner may
issue the Stage 1b-ii implementation token, parented to this review, with STOP-1 excluded and the exact scope
enumerated. Branch remains local and unpublished. GitHub Actions remain uninvoked. Nothing pushes, opens a
PR, merges, seals, deploys, publishes or releases; the land order and absolute release hold bind.

ACTIONS_GIT_REF: read-only plan review against bivpak local head 469d6d31f293415a2b8f44cd71d0782e61a13a35 and pdc pins a016f953/e30f845; no product, test, fixture, branch or remote mutation; this review plus one append-only INDEX row ride a separate explicit-path docs-lane commit
RELAY_LINT: exact review passed with freshness before INDEX append and passed again with --no-freshness; INDEX lint reports only inherited line-222 (142630 before 142708) and line-393 (013935 before 014004) monotonicity errors; full-root lint reports 61 historical/external-lineage errors, including the disclosed same-owner-design modeling class on rev0/rev1, and no error names this review; append-only history was not rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree clean at 469d6d3; coordination checkout carries unrelated pre-existing untracked historical relay files and this seat will commit only this review plus one INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-STAGE1B-II-REV1-APPROVE-V11-OPEN-SIDE-20260815-050127.md` -> `s4-floor.planner`
- combined rev0 `044233` + rev1 `044942` -> APPROVE under V1–V11
- STOP-1 exit class + leg (e) -> held until locked m3-addendum-4 successor
- final J-1..3/count-source review ownership -> route before hand-up, not a keyboard decision
- implementation -> awaits the pair-Planner's separately filed, correctly parented token
- publication, PR, Actions, merge, seal, deployment and release -> held; release hold ABSOLUTE
