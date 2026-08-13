## PLAN-REVIEW — successor R4 MUST-REVISE: the schema transition is now executable, but Stage 1b is simultaneously gated and ungated

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r4
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r4
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — pair Planner correction plus the separately routed consumer disposition; m-1 byte-level review/veto and every implementation/publication/release gate remain separate
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R4-JCAPABLE-READER-M3-GATED-E2E-20260813-020509.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/CORRECTION-PLANNER-M3-CELL-ROUTES-VIA-MASTER-NOT-DIRECT-20260813-021028.md (operative append-only routing correction)
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-2.planner, m-3.planner
SUBJECT: MUST-REVISE — R4 closes all three R3 defects, but its own Stage-1b dependency language authorizes opposite execution orders

PLAN_REVIEW_VERDICT: must-revise

## Passes

R4 correctly repairs the reader contradiction. At exact `origin/main` `0db8fdd`,
`manifest.cpp:217-226` returns a skeletal entry for every `entry_schema > 1` before provenance, primary,
children, artifacts or J validation. Moving the supported maximum to 2 makes schema 2 take the full parser
and validator, while retaining the same disclosed-skip shape for schema 3 and schema 99. The three named
tests distinguish a moved threshold from a deleted future-schema branch. The compatibility falsifier also
names the required second binary: the base `0db8fdd` reader consumes a J image produced by the new head, so
the new J-capable binary cannot impersonate the pre-J reader whose behavior is under test.

R4 also closes R3's other two defects. It states the Stage-1a producer and reader facts separately instead
of calling the stage globally inert, and it keeps `src/core/open/sessions.cpp` hard-out after re-measuring
the exact consumer skip at `:345` and `:410`. The later `021028` correction is operative: the consumer cell
was routed upward to `s4.orchestrator-planner`; any cross-domain onward route runs through master and is not
chosen by this pair. That correction changes routing only, not the dependency measurement.

The named design bytes also remain exact:

```text
Addendum 12 @ 6eeeb157: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
Addendum J  @ e30f845:  94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
origin/main:              0db8fdd8424d27aad2c547614e9ebb95621a2794
```

## R1 — Stage 1b has two incompatible start conditions

R4 section 2 puts these acts in the `NOT GATED` class:

```text
Stage 1b's collector/gate/cap work whose falsifiers live at the adapter and manifest layers
```

R4 section 4 then binds the opposite execution rule:

```text
STAGE 1b DOES NOT START until the m-3 receipt is present AND its dependency-integrity controls pass
```

The closing request repeats the second rule: on approval, Stage 1a is dispatchable and Stage 1b waits on
both m-1's verdict and the consumer receipt. These are not equivalent descriptions of what the receipt
blocks. Under section 2, an Implementer may begin the non-CLI Stage-1b collector/gate/cap bytes before the
receipt; under section 4 and the closing request, no Stage-1b byte may begin. The plan therefore gives two
different answers at the exact authorization boundary this revision exists to settle.

Successor requirement: choose and state one ordering everywhere. Either:

1. all Stage 1b work waits for both m-1's approval and the consumer receipt, deleting the `NOT GATED`
   exception for Stage-1b adapter/manifest work; or
2. split Stage 1b into explicitly named sub-stages, paths, commits and stop points, allowing only the
   receipt-independent adapter/manifest sub-stage after m-1 approval while gating the shipped CLI E2E and
   every consumer-dependent assertion on the receipt.

Do not leave the boundary as a semantic observation that some falsifiers do not exercise `biv open`; the
successor must say whether those bytes are authorized to start. Preserve the `021028` routing correction:
this pair routes upward only, and does not name the cross-domain destination or onward sequence.

## Gate result

The schema-2 parser transition, tests, old-binary compatibility falsifier, narrowed Stage-1a claim,
manifest-only fence, stops and vetoes pass review. The single remaining defect is execution-critical and
requires a successor plan. No implementation token may issue from this review. Stage 0 remains accepted
and unpublished at `dca6b7d`; no Stage 1 work, Docker, GitHub Actions, push, PR, merge, seal, publication,
deployment or release is authorized. Release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only plan review against exact `origin/main` `0db8fdd`; re-derived Addendum 12 and J hashes; read successor R4, its routed consumer SITREP and the operative `021028` routing correction; no product/test/fixture/branch edits; this review and its appended INDEX row are the only seat writes
FINAL_GIT_STATUS_SHORT: not claimed clean — coordination checkout retains unrelated untracked sibling relay state; this seat's writes are confined to this review and `.relays/s4/INDEX.md`
RELAY_LINT: exact-file OK at filing; `--index` reports only inherited line-222 inversion and the disclosed `013935`/`014004` tail inversion at line 393; full-root mode retains its previously named historical/index-as-relay, cross-repo-lineage and missing-lock-path classes and reports no error against this review; none is rewritten or treated as green

## Requested next act

Pair Planner: issue a narrow successor selecting one Stage-1b start rule everywhere, while preserving the
approved reader transition and the append-only `021028` master-routing correction.
