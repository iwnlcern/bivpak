# Task 4 — rev15 evidence report

## Disposition

Task 4 evidence is complete at exact candidate
`a2f6fd1adf67fd86c8d0c692db34f113a9691135` on `intg/format-act`. All
candidate-attributable static, macOS product, Linux build/product/tidy/hardening,
FX-O/FX-N, E4, and A6 gates are green. Aggregate nonzero returns are solely the
registered environment/configuration observations below; they are not
merge-readiness evidence.

- Rev15 plan SHA-256:
  `beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265`
- Parent/base: `363d812fba2610f7e5c71fdb9daee5c7f740027a` / `46df8f3`
- Retained Task-3 commits: `9e6ebe8fca2454164051573323dd7adfa2901219`,
  `b09e1922c16da50b5bef0644d9923a567b98c468`
- Evidence home: `/tmp/bivpak-format-act-task4-rev15.Z1yIwJ`
- No credential value was printed, passed to the container, or retained.

## Newly measured receipts

### Identity and static fences

```text
$ shasum -a 256 PL-intg-substep2a-20260830.md
beba597c20d43441f6901f4930e4e4141bd866ecdc27c3f8cec3f403dcb0f265
[rc=0]
$ git rev-parse HEAD
a2f6fd1adf67fd86c8d0c692db34f113a9691135
[rc=0]
$ git rev-parse HEAD^
363d812fba2610f7e5c71fdb9daee5c7f740027a
[rc=0]
$ git branch --show-current
intg/format-act
[rc=0]
$ git rev-list --count 46df8f3..HEAD
4
[rc=0]
$ git status --short --untracked-files=all
[no output]
[rc=0]
$ git diff --cached --name-only
[no output]
[rc=0]
$ git diff --check 46df8f3..HEAD
[no output]
[rc=0]
```

The linked gitdir is
`/Users/jack/Programming/bivpak/.git/worktrees/bivpak-intg-format-act`; common
gitdir is `/Users/jack/Programming/bivpak/.git`; no superproject is present.

```text
$ git grep -n 'run_eligibility\|restore_entry\|repo::capture' -- src ':!src/core/repo'
[no output]
[rc=1, expected no-match]
$ grep -n kFormatVersion src/core/manifest/manifest.hpp
14:inline constexpr int kFormatVersion = 1;
[rc=0]
$ git show 46df8f3:src/core/manifest/manifest.hpp | grep kFormatVersion
inline constexpr int kFormatVersion = 1;
[rc=0]
$ current_literal=$(grep 'kFormatVersion = ' src/core/manifest/manifest.hpp); base_literal=$(git show 46df8f3:src/core/manifest/manifest.hpp | grep 'kFormatVersion = '); test "$current_literal" = "$base_literal"
[rc=0]
```

The four textual version-token diff matches are unchanged context/restructure;
the literal fence proves no bump.

Exact ruling-231935 base..HEAD allowlist:

```text
src/core/manifest/manifest.cpp
src/core/manifest/manifest.hpp
src/core/pack/pack.cpp
src/core/repo/classify.cpp
src/core/repo/restore.cpp
src/core/repo/types.hpp
tests/test_cli.cpp
tests/test_manifest.cpp
tests/test_open.cpp
tests/test_repo_engine.cpp
[membership rc=0; cardinality=10 rc=0]
```

### C-1 exact whole-tree confinement pipeline

```text
$ git grep -n 'serialize(' HEAD | grep -v checksums | grep -v 'src/core/manifest/manifest\.[ch]pp' | grep -v test_manifest.cpp | grep -v ':docs/'
HEAD:src/core/pack/pack.cpp:765:  auto manifest_json = manifest::serialize(manifest_model);
HEAD:tests/test_cli.cpp:192:  auto serialized = biv::manifest::serialize(manifest);
HEAD:tests/test_open.cpp:131:  const auto serialized = biv::manifest::serialize(manifest);
[pipeline_rc=0]
$ git grep -n 'serialize(' 9e6ebe8 | grep -v checksums | grep -v 'src/core/manifest/manifest\.[ch]pp' | grep -v test_manifest.cpp | grep -v ':docs/'
9e6ebe8:src/core/pack/pack.cpp:765:  const std::string manifest_json = manifest::serialize(manifest_model);
9e6ebe8:tests/test_cli.cpp:192:  auto manifest_json = biv::manifest::serialize(manifest);
9e6ebe8:tests/test_open.cpp:131:  const auto manifest_json = biv::manifest::serialize(manifest);
[pipeline_rc=0]
$ grep -n 'expected<std::string> serialize' src/core/manifest/manifest.hpp
88:expected<std::string> serialize(const Manifest& manifest);
[rc=0]
```

Exactly three candidate sites remain and each consumes the `expected<>`.

### C-3 actual complete per-file diffs and bounds

