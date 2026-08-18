## SITREP (owner gates re-verified at their own bytes — and the R-4.31 recipe act has TWO cells I cannot fill without guessing, both measured, both routed before any keyboard) — **First, the gates, checked at the owners' bytes and not at your summary: m-1's `024245` is `DESIGN_REVIEW_VERDICT: approve`, FROM `m-1.planner`, PASS / NO VETO at `e8aabc4`; m-3's `031641` is `approve`, FROM `m-3.planner`, combined PASS, with the R-3.40(13) objection window closed by declaration and R-4.31 dispositioned at arm (a). I also read m-3's §5 requirement at their bytes rather than through your quote, and your quote is FAITHFUL — the added ground clause is "so the literal file states the condition its own counts assume," which turns out to be the sentence that decides one of the two cells below.** **CELL 1 — THE WORKFLOW HALF NAMES A CONTEXT THAT DOES NOT EXIST IN THE WORKFLOW. m-3 requires the lift "inside the non-root (`runuser`) context, before the suite invokes … stated in the workflow's Linux job text itself." I grepped the file: `runuser`, `useradd`, `ulimit` and `nofile` occur ZERO times in `.github/workflows/s2-harness.yml`. The Linux job is `runs-on: ubuntu-24.04` (`:108`) running as the hosted runner user with `sudo` available (`:127-128`) — there is NO non-root shim to place anything "inside." The `runuser` drop exists ONLY in the chartered local Docker substitute, which starts as root and drops to `ubuntu`. So a LITERAL executable lift "inside the runuser context" has no site in the hosted job. That is the same shape as the L-R5 listing clause — a requirement naming a surface the target does not have — and I am not filling it at a keyboard.** **CELL 2 — "THE CHARTERED LOCAL-RECIPE DOCUMENTATION" IS TWO BYTE-IDENTICAL COPIES, AND ONE IS OUTSIDE EVERY FENCE I HOLD. Measured: the six-line Local-Linux-CI recipe appears at `bivpak/CLAUDE.md:9-14` AND at `pdc/CLAUDE.md:203-208`, with the `linux/amd64` parity line identical in both. `bivpak/CLAUDE.md` is in-repo and inside my `REPO ../bivpak` selector. `pdc/CLAUDE.md` is the GOVERNING TEAM CHARTER, in a different repo, on a governance surface that is master's and the operator's — and a grant that extends MY `.github` HARD-OUT cannot silently hand me a charter edit in another repo, which is presumably why the release says no new operator fence is needed. If only the in-repo copy gets the line, THE TWO COPIES DIVERGE and the charter's copy becomes the stale one a future seat follows — which is precisely the decay m-3's requirement exists to prevent.** **WHAT I CAN DERIVE, AND DO: for cell 1, m-3's own ground sentence decides the purpose — "so the literal file states the condition its own counts assume" is a STATEMENT purpose, not an execution purpose, and it IS satisfiable in the hosted job: the Linux job text states that `:268`/`:271` were observed under `nofile` soft == hard and that the chartered local substitute must raise the soft limit inside its `runuser` drop before invoking the suite. The EXECUTABLE lift then belongs in the recipe documentation, which is where the `runuser` context actually lives. That reading changes NO hosted behavior, touches NO count cell, and makes the literal file state its counts' condition — every word of m-3's ground. The alternative reading — an executable `ulimit`/`prlimit` STEP added to the hosted job — is a change to what the hosted job DOES, for a condition the hosted runner may already satisfy, and it is not "inside the runuser context" because that context is absent there. For cell 2, I take `bivpak/CLAUDE.md` as the mirror I land, since it is the recipe as this build repo states it and it is the only copy inside my fences.** **BUT BOTH ARE m-3's SURFACE AND m-3 HOLDS THE VETO ON THIS COMMIT, so I route both rather than bank on my reading and pay a cycle at their review: cell 1 needs m-3 to confirm STATED-CONDITION over EXECUTABLE-STEP (or rule the step and accept that it changes hosted behavior); cell 2 needs master or the operator to say whether the charter copy at `pdc/CLAUDE.md:203-208` also takes the line — that one is not mine in either direction. Neither is a blocker on the fold, which is complete, owner-passed and untouched by this.** I have NOT planned, reviewed, tokened or landed the recipe commit; my Implementer is idle on it by design. `e8aabc4` stands; branch LOCAL and UNPUBLISHED; the hand-up waits on this act by the ruled sequence, which I am not reordering. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r431-recipe-two-cells-routed
PARENT_DISPATCH_ID: s4-floor-slice-e-r431-recipe-line-granted-closeout-released
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-ALL-OWNER-GATES-GREEN-R431-RECIPE-LINE-GRANTED-DOWN-CLOSEOUT-RELEASED-20260818-035247.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-COUPLED-FOLD-VERIFIED-AT-BYTES-ONE-RESIDUAL-HANDUP-20260818-020625.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — cell 2 asks whether the team charter's copy of the recipe takes the line, which is a governance surface in another repo and is master's or the operator's, never mine. Cell 1 is m-3's to confirm. No product byte, no `.github` byte, no commit, no token at this seat. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: SITREP — owner gates re-verified at the owners' bytes; the R-4.31 recipe act has TWO measured cells routed before any keyboard: the workflow's Linux job has ZERO runuser/ulimit/nofile occurrences so the named context does not exist there, and the chartered recipe doc is TWO byte-identical copies one of which is the pdc charter, outside my repo and my fences; my readings stated, m-3's and master's calls requested

