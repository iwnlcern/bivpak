## PLAN-REVIEW — Slice E successor APPROVE: three distinct locks, fourteen-path scope, two ceilings and deferred parity leg are executable at d7db861

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-three-locks
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-three-locks
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this approval clears only the pair plan gate; the pair Planner still owes a separately filed implementation token after W-1 re-derivation, and m-1 plus m-3 retain the named byte-review gates before hand-up
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
TARGET_DESIGN_SHA256: 5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667
TARGET_DESIGN_COMMIT: 0e455ef5
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-THREE-LOCKS-SCOPE-LOCKED-20260816-055840.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-SUCCESSOR-RELEASED-ALL-THREE-LOCKS-CELLS-CLOSED-20260816-055058.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-CELL3-CLOSED-SUPPORTED-1-LEG-P-DEFERS-SEAM-VETOED-HOLD-CELL2-ONLY-20260816-045620.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: APPROVE — successor plan is executable at d7db861 with A4, A5 and K kept cross-identity distinct; render.hpp/main.cpp remain OUT, test_manifest returns IN, leg p self-activates only at supported/parse parity, and the coupled implementation belongs in one commit

PLAN_REVIEW_VERDICT: approve

## Review basis

I reviewed the exact `055840` plan at coordination head
`00be8e00fe7eeb491eaf3b0ddb133723aedf5bfc` and the implementation base at clean local,
unpublished head `d7db861d79e3e2320462237f15779ca66ad90290`. The user's wrapped `055807` path
resolves to the committed `055840` artifact; no separate `055807` file exists.

All three owner blobs were read as owner documents, not as one composite grant, and independently re-hashed:

```text
A4 @ 40bd88a6  9049de443e8ecc91ff72c291e85fd1c0c3c8876ac6deed28265fb10154600746  EQUAL
A5 @ c57067fe  b8686c75753558d5c8825403446afab70a3b18ffef8cdf65faf31763cc670545  EQUAL
K  @ 0e455ef5  5da667fa507f7d8687bb0ffaa2dfa919220e4939172207269f25f55c89f94667  EQUAL
```

The plan's cross-identity attribution is correct: A4 owns the new kind and earned exit behavior; A5 owns
the floor cardinal, uncertainty surfaces and legs; K owns the parse-ceiling export and its two uses; the
supported-ceiling constant at value 1 remains the separately routed m-3 determination. No identity is used
as authority for another's bytes.

## The four requested attacks

### 1. OUT rows, especially render.hpp — PASS

Both `render_probe_disclosure` and `render_summary` already receive `const SessionPreview&` at `d7db861`.
`entry_schema_unparsed_count` can therefore drive both at-least variants through a file-local helper in
`render.cpp`; no declaration or signature must move. `render.hpp` is correctly OUT.

`src/cli/main.cpp` is also correctly OUT. The new identity is selected by `kind_for_row`, reduced by
`exit_for_sessions`, and serialized by the envelope below the CLI. The five consumer surfaces already receive
the Stage 1b-ii preview/summary data. A discovered need to edit either OUT file is a STOP.

The `tests/test_manifest.cpp` reversal is grounded independently of its prior disposition. Its existing schema-2
full-parse and future-schema stub assertions are the exact place to bind FX-K-1 to
`kEntrySchemaParseCeiling` and `kEntrySchemaParseCeiling + 1`; returning this test file to IN does not reopen
the rejected Stage 1b-ii `child_count` theory.

### 2. manifest.cpp's one-line boundary — PASS

The exported constant can be added in `manifest.hpp` beside the existing constants without moving, renaming or
re-typing another export. In `manifest.cpp`, only the current `entry.entry_schema > 2` gate needs substitution.
The separate `< 1` validity floor remains byte-for-byte and semantically intact. No other production parse-ceiling
comparison exists at the reviewed head. Thus K-R3(1) and K-R3(3) are achievable exactly as written.

### 3. Leg (p)'s two-constant guard — PASS, with execution shape bound

An expression equivalent to
`kEntrySchemaSupportedCeiling < manifest::kEntrySchemaParseCeiling` reads two distinct owner constants; it does
not express both ceilings through one identifier and therefore does not trip K-R4(3). It is the correct automatic
activation predicate: current supported=1/parse=2 defers the impossible parity population, and the R-4.29 value
flip makes the leg execute without a remembered tag.

The guarded population must remain an executable, countable test unit whose conditional `SKIP` cannot abort or
mask legs (l)-(o). Its body must already pin both asymmetric per-agent objects, both notice/summary pairs, the
successful schema-2 controls and the aggregate/duplicate/bleed mutants. A hidden pending tag, unconditional skip,
or guard on anything other than the two exported constants is outside this approval.

### 4. One coupled commit — PASS and preferred

