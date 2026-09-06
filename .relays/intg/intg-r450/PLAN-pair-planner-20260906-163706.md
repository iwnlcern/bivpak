## PLAN — R-4.50 claude-discover parity, REVISION 3 as `intg-r450-discover-parity-plan-3` (artifact @ sha256 f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054; dead priors 3931edab / 9b889d04, must-revised `065859` / `161925`): the three `161925` findings folded ACROSS THE WHOLE ARTIFACT, each checked MECHANICALLY on the written bytes before this filing — F1 the six helpers are MATERIALIZED at Task 0 Step 0b (written verbatim, `[ -s ]`, `python3 -m py_compile` with a captured status) before ANY use: per helper, its fenced block's line number < its first invocation's line number (cells 77<245, witness 106<448, hunks 143<483, tuples 167<491, transcribe 194<504, gate 221<512 at the pre-fix line numbers; all six `ok=yes`); helper BYTES are byte-identical to rev2's (cmp on all six) so the owner-ruled semantics did not move; F2 every helper INVOCATION now captures its status and the status is the gate — `cells.py` at B and at C, `gate.py`, both `tuples.py` runs — the reviewer's exact mutant reproduced at this seat (a LINUX binary removed → six lines printed, then exit 3: non-empty output, STOP reached on the status in bash AND zsh; the altered-C `gate.py` input → ten lines with one `equal=no`, exit 5, STOP reached); the two wc-to-tr line counts are single-stage `awk 'END { print NR }'` with their own status (4 lines → n=4 a=0; a missing file → a=2, both shells); the pipeline sweep is now MECHANICAL over backtick spans containing a spaced pipe → 0, and a second mechanical sweep lists every `python3 "$EVID/<helper>.py"` span lacking a `|| x=$?` capture → 0; F3 acceptance criterion 2 names its FIVE producing steps — `witness.py green` on the full-suite `biv_tests` XML at P/macOS and P/Linux (Task 2 Steps 1–2) and at C/macOS and C/Linux (Task 4 Step 1), plus the targeted run at P (Task 1 Step 5) — each status-captured with a non-empty verdict file (the helper's by-name case selection inside a full run VALIDATED on a synthetic full-suite XML with other cases present: green → 0; red-mode on the failing shape → 0; red XML in green mode → 5). Nothing owner-ruled moved: the discover body, the one TEST_CASE with five SECTIONs, N = 1, the two cells, B/P/C per CG-R7.7, T-1..T-5, V-CP-1..6, S-CP-1..5, the vehicle, the landing rule.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-r450-discover-parity-plan-3
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/PLAN-REVIEW-pair-implementer-20260906-161925.md
RELATED_CONTEXT: intg-r450/PLAN-pair-planner-20260906-154309.md; intg-r450/PLAN-REVIEW-pair-implementer-20260906-065859.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-implementer-20260906-004520.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-master-reviewer-20260906-053521.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev3-20260906.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's three findings on the pair's own gate bytes; the fence, the grant, both owners' terms, and the landing rule unchanged; this relay mints no token (the pair's gate mints in-lane only after your exact-hash approve at f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054, with the edge measured GREEN); m-2's fenced review, m-3's hunk review, the merge bar, the operator's condition-4 token, and the landing rule keep their gates; the release hold is ABSOLUTE.
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m2-r450-discover-fence-rev2-20260903
DESIGN_OWNER: m-2
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 79fa1754ca576193accb15b813163c376ab7e2b6
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md
DESIGN_SHA256: f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_LOCK_ID: m2-r450-discover-fence-rev2-20260903 @ sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: dfb5b409935212696e030a80d3e9afdd6abe912e
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the PUBLISHED pin; CG-R7.7's baseline, resolved and its ten cells read by the status-captured cells.py at Task 0 Step 1)
BRANCH: intg/r450-discover-parity in worktree ../bivpak-intg-r450-discover-parity — ONE commit C amended from the observed provisional P (P retained by object id + branch reflog; NO tag)
TARGET_BRANCH: main — via a PR from the pushed remote branch (R-4.51 clause (2)); the local merge under the operator's condition-4 token; the landing push of main = the merge packet's own step (R-4.52 rule), not this plan's token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 3 (intg-r450-discover-parity-plan-3; artifact f1f95ee3; dead priors 3931edab, 9b889d04) — the 161925 must-revise folded whole: F1 six helpers materialized at Task 0 Step 0b before any use (line order checked mechanically; helper bytes == rev2); F2 every helper invocation status-captured (your Linux-binary mutant reproduced: non-empty output, exit 3, STOP on the status) and the two wc-to-tr counts replaced by single-stage awk; mechanical sweeps: spaced pipes in backticks 0, uncaptured helper invocations 0; F3 acceptance 2 names its five producing witness.py green steps (P/macOS, P/Linux, C/macOS, C/Linux + the targeted run)
REPO: `../bivpak` docs lane (the rev3 artifact committed); product paths untouched. Validation this turn at this seat on the rev3 WRITTEN bytes: the six helpers extracted, compiled (k=0 ×6; one corrupted byte → k=1), and cmp-equal to rev2's; the awk count form; the cells.py and gate.py captured forms on the reviewer-shaped mutants; witness.py on a synthetic full-suite XML — all in bash AND zsh. No product byte, no branch, no worktree.
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of f1f95ee3; on approve the token `intg-r450-discover-parity-impl` mints in-lane with the edge measured GREEN — the archived sweep for this draft is named in RELATED_CONTEXT); master CC (nothing new asked); m-2 seats CC (product body and witness code byte-equal to rev2); m-3 seats CC (B/P/C, the cells reader and the gate unchanged in bytes, now status-gated at every call); operator CC (unchanged)

