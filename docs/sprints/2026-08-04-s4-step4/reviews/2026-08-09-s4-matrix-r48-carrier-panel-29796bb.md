# Rigorous review panel — R-4.8 packer-home carrier at `29796bbe3929429d2d959278053089c5f852e5e2`

DISPATCH_ID: s4-matrix-arm1-r48-panel
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-impl-r1-complete
CANDIDATE_SHA: 29796bbe3929429d2d959278053089c5f852e5e2 (branch `s4-matrix/r48-carrier`, LOCAL, unpublished; three task commits over BASE)
BASE: 6047ab0311491da5567c99f32b22ff14433fb1d2
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md (rev2, `349ef6e1…`)
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md (rev2, `438365bd…`)
LEAD: s4-matrix.planner (non-lens — no findings of its own, no re-grading of lens severities; synthesis and dedup only)
DATE: 2026-08-09

PANEL_CHOSEN: team-of-4 seats, FULL-BRANCH scope (first panel at this head; every lens pinned to the sealed candidate SHA and instructed to judge committed blobs via `git show`/`git diff` only — never the working tree)
DEFAULT_ROLES_CHANGED: yes — performance and idiomaticity merged into one seat (lowest residual-risk domains for a transport-only delta); correctness/design-conformance, security, and test-coverage kept dedicated seats
ROLES:
- correctness/design-conformance — product bytes vs locked design §§3-10; §8 parse table; §9 binding test list
- security — untrusted-image parse surface, validator bypass, leak surface, parse DoS, both Step-3 fences; four assigned probes
- test-coverage — §9 matrix mapping, non-vacuousness, absence-blindness walk, env hygiene, receipt honesty
- performance+idiomaticity (merged) — allocation/parse cost, per-agent copy amplification, match-this-file idiom
PANEL_COMPOSITION: four independent cold read-only subagents (r48-lens-correctness, r48-lens-security, r48-lens-tests, r48-lens-perf-idiom), each pinned to `29796bbe`, BASE `6047ab03`. Both pair seats excluded from lenses; this seat non-lens lead. No re-spawn.

## Spawn-count reconciliation

| lens seat | spawns | stalls | finding-sets |
|---|---|---|---|
| correctness | 1 | 0 | 1 |
| security | 1 | 0 | 1 |
| test-coverage | 1 | 0 | 1 |
| performance+idiomaticity | 1 | 0 | 1 |

4 spawns = 4 finding-sets + 0 stalls.

**Record-provenance disclosure (session boundary):** the lead seat crossed a context-window
boundary after all four reports were delivered but before this record was finished — the
prior write died at a 611-byte stub, which this file replaces.
The four reports below were recovered VERBATIM from the lead session's on-disk transcript
(`~/.claude/projects/-Users-jack-Programming-bivpak/1f839818-….jsonl`, the recorded
agent-message bodies), not reconstructed from memory; the test-coverage report appeared in
the transcript three times byte-identically (delivery retries) and is reproduced once.
Every load-bearing claim behind a must-fix was additionally RE-VERIFIED by the lead at the
sealed blobs after recovery (see lead verification below), so the synthesis does not rest
on the recovery alone.

## LEAD VERIFICATION (E1, at `29796bbe`, re-run post-recovery)

- Branch delta `git diff --name-only 6047ab03..29796bbe` = EXACTLY the ten dispatched
  paths (5 src, 5 tests); nothing else.
- Both Step-3 fences LIVE at the candidate: `scan.cpp` raises
  `RepoDiscoveredUnsupported` on a discovered `.git`; `manifest.cpp` calls
  `require_empty_array(object, "repos")` with its error checked.
- MF-1 evidence CONFIRMED: `packer_home_valid` = `!path.empty() && classify_absolute(path) == flavor`;
  `classify_absolute` returns posix for `"/"` (bare `starts_with('/')`), windows for
  `"//?/"`/`R"(\\?\)"` prefixes, wsl for 7-byte `/mnt/<alpha>/` — root-only spellings clear
  the validator.
- MF-2 evidence CONFIRMED: the only positional guard is
  `REQUIRE(json.find("\"source_path_flavor\"") < json.find("\"packer_home\""))`; the
  exact-bytes golden ("Manifest serializes in the locked field order") runs on
  `fixed_manifest()`, which never engages `packer_home` — carrier-absent layout only.
- MF-3 evidence CONFIRMED: no test fixture anywhere in `tests/test_manifest.cpp` at this
  SHA supplies a non-null, non-string `packer_home_flavor` (grep over the blob: zero hits).
- MF-4 evidence CONFIRMED: in both adapter "receipt" tests, `transported` appears exactly
  twice — declaration and `target.packer_home = transported;` — and is never read by any
  assertion.
- MF-5 evidence CONFIRMED: `tests/test_pack.cpp:229` row `{"absolute-posix", "/Users/jack", …}`
  is the operator's real home; the case pins HOME only (no `CLAUDE_CONFIG_DIR`/`CODEX_HOME`
  guards, unlike every sibling `pack()` test in the file).

---

## VERBATIM REPORT — correctness/design-conformance lens

