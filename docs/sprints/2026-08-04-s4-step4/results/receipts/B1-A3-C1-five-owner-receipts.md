# B1 fold A3 C1 five-owner mutation receipts

Run date: 2026-08-06
Branch: `s4-floor/b1-codex-liveness`
Committed starting head: `d5642ed9ea19cd6256276681b63199adff21aea4`
Final folded `src/adapters/codex/codex.cpp` SHA-256:
`6f8ec5721e7aed0950d6d2a16bc2463cf5f5085412594fafc338ea8ae1f318cf`

These receipts execute Amendment A3's five Codex read-side owner arms against the
final staged B1 fold bytes. The intended fold and its one `codex_adapter_file` anchor
recapture were staged first, so each `git diff -- src/adapters/codex/codex.cpp`
captured only the disposable mutation. Every mutation used the same C1 command:

```sh
/Library/Frameworks/Python.framework/Versions/3.12/bin/python3.12 -m pytest \
  harness/selftest/test_e3_asserts.py::test_drift_tripwire_is_green_at_pinned_source -q
```

Before the mutation arms, the executable five-owner enumeration exited `0`:

```text
.....                                                                    [100%]
5 passed in 0.50s
```

The pinned-source control also exited `0` (`1 passed in 0.44s`).

## Common RED assertion

Every arm below exited `1` with the same relevant failure:

```text
AssertionError: assert ['C1 drift tripwire RED: adapter session-location source changed (codex_adapter_file)'] == []
FAILED harness/selftest/test_e3_asserts.py::test_drift_tripwire_is_green_at_pinned_source
1 failed
```

After each inverse patch, `git diff --exit-code --
src/adapters/codex/codex.cpp` exited `0`, and `shasum -a 256` returned the final
folded hash above before the next arm.

## Arm 1 — inventory glob

```diff
-.globs = {"sessions/**/rollout-*.jsonl"}
+.globs = {"sessions/**/rollout-*.jsonl", "x/**"}
```

Observed result: exact common C1 RED; mutation reverted; folded hash restored.

## Arm 2 — primary-store discovery

```diff
-StoreLocator{.kind = "sessions_root", .path = root / "sessions"}
+StoreLocator{.kind = "sessions_root", .path = root / "sessions_moved"}
```

Observed result: exact common C1 RED; mutation reverted; folded hash restored.

## Arm 3 — archived-store discovery

```diff
-.path = root / "archived_sessions"
+.path = root / "archived_sessions2"
```

Observed result: exact common C1 RED; mutation reverted; folded hash restored.

## Arm 4 — novel StoreLocator/Store insertion

```diff
 expected<std::vector<Store>> discover(const Env& env) const override {
   std::vector<Store> stores;
+  stores.push_back(Store{
+      .root = env.home / ".codex",
+      .locators = {StoreLocator{.kind = "sessions_root",
+                                .path = env.home / "legacy_sessions"}},
+      .tier = DiscoveryTier::defaults,
+      .archived = false});
```

Observed result: exact common C1 RED; mutation reverted; folded hash restored.

## Arm 5 — post-initializer ArtifactClass insertion

```diff
 value.caveat_facts.relocated_contents.insert(
     value.caveat_facts.relocated_contents.end(), value.never_collect.begin(),
     value.never_collect.end());
+value.collect.push_back(ArtifactClass{.name = "late-sessions",
+                                      .globs = {"late-sessions/**"}});
```

Observed result: exact common C1 RED; mutation reverted; folded hash restored.

## Post-revert control and class-scoped no-touch proof

After all five reversions, the pinned-source control exited `0` (`1 passed in
0.43s`) and the `codex.cpp` SHA-256 again matched the recaptured literal.

The folded candidate was checked from `fabc079` through the staged final tree:

```sh
git diff --cached --unified=0 fabc079 -- src/adapters/codex/codex.cpp |
  rg '^[+-][^+-].*(sessions/\*\*/rollout-\*\.jsonl|root / "sessions"|archived_sessions|StoreLocator|stores\.push_back|value\.collect\.push_back|ArtifactClass)'
```

The command emitted no lines and `rg` exited `1`, its expected no-match result. Thus
the folded B1 product diff touches none of the five enumerated owner classes:
inventory glob, primary-store discovery, archived-store discovery, novel
StoreLocator/Store insertion, or post-initializer `ArtifactClass` insertion. This is
the required class-scoped statement, not a bare global negative.

The five-arm ceremony remains materially burdensome: it requires staged-baseline
management, ten disposable source edits, five expected failing harness invocations,
five byte-restoration checks, and the final green control for each per-head recapture.
That burden is reported here rather than silently absorbed, preserving the upstream
R-3.40 item (11) trigger.
