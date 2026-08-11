## REVIEW-FOLD — CB2 live-leak fold completed under the L-1/L-2 hold at B2 `e0d6c19`; independent review CLEAR; guarded draft-branch publication complete

ROLE: Implementer
PHASE: REVIEW-FOLD
AUTHORITY: fold-in-only
DISPATCH_ID: s4-floor-impl-2-cb2-live-fold-partial-hold-complete
PARENT_DISPATCH_ID: s4-floor-impl-2-cb2-live-leak-fold
RUN_ID: s4
TASK_ID: B2
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — option (a) is decided but implementation still awaits operator ratification and direct carry-down; merge, seal, and release remain separately gated; the release hold is ABSOLUTE
DESIGN_LOCK_ID: m2-addendum11-422d451b-lock-20260810
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: s4-floor-fold-plan-20260805
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-HOLD-L1-ALIAS-ARM-PENDING-R415-DESIGN-20260810-203310.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/IMPL-PLANNER-CB2-LIVE-LEAK-FOLD-DISPATCH-IMPL-TOKEN-20260810-191812.md; .relays/s4/s4-floor-impl/PLAN-PLANNER-CB2-FOLD-ONE-LEVEL-CONSISTENT-CONSTRAINT-20260810-193623.md; .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-CB2-OPTION-A-DECIDED-CORPUS-PROVENANCE-OWED-FIXTURES-BARE-HEX-20260810-212119.md; .relays/s4/s4-floor-impl/IMPL-PLANNER-B2-GUARDED-PUBLICATION-DISPATCH-IMPL-TOKEN-20260810-154400.md
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, m-2.planner
SUBJECT: DONE_WITH_CONCERNS — authorized L-3/X-2/X-3/T-1..T-4/C-1/M-1 fold complete at `e0d6c19`; L-1/L-2 implementation held and absent; pending falsifiers retained; host and bounded Ubuntu amd64 validation complete; independent review CLEAR; only draft B2 branch republished

DONE_WITH_CONCERNS / REVIEW-FOLD FILED

The operative `191812` fold has been completed only to the boundary left live by the
planner's `203310` urgent amendment. L-3, X-2, X-3, T-1..T-4, C-1, and M-1 are folded,
tested, reviewed, committed, and published under the carried-forward guarded terms.
The locally written L-1 main/every-JSONL alias harvest and L-2 union-widening
implementation were reverted before publication. No new child alias is minted, no
additional parent-transcript value is rewritten, and no held implementation byte is in
the candidate.

The L-1 and L-2 falsifiers remain compiled but hidden under `[.pending-r415]` so the
unresolved contract stays executable without turning the held design into a false
release gate. The explicit L-1 falsifier was run on both consent paths and remains RED
at the held defect: the restored content still contains the origin alias. This is the
required visible pending state, not a claim that L-1 or L-2 is closed.

The newer `212119` relay selects option (a), stop minting, but is addressed to the floor
planner with this seat only CC'd. It also says implementation remains gated on operator
ratification of the content-scope widening. I therefore record it as the expected next
direction without treating it as an implementation dispatch.

No GitHub Actions run or check was invoked, rerun, cancelled, or inspected. No PR
metadata was changed. No merge, tag, deployment, seal, or release occurred.

## Final topology and exact fold scope

- C remains byte-identical at
  `b8083be8529a97d1d3d5931a2c7b308335bbd09c`.
- B2 is one commit directly atop exact C at
  `e0d6c1994e286291cc7ab3439228edbb65f048a4`.
- The preserved subject is `feat(pack): collect torn tails and staged sidecars`.
- The product worktree is clean.
- `.github/**` is absent from the delta and remains Hard OUT.

FOLD_SCOPE:
- harness/bivharness/e3.py -> in
- src/adapters/claude_code/install.cpp -> in
- src/adapters/codex/codex.cpp -> in
- src/adapters/rewrite_common.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_adapter_claude_install.cpp -> in
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_pack.cpp -> in

FOLD_SCOPE_RESULT: all-in

The result covers exactly eight authorized paths.

The final Codex collector hash pinned in the harness is
`2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d`.
The unchanged Claude collector anchor remains
`cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851`.

## Hold compliance and measured premises

The latest implementer-directed planner measurement is carried as the governing
real-store premise:

- `.meta.json` has no `id` member, so the filename is the only reference-to-file index;
- `senderTaskId` resolves to an on-disk stem 107/107;
- `agentId` resolves 240/244;
- the four misses are the already-measured L-1 orphan session whose files genuinely do
  not exist, so they are pre-existing dangles rather than defects created by this fold.

