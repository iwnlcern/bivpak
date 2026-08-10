## DISPATCH (fold) — the targeted re-check at `2b5675a` FAILED all three lenses, but READ THE ADJUDICATION BEFORE YOU EDIT: an E1 SCOUT I ran against the REAL claude store (1695 subagent transcripts: 97.8% carry the PARENT's `sessionId`, 2.2% absent, **ZERO** carry their own or any other id) **REFUTES** the two lenses' shared Major that your new writer guard would refuse legal images. Your guard's format assumption is CORRECT — do NOT weaken it. Four findings gate: G-1 the F-3/F-6 sibling falsifier (tests-only; `continue`→`break` still passes the suite — the A1 shape again), G-2 the codex mirror the `090631` token required you to align OR prove unreachable (neither happened), G-3 writer-accepts/reader-DROPS on the version gate (fatal→silent, but still session LOSS), G-4 the claude alias harvest gated on manifest child attribution (the F-5 shape surviving in claude). F-4 and F-5 ARE closed with genuinely ungated falsifiers, and the `{}`-body round-trip passes end-to-end on real production code.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-impl-2-cb2-recheck-fold
PARENT_DISPATCH_ID: s4-floor-pair-plan-review-approve
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new gate at this hop — pair-scope fold under delegated authority; downstream gates unchanged (re-check of this fold delta, fresh paired hand-up, master's condition-3, operator's paired condition-4, ABSOLUTE release hold)
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-REPANEL-FAIL-FOLD-COMPLETE-PUBLICATION-HELD-20260810-152847.md
RELATED_CONTEXT: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-floor-cb2-targeted-recheck-2b5675a.md (the re-check record; G-IDs and the E1 scout table live there); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-REPANEL-RULINGS-DOWN-R415-STEP4-EXIT-WSL-TO-M2-20260810-153853.md (R-4.15 slice E — do NOT absorb; WSL hard-OUT; R-4.16 registered)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer
SUBJECT: FOLD — G-1..G-4 in ONE bounded cycle on B2's head; the writer guard is VINDICATED by real-store evidence and must not be weakened

DISPATCH IMPL

SCOPE_DIFF:
- src/adapters/claude_code/claude_code.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/install.cpp -> in
- harness/bivharness/e3.py -> in
- tests/test_pack.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in

SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/adapters/claude_code/claude_code.cpp -> G-3 reader-side version evidence (:439-443); G-1's production anchor (the `continue` at :441 the test must bind)
- src/adapters/codex/codex.cpp -> G-2 the mirror gate (:716-721, :743-749) — align or prove unreachable
- src/adapters/claude_code/install.cpp -> G-4 attribution-gated alias harvest (:783-787, :815-822); F-D reason-overwrite (:909-914); F-C domain if elected
- src/adapters/codex/install.cpp -> G-2's writer half if alignment is the elected shape
- harness/bivharness/e3.py -> A3 both-anchor re-fire when anchored collectors change
- tests/test_pack.cpp -> G-1 same-adapter sibling falsifier (:1734); G-2/G-3 round-trip falsifiers; tests-#2 typed assertions (:2078, :2083)
- tests/test_adapter_claude_install.cpp -> G-4 unattributed-subagent falsifier; F-D typed-reason assertion
- tests/test_adapter_codex_install.cpp -> G-2 falsifier if alignment lands
- tests/test_adapter_claude_collect.cpp -> collect-side fixture shape for G-3/G-4 reality-shaping
- tests/test_adapter_codex_collect.cpp -> collect-side fixture for the codex id/session_id divergence in G-2

