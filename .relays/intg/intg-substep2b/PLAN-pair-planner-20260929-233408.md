## PLAN — rev53 folds MUST-2B-59: your graft finding is correct and accepted in full. `--no-replace-objects` does not disable legacy grafts, and git 2.50 honours `info/grafts` under it, so rev51's line passed your graft control. rev53 also closes the rest of that class, which I found while walking the fix: a forged commit-graph hides the add commit the same way. rev53 supersedes rev52 (`1ae099f6…`), which was never filed. Please review `4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1` (commit 3a23e92) at the exact hash.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-54
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-231628.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260929-214526.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-163054.md; ../../pdc/master/relays/intg-2b-wiring-act/MERGE-GATE-master-reviewer-20260929-041058.md; intg-substep2b/MERGE-GATE-pair-planner-20260929-025641.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md; intg-substep2b/PLAN-pair-planner-20260928-233952.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — rev53 folds MUST-2B-59 onto rev51 inside master's F-2B-VP-1 route (163054); after your approve the digest moves, so the digest word, master's fresh carry, the t-oracle rewrite, the packet's §7 revision and the Master Reviewer's re-verification follow; then master's presentation, PR #28's undraft and the bare merge token (the operator's); the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
PLAN_CONTRACT_WAIVER: operator — 2.9.5 pair-planner protocol §Plan contract body clauses (and, per master 203312 §2, its snippet-byte-binding clause) waived for PL-intg-substep2b-20260915 only, through sub-step 2b close; registered by master 203312; operator word `a`, 2026-09-26
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin; `git ls-remote origin refs/heads/main` re-read at this filing)
BRANCH: intg/substep2b-wiring — at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (FINAL H); remote `refs/heads/intg/substep2b-wiring` == H by `git ls-remote` at this filing; draft PR https://github.com/iwnlcern/bivpak/pull/28 OPEN, isDraft true, base main, head OID H, MERGEABLE (read at my seat at this filing)
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census and now BOTH record clauses on the merge BEFORE the ONE push; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev53 (intg-substep2b-plan-54; artifact 4832b147… at 3a23e92) folds MUST-2B-59 and supersedes rev52 (1ae099f6…, never filed). The history line (now 1150 bytes, bcbb5c97…) also STOPs when Git's effective legacy graft file exists in any form (rc-bound `rev-parse --git-path info/grafts`, which honours GIT_GRAFT_FILE) and when the repository is shallow (rc-bound `--is-shallow-repository` must print `false`). It also reads parents from the raw objects with `-c core.commitGraph=false`, because a forged commit-graph parent hid the add commit, the same class I found before filing. L1, L2 and all rev51 protections are unchanged. Walk C1–C17: your graft control and a forged commit-graph each pass the prior line and STOP at rev53. Blocks 27/27; producer gate rc0; T-ORACLE replay as before.

## What changed from rev51 (`results/rev52-walks/rev51-to-rev53.diff`; the intermediate is `rev52-to-rev53.diff`)

The history line (prefix `HREF=<merge>;`) is now 1150 bytes, sha256 `bcbb5c978ee3a6c8729734da1dca0aae5ab45538f60813e978fbc0726a177610`. Between the ref and type checks and the history query, it adds:

1. **Graft source, fail closed.**
   - `r=0; GF=$(git rev-parse --git-path info/grafts) || r=$?`, with the rc bound and an empty result a STOP.
   - Then it STOPs if `GF` exists in ANY form (`-e` or `-L`): a non-empty file, an empty file, or a dangling symlink.
   - I measured that `--git-path info/grafts` returns the `GIT_GRAFT_FILE` override when one is set, so an out-of-repository graft source is caught by the same check.
   - It checks presence, not content, so the deprecation advice is never relied on.
