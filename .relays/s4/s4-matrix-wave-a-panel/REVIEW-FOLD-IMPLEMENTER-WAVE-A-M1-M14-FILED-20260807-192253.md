## REVIEW-FOLD — Wave-A M1-M14 folded at cumulative product head c52bcca; targeted replacement-head panel requested

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-PLANNER-DISPATCH-20260807-162054.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this filing — the pair Planner's targeted panel at the replacement head is next; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — M1-M14 and bounded cheap fold-ins complete at cumulative product head c52bcca; local E2 green on every Darwin-applicable row; one final cumulative CI publication and targeted panel requested; merge/release held

FOLD_SCOPE:
- CMakeLists.txt -> in
- src/core/support/subprocess.hpp -> in
- src/core/support/subprocess.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/git.hpp -> in
- src/core/repo/git.cpp -> in
- src/core/repo/git_exec.hpp -> in
- src/core/repo/git_exec.cpp -> in
- src/core/repo/discover.cpp -> in
- src/core/repo/classify.hpp -> in
- src/core/repo/classify.cpp -> in
- src/core/repo/eligibility.hpp -> in
- src/core/repo/eligibility.cpp -> in
- src/core/repo/capture.hpp -> in
- src/core/repo/capture.cpp -> in
- src/core/repo/restore.hpp -> in
- src/core/repo/restore.cpp -> in
- tests/support/temp_dir.hpp -> in
- tests/test_probe.cpp -> in
- tests/test_subprocess.cpp -> in
- tests/test_repo_git.cpp -> in
- tests/test_repo_engine.cpp -> in
- harness/bivharness/compare.py -> in
- harness/bivharness/fixtures.py -> in
- harness/tolerance/tolerance-v1.json -> in
- harness/selftest/test_compare.py -> in
- harness/selftest/test_fixtures.py -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

DONE_WITH_CONCERNS

The fold is complete as four review commits on the original linear T1 -> T2 -> T3 ->
T4 topology, with cumulative product head
`c52bcca1f268b9d8ac6e414cd3874a5ba9829601`:

- T1 `bbe824a2b4c27e125a1c7882c24e3d7c98cb5e3b` — subprocess capture and shared test fixtures;
- T2 `c817a455107a91651f4bd919dac66658fe6156e2` — restore-scoped Git isolation and hostile-config coverage;
- T3 `2676fc6` — declared Git tolerance rows and harness timeout/lookup hardening;
- T4 `c52bcca1f268b9d8ac6e414cd3874a5ba9829601` — shared Git execution policy and the engine findings.

The pre-edit scope artifact is
`.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-SCOPE-IMPLEMENTER-20260807-182355.md`
at ancestor commit `6a0b3f0`. It was written, exact-file linted, INDEX-appended, and
committed before the first product/test/harness fold edit. The cumulative diff contains
no path outside that all-IN declaration.

## Required finding dispositions

- **M1 folded:** global-config isolation is restore-side only, so classification sees
  user global excludes. Repo-local hooks, credential helper, and SSH command are
  neutralized through injected config. Generic calls pin `GIT_PROTOCOL_FROM_USER=0`;
  explicitly intended top-level bundle/remote transports opt in at their call sites.
  No URL/host policy was introduced.
- **M2 folded:** path-like values use the operand channel. Object names, refs, and
  manifest-relative paths are validated at their type boundary before interpolation.
- **M3 folded:** relpath, bundle, and local-refs bundle members are normalized and
  containment-checked before restore performs a mkdir or spawns Git. Hostile members
  have pre-spawn tests.
- **M4 folded:** metadata/local, network, and bundle call classes have separate
  budgets; budget expiration maps to `git_budget_expired`, distinct from Git process
  failure. Incomplete capped output fails closed for Git.
- **M5 folded:** remote tips are de-duplicated and checked once, then ancestry is
  evaluated once per ref rather than once per ref-tip pair. The 4,096-tip ceiling has
  an explicit honest-unknown/full result and a 4,097-tip test.
- **M6 folded:** the classification-time promisor bit is carried on `RepoEntry`.
  Classification, eligibility, and capture use one promisor policy and one
  missing-object predicate; request-trace tests prove `GIT_NO_LAZY_FETCH=1` on every
  promisor Git invocation.
- **M7 folded:** restore returns per-ref failed rows with details. Verification
  mismatch is a failed repo row plus `repo-verify-divergence`, retaining warning-class
  exit 2 instead of becoming `RepoRestoreFailed` exit 4.
- **M8 folded:** bundle create/verify process failures map to
  `GitInvocationFailed` facts carrying repo, operation, and exit code. Only a proven
  missing-object failure maps to promisor unavailability. A real neither-route
  precheck emits `RefUncapturable` with repo/ref facts.
- **M9 folded:** `git-administration: semantic-only` and
  `git-tracked-file-mtime: ignore-checkout` are declared tolerance rows consumed by
  the comparator. Row-removal RED tests prove both policies are live.
