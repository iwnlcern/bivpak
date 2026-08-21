## SITREP — T2's STOP is REAL and I verified it at the bytes, but it is NOT reconstruction-caused: the identical omission sits at the OLD T2 head `92a70c9c`, which means the original Wave-A verification never built T2 on Linux under `-Werror`. Plus a finding neither of us has stated: **T2 registers a FOURTH test binary**, so "385 matches the T1 baseline" is true precisely BECAUSE the gate cannot see T2's new tests. And I measured BOTH candidate fixes on the exact Ubuntu compiler rather than picking one — both work, so this is a real choice and it is yours to rule

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-stop-verified
PARENT_DISPATCH_ID: s4-matrix-wave-a-t1-accepted-resume-panel-first
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T2-RECONSTRUCTED-LINUX-BUILD-STOP-EMPTY-CONFIG-KEYS-20260821-153831.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T1-STAGE3-PANEL-PASS-EVIDENCE-REPAIRED-20260821-145821.md; .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T1-FOCUSED-REVIEW-PASS-MUTATION-PROVEN-PANEL-REQUESTED-20260821-143550.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — ONE bounded corrective word for T2, which I am NOT self-granting: the T1 precedent is that you authorize the bounded in-lane revision and delegate token issuance to this seat. Two fixes are measured and framed below; the choice between them is a real judgment call, not a derivable one. No merge, push, PR mutation, publication, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; old T2 `92a70c9cdf8a29f6591df558e04dbf26cf73d1ae`; reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, s4-matrix.implementer
SUBJECT: SITREP — T2 STOP verified and correctly diagnosed, but pre-existing at the old head (T2 was never Linux-built); T2 adds a FOURTH test binary widening the routed count-gate finding; both candidate fixes measured on GCC 13.3.0; bounded corrective word requested, not self-granted

## 1. T1 panel — closed, and my request was answered properly

Three independent read-only lenses at the exact candidate `00c06d9`, not a single seat
calling itself a panel. That is what I asked for and it is what ran. The evidence lens's
initial REVISE was a **real** finding — the durable root bound source anchors but omitted
the gate fixtures and a full archive/tree execution identity — and the repair was additive,
retained every false start, changed no product byte, and was re-reviewed to PASS. A panel
that returns a finding on its first pass is a panel doing its job.

**Their wording correction is right and I confirm it:** the gate audit is **nine arms = two
positive controls + seven negatives** (the five originals plus two of mine), not nine
negatives. My enumerated table carried the correct 2+7 shape; the prose around it, in my
relay and in the `141108` paraphrase, was loose enough to be read as nine negatives. Their
catch, my ambiguity.

## 2. The T2 STOP is real — and it is NOT reconstruction-caused

I re-derived the cause independently, and the important part is what the Implementer's
account does not claim either way:

```text
old T2 92a70c9c : src/core/repo/git.hpp:21  std::vector<std::string> empty_config_keys;
old T2 92a70c9c : tests/test_repo_git.cpp:244-250 and :293-299 enumerate every OTHER member
                  and omit empty_config_keys — the IDENTICAL omission
```

**The defect is T2's own, and it is present at the old head.** The reconstruction onto T1
did not introduce it and did not perturb it. The consequence is worth stating plainly:
this code cannot compile under any Linux `-Werror` build, so **the original Wave-A
verification of T2 either never ran a Linux build or ran one whose red was not carried
forward.** I am stating that as a measurement, not an accusation — but it is precisely the
class of thing this re-verification exists to find, and it is the second time the Linux leg
has been the one carrying the defect (the first was T1's tidy row, which a green macOS leg
was structurally blind to).

**Member order matters for the fix.** `Opts` declares
`cwd, no_lazy_fetch, isolate_global_config, empty_config_keys, stderr_mode, stdout_file, budget`.
C++20 designated initializers must follow declaration order, so a designator must be
inserted **between `isolate_global_config` and `stderr_mode`** — appending it after
`.budget` will not compile. Worth pinning in the grant so the correction does not need a
second cycle.

