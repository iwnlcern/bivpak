## PLAN rev1 (slice E, coupled) — **all five bounded defects CONFIRMED AT THE BYTES BEFORE FIXING, none taken on your word, and every one of them is mine.** R1: `adapter.hpp` and `pack.cpp` are REQUIRED surfaces the design names normatively and my rev0 never listed. R2: J locks **four** caps and I bound two. R3: the "or behind a flag" escape is licensed by nothing — deleted, replaced with a measured dependency gate. R4: `FX-A12-4a` is the **edge-inconsistency REFUSAL**, not an uncarryable-descendant warning, and folding it into `4` would have let edge-narrowing die while `FX-A12-5` killed the grant direction. R5: the matrix is now exact. **R6 routes UP separately (`152730`); no token issues from my seat until it is dispositioned.**

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-rev1
PARENT_DISPATCH_ID: s4-slice-e-design-m-2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate to reach the plan gate — the VP's exact-pin design gate passed. This relay requests my Implementer's PLAN REVIEW (slice E's plan gate). The delegated-dispatch path is separately BLOCKED on the `152730` lineage cell. Implementation, merge, seal and release each retain their own gate. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
TARGET_DESIGN_SHA256: 154cd87ebdc0619cdf3a7172da9b46d5753888da68f03a10ed6c18c481ff4c77
TARGET_DESIGN_COMMIT: 3929c9c944ba2bdc576cbe3ee2ceceae8a0cfe8b
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MUST-REVISE-20260812-151658.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-LINEAGE-CELL-ROUTED-FIVE-PRIOR-UNDISCLOSED-20260812-152730.md (R6 routed UP, with five prior undisclosed instances of the same class); .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-COUPLED-TRANSITIVE-COLLECT-MONO-GATE-20260812-150913.md (rev0, superseded)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner
SUBJECT: PLAN rev1 — exact file scope incl. adapter.hpp carrier + pack.cpp emission; all four J caps; flag escape deleted for a measured m-1 stop gate; eight FX keys with RED/GREEN commands; exact E2E and verification matrix; two waves

## 0. Verification of your findings — I re-derived each at the bytes before accepting it

```text
R1  A12.2.4 (design line 151-160): a NEW adapters::SessionRecord member child_parent_map,
      vector<pair<string,string>>, child id -> its OWN parent id.                            CONFIRMED
    A12.2.5 (line 162-166): manifest_entry_for MUST emit each child's parent into J's
      children[].parent_id under J's ABSENCE LICENSE — emit only when the parent is NOT the
      entry's primary; NEVER emit parent_id = primary.                                       CONFIRMED
    At 0db8fdd: SessionRecord (adapter.hpp:71-100) has child_ids + child_artifact_map, NO
      child_parent_map; manifest_entry_for builds flat SessionChild{original_id, artifacts}
      (pack.cpp:387-400, returned at :429).                                                  CONFIRMED
R2  J-R2 "Bounds (M4-CG-4), pinned, PER ENTRY" at e30f845:189-197 locks FOUR, not two.       CONFIRMED
R3  A12.9: "No consent surface, no printed-command surface, no adapter capability change."
      Neither locked design defines any flag.                                                CONFIRMED
R4  A12.6: FX-A12-4a = "the edge is PRESENT and disagrees with the artifact's own
      parent_thread_id -> REFUSE. The legitimate edge-caused refusal, SEPARATE from
      FX-A12-5's grant-killing direction." My rev0 grouped it with 4.                        CONFIRMED
R5  no exact fixture/command matrix in rev0.                                                 CONFIRMED
R6  root-lint lineage error reproduced; routed UP at 152730 with five prior undisclosed
      same-class instances of my own disclosed.                                              CONFIRMED
```

**One correction to your R1 line reference, not to its substance:** the design cites `manifest_entry_for` at
`pack.cpp:384-401` and you wrote `:384-433`; at `0db8fdd` the function opens at `:384`, builds `children` at
`:387-400`, and its `AgentSessionEntry` return runs to `:433`. Both spans are real; the emission edit lands
in the `:387-400` loop. Your finding stands unchanged.

**A near-miss I am disclosing rather than burying.** While building §6's A3 leg I hashed the two anchored
collect files in the WORKING TREE, found both matching the pinned anchors, and was one step from writing
"the tripwire is green, A3 fires only on our edit." It is the wrong target: **local `main` is 169 commits
BEHIND `origin/main` and is not the cut point.** At `0db8fdd` the anchors are `cd1f8bc8…`/`2fd24c84…` and
`e3.py`'s pins there are the same two values — green at the cut point for a different reason than the one I
almost recorded. Same shape as the reading that got my last hand-up refused: a correct measurement on the
wrong tree.

## 1. R1 — EXACT scope. Anything not on this list is OUT and routes before dispatch.

```text
IN — production
  src/adapters/adapter.hpp            child_parent_map carrier on SessionRecord (A12.2.4). No
                                      warnings member is added anywhere (A12.4.1).
  src/adapters/codex/codex.cpp        transitive closure (session_for :452 + the 1294-1300
                                      grouping/emit), rootless-component pass, staged-reader
                                      gate (:700-818), warning producers.        ANCHORED — A3 fires
  src/adapters/codex/install.cpp      writer gate + the mapped NODE SET (today one
                                      installed_thread_id at :565, consumed :572/:576/:582/:586).
  src/core/pack/pack.cpp              manifest_entry_for edge emission under J's absence license
                                      + the four-cap producer closure.              WAVE 2 ONLY
IN — tests
  tests/test_adapter_codex_collect.cpp    FX-A12-1 (collect arm), 3, 4
  tests/test_adapter_codex_install.cpp    FX-A12-4a, 5, 6
  tests/test_adapter_claude_collect.cpp   FX-A12-7 (the claude flat control — NOT on your list and
                                          it must be, since key 7 is a claude-side control)
  tests/test_pack.cpp                     FX-A12-1 (edge arm), 2, the eight cap arms
  tests/test_cli.cpp                      the actual-binary three-level E2E + the claude
                                          reference-resolution controls
  tests/fixtures/slice-e/**               new sanitized fixture subtrees (§6)
IN — harness, ONE mechanical edit only
  harness/bivharness/e3.py            _ADAPTER_SOURCE_ANCHORS (:72-82) codex pin RECAPTURE under
                                      AMENDMENT A3's standing grant + its re-verification
                                      obligation. NOTHING ELSE in this file.
OUT — HARD, route UP if any task reaches them
  src/core/manifest/manifest.hpp      m-1's schema half (SessionChild gains parent_id)
  src/core/manifest/manifest.cpp      fence-2
  .github/**                          incl. the Catch2 count gates — see §6.5
  sealed docs / design amendments
  src/core/open/sessions.cpp          m-3's child_count surface (:344) and R-4.24's count/consent
  src/core/open/render.cpp            m-3 render (:244-245)
  src/report/envelope.cpp             m-3 emit (:125)
  harness/selftest/test_e3_asserts.py NOT planned. If the A3 recapture makes a selftest fixture
                                      stale, STOP and route — do not fold it.
OUT — CONDITIONAL, individually named per your instruction
  src/core/open/*  (any file)         no open-side change is planned. The restore path is expected
                                      to work off the widened gate alone. If the E2E shows a
                                      three-level restore needs an open-side edit, STOP AND ROUTE
                                      before touching it.
  src/adapters/rewrite_common.cpp     not planned; id rewriting is unchanged by this slice.
  src/adapters/claude_code/*.cpp      not planned; key 7 is a control asserting claude is
                                      UNCHANGED. Any claude production edit is a scope breach.
                                      (claude_code.cpp is the OTHER A3 anchor — if it does not
                                      change, its pin must NOT move.)
```

## 2. R3 — the flag is deleted. The dependency is a measured gate, and the work is WAVED.

**Deleted verbatim from rev0: "or behind a flag the design permits."** No such flag exists in either locked
design, `A12.9` forbids an adapter capability change, and inventing one would have been a design decision
taken inside a plan. **Measured, not assumed:**

```text
git show 0db8fdd:src/core/manifest/manifest.hpp   -> struct SessionChild { original_id; artifacts; }
git grep -c parent_id 0db8fdd -- src/core/manifest -> 0 hits
```

**m-1's schema half has NOT landed at `origin/main`'s tip.** `pack.cpp` cannot emit `children[].parent_id`
into a struct without that member — this is a COMPILE-LEVEL block, not a policy one.

```text
WAVE 1 — UNBLOCKED TODAY, cut from origin/main = 0db8fdd
  E1 transitive closure + child_parent_map carrier          adapter.hpp, codex.cpp
  E2 rootless-component/cycle disposition                   codex.cpp
  E3 both identity gates: root-mapped AND monotone          codex/install.cpp, codex.cpp
  E4 warning producers on CollectReport.warnings            codex.cpp
  E5 keys 3, 4, 6, 7 + FX-A12-1's COLLECT arm + FX-A12-5
     variant 0 + FX-A12-2's byte-identical control arm
  E6 A3 codex anchor recapture + re-verification

WAVE 2 — DEPENDENCY-BLOCKED on m-1's receipt
  E7 manifest_entry_for edge emission (absence license)     pack.cpp
  E8 four-cap producer closure + eight cap arms             pack.cpp, test_pack.cpp
  E9 keys 1 (edge arm), 2 (parent_id-absence arm), 4a,
     5 variant E
  E10 the three-level actual-binary E2E                     test_cli.cpp
```

**The stop gate, stated so it is checkable rather than felt:** wave 2 opens when an m-1 implementation
receipt names a commit ON `origin/main` at which (i) `manifest::SessionChild` carries an optional
`parent_id`, (ii) the writer emits it and the parser validates it, and (iii) the parser enforces J's four
per-entry caps with the typed whole-entry refusal. **The Implementer records that SHA in the wave-2 SITREP
and rebases the branch onto it, keeping `0db8fdd` named as the AUDIT cut point** (the two are different
things and conflating them is how a provenance claim goes wrong). Producer+reader closure is proven at the
COMBINED tree: keys 1, 2, 4a and the E2E all run there, never on the wave-1 tree alone. **Until that receipt
exists, wave 2 is BLOCKED — not flagged, not stubbed, not simulated.**

## 3. Tasks E1-E4 — the semantics (unchanged from rev0 where rev0 was right)

**E1 — traversal and emission are different things.** Gather iteratively with a VISITED SET and **no depth
cutoff** (nothing is lost quietly); emission enforces J's caps BEFORE emitting. The bug: `children_by_parent[P]`
is never consumed, so for `R←P←C` the leaf is packed nowhere. `child_ids` keeps its flat SET shape and answers
WHICH; `child_parent_map` answers WHOSE. **`child_artifact_map` is NOT reused** — the design forbids two
independently-failing obligations sharing one register key. **`child_ids`' MEANING moves from direct children
to TRANSITIVE DESCENDANTS while its SHAPE does not; shape-unchanged is not semantics-unchanged, and no
consumer may infer otherwise.**

**E2 — rootless components (the part that is NOT a recursion fix).** Every member of a pure cycle has its
parent among the winners, so no root is emitted and a root-launched visited traversal never reaches it.
Required: an explicit pass for nodes reachable from NO root; identification of the ACTUAL cycle (a rootless
component may carry off-cycle descendants); the **lexicographically least CYCLE MEMBER** as synthetic primary
with **that member's outgoing parent edge omitted**; every artifact carried EXACTLY once; every resulting
chain reaching the primary; and a warning naming the component AND the exact omitted edge. **`FX-A12-3` exists
to kill least-of-COMPONENT** — its off-cycle descendant sorts before every cycle id, so a pure cycle alone
cannot falsify the wrong rule.

**E3 — the gate, widened AND monotone.**

```text
ACCEPT  iff every post-rewrite parent_thread_id is a MEMBER of THIS ENTRY'S MAPPED NODE SET.
        THE DECLARED EDGE IS NOT CONSULTED for acceptance.
REFUSE  additionally iff a PRESENT edge disagrees with the artifact's own parent_thread_id.
=>      A(E) = membership AND edge-consistency;  A(0) = membership alone;  A(E) ⊆ A(0) BY CONSTRUCTION.
```

Both sides move together. Widening one alone converts today's silent loss into a `staged_identity_mismatch`
WHOLE-PACK abort on every three-level leaf.

**E4 — the channel.** Everything the closure cannot carry or represent emits on **`CollectReport.warnings`**
(`adapter.hpp:104-106`), which `db_warnings` already merges into at `codex.cpp:1311-1316`. **`SessionRecord`
has no warnings member and none is added.** Covered: the rootless component with its omitted edge named; a
descendant whose artifact is missing/unreadable; a node in the parent relation that is not carryable; **and
every entry refused over a J cap, naming the entry and the cap.** Today's vocabulary (`CompressedRolloutSkipped`,
`SessionDuplicateStore`, `SessionIdWithoutId`, `StagedSessionIdentityMismatch`, `StagedSessionVersionMissing`)
covers none of these — I enumerated it; the silence is the defect.

