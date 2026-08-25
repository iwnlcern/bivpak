## PLAN-REVIEW — APPROVE the F-URL-1 engine-only corrective under M rev8 and A6 rev14

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-furl1-engine-only-plan-review
PARENT_DISPATCH_ID: s4-matrix-furl1-engine-only-impl-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-ENGINE-ONLY-M-REV8-A6-REV14-SIX-PATHS-FOURTEEN-UNITS-20260825-152627.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-ENGINE-ONLY-CORRECTIVE-RESUMED-REV8-REV14-LOCKS-VERIFIED-20260825-151627.md; ../../../../pdc/master/relays/s4-wave-a-furl1-e2-timing-m3-ruling/PLAN-orchestrator-planner-20260825-151141.md; ../../../../pdc/master/relays/s4-wave-a-furl1-e2-timing-m3-ruling/PLAN-REVIEW-orchestrator-reviewer-20260825-150851.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
LOCKED_DESIGN_SHA256: c41d015fd867464aefc479e25f0fc7521b5e259cb88d79cb1d36fe05db19150c
POST_STAMP_SHA256: 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771
COORDINATED_TWIN_POST_STAMP_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m1-addendum-M-2966b839-lock-20260825 (57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no new operator gate. This approval closes PLAN-REVIEW only and carries no keyboard authority. Implementation still requires the Planner's later fresh, uniquely keyed, correctly parented bare implementation token addressed to exactly one Implementer. No merge claim may be made without a MERGE-GATE relay; the T4 FINAL re-weigh returns to the operator, and the release hold is absolute.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 6ba01ef92ef5052b317f6210fa202d5577e1e6c1 on FINAL T3 70601fc201b3c41d2542d82399787b5febcbf03c
REVIEWED_PLAN: commit 3bf085b00463784ba4dbe042ee7e79e108e64e35, blob 93a61dd0ee5fe9f8a304d6d6d5cd3b0f16a6afd6, SHA-256 9329355d204e8528e52bc98e06e1d68e69717913707e6f8f777f3ba74bd84bb3
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: APPROVE exact plan bytes — revised locks re-hash, six-member package taxonomy, six-path engine-only fence, fourteen top-level real-Git units including both subarms of unit n, zero m-3 surface bytes, absent-hook fail-safe, one commit, local macOS plus disposable Linux CI, owner byte reviews, and every authority hold are coherent and implementable; fake_network_git remains seam proof only

## Verdict

**APPROVE.** The exact plan at commit `3bf085b00463784ba4dbe042ee7e79e108e64e35`, blob
`93a61dd0ee5fe9f8a304d6d6d5cd3b0f16a6afd6`, SHA-256
`9329355d204e8528e52bc98e06e1d68e69717913707e6f8f777f3ba74bd84bb3` is internally coherent,
technically feasible, and bounded to the authority actually granted by the revised package. This
approval does not authorize implementation.

## Independent review evidence

- M rev8 re-hashes at this seat to `57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082`
  over 40,401 bytes, with `m1-addendum-M-2966b839-lock-20260825` occurring once.
- A6 rev14 re-hashes to `7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771`
  over 60,314 bytes, with `m3-addendum-6-c41d015f-lock-20260825` occurring once. SR-URL remains
  `a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798` over 10,249 bytes.
- The master registry and approved package preserve six distinct members. In particular, ruling
  R4's zero-m-3-surface absence bar is separate from `V-A6-1..6` and is not A6-R4. The plan does
  not collapse or substitute those obligations.
- The reduced E2 count is fourteen retained top-level engine units: `(a)` non-interactive,
  `(b)`, `(c)`, and `(e)` through `(o)`. Unit `(n)` retains both mandatory subarms, `n.i` and
  `n.ii`; the top-level count does not discard either. Leg `(d)` and only `(a)`'s interactive arm
  remain deferred to the later product-scope integration act. `fake_network_git` is correctly
  treated as seam proof, never as real-Git discharge.
- A real Git 2.50.1 probe in a disposable repository established the exact wrapper form and
  context dependence: repo-local
  `url.https://effective.invalid/.insteadOf=https://requested.invalid/` made
  `git -C <repo> ls-remote --get-url -- https://requested.invalid/proj.git` return
  `https://effective.invalid/proj.git`; the same command outside that repository returned the
  requested URL, and an input with no rewrite remained unchanged.
- The six admitted preimages independently match the plan: `git_exec.hpp` 2,500 bytes,
  `git_exec.cpp` 10,844, `types.hpp` 6,253, `eligibility.cpp` 8,085, `restore.cpp` 19,919, and
  `test_repo_engine.cpp` 54,027. The named nine retired CLI/report/schema test paths are OUT and
  form the independently reviewed absence bar.
- The isolated candidate remains at `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` with exactly the
  six authorized paths modified, no untracked candidate file, and clean `git diff --check`. Its
  frozen 37-assertion fake-Git slice is only a seed; it is not accepted as completion of O-1.
- Exact-file lint passes under the active v2.9.2 pair linter. The prior v2.9.1 path has moved and
  its not-found result was an instrument-path failure, not a relay defect.

## Binding conditions preserved

The implementation token must retain all of O-1 through O-6: real Git at the engine seam for all
fourteen top-level units and every required subarm; each named mutant demonstrated RED at its own
leg and then restored GREEN; comparator closure only over M-R2's enumerated set; central network
classification before spawn; same-context effective endpoint resolution; run-scoped hook and
memo; absent-hook fail-safe refusal; typed-carrier zero-or-many closure by population; exactly the
six named paths in one implementation commit; and a commit-diff proof of zero CLI/help/prompt,
envelope/schema/exit-map, wiring, manifest, pack/open, harness, workflow, or other m-3-surface byte.

Validation remains local: macOS plus disposable Ubuntu 24.04 `linux/amd64` Docker with `--init`
and the nofile soft limit raised to hard, following the canonical workflow and reporting any
difference. Do not trigger remote CI. After local green, m-1 reviews the engine bytes against M
rev8 and m-3 independently reviews the absence bar against A6 rev14; each retains pre-merge veto.
No push, PR mutation, merge, publication, deployment, or release is authorized here.

## Next act

The next actor is `s4-matrix.planner`. It may issue one fresh bare implementation token parented
exactly to `s4-matrix-furl1-engine-only-plan-review`, addressed to exactly one
`s4-matrix.implementer`, and fenced to the six paths and the full revised package. Until those
exact daemon-admitted bytes arrive and receipt checks pass, this Implementer performs no further
candidate edit or test execution.

ACTIONS_GIT_REF: review-only docs-lane act through the active relay engine: this approving review and daemon-owned INDEX/SEATS projections. Read-only review covered exact plan identity, lock bytes, package taxonomy, real-Git command feasibility, six base preimages, candidate status, active linter identity, and authority boundaries. No product/test/design/workflow edit, candidate commit, CI, push, PR mutation, merge, publication, deployment, or release act.
RELAY_LINT: exact-file v2.9.2 lint passes on the reviewed plan with --no-freshness; the live engine has reconciled the two newer hand-authored plan relays as hand-origin records so their provenance remains explicit.
FINAL_GIT_STATUS_SHORT: before engine submission, main carries daemon-generated modifications to .relays/s4/INDEX.md and .relays/s4/SEATS.md plus preserved sibling-authored untracked history; no product, test, build, or workflow path is modified in main. The isolated candidate remains at 6ba01ef with exactly six authorized modified paths, no untracked file, and clean diff-check. The daemon assigns this review's rendered path and final projections only after immutable draft admission; the post-submit literal status is therefore captured in the delivery receipt, not predicted here.

CARRY LIST:
- the daemon receipt path for this approving review -> TO `s4-matrix.planner`
- VERDICT APPROVE exact plan commit `3bf085b00463784ba4dbe042ee7e79e108e64e35`, blob `93a61dd0ee5fe9f8a304d6d6d5cd3b0f16a6afd6`, SHA-256 `9329355d204e8528e52bc98e06e1d68e69717913707e6f8f777f3ba74bd84bb3`
- NEXT ACTOR Planner: one fresh unique bare token parented to `s4-matrix-furl1-engine-only-plan-review`, exactly one Implementer, six paths, one implementation commit
- authority: no keyboard act under this approval; local CI only after implementation; m-1 and m-3 retain veto; MERGE-GATE and operator T4 FINAL remain later; release hold absolute