The later `212119` correction says this host contains 578 child JSONL files split 309
bare-hex and 269 slug-hex, with bare-hex the majority. Any future standing round-trip
fixture must model that corrected majority. The earlier 1,702-stem population is not
cited here as a live-store measurement; its provenance remains owed by the planning
pair before either absolute figure is reused.

The earlier Codex X-2 measurement also stands: the real corpus contains zero rows with
`session_id` but no `id`. The implementation therefore warns when the narrowed `id`
fallback is exercised; it does not represent that warning as evidence of a live
real-store population.

The R-4.18 one-level-consistency constraint was honored exactly:

- no recursive `session_for` or grandchild collection was added;
- no `installed_thread_id` or staged-reader comparison was widened to a mapped root;
- no warning or refusal was added for the dropped three-level leaf;
- the coupled X-1/cardinality/root-mapped identity change remains wholly outside B2.

## Folded behavior and falsifiers

- L-3: an alias must be 8..255 bytes of ASCII alphanumeric, hyphen, or underscore
  before it can become a rewrite key. Rewrites are token-boundary-aware in JSON and raw
  text, using alphanumeric/hyphen/underscore identifier boundaries. Final containment
  verification intentionally remains strict substring scanning: an embedded origin ID
  refuses publication instead of being declared clean.
- M-1: later explicit child attribution replaces an earlier provisional unattributed
  alias pair within the same session.
- X-2: `SessionIdWithoutId:<path>` is emitted only for in-source-root rows that exercise
  the narrowed Codex fallback.
- X-3: a staged Codex identity mismatch emits
  `StagedSessionIdentityMismatch:<path>` and skips only the affected row rather than
  aborting the whole pack.
- T-1..T-4 and C-1: the dispatched shape, scope, warning, containment, and tripwire
  controls are retained and pass in the full suite.
- L-1/L-2: implementation is absent under the hold; their falsifiers remain hidden and
  executable. The explicit L-1 consent-YES and consent-NO runs both go RED at
  `installed.find(alias) == npos`, proving the held defect was not obscured.

The L-3 one-character fixture uses valid JSON. The canonical UUID embedded in a JSON
key, a JSON value, and raw text proves at least three strict verification hits and no
publication. The active focused L-3/M-1/raw selection passes 42 assertions across four
cases. A post-commit L-3/M-1/X-2/X-3/T-3 focused selection passes 63 assertions across
eight matched cases; T-4 and C-1 remain covered by the full suite because those literal
wildcard names select no standalone cases.

## Independent review

The independent read-only review initially caught one semantic regression: using the
new token-boundary predicate in verification would have weakened the containment
contract by allowing an embedded origin identifier to publish. Verification was
restored to strict substring scanning while rewrite remained boundary-aware, and the
JSON-key/value/raw falsifier was strengthened accordingly.

The final review rechecked hold compliance, the exact eight-path delta, the strict
verification boundary, L-3, M-1, X-2/X-3, and the current verification receipts.

Final independent verdict: CLEAR — no Critical, Important, or Minor findings. The
reviewer made no edits, commit, publication, or GitHub Actions call.

## Final host verification

At exact committed candidate `e0d6c19`:

- full product suite: 367 cases, 365 passed, two expected WSL skips, and
  10,417/10,417 assertions passed;
- `ctest --preset dev -E '^safety-hardening$' --output-on-failure`: 100% pass,
  zero failed out of 14, 548.50 seconds;
- `biv_tests`: PASS in 351.01 seconds;
- `harness-selftest`: PASS in 8.78 seconds, including a post-commit standalone rerun in
  8.70 seconds;
- `harness-e2`: PASS in 185.84 seconds;
- generated-envelope, open-no-rewrite, adapter purity, version-floor mirror, errno,
  probe-schema, and Werror gates: PASS;
- macOS ASan/UBSan, tidy/analyzer, and fuzz smoke: preset-configured skips.

## Ubuntu 24.04 linux/amd64 Docker parity

A disposable `ubuntu:24.04` container ran with `--init --platform linux/amd64` from the
exact product bytes, preserving the host worktree. All eight official workflow-pinned
LLVM package hashes matched before installation. The installed package version and
architecture were
`1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78 amd64`;
`clang-tidy-22` reported LLVM 22.1.8. Configuration used the workflow-equivalent
`-DBIVHARNESS_REQUIRE_CLANG_TIDY=ON`, and the non-root build completed with writable
`/mnt/c/tmp`.

Linux results:

- exact raw product row: 366 successes, one failure, zero expected failures, zero
  skips;
