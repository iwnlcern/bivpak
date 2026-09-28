## SITREP — THE WORD FOR THE FRESH CARRY: rev45 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-224421.md` (`intg-substep2b-plan-review-47`, PARENT plan-47) APPROVES `bd2d21f5c2e5681b2608414139c754bd3b8933889518d0223424c9e46c85bfe6` at 31a6123, under the operator's registered Plan-contract waiver. Task 10 is COMPLETE under impl-16: FINAL H `cb19326a` was pushed once (class a), and draft PR #28 is open at H. rev45 changes Task 11 and the `census_population.sh` block only. My pre-token walk of Task 11 on a real-home clone found the sealed census producer counting one row per match where your pinned instrument counts one per line, which gives a deterministic tree-delta STOP. Please carry the five fields below verbatim TO intg.pair-planner; only the plan digest differs from your 181059. No product byte; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-224421.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-224421.md; intg-substep2b/PLAN-pair-planner-20260927-221259.md; intg-substep2b/IMPL-pair-implementer-20260927-213948.md; intg-substep2b/IMPL-pair-planner-20260927-203134.md; intg-substep2b/SITREP-pair-planner-20260927-202731.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-181059.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry at rev45's approved digest; no plan byte moves; Task 11 is local (no push or PR act, no candidate commit); PR #28's undraft, the merge (Task 12, behind the operator's bare token) and the release stay the operator's; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 bd2d21f5c2e5681b2608414139c754bd3b8933889518d0223424c9e46c85bfe6
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev45 bd2d21f5 stands (plan-review-47 approve at the exact hash). Task 10 COMPLETE (impl-16: H cb19326a pushed once, class a; draft PR #28 OPEN at H; remote main still B; verified at my seat). rev45 = Task 11 + the census_population.sh block: the sealed Task 0 producer's tree arm used `git grep -n -o` (one row per match) against your pinned instrument's `git grep -n` (one row per line), a deterministic tree-delta at the rehearsal and at the landing; Task 11 now produces census_population.rev45.sh (0c7124d7) beside the sealed copy; the instrument is untouched. Carry the five fields verbatim TO intg.pair-planner (only T_ORACLE_PLAN_SHA256 moves from 181059); the T-ORACLE prefix replayed at the new digest (YES + carry-to + stale-digest NO)
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at 31a6123 untouched (live == blob == bd2d21f5…); product bytes untouched at this seat. `../pdc` read-only at ac537569: your 181059 and the three owner objects tracked and unmodified, their digests computed at this filing and equal to 181059's lines. The prefix replay ran in scratch clones only (bivpak at b9ad231, holding rev45; pdc at ac537569 plus synthetic COMMITTED carries); nothing written under `../pdc`.
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines; Task 10's completion and the census-producer fold, for your view since the instrument is yours); implementer CC (your plan-review-47 approve is impl-17's PARENT); m-1 / m-3 / m-4 CC (H unchanged; nothing asked); operator CC (PR #28 is public and a DRAFT; the undraft, the merge token and the release are yours)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (other seats in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: bd2d21f5c2e5681b2608414139c754bd3b8933889518d0223424c9e46c85bfe6
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE prefix (56 lines, `1c437ac4…`, byte-present once in rev45) ran in fresh scratch clones of bivpak (b9ad231, holding rev45) and pdc (ac537569). It ran against synthetic carries made from your 181059 with only the plan digest changed (and, for the control, the TO line), each committed by explicit path and asserted tracked before any result was read.
Results:
- The carry gives `t-oracle OK`, rc 0, one receipt.
- The same carry with `TO: intg.pair-planner, m-3.planner` gives `STOP-t-oracle carry-to`, rc 1, no receipt.
- A locator holding rev44's digest `7d55f0b8…` against the rev45 plan gives `STOP-t-oracle plan-sha-mismatch-live-…`, rc 1, no receipt.

## Task 10, complete (impl-16)

The return `intg-substep2b/IMPL-pair-implementer-20260927-213948.md` is verified at my seat:
- task-10 exit and done are rc=0; push_rc=0; class=a; pr_rc=0.
- Impl-15's attempt is preserved (9/9 manifest rows OK, its pyc included).
- `git ls-remote` on the literal URL shows the feature branch == H `cb19326a` and `main` == B `186adf7d`.
- `gh pr view 28 --repo github.com/iwnlcern/bivpak` shows OPEN, isDraft true, base main, head OID H.
- The candidate is clean at H, and the new runners directory is `s2b-runners-V1jS1t`.
- Your 042625 (1) condition is met in the return: each of the 26 commits' paths enumerated, and the PR URL and remote head quoted.

## The census-producer fold (rev45; your instrument untouched)

I walked Task 11's body on a full clone of the real evidence home before any token. The H0 rehearsal STOPs `STOP-landing-census line=38 reason=tree-delta`.
- The sealed Task 0 `census_population.sh` (`1917222c…`) runs `git grep -n -o` in its tree arm, one row per match. Your `intg-r449-landing-census.sh` (`9c9391d5…`) runs `git grep -n`, one row per line, and digests each line's first match.
- The sets are identical (81 locations). The producer's list carries 4 extra rows for 3 lines holding two matches.
- The landing census, which re-runs the producer on the merge head, would have STOPped the same way.

rev45 fixes the block (one row per line, first match: your instrument's rule). Task 11 produces `census_population.rev45.sh` (`0c7124d7…`) beside the sealed copy, digest-pinned, and both the population and the landing declaration use it.
Walked:
- The fix PASSes your instrument at H0 `b3039506` and at H `cb19326a` (81 rows, A=3 B=76 C=2).
- The derived rev45 Task 11 body runs rc 0 on a clone, with `finalize check` rc 0 and 2,329 files.
- Tampered and symlinked beside-copies STOP.
- The producer gate is rc 0 on a rev45 baseline (rev41's plus two classified rows).
The implementer re-ran the producer and instrument pair independently at both refs: PASS.
The landing declaration Task 11 writes (for the merge packet) will name `census_population.rev45.sh` and its digest beside your instrument's.

## What the token then names (for the record; nothing moves before the carry)

1. On the carry, `$RUNNERS/t-oracle.txt` in `s2b-runners-V1jS1t` (read from the pointer) is preserved as `t-oracle.prev-<stamp>.txt` and rewritten with `carry_relay=<the carry's path>` and exactly one `plan_sha256=bd2d21f5c2e5681b2608414139c754bd3b8933889518d0223424c9e46c85bfe6` line.
2. `intg-substep2b-impl-17` issues at PARENT `intg-substep2b-plan-review-47`: Step 0′ (a new runners directory on the rev45 lock), then Task 11 ONCE, then return.
3. Task 11 is local: the H0 rehearsal, the landing declaration, and the tracked record `results/s2b-intg-substep2b-impl-1/` in the docs lane. It makes no push or PR act.
4. Task 12 (the landing) waits on PR #28's undraft and the operator's bare merge token.

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at 31a6123 untouched; the prefix replay in this seat's scratchpad clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
