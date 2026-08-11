# s4-matrix AUDIT — planner seat — git-engine surface at `main@8981bfd`

**Seat:** `s4-matrix.planner` · **Dispatch:** `s4-matrix-audit` (re-homed copy of record, 20260804-231720) · **Date:** 2026-08-04.
**Baseline:** every read pinned to `main@8981bfd` via `git show 8981bfd:<path>` / `git grep … 8981bfd`; the working tree was never used as evidence.
**Independence:** authored without reading the implementer's artifact; reconciliation is the orchestrator's.
All claims E1 (path + re-findable criterion; line numbers are convenience beside the criterion, valid at the pinned SHA).

---

## 1. The Step-3 fences, re-found by criterion (R-3.50)

### Fence 1 — scanner refusal of any `.git`

**Criterion:** the directory walk, on encountering a child whose *name* is `.git` (dir or file form — the test is name-based), fail-stops the whole scan with the typed error `RepoDiscoveredUnsupported` carrying the child path.
**Site:** `src/core/scan/scan.cpp:137-138` (`if (name == ".git") return std::unexpected(BivError{ErrKind::RepoDiscoveredUnsupported, …})`), inside `walk()`, which recurses, so the fence fires at ANY depth.
**Only-site proof:** `git grep -n -F 'RepoDiscoveredUnsupported' 8981bfd -- src` → constructed exactly once (scan.cpp:138); the other src hits are the enum member (`support/error.hpp:11`), its name string (`support/error.cpp:9-10`), and the exit-map row (`report/envelope.cpp:399`).

**Ordering carve-out (deliberate, tested, matches sealed design):** the `.bivignore` prune check runs BEFORE the `.git` test (`scan.cpp:129-135` vs `:137`), so an ignored `.git` is pruned, not refused.
Pinned by test "root .bivignore can prune .git before repo refusal" (`tests/test_scan.cpp:83-95`).
This matches sealed pack-engine §1.1 ("an ignored dir is not walked, not scanned for repos, not captured") and is NOT drift; Arm 1's discovery walk must preserve prune-beats-discovery.
Also adjacent at the same site: `.biv` dirs are skipped un-refused (`scan.cpp:140-142`) — the pack-side half of the §1.2 `.biv`-never-payload rule already exists.

**Blast radius:** `scan::scan` has exactly one production caller — `src/core/pack/pack.cpp:477` (`git grep -F 'scan::scan' 8981bfd` → pack.cpp + test_scan.cpp only).
The error propagates through `pack()`'s `cleanup_error` (removes `.partial` + spool, pack.cpp:470-475), out through the CLI pack verb, mapped by `envelope.cpp:399` into exit class refusal/exit 3.
The exit map row is `transitional: true` (`schemas/biv-exit-map.v1.json:5`) — the fence knows it is temporary.
`open` never scans a source tree, so the fence is unreachable from the open verb.
Reachable-from set, complete: `biv pack` (and `test_scan.cpp:135-138`, `test_pack.cpp:236-245` directly).

### Fence 2 — manifest reader requires `repos` empty

**Criterion:** the manifest parser accepts `repos` ABSENT or `[]` and refuses any populated value with `ParseError` detail `step2-plain-dir-only`.
**Sites:** helper `require_empty_array` at `src/core/manifest/manifest.cpp:81-97` (NO_SUCH_FIELD → ok; non-array → ParseError on the key; `array.size() != 0` → ParseError `"step2-plain-dir-only"` at :94); sole call for `repos` at `manifest.cpp:597`.
**Only-site proof:** `git grep -n -F 'require_empty_array' 8981bfd` → definition (:81) + the one call (:597); `git grep -n -F 'step2-plain-dir-only' 8981bfd` → manifest.cpp:94 + tests/test_manifest.cpp:167.

**Blast radius:** `manifest::parse` has two consumers: `src/core/open/open.cpp:230` (`read_archive_plan`) and the fuzz target `fuzz/fuzz_manifest_json.cc:12`.
At open, the parse failure is WRAPPED: `open.cpp:230-233` converts it to `IntegrityFailurePreApply` (refusal, exit 3), carrying the `step2-plain-dir-only` detail — so the user-visible refusal kind for a populated-repos image is `IntegrityFailurePreApply`, not `ParseError`.
`read_archive_plan` feeds `plan_open` (open.cpp:~735), whose one CLI caller is `src/cli/main.cpp:253`; `open::open` composes the same pair.
The pack side never parses; it SERIALIZES a hardcoded empty `repos` array at `manifest.cpp:498-500` — the `Manifest` struct (`manifest.hpp:58-68`) has NO repos field at all.

