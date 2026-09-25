## SITREP — THE WORD FOR THE FRESH CARRY: rev32 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-164230.md` (`intg-substep2b-plan-review-32`, PARENT plan-33) APPROVES `90b5274d11f60afa015fe95726675a6aebee048ff6d18f2ed78ffe1fa476ed0f` at 783dd49 with no must-revise, after its own fault replay: `cp` failing after prefixes 0–4, a corrupt copy returning 0, and a failed rename, each followed by a clean same-token retry, plus `finalize.py`'s path-level split of the fault stage from `task-9/`. Please carry the five fields below verbatim TO intg.pair-planner; only the plan digest differs from your 140701. No product byte; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-164230.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-164230.md; intg-substep2b/PLAN-pair-planner-20260924-160113.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-153636.md; intg-substep2b/PLAN-pair-planner-20260924-151216.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-145529.md; intg-substep2b/PLAN-pair-planner-20260924-143458.md; intg-substep2b/IMPL-pair-implementer-20260924-143008.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-140701.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry at rev32's approved digest; no plan byte moves; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev32 90b5274d stands (164230 approve at the exact hash, plan-review-32) after three revisions of one runner-prologue line (impl-9 STOP → rev30; MUST-2B-48 confinement → rev31; MUST-2B-49 atomic publication → rev32); carry the five fields below verbatim TO intg.pair-planner (only T_ORACLE_PLAN_SHA256 moves from 140701); the T-ORACLE prefix replayed at the new digest (YES + carry-to + stale-digest NO)
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at 783dd49 untouched (live == blob == 90b5274d11f6…); product bytes untouched at this seat. `../pdc` read-only at b2e2740b: the three owner objects tracked and unmodified, their digests computed at this filing. The prefix replay ran in scratch clones only (bivpak at 8099acd, pdc at b2e2740b, synthetic COMMITTED carries); nothing written under `../pdc`.
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines); implementer CC (your 164230 approve is impl-10's PARENT); m-3 / m-1 / m-4 CC (nothing asked); operator CC (no push, no PR, no merge, no release)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (the gate greps that whole line; other seats go in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 90b5274d11f60afa015fe95726675a6aebee048ff6d18f2ed78ffe1fa476ed0f
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE prefix (the first 56 lines of Task 4 Step 5's block, byte-present once in rev32, sha `1c437ac4…`, unchanged since rev27) ran in fresh scratch clones of bivpak (8099acd, holding rev32) and pdc (b2e2740b), against synthetic carries made from your 140701 with only the plan digest changed, committed by explicit path (tracking asserted with `git ls-files` before any result was read).
Results: `t-oracle OK`, rc 0, one receipt. The same carry with `TO: intg.pair-planner, intg.pair-implementer` gives `STOP-t-oracle carry-to`, rc 1, no receipt. A locator holding the rev31 digest against the rev32 plan gives `STOP-t-oracle plan-sha-mismatch-live-…`, rc 1, no receipt.
The three object digests were computed at this filing over the tracked, unmodified files at pdc HEAD b2e2740b. They are byte-identical to 140701's.

## What changed since your 140701 carry (one BLOCK, one template)

impl-9 (issued on your 140701) STOPPED at Task 9's prologue (143008): the runner-record copy was FLAT into `$EVID/runners/`, where impl-8's rev28 `task-9.sh` sits at 0500. The defect was mine: my token asserted home state I had never run against the home.
rev30 moved the copy to `$EVID/runners/<token-id>/`, and was must-revised (145529, MUST-2B-48) because a symlinked token directory or a dangling name escaped the home and was invisible to `finalize.py`.
rev31 confined it: real, physically resolved runners and token directories, and all four names lexically absent. It was must-revised (153636, MUST-2B-49) because a `cp` failing mid-copy left a partial record under the final names that blocked any same-token retry, and rev31's text had accepted that state.
rev32 publishes the four records as ONE unit, `runners/<token-id>/task-N/`: a fresh `mktemp -d` stage in the token directory, exact verification, one same-directory rename, then re-verification. A fault leaves `task-N` absent and its own `stage-task-N.*` as the durable fault record, and a same-token retry publishes cleanly. The stated residual is concurrency, which the one-runner-at-a-time lane excludes.
In every revision only `plan_blocks.py` moved among the 22 BLOCKs (`PROLOGUE_EVID`). task-0, `resume.sh` (`192369f3…`) and `run-task.sh` are byte-identical to rev29, and each revision was walked on `cp -Rp` mirrors of the real evidence home with the previous prologue as its control.
The flat impl-8/impl-9 remnants in the home are preserved verbatim and recorded in the plan.

## What the token then names (for the record; nothing moves before the carry)

On the carry: `$RUNNERS/t-oracle.txt` in the directory the pointer names (read as its own command; today `s2b-runners-IvrESr`, published by impl-9's Step 0′) is preserved as `t-oracle.prev-<stamp>.txt`, if present, and rewritten with `carry_relay=<the carry's pdc path>` and exactly one `plan_sha256=90b5274d11f60afa015fe95726675a6aebee048ff6d18f2ed78ffe1fa476ed0f` line.
`r472-owner-words.txt` and `red1-owner-words.txt` are unchanged and carried.
The T-ORACLE prefix and the R-4.72 gate then run from the candidate against the real files, `resume.sh` is walked on a mirror, the producer gate is run on the live plan, and rev32's prologue walk is re-run on a fresh mirror of the real home.
Then `intg-substep2b-impl-10` issues at PARENT `intg-substep2b-plan-review-32` with SCOPE_DIFF the same 52 paths. Only the Task 9 count-cell path is still expected, and every other row is LANDED (the candidate is unchanged at a83657e).
Its order is Step 0′, then Task 9, then Tasks 10–11. Task 10 waits on my GO with the three H reviews, your 042625 condition (1), your 060842 on R-4.74, and your 140701 carry of m-3's 081947.
The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), no trailer; the plan artifact at 783dd49 untouched; the prefix replay in this seat's scratchpad clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.3 `relay-lint.py --no-freshness` on the draft (2.9.3 is the linter of record per 171038); python-written; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
