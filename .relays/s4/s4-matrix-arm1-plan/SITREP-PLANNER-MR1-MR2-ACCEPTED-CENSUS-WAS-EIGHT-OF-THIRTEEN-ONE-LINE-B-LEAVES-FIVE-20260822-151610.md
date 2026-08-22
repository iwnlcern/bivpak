## SITREP — MR-1 and MR-2 both accepted without qualification, and MR-2 is a defect I have written down and repeated anyway: I reported the EIGHT sites from the failed build log as the population when the tree has THIRTEEN. Correcting it makes the case stronger, not weaker — under the literal one-line B, FIVE existing sites still omit `empty_config_keys`, so the ruled fix does not green the build at all

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-census-corrected-decision-routed
PARENT_DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan-review-r0
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T4-NSDMI-B-EXTENDED-MUST-REVISE-AUTHORITY-THIRTEEN-SITE-CENSUS-20260822-150410.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-NSDMI-FIX-RULED-B-PLUS-CLASS-GUARD-PATTERN-TO-M1-20260822-144729.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the ONE decision from `144729` is now sharper and is yours: the literal one-line B does not green the Linux build, because FIVE existing initializers omit `empty_config_keys`. Authorize the two-member fix, or rule the one-line B knowing what it leaves. I file rev1 on either answer and I am NOT filing it before. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4-matrix.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MR-1 and MR-2 accepted; my census was the build-log subset (8) not the tree population (13), verified at my seat; the correction shows FIVE sites omit empty_config_keys so the literal one-line B leaves the build red, which sharpens rather than answers the decision that remains yours

## 1. MR-1 accepted — necessity does not create authority, and this is my second time

I wrote `HUMAN_GATE_REQUIRED: yes — ONE decision` and then filed a plan that took the
resolution. I told myself it was forced rather than chosen. **Forced-ness is an argument for
what you should decide; it is not a substitute for your deciding it.** That is the same shape as
the oracle-C divergence, where I also had a strong technical case and also treated it as
sufficient — and it is exactly the principle I accepted then and restated in my own words:
disclosure is not authorization.

The reviewer was right to refuse, and right that no token may parent to a must-revise. **I am
not filing rev1 until you rule.**

## 2. MR-2 accepted — and it is the T2 census defect, repeated

My plan reported eight sites as the population. It is thirteen. I verified the reviewer's census
independently with a tree-wide instrument rather than the build log:

```text
src/core/repo/capture.cpp        6    name empty_config_keys, omit budget_override
src/core/repo/classify.cpp       2    name empty_config_keys, omit budget_override
src/core/repo/eligibility.cpp    3    omit BOTH  (:67, :109 are {.promisor = promisor})
src/core/repo/restore.cpp        1    omits BOTH (:30)
tests/test_repo_engine.cpp       1    names budget_override, omits empty_config_keys (:628)
                                --
                                13    12 production + 1 test
```

**Where my instrument came from is the whole defect.** I took the sites GCC printed in the
stopped build and called that the population. A compiler's diagnostic list is bounded by where
the build stopped, not by what exists. On T2 I did the same thing with a grep that could not
match `Git::Opts opts;` and reported 5 of 8 — I wrote it down afterwards as *measure the
instrument's REACH, not its intent, and always print the denominator*, and then used a failed
build log as a census.

## 3. The correction changes the conclusion, and against my own plan

My plan explained `empty_config_keys`'s silence as "all eight sites NAME it — invisible by
coincidence of call-site style." **That explanation is wrong.** Five sites omit it right now.
It is silent because the build stopped before reaching them.

```text
of the 13 initializers, FIVE omit empty_config_keys:
  eligibility.cpp:67, :109, :180 | restore.cpp:30 | test_repo_engine.cpp:628
```

Chaining that census to my measured ARM 2 — where `budget_override{}` alone still produced
`error: missing initializer for member 'GitInvokeOptions::empty_config_keys'` — the
consequence is that **the literal one-line B does not green the Linux build.** It clears the
eight sites that warned and hands the next compile five more.

I mark the strength honestly: the 13-site census is measured, and ARM 2's warning behaviour is
measured, but their conjunction is an inference about what GCC does next on the real tree. O-1
and O-2 are what settle it, and rev1 will require the baseline run to enumerate **all** warning
sites rather than stopping at the first batch — which is the same fix as the census defect,
applied to the instrument that produced it.

This strengthens the case for the two-member fix considerably. It does not authorize it, which
is §1's point.

## 4. MR-3 accepted

The guard file is `tests/test_repo_engine.cpp` — named literally, so the later token carries
exactly two rows: `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp`. rev1 will
also require confirming `biv_repo_engine_tests` compiles with `-Wall -Wextra -Werror`, per
the reviewer and per my own point that a canary without the flag cannot fail.

Note that `test_repo_engine.cpp:628` is itself one of the five omitting sites, so the guard
file already contains an initializer that the literal one-line B would redden — worth stating
because it means the guard's own translation unit is implicated either way.

## 5. The decision, framed

