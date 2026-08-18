## SITREP (the Linux STOP is CORRECT and I uphold it — but the CAUSE is wrong, and the wrong cause would send the operator on an impossible errand) — **My Implementer stopped exactly where they should have: `failures=1` is observe-and-route, the four counts stayed untouched, nothing was committed, and no number was normalized. I uphold all of that. What I do NOT uphold is the diagnosis. The report calls the failing case "one inherited emulation-only product failure" that amd64 emulation "classifies as `nonzero_exit` rather than `spawn_error`", and asks me for either (1) "a canonical Ubuntu 24.04 native-amd64 runtime that preserves the workflow's invalid-executable semantics" or (2) a named inherited-emulation exception. OPTION 1 CANNOT BE SATISFIED BY ANY GLIBC LINUX RUNTIME, native or emulated, and routing it would burn a cycle chasing a runtime that does not exist.** **THE CAUSE IS ALREADY DIAGNOSED, AT MASTER, ON 2026-08-11, AND IT IS REGISTERED: `pdc/master/RESIDUALS.md` R-3.40's harness work-list, item (13), names this exact case — `tests/test_probe.cpp:273`, `"version probe does not fall back to PATH when a pinned executable cannot spawn"` — and states the mechanism as PROVED IN-CONTAINER: the fixture writes the TEXT `not an executable image\n` at mode 0700 (`test_probe.cpp:59-65`, read at the bytes at `9729191`) and expects `ProbeOutcome::spawn_error`; GLIBC's `posix_spawnp`/`execvp` FALL BACK TO `/bin/sh` ON ENOEXEC, so the spawn SUCCEEDS and a shell reports a bad command — `nonzero_exit`. macOS/BSD returns ENOEXEC to the caller, so the assertion holds there and FAILS ON LINUX BY CONSTRUCTION. The registry's words: "DETERMINISTIC PLATFORM SEMANTICS, not a flake" · "REPRODUCES on BASE and HEAD identically" · "attributable to NO build slice" · and, verbatim, "it must not be carried as 'unexplained' again."** **SO: this is not emulation, and a native amd64 GitHub `ubuntu-24.04` runner — glibc — would fail IDENTICALLY. The registry even names the two fix shapes (assert the platform-correct outcome, or make the fixture un-spawnable in a way glibc cannot reinterpret: a directory, or an invalid ELF header instead of shell-interpretable text), and names the owner: the harness/test seat, DUE "at the next Linux-touching head". THIS IS THAT HEAD.** **THE CHARACTERIZATION MATTERS AND I AM CORRECTING IT ON PURPOSE: "inherited emulation-only" is a FLAKE-SHAPED label for a deterministic semantic difference, and this registry carries an explicit anti-flake prohibition on a sibling row precisely because an owner would reasonably close a true finding filed that way. I will not route it under a label that could get it closed as environmental.** **THE ACTUAL BLOCKER, correctly framed: the workflow's Linux `failures: 0` pin CANNOT BE MET ON ANY GLIBC LINUX HOST while `test_probe.cpp:273` encodes a BSD assumption — so M-a's Linux half (`:268`, `:271`) cannot be transcribed from a green run. Not because of this fold. Not because of emulation. Because of a registered, diagnosed, already-owned test defect that has now come due by its own condition, and whose fix is OUT of my pair's scope in both directions — `test_probe.cpp` is not an IN path and the owner is not us.** **WHAT I VERIFIED AS GOOD, at the bytes, so the fold is not re-litigated on the way back: the held delta is exactly the seven authorized paths; every OUT row is zero-diff, INCLUDING `tests/test_probe.cpp` and `src/core/support/probe.cpp`, which is what excludes our delta as the cause ON MECHANISM rather than on correlation; the workflow diff is ONE line and it is m-3's, byte-exact — I re-derived the landed line's SHA-256 as `9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481`, EQUAL to the pin; `9729191` is untouched and nothing is staged.** Routing: me → `s4.orchestrator-planner` → master → the harness/test owner. I am not naming an m-x hop and I am not proposing a fix on an OUT path. Branch LOCAL and UNPUBLISHED; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-linux-stop-cause-corrected
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-linux-amd64-stop
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-COUPLED-FOLD-LINUX-AMD64-STOP-20260817-210613.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-DISPATCH-IMPL-TOKEN-20260817-193748.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the Linux half of the M-a grant cannot be discharged from any glibc Linux run while a registered test defect stands. The disposition is master's (with m-3 for the gate surface) and the fix is the harness/test seat's; neither is this pair's. No product byte moved, no count transcribed, no commit. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner
SUBJECT: SITREP — the Linux STOP is upheld but its CAUSE is corrected: not emulation, it is glibc ENOEXEC-to-/bin/sh fallback, already diagnosed and REGISTERED as R-3.40 work-list item (13) with a named owner and a due condition this head satisfies; option 1 as written is unsatisfiable on any glibc runtime; M-a's Linux half is blocked on that item, not on this fold

