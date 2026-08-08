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
| 3 | Addenda F **and G** land — **G: LANDED at pin `12a1c82`/`ef96d2d0…` (VP approve, signal carried `211923`)**; F: PENDING UP, same pin format; the ONE fenced `manifest.cpp` reopening consumes BOTH | G DONE / F PENDING |
| 4 | Local DESIGN per pair | BOTH COMPLETE — floor rev5 approve `42cdfd94…`; matrix rev4 approve `802b8499…` at `934fca3` (G pin governing) |
| 5 | PLAN → implement → panel → merge-gate | floor: B1 #15, slice A #21, slice C #22 (`ec9a2db`) all bar-ready/routed; B2 seeding. matrix: Wave-A stack #16/#17/#19/#20 panel-clean pending check-5. Slice C + matrix Wave-A condition-3 verified; B1/A content-ready. The `.github` count gate reddens remote Actions but `main` is UNPROTECTED (no required checks) so it gates NOTHING — a cosmetic red, R-3.48 hygiene; local-Docker is the validation leg (charter `9d933a9`). Merges await the operator's token, not the gate. |
| 6 | Arm 1 end-to-end + golden harness day one; then Arms 2–5; floor rides after Arm-1 schema act | matrix Wave-A (Arm-1 non-schema) + condition-3 banked `cb1f6254`; floor B1/A/C condition-3 banked; both await operator token; Waves B/C/D + schema act F+G-fenced |
| 7 | Receipts executed as arms land (EIGHTEEN: 12 A5 + 6 A7, run-traceable; plans — A7 six in R-4.4/`170500` §3, A5 twelve at `224200`) | — |
| 8 | Exit: ROADMAP exit test (Arm 5 closure), both addendum seals (VP), R-3.25 both legs in (a)→(b) order, DR-3 decided, clause-1 cold panel at final SHA | — |

## Standing fences (charter §2 carries the full set)

- Addendum F → Arm-1 schema act → floor `repos[]`-adjacent work (the `manifest.cpp` serialization).
- R-3.25: (b) torn-tail INOPERATIVE on the codex leg until (a) `live_at_pack` lands.
- R-4.1 promisor arm (i) HOLD; R-4.2 `sparse` reserved-and-null — both are traps, not tasks.
- Merge: the full bar at ONE exact SHA; `DISPATCH MERGE` is the operator's; RELEASE HOLD ABSOLUTE.
