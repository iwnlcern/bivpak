## PLAN (slice E, coupled — gated; plan-review requested) — both design pins RE-DERIVED at my seat: addendum-12 `154cd87e…` at pdc `3929c9c`, consuming J `94b6440c…` at `e30f845`. The contract is materially larger than "make `session_for` recursive": it adds **rootless-cycle detection with a named omitted edge**, a **MONOTONE membership gate where the declared edge may only SUBTRACT acceptances**, and a warning channel bound to `CollectReport.warnings` — **not** `SessionRecord`, which has no such member (the design says so in its own voice, having caught that error in rev0). Six tasks, RED-first, `manifest.cpp` HARD-OUT with the m-1 dependency named and co-sequenced.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate to reach the plan gate — the VP's exact-pin design gate passed. This relay requests my Implementer's PLAN REVIEW, which IS slice E's plan gate; implementation, merge, seal and release each retain their own. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
TARGET_DESIGN_COMMIT: 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PROCEED-TO-PLAN-ORCHESTRATOR-PLANNER-SLICE-E-RELEASED-R418-COUPLED-DESIGN-LOCKED-20260812-150245.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN — slice E coupled: transitive collect + rootless-cycle disposition + MONOTONE root-mapped gate + warning channel + FX-A12-1..7 + a three-level CLI E2E; plan review requested

## 0. Pins re-derived at this seat (do not act on any other design bytes)
```
addendum-12  pdc 3929c9c : master/domains/m-2-agent-adapters/design/2026-08-12-ADDENDUM-12-…md
             sha256 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77   MATCHES the lock
J (sealed)   pdc e30f845 : master/domains/m-1-format-engine/design/2026-08-11-ADDENDUM-J-…md
             sha256 94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18   MATCHES the contract
approving DESIGN-REVIEW: …ADDENDUM12-LOCK-APPROVE-MONO-CORRECTED-20260812-145249, verdict approve,
             TARGET_DESIGN_SHA256 identical  -> lineage satisfied on the exact doc hash
```
**Read the design at the pdc BLOB, not any working copy.** Cut against `0db8fdd`.

## 1. T1 — transitive collect (`codex.cpp` `session_for` + the `1294+` grouping/emit)
Traversal and emission are DIFFERENT and the design says rev0 conflated them:
- **TRAVERSAL (gather):** iterative, with a VISITED SET, **no depth cutoff** — never truncates silently.
- **EMISSION (record):** J's producer caps enforced BEFORE emitting — **≤1024 nodes per entry, ≤64 parent
  depth**. Over either cap ⇒ **J's locked typed WHOLE-ENTRY refusal**. **Neither cap truncates.**
Root predicate is unchanged (a node is a root iff its parent is not in `winners`); only roots are emitted.
The bug to kill: `children_by_parent[P]` is never consumed, so for `R←P←C` the leaf is packed nowhere.

## 2. T2 — rootless components and cycles (the part that is NOT a recursion fix)
A pure cycle has every member's parent in `winners`, so **every member is marked a child and no root is
emitted — a root-launched traversal never reaches it, and a visited set cannot detect it.** Required:
- **DETECTION:** an explicit pass over `winners` for nodes reachable from NO root.
- **CYCLE ID:** within that component identify the actual cycle (the closed parent walk) — a rootless
  component is not necessarily a pure cycle; off-cycle descendants may hang off it.
- **DISPOSITION:** the **lexicographically least CYCLE MEMBER** becomes the synthetic primary and **that
  member's outgoing parent edge is omitted** — so every other chain reaches the primary and the component is
  one rooted tree satisfying J's wire contract. **Least-of-component is the wrong rule and FX-A12-3 exists
  to kill it** (its off-cycle descendant sorts before every cycle id).
- **CARRIAGE:** every artifact in the component carried **exactly once**.
- **WARNING:** a typed line naming the component AND the exact edge omitted.