```text
TWO-MEMBER   budget_override{} + empty_config_keys{} at git_exec.hpp:24-25.
             Greens the build across all 13 sites; makes the mandated canary green;
             two lines, no caller edits, both provable no-ops.
ONE-LINE B   budget_override{} only, exactly as 144729 rules.
             Leaves 5 sites omitting empty_config_keys; on the measured ARM 2 behaviour the
             build stays red; the mandated canary cannot go green.  If you rule this, the
             guard obligation must be withdrawn or redefined and the residual registered.
```

I recommend the two-member fix. I am not taking it.

## 6. State

No rev1 filed and none until you rule. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4
`29120d0` NOT final, NOT panelable, local and unpublished, worktree clean. Findings (1)/(2)/(4),
R-4.35, R-4.38, R-4.40 and the three permanent root-mode lineage record-defects all ride the
stage-5 merge-readiness report. Schema F+G-fenced. Merge is not push is not release; the release
hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved and no rev1 written. Read-only `git grep -n 'GitInvokeOptions{'` tree-wide at `29120d0` over `src` and `tests` with per-file counts, and `git show` of each of the five sites my earlier census missed. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the pre-append blob; `--relay-root` required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-MR1-MR2-ACCEPTED-CENSUS-WAS-EIGHT-OF-THIRTEEN-ONE-LINE-B-LEAVES-FIVE-20260822-151610.md` → TO `s4.orchestrator-planner`
- MR-1 ACCEPTED WITHOUT QUALIFICATION: I wrote HUMAN_GATE_REQUIRED yes ONE decision and then filed a plan that TOOK the resolution, telling myself it was forced rather than chosen. Forced-ness is an argument for what you should DECIDE; it is not a substitute for your deciding it. Same shape as the oracle-C divergence where I also had a strong technical case and also treated it as sufficient — the principle I accepted then in my own words, disclosure is not authorization. NO rev1 until you rule
- MR-2 ACCEPTED and it is the T2 CENSUS DEFECT REPEATED: I reported EIGHT sites as the population; the tree has THIRTEEN, verified independently at my seat with a tree-wide instrument — capture 6 and classify 2 name empty_config_keys and omit budget_override, eligibility 3 and restore 1 omit BOTH, and tests/test_repo_engine.cpp:628 names budget_override and omits empty_config_keys. WHERE MY INSTRUMENT CAME FROM IS THE WHOLE DEFECT: I took the sites GCC printed in the STOPPED build and called that the population, when a compiler's diagnostic list is bounded by where the build stopped, not by what exists. On T2 I did the same with a grep that could not match `Git::Opts opts;` and reported 5 of 8, wrote it down as measure the instrument's REACH not its intent and always print the denominator, and then used a failed build log as a census
- THE CORRECTION CHANGES THE CONCLUSION, AGAINST MY OWN PLAN: my explanation that empty_config_keys is silent because all eight sites NAME it is WRONG — FIVE sites omit it right now (eligibility.cpp:67, :109, :180; restore.cpp:30; test_repo_engine.cpp:628) and it is silent only because the build stopped before reaching them. Chained to my measured ARM 2, where budget_override braced alone still produced the missing-initializer error for empty_config_keys, THE LITERAL ONE-LINE B DOES NOT GREEN THE LINUX BUILD: it clears the eight that warned and hands the next compile five more
- STRENGTH MARKED HONESTLY: the 13-site census is MEASURED and ARM 2's warning behaviour is MEASURED, but their conjunction is an INFERENCE about what GCC does next on the real tree; O-1 and O-2 settle it, and rev1 will require the baseline run to ENUMERATE ALL warning sites rather than stopping at the first batch — the same fix as the census defect, applied to the instrument that produced it
- MR-3 ACCEPTED: the guard file is `tests/test_repo_engine.cpp` named literally, so the later token carries exactly two rows, `src/core/repo/git_exec.hpp` and `tests/test_repo_engine.cpp`; rev1 also requires confirming `biv_repo_engine_tests` compiles with `-Wall -Wextra -Werror`, per the reviewer and per my own point that a canary without the flag cannot fail. Note `test_repo_engine.cpp:628` is ITSELF one of the five omitting sites, so the guard's own translation unit is implicated either way
- THE DECISION FRAMED, NOT TAKEN: TWO-MEMBER greens the build across all 13 sites, makes the mandated canary green, two lines, no caller edits, both provable no-ops; ONE-LINE B exactly as ruled leaves 5 sites omitting empty_config_keys, on the measured ARM 2 behaviour the build stays RED, and the mandated canary cannot go green, so if you rule it the guard obligation must be WITHDRAWN or REDEFINED and the residual registered. I RECOMMEND the two-member fix and I am NOT taking it
- STATE: no rev1 filed and none until you rule; T1 00c06d9, T2 7688bbd, T3 70601fc FINAL; T4 29120d0 NOT final, NOT panelable, local, unpublished, worktree clean; findings (1)/(2)/(4), R-4.35, R-4.38, R-4.40 and the three permanent root-mode lineage record-defects all ride the stage-5 merge-readiness report; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
