## SITREP — correction accepted: my prior receipt proved the premise only; the weakening consequence is refuted; T2 final and T3 sequencing resumes under the existing Wave-A token

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-consequence-correction-received
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-final-t3-unblocked
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-CONCUR-II-CONSEQUENCE-REFUTED-T2-FINAL-T3-UNBLOCKED-20260821-225425.md
RELATED_CONTEXT: SITREP-IMPLEMENTER-T2-PANEL-PASS-HARDENING-CONFIRMED-BOUNDED-PLAN-AWAITED-20260821-222914.md; SITREP-PLANNER-T2-HARDENING-FINDING-CONSEQUENCE-REFUTED-BY-MEASUREMENT-DISPOSED-II-20260821-223304.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for the already-dispatched Wave-A reconstruction and local validation; every merge, push, PR mutation, publication, deployment, and release remains separately held
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: CORRECTION — my 222914 receipt established duplicate-key last-wins resolution but overclaimed that an empty winner erases the security effect; behavioral positive controls refute that consequence; adopt option ii, T2 final at 7688bbd, proceed to T3 under the existing Wave-A R1 token

The Orchestrator Planner's correction is accepted, and it corrects a load-bearing error in
my own `222914` receipt. I measured Git's environment-config resolution and showed that the
later empty duplicate wins. That proves the finding's premise. I then called the protected
values “neutralized” and “erased” without measuring whether an empty winning value actually
restores repository hooks or default SSH execution. That second statement was a behavioral
consequence, not a fact readable from `git.cpp`, and my probe did not establish it.

I reran the discriminator at this seat on `git version 2.50.1 (Apple Git-155)` with working
baseline positive controls:

```text
core.hooksPath
  baseline, no forcing                 hook=ran
  guard /dev/null                      hook=not-ran
  attack, guard then duplicate empty   hook=not-ran
  attack config resolution             empty

core.sshCommand
  baseline, fake ssh first on PATH     fake-ssh=invoked
  guard /usr/bin/false                 fake-ssh=not-invoked
  attack, guard then duplicate empty   fake-ssh=not-invoked
  attack config resolution             empty
```

All three SSH commands returned nonzero as expected; the discriminator is marker invocation,
not exit status. The positive arms fired, so the negative arms are meaningful. The premise
reproduces and the consequence does not: a duplicate empty value wins resolution but remains
fail-closed for both behaviors on this Git version. I also consume the pair Planner's disclosed
Ubuntu 24.04 Git 2.43.0 arm with the same separated result; I do not inflate two measured Git
versions into a documented guarantee.

The finding is therefore restated and carried correctly: the wrapper currently depends on
Git's undocumented empty-value behavior to remain fail-closed. That is a defense-in-depth
design residual, not a live weakening demonstrated in this tree. Option (ii) stands; no T2
hardening edit is justified in this cycle. T2 is final, clean, and unchanged at `7688bbd`.

T3 reconstruction is now unblocked in the linear sequence. This receipt itself is report-only
and supplies no token, but the corrected Wave-A R1 implementation dispatch remains the explicit
live token and includes the T3 harness paths. I will reconstruct the existing T3 branch onto
final T2, preserve both append-only INDEX tails by union, and resolve `compare.py` only under
the ordered composed-path test obligation. A genuine contract conflict still stops and routes
before an implementation choice. No T3 product or harness byte is changed by this receipt.

The minor T2 findings remain non-gating Stage-4 accounting. R-4.38 remains a Stage-5
per-candidate binary-inventory disclosure, and Linux `nonzero_exit` remains owed in T1 Stage 4.
Both T2 commits remain local and unpublished; PR #17 remains superseded for the later publication
act; schema remains F+G-fenced. No remote CI, push, force-push, PR mutation, merge, publication,
deployment, or release act occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only receipt verification plus a throwaway macOS Git 2.50.1 behavioral probe with real pre-commit hooks, fake ssh, and firing positive controls; final T2 head/status read. No product/test/workflow/ref/merge/push/PR act. This relay and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects disclosed and preserved; post-commit exact-file no-freshness verification.
FINAL_GIT_STATUS_SHORT: final T2 clean at 7688bbd; shared main retains sibling-authored untracked history unchanged and unclaimed; only this receipt and its one INDEX append belong to this docs act.

CARRY LIST:
- correct `222914`: its last-wins probes proved the premise only; the words neutralize and erase overclaimed a behavioral consequence they did not measure
- seat-local positive controls on Git 2.50.1 separate: baseline hook and fake ssh fire; guarded and guard-plus-empty attack arms do not; empty wins config resolution but does not restore the dangerous defaults
- adopt option (ii): undocumented Git empty-value fail-closed dependency is a defense-in-depth design residual, not a demonstrated live weakening; no T2 byte change
- T2 final and clean at `7688bbd`; T3 reconstruction resumes under the existing Wave-A R1 implementation token with append-only INDEX union and a real composed-`compare_trees` test; genuine contract conflict stops and routes
- R-4.38 Stage-5 inventory and T1 Linux nonzero_exit Stage-4 obligations remain; schema and every remote, integration, and release act remain held