## 3. T3 — the identity gate: widened AND monotone (get the ground right)
```
ACCEPT  iff every parent_thread_id in the artifact's POST-REWRITE bytes is a member of THIS ENTRY'S
        MAPPED NODE SET (the installer's own mapping over J's M4-CG-1 closed node set).
        THE DECLARED EDGE IS NOT CONSULTED.
REFUSE  additionally if the declared edge is PRESENT and disagrees (edge says X's parent is Y; the bytes
        name something other than mapped(Y)).
=>      A(E) = membership AND edge-consistency;  A(0) = membership alone;  A(E) ⊆ A(0) BY CONSTRUCTION.
```
**The edge may only ever SUBTRACT an acceptance, never create one** — that is `R-4.20` and the MONO
direction, and the design records rev0 asserting the opposite inside the document that forbids it. Both
sides move: writer `codex/install.cpp` (today one `installed_thread_id`, immediate-parent-or-self at
`:565-592`) and the staged reader (`codex.cpp:700-818`). Widening one alone converts today's silent loss
into a `staged_identity_mismatch` whole-pack abort on every three-level leaf.

## 4. T4 — the warning channel (bind the right struct)
Everything the closure cannot carry or represent MUST emit on **`CollectReport.warnings`**
(`adapter.hpp:104-106`), the channel `db_warnings` already merges into at `codex.cpp:1311-1316`.
**`SessionRecord` has no warnings member** — the design corrects rev0 for citing one. **Add no warnings
member.** Covered: a detected rootless component with its omitted edge named; a descendant whose artifact is
missing/unreadable/non-UTF-8; a child rollout that failed to read; any node reachable in the parent relation
but not carryable; **any entry refused for exceeding J's caps**. My audit enumerated the existing vocabulary
(`CompressedRolloutSkipped`, `SessionDuplicateStore`, `SessionIdWithoutId`, `StagedSessionIdentityMismatch`,
`StagedSessionVersionMissing`) — none covers a dropped descendant, which is why silence is today's defect.

## 5. T5 — fixtures FX-A12-1..7, RED first
`FX-A12-1` three-level chain carried (the STOP; RED at `0db8fdd`); `FX-A12-2` two-level unchanged —
**compatibility control, byte-identical round trip, no `parent_id` emitted** under J's absence license;
`FX-A12-3` rootless cycle broken and carried, with the off-cycle-descendant trap above; `FX-A12-4`/`4a`
uncarryable descendant warns; `FX-A12-5`/`6`/`7` per the design's own text — read them at the blob, do not
work from this summary. Each RED before its fix, with the RED receipt in the report.

## 6. T6 — the E2E (acceptance, not a unit fixture)
A real `biv pack` → `biv open` of a **three-level chain** from a fixture store into a clean target, showing
the leaf's rollout **present AND its references resolving to files that exist** — the operator's criterion,
"installed and working without recollection issues." **The current E2E contains no three-level chain.**
Reuse what exists rather than reinventing: R-4.8's `ScopedPackDiscoveryEnv` (HOME + `CLAUDE_CONFIG_DIR` +
`CODEX_HOME` + `CODEX_SQLITE_HOME`) and `require_store_roots_under` (35 guard sites at `0db8fdd`), plus
`test_cli.cpp`'s actual-binary harness. **NEVER read or mutate the live `~/.claude` / `~/.codex`** — fixture
tree or explicit disposable copy only; **no credential collection**; read host state freely, write only with
consent. **State covered axes AND non-coverage.**
**Corpus basis, binding and obeyed as locked:** `309` bare-hex + `269` slug-hex of `578`, bare-hex the
MAJORITY; the withdrawn "578/578 slug-hex" must not reach a fixture. **The design directs that the
`1702`-stem figure is cited nowhere, and this plan cites it nowhere** — note only that LAYOUT coverage
(flat and nested `subagents/<wf>/`) is still required by the proceed-to-plan, and is satisfiable from the
578 basis without invoking the other figure.

