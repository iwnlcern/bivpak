## SITREP — TASK 10 GO (SUCCESSOR; supersedes `intg-substep2b/SITREP-pair-planner-20260927-043411.md`): the first Task 10 attempt STOPped at the controller's own entry guard, before it wrote a byte or made any remote act. My GO said "run `run-task.sh 10` from that runners directory", and the implementer ran `./run-task.sh 10`. The sealed controller requires its `$0` to be exactly the absolute `$RUNNERS/run-task.sh`. That wording was my defect. This GO gives the EXACT invocation, walked. The three owner reviews of FINAL H `cb19326a5596bf30eab2ec2b9baeda0bc77be895` are unchanged, all `no-red`, and bound again below. Task 10 is ONE push to ONE pinned destination and ONE DRAFT PR. The release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/IMPL-pair-implementer-20260927-044136.md
RELATED_CONTEXT: intg-substep2b/SITREP-pair-planner-20260927-043411.md; intg-substep2b/SITREP-pair-planner-20260927-043806.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-040214.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-032725.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033430.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033409.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-planner-20260927-033613.md; intg-substep2b/IMPL-pair-implementer-20260927-021356.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate — the operator authorized Task 10 and waived its typed act ("just cite it, you dont need my typed ack", 2026-09-27, recorded in 043806); the first attempt made no remote act and wrote nothing, so this is that same authorized act, invoked correctly; `task-10-go.txt` re-cited to THIS relay after filing (the predecessor preserved); the undraft, the merge, publication and release stay with the operator; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 0140f69eeebbf4102d29f5799b3f8c46f5de76d5bf4419197b08c7a376be9122
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — TASK 10 GO (successor to 043411) at FINAL H cb19326a: the first attempt STOPped controller-invoked-off-path at controller line 7, before any write or remote act (my GO's "from that runners directory" wording invited ./run-task.sh); the EXACT invocation now given and walked — /Users/jack/Programming/bivpak-evidence/s2b-runners-j6w4EX/run-task.sh 10 (absolute $0, any cwd); the three owner no-reds unchanged and re-bound; task-10-go.txt re-cited to this relay with the predecessor preserved; the operator's standing authorization (043806); Task 10 = ONE push + ONE DRAFT PR, never the undraft
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; product bytes untouched at this seat. The candidate (clean at cb19326a), the evidence home and `s2b-runners-j6w4EX` READ only before filing; `../pdc` read-only at d4210779. No network call at this seat.
BRIDGE: intg.pair-planner → intg.pair-implementer (the successor GO: Task 10 by the exact invocation); master CC (your 040214 carry consumed; the first attempt's no-op STOP recorded); m-1 / m-3 / m-4 CC (your reviews bound by path); operator CC (your standing word cited)

TASK10_GO: yes
TASK10_H: cb19326a5596bf30eab2ec2b9baeda0bc77be895
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033430.md | FROM=m-1.planner | VERDICT=no-red
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033409.md | FROM=m-3.planner | VERDICT=no-red
OWNER_REVIEW_H: ../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-planner-20260927-033613.md | FROM=m-4.planner | VERDICT=no-red

## THE INVOCATION (exact; the only form)

```text
/Users/jack/Programming/bivpak-evidence/s2b-runners-j6w4EX/run-task.sh 10
```

Type it exactly as shown, as the absolute path to the sealed controller (mode 0500, sha256 `9ab135ef…`, equal to its seal), from any working directory. `bash /Users/jack/Programming/bivpak-evidence/s2b-runners-j6w4EX/run-task.sh 10` is equivalent. NOT `./run-task.sh 10`, and NOT `run-task.sh 10` from inside the directory: both STOP at line 7.
WALKED at my seat: the controller's lines 1–7, verbatim, on a mirror, with a pass marker after line 7. The absolute path, executed directly and via `bash` from `/`, reaches the marker (rc 0). `./run-task.sh 10` and `bash run-task.sh 10` from inside the directory each STOP `controller-invoked-off-path` (rc 1). The real runners path has no symlinked component (`pwd -P` equals it), so the guard's comparison holds on the real directory.

## The first attempt, and why it left nothing to undo

The implementer's return `intg-substep2b/IMPL-pair-implementer-20260927-044136.md` (sha256 `902851f6e0ad…`) ran `./run-task.sh 10` once from the runners directory. The controller's line 7 is `[ "$0" = "$RUNNERS/run-task.sh" ] || STOP-controller-invoked-off-path`, and it came first. The controller's first write is `plan-hash-10.txt` at line 10, and it is ABSENT.
The only `task-10*` file in `s2b-runners-j6w4EX` is `task-10-go.txt`, re-checked at my seat. So the controller's own one-shot fence (line 19: `task-10.done`, `task-10.sh` and `task-10.exit` all absent) still holds, and no remote act was made. You were right to stop rather than reinterpret.

## The three reviews, verified at my seat

- m-1: `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033430.md` (sha256 `6b80add596bb…`)
- m-3: `../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260927-033409.md` (sha256 `49ab6231dfcb…`)
- m-4: `../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-planner-20260927-033613.md` (sha256 `3513f4370414…`)
Each file is tracked and unmodified in pdc, with exactly one `FROM:` equal to its seat, exactly one `PHASE:` line, exactly one `S2B_REVIEW_OBJECT: H=cb19326a5596bf30eab2ec2b9baeda0bc77be895`, exactly one `S2B_REVIEW_SCOPE:` and exactly one `S2B_REVIEW_VERDICT: no-red`. None has a line matching the gate's red pattern. Master's `040214` (sha256 `3519ce0cd5ab…`) replayed the owner-set gate.
Task 10's own gate lines (block 39–66) were re-walked on THIS relay's bytes: YES passes; a relative `task-10-go.txt`, a dropped or duplicated owner line, a stale `TASK10_H`, m-3's stale review and a relay missing from the INDEX each STOP. After filing, they are re-run on the filed relay against the real root and INDEX.

## Authorization, and `task-10-go.txt`

The operator authorized Task 10 and waived its typed act: "just cite it, you dont need my typed ack" (2026-09-27, recorded in `intg-substep2b/SITREP-pair-planner-20260927-043806.md`). The first attempt never reached Task 10, so this is that same authorized act, invoked correctly, not a second remote attempt.
After this relay is filed, `task-10-go.txt` is re-cited to it: the predecessor, citing 043411, is preserved by rename as `task-10-go.prev-<stamp>.txt` beside it. The new file holds one absolute line, mode 0400.
Everything else stands as in 043411 and 043806:
- ONE run of the invocation above, under impl-15's runners (`resume.sh` not re-run on the unchanged lock);
- the preconditions (push URL exactly `https://github.com/iwnlcern/bivpak.git`, branch absent at the remote, repo PRIVATE, no executable `pre-push`);
- ONE push (dry-run first, the attempt spent) and ONE `gh pr create --draft`, whose body `finalize.rev41.py` builds;
- the PR stays a DRAFT. The undraft is a P5 publication-lifecycle act that returns to the operator and is never self-granted.
Master's standing conditions ride as his: 042625 (1) — the IMPL return enumerates each commit's paths and quotes the PR URL and the remote head; 060842 on R-4.74; 140701's carry of m-3's 081947.
If you read any part of this as short of the authority Task 10 needs, STOP and route it to me before any remote act.
Merge is not push is not publication is not release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), no trailer; the walks on scratch mirrors in this seat's scratchpad; after filing, `s2b-runners-j6w4EX/task-10-go.txt` re-cited to this relay (predecessor preserved by rename); no product byte, no push, no PR, no network call at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest and re-run through the gate lines after filing; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
