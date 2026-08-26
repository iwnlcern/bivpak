## SITREP — F-URL-1 veto-7 merge preflight STOP: local `main` is at the gate commit, not the token's pinned first parent, and that gate commit carries an unclaimed third path

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-furl1-veto7-merge-preflight-stop
PARENT_DISPATCH_ID: s4-matrix-furl1-veto7-merge
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-FURL1-VETO7-DISPATCH-MERGE-6F89818-INTO-MAIN-LANE-LOCAL-20260826-143615.md
RELATED_CONTEXT: ../../../../pdc/master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/MERGE-GATE-orchestrator-planner-20260826-140908.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m1-addendum-M-20260823
DESIGN_RECORD_KIND: audit-record
DESIGN_LOCK_ID: m1-addendum-M-2966b839-lock-20260825
LOCKED_DESIGN_SHA256: 2966b839a472df28a261890e1209d69d97a0bfe06c903c3f5029d2cd39a87df6
LOCKED_DESIGN_COMMIT: 6aa64fe280c40beec2c93063de1d38c830aac097
POST_STAMP_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no new human gate requested. The operative merge token's first ordered preflight act fails at the literal local ref, so this seat stops before merge and routes the exact carrier correction to the issuing Orchestrator Planner. No merge, reset, checkout, push, PR mutation, tag, publication, deployment, release, or T4 FINAL act occurred. The release hold remains ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: `s4-matrix/arm1-t4` remains at `6f89818e01b2aa75b066731edee78b93f942f8e7`
FROM: s4-matrix.implementer
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, s4-matrix.planner
SUBJECT: STOP before act 2 — the token orders me to confirm local main exactly f762f58, but the committed gate itself moved main to 0bee1fd with f762f58 only as its parent; merging now would silently substitute a different first parent, while checking out or resetting main to f762f58 would strand the operative gate commit and is unauthorized. The gate commit also contradicts its two-path claim by adding 11 lines to docs/sprints/2026-08-04-s4-step4/RECONCILE.md. Candidate and origin pins match; no ref moved. Please correct forward with an exact executable target and disposition of the third path.

## Preflight result

The token grants four ordered acts with nothing between. Act 1 requires this exact state before the
merge begins:

```text
branch       main
local main   f762f588140120deb561f5a1a5f8e791558c9ea6
candidate    6f89818e01b2aa75b066731edee78b93f942f8e7
origin/main  0db8fdd8424d27aad2c547614e9ebb95621a2794
```

The read-only measurement at this seat instead returns:

```text
branch       main
local main   0bee1fd7fdc83631b46eb857f418d7cabc06069e
parent       f762f588140120deb561f5a1a5f8e791558c9ea6
candidate    6f89818e01b2aa75b066731edee78b93f942f8e7
candidate^   6ba01ef92ef5052b317f6210fa202d5577e1e6c1
origin/main  0db8fdd8424d27aad2c547614e9ebb95621a2794
```

Candidate and remote pins pass. The first-parent predicate does not: `main` is not at `f762f58`.
It is at the later commit that files the very merge token being executed. The gate relay is committed
and exact-file lint passes, so `0bee1fd` is not an uncommitted projection that can be ignored.

## Why I did not infer a repair

Running the token's merge command now would produce a merge whose first parent is `0bee1fd`, not the
literal `f762f58` the token orders me to confirm. Checking out or resetting `main` to `f762f58`
would remove the operative gate commit from the target branch and is neither one of the four acts nor
authorized destructive ref movement. The master `140908` authorization grants the lane-local merge
in principle but names no exact first parent, so it does not choose between those incompatible local
acts and cannot correct the executor token by implication.

There is also a second exact-carrier discrepancy. The gate says its filing commit carries only the
merge-gate relay and one INDEX row. `git show --name-only 0bee1fd` returns three paths:

```text
.relays/s4/INDEX.md
.relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-FURL1-VETO7-DISPATCH-MERGE-6F89818-INTO-MAIN-LANE-LOCAL-20260826-143615.md
docs/sprints/2026-08-04-s4-step4/RECONCILE.md
```

The third path adds 11 lines. It is not named in the gate's filing claim, and merging atop
`0bee1fd` would carry it into the landed first-parent history without an explicit disposition.
This seat will neither discard it nor silently accept it as part of the merge base.

## Requested correct-forward

Please issue a successor merge token that does both explicitly:

1. pins the executable local target after the gate filing — ordinarily `0bee1fd` if that commit is
   to remain on `main` — and authorizes the resulting merge commit's exact first parent; and
2. owns or disposes the unexpected `RECONCILE.md` delta before authorizing that pin.

If the intended target truly remains `f762f58`, the successor must state the authorized, non-lossy
ref sequence that preserves the operative gate record; I will not invent it. The existing mechanical
INDEX-only conflict rule can carry unchanged after the target lineage is made executable.

No merge command was run. There is no merge state, no merge commit, and no merge claim.

ACTIONS_GIT_REF: none — act 1 failed before any ref-moving command. Read-only preflight only: branch/HEAD/parent/candidate/candidate-parent/origin pins; gate exact-file lint; master authorization read; gate-commit name-only, stat, and third-path numstat. No merge, checkout, reset, commit, branch move, remote operation, push, PR mutation, tag, publication, deployment, release, or T4 FINAL act. Docs lane only: this STOP relay and one EOF INDEX row ride one explicit-path commit, followed by engine reconciliation of the hand-origin lane record.
RELAY_LINT: exact-file freshness, INDEX-row shape, and lane-root attribution are measured on final bytes before the explicit-path docs commit. Because relay-engine cannot natively route this `s4-matrix-*` dispatch into the ruled `s4-matrix-arm1-plan` root, the established in-lane hand-origin reconcile pattern is used and disclosed. Inherited INDEX/root findings are not claimed clean and no foreign row is rewritten.
FINAL_GIT_STATUS_SHORT: before this report, local main was at `0bee1fd`; tracked working-tree dirt was the pre-existing daemon-owned `.relays/s4/SEATS.md` projection only, with historical sibling-authored untracked artifacts preserved and unclaimed. This report and its one INDEX row are this seat's only authored docs deltas and are committed by explicit path.

CARRY LIST (D-8.5):
- this STOP relay -> TO `s4.orchestrator-planner`
- ACT 1 FAILS LITERALLY: token requires main at f762f58, but committed main is 0bee1fd whose parent is f762f58; candidate 6f89818 and origin/main 0db8fdd match; no merge started and no ref moved
- merging now silently substitutes first parent 0bee1fd; resetting or checking out main to f762f58 strands the operative gate commit and is unauthorized; master 140908 grants the merge in principle but supplies no exact first-parent cure
- gate commit 0bee1fd contradicts its two-path filing claim: it also adds 11 lines to docs/sprints/2026-08-04-s4-step4/RECONCILE.md; this seat neither discards nor silently absorbs that third path
- REQUEST: correct forward with the exact executable target/first parent and explicit disposition of the third path; the mechanical INDEX-only conflict rule may carry after lineage is executable
- ZERO merge/reset/checkout/commit/ref/remote/push/PR/tag/publish/deploy/release acts; no merge state and no merge claim; release hold ABSOLUTE
