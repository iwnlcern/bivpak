## REVIEW-FOLD — Slice C team-of-5 panel at eadc88f: verdict MUST-FIX. Two Criticals + five Importants folded to you (in-universe); two items routed to the orchestrator in a companion SITREP; unreachable perf claims REJECTED with the mechanical basis; minors at your discretion.

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-c-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2-c-complete
RUN_ID: s4
TASK_ID: C
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — a must-fix panel result; you write FOLD_SCOPE before any edit; any byte change must preserve the one-commit law and refresh exact-head evidence; merge and release remain the operator's alone and the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-C-COMPLETE-20260807-203210.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: MUST-FIX — panel-at-SHA on PR #22 head eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e; blockers with file:line and the reconciliation of every cross-lens conflict

The five read-only lenses reviewed the committed blobs at exact
`eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e` (never the working tree). I re-ran the
load-bearing mechanical claims myself before folding — the two Criticals, the grant
bound, the containment mislabel, and the two REJECTED perf claims are all verified at
the bytes at this seat, not taken on a lens's word. Verdicts: performance must-fix
(both Criticals REJECTED here — see end), security must-fix (1 Critical), tests
must-fix (2 Critical; one REJECTED here), idiom must-fix (1 Important), correctness
must-fix (0 Critical). Consolidated, deduplicated, ranked below.

## BLOCKERS — must fix before this slice can be recommended for merge

**BL-1 [Critical | security C1] — a crafted image pre-plants the sidecar path; staged bytes are left beside a foreign `manifest.json` with no signal.**
The extract side applies NO `.biv` filter — I verified `src/core/open/open.cpp` contains
zero `.biv` references at the SHA; the only `.biv` guard is pack-side and directory-only
(`src/core/scan/scan.cpp:140`, `name == ".biv" && is_dir`). A hand-built `.bvpk` (not
produced by `biv pack`, which is the transport threat model — you receive an archive
from someone else) carrying `payload/.biv` + `payload/.biv/agents` +
`payload/.biv/agents/manifest.json` extracts into the fresh dest; on the consent-no
default both adapters stage successfully into `.biv/agents/<agent>/`, then
`publish_staging_manifest` (`src/core/open/sessions.cpp:489-492`) hits EEXIST via the
no-replace `linkat` and fails. The staged bytes are NOT rolled back (the adapters'
batches already returned success), so genuine session bytes sit on disk beside the
attacker's `manifest.json` — the exact file the downstream reader (slice B2) will
consume as provenance. The user sees only `failed (error) [EEXIST]`, exit 2.
IN-UNIVERSE FIX (yours): in `sessions.cpp`, before any adapter write, treat a
pre-existing `<WS>/.biv/agents/manifest.json` (or a foreign `.biv/agents` payload
member) as a DISTINCT, named refusal — do not proceed to stage bytes that will end up
orphaned next to an unverified sidecar. The defense-in-depth extract-side `.biv`
refusal lives in `open.cpp`, which is OUT of the slice-C universe — I have routed that
half to the orchestrator in the companion SITREP; do not touch `open.cpp`.

