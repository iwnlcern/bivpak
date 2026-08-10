# TARGETED CHECK RECORD — R-4.8 carrier second fold at `4c35f0f`

DISPATCH_ID: s4-matrix-arm1-r48-fold2-check
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold2-impl-complete
CANDIDATE_SHA: 4c35f0fec8f845500ef7220e0df323d4924c8265 (branch `s4-matrix/r48-carrier`, LOCAL, unpublished; ONE second-fold commit over `2bc7a078`)
FOLD_DELTA: `git diff 2bc7a078..4c35f0f` = 5 files (production delta confined to ONE hunk of manifest.cpp; four test files)
BASE: 6047ab0311491da5567c99f32b22ff14433fb1d2
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md (rev6, `e653457e…@2c7b887`, approved `231944`)
PRIOR_RECORDS: panel `006144b2…` at `29796bb`; re-check `e6a589a5…` at `2bc7a078`
LEAD: s4-matrix.planner (non-lens — no findings of its own, no re-grading; synthesis only)
DATE: 2026-08-10

PANEL_CHOSEN: team-of-2 owning lenses per the ruled sizing (`224450` step 3: "lead + tests + security"): security (owned F3 and the validator move), test-coverage (owned RF-1/RF-2 and the boundary-row non-vacuousness bar). Correctness was not owed a seat — its prior findings were closed at the re-check and no conformance question was open; the rev6 conformance walk was covered by the security lens's line-for-line check against the approved doc.
PANEL_COMPOSITION: two independent cold read-only subagents (r48-check2-security, r48-check2-tests), each pinned to `4c35f0f`, committed blobs only, dual charter (confirm assigned closures + hunt fold-introduced defects), each instructed to deliver via message. Both pair seats excluded from lenses; this seat non-lens lead. No re-spawn.

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| security | 1 | 0 | 1 |
| test-coverage | 1 | 0 | 1 |

2 spawns = 2 finding-sets + 0 stalls. Both reports delivered to the lead via the agent
mailbox and reproduced below unaltered.

## LEAD PRE-PANEL VERIFICATION (E1, at `4c35f0f`, before spawning)

- One commit over `2bc7a078` (`rev-list --count` = 1); delta exactly the five paths the
  completion report named; helper stayed TU-local so `manifest.hpp` needed no edit
  (disclosed and confirmed).
- `classify_carrier_root` single grammar/root authority, fail-closed default;
  `classify_absolute` a two-line projection; `packer_home_valid` three-term over the
  authority with the old second discriminator deleted. Lead proved the extended/drive
  branch disjointness (drive requires alpha at index 0; extended prefixes start with a
  separator) before spawning.
- Full boundary matrix present (three degenerate extended roots + both 8-byte accept
  controls); §9-14 parity pin test byte-untouched; zero `source_path_flavor` contact.
- RF-1 both halves live (dirs created at test_pack.cpp:232-233 BEFORE the guards;
  falsifier at :245); RF-2 whole-store receipts (sorted list + contents map, both arms).
- T-1's central claim RE-VERIFIED by the lead after the tests report landed:
  `mint_rollout_name` (codex install.cpp:121-128) is wall-clock; the destination path
  embeds stamp + Y/M/D (install.cpp:368-372); the receipt normalizes only the installed
  id. Confirmed fold-introduced nondeterminism.

---

## VERBATIM REPORT — security lens

```
SECURITY LENS — R48 carrier second fold @ 4c35f0fec8f845500ef7220e0df323d4924c8265

VERDICT: pass

My F3 (Medium, structural) is CLOSED. The ruled >4 → >7 tightening lands exactly, in both spellings, on all three surfaces (factory, serialize-collapse, parse-reject). No new findings at any severity. Nothing on the rejection list is present.

=====================================================================
CHARTER 1 — F3 CLOSURE AND THE RULED TIGHTENING
=====================================================================

(a) SINGLE ROOT-LENGTH AUTHORITY, FAIL-CLOSED — CONFIRMED

src/core/manifest/manifest.cpp:445-466 (all line refs at 4c35f0f):

  445  struct CarrierRoot { PathFlavor flavor; std::size_t root_length; };
  450  std::optional<CarrierRoot> classify_carrier_root(std::string_view path)
  451-454  wsl grammar        -> {wsl,     7}
  455-457  extended prefix    -> {windows, 7}
  458-461  drive grammar      -> {windows, 3}
  462-464  leading '/'        -> {posix,   1}
  465      return std::nullopt;            // fail-closed default

Every branch returns flavor and root_length in ONE aggregate initializer. There is no
switch, no ternary, no default-assigned threshold: a sub-form added later CANNOT inherit
a bound, because the only way to leave the function with a length is to write one in the
same return. This is precisely the structural property F3 asked for. The old permissive
`? 4U : 3U` selector in packer_home_valid is gone (deleted at 2bc7a07..4c35f0f).

manifest.cpp:475-479 — packer_home_valid is now a three-term expression over the single
authority: `root && root->flavor == value.flavor && value.path.size() > root->root_length`.
manifest.cpp:470-473 — classify_absolute is a pure projection onto `.flavor`.
manifest.cpp:481-489 — make_packer_home unchanged in this fold; it composes
classify_absolute then packer_home_valid, so it inherits the same single authority.

NO SECOND EXTENDED-PREFIX DISCRIMINATOR IN THE CARRIER PATH. Tree-wide grep for
`\\?\` / `//?/` over src/ and include/ returns exactly three sites:
  - src/core/manifest/manifest.cpp:455   — THE authority (this one)
  - src/adapters/rewrite_common.cpp:53   — rewrite::path_flavor_for's peer; the design
    deliberately rejected direct reuse as circular (manifest cannot include
    rewrite_common) and pins the two together by the §9 test-14 parity table
  - src/core/pack/pack.cpp:256           — path_segments' 4-char prefix STRIP for segment
    matching; a different operation (normalization, not validation), no root length, not
    on the carrier path
