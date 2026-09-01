## IMPL STOP RETURN — Tasks 1 and 2 are reviewed green; Task 3 reached its one symmetric commit and full macOS floor green, then independent review fired S-FA-1/S-FA-2 before Task 4: the carrier admits host-absolute schema-path values and otherwise invalid state combinations, while `serialize(const Manifest&) -> std::string` has no sealed invalid-carrier disposition; H also leaves the `local_refs_bundle` interaction outside its exact four-field discriminator — HOLD at `9e6ebe8`, no local mapping or fix, route to the owning schema seat

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-return
PARENT_DISPATCH_ID: intg-substep2a-impl
IN_REPLY_TO: intg-substep2a/PLAN-pair-planner-20260901-012635.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-planner-20260831-030859.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260831-025316.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/domains/m-1-format-engine/design/2026-08-26-ADDENDUM-N-shallow-payload-only-cell.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — S-FA-1/S-FA-2 and the generic defer-or-silence rule fired at Task 3 review; the schema owner must determine the invalid-carrier writer contract, the host-absolute rejection surface, and the H/local_refs_bundle composition before any fix, Task 4, byte-review submission, merge, push, or release act; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-N-82293732-lock-20260827
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 57ab3b9ba15c5674dae5b42dc3a3c48252e844f8e3d863d0cb1f3682c33b4a4b
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act@9e6ebe8fca2454164051573323dd7adfa2901219 in /Users/jack/Programming/bivpak-intg-format-act; clean; seven-path branch diff; NOT a submitted V-FA candidate while this STOP is open
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer
SUBJECT: STOP UP — Task 3 independent review found a real RepoEntry↔schema/serializer seam the sealed texts do not dispose: schema-carried path members accept and emit host absolutes; the writer can emit state the parser rejects; the current string-returning serializer cannot return a typed invalid-carrier result; H's exact discriminator omits local_refs_bundle. Tasks 1-2 stand reviewed green; Task 3's one commit and green receipts are retained, but no fix or Task 4 proceeds pending owner ruling

## Stop point and unchanged authority boundary

The `012635` resume was consumed under the standing bare token `030859` and exact plan digest `57ab3b9b…`. Work executed only in the named isolated worktree and only across the plan's seven authorized paths. Task 1 and Task 2 completed their TDD and independent task-review loops cleanly. Task 3 landed the carrier, writer, parser, round-trip witness, and fence retirement in the required ONE symmetric commit, then passed its focused and full macOS floors. Its independent task review found two blocking contract gaps and four additional defects before Task 4 began.

The generic defer-or-silence rule and S-FA-1/S-FA-2 therefore fire. No local validation rule, normalization, omission behavior, assertion, serializer API change, or H discriminator amendment has been invented. No Task 4 census, Linux leg, m-1 candidate submission, merge, push, PR, remote CI, publication, deployment, seal, or release act occurred.

The branch remains clean at `9e6ebe8fca2454164051573323dd7adfa2901219`. It is retained for inspection and forward correction; it is NOT claimed byte-review-ready or merge-ready.

## Work completed before the STOP

```text
815677a  Task 1 classifier lattice, boundary-only Shallow, shallow bundle/ref suppression
3618069  Task 1 review fix: born-shallow payload-only invariant assertions
363d812  Task 2 shallow_pointer before payload_only_unborn + empty request-trace witness
9e6ebe8  Task 3 ONE symmetric commit: Manifest.repos carrier + writer + parser +
         populated/hostile tests + require_empty_array("repos") retirement
```

Task 1 TDD/review receipts:

- RED: all four new real-source arms failed before production edits because the old classifier returned before or probed after shallow detection.
- GREEN: focused four arms, then full `biv_repo_engine_tests`; after the review's one assertion gap was fixed and scoped re-reviewed, `451 assertions / 60 cases` green.
- Final task review state: clean; no open Critical/Important/Minor.

Task 2 TDD/review receipts:

- RED: shallow×unborn returned enum value 2 (`payload_only_unborn`) and no boundary.
- GREEN: focused two-arm witness `13 assertions / 1 case`; full `biv_repo_engine_tests` `452 assertions / 60 cases`.
- Independent task review: APPROVED, no findings.

Task 3 TDD/verification receipts:

- compile RED before the carrier: missing `biv::repo`/`Manifest.repos` surface.
- behavior RED after carrier only: `8 cases`, `7 failed`, old empty-array fence and zero parsed rows observed.
- UnknownNote verbatim RED: the initial implementation minified interior whitespace; source-slice binding corrected it.
- focused GREEN: `276 assertions / 8 cases`.
- full GREEN at exact commit bytes: aggregate `biv_tests` `15,060 assertions / 407 cases` (`404 passed`, `3 declared skips`); full `biv_repo_engine_tests` `452 assertions / 60 cases`.
- `git diff --check 46df8f3..9e6ebe8` clean; exact changed-path set is the seven authorized paths.

The macOS invocations used the standing value-free `env -u ANTHROPIC_API_KEY`; its value was never inspected or recorded. The owner-disclosed `open-unknown-agent` baseline class was not encountered in these focused/full binary invocations.

## Blocking findings — verified at the committed bytes

### B1 — S-FA-1: host-absolute schema-path carriers and no determined writer refusal

`RepoEntry` carries unconstrained path-bearing values (`relpath`, capture patch paths, `payload_prefix`, forced-payload paths, local-ref bundle, repo bundle). Task 3's writer emits those values directly; its parser constructs path values directly. A constructed entry containing an absolute carried path therefore serializes that host path, and a hostile manifest can parse one.

