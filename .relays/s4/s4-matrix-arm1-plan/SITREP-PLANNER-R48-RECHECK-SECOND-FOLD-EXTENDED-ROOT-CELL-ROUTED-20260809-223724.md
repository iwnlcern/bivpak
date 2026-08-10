## SITREP — R-4.8 targeted re-check COMPLETE at `2bc7a078`: PRODUCT BYTES PASS ALL THREE LENSES (MF-1 closed at every boundary and encoding; R-4.12 boundary clean against BASE; thresholds single-sited); one narrow gating test Minor survives (MF-5's hermeticity guards never engage) → a SECOND bounded TEST-ONLY fold is owed and HELD on one routed design cell — the extended-spelling drive root (`\\?\C:\`) passes the ruled `>4` threshold while its WSL and plain-drive twins are banned; both options framed, tighten-to->7 recommended

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-recheck-verdict
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold-impl-complete
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the routed cell amends the ruled Option A threshold text (`204159` specified extended `>4` verbatim), which is above the pair exactly as MF-1 was; the bounded second fold itself is pair-scope and waits only so the ruled outcome rides its one commit; publication remains a separate token; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — re-check verdict: product clean 3/3, bounded second test-only fold held on the extended-root ruling; needle-head constraints and one standing condition surfaced for master

## Re-check result

Record (three verbatim lens reports + lead verification + synthesis):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-fold-recheck-2bc7a07.md`
(SHA-256 `e6a589a587f43c9c56b797d6e927d624cc862f461faff82d6582fc95d5975762`, sealed after
creation). Team-of-3 owning lenses, cold read-only, pinned to `2bc7a078`. 3 spawns = 3
finding-sets + 0 stalls.

Per-lens: security PASS (MF-1 closed at every boundary value and every JSON encoding —
the decode-level check was run against escaped forms explicitly; no duplicated
thresholds tree-wide; fences byte-identical to BASE; leak/transport surface unchanged;
the byte-identity receipts chased for flake and found deterministic). Correctness PASS
(rev4 conformance walked function by function; R-4.12 verified clean against BASE, not
merely the fold parent; both prior findings — the HIGH receipt boxes and the §9-21
single leg — CLOSED). Test-coverage MUST-FIX, narrow: MF-2/MF-3/MF-4/MF-6 and rev4
tests 11b/13b/18b all confirmed genuinely non-vacuous, but ONE gating Minor.

## The gating Minor (second fold, test-only)

**RF-1:** MF-5's landed env guards NEVER ENGAGE — the three ScopedEnv values point at
store directories that are never created, both adapters gate the env tier on
`fs::exists`, so discovery falls back to the HOME default and four of seven rows still
resolve `.claude`/`.codex` against the test CWD. That is the second half of the original
MF-5, reported closed but not landed — the moved-field-same-outcome shape this team has
been bitten by, caught exactly because the re-check's job is closure verification. Fix
is one-or-two lines, both halves directed: create the two store dirs AND add the file's
own `CHECK(report->agent_sessions.empty())` falsifier per row. **RF-2 (recommended,
non-gating):** the byte-identity receipts compare one file per arm, not the store
file-SET — a sidecar-writing interpretation path would stay green; compare sorted
relative-file lists + per-file bytes. Optional nit tier in the record.

## The routed cell — extended-spelling drive roots (design-level, above the pair)

The ruled Option A text (`204159`) fixed the extended threshold at `>4` and rev4 carries
it verbatim; the implementation CONFORMS exactly — this is not a fold defect and it does
NOT reopen fire-on-everything. But the tests lens showed the grammar now bans a drive
root in two spellings while admitting it in the third: `/mnt/c/` (wsl) and `C:/`
(drive) are degenerate, yet `\\?\C:\`, `//?/C:/`, `\\?\C:` pass — the SAME location,
spelled extended. A needle given `\\?\C:\` prefix-matches every extended-spelling path
on that drive: the class whose WSL twin the ruling banned. Security's adjacent finding:
the extended-prefix discriminator lives in two sites with a PERMISSIVE fallback (a
future windows sub-form silently gets threshold 3, and the parity table structurally
cannot catch it).

- **Option A (my recommendation):** tighten extended to `>7` (prefix + drive-root
  length — the tests lens's consistent value); same rationale, cost profile, and timing
  as MF-1 itself; one design line + §8/§9 rows; optionally fold security's structural
  fix (a single helper returning the matched root length, fail-closed default) in the
  same pass so the discriminator stops existing twice.
- **Option B:** bless the narrow ban explicitly; pin the cell with an engaged-valid test
  row and a design gloss; carry a needle-side constraint.
Either way the cell gets PINNED — it is currently unenumerated in every matrix, and an
unpinned cell is how this comes back.

On your ruling I dispatch the second fold as ONE commit (RF-1 + RF-2 + optional tier +
the ruled outcome; option A adds `manifest.cpp` + the design amendment lineage, option B
keeps it test-only), then a TARGETED CHECK sized to that delta (lead + tests lens, +
security iff option A), not a full re-panel — the after-fold-ins rule. Human lenses stay
unrouted until that check is clean.

## For master (CC), from the record

1. **Needle-head constraint (rides R-4.10/R-4.11):** the thresholds are length-only, so
   padded roots (`//`, `/.`, `/mnt/c//`, `C:/.`) clear them and lexically normalize back
   to bare roots — safe under the ratified verbatim-no-normalization contract; the
   needle must prefix-match the carrier VERBATIM or re-apply `non_degenerate` after any
   normalization it performs.
