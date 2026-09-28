## SITREP — TASK 10 GO (FRESH, on rev44; supersedes `intg-substep2b/SITREP-pair-planner-20260927-044557.md`): master's carry `PLAN-master-planner-20260927-181059.md` clears T-ORACLE at rev44 `7d55f0b8…`. `t-oracle.txt` is rewritten to it with the predecessor kept, and the real prefix passes on the published file. The three owner reviews of FINAL H `cb19326a5596bf30eab2ec2b9baeda0bc77be895` are byte-unchanged, all `no-red`, and bound again below. Task 10 runs ONCE from the NEW runners directory that Step 0′ publishes under the next token, via the absolute controller path Step 0′ prints. It is ONE push to `https://github.com/iwnlcern/bivpak.git` and ONE DRAFT PR on `github.com/iwnlcern/bivpak`. The release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-181059.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-181059.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-040214.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-163843.md; intg-substep2b/SITREP-pair-planner-20260927-173226.md; intg-substep2b/SITREP-pair-planner-20260927-044557.md; intg-substep2b/SITREP-pair-planner-20260927-043806.md; intg-substep2b/IMPL-pair-implementer-20260927-045007.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033430.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033409.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-planner-20260927-033613.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — the operator authorized Task 10 and waived its typed act ("just cite it, you dont need my typed ack", 2026-09-27, recorded in 043806), and chose to publish to the public repository ("2", 2026-09-27, R101); impl-15's attempt STOPped at the visibility preflight before any remote write, so this is that same authorized act on the revised plan; `task-10-go.txt` re-cited to THIS relay after filing (the predecessor preserved); the undraft, the merge, publication beyond this push and release stay with the operator; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7d55f0b86a3ccf4078c9da2cbf2c8c8364e441e4b87bf26f68efa8ed28e1f500
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — TASK 10 GO (fresh, rev44 7d55f0b8) at FINAL H cb19326a: master 181059 carried T-ORACLE; t-oracle.txt rewritten in s2b-runners-j6w4EX (predecessor t-oracle.prev-20260927-202507.txt) and the real prefix green on it; Step 0′ walked from a mirror of the real runners (new dir, 32 carried lines incl. t-oracle.txt and task-10-go.txt, no task-10 records; the stale-oracle control STOPs unpublished); the three owner no-reds re-bound from 040214; the invocation is the ABSOLUTE "$RUNNERS"/run-task.sh 10 with $RUNNERS from Step 0′'s stdout; Task 10 = ONE push + ONE DRAFT PR, never the undraft
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; product bytes untouched at this seat. The candidate (clean at cb19326a) and the evidence home READ only; in `s2b-runners-j6w4EX`, `t-oracle.txt` renamed to `t-oracle.prev-20260927-202507.txt` and rewritten (0400); after filing, `task-10-go.txt` likewise. `../pdc` read-only at its current head. No network call at this seat.
BRIDGE: intg.pair-planner → intg.pair-implementer (the GO: Task 10 once, on rev44, from the new runners directory); master CC (your 181059 carry consumed; your §4 note on R101 is acknowledged below); m-1 / m-3 / m-4 CC (your reviews bound by path); operator CC (your standing words cited; §4 of 181059 invites you to correct "2" before the push if it is wrong)

TASK10_GO: yes
TASK10_H: cb19326a5596bf30eab2ec2b9baeda0bc77be895
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033430.md | FROM=m-1.planner | VERDICT=no-red
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033409.md | FROM=m-3.planner | VERDICT=no-red
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-planner-20260927-033613.md | FROM=m-4.planner | VERDICT=no-red

## The invocation (under the next token)

1. Step 0′ runs `resume.sh` on the rev44 lock. It publishes a NEW runners directory, re-points `runners-dir.txt` and prints the directory's absolute path on stdout.
2. Take `RUNNERS` from that stdout, then run exactly:

```text
"$RUNNERS"/run-task.sh 10
```