```
CORRECTNESS / DESIGN-CONFORMANCE LENS — R-4.8 packer-home carrier
PIN: 29796bbe3929429d2d959278053089c5f852e5e2 (branch s4-matrix/r48-carrier), BASE 6047ab0311491da5567c99f32b22ff14433fb1d2
Graded against: 6047ab03:docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md (rev2, §§3-9 binding)
Judged from committed blobs only (git show / git diff). Working tree never read.

VERDICT: must-fix

The five product files are clean. I found NO divergence between the committed product bytes and the locked design, and no correctness defect in them. The must-fix is confined entirely to the test delta, where §9 tests 21 and 23 — a binding section — are not implemented as specified, and §7's Proof row makes a claim no committed assertion can falsify.

=============================
FINDINGS
=============================

1. HIGH — tests/test_adapter_claude_install.cpp:534 and tests/test_adapter_codex_install.cpp:484
   Defect: neither "receipt" test contains an assertion that can fail for a packer_home reason, and the nullopt arm required by §9 test 23 does not exist.
   Evidence: both new tests are line-for-line clones of the tests immediately following them ("Claude/Codex install rewrites escaped values without changing keys or numbers", claude:575 / codex:531), with exactly two lines added:
       const biv::manifest::PackerHome transported{"/Users/packer", biv::manifest::PathFlavor::posix};
       target.packer_home = transported;
   `transported` is never read again. Every REQUIRE/CHECK in both bodies is byte-identical to the adjacent pre-existing test and concerns rewrite escaping and number preservation. Delete the assignment line and the tests still pass. Break sessions.cpp's population of the field and they still pass, because each test builds its own InstallTarget via target_for(). The only new information carried is that the field is assignable — a compile-time fact.
   §9 test 23 requires BOTH arms ("observes the transported value when present AND the nullopt when absent"); no absent arm exists in either file. §7's Proof row rests "both adapter legs receive the value" on exactly these two files; nothing in them measures receipt.
   This is the known unfalsifiable-box shape. A falsifiable version is implementable today with no adapter seam: install twice against identical fixtures, once engaged and once nullopt, and assert the produced store bytes are identical — that actually falsifies the "inert metadata" the test name claims, and fails the day an adapter starts interpreting the value.

2. MED — tests/test_pack.cpp:222 (helper at :167)
   Defect: the capture test does not isolate the agent-store environment, unlike every sibling pack() test in the same file.
   Evidence: ScopedHome binds only HOME. Every other test in this file that calls pack() also binds the store variables — test_pack.cpp:286-288, :350-352, :609-610 each pair ScopedEnv{"HOME",...} with ScopedEnv{"CODEX_HOME",...} and ScopedEnv{"CLAUDE_CONFIG_DIR",...}. Without them, pack_impl's adapter->discover(env) (pack.cpp:542) consults the ambient CODEX_HOME/CLAUDE_CONFIG_DIR, so on any host where a developer or CI job exports them the test packs the operator's real agent stores into the fixture image. The packer_home assertion would survive that, but REQUIRE(report.has_value()) becomes hostage to the state of a real store. Separately, the "unset" row leaves env.home empty, so the default-tier probe degenerates to the RELATIVE paths ".claude"/".codex" resolved against the test process CWD.

3. MED — tests/test_sessions.cpp:398
   Defect: §9 test 21 requires the value be proven identical "for every adapter leg invoked"; the test invokes one leg.
   Evidence: preview.agents receives a single "fixture-agent" and the test asserts install_calls == 1U. The seam itself is also single-valued — CountingAdapter::seen_packer_home (test_sessions.cpp:176) is overwritten on each call, so even with two agents only the last would be recorded. §7's "both adapter legs receive the same image-level value by construction" is unmeasured. A second agent plus a per-call vector of observed values closes it.

4. LOW — tests/test_manifest.cpp:89 (guarding src/core/manifest/manifest.cpp:513-518)
   Defect: the key-POSITION half of the §3/§5 wire contract is unguarded.
   Evidence: §3 requires the pair be "emitted together immediately after source_path_flavor", home key first. The only positional assertion is
       REQUIRE(json.find("\"source_path_flavor\"") < json.find("\"packer_home\""));
   which is satisfied by any position after source_path_flavor — including after agent_sessions at the end of the object — and says nothing about the two keys being adjacent to each other or ordered home-then-flavor. The pre-existing exact-bytes test ("Manifest serializes in the locked field order") uses fixed_manifest(), whose packer_home is nullopt, so it pins the carrier-ABSENT layout only. The emitted bytes are correct; the guard is weaker than the clause the floor ratified at 050728. An exact-string assertion over the carrier-present serialization would pin it.

5. LOW — src/core/manifest/manifest.cpp:447 (classify_absolute) / :463 (packer_home_valid)
   Observation, NOT a divergence: degenerate-but-valid values clear the validator. classify_absolute accepts "/" -> posix, "//?/" -> windows, and "\\?\" -> windows, each of which then satisfies packer_home_valid as "non-empty, absolute, flavor-verified". A untrusted image can therefore ship "packer_home": "/" past parse. This conforms exactly to §3's grammar (which deliberately mirrors rewrite_common.cpp:43-53), and §7 already records the honest-packer limitation on the floor's side, so I am not grading it a defect — but the floor's needle must not treat a cleared carrier as a bounded prefix.

6. NIT — src/core/manifest/manifest.cpp:605-626
   The carrier parse block sits before require_empty_array(object, "repos") — the step2-plain-dir-only Step-3 fence (manifest.cpp:655 at this SHA; 597 at BASE). A manifest violating both now reports packer_home / packer_home_flavor instead of step2-plain-dir-only. Refusal is preserved in every case and the fence bytes are untouched, so §10's "both Step-3 fences unaffected" holds on the property that matters; only detail precedence moved, and no fixture combines the two.

7. NIT — design wording, code is right. §6 describes presence-XOR as "ParseError naming the lone key ("packer_home" or "packer_home_flavor")", implying two possible details; §8's exhaustive table and its closing paragraph resolve BOTH directions to packer_home_flavor. manifest.cpp:613-615 returns packer_home_flavor unconditionally, matching §8. Worth tightening §6 at the next rev so a future reader does not "correct" the code toward the looser sentence.

8. NIT — tests/test_pack.cpp:167. ScopedHome duplicates ScopedEnv (:140) with an optional value, and unlike ScopedEnv deletes only the copy operations, not the move ones. Harmless (a user-declared destructor already suppresses implicit moves) but inconsistent with its sibling one screen above. Generalizing ScopedEnv to take std::optional<std::string> would remove the second class.

9. NIT — no fuzz corpus seed carries the keys. fuzz/corpora/manifest/seed1.json and harness/fuzz/corpus/manifest/golden.json are both pre-carrier, so the new parse branch is reachable only by mutation from a corpus that has never seen the key names.

=============================
STRONGEST CHECKS THAT FAILED TO FIND A DEFECT
=============================
(the product half is approve; these are the checks I expected to break and did not)

- env snapshot identity, verified at the bytes rather than from the report's word. process_env() has exactly ONE call site in the whole file, pack.cpp:538 (definition at :241). `const auto env` at :538 sits at two-space function-body indent and manifest_model at :673 sits at the same indent; the only intervening brace pair is the nested block at :636-671. So packer_home_carrier(env.home) at :681 reads the identical snapshot the adapters were discovered and collected with. No second process_env() exists anywhere in src/.

- Mid-struct insertion shifting a positional aggregate init. Enumerated EVERY construction site of both changed structs across src/, tests/ and fuzz/: Manifest at pack.cpp:673, test_manifest.cpp:23, test_open.cpp:79, and test_sessions.cpp:49 (field-by-field, not aggregate); InstallTarget at sessions.cpp:267, test_adapter_claude_install.cpp:269, test_adapter_codex_install.cpp:186. All seven use designated initializers in declaration order, so no member can silently shift. The default member initializer keeps both structs aggregates, and the two adapter helpers that omit the field get nullopt.

- Backslash spellings surviving the round trip. §9 test 3 asserts C:\Users\x and \\?\C:\Users\x round-trip; that depends on json::Writer::write_escaped (src/core/json/writer.cpp), which escapes '"', '\\' and every byte below 0x20 — so those windows rows are genuinely exercised, not passing by accident.

- Classifier parity compared grammar-to-grammar rather than trusting the parity test. manifest.cpp:447-461 vs rewrite_common.cpp:43-53: the wsl branch matches on all three conjuncts including the size()>=7 guard, the ascii-alpha drive and path[6]=='/'; the windows branch matches on the drive form (both separators) and both extended spellings (R"(\\?\)" is the same four bytes as rewrite's "\\\\?\\"). The only difference is the intended §3 one — rewrite falls through to posix, the carrier returns nullopt. Corner rows check out: /mnt/C/ -> wsl (both layers accept uppercase drives), /mnt/cc/ -> posix, C:/ -> windows, C: -> nullopt, C:x -> nullopt, "" -> nullopt, and every .at() is size-guarded so the fuzzer cannot reach an out-of-range throw.

- Wire-compat blast radius on CI. harness/schemas/manifest-plaindir-v1.schema.json is additionalProperties:true at the top level and does not list the new keys as required, so every image that now carries the pair still validates. schemas/biv-json-envelope.v1.schema.json is unaffected because write_pack_result (src/core/report/envelope.cpp:132-146) builds from PackReport, not Manifest, and never surfaces the carrier. No golden fixture compares manifest bytes.

- Parse-branch walk, all eight paths against §8. Type errors on either key are checked BEFORE the pairing test, so {"packer_home": 42} alone yields detail packer_home rather than a pairing error — which is what §8 specifies. Both null combinations, both XOR directions, the local unknown-flavor remap, and all five validator rejections conform. On move semantics: optional_string returns expected<std::optional<std::string>> holding an OWNING copy (manifest.cpp:100-115), not a simdjson view, so std::move(**packer_home_text) at :621 moves a heap string with no dangling into the padded_string, and the moved-from optional is never read again (packer_home_flavor_text is a separate object, dereferenced at :617 before the move).

- Transport containment. Exactly one "->install(" call site in all of src/ (sessions.cpp:267), exactly one InstallTarget construction site, and the only core reference to the field anywhere is the single copy `.packer_home = manifest.packer_home` at sessions.cpp:271. No core path reads, tests, or performs any path operation on the value.

Recommended disposition: product bytes approve as-is; fixes for findings 1-3 are test-only and do not touch the sealed wire shape, so no floor re-route is owed.
```

