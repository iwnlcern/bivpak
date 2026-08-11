## AUDIT (slice E, implementer half — read-only) — `R<-P<-C` loss and the one-level identity coupling are source-confirmed at `0db8fdd`; a real CLI restore E2E is absent

ROLE: Implementer
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-slice-e-audit-implementer
PARENT_DISPATCH_ID: s4-slice-e-audit
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — read-only audit inside the existing Step 4 gate. Any manifest child-shape change remains outside this seat and routes UP.
DESIGN_LOCK_ID: pending — m-2 owns the R-4.18 design predicate
DESIGN_RECORD_KIND: design-doc
IN_REPLY_TO: .relays/s4/s4-floor-impl/AUDIT-ORCHESTRATOR-PLANNER-SLICE-E-OPEN-R418-CHAIN-DROP-COUPLED-IDENTITY-GATE-REAL-E2E-20260811-063138.md
FROM: s4-floor.implementer
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.planner, master.orchestrator-planner, m-2.planner
SUBJECT: AUDIT (implementer half) — R-4.18 source path and coupled gates confirmed; warning transport distinguished from missing producer; manifest seam conditional; real disposable-store CLI E2E scoped

## 1. Executive result and four-bucket disposition

PRIMARY_BUCKET: still-open

- `still-open`: Codex collection loses the third node of `R<-P<-C`. Both descendants are classified as children, only the root is emitted, and `session_for(root, direct_children)` never consumes the grandchild list attached to the intermediate parent.
- `still-open`: both write-time and staged-read identity gates model one installed thread identity. A real leaf whose `session_id` names the chain root while `parent_thread_id` names the immediate parent cannot pass that model after the dropped leaf is made visible.
- `still-open`: no test drives the shipped `biv pack` then `biv open` binary over a genuine subagent-bearing fixture and proves the restored parent reference resolves to a readable child file.
- `already-closed`: R-4.15 is landed and is not slice E work. Exact-tree search finds no `child_alias_ids`; Claude emits the child identity map, and Codex mints the name used as the rollout destination.
- `product-overlapped`: generic `CollectReport.warnings` transport through pack and CLI already exists; the missing part is a chain-drop producer/policy. CLI E2E isolation and actual-binary helpers already exist in `tests/test_cli.cpp`. Manifest serialization is a conditional shared seam, not a proven mandatory edit.
- `recommended-next`: reconcile this audit with the planner half, let m-2 lock graph/cardinality and failure semantics, route UP only if that decision changes manifest child shape, then issue a bounded PLAN/IMPL dispatch for collector + both identity gates + their killing tests + the disposable-store CLI E2E as one coupled slice.

No product, test, schema, workflow, PR, or branch byte was changed by this audit.

## 2. Exact target and R-4.15 duplicate gate

The dispatched commit is merge `0db8fdd8424d27aad2c547614e9ebb95621a2794`, with tree
`2d47080877eaf9366e416c39b298905cd051aa9e`. The clean B2 candidate worktree at `fd857f1` has the same tree,
so all source and test inspection was tied to the dispatched bytes rather than checkout ancestry.

Exact-tree findings:

```text
git grep child_alias_ids 0db8fdd -- src tests
  -> 0 hits

src/adapters/claude_code/install.cpp:721-723
  -> session.child_ids.push_back({child.original_id, child.original_id})

src/adapters/codex/install.cpp:425-464
  -> each primary/child receives a minted rollout name; that same installed name is used in
     the id map and as the destination filename
```

PRIMARY_BUCKET for R-4.15: already-closed. Do not rebuild it, and do not use its stale residual history to
expand slice E.

## 3. R-4.18 collector path — the drop is deterministic

At `src/adapters/codex/codex.cpp:452-486`, `session_for(candidate, children)` adds the candidate, then loops
exactly once over the supplied direct `children`. There is no recursive walk, descendant closure, or queue.

At `src/adapters/codex/codex.cpp:1294-1310`:

1. every candidate whose parent is present in `winners` enters `child_ids`;
2. the same edge enters `children_by_parent[parent]`;
3. the emission loop skips every id in `child_ids`;
4. only a non-child candidate is emitted, using only `children_by_parent[id]`.

