## RECONCILE (slice E Stage 0 at `dca6b7d`) — **the stage is substantively sound and I verified its hardest claim independently: the scope is clean and the five test files are INSERTIONS-ONLY against the dispatched base (0 deletions each), which makes the Stage-0 invariant STRUCTURAL rather than argued — no existing test was even touched, so nothing pre-existing could have changed behavior.** **But the four RED receipts bind `2f39277`, and the head is `dca6b7d`, where all four RED cases have DIFFERENT BYTES** — the control commit changed 48/4 and 58/8 lines in the two RED files, renaming the containment helper and rewriting its call sites inside those very cases. **The receipts describe superseded bytes. That is the measure→edit→hand-over race, and it is mine to catch, not yours to have avoided by intuition.** One bounded re-check owed; nothing else is.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-stage0-review
PARENT_DISPATCH_ID: s4-floor-slice-e-stage0-complete
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — Stage 0 is test-only and unpublished; this review asks for one re-run at the head. Stage 1 still needs the m-1 receipt AND a fresh token from me. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-STAGE0-COMPLETE-PUBLICATION-HELD-20260813-003112.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: RECONCILE — scope and invariant VERIFIED at the bytes; RED receipts bind 2f39277 not the head dca6b7d; re-run the four at the head; FX-A12-3's gated legs carried to Stage 1

## 1. What I verified independently at `dca6b7d` (not accepted on the report)

```text
topology        0db8fdd..dca6b7d -> exactly 2 commits, 2f39277 (reds) then dca6b7d (controls)   CONFIRMED
merge-base      git merge-base dca6b7d origin/main -> 0db8fdd8424…  (the dispatched base)       CONFIRMED
scope           every changed path filtered against the six authorized rows -> ZERO outside     CONFIRMED
                grep -cE '^(src|harness|\.github)/' over the changed set -> 0                   CONFIRMED
totals          34 files, 697 insertions, ZERO deletions                                        CONFIRMED
per-file        the five test files, net vs base: 233/0, 120/0, 104/0, 144/0, 55/0
                -> INSERTIONS ONLY. No existing test was modified at all.                       CONFIRMED
diff --check    0db8fdd..dca6b7d -> clean                                                       CONFIRMED
```

**The insertions-only result is stronger than the report claimed and I want it on the record**, because it
converts the Stage-0 invariant from an argument into a structural fact: with **zero bytes under `src/`** and
**zero deletions anywhere**, no production output and no `collect()` return value can have changed, and no
pre-existing test's meaning can have shifted. **No anchor moved, so no A3 ceremony fired** — correct.

**The `safety-hardening: readelf unavailable` row needs no control run, and here is the stronger argument:**
a hardening row inspects **built product binaries**, and this branch changes **no production byte**. It
therefore cannot have been affected by anything in this stage — inherited by construction, not by
classification. I record it as an environment disclosure and it gates nothing. **Docker not run is within
the token** (test-only stage, all four REDs behaved as designed on macOS); its non-coverage stands stated.

## 2. The one bounded defect — the receipts bind bytes that are not the head

```text
git diff --numstat 2f39277 dca6b7d -- <the two RED files>
  48  4  tests/test_adapter_codex_collect.cpp
  58  8  tests/test_adapter_codex_install.cpp
and inside those changes:
  - require_slice_e_provenance_under(...)     REMOVED from THREE red cases  (3 call sites)
  + require_store_roots_under(...)            the renamed replacement
  - REQUIRE(!workspace_relative.empty()); CHECK(*workspace_relative.begin() != "..")
  + REQUIRE(!relative.empty());               REQUIRE(*relative.begin() != "..")
```

**All four RED cases were edited by the control commit.** The per-key receipts in your report — the
`child_ids` mismatch, `0 == 1`, the missing warning, the `2 == 1` staged outcome — were captured against
`2f39277`. At `dca6b7d` those cases have different bytes. **A RED receipt certifies the bytes it ran on; the
hand-over head is not those bytes.** This is the measure→edit→hand-over race, and I am not treating "the
changes look like refactoring" as a substitute for a run — that inference is exactly what the discipline
exists to refuse.

**I did examine the refactor rather than only flagging it, and it is not a weakening — it is a
strengthening:** the helper was renamed to `require_store_roots_under`, matching R-4.8's landed name, and
its containment assertions went from `CHECK` to `REQUIRE`. **The sandbox guard survives and is stricter.**
So I expect all four to fail identically at the head. **Expecting is not evidencing.**

**OWED — the whole fold, and nothing beyond it:** re-run the four REDs at exactly `dca6b7d`, paste the
receipts, and **state the SHA each receipt was taken at.** Also state whether your aggregate line
(`4 cases | 56 assertions | 9 failed | exit 42`) was already at the head or at `2f39277`; the report calls
it "fresh" without naming the SHA, and that is the one place the ambiguity actually matters. **No new
commit is required if the head is unchanged** — this is a re-run and a report, not an edit.

## 3. Carried to Stage 1 — `FX-A12-3`'s contract legs have not executed

At the head, `FX-A12-3` gates on `REQUIRE(report->sessions.size() == 1U)`, which fails `0 == 1`, so the
three legs that follow **never run**:

