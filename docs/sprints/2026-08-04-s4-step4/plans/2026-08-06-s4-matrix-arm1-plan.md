# s4-matrix Arm-1 Implementation Plan (rev1)

> **rev1** folds PLAN-REVIEW-IMPLEMENTER-REV0-20260806-002313 (must-revise at `5b3c603`): R1 — namespace admission/accounting moved INTO the T5 act head, and Wave C reordered CONSUMER-FIRST (T6 = open side, T7 = pack side; ledger task keys corrected to match); R2 — the ledger/ROADMAP/report/INDEX writes added to the locked file universe with bounded semantics; R3 — the NINE D5 kinds enumerated with a closed-count test (rev0's "eight" was a count error); R4 — `run_argv` gains a spawn-time stderr topology (probe merges at spawn, git separates; stderr byte-exact generically); R5 — `eligibility` optional in the frozen type, `--` delimiter mechanical via typed operands; R6 — stacked-branch PR topology locked with restack and stop rules.

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking. The executor is `s4-matrix.implementer` under the s4 protocol — implementation starts ONLY on the pair Planner's delegated dispatch token, per task-wave gating below.

**Goal:** Land Arm 1 of the git matrix — single-clean-repo pack/restore end-to-end with the golden harness — exactly as designed in rev4.

**Locked design:** `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md` (rev4, blob SHA-256 `802b8499a727df6ceb465f3f05d0ba1092cec2bb17797d6c49f1eeda1af878c8` at `main@934fca3`).
Governing pins: addendum G at pdc `12a1c826206f24ab334cbee8ac29a1c7458560d3` (SHA-256 `ef96d2d0…e4c42a1`); addendum F consumed at ITS landing-signal pin when it arrives.
Design clauses cited as D1…D10 below; sealed-doc clauses as in the design.
The behavior authority is the design + sealed docs; this plan sequences and locks scope — it restates contracts only where a task boundary needs the exact signature.

**Architecture:** one generic process runner under `core/support`, a git wrapper and five engine units under `core/repo`, one fenced schema act in `core/manifest` + report surfaces, integration strictly inside the landed pack/open pipelines and staging boundary, golden harness on the existing scenario/compare/tolerance substrate.

**Tech stack:** C++23 (existing tree conventions), Catch2-style tests in `tests/`, Python harness in `harness/`, git ≥ 2.x on PATH resolved once per run.

## Global constraints (every task; from the charter, reconcile, and design)

- CEREMONY_TIER production-risk; EVIDENCE_TARGET E2 per task (tests), E2 harness rows at closure; the release hold is ABSOLUTE — no merge authority exists in this plan.
- **Wave gating:** Wave A tasks are dispatchable under the delegated authority; **Wave B/C/D tasks are F-FENCED — NOT dispatchable until addendum F's landing signal arrives across the bridge** (PROCEED-TO-PLAN carve-out; an F-fenced task in a SCOPE_DIFF is an OUT row until then).
- Landing discipline: new-file tasks (Wave A) change no landed behavior — both Step-3 fences STAY LIVE until Wave B/C flips them with their ledger rows; no state on `main` where pack captures repos but the manifest refuses them.
- The three shared clusters (`src/cli/main.cpp`; error-enum/exit-map/envelope cluster; frozen envelope oracle) are matrix-owned THIS window; the floor's additive `value_uint` writer addition is rebased over, never touched.
- Locked-schema changes recapture `harness/selftest/test_envelope.py`'s blob lock literal-for-literal in the SAME reviewed head (ruling `200505`).
- DR-3 flips follow the FROZEN ledger (`docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md`) — decided, never deleted; the ledger's task keys bind.
- **Branch/PR topology (R6, locked): STACKED task branches.** `s4-matrix/arm1-t1` bases on `main`; every later task branch bases on its PREDECESSOR task branch (t2←t1, t3←t1 [independent, may base main], t4←t2, t5←t4, t6←t5, t7←t6, t8←t7). Each task ends in a PR targeting its base branch; when the operator merges a predecessor, dependents RESTACK (rebase onto the new base, retarget the PR to `main` when the whole chain below is merged). Rebase-before-land for shared files (reconcile rule). STOP RULE: a task whose base branch is unreachable, conflicted beyond mechanical rebase, or not yet pushed STOPS and relays — never re-implements predecessor work. Merge is the operator's at every level; no wait-for-merge is required to CONTINUE the stack.
- **Locked file universe additions (R2):** every task that lands rows also updates `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` — STATUS-ONLY transitions (`FROZEN → DONE` in its own task-keyed rows; any other ledger edit is out of scope); every task ends with a file-first implementation report under `.relays/s4/s4-matrix-arm1-impl/` (exact new file) plus ONE append-at-EOF row in `.relays/s4/INDEX.md` — no other `.relays/` write; T8 may update `docs/sprints/2026-08-04-s4-step4/ROADMAP.md` matrix rows only.
- Commit style: repo conventions, explicit paths, no co-author lines.
- Verdict lines bare (R-3.40 item 7); describe-never-reproduce for instrument text; no host probing; no `.github/` edits; product DNA (no host-store surface, never launch agents).

## File structure (who owns what)

```
src/core/support/subprocess.{hpp,cpp}   NEW  generic argv runner (T1)
src/core/support/probe.{hpp,cpp}        MOD  thin adapter over runner; law-comment re-scope (T1)
src/core/repo/types.hpp                 NEW  RepoEntry + eligibility/local-ref structs mirroring §2.3+G (T2)
src/core/repo/git.{hpp,cpp}             NEW  env-pinned git wrapper (T2)
src/core/repo/discover.{hpp,cpp}        NEW  boundary discovery consumed by scan (T4)
src/core/repo/classify.{hpp,cpp}        NEW  ordered D2.2 gate + promisor policy bit (T4)
src/core/repo/eligibility.{hpp,cpp}     NEW  COND-5/5b gate + proofs (T4)
src/core/repo/capture.{hpp,cpp}         NEW  bundles + non-carried-refs note writer + clean-case oracle (T4)
src/core/repo/restore.{hpp,cpp}         NEW  per-entry dispatch core (T6 consumes; unit core in T4)
src/core/manifest/manifest.{hpp,cpp}    MOD  the schema act (T5, F-FENCED)
src/core/report/envelope.cpp            MOD  repo rows + exit map (T5)
src/core/support/error.{hpp,cpp}        MOD  D5 kinds (T5)
schemas/biv-exit-map.v1.json            MOD  (T5)
schemas/biv-json-envelope.v1.schema.json MOD (T5)
src/core/scan/scan.{hpp,cpp}            MOD  fence-1 flip → discovery (T7)
src/core/pack/pack.cpp                  MOD  capture integration (T7)
src/core/open/open.{hpp,cpp}            MOD  namespace admission/accounting (T5); repo phase, containment inventory, partial lifecycle, representability (T6)
src/cli/main.cpp                        MOD  only if report plumbing requires (T6; matrix-owned window)
harness/bivharness/fixtures.py          MOD  git-repo/git-bare builders (T3)
harness/bivharness/compare.py           MOD  repo-aware walk + semantic oracle (T3)
harness/tolerance/tolerance-v1.json     MOD  git rows reachable (T3)
harness/bivharness/scenario.py          MOD  repo ops + assertions (T3)
harness/bivharness/manifest.py          MOD  §2.3+G validation (T5)
harness/scenarios/d-git-restore.json    PROMOTE from shells/ (T8)
tests/test_subprocess.cpp NEW (T1) · tests/test_repo_git.cpp NEW (T2) · tests/test_repo_engine.cpp NEW (T4)
tests/test_manifest.cpp MOD (T5) · tests/test_envelope.cpp MOD (T5/T6) · tests/test_scan.cpp MOD (T7)
tests/test_pack.cpp MOD (T7) · tests/test_open.cpp MOD (T5/T6)
docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md  MOD status-only (T5/T6/T7/T8)
docs/sprints/2026-08-04-s4-step4/ROADMAP.md                     MOD matrix rows only (T8)
.relays/s4/s4-matrix-arm1-impl/IMPL-IMPLEMENTER-<stamp>.md      NEW one per task (T1-T8)
.relays/s4/INDEX.md                                             MOD append-at-EOF, one row per report
```

---

## WAVE A — dispatchable now (no landed behavior changes; fences stay live)

### Task T1: generic argv runner extraction

**Files:** Create `src/core/support/subprocess.{hpp,cpp}`, `tests/test_subprocess.cpp`; Modify `src/core/support/probe.{hpp,cpp}`, `CMakeLists.txt` (add sources/tests, explicit paths).

**Interfaces (Produces — T2 consumes verbatim):**
```cpp
namespace biv::support {
enum class StderrMode { separate, merge_into_stdout };  // R4: topology fixed AT SPAWN (dup2), never post-hoc
struct SpawnRequest {
  std::filesystem::path executable;          // fully resolved; runner never PATH-searches
  std::vector<std::string> argv;             // argv[0..n]; runner adds nothing
  std::vector<std::string> env;              // FULL environment ("K=V"); no parent passthrough
  StderrMode stderr_mode{StderrMode::separate};
  std::optional<std::filesystem::path> stdout_file; // stream-to-file sink; else bounded memory
  size_t stdout_cap;                          // bytes, memory sink only
  size_t stderr_cap;                          // separate-mode only; byte-exact capture
  ProbeBudgets budgets;                       // reused shape; per-call values
};
struct SpawnResult {
  int exit_code;                              // data, not verdict (-1 = not exited)
  bool timed_out; bool spawn_failed; bool io_failed;
  std::vector<std::byte> stdout_bytes;        // raw bytes — NO sanitization (patches/porcelain)
  std::vector<std::byte> stderr_bytes;        // raw bytes too (R4); consumers sanitize for display
};
expected<SpawnResult> run_argv(const SpawnRequest&, const ProbeClock& = production_probe_clock(),
                               const ProbeWaiter& = production_probe_waiter());
}
```

- [ ] **T1.1** Write failing tests in `tests/test_subprocess.cpp` (the runner does not exist): `run_argv echoes argv and env` (spawn `/bin/sh -c 'echo "$MARK"'` with `env={"MARK=x1"}`, expect stdout `x1\n`, exit 0); `separate topology keeps streams apart` (`sh -c 'echo out; echo err 1>&2'` with `StderrMode::separate` → stdout_bytes `out\n`, stderr_bytes contains `err`); `merge topology interleaves at source` (`sh -c 'echo a; echo b 1>&2; echo c'` with `merge_into_stdout` → stdout_bytes `a\nb\nc\n` in write order, stderr_bytes empty — the spawn-time dup2 property post-hoc concatenation cannot fake); `exit code is data` (`sh -c 'exit 7'` → exit_code 7, no error); `timeout sweeps the group` (a `sleep 30` child with 100ms budget → timed_out, reaped); `stdout streams to file`; `raw bytes survive on BOTH streams` (`printf '\xff\x00'` to stdout and to stderr → exact bytes in each).
- [ ] **T1.2** Run: `ctest -R subprocess` — expect FAIL (no such target/symbols).
- [ ] **T1.3** Implement `subprocess.{hpp,cpp}` by EXTRACTING `probe.cpp:669-880`'s machinery (posix_spawn, Fd hygiene, own-process-group, poll-slice loop, TERM→grace→KILL sweep, post-kill reap) — generalized exactly per D1.1: caller argv/env, split pipes, raw-byte + to-file sinks, per-call budgets, exit-as-data.
- [ ] **T1.4** Run: `ctest -R subprocess` — expect PASS.
- [ ] **T1.5** Refactor `run_version_probe` into a thin adapter over `run_argv` using `StderrMode::merge_into_stdout` (the SAME spawn-time dup2 topology the probe has today — source interleaving preserved; UTF-8 sanitize at the adapter; same ProbeEvidence semantics). Re-scope the `probe.hpp:73-76` law comment per D1.1: agent-exec prohibition absolute (operator ruling 062318 cited), git exec governed by the sealed Step-4 contracts — reworded, on the record, never deleted.
- [ ] **T1.6** Run: `ctest -R probe` — expect PASS with ZERO probe test edits (the acceptance bar: probe contract unchanged).
- [ ] **T1.7** Commit `s4-matrix/arm1-runner`: `feat(support): extract generic argv runner; probe becomes adapter`.

**Acceptance:** one process-safety implementation (grep: no second posix_spawn site outside subprocess.cpp); probe tests untouched and green; law comment re-scoped with both citations.

### Task T2: repo types + git wrapper

**Files:** Create `src/core/repo/types.hpp`, `src/core/repo/git.{hpp,cpp}`, `tests/test_repo_git.cpp`; Modify `CMakeLists.txt`.

**Interfaces (Produces):**
```cpp
namespace biv::repo {
// types.hpp — mirrors sealed §2.3 + addendum G at the pin; manifest.cpp maps these in T5.
enum class RepoKind { repo, nested, submodule };
enum class HeadState { branch, detached, unborn };
enum class EligibilityResult { proven, unknown_tip, no_remote, sha_unpushed, remote_unreachable, offline_declared, unborn_head };
enum class RefAvailability { remote_proven, bundle_carried, repo_bundle_carried };
struct Proof { std::string remote, url, ref, tip_sha; };
struct LocalRef { std::string ref, sha; RefAvailability availability; std::optional<Proof> proof; };
struct NonCarriedRefsNote { std::vector<std::string> refs_p1; std::optional<uint64_t> omitted_count; };
struct Eligibility { std::string method; EligibilityResult result; std::string checked_at; std::optional<Proof> proof; };
struct RepoEntry { /* id, relpath, kind, parent_id, remote, remotes, sha: std::optional<std::string>, branch,
  head_state, dirty(false at Arm 1), capture_mode,
  eligibility: std::optional<Eligibility>,   // R5: OPTIONAL — the zero-ref unborn entry carries NONE (pinned G invariant)
  local_refs, local_refs_bundle?, bundle?, shallow?{sha,boundary,remote_urls}, sparse(null), notes incl. NonCarriedRefsNote */ };

// git.hpp — policy wrapper over support::run_argv (D1.1).
class Git {
 public:
  static expected<Git> resolve(const support::Getenv&);   // one binary per run, recorded
  struct Opts { std::optional<std::filesystem::path> cwd; bool no_lazy_fetch{false};
                support::StderrMode stderr_mode{support::StderrMode::separate};
                std::optional<std::filesystem::path> stdout_file; std::chrono::milliseconds budget; };
  // R5: delimiter ownership is MECHANICAL — `args` are flags/subcommand only; every pathish or
  // URL-ish value goes in `operands`, and the wrapper itself emits `--` before them whenever
  // operands is non-empty. There is no overload that takes operands positionally in args.
  expected<support::SpawnResult> run(std::span<const std::string> args,
                                     std::span<const std::string> operands, const Opts&) const;
};
}
```
Env pinned inside `Git::run` per D1.1: `GIT_TERMINAL_PROMPT=0`, `LC_ALL=C`, `GIT_CONFIG_NOSYSTEM=1`, isolated `GIT_CONFIG_GLOBAL`, `GIT_NO_LAZY_FETCH=1` iff `no_lazy_fetch`; cwd via `-C`.

- [ ] **T2.1** Failing tests (`tests/test_repo_git.cpp`, fixture repos built by test helpers running real git): `resolve records one binary`; `env is pinned` (a `git var GIT_COMMITTER_IDENT`-style read under a hostile fake HOME config proves isolation — the hostile config's values do NOT appear); `exit-as-data` (`merge-base --is-ancestor` false → exit 1, not error); `no_lazy_fetch sets the env` and `operands ride behind --` (both via the `BIV_REPO_TESTING` unit seam mirroring `probe_testing`'s pattern: the built `SpawnRequest` carries `GIT_NO_LAZY_FETCH=1`, and argv is `args… -- operands…` exactly when operands is non-empty — incl. an operand named `-rf` proving the delimiter defangs it); `eligibility is optional` (a `RepoEntry` with `eligibility == std::nullopt` constructs and round-trips through the T4 classify shapes); `stdout to file` (a `cat-file --batch`-scale output streams).
- [ ] **T2.2** Run → FAIL; **T2.3** implement; **T2.4** run → PASS.
- [ ] **T2.5** Commit: `feat(repo): repo types + env-pinned git wrapper`.

**Acceptance:** every git invocation in later tasks goes through `Git::run` (greppable: no `run_argv` call in `src/core/repo/` outside git.cpp); types compile standalone (no manifest include).

### Task T3: golden-harness day one (harness only; no product code)

**Files:** Modify `harness/bivharness/fixtures.py`, `compare.py`, `scenario.py`, `harness/tolerance/tolerance-v1.json`; harness selftests (`harness/selftest/test_fixtures.py`, `test_compare.py`, `test_scenario.py`).

**Interfaces (Produces — T8 consumes):** fixture entry types `{"type": "git-repo", "path", "commits": [{"files": {...}, "message"}], "branches": {name: <commit-index>}, "tags": {...}, "remote": "<git-bare fixture id>", "push": [...]}` and `{"type": "git-bare", "id"}`; scenario expectation block `"repo_state": {"<relpath>": {"head_sha"|"head_unborn", "branch", "porcelain_clean": true, "refs": {...}}}`; tolerance git rows flipped `reachable: true` with policies `head-and-refs` (git-object-id), `semantic-only` (git-index), `recorded-remote` (git-remote-config), consumed by `compare.py` (`.git/**` excluded from the byte walk; the semantic oracle asserts instead).

- [ ] **T3.1** Failing selftests: builder creates a deterministic repo (two runs → identical HEAD sha) under the pinned env (isolated HOME/`GIT_CONFIG_GLOBAL`, `GIT_CONFIG_NOSYSTEM=1`, fixed author/committer identity + `GIT_AUTHOR_DATE`/`GIT_COMMITTER_DATE`, `commit.gpgsign=false`); compare excludes `.git/**` from byte findings; semantic oracle flags a HEAD mismatch and a missing ref; tolerance validator rejects a policy not in `ALLOWED_POLICIES` (extended in lockstep, ledger L-G2/L-G3).
- [ ] **T3.2** Run: `python -m pytest harness/selftest -k 'fixtures or compare or scenario'` → FAIL; **T3.3** implement; **T3.4** → PASS (full selftest suite green).
- [ ] **T3.5** Commit: `feat(harness): git fixture builders, repo-aware compare, tolerance git rows`.

**Acceptance:** one tolerance surface (no second table; policies consumed = policies declared); determinism proven by the double-build selftest; zero product-tree edits.

### Task T4: repo engine units (new files; nothing calls them yet)

**Files:** Create `src/core/repo/discover.{hpp,cpp}`, `classify.{hpp,cpp}`, `eligibility.{hpp,cpp}`, `capture.{hpp,cpp}`, `restore.{hpp,cpp}`, `tests/test_repo_engine.cpp`; Modify `CMakeLists.txt`.

**Interfaces (Produces — T6/T7 consume):**
```cpp
namespace biv::repo {
struct Discovery { std::vector<RepoBoundary> repos; };            // {relpath, kind, parent_index}
expected<Discovery> discover(const std::filesystem::path& root, const ignore::Matcher&); // prune-beats-discovery, .biv skip, nested recursion per D2.1
struct Classification { RepoEntry entry; bool promisor;           // the D2.2 policy bit
                        enum class Fence { none, dirty, nested, submodule, unmerged } fence; };
expected<Classification> classify(const Git&, const std::filesystem::path& repo, const Discovery&); // the ORDERED D2.2 procedure, steps 1-7
expected<void> run_eligibility(const Git&, RepoEntry&);           // COND-5/5b + proofs; unborn-head forcing per G-R1
struct CaptureResult { std::vector<ArtifactFile> artifacts;       // {archive_path, disk_path} for bundle/local-refs.bundle
                       std::vector<std::string> advisories; };
expected<CaptureResult> capture(const Git&, RepoEntry&, const std::filesystem::path& scratch); // bundles + verify + note writer (G-R5/G-R6 writer algorithm) + clean-case oracle
expected<RepoRestoreRow> restore_entry(const Git&, const RepoEntry&, const std::filesystem::path& partial_root,
                                       const std::filesystem::path& stage_root);              // D4.2 per-entry dispatch incl. object-closure + symref
}
```

- [ ] **T4.1** Failing tests, one section per D2.2 step + capture/restore branch, each against a real fixture repo built through `Git` under the pinned env. Mandatory sections (each maps to a design/ledger row): discovery (prune-beats-discovery preserved; nested recorded; gitlink detected); ordered gate (unmerged → `UnmergedIndexUnrepresentable` facts carry paths; zero-ref unborn → payload-only entry, NO eligibility object; any-ref unborn → `unborn_head`+full [FX-G-1 a]; stash-only [b2 capture side]; dirty/nested/submodule → fence values; shallow → shallow metadata, no bundle; shallow+promisor → shallow branch under no-lazy-fetch [L-A8 capture side]); eligibility (proven ⇒ overlay with structured proof; sha-unpushed ⇒ full; unknown-tip fetch-probe path); capture (bundle --all + verify; thin local-refs bundle with clone-remote bases; note writer legs o1–o4 + o5 via injected enumeration [L-A6]; P1 at-rest encoding of a hostile ref name); restore unit (object-closure import installs NO source ref — stash absent [b2 restore side]; §A2 skip-at-sha/update-ref/HEAD correction; unborn symref branch [f]; per-entry dispatch totality incl. zero-artifact overlay against a local bare remote).
- [ ] **T4.2** Run → FAIL; **T4.3** implement unit by unit (classify → eligibility → capture → restore; discover first); **T4.4** → PASS.
- [ ] **T4.5** Commit per unit landed (5 commits): `feat(repo): <unit>`.

**Acceptance:** all D2.2/D4.2 branches unit-proven at E2; ZERO edits to scan/pack/open/manifest (fences still live — `ctest` full suite green unchanged); error KINDS used here that T5 introduces are declared in `repo/types.hpp` as engine-internal results until T5 maps them (no `error.hpp` edit in Wave A).

---

## WAVE B — F-FENCED (not dispatchable until the F landing signal; one `manifest.cpp` reopening)

### Task T5: the schema act (all four surfaces, one reviewed head)

**Files:** Modify `src/core/manifest/manifest.{hpp,cpp}`, `src/core/open/open.{hpp,cpp}` (member-namespace admission + accounting ONLY — R1: the D3.3 surface belongs to THIS head; no materialization here), `src/core/support/error.{hpp,cpp}`, `src/core/report/envelope.cpp`, `schemas/biv-exit-map.v1.json`, `schemas/biv-json-envelope.v1.schema.json`, `harness/bivharness/manifest.py`, `harness/schemas/manifest-plaindir-v1.schema.json`, `harness/selftest/test_manifest.py`, `tests/test_manifest.cpp`, `tests/test_open.cpp` (namespace/accounting tests), `tests/test_envelope.cpp`, `harness/selftest/test_envelope.py` (blob-lock recapture, same head), `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` (status-only).

**Interfaces (Produces):** `Manifest` gains `std::vector<repo::RepoEntry> repos;` `manifest::parse` implements full §2.3 + F (as landed at F's pin) + G (both license equivalences; G-R6 note schema; unknown-note-kind tolerance) — violations = `ParseError` (repo id + note index in detail/facts); `serialize` emits entries in locked field order (empty list still `[]`); `read_archive_plan` admits the `repos/` member family with full accounting (entry-named artifacts REQUIRED members ⇒ `IntegrityFailurePreApply` `missing-repo-member`; surplus ⇒ `UnmanifestedMember`; `ArchivePlan` gains the repos artifact table) and `apply_archive` accounts the family (extraction to stage only — the repo PHASE lands in T6); **`ErrKind` gains the NINE D5.1 kinds** — `RepoDirtyUnsupported`, `RepoNestedUnsupported`, `RepoSubmoduleUnsupported`, `RepoUnbornRefsUnsupported` is NOT one of them (deleted unshipped), `MemberAncestryUnsafe`, `UnmergedIndexUnrepresentable`, `RefUncapturable`, `PromisorObjectsUnavailable`, `GitInvocationFailed`, `RepoRestoreFailed` — with the D5.1 fact shapes and exit/family rows, and DROPS `RepoDiscoveredUnsupported`; `exit_for_error` + exit-map + envelope render the D5 surface; envelope repo rows per D5.2/D5.4.

- [ ] **T5.1** Failing tests first, from the ledger: L-F1 replacement suite (positive parse of every §2.3 field incl. unborn-head/shallow/note and an ABSENT-eligibility entry; malformed-item negatives; legs c/d/e/g/j; l1–l9 each an independent `ParseError`; leg m tolerance) in `tests/test_manifest.cpp`; member-namespace tests in `tests/test_open.cpp` (a `repos/x/repo.bundle` member with a matching manifest entry plans cleanly; entry-named-but-absent artifact ⇒ `missing-repo-member`; surplus `repos/` member ⇒ `UnmanifestedMember`); L-F4/L-F5 new exit-map row set + a CLOSED-COUNT test asserting the exact nine-name set (R3 — the mismatch cannot survive prose); L-F7 oracle recapture DECISION (new literal captured from the new serializer AT THIS HEAD, recorded in the test comment with base SHA per the ORACLE RULE; `harness/selftest/test_envelope.py` blob lock recaptured literal-for-literal, same head); L-F6/L-A1/L-A2 harness validator + schema + selftests; L-R1..L-R8 verified green.
- [ ] **T5.2** Run → FAIL on the new suites; **T5.3** implement the parser/serializer over `repo::types` + error/envelope/schema surfaces; **T5.4** full `ctest` + harness selftests → PASS incl. every RETAIN row.
- [ ] **T5.5** Commit (one reviewed head for the act): `feat(manifest)!: schema act — repos §2.3+F+G parser, member kinds, envelope rows`.

**Acceptance:** all four design-D3 surfaces changed together; F+G consumed at their pins; `git grep -F 'RepoDiscoveredUnsupported'` → zero hits tree-wide; ledger rows L-F1/4/5/6/7/8, L-A1/2/4, L-R* moved to DONE.

## WAVE C — integration (after T5 lands; CONSUMER FIRST per R1 — the reader/materializer lands before any producer)

### Task T6: open side — repo phase + containment + lifecycle (consumer)

**Files:** Modify `src/core/open/open.{hpp,cpp}` (the manifest-driven repo phase at first non-`repos/` member or EOF; per-entry dispatch via `repo::restore_entry`; no-follow directory inventory + `MemberAncestryUnsafe` [D4.3]; `.biv-stage` lifecycle + `stage-cleanup` failure; `detect_partial`/`clean_partial` [D8]; plan-time representability checks + `opts` bag [D8]; OpenReport rows/advisories incl. note re-render — namespace admission/accounting ALREADY landed in T5), `src/cli/main.cpp` (report plumbing only), `tests/test_open.cpp`, `tests/test_envelope.cpp` (P1 render leg L-A5), `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` (status-only).

Test images at this head are SYNTHETIC (pack cannot produce repo images yet): built in-test from `manifest::serialize` + the tar/zstd writers, with REAL bundles created via `repo::Git` fixture helpers — the same construction style the hostile legs need anyway.

- [ ] **T6.1** Failing tests: zero-artifact proven overlay materializes (from a local bare remote fixture) [L-A11]; full-from-bundle; repo phase triggers on `agents/`-first archive (empty payload) — the R4 trigger case; B3 hostile row ⇒ `MemberAncestryUnsafe` + partial reported + no out-of-root write [L-A7]; `.biv-stage` absent post-restore + cleanup-failure row [L-A9]; unborn zero-ref/any-ref restore legs (e/f incl. symref + stash-absent b2 restore side); note re-render advisory on open + leg n P1 assertions on both surfaces [L-A5]; `detect_partial` reports / `clean_partial` removes / `OpenPartialPresent` carries the summary; representability: case-collision + path-length ⇒ `PathUnrepresentable` findings, probe-pair + `no_probe` degradation.
- [ ] **T6.2** → FAIL; **T6.3** implement; **T6.4** full suite → PASS.
- [ ] **T6.5** File the T6 implementation report (`.relays/s4/s4-matrix-arm1-impl/` + INDEX row); commit: `feat(open): manifest-driven repo restore inside the staging boundary (Arm 1)`.

**Acceptance:** everything lands inside the partial-dir boundary (no second staging path — grep for a second `rename(` finalization); containment property unweakened (the hostile row is the proof); the D5 outcome vocabulary is the ONLY new report surface; ledger rows L-A5/A7/A9/A11 status → DONE.

### Task T7: pack side — discovery flip + capture wiring (producer, after the consumer exists)

**Files:** Modify `src/core/scan/scan.{hpp,cpp}` (fence-1 flip → `repo::discover` integration; `ScanResult.repos`), `src/core/pack/pack.cpp` (classify/eligibility/capture per repo; single-writer exclusion prefixes; `repos/` area assembly BEFORE payload per D4; PackReport rows + advisories; transitional fences), `tests/test_scan.cpp` (L-F2), `tests/test_pack.cpp` (L-F3 + fence rows L-A10 + shallow/promisor L-A8 + note legs L-A6), `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` (status-only).

- [ ] **T7.1** Failing tests: L-F2 replacement (boundary recorded, walk continues; prune-beats-discovery test STAYS green untouched); L-F3 replacement (clean repo packs; manifest entry + `repos/` members + checksums; area order repos-before-payload asserted on the member sequence; AND the packed image round-trips through the T6 open — the producer/consumer closure in one test); dirty/nested/submodule sources → the three D5 transitional refusals with facts; unmerged → sealed refusal; shallow and shallow+promisor rows [L-A8]; unborn zero-ref/any-ref pack legs (a/b/b2/i capture side); note emission at the uniform bundle site incl. a BORN repo with `refs/notes/x` + writer legs o1–o5 [L-A6].
- [ ] **T7.2** → FAIL; **T7.3** wire; **T7.4** full suite → PASS.
- [ ] **T7.5** File the T7 implementation report (`.relays/s4/s4-matrix-arm1-impl/` + INDEX row); commit: `feat(pack): repo discovery + clean-repo capture (Arm 1)`.

**Acceptance:** fence 1 flipped WITH its ledger rows (L-F2/F3, L-A6/A8/A10 → DONE); every image this head can emit, this head can restore (T5+T6 landed below it — the R1 guarantee is structural, and the round-trip test proves it); pack refuses nothing the design accepts and captures nothing silently.

## WAVE D — closure

### Task T8: golden rows + scenario promotion

**Files:** Promote `harness/scenarios/shells/d-git-restore.json` → `harness/scenarios/d-git-restore.json` with real steps; add the D6 day-one scenario rows (eligibility spread [L-A12], zero-artifact overlay [L-A11 golden half], shallow, shallow+promisor, unborn pair, FX-G-1 engine legs a/b/b2/f/i/k as scenario assertions [L-A3]); determinism leg (pack twice, manifests equal modulo documented-volatile fields); Modify `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` (status-only) and `docs/sprints/2026-08-04-s4-step4/ROADMAP.md` (matrix rows only).

- [ ] **T8.1** Write the rows (RED against any remaining gap); **T8.2** run the harness suite → all rows GREEN; L-R7 ten scenarios still green; **T8.3** file the T8 implementation report (`.relays/s4/s4-matrix-arm1-impl/` + INDEX row); commit: `feat(harness): Arm-1 golden rows — d-git-restore live`.

**Acceptance:** the golden harness asserts contract-§5 semantics over Arm 1 end-to-end at E2; every FROZEN ledger row is DONE or explicitly still-frozen-for-a-later-arm; ROADMAP matrix rows updated.

---

## Boundary contract (plan-level)

Writes: `.bvpk` images whose manifests carry `repos[]` per §2.3+F+G; restored workspaces with materialized repos. Reads: source trees + their git state via the wrapper. Target entity: the image format + the restored workspace. Downstream consumers: `biv open` (this plan), m-3 CLI rendering (envelope rows — additive), the golden harness. Contract: sealed §2.3 + pinned G + D5 surface. Proof: E2 per task + T8 harness rows. No-consumer action: none — every surface lands with its consumer in this plan.

## Out of scope (hard lines)

Arms 2–5 behavior (the transitional fences ARE the boundary); `--offline` and `PromisorSourceOffline`; unborn re-init option; sparse (reserved-null stays); `.github/`; host probing; floor surfaces (adapters/version-floor/receipts, `value_uint` rebased over); sealed-doc amendments; merge/release (operator's, absolute hold); the m-2 seam may-not-move list.

## Verification targets & anti-half-fix guards

Per task E2 (named suites); plan-level: full `ctest` + harness selftests + scenario suite green at every landed head; panel-at-SHA governs the eventual merge candidate (org law, outside this plan's authority).
Guards: fences flip only WITH their ledger rows (T5/T6); the schema act is one reviewed head; no engine unit may grow a second spawn/staging/tolerance surface; a task that needs an out-of-scope file STOPS and relays (SCOPE_DIFF discipline — an F-fenced file is OUT until the signal).

## Operator-judgment items

None new — all rulings consumed (option-1/G at its pin; arm (i); scope concurrence `001031`; docs-lane rules). The F landing signal is awaited from the bridge, not requested here.
