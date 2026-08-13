## PLAN-REVIEW — successor pin and cap predicate pass, but the executable fatal carrier and the key-1a checkpoint remain contradictory; MUST-REVISE on two bounded points

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-plan-review-successor
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — W-1 is effective and the exact successor lock is VP-approved; these are local execution-plan corrections before any delegated implementation token
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-29A5B3A3-CAP-OUTSIDE-A1241-BY-PREDICATE-20260812-212557.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV2-MUST-REVISE-STAGE0-CAP-REENTRY-20260812-164019.md; .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-MUST-REVISE-EXACT-STAGE0-SCOPE-KEY2-CONTROL-20260812-165204.md; ../pdc/master/relays/s4-build-standup/DESIGN-REVIEW-ORCHESTRATOR-REVIEWER-ADDENDUM12-SUCCESSOR-LOCK-APPROVE-A124-PREDICATE-20260812-191415.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: MUST-REVISE successor Slice E PLAN — bind the J fatal to exact BivError/CLI fields and make the combined-tree checkpoint agree that key 1a is already creditable at Stage 0

PLAN_REVIEW_VERDICT: must-revise

The successor does the difficult semantic work correctly. I independently re-derived the locked Addendum-12
blob as `29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb`, live post-stamp as
`d0e2c6eba6047c3b7185339f1699ee13ac912d1545e08d60dbf40bbbdca4a42b`, and J as
`94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18`. The target-to-stamp diff is
one head-region hunk, 49 insertions / 12 deletions. The `191415` VP approval names the exact lock, full target
hash, and full target commit. W-1 is recorded CONCURRED/EFFECTIVE at `211308`. `origin/main` remains
`0db8fdd8424d27aad2c547614e9ebb95621a2794`, with no `parent_id` under `src/core/manifest`; Stage 1 is
correctly held on the m-1 receipt.

The cap reading also passes: a whole-entry refusal is outside `A12.4.1` by the emitted-result predicate;
`A12.4.2` points to J's loud typed refusal; no dead warning line is owed; the third killing arm preserves the
warning obligation for a genuine omission or alteration inside a result that is emitted. The exact six-path
Stage 0, key-2 GREEN/dependency stop, atomic key 5, coupled Stage 1, A3 same-head checks, local Ubuntu
24.04 `linux/amd64` Docker signal, and remote-Actions hold all stand.

## R1 — the plan does not select an executable typed-fatal carrier or CLI oracle

The plan requires the cap refusal to be typed and name both the offending entry and cap, but never binds
that requirement to the current error surface. At `0db8fdd`, `BivError` is exactly
`{kind, path, detail, err_no, facts}`. Text-mode `biv pack` prints only `kind` plus `detail`; JSON emits
`kind`, `path`, `detail`, `errno`, and `facts`. The scoped production list contains `pack.cpp` but excludes
`error.hpp`, `error.cpp`, `envelope.cpp`, `main.cpp`, and `exit_map.hpp`. Therefore an implementer still has
to choose among materially different outcomes during the build:

- reuse an existing `ErrKind` or add a new typed kind;
- place the entry and cap in `path`, `detail`, named `facts`, or duplicated fields;
- assert text output, JSON output, or only an in-process `BivError`;
- inherit an existing exit class or widen the report/CLI scope to define another one.

That is the exact carrier decision rev2 required to re-enter the reviewed successor PLAN; “typed fatal
naming entry and cap” states the semantic result but does not make it executable against this repository.

Required revision: name the selected `ErrKind`, exact `BivError` field mapping for **entry** and **cap**, the
expected exit class, and the exact in-process plus actual-CLI assertions that prove both names survive to an
operator-visible refusal. Name every production and test path needed. If the choice requires a new error
kind or a CLI/report change, route the scope/design delta rather than silently widening beyond the current
four-file production list. Keep the existing killing arms: omission of either name fails; any truncated or
whole over-cap emission fails; and emitted partial success without its required warning fails.

## R2 — the combined-tree checkpoint contradicts the plan's valid Stage-0 credit for key 1a

Section 2 says the post-m-1 combined tree is the **first** point at which keys `1a`, `1b`, key 2's absence
arm, `4a`, `5`, and E2E are creditable. Section 3 then correctly places key `1a` in Stage 0 and requires its
assertion-level RED at `0db8fdd` before the rebase. Both cannot govern. Key `1a` is the schema-independent
collector-carriage failure and is intentionally one of the four Stage-0 behavioral REDs; only `1b`, key 2's
second GREEN arm, `4a`, `5`, and the schema-dependent E2E wait for the m-1 combined tree.

Required revision: remove `1a` from the combined-tree-first list and state the checkpoints once, consistently:
Stage-0 REDs `1a/3/4/6` plus controls at `0db8fdd`; post-rebase key-2 arm 2 GREEN plus REDs `1b/4a/5`;
then Stage 1 and the actual-binary E2E. Preserve the no-compile-failure-credit rule and the dependency stop.

## Gate result

This is a bounded PLAN correction, not a design reopening. The exact successor design pin, W-1 property,
cap predicate, six-path Stage 0, key-2 classification, and m-1 stop remain accepted. The local PLAN gate is
red until R1 and R2 enter one successor and receive review. No Stage-0 dispatch and no Stage-1 token follows
from this verdict. No product, fixture, schema, harness, branch, PR, GitHub Actions, merge, seal,
publication, deployment, or release action is authorized; the release hold remains ABSOLUTE.

ACTIONS_GIT_REF: review-only — read and re-hashed the exact Addendum-12/J bytes, read the VP approval and W-1 closure, inspected the live BivError/text/JSON/exit surfaces and the incoming checkpoint matrix, and re-measured the absent m-1 receipt at origin/main 0db8fdd; this relay and its append-only INDEX row are the only writes from this act
RELAY_LINT: per D-3.4 — exact-file freshness lint before filing; INDEX tail re-read immediately before append; exact-file no-freshness and `--index` after append; active-root structural result disclosed separately and never claimed green under W-1
FINAL_GIT_STATUS_SHORT: not claimed clean — the shared checkout contains pre-existing sibling untracked files; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-MUST-REVISE-CARRIER-CHECKPOINT-20260812-213906.md` -> `s4-floor.planner`
- MUST-REVISE R1: select the exact BivError kind, entry/cap fields, exit class, operator-visible CLI assertions, and complete scope
- MUST-REVISE R2: key `1a` is creditable at Stage 0; only the schema-dependent arms wait for the combined tree
- successor pin, W-1, cap predicate, six-path Stage 0, key-2 GREEN stop, coupled Stage 1, A3, Docker parity, and Actions hold otherwise stand; no token or later gate; release hold ABSOLUTE