```text
CHECK(carried.child_ids == …)                 the CYCLE-MEMBER primary  -- UNEXECUTED
CHECK(sorted_artifacts(carried) == …)         exactly-once carriage     -- UNEXECUTED
REQUIRE(warning != …end()) / CHECK(cursor == primary)   named omitted edge, chains reach primary -- UNEXECUTED
```

**You disclosed this and I am not calling it a defect in Stage 0** — a case that fails is a RED, and a
`REQUIRE` gate is the right shape when the precondition is what is broken. **The obligation it creates is
Stage 1's and I am registering it now so it cannot evaporate:** `FX-A12-3` exists specifically to kill the
**least-of-COMPONENT** algorithm, and the leg that does that — the primary being a CYCLE MEMBER even though
the off-cycle descendant `…0301` sorts first — **is currently an assertion nobody has watched run.** At
Stage 1 it must be shown **executing and passing**, and the honest way to prove it discriminates is to show
it **failing against a least-of-component implementation.** An assertion that has never executed cannot yet
be said to protect anything.

## 4. Everything else in the report reconciles

Four RED keys and the control set match the dispatched Stage-0 list; the fixture subtree is present with
`data-only/` holding `1b`, `4a` and `5` with no test compiled against the absent m-1 member; the credential
decoy is asserted absent from collected streams, archive bytes, member reads and restored output; the three
CLI shapes cover flat bare-hex, flat slug-hex and nested `subagents/workflows/<wf>/` and are stated as AXES
rather than a distribution; the corpus basis is quoted as locked with the `1702` figure appearing nowhere;
publication is held with no push, no PR, no Actions. **D-5.5(a) at hand-up is `0` and is correct for the
reason worth stating precisely: the branch cut point IS `origin/main`, so a merge would publish no prior
commit** — the two commits on top are the stage's own work, not inherited lineage.

## 5. What happens next

Send the re-run receipts at `dca6b7d`. On those, Stage 0 is accepted at this seat and the branch stays
unpublished and unmerged. **Stage 1 still requires BOTH m-1's receipt — re-measured absent at my seat 40
minutes ago and again at this act (`origin/main` = `0db8fdd`, `SessionChild` unchanged, 0 `parent_id` hits)
— AND a fresh `DISPATCH IMPL` from me.** Nothing about Stage 0 authorizes it. Merge ≠ push ≠ release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only verification at `dca6b7d`: topology and merge-base against `0db8fdd`, the full changed-path set filtered against the six authorized rows, the `(src|harness|\.github)` count, `--shortstat` and per-file `--numstat` (insertions-only), `diff --check`, the RED/control commit split, the `2f39277..dca6b7d` delta inside both RED files including the helper rename and the `CHECK`→`REQUIRE` strengthening, the `FX-A12-3` `REQUIRE` gate and the three assertions behind it, and the Catch2 tags on all four RED cases; plus a re-measure of `origin/main`/`SessionChild`/`parent_id`. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-STAGE0-RECEIPTS-BIND-SUPERSEDED-BYTES-20260813-003851.md` → `s4-floor.implementer`
- **VERIFIED AT THE BYTES:** two ordered commits over the dispatched base, merge-base exactly `0db8fdd`, ZERO paths outside the six authorized rows, ZERO files under `src|harness|.github`, 34 files / 697 insertions / **ZERO deletions**, and the five test files **INSERTIONS-ONLY** net vs base — which makes the Stage-0 invariant STRUCTURAL: no production byte and no pre-existing test touched, so nothing emitted or returned could change. `diff --check` clean. No anchor moved, no A3 fired
- **OWED (the whole fold):** the four RED receipts **RE-RUN AT `dca6b7d`** with the SHA stated per receipt — the current receipts bind `2f39277`, and the control commit edited all four RED cases (48/4 and 58/8 lines, helper renamed, call sites rewritten). Also state which SHA the aggregate `4/56/9/exit 42` line was taken at. **No new commit needed** if the head is unchanged
- I examined the refactor rather than only flagging it: `require_slice_e_provenance_under` → `require_store_roots_under` (R-4.8's landed name) with containment `CHECK`→`REQUIRE`. **A STRENGTHENING, not a weakening** — so I expect identical REDs; expecting is not evidencing
- **CARRIED TO STAGE 1:** `FX-A12-3`'s cycle-member/exactly-once/named-edge legs sit behind a failing `REQUIRE` and have **NEVER EXECUTED**. Correct for a RED, but the leg that kills least-of-COMPONENT must be shown EXECUTING and PASSING at Stage 1, and shown FAILING against a least-of-component implementation — an assertion nobody has watched run protects nothing yet
- `safety-hardening: readelf unavailable` is inherited BY CONSTRUCTION (a hardening row inspects built binaries; this branch changes no production byte) — disclosure, gates nothing, no control run needed. Docker non-run is within the token; non-coverage stated
- **Stage 1 needs m-1's receipt (re-measured ABSENT at this act) AND a fresh token from me**; publication, merge, seal, deployment, release all held; release hold ABSOLUTE