For `R<-P<-C`, P and C are both skipped. R is emitted with P, while `children_by_parent[P] = [C]` is never
read. C's rollout and identity do not reach the packed `SessionRecord`. This is E1 source proof of silent
loss at the exact target.

The existing collection test at `tests/test_adapter_codex_collect.cpp:325-370` proves only root + direct
child + duplicate selection. No relevant depth-three or grandchild collection case exists. The checked-in
Codex store fixture likewise contains only self/direct-parent shapes.

### Warning-channel correction

The dispatch's phrase “no warning channel” is too broad if read as an architecture claim:

- `CollectReport.warnings` already exists;
- `src/core/pack/pack.cpp:557-558` carries adapter warnings through `adapter_warning`;
- `src/core/pack/pack.cpp:334-340,741-768` converts and renders generic warning kinds;
- `src/cli/main.cpp:44-49` emits pack warning text.

What is absent is the chain-drop producer and its locked policy: the collector emits no warning for a
descendant that it classifies as a child but never consumes. Therefore the current behavior is silent, but a
design choosing loud refusal or partial-pack warning can reuse an existing end-to-end transport. This audit
does not choose that policy.

## 4. Coupled identity gates — root and immediate parent cannot share one slot

### Writer/install gate

`src/adapters/codex/install.cpp:425-464` mints mappings per prepared record. `:494-505` adds at most one
in-image parent mapping. At `:540-606`, a primary write with a parent selects one `installed_thread_id` and
requires both of these independent source fields to collapse onto it:

- `session_id` must equal the record's installed id or `installed_thread_id`;
- every `parent_thread_id` must equal `installed_thread_id`.

In a three-level chain, a leaf's `session_id` can map to installed R while its `parent_thread_id` maps to
installed P. Because R and P are distinct, the current single-slot predicate refuses the leaf as
`containment_refused` / `staged_identity_mismatch`. Emitting separate rows does not by itself close the gate:
the leaf row prepares C and immediate P, but has no global installed-root mapping for R.

### Staged-reader gate

`src/adapters/codex/codex.cpp:700-818` independently repeats the one-level model. The main row finds at most
one referenced staged parent. Its direct-child loop at `:763-789` accepts a child `session_id` only as the
child's minted id or the row's minted id, and requires every child parent id to equal the row's minted id.
There is no separate mapped-root and mapped-immediate-parent concept. A mismatch emits
`StagedSessionIdentityMismatch` and skips the row, making “collector only” an invalid repair.

Existing R-5/R-6 and pack tests (`tests/test_adapter_codex_install.cpp:2383-2562` and
`tests/test_pack.cpp:2083-2165`) exercise one-level parent-valued identities and one separately mapped
immediate parent. They do not prove a leaf where mapped root and mapped immediate parent are different.

## 5. Manifest/cardinality boundary — conditional route, not a design decision

Current wire-side shapes:

```text
src/core/manifest/manifest.hpp:43-46
  SessionChild = { original_id, artifacts }       // no edge/parent field

src/core/manifest/manifest.hpp:48-63
  AgentSessionEntry = one original parent + flat children

src/core/pack/pack.cpp:384-433
  SessionRecord.child_ids -> flat SessionChild list

src/core/manifest/manifest.cpp:180-203,305-345
  parse flat children, then agent_sessions entries
```

The source does not prove that a wire-shape change is mandatory. A design could potentially use the existing
flat child list or existing per-entry parent fields. Conversely, if m-2 requires an explicit child edge,
ancestor vector, changed `SessionChild`, or changed `agent_sessions[]` cardinality contract, then the minimum
surface necessarily reaches:

- `src/core/manifest/manifest.hpp`;
- `src/core/manifest/manifest.cpp` — HARD-OUT / fence-2;
- `src/core/pack/pack.cpp`;
- `tests/test_manifest.cpp`.

That branch routes UP for m-1 joint-lock authority. This implementer makes no flatten/promote/schema choice
in AUDIT.

## 6. Real end-user restore E2E — current proof and missing instrument