Both non-manifest sites are BYTE-UNCHANGED vs BASE 6047ab03 (rewrite_common.cpp does not
appear in `git diff --name-only 6047ab03 4c35f0f`; the pack.cpp diff contains no line
touching either prefix). Neither is a duplicate of the discriminator F3 flagged, which
was specifically the second *root-length* decision inside packer_home_valid.

CarrierRoot and classify_carrier_root live inside the anonymous namespace
(manifest.cpp:439 `namespace {` ... 468 `}  // namespace`). Internal linkage; no new
public API surface; manifest.hpp is byte-unchanged in this fold.

(b) BEHAVIOR-IDENTITY OF THE REORDER — PROVEN, NOT ASSERTED

Old classifier (2bc7a07): 1. wsl  2. windows = (drive-form OR extended-prefix)  3. posix
New classifier (4c35f0f): 1. wsl  2. extended  3. drive  4. posix

Proof in two steps.

Step 1 — the two windows sub-branches are DISJOINT, so their relative order is
unobservable even for root_length. The drive branch requires `carrier_ascii_alpha(path[0])`
(manifest.cpp:458). Both extended prefixes begin with `\` or `/` (manifest.cpp:455),
neither of which is ASCII alpha. No string can satisfy both predicates. Therefore the
old `?4:3` partition of the windows set and the new branch-2/branch-3 partition of the
windows set are the SAME partition, cell for cell — the reorder cannot move any path
between them.

Step 2 — the flavor mapping is pointwise identical. The new branches 2 and 3 both return
PathFlavor::windows, so their union is exactly the old branch 2's disjunction, mapping to
the same flavor. wsl is first in both orderings; posix is last in both orderings. Hence
classify_absolute(p) at 4c35f0f == classify_absolute(p) at 2bc7a07 for EVERY p, including
inputs no test names. Specifically checked adversarial straddlers:
  - `//?/mnt/c/x`  — wsl branch needs starts_with("/mnt/"), index 1 is '/' not 'm' -> fails;
                     extended matches -> windows. Old: wsl fails, disjunction's extended
                     arm matches -> windows. Same.
  - `/mnt/c/x`     — wsl first in both -> wsl (never reaches posix). Same.
  - `\\?/C:\x`     — 4th char is '/' so neither prefix literal matches; path[0]='\' is not
                     alpha so drive fails; starts_with('/') fails -> nullopt in both.
  - `/\?/C:/x`     — falls to leading-'/' -> posix in both.
  - `C:x`, `1:/x`, `mnt/c/x`, `""` -> nullopt in both.

Root-length identity against the OLD packer_home_valid switch:
  posix   old `size > 1`  |  new rl 1 -> `size > 1`   IDENTICAL
  wsl     old `size > 7`  |  new rl 7 -> `size > 7`   IDENTICAL
  windows drive     old `size > 3`  |  new rl 3       IDENTICAL
  windows extended  old `size > 4`  |  new rl 7       TIGHTENED, exactly as ruled (224450)
So the ONLY behavioral delta in the whole fold is the intended one, on the intended cell.
Implementation matches approved design rev6 §3 line for line (branch order, the four
lengths, the nullopt default, the "projection" definition of classify_absolute) —
verified against `git show 2c7b887:docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md`.

(c) THE >7 BOUNDARY, BYTE-EXACT — CONFIRMED

  `\\?\C:\`   7 bytes  ->  7 > 7 false  -> INVALID   (extended drive root, banned)
  `\\?\C:\x`  8 bytes  ->  8 > 7 true   -> valid
  `//?/C:/`   7 bytes  ->  INVALID
  `//?/C:/x`  8 bytes  ->  valid
  `\\?\C:`    6 bytes  ->  INVALID

All five are pinned in tests/test_manifest.cpp:150-155 (make_packer_home factory rows).
The three invalid ones are additionally pinned on the serialize-collapse surface at
tests/test_manifest.cpp:197-203 and on the parse-reject surface at
tests/test_manifest.cpp:266-268 (detail == "packer_home"). Both 8-byte controls are pinned
on the parse-ACCEPT surface at tests/test_manifest.cpp:284-303 — the rejection list's
"missing 8-byte control in either spelling" item is satisfied in BOTH spellings, and the
controls assert the parsed value equals the expected string, not merely that parse
succeeded, so a silently-mangled accept cannot pass them.

My original degenerate set still rejects, unchanged: `""`, `relative/home`, `/`,
`/mnt/c/`, `C:/`, `C:\`, `//?/`, `\\?\` (tests/test_manifest.cpp:145-151). Note
packer_home_valid no longer carries an explicit `!path.empty()` term — it does not need
one: on an empty view, size>=7 fails, both starts_with(literal) fail, size>=3 fails, and
starts_with('/') is false on empty, so classify_carrier_root returns nullopt and the `root &&`
short-circuits. The `""` row on the factory surface and the `"packer_home":""` row on the
parse surface both pin this.

