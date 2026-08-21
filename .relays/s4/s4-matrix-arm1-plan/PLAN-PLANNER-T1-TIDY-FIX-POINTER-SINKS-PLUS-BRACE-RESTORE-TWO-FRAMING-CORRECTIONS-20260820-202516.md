## PLAN (bounded T1 tidy repair — I am NOT issuing the impl token in this relay; this is the PLAN your PLAN-REVIEW gates, and the bare `DISPATCH IMPL` follows only after your approve) — the chosen shape is **pointer-held sinks + restore the `{}`**, deliberately the narrowest change that clears both firing checks, because it preserves properties (ii) and (iii) *by not touching the logic that implements them*. **TWO CORRECTIONS to the framing I was handed, both verified at the bytes and both material to the acceptance bar: (1) there is NO "per-stream `output_incomplete` replacing a shared flag" — `output_incomplete` does not exist ANYWHERE at the frozen base (`git grep output_incomplete a02a65b9 -- src/ tests/` returns nothing); T1 ADDED the field. What is per-stream is the DETECTION (each `ByteCapture` measures its own `cap_` against its own `bytes_`), OR-accumulated into ONE `SpawnResult::output_incomplete`. Preserving "a per-stream field" would be preserving something that has never existed, and I will not write that into a plan. (2) The violation's origin is narrower than "the extraction": `ff37028` held `bytes_` as `std::reference_wrapper` and was tidy-CLEAN; `d87d83a` reduced it to a plain `T&` AND added `bool& output_incomplete_` — that ONE commit introduced BOTH firing members, and it is the SAME commit whose `bytes_.reserve()` hunk `76638a0` already had to revert as the O(N²) defect. So this is not a mystery regression; it is the remaining bad hunk of a commit already known-bad in part.** **A THIRD FINDING I am putting IN SCOPE because it makes property (ii) falsifiable instead of asserted: `output_incomplete` is bound by exactly ONE test (`test_subprocess.cpp:86`), and that test caps BOTH streams at 3 — so it cannot distinguish per-stream detection from any coarser mechanism, and there is NO negative case anywhere. A permanently-true flag passes the current suite. That is the unfalsifiable-box shape this lane has paid for repeatedly, and "preserve behavior the tests cannot see" is not a bar anyone can grade. I am requiring three cases: stdout-only truncation (must-be-YES), stderr-only truncation (must-be-YES), and both caps ample (must-be-NO, the discriminator).** **REFERENCE_WRAPPER, SAID OUT LOUD AND NOT SILENTLY: the Orchestrator instructed that `reference_wrapper` was reduced to a plain reference upstream and must not be silently reintroduced. I considered it and I am NOT choosing it — for `bytes_` it would be a clean revert of `d87d83a`'s bad hunk, but `std::reference_wrapper<bool>` for the flag forces `output_incomplete_.get() = output_incomplete_.get() || ...`, and I will not split the two members across two idioms for symmetry's sake. I also considered and REJECTED the ownership reshape (`Utf8Capture`'s shape) for this pass: it is the better long-term design and the Orchestrator named it first, but it moves the byte sinks out of `SpawnResult` and forces a transfer at BOTH tail returns (`:711` and `:726`), so a missed path silently DROPS captured output — trading a compile-time analyzer red for a runtime data-loss class, on a release-held product, inside a repair pass. I am registering it as a follow-up, not doing it here.** the fix is 7 changed lines in ONE file plus three test cases; nothing sealed, schema, charter, `.github`, or cross-lane is touched; the Linux tidy leg must be re-run GREEN at the fixed head before the stack resumes; T2/T3/T4 and the `compare.py` composition stay held; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t1-tidy-fix-authorized-in-lane
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-WAVE-A-T1-LINUX-REDS-ADJUDICATED-ONE-REAL-ONE-PREEXISTING-FLAKY-20260820-200142.md; .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-SUPERSESSION-COMMENTS-COMPLETE-T1-TIDY-AWAITS-IMPL-TOKEN-20260820-200811.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane revision of T1 authorized at `201613`. This relay carries NO token and authorizes NO keyboard: it is the PLAN your PLAN-REVIEW gates. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`, verified)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — T1 tidy repair: pointer-held sinks in ByteCapture + restore the value-initializer, plus three tests making the truncation flag falsifiable; two byte-verified corrections to the acceptance-bar framing; PLAN-REVIEW requested

## 1. What is actually wrong, at the bytes

Two members and one local, all inside T1's own new `src/core/support/subprocess.cpp`:

```text
:136  std::vector<std::byte>& bytes_;             cppcoreguidelines-avoid-const-or-ref-data-members
:138  bool& output_incomplete_;                   same check
:220  std::array<char, 8192> buffer;              uninitialized local (base probe.cpp:366 has buffer{})
```

`.clang-tidy` runs `cppcoreguidelines-*,bugprone-*,cert-*` minus three exclusions — none of
which covers either firing check — under `WarningsAsErrors: '*'`. So all three are errors.

Provenance, which narrows the repair (`git log -L 118,140:src/core/support/subprocess.cpp`):

```text
ff37028   bytes_ held as std::reference_wrapper<std::vector<std::byte>>   -> TIDY-CLEAN
d87d83a   reference_wrapper reduced to plain T&  + adds bool& output_incomplete_
          + adds bytes_.reserve(bytes_.size() + retained)                 -> BOTH violations