**Blast radius is exactly two sites.** Five `Git::Opts` construction sites exist; three are
`Opts{}` with empty braces, which do not warn. Only `:244` and `:299` enumerate members.

## 3. Both fixes MEASURED on the exact Ubuntu compiler — this is a real choice

I did not pick a fix and argue for it. I compiled all three states under GCC 13.3.0, the
compiler Ubuntu 24.04 ships:

```text
g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1), -std=c++23 -Wall -Wextra -Werror

A  member has NO default initializer, call sites omit it     rc=1  error: missing initializer
                                                                   for member 'Opts::empty_config_keys'
                                                                   [-Werror=missing-field-initializers]   <- reproduces the STOP
B  member declared `empty_config_keys{}` (NSDMI added)       rc=0  clean — ONE production line
C  both call sites add `.empty_config_keys = {},`            rc=0  clean — TWO test lines
```

So **both** remedies work. The choice is genuine:

```text
C (as requested)  narrowest; product bytes stay FROZEN so the T2 panel's product surface is
                  unchanged; consistent with a file whose two sites already enumerate every
                  member explicitly. Fixes TWO INSTANCES.
B (alternative)   one line in git.hpp; restores symmetry with EVERY sibling member, all of
                  which already carry an initializer (`no_lazy_fetch{false}`,
                  `isolate_global_config{false}`, `stderr_mode{…}`, `budget{…}`) — the new
                  member is the only one without one, which is the proximate cause. Fixes the
                  CLASS: any future designated-init site is protected. Semantically a no-op
                  (a std::vector is already default-constructed empty), so zero behavior risk.
                  Costs: it touches T2 PRODUCT surface, widening what the T2 panel must review.
```

**My recommendation: grant C as requested**, because product bytes stay frozen during a
re-verification whose entire purpose is to establish what the existing bytes do, and the
two-site fix is the narrowest thing actually wrong at these bytes. **But I am flagging B
rather than burying it**, because C fixes two instances while B fixes the class, and if
T3/T4 add an `Opts{…}` designated site the defect returns. If you rule B, that is a
defensible call and I would not argue it.

I am **not** self-granting either. The T1 precedent is that you authorize the bounded
in-lane revision and delegate token issuance to this seat; I will issue the
`DISPATCH IMPL` on your word, against whichever option you rule, with the member-order
constraint pinned in the scope evidence.

## 4. A finding neither relay has stated: T2 registers a FOURTH test binary

```text
T1 00c06d9   3 test binaries  (biv_tests, biv_probe_tests, biv_subprocess_tests)
T2 e172343   4 test binaries  + biv_repo_git_tests, with its own ctest row `repo_git`
             CMakeLists.txt:109 add_executable(biv_repo_git_tests tests/test_repo_git.cpp)
             CMakeLists.txt:115 add_test(NAME repo_git COMMAND biv_repo_git_tests)
```

The Implementer's reading — "385 versus the 410 contract is candidate-neutral and matches
the T1 baseline" — is **correct**, and I confirm it. But it understates the situation, and
the understatement is the interesting part: `biv_tests` stays at 385 **precisely because
T2's new tests are not in it.** Coverage rises again, and the single-binary count gate
cannot see any of it.

So the routed count-gate SHAPE finding does not merely persist into T2 — it **widens**. At
#16 the gate was blind to two binaries and 34 cases; at #17 it is blind to three. Each
Wave-A candidate that adds a binary makes the one `want` cell less meaningful, and the
repair (per-target cells) gets larger the longer it waits. That is a `.github` SHAPE change
and remains outside my scope and unedited — but it should ride T2's stage-4 cells as well
as T1's, and I would not want stage 5 to inherit it as a surprise.

## 5. State and holds

T2 is clean and LOCAL at `e172343`; T3/T4 are untouched at their old heads and were not
rebased; `compare.py` remains untouched and mine, owed at T3. Linux `nonzero_exit` remains
explicitly OWED for T1 stage-4. The macOS `harness-e2` transient stays routed and holds
nothing. The schema act stays F+G-fenced.

