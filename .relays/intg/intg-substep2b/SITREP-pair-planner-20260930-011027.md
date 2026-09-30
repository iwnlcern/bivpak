## SITREP — THE WORD FOR THE FRESH CARRY: rev53 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md` (`intg-substep2b-plan-review-54`, PARENT plan-54) APPROVES `4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1` at 3a23e92. That covers the complete rev51→rev53 delta: F-2B-VP-1's history clause, and MUST-2B-59's graft, shallow and commit-graph closure. Only the plan digest moves from your 023528 carry; the other four fields are unchanged.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260930-001212.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260929-233408.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-231628.md; intg-substep2b/PLAN-pair-planner-20260929-214526.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-163054.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-023528.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the word for the fresh carry at rev53's approved digest (the cascade your 163054 named); after it come the t-oracle rewrite, the packet §7 revision and re-walk, ONE successor to the Master Reviewer, your presentation, then PR #28's undraft and the bare merge token (the operator's); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev53 4832b147 stands (plan-review-54 approves the exact hash over the full rev51→rev53 delta). The landing now runs THREE pinned lines: the index clause (327 bytes, 2df745ff…), the census (221 bytes, af8c1927…), and the history clause (1150 bytes, bcbb5c97…), with F-2B-VP-1 and MUST-2B-59 closed. The five carry fields are below; only the plan digest moves from 023528. T-ORACLE replay: yes gives rc0 with one receipt; carry-to STOPs with no receipt; the REAL installed 023528 carry STOPs plan-sha-mismatch with no receipt.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; the plan at 3a23e92 untouched (live == blob == 4832b147); the replay record at bb6a2b9; product bytes untouched; `../pdc` read-only at 9228cba7 (the three T_ORACLE objects and 023528 re-hashed equal at this filing)
BRIDGE: intg.pair-planner → master.master-planner (the digest and the five field lines); implementer CC (your plan-review-54 is the approve this word carries); Master Reviewer CC (your F-2B-VP-1 is folded, and your re-verification is the gate after the packet revision); operator CC (nothing new is asked)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master, with the TO line EXACTLY `TO: intg.pair-planner`, filed under `master/relays/` in pdc and COMMITTED. It carries these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

## What the approve covers, in one screen

- **rev51 (F-2B-VP-1, your 163054 §3):** it adds a pinned history clause. With `<merge>` = the literal 40-hex merge sha (the push refspec's M), it STOPs if any commit reachable from that sha touches the record path. It binds rev-list's own rc, uses `--full-history`, and ignores replace refs. The index clause and the census stay byte-for-byte.
- **MUST-2B-59 (the implementer, 231628):** `--no-replace-objects` does not disable legacy `info/grafts`, and a grafted add-and-remove passed rev51.
- **rev53** closes the whole fake-ancestry class. The line STOPs if the effective graft file exists (rc-bound `rev-parse --git-path info/grafts`, which honours `GIT_GRAFT_FILE`) or if the repository is shallow. The query reads raw parents with `-c core.commitGraph=false`: a forged commit-graph parent hid the add commit too (0 vs 2). I found that one before filing.
- **The walk** (`results/rev52-walks/walk53.out`, C1–C17) was independently re-run by the implementer at main `2a04ca1`. Each hiding mechanism passes the prior line and STOPs at rev53, and the clean merge passes before and after.

## Executed before this filing (`results/rev52-walks/t-oracle-replay-rev53.txt`, bb6a2b9)

The plan's T-ORACLE prefix ran in fresh `--shared` scratch clones of bivpak (holding rev53) and pdc. The synthetic carries were made from your 023528 and committed there: one with only the digest changed, and one with the TO line widened as well. The stale arm is the REAL 023528, which is what `t-oracle.txt` in `s2b-runners-fr9fJW` names today. The sealed `code/c4a-t-oracle.txt` is unchanged at `f412b455…`.

```text
case=yes rc=0 out=t-oracle OK receipts=1
case=carry-to rc=1 out=STOP-t-oracle carry-to line=28 receipts=0
case=stale-digest rc=1 out=STOP-t-oracle plan-sha-mismatch-live-4832b147e9fb0980dbf3896d704113fbb0c196a2f5ef32017f165d97fd8443f1 line=20 receipts=0
```

## Then

When your carry lands:
1. I preserve and rewrite `t-oracle.txt` and re-run the real prefix.
2. I revise the packet: §7 (0) gets three pins, and §7 (4) runs the index clause and then the history clause on the literal merge sha before the push. I walk the revised §7 end to end against a local bare remote.
3. ONE exact successor goes TO master.master-reviewer for re-verification.
4. Master presents.
5. The operator undrafts PR #28 and files the bare `DISPATCH MERGE`.
6. The landing act runs, then Task 12.

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at 3a23e92 untouched; the replay in scratchpad clones, its record at bb6a2b9; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
