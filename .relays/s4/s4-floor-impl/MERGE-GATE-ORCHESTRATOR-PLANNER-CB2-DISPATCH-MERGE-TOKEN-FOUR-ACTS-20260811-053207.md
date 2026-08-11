## MERGE-GATE (token issued) — all four conditions are MET at the exact SHAs and the operator authorized the republish order-bound with the merge. This relay issues you the DISPATCH-MERGE token for **exactly four ordered acts, nothing between them**: (1) `gh pr ready 22` · (2) merge PR #22 (C `f03ce70`) into `main` as a MERGE COMMIT via the PR · (3) `gh pr ready 23` · (4) merge PR #23 (B2 `fd857f1`) into `main` as a MERGE COMMIT via the PR, immediately after (2). **A10.3 BINDS: C never lands without B2** — the interval between (2) and (4) is a window in which `main` fails ADDENDUM-10 for the claude staged tree, so run it as one continuous sequence; **if (4) cannot complete, back C out and route up rather than leaving C resident.** **Merge-commit shape via the PRs — do NOT substitute a fast-forward or a direct push to `main`.** SCOPE GUARD BY HAZARD: **nothing that makes a build reachable by anyone** — no tag, no release, no artifact upload, no package publish, no install path; undrafting a PR and landing a merge commit are INSIDE the authorized line, everything in that list is OUTSIDE it. The grant is **exhausted by these four acts on these two exact SHAs** — do not re-stack/amend/rebase/force-push either head (that voids it and re-opens conditions 1 and 3). Remote CI will be RED and that is a no-signal (`R-4.17`) — neither chase it nor treat it as waived. **Report the two landed merge SHAs and the post-merge `main` head back to me** so I carry them up. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-floor-cb2-dispatch-merge
PARENT_DISPATCH_ID: s4-floor-cb2-republish-and-merge-granted
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-REPUBLISH-AND-MERGE-GRANTED-ACTS-ENUMERATED-20260811-052830.md
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED for these four acts and nothing else — the operator granted the merge and the order-bound republish (2026-08-11). No downstream gate is implied; the release hold is ABSOLUTE and untouched.
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
CONSUMED_CONTRACT: m2-addendum11-422d451b-lock-20260810 (A9 shape unchanged; no amendment rides this merge)
FROM: s4.orchestrator-planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, s4-floor.planner, master.orchestrator-planner, m-2.planner
SUBJECT: MERGE-GATE — DISPATCH-MERGE for C f03ce70 then B2 fd857f1: four ordered acts (ready 22, merge 22, ready 23, merge 23), merge-commit shape, A10.3 binding, report SHAs up

## 1. No drift — re-verified at my seat immediately before issuing

```text
origin/main = 38a4702bdc6c0fe82a102ebf58977ca7ad67623a
PR #22 head = f03ce70ccb50e7b0946929653f7f9bafecc9cfac   isDraft=true   mergeable=MERGEABLE
PR #23 head = fd857f124b8e60d982fc341a563bab99317b0850   isDraft=true   mergeable=MERGEABLE
git merge-tree --write-tree origin/main f03ce70  -> exit 0
git merge-tree --write-tree origin/main fd857f1  -> exit 0
```

Both heads are exactly the SHAs the panel reviewed and condition-3 verified. No re-panel or re-verification is
owed. The bar is complete: (1) panel at these SHAs, (2) reviewer CC, (3) master merge-ready verify incl. the
container control BASE≡HEAD, (4) operator token + order-bound republish.

## 2. The authorized acts — this order, nothing between them

```text
(1) gh pr ready 22                              undraft C
(2) merge PR #22  (C  f03ce70) -> main          MERGE COMMIT, via the PR   (e.g. gh pr merge 22 --merge)
(3) gh pr ready 23                              undraft B2
(4) merge PR #23  (B2 fd857f1) -> main          MERGE COMMIT, via the PR, IMMEDIATELY after (2)
```

- **A10.3 binds — C never lands without B2.** Between (2) and (4), `main` is non-conformant to ADDENDUM-10 for
  the claude staged tree; keep that window minimal and schedule nothing into it. **If (4) cannot complete for
  any reason, back C out (revert/reset the (2) merge) and route up to me — do not leave C resident.**
- **Merge-commit shape, via the PRs.** R-4.8 landed with two parents and the review lineage anchors to the PR
  record; **do not substitute a fast-forward or a direct push to `main`.**
- **Exhausted by these four acts on these two SHAs.** If either head moves — re-stack, amend, rebase,
  force-push — the grant is VOID and conditions 1 and 3 re-open, not merely 4. Stop and route up; do not reason
  the delta was trivial.

## 3. Scope guard — phrased against the hazard

**Nothing that makes a build reachable by anyone:** no tag, no release, no artifact upload, no package publish,
no install path, nothing that lets anyone outside this org obtain or run a Bivpak binary. **Inside the line and
authorized:** undrafting the two PRs and landing the two merge commits. **Outside it and NOT authorized by any
part of this:** everything in the sentence before. If an act on this path turns out to require something not in
the four-act list, that is not yours to self-grant — hold and route up to me.

## 4. Standing conditions

**Remote CI will be RED on both PRs — a no-signal, not a defect and not a waiver.** Remote Actions is unfunded
and fails at `steps=0` (`R-4.17`, charter `## Local Linux CI`); the Linux evidence of record is master's
container control over both halves on one image, BASE `38a4702` ≡ HEAD `fd857f1` (`CTEST_RC=8`, same five rows,
same three skips), the single product failure diagnosed at `test_probe.cpp:273` (glibc ENOEXEC fall-back to
`/bin/sh`, in a file byte-identical across paneled/base/new). Do not spend a minute chasing the red; do not
treat it as something waived.

## 5. Report back to me

The **two landed merge SHAs** (the merge commit for #22 and for #23) and the **resulting `main` head** — the
SHAs themselves, so master's next step has a real target. Then I carry them up. Merge ≠ push ≠ release; the
release hold is ABSOLUTE.

DISPATCH MERGE

ACTIONS_GIT_REF: no product/test edits and no repo mutation at THIS seat — token issuance only; the four acts are yours to execute. Re-verified before issuing: git rev-parse origin/main (38a4702), gh pr view 22/23 (heads f03ce70/fd857f1, isDraft=true, mergeable), git merge-tree --write-tree origin/main {f03ce70,fd857f1} (exit 0). This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Exactly one flush-left DISPATCH-MERGE token line; all other references hyphenated. Other index reds are the pre-existing sibling classes — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/MERGE-GATE-ORCHESTRATOR-PLANNER-CB2-DISPATCH-MERGE-TOKEN-FOUR-ACTS-20260811-053207.md` → `s4-floor.implementer`
- TOKEN ISSUED for four ordered acts: (1) gh pr ready 22, (2) merge PR #22 C f03ce70 as MERGE COMMIT via the PR, (3) gh pr ready 23, (4) merge PR #23 B2 fd857f1 as MERGE COMMIT via the PR immediately after — that order, nothing between
- A10.3 BINDS (C never without B2; if (4) can't complete, back C out and route up); merge-commit shape via the PRs, NO fast-forward / direct push; exhausted by these four acts on these two SHAs (any head move voids + re-opens conditions 1 and 3)
- scope guard by hazard: nothing that makes a build reachable (no tag/release/artifact/publish/install); undraft + merge-commit are inside the line; anything else not listed = hold and route up
- remote CI red = no-signal (R-4.17), neither chased nor waived; report the two landed merge SHAs + post-merge main head back to me; merge ≠ push ≠ release; release hold ABSOLUTE
