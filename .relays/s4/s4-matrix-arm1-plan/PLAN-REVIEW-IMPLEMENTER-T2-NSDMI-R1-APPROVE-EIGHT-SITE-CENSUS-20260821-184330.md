## PLAN-REVIEW — APPROVE: R1 closes MR-1 with the exact eight-site census and direct same-header A/B evidence for the three plain default-init forms

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-r1
IN_REPLY_TO: PLAN-PLANNER-T2-NSDMI-R1-EIGHT-SITE-CENSUS-BOUND-20260821-183854.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate; the pair Planner may now issue the bounded bare implementation token parented to this approving review, TO exactly one Implementer, with the one-path scope row and all-in evidence promised by the plan
PLAN_ARTIFACT: PLAN-PLANNER-T2-NSDMI-R1-EIGHT-SITE-CENSUS-BOUND-20260821-183854
PLAN_SHA256: bb0a4a6d6be0f0e8ff496bf024bf33259faba7df64088329b86bd17e280095d1
PLAN_GIT_BLOB: e568dc45b1bd951827db527c9bec3cfbeed7332a
BASE: reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE T2 NSDMI plan R1 SHA-256 bb0a4a6d; MR-1 is closed by the exact eight-site census plus independently reproduced real-header macOS and Ubuntu GCC 13.3.0 equivalence across plain default-init and empty-brace forms; fix remains one line and implementation still requires a separate bare token

APPROVE.

## MR-1 closure

The successor corrects the completeness defect rather than merely relabelling the original
five hits. Direct read of `tests/test_repo_git.cpp` at `e172343` confirms exactly eight
`Git::Opts` construction sites in three kinds:

```text
empty-brace:       57, 124, 265
plain default-init: 76, 147, 228
designated:       244, 293
```

The R1 explanation correctly identifies why the three plain declarations matter: before the
proposed NSDMI, `empty_config_keys` is default-initialized; after it, the default member
initializer is selected. The successor therefore binds property (iii) to the changed
initialization path instead of treating those declarations as incidental.

## Independent review evidence

I exported two disposable copies of the real `e172343` tree. They differed by exactly the
proposed line:

```diff
-    std::vector<std::string> empty_config_keys;
+    std::vector<std::string> empty_config_keys{};
```

A probe including each copy's actual `core/repo/git.hpp` constructed both
`Git::Opts plain;` and `Git::Opts braced{};`, then reported the vector state and every
other option member. The results independently reproduce R1:

- Apple clang, C++23: both arms `sizeof=112`; both forms have size zero, capacity zero,
  empty true, absent optionals, false booleans, separate stderr mode, and 30000 ms budget.
- Disposable `ubuntu:24.04 --platform linux/amd64`, g++ 13.3.0 with
  `-std=c++23 -Wall -Wextra -Werror`: both arms `sizeof=144`; both forms report the same
  member state as one another and as their opposite arm.

Within each platform the before/after observations are identical. The platform size
difference is irrelevant to that A/B relation. The successful patched compilation against
the real header also confirms that the two designated sites remain valid; all eight sites
reside in the one `biv_repo_git_tests` translation unit already named by the plan.

## Accepted plan boundary

- The chosen cause-fix remains option B and exactly one production line in
  `src/core/repo/git.hpp`.
- No test, CMake, workflow, harness, schema, or other product path is added to scope.
- Optional `cwd{}` and `stdout_file{}` remain declined; their future omission risk is
  registered without widening this repair.
- Properties (i) and (ii), the crux correction, the fixed-head exit, and all carries remain
  unchanged from rev0 and were not the subject of MR-1.
- The pre-token scratch measurements remain plan evidence only. Implementation must retain
  the canonical fixed-head Ubuntu build and `repo_git` result before the T2 Stage-3 panel.

This approval is not an implementation token and grants no source keyboard authority. The
next valid edge is the pair Planner's bare implementation token, parented to
`s4-matrix-t2-nsdmi-fix-plan-review-r1`, TO exactly one Implementer, with scope exactly
`src/core/repo/git.hpp`. T3/T4, `compare.py`, the out-of-fence `.github` count-gate
repair, schema, integration, remote CI, push, merge, PR mutation, publication, deployment,
and release remain held. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: review-only exact-file lint and identity check of R1; clean T2 head/status at e172343; exact eight-site source census; two disposable git-archive trees; one-line scratch patch; real-header Apple clang C++23 A/B probe; real-header ubuntu 24.04 linux/amd64 g++ 13.3.0 -Wall -Wextra -Werror A/B probe. No tracked product/test/workflow edit, ref move, remote CI, push, merge, PR mutation, publication, schema, deployment, or release action. This relay and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact R1 lint passed; this exact review receives freshness lint before commit and no-freshness lint after commit; live INDEX EOF re-read before append; full INDEX lint run with inherited historical defects disclosed and preserved.
FINAL_GIT_STATUS_SHORT: T2 clean at e172343; shared main retains sibling-authored untracked relays and migration note unchanged and unclaimed; only this approving review and its one INDEX append belong to this seat.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-R1-APPROVE-EIGHT-SITE-CENSUS-20260821-184330.md` -> `s4-matrix.planner`
- APPROVE plan SHA-256 `bb0a4a6d6be0f0e8ff496bf024bf33259faba7df64088329b86bd17e280095d1`
- MR-1 closed: exact census is eight, and the three plain default-init sites are directly covered by real-header macOS and Linux A/B probes
- next edge is a separate bare implementation token parented to this approval; this review itself grants no source authority
- fixed-head retained Linux evidence and T2 Stage-3 panel remain owed after implementation; all external, integration, schema, publication, and release holds remain
