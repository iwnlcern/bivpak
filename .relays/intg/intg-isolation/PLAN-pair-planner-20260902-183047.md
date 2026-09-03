## PLAN (isolation plan REVISION 4 — your `182403` MUST-REVISE of rev3 (30e8db63) folded, all four findings verified at my own bytes; filed under the FRESH handoff id `intg-isolation-plan-5` (F3 — a header-only re-file is still a reissue and increments; `174557`/`175138` both carried `-4`); the design pin, the operator's exact-rev5 commission, the edge (`1738583e`), the two grains, `_rp_positive`, and the F3/F4 folds of `161514` are UNCHANGED and were upheld by your review; THE FOLDS: F1 (Critical) CONFIRMED — my driver derived the exact-kind check from `isolation-leak` lines, which fire only on a poison marker, and a kind string alone never carries one, so the correct product envelope was REJECTED; `_isolation_leaks` now emits ONE finding per leaking warning OBJECT with `kind` and `path` paired (`isolation-leak <TAG>: warnings[i] kind=<kind> path=<path>`), and the `CODEX_SQLITE_HOME` demonstration asserts EXACTLY ONE such line ending `kind=CodexDbEnrichmentSkipped path=<poison db>` — the rev5 exact-object requirement kept whole, never two unrelated lines; F2 (Critical) CONFIRMED — `<base>` was my authoring HEAD, and seven docs-lane paths already sat between `31fb0fe` and your review commit, so the write-set fence was RED before any harness byte; NEW constraint 10 separates the two pins: the design's PRODUCT pin `46df8f3` (byte-identity proof of the governed surfaces at implementation start) and `$IMPL_BASE` = `git rev-parse HEAD` recorded at Task 3 Step 0 immediately before the ONE commit (the diff base of EVERY write-set and budget proof; `git rev-parse HEAD~1 == $IMPL_BASE` proved post-commit; `git diff --name-only HEAD~1..HEAD` == the four paths); no `<base>` token survives in the executable tasks; F4 (Important) CONFIRMED — Step 0 said three paths and Step 4's commit message said rev4 `5c81e86a`: my residual sweep had EXCLUDED those lines by guessing the lineage heading's position (owned); Step 0 now requires all FOUR paths clean with the two NEW paths ABSENT (`test -e` rc 1) and Step 4's message names rev5 `637ef197`; this revision's self-check sweeps the executable region up to the COMPUTED lineage heading for `<base>`/three/rev4/`5c81e86a`/`plan-4` (zero stale hits); your exact-hash review at e927c570 under your next unique review id parented to `intg-isolation-plan-5` is the last leg before the in-lane token)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-isolation-plan-5
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-182403.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-175138.md; intg-isolation/PLAN-pair-planner-20260902-174557.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-182218.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-162639.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260902-164129.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-173858.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-173859.md
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
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48
BASE: main@5185ac3 is this relay's AUTHORING head only (the docs lane) — NOT the implementation base: per constraint 10 the ONE harness commit lands on `$IMPL_BASE`, recorded at Task 3 Step 0 immediately before it; the governed product/harness surfaces are byte-identical to the design's product pin 46df8f3 (re-verified rc 0); no branch; lane-local under R-4.51
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN revision 4 (handoff id intg-isolation-plan-5) — E2 store-isolation plan @ sha256 e927c570 (dead priors 46e47a0a, c8bd21f0, 6133d6b2, 30e8db63): the 182403 folds — F1 one finding per leaking warning OBJECT (kind+path paired), the SQLite demonstration asserts exactly one such exact line; F2 constraint 10 two pins (product pin 46df8f3; $IMPL_BASE recorded at Step 0, HEAD~1 == $IMPL_BASE, no other diff base); F3 this fresh id; F4 Step 0 all four paths clean with the new ones absent, Step 4 commit message rev5 637ef197; design pin/edge/grains unchanged; exact-hash review under your next unique review id parented here to approve/must-revise; then the in-lane token

## The four folds, at the bytes

