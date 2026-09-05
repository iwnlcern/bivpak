## SITREP — STOP UP: the first-push attempt under `intg-firstpush-impl` FAILED on MY DEFECT and the one-shot token is CONSUMED; origin `refs/heads/main` is UNCHANGED at `0db8fdd8424d27aad2c547614e9ebb95621a2794`; nothing published, nothing retried; a NEW governed decision is needed for a second attempt. THE FACTS, from the implementer's return `intg-firstpush/IMPL-pair-implementer-20260905-163348.md` and RE-DERIVED at this seat: Task 1 was GREEN end to end (evidence home proved external; 17,817 files + 17 symlinks inventoried; STOP-1 rc 0; STOP-2 `0db8fdd8…`; the census of record exactly 3/2 at the pin; the fresh gate `prepush-gate.txt` with one push URL == the fetch URL, hook absent, PRIVATE); the ONE permitted `git push` returned 1 with stderr `error: src refspec bbf297e36a38a1fab8c2675f945098a0633f9f8befs/heads/main does not match any`; the outcome probe ran, `class=b` was WRITTEN (remote stayed old), receipt (i) was materialized by the checked copy and reads OLD; the boundary proof is byte-clean (`status_diff_rc=0 files=17817 inventory_diff_rc=0 symlinks=17 symlink_cmp_rc=0 findings=0`); the computed verdict is STOP UP; no second push, no corrected refspec, no force, no other ref. At this seat now: `git ls-remote origin refs/heads/main` = `0db8fdd8…`; local `main` = `fd75f96`; the pin is still an ancestor of `main`; tags 5, branches 34, unchanged. THE CAUSE, MINE, reproduced as a discriminator at this seat: the plan's Task 2 Step 1 refspec was written `"$PIN:refs/heads/main"`; in zsh — the implementer's execution shell — `$PIN:r` inside double quotes is parsed as the `:r` PARAMETER MODIFIER, so the expansion is `bbf297e…8b` + `efs/heads/main` = exactly the malformed src refspec in the stderr; bash expands it correctly; the braced form `"${PIN}:refs/heads/main"` expands correctly in BOTH shells (`zsh -c 'printf %s "$PIN:refs/heads/main"'` → mangled; `"${PIN}:…"` → correct). WORSE: this exact hazard is a RECORDED lesson at my seat (`quote-git-refspecs-zsh-history-modifiers`, 2026-08-22, three prior instances in the s4 wave: "even `\"$sha:path\"` is unsafe; `\"${sha}:path\"` is safe because the brace ends the parameter name before the colon") — I wrote the unsafe form into the plan that gated an irreversible act, and the plan's "validated in bash AND zsh" claims covered the boundary, inventory, class, and fetch forms but NEVER the push line itself, which I did not execute (not even as a `printf` expansion) because "it cannot be dry-run" — it can: `git push --dry-run` exists, and a `printf` of the expanded refspec costs nothing. Four plan revisions hardened every instrument around the act and left the act's own one line unvalidated; the implementer's rev4 review, which reproduced every other form, did not catch it either — the plan said validated, and the claim was believed. This is the "claimed-but-unmeasured" class I named two rounds ago, on my own load-bearing line. NO HARM TO THE TREE OR THE REMOTE: the remote did not move; the checkout is byte-identical; the credential was not exposed; the only writes are the implementer's return relay and this one. WHAT IS CONSUMED: the pair's token `intg-firstpush-impl` (one attempt by its own rule). WHAT IS NOT CONSUMED, in my reading — for YOU to rule: the operator's R-4.51 clause (1) authorizes the first push of local `main` as a standing authorization from the moment the R-4.38 repair landed; your route `075759`/`082012` named the act once; the act DID NOT OCCUR (no ref moved). ASKED OF YOU, one hop: (1) confirm that a SECOND attempt is within the same routed act (the authorized publication has not happened) — or re-route it explicitly; (2) confirm the pre-push facts you pinned still bind unchanged (PIN `bbf297e…`, STOP-1 pin-is-ancestor, STOP-2 `0db8fdd8…`, the census of record, the three-line receipt). ON YOUR ANSWER the pair runs its gate again: plan rev5 with (a) the refspec `"${PIN}:refs/heads/main"` (braced), (b) a fresh-gate step that RECORDS the execution shell (`$ZSH_VERSION`/`$BASH_VERSION`) and the EXPANDED refspec via `printf '%s' "${PIN}:refs/heads/main" > refspec-expanded.txt`, REQUIRED byte-equal to the literal `bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main` (a STOP otherwise — the shell's expansion is measured, not assumed), (c) `git push --dry-run origin "${PIN}:refs/heads/main"` in the fresh gate with its status and output recorded (read-only against the remote; REQUIRED rc 0 and the dry-run line naming `refs/heads/main` `0db8fdd8…` → `bbf297e…`), and (d) the push as the very next command — every one of (a)–(c) EXECUTED in zsh AND bash at my seat before filing, including the `--dry-run`; then the implementer's exact-hash review → a fresh token `intg-firstpush-impl-2`. R-4.52 unchanged (the residue above the pin is now 6, this SITREP's commit makes 7). No PR, no tag, no remote-CI citation, no release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-firstpush-impl
PARENT_DISPATCH_ID: intg-firstpush-plan-review-4
IN_REPLY_TO: intg-firstpush/IMPL-pair-implementer-20260905-163348.md
RELATED_CONTEXT: intg-firstpush/IMPL-pair-planner-20260905-155001.md; intg-firstpush/PLAN-pair-planner-20260905-151513.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-firstpush-20260905.md; intg-firstpush/SITREP-pair-planner-20260905-155826.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-082012.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260905-075759.md; ../../pdc/master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — a STOP UP on a routed one-time act whose single attempt failed without publishing: whether a second attempt is within the same routed act or needs a fresh route is master's (and, if master so reads R-4.51, the operator's) decision, not the pair's; no push, retry, PR, tag, remote-CI citation, or release until that decision and the pair's re-run gate; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
PLAN_LOCK_ID: intg-firstpush-plan-20260905 @ sha256 e8e4b32bbcb1ad32f0045871fbf6d55473688bcc9d4731b75c46f286b68f1bc4
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-3.planner, m-3.implementer, m-4.planner
SUBJECT: SITREP — STOP UP: the first-push attempt FAILED (push rc 1, class b, remote unchanged at 0db8fdd; token consumed; nothing retried; boundary clean) on MY plan defect — the refspec "$PIN:refs/heads/main" is mangled by zsh's :r parameter modifier (a lesson already recorded at my seat; the push line was the one form never validated) — asking whether a second attempt is within the same routed act or needs a fresh route; rev5 will brace the refspec, record the shell and the EXPANDED refspec byte-equal to the literal, and run git push --dry-run in the fresh gate, all executed in zsh and bash before filing

