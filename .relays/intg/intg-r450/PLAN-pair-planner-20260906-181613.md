## PLAN — R-4.50 claude-discover parity, REVISION 4 as `intg-r450-discover-parity-plan-4` (artifact @ sha256 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e; rev3 f1f95ee3 APPROVED `165625` and its token `intg-r450-discover-parity-impl` CONSUMED at your Task 0 Step 5 STOP `175211`): the STOP is PAIR-OWNED — the observer environment, not a fence surface — and rev4 folds it as content, not as a retry. Cause, re-derived at my seat: the isolated worktree has no `.venv-harness`, so `harness/CMakeLists.txt:12-20` fell through to Homebrew Python 3.14.6 without `jsonschema`/`zstandard` (your ten collection errors; rc2=8); the main checkout and the 2a worktree carry the venv, which is why the same discriminator was green at both reviewers' seats and at the count-gate's run. rev4 adds Task 0 Step 3b — provision the worktree's harness venv EXACTLY as CI does (`s2-harness.yml:14-17`: `/opt/homebrew/bin/python3.12 -m venv .venv-harness` + `pip install -r harness/requirements.lock`, module proof for the three names, statuses captured) into the IGNORED path `.venv-harness/` (`.git/info/exclude:8`, shared by every worktree) — with the check-ignore query in its TRAILING-SLASH form, because the exclude pattern is directory-only and the no-slash query on the ABSENT path returns 1 (MEASURED in a scratch repo and at your retained worktree, both shells: absent+no-slash 1, absent+slash 0, existing dir 0 — a defect my first rev4 draft carried and the written-bytes execution caught); and Task 0 Step 4 now configures into a FRESH build directory because `BIVHARNESS_PYTHON` is a CMake CACHE entry — re-configuring the existing `build/ci-macos` KEEPS the 3.14 fallback (MEASURED on a scratch harness configure: same build dir after the venv appeared → still 3.14; fresh build dir → the venv python) — with the CMakeCache `grep -c` proof as the gate (k=1 on the venv cache, k=0/g=1 → STOP on the 3.14 cache, both shells). Task 0 Step 2 becomes CREATE-or-VERIFY so your clean worktree at B is kept, not re-created; Step 5 runs the discriminator ONCE under rev4's token as a NEW execution (the 175211 run is consumed and cited). Nothing else moved: helper bytes, the discover body, the witness, B/P/C, the vehicle, the landing rule — the six helpers cmp-equal to rev2/rev3.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-r450-discover-parity-plan-4
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/SITREP-pair-implementer-20260906-175211.md
RELATED_CONTEXT: intg-r450/IMPL-pair-planner-20260906-173252.md; intg-r450/PLAN-REVIEW-pair-implementer-20260906-165625.md; intg-r450/PLAN-pair-planner-20260906-163706.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-004023.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260906-015102.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md; ../../pdc/master/relays/intg-r450-discover-parity-act/DESIGN-REVIEW-implementer-20260906-004520.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev4-20260906.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's own STOP on the pair's own observer-environment gate; no fence surface, no owner term, no ruling touched; this relay mints no token (the pair's gate mints `intg-r450-discover-parity-impl-2` in-lane only after your exact-hash approve at 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e, with the edge measured GREEN); m-2's fenced review, m-3's hunk review, the merge bar, the operator's condition-4 token, and the landing rule keep their gates; the release hold is ABSOLUTE.
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the PUBLISHED pin; your 175211 resolved and recorded it; product diff 0)
BRANCH: intg/r450-discover-parity in worktree ../bivpak-intg-r450-discover-parity — EXISTS at B, clean, no P (your 175211 retained it; rev4 Task 0 Step 2 VERIFIES it instead of re-creating); ONE commit C amended from the observed provisional P; NO tag
TARGET_BRANCH: main — via a PR from the pushed remote branch (R-4.51 clause (2)); the local merge under the operator's condition-4 token; the landing push of main = the merge packet's own step (R-4.52 rule), not this plan's token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 4 (intg-r450-discover-parity-plan-4; artifact 6ebbfa42; rev3 f1f95ee3 approved, its token consumed at your 175211 STOP) — the Task 0 venv STOP folded as content: Step 3b provisions the worktree's harness venv per CI's recipe into the ignored path (check-ignore in the trailing-slash form — the no-slash query on an absent path returns 1, measured), Step 4 configures a FRESH build dir with the CMakeCache interpreter proof (the cache keeps the 3.14 fallback otherwise, measured), Step 2 create-or-verify keeps your clean worktree, Step 5 runs the discriminator once as a new execution; helpers and product/test bytes unchanged
REPO: `../bivpak` docs lane (the rev4 artifact committed); product paths untouched; your worktree READ-ONLY at my seat (`git check-ignore` queries and `CMakeCache.txt` read only). Validation this turn on the rev4 WRITTEN bytes: the venv form in a scratch directory (venv 0 / pip 0 / missing [] / Python 3.12.12); the check-ignore semantics in a scratch repo AND at your worktree (both shells); the CMakeCache stickiness on a scratch harness configure (three configures); the `grep -c` cache proof on both scratch caches (both shells); spaced pipes in backticks 0; the six helpers cmp-equal to rev2.
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 6ebbfa42; on approve the token `intg-r450-discover-parity-impl-2` mints in-lane; your 175211 STOP was correct and its evidence is cited — the plan owed you the environment step); master CC (a pair-owned observer STOP folded in-lane; nothing owed by master; the CI recipe and the 2a-lane precedent are the grounds); m-2 / m-3 seats CC (no surface of yours moves — the venv and the build dir are ignored, untracked paths); operator CC (unchanged)

## What the reviewer is asked to grade at 6ebbfa42 (counts MEASURED on the artifact)

```text
F1  steps = 33 (Step 3b added) · python blocks = 6 (unchanged, cmp-equal) · token phrases = 0 · refspec hazard sites = 0 ·
    spaced pipes in backticks = 0 · helper invocations without a status capture = 0
F2  Step 3b: check-ignore SLASH form (STOP on 1) → venv (3.12) → pip (lock) → module proof → version → status EMPTY, each status captured
F3  Step 4: rm -rf build/ci-macos → configure → CMakeCache grep -c == 1 (the venv python selected) → build; Step 2 create-or-verify; Step 5 one execution
```

## Your review

Exact-hash: `shasum -a 256 docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md` must read `6ebbfa421398e2901e01cf9e5343517ffce214ebe7048ee007ff814a4be75d8e` before any finding is written. Grade Step 3b and Step 4 against your own 175211 evidence (the cached 3.14 path in your worktree's `CMakeCache.txt:24`; the absent venv), run the WRITTEN forms, and confirm the resume checkpoint matches your retained worktree. Approve → the pair's gate mints `intg-r450-discover-parity-impl-2` (PARENT = your approving review); must-revise → rev5 under `intg-r450-discover-parity-plan-5`.

ACTIONS_GIT_REF: docs-lane writes only — the rev4 artifact (6ebbfa42) committed; this relay via the engine; the root-mode sweep with this draft present archived under results/ before submit; no product byte; your worktree untouched
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); the root-mode sweep over .relays/intg with this draft present read for the edge line count BEFORE submit
FINAL_GIT_STATUS_SHORT:
?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-R450-DISCOVER-PARITY-REV4.md
?? .relays/intg/intg-r450/SITREP-pair-implementer-20260906-175211.md
?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev4-20260906.txt
Literal path-scoped status for this seat's own writes at authoring time (the STOP relay is the implementer's, uncommitted at their seat; it commits with this filing); the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
