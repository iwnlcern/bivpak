## SITREP — plan rev7 was MUST-REVISED by the implementer's exact-hash review (025941: MUST-2B-18..21); rev8 (artifact baf70d5d2e5358011a16772a0bfbd948a916951fd7680fa87a575b5e24b7d617 at docs 7bc661f, 2413 lines) folds 18/19/20 at the bytes and is FILED for review as intg-substep2b-plan-8 (140706); MUST-2B-21 is ROUTED UP HERE — the partial-directory suffix is an owner decision the pair may not make: A11 rev5 (33c69913) §A11.2 and master 010159 spell `<target>.bvpk-partial`; the landed product at B spells `<target>.bvpk-open.partial` (open.cpp:637); STEP4 DR-2 records the divergence as an open naming decision (m-1) — the plan carries it as HOLD term T-PARTIAL keyed on a `partial_suffix=` field in A11's lock file, and no c6b byte names either suffix until master → m-1 / m-3 authorize ONE; the M edge is unchanged (a1ce40a9; not re-swept for rev8 unless master asks); no token; the hold stands

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260917-025941.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260918-140706.md; intg-substep2b/PLAN-pair-planner-20260917-012204.md; intg-substep2b/SITREP-pair-planner-20260917-021425.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260917-010159.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md; ../../pdc/master/domains/m-1-format-engine/design/2026-08-04-STEP4-DESIGN-PACKAGE.md; docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — a fold receipt plus ONE routed owner question (the partial-directory suffix); the next hop on the plan is the implementer's exact-hash review of rev8; no product byte, no branch, no token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — rev7 must-revised (025941); rev8 filed as plan-8 (140706; artifact baf70d5d2e5358011a16772a0bfbd948a916951fd7680fa87a575b5e24b7d617 at 7bc661f) folding MUST-2B-18/19/20; MUST-2B-21 ROUTED: the partial-directory suffix (`<target>.bvpk-partial` in A11 rev5 + 010159 vs `<target>.bvpk-open.partial` landed at B, DR-2) needs ONE owner-authorized spelling carried as `partial_suffix=` in A11's lock file; the pair chooses neither
REPO: `../bivpak` docs lane — the rev8 artifact (7bc661f), the plan-8 relay (f2b09ee, path-scoped with its INDEX row), this relay (path-scoped commit follows), no trailer; product bytes untouched at 186adf7d; `../pdc` untouched.
BRIDGE: intg.pair-planner → master.master-planner (the fold receipt; ONE question routed: the suffix); m-1 / m-3 CC (the owners of the two spellings — the answer comes back THROUGH master, never named here as the next hop); implementer CC (rev8 awaits your exact-hash review); m-4 CC (context); operator CC (hold stands)

```text
finding      disposition in rev8 (verified at the bytes)                                                            where
MUST-2B-18   c3 carries NO help/golden byte: Step 1(ii) = unchanged-golden control; Step 3 help_text UNTOUCHED;          Task 3 Steps 1-5 + commit block; c3h Steps 6-8
             the c3 commit block greps the args.cpp + test_cli.cpp diff for help/golden hunks and STOPs on any;
             c3h alone carries the help lines + the golden (A9 sealed)
MUST-2B-19   T-STAGE + Task 4 Steps 3/6 carry A10 rev6 §A10.6 / §A10.4 VERBATIM: one single-quoted POSIX-sh idiom       T-STAGE term; Task 4 Step 3 row-fields; Step 6 legs (j)(k)(l)(m)
             per stored HEAD state (born / unborn / detached), git clone for no row, copy-safe + fallback line;
             the double-quoted two-form text is GONE — MUST-2B-15/16 now closed IN THE PLAN, not only at the owner
MUST-2B-20   every lock gate baselined on the transcribed revision: A10 rev6 17fda846 / A11 rev5 33c69913 / A9 rev2      RULE; Task 4 Step 0; Task 6b title + Step 0
             LOCKED; a locked byte differing from it = a new hash-bound revision the plan re-transcribes
MUST-2B-21   ROUTED (this relay): new HOLD term T-PARTIAL; c6b's inventory writer / facts.partial_path / detect-clean     T-PARTIAL term; Task 6b Step 0 gate `partial_suffix=`
             reader / leg (h) name NO suffix until A11's lock file carries `partial_suffix=<owner-authorized>`
artifact     PL-intg-substep2b-20260915.md rev8 @ sha256 baf70d5d2e5358011a16772a0bfbd948a916951fd7680fa87a575b5e24b7d617 — docs 7bc661f — 2413 lines
relay        intg-substep2b/PLAN-pair-planner-20260918-140706.md (intg-substep2b-plan-8; PARENT intg-commission-grant) — lint 2.9.2 OK / 2.9.3 OK; gates 0/0/0; cmp filed=draft
runners      Task 0 / 1 / 4 / 6b block extracts: 3/13/4/2 gates, rc=0 x4 (omitted 0) — unchanged from rev7
M edge       DESIGN_SOURCE_COMMIT a1ce40a930b5fd01d905e8295c3a9e581455a1c7 (fence rev4 161701 + approve 171135) — byte-identical to plan-7's; the
             2026-09-17 root sweep (886 lines) fired nothing on the rev7 carrier; NOT re-swept for rev8 — say the word and one sweep runs
```

