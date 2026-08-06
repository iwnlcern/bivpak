# s4-matrix DESIGN — Arm 1 integration shape (+ arm-plan skeleton), rev4

**DESIGN_DOC_ID:** `docs/sprints/2026-08-04-s4-step4/designs/2026-08-05-s4-matrix-arm1-design.md`
**Author:** `s4-matrix.planner` · **Dispatch:** `s4-matrix-design` (20260804-235022) · **Date:** 2026-08-05.
**rev1:** folds the four blockers of DESIGN-REVIEW-IMPLEMENTER-20260805-013222 (must-revise at BASE `a5fb475`): B1 manifest-driven repo phase (D4.1); B2 ordered classification with explicit unborn/shallow branches (D2.2, D4.2); B3 no-follow directory inventory preserving symlink-ancestry containment + hostile fixture (D4.3, D6); B4 exact public error/advisory/outcome membership frozen here (D5).
**rev2:** folds the four residual blockers of DESIGN-REVIEW-IMPLEMENTER-REV1-20260805-014657 (must-revise at BASE `0da935a`): R1 promisor as a per-repo POLICY that composes with every branch incl. shallow (D2.2); R2 unborn-with-refs — fail-safe rule defined, the one inexpressible `eligibility.result` cell ROUTED UP, class transitionally fenced until the ruling (D2.2, D4.2, D5); R3 plan-time member containment vs a distinct mid-apply ancestry kind, exact mapping (D4.3, D5); R4 helper-artifact lifecycle + repo-phase trigger at first non-`repos/` member or EOF (D4.1).
**rev3:** folds the R2 RULING — option 1, addendum G (`m1-addendum-G-20260805`, rev1; routed via `DESIGN-ORCHESTRATOR-PLANNER-RULING-IN-OPTION1-ADDENDUM-G-20260805-044328`): `eligibility.result: unborn-head` with the bidirectional license, the class un-fenced and treated as normal per §A6 (D2.2 step 4, D4.2, D5, D6, criterion 5); `RepoUnbornRefsUnsupported` DELETED unshipped (option 2's fence not taken); restore discriminator corrected to `head_state: unborn` AND recorded bundle, never `local_refs[]` cardinality (G-R2/B1); schema act consumes addenda F AND G together in the one reopening after both reviews close (D3, D10).
**rev4 — THE PINNED-G FOLD (releases the second hold):** binds addendum G at its VP-APPROVED immutable pin — **pdc commit `12a1c826206f24ab334cbee8ac29a1c7458560d3`, doc SHA-256 `ef96d2d03da3495fc318b8ee17c7ca97d87497815873904938891bb85e4c42a1` (G rev18)** — hash re-verified at this seat against the blob before folding; a changed pin re-issues from master via the orchestrator, this design never follows the live file.
Folds N1–N4 of DESIGN-REVIEW-IMPLEMENTER-REV3-20260805-052110 as the floor plus the pinned-bytes deltas: any-ref/zero-ref class semantics (D2.2); the complete parser-observable license + the G-R6 `non-carried-refs` closed hostile note schema in the schema act (D3); object-closure import with the stash-absent/advisory-survives postcondition (D4.2); the G-R5 taxonomy note at the uniform `bundle --all` site incl. BORN repos (D2.3, D5); the fifteen-leg FX-G-1 ownership map (D6); the test_envelope blob-lock recapture discipline inherited by the schema act (D3, RECONCILE ruling `200505`).
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

Arm 1 handles exactly the single-clean-repo classes; everything beyond gets a TYPED, transitional refusal — the same honest fencing Step 3 used, flipped by the later arm that owns it.

**Promisor is a POLICY, not a routing step (R1 fold).**
Before the ordered procedure runs, per-repo classification detects the promisor property (`config remote.<name>.promisor` true or any `partialclonefilter`) and, when set: EVERY subsequent git invocation for that repo runs under `GIT_NO_LAZY_FETCH=1` (sealed §A5's "explicit, not ambient" lazy-fetch policy — HELD unchanged by addendum-D rev3), and a genuinely-missing-object failure in ANY of those invocations maps to `PromisorObjectsUnavailable`.
A property cannot be shadowed by routing, so no branch — shallow included — can bypass §A5.

Classification is then an ORDERED decision procedure (B2 fold); the first matching step decides, so no repo can route two ways:

1. **Repo-set shape (from discovery, before per-repo classification):** nested repo present ⇒ `RepoNestedUnsupported` (transitional, Arm 3); submodule present (gitlink in the parent index, `ls-files -s`) ⇒ `RepoSubmoduleUnsupported` (transitional, Arm 4).
2. **Unmerged index** (`ls-files -u` non-empty) ⇒ `UnmergedIndexUnrepresentable` — PERMANENT sealed refusal (addendum-B B1), fail-stop before any archive write, facts carry the conflicted paths (paths, never content).
3. **Unborn HEAD, ZERO-REF** (`rev-parse HEAD` fails AND `for-each-ref` empty — pinned G's rev3 narrowing of §A6's "zero-commit" phrase: a refless repo has no commits, so every repo the sealed sentence governed still lands here) ⇒ payload-only capture: worktree files ride as ordinary payload (their untracked-ness IS the payload — this step deliberately precedes the dirt gate), `head_state: unborn`, `sha: null`, no bundle, empty-or-absent `local_refs[]`, and NO `eligibility` object recorded at all — `unborn-head` is exclusively step 4's cell, and `payload-only-unborn`/`EmptyRepoPayloadOnly` are exclusively this one (FX-G-1 legs e/j).
4. **Unborn HEAD, ANY-REF** (`for-each-ref` non-empty — ANY ref, ANY object type; pinned G's honestly-named REF test, rev3's arm after the commit-peel arm was withdrawn for colliding with sealed C3's tag arm) ⇒ treated as NORMAL under the pinned addendum-G ruling (G-R1): `eligibility.result: unborn-head` (not-applicable semantics — names why `ls-remote-ancestry` could not start; never asserts the check ran; `proof` null, `method` stays `ls-remote-ancestry`, `checked_at` recorded), which FORCES `capture_mode: full` in the honest-unknown family.
   The license is BIDIRECTIONAL and PARSER-OBSERVABLE (G-R1/R3, fields only): for `head_state: unborn`, `bundle` recorded ⟺ `unborn-head` (+ `sha: null` + `capture_mode: full`); no bundle ⟺ NO `eligibility` object AND `local_refs[]` absent-or-empty; the validator REJECTS every other combination, never warns (FX-G-1 negative legs c/d/g/e/j — all five directions).
   `bundle create --all` is valid from REF presence, not commit presence (probe-verified for commit refs, blob tags, and annotated tags alike — a non-commit-tag-only repo enters this class and round-trips, leg i); COND-5b/C3 per-ref availability is UNCHANGED (per-ref proofs run from their own non-null shas); restore per the D4.2 unborn-with-refs branch.
5. **Dirt** (porcelain v2 shows any staged/unstaged/untracked entry; ignored files are NOT dirt — they are penumbra payload) ⇒ `RepoDirtyUnsupported` (transitional, Arm 2).
6. **Shallow** (`rev-parse --is-shallow-repository` true) ⇒ shallow-aware capture per sealed addendum-D §D4: worktree content as payload + manifest metadata `{shallow: true, sha, shallow_boundary, remote_urls[]}`, NO bundle stored (a shallow bundle is dead-or-corrupt weight, the §A4-inverted trap), never refused.
   **Combined shallow+promisor (R1 fold):** takes THIS branch under the promisor policy — worktree capture is pure file I/O with zero git object access, classification reads ran under `GIT_NO_LAZY_FETCH=1`, the manifest entry carries a `promisor-source` note (the `sparse-source` note precedent), and the D6 fixture proves zero fetch subprocess activity; §A5 is composed, not bypassed.
7. **Eligibility** (everything that reaches here: clean single repo, incl. detached HEAD / no-remote / unknown-tip / sha-unpushed / remote-unreachable) ⇒ overlay iff `proven`, else full — fail-safe by construction; full-capture bundle creation on a promisor-property repo enforces sealed §A5 verbatim (`GIT_NO_LAZY_FETCH=1`, typed refusal on missing objects, never a silent balloon).

Steps 3/4/6 are capture BRANCHES with their own apply behavior and report rows — specified in D4.2, membership frozen in D5, day-one fixtures in D6.

Cross-cutting rules bound in from day one: promisor HELD (§A5 sealed, addendum-D made no change); shallow never-refuse (addendum-D §D4); `.bivignore`-only exclusion (addendum E — no credential floor, no default key exclusions); single-writer; no host-store surface.
`--offline` pack mode is NOT an Arm-1 deliverable (its refusal semantics interlock with Arm-4/offline work), but `eligibility.result` plumbs the full sealed enum including `offline-declared` so the mode lands later without a schema reopen.

### D2.3 Eligibility, capture, and the clean-case self-check

Eligibility is the sealed audit-locked method verbatim (pack-engine §2): union of `ls-remote --heads --tags` over ALL configured remotes, `cat-file -e` + `merge-base --is-ancestor` per tip, structured `proof {remote, url, ref, tip_sha}` from the same advertisement snapshot, only `proven` ⇒ overlay, everything else full — fail-safe by construction.
`local_refs[]` emitted in every mode (rev3 F2); thin bundles based ONLY on clone-remote tips (§A1.2); a ref reaching the image by neither route is pack-time `RefUncapturable` (§A1.3).
The unknown-tip single-ref fetch probe (pack-engine §2, default ON) rides Arm 1.
Bundles: `bundle create --all` for full; thin `local-refs.bundle` for overlay-with-unpushed; `bundle verify` before sealing — necessary-not-sufficient, with the shallow branch already diverted to addendum-D §D4 capture (so §A4's dead-bundle trap cannot arise).
Clean-case capture check: the full §3.3 self-test worktree is Arm-2 machinery (it exists to catch dirty-capture loss); Arm 1's cheaper equivalent is bundle-verify plus the classification-snapshot oracle over the penumbra payload set (expected-vs-captured, both directions), recorded as capture loss/contamination degrade notes per §3.2.

**The `non-carried-refs` note (pinned G-R5/G-R6, at the uniform `bundle --all` site — BORN repos included, not an unborn-only rule):** wherever full-capture bundling runs, pack partitions the repo's refs per the G-R5 taxonomy (heads/tags carried; `refs/stash` C3-non-carried; `refs/remotes` accepted-difference; EVERY other namespace non-carried) and, when the catch-all set is non-empty, writes the structured manifest note `{kind: "non-carried-refs", refs: […]}` per the pinned WRITER algorithm (eligible set = decoded-length ≤1024 sorted strictly ascending, first ≤4096; `omitted_count` by the three-case canonical rule: omit at zero, exact below the sentinel, floor sentinel `2^53−1` = "at least"), refs stored in P1 form at rest, plus the default-visible PackReport advisory.
Non-carried is defined by the TABLE, never by implication from `local_refs[]` absence; the pack-time stash advisory (C3) is unchanged beside it.
Arm (i) — the advisory posture — is CONSUMED as decided by the pinned addendum (its rev5 R11); this design re-decides nothing, and full carry is `R-X.2` at a future gate.

## D3 — The schema act: four surfaces, one act window

The reconciled ruling stands: the act scopes fence 1 (D2.1), fence 2, the member-namespace gate, and the envelope summaries + frozen oracle — matrix-owned at the Arm-1 window; floor follows after it lands.
Sequenced strictly after addenda F AND G both close review — consumed TOGETHER in the ONE fenced `manifest.cpp` reopening (G rides F's review path; the landing signal comes across the bridge; no polling).

1. **Parser (fence 2):** `require_empty_array(…, "repos")` (`manifest.cpp:597`) is replaced by a FULL sealed-§2.3 parser — all fields, closed enums exactly as sealed (+`head_state: unborn`/nullable-sha per §A6, +`eligibility.result: unborn-head` with the COMPLETE parser-observable license per pinned G-R1/R3 — both equivalences (bundle ⟺ `unborn-head`+null-sha+full; no-bundle ⟺ no-eligibility AND `local_refs[]` absent-or-empty), REJECT never warn, negative legs c/d/g/e/j — +the addendum-D §D4 shallow metadata), structured `proof` objects, per-entry `local_refs[]`.
   The parser also lands the G-R6 CLOSED hostile schema for the `notes[]` `non-carried-refs` member: multiplicity ≤1; canonical-P1-only decode (bijective; every alias/malformed form INVALID); strictly-ascending order and the 1024-byte bound over DECODED octets; check-ref-format grammar; catch-all-namespace membership only; 4096-entry cap; `omitted_count` wire range `1…2^53−1` with reader refusal (never wrap/clamp/saturate) and the empty-`refs`-requires-positive-count rule; violations are image-level typed refusals via the landed `ParseError` (repo id + note index in the detail/facts) — no new ErrKind; unknown `kind` members are TOLERATED per the §2.2 law (skip-render, verbatim `--json`).
   A hostile no-bundle/no-eligibility/non-empty-`local_refs[]` manifest is rejected BEFORE apply (leg j) — never silently ignored.
   Parse the full sealed shape ONCE, now: later arms populate more fields but never reopen the parser (the one-window rule exists precisely to avoid serial `manifest.cpp` reopenings).
   Unknown `path_flavor` VALUES follow addendum F's rules as landed; the enum surface itself stays exactly as sealed (m-2 seam, package §4).
   `sparse` stays reserved-and-null (R-4.2: parse-tolerate null, refuse non-null as unknown-shape, never implement).
2. **Model + writer:** `Manifest` gains `repos: std::vector<RepoEntry>` (`manifest.hpp`), shape mirroring §2.3; `serialize` replaces the hardcoded empty array (`manifest.cpp:498-500`) with entry serialization in locked field order; Arm 1's WRITER emits the fields Arm 1 produces (clean-repo subset: no `capture.staged_patch`/`worktree_patch` yet — absent, not empty-stringed).
3. **Member namespace:** `read_archive_plan` (`open.cpp:275-279`) admits `repos/<id>/…` as a third family — checksummed like all members, accounted against the manifest's repo entries (bundle paths named in the entry are REQUIRED members; unmanifested `repos/` members refuse exactly like unmanifested anything).
   `apply_archive`'s branch structure gains the family with the same strict accounting.
4. **Envelope + oracle:** `envelope.cpp:79-81/:107-109` render real repo summaries; the envelope schema (`biv-json-envelope.v1.schema.json`) gains the repo-row shape; the frozen open-envelope oracle (`test_envelope.cpp:446-…`) is RECAPTURED at the act's base as ONE recorded ledger decision (never regenerated ad hoc), matrix-first per the reconcile sequencing; the exit-map row-count pin and the `RepoDiscoveredUnsupported` transitional row retire/flip as ledger rows (D7).
   Ref-name text on every render surface obeys the pinned G-R6 bars: P1-encoded, no byte outside printable ASCII unescaped on the default surface, `--json` carries the same P1 strings (documented in the envelope schema for consumer decode); the note's refs are REPORT DATA — never passed to git, never a path/member name, never compared to recipient state, and never rendered as an attestation about the named refs; validate-before-render (the renderer cannot receive an invalid note and never repairs).
   Inherited discipline (RECONCILE ruling of record `200505`): the locked-schema blob lock in `harness/selftest/test_envelope.py` recaptures literal-for-literal in the SAME reviewed head that changes a locked schema — this act's window inherits that rule.

## D4 — Restore integration (into the landed staging, not beside it)

**Area ordering decision:** the archive assembly order becomes manifest, checksums, `repos/` area, `payload/` area, `agents/` area.
Rationale: `git clone` requires an empty target; penumbra payload inside a repo subtree must be laid AFTER the repo materializes, so every repo artifact must be on disk before the repo phase runs and every repo must be materialized before payload streams.
Manifest-first is the only container-fixed intra-order rule; member-area ordering is explicitly a deferred build detail (manifest-format §4), so this is a build choice, not a contract change.

### D4.1 The repository phase is MANIFEST-driven, not artifact-arrival-driven (B1 fold)

Artifacts and materialization are decoupled:
- **Accounting (at plan):** `read_archive_plan` verifies, for EVERY manifest repo entry, that each artifact path the entry names (`bundle`, `local_refs_bundle`) exists as a checksummed `repos/` member, and that no `repos/` member exists that no entry names — missing ⇒ `IntegrityFailurePreApply` (detail `missing-repo-member`), surplus ⇒ `UnmanifestedMember`.
  An entry that names NO artifacts (the fully remote-proven overlay, `bundle: null`, `local_refs_bundle` absent — legal per sealed §2.3) accounts vacuously.
- **Artifact extraction (streaming):** `repos/` members stream first (area order above) and are extracted to the helper staging path `<partial>/.biv-stage/repos/<id>/…` — Bivpak-internal, inside the partial dir (§A7's contained-bundle-path practice survives as file mechanics even though its URL-policing died with addendum-D).
- **The repo phase (trigger — R4 fold):** runs on encountering the FIRST non-`repos/` member — `payload/`, `agents/`, whichever comes first — or at end-of-archive; an archive with empty payload but agent members cannot skip or defer materialization.
  The phase iterates EVERY `manifest.repos[]` entry — never the artifact list — and dispatches on entry state per D4.2.
  Totality is by construction: the loop is over manifest entries, so the zero-artifact overlay repo, the no-bundle shallow repo, and the no-anything unborn repo each reach their branch with no arrival event needed.
- **Helper-artifact lifecycle (R4 fold):** the ONLINE helper artifacts (extracted bundles) are consumed by the repo phase and REMOVED — the whole `<partial>/.biv-stage/` tree is deleted when the phase completes, before any payload member applies and long before the fsync/rename seal, so no helper byte can ride the rename into the workspace.
  Removal failure is a mid-apply failure (`RepoRestoreFailed`, step `stage-cleanup` — D5), never a silent leak; the D6 golden rows assert the restored tree contains no `.biv-stage` path.
  This is the ONLINE rule only: addendum-D §D2's offline mode deliberately DELIVERS extracted bundles as workspace files — that is a distinct, Arm-4-window surface, and the shallow pointer row (data in the report, no artifact) is distinct from both.
- **Then payload streams** (residue + penumbra), then `agents/` replay as landed.

### D4.2 Per-entry dispatch (the apply branches, ordered by entry state — B2 fold)

- **`head_state: unborn`, no bundle, no eligibility object (ZERO-REF, per the pinned invariant):** NO git materialization; the worktree arrives as ordinary payload members; the per-repo row reports `outcome: payload-only-unborn` with the sealed §A6 `EmptyRepoPayloadOnly` note; the restored dir is a plain re-`git init`-able tree (the recorded-config re-init option of §A6 is deliberately NOT taken at Arm 1 — no config subset is captured).
- **`shallow: true`:** NO git materialization and NO bundle exists to clone (sealed addendum-D §D4); the worktree arrives as payload; the per-repo row reports `outcome: shallow-pointer` carrying `{sha, shallow_boundary, remote_urls[]}` — the honest manual re-clone pointer (addendum-D §D3 posture: extract-and-report is never described as a full repo restore).
- **`capture_mode: overlay`:** clone from the recorded remote, checkout recorded sha (detached; re-point branch iff `head_state: branch`), then local_refs recreation (below).
- **`capture_mode: full`:** clone from the EXTRACTED bundle path, re-point origin to the recorded URL, then local_refs recreation.
- **Unborn any-ref (D2.2 step 4) — authorized as designed by pinned G-R2:** the branch is selected by `head_state: unborn` AND a recorded bundle (equivalently `eligibility.result: unborn-head` — the parser-observable invariant guarantees co-occurrence), NEVER by `local_refs[]` cardinality (`refs/stash` is C3-non-carried yet enters the class with `local_refs[]` empty — leg b2 is the witness; non-carried is defined by the G-R5 TABLE, never by implication from `local_refs[]` absence), and it is evaluated BEFORE the generic full branch (leg f).
  NO sha checkout (there is none): **import the extracted bundle's OBJECT CLOSURE — installing NO source ref** (the pinned single-instruction sentence; an implementation that fetches bundle refs into their source names is NON-CONFORMANT); then recreate ONLY the manifest-carried `local_refs[]` per sealed §A2 (branches + C3 tags, any object type); re-establish the unborn HEAD via `symbolic-ref` to the recorded `branch`; per-repo verification checks the HEAD symref + all carried refs against the manifest entry — never a HEAD sha.
  Postcondition pinned by G-R2: `refs/stash` (and every non-carried source ref) is ABSENT after restore while the pack-time C3 stash advisory survives as the visible record; the G-R5 catch-all namespaces recreate NOTHING, disclosed by the note/advisory instead.
  Success row pinned by G-R2/B3: `outcome: restored`, `sha: null`, `capture_mode: full`, normal `local_refs[]` rows; never `payload-only-unborn`, never a null-sha checkout failure.
- **Open-side note advisory (pinned G-R5):** for every repo entry carrying a valid `non-carried-refs` note, open RE-RENDERS it deterministically from the manifest bytes as a default-visible per-repo OpenReport advisory row (advisory, not warning — the loss occurred at pack and was disclosed); absence of the advisory when the note exists is NON-CONFORMANT on either surface.
- **local_refs recreation (overlay and full), sealed §A2 exactly:** skip-at-sha no-op; non-checked-out refs via `update-ref` (objects fetched per §A1 `proof.url` first if absent); the checked-out branch corrected explicitly (symbolic-ref/checkout per `head_state`); per-ref failure ⇒ the D5 per-ref divergence row, never silent.
- **Per-repo verification (overlay and full):** porcelain-v2 emptiness + HEAD/branch/refs against the manifest entry; result recorded per repo id (R-m1-9).
All clone/fetch/update-ref targets are INSIDE the partial dir.

### D4.3 Containment: materialized trees enter the ancestry set by NO-FOLLOW inventory (B3 fold)

The landed created-ancestry property — a payload member's every parent must be a KNOWN DIRECTORY, symlinks never traversable (`open.cpp:443-476@8981bfd`) — is retained UNWEAKENED for post-materialization payload.
A checkout can legitimately create symlinks inside its worktree, so "inside a materialized repo root" proves nothing about a member's ancestry; instead, after each repo materializes, the engine walks the materialized subtree with `lstat` (no-follow) and registers exactly its DIRECTORIES into the created map (symlinks and files are recorded as their own kinds, exactly as tar-created entries are).
Payload validation logic is then UNCHANGED: a penumbra member under a repo root is admitted only when every ancestor segment is a registered directory.

**Phase-exact failure mapping (R3 fold):**
- What is knowable from the archive alone moves to PLAN, where sealed §2.5 wants it: member-path lexical safety AND tar-member ancestry (member order and kinds are fully known at plan) validate in `read_archive_plan`; a violation is the landed `MemberPathUnsafe` — refusal/exit 3, refused-preflight family, NOTHING touched.
  This narrows the landed kind's blur (at `8981bfd` it can fire mid-stream): after Arm 1, `MemberPathUnsafe` is preflight-only — a ledger row, not an accident.
- What is only knowable AFTER materialization — a checkout-created symlink parent under a declared member — is a NEW mid-apply kind, `MemberAncestryUnsafe` (D5): mid-fail/exit 4, failed-mid-apply family, partial residue reported (`partial_dir` fact + `detect_partial`); the mid-apply re-check also backstops the plan-time pass as defense-in-depth.
The final canonical containment assertion on the partial dir is retained.
Day-one hostile fixture (D6): a fixture repo whose tracked tree contains a symlink `dir-link -> elsewhere`, plus a declared penumbra payload member at `dir-link/x`; the member must fail as `MemberAncestryUnsafe` with no out-of-root write and the partial reported.

The staging atomicity story is UNCHANGED: everything lands in the partial dir; dir-mtime pass, fsync tree, single rename, EEXIST refusal — repo dirs ride the same boundary.
`OpenReport` gains per-repo rows `{id, relpath, sha, capture_mode, outcome, local_refs[], advisories}` (contract R-m1-7/9 anchor shape; outcome vocabulary frozen in D5), rendered by the envelope.

**Orchestration (`main.cpp`, matrix-owned this window):** repo materialization is part of `execute_open` (inside the staging boundary), so the CLI sequence plan → preview → consent → execute → session leg is UNCHANGED in shape — the session leg still runs after the workspace rename, per spec §5 order.

## D5 — Public error/advisory/outcome membership, EXACT and frozen here (B4 fold)

This section IS the Arm-1 public surface; PLAN enumerates edit/test steps but may not change membership.
Every row maps into exactly one sealed contract-§3 outcome family.

### D5.1 New `ErrKind` members (closed enum + exit-map rows + envelope schema)

| Kind | Class / exit | Transitional | Facts shape | §3 family |
|---|---|---|---|---|
| `RepoDirtyUnsupported` | refusal / 3 | yes → Arm 2 | `{repo_relpath, dirty_paths_count}` | refused-preflight |
| `RepoNestedUnsupported` | refusal / 3 | yes → Arm 3 | `{repo_relpath, parent_relpath}` | refused-preflight |
| `RepoSubmoduleUnsupported` | refusal / 3 | yes → Arm 4 | `{repo_relpath, gitlink_relpath}` | refused-preflight |
| `MemberAncestryUnsafe` | mid-fail / 4 | no | `{repo_relpath, member_path, symlink_component}` + `partial_dir` | failed-mid-apply |
| `UnmergedIndexUnrepresentable` | refusal / 3 | no (sealed B1) | `{repo_relpath, conflicted_paths[]}` — paths, never content | refused-preflight |
| `RefUncapturable` | refusal / 3 | no (sealed §A1.3) | `{repo_relpath, ref}` | refused-preflight |
| `PromisorObjectsUnavailable` | refusal / 3 | no (sealed §A5) | `{repo_relpath}` | refused-preflight |
| `GitInvocationFailed` | mid-fail / 4 | no | `{repo_relpath, op, exit_code}` — op is the wrapper's operation name, never raw argv | failed-mid-apply (restore) / pack-time error surface (pack) |
| `RepoRestoreFailed` | mid-fail / 4 | no | `{repo_relpath, step, detail}` — step ∈ {clone, ref-recreation, checkout, inventory, stage-cleanup} | failed-mid-apply |

Reused landed kinds (no new member): manifest-named artifact missing ⇒ `IntegrityFailurePreApply` detail `missing-repo-member` (D4.1); surplus `repos/` member ⇒ `UnmanifestedMember`; PLAN-TIME member lexical/ancestry violations ⇒ `MemberPathUnsafe`, which becomes preflight-ONLY after Arm 1 (refusal/3, refused-preflight, nothing touched — the phase narrowing is a D4.3 ledger row; the post-materialization case is `MemberAncestryUnsafe` above, never this kind).
RETIRED: `RepoDiscoveredUnsupported` leaves the enum, the exit map, and the row-count pin at the schema act — ledger rows, honoring its shipped `transitional: true`.
NOT declared at Arm 1: `PromisorSourceOffline` (enters with `--offline` at the Arm-4 window); Arm-2+ kinds.

### D5.2 Per-repo outcome vocabulary (`OpenReport` rows, envelope-rendered)

`outcome ∈ { restored, shallow-pointer, payload-only-unborn, failed(kind, detail) }`;
`local_refs[]` rows `{ref, outcome: recreated | failed(detail)}`;
`shallow-pointer` rows carry `{sha, shallow_boundary, remote_urls[]}`; `payload-only-unborn` rows carry the `EmptyRepoPayloadOnly` note.
`restored`/`shallow-pointer`/`payload-only-unborn` are the ok family (`ok-with-advisories` when any advisory/warning row is present); `failed` is `failed-mid-apply` with the partial dir reported as landed.
`restored` rows carry `sha: null` for the unborn any-ref class (pinned G-R2 row); `payload-only-unborn` is exclusive to the zero-ref class and the any-ref class may never be misreported as it (FX-G-1 legs e/f); a `restored` row stays honest UNDER a rendered `non-carried-refs` advisory (G-R5).
The rev2 `RepoUnbornRefsUnsupported` fence was DELETED UNSHIPPED — option 2 was not taken; no flip gate exists.

### D5.3 Warning vs advisory mapping (exit semantics per the landed envelope split)

WARNINGS (divergence class, exit 2 via `exit_for_warnings`): restore-side per-ref recreation failure (`local-ref-failed`, per sealed §2.2 "per-ref failure is a per-repo advisory, never silent" — it diverges from full restore); per-repo verification mismatch (`repo-verify-divergence`).
ADVISORIES (exit 0, the landed `prune-summary` pattern): pack-side capture-mode degrade notes (`overlay-degraded: <reason>` incl. eligibility-indeterminate, per pack-engine §5 "never blocks — degrades to full"); `shallow-capture` note; `EmptyRepoPayloadOnly` note; the `non-carried-refs` advisory on BOTH surfaces (pack renders at note-write; open re-renders from the manifest note — default-visible, advisory class, explicitly NOT a C4 typed-error constructor, per pinned G-R5); per-repo `notes[]` passthrough (`exclude-rules-local` etc. arrive with later arms).
Hostile-note validation failures are NOT advisory: they are the landed `ParseError` at manifest parse (repo id + note index), surfacing at open wrapped as `IntegrityFailurePreApply` exactly like every manifest parse refusal — no new ErrKind (pinned G-R6).
Nothing in the Arm-1 surface writes "fixed/done/verified" semantics into an exit-0 row that a divergence actually occurred — divergence is always the warning class.

### D5.4 Pack-report rows

`PackReport` gains per-repo rows `{id, relpath, kind, capture_mode, eligibility_result, notes[]}` — the envelope pack summary renders them (the D3 surface-4 flip); `notes[]` includes the structured `non-carried-refs` member where written, rendered under the D3 P1/never-attests bars.

## D6 — Golden harness, day one (one tolerance surface, never a second harness)

- **Fixture builder:** `fixtures.py` gains repo entry types executed through real git under a CONTROLLED env: isolated `HOME`/`GIT_CONFIG_GLOBAL`, `GIT_CONFIG_NOSYSTEM`, pinned author/committer identity and `GIT_AUTHOR_DATE`/`GIT_COMMITTER_DATE`, `commit.gpgsign=false` — deterministic shas, host-config-independent.
  Grammar (shape, not final syntax): `{type: "git-repo", path, commits: […], branches: {...}, remote: <name of a bare-repo fixture>}` plus `{type: "git-bare"}` for local remotes; push/advertisement state is fixture-declared so eligibility outcomes (proven/sha-unpushed/no-remote) are constructible.
- **Comparator:** `compare_trees` becomes repo-aware — `.git/**` excluded from the byte walk (contract §5 acceptable-difference), replaced by a semantic git oracle per repo: HEAD sha, current branch, porcelain-v2 emptiness, local-refs set with shas, worktree bytes/modes/symlink targets via the existing walk.
  The three git tolerance rows flip `reachable: true` with policies the comparator ACTUALLY consumes (`ALLOWED_POLICIES` extended in lockstep); the §5 class list seeds any further rows; tolerance stays the single source.
- **Scenario ops:** repo fixtures in setup; an `assert-repo-state` expectation block; `d-git-restore` promoted from xfail-pending shell to the first real row (round-trip: pack clean repo → open → semantic oracle + tree compare), gaining a determinism leg (pack twice, compare manifests modulo documented-volatile fields).
- **Day-one fixture set (B2/B3 + R1/R2/R4 rows included):** the clean round-trip row (promoted `d-git-restore`); an eligibility spread (proven-overlay, sha-unpushed-full, no-remote-full); the ZERO-ARTIFACT proven-overlay row (B1's class: `bundle: null`, no `local_refs_bundle` — materializes from remote alone); a shallow-capture row (payload + pointer, no bundle member, restored tree matches worktree); the COMBINED shallow+promisor row (shallow branch under the promisor policy — captures payload-only, subprocess trace proves ZERO fetch activity, manifest carries the `promisor-source` note); an unborn ZERO-REF row (payload-only, `EmptyRepoPayloadOnly` note — FX-G-1 leg e's control); the FULL pinned FX-G-1 matrix — FIFTEEN top-level legs, exactly `a, b, b2, c, d, e, f, g, i, j, k, l, m, n, o`, mapped by ownership: ENGINE end-to-end legs `a` (branch-ref positive), `b` (commit-tag-only), `b2` (stash-only cardinality witness incl. stash-ABSENT-after-restore), `f` (dispatch order), `i` (non-commit-tag positive, both tag forms), `k` (notes-only end-to-end: manifest note bytes + BOTH surface advisories + nothing recreated) — these ride the harness scenario rows; SCHEMA/PARSER legs `c, d, e, g, j` (the five license directions) and `l` (hostile-note closed vector, subcases l1–l9, each an independent typed refusal) and `m` (unknown-kind tolerance) — these ride the schema-act test suite; RENDER leg `n` (attacker-shaped VALID text: P1 on both default surfaces, `--json` round-trip decode) — envelope/harness; WRITER leg `o` (bounds boundary, sub-legs o1–o5; o5 is a constructed-trigger with injected enumeration per its own label) — pack-side tests; the B3 hostile row (checkout-created symlink parent + declared penumbra member beneath it ⇒ `MemberAncestryUnsafe`, no out-of-root write, partial reported); golden rows assert NO `.biv-stage` path in any restored tree (R4 cleanup); transitional-fence rows (dirty/nested/submodule each refusing with its typed kind).
- **Harness selftests** cover the new builder and comparator branches (positive and negative), per the implementer's coverage-gap finding.

## D7 — DR-3 fixture ledger (structure + home)

Home: `docs/sprints/2026-08-04-s4-step4/results/dr3-fixture-ledger.md` — created at PLAN, FROZEN before `DISPATCH IMPL` (implementer gate), maintained as arms land.
Row shape: `{id, site (path:lines at the act's base SHA), class: flip | retain | add, decision (what the new assertion is, or why retained), instrument (the exact grep/command that found or re-finds it), arm, status}`.
Seed content merges BOTH audit lists verbatim: planner F1–F7 (incl. the F7 oracle-recapture DECISION row and the F4 row-count pin), C1–C9 carriers, the three green-side seams; implementer's ten `manifest_variant` scenario retentions, the schema `maxItems`/`minItems` gap row, and the selftest positive/negative coverage additions.
The pinned FX-G-1 legs (fifteen, per the D6 ownership map) enter as ADD rows citing the pin.
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

Addenda F AND G (G rides F's review path; both reviews closed; ONE `manifest.cpp` reopening) → Arm-1 schema act (all four surfaces) → floor `repos[]`-adjacent act → separately-owned integration acts with rebases between.
The three shared clusters are matrix-owned during the Arm-1 window: `main.cpp` orchestration; the error-enum/exit-map/envelope cluster; the frozen-oracle recapture (one decision this window).
`CMakeLists.txt` and shared open/cli tests: explicit-path, rebase-before-land.

## Out of scope

Arm 2–5 design depth (skeleton only); the A7 floor and adapter legs; sealed-doc amendments of any kind; R-4.1 arm (ii); R-4.2 sparse implementation; FU-1's ruling itself; `--offline` mode landing (plumbed, not shipped); host probing; `.github/` work.

## Design acceptance criteria (what the design review checks)

1. Every semantic claim traces to a sealed clause or the reconciled audit base (spot-checkable citations throughout).
2. The runner decision leaves exactly ONE process-safety implementation and keeps the probe contract/tests intact; the probe-comment re-scope is on the record.
3. The schema act covers all FOUR reconciled surfaces and the parser is the full sealed shape (no per-arm parser reopenings).
4. Repo restore lands strictly inside the existing staging boundary (no second staging/finalization mechanism anywhere in the design).
5. The classification procedure is ORDERED and total INCLUDING combined and stateful classes: promisor composes as a policy with every branch (shallow included), the unborn classes implement addendum G AT ITS IMMUTABLE PIN (`m1-addendum-G-20260805` at pdc `12a1c826…`, SHA-256 `ef96d2d0…e4c42a1`: any-ref/zero-ref predicates, `unborn-head` cell with the complete parser-observable license, G-R2 object-closure branch and pinned row, G-R5 taxonomy + note, G-R6 hostile schema), every accepted class has a specified apply branch and report row, and every unhandled class has a typed fence (addendum-B B1 unmerged refusal permanent) — no silent-loss path and no class that routes two ways.
6. The repo phase iterates manifest entries, never artifact arrivals; it triggers at the first non-`repos/` member or EOF; artifact accounting is proven at plan; helper artifacts have a stated lifecycle ending before the seal.
7. Symlink-ancestry containment holds unweakened across materialized repo subtrees (no-follow inventory), with the hostile fixture named.
8. The D5 membership is exact and PLAN cannot change it; every row maps to one sealed §3 family with phase-consistent exit semantics (no residue-leaving failure labeled preflight).
9. Harness: one tolerance surface; comparator consumes what tolerance declares; fixture determinism is env-pinned; the D6 day-one fixture set includes the B2/B3 rows.
10. DR-3 ledger structure merges both audits' lists with no dropped row.
11. Sequencing/ownership matches the reconcile rulings verbatim.