- **M10 folded:** tests now falsify parent environment passthrough, exercise a real
  zero-ref `classify()` result, and saturate both stdout and stderr. General subprocess
  output exposes `output_incomplete`; probe remains prefix-capable while Git fails
  closed.
- **M11 folded:** shared `git_exec.{hpp,cpp}` owns the duplicated execution helpers,
  validation, missing-object mapping, and the single penumbra snapshot implementation.
- **M12 folded:** restore filesystem operations use nonthrowing `error_code`
  overloads and preserve typed restore errors.
- **M13 folded:** one noncopyable `tests/support/temp_dir.hpp` replaces the test-local
  implementations and uses a collision-resistant id.
- **M14 folded to conformance:** root repo `.` materializes directly inside the
  existing partial-dir staging boundary. No `repo-materialize-*` second mechanism or
  per-child rename remains; a slot-collision test guards the absence of that helper.

The bounded cheap fold-ins used only already-open surfaces: duplicate
`tests/test_probe.cpp` compilation was removed, capture uses bulk insertion, harness Git
lookups are cached with explicit timeouts, engine errors are array-driven, and the
ordered-gate tests were extended. No optional URL allowlist, unrelated product surface,
Wave B/C/D path, schema act, merge, or release work was taken.

## Ruled, byte-answered, and held items

- **Security #1 allowlist half — ANSWERED-BY-SEALED-RECORD, unchanged:** the finding's
  transport-policy argument is not folded. Operator addendum-D lines 26-28 remove the
  SR-M14 URL allowlist/host floor and make networked open Git-clone-grade trust:
  `../pdc/master/domains/m-1-format-engine/design/2026-07-04-ADDENDUM-D-offline-and-n3.md:26-28`.
  Only the separately authorized process-hygiene half was implemented.
- **Correctness Q1 / recovery fetch — folded out:** the source-repo fetch was removed.
  Unknown advertised objects remain honest `unknown-tip` and force full capture. This
  follows the read-only tips-union ruling and the source-write prohibition at addendum-C
  lines 228-240.
- **Correctness Q2 / reset — folded:** `reset --hard` was replaced by branch/detached
  checkout behavior. Sealed addendum-A lines 93-100 requires checked-out-branch
  correction through symbolic-ref/checkout or detach.
- **Correctness Q3 / nested scope — no change:** D2.2 step 1 explicitly makes repo-set
  shape a discovery-time predicate before per-repo classification
  (`2026-08-05-s4-matrix-arm1-design.md:74-76`), so the workspace-wide fence remains.
- **Correctness Q4 / zero-ref capture_mode — HELD and unblessed:** the current value is
  unchanged and no test asserts it as correct. The named inexpressible cell remains
  routed in `SITREP-PLANNER-CAPTUREMODE-CELL-ROUTED-20260807-162054.md`.

## Fresh local verification

After the final code change, this exact cumulative product head passed:

`git diff --check && cmake --build --preset dev -j8 && ctest --preset dev -E '^safety-hardening$' --output-on-failure`

Result: build success and 17/17 applicable CTest rows passed, including 32/32 repo-engine
test cases, the complete harness selftest, harness E2, and Werror. The harness tolerance
focused suite separately passed 33/33 tests. The full unfiltered dev run had the same
functional greens and one platform-prerequisite red only: Linux ELF hardening requires
`readelf`, which is unavailable on Darwin. ASan, UBSan, fuzz smoke, and pinned
clang-tidy are configured skips in this macOS preset; no unsupported analyzer or Linux
hardening verdict is claimed.

Per the operator's current CI direction, no GitHub workflow was triggered during the
fold. The cumulative replacement branch will be published once after this filing; its
single final-head CI run is validation evidence to observe, not merge authority.

## Requested next action and holds

Planner TARGETED panel is requested against the final published head of draft PR #20,
sized to the cumulative `66250856..c52bcca` fold delta and these M1-M14 dispositions.
The panel record must bind the exact replacement head before the candidate can return to
the bar. Intermediate PRs remain unmerged; Waves B/C/D remain F-fenced. No merge or
release action is taken or authorized.

ACTIONS_GIT_REF: review commits `bbe824a2b4c27e125a1c7882c24e3d7c98cb5e3b`, `c817a455107a91651f4bd919dac66658fe6156e2`, `2676fc6`, and cumulative product head `c52bcca1f268b9d8ac6e414cd3874a5ba9829601`; pre-edit scope commit `6a0b3f0`; this relay and append-only INDEX row ride the final cumulative filing commit whose SHA lands in repository history after filing; one guarded force-with-lease publication to PR #20 follows, with no merge/release
FINAL_GIT_STATUS_SHORT: cumulative T4 worktree clean at c52bcca before this relay and INDEX append; origin/s4-matrix/arm1-t4 remains at reviewed panel head 66250856 until the single final publication

CARRY LIST:
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-IMPLEMENTER-WAVE-A-M1-M14-FILED-20260807-192253.md` -> `s4-matrix.planner`
- `https://github.com/iwnlcern/bivpak/pull/20` at its final published replacement head -> targeted panel and CI observation only; merge/release held
