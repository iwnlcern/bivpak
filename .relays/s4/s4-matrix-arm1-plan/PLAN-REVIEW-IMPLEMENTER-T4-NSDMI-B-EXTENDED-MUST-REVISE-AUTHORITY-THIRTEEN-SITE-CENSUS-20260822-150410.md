## PLAN-REVIEW — MUST REVISE: the two-NSDMI technical diagnosis is corroborated, but necessity does not create authority, and the plan repeats the T2 census defect by treating eight warning sites as the full population where the exact T4 tree has thirteen initializers

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r0
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-B-EXTENDED-TWO-MEMBERS-CLASS-GUARD-20260822-145748.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-NSDMI-FIX-RULED-B-PLUS-CLASS-GUARD-PATTERN-TO-M1-20260822-144729.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the Orchestrator must explicitly dispose the proposed expansion from the ruled one-line `budget_override{}` change to a two-member `git_exec.hpp` change. This review cannot manufacture that authority. No bare `DISPATCH IMPL` may parent to this must-revise review; a successor Orchestrator ruling, corrected Planner PLAN, and approving successor Implementer PLAN-REVIEW are required. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_ARTIFACT: PLAN-PLANNER-T4-NSDMI-B-EXTENDED-TWO-MEMBERS-CLASS-GUARD-20260822-145748
PLAN_SHA256: 8a1db5b0e07ad1172b0de39e9b1e564cd5c8d34b6dcf9dd0c1370abec2181a5a
PLAN_GIT_BLOB: 9a05d18e31960e5153c0593efc9c4513b9f356cc
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE T4 NSDMI plan at SHA-256 8a1db5b; two-member cause diagnosis and canary are technically corroborated, but the second header edit lacks literal ruling authority, the exact initializer population is thirteen rather than eight, and the guard file must be named before token scope can be sealed

MUST REVISE. The plan found a real second NSDMI omission and its proposed guard is a real
discriminator. Those facts do not clear the plan as filed. There are two blocking defects: the
plan expands a literal one-line ruling while declaring that the expansion still needs the
Orchestrator's decision, and its semantic no-op proof counts the eight sites that happened to
appear in the first failed build rather than the thirteen aggregate initializers in the tree.
The test path is also left as "one test file", which is not precise enough for the successor
scope rows.

## MR-1 — necessity does not create the missing authority

The parent Orchestrator relay rules this exact production edit:

```text
src/core/repo/git_exec.hpp:24
  budget_override;
  -> budget_override{};
```

The plan proposes a second production edit at `:25`,
`empty_config_keys` to `empty_config_keys{}`. The technical reason is strong: the same GCC
warning class remains on `empty_config_keys` under the literal one-line B when a designated
initializer omits it. But the plan itself records `HUMAN_GATE_REQUIRED: yes — ONE decision`.
An Implementer PLAN-REVIEW cannot answer that Orchestrator decision by treating a necessary
scope expansion as self-authorizing.

The successor sequence is therefore explicit:

```text
Orchestrator successor ruling expressly authorizes or rejects empty_config_keys{}
  -> Planner rev1 binds exactly that disposition
  -> Implementer reviews rev1
  -> bare token only after an approve
```

No token may parent to this review.

## MR-2 — eight is the warning subset, not the initializer population

The plan says all eight `GitInvokeOptions` sites name `empty_config_keys`, and O-5 requires all
eight sites unchanged. That is true only of the eight sites printed in the first stopped build:
two in `classify.cpp` and six in `capture.cpp`. A broad exact-tree census at `29120d0` finds
**thirteen** aggregate initializers:

```text
src/core/repo/classify.cpp     2   name empty_config_keys; omit budget_override
src/core/repo/capture.cpp      6   name empty_config_keys; omit budget_override
src/core/repo/eligibility.cpp  3   omit BOTH budget_override and empty_config_keys
src/core/repo/restore.cpp      1   omits BOTH budget_override and empty_config_keys
tests/test_repo_engine.cpp     1   names budget_override; omits empty_config_keys
                               --
TOTAL                         13   12 production plus 1 test
```

This is the same instrument defect corrected at T2: a diagnostic subset was reported as the
population. Here the omitted five are especially material. Under the literal one-line B,
GCC's next compile can diagnose `empty_config_keys` at the three eligibility sites, the one
restore site, and the existing budget-expiry test initializer. Whether all five appear in one
parallel build log is scheduling, not semantics.

Rev1 must bind O-5 to all thirteen sites, require all twelve production initializers and the
existing test initializer to remain unchanged unless the Orchestrator expressly authorizes a
different row, and explain the no-op across the full population. This correction strengthens
the case for the second NSDMI; it does not supply the missing authority from MR-1.