## 1. What my Implementer got RIGHT, and I uphold

```text
STOPPED before transcribing counts on a run whose `failures` was nonzero            CORRECT
left :68 / :71 / :268 / :271 untouched                                              CORRECT
treated failures=1 as OBSERVE-AND-ROUTE rather than a number to normalize           CORRECT
committed nothing; no incoherent or partially-counted state exists                  CORRECT
proposed no fix on an OUT path                                                      CORRECT
```

Had they transcribed `successes=411` from that run, the gate would have asserted `failures: 0` against a run
that observed 1. The refusal is the instrument working.

## 2. What I verified at the bytes before touching the diagnosis

```text
HEAD              972919137203cb2ecb1d9f4bba8d8cd31e27befc, untouched, nothing staged
held delta        exactly 7 modified paths, 460 insertions / 4 deletions — the seven authorized IN rows
OUT rows          ZERO DIFF, including tests/test_probe.cpp and src/core/support/probe.cpp
                  (this is what excludes our delta as the cause ON MECHANISM, not on correlation)
                  and sessions.cpp / render.cpp / envelope.cpp / main.cpp / pack/** per S-9 and the token
workflow diff     ONE added line at :76, inside expected_skips — m-3's, and BYTE-EXACT:
                  sha256 of the landed line = 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481
                  EQUAL to the pin taken from 224751:46. The four count lines are untouched.
```

## 3. The cause — corrected, with the measurement

### 3.1 The case and its fixture, read at `9729191`

```text
tests/test_probe.cpp:260-278   TEST_CASE("version probe does not fall back to PATH when a pinned
                               executable cannot spawn")
tests/test_probe.cpp:273       CHECK(result->outcome == biv::support::ProbeOutcome::spawn_error);
tests/test_probe.cpp:59-65     write_invalid_executable: `out << "not an executable image\n";`
                               then chmod 0700 — a TEXT file, mode 0700
```

### 3.2 The registry already holds the diagnosis

`pdc/master/RESIDUALS.md`, R-3.40's harness work-list, **item (13)** — *"NOW DIAGNOSED AT MASTER
(2026-08-11)"*:

- the failure is `tests/test_probe.cpp:273`, this exact case, and it is **"DETERMINISTIC PLATFORM
  SEMANTICS, not a flake"**;
- mechanism, **demonstrated in-container**: **glibc's `posix_spawnp`/`execvp` FALL BACK TO `/bin/sh` on
  ENOEXEC** — the spawn SUCCEEDS and a shell reports a bad command, so the outcome is `nonzero_exit`.
  macOS/BSD returns ENOEXEC to the caller, so the assertion holds there and **fails on Linux BY
  CONSTRUCTION**;
- **"REPRODUCES on BASE … and HEAD identically"**, `test_probe.cpp` **byte-identical** across the paneled,
  base and new SHAs, **"attributable to NO build slice"**;
- the fix is the TEST's — *"assert the platform-correct outcome, or make the fixture un-spawnable in a way
  glibc cannot reinterpret — e.g. a directory, or a binary with an invalid ELF header rather than
  shell-interpretable text"*; **owner = the harness/test seat, DUE "at the next Linux-touching head"**;
- and, verbatim: **"it must not be carried as 'unexplained' again."**

The observed behavior matches the mechanism exactly: `/bin/sh` reading `not an executable image` finds no
command called `not`, exits nonzero, and the probe classifies `nonzero_exit`.

### 3.3 Therefore option 1 is unsatisfiable, and I am not routing it

> *"provide a canonical Ubuntu 24.04 native-amd64 runtime that preserves the workflow's invalid-executable
> semantics"*

**No such glibc runtime exists.** The behavior is glibc's `execvp`, not qemu's. GitHub's `ubuntu-24.04`
runner is glibc, so the REAL target fails identically — a native amd64 host changes nothing. Routing this
would spend a cycle looking for a runtime that cannot be found, and would leave the actual defect unfixed.

### 3.4 And the label matters

"Inherited emulation-only" is a **flake-shaped** label for a deterministic semantic difference. This registry
carries an explicit anti-flake prohibition on a sibling row (R-3.39) for exactly this reason: *an owner would
reasonably close a true finding filed as environmental, and the defect would survive the closure.* I am not
routing this one under a label that invites that outcome.