```diff
$ git diff 9e6ebe8..HEAD -- src/core/pack/pack.cpp
diff --git a/src/core/pack/pack.cpp b/src/core/pack/pack.cpp
index 93223b5..8dae198 100644
--- a/src/core/pack/pack.cpp
+++ b/src/core/pack/pack.cpp
@@ -762,7 +762,10 @@ expected<PackReport> pack_impl(const std::filesystem::path& source_dir) {
       .agent_sessions = report.agent_sessions,
       .bivignore = scan_result->bivignore,
   };
-  const std::string manifest_json = manifest::serialize(manifest_model);
+  auto manifest_json = manifest::serialize(manifest_model);
+  if (!manifest_json) {
+    return cleanup_error(manifest_json.error());
+  }
   const std::string checksums_json = manifest::serialize(checksums);
 
   {
@@ -775,7 +778,7 @@ expected<PackReport> pack_impl(const std::filesystem::path& source_dir) {
     }};
     auto zstd_sink = zstd.as_sink();
     container::TarWriter archive{zstd_sink};
-    if (auto ok = write_string_member(archive, "manifest.json", manifest_json, created.seconds); !ok) {
+    if (auto ok = write_string_member(archive, "manifest.json", *manifest_json, created.seconds); !ok) {
       return cleanup_error(ok.error());
     }
     if (auto ok = write_string_member(archive, "checksums.json", checksums_json, created.seconds); !ok) {
[rc=0]
$ git diff 9e6ebe8..HEAD -- src/core/pack/pack.cpp | grep '^[+-][^+-]' | grep -v '^[+-][[:space:]]*[{}][[:space:]]*$' | grep -vc 'manifest_json\|serialized\|has_value\|cleanup_error'
0
[pipeline_rc=1, printed zero is the gate]
$ git diff --numstat 9e6ebe8..HEAD -- src/core/pack/pack.cpp
5       2       src/core/pack/pack.cpp
[rc=0]

$ git diff 9e6ebe8..HEAD -- tests/test_cli.cpp
diff --git a/tests/test_cli.cpp b/tests/test_cli.cpp
index 0176a90..29574ef 100644
--- a/tests/test_cli.cpp
+++ b/tests/test_cli.cpp
@@ -189,7 +189,9 @@ std::filesystem::path make_slice_e_consumer_image(
     REQUIRE(writer.write_data(std::as_bytes(std::span{content})));
     REQUIRE(writer.end_member());
   };
-  auto manifest_json = biv::manifest::serialize(manifest);
+  auto serialized = biv::manifest::serialize(manifest);
+  REQUIRE(serialized.has_value());
+  auto manifest_json = std::move(*serialized);
   size_t schema_cursor = 0U;
   for (const int schema : entry_schemas) {
     const auto position = manifest_json.find("\"entry_schema\": 1", schema_cursor);
[rc=0]
$ git diff 9e6ebe8..HEAD -- tests/test_cli.cpp | grep '^[+-][^+-]' | grep -v '^[+-][[:space:]]*[{}][[:space:]]*$' | grep -vc 'manifest_json\|serialized\|has_value\|cleanup_error'
0
[pipeline_rc=1, printed zero is the gate]
$ git diff --numstat 9e6ebe8..HEAD -- tests/test_cli.cpp
3       1       tests/test_cli.cpp
[rc=0]

$ git diff 9e6ebe8..HEAD -- tests/test_open.cpp
diff --git a/tests/test_open.cpp b/tests/test_open.cpp
index 28639a6..0e5e391 100644
--- a/tests/test_open.cpp
+++ b/tests/test_open.cpp
@@ -128,7 +128,9 @@ void write_bivpak(const std::filesystem::path& image,
   auto sink = zstd.as_sink();
   biv::container::TarWriter writer{sink};
 
-  const auto manifest_json = biv::manifest::serialize(manifest);
+  const auto serialized = biv::manifest::serialize(manifest);
+  REQUIRE(serialized.has_value());
+  const auto& manifest_json = *serialized;
   REQUIRE(writer.begin_member(biv::container::MemberMeta{.path = "manifest.json",
                                                          .kind = biv::scan::NodeKind::file,
                                                          .mode = 0644,
[rc=0]
$ git diff 9e6ebe8..HEAD -- tests/test_open.cpp | grep '^[+-][^+-]' | grep -v '^[+-][[:space:]]*[{}][[:space:]]*$' | grep -vc 'manifest_json\|serialized\|has_value\|cleanup_error'
0
[pipeline_rc=1, printed zero is the gate]
$ git diff --numstat 9e6ebe8..HEAD -- tests/test_open.cpp
3       1       tests/test_open.cpp
[rc=0]
```

### C-4 exact term and witness

> On an O-R1 refusal at the pack.cpp Manifest-overload site, the writer refuses BEFORE the partial archive is opened (:765 precedes the ofstream at :769); cleanup_error removes partial_path and spool_path; NO NEW OR REPLACEMENT .bvpk is emitted; a PRE-EXISTING image at image_path, if any, is UNCHANGED (image_path is written only by the :801 rename, which is never reached). This is O-R1's "emitting NO output" at the pack level. Task 4 evidence STATES whether any FX-O leg exercises this pack-level path or the refusal is witnessed at the writer unit level only; no new pack-level test is REQUIRED by this term; silence on the point is a V-FA-7 red.

> NO FX-O leg exercises this pack-level path; the refusal is witnessed at the WRITER UNIT LEVEL ONLY (legs (a)(b)(d.i)(d.ii) at `test_manifest`); no new pack-level test was added (none is required by the term)

Historical coordinates above are verbatim. Fresh candidate coordinates are
serialize `:765`, partial archive open `:772`, final rename `:804`; predicate
`765<772<804` rc=0. Cleanup removes partial `:571` and spool `:572/:812`.

### C-5, M, and mechanical counts

```text
$ git diff --quiet 46df8f3..HEAD -- src/cli src/cli/main.cpp schemas
[rc=0]
$ grep -n '"promisor"\|"engine_source"' src/core/manifest/manifest.cpp
[no output; rc=1 expected]
$ git diff --quiet 46df8f3..HEAD -- src/core/repo/git_exec.hpp src/core/repo/git_exec.cpp src/core/repo/eligibility.cpp
[rc=0]

$ sed -n '/^constexpr std::array kRepoRowClauses{/,/^};/p' src/core/manifest/manifest.cpp | grep -c 'RepoRowClause{'
64
[rc=0]
$ sed -n '/^constexpr std::array kWriterImageExclusions{/,/^};/p' src/core/manifest/manifest.cpp | grep -c 'WriterImageExclusion{'
8
[rc=0]
$ sed -n '/^constexpr std::array kRepoWireClauses{/,/^};/p' src/core/manifest/manifest.cpp | grep -c 'RepoRowClause{'
3
[rc=0]
$ grep -c FX-O-INV tests/test_manifest.cpp
72
[rc=0]
$ awk '/^expected<std::optional<std::filesystem::path>>$/{f=1} /^expected<std::vector<RepoEntry>>$/{f=0} f && /ErrKind::ParseError/{c++} END{print c+0}' src/core/manifest/manifest.cpp
44
[rc=0]
$ grep -c FX-O-FIELD tests/test_manifest.cpp
7
[rc=0]
$ grep -c 'FX-O-LEG (' tests/test_manifest.cpp
6
[rc=0]
$ grep -c O-MUTANT: tests/test_manifest.cpp
8
[rc=0]
$ grep -c 'NAMED MUTANT' tests/test_manifest.cpp
9
[rc=0]
```

