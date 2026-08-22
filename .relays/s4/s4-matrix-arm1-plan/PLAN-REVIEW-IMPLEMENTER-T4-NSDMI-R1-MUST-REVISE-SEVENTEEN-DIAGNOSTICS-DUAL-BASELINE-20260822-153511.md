## PLAN-REVIEW — MUST REVISE: authority, two-member scope, thirteen-site population, guard, and fence now close; O-1 still partitions four double-omission sites incorrectly and asks one compiler arm to be both RED and warning-demoted

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r1
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-R1-TWO-MEMBER-THIRTEEN-SITE-CENSUS-20260822-153332.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-NSDMI-SUCCESSOR-RULED-TWO-MEMBER-MY-CENSUS-WAS-DEFECTIVE-TOO-20260822-152652.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate. The two-member production decision is now expressly authorized and remains sound. Before a token, the Orchestrator must correct the exact O-1 expected warning multiset inherited by rev1, then the Planner must file rev2 with separate canonical-RED and warning-enumeration arms, followed by an approving Implementer review. No bare token may parent to this must-revise review. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_ARTIFACT: PLAN-PLANNER-T4-NSDMI-R1-TWO-MEMBER-THIRTEEN-SITE-CENSUS-20260822-153332
PLAN_SHA256: f56fa24f90b451953ed3f72165305d31d6e6672d38853148dce355dcf81ff61a
PLAN_GIT_BLOB: 19aa06e4b82493e76defc5051e51386de7e458ea
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.implementer
TO: s4-matrix.planner, s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE rev1 at SHA-256 f56fa24f: O-1 must expect 12 budget_override plus 5 empty_config_keys member-site diagnostics, seventeen across thirteen initializers, because eligibility 3 and restore 1 omit BOTH; and the canonical MUST-BE-RED arm must remain separate from the warning-demoted enumerate-all arm, whose expected exit is zero absent other errors

MUST REVISE. Rev1 closes every prior scope and authority finding. The remaining defect is
isolated to O-1, but O-1 is the proof designed specifically to prevent another bounded-census
error, so its own population and verdict cannot be approximate.

## MR-1 — the exact multiset is seventeen member-site pairs, not thirteen

Rev1 correctly counts thirteen aggregate initializer **sites**, then requires this warning set:

```text
8 budget_override warnings + 5 empty_config_keys warnings = 13
```

That treats the site categories as mutually exclusive. They are not. The three eligibility
sites and one restore site omit both members, and GCC emits a member-specific warning for each
omitted member:

```text
file                         sites  budget omitted  empty keys omitted  warning pairs
src/core/repo/classify.cpp      2        2                 0                 2
src/core/repo/capture.cpp       6        6                 0                 6
src/core/repo/eligibility.cpp   3        3                 3                 6
src/core/repo/restore.cpp       1        1                 1                 2
tests/test_repo_engine.cpp      1        0                 1                 1
                               --       --                --                --
initializer sites              13       12                 5                17
```

The first stopped build printed eight `budget_override` warnings because it reached the two
classify and six capture sites. That output is not evidence that the four eligibility/restore
initializers omit only `empty_config_keys`; direct source inspection shows they omit both.

I independently compiled representative shapes against the actual
`29120d0:src/core/repo/git_exec.hpp` in a disposable `gcc:13` linux/amd64 Docker-init container,
GCC 13.4.0, with the warning demoted only to let compilation finish:

```text
{.promisor = true}                         -> budget_override warning AND empty_config_keys warning
{.promisor = true, .empty_config_keys={}}  -> budget_override warning
{.budget_override = 20ms}                  -> empty_config_keys warning
```

The actual-header probe confirms the overlap. The successor correction and rev2 must bind O-1
to the exact file-line-member multiset: twelve `budget_override` omissions plus five
`empty_config_keys` omissions, seventeen warning pairs across thirteen sites. A retained run
that differs must STOP and route; the total alone is not enough.

## MR-2 — one arm cannot be both MUST-BE-RED and warning-demoted

Rev1 calls O-1 a `MUST-BE-RED BASELINE`, then offers
`-Wno-error=missing-field-initializers` so the build compiles to completion. If those omissions
are the only defect, that demoted arm exits zero. It is the right enumeration instrument but
cannot simultaneously prove the canonical warning-as-error failure.

Rev2 must separate the two claims:

