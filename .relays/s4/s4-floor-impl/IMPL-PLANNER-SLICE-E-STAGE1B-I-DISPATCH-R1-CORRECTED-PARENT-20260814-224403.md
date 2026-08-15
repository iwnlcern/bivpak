## IMPL DISPATCH R1 (slice E, STAGE 1b-i) — **I made the same mistake twice, and the second time is the serious one.** At `140738` I disclosed pointing a token at the PLAN instead of the approving PLAN-REVIEW, wrote out why the edge matters, and adopted the correction. Then I pointed this one at the **orchestrator's gate-clearance** — a different wrong relay, the same wrong instinct: **both times I reached for the relay I was REPLYING to.** That is `IN_REPLY_TO`'s job. **`IN_REPLY_TO` is what prompted a relay; `PARENT_DISPATCH_ID` is what AUTHORIZES it, and an orchestrator PROCEED clears a GATE — it does not supply a REVIEW.** Corrected to `s4-floor-slice-e-plan-review-successor-r7d`. **`215636` is WITHDRAWN and INERT.** Scope, pins, the A3 baseline and every constraint are byte-identical — **nothing about the work changed, only the edge that authorizes it.**

## 0. The defect, and the reproduction

```text
215636 (WITHDRAWN)  PARENT_DISPATCH_ID: s4-floor-slice-e-stage1b-i-cleared   <- an ORCHESTRATOR PLAN gate-clearance
REQUIRED            PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7d
                      FROM s4-floor.implementer · PLAN_REVIEW_VERDICT: approve
                      its own parent -> s4-floor-slice-e-plan-successor-r7d (the PLAN)
reproduced at my seat: relay-lint --relay-root .relays/s4/s4-floor-impl -> FOUR errors naming 215636
                       exact-file lint -> OK. Clean shape, wrong lineage, AGAIN.
```

**The instrument note is the part worth keeping:** the exact-file arm false-greens this class **both times**,
and the `--relay-root` arm fires. I have now added the root arm to my pre-file sequence for any relay carrying
a token, and I write the chain out hop by hop — *this token → which review? its verdict and FROM? its parent →
which plan?* — instead of trusting that the newest relay is the authorizing one.

**The correction I owe my own record:** my `140738` relay said the lesson was "point at the review, not the
plan." That was too narrow — it named one wrong answer instead of the rule. **The rule is that the parent is
the approving review, whatever else has happened since**, and a gate-clearance arriving later does not become
the parent by being recent.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage1b-i-impl-r1
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-review-successor-r7d
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — any `src/core/manifest` delta returns for m-1's byte-level review (the (A) fence persists). Stage 1b-ii stays blocked on the consumer half; merge stays blocked by the land order. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_TARGET_DESIGN_SHA256: eeb4dd01cc907b5dc793a7a27892395a8af258f4967a38fd744f2b424013c7aa
CONSUMER_TARGET_DESIGN_COMMIT: a016f9532d6a4abff2d4e642062f8127efa0eae8
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-STAGE1B-I-DISPATCH-LINEAGE-BLOCKER-20260814-215737.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R7D-SECOND-VALUE-AND-ALL-A36-LEGS-20260814-134034.md (the approved plan); .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-STAGE1A-FOLD-VERIFIED-HANDUP-M1-20260814-190258.md (Stage 1a at `c74c20b`, the base)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: IMPL DISPATCH R1 — canonical parent corrected to the approving PLAN-REVIEW; 215636 WITHDRAWN; scope, pins, A3 baseline and every constraint unchanged

## 1. Pins and base, RE-DERIVED AT THIS ACT

```text
addendum-12 @ 6eeeb157  29a5b3a3abb6777a…    J @ e30f845  94b6440c6ea5342a…
m3-addendum-3 @ a016f953  eeb4dd01cc907b5d…
later commits per document: 1 / 1 / 1 — each is that document's own lock or lock-stamp   ZERO drift
origin/main  0db8fdd (unchanged)      BASE FOR 1b-i:  c74c20b  (m-1-approved Stage 1a)
```