A+B=72 equals FX-O-INV=72. Carried Step-0 diagnostic=60; fresh diagnostic-only
syntax=44 after folding; semantic census remains 64+8. Six unique legs are
`(a)/(b)/(d.i)/(d.ii)/(e)/(f)`, once each (rc=0). CTRL unknown-note-roundtrip
is at `:1811`. O is 8 executable + six-of-seven census mutant=9; NAMED=9.

The complete A/B and parser-local census follows below. All seven named path
fields reach both parser and writer. Enforcement coordinates:

```text
repo_row_violation :1466
validate_repo_entry :1599; writer call :1608
parser post-build call :2362; writer validation call :2459
valid_manifest_path sites :1051/:1823/:1841/:2003/:2024/:2272
[rc=0]
```

### Predicate Table A — all 64 rows, revalidated at a2f6fd1

`I` is the inventory (`manifest.cpp:964-1039`), `W` is writer enforcement
(`:1599-1616`, shared call `:1608`), `S` is candidate parser enforcement
(`:2362-2383`). Pre-build/raw twins are named explicitly.

|row|field / predicate|I/W|candidate parser twin|FX-O arm|
|---|---|---|---|---|
|A01|relpath path|I:965/W|parse_repo_entry:2272-2274|path-relpath|
|A02|local_refs_bundle path|I:966-967/W|optional_nullable_path:1823-1825, call :2310-2311|path-local-refs-bundle|
|A03|bundle path|I:968/W|optional_nullable_path:1823-1825, call :2313|path-bundle|
|A04|capture.staged_patch path|I:969/W|required_nullable_path:1841-1843, call :1992|path-staged-patch|
|A05|capture.worktree_patch path|I:970/W|required_nullable_path:1841-1843, call :1993-1994|path-worktree-patch|
|A06|capture.payload_prefix path|I:971/W|parse_capture:2002-2006|path-payload-prefix|
|A07|capture.forced_payload[].path path|I:972-973/W|parse_capture:2021-2025|path-forced-payload|
|A08|id UTF-8|I:974/W|outer simdjson parse:2567-2571|utf8-id|
|A09|relpath UTF-8|I:975/W|outer parse:2567-2571|utf8-relpath|
|A10|parent_id UTF-8|I:976/W|outer parse:2567-2571|utf8-parent-id|
|A11|remote UTF-8|I:977/W|outer parse:2567-2571|utf8-remote|
|A12|remotes[].name UTF-8|I:978/W|outer parse:2567-2571|utf8-remotes-name|
|A13|remotes[].url UTF-8|I:979/W|outer parse:2567-2571|utf8-remotes-url|
|A14|branch UTF-8|I:980/W|outer parse:2567-2571|utf8-branch|
|A15|eligibility.method UTF-8|I:981/W|outer parse:2567-2571|utf8-eligibility-method|
|A16|eligibility.checked_at UTF-8|I:982/W|outer parse:2567-2571|utf8-eligibility-checked-at|
|A17|eligibility.proof.remote UTF-8|I:983/W|outer parse:2567-2571|utf8-eligibility-proof-remote|
|A18|eligibility.proof.url UTF-8|I:984/W|outer parse:2567-2571|utf8-eligibility-proof-url|
|A19|eligibility.proof.ref UTF-8|I:985/W|outer parse:2567-2571|utf8-eligibility-proof-ref|
|A20|local_refs[].ref UTF-8|I:986/W|outer parse:2567-2571|utf8-local-refs-ref|
|A21|local_refs[].proof.remote UTF-8|I:987/W|outer parse:2567-2571|utf8-local-refs-proof-remote|
|A22|local_refs[].proof.url UTF-8|I:988/W|outer parse:2567-2571|utf8-local-refs-proof-url|
|A23|local_refs[].proof.ref UTF-8|I:989/W|outer parse:2567-2571|utf8-local-refs-proof-ref|
|A24|local_refs_bundle UTF-8|I:990/W|outer parse:2567-2571|utf8-local-refs-bundle|
|A25|capture.staged_patch UTF-8|I:991/W|outer parse:2567-2571|utf8-staged-patch|
|A26|capture.worktree_patch UTF-8|I:992/W|outer parse:2567-2571|utf8-worktree-patch|
|A27|capture.payload_prefix UTF-8|I:993/W|outer parse:2567-2571|utf8-payload-prefix|
|A28|forced_payload[].path UTF-8|I:994/W|outer parse:2567-2571|utf8-forced-payload-path|
|A29|capture_env.core_autocrlf UTF-8|I:995/W|outer parse:2567-2571|utf8-core-autocrlf|
|A30|bundle UTF-8|I:996/W|outer parse:2567-2571|utf8-bundle|
|A31|sha/head-state relation|I:997/W|S, legacy detail sha|sha-head-state|
|A32|sha 40-hex|I:998/W|S, detail sha|sha-hex|
|A33|eligibility.method domain|I:999/W|S, mapped detail eligibility :2368-2382|eligibility-method|
|A34|eligibility.proof.tip_sha 40-hex|I:1000-1001/W|S, mapped eligibility|eligibility-proof-tip-sha|
|A35|local_refs[].sha 40-hex|I:1002/W|S, mapped local_refs|local-refs-sha|
|A36|local_refs[].proof.tip_sha 40-hex|I:1003-1004/W|S, mapped local_refs|local-refs-proof-tip-sha|
|A37|local_refs[].proof availability relation|I:1005-1006/W|S, mapped local_refs|local-refs-proof-presence|
|A38|eligibility shallow empty|I:1007/W|S|shallow-eligibility|
|A39|local_refs shallow empty|I:1008/W|S|shallow-local-refs|
|A40|local_refs_bundle shallow absent|I:1009-1010/W|S|shallow-local-refs-bundle|
|A41|bundle shallow absent|I:1011/W|S|shallow-bundle|
|A42|shallow.boundary[] 40-hex|I:1012/W|S|shallow-boundary-hex|
|A43|eligibility unborn+bundle required|I:1013/W|S|unborn-bundle-eligibility|
|A44|eligibility.result unborn+bundle|I:1014/W|S|unborn-bundle-result|
|A45|capture_mode unborn+bundle full|I:1015-1016/W|S, mapped eligibility|unborn-bundle-capture-mode|
|A46|eligibility.result born not unborn-head|I:1017/W|S|born-unborn-head-result|
|A47|eligibility payload-only unborn empty|I:1018-1019/W|S|payload-only-unborn-eligibility|
|A48|local_refs non-shallow unborn/no-bundle empty|I:1020-1021/W|S, legacy detail eligibility|unborn-no-bundle-local-refs|
|A49|notes non-carried unique|I:1022/W|S|non-carried-unique|
|A50|notes refs cap|I:1023/W|S|non-carried-refs-cap|
|A51|notes omitted positive|I:1024/W|S|non-carried-omitted-positive|
|A52|notes omitted max|I:1025/W|S|non-carried-omitted-max|
|A53|notes refs or omitted|I:1026/W|S|non-carried-nonempty|
|A54|notes P1 decodable|I:1027/W|S|non-carried-p1|
|A55|notes decoded ref byte cap|I:1028/W|S|non-carried-ref-bytes|
|A56|notes decoded full ref name|I:1029/W|S|non-carried-full-ref|
|A57|notes no catch-all ref|I:1030/W|S|non-carried-catch-all|
|A58|notes strict order|I:1031/W|S|non-carried-strict-order|
|A59|UnknownNote JSON valid/UTF-8|I:1032/W|outer simdjson parse:2567-2571|unknown-note-json-valid|
|A60|UnknownNote JSON single value|I:1033/W|raw_repo_note_values:2171-2205|unknown-note-single-value|
|A61|UnknownNote JSON object|I:1034/W|parse_notes:2208-2218|unknown-note-object|
|A62|UnknownNote kind present|I:1035/W|parse_notes:2219-2222|unknown-note-kind-present|
|A63|UnknownNote kind string|I:1036/W|required_string call parse_notes:2219|unknown-note-kind-string|
|A64|local_refs_bundle iff bundle-carried|I:1037-1038/W|S|local-refs-bundle-biconditional|

