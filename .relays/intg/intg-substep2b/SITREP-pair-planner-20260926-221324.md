## SITREP — THE WORD FOR THE FRESH CARRY: rev40 STANDS. The implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260926-220656.md` (`intg-substep2b-plan-review-41`, PARENT plan-42) APPROVES `682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607` at e86c891, under the operator's registered Plan-contract waiver. rev40 folds impl-13's STOP in the c10 mutant gate (my defect; c10 `2291a46` stands, green). Please carry the five fields below verbatim TO intg.pair-planner; only the plan digest differs from your 203312. No product byte; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260926-220656.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260926-220656.md; intg-substep2b/PLAN-pair-planner-20260926-214841.md; intg-substep2b/IMPL-pair-implementer-20260926-211822.md; intg-substep2b/IMPL-pair-planner-20260926-204715.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-203312.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260926-203555.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry at rev40's approved digest; no plan byte moves; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev40 682ceb88 stands (plan-review-41 approve at the exact hash). impl-13 committed c10 2291a46 green at its ten paths, then STOPped in c10-mutants.sh because my rev39 demanded a conforms-row FAILURE that CTest's fixture semantics make Not Run. rev40: mutants killed by their named witnesses, regate reads a verdict line, resume.sh binds Task 9 by content (the second successor). Carry the five fields below verbatim TO intg.pair-planner (only T_ORACLE_PLAN_SHA256 moves from 203312); the T-ORACLE prefix replayed at the new digest (YES + carry-to + stale-digest NO)
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at e86c891 untouched (live == blob == 682ceb885cf0…); product bytes untouched at this seat. `../pdc` read-only at d9c0d298: the three owner objects tracked and unmodified, their digests computed at this filing and equal to 203312's lines. The prefix replay ran in scratch clones only (bivpak at 0a4cab4, holding rev40; pdc at d9c0d298 plus synthetic COMMITTED carries); nothing written under `../pdc`.
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines); implementer CC (your plan-review-41 approve is impl-14's PARENT); m-3 CC (your F5 witnesses kill every mutant; the assertions now name them; your re-review is at `R/H.txt`); m-1 / m-4 CC (nothing asked); operator CC (no push, no PR, no merge, no release)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (other seats in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE prefix (56 lines, `1c437ac4…`, byte-present once in rev40) ran in fresh scratch clones of bivpak (0a4cab4, holding rev40) and pdc (d9c0d298), against synthetic carries made from your 203312 with only the plan digest changed (and, for the control, the TO line), each committed by explicit path and asserted tracked before any result was read.
Results: `t-oracle OK`, rc 0, one receipt. The same carry with `TO: intg.pair-planner, intg.pair-implementer` gives `STOP-t-oracle carry-to`, rc 1, no receipt. A locator holding rev39's digest `d5a868d3…` against the rev40 plan gives `STOP-t-oracle plan-sha-mismatch-live-…`, rc 1, no receipt.

## What happened under impl-13, and what rev40 changes

impl-13 (`intg-substep2b/IMPL-pair-implementer-20260926-211822.md`) ran Step 0′ (new runners `s2b-runners-r9Akl6`, 31 carried lines) and Task 8c Steps 0–4 red → green, committing c10 `2291a46` at exactly its ten Files-line paths (none under `src/core/repo`).
Its one `c10-mutants.sh` run then STOPped `survived-M-H1-PRE`. rev39 demanded `divergence_envelope_conforms (Failed)` under M-H1-PRE, but that row REQUIRES the fixture `biv_tests` sets up, so CTest reports it `Not Run` whenever the mutant reddens `biv_tests`. The assertion was impossible by the plan's own topology, and it sat in the one arm rev39 disclosed as unwalked; the defect is mine.
From the retained logs every mutant was killed: M-H1-PRE by (w1)'s one case, M-H1-SCHEMA by the conforms row alone with every case green, M-H1-F4 by (w3)'s two cases. No product byte is in question.
rev40 `682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607` (plan-42) changes three blocks and nothing else:
- `c10-mutants.sh`: each mutant is killed by the witness it NAMES (both CTest statuses plus the failed Catch2 cases by name), in `receipts/c10-mutants.rev40.txt` ending in ONE `verdict=ok`. impl-13's rev39 record stays pinned by digest.
- `regate.sh`: Task 9b reads that verdict line. rev39's `[ -s receipts/c10-mutants.txt ]` would have admitted impl-13's FAILED record.
- `resume.sh`: found by walking Step 0′ for impl-14 from a mirror of `r9Akl6` — rev39 bound Task 9's records to the previous directory's token, which holds only for the first successor. rev40 binds them by content to exactly one token.
This time the mutant arm was walked FOR REAL, on a scratch clone at c10 with its own venv and a fresh `ci-macos` build (7 min; `verdict=ok`), with ten NO cases served the real artifacts. The task runners are unchanged, and the producer gate is rc 0.
Your 203312 §2 waiver reading covers rev40's blocks (the same artifact, through 2b), and the implementer's approve records it so.

## What the token then names (for the record; nothing moves before the carry)

On the carry, `$RUNNERS/t-oracle.txt` in `s2b-runners-r9Akl6` (read from the pointer as its own command) is preserved as `t-oracle.prev-<stamp>.txt`, then rewritten with `carry_relay=<the carry's path>` and exactly one `plan_sha256=682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607` line.
The T-ORACLE prefix and the R-4.72 gate then run from the candidate against the real files, `resume.sh` rev40 is walked from a mirror of `r9Akl6`, and the producer gate runs on the live plan.
Then `intg-substep2b-impl-14` issues at PARENT `intg-substep2b-plan-review-41`, SCOPE 53: Step 0′, then Task 8c from Step 5 (c10 is not rewritten), then the c10 head gate, then Task 9b once, then STOP before Task 10.
The three owner reviews retake at `R/H.txt`, then my GO.
The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), no trailer; the plan artifact at e86c891 untouched; the prefix replay in this seat's scratchpad clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M .relays/intg/SEATS.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
