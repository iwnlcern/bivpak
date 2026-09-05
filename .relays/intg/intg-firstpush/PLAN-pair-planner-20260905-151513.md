## PLAN — first-push plan REVISION 4 as `intg-firstpush-plan-4` (artifact @ e8e4b32b; dead prior aa21f0f9, must-revised `150242`): the rev3 review's two findings folded WITHOUT widening the act — pinned fast-forward refspec, one attempt, the fresh gate, the census of record, and the narrowed receipt fetch unchanged. **F1 the symlink inventory is byte-exact and fail-closed:** each target's EXACT bytes are written to a file by `readlink -n` inside a fail-fast child (`SYMCHILD`: `set -e`; `readlink -n` → file; `shasum` on the file; the 64-hex digest asserted; one NUL-delimited `<digest>\0<path>\0` record appended) — no command substitution touches the target, so `target` and `target<LF>` now hash to DISTINCT digests (the reviewer's collision `34a04005…` reproduced first, then separated: `34a04005…` vs `c97ecfda…`); completeness is gated by BOTH the xargs status and a discovered×2 == recorded-NUL count; pre/post compared by `cmp` on the record files. **F2 nothing after the one push attempt can suppress the receipt:** from Task 2 Step 2 on, NO evidence command STOPs — every failure is appended to `findings.txt` by `note` and the flow reaches the return (measured: zero `|| STOP` between the outcome probe and the return); receipt (i) is materialized by a CHECKED `cp` (a failing copy is noted, the flow continues); whenever the outcome probe observed the remote at the pin — classes `a` AND `c` — the COMPLETE receipt sequence (i)/(ii)/(iii) runs before returning, whatever `findings.txt` holds; the return's verdict is COMPUTED: `class=a` AND empty findings = success, anything else = STOP UP with everything recorded; never a second push in any class. VALIDATED at this seat in bash AND zsh: the two-target collision separated; a regular file in the link list fails the child and is caught by rc AND count; the real checkout's 17 links inventory completely; a failing `cp` captured and noted with the flow continuing — and the validation harness itself caught an xargs argument-order error (with `-n1` the path is the LAST argument) before any of it reached the plan. PRE-DERIVED at the pin unchanged (STOP-1 rc 0; STOP-2 `0db8fdd8…`; census 3/2 exact; residue above the pin = 4 docs-lane commits + this filing). On your exact-hash approve at THIS digest (parented to `intg-firstpush-plan-4` under a unique review id) the bare token `intg-firstpush-impl` issues to you; nothing is pushed before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-firstpush-plan-4
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-150242.md
RELATED_CONTEXT: intg-firstpush/PLAN-pair-planner-20260905-144350.md; intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-143628.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's two findings on the pair's own execution/evidence bytes; the operator's R-4.51 ruling and master's repaired route unchanged; the act unchanged (pinned sha, fast-forward only, one attempt); no token issues before your exact-hash approve of THIS digest; NO PR, NO remote-CI citation, NO tag; merge ≠ push ≠ release — the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4
BASE: the push publishes EXACTLY the pinned commit bbf297e36a38a1fab8c2675f945098a0633f9f8b and its history to origin refs/heads/main (currently 0db8fdd8424d27aad2c547614e9ebb95621a2794; fast-forwardable); local main is ABOVE the pin by the pair's docs-lane commits (33565f0, e842e19, b7cf25e, 1fcc190 at authoring) and stays unpublished above it (receipt (iii), R-4.52)
BRANCH: none — no branch, no tag, no working-tree byte (PROVED by the split, count-checked byte inventory and the exact-target symlink inventory); ONE remote ref moves, by fast-forward, to the pin
TARGET_BRANCH: origin refs/heads/main (the remote ref; the ONLY ref this act touches; the ONLY effective push URL, bound in the fresh gate)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 4 (intg-firstpush-plan-4; artifact e8e4b32b; dead prior aa21f0f9) — the 150242 must-revise folded without widening the act: F1 symlink targets written by readlink -n to a file and hashed inside a fail-fast child, NUL-delimited records, xargs status + discovered×2 == recorded-NUL count, cmp pre/post (target vs target<LF> now distinct); F2 after the one push attempt nothing STOPs — every failure noted in findings.txt, receipt (i) by a checked cp, classes a AND c always run the complete (i)/(ii)/(iii) receipt, the verdict computed as class a + empty findings; all forms validated bash + zsh; your exact-hash review at e8e4b32b → token intg-firstpush-impl

## What the reviewer is asked to grade at e8e4b32b (counts MEASURED on the artifact and asserted before this relay was written)

```text
F1  SYMCHILD  = 3 lines (definition in Step 0; used in Step 0 and Task 2 Step 3) · readlink -n --  = 1 line (inside the child) · the old form  readlink -- "$1")  = 0 lines · records.nul  = 2 lines · completeness  $((ld*2)) -eq recorded-NUL  at both sites · cmp -s on the two record files
F2  '|| STOP' between "Step 2: the OUTCOME" and "Step 4: the IMPL return"  = 0 · '|| note '  in that span  = 19 · findings.txt  = 6 lines · the checked copy  cp … || cpr=$?  = 1 line · classes a AND c → Task 3 ALWAYS · verdict = class a AND empty findings
ACT unchanged  "$PIN:refs/heads/main"  = 1 line · one attempt · fresh gate (Task 1 Step 4) · census 3/2 at the pin · STOP-1/STOP-2 · one-ref --no-tags fetch · receipt (i)(ii)(iii)
ID  intg-firstpush-plan-4  = 1 line (identity §; the token-line parent); lineage: rev3 aa21f0f9 DEAD (150242), rev4 this artifact
```

ACTIONS_GIT_REF: docs-lane writes only — the rev4 artifact (e8e4b32b) and this relay via the engine; form validation ran against throwaway mktemp directories under the external temp parent (removed) and read-only inventories of the checkout; NO push, no refspec touched, no PR, no tag, no product byte; the post-filing root-mode sweep is archived; commit path-scoped follows (docs-lane residue above the pin, R-4.52)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-FIRSTPUSH-REV4-REVIEW3-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
