## MERGE-GATE — the OPERATOR'S UNDRAFT RULING, passed down to you as routed. The operator's typed word, 2026-09-30, is "the impl can undraft it". Master routes it and registers it as R-4.97 in `MERGE-GATE-master-planner-20260930-042236.md`. You MAY run exactly `gh pr ready 28` and nothing else, then read back four values and report them UP through me. This is NOT the merge token: condition 4 stays the operator's and PENDING. Do not run any part of the landing act.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-planner-20260930-042236.md
RELATED_CONTEXT: intg-substep2b/MERGE-GATE-pair-planner-20260930-032254.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260930-032028.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the condition-4 merge token is still owed and still the operator's (a BARE `DISPATCH MERGE` FROM operator, filed from the intg engine's operator seat); only the undraft is delegated, by the operator's own word (R-4.97); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == H by ls-remote at this filing; PR #28 OPEN, isDraft true, MERGEABLE, head H, read at this filing)
TARGET_BRANCH: main — untouched by this act; the landing is §7 of the approved packet 07418d95, and runs only under the operator's token
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (ls-remote at this filing)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, operator, master.master-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — the operator's undraft ruling (R-4.97, via master 042236), passed down: run exactly `gh pr ready 28`, then read back state, isDraft, headRefOid and mergeable (expected OPEN, false, cb19326a5596bf30eab2ec2b9baeda0bc77be895, MERGEABLE), and report the four values UP to me. Nothing else: no PR edit, label, comment, reviewer request, close or merge button, no push, and no step of §7 (do not create $EVID/landing, do not merge, do not derive M). The merge token is NOT delegated and remains the operator's; cell 4 is PENDING.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; the approved packet (07418d95), the plan (4832b147) and the evidence untouched; PR #28 read with `gh pr view` only at this seat; no forge mutation by this seat
BRIDGE: intg.pair-planner → intg.pair-implementer (the operator's delegated undraft, with its exact bounds); master CC (routed as you set it: undraft first, token second); operator CC (your word is what authorizes this act, and your token is still what authorizes the merge)

## The ruling, with its bounds (master 042236 §1, carried exactly)

```text
DELEGATED   the undraft of PR #28, to intg.pair-implementer, by the operator's typed word 2026-09-30
THE ACT     `gh pr ready 28` and nothing else
READ BACK   state, isDraft, headRefOid, mergeable — four values, reported UP through the pair-planner
            expected: OPEN, isDraft false, headRefOid cb19326a5596bf30eab2ec2b9baeda0bc77be895, MERGEABLE
NOT         any PR body edit, base change, label, reviewer request, comment, close, reopen, or merge button;
            any push; any tag; any release. The undraft is not a token and authorizes no later step.
ORDER       undraft FIRST, token SECOND — unchanged. If the token never issues, the PR simply stands
            undrafted at H, which is a reversible state (`gh pr ready --undo`).
```

## Before and after (a suggestion, not a widening)

- **Before the act:** read `gh pr view 28 --json state,isDraft,headRefOid,mergeable` and require OPEN, isDraft true, head H. If the head is not H, or the PR is not OPEN, STOP and report; do not undraft.
- **The act:** `gh pr ready 28`, run once. Record its rc.
- **After:** read the four values again and report them all UP, with the before-read and the rc. If isDraft is still true or the head moved, report that; do not retry beyond what you judge the act itself to be.
- **Master 042236 §3:** do NOT touch the packet, do NOT create `$EVID/landing`, do NOT pre-derive M, and do NOT run any part of §7. Step (0) STOPs `landing-dir-exists` if that directory exists early.
- **Credentials:** the GitHub token stays out of every file and container, and no `GH_DEBUG`.

After your report I carry the four values to master. The token remains the operator's to file from the intg engine's operator seat. If it issues, §7 runs exactly as approved at `07418d95…`.

Nothing in this relay is a merge token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (a path-scoped commit follows), no trailer; no forge mutation at this seat; no packet, plan, evidence or product byte changed.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
