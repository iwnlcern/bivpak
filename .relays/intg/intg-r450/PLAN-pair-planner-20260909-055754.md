## PLAN — R-4.50 claude-discover parity, REVISION 11 as `intg-r450-discover-parity-plan-11` (artifact @ sha256 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747; dead prior 1a07c564, must-revised `052749`) — WORDING ONLY: your F1 and F2 folded, the two executable pathspec commands BYTE-IDENTICAL to rev10 (proven below), the archived rev10 validation run standing as the evidence. F1 (the overclaim): rev10 said "a write at ANY other path still fires"; the instrument is `git status --porcelain` without `--ignored`, so the property it proves is that the GIT-VISIBLE status — tracked modifications and untracked files — outside `.relays/` and `docs/sprints/` is UNCHANGED between the snapshot and the comparison; ignored paths (`build/` at `.gitignore:1`, the venv, `__pycache__/`) and byte-restoring writes are outside the oracle, exactly as they are outside the repository bytes under this plan's own constraint ("IGNORED, UNTRACKED environment paths … are not repository bytes"); the Revision paragraph, the MAIN-CHECKOUT NO-MUTATION PROOF constraint and the review question below now say that and nothing more — I took your first option; no stronger instrument, no re-run. F2 (the census): the real-checkout residual is bound to the archived run (sha256 `8541211e…`): `A ok lines=1`, the one line `?? relay-draft-intg-task4-stop.md` in both shells — my "two inherited untracked files" was measured on an EARLIER probe that excluded only this sprint's directory, before I widened the pathspec to `docs/sprints`, and I carried the stale count into the artifact; and the scratch-clone validation had FIVE mutation states after clean (three excluded → 0; two detecting → fire), six outcomes in all — "four" was written before I added the sibling-sprint case and not re-counted. Both are the same defect as the token-9 instrument itself: a claim not re-derived from the measurement it cites. Nothing else changes: no fence surface, no owner term, no ruling, no product byte; the token-7/8/9 evidence homes are sealed records; Task 0 re-runs; state `ii` at P is the expected route. Please review at the exact hash; on approve the token `intg-r450-discover-parity-impl-10` mints in-lane in the token-3 shape.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-r450-discover-parity-plan-11
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-r450/PLAN-REVIEW-pair-implementer-20260909-052749.md
RELATED_CONTEXT: intg-r450/PLAN-pair-planner-20260909-051237.md; intg-r450/SITREP-pair-implementer-20260909-042759.md; intg-r450/IMPL-pair-planner-20260909-031538.md; intg-r450/SITREP-pair-implementer-20260909-025213.md; intg-r450/PLAN-REVIEW-pair-implementer-20260909-014848.md; intg-r450/PLAN-pair-planner-20260909-013355.md; intg-r450/PLAN-pair-planner-20260908-234427.md; intg-r450/SITREP-pair-implementer-20260908-231512.md; intg-r450/PLAN-REVIEW-pair-implementer-20260907-163759.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260908-140952.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260907-134909.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev9-flow-state-ii-bash-20260909.log; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev9-flow-state-i-bash-20260909.log; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r450-plan-rev9-20260909.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a wording-only plan revision folding the implementer's two exact-claim findings on rev10 (the oracle stated as what it measures; the census bound to the archived run); executable bytes unchanged; no fence surface, no owner term, no ruling touched; this relay mints no token (the pair's gate mints `intg-r450-discover-parity-impl-10` in-lane only after your exact-hash approve at 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747, with the edge measured GREEN); m-2's fenced review of C, m-3's hunk review of C and byte review of H at the PR head, the merge bar, the operator's condition-4 token, and the R-4.52 landing rule keep their gates; the release hold is ABSOLUTE.
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the PUBLISHED pin; re-read at this filing)
BRANCH: intg/r450-discover-parity in worktree ../bivpak-intg-r450-discover-parity — HEAD == P 54954281b30cae113f399055fff106963a37a443 (bound under token 7, verified by hash under tokens 8 and 9; parent bbf297e; clean — re-measured at this filing; untouched by this revision (wording only, no validation run)), plan Task 0 Step 2 state `ii`; C = P amended after Task 2's observation; then its child H; NO tag
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 clause (2)); the local merge under the operator's condition-4 token; the landing push of main = the merge packet's own step (R-4.52 rule), not this plan's token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 11 (intg-r450-discover-parity-plan-11; artifact 97bef383; dead prior 1a07c564) — WORDING ONLY: the 052749 must-revise folded — F1 the oracle stated as what it measures (Git-visible status outside .relays/ and docs/sprints/ unchanged; ignored paths outside it as outside the repository bytes); F2 the census bound to the archived run (one residual untracked line; five mutation states, six outcomes); the two executable pathspec commands byte-identical to rev10; exact-hash review requested; token impl-10 on approve
REPO: `../bivpak` docs lane (the rev11 artifact committed with your 052749 review); product paths untouched; your worktree untouched (no read, no write); no validation run — the executable bytes did not change and the archived rev10 run is the evidence
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 97bef383; on approve the token `intg-r450-discover-parity-impl-10` mints in-lane, PARENT = your approving review, in the token-3 shape with master's per-task convention as its only execution statement); master CC (two claim defects of mine corrected in the plan; the instrument and its validation unchanged); m-2 and m-3 CC (no fence or owner surface touched); Master Reviewer CC; operator CC

## What the reviewer is asked to grade at 97bef383 (counts MEASURED on the artifact)

```text
steps = 45 · python blocks = 12 · text blocks = 3 · token phrases = 0 · refspec hazard sites = 0 · exact pathspec occurrences = 4 (paragraph, constraint, Step 0, Step 4) ·
`status --porcelain` occurrences = 15 on 12 lines, all byte-identical to rev10 (git diff rev10 → rev11: 5 insertions, 4 deletions; hunks at lines 1, 5, 29, 876–877 only; zero changed lines contain `status --porcelain`)
claims now stated: oracle = Git-visible status (tracked modifications + untracked files) outside `.relays/` and `docs/sprints/` unchanged; ignored paths outside it ·
residual = the archived run's ONE line (`?? relay-draft-intg-task4-stop.md`) · mutation states = FIVE after clean (three excluded → 0; two detecting → fire), six outcomes ·
strings removed: 'two inherited untracked files' = 0 · 'the four mutations' = 0 · 'any other path in the main checkout still fires' = 0
```

## Your review

Exact-hash: `shasum -a 256 docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-r450-discover-parity-20260906.md` must read `97bef383a22771fc4855f87caa4ec6865d3f596af57860165e903f7f712d7747` before any finding is written. Grade the Revision 11 paragraph, the MAIN-CHECKOUT NO-MUTATION PROOF constraint sentence and the rev10/rev11 history rows against your F1 and F2; confirm from `git diff dac93e8 c90aae2 -- <artifact>` that no line containing `status --porcelain` changed. The question the review answers: do the claims now state exactly the property the archived run measured — the Git-visible status outside the two excluded surfaces unchanged — and does the census match that run (one residual line; five mutation states)?

ACTIONS_GIT_REF: docs-lane writes only — the rev11 artifact committed (c90aae2, with your 052749 review); this relay via the engine; the root-mode sweep with this draft present archived under results/ before submit; no product byte; your worktree untouched
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the firstpush plan relay and hash-checked against the grant); the root-mode sweep over .relays/intg with this draft present read for the edge line count BEFORE submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-R450-DISCOVER-PARITY-REV11.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