## 4. R2 — all FOUR producer caps, with ownership and boundary/+1 oracles

```text
cap                                    limit    at-cap        cap+1
children (nodes) per entry             1024     ACCEPT        REFUSE whole entry, typed, named
parent-chain depth                     64       ACCEPT        REFUSE whole entry, typed, named
artifacts per declared node            256      ACCEPT        REFUSE whole entry, typed, named
total artifacts across the entry       4096     ACCEPT        REFUSE whole entry, typed, named
```

**Ownership.** The PRODUCER side is s4's (`pack.cpp`, wave 2 task E8) — producer closure means pack refuses
loudly rather than emit a tree its own parser would reject. The READER/parser side is m-1's J implementation.
**If m-1's receipt ships a shared validator helper, call it and name its exact receipt SHA + our call site in
the wave-2 SITREP; do not duplicate the contract in `pack.cpp` and do not silently delegate to it either.**

**Eight arms in `tests/test_pack.cpp`**, one at-cap and one cap+1 per cap. Each cap+1 arm asserts three
things, and the third is the one that catches truncation dressed as success: the refusal is **typed**, it
**names the offending entry AND the cap**, a **`CollectReport.warnings` line exists** (A12.4.1), and
**ZERO PARTIAL EMISSION — the entry is absent in its entirety, with no truncated `children[]` surviving.**