The seven path rows retain parser-local checks because typed path construction
has not yet completed. The five raw-note shape rows retain raw/pre-build twins
because malformed raw JSON cannot be represented by a constructed RepoEntry.

### Projection-canonicalization Table B — all 8 rows, revalidated at a2f6fd1

|row|field / exclusion|writer rejection|candidate parser construction witness|FX-O arm|
|---|---|---|---|---|
|B01|kind / repo_kind|:1497,:1515-1519|parse_repo_entry:2275-2279 enum spelling|enum-repo-kind|
|B02|head_state / head_state|:1498,:1520-1524|parse_repo_entry:2276-2279 enum spelling|enum-head-state|
|B03|capture_mode / capture_mode|:1499-1500,:1525-1530|:2281-2301; absent contextual carrier constructs full :2351|enum-capture-mode|
|B04|eligibility.result / eligibility_result|:1501-1502,:1531-1537|parse_optional_eligibility:1915-1925|enum-eligibility-result|
|B05|local_refs[].availability / ref_availability|:1503-1504,:1538-1544|parse_local_refs:1973-1981|enum-ref-availability|
|B06|forced_payload[].reason / forced_payload_reason|:1505-1506,:1545-1552|parse_capture:2031-2037|enum-forced-payload-reason|
|B07|UnknownNote.kind / unknown_note_kind|:1507,:1553-1577|parse_notes:2227-2232 preserves raw kind|unknown-note-kind|
|B08|UnknownNote alias / unknown_note_alias|:1508,:1578-1583|parse_notes:2223-2233 constructs structured variants|unknown-note-aliases-structured|

These are construction/canonicalization witnesses, not invented parser
rejections. The independent `ProjectedRow` oracle reads every included
coordinate and neither excluded field; equality is only over `pi_repo`.

### Complete parser-local predicate census — P01-P122, revalidated at a2f6fd1

This is the complete transitive `repos[]` route through `parse_repo_entries`,
`parse_repo_entry`, and helpers. A/B-owned rows are cross-referenced, not
double-counted. Each carrier predicate is independently mutable. No duplicate-
key or unknown-key rejection exists on this route: recognized keys are looked
up and unknown members are deliberately accepted.

