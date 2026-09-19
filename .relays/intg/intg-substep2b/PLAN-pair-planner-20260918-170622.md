## PLAN — sub-step 2b rev12 (intg-substep2b-plan-12; artifact f65000bf1ce230569c5f5dc9bc907944c3ff9fdc4f2434c90b959b1880995343 at docs commit 4ffd8cf): folds the implementer's exact-hash MUST-REVISE of rev11 (165800, MUST-2B-26 — `relay` resolved, never read; arm 2 identity-weak) — the Task 6b Step 0 block now BINDS three carriers, none by existence: (1) the A11 LOCK carrier `relay` = m-3.planner's DESIGN relay to master (exact `FROM: m-3.planner` / `TO: master.master-planner` / `PHASE: DESIGN` / `AUTHORITY: design-only` lines; the lock id as a whole word; the locked doc sha; the A11 document cited in RELATED_CONTEXT/IN_REPLY_TO); (2) a NEW `seal_relay` field = master's PLAN relay TO the pair (exact FROM/TO/PHASE/AUTHORITY lines) whose `IN_REPLY_TO` line is EXACTLY the lock relay (lineage), naming the same id + sha and the word SEALED, and ≠ `relay`; (3) the suffix word as before (arm 1 the 162306 ruling by sha256 + header + verdict; arm 2 now rides on the ALREADY-BOUND lock carrier declaring the field); every relay path tracked and unmodified in pdc (`git ls-files` + empty `status --porcelain`) besides the `..`-free beneath-`master/relays` resolution; the lock id accepts the A9-shaped `m3-addendum-11-<8 hex>-lock-<date>` or the planned `m3-addendum-11-<date>`, whichever the ceremony declares; receipts carry both carriers' sha256. VALIDATED ON A REAL CEREMONY: the carrier checks are the shape of the A9 lock (m-3 165214 → master 170242, post-stamp ae272647…) and the pair executed the block on it as the must-be-YES (the block plus exactly two constant substitutions — the doc path and the id prefix — diffed to prove that): pre + post PASS; nine must-be-NO controls STOP before any receipt — the reviewer's exact bypass (`relay` = 010159 with the true ruling ⇒ `lock-from`), `seal_relay` = 010159 (`seal-lineage`), `relay` = another m-3 DESIGN relay 134813 (`lock-to`), the planned-shape id absent from the carriers (`lock-id-absent-in-lock-relay`), arm 2 on a lock relay lacking the field (`lock-relay-spelling`), seal == lock (`lock-seal-same-file`), a master-to-pair PLAN not replying to the lock relay 135421 (`seal-lineage`), a wrong doc sha (`a11-sha-mismatch`), and the unmodified A11 block with `relay` = 010159 (`lock-from`); the block in the plan is byte-equal to the executed one. Everything else stands byte-for-byte from rev11 (MUST-2B-22..25 closed per 164316/165800; T-PARTIAL RULED (A); the M edge fields byte-identical to plan-7..11's at a1ce40a9, not re-swept per 152800; the four runner proofs 3/13/4/2, omitted 0). The lock file's writer (the pair Planner, at the lock) now records `seal_relay=` too — the LOCK IDS row says so

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-12
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-165800.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-165800.md; intg-substep2b/PLAN-pair-planner-20260918-164800.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-165214.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-170242.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-164316.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260918-163608.md; intg-substep2b/PLAN-pair-planner-20260918-162953.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260918-162306.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260918-153551.md; intg-substep2b/PLAN-pair-planner-20260918-140706.md; ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-restore-apply-contract.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260918-152800.md; intg-substep2b/SITREP-pair-planner-20260918-141053.md; docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-s2b-plan-edge-remeasure-20260917.txt; ../../pdc/master/domains/m-1-format-engine/design/2026-08-04-STEP4-DESIGN-PACKAGE.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260917-010159.md; ../../pdc/master/relays/intg-2b-wiring-act-m1-fence-review-r4/DESIGN-REVIEW-implementer-20260916-171135.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-161701.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-171446.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-170242.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-165214.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-134813.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-140043.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-140044.md; intg-substep2b/SITREP-pair-planner-20260916-090252.md; intg-substep2b/PLAN-pair-planner-20260916-082515.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-072353.md; intg-substep2b/PLAN-pair-planner-20260916-070942.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-074712.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-075225.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080308.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080306.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080307.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md; intg-substep2b/PLAN-pair-planner-20260916-054308.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-152914.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-164151.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-051652.md; ../../pdc/master/relays/intg-2b-wiring-act-m1-fence-review-r2/DESIGN-REVIEW-implementer-20260916-044559.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-171041.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-140509.md; intg-substep2b/PLAN-pair-planner-20260915-134648.md; docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r449-plan-edge-20260913.txt; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260915-132531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-132001.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-15-addendum-9-unclaimed-git-entry-and-offline-cli.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-131404.md; intg-substep2b/AUDIT-pair-planner-20260915-040846.md; intg-substep2b/AUDIT-pair-implementer-20260915-041820.md; intg-substep2b/SITREP-pair-planner-20260915-042253.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-041518.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-043301.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-042531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-130818.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-035001.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-m2-planner-20260915-125200.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md; docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md
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
DESIGN_SOURCE_COMMIT: a1ce40a930b5fd01d905e8295c3a9e581455a1c7
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md
DESIGN_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (A6 rev14, post-stamp 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771)
SECOND_CONSUMED_CONTRACT: m3-addendum-7-4c40fe37-lock-20260827 (A7 rev2)
THIRD_CONSUMED_CONTRACT: m3-addendum-8 lock d686e39a (A8 rev8)
FOURTH_CONSUMED_CONTRACT: m1-addendum-N-82293732-lock-20260827; m1-addendum-O-63c46631-lock-20260901; m4-sr-url rev5
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 f65000bf1ce230569c5f5dc9bc907944c3ff9fdc4f2434c90b959b1880995343
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — DOES NOT EXIST YET (no local ref, no remote head); Task 0 cuts it with a FRESH worktree ../bivpak-intg-substep2b-wiring from B and disposes the three retained pair worktrees with receipts
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev12 (intg-substep2b-plan-12; folds 165800 MUST-2B-26: the Task 6b gate binds the A11 lock carrier (m-3 DESIGN relay by header, lock id, doc sha, A11 cited) and master's seal relay (PLAN to the pair, IN_REPLY_TO the lock relay, same id + sha, SEALED), each tracked + unmodified in pdc; executed on the real A9 ceremony as the must-be-YES and nine controls incl. the reviewer's bypass; artifact f65000bf1ce230569c5f5dc9bc907944c3ff9fdc4f2434c90b959b1880995343 at docs commit 4ffd8cf)
REPO: `../bivpak` docs lane — the rev12 artifact committed path-scoped (4ffd8cf), no trailer; product bytes untouched at 186adf7d; the four runner blocks extracted and proved by the plan's own extractor (task-0 82 lines gates=3, task-9 157 gates=13, task-10 69 gates=4, task-11 53 gates=2; bytes=equal, omitted=0, out_of_order=0, check rc=0 each; bash -n rc=0 each; the eleven python instruments py_compile rc=0; the four shell instruments bash -n rc=0); `../pdc` READ-ONLY (the three fences, the five master relays, the sealed texts cited on the plan face)
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of f65000bf1ce230569c5f5dc9bc907944c3ff9fdc4f2434c90b959b1880995343; on approve the token mints in-lane with PARENT = your approving review; the contingent terms' words are NOT review inputs — each gates its own commit under the HOLD-before-bytes RULE); master CC (the companion SITREP carries the R5 dispositions, the edge measurement and the still-open Q8–Q13 UP); m-1 / m-3 / m-4 CC (your fences are graded against on the plan face by reference — nothing paraphrased as authority); operator CC (the hold stands; no byte moves)

