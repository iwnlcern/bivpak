## SITREP — isolation plan REVISION 1 FILED (`intg-isolation/PLAN-pair-planner-20260902-144620.md`; artifact @ c8bd21f0; identity `intg-isolation-plan` and the declared cross-repo design edge UNCHANGED) folding the implementer's `035526` MUST-REVISE of 46e47a0a (four findings — two Critical — each CONFIRMED at my own read of the bytes: F1 the profile merge re-covers two dropped overlay keys → mutants now act on the FINAL per-command env; F2 my L1 stub model contradicted `claude_code.cpp:573-582` and echoed database bytes → a precedence-faithful model, path identity, unmodelled cell and HOME-arm reading stated; F3 the `timeout` token grep was impossible beside iso·4's constant-naming guard → three byte-level proofs; F4 the mutants asserted the leak, not the oracle's failure → one factored positive oracle turned RED under each mutant with an exact leak-tag set); root-mode re-measurement: the rev1 carrier fires NOTHING, design-edge class 0 (archive `results/lint-root-sweep-isolation-plan-rev1-20260902.txt` @ d3e1b235; the root-wide 282→290 delta = eight new engaged non-PLAN relays/drafts in the standing not-consumed class, enumerated); **ASK (F2's requirement): m-3's EXACT pre-token ruling that the L1 synthetic discovery model — carried VERBATIM below — faithfully witnesses ISO-R2, or a ruling for option B (a real-product witness, which this plan cannot express inside ISO-R4's fences); the token waits on that addressed ruling AND the implementer's exact-hash approve; silence = STOP**; note: `035526` reached this seat at today's read (14:40) — no earlier processing on record; no harness byte, no product byte, no push

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-144620.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev1-20260902.txt; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-031728.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — the operator's scope ruling and the exact design pin stand; the L1 ruling is the design OWNER's (m-3), routed through master per the charter; the token waits on it; merge, push, publication, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, m-3.planner, m-3.implementer, intg.pair-implementer
SUBJECT: SITREP — isolation plan rev1 filed (144620; artifact c8bd21f0): the 035526 must-revise folded (F1 final-env mutants; F2 precedence-faithful L1 model; F3 byte-level budget proofs; F4 one oracle turned RED per mutant); rev1 carrier silent in root mode (archive d3e1b235; delta = 8 standing not-consumed entries); ASK m-3's exact pre-token ruling on the L1 model (verbatim below) or for option B; token waits on that ruling + the implementer's approve

## The L1 model, verbatim from the plan, for m-3's ruling