76638a0   removes that reserve (the O(N^2) defect)                        -> partial revert of d87d83a
```

`d87d83a` is the single origin of both firing members, and one of its other hunks has
already been reverted for a separate defect. That is the commit under repair, not "the
extraction" generally.

## 2. Correction 1 — there is no per-stream `output_incomplete` field, and never was

The acceptance bar I was handed says the fix must preserve "the per-stream
`output_incomplete` behavior the review-fold introduced". Measured:

```text
git grep -n output_incomplete a02a65b9 -- src/ tests/     -> NO MATCHES (absent at base)
git show d87d83a -- src/core/support/subprocess.hpp       -> + bool output_incomplete{false};  (ADDED)
:554-557  BOTH captures are constructed over the SAME result.output_incomplete
```

So the field is **new in T1**, it is **one shared bool on `SpawnResult`**, and nothing was
"replaced". The real, preservable property is narrower and I state it in the form I intend
to be graded on:

> **P2 (the true property):** truncation is DETECTED per stream — each `ByteCapture`
> compares its own `cap_` against its own `bytes_.size()` — and any stream's truncation
> is OR-accumulated, monotonically, into the single `SpawnResult::output_incomplete`,
> which once set is never cleared by a later complete write.

I am flagging this rather than transcribing the phrase I was given, because a plan that
promises to preserve a per-stream field would be unprovable at the bytes and your
PLAN-REVIEW should refuse it.

## 3. Correction 2 — the property is currently untestable, so I am fixing that too

`output_incomplete` is bound by exactly one assertion in the whole suite:

```text
tests/test_subprocess.cpp:86   CHECK(result->output_incomplete);
   in TEST_CASE "run_argv marks both captured streams incomplete at their caps"
   ... which sets request.stdout_cap = 3U AND request.stderr_cap = 3U
```

Both streams are capped, so the case cannot separate per-stream detection from a single
coarse flag — and **there is no negative case anywhere**, so a flag hard-wired to `true`
passes the current suite unchanged. That is a box that cannot fail for the thing it exists
to catch. Preserving P2 against this suite would be preserving nothing measurable, so the
three cases in §4 are part of the fix, not a nicety.

## 4. The change, in full

**(a) `subprocess.cpp` ByteCapture — pointer-held sinks.** Sole change is how the two
sinks are held; every arithmetic and control expression is character-for-character
unchanged apart from `.`→`->` and `x`→`*x`:

```cpp
  ByteCapture(std::vector<std::byte>& bytes, const std::size_t cap,
              bool& output_incomplete)
      : bytes_{&bytes}, cap_{cap}, output_incomplete_{&output_incomplete} {}

  void write(const char* data, const std::size_t size) {
    const auto retained =
        std::min(size, cap_ - std::min(cap_, bytes_->size()));
    *output_incomplete_ = *output_incomplete_ || retained != size;
    const std::string_view input{data, retained};
    std::ranges::transform(
        input, std::back_inserter(*bytes_), [](const unsigned char value) {
          return static_cast<std::byte>(value);
        });
  }

 private:
  std::vector<std::byte>* bytes_;
  std::size_t cap_;
  bool* output_incomplete_;
```

Both members are initialized from **references** in the ctor init list, so they are
non-null by construction; no arithmetic is performed on either, so no
`pro-bounds-pointer-arithmetic` surface is created.

**(b) `subprocess.cpp:220` — restore the value-initializer**, exactly as base
`probe.cpp:366` has it:

```cpp
  std::array<char, 8192> buffer{};
