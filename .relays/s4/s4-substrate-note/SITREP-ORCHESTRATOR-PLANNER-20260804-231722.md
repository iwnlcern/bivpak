## SITREP — s4 SUBSTRATE CORRECTED (operator direction): s4 artifacts live in THIS repo; boots stay in the docs repo; the audit dispatches are re-homed

ROLE: Orchestrator Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-substrate-note
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a substrate/bookkeeping correction; no work authority, no gate, no token; the release hold is ABSOLUTE and untouched
FROM: s4.orchestrator-planner
TO: s4.orchestrator-reviewer, s4-matrix.planner, s4-matrix.implementer, s4-floor.planner, s4-floor.implementer
CC: operator
SUBJECT: SITREP — where s4 files live, corrected before any of you filed anything

The operator corrected the s4 file substrate on 2026-08-04, before any seat transported or
answered anything. What changes for you, completely:

1. **Everything an s4 session produces lives in THIS repo** (the bivpak code repo, your
   cwd), per the sprint-doc-setup layout:
   - Sprint doc root: `docs/sprints/2026-08-04-s4-step4/` (`ROADMAP.md`, `RECONCILE.md`,
     and the durable `audits/`, `designs/`, `plans/`, `reviews/`, `results/`).
   - Operational relay root: `.relays/s4/` at the repo root — gitignored on purpose.
   - Local INDEX: `.relays/s4/INDEX.md` (append-only at END, non-decreasing `time`, the
     `time` cell equals the filename stamp).
2. **Your boot relay stays where it is** in the docs repo
   (`../pdc/master/subteams/s4/relays/boot/…`) — read it as delivered, but where its
   substrate lines disagree with this SITREP, THIS SITREP and the updated charter §6
   govern. The charter (`../pdc/master/subteams/s4/README.md`, read-FIRST rule unchanged)
   carries the corrected §6.
3. **The two AUDIT dispatches were re-homed pre-transport** and the copies of record are:
   - `.relays/s4/s4-matrix-audit/AUDIT-ORCHESTRATOR-PLANNER-20260804-231720.md`
   - `.relays/s4/s4-floor-audit/AUDIT-ORCHESTRATOR-PLANNER-20260804-231721.md`
   Content is unchanged from the pdc-filed originals except substrate paths (audit
   artifacts now go to `docs/sprints/2026-08-04-s4-step4/audits/`; replies and INDEX rows
   into `.relays/s4/`). The pdc copies were removed before any transport; nothing any seat
   has acted on changed meaning.
4. **Cross-bridge traffic is untouched:** master↔s4 relays stay in
   `../pdc/master/relays/s4-build-standup/` with rows in the pdc master INDEX; the bridge
   rule stands (pairs never cross it — everything above your pair routes TO
   `s4.orchestrator-planner`).
5. Path convention from your cwd: this repo's files are repo-relative; the docs repo is
   `../pdc/` (cited paths like `master/…` resolve under it).

No action is required beyond noting the substrate. Pair seats: proceed per your AUDIT
dispatch (the re-homed copy). Reviewer: your remit and the visibility CC discipline are
unchanged; my authority-bearing relays continue to CC you wherever they live.

ACTIONS_GIT_REF: this repo (bivpak) — tracked writes at filing: docs/sprints/2026-08-04-s4-step4/{ROADMAP.md,RECONCILE.md} + .gitignore gains `.relays/` (uncommitted; committing to this repo is gated by the operator's merge/branch discipline); untracked-by-design: .relays/s4/ substrate (gitignored). Docs repo (../pdc) — charter §6 corrected, the two pdc audit copies git-rm'd, local INDEX annotated, correction SITREP filed UP; committed there with explicit paths (SHA in that commit's record).
FINAL_GIT_STATUS_SHORT:
 M .gitignore
?? docs/
Path-scoped to this seat's writes in this repo at filing (branch `docs/r-3.21-readme-git-scope` was otherwise clean at session start; `build/` and `.relays/` are gitignored).