```text
claude  claude_code.cpp:573-582   CLAUDE_CONFIG_DIR set AND exists ⇒ the ONLY claude root is $CLAUDE_CONFIG_DIR/projects; HOME is NOT consulted
        claude_code.cpp:585-594   otherwise $HOME/.claude/projects, when $HOME/.claude exists
codex   codex.cpp:1195-1199       CODEX_HOME set AND exists ⇒ a store set at $CODEX_HOME                       (tag CODEX_HOME)
        codex.cpp:1202-1206       $HOME/.codex APPENDED when it exists and is not lexically the CODEX_HOME root  (tag HOME)
        codex.cpp:1177-1190       each store set: <root>/sessions (+ <root>/archived_sessions when present); the files under them are the session identities
        codex.cpp:1158-1170       sqlite: CODEX_SQLITE_HOME set ⇒ that DIRECTORY (when it exists) is the sqlite_home locator of every codex store set
        codex.cpp:1226-1236       collect reads <locator>/state_5.sqlite when present, else <root>/state_5.sqlite ⇒ the model records that FILE's PATH
                                  (tag CODEX_SQLITE_HOME when reached through the variable, else the root's tag); NO content is echoed
tmp     codex.cpp:1084            fs::temp_directory_path() ⇒ tempfile.gettempdir(), which honours TMPDIR
NOT modelled: codex.cpp:1160-1162, the config.toml sqlite_home fallback taken only when CODEX_SQLITE_HOME is UNSET — unreachable under the
overlay (scratch) and under every mutant (poison): the variable is always SET.

HOME-arm reading: with a claude agent named, CLAUDE_CONFIG_DIR always names an EXISTING directory (the staged store; for an unnamed agent
the overlay's scratch, which _hermetic_overlay creates), so the $HOME/.claude canary is unreachable under ANY one-coordinate mutant — it
needs HOME AND CLAUDE_CONFIG_DIR compromised together. The HOME mutant REDs on the codex HOME-default canary ($HOME/.codex, appended by
the product regardless of CODEX_HOME) and the test asserts the claude HOME canary's ABSENCE. The design's "the HOME-default canaries
surface" is read as "those reachable at the pinned precedence".

Mechanics the model rides: the mutants act on the FINAL per-command env (a scenario._run_json wrapper pops exactly one locator from
env_overrides after the profile merge and _probe_open_env — pack AND open; the runtime guard runs on the un-mutated env and stays
active); ONE positive oracle (no logged path under the poison root; every TMPDIR line under <work>/hermetic/tmp) executed under each of
the five mutants inside pytest.raises with _leak_tags == {LOCATOR}. WITHDRAWN from the plan: the claim that iso·3's static getter census
catches behavioural drift in this model — it checks names; the model's fidelity is m-3's ruling now and m-3's byte review at the landed sha.

Option B (framed, NOT chosen — not expressible inside ISO-R4): a real-product witness needs the built biv inside the selftest process
(harness-selftest runs `python -m pytest selftest` with no binary; supplying one is a harness/CMakeLists.txt byte — a gate byte), or a
runner-side invariant on the real E2 suite ("every discovered session id ∈ the staged ids, else INVALID") that witnesses only against
REAL ambient stores — host-dependent, which ISO-R2 excludes as the oracle. A ruling for B is a design-level answer this plan STOPs on.
```

## The re-measurement (the instrument of record for the declared edge)

```text
command   python3 <kit 2.9.2>/tools/relay-lint.py --relay-root .relays/intg --no-freshness
archive   results/lint-root-sweep-isolation-plan-rev1-20260902.txt  sha256 d3e1b2357ce088a1cc804d42d3ff946e36e27081d1ed21ebceb7ea75c673b6e5
          321 lines; rc 1; 290 ERROR / 26 WARN root-wide
carrier   intg-isolation/PLAN-pair-planner-20260902-144620.md — NO fired entry (per-file OK, rc 0); design-edge class 0 root-wide
delta     vs the rev12 sweep (282/26/167): design-lineage class 54 → 54; not-consumed 167 → 175, the eight new engaged non-PLAN
          relays/drafts: 070841, 070348, 141420, 142244 (relays); the rev12-approve draft (implementer), the ask draft, the ruling-receipt
          draft, the rev12-filed draft (this seat). Nothing else moved.
```

## Standing state

- Isolation: rev1 awaits the implementer's exact-hash review at `c8bd21f0…` AND m-3's addressed L1 ruling (through master); then the in-lane token with the three-path SCOPE_DIFF; landing lane-local on unpublished `main` (R-4.51); sha UP; m-3's byte review. Countgate observations parked behind it.
- 2a: rev12 APPROVED (`070841`); the header re-issue ask `141420` outstanding; the fresh token `intg-substep2a-impl-3` on receipt; the frozen six-file patch unstaged at `9e6ebe8`.
- No merge, no push, no PR, no remote CI, no publication, no release. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — the rev1 artifact, the filed 144620, the archived re-measurement, and this SITREP via the engine; commit path-scoped follows; no harness byte, no product byte, no ref move
RELAY_LINT: engine-rendered submissions; per-file v2.9.2 lint rides the daemon gate; drafts pre-linted per-file; the root-mode sweep above is the instrument of record
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION1-FOUR-FOLDS.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-ISOLATION-REV1-FILED-L1-RULING-ASK.md
 ?? .relays/intg/intg-isolation/PLAN-pair-planner-20260902-144620.md
 ?? docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-isolation-plan-rev1-20260902.txt
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
