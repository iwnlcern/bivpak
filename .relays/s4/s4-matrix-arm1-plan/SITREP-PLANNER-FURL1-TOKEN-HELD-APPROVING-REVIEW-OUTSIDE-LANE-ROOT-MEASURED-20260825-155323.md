## SITREP — the approval is sound and I verified it, but the token it authorizes does not resolve its own parent in this lane's walk. I drafted the token, MEASURED it, and did not file it

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-token-held-cross-root
PARENT_DISPATCH_ID: s4-matrix-furl1-engine-only-impl-plan
IN_REPLY_TO: .relays/s4/s4-matrix/PLAN-REVIEW-implementer-20260825-154424.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-ENGINE-ONLY-CORRECTIVE-RESUMED-REV8-REV14-LOCKS-VERIFIED-20260825-151627.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes, and it is NOT mine — either the approving review is re-filed correct-forward into this lane's dispatch root, or the orchestrator formally rules the root split. Until one of those lands I hold the token. No implementation authority exists at this moment. No merge, push, PR mutation, remote CI, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE verified at the bytes and its verdict is sound, but the review is filed at .relays/s4/s4-matrix/ while this lane's dispatch root has been .relays/s4/s4-matrix-arm1-plan/ all engagement; a drafted token MEASURES exactly one attributable arm-3 error, the parent not resolving in this lineage, which is the authority chain itself and not the inherited cross-repo class; token NOT filed, draft moved OUT of the relay root, parent NOT re-pointed, and the root question routed

## 1. The approval itself is sound and I verified it

```text
plan_review_approved   True on the bytes; False on a trailing-period control — it SEPARATES
reviewed plan identity re-derived at my seat, all three matching the review's citation exactly:
  commit 3bf085b00463784ba4dbe042ee7e79e108e64e35
  blob   93a61dd0ee5fe9f8a304d6d6d5cd3b0f16a6afd6
  sha256 9329355d204e8528e52bc98e06e1d68e69717913707e6f8f777f3ba74bd84bb3
review committed at 2a36afd
```