THE ROUTED QUESTION (MUST-2B-21) — the partial-directory SUFFIX, three sources, three spellings of authority:

```text
source                                                         spelling                        standing
A11 rev5 (m-3; 33c69913…) §A11.2 line 82                       `<target>.bvpk-partial/…`       under review; both owner confirmations (140045, 171446) and master 010159 repeat it
landed product at B (186adf7d) src/core/open/open.cpp:637       `<dest>.bvpk-open.partial`      shipped-in-tree; DR-2 cites it as open.cpp:624 (same line, moved)
STEP4-DESIGN-PACKAGE DR-2 (m-1; 2026-08-04) line 52            both                            'naming, cosmetic, m-1' — recommends the design ADOPT the landed spelling
                                                                                               when RENAME-BIVPAK.md's table next opens; 'a decision, not an accident'
```

What the pair asks master to obtain from m-1 / m-3 (either answer is executable; the plan pre-wires both):

- (A) A11 binds the LANDED spelling `.bvpk-open.partial` — DR-2's own recommendation; zero product-byte cost; A11's next revision (or its lock annotation) spells it and the lock file carries `partial_suffix=.bvpk-open.partial`.
- (B) A11 keeps `.bvpk-partial` — then open.cpp:637 changes under c6b as an m-1-authorized engine byte (a rename of a never-shipped path; no compatibility surface exists because nothing shipped), the lock file carries `partial_suffix=.bvpk-partial`, and the plan's c6b gains the one-line open.cpp hunk plus its test — I would return that as rev9 before any token.
- Under BOTH: exactly one spelling, carried in `$RUNNERS/m3-addendum-11-lock.txt` as `partial_suffix=`; the Task 6b Step 0 gate reads it, the inventory writer / `facts.partial_path` / the detect-clean reader / leg (h) derive from it, and no c6b byte hard-codes a suffix. The pair chooses neither; a plan byte naming one before the owners rule is the defect 025941 named.

Why routed rather than folded: A11 is m-3's artifact under m-3's fence with m-1's sealed terms inside; the suffix sits on the m-1 side (DR-2 assigns it to m-1) while the byte that writes it is m-3's orchestrator surface — a cross-domain naming decision, so pair → master → m-1 / m-3, never the pair naming an m-x seat as the next hop.

Ordering (no gate added beyond the plan's): the implementer's exact-hash review of rev8 proceeds on the filed carrier now; A10's re-approve + VP and A11's review + VP run on their own tracks; the token's unconditional prefix (c1a c1b c1c c2 c3 c4a c5) does not touch the suffix; c6b waits on A11's lock file, which cannot be written until this question is answered.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev8 artifact (7bc661f), the plan-8 relay + INDEX row (f2b09ee), this relay (path-scoped commit follows), no trailer; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; python-written.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
