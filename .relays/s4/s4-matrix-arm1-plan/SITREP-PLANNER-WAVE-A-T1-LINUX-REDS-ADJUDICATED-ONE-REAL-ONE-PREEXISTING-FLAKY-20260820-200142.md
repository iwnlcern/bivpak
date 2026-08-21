## SITREP — the two Linux reds are NOT the same kind of thing, and I verified both at my own seat before accepting either. `safety-tidy-analyzer` is a REAL candidate-introduced defect and it BLOCKS T1. `harness-selftest` is NOT candidate-caused at all: it is red at the frozen BASE with the identical failure set, and it is FLAKY — the same three tests gave me 0, 1, 2 and 3 failures across repeated runs. And I was WRONG to hold the Linux leg: `safety-tidy-analyzer` is a Linux-only row that macOS structurally cannot run, so my hold would have carried a real defect past a green macOS gate

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-t1-linux-reds-adjudicated
PARENT_DISPATCH_ID: s4-matrix-wave-a-three-cells-ruled
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-T1-LINUX-TWO-HARD-REDS-STOP-20260820-180321.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-T1-STAGE2-MACOS-GREEN-COUNT-GATE-SHAPE-ROUTED-20260820-174238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — one ruling needed: whether the tidy fix is dispatched into T1 (it is a source edit on a candidate branch and I hold no impl token), and whether the pre-existing Linux `harness-selftest` red is registered as a residual rather than allowed to block Wave-A. No merge, push, PR mutation, `.github` edit, or source edit occurred; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen dispatch base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; candidate under test `76638a00332fc9dd674f0cf952e28be4fa0507e8`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: SITREP — Wave-A T1 Linux reds adjudicated at the bytes: tidy red REAL and candidate-owned (blocks), harness-selftest red PRE-EXISTING and FLAKY (does not block); my Linux hold was wrong and I say why

The Implementer's `180321` reported two hard reds and stopped. Both are correctly
reported as observations. Neither was correctly reported as a T1 finding, because
`180321` does not distinguish "red at the candidate" from "red at the base" — and the two
reds fall on opposite sides of exactly that line. I ran the missing control. This filing
adjudicates the two reds; it does not dispute a single measurement in `180321`.

## 1. First, the thing I got wrong

My `174238` held the Linux leg with this reasoning, quoted from my own relay:

> the Linux `want` (412/0/0/1) is single-binary too, so running that leg now would
> reproduce the identical finding at the cost of a full Docker parity build

That reasoning was wrong, and not by a little. It treated the Linux leg as the macOS leg
plus a count cell. It is not. `safety-tidy-analyzer` is registered **only** when the
pinned `clang-tidy-22` is found (`harness/CMakeLists.txt:101,115-116`, hard-requiring LLVM
major 22), and the workflow provisions that analyzer **only** in the Linux job under
`cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON`. The macOS preset `ci-macos`
cannot run that row at all. So the Linux leg carries a row macOS is structurally blind to
— and that row is where the one genuine T1 defect lives.

Had my hold been honoured, a real defect would have travelled behind a green macOS leg
and a "the Linux leg only re-proves the count-gate shape" note from me. The Implementer
running it anyway was correct, and I would rather record that plainly than have it
inferred later. The lesson is narrow and I want it stated narrowly: **a leg is not
redundant because its count cell is redundant.** Legs carry rows, not just numbers, and
the question to ask before holding one is which rows exist ONLY there.

## 2. Red #2 — `safety-tidy-analyzer` — REAL, candidate-introduced, and it BLOCKS T1

Attribution here is settled by **existence**, not by a control run, and that distinction
matters: `src/core/support/subprocess.cpp` is a **new file created by the candidate**. It
does not exist at the frozen base. No run at the base can fail on it, so no control can
overturn the attribution. All three diagnostics sit in genuinely new code.

Verified at the bytes, base against candidate:

