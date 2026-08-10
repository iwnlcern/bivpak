## SITREP — R-4.8 lens-fold re-check COMPLETE at `d234314`: FIVE of the six human-lens must-fixes land and are confirmed at depth (hermeticity closed against the PRODUCTION input set; the decoy falsifier structurally genuine; the pre-fold live-pack hole CLOSED) — but the lens caught the V1 non-vacuity guard being ITSELF unfalsifiable (two false witnesses: the workspace directory name and the sealed JSON key; literal uncoupled from the carrier) plus a missing zero-row post-state; a bounded TEST-ONLY micro-fold is chained (PLAN riding this commit) — the merge hand-up waits on its pass

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-lensfold-check-verdict
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-lensfold-impl-complete
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this relay — the micro-fold is test-only pair scope via the established two-edge chain (its PLAN rides this commit); the merge hand-up (six-fold proof + end-state-bytes condition-3 + condition-4) waits on the micro-fold's verification pass; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — lens-fold check verdict: 5/6 landed deep, V1's guard must be re-proven; micro-fold chained; one residual recorded for the registry

## Check result

Record (verbatim lens report + lead verification + synthesis):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-lensfold-check-d234314.md`
(SHA-256 `eb187d093c9daa352519bce376dd7a35c054faf692a1b136e8570028c05a8ab6`, sealed
after creation). Single owning lens per the approved sizing; 1 spawn = 1 finding-set +
0 stalls. The lens disclosed and corrected its own method error mid-pass (first grep
landed on the main working tree; every reported fact re-read from the `d234314` blobs).

CONFIRMED AT DEPTH: H1/H2 hermeticity is real — all 16 pack call sites guarded, the
four-variable set closed against PRODUCTION (`getenv` grep across src at the head, PATH
excluded by call-graph), restore/unwind/aliasing clean, the two-tier codex intent
preserved, `require_store_roots_under` sound on symlinked macOS temp paths and invoked
after every successful report; the constructed decoy is a genuine RED-before/
GREEN-after falsifier discovered through the real codex home tier; V2, V3, O1, BR1 all
correctly implemented; and Lens B's original live-pack hole is CLOSED — before this
fold the happy-path pack test walked the operator's real HOME and CLAUDE_CONFIG_DIR.

## The two micro-fold items (chained, test-only)

**MFX-1 (Critical — gates):** the V1 non-vacuity guard cannot fail: `find("/ws")` over
installed content is satisfied by the restore workspace directory literally named
"workspace" AND by the sealed never-rewritten `"/ws/proj"` JSON key — and the literal
is uncoupled from the carrier (a `/zz` carrier leaves it green). The INPUT half of V1
landed (the fixture is genuinely carrier-rooted); the PROOF half is a second
unfalsifiable box — the same shape the human lens originally flagged, one level up,
which is exactly why this re-check ran. Fix per the lens: hoist `kEngagedCarrier`,
assert the record origin as a strict prefix match and the INPUT member bytes in their
encoded spelling — neither false witness can satisfy those; any post-install search
must exclude the workspace path. Lead re-verified both false witnesses at the bytes
before chaining. **MFX-2 (Medium):** the decoy block's post-state is two universally
quantified assertions over an expected-EMPTY vector — add the file's own explicit
`CHECK(report->agent_sessions.empty())`. Optional tier: decoy SECTION/CAPTURE
attribution; ORACLE provenance-sha wording.

The micro-fold PLAN (`…144720`, riding this same commit, Edge 1 → the rev6
DESIGN-REVIEW) is with the Implementer for PLAN-REVIEW; the token follows the approve
(Edge 2); then a verification sized to the ~2-file delta (lead + tests).

## For the registry (master CC'd)

Lens Finding 5 (Low, recorded): the degenerate-HOME matrix rows leave codex's home
tier resolving a CWD-relative `.codex` — production composes `env.home / ".codex"`
from a deliberately degenerate HOME, un-neutralizable by the env fixture; the failure
direction is loud (the new guards catch contamination), not silent. Joins the T-2
family already with master.

Carried unchanged: published PR #24 untouched at `2341667` (the fold commits sit
locally on top pending the merge hand-up's republish decision); decided cells stand
(zero-session capture (b); A-obs-2 registered); Docker sizing per the approve; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this SITREP + the micro-fold PLAN + the sealed check record + their INDEX rows ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; branch/PR untouched by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-144720 before these relays + INDEX writes; the two relays, two INDEX rows, and the record are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-LENSFOLD-CHECK-FIVE-OF-SIX-MICRO-FOLD-20260810-144720.md` → TO `s4.orchestrator-planner`
- check record `eb187d09…` at `d234314` → 5/6 must-fixes confirmed at depth; MFX-1 (V1 guard unfalsifiable — two false witnesses, uncoupled literal) + MFX-2 (decoy zero-row) gate; micro-fold PLAN chained this commit
- F5 CWD-relative codex home tier on degenerate rows → registry (T-2 family)
- merge hand-up waits on the micro-fold verification; PR #24 untouched; release hold ABSOLUTE
