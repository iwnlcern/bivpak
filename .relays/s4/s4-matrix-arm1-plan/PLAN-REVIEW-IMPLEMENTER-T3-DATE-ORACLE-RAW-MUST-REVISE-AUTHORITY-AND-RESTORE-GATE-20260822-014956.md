## PLAN-REVIEW — MUST REVISE: the raw oracle is technically promising and its pinned edit reproduces, but it exceeds the literal authorized mechanism and O-4 hashes the untouched file instead of the mutated file

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan
IN_REPLY_TO: PLAN-PLANNER-T3-DATE-ORACLE-RAW-STRONGER-THAN-EPOCH-20260822-012142.md
RELATED_CONTEXT: PLAN-ORCHESTRATOR-PLANNER-T3-COMPOSITION-ACCEPTED-DATE-ORACLE-AUTHORIZED-PROBE-REDS-NEED-OWN-ATTRIBUTION-20260821-235525.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — either Orchestrator concurrence authorizing the changed raw-date mechanism or a rev1 returning to the literally authorized epoch mechanism; then a corrected Implementer PLAN-REVIEW and separate bare implementation token remain required
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reviewed PLAN commit `f8fe8d56a554ebaceef14ce9bc1246edbe50ab68`, blob `2b96b2fe798d0854d5d96e79e22567469bb5b744`, SHA-256 `18cdd420c0f9a0592a7e10bcea90003f4c6b2c1e2fab41a73c030289df0a7266`; reconstructed T3 remains `a3501cc1728ca13289a8a4a96e49c9ee95e54698`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: MUST REVISE — raw-date edit and target digest reproduce, but 235525 literally authorizes the epoch oracle rather than this declared mechanism change; O-4's restore hash cannot detect residue in fixtures.py; bind O-3 to a durable actual-fixture path and correct the raw-format claim before a token

VERDICT: MUST REVISE

I re-derived the technical spine rather than rejecting the deviation merely because it is
different. At exact `a3501cc`, the current file is 7842 bytes with SHA-256
`b09f735297de49db08798bceed6cf4258d86bc16c39666496f9f6186192fd3df`, and the named anchor
occurs exactly once. Applying the PLAN's exact replacement in a throwaway copy produces
7868 bytes and SHA-256 `ca9f04e1ad06856d3c5d093ee2c6ba5d76e034d020c1cb482d65fc2868c68aaf`, matching the PLAN.
The exact node passes on macOS in that scratch copy. Independently materializing the real
fixture on macOS Git 2.50.1 yields the planned raw value, and `git cat-file commit` shows the
same epoch and stored offset. The validated census has one hit in `test_fixtures.py` and zero
in `compare.py`. The proposed mechanism is therefore plausible; the refusal is about two
load-bearing gaps, not the date arithmetic.

## MF-1 — the declared oracle deviation does not fit the literal mechanism authorized at 235525

The Orchestrator did not authorize an unspecified date-oracle class. Its relay says the
corrective is `%at` and `%ct`, requires a PLAN naming that oracle, and delegates the pair
Planner to issue the later token within that bounded mechanism. This PLAN deliberately changes
the mechanism to `%ad` and `%cd` under `--date=raw`. Staying in the same file and strengthening
coverage does not manufacture authority for a token the upstream relay did not name.

Route the offset-coverage discriminator and proposed raw mechanism back to the Orchestrator
for explicit concurrence, or file rev1 using the literal epoch mechanism. I will review either
successor on its own bytes. I will not approve this version and let the later implementation
token silently become the first record that treats “authorized epoch oracle” as “authorized
any oracle judged stronger by the pair.”

The successor must also correct one factual overstatement in the proof framing. `%ad` and `%cd`
under `--date=raw` are still Git pretty-format output governed by Git's raw date formatter;
they are a stable rendering of the stored epoch and offset, not themselves the commit object's
own bytes. `git cat-file commit` exposes the object bytes and corroborates them, but it does not
turn a separate `git show --date=raw` command into object-byte access. If the Orchestrator
accepts the stable raw rendering as satisfying requirement (ii), record that concurrence rather
than claiming the presentation layer disappeared.

## MF-2 — O-4's restore gate hashes the wrong file

O-4 mutates `harness/bivharness/fixtures.py`, then says to restore and gate on SHA-256
`ca9f04e1...` before continuing. That digest belongs to the post-edit
`harness/selftest/test_fixtures.py`, which O-4 never mutates. It will stay green even if the
date-pin mutation remains in `fixtures.py`, so it cannot enforce the stated no-residue property.

At `a3501cc`, `harness/bivharness/fixtures.py` is 9980 bytes with SHA-256
`6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303`. Rev1 must pin and gate
that exact file after each scratch mutation, while separately retaining the planned target
digest gate for `test_fixtures.py`. Both hashes are required because they prove different
things.

## MF-3 — O-3 needs an executable binding to the same materialized test fixture

O-3 correctly refuses a fresh standalone repo, but it does not say how the successful pytest
node's `tmp_path` repository is retained and identified for the subsequent exact command.
Without a bound location, an implementer can accidentally reproduce the Planner's standalone
probe while claiming the end-to-end obligation. Rev1 should prescribe a durable `--basetemp`
under the evidence root and the exact resulting `first/source/project` path, or another
equally falsifiable method that proves the queried repo is the one the test itself materialized.
Bind the same recipe on macOS and Linux.

MINOR: the SUBJECT says five proof obligations while section 5 defines O-1 through O-6. Make
the count six so the header cannot become an incomplete checklist.

No source, test, fixture, workflow, candidate ref, or Docker resource was changed by this
review. The only candidate-like edit occurred in a throwaway copy and remains outside every
tracked worktree. T3 remains clean at `a3501cc`, not final, and not panelable. T4 remains held.
No remote CI, push, PR mutation, merge, publication, schema, deployment, or release occurred.
The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only review of the exact PLAN and a3501cc bytes; one throwaway-copy application of the exact proposed block to verify the target digest and macOS node; one throwaway real-fixture materialization for raw-date and cat-file comparison; no candidate/source/ref/remote/integration act. This review and one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; full INDEX lint with inherited historical defects preserved; post-commit exact-file no-freshness verification.
FINAL_GIT_STATUS_SHORT: T3 worktree clean at a3501cc; shared main retains sibling-authored untracked history unchanged and unclaimed; only this review and its one INDEX append belong to this docs act.

CARRY LIST:
- VERDICT MUST REVISE; no implementation token may parent to this review
- technically reproduced: unique current anchor, before digest and size, exact after digest and size, macOS raw output, scratch node pass, and validated one-site census
- MF-1: raw-date is a declared mechanism change beyond the literal epoch oracle named by 235525; obtain Orchestrator concurrence or return to the authorized mechanism; describe raw output as a stable Git rendering, not object bytes
- MF-2: O-4 mutates fixtures.py but gates the untouched test_fixtures.py digest; rev1 must restore-gate fixtures.py at SHA-256 6776756f8f50ea9f9c4a46d2cb9804586da4e628fa5698041ec00356a4b81303 and separately gate the target test file
- MF-3: bind O-3 to a durable actual pytest fixture path on both hosts so a standalone probe cannot satisfy it
- correct five obligations to six; T3 remains not final or panelable, T4 held, no remote or integration act, release hold ABSOLUTE
