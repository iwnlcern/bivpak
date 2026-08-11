## REVIEW-FOLD — B1 panel consolidated at d5642ed: NO blocks; nine must-fix findings (one major, strongly cross-converged) to fold before the merge bar; optionals at your discretion; two questions routed up

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-impl-2-b1-review-fold
PARENT_DISPATCH_ID: s4-floor-impl-2
RUN_ID: s4
TASK_ID: B1
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — panel findings routed to the Implementer for fold-in on the open PR head; merge remains the operator's; the release hold is ABSOLUTE
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-B1-PR-FOUR-CHECKS-20260806-010202.md
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator
SUBJECT: REVIEW-FOLD — PR #15 panel verdicts approve/must-fix×4, zero blocks; fold F1-F9; the child-liveness major is a design-conformance fix, not new semantics

PANEL_CHOSEN: team-of-5
DEFAULT_ROLES_CHANGED: no
WHY_THIS_PANEL: C++/systems, production-risk, first Step-4 merge-bar candidate
ROLES:
- defensive-security — hostile inputs, injection, host-store surface (verdict: must-fix)
- performance — I/O, allocations, hot paths (verdict: approve)
- test-coverage — false-green hunt over the matrix and controls (verdict: must-fix)
- correctness-vs-design — plan/design/amendment conformance, boundary (verdict: must-fix)
- cpp-idiomaticity — project idiom, UB, seams (verdict: must-fix)
All five reviewed COMMITTED bytes at exactly `d5642ed` (read-only; no builds). Every
finding below carries lens evidence at file:line; findings the lenses could not evidence
were dropped per the consolidation rules.

## MUST-FIX (fold before the merge bar; all in-slice, no scope expansion needed)

