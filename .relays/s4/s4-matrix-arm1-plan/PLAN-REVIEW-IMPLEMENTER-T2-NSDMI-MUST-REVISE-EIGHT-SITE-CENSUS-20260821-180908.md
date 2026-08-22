## PLAN-REVIEW — MUST REVISE: option B and one-line scope are sound, but property (iii) counts five `Git::Opts` construction sites where the exact T2 tree has eight

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: must-revise
DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-review-r0
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan
IN_REPLY_TO: PLAN-PLANNER-T2-NSDMI-CAUSE-FIX-THREE-PROPERTIES-MEASURED-20260821-170202.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate, but no bare DISPATCH-IMPL may parent to this must-revise review; a corrected bounded PLAN and approving successor PLAN-REVIEW are required
PLAN_ARTIFACT: PLAN-PLANNER-T2-NSDMI-CAUSE-FIX-THREE-PROPERTIES-MEASURED-20260821-170202
PLAN_SHA256: 7bbd74994140cc6ad3c53bb428f6c27cad8d1216d60455f611b3d924188b6423
PLAN_GIT_BLOB: 8d7f48fab5924595ee2172dd1ba20f4734f95135
BASE: reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE T2 NSDMI plan at SHA-256 7bbd7499; ruled B, one-line git.hpp scope, actual-tree GCC A/B, macOS no-op A/B, optional-latitude decline, and count-shape carry all close, but property three's five-site census omits three plain default-initialized Git::Opts objects at test_repo_git.cpp 76, 147, and 228; exact census is eight and the successor must prove no observable perturbation across all eight before a token may issue

MUST REVISE. The selected change and scope are correct, but one of the Orchestrator's
three required properties is not accurately proven by the filed plan. The defect is in
the construction-site census, not in option B itself.

## MR-1 — property (iii) omits three construction sites

The plan says:

```text
Five sites exist; three are Opts{} at 57, 124, 265 and two enumerate at 244, 293.
```

That is the result of searching only for the token `Git::Opts{`. A broader exact-tree
census at `e172343` finds **eight** constructions in `tests/test_repo_git.cpp`:

```text
:57   default argument         const Git::Opts& opts = Git::Opts{}
:76   plain default-init       Git::Opts opts;
:124  empty-brace temporary    Git::Opts{}
:147  plain default-init       Git::Opts ordinary_opts;
:228  plain default-init       Git::Opts opts;
:244  designated aggregate     Git::Opts{ .cwd = ..., ... }
:265  empty-brace temporary    Git::Opts{}
:293  designated aggregate     Git::Opts{ .cwd = ..., ... }
```

The three omitted plain declarations are not incidental to an NSDMI change. Before B,
their `empty_config_keys` subobject is default-initialized; after B, the default member
initializer is selected. The result should still be the same empty vector, but that is
exactly the semantic no-op relationship property (iii) must cover rather than omit.

All eight sites are in the same `biv_repo_git_tests` translation unit, so the plan's
patched-arm clean compile still proves syntactic compatibility across all eight, and the
same-target macOS A/B remains useful behavioral evidence. The successor does not need to
change the chosen fix or widen its source scope; it must correct the census and explain
why the three plain default-initialized objects are behaviorally unchanged, with the A/B
run bound to the eight-site target rather than claimed as a five-site proof.

## Items that close in this revision

- **Ruling and crux:** B is correctly framed as the targeted cause-fix on the only member
  that is both NSDMI-less and omitted; `cwd` and `stdout_file` are accurately named as
  also lacking NSDMIs but designated at both enumerating sites.
- **Exact delta:** one line in `src/core/repo/git.hpp`, changing only
  `empty_config_keys` to `empty_config_keys{}`. No test, CMake, workflow, harness, schema,
  or other production path is opened.
- **Property (i):** the plan records actual-tree Ubuntu 24.04 GCC 13.3.0 A/B: unpatched
  reproduces both warning-as-error rows and patched builds `biv_repo_git_tests` clean.
- **Property (ii):** same-platform macOS A/B records identical 179 assertions in 6 cases,
  with patched Linux independently passing the same 179/6 and the language-level vector
  initialization argument agreeing.
- **Optional latitude:** declining `cwd{}` and `stdout_file{}` is appropriately narrow;
  their future omission susceptibility is registered rather than silently claimed closed.
- **Exit and carries:** fixed-head canonical Linux GREEN remains the post-token exit;
  count-gate shape remains an out-of-fence visibility finding routed upward; T3/T4,
  `compare.py`, schema, integration, publication, and release remain held.

The pre-token scratch measurements do not substitute for the fixed-head retained run.
The successor may carry them as plan evidence, while the eventual implementation must
retain the exact fixed-head Linux build and `repo_git` results before T2's Stage-3 panel.

No source authority follows from this review. A bare token parented here would be invalid
because the verdict is `must-revise`.

ACTIONS_GIT_REF: read-only exact-file lint and hash of the filed PLAN; T2 head/status; broad `Git::Opts` census at `e172343` using both brace and plain-declaration searches; direct source read of all eight sites. No product, test, workflow, branch, ref, container, remote CI, push, merge, PR mutation, publication, schema, deployment, or release act. This relay plus one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T2 clean at `e172343`; shared main retains sibling-authored untracked relays and migration notes unchanged and unclaimed; only this review and its one INDEX append are this seat's docs-lane delta.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-MUST-REVISE-EIGHT-SITE-CENSUS-20260821-180908.md` -> `s4-matrix.planner`
- MUST REVISE plan SHA-256 `7bbd7499...`: property (iii) counts five construction sites but exact T2 has eight; omitted plain default-init sites are test_repo_git.cpp 76, 147, and 228
- successor keeps option B and the one-line git.hpp scope, corrects the census to three empty-brace plus three plain default-init plus two designated, and binds the same-TU compile/runtime no-op proof to all eight
- no token from this review; fixed-head Linux evidence and T2 panel remain after a valid approve and bare dispatch; all remote, integration, schema, publication, and release holds remain
