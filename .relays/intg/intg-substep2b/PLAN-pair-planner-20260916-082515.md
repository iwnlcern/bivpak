## PLAN — sub-step 2b rev6 (intg-substep2b-plan-6; artifact 114eabe632339deb2ed85405c62af54c834368d86fc20453992e273264879c0b at docs commit 164cc48): OWED by master 080937 before the token — rev5 (5aabe373, APPROVED by the implementer at 072353 with HOLDs intact) is the baseline this revision is diffed against; rev6 folds EVERY owner word carried by 080937 as plan TERMS keyed on THREE contingent lock ids, each binding at ITS lock: A9 (`m3-addendum-9-20260915`, rev2 40eaea22) → c6a; A10 (`m3-addendum-10-20260916`, rev2 81e2abca) → c4b; A11 (`m3-addendum-11-20260916`, rev1 26161c41) → c6b. THE WORDS: Q11 (m-1 074712 §1) every pack fence is a WHOLE-OPERATION typed refusal — no image, never exclusion, never full+note; `unmerged` permanent, `dirty`/`nested`/`submodule` transitional (R-4.57) — Task 5 STARTS on it, surfacing fences through the engine seam at c5 with the refusal bytes landing at A11's lock; Q10 promisor = whole-op refusal at PACK only, both arms, `facts.offline` from the CLI flag; Q13 (m-1 §2 + A10.6) THE T-STAGE INTERIM IS OVER — under `open --offline` a full-capture row's `repo.bundle` is placed DURABLY at `<dest>/.biv/repos/<id>/repo.bundle` inside the §2.1 staging and carried by the rename (checksums-verified, zero git; overlay rows write nothing — R-4.58), with `bundle_path` (absolute printed / dest-relative JSON) and a URL-free `reconstruct` in TWO forms selected by `<dest>/<relpath>`'s state (clone | in-place) — rev5's drain-only routing stands at c4a and gains the placement at c4b; Q8 (m-3 075225 + A10.2) `--network` is NOT inert — A2 D3 EXECUTES: the NOTICE + PROMPT bytes quoted verbatim, before any git subprocess, once per run, A7-R1 predicate, decline ⇒ zero git + offline-pointer rows exit 0, `--network` non-interactive, `--json` mirror, `--offline` never, no persistence, no envelope member, PROMPT D untouched (c4b); Q9 (A10.1) `result.repos` = RepoRestoreRow verbatim + failed kind/detail + the offline fields, absent at zero state, schema in the same commit (c4b); the GAP → A11's nine wire kinds (three transitional fence refusals/3; Unmerged/RefUncapturable/PromisorObjectsUnavailable refusal/3; GitInvocationFailed/GitBudgetExpired/RepoRestoreFailed mid-fail/4), whole-operation grain, A11.2 error objects, A11.3 sentences rendered ONCE, ErrKind 27→36, exit map 29→38, unknown kinds stay InternalError (c6b). ORDER: the token's UNCONDITIONAL prefix is c1a c1b c2 c3 c4a c5; c6a/c4b/c6b land after c5 in lock order; c7–c9 after all three. ARM-1 REALITY (m-1 074712) applied to every fixture: `classify.cpp:347-357` fences ANY `git status --porcelain=v2` output — an untracked file is the dirty fence — so every packed fixture is CLEAN with `.gitignore`d penumbra; legs that need Arm 2/3/4 (patch round trip; nested two-row images; leaves-first and parents-before-children at product scope; submodules) are REGISTERED as T-ARM, the open-side ordering witness stays hand-built and labelled; W-D1's product form is the nested-fence refusal naming the nested repository (the any-depth-skip mutant packs it silently); the MUST-2B-02 leg corrected to the real bundle + local-refs round trip. No engine byte moves; the M edge unchanged at pdc 631aae82; the four runner proofs unchanged (3/13/4/2, omitted 0)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2b-plan-6
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-080937.md
RELATED_CONTEXT: intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-072353.md; intg-substep2b/PLAN-pair-planner-20260916-070942.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-074712.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-075225.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080308.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080306.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-080307.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md; intg-substep2b/PLAN-pair-planner-20260916-054308.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-152914.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-164151.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-051652.md; ../../pdc/master/relays/intg-2b-wiring-act-m1-fence-review-r2/DESIGN-REVIEW-implementer-20260916-044559.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-171041.md; intg-substep2b/PLAN-REVIEW-pair-implementer-20260915-140509.md; intg-substep2b/PLAN-pair-planner-20260915-134648.md; docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-r449-plan-edge-20260913.txt; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-REVIEW-implementer-20260915-132531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-132001.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-15-addendum-9-unclaimed-git-entry-and-offline-cli.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-131404.md; intg-substep2b/AUDIT-pair-planner-20260915-040846.md; intg-substep2b/AUDIT-pair-implementer-20260915-041820.md; intg-substep2b/SITREP-pair-planner-20260915-042253.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-041518.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260915-043301.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-042531.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-130818.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260915-035001.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-m2-planner-20260915-125200.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md; docs/sprints/2026-08-27-intg-consent-fabric/OBLIGATIONS.md
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
PLAN_LOCK_ID: intg-substep2b-plan-20260915 @ sha256 114eabe632339deb2ed85405c62af54c834368d86fc20453992e273264879c0b
BASE: B = origin/main = 186adf7d67171bd7afe621f39b657a1a113ce299 (the PUBLISHED pin, the R-4.49 landing merge; re-read at this filing)
BRANCH: intg/substep2b-wiring — DOES NOT EXIST YET (no local ref, no remote head); Task 0 cuts it with a FRESH worktree ../bivpak-intg-substep2b-wiring from B and disposes the three retained pair worktrees with receipts
TARGET_BRANCH: main — via a PR from the pushed remote branch at head H (R-4.51 (2)); the local merge under the operator's bare token filed under .relays/intg; the census FOR the merge head; R-4.52
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, operator, m-1.planner, m-3.planner, m-4.planner
SUBJECT: PLAN rev6 (intg-substep2b-plan-6; owed by master 080937; baseline = rev5 approved at 072353): every owner word folded as terms on three lock ids A9→c6a, A10→c4b, A11→c6b; Q11 fences whole-op refusals (Task 5 starts); Q10; Q13 durable artifact + two reconstruct forms; Q8 D3 executes; Q9 result.repos; the nine A11 kinds; token prefix c1a..c5 unconditional; ARM-1 reality on every fixture; T-ARM registrations; M edge unchanged at 631aae82; artifact 114eabe632339deb2ed85405c62af54c834368d86fc20453992e273264879c0b at docs commit 164cc48) — sub-step 2b wiring, both verbs; c1 engine offline input FIRST (m-1 S-2b-1) → c2 A8 policy inside the renderers + generated table → c3 flags/hook truth table/stderr writers/predicate dedup → c4 open repos/ class + restore_entry per row + result.repos[] + D4 listing → c5 pack sealed order + narrowed .git class → c6 UnclaimedGitEntry (contingent on m-3's lock) → c7 product-scope witnesses on biv-pack-produced images → c8 m-3 harness → c9 count cells iff moved (inside the Task 9 runner, H last); contingent terms gated under HOLD-before-bytes; runner tasks 0/9/10/11 proved with bound gates; the cross-repo design edge declared and measured; grade at the exact hash
REPO: `../bivpak` docs lane — the rev6 artifact committed path-scoped (164cc48), no trailer; product bytes untouched at 186adf7d; the four runner blocks extracted and proved by the plan's own extractor (task-0 82 lines gates=3, task-9 156 gates=13, task-10 69 gates=4, task-11 53 gates=2; bytes=equal, omitted=0, out_of_order=0, check rc=0 each; bash -n rc=0 each; the eleven python instruments py_compile rc=0; the four shell instruments bash -n rc=0); `../pdc` READ-ONLY (the three fences, the five master relays, the sealed texts cited on the plan face)
BRIDGE: intg.pair-planner → intg.pair-implementer (your exact-hash review of 114eabe632339deb2ed85405c62af54c834368d86fc20453992e273264879c0b; on approve the token mints in-lane with PARENT = your approving review; the contingent terms' words are NOT review inputs — each gates its own commit under the HOLD-before-bytes RULE); master CC (the companion SITREP carries the R5 dispositions, the edge measurement and the still-open Q8–Q13 UP); m-1 / m-3 / m-4 CC (your fences are graded against on the plan face by reference — nothing paraphrased as authority); operator CC (the hold stands; no byte moves)

## What the reviewer is asked to grade at 114eabe632339deb2ed85405c62af54c834368d86fc20453992e273264879c0b (every count below produced by its measuring command on the artifact at this hash)

```text
artifact          docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md — 2284 lines (rev6); placeholders 0; token phrases 0; census alternation 0
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

## The rev6 fold — every owner word of 080937, its source, the lock it binds at, and the commit it lands in

```text
cell   word (source)                                                          lock / gate                          commit   plan term
Q11    every pack fence = WHOLE-OP typed refusal; unmerged permanent;         RULED (074712 §1; R-4.57) — Task 5   c5 (seam)  T-FENCE
       dirty/nested/submodule transitional; never exclusion/full+note         STARTS; refusal bytes at A11's lock   c6b (kinds)
Q10    promisor_objects_unavailable = whole-op refusal, PACK only, both      RULED (074712 §2) + A11 lock          c5 → c6b  T-PROM
       arms; facts.offline from the CLI flag; no PromisorSourceOffline
Q13    durable <dest>/.biv/repos/<id>/repo.bundle via §2.1 staging (m-1 §2); RULED apply half + A10 lock (UX half:  c4b       T-STAGE
       bundle_path abs/rel; reconstruct URL-free, clone | in-place (A10.6)    $RUNNERS/m3-addendum-10-lock.txt)
Q8     --network NOT inert; D3 executes: notice+prompt verbatim before any   A10 lock (A10.2)                      c4b       T-NET
       git; decline ⇒ offline-pointer rows exit 0; --json mirror; --offline
       never; no persistence; PROMPT D untouched
Q9     result.repos: RepoRestoreRow verbatim + failed kind/detail + offline  A10 lock (A10.1); schema same commit  c4b       T-JSON
       fields; absent at zero state; manifest order
GAP    nine wire kinds; whole-op grain; A11.2 objects; A11.3 sentences;      A11 lock (A11.1–A11.3)                c6b       T-A11
       ErrKind 27→36; exit map 29→38; unknown stays InternalError
Q12    help lines after --accept-url-divergence, before --agent-bin (A9 rev2) A9 lock ($RUNNERS/m3-help-order.txt)   c3 (held) T-HELP
A9     UnclaimedGitEntry refusal/3; RepoDiscoveredUnsupported retired         A9 lock ($RUNNERS/m3-addendum-9-lock)  c6a       T-KIND
Q14    closed (m-3 §6; 015244 verbatim in series_verdict.py)                  —                                     Task 9    —
ARM-1  clean fixtures only; ignored penumbra; Arm 2/3/4 legs registered      m-1 074712 (fact) — no lock            Tasks 4/5/7  T-ARM
ORDER  token prefix c1a c1b c2 c3 c4a c5 unconditional; c6a/c4b/c6b in lock order after c5; c7–c9 after all three (master 080937)
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

## Review asks (each a must-revise if you find it wrong) — rev6 supersedes rev5 070942 (approved 072353, the diff baseline); grade rev6 only

1. The sealed orderings as coded: pack-engine §1.1/§1.2/§1.3/§2/§4 in Task 5 Step 3; restore-apply §1/§2.2 in Task 4 Step 3; A7-R3's encounter points; the hook install scope in Task 3.
2. The hook truth table and the predicate dedup (I2B-02); the stderr-only consent surfaces (I2B-03); the a7·3 topology (I2B-04); the fence paths (I2B-05); the scan refusal precision (I2B-06); the tier labels (I2B-07); the case-count gate (I2B-08); the reader disposition (I2B-09 → option (b) + T-JSON).
3. The A8 policy placement (inside the four renderers, composed clauses 1–5, the generated table with pinned inputs; `display()` untouched).
4. The contingent-term gates: is each cell truly undetermined by sealed text, and does each gate block exactly the bytes the word governs and nothing more?
5. The runner blocks (Tasks 0/9/10/11): every gate a runner line; no evidence-producing pipeline; bash 3.2 syntax; the Linux leg's receipts.
6. Anything the plan DECIDES that an owner should have — name it; the SITREP routes it UP.
7. MUST-2B-01..13 were CLOSED at 072353 (rev5); rev6 re-opens by design exactly the cells the owner words changed — T-STAGE (now a durable placement at c4b over the c4a drain), T-FENCE (now RULED: Task 5 starts; the refusal bytes at A11's lock), T-NET (now D3 executes at c4b), T-JSON (now A10.1's rows at c4b), T-PROM (now A11's kind) — grade each against the addendum bytes QUOTED in the terms block and the owner relays named on the face; any paraphrase that drifts from A10 rev2 / A11 rev1 / 074712 is a must-revise (they bind at their LOCKS; the plan re-verifies against the locked pin before writing).
9. The ARM-1 consequences: every fixture that packs is clean with `.gitignore`d penumbra (an untracked file is the dirty fence — classify.cpp:347-357); the MUST-2B-02 leg corrected (no patch artifact exists); W-D1's product form as the nested-fence refusal; the T-ARM registrations (patch round trip; two-row images; leaves-first / parents-before-children at product scope; submodules) — name any leg that still asserts a dirty/nested/submodule pack succeeding, or any Arm-2/3/4 behaviour asserted at product scope.
10. The commit topology and the token rule: c1a c1b c2 c3 c4a c5 unconditional; c6a/c4b/c6b in lock order after c5; c7 after the last of them; every c4b/c6b byte planned from the reviewed revision and re-verified at the locked pin; the same-commit rules (A10 schema; A11 enum/exit-map/tests; A9 as before).
8. (carried from rev4, closed at 065734 unless a rev5 byte reaches it) The rev4 fold of m-1's fence rev2 against 171041 §1–§2 and 044559: c1a's placement after the unborn/shallow return and the W-O shapes; c1b's depth-scoped skip, the retained `.git`/symlink rules and the W-D cases (W-D1 as the discriminator; W-D3's two halves; W-D4's credited status); the RCPT-P / E4+RCPT-O rows; the V-2b-5 rev2 runner gate; T-PROM's scoping. Anything that reads a rev2 clause into a task it does not govern is a must-revise.

Merge ≠ push ≠ publication ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the plan artifact rev6 (164cc48), this relay and its INDEX row (path-scoped commit follows), no trailer; product bytes untouched at 186adf7d; no worktree, branch, token, push or release.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
