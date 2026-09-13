## SITREP — revised R-4.50 landing census STOP on history line order; push unspent

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
STATUS: LANDING-CENSUS-ORDER-STOP
DISPATCH_ID: intg-r450-merge-token-resume-order-stop-1
PARENT_DISPATCH_ID: intg-r450-merge-token
IN_REPLY_TO: ../pdc/master/relays/intg-r450-merge-token/MERGE-GATE-operator-20260913-144619.md
RELATED_CONTEXT: intg-r450/SITREP-pair-implementer-20260913-134320.md; intg-r450/MERGE-GATE-pair-planner-20260913-135647.md; ../pdc/master/relays/intg-r450-discover-parity-act/MERGE-GATE-master-reviewer-20260913-143104.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — rev4 requires the history census to equal the written population file line for line after its declared sort reduction, but the unqualified sort in this seat's C.UTF-8 collation produces a different order for the same 34 paths. Step (3) STOP fired; a clarified/pinned collation contract and renewed operator authorization are required before any push. This seat will not change locale opportunistically, reorder the population file, or retry the push. Release hold ABSOLUTE.
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: R-4.50 operator-authorized resume of the 133413 landing at revised §7 step (3), stopped before step (4)
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 dd7ec27bee1e45cf2226446f00c58c86efffbe67c20d1e56d4fc824f7661716f
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: STOP UP — revised whole-payload census on pinned merge 4cf135ee: tree 69/69 line-equal and A/B value checks pass; history same 34-path set but line 6 order differs under C.UTF-8; no dry-run/push, origin/main B, PR #26 OPEN

The operator's new bare `DISPATCH MERGE` (`144619`) is addressed solely to this seat and exact-file lint rc 0. It binds the prior token/STOP, packet rev4 `d15e5d0231dd8d284ff34f0f6271487be8adc212aabc3934c128187ed17476c3`, population file `results/intg-r450-main-head-census-20260913.txt` at SHA-256 `6d8cfe4c22115a2a04bfacc685e12297f6e7bfc548cb40faedbce0b6d76910fb`, and only the already-created merge `4cf135ee97f57021c5fc5fd5343de6f655fb0d24`. Those file hashes matched before the census. The pinned merge still has parents `1e6b0854acb4ec9c8d9f575a7de8da9152ba2e35` and H′ `e8a1128d75cd4693d21269c4d040095df570f116`, tree `49dcdeef06abbb6b0fad0804f76df1166288aa5b`; the product-root H′→merge diff is empty. Later local `main` is `ddaeb4ef04a7e947d3600734643a0b075d4519c9`; no second merge or amend occurred.

I reran the plan's alternation on the LITERAL pinned merge across its whole tree and reachable history. The tree arm returned 69 locations and matched the population file's 69 `path:line` entries **line for line**. Its declared A/B/C class counts are 3/64/2; the class-A and class-B matches resolve to the same one synthetic fixture token, class C to one distinct value, two distinct matched values total. The history producers returned rc 0, reduced to 34 unique paths; the expected and actual **sets** are equal (no missing/extra path), but the line-for-line comparison is **red**. The first order difference is entry 6: the file puts `docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md` there, while this seat's `sort -u` puts `docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md` there. This shell reports `LC_ALL=C.UTF-8` and `LC_COLLATE=C.UTF-8`; the written file's history order equals `sort -u` under `en_US.UTF-8`, but not under `C.UTF-8`. The plan's Task 7 reduction and rev4 §7 step (3) do not pin a locale. The fail-closed script stopped at the history line mismatch before its product-scoped assertion, so I make no independent product-scoped pass claim for this resumed run. Names and status, without matched text, are preserved in `/Users/jack/Programming/bivpak-evidence/r450-merge-resume-20260913-TiN3axYe/census-order-stop.txt`.

Rev4 §7 step (3) and the operator's relay require any line discrepancy or input error to STOP before step (4). I stopped. There was **no dry-run and no push attempt**; the one push attempt remains unspent but not executable under this red predicate. Fresh remote observation reads `origin/main` at B `bbf297e36a38a1fab8c2675f945098a0633f9f8b`; PR #26 remains OPEN at H′ with `mergedAt=null`. The local merge remains in history, unpublished. Pair Planner: route the collation/line-order ambiguity to master and operator; do not characterize the equal set as a passing line-for-line census or silently pin `en_US.UTF-8` at this seat. No tag, release, or deployment.

ACTIONS_GIT_REF: no new commit, merge, amend, dry-run or push by this resumed act. Prior authorized local merge `4cf135ee97f57021c5fc5fd5343de6f655fb0d24` remains; current local main `ddaeb4ef04a7e947d3600734643a0b075d4519c9`; origin/main remains B `bbf297e36a38a1fab8c2675f945098a0633f9f8b`; PR #26 OPEN. Only external diagnostic receipt and this daemon-submitted relay are this seat's new writes.
RELAY_LINT: engine-rendered per-file lint required; exact-file status to be checked on render. Root-wide inherited findings are not rewritten.
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-planner
FINAL_GIT_STATUS_SHORT: before filing, `.relays/intg` and the pinned population path have empty porcelain; the overall worktree retains inherited S4 modified projections/untracked S4 files, and local main is ahead of origin by unpublished docs and merge commits. Filing changes only this relay and the daemon-owned intg INDEX projection.
