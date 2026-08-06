# DR-3 fixture ledger — Arm 1 (FROZEN at PLAN, 2026-08-06)

**Status: FROZEN** — materialized inside the Arm-1 PLAN per design D7 (rev4 at `934fca3`, blob `802b8499…`).
Flips are decided-not-deleted: every flip row names its replacement oracle; every retain row says why the empty-repos case stays valid (payload-only images remain legal — `repos` may be empty forever).
Sites cite `main@8981bfd` (the audit baseline); instruments are the audit's greps, re-runnable at any base.
`arm/task` keys into the Arm-1 plan (`2026-08-06-s4-matrix-arm1-plan.md`); `status` moves FROZEN → DONE as tasks land, never edited otherwise.

## FLIP rows (assert a fence; go RED when it opens; replacement oracle named)

| id | site (at 8981bfd) | decision — replacement oracle | instrument | task | status |
|---|---|---|---|---|---|
| L-F1 | `tests/test_manifest.cpp:163-167` (`"repos": [1]` ⇒ refused, `step2-plain-dir-only`) | replace with positive full-§2.3+G parse suite + malformed-item rejection (an explicit negative-schema case retained) | `git grep -F 'step2-plain-dir-only'` | T5 | FROZEN |
| L-F2 | `tests/test_scan.cpp:131-138` ("scan refuses repo-bearing roots") | replace with discovery oracle: repo boundary recorded (id/relpath/kind), walk continues, no refusal | `git grep -F 'RepoDiscoveredUnsupported' -- tests` | T6 | FROZEN |
| L-F3 | `tests/test_pack.cpp:236-245` ("pack refuses repo-bearing source", no `.bvpk` left) | replace with clean-repo pack oracle: image seals, manifest carries the repo entry, `repos/` members present per entry | same as L-F2 | T6 | FROZEN |
| L-F4 | `tests/test_envelope.cpp:147,180,181` (exit-map row + closed count + transitional literal) | row list updated: `RepoDiscoveredUnsupported` REMOVED (honoring its shipped `transitional: true`), D5 new kinds added, count re-closed at the new total | `git grep -F 'RepoDiscoveredUnsupported' -- tests schemas` | T5 | FROZEN |
| L-F5 | `schemas/biv-exit-map.v1.json:5` (the transitional row) | row removed + D5 rows added in the same reviewed head as L-F4 | same | T5 | FROZEN |
| L-F6 | `harness/bivharness/manifest.py:81-82` ("repos must be [] for Step-2 plain-dir") | replace with per-item §2.3+G validation mirroring the product parser (incl. the G-R6 note member) | `git grep -F 'repos must be' -- harness` | T5 | FROZEN |
| L-F7 | `tests/test_envelope.cpp:446-464` (frozen open-envelope byte-oracle, "NEVER regenerate") | ORACLE RECAPTURE — ONE recorded decision, new literal captured at the schema-act head, same-head with the schema change per ruling `200505`; never a serializer re-dump habit | manual: the ORACLE RULE comment | T5 | FROZEN |
| L-F8 | `src/core/report/envelope.cpp:79-81,107-109` (hardcoded empty `repos: []` summaries) | production flip WITH L-F7: real repo rows rendered; envelope schema gains the row shape | `git grep -n -F '"repos"' -- src` | T5 | FROZEN |

## RETAIN rows (carry `repos: []` as input/fixture; stay GREEN; survival decided, not assumed)