### 3.5 What was NOT run, stated so nobody reads more into this than it holds

The current Linux run took **no exact-base control at `9729191` in that container**; the registry's control
was taken at `origin/main 38a4702`. I am **not** claiming a fresh base control. I am claiming something
stronger and cheaper: the failing test and the code it exercises are **zero-diff** in the held delta, and the
mechanism is deterministic platform semantics with no dependency on anything the delta touches. If master
wants the base control re-taken at `9729191` anyway, that is a reasonable ask and my Implementer can run it —
but it would confirm, not decide.

## 4. The real blocker, correctly framed

```text
The Linux job pins  failures: 0   (:269) — OBSERVE-AND-ROUTE, never editable by this arm
No glibc Linux run of this suite can produce failures=0 while test_probe.cpp:273 encodes a BSD assumption
=> M-a's Linux half (:268 successes, :271 skips) cannot be transcribed FROM A GREEN RUN
=> the coupled fold's "both platforms green in the ONE head" cannot be reached from inside this pair's scope
```

**This is not caused by the fold and cannot be discharged by the fold.** `tests/test_probe.cpp` is not an IN
path, the owner is the harness/test seat, and the item's own due condition — *the next Linux-touching head* —
is satisfied by this head.

## 5. Options, framed — the choice is master's, not mine

```text
(i)  RECOMMENDED — route R-3.40 work-list item (13) to its NAMED OWNER for the one-test fix (the registry
     already specifies both acceptable shapes). It is DUE by its own condition at this head. Then re-observe
     Linux on the fold tree and land ONE GREEN HEAD as the token requires. Cost: one cross-team hop for a
     defect that is diagnosed, owned, and overdue — and the Linux count gate stays honest.
(ii) land the macOS half and hold the Linux counts — I NAME IT TO REJECT IT. The token requires both
     platforms green in one head, and it would move :68/:71 while leaving :268/:271 stale, i.e. a
     half-repaired gate that reads as repaired.
(iii) master rules a BOUNDED exception for the Linux observation with R-3.40(13) named and excluded, and
     specifies how the two Linux numbers may be observed without laundering failures=1. This is a .github
     gate-semantics question (m-3's surface) crossed with M-a's binding condition ("transcribed from an
     observed run on the target it governs"), so it is master's with m-3 — not mine, and not my pair's.
```

**Not requested:** authority to touch `test_probe.cpp`, `probe.cpp`, the harness, or Docker/CI policy; a
remote Actions run (unfunded by operator ruling, and forbidden absent an explicit request); or any edit to
`:269`/`:270`.

## 6. State

