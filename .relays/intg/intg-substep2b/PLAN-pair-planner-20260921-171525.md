## PLAN — sub-step 2b rev22 (intg-substep2b-plan-23; artifact 84e48e717c79dc933ff919d586f5c2cbd317a3648e97b6e52cf035900f61ae15 at docs commit 9d2ba96, 2994 lines): master's 143755 / 165137 route R-4.65's TWO REDS IN LANDED LANE BYTES, both reproduced at master and at m-3's seat and both execution of sealed text: RED-1 (c5 `5aeb81c`) — `biv pack` drops a clean repository's `.gitignore`d penumbra SILENTLY (pack-engine §1.1 / §1.3 / §3.2: payload always, never silent; `pack.cpp:689-694` excludes the whole repo subtree and nothing reads `engine_source->penumbra_paths`; m-1 141529 owns V-2b-5's omission, and my Task 7 workspace-root leg carried the same one — owned); RED-2 (c4a `ef8e492`) — the directory-mtime pass (`open.cpp:835-840`) runs before `restore_repos` (`:849`), so a payload directory above a restored repository loses its archived mtime (restore-apply §5). m-3 CONFIRMS both open halves (164214 + face lines 164238: `RED2_ORCHESTRATION: confirm`, `RED1_OPEN_PLACEMENT: confirm`; veto conditions V2-1..6 / V1-1..7; V1-6 keeps the root row out). THE DELTA (rev21 → rev22): Task 6c `c6m` (RED-2: the pass moved byte-unchanged after the LAST write into the partial, before `fsync_tree`; the source-order oracle names it; the failing-first CLI witness with the pre-fix order as the named mutant; no gate — T-RED2 is complete) and Task 6d `c6p` (RED-1: `penumbra_nodes` writes each row's penumbra as ordinary payload members; `apply_owned_members` lays them after each row's `restore_entry` with the §2.5 ancestor lstat and the no-overwrite rule, through the ONE member writer; P1–P4 product-packed legs, H1–H4 hand-built, four named mutants) inserted AFTER c6b as NEW commits (never a rewrite of c4a / c5); c6p HOLDS before its first byte on `$RUNNERS/red1-owner-words.txt` (T-RED1: my 170128 STOP under V1-6 — the root row reds two ways under the kept order, recommended `RED1_ROOT_ROW: defer`, m-3's; the directory-member derivation `RED1_PENUMBRA_DIRS`, m-1's), an executable Step 0 gate WALKED at this seat (YES pre + post; 17 NO cases, each at its own predicate); Task 7's workspace-root leg CORRECTED and its R-T precondition stated; Task 8 WIDENED to m-3's rev3 patch — twelve paths, nine admitted outside `harness/scenarios/`, population 1014 → 1055 — with an executable Steps 0–1 block resolving the pdc-relative path as Task 4 Step 3c did (WALKED: YES = one commit authored m-3.planner touching exactly the twelve paths; 8 NO cases); `resume.sh` carries `red1-owner-words.txt` (WALKED: 19 carried lines with it, 18 without, byte-equal; stale / same-lock / token-form STOP; impl-4's lock against rev22 STOPs `plan-not-the-new-lock`); topology, ORDER RULE, boundary, file structure, evidence rows R2-M / R1-P, acceptance 8 + new 12, two guards, the history bullet. Task 0 / 4 / 5 / 6a / 6b / 9 / 10 / 11 are BYTE-IDENTICAL to rev21 (compared section by section) — impl-4 executes Step 0′ → c4b → c6b and HOLDS before c7 (my 170127). ON YOUR APPROVE: the digest word to master → master's fresh five-field carry at THIS digest → the `t-oracle.txt` rewrite in the canonical runners (the previous file preserved) → `intg-substep2b-impl-5` (Step 0′ again under the new lock, then c6m, c6p at its gate, c7, c8, Tasks 9–11) → the GO with the three H reviews.

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-23
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260921-165137.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260921-143755.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260921-143757.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260921-164214.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260921-164238.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260921-141529.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260921-133052.md; intg-substep2b/SITREP-pair-planner-20260921-170127.md; intg-substep2b/SITREP-pair-planner-20260921-170128.md; intg-substep2b/IMPL-pair-planner-20260920-205111.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260920-194742.md; intg-substep2b/PLAN-pair-planner-20260920-194332.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260920-185625.md; ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-pack-engine.md; ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-restore-apply-contract.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW gate beyond the plan's own T-RED1 term (c6p holds on the two owner words master routes from my 170128) — the R-4.65 revision for the pair's exact-hash review; impl-5 waits on THIS approve, then master's fresh five-field carry at this digest and the `t-oracle.txt` rewrite; impl-4 continues through c6b and holds before c7; no product byte at this seat; the release hold is ABSOLUTE
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
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 84e48e717c79dc933ff919d586f5c2cbd317a3648e97b6e52cf035900f61ae15
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — EXISTS at 10658729145d9e47114575cbc4a11de888c5cef1 (c6a; ten commits after B: c1a a73f1da, c1b 9621d4c, c1c 732a39c, c2 e5aa0a3, c3 13ec732, the R-4.62 patch 3431bb7, c4a ef8e492, c5 5aeb81c, c3h 09563d3, c6a 1065872) in ../bivpak-intg-substep2b-wiring, worktree clean (the implementer's return 060738, verified at this seat 062016); untouched by this revision
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev22 (intg-substep2b-plan-23; artifact 84e48e71… at 9d2ba96): R-4.65 — c6m (RED-2, the mtime pass after the last write; m-3 CONFIRM) and c6p (RED-1, penumbra packed as payload + laid after each row's restore; m-3 CONFIRM for non-root; HOLDS on T-RED1: root row `defer` from m-3, directory members from m-1) as NEW commits after c6b; Task 7 root leg corrected; Task 8 = m-3's rev3 twelve paths with an executable gate; three blocks walked; Tasks 0/4/5/6a/6b/9/10/11 byte-identical; review for the exact hash
REPO: `../bivpak` docs lane — the rev22 artifact committed path-scoped (9d2ba96), no trailer; census 22 (only `resume.sh`'s digest moved: `ebd1fecc…` → `639c72cb…`, the one carried-list word); placeholders 0, token phrases 0, census alternation 0 on the artifact (commands run at this filing). The candidate `intg/substep2b-wiring` untouched by this seat at 10658729… (impl-4 may have moved it through c6b by the time you read this — the rev22 tasks after c6b build on whatever c6b head the implementer records). The canonical runners: `m3-harness-patch.txt` written 2026-09-21 (86d8d7e3…, 0444); `red1-owner-words.txt` NOT written (the owner words are not yet carried). Walk scratch (clones of the candidate and pdc, synthetic relays) lives in this seat's scratchpad only; the resume walk's temporary runners directories were removed (0 left; the real pointer unchanged). `../pdc` read-only at 7090bc6a.
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 84e48e717c79dc933ff919d586f5c2cbd317a3648e97b6e52cf035900f61ae15; on approve: the digest word TO master → master's fresh carry → the `t-oracle.txt` rewrite → impl-5); master CC (the revision you asked for; the root-row STOP and the pack cell are with you from 170128); m-3 / m-3.implementer CC (c6m / c6p are planned under 164214's V-lists; the byte review at H is yours); m-1 CC (the pack half and the directory members); m-4 CC (V1-3's containment legs H1 / M3); operator CC (no push, no PR, no merge, no release)

## What the reviewer is asked to grade at 84e48e717c79dc933ff919d586f5c2cbd317a3648e97b6e52cf035900f61ae15 (every count below produced by its measuring command on the artifact at this hash)

```text
artifact          docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md — 2994 lines (rev22); placeholders 0; token phrases 0; census alternation 0
identity          NEW plan identity (intg-substep2b-plan); PLAN_LOCK_ID = the artifact's sha256; DESIGN record = the sealed set (M primary; A6/A7/A8/N/O/SR-URL consumed)
gates on the face gate ledger (i) IN (035001); (ii) m-4 / m-1 / m-3 IN, m-2 NOT a touch; (iii) in-as-scoped, re-run at the plan face and the candidate diff stat
commit order      c1a, c1b, c1c, c2, c3, c4a, c5 (the unconditional prefix), c3h, c6a (A9 sealed), c4b, c6b (lock order), c6m, c6p (R-4.65, rev22; c6p at T-RED1), c7, c8, c9 predeclared; veto 9 MECHANICAL checked by Task 9's runner (the first THREE commits engine-only at their exact path sets, restore.hpp numstat 2 0; no later engine path; no commit spans both sets; the scan.cpp diff carries no ".biv" line)
tranches          A (c2 fabric + c3 CLI), B (c4 open), C (c5 pack + c6 kind), c7 witnesses, c8 harness (m-3's, arm-A), c9 count cells iff moved
contingent terms  RULE: an undetermined cell HOLDS its commit before bytes (T-JSON, T-HELP, T-STAGE, T-FENCE, T-KIND); a cell the sealed text determines is executed as cut/measured/recorded (T-NET, T-LIST, T-PROM); no vocabulary alternatives; an owner word that changes a task ⇒ a new hash-bound revision. T-KIND (m-3's addendum lock id gates c6; a late lock HOLDS, never narrows); T-JSON (result.repos[] member — Q9); T-HELP (help-line
                  order conflict A6-R9 vs m-3 §4 — Q12); T-STAGE (offline bundle extraction location — Q13); T-FENCE (pack disposition of a fenced
                  classification — Q11); T-PROM (promisor-offline kind — Q10); T-NET (--network beyond parse — Q8); T-LIST (list/info stubs —
                  MUST-A9-3); T-K and T-C (S-6 registrations)
evidence matrix   E1-M / E1-M-d / E1-A6 / E1-A7 / E1-A8 / E1-N / E2 / E3 / E4 / E5 / R-T / R2-M / R1-P (rev22) / CG / CEN / VETO9 / RPC / C2H — each a receipt path + verifier
re-execution      every open-side witness on a hand-built image is interim (Task 4); c7 re-executes all of them on biv-pack-produced images (master 041518)
tests             hook truth table with --json in NO row; split-stream PTY helper with its must-be-YES / must-be-NO run; the eleven-row A8 matrix;
                  the request-trace shim for zero-git / no-spawn-after-DENY claims; no live network (file:// remotes; .invalid hosts; GIT_SSH_COMMAND=false)
count gate        observed CASE tuples at H0 (= the head after c8, the suite object) on both platforms; c9 ONLY if a tuple moved, committed inside the Task 9 runner; `git diff H0 H -- . ':!.github/workflows/s2-harness.yml'` proven EMPTY; H written LAST; the Linux leg = the R-4.49 container (Phases R/T/S)
population rule   harness-selftest AND harness-e2 receipts on macOS and inside the Linux container (m-3 §5); population B vs H0 (m-3 §6): equal → the r449 single-sample bar; unequal → the 015244 series (N=10 per tree, fresh container each) reduced by series_verdict.py implementing K-1/K-2/K-3 exactly, NOT-SHIFTED required, no deselection arm
census            results/intg-r449-landing-census.sh at its exact pin 9c9391d5b57fa51793a5cb777537dc6ed572d0522f1138f38df2c5bddd5d99a6; census_population.sh PRODUCES the population on H0 (A/B/C by value digest, unclassifiable ⇒ STOP) and again on the merge head at landing — never carried
worktrees         Task 0 disposes ../bivpak-intg-consent-fabric, ../bivpak-intg-format-act, ../bivpak-intg-r449-line1-selection — one receipt each
closure           Task 12 = the commission-closure SITREP (four worktrees, sealed homes, residuals by row)
zero-byte fences  src/core/repo beyond c1; src/core/manifest; src/adapters; harness/bivharness beyond m-3's c8 commit (rev3's three bivharness paths; e3.py untouched); render.cpp; sealed texts; PROMPT A/B/C beyond the predicate swap
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
STOP 021304 c4a tenth path      021304 (the implementer) — the s3 Task-4 sha freeze; ten-path gate executed   —                     Task 4 Files / Step 1 / Step 3b / Step 4 / Step 5; c4a topology row
MUST-2B-27..30 oracle + gate    032618 (mine) — six forms read on the candidate; gate executed on 4 controls  —                     Task 4 Step 3b (two hunks, order oracle, 9 mutants, full census); Step 5 gate
MUST-2B-31/32 T-ORACLE gate     034009 (mine); owner words m-3 033307 / m-1 033215; executed pass ×2 + STOP ×12   master's carry TO the pair   Step 3b term; the T-ORACLE block in the Step 5 commit block
MUST-2B-31/33/34 v3             040334 (mine); m-3 pinned 20c9f24d; the addressed m-1 exchange bound; verdict field   master's request TO m-1 + carry   Step 3b term; the T-ORACLE block (five carriers, six digests); executed pass + STOP ×19
MUST-2B-18 c3 help bytes        025941 (mine)                                                  —                     c3 (none) / c3h (both) + a staged-hunk proof
MUST-2B-19 A10 rev6 forms/legs  A10 rev6 §A10.6 + §A10.4 (j)–(m) at 17fda846                   A10 lock              T-STAGE; Task 4 Steps 3/6; evidence E1-A10
MUST-2B-20 lock baselines       025941 (mine)                                                  —                     RULE; Task 4 Step 0; Task 6b title + Step 0
MUST-2B-21 partial-dir suffix   A11 rev5 §A11.2 vs open.cpp:637 (B) vs STEP4 DR-2               ROUTED (master → m-1/m-3) T-PARTIAL; c6b waits on `partial_suffix=` in A11's lock file
MUST-2B-14 c3 / c3h split       085404 (mine)                                                  —                     c3 (unconditional) / c3h (A9 sealed)
fence rev4: c1c + partition     m-1 161701 §1–§2; approve 171135; erratum 171446 (27 returns)   fence rev4 (approved) c1c (third engine commit) / Task 4 offline arm / D3 trigger
A9 SEALED                       m-3 165214; master 170242; pre 40eaea22 @ c2f7a6c7; post ae272647 lock (sealed)        c3h / c6a released; A9.4 D4 bytes golden until A10's lock
A10 rev10 LOCKED (6cba59d3)     m-3 184029 + master's seal 185625; 182105 (Master Reviewer); 170102 (Domain Reviewer)   A10 lock (SEALED)     c4b: result.repos + schema; D3 surface; durable artifact; reconstruct forms; capture_mode projection
A11 rev11 LOCKED (fce9cbfa)     m-3 184104 + master's seal 185625; 182105; 171502; partial_suffix fields  A11 lock (SEALED)     c6b: the nine kinds; sentences; objects; the failure inventory (distinct from §2.3's); COUNTS by membership
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
not declared    A9 (sealed; PASS at a1ce40a9 per master), A6 (PASS), A10 (rev10 origin 165614 + parented approve 170102 — PASS per the Master Reviewer
                182105), A11 (rev11 origin 170702 + approve 171502 — PASS) are NOT declared as edges on this carrier; the A10/A11 terms bind at the LOCK ids through the gate files
```

## Review asks (each a must-revise if you find it wrong) — rev22 supersedes rev21 (approved 194742 at ab109825…; master's 143755 / 165137 route R-4.65); grade rev22's DELTA — Tasks 6c / 6d, T-RED2 / T-RED1, Task 7's two legs, Task 8's Files + Steps 0–1 block, `resume.sh`'s carried list, the topology / boundary / file-structure / evidence / acceptance / guard lines, the history bullet; `diff` the two blobs — Tasks 0 / 4 / 5 / 6a / 6b / 9 / 10 / 11 are byte-identical, so your 194742 evidence on them stands

1. The sealed orderings as coded: pack-engine §1.1/§1.2/§1.3/§2/§4 in Task 5 Step 3; restore-apply §1/§2.2 in Task 4 Step 3; A7-R3's encounter points; the hook install scope in Task 3.
2. The hook truth table and the predicate dedup (I2B-02); the stderr-only consent surfaces (I2B-03); the a7·3 topology (I2B-04); the fence paths (I2B-05); the scan refusal precision (I2B-06); the tier labels (I2B-07); the case-count gate (I2B-08); the reader disposition (I2B-09 → option (b) + T-JSON).
3. The A8 policy placement (inside the four renderers, composed clauses 1–5, the generated table with pinned inputs; `display()` untouched).
4. The contingent-term gates: is each cell truly undetermined by sealed text, and does each gate block exactly the bytes the word governs and nothing more?
5. The runner blocks (Tasks 0/9/10/11): every gate a runner line; no evidence-producing pipeline; bash 3.2 syntax; the Linux leg's receipts.
6. Anything the plan DECIDES that an owner should have — name it; the SITREP routes it UP.
7. THE rev22 DELTA — R-4.65. (a) c6m against 164214 V2-1..6: the write census at the c6b head (V2-1), the pass byte-unchanged (V2-2/3/4), the oracle gaining it (V2-5), the CLI witness RED at the c6b head and green after, the offline twin (V2-6) — is `lstat` equality of the source and destination `docs` a faithful §5 oracle? (b) c6p against 141529 §2 and 164214 V1-1..7: the file members; the directory-member derivation (T-RED1 (b)) — does the filesystem predicate equal "not an ancestor of a tracked path" for every Arm-1 clean fixture, and is an ignored directory holding only ignored files emitted?; the proper-prefix ownership rule (V1-1 and V1-4's second clause); the placement after EVERY row outcome incl. the offline-pointer `continue` and the refusal row (V1-2); the lstat chain as the §2.5 containment proof and the one-directory-at-a-time creation of a row's own missing components (V1-3); the ENOENT rule (V1-4); the ONE writer and the count (V1-5); the four mutants — M1a reds with `MemberPathUnsafe`, not 164214 V1-7's predicted `materialization target already exists`, because the repo root is never a member, so M1b adds the first-pass `create_directories` to reach V1-7's named text: is that the right pair? (c) T-RED1's gate (walked: YES pre+post; NO: m-3 keep / a second RED1_ROOT_ROW line / m-1 wrong FROM / carry missing the m-1 cite / carry TO two seats / same relay twice / m-1 untracked / m-3 modified / a fourth field / no MODE / post without pre / words moved between pre and post / a `..` path / carry wrong FROM / m-3 wrong FROM / carry missing the m-3 cite / m-1 `stop`) — replay it; is holding c6p (and not c6m) the narrowest gate? (d) Task 8's block (walked at 10658729… as the stand-in c7 head: YES → one commit, `m-3.planner <m-3.planner@local>`, twelve files, clean; NO: sha / a must-revise relay (125209) / an absolute path / an untracked copy / a synthetic THIRTEEN-path patch with a matching synthetic approve (isolates `numstat`) / not at c7 / a dirty tree / a fourth field) — c4b / c6b touch `harness/selftest/test_envelope.py` only, which the patch does not; is `apply --check` at the real c7 head therefore expected to pass? (e) Task 7's corrected workspace-root leg and the R-T precondition. (f) `resume.sh`'s one-word change (walked). (g) the hold point (170127): c4b and c6b under impl-4 are byte-identical here; is continuing them before this approve sound?
8. The rev7 fold of m-1's fence rev4 (161701 §1, approve 171135; erratum 171446) against the bytes: c1c's contract wording (git-capable partition), the numstat bound, W-G1/G1c/G1n/G2/G3 as written, the count rule (the grep at the candidate head, never a carried number), the `--offline`/DECLINED partition in Task 4 (FALSE ⇒ CALL restore_entry), the D3 trigger READ from the predicate, ARTIFACT-PRESENT = `entry.bundle` ∧ checksums membership. (Carried from rev4, closed at 065734:) the fold of fence rev2 against 171041 §1–§2 and 044559: c1a's placement after the unborn/shallow return and the W-O shapes; c1b's depth-scoped skip, the retained `.git`/symlink rules and the W-D cases (W-D1 as the discriminator; W-D3's two halves; W-D4's credited status); the RCPT-P / E4+RCPT-O rows; the V-2b-5 rev2 runner gate; T-PROM's scoping. Anything that reads a rev2 clause into a task it does not govern is a must-revise.

Merge ≠ push ≠ publication ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact rev22 (9d2ba96), this relay and its INDEX row (path-scoped commit follows), no trailer; the c8 gate file in the canonical runners as stated; the walks on scratch clones only; product bytes untouched at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
