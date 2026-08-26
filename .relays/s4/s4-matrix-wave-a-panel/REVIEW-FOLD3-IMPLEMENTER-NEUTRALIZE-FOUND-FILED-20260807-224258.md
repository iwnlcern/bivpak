## REVIEW-FOLD3 — neutralize-found completes the repo-local driver command class; fourth replacement head requests the bounded lead/security check

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD3-PLANNER-DISPATCH-NEUTRALIZE-FOUND-20260807-215450.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no for this filing — the pair Planner's fourth bounded lead/security check at the replacement head is next; merge remains operator-owned and the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: s4.orchestrator-planner, operator
SUBJECT: DONE_WITH_CONCERNS — neutralize-found is folded with real hostile clean-filter RED/GREEN and full local E2; one fourth PR #20 publication follows; bounded lead/security check requested; merge/release held

FOLD_SCOPE:
- src/core/repo/git.hpp -> in
- src/core/repo/git.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/git_exec.hpp -> in
- src/core/repo/git_exec.cpp -> in
- src/core/repo/classify.cpp -> in
- src/core/repo/capture.cpp -> in
- tests/test_repo_git.cpp -> in
- tests/test_repo_engine.cpp -> in
- .relays/s4/s4-matrix-wave-a-panel/** -> in
- .relays/s4/INDEX.md -> in
FOLD_SCOPE_RESULT: all-in

DONE_WITH_CONCERNS

The directed structural fold is complete on the required linear topology:

- T2 static-plus-dynamic request-composition commit
  `92a70c9cdf8a29f6591df558e04dbf26cf73d1ae`;
- restacked T3 head `d7d32f94c86f7043b0c28d6c0a51cff9063e6628`;
- restacked T4 pre-edit scope commit `9494313`;
- T4 enumeration, classification/capture carry, and hostile-fixture commit
  `a3c5454539ab4664573a51840855198416630ffd`;
- this final relay and INDEX row ride the cumulative filing commit.

The scope artifact
`.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD3-SCOPE-IMPLEMENTER-NEUTRALIZE-FOUND-20260807-222224.md`
was written, exact-file linted, INDEX-appended, and committed before the first product or
test edit. Every changed product, test, relay, and INDEX path is IN. There was no
fail-closed refusal, global config enumeration, eligibility/restore policy change,
Wave-C exit-mapping change, or zero-ref `capture_mode` change.

## Structural neutralize-found implementation

The five static injected Git config entries remain unchanged. `Git::Opts` now accepts a
bounded vector of additional config keys and emits one empty `GIT_CONFIG_VALUE_n` for
each after the static base, with `GIT_CONFIG_COUNT` equal to five plus the dynamic count.
The wrapper seam test proved the exact seven-entry composition for two representative
dynamic keys after first producing the intended compile-time RED because the dynamic
option did not exist.

Before classification's first `ls-files`, an un-neutralized config read runs
`git config --local --null --name-only --get-regexp` over the union of these defined
repo-local command-driver families:

- `filter.*.(clean|smudge|process)`;
- `diff.*.(command|textconv)`;
- `merge.*.driver`.

Exit 1 is the ordinary empty-set result; any other nonzero or transport failure remains
a typed Git invocation failure. The parsed names are sorted and deduplicated. Every
subsequent classification Git request receives the empty overrides, and the exact set is
carried in transient engine source state into source-repo penumbra, ref, bundle-create,
bundle-verify, and ref-inventory capture requests. Global config is neither enumerated
nor suppressed.

## Required hostile clean-filter RED/GREEN

The real fixture commits `.gitattributes` containing `* filter=evil`, installs a
repo-local `filter.evil.clean` executable that writes a marker outside the worktree, and
runs the real classification status path. Before the fold, classification returned no
fence but the marker assertion was RED because Git executed the clean program. With the
fold, the focused case passed all six assertions: classification returned no fence, the
marker remained absent, all six required driver-family key forms were enumerated, and an
unrelated `core.editor` key was excluded. Git therefore accepts the empty program value
as the intended neutralization; no unbuildable-shape deviation is required.

## Verification at the cumulative head

- focused hostile clean-filter case: 6 assertions in 1 case passed;
- `biv_repo_engine_tests`: 33 cases passed in the focused regression run;
- `biv_repo_git_tests`: 183 assertions in 6 cases passed;
- `biv_subprocess_tests`: 51 assertions in 9 cases passed;
- fresh full command:
  `git diff --check && cmake --build --preset dev -j8 && ctest --preset dev -E '^safety-hardening$' --output-on-failure`;
- full result: 17/17 locally applicable CTest rows passed, zero failed, in 467.28
  seconds; repo-engine passed in 17.00 seconds, `biv_tests` in 246.15 seconds,
  harness selftest in 10.54 seconds, harness E2 in 179.04 seconds, and Werror passed;
- the macOS preset reported ASan/UBSan, pinned clang-tidy, and fuzz smoke as skips.
  Linux ELF hardening remains excluded locally because Darwin has no applicable
  `readelf`; no unsupported platform verdict is claimed.

No GitHub workflow was triggered during editing, restacking, or local validation. PR #20
was re-read immediately before filing and remains open from `s4-matrix/arm1-t4` into
`s4-matrix/arm1-t3` at remote head
`28cf57185a0d0b4b3409e257fa32c90fb6451c85`. Per the operator's current direction, the
fourth cumulative T4 replacement will be published once after this filing and the
resulting checks observed without reruns.

## Preserved boundaries and requested action

The c52bcca-panel optionals/nits, Wave-C exit-mapping flag, and held zero-ref
`capture_mode` cell remain unchanged. No Wave-B/C/D implementation, new PR, merge, or
release action was taken.

Planner TARGETED CHECK #4 is requested against the final published PR #20 head: lead
byte-verification plus the security-owning lens over the cumulative window from
`66250856`, incorporating the c52bcca and d11c49c records by reference as directed. On a
green recorded check, condition 1 may be called met at that exact head; this Implementer
report grants no merge or release authority.

ACTIONS_GIT_REF: T2 dynamic composer `92a70c9cdf8a29f6591df558e04dbf26cf73d1ae`; restacked T3 `d7d32f94c86f7043b0c28d6c0a51cff9063e6628`; T4 neutralize-found `a3c5454539ab4664573a51840855198416630ffd`; this relay and append-only INDEX row ride the final cumulative filing commit whose SHA lands in repository history after filing; one guarded force-with-lease publication to existing PR #20 follows; no merge/release
FINAL_GIT_STATUS_SHORT: cumulative T4 clean at `a3c5454539ab4664573a51840855198416630ffd` before this relay and INDEX append; origin/s4-matrix/arm1-t4 remains at `28cf57185a0d0b4b3409e257fa32c90fb6451c85` until the single final publication

CARRY LIST:
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD3-IMPLEMENTER-NEUTRALIZE-FOUND-FILED-20260807-224258.md` -> `s4-matrix.planner`
- `https://github.com/iwnlcern/bivpak/pull/20` at its final published replacement head -> bounded lead/security check #4 and one CI observation only; merge/release held
