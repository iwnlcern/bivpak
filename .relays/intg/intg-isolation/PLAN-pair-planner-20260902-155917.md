## PLAN (isolation plan REVISION 2 — consumes design rev4 `5c81e86a` @ pdc `e19e61fb` (owner-approved `153855`; rev2 `290db9a4` and rev3 `59d5ec91` DEAD PINS), carried by master `154650` with m-3's L1 ruling `151302`: (A) my selftest model is FAITHFUL and ACCEPTED as the SELFTEST GRAIN (HOME-arm reading CONFIRMED), AND a REAL-PRODUCT GRAIN is REQUIRED — my rev1 "option B is inexpressible" ANSWERED (it conflated the real product with real ambient stores; over a POISONED inherited env the witness is deterministic and gate-byte-free because harness-e2 already consumes the built biv); THE FOLD (L3, this plan's HOW for the design's WHAT): ONE shared poison builder `_poison_roots(root, source)` with VALID workspace-scoped canary transcripts (the product packs only cwd-in-source sessions with grammar-valid ids — a canary it would skip could never leak; deterministic hex UUIDs unique per root) and a deterministic INVALID `state_5.sqlite`; the ONE new spec `harness/scenarios/store-isolation-witness.json` (`"isolation_witness": true`; V-ISO-4 reading: isolation STAGING) — `run_scenario` builds the poison at `<scratch>/<id>.poison` and runs the body (extracted verbatim into `_execute_scenario`) inside `_inherited_environment(poison_env)`, so `_run_json`'s untouched `os.environ.copy()` base IS the poisoned inherited env; THE RP ORACLE `_isolation_leaks` reads ONLY product-owned evidence — both envelopes' `warnings[].kind/.path`, the open envelope's `store_root`/`image_session_id`/`installed_session_id` — a hit is a FINDING (FAIL, never INVALID) tagged by the poison root reached; the `session_rows` pin the STAGED ids so the positive is not vacuous; the four restore-to-poison mutants are DEMONSTRATED against the built binary by an out-of-tree driver (`$EVID/rp_mutants.py`: pop ONE locator from the FINAL overrides after the guard; expected FAIL with exactly its own `isolation-leak <TAG>`; `CODEX_SQLITE_HOME` through `CodexDbEnrichmentSkipped:<poison path>` — MUST-RP-1) and RECORDED in the IMPL report, never shipped; NO knob in production harness code (R-CLASS.3, grep-fenced); the write set grows to FOUR paths; markers unchanged 7 (4/1/1/1); the canonical edge re-pointed to `DESIGN_SOURCE_COMMIT 2e52fadf` (the pdc commit filing `153855`, derived at git) with `DESIGN_SHA256 5c81e86a`; the TOKEN now waits on the Master Reviewer's approve of `5c81e86a` (routed by master `154649`) AND your exact-hash approve at 6133d6b2; the L1 selftest grain stays as filed at rev1 with its poison fixture now calling the shared builder)

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-isolation-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154650.md
RELATED_CONTEXT: intg-isolation/PLAN-pair-planner-20260902-144620.md; intg-isolation/PLAN-REVIEW-pair-implementer-20260902-035526.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260902-151302.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-152021.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-planner-20260902-152548.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/DESIGN-REVIEW-implementer-20260902-153855.md; ../../pdc/master/relays/r437-pack-timeout-diagnosis/PLAN-master-planner-20260902-154649.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan revision consuming the owner-approved rev4 pin carried down by master; this relay mints no token (the pair's gate mints in-lane only after your exact-hash approve AND the Master Reviewer's approve of 5c81e86a carried as an addressed relay); m-3's byte review is the acceptance gate at the landed sha; landing lane-local on unpublished main (R-4.51); no push, no PR, no publication, no release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: m3-e2-store-isolation-20260901
DESIGN_OWNER: m-3
DESIGN_SOURCE_REPO: ../pdc
DESIGN_SOURCE_COMMIT: 2e52fadf90be026dafc28276889c8cacb2583518
DESIGN_SOURCE_ROOT: master/relays
DESIGN_SOURCE_PATH: master/domains/m-3-restore-cli/design/2026-09-01-e2-store-isolation-r437.md
DESIGN_SHA256: 5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e
DESIGN_LOCK_ID: m3-e2-store-isolation-20260901 @ sha256 5c81e86a395286995286eb097c5ed155f33b9115e89c75ed9edd1bfa0037527e
DESIGN_RECORD_KIND: design-doc
TARGET_DESIGN_COMMIT: e19e61fb6c9f6c8ee483e9d00f4bf5161dd34c5b
PLAN_LOCK_ID: intg-isolation-plan-20260902 @ sha256 6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94
BASE: main@292a448 (harness, src/adapters, src/cli/main.cpp, src/core/report/envelope.cpp, src/core/pack/pack.cpp byte-identical to the design's product pin 46df8f3 — re-verified rc 0); the ONE commit lands on local main under the token, no branch; lane-local under R-4.51
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN revision 2 — E2 store-isolation plan @ sha256 6133d6b2 (dead priors 46e47a0a, c8bd21f0; same identity intg-isolation-plan): consumes design rev4 5c81e86a @ e19e61fb (edge re-pointed to 2e52fadf, the commit filing the owner's approve 153855); iso·1 at TWO grains — L1 selftest model (ruled faithful, as filed) + the RP real-product grain (L3: one isolation-witness E2 spec under a poisoned inherited env; product-owned oracle over warnings/store_root/session ids; invalid sqlite → CodexDbEnrichmentSkipped; four real-binary demonstrations recorded not shipped; no knob); write set FOUR paths; token waits on your approve + the Master Reviewer's approve of rev4; exact-hash review to approve/must-revise

## What changed rev1 → rev2 (design rev2 → rev4 consumed)

```text
pin        290db9a4 @ 62a26181 (dead)  →  5c81e86a @ e19e61fb (rev4; owner-approved 153855; live == e19e61fb == 2e52fadf blob)
edge       DESIGN_SOURCE_COMMIT b706e745 → 2e52fadf (git log -1 -- DESIGN-REVIEW-implementer-20260902-153855.md); population at
           that commit: origin = m-3.planner DESIGN 152548 (rev4), review = m-3.implementer DESIGN-REVIEW 153855 approve
L1         RULED (151302): faithful; the selftest grain; HOME-arm reading confirmed; config.toml fallback correctly out of model.
           Unchanged as filed at rev1 except the poison fixture now calls the shared builder (UUID-named canaries).
L3 (NEW)   _poison_roots(root, source): home/.codex + home/.claude + codex-home + codex-sqlite (INVALID state_5.sqlite) +
           claude-config + tmp; canaries = VALID two-line transcripts with cwd = source and ids 0d15ea5e-000{1,2,3,4}-…
           (codex packs only cwd-in-source rollouts, codex.cpp:1278-1285; claude likewise, claude_code.cpp:666-669; ids must pass
           agent_member.hpp:17 or pack REFUSES, pack.cpp:631-639). "isolation_witness": true on the ONE new spec →
           run_scenario builds the poison at <scratch>/<id>.poison and runs _execute_scenario (the body, extracted verbatim)
           inside _inherited_environment(poison_env). _isolation_leaks([pack_envelope, open_envelope], poison_root) →
           FINDINGS "isolation-leak <TAG>: <field>=<value>" over warnings[].kind/.path (both envelopes; envelope.cpp:16-35,
           pack.cpp:628-629 via adapter_warning :334-341) and agents[].store_root / image_session_id / installed_session_id
           (open; envelope.cpp:321-333). The pack envelope carries counts only — no identities — so the identities come from
           open; CODEX_SQLITE_HOME is seen ONLY through the warning (codex.cpp:1240-1246; published when a session exists for the
           store root, :1394-1400 — the staged codex transcript provides it): MUST-RP-1 honoured.
demos      $EVID/rp_mutants.py (out of tree): wraps scenario._run_json to pop ONE locator from the FINAL overrides (after the
           guard), runs the RP spec against the built biv per locator; expected FAIL with leak tags == {LOCATOR}; transcripts
           into the IMPL report. grep fence: no 'BIVHARNESS_ISOLATION' / 'MUTANT' token in scenario.py (R-CLASS.3).
write set  FOUR paths: + harness/scenarios/store-isolation-witness.json (17 → 18 specs; no existing spec edited — grep-proved).
budgets    the (iii) changed-line proof now spans the three production-side files (scenario.py, stub_biv.py, the spec).
gate       token = your exact-hash approve at 6133d6b2 AND the Master Reviewer's approve of rev4 (master 154649), carried down.
unchanged  L2; the overlay/guard; iso·2/3/4; the seven markers (4/1/1/1); ONE commit; both platforms; no budget byte; no push.
```

## Your review

Exact-hash review at `6133d6b2042300397dd9c5a81d344898057813b2a68bf1e178a6f2a0c2617d94`: the RP mechanics against the product bytes cited (does every one of the four coordinates surface in product-owned evidence under its mutant — in particular `CODEX_SQLITE_HOME` via `warnings[]` given `codex.cpp:1394-1400`'s same-store-root condition; does the HOME mutant surface the codex canary and NOT the claude one); the poison transcripts' validity (`cwd` = source; ids grammar-valid; the codex `session_meta`/`turn_context` and claude `user`/`assistant` shapes mirror the staged seeds); the extraction of `_execute_scenario` and the `with` placement (poison built as a SIBLING of `work`, so the body's rmtree/mkdir never touches it); the oracle's FAIL-not-INVALID posture; the out-of-tree demonstration driver; the four-path write set and its fences. No edit under this relay. The token issues only after your approve AND the Master Reviewer's approve of `5c81e86a`.

ACTIONS_GIT_REF: docs-lane writes only — the rev2 artifact (6133d6b2) and this relay via the engine; the root-mode measurement and the SITREP UP follow this filing; no harness byte, no product byte, no ref move; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate (the draft pre-linted per-file); the root-mode measurement (the instrument of record for the re-pointed cross-repo edge) runs on the filed revision BEFORE any waiver word and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-isolation-20260902.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-ISOLATION-REVISION2-REV4-TWO-GRAINS.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