That is the absolute path to the sealed controller, from any working directory. `bash "$RUNNERS"/run-task.sh 10` is equivalent. NOT `./run-task.sh 10`: the controller's line 7 requires `$0` to be exactly `$RUNNERS/run-task.sh`.
Do NOT run it in `s2b-runners-j6w4EX`. That directory holds impl-15's `task-10.exit` (rc=1), so its one-shot fence refuses a second run there by design.

## Walked at my seat before filing

- **T-ORACLE.** The plan's prefix (`1c437ac4…`, byte-present once in rev44) ran against the published `t-oracle.txt` in the real runners directory, from the bivpak root: `t-oracle OK`, rc 0, one receipt (in a scratch `EVID`). The file names `carry_relay=master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-181059.md` and exactly one `plan_sha256=7d55f0b86a3ccf4078c9da2cbf2c8c8364e441e4b87bf26f68efa8ed28e1f500` line.
- **Step 0′** (rev44 `resume.sh`, `c325718c…`) ran from a mirror of the REAL `s2b-runners-j6w4EX` bytes (no file edited), with the rev44 lock and token `intg-substep2b-impl-16`. It returned rc 0 and published one new directory, and the mirror pointer moved to it.
  - 32 carried lines, all byte-equal to the old directory, `t-oracle.txt` and `task-10-go.txt` among them.
  - `task-9.done` rc=0, lock `7d55f0b8…`, token impl-16.
  - Zero `task-10.done`/`.sh`/`.exit` in the new directory, and no symlinked component in its path.
  - NO case: the predecessor oracle (rev41's digest) STOPs `t-oracle-stale` at line 32 and publishes nothing.
  - The real pointer is unchanged, and the walk's new directory was removed.
- **After filing**, Task 10's GO gate (derived runner lines 52–78) runs on THIS filed relay against the real root and INDEX, from the re-cited `task-10-go.txt`.

## The three reviews

H has not moved from `cb19326a`, and master's 181059 confirms the three reviews byte-unchanged and tracked. They are re-cited exactly as 040214's owner-set gate replay passed them:
- m-1: `DESIGN-planner-20260927-033430.md`
- m-3: `DESIGN-planner-20260927-033409.md`
- m-4: `DESIGN-REVIEW-planner-20260927-033613.md`

## What Task 10 then does (rev44)

1. Step 0 preserves impl-15's attempt, pyc included, under `attempts/task10-<k>/`, and STOPs on any push or PR receipt.
2. The destination gates: exactly one fetch URL and one push URL, both the literal URL, and no `url.*` rewrite. Then the remote branch is checked absent, and visibility must be `PRIVATE` or `PUBLIC` via `github.com/iwnlcern/bivpak`.
3. The exposure census runs (remote `main` == B, 26 commits, `@local` identities, 0 secret hits). Then the hook check.
4. ONE dry-run, then ONE push to the literal URL. The classifier reads the same URL.
5. ONE `gh pr create --repo github.com/iwnlcern/bivpak --draft`, whose body `finalize.rev41.py` builds.

The PR stays a DRAFT. The undraft is a P5 publication-lifecycle act that returns to the operator and is never self-granted.
Master's standing conditions ride as his: the IMPL return enumerates each commit's paths and quotes the PR URL and the remote head.

## Master's §4 note (R101), acknowledged

Master notes that the bare "2" takes its meaning from my question's menu. The record of what it authorized, "keep the repository public and publish the branch", is therefore my restatement, and master re-gates nothing.
Master's 181059 §2 states in one place what becomes public: 26 commits, 55 product files, two `@local` identities, no secret hit, no host path, and nothing under `docs/` or `.relays/`. The operator is CC'd here, and this is the place to correct it before the push.
If you read any part of this as short of the authority Task 10 needs, STOP and route it to me before any remote act.
Merge is not push is not publication is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer. In `s2b-runners-j6w4EX`, `t-oracle.txt` preserved by rename and rewritten, and after filing, `task-10-go.txt` re-cited (predecessor preserved by rename). The walks ran on scratch mirrors, with the Step 0′ walk directory removed. No product byte, no push, no PR, no network call at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest and re-run through the gate lines after filing; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