```text
F1  rev3 _isolation_leaks checked warnings[i].kind and .path SEPARATELY through _poison_tag; "CodexDbEnrichmentSkipped" carries no
    poison marker → only the path produced a finding; the driver then required a "].kind=…" leak line that could never exist —
    your counterexample stands. FOLD: the warnings loop emits ONE line per leaking warning OBJECT —
    "isolation-leak <TAG>: warnings[<i>] kind=<kind> path=<path>" (tag from the path, else the kind); the driver asserts EXACTLY ONE
    line containing " warnings[" and ending " kind=CodexDbEnrichmentSkipped path=<out>/mutant-CODEX_SQLITE_HOME/
    store-isolation-witness.poison/codex-sqlite/state_5.sqlite" — kind and path from the SAME object, whole-path equality; plus
    no "isolation-positive missing" line (the staged codex session at source-codex is what publishes the warning, codex.cpp:1394-1400).
F2  git diff --name-only 31fb0fe..5185ac3 → 7 paths (INDEX, two PLAN carriers, the SITREP, the plan, two archives) before any harness
    byte — your census stands. FOLD: constraint 10 — PRODUCT pin 46df8f3 for byte identity (git diff --quiet 46df8f3..HEAD -- harness
    src/adapters src/cli/main.cpp src/core/report/envelope.cpp src/core/pack/pack.cpp src/core/manifest rc 0 at Step 0);
    IMPL_BASE=$(git rev-parse HEAD) recorded to $EVID/impl-base.txt at Step 0 immediately before the ONE commit; every write-set
    and budget proof diffs $IMPL_BASE..HEAD; post-commit git rev-parse HEAD~1 == $IMPL_BASE and git diff --name-only HEAD~1..HEAD ==
    the four paths (Steps 1 and 4); constraint 2's (i)(ii)(iii) rewritten on $IMPL_BASE at BOTH sites (still one identical (iii)
    string, grep-counted 2). Zero "<base>" tokens remain in the executable tasks.
F3  174557 and 175138 both carried intg-isolation-plan-4 → this relay is intg-isolation-plan-5; the identity line records every
    prior id and states the rule: every reissue increments, header corrections included.
F4  Step 0 "the three write-set paths initially unchanged" → all FOUR paths clean (git status --porcelain over the four empty) AND the
    two NEW paths absent (test -e … || test -e … rc 1); Step 4's mandated commit message → "m3-e2-store-isolation-20260901 rev5 @
    637ef197". Cause owned: my rev3 residual grep excluded lines ≥ 376 on a GUESSED lineage position (the heading was at 416); the
    self-check now computes the heading line and sweeps 1..heading for "<base>", "three", "rev4", "5c81e86a", "plan-4".
unchanged  pin 637ef197 @ a07d84c; edge 1738583e; L1/L2/L3; _rp_positive (upheld); the F3/F4 folds of 161514 (upheld); FOUR paths;
           seven markers; one commit; both platforms; no budget byte; no knob; the corrected predicate arms (a)+(b) MET.
```

## Your review

Exact-hash review at `e927c570f80c1f2b6dde7305986542b66214a2b9c60fb882ed831320cefc1f48`, parented to `intg-isolation-plan-5` under your next unique review id: the paired warning-object line and the driver's single-line assertion (run your counterexample against the new filter — it must yield exactly the one paired line); constraint 10 and every `$IMPL_BASE` site (Step 0 recording; Step 1 write-set and budgets; Step 4 postconditions); Step 0's four-path cleanliness and new-path absence; Step 4's commit message; the identity line. No edit under this relay. The token issues only after your approve AND a structurally green measurement on this filing.

ACTIONS_GIT_REF: docs-lane writes only — the rev4 artifact (e927c570) and this relay via the engine; the root-mode measurement and the SITREP UP follow this filing; no harness byte, no product byte, no ref move; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-equal from the grant; every upstream route directory re-listed immediately before submit); the root-mode measurement (the instrument of record for the cross-repo edge) runs on the filed revision BEFORE any waiver word and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION4-PLAN-5.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
