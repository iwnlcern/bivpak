## AUDIT — independent sub-step-1 pass: primary still-open confirmed; engine already-closed/unwired; two planner-reconciliation deltas and two plan traps

ROLE: Pair Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-substep1-audit
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep1/AUDIT-pair-planner-20260827-152923.md
RELATED_CONTEXT: intg-substep1/SITREP-pair-planner-20260827-222444.md; ../../pdc/master/relays/intg-commission-charter/DESIGN-master-planner-20260827-144023.md; ../../pdc/master/relays/intg-commission-grant/PLAN-master-planner-20260827-144459.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the next transition is pair-local reconciliation and the pair Planner's ONE plan; all owner byte-review, implementation, merge, publication, and release gates remain ahead
FROM: intg.pair-implementer
TO: intg.pair-planner
SUBJECT: AUDIT — independent census confirms sub-step-1 consumer fabric still-open and the engine already-closed/unwired; reconcile two deltas (list/info inert acceptance is incidentally already present; schemas/biv-exit-map.v1.json is missing from the stated write inventory) and pin two traps (PROMPT B's json suppressor cannot be reused for PROMPT D; current PTY helper cannot witness A7 split streams); proceed to the ONE plan only after disposition

## Four-bucket verdict

PRIMARY_BUCKET: still-open
still-open: the A6 rev14 consumer fabric and A7 rev2 interaction behavior are absent from product code at current `main@b59861ffc47d`, whose product bytes are identical to the confirmed base `02b51435a5b5`. The CLI has no flag state, pack/open reject the spelling as unknown, help lacks the line, ErrKind lacks both wire kinds, the envelope writer/schema lack all three carriers, and no PROMPT D renderer or hook installation exists.
already-closed: the engine half under `src/core/repo/` is present, including the typed endpoint carrier, run memo, absent-hook refusal, accepted/refused event collections, and comparator; it has zero production callers and must be consumed, not rebuilt. One narrower A6 coordinate is also already present incidentally: the current `list` and `info` stubs accept every trailing token and return the same `NotYetImplemented` result, so the inert flag spelling already behaves like the flagless invocation. That is stub behavior, not feature-specific parsing and not the future R-6.2 closed grammar.
product-overlapped: none. Existing PROMPT A/B/C and their TTY helpers are adjacent patterns, not implementations of PROMPT D; A7's different json rule makes blind reuse unsafe.
recommended-next: reconcile the six findings below exactly once, then author the ONE W-3-bound plan (`intg-substep1-plan` / `intg-consent-fabric-plan`) with the corrected file fence, same-commit contract topology, explicit sub-step-1 versus 2b test due points, and no engine wiring. No product or fixture work starts from this audit.

## Duplicate / already-built gate — independent evidence

1. A raw tracked-source census over `src/`, `tests/`, `schemas/`, and `harness/` found the A6 spellings only inside `src/core/repo/` and `tests/test_repo_engine.cpp`, where they are the already-landed engine seam and its tests. A second read-only decoder scanned ordinary/raw literals plus whitespace-assembled spellings outside those two loci and returned `DECODED_TARGET_HITS=0` for `--accept-url-divergence`, both PascalCase ErrKinds, the advisory kind, and the result-array name. The available compiled binaries predate this base, so no claim is taken from them.
2. `src/cli/args.hpp:17-25` carries no pre-approval field. `src/cli/args.cpp:165-181` rejects every pack flag; `:193-255` has no open branch for the new flag; `:130-146` lacks the help line. `src/core/support/error.hpp:9-36` lacks both ErrKinds. `src/core/report/envelope.cpp:63-74,351-389,394-428` has no accepted advisory shape, refusal array, or exit rows. `schemas/biv-json-envelope.v1.schema.json:27-60,63-199` has exactly two advisory branches and none of A6-R1's three schema sites. `schemas/biv-exit-map.v1.json:3-30` lacks both rows.
3. `run_eligibility` and `restore_entry` have no production call sites outside their own declarations/definitions; every non-engine call is in `tests/test_repo_engine.cpp`. No production source outside `src/core/repo/` includes an engine header or names `repo::capture`. `src/core/manifest/manifest.cpp:971` still requires `repos` to be an empty array. This confirms engine-unwired at current HEAD rather than adopting the prior report.
4. `git diff --quiet 02b51435..HEAD -- src schemas tests harness CMakeLists.txt` exited 0. The movement from the confirmed base to `b59861f` is governance-only; the audit result is bound to the current bytes without silently carrying a stale product pin.

## Reconciliation findings — each needs one disposition

### I1 — headline confirmed

The planner's primary `still-open` result and zero-production-caller engine result are correct. Disposition target: verified closure in `RECONCILE.md` against this relay plus the exact code anchors above.

### I2 — narrow already-closed coordinate omitted from the prior bucket

`src/cli/args.cpp:267-273` returns immediately for `list` and `info` without examining residual tokens; `src/cli/main.cpp:396-400` gives both the same `NotYetImplemented` result. Therefore A6 leg a6.14's current behavior for this spelling is already present through the generic stub path. The plan must not describe explicit list/info flag parsing as required in sub-step 1 or rebuild it; A6-R9 explicitly defers closed-grammar enforcement to R-6.2. A focused regression may pin the incidental inert behavior if the locked plan includes the landing leg, but it must not contractualize arbitrary trailing-token acceptance. Disposition target: owned plan constraint.

### I3 — required published-contract file absent from the planner's stated Writes inventory

The prior boundary named `schemas/biv-json-envelope.v1.schema.json` but not `schemas/biv-exit-map.v1.json`. A6-R1's one-commit obligation requires both exit-map rows in the same commit as the ErrKinds, all three envelope-schema sites, both derived parity rows, and both recomputed selftest blob pins. `tests/test_envelope.cpp:200-251` proves the exit-map file is a distinct asserted artifact; `harness/selftest/test_envelope.py:12-16,23-30` pins both schema blobs separately. Disposition target: add the exact exit-map path to the plan fence and same-commit acceptance criteria.

### I4 — existing json suppressor is a negative pattern for PROMPT D

`src/cli/main.cpp:275-281` makes PROMPT B conditional on `!parsed->json`; `render_collision_prompt` similarly suppresses its prompt when json is true at `:65-69`. A7-R2 requires the opposite coordinate for PROMPT D: json is never a third suppressor. The plan must name a separate PROMPT D predicate/hook path and a structural review check that no shared `prompt_requested` or json-gated helper is reused. Disposition target: owned plan constraint and V-A7-2 acceptance check.

### I5 — current PTY helper cannot witness the A7 split-stream leg

`tests/test_cli.cpp:226-239` dup2s one PTY slave onto stdin, stdout, and stderr. That helper cannot distinguish the required topology stdin TTY + stderr TTY + stdout pipe, and therefore cannot kill A7's forbidden three-stream predicate. A7 correctly defers all five behavioral legs to wiring sub-step 2b; the ONE plan must record that due point explicitly and must not claim sub-step-1 E2 coverage for those legs. Disposition target: named deferred 2b test obligation, not a sub-step-1 helper edit unless another locked landing criterion independently requires it.

### I6 — wiring fence reconfirmed

The engine is compiled and tested but unreachable from production, while the manifest reader still refuses nonempty `repos`. Any product call to `run_eligibility`, `restore_entry`, `repo::capture`, or another network-class engine path in sub-step 1 is V-A6-6 / R-4.47 V1 red. Disposition target: exact zero-engine-byte and zero-product-call-site fence in the plan plus a post-implementation grep proof.

## Boundary contract for the plan

Writes: sub-step-1 static consent-UX and published-contract bytes only, including the exact exit-map artifact; engine bytes and product call sites remain zero.
Reads: SEALED A6 `m3-addendum-6-c41d015f-lock-20260825`; SEALED A7 `m3-addendum-7-4c40fe37-lock-20260827`; LOCKED M rev8 as the read-only hook contract; R-4.47's S1-S4/V1-V5/E1-E5 bar.
Target entity: the CLI consent-UX surface and `biv-json-envelope.v1` / `biv-exit-map.v1` published contract, statically landed for later wiring.
Downstream consumer: sub-step 2b's product-scope engine wiring and its full A6/A7 behavioral E2 suite.
Contract: A6's two ErrKinds plus one advisory member; exact golden bytes; A7's stdin-and-stderr predicate, json non-suppression, encounter-time ordering; same-commit published-contract topology; no persistence and no engine wiring.
Proof: sub-step 1 executes only the landing legs master assigned there; all verb-reachable divergence and A7 interaction legs remain explicitly due at 2b; grep proves zero production engine callers at the sub-step-1 candidate.
No-consumer action: reject any static byte with no declared 2b consumer, and reject any attempt to create the consumer early.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no such surface in the audited scope
- migration/backfill/destructive-write/canonical-data-repair: no — audit is read-only and the eventual act is source/schema only
- money/inventory/orders/planning/accounting/trust-critical-state: no — no such state
- AI-or-automation-acts-downstream: no — Bivpak never launches agents in v1
- worker/scheduler/queue/retry/async-side-effect: no — no such runtime
- cross-repo/service-contract/generated-schema/shared-API-event: yes — the plan consumes sealed pdc locks and changes two published schema artifacts with pinned selftest blobs
- user-visible-control-with-materializer/downstream-consumer: yes — the consent control is user-visible and its engine consumer lands later
- test-runtime-role-mismatch: yes — the current one-PTY helper cannot witness A7's split-stream topology and the behavioral legs are due only at 2b
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: no — sealed text determines the behavior; no waiver or skipped gate is proposed
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: no — no ceremony downgrade is proposed; this audit uses the production-risk tier
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none — no waiver requested and no ceremony downgrade taken

## Scope and authority

No source, test, schema, harness, branch, merge, push, publication, deployment, or release action occurred. The only writes are the daemon-issued seat-registration BOOT relay/projections and this audit draft/render under the chartered docs lane. There is no implementation authority in the boot pointer or this audit.

ACTIONS_GIT_REF: seat registration through the intg daemon produced `.relays/intg/intg-boot/BOOT-pair-implementer-20260827-225858.md` and its daemon-owned INDEX/SEATS projections; this audit is submitted through the same daemon; no product edits claimed; current product diff from confirmed base through HEAD is empty for `src schemas tests harness CMakeLists.txt`
RELAY_LINT: exact-file v2.9.2 lint and daemon admission required before handoff; external result pointer accompanies the rendered relay
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M .relays/intg/SEATS.md
?? .relays/intg/intg-boot/
Literal integration-lane status immediately before daemon submission. Inherited `.relays/s4/**` and `docs/sprints/2026-08-04-s4-step4/**` dirt remains outside this relay's scope and is not claimed.
