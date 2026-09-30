## MERGE-GATE — PR #28 is UNDRAFTED under the operator's R-4.97, and the four values are exact, independently re-read at my seat: OPEN, isDraft false, headRefOid `cb19326a5596bf30eab2ec2b9baeda0bc77be895`, MERGEABLE. The implementer's receipt is `intg-substep2b/MERGE-GATE-pair-implementer-20260930-044549.md` (`gh pr ready 28` rc 0, run once). Remote main == B and the branch == H. `$EVID/landing` is absent. Cell 4, the operator's bare merge token, is now the only open condition.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/MERGE-GATE-pair-implementer-20260930-044549.md
RELATED_CONTEXT: intg-substep2b/MERGE-GATE-pair-planner-20260930-043515.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-planner-20260930-042236.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260930-032028.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — cell 4: the operator's BARE `DISPATCH MERGE` TO intg.pair-implementer, FROM operator, filed from the intg engine's operator seat under ../bivpak/.relays/intg/ (master 042236 §2); nothing here is or substitutes for it; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == H by ls-remote at this filing; PR #28 OPEN, isDraft false, MERGEABLE, head H, read at this filing)
TARGET_BRANCH: main — unchanged at B; the landing is §7 of the approved packet 07418d95, run only under the operator's token
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (ls-remote at this filing)
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — undraft DONE under R-4.97: `gh pr ready 28` rc 0 (run once, by the implementer, 044549). The four values were re-read at my seat: OPEN, false, cb19326a5596bf30eab2ec2b9baeda0bc77be895, MERGEABLE. main == B, the branch == H, $EVID/landing absent, and the packet 07418d95 untouched. Cell 4, the operator's bare merge token from the intg operator seat, is the only open condition; the release hold is ABSOLUTE.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; no forge mutation at this seat (PR #28 and the refs read only); packet, plan and evidence untouched
BRIDGE: intg.pair-planner → master.master-planner (the undraft receipt, so the order master set can proceed: undraft first, token second); operator CC (the undraft you delegated is done; the token is yours when you choose, from the intg operator seat); implementer CC (hold: §7 runs only under the operator's token)

## The receipt, verified

```text
implementer pre-read    OPEN, isDraft true,  head cb19326a…, MERGEABLE; remote branch == H, main == B, landing-dir absent
the act                 gh pr ready 28 -> rc 0, "Pull request iwnlcern/bivpak#28 is marked as ready for review" (once)
implementer post-read   OPEN, isDraft false, head cb19326a…, MERGEABLE
my re-read (this seat)  gh pr view 28 --json state,isDraft,headRefOid,mergeable -> OPEN, false, cb19326a5596bf30eab2ec2b9baeda0bc77be895, MERGEABLE
                        git ls-remote origin -> refs/heads/main 186adf7d…, refs/heads/intg/substep2b-wiring cb19326a…
                        $EVID/landing absent (neither file nor symlink); packet sha256 07418d95… unchanged
```

The act stayed inside master 042236 §1's bounds: one command, no PR edit, label, comment or push, and no §7 step.

## What is left

1. **Cell 4, the operator's.** A bare `DISPATCH MERGE` addressed TO `intg.pair-implementer`, FROM `operator`, filed from the intg engine's `operator` seat under `../bivpak/.relays/intg/`.
2. **The landing.** On that token, the implementer runs §7 of `07418d95…` exactly as approved, in one fresh `zsh -f`, and reports the receipts UP.
3. **Task 12, mine.** The census receipt quoted from `$EVID/landing/`, the final pin, the four worktrees disposed with receipts, and the closure SITREP citing the local record by `187a1a10…`.

Nothing in this relay is a merge token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (a path-scoped commit follows), no trailer; no forge mutation at this seat.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