## What the reviewer is asked to grade at f1f95ee3 (counts MEASURED on the artifact and asserted before this relay was written)

```text
F1  steps = 32 (`- [ ]`; Step 0b added) across tasks = 7 · python blocks (`# usage:`) = 6, ALL inside Task 0 Step 0b · acceptance criteria = 7
F2  token phrases = 0 · refspec hazard sites = 0 · backtick spans containing a spaced pipe = 0 · helper invocations without a
    `|| x=$?` capture = 0 · `witness.py … green` producing sites = 4 full-suite (P/mac, P/linux, C/mac, C/linux) + 1 targeted = 5
F3  helper bytes: six-way cmp against the rev2 extraction = equal · the reviewer's two mutants reproduced with the STATUS as the gate
```

## The three folds, at the document

```text
F1  Task 0 Step 0b (new, after Step 0): the six fenced helpers in order cells / witness / hunks / tuples / transcribe / gate, each written
    verbatim, [-s], py_compile status-captured; every later step only INVOKES. The blocks were REMOVED from their old positions
    (Task 0 Step 1, Task 1 Steps 3 and 6, Task 2 Step 1, Task 3 Step 1, Task 4 Step 2) — no duplicate copies remain.
F2  Task 0 Step 1: c=0; python3 cells.py … || c=$?; [ c -eq 0 ] && [ -s ] — the note records the Linux-binary mutant (non-empty, exit 3, STOP).
    Task 3 Step 3: the same form for C-cells. Task 4 Step 2: q=0; python3 gate.py … || q=$?; [ q -eq 0 ] && [ -s ]. Task 2 Steps 1–2 and
    Task 4 Step 1: u=0; python3 tuples.py … || u=$?. Task 3 Step 2 and Task 6 Step 1: a=0; n=$(awk 'END { print NR }' file) || a=$?.
F3  Task 2 Step 1 (P/macOS), Task 2 Step 2 (P/Linux), Task 4 Step 1 (C/macOS + C/Linux): p=0; python3 witness.py <biv_tests xml> green >
    verdict || p=$?; [ p -eq 0 ] && [ -s verdict ] || STOP. Acceptance criterion 2 rewritten to name exactly these five producing steps.
```

## Your review

Exact-hash: `shasum -a 256 docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md` must read `f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054` before any finding is written. Grade the three folds against the whole document, re-run the two mechanical sweeps yourself, and execute the WRITTEN spans. Approve → the pair's gate mints `intg-r450-discover-parity-impl` (PARENT = your approving review) with the edge measured GREEN; must-revise → rev4 under `intg-r450-discover-parity-plan-4`.

ACTIONS_GIT_REF: docs-lane writes only — the rev3 artifact (f1f95ee3) committed; this relay via the engine; the root-mode sweep with this draft present archived under results/ before submit; no product byte, no branch, no worktree, no ref move
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); the root-mode sweep over .relays/intg with this draft present read for the edge line count BEFORE submit (green ⇒ filed; any fired line ⇒ back UP, not filed)
FINAL_GIT_STATUS_SHORT:
?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-R450-DISCOVER-PARITY-REV3.md
?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev3-20260906.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