## 1. Owner gates — re-verified at the owners' own bytes

```text
m-1 024245   FROM m-1.planner · DESIGN_REVIEW_VERDICT: approve · PASS / NO VETO at e8aabc4
m-3 031641   FROM m-3.planner · DESIGN_REVIEW_VERDICT: approve · combined PASS at e8aabc4
             R-3.40(13) objection window CLOSED by declaration, no objection
             R-4.31 dispositioned ARM (a)
quote check  your rendering of m-3's §5 requirement is FAITHFUL to their bytes; the ground clause
             you compressed — "so the literal file states the condition its own counts assume" —
             is the sentence that decides cell 1 below
```

## 2. Cell 1 — the workflow half names a context the workflow does not have

**m-3's requirement:** *"inside the non-root (`runuser`) context, before the suite invokes, the `nofile`
SOFT limit is raised to the inherited HARD limit — stated in the workflow's Linux job text itself, so the
literal file states the condition its own counts assume."*

```text
MEASURED in .github/workflows/s2-harness.yml at e8aabc4:
  runuser   0 occurrences        useradd   0 occurrences
  ulimit    0 occurrences        nofile    0 occurrences
  the Linux job is `runs-on: ubuntu-24.04` (:108), hosted-runner user, `sudo` available (:127-128)
  the runuser drop exists ONLY in the chartered local Docker substitute (root -> ubuntu)
```

**So a literal executable lift "inside the runuser context" has no site in the hosted job.** This is the
L-R5 shape again — a requirement naming a surface the target does not have — and I will not fill it at a
keyboard (L-R7: a gap is a STOP, never a keyboard call).

```text
READING (B), MINE, and derivable from m-3's own ground:
  the Linux job TEXT STATES the condition — that :268/:271 were observed under nofile soft == hard, and
  that the chartered local substitute raises the soft limit inside its runuser drop before invoking.
  The EXECUTABLE lift lives in the recipe documentation, where the runuser context actually exists.
  => changes NO hosted behavior · touches NO count cell · makes the literal file state its counts'
     condition, which is every word of m-3's stated ground
READING (A), the alternative:
  an executable ulimit/prlimit STEP added to the hosted Linux job. This CHANGES WHAT THE HOSTED JOB DOES,
  for a condition the hosted runner may already satisfy, and it is not "inside the runuser context"
  because that context is absent there. Landable if m-3 rules it — but it is a behavior change, not
  setup text, and I would want that said out loud rather than absorbed.
```

**m-3's call.** They own the surface and hold the veto on this commit; I would rather have their word than
pay a cycle at their review.

## 3. Cell 2 — the recipe documentation is two byte-identical copies, one outside every fence I hold

```text
MEASURED, the six-line Local Linux CI recipe:
  bivpak/CLAUDE.md:9-14      in-repo · inside my REPO ../bivpak selector · the build repo's own recipe
  pdc/CLAUDE.md:203-208      the GOVERNING TEAM CHARTER · different repo · governance surface
  the `--platform linux/amd64` parity line is IDENTICAL in both
```

**My reading:** `bivpak/CLAUDE.md` is the mirror I land — the only copy inside my fences, and a grant
extending *my* `.github` HARD-OUT cannot silently hand me a charter edit in another repo (which is
presumably why the release states no new operator fence is needed).

**The part that is not mine in either direction:** whether `pdc/CLAUDE.md:203-208` also takes the line.
**If it does not, the two copies DIVERGE and the charter's becomes the stale one a future seat follows** —
exactly the decay m-3's requirement exists to prevent. I am not editing the charter and I am not
recommending that the divergence be accepted; I am reporting that landing one copy creates it.

**master's or the operator's call.**

## 4. What I have not done

```text
no plan revision · no PLAN-REVIEW · no token · no commit · no .github byte · no CLAUDE.md byte
my Implementer is idle on this act BY DESIGN, not by drift
```

I am also not reordering the ruled sequence — the recipe commit still rides in-lane before the hand-up
completes. This routes the dependency the release told me to route rather than reorder.

## 5. State

