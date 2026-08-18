## IMPL — the W-2 join re-run FRESH and passing; the ONE R-4.31 recipe commit is DISPATCHED, with both review clarifications adopted as binds and one of them owning a defect in my own plan

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-r431-recipe-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-r431-recipe-plan-review-rev3
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-REV3-S17-R431-APPROVE-CONTENT-ANCHORS-20260818-144652.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R431-KEYBOARD-RELEASED-READING-B-CONFIRMED-MIRROR-FROM-CHARTER-BYTES-20260818-143817.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the landed commit returns to m-3 for a FRESH byte review on their own workflow surface, which the earlier combined PASS does not cover. R-4.31 closes at master's pen only on that review. The merge remains the operator's SEPARATE gate on the presented head. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: IMPL — R-4.31 recipe commit dispatched on the 144652 approve; W-2 join RE-RUN fresh at token time and passing on all eleven elements; both clarifications adopted as binds, including my own A20 position-anchor defect owned and replaced by job/key evidence; two paths, one commit, then m-3

DISPATCH IMPL

## 1. The W-2 join — RE-RUN at token time, not carried from `011101`

**The join is a TOKEN-TIME instrument. I did not reuse the `011101` result** — two of its elements are
time-sensitive and pdc has moved since (master committed `47b70f8` and `184a9c2` in between).

```text
SELECTOR   REPO ../bivpak · RELAY_ROOT .relays/s4/s4-floor-impl · PLAN_LOCK_ID
           s4-floor-slice-e-plan-20260812 · DESIGN_BINDINGS = rev3 §1's one-item list, rev3 having
           passed local plan-review at 144652 · ERROR_CLASS the cross-repo lineage red, measured
           firing on rev3 and naming this lock alone                                          PASS

1 OWNER LOCK DECLARATION  184619 · FROM m-1.planner
    DESIGN_LOCK_ID m1-addendum-L-10c8e8e6-lock-20260817
    LOCKED_DESIGN_SHA256 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
    LOCKED_DESIGN_COMMIT 8c7f9281d538704419ea7142a417495eec46e8a5                             PASS
2 VP EXACT-PIN APPROVAL   154000 · FROM master.orchestrator-reviewer · approve · same SHA + commit  PASS
3 GATE DISPOSITION        144843 · FROM m-1.implementer · approve · same SHA                  PASS
4 PRECEDENCE              144843 < 154000 < 154351 < 184619 < 144504 (rev3) < 144652 (approve)
                          < this token                                                        PASS
5 NO LATER SUPERSESSION   RE-MEASURED NOW: master/ARCHITECTURE.md's L row still reads
                          LOCKED `m1-addendum-L-10c8e8e6-lock-20260817`, exactly one occurrence PASS
6 NO LATER UNLOCKED EDIT  RE-MEASURED NOW: live L doc still hashes b3599511…; locked->live diff
                          still ONE hunk `14,18c14,47` inside the Status block; last commit
                          touching the doc still 437520e, the lock declaration itself          PASS
```

**Eleven elements, zero mismatches.** Elements 5 and 6 were re-measured at this hour precisely because
they are the two that can decay between tokens.

## 2. The review's two clarifications — ADOPTED AS BINDS, and the first is a defect in my own plan

### 2.1 Content anchors govern EVIDENCE too — my A20 was wrong and I am replacing it

I wrote §4.4 of rev3 making content anchors a bind because a bare position in a living artifact expires
silently — and then, one section later, **I wrote A20 citing `:68` / `:71` / `:268` / `:271`.** Living
positions, as acceptance evidence, in the same plan that bans them. My Implementer caught it. **The rule
was right and I broke it in the act of writing it** — which is exactly the shape m-3 caught in master's cut,
now three instances in three days from one habit.

