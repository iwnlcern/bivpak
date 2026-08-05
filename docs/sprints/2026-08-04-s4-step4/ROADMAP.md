# s4 sprint — Step 4: git engine + restore matrix + A7 version-floor (RUN_ID `s4`)

**This is the s4 build team's sprint doc root.** The team charter (read FIRST) lives in the
docs repo: `../pdc/master/subteams/s4/README.md`. This tree holds the durable artifacts the
s4 sessions produce; the operational relay substrate is `.relays/s4/` at this repo's root
(git-tracked, operator ruling 2026-08-04, docs lane). Cross-bridge relays and boot relays stay in the docs repo
(`../pdc/master/relays/s4-build-standup/`, `../pdc/master/subteams/s4/relays/boot/`).

Authorized scope (opening dispatch `s4-build-standup-step4-opening-dispatch`): the five-arm
git matrix in m-1's order + the addendum-7 floor implementation inside the same gate.
Consuming artifact: `../pdc/master/domains/m-1-format-engine/design/2026-08-04-STEP4-DESIGN-PACKAGE.md`.
Work branches from `main@8981bfd`.

## Sequence

| # | Milestone | State |
|---|---|---|
| 0 | Standup: charter, boots, paired AUDIT dispatches | DONE 2026-08-04 |
| 1 | Paired independent audits (s4-matrix, s4-floor) + reconcile | DISPATCHED |
| 2 | FU-1 authoring duty ASSIGNED to s4 (master `230800`); the three-arm ruling folds `TO: operator` at Arm-2 design — design does not close unruled | ASSIGNED |
| 3 | Addenda F **and G** land (unborn-HEAD ruled option 1, G rev0 authored 2026-08-05; the ONE fenced `manifest.cpp` reopening consumes BOTH after both reviews close); master relays the landing signal — no polling | PENDING UP |
| 4 | Local DESIGN per pair (Superpowers brainstorming; grill where semantics unsettled) | — |
| 5 | PLAN → plan-review → delegated `DISPATCH IMPL` per pair | — |
| 6 | Arm 1 end-to-end + golden harness day one; then Arms 2–5; floor rides after Arm-1 schema act | — |
| 7 | Receipts executed as arms land (EIGHTEEN: 12 A5 + 6 A7, run-traceable; plans — A7 six in R-4.4/`170500` §3, A5 twelve at `224200`) | — |
| 8 | Exit: ROADMAP exit test (Arm 5 closure), both addendum seals (VP), R-3.25 both legs in (a)→(b) order, DR-3 decided, clause-1 cold panel at final SHA | — |

## Standing fences (charter §2 carries the full set)

- Addendum F → Arm-1 schema act → floor `repos[]`-adjacent work (the `manifest.cpp` serialization).
- R-3.25: (b) torn-tail INOPERATIVE on the codex leg until (a) `live_at_pack` lands.
- R-4.1 promisor arm (i) HOLD; R-4.2 `sparse` reserved-and-null — both are traps, not tasks.
- Merge: the full bar at ONE exact SHA; `DISPATCH MERGE` is the operator's; RELEASE HOLD ABSOLUTE.
