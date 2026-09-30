## MERGE-GATE — the Master Reviewer APPROVES packet revision 3 at the exact hash (`MERGE-GATE-master-reviewer-20260930-032028.md`: `07418d95aa8637bee7b6c8846132e26aa692ffefb34f2928b44d7f5a8eb22ea8`, commit d1552ff). F-2B-VP-1 and F-2B-VP-2 are CLOSED, and the hold on presentation is discharged. Per that relay's next route, this returns the clean verification to you for your own-bytes check and presentation. The packet is HELD at H `cb19326a`: cells 1–3 are DONE, and cell 4 is PENDING and the operator's.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260930-032028.md
RELATED_CONTEXT: intg-substep2b/MERGE-GATE-pair-planner-20260930-025901.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260930-021153.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260930-012837.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — cell 4 is the operator's: after your own-bytes check and presentation, the operator undrafts PR #28 and files a BARE `DISPATCH MERGE` TO intg.pair-implementer under ../bivpak/.relays/intg/ (grantor set excludes the pair-planner); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == H by ls-remote at this filing; PR #28 OPEN, draft, MERGEABLE, head H)
TARGET_BRANCH: main — the TRUE local merge under the operator's token, M derived once, the census and both record clauses on M, then the ONE push of M (R-4.52), per packet §7
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (ls-remote at this filing)
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — the Master Reviewer approves packet revision 3 (07418d95 @ d1552ff) at the exact hash on its own controls: a positive plus eleven negatives, including a /dev/null read-back sink, a pre-receive rejection and an ls-remote fault. F-2B-VP-1 and F-2B-VP-2 are CLOSED; plan rev53 4832b147 is unchanged; §7 run.zsh is 666e2e9b. It returns to you for your own-bytes check and presentation; cell 4 is the operator's. The live bytes equal the approved digest at this filing; remote main == B, branch == H; PR #28 is a draft.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; the packet (07418d95), the plan (4832b147) and the walks untouched since the approved commit; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-planner (the clean exact-packet verification, for your own-bytes check and presentation); operator CC (after that presentation: your undraft of PR #28, then your bare token under .relays/intg); implementer CC (packet §7 is your landing act if the token issues); Master Reviewer CC (your approve is what this carries)

## What is presented

- **The packet:** `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md`, revision 3, sha256 `07418d95aa8637bee7b6c8846132e26aa692ffefb34f2928b44d7f5a8eb22ea8`, commit d1552ff. Its live bytes were re-hashed equal at this filing.
- **The plan of record:** rev53 `4832b147…`, approved by plan-review-54 and verified at your bytes (012837), with the T-ORACLE carry installed (real prefix rc 0).
- **Cells:**
  - (1) the local suites at H on both platforms: DONE (c11 head gate; the harness-selftest family red disclosed under R-4.35, never an all-green claim);
  - (2) the parity container reached ctest: DONE;
  - (3) the owner reviews: DONE (m-1 033430, m-3 033409, m-4 033613, re-hashed unchanged by the Master Reviewer);
  - (4) the operator's merge token: PENDING.
- **The landing act (§7)** is six runnable zsh blocks. The Master Reviewer executed them unedited, extracted by its own section and fence parsing (`666e2e9b…`), and the positive pushed its scratch M to a local bare repo with `landing-pushed-ok`:
  - (0) three pins;
  - (1) the invariants, your advisory pre-check, and the pinned history line on both parents, all before the merge;
  - (2) the merge and M derived once;
  - (3) the census on M;
  - (4) the index and history clauses on M;
  - (5) ONE push of M, receipts checked.
- **The local record** is retained and unpublished (R-4.88 arm (b), R-4.95 path-scoped). The Master Reviewer re-hashed all 2,342 entries at `187a1a10…`.

## The Master Reviewer's non-blocking caveat, carried as stated

§7's introductory phrases ("any STOP means NO push"; the pre-push receipts before the dry run) are to be read with step (5)'s explicit exceptions:
- the dry-run receipt can only be kept after the dry run;
- the attempt marker follows it;
- a post-push STOP does not undo the attempt.

The reviewer accepts the disclosed and measured order, not a claim of zero invocations in those three cases. The two record-receipt controls still require, and achieve, zero invocations. I have not changed the packet for this, because a byte change would un-approve the exact digest. If you want the wording tightened before you present, say so, and it becomes a revision 4 with a fresh exact-hash verification.

Nothing in this relay is a token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (a path-scoped commit follows), no trailer; no packet, plan, evidence or product byte changed since d1552ff; no remote write.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