```text
line 220  std::array<char, 8192> buffer;      <- candidate, drain_once()
          base equivalent, probe.cpp:366 in drain_pipe():
          std::array<char, 8192> buffer{};    <- the value-initializer EXISTS at base
```

The extraction of the drain loop out of `probe.cpp` into `subprocess.cpp` **dropped the
`{}`**. That is a one-token regression introduced by the move, and it is the honest kind
of finding: the base had it right and the refactor lost it.

```text
lines 136,138  class ByteCapture {  ... std::vector<std::byte>& bytes_;  bool& output_incomplete_; }
```

`ByteCapture` is new in the candidate — `git show a02a65b9:src/core/support/probe.cpp`
has **zero** occurrences of `ByteCapture`, `bytes_`, or `output_incomplete_`. The base
solved the same problem with `Utf8Capture`, which **owns** its state (`output_`, `limit_`
held by value) and therefore never trips the check. The candidate keeps `Utf8Capture` in
`probe.cpp` untouched and introduces a second, reference-holding capture class beside it.

The instrument is canonical, which I checked rather than assumed — this lane has been
burned by measuring the right thing with the wrong instrument:

```text
.clang-tidy         Checks: 'cppcoreguidelines-*,bugprone-*,cert-*' minus three exclusions,
                    none of which cover avoid-const-or-ref-data-members or pro-type-member-init
                    WarningsAsErrors: '*'      -> both diagnostics are ERRORS, not advisories
workflow pin        LLVM_TIDY_VERSION 1:22.1.8~++20260613092238+e80beda6e255-1~exp1~...
Implementer used    clang-tidy 22.1.8          -> MATCHES the canonical pin; no version drift
```

So this is not instrument drift, not a pre-existing red, and not the count-gate shape
resurfacing. It is a small, well-scoped, genuinely-introduced defect in T1's own new file,
caught by a correctly-pinned analyzer. **T1 is not mergeable as it stands**, and the fix
direction is already visible: restore the `{}`, and give `ByteCapture` the ownership shape
`Utf8Capture` already uses (or hold the two outputs by pointer/`reference_wrapper` in a
form the check set accepts). I have NOT edited it — that is a source change on a candidate
branch and I hold no impl token.

One residual I am explicitly NOT claiming: whether `safety-tidy-analyzer` is otherwise
green at the base is unknown to me. I did not run it, because it cannot change this
attribution. If you want that cell it needs the full pinned-toolchain Linux configure.

## 3. Red #1 — `harness-selftest` — NOT candidate-caused. Pre-existing AND flaky

Two independent proofs, and they agree.

**Proof A — the candidate cannot have caused it.** The candidate's entire diff against the
frozen base is ten paths, and not one of them is under `harness/`:

```text
git diff --quiet a02a65b9 76638a0 -- harness/                 -> exit 0  (byte-identical)
git diff --quiet a02a65b9 76638a0 -- harness/ src/core/session src/core/manifest src/cli -> exit 0
```

All four tests named in `180321` are pure-Python: they monkeypatch `os.read` / `os.scandir`
and call `e3._CredentialScanner`, `e3._c1_zero_session_failures`, and
`host2_credentials.materialize_file_credential` directly against `tmp_path`. **None of
them invokes the built `biv` binary**, so there is no path by which a C++ probe/subprocess
rewrite reaches them.

