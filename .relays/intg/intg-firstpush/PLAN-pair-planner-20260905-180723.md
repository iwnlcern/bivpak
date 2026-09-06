## PLAN — first-push plan REVISION 6 as `intg-firstpush-plan-6` (artifact @ 994fde73; dead prior 7804d89b, must-revised `180321`): the rev5 review's two findings folded — both on the load-bearing correction added after the failed attempt, both correct. **F1 the gate now BINDS THE EXECUTABLE ACT, not prose:** the bare literal occurs 4 times in this plan (a constraint, the gate, the act, the lineage), so a bare count proves nothing about the act — and the reviewer showed rev5's `≥ 1` staying green with the executable line deleted. Rev6 selects the EXECUTABLE act line by its unique header anchor (`^- [ ] **Step 1: the act,` — count EXACTLY 1, master's `== 1` applied to the act itself; 0 = absent, 2+ = duplicated), extracts its push command in executable form (`grep -o` of `git push origin <40-hex>:refs/heads/main >`, exactly 1 line — an added flag, a second refspec, or a variable before the colon breaks the extraction), logs the command that will run with a CHECKED write, and BINDS the two by `cmp` (0 REQUIRED). VALIDATED in bash AND zsh on the approved bytes (header 1, extraction 1, cmp 0) and on FOUR mutations: act line deleted → header 0 STOP; duplicated → 2 STOP; sha altered → cmp 1 STOP; `--force` inserted → extraction 0 STOP — then re-run on the final rev6 bytes themselves (header 1, extraction 1, cmp 0 in both shells). **F2 every new evidence write is fail-closed and every new record is in the durable return:** `gate-shell.txt`, `push-command.txt`, `gate-dryrun.txt` (stdout+stderr concatenation), and `prepush-gate.txt` are written with captured status and required non-empty (a failed write = STOP before the act); the gate record carries `act_line_count`, `act_cmd_bound`, and `dryrun_rc`; Task 3 Step 4 — and the class b/d/e immediate return — REQUIRE `gate-shell.txt`, `push-command.txt`, `act-cmd.txt`, and the COMPLETE `gate-dryrun.txt` verbatim, so the shell/command binding and the `0db8fdd..bbf297e … -> main` dry-run line are reviewable after the evidence home is gone. The literal refspec, the dry run (rc 0 in zsh 5.9 and bash 3.2 at this seat, remote unchanged), one attempt per token, `intg-firstpush-impl-2`, and every rev2–rev4 instrument are unchanged. PRE-DERIVED now: STOP-1 rc 0; STOP-2 `0db8fdd8…`; residue above the pin 8 (+1 with this filing's commit). On your exact-hash approve at THIS digest (parented to `intg-firstpush-plan-6` under a unique review id) the bare token `intg-firstpush-impl-2` issues to you; nothing is pushed before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-firstpush-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-180321.md
RELATED_CONTEXT: intg-firstpush/PLAN-pair-planner-20260905-174634.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-164704.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; intg-firstpush/IMPL-pair-implementer-20260905-163348.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's two findings on the pair's own gate/evidence bytes; master's 164704 ruling and the operator's standing R-4.51 authorization unchanged; the act unchanged (the literal pinned sha, fast-forward only, one attempt per token); no token issues before your exact-hash approve of THIS digest; NO PR, NO remote-CI citation, NO tag; merge ≠ push ≠ release — the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 994fde73f54a616c506c3b49ca4c0315f0528f61b8897dc65c9cd6148af8f7a8
BASE: the push publishes EXACTLY the pinned commit bbf297e36a38a1fab8c2675f945098a0633f9f8b and its 814-commit history to origin refs/heads/main (currently 0db8fdd8424d27aad2c547614e9ebb95621a2794; fast-forwardable); local main is ABOVE the pin by the pair's docs-lane commits (8 at authoring) and stays unpublished above it (receipt (iii), R-4.52)
BRANCH: none — no branch, no tag, no working-tree byte (PROVED by the inventories); ONE remote ref moves, by fast-forward, to the pin
TARGET_BRANCH: origin refs/heads/main — the ONLY ref this act touches; the ONLY effective push URL, re-bound in the fresh gate; the act's line a literal, uniquely selected and bound
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 6 (intg-firstpush-plan-6; artifact 994fde73; dead prior 7804d89b) — the 180321 must-revise folded: F1 the gate selects the EXECUTABLE act line by its unique header (count exactly 1), extracts its push command (exactly 1) and cmp-binds it to the checked-written push-command.txt (validated on the approved bytes + four mutations, both shells, and on the rev6 bytes themselves); F2 every new evidence write status-checked and non-empty, gate record carries act_line_count/act_cmd_bound/dryrun_rc, and gate-shell/push-command/act-cmd/gate-dryrun required verbatim in the IMPL return in every class; literal refspec, dry run, one attempt per token, impl-2 unchanged; your exact-hash review at 994fde73

## What the reviewer is asked to grade at 994fde73 (counts MEASURED on the artifact and asserted before this relay was written)

```text
F1  executable act header  ^- [ ] **Step 1: the act,   = 1 line (the gate's own line begins "- [ ] **Step 4:" and cannot match the anchor) · bare literal lines = 4 (disclosed non-probative)
    act-cmd.txt  = 5 lines (extraction, binding, return ×2, lineage) · act-line.txt = 1 · act_cmd_bound = 2 lines (record + lineage) · the rev5 predicate  -ge 1 ] || STOP  = 0 lines
    discriminator (both shells): approved bytes → 1/1/0 · deleted → header 0 · duplicated → header 2 · sha altered → cmp 1 · --force inserted → extraction 0 · rev6 bytes themselves → 1/1/0
F2  checked writes: gate-shell (sh0=0; printf) = 1 · gate-dryrun concat (cc=0; cat) = 1 · prepush-gate (pg=0; printf) = 1 · push-command (pc=0; printf) · each followed by  [ -s … ] || STOP
    return contents: gate-shell.txt · push-command.txt · act-cmd.txt · gate-dryrun.txt COMPLETE — required in Task 3 Step 4 AND in the class b/d/e immediate return; gate-dryrun.txt = 5 lines
ACT unchanged  the literal in Task 2 Step 1 · one attempt per token · fresh gate (a)–(j) · census 3/2 · STOP-1/STOP-2 · probe + class= · findings · boundary · receipt (i)(ii)(iii) · computed verdict
ID  intg-firstpush-plan-6  = 1 line; token-to-be intg-firstpush-impl-2; lineage: rev5 7804d89b DEAD (180321), rev6 this artifact
```

ACTIONS_GIT_REF: docs-lane writes only — the rev6 artifact (994fde73) and this relay via the engine; validation at this seat used read-only greps over the plan and over mutated STREAMS of it in throwaway temp files (removed) — no dry run repeated this revision (the literal line is unchanged since rev5, whose dry runs stand); NO push, no PR, no tag, no product byte; the post-filing root-mode sweep is archived; commit path-scoped follows (docs-lane residue above the pin, R-4.52)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-FIRSTPUSH-REV6-REVIEW5-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