## VERBATIM REPORT — security lens

```
SECURITY LENS — R-4.8 packer home carrier @ 29796bbe3929429d2d959278053089c5f852e5e2 (BASE 6047ab03)

VERDICT: must-fix (one finding; everything else is approve-grade)

The core transport claim holds — no path from parsed bytes to any filesystem operation. The one real hole is that the validator's admitted set includes root-only / prefix-only spellings, handing a untrusted image author byte-level control of the future needle's reference frame for the cost of one character.

===================================================================
F1 — MEDIUM (must-fix). Validator admits degenerate roots; untrusted image controls the needle's reference frame
===================================================================
src/core/manifest/manifest.cpp:463 — packer_home_valid = !path.empty() && classify_absolute(path) == flavor. "Non-empty + absolute" is satisfied by the bare root of every flavor, so all of the following parse successfully and land in InstallTarget.packer_home:

  "packer_home":"/",           "packer_home_flavor":"posix"    -> posix   (starts_with('/'))
  "packer_home":"/mnt/c/",     "packer_home_flavor":"wsl"      -> wsl     (size==7, at(5)='c', at(6)='/')
  "packer_home":"C:/",         "packer_home_flavor":"windows"  -> windows drive (size==3)
  "packer_home":"//?/",        "packer_home_flavor":"windows"  -> windows extended
  "packer_home":"\\\\?\\",     "packer_home_flavor":"windows"  -> windows extended  (JSON source bytes: backslash-backslash-?-backslash)

The contract this delta seals is "present => non-empty absolute in its verified flavor". "/" satisfies the letter and destroys the spirit: it is relative-in-practice as a reference frame. A needle that searches session artifacts for the packer's home substring, given packer_home = "/", matches every absolute POSIX path in every artifact. "/mnt/c/" matches every WSL-mounted path; "//?/" matches every extended-length Windows path.

This is materially different from the ratified honest-packer limitation, and I am not re-litigating that limitation. Omitting the pair makes the needle SKIP (ratified, fail-open, silent). Setting "/" makes the needle FIRE ON EVERYTHING — a untrusted image can flood a restore with false positives, which either blocks a legitimate restore or trains the operator to disregard the needle's output. Corrupting a control is a different risk from disabling it, and only the disabling case is on record.

Fix here, not in the needle: packer_home_valid is the sealed boundary, and per the fences-over-sealed-behavior rule, changing it after the needle lands is itself a sealed-behavior change. Narrowest prohibition — require a non-empty remainder after the flavor's root prefix:
  posix: size() > 1
  wsl: size() > 7
  windows drive: size() > 3
  windows extended: non-empty remainder after the 4-byte \\?\ / //?/ prefix (ideally drive + separator + component)
Cost of the ban is nil for real packers: HOME=/ degrades to absent, which is the already-ratified skip path and strictly safer than a "/" frame. HOME=/mnt/c/ and HOME=C:\ are not plausible home directories.

===================================================================
F2 — LOW. C0 control characters and embedded NUL survive parse into PackerHome.path
===================================================================
src/core/manifest/manifest.cpp:605-625. optional_string yields simdjson's unescaped string, so JSON \u0000 produces a std::string with an embedded NUL and \u001b produces a raw ESC. Neither classify_absolute nor packer_home_valid inspects anything past the prefix. Both of these parse clean:
  "packer_home":"/home/u\u0000/x","packer_home_flavor":"posix"
  "packer_home":"/home/\u001b[2J\u001b[1;1H","packer_home_flavor":"posix"
No reachable abuse at this SHA (nothing reads the field). Two forward hazards: an embedded NUL converted to std::filesystem::path silently truncates at c_str(), so a length-based match and a syscall would disagree about the same value; and an ESC sequence reaching operator-facing output is terminal-escape injection.
PARTIALLY MITIGATED ALREADY: src/core/open/render.cpp:56 display() and :78 display_path() escape C0/DEL/C1, and every rendered string in that file goes through them. The render layer is defended by convention. Rejecting C0/DEL at parse would make it structural rather than a convention the needle must remember to follow. Recommend, do not block.

===================================================================
F3 — LOW. packer_home_flavor carries zero independent information; WSL-shaped POSIX homes are mislabeled
===================================================================
packer_home_valid requires classify_absolute(path) == flavor, and classify_absolute is a pure function of path. The flavor key is therefore fully redundant on the parse side — a mismatched pair cannot decouple them (a genuine strength; I tried). Consequence: a legitimate non-WSL Linux packer with HOME=/mnt/d/home/bob (a mounted second drive) is recorded flavor: wsl, and the needle's flavor-driven spelling derivation will re-spell it as a Windows path. Correctness-lens overlap; noted because it affects what the needle matches.

===================================================================
F4 — INFORMATIONAL. No length bound on packer_home; duplicate-key differential
===================================================================
No explicit cap on the string; bounded only by the 16 MiB manifest cap (src/core/manifest/manifest.hpp:14, kManifestByteCap = 16U << 20), re-checked inside parse at manifest.cpp:546 independent of the caller — good. Consistent with source_path, which is also uncapped. Separately, simdjson DOM at_key takes the FIRST duplicate key; a parser that takes the last would read a different packer_home from the same bytes. No second consumer of manifest.json exists in the tree, so latent only.

===================================================================
F5 — INFORMATIONAL. Silent carrier-absent has no report surface
===================================================================
src/core/pack/pack.cpp:142 returns nullopt when HOME is unset, empty, or relative; src/core/manifest/manifest.cpp:513 silently drops an engaged-but-invalid pair at serialize. Both produce an image with no carrier and no warning. The consequence (absent => skip) is ratified and I am not re-litigating it; the narrower point is that no field in the pack report tells an operator whether the carrier was emitted, so "the needle ran and found nothing" is indistinguishable from "the needle never ran". Worth a RESIDUALS.md row against the needle work rather than a change here.

===================================================================
ANSWERS TO THE FOUR ASSIGNED PROBES
===================================================================
1. TRANSPORT-ONLY — CONFIRMED. `git grep -n packer_home 29796bb -- src/` returns exactly five sites: the Manifest field (manifest.hpp:73), the InstallTarget field (adapter.hpp:161), serialize (manifest.cpp:513-517), parse (manifest.cpp:605-625), and pack (pack.cpp:142, :681). ZERO reads in src/adapters/ — no adapter, including both install.cpp files, touches target.packer_home. The single consumer is the copy at src/core/open/sessions.cpp:271. Nothing concatenates it, converts it to std::filesystem::path, or passes it to a syscall. Path traversal (/home/../../etc/shadow) parses fine and goes nowhere: never joined, canonicalized, or opened.

2. LEAK SURFACE — CLEAN. The only new read of the environment is env.home at pack.cpp:681, sourced from getenv("HOME") at pack.cpp:251. No other env value added. packer_home appears in NO report path: src/core/report/envelope.cpp emits source_path/source_path_flavor (:135-137) and nothing new; src/core/open/render.cpp:264 prints only source_path. No new log or warning line on either side. manifest.json is read in memory on open (open.cpp:222, :537) and is never extracted into the restored workspace. Mitigating context: source_path already put an absolute host path in the manifest, so packing from under ~ disclosed the home transitively before this delta.

3. VALIDATOR BYPASS — see F1. The flavor cannot be desynchronized from the path (F3), but the root-only spellings pass.

4. PARSE DOS — CLEAN. classify_absolute is a fixed set of prefix comparisons and three bounds-guarded .at() reads, all O(1); every .at() is protected by a preceding size check (>= 7U before at(5)/at(6), >= 3U before at(0..2)), and starts_with is safe on short input. No loops, no recursion, no allocation beyond the one std::string copy optional_string already performs. The delta adds two at_key lookups to a function that already performs ~15; at_key is a linear key scan, so worst case is ~2M keys x 17 lookups on a 16 MiB manifest — tens of millions of comparisons, not a DoS, and a constant factor on a pre-existing pattern rather than a new class. The per-agent InstallTarget copy is inside a loop over the fixed adapter set, not the session list.

5. FENCES — BOTH LIVE AT 29796bb. RepoDiscoveredUnsupported is raised at src/core/scan/scan.cpp:138 (std::unexpected(BivError{ErrKind::RepoDiscoveredUnsupported, child.path().generic_string()})) and rendered at src/core/report/envelope.cpp:398. require_empty_array(object, "repos") is called at src/core/manifest/manifest.cpp:654 with its error checked, and the helper at :81-95 rejects any non-empty array with detail "step2-plain-dir-only".

===================================================================
STRONGEST ATTACKS THAT FAILED
===================================================================
- JSON injection via a crafted home breaking out of the string into sibling manifest keys. json::Writer::write_escaped (src/core/json/writer.cpp:142) escapes '"', '\', and every byte < 0x20 as \u00XX. A packer_home of /home/u", "image_id": "evil re-serializes fully escaped. No breakout.
- Non-UTF-8 / lone surrogates. simdjson validates UTF-8 across the whole document and rejects malformed \uD800 escapes before the new block is reached; the error is caught by the simdjson_error handler at manifest.cpp:665.
- Flavor/path desynchronization (e.g. claiming "C:\\Users\\x" with flavor "posix" to make a Windows path be treated as POSIX). Rejected: packer_home_valid recomputes the flavor from the path. Covered by tests/test_manifest.cpp "packer_home malformed values fail closed naming the home key".
- Half-pair smuggling. packer_home without packer_home_flavor, or vice versa, including null on either side (optional_string maps null to absent), fails closed at manifest.cpp:613 with detail "packer_home_flavor". All five null/lone-key permutations are tested.
- Classifier divergence between the carrier and the rewriter. classify_absolute (manifest.cpp:471) is a structural clone of wsl_mount_path / windows_drive_path / windows_extended_path (src/adapters/rewrite_common.cpp:43-54) in the same precedence order, differing only by adding the POSIX branch and returning nullopt instead of falling back to posix. Compared predicate by predicate; on the absolute domain they agree, and a test pins that agreement. Note for the record: src/core/pack/pack.cpp:131 path_flavor, used for source_path_flavor, is a FOURTH, weaker copy of the same grammar with no windows branch at all — so source_path_flavor can never be windows while packer_home_flavor can. Pre-existing, not introduced here, but four copies of one grammar is a divergence waiting to happen.
- Unbounded amplification through the install loop. See probe 4.
```