**A20 is REPLACED (this supersedes rev3's A20):**

```text
A20  the four count cells and the identity line are unchanged from e8aabc4, EVIDENCED BY JOB AND
     MAPPING KEY, never by line position:
       macOS job   want.successes = 410   want.skips = 3
       Linux job   want.successes = 412   want.skips = 1
       both jobs   want.failures = 0      want.expectedFailures = 0
       m-3's identity line   compared BY EXACT CONTENT (and by its sha256), not by position
     Neither the landed comment NOR the implementation report may cite these by living line position.
     The historical `:68`/`:71`/`:268`/`:271` references in rev0-rev3 identify the e8aabc4 cells for
     reading only; they are NOT durable acceptance evidence and must not be used as such.
```

### 2.2 The comment IS on m-3's owned surface — my wording was loose and the correction stands

rev3 said S-17 "touches neither owner's reviewed surface." **The correct reading, adopted:** S-17 lies
outside the prior `e8aabc4` verdict FENCES and does not reopen their substance — **but the workflow IS
m-3's owned surface, so the fresh m-3 byte review on the landed commit is MANDATORY and cannot be elided
by quoting the earlier combined PASS.** That distinction is load-bearing: "outside the fence" and "needs no
new review" are different claims, and my phrasing blurred them.

**Any token that treated positions as acceptance anchors, or the prior m-3 PASS as covering this comment,
would be invalid. This one does neither.**

## 3. What implements

### 3.1 The workflow half — statement text only

```text
WHERE     ONE multi-line Python comment IMMEDIATELY ABOVE the Linux count gate's `want = {` mapping,
          inside the existing Python heredoc — closer to the content the condition qualifies than the
          step heading, and incapable of altering YAML or shell execution
CONTENT   the approved self-relative shape (repository indentation for the heredoc is not part of the prose):
            # The `want` counts in this job were observed with the `nofile` soft limit equal
            # to the hard limit. The chartered local substitute raises the soft limit to the
            # inherited hard limit inside its `runuser` drop before invoking the suite.
FORBIDDEN no executable step · no run-line touched · no `want` value · no `expected_skips` member ·
          NO line-number citation of any kind, including its own
```

### 3.2 The mirror half — bytes from the charter object, hash to check

```text
SOURCE    pdc object 184a9c2 (full 184a9c2e676d59150e4a220be4c2829a54b019e1, ancestor of pdc HEAD —
          re-confirmed at my seat), `CLAUDE.md` lines 206-210
WHERE     bivpak/CLAUDE.md, directly AFTER the parity bullet at `:11`
CHECK     hash the LANDED five-line block; it must equal
          6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd
RULE      COPY FROM THE CHARTER OBJECT. The plan, the review and this token are CHECKS, not typing
          sources — my hash, my Implementer's independent re-derivation and this line all agree, and
          none of them is where the bytes come from.
```

### 3.3 Absolute

```text
ZERO `want` values move · ZERO `expected_skips` members move · no run-line · no product, test or fixture byte
ONE commit, message NAMING R-4.31, touching EXACTLY the two paths below
NO re-run is owed — the green under the stated condition is already observed (412/0/1)
```

## 4. Scope

SCOPE_DIFF:
- .github/workflows/s2-harness.yml -> in
- CLAUDE.md -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `.github/workflows/s2-harness.yml` — §3.1 ONLY: one Python comment immediately above the Linux job's `want = {` mapping, statement text, self-relative. No executable step, no run-line, no `want` value, no `expected_skips` member. The cells landed at `e8aabc4` are untouched.
- `CLAUDE.md` — §3.2 ONLY: the mirror bullet after `:11`, byte-identical to the charter object's `CLAUDE.md:206-210` at `184a9c2`. No other line of this file.

**OUT — a discovered need is a STOP to me, never a licence:** every other byte of `.github/**`; every product, test and fixture path (the fold at `e8aabc4` is landed and owner-passed — reopening it is not in this act); `pdc/**` entirely, the charter included; any third path; any executable workflow change (m-3 declined reading (A) out loud, and a fresh hosted-behavior proposal routes fresh, not through this token).

## 5. Acceptance

```text
A16  the workflow change is a COMMENT ONLY — no executable line, no run-line, no `want` value, no
     `expected_skips` member changed
A17  the comment contains NO line-number citation of any kind, including its own
A18  the comment states BOTH ruled halves
A19  the landed CLAUDE.md block hashes EQUAL to 6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd
     — report the hash you computed of what YOU landed
A20  as REPLACED in §2.1 — by job and mapping key, never by position
A21  ONE commit, message names R-4.31, touching exactly the two paths in §4
```

## 6. Return path

```text
land      the ONE commit, in-lane BEFORE the hand-up completes
route     to m-3 for a FRESH byte review — their surface, their veto; the earlier combined PASS does
          NOT cover this comment (§2.2)
then      R-4.31 closes at master's pen on m-3's PASS; s4's close-out and the hand-up complete on ONE
          finished head, and the MERGE is the operator's separate gate on that head
```

**Standing constraints unchanged:** GitHub Actions NOT invoked; branch stays LOCAL and UNPUBLISHED — no
push, no PR, no merge, no seal, no publication; live `~/.claude` / `~/.codex` never read-for-mutation or
written; no credential collection. **Any gap rev0–rev3 plus §2's binds do not decide is a STOP to me**,
never a keyboard call.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — this relay delegates. Read-only this pass: the `144652` approve read in full; rev3 re-hashed from BOTH the worktree and the `3099cee` blob (`c681315d…`, equal to each other and to the review's declared value); the W-2 join RE-RUN — elements 1-3 re-read at `184619`/`154000`/`144843` for their identity fields, element 5 re-measured against `master/ARCHITECTURE.md`'s L row, element 6 re-measured by re-hashing the live L doc (`b3599511…`), re-diffing it against `8c7f9281` (one Status-block hunk `14,18c14,47`) and re-checking its last commit (`437520e`); `184a9c2` re-resolved to its full SHA and re-confirmed an ancestor of pdc HEAD. I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before filing (D-5.10), per-file WITH freshness and the exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for the listed identity is the eleven-element W-2 join re-run in §1 of this relay; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `e8aabc4`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-S17-R431-RECIPE-DISPATCH-IMPL-TOKEN-20260818-145233.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-S17-R431-RECIPE-DISPATCH-IMPL-TOKEN-20260818-145233.md` → `s4-floor.implementer` — LIVE bare implementation token, parented to the `144652` rev3 plan-review approve
- THE W-2 JOIN WAS RE-RUN AT TOKEN TIME AND NOT CARRIED from the 011101 result, because two of its elements are time-sensitive and pdc moved in between with master's 47b70f8 and 184a9c2. All eleven elements PASS: the selector's five with rev3's one-item list now the current coverage since rev3 passed local plan-review at 144652; element one, the owner lock declaration at 184619 from m-1.planner with the complete tuple; element two, the VP exact-pin approval at 154000 from master.orchestrator-reviewer with the same SHA and commit; element three, the gate disposition at 144843 from m-1.implementer; element four, precedence with every artifact before this token; element five RE-MEASURED NOW, ARCHITECTURE.md's L row still reading LOCKED m1-addendum-L-10c8e8e6-lock-20260817 with exactly one occurrence; element six RE-MEASURED NOW, the live L doc still hashing b3599511, the locked-to-live diff still one Status-block hunk, the last commit touching it still 437520e. Zero mismatches
- CLARIFICATION ONE ADOPTED, AND IT IS A DEFECT IN MY OWN PLAN THAT I OWN: rev3's section 4.4 made content anchors a bind because a bare position in a living artifact expires silently, and one section later I wrote A20 citing the four count cells BY LIVING POSITION as acceptance evidence — the rule was right and I broke it in the act of writing it, the third instance in three days from one habit. A20 IS REPLACED: the four counts and the identity line are evidenced BY JOB AND MAPPING KEY, macOS want.successes 410 and want.skips 3, Linux want.successes 412 and want.skips 1, both jobs want.failures 0 and want.expectedFailures 0, and m-3's identity line compared BY EXACT CONTENT and its sha256; neither the landed comment nor the implementation report may cite these by living line position, and the historical position references across rev0 through rev3 are reading aids only and are NOT durable acceptance evidence
- CLARIFICATION TWO ADOPTED: rev3's phrase that S-17 touches neither owner's reviewed surface was loose. The correct reading is that S-17 lies outside the prior e8aabc4 verdict FENCES and does not reopen their substance, but the workflow IS m-3's owned surface, so the FRESH m-3 byte review on the landed commit is MANDATORY and cannot be elided by quoting the earlier combined PASS. Outside the fence and needs no new review are different claims and my phrasing blurred them
- WHAT IMPLEMENTS: the workflow half is ONE multi-line Python comment IMMEDIATELY ABOVE the Linux count gate's want mapping inside the existing heredoc, in the approved self-relative three-line shape stating both ruled halves, with no executable step, no run-line, no want value, no expected_skips member and NO line-number citation of any kind including its own; the mirror half copies the five-line bullet FROM THE CHARTER OBJECT 184a9c2 at CLAUDE.md lines 206 through 210 into bivpak/CLAUDE.md directly after the parity bullet, with the landed block hashed and required to equal 6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd — the plan, the review and this token are CHECKS and not typing sources
- ABSOLUTE: zero want values move, zero expected_skips move, no run-line, no product test or fixture byte; ONE commit naming R-4.31 touching exactly the two scope paths; NO re-run owed since the green under the stated condition is already observed at 412 successes, 0 failures and 1 skip. OUT and a STOP if needed: every other .github byte, every product test and fixture path since the fold is landed and owner-passed, pdc entirely including the charter, any third path, and any executable workflow change since m-3 declined reading (A) out loud and a fresh hosted-behavior proposal routes fresh rather than through this token
- RETURN PATH: land the one commit in-lane BEFORE the hand-up completes, route it to m-3 for a FRESH byte review on their own surface, then R-4.31 closes at master's pen on m-3's PASS and s4's close-out and hand-up complete on ONE finished head with the MERGE remaining the operator's separate gate. Actions NOT invoked; branch LOCAL and UNPUBLISHED; live ~/.claude and ~/.codex never read-for-mutation or written; no credential collection; any gap the plans and these binds do not decide is a STOP to me; merge is not push is not release; release hold ABSOLUTE
