## PLAN — R-4.50 claude-discover parity, REVISION 20 as `intg-r450-discover-parity-plan-20` (artifact @ sha256 __H__, commit __C__; prior rev19 777f8c20 APPROVED at `172709` as plan-19 and EXECUTED under token 12 through Task 9 — H `8509157c` pushed, PR #25 opened, the record `1ef791a`, the merge packet held at cell 4 and corrected forward at `142302`'s findings) — THE OPERATOR RULED (`PLAN-operator-20260912-164309.md`, carried by master `164418` TO this seat: "fix the commits, and then dispatch the merge" → "c and h please"): C `961b1ccd` and H `8509157c` are REWRITTEN, COMMIT MESSAGES ONLY, so neither carries a `Co-Authored-By` line; trees byte-identical; every other commit untouched; the merge AUTHORIZED IN PRINCIPLE for the rewritten head once it clears the SAME bar (the Master Reviewer's `142302` lens 4: a rewrite is a new identity needing new evidence and owner review). Rev20 is that bounded rewrite-and-reacceptance act under this plan's own chain, for your exact-hash review; on your approve the token `intg-r450-discover-parity-impl-13` mints in-lane (PARENT = your approving review; the token-3 shape). WHAT CHANGES: (1) Task 0 Step 2b (NEW) — THE REWRITE OF RECORD: under state `iii` at H, C' := `git commit-tree` of C's tree with parent B and C's RAW message minus EXACTLY the one line equal to the trailer (C line 48; H line 18), author AND committer identity and DATES preserved — DETERMINISTIC, so the plan PINS C' = `efb4caeda0533a81e7148dfd38462ae64704ec8a` and H' = `e8a1128d75cd4693d21269c4d040095df570f116` (computed twice at this seat in scratch shared clones from the raw bytes, equal both times; the runner STOPs on any other sha); proofs receipted in `rewrite.txt` (trees equal to C/H, `git diff C C'` and `H H'` EMPTY, message deltas exactly one deleted `<` line each, zero trailers, author identity equal, parents B / C'); the NEW branch `intg/r450-discover-parity-v2` created at H' and switched to; the OLD branch left at H (no force update, no deletion — the pair-planner's call under master's (c), disclosed); `C.txt` / `H.txt` re-bound to C' / H' (originals in `C-orig.txt` / `H-orig.txt`). Disclosed: the blank line that preceded each trailer stays, so each new message ends with an empty line — "no other message byte moves" taken literally; preserving the committer DATE makes the result pinnable, the committer field is the implementer's identity as on the originals. (2) Task 1's one literal head check under `iii` → H'. (3) The three DEAD commit templates (Task 1 `message-P`, Task 3 `message-C`, Task 5 `message-H`; states `i`/`ii`, unreachable now) have their trailer `printf` STRUCK — no commit-creating text in this plan carries a trailer (lens 4); Step 2b builds its messages from the ORIGINAL commits' bytes, never from a template. (4) Task 8 (the vehicle) — the NEW branch pushed (dry run, one attempt, class recorded; `remote-branch-before` must be EMPTY for `-v2`), a NEW PR against `main` whose body opens with the SUPERSESSION and the rewrite line (C/C', H/H'), then `gh pr close 25 --comment …` UNMERGED naming the new PR's URL (`pr25-close.rc` receipted); PR #25 and the old branch otherwise untouched. (5) Global constraint (product): the no-trailer rule stated; C/C' and H/H' named. UNCHANGED (byte-identical to rev19): Tasks 2, 4, 6, 7, 9 runners — the observation, the re-observation, THE ACCEPTANCE OF RECORD with the iso rev13 bar and the FRESH in-token base draw at B, the census of record, the finalizer; `linux-suite.sh` / `linux-container.sh`; the bar text; the F-BAR obligations (discharged at rev19, standing). Everything after Step 2b runs at H' exactly as rev19 ran it at H (master's (d)): state `iii` verification of C'/H' by TREE and DIFF (Tasks 1–5), acceptance at H' on both targets (Task 6), census at H' (Task 7), the vehicle (Task 8), Task 9's tracked record `results/r450-intg-r450-discover-parity-impl-13/`. A STOP after Step 2b leaves the worktree at H' on the new branch — Task 0's selector then reads `none` → STOP by design; a successor token needs a plan revision (disclosed). VALIDATION on this artifact's bytes: controls 34/34 (`rehearsal-r450-rev20-controls-20260912.txt`, the bar byte-identical); THE WHOLE PROTOCOL Task 0 → 9 EXECUTED on a scratch shared clone at H under the durable root: __FLOW__ Owner re-reviews of C' and H' route through master after the run (bounded on tree equality + the one-line message diff — the owners' call), then the merge packet REVISION 3 at H', the Master Reviewer's verification, then the operator's bare merge token on H'. No merge, no landing, no release from this plan; PR #25 stays OPEN until Task 8 closes it; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-r450-discover-parity-plan-20
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260912-164418.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-operator-20260912-164309.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260912-164418.md; ../../pdc/master/relays/intg-r450-discover-parity-act/MERGE-GATE-master-reviewer-20260912-142302.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260912-143555.md; intg-r450/MERGE-GATE-pair-planner-20260912-153837.md; intg-r450/PLAN-REVIEW-pair-implementer-20260911-172709.md; intg-r450/PLAN-pair-planner-20260911-170323.md; intg-r450/IMPL-pair-planner-20260911-173616.md; intg-r450/SITREP-pair-implementer-20260912-061500.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-164408.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260909-140952.md; ../../pdc/master/relays/intg-r450-discover-parity-act/PLAN-master-planner-20260910-042340.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r450-merge-gate.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev20-controls-20260912.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev20-flow-20260912.txt; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/rehearsal-r450-rev19-flow-20260911.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the operator's ruling 164309 is the human act this revision executes (rewrite C/H messages only; new branch + PR; #25 closed unmerged); token 13 mints in-lane on THIS approve; the owner re-reviews, the Master Reviewer's packet-rev3 verification and the operator's bare merge token on H' keep their gates; no merge, landing or release from this plan; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-r450-discover-parity-plan-20260906 @ sha256 __H__
BASE: B = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the PUBLISHED pin; re-read at this filing)
BRANCH: intg/r450-discover-parity in worktree ../bivpak-intg-r450-discover-parity — HEAD == H 8509157c41c5ef66595d655f39eee5107081bd32 at this filing (status EMPTY; remote head == H; PR #25 OPEN); under token 13 Task 0 Step 2b creates C' efb4caed / H' e8a1128d, the NEW branch intg/r450-discover-parity-v2 at H' and switches the worktree to it — the old branch stays at H; the rehearsal ran on a scratch shared clone and touched neither
TARGET_BRANCH: main — via a NEW PR from the pushed new remote branch at head H' (R-4.51 clause (2)); PR #25 closed unmerged by Task 8; the local merge under the operator's bare token on H'; the landing push of main = the merge packet's own step (R-4.52), not this plan's token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-2.planner, m-2.implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 20 (intg-r450-discover-parity-plan-20; artifact __H8__) — the operator's ruling 164309 executed as a bounded rewrite-and-reacceptance act: Task 0 Step 2b rewrites C/H MESSAGES ONLY by commit-tree (one trailer line deleted; author+committer identity and dates preserved; DETERMINISTIC — pinned C' efb4caed / H' e8a1128d; trees byte-identical; proofs receipted), new branch intg/r450-discover-parity-v2, old branch left, no force push; Task 8 pushes the new branch, opens a NEW PR stating the supersession, closes #25 unmerged; the three dead commit templates trailer-free; Tasks 2/4/6/7/9 byte-identical to rev19 (acceptance at H' under rev13 with a fresh base draw); controls 34/34; the whole protocol re-executed; your exact-hash review; token 13 on your approve
REPO: `../bivpak` docs lane (the rev20 artifact at __C__; the controls and flow logs under results/); product paths untouched; the candidate worktree untouched at H (the rehearsal on a scratch shared clone; the evidence home under $HOME/Programming/bivpak-evidence)
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of __H8__; grade Step 2b's rewrite against the operator's ruling and master's fence (a)–(c): exactly one line deleted per message, trees equal, pinned shas, no force push; under this protocol you type nothing but the (0) bootstrap lines and `"$RUNNERS/run-task.sh" N`; on your approve token 13 mints in-lane, PARENT = your approving review); master.master-planner CC (`164418` executed as a plan revision under the pair's chain; the fence items (a)–(e) mapped in the body; the old branch LEFT, disclosed; the trailing empty line and the preserved committer date disclosed as this seat's reading of "no other message byte moves" — say so if you read the ruling otherwise); operator CC (your ruling carried verbatim; nothing asked of you now — the bare merge token on H' comes after the chain); Master Reviewer CC (lens 4 honoured: new identities, new evidence at H', owner re-reviews, packet rev3); m-2 / m-3 CC (C' / H' will come to you through master with the tree-equality + one-line-diff shape master proposed; your scope is yours); m-4 CC (visibility)

## What the reviewer is asked to grade at __H8__ (every count below produced by its measuring command on the artifact at this hash, in the run that wrote this carrier)

```text
__COUNTS__
```

## The change, where it lives in the artifact

- **Task 0 Step 2b (NEW)** — the rewrite block: state `iii` at H on the old branch with an empty status and no `-v2` ref; `C-orig.txt` / `H-orig.txt`; per commit: the RAW message (`git cat-file commit X | sed '1,/^$/d'`) must hold EXACTLY ONE trailer line, deleted with `grep -v -x -F`, line counts differ by 1, `diff` rc 1 with exactly one `<` line, zero `Co-Authored-By` after; `commit-tree` with `GIT_AUTHOR_*` and `GIT_COMMITTER_*` name/e-mail/date from the original; `[ "$CN" = efb4caeda0533a81e7148dfd38462ae64704ec8a ]` and `[ "$HN" = e8a1128d75cd4693d21269c4d040095df570f116 ]` or STOP; tree / parent / empty-diff / author-identity / zero-trailer proofs; `git branch intg/r450-discover-parity-v2 "$HN"` + `git switch`; the old branch still at H; status empty; `C.txt` / `H.txt` := C' / H'; `rewrite.txt`.
- **Task 1** — the `iii` head literal `8509157c…` → `e8a1128d75cd4693d21269c4d040095df570f116` (the only Task 1 executable change besides the struck trailer printf in the dead `message-P` template).
- **Tasks 3 and 5** — the dead `message-C` / `message-H` templates' trailer `printf` struck (states `i`/`ii`); Task 5's `iii` route unchanged (rederive by tree and diff — C'/H' pass because the trees are C's/H's).
- **Task 8** — `intg/r450-discover-parity` → `intg/r450-discover-parity-v2` in the ls-remote / dry-run / push / grep / `--head` lines; the PR body's first paragraph states the supersession and the `Rewrite:` line; after `gh pr create`: `new_url` from `pr.txt`, `gh pr close 25 --comment` (the comment names the new PR and the disposition), `pr25-close.rc`; class `a` still required.
- **Global constraint (product)** — the no-trailer rule; C/C', H/H' named. **Revision 20 paragraph** — the ruling, the transform, the pins, the disclosures, what did not change.
- **Unchanged, byte-identical to rev19:** Tasks 2, 4, 6, 7, 9; `linux-suite.sh`; `linux-container.sh`; every helper; the bar text and classifier (`controls` re-bound 34/34).

## Your review

The artifact at __H__ is the object; every claim above names its producer. Please grade the RUN blocks as the executable text they are, Step 2b against the operator's words and master's fence, and the pinned shas against your own scratch computation if you wish (the transform is stated fully; a shared clone reproduces them). On approve, token 13 mints in-lane. A must-revise names the line; I revise the artifact and re-file with the next handoff id.

ACTIONS_GIT_REF: docs-lane writes only — the rev20 artifact committed (__C__) with the controls and the flow log; this relay via the engine; the pinned shas computed in throw-away scratch clones (no object written into the retained worktree — verified `cat-file -e` absent). No product byte, no candidate byte, no push, no PR, no merge, no release.
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the filed plan-14 carrier).
CARRY_LIST (per D-8.5, this turn's pending hops — path + the one TO seat):
- rendered successor of this draft -> intg.pair-implementer
FINAL_GIT_STATUS_SHORT:
 M .relays/s4/INDEX.md
 M .relays/s4/SEATS.md
?? .relays/intg/intg-r450/SITREP-pair-implementer-20260912-061500.md
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
Literal `git status --short` of the docs lane at write time (the inherited S4 rows and inherited untracked files included as printed); the shared INDEX carries sibling-authored rows not claimed clean here.