## VERBATIM REPORT — test-coverage lens

```
TEST-COVERAGE LENS — R-4.8 packer-home carrier, candidate 29796bbe3929429d2d959278053089c5f852e5e2, BASE 6047ab0311491da5567c99f32b22ff14433fb1d2. Judged from committed bytes only (git show/git diff); no build, no run, no edits.

VERDICT: must-fix (2 Major, 6 Minor, 1 advisory)

MATRIX: 19/23 fully mapped, 4 partial, 0 missing outright.
Partial list: design §9-10 (relative value "each flavor declared" — 1 of 3 declared flavors), §9-11 (mismatch matrix — 2 of 4 enumerated rows), §9-21 (transport "identically for every adapter leg invoked" — one leg only), §9-23 (adapter receipt — present half only; the nullopt-when-absent half is unasserted).

BLAME FRAMING (load-bearing for the fold): every case-level shortfall in findings 3-7 is already present in the plan's own literal code blocks at 6047ab03 (Step 1.1 / 2.1 / 3.1). The implementer reproduced those blocks essentially byte-faithfully; the reduction from design §9 happened at PLAN-authoring time, not at implementation time. Findings 1 and 2 are the exceptions — those are gaps neither the plan nor the implementation caught.

FINDINGS

1. MAJOR — the sealed wire POSITION is not pinned; relocating the emit block stays green.
   File: tests/test_manifest.cpp:88 at 29796bb (and the un-extended golden at tests/test_manifest.cpp:237).
   Gap: the only ordering assertion is `REQUIRE(json.find("\"source_path_flavor\"") < json.find("\"packer_home\""))`. FLOOR_CONTRACT seals the wire shape and the plan's Global Constraints say the pair is emitted "right after `source_path_flavor`", but adjacency is never tested.
   Evidence: move the emit block at src/core/manifest/manifest.cpp:513-518 to after the `repos` array and all fifteen new TEST_CASEs still pass, because `repos` also follows `source_path_flavor`. The repo already owns the correct instrument and it was not extended: TEST_CASE("Manifest serializes in the locked field order") at tests/test_manifest.cpp:237 asserts a full JSON literal but runs on `fixed_manifest()`, whose `packer_home` is `nullopt` — so the golden is structurally blind to the carrier. Cheapest remedy: a carrier-engaged variant of that golden (full literal), or at minimum `REQUIRE(json.find("\"packer_home_flavor\"") < json.find("\"bivignore\""))`.

2. MAJOR — one branch of the new parse block is unreached by any test.
   File: src/core/manifest/manifest.cpp:610-611 at 29796bb (`if (!packer_home_flavor_text) { return std::unexpected(packer_home_flavor_text.error()); }`).
   Gap: that branch fires only when `packer_home_flavor` is a non-null, non-string JSON value. Walking every injected fixture at 29796bb, the flavor key is only ever a string ("posix", "windows", "vms"), `null`, or absent — never a wrong type.
   Evidence: the home-key twin IS covered (tests/test_manifest.cpp:188, the `"packer_home":42` row), so the asymmetry is an oversight rather than a design choice. This is the wire's fail-closed rejection path and its detail string (`packer_home_flavor`) is unguarded — a refactor collapsing it to the generic `packer_home` detail would go unnoticed. Fix: one row `"packer_home":"/x","packer_home_flavor":42,` expecting `detail == "packer_home_flavor"` — it belongs in a flavor-detail case, NOT in the `packer_home`-detail array at tests/test_manifest.cpp:186.

3. Minor — design §9-11 mismatch matrix is half-populated.
   File: tests/test_manifest.cpp:191-192 at 29796bb.
   Gap: present rows are posix-path-declared-`windows` and `/mnt/c/...`-declared-`posix`. Design §9 line 245 also enumerates posix-path-declared-`wsl` and `C:\...`-declared-`posix`.
   Evidence: all four traverse the same `packer_home_valid` false branch (manifest.cpp:622) and the classifier unit rows pin each spelling independently, so material risk is low — but the absent row `C:\...` declared `posix` is precisely the one that would independently falsify the classifier's windows-before-posix ordering.

4. Minor — design §9-10 "relative value (each flavor declared)" is one row, not three.
   File: tests/test_manifest.cpp:190 at 29796bb — only `"relative/home"` declared `posix`.

5. Minor — §9-21 is proven on a single leg, and the absent case has no falsifier of its own.
   File: tests/test_sessions.cpp:398 (present) and :437 (absent) at 29796bb.
   Gap/evidence: the preview is built with one `AgentPreview`, so "identically for every adapter leg invoked" is not demonstrated (there is exactly one `InstallTarget` construction site at src/core/open/sessions.cpp:267, so a second leg is the same code path — the risk is presentational, not behavioral). Separately, the absent case would stay GREEN if `.packer_home = manifest.packer_home` were deleted outright, because both `CountingAdapter::seen_packer_home` and the new `InstallTarget` field default to `nullopt`. The present case at :398 is the sole transport falsifier.

6. Minor — classify_absolute negative branches at the boundary are untested.
   File: tests/test_manifest.cpp:208-224 at 29796bb.
   Gap: never reached — `/mnt/c` (length 6, fails the `size() >= 7U` guard and falls through to posix), `/mnt/1/x` (fails `carrier_ascii_alpha(path.at(5))`), `1:/x` (fails `carrier_ascii_alpha(path.at(0))`). The positive grammar rows are complete.

7. Minor — the pack table's absolute row uses the operator's real home path.
   File: tests/test_pack.cpp:227 at 29796bb (`Row{"absolute-posix", "/Users/jack", ...}`).
   Gap/evidence: `pack()` runs real adapter discovery against `env.home` (src/core/pack/pack.cpp:241-256, consumed at :538), so on the operator's own mac this unit test enumerates the live ~/.claude and ~/.codex stores. No assertion depends on the result, so it is not a false green, but it makes runtime host-dependent and embeds a personal path in a fixture. The file's own idiom at tests/test_pack.cpp:286 / :350 / :610 is `(root / "home").string()` — same posix-absolute branch, hermetic.

8. Advisory — the adapter receipt cases are compile-time falsifiers only, and skip the assertions that will matter when the floor needle lands.
   Files: tests/test_adapter_claude_install.cpp:534 and tests/test_adapter_codex_install.cpp:484 at 29796bb.
   RECEIPT HONESTY: PASS. I diffed both against their donors ("Claude/Codex install rewrites escaped values without changing keys or numbers", at :575 and :531 respectively) — the copies are byte-identical plus exactly two carrier lines; zero assertions were dropped, weakened, or reordered.
   Caveat: no adapter .cpp reads the field (the src diff touches only adapter.hpp:161), so the runtime half cannot discriminate anything — the only real falsifier is that `target.packer_home = transported;` would not compile without the field. The donor chosen also omits the verify-count assertions (`verify.origin_path_hits == 0`, `verify.artifacts_checked`) that the larger install case carries, and those are exactly what would catch a future needle making the field non-inert.

NON-VACUOUSNESS: PASS on every major arm.
- Parity table (tests/test_manifest.cpp:226-234) genuinely calls the production `biv::adapters::rewrite::path_flavor_for` (src/adapters/rewrite_common.cpp:626, built on independent helpers at :43-54). `classify_absolute` is a hand-copied re-implementation in a different TU, so the two can really drift and the table would catch it. Not vacuous.
- Unknown-flavor case is a true remap falsifier: `parse_path_flavor` returns `detail == "source_path_flavor"` (manifest.cpp:479), so without the local remap at manifest.cpp:619 the exact-string assertion goes red.
- Serialize-collapse case constructs genuinely invalid engaged values ({"" ,posix}, {"relative/home",posix}, {"/home/user",windows}) and goes red without the `&& packer_home_valid(...)` guard at manifest.cpp:513. Its `find("packer_home") == npos` check also catches a lone `packer_home_flavor` emission, since that spelling contains the substring.
- Both transport cases assert `install_calls == 1U` BEFORE reading the mutable capture, so neither can pass on a skipped install.
- No tautologies found: every round-trip assertion routes the test-set value through serialize→parse or a real `install()` call before comparing.

ABSENCE-BLINDNESS / parse-block walk (manifest.cpp:605-626): branch `!packer_home_text` covered (`42` row); `!packer_home_flavor_text` UNCOVERED (finding 2); has_value() mismatch covered four ways (lone_home, lone_flavor, null+flavor, home+null-flavor); `parse_path_flavor` failure covered ("vms"); `!packer_home_valid` covered (empty, relative, two mismatches); success path covered by the round-trips.

ENV HYGIENE: PASS. `ScopedHome` (tests/test_pack.cpp:167-192) copies prior HOME into a `std::string` before calling setenv, restores set-or-unset symmetrically in the destructor, and that destructor runs during Catch2's exception unwind on a REQUIRE failure. It is constructed AFTER `make_tmp` (which reads TMPDIR, not HOME) and scoped inside the loop body, so rows are independent. The unset row genuinely calls `unsetenv`, and `process_env` returns an empty `std::filesystem::path{}` for it (pack.cpp:250-255), which classifies to `nullopt`. One note: rows 16 (unset) and 17 (empty) collapse to the identical empty-string input at the carrier, so neither can falsify the other — both are mapped but they are not independent instruments. `make_tmp` collision risk across the two new adapter receipt cases is nil: the prefixes differ per file (biv-claude-install- / biv-codex-install-) and each does remove_all before create_directories.

Cross-check on count: 15 new TEST_CASEs (manifest 10, pack 1, sessions 2, adapters 2), consistent with the plan's Step 3.7 "fifteen new TEST_CASEs" disclosure for the R-3.48 count-gate red.
```

