## SITREP — before writing rev33 I scouted c8T in full at scratch bytes. 23 of the 32 tidy findings take behaviour-neutral repairs. At that scout head, the plan's own canonical container gives rc 0 and tidy leaves EXACTLY the 9 remaining findings, and macOS `-r xml` is green on all five binaries. Those 9 are the "interface-level findings" that your R2 says STOP up: 4 are in a GENERATED sealed table and 5 are parameter-order findings on function signatures. I also need one ruling where your "ONE c8T" meets sealed per-commit veto 9: the `restore.cpp` fix must be its own commit. rev33 is written around these; I file it after your word on the three asks below. No product byte at this seat; the release hold is ABSOLUTE.

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-215035.md
RELATED_CONTEXT: ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260924-215035.md; intg-substep2b/SITREP-pair-planner-20260924-212307.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924/SHA256SUMS; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the three asks sit inside your 215035 rulings (R2's STOP-up of interface-level findings, and the veto-9 reading of R2's commit count); owner words are yours to route; no operator gate is sought; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-3.planner, m-4.planner, operator
SUBJECT: SITREP — c8T scouted whole at scratch bytes: 23 of 32 tidy findings repaired behaviour-neutrally (container rc 0, tidy = exactly the 9 held, macOS -r xml five binaries rc 0 incl. biv_tests 484/0/0/3); asks: (A) veto 9 forces the restore.cpp repair into its own commit c8Tr before c8T; (B) the owners' word on the 9 interface-level findings (4 in the generated consent table, 5 swappable-parameter signatures), with proposals; (C) the owner byte-review list by file:line
REPO: `../bivpak` docs lane — this relay and the census record `docs/sprints/2026-08-27-intg-consent-fabric/results/linux-census-20260924/` (commit f4af9a2: the two scout patches, the held list and the scout-head summary; SHA256SUMS a57cbbe6ba9e…), no trailer; the candidate at a83657e untouched; the evidence home read only (`runners-dir.txt` still names `s2b-runners-sK9rhy`). Scout = a scratch clone with the repair-1/2 commits plus two scratch commits; containers disposable (`ubuntu:24.04` `linux/amd64` `--init`, the plan's own `linux-container.sh`, impl-10's verified LLVM mirror read-only, one persistent tidy-loop container of my own that I remove at the end). No credential entered any container. `../pdc` read-only.
BRIDGE: intg.pair-planner → master.master-planner (three asks, then rev33); m-1 / m-3 / m-4 CC (the proposals below are for your word once master routes them; nothing is asked of you directly); implementer CC (nothing to run); operator CC (no push, no PR, no merge, no release)

## The scout, measured

Scout head `8532d0cf35ebbf6cde3d3cc68ad764a9214eb420`, = a83657e + repair 1 (c8L) + repair 2 (c8H) + c8Tr (`repair-3-c8Tr-restore-seam.patch`, f58cc04302f7…, `restore.cpp` +6/−3) + c8T (`repair-4-c8T-mechanical-tidy.patch`, 165b8f969ca5…, 5 files +38/−22: main.cpp 1/1, url_consent.cpp 12/4, open.cpp 16/10, pack.cpp 3/4, envelope.cpp 6/3).
Canonical container at that head: rc 0; Phases R/T/S 0; every producer 0; ctest rc 8 as data. Two tests failed. `safety-tidy-analyzer` shows exactly the 9 lines of `clang-tidy-held-after-c8T.txt` (ac1e50744c8e…), coverage 37/37. `harness-selftest` failed the same 4 cases as the repair-2 head (4th variance sample, appended to the record).
macOS `ci-macos` at the same head: build rc 0, and under `-r xml` biv_tests 484/0/0/3, engine 82, git 6, subprocess 12, probe 25, all rc 0.

## The 23 repairs and their neutrality arguments (for rev33 and the owners)

- `restore.cpp:13` non-const global → a function-local static behind `forced_ceiling_error()`; the same single bool, same seam semantics, same two accessors (c8Tr).
- `main.cpp:539` unchecked optional → `row.sha.value_or(std::string{})`; unreachable-empty: `manifest.cpp:1207` requires `unborn == !sha`, and `open.cpp:1158-1159` renders unborn rows as "(no commits)" before this line.
- `url_consent.cpp`: do-while → `while (true)` with the identical break test; `paths[i]` → `paths.at(i)` inside the unchanged bound; `catch (...) {}` → `catch (const std::invalid_argument&)` / `catch (const std::out_of_range&)`, each setting `total = 0` (the only two throws `std::stoull` makes, and `total` was already 0 on that path); `+#include <stdexcept>`.
- `envelope.cpp:447/464`, `open.cpp:1370`: inside the UNCHANGED `if (x.has_value())` guards, `const auto v = x.value_or(T{});` (binding `*x` or re-testing `has_value()` still trips the check).
- `open.cpp`: `operator[]` → `.at()` at 564, 572, 597, 624, 644, 647, 946, 958 and 962, every one inside an existing bound check, so none can throw; `StageCleanup` gains a defaulted ctor and deleted copy/move (it is never copied or moved).
- `pack.cpp`: a hand loop → `std::iota(order.begin(), order.end(), std::size_t{0})` (`+#include <numeric>`), with identical contents; `entries[i]` → `entries.at(i)` inside the bound. The c2 manifest-serialize hunk is untouched.
No NOLINT, no `.clang-tidy` change, and no header or signature change; `restore.hpp` is untouched. None of the zero-byte fences move (manifest, adapters, e3.py, render.cpp). The A8 facts-lines still each contain `consent_display(` because c8T touches no facts line.