### A third gate the package does not cite (finding, load-bearing for Arm 1)

The archive-member namespace is CLOSED to `payload/` and `agents/`: `open.cpp:275-279` refuses any other member prefix as `UnmanifestedMember`.
So even with fence 2 opened, `repos/<id>/…` members brick at plan time until this allowlist admits a `repos/` family; `apply_archive` (open.cpp:560-566) likewise branches only `agents/` vs payload-by-index.
And a fourth, cosmetic-but-pinned surface: the JSON envelope hardcodes empty `repos: []` in both manifest summaries (`report/envelope.cpp:79-81` pack-side, `:107-109` open-side), pinned byte-for-byte by the frozen envelope oracle (§3 below).
Arm 1's schema act must scope all four surfaces, not two.

## 2. The landed payload-restore base Arm 1 extends (package §1.2 verified)

Verified as landed behavior at the blob, all in `src/core/open/open.cpp`:

- **Partial-dir staging:** `execute_archive` stages into `<dest>.bvpk-open.partial` (suffix literal at :624), refuses a pre-existing partial (`OpenPartialPresent`, :625-628), never adopts it — matching contract §2.1 incl. the AD-2 refusal.
- **All-or-nothing seal:** members stream into the partial dir; dir mtimes are applied deepest-first afterwards (:646-651); `fsync_tree` + parent fsync (:652-657); single `std::filesystem::rename(partial, dest)` (:659); `EEXIST` at rename → `CollisionRefused` (:660-664); parent fsync after.
- **Collision handling incl. rename-exhausted refusal:** dest-exists → rename mode probes `dest(1)`…`dest(9999)` (`choose_rename_dest`, :329-339) and refuses `CollisionRefused{"rename-exhausted"}` when exhausted (:613-617); non-rename modes refuse immediately (:618-620).
- **Containment / member safety (§2.5 class):** `contained_output_path` (:443-477) requires the `payload/` prefix, rejects empty rel, and — the load-bearing part — admits a member only if every parent path segment was already created AS A DIRECTORY by this same apply (`created` map), so no member write can traverse a symlink member or escape the partial root; duplicate member paths refuse (`created.contains(rel)`, :473-475).
  Symlink members are created as symlinks and never followed (`apply_member` :516-527).
- **Member-stream integrity:** strict order/count agreement with the plan (`member-mismatch` :559-566, `member-count` :583-585) and per-member sha256 vs `checksums.json` under `--verify`.
- **Plan/apply split (contract §1 shape):** `plan_open` (read-only; no disk writes) → `OpenPlanHandle` → consent/collision decisions → `execute_open` — the mutation boundary the contract draws between `plan` and `apply` already exists (`open.cpp:~735-775`, consumed at `main.cpp:253-352`).
- **Adapter member-read seam (Addendum C M13):** `make_member_read` (:680-733) replays the archive per request; sessions containment rows live in `sessions.cpp` (`containment_refused` rows, :44/:56-57/:268-283).

**Seams a repo-restore path plugs into (extend, not re-invent):**
`ArchivePlan {manifest, checksums, payload, agents}` grows a `repos` plan area; `read_archive_plan` admits the `repos/` member family; `apply_archive` gains a repo materialization step INTO `partial_dir` before the rename (staging atomicity then covers repos for free); `OpenDecisions` carries the future consent/collision surface; checksums.json already covers any new member family; `OpenReport` grows per-repo rows rendered by `envelope.cpp`.