## 7. Boundary and the m-1 dependency (name it, do not author it)
J changes `agent_sessions[].children[]` — gaining the child→parent edge, meaning direct children become
**transitive descendants**. That schema implementation lives in `manifest.hpp`/`manifest.cpp`; **`manifest.cpp`
is fence-2 and HARD-OUT for this pair.** **CO-SEQUENCING, stated as a dependency: the adapter cannot emit
transitive descendants before the manifest carries them** — so T1/T2's emission half lands only once m-1's
schema work is in, or behind a flag the design permits. If any task turns out to require touching
`manifest.cpp`, **STOP and route to me**; do not author it. Also hard-out: `.github`, sealed-doc amendments.

## 8. Constraints to build against (not to rediscover)
`R-4.20` — the declared edge produces **refusals only**; containment rests on **locally-minted destinations**,
whose real mint sites are `codex/install.cpp:122-143 uuidv7_from_ms`, `:430`, `:455 mint_rollout_name()`,
writes `:483-489`. **Do not cite `:507-513` as minting proof — it calls `derive_install_pair_set` and mints
nothing.** Image-derived identifiers are lookup/rewrite keys only, never destination identities or path
components. MONO `A(E) ⊆ A(0)`. Producer closure — pack refuses loudly rather than emit a tree its own parser
would reject. Per-entry caps with typed refusal, **never silent truncation**. `M4-CG-0` duplicate-known-key
refusal (`at_key` first-wins). **`R-4.24` is m-3 (surface) / m-1 (count) — adjacent to our count/consent
surface, NOT ours, and we do not gate on it.**

## 9. Evidence plan
RED-first per task with receipts; full macOS suite and bounded Ubuntu 24.04 `linux/amd64` Docker parity at
the exact candidate SHAs with the standing disclosed classes; A3 both-anchor re-fire if an anchored collector
moves; **the base-container control if any Linux failure-set count changes** (the C/B2 lesson: a bounded
exclusion cannot distinguish inherited from introduced); cut against `0db8fdd` with the D-5.5(a) cut-point
blast radius measured against `origin/main` **at hand-up time**, not carried forward.

## 10. What I am asking of you
**A plan review** — this is slice E's plan gate. Grade the plan, not the code: is the task decomposition
complete against the locked design (read it at the blob), is the boundary correct, are the falsifiers the
right ones, and is anything here a design decision I had no authority to make? Reply with
`PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no backticks; remarks via
em-dash only, per the matcher's recorded grammar). On approve I issue exactly one implementation dispatch.
Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — design pins re-derived at pdc `3929c9c`/`e30f845`, the approving DESIGN-REVIEW's verdict and target hash confirmed, and the normative sections (A12.2/.3/.4/.6/.7) read at the blob; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MONO-GATE-20260812-150913.md` → `s4-floor.implementer` (plan review = slice E's plan gate)
- both pins RE-DERIVED here: addendum-12 `154cd87e` @ `3929c9c` consuming J `94b6440c` @ `e30f845`; lineage satisfied on the exact doc hash by the `145249` approve
- six tasks: transitive collect (unbounded traversal / J-capped emission, typed whole-entry refusal, never truncate) · rootless-cycle detection with least-CYCLE-MEMBER primary and the omitted edge NAMED · both gates root-mapped and MONOTONE (membership is the ground; the edge only SUBTRACTS) · warnings on `CollectReport.warnings` NOT `SessionRecord` · FX-A12-1..7 RED-first · three-level CLI E2E on disposable stores
- `manifest.cpp` fence-2 HARD-OUT; m-1 schema dependency NAMED with co-sequencing (the adapter cannot emit transitive descendants before the manifest carries them); route UP if a task needs it
- constraints carried not rediscovered: R-4.20 mint sites `:122/:430/:455` (NOT `:507-513`), MONO `A(E) ⊆ A(0)`, producer closure, typed refusal never silent truncation, M4-CG-0; R-4.24 is m-3/m-1's; release hold ABSOLUTE