```text
O-1a  CANONICAL RED
      untouched 29120d0 with the real -Wall -Wextra -Werror policy
      expected nonzero build exit and exact missing-field diagnostic class

O-1b  ENUMERATE ALL
      same bytes and compiler, but append -Wno-error=missing-field-initializers after -Werror
      and compile every relevant TU to completion
      expected exit zero if no other error; exact multiset = 12 budget + 5 empty keys
      bind every warning by file, line, and member; any delta STOPS
```

An alternative keep-going `-Werror` arm is acceptable only if it proves every relevant TU was
actually compiled and retains the nonzero verdict. Merely setting `-fmax-errors=0` inside a TU
does not by itself prove the build driver scheduled every other TU after a failure.

For O-4, use the C++-specific verdict directly: the temporary member arm passes only when the
build is nonzero and the diagnostic names that temporary member; removal passes only when the
focused build and test are green and the fixed header digest is restored. The imported-module
ERROR-versus-FAILURE wording is unnecessary in this C++ target and should not substitute for
those exact predicates.

## Items that close in rev1

- **Authority:** `152652` expressly authorizes both NSDMIs. MR-1 from review r0 is discharged.
- **Production shape:** `budget_override{}` plus `empty_config_keys{}` is the minimal cause fix;
  both are behavioral no-ops and no caller initializer changes.
- **Population:** thirteen initializer sites, twelve production plus one test, is correct. The
  defect is only the overlapping member-warning multiset in O-1.
- **Guard path and target:** `tests/test_repo_engine.cpp` is literal, and
  `biv_repo_engine_tests` carries `-Wall -Wextra -Werror` at `CMakeLists.txt:123-127`.
- **Guard design:** the minimal `.promisor = true` initializer plus default assertions is a
  meaningful class canary; temporary-member RED then restored GREEN remains required.
- **Fence:** exactly `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp`; no caller,
  `Git::Opts`, workflow, harness, schema, or other T4 byte.
- **O-2/O-3/O-5:** Linux Docker-init plus nofile proof, macOS interaction proof, and exact
  two-file/no-op proof remain properly scoped.
- **Holds:** T1/T2/T3 stay FINAL; T4 stays local, unpublished, not final, and not panelable.

No product authority follows from this review. No bare token may parent here.
Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only exact-file lint/hash/blob of rev1; tree-wide `GitInvokeOptions{` census and direct reads of all thirteen bodies at reconstructed T4 `29120d0`; direct CMake target-option read; one disposable Docker-init `gcc:13 --platform linux/amd64` GCC 13.4.0 syntax-only probe including the actual T4 header from a read-only mount, with warning demotion solely to enumerate representative overlapping diagnostics. No T4 product/test/workflow edit, branch/ref move, remote CI, push, PR mutation, merge, schema, publication, deployment, or release. Docs lane: this relay plus one live-EOF INDEX row ride one explicit-path commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T4 clean at `29120d0`; shared main retains sibling-authored untracked relays and migration notes unchanged and unclaimed; only this review and its one INDEX append are this seat's docs-lane delta.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-R1-MUST-REVISE-SEVENTEEN-DIAGNOSTICS-DUAL-BASELINE-20260822-153511.md` -> `s4-matrix.planner`, `s4.orchestrator-planner`
- REV1 ITEMS CLOSED: successor authority for both NSDMIs, minimal two-member/no-caller shape, thirteen initializer sites, literal tests/test_repo_engine.cpp guard path, -Werror target confirmation, guard design, exact two-file fence, O-2/O-3/O-5, Git::Opts exclusion, and all integration/release holds
- MR-1 WARNING MULTISET: eligibility 3 plus restore 1 omit BOTH members, so thirteen initializer sites yield 12 budget_override omissions plus 5 empty_config_keys omissions equals 17 member-site pairs; actual-header GCC 13.4.0 probe emits both warnings for the eligibility shape
- MR-2 DUAL BASELINE: canonical unchanged -Werror arm must be nonzero RED; separate same-byte warning-demoted arm compiles all relevant TUs to completion, expects zero absent other errors, and enumerates exact 17 file-line-member pairs. One arm cannot prove both claims
- O-4 C++ VERDICT: temporary member arm is valid only on nonzero build with that member named; removal arm requires focused build and test green plus fixed header digest restored; do not substitute imported-module ERROR-versus-FAILURE wording
- NO token from this must-revise review; exact sequence is Orchestrator O-1 correction -> Planner rev2 -> approving Implementer review -> bare token. T4 remains clean/local/unpublished/not-final/not-panelable at 29120d0; no product, remote CI, push, PR mutation, merge, schema, publication, deployment, or release act; release hold ABSOLUTE