**Nothing found that forces re-invention.**
One design-fit note (not a defect): `apply_archive` enforces a single strict member order indexed against `plan.payload`, so the pack-side assembly order for `repos/…` members must be fixed (container doc's area ordering) and the open-side classifier extended in the same act.

## 3. DR-3 fixture inventory — the RED-to-GREEN flip set

**Instrument (absence claims per D-3.4, all at the blob):**
`git grep -n -F 'repos' 8981bfd -- tests fuzz harness schemas src`, `git grep -n -F 'step2-plain-dir-only' 8981bfd` (whole tree), `git grep -n -F 'RepoDiscoveredUnsupported' 8981bfd` (whole tree), `git grep -n -F '".git"' 8981bfd -- tests` + `git grep -n -F "'.git'" 8981bfd -- tests harness` (fence-pin sweep).
Population: every blob at `8981bfd` in `tests/`, `fuzz/`, `harness/`, `schemas/`, `src/`; session-store fixtures (`tests/fixtures/{claude,codex}_store`) inspected via the same grep and contain no repos/git pins.
No other pin sites exist under these instruments.

### 3a. Direct flips — assert the fence and go RED when it opens

| # | Site | What it asserts |
|---|---|---|
| F1 | `tests/test_manifest.cpp:163-167` | `"repos": [1]` → parse refused, detail `step2-plain-dir-only` — the fence-2 pin itself |
| F2 | `tests/test_scan.cpp:131-138` "scan refuses repo-bearing roots" | `.git` dir → `RepoDiscoveredUnsupported` — the fence-1 pin |
| F3 | `tests/test_pack.cpp:236-245` "pack refuses repo-bearing source" | same through pack, plus no `.bvpk` left behind |
| F4 | `tests/test_envelope.cpp:147` + `:180` + `:181` | exit-map row present; row COUNT closed (`count_occurrences == rows.size()`); the literal `"RepoDiscoveredUnsupported", "class": "refusal", "exit": 3, "transitional": true` |
| F5 | `schemas/biv-exit-map.v1.json:5` | the transitional refusal row (data, pinned by F4) |
| F6 | `harness/bivharness/manifest.py:81-82` | harness validator hard-errors `repos must be [] for Step-2 plain-dir` |

### 3b. Frozen-oracle flip — needs a DECIDED recapture, not a regeneration

| # | Site | Note |
|---|---|---|
| F7 | `tests/test_envelope.cpp:446-464` | open-envelope byte-golden containing `"repos": []`, guarded by the comment "ORACLE RULE: captured at BASE cd61ac6 … NEVER regenerate this literal from the serializer"; flipping it is an oracle-recapture DECISION recorded in the ledger, not a serializer re-dump |

### 3c. Carriers — hold `repos: []` as input/fixture, stay GREEN through the flip, listed so their survival is decided not assumed

| # | Site |
|---|---|
| C1 | `tests/test_manifest.cpp:78-79` (serialize golden; stays green while an empty-repos manifest still serializes `[]`) |
| C2 | `tests/test_manifest.cpp:124` (unknown-fields fixture) |
| C3 | `fuzz/corpora/manifest/seed1.json:14` |
| C4 | `harness/fuzz/corpus/manifest/golden.json`, `fv99.json`, `oversize-field.json` (one line each) |
| C5 | `tests/fixtures/probe-envelope-v1.json:66` (consumed via `CMakeLists.txt:219`) |
| C6 | `harness/selftest/test_manifest.py:22` + `harness/selftest/stub_biv.py:71` |
| C7 | `harness/schemas/manifest-plaindir-v1.schema.json:14,34` (requires the key, type array — TOLERANT of populated; the v1-plaindir schema itself needs a decided successor when `repos[]` populates) |
| C8 | `schemas/biv-json-envelope.v1.schema.json:155,158` (same tolerance) |
| C9 | `src/core/report/envelope.cpp:79-81, :107-109` (production hardcode the goldens pin — flips WITH F7) |

### 3d. Reserved GREEN-side seams already waiting

`harness/scenarios/shells/d-git-restore.json` (xfail-pending shell, classes D/K, `dor_pointers: ["m-1 §5 git restore rows"]`); `harness/tolerance/tolerance-v1.json:11-13` (`git-object-id`, `git-index`, `git-remote-config` rows at `policy: future-step, reachable: false`); `harness/bivharness/compare.py:17-19` (`ALLOWED_POLICIES` mirrors those rows).

## 4. Golden-harness seam (contract §5)

**Exists today (the base the §5 harness builds on):**
scenario-driven round-trip runner `harness/bivharness/scenario.py` (ops: `pack`, `open`, `synthesize-fv99`, `synthesize-unknown-agent` — :497-527); fixture materializer `fixtures.py` (entry types `dir`/`file`/`symlink` only — :38-51); tree comparator `compare.py::compare_trees` (byte/mode/mtime-ns/symlink-target findings classed A/B/C) driven by the versioned tolerance table `tolerance/tolerance-v1.json`, which ALREADY reserves the three git rows as `future-step/unreachable`; E2 scenario corpus + E3 cross-host runner (`e3.py`, `scenarios-e3/`); harness selftests; the reserved `d-git-restore` shell.

**Missing for a day-one Arm-1 row:**
(a) a git-repo fixture builder (`fixtures.py` cannot create repos; no git invocation exists anywhere in the harness fixture path);
(b) repo-aware comparison — `compare_trees` walks `rglob("*")` indiscriminately and would byte-compare `.git` internals, which §5 classifies as acceptable-difference; it needs a repo-boundary walk plus the §5 assertions (porcelain-v2 equality, recorded-sha checks) and tolerance rows flipped `reachable: true` with real policies (extending `ALLOWED_POLICIES` in lockstep);
(c) scenario ops for repo fixtures/assertions and the promotion of `d-git-restore` from xfail-pending shell to a real row;
(d) the DR-3 fixture ledger artifact itself (§3 above seeds it).
The §5 acceptable-difference list maps cleanly onto the existing tolerance-table mechanism — extend `tolerance-v1.json` (or version-bump it), do not invent a second tolerance surface.

## 5. Arm-by-arm surface map (package §2) + collision surfaces

Shorthand: **A** = absent (nothing landed), **E** = exists-and-extends.

**Arm 1 — single clean repo end-to-end.**
`scan.cpp/hpp` (fence 1 → two-phase discovery; `ScanResult` grows a repo tree) [E→rework]; a NEW repo-engine module (eligibility gate, bundle capture, self-verify — no existing home; `git grep` for git/bundle/clone/subprocess machinery in `src` at the blob returns nothing) [A]; `pack.cpp` (repo capture units, single-writer exclusion prefixes, `repos/` member assembly, manifest population) [E]; `manifest.hpp/cpp` (schema act: `Manifest` gains `repos[]`; §2.3 parser replaces `require_empty_array` at :597; serializer replaces :498-500) [E]; `open.cpp` (member-namespace gate :275-279, `ArchivePlan` repos area, clone/apply into the partial dir, report rows) [E]; `error.hpp/cpp` + `envelope.cpp` + `schemas/biv-exit-map.v1.json` (new typed kinds; the transitional row retires DECIDEDLY) [E]; `envelope.cpp:79/:107` + envelope schema (repos rows in summaries) [E]; `main.cpp:253-352` (orchestration order around the session leg) [E]; harness items §4(a-d) [E/A]; the §3 flip set.

**Arm 2 — dirty-state overlay.**
Repo-engine module: classification pass (porcelain v2, ls-files variants, `check-attr` incl. Addendum-B `filter`/`working-tree-encoding`/`ident`, `ls-files -u` unmerged refusal), two-patch capture, forced-payload triggers, pack-time self-verification worktree + oracle [A]; `pack.cpp` integration [E]; open-side patch-apply steps [E on the apply chain]; manifest `capture`/`capture_env`/`forced_payload` fields [A in struct]; Addendum-B fixture rows in the harness [A].

**Arm 3 — nested independent repos.**
Scanner nested-discovery recursion (a repo boundary must keep recursing for nested repos — sealed §1.1) [rework of the Arm-1 walk]; leaves-first capture ordering in pack; parents-before-children apply ordering in open; per-repo outcome isolation in report rows [E surfaces, A logic].

**Arm 4 — submodules.**
Classification `git ls-files -s` gitlink test; per-submodule eligibility against effective config; `.gitmodules` handling; absorbed-gitdir capture; restore chain per A §A3 + B3 (bundle-before-URL, recorded-sha checkout, `update-index --cacheinfo`); the FX-D-OFFLINE hostile-image row under the offline fence [all A; rides Arm 1-3 surfaces].

**Arm 5 — quarantine/invariants closure.**
Quarantine mechanics + inventory (`.biv/quarantine/`, ApplyReport rows) [A]; `.git/info/exclude` write + `ExcludeWriteFailed` advisory + root-not-repo row (§2.6) [A]; cross-config hazards §2.4 [A]; collision-table completion; §5 determinism classes asserted over the full matrix; spec-§10 fixture matrix green [harness E, rows A].
Pack-side `.biv` exclusion already exists (`scan.cpp:140-142`) [E].

**Cross-cutting every arm (bind, already positioned):** shallow never-refuse (D4) shapes the eligibility/bundle module from Arm 1; promisor HELD (`PromisorSourceOffline` offline, `GIT_NO_LAZY_FETCH` online — sealed §A5) same module; offline zero-git/zero-network (D2) constrains every restore step Arm 1 adds; `.bivignore`-only exclusion (E) is already how scan behaves; single-writer §1.2; no host-store surface.

### Collision surfaces with `s4-floor` (beyond the already-named `manifest.cpp`)

1. **`src/cli/main.cpp:253-352`** — one function orchestrates payload restore (`execute_open`, matrix inserts the repo step) and the session leg (`run_session_leg`, floor's R-VF surface). Serialize or partition.
2. **`src/core/support/error.hpp/cpp` + `src/core/report/envelope.cpp` exit map + `schemas/biv-exit-map.v1.json` + `tests/test_envelope.cpp:140-185`** — ONE closed enum, one exit map, one row-count-pinned test; matrix adds repo kinds while floor's R-VF.3 `staged`→`session_install_failed` mapper correction (`sessions.cpp:53-79` `kind_for_row`) changes row semantics. The closed-count assert (`test_envelope.cpp:180`) makes concurrent edits collide by construction.
3. **`tests/test_envelope.cpp:446-…` frozen open-envelope oracle** — matrix adds repos rows to the same byte-golden floor's session-row work edits; one recapture decision, not two.
4. **`schemas/biv-json-envelope.v1.schema.json`** — both pairs extend it.
5. **`harness/bivharness/manifest.py` + `harness/schemas/manifest-plaindir-v1.schema.json`** — matrix flips the repos pin; floor's `entry_schema`-2 archive-only marker lands in the same validator + schema (`entry_schema > 1` handling, `test_manifest.py`).
6. **`tests/test_open.cpp` / `tests/test_cli.cpp`** — shared asserting tests over the open verb both pairs modify.
7. **`CMakeLists.txt`** — both pairs add sources/tests (trivial, name it anyway).
8. **`src/core/manifest/manifest.hpp`** — the `Manifest`/`AgentSessionEntry` structs sit in one header (repos field vs archive-only marker).
The charter's sequencing fences (Addendum F before Arm 1's schema act; floor's `manifest.cpp` work after Arm 1's schema act lands) govern 5/8 of these; items 1-3 need explicit sequencing the fences do not yet name.

## 6. Duplicate/already-built gate — 4-bucket per surface

**Instrument for the dead-path sweep:** `git grep -n -i -E 'git|bundle|clone|overlay|eligib|quarantine|submodule' 8981bfd -- src` (all hits are false positives: digit/digest/eligible-sessions) and `git grep -n -E 'popen|fork\(|execv|system\(|subprocess|"git"' 8981bfd -- src` (zero hits).
There is NO dead-pathed, flagged, or partial git-engine code beyond the two fences.

**Arm 1:** PRIMARY_BUCKET: still-open.
still-open: the entire git engine (discovery, eligibility, bundle, schema act, repo restore) is absent by fence, 0% landed.
already-closed: staging atomicity, containment, checksums, plan/execute split, member-read seam (§2) — extend, do not rebuild; scanner walk + prune machinery exists and is reworked, not duplicated.
product-overlapped: none — the session leg is Step-3 property behind the m-2 seam (adjacent, not overlapping).
recommended-next: implement, gated on Addendum F landing first (charter fence 1); golden-harness row and fixture ledger in the same plan.

**Arm 2:** PRIMARY_BUCKET: still-open.
still-open: all classification/two-patch/self-test machinery.
already-closed: none beyond Arm 1's base.
product-overlapped: none.
recommended-next: implement after Arm 1, per package order.

**Arm 3:** PRIMARY_BUCKET: still-open.
still-open: nested discovery + ordering semantics.
already-closed: none (ordering hooks ride Arm 1 surfaces).
product-overlapped: none.
recommended-next: implement after Arm 2.

**Arm 4:** PRIMARY_BUCKET: still-open.
still-open: all submodule semantics.
already-closed: none.
product-overlapped: none.
recommended-next: implement after Arm 3 (strict superset of nested).

**Arm 5:** PRIMARY_BUCKET: still-open.
still-open: quarantine, exclude write, hazards, closure matrix.
already-closed: pack-side `.biv` skip (`scan.cpp:140-142`); staging all-or-nothing (the workspace-level invariant §2.1 already enforced).
product-overlapped: none.
recommended-next: accrete rows from Arm 1 onward; closure pass last, per package.

**Golden harness:** PRIMARY_BUCKET: still-open (for the git rows).
already-closed: the scenario/compare/tolerance substrate (§4) — PROMOTE/extend it; do not build a second harness.
product-overlapped: none.
recommended-next: extend `tolerance-v1.json` + `compare.py` + `fixtures.py` in Arm 1's plan; promote `d-git-restore` shell.

No bucket line above contradicts its recommendation (checked row-by-row).

## 7. Drift check (beyond DR-1/DR-2/DR-3 — report-only)

**No new drift found.** Specifically compared, landed vs sealed:
staging/rename/partial semantics vs contract §2.1 — match (incl. the AD-2 pre-existing-partial refusal and no-adoption rule);
containment vs §2.5 (member paths, symlink-member non-traversal, duplicate refusal) — match for the payload slice;
plan/apply mutation boundary vs §1 — match (`plan_open` performs no writes; the §2.5a case-probe exception is NOT landed — an absence, not a divergence);
prune-beats-fence vs pack-engine §1.1 — match;
member-read replay vs Addendum C M13 — match;
`.biv` pack-side exclusion vs §1.2 — match.
Interface members not yet landed (`inspect`, `detect_partial`, `clean_partial`, the `opts` bag) are Step-4 work, recorded per arm in §5 — absent, not divergent.
DR-2 (`.bvpk-open.partial` spelling) re-confirmed at :624 and not re-litigated.
One classification note for the ledger: fence 2's user-visible refusal kind at open is `IntegrityFailurePreApply` (the :230 wrap), so DR-3's flip changes an integrity-class row, not a ParseError row — worth stating in the ledger so the exit-map delta is decided consciously.

## 8. Planner audit deliverable summary

4-bucket verdict (whole surface): still-open — the five-arm matrix is 0% landed by design fence; already-closed — the §2 payload-restore base and §4 harness substrate, which the arms EXTEND; product-overlapped — none (session leg is seam-bound, not overlapping); recommended-next — proceed to reconciliation, then DESIGN/PLAN for Arm 1 gated on Addendum F (charter fence 1), with the §5 collision list serialized against `s4-floor`.

Boundary contract: not applicable at audit (read-only; no writes produced).

Design recommendation (for the reconciled audit, not a sealed-doc question): Arm 1's schema act must scope FOUR surfaces (fence 1, fence 2, the member-namespace gate, the envelope summaries) — the package names two; and the golden harness lands as an extension of the existing tolerance-table mechanism.

Risks / reject-or-narrow gates:
(1) the member-namespace gate (`open.cpp:275-279`) missing from Arm 1's plan would brick `repos/` members at open despite an opened parser;
(2) the closed-row-count exit-map test + frozen envelope oracle force DECIDED flips — regeneration habits would silently violate the org's oracle rule;
(3) `main.cpp` and the error-enum/exit-map/oracle cluster are matrix×floor collisions the charter fences do not yet sequence (§5 items 1-3);
(4) `compare.py`'s indiscriminate walk asserting `.git` internals would make every Arm-1 row RED for the wrong reason if the tolerance flip is skipped;
(5) FU-1 (symlink-target ruling, top-level/operator) is unruled and touches restore semantics the arms inherit;
(6) R-4.2: `manifest-format.md` §2.3 carries `sparse: null` — keep reserved-and-null, do not delete the seam.

Questions routed to `s4.orchestrator-planner`: none blocking the audit; the §5 collision-sequencing gap (items 1-3) and the FU-1 dependency are flagged for reconciliation.

---

**Instruments, complete list:** `git show 8981bfd:<path>` for every file read; `git grep -n -F` / `-E` at `8981bfd` as quoted inline in §1, §3, §6; no working-tree evidence; no build, no execution (E1 audit).
