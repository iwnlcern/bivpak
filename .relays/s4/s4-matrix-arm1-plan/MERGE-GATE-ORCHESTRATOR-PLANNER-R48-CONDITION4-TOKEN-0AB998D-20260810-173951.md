## MERGE-GATE (STEP 3 — condition-4 token) — the published-head-equals-reviewed-head precondition is MET, RE-VERIFIED INDEPENDENTLY AT MY SEAT with both instruments: `git ls-remote origin refs/heads/s4-matrix/r48-carrier` = `0ab998d8431a20de80b8d769fb82c1350ed0728d` AND `gh pr view 24` headRefOid = `0ab998d8431a20de80b8d769fb82c1350ed0728d` (the PR's own head — what PR #24 would merge — base `main`, OPEN). Published == reviewed == `0ab998d`, byte-exact; the stale `2341667` is gone. Conditions 1+2+3+4 are all satisfied for `0ab998d`. I hereby issue the bare condition-4 authorization to you, the matrix implementer, to merge PR #24 at `0ab998d` into `main`. Execution conditions are HARD, below. You merge; I merge nothing. Merge ≠ release — the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: MERGE-GATE
AUTHORITY: merge-gated
DISPATCH_ID: s4-matrix-r48-condition4-token
PARENT_DISPATCH_ID: s4-matrix-r48-republish-then-merge
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-REPUBLISHED-STEP2-VERIFIED-0AB998D-20260810-172837.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: DISCHARGED — the operator granted condition-4 (order-bound), the P5 republication has landed and verified at `0ab998d`, and I have independently re-verified published==reviewed at my seat. This relay carries the bare condition-4 authorization to the one implementer. The release hold is ABSOLUTE and SEPARATE (merge ≠ release); the local-`main` publication-timing question is a separate open operator item this does not touch.
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4.orchestrator-planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, s4-matrix.planner, master.orchestrator-planner
SUBJECT: MERGE-GATE — condition-4 authorization for PR #24 at 0ab998d; merge into main; re-verify at the actual merge tip; report the landed SHA up

## Precondition verified at my seat (both instruments)

```text
git ls-remote origin refs/heads/s4-matrix/r48-carrier  → 0ab998d8431a20de80b8d769fb82c1350ed0728d
gh pr view 24 --json headRefOid,baseRefName,state      → headRefOid 0ab998d…  base main  OPEN
reviewed head                                          → 0ab998d8431a20de80b8d769fb82c1350ed0728d
published == reviewed == 0ab998d                        ✓  (stale 2341667 gone)
conditions 1+2 (panel/lenses+CC) · 3 (end-state-bytes disjoint, master 165050) · 4 (operator grant) — ALL MET
```

## The authorization

The bare condition-4 token below authorizes you, and only you (`s4-matrix.implementer`), to merge PR #24
(`s4-matrix/r48-carrier` at head `0ab998d`) into `main`. It authorizes exactly that merge and nothing else.

DISPATCH MERGE

## Execution conditions (HARD — a violation STOPS and routes up)

1. **Merge ONLY head `0ab998d8431a20de80b8d769fb82c1350ed0728d`.** Re-verify the PR head OID immediately
   before merging; if PR #24's head is anything other than `0ab998d`, DO NOT MERGE — STOP and route up (a
   moved head is a new review, and this authorization is bound to `0ab998d`, not to "PR #24" as a moving
   target).
2. **Re-verify clean at the ACTUAL merge tip.** `main` is docs-lane advancing; confirm the merge into the
   current `main` is conflict-free at merge time. Any surprise conflict STOPS and routes up — do not resolve
   a merge conflict under this token.
3. **No release, no ancillary mutation.** Merge only. No tag, no release, no branch delete beyond the normal
   PR-merge branch handling, no local-`main` publication decision (the operator's separate open item). The
   release hold is ABSOLUTE.
4. **STEP 4 report.** On the landed merge, route the published ref + the landed merge commit SHA UP (to me,
   onward to master) for condition-3-of-record closure against the merged SHA.

## Carried unchanged

The two aggregate items stay OPEN after this merge and are not this branch's debt (harness probe flake —
"did not reproduce" is not "diagnosed"; `harness-e2` stale ceiling). INFO-3 stands: the byte-identity
receipts are fixture non-vacuity guards, and this merge converts them into nothing else — the behavioral pin
arrives at the needle head (R-4.10/R-4.11). The C/B2 pair is a separate track mid-fold under its own token;
`231437` stays WITHDRAWN. Merge ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits and NO merge at this seat — independent re-verification only (git ls-remote + gh pr view 24, both == 0ab998d) + this token relay + its INDEX row on one explicit-path docs-lane commit whose SHA lands after filing. The merge is your act under the operator's condition-4 grant; I merge nothing and push nothing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit. Expected `--index` reds: the R-4.8 design/plan path-style-lock false-reds (relay-lint.py:1639; referents exist at repo-root) + the line-222 sibling inversion — none mine.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/MERGE-GATE-ORCHESTRATOR-PLANNER-R48-CONDITION4-TOKEN-0AB998D-20260810-173951.md` → `s4-matrix.implementer`
- precondition MET: published==reviewed==0ab998d re-verified at my seat (ls-remote ref + PR head OID); conditions 1+2+3+4 all satisfied
- bare condition-4 authorization issued to s4-matrix.implementer to merge PR #24 at 0ab998d into main
- HARD execution: merge ONLY 0ab998d (re-verify head before merge, moved→STOP); re-verify clean at the actual merge tip (surprise conflict→STOP); no release/ancillary mutation; STEP 4 report the landed merge SHA up for condition-3-of-record
- merge ≠ release (hold ABSOLUTE); aggregate items OPEN not this branch's debt; INFO-3 receipts fixture-non-vacuity; C/B2 231437 WITHDRAWN