Also confirmed the tightening rejects NOTHING legitimate: any real extended path is at
least `\\?\C:\x` = 8. And there is zero backward-compat exposure — packer_home is
introduced by this very branch (21c6d8c), the branch is unmerged, so no shipped image
carries the field under the older >4 threshold. The parse-side hard ParseError on an
invalid carrier therefore cannot orphan any existing .bvpk.

(d) ENCODED FORMS CONVERGE — CONFIRMED

Validation runs strictly on the DECODED string. manifest.cpp:629-631 pulls the value via
optional_string (manifest.cpp:99-116), which does `element.get(std::string_view)` on the
simdjson DOM — simdjson unescapes into its string buffer, so `\\`, `\u005c`, and any
mixed spelling all reach `std::string{value}` as the same raw bytes. packer_home_valid is
then called on that std::string (manifest.cpp:645-649). The classifier never sees JSON
escape syntax, so there is no encoding level at which a 7-byte extended root can be
smuggled past the length gate. This is the correct side of the decode boundary — the
byte-literal-scan hazard does not apply here. The parse-side controls at
tests/test_manifest.cpp:284-303 exercise the escaped-backslash spelling (`\\\\?\\C:\\x` in
JSON source) and confirm it decodes to the 8-byte `\\?\C:\x`.

=====================================================================
CHARTER 2 — DEFECT HUNT ON THE FOLD DELTA
=====================================================================

Scope verified first: `git diff 2bc7a078 4c35f0f` touches five files, and manifest.cpp has
exactly ONE hunk, `@@ -442,41 +442,40 @@`. Every other byte of manifest.cpp — serialize
(the valid-gated emit at :537-542 and the locked field order), parse (the XOR pairing
check, the flavor remap to detail "packer_home_flavor", the "packer_home" reject, the
repos fence, bivignore, unknown-field tolerance) — is byte-unchanged. No other production
file is touched. Containment surface is exactly the 439-492 region as required.

Classification drift the parity table would miss: NONE. Step 1/Step 2 above is a
total-function argument over all std::string_view inputs, not a table walk, so it covers
precisely the class the parity table cannot see. The parity pin
(tests/test_manifest.cpp:341-350) still holds because classify_absolute's flavor mapping
is unchanged — as the design predicted.

New reachable out-of-range access: NONE. root_length is never used as an index or in any
arithmetic — it appears only on the right of `size() >` at manifest.cpp:478, an unsigned/
unsigned comparison with no subtraction, so no underflow path exists. The indexed reads in
classify_carrier_root are `.at(5)`/`.at(6)` guarded by `size() >= 7U` (manifest.cpp:451-452)
and `.at(0)`/`.at(1)`/`.at(2)` guarded by `size() >= 3U` (manifest.cpp:458-459); `.at()` is
bounds-checked regardless, and the guards mean the throwing path is unreachable, so there is
no new exception escaping into the parser either. `starts_with` on a short or empty view is
well-defined.

Parse-surface / DoS change: NONE. The parser is byte-unchanged. classify_carrier_root is
branch-only, O(1), no loop, no recursion, no allocation (it takes a string_view; the single
std::string construction lives in make_packer_home, unchanged). Worst-case cost per call is
strictly lower than the old code's, which called classify_absolute and then re-ran two
starts_with tests. No unbounded-length concern is introduced — the absence of a length cap on
packer_home is inherited from the previous fold and shared with source_path; out of scope here
and unchanged.

Leak / transport containment: STRENGTHENED, not weakened. The engaged-vs-absent equal-bytes
controls previously compared ONE file (the installed parent .jsonl). They now build a whole-
store receipt — the sorted relative-path LIST plus a path->contents map over every regular
file under the store — and compare both
(tests/test_adapter_claude_install.cpp:566-591, tests/test_adapter_codex_install.cpp:519-545).
That closes a real absence-blind hole: a packer_home value leaking into a sibling file, or
into a FILENAME, was invisible to the old single-file read and is now caught. The
installed-id normalization is applied to the relative path as well as the contents, so the
comparison is not defeated by the id appearing in a name. Helpers and headers check out:
regular_files is defined at test_adapter_claude_install.cpp:123, relative_files at
test_adapter_codex_install.cpp:101, and both files already include <map> and <algorithm>.
tests/test_pack.cpp:245 adds `CHECK(report->agent_sessions.empty())`, which pins that the
per-HOME capture rows stay inert — a control that was previously unstated.

No source_path_flavor semantic contact: parse_path_flavor (manifest.cpp:503-514) and its
"source_path_flavor" ParseError detail are untouched; the carrier's flavor errors still
remap locally to "packer_home_flavor" (manifest.cpp:640-643, unchanged).

=====================================================================
STRONGEST ATTACKS THAT FAILED
=====================================================================

1. Reorder-induced misclassification. Tried to find any input the old classifier called
   windows-via-drive that the new one reaches through the extended branch (or vice versa),
   which would silently swap root_length 3 and 7. Refuted by disjointness: drive requires
   alpha at index 0, both extended prefixes start with a separator. The partition is
   provably identical, so the reorder is a no-op on length as well as flavor.

