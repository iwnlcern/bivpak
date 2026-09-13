## SITREP — R-4.49 AUDIT OPENED (`intg-r449/AUDIT-pair-planner-20260913-165304.md`, TO the implementer for the independent pass) and TWO CONFIRMATIONS ROUTED UP to m-2 through you, both S-LS-1/S-LS-2 by the fence's own words, both cheap because m-2's own texts already answer them: C-1 CLAUDE — the fence's DETERMINING TEXT quotes c1 §3 "reads `cwd` from line 1", but m-2's ADDENDUM 1 §A1 (M06, SEAL-READY, `../../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md`) SUPERSEDED that sentence with STREAM-SCAN-TO-FIRST-CWD (stop at first hit; whole file when none → `no_cwd_record`) — which is what the code does today and what the real store requires: MEASURED at this seat, structure only, 2 of 100 real transcripts carry cwd on line 1; the first cwd-bearing record sits at lines 3–9 for 76 of them (worst line 106; up to 15.5 MB in); the on-disk fixture has the same metadata-first head. A literal line-1 or fixed-byte head bound on claude would DROP sessions — a V-LS-2 membership delta — so the ask is m-2's CONFIRMATION that A1 §A1 governs the claude side of this act and the bound is "the first cwd-bearing record, the whole file when none" (unparseable lines skipped as today); any other answer is m-2's ruling, never the lane's. C-2 CODEX — c1 §4 and A5 §A5.4-CX say line 1 == `session_meta`; 1,503 of 1,503 real rollouts agree (line-1 bytes max 22,552); the code's rule is "the first `session_meta` record" — the ask is m-2's CONFIRMATION of that as the bound (identity with today's parser) rather than a fixed byte cap. THE ACT'S SHAPE, from the audit: both adapters read every store file WHOLE by `source_text` BEFORE inspecting its head facts (`claude_code.cpp:654-658`, `codex.cpp:1273-1276`) while the head parsers already stop at the first hit — so R-4.49 is a READ-BOUNDING change with no selection change: a streaming head reader in each adapter over the existing `secure_io::ReadHandle::stream` (which aborts on a sink error and re-reads from offset 0 — no byte outside the fence), stop conditions IDENTICAL to today's parser exits (every SessionRecord field byte-identical, not only membership), full reads only for selected sessions + descendants (V-LS-4); S-LS-3 fires for no warning (`no_cwd_record` needs the whole file scanned and the reader reads to EOF when no cwd appears; the other warnings come from enumeration/head facts/sqlite); S-LS-4 dormant (m-3 C-2 rule 5); V-LS-3 untouched. SEQUENCE FROM HERE: the implementer's independent audit → reconcile → the PLAN with a NEW identity `intg-r449-line1-selection-plan-…` against the fence rev2 design block (the canonical edge measured root-mode ONCE at plan time as your gate asks; the operator's no-sweeps rule otherwise stands) with the R-4.50 lessons as plan terms (fresh branch + worktree from `4cf135ee`; the `-v2` worktree disposed at Task 0 with a receipt; census at the branch head and at the merge head with population + reduction + `LC_ALL=C` pinned; the synthetic store disclosed; R-4.53 arm (a); m-3's five rules on the instrument; the three-leg witness as tests; one commit; PR against `main`) → exact-hash review → the token ONLY after m-3's settle word is on the record → implement → verify → m-2's byte review at the sha → packet → the operator's token → landing. Nothing is asked of the operator; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-r449-line1-selection
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md
RELATED_CONTEXT: intg-r449/AUDIT-pair-planner-20260913-165304.md; ../../pdc/master/relays/intg-r449-line1-selection-act/PLAN-master-planner-20260913-164219.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-142000.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260903-143638.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-04-ADDENDUM-1-adapter-remediation.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-12-ADDENDUM-5-codex-tiered-verdict.md; ../../pdc/master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260903-152118.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — m-2's two confirmations (through you) and m-3's settle word precede any token; no plan filed yet, no branch, no product byte; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner, intg.pair-implementer
SUBJECT: SITREP — R-4.49 audit opened (AUDIT-pair-planner-20260913-165304.md); two confirmations to m-2 through you: C-1 claude — A1 §A1's stream-scan-to-first-cwd governs (the fence quotes §3's "line 1"; measured 2/100 real transcripts have cwd on line 1, first cwd at lines 3-9, worst 106, up to 15.5 MB in; a fixed head bound = V-LS-2 delta), bound = first cwd record / whole file when none; C-2 codex — bound = the first session_meta record (1503/1503 on line 1, max 22,552 B); the act = read-bounding via an in-fence streaming reader over secure_io stream (aborts on sink error, re-reads from 0), stop conditions identical to today's parsers; S-LS-3 none; plan follows the implementer's pass + m-2's words; token after m-3's settle
REPO: `../bivpak` READ-ONLY (product bytes == origin/main 4cf135ee; local HEAD 26f94e3 docs-only); `../pdc` READ-ONLY (fence rev2 == f2216ee6; A1 df523d97…); the real host stores READ for structure only (no value in any output); no draft, no scout, no product byte
BRIDGE: intg.pair-planner → master.master-planner (route C-1/C-2 to m-2.planner; m-3's settle word is the token gate you named — nothing else owed by you); m-2 seats CC (the asks are confirmations of your own A1/A5 texts against the fence's §3 quote; your ruling if you read them otherwise); m-3 seats CC (your five rules bind the instrument; your settle word gates the token; S-LS-4 dormant by your own rule 5); m-4 CC (the act only reads less); intg.pair-implementer CC (the audit is yours to reconcile); operator CC (visibility; nothing asked)

ACTIONS_GIT_REF: docs-lane writes only — the audit, this SITREP and the ROADMAP bullet committed path-scoped (INDEX rows additions only), no trailer; no product byte, no branch, no token, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file).
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> master.master-planner
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/intg/intg-r449/
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-WAVE-A-REVERIFY-STAGE1-INDEPENDENT-STOP-CORROBORATION-20260820-161626.md
?? .relays/s4/s4-matrix/SITREP-implementer-20260825-220111.md
?? docs/sprints/2026-08-04-s4-step4/MIGRATION-adt-skills-2.9-20260816.md
?? relay-draft-intg-task4-stop.md
Literal `git status --short` of the docs lane at write time (inherited S4 rows and inherited untracked files included as printed); the shared INDEX carries sibling-authored rows not claimed clean here.
