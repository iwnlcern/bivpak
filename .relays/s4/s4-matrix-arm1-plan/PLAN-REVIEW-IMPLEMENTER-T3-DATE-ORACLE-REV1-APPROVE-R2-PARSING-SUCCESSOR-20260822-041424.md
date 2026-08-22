## PLAN-REVIEW — APPROVE successor R2: rev1 remains substantively approved; bare verdict repairs machine readability with a fresh ID, while the concurrently-created local candidate remains inert pending a valid new token

ROLE: Implementer
PHASE: PLAN-REVIEW
AUTHORITY: review-only
VERDICT: approve
DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-review-r2
PARENT_DISPATCH_ID: s4-matrix-t3-date-oracle-fix-plan-r1
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-TOKEN-WITHHELD-APPROVE-DOES-NOT-PARSE-T1-TOKEN-CARRIES-SAME-DEFECT-20260822-041055.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T3-DATE-ORACLE-REV1-APPROVE-20260822-025839.md; .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T3-DATE-ORACLE-REV1-ORACLE-C-DUAL-RESTORE-GATE-BOUND-FIXTURE-20260822-024647.md; .relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-T3-DATE-ORACLE-DISPATCH-20260822-040750.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate for this review correction. The Pair Planner must issue a fresh lineage-valid bare implementation token parented to this R2 ID before any further source, proof, or ref act. That token must explicitly disposition the inert local candidate `d406868`; this review neither retroactively authorizes it nor chooses adoption versus forward reconstruction. T1's separate landed-lineage disposition remains routed to the Orchestrator and master. No remote CI, push, PR mutation, merge, schema, deployment, or release; the release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T3 `a3501cc1728ca13289a8a4a96e49c9ee95e54698`; live but inert local candidate `d4068684e51f67d0a11fb6d2251178fb2a1a70ea`
SUPERSEDES: the substantively-correct but parser-false review `s4-matrix-t3-date-oracle-fix-plan-review-r1` at commit `713e790ee6cb27f69cdfdffbacabdd8ee236ba6d`; this successor uses a fresh ID and does not create a collision
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: APPROVE successor R2 — exact bare verdict parses true; rev1 plan bytes and the prior independent pressure test remain unchanged; next valid edge is a fresh Planner token parented to R2 and explicitly disposing the inert local candidate created under the lineage-invalid token

APPROVE.

## 1. Parser defect reproduced and corrected without an ID collision

The Planner's `041055` finding reproduces exactly. Calling the installed
`plan_review_approved` matcher returns `False` for the R1 review's bolded
`**VERDICT: APPROVE.**` prose and `True` for the bare header form used here:

```text
R1  s4-matrix-t3-date-oracle-fix-plan-review-r1  -> False
R2  s4-matrix-t3-date-oracle-fix-plan-review-r2  -> True
```

Root-mode lint also reports the existing `040750` token because its parent is R1. Per-file lint
was insufficient: it passed that token because the parent-verdict gate is evaluated only during
the lineage walk. This successor does not reuse R1's ID. Before filing, the R1 ID had exactly one
holder, the fresh R2 ID had zero, and the token ID had exactly one; no ambiguity is introduced.

## 2. Substantive approval is unchanged

The reviewed PLAN remains commit `e01de7f`, Git blob
`9b51c25baa24c84063abcd0a99a11fbcd2617e31`, SHA-256
`c15e5a99f600aff1f3aebd9c6525f62ad264a2271cdd8cfa97ee5e11191f0dbd`.
R1's independent pressure test remains valid and is incorporated here rather than silently
discarded:

- Oracle C has literal Orchestrator authority from `022336`, reaffirmed by `035347`.
- The unique pre-edit anchor and 7842-byte SHA-256 `b09f7352…` target were reproduced.
- Exact planned replacement yields 7868 bytes at SHA-256 `ca9f04e1…`.
- The named node passed in the scratch pressure test, the real-fixture locator returned exactly
  one repository, the raw output matched the planned string, and the empty-root locator control
  returned zero.
- The dual restore gates bind the scratch-mutated `fixtures.py` at `6776756f…` and the planned
  test target at `ca9f04e1…`; all six obligations and the one-file fence remain binding.

No plan byte, scope row, proof obligation, or technical conclusion changes in R2. The only review
correction is the machine-readable verdict plus a fresh collision-free dispatch identity.

## 3. Concurrent live state: preserve, do not launder

The Planner's `041055` relay accurately says that no valid token existed and records T3 at
`a3501cc`. By the time it was delivered to this Implementer session, a concurrent path had already:

1. filed token `040750` in docs commit `6f394d5`, after checking only per-file lint; and
2. created local source commit `d406868` containing the exact planned one-file bytes.

The root-mode measurement now proves the `040750` token lineage-invalid. Therefore `d406868` is
not accepted as authorized implementation merely because its bytes match the plan. It is LOCAL,
UNPUBLISHED, clean, and preserved as an inert candidate artifact; no further O-1 through O-6 work
continues under it, and this review does not retroactively grant the missing authority.

The next Pair Planner token must parent to `s4-matrix-t3-date-oracle-fix-plan-review-r2` and name
the disposition of `d406868` explicitly. Safe forward choices remain the Planner's to grant:

- adopt the exact inert candidate bytes as the starting artifact and authorize the remaining
  fixed-head proof obligations; or
- authorize a forward reconstruction sequence from `a3501cc` without rewriting immutable relay
  history.

Until that token arrives, no source, proof, ref, or integration act is authorized. This state is
reported rather than hidden because a correct final byte does not repair a missing lineage edge.

## 4. Separate T1 defect

The T1 R8 matcher result also reproduces `False`, while its parent ID has one holder, so the
Planner's landed-lineage finding is genuine. This review does not disposition it: T1's append-only
record question and the evidence-triggered R-3.40 item remain routed to the Orchestrator and master.
T1's product bytes and its pre-existing PID-1 topology attribution are not reopened here.

T3 remains not final and not panelable; T4 remains held. T2 stays final at `7688bbd`. No remote CI,
push, PR mutation, merge, publication, schema act, deployment, or release is authorized. The
release hold is ABSOLUTE.

ACTIONS_GIT_REF: review correction only. Read-only calls reproduced `plan_review_approved` false for R1 and T1 R8 and true for the known-good T2 precedent; root-mode lint reproduced the `040750` and T1 token parent-verdict errors; sole-ID counts, commits, status, target digest, and size were read. No source, test, candidate, worktree, or integration byte changed in this review act. This relay and one live-EOF INDEX append ride one explicit-path docs commit.
FINAL_GIT_STATUS_SHORT: only this successor review and its INDEX row are claimed by this act; the shared checkout's sibling-authored untracked paths remain preserved and unclaimed; T3 is clean at inert local `d406868`

CARRY LIST:
- fresh machine-readable successor approval ID `s4-matrix-t3-date-oracle-fix-plan-review-r2`; bare `VERDICT: approve` parses true
- substantive rev1 approval unchanged at plan commit e01de7f, blob 9b51c25, SHA-256 c15e5a99; exact one-file scope and six obligations remain binding
- old R1 review remains immutable and parser-false; no ID reuse or collision
- `040750` token is lineage-invalid under root mode; local `d406868` is inert, unaccepted, unpublished, and preserved rather than rewritten
- next Pair Planner token must parent to R2 and explicitly disposition the inert candidate before any proof or source act resumes
- T1 lineage defect remains separately routed; T3 not final or panelable; T4 held; no remote CI, push, PR mutation, merge, publication, schema, deployment, or release; release hold ABSOLUTE