## The evidence, verbatim from the implementer's recorded files (re-read at this seat)

```text
prepush-gate.txt   stop1_rc=0 stop2_remote=0db8fdd8424d27aad2c547614e9ebb95621a2794 push_url_count=1 push_url=https://github.com/iwnlcern/bivpak.git fetch_url=https://github.com/iwnlcern/bivpak.git hook=pre_push_hook_path=.git/hooks/pre-push executable=no visibility=PRIVATE census=census_tree_lines=3 census_tree_diff_rc=0 census_history_paths=2 census_history_diff_rc=0
push-stderr.txt    error: src refspec bbf297e36a38a1fab8c2675f945098a0633f9f8befs/heads/main does not match any
                   error: failed to push some refs to 'https://github.com/iwnlcern/bivpak.git'
push-rc.txt        push_rc=1 · outcome_probe_rc=0 · remote_after=0db8fdd8424d27aad2c547614e9ebb95621a2794 · class=b
receipt-i.txt      0db8fdd8424d27aad2c547614e9ebb95621a2794	refs/heads/main      (outcome evidence, not a success receipt)
boundary-proof.txt status_diff_rc=0 files=17817 inventory_diff_rc=0 symlinks=17 symlink_cmp_rc=0 findings=0
findings.txt       (empty)
verdict            class b → STOP UP (success required class a AND empty findings)
```

## The discriminator, run at this seat 2026-09-05 16:4x

```text
zsh   printf '%s' "$PIN:refs/heads/main"    → bbf297e36a38a1fab8c2675f945098a0633f9f8befs/heads/main     (the :r modifier consumed ":r"; == the stderr)
zsh   printf '%s' "${PIN}:refs/heads/main"  → bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main   (correct)
bash  both forms                            → bbf297e36a38a1fab8c2675f945098a0633f9f8b:refs/heads/main   (correct)
plan sweep for `$VAR:letter` hazards: exactly ONE site — the refspec at Task 2 Step 1 (line 39); none in the count-gate plan
state now: ls-remote origin refs/heads/main = 0db8fdd8…; main = fd75f96; pin is-ancestor rc 0; tags 5 / branches 34 unchanged; residue above the pin 6
```

## Owned, for the ledger

The act's own line was the one form I never executed in the target shell; every surrounding instrument was. The recorded lesson existed and was not applied. The "validated in bash AND zsh" sentence in the plan was true of the forms it named and was read — by me and by the reviewer — as covering the act. Rule, added to the seat: every load-bearing command in a plan is EXECUTED in the target shell before filing, with its expansion recorded, and "validated" is never written next to a form that was not; for a push, `git push --dry-run` is the validation.

ACTIONS_GIT_REF: read-only re-derivation at `../bivpak` (`ls-remote`, `rev-parse`, `merge-base`, `tag`, `branch`, `printf` expansions in zsh and bash, a plan grep); this SITREP via the engine; ONE path-scoped commit follows (the implementer's 163348 return relay, this relay, the INDEX projection, the ROADMAP line) — a docs-lane commit above the pin, R-4.52 residue; NO push, no retry, no refspec touched, no PR, no tag, no product byte
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (this draft pre-linted per-file); every upstream route directory and every pair cycle directory re-listed immediately before submit
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-FIRSTPUSH-ATTEMPT-FAILED-STOP-UP.md
?? .relays/intg/intg-firstpush/IMPL-pair-implementer-20260905-163348.md
Literal path-scoped status for this seat's own writes at authoring time (ROADMAP edited after this draft); the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
