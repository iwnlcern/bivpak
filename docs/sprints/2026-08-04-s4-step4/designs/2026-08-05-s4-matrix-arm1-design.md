# s4-matrix DESIGN — Arm 1 integration shape (+ arm-plan skeleton), rev0

**DESIGN_DOC_ID:** `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md`
**Author:** `s4-matrix.planner` · **Dispatch:** `s4-matrix-design` (20260804-235022) · **Date:** 2026-08-05.
**Kind:** LOCAL integration design under sealed contracts.
Semantics are governed by the sealed docs (pack-engine, restore-apply contract, addenda A/B/D/E, manifest-format §2.3) and are cited, never restated as authority; nothing here amends a sealed doc.
The reconciled audit base (`RECONCILE.md` §s4-matrix) binds; audit citations are at `main@8981bfd`.
Design depth is Arm 1 only; §9 is a skeleton for Arms 2–5.

---

## D1 — Module shape and the git-runner decision

### D1.1 The runner (named decision, ruled here): extract a generic argv runner; the git wrapper builds on it

**Decision: extract `probe.cpp`'s process-safety core into a generic argv runner in `core/support`; `run_version_probe` becomes a thin adapter over it with its contract unchanged; the repo engine owns a git-specific wrapper on top.**
One process-safety implementation, two thin skins — the two-implementations failure the reconcile names is avoided at the root.

What the extraction carries (all landed and hardened in `probe.cpp:669-880`): `posix_spawn` with fd hygiene (CLOEXEC, move-above-standard-streams, nonblocking pipe), `/dev/null` stdin, own-process-group placement, the poll-slice wait loop with injected clock/waiter (testability preserved), bounded capture, TERM → grace → KILL group sweep, post-exit drain, post-kill reap with reaper transfer.

What the generic runner generalizes (each a probe hardcode the git engine cannot live with):
- argv: arbitrary vector, not `{binary, "--version"}` (`probe.cpp:715-721`);
- environment: an EXPLICIT env built by the caller, not `parent_environment()` passthrough — the git wrapper pins its env (below);
- streams: stdout and stderr SEPARATE — the probe dup2's both into one pipe, but porcelain/-z parsing needs clean stdout with diagnostics kept apart;
- capture: byte-exact sinks — the probe's UTF-8 sanitizing capture would corrupt binary output; the runner offers raw-bytes-to-memory (bounded) and stream-to-file sinks (bundles and patches are file-sized; pipe-buffer capture does not scale);
- budgets: per-call, not the 2s probe constant (a bundle create is minutes-class; the budget struct shape is reused);
- exit codes: returned as DATA, not folded to ok/nonzero — `git merge-base --is-ancestor` answers via exit 1, so nonzero is an ANSWER at some call sites.

The git wrapper (`repo::Git`, owned by the repo engine) fixes policy the runner must not know:
one resolved git binary per pack/open run (PATH resolution once, recorded for the report);
pinned env on every call — `GIT_TERMINAL_PROMPT=0`, no askpass, `LC_ALL=C`, `GIT_CONFIG_NOSYSTEM=1` plus an isolated `GIT_CONFIG_GLOBAL` for restore-side invocations (hygiene per the D1 "argv arrays, honestly labeled" retained practice — explicitly NOT a URL-safety claim, per addendum-D), and `GIT_NO_LAZY_FETCH=1` exactly where sealed §A5 requires it;
argv arrays with `--` before pathish/URL-ish operands;
cwd via `-C <dir>`;
typed error mapping into the D5 surface.

**Law flag (carried to review and the completion report, not silently edited):** `probe.hpp:73-76` carries the comment "the disclosed, pinnable, shell-free `<binary> --version` probe is the sole sanctioned exec (operator ruling 062318)".
The Step-4 sealed designs sanction git subprocess execution, and product DNA's prohibition is on launching AGENTS, which git is not.
The runner act must RE-SCOPE that comment (agent-exec prohibition stays absolute; git exec is governed by the sealed pack/restore contracts), citing both the original ruling and the Step-4 gate — a comment rewording in code, flagged here so it is a decision on the record, not an accident.

### D1.2 Module layout (new files under `src/core/repo/`, integration edits elsewhere)