| id | site | why retained | task | status |
|---|---|---|---|---|
| L-R1 | `tests/test_manifest.cpp:78-79` (serialize golden) | an empty-repos manifest still serializes `[]` — the golden stays true | T5 verify | FROZEN |
| L-R2 | `tests/test_manifest.cpp:124` (unknown-fields fixture) | input fixture; parser change keeps it green | T5 verify | FROZEN |
| L-R3 | `fuzz/corpora/manifest/seed1.json:14` | valid seed under the new parser | T5 verify | FROZEN |
| L-R4 | `harness/fuzz/corpus/manifest/{golden,fv99,oversize-field}.json` | same | T5 verify | FROZEN |
| L-R5 | `tests/fixtures/probe-envelope-v1.json:66` (via `CMakeLists.txt:219`) | probe envelope unaffected by populated-repos support | T5 verify | FROZEN |
| L-R6 | `harness/selftest/test_manifest.py:22` + `harness/selftest/stub_biv.py:71` | empty-repos goldens remain legal images | T5 verify | FROZEN |
| L-R7 | the ten `manifest_variant` scenarios (`open-collision-rename-projectkey`, `open-consent-no`, `open-consent-per-agent`, `open-consent-yes`, `open-deny-default`, `open-no-sessions-regression`, `open-store-locked`, `open-unknown-agent`, `plain-dir-v1`, `plain-dir-v2`) | payload-only manifests remain legitimate empty-repository cases (implementer audit §3) | T8 verify | FROZEN |
| L-R8 | `schemas/biv-json-envelope.v1.schema.json:155,158` | already tolerant (type array); gains the repo-row item shape additively | T5 | FROZEN |

## ADD rows (new assertions the flip set does not cover)

| id | addition | task | status |
|---|---|---|---|
| L-A1 | `harness/schemas/manifest-plaindir-v1.schema.json`: repos item shape + the missing `maxItems`/`minItems` decision (implementer audit gap) — schema gains the §2.3 entry shape; no maxItems (unbounded repos list is legal) recorded as the decision | T5 | FROZEN |
| L-A2 | harness selftest positive/negative coverage for populated repos (currently empty-array-only) | T5 | FROZEN |
| L-A3 | FX-G-1 legs — engine `a, b, b2, f, i, k` (harness scenario rows) | T8 | FROZEN |
| L-A4 | FX-G-1 legs — schema/parser `c, d, e, g, j`, `l`(l1–l9), `m` (schema-act test suite) | T5 | FROZEN |
| L-A5 | FX-G-1 leg `n` (P1 render bar, both surfaces + `--json` round-trip decode) | T7 | FROZEN |
| L-A6 | FX-G-1 leg `o` (writer bounds, o1–o5; o5 constructed-trigger with injected enumeration) | T6 | FROZEN |
| L-A7 | B3 hostile row: checkout-created symlink parent + declared penumbra member ⇒ `MemberAncestryUnsafe`, no out-of-root write, partial reported | T7 | FROZEN |
| L-A8 | combined shallow+promisor row: shallow capture under `GIT_NO_LAZY_FETCH=1`, zero fetch subprocess activity, `promisor-source` note | T6 | FROZEN |
| L-A9 | stage-lifecycle golden assert: no `.biv-stage` path in any restored tree | T7/T8 | FROZEN |
| L-A10 | transitional-fence rows: dirty/nested/submodule each refusing with its D5 typed kind | T6 | FROZEN |
| L-A11 | zero-artifact proven-overlay row (`bundle: null`, no `local_refs_bundle` — materializes from remote alone) | T8 | FROZEN |
| L-A12 | eligibility spread rows (proven-overlay / sha-unpushed-full / no-remote-full) + unborn zero-ref control (leg e) | T8 | FROZEN |

## GREEN-side seams (exist today, promoted rather than created)

| id | seam | task | status |
|---|---|---|---|
| L-G1 | `harness/scenarios/shells/d-git-restore.json` (xfail-pending shell) → the first real golden row | T8 | FROZEN |
| L-G2 | `harness/tolerance/tolerance-v1.json:11-13` (git rows `future-step/unreachable`) → reachable with consumed policies | T3 | FROZEN |
| L-G3 | `harness/bivharness/compare.py:17-19` (`ALLOWED_POLICIES` git rows) → extended in lockstep with L-G2 | T3 | FROZEN |