## MR-3 — name the guard file and exact guard mechanism

The plan scopes "one test file" but does not name it. The live target and shown test shape bind
the intended path as `tests/test_repo_engine.cpp`; rev1 must say that literally so the later
token can carry two unambiguous `SCOPE_DIFF` and `SCOPE_ROW_EVIDENCE` rows:

```text
src/core/repo/git_exec.hpp
tests/test_repo_engine.cpp
```

The proposed minimal designated initializer is technically sound if both NSDMI edits are
authorized. Rev1 should keep the meaningful assertions, confirm `biv_repo_engine_tests`
compiles with `-Wall -Wextra -Werror`, and retain the temporary NSDMI-less-member mutation
RED then restored GREEN proof. The fixed digest must be re-established after the mutation.

## Independently corroborated items

I reproduced the plan's compiler claim independently in a disposable `gcc:13` linux/amd64
container under Docker `--init`, using GCC 13.4.0 and
`-std=c++23 -Wall -Wextra -Werror`:

```text
current struct + {.promisor = true}             RED  budget_override + empty_config_keys
budget_override{} only + {.promisor = true}     RED  empty_config_keys
both members NSDMI'd + {.promisor = true}       GREEN
budget_override{} only + {.budget_override=20}  RED  empty_config_keys
```

That probe corroborates the two-member cause diagnosis and the canary's ability to fail. It is
a standalone GCC discriminator, not canonical Ubuntu 24.04 product evidence and not a
substitute for the fixed-head Docker run after valid implementation authority.

The following plan elements otherwise close:

- option C remains correctly rejected; no caller edit is justified;
- both proposed NSDMIs are behavioral no-ops for `std::optional` and `std::span`;
- O-1 through O-4 have the right evidence classes: untouched GCC red, fixed-head Linux green
  under Docker `--init`, macOS interaction green, and mutation red then restored green;
- the guard is confined to `GitInvokeOptions`; the repo-wide convention and `Git::Opts` remain
  routed rather than silently widened;
- T1, T2, and T3 remain FINAL; T4 remains local, unpublished, not final, and not panelable.

No product authority follows from this review. The T4 worktree remains clean at `29120d0`.
Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-file lint/hash/blob of the filed PLAN; read-only full `GitInvokeOptions{` census at reconstructed T4 `29120d0`; direct reads of all thirteen sites and the target compile options; one disposable `gcc:13 --platform linux/amd64` Docker-init standalone four-arm syntax probe under GCC 13.4.0. No T4 product/test/workflow edit, branch/ref move, remote CI, push, PR mutation, merge, schema, publication, deployment, or release. The ignored scratch probe is plan-review evidence only. Docs lane: this relay plus one live-EOF INDEX row ride one explicit-path commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T4 clean at `29120d0`; shared main retains sibling-authored untracked relays and migration notes unchanged and unclaimed; only this review and its one INDEX append are this seat's docs-lane delta.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-B-EXTENDED-MUST-REVISE-AUTHORITY-THIRTEEN-SITE-CENSUS-20260822-150410.md` -> `s4-matrix.planner`, `s4.orchestrator-planner`
- MUST REVISE plan SHA-256 `8a1db5b0e07ad1172b0de39e9b1e564cd5c8d34b6dcf9dd0c1370abec2181a5a`: the proposed `empty_config_keys{}` production edit is technically justified but not literally authorized by `144729`; necessity does not create authority, and the plan itself records the Orchestrator decision as a human gate
- FULL CENSUS is thirteen, not eight: classify 2 plus capture 6 name `empty_config_keys`; eligibility 3 plus restore 1 omit both members; the existing repo-engine budget test names `budget_override` and omits `empty_config_keys`; rev1 binds semantic no-op and unchanged-site proof to all 12 production plus 1 test initializers
- NAME THE TEST PATH in rev1 as `tests/test_repo_engine.cpp`; later token rows are exactly `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp` if the Orchestrator authorizes the two-member shape
- INDEPENDENT GCC 13.4.0 discriminator corroborates the technical claim: current red on both, budget-only still red on span, both NSDMI'd green, and budget-only plus the existing test shape red on span; standalone probe only, fixed-head Ubuntu evidence still owed after valid token
- no token from this must-revise review; Orchestrator successor disposition -> Planner rev1 -> Implementer review -> token only on approve. No product, remote CI, push, PR mutation, merge, schema, publication, deployment, or release act; T4 remains clean/local/unpublished/not-final/not-panelable; release hold ABSOLUTE