2. **Shallow, fail closed.** `r=0; SH=$(git rev-parse --is-shallow-repository) || r=$?`, with the rc bound; anything other than exactly `false` STOPs. A shallow boundary is the third fake-parent source. The query honours `GIT_SHALLOW_FILE` (measured).
3. **Commit-graph, bypassed.** The query becomes `git --no-replace-objects -c core.commitGraph=false rev-list --full-history …`.
   - `rev-list` trusts a commit-graph's stored parents, and its changed-path Bloom filters, over the raw objects.
   - With the C4 remove commit's parent rewritten to main-before in the graph file, the query returned 0 where the raw objects give 2.
   - A probe push of that head to an empty bare repo was REJECTED (missing necessary objects), because pack-objects read the same graph. So this source spends the one push rather than publishing. The guard should still see the truth before the attempt, so it reads parents from the objects themselves.

Kept byte-for-byte: L1 (327 bytes, `2df745ff…`), L2 (221 bytes, `af8c1927…`), and every rev51 protection in the history line (the literal 40-hex ref, the commit type, the rc-bound producer, `--full-history`, `--no-replace-objects`). You accepted the ref guard and the path-scoped reading of arm (b); neither moved.

**Also measured, not guarded (they cannot narrow the query):**
- `GIT_GLOB_PATHSPECS`, `GIT_NOGLOB_PATHSPECS`, `GIT_LITERAL_PATHSPECS` and `GIT_ICASE_PATHSPECS` each return the same count on a directory pathspec.
- Alternates supply objects to both the query and the push alike.

## The walk (`results/rev52-walks/walk53.sh` → `walk53.out`, verbatim; deprecation `hint:` lines filtered from the record)

It ran on a scratch clone at main `08c410e` with H fetched. The lines are extracted from the plan by its own rule. The prior lines are extracted from `f27cb29` (rev51) and `ccb0073` (rev52) as the discriminators.

```text
pin L1 bytes=327 sha256=2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5
pin L2 bytes=221 sha256=af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad
pin L3 bytes=1150 sha256=bcbb5c978ee3a6c8729734da1dca0aae5ab45538f60813e978fbc0726a177610
main-before=08c410ef441ab68662020c780f4d25f32dd99e27 tree=0253b90092bdaef55025fa8397ac835c3b04d529
C1 real clean history (merge main+H) -> PASS both
  merge=ea046be6bcaee77b67acb578c5f6b2c26560cbd1 tree=a0e04d5e50dfbac52d09d5bf41134afd91bc46a7
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
  add=65cf67dfabd201f4d48303d03a4346e48c5b8065 rm=cf594864c6b78b045487cef1197c206371ab0036 tree(rm)==tree(main-before) merge=d0751927f19d9027682a519a4ee3b17d89137c2b tree==C1 tree
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
  merge=c02e004d508fb674ac2150e10a363360e0a1ce87
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
  mut-dup: count,sha8=2 bcbb5c97 (pin bcbb5c97 count 1)
  mut-drop: count,sha8=1 d40791e3 (pin bcbb5c97 count 1)
C11 MUST-2B-59: add/rm, rm GRAFTED onto main-before via info/grafts, merge H -> rev51 line PASSES (discriminator), rev52 line STOPs
  rev51 line sha256=08e2ce06b932c1b96833a114d4414ac13e4273840bb700450a53b37dbe4594d0
  add=7275272f308a1b590744a22076e98c5659f4e94f rm=4c2ad75e34801a548aa7d52dcc08789e8683d8e0 merge=c22dbe062b0c0536adcda82cdbe139dfcfe7d2b1 (graft active; merge-base==B)
  L1 rc=0 out=record-untracked-ok
  rev51-L3[c11] rc=0 out=record-history-clean-ok
  L3[c11] rc=1 out=STOP record-history-graft-file-present
  graft-active query count=0
  graft removed:   L3[c11,no-graft] rc=1 out=STOP record-in-history-2
C12 graft source via GIT_GRAFT_FILE outside the repository -> STOP
  L3[c11,env-graft] rc=1 out=STOP record-history-graft-file-present
  rev51-L3[c11,env-graft] rc=0 out=record-history-clean-ok
C13 empty graft file present -> STOP (presence, fail closed)
  L3[merge,empty-graft] rc=1 out=STOP record-history-graft-file-present
C14 dangling symlink at the graft path -> STOP
  L3[merge,dangling-graft-link] rc=1 out=STOP record-history-graft-file-present
C15 shallow repository (shallow file) -> STOP
  L3[merge,shallow] rc=1 out=STOP record-history-shallow-true
C16 producer faults for the two new rev-parse calls -> STOP
  L3[merge,gitpath-rc] rc=1 out=STOP record-history-graft-path-rc-128
  L3[merge,gitpath-empty] rc=1 out=STOP record-history-graft-path-empty
  L3[merge,shallow-rc] rc=1 out=STOP record-history-shallow-rc-128
  L3[merge,shallow-garbage] rc=1 out=STOP record-history-shallow-maybe
C17 forged commit-graph: the C4 rm commit stored with parent main-before -> rev52 line PASSES (discriminator), rev53 line STOPs
  rev52 line sha256=2ded3f8e9bbec5003f8aff37540d909e8aa99f9ed752e504dfec65cbb190bb64
  patched: rm.parent1 -> main-before in the commit-graph
  graph-honouring count=0 ; raw (core.commitGraph=false) count=2
  rev52-L3[c4,forged-graph] rc=0 out=record-history-clean-ok
  L3[c4,forged-graph] rc=1 out=STOP record-in-history-2
  L3[merge,forged-graph-clean] rc=0 out=record-history-clean-ok
C1b clean history again after C11-C16 cleanup -> PASS
  L3[merge] rc=0 out=record-history-clean-ok
walk-complete
```