```

Noted honestly: this zero-fills 8 KiB per `drain_once` call, and `drain_once` runs in a
loop. That is **base parity, not a new cost** — the base carries the identical
initializer on the identical buffer. Hoisting the buffer out of the drain loop would be a
different change and is out of this scope.

**(c) `tests/test_subprocess.cpp` — three cases that make P2 falsifiable:**

```text
stdout-only truncation   stdout_cap=3, stderr_cap ample  -> EXPECT output_incomplete == true
stderr-only truncation   stderr_cap=3, stdout_cap ample  -> EXPECT output_incomplete == true
both caps ample          neither stream truncates        -> EXPECT output_incomplete == FALSE
```

The third is the discriminator and is the one that matters: without a must-be-NO case the
other two cannot tell a working flag from a stuck one. All three use the existing
`shell_request` helper (`stdout_cap`/`stderr_cap` default to 64 KiB) and assert the
retained bytes alongside the flag, so a cap that silently stops retaining is caught too.

## 5. The three required properties, and how each is proven

```text
(i)  CLEARS BOTH FIRING CHECKS
     avoid-const-or-ref-data-members flags reference and const-qualified DATA MEMBERS;
     after (a) ByteCapture has none - two raw non-owning pointers and a std::size_t.
     The uninitialized local at :220 is closed by (b), restoring base's own spelling.
     PROOF IS THE RUN, NOT THIS PARAGRAPH: green is established only by re-running the
     Linux tidy leg at the fixed head (below). I do not claim no OTHER check fires.

(ii) PRESERVES P2 (per-stream DETECTION, OR-accumulated into one monotonic flag)
     Preserved BY CONSTRUCTION: the capture still writes THROUGH to result.stdout_bytes /
     result.stderr_bytes, cap_ still per-instance, and the `||` accumulate is textually
     unchanged. No early-return path acquires a new obligation, because nothing is
     buffered anywhere new. And for the first time P2 is FALSIFIABLE, via the three
     cases in (c) - two must-be-YES and one must-be-NO.

(iii) NO CAPTURE-GROWTH REGRESSION
     76638a0 restored geometric growth by REMOVING `bytes_.reserve(bytes_.size()+retained)`,
     which forced an exact reallocation per write and defeated the vector's own doubling.
     This plan adds NO reserve, and leaves the sole growth path as back_inserter into a
     std::vector - i.e. the line 76638a0 deleted stays deleted. The Implementer must
     confirm no `reserve` re-enters ByteCapture::write; that is a grep, not a judgement.
```

## 6. Alternatives considered and rejected — stated, not silent

```text
reference_wrapper for both     REJECTED. Clean revert of d87d83a for bytes_, but
                               reference_wrapper<bool> forces
                               output_incomplete_.get() = output_incomplete_.get() || ...
                               I will not split the two members across two idioms.
                               Raised explicitly per 201613's instruction not to
                               reintroduce it silently. It is not being reintroduced.
ownership reshape (Utf8Capture) REJECTED FOR THIS PASS, registered as follow-up. It is the
                               better design and was named first at 201613, but it moves
                               the byte sinks out of SpawnResult and forces a transfer at
                               BOTH tail returns (:711, :726). A missed path silently DROPS
                               captured output: a compile-time analyzer red traded for a
                               runtime data-loss class, on a release-held product, during a
                               repair pass. Every repair pass breeds defects; this one
                               should breed as few as possible.
NOLINT suppression             NOT CONSIDERED as a fix. Suppressing a check that is
                               correctly firing on a real construct is how a gate stops
                               being able to fail.
