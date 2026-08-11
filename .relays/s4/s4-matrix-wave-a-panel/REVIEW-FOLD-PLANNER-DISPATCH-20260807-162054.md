## REVIEW-FOLD DISPATCH — Wave-A panel must-fixes routed to the Implementer with per-finding dispositions; two routed items ruled, one held; FOLD_SCOPE is yours before any edit

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-wave-a-panel
PARENT_DISPATCH_ID: s4-matrix-wave-a-panel-disposition
IN_REPLY_TO: .relays/s4/s4-matrix-wave-a-panel/PLAN-ORCHESTRATOR-PLANNER-FOLD-AUTHORIZED-ALLOWLIST-DOES-NOT-FOLD-FETCH-RULED-20260807-161034.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — REVIEW-FOLD authorized at the pair by the orchestrator disposition; you write FOLD_SCOPE before any edit; merge stays the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-06-s4-matrix-arm1-plan.md
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD — the authorized must-fix set with dispositions; fold produces a replacement SHA that owes its own targeted panel

Panel record of record: `docs/sprints/2026-08-04-s4-step4/reviews/2026-08-07-s4-matrix-wave-a-panel-66250856.md`
(five cold SHA-bound lenses, all verbatim; consolidated must-fix M1–M14 in §"Consolidated must-fix").
The orchestrator AUTHORIZED REVIEW-FOLD for the foldable set and ruled the routed items
(`…FOLD-AUTHORIZED…-20260807-161034`). Fold at the pair under the standing discipline:
**write FOLD_SCOPE (every touched file vs the findings scope) BEFORE any edit; every row inside
the Wave-A file universe; a row outside it is a deviation to the orchestrator BEFORE the edit,
however small.** The replacement head owes a TARGETED panel sized to the fold delta (my job to
run after your fold); the stack stays open; B/C/D stay F-fenced.

DISPOSITION PER ITEM (fold unless marked otherwise; record has the evidence):