2. Straddler between wsl and extended. `//?/mnt/c/x` and `/mnt/` variants under the extended
   prefix. The wsl predicate anchors on "/mnt/" at offset 0, so it cannot fire on an
   extended-prefixed path; ordering is unchanged from the old code anyway (wsl first in both).

3. Off-by-one at the new boundary. Probed 6/7/8 bytes in both spellings and confirmed the
   comparison is strict `>` against 7, so 7 rejects and 8 accepts. Also confirmed the old
   `>4` cell is fully gone — no path reaches a 4-valued threshold anywhere in the tree.

4. Escape-level bypass. Attempted to reason a 7-byte extended root past the gate by spelling
   it `\u005c\u005c?\u005cC:\u005c` or with doubled backslashes. Refuted: simdjson unescapes
   before optional_string materializes the std::string, so the validator sees 7 decoded bytes
   in every spelling.

5. Flavor spoofing from a hostile manifest. Claimed `packer_home:"/mnt/c/x"` with
   flavor "posix", and `"/home/x"` with "windows". Both die on the
   `root->flavor == value.flavor` term (manifest.cpp:477) before the length check — an
   attacker cannot hand the adapters a flavor that disagrees with the spelling.

6. Fail-open on an unhandled sub-form. Looked for any path out of classify_carrier_root that
   yields a CarrierRoot without an explicitly written length — a fallthrough, a default-
   constructed aggregate, a designated-init omitting root_length (which would zero it and make
   every non-empty path valid). None exists: all four returns are complete designated
   initializers and the only other exit is nullopt.

7. Containment regression in the receipt rewrite. Checked whether the new whole-store
   comparison could be weaker than the old single-file one — e.g. by comparing only the file
   list, or by normalizing away real differences. It compares both the list and the contents
   map, and normalizes only the installed session id. Strictly stronger.

Residual observation (informational, NOT a finding, no action asked): the engaged-vs-absent
receipt is scoped to the adapter store, so it cannot see a hypothetical write outside the
store. That scope predates this fold and a write outside the store would be a separate and
larger defect; the existing `regular_files(outside).empty()` controls
(test_adapter_claude_install.cpp:940, test_adapter_codex_install.cpp:898) cover that class
independently. Likewise, there is no explicit `\u005c`-spelled parse row; it is unnecessary
because the decode precedes the validator, and adding one would be a nicety rather than a gap.
```

## VERBATIM REPORT — test-coverage lens

```
TEST-COVERAGE LENS — R48 carrier, second fold, head 4c35f0fec8f845500ef7220e0df323d4924c8265 (fold delta 2bc7a078..4c35f0f, BASE 6047ab03). Read-only, judged from committed blobs.

VERDICT: must-fix — one Major fold-INTRODUCED nondeterminism in the codex byte-identity receipt (T-1). Both gated items (F-1, F-2) are otherwise closed non-vacuously, all boundary rows are present at all required surfaces, and the strict-TDD RED claim holds at the bytes. Every disclosed decline is acceptable; two carry caveats I want recorded.

=== FINDINGS ===

T-1 (MAJOR, must-fix) — the reworked codex receipt compares wall-clock-derived FILE PATHS, so the two arms can disagree for reasons unrelated to packer_home.
tests/test_adapter_codex_install.cpp:519-545 at 4c35f0f.

The new receipt puts the store-relative path into both `receipt.files` (line 533) and the key of `receipt.contents` (line 534), and the only normalizer applied to that path is `normalize_id` (line 524), which replaces `result->id_map.front().installed_session_id` and nothing else. But the codex destination path is minted from the wall clock at install time, independently per arm:

  src/adapters/codex/install.cpp:120-128
    RolloutName mint_rollout_name() {
      const uint64_t ms = unix_ms_now();
      const auto tm = gmtime_from_ms(ms);
      return RolloutName{.id = uuidv7_from_ms(ms),
                         .file_stamp = strftime_utc(tm, "%Y-%m-%dT%H-%M-%S"),
                         .year = ..., .month = ..., .day = ...};
    }
  src/adapters/codex/install.cpp:368-372
    const auto path = target.target_store.root / "sessions" / rollout.year /
        rollout.month / rollout.day /
        ("rollout-" + rollout.file_stamp + "-" + rollout.id + ".jsonl");

`install_receipt("engaged", …)` and `install_receipt("absent", …)` each call `install()`, so `mint_rollout_name()` runs twice at two different instants. The uuid part is normalized; the `%Y-%m-%dT%H-%M-%S` stamp and the `sessions/<Y>/<M>/<D>/` directory components are NOT. If the two mints straddle a UTC second boundary, the arms produce e.g. `sessions/2026/08/10/rollout-2026-08-10T12-34-56-<installed-id>.jsonl` versus `...T12-34-57-<installed-id>.jsonl`, and BOTH `REQUIRE(engaged.files == absent.files)` (line 544) and `REQUIRE(engaged.contents == absent.contents)` (line 545, different map keys) fail. A UTC midnight crossing gives the same failure via the date directories.

This is fold-introduced. At 2bc7a078 the codex arm returned only the CONTENT string of the one file located by id-substring; file names were never compared, and the fixture's `"timestamp"` values are literals from `codex_members()`, not re-minted, so content was stable. Widening to a whole-store receipt is the right direction — it just pulled a time-bearing name into the compared structure.

