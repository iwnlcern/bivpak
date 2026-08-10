## SITREP (MERGE HAND-UP) — R-4.8 micro-fold verification PASS at `0ab998d`: the six human-lens must-fixes are ALL proven closed, and the R-4.8 review bar is MET at that exact head; handing up for the merge bar with THREE things the hand-up must not lose — (1) the published DRAFT PR #24 is STALE at `2341667`, TWO commits behind the reviewed head, so republication under a separate P5 token is owed BEFORE any merge acts on reviewed bytes; (2) the standing end-state-bytes condition-3 at the eventual merge base (this branch predates C/B2); (3) two aggregate items TRACKED-not-closed in the harness lineage

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-arm1-r48-merge-handup
PARENT_DISPATCH_ID: s4-matrix-arm1-r48-microfold-impl-complete
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: yes — the merge bar is master's/the operator's (condition-3 end-state-bytes + condition-4), and the PR republication is a separate OPERATOR P5 token; nothing here grants merge, publication, or release; the release hold is ABSOLUTE
DESIGN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
DESIGN_RECORD_KIND: design-doc
PLAN_LOCK_ID: docs/sprints/2026-08-04-s4-step4/plans/2026-08-09-s4-matrix-arm1-r48-carrier-plan.md
FROM: s4-matrix.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-matrix.implementer, master.orchestrator-planner
SUBJECT: SITREP — merge hand-up: six must-fixes closed at `0ab998d`; PR staleness, end-state-bytes condition, and two tracked items carried

## Verification result

Record (verbatim lens report + lead verification + synthesis):
`docs/sprints/2026-08-04-s4-step4/reviews/2026-08-10-s4-matrix-r48-microfold-verify-0ab998d.md`
(SHA-256 `ee1f5ef5b1202552140b89bcc6c008baaf7ffb8aaa454315346542042fe8a121`, sealed after
creation). Single owning lens per the approved sizing; 1 spawn = 1 finding-set + 0
stalls; PASS with zero Critical/Important/Minor findings.

**MFX-1 closed with a false-witness immunity ANALYSIS, not an assertion:** the prefix
predicate is immune to the workspace-directory witness by ANCHORING (`starts_with` at
position 0 with a component-boundary `/`, versus the position-free `find` that fell),
and the member predicate is immune to the immutable-JSON-key witness by ENCODING (the
computed needle `\/ws` leads with a backslash the bare key cannot supply) — and immune
to the workspace witness twice over, since it searches raw INPUT bytes containing no
filesystem path. The lens constructed the adversarial cases (including renaming the
workspace directory to `/ws`) and showed both predicates unaffected: a structural fix,
not a fixture accident. The single satisfying site is exactly the escaped string VALUE
the rewriter would act on. **MFX-2 closed** — the block's two surviving quantifiers
contribute zero assertions over an empty vector, so the new CHECK is the only assertion
pinning the outcome, stated positively.

**The mutation evidence reconciles, and the non-fatal requirement was proven from the
arithmetic:** four exact line numbers including the closing-paren attribution of the
three-line macros (the tell of a real run); the source FORCES exactly four failures and
forbids a fifth; and the assertion TOTAL is invariant at 62 across RED and GREEN — only
possible if both predicates are non-fatal, since a `REQUIRE` would have aborted each
case at its first failure. The lens also caught and CORRECTED its own near-finding
(exit-42 on Catch2 v2 semantics before verifying this repo pins v3.7.1's fixed
`TestFailureExitCode`), and was straight about its read-only limit: it did not derive
the absolute 62 from source and said so, resting the verdict on invariance and
forced-four instead.

## The six must-fixes — all closed

Five landed at `d234314` and were confirmed at depth by the prior check (`eb187d09…`):
H1/H2 hermeticity (all 16 pack sites guarded; the four-variable set closed against the
PRODUCTION input set; the constructed decoy a genuine RED-before/GREEN-after
falsifier), V2 loud duplicate insert, V3 stable-shape id-map compare, O1 ORACLE pin,
BR1 minimal-accept brackets. The two gating repairs (V1's proof and the decoy
post-state) closed at `0ab998d` per this record. **The R-4.8 review bar is MET at exact
head `0ab998d8431a20de80b8d769fb82c1350ed0728d`.**

## THREE things this hand-up must not lose

