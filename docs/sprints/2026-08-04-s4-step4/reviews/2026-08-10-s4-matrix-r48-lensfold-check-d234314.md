# TARGETED RE-CHECK RECORD — R-4.8 lens-fold at `d234314`

DISPATCH_ID: s4-matrix-arm1-r48-lensfold-check
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-lensfold-impl-complete
CANDIDATE_SHA: d2343147243b9cc65ce94c853b49f5ecac1227ae (branch `s4-matrix/r48-carrier`, ONE test-only commit over the published head `2341667`; remote/PR NOT updated)
FOLD_DELTA: `git diff 2341667..d234314` = exactly the 4 dispatched test files; ZERO production bytes
PLAN: lens-fold PLAN (`e1837e21…`, approved `074840` with three binding proof pins)
PRIOR_RECORDS: panel `006144b2…`; re-check `e6a589a5…`; check `c1e7eb8d…`; verification `4f90641f…`; the human-lens carry-down `071834`
LEAD: s4-matrix.planner (non-lens; synthesis only)
DATE: 2026-08-10

PANEL_CHOSEN: single owning lens per the approved sizing (lead + tests). PANEL_COMPOSITION: one independent cold read-only subagent (r48-lensfold-check-tests), pinned to `d234314`, committed blobs only. Both pair seats excluded; no re-spawn. The lens disclosed and corrected its own method error mid-pass (a first working-tree grep landed on main; every reported fact was re-read from the `d234314` blobs).

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| test-coverage | 1 | 0 | 1 |

1 spawn = 1 finding-set + 0 stalls. Report delivered via the agent mailbox, reproduced below unaltered.

## LEAD PRE-PANEL VERIFICATION (E1, at `d234314`, before spawning)

- One commit; delta exactly the four dispatched paths; 16 `pack(source)` sites vs 18
  fixture references; the decoy falsifier block real (ambient HOME at a decoy `.codex`
  with a genuine session; `require_store_roots_under` + `none_of` on the report).
- V1/V2/V3/O1/BR1 all present at the expected sites. The lead did NOT catch Finding 1
  pre-panel — the guard LOOKED live at the grep level; the lens's substring analysis
  (workspace-name and immutable-key false witnesses) is exactly why the re-check exists.
- Finding 1's two false witnesses RE-VERIFIED by the lead at the bytes after the report
  landed: `workspace = root / "workspace"` (path contains `/ws`), the fixture key
  `"/ws/proj"` immutable, the guard a bare `find("/ws")` over content.

## VERBATIM REPORT — test-coverage lens

