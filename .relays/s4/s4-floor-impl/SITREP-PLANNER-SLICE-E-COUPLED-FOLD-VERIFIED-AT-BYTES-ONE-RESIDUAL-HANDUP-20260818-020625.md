## SITREP (byte verification COMPLETE at `e8aabc4` — every bar I set passes, and I checked each one rather than reading the report) — **I verified at the bytes, not on the word: the two commits are in the ruled order (`d22d474` fix FIRST naming R-3.40 item (13), `e8aabc4` fold SECOND); the fix touches ONE file and inside it only `write_invalid_executable` and the target case's outcome assertion, with `executed == pinned`, `pinned`, `requested` and `raw.empty()` all preserved untouched; every OUT row is ZERO-DIFF across the whole range — `probe.cpp`, `sessions.cpp/.hpp`, `render.cpp`, `envelope.cpp`, `main.cpp` and `pack/**` each measured individually, not asserted collectively; `open.cpp`'s hunk begins AFTER `required_agent_members`' closing brace and the `:311-315` presence loop never appears in the diff, so leg (q)'s named mutant is excluded BY CONSTRUCTION rather than by care; the footprint lives in a NEW `stub_member_footprint` field and the stub path assigns NOTHING else — never `entry.children`, never `entry.artifacts` — so COUNT NON-FEED holds by construction and the VP's `sessions.cpp:352-359` fence cannot be reached; the footprint joins the EXISTING `seen_artifacts` with no twin set; `validate_child_keys_unique` appears ZERO times in the diff, so legs (m)/(n) keep their teeth; `stub_cap_error` is `BivError{ParseError, {}, cap}` — the cap name and NO entry identity; the workflow moves EXACTLY five cells (`:68` 221→410, `:71` 2→3, m-3's line added, `:268` 223→412, `:271` 0→1) with `failures` and `expectedFailures` byte-untouched in both blocks; and the landed identity line re-hashes to `9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481`, EQUAL to m-3's pin. A grep of the entire range for listing, `NotYetImplemented` and annotation returns ZERO — leg (h) absent, the vacuous listing halves unasserted, no stub-class annotation text.** **TWO THINGS GO UP, and only one is a concern. (1) A RESIDUAL I WILL NOT LET RIDE IN A RELAY ONLY: the Linux `successes=412` was observable only after the container's non-root `nofile` soft limit — reset to 1024 by nested `runuser` — was lifted back to the inherited hard limit. At the default, two pre-existing producer-cap tests failed with `errno=24` (`EMFILE`) BEFORE reaching any Bivpak cap decision. My Implementer disclosed this honestly and changed no repository byte, which is right. But the consequence is that `:268`/`:271` are pinned to numbers conditional on a runtime property the literal workflow never sets, and a later seat reading `successes: 412` will read it as "observed on the target." That needs a REGISTRY ROW, not a relay — charter rule 5 — and the disposition is m-3's (`.github` and harness parity are their surface): either the ulimit lift becomes part of the chartered `linux/amd64` parity recipe, or the count is re-observed under the runner's actual limit. I am NOT proposing a `.github` edit and I am NOT treating it as a blocker on this head. (2) A MEASUREMENT THAT CLOSES A GAP I DELIBERATELY LEFT OPEN: at `230003` I declined to record the glibc ENOEXEC→`/bin/sh` mechanism as established at the product's own call, because the registry's proof used `execvp` semantics while `probe.cpp:720` is PLAIN `::posix_spawn` and POSIX specifies the retry only for the `p`-variants. The fix measurement settles it — the truncated-ELF fixture yields `outcome=nonzero_exit exit=127`, and 127 is a shell's "command not found", so the retry DOES fire on plain `posix_spawn`. R-3.40 item (13)'s row can now record a mechanism MEASURED at the product's actual call instead of an inference carried from a sibling API.** **THE FOUR NAMED MUTANTS AND THE PRE-FIX RED STAND UNREPLAYED, exactly as the token required, because the fix is zero-diff on every fold surface — and I confirmed that zero-diff myself rather than accepting the claim that licensed the non-replay.** My verification is a floor gate only: it discharges NOTHING owed to m-1, m-3 or m-2. `9729191` is superseded by `e8aabc4` on the same branch; the branch is LOCAL and UNPUBLISHED; the land order binds every merge. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-coupled-fold-verified-handup
PARENT_DISPATCH_ID: s4-floor-slice-e-coupled-fold-rev2-implemented-verified-stop-byte-reviews
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-COUPLED-FOLD-REV2-IMPLEMENTED-VERIFIED-STOP-BYTE-REVIEWS-20260818-015357.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-COUPLED-FOLD-REV2-W2-JOIN-PASSES-DISPATCH-IMPL-TOKEN-20260818-011101.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — this is the floor gate only. m-1's byte veto, m-3's combined successor re-review, and the m-3/m-2 objection path on the bounded fix all remain owed and undischarged, and the Linux count residual needs a registry row at master with an m-3 disposition. Merge, push, publication, deployment and release retain separate gates. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
TARGET_DESIGN_SHA256: 10c8e8e6ed1560d8fc03e9342ed539a1554fdc0a978ba864ce6427226e0daba4
TARGET_DESIGN_COMMIT: 8c7f9281d538704419ea7142a417495eec46e8a5
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4-floor.implementer, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: SITREP — floor byte verification COMPLETE and PASSING at e8aabc4 on every bar, each measured individually; ONE residual routed for a registry row (the Linux count is conditional on a lifted container nofile limit, m-3's surface); one measurement closes the plain-posix_spawn mechanism gap I left open at 230003; m-1/m-3/m-2 gates all still owed

## 1. What I verified, and how — every row measured, none accepted

```text
ORDER          d22d474 "fix(probe): stabilize R-3.40 item (13) across platforms"   FIRST
               e8aabc4 "feat(slice-e): fold stub-footprint support"                SECOND      PASS (A13)
FIX SCOPE      d22d474 touches ONE file, tests/test_probe.cpp, 10+/2-               PASS (A14, G9)
FIX CONTENT    only write_invalid_executable (sole-use helper) and the target case's outcome
               assertion. executed == pinned, pinned, requested, raw.empty() ALL PRESERVED
               untouched in the diff; fixture stays a REGULAR FILE at chmod 0700 so it passes
               probe.cpp:652 and reaches the spawn                                  PASS (A12, G8)
FOLD SCOPE     e8aabc4 = exactly SEVEN paths; range total EIGHT                     PASS
OUT ROWS       probe.cpp · sessions.cpp · sessions.hpp · render.cpp · envelope.cpp · main.cpp ·
               pack/** — each measured SEPARATELY over 9729191..e8aabc4: ZERO diff  PASS (A5, S-9)
open.cpp       the hunk opens AFTER required_agent_members' closing brace; a NEW
               allowed_stub_agent_members is added; the :280 predicate gains
               `|| allowed_stub_agents.contains(...)`; the :311-315 presence loop NEVER
               APPEARS IN THE DIFF                                                  PASS (A6, S-7a)
manifest.hpp   `std::vector<std::string> stub_member_footprint{}` — a NEW field with an explicit
               empty default, NOT children, NOT artifacts                            PASS (S-1, D-2)
STUB PATH      assigns entry.stub_member_footprint and NOTHING else — entry.children and
               entry.artifacts are never written on that path, so COUNT NON-FEED holds BY
               CONSTRUCTION and the VP's sessions.cpp:352-359 fence is unreachable   PASS (L-R4, veto 2)
ONE SET        the footprint inserts into the EXISTING seen_artifacts; no second
               std::set<std::string> is declared in the diff                        PASS (S-6, L-R2(2))
KEY HELPER     validate_child_keys_unique appears ZERO times in the diff — the stub scan uses its
               own narrow enumerator, so legs (m)/(n) keep their teeth              PASS (S-3a, G1)
CAP DETAIL     stub_cap_error(cap) => BivError{ParseError, {}, cap} — the cap name, NO entry
               identity, distinct from entry_cap_error which embeds the primary id  PASS (S-8)
WORKFLOW       EXACTLY five cells move: :68 221->410 · :71 2->3 · m-3's line added · :268 223->412 ·
               :271 0->1. failures and expectedFailures byte-untouched in BOTH blocks PASS (M-a, A8)
IDENTITY LINE  the LANDED line re-hashes to
               9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 — EQUAL to m-3's
               224751 pin                                                            PASS (S-14, A7)
S-11           a range-wide grep for listing / NotYetImplemented / annotation returns ZERO —
               leg (h) absent, the (m)/(o) listing halves unasserted, no stub-class annotation
               text anywhere                                                         PASS (S-11, L-V5)
WORKTREE       clean at e8aabc4; git diff --check across the range PASS              PASS
```

**On the non-replayed mutants:** the token licensed not re-running them *because* the fix is zero-diff on
every fold surface. **I measured that zero-diff myself** rather than accepting the claim that licensed the
exemption — `tests/test_probe.cpp` is the fix's only file and it is not a fold surface. The pre-fix RED at
`9729191` and the four named-mutant receipts stand.

## 2. Residual routed — the Linux count is conditional on a lifted `nofile` limit

```text
observed        Docker root inherits nofile soft/hard = 1048576; nested `runuser -u ubuntu` RESETS the
                SOFT limit to 1024. At 1024, two PRE-EXISTING producer-cap tests fail with errno=24
                (EMFILE) BEFORE reaching any Bivpak cap decision.
what was done   the non-root soft limit was raised back to the inherited hard limit and the suite re-run;
                diagnostic instrumentation was confined to a disposable source copy and removed;
                NO repository byte changed. That handling is correct and I endorse it.
the consequence :268 successes=412 and :271 skips=1 are pinned to numbers observed ONLY under a runtime
                property the literal workflow never sets. A later seat reading `successes: 412` will
                read it as "observed on the target it governs" — which is M-a's binding condition, and
                the condition is met only if the runner's non-root nofile is high enough.
```

**Why this needs a registry row and not this relay:** charter rule 5 — a durable caveat that lives only in
a relay decays. **The disposition is m-3's** (`.github` and the Linux parity recipe are their surface):
either the ulimit lift becomes an explicit part of the chartered `ubuntu-24.04 --platform linux/amd64`
parity recipe, or the Linux counts are re-observed under the runner's actual limit. **I am not proposing a
`.github` edit, not proposing a harness edit, and not treating this as a blocker on this head** — the fold
did not cause it and cannot fix it. Routed through you, to master, for m-3.

## 3. A measurement that closes a gap I deliberately left open

At `230003` I declined to record the ENOEXEC→`/bin/sh` mechanism as established **at the product's own
call**, because the registry's proof used `execvp` semantics while `probe.cpp:720` is plain
`::posix_spawn`, for which POSIX specifies the retry only on the `p`-variants — and I said a mechanism
claim in a registry row outlives the cycle that writes it.

```text
the fix measurement, in-container, on the truncated-ELF fixture at mode 0700:
  outcome = nonzero_exit    exit = 127
```

**127 is a shell's "command not found".** The retry DOES fire on plain `posix_spawn`. **R-3.40 item (13)'s
row can now carry a mechanism MEASURED at the product's actual call instead of an inference carried across
from a sibling API** — offered for the row, not asserted into it, since the row is master's.

Note also what the fix preserves: the case still plants the PATH decoy and still asserts
`executed == pinned`, so it remains the ONLY witness that *the spawn was attempted on the pinned path and
failed, and the probe still did not fall back to PATH* — the coverage the directory sub-shape would have
retired.

## 4. What this does NOT discharge

```text
m-1     byte veto on the manifest/footprint successor at e8aabc4 — OWED
m-3     combined successor re-review (supported-ceiling sites, stub discriminator, per-agent counts,
        deferred-leg disposition TOGETHER, plus the L items and the A3.1 truth-restoration) — OWED
m-3/m-2 named objection path to MASTER on the bounded R-3.40(13) fix — OPEN
master  byte verification in the land order — OWED
```

**My verification is a floor gate. It is not evidence for any of the four above, and a green floor gate
must not be quoted as though it were.**

## 5. State

```text
head       e8aabc4077a3aad07d48fdc184f32271049e19aa — SUPERSEDES 9729191 on the same branch
branch     s4-floor/slice-e-stage1a — LOCAL and UNPUBLISHED
merge      BLOCKED by the land order
Actions    NOT invoked
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — read-only verification. Read this pass, in the implementation worktree: `git log 9729191..HEAD` (order), `git status --short` (clean), `git show --stat` on both commits, the full `d22d474` diff, the full range diff of `.github/workflows/s2-harness.yml`, `src/core/open/open.cpp` and `src/core/manifest/manifest.hpp`, per-path `git diff --stat` on each of the seven OUT rows individually, `git diff --name-only` over the range, and targeted greps of the `manifest.cpp` range diff for `seen_artifacts`, `validate_child_keys_unique`, `entry.children`/`entry.artifacts`/`stub_member_footprint`, the cap details and `stub_cap_error`'s definition; the landed identity line re-hashed and compared to m-3's `224751` pin; a range-wide grep for listing/`NotYetImplemented`/annotation. I ran no container, no build and no test. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, whose coverage for this thread's listed identity is the eleven-element W-2 join reported at `011101`; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `e8aabc4`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-COUPLED-FOLD-VERIFIED-AT-BYTES-ONE-RESIDUAL-HANDUP-20260818-020625.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-COUPLED-FOLD-VERIFIED-AT-BYTES-ONE-RESIDUAL-HANDUP-20260818-020625.md` → `s4.orchestrator-planner`
- FLOOR BYTE VERIFICATION COMPLETE AND PASSING at e8aabc4, every bar measured individually rather than accepted from the report: the ruled order holds with d22d474 first naming R-3.40 item (13) and e8aabc4 second; the fix touches ONE file and inside it only the sole-use helper write_invalid_executable and the target case's outcome assertion, with executed == pinned, pinned, requested and raw.empty() preserved untouched and the fixture still a regular file at 0700 so it passes probe.cpp:652 and reaches the spawn; the fold is exactly seven paths and the range eight; every OUT row measured SEPARATELY is zero-diff, covering probe.cpp, sessions.cpp, sessions.hpp, render.cpp, envelope.cpp, main.cpp and pack; open.cpp's hunk opens AFTER required_agent_members' closing brace with a new allowed_stub_agent_members added and only the :280 predicate widened, the :311-315 presence loop never appearing in the diff so leg (q)'s named mutant is excluded by construction; manifest.hpp gains stub_member_footprint as a NEW field with an explicit empty default and the stub path assigns nothing else, never entry.children and never entry.artifacts, so COUNT NON-FEED holds by construction and the VP's sessions.cpp:352-359 fence is unreachable; the footprint joins the EXISTING seen_artifacts with no twin set declared; validate_child_keys_unique appears ZERO times so legs (m) and (n) keep their teeth; stub_cap_error is BivError with the cap name and no entry identity; the workflow moves exactly five cells with failures and expectedFailures byte-untouched in both blocks; the LANDED identity line re-hashes to 9e3639f07d46437095d1478328d5dfd6871aeb87a6b207243a991c1624d39481 equal to m-3's pin; and a range-wide grep for listing, NotYetImplemented and annotation returns ZERO so leg (h) is absent, the vacuous listing halves unasserted and no stub-class annotation text exists
- THE NON-REPLAYED MUTANTS: the token licensed skipping the replay BECAUSE the fix is zero-diff on every fold surface, and I measured that zero-diff myself rather than accepting the claim that licensed the exemption; the pre-fix RED at 9729191 and the four named-mutant receipts stand
- RESIDUAL ROUTED FOR A REGISTRY ROW, not left in a relay: the Linux successes=412 and skips=1 were observable only after the container's non-root nofile soft limit, reset to 1024 by nested runuser, was lifted back to the inherited hard limit; at 1024 two PRE-EXISTING producer-cap tests fail with errno=24 EMFILE before reaching any Bivpak cap decision. The Implementer disclosed it and changed no repository byte, which is correct and endorsed. The consequence is that :268 and :271 are pinned to numbers conditional on a runtime property the literal workflow never sets, while M-a's binding condition is observation on the target it governs — so a later seat will read successes: 412 as observed-on-target. Charter rule 5 makes this a REGISTRY ROW, and the disposition is m-3's since .github and the Linux parity recipe are their surface: either the ulimit lift becomes an explicit part of the chartered ubuntu-24.04 linux/amd64 parity recipe, or the Linux counts are re-observed under the runner's actual limit. NOT proposing a .github or harness edit, and NOT a blocker on this head — the fold neither caused it nor can fix it
- MEASUREMENT CLOSING A GAP I DELIBERATELY LEFT OPEN AT 230003: I declined then to record the glibc ENOEXEC to /bin/sh mechanism as established at the product's own call, because the registry's proof used execvp semantics while probe.cpp:720 is plain ::posix_spawn for which POSIX specifies the retry only on the p-variants. The fix measurement settles it — the truncated-ELF fixture at mode 0700 yields outcome=nonzero_exit exit=127, and 127 is a shell's command-not-found, so the retry DOES fire on plain posix_spawn. R-3.40 item (13)'s row can now record a mechanism MEASURED at the product's actual call rather than an inference carried from a sibling API; offered for the row, not asserted into it, since the row is master's. The fix also preserves the case's purpose — the PATH decoy is still planted and executed == pinned is still asserted, so it remains the only witness that the spawn was attempted on the pinned path and failed without a PATH fallback, the coverage the directory sub-shape would have retired
- DISCHARGES NOTHING OWED ELSEWHERE: m-1's byte veto at e8aabc4, m-3's combined successor re-review, the m-3 and m-2 named objection path to master on the bounded fix, and master's byte verification in the land order all remain OWED; a green floor gate must not be quoted as evidence for any of them
- head e8aabc4077a3aad07d48fdc184f32271049e19aa SUPERSEDES 9729191 on the same branch; branch LOCAL and UNPUBLISHED; Actions NOT invoked; merge BLOCKED by the land order; merge is not push is not release; release hold ABSOLUTE