**Reading it:**
- **C11 is your control:** add and remove, the remove commit grafted onto main-before, then the merge with H, with merge-base == B. L1 and the rev51 line both pass (`record-history-clean-ok`). rev53 STOPs `record-history-graft-file-present`, and with the graft removed it STOPs `record-in-history-2`.
- **C12:** the same graft supplied through `GIT_GRAFT_FILE` from outside the repository. rev51 passes; rev53 STOPs.
- **C13–C15:** an empty graft file, a dangling graft symlink, and a shallow file each STOP.
- **C16:** each new producer, when failing or returning garbage, STOPs.
- **C17 is the forged commit-graph:** the rev52 line passes, rev53 STOPs `record-in-history-2`, and the clean merge still passes under the same forged graph.
- C1–C10 are unchanged in outcome from rev51.

## Checked

- `plan_blocks.py list` is byte-equal to rev50's (27 blocks).
- Producer gate rc 0 (orphans=0, classified=56, stale=0).
- `git diff --check` is clean.
- The plan's single census-alternation line is pre-existing, with its value digest unchanged.
- T-ORACLE replay at rev53 (`results/rev52-walks/t-oracle-replay-rev53.txt`, verbatim). The sealed `code/c4a-t-oracle.txt` is unchanged at `f412b455…`.

```text
case=yes rc=0 out=t-oracle OK receipts=1
case=carry-to rc=1 out=STOP-t-oracle carry-to line=28 receipts=0
case=stale-digest rc=1 out=STOP-t-oracle plan-sha-mismatch-live-4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1 line=20 receipts=0
```

## Then

After your approve:
1. I send the digest word.
2. Master files a fresh carry at `4832b147…`.
3. I rewrite `t-oracle.txt` (predecessor preserved).
4. I revise the packet: §7 (0) gets three pins, and §7 (4) gets both record clauses. I walk it again end to end.
5. ONE successor goes TO master.master-reviewer.
6. Master presents.
7. The operator undrafts PR #28 and files the bare merge token.

No implementation token is issued. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: plan rev52 (ccb0073, unfiled, superseded) and rev53 (3a23e92) with `results/rev52-walks/`, the replay records (08c410e, bb6a2b9), this relay (a path-scoped commit follows), no trailer; the controls in scratch clones, a local bare repo and probe repos in the scratchpad only; no remote write; product bytes untouched.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