F1 (MAJOR; correctness #1 ≡ tests #3, independently converged) — `codex.cpp:396,423`
with `:857`: `session_for` takes `live_at_pack` from the PARENT candidate alone; a
terminal parent with a dangling/truncated CHILD rollout packs the live child's bytes
silently — fail-OPEN against the design's fail-closed "ANY other tail" rule, and it
propagates into B2's branch-3/4 selection (the live child would later misroute to
`undecodable_line`). FIX: aggregate — parent OR any child's liveness — in `session_for`;
one collect fixture pair (terminal parent + dangling child ⇒ `live_at_pack == true`);
the matching CLI warning assertion. FRAMING (for the CC'd orchestrator to object to if
m-2's seam disagrees): this is the locked design's own fail-closed rule applied to the
artifacts the session packs — a conformance fix, not new semantics.

F2 (security #1, medium) — `main.cpp:53-54`: the NEW generic warning branch writes
`warning.path` raw to stdout; for kinds like `UnsupportedFileTypeSkipped` that string is
an unvalidated POSIX filename (any byte but `/` and NUL) built at `scan.cpp:135`, so
this PR creates a terminal control-byte pass-through where none existed — the text
renderer is strictly weaker than the JSON renderer over identical data. FIX: sanitize
`kind`/`path`/`artifact` (bytes < 0x20 and 0x7F) in `emit_pack_text`; this also closes
the B2-inherited artifact-path concern (security #2). The `SessionLiveAtPack` branch is
NOT affected (session ids are grammar-gated upstream — verified). E2 witness the lens
could not run read-only: pack a source dir containing a control-byte filename and
inspect raw stdout — run it in your fold evidence.

F3 (tests #1) — `test_cli.cpp:602-609`: the design-§7-test-3 negative control is
ABSENCE-BLIND — exit 0 + no warning text is equally satisfied by "collected, correctly
quiet" and "never collected at all". FIX: add the positive witness — a `--json` pack run
asserting the codex session appears in `agent_sessions` (envelope.cpp:90-100 carries the
field) alongside the text-absence checks.

F4 (tests #2 + correctness #5) — the zero-byte row never touches production and its
guard is a tautology (`CHECK(rollout.empty())`). FIX: drive `collect` over the zero-byte
store and pin the production disposition (`report->sessions.empty()` — the candidate
drops at `inspect_rollout_head`, `codex.cpp:839-845`), keep the seam row, and state in
the PR body that zero-byte has NO product liveness path on this leg (so the green is
never read as product coverage).

F5 (idiom #1, boundary-contract fail; ≡ your carried linkage-seam item, now with the
exact fix) — `codex.cpp:936-942` + `test_adapter_codex_collect.cpp:21-25`: the
`codex_testing` seam is declared nowhere, hand-redeclared in the test TU, and linked
UNCONDITIONALLY into the shipping binary — against the repo's own guarded-seam idiom
(`probe.hpp:85-103` + `CMakeLists.txt:96,127`). FIX: declare in `codex.hpp` behind
`#if defined(BIV_CODEX_TESTING)`, add the define to `biv_tests` only, delete the
redeclaration. ALSO (correctness #6 + performance tip, same surface): have the
production call site `:857` call the seam helper so exactly ONE spelling of the
predicate's polarity exists.

F6 (correctness, A3 evidence) — A3 checks (3) and (4) — the five mutation receipts and
the class-scoped no-touch statement — exist only in your SITREP narrative; the range
carries no durable evidence. FIX: land them in the PR body AND under
`docs/sprints/2026-08-04-s4-step4/results/receipts/` per the plan's evidence path
(mutation diff + failing assertion per receipt, the receipt form).

F7 (correctness #2) — the plan-mandated `/* m-3 spelling at consumer review */` markers
are absent at both kind-specific line shapes in `main.cpp:46-51` (zero grep hits). FIX:
add the marker comments — they are the mechanism the consumer leg finds its strings by.

F8 (correctness #3 + idiom #6) — `test_envelope.cpp:103,138` model a COMPETING kind
spelling (`AgentArtifactTornTail`, path==artifact) against the design-pinned
`TornTailDropped`/{path: session id, artifact: member path} that `main.cpp:49` keys on;
B1 is the head that pins this carrier for B2. FIX: use the pinned kind and shape.

F9 (tests #5 + correctness #4, converged) — two of the three renderer branches B1 OWNS
(the design's "both kinds' line shapes defined now" + the genericity claim) ship
untested. FIX: one test covering the three shapes incl. an unknown kind (the
`SessionDuplicateStore` warning already takes the generic branch) and the
`TornTailDropped` shape; mirror the serializer's `!path.empty()` guard in the generic
line while there (idiom #4 — the dangling `": "` latent case).

## OPTIONAL (your discretion; no human direction attached)

O1 (3 lenses) — `padded_string{record}` via the string_view ctor at `codex.cpp:145`
(drops one full copy of the tail record).
O2 (2 lenses) — `#include <array>` in `test_adapter_codex_collect.cpp`, `<utility>` in
`test_cli.cpp`.
O3 (2 lenses) — a lone-`"\n"` fixture row pinning the `record_end == 0U` guard (the one
wrap-capable arithmetic in the function; verified correct, unpinned).
O4 (idiom #2) — `terminal_tail_type` returns an `optional<string>` nobody reads; a named
`bool` predicate is the honest shape.
O5 (idiom fold-in; PREVENTION for F8) — promote warning kinds to
`inline constexpr std::string_view` constants in `pack.hpp`, consumed by pack.cpp,
main.cpp, and tests.
O6 (correctness fold-in) — the generic line includes artifact/bytes when present.
O7 (correctness fold-in) — a final-record-parses-but-no-`type`-key fixture (live by
fallthrough, untested).
O8 (tests #7) — one PR-body line: the harness suite is red across
`d6133de..4944801` by the checkpoint flow (bisectability note).

## ROUTED UP (CC'd orchestrator; not the pair's to decide)

Q1 (security #4) — `bytes` is exact to UINT64_MAX by design, but any double-backed JSON
consumer silently misreads values above 2^53. Whether the envelope contracts exact
round-trip (document bignum requirement) or bounds the field is an m-3 consumer-surface
question for the panel's consumer leg.
Q2 (security fold-in; pre-existing) — `write_escaped` passes bytes ≥ 0x80 raw (e.g.
U+202E) on BOTH surfaces; pre-existing on JSON, first terminal exposure via B1's text
renderer. Upstream hardening question, not a B1 defect beyond F2's sanitizer.

Fold shape (phase note: this relay is the PANEL FINDINGS PACKAGE, filed report-only —
the REVIEW-FOLD-phase artifact is YOUR fold report): per protocol it carries FOLD_SCOPE
(every touched file vs this findings scope) above its ACTIONS_GIT_REF with
`FOLD_SCOPE_RESULT: all-in`; after the fold I run the targeted re-check on the folded
head (F1 fixture, F2 witness, F3 witness, the seam relink) — NOT a full re-panel unless
the fold changes design/blast radius. All F-fixes are inside the already-granted
universe (code + tests + PR body + receipts path); no new scope is needed — if you find
otherwise mid-fold, STOP and route.

ACTIONS_GIT_REF: no edits claimed at this seat — the panel lenses were read-only, the fold belongs to the Implementer, and this relay plus its INDEX row are the only seat writes, riding a docs-lane commit whose SHA lands in repository history after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two docs-lane paths named above

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-PLANNER-B1-PANEL-CONSOLIDATED-20260806-015651.md` → `s4-floor.implementer`