`tests/test_pack.cpp:1748-1893` is a useful in-process fixture test, not an end-user E2E. It constructs
manifest entries directly, invokes adapter install, and manually scans the destination. It does not run
`biv pack` then `biv open`. Its three synthetic cases cover flat bare-hex, flat slug-hex, and nested bare-hex,
but use the full `agent-...` filename stem directly in parent reference fields. The recorded real shape uses
an unprefixed task id in the parent reference and an `agent-<taskId>.jsonl` child filename, so the current
test cannot kill a broken prefix resolver.

The reusable actual-binary harness already exists in `tests/test_cli.cpp`: `make_tmp`, `run_cmd`, `ScopedEnv`,
isolated `HOME` / `CODEX_HOME` / `CLAUDE_CONFIG_DIR`, fake pinned agent binaries, and actual pack/open flows.
A valid next instrument can stay wholly disposable and must prove:

1. a committed, sanitized genuine-store-shaped source contains flat bare-hex, flat slug-hex, and nested
   bare-hex cases (or explicitly states any omitted axis);
2. parent references contain realistic unprefixed task ids while child files use the prefixed filename;
3. the shipped CLI packs the source and opens with explicit consent into a clean target;
4. a resolver reads each restored parent reference, constructs the expected flat/nested child path, finds a
   regular file, and reads a known marker from it;
5. source and target roots stay beneath the test sandbox; live `~/.claude` and `~/.codex` are never read or
   mutated;
6. credential-like decoys are not collected or restored.

The fixture states coverage, not corpus representativeness. The dispatch's `309 bare-hex + 269 slug-hex of
578`, both-layout basis is recorded in committed reconciliation evidence, but this implementer did not and
could not freshly remeasure it without violating the same dispatch's prohibition on reading live stores.
Likewise, `145 self / 635 two-level / 7 three-level of 940` is treated here as upstream provenance, not as a
fresh E2 corpus measurement. The code mechanism is independently confirmed; the absolute population count is
not upgraded beyond its committed provenance by this audit.

## 7. Minimum surface map for the later locked plan

Compelled product surface under any coupled repair:

- `src/adapters/codex/codex.cpp` — descendant grouping/emit, staged-reader gate, warning production if selected;
- `src/adapters/codex/install.cpp` — installed root + immediate-parent identity mapping/gate;
- `src/core/pack/pack.cpp` — record-to-manifest cardinality and existing warning transport.

Compelled proof surface:

- `tests/test_adapter_codex_collect.cpp` — depth-three killing case and exact-once artifact closure;
- `tests/test_adapter_codex_install.cpp` — root-valued session id plus distinct immediate-parent id;
- `tests/test_pack.cpp` — staged repack/open and identity/refusal propagation;
- `tests/test_cli.cpp` — actual binary pack/open reference-resolution E2E;
- dedicated sanitized fixture subtree(s) under `tests/fixtures/`.

Conditional shared/hard-out surface only if the locked graph shape changes wire semantics:

- `src/core/manifest/manifest.hpp`;
- `src/core/manifest/manifest.cpp` (fence-2; route UP);
- `tests/test_manifest.cpp`;
- `tests/test_sessions.cpp` only if the session-leg result contract changes.

Boundary contract for the plan: read Codex rollout `id`, `session_id`, and `parent_thread_id` edges; preserve
every reachable artifact exactly once; preserve mapped root and mapped immediate parent as distinct identities;
write a self-consistent packed/staged graph; restore references to existing readable files; never silently
omit a reachable descendant; never discover or write a live operator store.

## 8. Existing local verification (non-acceptance control)

No GitHub Actions or other remote CI was run, triggered, rerun, cancelled, or inspected. Existing exact-tree
macOS tests were run locally after correcting an initially malformed zero-match filter; the zero-test command
is excluded from evidence. Actual results:

```text
Codex adapter collects rollout parent, child, and same-store newest duplicate
  24 assertions / 1 case PASS

B2 standing Claude stage pack open keeps parent references equal to child stems
  482 assertions / 1 case PASS

R-1b Codex parent-valued child session identity survives staged repack
  122 assertions / 1 case PASS

R-1b Codex staged reader accepts a separately mapped in-image parent reference
  153 assertions / 1 case PASS

R-5 Codex preserves a typed identity refusal over an earlier verify hit
  6 assertions / 1 case PASS