Exposure: the window is the gap between the two mints (tail of arm 1's install + the arm-1 receipt walk + head of arm 2's install), so on a normal build this is a sub-percent intermittent — but CMakePresets.json:33-38 defines an `-fsanitize=address,undefined` preset, and under ASAN/UBSAN that window widens by an order of magnitude. Given this repo's stated standard on test flakiness, I am not willing to pass it. It is a false-RED, not a false-GREEN — it cannot mask a leak — so if master prefers to land and file it, that is a defensible call, but it must be an explicit ruling, not a silent one.

Fix (test-only, keeps the whole-store receipt): normalize the minted stamp alongside the id before the path enters `receipt.files`/`receipt.contents`. The layout is fixed-width — `sessions/YYYY/MM/DD/rollout-YYYY-MM-DDTHH-MM-SS-<uuid>.jsonl` — and this file already parses it by offset at line 664 onward, so an offset-based blanking of the date directories and the 19-char `file_stamp` is idiomatic here. The claude arm needs no such change (see below).

T-2 (LOW) — the pack matrix's env guards now engage, but codex's DEFAULTS tier is still probed on a CWD-relative path for four rows.
tests/test_pack.cpp:232-245 at 4c35f0f; src/adapters/codex/codex.cpp:769-773.

The prescribed fix landed correctly: `create_directories(codex_store)` / `create_directories(claude_store)` at lines 232-233 run BEFORE the `ScopedEnv` guards at 238-240, so `fs::exists(*configured, ec)` is true when `pack()` runs and the env tier engages for both adapters. For claude that is total insulation — `src/adapters/claude_code/claude_code.cpp:300-309` returns from inside the env branch, so `env.home / ".claude"` is never consulted. Codex does not early-return: after appending the env store set it still evaluates `const auto root = env.home / ".codex"` and appends a defaults store if that exists.

`process_env()` (src/core/pack/pack.cpp:245-250) sets `.home` to `path{getenv("HOME")}` with an EMPTY path when HOME is unset — there is no getpwuid fallback — so no row can reach a real `$HOME` store, which is the important half. What remains is that for the `unset` and `empty` rows `env.home` is `""`, making the probe `".codex"` relative to the test process's CWD; the `relative` and `windows-drive` rows probe `relative/home/.codex` and `C:/Users/x/.codex`, also CWD-relative. On a developer machine whose CWD happened to contain `.codex`, codex would walk it.

I rate this LOW rather than gating because the consequences are bounded: `pack()` filters candidates by the source cwd, and the source is a freshly-made `/tmp/biv-pack-…-<pid>/proj`, so a foreign store's sessions cannot be captured; the worst outcome is a false RED (a `validate_directory_no_follow` failure tripping `REQUIRE(report.has_value())`), never a false GREEN. Optional hardening if you want it closed: a `CHECK(!std::filesystem::exists(".codex"))` precondition in the loop, which fails loudly instead of silently walking.

T-3 (LOW) — neither receipt asserts it is non-empty, which is a new vacuity window opened by dropping the liveness precondition.
tests/test_adapter_claude_install.cpp:566-582 and tests/test_adapter_codex_install.cpp:518-537.

The panel asked directly: does anything still fail if the id stops appearing at all? No — nothing. But I do not think that is the real loss, because the liveness of the NORMALIZER is now self-enforcing: `installed_session_id` is a fresh random value per install (`uuid4()` at src/adapters/claude_code/install.cpp:472; `uuidv7_from_ms(unix_ms_now())` at src/adapters/codex/install.cpp:508, over `support::secure_random_bytes`), and it appears in the destination filename in both adapters. If `normalize_id` ever stopped matching, the two arms' file lists would differ and the test would go RED, loudly. So the old `REQUIRE(id_position != std::string::npos)` is genuinely redundant as a normalizer-liveness assert, and dropping it is defensible.

What the old precondition ALSO did, incidentally, was prove the store was non-empty — it read one specific named file. The new form does not. If `install()` ever reported `Outcome::installed` while writing nothing, both receipts would be empty and equal, and both REQUIREs would pass vacuously. The `REQUIRE(result->sessions.front().outcome == installed)` above it is the adapter's own self-report, not filesystem evidence. This is not a suite-level coverage hole — the neighbouring TEST_CASEs (claude 608/642, codex 451/577/664) read installed files directly — but it is a one-line fix inside the TEST_CASE: `REQUIRE_FALSE(receipt.files.empty());` before returning. Recommend, do not gate.

T-4 (NIT) — receipt blind spots worth recording, none of which mask a packer_home leak today.
`receipt.contents.emplace(...)` (claude :581, codex :534) silently DROPS a second entry if two distinct files normalize to the same relative key; `receipt.files` keeps the duplicate, so a divergence would still surface through the file-list compare, but the content of the shadowed file would go unchecked. `regular_files`/`relative_files` (claude :123, codex :101) filter on `is_regular_file()`, so an empty directory created in only one arm is invisible, as are mode/permission differences. And the receipt is scoped to `store`, so a hypothetical leak that wrote OUTSIDE `target.target_store.root` — e.g. to a path derived from the carrier `/Users/packer` — would not be seen. That last one is theoretical at 4c35f0f: writes go through `secure_io::write_batch_no_replace(target.target_store.root, writes)` in both adapters, which confines them.

