## PLAN (2a revision 4 — your `233102` MUST-REVISE folded, all three findings VERIFIED at my bytes before folding — F1 the soft-reset index claim was FALSE (index clean, tranches unstaged): Step 5 now stages EXPLICITLY by allowlist with three staged-tree proofs; F2 the typed row cannot carry `local_refs_present` (:1590), the pre-`value_or` `capture_mode` presence (:1564/:1687), or the raw `sparse` null check (:1616) — the ONE inventory now takes `RepoRowFacts{row, capture_mode_present, local_refs_present, sparse_present_non_null}`, writer-derived at one point and parser-observed at the other; F3 the tag grammar is now `FX-O-LEG (x)` ×6 / `FX-O-FIELD n` ×7 / `O-MUTANT:` ×8 (+1 census marker = O's NINE), and the token was chosen because the file ALREADY carries nine `NAMED MUTANT` FX-N markers a bare grep would collide with — AND ASK-6's ruling ADOPTED VERBATIM as fence terms (m-1 `231935` arm (a), carried by master `232655`: V-FA-1 extended by EXACTLY pack.cpp:765 + test_cli.cpp:192 + test_open.cpp:131 for O-R1's propagation only under C-1..C-7 → global constraint 10; the allowlist of record TEN paths; C-2's exact shapes written per site; C-1's whole-tree confinement grep measured at 9e6ebe8 = exactly the three; C-4's fail-closed statement made a V-FA-7 item with the witness level NAMED (writer unit only); C-5's CLI pathspec bound to the real `src/cli/main.cpp`; C-6 parallel m-3/m-1 review; C-7 the SCOPE_DIFF rows with 231935 as evidence); identities unchanged; your exact-hash PLAN-REVIEW at e0d5585b requested; the root-mode re-measurement runs on this filing and goes UP

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/PLAN-REVIEW-pair-implementer-20260901-233102.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260901-232655.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260901-231935.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; intg-substep2a/PLAN-pair-planner-20260901-230031.md; intg-substep2a/IMPL-pair-implementer-20260901-063948.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding an exact-hash review and adopting the fence owner's ruling as terms; no sealed byte, no product byte, no ref move; the tranche-2 token waits on your exact-hash approve of THIS digest AND the operator's W-5 disposition (vi) AND the Master Reviewer's concurrence + effectiveness notice; m-1's and m-3's parallel byte reviews, merge, push, and release stay behind their own gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index CLEAN; tranche-1 diff UNSTAGED and UNCOMMITTED (sha256 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf over exactly src/core/manifest/manifest.cpp + tests/test_manifest.cpp — re-verified this turn); NOT a candidate; NO byte moves before the gates below
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 4 — artifact @ sha256 e0d5585b (dead priors: 8f19819e, 57ab3b9b; same identity via engine supersession): F1 explicit `git add` by the six-path Task-3 allowlist after the soft reset + proofs (a) unstaged empty, (b) cached set == allowlist sorted, (c) both tranches in the cached tree by their own discriminators (tranche 1's three added test-case names + ≥5 valid_manifest_path sites; tranche 2's `expected<std::string> serialize` + 6 leg tags), plus the four-commit / retained-tag / status-clean postconditions; F2 `RepoRowFacts` as the validator's ONLY input with writer-derived vs parser-observed facts stated line-by-line, the H/N presence clauses expressed in it, and member-level SHAPE errors explicitly left at the parser's existing sites (they have no typed twin); F3 the grammar with exact commands/results and the `NAMED MUTANT` (FX-N ×9) non-collision proof; C-1..C-7 as global constraint 10 with Task-3 Step 3's exact per-site hunks and Task 4's confinement/diff-bound/fail-closed/CLI items; W-5 named as the standing coverage proposal; exact-hash review to approve/must-revise

## The three findings, verified then folded