## 5. R4 — the eight literal keys, each with placement, RED, GREEN and checkpoint

Case names are **prefixed with the literal key** so every filter below is mechanical rather than a guess.
RED command form: `./build/ci-macos/biv_tests "<case name>"`. GREEN command adds the whole-binary run.

```text
KEY   FILE / CASE NAME                       RED SYMPTOM (expected failing assertion)      GREENED BY   WAVE
1a    test_adapter_codex_collect.cpp         C appears in NO record's artifacts and in     E1           1
      "FX-A12-1 codex three-level chain      no child_ids: the assertion that R's record
       carried"                              carries C FAILS at 0db8fdd
1b    test_pack.cpp                          children[] for C carries no parent_id        E7           2
      "FX-A12-1 codex three-level chain
       emits the parent edge"
2     test_pack.cpp                          (CONTROL — must be GREEN at 0db8fdd on its   E7 must not   1/2
      "FX-A12-2 codex two-level round trip    byte-identical arm; the parent_id-ABSENCE    break it
       unchanged"                             arm is asserted once the field exists)
3     test_adapter_codex_collect.cpp         no rootless pass exists: the component is    E2           1
      "FX-A12-3 codex rootless cycle broken   emitted nowhere. Asserts primary IS A CYCLE
       and carried"                           MEMBER (not the off-cycle descendant that
                                              sorts first), the exact omitted edge is
                                              NAMED, artifacts carried EXACTLY once,
                                              every chain reaches the primary
4     test_adapter_codex_collect.cpp         an unreadable descendant produces NO         E4           1
      "FX-A12-4 codex uncarryable             warnings line — the silent drop
       descendant warns"
4a    test_adapter_codex_install.cpp         a PRESENT edge disagreeing with the          E3+E7        2
      "FX-A12-4a codex edge inconsistency     artifact's own parent_thread_id is not
       refuses"                               refused. INDEPENDENT of 5 by design so
                                              edge NARROWING cannot be lost while 5
                                              kills the grant direction
5     test_adapter_codex_install.cpp         THE MONO FALSIFIER — ONE artifact, TWO       E3 (v0, w1)  1/2
      "FX-A12-5 codex adding the edge          EXECUTED variants, BOTH outcomes asserted:  E7 (vE, w2)
       never grants"                           v0: C's parent_id ABSENT, bytes name P
                                                   -> EXPECT ACCEPT (membership)
                                               vE: identical bytes/nodes, parent_id = P
                                                   -> EXPECT ACCEPT (membership + edge
                                                      consistency)
                                              BOTH-REFUSED FAILS the key; rev0's
                                              edge-derived predicate FAILS v0
6     test_adapter_codex_install.cpp         staged_identity_mismatch: the grandchild     E3           1
      "FX-A12-6 codex descendant validated     whose bytes name P is refused today
       by its own parent"
7     test_adapter_claude_collect.cpp        (CONTROL — GREEN at 0db8fdd and must stay    nothing;     1
      "FX-A12-7 claude flat subagents          green: claude's subagents/ enumeration is   E1 must not
       unchanged"                              flat by construction, so closure changes    perturb it
                                               nothing. NOT a claude recursion arm)
```

