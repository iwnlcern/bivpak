## PLAN — rev46 of the sub-step 2b plan: master's rev45 carry `PLAN-master-planner-20260927-231805.md` arrived. Before issuing impl-17 I walked the next token's whole handoff, which I had not done for rev45: Step 0′ from a mirror of the real `s2b-runners-V1jS1t`, then the sealed controller `run-task.sh 11` from the new directory. The controller STOPs at its predecessor check (line 16), because a resumed directory never carries Task 10's receipts. So impl-17 on rev45 would have STOPped before Task 11 was even extracted. rev46 changes `resume.sh` ONLY: it binds and carries Task 10's eleven receipts exactly as rev39 did Task 9's. The rev45 Task 11 fold is unchanged. Please review `86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa` at the exact hash. The release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-48
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-231805.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260927-231805.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-224421.md; intg-substep2b/PLAN-pair-planner-20260927-221259.md; intg-substep2b/SITREP-pair-planner-20260927-224915.md; intg-substep2b/IMPL-pair-implementer-20260927-213948.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — rev42 folds impl-15's Task 10 visibility STOP under the operator's explicit choice to keep the repository public and publish the branch ("2", 2026-09-27; the charter's operator-gated publication act, rev3 :54, discharged by that word); the undraft, the merge, publication beyond the branch push and release stay with the operator; the operator's Plan-contract waiver for this plan through sub-step 2b stands; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m1-addendum-M-20260823
DESIGN_LOCK_ID: m1-addendum-M-2966b839-lock-20260825
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_COMMIT: 6aa64fe280c40beec2c93063de1d38c830aac097
DESIGN_OWNER: m-1
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: a1ce40a930b5fd01d905e8295c3a9e581455a1c7
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md
DESIGN_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (A6 rev14, post-stamp 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m3-addendum-7-4c40fe37-lock-20260827 (A7 rev2)
THIRD_CONSUMED_CONTRACT: m3-addendum-8 lock d686e39a (A8 rev8)
FOURTH_CONSUMED_CONTRACT: m1-addendum-N-82293732-lock-20260827; m1-addendum-O-63c46631-lock-20260901; m4-sr-url rev5
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa
PLAN_CONTRACT_WAIVER: operator — 2.9.5 pair-planner protocol §Plan contract body clauses (and, per master 203312 §2, its snippet-byte-binding clause) waived for PL-intg-substep2b-20260915 only, through sub-step 2b close; registered by master 203312; operator word `a`, 2026-09-26
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (FINAL H), clean, PUSHED once by impl-16 (remote `refs/heads/intg/substep2b-wiring` == H; remote `main` still B), no local upstream; draft PR https://github.com/iwnlcern/bivpak/pull/28 OPEN, isDraft true, base main, head OID H (read at my seat)
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev46 (intg-substep2b-plan-48; artifact 86f0f7d3… at 885e754): the next token's handoff walked (Step 0′ from a real-runners mirror, then the sealed controller for Task 11) STOPs at the controller's predecessor check, line 16 — a resumed directory never carried task-10.done; resume.sh now binds and carries Task 10's eleven receipts as rev39 did Task 9's; walked YES through the controller into Task 11's prologue, four NO cases in pre-flight, and the no-Task-10 regression
REPO: `../bivpak` docs lane — rev46 committed path-scoped (885e754) with its walk records, no trailer, generated from the COMMITTED rev45 blob (`bd2d21f5…` at 31a6123) by one generator (`docs/sprints/2026-08-27-intg-consent-fabric/results/rev46-walks/gen46.py`); live == blob == `86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa`, 4,276 lines
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 86f0f7d305567828eb156f918464360c825476b75b8252e3c1054a5770e070aa); master CC (your 231805 carry consumed at rev45: `t-oracle.txt` in `s2b-runners-V1jS1t` rewritten to it, the predecessor kept; rev46 moves the digest, so a fresh carry is needed after this approve, and your two conditions on impl-17's return stand); operator CC (PR #28 stays a DRAFT; nothing remote here)

## The finding

After master's 231805, I rewrote `t-oracle.txt` in `s2b-runners-V1jS1t` to it (the predecessor kept as `t-oracle.prev-20260928-010712.txt`), and the real T-ORACLE prefix passed on the published file.
Then I walked what impl-17 would do: rev45's Step 0′ (`resume.sh` `c325718c…`) from a mirror of the real runners directory on the rev45 lock, then `"$NEW"/run-task.sh 11`:
- Step 0′ publishes a new directory with 32 carried lines and no `task-10.done`.
- The controller then STOPs `STOP-controller-task-11 line=16`. That is its predecessor check (`case "$N" in … 11) M=10;; esac; [ -s "$RUNNERS/task-$M.done" ] && … = rc=0 || STOP`), and it fires before Task 11 is extracted (`results/rev46-walks/w45resume-control.*`).
`resume.sh` has carried Task 9's receipts since rev39, so that Task 10's controller finds `task-9.done`, but it never carried Task 10's. My rev45 walks ran Step 0′ and the Task 11 body separately, never the controller between them. That is my miss.

## What rev46 changes (`plan_blocks.py list` differs from rev45 in the `resume.sh` row alone: `c325718c…` → `e0b5eed5…`, 71 → 80 lines)

1. **Pre-flight (a new T10 branch after the T9 branch):** when the previous directory holds `task-10.done`, and only beside a carried Task 9 (`task-10-without-task-9` otherwise), the following must hold:
   - `task-10.done` reads `rc=0` and is a regular file;
   - `task-10.done`, `task-10.exit`, `proof-10.tail` and `plan_blocks.sha256-10` equal the controller's copies in `$EVID/runners/`;
   - `task-10.sh` re-hashes to `task-10.sha256`;
   - its runner, proof, digest and invocation equal the prologue records of exactly ONE token, found by content (impl-16's; impl-15's failed attempt's records differ and do not count);
   - `task-10.proof-tail`, `task-10.self.sha256` and `plan-hash-10.txt` exist.
2. **Build:** all eleven Task 10 receipts are copied and re-compared, and they join `carried.sha256`.
3. **Prose:** the Step 0′ heading and a rev46 sentence beside rev39's, plus the rev46 history entry. Nothing else moves: Tasks 0, 9, 10 and 11 (rev45's fold included) are byte-identical to rev45.

## Walked (`results/rev46-walks/`)

- **YES:** rev46 Step 0′ ran from a mirror of the real `s2b-runners-V1jS1t`, with the evidence home a full APFS clone, on the rev46 lock with token `intg-substep2b-impl-17`. It publishes a new directory with 43 carried lines, byte-equal, including all eleven Task 10 receipts.
  - The sealed controller `run-task.sh 11` from that directory passes the predecessor check, extracts and proves Task 11 (`proof-11.tail` rc=0), and the prologue writes its record under `runners/intg-substep2b-impl-17/task-11/`.
  - The body then STOPs at its helpers line (runner line 26), because the walk tampered `cells.py` in the clone on purpose, so nothing is written into the real `results/`.
  - The body itself, byte-identical since rev45, was walked end to end at rc 0 in `results/rev45-walks/`.
- **NO**, each in pre-flight with nothing published and the pointer unchanged:
  - `task-10.done` rc=1 → `task-10-not-done`;
  - the controller's `task-10.exit` copy differing → `task-10-copy-mismatch-task-10.exit`;
  - `task-10.sh` altered → `task-10-sh-altered`;
  - a second token directory holding the same records → `task-10-record-owner-2`.
- **Regression:** a previous directory with no Task 10 records resumes as before, with 32 lines and no `task-10.done`.
- **Checks:** no walk directory is left in the evidence root, and the real pointer still names `s2b-runners-V1jS1t`. `plan_blocks.py check` passes for tasks 0, 9, 10 and 11, and `bash -n` passes on the extracted `resume.sh`. The producer gate reports `orphans=0 classified=56 stale=0` on the rev45 baseline, unchanged since `resume.sh` is not a task runner.

## Then

After your approve, the digest word goes to master, then his fresh carry for `86f0f7d3…`. Then `t-oracle.txt` in `s2b-runners-V1jS1t` is rewritten again (the rev45 file kept), and impl-17 is issued: Step 0′ on the rev46 lock (43 carried lines), then Task 11 ONCE via `"$RUNNERS"/run-task.sh 11`, then return.
The return carries master's two 231805 conditions:
- the landing declaration's two command lines verbatim, naming `census_population.rev45.sh` at `0c7124d7…` beside the instrument's `9c9391d5…`;
- the rehearsal's own H0 numbers (rows, A/B/C, the PASS line).
Task 11 is local, and PR #28 stays a DRAFT.

## The diff (rev45 → rev46, the plan file only; 53 lines)

It is committed as `docs/sprints/2026-08-27-intg-consent-fabric/results/rev46-walks/rev45-to-rev46.diff` (885e754), sha256 `e7348b535c1603fd15099d07f70922813ff8f98ec8ce7e9a41dc6840278edb03`. It is not inlined because a context line is a plan fence marker, which the linter's fence parser toggles on.

ACTIONS_GIT_REF: docs-lane writes only: the plan artifact rev46 and its walk records (885e754); this relay and its INDEX row (a path-scoped commit follows), no trailer. In `s2b-runners-V1jS1t`, `t-oracle.txt` was preserved by rename and rewritten to master's 231805. The walks ran on mirrors and APFS clones in my scratchpad, with the walk directories created under the evidence root removed. No product byte, no push, no PR act.
RELAY_LINT: engine-rendered submission; per-file 2.9.5 `relay-lint.py --no-freshness` on the draft; python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
