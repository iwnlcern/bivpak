## PLAN — rev51 folds F-2B-VP-1, the Master Reviewer's finding that master accepted and routed to this seat in `PLAN-master-planner-20260929-163054.md`. The rev48 no-commit line checks the INDEX. A record committed and then removed empties the index again, but R-4.52 still publishes that history. rev51 adds a third executed line, pinned like the other two, that checks the HISTORY reachable from the literal merge sha. Please review `7c723a1b82030bd0cabba1730d9a91c5c25ac672cf1d8bd33308139b25278335` (commit f27cb29) at the exact hash.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-53
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-163054.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260929-041058.md; intg-substep2b/MERGE-GATE-pair-planner-20260929-025641.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md; intg-substep2b/PLAN-pair-planner-20260928-233952.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — rev51 folds F-2B-VP-1 as master routed it (163054); after your approve the digest moves, so the digest word, master's fresh carry, the t-oracle rewrite, the packet's §7 revision and the Master Reviewer's re-verification follow; then master's presentation, PR #28's undraft and the bare merge token (the operator's); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m1-addendum-M-20260823
DESIGN_LOCK_ID: m1-addendum-M-2966b839-lock-20260825
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_COMMIT: 6aa64fe280c40beec2c93063de1d38c830aac097
DESIGN_OWNER: m-1
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: a1ce40a930b5fd01d905e8295c3a9e581455a1c7
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md
DESIGN_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (A6 rev14, post-stamp 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m3-addendum-7-4c40fe37-lock-20260827 (A7 rev2)
THIRD_CONSUMED_CONTRACT: m3-addendum-8 lock d686e39a (A8 rev8)
FOURTH_CONSUMED_CONTRACT: m1-addendum-N-82293732-lock-20260827; m1-addendum-O-63c46631-lock-20260901; m4-sr-url rev5
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7c723a1b82030bd0cabba1730d9a91c5c25ac672cf1d8bd33308139b25278335
PLAN_CONTRACT_WAIVER: operator — 2.9.5 pair-planner protocol §Plan contract body clauses (and, per master 203312 §2, its snippet-byte-binding clause) waived for PL-intg-substep2b-20260915 only, through sub-step 2b close; registered by master 203312; operator word `a`, 2026-09-26
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin; `git ls-remote origin refs/heads/main` re-read at this filing)
BRANCH: intg/substep2b-wiring — at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (FINAL H); remote `refs/heads/intg/substep2b-wiring` == H by `git ls-remote` at this filing; draft PR https://github.com/iwnlcern/bivpak/pull/28 OPEN, isDraft true, base main, head OID H, MERGEABLE (read at my seat at this filing)
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census and now BOTH record clauses on the merge BEFORE the ONE push; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev51 (intg-substep2b-plan-53; artifact 7c723a1b… at f27cb29) folds F-2B-VP-1. The LANDING row gains a third executed line, additive, pinned like the other two (704 bytes, 08e2ce06…): with `<merge>` = the literal 40-hex merge sha (the same value as the push refspec's M), it STOPs if any commit reachable from that sha touches the record path. It binds rev-list's own rc, uses --full-history and --no-replace-objects, and refuses a ref that is not 40-hex naming a commit. The rev48 index line and the census line do not move. Walked C1–C10 on a scratch clone: the finding's control STOPs (record-in-history-2) where the index line passes; the empty and partial query failures STOP; both traps discriminate. Blocks 27/27 equal; producer gate rc0; T-ORACLE replay as rev50's.

## What changed (the LANDING row only; `results/rev51-walks/rev50-to-rev51.diff`)

- **The rev48 index line STAYS** byte-for-byte (327 bytes, `2df745ff…`). The census line also stays (221 bytes, `af8c1927…`).
- **ADDED, after the merge and BEFORE the push, as its own `bash` whose nonzero exit forbids the push:** a line with prefix `HREF=<merge>;` (704 bytes, sha256 `08e2ce06b932c1b96833a114d4414ac13e4273840bb700450a53b37dbe4594d0`). `<merge>` is the literal 40-hex merge sha, the SAME value as `M` in the push refspec. It is never `main`, never H, and never an abbreviation.
- **The property:** NO commit reachable from the literal push sha touches the record path. The line STOPs on any such commit, and on any failure to establish it.
- **Master's §3 carried exactly:**
  - Trap 1: `rev-list`'s own rc is bound before its output is read (`r=0; C=$(git … rev-list …) || r=$?`), as the index clause binds `ls-files`.
  - Trap 2: `--full-history`.
- **Two additions of mine beyond §3.** Please rule on both as design, not wording.
  - (a) `--no-replace-objects`: `push` packs the REAL history, but a replace ref would hide a touching commit from a replace-honouring query. Control C8 shows the gap is real.
  - (b) A ref guard: HREF must be 40 lowercase hex, and `cat-file -t` (its rc bound) must say `commit`. A movable name, an abbreviation, a tree or an absent object STOPs instead of scanning some other history.
- **Scope, stated:** the guard covers the record PATH, as arm (b) names it. A byte-copy of record files committed under a DIFFERENT path is not detected by this line; the value census does not claim it either. I read arm (b) as path-scoped, and the reviewer's own witness query is a path query. If you or the Master Reviewer read it as content-scoped, say so, and I will route the question UP rather than widen the line on my own word.
- **The pins become THREE**, all extracted by the rev50 rule, each count exactly one, each digest checked before `<merge>` is substituted.

## The walk (`results/rev51-walks/walk51.sh` → `walk51.out`, verbatim)

It ran on a scratch clone of this lane at main `14292d09`, with H fetched. Each built commit was asserted to have moved the ref before the next step. The three lines are the bytes extracted from the plan by its own rule, not retyped.

```text
pin L1 bytes=327 sha256=2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5
pin L2 bytes=221 sha256=af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad
pin L3 bytes=704 sha256=08e2ce06b932c1b96833a114d4414ac13e4273840bb700450a53b37dbe4594d0
main-before=14292d09c973fdadece47209b30c380f159e901d tree=bfc3f4ea15e690ab5348b2a8be1f8c516b01d8b0
C1 real clean history (merge main+H) -> PASS both
  merge=57b2c205497717127d94432d2e959ac7cfd0a2a6 tree=a82a788976c2f98d8aeeb3359d9dc362cc19aa75
  L1 rc=0 out=record-untracked-ok
  L3[merge] rc=0 out=record-history-clean-ok
  replace-honouring plain rev-list count=0 ; --full-history count=0
C2 untracked record file on disk -> PASS both
  L1 rc=0 out=record-untracked-ok
  L3[merge] rc=0 out=record-history-clean-ok
C3a staged record -> L1 STOP
  L1 rc=1 out=STOP record-tracked-1
C3b committed now -> L1 STOP, L3 STOP
  L1 rc=1 out=STOP record-tracked-1
  L3[c3] rc=1 out=STOP record-in-history-1
C4 committed-then-removed, final tree unchanged (THE FINDING) -> L1 PASS, L3 STOP
  add=499b9ddfeecc27488d6ec44fb4497f2024cbeb43 rm=5ef8e1263291e181f5ce7bcbe2bb9567d40bbd83 tree(rm)==tree(main-before) merge=ebc6884ac261f083a014b7655f0c221fb1cf7ed8 tree==C1 tree
  L1 rc=0 out=record-untracked-ok
  L3[c4] rc=1 out=STOP record-in-history-2
  replace-honouring plain rev-list count=2 ; --full-history count=2
C5 history query fails with EMPTY output (shim rev-list: rc 128, no output) -> STOP
  L3[merge,shim-empty] rc=1 out=fatal: shim
STOP record-history-rc-128
C6 history query fails with PARTIAL output (shim: first real line, then rc 141) -> STOP
  L3[c4,shim-partial] rc=1 out=STOP record-history-rc-141
  L3[merge,shim-partial-on-clean] rc=1 out=STOP record-history-rc-141
C7 add+remove on a SIDE branch merged TREESAME, then merge H (trap 2) -> L3 STOP
  merge=3f06708885c57cd747e1c06cd5461a2c9b63e89a
  L1 rc=0 out=record-untracked-ok
  L3[c7] rc=1 out=STOP record-in-history-2
  replace-honouring plain rev-list count=0 ; --full-history count=2
C8 replace ref grafts rm onto main-before, hiding add from a replace-honouring query -> L3 STOP; push publishes add
  replace-honouring plain rev-list count=0 ; --full-history count=0
  L3[c4,replaced] rc=1 out=STOP record-in-history-2
  push rc=0 ; add commit in bare: present
C9 ref guards -> each STOP
  L3[main] rc=1 out=STOP record-history-ref-not-hex
  L3[abbrev12] rc=1 out=STOP record-history-ref-len-12
  L3[uppercase] rc=1 out=STOP record-history-ref-not-hex
  L3[empty] rc=1 out=STOP record-history-ref-not-hex
  L3[tree-sha] rc=1 out=STOP record-history-ref-type-tree
  L3[absent-sha] rc=1 out=fatal: git cat-file: could not get object info
STOP record-history-cat-file-rc-128
  L3[unsubstituted] rc=2 out=bash: -c: line 1: syntax error near unexpected token `;'
C10 pin mutants (the extraction rule) -> STOP
  mut-dup: count,sha8=2 08e2ce06 (pin 08e2ce06 count 1)
  mut-drop: count,sha8=1 6d685b7d (pin 08e2ce06 count 1)
walk-complete
```

**Reading it:**
- **C4 is the finding.** The index line passes (`record-untracked-ok`), and the new line STOPs `record-in-history-2`. The merge tree is the real predicted `a82a7889…`.
- **C5 and C6 are master's controls (5) and (6).** An empty failed query and a partial failed query both STOP on rc. A partial failure on the CLEAN history also STOPs.
- **C7 shows trap 2 is not theoretical.** An add and remove on a side branch, merged TREESAME: plain `rev-list` returns 0, `--full-history` returns 2, and the line STOPs.
- **C8 shows (a) is not theoretical.** A replace graft makes the replace-honouring query return 0 in BOTH modes, yet the line STOPs, and a push to a local bare repo carries the add commit.
- **C9:** every malformed ref STOPs. The unsubstituted template is a bash syntax error at rc 2, so a forgotten substitution can never read as a pass.
- **C10:** the pin rule catches a duplicated line (count 2) and a dropped `--full-history` (digest `6d685b7d`, which does not equal the pin).

## Checked

- `plan_blocks.py list` on rev51 is byte-equal to rev50's list (27 blocks).
- Producer gate rc 0 (orphans=0, classified=56, stale=0).
- The plan's single census-alternation line is pre-existing: its value digest is equal at rev50 and rev51, and only its line number moved (2886 to 2900, from the 14 inserted lines).
- T-ORACLE prefix replay against rev51 (`results/rev51-walks/t-oracle-replay-rev51.txt`, verbatim). The sealed `code/c4a-t-oracle.txt` is unchanged at `f412b455…`.

```text
case=yes rc=0 out=t-oracle OK receipts=1
case=carry-to rc=1 out=STOP-t-oracle carry-to line=28 receipts=0
case=stale-digest rc=1 out=STOP-t-oracle plan-sha-mismatch-live-7c723a1b82030bd0cabba1730d9a91c5c25ac672cf1d8bd33308139b25278335 line=20 receipts=0
```

The real installed t-oracle (carry 023528 at `7a2b894a…`) STOPs plan-sha-mismatch, as designed, until master's fresh carry at `7c723a1b…`.

## Then

After your approve:
1. I send the digest word.
2. Master files a fresh carry at `7c723a1b…`.
3. I rewrite `t-oracle.txt` (predecessor preserved).
4. I revise the packet: §7 step (0) gets three pins, and step (4) gets both record clauses. I walk the revised §7 again end to end.
5. ONE exact successor goes TO master.master-reviewer for re-verification.
6. Master presents.
7. The operator undrafts PR #28 and files the bare merge token.

No implementation token is issued. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: plan rev51 + `results/rev51-walks/` (f27cb29), the T-ORACLE replay record (d0ae71e), this relay (a path-scoped commit follows), no trailer; the controls only in a scratch clone and a local bare repo in the scratchpad; the replay in `--shared` scratch clones; no remote write; product bytes untouched.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