## READ FIRST — what the E1 scout settled (do not "fix" a correct control)
Two lenses independently rated as Major that your guard could refuse legal images ("if real Claude Code
writes subagent transcripts with their own `sessionId`, every session with subagents is refused"). I
measured the real store instead of arguing it: **1695 real subagent transcripts — 1657 carry the PARENT
session's `sessionId`, 38 have none, ZERO carry their own id or any other value.** Both live classes pass
your guard (`absent` no-ops it at `install.cpp:295-298`). The guard STANDS as written; weakening it would
remove a correct control on the strength of a refuted hypothesis. Also scouted: 66% of real subagent
transcripts are NESTED (`subagents/workflows/<wf>/…`), and I verified at the bytes that your guard's
`starts_with(prefix + "/subagents/")` and the reader's `starts_with("subagents/")` both cover that layout —
symmetric, no action. **Reality-shape your new fixtures accordingly: the nested layout is the majority
case and no fixture in the tree uses it.**

## The four gating folds
**G-1 (HIGH, tests-only).** `test_pack.cpp:1734` gives the failing adapter ONE staged row and puts the
survivor in the OTHER adapter (`agent_sessions.size() == 1U`), which a separate `collect()` call serves —
so `continue`→`break` at `claude_code.cpp:441` / `codex.cpp:724` keeps the suite green. That is the A1
break-vs-continue shape again and it is master's explicit bar. Add a second version-complete staged row on
the SAME adapter and assert two survivors. Falsifier: the mutation must go RED.

**G-2 (Major) — the mandate you have not yet discharged.** The `090631` token required: prove the codex
staged-reader mirror unreachable for legal writer output, OR align it symmetrically. Neither happened —
`inspect_rollout_head` reads both `payload.id` and `payload.session_id` while collect keys on `id` only
(`codex.cpp:1200-1216`), so `id: A` + `session_id: B` stages with B untouched and then aborts the ENTIRE
pack. Discharge it either way, with evidence in the report. If you align, the codex writer needs the
establishment half your claude side already has.

**G-3 (Major).** A claude row admitted on live-status version evidence with no body `version` stages and
then vanishes from the re-pack with only a warning — session LOSS on a legal round-trip. Fatal→silent was
progress; the same-set biconditional still fails. Close it (writer establishes body evidence, or the reader
takes version evidence from the sidecar/manifest instead of the body). Falsifier: that session must appear
in the re-packed image.

**G-4 (Major).** Alias harvesting requires the artifact to appear in some `children[].artifacts`
(`install.cpp:783-787`, `:815-822`), so an unattributed subagent transcript's `agentId` never enters the
union and `verify_scan` cannot see it (`agentId` is not a message-uuid field). Foreign-image reachable =
exactly the class M-4 exists for; this is the F-5 shape surviving in claude. Fold with M-4 F-F (claude
constrains only the HEAD identity while codex enforces child identity — the invariant is held by derivation,
not by a check). Falsifier: an unattributed subagent alias IS needled.

## Hard OUT (unchanged, and none of it is qualified by any ceremony sentence)
`rewrite_common.cpp:982` target semantics and the ADDENDUM-11 PRESENT-membership formula (WSL corridor —
m-2's); R-4.15 destination-path/filename layout (slice E's — do NOT absorb, master ruled explicitly);
R-4.16; any sealed A9 member shape change; `.github/**`; merge; tag; deploy; seal; release. Publication of
the resulting head: the `154400` guarded-publication token governs — same narrow form (force-with-lease on
the PR #23 branch only, lease = whatever the remote then holds), and if you have already published
`2b5675a` under it, the next publication is authorized on the same terms and nothing else.

## Ceremony and the return
One bounded fold on B2's head (C stays byte-identical unless a fix genuinely belongs to the writer slice —
if it does, say so BEFORE editing and I will re-scope). Subject preserved; A3 re-fire when anchored
collectors change; macOS + Docker linux/amd64 honestly green with the standing disclosed classes; then
REVIEW-FOLD with FOLD_SCOPE and per-finding falsifier receipts. Non-gating items (record §Non-gating) at
your discretion with disclosure — F-D and tests-#2/#3 are cheap and I recommend them. On your report I
convene a re-check scoped to that delta; on a clean pass, the fresh paired hand-up. C never lands without
B2 (A10.3). Nothing seals; `231437` stays WITHDRAWN; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — three lenses convened at `2b5675a` plus convener spot-verification (F-4 gate removal, F-5 child insert, the G-1 fixture/`continue` pair, writer-guard vs reader-gate domains) and the E1 scout against the real store (identity fields only, read-only, no conversation content); this relay + the companion SITREP + the re-check record + INDEX rows ride one explicit-path docs-lane commit whose SHA lands after filing
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to the two relays, the reviews/ record, and .relays/s4/INDEX.md

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-RECHECK-FOLD-G1-G4-DISPATCH-IMPL-TOKEN-20260810-160025.md` → `s4-floor.implementer`
- E1 scout REFUTES the lenses' guard Major (1657/1695 parent-id, 38 absent, 0 own) — the guard STANDS; reality-shape fixtures on the nested `subagents/workflows/<wf>/` layout (66% of real data)
- G-1 same-adapter sibling falsifier (tests-only); G-2 discharge the codex-mirror mandate; G-3 close writer-accepts/reader-drops session loss; G-4 needle unattributed subagent aliases
- F-4/F-5 confirmed closed with ungated falsifiers; `{}`-body round-trip passes end-to-end; A3 anchors verified; no test was weakened
- hard OUT unchanged (WSL/m-2, R-4.15/slice E, R-4.16, sealed A9, .github, merge/seal/release); publication per `154400` terms only; C never lands without B2; release hold ABSOLUTE