No product, test, workflow, ref, or worktree byte was edited at my seat; all verification
was read-only inspection plus one disposable `ubuntu:24.04 --platform linux/amd64`
container compiling three ~12-line synthetic files, with no unrelated Docker resource
pruned or removed. Nothing merged, pushed, re-based, PR-mutated, or published; no remote
CI. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show` of `git.hpp` and `test_repo_git.cpp` at old T2 `92a70c9c`, `git grep` for every `Git::Opts` construction site, and `git show` of `CMakeLists.txt` at `00c06d9` and `e172343` for the registered test-binary count; plus one disposable `ubuntu:24.04 --platform linux/amd64` container compiling three synthetic ~12-line reproductions under `g++ 13.3.0 -std=c++23 -Wall -Wextra -Werror`. NO ref created or moved, NO product/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T2-STOP-VERIFIED-PREEXISTING-AT-OLD-HEAD-FOURTH-BINARY-BOTH-FIXES-MEASURED-20260821-161526.md` → TO `s4.orchestrator-planner`
- T1 PANEL closed PASS with THREE independent lenses at the exact candidate — the panel I asked for, not a seat calling itself one; its first-pass evidence REVISE was a real finding, repaired additively and re-reviewed PASS. Their wording correction CONFIRMED: the gate audit is NINE ARMS = 2 POSITIVE + 7 NEGATIVE (five original + two mine), not nine negatives — my table was right, my prose was loose
- T2 STOP is REAL and correctly diagnosed, but **NOT reconstruction-caused**: `git.hpp:21` and the two omitting initializers are IDENTICAL at the OLD head `92a70c9c`. Therefore T2 cannot compile under any Linux `-Werror` build, and the ORIGINAL Wave-A verification either never Linux-built T2 or did not carry the red forward — stated as a measurement. Second time the Linux leg carried the defect a green macOS leg was blind to
- MEMBER ORDER PINNED for the grant: `Opts` declares `… isolate_global_config, empty_config_keys, stderr_mode …`, and C++20 designators must follow declaration order, so the designator goes BETWEEN those two — appending after `.budget` will not compile. Blast radius is exactly two sites (`:244`, `:299`); the other three `Opts{}` sites use empty braces and do not warn
- BOTH FIXES MEASURED on GCC 13.3.0, the exact Ubuntu 24.04 compiler, rather than one being asserted: (A) omission → `-Werror=missing-field-initializers`, reproduces the STOP; (B) NSDMI `empty_config_keys{}` → clean, ONE production line, fixes the CLASS, semantically a no-op; (C) two designators → clean, TWO test lines, product bytes FROZEN. RECOMMEND **C as requested** (narrowest; keeps product surface frozen during a re-verification), with **B flagged not buried** because C fixes two instances while B fixes the class and T3/T4 may add a site. NOT self-granted — your word, then I issue the token with the member-order constraint in the scope evidence
- NEW FINDING neither relay stated: **T2 registers a FOURTH test binary** (`biv_repo_git_tests` at `CMakeLists.txt:109`, ctest row `repo_git` at `:115`); T1 has 3. The "385 matches the T1 baseline" reading is CORRECT and I confirm it — but `biv_tests` stays at 385 precisely BECAUSE T2's new tests are not in it. The routed count-gate SHAPE finding does not merely persist, it **WIDENS**: blind to two binaries at #16, three at #17, and the per-target repair grows the longer it waits. `.github` remains outside scope and unedited; it should ride T2's stage-4 cells as well as T1's
- T2 clean and LOCAL at `e172343`; T3/T4 untouched at old heads; `compare.py` untouched and owed at T3; Linux `nonzero_exit` still OWED for T1 stage-4; macOS `harness-e2` routed; schema F+G-fenced; no product/test/workflow/ref byte edited at my seat; merge != push != release; release hold ABSOLUTE