```

## 7. Scope, and what happens after your review

The intended `SCOPE_DIFF` for the token that follows your approve — recorded here so the
review can grade the boundary, **not** as a grant:

```text
- src/core/support/subprocess.cpp -> in     (ByteCapture members + ctor + write; :220 buffer{})
- tests/test_subprocess.cpp       -> in     (three cases making P2 falsifiable)
```

Nothing else. No `probe.cpp`, no `.hpp` (the `SpawnResult` field is unchanged), no
`CMakeLists.txt`, no `.github`, no harness, no sealed or schema surface.

If you approve, I issue the bare `DISPATCH IMPL` token parented to **your PLAN-REVIEW**
(not to this PLAN, and not to `201613`), TO exactly one Implementer, with the `SCOPE_DIFF`
rows above plus a `SCOPE_ROW_EVIDENCE` row per IN path and `SCOPE_DIFF_RESULT: all-in`.

After the edit, the exit condition is the run, not the diff: **re-run the Linux tidy leg to
GREEN at the fixed head** in a disposable Ubuntu 24.04 `linux/amd64` container with the
pinned `clang-tidy-22` and the charter's descriptor lift, and re-run the macOS suite so the
three new cases are exercised on both hosts. `harness-selftest` is expected to stay red on
that Linux run and must NOT be read as a regression — it is the pre-existing flaky residual
ruled at `201613`, candidate-neutral by byte-identity.

## 8. What stays held

T2/T3/T4 and the T3 `compare.py` composition with its test obligation remain held until
T1's fix lands, per `201613`. The count-gate shape stays routed and the Linux
`nonzero_exit` claim stays owed; both ride T1's fixed head. The Arm-1 schema act remains
F+G-fenced and untouched.

## 9. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Nothing merged,
pushed, re-based, or PR-mutated; no remote CI, publication, deployment, or release. All
verification in this relay was read-only `git grep` / `git show` / `git log -L` against
committed blobs. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only only — `git grep output_incomplete a02a65b9` (no matches),
`git show d87d83a` / `git log -L 118,140:src/core/support/subprocess.cpp 76638a0` for
provenance, `git show 76638a0:` for the ByteCapture members, the `:220` buffer, the two
tail returns (`:711`, `:726`), `SpawnResult`, and `tests/test_subprocess.cpp`, and
`git rev-parse s4-matrix/arm1-t1` (= 76638a0, confirmed). NO ref created or moved, NO
source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this
relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree
delta at commit time; the shared checkout carries sibling-authored untracked paths,
preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-POINTER-SINKS-PLUS-BRACE-RESTORE-TWO-FRAMING-CORRECTIONS-20260820-202516.md` → TO `s4-matrix.implementer` for PLAN-REVIEW
- THIS RELAY CARRIES NO TOKEN and authorizes no keyboard; the bare `DISPATCH IMPL` follows only after your approve, parented to YOUR PLAN-REVIEW
- CHOSEN SHAPE: pointer-held sinks in `ByteCapture` (`std::vector<std::byte>* bytes_`, `bool* output_incomplete_`, both initialized from references so non-null by construction, no pointer arithmetic) + restore `std::array<char, 8192> buffer{}` at `:220` matching base `probe.cpp:366`
- CORRECTION 1 (byte-verified): there is NO per-stream `output_incomplete` field and never was — `git grep output_incomplete a02a65b9 -- src/ tests/` returns NOTHING; T1 ADDED one shared `SpawnResult` bool. The true property P2 is per-stream DETECTION OR-accumulated monotonically into that single flag. I will not plan to preserve a field that does not exist
- CORRECTION 2 (byte-verified): both firing members came from ONE commit, `d87d83a`, which reduced `bytes_` from `reference_wrapper` (tidy-clean at `ff37028`) to a plain `T&` and added `bool& output_incomplete_` — the same commit whose `reserve` hunk `76638a0` already reverted as the O(N²) defect
- THIRD FINDING, put IN SCOPE: `output_incomplete` is bound by ONE assertion (`test_subprocess.cpp:86`) that caps BOTH streams and has NO negative case, so a permanently-true flag passes today. Requiring stdout-only YES, stderr-only YES, and both-ample NO — the must-be-NO case is the discriminator without which the other two prove nothing
- REFERENCE_WRAPPER SAID OUT LOUD per `201613`: considered and REJECTED, not silently reintroduced (`reference_wrapper<bool>` forces `.get()` on both sides of the accumulate; will not split two members across two idioms)
- OWNERSHIP RESHAPE REJECTED FOR THIS PASS and registered as follow-up: it moves the sinks out of `SpawnResult` and forces a transfer at BOTH tail returns (`:711`, `:726`), so a missed path silently DROPS captured output — trading an analyzer red for a runtime data-loss class on a release-held product during a repair pass
- SCOPE (recorded for grading, NOT a grant): `src/core/support/subprocess.cpp` and `tests/test_subprocess.cpp` only; no `.hpp`, `probe.cpp`, `CMakeLists.txt`, `.github`, harness, sealed, or schema surface
- EXIT IS THE RUN NOT THE DIFF: re-run the Linux tidy leg GREEN at the fixed head (pinned clang-tidy-22, disposable Ubuntu 24.04 amd64, charter descriptor lift) plus the macOS suite for the three new cases; `harness-selftest` is EXPECTED to stay red there and must NOT be read as a regression
- T2/T3/T4 + `compare.py` composition stay held; count-gate shape stays routed; Linux `nonzero_exit` stays owed; schema F+G-fenced; merge ≠ push ≠ release; release hold ABSOLUTE
