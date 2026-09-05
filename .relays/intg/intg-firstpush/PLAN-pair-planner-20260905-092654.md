## PLAN — first-push plan REVISION 2 as `intg-firstpush-plan-2` (artifact @ 69447b2a; dead prior 3cb78373, must-revised `091850`): the rev1 review's four findings folded WITHOUT widening the act — the pinned fast-forward refspec, one attempt, the census of record, STOP-1/STOP-2, and the three-line receipt are unchanged. **F1 the endpoint is BOUND:** Task 1 Step 0 measures `git remote get-url --push --all origin` and requires EXACTLY ONE line equal to `https://github.com/iwnlcern/bivpak.git` (a `pushurl`, a second push URL, or a `pushInsteadOf` rewrite = STOP), measures the fetch URL separately, and requires NO executable `pre-push` hook (a hook could alter or veto the act outside the plan). **F2 the outcome is MEASURED after ANY client status:** Task 2 Step 2 ALWAYS runs the read-only `ls-remote` probe after the one attempt and classifies, recorded as data — (a) rc 0 and remote == pin → success; (b) rc ≠ 0 and remote still `0db8fdd8…` → STOP "stayed old"; (c) rc ≠ 0 and remote == pin → STOP "reached the pin despite client failure" (the publication HAPPENED, recorded as receipt (i), never pushed again); (d) probe failed → STOP "unobserved"; (e) any other head → STOP as a FINDING — no retry in any class, the token consumed by the attempt. **F3 the no-byte boundary is PROVED, not labelled:** Step 0 proves the evidence home canonically outside the canonical checkout root (fail-closed `case` on `pwd -P` paths — a caller's `TMPDIR` under an ignored directory STOPs) and takes a BYTE-COMPLETE sha256 inventory of every regular file outside `.git` (tracked, untracked, ignored; hashes and names only) plus a symlink inventory; Task 2 Step 3 retakes both on EVERY outcome class and requires diff rc 0; `git status --porcelain` is demoted to a secondary label. **F4 the receipt fetch is ONE ref, no tags:** Task 3 Step 2 runs `git fetch --no-tags origin +refs/heads/main:refs/remotes/origin/main` (the configured wildcard over 25 heads is NOT used) and requires `refs/remotes/origin/main` to read the pin before `main..origin/main` is counted. EVERY new form validated at this seat in bash AND zsh: external vs in-repo evidence home separate (0/1); the push-URL list is one line at this checkout; the hook is absent; two consecutive inventories of ~17.8k files diff rc 0 in a few seconds; the narrowed fetch refspec accepted by `git fetch --dry-run`. PRE-DERIVED at the pin remain as at rev1 (STOP-1 rc 0; STOP-2 `0db8fdd8…`; census 3/2 exact; residue above the pin now `b7cf25e` + `1fcc190`). On your exact-hash approve at THIS digest (parented to `intg-firstpush-plan-2` under a unique review id) the bare token `intg-firstpush-impl` issues to you; nothing is pushed before it

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-firstpush-plan-2
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-firstpush/PLAN-REVIEW-pair-implementer-20260905-091850.md
RELATED_CONTEXT: intg-firstpush/PLAN-pair-planner-20260905-084607.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-075759.md; ../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a plan revision folding the pair Implementer's four findings on the pair's own execution/evidence bytes; the operator's R-4.51 ruling and master's repaired route unchanged; the act unchanged (pinned sha, fast-forward only, one attempt); no token issues before your exact-hash approve of THIS digest; NO PR, NO remote-CI citation, NO tag; merge ≠ push ≠ release — the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 69447b2a4e18eeacce492c085686ae2d5378f5988e041d23ebcb7d3a31eefc41
BASE: the push publishes EXACTLY the pinned commit bbf297e36a38a1fab8c2675f945098a0633f9f8b and its history to origin refs/heads/main (currently 0db8fdd8424d27aad2c547614e9ebb95621a2794; fast-forwardable); local main is ABOVE the pin by the pair's docs-lane commits (b7cf25e, 1fcc190 at authoring) and stays unpublished above it (receipt (iii), R-4.52)
BRANCH: none — no branch, no tag, no working-tree byte (PROVED by the byte-complete inventory); ONE remote ref moves, by fast-forward, to the pin
TARGET_BRANCH: origin refs/heads/main (the remote ref; the ONLY ref this act touches; the ONLY effective push URL bound at Step 0)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: PLAN revision 2 (intg-firstpush-plan-2; artifact 69447b2a; dead prior 3cb78373) — the 091850 must-revise folded without widening the act: F1 effective push URL set bound to exactly the one authorized URL + fetch URL separate + no pre-push hook; F2 outcome probed after ANY push rc and classified (success / stayed old / reached despite failure / unobserved / unexpected), boundary proof in every class, never a retry; F3 evidence home proved canonically outside the checkout + byte-complete sha256 inventory of every worktree file outside .git compared after the act; F4 one-ref --no-tags receipt fetch with origin/main required to read the pin; all forms validated bash + zsh; your exact-hash review at 69447b2a → token intg-firstpush-impl

## What the reviewer is asked to grade at 69447b2a (counts MEASURED on the artifact and asserted before this relay was written)

```text
F1  get-url --push --all  = 3 lines (constraint, Step 0, lineage) · hooks/pre-push  = 1 line · fetch URL measured separately (remote-fetch-url.txt)
F2  remote_after  = 3 lines (Task 2 Step 2 classification (a)–(e) + return contents) · the probe ALWAYS runs · no retry in any class · Step 3 boundary proof runs in every class
F3  pwd -P  = 2 lines (Step 0 boundary proof) · inventory-initial.txt  = 2 lines (Step 0 + Task 2 Step 3 diff) · symlink inventory · status labels secondary
F4  --no-tags origin +refs/heads/main:refs/remotes/origin/main  = 1 line · the wildcard form  git fetch origin >  = 0 lines · origin/main must read the pin
ACT unchanged  "$PIN:refs/heads/main"  = 1 line · --force  = 2 lines (prohibitions only) · one attempt · census 3/2 at the pin · STOP-1/STOP-2 · receipt (i)(ii)(iii)
ID  intg-firstpush-plan-2  = 1 line (identity §; the token-line parent); lineage: rev1 3cb78373 DEAD (091850), rev2 this artifact
```

ACTIONS_GIT_REF: docs-lane writes only — the rev2 artifact (69447b2a) and this relay via the engine; form validation ran read-only git queries, a `--dry-run` fetch, and two inventories of the checkout with throwaway mktemp directories (removed; one under `build/` created and removed for the must-STOP case); NO push, no refspec touched, no PR, no tag, no product byte; the post-filing root-mode sweep is archived; commit path-scoped follows (docs-lane residue above the pin, R-4.52)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file; the four commission-surface lines copied byte-for-byte from the grant, hash-checked); every grading count above computed from the artifact bytes and asserted before this draft was written; every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-FIRSTPUSH-REV2-REVIEW1-FOLDED.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