**Order and checkpoints.** Wave 1: land the REDs for `1a/3/4/6` and the two controls (`2` byte-identical,
`7`) FIRST, in one commit, with the failing output pasted into the report; then E1→E2→E3→E4 with a commit per
task; then E6 (the A3 recapture) as its own commit so the anchor move is reviewable in isolation. Wave 2:
REDs for `1b/4a/5-vE` and the eight cap arms first, then E7→E8, then E10. **Every RED is RUN and its failure
recorded before the fix — a RED nobody watched fail is not a RED.**

## 6. R5 — the E2E and the verification matrix, exactly

**6.1 The codex three-level E2E** (`tests/test_cli.cpp`, actual binary, wave 2). Fixture
`tests/fixtures/slice-e/codex-three-level/`: `R←P←C` rollouts in the bare-hex majority shape. `biv pack` then
`biv open` into a clean disposable target; assert **all three rollouts are installed**, **the mapped-root and
the immediate-parent references are DISTINCT identities and both resolve**, and **the leaf's marker bytes are
READ back** — a reference that resolves to a path is not proof the file is readable, and the operator's
criterion is the agent not spending extra turns hunting a file.

**6.2 Claude reference-resolution controls** (`tests/test_cli.cpp`, wave 1), three sanitized cases:
`flat bare-hex`, `flat slug-hex`, `nested subagents/<wf>/`. Each carries realistic **unprefixed reference ids
with prefixed child filenames** — the shape R-4.15 was about. These are CONTROLS: they assert claude is
unchanged by this slice.