**A3 anchors measured at the base, not assumed:**

```text
e3.py pins at c74c20b   claude cd1f8bc8…   codex 2fd24c84…
actual at c74c20b       claude cd1f8bc8…   codex 2fd24c84…      -> BOTH MATCH; tripwire GREEN NOW
```

**So the A3 ceremony fires with CERTAINTY the moment you touch `codex.cpp`** — it is not conditional, and the
green baseline above is what makes the RED meaningful.

## 2. Scope

SCOPE_DIFF:
- src/adapters/adapter.hpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/codex/install.cpp -> in
- src/core/pack/pack.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_pack.cpp -> in
- tests/fixtures/slice-e/** -> in
- harness/bivharness/e3.py -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/adapter.hpp — the `child_parent_map` carrier on `SessionRecord` (`A12.2.4`), declared, populated and consumed here; `child_ids` keeps its flat SET shape and `child_artifact_map` is NOT reused. Named IN by the approved plan's Stage-1b-i row.
- src/adapters/codex/codex.cpp — transitive closure at `session_for`/the grouping-emit block, the rootless-component pass, the staged-reader gate, and the warning producers on `CollectReport.warnings`. **ANCHORED — the A3 ceremony fires here.** Named IN by the plan.
- src/adapters/codex/install.cpp — the writer gate and the mapped node set, made root-mapped and MONOTONE. Named IN by the plan. **Not anchored** (`153958` excludes `install.cpp` normatively), so it moves no pin.
- src/core/pack/pack.cpp — `manifest_entry_for`'s edge emission under J's absence license, and the four producer caps with the `ArchiveWriteFailed` carrier. Named IN by the plan.
- tests/test_adapter_codex_collect.cpp — greens `FX-A12-1a`, `FX-A12-3`, `FX-A12-4`. Named IN by the plan.
- tests/test_adapter_codex_install.cpp — carries `FX-A12-4a`, `FX-A12-5` (atomic), `FX-A12-6`. Named IN by the plan.
- tests/test_pack.cpp — carries `FX-A12-1b`, key 2 BOTH arms, and the eight cap arms with the atomic-absence oracle. Named IN by the plan.
- tests/fixtures/slice-e/** — existing subtree from Stage 0, incl. the DATA-ONLY trees for `1b`/`4a`/`5` whose tests become compilable now. Named IN by the plan.
- harness/bivharness/e3.py — the codex anchor pin ONLY, inside the single anchored head, under AMENDMENT A3's standing grant. Nothing else in this file.

**FORBIDDEN — a byte in any of these is a scope breach: STOP and route.** `src/core/manifest/**` (Stage 1a is
approved and closed; **any delta there returns for m-1's byte review and is not a 1b-i act**),
`src/core/open/**` (m-3's, HARD-OUT pending the operator's §5), `src/cli/**`, `tests/test_manifest.cpp`,
`tests/test_adapter_claude_collect.cpp` (key 7 is a Stage-0 control, already green — leave it), `.github/**`,
sealed docs, `harness/**` other than the one pin, and every path not listed.

## 3. What to build

**One coupled change.** Transitive closure with a visited set and **no depth cutoff** in the traversal, while
**emission enforces J's caps BEFORE emitting** with the locked typed whole-entry refusal — **traversal and
emission are different things and neither truncates.** `child_ids`' MEANING moves to TRANSITIVE DESCENDANTS
while its SHAPE does not; **shape-unchanged is not semantics-unchanged**, and no consumer may infer otherwise.

**Rootless components** need an explicit pass — every member of a pure cycle has its parent among the winners,
so no root is emitted and a root-launched visited traversal never reaches it. The **lexicographically least
CYCLE MEMBER** is the synthetic primary with **that member's outgoing edge omitted**; every artifact carried
exactly once; the omitted edge NAMED in a warning.

**Both gates root-mapped AND monotone:** ACCEPT iff every post-rewrite `parent_thread_id` is a MEMBER of the
entry's mapped node set, **with the declared edge NOT consulted**; REFUSE additionally when a PRESENT edge
disagrees. `A(E) ⊆ A(0)` by construction — **the edge may only SUBTRACT.**

**`FX-A12-3`'s three legs are OWED here and are the reason this stage is not just a recursion fix.** They have
**never executed** — they sit behind the failing cardinality `REQUIRE`. Show them **executing and passing**,
and show the **cycle-member leg FAILING against a least-of-component implementation** where the off-cycle
descendant sorts first. **An assertion nobody has watched run protects nothing**, and that leg is the entire
reason the fixture carries an off-cycle descendant.

**Key 5 is ATOMIC** — one artifact, two executed variants, both outcomes asserted; both-refused FAILS.
**Key 2 keeps both arms.** The cap arms use the **atomic-absence oracle on the three SOURCE-DERIVED paths**
(`<name>.bvpk`, `.bvpk.partial`, `.bvpk.spool`), fresh output directory per arm, with the at-cap positive arm
proving the fixture is packable at the boundary.

**RED-first, three points as planned:** the remaining REDs (`1b`, key 2 arm 2 as a GREEN control, `4a`, `5`)
are authored and RUN now that the schema exists — **observed failing, receipts recorded — before the fix.**
**A compile failure earns no behavioral-RED credit.**

**THE THREE STOPS — halt and route to me, do NOT decide:** (1) MULTI-CAP BREACH → m-1's, and note
**STOP-1 is RULED first-breached-in-declared-order with the implemented order already pinned**, so this fires
only if 1b-i introduces a *new* ordering question; (2) J-R6/J-R7 originate on **m-3's** surface — never
re-derived from J's reasoning; (3) the cap-carrier seam `§A12.4.2` — consistent with **m-2's ruling**, and
**a warning appended where the failure path discards it is dead code that reads as compliance in a diff.**

**m-1's VETO LIST stands, with cycle 1's specific lesson at the top: DO NOT ADD A CHECK J DOES NOT LICENSE.**
Then: no post-loop cap check instead of the short-circuit-at-the-Nth-before-construct; **no truncation
anywhere**; no writer emitting what its own parser refuses; no cap error missing either the cap or the entry;
no silent STOP-filling. **And do not reintroduce the vetoed entry-artifacts-per-node check in any form.**

DISPATCH IMPL

## 4. A3 — one head, one pin, four checks

**All `codex.cpp` changes land in ONE head carrying its ONE `_ADAPTER_SOURCE_ANCHORS` codex-pin update in the
SAME commit** — the only shape satisfying check 1. Then the four checks, on that same head: (1) the diff shows
`codex.cpp`'s change plus the ONE anchor-literal update and nothing else anchor-side; (2) the review re-derives
`codex.cpp`'s whole-file hash at the head and matches the new literal; (3) each `153958` §4 read-side session
literal is **mutation-checked** — mutate, observe RED, revert, record the mutation diff and the failing
assertion; (4) the review states, **CLASS-SCOPED**, that the diff touches none of those literals.

**Re-locate the literal classes at the head — our own edits move these line numbers, so do not carry them:**
the sessions-root locator, the archived-sessions locator, the `state_5.sqlite` selection and its store-root
fallback, the `config.toml` `sqlite_home` read, and the rollout path construction. **The claude pin must NOT
move** — if it does, a claude production file changed and that is a scope breach, not a recapture. **Report
the ceremony burden** per the grant's own R-3.40(11) trigger rather than absorbing it.

## 5. Evidence and where this ends

Build on `c74c20b`, branch **LOCAL and UNPUBLISHED**. Full macOS suite plus `git diff --check`; the local
Ubuntu 24.04 `linux/amd64` Docker suite **governs** Linux. **GitHub Actions NOT invoked.** **Run the
base-container control if the Linux failure-set count changes at all** — a bounded exclusion cannot
distinguish inherited from introduced. **The two known inherited rows** (macOS `readelf`, the Linux registered
probe case) are expected; **anything else is a finding.** Never read or mutate the live `~/.claude` /
`~/.codex`; no credential collection; sandbox guards and the credential decoy on every case.

**Then STOP and report.** This token covers Stage 1b-i only. **Stage 1b-ii needs the consumer half and a fresh
dispatch from me. Any `src/core/manifest` delta returns for m-1's byte review.** **NOTHING MERGES:** the land
order binds — no schema-2-capable head lands ahead of `M3-J-4..7` in force at a named receipt SHA — and the
early-merge narrowing **stays REFUSED**. No push, no PR, no Actions, no merge, no seal, no deployment, no
release. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed all three design targets (`29a5b3a3`/`94b6440c`/`eeb4dd01`) and counted later commits per document (1/1/1, each its own lock stamp); re-measured `origin/main`; and measured the A3 anchors at the 1b-i base `c74c20b`, confirming `e3.py`'s two pins equal the actual `claude_code.cpp`/`codex.cpp` hashes there, so the tripwire is green at the base and the ceremony fires with certainty on the codex edit. This relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1B-I-DISPATCH-IMPL-TOKEN-20260814-224403.md` → `s4-floor.implementer`
- **pins re-derived AT THIS ACT** — three targets match, 1/1/1 later commits each being that document's own lock stamp, zero drift; base is `c74c20b` (m-1-approved Stage 1a); `origin/main` unchanged at `0db8fdd`
- **A3 anchors MEASURED at the base, not assumed:** `e3.py`'s two pins equal the actual hashes at `c74c20b`, so **the tripwire is GREEN NOW and the codex edit turns it RED** — the ceremony fires with CERTAINTY, in ONE head carrying its ONE pin, with all four checks and the literal classes **re-located at the head** since our edits move those line numbers; **the claude pin must NOT move**; burden reported per R-3.40(11)
- **nine scope rows, `all-in`, per-row evidence**; `src/core/manifest/**` is FORBIDDEN here — **any delta there returns for m-1's byte review and is not a 1b-i act**; `sessions.cpp` HARD-OUT pending operator §5; `test_adapter_claude_collect.cpp` left alone since key 7 is an already-green Stage-0 control
- build: one coupled change — traversal unbounded with a visited set while **emission** enforces J's caps with typed whole-entry refusal (**different things, neither truncates**); `child_ids`' MEANING moves to transitive descendants though its SHAPE does not; rootless pass with the **least CYCLE MEMBER** primary and its outgoing edge omitted; both gates root-mapped and MONOTONE with `A(E) ⊆ A(0)` so **the edge may only SUBTRACT**
- **`FX-A12-3`'s three legs are OWED here** — they have NEVER EXECUTED; show them executing and passing, and the **cycle-member leg FAILING against a least-of-component implementation**, because an assertion nobody has watched run protects nothing. Key 5 ATOMIC, key 2 both arms, cap arms on the three SOURCE-DERIVED paths with the at-cap positive arm
- **m-1's veto list with cycle 1's lesson at the top: ADD NO CHECK J DOES NOT LICENSE**, and do not reintroduce the vetoed entry-artifacts-per-node check in any form; the three STOPs rebound (**STOP-1 already ruled and the implemented order pinned**, so it fires only on a NEW ordering question)
- evidence: macOS + **governing** local Ubuntu Docker, **Actions NOT invoked**, base-container control on ANY change in the Linux failure count, the two known inherited rows expected and **anything else is a finding**; live stores never touched
- **STOP and report at the end** — 1b-ii needs the consumer half AND a fresh token from me; **NOTHING MERGES**, the land order binds and the early-merge narrowing stays REFUSED; branch local and unpublished; release hold ABSOLUTE