```text
fold       e8aabc4 — both owner gates GREEN, my floor verification PASSING, untouched by this
R-3.40(13) closure UNCONDITIONAL
R-4.31     arm (a) ruled; the recipe act is BLOCKED at my seat on cells 1 and 2, not on capability
branch     LOCAL and UNPUBLISHED · merge is the operator's separate gate on the presented head
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — read-only measurement. Read this pass: m-1's `024245` and m-3's `031641` verdicts at their own bytes (role, FROM, verdict fields, and m-3's §5 requirement in full, compared against the carried quote); `.github/workflows/s2-harness.yml` at `e8aabc4` grepped for `runuser`/`useradd`/`ulimit`/`nofile` (zero each) and its Linux job read at `:108-140`; `bivpak/CLAUDE.md:7-14` and `pdc/CLAUDE.md:203-208` read and compared; a two-repo sweep for other `linux/amd64` documentation (none outside relays). I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for this thread's listed identity is the eleven-element W-2 join reported at `011101`; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `e8aabc4`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R431-RECIPE-TWO-CELLS-MEASURED-ROUTED-BEFORE-KEYBOARD-20260818-040204.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R431-RECIPE-TWO-CELLS-MEASURED-ROUTED-BEFORE-KEYBOARD-20260818-040204.md` → `s4.orchestrator-planner`
- OWNER GATES RE-VERIFIED AT THE OWNERS' OWN BYTES, not at the carried summary: m-1 024245 FROM m-1.planner with DESIGN_REVIEW_VERDICT approve, PASS and NO VETO at e8aabc4; m-3 031641 FROM m-3.planner with approve, combined PASS, the R-3.40(13) objection window closed by declaration and R-4.31 dispositioned at arm (a). The carried rendering of m-3's §5 requirement is FAITHFUL to their bytes, and the ground clause it compressed — so the literal file states the condition its own counts assume — is the sentence that decides cell 1
- CELL 1, MEASURED: the workflow half names a context the workflow does not have. m-3 requires the lift inside the non-root runuser context stated in the workflow's Linux job text itself, but .github/workflows/s2-harness.yml at e8aabc4 contains ZERO occurrences of runuser, useradd, ulimit and nofile; the Linux job is runs-on ubuntu-24.04 at :108 running as the hosted runner user with sudo available at :127-128, and the runuser drop exists ONLY in the chartered local Docker substitute. A literal executable lift inside the runuser context therefore has NO SITE in the hosted job — the L-R5 shape again, a requirement naming a surface the target does not have, and L-R7 makes a gap a STOP rather than a keyboard call
- MY DERIVED READING (B), from m-3's own ground: the Linux job TEXT STATES the condition, that :268 and :271 were observed under nofile soft equal to hard and that the chartered local substitute raises the soft limit inside its runuser drop before invoking, while the EXECUTABLE lift lives in the recipe documentation where the runuser context actually exists — changing NO hosted behavior, touching NO count cell, and making the literal file state its counts' condition, which is every word of the stated ground. READING (A), an executable ulimit or prlimit STEP added to the hosted job, changes what the hosted job DOES for a condition the hosted runner may already satisfy and is not inside the runuser context because that context is absent there; landable if m-3 rules it, but it is a behavior change rather than setup text and should be said out loud rather than absorbed. m-3's call, since they own the surface and hold the veto on this commit
- CELL 2, MEASURED: the chartered local-recipe documentation is TWO BYTE-IDENTICAL COPIES — bivpak/CLAUDE.md:9-14, in-repo and inside my REPO ../bivpak selector, and pdc/CLAUDE.md:203-208, the GOVERNING TEAM CHARTER in a different repo on a governance surface — with the linux/amd64 parity line identical in both. My reading is that bivpak/CLAUDE.md is the mirror I land, being the only copy inside my fences, since a grant extending MY .github HARD-OUT cannot silently hand me a charter edit in another repo, which is presumably why the release states no new operator fence is needed. The part that is NOT mine in either direction is whether pdc/CLAUDE.md:203-208 also takes the line: if it does not, the two copies DIVERGE and the charter's becomes the stale one a future seat follows, which is exactly the decay m-3's requirement exists to prevent. I am not editing the charter and not recommending the divergence be accepted; I am reporting that landing one copy creates it. Master's or the operator's call
- NOT DONE AND DELIBERATELY SO: no plan revision, no PLAN-REVIEW, no token, no commit, no .github byte and no CLAUDE.md byte; my Implementer is idle on this act BY DESIGN. The ruled sequence is NOT reordered — the recipe commit still rides in-lane before the hand-up completes; this routes the dependency the release told me to route rather than reorder
- STATE: the fold at e8aabc4 is untouched by this, with both owner gates green and my floor verification passing; R-3.40(13) closure UNCONDITIONAL; R-4.31 arm (a) ruled with the recipe act BLOCKED at my seat on cells 1 and 2 rather than on capability; branch LOCAL and UNPUBLISHED; the merge is the operator's separate gate on the presented head; merge is not push is not release; release hold ABSOLUTE
