## PLAN — sub-step 2b rev5 (intg-substep2b-plan-5; artifact 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8 at docs commit 138a322): folds the implementer's exact-hash MUST-REVISE of rev4 (065734) on its three findings, each verified at the pin before folding — MUST-2B-04: T-STAGE is now ROUTED, not narrated: `apply_archive` gains an `std::optional<path> stage` parameter (online: `repos/` members extracted into the stage dir; offline: drained + checksum-verified like `agents/` members and NEVER materialized; the stage path is never stat'ed, created or removed under --offline) with a product discriminator (a regular FILE pre-created at the stage path: `open --offline` exits 0 and leaves it byte-unchanged, the online control reports OpenPartialPresent naming it, the extract-regardless mutant reds); T-FENCE: the `STOP-T-FENCE` InternalError branch is REMOVED — Task 5 does not start until $RUNNERS/m1-fence-word.txt holds m-1's disposition (Q11), the candidate HOLDS at c4, and the fence branch is transcribed from the word in the revision that carries it; MUST-2B-12: ONE canonical root representation (`ScanExclusions::canonical`: discover's `.` and the walker's `` both → the root) + a root-claimed FAST PATH in `scan()` (payload and prune list EMPTY, nothing read) + pack canonicalizes every discover relpath; the unit test uses the PRODUCTION value with the fast-path mutant named and Task 7's workspace-root leg (tracked + untracked + subdir; ZERO `payload/` members; the repo restored with its untracked penumbra) is the product discriminator; MUST-2B-13: the identity block, the CEN row and Task 12 now say the landing census FOR the merge head is Task 12's, POST-merge, after the operator's token (Task 11 = the pre-merge rehearsal at H0 + declaration; Task 10 = the vehicle); the `--offline` claims are scoped to the born non-shallow lane everywhere they appear. MUST-2B-01..03, 05..11 CLOSED at 065734 and untouched; the M edge unchanged at pdc 631aae82 (PASS); the four runner proofs unchanged (3/13/4/2, omitted 0); no other section changes

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-5
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md; intg-substep2b/PLAN-pair-planner-20260916-054308.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-152914.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-164151.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-051652.md; ../../pdc/master/relays/intg-2b-wiring-act-m1-fence-review-r2/DESIGN-REVIEW-implementer-20260916-044559.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-171041.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-140509.md; intg-substep2b/PLAN-pair-planner-20260915-134648.md; docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r449-plan-edge-20260913.txt; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260915-132531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-132001.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-15-addendum-9-unclaimed-git-entry-and-offline-cli.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-131404.md; intg-substep2b/AUDIT-pair-planner-20260915-040846.md; intg-substep2b/AUDIT-pair-implementer-20260915-041820.md; intg-substep2b/SITREP-pair-planner-20260915-042253.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-041518.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-043301.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-042531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-130818.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-035001.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-m2-planner-20260915-125200.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md; docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate — the act's plan for the pair's exact-hash review; the token waits on THIS approve (all three pre-token gates are on the record: 035001, 042531/043301, 130818/131404); seven owner cells ride as contingent terms whose words gate individual commits, not the review; no token, no branch, no byte; the release hold is ABSOLUTE
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
DESIGN_SOURCE_COMMIT: 631aae8298801245f6281ae012cd06498576e671
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md
DESIGN_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (A6 rev14, post-stamp 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m3-addendum-7-4c40fe37-lock-20260827 (A7 rev2)
THIRD_CONSUMED_CONTRACT: m3-addendum-8 lock d686e39a (A8 rev8)
FOURTH_CONSUMED_CONTRACT: m1-addendum-N-82293732-lock-20260827; m1-addendum-O-63c46631-lock-20260901; m4-sr-url rev5
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — DOES NOT EXIST YET (no local ref, no remote head); Task 0 cuts it with a FRESH worktree ../bivpak-intg-substep2b-wiring from B and disposes the three retained pair worktrees with receipts
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev5 (intg-substep2b-plan-5; folds 065734: T-STAGE routed by an optional stage parameter with a product discriminator, T-FENCE product STOP branch removed (Task 5 waits on the word, hold at c4), canonical root representation + root-claimed fast path, Task 12 owns the post-merge census; M edge unchanged at 631aae82; artifact 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8 at docs commit 138a322) — sub-step 2b wiring, both verbs; c1 engine offline input FIRST (m-1 S-2b-1) → c2 A8 policy inside the renderers + generated table → c3 flags/hook truth table/stderr writers/predicate dedup → c4 open repos/ class + restore_entry per row + result.repos[] + D4 listing → c5 pack sealed order + narrowed .git class → c6 UnclaimedGitEntry (contingent on m-3's lock) → c7 product-scope witnesses on biv-pack-produced images → c8 m-3 harness → c9 count cells iff moved (inside the Task 9 runner, H last); contingent terms gated under HOLD-before-bytes; runner tasks 0/9/10/11 proved with bound gates; the cross-repo design edge declared and measured; grade at the exact hash
REPO: `../bivpak` docs lane — the rev5 artifact committed path-scoped (138a322), no trailer; product bytes untouched at 186adf7d; the four runner blocks extracted and proved by the plan's own extractor (task-0 82 lines gates=3, task-9 156 gates=13, task-10 69 gates=4, task-11 53 gates=2; bytes=equal, omitted=0, out_of_order=0, check rc=0 each; bash -n rc=0 each; the eleven python instruments py_compile rc=0; the four shell instruments bash -n rc=0); `../pdc` READ-ONLY (the three fences, the five master relays, the sealed texts cited on the plan face)
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8; on approve the token mints in-lane with PARENT = your approving review; the contingent terms' words are NOT review inputs — each gates its own commit under the HOLD-before-bytes RULE); master CC (the companion SITREP carries the R5 dispositions, the edge measurement and the still-open Q8–Q13 UP); m-1 / m-3 / m-4 CC (your fences are graded against on the plan face by reference — nothing paraphrased as authority); operator CC (the hold stands; no byte moves)

## What the reviewer is asked to grade at 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8 (every count below produced by its measuring command on the artifact at this hash)

```text
artifact          docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md — 2164 lines (rev5); placeholders 0; token phrases 0; census alternation 0
identity          NEW plan identity (intg-substep2b-plan); PLAN_LOCK_ID = the artifact's sha256; DESIGN record = the sealed set (M primary; A6/A7/A8/N/O/SR-URL consumed)
gates on the face gate ledger (i) IN (035001); (ii) m-4 / m-1 / m-3 IN, m-2 NOT a touch; (iii) in-as-scoped, re-run at the plan face and the candidate diff stat
commit order      c1a, c1b, c2..c9 predeclared; veto 9 MECHANICAL checked by Task 9's runner (the first TWO commits engine-only at their exact path sets; no later engine path; no commit spans both sets; the scan.cpp diff carries no ".biv" line)
tranches          A (c2 fabric + c3 CLI), B (c4 open), C (c5 pack + c6 kind), c7 witnesses, c8 harness (m-3's, arm-A), c9 count cells iff moved
contingent terms  RULE: an undetermined cell HOLDS its commit before bytes (T-JSON, T-HELP, T-STAGE, T-FENCE, T-KIND); a cell the sealed text determines is executed as cut/measured/recorded (T-NET, T-LIST, T-PROM); no vocabulary alternatives; an owner word that changes a task ⇒ a new hash-bound revision. T-KIND (m-3's addendum lock id gates c6; a late lock HOLDS, never narrows); T-JSON (result.repos[] member — Q9); T-HELP (help-line
                  order conflict A6-R9 vs m-3 §4 — Q12); T-STAGE (offline bundle extraction location — Q13); T-FENCE (pack disposition of a fenced
                  classification — Q11); T-PROM (promisor-offline kind — Q10); T-NET (--network beyond parse — Q8); T-LIST (list/info stubs —
                  MUST-A9-3); T-K and T-C (S-6 registrations)
evidence matrix   E1-M / E1-M-d / E1-A6 / E1-A7 / E1-A8 / E1-N / E2 / E3 / E4 / E5 / R-T / CG / CEN / VETO9 / RPC / C2H — each a receipt path + verifier
re-execution      every open-side witness on a hand-built image is interim (Task 4); c7 re-executes all of them on biv-pack-produced images (master 041518)
tests             hook truth table with --json in NO row; split-stream PTY helper with its must-be-YES / must-be-NO run; the eleven-row A8 matrix;
                  the request-trace shim for zero-git / no-spawn-after-DENY claims; no live network (file:// remotes; .invalid hosts; GIT_SSH_COMMAND=false)
count gate        observed CASE tuples at H0 (= the head after c8, the suite object) on both platforms; c9 ONLY if a tuple moved, committed inside the Task 9 runner; `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` proven EMPTY; H written LAST; the Linux leg = the R-4.49 container (Phases R/T/S)
population rule   harness-selftest AND harness-e2 receipts on macOS and inside the Linux container (m-3 §5); population B vs H0 (m-3 §6): equal → the r449 single-sample bar; unequal → the 015244 series (N=10 per tree, fresh container each) reduced by series_verdict.py implementing K-1/K-2/K-3 exactly, NOT-SHIFTED required, no deselection arm
census            results/intg-r449-landing-census.sh at its exact pin 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6; census_population.sh PRODUCES the population on H0 (A/B/C by value digest, unclassifiable ⇒ STOP) and again on the merge head at landing — never carried
worktrees         Task 0 disposes ../bivpak-intg-consent-fabric, ../bivpak-intg-format-act, ../bivpak-intg-r449-line1-selection — one receipt each
closure           Task 12 = the commission-closure SITREP (four worktrees, sealed homes, residuals by row)
zero-byte fences  src/core/repo beyond c1; src/core/manifest; src/adapters; harness/bivharness; render.cpp; sealed texts; PROMPT A/B/C beyond the predicate swap
```

## MUST-2B-01..11 — the Planner disposition (every finding ACCEPTED; evidence re-checked at B before disposing; RECONCILE.md §R5 holds the same eleven rows; each finding owned exactly once)

```text
MUST-2B-01  typed refusal mapping     checked: types.hpp:56-110 wire string is `url-divergence-refused`; accessor engine_error_kind(const BivError&)
            → Tasks 4/5 compare engine_error_kind(err) == EngineErrorKind::url_divergence_refused; pack control (UrlDivergenceRefused, exit 3) +
              open control (refusal row, continue, exit 2); the underscore-string mutant is the named must-be-NO
MUST-2B-02  stage path / offline rows checked: restore.cpp:138-145 stages stage_root/<artifact relpath> with containment; :444-452 structural branches
            → members staged at the FULL manifest-relative path (repos/<id>/repo.bundle); a real bundle + both patch classes restored in a witness;
              offline = three branches (shallow-pointer and payload-only-unborn identical with/without --offline; offline-pointer only where a
              network act would occur)
MUST-2B-03  machine carriers          checked: A8 :195-220/:307-339 (valid = byte-exact; malformed = VISIBLY replaced; never a display escape);
            writer.cpp:142-163 passes >=0x20 raw
            → machine_text (= sanitize_utf8) at every A8-census emission in envelope.cpp (error.path, error.facts values, refusal rows, advisory
              entries); a8·5 oracles restated (U+FFFD bytes in JSON; raw never; escape never); Task 2 asserts whole-byte-golden renders and scans
              ONLY the encoded slot (the LF false positive is gone)
MUST-2B-04  contingent authority      checked (065734 reopened it): rev4 narrated T-STAGE's hold while apply_archive extracted every repos/ member
            unconditionally, and rev4's Task 5 wrote a product STOP branch for a fenced classification
            → rev5: T-STAGE ROUTED by `stage` (offline ⇒ nullopt ⇒ drain + verify, never materialize; the stage path untouched) with the
              pre-created-file discriminator; T-FENCE: no branch, no wording — Task 5 does not start without the word, hold at c4; the RULE
              (hold-before-bytes; a word ⇒ a new hash) stands for every HOLD term
MUST-2B-12  root-repo exclusion        checked: scan.cpp's walker relpath is "" at the root (child_relpath :74-84); discover reports "." — two spellings
            → ScanExclusions::canonical maps both to ""; claims_root() ⇒ the fast path returns an EMPTY ScanResult before any read; pack
              canonicalizes each discover relpath; unit test on the PRODUCTION value + the {""} twin + the nested arm, fast-path mutant named;
              Task 7's workspace-root leg (ZERO payload/ members; untracked penumbra restored) is the product discriminator
MUST-2B-13  task numbering / scope     checked: identity LANDING/CLOSURE and the CEN row said Task 10/11 while the bodies put the vehicle at 10,
            the rehearsal at 11 and the post-merge closure at 12
            → identity + CEN → Task 12 (POST-merge, after the operator's token; Task 11 pre-merge); Task 12 opens with the ORDER line and the
              landing census on the merge head with its population re-produced there; the --offline claims scoped to the born non-shallow lane
MUST-2B-05  file lists / boundaries   checked: rev2 Task 4/6 Files vs bodies; A9.3 keeps error.kind a free string
            → Files + git add lists complete (url_consent.{hpp,cpp}, main.cpp, cli_run.hpp, test_wiring.cpp, test_url_consent.cpp, test_open.cpp);
              raw core contract tested in test_open/test_pack, rendered CLI contract in test_cli/test_wiring; no envelope-schema enum invented
MUST-2B-06  runner proof / censuses   checked: rev2 proofs gates=0; plan_blocks.py list looped "0123456789"; the untyped RepoEntry grep hit 26 lines at B
            → listing enumerates present RUN markers; prose gate spans byte-equal to runner lines (rev4: gates 3/13/4/2, omitted 0); set -o pipefail
              + PIPEOK + Task 9 Step 0 controls (must-be-NO on `false | cat`; read-only dir write; partial-stdout producer); repoentry_census.py
              type-scoped with its mutant; network class compared by CONTENT (no line numbers); invoke_git(/spawn closure greps; C-2 hunk cmp;
              A8/predicate/hook censuses EXECUTED with receipts; fence-proofs file assembled
MUST-2B-07  stale H                   checked: rev2 wrote H.txt before c9 could exist
            → H0 = head after c8 (the suite object); cellpatch.py + c9 inside the Task 9 runner; `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'`
              EMPTY proven; H written LAST; reviews/GO/vehicle bind H
MUST-2B-08  harness bar / series      checked: m-3 130818 §5 names BOTH harness targets; §6 the population rule; 015244 K-1/K-2/K-3 re-read
            → harness-e2 receipts on macOS (Task 9 Step 3) and inside the Linux container (Step 4); equal population → the r449 single-sample bar;
              series_verdict.py = 015244 exactly (validity → K-1 categorical → K-2 any run >=5 → K-3 mean/min), NOT-SHIFTED required, no deselection
MUST-2B-09  owner set / push URL      checked: rev2 accepted any three no-red reviews and an unpinned remote
            → exactly ONE no-red review from EACH of m-1, m-3, m-4 at three DISTINCT pdc paths (object/scope/verdict/no-red-status checked per relay);
              ONE push URL line == https://github.com/iwnlcern/bivpak.git; no process substitution
MUST-2B-10  census pin / population   checked: packet §8 carries the full digest; the instrument requires a population file; r449 finalize ordering
            → the full digest literal 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6 (no extractor); census_population.sh produces
              the population on H0 in the instrument's form; H0 as tree AND history ref; the landing declaration for the merge head; classify →
              freeze → copy
MUST-2B-11  cross-repo design edge    checked: relay-lint 2.9.3 xroot_* — per-file mode does not engage the edge (OK instantly); root mode resolves the
            latest DESIGN origin for DESIGN_DOC_ID under DESIGN_SOURCE_ROOT at DESIGN_SOURCE_COMMIT and a parented approving DESIGN-REVIEW
            → this carrier DECLARES the edge (M rev8 at pdc 1e987860; DESIGN_SHA256 57d89625…; owner m-1; root master/relays) and the root-mode
              measurement is running with the carrier in scope — result in the next section
```

## MUST-2B-11 — RESOLVED: the canonical cross-repo edge at the PINNED source commit (master 051652; route (b) of 164151)

```text
declaration     unchanged from 144707 except DESIGN_SOURCE_COMMIT: 631aae8298801245f6281ae012cd06498576e671 (a PIN named by master, never HEAD);
                DESIGN_SHA256 57d89625… unchanged (the M rev8 blob is identical at that tree); DESIGN_DOC_ID m1-addendum-M-20260823; owner m-1
authority at    origins carrying the M doc id with PHASE DESIGN under master/relays @ 631aae82: unique-latest = intg-2b-wiring-act/
the pin         DESIGN-planner-20260915-171041.md (m-1's fence rev2, FROM m-1.planner, DISPATCH_ID intg-2b-wiring-act); reviews with the
                M doc id AND PARENT_DISPATCH_ID intg-2b-wiring-act: intg-2b-wiring-act-m1-fence-review/…-165247 (must-revise, earlier)
                and intg-2b-wiring-act-m1-fence-review-r2/DESIGN-REVIEW-implementer-20260916-044559.md (approve; FROM m-1.implementer, the
                planner origin's peer; stamp later than 171041) — unique-latest = 044559
measured        relay-lint 2.9.3 imported as a module at this seat, xroot_authority(../pdc, <master/relays tree @ 631aae82>,
                {DESIGN_DOC_ID m1-addendum-M-20260823, DESIGN_OWNER m-1}) → PASS (must-be-YES); the same call at 1e987860 → FIRES
                authority-parent "no DESIGN-REVIEW found for selected origin intg-2b-wiring-act" (must-be-NO) — the discriminator separates
                the two trees; master executed the same function with the same result (051652)
root sweep      re-run ONCE after THIS relay is filed (kit 2.9.2 root mode, the same invocation as the two prior sweeps), with the FILED
                rev4 carrier in scope (no scout); archived beside results/lint-root-sweep-s2b-plan-edge-20260915.txt; the fired set and
                the line count reported by SITREP; the review of this plan may proceed on the module-level PASS and is not asked to wait
                on the archive — if the sweep fires a declared-edge line the pair STOPs and reports it, never re-pins on its own
ordering hazard the origin is unique-latest by stamp; at 631aae82 no PHASE DESIGN relay carrying the M doc id is later than 171041 (verified
                by enumeration: 69 carriers; latest DESIGN stamp 20260915-171041); a later one landing in pdc would re-select — the pin,
                not HEAD, is what the carrier declares and what the sweep measures
not declared    A9 (m3-addendum-9-20260915) and A6 (m3-addendum-6-20260824) are NOT declared as edges on this carrier: master measured
                both at 631aae82 and authority-parent fires for each until m-3's binding re-files land (051138/051139); the A9 terms
                bind to the LOCK id as before
```

## Review asks (each a must-revise if you find it wrong) — rev5 supersedes rev4 054308; grade rev5 only

1. The sealed orderings as coded: pack-engine §1.1/§1.2/§1.3/§2/§4 in Task 5 Step 3; restore-apply §1/§2.2 in Task 4 Step 3; A7-R3's encounter points; the hook install scope in Task 3.
2. The hook truth table and the predicate dedup (I2B-02); the stderr-only consent surfaces (I2B-03); the a7·3 topology (I2B-04); the fence paths (I2B-05); the scan refusal precision (I2B-06); the tier labels (I2B-07); the case-count gate (I2B-08); the reader disposition (I2B-09 → option (b) + T-JSON).
3. The A8 policy placement (inside the four renderers, composed clauses 1–5, the generated table with pinned inputs; `display()` untouched).
4. The contingent-term gates: is each cell truly undetermined by sealed text, and does each gate block exactly the bytes the word governs and nothing more?
5. The runner blocks (Tasks 0/9/10/11): every gate a runner line; no evidence-producing pipeline; bash 3.2 syntax; the Linux leg's receipts.
6. Anything the plan DECIDES that an owner should have — name it; the SITREP routes it UP.
7. MUST-2B-01..03 and 05..11 were CLOSED at 065734; rev5 touches none of their bytes — re-grade only if a rev5 change reaches one. MUST-2B-04, 12 and 13 are the rev5 fold: grade each against the exact bytes named in the revision history entry (T-STAGE routing + discriminator; T-FENCE gate with no product branch; canonical root + fast path + both discriminators; the Task 12 ordering line and the CEN row).
8. (carried from rev4, closed at 065734 unless a rev5 byte reaches it) The rev4 fold of m-1's fence rev2 against 171041 §1–§2 and 044559: c1a's placement after the unborn/shallow return and the W-O shapes; c1b's depth-scoped skip, the retained `.git`/symlink rules and the W-D cases (W-D1 as the discriminator; W-D3's two halves; W-D4's credited status); the RCPT-P / E4+RCPT-O rows; the V-2b-5 rev2 runner gate; T-PROM's scoping. Anything that reads a rev2 clause into a task it does not govern is a must-revise.

Merge ≠ push ≠ publication ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact rev5 (138a322), this relay and its INDEX row (path-scoped commit follows), no trailer; product bytes untouched at 186adf7d; no worktree, branch, token, push or release.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
