# Harness Safety Gates

These rows are merge-gating for the Step-2 harness and consume the s2-core target names
`fuzz_manifest_json` and `fuzz_tar_member`.

Runnable rows:

- `safety-build-werror`: builds `biv_tests` from the active CMake tree, consuming the
  product `-Wall -Wextra -Werror` settings.
- `safety-asan-ubsan`: runs `biv_tests` only when the active CMake tree is bound to
  sanitizer flags, with ASan/UBSan abort options set by CTest.
- `safety-tidy-analyzer`: runs `clang-tidy` through `ci/run_clang_tidy.py` over
  product `src/` files from `compile_commands.json`, with analyzer checks and
  `--warnings-as-errors=*`.
- `safety-hardening`: checks the `biv` binary for PIE, RELRO, BIND_NOW,
  stack-protector, fortify, and stack-clash evidence.
- `safety-fuzz-smoke`: runs `fuzz_manifest_json` and `fuzz_tar_member` with fixed
  `-runs=100000 -seed=1` from scratch-copied corpora and writes fuzz artifacts to
  scratch via `-artifact_prefix=`.

A disabled check is a top-level review item, never a local waiver.

Pending shell rows:

- TSan: pending until threaded code exists.
- CB4-1 git/SQLite/host-store fuzz: pending future-step surface.
- git restore, SQLite/Codex, and host-store gates remain pending shells for later
  roadmap steps.