|row|field and predicate|candidate parser site / classification|
|---|---|---|
|P01|document empty or byte-cap exceeded|parse:2548-2551; `manifest-size`|
|P02|first non-space not `{`|parse:2559-2561; `root`|
|P03|malformed JSON/document UTF-8|parse:2567-2571; simdjson detail|
|P04|root not object|parse:2572-2575; `root`|
|P05|repos missing|parse_repo_entries:2389-2393; `repos`|
|P06|repos[] non-object|parse_repo_entries:2395-2399; `repos`|
|P07|id missing string|required_string:41-47, call :2258/:2268-2270; construction|
|P08|id wrong type|required_string:41-47, call :2258/:2268-2270; construction|
|P09|relpath missing string|required_string call :2259/:2268-2270; A01 owns value|
|P10|relpath wrong type|required_string call :2259/:2268-2270; A01 twin :2272-2274|
|P11|kind missing string|required_string call :2260/:2268-2270; construction|
|P12|kind wrong type|required_string call :2260/:2268-2270; construction|
|P13|kind unknown enum|parse_enum_field:836-843, call :2275-2279; B01|
|P14|parent_id missing|required_nullable_string:1795-1808, call :2261/:2268-2270|
|P15|parent_id wrong non-null type|required_nullable_string call :2261/:2268-2270|
|P16|remote missing|required_nullable_string call :2262/:2268-2270|
|P17|remote wrong non-null type|required_nullable_string call :2262/:2268-2270|
|P18|remotes missing|parse_remotes:1929-1933, call :2263|
|P19|remotes[] non-object|parse_remotes:1935-1939|
|P20|remotes[].name missing|required_string call parse_remotes:1940-1943|
|P21|remotes[].name wrong type|required_string call :1940-1943|
|P22|remotes[].url missing|required_string call :1941-1943|
|P23|remotes[].url wrong type|required_string call :1941-1943|
|P24|sha missing|required_nullable_string call parse_repo_entry:2264/:2268-2270|
|P25|sha wrong non-null type|required_nullable_string call :2264/:2268-2270; A31-A32|
|P26|branch missing|required_nullable_string call :2265/:2268-2270|
|P27|branch wrong non-null type|required_nullable_string call :2265/:2268-2270|
|P28|head_state missing|required_string call :2266/:2268-2270|
|P29|head_state wrong type|required_string call :2266/:2268-2270|
|P30|head_state unknown enum|parse_enum_field call :2276-2279; B02|
|P31|dirty missing boolean|required_bool:62-69, call :2267-2270|
|P32|dirty wrong type|required_bool:62-69, call :2267-2270|
|P33|capture_mode present null|parse_repo_entry:2281-2288; wire shape|
|P34|capture_mode present wrong type|parse_repo_entry:2289-2292; wire shape|
|P35|capture_mode unknown enum|parse_enum_field call :2294-2297; B03|
|P36|capture_mode lookup error other than absent|parse_repo_entry:2300-2301|
|P37|eligibility present null|parse_optional_eligibility:1897-1903|
|P38|eligibility present non-object|parse_optional_eligibility:1904-1907|
|P39|eligibility.method missing|required_string call :1908-1913; A33 owns semantic|
|P40|eligibility.method wrong type|required_string call :1908-1913|
|P41|eligibility.result missing|required_string call :1909-1913|
|P42|eligibility.result wrong type|required_string call :1909-1913|
|P43|eligibility.result unknown enum|parse_enum_field call :1915-1918; B04|
|P44|eligibility.checked_at missing|required_string call :1910-1913|
|P45|eligibility.checked_at wrong type|required_string call :1910-1913|
|P46|eligibility.proof present non-object|parse_optional_proof:1865-1879; caller maps detail|
|P47|eligibility proof remote missing|required_string call :1880-1885|
|P48|eligibility proof url missing|required_string call :1881-1885|
|P49|eligibility proof ref missing|required_string call :1882-1885|
|P50|eligibility proof tip_sha missing|required_string call :1883-1885; A34 owns hex|
|P51|local_refs present non-array|parse_local_refs:1952-1959|
|P52|local_refs[] non-object|parse_local_refs:1961-1965|
|P53|local_refs[].ref missing|required_string call :1966-1971|
|P54|local_refs[].sha missing|required_string call :1967-1971; A35 owns hex|
|P55|local_refs[].availability missing|required_string call :1968-1971|
|P56|local_refs availability unknown enum|parse_enum_field call :1973-1976; B05|
|P57|local_refs proof present non-object|parse_optional_proof call :1969-1971|
|P58|local_refs proof remote missing|required_string call :1880-1885|
|P59|local_refs proof url missing|required_string call :1881-1885|
|P60|local_refs proof ref missing|required_string call :1882-1885|
|P61|local_refs proof tip_sha missing|required_string call :1883-1885; A36 owns hex|
|P62|local_refs_bundle wrong non-string|optional_string:119-134, call :2310-2311; A02/A24/A64|
|P63|capture missing|required_object:71-78, call parse_capture:1986-1990|
|P64|staged_patch missing|required_nullable_string call :1992-2000; A04 owns path|
|P65|worktree_patch missing|required_nullable_string call :1993-2000; A05 owns path|
|P66|payload_prefix missing string|required_string call :1995-2005; A06 owns path|
|P67|forced_payload missing|parse_capture:2008-2013|
|P68|forced_payload[] non-object|parse_capture:2015-2019|
|P69|forced_payload path missing|required_string call :2021-2025; A07 owns path|
|P70|forced_payload reason missing|required_string call :2022/:2027-2029|
|P71|forced_payload reason unknown enum|parse_enum_field call :2031-2034; B06|
|P72|capture_env missing|required_object call :2040-2042|
|P73|core_autocrlf missing|required_nullable_string call :2045-2051|
|P74|core_autocrlf wrong non-null type|required_nullable_string call :2045-2051|
|P75|core_filemode missing|required_nullable_bool:1847-1861, call :2047-2051|
|P76|core_filemode wrong non-null type|required_nullable_bool call :2047-2051|
|P77|capture_env.sparse missing|required_bool call :2049-2051|
|P78|capture_env.sparse wrong type|required_bool call :2049-2051|
|P79|bundle wrong non-string|optional_string:119-134, call :2313; A03/A30/A41|
|P80|shallow present null|parse_optional_shallow:2068-2075, call :2314|
|P81|shallow present non-object|parse_optional_shallow:2076-2079|
|P82|shallow.boundary missing|required_string_array:80-95, call :2080-2082|
|P83|shallow.boundary[] non-string|required_string_array call :2080-2082; A42 owns hex|
|P84|notes missing|parse_notes:2208-2212, call parse_repo_entry:2315|
|P85|notes[] non-object|parse_notes:2214-2218|
|P86|notes.kind missing|required_string call :2219-2222; A62-A63 raw shape|
|P87|non-carried refs missing|required_string_array call parse_notes:2234-2236|
|P88|non-carried refs[] non-string|required_string_array call :2234-2236; A49-A58|
|P89|omitted_count non-integer|parse_notes:2238-2250|
|P90|omitted_count outside uint64|parse_notes:2238-2250|
|P91|local_refs absent outside H/N wire conditions|facts :2306-2309; wire dispatch :1220-1223/:1467-1470|
|P92|capture_mode presence biconditional|facts :2362-2367; wire dispatch :1224-1228/:1467-1470|
|P93|raw repo count differs from DOM repo count|parse:2661-2664; reconciliation|
|P94|raw note count differs from constructed notes|parse:2665-2669; reconciliation|
|P95|UnknownNote raw JSON/single/object/kind shapes|A59-A63; raw extraction :2171-2205; A-owned|
|P96|shared typed row semantics|A01-A58/A64; parser call :2362-2383; A-owned|
|P97|eligibility proof remote wrong type|required_string call :1880-1885|
|P98|eligibility proof url wrong type|required_string call :1881-1885|
|P99|eligibility proof ref wrong type|required_string call :1882-1885|
|P100|eligibility proof tip_sha wrong type|required_string call :1883-1885|
|P101|local_refs.ref wrong type|required_string call :1966-1971|
|P102|local_refs.sha wrong type|required_string call :1967-1971|
|P103|local_refs availability wrong type|required_string call :1968-1971|
|P104|local_refs proof remote wrong type|required_string call :1880-1885|
|P105|local_refs proof url wrong type|required_string call :1881-1885|
|P106|local_refs proof ref wrong type|required_string call :1882-1885|
|P107|local_refs proof tip_sha wrong type|required_string call :1883-1885|
|P108|capture wrong non-object|required_object call :1986-1990|
|P109|staged_patch wrong non-null type|required_nullable_string call :1992-2000|
|P110|worktree_patch wrong non-null type|required_nullable_string call :1993-2000|
|P111|payload_prefix wrong type|required_string call :1995-2005|
|P112|forced_payload wrong non-array|parse_capture:2008-2013|
|P113|forced_payload path wrong type|required_string call :2021-2025|
|P114|forced_payload reason wrong type|required_string call :2022/:2027-2029|
|P115|capture_env wrong non-object|required_object call :2040-2042|
|P116|shallow.boundary wrong non-array|required_string_array call :2080-2082|
|P117|notes wrong non-array|parse_notes:2208-2212, call :2315|
|P118|non-carried refs wrong non-array|required_string_array call :2234-2236|
|P119|repos present non-array|parse_repo_entries:2389-2393|
|P120|remotes present non-array|parse_remotes:1929-1933, call :2263|
|P121|notes.kind wrong type|required_string call :2219-2222|
|P122|repo sparse present non-null|facts parse_repo_entry:2333-2338; wire dispatch :1216-1219/:1467-1470|