- controlled product row excluding exactly the known Docker Desktop/Rosetta spawn
  classification case: 366/366 cases and 10,139 assertions passed;
- controlled harness self-test: 967 passed, three skipped, four deselected;
- E2: PASS in 1.10 seconds;
- Werror: PASS in 1.59 seconds;
- LLVM 22 tidy: EXECUTED and PASS in 44.43 seconds;
- the workflow JUnit tidy parser: `tidy row gate: OK - executed and passed`;
- hardening: PASS in 0.14 seconds;
- ASan/UBSan and fuzz smoke: configured skips.

The sole raw product failure is the known Docker Desktop/Rosetta difference in
`version probe does not fall back to PATH when a pinned executable cannot spawn`: the
invalid executable is classified as `nonzero_exit` instead of native Linux
`spawn_error`. The four harness exclusions are the known emulated overlay-filesystem
metadata/enumeration races:

1. `test_file_reader_rejects_same_size_cross_chunk_in_place_rewrite`;
2. `test_c1_zero_session_control_reds_on_file_inserted_at_scandir_stop`;
3. `test_credential_scanner_detects_entry_added_after_directory_enumeration`;
4. `test_run_e3_session_inserted_at_scandir_stop_reds_c1_before_open`.

The generated-envelope row was dependency-not-run because the raw product row was
non-green, but its direct validation passed. The workflow's hard-coded Catch2
expectation of 223/0/0/0 is inherited and stale against the observed 366/1/0/0; no
`.github/**` edit was authorized or made.

The task-owned CB2 container, volume, and temporary LLVM downloads were removed after
evidence capture. They contained no unique source and are not recoverable. The unrelated
`bivpak-slice-a-d885530-ci` container remained running and untouched; no Docker prune or
unrelated removal occurred.

## Guarded publication and remaining gates

The candidate was amended as the single preserved B2 commit, then the carried-forward
`154400` guarded terms were applied with the exact prior remote head as the lease:

`git push --force-with-lease=s4-floor/b2-torn-tail:355aad6cb74131b0768960aabde193ed4f611428 origin e0d6c1994e286291cc7ab3439228edbb65f048a4:s4-floor/b2-torn-tail`

The lease succeeded. Postflight established:

- remote B2 and PR #23 head equal exact
  `e0d6c1994e286291cc7ab3439228edbb65f048a4`;
- PR #23 remains OPEN, DRAFT, and based on `main`;
- remote C and PR #22 remain exact
  `b8083be8529a97d1d3d5931a2c7b308335bbd09c`, OPEN, DRAFT, and based on `main`.

Only the B2 draft branch moved. No PR body/title/base/label/reviewer mutation, undraft,
Actions invocation or inspection, merge, tag, deployment, seal, or release occurred.

Requested next action: operator ratification or countermand of the content-scope
widening, followed by an explicit planner carry-down for option (a). The L-1/L-2/R-4.15
pending falsifiers and standing round-trip resolution acceptance remain available for
that next ruled fold. This report does not claim those held items are closed.

C never lands without B2 (A10.3).

The release hold is ABSOLUTE.

ACTIONS_GIT_REF: local and remote B2 `e0d6c1994e286291cc7ab3439228edbb65f048a4` atop exact C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`; guarded force-with-lease updated only `origin/s4-floor/b2-torn-tail`; this report and its append-only INDEX row are the only docs-lane writes from this filing
FINAL_GIT_STATUS_SHORT: product worktree clean; shared docs checkout retains pre-existing sibling untracked state, preserved; this filing adds only the named report and its INDEX row

CARRY LIST:
- `.relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-LIVE-FOLD-PARTIAL-HOLD-COMPLETE-PUBLISHED-20260810-212701.md` -> `s4-floor.planner`
- B2 `e0d6c19` over byte-identical C `b8083be`; exact eight-path partial fold; L-3/X-2/X-3/T-1..T-4/C-1/M-1 complete; L-1/L-2 implementation held and absent; pending falsifiers retained
- host suite green; bounded Ubuntu amd64 implementation/tidy/E2/Werror/hardening evidence green with exact Docker-emulation/overlay exceptions and stale count gate disclosed; GitHub Actions untouched
- independent review CLEAR; PR #23 OPEN/DRAFT at exact B2; PR #22 OPEN/DRAFT at exact C; no merge/seal/release
- option (a) is selected but implementation waits for operator ratification and direct carry-down; corrected fixtures must model 309 bare-hex / 269 slug-hex; disputed 1,702-stem corpus not cited as live-store measurement
- C never lands without B2 (A10.3); release hold ABSOLUTE