T-5 (LOW, observation on the product, not the tests) — the tightened extended-root rule is a LENGTH rule, not a STRUCTURE rule.
src/core/manifest/manifest.cpp:450-479. `classify_carrier_root` assigns `root_length = 7U` to anything merely starting with `\\?\` or `//?/`, and `packer_home_valid` accepts on `size > root_length`. That correctly rejects all three degenerate roots, but it also accepts `\\?\zzzz` or `//?/UNCx` (8 bytes, no drive letter, no separator at position 6) as `PathFlavor::windows`. The design's stated requirement is met and this is not a regression — the old rule (`> 4U`) was strictly looser — but there is no row anywhere proving the three bytes after the prefix are actually `X:` plus a separator. If master wants that class covered, the cheap addition is a `FactoryRow{R"(\\?\zzzz)", std::nullopt}` expectation plus the matching predicate tightening. I flag it as an observation and do NOT gate on it; it is outside the fold's dispatched scope.

=== NON-VACUOUSNESS CONFIRMATIONS ===

RF-1 (MF-5 env guards now engage) — CONFIRMED, with the T-2 residual.
Ordering verified at the bytes: `create_directories` for both stores at tests/test_pack.cpp:232-233 precedes `ScopedEnv codex_home` / `ScopedEnv claude_config` at 239-240, which precede `biv::pack::pack(source)` at 242. Both adapters' env tier gates on `fs::exists` of the configured value (claude_code.cpp:302, codex.cpp:763), so both now take the env branch on every one of the seven rows instead of falling through. Claude is fully insulated by its early `return stores;` (claude_code.cpp:308). Codex is not, per T-2. No row can reach a real host store on macOS or in a root-HOME Linux container, because `process_env()` yields an EMPTY home rather than a passwd fallback when HOME is unset (pack.cpp:245-250) and every row overrides HOME — including `degenerate-root`, which probes `/.codex`, not `/root/.codex`. The `wsl-mount` row probes `/mnt/c/Users/x/.codex`, which is a real absolute path on a WSL host but names a placeholder user; low but non-zero.

The per-row `CHECK(report->agent_sessions.empty())` at line 245 is correctly placed and correctly falsifies accidental CAPTURE on every row including the four formerly CWD-dependent ones. I want to be precise about its strength, though: it falsifies capture, not WALKING. A foreign store that got walked would still yield an empty `agent_sessions`, because pack filters candidates by recorded cwd against the fresh tmp source path. It is a genuine negative control — it has no positive arm by construction, since the engaged store dirs are created empty — but it is not a complete answer to "did we touch something we should not have." That is why T-2 remains open at LOW rather than closed.

RF-2 (whole-store receipts) — CONFIRMED as structurally sound, subject to T-1.
Both arms now walk the entire store (`regular_files(store)` claude :567; `relative_files(store)` codex :519), build a sorted relative file list and a full path→content map, normalize the installed id in BOTH the path and the content, and compare both structures (claude :581-582/587-588, codex :533-534/544-545). That is what F-2 asked for.

Can the normalization mask a packer_home divergence? No. `normalize_id` replaces exactly one token — the installed session UUID — with the 14-character `"<installed-id>"`, and the `id_position + 14U` advance is correct (`strlen("<installed-id>") == 14`) and cannot loop, since the placeholder does not contain the uuid. A divergence in a home path such as `/Users/packer` shares no bytes with a UUID and survives normalization intact.

Does the zero-or-more choice weaken the receipt? Not in the direction that matters. The dangerous shape would be normalization that erases a real difference; here the opposite holds — any id spelling the normalizer FAILS to match (escaped, split, re-encoded) leaves the two arms' random UUIDs unequal and drives the test RED. See T-3 for the one thing that was genuinely lost.

I also confirmed the receipts are otherwise deterministic on the claude side: both installs write only planned member files via `write_batch_no_replace`, with no config/history/sqlite side-writes, and the claude destination path (`src/adapters/claude_code/install.cpp:152-173`) is built from the project key and the installed id with no time component. The fixture line substituted at claude :537-543 carries no `uuid`/`parentUuid`/`leafUuid`/`toolUseID` field, so `minted_message_uuid_pairs` (install.cpp:267-273) mints nothing and no unnormalized random value enters the content. The claude arm is clean.

BOUNDARY ROWS — CONFIRMED at all required surfaces.
All three degenerate extended roots are present and expected to REJECT at each of the three surfaces, and all three surfaces route through the same `packer_home_valid` predicate (factory at manifest.cpp:487, serialize at :537, parse at :646), so the coverage is real rather than three views of one call:
 - factory: tests/test_manifest.cpp:153-155 — `\\?\C:\`, `//?/C:/`, `\\?\C:` all `std::nullopt`.
 - serialize-collapse: tests/test_manifest.cpp:197-203 — all three assert `serialize(...).find("packer_home") == npos`.
 - parse: tests/test_manifest.cpp:266-268 — all three assert `REQUIRE_FALSE(parsed.has_value())` and `error().detail == "packer_home"`.

Both 8-byte root-plus-one accept controls are present at factory (tests/test_manifest.cpp:156-157, `\\?\C:\x` and `//?/C:/x`, each expected `PathFlavor::windows` and each additionally asserting `packer_home_valid`) and at parse (tests/test_manifest.cpp:284-303, both expected to parse and to equal the exact 8-byte value). They are absent from the serialize-collapse surface, which I judge acceptable: the predicate is shared, so factory and parse already pin it. A misimplementation that required `> 8` instead of `> 7` — the exact off-by-one being controlled for — goes RED at four independent assertion sites.