1. **The published PR is STALE — republication owed before merge.** `git ls-remote`
   shows PR #24's head is `2341667`; the reviewed head is `0ab998d`, TWO commits ahead
   (`d234314` lens-fold, `0ab998d` micro-fold). The PR as published does NOT contain the
   reviewed bytes. Merging it as-is would merge a head that failed this very review
   window. Republication of `0ab998d` is a separate OPERATOR P5 token — I am not
   assuming it and have taken no push/PR action.
2. **End-state-bytes condition-3 stands.** This branch sits on pre-C/B2 BASE
   `6047ab03`. Per the C→B2 provenance lesson, the five sealed records carry to any
   re-stacked head ONLY for files whose END-STATE bytes match `0ab998d` — the merge-time
   verification must compare per-file end-state hashes, never delta-equality.
3. **Two aggregate items TRACKED, not closed** (both outside the diff; the three test
   TUs feed neither the `biv` binary nor the harness): (a) the pinned-executable probe
   failure that vanished in isolation — the lens's standing rule restated at its
   sharpest, **"did not reproduce" is not "diagnosed"**: a failure present in the
   aggregate and absent alone is the signature of cross-case state leakage, and the
   isolated re-run is precisely the instrument that CANNOT discriminate flake from
   order-dependent defect; it belongs in the harness lineage as OPEN with the aggregate
   ordering recorded. (b) the inherited `harness-e2` 180s wrapper timeout — the
   already-ruled stale-ceiling class, reproduced at the pre-patch baseline, underlying
   harness exits 0 past the budget. Neither gates this fold; neither is this branch's
   debt. The Implementer correctly declined to call the full gate green while they are
   open, and I preserve that posture: **this hand-up asserts the REVIEW bar is met, not
   that the aggregate CTest row is green.**

## For the registry (master CC'd)

- **INFO-1 (candidate row):** empty-carrier vacuity remains theoretically open — an
  EMPTIED `kEngagedCarrier` makes both predicates trivially true (same class as MFX-1
  by a different edit; unreachable by any realistic edit path). A one-line
  `static_assert(kEngagedCarrier.size() > 1U && kEngagedCarrier.front() == '/')` shuts
  it. Deliberately NOT re-opening a hash-bound cycle for it — registry, not fold.
- **INFO-2:** the needle transform models solidus escaping only; widening the constant
  to `/ws/proj` fails for an ENCODING reason. Fails loud; recorded so a future widener
  does not lose time.
- **INFO-3 (scope honesty, worth carrying):** `packer_home` is write-only on the
  install path — no adapter reads it — so the byte-identity REQUIREs are true by
  construction today. These predicates are FIXTURE NON-VACUITY guards, NOT a behavioral
  pin on the carrier, and must not be cited as one. The behavioral pin arrives with the
  needle (R-4.10/R-4.11 head).
- Prior candidates stand: the needle-head verbatim-match constraint; the MF-6 absent-arm
  condition; T-2/F5 (codex CWD-relative defaults probe on degenerate HOME rows); T-5
  (length-not-structure extended rule).

## The ask

Take the merge bar: condition-3 (end-state-bytes at the eventual merge base) and
condition-4. Route the PR republication question to the operator as its own P5 token —
the reviewed head must be the published head before merge. Decided cells stand
(zero-session capture (b); A-obs-2 registered; extended grammar/UNC and oracle-2 at the
needle head). The release hold is ABSOLUTE.

ACTIONS_GIT_REF: docs lane only — this hand-up + its INDEX row + the sealed verification record ride one explicit-path commit (SHA lands after filing); product and test paths were touched by no action at this seat; the branch and PR #24 are untouched by this relay.
FINAL_GIT_STATUS_SHORT:
none — clean tree (matrix-seat paths; the shared checkout carries sibling seats' untracked relays, preserved untouched)
Fresh at 20260810-163003 before this relay + INDEX write; this relay, the INDEX row, and the verification record are this seat's working-tree delta at commit time.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R48-MERGE-HANDUP-SIX-MUSTFIX-CLOSED-PR-STALE-20260810-163003.md` → TO `s4.orchestrator-planner`
- verification record `ee1f5ef5…` at `0ab998d` → PASS; six must-fixes ALL closed; R-4.8 review bar MET
- PR #24 STALE at `2341667` (reviewed head `0ab998d`, two commits ahead) → republication owed under a separate OPERATOR P5 token BEFORE merge
- end-state-bytes condition-3 (branch predates C/B2 at `6047ab03`) → per-file end-state hashes, never delta-equality
- two aggregate items → TRACKED not closed in the harness lineage; review bar met ≠ aggregate row green
- INFO-1/2/3 + prior candidates → registry; release hold ABSOLUTE
