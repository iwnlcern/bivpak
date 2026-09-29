## SITREP — THE WORD FOR THE FRESH CARRY: rev50 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md` (`intg-substep2b-plan-review-52`, PARENT plan-52) APPROVES `7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f` at df2935e, covering the complete rev48→rev50 landing delta. Only the plan digest moves from your 181421 carry; the other four fields are unchanged.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260929-020827.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260928-233952.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260929-001609.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-181421.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the word for the fresh carry at rev50's approved digest; no plan byte moves; the packet, the Master Reviewer, PR #28's undraft, the bare merge token and the release follow in order; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev50 7a2b894a stands (plan-review-52 approve at the exact hash over the full rev48→rev50 delta). The five carry fields are below, and only the plan digest moves from 181421. T-ORACLE replay: yes gives rc0 with one receipt; carry-to STOPs with no receipt; the REAL installed 181421 carry STOPs plan-sha-mismatch with no receipt. After your carry I rewrite t-oracle.txt, keeping the predecessor, and assemble the packet.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; the plan at df2935e untouched (live == blob == 7a2b894a); the replay record at 4885b88; product bytes untouched; `../pdc` read-only at 984eb293 (the three owner objects tracked, unmodified, re-hashed equal)
BRIDGE: intg.pair-planner → master.master-planner (the digest and the five field lines); implementer CC (your plan-review-52 is the approve this word carries); operator CC (nothing new is asked)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner`, filed under `master/relays/` in pdc and COMMITTED, carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

## Executed before this filing (`results/landing-2b/t-oracle-replay-rev50.txt`, 4885b88)

The plan's T-ORACLE prefix ran in fresh scratch clones of bivpak (holding rev50) and pdc (984eb293). Two synthetic carries were made from your 181421 and committed there: one with only the digest changed, and one with the TO line widened as well. The stale arm used the REAL 181421, which is byte-for-byte what `t-oracle.txt` in `s2b-runners-fr9fJW` names today.
Results:
- The carry gives `t-oracle OK`, rc 0, one receipt.
- The widened TO gives `STOP-t-oracle carry-to line=28`, rc 1, no receipt.
- The real 181421 against rev50 gives `STOP-t-oracle plan-sha-mismatch-live-7a2b894a… line=20`, rc 1, no receipt.

## Then

When your carry lands:
1. I preserve and rewrite `t-oracle.txt` and re-run the real prefix.
2. I assemble the packet (the r449 shape, §7 citing both pinned lines and the rev49 census pins) and route it to the Master Reviewer.
3. Master does the own-bytes presentation.
4. The operator undrafts PR #28 and files the bare `DISPATCH MERGE`.
5. The landing act runs: both pins, the no-commit predicate, the merge, the census on the merge as both refs, then ONE push after PASS.
6. Task 12 follows.

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at df2935e untouched; the replay in scratchpad clones, its record at 4885b88; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
