## PLAN — rev50 SUPERSEDES rev49 before its review. It folds master's `PLAN-master-planner-20260928-233421.md` condition: the census invocation is pinned the same way the R-4.90 predicate is (221 bytes, `af8c1927…`). It also states the extraction rule for both executed lines as it actually runs, the prose master asked to be folded at the next touch. It changes the LANDING row only, and neither executed line's bytes move. Please review `7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f` (commit df2935e) at the exact hash, in place of plan-51's `6b9c507e…`.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-52
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-233421.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260928-215755.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-212748.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-211118.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260928-062658.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — rev50 folds master's 233421 condition onto rev49; after your approve the plan digest moves, so the digest word, master's fresh carry and the t-oracle rewrite follow; then the packet, the Master Reviewer, PR #28's undraft and the bare merge token; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f
PLAN_CONTRACT_WAIVER: operator — 2.9.5 pair-planner protocol §Plan contract body clauses (and, per master 203312 §2, its snippet-byte-binding clause) waived for PL-intg-substep2b-20260915 only, through sub-step 2b close; registered by master 203312; operator word `a`, 2026-09-26
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — at cb19326a5596bf30eab2ec2b9baeda0bc77be895 (FINAL H), clean, PUSHED once by impl-16 (remote `refs/heads/intg/substep2b-wiring` == H; remote `main` still B), no local upstream; draft PR https://github.com/iwnlcern/bivpak/pull/28 OPEN, isDraft true, base main, head OID H (read at my seat)
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev50 (intg-substep2b-plan-52; artifact 7a2b894a… at df2935e) supersedes rev49 (plan-51, unreviewed). The LANDING row now requires the landing act to extract and pin BOTH executed lines before the push: the R-4.90 predicate (327 bytes, 2df745ff…) and the census invocation (221 bytes, af8c1927…, checked before `<merge>` is substituted in both ref positions). The count must be exactly one and the digest must match, or it STOPs with no push. Everything else in rev49 is unchanged; 27/27 blocks equal; producer gate rc0; the pin check gives YES rc0, and two mutants STOP.
REPO: `../bivpak` docs lane — rev50 committed path-scoped (df2935e) with `docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/census-line-pin-check.txt`, `census-line-pincheck.py` and `rev49-to-rev50.diff`, no trailer; committed blob == live == 7a2b894a; product bytes untouched; no census literal added; `../pdc` read-only
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 7a2b894a98ff3da7107a51f0088a7bb29829c6ee8edd8889c821deb619cdcc2f, in place of plan-51); master CC (233421's condition folded as written); operator CC (nothing new is asked)

## What rev50 adds (plan text only; `docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/rev49-to-rev50.diff`, 24 lines)

New lines in the LANDING cell, directly after rev49's census paragraph, plus one revision-log line. Before the push, the landing act EXTRACTS and PINS BOTH executed lines. Each is the single plan line that, after `strip()`, begins with a backtick followed by its prefix and ends with a backtick, with the enclosing backticks removed:
1. prefix `STOP(){ printf` — 327 bytes, sha256 `2df745ff830766b3067c7ba5dd88ee447ffb602c0fb16356e8ee2784fc17f8b5`;
2. the census prefix — 221 bytes, sha256 `af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad`. This is checked BEFORE `<merge>` is substituted (the merge sha goes into both the tree-ref and history-ref positions) and before `$EVID` is set.

Any count other than one, or any digest mismatch, is a STOP with no push. Each line runs as its own `bash`. The census line's bytes are unchanged from rev49, so rev49's walks (`walk49.out`, `landing-line-walk.txt`) stand for rev50.

## Checked (`docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/census-line-pin-check.txt`, verbatim)

# rev50 census-line pin check (the plan's stated rule), YES on the plan and must-be-NO on two scratch mutants
census-line-pin-ok
yes rc=0
STOP census-line-digest
mutant pre-merge-history-ref rc=1
STOP census-line-count-2
mutant duplicated-line rc=1

The first mutant rewrites the census line's history ref to a pre-merge ref, which is master's silent-miss case. The second duplicates the line. Also re-measured on rev50: both rules resolve to exactly one line with the pinned digest (327/`2df745ff…` and 221/`af8c1927…`); `plan_blocks.py list` is byte-equal to rev48's `l48.txt` (27 blocks); the producer gate gives rc 0 (orphans=0, classified=56, stale=0); the T-ORACLE prefix is present once; `git diff --check` reports nothing; census literals in the plan stay at 2, none added.

## Then

After your approve:
1. I send the digest word.
2. Master files a fresh carry at `7a2b894a…`.
3. I rewrite `t-oracle.txt`.
4. I assemble the packet, then the Master Reviewer verifies it.
5. Master does the own-bytes presentation.
6. The operator undrafts PR #28 and files the bare merge token.
7. The landing act runs: both pins checked, the no-commit predicate, the merge, the census, then ONE push.

No implementation token is issued. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only: plan rev50 and its pin-check records (df2935e); this relay (a path-scoped commit follows), no trailer; the mutants only in the scratchpad; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission (daemon on kit 2.9.6); per-file 2.9.6 `relay-lint.py --no-freshness` on the draft; python-written; the draft scanned with the census alternation before submit; the filed bytes compared to the draft by digest; every newer upstream file opened before this submit (the listing run as its own command).
FINAL_GIT_STATUS_SHORT:
none — no path-scoped change at write time
Literal path-scoped status for this seat's own writes at write time; the untracked results record is impl-17's; the shared bivpak tree carries other seats' untracked relays and a daemon-projected SEATS.md, not claimed clean here.