## VERBATIM REPORT — performance+idiomaticity lens

```
COMBINED PERFORMANCE + IDIOMATICITY LENS — R-4.8 packer_home carrier
Candidate: 29796bbe3929429d2d959278053089c5f852e5e2 (branch s4-matrix/r48-carrier)
BASE: 6047ab0311491da5567c99f32b22ff14433fb1d2
Read-only; judged from committed blobs via `git show 29796bb:PATH` / `git diff 6047ab03 29796bb`. Working tree never consulted.

VERDICT: approve

No Critical and no Major within my two lenses. One Major outside my remit is raised at the end because I hit it while tracing the pack path; it belongs to the tests/hygiene lens.

=====================================================================
PERFORMANCE FINDINGS
=====================================================================

P1 — Nit — src/core/pack/pack.cpp:142-150
Issue: `const auto text = home.generic_string();` makes the string unmovable, so
`return manifest::PackerHome{.path = text, .flavor = *flavor};` COPIES it. One avoidable
heap allocation per pack invocation.
Evidence: the declaration is `const auto`, and `.path = text` binds an lvalue, so the
PackerHome member is copy-constructed. Dropping the const and writing
`.path = std::move(text)` removes the copy. Cold path (once per pack), hence Nit, not a
fix I would hold the branch for.

No other performance findings.

WHAT I CHECKED HARDEST (perf), all clean:

(a) parse allocation trace — exactly ONE allocation for the carrier, the minimum the
existing helper signature permits. `optional_string` (manifest.cpp:99-115) builds one
std::string from the simdjson view; manifest.cpp:621 `std::move(**packer_home_text)`
moves it into PackerHome; manifest.cpp:625 `manifest.packer_home = std::move(value)`
move-constructs into the optional. No hidden copy anywhere in the chain. The flavor
string ("posix"/"windows"/"wsl", <=7 chars) stays in SSO and never touches the heap.

(b) parse added cost on every archive open — two additional
`simdjson::dom::object::at_key` scans over a root object of ~8 keys. Noise against
decompressing up to the 16 MiB cap.

(c) classify_absolute (manifest.cpp:446-461) is O(1) — prefix and index comparisons only,
no allocation, cost independent of path length. Runs at most once per parse (inside
packer_home_valid) and once per serialize. The `.at()` bounds checks are guarded by the
preceding size tests and match rewrite_common.cpp:44-49's own idiom exactly.

(d) serialize (manifest.cpp:513-518) adds one `to_string` returning an SSO string,
identical to what the adjacent source_path_flavor line already does.

(e) THE PER-AGENT COPY YOU FLAGGED — sessions.cpp:271 `.packer_home = manifest.packer_home`
does copy the optional<PackerHome> once per loop iteration, and the loop at :175 is per
agent. I chased whether that count is externally influenced, since `preview.agents` gets one
entry per DISTINCT `entry.agent` string in the manifest (sessions.cpp:113-133) and a
untrusted image controls those strings. It is NOT reachable: every unknown agent takes the
`!agent.known_adapter` branch (sessions.cpp:~185), leaves `eligible` empty, and hits
`continue` well before the InstallTarget construction site. So the copy count is bounded by
the adapter registry = 2. Further, InstallTarget already copies `Store` (a path plus a
vector of locators) and `Capabilities` (a string plus optional<ProbeEvidence>) at that same
site, so the new field costs strictly less than what the struct already pays. Not a finding;
no change recommended.

(f) No behavior change to existing rows. The emit is guarded on
`packer_home && packer_home_valid(...)` (manifest.cpp:513), so a manifest without the
carrier serializes byte-identically to BASE. `optional_string` returning an empty optional
on simdjson::NO_SUCH_FIELD (manifest.cpp:101-102) means pre-carrier images parse unchanged.

=====================================================================
IDIOMATICITY FINDINGS
=====================================================================

I1 — Nit — src/core/manifest/manifest.cpp:439-443
Issue: the delta closes the file's single anonymous namespace at :437 and IMMEDIATELY
opens a second one holding one helper, closing it again at :443.
Evidence: the first block (:23-437) already holds every file-local helper in the file
(required_string, optional_string, write_agent_session, ...). The new helper belongs in
it; the second block reads as an accretion seam.

I2 — Nit — src/core/manifest/manifest.cpp:441
Issue: `carrier_ascii_alpha` diverges in name from three pre-existing byte-identical
copies of the same predicate, all named `ascii_alpha`.
Evidence: src/adapters/rewrite_common.cpp:39, src/adapters/claude_code/install.cpp:75,
src/adapters/codex/install.cpp:58. I checked whether the `carrier_` prefix buys ODR
safety and it does NOT — all three prior copies sit inside anonymous namespaces
(rewrite_common.cpp:21, claude_code/install.cpp:39, codex/install.cpp:29), and two of them
coexist inside the SAME named namespace `biv::adapters` in different TUs for exactly that
reason. A fourth copy named `ascii_alpha` in manifest.cpp's anonymous namespace would be
equally safe. The design's own §3 sketch writes it as `ascii_alpha(path[5])`. The new copy
also flips the branch order (lowercase range first; rewrite_common.cpp:40 tests uppercase
first), suggesting it was retyped rather than transcribed.
NOT flagged: the grammar duplication itself — design-ruled §3, parity-pinned by
tests/test_manifest.cpp:226-235.

I3 — Minor — tests/test_pack.cpp:167-192
Issue: `ScopedHome` reimplements `ScopedEnv`, defined 27 lines above at :140-165.
Evidence: ScopedEnv has fifteen call sites in the same file, THREE of them literally
`ScopedEnv home{"HOME", ...}` (:286, :350, :610). The only capability ScopedEnv lacks is
unsetting, since its ctor always calls setenv (:147). Widening its value parameter to
`std::optional<std::string>` covers the new rows and leaves all fifteen existing call
sites compiling unchanged — the smaller and more conventional change. Secondary evidence
that this is a partial clone: ScopedEnv deletes all four copy AND move operations
(:157-160); ScopedHome deletes only the two copy ones (:186-187).

I4 — Nit — tests/test_manifest.cpp:80-235
Issue: TEST_CASE naming diverges from the file's unanimous convention.
Evidence: all ten new names lead with the lowercase symbol under test ("packer_home ...",
"classify_absolute ..."); all ten pre-existing names in the file lead with a capitalized
subject ("Manifest serializes ...", "Manifest parser ..." at :237, :259, :273, :287, :308,
:317, :344, :374, :421, :439). Ten for ten. Naming after the symbol is defensible in the
abstract, but this lens is match-this-file.

I5 — Minor — tests/test_sessions.cpp:398-478
Issue: the two transport cases are near-verbatim clones of ~40 lines each, differing only
in one assignment (`manifest.packer_home = ...`) and one final assertion.
Evidence: the SAME delta uses table-driven `struct Row` + std::array + CAPTURE loops in
tests/test_manifest.cpp:95-116 and tests/test_pack.cpp:222-262. Inconsistent with the
author's own idiom two files over, not merely with the codebase's.

I6 — Nit — tests/test_pack.cpp:257
Issue: `if (row.label == std::string_view{"wsl-mount"})` is a stringly-typed per-row branch
inside an otherwise clean table loop.
Evidence: an `expected_source_flavor` column would keep the row data in the table at
:228-243 where the rest of it lives.

I7 — Nit — production and tests, mixed aggregate-init style
Issue: PackerHome is built with designated initializers in production
(manifest.cpp:621, pack.cpp:148) and in one test (test_manifest.cpp:82), but POSITIONALLY
at seven-plus test sites: test_manifest.cpp:101-105, :133-138; test_pack.cpp:230-241;
test_sessions.cpp:401, :433; test_adapter_claude_install.cpp:548-549;
test_adapter_codex_install.cpp:501-502.
Evidence: the codebase leans hard on designated initializers everywhere else, including
the aggregate initializations immediately surrounding these call sites.

I8 — Minor (shades into the tests lens) — tests/test_adapter_claude_install.cpp:534-573
and tests/test_adapter_codex_install.cpp:484-530
Issue: both cases set `target.packer_home` (:550 / :503) and then assert NOTHING that can
distinguish present from absent, so they cannot fail for the reason they name.
Evidence: every assertion in both bodies is a payload-fidelity check (key untouched, cwd
rewritten to workspace, decimal/integral/exponent/unsigned preserved), cloned from the
adjacent "install rewrites escaped values without changing keys or numbers" test. No
adapter reads InstallTarget.packer_home at this SHA (`git grep -n packer_home 29796bb --
src/` returns only adapter.hpp:161 as the declaration; zero reads). The assertions
therefore hold identically whether the packer_home line is present or deleted. Design §9
item 23 asks for BOTH arms — "observes the transported value when present AND the nullopt
when absent" — and only the present arm exists, with no cross-arm comparison. A real
inertness control would assert byte-identity of the installed output across the two arms.
Deferring severity to the tests lens; raised because "receipt" is the design's word and
this is not yet one.

WHAT I CHECKED HARDEST (idiom), all clean and worth recording:

- Error construction/propagation: `std::unexpected(x.error())` at manifest.cpp:607, :611
  matches fourteen prior sites in the same function family (:199, :210, :219, :246, :252,
  :268, :293, :328, :577, :583, :601, :656, :660). BivError{ErrKind::ParseError, {}, key}
  form at :614, :619, :623 matches the file exactly.
- Optional handling: the double-deref `**packer_home_text` (:621) and the
  `std::move(*x)` handoff match the SessionIds.parent prior art at :271-280 exactly. The
  new code uses the one-at-a-time fetch/check style rather than :272's combined
  `if (!primary || !parent || !parent_in_image)` — correctly so, because the design's §6
  per-key error remap requires distinct details, and the top-level cluster (:577-601)
  already uses the one-at-a-time style.
- The parse_path_flavor remap at :617-620 is not merely idiomatic but NECESSARY: that
  helper hardcodes its detail to "source_path_flavor" (:462), so discarding and rebuilding
  the error is the right call, and it leaves helper and existing callers untouched.
- Top-level-const-on-by-value-parameter split between header declaration
  (`std::string_view path`, manifest.hpp:80) and .cpp definition
  (`const std::string_view path`, manifest.cpp:446) matches to_string (:466) and
  parse_path_flavor (:479) in the same file.
- `friend bool operator==(const PackerHome&, const PackerHome&) = default;`
  (manifest.hpp:27) IS the first and only operator== in src/ (`git grep -n 'operator=='
  29796bb -- src/` returns exactly that one line). I judged the style FITS rather than
  flagged it: the design §3 requires "pair equality and round-trip checks are a single
  ==", the hidden-friend form is the modern-C++ default for an aggregate, and the tests
  consume it directly (test_manifest.cpp:93, :113; test_sessions.cpp:436). No finding.
- `mutable std::optional<...> seen_packer_home` on CountingAdapter (test_sessions.cpp:176)
  matches the sibling `mutable std::size_t install_calls` (:175).
- Build wiring: the parity test's cross-layer include of "adapters/rewrite_common.hpp"
  (test_manifest.cpp:9) links fine — biv_tests is a single executable linking BOTH bivcore
  and biv_adapters (CMakeLists.txt:100-124), so no CMake change is missing despite the
  delta touching no build file.
- No .clang-format exists in the tree at 29796bb, so there is no formatting instrument to
  fail against; I dropped a line-width angle after confirming rewrite_common.cpp:44 already
  runs to 103 columns.

DELIBERATELY NOT FLAGGED (design-ruled, verified against the doc at 29796bb):
- pack.cpp::path_flavor (:131-140) now sits three lines above a strictly more capable
  classifier and is a near-duplicate. Design §10 puts path_flavor/source_path_flavor
  semantics explicitly out of scope, and §3 states they are UNTOUCHED by intent.
  Consolidating would change source_path_flavor for windows-spelled sources = sealed
  behavior needing authority. Leaving it is correct; possibly worth a registered residual
  rather than a review finding.
- serialize silently dropping an engaged-but-invalid value rather than erroring — design §5
  specifies the stated-collapse rule exactly.
- The two-key wire shape and the rewrite_common grammar duplication, per your exclusions.

=====================================================================
CROSS-LENS MAJOR — TEST HERMETICITY (outside my two lenses; routing to
whoever owns test hygiene)
=====================================================================

tests/test_pack.cpp:222-262 — the new "pack captures packer_home per HOME shape" case is
the ONLY pack test in the file that does not sandbox the agent stores.

Every other test in the file that manipulates HOME also pins CLAUDE_CONFIG_DIR and
CODEX_HOME to temp directories (:286-288, :350-352, :609-610). This one sets only HOME,
via `const ScopedHome home{row.home};` at :248.

That matters because store discovery falls back to the home directory when the env var is
unset or its path does not exist:
  src/adapters/claude_code/claude_code.cpp:311 — `const auto root = env.home / ".claude";`
  src/adapters/codex/codex.cpp:770            — `const auto root = env.home / ".codex";`
both reached when the `env.getenv(...)` + `fs::exists` guard above them fails.

The row at test_pack.cpp:232 sets HOME to "/Users/jack" — this operator's ACTUAL home
directory. On that machine the test will find the real ~/.claude and ~/.codex stores, walk
the real session tree, and open the real Codex SQLite database. On a Linux CI runner
/Users/jack does not exist, so discovery finds nothing and the test passes cleanly — which
is precisely what makes this the kind of divergence that surfaces only on the operator's
box.

Being precise about blast radius rather than overstating: collection is keyed to the source
workspace, and the source here is a freshly created temp dir (:245-247), so no real session
should match and I would not expect real user data to land in the archive. The assertion
under test (`manifest->packer_home == row.expected`, :256) is unaffected either way. The
concrete costs are (1) a unit test reads the developer's real session store, (2) its
runtime scales with how large that store is, (3) its behavior differs between the
operator's machine and CI.

Fix, in the spirit of the file's existing pattern: add temp-dir ScopedEnv guards for
CLAUDE_CONFIG_DIR and CODEX_HOME alongside the ScopedHome at :248, or use a
non-existent path such as "/nonexistent/home" instead of a real one for the posix row.
```

