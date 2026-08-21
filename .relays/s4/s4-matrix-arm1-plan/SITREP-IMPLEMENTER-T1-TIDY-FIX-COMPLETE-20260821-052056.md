## SITREP — T1 tidy repair complete in two bounded local commits; one-root S2 RED GREEN S5 chain verified on macOS and Ubuntu 24.04 amd64; parser residual corrected from real evidence

ROLE: Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-t1-tidy-fix-impl-complete
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-impl
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T1-TIDY-FIX-DISPATCH-20260821-035403.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — Planner review and every later integration or publication act remain separately gated; no merge, push, PR mutation, remote CI, publication, deployment, or release authority is carried here
BASE: candidate base `76638a00332fc9dd674f0cf952e28be4fa0507e8`; tests-only head `b61e761f530ed86e4f54b65a5b3259b5a5d03e3b`; fixed head `00c06d93146f13c0f8518b0893d2d944f0bd8231`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: COMPLETE — T1 tidy repair is local and clean at `00c06d9`; exact RED to GREEN chain retained; review requested; no integration or publication act performed

## 1. Exact commits and scope

The existing isolated worktree remains on `s4-matrix/arm1-t1`. The dispatched work is
exactly two commits after base `76638a00332fc9dd674f0cf952e28be4fa0507e8`:

```text
b61e761f530ed86e4f54b65a5b3259b5a5d03e3b  test(subprocess): characterize per-stream truncation
00c06d93146f13c0f8518b0893d2d944f0bd8231  fix(subprocess): satisfy tidy ownership checks
```

`git diff --name-status 76638a0..00c06d9` names only the two dispatched paths:

- `tests/test_subprocess.cpp`
- `src/core/support/subprocess.cpp`

S1 adds exactly the three frozen real-shell characterization cases: stdout-only cap,
stderr-only cap, and the both-streams-ample negative discriminator. The pre-existing
both-capped case is unchanged. Before S1 was committed, the production source SHA-256
was rechecked as the approved pre-edit value
`9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b`.

S4 makes only the approved source edits: the two `ByteCapture` reference members become
non-owning pointers initialized from the constructor references; the three use sites
derefence those pointers; and the 8192-byte read buffer is value-initialized. No reserve,
pointer arithmetic, cap logic, monotonic-OR behavior, `SpawnResult`, workflow, schema, or
other product expression changed. The fixed source SHA-256 is
`b30c2949121ca645e70922c3a80f641079120829828beb6f0c806b16f8165695`.

The candidate worktree is clean at `00c06d9`; both commits and the branch remain LOCAL.

## 2. Canonical one-root evidence chain

The complete accepted chain is retained at:

```text
/Users/jack/Programming/bivpak/.superpowers/sdd/t1-tidy-QTViwhrG
```

Its `RECEIPTS.sha256` has SHA-256
`b69a72ba02936fdb885e5539668baf114f7d50821c0d0434792c1e07602cdb00`.
A fresh `shasum -a 256 -c RECEIPTS.sha256` verified all 22 listed artifacts `OK`.
The same root was passed unchanged to every accepted phase and no phase re-created it.

Observed status and source-anchor receipts:

```text
S2 macOS:   SUBPROCESS_RC=0  NAMED_RC=0
             source=9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
S3 Linux:   TIDY_RC=8
             source=9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
S5 Linux:   SUBPROCESS_RC=0  TIDY_RC=0
             source=b30c2949121ca645e70922c3a80f641079120829828beb6f0c806b16f8165695
S5 macOS:   SUBPROCESS_RC=0  NAMED_RC=0
             source=b30c2949121ca645e70922c3a80f641079120829828beb6f0c806b16f8165695
```

The Linux rows ran from Git archives in disposable Ubuntu 24.04 containers with
`--platform linux/amd64`, the eight checksum-pinned Clang 22 packages, non-root
`runuser -u biv`, and `nofile_soft=1048576` equal to inherited
`nofile_hard=1048576`. The host candidate was never mounted into either container and
no unrelated Docker resource was pruned.

S3's executed analyzer row failed with exactly these findings and no fourth:

```text
136  cppcoreguidelines-avoid-const-or-ref-data-members
138  cppcoreguidelines-avoid-const-or-ref-data-members
220  cppcoreguidelines-pro-type-member-init
```

Its retained gate output is `S3 RED gate OK: row EXECUTED and FAILED with exactly the
three known findings`. S5's analyzer row executed and passed with `TIDY_RC=0`; its gate
output is `S5 GREEN gate OK: row EXECUTED and PASSED`. The Linux subprocess CTest row
also passed at the fixed head in 0.83s.

The final macOS focused subprocess row passed in 0.84s. The final named selection passed
all six registered rows with zero failures: `biv_tests` 364.35s, `errno_table_gate`
1.18s, `generated_envelope_conforms` 0.10s, `harness-selftest` 4.85s, and
`harness-e2` 231.53s, plus its envelope-reset fixture.

## 3. Real-log gate residual: observed, corrected, and retained

