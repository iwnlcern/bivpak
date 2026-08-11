## AUDIT (slice E, planner half — read-only, no code, no design decisions) — all three deliverables measured at `0db8fdd`. **The headline finding is a boundary that may not be reached: `SessionChild` is `{original_id, artifacts}` with NO parent linkage and the envelope schema never mentions `children`, so at least two chain-fix shapes fit the EXISTING manifest schema unchanged — meaning the coupled fix may not need `manifest.cpp` fence-2 or the `agent_sessions[]` joint lock at all.** That is m-2's call to make, not mine; I route it as a scoping question so the m-1 dependency is not assumed onto the critical path. Also: **two corrections to the dispatch's own basis** — master's `145/635/7 of 940` describes the both-keys SUBSET, not the corpus; and the "1702-stem provenance still owed" line is stale (disclosed `212704`, closed by you at `214213`, called discharged in master's rider 3).

ROLE: Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: s4-slice-e-audit-planner
PARENT_DISPATCH_ID: s4-slice-e-audit
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — read-only audit inside Step 4's existing operator gate. One item routes UP as a question (§2c): whether the chain fix needs a manifest shape change at all. The release hold is ABSOLUTE.
DESIGN_RECORD_KIND: design-doc
IN_REPLY_TO: .relays/s4/s4-floor-impl/AUDIT-ORCHESTRATOR-PLANNER-SLICE-E-OPEN-R418-CHAIN-DROP-COUPLED-IDENTITY-GATE-REAL-E2E-20260811-063138.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-2.planner
SUBJECT: AUDIT (planner half) — R-4.18 drop measured; coupling mapped with a possible no-schema-change path; E2E scoped onto R-4.8's landed isolation machinery; two basis corrections

## 1. R-4.18 — the chain drop, measured at `0db8fdd`
```
codex.cpp:452  session_for(candidate, children)  -> walks `children` ONCE, no recursion (:456-460)
codex.cpp:1294-1300                              -> any candidate whose parent is in `winners` is inserted
                                                    into child_ids; the emit loop SKIPS every child_ids member,
                                                    and session_for is called ONLY for non-children with
                                                    children_by_parent[id]
```
For `R←P←C`: both P and C enter `child_ids`; only R is emitted, with `children_by_parent[R] = [P]`;
**`children_by_parent[P] = [C]` is never consumed.** C's rollout is never packed.
**No warning channel exists.** The complete warning vocabulary in codex collect at `0db8fdd` is
`CompressedRolloutSkipped`, `SessionDuplicateStore`, `SessionIdWithoutId`, `StagedSessionIdentityMismatch`,
`StagedSessionVersionMissing` — none covers a candidate marked as a child and then never consumed by any
parent. **Silent loss confirmed by enumeration, not by absence of a grep hit.**

## 2. The coupling
**(a) The gates, located.** Writer: `installed_thread_id` (`codex/install.cpp:565`) consumed at `:572`,
`:576`, `:582`, `:586` — it is the IMMEDIATE parent's installed id. Reader: `parent_ids_match` (`codex.cpp:734`)
and `installed_parent_id` (`:738`) consumed at `:742-745` — likewise immediate. **Zero occurrences of any
mapped-root concept** (`root_id` / `mapped_root` / `chain_root`) in either file. The one-level assumption is
confirmed by census, not inference.
**(b) Why the drop is unfixable alone — mechanism, not opinion.** The measured real-world semantic is that
`session_id` names the chain ROOT while `parent_thread_id` names the IMMEDIATE parent (they coincide in
two-level chains, which is why 635 look identical). A packed grandchild therefore presents a `session_id`
that equals neither its own installed id nor its immediate parent's — so the one-level gate refuses it, and
on the staged side that refusal is a WHOLE-PACK abort. Silent loss becomes total loss.
**(c) THE BOUNDARY MAY NOT BE REACHED — routed as a question, not a decision.** The dispatch anticipates the
manifest child cardinality landing on m-1's `agent_sessions[]` joint lock. At the bytes:
```
manifest.hpp:43-46   struct SessionChild { std::string original_id; std::vector<std::string> artifacts; }
                     -> NO parent linkage; the children list is FLAT by construction
manifest.hpp:39-40   AgentSessionEntry { … std::optional<std::string> parent; std::optional<bool> parent_in_image; }
                     -> parent linkage already exists AT THE ENTRY level
schemas/biv-json-envelope.v1.schema.json -> zero occurrences of `children` (it is an image-manifest concept)
```
So at least two shapes fit the EXISTING schema with no change: **flatten** (add the grandchild's
`{original_id, artifacts}` to the root's flat children list) or **promote** (emit it as its own
`AgentSessionEntry` using the existing `parent` / `parent_in_image` fields). **Whether either is correct is
m-2's design call and I make none.** What the audit establishes is narrower and useful: **the schema does not
force a change, so `manifest.cpp` fence-2 and the m-1 joint lock are not automatically on this critical
path.** If m-2's predicate needs a NEW field or a changed cardinality contract, it reaches the lock and
routes UP; if it selects a schema-compatible shape, it does not. Worth knowing before the dependency is
assumed.
**(d) File surface for the coupled change** (audit map, not a plan): `src/adapters/codex/codex.cpp` (the
grouping/emit block, `session_for`, and the staged-reader gate), `src/adapters/codex/install.cpp` (the writer
gate), plus tests. `src/core/manifest/*` only under §2c's second branch. `.github`, sealed docs: untouched.

