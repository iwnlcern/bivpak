## SITREP / STOP UP — 2a tranche 2 EXECUTED to the replacement candidate `intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468` (Step 0-bis → Steps 4–6 → ONE replacement commit, four commits above `46df8f3`, `9e6ebe8` retained; Task 3's fresh reviewer CLEAN×2; the static fence battery GREEN — TEN-path census, C-1 three callers, C-3 +5/-2 · +3/-1 · +3/-1, C-4 verbatim + writer-unit witness level, C-5, (c) census A=64/B=8/INV=72, LEG 6 / FIELD 7 / O-MUTANT 8+census, (i)(j), E4; macOS product rows GREEN incl. FX-O 803 assertions) — but the chartered Ubuntu 24.04 amd64 leg is CANDIDATE-ATTRIBUTABLE RED and the implementer STOPPED correctly (`181612`, token `153402` CONSUMED; no repair, no amend, no second commit): GCC 13 `pack.cpp:764: error: missing initializer for member 'biv::manifest::Manifest::repos' [-Werror=missing-field-initializers]` — the candidate inserts `Manifest::repos` (`manifest.hpp:78`) BEFORE `.agent_sessions`, and the pack aggregate `:753-764` (inherited, untouched) names no `.repos`; clang-tidy-22 fires the same site (`clang-diagnostic-missing-designated-field-initializers`) plus FOUR candidate-owned `manifest.cpp` findings (`:836` bugprone-easily-swappable-parameters; `:905` cppcoreguidelines-avoid-const-or-ref-data-members — `RepoRowFacts` holds `const RepoEntry &row`; `:2176`/`:2179` pro-bounds-avoid-unchecked-container-access on simdjson `operator[]`); the apparent one-line repair `.repos = {}` is a `pack.cpp` byte OUTSIDE m-1's C-2/C-3 propagation hunk ("NOTHING else"), so the execution-not-amendment STOP is the right call. VERIFIED AT MY BYTES and MEASURED beyond the report: (1) the defect PRE-DATES tranche 2 — at retained `9e6ebe8` `manifest.hpp:78` already declares `repos` before `agent_sessions` and `pack.cpp:753-764` already omits it; Linux was never run on that tree (the `063445` STOP preceded Task 4), so two tokens carried a Linux compile red no macOS gate could see — a plan defect I own: Task 3 Step 4 "run green" is macOS-only and Linux waits for Task 4; (2) STOPPED INSTRUMENT ≠ CENSUS: the build died at `bivcore`, so GCC never reached the tests — the three `Manifest` fixture aggregates `tests/test_cli.cpp:92-101`, `tests/test_open.cpp:79-88`, `tests/test_manifest.cpp:38-47` omit `.repos` identically (each goes `.packer_home` → `.agent_sessions`) and will fire the same `-Werror` once `bivcore` compiles — a per-site repair is therefore FOUR bytes, THREE of them outside their ruled hunks (`pack.cpp`, `test_cli.cpp`, `test_open.cpp`), not one; (3) THE DISCRIMINATOR, RUN on both compilers: an omitted designated member with NO default member initializer is RED; the SAME omission with `member{}` in the struct is OK; an explicit `.member = {}` is OK — GCC 13.4.0 (`gcc:13` amd64 container) and Homebrew clang 22.1.8 (the container's clang-tidy major) partition identically; hence a default member initializer `std::vector<repo::RepoEntry> repos{};` at `manifest.hpp:78` — the struct's own existing pattern (`required_capabilities{}` at `:71`, `packer_home{std::nullopt}` at `:77`), in the write set, semantically identical (an omitted member value-initializes to the same empty vector; the writer emits `"repos": []` either way; no behaviour, wire, or sealed-text change) — silences ALL FOUR sites on BOTH instruments with ZERO fenced-file byte. TWO ROUTES for the owner: (A) RECOMMENDED — the header default member initializer; no C-2/C-3 change; execution within the allowlist of record; asks only m-1's CONFIRMATION that this reading is right (a struct default initializer is not a fence byte and not an amendment of sealed O/N/M, which are silent on C++ initializer form); (B) four per-site `.repos = {}` initializers; requires m-1 to EXTEND C-2/C-3 to three more hunks (pack `+6/-2`; test_cli/test_open each `+4/-1`). The four tidy findings are in-scope `manifest.cpp` bytes (no ruling needed; the repair shapes are the implementer's under the plan — `.at()`/`find` for `:2176/:2179`; a pointer or index for `:905`; a NOLINT with reason or a struct parameter for `:836`, NOLINT precedent exists at `adapter.hpp`/`restore.cpp`). RESUME PLAN, in-lane on the carry (per master's 2026-08-20 confirmation that a candidate-introduced defect repairs in-lane through local gates): plan REVISION 13 (identity preserved, W-5 selector frozen; replacement measurement filed) adding Step 0-ter — the ruled initializer route; the four tidy folds; a LINUX CONFIGURE+BUILD GATE (H/R/T + `cmake --preset ci` + build, no suite) BEFORE the replacement commit so a compile-level platform divergence can never again ride to Task 4; re-cut by `git reset --soft 363d812` + explicit staging of the six paths with proofs (a)(b)(c); Task 4 re-run in full — → your implementer's exact-hash review → fresh token `intg-substep2a-impl-4`. The candidate `b09e192` is FROZEN: not a merge-packet input; m-1's V-FA and m-3's C-6 reviews NOT requested at it. DISCLOSED: the implementer's `181132` is a 15-line skeleton (`SUBJECT: draft`) that reached the root before the real STOP `181438`/`181612` — inert, the implementer's to note; no byte of mine. The count-gate token stays HELD (its precondition, the tranche-2 landing, has moved out); no product byte at this seat; no merge, push, PR, publication, release; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2a-impl-3
PARENT_DISPATCH_ID: intg-substep2a-plan-review-12
IN_REPLY_TO: intg-substep2a/IMPL-pair-implementer-20260903-181612.md
RELATED_CONTEXT: intg-substep2a/IMPL-pair-planner-20260903-153402.md; intg-substep2a/PLAN-pair-planner-20260902-070149.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260901-231935.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md; ../../pdc/master/relays/intg-substep2a-format-act/PLAN-master-planner-20260902-035616.md; ../../pdc/master/relays/r438-transcription-at-merged-bytes/PLAN-master-planner-20260903-135906.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md; ../../pdc/master/RESIDUALS.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — the ruling asked is the fence owner's (m-1, via master): confirm route (A) or extend C-2/C-3 for route (B); the tidy folds and the Linux compile gate are in-lane plan work under the standing local gates; the candidate is frozen and no byte moves before rev13 → exact-hash review → a fresh addressed token; m-1's and m-3's byte reviews, the merge packet, the count-gate observations, push, publication, deployment, and release keep their gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 e5875e8ee830265743e05c09db2224d2bca956f9dba7ed7372cfc417889dd2bc
BRANCH: intg/format-act@b09e1922c16da50b5bef0644d9923a567b98c468 in ../bivpak-intg-format-act (verified at this seat: HEAD, `git log --oneline 46df8f3..HEAD` = 4, `git diff --name-only 9e6ebe8..HEAD | sort` = the six Task-3 paths, status empty); FROZEN RED CANDIDATE — not a merge-packet input
FROM: intg.pair-planner
TO: master.master-planner
CC: operator, master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP — tranche 2 candidate b09e192: macOS + static fences GREEN, Ubuntu RED candidate-attributable (GCC 13 missing initializer for Manifest::repos at pack.cpp:764; clang-tidy same + four manifest.cpp findings); the per-site repair is outside m-1's C-2/C-3 hunk — implementer STOPPED correctly; measured: defect pre-dates tranche 2 (9e6ebe8, Linux never run), THREE test fixtures share it (stopped build never reached them), and a header default member initializer repos{} silences GCC 13 + clang 22 with zero fenced byte (discriminator run both compilers) — ask m-1 via you: confirm route (A) header NSDMI [recommended] or extend C-2/C-3 for route (B) four per-site initializers; rev13 in-lane on the carry (initializer route + four tidy folds + a Linux compile gate before the replacement commit) → review → intg-substep2a-impl-4; candidate frozen; count-gate token held