---

## LEAD SYNTHESIS

Per-lens verdicts (bare):
- correctness/design-conformance: must-fix (product bytes clean — must-fix confined to the test delta)
- security: must-fix (one Medium; everything else approve-grade)
- test-coverage: must-fix (2 Major, 6 Minor, 1 advisory)
- performance+idiomaticity: approve (plus one cross-lens Major routed to test hygiene)

**PANEL VERDICT: must-fix — REVIEW-FOLD required.** The five product files are clean on
three lenses' independent reads (no design divergence, no correctness defect, no leak, no
parse DoS, transport containment proven at one construction site and one copy site). Every
must-fix save one is confined to the test delta. Deduplicated must-fix set, cross-lens
overlaps merged (severity shown is the highest any lens assigned):

**MF-1 (Medium, security F1 ⟷ correctness #5 — CROSS-LENS CONFLICT, ROUTED UP).**
`packer_home_valid` admits degenerate root-only spellings: `/` (posix), `/mnt/c/` (wsl),
`C:/`, `//?/`, `\\?\` (windows) all parse into `InstallTarget.packer_home`. Both lenses
agree on the FACTS (lead re-verified at the blob); they disagree on disposition: security
grades must-fix at the sealed boundary (a corrupted reference frame makes the future
needle fire on everything — a different risk class from the ratified absent⇒skip), while
correctness grades it conformant (the grammar deliberately mirrors
`rewrite_common.cpp:43-53` per design §3). Adjudicated at the bytes: BOTH are right —
the implementation conforms to the locked design, and the locked design admits the
degenerate values. The defect, if it is one, lives in the floor-ratified contract's
grammar, which is above the pair. ROUTED UP with both options framed (see the routing
relay); not folded on pair authority.

**MF-2 (Major, tests #1 ≡ correctness #4).** The sealed wire POSITION of the emit block
is unpinned: the only ordering assertion is `source_path_flavor < packer_home`, satisfied
by any later position; the exact-bytes golden runs carrier-absent. Relocating the emit
block after `repos` keeps all fifteen new TEST_CASEs green. Fix: a carrier-ENGAGED
exact-bytes golden (full literal), pinning adjacency and home-before-flavor order.

**MF-3 (Major, tests #2).** The `!packer_home_flavor_text` wrong-type branch
(manifest.cpp:610-611) is unreached by any test; its fail-closed detail string
(`packer_home_flavor`) is unguarded. Fix: one row `"packer_home":"/x","packer_home_flavor":42`
expecting `detail == "packer_home_flavor"`, in a flavor-detail case (not the
`packer_home`-detail array).

**MF-4 (HIGH, correctness #1 ≡ perf-idiom I8 ≡ tests #8).** Both adapter "receipt" tests
are unfalsifiable boxes: clones of the adjacent rewrite test plus two lines, `transported`
never read, no assertion can fail for a packer_home reason, and §9 test 23's REQUIRED
nullopt arm does not exist in either file. The known unfalsifiable-box shape. Fix
(implementable today, no adapter seam): install twice against identical fixtures — once
engaged, once nullopt — and assert the produced store bytes are IDENTICAL; that is a real
inertness receipt and fails the day an adapter starts interpreting the value.

**MF-5 (Major, perf-idiom cross-lens ≡ correctness #2 ≡ tests #7).** The new pack capture
test is the only `pack()` test in its file that does not sandbox the agent stores: it pins
HOME only (no `CLAUDE_CONFIG_DIR`/`CODEX_HOME` guards, unlike siblings at :286/:350/:609),
and its absolute row sets HOME to `/Users/jack` — the operator's REAL home — so on the
operator's machine the test walks the live `~/.claude` and `~/.codex` stores (real Codex
SQLite included) and behaves differently than on CI. The unset row additionally leaves
store discovery resolving relative `.claude`/`.codex` against the test CWD. Fix: temp-dir
`ScopedEnv` guards for both store variables alongside the HOME guard, and a hermetic
fixture path (e.g. `(root / "home").string()`, the file's own idiom) instead of a real one.

**MF-6 (Major, correctness #3 ≡ tests #5).** Design §9 test 21 requires the transported
value proven identical "for every adapter leg invoked"; the test invokes ONE leg, and the
`CountingAdapter::seen_packer_home` seam is single-valued (overwritten per call), so even
a second agent could not be independently observed. The absent arm also has no falsifier
of its own (deleting the `.packer_home = manifest.packer_home` copy keeps it green). Fix:
a second agent plus a per-call vector of observed values; assert both legs and the
absent-arm nullopt against it.

### Blame framing (carried verbatim from the test-coverage lens; load-bearing for the fold)

The case-level shortfalls in the Minor tier (mismatch matrix half-populated, relative-value
one flavor of three, classifier negative boundary rows, the real-home fixture) are already
present in the PLAN's own literal code blocks at `6047ab03` — the implementer reproduced
those blocks essentially byte-faithfully; the reduction from design §9 happened at
PLAN-authoring time, i.e. at THIS seat. MF-2 and MF-3 are the exceptions (gaps neither
the plan nor the implementation caught). The fold dispatch will say so explicitly: the
majority of the test debt is plan-authored, not implementer drift.

### Optional / nit tier (Implementer discretion within the fold; verbatim details in the reports)

- tests #3/#4/#6 — complete the §9-11 mismatch matrix (the two absent rows incl.
  `C:\…`-declared-posix), the three-flavor relative-value row, and the three
  classifier negative boundary rows (`/mnt/c`, `/mnt/1/x`, `1:/x`).
- perf P1 — `std::move` the captured home text in `pack.cpp` (one avoidable copy, cold path).
- idiom I1-I7 — fold the helper into the file's existing anonymous namespace; rename
  `carrier_ascii_alpha` → `ascii_alpha` (prefix buys no ODR safety); generalize
  `ScopedEnv` to `optional<string>` instead of the `ScopedHome` clone (≡ correctness #8);
  match the file's TEST_CASE naming convention; table-drive the two transport clones;
  hoist the `wsl-mount` per-row branch into a table column; designated initializers at the
  seven-plus positional sites.
- security F2 — C0/NUL survive parse into `PackerHome.path`; render layer already escapes
  (defended by convention); rejecting C0/DEL at parse would make it structural. Recommend,
  not block.
- correctness #6 — carrier parse block now precedes the `repos` fence, so a doubly-invalid
  manifest reports the carrier detail instead of `step2-plain-dir-only`; refusal preserved,
  detail precedence only; no fixture combines the two.
- correctness #7 — design §6 wording implies two XOR details; §8 and the code resolve both
  to `packer_home_flavor`. Tighten §6 at the next design rev (rides MF-1's amendment if
  option A is ruled).
- correctness #9 — no fuzz corpus seed carries the new keys; the parse branch is reachable
  only by mutation from a corpus that has never seen the key names. Add a carrier-engaged seed.

### Candidate RESIDUALS rows (master's to write — routed via the relay, NOT registered here)

- R-cand-1 (security F5): no pack-report surface says whether the carrier was emitted, so
  "needle found nothing" is indistinguishable from "needle never ran". Belongs to the
  needle work.
- R-cand-2 (security F3 / correctness #5 penumbra): `packer_home_flavor` carries zero
  independent information, and a legitimate non-WSL Linux HOME under `/mnt/<alpha>/` is
  recorded `wsl` — the needle's flavor-driven spelling derivation must tolerate this.
- R-cand-3 (security probe-5 note ≡ perf-idiom not-flagged): `pack.cpp::path_flavor` is a
  FOURTH, weaker copy of the flavor grammar (no windows branch), so `source_path_flavor`
  can never be windows while `packer_home_flavor` can. Pre-existing; consolidation would
  change sealed `source_path_flavor` behavior and needs its own authority.

### Rejected / weak: none — every finding cites file:line at `29796bbe`, and the lead
re-verified each must-fix's central claim at the sealed blob post-recovery.

### Disposition

Test-only must-fixes MF-2..MF-6 fold on pair authority (no sealed wire shape touched — the
correctness lens is explicit that no floor re-route is owed for them). MF-1 is routed up
before the fold dispatch issues, so the fold can ride as ONE commit covering the ruled
outcome plus the test set (the B2 complete-amend precedent), followed by ONE targeted
re-check (lead + owning lenses) rather than two. The two human lenses remain unrouted
until the panel (and its fold verification) has cleared the exact SHA — panel-before-lenses.
