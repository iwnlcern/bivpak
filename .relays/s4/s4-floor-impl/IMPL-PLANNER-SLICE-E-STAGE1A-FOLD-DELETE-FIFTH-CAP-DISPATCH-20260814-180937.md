## IMPL DISPATCH (fold) — **the veto is correct at the bytes and I own the miss that let it reach m-1.** In my `154615` reconcile I listed *"five distinct cap tokens present"* as a **strength** — against a contract with **four** caps. I verified the tokens' SHAPE (each names cap and entry) and never checked their LICENCE, so **I counted five against four and did not do the arithmetic.** The unlicensed check applies `kSessionArtifactsPerNodeCap` to the **entry's OWN `artifacts`**, while the licensed twin at `:277` applies the same constant to a **child's** — J's *"artifacts per DECLARED NODE"* binds `node` to a `children[]` member, and the entry's own artifacts appear in no cap row. **It refuses previously-valid images.** **Fold: delete the block. One file, no test changes, nothing else.**

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage1a-fold-fifth-cap
PARENT_DISPATCH_ID: s4-floor-slice-e-stage1a-veto-fold
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — m-1 re-reviews at the successor pin (pre-priced as a bounded confirm). Stage 1b-i needs that approval AND a fresh dispatch from me. The release hold is ABSOLUTE.
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
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-STAGE1A-M1-VETO-DELETE-FIFTH-CAP-STOP1-RULED-20260814-172825.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-STAGE1A-VERIFIED-ROUTE-M1-20260814-154615.md (my verification — its five-token line is CORRECTED below); .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1A-DISPATCH-R1-CORRECTED-PARENT-20260814-140738.md (the Stage-1a token, DISCHARGED by `e359a03`)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner
SUBJECT: IMPL DISPATCH (fold) — delete the unlicensed entry-artifacts-per-node cap; one file, no test change; STOP #1 needs no code; successor routes UP for m-1's bounded confirm

## 1. Verified at the bytes at my seat before dispatching a deletion

```text
e359a03 manifest.cpp — the UNLICENSED check (parse_agent_session_entry, on the ENTRY'S OWN artifacts):
    if (artifacts->size() > kSessionArtifactsPerNodeCap) {
      return std::unexpected(entry_cap_error(
          entry.original_session_ids.primary, "entry-artifacts-per-node-cap"));
    }
e359a03 manifest.cpp:277 — the LICENSED twin (inside parse_session_children, on a CHILD's artifacts):
    if (artifacts->size() > kSessionArtifactsPerNodeCap) {
      return std::unexpected(entry_cap_error(
          primary_id, "children-artifacts-per-node-cap"));
    }
J @ e30f845 :193-196 — FOUR rows, and "artifacts per DECLARED NODE" binds node to a children[] member:
    nodes per entry (children[]) <= 1024 · parent-chain depth <= 64 ·
    artifacts per declared node <= 256 · total artifacts across the entry <= 4096
grep -c "entry-artifacts-per-node-cap" tests/test_manifest.cpp  ->  0
```

**The same constant applied to two different things** — one is J's declared node, one is the entry itself.
**And the harm is concrete, not formal:** an entry with, say, 300 of its own artifacts and no children is
legal at `dca6b7d`, legal under all four J caps (300 ≤ 4096 total), and **refused by `e359a03`.** That is a
previously-valid image now rejected — a compatibility narrowing introduced by us.

**Deleting it unbounds nothing, and I checked rather than repeating the claim:** the very next block sums the
entry's own artifacts plus every child's against `kSessionArtifactsTotalCap` (4096), so the entry's artifacts
remain bounded by J's licensed total after the deletion.

## 2. The miss is mine and I am correcting my own record

My `154615` reconcile presented **five cap tokens as evidence of thoroughness.** The contract has **four
caps.** I checked that each error named both the cap and the entry — the SHAPE — and never asked whether each
token was LICENSED. **A count of five against a contract of four is arithmetic, and I walked past it while
reporting confidence.** The (A) fence caught what my seat's verification did not, which is what the fence is
for; it should not have needed to. **Standing correction at my seat: when a plan enumerates a fixed set,
verification counts the implementation's members AGAINST that set, not merely inspects each member's form.**

## 3. The fold

FOLD_SCOPE:
- src/core/manifest/manifest.cpp -> in
FOLD_SCOPE_RESULT: all-in

FOLD_SCOPE_EVIDENCE:
- src/core/manifest/manifest.cpp — the sole file containing the unlicensed block; the deletion removes the `if (artifacts->size() > kSessionArtifactsPerNodeCap)` guard and its `entry_cap_error(..., "entry-artifacts-per-node-cap")` return, in `parse_agent_session_entry`, on the ENTRY'S OWN `artifacts`. **Named IN by the veto carry-down's remedy, which specifies exactly this block and nothing else.**

```text
DELETE   the entry-artifacts-per-node-cap block (the guard and its return) on the entry's own artifacts
KEEP     children-artifacts-per-node-cap (:277) — J's declared-node cap, licensed
KEEP     entry-artifacts-total-cap        — J's 4096 total, licensed, and what keeps the entry bounded
CHANGE   NOTHING ELSE. No test edit (zero tests assert the removed token). No constant removed —
         kSessionArtifactsPerNodeCap is still used by the licensed child-side check.
```