FOLD — engine/wrapper correctness + safety:
- M1 env pinning: move the isolated `GIT_CONFIG_GLOBAL` to restore-side `Opts` (D1.1 scopes it restore-side); let classification read the user's global excludes; neutralize repo-local `core.hooksPath`/`credential.helper`/`core.sshCommand` via `GIT_CONFIG_COUNT`; MOVE the T2 "env is pinned" test with the scope fix.
- M1-hygiene (security #1 hygiene half only): pin `GIT_PROTOCOL_FROM_USER=0` and credential-helper neutralization with the env fix. This is generic subprocess hygiene, NOT URL policing.
- M2 delimiter: route pathish values through `operands`; where a value cannot be an operand (revisions), VALIDATE at the type boundary (object names hex-only; ref names against check-ref-format) — validation, not delimiting, per the record.
- M3 restore containment: reject non-relative / non-normalizing `relpath`/`bundle`/`local_refs_bundle` inside `restore_entry` before any mkdir or spawn; hostile-manifest test.
- M4/M8-budget: per-call budgets by call class (short metadata; minutes-class bundle/clone/unbundle; network ls-remote/fetch); distinguish budget-expiry from git-failure in the error kind.
- M5 eligibility O(refs×tips): hoist the per-tip presence pass out of the per-ref loop; bound the tip-list with an explicit over-threshold result.
- M6 promisor policy: thread the classification-time bit onto `RepoEntry`; one predicate; one missing-object mapping across classify/eligibility/capture; assert `GIT_NO_LAZY_FETCH=1` on every promisor invocation via a request-trace seam (closes tests #2).
- M7 divergence vocabulary: return per-ref rows with `outcome: failed(detail)` and per-repo `repo-verify-divergence` as WARNING-class (exit 2), not `RepoRestoreFailed` (exit 4); wire the two dead fields.
- M8 RefUncapturable/verify_bundle: map create/verify PROCESS failures to `GitInvocationFailed{repo_relpath,op,exit_code}`; gate the promisor mapping on `missing_object_failure` in `verify_bundle` too; implement the genuine per-ref neither-route `RefUncapturable{repo_relpath,ref}` or leave it unreachable-by-construction with a comment (it cannot fire at Arm 1 since eligibility assigns every ref a carried availability).
- M9 comparator second tolerance surface: express the tracked-file `file-mtime` exemption and the `.git` exclusion as DECLARED tolerance rows the comparator reads (D6 single-source).
- M10 tests-assert-fixtures: rewrite the full-environment/no-passthrough test to falsify a parent-passthrough regression; rewrite "eligibility optional" against a real `classify()` zero-ref result; add cap-saturation tests on both streams and decide (below) whether truncation surfaces as `io_failed`.
- M11 helper duplication: hoist the nine copied helpers into one `src/core/repo/git_exec.{hpp,cpp}`; the penumbra snapshot MUST be a single function called from both sites; rename the `expected`-shadowing local.
- M12 throwing filesystem: switch the four `restore.cpp` calls to the `error_code` overloads, fold into `restore_error`.
- M13 TempDir: extract one `tests/support/temp_dir.hpp` with deleted copies + id counter; all four test files include it.

FOLD TO CONFORMANCE (orchestrator ruling 4):
- M14 root-repo relpath ".": design criterion 4 and the reconciled base are unambiguous — ONE staging mechanism; the matrix EXTENDS the partial-dir staging, never invents a second. Fold the `<stage>/repo-materialize-<id>` + per-child-rename mechanism to conformance (materialize inside the existing partial-dir boundary). If conformance genuinely cannot be reached inside the Wave-A universe, that is a DEVIATION routed to the orchestrator with the impossibility SHOWN — never a fence invented here (the fences-need-authority rule).

DO NOT FOLD — answered by sealed record (orchestrator ruling 2):
- security #1 ALLOWLIST half (a git transport-policy allowlist): sealed addendum-D `:26-28` is an OPERATOR ruling deleting the SR-M14 URL allowlist/host-floor ("Bivpak is a portability tool, not a git-URL firewall; networked open is git-clone-grade trust"). Re-introducing it is above every s4 seat. Disposition in your fold report: `ANSWERED-BY-SEALED-RECORD`, the finding's text UNALTERED, the citation attached; the lens argument travels UP by pointer on the operator's cadence, no fold work holds on it.

FOLD — DNA/sealed-method ruling (orchestrator ruling 3):
- security #9 / correctness Q1 (the mutating unknown-tip `fetch --no-tags` into the user's SOURCE repo during pack): NOT SANCTIONED. The sealed method is the `ls-remote --heads --tags` tips-union (pack-engine `:88`) + local ancestry; where a tip's object is absent, ancestry is UNPROVABLE ⇒ honest-unknown ⇒ `capture_mode: full` (fail-safe), never a fetch to make the check answerable — and a write into the user's repo violates product DNA ("read host state freely, write only with consent"). Fold: REMOVE the recovery fetch; unprovable tips classify honest-unknown → full.

DESIGN-READING ANSWERS FROM THE BYTES (fold or no-change per each; cite in your fold report):
- correctness Q2 (`reset --hard` vs `checkout` under §A2): the §A2 method for the checked-out branch is EXPLICIT — "restore sets HEAD to the manifest-recorded branch (`git symbolic-ref HEAD` / `git checkout <branch>` or detach per `head_state`)" (addendum-A §A2, new normative text, lines 96–100). `reset --hard <sha>` force-moves the branch ref AND the worktree — a heavier operation NOT in the sealed method. FOLD: replace `reset --hard` with the §A2 symbolic-ref/checkout method per `head_state`.
- correctness Q3 (workspace-wide vs subtree nested fencing): design D2.2 step 1 is "**Repo-set shape (from discovery, before per-repo classification)**" — the predicate is over the discovered repo-SET, evaluated before per-repo work, so workspace-wide fencing is CONFORMANT to the design text; and at Arm 1's actual single-clean-repo scope the sibling-repo distinction is moot. NO CHANGE; note the citation in the fold report.

HELD — routed back to the orchestrator this turn (do NOT bless a value in the fold):
- correctness Q4 (`capture_mode` for the zero-ref payload-only entry): the sealed §2.3 enum is `overlay | full` only; §A6 and pinned-G leg (e) make the zero-ref entry payload-only / no-bundle / no-eligibility but assign NO `capture_mode` — `full` normally implies a bundle, which this entry does not have. The bytes do not decide this cell. I am routing it to the orchestrator as a named inexpressible-cell (the eligibility-cell/addendum-G shape). Until ruled, leave the current value in place but DO NOT add a test that blesses `full` as correct for this class; your other zero-ref assertions (payload-only-unborn, EmptyRepoPayloadOnly, no bundle, no eligibility) stand and are byte-backed.

Cheap fold-ins (Implementer discretion, all named verbatim in the record): drop `tests/test_probe.cpp` from `biv_tests` (it compiles into both targets); CLOEXEC-default floor / `pipe2` / `O_NOFOLLOW`; redundant `show-ref` + per-ref sweeps; capture-buffer `{}`-init + bulk insert; harness `_run_git` timeouts + hoisted `which`; `engine_error_kind` array-driven + `<initializer_list>`; the two `std::move`s; the `kOmittedSentinel`/`LC_ALL=C` constraint comments; the ordered-gate coverage extensions.

Authority: this SITREP ROUTES the orchestrator-authorized fold with per-finding dispositions; you hold fold-in authority under that disposition (you are CC'd on `…-161034`). Branch mechanics: fold on the stacked topology per the plan (the findings span T1–T4, so expect fold commits across the affected stack branches, restacked); the result is a replacement candidate head. YOUR `PHASE: REVIEW-FOLD` report carries the FOLD_SCOPE block (every touched file vs the findings scope) above `ACTIONS_GIT_REF`, `FOLD_SCOPE_RESULT: all-in`, and the new head; I run the targeted panel on it before it returns to the bar.

ACTIONS_GIT_REF: none — no product/test/harness edit by this seat; this routing relay + its INDEX row are the only writes, docs-lane.
FINAL_GIT_STATUS_SHORT: none — clean tree; fresh at 20260807-162054, this relay + INDEX row the only delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-wave-a-panel/REVIEW-FOLD-PLANNER-DISPATCH-20260807-162054.md` → TO `s4-matrix.implementer`
- `.relays/s4/s4-matrix-wave-a-panel/SITREP-PLANNER-CAPTUREMODE-CELL-ROUTED-20260807-162054.md` → TO `s4.orchestrator-planner`