## Ask A — veto 9 makes it two commits

Task 9's sealed per-commit veto (`[ "$ne" -eq 0 ] || [ "$ns" -eq 0 ] || STOP`) refuses any commit touching both `src/core/repo/` and `src/cli|src/core/pack|src/core/scan|src/core/open`. One c8T spanning `restore.cpp` and the other six files STOPs Task 9 by construction.
rev33 therefore carries **c8Tr** (`restore.cpp` alone, m-1) and then **c8T** (the rest), both behaviour-neutral under your R2 fence, with the per-head container gate at each. Commit order: c8L → c8H → c8Tr → c8T → Task 9 → c9. I read your "one c8T" as a statement about the class, not the commit count. If you meant otherwise, the alternative is an amendment of veto 9, which I do not recommend.

## Ask B — the 9 interface-level findings (R2: STOP up), with proposals

Until these are ruled, no head can turn `safety-tidy-analyzer` green, and your R3 gate needs it green at every new head. rev33 cannot pass its own gate without them.
- B1 `consent_display_table.hpp:44/45` ×4 (constant-array-index ×2, unchecked `operator[]` ×2): the file is GENERATED by `tools/gen_consent_display_table.py` under A8 rev8 (m-3). Proposal: the generator emits `kConsentDisplayActive.at(mid)` (and its twin), regenerated by the tool, never hand-edited. That is a generator change in a sealed tool, so it needs m-3's word and possibly an A8 wording note.
- B2 `url_consent.cpp:263` `render_offline_bundle_row` (two adjacent `std::string_view`; declared in `url_consent.hpp`, called from `main.cpp` and tests; m-3, m-4 read): this is a public signature. Proposal: a small parameter struct with named members (value members, not references, so avoid-const-or-ref-data-members does not trip), updating the declaration, the one product call site and the test sites. The header is then in c8T's scope; `url_consent.hpp` is in the 53.
- B3 `open.cpp:481` `ensure_private_directories` (two `const path&`; file-local; m-3, m-1 co-review): proposal: a named struct `{root, leaf}` at the single call site.
- B4 `open.cpp:569` `next_utf8` (convertible adjacent parameters; file-local): proposal: return `std::optional<char32_t>` and take the cursor alone, which removes the out-parameter.
- B5 `pack.cpp:651` `path_has_segment` (two `string_view`; file-local; m-1) and B6 `pack.cpp:684` `directory_is_all_penumbra` (two `const path&`; file-local; m-1): proposal: named structs at the call sites, or reordering so the types differ.
B2–B6 change function signatures, which is behaviour-neutral but beyond the 'mechanical' class your fence names. B1 changes a sealed generator. Both are why I stop here instead of folding them into c8T. If you and the owners rule them in, they land in c8T (B1 as its own generator commit if m-3 prefers) and rev33 carries the resulting tidy-green expectation.

## Ask C — owner byte review, by file:line, before the landing

- m-1: `restore.cpp:10-18` (c8Tr); `pack.cpp:9, 629` (c8T); co-review `open.cpp:561-647` (dot-name helpers) and `open.cpp:943-962` (c6p's ancestor loops) inside the restore-apply contract.
- m-3: `open.cpp` (the hunks at 561, 569, 594, 621, 641, 943, 955, 1243, 1368), `envelope.cpp:447, 464`, `main.cpp:536`, `url_consent.cpp:3, 59, 168`, and B1's generator if ruled in.
- m-4 (security read): `url_consent.cpp:168` (the catch that replaces the empty one), `restore.cpp:10-18` (the replacement for the non-const global), and the consent files as a whole.
These line numbers are hunk starts in the scout patches; rev33 re-derives them at the landed bytes, never from this relay.

## rev33, in hand
It carries: SCOPE 53; c8L → c8H → c8Tr → c8T before Task 9, with H0 = the head after c8T; the canonical-container gate at every new head (rc 0 plus `safety-tidy-analyzer` green, coverage 37/37); the macOS count gate refusing failures > 0; the staged preservation of impl-10's `H/`, `H0.txt` and `helpers.verify-9.txt` into `$EVID/attempts/task9-H0-a83657e/`, walked with fault injection on a real-home mirror; and R-4.77 with ≥5 runs each at B and at the final head, with a per-case frequency table before the GO. I write the c8T expectations once Ask B is ruled, then walk and file for the implementer's exact-hash review. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — f4af9a2 (the scout record) and this relay, no trailer; the candidate untouched; the evidence home read only; containers disposable, nothing unrelated pruned; no product byte at this seat.
RELAY_LINT: engine-rendered submission; per-file 2.9.3 `relay-lint.py --no-freshness` on the draft; python-written; upstream listed as its own command (nothing newer than 215035, sha 39f0e8f6f784…) before this submit.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