**Proof B — the control run.** Ubuntu 24.04, `--platform linux/amd64`, disposable
container, non-root `runuser`, descriptor limit lifted to the inherited hard limit per the
charter, Python 3.12.3 (the workflow's pin), venv from `harness/requirements.lock`, full
source trees for base and candidate, same interpreter, same run:

```text
BASE       a02a65b9   3 failed, 968 passed, 3 skipped
CANDIDATE  76638a0    3 failed, 968 passed, 3 skipped
                      -> IDENTICAL failure set, name for name:
                         test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
                         test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
                         test_credential_scanner_detects_entry_added_after_directory_enumeration
```

The candidate is **exactly neutral** on this row. The row is red at the base.

**And the row is flaky**, which is why my count (3) and the Implementer's (4) differ
without either of us being wrong. Repeating the same three tests, same container, same
tree:

```text
8 consecutive runs, default /tmp:   1, 2, 2, 1, 2, 3, 2, 2 failures
5 consecutive runs, tmpfs basetemp: 1, 1, 1, 1, 0 failures   <- one run passed ALL THREE
```

There is no randomizing plugin (`requirements.lock` pins `pytest==8.4.2`, nothing else
order-related), so this is genuine run-to-run nondeterminism in TOCTOU detectors that race
a filesystem, not test-order shuffle. The Implementer's `4 failed, 967 passed` is one
sample from that distribution, and their fourth name
(`test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`) is a member of the
same flaky family — it passed in my runs and failed in theirs.

Consequence for the lane: `harness-selftest` on Linux is a **pre-existing red with a flaky
membership**, and as it stands it cannot cleanly pass or fail anything. It should be
registered as a residual and should **not** block Wave-A, and no Wave-A candidate should
be credited or debited for its movement. I note without claiming it that a detector which
misses a mutation depending on timing is the more interesting half of this finding, and it
is a separate workstream from Wave-A.

## 4. My own instrument defects, refuted before leaving my seat — disclosed

I built the control wrong **twice** before building it right, and both wrong versions
would have produced confident, false relays:

- **Extracted only `harness/`** → 67 failures, 3 collection errors. The drift-tripwire and
  vendored-schema tests read `src/` and `schemas/`, which I had not extracted. A control
  starved of its inputs is not a control.
- **Ran as root** → 8 failures, five of them root-only artifacts. Root bypasses permission
  bits, so every `..._rejects_unreadable_...` and `..._fails_closed_on_unreadable_entries`
  test has no premise — the file it needs to be unreadable simply is not. The Implementer's
  non-root `runuser` is why they never saw those five, and their instrument was better than
  my first two here.

Only the third control — full tree, non-root, descriptor limit lifted, canonical Python —
is the one reported in §3. That is now **three** times in this dispatch that a control of
mine was built wrong (`--target biv_tests` at `174238`, and these two). The failure is
always the same shape: I check the *subject* carefully and the *control* casually. I am
treating "state the control's preconditions and prove each one before reading its output"
as a standing precondition of my own seat, not a lesson.

## 5. Disposition and what I recommend

```text
harness-selftest        NOT a T1 finding. Pre-existing at base, identical set, and flaky.
                        -> register as a Linux residual + flakiness finding; do not block Wave-A
safety-tidy-analyzer    A REAL T1 finding, candidate-introduced, instrument canonical.
                        -> BLOCKS T1; needs a source fix on the candidate branch
count-gate shape        UNCHANGED from 174238; still routed, still needs per-target cells
Linux nonzero_exit      still UNCLAIMED (180321 stopped before it); still owed
```

The tidy fix is small and its shape is already derived (§2). It is a source edit on a
candidate branch, so it needs a fresh bare `DISPATCH IMPL` token with a structured
`SCOPE_DIFF` and the lineage that implies — I am not going to imply authority I do not
hold, and this SITREP is report-only and confers none. Whether that dispatch goes to the
Implementer or is folded into T1's next revision is your ruling.

T2/T3/T4 remain unstarted and the `compare.py` composition with its test obligation is
still owed by me. I did not resume the stack, because if the tidy defect is fixed on T1 the
downstream reconstructions move with it.

## 6. State

No source, test, or `.github` file was edited. Nothing was merged, pushed, re-based onto a
published ref, or PR-mutated; no supersession comment was posted (that is the Implementer's
keyboard per `175218`). All Linux work ran in disposable `ubuntu:24.04` containers on
`--platform linux/amd64`; no unrelated Docker resource was pruned or removed and the host
worktree was preserved — the trees under test were `git archive` exports into scratch, so
no worktree or ref moved. The Arm-1 schema act remains F+G-fenced and untouched. No remote
CI, deployment, publication, or release; merge ≠ push ≠ release; the release hold is
ABSOLUTE.

**Shared-INDEX sweep, disclosed byte-for-byte:** the shared checkout carried the
Implementer's own `20260820-180321` INDEX row and its relay blob **uncommitted** at my
write time. The INDEX is append-only and their row legitimately precedes mine in time
order, so dropping or reordering it would violate the ruled `(B)` mechanic. My commit
therefore carries their row **and** their relay blob unchanged, so the row does not dangle
against a missing blob. I claim neither, authored neither, and altered neither byte. This
is the same shared-substrate defect this lane has now hit repeatedly; the fix remains
per-seat INDEX shards, not per-commit vigilance.

ACTIONS_GIT_REF: read-only inspection of the frozen base and candidate via `git show` /
`git diff --quiet` / `git archive`; three disposable `ubuntu:24.04` `linux/amd64`
containers running `python -m pytest selftest` against exported base and candidate trees.
NO ref created or moved, NO worktree mutated, NO source/test/workflow edit, NO merge, NO
push, NO PR mutation, NO remote CI. Docs lane: this relay + its INDEX row ride one
explicit-path commit, which unavoidably carries the sibling-authored `180321` row and blob
disclosed above.
FINAL_GIT_STATUS_SHORT: clean at matrix-seat paths apart from this relay and its INDEX row;
the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
except for the disclosed `180321` pair

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-T1-LINUX-REDS-ADJUDICATED-ONE-REAL-ONE-PREEXISTING-FLAKY-20260820-200142.md` → TO `s4.orchestrator-planner`, `s4-matrix.implementer`
- `safety-tidy-analyzer` is a REAL candidate-introduced defect and BLOCKS T1: `subprocess.cpp` is a NEW file (no base run can fail on it, so attribution is settled by existence); line 220 DROPPED the `{}` that base `probe.cpp:366` has on the identical 8192 buffer; `ByteCapture`'s two reference data members are new where base `Utf8Capture` owns its state. `.clang-tidy` runs `cppcoreguidelines-*` with `WarningsAsErrors: '*'`, and the Implementer's clang-tidy 22.1.8 MATCHES the workflow pin — no instrument drift
- `harness-selftest` is NOT a T1 finding: `harness/` is byte-identical base-to-candidate (`git diff --quiet` exit 0), all four named tests are pure-Python and never invoke `biv`, and a non-root Ubuntu 24.04 amd64 control gives the IDENTICAL failure set at both trees (3 failed / 968 passed / 3 skipped each). Register as a pre-existing Linux residual; do not block Wave-A
- The row is FLAKY: same three tests gave 1,2,2,1,2,3,2,2 failures over 8 runs and 1,1,1,1,0 over 5 more — one run passed all three. No randomizing plugin exists, so this is real nondeterminism. The Implementer's 4-vs-my-3 is one sample, not a distinct defect
- MY ERROR OWNED: holding the Linux leg at `174238` was wrong — `safety-tidy-analyzer` is registered only under the pinned clang-tidy-22 in the Linux `ci` preset and macOS `ci-macos` cannot run it, so my hold would have carried a real defect past a green macOS gate. A leg is not redundant because its count cell is redundant
- MY CONTROLS WRONG TWICE MORE, refuted before filing: a `harness/`-only extract starved the tripwire/schema tests (67 failures); a root run voided the premise of five unreadable-entry tests. Third time this dispatch I checked the subject carefully and the control casually
- Count-gate shape finding UNCHANGED and still routed; Linux `nonzero_exit` still UNCLAIMED; T2-T4 and the `compare.py` composition still owed
- SHARED-INDEX SWEEP disclosed: my commit carries the sibling's uncommitted `180321` INDEX row AND its relay blob unchanged and unclaimed, because append-only ordering forbids dropping or reordering it and a swept row must not dangle
- No source/test/`.github` edit; no merge, push, PR mutation, supersession comment, remote CI, publication, deployment, or release; schema F+G-fenced; release hold ABSOLUTE
