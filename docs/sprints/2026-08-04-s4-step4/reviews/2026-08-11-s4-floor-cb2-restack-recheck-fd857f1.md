# RE-STACK re-check — C `f03ce70` / B2 `fd857f1` (post-R-4.8)

Two read-only lenses over the SEVEN FRESH files; the other 27 of the 34-path paneled union are byte-identical
to `3762f37` and carry their prior combined-re-check PASS.

| Lens | Verdict |
|---|---|
| Reconciliation completeness | **PASS** — 1 LOW cosmetic, 2 INFO |
| Containment at the re-stacked head | **PASS** — 1 MEDIUM (inherited, already registered), 1 LOW (inherited), 2 INFO |

**RE-CHECK VERDICT: PASS.** One evidence item is still owed before hand-up (§5).

## The reconciliation is mechanically proven, not asserted
Convener-reproduced independently:
```
ideal 3-way merge:  git merge-tree --write-tree --merge-base <old-base> <new-base> <paneled-B2>
                    -> tree 76678b81fcf13e0fd67308471f6619f7a89dc0bf
diff(ideal tree, NEW B2) -> EXACTLY the 5 manually-reconciled files
                            adapter.hpp and pack.cpp ABSENT => the hand result equals git's
                            auto-merge BYTE-FOR-BYTE for both unions
path union: paneled pair vs re-stacked pair -> IDENTICAL 34 paths (no drops, no additions)
```
The lens added the two-directional half: R-4.8's 275-file change set intersects the pair union in EXACTLY
the 7 differing paths, and for 6 of those 7 the `paneled → new` delta is **line-for-line identical to R-4.8's
own delta** (added/removed line multisets compared both ways; "missing from reconciled" and "smuggled into
reconciled" both empty). So nothing of the pair changed and R-4.8 landed verbatim. The 27 carrying files are
not merely identical — they are **untouched by R-4.8**, so their carry is legitimate rather than a silent
revert of base work.

## `sessions.cpp` — the file that forced C to move — is a one-field change
Delta from the paneled bytes is exactly `.packer_home = manifest.packer_home` on the `InstallTarget`
initializer. **And the conservative side won the neighbouring argument:** the base hardcodes
`adapters::Consent::yes` at that call site while the pair passes `adapter_consent`; the reconciliation kept
`adapter_consent`, so C's per-agent consent flow — the whole point of that slice — did not get silently
reverted by taking the base's side. Convener-verified at the bytes.

## The pair's contract survived the merge (each item verified)
`.pending-r415` / `child_alias_ids` / `child_identity_shape` absent repo-wide (wrap-tolerant sweep); no
"origin `agentId` is ABSENT" assertion resurrected (all 10 `agentId`-near-`npos` sites are PRESENCE checks,
structurally identical to the paneled bytes); `IdMapEntry.children` identity assertions intact (counts
identical: 10 / 19 / 22); **the three-layout acceptance case is byte-identical to the paneled bytes**, all
three fixture classes driving stage→pack→open; A9 `children` still a pair list and the schema file
byte-identical.

## Findings — none gating
- **[MEDIUM, INHERITED, ALREADY REGISTERED]** R-4.8's `packer_home` writes the packer's raw `$HOME` into the
  image manifest and **no production code reads it** — a write-only carrier at this SHA. The lens declined to
  call it Critical on sound grounds: the manifest already discloses the packer's home via `source_path`,
  `original_path` and `provenance.store_root`, all predating this pair, so it opens no new channel or class;
  reading the invariant as "no packer home in an image at all" condemns the shipped baseline, not this
  candidate. **Convener check: this is not a new residual — `master/RESIDUALS.md:951` is the R-4.8 row, the
  deferred home-prefix needle IS the missing consumer, it has named owners, and line 1042 already gates it:
  "R-4.8's release gate should not close with the needle's observability dark."** Inherited, tracked, gated.
- **[LOW, INHERITED]** A malformed/lone `packer_home` / `packer_home_flavor` fails the whole manifest parse —
  open/parse-side, fail-closed, consistent with every other manifest field. Not a widened pack abort.
- **[LOW, cosmetic]** One leading space lost on `install_calls` in `tests/test_sessions.cpp` — the ONLY byte
  in all seven files belonging to neither side's delta. No semantic effect; no `.clang-format` in the repo and
  the workflow runs clang-tidy only, so no CI risk. Restore on any follow-up touch; not worth a cycle.
- **[INFO]** R-4.8's `const InstallTarget&` → `const InstallTarget& target` rename appears "missing" from the
  reconciled delta because the pair had already named that parameter — base intent satisfied, verified at
  source rather than inferred from diff shape.
- **[INFO]** Cross-side interaction no per-file diff can see: R-4.8's two new `test_sessions.cpp` cases were
  written against the BASE `run_session_leg` and now execute against the PAIR's, which adds two pre-install
  gates. Both enumerated and neither fires for those fixtures (`adapter_consent == yes` so the
  foreign-staging-carrier gate is not taken; the store dir exists with default write bits so
  `store_write_bits_absent` is false), signatures and arities compatible, no duplicate-symbol collision.

## Carried from the paneled verdict (27 files, byte-identical AND untouched by R-4.8)
The option-(a) logic (`child_ids` identity, alias-arm removal, A9-safety), the acceptance instrument's
genuineness, contained-side intactness on the path channel, and the routed items (E-1/E-2/E-3 → slice E,
R-a → residual). **The struck `staged_path_caveats` convener-error line stays struck.**

## Mechanical (convener)
C one commit on `38a4702`, B2 one atop C, subjects preserved; both merge CLEAN into `origin/main`;
`38a4702` an ancestor of new C; both union files retain R-4.8's `packer_home` (1 in `adapter.hpp`, 3 in
`pack.cpp`, vs 0 paneled); A3 correctly does not re-fire (`e3.py` + both anchored collectors are exact CARRY
rows); **blast radius 1**, down from 27.

## §5 — the one item owed before hand-up
The Linux product failure count moved **1 → 5**, and the report classifies the four new ones as a
"registered emulated process-lifecycle class" on a bounded control that EXCLUDES the disputed cases — it
cannot distinguish inherited from introduced. Convener static chase: `tests/test_probe.cpp` is
**byte-identical across paneled B2, `origin/main`, and the new head** (25 cases throughout), neither R-4.8
nor this stack touches any probe/process/spawn source, and `error.cpp` has zero probe-classification logic —
so environment variance is the only explanation consistent with the bytes. **That is an inference; one
container run on plain `origin/main` converts it to evidence.** Requested at `013353`. Same five on the base
⇒ inherited and the pair is exonerated; fewer ⇒ STOP and diagnose.

## Disposition
Re-check PASS. On the base-container control, file the fresh paired hand-up (C first, B2 immediate) with
A10.3 and the blast-radius line of **1**. Nothing seals; merge ≠ push ≠ release; the release hold is ABSOLUTE.