Mechanical reconciliation: P01-P122 each occur exactly once; count=122. The
intentional split pairs are P05/P119 (repos missing/type), P18/P120 (remotes
missing/type), P86/P121 (kind missing/type), and P89/P90 (two omitted-count
conversion failures). P122 records present-non-null sparse while absence is
accepted. P95/P96 cross-reference A-owned predicates rather than duplicating
them. P91/P92/P122 are exactly the three wire-only rows. P93/P94 are the two
post-span raw reconciliation rows. Every parser rejection on the transitive
route is classified; unclassified count=0.

```text
$ awk -F'|' '/^### Complete parser-local predicate census/{f=1;next} /^### \(i\)/{f=0} f && /^\|P[0-9]+\|/ {rows++; if ($4 ~ /^[[:space:]]*$/) unclassified++} END {print "parser_local_rows=" rows " unclassified=" (unclassified+0); exit !(rows==122 && unclassified==0)}' task-4-report.md
parser_local_rows=122 unclassified=0
[rc=0]
```

### (i) exact Shallow boundary-only census

```text
$ sed -n '/^struct Shallow {$/,/^};$/p' src/core/repo/types.hpp
struct Shallow {
  std::vector<std::string> boundary;
};
[rc=0]
$ sed -n '/^struct Shallow {$/,/^};$/p' src/core/repo/types.hpp | sed '1d;$d' | grep -c ';'
1
[rc=0]
$ git grep -n -F 'Shallow{' -- src
src/core/manifest/manifest.cpp:2085:      repo::Shallow{.boundary = std::move(*boundary)}};
[rc=0]
$ git grep -n -E 'Shallow[[:space:]]+[[:alnum:]_]+\{' -- src
src/core/repo/classify.cpp:207:    Shallow metadata{.boundary = {}};
[rc=0]
$ git grep -n -e 'shallow.sha' -e 'shallow->sha' -e 'shallow.remote_urls' -e 'shallow->remote_urls' -- src
[no output]
[rc=1, expected no-match]
$ git grep -n remote_urls -- src
[no output]
[rc=1, expected no-match]
```

There are two boundary-only constructions and zero mirror population/consumer
sites for shallow-carried SHA or remotes. The former false no-match claim for
literal `Shallow{` is retired.

### (j) exact classifier order and fence nonserialization census

```text
$ grep -nE 'Classification::Fence::(submodule|nested|unmerged)|--is-shallow-repository|result\.entry\.shallow =|head_state = HeadState::unborn|status", "--porcelain|Classification::Fence::dirty' src/core/repo/classify.cpp
134:    result.fence = Classification::Fence::submodule;
146:    result.fence = Classification::Fence::nested;
179:    result.fence = Classification::Fence::unmerged;
200:  auto shallow = invoke_classify({"rev-parse", "--is-shallow-repository"},
216:    result.entry.shallow = std::move(metadata);
222:    result.entry.head_state = HeadState::unborn;
347:  auto dirt = invoke_classify({"status", "--porcelain=v2", "-z"},
354:    result.fence = Classification::Fence::dirty;
[rc=0]
$ awk '/result\.fence = Classification::Fence::(submodule|nested|unmerged)/ {need=1} need && /return result;/ {lines=(lines?lines ",":"") NR; max=NR; need=0} /--is-shallow-repository/ && !probe {probe=NR} END {print "tier1_return_lines=" lines " first_shallow_probe=" probe; exit !(max < probe)}' src/core/repo/classify.cpp
tier1_return_lines=139,150,184 first_shallow_probe=200
[rc=0]
$ awk '/--is-shallow-repository/ && !probe {probe=NR} !probe && /return result;/ {before=NR} /result\.entry\.shallow =/ && !population {population=NR} END {print "last_return_before_shallow=" before " first_shallow_probe=" probe " first_shallow_population=" population; exit !(before < probe && probe < population)}' src/core/repo/classify.cpp
last_return_before_shallow=184 first_shallow_probe=200 first_shallow_population=216
[rc=0]
$ awk '/result\.entry\.shallow =/ && !population {population=NR} /head_state = HeadState::unborn/ && !unborn {unborn=NR} /status", "--porcelain=v2"/ && !dirty {dirty=NR} END {print "first_shallow_population=" population " unborn=" unborn " dirty_probe=" dirty; exit !(population < unborn && unborn < dirty)}' src/core/repo/classify.cpp
first_shallow_population=216 unborn=222 dirty_probe=347
[rc=0]
$ git grep -n 'Classification::Fence' -- src/core/manifest src/core/pack
[no output]
[rc=1, expected no-match]
```

### E4 exact request trace