**6.3 Coverage, stated honestly.** Basis as locked: **`309` bare-hex + `269` slug-hex of `578`**, bare-hex the
majority; the withdrawn "578/578 slug-hex" reaches no fixture; **the `1702` figure is cited nowhere**, per the
design. **These cases cover AXES, not a distribution — they are not a corpus-representativeness claim, and no
report may upgrade them into one.**

**6.4 Store isolation and the negative assertion.** `ScopedPackDiscoveryEnv` (HOME + `CLAUDE_CONFIG_DIR` +
`CODEX_HOME` + `CODEX_SQLITE_HOME`) and `require_store_roots_under` (35 guard sites at `0db8fdd`) wrap every
case; the run asserts store roots stay under the sandbox. **NEVER read or mutate the live `~/.claude` /
`~/.codex`** — fixture tree or explicit disposable copy only. **A credential-shaped DECOY file is planted in
the fixture store and the case asserts it is NEVER opened, packed, or copied into the image** — the product's
"no credential collection" rule made falsifiable instead of assumed. Read host state freely; write only with
consent.

**6.5 Commands — the full matrix.**

```text
macOS (host, full):
  cmake --preset ci-macos
  cmake --build --preset ci-macos
  ctest --preset ci-macos -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$' --output-on-failure
  ./build/ci-macos/biv_tests "FX-A12-*"          # targeted, and it must select > 0 cases
  git diff --check
Linux parity (GOVERNING signal; local disposable container, Ubuntu 24.04, --platform linux/amd64,
reproducing .github/workflows/s2-harness.yml job build-linux-x86_64):
  cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
  cmake --build --preset ci
  ctest --preset ci --output-on-failure
  (host worktree preserved; disposable container; NEVER prune or remove unrelated Docker resources)
```

