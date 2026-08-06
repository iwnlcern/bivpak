# Slice A — nine mutation receipts run trace

Reviewed head: `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`

Authority read before execution:

- `docs/sprints/2026-08-04-s4-step4/plans/2026-08-05-s4-floor-fold-plan.md` lines 21–25, 138, 191–193
- `DESIGN-PLANNER-M2-GATE3-MEASURED-TWELVE-RECEIPTS-CIRCULARITY-G5-DISPOSED-20260804-170500.md` §3
- `DESIGN-PLANNER-M2-TWELVE-A5-RECEIPT-PLANS-UNDERTAKING-DISCHARGED-20260804-224200.md` §§4b, 4d, 5
- `2026-07-13-rclass2-fixture-evidence-map.md` §8

Protocol: each arm is correct-code GREEN → one isolated mutation → intended RED with required sibling observations → exact inverse → same-command GREEN → temporary instrument removal → clean diff. No mutation or temporary test is committed.

Parent-provided exact-head validation (not independently rerun during this receipt replay): all 14 locally applicable CTest rows passed. The safety-hardening row was excluded only on Darwin because its `readelf` prerequisite is unavailable. Branch topology remained one Slice A commit over `ff63e521d8ae5229a831aab8718a3fa58205f40f` (`git rev-list --count ff63e52..HEAD` → `1`).

## Receipt summary

| # | Receipt | Correct GREEN | Intended RED | Required sibling observation | Post-inverse GREEN |
|---:|---|---|---|---|---|
| 1 | O3 Codex default disclosure | 27/27 | visibility only, 26/27 | install + verdict green | 27/27 |
| 2 | O3 Claude default disclosure | 27/27 | visibility only, 26/27 | install + verdict green | 27/27 |
| 3 | `FX-VF-O6/claude/no-image-field-in-derivation` | 12/12 | exact vector + purity, 10/12 | install/refusal outcomes green | 12/12 |
| 4 | `FX-VF-O6/codex/no-image-field-in-derivation` | 12/12 | exact vector + purity, 10/12 | install/refusal outcomes green | 12/12 |
| 5 | O4 Codex real-NUL ordering | 65/65 | ordering + detail, 62/65 | exact row 7 and exit 2 green | 65/65 |
| 6 | O4 Claude real-NUL ordering | 65/65 | ordering and all mapped siblings, 56/65 | raw row 0 and exit 0 recorded | 65/65 |
| 7 | MG7 Codex full grammar | 112/112 | Codex hostile matrix, 72/112 | Claude 56/56 green | 112/112 |
| 8 | MG7 Claude full grammar | 112/112 | Claude hostile matrix, 72/112 | Codex 56/56 green | 112/112 |
| 9 | A5.8 silent promotion | 6/6 | both O7 loud lines, 4/6 | frozen inputs + both MINs green | 6/6 |

## 1. `FX-VF-O3/codex/disclosure-default-visible`

Discriminating-input-class precheck: **YES**. The Codex host `0.300.0` above survey `0.144`, readable-newer verdict, successful forward install, and default-render channel all exist at the reviewed head. The shipped render fixture combined both legs and did not bind install success separately, so a temporary receipt-only test was added to `tests/test_render.cpp` and paired with the existing Codex grammar/direction install test.

Temporary setup diff:

```diff
+TEST_CASE("RECEIPT FX-VF-O3 codex default disclosure") {
+  // Constructs readable Codex 0.300.0 with newer_than_survey=true.
+  // Asserts verdict readable, wire verdict readable-newer-than-survey,
+  // and the exact default-visible loud line.
+}
```