V-FA-3/V-M-INT-1 says host-absolute paths are never serialized, but §2.3+G+H+N does not specify the invalid-carrier disposition at this API seam. The current function is `std::string serialize(const Manifest&)`; it cannot return the existing typed `BivError` without an API change. Omitting, rewriting, relativizing, throwing, asserting, or changing the API are materially different contracts. This is exactly S-FA-1's RepoEntry↔schema mismatch/defer class. No choice was made locally.

The original transient-state test proved only that `promisor`, `engine_source`, and the absolute paths inside `engine_source` stay absent; it did not exercise absolute values in schema-carried path fields.

### B2 — S-FA-1/S-FA-2: writer accepts states the parser refuses

The writer emits carrier values directly while the parser enforces semantic invariants. Concrete committed examples:

- `entry.sha` is emitted independently of `head_state`, while the parser requires null iff unborn and 40-hex when born.
- shallow rows still emit any engaged eligibility, non-empty `local_refs`, `local_refs_bundle`, or bundle from the carrier, while the parser rejects all of them under N-R2.
- the writer's absence predicate can omit `capture_mode` based on an invalid carrier state that its parser later rejects.

Thus `parse(serialize(manifest))` is not symmetric for admitted in-memory states. The plan calls asymmetry V-FA-2 red, but the sealed texts do not say whether the writer validates, normalizes, refuses, or relies on a separately proven carrier-validity precondition. State combinations involving capture/eligibility also meet S-FA-2's literal serializer-encounter trigger. No local fix was dispatched.

## Additional review findings retained behind the STOP

1. UnknownNote forward placeholder replacement can corrupt bytes when an earlier valid unknown note contains the quoted placeholder token assigned to a later note. Replacements need collision-safe positional handling or an authorized raw-JSON writer route, plus a two-note sentinel-collision arm.
2. The populated DOM witness checks top-level row sets and only some nested sets. It lacks exact member/cardinality/distinct-value assertions for `remotes[]`, `local_refs[]`, `forced_payload[]`, `shallow`, and structured notes, so an extra nested writer field could escape the mandatory witness.
3. `parse_local_refs` aliases an absent member to empty for every row. G/H explicitly license absent-or-empty for payload-only unborn, so unconditional presence is NOT the correction; a presence-aware outside-class check is the actual gap if the owner confirms §2.3 requires the array elsewhere.
4. The H absence predicate ignores `local_refs_bundle`. H normatively names an exact four-field discriminator (`head_state`, no bundle, no eligibility, local_refs absent-or-empty) and does not name `local_refs_bundle`. Adding it locally would amend H. Whether a marker-free unborn row carrying only `local_refs_bundle` is separately invalid is routed as an S-FA-1 question.
5. The ignored Task 3 worker report's nested-field summary uses obsolete names (`remote_name`, `remote_url`, `refname`, `resolved_sha`, `relpath`) although committed code uses the sealed spellings (`remote`, `url`, `ref`, `tip_sha`, `path`). This evidence text must be corrected before final reporting.

One reviewer suggestion is NOT adopted: requiring `sparse` to be present. Sealed §2.3 states `sparse` stays null/absent in v1. The writer's `sparse:null` emission remains required, but parser acceptance of absence is not itself a defect.

## Exact asks to the owner chain

1. **Invalid writer carrier:** choose the contract for a `RepoEntry` that cannot be represented without violating §2.3/V-M-INT-1. Is carrier validity a proven precondition; must `serialize` become typed/fallible; or is another exact refusal mechanism sealed? State the writer-side witness required.
2. **Host-absolute scope:** enumerate which `repos[]` schema-carried fields must reject absolute values and the exact archive-relative/path-normalization predicate. The pair will not infer it from C++ path types.
3. **H composition:** rule whether `local_refs_bundle` participates in payload-only-unborn validity outside N's shallow marker, without silently changing H's exact four-field discriminator.
4. **Symmetry scope:** confirm whether writer/parser symmetry covers every constructible `RepoEntry` or only a separately validated subset; if subset, name and mechanically witness the validator/precondition.
5. **Resume:** after the above, authorize the smallest forward correction at the retained branch. The pair will then fix the mechanically determined remaining findings, re-run the scoped review loop, and only after Task 3 is clean begin Task 4.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no permission or credential value touched; standing value-free sanitation only
- migration/backfill/destructive-write/canonical-data-repair: no — no data mutation or destructive act
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — parse-reach only, zero product caller intended
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC §2.3+G+H+N and the public manifest writer/parser contract govern the disputed seam
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and future restore behavior are user-visible, though 2b wiring remains absent
- test-runtime-role-mismatch: yes — Task 4's Linux parity leg has not run because the STOP precedes it
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — invalid-carrier handling and H composition are not determined locally
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: not applicable to these product/schema findings — W-4 covers only the named structural lineage-red partition
- valid_waiver: no

ACTIONS_GIT_REF: product work retained only on intg/format-act through 9e6ebe8; this STOP report via the engine from the primary docs lane; no product amendment after the review, no Task 4, no byte-review submission, no merge/push/PR/remote-CI/publication/deployment/seal/release
RELAY_LINT: to be engine-rendered; exact-file lint and verify follow submission
FINAL_GIT_STATUS_SHORT:
 ?? .superpowers/relay-drafts/IMPL-TASK3-STOP-UP-SCHEMA-SEAM.md
Literal path-scoped status for this seat's own write at authoring time. The primary checkout separately retains inherited S4 relay/docs state, untouched and not claimed clean; the isolated intg/format-act worktree is clean at 9e6ebe8.