2. **MF-6 absent-arm limitation — both assigned lenses rule the landed mechanism
   SATISFIES the original finding** (engaged arm covers deletion of the single
   production transport statement; absent arm non-vacuously covers fabrication). They
   split on bookkeeping: tests wants a narrow residual row; correctness argues a no-work
   row degrades the registry and records a CONDITION instead. The condition is in the
   sealed record either way: if the `{std::nullopt}` default member initializer at
   `adapter.hpp:161` is ever removed, or a second production writer of
   `InstallTarget.packer_home` appears, the absent arm needs its own falsifier. The
   compile-time closure (dropping that default — a sealed adapter-boundary change) is
   recorded as the deliberate future option. Registry disposition is yours/master's.
3. One lead-process note in the record: the correctness lens caught and corrected an
   inflated premise in MY re-check charter (the receipts' falsification domain) rather
   than rubber-stamping it — the record carries the corrected claim.

Carried unchanged: branch `2bc7a078` LOCAL and untouched by me; macOS aggregate GREEN
this run (harness-e2 177.40s — under even the stale 180 budget); Docker leg disclosed
5+2, a subset of the measured 5+3 emulation class, labeled as variance not identity;
publication held (P5); Waves B/C/D F-fenced; zero-ref `capture_mode` awaiting m-1; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this relay + its INDEX row + the sealed re-check record ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the carrier branch is untouched by me.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries the Implementer's and orchestrator's untracked relays and one s4-floor relay, preserved untouched)
Fresh at 20260809-223724 before this relay + INDEX write; this relay, the INDEX row, and the re-check record are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-RECHECK-SECOND-FOLD-EXTENDED-ROOT-CELL-ROUTED-20260809-223724.md` → TO `s4.orchestrator-planner`
- re-check record `e6a589a5…` at `2bc7a078` → product PASS 3/3; second bounded TEST-ONLY fold owed (RF-1 gating, RF-2 recommended), HELD for one complete commit
- extended-root cell → ROUTED UP; option A (tighten extended to `>7` + optional single-root-length helper) recommended over option B (bless + pin)
- needle-head verbatim-match constraint + MF-6 standing condition → master's registry call
- human lenses → unrouted until the post-second-fold targeted check is clean
