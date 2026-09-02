## PLAN (isolation plan REVISION 1 — your `035526` MUST-REVISE at 46e47a0a folded, all four findings verified at my own read of the bytes before folding: F1 (Critical) CONFIRMED — `scenario.py:290-291`/`:316-317` re-cover `CLAUDE_CONFIG_DIR`/`CODEX_HOME` for a named agent, so an overlay-drop mutant never exposed poison; the mutants now act on the FINAL per-command env through a `scenario._run_json` wrapper that removes exactly ONE locator from `env_overrides` after the profile merge and `_probe_open_env` (pack AND open; the runtime guard stays ACTIVE — one coordinate per arm); F2 (Critical) CONFIRMED — `claude_code.cpp:573-582` returns from an existing `CLAUDE_CONFIG_DIR` without consulting HOME, and the product publishes no database bytes; L1 is now a precedence-FAITHFUL model transcribed cell-by-cell with the product lines cited (`_discover_model`), identity by PATH not content, its one unmodelled cell (the config.toml `sqlite_home` fallback — unreachable while the variable is always set) stated, the HOME-arm reading stated (the `$HOME/.claude` canary is unreachable under any ONE-coordinate mutant because `CLAUDE_CONFIG_DIR` always names an existing directory; the HOME mutant REDs on the codex `$HOME/.codex` canary and asserts the claude one's ABSENCE), and the whole model ROUTED UP for m-3's exact pre-token ruling with option B (a real-product witness) framed and the fence reason it is not chosen; the false claim that iso·3's census catches behavioural drift is WITHDRAWN; F3 (Important) CONFIRMED — the `timeout` token grep contradicted iso·4's constant-naming guard; replaced by three byte-level proofs (e3.py whole-file equal; `COMMAND_TIMEOUT_S` line-and-value equal at line 24, new constants placed BELOW it; zero changed lines of the two production-side harness files carrying the token); F4 (Important) CONFIRMED — the mutant tests asserted the leak, not the oracle's failure; now ONE factored positive oracle `_assert_hermetic_discovery` is executed under each mutation inside `pytest.raises(AssertionError)` with `_leak_tags == {<LOCATOR>}` — RED on exactly its own canary; iso·2 rides the same oracle; seven markers unchanged (4/1/1/1); the token now waits on your exact-hash approve AND m-3's L1 ruling; your exact-hash review at c8bd21f0 requested)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-033604.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-master-reviewer-20260901-155517.md; ../../pdc/master/relays/r437-operator-scope-ruling/PLAN-operator-20260902-031727.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260901-142647.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260901-142445.md; ../../pdc/master/relays/publication-path-ruling/PLAN-master-planner-20260902-141707.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision folding an in-lane must-revise; the operator's scope ruling and the Master Reviewer's exact-pin approval stand; this relay mints no token (the pair's gate mints in-lane only after your exact-hash approve AND m-3's addressed pre-token ruling on the L1 model, carried through master); m-3's byte review is the acceptance gate at the landed sha; no push, no PR, no publication, no release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: b706e745c1890ce43c117a756103c415b4d0c29a
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
DESIGN_SHA256: 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 290db9a47b8624170a996cb30f2ac73493280db3baef631708131a8be0b0c8dc
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: 62a261819ca66ed93be174ecef3c0ce10441f085
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed
BASE: main@56fe0fb (docs-lane HEAD at filing; harness, src/adapters, src/cli/main.cpp byte-identical to the design's product pin 46df8f3 — re-verified `git diff --quiet 46df8f3..HEAD -- harness src/adapters src/cli/main.cpp` rc 0); the ONE commit lands on local main under the token, no branch; lane-local under R-4.51 (the trunk is unpublished)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN revision 1 — E2 store-isolation plan @ sha256 c8bd21f0 (dead prior 46e47a0a; same identity intg-isolation-plan; same declared cross-repo design edge b706e745 / 290db9a4): F1 mutants act on the FINAL per-command env via a _run_json wrapper, guard active; F2 L1 = a precedence-faithful model (product lines cited; path identity; unmodelled cell + HOME-arm reading stated) routed UP for m-3's pre-token ruling, option B framed; F3 three byte-level budget proofs replace the impossible token grep; F4 one factored positive oracle turned RED under each mutant with an exact leak-tag set; token waits on your approve AND m-3's ruling; exact-hash review to approve/must-revise

## The four folds, at the bytes

```text
F1  scenario.py:290-291 (claude) and :316-317 (codex) write CLAUDE_CONFIG_DIR / CODEX_HOME into the profile env
    for a NAMED agent; {**overlay, **profile_env} restores them after any overlay drop → your finding holds.
    FOLD: _restore_poison(monkeypatch, LOCATOR) wraps scenario._run_json and pops exactly that key from the
    FINAL env_overrides (after the merge and _probe_open_env), so os.environ's poison survives for it on pack
    AND open. The runtime guard runs on the un-mutated env and stays ACTIVE — no test disables it.
F2  claude_code.cpp:573-582 returns from an existing CLAUDE_CONFIG_DIR (HOME never consulted); :585-594 the
    $HOME/.claude default otherwise. codex.cpp:1195-1199 CODEX_HOME if it exists; :1202-1206 $HOME/.codex
    APPENDED when it exists and is not lexically the same root; :1158-1170 CODEX_SQLITE_HOME is a DIRECTORY
    locator; collect :1226-1236 reads <locator>/state_5.sqlite else <root>/state_5.sqlite — no bytes published.
    FOLD: L1 = _discover_model(env), the precedence above transcribed with each product line cited; rows are
    (locator-tag, absolute path); NO content echoed. Unmodelled cell STATED: the config.toml sqlite_home
    fallback (:1160-1162) — unreachable under the overlay (scratch) and every mutant (poison): the variable is
    always SET. HOME-arm reading STATED: CLAUDE_CONFIG_DIR always names an existing directory (staged store, or
    the overlay's scratch which _hermetic_overlay creates), so the $HOME/.claude canary needs TWO coordinates;
    the HOME mutant REDs on the codex $HOME/.codex canary and asserts the claude one's ABSENCE.
    ROUTED UP (the SITREP filed with this revision) for m-3's exact pre-token ruling; option B framed: a
    real-product witness needs the built biv in the selftest process (a CMakeLists byte — a gate byte under
    ISO-R4) or a runner-side invariant on the real E2 suite that witnesses only against REAL ambient stores
    (host-dependent — what ISO-R2 excludes as the oracle). WITHDRAWN: "iso·3's census catches model drift".
F3  iso·4's guard names scenario.COMMAND_TIMEOUT_S / e3.COMMAND_TIMEOUT_S, so any 'timeout' grep over the diff
    fires on the test itself → your finding holds.
    FOLD: (i) git diff --quiet <base>..HEAD -- harness/bivharness/e3.py rc 0; (ii) grep -n '^COMMAND_TIMEOUT_S = '
    byte-equal between <base> and HEAD (24:COMMAND_TIMEOUT_S = 30; the new constants go BELOW it); (iii) the
    changed lines of scenario.py + stub_biv.py carry zero 'timeout' tokens. The selftest file is exempt from (iii).
F4  the rev0 mutants REQUIRED poison to appear — green when leaking → your finding holds.
    FOLD: _assert_hermetic_discovery(entries, poison_root, work) is the ONE positive oracle (no logged path
    under the poison root; every TMPDIR line under <work>/hermetic/tmp); the positive test runs it and it PASSES
    (with the two staged transcripts present under their tags — not vacuous); each of the FIVE mutants
    (HOME, CODEX_HOME, CODEX_SQLITE_HOME, CLAUDE_CONFIG_DIR, TMPDIR) runs the SAME oracle inside
    pytest.raises(AssertionError) and asserts _leak_tags == {LOCATOR} — RED on exactly its own canary.
    Markers unchanged: 7 (iso·1 four, iso·2 one, iso·3 one, iso·4 one).
also the sequencing line now states 2a's actual state and R-4.51's lane-local landing.
```

## Your review

Exact-hash review at `c8bd21f05c59de5285618367872399220bbc9d0ed4343578db3ff7cb912c05ed`: the `_restore_poison` mechanics against `scenario.py:134-142` and the two command sites; the L1 model against `claude_code.cpp:573-594` and `codex.cpp:1156-1247` at the pin (every cell; the unmodelled cell; the HOME-arm reading); the three budget proofs; the oracle/mutant coupling and the exact leak-tag sets. No edit under this relay. The token issues only after your approve AND m-3's addressed ruling on L1; if m-3 rules for option B, this plan STOPs and a further revision consumes the answer.

ACTIONS_GIT_REF: docs-lane writes only — the rev1 artifact (c8bd21f0) and this relay via the engine; the root-mode measurement and the SITREP UP follow this filing; no harness byte, no product byte, no ref move; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file); the root-mode measurement (the instrument of record for the declared cross-repo edge) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION1-FOUR-FOLDS.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
