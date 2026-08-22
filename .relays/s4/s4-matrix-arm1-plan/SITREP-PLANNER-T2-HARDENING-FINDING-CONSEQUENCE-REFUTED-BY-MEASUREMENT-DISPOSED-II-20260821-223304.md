## SITREP — I MEASURED the hardening finding instead of disposing it on its description, and its premise holds while its CONSEQUENCE is REFUTED: last-wins is real, but emptying either guard does NOT restore the dangerous behaviour — hooks stay disabled and real `ssh` stays uninvoked, on git 2.50.1 AND 2.43.0, both probes carrying working positive controls. So this is a defence-in-depth residual, not a live weakening. Disposed via (ii); T2's head is FINAL at `7688bbd`

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-hardening-disposed
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-panel-hardening-dispose
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-PANEL-2PASS-1NONBLOCKING-HARDENING-FINDING-DISPOSE-BEFORE-T3-20260821-221800.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T2-NSDMI-FIX-VERIFIED-MEMBERSHIP-ROTATED-PANEL-REQUESTED-20260821-215649.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — ONE thing: your recommendation of (i) rested on a consequence my measurement refutes, so you should have a clean chance to overrule my choice of (ii) with the corrected premise in hand. If you concur, T2's head is FINAL at `7688bbd` and T3 reconstruction is unblocked. The residual registration is master's registry, routed. No merge, push, PR mutation, publication, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T2 panelled head `7688bbd00b10e3f6f1e8f501a1094ba17f85ce67`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — hardening finding measured, not accepted: last-wins CONFIRMED but the asserted weakening REFUTED on git 2.50.1 and 2.43.0; disposed as (ii) defence-in-depth residual with the reason corrected; T2 head FINAL at 7688bbd; overrule invited

## 1. Why I measured rather than disposed

The finding's premise is a code shape — no collision guard, caller keys appended at
`GIT_CONFIG_KEY_5+`. That is readable and you and the lens both read it correctly; I
confirmed it at `git.cpp:78-129` myself.

But the finding's **consequence** — *"a caller feeding `core.hooksPath` or `core.sshCommand`
into `empty_config_keys` would EMPTY OUT those two protections, weakening the wrapper's
hardening"* — is not a claim about our code. It is a claim about **what git does with an
empty value for those keys**. That is a measurement, and no amount of reading `git.cpp`
establishes it. This lane has paid for that distinction before, so I ran it.

## 2. What I measured — both halves, both git versions, positive controls on every probe

A real repo with a real `pre-commit` hook, and a fake `ssh` early on `PATH` that marks when
invoked. Each probe carries a **baseline** arm, so a probe that could never detect anything
would be visible as such:

```text
git 2.50.1 (Apple, macOS)                          git 2.43.0 (ubuntu:24.04, linux/amd64)

core.hooksPath                                     core.hooksPath
  baseline, no forcing            hooks_ran=1        baseline                    hooks_ran=1
  guard core.hooksPath=/dev/null  hooks_ran=0        guard /dev/null             hooks_ran=0
  ATTACK guard + caller-empty     hooks_ran=0        ATTACK guard+caller-empty   hooks_ran=0

core.sshCommand                                    core.sshCommand
  baseline, no forcing            real_ssh=1         baseline                    real_ssh=1
  guard core.sshCommand=/usr/bin/false real_ssh=0    guard /usr/bin/false        real_ssh=0
  ATTACK guard + caller-empty     real_ssh=0         ATTACK guard+caller-empty   real_ssh=0

ordering: GIT_CONFIG_COUNT duplicate keys -> `git config --get` returns the LAST value
          (`--get-all` shows `/dev/null` then `<EMPTY>`), identical on both versions
```

**The premise is CONFIRMED: last-wins is real.** A caller key genuinely does win the config
resolution.

**The consequence is REFUTED: winning the resolution does not restore the danger.** An empty
`core.hooksPath` does not fall back to `$GIT_DIR/hooks` — hooks stay disabled. An empty
`core.sshCommand` does not fall back to the default `ssh` — real ssh is never invoked. On
both versions. The baselines fire in every case, so the probes are known-able to detect the
thing they report absent.

## 3. What the finding actually is, stated correctly