Exact focused command, used before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O3 codex default disclosure,Codex install uses grammar and direction instead of an allowlist'
```

Correct-code GREEN (seed `2093554264`):

```text
Codex forward install: outcome installed; host_version_unverified true; activation size 1; sessions path exists — all PASSED.
Receipt verdict: readable — PASSED.
Receipt wire verdict: "readable-newer-than-survey" — PASSED.
Receipt default loud-line `find(...) != npos` — PASSED.
All tests passed (27 assertions in 2 test cases)
```

One isolated mutation:

```diff
diff --git a/src/core/open/render.cpp b/src/core/open/render.cpp
@@
     if (agent.caps.has_value() &&
+        agent.agent != "codex" &&
         agent.caps->wire_verdict() == "readable-newer-than-survey") {
```

Observed intended RED (same command, seed `1228704767`):

```text
Codex install test case: PASSED (23 assertions), including forward outcome installed,
host_version_unverified true, activation size 1, and sessions path exists.
Receipt verdict readable: PASSED.
Receipt wire verdict readable-newer-than-survey: PASSED.
Exact receipt loud-line check: FAILED:
  CHECK(text.find("codex host version 0.300.0 is newer than surveyed through 0.144; session import compatibility is uncertain") != std::string::npos)
with expansion: npos != npos
test cases: 2 | 1 passed | 1 failed
assertions: 27 | 26 passed | 1 failed
```

Thus only default visibility reddened; install and verdict siblings stayed GREEN.

Complete inverse: removed only `agent.agent != "codex" &&`. Post-revert same-command GREEN (seed `1179988306`): `All tests passed (27 assertions in 2 test cases)`.

The temporary test block was then removed with its exact inverse. Clean proof:

```text
$ git diff --exit-code
(no output; exit 0)
$ git status --short
(no output)
$ git rev-parse HEAD
26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6
```

## 2. `FX-VF-O3/claude/disclosure-default-visible`

Discriminating-input-class precheck: **YES**. The Claude host `2.9.0` above survey `2.1`, readable-newer verdict, successful forward install, and default-render channel exist. A per-leg temporary receipt test was added to `tests/test_render.cpp`, paired with the existing Claude grammar/direction install test.

Temporary setup diff:

```diff
+TEST_CASE("RECEIPT FX-VF-O3 claude default disclosure") {
+  // Constructs readable Claude 2.9.0 with newer_than_survey=true.
+  // Asserts readable verdict, readable-newer-than-survey wire state,
+  // and the exact default-visible loud line.
+}
```

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O3 claude default disclosure,Claude install uses grammar and direction instead of an allowlist'
```

Correct-code GREEN (seed `3469422775`): Claude forward install outcome installed, `host_version_unverified` true, activation size 1, projects path present; receipt verdict and wire verdict passed; exact loud line was present. `All tests passed (27 assertions in 2 test cases)`.

One isolated mutation:

```diff
diff --git a/src/core/open/render.cpp b/src/core/open/render.cpp
@@
     if (agent.caps.has_value() &&
+        agent.agent != "claude-code" &&
         agent.caps->wire_verdict() == "readable-newer-than-survey") {
```

Observed intended RED (same command, seed `845440388`):

```text
Claude install test case: PASSED (23 assertions), including forward installed,
host_version_unverified true, activation size 1, projects path exists.
Receipt readable verdict: PASSED.
Receipt readable-newer-than-survey wire verdict: PASSED.
Exact receipt loud-line check: FAILED:
  CHECK(text.find("claude-code host version 2.9.0 is newer than surveyed through 2.1; session import compatibility is uncertain") != std::string::npos)
with expansion: npos != npos
test cases: 2 | 1 passed | 1 failed
assertions: 27 | 26 passed | 1 failed
```

Only visibility reddened; install and verdict siblings stayed GREEN.

Complete inverse removed only `agent.agent != "claude-code" &&`. Post-revert same-command GREEN (seed `2299722715`): `All tests passed (27 assertions in 2 test cases)`. Temporary test removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 3. `FX-VF-O6/claude/no-image-field-in-derivation`

Discriminating-input-class precheck: **YES**. Claude admission consumes `agent_version_at_pack`, while the installed-row watermark derives only from the fixed host capability. A temporary install-level instrument swept the exact required image bases `{absent, null, 0.0.1, 0.142.5, 0.300.0}` under fixed readable Claude host `2.9.0` with `newer_than_survey=true`.

Temporary setup diff:

```diff
+TEST_CASE("RECEIPT FX-VF-O6 claude derivation purity") {
+  // Runs each exact basis in an isolated target store under fixed host 2.9.0.
+  // Binds label|outcome|detail|host_version_unverified before and after.
+}
```

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O6 claude derivation purity'
```

Correct-code GREEN (seed `2495259495`):

```text
absent|failed|basis_unorderable|false
null|failed|basis_unorderable|false
0.0.1|installed|-|true
0.142.5|installed|-|true
0.300.0|installed|-|true
FX-VF-O6/claude/decision-vector-exact — PASSED
FX-VF-O6/claude/no-image-field-in-derivation — PASSED
All tests passed (12 assertions in 1 test case)
```

One isolated mutation fed the parsed image basis into the installed-row watermark derivation:

```diff
diff --git a/src/adapters/claude_code/install.cpp b/src/adapters/claude_code/install.cpp
@@
+  const auto surveyed = version_floor::parse_grammar(
+      version_floor::row_for("claude-code").surveyed_through);
+  assert(surveyed.has_value());
   return {.admitted = true,
-          .host_version_unverified = caps.newer_than_survey(),
+          .host_version_unverified =
+              version_floor::compare_line(*basis, *surveyed) ==
+              version_floor::Order::greater,
           .detail = {}};
```

Observed intended RED (same filter with `--success`, seed `2811947710`):

```text
Before vector:
  absent false; null false; 0.0.1 true; 0.142.5 true; 0.300.0 true
After vector:
  absent false; null false; 0.0.1 false; 0.142.5 false; 0.300.0 false
FX-VF-O6/claude/decision-vector-exact — FAILED
FX-VF-O6/claude/no-image-field-in-derivation — FAILED
All ten install/result sibling REQUIREs stayed PASSED.
test cases: 1 | 0 passed | 1 failed
assertions: 12 | 10 passed | 2 failed
```

All three valid `0.x` image bases moved against Claude survey `2.1`, while invalid-basis refusal and every install outcome remained fixed. This is the exact forbidden image-field dependency.

Complete inverse restored `caps.newer_than_survey()` as the sole watermark source. Post-revert same-command GREEN (seed `2198900590`): `All tests passed (12 assertions in 1 test case)`. Temporary instrument removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 4. `FX-VF-O6/codex/no-image-field-in-derivation`

Discriminating-input-class precheck: **YES**. At the reviewed head, Codex install admission consumes `agent_version_at_pack`, while the installed-row watermark is derived only from the fixed host capability. The temporary instrument swept the required image-basis vector `{absent, null, 0.0.1, 0.142.5, 0.300.0}` under one fixed readable Codex host `0.300.0` with `newer_than_survey=true`.

Temporary setup diff:

```diff
+TEST_CASE("RECEIPT FX-VF-O6 codex derivation purity") {
+  // Installs one record for each exact basis in an isolated store.
+  // Captures label|outcome|detail|host_version_unverified.
+  // Binds both the exact decision vector and invariance across valid bases.
+}
```

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O6 codex derivation purity'
```

Correct-code GREEN (seed `1395678602`):

```text
absent|failed|basis_unorderable|false
null|failed|basis_unorderable|false
0.0.1|installed|-|true
0.142.5|installed|-|true
0.300.0|installed|-|true
FX-VF-O6/codex/decision-vector-exact — PASSED
FX-VF-O6/codex/no-image-field-in-derivation — PASSED
All tests passed (12 assertions in 1 test case)
```

One isolated mutation fed the parsed image basis into the installed-row watermark derivation:

```diff
diff --git a/src/adapters/codex/install.cpp b/src/adapters/codex/install.cpp
@@
+  const auto surveyed = version_floor::parse_grammar(
+      version_floor::row_for("codex").surveyed_through);
+  assert(surveyed.has_value());
   return {.admitted = true,
-          .host_version_unverified = caps.newer_than_survey(),
+          .host_version_unverified =
+              version_floor::compare_line(*basis, *surveyed) ==
+              version_floor::Order::greater,
           .detail = {}};
```

Observed intended RED (same filter with `--success`, seed `3057742409`):

```text
Before vector:
  absent false; null false; 0.0.1 true; 0.142.5 true; 0.300.0 true
After vector:
  absent false; null false; 0.0.1 false; 0.142.5 false; 0.300.0 true
FX-VF-O6/codex/decision-vector-exact — FAILED
FX-VF-O6/codex/no-image-field-in-derivation — FAILED
All ten install/result sibling REQUIREs stayed PASSED.
test cases: 1 | 0 passed | 1 failed
assertions: 12 | 10 passed | 2 failed
```

The exact vector moved only where image-basis comparison would move it, proving the purity assertion is discriminating rather than decorative. Invalid-basis refusal and all install outcomes remained unchanged.

Complete inverse restored `caps.newer_than_survey()` as the sole watermark source. Post-revert same-command GREEN (seed `1214767663`): `All tests passed (12 assertions in 1 test case)`. The temporary test was then removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 5. `FX-VF-O4/codex/basis-nul-bearing/refuses-before-comparison`

Discriminating-input-class precheck: **YES**. The exact seven-byte basis `0.144.` + real NUL predates/straddles A7 and is accepted by the manifest model but rejected by full grammar. The fixed readable Codex host is `0.142.5`, so an ordering-first implementation can truncate to `0.144`, compare, and expose that comparison. A temporary session-leg instrument used the real Codex adapter and recorded the mapped row and exit; it was paired with the shipped eight-case hostile-basis adapter test.

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O4 codex NUL basis refuses before comparison,FX-VF-O4 and FX-MG-7 codex hostile bases refuse before ordering' --success
```

Correct-code GREEN (seed `658458551`): the probe proved `basis.size() == 7` and `basis.back() == '\0'`; raw session state was reason `basis-unorderable`, detail `basis_unorderable`, exact row enum `agent_not_validated_failed` (`7`), exit `2`, member reads `0`. The shipped adapter test kept all eight hostile cases green. `All tests passed (65 assertions in 2 test cases)`.

One isolated ordering-before-grammar mutation was added only to the Codex admission function. For the real-NUL path it trims the truncatable prefix's terminal dot, parses `0.144`, compares it with host `0.142.5`, and returns the ordering result before the full-string grammar gate:

```diff
diff --git a/src/adapters/codex/install.cpp b/src/adapters/codex/install.cpp
@@
+  const auto nul = image_version.find('\0');
+  if (nul != std::string_view::npos) {
+    auto truncatable_prefix = image_version.substr(0, nul);
+    if (truncatable_prefix.ends_with('.')) {
+      truncatable_prefix.remove_suffix(1);
+    }
+    const auto ordering_basis = version_floor::parse_grammar(truncatable_prefix);
+    const auto ordering_host = version_floor::parse_grammar(caps.agent_version());
+    if (ordering_basis.has_value() && ordering_host.has_value()) {
+      if (version_floor::compare_line(*ordering_host, *ordering_basis) ==
+          version_floor::Order::less) {
+        return {.detail = version_floor::kBasisNewerThanHost};
+      }
+      return {.admitted = true,
+              .host_version_unverified = caps.newer_than_survey(),
+              .detail = {}};
+    }
+  }
   const auto basis = version_floor::parse_grammar(image_version);
```

Observed intended RED (same command, seed `3763361010`):

```text
FX-VF-O4/codex/basis-nul-bearing/refuses-before-comparison — FAILED
raw reason: basis-newer-than-host
FX-VF-O4/codex/adapter-detail — FAILED
raw detail: basis_newer_than_host
FX-VF-O4/codex/exact-row — PASSED; row 7 / agent_not_validated_failed
FX-VF-O4/codex/exit-2 — PASSED; exit 2
member reads — PASSED; 0
Shipped adapter test: only basis-nul-bearing detail failed; the other seven
hostile sublegs, result cardinality, failed outcome, not-validated reason,
empty id_map, and empty activation remained GREEN.
test cases: 2 | 0 passed | 2 failed
assertions: 65 | 62 passed | 3 failed
```

This records the sibling states raw rather than assuming they move: adapter detail moved, while exact row and exit-2 did not.

Complete inverse removed the entire NUL ordering-first block. Post-revert same-command GREEN (seed `1422791818`): `All tests passed (65 assertions in 2 test cases)`. The temporary real-adapter session test and temporary include were removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 6. `FX-VF-O4/claude/basis-nul-bearing/refuses-before-comparison`

Discriminating-input-class precheck: **YES**. The exact five-byte basis `2.1.` + real NUL reaches Claude admission and is rejected by full grammar. Under fixed readable host `2.1.100`, an ordering-first path can truncate to `2.1`, compare, and admit. A temporary real-Claude-adapter session test recorded the mapped row and exit and was paired with the shipped eight-case hostile-basis test.

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT FX-VF-O4 claude NUL basis refuses before comparison,FX-VF-O4 and FX-MG-7 claude hostile bases refuse before ordering' --success
```

Correct-code GREEN (seed `673258085`): the probe proved `basis.size() == 5` and a real terminal NUL. Raw session state was reason `basis-unorderable`, detail `basis_unorderable`, exact row enum `agent_not_validated_failed` (`7`), exit `2`, member reads `0`; all eight shipped hostile sublegs passed. `All tests passed (65 assertions in 2 test cases)`.

The one isolated mutation was the Claude-local equivalent of receipt 5: for NUL input only, parse the truncatable `2.1` prefix and evaluate host ordering before the full-string grammar gate.

```diff
diff --git a/src/adapters/claude_code/install.cpp b/src/adapters/claude_code/install.cpp
@@
+  const auto nul = image_version.find('\0');
+  if (nul != std::string_view::npos) {
+    auto truncatable_prefix = image_version.substr(0, nul);
+    if (truncatable_prefix.ends_with('.')) {
+      truncatable_prefix.remove_suffix(1);
+    }
+    const auto ordering_basis = version_floor::parse_grammar(truncatable_prefix);
+    const auto ordering_host = version_floor::parse_grammar(caps.agent_version());
+    if (ordering_basis.has_value() && ordering_host.has_value()) {
+      if (version_floor::compare_line(*ordering_host, *ordering_basis) ==
+          version_floor::Order::less) {
+        return {.detail = version_floor::kBasisNewerThanHost};
+      }
+      return {.admitted = true,
+              .host_version_unverified = caps.newer_than_survey(),
+              .detail = {}};
+    }
+  }
   const auto basis = version_floor::parse_grammar(image_version);
```

Observed intended RED (same command, seed `511754739`):

```text
FX-VF-O4/claude/basis-nul-bearing/refuses-before-comparison — FAILED
raw reason: -
FX-VF-O4/claude/adapter-detail — FAILED
raw detail: -
FX-VF-O4/claude/exact-row — FAILED; raw row 0 / installed
FX-VF-O4/claude/exit-2 — FAILED; raw exit 0
member reads — PASSED; 0
Shipped adapter test: only basis-nul-bearing moved to installed, with non-empty
id_map and activation; the other seven hostile sublegs remained GREEN.
test cases: 2 | 0 passed | 2 failed
assertions: 65 | 56 passed | 9 failed
```

The required sibling states are recorded raw: on this host all three named siblings moved, rather than being presumed either green or red.

Complete inverse removed the entire NUL ordering-first block. Post-revert same-command GREEN (seed `341233099`): `All tests passed (65 assertions in 2 test cases)`. The temporary real-adapter session test and include were removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 7. `FX-MG-7/codex/full-grammar-red`

Discriminating-input-class precheck: **YES**. The shipped Codex hostile-basis fixture covers absent, null, real NUL, non-numeric, overlong-patch, control, Unicode, and line-valid-but-unparseable inputs. The identical Claude fixture is the required per-leg isolation control; no temporary fixture was needed.

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'FX-VF-O4 and FX-MG-7 codex hostile bases refuse before ordering,FX-VF-O4 and FX-MG-7 claude hostile bases refuse before ordering'
```

Correct-code GREEN (seed `3154077261`): `All tests passed (112 assertions in 2 test cases)` — 56 Codex and 56 Claude assertions.

One isolated Codex-only mutation removed the invalid-full-grammar refusal by admitting an unparseable basis:

```diff
diff --git a/src/adapters/codex/install.cpp b/src/adapters/codex/install.cpp
@@
   const auto basis = version_floor::parse_grammar(image_version);
   if (!basis.has_value()) {
-    return {.detail = version_floor::kBasisUnorderable};
+    return {.admitted = true,
+            .host_version_unverified = caps.newer_than_survey(),
+            .detail = {}};
   }
```

Observed intended RED (combined command with compact reporter, seed `4228561241`): every Codex hostile subleg stopped refusing — outcome became installed (`0` vs failed `2`), reason/detail disappeared, and `id_map`/activation became non-empty. `test cases: 2 | 1 passed | 1 failed`; `assertions: 112 | 72 passed | 40 failed`.

Required other-leg observation while the Codex mutation remained applied:

```text
$ build/dev/biv_tests 'FX-VF-O4 and FX-MG-7 claude hostile bases refuse before ordering'
Randomness seeded to: 1476199824
All tests passed (56 assertions in 1 test case)
```

Thus the mutation reddened only Codex; Claude was unaffected, proving per-leg rather than shared enforcement.

Complete inverse restored `return {.detail = version_floor::kBasisUnorderable};`. Post-revert same-command GREEN (seed `3450339330`): `All tests passed (112 assertions in 2 test cases)`.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 8. `FX-MG-7/claude/full-grammar-red`

Discriminating-input-class precheck: **YES**. The shipped Claude fixture exercises all eight hostile full-grammar classes, with the Codex fixture as the required unaffected-leg control.

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'FX-VF-O4 and FX-MG-7 codex hostile bases refuse before ordering,FX-VF-O4 and FX-MG-7 claude hostile bases refuse before ordering'
```

Correct-code GREEN (seed `3921190158`): `All tests passed (112 assertions in 2 test cases)`.

One isolated Claude-only mutation removed its invalid-full-grammar refusal:

```diff
diff --git a/src/adapters/claude_code/install.cpp b/src/adapters/claude_code/install.cpp
@@
   const auto basis = version_floor::parse_grammar(image_version);
   if (!basis.has_value()) {
-    return {.detail = version_floor::kBasisUnorderable};
+    return {.admitted = true,
+            .host_version_unverified = caps.newer_than_survey(),
+            .detail = {}};
   }
```

Observed intended RED (combined command with compact reporter, seed `3527569928`): every Claude hostile subleg stopped refusing — outcome installed (`0` vs failed `2`), reason/detail absent, and `id_map`/activation non-empty. `test cases: 2 | 1 passed | 1 failed`; `assertions: 112 | 72 passed | 40 failed`.

Required other-leg observation while the Claude mutation remained applied:

```text
$ build/dev/biv_tests 'FX-VF-O4 and FX-MG-7 codex hostile bases refuse before ordering'
Randomness seeded to: 2421877536
All tests passed (56 assertions in 1 test case)
```

Only Claude reddened; Codex remained green, satisfying per-leg separation.

Complete inverse restored the Claude `basis_unorderable` refusal. Post-revert same-command GREEN (seed `3276202413`): `All tests passed (112 assertions in 2 test cases)`.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

## 9. `A5.8/silent-promotion`

Discriminating-input-class precheck: **YES**. The shipped O7 render fixture freezes `0.145.0` and `2.2.0` but injects the newer-state boolean, so a temporary receipt-only test was required to obtain that state from the real Codex and Claude capability derivations. Its host probe literals remained exactly Codex `0.145.0` and Claude `2.2.0`; MIN assertions remained exactly `0.142` and `2.1`.

Exact focused command, before mutation and after inverse:

```sh
cmake --build build/dev -j4 --target biv_tests && build/dev/biv_tests 'RECEIPT A5.8 silent promotion with frozen O7 inputs' --success
```

Correct-code GREEN (seed `4169873715`):

```text
codex_version  = 0.145.0
claude_version = 2.2.0
codex_wire     = readable-newer-than-survey
claude_wire    = readable-newer-than-survey
codex_min      = 0.142
claude_min     = 2.1
FX-VF-O7/codex/above-survey/loud-line-default-visible — PASSED
FX-VF-O7/claude/above-survey/loud-line-default-visible — PASSED
All tests passed (6 assertions in 1 test case)
```

One isolated product mutation raised `surveyed_through` only, leaving both MIN fields untouched:

```diff
diff --git a/src/adapters/version_floor.cpp b/src/adapters/version_floor.cpp
@@
-constexpr FloorRow kCodexFloor{"0.142", "0.144"};
-constexpr FloorRow kClaudeCodeFloor{"2.1", "2.1"};
+constexpr FloorRow kCodexFloor{"0.142", "0.145"};
+constexpr FloorRow kClaudeCodeFloor{"2.1", "2.2"};
```

Before the RED run, the unchanged temporary-test diff was searched and still contained the literal O7 inputs `0.145.0` and `2.2.0`, plus the frozen MIN assertions. No test input was retuned.

Observed intended RED (same command, seed `330124780`):

```text
codex_version  = 0.145.0                         — PASSED frozen input
claude_version = 2.2.0                           — PASSED frozen input
codex_min      = 0.142                           — PASSED frozen MIN
claude_min     = 2.1                             — PASSED frozen MIN
codex_wire     = readable                        — became quiet at survey
claude_wire    = readable                        — became quiet at survey
FX-VF-O7/codex/above-survey/loud-line-default-visible — FAILED (npos)
FX-VF-O7/claude/above-survey/loud-line-default-visible — FAILED (npos)
assertions: 6 | 4 passed | 2 failed
```

Both exact O7 loud-line assertions reddened while all four frozen-input/MIN assertions stayed green; this is the silent-promotion falsifier with no oracle retune.

Complete inverse restored surveyed-through `0.144` / `2.1`. Post-revert same-command GREEN (seed `1929154726`): `All tests passed (6 assertions in 1 test case)`. The temporary real-capability test and its temporary includes were removed by exact inverse.

Clean proof: `git diff --exit-code` exit 0; `git status --short` empty; HEAD `26e6eb1fbe57401e9ed3c931a57f0d8863d96fd6`.

Remote boundary: no commit, push, PR, GitHub CI/CD action, merge, release, or other remote operation was performed.