aggregate: 787 assertions / 5 actual cases PASS
```

These controls confirm the existing direct-child and one-level behaviors. They do not establish R-4.18 or the
real E2E acceptance criterion.

## 9. Acceptance obligations for a future authorized implementation

- a RED collector case at minimum `R<-P<-C` that fails on `0db8fdd` and requires R, P, and C artifacts and
  identities exactly once;
- design-locked behavior for longer depth, malformed/cyclic ancestry, and any partial-pack/refusal warning;
- write and staged-read cases where installed root and installed immediate parent are deliberately different;
- pack/open proof that no reachable descendant is silently lost and a refused graph fails with the exact
  locked user-visible row/warning;
- actual CLI pack/open E2E over disposable store roots, including all declared Claude shape/layout axes and a
  resolver read of the restored child bytes;
- killing mutations for non-recursion and for collapsing root onto immediate parent;
- macOS plus the AGENTS.md canonical Ubuntu 24.04 `linux/amd64` Docker workflow only after implementation is
  complete; GitHub CI/CD remains deferred unless separately authorized.

## 10. Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — fixture-only, and credential collection is explicitly prohibited
- migration/backfill/destructive-write/canonical-data-repair: no — no audit mutation and no live-store write
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — no downstream act authorized
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — a selected new manifest child shape would cross the shared `agent_sessions[]` API and m-1 fence
- user-visible-control-with-materializer/downstream-consumer: yes — restored session references are consumed by agent resume behavior
- test-runtime-role-mismatch: no — existing controls ran the exact-tree product tests; the missing E2E is named, not waived
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — graph/cardinality and fail-loud semantics await m-2; population totals cannot be freshly remeasured under the live-store prohibition
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- scan_presented_to_operator: yes — this addressed audit reports the conditional manifest seam and evidence limit
- operator_reply_after_scan: none
- valid_waiver: no
WAIVED_RISK_ACCEPTANCE: none

## 11. Boundaries and closeout

`manifest.cpp`, `.github`, sealed docs, product/test source, live stores, credentials, refs, PR state, Actions,
merge, tag, release, publish, install, and deploy were untouched. R-4.15 was not reopened. Merge != push !=
release; the release hold remains ABSOLUTE.

ACTIONS_GIT_REF: read-only source/test inspection and local existing-test execution at exact tree `2d47080877eaf9366e416c39b298905cd051aa9e` for dispatched commit `0db8fdd8424d27aad2c547614e9ebb95621a2794`; this relay plus one append-only INDEX row are the only seat-authored repository writes and will ride one explicit-path docs-lane commit
RELAY_LINT: exact file PASS with freshness (`OK ...144528.md`); `--index .relays/s4/INDEX.md` reports only the inherited line-222 regression (`20260809-142630` follows `20260809-142708`). This seat's appended `20260811-144528` row is monotonic, filename-matched, and untouched except for this authorized append; the historical row was not rewritten
FINAL_GIT_STATUS_SHORT: captured after filing; shared checkout contains pre-existing sibling relay artifacts, while this seat's scoped status is `.relays/s4/INDEX.md` modified and this report untracked

CARRY LIST:
- `.relays/s4/s4-floor-impl/AUDIT-IMPLEMENTER-SLICE-E-R418-SURFACE-IDENTITY-E2E-20260811-144528.md` -> `s4.orchestrator-planner`
- R-4.18 CONFIRMED at `0db8fdd`: `session_for` consumes direct children once; P and C are skipped; `children_by_parent[P]` is never consumed, so C is silently omitted
- coupled gates CONFIRMED: writer and staged reader each collapse chain root and immediate parent into one installed-thread identity; collector-only repair would refuse the newly visible leaf
- warning correction: generic adapter-warning -> pack -> CLI transport already exists, but no chain-drop warning producer/policy exists
- manifest dependency is CONDITIONAL: existing flat/per-entry shapes may avoid fence-2; any new child edge/cardinality contract reaches `manifest.cpp` and routes UP to m-1
- real E2E OWED: actual `biv pack` + `biv open`, disposable genuine-store-shaped fixtures, realistic unprefixed references/prefixed files, resolution/read assertion, no live store and no credentials
- corpus totals remain provenance-backed, not freshly remeasured by this implementer under the live-store prohibition; no code/PR/design decision/remote CI; release hold ABSOLUTE
