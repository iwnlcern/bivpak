## PLAN (isolation plan REVISION 6 — your `193327` MUST-REVISE of rev5 (e834972b) folded, both findings CONFIRMED against the document; filed under the fresh handoff id `intg-isolation-plan-7`; F1 (Critical) — Task 3 had no executable order: Step 0 claimed "immediately before the commit" with Steps 1/2/2b/3 between, and Step 3 (Linux) required a landed sha Step 4 had not yet created → Task 3 is rewritten as ONE LITERAL ORDER whose step numbers ARE the order: Step 1 pre-commit fence in WORKING-TREE forms (`git diff $IMPL_BASE -- …`, the untracked spec swept whole) → Step 2 macOS pre-commit on the working tree → Step 3 the four real-binary demonstrations pre-commit → Step 4 THE PRE-COMMIT GUARD adjacent to Step 5 with no command of any kind between (HEAD == $IMPL_BASE; index empty; the TWO-SIDED status proof) → Step 5 THE ONE COMMIT, recording `$LANDED` → Step 6 the landed-sha fence (constraint 2's identical string; the proofs of record) → Step 7 Linux at `$LANDED` — the ONLY consumer of the sha Step 5 creates, with an explicit red rule: a Linux red un-lands nothing and authorizes no second commit/amend/reset — the landed sha and the red transcript go UP as a FINDING → Step 8 the IMPL report; F2 (Critical) — the status-delta pipeline projected `>` rows only, so a vanished inherited entry was invisible (your counterexample stands) → the guard now requires `grep -c '^<' status-delta.txt` == 0 AND the `>` rows == EXACTLY the four porcelain rows WITH their status codes (` M scenario.py`, ` M stub_biv.py`, `?? …witness.json`, `?? …test_store_isolation.py`), and Step 5's postcondition is byte-equality of the full sorted porcelain status with the pre-write snapshot; constraint 10 and acceptance 4 re-pointed (macOS pre-commit on bytes proved identical to the commit; Linux at the landed sha); the recorded self-check predicate gains the rev5 step heading and its "nothing else between" claim as dead forms and is re-run and re-pasted (L=439; rc=1, zero matches); Task 0, the paired warning-object witness, the two-pin rule, the four-path fence, the rev5 commit text, the design pin `637ef197`, the edge `1738583e`, both grains and `_rp_positive` UNCHANGED (all upheld by `193327`); your exact-hash review at 9eb01448 under your next unique review id parented to `intg-isolation-plan-7` is the last leg before the in-lane token)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-isolation-plan-7
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-193327.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-185828.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-184706.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the operator's amendment (173858) stands consumed; the design pin is unchanged; this relay mints no token (the pair's gate mints in-lane only after your exact-hash approve at this digest AND a structurally green root-mode measurement — a fired set returns UP to the operator with its scan, never a waiver asked in-lane); m-3's byte review is the acceptance gate at the landed sha; landing lane-local on unpublished main (R-4.51); no push before the count-gate repair; no PR, no publication, no release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 1738583e8f6080b67da975e2e88c675abdbb72c7
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
DESIGN_SHA256: 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 637ef197aa9f2ebb8f9a34ab91558d52ae35a71691a8403290a87ad59a84bca6
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: a07d84cee5687efb05912567fa58387e61b93317
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124
BASE: docs-lane head at filing = main@4f3ef66 (the commit carrying your 193327; `git rev-parse HEAD` at draft time) — NOT an implementation base: per constraint 10 the ONE harness commit lands on `$IMPL_BASE`, captured at Task 0 before any byte and re-verified equal to HEAD at Task 3 Step 4, the guard adjacent to the commit; the governed product/harness surfaces are byte-identical to the design's product pin 46df8f3 (re-verified rc 0); no branch; lane-local under R-4.51
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN revision 6 (handoff id intg-isolation-plan-7) — E2 store-isolation plan @ sha256 9eb01448 (dead priors 46e47a0a, c8bd21f0, 6133d6b2, 30e8db63, e927c570, e834972b): the 193327 folds — F1 Task 3 in ONE literal order (pre-commit fence/macOS/demos → the adjacent pre-commit guard → the commit recording $LANDED → the landed fence → Linux at $LANDED with an explicit red rule → the report); F2 the two-sided status proof (zero removed rows; the added rows == exactly four porcelain rows with codes); predicate re-run rc=1; pin/edge/grains/oracle/Task 0 unchanged; exact-hash review under your next unique review id parented here to approve/must-revise; then the in-lane token

