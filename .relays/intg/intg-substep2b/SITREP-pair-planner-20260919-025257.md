## SITREP — 232600 RECEIVED (the A9-shaped seals: taken; `seal_relay=` binds without a cycle). Under the token the implementer landed Task 0 and the prefix through c3 (c1a a73f1da, c1b 9621d4c, c1c 732a39c, c2 e5aa0a3, c3 13ec732 — each with its independent review; one review fix in c1a's W-O2 folded and re-approved), built c4a's nine-path candidate to focused GREEN (817 assertions / 11 cases; the pointer-heads partition; four mutants red), then STOPped correctly at the mandatory full suite (`IMPL-pair-implementer-20260919-021304.md`, superseding 020901 to add the waiver block): ONE case fails deterministically — `tests/test_open.cpp:343` `Task 4 open occupancy and destination contracts stay bounded` (origin 2537eb6, s3 Step 3 Task 4), which sha-pins two whole `open.cpp` slices that sealed c4a must change, on a path Task 4 did not authorize. THE PLAN HAD THE CONTRADICTION (nine paths + the whole floor rc 0 + a freeze over the bytes it rewrites), not the seat; my plan never grepped the tests for the source PATH before locking (the shape-6 lesson, missed here). rev13 (16722d72 at docs 36b6b7d, 2526 lines) is FILED as plan-13 (025144) for the implementer's exact-hash review: `tests/test_open.cpp` is c4a's TENTH path with a ten-path write-set gate (executed: ten pass, nine/eleven STOP); the ONE case is re-oracled IN THE SAME COMMIT — the two sha pins deleted, the contract's text controls kept verbatim, the write slice bounded by a stable anchor and asserted directly (occupancy, `OpenPartialPresent`, `create_directories`, `fsync_tree`, `rename`, no `absolute`/`weakly_canonical`, the suffix once), five named oracle mutants, the new oracle verified READ-ONLY on the retained candidate; the full floor re-run before the commit; the typed-refusal fixture affirmed as the implementer's request-trace shim (a temp-HOME insteadOf is impossible at B: restore sets `GIT_CONFIG_GLOBAL=/dev/null`); `intg-substep2b-impl-1` is CONSUMED through c3 and a FRESH token follows the approve. DISCLOSED FOR OBJECTION (m-1 / m-3 through master): the pair re-oracles an s3-era product TEST over m-3's open surface — the sealed behaviour is untouched and asserted more directly, no design byte moves, and the pair chose the oracle's form; if an owner wants the sha freeze kept (re-pinned three times, at c4a / c4b / c6b), say so and rev14 carries it. No product byte at this seat; the hold stands

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260918-232600.md
RELATED_CONTEXT: intg-substep2b/IMPL-pair-implementer-20260919-021304.md; intg-substep2b/IMPL-pair-implementer-20260919-020901.md; intg-substep2b/PLAN-pair-planner-20260919-025144.md; intg-substep2b/IMPL-pair-planner-20260918-184804.md; intg-substep2b/SITREP-pair-planner-20260918-184913.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a STOP received and folded into an exact-hash plan revision for the implementer's review; ONE disclosure for owner objection (the re-oracle of an s3-era test over the open surface); no product byte at this seat; the token consumed through c3; a fresh token only after the approve; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — 232600 received; prefix landed through c3 under the token; c4a STOPped at the full suite on an s3 Task-4 source-hash freeze in tests/test_open.cpp (a plan contradiction, mine); rev13 16722d72 at 36b6b7d filed as plan-13 025144 (tenth path + re-oracle in one commit, verified on the candidate); the re-oracle disclosed for m-1/m-3 objection; fresh token after the approve; the hold stands
REPO: `../bivpak` docs lane — rev13 (36b6b7d) + plan-13 relay (5ea8059), this relay (path-scoped commit follows), no trailer; product bytes untouched at this seat (the ten-path gate ran in a throwaway worktree; the candidate in ../bivpak-intg-substep2b-wiring was READ, not written); the implementer's branch intg/substep2b-wiring at 13ec732 (+9 uncommitted c4a paths) is theirs. `../pdc` untouched.
BRIDGE: intg.pair-planner → master.master-planner (receipt; the STOP and its fold; ONE disclosure); m-3 CC (the re-oracled case guards your open surface's occupancy/destination contract — object through master if the sha freeze must stay); m-1 CC (restore-apply §2.1 staging atomicity is asserted directly by the new oracle: partial dir, fsync_tree, rename); implementer CC (rev13 awaits your exact-hash review; your candidate is the forward base; impl-1 is consumed through c3); m-4 CC (context); operator CC (no push, PR, merge or release; the hold stands)

```text
landed    Task 0 rc=0 (evidence home s2b-intg-substep2b-impl-1-y3iCLB); c1a a73f1da; c1b 9621d4c; c1c 732a39c; c2 e5aa0a3; c3 13ec732 — reviews APPROVED
c4a       nine paths uncommitted at 13ec732+9: focused GREEN 817/11; pointer-heads 90 GREEN; 4 mutants RED; full suite 446 cases: 1 failed
the case  tests/test_open.cpp:343 (2537eb6, s3 Task 4): sha256 over `plan_open`…`execute_open` (940128ad…) and `const auto partial_dir =`…`return OpenReport{`
          (eab078f6…) — sealed c4a changes both slices and removes the second marker (`write_end == npos`)
census    the suite's ONLY sha pin over product source; test_cli.cpp :1382 (args.cpp) / :1605 (main.cpp) are order checks c3 already passed
rev13     tests/test_open.cpp = c4a's tenth path (ten-path gate before git add — executed: 10 pass / 9 STOP / 11 STOP); Step 3b re-oracles the case
          in the same commit: sha pins DELETED; kept verbatim: 2 symlink_status finds + plan_open's 3 controls (same anchors); new write slice
          `const auto partial_dir =` → the function's column-0 `}`: exists(partial_dir, ec) / OpenPartialPresent / create_directories / fsync_tree /
          rename(partial_dir, dest / no absolute / no weakly_canonical / ".bvpk-open.partial" once; 5 named mutants; verified read-only on the candidate
          Step 4 = focused receipts + 4 c4a mutants + the FULL floor at the final bytes; Step 1's refusal fixture = the request-trace shim (affirmed)
artifact  16722d72790ffe35fe931710e48c6b3684ed06b12803dba7650946990270023e @ 36b6b7d (2526 lines) — plan-13 025144 — lint 2.9.2/2.9.3 OK; gates 0/0/0; cmp filed=draft; runners 3/13/4/2 rc=0 ×4
token     intg-substep2b-impl-1 CONSUMED through c3 (its c4a authorization is superseded by this revision); intg-substep2b-impl-2 after the approve
```

Why the freeze is dropped rather than re-pinned: a sha over a region the locked plan itself rewrites, recomputed in the commit that rewrites it, is a hash of the bytes just written — it grades nothing (the freeze-the-artifact rule); c4b and c6b would recompute it twice more. The case's NAME states the contract (occupancy, destination boundedness, staging atomicity) and rev13 asserts each of those directly with anchors that survive the three commits. The one thing the sha did that the controls do not is forbid ANY other change in those regions; under a locked, reviewed plan that guard is the review itself.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — 36b6b7d, 5ea8059, this relay (path-scoped commit follows), no trailer; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written; every newer upstream file opened before this submit (listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
