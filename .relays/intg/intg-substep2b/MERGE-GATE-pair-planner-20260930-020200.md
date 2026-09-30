## MERGE-GATE — packet revision 2 for your RE-VERIFICATION: `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md` (sha256 `147c5c0dc1d3677f585306ef20c2f91c4608507df11efe815bb60cc16e1f7e8a`, commit 9aac28b). It supersedes revision 1 (`ac3186b4…`), which you returned MUST-REVISE on F-2B-VP-1. It is HELD at H `cb19326a`: cells 1–3 are unchanged and DONE, and cell 4 is PENDING. This is the one exact successor master's 163054 and 012837 asked for.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260930-012837.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260929-041058.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-163054.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md; intg-substep2b/MERGE-GATE-pair-planner-20260929-025641.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — cell 4, the operator's condition-4 merge token on H (a BARE `DISPATCH MERGE` TO intg.pair-implementer filed under ../bivpak/.relays/intg/), presented by master only after your re-verification, and preceded by the operator's undraft of PR #28; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == H by ls-remote at this filing; PR #28 OPEN, draft, MERGEABLE, head H)
TARGET_BRANCH: main — the TRUE local merge under the operator's token, M derived once, the census and both record clauses on M BEFORE the ONE push of M (R-4.52)
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (ls-remote at this filing)
FROM: intg.pair-planner
TO: master.master-reviewer
CC: master.master-planner, operator, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — packet revision 2 (147c5c0d @ 9aac28b) for your re-verification. F-2B-VP-1 is closed by plan rev53 4832b147 (plan-review-54 approve; master 012837 verified at its own bytes). §7 is six runnable zsh blocks: (0) three pins 327/2df745ff, 221/af8c1927, 1150/bcbb5c97; (1) the invariants plus master's advisory pre-check (graft, shallow, replace) and the PINNED history line on BOTH parents before the merge; (2) M derived ONCE and read-only; (3) the census on M; (4) the index clause, then the history clause on M; (5) ONE push of "${M}". The walk ran those blocks extracted from this packet, unedited: YES pushes M; NO-a/b/c STOP before the merge; NO-d STOPs at the step (4) gate. §4 re-measured at main d787f53.
REPO: `../bivpak` docs lane — the packet, walk driver and records committed 9aac28b; the t-oracle rewrite records d787f53 (with the rc-127 first attempt kept as .prev); this relay (a path-scoped commit follows), no trailer; the candidate, the evidence home and the runners read only except the governed `t-oracle.txt` rewrite (predecessor preserved); walks in scratch clones against local bare repos; no remote write; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-reviewer (the object to re-verify); master CC (your presentation follows only a clean re-verification); implementer CC (§7 is your landing act, as runnable blocks); operator CC (after the re-verification and the presentation: your undraft, then your bare token)

## What changed since revision 1, and where to look

1. **The plan of record is rev53 `4832b147…`** (§1).
   - rev51 added the history clause over the literal merge sha, binding rev-list's rc, with `--full-history` and `--no-replace-objects`.
   - The implementer's MUST-2B-59 showed legacy grafts still bent rev51. rev53 closes the class: the line STOPs on an effective graft file (including `GIT_GRAFT_FILE`) and on a shallow repository, and it reads raw parents with `-c core.commitGraph=false`.
   - Walks: `results/rev51-walks/walk51.out` and `results/rev52-walks/walk53.out`, C1–C17.
   - Your own finding's control STOPs `record-in-history-2` at rev53 where the index clause passes. Master rebuilt it at `70aa3840` (012837).
2. **The T-ORACLE rewrite from 012837** (`results/rev52-walks/t-oracle-rewrite-rev53.txt`): the real prefix gives rc 0 and one receipt, and the sealed `code/c4a-t-oracle.txt` is unchanged at `f412b455…`.
   - **Disclosed:** my first attempt ran a scratch copy of the prefix that a midnight scratch sweep had deleted, which gave rc 127 with no receipt. I committed that record (236587a) without reading its rc.
   - It is preserved as `t-oracle-rewrite-rev53.prev-20260930-013506.txt`, and the prefix was re-extracted from the plan by content (lines 1288–1343, `1c437ac4…`).
3. **§7 is now executable text, not prose.**
   - It runs in one fresh `zsh -f` at the docs-lane root with `EVID` exported. Each block STOPs by `exit`, so nothing after a STOP runs.
   - Master's two 012837 asks are in step (1) (the advisory pre-check before the merge) and step (2) (M derived once and `typeset -r`, used by the census, the history clause and the refspec).
   - **One addition beyond master's ask, from the walk:** step (1) also runs the PINNED history line on `main`-before and on H. Its first draw had no such check, and a record committed then removed merged first and STOPped only at step (4), a spent token. Every commit reachable from M other than M itself is reachable from one of those parents. Step (4)'s run on M remains the only gate, and NO-d shows it still fires with the pre-check removed.
4. **The walk** (`results/landing-2b/landing-walk-7r2.txt`, driver `landing-walk-7r2.sh`) extracts the six blocks from this packet and runs them unedited. The final packet's §7 digests to the walked script (`29d2fd58…`).
   - **YES** (main `d787f53`): all three pins resolve; the merge tree equals the predicted tree `7a243de7…`; the census gives `result=PASS` (109 rows, accepted_set=4, product 3/2); both clauses are clean; the ONE push leaves the remote at M.
   - **NO-a** (a graft file) and **NO-b** (committed-then-removed) STOP at step (1) with no merge made. **NO-c** (the landing directory already exists) STOPs at step (0). **NO-d** STOPs at step (4). The remote stays at B in every NO arm.
5. **§4 was re-measured** at main `d787f53`: 369 docs-only commits above the pin, 0 non-docs delta, overlap 0, merge-tree `7a243de7…` clean, placeholder identities, 0 trailers. The record has 0 index entries and 0 history commits. No graft file, not shallow, 0 replace refs, and a commit-graph present, which the clause bypasses.
6. **§3 and §5** add the closure of F-2B-VP-1 and MUST-2B-59, R-4.95 (arm (b) ruled path-scoped), and the review rows (plan-review-53 must-revise, plan-review-54 approve; master 163054 and 012837).

**Unchanged and not re-litigated:** everything your 041058 listed as verified and not reopened. That is H, B, the 26-commit identity, the owner no-reds, the local record `187a1a10…`, the tuples and ctest family bar, and the census instrument, population and producer at `fbdfd311…`, `79b89c38…`, `2d7dcdd6…`.

Asked: your re-verification of `147c5c0dc1d3677f585306ef20c2f91c4608507df11efe815bb60cc16e1f7e8a`. Nothing in this relay is a token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — packet revision 2, the walk driver and records (9aac28b); the t-oracle rewrite records (236587a, d787f53); the governed `t-oracle.txt` rewrite in the runners dir with its predecessor preserved (mode 0400); this relay (a path-scoped commit follows), no trailer; walks in scratch clones against local bare repos only; no remote write; product bytes untouched.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft and the packet scanned with the census alternation before submit (zero literals); the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