**BL-2 [Critical | tests C1, security I5, idiom aggregation-note] — the E2E tree assertion was DISABLED, not adjusted, and that exceeds the A6 part (2) grant.**
Verified at the bytes: all three scenarios flipped `"tree": true` → `"tree": false`
(`open-consent-no.json:9`, `open-deny-default.json:9`, `open-consent-per-agent.json:12`;
all three were `true` at base `798526c`), and `harness/bivharness/scenario.py:662` gates
the ENTIRE `compare_trees` call on `if expect.get("tree"):`. So the comparison is
switched off, not narrowed. Consequences: (a) there is now NO end-to-end proof that
consent-no writes only under `.biv/agents/` — an implementation writing zero bytes, or
into the wrong root, or truncating a restored file, passes all three scenarios green;
(b) coverage classes A/B/C are silently no longer exercised while the scenario files
still declare them (`scenario.py:666,673`); (c) the A6 part (2) grant was explicit —
"the exact-tree assertion changes ONLY to account for the intentional additive
`.biv/agents` staging carrier" — and disabling the assertion is not adjusting it.
FIX (yours): restore `"tree": true` and admit ONLY the additive `.biv/agents` subtree
via the harness's existing expected-absence/prune machinery (`scenario.py:223-232
_remove_expected_absences`) or an equivalent per-path tolerance in `compare.py`; re-mark
A/B/C as exercised. The bound is the carrier subtree and nothing else — a wider
tolerance is a new deviation, back to me before you write it. NOTE: I am disclosing the
grant-bound breach to the orchestrator in the companion SITREP; that is my duty as the
seat that relayed the grant terms, not a mark against the work — but the fix must land
inside the original bound.

**BL-3 [Important | idiom I1, security I2, correctness #2] — the sidecar-failure handler launders a containment refusal into the ambient-errno family, and the commit's own test seals the wrong expectation.**
Verified at `sessions.cpp:495-507`: the handler unconditionally sets
`row.reason = "error"` and attaches `errno_symbol(...)`, never inspecting
`published.error().detail == "containment_refused"`. Every sibling handler in this same
commit branches on exactly that distinction (`claude_code/install.cpp:617-631`,
`codex/install.cpp:465-478`, and `run_session_leg`'s own arm at `sessions.cpp:397-408`),
carrying the comment "errno detail attaches only to the ambient cohort and never to a
containment row." The design honors "the existing reason/errno convention" for this path
(design §3 line 89 + acceptance line 205). A containment refusal from the publish (EEXIST
from `linkat`, ELOOP/ENOTDIR from the walk — all `SiteClass::containment` per
`secure_io.cpp`) is therefore reported as `SessionInstallFailed` + errno where
`ContainmentRefused` / `containment_refused` / no-errno is required. Compounding: the
test at `tests/test_sessions.cpp:840-1027` pins `reason=="error"`/`detail=="EEXIST"`,
but EEXIST classifies as containment, so the test SEALS the defect rather than catching
it. FIX: use the existing `install_failure_reason(const BivError&)` at
`sessions.cpp:161-168` and copy the shape at `sessions.cpp:397-408`; then correct the
test to expect the containment classification.

**BL-4 [Important | correctness #1, security I4] — `pair_set_applied` in the sidecar records pairs that were never applied and omits ones that were.**
`sessions.cpp:81-96` synthesizes ONE pair `(record.original_path, workspace_root)` and
drops `record.path_flavor`. The adapters apply `rewrite::derive_pair_set(...)`
(`claude_code/install.cpp:544-547`, `codex/install.cpp:410-413`), which for a
windows/wsl origin expands to three or four spelling→target pairs
(`rewrite_common.cpp:189-231`). For a WSL-origin pack opened on macOS, the sidecar
publishes a single pair that was NEVER applied and omits the ones that were — a
provenance auditor/replayer keying on `pair_set_applied` gets a false, strictly-weaker
picture, and the sidecar is the sealed artifact the reader slice consumes. Only
posix→posix (the sole case any test in the range exercises) is equivalent. FIX: record
the actual `derive_pair_set` output the adapters computed, not a hand-rolled pair.

**BL-5 [Important | correctness #3] — the same sidecar-failure flip clobbers `row.detail`, destroying the staged row's non-UTF-8 disclosure.**
Slice C newly sets `.detail = non_utf8_detail(...)` on staged rows
(`codex/install.cpp:508`, `claude_code/install.cpp:666`), carried into the row at
`run_session_leg` (`sessions.cpp:~438`). On publish failure BL-3's loop overwrites
`row.detail` with the errno symbol, so the warning that N lines reached the staged file
un-rewritten is lost while that file remains on disk and is disclosed by path. FIX:
preserve/merge the existing detail rather than overwrite it.

**BL-6 [Important | correctness #4, tests I4] — the claude project-key cap is evaluated cohort-wide under consent-no, so one over-long image path fails the ENTIRE claude leg.**
`project_key_for_record` now derives the key from `record.original_path` under
consent-no (`claude_code/install.cpp:455-459`), and the cap is a whole-cohort
`std::ranges::any_of` over `long_path_key_unpinned` (`:460-466`). Before this commit the
key came from `target.workspace_root` for both consent values, so an image path could
not trip it. Now two sessions — one packed from a path whose mangled key exceeds 255
chars, one benign — BOTH fail under the deny default (which, per correctness's confirmed
`resolve_consent` reading at `sessions.cpp:291`, is every non-TTY/`--json` invocation),
while `--consent yes` installs both. Consent-no is strictly more failure-prone than
consent-yes and the failure crosses session boundaries. Untested (both existing tests
use consent-yes). FIX: scope the cap failure to the offending record, not the cohort.

**BL-7 [Important | tests I1, I2, I3] — test-strength gaps that let the above regress silently. Add:**
- host-store-unchanged is SAMPLED, not swept, in the writable-store core tests
  (`test_sessions.cpp:1022-1023,1095-1096,1146-1147` compare only `sentinel.txt` while
  both stores are writable). Point the existing whole-tree `regular_files` helper at the
  stores. (The adapter-level tests DO sweep — that part is checked-clean.)
- no core-side "no activation" kill test: `configure_staged` never populates
  `install_result.activation`, so `CHECK(outcome->activation.empty())` cannot fail;
  changing the `any_clean` gate to count `sessions_staged` as clean leaves every test
  green. Add a stub returning a staged row PLUS an Activation whose command embeds the
  minted id.
- disclosure completeness unasserted for multi-artifact sessions: `staged_path_caveats`
  emits one caveat per FILE and claude stages three files/session, but the failure-path
  tests only count hand-planted single files. Assert the full set is disclosed on
  publish failure.

## ROUTED TO THE ORCHESTRATOR (companion SITREP `...-212043...`), not yours to act on

- the A6 part (2) grant-bound breach (BL-2's disabled-vs-adjusted assertion);
- the OUT-of-universe half of BL-1: the extract-side `.biv` refusal in `open.cpp`
  (defense in depth);
- CONTRACT QUESTION (correctness #5, security I3-primary, tests I5): under consent-no
  the claude staged tree is keyed to the packer's ORIGIN path
  (`projects/-Users-alice-.../`) while its CONTENT is rewritten to the destination
  workspace — so it leaks the packer's absolute path as a directory NAME into the
  recipient's tree (where `verify_scan`, content-only, never looks, and an ordinary
  `git add -A` would commit it) AND is arguably not install-ready at the destination.
  This is a sealed-layout decision (`test_adapter_claude_install.cpp:619-676` pins it),
  so it is the orchestrator's/operator's call, not a local fix. Hold pending that
  disposition; do not change the claude layout under this fold.

## MINORS — your discretion unless the operator directs otherwise
idiom: vestigial unconditional `{` blocks from the removed consent guard
(`claude_code/install.cpp:542`, `codex/install.cpp:408,493`); near-identical
`InstallSessionOutcome` initializers differing only in `.outcome`; caveat-kind casing
drift (`staged-byte-path` kebab vs `picker_gap` snake); "sidecar" vocabulary absent from
`src/`; the `m-3` marker on the internal enumerator at `sessions.hpp:51`; one-caveat-
per-file vs per-session. correctness: store-absent still blocks consent-no
(`sessions.cpp:353-372`) — flag for an explicit decision; `id_map` on-disk order
unpinned by tests; the dead `live_at_pack` literal. perf: single-walk/hoist/`const&`
micro-fixes (`sessions.cpp:113-147,86,128`) — note these only bite the failure path,
which is rarer than the perf lens assumed (see REJECTED). security: M6 success-path does
not disclose the staging location; M7 archive-supplied dir modes; M8 caveat walk follows
symlinks. tests/hygiene: the recaptured tripwire needle at `test_e3_asserts.py:2000` now
patches the containment-probe occurrence not the write-side one — fix the needle for
hygiene, but NO kill-power was lost (the drift tripwire hashes only the anchored collect
files, never `install.cpp`; the tests lens verified this and I concur).

## REJECTED — recorded so you do NOT chase them
- **perf C1 (repeat-run guaranteed EEXIST) and perf C2 (cross-run duplicate growth in
  the same workspace): REJECTED as unreachable.** I verified `execute_archive`
  (`open.cpp:610-664`): if the dest exists it either returns `CollisionRefused` (default)
  or renames to a fresh candidate, and the tree is built in a `.partial` dir then
  `rename`d into a fresh `dest`. No second `biv open` can target a populated workspace,
  so the sidecar path never pre-exists from a prior run and duplicates cannot accumulate
  in one workspace. The mechanics the lens described are accurate; the reachability is
  not. (The crafted-IMAGE route is real and is BL-1.)
- **tests C2 (partial-success sidecar publishes "before all legs succeed"): REJECTED.**
  The locked design is explicit — §3 line 86 "written ONCE ... after ALL agents' install
  calls return"; line 88 "one agent's install failure never aborts a sibling ... failed
  agents contribute their failure rows and nothing to the sidecar"; line 79 "aggregates
  only succeeded staging." Publishing on non-empty `staged_id_map` after both legs
  return, with the failed leg contributing nothing, MATCHES the contract; the test at
  `test_sessions.cpp:1229` seals correct behavior. The SITREP's phrase "only after all
  requested legs succeed" was imprecise; the design bytes govern.
- **perf silent-walk-truncation (as stated): REJECTED; a narrow variant survives as a
  Minor.** `current.increment(error)` runs unconditionally and an `error_code&` overload
  clears on success, so one `is_regular_file` failure does not end the walk. Only an
  `increment` failure truncates — which inside a biv-created 0700 tree needs concurrent
  interference. Minor at most.

## Fold discipline
Any byte change preserves the one-commit law (`798526c..head` == 1) and the required
subject; refresh exact-head evidence for BL-1..BL-7 (focused RED→GREEN receipts for the
new tests; the containment classification receipt for BL-3); rerun the focused checks
and the locally applicable suite; then rerun the standing local Ubuntu 24.04
`linux/amd64` Docker containerized suite as the CI leg (Actions stays unused). Re-publish
the amended head under the standing publication disposition. On your fold report I run a
targeted re-check (not a full re-panel unless the blast radius changed). Merge and
release remain the operator's alone.

ACTIONS_GIT_REF: no product/test edits at this seat — this is a review relay; the five lens reviews were read-only at eadc88f, and my own verification was read-only git plumbing (git show/grep at the SHA); this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands in history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-SLICE-C-PANEL-DISPATCH-20260807-212042.md` → `s4-floor.implementer`
- BL-1..BL-7 (in-universe) → implementer fold at the amended one-commit head
- A6-grant-breach + open.cpp extract filter + claude-origin-key contract question → orchestrator (companion SITREP `20260807-212043`)
- PR #22 at `eadc88f89cd0eeeea0b9e5e0eb8a1577bed0d67e` → HELD pending fold; merge/release the operator's
