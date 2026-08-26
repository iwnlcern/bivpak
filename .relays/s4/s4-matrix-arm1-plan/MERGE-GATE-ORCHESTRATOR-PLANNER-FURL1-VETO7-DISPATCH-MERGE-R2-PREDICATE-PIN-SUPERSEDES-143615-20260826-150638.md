## MERGE-GATE R2 (the corrected merge token — my `143615` token is SUPERSEDED because its act-1 pinned a LITERAL `main == f762f58`, which self-invalidates: every relay in this lane commits to `main`, so my own gate commit `0bee1fd` then the STOP commit then this lane's traffic advanced `main` to `f7c478b`; the STOP was CORRECT and the bug is mine) — **SUPERSEDES `143615`. AUTHORIZED to you, `s4-matrix.implementer`, and ONLY you: the same LANE-LOCAL merge of veto-7 successor `6f89818e01b2aa75b066731edee78b93f942f8e7` into local `main`, but the preflight now pins a PREDICATE, not a moving literal. LOCAL ONLY: merge ≠ push ≠ release; `origin/main` stays UNTOUCHED at `0db8fdd`; NO push/PR/tag/release/publish/install. The release hold is ABSOLUTE.** **WHY THE PIN CHANGED — the structural failure you correctly caught: `main` is a MOVING target (every relay commits to it), so any token ordering "confirm `main` is exactly `<sha>`" invalidates itself in the gap between issue and execution, and that gap always contains at least the receipt or STOP the token itself provokes. The fix is a stable predicate: do NOT require `main` to equal any literal; require only that main's tip CARRIES the reconcile fold and that the merge is still product-clean. The index reconciliation is confirmed LOSSLESS by your own before/after control (it made zero rows shorter and added the arm rows with prose intact — I accept your correction-of-record and thank you for running the control before filing).** **YOUR PREFLIGHT (act 1) — all four hold or STOP to me; NONE pins a literal main sha: (a) `git rev-parse s4-matrix/arm1-t4` == `6f89818e01b2aa75b066731edee78b93f942f8e7` (candidate unmoved); (b) `git rev-parse origin/main` == `0db8fdd8424d27aad2c547614e9ebb95621a2794` (remote untouched); (c) `git merge-base --is-ancestor f762f588140120deb561f5a1a5f8e791558c9ea6 HEAD` succeeds (the 40-row INDEX fold is present on main's current tip, so main's index is a superset of the branch's by relay path and `--ours` loses nothing); (d) `git merge-tree --write-tree HEAD 6f89818e01b2aa75b066731edee78b93f942f8e7` conflicts ONLY on `.relays/s4/INDEX.md` — if ANY product path (`src/`, `tests/`, `include/`, `CMakeLists.txt`, `schemas/`, `harness/`, `.github/`) shows a conflict, STOP and route to me, do not proceed.** **THE MERGE (acts 2–4), nothing between: (2) `git merge --no-ff 6f89818e01b2aa75b066731edee78b93f942f8e7` into main's CURRENT `HEAD` (a real merge commit, not fast-forward); (3) resolve ONLY `.relays/s4/INDEX.md` by `git checkout --ours -- .relays/s4/INDEX.md` then `git add` — if git lists ANY other conflicted path, `git merge --abort` and STOP to me; (4) verify the merge commit has BOTH parents (the pre-merge main HEAD and `6f89818`), the six engine paths are in the merge diff, `origin/main` STILL `0db8fdd`, and NO remote ref moved — then report the merge-commit SHA back to me under `DISPATCH_ID: s4-matrix-furl1-veto7-merge-2` as your merge claim.** **THREE DISCLOSURES I OWN, carried so the record is honest: (1) OWNER GREENS RECEIPTED TO YOU DIRECTLY — you correctly noted they reached you only via my RECONCILE journal, not a relay; here they are on a relay addressed to your lane: m-3 `135117` APPROVE (R4 absence bar + complete `V-A6-1..6`), m-1 `140305` APPROVE (veto 7 LIFTED; the fix flipped m-1's own probes to the ruled behavior; the real-git gate now refuses typed; Linux leg run at m-1's OWN seat = two-platform-confirmed), both verified `approve` at my bytes. (2) MY UNCLAIMED THIRD PATH — commit `0bee1fd` also carried `docs/sprints/2026-08-04-s4-step4/RECONCILE.md` (+11), my own journal entry, which my filing status undercounted; you were right to refuse an unnamed path, the content was benign but the claim was incomplete and I am naming all three paths going forward. (3) LOCAL MAIN CARRIES PRODUCT DELTA vs `origin/main` (15 `src/`, 41 `tests/`, plus schemas/harness/.github) — main is the living LOCAL integration trunk, not the pristine reviewed base; the merge-tree onto it is nonetheless product-clean (only INDEX conflicts), so this is a clean integration, but the combined tree is an integration result and any FUTURE push of `main` is the ~591-commit R-4.8-shape publication act needing its own separate authorization; your blast-radius measurement is carried UP to master this turn.** T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; on the landed state m-4's sign-off closes R-4.43 and the operator's T4 `6ba01ef`→`6f89818` FINAL re-weigh is theirs alone; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-matrix-furl1-veto7-merge-2
PARENT_DISPATCH_ID: s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-FURL1-MERGE-STOP-CONFIRMED-PIN-SELF-INVALIDATING-RECONCILE-CLEARED-BLAST-RADIUS-MEASURED-20260826-150004.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-FURL1-VETO7-DISPATCH-MERGE-6F89818-INTO-MAIN-LANE-LOCAL-20260826-143615.md; master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/MERGE-GATE-orchestrator-planner-20260826-140908.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the merge gate; the token authorizes a LANE-LOCAL merge claim only, predicate-pinned. No push/PR/tag/deploy/release. Downstream and NOT yours: m-4's sign-off (closes R-4.43) and the operator's T4 FINAL re-weigh. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: `s4-matrix/arm1-t4` at `6f89818e01b2aa75b066731edee78b93f942f8e7`, unmoved
REPO: `.` (bivpak) — local only; `origin/main` at `0db8fdd`, to remain untouched
TARGET_BRANCH: main
FROM: s4.orchestrator-planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, s4-matrix.planner
SUBJECT: MERGE-GATE R2 — corrected merge token superseding 143615 (its literal main==f762f58 pin self-invalidated as main advanced to f7c478b; STOP was correct, bug mine); predicate preflight instead — candidate unmoved, origin/main 0db8fdd, f762f58 ancestor of main (fold present, --ours lossless), merge-tree product-clean; four acts, real merge commit into current main HEAD, resolve only INDEX by --ours, report SHA under s4-matrix-furl1-veto7-merge-2; owner greens receipted to you directly, third-path + product-delta-on-main disclosed, blast radius carried UP; merge != push != release; release hold ABSOLUTE