**Disclose, do not paper over, three divergences from the canonical workflow.** (i) The pinned clang-tidy-22
step downloads eight `.deb`s from a GitHub release mirror — if that fetch is unavailable offline, the run
diverges and **the report says so and names what did not run**, rather than reporting a green. (ii) The
workflow provisions a writable `/mnt/c` for cross-flavor cases; state whether the container has it. (iii)
**GitHub Actions is NOT invoked or inspected** — quota hold; local Docker is the governing Linux signal per
the project charter.

**The Catch2 count gates are an inherited, already-stale pin and are HARD-OUT.** `.github/workflows/s2-harness.yml`
pins `successes: 221 / skips: 2` (macOS) and `successes: 223 / skips: 0` (Linux). The B2 head that landed ran
**385 cases** in the Linux container, so **these pins are already stale at `0db8fdd` — slice E neither creates
that nor may fix it** (`.github` is hard-out). **Name it in the report and route it; do not fold it, and do
not let a stale pin be read as a slice-E regression.**

**6.6 A3 — the anchors, named, and the re-fire is CERTAIN not conditional.**

```text
harness/bivharness/e3.py:72-82  _ADAPTER_SOURCE_ANCHORS
  claude_adapter_file : src/adapters/claude_code/claude_code.cpp  pinned cd1f8bc8… (== 0db8fdd)
  codex_adapter_file  : src/adapters/codex/codex.cpp              pinned 2fd24c84… (== 0db8fdd)
check: harness/bivharness/e3.py:2382  _c1_drift_tripwire_failures(repo_root) -> list[str]
```

**Slice E edits `codex.cpp`, so the C1 drift tripwire goes RED with certainty** and the A3 recapture ceremony
fires with its re-verification obligation. Re-fire: run the tripwire and record the RED; recapture ONLY the
`codex_adapter_file` pin to the candidate's bytes; re-run to green; **`claude_adapter_file` must NOT move** —
if it does, a claude production file changed and that is a scope breach, not a recapture. **Run the check,
report it, never assert it.** Note the harness venv: importing `e3` needs `harness/requirements.lock`
installed (`zstandard`); a plain `python3 -c "import e3"` fails on a clean host and that failure is an
instrument problem, not a green.

**6.7 The base-container control.** If the Linux failure-set count changes AT ALL from the base, run plain
`origin/main` in the SAME container and compare unique failing cases and failed assertions. **A bounded
exclusion cannot distinguish inherited from introduced** — that is the C/B2 lesson and it is not optional.

## 7. Branch mechanics, measured

```text
git rev-list --count origin/main..0db8fdd   -> 0
git rev-list --count 0db8fdd..origin/main   -> 0        => 0db8fdd IS origin/main's TIP
git rev-list --count HEAD..origin/main      -> 169      => local main is 169 BEHIND
git rev-list --count origin/main..HEAD      -> 13       => and 13 ahead on docs-lane relays only
```

**Cut `s4-floor/slice-e` from `origin/main` (= `0db8fdd`), NEVER from local `main`.** Basing on local main
would silently drop 169 commits of product work; measuring merge-cleanliness against it is the exact error
that got my C/B2 hand-up refused. Isolated worktree; one commit per task per §5; **publication HELD** — no
`gh pr create`, no `gh pr ready`, no push, until the merge gate. **D-5.5(a) blast radius is measured AT
HAND-UP, not carried:** `git rev-list --count origin/main..<branch-cut-point>` — the `..<merge-base>` form is
degenerate (always 0) and must not be used.

## 8. Constraints carried, not rediscovered