```text
implementation   COMPLETE in the worktree, HELD unstaged and uncommitted at 9729191 — correct
macOS            canonical selector GREEN on the exact final tree (6/6 suites)
named mutants    (m)/(n)/(o)/(q) each executed, observed behaviourally RED, reverted, GREEN — as dispatched
leg (h)          ABSENT, not stubbed, not ticked; listing halves unasserted; no stub annotation text
counts           NONE transcribed. The four grant lines are untouched.
gates ahead      my byte verification of the successor commit, then m-1's byte veto and m-3's combined
                 successor review — none of them eligible yet, because no product commit exists
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — read-only verification. Read this pass: the `210613` report in full; the held worktree's `git rev-parse HEAD`, `git status --short`, `git diff --stat`, and the full `.github/workflows/s2-harness.yml` diff; the landed `:76` line re-hashed and compared to the `224751:46` pin; `tests/test_probe.cpp:59-65` and `:255-290` at `9729191`; `pdc/master/RESIDUALS.md` R-3.40's harness work-list item (13) and the sibling anti-flake prohibition on R-3.39; the prior successor report `163751`'s exact-base-control paragraph (control taken at `d7db861`, not at `9729191`). I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped; `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds disclosed by line and unchanged: cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; time inversions at 222 and 393. None mine; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` at `9729191` carries my Implementer's SEVEN authorized unstaged paths, held deliberately and not mine to touch; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LINUX-STOP-VERIFIED-CAUSE-CORRECTED-R340-13-DUE-20260817-214907.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LINUX-STOP-VERIFIED-CAUSE-CORRECTED-R340-13-DUE-20260817-214907.md` → `s4.orchestrator-planner`
- THE STOP IS UPHELD: my Implementer refused to transcribe counts from a run whose failures was nonzero, left :68/:71/:268/:271 untouched, committed nothing, and proposed no OUT-path fix. All correct — transcribing successes=411 there would have pinned a gate asserting failures:0 against a run that observed 1
- THE CAUSE IS CORRECTED, and the correction is load-bearing: this is NOT emulation. The registry already holds the diagnosis — pdc/master/RESIDUALS.md R-3.40 harness work-list item (13), DIAGNOSED AT MASTER 2026-08-11, names this exact case (tests/test_probe.cpp:273, "version probe does not fall back to PATH when a pinned executable cannot spawn") and proves the mechanism in-container: the fixture writes the TEXT "not an executable image" at mode 0700 (test_probe.cpp:59-65, read at the bytes) and expects spawn_error, but GLIBC's posix_spawnp/execvp FALL BACK TO /bin/sh on ENOEXEC, so the spawn succeeds and a shell reports a bad command — nonzero_exit. macOS/BSD returns ENOEXEC, so the assertion holds there and FAILS ON LINUX BY CONSTRUCTION. Registry words: DETERMINISTIC PLATFORM SEMANTICS not a flake; REPRODUCES on BASE and HEAD identically; attributable to NO build slice; and verbatim, it must not be carried as unexplained again
- CONSEQUENCE: the report's OPTION 1 — a native amd64 Ubuntu runtime preserving the invalid-executable semantics — IS UNSATISFIABLE ON ANY GLIBC RUNTIME, since the behavior is glibc's execvp and not qemu's, and GitHub's ubuntu-24.04 runner is glibc, so the REAL target fails identically. Routing it would spend a cycle hunting a runtime that does not exist and leave the defect unfixed. I am also refusing the "inherited emulation-only" LABEL: it is flake-shaped for a deterministic semantic difference, and this registry carries an explicit anti-flake prohibition on the sibling R-3.39 row precisely because an owner would reasonably close a true finding filed that way
- THE REAL BLOCKER, framed: no glibc Linux run of this suite can produce failures=0 while test_probe.cpp:273 encodes a BSD assumption, so M-a's Linux half (:268 successes, :271 skips) cannot be transcribed from a green run, and the token's both-platforms-green head is unreachable from inside this pair's scope. test_probe.cpp is not an IN path and the owner is the harness/test seat — whose due condition, "at the next Linux-touching head", THIS HEAD SATISFIES
- VERIFIED GOOD AT THE BYTES so the fold is not re-litigated: HEAD 9729191 untouched with nothing staged; the held delta is exactly the seven authorized paths at 460 insertions and 4 deletions; every OUT row is ZERO-DIFF including tests/test_probe.cpp and src/core/support/probe.cpp, which excludes our delta as the cause ON MECHANISM rather than on correlation; the workflow diff is ONE line at :76 and it is m-3's, byte-exact, its sha256 re-derived by me as 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 EQUAL to the 224751:46 pin; macOS canonical 6/6 green; all four named mutants executed RED, reverted, GREEN; leg (h) absent not stubbed not ticked
- DISCLOSED, NOT CLAIMED: the current Linux run took NO exact-base control at 9729191 in that container, and the registry's control was at origin/main 38a4702. I claim the stronger and cheaper ground instead — the failing test and the code it exercises are zero-diff, and the mechanism is deterministic platform semantics independent of everything the delta touches. If master wants the base control re-taken at 9729191 it is a reasonable ask and would confirm, not decide
- OPTIONS (master's, with m-3 for the gate surface): (i) RECOMMENDED route R-3.40 item (13) to its NAMED OWNER for the one-test fix, whose two acceptable shapes the registry already specifies, since it is DUE at this head, then re-observe Linux on the fold tree and land ONE GREEN HEAD; (ii) land the macOS half and hold the Linux counts — NAMED ONLY TO REJECT IT, since it moves :68/:71 while leaving :268/:271 stale, a half-repaired gate that reads as repaired; (iii) master rules a BOUNDED exception naming and excluding R-3.40(13) and specifying how the two Linux numbers may be observed without laundering failures=1. NOT REQUESTED: authority over test_probe.cpp, probe.cpp, the harness, Docker/CI policy, a remote Actions run, or any edit to :269/:270
- ROUTING is pair to s4.orchestrator-planner to master to the harness/test owner; no m-x hop named and no fix proposed on an OUT path. Implementation COMPLETE but HELD unstaged at 9729191; no counts transcribed; my byte verification, m-1's veto and m-3's combined review are all still ineligible because no product commit exists; branch LOCAL and UNPUBLISHED; merge is not push is not release; release hold ABSOLUTE
