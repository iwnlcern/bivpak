## SITREP — T2 Stage-3 panel PASS received; latent static-guard collision confirmed independently; in-lane hardening is technically sound, but no source token exists and the bounded pair plan is awaited before T3

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-panel-hardening-received-await-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-panel-hardening-dispose
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-T2-PANEL-2PASS-1NONBLOCKING-HARDENING-FINDING-DISPOSE-BEFORE-T3-20260821-221800.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for the bounded in-lane cycle; a pair Planner PLAN, approving Implementer PLAN-REVIEW, and later separate implementation token remain required before any source keyboard act
BASE: panelled T2 `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T2 panel PASS received and hardening finding confirmed; recommend the bounded in-lane disposition, await the pair PLAN naming collision invariant plus adversarial test; T2 not final and T3 remains held

The Stage-3 disposition is received exactly as filed: two independent lenses PASS, the
third returns only nonblocking findings, and T2 at `7688bbd` is not refuted. The panel
PASS does not make that head final because the real hardening finding must be disposed
before T3 reconstructs.

## Independent confirmation of the hardening finding

Direct read of `src/core/repo/git.cpp` at `7688bbd` confirms:

```text
GIT_CONFIG_KEY_0  core.hooksPath             value /dev/null
GIT_CONFIG_KEY_1  credential.helper          value empty
GIT_CONFIG_KEY_2  core.sshCommand            value /usr/bin/false
GIT_CONFIG_KEY_3  core.fsmonitor             value empty
GIT_CONFIG_KEY_4  core.alternateRefsCommand  value empty
caller keys       appended at index 5 onward, always with empty values
collision guard   absent
```

The claim that order is security-relevant was tested directly with Git's environment-config
interface:

```text
core.hooksPath: guard /dev/null then caller empty  -> rc 0, resolved value empty
core.hooksPath: caller empty then guard /dev/null  -> rc 0, resolved value /dev/null
core.sshCommand: guard /usr/bin/false then empty   -> rc 0, resolved value empty
```

The current append order therefore lets a caller name either protected key and neutralize
its non-empty guard. The finding is real.

The nonblocking classification is also accurate. A broad fixed-tree search finds no product
producer of `empty_config_keys`: production only declares the member and consumes it in
`build_spawn_request`; the sole population is the test assignment at
`tests/test_repo_git.cpp:195`. There is no current call path that supplies either protected
name.

## Disposition

I recommend option (i), bounded in-lane hardening. The existing non-empty static values already
express the invariant that hooks and SSH execution must fail closed; allowing a general
empty-key facility to erase them is inconsistent with that existing protection rather than a
new product feature. The mechanism remains plan-owned: the successor must name whether it
skips/rejects protected caller keys or orders static guards last, keep
`GIT_CONFIG_COUNT` exact, and add an adversarial test proving both
`core.hooksPath=/dev/null` and `core.sshCommand=/usr/bin/false` survive caller collision.

This relay is not that PLAN, not a PLAN-REVIEW, and not an implementation token. No source,
test, branch, or evidence head changes here. Await the pair Planner's bounded PLAN; I will
review it against the collision invariant and exact test oracle before any later source token.

The panel's minor findings remain non-gating stage-4 accounting and do not silently widen the
hardening scope. The R-4.38 stage-5 obligation is received: report the per-candidate binary
inventory, identify which binaries the count gate reads, and disclose that CTest still runs
the suites while the counting instrument has incomplete reach.

T2 remains local at clean `7688bbd`, but is not final. T3/T4 and `compare.py` stay held;
Linux `nonzero_exit` remains owed in T1 Stage-4; schema remains F+G-fenced. No remote CI,
push, force-push, PR mutation, merge, publication, deployment, or release act occurred. The
release hold is ABSOLUTE.

ACTIONS_GIT_REF: review-only exact panel lint/identity read; fixed-head git.cpp and reference census; three direct Git environment-config order probes; T2 head/status. No product, test, workflow, branch, ref, container, remote CI, push, merge, PR mutation, publication, schema, deployment, or release act. This relay plus one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects disclosed and preserved; post-commit exact-file no-freshness verification.
FINAL_GIT_STATUS_SHORT: T2 clean at 7688bbd; shared main retains sibling-authored untracked relays and migration note unchanged and unclaimed; only this receipt and its one INDEX append belong to this seat.

CARRY LIST:
- T2 Stage-3 panel PASS received at `7688bbd`; candidate not refuted, but head not final until hardening disposition
- collision independently confirmed: caller empty values appended after static `core.hooksPath=/dev/null` and `core.sshCommand=/usr/bin/false` win last and erase both guards
- latent/nonblocking independently confirmed: no production producer of `empty_config_keys`; only test line 195 populates it
- recommend bounded in-lane hardening with exact count plus adversarial protection test; await pair Planner PLAN, then Implementer PLAN-REVIEW, then separate implementation token
- T3 reconstruction held until final T2 head and focused re-lens; R-4.38 binary inventory disclosure carried to Stage 5; all integration and release holds remain
