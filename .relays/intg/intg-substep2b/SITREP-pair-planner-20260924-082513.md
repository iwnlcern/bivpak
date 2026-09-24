## SITREP — THE WORD FOR THE FRESH CARRY: rev29 STANDS — the implementer's `intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-080955.md` (`intg-substep2b-plan-review-28`, PARENT plan-30) APPROVES `6ef818b3aea624360fa51aa6593953b21b564e34218524dea002b20b62b6f59a` at 7774feb with no must-revise, after its own replay of Task 9's new lines 21–35 (2 YES, 10 NO, each at its own guard) and its read of every consumer. Please carry the five fields below verbatim TO intg.pair-planner; only the plan digest differs from 184303. m-3's `C8_CLASS_SET: discharged` (081947) is seen here as CC and reaches my GO through your carry of it. One new standing step at this seat: the producer gate. No product byte; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-080955.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260924-080955.md; intg-substep2b/PLAN-pair-planner-20260924-074742.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-080734.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-080645.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260924-081947.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260923-184303.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/producer-gate/README.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the word for the fresh carry at rev29's approved digest; no plan byte moves; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-3.planner, m-1.planner, m-4.planner, operator
SUBJECT: SITREP — the word: rev29 6ef818b3 stands (080955 approve at the exact hash, plan-review-28); carry the five fields below verbatim TO intg.pair-planner (only T_ORACLE_PLAN_SHA256 moves from 184303); the T-ORACLE prefix replayed at the new digest (YES + carry-to + stale-digest NO); m-3's C8_CLASS_SET discharged seen; the producer gate adopted as a standing pre-token step
REPO: `../bivpak` docs lane — this relay (path-scoped commit follows), no trailer; the plan at 7774feb untouched (live == blob == 6ef818b3aea6…); product bytes untouched at this seat. `../pdc` read-only at 5fcc90ce: the three owner objects tracked and unmodified, their digests computed at this filing; 080734, 080645 and 081947 read. The prefix replay ran in scratch clones only (bivpak at fd053b7, pdc at 5fcc90ce, a synthetic COMMITTED carry); nothing written under `../pdc`.
BRIDGE: intg.pair-planner → master.master-planner (the digest; the five field lines; the producer gate); implementer CC (your approve is the token's PARENT; the 072544 STOP relay still carries no INDEX row — please submit it through the engine); m-3 CC (your word reaches the GO through master's carry); m-1 / m-4 CC; operator CC (no push, no PR, no merge, no release)

## The carry, as the gate reads it

A `PHASE: PLAN` / `AUTHORITY: plan-only` relay from master with the TO line EXACTLY `TO: intg.pair-planner` (the gate greps that whole line; other seats go in CC), filed under `master/relays/` in pdc and COMMITTED (tracked and unmodified), carrying these five header lines byte-for-byte, with exactly one `T_ORACLE_VERDICT:` line in the relay:

```text
T_ORACLE_VERDICT: cleared
T_ORACLE_PLAN_SHA256: 6ef818b3aea624360fa51aa6593953b21b564e34218524dea002b20b62b6f59a
T_ORACLE_M3: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-033307.md sha256=20c9f24d0652285298ca88bd67d66d3cd861d1ebc2093b6606d76a1d4a9554e7
T_ORACLE_M1: master/relays/intg-2b-wiring-act/DESIGN-planner-20260919-155106.md sha256=e706797eb23dc5b1e16f38b6794d3f46a20191212b4d32f0f9f0b83c0e204375
T_ORACLE_M1_REQUEST: master/relays/intg-2b-wiring-act/PLAN-master-planner-20260919-131720.md sha256=6e5b30237723b57712750183a2a16417776e455d28fad8b90f02dba4f5adfe66
```

EXECUTED before this filing: the plan's T-ORACLE prefix (the first 56 lines of Task 4 Step 5's block, byte-present once in rev29, sha `1c437ac4…`, unchanged since rev27) ran in scratch clones of bivpak and pdc on a synthetic COMMITTED carry made from your 184303 with only the plan digest changed.
Results: `t-oracle OK`, rc 0, one receipt; the same carry with `TO: intg.pair-planner, intg.pair-implementer` gives `STOP-t-oracle carry-to`, rc 1, no receipt; a locator holding the rev28 digest against the rev29 plan gives `STOP-t-oracle plan-sha-mismatch-live-…`, rc 1, no receipt.
(A first attempt was invalid: a zsh glob left the synthetic carries uncommitted, so all three cases stopped `untracked-carry`. It was discarded and re-run with the carries committed by explicit path.)
The three object digests were computed at this filing over the tracked, unmodified files at pdc HEAD 5fcc90ce. They are byte-identical to 184303's.

## What the token then names (for the record; nothing moves before the carry)

On the carry: `$RUNNERS/t-oracle.txt` in the directory the pointer names (read as its own command; today `s2b-runners-Xi2bWL`) is preserved as `t-oracle.prev-<stamp>.txt` and rewritten with `carry_relay=<the carry's pdc path>` and exactly one `plan_sha256=6ef818b3aea624360fa51aa6593953b21b564e34218524dea002b20b62b6f59a` line.
`r472-owner-words.txt` and `red1-owner-words.txt` are unchanged and carried.
The T-ORACLE prefix and the R-4.72 gate then run from the candidate against the real files, `resume.sh` (unchanged `192369f3…`) is walked on a mirror, and the producer gate is run on the live plan.
Then `intg-substep2b-impl-9` issues at PARENT `intg-substep2b-plan-review-28` with SCOPE_DIFF the same 52 paths. Only the Task 9 count-cell path is still expected, and every other row is LANDED.
Its order is Step 0′, then Task 9, then Tasks 10–11. Task 10 waits on my GO with the three H reviews, your 042625 condition (1), your 060842 on R-4.74, and your carry of m-3's 081947.

## The producer gate (your 080734 suggestion, cut at this seat)

`docs/sprints/2026-08-27-intg-consent-fabric/results/producer-gate/` (commit fd053b7): every literal `$EVID` / `$RUNNERS` READ in the RUN tasks must have an earlier writer.
Writers a textual scan cannot see (25) are classified one row each against their real writer; any orphan outside that set, or any stale row, fails.
MY FIRST CUT CHECKED ONLY `[ -s … ]` GUARDS AND PASSED a rev29 mutant with the names producer deleted (the file was still read by `grep` and `shasum`), so it was rebuilt to gate on reads.
Discriminator: rev28 rc 1 (exactly the two real orphans); rev29 rc 0; names-only mutant rc 1 (that file); manifest-only mutant rc 1 (its pair). It is a standing step before every token at this seat, and it adds no plan byte.

Receipt: m-3's 081947 (`C8_CLASS_SET: discharged`; the H drop owned; H's kind and exit 3 landed at CLI level with the exact recipe, envelope measured valid; the harness H row registered as an m-3 residual) is seen here as CC; my GO cites your carry of it.
The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this relay (path-scoped commit follows), no trailer; the plan artifact at 7774feb untouched; the prefix replay in this seat's scratchpad clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.3 `relay-lint.py --no-freshness` on the draft (2.9.3 is the linter of record per 171038); python-written; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
