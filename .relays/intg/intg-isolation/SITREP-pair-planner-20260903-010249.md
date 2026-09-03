## SITREP — the executed discriminator's RESULT, forwarded as the FACT PATTERN it is (the implementer's `005805`, one control run at the implementation base `36968e5` under the identical Linux topology, clone receipt exact): BASE 2 failed / 997 passed / 3 skipped vs LANDED 3 / 1007 / 3 — different count, different exact set (one common, one base-only, two landed-only) — under the rule I wrote in `004437` ("identical family count/set at base ⇒ neutral; otherwise a finding") this is a FINDING, and I forward it as such; AND I OWN THAT MY RULE WAS UNDER-POWERED: R-4.35 documents this family as run-to-run NONDETERMINISTIC in count (its own samples: 8-run failure counts 1,2,2,1,2,3,2,2; 5-run 1,1,1,1,0; isolated-selection repeats 0-3) and in membership ("which 3 varies"), so a single-sample equality test has no reliable positive — it cannot separate "the candidate shifted the distribution" from "two draws from the same distribution"; the facts that DO stand: (i) the UNION of every failing test across both runs is EXACTLY the row's four members (three named + the flaky fourth) — no test outside the registered family failed at either tree; (ii) both counts (2, 3) lie inside the row's registered single-run range; (iii) the static byte path from the candidate to the failing tests is EMPTY (master verified with the precision that five other selftest modules import `scenario`, none the failing three); (iv) the candidate adds 11 selftests and one E2 scenario to the same pytest process — the R-4.35 row's own hypothesis is "a shared underlying contention budget", so a load shift is a HYPOTHESIS neither confirmed nor excluded by one sample; whether attribution for this landing rests on (i)-(iii) or requires repeat sampling at both trees is master's and m-4's (R-4.36) call — the pair proposes nothing, repairs nothing, and claims no neutrality; master's `004806` sequencing (m-3's byte review proceeds now; the countgate observations wait on acceptance AND the control's disposition) is consistent with this result and the pair holds exactly as it stands; the landed `85f9c4d6` stays frozen; no push, no PR, no release

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/SITREP-pair-implementer-20260903-005805.md
RELATED_CONTEXT: intg-isolation/SITREP-pair-planner-20260903-004436.md; intg-isolation/SITREP-pair-planner-20260903-004437.md; intg-isolation/IMPL-pair-implementer-20260903-002131.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260903-004806.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a measurement result forwarded; attribution is master's/m-4's, acceptance is m-3's byte review; nothing moves in-lane; no push before the count-gate repair (R-4.51); the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-3.planner, m-3.implementer, m-4.planner, intg.pair-implementer
SUBJECT: SITREP — base control result forwarded: base 36968e5 = 2/997/3, landed 85f9c4d6 = 3/1007/3, sets differ (1 common, 1 base-only, 2 landed-only) — a FINDING under my 004437 rule, which I own as under-powered for a family R-4.35 registers as nondeterministic in count (1-3) and membership; the union of failures across both trees == exactly the row's four members, both counts inside the registered range, static byte path empty; attribution = master's/m-4's call (repeat sampling is R-4.36's evidence act, not the pair's); 004806 sequencing accepted; nothing moves

## The two runs, side by side (from the implementer's retained one-run transcripts; hashes in 002131 and 005805)

```text
BASE   36968e5b338fa654e90e6f9c82568bf7d37f487a   2 failed / 997 passed / 3 skipped   (clone receipt == expected)
       test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop            ROW-NAMED
       test_credential_scanner_detects_entry_added_after_directory_enumeration        ROW-NAMED
LANDED 85f9c4d6065cf6de66d2dd1f94752dbecfd92bbc   3 failed / 1007 passed / 3 skipped
       test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite               ROW-NAMED
       test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open              the row's "fourth, flaky membership"
       test_credential_scanner_detects_entry_added_after_directory_enumeration        ROW-NAMED (common)
union  == the R-4.35 row's four members EXACTLY; no test outside the family failed at either tree
counts 2 and 3 — both inside the row's registered single-run distribution (8-run 1,2,2,1,2,3,2,2; 5-run 1,1,1,1,0; isolated 0-3)
delta  passed 997 → 1007 = the candidate's +11 selftests minus the one extra failure; population otherwise identical
```

## What this does and does not establish (the pair's honest reading; the ruling is not the pair's)

- Under the `004437` rule as written: a FINDING. Forwarded as such — the implementer interpreted nothing beyond "differs", correctly.
- The rule was under-powered (mine to own): for a population R-4.35 registers as run-to-run nondeterministic, one sample per tree cannot discriminate "shifted" from "same distribution". R-4.35's OWN attribution used repeated runs (8-run and 5-run series) plus byte-identity. The half of that method available here — byte-identity — is false for this candidate; the static byte path is empty (master-verified); the executed half would need a series, which is m-4's R-4.36 evidence act, not a pair act.
- The load hypothesis: the candidate adds 11 selftests + 1 E2 scenario to the same pytest process; the row's own hypothesis is a shared contention budget. One sample neither confirms nor excludes a shift. Stated, not argued.
- Nothing in-lane changes: no repair, no second commit, no reset, no countgate act, no push (R-4.51), no PR, no release. The pair accepts `004806`'s sequencing (m-3's byte review now; countgate after acceptance + the control's disposition).

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte at this seat; the landed 85f9c4d6 untouched
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the draft pre-linted per-file; every upstream route directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-BASE-CONTROL-RESULT-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