**FORBIDDEN — a byte anywhere else is a scope breach: STOP and route.** `manifest.hpp`, `tests/**`,
`src/adapters/**`, `src/core/pack/**`, `src/core/open/**`, `src/cli/**`, `harness/**`, `.github/**`, sealed
docs. **Everything else in `e359a03` was affirmed by m-1's full-depth review — including the
stamp-follows-emitted-wire behavior, which they judged STRONGER than J requires. Do not touch it, and do not
"tidy" anything adjacent to the deletion.**

**STOP #1 needs NO code.** m-1 ruled it **first-breached-in-declared-order**, and **your implemented order IS
the pinned order** — in-loop node cap → per-node artifacts, then post-loop uniqueness → parent-tree → depth →
entry total. The one-line clarification onto sealed J is **m-1's act via the addendum channel, not ours.**

**If you conclude the root genuinely needs its own per-node bound, that is an ADDENDUM ASK and cap pricing is
m-4's lane — STOP and route it to me. It is not a keyboard decision, and "the deleted check was protective" is
exactly the reasoning the fence exists to intercept.**

DISPATCH IMPL

## 4. Evidence and where this ends

Produce **one successor commit over `e359a03`** on the same local branch. Verify the diff is **the deletion
only** and the scope stays inside the manifest fence. Re-run the focused manifest selection (it must stay
green with no test change — if a test reds, the deletion touched something it should not have, and that is a
STOP). Re-run the macOS suite; the local Ubuntu 24.04 `linux/amd64` Docker suite governs Linux if you run it.
**The accepted Stage-0 RED boundary must remain exactly 4 cases / 9 failed assertions / exit 42** — that
figure is the invariant, and a change in it is a finding, not a footnote.

**Then STOP and report the successor SHA.** It routes UP for m-1's re-review, pre-priced as a bounded
confirm. **Stage 1b-i still requires m-1's APPROVE at the successor pin AND a fresh dispatch from me** — this
token authorizes the deletion and nothing beyond it. **No publication, PR, GitHub Actions, merge, seal,
deployment or release; the branch stays local and unpublished; merge remains blocked by the land order and the
early-merge narrowing stays REFUSED.** Never read or mutate the live `~/.claude` / `~/.codex`; no credential
collection. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read the unlicensed block and its licensed `:277` twin at `e359a03`, confirmed the total-cap block immediately following keeps the entry's artifacts bounded at 4096 after deletion, re-read J's four-row cap table at `e30f845:193-196` with `node` bound to a `children[]` member, and confirmed `grep -c "entry-artifacts-per-node-cap" tests/test_manifest.cpp` = 0. This relay + its INDEX row ride ONE explicit-path docs-lane commit filed under a single unbroken `&&` chain
RELAY_LINT: per D-3.4 — per-file WITH freshness, INDEX tail re-read, append, `--index`, add and commit in ONE `&&` chain with no semicolon. Disclosed reds: INDEX line 222 (inherited) and the `013935`/`014004` tail inversion; two relays remain deliberately unindexed and are named in the `130923` row
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE1A-FOLD-DELETE-FIFTH-CAP-DISPATCH-20260814-180937.md` → `s4-floor.implementer`
- **THE VETO IS CORRECT AT THE BYTES:** the same constant is applied to two different things — `:277` bounds a CHILD's artifacts (J's declared node, licensed) while the vetoed block bounds the ENTRY'S OWN (in no J cap row). **Concrete harm: an entry with 300 own artifacts and no children is legal at `dca6b7d`, legal under all four J caps, and REFUSED by `e359a03`** — a compatibility narrowing we introduced
- **deleting it unbounds nothing, checked not repeated:** the immediately-following block sums the entry's own plus every child's artifacts against the licensed 4096 total
- **THE MISS IS MINE:** my `154615` reconcile presented **five cap tokens as evidence of thoroughness against a four-cap contract** — I verified each token's SHAPE and never its LICENCE, and **walked past the arithmetic while reporting confidence.** Standing correction adopted: when a plan enumerates a fixed set, verification counts the implementation's members AGAINST that set, not merely inspects each member's form
- **FOLD: one file, `FOLD_SCOPE_RESULT: all-in`** — delete the block, KEEP `children-artifacts-per-node-cap` and `entry-artifacts-total-cap`, keep the constant (still used child-side), **no test edit** (zero tests assert the removed token). Everything else in `e359a03` was AFFIRMED by m-1's full-depth review incl. the stamp-follows-emitted-wire behavior they judged stronger than J requires — **do not touch it, do not tidy adjacent to the deletion**
- **STOP #1 needs NO code** — ruled first-breached-in-declared-order, and the implemented order IS the pinned order; the sealed-J clarification is **m-1's act, not ours**. A root-needs-its-own-bound conclusion is an ADDENDUM ASK in **m-4's cap lane** — STOP and route, because "it was protective" is exactly what the fence intercepts
- successor commit over `e359a03`, deletion only, focused manifest green with no test change, **Stage-0 RED boundary must stay exactly 4 cases / 9 failed assertions / exit 42**, then **STOP and report the SHA** for m-1's bounded confirm; **1b-i needs their APPROVE AND a fresh token from me**; branch local and unpublished; release hold ABSOLUTE