## The red, at the bytes (verified at this seat, `git show b09e192:…`)

```text
manifest.hpp:69-81 @ b09e192      struct Manifest { … :77 std::optional<PackerHome> packer_home{std::nullopt};
                                                  :78 std::vector<repo::RepoEntry> repos;          ← NEW member, NO default initializer
                                                  :79 std::vector<AgentSessionEntry> agent_sessions; :80 BivignoreProvenance bivignore; };
pack.cpp:753-764 @ b09e192        const manifest::Manifest manifest_model{ … :761 .packer_home = …, :762 .agent_sessions = …, :763 .bivignore = …, :764 };
                                  → GCC 13: error: missing initializer for member 'biv::manifest::Manifest::repos' [-Werror=missing-field-initializers]
                                  → clang-tidy-22: error: missing field 'repos' initializer [clang-diagnostic-missing-designated-field-initializers]
pack.cpp diff 363d812..b09e192    EXACTLY the ruled hunk: :765 auto manifest_json = manifest::serialize(manifest_model); + the braced refusal; :778 *manifest_json  (+5/-2)
                                  the aggregate :753-764 is UNTOUCHED by the candidate — the repair site is outside the hunk by construction
same shape, NOT yet reached:      tests/test_cli.cpp:92-101 · tests/test_open.cpp:79-88 · tests/test_manifest.cpp:38-47  (each .packer_home → .agent_sessions, no .repos)
pre-existence:                    9e6ebe8: manifest.hpp:78 repos before agent_sessions; pack.cpp:753-764 without .repos  → the SAME red at the retained tree; Linux never run there
warning policy:                   CMakeLists.txt: -Wall -Wextra -Werror on every target (:50/:80/:94/:99/:106…:174); .clang-tidy WarningsAsErrors '*'
```

