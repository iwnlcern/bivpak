## PLAN REVIEW rev0 — the ledger is complete, but the act boundary, integration order, scope, and interfaces are not executable as locked

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-arm1-plan-review-rev0
PARENT_DISPATCH_ID: s4-matrix-arm1-plan
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — the semantic corrections are locally decidable; delegated dispatch remains held, and the relay-root lint blocker must be remediated or dispositioned by the authorized seat before any token
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
PLAN_REVIEW_VERDICT: must-revise
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-20260806-001618.md
RELAY_PATH: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV0-20260806-002313.md
BASE: 5b3c603b5335de356b6509a2882fee25f43f9945
SUBJECT: MUST-REVISE rev0 — restore the one-head four-surface schema act, remove producer-before-consumer state, close scope and interface gaps, and define an executable branch/PR chain

## Review basis

- Plan doc: `docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md`, SHA-256 `33bfa801616b276023c71a7d49bfbcd909bed94db7fd39315813bd6948909c4b`.
- Frozen ledger: `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md`, SHA-256 `229e7e6c0b8aa78f9d39fc9b0c2b25c5ba7faf062a8bb27e8dfef16bb65fb8a3`.
- Review request: `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-20260806-001618.md`, SHA-256 `c793fa2cccb5f1fba8a673a8a068c7971aa31a9e92cae552d68c467a6377285d`.
- Filing commit: `5b3c603b5335de356b6509a2882fee25f43f9945`; all three reviewed paths remain byte-identical at current HEAD.
- Design lock: approved rev4 blob `802b8499…f878c8` at `934fca3`; parent review `s4-matrix-design-review-rev4`; governing G pin unchanged.

Addressing, unique pair-PLAN id, design-review parent, F carve-out, merge hold, exact-file relay lint,
and immutable plan/ledger bytes pass. The following revisions are required before delegated dispatch.

## Required revisions

### R1 — T5 is not the locked four-surface schema act, and T6 creates the forbidden producer-without-consumer head

Design D3.3 requires `read_archive_plan` and `apply_archive` to admit and account for the
`repos/<id>/…` member family in the same four-surface act as parser/model-writer and
envelope/oracle (`design:104-120`); criterion 3 and D10 make that one reviewed act binding.
T5 claims all four surfaces but omits `src/core/open/open.{hpp,cpp}` and its member-namespace
tests (`plan:180-190`); those edits first appear in T7 (`plan:204-212`).

The resulting order is also unsafe: T6 wires pack before T7 wires open, then asserts that
T5 makes open able to read the emitted image (`plan:192-202`). T5 as written neither admits
the `repos/` family nor materializes its entries, so a T6 head can emit an image the same
head cannot restore. That contradicts the global no-half-fix guard (`plan:20`).

Required correction: put D3.3's namespace admission/accounting and its exact tests in T5's
same reviewed head. Then order the open consumer before the pack producer, or make T6/T7
one reviewed integration head, so no landed head writes a repo-bearing image without the
complete reader/materializer. Preserve the F fence over the entire corrected act/integration chain.

### R2 — mandatory ledger/report/ROADMAP writes are outside the locked file universe

The ledger itself says each status moves `FROZEN → DONE` as tasks land (`ledger:6`), and T5
explicitly requires ledger rows moved to DONE (`plan:190`), but the ledger path appears in
no task `Files:` block. T8 also requires `ROADMAP` updated (`plan:222`) without naming the
ROADMAP path. The protocol-required file-first implementation report and append-only INDEX
row have no bounded path in the plan at all. A truthful per-wave SCOPE_DIFF must mark each
such write OUT.

Required correction: add the exact ledger path to every task that advances its owned rows,
bounded to status-only transitions; either add the exact ROADMAP path with its authorized
update semantics or remove/reroute that acceptance item; and authorize one dedicated
matrix implementation-report directory plus `.relays/s4/INDEX.md` append-at-EOF only.
No broad `.relays/s4/**` wildcard is acceptable.

### R3 — T5 changes the locked D5 membership from nine kinds to eight

T5 says `ErrKind` gains “the D5.1 eight kinds” (`plan:184`). The locked design's exact,
PLAN-may-not-change table contains NINE rows (`design:175-196`):
`RepoDirtyUnsupported`, `RepoNestedUnsupported`, `RepoSubmoduleUnsupported`,
`MemberAncestryUnsafe`, `UnmergedIndexUnrepresentable`, `RefUncapturable`,
`PromisorObjectsUnavailable`, `GitInvocationFailed`, and `RepoRestoreFailed`.

Required correction: enumerate all nine names, fact shapes, phase/exit families, envelope
and exit-map rows in T5; keep the three reused landed kinds and the retired
`RepoDiscoveredUnsupported` treatment separate. Add a test that asserts the exact set and
closed row count so the mismatch cannot survive prose.

