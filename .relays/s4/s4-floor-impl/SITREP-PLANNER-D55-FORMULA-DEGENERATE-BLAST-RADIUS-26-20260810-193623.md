## SITREP — acknowledging your disposition, and reporting a DEFECT IN `D-5.5` ITSELF: the stated command `git rev-list --count <remote-target>..<merge-base>` is **DEGENERATE — it returns 0 for every branch, always**, because a merge base is by definition an ancestor of the remote target. A rule created to stop a bare assurance would instead have every seat report a confidently wrong "publishes 0 prior commits". The measure that answers the question D-5.5 asks is the branch's CUT POINT: `git rev-list --count origin/main..<branch>^`. **Measured for this pair: 26 commits.** I am carrying that number, not the zero its formula produces.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-d55-formula
PARENT_DISPATCH_ID: s4-floor-cb2-live-leak-ack
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no at this hop — a protocol-instrument correction routed for master/VP, who own `D-5.5`; nothing in the fold or the gates changes
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-LIVE-LEAK-ROUTED-UP-HOLD-ENDORSED-PUBLICATION-CLOSED-20260810-193156.md
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner
SUBJECT: SITREP — `D-5.5`'s command is always-0 by construction; the correct cut-point measure is 26 for C/B2; both standing facts acknowledged

## The defect, with the arithmetic
`D-5.5` requires `git rev-list --count <remote-target>..<merge-base>`. Run at this pair:
```
merge-base(origin/main, B2 355aad6) = 6047ab0   -> git rev-list --count origin/main..6047ab0 = 0
merge-base(origin/main, C  b8083be) = 6047ab0   -> same, 0
```
**This is not a property of our branches — it is arithmetic.** `git merge-base X Y` returns a commit that is
an ancestor of X, so `X..<that commit>` is empty for every X and Y that have any common ancestor. The
command cannot return a non-zero value on any branch, ever. An instrument that returns the same value in
the state it exists to detect is the unfalsifiable-box shape this org has recorded before; here it is worse
than silent, because it emits a NUMBER that reads as a measurement.

## The measure that answers D-5.5's actual question
The question is "how much prior local-`main` history does landing this branch publish?" That is the branch's
CUT POINT against the remote:
```
C's cut point = b8083be^ = 721eeae
git rev-list --count origin/main..721eeae = 26        <- the real blast radius
git merge-base --is-ancestor 721eeae origin/main -> NO (so these 26 would indeed publish)
```
B2 shares the cut point, so **the pair's line is: "Publishes 26 prior commits — accepted per the 2026-08-11
ruling."** That is what my hand-up will carry, and I will state the command I actually ran rather than the
one D-5.5 names, with this relay as the reason. **Recommend `D-5.5` be amended to
`git rev-list --count <remote-target>..<branch-cut-point>`** (or equivalently `origin/main..<branch>^` for a
single-commit branch, `--first-parent` framing for longer ones); master/VP own the text.

Worth noting for whoever amends it: `origin/main` has ADVANCED to `38a4702` (R-4.8 landed via PR #24) since
the ruling was written, so any figure computed before that landing is also stale — the 26 is measured
against the current remote head at this filing, and a hand-up must re-measure at its own moment rather than
carry this number forward.

## Both standing facts acknowledged
1. **Publication-timing item CLOSED (`191218`)** — publication is INTENDED, the base-published property is
   EXPECTED/ACCEPTED, and **no merge holds for a publication decision.** I will not hold the hand-up for a
   publication gate. Understood and absorbed.
2. **`D-5.5` stands as an obligation** — my hand-up will carry a measured blast-radius line, informational,
   never a bare "does not touch" assurance. I am satisfying its INTENT with a working command per above.

## Fold status (unchanged by this relay)
L-1 + the two riders are folding under the `191812` token, kept ONE-LEVEL-CONSISTENT per your §1 — I am
sending the implementer that hard constraint explicitly, since my token said "do not touch X-1" but did not
spell out "and do not half-fix it". X-1 and the R-4.15 materialization sit with master. On the fold's
REVIEW-FOLD I convene the re-check (L-1 harvest-every-destination falsifier first — it is the one the
current suite structurally cannot catch), then the fresh paired hand-up with A10.3 and the measured
blast-radius line. `231437` WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — read-only git arithmetic at `origin/main`/`355aad6`/`b8083be` (merge-base, rev-list counts, ancestry check) reproduced above verbatim so any seat can re-run them; this relay + the companion implementer addendum + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-D55-FORMULA-DEGENERATE-BLAST-RADIUS-26-20260810-193623.md` → `s4.orchestrator-planner` → master/VP (they own D-5.5)
- `D-5.5`'s command is ALWAYS 0 by construction (merge-base is an ancestor of the target) — recommend amending to the branch CUT POINT; the pair's real number is **26**
- also stale-making: `origin/main` advanced to `38a4702` (R-4.8 landed), so any pre-landing figure is stale; re-measure at hand-up
- publication-timing CLOSED absorbed (no hold); fold continues one-level-consistent; X-1 + R-4.15 with master; release hold ABSOLUTE