## The discriminator, RUN (must-be-RED / must-be-OK on both instruments)

```text
probe   struct S { int a{1}; std::vector<int> r;    int b{2}; };  S s{.a = 1, .b = 2};          (a) omitted, no NSDMI
        struct S { int a{1}; std::vector<int> r{};  int b{2}; };  S s{.a = 1, .b = 2};          (b) omitted, WITH NSDMI  ← route (A)
        struct S { int a{1}; std::vector<int> r;    int b{2}; };  S s{.a = 1, .r = {}, .b = 2};  (c) explicit               ← route (B)
GCC 13.4.0   (docker gcc:13, linux/amd64; -std=c++20 -Wall -Wextra -Werror)                      (a) RED  (b) OK  (c) OK
clang 22.1.8 (Homebrew; -std=c++20 -Wall -Wextra -Wmissing-designated-field-initializers -Werror) (a) RED  (b) OK  (c) OK
semantics    (b) ≡ (c): the omitted member is value-initialized → empty vector → the writer emits "repos": [] in both; no wire byte differs
```

## Ask (m-1 via you) and the lane's resume

```text
(A) RECOMMENDED  manifest.hpp:78  std::vector<repo::RepoEntry> repos{};   — write-set file; the struct's own pattern (:71, :77); zero fenced byte;
                 C-1..C-7 unchanged; O/N/M silent on initializer form → CONFIRM this is execution within the allowlist, not amendment
(B)              .repos = {}, at pack.cpp:761/762, test_cli.cpp:100, test_open.cpp:87 (+ test_manifest.cpp:46, in scope)
                 → m-1 must EXTEND C-2/C-3 to three more hunks (pack +6/-2; test_cli, test_open +4/-1) — three fenced bytes for the same result
either way       plan rev13 in-lane (identity preserved; W-5 replacement measurement filed): Step 0-ter = the ruled initializer route + the four
                 manifest.cpp tidy folds (:836 :905 :2176 :2179; shapes the implementer's; NOLINT-with-reason precedent adapter.hpp/restore.cpp)
                 + a LINUX CONFIGURE+BUILD GATE before the replacement commit (the gate this plan lacked) → reset --soft 363d812 → explicit
                 staging, proofs (a)(b)(c) → the replacement commit → Task 4 in full → exact-hash review → fresh token intg-substep2a-impl-4
frozen           b09e192 not a merge-packet input; m-1 V-FA / m-3 C-6 reviews NOT requested at it; 9e6ebe8 stays retained by tag
```

ACTIONS_GIT_REF: docs-lane writes only — this SITREP via the engine; ROADMAP's tranche-2 state entry; commit path-scoped follows; the compiler probe ran in /tmp and a disposable `gcc:13` container (read-only mount; nothing pruned); no product byte, no ref move on the candidate branch, no observation run
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the draft pre-linted per-file; every upstream route directory and every pair cycle directory re-listed immediately before submit (160358 and 153458, TO m-3, read as CC context)
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
 M docs/sprints/2026-08-27-intg-consent-fabric/ROADMAP.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/SITREP-2A-TRANCHE2-LINUX-RED-STOP-ROUTED-UP.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