### R4 — T1's runner interface cannot preserve the existing probe stream contract

The current probe duplicates stdout and stderr into ONE pipe at spawn
(`probe.cpp:669-703`) and has an untouched test for merged output
(`test_probe.cpp:312-323`). The locked design requires separate generic streams while the
probe remains a thin adapter with its contract unchanged. T1's `SpawnRequest` exposes only
separate streams and T1.5 says the adapter will merge them afterward (`plan:68-95`).
Post-capture concatenation cannot preserve source interleaving. The interface also makes
generic stderr a sanitized `std::string`, despite D1.1's byte-exact generic capture bar.

Required correction: give `run_argv` an explicit spawn-time stderr-to-stdout topology used
by the probe adapter, while git uses separate pipes; expose byte-exact generic stderr
capture and sanitize only at the adapter/diagnostic consumer. Test both topologies, retain
all existing probe tests untouched, and keep one `posix_spawn` implementation.

### R5 — the T2 boundary types do not encode two locked invariants

`RepoEntry`'s sketched interface does not make `eligibility` optional (`plan:107-117`),
yet ZERO-REF unborn entries MUST carry no eligibility object and T4 tests exactly that.
Also, `Git::run(std::span<const std::string>)` has no typed operand boundary with which the
wrapper can enforce D1.1's `--`-before-pathish/URL-ish policy (`plan:119-135`).

Required correction: freeze `eligibility` as an optional value in the cross-task type,
with parser/writer tests for presence and absence; and make delimiter ownership mechanical
(typed git operations that insert it, or an explicit caller contract with assertions and
tests at every pathish/URL-ish operation). Do not leave either rule as prose beside an
interface that cannot enforce it.

### R6 — dependent task branches have no executable PR/rebase topology

The plan says every task branch starts from `main` (`plan:24`) while T2 consumes T1, T4
consumes T1/T2, and T5-T8 consume their predecessors. It gives commit steps but no PR,
predecessor-base, restack/rebase, implementation-report, or wait-for-operator-merge steps.
With merge authority expressly absent, independently branching all tasks from the same
main cannot satisfy those interfaces.

Required correction: choose and lock one topology: stacked task branches with explicit
predecessor bases/restack rules, or strictly serial branches created only after each
operator-authorized merge and main catch-up. Name PR targets, per-head verification,
file-first implementation reports, rebase-before-land for shared files, and the stop rule
when a predecessor is not merged/reachable. Preserve per-wave F gating and operator-only merge.

## Ledger and grading disposition

The FROZEN ledger's CONTENT passes: 8 flip, 8 retain, 12 add, and 3 green-side rows match
the planner F1-F7/C1-C9 inventory, the Implementer retentions and coverage gaps, and the
fifteen pinned FX-G-1 legs. Every flip names a replacement oracle and every retain gives a
survival reason. R2 concerns the missing status-maintenance scope, not row completeness.

Design trace grade: D2/D4/D5 behavior and the Wave-A no-product-wiring concept are
substantially represented; D3/D10 FAIL on R1; exact D5 membership FAILS on R3; D1 interface
closure FAILS on R4/R5; D7/SCOPE_DIFF executability FAILS on R2; delivery topology FAILS on R6.
The boundary contract, out-of-scope behavior, F landing gate, and absolute merge/release
holds otherwise remain correctly stated.

## Mechanical dispatch blocker

The incoming relay is exact-file lint-clean. Full `.relays/s4` lineage lint is red on
historical INDEX/floor scars and additionally reports this PLAN's valid repo-relative
`DESIGN_LOCK_ID` as a missing file. That matrix-specific resolver result must be remediated
or receive an explicit authorized named-error disposition before any delegated token;
an exact-file pass does not substitute for the available lineage gate.

## Verdict

MUST-REVISE

Revise the same plan and frozen ledger for R1-R6, preserve their immutable baseline rows,
and request a fresh PLAN-REVIEW. No implementation token may issue from this verdict.

ACTIONS_GIT_REF: docs-lane review writes only — .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV0-20260806-002313.md and its append-only .relays/s4/INDEX.md row; explicit paths only; carrying commit in repository record; no product, test, harness, schema, plan-doc, ledger, design-doc, branch, PR, push, merge, seal, or release action
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-REV0-20260806-002313.md

RELAY_LINT: OK — author-side freshness lint, shared INDEX lint, and git diff --check

## Next action

Planner: fold R1-R6, keep Wave A non-wiring and Waves B-D F-fenced, route the lineage-lint
resolver blocker, and re-request review. SCOPE_DIFF and delegated dispatch remain held.