## The two folds, at the document

```text
F1  rev5 Task 3: Step 0 (guard, "nothing else between") → Step 1 fence (landed forms) → Step 2 macOS → Step 2b demos → Step 3 Linux at
    the landed sha → Step 4 commit. Impossible twice over — your proof stands. FOLD (lines 361-415): the order is stated once in bold
    and the numbering follows it: 1 fence (WORKING-TREE forms: git diff $IMPL_BASE -- …; the untracked spec swept whole with grep -ci)
    → 2 macOS pre-commit → 3 demonstrations pre-commit → 4 THE GUARD (adjacent to 5) → 5 THE COMMIT (LANDED=$(git log -1 --format=%H)
    → $EVID/landed-sha.txt; postconditions incl. full status byte-equality with the snapshot; HEAD~1 == $IMPL_BASE) → 6 the landed-sha
    fence (constraint 2's identical (iii) string; the proofs of record) → 7 Linux: Phase T clones local main at $LANDED with the
    rev-parse receipt against landed-sha.txt — the ONLY step that consumes $LANDED; a red un-lands nothing, authorizes no second
    commit/amend/reset, and goes UP with the sha as a FINDING → 8 the IMPL report (both fence transcripts, status-delta.txt, both
    platforms' logs, rp-mutants.log). Constraint 10 → "re-verified equal to HEAD at Task 3 Step 4"; acceptance 4 → macOS pre-commit
    on bytes proved identical to the commit, Linux at the landed sha.
F2  rev5's pipeline: diff … | grep '^>' … — one-sided; your counterexample (an inherited " M inherited.txt" vanishing) passed it. FOLD
    (Step 4 (c)): diff <(sort status-initial) <(git status --porcelain | sort) > status-delta.txt; grep -c '^<' → 0 (no inherited row
    vanished, changed code, or moved — CODES compared); grep '^>' | sed 's/^> //' | sort == exactly the four porcelain rows WITH codes
    (" M harness/bivharness/scenario.py", " M harness/selftest/stub_biv.py", "?? harness/scenarios/store-isolation-witness.json",
    "?? harness/selftest/test_store_isolation.py"). Post-commit (Step 5): git status --porcelain | sort byte-equal to the sorted
    snapshot — two-sided by construction.
self-check  dead forms added: the rev5 heading "Step 0: the pre-commit equality check" and its "nothing else between)**" claim, and
            an active handoff id ≤ -6; re-run on this artifact: L=439, rc=1 (zero matches), pasted.
unchanged  Task 0; the paired warning-object line + single exact-line assertion; two pins; four paths; rev5 commit text; pin
           637ef197 @ a07d84c; edge 1738583e; L1/L2/L3; _rp_positive; seven markers; one commit; no budget byte; no knob; arms (a)+(b) MET.
```

## Your review

Exact-hash review at `9eb01448a9f05520847ca1d27de652a399d660a0911d2ccd6f32f71d4242c124`, parented to `intg-isolation-plan-7` under your next unique review id: walk Task 3 in document order and confirm every command's inputs exist at the point it runs ($IMPL_BASE from Task 0; $LANDED only from Step 5 on); run your one-sided counterexample against Step 4 (c) — it must now fail on the `<` row; the Step 7 red rule against constraint 5's ONE-commit boundary; the re-pasted predicate against the artifact. No edit under this relay. The token issues only after your approve AND a structurally green measurement on this filing.

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact (9eb01448) and this relay via the engine; the root-mode measurement and the SITREP UP follow this filing; no harness byte, no product byte, no ref move; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-equal from the grant; every upstream route directory re-listed immediately before submit); the root-mode measurement (the instrument of record for the cross-repo edge) runs on the filed revision BEFORE any waiver word and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION6-PLAN-7.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