One product/test commit is the clean sequencing under K-R4. It lets the exported parse ceiling, manifest gate,
preview stub discriminator, supported-ceiling sites, A4 identity, A5 cardinal/key/surfaces and every acceptance leg
enter the history at one coherent head. Splitting them would create an avoidable intermediate Git head with
copied or disagreeing thresholds. RED-first worktree states may exist during implementation; no incoherent state
may be committed.

## Scope and within-file fences

The fourteen IN rows are complete for the described mechanism and tests. The hard boundaries remain:

- `manifest.cpp`: only `> 2` becomes `> kEntrySchemaParseCeiling`; preserve `< 1` and every other export surface.
- `envelope.cpp`: pack-side `write_manifest_summary` stays untouched; `exit_for_error` gains exactly one row.
- `sessions.cpp`: `any_sessions()` stays untouched; the skipped path has exactly the supported-ceiling test and
  the parse-ceiling stub test, not a third adjacent discriminator.
- `src/core/pack/**`, `src/cli/main.cpp`, `src/core/open/render.hpp`, `.github/**`, sealed design bytes and live
  stores stay OUT.

The existing `AgentPreview` aggregate initializers outside the listed test files do not force a scope widening:
the new defaulted member can be skipped while later designated members retain declaration order. The full compile
and suite remain the enforcement; if the bytes contradict this measurement, implementation stops rather than
editing an unlisted path.

## Acceptance review

The acceptance matrix is executable and sufficiently differentiating at supported=1:

- FX-K-1 covers full materialization at the parse ceiling, a stub at ceiling+1, and the stub's restricted shape.
- A4 (a)-(d) separately kill spelling/identity collapse, unknown-agent cause collapse, incorrect worst-outcome
  composition, and exit 0 without the pre-write notice.
- A5 (l)-(o) distinguish parsed child cardinal from stub floor, exact from at-least rendering, mixed-shape addition,
  and leakage into primary/descendant counts.
- A5 (p) is implemented now but behaviorally witnessed at the parity gate; its two-agent asymmetry makes aggregate,
  duplicate and bleed mutants independently observable when the guard opens.

For all active legs, a compile failure is not behavioral RED. Each named mutant must be executed against its killing
fixture, observed RED, reverted, and followed by GREEN. The hand-up must include function-scoped diffs for all three
within-file fences and report (p) as configured-deferred, not green-behaviorally-witnessed at this head.

## Instrumentation and gate state

The exact `055840` plan passes isolated relay lint with `--no-freshness`. Full dispatch-root lint reproduces the
disclosed external-owner lineage error naming that plan — K's pdc-owned design has no same-owner floor DESIGN relay —
among the historical/external-lineage errors. This approval does not convert that mechanical red into a waiver.
W-1 remains void until the pair Planner re-derives its seven-element tuple at token time; a mismatch means
INAPPLICABLE/NO-TOKEN.

This approval clears only PLAN-REVIEW. It grants no implementation authority. The next lawful act is the pair
Planner's separately filed implementation token parented to this review. Implementation remains local and unpublished;
GitHub Actions are not invoked. m-1 reviews every manifest byte and m-3 reviews the consumer surface and deferred-leg
disposition before hand-up. Nothing pushes, opens a PR, merges, deploys, publishes or releases; the land order and
absolute release hold bind.

ACTIONS_GIT_REF: read-only plan review at coordination head 00be8e00fe7eeb491eaf3b0ddb133723aedf5bfc and clean local unpublished implementation head d7db861d79e3e2320462237f15779ca66ad90290; exact A4/A5/K owner blobs re-hashed in ../pdc; no product, test, fixture, branch or remote mutation; this review and one append-only INDEX row ride a separate explicit-path docs-lane commit
RELAY_LINT: exact review passes with freshness before INDEX append and with --no-freshness after filing; exact source plan passes with --no-freshness; full dispatch-root lint reproduces the disclosed external-owner lineage error on the source plan plus inherited historical/external-lineage errors and does not provide a green root claim; INDEX lint retains only the standing historical inversions; append-only history is not rewritten
FINAL_GIT_STATUS_SHORT: implementation worktree clean at d7db861; coordination checkout contains unrelated pre-existing untracked relay files, and this seat commits only this review plus its one INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-THREE-LOCKS-APPROVE-20260816-060530.md` -> `s4-floor.planner`
- `PLAN_REVIEW_VERDICT: approve` -> clears only the pair plan gate
- A4 `9049de44`, A5 `b8686c75`, K `5da667fa` -> exact and cross-identity distinct
- fourteen IN rows and named OUT rows -> approved; newly discovered silence is a STOP
- supported ceiling 1 and parse ceiling 2 -> separate constants; leg (p) guarded by both and deferred until parity
- implementation sequencing -> one coupled commit after a separately filed valid token
- local macOS plus Ubuntu 24.04 `linux/amd64` Docker -> required after implementation; GitHub Actions not invoked
- m-1 manifest byte review plus m-3 consumer/deferred-leg review -> required before hand-up
- branch publication, PR, Actions, merge, deployment, publication and release -> held; release hold ABSOLUTE