I decoded the escaped JSON literals by hand rather than trusting them. `"\"packer_home\":\"\\\\\\\\?\\\\C:\\\\\","` is the JSON text `"packer_home":"\\\\?\\C:\\"`, which decodes to the 7-byte `\\?\C:\`; the `\\?\C:` row decodes to 6 bytes; the accept control decodes to the 8-byte `\\?\C:\x`. All correct. I also counted the initializers of `std::array<std::string, 16>` at tests/test_manifest.cpp:252-269 — exactly 16, so the 13→16 bump is not hiding a truncation or a default-constructed empty row.

I checked for collateral: `classify_absolute` has exactly one production consumer (`make_packer_home`, manifest.cpp:482), the refactor preserves its mapping for every input (the extended-prefix test simply moved ahead of the drive-letter test, and no string can match both), and the posix/wsl/windows-drive thresholds are byte-identical to the old rule (`> 1`, `> 7`, `> 3`). `tests/test_manifest.cpp` "classify_absolute covers every grammar branch" still holds unchanged. The only `\\?\`/`//?/` literals elsewhere in tests (test_adapter_claude_collect.cpp:196, test_pack.cpp:703) are `cwd` values that never reach `packer_home_valid`. No other test's expectations move.

TDD-RED CLAIM — CONFIRMED at the bytes.
At 2bc7a078 the predicate was `value.path.size() > (starts_with(R"(\\?\)") || starts_with("//?/") ? 4U : 3U)`, and `classify_absolute` there returned `PathFlavor::windows` for any `\\?\`/`//?/` prefix. So `\\?\C:\` (7 > 4), `//?/C:/` (7 > 4) and `\\?\C:` (6 > 4) were all VALID at the old head. Each of the three new rows therefore could not have passed there: the factory rows expect `std::nullopt` but would have received an engaged value; the serialize rows expect the key absent but it would have been emitted; the parse rows expect `REQUIRE_FALSE(has_value())` but parse would have succeeded. Nine genuinely RED assertions at the predecessor. The two 8-byte accept controls were already green at 2bc7a078 (8 > 4) — they are controls, not RED rows, and the implementer characterized them as such correctly.

=== RULING ON THE DISCLOSED DECLINES ===
All five were nit tier at the previous re-check and none hides a gating gap. Two carry caveats.

1. Sibling temp roots (declined) — ACCEPTED, no gap. Both arms are subdirectories of one `root` (`store = root / arm`), each receipt is computed relative to its own store, and writes are confined to `target.target_store.root` by `write_batch_no_replace`. Sharing `workspace` across the arms is not merely harmless, it is REQUIRED: the claude project key derives from the workspace path, so a per-arm workspace would make the relative paths differ by construction and destroy the comparison.

2. Named placeholder constant (declined) — ACCEPTED, no gap; latent maintenance hazard only. The magic `14U` matches `strlen("<installed-id>")` in both copies today. It is duplicated across two files, so a future edit to the placeholder text that misses one `14U` would silently mis-advance the scan. A `constexpr std::string_view` plus `.size()` removes the hazard whenever this code is next touched.

3. Full id_map normalization (declined) — ACCEPTED at 4c35f0f, but this is where I want the record to be explicit: `children.clear()` is STILL load-bearing, and the fold made it MORE load-bearing than it was. Both receipt tests clear children (claude :548, codex :499), which drives `id_map.size() == 1`, so the single normalized token covers every random value in the store. Under the old one-file compare, a child's freshly minted id was invisible because the child's file was never read. Under the whole-store receipt, a restored child would put an unnormalized `uuid4()` (claude) or `uuidv7_from_ms` (codex, minted at install.cpp:511) into a compared file and its name, and the test would go RED for a reason having nothing to do with packer_home. So the decline is correct today and a trap tomorrow. Normalizing the whole `id_map` is the same one-loop change that fixes T-1's class — per-install nondeterministic tokens should ALL be normalized, not just the primary id — and I would take both together.

4. HOME-flavor precondition (declined) — ACCEPTED, no gap. The per-row assertion at tests/test_pack.cpp:250-256 binds BOTH fields exactly: `expected` is built as `PackerHome{.path = *home_value, .flavor = *row.expected_flavor}` and compared with `REQUIRE(manifest->packer_home == expected)`, so a flavor misclassification fails the row without any separate precondition. I checked the ternary for a null-deref trap: `*home_value` is evaluated only in the engaged branch, and all three engaged rows (`absolute-posix`, `wsl-mount`, `windows-drive`) have a non-null `home_value`. Safe.

5. 13b TEST_CASE split (declined) — ACCEPTED, cosmetic. Every row in the malformed-values loop carries `CAPTURE(injected)`, and the two positive controls that follow (the `\\?\C:\Users\x` control at :270-278 and the new 8-byte loop at :284-303) carry their own `CAPTURE`, so a failure is fully attributable without the split. Keeping the negative rows and their positive controls in one TEST_CASE arguably reads better, since the controls exist precisely to bound the negatives.

