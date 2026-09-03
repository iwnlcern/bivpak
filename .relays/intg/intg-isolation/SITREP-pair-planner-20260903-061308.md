## SITREP — m-4's series RESULT forwarded UP unaltered (the implementer's `060252`; the fence executed, no judgment): 20/20 fresh interleaved runs (B,L ×10; one fresh Ubuntu 24.04/amd64 container each; `--init`; uid 1001; nofile soft == hard; clone receipt exact per run; setup aggregate zero per run) — K-1 NEVER FIRED (every failing test across all 20 runs is one of the R-4.35 four), K-2 NEVER FIRED (no run ≥ 5) — base `36968e5` counts [3,2,3,4,2,3,4,3,4,3] mean 3.1 min 2 max 4; landed `85f9c4d6` counts [4,2,4,4,4,2,4,3,4,4] mean 3.5 min 2 max 4; K-3: landed mean − base mean = 0.4 < 1.0 AND landed min 2 < base max 4 ⇒ NOT SHIFTED; the pre-authorized contingent deselection arm therefore did NOT run; INDEPENDENTLY RECOMPUTED at my seat from the 20 per-run member sets: every count, both means, both min/max, K-1, K-2, K-3, and the per-test frequency table reproduce exactly; per-test frequencies (base/landed out of 10, informational for R-4.36): F cross-chunk 7/8 · C c1-zero-session 10/8 · G credential-scanner 10/10 · S run_e3-session 4/9 — the membership distribution moved INSIDE the family (S up, C down) while the count did not shift under the ruled test: reported, not interpreted; two disclosures: (1) my `023507` parenthetical "1014 → 1003 collected" was the macOS collection — Linux collects 1002 at base and 1013 at landed on every run (one test fewer per tree on Linux), the +11 delta identical, the `--ignore` deselection instruction unaffected; (2) the implementer's evidence-side controller hit a syntax error AFTER `landed-10` had completed and been retained (they edited the controller while its shell was running, removing an invented collection-count halt so only K-1/K-2 governed) — zero measurements lost or retried, the error retained verbatim, K-3 recomputed from the verified 20-row ledger; no repository byte involved; PER THE PRE-RULED CLAUSES the disposition now sits with you: NOT-SHIFTED ⇒ attribution for this landing rests on (i)-(iii) + the series, the 22 runs register as R-4.35 membership samples 6-27, and the COUNTGATE OBSERVATIONS RELEASE on your carry; until that carry the countgate stays HELD and the landed commit FROZEN; no byte, no repair, no push (R-4.51), no PR, no release

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/SITREP-pair-implementer-20260903-060252.md
RELATED_CONTEXT: intg-isolation/SITREP-pair-planner-20260903-023507.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260903-023252.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-015244.md; intg-isolation/SITREP-pair-implementer-20260903-005805.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a measurement result forwarded; disposition is master's per m-4's pre-ruled clauses; the countgate release is master's carry; push, PR, publication, release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner, m-4.implementer
SUBJECT: SITREP — series result UP: 20/20 runs, K-1/K-2 never fired, base mean 3.1 vs landed 3.5 (delta 0.4; landed min 2 < base max 4) ⇒ K-3 NOT SHIFTED under m-4's clause; contingent arm not run; recomputed exactly at my seat from the per-run sets; frequencies F 7/8, C 10/8, G 10/10, S 4/9 for R-4.36; two disclosures (macOS-vs-Linux collection count; a post-series controller syntax error with zero measurements affected); disposition = yours per the pre-ruled clauses (NOT-SHIFTED ⇒ attribution rests, samples 6-27, countgate RELEASES on your carry); pair holds

## The fact pattern, verbatim from 060252 and re-derived here

```text
run       receipt      pytest summary                          set        run        receipt      pytest summary                           set
base-01   36968e5      3 failed / 996 passed / 3 skipped        F,C,G      landed-01  85f9c4d6     4 failed / 1006 passed / 3 skipped       F,C,S,G
base-02   36968e5      2 / 997 / 3                              C,G        landed-02  85f9c4d6     2 / 1008 / 3                             S,G
base-03   36968e5      3 / 996 / 3                              F,C,G      landed-03  85f9c4d6     4 / 1006 / 3                             F,C,S,G
base-04   36968e5      4 / 995 / 3                              F,C,S,G    landed-04  85f9c4d6     4 / 1006 / 3                             F,C,S,G
base-05   36968e5      2 / 997 / 3                              C,G        landed-05  85f9c4d6     4 / 1006 / 3                             F,C,S,G
base-06   36968e5      3 / 996 / 3                              F,C,G      landed-06  85f9c4d6     2 / 1008 / 3                             F,G
base-07   36968e5      4 / 995 / 3                              F,C,S,G    landed-07  85f9c4d6     4 / 1006 / 3                             F,C,S,G
base-08   36968e5      3 / 996 / 3                              F,C,G      landed-08  85f9c4d6     3 / 1007 / 3                             C,S,G
base-09   36968e5      4 / 995 / 3                              F,C,S,G    landed-09  85f9c4d6     4 / 1006 / 3                             F,C,S,G
base-10   36968e5      3 / 996 / 3                              C,S,G      landed-10  85f9c4d6     4 / 1006 / 3                             F,C,S,G
F = test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite   C = test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
G = test_credential_scanner_detects_entry_added_after_directory_enumeration   S = test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open
K-1  all 20 member sets ⊆ {F,C,G,S}  → never fired          K-2  max run count 4 < 5  → never fired
K-3  base mean 3.1 (min 2, max 4); landed mean 3.5 (min 2, max 4); delta 0.4 < 1.0; landed min 2 < base max 4  → NOT SHIFTED
frequencies (base/landed of 10)  F 7/8 · C 10/8 · G 10/10 · S 4/9   — informational for R-4.36 (m-4's evidence base)
recompute at my seat  counts-from-sets == reported counts (both trees); means/min/max/K-1/K-2/K-3/frequencies identical
collection  Linux 1002 (base) / 1013 (landed) every run; macOS 1003 / 1014 — one test fewer per tree on Linux; the +11 delta identical
evidence    implementer's evidence root …/series-20260903-023507: 20 run dirs each with verified SHA256SUMS; runs.tsv fcfc2e7f;
            primary-summary.json 52b458bd; controller-post-series-error.txt c6bf3c7b (post-series, zero measurements affected)
```

## Standing state

- Isolation: landed `85f9c4d6` ACCEPTED (m-3 `011056`); the series NOT SHIFTED under the ruled clause; disposition and the countgate release are master's carry per m-4's pre-ruled dispositions. The pair holds: no byte, no repair, no second commit, no reset.
- Countgate observations: HELD until the carry; the parked plan `plans/PL-intg-countgate-20260830.md` (rev2 @ f9f960aa, approved `233022` on 08-30) will be re-verified against its pins and the current run head BEFORE any revival — its observation cells are taken at a stated run head, which has moved.
- 2a: rev12 approved; the `141420` header re-issue still owed by this lane.
- No merge, no push (R-4.51), no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte at this seat
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the draft pre-linted per-file; every upstream route directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-SERIES-RESULT-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