- `src/core/support/subprocess.{hpp,cpp}` — the generic argv runner (extraction target; `probe.cpp` refactored onto it, probe tests unchanged).
- `src/core/repo/git.{hpp,cpp}` — the git wrapper above.
- `src/core/repo/discover.{hpp,cpp}` — phase-D boundary discovery consumed by scan (D2.1).
- `src/core/repo/classify.{hpp,cpp}` — per-repo classification: porcelain state, shallow/promisor/unborn probes, Arm-1 acceptance gate (D2.2).
- `src/core/repo/eligibility.{hpp,cpp}` — the COND-5/5b gate with structured proofs (pack-engine §2 + rev3 F1/F2 + §A1).
- `src/core/repo/capture.{hpp,cpp}` — bundle creation/verify (`--all` + thin local-refs per COND-5b/§A1.2), clean-case capture oracle (D2.3).
- `src/core/repo/restore.{hpp,cpp}` — the §2.2 chain, Arm-1 steps (D4).
- Integration edits: `scan.{hpp,cpp}`, `pack.cpp`, `manifest.{hpp,cpp}`, `open.{hpp,cpp}`, `error.{hpp,cpp}`, `envelope.cpp`, exit-map schema, envelope schema, `main.cpp`, CMake, tests, harness (D3–D7).
Each unit is independently testable against fixture repos without the container in the loop; the container round-trip is the harness's job (D6).

## D2 — Arm-1 engine semantics (pack side)

### D2.1 Discovery replaces fence 1

`scan.cpp`'s `.git` refusal (`:137-138`) is replaced by boundary recording: a child named `.git` (dir or file form) marks its parent directory a repo boundary; the walk records the boundary and continues per sealed §1.1 (recursing for nested discovery, not for payload inside repo subtrees).
Prune-beats-discovery ordering is PRESERVED exactly as landed and tested (`test_scan.cpp:83-95`): an ignored subtree is not walked, not scanned for repos — sealed §1.1's visible data-loss boundary.
`.biv` skip (`scan.cpp:140-142`) unchanged.
`ScanResult` grows the repo tree (ids, relpaths, parent edges, kind) per sealed §1.1 output; payload enumeration excludes repo subtrees except penumbra (single-writer §1.2, exclusion prefixes).

### D2.2 The Arm-1 acceptance gate and transitional fences (the Step-3 fence pattern, moved one ring in)

Arm 1 handles exactly the single-clean-repo classes; everything beyond gets a TYPED, transitional refusal — the same honest fencing Step 3 used, flipped by the later arm that owns it:

| Class at 8981bfd-style classification | Arm-1 behavior | Flip owner |
|---|---|---|
| single repo, porcelain-v2 empty (no staged/unstaged/untracked; ignored files allowed as penumbra) | capture (overlay or full per eligibility) | — |
| any staged/unstaged/untracked dirt | typed transitional refusal (D5) | Arm 2 |
| unmerged index (`ls-files -u` non-empty) | typed refusal per sealed B1 — PERMANENT v1, not transitional | — |
| nested repo discovered | typed transitional refusal | Arm 3 |
| submodule discovered (gitlink in parent index) | typed transitional refusal | Arm 4 |
| shallow source | shallow-aware capture per sealed addendum-D §D4: working-tree payload + `{shallow, sha, shallow_boundary, remote_urls[]}`; never refused | — |
| promisor source (online) | full-capture under `GIT_NO_LAZY_FETCH=1`; missing objects ⇒ typed `PromisorObjectsUnavailable` per sealed §A5 | — |
| unborn HEAD (fresh init) | payload-only capture, `head_state: unborn`, `sha: null`, no bundle, per sealed §A6 | — |
| detached HEAD / no-remote / unknown-tip / sha-unpushed / remote-unreachable | capture; eligibility result forces `full` where not proven (fail-safe) | — |

Cross-cutting rules bound in from day one: promisor HELD (§A5 sealed, addendum-D made no change); shallow never-refuse (addendum-D §D4); `.bivignore`-only exclusion (addendum E — no credential floor, no default key exclusions); single-writer; no host-store surface.
`--offline` pack mode is NOT an Arm-1 deliverable (its refusal semantics interlock with Arm-4/offline work), but `eligibility.result` plumbs the full sealed enum including `offline-declared` so the mode lands later without a schema reopen.

### D2.3 Eligibility, capture, and the clean-case self-check

