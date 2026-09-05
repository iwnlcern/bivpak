## PLAN — first-push plan REVISION 3 as `intg-firstpush-plan-3` (artifact @ aa21f0f9; dead prior 69447b2a, must-revised `143628`): the rev2 review's four findings folded WITHOUT widening the act — pinned fast-forward refspec, one attempt, the census of record, STOP-1/STOP-2, and the three-line receipt unchanged; what changed is that the strengthened claims are now EXECUTED by the commands, not described beside them. **F1 the fresh gate is complete:** Task 1 Step 4 re-measures STOP-1, STOP-2, the effective push URL set (`get-url --push --all`, exactly the one authorized line), the fetch URL, the hook at its RESOLVED path (`core.hooksPath` honoured), and the visibility TOGETHER, writes them to `prepush-gate.txt`, and Task 2 Step 1 is the very next command — nothing measured before the slow census is trusted at push time. **F2 the inventories cannot lie:** discovery (`find -print0`), ordering (`sort -z`), and hashing (`xargs -0 shasum`) are SEPARATE commands over NUL-safe files, each status checked, with a discovered-count == hashed-count completeness check (the old pipeline form masked an upstream failure: `false | sort -z | xargs -0 shasum` exits 0 in both shells, reproduced); the symlink inventory hashes each link's `readlink` bytes with its path, so a retargeted link changes its line. **F3 the class is written, not narrated:** Task 2 Step 2 assigns `class=` by ONE command over all six input combinations — (a) rc 0 + remote at pin; (b) rc ≠ 0 + remote still old; (c) rc ≠ 0 + remote at pin (the publication HAPPENED); (d) probe failed; (e) anything else, INCLUDING rc 0 with a remote not at the pin — appends it to `push-rc.txt`, materializes `receipt-i.txt` from the probe whenever it succeeded, and Step 3 runs the boundary proof UNCONDITIONALLY before the flow branches on the recorded class (classes b–e return immediately with the STOP; no retry anywhere). **F4 nothing is created before the boundary is judged:** the temp PARENT is canonicalized and rejected BEFORE `mktemp` (an in-repo `TMPDIR` STOPs with zero directories made), and the created home is judged again. EVERY new form validated at this seat in bash AND zsh: in-repo parent → STOP, 0 directories created; split inventory 17,801 discovered == 17,801 hashed, a failing producer captured nonzero; a retargeted symlink detected; the classifier on six inputs → a b c d e and e. PRE-DERIVED at the pin unchanged (STOP-1 rc 0; STOP-2 `0db8fdd8…`; census 3/2 exact; residue above the pin = 3 docs-lane commits + this filing). On your exact-hash approve at THIS digest (parented to `intg-firstpush-plan-3` under a unique review id) the bare token `intg-firstpush-impl` issues to you; nothing is pushed before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-firstpush-plan-3
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-143628.md
RELATED_CONTEXT: intg-firstpush/PLAN-pair-planner-20260905-092654.md; intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-091850.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's four findings on the pair's own execution/evidence bytes; the operator's R-4.51 ruling and master's repaired route unchanged; the act unchanged (pinned sha, fast-forward only, one attempt); no token issues before your exact-hash approve of THIS digest; NO PR, NO remote-CI citation, NO tag; merge ≠ push ≠ release — the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 aa21f0f9a0929887a26de87e471185723e2427ba5dd17714064e83a09fc578a6
BASE: the push publishes EXACTLY the pinned commit bbf297e36a38a1fab8c2675f945098a0633f9f8b and its history to origin refs/heads/main (currently 0db8fdd8424d27aad2c547614e9ebb95621a2794; fast-forwardable); local main is ABOVE the pin by the pair's docs-lane commits (e842e19, b7cf25e, 1fcc190 at authoring) and stays unpublished above it (receipt (iii), R-4.52)
BRANCH: none — no branch, no tag, no working-tree byte (PROVED by the split, count-checked byte inventory and the symlink-target inventory); ONE remote ref moves, by fast-forward, to the pin
TARGET_BRANCH: origin refs/heads/main (the remote ref; the ONLY ref this act touches; the ONLY effective push URL, bound in the fresh gate)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 3 (intg-firstpush-plan-3; artifact aa21f0f9; dead prior 69447b2a) — the 143628 must-revise folded without widening the act: F1 the fresh gate re-measures STOP-1/STOP-2/push URLs/fetch URL/resolved hook/visibility together into prepush-gate.txt with the push the very next command; F2 inventories as separate status-checked find/sort/xargs stages over NUL files with discovered == hashed, symlink targets hashed; F3 class= written by one command over six input combinations, receipt (i) materialized whenever observable, boundary proof unconditional before branching; F4 the temp parent judged before mktemp so the STOP path creates nothing; all forms validated bash + zsh; your exact-hash review at aa21f0f9 → token intg-firstpush-impl

## What the reviewer is asked to grade at aa21f0f9 (counts MEASURED on the artifact and asserted before this relay was written)

```text
F1  prepush-gate.txt  = 4 lines (constraint, Step 4 (g), return contents, acceptance 2) · hooks/pre-push  = 1 line (resolved via rev-parse --git-path) · "The next command executed is Task 2 Step 1"
F2  files-initial.nul  = 1 line (discovery stage) · the pipeline form  find … -print0 | sort  = 0 lines · readlink --  = 2 lines (Step 0 + Step 3 symlink-target hashing) · discovered-count == hashed-count in both inventories
F3  class=  = 4 lines (the one-command assignment + record + return + acceptance 4) · receipt-i.txt  = 5 lines (materialized at Task 2 Step 2; verified at Task 3 Step 1; carried) · Step 3 boundary proof BEFORE the branch
F4  PARENT_CANON  = 1 line (canonicalized + judged BEFORE mktemp; the created home judged again)
ACT unchanged  "$PIN:refs/heads/main"  = 1 line · one attempt · census 3/2 at the pin · STOP-1/STOP-2 · one-ref --no-tags fetch  = 1 line · receipt (i)(ii)(iii)
ID  intg-firstpush-plan-3  = 1 line (identity §; the token-line parent); lineage: rev2 69447b2a DEAD (143628), rev3 this artifact
```

ACTIONS_GIT_REF: docs-lane writes only — the rev3 artifact (aa21f0f9) and this relay via the engine; form validation ran read-only git queries and inventories of the checkout with throwaway mktemp directories under the external temp parent (removed; the in-repo-parent case was judged WITHOUT creating anything, verified by a directory count of 0); NO push, no refspec touched, no PR, no tag, no product byte; the post-filing root-mode sweep is archived; commit path-scoped follows (docs-lane residue above the pin, R-4.52)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-FIRSTPUSH-REV3-REVIEW2-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