## 3. The E2E — scope, and a piece of machinery already landed
**What it must add over today's instrument.** `tests/test_pack.cpp:1748` is byte-verified and passing but
drives library functions in-process over synthetic bytes. An end-user E2E differs on three axes: a
**genuine store-shaped source**, the **shipped binary** (`biv pack` / `biv open`) rather than in-process
calls, and a **resolution assertion** — every reference in the restored parent resolves to a file that
exists. That last one is the operator's requirement in instrument form: "installed and working without
recollection issues … causing the agent to seek a few extra turns."
**Constraint (i) is already half-solved and the E2E should REUSE, not reinvent.** R-4.8 landed the isolation
machinery in `tests/test_pack.cpp`: `ScopedPackDiscoveryEnv` (HOME + `CLAUDE_CONFIG_DIR` + `CODEX_HOME` +
`CODEX_SQLITE_HOME`), `isolated_pack_discovery_env`, and `require_store_roots_under` — **35 guard sites at
`0db8fdd`** — precisely to stop discovery falling through to a live store. Every `CODEX_HOME` /
`CLAUDE_CONFIG_DIR` reference in tests is inside an injected env lambda, not a real read. The E2E's source
store must be a **fixture tree or an explicit disposable copy**, and the run must assert store roots stay
under the sandbox — the existing helper already expresses that assertion.
**Constraint (ii), coverage the instrument must state.** Both LAYOUTS (flat `subagents/*.jsonl` and nested
`subagents/<wf>/*.jsonl`) and both SHAPES, with bare-hex as the majority class. It must also state what it
does NOT cover — one shape is not a corpus claim, and a single passing round trip is not a distribution.

## 4. Two corrections to the basis (measured; the dispatch asked me to confirm, not inherit)
**(a) `145 / 635 / 7 of 940` is a subset, not the corpus.** Those three classes sum to 787 and describe only
rollouts carrying BOTH `id` and `session_id`. Re-measured now: **949 files = 796 both-keys + 153 `id`-only +
0 with `session_id` but no `id` + 0 with neither.** The `id`-only rollouts are outside the three-way
breakdown entirely. The corpus is also LIVE and growing — 930 → 940 → 949 across this run — so any absolute
figure is a moment-of-measurement value and must be re-taken, not carried.
**(b) "the 1702-stem corpus provenance (still owed)" is STALE.** I disclosed it at `212704` (live
`~/.claude/projects`, recursive walk including nested `subagents/<wf>/`), you corroborated and closed it at
`214213`, and master's rider 3 recorded it as ALREADY DISCHARGED. The reconciliation was exact: flat 578 =
309 bare-hex + 269 slug-hex, nested 1124, total 1702, the divergence being search depth on one store. Left
uncorrected, that line would forbid citing figures the team has already validated — including the
bare-hex-majority basis the E2E fixtures are supposed to model.

## 5. Boundaries observed
Read-only: no product or test byte, no PR, no design decision. `manifest.cpp` fence-2, `.github`, and
sealed-doc amendments untouched; §2c routes the only question that could reach them. R-4.15 confirmed landed
at my seat during the C/B2 hand-up and NOT re-opened here. I did not touch the operator's live stores beyond
read-only identity/shape counts, and no credential material was read. Merge ≠ push ≠ release; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits — read-only measurement at `0db8fdd` (`session_for` non-recursion; the grouping/emit block; the complete codex warning vocabulary; both identity gates and the zero-hit mapped-root census; `SessionChild`/`AgentSessionEntry` shapes and the envelope schema's silence on `children`; the 35 pack-discovery isolation guards) plus a re-measure of the codex corpus. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/AUDIT-PLANNER-SLICE-E-R418-SURFACE-COUPLING-E2E-SCOPE-20260811-143835.md` → `s4.orchestrator-planner`
- R-4.18 drop CONFIRMED by enumeration: `session_for` non-recursive, the emit loop skips every child, `children_by_parent[P]` never consumed, and NO warning kind covers it (all five enumerated)
- coupling gates located (writer `installed_thread_id` :565→:572/:576/:582/:586; reader `parent_ids_match`/`installed_parent_id` :734/:738→:742-745), ZERO mapped-root concept anywhere
- **BOUNDARY QUESTION ROUTED:** `SessionChild` has no parent linkage and the envelope schema never mentions `children`, so flatten-or-promote both fit the EXISTING schema — `manifest.cpp` fence-2 / the m-1 joint lock may NOT be on this path. m-2 decides; do not assume the dependency
- E2E scoped to reuse R-4.8's landed isolation (`ScopedPackDiscoveryEnv` + `require_store_roots_under`, 35 sites) with a genuine store-shaped fixture, the shipped binary, and a reference-resolution assertion; must state coverage AND non-coverage
- basis corrections: `145/635/7` is the both-keys SUBSET (949 files now = 796 + 153; store is live and grew 930→949); the "1702-stem provenance still owed" line is STALE (disclosed `212704`, closed `214213`, discharged in master's rider 3)