```text
$ sed -n '1711,1753p' tests/test_repo_engine.cpp
TEST_CASE(
    "restore dispatch leaves zero-ref and shallow payload trees untouched") {
  std::vector<biv::support::SpawnRequest> requests;
  auto git = resolved_git(
      [&](const auto &request) { requests.push_back(request); });
  TempDir root{"restore-payload-branches"};
  const auto partial = root.path() / "partial";
  touch(partial / "empty/payload.txt", "payload\n");
  biv::repo::RepoEntry empty;
  empty.id = "empty";
  empty.relpath = "empty";
  empty.head_state = biv::repo::HeadState::unborn;

  auto payload =
      biv::repo::restore_entry(git, empty, partial, root.path() / "stage");

  REQUIRE(payload.has_value());
  CHECK(payload->outcome == biv::repo::RepoRestoreOutcome::payload_only_unborn);
  CHECK(std::filesystem::is_regular_file(partial / "empty/payload.txt"));
  CHECK_FALSE(std::filesystem::exists(partial / "empty/.git"));
  REQUIRE(payload->advisories.size() == 1);
  CHECK(payload->advisories[0] == "EmptyRepoPayloadOnly");

  touch(partial / "shallow/file.txt", "shallow payload\n");
  biv::repo::RepoEntry shallow;
  shallow.id = "shallow";
  shallow.relpath = "shallow";
  shallow.sha = "0123456789012345678901234567890123456789";
  shallow.head_state = biv::repo::HeadState::unborn;
  shallow.shallow = biv::repo::Shallow{
      .boundary = {"0123456789012345678901234567890123456789"}};

  auto pointer =
      biv::repo::restore_entry(git, shallow, partial, root.path() / "stage");

  REQUIRE(pointer.has_value());
  CHECK(pointer->outcome == biv::repo::RepoRestoreOutcome::shallow_pointer);
  REQUIRE(pointer->shallow.has_value());
  CHECK(pointer->sha == shallow.sha);
  CHECK(pointer->shallow->boundary == shallow.shallow->boundary);
  CHECK(requests.empty());
  CHECK_FALSE(std::filesystem::exists(partial / "shallow/.git"));
}
[rc=0]
$ ./build/ci-macos/biv_repo_engine_tests 'restore dispatch leaves zero-ref and shallow payload trees untouched' --reporter compact
Filters: "restore dispatch leaves zero-ref and shallow payload trees untouched"
RNG seed: 1671824834
All tests passed (13 assertions in 1 test case)
[rc=0]
```

### T-1 through T-5

- T-1 manifest.hpp numstat `2/2`: only `repos` to `repos{}` and serialize string
  to expected string; rc=0.
- T-2: the three inherited aggregates intentionally still omit `.repos`; they
  are untouched. Exact proof:

  ```text
  $ git diff 9e6ebe8..HEAD -- src/core/pack/pack.cpp tests/test_cli.cpp tests/test_open.cpp | grep -c 'repos'
  0
  [rc=1, grep -c zero-match semantics; printed integer is the gate]
  ```
- T-4 typed-error literal multiset unchanged b09..HEAD; rc=0.
- Exact checkpoint paths: manifest.cpp, manifest.hpp, test_manifest.cpp; rc=0.
- Four manifest warning folds: const-char enum key, pointer RepoRowFacts row,
  checked repos lookup, checked notes lookup. Test change only `dot{}` (`1/1`).
- No NOLINT addition; no-match rc=1. T-3 carried below. T-5 no protocol change.

## macOS full suite

```text
$ cmake --preset ci-macos
[rc=0]
$ cmake --build --preset ci-macos
[rc=0]
$ ctest --preset ci-macos --output-on-failure
84% tests passed, 3 failed of 19; total 857.09 sec
[rc=8]
```

All candidate product rows passed. Registered/configured rows: harness-selftest
119 red/884 green due ambient `ANTHROPIC_API_KEY` (value not exposed);
harness-e2 closed R-4.37, not re-diagnosed; hardening `readelf unavailable`;
ASan/tidy/fuzz configured skips.

```text
$ env -u ANTHROPIC_API_KEY ./build/ci-macos/biv_tests 'FX-O*' --reporter compact
All tests passed (803 assertions in 11 test cases) [rc=0]
$ env -u ANTHROPIC_API_KEY ./build/ci-macos/biv_tests 'FX-N*' --reporter compact
All tests passed (135 assertions in 5 test cases) [rc=0]
```

## Linux full parity battery

Host `gh` downloaded exactly eight LLVM 22.1.8 amd64 debs outside the worktree.
`sha256sum --check --strict SHA256SUMS` printed eight OK rows, rc=0; exact asset
count rc=0. SHA256SUMS:

```text
c35ae50ecf7704b3dd0278837c4c223e72318e15de6869e3c73b58fbc64b547d  clang-22_..._amd64.deb
1e5917c1cd027548aff5cd35ee4f781a867d5daf03d9eb92611fc838ae9fa3dc  clang-tidy-22_..._amd64.deb
05215c729cd18307e2bbfb710505b034e3ced630f68e146d4c0762877073c085  clang-tools-22_..._amd64.deb
a722846476ee806a76710eea0c8cc63b18082b55eac8e2c6f092b7495a054240  libclang-common-22-dev_..._amd64.deb
4c558366775f03a236a98a3e26f0f09ffab9d5df32c40050cee94c7aeca1ca44  libclang-cpp22_..._amd64.deb
8488e5d288780d269c3516855247542f269bafafc55699502625f3ebdabce73b  libclang1-22_..._amd64.deb
061b48c5a47589db2ee24bcba17aebb258c973bfa41e5bdc8e46a64ea4244ceb  libllvm22_..._amd64.deb
f397059ac1ab2a8ea2a5707d7eec2dac6724f2f141e4668b75d08da62dd4280a  llvm-22-linker-tools_..._amd64.deb
```

Topology: Ubuntu 24.04, amd64, `--init`, repo/mirror read-only, frozen packages
including openssh-client, canonical deb validation/install, uid/gid 1001,
branch clone without hardlinks, exact HEAD, WSL fixture as suite user, runuser
nofile soft=hard, harness venv, and no-short-circuit post-CTest ledger.

```text
expected_head=a2f6fd1adf67fd86c8d0c692db34f113a9691135
observed_head=a2f6fd1adf67fd86c8d0c692db34f113a9691135
nofile_before=1024
nofile_hard=1048576
nofile_after=1048576
base-provision=0
deb-provision=0
transition=0
fixture=0
nofile=0
harness-venv=0
configure=0
build=0
ctest=8
tidy-row-gate=0
a6-fabric-success=0
catch2-xml=0
count-read=1
linux_battery_aggregate_rc=1
container_suite_rc=1
```