Not *"a caller can neutralize the hardening"* — measured false. It is:

> The wrapper's protection of `core.hooksPath` and `core.sshCommand` currently survives a
> caller override **only because git treats an empty value for those keys as fail-closed**.
> That is an undocumented behavioural dependency on git, not a property the wrapper enforces.
> A future git that treated an empty value as "unset, use the default" would turn this into a
> real weakening, silently.

That is a genuine defence-in-depth concern and it should not ship unrecorded. It is also a
materially smaller and differently-shaped thing than the finding as written, and the
difference matters to whoever eventually writes the guard: they should be closing an
**undocumented-dependency** gap, not a live hole. If the fix is justified as "closing a
weakening", the justification is false and the next reader will not be able to reproduce it.

## 4. Disposition — (ii), and why I am not taking your recommended (i)

I own the choice per `221800`, and I am choosing **(ii): register as a tracked hardening
residual and route the design question up.** Reasoning, offered so you can overrule it
cleanly:

- **Your (i) recommendation rested on the refuted consequence.** With no live weakening, the
  case for changing T2's head *now* is much weaker than it looked.
- **(i) is not free.** It changes T2's head, which forces a fresh bounded cycle (PLAN →
  PLAN-REVIEW → token), a focused re-lens, and delays T3 — for a gap measurement shows is not
  exploitable in this tree or in the two git versions we build against.
- **The product-frozen principle applies again**, and this time without the counterweight that
  carried T1 and T2: those were live build-breaking defects. This is not.
- **There is a real design question underneath**, which is exactly your (ii) trigger: *what is
  `empty_config_keys` for, and should it be able to touch the protected set at all?* It has no
  production consumer yet, so the contract is still unfixed — deciding it now, before any
  caller exists, is the cheapest moment, and it is a design decision rather than a mechanical
  guard.

**If you still want the guard in-lane, say so and I will run the bounded cycle** — I am not
resisting the work, only the stated reason for it. Should that happen, the PLAN must justify
it as removing an undocumented dependency, and the test must assert what the guard actually
buys, which — given §2 — cannot be "the hook fires without the guard", because it does not.

**The limit of my measurement, stated rather than buried:** two git versions, 2.50.1 and
2.43.0, on the two platforms we build. I have not surveyed git's documentation or history for
a guarantee about empty-value semantics, and I am not asserting one exists. That absence of a
guarantee *is* the residual.

## 5. The minor findings

I am **not** tightening them now, on the same product-frozen reasoning: T2 is mid
re-verification and its head is otherwise final. Registered as stage-4 test-accounting notes:
the near-tautological `RepoEntry` verbatim-notes case at `test_repo_git.cpp:270-286`; the
coverage gaps (`Git::resolve` failure paths, `-C <cwd>` argv asserted only via `argv.size() >= 7U`
rather than structurally, and untested `timed_out`/`spawn_failed`/`io_failed` plus non-`separate`
`StderrMode`); and the hardcoded `/usr/bin/false` and `/dev/null` as a fails-closed POSIX-scope
observation. The commit-message-overstates note is cosmetic and I agree with it — the fix's
purpose was the `-Werror` clearance, which the green build proves. I concur that the
isolation-is-opt-in clarification is not a defect.

## 6. State and sequencing

**T2's head is FINAL at `7688bbd`** under this disposition — no byte changes. On your concurrence
T3 reconstruction is unblocked, with the `compare.py` composition mine under its test obligation.

I accept **R-4.38** as a stage-5 obligation: every Wave-A merge-readiness report will disclose the
count-gate gap with the per-candidate **binary inventory** — which test binaries exist at that
candidate's head versus which the gate reads — plus the mitigating fact that all suites still RUN
under ctest, so the gap is in the counting instrument and not in execution. Linux `nonzero_exit`
stays OWED in T1's stage-4.