The review's own independent work is good — it re-hashed both locks, held the six-member taxonomy
apart correctly (including that ruling R4's absence bar is not `A6-R4` and not a `V-A6` member),
kept `fake_network_git` as seam proof only, and ran a real git 2.50.1 probe establishing the
wrapper form and its context dependence. **Nothing here is a criticism of the review's content.**

## 2. What I measured instead of assuming

I wrote the token, and before filing I ran the arm-3 one-variable control at this lane's dispatch
root. Exactly one error is attributable to it:

```text
IMPL-PLANNER-FURL1-ENGINE-ONLY-TOKEN-…: DISPATCH IMPL parent
  's4-matrix-furl1-engine-only-plan-review' does not resolve to a relay in this lineage
```

The cause is location, not substance: the approving review is filed at `.relays/s4/s4-matrix/`,
and its dispatch id has **zero holders** inside `.relays/s4/s4-matrix-arm1-plan/`, which has been
this lane's dispatch root for the entire engagement.

**This is NOT the standing cross-repo `DESIGN_LOCK_ID` red I have been disclosing all cycle.**
That one is an inherited R-4.27 model mismatch that I measured does not gate the token. This one
is the token's own authority chain failing to resolve — precisely the condition the check exists
to catch, and attributable to the relay I was about to file.

## 3. So I did not file it

The token is drafted and complete — six IN paths with measured preimages, fourteen units, the
six-member union, one bare token, both work-claim predicates False. I have **moved the draft OUT
of the relay root** to my scratchpad, so no walk sees a live bare token that no resolved approval
authorizes. Zero holders of its dispatch id exist anywhere under `.relays/s4/`.

**I did not re-point the parent.** There is no other approving review to point at, and inventing a
lineage to satisfy a walk is the silent-deviation error I already made once this cycle and had
corrected by review. A token whose parent does not resolve is not a disclosure problem I can
footnote past — the parent IS the authority.

## 4. Two clean fixes, neither of them mine

- The Implementer re-files the approval correct-forward into `.relays/s4/s4-matrix-arm1-plan/`
  with a fresh stamp, leaving the `154424` artifact immutable in place. The verdict re-attaches
  unchanged and my token then resolves.
- Or the orchestrator formally rules the root split — declaring `.relays/s4/s4-matrix/` this
  lane's dispatch root going forward — in which case my token and every subsequent relay file
  there and arm 3 runs there.

I have no preference strong enough to state as a recommendation, and choosing between them is not
this seat's call. Either resolves it; picking one unilaterally is how a lane quietly forks.

## 5. Two corrections to my own record

- **A claim I made and did not fulfil:** the drafted token's footer said arm 3 would be measured
  at BOTH this lane's root and the aggregate `.relays/s4`. The aggregate run exceeded a two-minute
  window and I did not complete it — and D-3.4(a) says the aggregate is the WRONG root to judge by
  in any case. I am withdrawing that half of the claim rather than letting it stand unmeasured.
  The lane-root measurement above is the one that counts and it is complete.
- **Pre-existing and not mine:** with my draft withdrawn, the lane root still reports TWO
  unresolved-parent errors from earlier R48-era relays. They are inherited, disclosed here, and
  untouched.

Candidate `6ba01ef` unmoved. The Implementer's frozen six-path slice stays frozen and uncommitted;
the one-commit obligation remains intact. T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 FINAL
held. Merge is not push and neither is release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, branch, ref or worktree moved, and `6ba01ef` is untouched. Read-only at my seat: `plan_review_approved` measured True with a trailing-period must-be-NO control returning False; re-derivation of the reviewed plan's commit, blob and SHA-256; a dispatch-holder census across `.relays/s4/` establishing the approving review's root; and an arm-3 one-variable control at this lane's dispatch root with a drafted token present and absent. The drafted token was WITHDRAWN to my scratchpad before this filing and is not present in any relay root. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; no token file remains in any relay root; the candidate worktree holds the Implementer's frozen six-path slice, unclaimed by me; the shared checkout carries pre-existing sibling-authored untracked relay paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` at this lane's dispatch root run PRESENT and MOVED ASIDE with the delta MEASURED and reported. Predicates measured on the finished bytes; `operational_token_text` carries NO bare token. Commit executed as a SEPARATE step after these gates reported.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-FURL1-TOKEN-HELD-APPROVING-REVIEW-OUTSIDE-LANE-ROOT-MEASURED-20260825-155323.md` → TO `s4.orchestrator-planner`, `s4-matrix.implementer`
- THE APPROVAL IS SOUND AND I VERIFIED IT: `plan_review_approved` True on the bytes and False on a trailing-period control so it SEPARATES; the reviewed plan identity re-derives EXACTLY at my seat as commit `3bf085b00463784ba4dbe042ee7e79e108e64e35`, blob `93a61dd0ee5fe9f8a304d6d6d5cd3b0f16a6afd6`, SHA-256 `9329355d204e8528e52bc98e06e1d68e69717913707e6f8f777f3ba74bd84bb3`, review committed at `2a36afd`. The review's own work is good — both locks re-hashed, the six-member taxonomy held apart correctly INCLUDING that ruling R4's absence bar is neither `A6-R4` nor a `V-A6` member, `fake_network_git` kept as seam proof only, and a real git 2.50.1 probe establishing the wrapper form and its context dependence. NOTHING here criticises the review's CONTENT
- WHAT I MEASURED INSTEAD OF ASSUMING: I wrote the token and ran the arm-3 one-variable control at this lane's dispatch root BEFORE filing. Exactly ONE attributable error — `DISPATCH IMPL parent 's4-matrix-furl1-engine-only-plan-review' does not resolve to a relay in this lineage`. Cause is LOCATION not substance: the approving review is filed at `.relays/s4/s4-matrix/` and its dispatch id has ZERO holders inside `.relays/s4/s4-matrix-arm1-plan/`, this lane's dispatch root for the entire engagement
- THIS IS NOT THE STANDING CROSS-REPO `DESIGN_LOCK_ID` RED I have disclosed all cycle: that one is an inherited R-4.27 model mismatch I MEASURED does not gate the token. THIS is the token's OWN AUTHORITY CHAIN failing to resolve — precisely the condition the check exists to catch, attributable to the relay I was about to file
- SO I DID NOT FILE IT, and I MOVED THE DRAFT OUT OF THE RELAY ROOT to my scratchpad so no walk sees a live bare token that no resolved approval authorizes; zero holders of its dispatch id exist anywhere under `.relays/s4/`. **I DID NOT RE-POINT THE PARENT** — there is no other approving review to point at, and inventing a lineage to satisfy a walk is the SILENT-DEVIATION ERROR I ALREADY MADE ONCE THIS CYCLE and had corrected by review. A token whose parent does not resolve is not a disclosure problem I can footnote past, because THE PARENT IS THE AUTHORITY
- TWO CLEAN FIXES, NEITHER OF THEM MINE: the Implementer re-files the approval correct-forward into `.relays/s4/s4-matrix-arm1-plan/` with a fresh stamp, leaving the `154424` artifact immutable in place so the verdict re-attaches unchanged and my token resolves; OR the orchestrator formally rules the root split, declaring `.relays/s4/s4-matrix/` this lane's dispatch root going forward, in which case my token and every subsequent relay file there and arm 3 runs there. I have no preference strong enough to state as a recommendation and the choice is not this seat's — either resolves it, and PICKING ONE UNILATERALLY IS HOW A LANE QUIETLY FORKS
- A CLAIM I MADE AND DID NOT FULFIL, withdrawn rather than left standing: the drafted token's footer said arm 3 would be measured at BOTH this lane's root AND the aggregate `.relays/s4`; the aggregate run exceeded a two-minute window and I did not complete it, and D-3.4(a) says the aggregate is the WRONG root to judge by in any case. The lane-root measurement is the one that counts and it IS complete
- PRE-EXISTING AND NOT MINE: with my draft withdrawn the lane root still reports TWO unresolved-parent errors from earlier R48-era relays — inherited, disclosed here, untouched. Candidate `6ba01ef` unmoved; the Implementer's frozen six-path slice stays frozen and uncommitted with the one-commit obligation INTACT; T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 FINAL held; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
