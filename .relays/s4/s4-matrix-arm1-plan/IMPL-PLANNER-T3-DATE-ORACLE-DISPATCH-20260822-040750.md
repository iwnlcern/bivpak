## IMPL DISPATCH — T3 Oracle C date fix per approved rev1: one assertion in `harness/selftest/test_fixtures.py`, then six fixed-head proof obligations; token below

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-impl
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-RESOLVED-PREEXISTING-TOPOLOGY-ARTIFACT-USE-INIT-DATE-ORACLE-PROCEEDS-20260822-035347.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — delegated dispatch on the verified rev1 approval chain. The Orchestrator's `035347` relay expressly says this Pair Planner issues the token and itself issues none. Merge, push, PR mutation, remote CI, `.github` edit, publication, schema, deployment, and release are not dispatched; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: final T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`; reconstructed T3 under repair `a3501cc1728ca13289a8a4a96e49c9ee95e54698` on `s4-matrix/arm1-t3`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: IMPL — execute the approved one-assertion Oracle C correction, prove RED before edit and GREEN at the fixed head on macOS and Ubuntu 24.04 amd64 with a reaping PID 1, complete O-1 through O-6, and report the resulting local T3 head for Stage-3 paneling

Delegated-condition verification at issue time (`040750`):

1. **Approving edge:** `PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839.md`
   is `VERDICT: APPROVE`, `AUTHORITY: review-only`, FROM `s4-matrix.implementer` TO this seat,
   and is the sole holder of `s4-matrix-t3-date-oracle-fix-plan-review-r1`.
2. **Approved bytes re-derived now:** the rev1 PLAN is SHA-256
   `c15e5a99f600aff1f3aebd9c6525f62ad264a2271cdd8cfa97ee5e11191f0dbd`, Git blob
   `9b51c25baa24c84063abcd0a99a11fbcd2617e31`, exactly matching the approval's binding.
3. **Chain:** this token -> rev1 approval -> rev1 PLAN -> Orchestrator authorization `022336`,
   reaffirmed by `035347`. Each Pair dispatch ID is a sole holder, and the token ID was unused.
4. **Target identity:** isolated worktree
   `/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t3` is clean at
   `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; the target is 7842 bytes at SHA-256
   `b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df`.
5. **No design edge is claimed.** This is the bounded in-lane correction already authorized
   and reviewed, not a design amendment.

SCOPE_DIFF:
- harness/selftest/test_fixtures.py -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `harness/selftest/test_fixtures.py`: replace exactly the unique `%aI` and `%cI` assertion in
  `test_git_repo_builder_is_deterministic_and_host_config_isolated` with `%ad` and `%cd` under
  `--date=raw`, expecting author and committer fields `946684800 +0000`. The resulting file must
  be 7868 bytes at SHA-256 `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`.

BINDING EXECUTION CONDITIONS:

1. **RED before edit.** In disposable Ubuntu 24.04 amd64, observe the named node fail at exact
   pre-edit `a3501cc` for the `%aI` or `%cI` rendering mismatch. Use Docker `--init`, non-root
   execution, and raise the `nofile` soft limit to the inherited hard limit inside the drop.
2. **O-1 macOS GREEN at the fixed head:** `python3 -m pytest harness/selftest -q` with 997 passed;
   record the named node explicitly as PASSED.
3. **O-2 Linux GREEN at the fixed head:** run the same suite in disposable Ubuntu 24.04
   `--platform linux/amd64`, Docker `--init`, non-root, with the descriptor lift. Record the named
   node explicitly as PASSED. Separately-owned R-4.35 observations remain separately classified
   and may not be laundered into a whole-suite GREEN claim.
4. **O-3 real-fixture identity on both hosts:** use a fresh `--basetemp`, find exactly one
   `*/first/source/project`, STOP unless `N == 1`, and prove the raw author/committer string is
   byte-identical on both hosts and exactly the planned value.
5. **O-4 two scratch-copy discriminators:** mutate the fixture pin to
   `2000-01-01T00:00:01+0000` and separately `1999-12-31T19:00:00-0500`; each named-node run MUST
   fail. After each mutation restore and gate both `harness/bivharness/fixtures.py` at
   `6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303` and the edited test at
   `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`.
6. **O-5 census:** validate the instrument first on one known-YES and one known-NO file, then
   prove zero `%aI` and zero `%cI` over `harness`, `src`, `tests`, and `schemas`. Do not use `\b`
   with `git grep -E`; quote historical refspecs as `"${sha}:path"`.
7. **O-6 scope:** exactly one changed file before the source commit. Any other path moves: STOP.
8. Capture each exit status explicitly, never through a pipe. Retain non-empty receipts, hash them,
   and preserve the host worktree and all unrelated Docker resources.

NOT DISPATCHED: merge, push, force-push, PR mutation or comment, remote CI, `.github` edit,
publication, schema, T4, deployment, or release. T3 remains local and unpublished. T4 remains
held until T3 is final and its Stage-3 panel completes. Merge is not push and neither is release;
the release hold is ABSOLUTE.

Completion report must carry the fixed T3 SHA, exact target digest and size, retained evidence
root and receipt manifest digest, RED and both GREEN results, O-3 host identities, both O-4
must-be-NO exits plus dual restore gates, O-5 instrument controls and census, O-6 one-path proof,
and the final clean branch status.

DISPATCH IMPL

ACTIONS_GIT_REF: docs lane only — this dispatch relay and one live-EOF INDEX row ride one explicit-path commit. Verification was read-only: exact re-hash and blob identity of the approved plan, sole-ID checks, approval and authority-chain reads, and isolated-worktree head, status, target digest, and size checks. No candidate byte or ref moved; no container or remote action occurred at this seat.
FINAL_GIT_STATUS_SHORT: the dispatch relay and INDEX append are this seat's only claimed docs delta; all sibling-authored untracked paths remain preserved and unclaimed

CARRY LIST:
- bare `DISPATCH IMPL` to `s4-matrix.implementer`, parented to the approving rev1 review
- one-file scope and exact target digest; six obligations binding; RED before edit and fixed-head GREEN on both platforms
- Linux product-behaviour runs use Ubuntu 24.04 amd64 with Docker `--init`, non-root, and soft `nofile` raised to hard
- no remote CI, push, PR mutation, merge, publication, schema, T4, deployment, or release; release hold ABSOLUTE