=== SUMMARY OF WHAT MUST CHANGE ===
One edit gates my pass: tests/test_adapter_codex_install.cpp:519-537 must normalize the minted rollout timestamp (the `%Y-%m-%dT%H-%M-%S` stamp and the `sessions/<Y>/<M>/<D>/` components) in addition to the installed id, before the path enters `receipt.files` and the `receipt.contents` key. I recommend, but do not gate on, folding in the whole-`id_map` normalization from decline 3 and the `REQUIRE_FALSE(receipt.files.empty())` from T-3 in the same pass, since all three are the same "normalize every per-install nondeterministic token, and prove the receipt is non-empty" change. T-2 and T-5 I am content to see routed as residuals.
```

---

## LEAD SYNTHESIS

Per-lens verdicts (bare):
- security: pass (zero findings at any severity; one informational observation)
- test-coverage: must-fix (1 Major fold-introduced; 3 Low; 1 Nit)

**CHECK VERDICT: REVIEW-FOLD required — a THIRD, minimal, TEST-ONLY fold of exactly one
gating Major plus two same-class riders.** Everything this fold was dispatched to do, it
did, and both lenses confirm it non-vacuously: the ruled `>7` tightening lands byte-exact
on all three surfaces in both spellings with the strict-TDD RED shape verified at the
predecessor head; security's F3 closes with the fail-closed single authority and a
TOTAL-FUNCTION behavior-identity proof for the reorder (covering exactly the class the
parity table cannot see); RF-1 engages on every row; RF-2 is a genuine whole-store
receipt that both lenses judge STRICTLY STRONGER than what it replaced. The production
bytes are clean — the sole gating item is a defect in a TEST the fold itself rewrote.

### The third-fold set (test-only; no ruling owed — no sealed contact, pair scope)

**TF-1 (GATES — tests T-1, Major, fold-introduced).** The widened codex receipt compares
wall-clock-derived FILE PATHS: `mint_rollout_name` stamps `%Y-%m-%dT%H-%M-%S` and
`sessions/Y/M/D/` per install, two installs run per test, and only the installed id is
normalized — so arms straddling a UTC second (or midnight) boundary diverge on both
compared structures. Intermittent false-RED, window widened by an order of magnitude
under the ASAN/UBSAN preset. The lens offered "land and file it" as a defensible
explicit ruling; the LEAD DECLINES that arm on the operator's standing near-picky
flakiness standard — the fix is one test file. Fix: normalize the minted stamp and date
components alongside the id before the path enters `receipt.files`/`receipt.contents`
(the fixed-width layout is already offset-parsed in the same file).
**TF-2 (rider — decline-3/T-1 same class).** Normalize the whole `id_map`, not just
`front()` — per-install nondeterministic tokens should all be normalized; also defuses
the now-more-load-bearing `children.clear()` trap for future ID-bearing fixtures.
**TF-3 (rider — T-3).** `REQUIRE_FALSE(receipt.files.empty())` in both receipts — the
one thing genuinely lost with the old liveness precondition (an installed-while-writing-
nothing outcome would compare two empty receipts equal). Optional alongside: the named
`kIdPlaceholder` constant (tests decline-2) since the same lines move.

The riders' safety cell is explicitly charged to the post-fold verification: widening
normalization to time/uuid tokens must be shown UNABLE to mask a carrier divergence
(`/Users/packer` shares no bytes with either token class — verify at the bytes).

### Post-fold verification sizing

Lead + tests lens ONLY at the new head. Security is not re-convened: no production byte
moves, its pass has no open cell, and the one new question (normalization masking) is
the tests lens's own finding class — assigned above. Per the after-fold-ins rule, the
check is sized to a one-to-two-test-file delta.

### Routed as candidate residuals / observations (master's registry, NOT this fold)

- **Tests T-2 (Low):** codex's DEFAULTS discovery tier still probes a CWD-relative
  `.codex` on the four HOME-degenerate rows (claude is insulated by its env-tier early
  return; codex appends the home-derived default unconditionally). Bounded: worst case
  is a loud false-RED, never capture (cwd filtering) — the lens's optional
  `!exists(".codex")` precondition is noted for any future hardening pass.
- **Tests T-5 (Low, product observation, outside dispatched scope):** the extended rule
  is a LENGTH rule, not a STRUCTURE rule — `\\?\zzzz` (8 bytes, no drive) is accepted as
  windows. Conforms to the ruled design (the old rule was strictly looser); if the
  registry wants the class covered, the cheap shape is a structural check that the three
  bytes after the extended prefix are `X:` + separator, plus one FactoryRow. Candidate
  registry row; NOT folded on pair authority (it would amend the ruled grammar again).
- **Security informational:** the receipt is scoped to the adapter store by design;
  writes outside the store are independently covered by the existing
  `regular_files(outside).empty()` controls.
- **Tests T-4 (Nit, recorded):** `contents.emplace` drops a shadowed duplicate key
  (list compare still surfaces the divergence); `is_regular_file` filtering is blind to
  empty dirs and modes.

### Rejected / weak: none — every finding cites file:line at `4c35f0f`; the lead
re-verified the gating finding's central claim at the sealed blobs before synthesis.

### Disposition

The third fold (TF-1..TF-3, test-only, one commit) is dispatched on pair authority in
parallel with this record — no orchestrator ruling is owed (no sealed-behavior contact,
no design change, no grammar movement) and the flake-fix arm is chosen over the
land-and-file arm per the operator's standing standard. Then lead + tests verification
at the new head; on ITS pass the Step-3.8 completion / publication-token path opens and
the two human lenses route (panel-before-lenses). The branch stays LOCAL; publication by
separate token; the release hold is ABSOLUTE.
