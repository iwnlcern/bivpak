## AUDIT — sub-step 1 (A6 rev14 consent-UX fabric, engine unwired): STILL-OPEN whole; the engine half is ALREADY-CLOSED on main and is consumed, never rebuilt; one live upstream dependency (A7 unsealed) bounds the build order

ROLE: Pair Planner
PHASE: AUDIT
AUTHORITY: read-only
DISPATCH_ID: intg-substep1-audit
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-commission-grant/PLAN-master-planner-20260827-144459.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-commission-charter/DESIGN-master-planner-20260827-144023.md; ../../pdc/master/relays/bivpak-repo-integration-phase-operator-gate/PLAN-orchestrator-planner-20260826-200932.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no — read-only audit inside the chartered commission; every build/merge/publication/release gate stands ahead; the release hold is ABSOLUTE
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: design-doc
CONSUMED_CONTRACT: m3-addendum-6-c41d015f-lock-20260825 (locked c41d015fd867464aefc479e25f0fc7521b5e259cb88d79cb1d36fe05db19150c; post-stamp 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771 — live file re-hashed EQUAL this turn; pre-stamp blob re-derived EQUAL at commit a633981)
SECOND_CONSUMED_CONTRACT: m1-addendum-M-2966b839-lock-20260825 (post-stamp 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082 — re-hashed EQUAL this turn)
THIRD_CONSUMED_CONTRACT: m1-addendum-N-82293732-lock-20260827 (post-stamp 3ba71be1c3cbd252494faa96fe770a0977277ac25a6084e5da32534194447c61 — re-hashed EQUAL this turn)
FOURTH_CONSUMED_CONTRACT: m4-sr-url-family-20260823 rev2 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798 — re-hashed EQUAL this turn)
PRODUCT_PIN: main@02b51435a5b50363df7f595dd827af107424b0c3 (contains lane-local merge 3d5cc6da, parents 6ca4d35 + 6f89818; corrective pin 6ba01ef verified ancestor of main; origin/main untouched per R-4.43's closed row)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner
SUBJECT: AUDIT — sub-step-1 4-bucket verdict: fabric STILL-OPEN (zero A6 bytes at main@02b51435), engine ALREADY-CLOSED (src/core/repo landed, zero production callers — consume via hook, never rebuild), no overlap; recommended-next = your independent audit, reconcile, then PLAN bounded to the 200932 spine's sub-step-1 leg set with A7-governed S5-S7 surfaces sequenced behind A7's seal (A7 = rev2 pair-approved 042911, routed up 043104, NOT yet VP-verified/sealed at this read)

## 4-bucket verdict

```text
PRIMARY_BUCKET: still-open
still-open: the ENTIRE A6 rev14 consumer fabric. At main@02b51435: zero occurrences of
  `--accept-url-divergence`, `UrlDivergenceRefused`, `UrlDivergenceEntryRefused`, or
  `url-divergence-accepted` anywhere outside src/core/repo/ (the PascalCase engine-internal
  hook/memo types inside src/core/repo are LOCKED M-R3 execution, not A6 bytes — m-3's own
  023238 classification, re-applied here). The envelope schema's advisories oneOf carries
  TWO branches (prune-summary, nested-bivignore-ignored — schemas/biv-json-envelope.v1.schema.json:35,56),
  not the third A6-R1 member; error.facts declares no requested/effective/op; the open
  result declares no url_divergence_refusals; help_text (src/cli/args.cpp:130-147) carries
  no flag line; no PROMPT D renderer exists.
already-closed: the ENGINE half. src/core/repo/ is on main (lane-local merge 3d5cc6da;
  veto-7 successor 6f89818 included) with the M-R3 hook seam, run-scoped memo, absent-hook
  fail-safe refusal, and the veto-7 comparator. Zero production callers: run_eligibility /
  restore_entry are referenced only within src/core/repo/ itself plus tests/test_repo_engine.cpp
  (grep this turn — matches the A6 rev14 census, now ALSO true of main, which has moved
  since A6's pinned observation of absence at 8b97d38). DO NOT REBUILD; sub-step 1 consumes
  the hook seam and wires nothing. Also pre-existing and preserved: `--agent-bin`
  (args.cpp:214, byte-goldened at test_cli.cpp:1425-1440) and the PROMPT A/B/C machinery
  (A6-R6: untouched).
product-overlapped: none. A6-R6 enumerates every adjacent surface as deliberately not
  moving; no narrowing or rerouting is indicated.
recommended-next: pair-implementer independent audit -> reconcile -> pair-Planner PLAN for
  sub-step 1 bounded to the 200932 spine's binding set (the static fabric; legs
  a6·14/15/17/18 + the zero-state half of a6·16 bind at landing; behavioral legs a6·1-13 +
  the divergence half of a6·16 arm at sub-step 2b), with the A7-governed S5-S7 surfaces
  (hook-install TTY predicate, --json posture, PROMPT D flow ordering — the hook
  implementation tranche) sequenced BEHIND A7's seal.
```

## Duplicate/already-built gate

Run whole at main@02b51435 this turn (E1, grep + file reads): no feature flag, dead path,
alternate UI/API, or existing test covers any A6-R1..R9 surface. The one adjacent landing —
the engine — is the consumed contract, not a duplicate. Nothing to promote/enable in place
of building the fabric.

## The A6 census re-verified live at the product pin (the sealing-SHA discipline)

Every A6-cited CLI anchor re-checked at main@02b51435 and found STANDING, byte-stable at the
cited lines: the raw-argv `--json` normalization (args.cpp:151-158); the exclusive
`open --help` residual production (args.cpp:186-188, tokens.size()==2U); the list/info stub
parsers returning without examining trailing tokens (args.cpp:267-273) and their
NotYetImplemented path (main.cpp:396-400); exit_for_sessions as the sole successful-open
exit source (main.cpp:363); the PROMPT B [y/N] convention (src/core/open/render.cpp:280);
ErrKind (src/core/support/error.hpp:9) + exit_for_error (src/core/report/envelope.cpp:394);
selftest blob-pin recompute (harness/selftest/test_envelope.py). The A6 rev14 census
transfers to today's HEAD without correction.

## Upstream authority state (verified at the pdc bytes this turn)

```text
chain      T1 142730 (operator "authorized") -> charter rev1 144023 @ 82d02a57 (re-hashed
           EQUAL) -> stage-(c) approve 144253 (TARGET_DESIGN_SHA256 equal) -> grant 144459
           (TO == COMMISSION_TO == intg.pair-planner); four identity fields byte-equal
R-4.43     CLOSED 2026-08-26 at master's pen on m-4's 171713 sign-off; VP package verdict
           APPROVE 150851; both locks JOINTLY AUTHORITATIVE; the bundle-join insufficiency
           on A6's lock face is DISCHARGED; release-gating clause SURVIVES the close (first
           release checklist must name the row)
A7         m3-addendum-7 (consent-interaction companion, S5-S7) is NOT SEALED: rev2
           pair-gate complete (implementer approve 042911), routed up 043104 for renewed VP
           verification; live file Status reads "rev2 — UNDER REVIEW", sha256 4c40fe37…,
           no lock stamp. The 200932 spine requires it SEALED before the build reaches the
           surfaces it governs. The charter's WHERE_THE_RULES_LIVE predates/omits it.
m-4 gate   the reachability re-review gate before any verb-to-engine wiring STANDS (the
           171713 sign-off re-verified unreachability at 6f89818 with wiring triggers
           standing); nothing in sub-step 1 approaches it.
```

## Boundary contract (sub-step 1, for the coming PLAN)

```text
Writes: CLI fabric bytes only — src/cli/ (flag parsing, help line, PROMPT D renderer +
        golden texts), src/core/report/ + src/core/support/error.hpp (two ErrKinds, exit
        rows, envelope carriers), schemas/biv-json-envelope.v1.schema.json (three A6-R1
        emission sites), tests/test_envelope.cpp (parity rows), tests/test_cli.cpp (help
        golden), harness/selftest pins — on branch intg/consent-fabric; engine bytes ZERO.
Reads: LOCKED A6 rev14 (hook contract consumer); LOCKED M rev8 (M-R3 hook inputs/semantics,
       read-only); A7 once sealed (S5-S7 predicates).
Target entity: the biv CLI consent-UX surface + the biv-json-envelope.v1 contract.
Downstream consumer: the sub-step-2b wiring act (installs/executes the hook), m-3's byte
       review at every landing, FX-A6 legs at their spine-assigned due points.
Contract: A6-R1 taxonomy CLOSED at two ErrKinds + one advisories member; V-A6-3 one-commit
       rule binds commit topology (any ErrKind lands with all three schema sites + parity
       rows + recomputed selftest pins in the SAME commit).
Proof: at sub-step-1 landing — legs a6·14, a6·15, a6·17, a6·18 + a6·16's zero-state half
       (E2); the behavioral remainder E2-binds at 2b per the sealed deferral.
No-consumer action: not applicable — the spine orders consumer-surface-first by design.
```

## Design recommendation

No pair design act exists or is permitted: the design of record is the SEALED A6 rev14
(plus A7 once sealed) under cardinal rule 1 — where sealed text determines, execute; where
it defers or is silent, STOP and route UP. The coming PLAN consumes
`m3-addendum-6-c41d015f-lock-20260825` as its DESIGN_LOCK_ID; the design-review lineage the
lint gate wants lives in the pdc master tree (m-3.implementer approve `100126` at the exact
pin) — the PLAN will declare the cross-root design edge (DESIGN_SOURCE_* seven-field form)
or, if the foreign-tree authority-reconstruction cannot see the m-3 pair-gate shape, route
UP for a master/operator direct-override rather than bending the declaration.

## Risks / reject-or-narrow gates

1. A7 UNSEALED is the one live dependency: building the hook-implementation tranche
   (install predicate, prompt timing, --json posture) before its seal violates the spine's
   ordering. Narrow the first PLAN tranche to A6-determined bytes if A7 is still unsealed
   at PLAN time, or hold the PLAN until the seal is carried down.
2. V-A6-2 byte-golden fence: every template byte comes from the sealed doc verbatim;
   any wording need is a STOP to m-3 via master (A6-R7(1)), never a local cut.
3. V-A6-3 one-commit shape constrains implementation sequencing inside the branch.
4. Charter docs lane: only docs/sprints/** + .relays/** commits land outside the merge
   bar; every product byte rides the branch behind the four-condition bar + owner
   predicate + operator merge token.
5. The spine recommended two pairs; the operator's T1 commissioned ONE — recorded, no
   action (the operator's word governs).

## Questions for Implementer/operator

1. To the pair-implementer: run your independent audit at the same pins; specifically
   re-verify my still-open sweep (encoded spellings included — decode-level match, not
   byte-literal only) and the zero-production-caller claim on the live call graph.
2. Routed UP (SITREP alongside this audit): A7 seal status + whether the pair consumes it
   as a spec of record; branch-base confirmation (local main@02b51435); bridge transport
   (no intg seat exists in the master engine root — hand-carry assumed).

ACTIONS_GIT_REF: no product edits; boot substrate writes this turn only — .relays/intg/ (engine-created projections + this draft) and docs/sprints/2026-08-27-intg-consent-fabric/{ROADMAP,RECONCILE,DEVIATIONS}.md; product tree clean at main@02b51435 (git status over src/ schemas/ tests/ harness/ = empty)
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate
FINAL_GIT_STATUS_SHORT:
 ?? .relays/intg/
 ?? docs/sprints/2026-08-27-intg-consent-fabric/
Literal path-scoped status for this seat's own writes at audit close; the shared bivpak tree additionally carries pre-existing s4-authored state (modified .relays/s4/INDEX.md, SEATS.md and untracked s4 relay files) not claimed clean here.