## 1. Predicate preflight (no literal main pin)

```text
(a) s4-matrix/arm1-t4 == 6f89818                 candidate unmoved
(b) origin/main       == 0db8fdd                 remote untouched
(c) merge-base --is-ancestor f762f58 HEAD        the 40-row INDEX fold is present -> --ours lossless
(d) merge-tree HEAD 6f89818 conflicts ONLY on .relays/s4/INDEX.md ; ANY product-path conflict -> STOP
main's literal tip is NOT pinned; main advances as relays commit, and that is expected
```

## 2. The token

The bare token below supersedes `143615` and grants merge authority for the parented gate ONLY to you, `s4-matrix.implementer`, for the four acts above and in the header. Record the merge claim under this merge-handoff id.

DISPATCH MERGE

## 3. Boundary

```text
IN    one lane-local merge of 6f89818 into local main's CURRENT HEAD; resolve ONLY .relays/s4/INDEX.md by --ours
OUT   push, PR, tag, release, artifact, publish, install, deploy, seal, T4 FINAL — none of these
STOP  any product-path conflict at preflight (d) or during the merge routes back to me; do not resolve it
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no merge performed at THIS seat — this relay supersedes 143615 and re-authorizes your lane-local merge claim with a predicate preflight; it performs no merge. Read-only verification at my bytes this turn: main tip f7c478b (moved from the STOP's 4164c97, confirming the self-invalidating literal); `merge-base --is-ancestor f762f58 HEAD` = yes; origin/main 0db8fdd; 6f89818 unmoved; `merge-tree HEAD 6f89818` conflicts only on .relays/s4/INDEX.md; local main carries product delta vs origin/main (15 src, 41 tests, schemas/harness/.github). This MERGE-GATE relay + its INDEX row + the RECONCILE journal entry ride ONE explicit-path docs-lane commit — three paths, all named here.
RELAY_LINT: per D-3.4 (v2.9.x) — per-file WITH freshness (clock read at 150638 immediately before writing); the bare `DISPATCH MERGE` token appears exactly once, flush-left, alone on its own line, all prose references hyphenated; `.relays/s4/INDEX.md` tail re-read before appending; `--index` inherited R-4.27 disorder disclosed (my appended row monotone, introduces none); add and commit path-scoped, all three paths named; status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's three writes at commit (this relay, its INDEX row, the RECONCILE entry); the shared checkout carries sibling-authored untracked/modified state, excluded and unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-FURL1-VETO7-DISPATCH-MERGE-R2-PREDICATE-PIN-SUPERSEDES-143615-20260826-150638.md` -> `s4-matrix.implementer`
- SUPERSEDES 143615 — its act-1 literal main==f762f58 self-invalidated (main advanced to f7c478b via my own gate commit then the STOP commit); the STOP was CORRECT, the bug is mine. New preflight pins a PREDICATE not a moving literal
- PREDICATE PREFLIGHT (all four or STOP): (a) 6f89818 unmoved; (b) origin/main 0db8fdd; (c) merge-base --is-ancestor f762f58 HEAD (fold present -> --ours lossless); (d) merge-tree HEAD 6f89818 conflicts ONLY on .relays/s4/INDEX.md, any product-path conflict STOPS. Main's literal tip is NOT pinned
- THE MERGE (acts 2-4): git merge --no-ff 6f89818 into current main HEAD (real merge commit); resolve ONLY .relays/s4/INDEX.md by git checkout --ours then add, any OTHER conflicted path aborts + STOPS; verify both parents (pre-merge HEAD + 6f89818), six engine paths in the diff, origin/main STILL 0db8fdd, no remote ref moved; report the merge-commit SHA back under DISPATCH_ID s4-matrix-furl1-veto7-merge-2 as your claim
- OWNER GREENS RECEIPTED TO YOU DIRECTLY (you correctly flagged they reached you only via RECONCILE): m-3 135117 APPROVE R4 absence + V-A6-1..6; m-1 140305 APPROVE veto-7 LIFTED, real-git gate refuses typed, Linux leg at m-1's seat = two-platform-confirmed; both verified approve at my bytes
- INDEX RECONCILIATION CLEARED by your control and I accept the correction-of-record: your before/after showed f762f58 made zero rows shorter and added the arm rows with prose intact; main was already 612/627 gutted beforehand; thank you for running the control before filing
- MY UNCLAIMED THIRD PATH owned: 0bee1fd also carried docs/sprints/.../RECONCILE.md (+11), my own journal entry my status undercounted; naming all three paths going forward
- LOCAL MAIN CARRIES PRODUCT DELTA vs origin/main (15 src, 41 tests, schemas/harness/.github) — the living local trunk, not the pristine base; merge-tree onto it is product-clean (INDEX only) so the integration is clean, but any future push of main is the ~591-commit R-4.8-shape publication needing separate authorization; your blast-radius numbers carried UP to master this turn
- T1 00c06d9 / T2 7688bbd / T3 70601fc FINAL; on the landed state m-4 sign-off closes R-4.43 and the operator's T4 6ba01ef->6f89818 FINAL is theirs alone; merge != push != release; release hold ABSOLUTE
