## PLAN — rev48 of the sub-step 2b plan: this folds MUST-2B-58 from your `intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-040246.md`. The finding is correct: rev47's pre-push predicate returned `tr`'s status, so a failed `git ls-files` read as zero entries and let the push through. rev48 binds the producer's rc before reading its output. The LANDING row is the only change; all 27 blocks are byte-identical. Please give it your exact-hash review of `acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048` (commit b127a02).

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-50
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260928-040246.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260928-032237.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-024840.md; intg-substep2b/SITREP-pair-planner-20260928-024612.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — a fail-closed repair of the rev47 predicate carrying the operator's R-4.88 word `b`; PR #28's undraft, the bare merge token under .relays/intg, and the release stay the operator's; the operator's Plan-contract waiver for this plan through sub-step 2b stands; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048
PLAN_CONTRACT_WAIVER: operator — 2.9.5 pair-planner protocol §Plan contract body clauses (and, per master 203312 §2, its snippet-byte-binding clause) waived for PL-intg-substep2b-20260915 only, through sub-step 2b close; registered by master 203312; operator word `a`, 2026-09-26
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (FINAL H), clean, PUSHED once by impl-16 (remote `refs/heads/intg/substep2b-wiring` == H; remote `main` still B), no local upstream; draft PR https://github.com/iwnlcern/bivpak/pull/28 OPEN, isDraft true, base main, head OID H (read at my seat)
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev48 (intg-substep2b-plan-50; artifact acb2ac80… at b127a02) — MUST-2B-58 folded. The landing predicate is now one physical line, run as its own bash: `r=0; L=$(git ls-files -- "$REC") || r=$?`; any nonzero rc STOPs record-ls-files-rc-<r>, and only empty output at rc 0 PASSes. Seven arms were walked on the extracted line, including three failing-producer must-be-NO arms (91 with empty output, partial output then 91, no repository → rc 128), plus rev47's predicate as the fail-open control (PASS under the failing git). 27/27 blocks equal; producer gate rc0.
REPO: `../bivpak` docs lane — rev48 committed path-scoped (b127a02) with `results/rev48-walks/`, no trailer; committed blob == live == acb2ac80; the record stays untracked (ls-files 0, staged 0); product bytes untouched at this seat; `../pdc` read-only
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of acb2ac80569857a86628a0c8ee2e50387c872038c9f4fff514491af620a03048); master CC (024840's predicate had the same fail-open shape, and rev48 keeps its one semantic predicate while binding the producer); operator CC (after an approve, the next acts are your undraft and bare token)

## The repair

MUST-2B-58 is accepted as filed. rev47's `n=$(git ls-files -- "$REC" | wc -l | tr -d ' ')` returned `tr`'s status, and a producer that fails with empty output reads as n=0. That shape came from master's 024840, and I carried it without a failing-producer control. It is the pipefail class I hold a standing lesson on, so the miss is mine.

rev48's LANDING row now carries this ONE physical line, which the landing act runs from the docs-lane root as its own `bash` process; a nonzero exit forbids the push:

`STOP(){ printf 'STOP %s\n' "$1"; exit 1; }; REC=docs/sprints/2026-08-27-intg-consent-fabric/results/s2b-intg-substep2b-impl-1; r=0; L=$(git ls-files -- "$REC") || r=$?; [ "$r" -eq 0 ] || STOP record-ls-files-rc-"$r"; [ -z "$L" ] || STOP record-tracked-"$(printf '%s\n' "$L" | wc -l | tr -d ' ')"; printf 'record-untracked-ok\n'`

- The producer's rc is bound FIRST, using the plan's own idiom (`r=0; RAW=$(git grep …) || r=$?`), and a nonzero rc STOPs distinctly as `record-ls-files-rc-<r>`.
- The semantic predicate stays master's single one: the record path has ZERO index entries, which means empty output at rc 0. The count is computed only for the STOP message, after the decision has been made, and no staged-path predicate is added.
- It is one physical line, so a copying executor has no wrap to rejoin. (rev47's form spanned three lines of the table.)

## Walked (`results/rev48-walks/`)

The line was extracted from the plan's own bytes (exactly one line in the plan starts with that backtick form) into `pred.sh`, and run in a disposable clone on a throwaway branch. The shims are committed as `shims/git-exit91` and `shims/git-partial-exit91`. `predicate-walk.txt`, verbatim:

# rev48 no-commit predicate walk: the ONE line extracted from the plan bytes (acb2ac80), run as its own bash; disposable clone of bivpak@f98c5cc, throwaway branch
record-untracked-ok
arm1 absent rc=0
STOP record-ls-files-rc-91
arm5 git exits 91, empty output (must-be-NO) rc=1
STOP record-ls-files-rc-91
arm6 git emits partial list then exits 91 (must-be-NO) rc=1
fatal: not a git repository (or any of the parent directories): .git
STOP record-ls-files-rc-128
arm7 cwd outside any repository (must-be-NO) rc=1
record-untracked-ok
arm2 untracked rc=0
STOP record-tracked-2343
arm3 add -A (must-be-NO) rc=1
STOP record-tracked-2343
arm4 committed (must-be-NO) rc=1
record-untracked-ok
real primary checkout (read-only) rc=0
real worktree: ls-files=0 staged=0
# control: rev47's predicate (results/rev47-walks/pred.sh, joined from rev47 bytes) under the same failing git
PASS tracked=0
rev47 predicate, git exits 91 rc=0

The control (the last two lines) is the discriminator: under the identical failing git, rev47's predicate PASSES with rc 0 and rev48's STOPs with rc 1.

Also checked:
- `plan_blocks.py list` on rev48 is byte-equal to rev47's `l47.txt` (27 rows).
- The producer gate gives rc 0: orphans=0, classified=56, stale=0.
- The T-ORACLE prefix is present exactly once.
- `git diff --check` reports nothing.
- The rev47 → rev48 plan diff (26 lines) is committed as `results/rev48-walks/rev47-to-rev48.diff`, sha256 `4bc8d663d25c35b4d033776a339cdd27a430509c38031ba231c6f7dde0ed44bf`, and is cited by digest.

The accepted rev47 portions are unchanged: arm (b), the `$EVID/landing/` census receipt, and the closure citing `187a1a10…` with 2,342 rows and 2,343 files.

## Then

After your approve:
1. The operator undrafts PR #28.
2. The operator files a bare `DISPATCH MERGE` token under `.relays/intg`, addressed to you.
3. Your landing act runs the rev48 line, then merges and pushes.
4. Task 12 follows.

No implementation token is issued by this relay. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: the plan artifact rev48 and its walk records (b127a02); this relay (a path-scoped commit follows), no trailer; the predicate walked in a disposable clone only, plus one read-only run in the primary checkout; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.6 `relay-lint.py --no-freshness` on the draft (the installed kit migrated 2.9.5 → 2.9.6 at 04:39 today; 2.9.5 is no longer installed, so no protocol-text diff was possible); python-written; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status over .relays/intg/INDEX.md, the plans dir and results/rev48-walks at write time (INDEX carries the implementer's 040246 row, uncommitted; rev48 committed at b127a02); the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays, not claimed clean here.
