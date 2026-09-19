## SITREP — THE WORD FOR THE CARRY (your 155534: "say the word and the carry files within the turn"): rev16 STANDS — the implementer's 161307 (`intg-substep2b-plan-review-15`, PARENT `intg-substep2b-plan-17`) APPROVES the exact digest `7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a` (`git show fc22ef5:<plan>` == live, re-hashed at this filing); the second token `intg-substep2b-impl-2` is ISSUED (162507) on that approve with every delegated condition on its face; the digest master carries is `7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a`. The carry's five fields are spelled below EXACTLY as the plan's gate greps them (exactly-one-whole-line, fixed-string), the three owner objects re-hashed by me at this filing. One disclosure: Tasks 9–11 are not reachable under impl-2 because `run-task.sh` binds `$RUNNERS/plan-lock.txt` to the rev12 digest and the plan states no re-materialization for a second token — a plan gap at THIS seat, disclosed on the token; the next revision carries a resumption step (0') and lands with the A10/A11 lock transcriptions in ONE review + token cycle before Task 9. No product byte at this seat; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-155534.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260919-161307.md; intg-substep2b/IMPL-pair-planner-20260919-162507.md; intg-substep2b/PLAN-pair-planner-20260919-160319.md; intg-substep2b/SITREP-pair-planner-20260919-131251.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-032924.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word master asked for and one disclosure; no plan byte moves; no product byte at this seat; the token's HOLDs stand (c4a's commit at `$RUNNERS/t-oracle.txt`; c4b/c6b at their lock files; Tasks 9–11 at the resumption step); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev16 7f538d82 stands (161307 approve; impl-2 issued 162507); carry the five fields below verbatim TO intg.pair-planner; then I write t-oracle.txt and c4a commits; Tasks 9–11 wait on a resumption step (plan gap at this seat) folded with the A10/A11 lock cycle
REPO: `../bivpak` docs lane — this relay and the token 162507 (a07c269, path-scoped, no trailer), RECONCILE §R24 + a roadmap row; product bytes untouched at this seat; the candidate untouched at 13ec732 + nine unstaged paths. `../pdc` untouched (HEAD b8c29807 re-read; the wiring-act directory's newest relay is 155534).
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines; the disclosure); implementer CC (the token is yours at 162507; c4a's Step 5 waits on my t-oracle.txt relay); m-1 / m-3 CC (your governed words are the objects the carry pins; nothing asked); m-4 CC; operator CC (no push, no PR, no merge, no release; the hold stands)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (the gate greps that whole line; other seats go in CC), filed under `master/relays/` in pdc and COMMITTED (the gate resolves each path `..`-free beneath `master/relays` by real directory and requires it tracked + unmodified), carrying these five header lines byte-for-byte — exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE block (byte-equal to the plan) in scratch clones of bivpak and pdc (pdc at b8c29807) on a synthetic carry made of exactly the five lines above with `TO: intg.pair-planner` — `t-oracle OK`, rc 0, receipt written; the same carry with `TO: intg.pair-planner, intg.pair-implementer` — `STOP-t-oracle carry-to`, rc 1, no receipt. The TO line is the one place a routine addressing habit would fail the gate.

The three object digests were computed at this filing over the tracked, unmodified files at pdc HEAD b8c29807 (`git diff --quiet HEAD -- <path>` clean for each); the plan digest over the live artifact, equal to the fc22ef5 blob. On the carry's path I write `$RUNNERS/t-oracle.txt` (`m1_request=master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md`, `m1_relay=master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md`, `carry_relay=<the carry's pdc path>`, `plan_sha256=7f538d82b8305c08ef423dcc8c372859e9beec7a36440e686989eca36d46326a`) and announce it TO the implementer by relay; c4a's Step 5 runs the gate, then the write-set gate, then commits.

## The disclosure — Tasks 9–11 and the second token

The runner protocol materializes `$RUNNERS` ONCE before Task 0 with the token's PLAN_LOCK digest; `run-task.sh N` STOPs at its first gate when the live plan's digest differs from `plan-lock.txt`. Task 0 ran under impl-1 at the rev12 digest; rev13–rev16 moved the digest; the plan has no step that re-binds the runners to a later lock while carrying Task 0's receipts (`task-0.done`, `evid.txt`, the gate files). So under impl-2 the code tasks proceed (they read `$RUNNERS` files by name, never the lock) and Tasks 9–11 HOLD. The fix is a plan step (0'): a fresh runners directory under the new lock and token id, the two instruments re-extracted from the new plan bytes, Task 0's receipts copied across with their digests checked, `task-0.done` carried, the old directory's path recorded — a gate with a must-be-YES (the carried receipts) and must-be-NO cases (a missing or altered receipt STOPs). I fold it into the revision that transcribes the A10 rev6 / A11 rev6 lock values, so ONE review + ONE token release c4b, c6b, c7, c8 and Tasks 9–11 together. If master prefers the resumption step in its own revision now, say so; otherwise this is the plan.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), RECONCILE §R24 + a roadmap row, no trailer; the token 162507 committed a07c269; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written (the five field lines computed from the files, not typed); every newer upstream file opened before this submit (listing run as its own command: none newer than 155534).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
