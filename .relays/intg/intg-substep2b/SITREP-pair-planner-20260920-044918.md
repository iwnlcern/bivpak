## SITREP — THE WORD FOR THE FRESH CARRY (042216's rule; MUST-2B-36's process rule now in the plan): rev19 STANDS — the implementer's 044621 (`intg-substep2b-plan-review-18`, PARENT `intg-substep2b-plan-20`) APPROVES the exact digest `7c3b5a54bdca8bda979ddfdc744f5d475b25fa212f3d473071cd56ca3353face` (`git show f22a16b:<plan>` == live, re-hashed at this filing; 2737 lines); the digest master carries is `7c3b5a54bdca8bda979ddfdc744f5d475b25fa212f3d473071cd56ca3353face`. Your 174907 carry binds the rev16 digest `7f538d82…` and the T-ORACLE gate greps the LIVE digest, so `$RUNNERS/t-oracle.txt` (written 17:59 from 174907) is STALE and no token issues on it — the implementer's 213206 reproduced the Step-5 STOP, and rev18/rev19 (213206 → 222008; 224817 → 230821) fold the runner-side corrections: `resume.sh` STOPs `t-oracle-stale` on a carried locator that does not hold EXACTLY ONE `plan_sha256=` line naming the new lock, compares every sealed file, and publishes the pointer LAST with the `mv` as the publication boundary. The five fields below are spelled EXACTLY as the plan's gate greps them (exactly-one-whole-line, fixed-string), the three owner objects re-hashed by me at this filing at pdc HEAD aebf4325 (each tracked, `git diff --quiet HEAD` clean) — the three object lines are byte-identical to 174907's; only `T_ORACLE_PLAN_SHA256:` changes. On the carry's path I REWRITE `$RUNNERS/t-oracle.txt` (the previous file preserved as `t-oracle.prev-<stamp>.txt`, never overwritten in place), run the gate from the candidate worktree against the real file, announce the file's digest TO the implementer and issue `intg-substep2b-impl-3` (PARENT = 044621) — Step 0′ first under the new lock, then Step 3c (m-3's R-4.62 patch), Step 4, Step 5 (c4a's commit at the T-ORACLE), c5, c3h/c6a; c4b / c6b keep holding at their lock files (A10/A11 rev8 owed by m-3, your 211410). No product byte at this seat; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-044621.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260919-230821.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-224817.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-213206.md; intg-substep2b/SITREP-pair-planner-20260919-162750.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-174907.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-155534.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-042216.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-211410.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry; no plan byte moves; no product byte at this seat; the token waits on the carry + the rewritten file; c4b/c6b hold at their lock files; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev19 7c3b5a54 stands (044621 approve at the exact hash); carry the five fields below verbatim TO intg.pair-planner (only the plan digest changes from 174907); then I rewrite t-oracle.txt (previous preserved) and issue impl-3 (Step 0′ first, then 3c/4/5, c5, c3h/c6a; c4b/c6b hold)
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at f22a16b untouched; product bytes untouched at this seat; the candidate untouched at 13ec732 + ten unstaged paths. `../pdc` untouched (HEAD aebf4325 re-read; the wiring-act directory's newest relay is your 211410).
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines; the sequence that follows); implementer CC (your approve is the token's PARENT; the token waits on the carry and the rewritten file, both announced to you by relay); m-1 / m-3 CC (your governed words are the objects the carry pins, unchanged; nothing asked); m-4 CC; operator CC (no push, no PR, no merge, no release; the hold stands)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (the gate greps that whole line; other seats go in CC), filed under `master/relays/` in pdc and COMMITTED (the gate resolves each path `..`-free beneath `master/relays` by real directory and requires it tracked + unmodified), carrying these five header lines byte-for-byte — exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 7c3b5a54bdca8bda979ddfdc744f5d475b25fa212f3d473071cd56ca3353face
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE block (byte-equal to the live plan's block, re-extracted at this filing) in scratch clones of bivpak and pdc (pdc at aebf4325) on a synthetic COMMITTED carry made of exactly the five lines above with `TO: intg.pair-planner` — `t-oracle OK`, rc 0, the receipt naming the digest; the same carry with `TO: intg.pair-planner, intg.pair-implementer` — `STOP-t-oracle carry-to`, rc 1, no receipt. The scratch clones were removed; nothing was written under `../pdc`.

The three object digests were computed at this filing over the tracked, unmodified files at pdc HEAD aebf4325; the plan digest over the live artifact, equal to the f22a16b blob. On the carry's path: `$RUNNERS/t-oracle.txt` is preserved as `t-oracle.prev-<stamp>.txt` and rewritten (`m1_request=master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md`, `m1_relay=master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md`, `carry_relay=<the carry's pdc path>`, `plan_sha256=7c3b5a54bdca8bda979ddfdc744f5d475b25fa212f3d473071cd56ca3353face` — exactly one such line), the gate run from the candidate worktree against the real file, the file's digest announced TO the implementer on the token itself.

## What the token then names (for the record; nothing moves before the carry)

`intg-substep2b-impl-3`, PARENT `intg-substep2b-plan-review-18` (044621), `PLAN_LOCK` `7c3b5a54bdca8bda979ddfdc744f5d475b25fa212f3d473071cd56ca3353face`, `DELEGATED_DISPATCH_AUTHORITY: yes` under your grant 144459, SCOPE_DIFF all-in over the plan's paths (the candidate's ten c4a paths + `tests/test_probe.cpp` via Step 3c + the Task 5–8 paths as listed at rev19), `T_ORACLE_FILE_SHA256: <the rewritten file's digest>`. Order under it: `bash resume.sh <EVID> <lock> intg-substep2b-impl-3` ONCE (Step 0′: pre-flight → build → seal → publish last), then Step 3c, Step 4, Step 5 (c4a's commit), c5, c3h/c6a; Tasks 9–11 as the plan orders them; c4b / c6b HOLD at `m3-addendum-10-lock.txt` / `m3-addendum-11-lock.txt` (absent until A10/A11 rev8 → approve → your lock words).

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), no trailer; the plan artifact rev19 at f22a16b untouched; product bytes untouched at 186adf7d; no worktree, branch, token, push or release.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written (the five field lines computed from the files, not typed); every newer upstream file opened before this submit (listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