The first real S3 run produced exactly the required three diagnostics but exposed the
declared parser residual in two concrete forms:

1. CTest JUnit records a failed executed row as `status="fail"`, not `status="run"`.
2. Clang 22 emits `[check-id,-warnings-as-errors]`, while the synthetic-only regex
   required the closing bracket immediately after `check-id`.

Per the dispatch, these were treated as gate defects, never as product findings or a
waiver. The raw first-run log and receipts remain unchanged under
`.superpowers/sdd/t1-tidy-BnRABAzv`. The gate was narrowed to accept only executed
`run` or `fail` status while still requiring a failure/error child, and to extract the
leading check ID while tolerating the comma suffix. Corrected gate SHA-256 is
`7b41082bf62f5ce9ffabbe2db82511850387080d442377960d4016b12842c239`.
It passes the real Clang 22 log and the original positive fixture, and rejects all five
original negative controls: zero CTest exit, green row, skipped row, fourth finding,
and swapped check ID.

The first corrected Linux phase also exposed a post-success cleanup defect: the wrapper
printed `PHASE s3 OK` after writing and hashing every S3 receipt, then its EXIT trap
referenced a function-local `stage` after scope exit under `set -u`. The retained S3
evidence was not rewritten or rerun. The scratch wrapper now gives `stage` process
lifetime; final wrapper SHA-256 is
`37a0c832188ecb3893f48549801194f2cdfe1e12bd4fa01c840bd7b60576d267`,
and S5 completed with exit zero through that cleanup path.

## 4. Preserved transient macOS observation

A superseded fresh root `.superpowers/sdd/t1-tidy-ufKPP5z5` recorded S2's focused
subprocess row and four of five named product rows green, then `harness-e2` failed only
because the trivial pinned Codex stand-in timed out at its 2000ms version-probe budget
in `open-consent-yes` and `open-store-locked`. The identical pre-edit binary and inputs
had passed in the immediately preceding full run. Each failed scenario was then rerun
alone from fresh scratch and passed. No code or timeout was changed. The final canonical
root repeated the complete pre-edit macOS selection green, and the post-edit selection
also passed all six rows. The superseded failure root remains retained rather than
erased or folded into the accepted receipts.

## 5. Boundaries and requested next gate

The known Linux `harness-selftest` residual remains separately adjudicated under the
`201613` ruling. This dispatch did not rerun or label the full Linux suite green. The
separate Linux `nonzero_exit` contract remains owed on the eventual fixed head and is
not claimed by the aggregate subprocess CTest receipt. T2, T3, T4, `compare.py`, the
count-gate shape, and the F+G-fenced schema act remain held exactly as dispatched.

Please review exact local head `00c06d93146f13c0f8518b0893d2d944f0bd8231`, the
two-commit TDD split, the real-log gate correction, and the retained canonical evidence
root. No GitHub Actions, remote CI, push, force-push, PR mutation or comment, merge,
publication, deployment, tag, or release occurred. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: created local tests-only commit `b61e761f530ed86e4f54b65a5b3259b5a5d03e3b` and local production-only commit `00c06d93146f13c0f8518b0893d2d944f0bd8231`; executed local macOS and disposable Ubuntu 24.04 amd64 evidence rows; retained three evidence roots and corrected only ignored scratch gate/driver artifacts; no remote or integration act. Docs-lane delta is this relay plus one live-EOF INDEX row only; all sibling-authored shared-checkout state is preserved and unclaimed.
FINAL_GIT_STATUS_SHORT: candidate worktree clean at `00c06d9`; shared main retains pre-existing sibling-authored untracked relays and docs unchanged, with only this relay plus its authorized INDEX append added by this seat
RELAY_LINT: exact-file freshness and post-append no-freshness checks pass. INDEX lint retains only the standing historical cell-count failures at lines 132, 222, 324, 362, 384, 388, 408, and 435 plus time inversions at lines 222 and 393; the new live-EOF row at line 550 is ten-cell and monotonic and produces no new error.

CARRY LIST (D-8.5):
- exact local candidate head `00c06d93146f13c0f8518b0893d2d944f0bd8231`; two commits after `76638a0`; scope exactly `tests/test_subprocess.cpp` plus `src/core/support/subprocess.cpp`.
- canonical evidence root `.superpowers/sdd/t1-tidy-QTViwhrG`; all 22 receipt hashes reverified; S2 green, S3 exact-three RED, S5 Linux analyzer plus subprocess green, S5 macOS green.
- declared real-log parser residual fired and was corrected without touching product bytes; raw first attempt retained; cleanup-lifetime defect also corrected in ignored scratch harness and exercised by S5 exit zero.
- one transient macOS harness-e2 two-scenario probe timeout is retained and disclosed; each scenario passed alone and both canonical full macOS selections passed.
- full Linux suite not called green; Linux `nonzero_exit` still owed; T2-T4, comparator, count shape, schema act, merge, push, PR mutation, remote CI, publication, deployment, and release remain held; release hold ABSOLUTE.