## What the reviewer is asked to grade at f65000bf1ce230569c5f5dc9bc907944c3ff9fdc4f2434c90b959b1880995343 (every count below produced by its measuring command on the artifact at this hash)

```text
artifact          docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md — 2523 lines (rev12); placeholders 0; token phrases 0; census alternation 0
identity          NEW plan identity (intg-substep2b-plan); PLAN_LOCK_ID = the artifact's sha256; DESIGN record = the sealed set (M primary; A6/A7/A8/N/O/SR-URL consumed)
gates on the face gate ledger (i) IN (035001); (ii) m-4 / m-1 / m-3 IN, m-2 NOT a touch; (iii) in-as-scoped, re-run at the plan face and the candidate diff stat
commit order      c1a, c1b, c1c, c2, c3, c4a, c5 (the unconditional prefix), c3h, c6a (A9 sealed), c4b, c6b (lock order), c7, c8, c9 predeclared; veto 9 MECHANICAL checked by Task 9's runner (the first THREE commits engine-only at their exact path sets, restore.hpp numstat 2 0; no later engine path; no commit spans both sets; the scan.cpp diff carries no ".biv" line)
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

## The rev7 fold — what changed since rev6 (085404 + every word that landed), its source, and where it binds

```text
item                            source (verified at the bytes)                                 binds at              lands in
MUST-2B-22 c3 split proof       153551 (mine) — executed in a throwaway worktree at B              —                     c3 commit block (staged-object gate + controls); topology row c3h
MUST-2B-23 reconstruct + (a)–(m) A10 rev6 §A10.4 (j)–(m) at 17fda846                                A10 lock              Task 4 interface; c4b commit text; Task 7 A10 cell; E1-A10 row
MUST-2B-24 T-PARTIAL gate       153551 (mine); master 152800 (routing to m-1, rec. (A); R-4.61)     owner word (m-1)      ROUTED (17); T-PARTIAL; Task 6b Step 0 + `$EVID/code/c6b-partial-suffix.txt`
MUST-2B-21 RULED (A)            m-1.planner 162306 (TO master; pair CC) — re-verified: open.cpp:637, pack.cpp:550, restore-apply §2.1/§3, RENAME :33, DR-2   A11 lock file `partial_suffix=`   T-PARTIAL narrowed; Step 0's admissible value; (B) text removed
MUST-2B-25 executable gate      164316 (mine) — executed at B: pass ×2, STOP ×7                    A11 lock file (both fields)   Task 6b Step 0 block (pre/post); Step 5's receipt refusal; Files prose
MUST-2B-26 carriers bound       165800 (mine) — executed on the A9 ceremony: pass ×2, STOP ×9       A11 lock + seal relays        Task 6b Step 0 block (lock/seal/suffix carriers); LOCK IDS row (`seal_relay=`)
MUST-2B-18 c3 help bytes        025941 (mine)                                                  —                     c3 (none) / c3h (both) + a staged-hunk proof
MUST-2B-19 A10 rev6 forms/legs  A10 rev6 §A10.6 + §A10.4 (j)–(m) at 17fda846                   A10 lock              T-STAGE; Task 4 Steps 3/6; evidence E1-A10
MUST-2B-20 lock baselines       025941 (mine)                                                  —                     RULE; Task 4 Step 0; Task 6b title + Step 0
MUST-2B-21 partial-dir suffix   A11 rev5 §A11.2 vs open.cpp:637 (B) vs STEP4 DR-2               ROUTED (master → m-1/m-3) T-PARTIAL; c6b waits on `partial_suffix=` in A11's lock file
MUST-2B-14 c3 / c3h split       085404 (mine)                                                  —                     c3 (unconditional) / c3h (A9 sealed)
fence rev4: c1c + partition     m-1 161701 §1–§2; approve 171135; erratum 171446 (27 returns)   fence rev4 (approved) c1c (third engine commit) / Task 4 offline arm / D3 trigger
A9 SEALED                       m-3 165214; master 170242; pre 40eaea22 @ c2f7a6c7; post ae272647 lock (sealed)        c3h / c6a released; A9.4 D4 bytes golden until A10's lock
A10 rev6 (17fda846)             m-3 140043: the partition verbatim; trigger source c1c; A10.6 rev5 forms A10 lock (pending)   c4b: result.repos + schema; D3 surface; durable artifact; reconstruct forms
A11 rev5 (33c69913)             m-3 140044/140045; m-1 171446: OPEN INVARIANT kept; inventory.json  A11 lock (pending)   c6b: the nine kinds; sentences; objects; the failure inventory (distinct from §2.3's)
MUST-2B-15 / 16 / 17            closed by owners (A10.6 quoting; unborn idiom; the seam)         their locks           c4b / c6b
M edge                          master 010159: pin a1ce40a9; xroot_authority PASS (re-run here)  the carrier            DESIGN_SOURCE_COMMIT on this relay; one re-sweep after filing
ORDER                           master 010159 (unchanged)                                        —                     c1a c1b c1c c2 c3 c4a c5 → c3h c6a → c4b c6b (lock order) → c7 c8 c9
```

## MUST-2B-11 — the canonical cross-repo edge at the RE-PINNED source commit (master 010159; the third re-pin: 1e987860 → 631aae82 → a1ce40a9)

```text
declaration     unchanged except DESIGN_SOURCE_COMMIT: a1ce40a930b5fd01d905e8295c3a9e581455a1c7 (a PIN named by master, never HEAD);
                DESIGN_SHA256 57d89625… unchanged (the M rev8 blob re-hashed at that tree); DESIGN_DOC_ID m1-addendum-M-20260823; owner m-1
authority at    origins carrying the M doc id with PHASE DESIGN under master/relays @ a1ce40a9: unique-latest = intg-2b-wiring-act/
the pin         DESIGN-planner-20260916-161701.md (m-1's fence rev4); reviews with the M doc id AND PARENT_DISPATCH_ID intg-2b-wiring-act:
                …-r3/…-171018 (must-revise, rendered) and …-r4/DESIGN-REVIEW-implementer-20260916-171135.md (approve; FROM m-1.implementer,
                the planner origin's peer; stamp later than 161701) — unique-latest = 171135; 73 carriers enumerated
measured        relay-lint 2.9.3 imported as a module at this seat: xroot_authority(../pdc, <master/relays tree @ a1ce40a9>, {M, m-1}) → PASS
                (must-be-YES); the same call at 4636fcef and at 74810810 (trees holding the rev4 origin but not yet its approve) → FIRES
                `ordering: selected review is not later than selected origin` (must-be-NO) — the discriminator separates the trees; master
                executed the same function with the same result (010159); the earlier pin 631aae82 (its own origin/approve pair) still
                PASSES at its own tree, as an immutable tree must
root sweep      re-run ONCE after THIS relay is filed (kit 2.9.2 root mode, the same invocation as the three prior sweeps) with the FILED
                rev7 carrier in scope; archived beside results/lint-root-sweep-s2b-plan-edge-remeasure-20260916.txt; the fired set reported
                by SITREP; the review of this plan may proceed on the module-level PASS — if the sweep fires a declared-edge line on THIS
                carrier the pair STOPs and reports it, never re-pins on its own; the superseded carriers (144707 at 1e987860; 054308,
                070942, 082515 at 631aae82) keep their own measured state
ordering hazard the origin is unique-latest by stamp; at a1ce40a9 no PHASE DESIGN relay carrying the M doc id is later than 161701 (enumerated);
                a later one landing in pdc would re-select — the pin, not HEAD, is what the carrier declares and what the sweep measures
not declared    A9 (sealed; PASS at a1ce40a9 per master), A6 (PASS), A10 (rev6 origin awaits its review — fires ordering), A11 (rev5 origin
                awaits its review — fires ordering) are NOT declared as edges on this carrier; the A10/A11 terms bind at the LOCK id
```

## Review asks (each a must-revise if you find it wrong) — rev12 supersedes rev11 164800 (must-revised 165800); grade rev12 only

1. The sealed orderings as coded: pack-engine §1.1/§1.2/§1.3/§2/§4 in Task 5 Step 3; restore-apply §1/§2.2 in Task 4 Step 3; A7-R3's encounter points; the hook install scope in Task 3.
2. The hook truth table and the predicate dedup (I2B-02); the stderr-only consent surfaces (I2B-03); the a7·3 topology (I2B-04); the fence paths (I2B-05); the scan refusal precision (I2B-06); the tier labels (I2B-07); the case-count gate (I2B-08); the reader disposition (I2B-09 → option (b) + T-JSON).
3. The A8 policy placement (inside the four renderers, composed clauses 1–5, the generated table with pinned inputs; `display()` untouched).
4. The contingent-term gates: is each cell truly undetermined by sealed text, and does each gate block exactly the bytes the word governs and nothing more?
5. The runner blocks (Tasks 0/9/10/11): every gate a runner line; no evidence-producing pipeline; bash 3.2 syntax; the Linux leg's receipts.
6. Anything the plan DECIDES that an owner should have — name it; the SITREP routes it UP.
7. MUST-2B-26: extract the Task 6b Step 0 block; apply exactly the two substitutions (`2026-09-16-addendum-11-engine-error-surfacing-rows.md` → `2026-09-15-addendum-9-unclaimed-git-entry-and-offline-cli.md`; `m3-addendum-11-` → `m3-addendum-9-`) and run it against the REAL A9 ceremony — `lock_id=m3-addendum-9-40eaea22-lock-20260916`, `doc_sha256=ae27264763b5ec20057b88f78f87d642ab22a28305a532c66c44063603eb2cf0`, `relay=…/DESIGN-planner-20260916-165214.md`, `seal_relay=…/PLAN-master-planner-20260916-170242.md`, the suffix fields on 162306 — `MODE=pre` then `post` must PASS; then your bypass verbatim (`relay` = 010159 with the exact ruling) must STOP `lock-from` with NO receipt, and the other eight controls as the Step 0 prose lists them; confirm no carrier is accepted by existence (every acceptance line is an exact header line, a whole-word id, a sha, a lineage line or a pdc tracked+unmodified check). MUST-2B-22..25 and the RULED (A) transcription stand as you graded them.
8. The rev7 fold of m-1's fence rev4 (161701 §1, approve 171135; erratum 171446) against the bytes: c1c's contract wording (git-capable partition), the numstat bound, W-G1/G1c/G1n/G2/G3 as written, the count rule (the grep at the candidate head, never a carried number), the `--offline`/DECLINED partition in Task 4 (FALSE ⇒ CALL restore_entry), the D3 trigger READ from the predicate, ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership. (Carried from rev4, closed at 065734:) the fold of fence rev2 against 171041 §1–§2 and 044559: c1a's placement after the unborn/shallow return and the W-O shapes; c1b's depth-scoped skip, the retained `.git`/symlink rules and the W-D cases (W-D1 as the discriminator; W-D3's two halves; W-D4's credited status); the RCPT-P / E4+RCPT-O rows; the V-2b-5 rev2 runner gate; T-PROM's scoping. Anything that reads a rev2 clause into a task it does not govern is a must-revise.

Merge ≠ push ≠ publication ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact rev12 (4ffd8cf), this relay and its INDEX row (path-scoped commit follows), no trailer; product bytes untouched at 186adf7d; no worktree, branch, token, push or release.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