GCC 13.3 build reached every target. All candidate product rows, tidy (65.32s),
hardening, Werror, and E2 passed. Tidy gate said EXECUTED/PASSED. ASan/fuzz
configured skips. Only CTest red was registered R-4.35 harness-selftest:
3 failed, 996 passed, 3 skipped:

```text
test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite
test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop
test_credential_scanner_detects_entry_added_after_directory_enumeration
```

Post-CTest continued: A6 127 assertions/12 cases rc=0; XML rc=0; count got
420/0/0/1 versus pinned 412/0/0/1, rc=1, registered R-4.38 and never readiness.

### T-3 carried independent warning census

Controller Step-4b exact a2 patch SHA
`453bb3374885f799e4066b619655fc04df132e5301e80514a8002af273b45257`
used the same Linux topology and three checkpoint files. Configure/build/tidy
all rc=0 and reached every target:

```text
missing_initializer_count=0
coverage_line_count=1
coverage_failure_count=0
17: clang-tidy coverage: 37 results == 37 sources
step4b_aggregate_rc=0
suite_rc=0
copy_evidence_rc=0
step4b_container_aggregate_rc=0
```

File SHA prefixes: `fd12d52...` hpp, `f7a89c8...` cpp, `60aace29...` test.
Evidence home `/tmp/bivpak-intg-rev15.zu1UX0`; host restored clean at exact a2.

## Evidence hashes

```text
e312a3c68de4cf622a9770737dbc39c887c3b957d54cec105bdfa5eb3ea398fe  static-fences.log
b39073941acbb64886f951c4cc8bd8a10e98f34dee1833347cbf00eb625bc5c2  macos-configure.log
a282885cbe7f3da446c88d6531acc35fe0045fe7a3d9328bbf791f8a090f7b06  macos-build.log
3d91beac405cf0b8e3d10c48dfe6d1ad95fde2eaa167b39b2c0c1d42222e4308  macos-ctest.log
d77d6d27f8d9905416966427578f4fe97f66b8761862536b3fae98ed31fe298e  linux-battery.log
07e449e144d0971c40ddd7b8b1e9a86816de764f606202004e88be5d0d204e2d  run-battery.sh
84d5a71e6268da6e1b906a565cd8cdcc83349211702214d1d3652dd2396bbcf2  suite-run.sh
```

Temp paths are provenance, not durable dependencies; required evidence is here.

## Carried evidence, residuals, and green gates

- Task 3 controller-reported dual CLEAN and committed; exact allowlist ruling
  231935.
- R-4.35 Linux three race controls retained-not-cited; R-4.37 not re-diagnosed;
  R-4.38 count disclosed and never readiness.
- Candidate gates green: exact digest/SHA/scope; C-1/C-3/C-4/C-5; T-1..T-5;
  A/B/FX-O/(i)/(j)/E4; macOS product/focused rows; Linux build/product/tidy/
  hardening/A6/XML.
- No candidate-attributable red and no Task-4 evidence STOP.

## C-7 dispatched scope receipt

The incoming mechanical scope is all-in and contains the exact TEN paths:

```text
SCOPE_DIFF:
- src/core/repo/classify.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/restore.cpp -> in
- src/core/manifest/manifest.hpp -> in
- src/core/manifest/manifest.cpp -> in
- tests/test_repo_engine.cpp -> in
- tests/test_manifest.cpp -> in
- src/core/pack/pack.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_open.cpp -> in
SCOPE_DIFF_RESULT: all-in
ROW_TRUTH_CHECK: required
```

Every incoming `SCOPE_ROW_EVIDENCE` row was checked against the candidate. The
three propagation rows each carry ruling `231935` as required by C-7:

```text
SCOPE_ROW_EVIDENCE:
- src/core/pack/pack.cpp: ASK-6 ruling 231935 arm (a), C-1/C-2/C-3 + 183510 T-2 — the propagation hunk at :765/:778 (+5/-2, braced per 034802) already in the candidate; the aggregate :753-764 is NOT edited; NOTHING else
- tests/test_cli.cpp: ASK-6 ruling 231935 arm (a), C-1/C-2/C-3 + 183510 T-2 — has_value + move at :192 (+3/-1) already in the candidate; the fixture aggregate :92-101 is NOT edited; NOTHING else
- tests/test_open.cpp: ASK-6 ruling 231935 arm (a), C-1/C-2/C-3 + 183510 T-2 — has_value + const-ref deref at :131 (+3/-1) already in the candidate; the fixture aggregate :79-88 is NOT edited; NOTHING else
```

The other seven rows reconcile to landed Task 1/2 bytes or the six authorized
checkpoint hunks: manifest.hpp `repos{}`, four manifest.cpp warning folds,
test_manifest `dot{}`, and no other byte. C-7 is green.

## Controller review requests (not sent/filed)

Request m-1 and m-3 independent byte review through the controller of the exact
candidate/digest, C/T fences, census, E4, writer-unit-only C-4, Linux topology,
tidy execution, and residual non-citation. This seat did not send/file a relay.

## Explicit NOT-DONE

- No product/test/docs/governed relay/plan byte edited.
- No commit, ref mutation, push, merge, PR, remote CI, publish, deploy, release,
  or closure.
- No Docker prune/removal of unrelated resources.
- No credential material copied, printed, or retained.
- No pack-level FX-O test; required witness is writer-unit-only.
- No 2b wiring.
- No `--offline` parity arm (product-scope-due under sealed N).
- No m-3 rendering or wording change.
- No m-1/m-3 review relay sent/filed.

## Final worktree receipt

```text
$ git rev-parse HEAD
a2f6fd1adf67fd86c8d0c692db34f113a9691135
[rc=0]
$ git status --short --untracked-files=all
[no output]
[rc=0]
$ git diff --cached --quiet
[rc=0]
$ git diff --check 46df8f3..HEAD
[no output]
[rc=0]
$ git diff --name-only 46df8f3..HEAD | sort
src/core/manifest/manifest.cpp
src/core/manifest/manifest.hpp
src/core/pack/pack.cpp
src/core/repo/classify.cpp
src/core/repo/restore.cpp
src/core/repo/types.hpp
tests/test_cli.cpp
tests/test_manifest.cpp
tests/test_open.cpp
tests/test_repo_engine.cpp
[rc=0]
```

The report is ignored evidence metadata, so its authorized update does not alter
the tracked/cached candidate receipts above.