Eligibility is the sealed audit-locked method verbatim (pack-engine §2): union of `ls-remote --heads --tags` over ALL configured remotes, `cat-file -e` + `merge-base --is-ancestor` per tip, structured `proof {remote, url, ref, tip_sha}` from the same advertisement snapshot, only `proven` ⇒ overlay, everything else full — fail-safe by construction.
`local_refs[]` emitted in every mode (rev3 F2); thin bundles based ONLY on clone-remote tips (§A1.2); a ref reaching the image by neither route is pack-time `RefUncapturable` (§A1.3).
The unknown-tip single-ref fetch probe (pack-engine §2, default ON) rides Arm 1.
Bundles: `bundle create --all` for full; thin `local-refs.bundle` for overlay-with-unpushed; `bundle verify` before sealing — necessary-not-sufficient, with the shallow branch already diverted to addendum-D §D4 capture (so §A4's dead-bundle trap cannot arise).
Clean-case capture check: the full §3.3 self-test worktree is Arm-2 machinery (it exists to catch dirty-capture loss); Arm 1's cheaper equivalent is bundle-verify plus the classification-snapshot oracle over the penumbra payload set (expected-vs-captured, both directions), recorded as capture loss/contamination degrade notes per §3.2.

## D3 — The schema act: four surfaces, one act window

The reconciled ruling stands: the act scopes fence 1 (D2.1), fence 2, the member-namespace gate, and the envelope summaries + frozen oracle — matrix-owned at the Arm-1 window; floor follows after it lands.
Sequenced strictly after addendum F lands (signal across the bridge; no polling).

1. **Parser (fence 2):** `require_empty_array(…, "repos")` (`manifest.cpp:597`) is replaced by a FULL sealed-§2.3 parser — all fields, closed enums exactly as sealed (+`head_state: unborn`/nullable-sha per §A6, +the D4 shallow metadata), structured `proof` objects, per-entry `local_refs[]`.
   Parse the full sealed shape ONCE, now: later arms populate more fields but never reopen the parser (the one-window rule exists precisely to avoid serial `manifest.cpp` reopenings).
   Unknown `path_flavor` VALUES follow addendum F's rules as landed; the enum surface itself stays exactly as sealed (m-2 seam, package §4).
   `sparse` stays reserved-and-null (R-4.2: parse-tolerate null, refuse non-null as unknown-shape, never implement).
2. **Model + writer:** `Manifest` gains `repos: std::vector<RepoEntry>` (`manifest.hpp`), shape mirroring §2.3; `serialize` replaces the hardcoded empty array (`manifest.cpp:498-500`) with entry serialization in locked field order; Arm 1's WRITER emits the fields Arm 1 produces (clean-repo subset: no `capture.staged_patch`/`worktree_patch` yet — absent, not empty-stringed).
3. **Member namespace:** `read_archive_plan` (`open.cpp:275-279`) admits `repos/<id>/…` as a third family — checksummed like all members, accounted against the manifest's repo entries (bundle paths named in the entry are REQUIRED members; unmanifested `repos/` members refuse exactly like unmanifested anything).
   `apply_archive`'s branch structure gains the family with the same strict accounting.
4. **Envelope + oracle:** `envelope.cpp:79-81/:107-109` render real repo summaries; the envelope schema (`biv-json-envelope.v1.schema.json`) gains the repo-row shape; the frozen open-envelope oracle (`test_envelope.cpp:446-…`) is RECAPTURED at the act's base as ONE recorded ledger decision (never regenerated ad hoc), matrix-first per the reconcile sequencing; the exit-map row-count pin and the `RepoDiscoveredUnsupported` transitional row retire/flip as ledger rows (D7).

## D4 — Restore integration (into the landed staging, not beside it)

**Area ordering decision:** the archive assembly order becomes manifest, checksums, `repos/` area, `payload/` area, `agents/` area.
Rationale: `git clone` requires an empty target; penumbra payload inside a repo subtree must be laid AFTER the repo materializes; with repos-first the single-pass streaming apply clones each repo as its bundle arrives, then payload members apply into and around the materialized trees.
Manifest-first is the only container-fixed intra-order rule; member-area ordering is explicitly a deferred build detail (manifest-format §4), so this is a build choice, not a contract change.

The Arm-1 apply chain (sealed §2.2 steps 1, 2, 6 — steps 3–5 are later arms):
1. Overlay: clone from the recorded remote, checkout recorded sha (detached; re-point branch iff `head_state: branch`); full: clone from the extracted bundle, re-point origin to the recorded URL.
   All clone/fetch targets are INSIDE the partial dir; the bundle is extracted to a Bivpak-internal path under the partial dir first (§A7's contained-bundle-path practice survives as file mechanics even though its URL-policing died with addendum-D).
2. `local_refs[]` recreation per sealed §A2 exactly: skip-at-sha no-op; non-checked-out refs via `update-ref` (objects fetched per §A1 first if absent); the checked-out branch corrected explicitly (symbolic-ref/checkout per `head_state`); per-ref failure is a per-repo advisory, never silent.
3. Per-repo verification: porcelain-v2 emptiness + HEAD/branch/refs against the manifest entry; result recorded per repo id.

**Containment adaptation:** the created-ancestry map currently admits only tar-member-created dirs; repo materialization registers its subtree root (and the clone owns everything below it), so subsequent penumbra payload members inside repo subtrees validate against "created dir OR inside a materialized repo root".
The staging atomicity story is UNCHANGED: everything lands in the partial dir; dir-mtime pass, fsync tree, single rename, EEXIST refusal — repo dirs ride the same boundary.
`OpenReport` gains per-repo rows `{id, relpath, sha, capture_mode, outcome, local_refs[], advisories}` (contract R-m1-7/9 anchor shape), rendered by the envelope.

**Orchestration (`main.cpp`, matrix-owned this window):** repo materialization is part of `execute_open` (inside the staging boundary), so the CLI sequence plan → preview → consent → execute → session leg is UNCHANGED in shape — the session leg still runs after the workspace rename, per spec §5 order.

## D5 — Error surface (design-level set; exact membership frozen at PLAN)

New typed kinds, following the landed pattern (closed `ErrKind` enum + exit-map row + class):
transitional refusals `RepoDirtyUnsupported`, `RepoNestedUnsupported`, `RepoSubmoduleUnsupported` (refusal/exit 3, `transitional: true` — each names its flip arm in the ledger);
permanent sealed refusals `UnmergedIndexUnrepresentable` (B1), `RefUncapturable` (§A1.3), `PromisorObjectsUnavailable` (§A5);
degrade-not-error advisories per pack-engine §5 (`EligibilityIndeterminate`, capture-check degrade) ride report advisories/notes, not refusals;
restore-side per-repo failures map into the contract §3 outcome families (per-repo rows), with `GitInvocationFailed(repo, op)` as the typed wrapper for unexpected git exits.
`RepoDiscoveredUnsupported` retires at the schema act — its exit-map row removal and the row-count-pin flip are ledger rows, honoring the `transitional: true` marker it shipped with.
`PromisorSourceOffline` is declared in the enum when offline mode lands (Arm 4 window), not before.

## D6 — Golden harness, day one (one tolerance surface, never a second harness)

- **Fixture builder:** `fixtures.py` gains repo entry types executed through real git under a CONTROLLED env: isolated `HOME`/`GIT_CONFIG_GLOBAL`, `GIT_CONFIG_NOSYSTEM`, pinned author/committer identity and `GIT_AUTHOR_DATE`/`GIT_COMMITTER_DATE`, `commit.gpgsign=false` — deterministic shas, host-config-independent.
  Grammar (shape, not final syntax): `{type: "git-repo", path, commits: […], branches: {...}, remote: <name of a bare-repo fixture>}` plus `{type: "git-bare"}` for local remotes; push/advertisement state is fixture-declared so eligibility outcomes (proven/sha-unpushed/no-remote) are constructible.
- **Comparator:** `compare_trees` becomes repo-aware — `.git/**` excluded from the byte walk (contract §5 acceptable-difference), replaced by a semantic git oracle per repo: HEAD sha, current branch, porcelain-v2 emptiness, local-refs set with shas, worktree bytes/modes/symlink targets via the existing walk.
  The three git tolerance rows flip `reachable: true` with policies the comparator ACTUALLY consumes (`ALLOWED_POLICIES` extended in lockstep); the §5 class list seeds any further rows; tolerance stays the single source.
- **Scenario ops:** repo fixtures in setup; an `assert-repo-state` expectation block; `d-git-restore` promoted from xfail-pending shell to the first real row (round-trip: pack clean repo → open → semantic oracle + tree compare), gaining a determinism leg (pack twice, compare manifests modulo documented-volatile fields).
- **Harness selftests** cover the new builder and comparator branches (positive and negative), per the implementer's coverage-gap finding.

## D7 — DR-3 fixture ledger (structure + home)

Home: `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` — created at PLAN, FROZEN before `DISPATCH IMPL` (implementer gate), maintained as arms land.
Row shape: `{id, site (path:lines at the act's base SHA), class: flip | retain | add, decision (what the new assertion is, or why retained), instrument (the exact grep/command that found or re-finds it), arm, status}`.
Seed content merges BOTH audit lists verbatim: planner F1–F7 (incl. the F7 oracle-recapture DECISION row and the F4 row-count pin), C1–C9 carriers, the three green-side seams; implementer's ten `manifest_variant` scenario retentions, the schema `maxItems`/`minItems` gap row, and the selftest positive/negative coverage additions.
Flips are decided-not-deleted: every flip row names the replacement oracle; every retain row asserts why the empty-repos case stays a valid fixture (payload-only images remain legal — `repos` may be empty forever).

## D8 — Partial-lifecycle and representability homes (reconcile-ruled in-scope)

- **Partial lifecycle (Arm-1 row):** `detect_partial(target) -> PartialState | None` and `clean_partial(target)` land in `open.hpp` per contract §1 — inspection reports the partial's path/member inventory summary; cleanup removes it typed; the existing `OpenPartialPresent` refusal starts CARRYING the `detect_partial` summary in its facts (contract §2.1).
  Arm-5 enriches with quarantine-aware state; the Arm-1 shape is deliberately minimal.
- **Plan-time representability (Arm-1 row):** plan gains the §2.5 lexical checks — case-collision detection within the member set (when target-fs case-insensitivity is assumed-or-probed), path-length overflow, per-path `PathUnrepresentable` findings.
  The §2.5a probe-pair (the one documented no-writes exception) and the `opts` bag with reserved `rename_map`/`no_probe` keys land with it; `rename_map`'s VALUE shape stays reserved (m-3 Track 2), unknown option keys are typed errors per contract §1.

## D9 — Arm-plan skeleton (Arms 2–5; design passes of their own, depth deliberately withheld)

- **Arm 2 — dirty-state:** classification rows (porcelain split, B-set attrs incl. `ident`, unmerged trigger), two-patch capture, forced-payload table, the §3.3 self-test worktree + oracle (blind-spot closures B2.3/B3.3), restore patch steps + cross-config hazards §2.4; flips the Arm-1 dirty fence.
  Design close BLOCKED on FU-1's operator ruling (symlink-target arm) per the dispatch.
- **Arm 3 — nested:** discovery already collects the tree (D2.1); adds leaves-first capture ordering, parents-before-children apply, per-repo outcome isolation; flips the nested fence.
- **Arm 4 — submodules + offline:** gitlink classification, per-submodule eligibility (effective config, never `.gitmodules` alone), §A3/B3 restore chain, FX-D-OFFLINE zero-git row, `--offline` mode + `PromisorSourceOffline`; flips the submodule fence.
- **Arm 5 — quarantine/closure:** quarantine mechanics + inventory, `.git/info/exclude` write + advisory + root-not-repo row (§2.6), collision-table completion, partial-lifecycle enrichment, determinism classes over the full matrix, spec-§10 green = ROADMAP exit.

## D10 — Sequencing and ownership (binding, restated from the reconcile)

Addendum F → Arm-1 schema act (all four surfaces) → floor `repos[]`-adjacent act → separately-owned integration acts with rebases between.
The three shared clusters are matrix-owned during the Arm-1 window: `main.cpp` orchestration; the error-enum/exit-map/envelope cluster; the frozen-oracle recapture (one decision this window).
`CMakeLists.txt` and shared open/cli tests: explicit-path, rebase-before-land.

## Out of scope

Arm 2–5 design depth (skeleton only); the A7 floor and adapter legs; sealed-doc amendments of any kind; R-4.1 arm (ii); R-4.2 sparse implementation; FU-1's ruling itself; `--offline` mode landing (plumbed, not shipped); host probing; `.github/` work.

## Design acceptance criteria (what the design review checks)

1. Every semantic claim traces to a sealed clause or the reconciled audit base (spot-checkable citations throughout).
2. The runner decision leaves exactly ONE process-safety implementation and keeps the probe contract/tests intact; the probe-comment re-scope is on the record.
3. The schema act covers all FOUR reconciled surfaces and the parser is the full sealed shape (no per-arm parser reopenings).
4. Repo restore lands strictly inside the existing staging boundary (no second staging/finalization mechanism anywhere in the design).
5. Transitional fences cover every class Arm 1 does not handle (no silent-loss path; B1 permanent refusal included).
6. Harness: one tolerance surface; comparator consumes what tolerance declares; fixture determinism is env-pinned.
7. DR-3 ledger structure merges both audits' lists with no dropped row.
8. Sequencing/ownership matches the reconcile rulings verbatim.
