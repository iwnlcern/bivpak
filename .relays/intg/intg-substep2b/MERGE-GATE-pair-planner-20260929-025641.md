## MERGE-GATE — the sub-step 2b merge packet is ASSEMBLED and HELD at H `cb19326a`: `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md` (sha256 `ac3186b47448cbdade776fd494853acec5eff9bbaa62fb48b0b1eecde6554b11`, commit 148ab1a). Cells 1–3 are DONE and cell 4 is PENDING. Its §7 landing sequence was walked end to end on a scratch clone with a local bare remote, and that walk found and fixed a zsh refspec trap in the push step. It is routed for the Master Reviewer's verification and your own-bytes presentation, per your 203750.

ROLE: Pair Planner
PHASE: MERGE-GATE
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b-merge-packet
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-023528.md
RELATED_CONTEXT: ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2b-merge-gate.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-203750.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md; intg-substep2b/SITREP-pair-planner-20260929-023044.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — cell 4, the operator's condition-4 merge token on H (a BARE `DISPATCH MERGE` TO intg.pair-implementer filed under ../bivpak/.relays/intg/, presented by master after the Master Reviewer's verification), preceded by the operator's undraft of PR #28; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f
BRANCH: intg/substep2b-wiring at H cb19326a5596bf30eab2ec2b9baeda0bc77be895 (remote == local; PR #28 the vehicle, OPEN, draft, MERGEABLE)
TARGET_BRANCH: main — the TRUE local merge under the operator's token, the census on the merge BEFORE the push, then the ONE push of the merge sha (R-4.52)
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: MERGE-GATE — 2b packet ASSEMBLED and HELD at H cb19326a (packet ac3186b4 @ 148ab1a; r449's eight sections). Cell 1: the c11 head gate at H (tidy 0, coverage 37/37, macOS 0 failures, Linux 0 failures), count gates rc0 on both targets, selftest pass-r435-disclosed-registered-red (3 in family). Cell 2: the container reached ctest. Cell 3: m-1 033430, m-3 033409, m-4 033613, all no-red. Cell 4 PENDING. §7 walked end to end: both pins, invariants, merge == predicted tree, census PASS, predicate ok, push rc0 to a local bare remote. The local record is cited by 187a1a10 and stated unpublished.
REPO: `../bivpak` docs lane — the packet and `results/landing-2b/landing-walk-7.txt` committed 148ab1a, this relay (a path-scoped commit follows), no trailer; the candidate worktree, the evidence home and the runners read only; the walk ran on a scratch clone against a local bare repo; no remote write; `../pdc` read-only
BRIDGE: intg.pair-planner → master.master-planner (the packet for the Master Reviewer's verification and your own-bytes presentation); Master Reviewer CC (the object to verify); implementer CC (§7 is your landing act, step by step); operator CC (after the verification and presentation: your undraft, then your bare token)

## The packet, in one screen

- **§1 Identity.**
  - H `cb19326a…`, B `186adf7d…`, `merge-base main H` == B.
  - 26 commits in B..H: 24 by the implementer and 2 by m-3 (the R-4.62 fixture commit, the harness commit), with 0 trailers and every identity a placeholder.
  - 55 files, +8195 −374.
  - Plan rev50 `7a2b894a…` approved exact-hash (plan-review-52); your 023528 carry is installed and the real prefix gives rc 0.
- **§2 Evidence at H.**
  - The c11 head gate, the tuples on both platforms and the final count gates, all rc 0.
  - The selftest bar (3 failed, all in the R-4.35 family, population 1055 equal); E3 Linux and harness-e2 on both platforms, rc 0.
  - 34 leg receipts with `verdict=PASS`, plus T-K and T-C registered.
  - The Task 10 push receipts.
  - The local record by `187a1a10…`, stated plainly as unverifiable off-host.
  - The rev49 census artifacts, with their walks.
- **§3** lists every registered residual and consumed precedent, none cited as green. That includes the synthetic `ghp_`-shaped control by digest `f419886e…`: a non-credential, class B, published by this landing, and disclosed.
- **§4 Blast radius**, measured at main `49a671f`:
  - 352 docs-lane commits above the pin, with no non-docs delta, all placeholder identities and 0 trailers;
  - merge-tree clean at `17437055…`, overlap 0;
  - the invariants are the binding face, and they are re-derived at landing.
- **§5 Review record** and **§6** the four-condition census: cells 1–3 DONE, cell 4 PENDING.
- **§7 Hold, plus the landing act at the implementer's seat.**
  - (0) Both pins are extracted and checked: the predicate `2df745ff…` (327 bytes) and the census line `af8c1927…` (221 bytes).
  - (1) The invariants and the predicted tree.
  - (2) The TRUE merge, with its message pinned and no trailer.
  - (3) The census of record ON THE MERGE, BEFORE the push. Exit 1 means NO push.
  - (4) The no-commit predicate.
  - (5) A dry run, then ONE push, refspec brace-quoted `"${M}:refs/heads/main"`.
  - (6) Observe PR #28, then report up; Task 12 follows.

## The §7 walk (`results/landing-2b/landing-walk-7.txt`)

The walk used a scratch clone of this lane at main `49a671f`, whose `origin` was re-pointed to a local bare repo seeded with main at B:
- (0) both pins resolve uniquely at the pinned lengths and digests;
- (1) merge-base == B, non-docs delta 0, overlap 0, predicted `17437055…`;
- (2) the merge tree equals the predicted tree, the parents are the old main and H, there are 0 trailers, and the product delta H..merge is empty;
- (3) the census gives rc 0, `tree_rows=109 … accepted_set=4 … product_tree_rows=3 product_history_paths=2 result=PASS`;
- (4) `record-untracked-ok`, rc 0;
- (5) the dry run and the ONE push give rc 0, with `ls-remote` equal to the merge.

**What the walk caught:** my first step-(5) run used a bare `$M:refs/heads/main` in zsh, which fired the `:r` history modifier and mangled the refspec. The seeding push failed the same way. §7 (5) now spells the refspec brace-quoted, and the walk records the negative. (The r449 packet's own §8 text carries the same mangled refspec as a display artifact.)

Asked: the Master Reviewer's verification of `ac3186b4…`, then your own-bytes presentation to the operator. Nothing in this relay is a token. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the packet and the §7 walk record committed 148ab1a; this relay (a path-scoped commit follows), no trailer; the walk on a scratch clone against a local bare repository only; no remote write; product bytes untouched.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft and the packet scanned with the census alternation before submit (zero literals); the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