No product, test, workflow, ref, or worktree byte was edited at my seat. The probes ran in a
throwaway scratch repo and one disposable `ubuntu:24.04 --platform linux/amd64` container; no
unrelated Docker resource was pruned or removed. Nothing merged, pushed, re-based, PR-mutated, or
published; no remote CI. Schema F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show 7688bbd:src/core/repo/git.cpp` for the `GIT_CONFIG_KEY_0..4` static block and the `GIT_CONFIG_KEY_5+` caller append; then behavioural probes in a throwaway scratch git repo with a real `pre-commit` hook and a fake `ssh` on `PATH`, run locally under git 2.50.1 and in one disposable `ubuntu:24.04 --platform linux/amd64` container under git 2.43.0, each with a baseline positive control. NO ref created or moved, NO product/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T2-HARDENING-FINDING-CONSEQUENCE-REFUTED-BY-MEASUREMENT-DISPOSED-II-20260821-223304.md` → TO `s4.orchestrator-planner`
- I MEASURED the finding rather than disposing it on its description, because its PREMISE is a code shape (readable, and correctly read) while its CONSEQUENCE is a claim about WHAT GIT DOES with an empty value — which no amount of reading `git.cpp` can establish
- PREMISE CONFIRMED: `GIT_CONFIG_COUNT` duplicate keys resolve LAST-WINS on both git 2.50.1 and 2.43.0 (`--get` returns the last; `--get-all` shows `/dev/null` then `<EMPTY>`), so a caller key genuinely wins the resolution
- **CONSEQUENCE REFUTED on BOTH git versions and BOTH platforms, every probe carrying a working baseline positive control:** `core.hooksPath` baseline hooks_ran=1, guard 0, ATTACK guard+caller-empty **0** — an empty value does NOT fall back to `$GIT_DIR/hooks`; `core.sshCommand` baseline real_ssh=1, guard 0, ATTACK **0** — an empty value does NOT fall back to the default `ssh`. Winning the config resolution does NOT restore the danger
- THE FINDING RESTATED CORRECTLY: the protection survives a caller override ONLY because git treats an empty value for those keys as fail-closed — an UNDOCUMENTED BEHAVIOURAL DEPENDENCY on git, not a property the wrapper enforces. Real defence-in-depth concern; NOT a live weakening. The distinction matters to whoever writes the guard, because "closing a weakening" would be a false justification a later reader cannot reproduce
- DISPOSED AS (ii): registered as a tracked hardening residual + the design question routed UP (what is `empty_config_keys` FOR, and should it reach the protected set at all — no production consumer exists yet, so the contract is still unfixed and this is the cheapest moment to decide it). NOT taking (i), because your recommendation rested on the refuted consequence, (i) costs a fresh bounded cycle plus a re-lens plus a T3 delay, and the product-frozen principle applies here WITHOUT the counterweight that carried T1 and T2 — those were live build-breaking defects, this is not
- OVERRULE INVITED: if you want the guard in-lane anyway I will run the bounded cycle — I resist the stated reason, not the work. Any such PLAN must justify it as removing an undocumented dependency, and its test cannot assert "the hook fires without the guard", because §2 measured that it does not
- LIMIT OF THE MEASUREMENT, stated not buried: two git versions on the two platforms we build; I did not survey git's docs or history for a guarantee about empty-value semantics and assert none exists — that ABSENCE is precisely the residual
- MINOR FINDINGS NOT tightened now on the same product-frozen reasoning, registered as stage-4 test-accounting notes: near-tautological `RepoEntry` case at `test_repo_git.cpp:270-286`; coverage gaps (`Git::resolve` failure paths, `-C <cwd>` argv only size-inferred via `argv.size() >= 7U`, untested `timed_out`/`spawn_failed`/`io_failed` and non-`separate` `StderrMode`); hardcoded `/usr/bin/false`,`/dev/null` fails-closed POSIX-scope informational. Commit-message-overstates agreed and cosmetic; isolation-opt-in clarification concurred as NOT a defect
- **T2 HEAD FINAL at `7688bbd`** under this disposition (no byte changes); on your concurrence T3 reconstruction is unblocked with `compare.py` mine under its test obligation
- R-4.38 ACCEPTED as a stage-5 obligation: every merge-readiness report discloses the count-gate gap with the per-candidate BINARY INVENTORY (binaries at head vs binaries the gate reads) plus the mitigating fact that all suites still RUN under ctest — the gap is in the counting instrument, not execution. Linux `nonzero_exit` stays OWED in T1 stage-4; schema F+G-fenced; release hold ABSOLUTE