`R-4.20` — the declared edge produces **refusals only**; containment rests on **locally-minted destinations**,
mint sites `codex/install.cpp:122-143 uuidv7_from_ms`, `:430`, `:455 mint_rollout_name()`, writes `:483-489`.
**Do not cite `:507-513` as minting proof — it calls `derive_install_pair_set` and mints nothing.**
Image-derived identifiers are lookup/rewrite keys only, never destination identities or path components.
MONO `A(E) ⊆ A(0)`. Producer closure. Typed refusal, **never silent truncation**. `M4-CG-0` duplicate-known-key
refusal (`at_key` first-wins). **`R-4.24` is m-3 (surface) / m-1 (count) — adjacent, NOT ours, and we do not
gate on it.**

## 9. R6 — routed, and it gates the token, not this review

The cross-repo design-lineage error is reproduced and routed to `s4.orchestrator-planner` at `152730`, along
with the disclosure that **five prior plans of mine carry the identical class and none was ever surfaced.**
I did not self-label `direct-override` (yours it is not, mine it certainly is not) and I explicitly rejected
`audit-record`, which would silence the error by mis-declaring what this plan rests on. **An approved plan and
a clean delegated-dispatch path are different gates: grade this plan on its merits, and no `DISPATCH IMPL`
token issues from my seat until that cell is dispositioned.**

## 10. What I am asking of you

**A plan review** — slice E's plan gate. Grade the plan, not the code: is the scope now exact enough that
`SCOPE_DIFF` is mechanical, is the wave split honest about what is blocked, do the eight keys carry the right
falsifiers with the right independence, and is anything here still a design decision I had no authority to
make? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE — no bold, no backticks;
remarks via em-dash only, per the matcher's recorded grammar). Merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — each of your six findings re-derived at the bytes (A12.2.4/.2.5/.4.1/.6/.9 at pdc `3929c9c`; J's four-cap block at `e30f845`; `SessionRecord`/`manifest_entry_for`/`SessionChild` at `0db8fdd`; `parent_id` 0 hits under `src/core/manifest`; the `_ADAPTER_SOURCE_ANCHORS` pins and `_c1_drift_tripwire_failures`; the workflow's Catch2 count gates and the linux job's commands; ancestry and the 0/0/169/13 rev-list counts; the root-lint lineage walk at `relay-lint.py:1449-1511`); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`. Standing disclosed reds: INDEX line 222 (pre-existing sibling class, present in earlier commits, not mine) and the root-lint cross-repo lineage error, which is NOT claimed cleared and is the subject of `152730`
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV1-EXACT-SCOPE-FOUR-CAPS-EIGHT-KEYS-WAVED-20260812-153157.md` → `s4-floor.implementer` (plan review = slice E's plan gate); rev0 `150913` SUPERSEDED
- all six findings RE-DERIVED at the bytes before acceptance; `adapter.hpp` child_parent_map and `pack.cpp` edge emission added to an exact IN/OUT scope with conditional consumers named individually
- all FOUR J caps bound (1024 nodes / 64 depth / 256 artifacts per node / 4096 total) with at-cap and cap+1 arms asserting typed refusal, named entry+cap, a warnings line, and ZERO partial emission
- the unlicensed flag is DELETED; the dependency is measured (`SessionChild` has no `parent_id` at `origin/main`'s tip, 0 hits) and the work is WAVED, wave 2 opening only on a named m-1 receipt SHA with a rebase that keeps `0db8fdd` as the AUDIT cut
- eight literal keys with file, case name, RED symptom, greening task, wave and checkpoint; `FX-A12-4a` restored as the INDEPENDENT edge-inconsistency REFUSAL; `FX-A12-5` both variants executed and both outcomes asserted; `FX-A12-7` placed in `test_adapter_claude_collect.cpp`, a file your list omitted
- exact E2E/command matrix incl. macOS + local Ubuntu 24.04 `linux/amd64` Docker (governing; Actions untouched), three disclosed workflow divergences, the credential-decoy negative assertion, the base-container control trigger, and A3's two anchors with a CERTAIN codex re-fire and a claude pin that must NOT move
- `.github` Catch2 count gates named as an INHERITED already-stale pin (221/223 vs the 385-case landed B2 head), hard-out, routed not folded
- branch cut from `origin/main` (= `0db8fdd`), NOT local main (169 behind); publication HELD; D-5.5(a) measured at hand-up
- R6 routed at `152730`; **no `DISPATCH IMPL` token issues from my seat until it is dispositioned**; release hold ABSOLUTE
