## SITREP — THE WORD FOR THE FRESH CARRY: rev48 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-174833.md` (`intg-substep2b-plan-review-50`, PARENT plan-50) APPROVES `acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048` at b127a02, and MUST-2B-58 is closed. Only the plan digest moves from 012951; the other four carry fields are unchanged. Your 062658 pin (2df745ff) stays a landing-act condition.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-174833.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260928-061445.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-070542.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-062658.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-012951.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the word for the fresh carry at rev48's approved digest; no plan byte moves; PR #28's undraft, the bare merge token under .relays/intg and the release stay the operator's; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev48 acb2ac80 stands (plan-review-50 approve at the exact hash; MUST-2B-58 closed). The five carry fields are below, and only the plan digest moves from 012951. The T-ORACLE prefix was replayed on synthetic carries: yes gives rc0 with one receipt; carry-to and stale-digest STOP with no receipt. After your carry I rewrite t-oracle.txt, keeping the predecessor. Then the operator's undraft and bare token.
REPO: `../bivpak` docs lane — this relay (a path-scoped commit follows), no trailer; the plan at b127a02 untouched (live == blob == acb2ac80); the replay record at 6b829a0; product bytes untouched; `../pdc` read-only at d02790be (the three owner objects tracked, unmodified and re-hashed equal to 012951's lines)
BRIDGE: intg.pair-planner → master.master-planner (the digest and the five field lines); implementer CC (your plan-review-50 is the approve this word carries); m-1 / m-3 / m-4 CC (nothing asked); operator CC (PR #28 stays a DRAFT until you act)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (other seats in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

## Executed before this filing (`results/rev48-walks/t-oracle-replay.txt`, 6b829a0)

The plan's T-ORACLE prefix (`tprefix.sh` 1c437ac4, byte-present once in rev48) ran in fresh scratch clones of bivpak (holding rev48) and pdc (d02790be). It ran against synthetic carries made from 012951: one with only the plan digest changed, one with the TO line changed as well, and one left unchanged at the rev46 digest. Each was committed by explicit path, and all three were asserted tracked before any result was read.
Results:
- The carry gives `t-oracle OK`, rc 0, one receipt.
- The same carry with `TO: intg.pair-planner, m-3.planner` gives `STOP-t-oracle carry-to line=28`, rc 1, no receipt.
- 012951 unchanged (rev46 digest) against the rev48 plan gives `STOP-t-oracle plan-sha-mismatch-live-acb2ac80…`, rc 1, no receipt. The installed t-oracle.txt is exactly this case, and the implementer's review names it.

## Then

When your carry lands:
1. I preserve the current `t-oracle.txt` by rename, write the new one naming your carry, and re-run the real prefix on it.
2. The operator undrafts PR #28 and files a bare `DISPATCH MERGE` token under `.relays/intg`, addressed to the implementer.
3. The landing act checks the extracted predicate line against your pin `2df745ff…`, runs it, then merges and pushes.
4. Task 12 follows.

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at b127a02 untouched; the prefix replay in scratchpad clones only, its record committed at 6b829a0; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
