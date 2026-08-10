## DISPATCH (fold) — master's operator-directed GLOBAL semantic check HELD the C `d6e44d9` / B2 `0653fea` pair and RULED FOUR gating findings FOLD before merge (I-3 precedent, no deferral). The core HOLDS (tree-equivalence proven, full suite 100% green at master's seat e2 173.5s<600, consent/DNA verified). But four defects the scoped panels missed gate the pair: A1+A2 (the union under-seeds from refused sessions — LIVE origin-ID leak, both adapters), B1+B2 (a legal consent-NO image round-trips to a `biv pack` HARD-ABORT exit 4). I re-verified A1/A2/B1 at the bytes at `0653fea` myself; B2 carries on master's byte-verification. ONE bounded fold (all four + falsifiers), suites honestly green, a targeted re-panel of the fold (M-4 + round-trip lenses at the new SHAs), then a fresh paired hand-up — on which master re-issues the paired condition-4 to the operator. The `231437` paired-authorization request is WITHDRAWN until then. No token; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-cb2-fold-dispatch
PARENT_DISPATCH_ID: s4-floor-cb2-merge-gate
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no at this hop — this is a DOWN fold dispatch; the human gate re-engages downstream (on your fold + targeted re-panel + fresh hand-up, master re-issues the paired condition-4 to the operator). The release hold is ABSOLUTE.
DESIGN_LOCK_ID: s4-floor-fold-design-20260805
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: master/relays/s4-build-standup/MERGE-GATE-ORCHESTRATOR-PLANNER-SEMANTIC-CHECK-PAIR-HELD-FOUR-FOLDS-ROUTED-SUITE-GREEN-AT-MASTER-20260809-233408.md
RELATED_CONTEXT: master/RESIDUALS.md (R-4.13 WIDENED by master's act — both adapters + the A1 truncation; disposition FOLDS, no longer a candidate residual); docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-floor-b2-targeted-recheck-0653fea.md (the scoped re-check that PASSED — it did not cover the round-trip class B1/B2 nor weight A2 as gating)
FROM: s4.orchestrator-planner
TO: s4-floor.planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer
SUBJECT: PLAN — carry master's four gating folds (A1+A2 union under-seed; B1 claude staged-subtree class mismatch; B2 codex sidecar multi-path) into ONE bounded fold on the C/B2 pair, with the B2 STOP-and-route-to-m-2 carrier-shape condition

Master ran an operator-directed global semantic check across the cross-slice seams BEFORE the paired
authorization and HELD both branches. What holds is not in doubt — tree-equivalence proven, the full suite
100% green at master's own seat (e2 173.5s under the ruled 600; only `safety-hardening` skipped, an
ELF/readelf check that can't run on a Mach-O host — the Docker leg covers it), consent-NO cannot reach the
agent host store (one write choke point, all store paths consent-gated, refused sessions never publish), pack
host-read-only, I-3 symmetric. But FOUR findings gate the pair, all in the C/B2 window, all RULED FOLD (the
I-3 precedent — no deferral). I re-verified A1/A2/B1 at the bytes at `0653fea` at this seat; B2 I carry on
master's byte-verification with a hard STOP condition.

## FOLD A — the union under-seeds from refused sessions (LIVE origin-ID leak, both adapters; R-4.13 widened)

**A1 (order-dependent truncation) — CONFIRMED at bytes at `0653fea`:** in claude `install.cpp` the
destinations loop sets `session.refusal_detail = "undecodable_line"` and then **`break`s** out of the loop, so
artifacts AFTER the break never feed `message_uuid_origins` — the image union that verifies EVERY sibling.
Contrast the pre-refused branch, which walks all artifacts with `continue`. Whether a refused session fully
seeds the needle set depends on WHEN it refused; a sibling carrying an origin uuid that lived only in a
skipped artifact installs with the packer's uuid intact.

**A2 (artifact-derived primary id) — CONFIRMED at bytes:** version-refused entries never contribute their
artifact-derived primary identity — claude guards the union insert `if (!image_session_id.empty())` and
`image_session_id = {}` for version-refused; codex folds `prepared.origin_ids` but version-refused records
never enter `prepared_sessions`, and the `records` pass adds only primary/parent/child.original_id, not the
artifact-derived alias. (This is the caveat I earlier routed as a candidate residual / non-blocker — master
WIDENED it to a LIVE gating leak across both adapters. Owning the mis-weight: an origin-ID leak vector gates
even when pre-existing and low-realism.)

**Fold shape (master-endorsed):** derive the id union from `records` — artifact-derived identity included —
BEFORE the version-floor gate, never from `prepared`; and collect-then-decide — needle harvesting never
`break`s on refusal (collect ALL artifacts, THEN set the refusal). **Falsifiers required:** (1) a
staged+version-refused sibling whose artifact-derived alias id IS needled (both adapters); (2) a
refused-mid-collection session that still fully seeds the union (the truncation falsifier — a refusal in an
early artifact must not drop a later artifact's origin uuid from the set).

## FOLD B — consent-NO output that `biv pack` cannot re-pack (round-trip HARD-ABORT ×2)

The consent-NO carrier exists precisely so consent-NO output round-trips; these ship the feature broken on
reachable inputs. This whole class is the dimension the scoped install-side M-4 panels never tested — flag it:
the fold's re-panel MUST carry round-trip lenses (open a legal image consent-NO → `biv pack` the workspace →
succeeds), not only M-4.

**B1 (claude staged-subtree class mismatch) — CONFIRMED at bytes at `0653fea`:** the installer places any safe
subtree artifact ending `.jsonl`/`.txt`/`.meta.json` with NO directory constraint (`install.cpp` safe-relative
subtree handling), but the staged RE-collector accepts ONLY `subagents/*.jsonl`, `subagents/*.meta.json`,
`tool-results/*.txt` and hard-errors otherwise (`staged_subtree_class`, `claude_code.cpp:478-488`), and
`append_staged_session` runs FIRST in `collect()` (`:606-608`) so the error aborts the ENTIRE pack (exit 4, NO
image). A legal image (e.g. `<id>/notes.txt`, `<id>/tool-results/x.jsonl`) opens consent-NO exit 0, then the
workspace is unpackable. **Writer and reader of the carrier must agree.** Fold: align the re-collector's class
set with the installer's (same-set is the invariant — you propose which side moves), OR skip-and-warn
per-session instead of aborting the pack. **Round-trip falsifier required.**

**B2 (codex sidecar multi-path) — carried on master's byte-verification:** collection admits any session whose
cwd is a DESCENDANT of the source root (`codex.cpp:1194-1196`), so one image routinely holds distinct
`original_path` values; consent-NO stages both and unions their pair sets into one sidecar
(`sessions.cpp:522-526`) — which `resolve_codex_staged_original_path` then rejects (`invalid_staged_sidecar`,
`codex.cpp:548-568`; the code's own comment concedes "A9 carries a global pair set, not a row-to-pair edge").
Same hard-abort at re-pack. **HARD CONDITION — STOP-and-route:** if closing this needs a sidecar/carrier SHAPE
change (a row-to-pair edge), that is design-of-record territory — **STOP and route UP through me for the m-2
addendum route; do NOT amend the sealed carrier shape at the pair.** If it closes within the sealed shape
(e.g. per-row `original_path` recorded in the existing structures), the pair folds it. **Round-trip falsifier
required either way.**

## Non-gating (your discretion — fold cheaply or register a condition; no ruling owed by me)

- Latent report-integrity hazard: the containment-refusal paths construct a FRESH `InstallResult`
  (codex `:414-427`) / push-all-and-return (claude `:662-667`), discarding already-accumulated typed
  version-refusal rows (the `sessions.clear()` shape as a fresh object). Unreachable today (pre-checks make the
  branches dead) — fold cheaply or register your own condition; disclose either way.
- Coherence (slice E, not leaks — both FAIL-CLOSED): claude lacks codex's in-image parent mapping
  (over-refuses a case codex resolves); codex's parent lookup makes a version-refused parent refuse its clean
  child. Dangling minted parent reference + report ordering — cosmetic, your discretion.
- Carve-out contradiction: `unsupported_subtree_class` tolerated batch-wide at claude `:603-606` then the same
  artifact refuses per-session at `:690-694` — clarify intent; if skip-the-artifact is intended, the prepare
  pass needs the same predicate.
- Consent-NO "clean skip" drift: CONFIRMED INTENDED at master — the staged carrier IS the consent-NO behavior
  per the sealed A9/A10 design; the Step-3 E-2 clean-skip was superseded. No action; recorded so the next
  reader does not re-open it.

## The return (what I need back)

ONE bounded fold on the pair — A1+A2+B1+B2 with their falsifiers, the non-gating items at your discretion —
suites honestly green, then a **targeted re-panel of the fold** (M-4 **and** round-trip lenses at the new exact
SHAs), then a fresh paired hand-up. On that hand-up master re-issues the paired condition-4 to the operator.
B1(slice) + slice A stay merged/clean; matrix R-4.8 work is unaffected; slice E follows the pair. If B2 forces
a carrier-shape change, STOP and route up to me BEFORE touching the sealed shape. No token rides this; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — byte re-verification only at `0653fea` (claude
`install.cpp` destinations-loop `break` vs pre-refused `continue`; `image_session_id` empty-guarded union
insert; `claude_code.cpp:478-488` re-collector class set vs installer subtree acceptance;
`claude_code.cpp:606-608` append_staged_session ordering). This relay + its INDEX row ride one explicit-path
docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 — per-file WITH freshness at this seat before filing; `.relays/s4/INDEX.md` tail
re-read for sibling rows before appending; `--index`; commit GATED on both exits, path-scoped add AND commit.
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this
seat's writes are confined to this relay and `.relays/s4/INDEX.md`.

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-FOUR-GATING-FOLDS-CARRIED-DOWN-A1-A2-B1-B2-20260809-234510.md` → `s4-floor.planner`
- master's global semantic check HELD C `d6e44d9` / B2 `0653fea`; four gating folds RULED (I-3 precedent, no deferral); core HOLDS, suite 100% green at master
- FOLD A (A1 truncation-`break` + A2 artifact-derived id): derive union from `records` before the version gate, collect-then-decide (never `break` on refusal); falsifiers = staged+version-refused alias needled + refused-mid-collection full seed
- FOLD B (B1 claude staged-subtree class mismatch → pack exit 4; B2 codex sidecar multi-path invalid_staged_sidecar): B1 same-set class invariant OR skip-and-warn; B2 per-row original_path within the sealed shape, else STOP-and-route to m-2 for the carrier-shape addendum; round-trip falsifiers required
- return = ONE bounded fold + falsifiers → suites green → targeted re-panel (M-4 + round-trip lenses at new SHAs) → fresh paired hand-up (master re-issues paired condition-4); `231437` paired-auth WITHDRAWN until then; release hold ABSOLUTE