```text
F1  VERIFIED: at the retained tree `git diff --cached --name-only` is EMPTY and both tracked
    changes are unstaged; `363d812..9e6ebe8` touches manifest.cpp/.hpp + test_manifest.cpp.
    My rev3 claim that reset --soft leaves "both tranches" in the index was FALSE — it
    would have recreated old Task 3. FOLDED: Step 5 = reset --soft 363d812 → explicit
    `git add -- <six Task-3 paths>` (never -A/.) → proofs (a)(b)(c) retained → ONE commit →
    postconditions (four commits above base; 9e6ebe8 reachable via the local tag; status
    clean; `git diff --name-only 9e6ebe8..HEAD | sort` == the six paths). Step 0 additionally
    preserves tranche 1 as a patch file in an mktemp evidence home (re-hashed 72fd3dc6).
F2  VERIFIED at :1564-1584 (capture_mode optional while parsing), :1687 (value_or(full)),
    :1590-1592 (local_refs_present raw bit), :1616-1620 (raw sparse null check),
    :1695 (entry.sparse = nullptr). FOLDED: `RepoRowFacts{row, capture_mode_present,
    local_refs_present, sparse_present_non_null}`; writer-derived = {!shallow &&
    !payload_only_unborn (manifest.cpp:920's predicate), true, false}; parser-observed = the
    three existing raw observations; `repo_row_violation(const RepoRowFacts&)` is the ONLY
    validator at BOTH points; the inventory lists O-R2/O-R3/G/H-N presence (both
    directions)/N-R2/COND-3; member-level SHAPE errors (type, 40-hex, enum text) stay at the
    parser's existing ParseError sites and are stated to have no writer twin — O-R4's domain
    is the typed row, not malformed text. The landed duplicated checks (:1626 etc.) are
    REPLACED by the shared call, never kept alongside.
F3  VERIFIED: rev3 demanded seven `FX-O (b)` tags and six `FX-O (` tags at once. ALSO
    MEASURED: test_manifest.cpp already carries NINE `NAMED MUTANT` markers (FX-N), so a bare
    "NAMED MUTANT" grep would have counted 17. FOLDED: `// FX-O-LEG (x)` once per logical
    leg → `grep -c 'FX-O-LEG ('` = 6 (uniq -c census shows each once; (c) has no test tag);
    `// FX-O-FIELD n name` → `grep -c 'FX-O-FIELD '` = 7; `// O-MUTANT:` → `grep -c
    'O-MUTANT:'` = 8, + the census marker recorded in Task-4 evidence = O's NINE;
    `grep -c 'NAMED MUTANT'` stays 9 (the non-collision proof). O's six legs and nine
    markers are untouched.
```

## ASK-6 ruled → fence terms (global constraint 10; carried into Task 3 Step 3 and Task 4)

```text
C-1  sites exact (pack.cpp:765 · test_cli.cpp:192 · test_open.cpp:131 at 9e6ebe8; the
     tranche-1 tree does not touch those files); Task-4 whole-tree confinement grep:
       git grep -n 'serialize(' HEAD | grep -v checksums | grep -v 'src/core/manifest/manifest\.[ch]pp' \
         | grep -v test_manifest.cpp | grep -v ':docs/'   == exactly three lines
     MEASURED at 9e6ebe8 this turn: exactly those three. A fourth = V-FA-1 red.
C-2  shapes written per site in Step 3: pack — `auto manifest_json = …; if (!manifest_json)
     { return cleanup_error(manifest_json.error()); }` + `*manifest_json` at :778 (the
     existing lambda at :569; nothing else); test_cli — `auto serialized = …;
     REQUIRE(serialized.has_value()); auto manifest_json = std::move(*serialized);` with the
     .find/.replace/std::move lines UNTOUCHED; test_open — `const auto serialized = …;
     REQUIRE(serialized.has_value()); const auto& manifest_json = *serialized;` with the
     following lines UNTOUCHED. No new kind, no wrapping, no caller-side detail.
C-3  Task 4: per-file `git diff 9e6ebe8..HEAD -- <file>` retained whole; every changed line
     names manifest_json/serialized/has_value/cleanup_error (grep -vc → 0); expected
     numstat ≈ +4/-1, +3/-1, +3/-1.
C-4  Task 4 STATES (a V-FA-7 item): cleanup_error removes partial_path + spool_path before
     std::unexpected — no .bvpk at the destination; NO FX-O leg exercises the pack-level
     path; refusal witnessed at the WRITER UNIT ONLY ((a)(b)(d.i)(d.ii)); no pack-level test
     added — none required.
C-5  CLI untouched: the TEN-path allowlist equality + `git diff --quiet <base>..HEAD --
     src/cli src/cli/main.cpp schemas` rc 0 (the pathspec bound to the path that EXISTS —
     `src/main.cpp` does not; measured); S-FA-4 stays armed (global 8).
C-6  m-3's byte review of the two test hunks in PARALLEL with m-1's V-FA review on the same
     candidate sha; both through master before the packet (master's call, adopted).
C-7  the token's SCOPE_DIFF: ten paths `-> in`; the three propagation rows each carry
     231935 as SCOPE_ROW_EVIDENCE.
```

## Coverage and gates (the plan's Identity section carries the same words)

W-4's 2a lineage terminated at 230031 (step iii). W-5 is PROPOSED at master (one lineage, three eligible rows M rev8/N/O, identities frozen as `intg-substep2a-plan` / `intg-format-act-plan` — both UNCHANGED here), scan complete, awaiting the operator's disposition (vi) and then the Master Reviewer's concurrence + effectiveness notice. W-5's replacement rule is W-4's: this revision re-measures root-mode on filing and reports the fired set UP verbatim (the O design-lineage red on this carrier is the expected entry). The token issues only when: your exact-hash approve at `e0d5585b…` + the operator's (vi) + the Master Reviewer's concurrence all stand.

## Your review

Exact-hash delta review at `e0d5585b77b52e464be97e4e03685c0509ee170660bdfccc3a7f6ee12f42baa4`: F1's Step-5 sequence and proofs against your own index/worktree evidence; F2's `RepoRowFacts` contract against :1564/:1590/:1616/:1687; F3's counts against O's FX-O text and the file's existing marker population; C-1..C-7 against `231935` verbatim. Tranche 1 stays as you left it — no edit under this relay.

ACTIONS_GIT_REF: docs-lane writes only — the rev4 artifact (e0d5585b) and this relay via the engine; the re-measurement archive and the SITREP to master follow this filing; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION4-F1F2F3-C1C7.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