```
TEST-COVERAGE LENS — R48 lens-fold re-check at d2343147243b9cc65ce94c853b49f5ecac1227ae (one test-only commit over 2341667). Read-only; all reads from committed blobs via `git show <sha>:<path>` and `git diff 2341667..d234314`.

VERDICT: must-fix

Delta confirmed exactly as scoped: tests/test_pack.cpp, tests/test_adapter_claude_install.cpp, tests/test_adapter_codex_install.cpp, tests/test_manifest.cpp. Zero production bytes (`git diff --name-status 2341667..d234314` returns four `M` rows, all under tests/). No TEST_CASE added or removed anywhere in the delta.

Note on method: my first pass grepped the working tree, which sits on main at 70089c5 and does not contain the carrier at all. Every production fact below was re-read from the d234314 blobs (`git grep -n ... d234314 -- src`). Nothing in this report is measured against main.

================================================================
FINDING 1 — CRITICAL — the pin-2 non-vacuity guard is itself unfalsifiable
================================================================
tests/test_adapter_claude_install.cpp:626-630
tests/test_adapter_codex_install.cpp:601-605

    // The engaged carrier is a prefix of fixture bytes, so a future
    // carrier-conditional content rewrite must make these arms diverge.
    REQUIRE(std::ranges::any_of(engaged.contents, [](const auto& entry) {
      return entry.second.find("/ws") != std::string::npos;
    }));

The mechanical parts of the pin are satisfied: the assertion runs on `engaged.contents`, which is exactly the map compared at `REQUIRE(engaged.contents == absent.contents)`, on the engaged arm, after `normalize_minted_ids`. The problem is that the predicate cannot fail, for two independent reasons, and neither reason has anything to do with the carrier.

False witness A — the restore workspace directory name. Both tests declare `const auto workspace = root / "workspace";` (claude:559, codex:527). The installer rewrites the session cwd from the record's `original_path` "/ws/proj" (claude_entry at claude:212, codex_entry at codex:171) with `relpath_key = "."` to the workspace root, so the installed content contains the absolute workspace path verbatim. That is asserted directly by the sibling tests that use the identical fixture line: test_adapter_claude_install.cpp:670 `CHECK(installed.find(workspace.generic_string()) != std::string::npos)` and test_adapter_codex_install.cpp:651 (same check), plus codex:517. The generic string of `root/"workspace"` contains the substring "/workspace", which contains "/ws". So `find("/ws")` succeeds on the rewritten cwd of every arm, in every run, whatever the carrier is and whatever the fixture carries.

False witness B — the immutable JSON key. The crafted main/parent artifact begins `{"/ws/proj":"key-must-not-change",...}` (claude:563, codex:531). Keys are sealed as never-rewritten — that is the whole content of test_adapter_claude_install.cpp:668 and test_adapter_codex_install.cpp:649. A carrier-conditional rewrite of string values can never touch this key, so its survival cannot witness that the arms would diverge. It nonetheless satisfies `find("/ws")`.

Decoupling defect on top of that: the search string "/ws" is a hard-coded literal, not derived from the `PackerHome` value handed to the engaged arm at claude:622-624 / codex:597-599. Change the engaged carrier to `PackerHome{"/zz", posix}` and leave everything else alone — nothing in the fixture is then carrier-prefixed at all, yet the guard still searches for "/ws" and still passes on both false witnesses. That is the cleanest executable falsifier of the guard, and I recommend the implementer run it rather than take my trace on faith (I am read-only and did not build).

To answer the pin's own adversarial question — "could the /ws prefix accidentally match something normalization inserts?" — normalization is not the culprit. `normalize_minted_ids` only substitutes ids (claude:103-112), and codex's `normalize_rollout_clock` rewrites the relative path, never the content. The accidental match comes from a source the pin did not enumerate: the restore workspace directory is literally named "workspace".

What the guard was supposed to establish is true of the *input*: the fixture does hand the installer a carrier-rooted value ("\/ws\/\u0070roj" decoding to "/ws/proj"), so a carrier-conditional rewrite added during install would have something to act on. The guard measures the *output*, where that value has already been rewritten away and only the two false witnesses remain. Post-install there is no compared byte that a carrier-conditional value rewrite could change — the record's children are cleared (claude:569, codex:540) so only the crafted main/parent artifact installs, and its single path value is the cwd.

Suggested repair (both files), asserting the property on the artifact that actually carries it and coupling it to the carrier constant:
  - hoist the engaged carrier to a named constant, e.g. `constexpr std::string_view kEngagedCarrier = "/ws";`
  - assert the record's origin is a strict path-prefix match: `REQUIRE(record.original_path.starts_with(std::string{kEngagedCarrier} + "/"));`
  - assert the input member bytes carry it in the encoded form the installer will see: `REQUIRE(text(members.at(main_artifact())).find("\\/ws\\/") != std::string::npos);` (parent_artifact() for codex)
Both fail the moment the fixture stops carrying carrier-prefixed bytes, and neither can be satisfied by the workspace directory name or by the immutable key. If a post-install check is also wanted, it must be boundary-aware and must exclude `workspace.generic_string()` from the searched text.

This is the same shape as the defect the fold was convened to close. Human Lens B's original finding was that "/Users/packer" appeared in zero fixture content bytes, making the receipts vacuous. Changing the carrier to "/ws" did make the *input* carrier-relevant — that half of V1 landed — but the guard written to prove it cannot fail, so the receipts are still not demonstrably non-vacuous.

================================================================
FINDING 2 — MEDIUM — the decoy falsifier has no explicit zero-row expectation
================================================================
tests/test_pack.cpp:263-270

    const auto report = biv::pack::pack(source);
    REQUIRE(report.has_value());
    require_store_roots_under(*report, root);
    CHECK(std::ranges::none_of(report->agent_sessions, ...));

`require_store_roots_under` loops over `report.agent_sessions` (tests/test_pack.cpp:208) and `none_of` is likewise a universally-quantified claim. On an empty vector both are trivially true. The expected post-fixture state here IS zero rows — with HOME, CODEX_HOME, CODEX_SQLITE_HOME and CLAUDE_CONFIG_DIR all pinned at non-existent paths beneath `root`, both adapters return an empty store list — so the block's entire post-condition is two vacuous quantifiers. It therefore cannot distinguish "the decoy is unreachable" from "discovery returned nothing for an unrelated reason".

Every other row-count site in this file states the count explicitly (`CHECK(report->agent_sessions.empty())` at :323 and :371, `REQUIRE(... .size() == 1)` at :436, :558, :712, :816, :861, :891). The falsifier block is the one exception, and it is the block the pin governs. Fix is one line after :266: `CHECK(report->agent_sessions.empty());`.

================================================================
PER-PIN CONFIRMATIONS
================================================================

PIN 1 — HERMETICITY (H1/H2). CONFIRMED, with one bounded residual (Finding 5 below).

Call-site walk. `biv::pack::pack(` appears at exactly 16 sites in tests/test_pack.cpp at d234314: lines 263, 319, 366, 432, 465, 516, 530, 554, 621, 649, 676, 708, 764, 812, 857, 887. Every one is preceded, in the same scope, by a `ScopedPackDiscoveryEnv` construction (260, 317, 364, 430, 462, 513, 528, 552, 619, 647, 674, 706, 762, 810, 855, 885). No pack call inherits any of the four variables from the runner. The count matches the completion report's claim of 16.

`require_store_roots_under` follows all 11 sites that produce a successful report (266, 322, 369, 435, 467, 557, 711, 767, 815, 860, 890). The five it does not follow are the five error-path sites, each asserting `REQUIRE_FALSE(report.has_value())` at :517, :531, :623, :651, :678 — there is no report to walk. So "invoked after EVERY successful pack report" holds exactly.

Four-variable closure is complete and I verified it against production rather than assuming it. `git grep -n 'getenv("' d234314 -- src`, excluding src/cli, yields exactly: CLAUDE_CONFIG_DIR (claude_code.cpp:301, install.cpp:322), CODEX_SQLITE_HOME (codex.cpp:726), CODEX_HOME (codex.cpp:763, install.cpp:185), HOME (pack.cpp:246), and PATH (probe.cpp:316). pack.cpp contains no reference to probe at d234314, so PATH is not a pack input. The four variables the fixture owns are therefore the complete set of environmental inputs to pack discovery. `packer_home_carrier(env.home)` at pack.cpp:676 confirms the manifest carrier is derived from the same pinned HOME.

Defaults beneath the temp root: `isolated_pack_discovery_env` (tests/test_pack.cpp:179-187) places all four under `root` — root/home, root/claude, root/codex, root/codex-sqlite. Knobs: `PackDiscoveryEnvValues` fields are `std::optional<std::string>`, so callers can override to any value or to `std::nullopt` for a genuine unset; `ScopedEnv` calls `unsetenv` on nullopt (tests/test_pack.cpp:150). The rows table exercises unset, empty, relative, "/" and both foreign flavors through that knob (:281-299, :314).

Restore symmetry and unwind safety: `ScopedPackDiscoveryEnv` holds four `ScopedEnv` members (tests/test_pack.cpp:199-202) which capture the prior value in their constructors and restore-or-unset in their destructors (:144-160). Members destruct in reverse declaration order, and the four names are pairwise distinct, so there is no aliasing and no ordering hazard. `ScopedEnv` is non-copyable and non-movable, so no double-restore is constructible. If a Catch2 assertion throws inside a guarded block, the guards unwind normally and the environment is restored; the `remove_all` calls at the end of each block are skipped on failure, but `make_tmp` (:32-38) does `remove_all` before `create_directories`, so leaked temp trees cannot poison a later run.

Nesting in the decoy block is correct: `ambient_home` (:259) is constructed before `discovery_env` (:260), so `discovery_env.home_` captures decoy_home as its prior value and restores it on scope exit, after which `ambient_home` restores the runner's real HOME. Symmetric in both directions.

Two-tier codex intent survives the knobs. "pack carries duplicate-store warning and A5 pick into the envelope" (:684) sets `env_values.codex_home = env_store` (root/"env-codex") at :705 and leaves HOME at the isolated default root/"home"; `default_store` is `root/"home"/".codex"` (:688). Both tiers are therefore still populated — env tier from CODEX_HOME, defaults tier from `env.home / ".codex"` (codex.cpp:762-772 at d234314) — and the A5 assertion that the newer home-tier store wins (:713-714) is unchanged. Intent intact.

PIN 1 — CONSTRUCTED DECOY FALSIFIER. Genuine by construction; I traced it rather than executed it.

RED-before: `write_agent_session(decoy_store, source, "codex", ...)` (:257-258) writes `decoy_home/.codex/sessions/2026/08/06/rollout-2026-08-06T01-00-00-<id>.jsonl` with `"cwd"` set to the packed `source` and `cli_version` "0.142.5". Codex `discover()` at d234314 (src/adapters/codex/codex.cpp, the `const auto root = env.home / ".codex"` tier) appends that home tier unconditionally whenever the directory exists and differs from the env root — it is not gated behind the absence of CODEX_HOME. With `ambient_home` in force and `ScopedPackDiscoveryEnv` removed, `env.home` is decoy_home, `decoy_home/.codex` exists, `append_store_set` builds `sessions_root = decoy_home/.codex/sessions`, and the layout is byte-identical to the one the Task-6 tests rely on for successful discovery through the env tier (the same `write_agent_session` helper feeds :359 and :425, and :436 asserts a row comes back). Version 0.142.5 clears the 0.142 floor, per the P2 case at :406. So the decoy row is discovered, `provenance.store_root` is decoy_store, and both `require_store_roots_under` and the `none_of` fail. The SITREP's "exit 42, one failed case" is consistent with that; I could not execute it and do not certify the exit code, only the mechanism.

GREEN-after and unreachable by construction: post-fixture the four pinned variables point at non-existent paths beneath `root`, decoy_home is reachable through none of them, and the four are the complete input set (see closure above). `sqlite_locator` cannot escape either — it reads CODEX_SQLITE_HOME first, and its fallback `config_string(root / "config.toml", "sqlite_home")` is rooted at the pinned codex root. So the decoy is unreachable by construction, not by accident. The one gap is that the post state is not asserted (Finding 2).

PIN 1 — require_store_roots_under soundness (tests/test_pack.cpp:205-218). Sound.
- Weakly-canonical containment: both sides go through `weakly_canonical`, so the macOS /var vs /private/var symlink is resolved identically on both. `make_tmp` already returns `fs::canonical(base)` (:37) and every store path is built from that canonical root, so the operation is idempotent for the mac cases. The two /mnt/c cases (:826) build `root` without canonicalising, but since both arguments are normalised by the same call the comparison still holds; those cases SKIP on macOS anyway (:791, :823).
- Non-empty: `lexically_relative` returns an empty path when the two paths have different roots, and `REQUIRE_FALSE(relative.empty())` catches that.
- Self: exact equality yields ".", caught by `REQUIRE(relative != ".")`.
- Escape: any sibling or ancestor yields a first component of "..", caught by `REQUIRE(*relative.begin() != "..")`.
- Ordering is safe: `REQUIRE` throws on failure, so the `*relative.begin()` dereference is unreachable when the path is empty. Had these been CHECK rather than REQUIRE, that line would be UB on an empty path. They are REQUIRE. Worth preserving deliberately if anyone later relaxes them.
- `REQUIRE_FALSE(relative.is_absolute())` is belt-and-braces; `lexically_relative` never returns an absolute path. Harmless.
- `CAPTURE(store_root, canonical_root, relative)` gives usable diagnostics on failure.

PIN 1 — zero-row expectations. Explicit at :323 and :371-372. NOT explicit in the decoy block — Finding 2.

PIN 2 — CARRIER NON-VACUITY (V1). NOT CONFIRMED. Both engaged arms do now use `PackerHome{"/ws", posix}` (claude:622-624, codex:597-599), and the direct pre-equality assertion is present, on the compared normalized content, in the engaged arm. But it cannot fail — Finding 1. One thing that did land correctly: "/ws" is a valid packer home, and BR1's new `FactoryRow{"/x", posix}` row (test_manifest.cpp:142) is exactly what pins that a single-component absolute posix path is accepted by `make_packer_home`, so the engaged arm is not silently a no-op carrier. That coupling is good work; the guard above it is the part that does not hold.

PIN 3 — ID-MAP SHAPE (V3). CONFIRMED.
`IdMapEntry` at src/adapters/adapter.hpp:181-186 (d234314) has exactly four members: `agent`, `image_session_id`, `installed_session_id`, `children` (vector<pair<string,string>>). `IdMapShape` (claude:572-578, codex:543-549) captures `agent`, `image_session_id`, and `image_children` built by transforming `children` to `child.first` in order (claude:598-607, codex:570-579). Excluded: `installed_session_id` and `children.second` — both minted per install, both correctly out. No stable member is accidentally excluded: entry count is compared via the vector comparison itself plus the explicit size REQUIRE, `agent` and `image_session_id` are in, and children order is preserved because a vector is used rather than a set. `bool operator==(const IdMapShape&) const = default` gives the correct memberwise compare, and `std::vector<IdMapShape>` comparison then covers count and order. The carve-out is stated in the comment at claude:631-632 / codex:606-607 ("Minted installed ids are normalized across arms by construction, so these byte-identity checks deliberately exclude id-only divergence"), which is accurate. `REQUIRE(engaged.id_map_shape.size() == absent.id_map_shape.size())` is redundant with the equality on the next line (and both are pinned to 1 by the earlier `REQUIRE(result->id_map.size() == 1U)`), but it produces a better first failure message; harmless, no action.

V2 — REQUIRE(emplace(...).second). CONFIRMED, both receipts: claude:614-615, codex:587-588. `receipt.files.push_back(relative)` precedes the `std::move(relative)` into `emplace` in both files (claude:613 before :614, codex:586 before :587), so no use-after-move. The comma inside `emplace(...)` is parenthesised and does not break the REQUIRE macro. This is a real tightening for codex specifically, where `normalize_rollout_clock` collapses the timestamp in the relative path (codex:58-72) and could in principle collapse two rollout files onto one key — previously `emplace` would have silently dropped the second and the receipt would have compared fewer files than the store held. Only one session installs here, so it does not fire today, but the guard is correctly placed.

O1 — ORACLE comment. CONFIRMED. tests/test_manifest.cpp:93-94:
    // ORACLE RULE: captured at BASE 2341667 for the engaged carrier.
    // NEVER regenerate this literal from the serializer.
Wording tracks the house form at tests/test_envelope.cpp:566-567 ("ORACLE RULE: captured at BASE cd61ac6, before SessionRowReport gained a detail field. NEVER regenerate this literal from the serializer."). Both clauses present, same imperative. The literal itself is byte-identical between 2341667 and d234314 (the diff adds only the two comment lines), so the claim is verifiable at the named sha. Informational only: 2341667 is the fold baseline, not the commit that first captured the literal — the envelope precedent names the commit where the literal was frozen. A reader tracing provenance would land on a commit that did not introduce it. Not worth a cycle on its own; fix it if the file is touched again.

BR1 — minimal-accept rows. CONFIRMED. tests/test_manifest.cpp:142 `/x` → posix, :144 `/mnt/c/x` → wsl, :146 `C:/x` → windows, each paired against an already-present reject row one component shorter (`"/"` at :152, `"/mnt/c/"` at :153, `"C:/"` at :154). That is a genuine accept/reject boundary pair on all three flavors, and each accept row is checked for path preservation, flavor, and `packer_home_valid` at :168-170. Growing the `std::array` from 17 to 20 rows is CTAD-safe; all rows are the same type.

================================================================
DEFECT HUNT
================================================================

FINDING 3 — LOW — the decoy falsifier is an unnamed inner block, not a SECTION.
tests/test_pack.cpp:248-273. A failure inside it is attributed to the enclosing TEST_CASE "pack captures packer_home per HOME shape", with no CAPTURE and no label distinguishing it from the seven rows that follow. A triager reading a red run sees a HOME-shape failure. Wrapping it as `SECTION("ambient home decoy")` or adding `CAPTURE` would attribute it. No correctness impact.

FINDING 4 — LOW/INFORMATIONAL — the ORACLE base sha names the fold baseline rather than the literal's introducing commit. Detail under O1 above.

FINDING 5 — LOW — degenerate HOME rows leave the codex home tier resolving relative to the process CWD.
For the "unset" and "empty" rows (tests/test_pack.cpp:285, :287), `env.home` is an empty path, so codex's `env.home / ".codex"` is the *relative* path ".codex", resolved against the test binary's working directory; the "relative" row (:289) likewise yields "relative/home/.codex". CODEX_HOME is set and exists in those rows, but the home tier is still evaluated because `root.lexically_normal() != env_root->lexically_normal()`, so a `.codex` directory in the runner's CWD would be appended as a defaults-tier store. Claude is not exposed — it returns early once CLAUDE_CONFIG_DIR exists. This is not something the four-variable fixture can neutralise, because the relative composition happens in production from a HOME value the test deliberately sets to a degenerate shape; closing it would mean pinning CWD, which is outside this fold's scope. The direction is safe: `require_store_roots_under` (:322) plus `CHECK(report->agent_sessions.empty())` (:323) would turn such a leak into a loud failure rather than a silent contamination. Recording it as a known residual, not a must-fix.

Hunted and found clean:
- Fixture collisions. `root` = make_tmp("ambient-home-guard") and `decoy_home` = make_tmp("ambient-home-decoy") are non-nested siblings under the temp dir, each suffixed with the pid (:32-38). No make_tmp name in the file is a path prefix of another in a way that nests, and every name is distinct across test cases. Both trees are removed at :271-272.
- ScopedEnv / ScopedPackDiscoveryEnv interaction. After the fold, the only bare `ScopedEnv` left in tests/test_pack.cpp is `ambient_home` at :259; every other use is inside `ScopedPackDiscoveryEnv`. No double-set of the same variable by two independent guards anywhere, and the one nesting that does exist is LIFO-correct (see PIN 1). No aliasing: the four names are distinct.
- Decoy session shape. Written by the same `write_agent_session` helper (:220-243) that the Task-6 cases rely on for successful discovery, same directory layout, same payload keys, version above the floor. It is not invisible for an unrelated reason, so the RED-before claim rests on a genuinely discoverable row.
- Weakening of existing assertions. None. Every substitution is neutral or strictly stronger: ScopedEnv→ScopedPackDiscoveryEnv adds pinning without removing any, `emplace(...)`→`REQUIRE(emplace(...).second)` adds a check, the carrier literal change is a fixture change. No CHECK downgraded, no assertion deleted, no expectation loosened.
- Case-count parity. No TEST_CASE line is added or removed in the whole delta. The falsifier is a pure insertion at :248-273 ahead of `struct Row`; nothing was displaced or replaced. The `struct Row` table and all seven rows are untouched.
- Side effects of newly pinning HOME in tests that previously did not. Four tests gain a pinned HOME they did not have (:462, :513, :528, and the /mnt/c case at :855). This changes the manifest's `packer_home` from the runner's real home to root/"home" — none of those tests assert `packer_home`, and the happy-path test's structural assertions (`REQUIRE(members.size() == 7)` at :476, the ordered member-path checks at :477-483) are unaffected because the pinned stores are empty. Worth stating positively: before this fold, "pack writes manifest, checksums, and payload extents" ran `pack()` against the operator's real HOME and real CLAUDE_CONFIG_DIR. That was exactly Lens B's live-pack finding, and it is closed.

Boundary compliance: I did not evaluate or re-raise the decided zero-session capture cell (operator ruling (b)). The parity pin and the fences are untouched by construction — neither file appears in the delta.

================================================================
BOTTOM LINE
================================================================
Five of the six must-fixes land. H1/H2 hermeticity is real and complete against the actual production input set; the decoy is a structurally genuine RED-before/GREEN-after falsifier; V2, V3, O1 and BR1 are all correctly implemented. V1 does not land: the guard written to prove the carrier receipts are non-vacuous is itself unfalsifiable, passing on the restore workspace directory name and on a deliberately-immutable JSON key, and its search literal is not coupled to the carrier it is meant to track. That plus the missing zero-row expectation in the decoy block are what I need fixed before I can pass this fold.
```

---

## LEAD SYNTHESIS

Lens verdict (bare): must-fix — 1 Critical, 1 Medium, 3 Low/Informational.

**RE-CHECK VERDICT: REVIEW-FOLD required — a bounded MICRO-FOLD of exactly two items,
test-only.** Five of the six human-lens must-fixes land and are confirmed at depth:
H1/H2 hermeticity is real and complete against the PRODUCTION input set (the lens
closed the four-variable set by grepping `getenv` across src at the head, not by
trusting the plan); the constructed decoy is a structurally genuine RED-before/
GREEN-after falsifier; V2, V3, O1, BR1 all correctly implemented; the pre-fold
live-pack hole (Lens B's original finding) is CLOSED — the happy-path pack test no
longer touches the operator's real stores.

**MFX-1 (GATES — lens Finding 1, Critical):** the V1 non-vacuity guard is itself
unfalsifiable — `find("/ws")` over installed content passes on TWO false witnesses
(the restore workspace directory literally named "workspace", and the sealed
never-rewritten JSON key), and the literal is uncoupled from the carrier value (a
`/zz` carrier leaves the guard green). The INPUT half of V1 landed (the fixture is
genuinely carrier-rooted); the PROOF half did not. Fix per the lens's prescription:
hoist `kEngagedCarrier`, assert the record origin is a strict prefix match, assert the
INPUT member bytes carry the encoded spelling — both fail the moment the fixture stops
being carrier-rooted, and neither false witness can satisfy them; any post-install
check must exclude `workspace.generic_string()`. The recursion is noted honestly: this
is the unfalsifiable-box shape found in the fix for the unfalsifiable-box finding.
**MFX-2 (lens Finding 2, Medium):** the decoy block's post-state is two vacuous
universal quantifiers — add the file's own explicit `CHECK(report->agent_sessions.empty())`.
**Optional tier:** SECTION/CAPTURE attribution for the decoy block (F3); ORACLE
provenance-sha wording (F4).
**Recorded, not folded:** F5 — the degenerate-HOME rows leave codex's home tier
resolving a CWD-relative `.codex` (production composition from a deliberately
degenerate HOME; un-neutralizable by the env fixture; failure direction loud, not
silent) — joins the T-2 registry family.

### Disposition

Micro-fold on pair authority (test-only, no sealed contact) via the established fresh
two-edge chain: a uniquely keyed PLAN (Edge 1 → the rev6 DESIGN-REVIEW) riding this
record, the Implementer's PLAN-REVIEW, then the token (Edge 2). Then a verification
sized to the ~2-file delta (lead + tests). The merge hand-up waits on that pass; the
published PR #24 is untouched; the release hold is ABSOLUTE.
