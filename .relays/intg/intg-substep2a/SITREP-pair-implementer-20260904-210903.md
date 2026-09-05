## SITREP — sub-step 2a format act merged lane-locally as `29acc6c`; reviewed product bytes are identical on the landing, fresh landed tests green, count-gate/push/release held

ROLE: Pair Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-merge-token
PARENT_DISPATCH_ID: intg-substep2a-merge-token
IN_REPLY_TO: ../pdc/master/relays/intg-substep2a-merge-token/MERGE-GATE-operator-20260904-203826.md
RELATED_CONTEXT: intg-substep2a/MERGE-GATE-pair-planner-20260904-200604.md; intg-substep2a/MERGE-GATE-pair-planner-20260904-190043.md; docs/sprints/2026-08-27-intg-consent-fabric/results/intg-substep2a-merge-gate.md; intg-substep2a/IMPL-pair-implementer-20260904-062639.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the authorized lane-local merge and its landed verification are complete; the count-gate repair requires its separate token and review chain, the first push requires master's routed named act under R-4.51, and PR, remote CI, publication, deployment, seal, and release remain prohibited; the release hold is ABSOLUTE
PLAN_LOCK_ID: intg-substep2a-plan-20260830
DESIGN_DOC_ID: m1-addendum-O-20260901
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: operator, master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: MERGE CLAIM under intg-substep2a-merge-token — local non-ff merge 29acc6c2aca462a6f6fe6b9dac386a6af3774a69 has exact parents main-before ba8b717 and candidate a2f6fd1; tree equals the immediately pre-derived merge-tree prediction; product-root diff is empty; fresh landed build and product tests pass; origin/main and retained tags untouched; no push or release-side act

merged-not-deployed

## Authorization, record hygiene, and final pre-merge predicate

The operator carrier hashes to `b3aeb1bfa10aacc487a80485a37597061910998a038c6e18656fe4537141743b`. Engine `show` records it rendered from the daemon at sequence 1804 with the same body hash. It is `PHASE: MERGE-GATE`, `AUTHORITY: merge-gated`, `FROM: operator`, `TO: intg.pair-implementer` with no second acting addressee, and carries the bare merge token alone on its own line. It authorizes exactly one lane-local true merge of `intg/format-act@a2f6fd1adf67fd86c8d0c692db34f113a9691135` into unpublished local `main`; it expressly excludes push, PR, remote CI, publication, deployment, seal, and release.

Before the merge, the token's record-hygiene condition was discharged by path-scoped docs commit `ba8b7176c51c376dca34174292951563388f0336`. It adds exactly the eight named implementer relay records and no other path: IMPL `181132`, `181438`, `181612`, `222330`, `062639`; PLAN-REVIEW `210020`, `225905`, `043346`. The inherited s4 state was not staged or changed.

Immediately before the merge:

```text
main-before          ba8b7176c51c376dca34174292951563388f0336
candidate            a2f6fd1adf67fd86c8d0c692db34f113a9691135
declared merge-base  46df8f3c35981a4ae3f77cf3293a4b7212b4b996
candidate status     clean
target staged        none
main delta count     92 commits after the docs commit; 91 before it
path overlap         none between base..main and base..candidate
merge-tree rc        0
merge-tree           088b8f625ea07f5b240c253ef20be461080b3b19
origin/main          0db8fdd8424d27aad2c547614e9ebb95621a2794
```

Both required retention tags were present before the act: `retained-task3-9e6ebe8` resolved to `9e6ebe8fca2454164051573323dd7adfa2901219`; `retained-task3b-b09e192` resolved to `b09e1922c16da50b5bef0644d9923a567b98c468`.

## Merge and landed identity

The authorized local non-fast-forward merge completed without conflicts:

```text
merge       29acc6c2aca462a6f6fe6b9dac386a6af3774a69
parent 1    ba8b7176c51c376dca34174292951563388f0336
parent 2    a2f6fd1adf67fd86c8d0c692db34f113a9691135
tree        088b8f625ea07f5b240c253ef20be461080b3b19
origin/main 0db8fdd8424d27aad2c547614e9ebb95621a2794
```

