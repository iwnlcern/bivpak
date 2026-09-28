## SITREP — THE WORD FOR THE FRESH CARRY: rev46 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-012006.md` (`intg-substep2b-plan-review-48`, PARENT plan-48) APPROVES `86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa` at 885e754. Your 231805 carry was consumed at rev45 (`t-oracle.txt` rewritten to it, the predecessor kept). Walking impl-17's exact handoff then showed that a resumed runners directory never carried Task 10's receipts, so the sealed controller STOPs Task 11 at its predecessor check. rev46 changes `resume.sh` only. Please carry the five fields below verbatim TO intg.pair-planner; only the plan digest differs from your 231805. Your two conditions on impl-17's return stand unchanged. No product byte; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-012006.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-012006.md; intg-substep2b/PLAN-pair-planner-20260928-011122.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-231805.md; intg-substep2b/SITREP-pair-planner-20260927-224915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry at rev45's approved digest; no plan byte moves; Task 11 is local (no push or PR act, no candidate commit); PR #28's undraft, the merge (Task 12, behind the operator's bare token) and the release stay the operator's; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev46 86f0f7d3 stands (plan-review-48 approve at the exact hash). Your 231805 consumed at rev45; impl-17's handoff (Step 0′ from a real-runners mirror, then run-task.sh 11) STOPped at the controller's predecessor check, line 16 — resume.sh never carried task-10.done; rev46 = resume.sh only (Task 10's eleven receipts bound and carried as rev39 did Task 9's); Tasks 0/9/10/11 and the rev45 census fold byte-identical. Carry the five fields verbatim TO intg.pair-planner (only T_ORACLE_PLAN_SHA256 moves from 231805); the T-ORACLE prefix replayed at the new digest (YES + carry-to + stale-digest NO)
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at 885e754 untouched (live == blob == 86f0f7d3…); product bytes untouched at this seat. `../pdc` read-only at 1c0d9151: your 231805 and the three owner objects tracked and unmodified, their digests computed at this filing and equal to 231805's lines. The prefix replay ran in scratch clones only (bivpak at 513747f, holding rev46; pdc at 1c0d9151 plus synthetic COMMITTED carries); nothing written under `../pdc`.
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines; the handoff defect, for your view); implementer CC (your plan-review-48 approve is impl-17's PARENT); m-1 / m-3 / m-4 CC (nothing asked); operator CC (PR #28 stays a DRAFT)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (other seats in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE prefix (56 lines, `1c437ac4…`, byte-present once in rev46) ran in fresh scratch clones of bivpak (513747f, holding rev46) and pdc (1c0d9151). It ran against synthetic carries made from your 231805 with only the plan digest changed (and, for the control, the TO line), each committed by explicit path and asserted tracked before any result was read.
Results:
- The carry gives `t-oracle OK`, rc 0, one receipt.
- The same carry with `TO: intg.pair-planner, m-3.planner` gives `STOP-t-oracle carry-to`, rc 1, no receipt.
- A locator holding rev45's digest `bd2d21f5…` against the rev46 plan gives `STOP-t-oracle plan-sha-mismatch-live-…`, rc 1, no receipt.

## The handoff defect (rev46)

After your 231805, I rewrote `t-oracle.txt` in `s2b-runners-V1jS1t` (the predecessor kept as `t-oracle.prev-20260928-010712.txt`). The real prefix passed on the published file.
Walking impl-17's exact chain showed the defect. I ran rev45's Step 0′ from a mirror of the real runners directory, then `"$NEW"/run-task.sh 11`:
- Step 0′ published a new directory with 32 carried lines and no `task-10.done`.
- The controller's line 16 (`11) M=10`; `task-$M.done` must read rc=0 in the directory it runs from) STOPped before Task 11 was extracted.
`resume.sh` has carried Task 9's receipts since rev39, but never Task 10's. rev45's walks ran Step 0′ and the Task 11 body separately, and that is my miss.
rev46 binds and carries Task 10's eleven receipts exactly as rev39 did Task 9's: the controller's copies, the runner's digest, and the one owning token's prologue records found by content. It does so only beside a carried Task 9.
Walked (`results/rev46-walks/`):
- **YES:** Step 0′ carries 43 lines byte-equal. The sealed controller passes line 16, extracts and proves Task 11, and the prologue writes its record. The body then STOPs at a helper the walk tampered on purpose, so nothing reaches the real `results/`. The body itself was walked end to end in rev45.
- **NO:** four receipt and ownership mutants STOP in pre-flight.
- **Regression:** a directory with no Task 10 records resumes with 32 lines.
The implementer independently added a `task-10-without-task-9` control.

## What the token then names (for the record; nothing moves before the carry)

1. On the carry, `t-oracle.txt` in `s2b-runners-V1jS1t` is preserved again (the rev45 file kept) and rewritten with `carry_relay=<the carry's path>` and exactly one `plan_sha256=86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa` line.
2. `intg-substep2b-impl-17` issues at PARENT `intg-substep2b-plan-review-48`: Step 0′ (43 carried lines), then Task 11 ONCE via `"$RUNNERS"/run-task.sh 11`, then return.
3. The return carries your two 231805 conditions: the declaration lines verbatim, and the H0 rehearsal numbers.
4. Task 12 waits on PR #28's undraft and the operator's bare merge token.

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: this relay (a path-scoped commit follows), no trailer; the plan artifact at 885e754 untouched; the prefix replay in this seat's scratchpad clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
