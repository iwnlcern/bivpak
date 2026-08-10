# TARGETED RE-CHECK RECORD — R-4.8 carrier panel fold at `2bc7a078`

DISPATCH_ID: s4-matrix-arm1-r48-fold-recheck
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-fold-impl-complete
CANDIDATE_SHA: 2bc7a078302f740721ac0d6412c843a8172368a5 (branch `s4-matrix/r48-carrier`, LOCAL, unpublished; ONE fold commit over `29796bbe`)
FOLD_DELTA: `git diff 29796bbe..2bc7a078` = 8 files (5 of the 10 authorized paths untouched-or-no-change: adapter.hpp, sessions.cpp required no edit)
BASE: 6047ab0311491da5567c99f32b22ff14433fb1d2
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md (rev4, `c1c3188b…@91d6841`, approved `211611`)
PRIOR_PANEL: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-carrier-panel-29796bb.md (sealed `006144b2…`; the MF-1..MF-6 set this fold answers)
LEAD: s4-matrix.planner (non-lens — no findings of its own, no re-grading; synthesis and cross-lens adjudication only)
DATE: 2026-08-09/10

PANEL_CHOSEN: team-of-3 owning lenses (targeted, fold-delta-scoped, per the ruled mechanism's "targeted re-check, lead + owning lenses"): security (owned MF-1), test-coverage (owned MF-2..MF-6 and the non-vacuousness bar), correctness/design-conformance (owned the HIGH receipt finding, §9-21, and rev4 conformance). Perf+idiom was approve-tier at the prior panel with only optional-tier findings — no seat owed.
PANEL_COMPOSITION: three independent cold read-only subagents (r48-recheck-security, r48-recheck-tests, r48-recheck-correctness), each pinned to `2bc7a078`, instructed to judge committed blobs only and to review the fold delta with whole-file context. Both pair seats excluded from lenses; this seat non-lens lead. No re-spawn. Each lens carried a dual charter: confirm its assigned MF-fixes close at the bytes AND hunt defects the fold introduced. Tests and correctness additionally carried the Implementer-routed ruling request on the MF-6 absent-arm limitation.

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| security | 1 | 0 | 1 |
| test-coverage | 1 | 0 | 1 |
| correctness | 1 | 0 | 1 |

3 spawns = 3 finding-sets + 0 stalls. Each report was delivered to the lead via the agent mailbox (each lens signalled idle first and delivered on the lead's request) and is reproduced below unaltered.

## LEAD PRE-PANEL VERIFICATION (E1, at `2bc7a078`, before spawning)

- One commit over `29796bbe`; delta exactly the eight paths the completion report named; the two no-change paths untouched.
- pack.cpp delta confined to `packer_home_carrier` collapsing to the one-line factory call; `path_flavor` and every `source_path_flavor` site untouched (R-4.12 boundary held).
- Thresholds single-sited in `packer_home_valid`'s switch; `make_packer_home` routes through the predicate — no duplicated branches (the rev4 approve's hard constraint).
- Both Step-3 fences live at the head.

## CHARTER CORRECTION ON THE RECORD (correctness lens caught the lead's error)

The lead's re-check charter to the correctness lens asked it to verify that "delete-the-assignment must go RED via the byte-identity comparison." That premise was WRONG — the adapter receipts are inertness receipts (their falsification domain is "an adapter starts interpreting the value"), and the production-copy deletion falsifier lives in the test_sessions transport arm, exactly as the original MF-4 text prescribed. The lens corrected the premise instead of verifying it — the desired behavior — and the closure is recorded under the correct claim, not the charter's inflated one.

---

## VERBATIM REPORT — security lens

```
SECURITY LENS — targeted post-fold re-check, R-4.8 packer-home carrier
CANDIDATE: s4-matrix/r48-carrier @ 2bc7a078302f740721ac0d6412c843a8172368a5
FOLD DELTA: 29796bbe..2bc7a078 (one commit); BASE 6047ab03
METHOD: committed blobs only (`git show <sha>:<path>`, `git diff`). No working-tree reads, no edits, no builds.

VERDICT: pass

MF-1 closes my F1 at the bytes, in every spelling I named including the JSON-encoded forms. Two Low advisory findings and two observations follow; neither finding is must-fix at this fold.

================================================================
1. MF-1 CONFIRMATION — F1 IS CLOSED
================================================================

The predicate is `packer_home_valid` at src/core/manifest/manifest.cpp:463-480; the new factory is `make_packer_home` at src/core/manifest/manifest.cpp:482-490. I walked both branch by branch.

`packer_home_valid` computes `classify_absolute(value.path)` into an std::optional<PathFlavor> and rejects on `classified != value.flavor` (manifest.cpp:464-467). Comparing an engaged-or-empty optional against a bare enumerator is well defined, and nullopt compares unequal to every value, so an unclassifiable path (empty, relative, "mnt/c/x", "C:") is rejected there. The switch below therefore only ever runs with `classified` engaged AND equal to the declared flavor. The switch applies the ruled thresholds, and the post-switch `return false` (manifest.cpp:479) is a fail-closed fallback for an out-of-range enum — which `parse_path_flavor` cannot produce anyway.

Boundary values, evaluated exactly against the code:

  "/"        -> posix,             threshold >1U, size 1 -> INVALID
  "/x"       -> posix,             threshold >1U, size 2 -> valid
  "/mnt/c/"  -> wsl,               threshold >7U, size 7 -> INVALID
  "/mnt/c/x" -> wsl,               threshold >7U, size 8 -> valid
  "C:/"      -> windows (drive),   threshold >3U, size 3 -> INVALID
  "C:\"      -> windows (drive),   threshold >3U, size 3 -> INVALID
  "C:/x"     -> windows (drive),   threshold >3U, size 4 -> valid
  "//?/"     -> windows (extended),threshold >4U, size 4 -> INVALID
  "//?/x"    -> windows (extended),threshold >4U, size 5 -> valid
  "\\?\"     -> windows (extended),threshold >4U, size 4 -> INVALID
  "\\?\C"    -> windows (extended),threshold >4U, size 5 -> valid

Every threshold is exclusive `>` against the exact root length, so each bare root is rejected and each root-plus-one-byte is admitted. That is the design spec (posix >1, wsl >7, windows drive >3, windows extended >4) with no off-by-one in either direction. The extended-prefix literal is the raw string R"(\\?\)" at manifest.cpp:475 — the four characters backslash-backslash-question-backslash, i.e. the correct in-memory form, not a doubled escape.

Both boundaries are gated, so F1's two halves close independently:

- PARSE FAILS CLOSED. manifest.cpp:646-649 constructs the PackerHome from the decoded strings and returns ParseError detail "packer_home" when `packer_home_valid` is false. The whole manifest parse fails; there is no partial accept and no path that stores a degenerate value into Manifest.packer_home.
- CAPTURE DEGRADES TO ABSENT. `make_packer_home` classifies, builds the aggregate, and returns nullopt unless `packer_home_valid` holds, so the factory cannot construct an engaged invalid value. src/core/pack/pack.cpp:142-144 is now the one-line delegation the design specifies; the single capture site is src/core/pack/pack.cpp:676 (`.packer_home = packer_home_carrier(env.home)`). With HOME unset or empty, pack.cpp:245-250 yields an empty std::filesystem::path whose generic_string() is "" — unclassifiable, hence absent. A degenerate HOME never becomes an in-memory engaged value; that is the capture-time property the old code lacked.

THE ENCODED-FORM CHECK (the part that matters). Validation runs on the DECODED std::string that `optional_string` (manifest.cpp:99-115) extracts via simdjson's element.get(std::string_view). simdjson has already resolved \\, \/, and \uXXXX escapes at that point, so every JSON spelling of the same four bytes converges on an identical std::string before `packer_home_valid` sees it. There is no encoding-level bypass: "\\\\?\\", "\u005c\u005c?\u005c", and any mixture decode to the same 4-byte \\?\ and take the same rejection. The scanner decode level matches the artifact format here — the exact failure shape I was watching for. The doubled-backslash form is exercised directly in tests/test_manifest.cpp (the C++ literal "\"packer_home\":\"\\\\\\\\?\\\\\"," is JSON text \\\\?\\, decoding to \\?\), with positive control "\\?\C:\Users\x" asserted to parse valid.

MY ORIGINAL F1 ATTACK ROWS, re-run against the code at 2bc7a078:

  "packer_home":"/"        + "packer_home_flavor":"posix"   -> ParseError detail "packer_home"
  "packer_home":"/mnt/c/"  + "packer_home_flavor":"wsl"     -> ParseError detail "packer_home"
  "packer_home":"C:/"      + "packer_home_flavor":"windows" -> ParseError detail "packer_home"
  "packer_home":"C:\\"     + "packer_home_flavor":"windows" -> ParseError detail "packer_home"
  "packer_home":"//?/"     + "packer_home_flavor":"windows" -> ParseError detail "packer_home"
  "packer_home":"\\\\?\\"  + "packer_home_flavor":"windows" -> ParseError detail "packer_home"

All six are present as executable rows in tests/test_manifest.cpp ("packer_home malformed values fail closed naming the home key", array widened 5 -> 13), with serialize-side collapse rows added to the invalid-engaged test and nullopt rows added to the new `make_packer_home` factory table. That factory table is the falsifier the design asked for: it calls make_packer_home("/") and asserts nullopt with NO serializer in the loop, so capture-time absence is now distinguishable from serializer collapse.

================================================================
2. FINDINGS
================================================================

F2 — LOW (advisory; route to the needle head, R-4.10/R-4.11) — src/core/manifest/manifest.cpp:463-480
The thresholds are pure byte-length tests, so a dot-padded or slash-padded root clears them in every flavor:
  posix:            "//" (2), "/." (2), "/.." (3)
  wsl:              "/mnt/c//" (8), "/mnt/c/." (9)
  windows drive:    "C:/." (4)
  windows extended: "//?/." (5)
Each lexically normalizes back to the bare root it is padding. Under the ruled contract this fold is safe — design §3/§7 make the value verbatim with no normalization, and a literal prefix match on "//" or "/." fires on almost nothing. But the F1 threat model reopens exactly if the future home-prefix needle normalizes or collapses the carrier before matching. Since R-4.10/R-4.11 bind the needle head, the honest place for this is a registered constraint on THAT head: the needle must prefix-match the carrier verbatim, or re-apply non_degenerate after any normalization it performs. Not must-fix here — the carrier implements the ruled design exactly and the consumer does not yet exist.

F3 — LOW — src/core/manifest/manifest.cpp:475-477 (against :452-455)
The windows extended-prefix discriminator is written twice: once in `classify_absolute` as part of the windows branch, and again in `packer_home_valid` to choose between thresholds 4 and 3. The selector's fallback is the PERMISSIVE one — any windows-classified spelling that does not literally start with \\?\ or //?/ gets threshold 3. So if the classifier's windows grammar ever gains a third sub-form (a device path such as \\.\, or a UNC form) and the validator is not edited in the same pass, that form's bare root is admitted with no error — F1 again in a new spelling. Note the §9 test-14 parity table CANNOT catch this: it pins classify_absolute against rewrite::path_flavor_for, and a grammar extension applied to both layers keeps parity green while the threshold silently defaults to 3. Structural fix: one helper returning the matched root length (or classify_absolute returning flavor + root length) consumed by both sites, with a fail-closed default. Advisory, not must-fix: unreachable at this SHA because the windows grammar today is exactly the two forms the validator lists.

================================================================
3. VERIFIED CLEAN
================================================================

- NO DUPLICATED THRESHOLD LOGIC ANYWHERE IN THE TREE. Grepped 2bc7a078 across all of src/ for the degenerate thresholds and flavor-root literals. The >1U / >7U / >3U / >4U root thresholds exist ONLY at manifest.cpp:470, :472, :474-477. The pre-existing classifier-grammar mirrors (src/adapters/rewrite_common.cpp:44,53; src/core/pack/pack.cpp:133,256-261; src/adapters/claude_code/install.cpp:95; src/adapters/codex/install.cpp:64) are classification-only and carry no degeneracy threshold; none was touched by the branch.
- BOTH STEP-3 FENCES LIVE AND BYTE-IDENTICAL TO BASE. `git diff 6047ab03..2bc7a078 -- src/core/scan/scan.cpp` is EMPTY; the RepoDiscoveredUnsupported refusal stands at src/core/scan/scan.cpp:138. The require_empty_array(object, "repos") fence stands at src/core/manifest/manifest.cpp:679 (helper at :81-97, still returning detail "step2-plain-dir-only" on a non-empty array); the branch diff for manifest.cpp contains no "repos"/"require_empty_array" hunk.
- NO NEW PARSE SURFACE. The fold adds no wire key and does not touch the parse block; the entire production delta is the predicate body, the new factory, one header declaration (manifest.hpp:82), and the pack one-liner. format_version stays 1; required_capabilities gains nothing.
- NO OUT-OF-RANGE ACCESS IN THE CHANGED CODE. classify_absolute guards path.at(5)/path.at(6) behind size()>=7U and path.at(0..2) behind size()>=3U; starts_with is total; packer_home_valid and make_packer_home index nothing and call no substr. The manifest is capped at 16 MiB (kManifestByteCap) and both new functions are O(1) in path length — no new parse-DoS surface.
- LEAK SURFACE STILL NIL. Grepping 2bc7a078 for `packer_home` across src/ returns exactly: the schema declarations, pack.cpp:142/676 (write), manifest.cpp serialize/parse, src/core/open/sessions.cpp:271 (the single opaque copy into InstallTarget), and src/adapters/adapter.hpp:161 (the field). NO code anywhere READS InstallTarget.packer_home — no adapter, no report, no envelope, no render path. The packer's home cannot reach any operator-visible output or any restored payload at this SHA.
- TRANSPORT UNTOUCHED BY THE FOLD. `git diff 29796bbe..2bc7a078 -- src/core/open src/adapters` is empty; the previously-cleared transport probe is unchanged code.
- PROBES STRENGTHENED, NOT WEAKENED. tests/test_sessions.cpp went from one adapter leg to two, asserting a vector of observed values per leg — that closes the "populated once, observed once" hole rather than opening one. The adapter tests converted from local content assertions to a differential (engaged == absent) byte comparison across two isolated store roots. I checked the coverage that MOVED: the dropped key-must-not-change / 0.1 / 1.0 / 1e+03 / 18446744073709551615 assertions still exist in the sibling "rewrites escaped values without changing keys or numbers" cases at tests/test_adapter_claude_install.cpp:590-616 and tests/test_adapter_codex_install.cpp:547-579 — nothing lost. I also checked the differential for FLAKE, since a false-green there would be worse than no probe: claude mints uuid4() only for uuid/parentUuid/leafUuid fields (src/adapters/claude_code/install.cpp:189-190, 267-272) and the fixture line contains none; codex's time-derived values land in the rollout PATH (src/adapters/codex/install.cpp:121-127, 368-372) while the content rewrite substitutes only origin paths and ids. The only cross-arm difference in the compared text is the installed session id, which the test normalizes. Deterministic. The `record.children.clear()` call is load-bearing for that determinism, since child ids are minted and not normalized.
- test_pack.cpp HARDENING. The capture matrix now pins CODEX_HOME and CLAUDE_CONFIG_DIR to the temp root alongside HOME — closing a real-store fallback the previous ScopedHome left open — adds the HOME=/ row, and promotes the source_path_flavor == posix independence assertion from the wsl row only to EVERY row.

================================================================
4. STRONGEST ATTACKS THAT FAILED
================================================================

- ENCODING LAUNDERING OF THE EXTENDED ROOT. "\\\\?\\", "\u005c\u005c?\u005c", and mixed escape forms all decode to the same four bytes before validation, so all take the same ParseError{"packer_home"}. Validation sits on the decoded string, not the raw JSON span — the correct decode level for this artifact.
- FLAVOR LAUNDERING OF A DEGENERATE ROOT. Declaring "/mnt/c/" as posix to dodge the wsl threshold fails: classify_absolute returns wsl (the wsl branch precedes posix), so the flavor-equality check rejects before any threshold runs. Same for "C:/" declared posix and "//?/" declared posix — the windows branch precedes the posix branch. No degenerate root can pick a flavor whose threshold it would clear.
- SUB-GRAMMAR LAUNDERING INSIDE WINDOWS. Declaring "//?/" windows and hoping the drive threshold (3) applies fails: the selector at manifest.cpp:475 re-tests both extended prefixes and picks 4. Conversely "C:/" cannot reach the extended threshold. (The INVERSE of this attack is F3's latent case, which needs a future grammar change to become reachable.)
- SERIALIZER ROUND-TRIP LAUNDERING. Aggregate-initializing a degenerate PackerHome and serializing, hoping the wire keeps it: the serialize gate at manifest.cpp:538 applies the same packer_home_valid, so both keys are omitted and the value collapses to absent. Writer emittable states remain exactly {absent, valid}.
- LONE-KEY AND NULL SMUGGLING. "packer_home": null with a present flavor, and each lone key, hit the XOR check at manifest.cpp:638 and fail with detail "packer_home_flavor"; neither yields a stored value. Wrong-type "packer_home": 42 fails inside optional_string with detail "packer_home".
- REJECTION-PATH ORACLE. A hostile manifest can distinguish detail "packer_home" from "packer_home_flavor", but both are total failures of the entire manifest parse over the attacker's OWN input, and the detail carries no value from the image and no host state. No oracle, no partial accept, no information gained.
- PARSE-COST AMPLIFICATION. A 16 MiB packer_home string was the obvious lever, but both new functions are constant-time prefix and size tests; the cost is the pre-existing simdjson string copy, unchanged by this fold.

================================================================
5. OBSERVATIONS FOR THE RECORD (not findings)
================================================================

O-1. The narrowing is fail-closed on the WHOLE IMAGE: an image carrying "packer_home":"/" now fails manifest parse entirely rather than ignoring the field. That is exactly what design §6/§8 rule, and it is unreachable in practice — the field is new on this unmerged branch, the release hold is absolute, and the only binary that could ever have emitted a degenerate carrier is one built from the pre-fold head 29796bbe. Stating it explicitly so the ruling's blast radius is on the record rather than inferred.

O-2. make_packer_home re-runs classify_absolute inside packer_home_valid (two classifications per call). Trivial cost, no DoS, and it buys the literal postcondition "an engaged result always satisfies valid()". Noted, not a defect.
```

## VERBATIM REPORT — test-coverage lens

```
TEST-COVERAGE LENS — targeted post-fold re-check, R-4.8 packer-home carrier. Candidate 2bc7a078302f740721ac0d6412c843a8172368a5; fold delta 29796bbe..2bc7a078; BASE 6047ab0311491da5567c99f32b22ff14433fb1d2. Judged from committed blobs only (git show / git diff). No build, no run, no edits, working tree untouched.

## VERDICT: must-fix (0 Major, 2 Minor — one of which gates, 4 Nit/Observation)

Everything the fold set out to close, it closed at the bytes: MF-2, MF-3, MF-4, MF-6 and design-rev4 tests 11b, 13b, 18b are all genuinely non-vacuous, and I confirm each individually below. The gating item is narrow: MF-5's landed hermeticity guards never engage, so the specific residual my own MF-5 text named (store discovery resolving `.claude`/`.codex` against the test CWD) is still open while the SITREP reports it closed. Closure is one or two lines.

---

## FINDINGS

### F-1 (Minor — GATES). MF-5 env guards point at directories that are never created, so the env discovery tier never fires and discovery falls back to the HOME-derived default on every row.
tests/test_pack.cpp:235-237 at 2bc7a078.

The three ScopedEnv guards are installed, but `(root / "codex")` and `(root / "claude")` are never create_directories'd. Both adapters gate the env tier on existence:

- src/adapters/claude_code/claude_code.cpp:302 — `if (configured.has_value() && fs::exists(*configured, ec))`, and only that branch early-returns the store set.
- src/adapters/codex/codex.cpp:763-767 — same existence gate; and even when it does fire, codex additionally appends `env.home / ".codex"` when that exists and differs (codex.cpp:771-774).

So for every one of the seven rows the guards are inert and discovery lands on `env.home / ".claude"` and `env.home / ".codex"`. Walking each row for what that resolves to:

- absolute-posix — env.home = `<root>/home` (never created) → nothing exists. Hermetic.
- unset — HOME unset → process_env() (src/core/pack/pack.cpp:245-250) yields `fs::path{}` → discovery stats `.claude` / `.codex` relative to the test process CWD.
- empty — HOME="" → same `fs::path{}` → same CWD-relative stat.
- relative — → `relative/home/.claude` relative to CWD.
- degenerate-root — HOME=/ → `/.claude`, `/.codex`. Absent on macOS; plausible in a root-HOME Linux container, which is exactly the CI-parity target in this repo's CLAUDE.md.
- wsl-mount — `/mnt/c/Users/x/.claude`, absolute and absent. Hermetic.
- windows-drive — `C:/Users/x` is a RELATIVE path on POSIX → `C:/Users/x/.claude` relative to CWD.

Four of seven rows are CWD-dependent. Blast radius today is nil — I checked: no `.claude` or `.codex` at the repo root (neither tracked nor present on the host), and a build-dir CWD has neither. The MF-5 harm that actually mattered (HOME=/Users/jack walking the operator's live ~/.claude and ~/.codex) IS closed; that row is gone. What is not closed is the second half of MF-5, and the fix as applied does not make the check fire — it moves the field without changing the outcome, the shape this repo has been bitten by before.

Why I gate on a Minor: this is a re-check whose whole job is confirming closure, and the receipt currently claims more than landed.

Minimal closure, ascending strength — either is acceptable, both is better:
1. create_directories(root / "codex") and (root / "claude") before the guards. Fully closes claude (its env branch early-returns); closes codex for every row except where a real `.codex` sits in CWD.
2. Add `CHECK(report->agent_sessions.empty())` inside the row loop. This is the file's own idiom (the sibling at test_pack.cpp:287 does exactly this) and it is a direct falsifier: RED the moment any store outside the fixture is discovered, on every row, regardless of which tier found it.

### F-2 (Minor — recommend folding, would not gate alone). The MF-4 byte-identity receipt compares one session file, not the produced store.
tests/test_adapter_claude_install.cpp:558-571; tests/test_adapter_codex_install.cpp:509-529.

My MF-4 fix text asked to "assert the produced store bytes are IDENTICAL". What landed reads exactly one file per arm — the installed parent session — and compares those two strings. The file SET is never compared. An adapter that started interpreting packer_home by writing a sidecar, a config entry, or an extra artifact keyed on the packer's home would leave the compared file byte-identical and the test green. That is precisely the scenario the receipt exists to catch.

The codex arm already computes relative_files(store) at line 512, so closure is cheap on that side: capture the sorted relative-file list alongside the normalized content and assert both the lists and the per-file bytes match across arms. Claude's arm has no file-list read today and would need one.

Minor rather than Major because the plausible interpretation path — rewriting paths into session content — IS covered byte-for-byte, and a behavioral divergence (a skipped or failed session) would also trip `sessions.size() == 1U` / `outcome == installed` inside the lambda. The gap is narrower than MF-4's original one, but not zero.

### F-3 (Observation — design-conformant; route as a registry residual, NOT a fold defect). packer_home_valid accepts the extended-prefix drive ROOT; the 11b/13b matrices are blind to that cell.
src/core/manifest/manifest.cpp:474-477; matrices at tests/test_manifest.cpp:147-152 and 241-255.

The windows arm uses a flat threshold: `size > 4` when the path starts with `\\?\` or `//?/`, else `size > 3`. So `C:/` (3) is rejected, but `\\?\C:\` (7), `//?/C:/` (7), and even `\\?\C:` (6) all pass as non-degenerate. Both are bare drive roots — exactly what the design's stated rationale ("a bare root is not a usable reference frame") bans. The consistent threshold for the extended spelling is `> 7`: prefix length plus the plain drive-root length.

I am NOT calling this a fold defect. Design rev4 at 91d6841 specifies `>4` explicitly (`// windows extended: path.size() > 4`) and separately rules `"\\?\C:\Users\x"` valid with the gloss "the rev3 rule bans only the bare 4-byte prefix". The implementation conforms exactly, and the matrices enumerate exactly the rows the design lists. The inconsistency lives in the design's own grammar, above this pair, and this is a sealed-contract cell.

What I do flag as a TEST matter: neither matrix contains `\\?\C:\` or `//?/C:/`, so the behavior at that cell is accidental rather than pinned. Whatever the ruling, add the row — either as nullopt / ParseError{"packer_home"} if the grammar is corrected, or as an explicit engaged-valid row documenting the narrow ban. An unpinned cell is how this comes back.

### F-4 (Nit). The two byte-identity arms do not use identical fixtures — the store roots differ.
tests/test_adapter_claude_install.cpp:550; tests/test_adapter_codex_install.cpp:503 — `const auto store = root / std::string{arm};` gives `<root>/engaged` vs `<root>/absent`. Workspace, members map, and record are shared and identical; only the store path differs. If the store root ever appeared in installed content the arms would diverge for a reason unrelated to packer_home. That failure direction is safe (false-RED, not false-GREEN), so this is a nit — but MF-4 asked for identical fixtures, and two sibling temp ROOTS with the same relative layout would give that literally.

### F-5 (Nit). Magic 14U duplicates strlen("<installed-id>").
tests/test_adapter_claude_install.cpp:569; tests/test_adapter_codex_install.cpp:526. The advance is correct (the replacement is exactly 14 chars, shorter than a 36-char UUID, so the scan terminates and cannot re-match), but the constant and the literal can drift apart silently. A named `constexpr std::string_view kIdPlaceholder` used in both the replace and the advance removes the coupling.

### F-6 (Nit). 13b's factory rows live inside a TEST_CASE whose first half exercises serialize/parse.
tests/test_manifest.cpp:114-163. The design calls 13b "the CAPTURE-boundary falsifier — no serializer in the loop". That is satisfied literally: the factory loop at 138-162 calls make_packer_home and packer_home_valid only. But sharing a TEST_CASE with the round-trip loop above it means a reader must verify the falsifier is serializer-free rather than see it. A separate TEST_CASE would make the property self-evident and would survive future edits to the round-trip half.

### F-7 (Observation, no action). unset and empty rows converge downstream.
tests/test_pack.cpp:222-225. unsetenv and setenv(HOME,"") take different branches in process_env()'s `.home` lambda (pack.cpp:246: nullptr vs non-null-empty), so the rows DO measure distinct inputs — but both produce `fs::path{}` and therefore an identical empty string at the carrier boundary. The distinction is real at the getenv edge and redundant at the predicate. Not vacuous; worth knowing the rows are not two independent carrier cases.

### F-8 (Observation, no action). .string() vs .generic_string().
tests/test_pack.cpp:233 builds the expected path with .string() while pack.cpp:144 captures via .generic_string(). Identical on POSIX and macOS, which is every host this suite runs on. Flagged only so it is a known equivalence rather than an unexamined one.

---

## NON-VACUOUSNESS CONFIRMATIONS

MF-2 — CONFIRMED, fully falsifies. tests/test_manifest.cpp:93-111 is a FULL exact JSON literal, not a substring or an ordering predicate, and it runs with the carrier ENGAGED (packer_home set at line 82). I walked it against serialize() at manifest.cpp:517-562 key by key: the golden reproduces production order exactly, with packer_home / packer_home_flavor emitted between source_path_flavor and bivignore, and repos after bivignore. Relocating the emit block (manifest.cpp:538-543) to after the repos array yields `..."bivignore": {...}, "repos": [], "packer_home": ...` — a different string, so the REQUIRE at line 93 goes RED. Moving it before source_path_flavor likewise. Adjacency of the two keys and home-before-flavor order are both pinned. The old weak predicate at line 88 (source_path_flavor < packer_home) survives alongside and is now redundant; harmless. The golden pins serialize only; parse position is genuinely order-independent via simdjson key lookup, so nothing is owed there.

MF-3 — CONFIRMED, fully falsifies. tests/test_manifest.cpp:277-281. The row is `"packer_home":"/x","packer_home_flavor":42` asserting `detail == "packer_home_flavor"`, and it sits in the FLAVOR-detail TEST_CASE (renamed "packer_home flavor errors name the flavor key not source_path_flavor"), not in the packer_home-detail array — exactly as MF-3 demanded. I traced the reached branch: optional_string(object, "packer_home_flavor") (manifest.cpp:634) hits the non-string `element.get(value)` failure at manifest.cpp:111-112, which constructs BivError{ParseError, {}, std::string{key}} with key = "packer_home_flavor"; that error is propagated verbatim by the previously-unreached `if (!packer_home_flavor_text) return std::unexpected(...)` at manifest.cpp:635-637. The detail string is now guarded at its source. Weakening it to "packer_home" or to the sibling "source_path_flavor" both go RED.

MF-4 — CONFIRMED, with the F-2 scope caveat. The two arms run against identical members, identical workspace, and the identical records vector (record.children.clear() applied once, before both calls); only the store root differs (F-4).
  What is normalized, and whether it can mask a divergence: only literal occurrences of that arm's own installed_session_id, replaced with `<installed-id>`. This cannot mask a real divergence. The replacement is keyed to a per-run 36-char UUID drawn from result->id_map.front(); it is not a wildcard and cannot swallow neighbouring bytes. Critically it cannot hide the value under test — "/Users/packer" is not a UUID, so no substitution touches it. The `REQUIRE(id_position != npos)` at line 566/523 is a real precondition: if the id ever stopped appearing in content the normalization would silently become a no-op, and that assert catches it.
  Does it fail if an adapter starts reading the field? Yes for the interpretation paths that matter. If packer_home were substituted into rewritten paths or written into session content, the engaged arm carries /Users/packer and the absent arm does not → strings differ → RED. Behavioral (non-byte) interpretation is partly covered too: a packer_home-conditional skip or failure trips `sessions.size() == 1U` or `outcome == installed` inside the lambda. The uncovered case is a write to a DIFFERENT file in the store — F-2.
  Coverage-regression check: the content-fidelity assertions the old test carried ("/ws/proj":"key-must-not-change", decimal 0.1, integral 1.0, exponent 1e+03, 18446744073709551615) are NOT lost. They are asserted against the same fixture by the adjacent full-install cases — test_adapter_claude_install.cpp:582 and test_adapter_codex_install.cpp:539, both titled "install rewrites escaped values without changing keys or numbers" — and by the rewrite-common case at test_adapter_claude_install.cpp:501. No net loss.

MF-5 — PARTIALLY CONFIRMED. Walking every row: the real-host /Users/jack row is GONE, replaced by a temp `(root / "home")` fixture path, and all remaining absolute values (/mnt/c/Users/x, C:/Users/x) are synthetic and cannot exist on any host this runs on. That closes the dangerous half. All three env vars are SET but none of them ENGAGE — F-1. The unset and empty rows do still measure distinct inputs (F-7). One genuine strengthening worth recording: `REQUIRE(manifest->source_path_flavor == PathFlavor::posix)` at test_pack.cpp:252 now runs on EVERY row rather than only wsl-mount, a real control proving HOME shape cannot leak into the source flavor — RED if the two capture paths were ever crossed.
  Env hygiene of the new ScopedEnv(optional<string>) generalization — CLEAN. tests/test_pack.cpp:140-166. Restore/unset symmetry holds on all paths: the constructor snapshots old_value_ from getenv BEFORE mutating, and the destructor restores when engaged and unsetenv's when not — the same total behavior the deleted ScopedHome had, now covering the unset direction for any variable. Copy and move are all `= delete`d, so no double-restore or use-after-move path exists. Exception unwind is safe: on a failed REQUIRE Catch2 throws, the three guards destruct in reverse declaration order, and no two guards name the same variable, so there is no aliasing. The one exception-safety gap is pre-existing file idiom, not fold-introduced: remove_all(root) at line 253 sits at the end of the loop body, so a failing row leaks its temp dir.
  Fixture collisions: none. make_tmp at test_pack.cpp:32 keys on label plus pid and the seven roots are label-distinct; the two adapter files both use the label "packer-home-receipt" but their make_tmp prefixes differ (biv-claude-install- vs biv-codex-install-), so no cross-file collision.
  CODEX_SQLITE_HOME is not guarded but is unreachable here: sqlite_locator is only invoked from inside append_store_set (codex.cpp:743), which only runs once a store root exists — which, per F-1, never happens in this test. Not a finding.

MF-6 — CONFIRMED, engaged arm fully falsifies. tests/test_sessions.cpp:176-178, 198 — the seam is now `std::vector<std::optional<PackerHome>> seen_packer_homes` with push_back per call, so per-call values are preserved rather than overwritten. Both legs are captured: run_session_leg (src/core/open/sessions.cpp:181-182) iterates preview.agents and matches manifest entries by `entry.agent != agent.agent`, and the tests build two preview agents named fixture-agent-a / fixture-agent-b against a manifest carrying one entry each (test_sessions.cpp:401, 439), both pointing at the same adapter instance. The adapter's id() returning "fixture-agent" is not used for matching, so this wires correctly. `REQUIRE(install_calls == 2U)` is itself a live control — if the store-writability gate at sessions.cpp:251 or the consent gate at sessions.cpp:235 rejected either agent, the count drops and the test goes RED.
  Engaged arm, deletion falsifier: deleting `.packer_home = manifest.packer_home` at sessions.cpp:271 leaves InstallTarget::packer_home at its declared default (src/adapters/adapter.hpp:161: `std::optional<manifest::PackerHome> packer_home{std::nullopt};`), so the observed vector becomes {nullopt, nullopt} and the assertion at test_sessions.cpp:431-433 fails. CONFIRMED RED. A leg-conditional copy (first leg only) also fails, since element [1] would be nullopt. Because both expected elements are identical the test cannot attribute a failure to a specific leg, but it cannot miss one either.
  Removal of install_result.sessions from both tests: harmless. The row-building loop at sessions.cpp:304 iterates an empty span, any_clean stays false, outcome remains engaged, REQUIRE(outcome) still holds. Nothing dereferences front().

13b — CONFIRMED complete against rev4. tests/test_manifest.cpp:135-162. The factory is called DIRECTLY (make_packer_home(row.path) at line 155) with no serializer, no parser, and no pack() in the loop. All rev4-specified rows are present: engaged "/Users/x" posix (140), "/mnt/c/Users/x" wsl (141), "C:/Users/x" windows (142), R"(\\?\C:\Users\x)" windows (143-144); nullopt "" (145), "relative/home" (146), "/" (147), "/mnt/c/" (148), "C:/" (149), "//?/" (151); plus two rows beyond spec, "C:\\" (150) and R"(\\?\)" (152). The postcondition row is present as `CHECK(packer_home_valid(*actual))` at line 160, inside the engaged branch, so it runs for every engaged result. `REQUIRE(actual.has_value() == row.flavor.has_value())` at 156 is the primary discriminator and CAPTURE(row.path) at 154 gives per-row attribution. The production edge is bound without an injected seam: pack.cpp:144 calls make_packer_home directly and test_pack.cpp drives the real pack(), so the unit and the integration meet at the same function.

11b — CONFIRMED complete. Parse side: all six degenerate roots at test_manifest.cpp:250-255, each expecting ParseError with detail == "packer_home"; the positive control `\\?\C:\Users\x` at 262-268 asserts the parse SUCCEEDS and the resulting PackerHome equals the exact expected value — that control is what stops the degenerate rows being satisfied by a blanket rejection of the extended spelling. Serialize-collapse extension: the same six values engaged in memory at test_manifest.cpp:186-191, each asserting `serialize(...).find("packer_home") == npos`, which covers BOTH keys since "packer_home_flavor" contains "packer_home" as a substring. Three classifier boundary rows landed too (/mnt/c → posix, /mnt/1/x → posix, 1:/x → nullopt, at lines 299-301). The one cell not enumerated is F-3.

18b — CONFIRMED. tests/test_pack.cpp:228-229, the degenerate-root row with HOME=/, driven through real pack(), real archive write, real read_archive, and real manifest::parse, expecting packer_home == nullopt. This is a true wire-ABSENCE assertion, not a parsed-nullopt equivocation: if the keys were emitted with a degenerate value, parse would fail the validator at manifest.cpp:647-649 and `REQUIRE(manifest.has_value())` at line 246 would go RED before the comparison. So parsed-nullopt here implies keys-absent.

---

## RULING ON THE DISCLOSED MF-6 ABSENT-ARM LIMITATION

The landed mechanism SATISFIES my finding as written. No escalation needed. Register as a residual; do not fold further.

My MF-6 fix text was: "a second agent plus a per-call vector of observed values; assert both legs and the absent-arm nullopt against it." That is precisely what landed. My finding did note "the absent arm also has no falsifier of its own (deleting the `.packer_home = manifest.packer_home` copy keeps it green)" — but I stated that as an observation motivating the fix, not as an additional requirement, and the fix I prescribed does not close it. The implementer's disclosure is accurate and honest, and asking the panel rather than silently widening scope was the right call.

Three things make me comfortable ruling it closed rather than escalating.

1. The limitation is structurally real and correctly diagnosed. InstallTarget::packer_home carries a default member initializer (src/adapters/adapter.hpp:161). Deleting the designated initializer at sessions.cpp:271 therefore yields nullopt, which is indistinguishable at any behavioral seam from correctly transporting an absent value. No test that observes only behavior can separate those two worlds. That is not a testing shortfall; it is an identity.

2. The absent arm is nonetheless NOT vacuous — its falsification domain is non-empty. It rules out a class the engaged arm cannot: any implementation that FABRICATES a value at the leg. Replace the copy with a hardcoded PackerHome{"/Users/packer", posix}, or default the field to an engaged sentinel, or have the adapter synthesize one from $HOME at install time, and the engaged arm stays green while the absent arm goes RED. The two arms together bracket the transport: engaged proves the value flows, absent proves nothing is invented. Only the deletion case escapes, and it escapes because deletion and correct-absence are the same program.

3. Both candidate broader mechanisms are worse than the residual. A source-text assertion is the shape this repo has been burned by — a test that reads production source freezes file layout in a way no call-graph or symbol instrument can see, and it would go RED on an innocent refactor while STILL not proving the value reached the adapter. I reject it, and would reject it even if the limitation were more serious. The API change — dropping the default member initializer so InstallTarget aggregate-init fails to compile without the field, or routing construction through a factory that demands it — would genuinely close it, at compile time, which is stronger than any test. But InstallTarget is a sealed adapter-boundary type; changing its initialization contract is a sealed-behavior change and sits above this pair, per the repo's own rule that a fence over sealed behavior needs authority. That is a design-lane question, not a fold item.

So: my original finding is SATISFIED. Route the residual to RESIDUALS.md (master's to write) phrased narrowly — "absent-arm packer_home transport cannot behaviorally falsify deletion of the sessions.cpp:271 initializer, because InstallTarget::packer_home value-initializes to nullopt; closable only by removing the default member initializer, a sealed-boundary change" — and record the compile-time option so a future design lane can pick it up deliberately rather than rediscovering it. Do not let it gate this fold.
```

## VERBATIM REPORT — correctness/design-conformance lens

```
CORRECTNESS / DESIGN-CONFORMANCE LENS — R-4.8 packer-home carrier, targeted post-fold re-check

VERDICT: pass

PIN: 2bc7a078302f740721ac0d6412c843a8172368a5 (branch s4-matrix/r48-carrier), fold parent 29796bbe3929429d2d959278053089c5f852e5e2, BASE 6047ab0311491da5567c99f32b22ff14433fb1d2.
Graded against 91d6841:docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md, re-hashed at the blob: c1c3188be6f4b3de5db72555e285fd292697927adcb70cd2df6695a850260f57 — matches the dispatched c1c3188b…, so I graded the intended bytes.
Judged from committed blobs only (git show / git diff). Working tree never read, nothing built or run.

Both of my prior findings are closed. I found no correctness or conformance defect that rises to must-fix. Four sub-Major observations follow, then the MF-6 ruling.

=============================
1. PRODUCT CONFORMANCE AT THE BYTES
=============================

(a) packer_home_valid — src/core/manifest/manifest.cpp:463-480.
The classify-match guard runs first and compares std::optional<PathFlavor> against PathFlavor, so a disengaged classify (non-absolute, empty) is unequal and returns false before the switch — the design's stated subsumption of the old !path.empty() conjunct is real, not asserted. I walked every threshold at its boundary:

  posix            "/" (1) invalid                  | "/x" (2) valid
  wsl              "/mnt/c/" (7) invalid            | "/mnt/c/x" (8) valid
  windows drive    "C:/", "C:\" (3) invalid         | "C:/x" (4) valid
  windows extended "//?/", "\\?\" (4) invalid       | "//?/C" (5) valid

The extended-versus-drive discrimination inside the windows arm cannot be inverted in either direction, and I checked both spellings. A drive path can never satisfy either extended prefix because its first byte is an ASCII letter and its second is ':', so a drive path can never be handed the 4-byte threshold. In the other direction, classify_absolute returns windows only via the drive grammar or via one of those two exact prefixes, so an extended path always matches the prefix test in packer_home_valid and can never fall through to the 3-byte threshold. The two prefix spellings in the validator (manifest.cpp:475) are byte-for-byte the same pair used in the classifier (manifest.cpp:454), and both match rewrite_common.cpp:53's windows_extended_path. "/mnt/c" (6 bytes, no trailing slash) correctly falls out of the wsl branch and classifies posix, which is the design's stated wsl-before-posix precedence rather than a leak.

(b) make_packer_home — manifest.cpp:482-490.
Engaged iff classify is engaged and packer_home_valid holds. It routes through packer_home_valid rather than restating any threshold, so the postcondition ("an engaged result always satisfies valid()") is true by construction and not by parallel maintenance. I greped the whole tree at 2bc7a078 for a second copy of the threshold constants and of the two prefix literals: the only production sites are manifest.cpp:448/454/475 (the carrier's own single core), rewrite_common.cpp:44/53 (the parity anchor the design deliberately mirrors and pins with test 14), pack.cpp:133/256/261 (the untouched path_flavor and path_segments), and claude_code/install.cpp:95 / codex/install.cpp:64 (pre-existing adapter code). No second copy of the 1/7/4/3 thresholds exists anywhere. The std::move(value) in the ternary is evaluated only in the true branch after the predicate has read value, so there is no moved-from read.

(c) Capture — src/core/pack/pack.cpp:142-145 and :676.
packer_home_carrier is now exactly `return manifest::make_packer_home(home.generic_string());`, and the call site is the single field initializer `.packer_home = packer_home_carrier(env.home)`. Retaining the file-local wrapper is the design's own wording (§4 says the wrapper's *body* collapses into the factory call), so this is conformant rather than a deviation. The temporary from generic_string() outlives the string_view parameter for the whole full-expression, and the returned PackerHome owns its own string, so nothing dangles.

The R-4.12 boundary is clean. Diffing pack.cpp against BASE rather than against the fold parent — which is the only way to see work that entered before the panel window — shows the entire carrier delta is the five-line wrapper plus the one field initializer. path_flavor() at pack.cpp:131-140 and every source_path_flavor producer and consumer are byte-untouched at both SHAs. No semantic contact of any kind.

(d) Parse and serialize — manifest.cpp:538-543 and :630-651.
Both are byte-unchanged from 29796bbe; the diff touches only the 461-492 region. Serialize gates on `packer_home && packer_home_valid(*packer_home)`, so every degenerate engaged value collapses to both keys omitted. Parse rejects with detail exactly "packer_home" at :648 for the whole invalid class, and the degenerate rows reach that line rather than any earlier one. The \\?\C:\Users\x positive control from §8 stays valid: it classifies windows via the extended prefix, and its 14 bytes clear the 4-byte threshold. Wrong type is still optional_string's own detail "packer_home" (manifest.cpp:104/112), matching §8's row.

(e) §6 pairing detail.
The XOR at manifest.cpp:638-639 is a single has_value() != has_value() test returning "packer_home_flavor", so both directions produce the flavor key by construction — there is no second code path that could drift. The flavor-parse remap at :644 overrides the helper's hardcoded source_path_flavor detail (:462) locally, with the helper and its existing callers untouched.

(f) Fences and wire order.
src/core/scan/scan.cpp has an empty diff against the fold parent. The manifest fence — require_empty_array(object, "repos"), at manifest.cpp:597 in the design's BASE-relative numbering — is at :679 in the candidate, byte-identical; the whole-file diff against BASE is three purely additive hunks, so no existing statement changed at all. Emission order and adjacency for valid carriers are unchanged, and the fold newly pins them byte-exactly with a full-document string compare at tests/test_manifest.cpp:93-111 showing packer_home / packer_home_flavor immediately after source_path_flavor.

I also confirmed the tightening breaks no previously green row: every value in the round-trip spelling table (test_manifest.cpp:119-125) and the "/x" used by the flavor-error test is comfortably above its threshold.

=============================
2. MY TWO CLOSED FINDINGS
=============================

FINDING #1 (HIGH) — CLOSED, and closed as the panel actually ruled it.
One correction to the re-check charter's premise, because it matters for how the closure is recorded. The charter asks me to verify that "delete-the-assignment must go RED via the byte-identity comparison." It does not, and it was never supposed to. Deleting `target.packer_home = std::move(home)` from the test's own lambda leaves both arms nullopt, the bytes still match, and the test passes; deleting the production copy at sessions.cpp:271 is invisible to these two files entirely, because each builds its own InstallTarget through target_for(). What MF-4 prescribed verbatim was an *inertness* receipt — "install twice against identical fixtures, once engaged, once nullopt, and assert the produced store bytes are IDENTICAL; that is a real inertness receipt and fails the day an adapter starts interpreting the value." That is exactly what landed at tests/test_adapter_claude_install.cpp:545-579 and tests/test_adapter_codex_install.cpp:498-536, and it is genuinely falsifiable for a packer_home reason: the day any adapter reads the value into its output, the arms diverge and both tests go red. The §9-23 nullopt arm that was missing now exists as the second call. The transport falsifier lives in test_sessions, which is where it belongs. Closed.

The normalization is sound, and I verified rather than assumed it. "<installed-id>" is 14 bytes, so resuming the search at id_position + 14U (claude:569, codex:526) lands exactly one byte past the replacement — no skipped region, no rescan. More importantly I checked what else could vary between two runs. Claude mints a fresh uuid4() for the session id (claude_code/install.cpp:472) — normalized — and a fresh one for every distinct value of uuid, parentUuid, leafUuid, or sourceToolAssistantUUID found in the artifact (install.cpp:189-191, :267-272); the test fully replaces the main artifact with a single line carrying none of those keys, and record.children.clear() removes the child artifacts, so no message uuid is minted and the id map has exactly one entry. Codex mints a uuidv7 whose high bytes are the current millisecond (codex/install.cpp:107-124) — normalized — and the wall-clock file_stamp goes only into the rollout path components, never the content; the string "timestamp" appears nowhere in codex/install.cpp, so the fixture's own timestamp passes through unrewritten. The store directory differs between arms by design (root/"engaged" vs root/"absent"), and nothing in either installed body carries the store path. So the only run-varying token in the compared bytes is the session id, and it is the one thing normalized.

The content assertions the rewrite dropped (key-must-not-change, the 0.1 / 1.0 / 1e+03 / 18446744073709551615 number-fidelity checks, the workspace-path check) are not a coverage loss. They survive verbatim in the adjacent pre-existing tests at test_adapter_claude_install.cpp:582 and test_adapter_codex_install.cpp:539 — which is precisely what my original finding identified these receipts as clones of.

FINDING #3 (MED) — CLOSED.
CountingAdapter at tests/test_sessions.cpp:176-177 now accumulates a std::vector<std::optional<PackerHome>> and pushes per call at :198, so each leg is independently observable rather than overwritten. Both transport tests build two agents (fixture-agent-a, fixture-agent-b) and assert install_calls == 2U plus the full observed vector (:430-433, :464-467). I confirmed the two legs actually fire: run_session_leg keys eligibility on entry.agent == agent.agent (sessions.cpp:184), the fixture entries carry those two names, and nothing in the absent/unreadable/consent/store-lock guards short-circuits them. That satisfies §9-21's "identical for every adapter leg invoked" at the bytes. The tests also drop the now-unnecessary install_result.sessions seeding; with an empty session list run_session_leg simply produces no rows and returns its outcome (sessions.cpp:304-352), so REQUIRE(outcome) still holds and the assertions that carry the verdict are the call count and the observed vector, neither of which can pass vacuously. No stale singular seen_packer_home reference remains anywhere in tests/.

=============================
3. RULING ON THE MF-6 ABSENT-ARM LIMITATION
=============================

ACCEPT AS LIMITATION. No residual, no must-fix.

The implementer's disclosure is accurate and the reasoning is sound, and I want to be precise about why it is sound, because "the test can't fail" is normally the exact shape this repo treats as a defect.

Does §9-21/22's contract as written require the discrimination? No. Test 22 is specified as "Manifest without carrier → InstallTarget.packer_home == nullopt" — an assertion about the observed value, not a demand that deleting the initializer be distinguishable. My own MF-6 text raised the absent arm's lack of an independent falsifier as an observation and then prescribed a fix — "a second agent plus a per-call vector of observed values; assert both legs and the absent-arm nullopt against it" — which is what landed.

Is the engaged-arm falsifier sufficient kill power for the production copy? Yes, and this is the load-bearing point. There is exactly one transport statement in production, sessions.cpp:271, and it handles both cases: the absent case is not a separate code path, it is that same statement copying a nullopt. Deleting it turns the engaged test's observed vector into {nullopt, nullopt} against an expectation of {engaged, engaged} — red. So the deletion mutation is fully covered. And test 22 is not dead weight against the rest of the mutation space: any substitution mutation (say, defaulting to a synthetic PackerHome when the manifest carries none) fails test 22 and would pass test 21. The two arms jointly cover deletion and substitution; the single uncovered cell is "deletion, observed only through the absent arm," which is covered by the other arm. That is not a coverage gap, so there is nothing for a residual row to track, and registering one would put a no-work row into a registry this family has already been burned by treating as read.

The two ways to make it independently fail are both worse than the limitation. A source-text assertion is disfavored here for a specific, earned reason: it seals file layout invisibly to call-graph and symbol instruments, which is a defect shape this project has already paid for. An API or default change — dropping the {std::nullopt} default member initializer at adapters/adapter.hpp:161, or introducing a sentinel — is a production change made to force a test failure, smuggled into a test-only fold, and it would remove a defensive default that is correct on its own merits. Declining both and disclosing is the right call.

What would change this ruling: if the default member initializer at adapter.hpp:161 were ever removed, or if a second production statement began writing InstallTarget.packer_home, the absent arm would stop being redundant and would need its own falsifier. Worth a line in the fold record so the next seat knows the condition, but not a residual today.

=============================
4. FINDINGS
=============================

None are must-fix.

LOW — tests/test_adapter_claude_install.cpp:565-571, tests/test_adapter_codex_install.cpp:522-528.
The byte-identity comparison normalizes only the installed session id, and its soundness depends on a fixture property that nothing in the test states: the installed artifact must contain no uuid / parentUuid / leafUuid / sourceToolAssistantUUID field, and the record must have no children. Both hold today because the test replaces the main artifact wholesale and calls record.children.clear() at claude:546 / codex:498. If a later edit reintroduces any of those keys or restores the children, claude mints fresh random uuids per arm and the comparison fails for a reason unrelated to packer_home. That is a false-red hazard, not a false-green, so it cannot hide a defect — which is why it is LOW. If the fold wants to harden it, the honest move is to normalize every id in result->id_map rather than just the front one, which covers the children case without touching production.

LOW — tests/test_pack.cpp:207-209, 231-233.
The absolute-posix row now derives HOME from std::filesystem::temp_directory_path() (a good MF-5 fix — it removes the operator's real home) but still asserts a literal PathFlavor::posix. That expectation depends on the temp directory not living under /mnt/<drive>/. It holds on both CI hosts (macOS /var/folders/…, Linux /tmp), but this project's matrix includes WSL, where a TMPDIR under /mnt/c would classify wsl and turn the row red. A one-line precondition guard on the derived home — rather than deriving the expectation from classify_absolute, which would make the row tautological — closes it. Not worth blocking the fold.

INFO — src/core/manifest/manifest.cpp:475 versus :454.
The two extended-prefix spellings are tested in both the classifier and the validator. The thresholds themselves are single-sourced, and the §3 spec genuinely distinguishes drive from extended, so this duplication is inherent to the ruled predicate rather than drift. Flagging only so the next seat editing the classifier's extended grammar knows a second site must move with it.

INFO — no action recommended.
"//" (posix), "C://" (drive), and "/mnt/c//" (wsl) all clear non_degenerate because their remainder past the root prefix is a non-empty "/". This conforms exactly to the ruled Option A text, which defines the rule as a non-empty remainder and enumerates only the bare roots in §8, so tightening further would deviate from sealed wording. I checked whether it reopens the MF-1 threat and it does not: a "//" prefix matches only paths that literally begin with //, not the every-absolute-path fire-on-everything behavior MF-1 closed. Recording it as considered and cleared, not as a gap.

=============================
5. STRONGEST CHECKS THAT FAILED TO FIND A DEFECT
=============================

These are the places I expected to find something and did not, so the panel can judge the coverage of this pass rather than just its conclusion.

I hunted the moved-from and optional-misuse class in the new factory specifically: std::move(value) at manifest.cpp:488 is inside a ternary whose condition already read value, and the true branch is the only evaluated arm, so there is no read-after-move. I checked the aggregate-init shift in sessions.cpp:271 for designated-initializer order against the InstallTarget declaration order at adapter.hpp:157-161 — workspace_root, target_store, member_read, capabilities, packer_home — which matches, and the new member is last with a default initializer, so no existing construction site is invalidated. I checked that adding a defaulted friend operator== to PackerHome (manifest.hpp:24-28) does not destroy aggregate-ness, which the tests depend on for positional and designated init; a friend function is not a constructor, so the struct remains an aggregate.

I tried to find a threshold copy that would drift and could not: the whole-tree grep for both prefix literals and for the numeric thresholds turned up only the single carrier core and the deliberately-mirrored rewrite_common anchor, whose parity is pinned by test_manifest.cpp:304-312. I read rewrite::path_flavor_for (rewrite_common.cpp:626-634) to confirm the parity direction actually holds: it orders wsl before drive-or-extended before posix, identical to classify_absolute, and the two differ only where classify_absolute returns nullopt for non-absolute input while path_flavor_for returns posix — a difference the parity table correctly avoids by containing only absolute spellings.

I tried to break the wire in both directions and could not: the XOR pairing is one statement so it cannot drift between directions, and the fold's new tests now cover both lone keys, both null-with-partner combinations, both null-alone combinations, all six degenerate roots at parse, all six at serialize, the extended positive control, and a wrong-type flavor. I verified the tightening does not regress any previously green round-trip row by checking each spelling in the table against its threshold.

I checked whether the two test-side changes could pass vacuously. In test_sessions, dropping install_result.sessions does not weaken the verdict, because the assertions that carry it are the call count and the per-call observed vector. In the adapter receipts, the arms install into distinct stores from an identical fixture, so an accidental shared-state carryover between arms would show as a red, not a false green.

Finally I re-derived provenance against BASE rather than against the fold parent for every production file, since a commit inside the branch but before the review baseline reads as pre-existing from inside the panel window. The full carrier delta against 6047ab03 is purely additive in all five production files, which is what lets me say the Step-3 fences and every source_path_flavor path are untouched rather than merely unchanged since the last panel.
```

---

## LEAD SYNTHESIS

Per-lens verdicts (bare):
- security: pass (2 Low advisory)
- test-coverage: must-fix (2 Minor, one gating; 4 Nit/Observation)
- correctness/design-conformance: pass (2 Low, 2 Info)

**RE-CHECK VERDICT: REVIEW-FOLD required — a SECOND, bounded, TEST-ONLY fold of exactly
one gating Minor plus one recommended Minor.** The product bytes PASS all three lenses:
MF-1 is closed at every boundary value and every encoding, the thresholds are
single-sited, the factory postcondition holds by construction, the R-4.12 boundary is
clean against BASE (not merely against the fold parent), both fences are byte-identical
to BASE, and the leak/transport surface is unchanged. MF-2, MF-3, MF-4, MF-6 and rev4
tests 11b/13b/18b are confirmed genuinely non-vacuous by the test-coverage lens's
walk-throughs. The second fold touches NO production file.

### The second-fold set

**RF-1 (GATES — tests F-1).** MF-5's hermeticity guards never engage: the three
ScopedEnv values point at `(root / "codex")` / `(root / "claude")` which are never
created, and both adapters gate the env tier on `fs::exists`, so discovery falls back to
the HOME-derived default and FOUR of seven rows resolve `.claude`/`.codex` against the
test CWD — the second half of the original MF-5, reported closed but not landed ("the
fix moves the field without changing the outcome, the shape this repo has been bitten by
before"). Fix, BOTH halves per the lens: `create_directories` both store dirs before the
guards AND add `CHECK(report->agent_sessions.empty())` inside the row loop (the file's
own idiom at test_pack.cpp:287 — a direct falsifier that goes RED the moment any store
outside the fixture is discovered, on every row, regardless of tier).

**RF-2 (recommended — tests F-2, would not gate alone).** The byte-identity receipts
compare ONE file per arm, not the produced store file-SET; a sidecar/extra-artifact
interpretation path stays green. Fix: capture the sorted relative-file list alongside the
normalized content in both arms and assert lists AND per-file bytes match (codex already
computes `relative_files(store)`; claude needs the file-list read). Correctness's LOW
hardening rides the same lines if taken: normalize every id in `result->id_map`, not just
`front()`, removing the fixture-property coupling (a false-RED hazard today, not
false-GREEN).

**Optional tier (Implementer discretion, disclosed declines):** sibling temp ROOTS with
identical relative layout for the two arms (tests F-4); named `kIdPlaceholder` constant
replacing the magic 14U (tests F-5); split 13b's factory rows into their own TEST_CASE
(tests F-6); precondition guard on the temp-derived HOME's flavor for WSL-hosted TMPDIR
(correctness LOW).

### The routed cell — extended-spelling drive roots (tests F-3 ∥ security F3; design-level, above the pair)

`packer_home_valid`'s windows arm uses the ruled flat `>4` for extended spellings, so
`\\?\C:\` (7), `//?/C:/` (7), and `\\?\C:` (6) pass as non-degenerate. These are bare
drive roots — and the grammar already bans the analogous drive roots in every other
spelling: `/mnt/c/` (the WSL drive root) and `C:/` (the plain drive root) are degenerate,
while the SAME location spelled extended is admitted. The implementation conforms to
rev4 EXACTLY (the design says `>4` and glosses "bans only the bare 4-byte prefix"), and
the 11b/13b matrices enumerate exactly the design's rows — so this is a design-grammar
cell, not a fold defect, and it is sealed-contract material (the ruled Option A
thresholds came from the ruling verbatim). Security's adjacent F3 notes the structural
hazard: the extended-prefix discriminator lives in two sites with a PERMISSIVE fallback
(a future windows sub-form defaults to threshold 3), and the parity table cannot catch
it. ROUTED UP with both options; the second fold is HELD so the ruled outcome rides the
same single commit (the B2/MF-1 complete-amend pattern):
- **Option A (lead recommends):** tighten the extended threshold to `>7` (prefix + drive
  root), the tests lens's consistent value — same rationale as MF-1 itself (a bare drive
  root is not a usable reference frame; a needle given `\\?\C:\` fires on every
  extended-spelling path on that drive, exactly the class whose WSL twin the ruling
  banned), nil honest-packer cost, pre-needle timing, one design line + §8/§9 rows.
  Optionally fold security F3's structural fix (one helper returning the matched root
  length, fail-closed default) in the same pass.
- **Option B:** bless the narrow ban explicitly; pin the cell with an engaged-valid test
  row and a design gloss; carry a needle-side constraint. Either way the cell MUST be
  pinned — "an unpinned cell is how this comes back."

### MF-6 absent-arm limitation — adjudicated

Both assigned lenses rule the landed mechanism SATISFIES the original finding: the
engaged arm fully covers deletion of the single production transport statement
(sessions.cpp:271), the absent arm non-vacuously covers fabrication/substitution, and
the one uncovered cell (deletion observed only through the absent arm) is covered by the
other arm. Both lenses independently REJECT the source-text-assertion route (the earned
lesson: it seals file layout invisibly). Both note the same compile-time closure exists
— removing the `{std::nullopt}` default member initializer at adapter.hpp:161 — and both
agree it is a sealed adapter-boundary change above this pair. They split only on
bookkeeping: tests says register a narrow residual; correctness says no residual (a
no-work row in a registry this family was burned by treating as read) and record the
CONDITION instead. The lead records the condition HERE, which both positions require,
and surfaces the split to the orchestrator/master rather than resolving registry policy
at this seat:
**CONDITION (standing):** if the default member initializer at
`src/adapters/adapter.hpp:161` is ever removed, or a second production statement begins
writing `InstallTarget.packer_home`, the absent transport arm stops being redundant and
needs its own falsifier.

### Needle-head constraints surfaced by this re-check (ride R-4.10/R-4.11, NOT this branch)

- Security F2: the length thresholds admit padded roots (`//`, `/.`, `/mnt/c//`,
  `C:/.`, `//?/.`) that lexically normalize back to bare roots. Safe under the ratified
  verbatim-no-normalization contract; reopens ONLY if the needle normalizes before
  matching. Constraint: the needle must prefix-match the carrier VERBATIM, or re-apply
  `non_degenerate` after any normalization it performs. (Correctness independently
  considered and cleared the same class for the carrier itself.)

### Rejected / weak: none — every finding cites file:line at `2bc7a078`, and the two
conflicting cells were adjudicated at the bytes above rather than by lens confidence.

### Disposition

The bounded second fold (RF-1 + RF-2 + optional tier; test-only, ~3 test files) is HELD
until the extended-root cell is ruled, then dispatched as ONE commit with the ruled
outcome; its replacement head gets a TARGETED CHECK sized to the delta (lead + the
test-coverage lens, plus security iff option A changes the validator), not a full
re-panel — per the after-fold-ins rule. Human lenses remain unrouted until that check is
clean at the exact head. The branch stays LOCAL; publication by separate token; the
release hold is ABSOLUTE.