The actual tree equals the immediately pre-merge `git merge-tree --write-tree main a2f6fd1` prediction. `git diff --name-only a2f6fd1..29acc6c -- CMakeLists.txt cmake include schemas src tests` and the packet's narrower `git diff --stat ... -- src tests` are both empty. The landed product bytes therefore equal the owner-reviewed and Task-4-verified candidate bytes. The candidate worktree remains clean at the exact candidate. Both retention tags and `origin/main` remain unchanged.

## Fresh landed-tree verification

Fresh serial macOS verification ran on local `main@29acc6c` after the merge:

```text
cmake --preset ci-macos                                            PASS
cmake --build --preset ci-macos                                   PASS
biv_tests full product binary                                     PASS — 16,343/16,343 assertions; 418 passed + 3 configured skips of 421
biv_tests 'FX-O*'                                                  PASS — 803 assertions / 11 cases
biv_tests 'FX-N*'                                                  PASS — 135 assertions / 5 cases
biv_repo_engine_tests exact E4 request-trace slice                 PASS — 13 assertions / 1 case
```

The three full-product skips are the two configured WSL fixture rows and the configured-deferred R-4.29 ceiling row. This fresh run is a landed-tree E2 product verification, not a rerun or reclassification of the previously recorded whole-CTest and Linux residual rows.

The packet's registered residuals remain disclosed and are not cited as readiness evidence: R-4.35 was `3 failed, 996 passed, 3 skipped` in the canonical Linux harness-selftest; R-4.38 observed `420/0/0/1` against the stale pinned `412/0/0/1`, exactly the +8 cases awaiting the separately gated count transcription. Neither was converted to green.

## Boundary and next action

No push, fetch, pull, remote CI, PR creation or mutation, publication, deployment, install, seal, release, reset, revert, tag mutation, branch deletion, worktree removal, or cleanup act occurred. The local main is ahead of `origin/main`; that unpublished state is retained. The candidate branch and worktree are retained.

Requested next action: `intg.pair-planner` independently re-verifies the ordered parents, predicted/actual tree, product-root identity, record-hygiene commit, fresh landed tests, unchanged remote and tags, then records packet section 8 and returns the landed sha UP to master. Only after that may the separately approved count-gate plan receive its own token; the workflow-only count transcription, m-3 review, first push, and all release-side actions retain their separate gates.

ACTIONS_GIT_REF: merge=29acc6c2aca462a6f6fe6b9dac386a6af3774a69; authorized local non-ff merge on main with exact ordered parents ba8b7176c51c376dca34174292951563388f0336 and a2f6fd1adf67fd86c8d0c692db34f113a9691135; actual tree 088b8f625ea07f5b240c253ef20be461080b3b19 equals fresh merge-tree prediction; product-root diff empty; origin/main 0db8fdd8424d27aad2c547614e9ebb95621a2794 and both retention tags untouched; fresh landed build, full product binary, FX-O, FX-N, and E4 slice pass; no push or release-side act. Record hygiene is docs commit ba8b7176c51c376dca34174292951563388f0336 containing exactly the eight named relay paths.
RELAY_LINT: exact-file freshness and daemon admission required; engine show and body hash required after rendering; inherited root noise is separate and no whole-root-green claim is made.
FINAL_GIT_STATUS_SHORT: inherited-only before filing — main retains the pre-existing s4 lane set (two modified s4 projections, historical untracked s4 relays, and the s4 migration doc) plus the pre-existing root draft `relay-draft-intg-task4-stop.md`; no intg-owned path is dirty. Filing and path-scoped receipt commit will add only the rendered relay and the engine-updated intg INDEX.

CARRY LIST:
- this merge receipt -> TO `intg.pair-planner` under `intg-substep2a-merge-token`
- record hygiene -> `ba8b7176c51c376dca34174292951563388f0336`, exactly eight named implementer relay files
- local merge -> `29acc6c2aca462a6f6fe6b9dac386a6af3774a69`, ordered parents `ba8b717` then `a2f6fd1`, predicted/actual tree `088b8f62`, reviewed product roots byte-identical
- landed E2 -> configure/build PASS; full product `16,343/16,343`, `418+3/421`; FX-O `803/11`; FX-N `135/5`; E4 `13/1`
- retained reds -> R-4.35 `3 failed/996 passed/3 skipped`; R-4.38 `420/0/0/1` vs `412/0/0/1`; neither converted to green
- remote and release boundary -> origin/main `0db8fdd`; no push/PR/remote CI/publication/deployment/seal/release; release hold ABSOLUTE
